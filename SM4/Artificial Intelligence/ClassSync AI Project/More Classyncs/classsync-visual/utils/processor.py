"""
Timetable Processor for ClassSync Visual
Handles CSV processing and conversion to Excel format
"""

import pandas as pd
from datetime import datetime, timedelta
from pathlib import Path
import traceback
from typing import List, Dict, Any, Callable, Optional

from .excel_generator import ExcelGenerator

class TimetableProcessor:
    """Processes ClassSync CSV files into timetables"""
    
    def __init__(self, config_manager):
        self.config_manager = config_manager
        self.excel_generator = ExcelGenerator(config_manager)
        
        # Required CSV columns for ClassSync format
        self.required_columns = [
            "Course_Name", "Instructor", "Section", "Program",
            "Weekday", "Start_Time", "End_Time", "Room"
        ]
        
        self.weekdays = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday']
    
    def process_files(self, 
                     csv_files: List[str], 
                     output_folder: Path,
                     progress_callback: Optional[Callable] = None) -> Dict[str, Any]:
        """Process multiple CSV files"""
        
        results = {
            'successful': [],
            'failed': [],
            'conflicts': [],
            'statistics': {},
            'total_files': len(csv_files)
        }
        
        time_slots = self.config_manager.get_time_slots()
        
        for i, csv_file in enumerate(csv_files):
            try:
                # Update progress
                if progress_callback:
                    progress_callback(i, f"Processing {Path(csv_file).name}")
                
                # Process single file
                file_result = self.process_single_file(csv_file, output_folder, time_slots)
                
                if file_result['success']:
                    results['successful'].append(file_result)
                    
                    # Collect conflicts
                    if file_result.get('conflicts'):
                        results['conflicts'].extend(file_result['conflicts'])
                        
                else:
                    results['failed'].append({
                        'file': csv_file,
                        'error': file_result.get('error', 'Unknown error')
                    })
                    
            except Exception as e:
                results['failed'].append({
                    'file': csv_file,
                    'error': str(e)
                })
        
        # Final progress update
        if progress_callback:
            progress_callback(len(csv_files), "Processing complete")
        
        return results
    
    def process_single_file(self, csv_file: str, output_folder: Path, time_slots: List[str]) -> Dict[str, Any]:
        """Process a single CSV file"""
        
        result = {
            'file': csv_file,
            'success': False,
            'output_file': None,
            'conflicts': [],
            'stats': {}
        }
        
        try:
            # Load and validate CSV
            df = self.load_csv(csv_file)
            if df is None:
                result['error'] = "Failed to load CSV file"
                return result
            
            validation_result = self.validate_csv(df, csv_file)
            if not validation_result['valid']:
                result['error'] = validation_result['error']
                return result
            
            # Process data into timetable grid
            grid_data = self.create_timetable_grid(df, time_slots)
            
            # Detect conflicts
            conflicts = self.detect_conflicts(grid_data, csv_file)
            result['conflicts'] = conflicts
            
            # Generate Excel file
            output_filename = Path(csv_file).stem + ".xlsx"
            output_path = output_folder / output_filename
            
            excel_result = self.excel_generator.create_timetable(
                grid_data, 
                time_slots, 
                output_path,
                Path(csv_file).stem
            )
            
            if excel_result['success']:
                result['success'] = True
                result['output_file'] = str(output_path)
                result['stats'] = self.calculate_file_stats(df, grid_data)
            else:
                result['error'] = excel_result.get('error', 'Excel generation failed')
                
        except Exception as e:
            result['error'] = f"Unexpected error: {str(e)}"
            print(f"Error processing {csv_file}:")
            print(f"  Error: {str(e)}")
            print(f"  Type: {type(e).__name__}")
            import traceback
            traceback.print_exc()
        
        return result
    
    def load_csv(self, csv_file: str) -> Optional[pd.DataFrame]:
        """Load CSV file with encoding detection"""
        encodings = ['utf-8', 'latin-1', 'cp1252', 'iso-8859-1']
        
        for encoding in encodings:
            try:
                df = pd.read_csv(csv_file, encoding=encoding)
                # Clean column names
                df.columns = df.columns.str.strip()
                return df
            except UnicodeDecodeError:
                continue
            except Exception as e:
                print(f"Error reading {csv_file} with {encoding}: {e}")
                break
        
        return None
    
    def validate_csv(self, df: pd.DataFrame, filename: str) -> Dict[str, Any]:
        """Validate CSV format and required columns"""
        
        result = {'valid': True, 'error': None}
        
        # Check for required columns
        missing_columns = [col for col in self.required_columns if col not in df.columns]
        if missing_columns:
            result['valid'] = False
            result['error'] = f"Missing required columns: {', '.join(missing_columns)}"
            return result
        
        # Check for empty data
        if df.empty:
            result['valid'] = False
            result['error'] = "CSV file is empty"
            return result
        
        # Check for essential data
        essential_cols = ["Course_Name", "Weekday", "Start_Time", "End_Time", "Room"]
        df_clean = df.dropna(subset=essential_cols)
        
        if df_clean.empty:
            result['valid'] = False
            result['error'] = "No valid rows found (essential columns are empty)"
            return result
        
        # Validate time format
        time_format_errors = []
        for idx, row in df_clean.iterrows():
            try:
                datetime.strptime(str(row["Start_Time"]).strip(), "%H:%M")
                datetime.strptime(str(row["End_Time"]).strip(), "%H:%M")
            except ValueError:
                time_format_errors.append(f"Row {idx + 1}")
        
        if time_format_errors:
            result['valid'] = False
            result['error'] = f"Invalid time format in rows: {', '.join(time_format_errors[:5])}"
            if len(time_format_errors) > 5:
                result['error'] += f" (and {len(time_format_errors) - 5} more)"
        
        return result
    
    def create_timetable_grid(self, df: pd.DataFrame, time_slots: List[str]) -> Dict[str, Any]:
        """Create timetable grid structure from CSV data"""
        
        # Initialize grid: {Day -> {Room -> {Slot -> session_info}}}
        grid = {day: {} for day in self.weekdays}
        
        # Clean data
        df_clean = df.dropna(subset=["Course_Name", "Weekday", "Start_Time", "End_Time", "Room"])
        
        for _, row in df_clean.iterrows():
            day = str(row["Weekday"]).strip()
            room = str(row["Room"]).strip()
            
            # Skip invalid weekdays
            if day not in self.weekdays:
                continue
            
            # Initialize room if not exists
            if room not in grid[day]:
                grid[day][room] = {slot: None for slot in time_slots}
            
            try:
                # Parse times
                start_time = datetime.strptime(str(row["Start_Time"]).strip(), "%H:%M")
                end_time = datetime.strptime(str(row["End_Time"]).strip(), "%H:%M")
                
                # Create session info
                session_info = {
                    "course": str(row["Course_Name"]).strip(),
                    "section": str(row["Section"]).strip() if pd.notna(row["Section"]) else "",
                    "program": str(row["Program"]).strip() if pd.notna(row["Program"]) else "",
                    "instructor": str(row["Instructor"]).strip() if pd.notna(row["Instructor"]) else "",
                    "start_time": start_time,
                    "end_time": end_time
                }
                
                # Place session in overlapping time slots
                for slot in time_slots:
                    if self.session_overlaps_slot(start_time, end_time, slot):
                        grid[day][room][slot] = session_info
                        
            except ValueError as e:
                print(f"Skipping row due to time parsing error: {e}")
                continue
        
        return grid
    
    def session_overlaps_slot(self, session_start: datetime, session_end: datetime, time_slot: str) -> bool:
        """Check if a session overlaps with a time slot"""
        try:
            slot_start_str, slot_end_str = time_slot.split(" - ")
            slot_start = datetime.strptime(slot_start_str, "%H:%M")
            slot_end = datetime.strptime(slot_end_str, "%H:%M")
            
            # Check for overlap: sessions overlap if they don't end before the other starts
            return not (session_end <= slot_start or session_start >= slot_end)
            
        except ValueError:
            return False
    
    def detect_conflicts(self, grid: Dict[str, Any], filename: str) -> List[Dict[str, Any]]:
        """Detect scheduling conflicts"""
        conflicts = []
        
        if not self.config_manager.get('app_settings.check_conflicts'):
            return conflicts
        
        for day, rooms in grid.items():
            for room, slots in rooms.items():
                # Check for multiple sessions in same time slot
                for slot, session in slots.items():
                    if session is None:
                        continue
                    
                    # Check for time overlaps within the same room
                    session_start = session['start_time']
                    session_end = session['end_time']
                    
                    for other_slot, other_session in slots.items():
                        if (other_session is None or 
                            slot == other_slot or 
                            session == other_session):
                            continue
                        
                        other_start = other_session['start_time']
                        other_end = other_session['end_time']
                        
                        # Check for overlap
                        if not (session_end <= other_start or session_start >= other_end):
                            conflicts.append({
                                'file': filename,
                                'type': 'Room Conflict',
                                'day': day,
                                'room': room,
                                'session1': f"{session['course']} ({session_start.strftime('%H:%M')}-{session_end.strftime('%H:%M')})",
                                'session2': f"{other_session['course']} ({other_start.strftime('%H:%M')}-{other_end.strftime('%H:%M')})",
                                'time_slot': slot
                            })
        
        return conflicts
    
    def calculate_file_stats(self, df: pd.DataFrame, grid: Dict[str, Any]) -> Dict[str, Any]:
        """Calculate statistics for a processed file"""
        
        stats = {
            'total_courses': len(df['Course_Name'].unique()) if 'Course_Name' in df.columns else 0,
            'total_sessions': len(df),
            'unique_rooms': len(df['Room'].unique()) if 'Room' in df.columns else 0,
            'unique_instructors': len(df['Instructor'].unique()) if 'Instructor' in df.columns else 0,
            'days_with_classes': 0,
            'room_utilization': {}
        }
        
        # Count days with classes
        for day, rooms in grid.items():
            if any(any(session for session in slots.values()) for slots in rooms.values()):
                stats['days_with_classes'] += 1
        
        # Calculate room utilization
        for day, rooms in grid.items():
            for room, slots in rooms.items():
                occupied_slots = sum(1 for session in slots.values() if session is not None)
                total_slots = len(slots)
                if total_slots > 0:
                    utilization = (occupied_slots / total_slots) * 100
                    stats['room_utilization'][f"{day} - {room}"] = round(utilization, 1)
        
        return stats
"""
File Organizer
Organizes output files by different categories (section, teacher, room, program)
"""

import os
import pandas as pd
from typing import Dict, Any, List

class FileOrganizer:
    def __init__(self, config: Dict[str, Any]):
        self.config = config
        self.base_output_dir = "output"
        self.categories = config.get("output_settings", {}).get("export_categories", 
                                   ["section", "teacher", "room", "program"])
    
    def organize_by_categories(self, schedule_df: pd.DataFrame) -> Dict[str, str]:
        """Organize schedule files by different categories"""
        results = {}
        
        if schedule_df.empty:
            return results
        
        # Create base output directory
        os.makedirs(self.base_output_dir, exist_ok=True)
        
        # Generate organized files for each category
        for category in self.categories:
            if category == "section":
                category_results = self._organize_by_section(schedule_df)
            elif category == "teacher":
                category_results = self._organize_by_teacher(schedule_df)
            elif category == "room":
                category_results = self._organize_by_room(schedule_df)
            elif category == "program":
                category_results = self._organize_by_program(schedule_df)
            else:
                continue
            
            results.update(category_results)
        
        # Create master files
        master_results = self._create_master_files(schedule_df)
        results.update(master_results)
        
        return results
    
    def _organize_by_section(self, schedule_df: pd.DataFrame) -> Dict[str, str]:
        """Organize files by section"""
        results = {}
        section_dir = os.path.join(self.base_output_dir, "by_section")
        os.makedirs(section_dir, exist_ok=True)
        
        for section in schedule_df["Section"].unique():
            section_schedule = schedule_df[schedule_df["Section"] == section]
            
            # Create safe filename
            safe_section = self._sanitize_filename(str(section))
            
            # Save CSV
            csv_path = os.path.join(section_dir, f"section_{safe_section}.csv")
            section_schedule.to_csv(csv_path, index=False)
            results[f"section_{safe_section}_csv"] = csv_path
            
            # Save Excel if enabled
            if self.config.get("output_settings", {}).get("generate_excel", True):
                excel_path = os.path.join(section_dir, f"section_{safe_section}.xlsx")
                self._save_excel(section_schedule, excel_path, f"Section {section} Schedule")
                results[f"section_{safe_section}_excel"] = excel_path
        
        return results
    
    def _organize_by_teacher(self, schedule_df: pd.DataFrame) -> Dict[str, str]:
        """Organize files by teacher/instructor"""
        results = {}
        teacher_dir = os.path.join(self.base_output_dir, "by_teacher")
        os.makedirs(teacher_dir, exist_ok=True)
        
        for teacher in schedule_df["Instructor"].unique():
            teacher_schedule = schedule_df[schedule_df["Instructor"] == teacher]
            
            # Create safe filename
            safe_teacher = self._sanitize_filename(str(teacher))
            
            # Save CSV
            csv_path = os.path.join(teacher_dir, f"teacher_{safe_teacher}.csv")
            teacher_schedule.to_csv(csv_path, index=False)
            results[f"teacher_{safe_teacher}_csv"] = csv_path
            
            # Save Excel if enabled
            if self.config.get("output_settings", {}).get("generate_excel", True):
                excel_path = os.path.join(teacher_dir, f"teacher_{safe_teacher}.xlsx")
                self._save_excel(teacher_schedule, excel_path, f"Instructor {teacher} Schedule")
                results[f"teacher_{safe_teacher}_excel"] = excel_path
        
        return results
    
    def _organize_by_room(self, schedule_df: pd.DataFrame) -> Dict[str, str]:
        """Organize files by room"""
        results = {}
        room_dir = os.path.join(self.base_output_dir, "by_room")
        os.makedirs(room_dir, exist_ok=True)
        
        for room in schedule_df["Room"].unique():
            room_schedule = schedule_df[schedule_df["Room"] == room]
            
            # Create safe filename
            safe_room = self._sanitize_filename(str(room))
            
            # Save CSV
            csv_path = os.path.join(room_dir, f"room_{safe_room}.csv")
            room_schedule.to_csv(csv_path, index=False)
            results[f"room_{safe_room}_csv"] = csv_path
            
            # Save Excel if enabled
            if self.config.get("output_settings", {}).get("generate_excel", True):
                excel_path = os.path.join(room_dir, f"room_{safe_room}.xlsx")
                self._save_excel(room_schedule, excel_path, f"Room {room} Schedule")
                results[f"room_{safe_room}_excel"] = excel_path
        
        return results
    
    def _organize_by_program(self, schedule_df: pd.DataFrame) -> Dict[str, str]:
        """Organize files by program"""
        results = {}
        program_dir = os.path.join(self.base_output_dir, "by_program")
        os.makedirs(program_dir, exist_ok=True)
        
        for program in schedule_df["Program"].unique():
            program_schedule = schedule_df[schedule_df["Program"] == program]
            
            # Create safe filename
            safe_program = self._sanitize_filename(str(program))
            
            # Save CSV
            csv_path = os.path.join(program_dir, f"program_{safe_program}.csv")
            program_schedule.to_csv(csv_path, index=False)
            results[f"program_{safe_program}_csv"] = csv_path
            
            # Save Excel if enabled
            if self.config.get("output_settings", {}).get("generate_excel", True):
                excel_path = os.path.join(program_dir, f"program_{safe_program}.xlsx")
                self._save_excel(program_schedule, excel_path, f"Program {program} Schedule")
                results[f"program_{safe_program}_excel"] = excel_path
        
        return results
    
    def _create_master_files(self, schedule_df: pd.DataFrame) -> Dict[str, str]:
        """Create master files containing all data"""
        results = {}
        
        # Master CSV
        csv_path = os.path.join(self.base_output_dir, "master_schedule.csv")
        schedule_df.to_csv(csv_path, index=False)
        results["master_csv"] = csv_path
        
        # Master Excel with multiple sheets if enabled
        if self.config.get("output_settings", {}).get("generate_excel", True):
            excel_path = os.path.join(self.base_output_dir, "master_schedule.xlsx")
            self._create_master_excel(schedule_df, excel_path)
            results["master_excel"] = excel_path
        
        return results
    
    def _save_excel(self, data_df: pd.DataFrame, filepath: str, sheet_name: str = "Schedule"):
        """Save DataFrame to Excel with basic formatting"""
        try:
            with pd.ExcelWriter(filepath, engine='openpyxl') as writer:
                data_df.to_excel(writer, sheet_name=sheet_name, index=False)
                
                # Get workbook and worksheet
                workbook = writer.book
                worksheet = writer.sheets[sheet_name]
                
                # Basic formatting
                self._apply_basic_excel_formatting(worksheet)
        
        except Exception:
            # Fallback to simple CSV if Excel fails
            csv_path = filepath.replace('.xlsx', '.csv')
            data_df.to_csv(csv_path, index=False)
    
    def _create_master_excel(self, schedule_df: pd.DataFrame, filepath: str):
        """Create master Excel file with multiple sheets"""
        try:
            with pd.ExcelWriter(filepath, engine='openpyxl') as writer:
                # Main schedule
                schedule_df.to_excel(writer, sheet_name="Full Schedule", index=False)
                
                # By instructor
                for instructor in schedule_df["Instructor"].unique():
                    safe_name = self._sanitize_sheet_name(str(instructor))
                    instructor_data = schedule_df[schedule_df["Instructor"] == instructor]
                    instructor_data.to_excel(writer, sheet_name=f"Inst_{safe_name}"[:31], index=False)
                
                # By section
                for section in schedule_df["Section"].unique():
                    safe_name = self._sanitize_sheet_name(str(section))
                    section_data = schedule_df[schedule_df["Section"] == section]
                    section_data.to_excel(writer, sheet_name=f"Sect_{safe_name}"[:31], index=False)
                
                # By room
                for room in schedule_df["Room"].unique():
                    safe_name = self._sanitize_sheet_name(str(room))
                    room_data = schedule_df[schedule_df["Room"] == room]
                    room_data.to_excel(writer, sheet_name=f"Room_{safe_name}"[:31], index=False)
                
                # Apply formatting to all sheets
                for sheet_name in writer.sheets:
                    self._apply_basic_excel_formatting(writer.sheets[sheet_name])
        
        except Exception:
            # Fallback to simple CSV
            csv_path = filepath.replace('.xlsx', '.csv')
            schedule_df.to_csv(csv_path, index=False)
    
    def _apply_basic_excel_formatting(self, worksheet):
        """Apply basic formatting to Excel worksheet"""
        try:
            from openpyxl.styles import Font, PatternFill
            
            # Header formatting
            header_font = Font(bold=True)
            header_fill = PatternFill(start_color="4472C4", end_color="4472C4", fill_type="solid")
            
            # Apply to first row (headers)
            for cell in worksheet[1]:
                cell.font = header_font
                cell.fill = header_fill
            
            # Auto-adjust column widths
            for column in worksheet.columns:
                max_length = 0
                column_letter = column[0].column_letter
                
                for cell in column:
                    try:
                        if len(str(cell.value)) > max_length:
                            max_length = len(str(cell.value))
                    except:
                        pass
                
                adjusted_width = min(max_length + 2, 50)
                worksheet.column_dimensions[column_letter].width = adjusted_width
        
        except Exception:
            pass  # Ignore formatting errors
    
    def _sanitize_filename(self, filename: str) -> str:
        """Sanitize filename to be filesystem-safe"""
        # Remove or replace problematic characters
        invalid_chars = '<>:"/\\|?*'
        for char in invalid_chars:
            filename = filename.replace(char, '_')
        
        # Remove leading/trailing spaces and dots
        filename = filename.strip(' .')
        
        # Ensure not empty
        if not filename:
            filename = "unnamed"
        
        # Limit length
        return filename[:50]
    
    def _sanitize_sheet_name(self, sheet_name: str) -> str:
        """Sanitize sheet name for Excel compatibility"""
        # Excel sheet name restrictions
        invalid_chars = '[]:*?/\\'
        for char in invalid_chars:
            sheet_name = sheet_name.replace(char, '_')
        
        # Remove leading/trailing spaces
        sheet_name = sheet_name.strip()
        
        # Ensure not empty
        if not sheet_name:
            sheet_name = "Sheet"
        
        # Limit to 31 characters (Excel limit)
        return sheet_name[:31]
    
    def create_summary_report(self, schedule_df: pd.DataFrame, results: Dict[str, str]) -> str:
        """Create a summary report of generated files"""
        if schedule_df.empty:
            return "No schedule data to report"
        
        report_lines = [
            "Schedule Generation Summary",
            "=" * 40,
            f"Total Sessions: {len(schedule_df)}",
            f"Lab Sessions: {len(schedule_df[schedule_df['Is_Lab']])}",
            f"Theory Sessions: {len(schedule_df[~schedule_df['Is_Lab']])}",
            f"Instructors: {schedule_df['Instructor'].nunique()}",
            f"Rooms Used: {schedule_df['Room'].nunique()}",
            f"Programs: {schedule_df['Program'].nunique()}",
            f"Sections: {schedule_df['Section'].nunique()}",
            "",
            "Generated Files:",
            "-" * 20
        ]
        
        # Group results by category
        categories = {}
        for key, path in results.items():
            if "_" in key:
                category = key.split("_")[0]
                if category not in categories:
                    categories[category] = []
                categories[category].append(path)
        
        for category, files in categories.items():
            report_lines.append(f"{category.title()}: {len(files)} files")
        
        report_lines.extend([
            "",
            f"All files saved to: {self.base_output_dir}/",
            ""
        ])
        
        # Save report file
        report_path = os.path.join(self.base_output_dir, "generation_report.txt")
        try:
            with open(report_path, 'w', encoding='utf-8') as f:
                f.write('\n'.join(report_lines))
        except Exception:
            pass
        
        return '\n'.join(report_lines)
    
    def cleanup_old_files(self, keep_last: int = 5) -> bool:
        """Clean up old output files, keeping only the most recent"""
        try:
            if not os.path.exists(self.base_output_dir):
                return True
            
            # Get all subdirectories
            subdirs = [d for d in os.listdir(self.base_output_dir) 
                      if os.path.isdir(os.path.join(self.base_output_dir, d))]
            
            for subdir in subdirs:
                subdir_path = os.path.join(self.base_output_dir, subdir)
                files = [f for f in os.listdir(subdir_path) 
                        if os.path.isfile(os.path.join(subdir_path, f))]
                
                if len(files) > keep_last:
                    # Sort by modification time
                    files_with_time = [(f, os.path.getmtime(os.path.join(subdir_path, f))) 
                                      for f in files]
                    files_with_time.sort(key=lambda x: x[1], reverse=True)
                    
                    # Remove older files
                    for filename, _ in files_with_time[keep_last:]:
                        try:
                            os.remove(os.path.join(subdir_path, filename))
                        except Exception:
                            pass
            
            return True
        
        except Exception:
            return False
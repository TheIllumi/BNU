"""
Data Manager
Handles loading, validation, and processing of course and room data
"""

import os
import pandas as pd
from typing import Dict, List, Tuple, Optional

class DataManager:
    def __init__(self):
        self.data_dir = "data"
        self.courses_file = os.path.join(self.data_dir, "Courses.csv")
        self.rooms_file = os.path.join(self.data_dir, "Rooms.csv")
        
        # Ensure data directory exists
        os.makedirs(self.data_dir, exist_ok=True)
        
        self.courses_df = None
        self.rooms_df = None
        self.sessions_df = None
    
    def load_courses(self) -> pd.DataFrame:
        """Load and validate course data"""
        if not os.path.exists(self.courses_file):
            # Create empty courses file
            self._create_empty_courses_file()
        
        try:
            df = pd.read_csv(self.courses_file, encoding='utf-8')
        except UnicodeDecodeError:
            df = pd.read_csv(self.courses_file, encoding='latin-1')
        
        # Clean and validate columns
        df.columns = df.columns.str.strip()
        required_columns = ["Course Name", "Program", "Section", "Instructor"]
        
        # Check for missing columns
        missing_columns = [col for col in required_columns if col not in df.columns]
        if missing_columns:
            raise ValueError(f"Missing required columns: {missing_columns}")
        
        # Clean data
        df["Course Name"] = df["Course Name"].fillna("").astype(str).str.strip()
        df["Program"] = df["Program"].fillna("General").astype(str).str.strip()
        df["Section"] = df["Section"].fillna("A").astype(str).str.strip()
        df["Instructor"] = df["Instructor"].fillna("TBD").astype(str).str.strip()
        df["Hours per week"] = pd.to_numeric(df.get("Hours per week", 3), errors='coerce').fillna(3)
        
        # Remove empty courses
        df = df[df["Course Name"] != ""]
        
        # Add derived columns
        df["Is_Lab"] = df["Course Name"].str.contains("Lab", case=False, na=False)
        df["Course_Key"] = (df["Course Name"] + "_" + df["Program"] + "_" + df["Section"]).str.replace(" ", "_")
        
        self.courses_df = df
        return df
    
    def load_rooms(self) -> pd.DataFrame:
        """Load and validate room data"""
        if not os.path.exists(self.rooms_file):
            # Create empty rooms file
            self._create_empty_rooms_file()
        
        try:
            df = pd.read_csv(self.rooms_file, encoding='utf-8')
        except UnicodeDecodeError:
            df = pd.read_csv(self.rooms_file, encoding='latin-1')
        
        # Clean and validate columns
        df.columns = df.columns.str.strip()
        
        if "Rooms" not in df.columns:
            raise ValueError("Missing required column: Rooms")
        
        # Clean data
        df["Rooms"] = df["Rooms"].fillna("").astype(str).str.strip()
        df["Type"] = df.get("Type", "Theory").fillna("Theory").astype(str).str.strip()
        
        # Remove empty rooms
        df = df[df["Rooms"] != ""]
        
        # Ensure at least one room exists
        if df.empty:
            df = pd.DataFrame({"Rooms": ["Room-1"], "Type": ["Theory"]})
        
        self.rooms_df = df
        return df
    
    def create_sessions(self) -> pd.DataFrame:
        """Create session data from courses"""
        if self.courses_df is None:
            raise ValueError("Courses data not loaded")
        
        sessions = []
        
        for _, course in self.courses_df.iterrows():
            # Labs get 1 long session, theory courses get 2 shorter sessions
            session_count = 1 if course["Is_Lab"] else 2
            
            for session_num in range(1, session_count + 1):
                sessions.append({
                    "Course_Key": course["Course_Key"],
                    "Course_Name": course["Course Name"],
                    "Program": course["Program"],
                    "Section": course["Section"],
                    "Instructor": course["Instructor"],
                    "Is_Lab": course["Is_Lab"],
                    "Session_Number": session_num,
                    "Session_ID": f"{course['Course_Key']}_S{session_num}"
                })
        
        self.sessions_df = pd.DataFrame(sessions)
        return self.sessions_df
    
    def validate_courses(self) -> Tuple[bool, List[str]]:
        """Validate course data"""
        if self.courses_df is None:
            return False, ["Course data not loaded"]
        
        errors = []
        
        # Check for empty required fields
        for idx, row in self.courses_df.iterrows():
            row_num = idx + 1
            
            if not row["Course Name"]:
                errors.append(f"Row {row_num}: Course Name is required")
            
            if not row["Program"]:
                errors.append(f"Row {row_num}: Program is required")
            
            if not row["Section"]:
                errors.append(f"Row {row_num}: Section is required")
            
            if not row["Instructor"]:
                errors.append(f"Row {row_num}: Instructor is required")
        
        # Check for duplicate courses
        duplicates = self.courses_df.groupby("Course_Key").size()
        duplicate_courses = duplicates[duplicates > 1]
        if not duplicate_courses.empty:
            for course_key in duplicate_courses.index:
                errors.append(f"Duplicate course: {course_key}")
        
        return len(errors) == 0, errors
    
    def validate_rooms(self) -> Tuple[bool, List[str]]:
        """Validate room data"""
        if self.rooms_df is None:
            return False, ["Room data not loaded"]
        
        errors = []
        
        # Check for empty room names
        for idx, row in self.rooms_df.iterrows():
            row_num = idx + 1
            if not row["Rooms"]:
                errors.append(f"Row {row_num}: Room name is required")
        
        # Check for duplicate rooms
        duplicates = self.rooms_df.groupby("Rooms").size()
        duplicate_rooms = duplicates[duplicates > 1]
        if not duplicate_rooms.empty:
            for room_name in duplicate_rooms.index:
                errors.append(f"Duplicate room: {room_name}")
        
        # Ensure we have at least one room
        if self.rooms_df.empty:
            errors.append("At least one room is required")
        
        return len(errors) == 0, errors
    
    def get_summary(self) -> Dict[str, any]:
        """Get data summary statistics"""
        summary = {
            "courses": {
                "total": 0,
                "lab_courses": 0,
                "theory_courses": 0,
                "programs": 0,
                "sections": 0,
                "instructors": 0
            },
            "rooms": {
                "total": 0,
                "lab_rooms": 0,
                "theory_rooms": 0
            },
            "sessions": {
                "total": 0
            }
        }
        
        if self.courses_df is not None:
            summary["courses"]["total"] = len(self.courses_df)
            summary["courses"]["lab_courses"] = len(self.courses_df[self.courses_df["Is_Lab"]])
            summary["courses"]["theory_courses"] = len(self.courses_df[~self.courses_df["Is_Lab"]])
            summary["courses"]["programs"] = self.courses_df["Program"].nunique()
            summary["courses"]["sections"] = self.courses_df["Section"].nunique()
            summary["courses"]["instructors"] = self.courses_df["Instructor"].nunique()
        
        if self.rooms_df is not None:
            summary["rooms"]["total"] = len(self.rooms_df)
            summary["rooms"]["lab_rooms"] = len(self.rooms_df[self.rooms_df["Type"].str.contains("Lab", case=False, na=False)])
            summary["rooms"]["theory_rooms"] = len(self.rooms_df[~self.rooms_df["Type"].str.contains("Lab", case=False, na=False)])
        
        if self.sessions_df is not None:
            summary["sessions"]["total"] = len(self.sessions_df)
        
        return summary
    
    def save_courses(self, df: pd.DataFrame) -> bool:
        """Save courses data to file"""
        try:
            df.to_csv(self.courses_file, index=False, encoding='utf-8')
            self.courses_df = df
            return True
        except Exception:
            return False
    
    def save_rooms(self, df: pd.DataFrame) -> bool:
        """Save rooms data to file"""
        try:
            df.to_csv(self.rooms_file, index=False, encoding='utf-8')
            self.rooms_df = df
            return True
        except Exception:
            return False
    
    def _create_empty_courses_file(self):
        """Create empty courses CSV file with headers"""
        headers = ["Course Name", "Hours per week", "Program", "Section", "Instructor"]
        df = pd.DataFrame(columns=headers)
        df.to_csv(self.courses_file, index=False, encoding='utf-8')
    
    def _create_empty_rooms_file(self):
        """Create empty rooms CSV file with headers"""
        headers = ["Rooms", "Type"]
        df = pd.DataFrame(columns=headers)
        df.to_csv(self.rooms_file, index=False, encoding='utf-8')
    
    def reload_data(self) -> bool:
        """Reload all data from files"""
        try:
            self.load_courses()
            self.load_rooms()
            self.create_sessions()
            return True
        except Exception:
            return False
    
    def export_data(self, export_dir: str) -> bool:
        """Export all data to specified directory"""
        try:
            os.makedirs(export_dir, exist_ok=True)
            
            if self.courses_df is not None:
                self.courses_df.to_csv(os.path.join(export_dir, "courses_export.csv"), index=False)
            
            if self.rooms_df is not None:
                self.rooms_df.to_csv(os.path.join(export_dir, "rooms_export.csv"), index=False)
            
            if self.sessions_df is not None:
                self.sessions_df.to_csv(os.path.join(export_dir, "sessions_export.csv"), index=False)
            
            return True
        except Exception:
            return False
"""
Data loading utilities for ClassSync AI.

This module handles loading and parsing of input data from various
sources including CSV files, JSON configurations, and databases.
"""

import csv
import json
import yaml
import logging
from pathlib import Path
from typing import List, Dict, Any, Optional
from datetime import time, datetime

from ..core.models import (
    Course, Room, Instructor, Session, TimeSlot,
    RoomType, SessionType, SchedulingConstraints
)


logger = logging.getLogger(__name__)


class DataLoader:
    """Handles loading of all input data."""
    
    def __init__(self, data_dir: str = "data"):
        """
        Initialize data loader.
        
        Args:
            data_dir: Directory containing data files
        """
        self.data_dir = Path(data_dir)
        self.data_dir.mkdir(exist_ok=True)
        
    def load_courses(self, filename: str = "Courses_Processed.csv") -> List[Course]:
        """
        Load courses from CSV file.
        
        Args:
            filename: Name of the CSV file
            
        Returns:
            List of Course objects
        """
        filepath = self.data_dir / filename
        if not filepath.exists():
            logger.error(f"Course file not found: {filepath}")
            return []
        
        courses = []
        instructors_cache = {}
        
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                reader = csv.DictReader(f)
                
                for row in reader:
                    # Clean data
                    row = {k.strip(): v.strip() if v else '' for k, v in row.items()}
                    
                    # Get or create instructor
                    instructor_name = row.get('Instructor', 'Unknown')
                    if instructor_name not in instructors_cache:
                        instructors_cache[instructor_name] = Instructor(
                            instructor_id=f"inst_{len(instructors_cache)}",
                            name=instructor_name
                        )
                    
                    # Determine course type
                    course_name = row.get('Course Name', '')
                    if 'lab' in course_name.lower():
                        course_type = SessionType.LAB
                    else:
                        course_type = SessionType.LECTURE
                    
                    # Create course
                    course = Course(
                        course_id=f"course_{len(courses)}",
                        name=course_name,
                        program=row.get('Program', ''),
                        section=row.get('Section', ''),
                        hours_per_week=int(row.get('Hours per week', 0)),
                        course_type=course_type,
                        instructor=instructors_cache[instructor_name]
                    )
                    
                    courses.append(course)
                    
        except Exception as e:
            logger.error(f"Error loading courses: {e}")
        
        logger.info(f"Loaded {len(courses)} courses")
        return courses
    
    def load_rooms(self, filename: str = "Rooms.csv") -> List[Room]:
        """
        Load rooms from CSV file.
        
        Args:
            filename: Name of the CSV file
            
        Returns:
            List of Room objects
        """
        filepath = self.data_dir / filename
        if not filepath.exists():
            logger.error(f"Room file not found: {filepath}")
            return []
        
        rooms = []
        
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                reader = csv.DictReader(f)
                
                for row in reader:
                    # Clean data
                    row = {k.strip(): v.strip() if v else '' for k, v in row.items()}
                    
                    # Determine room type
                    room_type_str = row.get('Type', 'theory').lower()
                    if room_type_str == 'lab':
                        room_type = RoomType.LAB
                    elif room_type_str == 'theory':
                        room_type = RoomType.THEORY
                    else:
                        room_type = RoomType.HYBRID
                    
                    # Create room
                    room = Room(
                        room_id=f"room_{len(rooms)}",
                        name=row.get('Rooms', row.get('Room Name', '')),
                        room_type=room_type,
                        capacity=int(row.get('Capacity', 0)) if row.get('Capacity') else 50
                    )
                    
                    rooms.append(room)
                    
        except Exception as e:
            logger.error(f"Error loading rooms: {e}")
        
        logger.info(f"Loaded {len(rooms)} rooms")
        return rooms
    
    def create_sessions(self, courses: List[Course]) -> List[Session]:
        """
        Create sessions from courses.
        
        Args:
            courses: List of courses
            
        Returns:
            List of Session objects
        """
        sessions = []
        session_counter = 0
        
        for course in courses:
            # Determine number of sessions based on course type
            if course.course_type == SessionType.LAB:
                num_sessions = 1  # Labs typically have one long session
                duration_minutes = 180  # 3 hours
            else:
                num_sessions = 2  # Theory courses have 2 sessions per week
                duration_minutes = 90  # 1.5 hours each
            
            for session_num in range(num_sessions):
                session = Session(
                    session_id=f"session_{session_counter}",
                    course=course,
                    session_number=session_num + 1,
                    duration_minutes=duration_minutes,
                    session_type=course.course_type,
                    requires_lab=(course.course_type == SessionType.LAB)
                )
                sessions.append(session)
                session_counter += 1
        
        logger.info(f"Created {len(sessions)} sessions from {len(courses)} courses")
        return sessions
    
    def load_constraints(self, filename: str = "constraints.yaml") -> SchedulingConstraints:
        """
        Load scheduling constraints from configuration file.
        
        Args:
            filename: Name of the configuration file
            
        Returns:
            SchedulingConstraints object
        """
        filepath = self.data_dir / filename
        
        # Try YAML first, then JSON
        if not filepath.exists():
            filepath = filepath.with_suffix('.json')
        
        if not filepath.exists():
            logger.warning(f"Constraints file not found, using defaults")
            return SchedulingConstraints()
        
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                if filepath.suffix == '.yaml':
                    data = yaml.safe_load(f)
                else:
                    data = json.load(f)
            
            # Parse constraints
            constraints = SchedulingConstraints(
                max_daily_hours_per_instructor=data.get('max_daily_hours_per_instructor', 8),
                max_consecutive_sessions=data.get('max_consecutive_sessions', 3),
                min_break_minutes=data.get('min_break_minutes', 15),
                preferred_gap_minutes=data.get('preferred_gap_minutes', 30),
                allow_evening_classes=data.get('allow_evening_classes', True),
                priority_sections=data.get('priority_sections', [])
            )
            
            # Parse evening threshold
            if 'evening_threshold' in data:
                hour, minute = map(int, data['evening_threshold'].split(':'))
                constraints.evening_threshold = time(hour, minute)
            
            # Parse blocked slots
            if 'blocked_slots' in data:
                for slot_data in data['blocked_slots']:
                    constraints.blocked_slots.append(
                        TimeSlot(
                            day=slot_data['day'],
                            start_time=time(*map(int, slot_data['start'].split(':'))),
                            end_time=time(*map(int, slot_data['end'].split(':')))
                        )
                    )
            
            logger.info("Loaded constraints from configuration")
            return constraints
            
        except Exception as e:
            logger.error(f"Error loading constraints: {e}")
            return SchedulingConstraints()
    
    def generate_time_slots(
        self,
        config: Optional[Dict[str, Any]] = None
    ) -> List[TimeSlot]:
        """
        Generate time slots based on configuration.
        
        Args:
            config: Time slot configuration
            
        Returns:
            List of TimeSlot objects
        """
        if config is None:
            config = self._load_time_config()
        
        time_slots = []
        
        working_days = config.get('working_days', 
                                  ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday'])
        
        daily_start = config.get('daily_start', '08:00')
        daily_end = config.get('daily_end', '17:00')
        slot_duration = config.get('slot_duration_minutes', 90)
        
        # Parse times
        start_hour, start_min = map(int, daily_start.split(':'))
        end_hour, end_min = map(int, daily_end.split(':'))
        
        start_time = datetime.strptime(daily_start, '%H:%M')
        end_time = datetime.strptime(daily_end, '%H:%M')
        
        # Generate slots for each day
        for day in working_days:
            current_time = start_time
            
            while current_time < end_time:
                slot_end = current_time + timedelta(minutes=slot_duration)
                if slot_end > end_time:
                    break
                
                time_slot = TimeSlot(
                    day=day,
                    start_time=current_time.time(),
                    end_time=slot_end.time()
                )
                
                # Check for VC slots or other special cases
                if not self._is_blocked_slot(time_slot, config):
                    time_slots.append(time_slot)
                
                current_time = slot_end
        
        logger.info(f"Generated {len(time_slots)} time slots")
        return time_slots
    
    def _load_time_config(self) -> Dict[str, Any]:
        """Load time configuration."""
        config_file = self.data_dir / "time_config.json"
        
        if config_file.exists():
            with open(config_file, 'r') as f:
                return json.load(f)
        
        # Default configuration
        return {
            'working_days': ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday'],
            'daily_start': '08:00',
            'daily_end': '17:00',
            'slot_duration_minutes': 90,
            'vc_slot_days': ['Monday', 'Tuesday', 'Friday'],
            'vc_slot_time': ['12:30', '14:00']
        }
    
    def _is_blocked_slot(self, time_slot: TimeSlot, config: Dict[str, Any]) -> bool:
        """Check if a time slot is blocked."""
        # Check for VC slots
        if 'vc_slot_days' in config and 'vc_slot_time' in config:
            if time_slot.day in config['vc_slot_days']:
                vc_start = datetime.strptime(config['vc_slot_time'][0], '%H:%M').time()
                vc_end = datetime.strptime(config['vc_slot_time'][1], '%H:%M').time()
                
                if (time_slot.start_time >= vc_start and 
                    time_slot.start_time < vc_end):
                    return True
        
        return False


class ConfigLoader:
    """Handles loading of configuration files."""
    
    @staticmethod
    def load_config(config_path: str = "config/default_config.yaml") -> Dict[str, Any]:
        """
        Load main configuration file.
        
        Args:
            config_path: Path to configuration file
            
        Returns:
            Configuration dictionary
        """
        config_file = Path(config_path)
        
        if not config_file.exists():
            logger.warning(f"Config file not found: {config_path}, using defaults")
            return ConfigLoader._get_default_config()
        
        try:
            with open(config_file, 'r', encoding='utf-8') as f:
                if config_file.suffix == '.yaml':
                    config = yaml.safe_load(f)
                else:
                    config = json.load(f)
            
            logger.info(f"Loaded configuration from {config_path}")
            return config
            
        except Exception as e:
            logger.error(f"Error loading config: {e}")
            return ConfigLoader._get_default_config()
    
    @staticmethod
    def _get_default_config() -> Dict[str, Any]:
        """Get default configuration."""
        return {
            'algorithm': {
                'name': 'genetic',
                'parameters': {
                    'population_size': 50,
                    'generations': 100,
                    'mutation_rate': 0.15,
                    'elite_size': 5
                }
            },
            'output': {
                'format': ['excel', 'csv'],
                'directory': 'output'
            },
            'logging': {
                'level': 'INFO',
                'file': 'classsync.log'
            }
        }


from datetime import timedelta
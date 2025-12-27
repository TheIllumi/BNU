"""
Data models for ClassSync AI.

This module contains all the data classes and models used throughout
the application for representing courses, rooms, sessions, and schedules.
"""

from dataclasses import dataclass, field
from typing import List, Optional, Dict, Any
from datetime import time, datetime
from enum import Enum


class RoomType(Enum):
    """Enumeration for room types."""
    LAB = "lab"
    THEORY = "theory"
    HYBRID = "hybrid"


class SessionType(Enum):
    """Enumeration for session types."""
    LECTURE = "lecture"
    LAB = "lab"
    TUTORIAL = "tutorial"
    SEMINAR = "seminar"


@dataclass
class TimeSlot:
    """Represents a time slot in the schedule."""
    day: str
    start_time: time
    end_time: time
    
    def __str__(self) -> str:
        return f"{self.day} {self.start_time.strftime('%H:%M')}-{self.end_time.strftime('%H:%M')}"
    
    def overlaps_with(self, other: 'TimeSlot') -> bool:
        """Check if this time slot overlaps with another."""
        if self.day != other.day:
            return False
        return not (self.end_time <= other.start_time or self.start_time >= other.end_time)
    
    def duration_minutes(self) -> int:
        """Calculate duration in minutes."""
        start_dt = datetime.combine(datetime.today(), self.start_time)
        end_dt = datetime.combine(datetime.today(), self.end_time)
        return int((end_dt - start_dt).total_seconds() / 60)


@dataclass
class Room:
    """Represents a room/classroom."""
    room_id: str
    name: str
    room_type: RoomType
    capacity: int = 0
    features: List[str] = field(default_factory=list)
    building: Optional[str] = None
    floor: Optional[int] = None
    
    def __hash__(self) -> int:
        return hash(self.room_id)
    
    def is_suitable_for(self, session_type: SessionType) -> bool:
        """Check if room is suitable for a session type."""
        if session_type == SessionType.LAB:
            return self.room_type in [RoomType.LAB, RoomType.HYBRID]
        return self.room_type in [RoomType.THEORY, RoomType.HYBRID]


@dataclass
class Instructor:
    """Represents an instructor/teacher."""
    instructor_id: str
    name: str
    department: Optional[str] = None
    email: Optional[str] = None
    max_daily_hours: int = 8
    preferred_times: List[TimeSlot] = field(default_factory=list)
    blocked_times: List[TimeSlot] = field(default_factory=list)
    
    def __hash__(self) -> int:
        return hash(self.instructor_id)


@dataclass
class Course:
    """Represents a course."""
    course_id: str
    name: str
    program: str
    section: str
    hours_per_week: int
    course_type: SessionType
    instructor: Instructor
    enrolled_students: int = 0
    prerequisites: List[str] = field(default_factory=list)
    
    def __str__(self) -> str:
        return f"{self.name} - {self.program}{self.section}"
    
    def get_key(self) -> str:
        """Generate unique key for the course."""
        return f"{self.name}_{self.program}_{self.section}"


@dataclass
class Session:
    """Represents a scheduled session."""
    session_id: str
    course: Course
    session_number: int
    duration_minutes: int
    session_type: SessionType
    requires_lab: bool = False
    
    def __str__(self) -> str:
        return f"{self.course} - Session {self.session_number}"
    
    def get_required_slots(self, slot_duration: int) -> int:
        """Calculate number of time slots required."""
        return (self.duration_minutes + slot_duration - 1) // slot_duration


@dataclass
class ScheduledSession:
    """Represents a session that has been scheduled."""
    session: Session
    time_slot: TimeSlot
    room: Room
    is_forced: bool = False
    force_strategy: Optional[str] = None
    conflicts: List[str] = field(default_factory=list)
    
    def __str__(self) -> str:
        return f"{self.session} @ {self.time_slot} in {self.room.name}"
    
    def has_conflicts(self) -> bool:
        """Check if session has any conflicts."""
        return len(self.conflicts) > 0


@dataclass
class Schedule:
    """Represents a complete schedule."""
    schedule_id: str
    sessions: List[ScheduledSession] = field(default_factory=list)
    fitness_score: float = 0.0
    metadata: Dict[str, Any] = field(default_factory=dict)
    
    def add_session(self, scheduled_session: ScheduledSession) -> None:
        """Add a scheduled session to the schedule."""
        self.sessions.append(scheduled_session)
    
    def get_sessions_by_day(self, day: str) -> List[ScheduledSession]:
        """Get all sessions for a specific day."""
        return [s for s in self.sessions if s.time_slot.day == day]
    
    def get_sessions_by_instructor(self, instructor: Instructor) -> List[ScheduledSession]:
        """Get all sessions for a specific instructor."""
        return [s for s in self.sessions if s.session.course.instructor == instructor]
    
    def get_sessions_by_room(self, room: Room) -> List[ScheduledSession]:
        """Get all sessions for a specific room."""
        return [s for s in self.sessions if s.room == room]
    
    def get_sessions_by_section(self, section: str) -> List[ScheduledSession]:
        """Get all sessions for a specific section."""
        return [s for s in self.sessions if s.session.course.section == section]
    
    def to_dict(self) -> Dict[str, Any]:
        """Convert schedule to dictionary representation."""
        return {
            'schedule_id': self.schedule_id,
            'fitness_score': self.fitness_score,
            'total_sessions': len(self.sessions),
            'sessions': [
                {
                    'course': str(s.session.course),
                    'session_number': s.session.session_number,
                    'day': s.time_slot.day,
                    'start_time': s.time_slot.start_time.strftime('%H:%M'),
                    'end_time': s.time_slot.end_time.strftime('%H:%M'),
                    'room': s.room.name,
                    'instructor': s.session.course.instructor.name,
                    'is_forced': s.is_forced
                }
                for s in self.sessions
            ],
            'metadata': self.metadata
        }


@dataclass
class SchedulingConstraints:
    """Represents scheduling constraints."""
    max_daily_hours_per_instructor: int = 8
    max_consecutive_sessions: int = 3
    min_break_minutes: int = 15
    preferred_gap_minutes: int = 30
    allow_evening_classes: bool = True
    evening_threshold: time = time(16, 0)
    blocked_slots: List[TimeSlot] = field(default_factory=list)
    priority_sections: List[str] = field(default_factory=list)
    
    def to_dict(self) -> Dict[str, Any]:
        """Convert constraints to dictionary."""
        return {
            'max_daily_hours_per_instructor': self.max_daily_hours_per_instructor,
            'max_consecutive_sessions': self.max_consecutive_sessions,
            'min_break_minutes': self.min_break_minutes,
            'preferred_gap_minutes': self.preferred_gap_minutes,
            'allow_evening_classes': self.allow_evening_classes,
            'evening_threshold': self.evening_threshold.strftime('%H:%M'),
            'blocked_slots': [str(slot) for slot in self.blocked_slots],
            'priority_sections': self.priority_sections
        }
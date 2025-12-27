"""
Constraint validation and management for ClassSync AI.

This module handles validation of scheduling constraints and provides
methods to check constraint violations during scheduling.
"""

from typing import List, Dict, Any, Optional, Tuple
from datetime import time, datetime, timedelta
import logging

from .models import (
    ScheduledSession, Session, Room, TimeSlot,
    SchedulingConstraints, Schedule, Instructor
)


logger = logging.getLogger(__name__)


class ConstraintValidator:
    """Validates and checks scheduling constraints."""
    
    def validate_constraints(self, constraints: SchedulingConstraints) -> Dict[str, Any]:
        """
        Validate that constraints are logical and consistent.
        
        Args:
            constraints: Constraints to validate
            
        Returns:
            Dictionary with validation results
        """
        errors = []
        warnings = []
        
        # Check daily hours
        if constraints.max_daily_hours_per_instructor <= 0:
            errors.append("Max daily hours must be positive")
        elif constraints.max_daily_hours_per_instructor > 12:
            warnings.append("Max daily hours > 12 may be unrealistic")
        
        # Check consecutive sessions
        if constraints.max_consecutive_sessions <= 0:
            errors.append("Max consecutive sessions must be positive")
        
        # Check break times
        if constraints.min_break_minutes < 0:
            errors.append("Min break minutes cannot be negative")
        
        if constraints.preferred_gap_minutes < constraints.min_break_minutes:
            warnings.append("Preferred gap is less than minimum break")
        
        # Check evening threshold
        if constraints.evening_threshold < time(8, 0):
            warnings.append("Evening threshold before 8 AM seems unusual")
        elif constraints.evening_threshold > time(22, 0):
            warnings.append("Evening threshold after 10 PM seems late")
        
        return {
            'valid': len(errors) == 0,
            'errors': errors,
            'warnings': warnings
        }
    
    def check_hard_constraints(
        self,
        session: Session,
        time_slot: TimeSlot,
        room: Room,
        current_schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> Tuple[bool, List[str]]:
        """
        Check if placing a session violates hard constraints.
        
        Args:
            session: Session to place
            time_slot: Proposed time slot
            room: Proposed room
            current_schedule: Current partial schedule
            constraints: Scheduling constraints
            
        Returns:
            Tuple of (is_valid, list_of_violations)
        """
        violations = []
        
        # Check room conflicts
        if self._has_room_conflict(room, time_slot, current_schedule):
            violations.append("Room already occupied")
        
        # Check instructor conflicts
        if self._has_instructor_conflict(session.course.instructor, time_slot, current_schedule):
            violations.append("Instructor has another class")
        
        # Check section conflicts
        if self._has_section_conflict(session.course.section, time_slot, current_schedule):
            violations.append("Section has another class")
        
        # Check instructor daily hours
        if self._exceeds_daily_hours(session.course.instructor, time_slot, 
                                    current_schedule, constraints):
            violations.append("Exceeds instructor daily hour limit")
        
        # Check blocked slots
        if self._is_blocked_slot(time_slot, constraints):
            violations.append("Time slot is blocked")
        
        # Check room suitability
        if not room.is_suitable_for(session.session_type):
            violations.append(f"Room not suitable for {session.session_type.value}")
        
        return len(violations) == 0, violations
    
    def check_soft_constraints(
        self,
        session: Session,
        time_slot: TimeSlot,
        room: Room,
        current_schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> Dict[str, float]:
        """
        Calculate soft constraint penalties.
        
        Args:
            session: Session to place
            time_slot: Proposed time slot
            room: Proposed room
            current_schedule: Current partial schedule
            constraints: Scheduling constraints
            
        Returns:
            Dictionary of penalty scores
        """
        penalties = {}
        
        # Evening class penalty
        if (not constraints.allow_evening_classes and 
            time_slot.start_time >= constraints.evening_threshold):
            penalties['evening_class'] = 10.0
        elif time_slot.start_time >= constraints.evening_threshold:
            penalties['evening_class'] = 3.0
        
        # Consecutive sessions penalty
        consecutive = self._count_consecutive_sessions(
            session.course.instructor, time_slot, current_schedule
        )
        if consecutive > constraints.max_consecutive_sessions:
            penalties['consecutive_sessions'] = 5.0 * (consecutive - constraints.max_consecutive_sessions)
        
        # Gap preference penalty
        gap_penalty = self._calculate_gap_penalty(
            session.course.instructor, time_slot, current_schedule, constraints
        )
        if gap_penalty > 0:
            penalties['gap_preference'] = gap_penalty
        
        # Room change penalty for same section
        room_changes = self._count_room_changes(
            session.course.section, room, time_slot, current_schedule
        )
        if room_changes > 0:
            penalties['room_changes'] = 2.0 * room_changes
        
        # Early morning penalty (before 9 AM)
        if time_slot.start_time < time(9, 0):
            penalties['early_morning'] = 2.0
        
        # Late afternoon penalty (after 5 PM)
        if time_slot.end_time > time(17, 0):
            penalties['late_afternoon'] = 2.0
        
        return penalties
    
    def _has_room_conflict(self, room: Room, time_slot: TimeSlot, 
                          schedule: Schedule) -> bool:
        """Check if room is already occupied."""
        for scheduled in schedule.sessions:
            if (scheduled.room == room and 
                scheduled.time_slot.overlaps_with(time_slot)):
                return True
        return False
    
    def _has_instructor_conflict(self, instructor: Instructor, time_slot: TimeSlot,
                                schedule: Schedule) -> bool:
        """Check if instructor has another class."""
        for scheduled in schedule.sessions:
            if (scheduled.session.course.instructor == instructor and
                scheduled.time_slot.overlaps_with(time_slot)):
                return True
        return False
    
    def _has_section_conflict(self, section: str, time_slot: TimeSlot,
                            schedule: Schedule) -> bool:
        """Check if section has another class."""
        for scheduled in schedule.sessions:
            if (scheduled.session.course.section == section and
                scheduled.time_slot.overlaps_with(time_slot)):
                return True
        return False
    
    def _exceeds_daily_hours(self, instructor: Instructor, time_slot: TimeSlot,
                           schedule: Schedule, constraints: SchedulingConstraints) -> bool:
        """Check if adding session exceeds daily hour limit."""
        daily_minutes = 0
        
        for scheduled in schedule.sessions:
            if (scheduled.session.course.instructor == instructor and
                scheduled.time_slot.day == time_slot.day):
                daily_minutes += scheduled.time_slot.duration_minutes()
        
        daily_minutes += time_slot.duration_minutes()
        daily_hours = daily_minutes / 60
        
        return daily_hours > constraints.max_daily_hours_per_instructor
    
    def _is_blocked_slot(self, time_slot: TimeSlot, 
                        constraints: SchedulingConstraints) -> bool:
        """Check if time slot is blocked."""
        for blocked in constraints.blocked_slots:
            if blocked.overlaps_with(time_slot):
                return True
        return False
    
    def _count_consecutive_sessions(self, instructor: Instructor, time_slot: TimeSlot,
                                   schedule: Schedule) -> int:
        """Count consecutive sessions for an instructor."""
        instructor_sessions = [
            s for s in schedule.get_sessions_by_instructor(instructor)
            if s.time_slot.day == time_slot.day
        ]
        
        if not instructor_sessions:
            return 1
        
        # Sort by start time
        instructor_sessions.sort(key=lambda x: x.time_slot.start_time)
        
        # Find where this session would fit
        consecutive_count = 1
        
        for scheduled in instructor_sessions:
            # Check if adjacent
            if (scheduled.time_slot.end_time == time_slot.start_time or
                scheduled.time_slot.start_time == time_slot.end_time):
                consecutive_count += 1
        
        return consecutive_count
    
    def _calculate_gap_penalty(self, instructor: Instructor, time_slot: TimeSlot,
                              schedule: Schedule, constraints: SchedulingConstraints) -> float:
        """Calculate penalty for gaps between sessions."""
        instructor_sessions = [
            s for s in schedule.get_sessions_by_instructor(instructor)
            if s.time_slot.day == time_slot.day
        ]
        
        if not instructor_sessions:
            return 0.0
        
        penalty = 0.0
        
        for scheduled in instructor_sessions:
            # Calculate gap
            if scheduled.time_slot.end_time < time_slot.start_time:
                gap_start = datetime.combine(datetime.today(), scheduled.time_slot.end_time)
                gap_end = datetime.combine(datetime.today(), time_slot.start_time)
                gap_minutes = (gap_end - gap_start).seconds / 60
                
                if gap_minutes < constraints.min_break_minutes:
                    penalty += 10.0  # Too short break
                elif gap_minutes > constraints.preferred_gap_minutes * 2:
                    penalty += 2.0  # Too long gap
            
            elif time_slot.end_time < scheduled.time_slot.start_time:
                gap_start = datetime.combine(datetime.today(), time_slot.end_time)
                gap_end = datetime.combine(datetime.today(), scheduled.time_slot.start_time)
                gap_minutes = (gap_end - gap_start).seconds / 60
                
                if gap_minutes < constraints.min_break_minutes:
                    penalty += 10.0
                elif gap_minutes > constraints.preferred_gap_minutes * 2:
                    penalty += 2.0
        
        return penalty
    
    def _count_room_changes(self, section: str, room: Room, time_slot: TimeSlot,
                          schedule: Schedule) -> int:
        """Count room changes for a section on the same day."""
        section_sessions = [
            s for s in schedule.get_sessions_by_section(section)
            if s.time_slot.day == time_slot.day
        ]
        
        unique_rooms = set(s.room for s in section_sessions)
        if room not in unique_rooms:
            return len(unique_rooms)
        
        return 0


class ConstraintAnalyzer:
    """Analyzes constraint violations in a schedule."""
    
    def __init__(self, validator: Optional[ConstraintValidator] = None):
        """Initialize analyzer."""
        self.validator = validator or ConstraintValidator()
    
    def analyze_schedule(
        self,
        schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> Dict[str, Any]:
        """
        Analyze constraint violations in a complete schedule.
        
        Args:
            schedule: Schedule to analyze
            constraints: Constraints to check against
            
        Returns:
            Analysis results
        """
        hard_violations = []
        soft_violations = []
        
        for scheduled in schedule.sessions:
            # Create temporary schedule without this session
            temp_schedule = Schedule(schedule_id="temp")
            temp_schedule.sessions = [s for s in schedule.sessions if s != scheduled]
            
            # Check hard constraints
            is_valid, violations = self.validator.check_hard_constraints(
                scheduled.session,
                scheduled.time_slot,
                scheduled.room,
                temp_schedule,
                constraints
            )
            
            if not is_valid:
                hard_violations.append({
                    'session': str(scheduled.session),
                    'violations': violations
                })
            
            # Check soft constraints
            penalties = self.validator.check_soft_constraints(
                scheduled.session,
                scheduled.time_slot,
                scheduled.room,
                temp_schedule,
                constraints
            )
            
            if penalties:
                soft_violations.append({
                    'session': str(scheduled.session),
                    'penalties': penalties,
                    'total_penalty': sum(penalties.values())
                })
        
        return {
            'hard_violations': hard_violations,
            'soft_violations': soft_violations,
            'total_hard_violations': len(hard_violations),
            'total_soft_penalty': sum(v['total_penalty'] for v in soft_violations),
            'is_feasible': len(hard_violations) == 0
        }
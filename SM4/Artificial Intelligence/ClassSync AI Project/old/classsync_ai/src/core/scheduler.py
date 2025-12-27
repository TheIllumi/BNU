"""
Core scheduler interface for ClassSync AI.

This module provides the main scheduling interface and orchestrates
the optimization process using various algorithms and constraints.
"""

from abc import ABC, abstractmethod
from typing import List, Dict, Any, Optional, Tuple
import logging
from datetime import datetime

from .models import (
    Schedule, Session, Room, TimeSlot, 
    ScheduledSession, SchedulingConstraints
)
from .constraints import ConstraintValidator


logger = logging.getLogger(__name__)


class SchedulingAlgorithm(ABC):
    """Abstract base class for scheduling algorithms."""
    
    @abstractmethod
    def optimize(
        self,
        sessions: List[Session],
        rooms: List[Room],
        time_slots: List[TimeSlot],
        constraints: SchedulingConstraints,
        **kwargs
    ) -> Schedule:
        """
        Optimize the schedule using the specific algorithm.
        
        Args:
            sessions: List of sessions to schedule
            rooms: Available rooms
            time_slots: Available time slots
            constraints: Scheduling constraints
            **kwargs: Algorithm-specific parameters
            
        Returns:
            Optimized schedule
        """
        pass
    
    @abstractmethod
    def get_name(self) -> str:
        """Get the name of the algorithm."""
        pass


class Scheduler:
    """
    Main scheduler class that orchestrates the scheduling process.
    """
    
    def __init__(
        self,
        algorithm: SchedulingAlgorithm,
        constraint_validator: Optional[ConstraintValidator] = None
    ):
        """
        Initialize the scheduler.
        
        Args:
            algorithm: Scheduling algorithm to use
            constraint_validator: Constraint validator instance
        """
        self.algorithm = algorithm
        self.constraint_validator = constraint_validator or ConstraintValidator()
        self.history: List[Dict[str, Any]] = []
        
    def create_schedule(
        self,
        sessions: List[Session],
        rooms: List[Room],
        time_slots: List[TimeSlot],
        constraints: SchedulingConstraints,
        **algorithm_params
    ) -> Tuple[Schedule, Dict[str, Any]]:
        """
        Create an optimized schedule.
        
        Args:
            sessions: Sessions to schedule
            rooms: Available rooms
            time_slots: Available time slots
            constraints: Scheduling constraints
            **algorithm_params: Additional algorithm parameters
            
        Returns:
            Tuple of (optimized schedule, statistics)
        """
        start_time = datetime.now()
        
        logger.info(f"Starting scheduling with {self.algorithm.get_name()}")
        logger.info(f"Sessions: {len(sessions)}, Rooms: {len(rooms)}, Slots: {len(time_slots)}")
        
        # Validate input data
        validation_result = self._validate_inputs(sessions, rooms, time_slots, constraints)
        if not validation_result['valid']:
            raise ValueError(f"Invalid input data: {validation_result['errors']}")
        
        # Run optimization
        schedule = self.algorithm.optimize(
            sessions=sessions,
            rooms=rooms,
            time_slots=time_slots,
            constraints=constraints,
            **algorithm_params
        )
        
        # Post-process schedule
        schedule = self._post_process_schedule(schedule, constraints)
        
        # Calculate statistics
        end_time = datetime.now()
        statistics = self._calculate_statistics(
            schedule, sessions, start_time, end_time
        )
        
        # Store in history
        self.history.append({
            'timestamp': start_time,
            'algorithm': self.algorithm.get_name(),
            'statistics': statistics,
            'schedule_id': schedule.schedule_id
        })
        
        logger.info(f"Scheduling completed in {statistics['execution_time']:.2f} seconds")
        logger.info(f"Coverage: {statistics['coverage_percentage']:.1f}%")
        
        return schedule, statistics
    
    def _validate_inputs(
        self,
        sessions: List[Session],
        rooms: List[Room],
        time_slots: List[TimeSlot],
        constraints: SchedulingConstraints
    ) -> Dict[str, Any]:
        """Validate input data."""
        errors = []
        warnings = []
        
        # Check if we have data
        if not sessions:
            errors.append("No sessions to schedule")
        if not rooms:
            errors.append("No rooms available")
        if not time_slots:
            errors.append("No time slots available")
        
        # Check for sufficient capacity
        total_session_hours = sum(s.duration_minutes / 60 for s in sessions)
        total_slot_hours = sum(slot.duration_minutes() / 60 for slot in time_slots) * len(rooms)
        
        if total_session_hours > total_slot_hours:
            warnings.append(
                f"Total session hours ({total_session_hours:.1f}) exceeds "
                f"available slot hours ({total_slot_hours:.1f})"
            )
        
        # Validate constraints
        constraint_validation = self.constraint_validator.validate_constraints(constraints)
        if not constraint_validation['valid']:
            errors.extend(constraint_validation['errors'])
        warnings.extend(constraint_validation.get('warnings', []))
        
        return {
            'valid': len(errors) == 0,
            'errors': errors,
            'warnings': warnings
        }
    
    def _post_process_schedule(
        self,
        schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> Schedule:
        """Post-process the schedule to fix any issues."""
        # Check and mark conflicts
        for i, session1 in enumerate(schedule.sessions):
            for session2 in schedule.sessions[i+1:]:
                # Check for time-room conflicts
                if (session1.time_slot.overlaps_with(session2.time_slot) and
                    session1.room == session2.room):
                    session1.conflicts.append(f"Room conflict with {session2.session}")
                    session2.conflicts.append(f"Room conflict with {session1.session}")
                
                # Check for instructor conflicts
                if (session1.time_slot.overlaps_with(session2.time_slot) and
                    session1.session.course.instructor == session2.session.course.instructor):
                    session1.conflicts.append(f"Instructor conflict with {session2.session}")
                    session2.conflicts.append(f"Instructor conflict with {session1.session}")
                
                # Check for section conflicts
                if (session1.time_slot.overlaps_with(session2.time_slot) and
                    session1.session.course.section == session2.session.course.section):
                    session1.conflicts.append(f"Section conflict with {session2.session}")
                    session2.conflicts.append(f"Section conflict with {session1.session}")
        
        return schedule
    
    def _calculate_statistics(
        self,
        schedule: Schedule,
        original_sessions: List[Session],
        start_time: datetime,
        end_time: datetime
    ) -> Dict[str, Any]:
        """Calculate scheduling statistics."""
        scheduled_session_ids = {s.session.session_id for s in schedule.sessions}
        original_session_ids = {s.session_id for s in original_sessions}
        missed_sessions = original_session_ids - scheduled_session_ids
        
        conflict_count = sum(1 for s in schedule.sessions if s.has_conflicts())
        forced_count = sum(1 for s in schedule.sessions if s.is_forced)
        
        # Calculate instructor workload
        instructor_hours = {}
        for scheduled in schedule.sessions:
            instructor = scheduled.session.course.instructor
            day = scheduled.time_slot.day
            key = f"{instructor.name}_{day}"
            hours = scheduled.time_slot.duration_minutes() / 60
            instructor_hours[key] = instructor_hours.get(key, 0) + hours
        
        # Calculate room utilization
        room_usage = {}
        for scheduled in schedule.sessions:
            room_name = scheduled.room.name
            room_usage[room_name] = room_usage.get(room_name, 0) + 1
        
        return {
            'execution_time': (end_time - start_time).total_seconds(),
            'total_sessions': len(original_sessions),
            'scheduled_sessions': len(schedule.sessions),
            'missed_sessions': len(missed_sessions),
            'coverage_percentage': (len(schedule.sessions) / len(original_sessions) * 100) 
                                  if original_sessions else 0,
            'conflicts': conflict_count,
            'forced_placements': forced_count,
            'fitness_score': schedule.fitness_score,
            'instructor_workload': instructor_hours,
            'room_utilization': room_usage,
            'missed_session_ids': list(missed_sessions)
        }
    
    def get_history(self) -> List[Dict[str, Any]]:
        """Get scheduling history."""
        return self.history
    
    def clear_history(self) -> None:
        """Clear scheduling history."""
        self.history.clear()


class SchedulerFactory:
    """Factory class for creating schedulers with different algorithms."""
    
    _algorithms: Dict[str, type] = {}
    
    @classmethod
    def register_algorithm(cls, name: str, algorithm_class: type) -> None:
        """Register a new algorithm."""
        cls._algorithms[name] = algorithm_class
    
    @classmethod
    def create_scheduler(
        cls,
        algorithm_name: str,
        **algorithm_params
    ) -> Scheduler:
        """
        Create a scheduler with the specified algorithm.
        
        Args:
            algorithm_name: Name of the algorithm to use
            **algorithm_params: Parameters for the algorithm
            
        Returns:
            Configured scheduler instance
        """
        if algorithm_name not in cls._algorithms:
            raise ValueError(f"Unknown algorithm: {algorithm_name}")
        
        algorithm_class = cls._algorithms[algorithm_name]
        algorithm = algorithm_class(**algorithm_params)
        
        return Scheduler(algorithm)
    
    @classmethod
    def get_available_algorithms(cls) -> List[str]:
        """Get list of available algorithms."""
        return list(cls._algorithms.keys())
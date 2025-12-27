"""
Fitness calculation for schedule optimization.

This module provides fitness functions to evaluate the quality of
generated schedules based on various criteria and constraints.
"""

from typing import Dict, Any, List, Optional
import logging
from collections import defaultdict

from ..core.models import Schedule, SchedulingConstraints, ScheduledSession
from ..core.constraints import ConstraintValidator


logger = logging.getLogger(__name__)


class FitnessCalculator:
    """Calculates fitness scores for schedules."""
    
    def __init__(self, validator: Optional[ConstraintValidator] = None):
        """
        Initialize fitness calculator.
        
        Args:
            validator: Constraint validator instance
        """
        self.validator = validator or ConstraintValidator()
        self.base_score = 1000.0
        
        # Weight configuration for different penalty types
        self.weights = {
            'hard_constraint': 100.0,
            'room_conflict': 50.0,
            'instructor_conflict': 50.0,
            'section_conflict': 40.0,
            'forced_placement': 10.0,
            'evening_class': 3.0,
            'early_morning': 2.0,
            'room_change': 2.0,
            'gap_penalty': 1.0,
            'coverage_bonus': 5.0,
            'balanced_load_bonus': 2.0,
            'optimal_room_usage': 3.0
        }
    
    def calculate(
        self,
        schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> float:
        """
        Calculate fitness score for a schedule.
        
        Args:
            schedule: Schedule to evaluate
            constraints: Scheduling constraints
            
        Returns:
            Fitness score (higher is better)
        """
        if not schedule.sessions:
            return 1.0
        
        score = self.base_score
        penalties = 0.0
        bonuses = 0.0
        
        # Calculate various penalty and bonus components
        conflict_penalties = self._calculate_conflict_penalties(schedule)
        constraint_penalties = self._calculate_constraint_penalties(schedule, constraints)
        placement_penalties = self._calculate_placement_penalties(schedule)
        coverage_bonus = self._calculate_coverage_bonus(schedule)
        balance_bonus = self._calculate_balance_bonus(schedule)
        room_usage_bonus = self._calculate_room_usage_bonus(schedule)
        
        # Apply penalties
        penalties += conflict_penalties
        penalties += constraint_penalties
        penalties += placement_penalties
        
        # Apply bonuses
        bonuses += coverage_bonus
        bonuses += balance_bonus
        bonuses += room_usage_bonus
        
        # Calculate final score
        final_score = max(1.0, score - penalties + bonuses)
        
        logger.debug(f"Fitness calculation: base={score}, penalties={penalties:.1f}, "
                    f"bonuses={bonuses:.1f}, final={final_score:.1f}")
        
        return final_score
    
    def _calculate_conflict_penalties(self, schedule: Schedule) -> float:
        """Calculate penalties for scheduling conflicts."""
        penalties = 0.0
        
        # Check each pair of sessions for conflicts
        for i, session1 in enumerate(schedule.sessions):
            for session2 in schedule.sessions[i+1:]:
                if not session1.time_slot.overlaps_with(session2.time_slot):
                    continue
                
                # Room conflict
                if session1.room == session2.room:
                    penalties += self.weights['room_conflict']
                    logger.debug(f"Room conflict: {session1.room.name}")
                
                # Instructor conflict
                if (session1.session.course.instructor == 
                    session2.session.course.instructor):
                    penalties += self.weights['instructor_conflict']
                    logger.debug(f"Instructor conflict: "
                               f"{session1.session.course.instructor.name}")
                
                # Section conflict (students can't be in two places)
                if (session1.session.course.section == 
                    session2.session.course.section):
                    penalties += self.weights['section_conflict']
                    logger.debug(f"Section conflict: "
                               f"{session1.session.course.section}")
        
        return penalties
    
    def _calculate_constraint_penalties(
        self,
        schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> float:
        """Calculate penalties for constraint violations."""
        penalties = 0.0
        
        # Check instructor daily hours
        instructor_daily_hours = defaultdict(float)
        
        for scheduled in schedule.sessions:
            instructor = scheduled.session.course.instructor
            day = scheduled.time_slot.day
            hours = scheduled.time_slot.duration_minutes() / 60
            
            key = f"{instructor.instructor_id}_{day}"
            instructor_daily_hours[key] += hours
        
        # Penalize excessive daily hours
        for key, hours in instructor_daily_hours.items():
            if hours > constraints.max_daily_hours_per_instructor:
                excess = hours - constraints.max_daily_hours_per_instructor
                penalties += excess * 20.0
                logger.debug(f"Excessive hours for {key}: {hours:.1f}")
        
        # Check evening classes
        if not constraints.allow_evening_classes:
            for scheduled in schedule.sessions:
                if scheduled.time_slot.start_time >= constraints.evening_threshold:
                    penalties += self.weights['evening_class'] * 3
        
        # Check for sessions in blocked slots
        for scheduled in schedule.sessions:
            for blocked_slot in constraints.blocked_slots:
                if scheduled.time_slot.overlaps_with(blocked_slot):
                    penalties += self.weights['hard_constraint']
                    logger.debug(f"Session in blocked slot: {scheduled.session}")
        
        return penalties
    
    def _calculate_placement_penalties(self, schedule: Schedule) -> float:
        """Calculate penalties for forced placements and suboptimal positions."""
        penalties = 0.0
        
        for scheduled in schedule.sessions:
            # Forced placement penalty
            if scheduled.is_forced:
                penalties += self.weights['forced_placement']
                
                # Additional penalty based on force strategy
                if scheduled.force_strategy == "relaxed_constraints":
                    penalties += 5.0
                elif scheduled.force_strategy == "any_room":
                    penalties += 3.0
            
            # Early morning penalty (before 9 AM)
            if scheduled.time_slot.start_time.hour < 9:
                penalties += self.weights['early_morning']
            
            # Late evening penalty (after 6 PM)
            if scheduled.time_slot.end_time.hour >= 18:
                penalties += self.weights['evening_class']
        
        # Room changes for same section on same day
        section_day_rooms = defaultdict(set)
        
        for scheduled in schedule.sessions:
            key = f"{scheduled.session.course.section}_{scheduled.time_slot.day}"
            section_day_rooms[key].add(scheduled.room.room_id)
        
        for key, rooms in section_day_rooms.items():
            if len(rooms) > 1:
                # Penalty for each additional room
                penalties += (len(rooms) - 1) * self.weights['room_change']
        
        return penalties
    
    def _calculate_coverage_bonus(self, schedule: Schedule) -> float:
        """Calculate bonus for session coverage."""
        # Simple bonus based on number of scheduled sessions
        # This encourages scheduling more sessions
        return len(schedule.sessions) * self.weights['coverage_bonus']
    
    def _calculate_balance_bonus(self, schedule: Schedule) -> float:
        """Calculate bonus for balanced instructor workload."""
        bonus = 0.0
        
        # Calculate daily loads for each instructor
        instructor_daily_loads = defaultdict(list)
        
        for scheduled in schedule.sessions:
            instructor = scheduled.session.course.instructor
            day = scheduled.time_slot.day
            hours = scheduled.time_slot.duration_minutes() / 60
            
            instructor_daily_loads[instructor.instructor_id].append(hours)
        
        # Reward balanced distribution
        for instructor_id, daily_hours in instructor_daily_loads.items():
            if not daily_hours:
                continue
            
            avg_hours = sum(daily_hours) / len(daily_hours)
            
            # Good range is 3-6 hours per day
            if 3 <= avg_hours <= 6:
                bonus += self.weights['balanced_load_bonus'] * len(daily_hours)
            
            # Check variance (lower variance = more balanced)
            if len(daily_hours) > 1:
                variance = sum((h - avg_hours) ** 2 for h in daily_hours) / len(daily_hours)
                if variance < 2.0:  # Low variance is good
                    bonus += self.weights['balanced_load_bonus']
        
        return bonus
    
    def _calculate_room_usage_bonus(self, schedule: Schedule) -> float:
        """Calculate bonus for optimal room usage."""
        bonus = 0.0
        
        # Count room usage
        room_usage = defaultdict(int)
        room_types_used = defaultdict(set)
        
        for scheduled in schedule.sessions:
            room_usage[scheduled.room.room_id] += 1
            
            # Track if room is used for appropriate session type
            if scheduled.room.is_suitable_for(scheduled.session.session_type):
                room_types_used[scheduled.room.room_id].add(scheduled.session.session_type)
                bonus += self.weights['optimal_room_usage']
        
        # Bonus for efficient room utilization (not too sparse, not too crowded)
        for room_id, count in room_usage.items():
            if 5 <= count <= 15:  # Optimal usage range
                bonus += 1.0
        
        return bonus
    
    def get_detailed_breakdown(
        self,
        schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> Dict[str, Any]:
        """
        Get detailed fitness breakdown for analysis.
        
        Args:
            schedule: Schedule to analyze
            constraints: Scheduling constraints
            
        Returns:
            Detailed breakdown of fitness components
        """
        breakdown = {
            'base_score': self.base_score,
            'conflicts': {},
            'constraints': {},
            'placements': {},
            'bonuses': {},
            'penalties_total': 0.0,
            'bonuses_total': 0.0,
            'final_score': 0.0
        }
        
        # Conflict analysis
        room_conflicts = 0
        instructor_conflicts = 0
        section_conflicts = 0
        
        for i, session1 in enumerate(schedule.sessions):
            for session2 in schedule.sessions[i+1:]:
                if not session1.time_slot.overlaps_with(session2.time_slot):
                    continue
                
                if session1.room == session2.room:
                    room_conflicts += 1
                
                if (session1.session.course.instructor == 
                    session2.session.course.instructor):
                    instructor_conflicts += 1
                
                if (session1.session.course.section == 
                    session2.session.course.section):
                    section_conflicts += 1
        
        breakdown['conflicts'] = {
            'room_conflicts': room_conflicts,
            'instructor_conflicts': instructor_conflicts,
            'section_conflicts': section_conflicts,
            'total_penalty': (room_conflicts * self.weights['room_conflict'] +
                            instructor_conflicts * self.weights['instructor_conflict'] +
                            section_conflicts * self.weights['section_conflict'])
        }
        
        # Constraint violations
        excessive_hours = 0
        evening_classes = 0
        blocked_slots = 0
        
        instructor_daily_hours = defaultdict(float)
        
        for scheduled in schedule.sessions:
            instructor = scheduled.session.course.instructor
            day = scheduled.time_slot.day
            hours = scheduled.time_slot.duration_minutes() / 60
            
            key = f"{instructor.instructor_id}_{day}"
            instructor_daily_hours[key] += hours
            
            if scheduled.time_slot.start_time >= constraints.evening_threshold:
                evening_classes += 1
            
            for blocked in constraints.blocked_slots:
                if scheduled.time_slot.overlaps_with(blocked):
                    blocked_slots += 1
        
        for hours in instructor_daily_hours.values():
            if hours > constraints.max_daily_hours_per_instructor:
                excessive_hours += 1
        
        breakdown['constraints'] = {
            'excessive_hours_count': excessive_hours,
            'evening_classes_count': evening_classes,
            'blocked_slots_count': blocked_slots,
            'total_penalty': (excessive_hours * 20.0 +
                            evening_classes * self.weights['evening_class'] +
                            blocked_slots * self.weights['hard_constraint'])
        }
        
        # Placement quality
        forced_count = sum(1 for s in schedule.sessions if s.is_forced)
        early_morning = sum(1 for s in schedule.sessions 
                          if s.time_slot.start_time.hour < 9)
        
        breakdown['placements'] = {
            'forced_placements': forced_count,
            'early_morning_sessions': early_morning,
            'total_penalty': (forced_count * self.weights['forced_placement'] +
                            early_morning * self.weights['early_morning'])
        }
        
        # Bonuses
        coverage_bonus = len(schedule.sessions) * self.weights['coverage_bonus']
        balance_bonus = self._calculate_balance_bonus(schedule)
        room_bonus = self._calculate_room_usage_bonus(schedule)
        
        breakdown['bonuses'] = {
            'coverage': coverage_bonus,
            'balance': balance_bonus,
            'room_usage': room_bonus,
            'total': coverage_bonus + balance_bonus + room_bonus
        }
        
        # Totals
        breakdown['penalties_total'] = (
            breakdown['conflicts']['total_penalty'] +
            breakdown['constraints']['total_penalty'] +
            breakdown['placements']['total_penalty']
        )
        breakdown['bonuses_total'] = breakdown['bonuses']['total']
        breakdown['final_score'] = max(
            1.0,
            self.base_score - breakdown['penalties_total'] + breakdown['bonuses_total']
        )
        
        return breakdown


class MultiObjectiveFitness:
    """
    Multi-objective fitness calculation for Pareto optimization.
    
    This class can be used for more advanced optimization techniques
    that consider multiple objectives simultaneously.
    """
    
    def __init__(self):
        """Initialize multi-objective fitness calculator."""
        self.validator = ConstraintValidator()
        self.objectives = {
            'minimize_conflicts': self._calculate_conflicts,
            'maximize_coverage': self._calculate_coverage,
            'minimize_gaps': self._calculate_gaps,
            'balance_workload': self._calculate_workload_balance,
            'optimize_room_usage': self._calculate_room_optimization
        }
    
    def calculate_objectives(
        self,
        schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> Dict[str, float]:
        """
        Calculate all objective values.
        
        Args:
            schedule: Schedule to evaluate
            constraints: Scheduling constraints
            
        Returns:
            Dictionary of objective values
        """
        results = {}
        
        for name, func in self.objectives.items():
            results[name] = func(schedule, constraints)
        
        return results
    
    def _calculate_conflicts(
        self,
        schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> float:
        """Calculate conflict score (lower is better)."""
        conflicts = 0
        
        for i, session1 in enumerate(schedule.sessions):
            for session2 in schedule.sessions[i+1:]:
                if not session1.time_slot.overlaps_with(session2.time_slot):
                    continue
                
                if session1.room == session2.room:
                    conflicts += 1
                
                if (session1.session.course.instructor == 
                    session2.session.course.instructor):
                    conflicts += 1
                
                if (session1.session.course.section == 
                    session2.session.course.section):
                    conflicts += 1
        
        return float(conflicts)
    
    def _calculate_coverage(
        self,
        schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> float:
        """Calculate coverage score (higher is better)."""
        return float(len(schedule.sessions))
    
    def _calculate_gaps(
        self,
        schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> float:
        """Calculate gap penalty (lower is better)."""
        gap_penalty = 0.0
        
        # Group sessions by instructor and day
        instructor_day_sessions = defaultdict(list)
        
        for scheduled in schedule.sessions:
            key = (scheduled.session.course.instructor.instructor_id,
                  scheduled.time_slot.day)
            instructor_day_sessions[key].append(scheduled)
        
        for sessions in instructor_day_sessions.values():
            if len(sessions) < 2:
                continue
            
            # Sort by start time
            sessions.sort(key=lambda x: x.time_slot.start_time)
            
            # Calculate gaps
            for i in range(len(sessions) - 1):
                end_time = sessions[i].time_slot.end_time
                start_time = sessions[i + 1].time_slot.start_time
                
                # Convert to minutes
                gap_minutes = (
                    (start_time.hour * 60 + start_time.minute) -
                    (end_time.hour * 60 + end_time.minute)
                )
                
                if gap_minutes > constraints.preferred_gap_minutes:
                    gap_penalty += (gap_minutes - constraints.preferred_gap_minutes) / 30
        
        return gap_penalty
    
    def _calculate_workload_balance(
        self,
        schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> float:
        """Calculate workload balance score (lower variance is better)."""
        instructor_loads = defaultdict(float)
        
        for scheduled in schedule.sessions:
            instructor = scheduled.session.course.instructor.instructor_id
            hours = scheduled.time_slot.duration_minutes() / 60
            instructor_loads[instructor] += hours
        
        if not instructor_loads:
            return 0.0
        
        loads = list(instructor_loads.values())
        avg_load = sum(loads) / len(loads)
        
        # Calculate variance
        variance = sum((load - avg_load) ** 2 for load in loads) / len(loads)
        
        return variance
    
    def _calculate_room_optimization(
        self,
        schedule: Schedule,
        constraints: SchedulingConstraints
    ) -> float:
        """Calculate room optimization score (higher is better)."""
        score = 0.0
        
        for scheduled in schedule.sessions:
            # Bonus for using appropriate room type
            if scheduled.room.is_suitable_for(scheduled.session.session_type):
                score += 1.0
            
            # Penalty for using oversized rooms for small classes
            if (scheduled.session.course.enrolled_students > 0 and
                scheduled.room.capacity > 0):
                utilization = (scheduled.session.course.enrolled_students / 
                             scheduled.room.capacity)
                
                if 0.5 <= utilization <= 0.9:  # Good utilization
                    score += 0.5
                elif utilization < 0.3:  # Poor utilization
                    score -= 0.5
        
        return score
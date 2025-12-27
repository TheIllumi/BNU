"""
Genetic Algorithm implementation for schedule optimization.

This module implements a genetic algorithm for solving the timetabling
problem with support for adaptive parameters and multiple strategies.
"""

import random
import logging
from typing import List, Dict, Any, Optional, Tuple
from dataclasses import dataclass
import numpy as np
from tqdm import tqdm

from ..core.scheduler import SchedulingAlgorithm
from ..core.models import (
    Schedule, Session, Room, TimeSlot, ScheduledSession,
    SchedulingConstraints
)
from .fitness import FitnessCalculator
from .operators import GeneticOperators


logger = logging.getLogger(__name__)


@dataclass
class GeneticAlgorithmConfig:
    """Configuration for genetic algorithm."""
    population_size: int = 50
    generations: int = 100
    elite_size: int = 5
    mutation_rate: float = 0.15
    crossover_rate: float = 0.8
    tournament_size: int = 3
    adaptive: bool = True
    adaptive_threshold: int = 10
    mutation_rate_min: float = 0.05
    mutation_rate_max: float = 0.3
    early_stopping: bool = True
    early_stopping_generations: int = 20
    verbose: bool = True


class Individual:
    """Represents an individual in the genetic algorithm population."""
    
    def __init__(self, schedule: Schedule, fitness: Optional[float] = None):
        """Initialize an individual."""
        self.schedule = schedule
        self.fitness = fitness
        self.age = 0
    
    def __lt__(self, other):
        """Compare individuals by fitness."""
        if self.fitness is None or other.fitness is None:
            return False
        return self.fitness < other.fitness
    
    def copy(self) -> 'Individual':
        """Create a deep copy of the individual."""
        new_schedule = Schedule(
            schedule_id=f"{self.schedule.schedule_id}_copy",
            sessions=self.schedule.sessions.copy(),
            fitness_score=self.schedule.fitness_score,
            metadata=self.schedule.metadata.copy()
        )
        return Individual(new_schedule, self.fitness)


class GeneticAlgorithm(SchedulingAlgorithm):
    """Genetic algorithm for schedule optimization."""
    
    def __init__(self, config: Optional[GeneticAlgorithmConfig] = None):
        """
        Initialize the genetic algorithm.
        
        Args:
            config: Algorithm configuration
        """
        self.config = config or GeneticAlgorithmConfig()
        self.fitness_calculator = FitnessCalculator()
        self.operators = GeneticOperators()
        self.generation_history: List[float] = []
        
    def get_name(self) -> str:
        """Get algorithm name."""
        return "Genetic Algorithm"
    
    def optimize(
        self,
        sessions: List[Session],
        rooms: List[Room],
        time_slots: List[TimeSlot],
        constraints: SchedulingConstraints,
        **kwargs
    ) -> Schedule:
        """
        Optimize schedule using genetic algorithm.
        
        Args:
            sessions: Sessions to schedule
            rooms: Available rooms
            time_slots: Available time slots
            constraints: Scheduling constraints
            **kwargs: Additional parameters
            
        Returns:
            Optimized schedule
        """
        # Override config with kwargs if provided
        for key, value in kwargs.items():
            if hasattr(self.config, key):
                setattr(self.config, key, value)
        
        logger.info(f"Starting GA with population size {self.config.population_size}")
        
        # Initialize population
        population = self._initialize_population(
            sessions, rooms, time_slots, constraints
        )
        
        # Evolution loop
        best_individual = None
        stagnation_counter = 0
        current_mutation_rate = self.config.mutation_rate
        
        progress_bar = None
        if self.config.verbose:
            progress_bar = tqdm(
                range(self.config.generations),
                desc="Evolving",
                unit="gen"
            )
        
        for generation in range(self.config.generations):
            # Evaluate fitness
            for individual in population:
                if individual.fitness is None:
                    individual.fitness = self.fitness_calculator.calculate(
                        individual.schedule, constraints
                    )
                    individual.schedule.fitness_score = individual.fitness
            
            # Sort by fitness (descending)
            population.sort(key=lambda x: x.fitness, reverse=True)
            
            # Track best
            if best_individual is None or population[0].fitness > best_individual.fitness:
                best_individual = population[0].copy()
                stagnation_counter = 0
            else:
                stagnation_counter += 1
            
            # Store history
            self.generation_history.append(population[0].fitness)
            
            # Update progress bar
            if progress_bar:
                avg_fitness = np.mean([ind.fitness for ind in population])
                progress_bar.set_postfix({
                    'Best': f'{population[0].fitness:.0f}',
                    'Avg': f'{avg_fitness:.0f}',
                    'MutRate': f'{current_mutation_rate:.3f}'
                })
                progress_bar.update(1)
            
            # Check early stopping
            if (self.config.early_stopping and 
                stagnation_counter >= self.config.early_stopping_generations):
                logger.info(f"Early stopping at generation {generation}")
                break
            
            # Adaptive mutation rate
            if self.config.adaptive:
                current_mutation_rate = self._adapt_mutation_rate(
                    current_mutation_rate, stagnation_counter
                )
            
            # Create next generation
            population = self._create_next_generation(
                population, sessions, rooms, time_slots, 
                constraints, current_mutation_rate
            )
        
        if progress_bar:
            progress_bar.close()
        
        logger.info(f"GA completed with best fitness: {best_individual.fitness:.0f}")
        
        return best_individual.schedule
    
    def _initialize_population(
        self,
        sessions: List[Session],
        rooms: List[Room],
        time_slots: List[TimeSlot],
        constraints: SchedulingConstraints
    ) -> List[Individual]:
        """Initialize the population with random schedules."""
        population = []
        
        for i in range(self.config.population_size):
            schedule = self._create_random_schedule(
                f"initial_{i}",
                sessions, rooms, time_slots, constraints
            )
            population.append(Individual(schedule))
        
        return population
    
    def _create_random_schedule(
        self,
        schedule_id: str,
        sessions: List[Session],
        rooms: List[Room],
        time_slots: List[TimeSlot],
        constraints: SchedulingConstraints
    ) -> Schedule:
        """Create a random schedule."""
        schedule = Schedule(schedule_id=schedule_id)
        
        # Sort sessions by priority
        sorted_sessions = self._sort_sessions_by_priority(sessions, constraints)
        
        for session in sorted_sessions:
            scheduled = self._try_schedule_session(
                session, schedule, rooms, time_slots, constraints
            )
            if scheduled:
                schedule.add_session(scheduled)
        
        return schedule
    
    def _try_schedule_session(
        self,
        session: Session,
        current_schedule: Schedule,
        rooms: List[Room],
        time_slots: List[TimeSlot],
        constraints: SchedulingConstraints,
        max_attempts: int = 100
    ) -> Optional[ScheduledSession]:
        """Try to schedule a session."""
        suitable_rooms = [r for r in rooms if r.is_suitable_for(session.session_type)]
        if not suitable_rooms:
            suitable_rooms = rooms  # Fallback to any room
        
        for attempt in range(max_attempts):
            room = random.choice(suitable_rooms)
            slot = random.choice(time_slots)
            
            # Check basic constraints
            if self._is_valid_placement(session, slot, room, current_schedule, constraints):
                return ScheduledSession(
                    session=session,
                    time_slot=slot,
                    room=room,
                    is_forced=False
                )
        
        # Try forced placement with relaxed constraints
        for attempt in range(max_attempts // 2):
            room = random.choice(rooms)
            slot = random.choice(time_slots)
            
            if self._is_valid_placement(session, slot, room, current_schedule, 
                                       constraints, relaxed=True):
                return ScheduledSession(
                    session=session,
                    time_slot=slot,
                    room=room,
                    is_forced=True,
                    force_strategy="relaxed_constraints"
                )
        
        return None
    
    def _is_valid_placement(
        self,
        session: Session,
        slot: TimeSlot,
        room: Room,
        schedule: Schedule,
        constraints: SchedulingConstraints,
        relaxed: bool = False
    ) -> bool:
        """Check if a placement is valid."""
        # Check room conflicts
        for scheduled in schedule.sessions:
            if scheduled.room == room and scheduled.time_slot.overlaps_with(slot):
                return False
        
        # Check instructor conflicts
        instructor = session.course.instructor
        for scheduled in schedule.sessions:
            if (scheduled.session.course.instructor == instructor and 
                scheduled.time_slot.overlaps_with(slot)):
                return False
        
        if not relaxed:
            # Check section conflicts
            section = session.course.section
            for scheduled in schedule.sessions:
                if (scheduled.session.course.section == section and 
                    scheduled.time_slot.overlaps_with(slot)):
                    return False
            
            # Check instructor daily hours
            day_sessions = [s for s in schedule.get_sessions_by_instructor(instructor)
                          if s.time_slot.day == slot.day]
            total_hours = sum(s.time_slot.duration_minutes() / 60 for s in day_sessions)
            if total_hours + (slot.duration_minutes() / 60) > constraints.max_daily_hours_per_instructor:
                return False
        
        return True
    
    def _sort_sessions_by_priority(
        self,
        sessions: List[Session],
        constraints: SchedulingConstraints
    ) -> List[Session]:
        """Sort sessions by scheduling priority."""
        def priority_score(session: Session) -> int:
            score = 0
            
            # Priority sections get higher score
            if session.course.section in constraints.priority_sections:
                score += 100
            
            # Labs are harder to schedule
            if session.requires_lab:
                score += 50
            
            # Longer sessions are harder to place
            score += session.duration_minutes // 30
            
            return score
        
        return sorted(sessions, key=priority_score, reverse=True)
    
    def _create_next_generation(
        self,
        population: List[Individual],
        sessions: List[Session],
        rooms: List[Room],
        time_slots: List[TimeSlot],
        constraints: SchedulingConstraints,
        mutation_rate: float
    ) -> List[Individual]:
        """Create the next generation."""
        new_population = []
        
        # Elitism - keep best individuals
        for i in range(self.config.elite_size):
            new_population.append(population[i].copy())
        
        # Create rest through crossover and mutation
        while len(new_population) < self.config.population_size:
            # Tournament selection
            parent1 = self._tournament_selection(population)
            parent2 = self._tournament_selection(population)
            
            # Crossover
            if random.random() < self.config.crossover_rate:
                offspring1, offspring2 = self.operators.crossover(
                    parent1.schedule, parent2.schedule
                )
            else:
                offspring1 = parent1.schedule
                offspring2 = parent2.schedule
            
            # Mutation
            if random.random() < mutation_rate:
                offspring1 = self.operators.mutate(
                    offspring1, rooms, time_slots, constraints
                )
            if random.random() < mutation_rate:
                offspring2 = self.operators.mutate(
                    offspring2, rooms, time_slots, constraints
                )
            
            # Add to population
            new_population.append(Individual(offspring1))
            if len(new_population) < self.config.population_size:
                new_population.append(Individual(offspring2))
        
        # Age individuals
        for ind in new_population:
            ind.age += 1
        
        return new_population[:self.config.population_size]
    
    def _tournament_selection(self, population: List[Individual]) -> Individual:
        """Select an individual using tournament selection."""
        tournament = random.sample(population, min(self.config.tournament_size, len(population)))
        return max(tournament, key=lambda x: x.fitness)
    
    def _adapt_mutation_rate(self, current_rate: float, stagnation_counter: int) -> float:
        """Adapt mutation rate based on stagnation."""
        if stagnation_counter > self.config.adaptive_threshold:
            # Increase mutation when stagnating
            new_rate = min(
                self.config.mutation_rate_max,
                current_rate * 1.1
            )
        else:
            # Decrease mutation when improving
            new_rate = max(
                self.config.mutation_rate_min,
                current_rate * 0.95
            )
        
        return new_rate
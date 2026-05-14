"""
Genetic Algorithm Optimizer
Enhanced timetable optimization with improved genetic algorithm
"""

import random
import numpy as np
import pandas as pd
from datetime import time, datetime, timedelta
from typing import List, Tuple, Dict, Any

class TimetableOptimizer:
    def __init__(self, config: Dict[str, Any]):
        self.config = config
        self.time_slots = self._generate_time_slots()
        
    def _generate_time_slots(self) -> List[Tuple[str, time, time]]:
        """Generate available time slots based on configuration"""
        slots = []
        
        time_settings = self.config["time_settings"]
        scheduling_rules = self.config["scheduling_rules"]
        
        start_time = self._parse_time(time_settings["daily_start_time"])
        end_time = self._parse_time(time_settings["daily_end_time"])
        slot_duration = time_settings["class_duration_minutes"]
        working_days = scheduling_rules["working_days"]
        
        for day in working_days:
            current = datetime.combine(datetime.today(), start_time)
            day_end = datetime.combine(datetime.today(), end_time)
            
            while current + timedelta(minutes=slot_duration) <= day_end:
                slot_start = current.time()
                slot_end = (current + timedelta(minutes=slot_duration)).time()
                slots.append((day, slot_start, slot_end))
                current += timedelta(minutes=slot_duration)
        
        return slots
    
    def _parse_time(self, time_str: str) -> time:
        """Parse time string to time object"""
        hours, minutes = time_str.split(":")
        return time(int(hours), int(minutes))
    
    def optimize(self, sessions_df: pd.DataFrame, rooms_df: pd.DataFrame, 
                progress_callback=None) -> Tuple[pd.DataFrame, float]:
        """Run genetic algorithm optimization"""
        
        ga_config = self.config["genetic_algorithm"]
        population_size = ga_config["population_size"]
        generations = ga_config["generations"]
        elite_size = ga_config["elite_size"]
        mutation_rate = ga_config["mutation_rate"]
        
        # Generate initial population
        population = [self._create_individual(sessions_df, rooms_df) 
                     for _ in range(population_size)]
        
        best_fitness = 0
        best_individual = None
        fitness_history = []
        
        for generation in range(generations):
            # Calculate fitness for all individuals
            fitness_scores = [self._calculate_fitness(ind) for ind in population]
            
            # Track best individual
            current_best_idx = np.argmax(fitness_scores)
            current_best_fitness = fitness_scores[current_best_idx]
            
            if current_best_fitness > best_fitness:
                best_fitness = current_best_fitness
                best_individual = population[current_best_idx].copy()
            
            fitness_history.append(best_fitness)
            
            # Progress callback
            if progress_callback:
                progress = int((generation + 1) / generations * 100)
                progress_callback(progress, f"Generation {generation + 1}/{generations}, Best Fitness: {best_fitness:.0f}")
            
            # Create new population
            new_population = []
            
            # Elitism - keep best individuals
            elite_indices = np.argsort(fitness_scores)[-elite_size:]
            for idx in elite_indices:
                new_population.append(population[idx].copy())
            
            # Generate offspring through crossover and mutation
            while len(new_population) < population_size:
                parent1 = self._tournament_selection(population, fitness_scores)
                parent2 = self._tournament_selection(population, fitness_scores)
                
                child1, child2 = self._crossover(parent1, parent2)
                
                child1 = self._mutate(child1, sessions_df, rooms_df, mutation_rate)
                child2 = self._mutate(child2, sessions_df, rooms_df, mutation_rate)
                
                new_population.extend([child1, child2])
            
            population = new_population[:population_size]
        
        return best_individual if best_individual is not None else population[0], best_fitness
    
    def _create_individual(self, sessions_df: pd.DataFrame, rooms_df: pd.DataFrame) -> pd.DataFrame:
        """Create a random schedule individual"""
        schedule = []
        rooms = rooms_df["Rooms"].tolist()
        
        for _, session in sessions_df.iterrows():
            # Randomly assign time slot and room
            day, start_time, end_time = random.choice(self.time_slots)
            room = random.choice(rooms)
            
            # Adjust end time for labs (make them longer)
            if session["Is_Lab"]:
                duration_minutes = self.config["time_settings"]["class_duration_minutes"] * 2
                end_time = (datetime.combine(datetime.today(), start_time) + 
                           timedelta(minutes=duration_minutes)).time()
            
            schedule.append({
                "Session_ID": session["Session_ID"],
                "Course_Key": session["Course_Key"],
                "Course_Name": session["Course_Name"],
                "Program": session["Program"],
                "Section": session["Section"],
                "Instructor": session["Instructor"],
                "Is_Lab": session["Is_Lab"],
                "Weekday": day,
                "Start_Time": start_time.strftime("%H:%M"),
                "End_Time": end_time.strftime("%H:%M"),
                "Room": room
            })
        
        return pd.DataFrame(schedule)
    
    def _calculate_fitness(self, schedule: pd.DataFrame) -> float:
        """Calculate fitness score for a schedule"""
        if schedule.empty:
            return 0
        
        score = 10000  # Base score
        penalty = 0
        
        # Convert time strings to time objects for comparison
        schedule = schedule.copy()
        schedule["Start_Time_obj"] = pd.to_datetime(schedule["Start_Time"], format="%H:%M").dt.time
        schedule["End_Time_obj"] = pd.to_datetime(schedule["End_Time"], format="%H:%M").dt.time
        
        # Check for conflicts
        for i, session in schedule.iterrows():
            overlapping = schedule[
                (schedule["Weekday"] == session["Weekday"]) &
                (schedule.index != i) &
                (schedule["Start_Time_obj"] < session["End_Time_obj"]) &
                (schedule["End_Time_obj"] > session["Start_Time_obj"])
            ]
            
            # Heavy penalties for conflicts
            instructor_conflicts = overlapping[overlapping["Instructor"] == session["Instructor"]]
            room_conflicts = overlapping[overlapping["Room"] == session["Room"]]
            section_conflicts = overlapping[overlapping["Section"] == session["Section"]]
            
            penalty += len(instructor_conflicts) * 1000  # Instructor double-booking
            penalty += len(room_conflicts) * 800        # Room double-booking
            penalty += len(section_conflicts) * 600     # Section conflicts
        
        # Penalty for evening classes if not allowed
        if not self.config["scheduling_rules"]["allow_evening_classes"]:
            evening_threshold = self._parse_time(self.config["scheduling_rules"]["evening_threshold"])
            evening_sessions = schedule[schedule["Start_Time_obj"] >= evening_threshold]
            penalty += len(evening_sessions) * 100
        
        # Instructor workload distribution
        instructor_daily_hours = {}
        max_hours = self.config["scheduling_rules"]["max_instructor_hours_per_day"]
        
        for _, session in schedule.iterrows():
            key = f"{session['Instructor']}_{session['Weekday']}"
            duration = 3 if session["Is_Lab"] else 1.5  # Hours
            instructor_daily_hours[key] = instructor_daily_hours.get(key, 0) + duration
        
        # Penalty for exceeding daily hour limits
        for hours in instructor_daily_hours.values():
            if hours > max_hours:
                penalty += (hours - max_hours) * 200
        
        # Bonus for balanced distribution
        if instructor_daily_hours:
            avg_hours = np.mean(list(instructor_daily_hours.values()))
            std_hours = np.std(list(instructor_daily_hours.values()))
            if std_hours < 2.0:  # Well-distributed workload
                score += 500
        
        # Penalty for back-to-back classes if not allowed
        if not self.config["scheduling_rules"]["allow_back_to_back"]:
            for instructor in schedule["Instructor"].unique():
                inst_schedule = schedule[schedule["Instructor"] == instructor].sort_values(["Weekday", "Start_Time"])
                for i in range(len(inst_schedule) - 1):
                    current = inst_schedule.iloc[i]
                    next_session = inst_schedule.iloc[i + 1]
                    
                    if (current["Weekday"] == next_session["Weekday"] and
                        current["End_Time_obj"] == next_session["Start_Time_obj"]):
                        penalty += 50
        
        return max(1, score - penalty)
    
    def _tournament_selection(self, population: List[pd.DataFrame], 
                            fitness_scores: List[float]) -> pd.DataFrame:
        """Tournament selection for parent selection"""
        tournament_size = self.config["genetic_algorithm"]["tournament_size"]
        tournament_indices = random.sample(range(len(population)), 
                                          min(tournament_size, len(population)))
        winner_idx = max(tournament_indices, key=lambda i: fitness_scores[i])
        return population[winner_idx]
    
    def _crossover(self, parent1: pd.DataFrame, parent2: pd.DataFrame) -> Tuple[pd.DataFrame, pd.DataFrame]:
        """Crossover operation to create offspring"""
        if parent1.empty or parent2.empty:
            return parent1.copy(), parent2.copy()
        
        # Instructor-based crossover
        all_instructors = list(set(parent1["Instructor"].unique()) | 
                              set(parent2["Instructor"].unique()))
        
        if len(all_instructors) > 1:
            # Split instructors randomly
            split_point = len(all_instructors) // 2
            group1 = all_instructors[:split_point]
            group2 = all_instructors[split_point:]
            
            child1 = pd.concat([
                parent1[parent1["Instructor"].isin(group1)],
                parent2[parent2["Instructor"].isin(group2)]
            ], ignore_index=True)
            
            child2 = pd.concat([
                parent2[parent2["Instructor"].isin(group1)],
                parent1[parent1["Instructor"].isin(group2)]
            ], ignore_index=True)
        else:
            # Fallback to simple split
            split_point = len(parent1) // 2
            child1 = pd.concat([parent1.iloc[:split_point], parent2.iloc[split_point:]], ignore_index=True)
            child2 = pd.concat([parent2.iloc[:split_point], parent1.iloc[split_point:]], ignore_index=True)
        
        # Remove duplicates while preserving session integrity
        child1 = child1.drop_duplicates(subset=["Session_ID"], keep="first").reset_index(drop=True)
        child2 = child2.drop_duplicates(subset=["Session_ID"], keep="first").reset_index(drop=True)
        
        return child1, child2
    
    def _mutate(self, individual: pd.DataFrame, sessions_df: pd.DataFrame, 
               rooms_df: pd.DataFrame, mutation_rate: float) -> pd.DataFrame:
        """Mutation operation"""
        if individual.empty or random.random() > mutation_rate:
            return individual
        
        individual = individual.copy()
        rooms = rooms_df["Rooms"].tolist()
        
        # Mutate random sessions
        num_mutations = max(1, int(len(individual) * mutation_rate))
        mutation_indices = random.sample(range(len(individual)), 
                                       min(num_mutations, len(individual)))
        
        for idx in mutation_indices:
            # Randomly choose what to mutate: time slot or room
            if random.random() < 0.7:  # 70% chance to mutate time slot
                day, start_time, end_time = random.choice(self.time_slots)
                
                # Adjust for labs
                if individual.iloc[idx]["Is_Lab"]:
                    duration_minutes = self.config["time_settings"]["class_duration_minutes"] * 2
                    end_time = (datetime.combine(datetime.today(), start_time) + 
                               timedelta(minutes=duration_minutes)).time()
                
                individual.at[idx, "Weekday"] = day
                individual.at[idx, "Start_Time"] = start_time.strftime("%H:%M")
                individual.at[idx, "End_Time"] = end_time.strftime("%H:%M")
            else:  # 30% chance to mutate room
                individual.at[idx, "Room"] = random.choice(rooms)
        
        return individual
    
    def get_schedule_statistics(self, schedule: pd.DataFrame) -> Dict[str, Any]:
        """Get statistics about the generated schedule"""
        if schedule.empty:
            return {}
        
        stats = {
            "total_sessions": len(schedule),
            "lab_sessions": len(schedule[schedule["Is_Lab"]]),
            "theory_sessions": len(schedule[~schedule["Is_Lab"]]),
            "instructors": schedule["Instructor"].nunique(),
            "rooms_used": schedule["Room"].nunique(),
            "programs": schedule["Program"].nunique(),
            "sections": schedule["Section"].nunique(),
            "fitness_score": self._calculate_fitness(schedule)
        }
        
        # Daily distribution
        daily_sessions = schedule.groupby("Weekday").size().to_dict()
        stats["daily_distribution"] = daily_sessions
        
        # Instructor workload
        instructor_sessions = schedule.groupby("Instructor").size().to_dict()
        stats["instructor_workload"] = instructor_sessions
        
        # Room utilization
        room_utilization = schedule.groupby("Room").size().to_dict()
        stats["room_utilization"] = room_utilization
        
        return stats
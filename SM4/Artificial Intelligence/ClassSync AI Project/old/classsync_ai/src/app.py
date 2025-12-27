"""
Main application entry point for ClassSync AI.

This module orchestrates the entire scheduling process, from loading
data to generating optimized timetables and exporting results.
"""

import logging
import sys
from pathlib import Path
from typing import Dict, Any, Optional
import click
from datetime import datetime

from core.scheduler import SchedulerFactory
from core.models import SchedulingConstraints
from algorithms.genetic import GeneticAlgorithm, GeneticAlgorithmConfig
from data.loader import DataLoader, ConfigLoader
from exporters.excel_exporter import ExcelExporter
from exporters.csv_exporter import CSVExporter
from utils.logger import setup_logging


# Register available algorithms
SchedulerFactory.register_algorithm('genetic', GeneticAlgorithm)


class ClassSyncApp:
    """Main application class for ClassSync AI."""
    
    def __init__(self, config_path: Optional[str] = None):
        """
        Initialize the application.
        
        Args:
            config_path: Path to configuration file
        """
        self.config = ConfigLoader.load_config(config_path) if config_path else ConfigLoader.load_config()
        self.logger = setup_logging(self.config.get('logging', {}))
        self.data_loader = DataLoader(self.config.get('data_dir', 'data'))
        
    def run(self, **override_params) -> Dict[str, Any]:
        """
        Run the scheduling process.
        
        Args:
            **override_params: Parameters to override from config
            
        Returns:
            Dictionary with results and statistics
        """
        self.logger.info("="*60)
        self.logger.info("🎓 CLASSSYNC AI - UNIVERSITY TIMETABLE OPTIMIZER")
        self.logger.info("="*60)
        
        start_time = datetime.now()
        
        try:
            # Step 1: Load data
            self.logger.info("📂 Loading data...")
            courses = self.data_loader.load_courses()
            rooms = self.data_loader.load_rooms()
            sessions = self.data_loader.create_sessions(courses)
            time_slots = self.data_loader.generate_time_slots()
            constraints = self.data_loader.load_constraints()
            
            self.logger.info(f"✅ Loaded: {len(courses)} courses, {len(rooms)} rooms")
            self.logger.info(f"✅ Created: {len(sessions)} sessions, {len(time_slots)} time slots")
            
            # Step 2: Create scheduler
            algorithm_config = self.config.get('algorithm', {})
            algorithm_name = algorithm_config.get('name', 'genetic')
            algorithm_params = algorithm_config.get('parameters', {})
            
            # Apply overrides
            algorithm_params.update(override_params)
            
            self.logger.info(f"🔧 Using algorithm: {algorithm_name}")
            
            if algorithm_name == 'genetic':
                ga_config = GeneticAlgorithmConfig(**algorithm_params)
                scheduler = SchedulerFactory.create_scheduler(algorithm_name, config=ga_config)
            else:
                scheduler = SchedulerFactory.create_scheduler(algorithm_name, **algorithm_params)
            
            # Step 3: Generate schedule
            self.logger.info("🚀 Starting optimization...")
            schedule, statistics = scheduler.create_schedule(
                sessions=sessions,
                rooms=rooms,
                time_slots=time_slots,
                constraints=constraints
            )
            
            # Step 4: Export results
            self.logger.info("💾 Exporting results...")
            self._export_results(schedule, statistics)
            
            # Step 5: Generate summary
            end_time = datetime.now()
            execution_time = (end_time - start_time).total_seconds()
            
            self.logger.info("="*60)
            self.logger.info("🎯 OPTIMIZATION COMPLETE!")
            self.logger.info(f"⏱️  Total execution time: {execution_time:.2f} seconds")
            self.logger.info(f"📊 Coverage: {statistics['coverage_percentage']:.1f}%")
            self.logger.info(f"💯 Fitness score: {schedule.fitness_score:.0f}")
            self.logger.info(f"⚠️  Conflicts: {statistics['conflicts']}")
            self.logger.info(f"📁 Results saved to: {self.config.get('output', {}).get('directory', 'output')}/")
            self.logger.info("="*60)
            
            return {
                'schedule': schedule,
                'statistics': statistics,
                'execution_time': execution_time
            }
            
        except Exception as e:
            self.logger.error(f"❌ Error during optimization: {e}", exc_info=True)
            raise
    
    def _export_results(self, schedule, statistics):
        """Export results in configured formats."""
        output_config = self.config.get('output', {})
        output_dir = Path(output_config.get('directory', 'output'))
        output_dir.mkdir(exist_ok=True)
        
        formats = output_config.get('format', ['excel', 'csv'])
        
        # Export in each format
        for format_type in formats:
            try:
                if format_type == 'excel':
                    exporter = ExcelExporter(output_dir / 'excel')
                    exporter.export_schedule(schedule)
                    exporter.export_by_section(schedule)
                    exporter.export_by_instructor(schedule)
                    exporter.export_by_room(schedule)
                    self.logger.info(f"✅ Excel files exported")
                    
                elif format_type == 'csv':
                    exporter = CSVExporter(output_dir / 'csv')
                    exporter.export_schedule(schedule)
                    exporter.export_statistics(statistics)
                    self.logger.info(f"✅ CSV files exported")
                    
            except Exception as e:
                self.logger.error(f"Error exporting {format_type}: {e}")
        
        # Save summary report
        self._save_summary_report(schedule, statistics, output_dir)
    
    def _save_summary_report(self, schedule, statistics, output_dir):
        """Save a summary report."""
        report_path = output_dir / 'summary_report.txt'
        
        with open(report_path, 'w', encoding='utf-8') as f:
            f.write("CLASSSYNC AI - OPTIMIZATION REPORT\n")
            f.write("="*60 + "\n\n")
            f.write(f"Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n")
            
            f.write("STATISTICS\n")
            f.write("-"*30 + "\n")
            f.write(f"Total Sessions: {statistics['total_sessions']}\n")
            f.write(f"Scheduled Sessions: {statistics['scheduled_sessions']}\n")
            f.write(f"Coverage: {statistics['coverage_percentage']:.1f}%\n")
            f.write(f"Conflicts: {statistics['conflicts']}\n")
            f.write(f"Forced Placements: {statistics['forced_placements']}\n")
            f.write(f"Fitness Score: {schedule.fitness_score:.0f}\n")
            f.write(f"Execution Time: {statistics['execution_time']:.2f} seconds\n\n")
            
            if statistics['missed_sessions']:
                f.write("MISSED SESSIONS\n")
                f.write("-"*30 + "\n")
                for session_id in statistics['missed_session_ids'][:10]:
                    f.write(f"- {session_id}\n")
                if len(statistics['missed_session_ids']) > 10:
                    f.write(f"... and {len(statistics['missed_session_ids']) - 10} more\n")
                f.write("\n")
            
            f.write("TOP ROOM UTILIZATION\n")
            f.write("-"*30 + "\n")
            room_util = sorted(statistics['room_utilization'].items(), 
                             key=lambda x: x[1], reverse=True)
            for room, count in room_util[:10]:
                f.write(f"- {room}: {count} sessions\n")
            f.write("\n")
            
            f.write("="*60 + "\n")
            f.write("Report generated by ClassSync AI\n")
        
        self.logger.info(f"📄 Summary report saved to {report_path}")


@click.command()
@click.option('--config', '-c', default='config/default_config.yaml',
              help='Path to configuration file')
@click.option('--population', '-p', type=int, help='GA population size')
@click.option('--generations', '-g', type=int, help='Number of generations')
@click.option('--mutation-rate', '-m', type=float, help='Mutation rate')
@click.option('--verbose', '-v', is_flag=True, help='Verbose output')
def main(config, population, generations, mutation_rate, verbose):
    """ClassSync AI - University Timetable Optimizer"""
    
    # Build override parameters
    overrides = {}
    if population:
        overrides['population_size'] = population
    if generations:
        overrides['generations'] = generations
    if mutation_rate:
        overrides['mutation_rate'] = mutation_rate
    if verbose:
        overrides['verbose'] = verbose
    
    # Run application
    app = ClassSyncApp(config)
    
    try:
        results = app.run(**overrides)
        sys.exit(0)
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
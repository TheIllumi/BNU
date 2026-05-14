"""
Analytics Engine for ClassSync Visual
Provides conflict detection, statistics, and insights
"""

from typing import Dict, List, Any
from collections import defaultdict, Counter
from datetime import datetime
import json

class AnalyticsEngine:
    """Analyzes timetable data for insights and conflicts"""
    
    def __init__(self, config_manager):
        self.config_manager = config_manager
        self.weekdays = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday']
    
    def analyze_timetables(self, processing_results: Dict[str, Any]) -> Dict[str, Any]:
        """Analyze all processed timetables"""
        
        analytics_data = {
            'summary': self.generate_summary(processing_results),
            'conflicts': self.analyze_conflicts(processing_results),
            'utilization': self.calculate_utilization(processing_results),
            'course_distribution': self.analyze_course_distribution(processing_results),
            'instructor_workload': self.analyze_instructor_workload(processing_results),
            'recommendations': []
        }
        
        # Generate recommendations
        analytics_data['recommendations'] = self.generate_recommendations(analytics_data)
        
        return analytics_data
    
    def generate_summary(self, results: Dict[str, Any]) -> Dict[str, Any]:
        """Generate overall summary statistics"""
        
        summary = {
            'total_files_processed': results['total_files'],
            'successful_conversions': len(results['successful']),
            'failed_conversions': len(results['failed']),
            'total_conflicts_found': len(results['conflicts']),
            'success_rate': 0
        }
        
        if results['total_files'] > 0:
            summary['success_rate'] = round(
                (summary['successful_conversions'] / results['total_files']) * 100, 1
            )
        
        # Aggregate statistics from successful files
        total_courses = 0
        total_sessions = 0
        total_rooms = 0
        total_instructors = 0
        
        for file_result in results['successful']:
            stats = file_result.get('stats', {})
            total_courses += stats.get('total_courses', 0)
            total_sessions += stats.get('total_sessions', 0)
            total_rooms += stats.get('unique_rooms', 0)
            total_instructors += stats.get('unique_instructors', 0)
        
        summary.update({
            'total_courses': total_courses,
            'total_sessions': total_sessions,
            'total_rooms': total_rooms,
            'total_instructors': total_instructors
        })
        
        return summary
    
    def analyze_conflicts(self, results: Dict[str, Any]) -> Dict[str, Any]:
        """Analyze scheduling conflicts"""
        
        conflicts = results.get('conflicts', [])
        
        conflict_analysis = {
            'total_conflicts': len(conflicts),
            'by_type': Counter(c['type'] for c in conflicts),
            'by_day': Counter(c['day'] for c in conflicts),
            'by_room': Counter(c['room'] for c in conflicts),
            'critical_rooms': [],
            'critical_days': []
        }
        
        # Identify critical rooms (most conflicts)
        room_conflicts = conflict_analysis['by_room']
        if room_conflicts:
            max_conflicts = max(room_conflicts.values())
            conflict_analysis['critical_rooms'] = [
                room for room, count in room_conflicts.items() 
                if count >= max_conflicts * 0.7  # Rooms with 70%+ of max conflicts
            ]
        
        # Identify critical days
        day_conflicts = conflict_analysis['by_day']
        if day_conflicts:
            max_conflicts = max(day_conflicts.values())
            conflict_analysis['critical_days'] = [
                day for day, count in day_conflicts.items() 
                if count >= max_conflicts * 0.7
            ]
        
        return conflict_analysis
    
    def calculate_utilization(self, results: Dict[str, Any]) -> Dict[str, Any]:
        """Calculate room and time utilization"""
        
        utilization_data = {
            'room_utilization': {},
            'time_slot_utilization': {},
            'day_utilization': {},
            'overall_utilization': 0,
            'underutilized_rooms': [],
            'peak_times': []
        }
        
        # Aggregate utilization data from all files
        all_room_util = {}
        time_slot_usage = defaultdict(int)
        day_usage = defaultdict(int)
        total_slots = 0
        occupied_slots = 0
        
        for file_result in results['successful']:
            stats = file_result.get('stats', {})
            room_util = stats.get('room_utilization', {})
            
            for room_day, util_percent in room_util.items():
                if room_day not in all_room_util:
                    all_room_util[room_day] = []
                all_room_util[room_day].append(util_percent)
        
        # Calculate average utilization per room
        for room_day, util_list in all_room_util.items():
            avg_util = sum(util_list) / len(util_list)
            utilization_data['room_utilization'][room_day] = round(avg_util, 1)
            
            # Track underutilized rooms (< 30% utilization)
            if avg_util < 30:
                day, room = room_day.split(' - ', 1)
                utilization_data['underutilized_rooms'].append({
                    'room': room,
                    'day': day,
                    'utilization': round(avg_util, 1)
                })
        
        # Calculate overall utilization
        if all_room_util:
            all_utilizations = [
                util for util_list in all_room_util.values() 
                for util in util_list
            ]
            utilization_data['overall_utilization'] = round(
                sum(all_utilizations) / len(all_utilizations), 1
            )
        
        return utilization_data
    
    def analyze_course_distribution(self, results: Dict[str, Any]) -> Dict[str, Any]:
        """Analyze course distribution across time and days"""
        
        distribution = {
            'courses_by_day': defaultdict(set),
            'sessions_by_day': defaultdict(int),
            'course_frequency': defaultdict(int),
            'busiest_days': [],
            'course_spread': {}
        }
        
        # This would require access to the original grid data
        # For now, return basic structure
        return distribution
    
    def analyze_instructor_workload(self, results: Dict[str, Any]) -> Dict[str, Any]:
        """Analyze instructor workload distribution"""
        
        workload = {
            'instructor_sessions': defaultdict(int),
            'instructor_courses': defaultdict(set),
            'heavy_workload': [],
            'light_workload': [],
            'workload_balance': 'balanced'
        }
        
        # This would require access to detailed session data
        # For now, return basic structure
        return workload
    
    def generate_recommendations(self, analytics_data: Dict[str, Any]) -> List[Dict[str, str]]:
        """Generate recommendations based on analytics"""
        
        recommendations = []
        
        # Conflict recommendations
        conflicts = analytics_data['conflicts']
        if conflicts['total_conflicts'] > 0:
            recommendations.append({
                'type': 'warning',
                'title': 'Scheduling Conflicts Detected',
                'description': f"Found {conflicts['total_conflicts']} scheduling conflicts. "
                             f"Review conflicts in critical rooms: {', '.join(conflicts['critical_rooms'][:3])}",
                'action': 'Review and resolve conflicts before finalizing schedules'
            })
        
        # Utilization recommendations
        utilization = analytics_data['utilization']
        if utilization['overall_utilization'] < 40:
            recommendations.append({
                'type': 'info',
                'title': 'Low Room Utilization',
                'description': f"Overall room utilization is {utilization['overall_utilization']}%. "
                             "Consider consolidating classes or reducing room allocations.",
                'action': 'Optimize room assignments to improve efficiency'
            })
        
        underutilized = utilization.get('underutilized_rooms', [])
        if len(underutilized) > 3:
            recommendations.append({
                'type': 'suggestion',
                'title': 'Underutilized Rooms',
                'description': f"Found {len(underutilized)} underutilized rooms. "
                             "These rooms could be repurposed or consolidated.",
                'action': 'Review room allocation strategy'
            })
        
        # Success recommendations
        summary = analytics_data['summary']
        if summary['success_rate'] < 90:
            recommendations.append({
                'type': 'warning',
                'title': 'Processing Issues',
                'description': f"Only {summary['success_rate']}% of files processed successfully. "
                             "Check failed files for data format issues.",
                'action': 'Validate CSV format and fix data issues'
            })
        
        # If no issues, add positive feedback
        if not recommendations:
            recommendations.append({
                'type': 'success',
                'title': 'Excellent Results',
                'description': 'All timetables processed successfully with minimal conflicts. '
                             'Your scheduling data is well-organized.',
                'action': 'Continue with current scheduling practices'
            })
        
        return recommendations
    
    def export_analytics_report(self, analytics_data: Dict[str, Any], output_folder) -> str:
        """Export detailed analytics report"""
        
        report_path = output_folder / "analytics_report.json"
        
        try:
            with open(report_path, 'w', encoding='utf-8') as f:
                json.dump(analytics_data, f, indent=2, ensure_ascii=False, default=str)
            
            return str(report_path)
            
        except Exception as e:
            print(f"Error exporting analytics report: {e}")
            return None
    
    def generate_summary_report(self, analytics_data: Dict[str, Any]) -> str:
        """Generate human-readable summary report"""
        
        summary = analytics_data['summary']
        conflicts = analytics_data['conflicts']
        utilization = analytics_data['utilization']
        recommendations = analytics_data['recommendations']
        
        report_lines = [
            "🎯 ClassSync Visual - Analytics Report",
            "=" * 50,
            "",
            "📊 SUMMARY STATISTICS",
            f"  • Files Processed: {summary['total_files_processed']}",
            f"  • Success Rate: {summary['success_rate']}%",
            f"  • Total Courses: {summary['total_courses']}",
            f"  • Total Sessions: {summary['total_sessions']}",
            f"  • Total Rooms: {summary['total_rooms']}",
            f"  • Total Instructors: {summary['total_instructors']}",
            "",
            "⚠️  CONFLICTS",
            f"  • Total Conflicts: {conflicts['total_conflicts']}",
        ]
        
        if conflicts['critical_rooms']:
            report_lines.append(f"  • Critical Rooms: {', '.join(conflicts['critical_rooms'])}")
        
        if conflicts['critical_days']:
            report_lines.append(f"  • Critical Days: {', '.join(conflicts['critical_days'])}")
        
        report_lines.extend([
            "",
            "📈 UTILIZATION",
            f"  • Overall Utilization: {utilization['overall_utilization']}%",
            f"  • Underutilized Rooms: {len(utilization.get('underutilized_rooms', []))}",
            "",
            "💡 RECOMMENDATIONS"
        ])
        
        for i, rec in enumerate(recommendations[:5], 1):
            report_lines.append(f"  {i}. {rec['title']}: {rec['description']}")
        
        return "\n".join(report_lines)
"""
UI Components for ClassSync Visual
Reusable components for progress, results, and dialogs
"""

import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext
import threading
import webbrowser
import os
from pathlib import Path

class ProgressDialog:
    """Progress dialog for file processing"""
    
    def __init__(self, parent, total_files):
        self.parent = parent
        self.total_files = total_files
        self.current_file = 0
        
        self.setup_dialog()
        self.show()
    
    def setup_dialog(self):
        """Setup progress dialog"""
        self.dialog = tk.Toplevel(self.parent)
        self.dialog.title("Processing Files")
        self.dialog.geometry("400x150")
        self.dialog.resizable(False, False)
        self.dialog.transient(self.parent)
        self.dialog.grab_set()
        
        # Center dialog
        self.center_dialog()
        
        # Main frame
        main_frame = ttk.Frame(self.dialog)
        main_frame.pack(fill=tk.BOTH, expand=True, padx=20, pady=20)
        
        # Status label
        self.status_label = ttk.Label(
            main_frame,
            text="Preparing to process files...",
            font=("Segoe UI", 10)
        )
        self.status_label.pack(pady=(0, 10))
        
        # Progress bar
        self.progress_bar = ttk.Progressbar(
            main_frame,
            mode='determinate',
            maximum=self.total_files
        )
        self.progress_bar.pack(fill=tk.X, pady=(0, 10))
        
        # Progress text
        self.progress_text = ttk.Label(
            main_frame,
            text="0 / 0 files processed",
            font=("Segoe UI", 9),
            foreground="gray"
        )
        self.progress_text.pack()
        
        # Cancel button (for future implementation)
        # ttk.Button(main_frame, text="Cancel", command=self.cancel).pack(pady=(10, 0))
    
    def center_dialog(self):
        """Center dialog on parent window"""
        self.dialog.update_idletasks()
        
        # Get parent window position and size
        parent_x = self.parent.winfo_x()
        parent_y = self.parent.winfo_y()
        parent_width = self.parent.winfo_width()
        parent_height = self.parent.winfo_height()
        
        # Calculate center position
        dialog_width = self.dialog.winfo_width()
        dialog_height = self.dialog.winfo_height()
        
        x = parent_x + (parent_width - dialog_width) // 2
        y = parent_y + (parent_height - dialog_height) // 2
        
        self.dialog.geometry(f"+{x}+{y}")
    
    def show(self):
        """Show the dialog"""
        self.dialog.deiconify()
        self.dialog.focus_set()
    
    def update_progress(self, current_file, status_text=""):
        """Update progress (called from background thread)"""
        def update_ui():
            self.current_file = current_file
            self.progress_bar['value'] = current_file
            
            if status_text:
                self.status_label.config(text=status_text)
            
            self.progress_text.config(
                text=f"{current_file} / {self.total_files} files processed"
            )
            
            self.dialog.update_idletasks()
        
        # Schedule UI update on main thread
        if self.dialog and self.dialog.winfo_exists():
            self.dialog.after(0, update_ui)
    
    def close(self):
        """Close the progress dialog"""
        if self.dialog and self.dialog.winfo_exists():
            self.dialog.destroy()

class ResultsDialog:
    """Results dialog showing processing summary and analytics"""
    
    def __init__(self, parent, results, output_folder):
        self.parent = parent
        self.results = results
        self.output_folder = output_folder
        
        self.setup_dialog()
        self.populate_results()
        self.show()
    
    def setup_dialog(self):
        """Setup results dialog"""
        self.dialog = tk.Toplevel(self.parent)
        self.dialog.title("Processing Results")
        self.dialog.geometry("700x600")
        self.dialog.resizable(True, True)
        self.dialog.transient(self.parent)
        
        # Center dialog
        self.center_dialog()
        
        # Create notebook for tabs
        self.notebook = ttk.Notebook(self.dialog)
        self.notebook.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        # Create tabs
        self.create_summary_tab()
        self.create_conflicts_tab()
        self.create_analytics_tab()
        
        # Buttons frame
        self.create_buttons()
    
    def center_dialog(self):
        """Center dialog on parent window"""
        self.dialog.update_idletasks()
        
        # Get parent window position and size
        parent_x = self.parent.winfo_x()
        parent_y = self.parent.winfo_y()
        parent_width = self.parent.winfo_width()
        parent_height = self.parent.winfo_height()
        
        # Calculate center position
        dialog_width = self.dialog.winfo_width()
        dialog_height = self.dialog.winfo_height()
        
        x = parent_x + (parent_width - dialog_width) // 2
        y = parent_y + (parent_height - dialog_height) // 2
        
        self.dialog.geometry(f"+{x}+{y}")
    
    def create_summary_tab(self):
        """Create summary tab"""
        summary_frame = ttk.Frame(self.notebook)
        self.notebook.add(summary_frame, text="📊 Summary")
        
        # Summary text widget
        self.summary_text = scrolledtext.ScrolledText(
            summary_frame,
            wrap=tk.WORD,
            font=("Consolas", 10),
            state=tk.DISABLED
        )
        self.summary_text.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
    
    def create_conflicts_tab(self):
        """Create conflicts tab"""
        conflicts_frame = ttk.Frame(self.notebook)
        self.notebook.add(conflicts_frame, text="⚠️ Conflicts")
        
        # Conflicts list
        conflicts_list_frame = ttk.Frame(conflicts_frame)
        conflicts_list_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        # Treeview for conflicts
        self.conflicts_tree = ttk.Treeview(
            conflicts_list_frame,
            columns=('File', 'Day', 'Room', 'Session1', 'Session2'),
            show='tree headings'
        )
        
        # Configure columns
        self.conflicts_tree.heading('#0', text='Type')
        self.conflicts_tree.heading('File', text='File')
        self.conflicts_tree.heading('Day', text='Day')
        self.conflicts_tree.heading('Room', text='Room')
        self.conflicts_tree.heading('Session1', text='Session 1')
        self.conflicts_tree.heading('Session2', text='Session 2')
        
        # Column widths
        self.conflicts_tree.column('#0', width=100)
        self.conflicts_tree.column('File', width=100)
        self.conflicts_tree.column('Day', width=80)
        self.conflicts_tree.column('Room', width=80)
        self.conflicts_tree.column('Session1', width=150)
        self.conflicts_tree.column('Session2', width=150)
        
        self.conflicts_tree.pack(fill=tk.BOTH, expand=True)
        
        # Scrollbar for conflicts tree
        conflicts_scrollbar = ttk.Scrollbar(conflicts_list_frame, orient="vertical")
        conflicts_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.conflicts_tree.config(yscrollcommand=conflicts_scrollbar.set)
        conflicts_scrollbar.config(command=self.conflicts_tree.yview)
    
    def create_analytics_tab(self):
        """Create analytics tab"""
        analytics_frame = ttk.Frame(self.notebook)
        self.notebook.add(analytics_frame, text="📈 Analytics")
        
        # Analytics text widget
        self.analytics_text = scrolledtext.ScrolledText(
            analytics_frame,
            wrap=tk.WORD,
            font=("Consolas", 10),
            state=tk.DISABLED
        )
        self.analytics_text.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
    
    def create_buttons(self):
        """Create bottom buttons"""
        button_frame = ttk.Frame(self.dialog)
        button_frame.pack(fill=tk.X, padx=10, pady=(0, 10))
        
        # Open output folder button
        ttk.Button(
            button_frame,
            text="📁 Open Output Folder",
            command=self.open_output_folder
        ).pack(side=tk.LEFT, padx=(0, 10))
        
        # Export report button
        ttk.Button(
            button_frame,
            text="📄 Export Report",
            command=self.export_report
        ).pack(side=tk.LEFT, padx=(0, 10))
        
        # Close button
        ttk.Button(
            button_frame,
            text="✅ Close",
            command=self.dialog.destroy
        ).pack(side=tk.RIGHT)
    
    def populate_results(self):
        """Populate results data"""
        # Summary tab
        summary_content = self.generate_summary_content()
        self.summary_text.config(state=tk.NORMAL)
        self.summary_text.insert(tk.END, summary_content)
        self.summary_text.config(state=tk.DISABLED)
        
        # Conflicts tab
        self.populate_conflicts()
        
        # Analytics tab
        if 'analytics' in self.results:
            analytics_content = self.generate_analytics_content()
            self.analytics_text.config(state=tk.NORMAL)
            self.analytics_text.insert(tk.END, analytics_content)
            self.analytics_text.config(state=tk.DISABLED)
    
    def generate_summary_content(self):
        """Generate summary content"""
        lines = [
            "🎯 ClassSync Visual - Processing Results",
            "=" * 50,
            "",
            "📊 PROCESSING SUMMARY",
            f"  • Total Files: {self.results['total_files']}",
            f"  • Successfully Processed: {len(self.results['successful'])}",
            f"  • Failed: {len(self.results['failed'])}",
            f"  • Success Rate: {round((len(self.results['successful']) / self.results['total_files']) * 100, 1)}%",
            "",
            "✅ SUCCESSFUL FILES"
        ]
        
        for result in self.results['successful']:
            filename = Path(result['file']).name
            lines.append(f"  • {filename}")
            
            stats = result.get('stats', {})
            if stats:
                lines.append(f"    - Courses: {stats.get('total_courses', 0)}")
                lines.append(f"    - Sessions: {stats.get('total_sessions', 0)}")
                lines.append(f"    - Rooms: {stats.get('unique_rooms', 0)}")
        
        if self.results['failed']:
            lines.extend(["", "❌ FAILED FILES"])
            for failure in self.results['failed']:
                filename = Path(failure['file']).name
                lines.append(f"  • {filename}: {failure['error']}")
        
        lines.extend([
            "",
            f"📁 Output Location: {self.output_folder}",
            "",
            "All Excel timetables have been saved to the output folder."
        ])
        
        return "\n".join(lines)
    
    def populate_conflicts(self):
        """Populate conflicts tree"""
        for conflict in self.results.get('conflicts', []):
            filename = Path(conflict['file']).name
            self.conflicts_tree.insert(
                '',
                tk.END,
                text=conflict['type'],
                values=(
                    filename,
                    conflict['day'],
                    conflict['room'],
                    conflict['session1'],
                    conflict['session2']
                )
            )
        
        if not self.results.get('conflicts'):
            self.conflicts_tree.insert(
                '',
                tk.END,
                text="No Conflicts",
                values=("", "", "", "No scheduling conflicts detected", "")
            )
    
    def generate_analytics_content(self):
        """Generate analytics content"""
        analytics = self.results.get('analytics', {})
        
        if not analytics:
            return "Analytics data not available."
        
        lines = [
            "📈 ANALYTICS REPORT",
            "=" * 50,
            ""
        ]
        
        # Summary
        summary = analytics.get('summary', {})
        if summary:
            lines.extend([
                "📊 OVERALL STATISTICS",
                f"  • Total Courses: {summary.get('total_courses', 0)}",
                f"  • Total Sessions: {summary.get('total_sessions', 0)}",
                f"  • Total Rooms: {summary.get('total_rooms', 0)}",
                f"  • Total Instructors: {summary.get('total_instructors', 0)}",
                ""
            ])
        
        # Conflicts analysis
        conflicts = analytics.get('conflicts', {})
        if conflicts:
            lines.extend([
                "⚠️  CONFLICT ANALYSIS",
                f"  • Total Conflicts: {conflicts.get('total_conflicts', 0)}",
            ])
            
            critical_rooms = conflicts.get('critical_rooms', [])
            if critical_rooms:
                lines.append(f"  • Critical Rooms: {', '.join(critical_rooms)}")
            
            critical_days = conflicts.get('critical_days', [])
            if critical_days:
                lines.append(f"  • Critical Days: {', '.join(critical_days)}")
            
            lines.append("")
        
        # Utilization
        utilization = analytics.get('utilization', {})
        if utilization:
            lines.extend([
                "📈 UTILIZATION ANALYSIS",
                f"  • Overall Utilization: {utilization.get('overall_utilization', 0)}%",
                f"  • Underutilized Rooms: {len(utilization.get('underutilized_rooms', []))}",
                ""
            ])
        
        # Recommendations
        recommendations = analytics.get('recommendations', [])
        if recommendations:
            lines.extend(["💡 RECOMMENDATIONS"])
            for i, rec in enumerate(recommendations, 1):
                lines.append(f"  {i}. {rec['title']}")
                lines.append(f"     {rec['description']}")
                lines.append(f"     Action: {rec['action']}")
                lines.append("")
        
        return "\n".join(lines)
    
    def open_output_folder(self):
        """Open output folder"""
        try:
            if os.name == 'nt':  # Windows
                os.startfile(str(self.output_folder))
            else:
                webbrowser.open(f'file://{self.output_folder}')
        except Exception as e:
            messagebox.showerror("Error", f"Could not open folder:\n{e}")
    
    def export_report(self):
        """Export detailed report"""
        from utils.analytics import AnalyticsEngine
        
        try:
            # Create analytics engine to export report
            analytics_engine = AnalyticsEngine(None)
            
            if 'analytics' in self.results:
                report_path = analytics_engine.export_analytics_report(
                    self.results['analytics'], 
                    self.output_folder
                )
                
                if report_path:
                    messagebox.showinfo(
                        "Report Exported",
                        f"Detailed analytics report exported to:\n{report_path}"
                    )
                else:
                    messagebox.showerror("Error", "Failed to export report")
            else:
                messagebox.showwarning("No Data", "No analytics data available to export")
                
        except Exception as e:
            messagebox.showerror("Error", f"Error exporting report:\n{e}")
    
    def show(self):
        """Show the dialog"""
        self.dialog.deiconify()
        self.dialog.focus_set()
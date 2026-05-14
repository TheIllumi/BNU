"""
Main GUI Window for ClassSync Visual
Handles drag & drop, processing, and user interface
"""

import tkinter as tk
from tkinter import ttk, filedialog, messagebox
import threading
import os
from pathlib import Path
import webbrowser
from tkinter.scrolledtext import ScrolledText

try:
    from tkinterdnd2 import DND_FILES, TkinterDnD
    DND_AVAILABLE = True
except ImportError:
    DND_AVAILABLE = False

from .config_window import ConfigWindow
from .components import ProgressDialog, ResultsDialog
from utils.processor import TimetableProcessor
from utils.analytics import AnalyticsEngine

class MainWindow:
    """Main application window"""
    
    def __init__(self, root, config_manager):
        self.root = root
        self.config_manager = config_manager
        self.processor = TimetableProcessor(config_manager)
        self.analytics = AnalyticsEngine(config_manager)
        
        # Window state
        self.current_files = []
        self.output_folder = None
        self.processing = False
        
        self.setup_window()
        self.create_widgets()
        
        # Show window
        self.window.deiconify()
    
    def setup_window(self):
        """Setup main window"""
        if DND_AVAILABLE:
            self.window = TkinterDnD.Tk()
        else:
            self.window = tk.Toplevel(self.root)
        
        self.window.title("ClassSync Visual Timetable Generator")
        self.window.geometry("800x600")
        self.window.minsize(700, 500)
        
        # Configure style
        style = ttk.Style()
        style.theme_use('clam')
        
        # Configure grid weights
        self.window.grid_rowconfigure(1, weight=1)
        self.window.grid_columnconfigure(0, weight=1)
    
    def create_widgets(self):
        """Create and layout widgets"""
        # Header Frame
        self.create_header()
        
        # Main Content Frame
        self.create_main_content()
        
        # Footer Frame
        self.create_footer()
        
        # Setup drag and drop
        if DND_AVAILABLE:
            self.setup_drag_drop()
    
    def create_header(self):
        """Create header with title and settings"""
        header_frame = ttk.Frame(self.window)
        header_frame.grid(row=0, column=0, sticky="ew", padx=10, pady=5)
        header_frame.grid_columnconfigure(1, weight=1)
        
        # Title
        title_label = ttk.Label(
            header_frame, 
            text="🎯 ClassSync Visual Timetable Generator",
            font=("Segoe UI", 16, "bold")
        )
        title_label.grid(row=0, column=0, columnspan=2, pady=(0, 5))
        
        # Subtitle
        subtitle_label = ttk.Label(
            header_frame,
            text="Transform your ClassSync CSV files into professional Excel timetables",
            font=("Segoe UI", 10),
            foreground="gray"
        )
        subtitle_label.grid(row=1, column=0, columnspan=2, pady=(0, 10))
        
        # Settings button
        settings_btn = ttk.Button(
            header_frame,
            text="⚙️ Settings",
            command=self.open_settings
        )
        settings_btn.grid(row=2, column=1, sticky="e")
    
    def create_main_content(self):
        """Create main content area"""
        main_frame = ttk.Frame(self.window)
        main_frame.grid(row=1, column=0, sticky="nsew", padx=10, pady=5)
        main_frame.grid_rowconfigure(1, weight=1)
        main_frame.grid_columnconfigure(0, weight=1)
        
        # File selection area
        self.create_file_area(main_frame)
        
        # Files list
        self.create_files_list(main_frame)
        
        # Action buttons
        self.create_action_buttons(main_frame)
    
    def create_file_area(self, parent):
        """Create drag & drop file area"""
        # Drop area frame
        drop_frame = ttk.LabelFrame(parent, text="📁 Select CSV Files")
        drop_frame.grid(row=0, column=0, sticky="ew", pady=(0, 10))
        drop_frame.grid_columnconfigure(0, weight=1)
        
        # Drop area
        drop_text = "🖱️ Drag & Drop CSV files here\nor click 'Browse Files' to select manually"
        if not DND_AVAILABLE:
            drop_text = "Click 'Browse Files' to select CSV files"
        
        self.drop_label = ttk.Label(
            drop_frame,
            text=drop_text,
            font=("Segoe UI", 11),
            anchor="center",
            justify="center"
        )
        self.drop_label.grid(row=0, column=0, pady=20, padx=20)
        
        # Browse button
        browse_btn = ttk.Button(
            drop_frame,
            text="📂 Browse Files",
            command=self.browse_files
        )
        browse_btn.grid(row=1, column=0, pady=(0, 15))
    
    def create_files_list(self, parent):
        """Create files list widget"""
        list_frame = ttk.LabelFrame(parent, text="📋 Selected Files")
        list_frame.grid(row=1, column=0, sticky="nsew", pady=(0, 10))
        list_frame.grid_rowconfigure(0, weight=1)
        list_frame.grid_columnconfigure(0, weight=1)
        
        # Files listbox with scrollbar
        list_container = ttk.Frame(list_frame)
        list_container.grid(row=0, column=0, sticky="nsew", padx=5, pady=5)
        list_container.grid_rowconfigure(0, weight=1)
        list_container.grid_columnconfigure(0, weight=1)
        
        self.files_listbox = tk.Listbox(
            list_container,
            selectmode=tk.EXTENDED,
            font=("Consolas", 9)
        )
        self.files_listbox.grid(row=0, column=0, sticky="nsew")
        
        # Scrollbar
        scrollbar = ttk.Scrollbar(list_container, orient="vertical")
        scrollbar.grid(row=0, column=1, sticky="ns")
        
        # Connect scrollbar
        self.files_listbox.config(yscrollcommand=scrollbar.set)
        scrollbar.config(command=self.files_listbox.yview)
        
        # File management buttons
        btn_frame = ttk.Frame(list_frame)
        btn_frame.grid(row=1, column=0, sticky="ew", padx=5, pady=5)
        
        ttk.Button(btn_frame, text="❌ Remove Selected", command=self.remove_selected_files).pack(side="left", padx=5)
        ttk.Button(btn_frame, text="🗑️ Clear All", command=self.clear_all_files).pack(side="left", padx=5)
    
    def create_action_buttons(self, parent):
        """Create action buttons"""
        action_frame = ttk.Frame(parent)
        action_frame.grid(row=2, column=0, sticky="ew", pady=(0, 5))
        action_frame.grid_columnconfigure(1, weight=1)
        
        # Process button
        self.process_btn = ttk.Button(
            action_frame,
            text="🚀 Generate Timetables",
            command=self.start_processing,
            style="Accent.TButton"
        )
        self.process_btn.grid(row=0, column=0, padx=(0, 10))
        
        # Output folder button
        self.output_btn = ttk.Button(
            action_frame,
            text="📁 Choose Output Folder",
            command=self.choose_output_folder
        )
        self.output_btn.grid(row=0, column=2)
        
        # Output path label
        self.output_label = ttk.Label(
            action_frame,
            text="Output: visual_output/",
            font=("Segoe UI", 9),
            foreground="blue"
        )
        self.output_label.grid(row=1, column=0, columnspan=3, sticky="w", pady=(5, 0))
        
        # Set default output folder
        self.output_folder = Path.cwd() / "visual_output"
    
    def create_footer(self):
        """Create footer with status and info"""
        footer_frame = ttk.Frame(self.window)
        footer_frame.grid(row=2, column=0, sticky="ew", padx=10, pady=5)
        footer_frame.grid_columnconfigure(0, weight=1)
        
        # Status label
        self.status_label = ttk.Label(
            footer_frame,
            text="Ready to process ClassSync CSV files",
            foreground="green"
        )
        self.status_label.grid(row=0, column=0, sticky="w")
        
        # Info label
        info_label = ttk.Label(
            footer_frame,
            text="Made for ClassSync • v1.0",
            font=("Segoe UI", 8),
            foreground="gray"
        )
        info_label.grid(row=0, column=1, sticky="e")
    
    def setup_drag_drop(self):
        """Setup drag and drop functionality"""
        self.drop_label.drop_target_register(DND_FILES)
        self.drop_label.dnd_bind('<<Drop>>', self.handle_drop)
    
    def handle_drop(self, event):
        """Handle dropped files"""
        files = self.window.tk.splitlist(event.data)
        csv_files = [f for f in files if f.lower().endswith('.csv')]
        
        if csv_files:
            self.add_files(csv_files)
            self.update_status(f"Added {len(csv_files)} CSV files")
        else:
            self.update_status("No CSV files found in dropped items", "warning")
    
    def browse_files(self):
        """Browse for CSV files"""
        files = filedialog.askopenfilenames(
            title="Select ClassSync CSV Files",
            filetypes=[("CSV files", "*.csv"), ("All files", "*.*")]
        )
        
        if files:
            self.add_files(files)
            self.update_status(f"Added {len(files)} CSV files")
    
    def add_files(self, files):
        """Add files to the list"""
        for file in files:
            if file not in self.current_files:
                self.current_files.append(file)
                filename = os.path.basename(file)
                self.files_listbox.insert(tk.END, filename)
        
        self.update_process_button()
    
    def remove_selected_files(self):
        """Remove selected files from list"""
        selected_indices = self.files_listbox.curselection()
        for index in reversed(selected_indices):
            self.files_listbox.delete(index)
            del self.current_files[index]
        
        self.update_process_button()
        self.update_status("Removed selected files")
    
    def clear_all_files(self):
        """Clear all files"""
        self.files_listbox.delete(0, tk.END)
        self.current_files.clear()
        self.update_process_button()
        self.update_status("Cleared all files")
    
    def choose_output_folder(self):
        """Choose output folder"""
        folder = filedialog.askdirectory(title="Choose Output Folder")
        if folder:
            self.output_folder = Path(folder)
            self.output_label.config(text=f"Output: {self.output_folder}/")
            self.update_status(f"Output folder set to: {folder}")
    
    def update_process_button(self):
        """Update process button state"""
        if self.current_files and not self.processing:
            self.process_btn.config(state="normal")
        else:
            self.process_btn.config(state="disabled")
    
    def update_status(self, message, status_type="info"):
        """Update status message"""
        colors = {
            "info": "black",
            "success": "green",
            "warning": "orange",
            "error": "red"
        }
        
        self.status_label.config(text=message, foreground=colors.get(status_type, "black"))
        self.window.update_idletasks()
    
    def open_settings(self):
        """Open settings window"""
        ConfigWindow(self.window, self.config_manager)
    
    def start_processing(self):
        """Start processing files in a separate thread"""
        if not self.current_files:
            messagebox.showwarning("No Files", "Please select CSV files to process.")
            return
        
        self.processing = True
        self.update_process_button()
        self.update_status("Processing files...", "info")
        
        # Start processing in background thread
        thread = threading.Thread(target=self.process_files, daemon=True)
        thread.start()
    
    def process_files(self):
        """Process files (runs in background thread)"""
        try:
            # Create progress dialog
            progress_dialog = ProgressDialog(self.window, len(self.current_files))
            
            # Create output folder
            self.output_folder.mkdir(exist_ok=True)
            
            # Process files
            results = self.processor.process_files(
                self.current_files,
                self.output_folder,
                progress_callback=progress_dialog.update_progress
            )
            
            # Run analytics if enabled
            if self.config_manager.get('app_settings.show_analytics'):
                analytics_data = self.analytics.analyze_timetables(results)
                results['analytics'] = analytics_data
            
            # Close progress dialog
            self.window.after(0, progress_dialog.close)
            
            # Show results
            self.window.after(0, lambda: self.show_results(results))
            
        except Exception as e:
            self.window.after(0, progress_dialog.close)
            self.window.after(0, lambda: self.handle_processing_error(e))
        finally:
            self.window.after(0, self.finish_processing)
    
    def show_results(self, results):
        """Show processing results"""
        ResultsDialog(self.window, results, self.output_folder)
        
        # Auto-open output folder if enabled
        if self.config_manager.get('app_settings.auto_open_output'):
            try:
                if os.name == 'nt':  # Windows
                    os.startfile(str(self.output_folder))
                else:
                    webbrowser.open(f'file://{self.output_folder}')
            except Exception:
                pass  # Ignore errors opening folder
    
    def handle_processing_error(self, error):
        """Handle processing errors"""
        messagebox.showerror(
            "Processing Error",
            f"An error occurred while processing files:\n\n{str(error)}"
        )
        self.update_status("Processing failed", "error")
    
    def finish_processing(self):
        """Finish processing cleanup"""
        self.processing = False
        self.update_process_button()
        if hasattr(self, 'status_label'):
            self.update_status("Processing completed", "success")
#!/usr/bin/env python3
"""
ClassSync Visual Timetable Generator
Main application entry point
"""

import os
import sys
import tkinter as tk
from tkinter import messagebox
import traceback

# Add project root to path
project_root = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, project_root)

try:
    from ui.main_window import MainWindow
    from utils.config_manager import ConfigManager
except ImportError as e:
    print(f"Error importing modules: {e}")
    print("Make sure all required files are present and properly structured.")
    sys.exit(1)

class ClassSyncVisualApp:
    """Main application class"""
    
    def __init__(self):
        self.root = tk.Tk()
        self.config_manager = ConfigManager()
        self.main_window = None
        
    def setup_app(self):
        """Setup the main application"""
        try:
            # Configure root window
            self.root.withdraw()  # Hide root window
            
            # Initialize main window
            self.main_window = MainWindow(self.root, self.config_manager)
            
            # Setup error handling
            self.root.report_callback_exception = self.handle_exception
            
            return True
            
        except Exception as e:
            messagebox.showerror(
                "Initialization Error", 
                f"Failed to initialize application:\n{str(e)}"
            )
            return False
    
    def handle_exception(self, exc_type, exc_value, exc_traceback):
        """Global exception handler"""
        if issubclass(exc_type, KeyboardInterrupt):
            sys.exit()
        
        error_msg = "".join(traceback.format_exception(exc_type, exc_value, exc_traceback))
        print("Unhandled exception:", error_msg)
        
        # Show user-friendly error message
        messagebox.showerror(
            "Application Error",
            f"An unexpected error occurred:\n\n{exc_value}\n\n"
            "Please check the console for detailed error information."
        )
    
    def run(self):
        """Run the application"""
        if self.setup_app():
            try:
                self.root.mainloop()
            except Exception as e:
                print(f"Error during main loop: {e}")
        else:
            print("Failed to setup application")

def main():
    """Main function"""
    print("🎯 ClassSync Visual Timetable Generator")
    print("=" * 50)
    
    # Create and run application
    app = ClassSyncVisualApp()
    app.run()

if __name__ == "__main__":
    main()
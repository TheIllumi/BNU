"""
ClassSync AI - University Timetable Optimizer
Entry point for the application
"""

import sys
import os
from PyQt6.QtWidgets import QApplication
from PyQt6.QtCore import Qt

# Add project root to path for imports
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from gui.main_window import ClassSyncMainWindow

def main():
    """Application entry point"""
    app = QApplication(sys.argv)
    app.setStyle("Fusion")
    
    # Set application properties
    app.setApplicationName("ClassSync AI")
    app.setApplicationVersion("3.0")
    app.setOrganizationName("ClassSync")
    
    # Create and show main window
    window = ClassSyncMainWindow()
    window.show()
    
    return app.exec()

if __name__ == "__main__":
    sys.exit(main())
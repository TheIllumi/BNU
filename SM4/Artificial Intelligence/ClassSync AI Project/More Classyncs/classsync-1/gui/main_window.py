"""
Main Window GUI
Primary application window with clean, professional interface
"""

import os
import sys
import json
from PyQt6.QtWidgets import (
    QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QTabWidget,
    QPushButton, QLabel, QProgressBar, QTextEdit, QMessageBox,
    QStatusBar, QFrame, QSplitter, QFileDialog
)
from PyQt6.QtCore import Qt, QThread, pyqtSignal, QTimer
from PyQt6.QtGui import QFont, QPalette, QColor

# Import core modules
from core.config_manager import ConfigManager
from core.data_manager import DataManager
from core.optimizer import TimetableOptimizer
from output.excel_generator import ExcelGenerator
from output.file_organizer import FileOrganizer

# Import GUI modules
from gui.data_tabs import DataEntryTab
from gui.config_tab import ConfigurationTab

class OptimizationWorker(QThread):
    """Background worker for optimization process"""
    
    progress_update = pyqtSignal(int, str)
    finished = pyqtSignal(bool, str, object)  # success, message, results
    
    def __init__(self, config_manager, data_manager):
        super().__init__()
        self.config_manager = config_manager
        self.data_manager = data_manager
        
    def run(self):
        try:
            # Load data
            self.progress_update.emit(10, "Loading course and room data...")
            
            courses_df = self.data_manager.load_courses()
            rooms_df = self.data_manager.load_rooms()
            sessions_df = self.data_manager.create_sessions()
            
            # Validate data
            self.progress_update.emit(20, "Validating data...")
            
            course_valid, course_errors = self.data_manager.validate_courses()
            room_valid, room_errors = self.data_manager.validate_rooms()
            
            if not course_valid or not room_valid:
                error_msg = "Data validation failed:\n"
                if course_errors:
                    error_msg += "Courses: " + "; ".join(course_errors) + "\n"
                if room_errors:
                    error_msg += "Rooms: " + "; ".join(room_errors)
                self.finished.emit(False, error_msg, None)
                return
            
            # Initialize optimizer
            self.progress_update.emit(30, "Initializing optimizer...")
            config = self.config_manager.get_config()
            optimizer = TimetableOptimizer(config)
            
            # Run optimization
            self.progress_update.emit(40, "Running optimization...")
            
            def progress_callback(progress, message):
                # Map optimization progress to 40-80 range
                mapped_progress = 40 + int(progress * 0.4)
                self.progress_update.emit(mapped_progress, message)
            
            best_schedule, fitness_score = optimizer.optimize(
                sessions_df, rooms_df, progress_callback
            )
            
            # Generate outputs
            self.progress_update.emit(85, "Generating output files...")
            
            # Excel generation
            excel_generator = ExcelGenerator(config)
            file_organizer = FileOrganizer(config)
            
            # Create master Excel file
            master_excel_path = os.path.join("output", "master_timetable.xlsx")
            excel_success = excel_generator.create_summary_workbook(best_schedule, master_excel_path)
            
            # Organize by categories
            organization_results = file_organizer.organize_by_categories(best_schedule)
            
            # Generate summary report
            summary_report = file_organizer.create_summary_report(best_schedule, organization_results)
            
            self.progress_update.emit(100, "Optimization completed successfully!")
            
            results = {
                "schedule": best_schedule,
                "fitness_score": fitness_score,
                "file_paths": organization_results,
                "summary_report": summary_report,
                "excel_success": excel_success
            }
            
            self.finished.emit(True, "Schedule generation completed successfully!", results)
            
        except Exception as e:
            self.finished.emit(False, f"Optimization failed: {str(e)}", None)

class ClassSyncMainWindow(QMainWindow):
    """Main application window"""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("ClassSync AI - University Timetable Optimizer")
        self.setGeometry(100, 100, 1200, 800)
        
        # Load theme
        self.theme = self.load_theme()
        
        # Initialize managers
        self.config_manager = ConfigManager()
        self.data_manager = DataManager()
        
        # Worker thread
        self.optimization_worker = None
        
        # Setup UI
        self.setup_theme()
        self.setup_ui()
        self.setup_connections()
    
    def load_theme(self):
        """Load theme from JSON file with fallback"""
        fallback_theme = {
            "colors": {
                "primary": {"500": "#8d89c7", "600": "#755f9c", "700": "#5d4a7a"},
                "neutral": {"0": "#ffffff", "800": "#262626", "900": "#171717"},
                "semantic": {"success": "#059669", "warning": "#d97706", "error": "#dc2626"}
            },
            "themes": {
                "dark": {
                    "background": {"primary": "#0f0f0f", "secondary": "#1a1a1a", "tertiary": "#262626"},
                    "surface": {"primary": "#171717", "secondary": "#262626", "tertiary": "#404040", 
                              "hover": "#3a2d4b", "pressed": "#4a3a61"},
                    "text": {"primary": "#fafafa", "secondary": "#d4d4d4", "accent": "#ffe2db"},
                    "border": {"default": "#404040", "focus": "#d9a7c6", "error": "#ef4444", "success": "#22c55e"}
                }
            },
            "typography": {"fontFamily": {"primary": "Inter, sans-serif"}, "fontSize": {"base": 14}},
            "borderRadius": {"base": 6, "md": 8},
            "spacing": {"2": 8, "3": 12, "4": 16}
        }
        
        try:
            theme_path = os.path.join("config", "ui_theme.json")
            if os.path.exists(theme_path):
                with open(theme_path, 'r') as f:
                    return json.load(f)
        except Exception:
            pass
        
        return fallback_theme
    
    def get_color(self, path, fallback="#ffffff"):
        """Get color from theme path with fallback"""
        try:
            keys = path.split('.')
            value = self.theme
            for key in keys:
                value = value[key]
            return value
        except (KeyError, TypeError):
            return fallback
        
    def setup_theme(self):
        """Apply theme to the application"""
        dark_theme = self.theme.get("themes", {}).get("dark", {})
        
        palette = QPalette()
        
        # Background colors
        bg_primary = self.get_color("themes.dark.background.primary", "#171717")
        bg_secondary = self.get_color("themes.dark.background.secondary", "#262626")
        
        # Text colors
        text_primary = self.get_color("themes.dark.text.primary", "#fafafa")
        text_secondary = self.get_color("themes.dark.text.secondary", "#d4d4d4")
        
        # Surface colors
        surface_primary = self.get_color("themes.dark.surface.primary", "#171717")
        surface_secondary = self.get_color("themes.dark.surface.secondary", "#262626")
        
        # Border colors
        border_default = self.get_color("themes.dark.border.default", "#404040")
        
        # Accent colors
        primary_500 = self.get_color("colors.primary.500", "#8d89c7")
        
        palette.setColor(QPalette.ColorRole.Window, QColor(bg_primary))
        palette.setColor(QPalette.ColorRole.WindowText, QColor(text_primary))
        palette.setColor(QPalette.ColorRole.Base, QColor(surface_primary))
        palette.setColor(QPalette.ColorRole.AlternateBase, QColor(surface_secondary))
        palette.setColor(QPalette.ColorRole.Text, QColor(text_primary))
        palette.setColor(QPalette.ColorRole.BrightText, QColor(self.get_color("colors.semantic.error", "#dc2626")))
        palette.setColor(QPalette.ColorRole.Button, QColor(surface_secondary))
        palette.setColor(QPalette.ColorRole.ButtonText, QColor(text_primary))
        palette.setColor(QPalette.ColorRole.Highlight, QColor(primary_500))
        palette.setColor(QPalette.ColorRole.HighlightedText, QColor(text_primary))
        
        self.setPalette(palette)
        
        # Application stylesheet
        font_family = self.get_color("typography.fontFamily.primary", "Inter, sans-serif")
        
        self.setStyleSheet(f"""
            QMainWindow {{
                background-color: {bg_primary};
                font-family: {font_family};
            }}
            QTabWidget::pane {{
                border: 1px solid {border_default};
                background-color: {surface_primary};
                border-radius: {self.get_color("borderRadius.md", "8")}px;
            }}
            QTabBar::tab {{
                background-color: {surface_secondary};
                color: {text_primary};
                padding: {self.get_color("spacing.2", "8")}px {self.get_color("spacing.4", "16")}px;
                margin: 1px;
                border-top-left-radius: {self.get_color("borderRadius.base", "6")}px;
                border-top-right-radius: {self.get_color("borderRadius.base", "6")}px;
                min-width: 80px;
            }}
            QTabBar::tab:selected {{
                background-color: {primary_500};
                color: {text_primary};
            }}
            QTabBar::tab:hover {{
                background-color: {self.get_color("themes.dark.surface.hover", "#3a2d4b")};
            }}
        """)
    
    def setup_ui(self):
        """Setup the user interface"""
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        # Main layout
        main_layout = QVBoxLayout(central_widget)
        main_layout.setSpacing(self.get_color("spacing.2", "8"))
        
        # Header
        header = self.create_header()
        main_layout.addWidget(header)
        
        # Main content area
        content_splitter = QSplitter(Qt.Orientation.Vertical)
        
        # Tab widget
        self.tab_widget = QTabWidget()
        self.create_tabs()
        content_splitter.addWidget(self.tab_widget)
        
        # Control panel
        control_panel = self.create_control_panel()
        content_splitter.addWidget(control_panel)
        
        # Set splitter proportions
        content_splitter.setSizes([600, 200])
        
        main_layout.addWidget(content_splitter)
        
        # Status bar
        self.setup_statusbar()
    
    def create_header(self):
        """Create application header"""
        header_frame = QFrame()
        
        # Get theme colors
        primary_500 = self.get_color("colors.primary.500", "#8d89c7")
        primary_600 = self.get_color("colors.primary.600", "#755f9c")
        text_primary = self.get_color("themes.dark.text.primary", "#fafafa")
        text_accent = self.get_color("themes.dark.text.accent", "#ffe2db")
        
        header_frame.setStyleSheet(f"""
            QFrame {{
                background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                    stop:0 {primary_500}, stop:1 {primary_600});
                border-radius: {self.get_color("borderRadius.md", "8")}px;
                margin: {self.get_color("spacing.1", "4")}px;
                padding: {self.get_color("spacing.4", "16")}px;
            }}
        """)
        header_frame.setMaximumHeight(100)
        
        layout = QHBoxLayout(header_frame)
        
        # Title section
        title_layout = QVBoxLayout()
        
        title_label = QLabel("ClassSync AI")
        title_label.setFont(QFont(self.get_color("typography.fontFamily.primary", "Inter"), 18, QFont.Weight.Bold))
        title_label.setStyleSheet(f"color: {text_primary};")
        
        subtitle_label = QLabel("University Timetable Optimization System")
        subtitle_label.setFont(QFont(self.get_color("typography.fontFamily.primary", "Inter"), 10))
        subtitle_label.setStyleSheet(f"color: {text_accent};")
        
        title_layout.addWidget(title_label)
        title_layout.addWidget(subtitle_label)
        
        layout.addLayout(title_layout)
        layout.addStretch()
        
        return header_frame
    
    def create_tabs(self):
        """Create application tabs"""
        # Courses tab
        course_columns = ["Course Name", "Hours per week", "Program", "Section", "Instructor"]
        self.courses_tab = DataEntryTab(
            data_manager=self.data_manager,
            data_type="courses",
            columns=course_columns,
            title="Courses",
            theme=self.theme
        )
        
        # Rooms tab
        room_columns = ["Rooms", "Type"]
        self.rooms_tab = DataEntryTab(
            data_manager=self.data_manager,
            data_type="rooms",
            columns=room_columns,
            title="Rooms",
            theme=self.theme
        )
        
        # Configuration tab
        self.config_tab = ConfigurationTab(self.config_manager, self.theme)
        
        # Add tabs
        self.tab_widget.addTab(self.courses_tab, "Courses")
        self.tab_widget.addTab(self.rooms_tab, "Rooms")
        self.tab_widget.addTab(self.config_tab, "Configuration")
    
    def create_control_panel(self):
        """Create control panel with actions"""
        control_frame = QFrame()
        
        # Get theme colors
        surface_secondary = self.get_color("themes.dark.surface.secondary", "#262626")
        border_default = self.get_color("themes.dark.border.default", "#404040")
        
        control_frame.setStyleSheet(f"""
            QFrame {{
                background-color: {surface_secondary};
                border: 1px solid {border_default};
                border-radius: {self.get_color("borderRadius.md", "8")}px;
                margin: {self.get_color("spacing.1", "4")}px;
                padding: {self.get_color("spacing.3", "12")}px;
            }}
        """)
        
        layout = QVBoxLayout(control_frame)
        layout.setSpacing(self.get_color("spacing.2", "8"))
        
        # Status and progress
        status_layout = QHBoxLayout()
        
        self.status_label = QLabel("Ready")
        self.status_label.setStyleSheet(f"""
            color: {self.get_color("colors.primary.500", "#8d89c7")}; 
            font-weight: {self.get_color("typography.fontWeight.semibold", "600")};
        """)
        
        status_layout.addWidget(self.status_label)
        status_layout.addStretch()
        
        self.progress_bar = QProgressBar()
        self.progress_bar.setVisible(False)
        
        # Get progress bar colors
        bg_primary = self.get_color("themes.dark.background.primary", "#171717")
        primary_500 = self.get_color("colors.primary.500", "#8d89c7")
        border_default = self.get_color("themes.dark.border.default", "#404040")
        text_primary = self.get_color("themes.dark.text.primary", "#fafafa")
        
        self.progress_bar.setStyleSheet(f"""
            QProgressBar {{
                border: 1px solid {border_default};
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                text-align: center;
                background-color: {bg_primary};
                color: {text_primary};
                font-weight: {self.get_color("typography.fontWeight.medium", "500")};
            }}
            QProgressBar::chunk {{
                background-color: {primary_500};
                border-radius: {self.get_color("borderRadius.base", "6")}px;
            }}
        """)
        
        # Console output
        self.console = QTextEdit()
        self.console.setMaximumHeight(80)
        self.console.setReadOnly(True)
        self.console.setVisible(False)
        
        console_bg = self.get_color("themes.dark.background.primary", "#0f0f0f")
        success_color = self.get_color("colors.semantic.success", "#059669")
        
        self.console.setStyleSheet(f"""
            QTextEdit {{
                background-color: {console_bg};
                color: {success_color};
                font-family: {self.get_color("typography.fontFamily.monospace", "monospace")};
                font-size: {self.get_color("typography.fontSize.xs", "12")}px;
                border: 1px solid {border_default};
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                padding: {self.get_color("spacing.2", "8")}px;
            }}
        """)
        
        # Buttons
        button_layout = QHBoxLayout()
        
        self.save_button = QPushButton("Save All Data")
        self.validate_button = QPushButton("Validate Data")
        self.generate_button = QPushButton("Generate Schedule")
        
        # Apply button styles
        self.apply_button_style(self.save_button, "primary")
        self.apply_button_style(self.validate_button, "success")
        self.apply_button_style(self.generate_button, "error")
        
        self.generate_button.setMinimumHeight(40)
        
        button_layout.addWidget(self.save_button)
        button_layout.addWidget(self.validate_button)
        button_layout.addStretch()
        button_layout.addWidget(self.generate_button)
        
        # Add to layout
        layout.addLayout(status_layout)
        layout.addWidget(self.progress_bar)
        layout.addWidget(self.console)
        layout.addLayout(button_layout)
        
        return control_frame
    
    def apply_button_style(self, button, style_type):
        """Apply themed button styles"""
        if style_type == "primary":
            bg_color = self.get_color("colors.primary.500", "#8d89c7")
            hover_color = self.get_color("colors.primary.600", "#755f9c")
            pressed_color = self.get_color("colors.primary.700", "#5d4a7a")
        elif style_type == "success":
            bg_color = self.get_color("colors.semantic.success", "#059669")
            hover_color = "#22c55e"
            pressed_color = "#16a34a"
        elif style_type == "error":
            bg_color = self.get_color("colors.semantic.error", "#dc2626")
            hover_color = "#ef4444"
            pressed_color = "#b91c1c"
        else:
            bg_color = self.get_color("colors.primary.500", "#8d89c7")
            hover_color = self.get_color("colors.primary.600", "#755f9c")
            pressed_color = self.get_color("colors.primary.700", "#5d4a7a")
        
        text_color = self.get_color("themes.dark.text.primary", "#ffffff")
        
        button.setStyleSheet(f"""
            QPushButton {{
                background-color: {bg_color};
                color: {text_color};
                border: none;
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                padding: {self.get_color("spacing.2", "8")}px {self.get_color("spacing.4", "16")}px;
                font-weight: {self.get_color("typography.fontWeight.semibold", "600")};
                font-size: {self.get_color("typography.fontSize.sm", "13")}px;
            }}
            QPushButton:hover {{
                background-color: {hover_color};
            }}
            QPushButton:pressed {{
                background-color: {pressed_color};
            }}
            QPushButton:disabled {{
                background-color: {self.get_color("themes.dark.surface.tertiary", "#404040")};
                color: {self.get_color("themes.dark.text.tertiary", "#a3a3a3")};
            }}
        """)
    
    def setup_statusbar(self):
        """Setup status bar"""
        self.status_bar = QStatusBar()
        self.setStatusBar(self.status_bar)
        
        # Data status indicators
        self.courses_status = QLabel("Courses: Not loaded")
        self.rooms_status = QLabel("Rooms: Not loaded")
        self.config_status = QLabel("Config: Ready")
        
        # Apply status bar styling
        text_secondary = self.get_color("themes.dark.text.secondary", "#d4d4d4")
        
        for label in [self.courses_status, self.rooms_status, self.config_status]:
            label.setStyleSheet(f"color: {text_secondary}; padding: 2px 8px;")
        
        self.status_bar.addWidget(self.courses_status)
        self.status_bar.addWidget(self.rooms_status)
        self.status_bar.addPermanentWidget(self.config_status)
        
        self.status_bar.showMessage("Application initialized")
        
        # Update status periodically
        self.status_timer = QTimer()
        self.status_timer.timeout.connect(self.update_status)
        self.status_timer.start(2000)  # Update every 2 seconds
    
    def setup_connections(self):
        """Setup signal connections"""
        self.save_button.clicked.connect(self.save_all_data)
        self.validate_button.clicked.connect(self.validate_all_data)
        self.generate_button.clicked.connect(self.generate_schedule)
        
        # Tab change handler
        self.tab_widget.currentChanged.connect(self.on_tab_changed)
    
    def update_status(self):
        """Update status indicators"""
        try:
            # Check course data
            if os.path.exists(self.data_manager.courses_file):
                courses_df = self.data_manager.load_courses()
                self.courses_status.setText(f"Courses: {len(courses_df)} loaded")
            else:
                self.courses_status.setText("Courses: No file")
            
            # Check room data
            if os.path.exists(self.data_manager.rooms_file):
                rooms_df = self.data_manager.load_rooms()
                self.rooms_status.setText(f"Rooms: {len(rooms_df)} loaded")
            else:
                self.rooms_status.setText("Rooms: No file")
                
        except Exception:
            pass
    
    def save_all_data(self):
        """Save all data"""
        try:
            success_count = 0
            errors = []
            
            # Save courses
            if self.courses_tab.save_data():
                success_count += 1
            else:
                errors.append("Failed to save courses")
            
            # Save rooms
            if self.rooms_tab.save_data():
                success_count += 1
            else:
                errors.append("Failed to save rooms")
            
            # Save configuration
            if self.config_tab.save_configuration():
                success_count += 1
            else:
                errors.append("Failed to save configuration")
            
            # Show results
            if errors:
                QMessageBox.warning(self, "Save Results", 
                                   f"Saved {success_count}/3 items.\n\nErrors: {'; '.join(errors)}")
            else:
                QMessageBox.information(self, "Success", "All data saved successfully!")
                self.status_bar.showMessage("All data saved", 3000)
                
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Error saving data: {str(e)}")
    
    def validate_all_data(self):
        """Validate all data"""
        try:
            validation_results = []
            
            # Validate courses
            course_valid, course_errors = self.data_manager.validate_courses()
            if course_valid:
                validation_results.append("Courses: Valid")
            else:
                validation_results.append(f"Courses: {'; '.join(course_errors)}")
            
            # Validate rooms
            room_valid, room_errors = self.data_manager.validate_rooms()
            if room_valid:
                validation_results.append("Rooms: Valid")
            else:
                validation_results.append(f"Rooms: {'; '.join(room_errors)}")
            
            # Validate configuration
            config_valid, config_error = self.config_manager.validate_config(self.config_manager.get_config())
            if config_valid:
                validation_results.append("Configuration: Valid")
            else:
                validation_results.append(f"Configuration: {config_error}")
            
            # Show results
            result_text = "\n".join(validation_results)
            if course_valid and room_valid and config_valid:
                QMessageBox.information(self, "Validation Results", f"All data is valid!\n\n{result_text}")
            else:
                QMessageBox.warning(self, "Validation Results", f"Issues found:\n\n{result_text}")
                
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Error during validation: {str(e)}")
    
    def generate_schedule(self):
        """Generate timetable schedule"""
        # Save all data first
        self.save_all_data()
        
        # Validate before proceeding
        try:
            course_valid, course_errors = self.data_manager.validate_courses()
            room_valid, room_errors = self.data_manager.validate_rooms()
            config_valid, config_error = self.config_manager.validate_config(self.config_manager.get_config())
            
            if not (course_valid and room_valid and config_valid):
                error_msg = "Please fix validation errors before generating schedule:\n"
                if not course_valid:
                    error_msg += f"Courses: {'; '.join(course_errors)}\n"
                if not room_valid:
                    error_msg += f"Rooms: {'; '.join(room_errors)}\n"
                if not config_valid:
                    error_msg += f"Configuration: {config_error}\n"
                
                QMessageBox.critical(self, "Validation Failed", error_msg)
                return
            
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Error during validation: {str(e)}")
            return
        
        # Start optimization
        self.start_optimization()
    
    def start_optimization(self):
        """Start optimization process"""
        # Update UI
        self.generate_button.setEnabled(False)
        self.progress_bar.setVisible(True)
        self.console.setVisible(True)
        self.console.clear()
        self.progress_bar.setValue(0)
        self.status_label.setText("Starting optimization...")
        
        # Create and start worker
        self.optimization_worker = OptimizationWorker(self.config_manager, self.data_manager)
        self.optimization_worker.progress_update.connect(self.update_optimization_progress)
        self.optimization_worker.finished.connect(self.optimization_finished)
        self.optimization_worker.start()
    
    def update_optimization_progress(self, progress, message):
        """Update optimization progress"""
        self.progress_bar.setValue(progress)
        self.status_label.setText(message)
        self.console.append(f"[{progress}%] {message}")
        
        # Auto-scroll console
        cursor = self.console.textCursor()
        cursor.movePosition(cursor.MoveOperation.End)
        self.console.setTextCursor(cursor)
    
    def optimization_finished(self, success, message, results):
        """Handle optimization completion"""
        self.generate_button.setEnabled(True)
        
        if success:
            self.status_label.setText("Optimization completed!")
            self.progress_bar.setValue(100)
            
            # Show success message with details
            if results:
                detail_msg = f"""Schedule generated successfully!

Statistics:
- Total Sessions: {len(results['schedule'])}
- Fitness Score: {results['fitness_score']:.0f}
- Files Generated: {len(results['file_paths'])}

Files saved to: output/ directory"""
                
                QMessageBox.information(self, "Success", detail_msg)
                
                # Show summary in console
                self.console.append("\n" + "="*50)
                self.console.append(results['summary_report'])
            else:
                QMessageBox.information(self, "Success", message)
            
            self.status_bar.showMessage("Schedule generation completed", 5000)
            
            # Hide progress after delay
            QTimer.singleShot(3000, lambda: self.progress_bar.setVisible(False))
            QTimer.singleShot(5000, lambda: self.console.setVisible(False))
            
        else:
            self.status_label.setText("Optimization failed")
            self.progress_bar.setVisible(False)
            QMessageBox.critical(self, "Optimization Failed", message)
            
            # Keep console visible to show error details
            self.console.append(f"\nERROR: {message}")
    
    def on_tab_changed(self, index):
        """Handle tab change"""
        tab_names = ["Courses", "Rooms", "Configuration"]
        if 0 <= index < len(tab_names):
            self.status_bar.showMessage(f"Switched to {tab_names[index]} tab", 2000)
    
    def closeEvent(self, event):
        """Handle application close"""
        # Stop worker if running
        if self.optimization_worker and self.optimization_worker.isRunning():
            reply = QMessageBox.question(
                self, "Confirm Exit",
                "Optimization is running. Are you sure you want to exit?",
                QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No,
                QMessageBox.StandardButton.No
            )
            
            if reply == QMessageBox.StandardButton.Yes:
                self.optimization_worker.terminate()
                self.optimization_worker.wait()
                event.accept()
            else:
                event.ignore()
        else:
            event.accept()
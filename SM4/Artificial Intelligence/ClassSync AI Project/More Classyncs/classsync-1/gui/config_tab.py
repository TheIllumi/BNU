"""
Configuration Tab
Clean interface for managing application settings
"""

import os
import json
from PyQt6.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QGridLayout, QPushButton,
    QLabel, QTimeEdit, QSpinBox, QCheckBox, QLineEdit, QGroupBox,
    QComboBox, QScrollArea, QFrame, QMessageBox, QFileDialog
)
from PyQt6.QtCore import QTime, Qt
from PyQt6.QtGui import QFont

class ConfigurationTab(QWidget):
    """Configuration management interface"""
    
    def __init__(self, config_manager, theme=None):
        super().__init__()
        self.config_manager = config_manager
        self.theme = theme or self.load_fallback_theme()
        self.setup_ui()
        self.load_configuration()
    
    def load_fallback_theme(self):
        """Load fallback theme if none provided"""
        return {
            "colors": {
                "primary": {"500": "#8d89c7", "600": "#755f9c", "700": "#5d4a7a"},
                "semantic": {"success": "#059669", "error": "#dc2626"}
            },
            "themes": {
                "dark": {
                    "background": {"primary": "#0f0f0f", "secondary": "#1a1a1a"},
                    "surface": {"primary": "#171717", "secondary": "#262626", "tertiary": "#404040"},
                    "text": {"primary": "#fafafa", "secondary": "#d4d4d4", "accent": "#ffe2db"},
                    "border": {"default": "#404040", "focus": "#d9a7c6"}
                }
            },
            "typography": {"fontFamily": {"primary": "Inter, sans-serif"}, "fontSize": {"base": 14}},
            "borderRadius": {"base": 6, "md": 8},
            "spacing": {"1": 4, "2": 8, "3": 12, "4": 16}
        }
    
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
    
    def setup_ui(self):
        """Setup the user interface"""
        layout = QVBoxLayout()
        layout.setSpacing(self.get_color("spacing.2", "8"))
        
        # Header
        header = self.create_header()
        layout.addWidget(header)
        
        # Scrollable content
        scroll_area = QScrollArea()
        scroll_widget = QWidget()
        scroll_layout = QVBoxLayout(scroll_widget)
        scroll_layout.setSpacing(self.get_color("spacing.3", "12"))
        
        # Configuration groups
        self.create_time_settings_group(scroll_layout)
        self.create_scheduling_rules_group(scroll_layout)
        self.create_genetic_algorithm_group(scroll_layout)
        self.create_output_settings_group(scroll_layout)
        self.create_excel_styling_group(scroll_layout)
        
        scroll_area.setWidget(scroll_widget)
        scroll_area.setWidgetResizable(True)
        
        # Style scroll area
        bg_primary = self.get_color("themes.dark.background.primary", "#0f0f0f")
        border_default = self.get_color("themes.dark.border.default", "#404040")
        
        scroll_area.setStyleSheet(f"""
            QScrollArea {{
                border: none;
                background-color: {bg_primary};
            }}
            QScrollBar:vertical {{
                background-color: {self.get_color("themes.dark.surface.secondary", "#262626")};
                border: 1px solid {border_default};
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                width: 12px;
                margin: 0;
            }}
            QScrollBar::handle:vertical {{
                background-color: {self.get_color("colors.primary.500", "#8d89c7")};
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                min-height: 20px;
                margin: 2px;
            }}
            QScrollBar::handle:vertical:hover {{
                background-color: {self.get_color("colors.primary.600", "#755f9c")};
            }}
            QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {{
                border: none;
                background: none;
            }}
        """)
        
        layout.addWidget(scroll_area)
        self.setLayout(layout)
    
    def create_header(self):
        """Create header with title and action buttons"""
        header_frame = QFrame()
        
        # Get theme colors
        primary_500 = self.get_color("colors.primary.500", "#8d89c7")
        primary_600 = self.get_color("colors.primary.600", "#755f9c")
        text_primary = self.get_color("themes.dark.text.primary", "#fafafa")
        
        header_frame.setStyleSheet(f"""
            QFrame {{
                background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                    stop:0 {primary_500}, stop:1 {primary_600});
                border-radius: {self.get_color("borderRadius.md", "8")}px;
                margin: {self.get_color("spacing.1", "4")}px;
                padding: {self.get_color("spacing.3", "12")}px;
            }}
        """)
        header_frame.setMaximumHeight(80)
        
        layout = QHBoxLayout(header_frame)
        
        # Title
        title_label = QLabel("Configuration Settings")
        title_label.setFont(QFont(self.get_color("typography.fontFamily.primary", "Inter"), 14, QFont.Weight.Bold))
        title_label.setStyleSheet(f"color: {text_primary};")
        
        # Buttons
        button_layout = QHBoxLayout()
        
        self.reset_button = QPushButton("Reset to Defaults")
        self.import_button = QPushButton("Import Config")
        self.export_button = QPushButton("Export Config")
        self.save_button = QPushButton("Save Configuration")
        
        # Apply button styles
        self.apply_button_style(self.reset_button, "error")
        self.apply_button_style(self.import_button, "primary")
        self.apply_button_style(self.export_button, "primary")
        self.apply_button_style(self.save_button, "success")
        
        for button in [self.reset_button, self.import_button, self.export_button, self.save_button]:
            button_layout.addWidget(button)
        
        layout.addWidget(title_label)
        layout.addStretch()
        layout.addLayout(button_layout)
        
        # Connect signals
        self.reset_button.clicked.connect(self.reset_to_defaults)
        self.import_button.clicked.connect(self.import_configuration)
        self.export_button.clicked.connect(self.export_configuration)
        self.save_button.clicked.connect(self.save_configuration)
        
        return header_frame
    
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
                padding: {self.get_color("spacing.2", "8")}px {self.get_color("spacing.3", "12")}px;
                font-weight: {self.get_color("typography.fontWeight.semibold", "600")};
                font-size: {self.get_color("typography.fontSize.sm", "13")}px;
                min-height: 28px;
            }}
            QPushButton:hover {{
                background-color: {hover_color};
            }}
            QPushButton:pressed {{
                background-color: {pressed_color};
            }}
        """)
    
    def create_time_settings_group(self, parent_layout):
        """Create time settings configuration group"""
        group = QGroupBox("Time Settings")
        group.setStyleSheet(self.get_group_style())
        
        layout = QGridLayout()
        layout.setSpacing(self.get_color("spacing.2", "8"))
        
        # Daily start time
        layout.addWidget(self.create_label("Daily Start Time:"), 0, 0)
        self.daily_start_time = QTimeEdit()
        self.daily_start_time.setDisplayFormat("HH:mm")
        self.daily_start_time.setTime(QTime(8, 0))
        self.style_widget(self.daily_start_time)
        layout.addWidget(self.daily_start_time, 0, 1)
        
        # Daily end time
        layout.addWidget(self.create_label("Daily End Time:"), 1, 0)
        self.daily_end_time = QTimeEdit()
        self.daily_end_time.setDisplayFormat("HH:mm")
        self.daily_end_time.setTime(QTime(17, 0))
        self.style_widget(self.daily_end_time)
        layout.addWidget(self.daily_end_time, 1, 1)
        
        # Class duration
        layout.addWidget(self.create_label("Class Duration (minutes):"), 2, 0)
        self.class_duration = QSpinBox()
        self.class_duration.setRange(30, 300)
        self.class_duration.setValue(90)
        self.class_duration.setSuffix(" min")
        self.style_widget(self.class_duration)
        layout.addWidget(self.class_duration, 2, 1)
        
        # Break duration
        layout.addWidget(self.create_label("Break Duration (minutes):"), 3, 0)
        self.break_duration = QSpinBox()
        self.break_duration.setRange(0, 60)
        self.break_duration.setValue(15)
        self.break_duration.setSuffix(" min")
        self.style_widget(self.break_duration)
        layout.addWidget(self.break_duration, 3, 1)
        
        group.setLayout(layout)
        parent_layout.addWidget(group)
    
    def create_scheduling_rules_group(self, parent_layout):
        """Create scheduling rules configuration group"""
        group = QGroupBox("Scheduling Rules")
        group.setStyleSheet(self.get_group_style())
        
        layout = QGridLayout()
        layout.setSpacing(self.get_color("spacing.2", "8"))
        
        # Working days
        layout.addWidget(self.create_label("Working Days:"), 0, 0)
        self.working_days = QLineEdit("Monday,Tuesday,Wednesday,Thursday,Friday")
        self.style_widget(self.working_days)
        layout.addWidget(self.working_days, 0, 1)
        
        # Max classes per day
        layout.addWidget(self.create_label("Max Classes per Day:"), 1, 0)
        self.max_classes_day = QSpinBox()
        self.max_classes_day.setRange(1, 15)
        self.max_classes_day.setValue(4)
        self.style_widget(self.max_classes_day)
        layout.addWidget(self.max_classes_day, 1, 1)
        
        # Max instructor hours per day
        layout.addWidget(self.create_label("Max Instructor Hours per Day:"), 2, 0)
        self.max_instructor_hours = QSpinBox()
        self.max_instructor_hours.setRange(1, 12)
        self.max_instructor_hours.setValue(8)
        self.style_widget(self.max_instructor_hours)
        layout.addWidget(self.max_instructor_hours, 2, 1)
        
        # Evening threshold
        layout.addWidget(self.create_label("Evening Classes Threshold:"), 3, 0)
        self.evening_threshold = QTimeEdit()
        self.evening_threshold.setDisplayFormat("HH:mm")
        self.evening_threshold.setTime(QTime(16, 0))
        self.style_widget(self.evening_threshold)
        layout.addWidget(self.evening_threshold, 3, 1)
        
        # Boolean settings
        self.allow_back_to_back = QCheckBox("Allow Back-to-Back Classes")
        self.allow_mixed_sections = QCheckBox("Allow Mixed Sections")
        self.allow_evening_classes = QCheckBox("Allow Evening Classes")
        
        for checkbox in [self.allow_back_to_back, self.allow_mixed_sections, self.allow_evening_classes]:
            checkbox.setChecked(True)
            self.style_checkbox(checkbox)
        
        layout.addWidget(self.allow_back_to_back, 4, 0, 1, 2)
        layout.addWidget(self.allow_mixed_sections, 5, 0, 1, 2)
        layout.addWidget(self.allow_evening_classes, 6, 0, 1, 2)
        
        group.setLayout(layout)
        parent_layout.addWidget(group)
    
    def create_genetic_algorithm_group(self, parent_layout):
        """Create genetic algorithm configuration group"""
        group = QGroupBox("Genetic Algorithm Settings")
        group.setStyleSheet(self.get_group_style())
        
        layout = QGridLayout()
        layout.setSpacing(self.get_color("spacing.2", "8"))
        
        # Population size
        layout.addWidget(self.create_label("Population Size:"), 0, 0)
        self.population_size = QSpinBox()
        self.population_size.setRange(10, 200)
        self.population_size.setValue(30)
        self.style_widget(self.population_size)
        layout.addWidget(self.population_size, 0, 1)
        
        # Generations
        layout.addWidget(self.create_label("Generations:"), 1, 0)
        self.generations = QSpinBox()
        self.generations.setRange(10, 1000)
        self.generations.setValue(100)
        self.style_widget(self.generations)
        layout.addWidget(self.generations, 1, 1)
        
        # Elite size
        layout.addWidget(self.create_label("Elite Size:"), 2, 0)
        self.elite_size = QSpinBox()
        self.elite_size.setRange(1, 20)
        self.elite_size.setValue(3)
        self.style_widget(self.elite_size)
        layout.addWidget(self.elite_size, 2, 1)
        
        # Mutation rate
        layout.addWidget(self.create_label("Mutation Rate:"), 3, 0)
        self.mutation_rate = QSpinBox()
        self.mutation_rate.setRange(1, 50)
        self.mutation_rate.setValue(15)
        self.mutation_rate.setSuffix("%")
        self.style_widget(self.mutation_rate)
        layout.addWidget(self.mutation_rate, 3, 1)
        
        # Crossover rate
        layout.addWidget(self.create_label("Crossover Rate:"), 4, 0)
        self.crossover_rate = QSpinBox()
        self.crossover_rate.setRange(50, 100)
        self.crossover_rate.setValue(80)
        self.crossover_rate.setSuffix("%")
        self.style_widget(self.crossover_rate)
        layout.addWidget(self.crossover_rate, 4, 1)
        
        # Tournament size
        layout.addWidget(self.create_label("Tournament Size:"), 5, 0)
        self.tournament_size = QSpinBox()
        self.tournament_size.setRange(2, 10)
        self.tournament_size.setValue(3)
        self.style_widget(self.tournament_size)
        layout.addWidget(self.tournament_size, 5, 1)
        
        group.setLayout(layout)
        parent_layout.addWidget(group)
    
    def create_output_settings_group(self, parent_layout):
        """Create output settings configuration group"""
        group = QGroupBox("Output Settings")
        group.setStyleSheet(self.get_group_style())
        
        layout = QGridLayout()
        layout.setSpacing(self.get_color("spacing.2", "8"))
        
        # Boolean settings
        self.generate_excel = QCheckBox("Generate Excel Files")
        self.generate_csv = QCheckBox("Generate CSV Files")
        self.organize_by_categories = QCheckBox("Organize by Categories")
        
        for checkbox in [self.generate_excel, self.generate_csv, self.organize_by_categories]:
            checkbox.setChecked(True)
            self.style_checkbox(checkbox)
        
        layout.addWidget(self.generate_excel, 0, 0, 1, 2)
        layout.addWidget(self.generate_csv, 1, 0, 1, 2)
        layout.addWidget(self.organize_by_categories, 2, 0, 1, 2)
        
        group.setLayout(layout)
        parent_layout.addWidget(group)
    
    def create_excel_styling_group(self, parent_layout):
        """Create Excel styling configuration group"""
        group = QGroupBox("Excel Styling")
        group.setStyleSheet(self.get_group_style())
        
        layout = QGridLayout()
        layout.setSpacing(self.get_color("spacing.2", "8"))
        
        # Theme
        layout.addWidget(self.create_label("Theme:"), 0, 0)
        self.theme_combo = QComboBox()
        self.theme_combo.addItems(["minimal", "colorful", "professional", "modern"])
        self.style_widget(self.theme_combo)
        layout.addWidget(self.theme_combo, 0, 1)
        
        # Font name
        layout.addWidget(self.create_label("Font Name:"), 1, 0)
        self.font_name = QLineEdit("Calibri")
        self.style_widget(self.font_name)
        layout.addWidget(self.font_name, 1, 1)
        
        # Font size
        layout.addWidget(self.create_label("Font Size:"), 2, 0)
        self.font_size = QSpinBox()
        self.font_size.setRange(8, 16)
        self.font_size.setValue(10)
        self.style_widget(self.font_size)
        layout.addWidget(self.font_size, 2, 1)
        
        # Auto adjust columns
        self.auto_adjust_columns = QCheckBox("Auto-adjust Column Widths")
        self.auto_adjust_columns.setChecked(True)
        self.style_checkbox(self.auto_adjust_columns)
        layout.addWidget(self.auto_adjust_columns, 3, 0, 1, 2)
        
        # Auto generate colors
        self.auto_generate_colors = QCheckBox("Auto-generate Course Colors")
        self.auto_generate_colors.setChecked(True)
        self.style_checkbox(self.auto_generate_colors)
        layout.addWidget(self.auto_generate_colors, 4, 0, 1, 2)
        
        group.setLayout(layout)
        parent_layout.addWidget(group)
    
    def create_label(self, text):
        """Create a styled label"""
        label = QLabel(text)
        label.setStyleSheet(f"""
            color: {self.get_color("themes.dark.text.primary", "#fafafa")};
            font-size: {self.get_color("typography.fontSize.sm", "13")}px;
            font-weight: {self.get_color("typography.fontWeight.medium", "500")};
        """)
        return label
    
    def get_group_style(self):
        """Get styling for group boxes"""
        surface_secondary = self.get_color("themes.dark.surface.secondary", "#262626")
        border_default = self.get_color("themes.dark.border.default", "#404040")
        text_primary = self.get_color("themes.dark.text.primary", "#fafafa")
        text_accent = self.get_color("themes.dark.text.accent", "#ffe2db")
        
        return f"""
            QGroupBox {{
                font-weight: {self.get_color("typography.fontWeight.semibold", "600")};
                border: 2px solid {border_default};
                border-radius: {self.get_color("borderRadius.md", "8")}px;
                margin-top: {self.get_color("spacing.3", "12")}px;
                padding-top: {self.get_color("spacing.3", "12")}px;
                color: {text_accent};
                background-color: {surface_secondary};
                font-size: {self.get_color("typography.fontSize.base", "14")}px;
            }}
            QGroupBox::title {{
                subcontrol-origin: margin;
                left: {self.get_color("spacing.3", "12")}px;
                padding: 0 {self.get_color("spacing.2", "8")}px 0 {self.get_color("spacing.2", "8")}px;
                background-color: {surface_secondary};
                color: {text_accent};
                border-radius: {self.get_color("borderRadius.base", "6")}px;
            }}
        """
    
    def style_widget(self, widget):
        """Apply consistent styling to input widgets"""
        surface_primary = self.get_color("themes.dark.surface.primary", "#171717")
        border_default = self.get_color("themes.dark.border.default", "#404040")
        border_focus = self.get_color("themes.dark.border.focus", "#d9a7c6")
        text_primary = self.get_color("themes.dark.text.primary", "#fafafa")
        primary_500 = self.get_color("colors.primary.500", "#8d89c7")
        
        widget.setStyleSheet(f"""
            QWidget {{
                background-color: {surface_primary};
                border: 1px solid {border_default};
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                padding: {self.get_color("spacing.2", "8")}px;
                color: {text_primary};
                font-size: {self.get_color("typography.fontSize.sm", "13")}px;
                min-height: 20px;
            }}
            QWidget:focus {{
                border-color: {border_focus};
                outline: none;
            }}
            QSpinBox::up-button, QSpinBox::down-button {{
                background-color: {primary_500};
                border: none;
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                width: 16px;
                margin: 1px;
            }}
            QSpinBox::up-button:hover, QSpinBox::down-button:hover {{
                background-color: {self.get_color("colors.primary.600", "#755f9c")};
            }}
            QSpinBox::up-arrow, QSpinBox::down-arrow {{
                image: none;
                border-left: 4px solid transparent;
                border-right: 4px solid transparent;
            }}
            QSpinBox::up-arrow {{
                border-bottom: 4px solid {text_primary};
            }}
            QSpinBox::down-arrow {{
                border-top: 4px solid {text_primary};
            }}
            QComboBox::drop-down {{
                border: none;
                background-color: {primary_500};
                border-top-right-radius: {self.get_color("borderRadius.base", "6")}px;
                border-bottom-right-radius: {self.get_color("borderRadius.base", "6")}px;
                width: 20px;
            }}
            QComboBox::drop-down:hover {{
                background-color: {self.get_color("colors.primary.600", "#755f9c")};
            }}
            QComboBox::down-arrow {{
                image: none;
                border-left: 5px solid transparent;
                border-right: 5px solid transparent;
                border-top: 5px solid {text_primary};
                margin: 5px;
            }}
            QComboBox QAbstractItemView {{
                background-color: {surface_primary};
                color: {text_primary};
                border: 1px solid {border_default};
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                selection-background-color: {primary_500};
            }}
            QTimeEdit::up-button, QTimeEdit::down-button {{
                background-color: {primary_500};
                border: none;
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                width: 16px;
                margin: 1px;
            }}
            QTimeEdit::up-button:hover, QTimeEdit::down-button:hover {{
                background-color: {self.get_color("colors.primary.600", "#755f9c")};
            }}
            QTimeEdit::up-arrow, QTimeEdit::down-arrow {{
                image: none;
                border-left: 4px solid transparent;
                border-right: 4px solid transparent;
            }}
            QTimeEdit::up-arrow {{
                border-bottom: 4px solid {text_primary};
            }}
            QTimeEdit::down-arrow {{
                border-top: 4px solid {text_primary};
            }}
        """)
    
    def style_checkbox(self, checkbox):
        """Apply styling to checkboxes"""
        text_primary = self.get_color("themes.dark.text.primary", "#fafafa")
        surface_primary = self.get_color("themes.dark.surface.primary", "#171717")
        border_default = self.get_color("themes.dark.border.default", "#404040")
        border_focus = self.get_color("themes.dark.border.focus", "#d9a7c6")
        primary_500 = self.get_color("colors.primary.500", "#8d89c7")
        
        checkbox.setStyleSheet(f"""
            QCheckBox {{
                color: {text_primary};
                font-size: {self.get_color("typography.fontSize.sm", "13")}px;
                spacing: {self.get_color("spacing.2", "8")}px;
                font-weight: {self.get_color("typography.fontWeight.medium", "500")};
            }}
            QCheckBox::indicator {{
                width: 18px;
                height: 18px;
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                border: 2px solid {border_default};
                background-color: {surface_primary};
            }}
            QCheckBox::indicator:checked {{
                background-color: {primary_500};
                border: 2px solid {primary_500};
                image: none;
            }}
            QCheckBox::indicator:checked::after {{
                content: "✓";
                color: {text_primary};
                font-weight: bold;
                font-size: 12px;
            }}
            QCheckBox::indicator:hover {{
                border-color: {border_focus};
            }}
            QCheckBox::indicator:focus {{
                border-color: {border_focus};
                outline: none;
            }}
        """)
    
    def get_configuration_dict(self):
        """Get current configuration as dictionary"""
        config = {
            "time_settings": {
                "daily_start_time": self.daily_start_time.time().toString("HH:mm"),
                "daily_end_time": self.daily_end_time.time().toString("HH:mm"),
                "class_duration_minutes": self.class_duration.value(),
                "break_duration_minutes": self.break_duration.value()
            },
            "scheduling_rules": {
                "working_days": [day.strip() for day in self.working_days.text().split(",")],
                "max_classes_per_day": self.max_classes_day.value(),
                "max_instructor_hours_per_day": self.max_instructor_hours.value(),
                "allow_back_to_back": self.allow_back_to_back.isChecked(),
                "allow_mixed_sections": self.allow_mixed_sections.isChecked(),
                "allow_evening_classes": self.allow_evening_classes.isChecked(),
                "evening_threshold": self.evening_threshold.time().toString("HH:mm")
            },
            "genetic_algorithm": {
                "population_size": self.population_size.value(),
                "generations": self.generations.value(),
                "elite_size": self.elite_size.value(),
                "mutation_rate": self.mutation_rate.value() / 100.0,
                "crossover_rate": self.crossover_rate.value() / 100.0,
                "tournament_size": self.tournament_size.value()
            },
            "output_settings": {
                "generate_excel": self.generate_excel.isChecked(),
                "generate_csv": self.generate_csv.isChecked(),
                "organize_by_categories": self.organize_by_categories.isChecked(),
                "export_categories": ["section", "teacher", "room", "program"]
            },
            "excel_styling": {
                "theme": self.theme_combo.currentText(),
                "header_color": "4472C4",
                "day_color": "D9E2F3",
                "room_color": "F2F2F2",
                "font_name": self.font_name.text(),
                "font_size": self.font_size.value(),
                "auto_adjust_columns": self.auto_adjust_columns.isChecked()
            },
            "colors": {
                "auto_generate": self.auto_generate_colors.isChecked(),
                "custom_colors": {}
            }
        }
        
        return config
    
    def set_configuration_from_dict(self, config):
        """Set configuration from dictionary"""
        try:
            # Time settings
            time_settings = config.get("time_settings", {})
            if "daily_start_time" in time_settings:
                time_parts = time_settings["daily_start_time"].split(":")
                self.daily_start_time.setTime(QTime(int(time_parts[0]), int(time_parts[1])))
            
            if "daily_end_time" in time_settings:
                time_parts = time_settings["daily_end_time"].split(":")
                self.daily_end_time.setTime(QTime(int(time_parts[0]), int(time_parts[1])))
            
            self.class_duration.setValue(time_settings.get("class_duration_minutes", 90))
            self.break_duration.setValue(time_settings.get("break_duration_minutes", 15))
            
            # Scheduling rules
            scheduling_rules = config.get("scheduling_rules", {})
            working_days = scheduling_rules.get("working_days", ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday"])
            self.working_days.setText(",".join(working_days))
            
            self.max_classes_day.setValue(scheduling_rules.get("max_classes_per_day", 4))
            self.max_instructor_hours.setValue(scheduling_rules.get("max_instructor_hours_per_day", 8))
            self.allow_back_to_back.setChecked(scheduling_rules.get("allow_back_to_back", True))
            self.allow_mixed_sections.setChecked(scheduling_rules.get("allow_mixed_sections", True))
            self.allow_evening_classes.setChecked(scheduling_rules.get("allow_evening_classes", True))
            
            if "evening_threshold" in scheduling_rules:
                time_parts = scheduling_rules["evening_threshold"].split(":")
                self.evening_threshold.setTime(QTime(int(time_parts[0]), int(time_parts[1])))
            
            # Genetic algorithm
            ga_settings = config.get("genetic_algorithm", {})
            self.population_size.setValue(ga_settings.get("population_size", 30))
            self.generations.setValue(ga_settings.get("generations", 100))
            self.elite_size.setValue(ga_settings.get("elite_size", 3))
            self.mutation_rate.setValue(int(ga_settings.get("mutation_rate", 0.15) * 100))
            self.crossover_rate.setValue(int(ga_settings.get("crossover_rate", 0.8) * 100))
            self.tournament_size.setValue(ga_settings.get("tournament_size", 3))
            
            # Output settings
            output_settings = config.get("output_settings", {})
            self.generate_excel.setChecked(output_settings.get("generate_excel", True))
            self.generate_csv.setChecked(output_settings.get("generate_csv", True))
            self.organize_by_categories.setChecked(output_settings.get("organize_by_categories", True))
            
            # Excel styling
            excel_styling = config.get("excel_styling", {})
            theme = excel_styling.get("theme", "minimal")
            index = self.theme_combo.findText(theme)
            if index >= 0:
                self.theme_combo.setCurrentIndex(index)
            
            self.font_name.setText(excel_styling.get("font_name", "Calibri"))
            self.font_size.setValue(excel_styling.get("font_size", 10))
            self.auto_adjust_columns.setChecked(excel_styling.get("auto_adjust_columns", True))
            
            # Colors
            colors = config.get("colors", {})
            self.auto_generate_colors.setChecked(colors.get("auto_generate", True))
            
        except Exception as e:
            QMessageBox.warning(self, "Configuration Error", f"Error loading configuration: {str(e)}")
    
    def load_configuration(self):
        """Load configuration from config manager"""
        try:
            config = self.config_manager.get_config()
            self.set_configuration_from_dict(config)
        except Exception as e:
            QMessageBox.warning(self, "Load Error", f"Failed to load configuration: {str(e)}")
    
    def save_configuration(self):
        """Save current configuration"""
        try:
            config = self.get_configuration_dict()
            
            # Validate configuration
            is_valid, error_msg = self.config_manager.validate_config(config)
            if not is_valid:
                QMessageBox.warning(self, "Validation Error", f"Configuration validation failed:\n{error_msg}")
                return False
            
            # Save configuration
            if self.config_manager.update_config(config):
                QMessageBox.information(self, "Success", "Configuration saved successfully!")
                return True
            else:
                QMessageBox.critical(self, "Error", "Failed to save configuration")
                return False
                
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Error saving configuration: {str(e)}")
            return False
    
    def reset_to_defaults(self):
        """Reset configuration to defaults"""
        reply = QMessageBox.question(
            self, "Confirm Reset",
            "Are you sure you want to reset all settings to defaults?",
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No,
            QMessageBox.StandardButton.No
        )
        
        if reply == QMessageBox.StandardButton.Yes:
            self.config_manager.reset_to_defaults()
            self.load_configuration()
            QMessageBox.information(self, "Reset Complete", "Configuration reset to defaults")
    
    def import_configuration(self):
        """Import configuration from file"""
        file_path, _ = QFileDialog.getOpenFileName(
            self, "Import Configuration", "",
            "JSON Files (*.json);;All Files (*)"
        )
        
        if file_path:
            if self.config_manager.import_config(file_path):
                self.load_configuration()
                QMessageBox.information(self, "Success", "Configuration imported successfully!")
            else:
                QMessageBox.critical(self, "Error", "Failed to import configuration")
    
    def export_configuration(self):
        """Export configuration to file"""
        file_path, _ = QFileDialog.getSaveFileName(
            self, "Export Configuration", "classsync_config.json",
            "JSON Files (*.json);;All Files (*)"
        )
        
        if file_path:
            if self.config_manager.export_config(file_path):
                QMessageBox.information(self, "Success", "Configuration exported successfully!")
            else:
                QMessageBox.critical(self, "Error", "Failed to export configuration")
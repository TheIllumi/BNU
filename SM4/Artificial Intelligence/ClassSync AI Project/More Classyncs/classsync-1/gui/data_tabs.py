"""
Data Entry Tabs
Clean, efficient data entry interface for courses and rooms
"""

import os
import json
import pandas as pd
from PyQt6.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QPushButton, QLabel,
    QTableWidget, QTableWidgetItem, QHeaderView, QMessageBox,
    QAbstractItemView, QComboBox, QFrame, QFileDialog
)
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QFont, QColor

class DataEntryTab(QWidget):
    """Generic data entry tab for courses and rooms"""
    
    def __init__(self, data_manager, data_type, columns, title, theme=None):
        super().__init__()
        self.data_manager = data_manager
        self.data_type = data_type  # "courses" or "rooms"
        self.columns = columns
        self.title = title
        self.theme = theme or self.load_fallback_theme()
        
        # Dropdown options for specific columns
        self.dropdown_options = {
            "Type": ["Theory", "Lab", "Seminar", "Workshop"]
        }
        
        self.setup_ui()
        self.load_data()
    
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
                    "surface": {"primary": "#171717", "secondary": "#262626", "tertiary": "#404040", 
                              "hover": "#3a2d4b", "interactive": "#2d1f3a"},
                    "text": {"primary": "#fafafa", "secondary": "#d4d4d4"},
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
        
        # Header section
        header = self.create_header()
        layout.addWidget(header)
        
        # Table section
        self.table = QTableWidget()
        self.setup_table()
        layout.addWidget(self.table)
        
        self.setLayout(layout)
    
    def create_header(self):
        """Create header with title and action buttons"""
        header_frame = QFrame()
        
        # Get theme colors
        surface_secondary = self.get_color("themes.dark.surface.secondary", "#262626")
        border_default = self.get_color("themes.dark.border.default", "#404040")
        text_primary = self.get_color("themes.dark.text.primary", "#fafafa")
        
        header_frame.setStyleSheet(f"""
            QFrame {{
                background-color: {surface_secondary};
                border: 1px solid {border_default};
                border-radius: {self.get_color("borderRadius.md", "8")}px;
                margin: {self.get_color("spacing.1", "4")}px;
                padding: {self.get_color("spacing.3", "12")}px;
            }}
        """)
        header_frame.setMaximumHeight(80)
        
        layout = QHBoxLayout(header_frame)
        
        # Title
        title_label = QLabel(f"{self.title} Management")
        title_label.setFont(QFont(self.get_color("typography.fontFamily.primary", "Inter"), 14, QFont.Weight.Bold))
        title_label.setStyleSheet(f"color: {text_primary};")
        
        # Buttons
        button_layout = QHBoxLayout()
        
        self.add_button = QPushButton("Add Row")
        self.remove_button = QPushButton("Remove Row")
        self.import_button = QPushButton("Import CSV")
        self.export_button = QPushButton("Export CSV")
        
        # Apply button styles
        self.apply_button_style(self.add_button, "primary")
        self.apply_button_style(self.remove_button, "error")
        self.apply_button_style(self.import_button, "primary")
        self.apply_button_style(self.export_button, "primary")
        
        for button in [self.add_button, self.remove_button, self.import_button, self.export_button]:
            button_layout.addWidget(button)
        
        button_layout.addStretch()
        
        layout.addWidget(title_label)
        layout.addLayout(button_layout)
        
        # Connect signals
        self.add_button.clicked.connect(self.add_row)
        self.remove_button.clicked.connect(self.remove_row)
        self.import_button.clicked.connect(self.import_data)
        self.export_button.clicked.connect(self.export_data)
        
        return header_frame
    
    def apply_button_style(self, button, style_type):
        """Apply themed button styles"""
        if style_type == "primary":
            bg_color = self.get_color("colors.primary.500", "#8d89c7")
            hover_color = self.get_color("colors.primary.600", "#755f9c")
            pressed_color = self.get_color("colors.primary.700", "#5d4a7a")
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
    
    def setup_table(self):
        """Setup the data table"""
        self.table.setColumnCount(len(self.columns))
        self.table.setHorizontalHeaderLabels(self.columns)
        
        # Table properties
        self.table.setAlternatingRowColors(True)
        self.table.setSelectionBehavior(QAbstractItemView.SelectionBehavior.SelectRows)
        self.table.setEditTriggers(QAbstractItemView.EditTrigger.DoubleClicked)
        
        # Header properties
        header = self.table.horizontalHeader()
        header.setSectionResizeMode(QHeaderView.ResizeMode.Stretch)
        
        # Get theme colors
        surface_primary = self.get_color("themes.dark.surface.primary", "#171717")
        surface_secondary = self.get_color("themes.dark.surface.secondary", "#262626")
        surface_hover = self.get_color("themes.dark.surface.hover", "#3a2d4b")
        border_default = self.get_color("themes.dark.border.default", "#404040")
        text_primary = self.get_color("themes.dark.text.primary", "#fafafa")
        primary_500 = self.get_color("colors.primary.500", "#8d89c7")
        
        # Styling
        self.table.setStyleSheet(f"""
            QTableWidget {{
                background-color: {surface_primary};
                alternate-background-color: {surface_secondary};
                gridline-color: {border_default};
                border: 1px solid {border_default};
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                selection-background-color: {primary_500};
                color: {text_primary};
                font-size: {self.get_color("typography.fontSize.sm", "13")}px;
            }}
            QTableWidget::item {{
                padding: {self.get_color("spacing.2", "8")}px;
                border: none;
            }}
            QTableWidget::item:hover {{
                background-color: {surface_hover};
            }}
            QTableWidget::item:selected {{
                background-color: {primary_500};
                color: {text_primary};
            }}
            QHeaderView::section {{
                background-color: {surface_secondary};
                color: {text_primary};
                padding: {self.get_color("spacing.2", "8")}px;
                border: 1px solid {border_default};
                font-weight: {self.get_color("typography.fontWeight.semibold", "600")};
                font-size: {self.get_color("typography.fontSize.sm", "13")}px;
            }}
            QHeaderView::section:horizontal {{
                border-top: none;
                border-left: none;
                border-right: 1px solid {border_default};
                border-bottom: 2px solid {primary_500};
            }}
        """)
    
    def load_data(self):
        """Load data from data manager"""
        try:
            if self.data_type == "courses":
                if os.path.exists(self.data_manager.courses_file):
                    df = self.data_manager.load_courses()
                else:
                    df = pd.DataFrame(columns=self.columns)
            else:  # rooms
                if os.path.exists(self.data_manager.rooms_file):
                    df = self.data_manager.load_rooms()
                else:
                    df = pd.DataFrame(columns=self.columns)
            
            self.populate_table(df)
            
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to load {self.data_type} data: {str(e)}")
    
    def populate_table(self, df):
        """Populate table with DataFrame data"""
        self.table.setRowCount(len(df))
        
        for row_idx, (_, row) in enumerate(df.iterrows()):
            for col_idx, column in enumerate(self.columns):
                value = str(row.get(column, "")) if column in row else ""
                
                # Check if this column should have a dropdown
                if column in self.dropdown_options:
                    combo = QComboBox()
                    combo.addItems(self.dropdown_options[column])
                    if value in self.dropdown_options[column]:
                        combo.setCurrentText(value)
                    
                    self.style_combo_widget(combo)
                    self.table.setCellWidget(row_idx, col_idx, combo)
                else:
                    item = QTableWidgetItem(value)
                    self.table.setItem(row_idx, col_idx, item)
    
    def style_combo_widget(self, combo):
        """Style combo box widgets"""
        surface_primary = self.get_color("themes.dark.surface.primary", "#171717")
        text_primary = self.get_color("themes.dark.text.primary", "#fafafa")
        border_default = self.get_color("themes.dark.border.default", "#404040")
        border_focus = self.get_color("themes.dark.border.focus", "#d9a7c6")
        primary_500 = self.get_color("colors.primary.500", "#8d89c7")
        
        combo.setStyleSheet(f"""
            QComboBox {{
                background-color: {surface_primary};
                color: {text_primary};
                border: 1px solid {border_default};
                border-radius: {self.get_color("borderRadius.base", "6")}px;
                padding: {self.get_color("spacing.1", "4")}px {self.get_color("spacing.2", "8")}px;
                font-size: {self.get_color("typography.fontSize.sm", "13")}px;
                min-height: 20px;
            }}
            QComboBox:focus {{
                border-color: {border_focus};
            }}
            QComboBox::drop-down {{
                border: none;
                background-color: {primary_500};
                border-top-right-radius: {self.get_color("borderRadius.base", "6")}px;
                border-bottom-right-radius: {self.get_color("borderRadius.base", "6")}px;
                width: 20px;
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
        """)
    
    def add_row(self):
        """Add a new empty row"""
        row_count = self.table.rowCount()
        self.table.insertRow(row_count)
        
        # Add dropdown widgets for appropriate columns
        for col_idx, column in enumerate(self.columns):
            if column in self.dropdown_options:
                combo = QComboBox()
                combo.addItems(self.dropdown_options[column])
                self.style_combo_widget(combo)
                self.table.setCellWidget(row_count, col_idx, combo)
            else:
                self.table.setItem(row_count, col_idx, QTableWidgetItem(""))
        
        # Scroll to new row
        self.table.scrollToBottom()
    
    def remove_row(self):
        """Remove selected rows"""
        selected_rows = set(index.row() for index in self.table.selectionModel().selectedRows())
        
        if not selected_rows:
            QMessageBox.information(self, "No Selection", "Please select one or more rows to delete.")
            return
        
        reply = QMessageBox.question(
            self, "Confirm Deletion",
            f"Are you sure you want to delete {len(selected_rows)} row(s)?",
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No,
            QMessageBox.StandardButton.No
        )
        
        if reply == QMessageBox.StandardButton.Yes:
            # Remove rows in reverse order to maintain indices
            for row in sorted(selected_rows, reverse=True):
                self.table.removeRow(row)
    
    def get_table_data(self):
        """Get current table data as DataFrame"""
        data = []
        
        for row in range(self.table.rowCount()):
            row_data = []
            for col in range(self.table.columnCount()):
                # Check if cell has a widget (dropdown)
                widget = self.table.cellWidget(row, col)
                if isinstance(widget, QComboBox):
                    value = widget.currentText()
                else:
                    item = self.table.item(row, col)
                    value = item.text() if item else ""
                
                row_data.append(value.strip())
            
            # Only add non-empty rows
            if any(cell for cell in row_data):
                data.append(row_data)
        
        return pd.DataFrame(data, columns=self.columns)
    
    def save_data(self):
        """Save current table data"""
        try:
            df = self.get_table_data()
            
            # Validate data
            if self.data_type == "courses":
                # Check required fields for courses
                for idx, row in df.iterrows():
                    if not row.get("Course Name", "").strip():
                        QMessageBox.warning(self, "Validation Error", 
                                          f"Row {idx + 1}: Course Name is required")
                        return False
                    if not row.get("Instructor", "").strip():
                        QMessageBox.warning(self, "Validation Error", 
                                          f"Row {idx + 1}: Instructor is required")
                        return False
                
                return self.data_manager.save_courses(df)
            
            else:  # rooms
                # Check required fields for rooms
                for idx, row in df.iterrows():
                    if not row.get("Rooms", "").strip():
                        QMessageBox.warning(self, "Validation Error", 
                                          f"Row {idx + 1}: Room name is required")
                        return False
                
                return self.data_manager.save_rooms(df)
        
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to save {self.data_type} data: {str(e)}")
            return False
    
    def import_data(self):
        """Import data from CSV file"""
        file_path, _ = QFileDialog.getOpenFileName(
            self, f"Import {self.title} Data", "",
            "CSV Files (*.csv);;All Files (*)"
        )
        
        if file_path:
            try:
                # Read CSV file
                df = pd.read_csv(file_path)
                
                # Check if columns match
                missing_columns = [col for col in self.columns if col not in df.columns]
                if missing_columns:
                    reply = QMessageBox.question(
                        self, "Column Mismatch",
                        f"The following columns are missing from the CSV file:\n{', '.join(missing_columns)}\n\nDo you want to continue anyway?",
                        QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No,
                        QMessageBox.StandardButton.No
                    )
                    if reply == QMessageBox.StandardButton.No:
                        return
                    
                    # Add missing columns
                    for col in missing_columns:
                        df[col] = ""
                
                # Reorder columns to match expected order
                df = df.reindex(columns=self.columns, fill_value="")
                
                # Populate table
                self.populate_table(df)
                
                QMessageBox.information(self, "Success", 
                                      f"Data imported successfully from {os.path.basename(file_path)}")
                
            except Exception as e:
                QMessageBox.critical(self, "Import Error", f"Failed to import data: {str(e)}")
    
    def export_data(self):
        """Export current table data to CSV file"""
        file_path, _ = QFileDialog.getSaveFileName(
            self, f"Export {self.title} Data", f"{self.title.lower()}_export.csv",
            "CSV Files (*.csv);;All Files (*)"
        )
        
        if file_path:
            try:
                df = self.get_table_data()
                df.to_csv(file_path, index=False)
                
                QMessageBox.information(self, "Success", 
                                      f"Data exported successfully to {os.path.basename(file_path)}")
                
            except Exception as e:
                QMessageBox.critical(self, "Export Error", f"Failed to export data: {str(e)}")
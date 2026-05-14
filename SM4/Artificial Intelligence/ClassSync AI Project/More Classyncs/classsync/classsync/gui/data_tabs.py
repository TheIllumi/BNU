"""
Data Entry Tabs
Clean, efficient data entry interface for courses and rooms
"""

import os
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
    
    def __init__(self, data_manager, data_type, columns, title):
        super().__init__()
        self.data_manager = data_manager
        self.data_type = data_type  # "courses" or "rooms"
        self.columns = columns
        self.title = title
        
        # Dropdown options for specific columns
        self.dropdown_options = {
            "Type": ["Theory", "Lab", "Seminar", "Workshop"]
        }
        
        self.setup_ui()
        self.load_data()
    
    def setup_ui(self):
        """Setup the user interface"""
        layout = QVBoxLayout()
        
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
        header_frame.setStyleSheet("""
            QFrame {
                background-color: #404040;
                border-radius: 8px;
                margin: 5px;
                padding: 10px;
            }
        """)
        header_frame.setMaximumHeight(80)
        
        layout = QHBoxLayout(header_frame)
        
        # Title
        title_label = QLabel(f"{self.title} Management")
        title_label.setFont(QFont("Arial", 14, QFont.Weight.Bold))
        title_label.setStyleSheet("color: white;")
        
        # Buttons
        button_layout = QHBoxLayout()
        
        self.add_button = QPushButton("Add Row")
        self.remove_button = QPushButton("Remove Row")
        self.import_button = QPushButton("Import CSV")
        self.export_button = QPushButton("Export CSV")
        
        # Style buttons
        button_style = """
            QPushButton {
                background-color: #4472C4;
                color: white;
                border: none;
                border-radius: 4px;
                padding: 6px 12px;
                font-weight: bold;
            }
            QPushButton:hover {
                background-color: #5A84D6;
            }
            QPushButton:pressed {
                background-color: #3A5FB8;
            }
        """
        
        for button in [self.add_button, self.remove_button, self.import_button, self.export_button]:
            button.setStyleSheet(button_style)
            button_layout.addWidget(button)
        
        # Different color for remove button
        self.remove_button.setStyleSheet(button_style.replace("#4472C4", "#DC3545").replace("#5A84D6", "#E55A6A").replace("#3A5FB8", "#C82333"))
        
        button_layout.addStretch()
        
        layout.addWidget(title_label)
        layout.addLayout(button_layout)
        
        # Connect signals
        self.add_button.clicked.connect(self.add_row)
        self.remove_button.clicked.connect(self.remove_row)
        self.import_button.clicked.connect(self.import_data)
        self.export_button.clicked.connect(self.export_data)
        
        return header_frame
    
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
        
        # Styling
        self.table.setStyleSheet("""
            QTableWidget {
                background-color: #353535;
                alternate-background-color: #404040;
                gridline-color: #555555;
                border: 1px solid #555555;
                border-radius: 4px;
                selection-background-color: #4472C4;
            }
            QTableWidget::item {
                padding: 8px;
                border: none;
            }
            QTableWidget::item:selected {
                background-color: #4472C4;
                color: white;
            }
            QHeaderView::section {
                background-color: #2d2d2d;
                color: white;
                padding: 8px;
                border: 1px solid #555555;
                font-weight: bold;
            }
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
                    
                    combo.setStyleSheet("""
                        QComboBox {
                            background-color: #353535;
                            color: white;
                            border: 1px solid #555555;
                            border-radius: 4px;
                            padding: 4px;
                        }
                        QComboBox::drop-down {
                            border: none;
                        }
                        QComboBox::down-arrow {
                            image: none;
                            border-left: 5px solid transparent;
                            border-right: 5px solid transparent;
                            border-top: 5px solid white;
                        }
                    """)
                    
                    self.table.setCellWidget(row_idx, col_idx, combo)
                else:
                    item = QTableWidgetItem(value)
                    self.table.setItem(row_idx, col_idx, item)
    
    def add_row(self):
        """Add a new empty row"""
        row_count = self.table.rowCount()
        self.table.insertRow(row_count)
        
        # Add dropdown widgets for appropriate columns
        for col_idx, column in enumerate(self.columns):
            if column in self.dropdown_options:
                combo = QComboBox()
                combo.addItems(self.dropdown_options[column])
                combo.setStyleSheet("""
                    QComboBox {
                        background-color: #353535;
                        color: white;
                        border: 1px solid #555555;
                        border-radius: 4px;
                        padding: 4px;
                    }
                """)
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
import sys
import os
import csv
import json
import subprocess
from PyQt6.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QTabWidget, QPushButton,
    QHBoxLayout, QLabel, QTableWidget, QTableWidgetItem,
    QHeaderView, QMessageBox, QAbstractItemView, QComboBox,
    QTimeEdit
)
from PyQt6.QtCore import Qt, QTime, QPropertyAnimation, QEasingCurve
from PyQt6.QtGui import QIcon, QColor, QPalette

COURSES_FILE = 'data/Courses_Processed.csv'
ROOMS_FILE = 'data/Rooms.csv'
CONFIG_FILE = 'data/constraints_config.csv'

class EntryTab(QWidget):
    def __init__(self, csv_file, columns, tab_name, dropdown_index=None, dropdown_options=None):
        super().__init__()
        self.csv_file = os.path.join("data", csv_file)
        self.columns = columns
        self.dropdown_index = dropdown_index
        self.dropdown_options = dropdown_options
        self.undo_stack = []

        self.layout = QVBoxLayout()
        self.table = QTableWidget()
        self.table.setColumnCount(len(columns))
        self.table.setHorizontalHeaderLabels(columns)
        self.layout.addWidget(self.table)
        self.setLayout(self.layout)

        self.load_data()
        self.setup_buttons()

    def setup_buttons(self):
        btn_layout = QHBoxLayout()
        add_btn = QPushButton("➕ Add Row")
        remove_btn = QPushButton("🗑 Remove Row")
        undo_btn = QPushButton("↩ Undo Remove")
        add_btn.clicked.connect(self.add_row)
        remove_btn.clicked.connect(self.remove_row)
        undo_btn.clicked.connect(self.undo_remove)
        btn_layout.addWidget(add_btn)
        btn_layout.addWidget(remove_btn)
        btn_layout.addWidget(undo_btn)
        self.layout.insertLayout(0, btn_layout)

    def load_data(self):
        os.makedirs("data", exist_ok=True)
        if not os.path.exists(self.csv_file):
            return
        with open(self.csv_file, newline='', encoding='utf-8') as f:
            reader = csv.reader(f)
            data = list(reader)
        if not data:
            return
        self.table.setRowCount(len(data) - 1)
        for row_idx, row_data in enumerate(data[1:]):
            for col_idx, cell_data in enumerate(row_data):
                self.table.setItem(row_idx, col_idx, QTableWidgetItem(cell_data))
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)
        self.table.setSelectionBehavior(QAbstractItemView.SelectionBehavior.SelectRows)
        self.table.setEditTriggers(QAbstractItemView.EditTrigger.DoubleClicked)

    def add_row(self):
        self.table.insertRow(self.table.rowCount())

    def remove_row(self):
        selected = self.table.selectionModel().selectedRows()
        if not selected:
            return
        confirm = QMessageBox.question(self, "Confirm Deletion", "Are you sure you want to delete the selected row(s)?",
                                       QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No)
        if confirm == QMessageBox.StandardButton.Yes:
            for index in sorted(selected, key=lambda x: x.row(), reverse=True):
                row_data = [self.table.item(index.row(), col).text() if self.table.item(index.row(), col) else '' for col in range(self.table.columnCount())]
                self.undo_stack.append((index.row(), row_data))
                self.table.removeRow(index.row())

    def undo_remove(self):
        if self.undo_stack:
            row_idx, row_data = self.undo_stack.pop()
            self.table.insertRow(row_idx)
            for col_idx, data in enumerate(row_data):
                self.table.setItem(row_idx, col_idx, QTableWidgetItem(data))

    def save_data(self):
        headers = [self.table.horizontalHeaderItem(i).text() for i in range(self.table.columnCount())]
        rows = [[self.table.item(row, col).text() if self.table.item(row, col) else '' for col in range(self.table.columnCount())]
                for row in range(self.table.rowCount())]
        with open(self.csv_file, 'w', newline='', encoding='utf-8') as f:
            writer = csv.writer(f)
            writer.writerow(headers)
            writer.writerows(rows)

class ConfigTab(QWidget):
    def __init__(self):
        super().__init__()
        self.layout = QVBoxLayout()
        self.setLayout(self.layout)

        self.config_options = [
            ("Working Days", "Mon,Tue,Wed,Thu,Fri"),
            ("Max Classes/Day", "4"),
            ("Max Consecutive Classes", "2"),
            ("Min Break Between Classes (min)", "5"),
            ("Preferred Room Gap", "1"),
            ("Allow Back to Back", "True"),
            ("Allow Mixed Sections", "True"),
            ("Class Duration (min)", "60"),
            ("Break Duration (min)", "10"),
            ("Allow Evening Classes", "True"),
            ("Generate Visual Timetable", "True"),
            ("Daily Start Time (e.g. 08:00)", "08:00"),
            ("Daily End Time (e.g. 18:00)", "18:00")
        ]

        self.config_table = QTableWidget(len(self.config_options), 2)
        self.config_table.setHorizontalHeaderLabels(["Option", "Value"])
        self.config_table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)

        self.layout.addWidget(QLabel("Configuration Options"))
        self.layout.addWidget(self.config_table)

        for row, (key, val) in enumerate(self.config_options):
            item_key = QTableWidgetItem(key)
            item_key.setFlags(Qt.ItemFlag.ItemIsEnabled)
            self.config_table.setItem(row, 0, item_key)

            if key.lower().startswith("allow") or key.lower().startswith("generate"):
                combo = QComboBox()
                combo.addItems(["True", "False"])
                combo.setCurrentText(val)
                combo.setMinimumHeight(25)
                self.config_table.setCellWidget(row, 1, combo)

            elif "time" in key.lower():
                time_edit = QTimeEdit()
                time_edit.setDisplayFormat("HH:mm")
                try:
                    hour, minute = map(int, val.split(":"))
                    time_edit.setTime(QTime(hour, minute))
                except:
                    time_edit.setTime(QTime(8, 0))
                time_edit.setMinimumHeight(25)
                self.config_table.setCellWidget(row, 1, time_edit)

            else:
                combo = QComboBox()
                combo.setEditable(True)
                combo.addItem(val)
                combo.setCurrentText(val)
                combo.setMinimumHeight(25)
                self.config_table.setCellWidget(row, 1, combo)

    def get_config_dict(self):
        config_dict = {}
        for row in range(self.config_table.rowCount()):
            key = self.config_table.item(row, 0).text()
            widget = self.config_table.cellWidget(row, 1)
            if isinstance(widget, QComboBox):
                config_dict[key] = widget.currentText()
            elif isinstance(widget, QTimeEdit):
                config_dict[key] = widget.time().toString("HH:mm")
        return config_dict

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("ClassSyncAI - Entry Portal")
        self.setGeometry(200, 200, 1000, 600)
        palette = QPalette()
        palette.setColor(QPalette.ColorRole.Window, QColor(30, 30, 30))
        palette.setColor(QPalette.ColorRole.WindowText, Qt.GlobalColor.white)
        self.setPalette(palette)

        layout = QVBoxLayout()
        self.tabs = QTabWidget()

        course_columns = ["Course Name", "Hours per week", "Program", "Section", "Instructor"]
        self.course_tab = EntryTab("Courses_Processed.csv", course_columns, "Course")

        room_columns = ["Room Name" ,"Type"]
        self.room_tab = EntryTab("Rooms.csv", room_columns, "Room", dropdown_index=1, dropdown_options=["Lab", "Theory"])

        self.config_tab = ConfigTab()

        self.tabs.addTab(self.course_tab, "Courses")
        self.tabs.addTab(self.room_tab, "Rooms")
        self.tabs.addTab(self.config_tab, "Config")

        layout.addWidget(self.tabs)

        self.run_btn = QPushButton("Run ClassSyncAI")
        self.run_btn.setMinimumHeight(30)
        self.run_btn.clicked.connect(self.animate_and_run)
        layout.addWidget(self.run_btn, alignment=Qt.AlignmentFlag.AlignRight)

        self.setLayout(layout)

    def animate_and_run(self):
        animation = QPropertyAnimation(self.run_btn, b"geometry")
        animation.setDuration(300)
        animation.setEasingCurve(QEasingCurve.Type.OutBounce)
        start_geom = self.run_btn.geometry()
        animation.setStartValue(start_geom.adjusted(0, 0, 0, 0))
        animation.setEndValue(start_geom.adjusted(0, -5, 0, 5))
        animation.start()
        self.run_optimizer()

    def run_optimizer(self):
        config_dict = self.config_tab.get_config_dict()
        for key, value in config_dict.items():
            if value == '':
                QMessageBox.critical(self, "Validation Error", f"Value missing for {key}")
                return
        os.makedirs("data", exist_ok=True)
        with open("data/constraints_config.json", "w") as f:
            json.dump(config_dict, f, indent=4)
        try:
            subprocess.run(["python", "enhanced_run_optimizer.py"], check=True)
            subprocess.run(["python", "generate_visual_timetables.py"], check=True)
        except subprocess.CalledProcessError as e:
            QMessageBox.critical(self, "Error", f"Error running optimizer:\n{str(e)}")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setStyle("Fusion")
    window = MainWindow()
    window.show()
    sys.exit(app.exec())

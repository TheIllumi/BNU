# ClassSync AI Setup Guide

## Project Structure

```
classsync/
├── main.py                     # Entry point
├── requirements.txt            # Dependencies
├── SETUP_GUIDE.md             # This file
├── core/                      # Core logic modules
│   ├── __init__.py
│   ├── config_manager.py      # Configuration handling
│   ├── data_manager.py        # Data loading/validation
│   └── optimizer.py           # Genetic algorithm optimizer
├── gui/                       # GUI components
│   ├── __init__.py
│   ├── main_window.py         # Main application window
│   ├── data_tabs.py          # Data entry tabs
│   └── config_tab.py         # Configuration tab
├── output/                    # Output generation
│   ├── __init__.py
│   ├── excel_generator.py     # Excel file creation
│   └── file_organizer.py      # File organization
├── config/                    # Configuration files
│   └── default_config.json    # Default settings
├── data/                      # Input data
│   ├── Courses.csv           # Course data
│   └── Rooms.csv             # Room data
└── output/                   # Generated output files
    ├── by_section/
    ├── by_teacher/
    ├── by_room/
    └── by_program/
```

## Installation Instructions

### 1. Prerequisites

- Python 3.8 or higher
- pip (Python package installer)

### 2. Setup Environment

1. **Navigate to project directory:**

   ```bash
   cd C:\Users\saadm\Downloads\classsync
   ```

2. **Create virtual environment (recommended):**

   ```bash
   python -m venv venv
   ```

3. **Activate virtual environment:**

   - Windows:
     ```bash
     venv\Scripts\activate
     ```
   - macOS/Linux:
     ```bash
     source venv/bin/activate
     ```

### 3. Install Dependencies

```bash
pip install -r requirements.txt
```

### 4. Create Required Directories

The application will create these automatically, but you can create them manually:

```bash
mkdir data config output
mkdir output\by_section output\by_teacher output\by_room output\by_program
```

### 5. Prepare Sample Data

Create sample data files in the `data/` directory:

**data/Courses.csv:**

```csv
Course Name,Hours per week,Program,Section,Instructor
Computer Science 101,3,CS,A,Dr. Smith
Data Structures,3,CS,A,Dr. Johnson
Data Structures Lab,3,CS,A,Dr. Johnson
Mathematics 201,3,Math,A,Prof. Brown
Physics 101,3,Physics,A,Dr. Wilson
Computer Science 101,3,CS,B,Dr. Adams
```

**data/Rooms.csv:**

```csv
Rooms,Type
Room-101,Theory
Room-102,Theory
Room-103,Theory
Lab-A,Lab
Lab-B,Lab
Seminar-Hall,Seminar
```

## Running the Application

### GUI Mode (Recommended)

```bash
python main.py
```

### Features

1. **Data Management:**

   - Add, edit, delete courses and rooms
   - Import/export CSV files
   - Real-time data validation

2. **Configuration:**

   - Time settings (working hours, class duration)
   - Scheduling rules (constraints, preferences)
   - Genetic algorithm parameters
   - Output formatting options

3. **Schedule Generation:**

   - Advanced genetic algorithm optimization
   - Conflict detection and resolution
   - Multiple output formats (Excel, CSV)
   - Organized by categories

4. **Output Organization:**

   - By section, teacher, room, program
   - Master files with all data
   - Summary reports

## Configuration Options

### Basic Settings

- **Working Hours:** 8:00 AM - 5:00 PM (configurable)
- **Class Duration:** 90 minutes (configurable)
- **Working Days:** Monday-Friday (configurable)
- **Max Classes per Day:** 4 (configurable)

### Advanced Settings

- **Population Size:** 30 (10-200)
- **Generations:** 100 (10-1000)
- **Mutation Rate:** 15% (1-50%)
- **Elite Size:** 3 (1-20)

### Output Settings

- **Excel Generation:** Enabled/Disabled
- **CSV Generation:** Enabled/Disabled
- **Category Organization:** Enabled/Disabled
- **Excel Themes:** minimal, colorful, professional, modern

## Troubleshooting

### Common Issues

1. **"No module named 'PyQt6'" Error:**

   ```bash
   pip install PyQt6
   ```

2. **Permission Errors:**

   - Run as administrator (Windows)
   - Check file permissions in project directory

3. **Empty Output:**

   - Verify course and room data is loaded
   - Check configuration settings
   - Ensure data validation passes

4. **Poor Schedule Quality:**

   - Increase population size
   - Increase number of generations
   - Add more rooms
   - Reduce constraints

### Data Validation Errors

- **Missing Required Fields:** Ensure Course Name, Instructor, Section, Program are filled
- **Duplicate Courses:** Check for identical course-section combinations
- **No Rooms Available:** Add at least one room in Rooms.csv

### Performance Optimization

- Reduce population size for faster execution
- Increase population size for better quality
- Use fewer generations for quick testing
- Use more generations for production runs

## File Formats

### Input Files

**Courses.csv columns:**

- Course Name (required)
- Hours per week (optional, default: 3)
- Program (required)
- Section (required)
- Instructor (required)

**Rooms.csv columns:**

- Rooms (required)
- Type (optional: Theory, Lab, Seminar, Workshop)

### Output Files

The application generates:

- `master_timetable.xlsx` - Complete schedule with multiple sheets
- `master_schedule.csv` - Simple CSV format
- Category-specific folders with individual files
- `generation_report.txt` - Summary statistics

## Customization

### Adding New Features

1. **New Constraints:** Modify `core/optimizer.py` fitness function
2. **New Output Formats:** Extend `output/` modules
3. **New GUI Components:** Add to `gui/` modules
4. **New Configuration Options:** Update `core/config_manager.py`

### Color Customization

Edit the configuration to add custom course colors:

```json
{
  "colors": {
    "auto_generate": false,
    "custom_colors": {
      "Computer Science 101": "FF5733",
      "Mathematics 201": "33FF57"
    }
  }
}
```

## Support

For issues or questions:

1. Check the troubleshooting section
2. Verify your data format matches the examples
3. Review error messages in the application console
4. Check configuration settings

## Version History

- **v3.0:** Complete rewrite with modular architecture
- **v2.0:** GUI improvements and enhanced features
- **v1.0:** Initial command-line version

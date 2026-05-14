# 🚀 ClassSync Visual - Complete Setup Guide

This guide will walk you through setting up ClassSync Visual from scratch, whether you're an end user or developer.

## 🎯 For End Users (Quick Start)

### Option 1: Download Executable (Recommended)

1. Download `ClassSync_Visual.exe` from releases
2. Double-click to run - no installation needed!
3. Start converting your ClassSync CSV files

### Option 2: Run from Source

If you prefer to run from source code, follow the developer setup below.

---

## 👨‍💻 For Developers (Complete Setup)

### Prerequisites

- **Python 3.8 or later** ([Download here](https://python.org/))
- **Git** (optional, for cloning)
- **VS Code** (recommended editor)

### Step 1: Get the Code

**Option A: Download ZIP**

1. Download this repository as ZIP
2. Extract to `classsync-visual` folder

**Option B: Clone with Git**

```bash
git clone <repository-url>
cd classsync-visual
```

### Step 2: Quick Setup (Windows)

Run the automated setup:

```bash
# Run this in the project folder
setup.bat
```

This will:

- ✅ Create virtual environment
- ✅ Install all dependencies
- ✅ Set up configuration
- ✅ Prepare for development

### Step 3: Manual Setup (All Platforms)

If the batch file doesn't work, follow these manual steps:

```bash
# 1. Create virtual environment
python -m venv venv

# 2. Activate virtual environment
# Windows:
venv\Scripts\activate
# Mac/Linux:
source venv/bin/activate

# 3. Upgrade pip
python -m pip install --upgrade pip

# 4. Install dependencies
pip install -r requirements.txt

# 5. Create config directory
mkdir config  # if it doesn't exist
```

### Step 4: Verify Setup

Test your installation:

```bash
# Run test suite
python test_app.py

# If all tests pass, run the app
python app.py
```

### Step 5: VS Code Setup (Recommended)

1. **Open project in VS Code**
   ```bash
   code .
   ```
2. **Install Python extension**
   - Go to Extensions (Ctrl+Shift+X)
   - Search "Python" and install Microsoft's Python extension
3. **Select Python interpreter**
   - Press `Ctrl+Shift+P`
   - Type "Python: Select Interpreter"
   - Choose `./venv/Scripts/python.exe`
4. **Configure workspace** (optional)
   Create `.vscode/settings.json`:
   ```json
   {
     "python.interpreter": "./venv/Scripts/python.exe",
     "python.linting.enabled": true,
     "python.formatting.provider": "black"
   }
   ```

---

## 🔨 Building Executable

### Quick Build (Windows)

```bash
# Run automated build
build.bat
```

### Manual Build (All Platforms)

```bash
# Install PyInstaller
pip install pyinstaller

# Build executable
pyinstaller build.spec

# Find executable in dist/ folder
```

### Build Customization

Edit `build.spec` to customize:

- **Icon** : Add `icon='path/to/icon.ico'`
- **Name** : Change `name='Your_App_Name'`
- **Console** : Set `console=True` for debugging

---

## 📁 Project Structure Explained

```
classsync-visual/
├── 🎯 app.py                    # Main entry point - run this
├── 📦 requirements.txt          # Dependencies list
├── 🔧 build.spec               # Executable build config
├── 🧪 test_app.py              # Test suite
├── ⚡ setup.bat                # Windows setup script
├── 🚀 build.bat                # Windows build script
│
├── 🎨 ui/                      # User Interface
│   ├── main_window.py          # Main app window
│   ├── config_window.py        # Settings window
│   └── components.py           # Dialogs and widgets
│
├── ⚙️ utils/                   # Core Logic
│   ├── config_manager.py       # Settings management
│   ├── processor.py            # CSV processing
│   ├── excel_generator.py      # Excel creation
│   └── analytics.py            # Statistics & conflicts
│
└── 📋 config/                  # Configuration
    └── default_config.json     # Default settings
```

---

## 🐛 Troubleshooting

### Common Issues & Solutions

#### ❌ "Python not found"

**Solution:** Install Python 3.8+ from [python.org](https://python.org/) and add to PATH

#### ❌ "Virtual environment creation failed"

**Solutions:**

```bash
# Try with different Python command
python3 -m venv venv
# Or
py -m venv venv
```

#### ❌ "Package installation failed"

**Solutions:**

```bash
# Upgrade pip first
python -m pip install --upgrade pip

# Install with verbose output
pip install -r requirements.txt -v

# Install packages individually
pip install pandas openpyxl
```

#### ❌ "tkinterdnd2 not available"

**Solution:** This is optional - drag & drop will be disabled but app will work

```bash
# Try installing manually
pip install tkinterdnd2
```

#### ❌ "Import errors when running"

**Solutions:**

1. Make sure virtual environment is activated
2. Run from project root directory
3. Check Python path: `python -c "import sys; print(sys.path)"`

#### ❌ "Build fails with PyInstaller"

**Solutions:**

```bash
# Clear build cache
rmdir /s build dist
# Try building with different options
pyinstaller --onefile --windowed app.py
```

### Getting Help

1. **Run test suite** : `python test_app.py`
2. **Check console output** for detailed error messages
3. **Verify file structure** matches the guide above
4. **Test with sample CSV** (create a simple test file)

---

## 📚 Usage Guide

### 1. Prepare Your CSV Files

Ensure your ClassSync CSV files have these columns:

- `Course_Name`, `Instructor`, `Section`, `Program`
- `Weekday`, `Start_Time`, `End_Time`, `Room`

### 2. Launch Application

```bash
# From source
python app.py

# Or run executable
ClassSync_Visual.exe
```

### 3. Process Files

1. **Drag & Drop** CSV files (or use Browse button)
2. **Choose output folder** (optional)
3. **Click "Generate Timetables"**
4. **View results** with analytics

### 4. Customize Settings

- Click **⚙️ Settings** to configure:
  - Time slots and duration
  - Colors and fonts
  - Export options
  - Analytics preferences

---

## 🎉 You're Ready!

Your ClassSync Visual application is now set up and ready to use. Start by:

1. **Testing** with a sample CSV file
2. **Exploring** the settings to customize output
3. **Generating** your first professional timetable
4. **Analyzing** conflicts and utilization statistics

**Happy scheduling! 🎯**

---

## 📞 Support

- **Documentation** : See README.md for detailed feature information
- **Issues** : Check troubleshooting section above
- **Testing** : Run `python test_app.py` to validate setup

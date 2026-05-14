@echo off
echo 🎯 ClassSync Visual - Development Setup
echo ======================================

:: Check Python installation
python --version >nul 2>&1
if errorlevel 1 (
    echo ❌ Python is not installed or not in PATH!
    echo Please install Python 3.8+ from https://python.org
    pause
    exit /b 1
)

echo ✅ Python found: 
python --version

:: Create virtual environment
echo 📦 Creating virtual environment...
python -m venv venv

:: Activate virtual environment
echo 🔧 Activating virtual environment...
call venv\Scripts\activate.bat

:: Upgrade pip
echo ⬆️ Upgrading pip...
python -m pip install --upgrade pip

:: Install requirements
echo 📥 Installing requirements...
pip install -r requirements.txt

:: Create config directory if it doesn't exist
if not exist "config\" mkdir config

:: Copy default config if it doesn't exist
if not exist "config\default_config.json" (
    echo 📋 Creating default configuration...
    copy /y "config\default_config.json" "config\default_config.json" >nul 2>&1
)

echo.
echo ✅ Setup complete!
echo.
echo 🚀 To run the application:
echo    1. Run: python app.py
echo.
echo 🔨 To build executable:
echo    1. Run: build.bat
echo.
echo 💡 Development tips:
echo    - Use VS Code with Python extension
echo    - Activate virtual environment: venv\Scripts\activate.bat
echo    - Install new packages: pip install package_name
echo.
pause
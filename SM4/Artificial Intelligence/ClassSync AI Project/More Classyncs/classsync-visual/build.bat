@echo off
echo 🎯 ClassSync Visual - Build Script
echo ================================

:: Check if virtual environment exists
if not exist "venv\" (
    echo ❌ Virtual environment not found!
    echo Please run setup.bat first.
    pause
    exit /b 1
)

:: Activate virtual environment
echo 📦 Activating virtual environment...
call venv\Scripts\activate.bat

:: Check if PyInstaller is installed
python -c "import PyInstaller" 2>nul
if errorlevel 1 (
    echo 📥 Installing PyInstaller...
    pip install pyinstaller
)

:: Clean previous build
echo 🧹 Cleaning previous build...
if exist "build\" rmdir /s /q "build"
if exist "dist\" rmdir /s /q "dist"

:: Build executable
echo 🚀 Building ClassSync Visual executable...
pyinstaller build.spec

:: Check if build was successful
if exist "dist\ClassSync_Visual.exe" (
    echo ✅ Build successful!
    echo 📁 Executable created: dist\ClassSync_Visual.exe
    echo.
    echo 🎉 Ready to distribute!
    echo.
    pause
) else (
    echo ❌ Build failed!
    echo Check the output above for errors.
    pause
    exit /b 1
)
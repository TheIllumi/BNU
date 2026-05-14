#!/usr/bin/env python3
"""
Test script for ClassSync Visual
Helps validate the application setup and core functionality
"""

import sys
import os
import traceback
from pathlib import Path

def test_imports():
    """Test all critical imports"""
    print("🧪 Testing imports...")
    
    try:
        import tkinter as tk
        print("✅ tkinter - OK")
    except ImportError as e:
        print(f"❌ tkinter - FAILED: {e}")
        return False
    
    try:
        import pandas as pd
        print("✅ pandas - OK")
    except ImportError as e:
        print(f"❌ pandas - FAILED: {e}")
        return False
    
    try:
        import openpyxl
        print("✅ openpyxl - OK")
    except ImportError as e:
        print(f"❌ openpyxl - FAILED: {e}")
        return False
    
    try:
        from tkinterdnd2 import TkinterDnD
        print("✅ tkinterdnd2 - OK (Drag & Drop available)")
    except ImportError:
        print("⚠️ tkinterdnd2 - Not available (Drag & Drop disabled)")
    
    return True

def test_project_structure():
    """Test project structure"""
    print("\n📁 Testing project structure...")
    
    required_files = [
        "app.py",
        "requirements.txt",
        "build.spec",
        "ui/__init__.py",
        "ui/main_window.py",
        "ui/config_window.py",
        "ui/components.py",
        "utils/__init__.py",
        "utils/config_manager.py",
        "utils/processor.py",
        "utils/excel_generator.py",
        "utils/analytics.py",
        "config/default_config.json"
    ]
    
    all_present = True
    for file_path in required_files:
        if Path(file_path).exists():
            print(f"✅ {file_path}")
        else:
            print(f"❌ {file_path} - MISSING")
            all_present = False
    
    return all_present

def test_config_manager():
    """Test configuration manager"""
    print("\n⚙️ Testing configuration manager...")
    
    try:
        from utils.config_manager import ConfigManager
        
        config = ConfigManager()
        
        # Test basic functionality
        start_time = config.get('time_slots.start')
        if start_time:
            print(f"✅ Config loading - OK (start_time: {start_time})")
        else:
            print("❌ Config loading - FAILED")
            return False
        
        # Test time slots generation
        time_slots = config.get_time_slots()
        if time_slots and len(time_slots) > 0:
            print(f"✅ Time slots generation - OK ({len(time_slots)} slots)")
        else:
            print("❌ Time slots generation - FAILED")
            return False
        
        # Test color generation
        color = config.get_color_for_course("Test Course")
        if color and color.startswith('FF'):
            print(f"✅ Color generation - OK ({color})")
        else:
            print("❌ Color generation - FAILED")
            return False
            
        return True
        
    except Exception as e:
        print(f"❌ Configuration manager - FAILED: {e}")
        traceback.print_exc()
        return False

def test_csv_processor():
    """Test CSV processor with sample data"""
    print("\n📊 Testing CSV processor...")
    
    try:
        from utils.config_manager import ConfigManager
        from utils.processor import TimetableProcessor
        
        config = ConfigManager()
        processor = TimetableProcessor(config)
        
        # Create sample CSV data
        sample_csv = """Course_Name,Instructor,Section,Program,Weekday,Start_Time,End_Time,Room
Mathematics 101,Dr. Smith,A,Computer Science,Monday,09:00,10:30,Room 101
Physics 201,Prof. Johnson,B,Engineering,Monday,11:00,12:30,Lab 201
Chemistry 301,Dr. Brown,C,Science,Tuesday,14:00,15:30,Lab 301"""
        
        # Write sample CSV
        test_csv_path = Path("test_sample.csv")
        with open(test_csv_path, 'w', encoding='utf-8') as f:
            f.write(sample_csv)
        
        # Load and validate
        df = processor.load_csv(str(test_csv_path))
        if df is not None and len(df) == 3:
            print("✅ CSV loading - OK")
        else:
            print("❌ CSV loading - FAILED")
            return False
        
        # Validate format
        validation = processor.validate_csv(df, str(test_csv_path))
        if validation['valid']:
            print("✅ CSV validation - OK")
        else:
            print(f"❌ CSV validation - FAILED: {validation['error']}")
            return False
        
        # Create grid
        time_slots = config.get_time_slots()
        grid = processor.create_timetable_grid(df, time_slots)
        if grid and 'Monday' in grid:
            print("✅ Grid creation - OK")
        else:
            print("❌ Grid creation - FAILED")
            return False
        
        # Clean up
        test_csv_path.unlink()
        
        return True
        
    except Exception as e:
        print(f"❌ CSV processor - FAILED: {e}")
        traceback.print_exc()
        return False

def test_excel_generator():
    """Test Excel generator"""
    print("\n📈 Testing Excel generator...")
    
    try:
        from utils.config_manager import ConfigManager
        from utils.excel_generator import ExcelGenerator
        
        config = ConfigManager()
        generator = ExcelGenerator(config)
        
        # Test style setup
        generator.setup_styles()
        if hasattr(generator, 'border') and hasattr(generator, 'header_fill'):
            print("✅ Style setup - OK")
        else:
            print("❌ Style setup - FAILED")
            return False
        
        print("✅ Excel generator - OK")
        return True
        
    except Exception as e:
        print(f"❌ Excel generator - FAILED: {e}")
        traceback.print_exc()
        return False

def test_ui_components():
    """Test UI components can be imported"""
    print("\n🖥️ Testing UI components...")
    
    try:
        from ui.main_window import MainWindow
        from ui.config_window import ConfigWindow
        from ui.components import ProgressDialog, ResultsDialog
        
        print("✅ UI imports - OK")
        return True
        
    except Exception as e:
        print(f"❌ UI components - FAILED: {e}")
        traceback.print_exc()
        return False

def run_all_tests():
    """Run all tests"""
    print("🎯 ClassSync Visual - Test Suite")
    print("=" * 40)
    
    tests = [
        ("Imports", test_imports),
        ("Project Structure", test_project_structure),
        ("Configuration Manager", test_config_manager),
        ("CSV Processor", test_csv_processor),
        ("Excel Generator", test_excel_generator),
        ("UI Components", test_ui_components)
    ]
    
    passed = 0
    total = len(tests)
    
    for test_name, test_func in tests:
        try:
            if test_func():
                passed += 1
        except Exception as e:
            print(f"❌ {test_name} - EXCEPTION: {e}")
    
    print(f"\n📊 Test Results: {passed}/{total} tests passed")
    
    if passed == total:
        print("🎉 All tests passed! Application should work correctly.")
        return True
    else:
        print("⚠️ Some tests failed. Please check the issues above.")
        return False

if __name__ == "__main__":
    success = run_all_tests()
    
    if not success:
        print("\n💡 Troubleshooting tips:")
        print("- Make sure virtual environment is activated")
        print("- Run: pip install -r requirements.txt")
        print("- Check Python version (3.8+ required)")
        print("- Verify all files are present")
    
    input("\nPress Enter to exit...")
    sys.exit(0 if success else 1)
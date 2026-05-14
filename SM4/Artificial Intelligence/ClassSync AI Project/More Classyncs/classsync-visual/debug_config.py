#!/usr/bin/env python3
"""
Debug script to check configuration issues
"""

import json
import os
from pathlib import Path

def check_config():
    """Check configuration setup"""
    print("🔍 ClassSync Visual - Configuration Debug")
    print("=" * 50)
    
    # Check if config directory exists
    config_dir = Path("config")
    if not config_dir.exists():
        print("❌ Config directory doesn't exist. Creating it...")
        config_dir.mkdir()
    else:
        print("✅ Config directory exists")
    
    # Check default config file
    default_config_path = config_dir / "default_config.json"
    if not default_config_path.exists():
        print("❌ Default config file missing. Creating it...")
        create_default_config(default_config_path)
    else:
        print("✅ Default config file exists")
        
        # Validate default config
        try:
            with open(default_config_path, 'r', encoding='utf-8') as f:
                config = json.load(f)
            
            # Check for required sections
            required_sections = ['time_slots', 'styling', 'export_options', 'app_settings', 'colors', 'watermark']
            for section in required_sections:
                if section in config:
                    print(f"✅ Config section '{section}' found")
                else:
                    print(f"❌ Config section '{section}' missing")
            
            # Check styling subsections
            if 'styling' in config:
                styling = config['styling']
                required_styling = ['header_color', 'day_color', 'room_color', 'font_name', 'font_size', 'border_style']
                for item in required_styling:
                    if item in styling:
                        print(f"✅ Styling '{item}': {styling[item]}")
                    else:
                        print(f"❌ Styling '{item}' missing")
            
        except json.JSONDecodeError as e:
            print(f"❌ Invalid JSON in config file: {e}")
        except Exception as e:
            print(f"❌ Error reading config: {e}")
    
    # Test config manager
    try:
        print("\n🧪 Testing ConfigManager...")
        from utils.config_manager import ConfigManager
        
        # Show what the ConfigManager's default config contains
        config_manager = ConfigManager()
        default_config = config_manager._get_default_config()
        default_styling = default_config.get('styling', {})
        print(f"📋 ConfigManager default styling has {len(default_styling)} items:")
        for key, value in default_styling.items():
            print(f"   - {key}: {value}")
        
        if 'border_style' not in default_styling:
            print("❌ border_style is MISSING from ConfigManager default config!")
        else:
            print("✅ border_style is present in ConfigManager default config")
        
        print(f"\n🔍 ConfigManager loaded config:")
        # Test basic access
        start_time = config_manager.get('time_slots.start')
        print(f"✅ start_time: {start_time}")
        
        border_style = config_manager.get('styling.border_style')
        print(f"⚠️ border_style: {border_style}")
        
        header_color = config_manager.get('styling.header_color')
        print(f"✅ header_color: {header_color}")
        
        # Test styling section
        styling = config_manager.get('styling')
        print(f"✅ styling section: {type(styling)} with {len(styling) if styling else 0} items")
        
        if styling:
            print("   Current styling contents:")
            for key, value in styling.items():
                print(f"   - {key}: {value}")
        
    except Exception as e:
        print(f"❌ ConfigManager test failed: {e}")
        import traceback
        traceback.print_exc()

def create_default_config(config_path):
    """Create default configuration file"""
    default_config = {
        "time_slots": {
            "start": "08:00",
            "end": "17:00",
            "slot_minutes": 90
        },
        "styling": {
            "header_color": "FF4472C4",
            "day_color": "FFD9E2F3",
            "room_color": "FFF2F2F2",
            "font_name": "Calibri",
            "font_size": 10,
            "header_font_size": 12,
            "auto_adjust_columns": True,
            "border_style": "thin"
        },
        "export_options": {
            "include_empty_days": False,
            "merge_day_cells": True,
            "show_instructor": True,
            "show_program": True,
            "compact_mode": False
        },
        "app_settings": {
            "remember_last_folder": True,
            "auto_open_output": True,
            "show_analytics": True,
            "check_conflicts": True
        },
        "colors": {
            "Mathematics": "FFE74C3C",
            "Physics": "FF3498DB",
            "Chemistry": "FF2ECC71",
            "Biology": "FF9B59B6",
            "Computer Science": "FF1ABC9C",
            "Engineering": "FFF39C12",
            "English": "FF34495E",
            "History": "FFAD4A28"
        },
        "watermark": {
            "text": "Generated by ClassSync Visual",
            "show": True,
            "position": "bottom-right",
            "font": "Arial",
            "fontsize": 10,
            "color": "FF808080"
        }
    }
    
    try:
        with open(config_path, 'w', encoding='utf-8') as f:
            json.dump(default_config, f, indent=2, ensure_ascii=False)
        print(f"✅ Created default config at {config_path}")
    except Exception as e:
        print(f"❌ Failed to create default config: {e}")

if __name__ == "__main__":
    check_config()
    input("\nPress Enter to exit...")
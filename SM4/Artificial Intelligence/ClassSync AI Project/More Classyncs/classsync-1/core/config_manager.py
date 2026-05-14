"""
Configuration Manager
Handles loading, saving, and validation of application configuration
"""

import json
import os
from typing import Dict, Any, Tuple
from datetime import time

class ConfigManager:
    def __init__(self):
        self.config_dir = "config"
        self.default_config_file = os.path.join(self.config_dir, "default_config.json")
        self.user_config_file = os.path.join(self.config_dir, "user_config.json")
        self.config = self._load_config()
    
    def _get_default_config(self) -> Dict[str, Any]:
        """Return default configuration"""
        return {
            "time_settings": {
                "daily_start_time": "08:00",
                "daily_end_time": "17:00",
                "class_duration_minutes": 90,
                "break_duration_minutes": 15
            },
            "scheduling_rules": {
                "working_days": ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday"],
                "max_classes_per_day": 4,
                "max_instructor_hours_per_day": 8,
                "allow_back_to_back": True,
                "allow_mixed_sections": True,
                "allow_evening_classes": True,
                "evening_threshold": "16:00"
            },
            "genetic_algorithm": {
                "population_size": 30,
                "generations": 100,
                "elite_size": 3,
                "mutation_rate": 0.15,
                "crossover_rate": 0.8,
                "tournament_size": 3
            },
            "output_settings": {
                "generate_excel": True,
                "generate_csv": True,
                "organize_by_categories": True,
                "export_categories": ["section", "teacher", "room", "program"]
            },
            "excel_styling": {
                "theme": "minimal",
                "header_color": "4472C4",
                "day_color": "D9E2F3",
                "room_color": "F2F2F2",
                "font_name": "Calibri",
                "font_size": 10,
                "auto_adjust_columns": True
            },
            "colors": {
                "auto_generate": True,
                "custom_colors": {}
            }
        }
    
    def _load_config(self) -> Dict[str, Any]:
        """Load configuration from files"""
        # Create config directory if it doesn't exist
        os.makedirs(self.config_dir, exist_ok=True)
        
        # Load default config
        default_config = self._get_default_config()
        
        # Save default config if it doesn't exist
        if not os.path.exists(self.default_config_file):
            self._save_json(default_config, self.default_config_file)
        
        # Load user config if it exists, otherwise use default
        if os.path.exists(self.user_config_file):
            try:
                user_config = self._load_json(self.user_config_file)
                # Merge with default config to ensure all keys exist
                return self._merge_configs(default_config, user_config)
            except Exception:
                # If user config is corrupted, use default
                return default_config
        else:
            return default_config
    
    def _load_json(self, filepath: str) -> Dict[str, Any]:
        """Load JSON file"""
        with open(filepath, 'r', encoding='utf-8') as f:
            return json.load(f)
    
    def _save_json(self, data: Dict[str, Any], filepath: str) -> None:
        """Save JSON file"""
        with open(filepath, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=4, ensure_ascii=False)
    
    def _merge_configs(self, default: Dict[str, Any], user: Dict[str, Any]) -> Dict[str, Any]:
        """Recursively merge user config with default config"""
        result = default.copy()
        
        for key, value in user.items():
            if key in result and isinstance(result[key], dict) and isinstance(value, dict):
                result[key] = self._merge_configs(result[key], value)
            else:
                result[key] = value
        
        return result
    
    def get_config(self) -> Dict[str, Any]:
        """Get current configuration"""
        return self.config.copy()
    
    def update_config(self, new_config: Dict[str, Any]) -> bool:
        """Update configuration"""
        try:
            # Validate config before updating
            is_valid, error_msg = self.validate_config(new_config)
            if not is_valid:
                raise ValueError(error_msg)
            
            self.config = new_config
            self._save_json(self.config, self.user_config_file)
            return True
        except Exception:
            return False
    
    def validate_config(self, config: Dict[str, Any]) -> Tuple[bool, str]:
        """Validate configuration"""
        errors = []
        
        try:
            # Validate time settings
            time_settings = config.get("time_settings", {})
            start_time = self._parse_time(time_settings.get("daily_start_time", "08:00"))
            end_time = self._parse_time(time_settings.get("daily_end_time", "17:00"))
            
            if start_time >= end_time:
                errors.append("Daily start time must be before end time")
            
            class_duration = time_settings.get("class_duration_minutes", 90)
            if not isinstance(class_duration, int) or class_duration < 30 or class_duration > 300:
                errors.append("Class duration must be between 30 and 300 minutes")
            
            # Validate scheduling rules
            scheduling_rules = config.get("scheduling_rules", {})
            working_days = scheduling_rules.get("working_days", [])
            if not working_days:
                errors.append("At least one working day must be specified")
            
            max_classes = scheduling_rules.get("max_classes_per_day", 4)
            if not isinstance(max_classes, int) or max_classes < 1 or max_classes > 10:
                errors.append("Max classes per day must be between 1 and 10")
            
            # Validate GA settings
            ga_settings = config.get("genetic_algorithm", {})
            population_size = ga_settings.get("population_size", 30)
            if not isinstance(population_size, int) or population_size < 10 or population_size > 200:
                errors.append("Population size must be between 10 and 200")
            
            generations = ga_settings.get("generations", 100)
            if not isinstance(generations, int) or generations < 10 or generations > 1000:
                errors.append("Generations must be between 10 and 1000")
            
        except Exception as e:
            errors.append(f"Configuration validation error: {str(e)}")
        
        return len(errors) == 0, "; ".join(errors)
    
    def _parse_time(self, time_str: str) -> time:
        """Parse time string to time object"""
        try:
            hours, minutes = time_str.split(":")
            return time(int(hours), int(minutes))
        except Exception:
            raise ValueError(f"Invalid time format: {time_str}")
    
    def reset_to_defaults(self) -> None:
        """Reset configuration to defaults"""
        self.config = self._get_default_config()
        if os.path.exists(self.user_config_file):
            os.remove(self.user_config_file)
    
    def export_config(self, filepath: str) -> bool:
        """Export current configuration to file"""
        try:
            self._save_json(self.config, filepath)
            return True
        except Exception:
            return False
    
    def import_config(self, filepath: str) -> bool:
        """Import configuration from file"""
        try:
            imported_config = self._load_json(filepath)
            return self.update_config(imported_config)
        except Exception:
            return False
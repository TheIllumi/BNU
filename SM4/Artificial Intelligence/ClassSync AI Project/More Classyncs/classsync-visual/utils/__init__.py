"""
Utils package for ClassSync Visual
Contains core processing logic and utilities
"""

__version__ = "1.0.0"
__author__ = "ClassSync Visual Team"

from .config_manager import ConfigManager
from .processor import TimetableProcessor
from .excel_generator import ExcelGenerator
from .analytics import AnalyticsEngine

__all__ = [
    'ConfigManager',
    'TimetableProcessor',
    'ExcelGenerator',
    'AnalyticsEngine'
]
"""
UI package for ClassSync Visual
Contains all user interface components and windows
"""

__version__ = "1.0.0"
__author__ = "ClassSync Visual Team"

from .main_window import MainWindow
from .config_window import ConfigWindow
from .components import ProgressDialog, ResultsDialog

__all__ = [
    'MainWindow',
    'ConfigWindow', 
    'ProgressDialog',
    'ResultsDialog'
]
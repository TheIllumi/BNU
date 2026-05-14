@echo off
REM ==============================
REM Create ClassSync Project Structure
REM ==============================

mkdir classsync
cd classsync

REM --- Top-level files ---
echo. > main.py
echo. > requirements.txt

REM --- Core folder ---
mkdir core
echo. > core\__init__.py
echo. > core\config_manager.py
echo. > core\data_manager.py
echo. > core\optimizer.py

REM --- GUI folder ---
mkdir gui
echo. > gui\__init__.py
echo. > gui\main_window.py
echo. > gui\data_tabs.py
echo. > gui\config_tab.py

REM --- Output folder ---
mkdir output
echo. > output\__init__.py
echo. > output\excel_generator.py
echo. > output\file_organizer.py

REM --- Config folder ---
mkdir config
echo {^
    "max_generations": 100,^
    "population_size": 50,^
    "elitism_rate": 0.1,^
    "mutation_rate": 0.05^
} > config\default_config.json

REM --- Data folder ---
mkdir data

echo Project structure created successfully!

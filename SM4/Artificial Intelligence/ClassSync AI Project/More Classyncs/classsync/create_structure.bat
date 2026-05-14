@echo off
REM Create folders
mkdir classsync
cd classsync

mkdir core
mkdir gui
mkdir output
mkdir data
mkdir config

REM Create Python package markers
echo. > core\__init__.py
echo. > gui\__init__.py
echo. > output\__init__.py

REM Create main entry point
echo. > main.py

REM Core files
echo. > core\optimizer.py
echo. > core\data_manager.py
echo. > core\config_manager.py

REM GUI files
echo. > gui\main_window.py
echo. > gui\data_tabs.py
echo. > gui\config_tab.py

REM Output files
echo. > output\excel_generator.py
echo. > output\file_organizer.py

REM Data CSVs
echo. > data\Courses.csv
echo. > data\Rooms.csv

REM Config file
echo. > config\default_config.json

REM Requirements
echo. > requirements.txt

echo Project structure created successfully!

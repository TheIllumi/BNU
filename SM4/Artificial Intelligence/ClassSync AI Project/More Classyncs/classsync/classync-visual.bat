mkdir classsync-visual
cd classsync-visual

:: Top-level files
type nul > app.py
type nul > requirements.txt
type nul > build.spec
type nul > setup.bat
type nul > build.bat
type nul > test_app.py
type nul > README.md
type nul > SETUP_GUIDE.md

:: UI folder
mkdir ui
cd ui
type nul > __init__.py
type nul > main_window.py
type nul > config_window.py
type nul > components.py
cd ..

:: Utils folder
mkdir utils
cd utils
type nul > __init__.py
type nul > config_manager.py
type nul > processor.py
type nul > excel_generator.py
type nul > analytics.py
cd ..

:: Config folder
mkdir config
cd config
type nul > default_config.json
cd ..

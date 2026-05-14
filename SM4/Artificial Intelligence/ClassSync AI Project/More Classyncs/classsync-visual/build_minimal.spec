# Minimal build spec for ClassSync Visual
# Use this if the main build is too slow

import os
from pathlib import Path

project_root = Path.cwd()

# Only essential data files
datas = [
    (str(project_root / 'config' / 'default_config.json'), 'config'),
]

# Only essential imports - FIXED with numpy
hiddenimports = [
    'tkinter',
    'tkinter.ttk',
    'tkinter.filedialog',
    'tkinter.messagebox',
    'pandas',
    'numpy',  # REQUIRED for pandas
    'openpyxl',
    'openpyxl.styles',
    'openpyxl.utils'
]

a = Analysis(
    ['app.py'],
    pathex=[str(project_root)],
    binaries=[],
    datas=datas,
    hiddenimports=hiddenimports,
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=[
        'matplotlib', 'scipy', 'IPython', 'jupyter', 'notebook',
        'PIL', 'Pillow', 'setuptools', 'distutils', 'unittest', 'test',
        'pytest', 'nose', 'wheel', 'pip', 'multiprocessing', 'asyncio',
        'email', 'html', 'http', 'urllib3', 'requests', 'sqlite3', 'xml'
    ],
    win_no_prefer_redirects=False,
    win_private_assemblies=False,
    cipher=None,
    noarchive=False,
)

pyz = PYZ(a.pure, a.zipped_data, cipher=None)

# Directory build (faster)
exe = EXE(
    pyz,
    a.scripts,
    [],
    exclude_binaries=True,
    name='ClassSync_Visual_Minimal',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=False,  # No compression for speed
    console=True,  # Show console for debugging
    icon=str(project_root / 'logo_visual.ico'),
)

coll = COLLECT(
    exe,
    a.binaries,
    a.zipfiles,
    a.datas,
    strip=False,
    upx=False,
    name='ClassSync_Visual_Minimal'
)
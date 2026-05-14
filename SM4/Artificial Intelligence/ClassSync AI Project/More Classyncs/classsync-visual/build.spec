# -*- mode: python ; coding: utf-8 -*-

import os
from pathlib import Path

# Get the current directory
project_root = Path.cwd()

# Data files to include
datas = [
    (str(project_root / 'config' / 'default_config.json'), 'config'),
]

# Hidden imports that PyInstaller might miss
hiddenimports = [
    'tkinter',
    'tkinter.ttk',
    'tkinter.filedialog',
    'tkinter.messagebox',
    'tkinter.scrolledtext',
    'pandas',
    'openpyxl',
    'openpyxl.styles',
    'openpyxl.utils',
    'openpyxl.worksheet.dimensions',
    'datetime',
    'pathlib',
    'json',
    'threading',
    'webbrowser',
    'hashlib',
    'collections',
    'traceback'
]

# Try to include tkinterdnd2 if available
try:
    import tkinterdnd2
    hiddenimports.append('tkinterdnd2')
    datas.append((tkinterdnd2.__path__[0], 'tkinterdnd2'))
except ImportError:
    pass

block_cipher = None

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
        'matplotlib',
        'numpy',
        'scipy',
        'IPython',
        'jupyter',
        'notebook',
        'PIL', 'Pillow',
        'setuptools',
        'distutils',
        'unittest',
        'test',
        'tests',
        'pytest',
        'nose',
        'wheel',
        'pip',
        'pydoc',
        'doctest',
        'argparse',
        'optparse',
        'multiprocessing',
        'concurrent.futures',
        'asyncio',
        'email',
        'html',
        'http',
        'urllib3',
        'requests',
        'sqlite3',
        'xml',
        'xmlrpc',
        'ftplib',
        'smtplib',
        'telnetlib'
    ],
    win_no_prefer_redirects=False,
    win_private_assemblies=False,
    cipher=block_cipher,
    noarchive=False,
)

pyz = PYZ(a.pure, a.zipped_data, cipher=block_cipher)

exe = EXE(
    pyz,
    a.scripts,
    [],  # Empty - for directory build
    exclude_binaries=True,  # This makes it MUCH faster
    name='ClassSync_Visual',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=False,  # Disable UPX compression for speed
    upx_exclude=[],
    runtime_tmpdir=None,
    console=True,  # ENABLE THIS to see what's happening
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
    icon=str(project_root / 'logo_visual.ico'),
    version_file=None
)

coll = COLLECT(
    exe,
    a.binaries,
    a.zipfiles,
    a.datas,
    strip=False,
    upx=False,  # Disable UPX for speed
    upx_exclude=[],
    name='ClassSync_Visual'
)
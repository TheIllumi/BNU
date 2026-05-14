# Comprehensive build - includes everything needed
import os
from pathlib import Path

project_root = Path.cwd()

datas = [
    (str(project_root / 'config' / 'default_config.json'), 'config'),
]

# Let PyInstaller auto-detect most modules, only exclude what we definitely don't need
excludes = [
    'matplotlib', 'scipy', 'IPython', 'jupyter', 'notebook', 'pytest', 
    'nose', 'wheel', 'setuptools', 'distutils'
]

a = Analysis(
    ['app.py'],
    pathex=[str(project_root)],
    binaries=[],
    datas=datas,
    hiddenimports=[],  # Let PyInstaller auto-detect
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=excludes,  # Only exclude what we're sure we don't need
    win_no_prefer_redirects=False,
    win_private_assemblies=False,
    cipher=None,
    noarchive=False,
)

pyz = PYZ(a.pure, a.zipped_data, cipher=None)

exe = EXE(
    pyz,
    a.scripts,
    [],
    exclude_binaries=True,
    name='ClassSync_Visual_Complete',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=False,
    console=False,  # Change to True if you need to see errors
    icon=str(project_root / 'logo_visual.ico'),
)

coll = COLLECT(
    exe,
    a.binaries,
    a.zipfiles,
    a.datas,
    strip=False,
    upx=False,
    name='ClassSync_Visual_Complete'
)
#!/usr/bin/env python3
"""
Diagnose PyInstaller build issues
"""

import sys
import os
import subprocess
from pathlib import Path

def diagnose_build():
    print("🔍 ClassSync Visual - Build Diagnosis")
    print("=" * 50)
    
    # Check if exe exists
    exe_paths = [
        Path("dist/ClassSync_Visual.exe"),
        Path("dist/ClassSync_Visual/ClassSync_Visual.exe")
    ]
    
    exe_found = None
    for exe_path in exe_paths:
        if exe_path.exists():
            exe_found = exe_path
            print(f"✅ Found executable: {exe_path}")
            break
    
    if not exe_found:
        print("❌ No executable found!")
        print("   Run: pyinstaller build.spec")
        return
    
    # Check file size
    size_mb = exe_found.stat().st_size / (1024 * 1024)
    print(f"📊 Executable size: {size_mb:.1f} MB")
    
    if size_mb > 200:
        print("⚠️  Large file size might cause slow startup")
    
    # Try to run with timeout
    print(f"\n🚀 Testing executable startup...")
    try:
        # Run with 30 second timeout
        result = subprocess.run(
            [str(exe_found), "--help"], 
            capture_output=True, 
            text=True, 
            timeout=30
        )
        
        if result.returncode == 0:
            print("✅ Executable starts successfully")
        else:
            print(f"❌ Executable failed with code: {result.returncode}")
            if result.stderr:
                print(f"Error: {result.stderr}")
    
    except subprocess.TimeoutExpired:
        print("❌ Executable timed out (>30 seconds)")
        print("   This indicates a startup performance issue")
    
    except Exception as e:
        print(f"❌ Could not test executable: {e}")
    
    # Suggest solutions
    print(f"\n💡 Suggested fixes:")
    print("1. Use directory build (faster):")
    print("   pyinstaller build_minimal.spec")
    print("\n2. Enable console mode to see errors:")
    print("   Edit build.spec: console=True")
    print("\n3. Check antivirus software")
    print("4. Run from SSD (not network drive)")

if __name__ == "__main__":
    diagnose_build()
    input("\nPress Enter to exit...")
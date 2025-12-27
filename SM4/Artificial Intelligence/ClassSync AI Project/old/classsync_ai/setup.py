"""
Setup script for ClassSync AI package.

This script allows installation of ClassSync AI as a Python package
and handles dependency management.
"""

from setuptools import setup, find_packages
from pathlib import Path

# Read README for long description
readme_file = Path(__file__).parent / "README.md"
long_description = ""
if readme_file.exists():
    long_description = readme_file.read_text(encoding="utf-8")

# Read requirements
requirements_file = Path(__file__).parent / "requirements.txt"
requirements = []
if requirements_file.exists():
    requirements = [
        line.strip() 
        for line in requirements_file.read_text().split('\n')
        if line.strip() and not line.startswith('#')
    ]

setup(
    name="classsync-ai",
    version="2.0.0",
    author="Your Name",
    author_email="your.email@example.com",
    description="AI-powered university timetable scheduling system",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/yourusername/classsync-ai",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    classifiers=[
        "Development Status :: 4 - Beta",
        "Intended Audience :: Education",
        "Topic :: Education",
        "Topic :: Scientific/Engineering :: Artificial Intelligence",
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
    ],
    python_requires=">=3.8",
    install_requires=requirements,
    extras_require={
        "dev": [
            "pytest>=7.3.0",
            "pytest-cov>=4.1.0",
            "black>=23.3.0",
            "flake8>=6.0.0",
            "mypy>=1.3.0",
            "pre-commit>=3.3.0",
        ],
        "ui": [
            "PyQt6>=6.5.0",
            "PyQt6-Qt6>=6.5.0",
        ],
        "web": [
            "fastapi>=0.100.0",
            "uvicorn>=0.22.0",
        ],
    },
    entry_points={
        "console_scripts": [
            "classsync=app:main",
            "classsync-gui=ui.desktop_app:main",
        ],
    },
    include_package_data=True,
    package_data={
        "": ["*.yaml", "*.json", "*.md"],
    },
    zip_safe=False,
)
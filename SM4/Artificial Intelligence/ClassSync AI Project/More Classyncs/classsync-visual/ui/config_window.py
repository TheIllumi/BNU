"""
Configuration Window for ClassSync Visual
User interface for modifying application settings
"""

import tkinter as tk
from tkinter import ttk, messagebox, colorchooser
from datetime import datetime

class ConfigWindow:
    """Configuration window for application settings"""
    
    def __init__(self, parent, config_manager):
        self.parent = parent
        self.config_manager = config_manager
        self.modified = False
        
        # Store original values for cancel functionality
        self.original_config = dict(config_manager.config)
        
        self.setup_window()
        self.create_widgets()
        self.load_current_values()
        self.show()
    
    def setup_window(self):
        """Setup configuration window"""
        self.window = tk.Toplevel(self.parent)
        self.window.title("Settings - ClassSync Visual")
        self.window.geometry("600x700")
        self.window.resizable(False, False)
        self.window.transient(self.parent)
        self.window.grab_set()
        
        # Center window
        self.center_window()
        
        # Handle window closing
        self.window.protocol("WM_DELETE_WINDOW", self.on_closing)
    
    def center_window(self):
        """Center window on parent"""
        self.window.update_idletasks()
        
        parent_x = self.parent.winfo_x()
        parent_y = self.parent.winfo_y()
        parent_width = self.parent.winfo_width()
        parent_height = self.parent.winfo_height()
        
        window_width = self.window.winfo_width()
        window_height = self.window.winfo_height()
        
        x = parent_x + (parent_width - window_width) // 2
        y = parent_y + (parent_height - window_height) // 2
        
        self.window.geometry(f"+{x}+{y}")
    
    def create_widgets(self):
        """Create and layout widgets"""
        # Main container with scrollable content
        canvas = tk.Canvas(self.window)
        scrollbar = ttk.Scrollbar(self.window, orient="vertical", command=canvas.yview)
        scrollable_frame = ttk.Frame(canvas)
        
        scrollable_frame.bind(
            "<Configure>",
            lambda e: canvas.configure(scrollregion=canvas.bbox("all"))
        )
        
        canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)
        
        # Pack scrollable components
        canvas.pack(side="left", fill="both", expand=True, padx=10, pady=10)
        scrollbar.pack(side="right", fill="y")
        
        # Create notebook for different setting categories
        self.notebook = ttk.Notebook(scrollable_frame)
        self.notebook.pack(fill="both", expand=True)
        
        # Create setting tabs
        self.create_time_settings_tab()
        self.create_appearance_tab()
        self.create_export_options_tab()
        self.create_app_settings_tab()
        
        # Buttons frame
        self.create_buttons(scrollable_frame)
    
    def create_time_settings_tab(self):
        """Create time settings tab"""
        time_frame = ttk.Frame(self.notebook)
        self.notebook.add(time_frame, text="⏰ Time Settings")
        
        # Time slots section
        time_group = ttk.LabelFrame(time_frame, text="Time Slot Configuration")
        time_group.pack(fill="x", padx=10, pady=10)
        
        # Start time
        ttk.Label(time_group, text="Start Time:").grid(row=0, column=0, sticky="w", padx=5, pady=5)
        self.start_time_var = tk.StringVar()
        self.start_time_entry = ttk.Entry(time_group, textvariable=self.start_time_var, width=10)
        self.start_time_entry.grid(row=0, column=1, padx=5, pady=5)
        ttk.Label(time_group, text="(HH:MM format)").grid(row=0, column=2, sticky="w", padx=5)
        
        # End time
        ttk.Label(time_group, text="End Time:").grid(row=1, column=0, sticky="w", padx=5, pady=5)
        self.end_time_var = tk.StringVar()
        self.end_time_entry = ttk.Entry(time_group, textvariable=self.end_time_var, width=10)
        self.end_time_entry.grid(row=1, column=1, padx=5, pady=5)
        ttk.Label(time_group, text="(HH:MM format)").grid(row=1, column=2, sticky="w", padx=5)
        
        # Slot duration
        ttk.Label(time_group, text="Slot Duration:").grid(row=2, column=0, sticky="w", padx=5, pady=5)
        self.slot_duration_var = tk.StringVar()
        duration_combo = ttk.Combobox(
            time_group,
            textvariable=self.slot_duration_var,
            values=["30", "45", "60", "90", "120"],
            width=8,
            state="readonly"
        )
        duration_combo.grid(row=2, column=1, padx=5, pady=5)
        ttk.Label(time_group, text="minutes").grid(row=2, column=2, sticky="w", padx=5)
        
        # Preview section
        preview_group = ttk.LabelFrame(time_frame, text="Time Slots Preview")
        preview_group.pack(fill="both", expand=True, padx=10, pady=10)
        
        self.time_preview_text = tk.Text(
            preview_group,
            height=8,
            width=50,
            state=tk.DISABLED,
            font=("Consolas", 9)
        )
        self.time_preview_text.pack(fill="both", expand=True, padx=5, pady=5)
        
        # Update preview button
        ttk.Button(
            time_frame,
            text="🔄 Update Preview",
            command=self.update_time_preview
        ).pack(pady=10)
        
        # Bind changes to auto-update preview
        self.start_time_var.trace('w', lambda *args: self.update_time_preview())
        self.end_time_var.trace('w', lambda *args: self.update_time_preview())
        self.slot_duration_var.trace('w', lambda *args: self.update_time_preview())
    
    def create_appearance_tab(self):
        """Create appearance settings tab"""
        appearance_frame = ttk.Frame(self.notebook)
        self.notebook.add(appearance_frame, text="🎨 Appearance")
        
        # Color settings
        color_group = ttk.LabelFrame(appearance_frame, text="Color Settings")
        color_group.pack(fill="x", padx=10, pady=10)
        
        # Header color
        ttk.Label(color_group, text="Header Color:").grid(row=0, column=0, sticky="w", padx=5, pady=5)
        self.header_color_var = tk.StringVar()
        header_color_frame = ttk.Frame(color_group)
        header_color_frame.grid(row=0, column=1, padx=5, pady=5)
        
        self.header_color_button = tk.Button(
            header_color_frame,
            text="   ",
            width=3,
            command=lambda: self.choose_color("header_color", self.header_color_var, self.header_color_button)
        )
        self.header_color_button.pack(side="left")
        
        ttk.Entry(header_color_frame, textvariable=self.header_color_var, width=10).pack(side="left", padx=5)
        
        # Day color
        ttk.Label(color_group, text="Day Color:").grid(row=1, column=0, sticky="w", padx=5, pady=5)
        self.day_color_var = tk.StringVar()
        day_color_frame = ttk.Frame(color_group)
        day_color_frame.grid(row=1, column=1, padx=5, pady=5)
        
        self.day_color_button = tk.Button(
            day_color_frame,
            text="   ",
            width=3,
            command=lambda: self.choose_color("day_color", self.day_color_var, self.day_color_button)
        )
        self.day_color_button.pack(side="left")
        
        ttk.Entry(day_color_frame, textvariable=self.day_color_var, width=10).pack(side="left", padx=5)
        
        # Room color
        ttk.Label(color_group, text="Room Color:").grid(row=2, column=0, sticky="w", padx=5, pady=5)
        self.room_color_var = tk.StringVar()
        room_color_frame = ttk.Frame(color_group)
        room_color_frame.grid(row=2, column=1, padx=5, pady=5)
        
        self.room_color_button = tk.Button(
            room_color_frame,
            text="   ",
            width=3,
            command=lambda: self.choose_color("room_color", self.room_color_var, self.room_color_button)
        )
        self.room_color_button.pack(side="left")
        
        ttk.Entry(room_color_frame, textvariable=self.room_color_var, width=10).pack(side="left", padx=5)
        
        # Font settings
        font_group = ttk.LabelFrame(appearance_frame, text="Font Settings")
        font_group.pack(fill="x", padx=10, pady=10)
        
        # Font name
        ttk.Label(font_group, text="Font Name:").grid(row=0, column=0, sticky="w", padx=5, pady=5)
        self.font_name_var = tk.StringVar()
        font_combo = ttk.Combobox(
            font_group,
            textvariable=self.font_name_var,
            values=["Calibri", "Arial", "Times New Roman", "Segoe UI", "Tahoma"],
            width=15,
            state="readonly"
        )
        font_combo.grid(row=0, column=1, padx=5, pady=5)
        
        # Font size
        ttk.Label(font_group, text="Font Size:").grid(row=1, column=0, sticky="w", padx=5, pady=5)
        self.font_size_var = tk.StringVar()
        size_combo = ttk.Combobox(
            font_group,
            textvariable=self.font_size_var,
            values=["8", "9", "10", "11", "12", "14"],
            width=8,
            state="readonly"
        )
        size_combo.grid(row=1, column=1, padx=5, pady=5)
        
        # Auto adjust columns
        self.auto_adjust_var = tk.BooleanVar()
        ttk.Checkbutton(
            font_group,
            text="Auto-adjust column widths",
            variable=self.auto_adjust_var
        ).grid(row=2, column=0, columnspan=2, sticky="w", padx=5, pady=5)
    
    def create_export_options_tab(self):
        """Create export options tab"""
        export_frame = ttk.Frame(self.notebook)
        self.notebook.add(export_frame, text="📋 Export Options")
        
        # Content options
        content_group = ttk.LabelFrame(export_frame, text="Content Options")
        content_group.pack(fill="x", padx=10, pady=10)
        
        self.include_empty_days_var = tk.BooleanVar()
        ttk.Checkbutton(
            content_group,
            text="Include empty days in timetable",
            variable=self.include_empty_days_var
        ).pack(anchor="w", padx=5, pady=2)
        
        self.merge_day_cells_var = tk.BooleanVar()
        ttk.Checkbutton(
            content_group,
            text="Merge day cells when multiple rooms",
            variable=self.merge_day_cells_var
        ).pack(anchor="w", padx=5, pady=2)
        
        self.show_instructor_var = tk.BooleanVar()
        ttk.Checkbutton(
            content_group,
            text="Show instructor names",
            variable=self.show_instructor_var
        ).pack(anchor="w", padx=5, pady=2)
        
        self.show_program_var = tk.BooleanVar()
        ttk.Checkbutton(
            content_group,
            text="Show program information",
            variable=self.show_program_var
        ).pack(anchor="w", padx=5, pady=2)
        
        self.compact_mode_var = tk.BooleanVar()
        ttk.Checkbutton(
            content_group,
            text="Compact mode (course name and section only)",
            variable=self.compact_mode_var
        ).pack(anchor="w", padx=5, pady=2)
        
        # Watermark options
        watermark_group = ttk.LabelFrame(export_frame, text="Watermark Options")
        watermark_group.pack(fill="x", padx=10, pady=10)
        
        self.show_watermark_var = tk.BooleanVar()
        ttk.Checkbutton(
            watermark_group,
            text="Show watermark",
            variable=self.show_watermark_var
        ).pack(anchor="w", padx=5, pady=2)
        
        ttk.Label(watermark_group, text="Watermark Text:").pack(anchor="w", padx=5)
        self.watermark_text_var = tk.StringVar()
        ttk.Entry(
            watermark_group,
            textvariable=self.watermark_text_var,
            width=40
        ).pack(anchor="w", padx=5, pady=2)
        
        ttk.Label(watermark_group, text="Position:").pack(anchor="w", padx=5, pady=(10, 0))
        self.watermark_position_var = tk.StringVar()
        position_frame = ttk.Frame(watermark_group)
        position_frame.pack(anchor="w", padx=5, pady=2)
        
        ttk.Radiobutton(
            position_frame,
            text="Top Header",
            variable=self.watermark_position_var,
            value="top-header"
        ).pack(side="left")
        
        ttk.Radiobutton(
            position_frame,
            text="Bottom Right",
            variable=self.watermark_position_var,
            value="bottom-right"
        ).pack(side="left", padx=(20, 0))
    
    def create_app_settings_tab(self):
        """Create application settings tab"""
        app_frame = ttk.Frame(self.notebook)
        self.notebook.add(app_frame, text="⚙️ App Settings")
        
        # Behavior settings
        behavior_group = ttk.LabelFrame(app_frame, text="Application Behavior")
        behavior_group.pack(fill="x", padx=10, pady=10)
        
        self.remember_folder_var = tk.BooleanVar()
        ttk.Checkbutton(
            behavior_group,
            text="Remember last used folder",
            variable=self.remember_folder_var
        ).pack(anchor="w", padx=5, pady=2)
        
        self.auto_open_output_var = tk.BooleanVar()
        ttk.Checkbutton(
            behavior_group,
            text="Automatically open output folder after processing",
            variable=self.auto_open_output_var
        ).pack(anchor="w", padx=5, pady=2)
        
        self.show_analytics_var = tk.BooleanVar()
        ttk.Checkbutton(
            behavior_group,
            text="Show analytics and statistics",
            variable=self.show_analytics_var
        ).pack(anchor="w", padx=5, pady=2)
        
        self.check_conflicts_var = tk.BooleanVar()
        ttk.Checkbutton(
            behavior_group,
            text="Check for scheduling conflicts",
            variable=self.check_conflicts_var
        ).pack(anchor="w", padx=5, pady=2)
        
        # Reset settings
        reset_group = ttk.LabelFrame(app_frame, text="Reset Settings")
        reset_group.pack(fill="x", padx=10, pady=10)
        
        ttk.Label(
            reset_group,
            text="Reset all settings to default values:"
        ).pack(anchor="w", padx=5, pady=2)
        
        ttk.Button(
            reset_group,
            text="🔄 Reset to Defaults",
            command=self.reset_to_defaults
        ).pack(anchor="w", padx=5, pady=5)
    
    def create_buttons(self, parent):
        """Create bottom buttons"""
        button_frame = ttk.Frame(parent)
        button_frame.pack(fill="x", pady=10)
        
        # Save button
        ttk.Button(
            button_frame,
            text="💾 Save",
            command=self.save_settings,
            style="Accent.TButton"
        ).pack(side="left", padx=(0, 10))
        
        # Apply button
        ttk.Button(
            button_frame,
            text="✅ Apply",
            command=self.apply_settings
        ).pack(side="left", padx=(0, 10))
        
        # Cancel button
        ttk.Button(
            button_frame,
            text="❌ Cancel",
            command=self.cancel_changes
        ).pack(side="right")
    
    def load_current_values(self):
        """Load current configuration values"""
        # Time settings
        self.start_time_var.set(self.config_manager.get('time_slots.start'))
        self.end_time_var.set(self.config_manager.get('time_slots.end'))
        self.slot_duration_var.set(str(self.config_manager.get('time_slots.slot_minutes')))
        
        # Appearance settings
        self.header_color_var.set(self.config_manager.get('styling.header_color'))
        self.day_color_var.set(self.config_manager.get('styling.day_color'))
        self.room_color_var.set(self.config_manager.get('styling.room_color'))
        self.font_name_var.set(self.config_manager.get('styling.font_name'))
        self.font_size_var.set(str(self.config_manager.get('styling.font_size')))
        self.auto_adjust_var.set(self.config_manager.get('styling.auto_adjust_columns'))
        
        # Update color button displays
        self.update_color_button(self.header_color_button, self.header_color_var.get())
        self.update_color_button(self.day_color_button, self.day_color_var.get())
        self.update_color_button(self.room_color_button, self.room_color_var.get())
        
        # Export options
        self.include_empty_days_var.set(self.config_manager.get('export_options.include_empty_days'))
        self.merge_day_cells_var.set(self.config_manager.get('export_options.merge_day_cells'))
        self.show_instructor_var.set(self.config_manager.get('export_options.show_instructor'))
        self.show_program_var.set(self.config_manager.get('export_options.show_program'))
        self.compact_mode_var.set(self.config_manager.get('export_options.compact_mode'))
        
        # Watermark settings
        self.show_watermark_var.set(self.config_manager.get('watermark.show'))
        self.watermark_text_var.set(self.config_manager.get('watermark.text'))
        self.watermark_position_var.set(self.config_manager.get('watermark.position'))
        
        # App settings
        self.remember_folder_var.set(self.config_manager.get('app_settings.remember_last_folder'))
        self.auto_open_output_var.set(self.config_manager.get('app_settings.auto_open_output'))
        self.show_analytics_var.set(self.config_manager.get('app_settings.show_analytics'))
        self.check_conflicts_var.set(self.config_manager.get('app_settings.check_conflicts'))
        
        # Update time preview
        self.update_time_preview()
    
    def choose_color(self, color_type, var, button):
        """Open color chooser dialog"""
        current_color = var.get()
        
        # Convert ARGB to RGB for color chooser
        if current_color.startswith('FF'):
            rgb_color = current_color[2:]
            try:
                r = int(rgb_color[0:2], 16)
                g = int(rgb_color[2:4], 16)
                b = int(rgb_color[4:6], 16)
                initial_color = f"#{rgb_color}"
            except ValueError:
                initial_color = "#FFFFFF"
        else:
            initial_color = "#FFFFFF"
        
        color = colorchooser.askcolor(color=initial_color)
        
        if color[1]:  # User selected a color
            # Convert to ARGB format
            hex_color = color[1].replace('#', '')
            argb_color = f"FF{hex_color.upper()}"
            var.set(argb_color)
            self.update_color_button(button, argb_color)
            self.modified = True
    
    def update_color_button(self, button, color):
        """Update color button appearance"""
        try:
            # Convert ARGB to RGB for display
            if color.startswith('FF'):
                rgb_color = f"#{color[2:]}"
                button.config(bg=rgb_color)
        except Exception:
            button.config(bg="#FFFFFF")
    
    def update_time_preview(self):
        """Update time slots preview"""
        try:
            start_time = self.start_time_var.get()
            end_time = self.end_time_var.get()
            duration = int(self.slot_duration_var.get() or 90)
            
            # Validate time format
            start_dt = datetime.strptime(start_time, "%H:%M")
            end_dt = datetime.strptime(end_time, "%H:%M")
            
            if start_dt >= end_dt:
                preview_text = "Error: Start time must be before end time"
            else:
                # Generate time slots
                from datetime import timedelta
                
                time_slots = []
                current_time = start_dt
                
                while current_time < end_dt:
                    slot_end = current_time + timedelta(minutes=duration)
                    if slot_end > end_dt:
                        break
                    time_slots.append(f"{current_time.strftime('%H:%M')} - {slot_end.strftime('%H:%M')}")
                    current_time = slot_end
                
                if time_slots:
                    preview_text = f"Generated {len(time_slots)} time slots:\n\n"
                    preview_text += "\n".join(time_slots)
                else:
                    preview_text = "No time slots generated. Check your settings."
            
        except ValueError:
            preview_text = "Invalid time format. Please use HH:MM format."
        except Exception as e:
            preview_text = f"Error: {str(e)}"
        
        # Update preview
        self.time_preview_text.config(state=tk.NORMAL)
        self.time_preview_text.delete(1.0, tk.END)
        self.time_preview_text.insert(tk.END, preview_text)
        self.time_preview_text.config(state=tk.DISABLED)
    
    def save_settings(self):
        """Save settings and close window"""
        if self.apply_settings():
            self.config_manager.save_user_config()
            self.window.destroy()
    
    def apply_settings(self):
        """Apply current settings"""
        try:
            # Validate time settings
            self.validate_time_settings()
            
            # Update configuration
            self.update_configuration()
            
            messagebox.showinfo("Settings Applied", "Settings have been applied successfully.")
            self.modified = False
            return True
            
        except ValueError as e:
            messagebox.showerror("Invalid Settings", str(e))
            return False
        except Exception as e:
            messagebox.showerror("Error", f"Error applying settings:\n{str(e)}")
            return False
    
    def validate_time_settings(self):
        """Validate time settings"""
        try:
            start_time = datetime.strptime(self.start_time_var.get(), "%H:%M")
            end_time = datetime.strptime(self.end_time_var.get(), "%H:%M")
            duration = int(self.slot_duration_var.get())
            
            if start_time >= end_time:
                raise ValueError("Start time must be before end time")
            
            if duration <= 0 or duration > 480:
                raise ValueError("Slot duration must be between 1 and 480 minutes")
                
        except ValueError as e:
            if "time data" in str(e):
                raise ValueError("Invalid time format. Please use HH:MM format.")
            raise
    
    def update_configuration(self):
        """Update configuration with current values"""
        # Time settings
        self.config_manager.set('time_slots.start', self.start_time_var.get())
        self.config_manager.set('time_slots.end', self.end_time_var.get())
        self.config_manager.set('time_slots.slot_minutes', int(self.slot_duration_var.get()))
        
        # Appearance settings
        self.config_manager.set('styling.header_color', self.header_color_var.get())
        self.config_manager.set('styling.day_color', self.day_color_var.get())
        self.config_manager.set('styling.room_color', self.room_color_var.get())
        self.config_manager.set('styling.font_name', self.font_name_var.get())
        self.config_manager.set('styling.font_size', int(self.font_size_var.get()))
        self.config_manager.set('styling.auto_adjust_columns', self.auto_adjust_var.get())
        
        # Export options
        self.config_manager.set('export_options.include_empty_days', self.include_empty_days_var.get())
        self.config_manager.set('export_options.merge_day_cells', self.merge_day_cells_var.get())
        self.config_manager.set('export_options.show_instructor', self.show_instructor_var.get())
        self.config_manager.set('export_options.show_program', self.show_program_var.get())
        self.config_manager.set('export_options.compact_mode', self.compact_mode_var.get())
        
        # Watermark settings
        self.config_manager.set('watermark.show', self.show_watermark_var.get())
        self.config_manager.set('watermark.text', self.watermark_text_var.get())
        self.config_manager.set('watermark.position', self.watermark_position_var.get())
        
        # App settings
        self.config_manager.set('app_settings.remember_last_folder', self.remember_folder_var.get())
        self.config_manager.set('app_settings.auto_open_output', self.auto_open_output_var.get())
        self.config_manager.set('app_settings.show_analytics', self.show_analytics_var.get())
        self.config_manager.set('app_settings.check_conflicts', self.check_conflicts_var.get())
    
    def reset_to_defaults(self):
        """Reset all settings to defaults"""
        if messagebox.askyesno(
            "Reset Settings",
            "Are you sure you want to reset all settings to their default values?\n\n"
            "This action cannot be undone."
        ):
            self.config_manager.reset_to_defaults()
            self.load_current_values()
            messagebox.showinfo("Settings Reset", "All settings have been reset to default values.")
            self.modified = True
    
    def cancel_changes(self):
        """Cancel changes and close window"""
        if self.modified:
            if messagebox.askyesno(
                "Unsaved Changes",
                "You have unsaved changes. Are you sure you want to cancel?"
            ):
                # Restore original configuration
                self.config_manager.config = self.original_config
                self.window.destroy()
        else:
            self.window.destroy()
    
    def on_closing(self):
        """Handle window closing"""
        self.cancel_changes()
    
    def show(self):
        """Show the configuration window"""
        self.window.deiconify()
        self.window.focus_set()
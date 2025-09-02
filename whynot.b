# Include extra config files

### Variables
# Logo key. Use Mod1 for alt
set $mod Mod4
# Home row direction keys, like vim
set $left h
set $down j
set $up k
set $right l
# Default terminal emulator
set $term alacritty
# Application launcher
# Note: pass the final command to swaymsg so that the resulting
# window can be opened on the original workspace that the command
# was run on.
set $menu wofi --show drun | xargs swaymsg exec --

### Output configuration
output * scale 1.5
output * bg ~/.assets/backgrounds/wallpaper.jpg fill

#
# Idle/lock configuration
#
bindsym $mod+Shift+x exec swaylock

exec swayidle -w \
    timeout 300 'swaylock' \
    timeout 600 'swaymsg "output * power off"' resume 'swaymsg "output * power on"' \
    timeout 600 'systemctl suspend' \

### Input configuration
#
# Example configuration:
#
#	input "2:14:SynPS/2_Synaptics_TouchPad" {
#		dwt enabled
#		tap enabled
#		natural_scroll enabled
#		middle_emulation enabled
#	}
#
# Get the names of the inputs by running swaymsg -t get-inputs
# Read `man 5 sway-input` for more information about this section.
input "type:keyboard" {
    xkb_layout us
    xkb_options caps:swapescape
}

# Set workspaces
set $ws1 1
set $ws2 2
set $ws3 3
set $ws4 4
set $ws5 5
set $ws6 6
set $ws7 7
set $ws8 8
set $ws9 9
set $ws10 10

### Key bindings
#
# Basics
#
	# Start a terminal
	bindsym $mod+Return exec $term

	# Kill focused window
	bindsym $mod+Shift+q kill

	# Start launcher
	bindsym $mod+d exec $menu

	# Drag floating windows by holding down $mod and left mouse button.
	# Resize them with $mod + right mouse button
	# Despite the name, works with non-floating windows
	# Change normal to inverse to use left mouse button for resizing
	# and right mouse button for dragging.
	floating_modifier $mod normal

	# Reload the configuration file
	bindsym $mod+Shift+r reload

	# Exit sway
	# bindsym $mod+Shift+e exec swaymsg -t warning -m "You pressed the exit shortcut. Do you really want to exit sway? This will end your wayland session." -B "Yes, exit sway" "swaymsg exit"
	bindsym $mod+Shift+e exec swaymsg exit
#
# Moving around
#
	# Move focus around
	bindsym $mod+$left focus left
	bindsym $mod+$down focus down
	bindsym $mod+$up focus up
	bindsym $mod+$right focus right
	# Or use $mod+[up|down|left|right]
	bindsym $mod+Left focus left
	bindsym $mod+Down focus down
	bindsym $mod+Up focus up
	bindsym $mod+Right focus right

	# Move the focused window with the same, but add shift
	bindsym $mod+Shift+$left move left
	bindsym $mod+Shift+$down move down
	bindsym $mod+Shift+$up move up
	bindsym $mod+Shift+$right move right
	# Ditto with arrow keys
	bindsym $mod+Shift+Left move left
	bindsym $mod+Shift+Down move down
	bindsym $mod+Shift+Up move up
	bindsym $mod+Shift+Right move right
#
# Workspaces:
#
	# Switch to workspace
	bindsym $mod+1 workspace $ws1
	bindsym $mod+2 workspace $ws2
	bindsym $mod+3 workspace $ws3
	bindsym $mod+4 workspace $ws4
	bindsym $mod+5 workspace $ws5
	bindsym $mod+6 workspace $ws6
	bindsym $mod+7 workspace $ws7
	bindsym $mod+8 workspace $ws8
	bindsym $mod+9 workspace $ws9
	bindsym $mod+0 workspace $ws10
	# Move focused container to workspace
	bindsym $mod+Shift+1 move container to workspace $ws1
	bindsym $mod+Shift+2 move container to workspace $ws2
	bindsym $mod+Shift+3 move container to workspace $ws3
	bindsym $mod+Shift+4 move container to workspace $ws4
	bindsym $mod+Shift+5 move container to workspace $ws5
	bindsym $mod+Shift+6 move container to workspace $ws6
	bindsym $mod+Shift+7 move container to workspace $ws7
	bindsym $mod+Shift+8 move container to workspace $ws8
	bindsym $mod+Shift+9 move container to workspace $ws9
	bindsym $mod+Shift+0 move container to workspace $ws10
#
# Layout:
#
	# Split the current object of focus
	bindsym $mod+b splith
	bindsym $mod+v splitv

	# Switch the current container between different layout styles
	bindsym $mod+s layout stacking
	bindsym $mod+w layout tabbed
	bindsym $mod+e layout toggle split

	# Make the current focus fullscreen
	bindsym $mod+f fullscreen

	# Toggle the current focus between tiling and floating mode
	bindsym $mod+Shift+space floating toggle

	# Swap focus between the tiling area and the floating area
	bindsym $mod+space focus mode_focus

	# Move focus to the parent container
	bindsym $mod+a focus parent
#
# Scratchpad:
#
	# Scratchpad is a bag of holding for windows.
	# Windows can be sent there to be retrieved later.

	# Move the currently focused window to the scratchpad
	bindsym $mod+Shift+minus move scratchpad

	# Show the next scratchpad window or hide the focused scratchpad window.
	# If there are multiple scratchpad windows, this command cycles through them.
	bindsym $mod+minus scratchpad show
#
# Miscellaneous keybinds
#
    bindsym $mod+Shift+c exec alacritty --class float-term -e clipboard
    bindsym $mod+Shift+s exec grim -g "(slurp)" - | tee "$GRIM_DEFAULT_DIR/screenshot_$(date +%Y%m%d-%H%M%S).png" | wl-copy
    bindsym $mod+Shift+s+d exec alacritty --class float-term -e clipboard-delete
#
# Resizing containers:
#
mode "resize" {
	# left will shrink the containers width
	# right will grow the containers width
	# up will shrink the containers height
	# down will grow the containers height
	bindsym $left resize shrink width 10px
	bindsym $right resize grow width 10px
	bindsym $up resize shrink height 10px
	bindsym $down resize grow height 10px

	# Ditto with arrow keys
	bindsym Left resize shrink width 10px
	bindsym Right resize grow width 10px
	bindsym Up resize shrink height 10px
	bindsym Down resize grow height 10px

	# Return to default mode
	bindsym Return mode "default"
	bindsym Escape mode "default"
}
bindsym $mod+r mode "resize"

include config.d/*

# Run startup applications
exec swaync
exec waybar
exec autotiling-rs
exec appimagelauncherd
exec wl-paste --watch cliphist store

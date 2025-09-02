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


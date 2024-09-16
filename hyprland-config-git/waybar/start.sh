#!/usr/bin/env bash

killall waybar
pkill waybar
sleep 0.1
waybar -c ~/Projects/hyprland-config-git/waybar/config.jsonc -s ~/Projects/hyprland-config-git/waybar/style.css &

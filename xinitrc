#!/bin/sh

# merge in defaults and keymaps
xrdb -merge ~/.Xresources
xmodmap ~/.Xmodmap

set +fp $HOME/.local/share/fonts
set fp rehash


# start bars
polybar -r mainbar &
betterlockscreen -w &
urxvtd -q -f -o &

compton --config $HOME/.config/compton/compton.conf -b
dunst -config ~/.config/dunst/dunstrc &

xfce4-power-manager &
redshift &

#setxkbmap -layout us -option ctrl:nocaps &

# Background image
feh --bg-fill "/home/dillon/Pictures/Wallpapers/SP1.jpg"


exec 2bwm


















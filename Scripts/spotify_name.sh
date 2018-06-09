#!/bin/sh
O1="$( sh ~/.config/polybar/mpris.sh -i %title -e "Nothing" )"
O2=" - "
O3="$( sh ~/.config/polybar/mpris.sh -i %artist -e "Playing" )"

O=${O1}${O2}${O3}
echo ${O}

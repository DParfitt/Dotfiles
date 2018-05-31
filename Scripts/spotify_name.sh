#!/bin/sh
O1="$(sh ~/.config/polybar/mpris.sh -i %title)"
O2=" - "
O3="$(sh ~/.config/polybar/mpris.sh -i %artist)"

O=${O1}${O2}${O3}
echo ${O}

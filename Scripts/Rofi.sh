#!/bin/sh

if [[ $1 = "-r" ]]; then
    rofi -show run
fi

if [[ $1 = "-w" ]]; then
    rofi -show window
fi



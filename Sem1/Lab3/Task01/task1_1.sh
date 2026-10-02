#!/bin/bash
# Задание 1, пункт 1
# Простой диалог: yes/no и реакция на выбор

zenity --title "Select" --question --text "Are you a man?" --width 300 --height 120
case "$?" in
    0)  zenity --info --title "Information" --text "Good day, Boy!" --width 250;;
    1)  zenity --info --title "Information" --text "Good day, Girl!" --width 250;;
    *)  zenity --info --title "Information" --text "Good day!" --width 250;;
esac
sleep 1
exit 0

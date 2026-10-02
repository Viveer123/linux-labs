#!/bin/bash
# Задание 1, пункт 2
# Диалог с вводом имени через inputbox

zenity --title "Select" --question --text "Are you a man?" --width 300 --height 120
case "$?" in
    0)
        Q_N=$(zenity --title "Add a new entry" --entry \
                     --text "Good day, Boy. What is your name?" \
                     --width 350)
        if [ -n "$Q_N" ]; then
            zenity --info --text "Hie, $Q_N" --width 250
        fi
        ;;
    1)  zenity --info --text "Good day, Girl!" --width 250;;
    *)  zenity --info --text "Good day!" --width 250;;
esac
sleep 1
exit 0

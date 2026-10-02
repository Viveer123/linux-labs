#!/bin/bash
# Задание 1, пункт 4
# Меню валют в цикле. Выход - вместо названия валюты ввести exit

while true; do
    currency=$(zenity --title "Выбор валюты" --entry \
                      --text "Введите название валюты (или 'exit' для выхода):" \
                      --width 350)

    # Если пользователь закрыл окно или нажал Cancel
    if [ -z "$currency" ]; then
        zenity --info --text "Программа завершена." --width 250
        exit 0
    fi

    if [ "$currency" = "exit" ]; then
        zenity --info --text "До свидания!" --width 250
        break
    fi

    zenity --info --text "Вы ввели: $currency" --width 250
done

sleep 1
exit 0

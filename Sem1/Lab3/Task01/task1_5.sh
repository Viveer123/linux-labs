#!/bin/bash
# Задание 1, пункт 5
# Меню валют с отдельным пунктом "выход" в списке

while true; do
    choice=$(zenity --title "Выбор валюты" --list \
                    --text "Выберите валюту (или выход):" \
                    --column "Валюта" \
                    USD EUR BYN RUB PLN "выход" 2>/dev/null)

    # Если закрыли окно
    if [ -z "$choice" ]; then
        zenity --info --text "Программа завершена." --width 250
        exit 0
    fi

    if [ "$choice" = "выход" ] || [ "$choice" = "exit" ]; then
        zenity --info --text "До свидания!" --width 250
        break
    fi

    zenity --info --text "Вы выбрали: $choice" --width 250
done

sleep 1
exit 0

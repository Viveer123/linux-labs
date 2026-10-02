#!/bin/bash
# Задание 1, пункт 3
# Диалог с оконным меню выбора валюты

currency=$(zenity --title "Выбор валюты" --list \
                  --text "Выберите валюту:" \
                  --column "Валюта" \
                  USD EUR BYN RUB PLN 2>/dev/null)

if [ -n "$currency" ]; then
    zenity --info --text "Вы выбрали: $currency" --width 250
else
    zenity --info --text "Ничего не выбрано" --width 250
fi

sleep 1
exit 0

#!/bin/bash
# Задание 2.7
# Заменить некоторые фамилии на фамилии членов команды
sed -i 's/Nutrina/Anishkevich/; s/Atomova/Nikanorova/; s/Petrov/Khodko/' basa.txt
echo "Фамилии заменены:"
cat basa.txt

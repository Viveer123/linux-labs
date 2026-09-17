#!/bin/bash
# Задание 2.11
# Вывести фамилию самого молодого человека (2-й столбец - возраст)
youngest=$(sort -t: -k2 -n basa.txt | head -1 | cut -d: -f1)
echo "Самый молодой: $youngest"

#!/bin/bash
# Задание 2.9
# Подсчитать число одинаковых слов в двух файлах
common=$(comm -12 <(sort file1.txt) <(sort file2.txt))
count=$(echo "$common" | wc -w)
echo "Общие слова:"
echo "$common"
echo "Количество одинаковых слов: $count"

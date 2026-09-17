#!/bin/bash
# Задание 2.14
# В каждой строке оставить только буквенные символы
sed 's/[^a-zA-Z ]//g' text14.txt > text14_clean.txt
echo "Исходный файл:"
cat text14.txt
echo "Очищенный файл:"
cat text14_clean.txt

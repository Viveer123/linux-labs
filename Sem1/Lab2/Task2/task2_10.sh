#!/bin/bash
# Задание 2.10
# Создать отсортированный файл, содержащий слова из двух файлов,
# исключая их общую часть
sort file1.txt > /tmp/s1
sort file2.txt > /tmp/s2
comm -3 /tmp/s1 /tmp/s2 | sed 's/^\t//' | sort > result_no_common.txt
echo "Результат (без общих слов):"
cat result_no_common.txt

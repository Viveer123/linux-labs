# Задание 1.2
# Найти все файлы, начинающиеся на script, и записать их имена в list.txt
find . -type f -name 'script*' > list.txt
echo "Имена файлов записаны в list.txt"
cat list.txt

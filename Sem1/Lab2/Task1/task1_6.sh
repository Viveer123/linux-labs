# Задание 1.6
# Создание шаблона другого скрипта
read -p "Введите имя файла скрипта: " filename
if [ -z "$filename" ]; then
  echo "Имя файла не может быть пустым."
  exit 1
fi
if [ -f "$filename" ]; then
  echo "Файл $filename уже существует."
  exit 1
fi
cat > "$filename" << TEMPLATE_EOF
#!/bin/bash
# Имя файла: $filename
# Разработчик: $(whoami)
# Пользователь: $(whoami)
# Дата создания: $(date)
# Уникальная информация: Шаблон сделан с помощью Семестр 1, лаб 2, задание 1.6
# Описание: Шаблон скрипта

echo "Это шаблон скрипта $filename"
TEMPLATE_EOF
chmod +x "$filename"
echo "Шаблон $filename создан и сделан исполняемым."

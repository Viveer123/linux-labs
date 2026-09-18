echo "=== Запуск двух скриптов с одинаковым именем ==="
echo ""

CURRENT_DIR="$(pwd)"

# Запускаем первый скрипт через source
cd ../dir1
echo "Перешли в: $(pwd)"
source ./same_name.sh
echo "VALUE после source в dir1: '$VALUE'"
echo ""

# Запускаем второй скрипт через source
cd ../dir2
echo "Перешли в: $(pwd)"
source ./same_name.sh
echo "VALUE после source в dir2: '$VALUE'"
echo ""

cd "$CURRENT_DIR"
echo "Готово. Мы снова в: $(pwd)"

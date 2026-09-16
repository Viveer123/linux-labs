# Задание 1.5
# Поиск командных интерпретаторов в системе
echo "Доступные оболочки в /etc/shells:"
cat /etc/shells 2>/dev/null
echo ""
echo "Поиск распространённых интерпретаторов:"
for sh in bash sh dash zsh ksh csh tcsh fish; do
  path=$(which $sh 2>/dev/null)
  if [ -n "$path" ]; then
    echo "$sh -> $path"
  fi
done
echo ""
echo "Текущий интерпретатор: $SHELL"
echo "Процесс текущей оболочки:"
ps -p $$ -o comm=

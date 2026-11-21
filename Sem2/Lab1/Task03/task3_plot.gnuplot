
#!/usr/bin/gnuplot

# ИЗМЕНЕНО: настройки графика для варианта 1.
set title "График функции y = sin(5x + 1) - cos(x)"

set xlabel "x"
set ylabel "y"

set grid
set key right bottom

# ИЗМЕНЕНО: используем файл с результатами task3.
plot "funtion_data.txt" using 1:2 with lines title "y = sin(5x + 1) - cos(x)"

# Ожидаем закрытия окна графика.
pause mouse close


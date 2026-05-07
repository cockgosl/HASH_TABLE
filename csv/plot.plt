set terminal pngcairo size 2400,1800
set output "images/graph.png"

set title "Мой график"
set xlabel "X"
set ylabel "Y"

set arrow from 0, 1885 to 0, 1906 nohead lw 2 lc rgb "violet"

plot "csv/data.csv" using 1:2 with points pt 7 ps 1.5 lc rgb "violet" title "данные"
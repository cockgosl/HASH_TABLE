set terminal pngcairo size 2400,1800
set output "Dump_inf/graph.png"

set title "Мой график"
set xlabel "X"
set ylabel "Y"

plot "csv/data.csv" using 1:2 with lines title "данные" 
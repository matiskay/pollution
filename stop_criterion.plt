set terminal png
set output "stop_criterion.png"

set title "Stop Criterion"
set xlabel "Iteration"
set ylabel "Stop Criterion"
set style function dots
plot "stop_criterion.dat"

set terminal pngcairo size 1200,800
set output "alpha_plot.png"

set title "Angular Accelerations vs Time"
set xlabel "Time (s)"
set ylabel "Angular Acceleration (rad/s^2)"
set grid

plot "alpha_vs_t.dat" using 1:2 with lines lw 2 title "alpha3", \
     "alpha_vs_t.dat" using 1:3 with lines lw 2 title "alpha4"

set output
set terminal qt
set terminal pngcairo size 1200,800
set output "omega_plot.png"

set title "Angular Velocities vs Time"
set xlabel "Time (s)"
set ylabel "Angular Velocity (rad/s)"
set grid

plot "omega_vs_t.dat" using 1:2 with lines lw 2 title "omega3", \
     "omega_vs_t.dat" using 1:3 with lines lw 2 title "omega4"

set output
set terminal qt
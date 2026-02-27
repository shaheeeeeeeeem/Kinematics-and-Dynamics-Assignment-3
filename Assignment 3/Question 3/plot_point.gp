set terminal pngcairo size 1200,800
set output "point_motion.png"

set title "Coupler Vertex Velocity and Acceleration"
set xlabel "Time (s)"
set ylabel "Magnitude"
set grid

plot "point_motion.dat" using 1:2 with lines lw 2 title "Velocity", \
     "point_motion.dat" using 1:3 with lines lw 2 title "Acceleration"

set output
set terminal qt
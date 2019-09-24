set xlabel "t(s)" 
set grid 
 
set title "Velocities vs time" 
set ylabel " dx dy "
set term postscript eps color
set output "velocities.eps" 
plot"state.dat" using ($1):($8) title "dx","state.dat" using ($1):($9) title "dy"

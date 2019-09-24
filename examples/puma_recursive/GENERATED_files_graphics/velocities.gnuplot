set xlabel "t(s)" 
set grid 
 
set title "Velocities vs time" 
set ylabel " da1 da2 da3 "
set term postscript eps color
set output "velocities.eps" 
plot"state.dat" using ($1):($5) title "da1","state.dat" using ($1):($6) title "da2","state.dat" using ($1):($7) title "da3"

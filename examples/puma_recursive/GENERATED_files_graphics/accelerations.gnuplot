set xlabel "t(s)" 
set grid 
 
set title "Accelerations vs time" 
set ylabel " dda1 dda2 dda3 "
set term postscript eps color
set output "accelerations.eps" 
plot"state.dat" using ($1):($8) title "dda1","state.dat" using ($1):($9) title "dda2","state.dat" using ($1):($10) title "dda3"

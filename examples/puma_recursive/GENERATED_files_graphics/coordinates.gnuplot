set xlabel "t(s)" 
set grid 
 
set title "Coordinates vs time" 
set ylabel " a1 a2 a3 "
set term postscript eps color
set output "coordinates.eps" 
plot"state.dat" using ($1):($2) title "a1","state.dat" using ($1):($3) title "a2","state.dat" using ($1):($4) title "a3"

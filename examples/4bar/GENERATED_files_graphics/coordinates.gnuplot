set xlabel "t(s)" 
set grid 
 
set title "Coordinates vs time" 
set ylabel " theta1 theta2 theta3 "
set term postscript eps color
set output "coordinates.eps" 
plot"state.dat" using ($1):($2) title "theta1","state.dat" using ($1):($3) title "theta2","state.dat" using ($1):($4) title "theta3"

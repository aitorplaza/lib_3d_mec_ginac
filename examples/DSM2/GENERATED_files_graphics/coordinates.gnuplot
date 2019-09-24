set xlabel "t(s)" 
set grid 
 
set title "Coordinates vs time" 
set ylabel " theta1 theta2 psi y z "
set term postscript eps color
set output "coordinates.eps" 
plot"state.dat" using ($1):($2) title "theta1","state.dat" using ($1):($3) title "theta2","state.dat" using ($1):($4) title "psi","state.dat" using ($1):($5) title "y","state.dat" using ($1):($6) title "z"

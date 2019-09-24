set xlabel "t(s)" 
set grid 
 
set title "Coordinates vs time" 
set ylabel " x y b c z a "
set term postscript eps color
set output "coordinates.eps" 
plot"state.dat" using ($1):($2) title "x","state.dat" using ($1):($3) title "y","state.dat" using ($1):($4) title "b","state.dat" using ($1):($5) title "c","state.dat" using ($1):($6) title "z","state.dat" using ($1):($7) title "a"

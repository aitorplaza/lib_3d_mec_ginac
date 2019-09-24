set xlabel "t(s)" 
set grid 
 
set title "Coordinates vs time" 
set ylabel " x y z a b c a1 a2 a3 a4 a5 a6 b1 b2 b3 b4 b5 b6 s1 s2 s3 s4 s5 s6 "
set term postscript eps color
set output "coordinates.eps" 
plot"state.dat" using ($1):($2) title "x","state.dat" using ($1):($3) title "y","state.dat" using ($1):($4) title "z","state.dat" using ($1):($5) title "a","state.dat" using ($1):($6) title "b","state.dat" using ($1):($7) title "c","state.dat" using ($1):($8) title "a1","state.dat" using ($1):($9) title "a2","state.dat" using ($1):($10) title "a3","state.dat" using ($1):($11) title "a4","state.dat" using ($1):($12) title "a5","state.dat" using ($1):($13) title "a6","state.dat" using ($1):($14) title "b1","state.dat" using ($1):($15) title "b2","state.dat" using ($1):($16) title "b3","state.dat" using ($1):($17) title "b4","state.dat" using ($1):($18) title "b5","state.dat" using ($1):($19) title "b6","state.dat" using ($1):($20) title "s1","state.dat" using ($1):($21) title "s2","state.dat" using ($1):($22) title "s3","state.dat" using ($1):($23) title "s4","state.dat" using ($1):($24) title "s5","state.dat" using ($1):($25) title "s6"

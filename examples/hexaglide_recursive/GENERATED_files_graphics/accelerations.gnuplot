set xlabel "t(s)" 
set grid 
 
set title "Accelerations vs time" 
set ylabel " ddx ddy ddz dda ddB ddc dda1 dda2 dda3 dda4 dda5 dda6 ddB1 ddB2 ddB3 ddB4 ddB5 ddB6 dds1 dds2 dds3 dds4 dds5 dds6 "
set term postscript eps color
set output "accelerations.eps" 
plot"state.dat" using ($1):($50) title "ddx","state.dat" using ($1):($51) title "ddy","state.dat" using ($1):($52) title "ddz","state.dat" using ($1):($53) title "dda","state.dat" using ($1):($54) title "ddB","state.dat" using ($1):($55) title "ddc","state.dat" using ($1):($56) title "dda1","state.dat" using ($1):($57) title "dda2","state.dat" using ($1):($58) title "dda3","state.dat" using ($1):($59) title "dda4","state.dat" using ($1):($60) title "dda5","state.dat" using ($1):($61) title "dda6","state.dat" using ($1):($62) title "ddB1","state.dat" using ($1):($63) title "ddB2","state.dat" using ($1):($64) title "ddB3","state.dat" using ($1):($65) title "ddB4","state.dat" using ($1):($66) title "ddB5","state.dat" using ($1):($67) title "ddB6","state.dat" using ($1):($68) title "dds1","state.dat" using ($1):($69) title "dds2","state.dat" using ($1):($70) title "dds3","state.dat" using ($1):($71) title "dds4","state.dat" using ($1):($72) title "dds5","state.dat" using ($1):($73) title "dds6"

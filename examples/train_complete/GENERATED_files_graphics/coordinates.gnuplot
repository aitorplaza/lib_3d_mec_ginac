set xlabel "t(s)" 
set grid 
 
set title "Coordinates vs time" 
set ylabel " xWAG yWAG zWAG aWAG bWAG cWAG bRWHSF bRWHSR bFWHSF bFWHSR "
set term postscript eps color
set output "coordinates.eps" 
plot"state.dat" using ($1):($2) title "xWAG","state.dat" using ($1):($3) title "yWAG","state.dat" using ($1):($4) title "zWAG","state.dat" using ($1):($5) title "aWAG","state.dat" using ($1):($6) title "bWAG","state.dat" using ($1):($7) title "cWAG","state.dat" using ($1):($8) title "bRWHSF","state.dat" using ($1):($9) title "bRWHSR","state.dat" using ($1):($10) title "bFWHSF","state.dat" using ($1):($11) title "bFWHSR"

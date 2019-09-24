set xlabel "t(s)" 
set grid 
 
set title "Velocities vs time" 
set ylabel " dx dy dz da dB dc da1 da2 da3 da4 da5 da6 dB1 dB2 dB3 dB4 dB5 dB6 ds1 ds2 ds3 ds4 ds5 ds6 "
set term postscript eps color
set output "velocities.eps" 
plot"state.dat" using ($1):($26) title "dx","state.dat" using ($1):($27) title "dy","state.dat" using ($1):($28) title "dz","state.dat" using ($1):($29) title "da","state.dat" using ($1):($30) title "dB","state.dat" using ($1):($31) title "dc","state.dat" using ($1):($32) title "da1","state.dat" using ($1):($33) title "da2","state.dat" using ($1):($34) title "da3","state.dat" using ($1):($35) title "da4","state.dat" using ($1):($36) title "da5","state.dat" using ($1):($37) title "da6","state.dat" using ($1):($38) title "dB1","state.dat" using ($1):($39) title "dB2","state.dat" using ($1):($40) title "dB3","state.dat" using ($1):($41) title "dB4","state.dat" using ($1):($42) title "dB5","state.dat" using ($1):($43) title "dB6","state.dat" using ($1):($44) title "ds1","state.dat" using ($1):($45) title "ds2","state.dat" using ($1):($46) title "ds3","state.dat" using ($1):($47) title "ds4","state.dat" using ($1):($48) title "ds5","state.dat" using ($1):($49) title "ds6"

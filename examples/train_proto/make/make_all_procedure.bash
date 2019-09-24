#!/bin/bash
#Compiles main_file.cc and based on its output compiles and executes main_numeric

################################################################################################################
# define variables
################################################################################################################
# STANDARD OPTIONS
################################################################################################################
METHOD=V_P		# ==> MVPhi_qZero.c
ORDER=CMO
MAPLE=MAPLE_ON

SLIP=ROLLING

GRPH=NO_GRAPHVIZ	# do not export to Latex
################################################################################################################
# ALTERNATIVE OPTIONS
# Note: Un-comment the Alternative-option line, Standard option variable becomes over-written. 
################################################################################################################
METHOD=LAG				# Remove Comment for ==> MPhi_qTPhi_qZero.c
#ORDER=RMO				# Remove Comment for standard CMO export.
#SLIP=SLIP					# Remove Comment for slipping.
#MAPLE=MAPLE_OFF		# Remove Comment for non mapple files.

# OTHER options
#GRPH=GRAPHVIZ			# Remove Comment for GRAPHVIZ function, export to Latex
#MEC=3D_MEC					# Remove Comment for 3D_MEC execution.

NAME=main_symbolic

#PROCEDURE=PROCEDURE

NEWTON_RAPHSON_TOLERANCE=1.0e-8
NR_TOL=-DNEWTON_RAPHSON_TOLERANCE=$NEWTON_RAPHSON_TOLERANCE

TRAPEZOIDAL_TOLERANCE=1.0e-8
TR_TOL=-DTRAPEZOIDAL_TOLERANCE=$TRAPEZOIDAL_TOLERANCE
################################################################################################################
if [[ $METHOD != "V_P" ]] && [[ $METHOD != "LAG" ]]; then echo "select METHOD"; exit ; fi
if [[ $ORDER != "CMO" ]] && [[ $ORDER != "RMO" ]]; then echo "select ORDER"; exit ; fi
if [[ $SLIP != "ROLLING" ]] && [[ $SLIP != "SLIP" ]]; then echo "select SLIP"; exit ; fi
if [[ $MAPLE != "MAPLE_ON" ]] && [[ $MAPLE != "MAPLE_OFF" ]]; then echo "select MAPLE"; exit ; fi
################################################################################################################

rm -f -r ./GENERATED_files_*
cp ./common/files_bash/* .
./aux_tree.bash

export PKG_CONFIG_PATH=`pwd`/../../../lib/pkgconfig
export LD_LIBRARY_PATH=`pwd`/../../../lib
#g++ -D$METHOD -DORDER=$ORDER -DMAPLE=$MAPLE -D$SLIP -D$GRPH -D$PROCEDURE -o $NAME $NAME.cc `pkg-config --cflags --libs lib_3d_mec_ginac-1.1 ginac`
g++ -D$METHOD -DORDER=$ORDER -DMAPLE=$MAPLE -D$SLIP -D$GRPH -o $NAME $NAME.cc `pkg-config --cflags --libs lib_3d_mec_ginac-1.1 ginac`

cp ./common/files_tex/* .
./$NAME DOWN NO

cp ./common/files_c_h/* .


./aux_clear_common.bash
./aux_move.bash $GRPH $MAPLE

cp GENERATED_files_matlab/environment.m SOURCE_matlab/


mv $NAME GENERATED_files_bin/

date


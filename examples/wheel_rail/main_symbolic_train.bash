#!/bin/bash
#Compiles main_file.cc and based on its output compiles and executes main_numeric
#####################################################################################################################################################
# define variables
#####################################################################################################################################################
# STANDARD OPTIONS
#####################################################################################################################################################
METHOD=V_P		# ==> MVPhi_qZero.c
ORDER=CMO
MAPLE=MAPLE_ON
GRPH=NO_GRAPHVIZ	# do not export to Latex
TYPE="ALL"
PROCEDURE=PROCEDURE
#AUX_PROCEDURE=-D$PROCEDURE
#####################################################################################################################################################
# ALTERNATIVE OPTIONS: Note: Un-comment the Alternative-option line, Standard option variable becomes over-written. 
#####################################################################################################################################################
METHOD=LAG				# Remove Comment for ==> MPhi_qTPhi_qZero.c
#ORDER=RMO				# Remove Comment for standard CMO export.
MAPLE=MAPLE_OFF		# Remove Comment for non mapple files.
#GRPH=GRAPHVIZ			# Remove Comment for GRAPHVIZ function, export to Latex
TYPE=Q
#TYPE="Z"
#TYPE="I3AL_Q"
#TYPE="I3AL_Z"
#####################################################################################################################################################
STD_OPTIONS="-D$METHOD -DORDER=$ORDER -DMAPLE=$MAPLE -D$GRPH -D$TYPE $AUX_PROCEDURE"
#####################################################################################################################################################
if [[ $METHOD != "V_P" ]] && [[ $METHOD != "LAG" ]]; then echo "select METHOD"; exit ; fi
if [[ $ORDER != "CMO" ]] && [[ $ORDER != "RMO" ]]; then echo "select ORDER"; exit ; fi
if [[ $MAPLE != "MAPLE_ON" ]] && [[ $MAPLE != "MAPLE_OFF" ]]; then echo "select MAPLE"; exit ; fi
#####################################################################################################################################################
#####################################################################################################################################################
# CUSTOMIZE YOUR OPTIONS:
#####################################################################################################################################################
OPTION_1=OPTION_1A
#OPTION_1=OPTION_1B
#AUX_OPTION_1=-D$OPTION_1
#####################################################################################################################################################
AUX_OPTIONS="$AUX_OPTION_1"
#####################################################################################################################################################
#NAME=main_symbolic_v40 # without kalker
#NAME=main_symbolic_v50 # with kalker
#NAME=main_symbolic_v31 # with kalker old model
#NAME=main_symbolic_v60  # with kalker and spline wheel and rail profile
NAME=main_symbolic_v61  # with kalker and spline wheel and rail profile and splines track

rm -f -r ./GENERATED_*
cp ./common_train/files_bash/replace.bash .
./common_train/files_bash/aux_tree.bash

export PKG_CONFIG_PATH=`pwd`/../../../lib/pkgconfig
export LD_LIBRARY_PATH=`pwd`/../../../lib
g++ $STD_OPTIONS $AUX_OPTIONS -o $NAME $NAME.cc `pkg-config --cflags --libs lib_3d_mec_ginac ginac`

cp ./common_train/files_tex/* .
./$NAME DOWN YES
mv $NAME ./GENERATED_files_bin

gnu_files=(*.gnuplot)
if [ -e ${gnu_files[0]} ]
then mv *.gnuplot GENERATED_OSG_bin/
fi


./common_train/files_bash/aux_clear_common.bash
./common_train/files_bash/aux_move.bash
rm -f replace.bash

#!/bin/bash

#Compiles main.cc
################################################################################################################
# DEFINES
################################################################################################################

# file name
NAME=$1

################################################################################################################
# METHOD
# Choose VIRTUAL_POWER or LAGRANGE
METHOD=VIRTUAL_POWER

################################################################################################################
# MAPLE	
# Choose  MAPLE_ON or MAPLE_OFF
MAPLE=MAPLE_ON

################################################################################################################
# INTEGRATOR
# Choose EULER or TRAPEZOIDAL
INTEGRATOR=EULER
################################################################################################################
# ORDER
# Choose CMO or RMO
ORDER=CMO

################################################################################################################
# GRAPHVIZ
# Remove Comment for GRAPHVIZ function, export to Latex
GRPH=GRAPHVIZ

################################################################################################################
rm -f -r ./GENERATED_*
cp ../common/files_bash/* .
./aux_tree.bash

export PKG_CONFIG_PATH=`pwd`/../../../lib/pkgconfig
export LD_LIBRARY_PATH=`pwd`/../../../lib
g++ -D$METHOD -DORDER=$ORDER -DMAPLE=$MAPLE -o $NAME $NAME.cc `pkg-config --cflags --libs lib_3d_mec_ginac-1.1 ginac`

cp ../common/files_tex/* .

./$NAME DOWN NO


cp ../common/files_c_h/* .


./aux_clear_common.bash

./aux_move.bash $GRPH $MAPLE



rm *.*~









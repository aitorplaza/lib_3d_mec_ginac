/*----------M_inertial_parameters.c lib3D_MEC exported-----------*/

/* CMO exported */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "time_3D_mec.h"
#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
#include "param.h"
#include "unknowns.h"
#include "inputs.h"

#include "step.h"

#include "M_inertial_parameters.h"

#define a1 q[ 0 ]
#define a2 q[ 1 ]
#define a3 q[ 2 ]
#define a4 q[ 3 ]
#define a5 q[ 4 ]
#define a6 q[ 5 ]
#define da1 dq[ 0 ]
#define da2 dq[ 1 ]
#define da3 dq[ 2 ]
#define da4 dq[ 3 ]
#define da5 dq[ 4 ]
#define da6 dq[ 5 ]
#define dda1 ddq[ 0 ]
#define dda2 ddq[ 1 ]
#define dda3 ddq[ 2 ]
#define dda4 ddq[ 3 ]
#define dda5 ddq[ 4 ]
#define dda6 ddq[ 5 ]
#define g param[ 0 ]
#define d3 param[ 1 ]
#define r3 param[ 2 ]
#define d4 param[ 3 ]
#define r4 param[ 4 ]
#define m1 param[ 5 ]
#define mx1 param[ 6 ]
#define my1 param[ 7 ]
#define mz1 param[ 8 ]
#define Ixx1 param[ 9 ]
#define Ixy1 param[ 10 ]
#define Ixz1 param[ 11 ]
#define Iyy1 param[ 12 ]
#define Iyz1 param[ 13 ]
#define Izz1 param[ 14 ]
#define m2 param[ 15 ]
#define mx2 param[ 16 ]
#define my2 param[ 17 ]
#define mz2 param[ 18 ]
#define Ixx2 param[ 19 ]
#define Ixy2 param[ 20 ]
#define Ixz2 param[ 21 ]
#define Iyy2 param[ 22 ]
#define Iyz2 param[ 23 ]
#define Izz2 param[ 24 ]
#define m3 param[ 25 ]
#define mx3 param[ 26 ]
#define my3 param[ 27 ]
#define mz3 param[ 28 ]
#define Ixx3 param[ 29 ]
#define Ixy3 param[ 30 ]
#define Ixz3 param[ 31 ]
#define Iyy3 param[ 32 ]
#define Iyz3 param[ 33 ]
#define Izz3 param[ 34 ]
#define m4 param[ 35 ]
#define mx4 param[ 36 ]
#define my4 param[ 37 ]
#define mz4 param[ 38 ]
#define Ixx4 param[ 39 ]
#define Ixy4 param[ 40 ]
#define Ixz4 param[ 41 ]
#define Iyy4 param[ 42 ]
#define Iyz4 param[ 43 ]
#define Izz4 param[ 44 ]
#define m5 param[ 45 ]
#define mx5 param[ 46 ]
#define my5 param[ 47 ]
#define mz5 param[ 48 ]
#define Ixx5 param[ 49 ]
#define Ixy5 param[ 50 ]
#define Ixz5 param[ 51 ]
#define Iyy5 param[ 52 ]
#define Iyz5 param[ 53 ]
#define Izz5 param[ 54 ]
#define m6 param[ 55 ]
#define mx6 param[ 56 ]
#define my6 param[ 57 ]
#define mz6 param[ 58 ]
#define Ixx6 param[ 59 ]
#define Ixy6 param[ 60 ]
#define Ixz6 param[ 61 ]
#define Iyy6 param[ 62 ]
#define Iyz6 param[ 63 ]
#define Izz6 param[ 64 ]
#define Ma1 param[ 65 ]
#define Ma2 param[ 66 ]
#define Ma3 param[ 67 ]
#define Ma4 param[ 68 ]
#define Ma5 param[ 69 ]
#define Ma6 param[ 70 ]
#define FS001 param[ 71 ]
#define FSa11 param[ 72 ]
#define FSb11 param[ 73 ]
#define FSa21 param[ 74 ]
#define FSb21 param[ 75 ]
#define FSa31 param[ 76 ]
#define FSb31 param[ 77 ]
#define FSa41 param[ 78 ]
#define FSb41 param[ 79 ]
#define FS002 param[ 80 ]
#define FSa12 param[ 81 ]
#define FSb12 param[ 82 ]
#define FSa22 param[ 83 ]
#define FSb22 param[ 84 ]
#define FSa32 param[ 85 ]
#define FSb32 param[ 86 ]
#define FSa42 param[ 87 ]
#define FSb42 param[ 88 ]
#define FS003 param[ 89 ]
#define FSa13 param[ 90 ]
#define FSb13 param[ 91 ]
#define FSa23 param[ 92 ]
#define FSb23 param[ 93 ]
#define FSa33 param[ 94 ]
#define FSb33 param[ 95 ]
#define FSa43 param[ 96 ]
#define FSb43 param[ 97 ]
#define FS004 param[ 98 ]
#define FSa14 param[ 99 ]
#define FSb14 param[ 100 ]
#define FSa24 param[ 101 ]
#define FSb24 param[ 102 ]
#define FSa34 param[ 103 ]
#define FSb34 param[ 104 ]
#define FSa44 param[ 105 ]
#define FSb44 param[ 106 ]
#define FS005 param[ 107 ]
#define FSa15 param[ 108 ]
#define FSb15 param[ 109 ]
#define FSa25 param[ 110 ]
#define FSb25 param[ 111 ]
#define FSa35 param[ 112 ]
#define FSb35 param[ 113 ]
#define FSa45 param[ 114 ]
#define FSb45 param[ 115 ]
#define FS006 param[ 116 ]
#define FSa16 param[ 117 ]
#define FSb16 param[ 118 ]
#define FSa26 param[ 119 ]
#define FSb26 param[ 120 ]
#define FSa36 param[ 121 ]
#define FSb36 param[ 122 ]
#define FSa46 param[ 123 ]
#define FSb46 param[ 124 ]
#define g param[ 125 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define lambda3 unknowns[ 2 ]
#define lambda4 unknowns[ 3 ]
#define lambda5 unknowns[ 4 ]
#define lambda6 unknowns[ 5 ]


double * _M_inertial_parameters = NULL;
void Init_M_inertial_parameters ( ) 
{
    _M_inertial_parameters = malloc ( M_inertial_parameters_n_rows * M_inertial_parameters_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < M_inertial_parameters_n_rows * M_inertial_parameters_n_cols ; i++ ) {_M_inertial_parameters[i]=0.0;}
  }
}

void Done_M_inertial_parameters ( ) 
{
if (_M_inertial_parameters != NULL) 
free (_M_inertial_parameters ); 
_M_inertial_parameters = NULL; 
}


double * M_inertial_parameters ()
{
if ( _M_inertial_parameters == NULL )
 {
    _M_inertial_parameters = malloc ( M_inertial_parameters_n_rows * M_inertial_parameters_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < M_inertial_parameters_n_rows * M_inertial_parameters_n_cols ; i++ ) {_M_inertial_parameters[i]=0.0;}
  }
 }


_M_inertial_parameters[0] = m1;
_M_inertial_parameters[1] = mx1;
_M_inertial_parameters[2] = my1;
_M_inertial_parameters[3] = mz1;
_M_inertial_parameters[4] = Ixx1;
_M_inertial_parameters[5] = Ixy1;
_M_inertial_parameters[6] = Iyy1;
_M_inertial_parameters[7] = Ixz1;
_M_inertial_parameters[8] = Iyz1;
_M_inertial_parameters[9] = Izz1;
_M_inertial_parameters[10] = m2;
_M_inertial_parameters[11] = mx2;
_M_inertial_parameters[12] = my2;
_M_inertial_parameters[13] = mz2;
_M_inertial_parameters[14] = Ixx2;
_M_inertial_parameters[15] = Ixy2;
_M_inertial_parameters[16] = Iyy2;
_M_inertial_parameters[17] = Ixz2;
_M_inertial_parameters[18] = Iyz2;
_M_inertial_parameters[19] = Izz2;
_M_inertial_parameters[20] = m3;
_M_inertial_parameters[21] = mx3;
_M_inertial_parameters[22] = my3;
_M_inertial_parameters[23] = mz3;
_M_inertial_parameters[24] = Ixx3;
_M_inertial_parameters[25] = Ixy3;
_M_inertial_parameters[26] = Iyy3;
_M_inertial_parameters[27] = Ixz3;
_M_inertial_parameters[28] = Iyz3;
_M_inertial_parameters[29] = Izz3;
_M_inertial_parameters[30] = m4;
_M_inertial_parameters[31] = mx4;
_M_inertial_parameters[32] = my4;
_M_inertial_parameters[33] = mz4;
_M_inertial_parameters[34] = Ixx4;
_M_inertial_parameters[35] = Ixy4;
_M_inertial_parameters[36] = Iyy4;
_M_inertial_parameters[37] = Ixz4;
_M_inertial_parameters[38] = Iyz4;
_M_inertial_parameters[39] = Izz4;
_M_inertial_parameters[40] = m5;
_M_inertial_parameters[41] = mx5;
_M_inertial_parameters[42] = my5;
_M_inertial_parameters[43] = mz5;
_M_inertial_parameters[44] = Ixx5;
_M_inertial_parameters[45] = Ixy5;
_M_inertial_parameters[46] = Iyy5;
_M_inertial_parameters[47] = Ixz5;
_M_inertial_parameters[48] = Iyz5;
_M_inertial_parameters[49] = Izz5;
_M_inertial_parameters[50] = m6;
_M_inertial_parameters[51] = mx6;
_M_inertial_parameters[52] = my6;
_M_inertial_parameters[53] = mz6;
_M_inertial_parameters[54] = Ixx6;
_M_inertial_parameters[55] = Ixy6;
_M_inertial_parameters[56] = Iyy6;
_M_inertial_parameters[57] = Ixz6;
_M_inertial_parameters[58] = Iyz6;
_M_inertial_parameters[59] = Izz6;

return _M_inertial_parameters;
}
/*----------dPhi_dq.c lib3D_MEC exported-----------*/

/* CMO exported */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "time.h"
#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
#include "param.h"
#include "unknowns.h"
#include "inputs.h"

#include "step.h"

#include "dPhi_dq.h"

#define a1 q[ 0 ]
#define a2 q[ 1 ]
#define a5 q[ 2 ]
#define a6 q[ 3 ]
#define a3 q[ 4 ]
#define a4 q[ 5 ]
#define da1 dq[ 0 ]
#define da2 dq[ 1 ]
#define da5 dq[ 2 ]
#define da6 dq[ 3 ]
#define da3 dq[ 4 ]
#define da4 dq[ 5 ]
#define dda1 ddq[ 0 ]
#define dda2 ddq[ 1 ]
#define dda5 ddq[ 2 ]
#define dda6 ddq[ 3 ]
#define dda3 ddq[ 4 ]
#define dda4 ddq[ 5 ]
#define g param[ 0 ]
#define a1_0 param[ 1 ]
#define da1_0 param[ 2 ]
#define a2_0 param[ 3 ]
#define da2_0 param[ 4 ]
#define a5_0 param[ 5 ]
#define da5_0 param[ 6 ]
#define a6_0 param[ 7 ]
#define da6_0 param[ 8 ]
#define Sp param[ 9 ]
#define Lp param[ 10 ]
#define Ln param[ 11 ]
#define Ww param[ 12 ]
#define W param[ 13 ]
#define Hn param[ 14 ]
#define Hi param[ 15 ]
#define Hs param[ 16 ]
#define Hb param[ 17 ]
#define Rw param[ 18 ]
#define Rr param[ 19 ]
#define Rx param[ 20 ]
#define Bx param[ 21 ]
#define Mx param[ 22 ]
#define Si param[ 23 ]
#define Ss param[ 24 ]
#define SR param[ 25 ]
#define VS param[ 26 ]
#define af1 param[ 27 ]
#define af2 param[ 28 ]
#define W1 param[ 29 ]
#define W2 param[ 30 ]
#define W3 param[ 31 ]
#define W4 param[ 32 ]
#define W5 param[ 33 ]
#define Cvis_a1 param[ 34 ]
#define Cvis_a2 param[ 35 ]
#define Cvis_a3 param[ 36 ]
#define Cvis_a5 param[ 37 ]
#define Cvis_a6 param[ 38 ]
#define Ki param[ 39 ]
#define Li0 param[ 40 ]
#define Li param[ 41 ]
#define Ks param[ 42 ]
#define Ls0 param[ 43 ]
#define Ls param[ 44 ]
#define Kt param[ 45 ]
#define L0 param[ 46 ]
#define L param[ 47 ]
#define Ds param[ 48 ]
#define Di param[ 49 ]
#define m1 param[ 50 ]
#define mx1 param[ 51 ]
#define my1 param[ 52 ]
#define mz1 param[ 53 ]
#define Ixx1 param[ 54 ]
#define Ixy1 param[ 55 ]
#define Ixz1 param[ 56 ]
#define Iyy1 param[ 57 ]
#define Iyz1 param[ 58 ]
#define Izz1 param[ 59 ]
#define m2 param[ 60 ]
#define mx2 param[ 61 ]
#define my2 param[ 62 ]
#define mz2 param[ 63 ]
#define Ixx2 param[ 64 ]
#define Ixy2 param[ 65 ]
#define Ixz2 param[ 66 ]
#define Iyy2 param[ 67 ]
#define Iyz2 param[ 68 ]
#define Izz2 param[ 69 ]
#define m3 param[ 70 ]
#define mx3 param[ 71 ]
#define my3 param[ 72 ]
#define mz3 param[ 73 ]
#define Ixx3 param[ 74 ]
#define Ixy3 param[ 75 ]
#define Ixz3 param[ 76 ]
#define Iyy3 param[ 77 ]
#define Iyz3 param[ 78 ]
#define Izz3 param[ 79 ]
#define m4 param[ 80 ]
#define mx4 param[ 81 ]
#define my4 param[ 82 ]
#define mz4 param[ 83 ]
#define Ixx4 param[ 84 ]
#define Ixy4 param[ 85 ]
#define Ixz4 param[ 86 ]
#define Iyy4 param[ 87 ]
#define Iyz4 param[ 88 ]
#define Izz4 param[ 89 ]
#define m5 param[ 90 ]
#define mx5 param[ 91 ]
#define my5 param[ 92 ]
#define mz5 param[ 93 ]
#define Ixx5 param[ 94 ]
#define Ixy5 param[ 95 ]
#define Ixz5 param[ 96 ]
#define Iyy5 param[ 97 ]
#define Iyz5 param[ 98 ]
#define Izz5 param[ 99 ]
#define m6 param[ 100 ]
#define mx6 param[ 101 ]
#define my6 param[ 102 ]
#define mz6 param[ 103 ]
#define Ixx6 param[ 104 ]
#define Ixy6 param[ 105 ]
#define Ixz6 param[ 106 ]
#define Iyy6 param[ 107 ]
#define Iyz6 param[ 108 ]
#define Izz6 param[ 109 ]
#define Fn unknowns[ 0 ]
#define Ft unknowns[ 1 ]
#define Tm inputs[ 0 ]
#define Tb inputs[ 1 ]
double * _dPhi_dq = NULL;
void Init_dPhi_dq ( ) 
 {
    _dPhi_dq = malloc ( dPhi_dq_n_rows * dPhi_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhi_dq_n_rows * dPhi_dq_n_cols ; i++ ) {_dPhi_dq[i]=0.0;}
  }
 }

void Done_dPhi_dq ( ) 
{
if (_dPhi_dq != NULL) 
free (_dPhi_dq ); 
_dPhi_dq = NULL; 
}


double * dPhi_dq ()
{
if ( _dPhi_dq == NULL )
 {
    _dPhi_dq = malloc ( dPhi_dq_n_rows * dPhi_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhi_dq_n_rows * dPhi_dq_n_cols ; i++ ) {_dPhi_dq[i]=0.0;}
  }
 }
{
#include "dPhi_dq_maple_include.c"
}
return _dPhi_dq;
}

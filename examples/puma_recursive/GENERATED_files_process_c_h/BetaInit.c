/*----------BetaInit.c lib3D_MEC exported-----------*/

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

#include "BetaInit.h"

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

double atom2255;
double atom2269;
double atom2259;
double atom2266;
double atom2251;
double atom2253;
double atom2263;
double atom2257;
double atom2272;
double atom2274;
double atom2261;

double * _BetaInit = NULL;
void Init_BetaInit ( ) 
{
    _BetaInit = malloc ( BetaInit_n_rows * BetaInit_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < BetaInit_n_rows * BetaInit_n_cols ; i++ ) {_BetaInit[i]=0.0;}
  }
}

void Done_BetaInit ( ) 
{
if (_BetaInit != NULL) 
free (_BetaInit ); 
_BetaInit = NULL; 
}


double * BetaInit ()
{
if ( _BetaInit == NULL )
 {
    _BetaInit = malloc ( BetaInit_n_rows * BetaInit_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < BetaInit_n_rows * BetaInit_n_cols ; i++ ) {_BetaInit[i]=0.0;}
  }
 }

atom2255 = 3.0*t;
atom2269 = -3.0*sin(atom2255);
atom2259 = 2.0*t;
atom2266 = 2.0*cos(atom2259);
atom2251 = 4.0*t;
atom2253 = 4.0*cos(atom2251);
atom2263 = cos(t);
atom2257 = 3.0*cos(atom2255);
atom2272 = -4.0*sin(atom2251);
atom2274 = sin(t);
atom2261 = -2.0*sin(atom2259);

_BetaInit[0] =  FSa41*atom2253+atom2263*FSa11+atom2266*FSa21+atom2261*FSb21+atom2272*FSb41-atom2274*FSb11+atom2269*FSb31+atom2257*FSa31;
_BetaInit[1] =  atom2266*FSa22+atom2272*FSb42+atom2257*FSa32-FSb12*atom2274+atom2269*FSb32+FSa42*atom2253+FSb22*atom2261+FSa12*atom2263;
_BetaInit[2] = -FSb13*atom2274+atom2263*FSa13+atom2257*FSa33+FSb43*atom2272+atom2261*FSb23+FSa23*atom2266+atom2253*FSa43+atom2269*FSb33;
_BetaInit[3] =  atom2272*FSb44+atom2257*FSa34+atom2261*FSb24+FSa24*atom2266+atom2269*FSb34+atom2263*FSa14-FSb14*atom2274+FSa44*atom2253;
_BetaInit[4] =  atom2263*FSa15-atom2274*FSb15+FSa25*atom2266+atom2257*FSa35+FSb35*atom2269+atom2261*FSb25+FSa45*atom2253+atom2272*FSb45;
_BetaInit[5] =  FSa46*atom2253+atom2266*FSa26+atom2272*FSb46+FSb26*atom2261+FSa16*atom2263+atom2269*FSb36-atom2274*FSb16+atom2257*FSa36;

return _BetaInit;
}

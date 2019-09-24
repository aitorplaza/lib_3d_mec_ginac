/*----------M.c lib3D_MEC exported-----------*/

/* CMO exported */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "time_3D_mec.h"
#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
#include "gen_auxcoord.h"
#include "gen_auxvel.h"
#include "gen_auxaccel.h"
#include "param.h"
#include "unknowns.h"
#include "inputs.h"

#include "step.h"

#include "M.h"

#define x q[ 0 ]
#define y q[ 1 ]
#define b q[ 2 ]
#define c q[ 3 ]
#define z q[ 4 ]
#define a q[ 5 ]
#define dx dq[ 0 ]
#define dy dq[ 1 ]
#define db dq[ 2 ]
#define dc dq[ 3 ]
#define dz dq[ 4 ]
#define da dq[ 5 ]
#define ddx ddq[ 0 ]
#define ddy ddq[ 1 ]
#define ddb ddq[ 2 ]
#define ddc ddq[ 3 ]
#define ddz ddq[ 4 ]
#define dda ddq[ 5 ]
#define thetaW_R qaux[ 0 ]
#define uW_R qaux[ 1 ]
#define uR_R qaux[ 2 ]
#define sR_R qaux[ 3 ]
#define thetaW_L qaux[ 4 ]
#define uW_L qaux[ 5 ]
#define uR_L qaux[ 6 ]
#define sR_L qaux[ 7 ]
#define dthetaW_R dqaux[ 0 ]
#define duW_R dqaux[ 1 ]
#define duR_R dqaux[ 2 ]
#define dsR_R dqaux[ 3 ]
#define dthetaW_L dqaux[ 4 ]
#define duW_L dqaux[ 5 ]
#define duR_L dqaux[ 6 ]
#define dsR_L dqaux[ 7 ]
#define ddthetaW_R ddqaux[ 0 ]
#define dduW_R ddqaux[ 1 ]
#define dduR_R ddqaux[ 2 ]
#define ddsR_R ddqaux[ 3 ]
#define ddthetaW_L ddqaux[ 4 ]
#define dduW_L ddqaux[ 5 ]
#define dduR_L ddqaux[ 6 ]
#define ddsR_L ddqaux[ 7 ]
#define g param[ 0 ]
#define a_pend param[ 1 ]
#define b_pend param[ 2 ]
#define L_R param[ 3 ]
#define L_WHS param[ 4 ]
#define a_rail param[ 5 ]
#define mWHS param[ 6 ]
#define I_WHSx param[ 7 ]
#define I_WHSy param[ 8 ]
#define I_WHSz param[ 9 ]
#define tor param[ 10 ]
#define asR param[ 11 ]
#define bsR param[ 12 ]
#define csR param[ 13 ]
#define dsR param[ 14 ]
#define esR param[ 15 ]
#define fsR param[ 16 ]
#define stasR param[ 17 ]
#define endsR param[ 18 ]
#define usRz param[ 19 ]
#define aW_R param[ 20 ]
#define bW_R param[ 21 ]
#define cW_R param[ 22 ]
#define dW_R param[ 23 ]
#define lW_R param[ 24 ]
#define aR_R param[ 25 ]
#define bR_R param[ 26 ]
#define cR_R param[ 27 ]
#define dR_R param[ 28 ]
#define lR_R param[ 29 ]
#define asL param[ 30 ]
#define bsL param[ 31 ]
#define csL param[ 32 ]
#define dsL param[ 33 ]
#define esL param[ 34 ]
#define fsL param[ 35 ]
#define stasL param[ 36 ]
#define endsL param[ 37 ]
#define usLz param[ 38 ]
#define aW_L param[ 39 ]
#define bW_L param[ 40 ]
#define cW_L param[ 41 ]
#define dW_L param[ 42 ]
#define lW_L param[ 43 ]
#define aR_L param[ 44 ]
#define bR_L param[ 45 ]
#define cR_L param[ 46 ]
#define dR_L param[ 47 ]
#define lR_L param[ 48 ]
#define E_elastic param[ 49 ]
#define nu_poisson param[ 50 ]
#define G_elastic param[ 51 ]
#define aR param[ 52 ]
#define bR param[ 53 ]
#define aL param[ 54 ]
#define bL param[ 55 ]
#define C11R param[ 56 ]
#define C22R param[ 57 ]
#define C23R param[ 58 ]
#define C33R param[ 59 ]
#define C11L param[ 60 ]
#define C22L param[ 61 ]
#define C23L param[ 62 ]
#define C33L param[ 63 ]
#define y0 param[ 64 ]
#define b0 param[ 65 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define Fx_R inputs[ 0 ]
#define Fy_R inputs[ 1 ]
#define Mz_R inputs[ 2 ]
#define Fx_L inputs[ 3 ]
#define Fy_L inputs[ 4 ]
#define Mz_L inputs[ 5 ]

double atom4;
double atom2;
double atom3;
double atom71;
double atom78;
double atom79;
double atom1;
double atom72;
double atom80;
double atom105;

double * _M = NULL;
void Init_M ( ) 
{
    _M = malloc ( M_n_rows * M_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < M_n_rows * M_n_cols ; i++ ) {_M[i]=0.0;}
  }
}

void Done_M ( ) 
{
if (_M != NULL) 
free (_M ); 
_M = NULL; 
}


double * M ()
{
if ( _M == NULL )
 {
    _M = malloc ( M_n_rows * M_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < M_n_rows * M_n_cols ; i++ ) {_M[i]=0.0;}
  }
 }

atom4 = sin(a);
atom2 = sin(b);
atom3 = cos(a);
atom71 = -atom2*atom3;
atom78 = I_WHSx*atom71;
atom79 = atom4*I_WHSy;
atom1 = cos(b);
atom72 = atom1*atom3;
atom80 = I_WHSz*atom72;
atom105 =  atom78*atom1+atom80*atom2;

_M[0] = -mWHS;
_M[1] = 0.0;
_M[2] = 0.0;
_M[3] = 0.0;
_M[4] = 0.0;
_M[5] = 0.0;
_M[6] = 0.0;
_M[7] = -mWHS;
_M[8] = 0.0;
_M[9] = 0.0;
_M[10] = 0.0;
_M[11] = 0.0;
_M[12] = 0.0;
_M[13] = 0.0;
_M[14] = -I_WHSy;
_M[15] = -atom79;
_M[16] = 0.0;
_M[17] = 0.0;
_M[18] = 0.0;
_M[19] = 0.0;
_M[20] = -atom79;
_M[21] = -atom79*atom4-atom80*atom72-atom78*atom71;
_M[22] = 0.0;
_M[23] = -atom105;
_M[24] = 0.0;
_M[25] = 0.0;
_M[26] = 0.0;
_M[27] = 0.0;
_M[28] = -mWHS;
_M[29] = 0.0;
_M[30] = 0.0;
_M[31] = 0.0;
_M[32] = 0.0;
_M[33] = -atom105;
_M[34] = 0.0;
_M[35] = -I_WHSz*(atom2*atom2)-(atom1*atom1)*I_WHSx;

return _M;
}

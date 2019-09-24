/*----------Delta.c lib3D_MEC exported-----------*/

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

#include "Delta.h"

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

double atom9;
double atom8;
double atom13;
double atom65;
double atom10;
double atom3;
double atom1;
double atom1158;
double atom2;
double atom1161;
double atom1164;
double atom4;
double atom6;
double atom7;
double atom16;
double atom31;
double atom758;
double atom12;
double atom11;
double atom5;
double atom22;
double atom37;
double atom759;
double atom28;
double atom14;
double atom43;
double atom760;
double atom1279;
double atom765;
double atom1157;
double atom1165;
double atom72;
double atom1280;
double atom1278;
double atom71;
double atom46;
double atom25;
double atom19;
double atom40;
double atom15;
double atom34;
double atom1313;
double atom1308;

double * _Delta = NULL;
void Init_Delta ( ) 
{
    _Delta = malloc ( Delta_n_rows * Delta_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Delta_n_rows * Delta_n_cols ; i++ ) {_Delta[i]=0.0;}
  }
}

void Done_Delta ( ) 
{
if (_Delta != NULL) 
free (_Delta ); 
_Delta = NULL; 
}


double * Delta ()
{
if ( _Delta == NULL )
 {
    _Delta = malloc ( Delta_n_rows * Delta_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Delta_n_rows * Delta_n_cols ; i++ ) {_Delta[i]=0.0;}
  }
 }

atom9 = cos(a_pend);
atom8 = sin(b_pend);
atom13 = -atom9*atom8;
atom65 = -mWHS*g;
atom10 = sin(a_pend);
atom3 = cos(a);
atom1 = cos(b);
atom1158 = atom3*dc;
atom2 = sin(b);
atom1161 = -atom1158*atom2+atom1*da;
atom1164 =  atom1*atom1158+atom2*da;
atom4 = sin(a);
atom6 = sin(c);
atom7 = cos(b_pend);
atom16 = -atom6*atom7;
atom31 =  atom16*atom3+atom4*atom8;
atom758 = tor*atom31;
atom12 = -atom10*atom7;
atom11 = atom10*atom8;
atom5 = cos(c);
atom22 = -atom6*atom11+atom5*atom9;
atom37 =  atom22*atom3+atom12*atom4;
atom759 = tor*atom37;
atom28 = -atom13*atom6+atom5*atom10;
atom14 = atom9*atom7;
atom43 =  atom28*atom3+atom14*atom4;
atom760 = tor*atom43;
atom1279 =  atom1164*atom1161*I_WHSx+atom1158*da*I_WHSy-atom1164*I_WHSz*atom1161;
atom765 =  atom759*atom37+atom43*atom760+atom758*atom31;
atom1157 = dc*atom4;
atom1165 =  db+atom1157;
atom72 = atom1*atom3;
atom1280 = -atom1161*I_WHSx*atom1165+atom1161*atom1165*I_WHSy+I_WHSz*( atom1161*db-atom1*da*atom1157);
atom1278 =  atom1164*I_WHSz*atom1165+( atom2*da*atom1157-atom1164*db)*I_WHSx-atom1164*atom1165*I_WHSy;
atom71 = -atom2*atom3;
atom46 = -atom28*atom4+atom14*atom3;
atom25 =  atom5*atom13+atom10*atom6;
atom19 =  atom5*atom11+atom9*atom6;
atom40 =  atom12*atom3-atom22*atom4;
atom15 = atom5*atom7;
atom34 =  atom3*atom8-atom16*atom4;
atom1313 =  atom758*( atom2*atom15+atom34*atom1)+atom759*( atom1*atom40+atom2*atom19)+( atom25*atom2+atom1*atom46)*atom760;
atom1308 = -atom759*( atom2*atom40-atom1*atom19)-atom758*( atom34*atom2-atom1*atom15)+atom760*( atom1*atom25-atom2*atom46);

_Delta[0] = -atom13*atom65;
_Delta[1] = -atom10*atom65;
_Delta[2] =  atom1279-atom765;
_Delta[3] =  atom1279*atom4-atom72*atom1313+atom72*atom1280+atom1278*atom71-atom765*atom4-atom1308*atom71;
_Delta[4] = -atom14*atom65;
_Delta[5] = -atom2*atom1313+atom2*atom1280+atom1*atom1278-atom1308*atom1;

return _Delta;
}

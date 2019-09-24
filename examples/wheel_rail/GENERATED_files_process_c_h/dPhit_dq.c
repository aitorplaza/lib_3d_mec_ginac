/*----------dPhit_dq.c lib3D_MEC exported-----------*/

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

#include "dPhit_dq.h"

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

double atom381;
double atom382;
double atom384;
double atom386;
double atom393;
double atom396;
double atom399;
double atom388;
double atom402;
double atom405;
double atom407;
double atom416;
double atom422;
double atom426;
double atom429;
double atom408;
double atom434;
double atom440;
double atom438;
double atom449;
double atom457;
double atom5;
double atom3;
double atom307;
double atom146;
double atom309;
double atom310;
double atom311;
double atom313;
double atom308;
double atom315;
double atom6;
double atom316;
double atom317;
double atom4;
double atom318;
double atom147;
double atom320;
double atom458;
double atom144;
double atom145;
double atom319;
double atom2104;
double atom459;
double atom2061;
double atom2108;
double atom2109;
double atom372;
double atom373;
double atom374;
double atom443;
double atom462;
double atom1076;
double atom463;
double atom445;
double atom444;
double atom451;
double atom452;
double atom453;
double atom454;
double atom350;
double atom351;
double atom354;
double atom566;
double atom567;
double atom569;
double atom571;
double atom573;
double atom578;
double atom581;
double atom584;
double atom587;
double atom590;
double atom592;
double atom593;
double atom605;
double atom609;
double atom601;
double atom614;
double atom619;
double atom625;
double atom623;
double atom634;
double atom642;
double atom497;
double atom498;
double atom499;
double atom501;
double atom503;
double atom505;
double atom506;
double atom496;
double atom504;
double atom643;
double atom2178;
double atom644;
double atom2182;
double atom557;
double atom558;
double atom559;
double atom628;
double atom647;
double atom648;
double atom630;
double atom629;
double atom636;
double atom638;
double atom637;
double atom639;
double atom535;
double atom538;
double atom536;

double * _dPhit_dq = NULL;
void Init_dPhit_dq ( ) 
{
    _dPhit_dq = malloc ( dPhit_dq_n_rows * dPhit_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhit_dq_n_rows * dPhit_dq_n_cols ; i++ ) {_dPhit_dq[i]=0.0;}
  }
}

void Done_dPhit_dq ( ) 
{
if (_dPhit_dq != NULL) 
free (_dPhit_dq ); 
_dPhit_dq = NULL; 
}


double * dPhit_dq ()
{
if ( _dPhit_dq == NULL )
 {
    _dPhit_dq = malloc ( dPhit_dq_n_rows * dPhit_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhit_dq_n_rows * dPhit_dq_n_cols ; i++ ) {_dPhit_dq[i]=0.0;}
  }
 }

atom381 = 1.0/( endsR-stasR);
atom382 = ( sR_R-stasR)*atom381;
atom384 =  bsR+atom382*asR;
atom386 =  atom382*atom384+csR;
atom393 = atom381*asR;
atom396 =  atom381*atom384+atom393*atom382;
atom399 =  atom382*atom396+atom386*atom381;
atom388 =  atom386*atom382+dsR;
atom402 =  atom399*atom382+atom381*atom388;
atom405 =  ( atom388*atom382+esR)*atom381+atom402*atom382;
atom407 =  (atom405*atom405)+1.0;
atom416 = atom381*atom396;
atom422 = atom381*atom399;
atom426 = atom381*atom402;
atom429 =  2.0*atom426+2.0*( atom422+( atom393*atom381*atom382+atom416)*atom382)*atom382;
atom408 = pow(atom407,(1.0/2.0));
atom434 = -1.0/(atom408*atom408)*atom429*atom405*pow(atom407,-(1.0/2.0));
atom440 =  atom405+-5.0000000000000000e-01*atom434*L_R;
atom438 =  5.0000000000000000e-01*1.0/atom408*atom429*L_R+5.0000000000000000e-01*atom405*atom434*L_R+1.0;
atom449 = (atom438*atom438);
atom457 = pow( (atom440*atom440)+atom449,-(1.0/2.0));
atom5 = cos(c);
atom3 = cos(a);
atom307 = -5.0000000000000000e-01*L_WHS;
atom146 = atom5*atom3;
atom309 =  uW_R-lW_R;
atom310 = aW_R*atom309;
atom311 =  bW_R+atom310;
atom313 =  atom309*atom311+cW_R;
atom308 = sin(thetaW_R);
atom315 =  dW_R+atom313*atom309;
atom6 = sin(c);
atom316 = -atom308*atom315;
atom317 = cos(thetaW_R);
atom4 = sin(a);
atom318 = atom315*atom317;
atom147 = -atom5*atom4;
atom320 = atom307*atom146;
atom458 = atom457*atom438;
atom144 = -atom6*atom3;
atom145 = atom6*atom4;
atom319 = atom144*atom307;
atom2104 =  atom5*atom316+atom318*atom145+uW_R*atom144+atom319;
atom459 = atom457*atom440;
atom2061 = atom145*atom307;
atom2108 = atom147*atom307;
atom2109 = -atom318*atom146+uW_R*atom147+atom2108;
atom372 =  uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 =  bR_R+atom373;
atom443 =  atom374*atom372+cR_R+atom372*( atom374+atom373);
atom462 = pow( (atom443*atom443)+1.0,-(1.0/2.0));
atom1076 = atom3*atom307;
atom463 = atom462*atom443;
atom445 = -atom438*atom443;
atom444 = atom443*atom440;
atom451 = pow( (atom444*atom444)+(atom445*atom445)+atom449,-(1.0/2.0));
atom452 = atom444*atom451;
atom453 = atom451*atom445;
atom454 = atom438*atom451;
atom350 =  atom313+( atom310+atom311)*atom309;
atom351 = -atom308*atom350;
atom354 = atom350*atom317;
atom566 = 1.0/( endsL-stasL);
atom567 = ( sR_L-stasL)*atom566;
atom569 =  bsL+atom567*asL;
atom571 =  atom567*atom569+csL;
atom573 =  atom567*atom571+dsL;
atom578 = atom566*asL;
atom581 =  atom567*atom578+atom569*atom566;
atom584 =  atom571*atom566+atom581*atom567;
atom587 =  atom573*atom566+atom584*atom567;
atom590 =  ( esL+atom567*atom573)*atom566+atom567*atom587;
atom592 =  (atom590*atom590)+1.0;
atom593 = pow(atom592,(1.0/2.0));
atom605 = atom581*atom566;
atom609 = atom584*atom566;
atom601 = atom587*atom566;
atom614 =  2.0*( atom567*( atom605+atom567*atom578*atom566)+atom609)*atom567+2.0*atom601;
atom619 = -1.0/(atom593*atom593)*atom614*atom590*pow(atom592,-(1.0/2.0));
atom625 =  atom590+5.0000000000000000e-01*L_R*atom619;
atom623 =  -5.0000000000000000e-01*atom590*L_R*atom619+-5.0000000000000000e-01*1.0/atom593*atom614*L_R+1.0;
atom634 = (atom623*atom623);
atom642 = pow( atom634+(atom625*atom625),-(1.0/2.0));
atom497 =  uW_L-lW_L;
atom498 = atom497*aW_L;
atom499 =  atom498+bW_L;
atom501 =  cW_L+atom497*atom499;
atom503 =  dW_L+atom497*atom501;
atom505 = cos(thetaW_L);
atom506 = atom503*atom505;
atom496 = sin(thetaW_L);
atom504 = -atom503*atom496;
atom643 = atom642*atom623;
atom2178 =  atom5*atom504+atom506*atom145+atom144*uW_L-atom319;
atom644 = atom625*atom642;
atom2182 = -atom506*atom146+atom147*uW_L-atom2108;
atom557 =  uR_L-lR_L;
atom558 = aR_L*atom557;
atom559 =  bR_L+atom558;
atom628 =  atom559*atom557+cR_L+( atom559+atom558)*atom557;
atom647 = pow( (atom628*atom628)+1.0,-(1.0/2.0));
atom648 = atom647*atom628;
atom630 = -atom623*atom628;
atom629 = atom625*atom628;
atom636 = pow( atom634+(atom629*atom629)+(atom630*atom630),-(1.0/2.0));
atom638 = atom630*atom636;
atom637 = atom629*atom636;
atom639 = atom623*atom636;
atom535 =  atom501+atom497*( atom498+atom499);
atom538 = -atom535*atom496;
atom536 = atom535*atom505;

_dPhit_dq[0] = atom458;
_dPhit_dq[1] = 0.0000000000000000e+00;
_dPhit_dq[2] = 0.0000000000000000e+00;
_dPhit_dq[3] = 0.0000000000000000e+00;
_dPhit_dq[4] = atom643;
_dPhit_dq[5] = 0.0000000000000000e+00;
_dPhit_dq[6] = 0.0000000000000000e+00;
_dPhit_dq[7] = 0.0000000000000000e+00;
_dPhit_dq[8] = atom459;
_dPhit_dq[9] = atom462;
_dPhit_dq[10] = 0.0000000000000000e+00;
_dPhit_dq[11] = 0.0000000000000000e+00;
_dPhit_dq[12] = atom644;
_dPhit_dq[13] = atom647;
_dPhit_dq[14] = 0.0000000000000000e+00;
_dPhit_dq[15] = 0.0000000000000000e+00;
_dPhit_dq[16] = 0.0000000000000000e+00;
_dPhit_dq[17] = 0.0000000000000000e+00;
_dPhit_dq[18] = 0.0000000000000000e+00;
_dPhit_dq[19] = 0.0000000000000000e+00;
_dPhit_dq[20] = 0.0000000000000000e+00;
_dPhit_dq[21] = 0.0000000000000000e+00;
_dPhit_dq[22] = 0.0000000000000000e+00;
_dPhit_dq[23] = 0.0000000000000000e+00;
_dPhit_dq[24] =  atom2104*atom459-( atom320+uW_R*atom146+atom6*atom316+atom318*atom147)*atom458;
_dPhit_dq[25] = atom2104*atom462;
_dPhit_dq[26] =  atom452*( atom318*atom6-atom147*atom316)+( atom145*atom316-atom318*atom5)*atom453;
_dPhit_dq[27] = -atom452*( atom6*atom351+atom147*atom354+atom146)+( atom144+atom5*atom351+atom145*atom354)*atom453;
_dPhit_dq[28] =  ( atom320-uW_L*atom146-atom506*atom147-atom6*atom504)*atom643+atom2178*atom644;
_dPhit_dq[29] = atom2178*atom647;
_dPhit_dq[30] = -atom637*( atom147*atom504-atom506*atom6)-atom638*( atom5*atom506-atom145*atom504);
_dPhit_dq[31] =  atom638*( atom144+atom5*atom538+atom145*atom536)-atom637*( atom147*atom536+atom538*atom6+atom146);
_dPhit_dq[32] = 0.0000000000000000e+00;
_dPhit_dq[33] = atom463;
_dPhit_dq[34] = 0.0000000000000000e+00;
_dPhit_dq[35] = 0.0000000000000000e+00;
_dPhit_dq[36] = 0.0000000000000000e+00;
_dPhit_dq[37] = atom648;
_dPhit_dq[38] = 0.0000000000000000e+00;
_dPhit_dq[39] = 0.0000000000000000e+00;
_dPhit_dq[40] =  ( atom2061+uW_R*atom145-atom318*atom144)*atom458+atom459*atom2109;
_dPhit_dq[41] =  ( uW_R*atom3-atom318*atom4+atom1076)*atom463+atom462*atom2109;
_dPhit_dq[42] = -atom453*atom316*atom146-atom452*atom144*atom316-atom454*atom4*atom316;
_dPhit_dq[43] = -( atom144*atom354-atom145)*atom452-( atom354*atom146-atom147)*atom453-atom454*( atom4*atom354-atom3);
_dPhit_dq[44] =  atom644*atom2182+( atom145*uW_L-atom2061-atom506*atom144)*atom643;
_dPhit_dq[45] =  atom647*atom2182-( atom506*atom4-atom3*uW_L+atom1076)*atom648;
_dPhit_dq[46] = -atom637*atom144*atom504-atom638*atom146*atom504-atom639*atom4*atom504;
_dPhit_dq[47] = -( atom144*atom536-atom145)*atom637+atom638*( atom147-atom536*atom146)-atom639*( atom4*atom536-atom3);

return _dPhit_dq;
}

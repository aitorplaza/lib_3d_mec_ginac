/*----------dPhic_ds.c lib3D_MEC exported-----------*/

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

#include "dPhic_ds.h"

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

double atom309;
double atom310;
double atom311;
double atom313;
double atom308;
double atom315;
double atom3;
double atom316;
double atom381;
double atom379;
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
double atom436;
double atom438;
double atom372;
double atom373;
double atom374;
double atom443;
double atom445;
double atom444;
double atom451;
double atom454;
double atom5;
double atom4;
double atom147;
double atom317;
double atom318;
double atom6;
double atom453;
double atom145;
double atom452;
double atom350;
double atom354;
double atom351;
double atom146;
double atom144;
double atom2086;
double atom2100;
double atom564;
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
double atom557;
double atom558;
double atom559;
double atom628;
double atom620;
double atom623;
double atom630;
double atom629;
double atom636;
double atom497;
double atom498;
double atom499;
double atom501;
double atom503;
double atom505;
double atom506;
double atom496;
double atom504;
double atom637;
double atom638;
double atom639;
double atom535;
double atom538;
double atom536;
double atom2160;
double atom2174;

double * _dPhic_ds = NULL;
void Init_dPhic_ds ( ) 
{
    _dPhic_ds = malloc ( dPhic_ds_n_rows * dPhic_ds_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhic_ds_n_rows * dPhic_ds_n_cols ; i++ ) {_dPhic_ds[i]=0.0;}
  }
}

void Done_dPhic_ds ( ) 
{
if (_dPhic_ds != NULL) 
free (_dPhic_ds ); 
_dPhic_ds = NULL; 
}


double * dPhic_ds ()
{
if ( _dPhic_ds == NULL )
 {
    _dPhic_ds = malloc ( dPhic_ds_n_rows * dPhic_ds_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhic_ds_n_rows * dPhic_ds_n_cols ; i++ ) {_dPhic_ds[i]=0.0;}
  }
 }

atom309 =  uW_R-lW_R;
atom310 = aW_R*atom309;
atom311 =  bW_R+atom310;
atom313 =  atom309*atom311+cW_R;
atom308 = sin(thetaW_R);
atom315 =  dW_R+atom313*atom309;
atom3 = cos(a);
atom316 = -atom308*atom315;
atom381 = 1.0/( endsR-stasR);
atom379 =  sR_R-stasR;
atom382 = atom381*atom379;
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
atom436 = 5.0000000000000000e-01*1.0/atom408*atom429*L_R;
atom438 =  5.0000000000000000e-01*atom405*atom434*L_R+atom436+1.0;
atom372 =  uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 =  bR_R+atom373;
atom443 =  atom374*atom372+cR_R+atom372*( atom374+atom373);
atom445 = -atom438*atom443;
atom444 = ( atom405+-5.0000000000000000e-01*atom434*L_R)*atom443;
atom451 = pow( (atom438*atom438)+(atom444*atom444)+(atom445*atom445),-(1.0/2.0));
atom454 = atom438*atom451;
atom5 = cos(c);
atom4 = sin(a);
atom147 = -atom5*atom4;
atom317 = cos(thetaW_R);
atom318 = atom315*atom317;
atom6 = sin(c);
atom453 = atom451*atom445;
atom145 = atom6*atom4;
atom452 = atom444*atom451;
atom350 =  atom313+( atom310+atom311)*atom309;
atom354 = atom350*atom317;
atom351 = -atom308*atom350;
atom146 = atom5*atom3;
atom144 = -atom6*atom3;
atom2086 =  atom381*( ( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)+atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)*atom379)*atom381*atom379+atom381*( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR))*atom379+atom381*( esR+atom381*( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR)*atom379);
atom2100 = -2.0*( atom381*( ( sR_R-stasR)*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*atom381+( sR_R-stasR)*(atom381*atom381)*asR)+atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR))*atom381+atom381*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR)+dsR))+atom381*( ( atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)+(atom381*atom381*atom381)*asR*atom379)*atom381*atom379+( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*atom381+( sR_R-stasR)*(atom381*atom381)*asR)+atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR))*atom381)*atom379)*pow( (atom2086*atom2086)+1.0,-(3.0/2.0))*atom2086;
atom564 =  sR_L-stasL;
atom566 = 1.0/( endsL-stasL);
atom567 = atom564*atom566;
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
atom557 =  uR_L-lR_L;
atom558 = aR_L*atom557;
atom559 =  bR_L+atom558;
atom628 =  atom559*atom557+cR_L+( atom559+atom558)*atom557;
atom620 = -5.0000000000000000e-01*1.0/atom593*atom614*L_R;
atom623 =  -5.0000000000000000e-01*atom590*L_R*atom619+atom620+1.0;
atom630 = -atom623*atom628;
atom629 = ( atom590+5.0000000000000000e-01*L_R*atom619)*atom628;
atom636 = pow( (atom623*atom623)+(atom629*atom629)+(atom630*atom630),-(1.0/2.0));
atom497 =  uW_L-lW_L;
atom498 = atom497*aW_L;
atom499 =  atom498+bW_L;
atom501 =  cW_L+atom497*atom499;
atom503 =  dW_L+atom497*atom501;
atom505 = cos(thetaW_L);
atom506 = atom503*atom505;
atom496 = sin(thetaW_L);
atom504 = -atom503*atom496;
atom637 = atom629*atom636;
atom638 = atom630*atom636;
atom639 = atom623*atom636;
atom535 =  atom501+atom497*( atom498+atom499);
atom538 = -atom535*atom496;
atom536 = atom535*atom505;
atom2160 =  ( esL+atom564*atom566*( atom564*atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+dsL))*atom566+atom564*( atom566*( atom564*atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+dsL)+atom564*( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566)*atom566;
atom2174 = -2.0*atom2160*( ( ( ( ( sR_L-stasL)*atom566*( bsL+( sR_L-stasL)*atom566*asL)+csL)*( sR_L-stasL)*atom566+dsL)*atom566+atom564*( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566)*atom566+( ( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566+( atom564*(atom566*atom566*atom566)*asL+( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom564*atom566)*atom564*atom566)*pow( (atom2160*atom2160)+1.0,-(3.0/2.0));

_dPhic_ds[0] =  atom3*atom454*atom316-( atom318*atom6-atom147*atom316)*atom453+atom452*( atom145*atom316-atom318*atom5);
_dPhic_ds[1] = 0.0000000000000000e+00;
_dPhic_ds[2] =  ( atom6*atom351+atom147*atom354+atom146)*atom453+atom452*( atom144+atom5*atom351+atom145*atom354)+atom454*( atom3*atom354+atom4);
_dPhic_ds[3] = 0.0000000000000000e+00;
_dPhic_ds[4] = -atom453-atom454*atom443;
_dPhic_ds[5] = 0.0000000000000000e+00;
_dPhic_ds[6] = -( atom405+-5.0000000000000000e-01*atom2100*L_R)*atom453-atom452*( 5.0000000000000000e-01*atom405*atom2100*L_R+atom436+1.0000000000000000e+00);
_dPhic_ds[7] = 0.0000000000000000e+00;
_dPhic_ds[8] = 0.0000000000000000e+00;
_dPhic_ds[9] = -( atom5*atom506-atom145*atom504)*atom637+atom3*atom639*atom504+atom638*( atom147*atom504-atom506*atom6);
_dPhic_ds[10] = 0.0000000000000000e+00;
_dPhic_ds[11] =  atom637*( atom144+atom5*atom538+atom145*atom536)+atom638*( atom147*atom536+atom538*atom6+atom146)+atom639*( atom3*atom536+atom4);
_dPhic_ds[12] = 0.0000000000000000e+00;
_dPhic_ds[13] = -atom638-atom639*atom628;
_dPhic_ds[14] = 0.0000000000000000e+00;
_dPhic_ds[15] = -atom637*( -5.0000000000000000e-01*atom590*atom2174*L_R+atom620+1.0000000000000000e+00)-atom638*( 5.0000000000000000e-01*atom2174*L_R+atom590);

return _dPhic_ds;
}

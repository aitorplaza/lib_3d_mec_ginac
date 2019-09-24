/*----------Phic.c lib3D_MEC exported-----------*/

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

#include "Phic.h"

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
double atom315;
double atom6;
double atom316;
double atom5;
double atom3;
double atom146;
double atom4;
double atom318;
double atom147;
double atom307;
double atom320;
double atom381;
double atom382;
double atom384;
double atom386;
double atom393;
double atom396;
double atom399;
double atom388;
double atom402;
double atom390;
double atom405;
double atom407;
double atom408;
double atom409;
double atom416;
double atom422;
double atom426;
double atom429;
double atom434;
double atom438;
double atom372;
double atom373;
double atom374;
double atom376;
double atom443;
double atom445;
double atom444;
double atom451;
double atom144;
double atom319;
double atom145;
double atom321;
double atom497;
double atom503;
double atom506;
double atom557;
double atom558;
double atom559;
double atom561;
double atom566;
double atom567;
double atom569;
double atom571;
double atom573;
double atom575;
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
double atom594;
double atom623;
double atom628;
double atom630;
double atom629;
double atom636;
double atom504;

double * _Phic = NULL;
void Init_Phic ( ) 
{
    _Phic = malloc ( Phic_n_rows * Phic_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Phic_n_rows * Phic_n_cols ; i++ ) {_Phic[i]=0.0;}
  }
}

void Done_Phic ( ) 
{
if (_Phic != NULL) 
free (_Phic ); 
_Phic = NULL; 
}


double * Phic ()
{
if ( _Phic == NULL )
 {
    _Phic = malloc ( Phic_n_rows * Phic_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Phic_n_rows * Phic_n_cols ; i++ ) {_Phic[i]=0.0;}
  }
 }

atom309 =  uW_R-lW_R;
atom315 =  atom309*( cW_R+( aW_R*atom309+bW_R)*atom309)+dW_R;
atom6 = sin(c);
atom316 = -atom315*sin(thetaW_R);
atom5 = cos(c);
atom3 = cos(a);
atom146 = atom5*atom3;
atom4 = sin(a);
atom318 = atom315*cos(thetaW_R);
atom147 = -atom5*atom4;
atom307 = -5.0000000000000000e-01*L_WHS;
atom320 = atom307*atom146;
atom381 = 1.0/( endsR-stasR);
atom382 = ( sR_R-stasR)*atom381;
atom384 =  bsR+atom382*asR;
atom386 =  atom382*atom384+csR;
atom393 = atom381*asR;
atom396 =  atom381*atom384+atom393*atom382;
atom399 =  atom382*atom396+atom386*atom381;
atom388 =  atom386*atom382+dsR;
atom402 =  atom399*atom382+atom381*atom388;
atom390 =  atom388*atom382+esR;
atom405 =  atom381*atom390+atom402*atom382;
atom407 =  (atom405*atom405)+1.0;
atom408 = pow(atom407,(1.0/2.0));
atom409 = 1.0/(atom408);
atom416 = atom381*atom396;
atom422 = atom381*atom399;
atom426 = atom381*atom402;
atom429 =  2.0*atom426+2.0*( atom422+( atom393*atom381*atom382+atom416)*atom382)*atom382;
atom434 = -1.0/(atom408*atom408)*atom429*atom405*pow(atom407,-(1.0/2.0));
atom438 =  5.0000000000000000e-01*atom405*atom434*L_R+5.0000000000000000e-01*atom429*atom409*L_R+1.0;
atom372 =  uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 =  bR_R+atom373;
atom376 =  atom374*atom372+cR_R;
atom443 =  atom376+atom372*( atom374+atom373);
atom445 = -atom438*atom443;
atom444 = ( atom405+-5.0000000000000000e-01*atom434*L_R)*atom443;
atom451 = pow( (atom438*atom438)+(atom444*atom444)+(atom445*atom445),-(1.0/2.0));
atom144 = -atom6*atom3;
atom319 = atom144*atom307;
atom145 = atom6*atom4;
atom321 = atom307*atom4;
atom497 =  uW_L-lW_L;
atom503 =  dW_L+atom497*( atom497*( atom497*aW_L+bW_L)+cW_L);
atom506 = cos(thetaW_L)*atom503;
atom557 =  uR_L-lR_L;
atom558 = aR_L*atom557;
atom559 =  bR_L+atom558;
atom561 =  atom559*atom557+cR_L;
atom566 = 1.0/( endsL-stasL);
atom567 = ( sR_L-stasL)*atom566;
atom569 =  bsL+atom567*asL;
atom571 =  atom567*atom569+csL;
atom573 =  atom567*atom571+dsL;
atom575 =  esL+atom567*atom573;
atom578 = atom566*asL;
atom581 =  atom567*atom578+atom569*atom566;
atom584 =  atom571*atom566+atom581*atom567;
atom587 =  atom573*atom566+atom584*atom567;
atom590 =  atom575*atom566+atom567*atom587;
atom592 =  (atom590*atom590)+1.0;
atom593 = pow(atom592,(1.0/2.0));
atom605 = atom581*atom566;
atom609 = atom584*atom566;
atom601 = atom587*atom566;
atom614 =  2.0*( atom567*( atom605+atom567*atom578*atom566)+atom609)*atom567+2.0*atom601;
atom619 = -1.0/(atom593*atom593)*atom614*atom590*pow(atom592,-(1.0/2.0));
atom594 = 1.0/(atom593);
atom623 =  -5.0000000000000000e-01*atom614*atom594*L_R+-5.0000000000000000e-01*atom590*L_R*atom619+1.0;
atom628 =  atom561+( atom559+atom558)*atom557;
atom630 = -atom623*atom628;
atom629 = ( atom590+5.0000000000000000e-01*L_R*atom619)*atom628;
atom636 = pow( (atom623*atom623)+(atom629*atom629)+(atom630*atom630),-(1.0/2.0));
atom504 = -atom503*sin(thetaW_L);

_Phic[0] = -atom444*atom451*( sR_R-atom5*atom316-atom318*atom145-uW_R*atom144-x-atom319+5.0000000000000000e-01*atom405*atom409*L_R)-( uR_R-atom320+fsR-y+-5.0000000000000000e-01*atom409*L_R-uW_R*atom146-atom6*atom316-atom318*atom147+atom390*atom382)*atom451*atom445-atom438*atom451*( atom372*atom376-z+usRz-uW_R*atom4+dR_R-atom321-atom318*atom3);
_Phic[1] = -atom630*atom636*( atom320+5.0000000000000000e-01*atom594*L_R+uR_L-y+fsL-uW_L*atom146-atom506*atom147-atom6*atom504+atom567*atom575)-( dR_L-z+usLz+atom557*atom561-uW_L*atom4+atom321-atom506*atom3)*atom623*atom636+( atom5*atom504+atom506*atom145+5.0000000000000000e-01*atom590*atom594*L_R-sR_L+x+atom144*uW_L-atom319)*atom629*atom636;

return _Phic;
}

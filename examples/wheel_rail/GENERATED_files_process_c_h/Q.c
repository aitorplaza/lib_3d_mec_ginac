/*----------Q.c lib3D_MEC exported-----------*/

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

#include "Q.h"

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
double atom10;
double atom469;
double atom11;
double atom372;
double atom373;
double atom374;
double atom443;
double atom462;
double atom471;
double atom7;
double atom12;
double atom468;
double atom820;
double atom815;
double atom14;
double atom825;
double atom830;
double atom557;
double atom558;
double atom559;
double atom628;
double atom647;
double atom653;
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
double atom654;
double atom952;
double atom656;
double atom957;
double atom962;
double atom967;
double atom833;
double atom970;
double atom497;
double atom503;
double atom5;
double atom4;
double atom506;
double atom147;
double atom6;
double atom504;
double atom3;
double atom146;
double atom307;
double atom320;
double atom923;
double atom321;
double atom924;
double atom144;
double atom145;
double atom319;
double atom922;
double atom1024;
double atom309;
double atom315;
double atom316;
double atom318;
double atom780;
double atom781;
double atom779;
double atom887;
double atom28;
double atom445;
double atom444;
double atom451;
double atom474;
double atom473;
double atom472;
double atom43;
double atom812;
double atom16;
double atom802;
double atom31;
double atom22;
double atom807;
double atom37;
double atom1;
double atom1158;
double atom2;
double atom1161;
double atom1164;
double atom758;
double atom759;
double atom760;
double atom1279;
double atom765;
double atom838;
double atom630;
double atom629;
double atom636;
double atom658;
double atom657;
double atom659;
double atom949;
double atom939;
double atom944;
double atom975;
double atom71;
double atom156;
double atom159;
double atom72;
double atom1382;
double atom1376;
double atom150;
double atom153;
double atom1389;
double atom46;
double atom25;
double atom64;
double atom19;
double atom40;
double atom58;
double atom15;
double atom34;
double atom52;
double atom1454;
double atom55;
double atom49;
double atom61;
double atom1449;
double atom1361;
double atom1356;
double atom1157;
double atom1165;
double atom1280;
double atom1278;
double atom1313;
double atom1308;
double atom1410;
double atom1406;
double atom1415;

double * _Q = NULL;
void Init_Q ( ) 
{
    _Q = malloc ( Q_n_rows * Q_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Q_n_rows * Q_n_cols ; i++ ) {_Q[i]=0.0;}
  }
}

void Done_Q ( ) 
{
if (_Q != NULL) 
free (_Q ); 
_Q = NULL; 
}


double * Q ()
{
if ( _Q == NULL )
 {
    _Q = malloc ( Q_n_rows * Q_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Q_n_rows * Q_n_cols ; i++ ) {_Q[i]=0.0;}
  }
 }

atom9 = cos(a_pend);
atom8 = sin(b_pend);
atom13 = -atom9*atom8;
atom65 = -mWHS*g;
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
atom10 = sin(a_pend);
atom469 = atom457*atom438*Fx_R;
atom11 = atom10*atom8;
atom372 =  uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 =  bR_R+atom373;
atom443 =  atom374*atom372+cR_R+atom372*( atom374+atom373);
atom462 = pow( (atom443*atom443)+1.0,-(1.0/2.0));
atom471 =  atom457*Fx_R*atom440+Fy_R*atom462;
atom7 = cos(b_pend);
atom12 = -atom10*atom7;
atom468 = Fy_R*atom462*atom443;
atom820 =  atom471*atom9+atom12*atom468+atom469*atom11;
atom815 =  atom468*atom8+atom469*atom7;
atom14 = atom9*atom7;
atom825 =  atom469*atom13+atom14*atom468+atom471*atom10;
atom830 =  atom13*atom825+atom7*atom815+atom820*atom11;
atom557 =  uR_L-lR_L;
atom558 = aR_L*atom557;
atom559 =  bR_L+atom558;
atom628 =  atom559*atom557+cR_L+( atom559+atom558)*atom557;
atom647 = pow( (atom628*atom628)+1.0,-(1.0/2.0));
atom653 = atom647*Fy_L*atom628;
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
atom654 = atom642*Fx_L*atom623;
atom952 =  atom653*atom8+atom654*atom7;
atom656 =  atom625*atom642*Fx_L+atom647*Fy_L;
atom957 =  atom9*atom656+atom654*atom11+atom12*atom653;
atom962 =  atom13*atom654+atom10*atom656+atom14*atom653;
atom967 =  atom952*atom7+atom13*atom962+atom11*atom957;
atom833 =  atom825*atom10+atom9*atom820;
atom970 =  atom10*atom962+atom9*atom957;
atom497 =  uW_L-lW_L;
atom503 =  dW_L+atom497*( atom497*( atom497*aW_L+bW_L)+cW_L);
atom5 = cos(c);
atom4 = sin(a);
atom506 = cos(thetaW_L)*atom503;
atom147 = -atom5*atom4;
atom6 = sin(c);
atom504 = -atom503*sin(thetaW_L);
atom3 = cos(a);
atom146 = atom5*atom3;
atom307 = -5.0000000000000000e-01*L_WHS;
atom320 = atom307*atom146;
atom923 = -atom320+uW_L*atom146+atom506*atom147+atom6*atom504;
atom321 = atom307*atom4;
atom924 =  uW_L*atom4-atom321+atom506*atom3;
atom144 = -atom6*atom3;
atom145 = atom6*atom4;
atom319 = atom144*atom307;
atom922 =  atom5*atom504+atom506*atom145+atom144*uW_L-atom319;
atom1024 =  atom952*atom8+atom14*atom962+atom12*atom957;
atom309 =  uW_R-lW_R;
atom315 =  atom309*( cW_R+( aW_R*atom309+bW_R)*atom309)+dW_R;
atom316 = -atom315*sin(thetaW_R);
atom318 = atom315*cos(thetaW_R);
atom780 =  atom320+uW_R*atom146+atom6*atom316+atom318*atom147;
atom781 =  uW_R*atom4+atom321+atom318*atom3;
atom779 =  atom5*atom316+atom318*atom145+uW_R*atom144+atom319;
atom887 =  atom14*atom825+atom12*atom820+atom815*atom8;
atom28 = -atom13*atom6+atom5*atom10;
atom445 = -atom438*atom443;
atom444 = atom443*atom440;
atom451 = pow( (atom444*atom444)+(atom445*atom445)+atom449,-(1.0/2.0));
atom474 = Mz_R*atom438*atom451;
atom473 = Mz_R*atom451*atom445;
atom472 = atom444*Mz_R*atom451;
atom43 =  atom28*atom3+atom14*atom4;
atom812 =  atom13*atom472+atom10*atom473+atom474*atom14;
atom16 = -atom6*atom7;
atom802 =  atom474*atom8+atom7*atom472;
atom31 =  atom16*atom3+atom4*atom8;
atom22 = -atom6*atom11+atom5*atom9;
atom807 =  atom11*atom472+atom474*atom12+atom9*atom473;
atom37 =  atom22*atom3+atom12*atom4;
atom1 = cos(b);
atom1158 = atom3*dc;
atom2 = sin(b);
atom1161 = -atom1158*atom2+atom1*da;
atom1164 =  atom1*atom1158+atom2*da;
atom758 = tor*atom31;
atom759 = tor*atom37;
atom760 = tor*atom43;
atom1279 =  atom1164*atom1161*I_WHSx+atom1158*da*I_WHSy-atom1164*I_WHSz*atom1161;
atom765 =  atom759*atom37+atom43*atom760+atom758*atom31;
atom838 =  atom802*atom31+atom807*atom37+atom43*atom812;
atom630 = -atom623*atom628;
atom629 = atom625*atom628;
atom636 = pow( atom634+(atom629*atom629)+(atom630*atom630),-(1.0/2.0));
atom658 = atom630*Mz_L*atom636;
atom657 = Mz_L*atom629*atom636;
atom659 = Mz_L*atom623*atom636;
atom949 =  atom10*atom658+atom657*atom13+atom14*atom659;
atom939 =  atom659*atom8+atom657*atom7;
atom944 =  atom657*atom11+atom9*atom658+atom12*atom659;
atom975 =  atom944*atom37+atom949*atom43+atom939*atom31;
atom71 = -atom2*atom3;
atom156 =  atom1*atom6-atom2*atom147;
atom159 =  atom2*atom6+atom1*atom147;
atom72 = atom1*atom3;
atom1382 =  atom4*atom146+atom159*atom72+atom71*atom156;
atom1376 =  (atom4*atom4)+(atom71*atom71)+(atom72*atom72);
atom150 = -atom2*atom145+atom5*atom1;
atom153 =  atom5*atom2+atom1*atom145;
atom1389 =  atom144*atom4+atom72*atom153+atom71*atom150;
atom46 = -atom28*atom4+atom14*atom3;
atom25 =  atom5*atom13+atom10*atom6;
atom64 =  atom25*atom2+atom1*atom46;
atom19 =  atom5*atom11+atom9*atom6;
atom40 =  atom12*atom3-atom22*atom4;
atom58 =  atom1*atom40+atom2*atom19;
atom15 = atom5*atom7;
atom34 =  atom3*atom8-atom16*atom4;
atom52 =  atom2*atom15+atom34*atom1;
atom1454 =  atom949*atom64+atom52*atom939+atom58*atom944;
atom55 = -atom2*atom40+atom1*atom19;
atom49 = -atom34*atom2+atom1*atom15;
atom61 =  atom1*atom25-atom2*atom46;
atom1449 =  atom939*atom49+atom55*atom944+atom61*atom949;
atom1361 =  atom802*atom52+atom807*atom58+atom64*atom812;
atom1356 =  atom807*atom55+atom61*atom812+atom802*atom49;
atom1157 = dc*atom4;
atom1165 =  db+atom1157;
atom1280 = -atom1161*I_WHSx*atom1165+atom1161*atom1165*I_WHSy+I_WHSz*( atom1161*db-atom1*da*atom1157);
atom1278 =  atom1164*I_WHSz*atom1165+( atom2*da*atom1157-atom1164*db)*I_WHSx-atom1164*atom1165*I_WHSy;
atom1313 =  atom759*atom58+atom52*atom758+atom760*atom64;
atom1308 =  atom61*atom760+atom49*atom758+atom759*atom55;
atom1410 =  atom1*atom156+atom2*atom159;
atom1406 =  atom2*atom72+atom1*atom71;
atom1415 =  atom1*atom150+atom2*atom153;

_Q[0] = -atom830-atom967-atom13*atom65;
_Q[1] = -atom10*atom65-atom833-atom970;
_Q[2] =  ( atom4*atom780-atom781*atom146)*atom830+atom1279+atom967*( atom4*atom923-atom924*atom146)-atom765-atom970*( atom922*atom4-atom924*atom144)-( atom144*atom923-atom922*atom146)*atom1024-atom833*( atom779*atom4-atom781*atom144)-atom838-atom887*( atom144*atom780-atom779*atom146)-atom975;
_Q[3] = -( atom1376*atom922-atom924*atom1389)*atom970+atom1279*atom4-atom887*( atom1389*atom780-atom1382*atom779)-atom967*( atom924*atom1382-atom1376*atom923)-atom830*( atom781*atom1382-atom1376*atom780)-atom4*atom975-atom1449*atom71-atom1454*atom72-atom72*atom1313-atom838*atom4+atom72*atom1280+atom1278*atom71-atom765*atom4-( atom1389*atom923-atom1382*atom922)*atom1024-atom1308*atom71+atom833*( atom781*atom1389-atom1376*atom779)-atom1361*atom72-atom1356*atom71;
_Q[4] = -atom887-atom14*atom65-atom1024;
_Q[5] = -( atom924*atom1410-atom1406*atom923)*atom967+atom833*( atom781*atom1415-atom1406*atom779)-atom2*atom1313+atom970*( atom924*atom1415-atom1406*atom922)-atom1361*atom2+atom2*atom1280-atom887*( atom780*atom1415-atom1410*atom779)-atom1*atom1356+atom1*atom1278+( atom1406*atom780-atom781*atom1410)*atom830+atom1024*( atom1410*atom922-atom923*atom1415)-atom1454*atom2-atom1*atom1449-atom1308*atom1;

return _Q;
}

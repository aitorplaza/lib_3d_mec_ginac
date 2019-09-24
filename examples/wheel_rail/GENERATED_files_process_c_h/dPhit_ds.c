/*----------dPhit_ds.c lib3D_MEC exported-----------*/

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

#include "dPhit_ds.h"

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
double atom379;
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
double atom418;
double atom416;
double atom421;
double atom422;
double atom425;
double atom426;
double atom429;
double atom431;
double atom430;
double atom408;
double atom432;
double atom433;
double atom434;
double atom440;
double atom409;
double atom436;
double atom438;
double atom449;
double atom457;
double atom5;
double atom4;
double atom309;
double atom310;
double atom311;
double atom313;
double atom308;
double atom315;
double atom147;
double atom316;
double atom317;
double atom318;
double atom6;
double atom459;
double atom346;
double atom145;
double atom343;
double atom458;
double atom348;
double atom350;
double atom351;
double atom3;
double atom146;
double atom354;
double atom360;
double atom144;
double atom356;
double atom2096;
double atom2099;
double atom2085;
double atom2074;
double atom2086;
double atom2087;
double atom2088;
double atom2220;
double atom2089;
double atom2229;
double atom2232;
double atom2234;
double atom2236;
double atom2238;
double atom2241;
double atom2247;
double atom2248;
double atom2250;
double atom2251;
double atom2254;
double atom2100;
double atom2257;
double atom2256;
double atom2255;
double atom2267;
double atom2279;
double atom2294;
double atom307;
double atom319;
double atom325;
double atom328;
double atom330;
double atom333;
double atom320;
double atom2281;
double atom465;
double atom2111;
double atom372;
double atom373;
double atom374;
double atom441;
double atom375;
double atom376;
double atom443;
double atom462;
double atom347;
double atom463;
double atom362;
double atom2315;
double atom2320;
double atom2321;
double atom1075;
double atom321;
double atom336;
double atom445;
double atom444;
double atom451;
double atom454;
double atom452;
double atom453;
double atom2316;
double atom2365;
double atom2369;
double atom2370;
double atom2380;
double atom2375;
double atom2387;
double atom2390;
double atom2400;
double atom2395;
double atom2419;
double atom2420;
double atom2423;
double atom497;
double atom498;
double atom499;
double atom501;
double atom503;
double atom505;
double atom506;
double atom496;
double atom504;
double atom564;
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
double atom603;
double atom605;
double atom607;
double atom609;
double atom611;
double atom601;
double atom614;
double atom615;
double atom616;
double atom618;
double atom617;
double atom619;
double atom625;
double atom594;
double atom620;
double atom623;
double atom634;
double atom642;
double atom531;
double atom644;
double atom643;
double atom528;
double atom533;
double atom535;
double atom538;
double atom536;
double atom541;
double atom545;
double atom2155;
double atom2156;
double atom2159;
double atom2173;
double atom2160;
double atom2174;
double atom2184;
double atom2458;
double atom2462;
double atom2467;
double atom2470;
double atom2480;
double atom2482;
double atom2161;
double atom2162;
double atom2484;
double atom2493;
double atom2495;
double atom2486;
double atom2504;
double atom2510;
double atom2502;
double atom2513;
double atom2514;
double atom2517;
double atom515;
double atom518;
double atom650;
double atom510;
double atom513;
double atom2530;
double atom557;
double atom558;
double atom559;
double atom626;
double atom560;
double atom561;
double atom628;
double atom647;
double atom532;
double atom648;
double atom547;
double atom521;
double atom1130;
double atom2553;
double atom2549;
double atom2557;
double atom630;
double atom629;
double atom636;
double atom639;
double atom638;
double atom637;
double atom2554;
double atom2605;
double atom2606;
double atom2609;
double atom2614;
double atom2617;
double atom2624;
double atom2637;
double atom2632;
double atom2627;
double atom2655;
double atom2656;
double atom2658;
double atom2361;
double atom2597;

double * _dPhit_ds = NULL;
void Init_dPhit_ds ( ) 
{
    _dPhit_ds = malloc ( dPhit_ds_n_rows * dPhit_ds_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhit_ds_n_rows * dPhit_ds_n_cols ; i++ ) {_dPhit_ds[i]=0.0;}
  }
}

void Done_dPhit_ds ( ) 
{
if (_dPhit_ds != NULL) 
free (_dPhit_ds ); 
_dPhit_ds = NULL; 
}


double * dPhit_ds ()
{
if ( _dPhit_ds == NULL )
 {
    _dPhit_ds = malloc ( dPhit_ds_n_rows * dPhit_ds_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhit_ds_n_rows * dPhit_ds_n_cols ; i++ ) {_dPhit_ds[i]=0.0;}
  }
 }

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
atom390 =  atom388*atom382+esR;
atom405 =  atom381*atom390+atom402*atom382;
atom407 =  (atom405*atom405)+1.0;
atom418 = 2.0*atom393*atom381;
atom416 = atom381*atom396;
atom421 =  atom418*atom382+2.0*atom416;
atom422 = atom381*atom399;
atom425 =  2.0*atom422+atom421*atom382;
atom426 = atom381*atom402;
atom429 =  2.0*atom426+atom382*atom425;
atom431 = pow(atom407,-(1.0/2.0));
atom430 = 2.0*atom429*atom405;
atom408 = pow(atom407,(1.0/2.0));
atom432 = (1.0/2.0)*atom431*atom430;
atom433 = 1.0/(atom408*atom408);
atom434 = -atom432*atom433;
atom440 =  atom405+-5.0000000000000000e-01*atom434*L_R;
atom409 = 1.0/(atom408);
atom436 = 5.0000000000000000e-01*atom429*atom409*L_R;
atom438 =  5.0000000000000000e-01*atom405*atom434*L_R+atom436+1.0;
atom449 = (atom438*atom438);
atom457 = pow( (atom440*atom440)+atom449,-(1.0/2.0));
atom5 = cos(c);
atom4 = sin(a);
atom309 =  uW_R-lW_R;
atom310 = aW_R*atom309;
atom311 =  bW_R+atom310;
atom313 =  atom309*atom311+cW_R;
atom308 = sin(thetaW_R);
atom315 =  dW_R+atom313*atom309;
atom147 = -atom5*atom4;
atom316 = -atom308*atom315;
atom317 = cos(thetaW_R);
atom318 = atom315*atom317;
atom6 = sin(c);
atom459 = atom457*atom440;
atom346 = -atom318*atom6+atom147*atom316;
atom145 = atom6*atom4;
atom343 =  atom145*atom316-atom318*atom5;
atom458 = atom457*atom438;
atom348 =  atom310+atom311;
atom350 =  atom313+atom309*atom348;
atom351 = -atom308*atom350;
atom3 = cos(a);
atom146 = atom5*atom3;
atom354 = atom350*atom317;
atom360 =  atom6*atom351+atom147*atom354+atom146;
atom144 = -atom6*atom3;
atom356 =  atom144+atom5*atom351+atom145*atom354;
atom2096 =  ( atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)+(atom381*atom381*atom381)*asR*atom379)*atom381*atom379+( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*atom381+( sR_R-stasR)*(atom381*atom381)*asR)+atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR))*atom381;
atom2099 =  atom381*atom2096*atom379+atom381*( ( sR_R-stasR)*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*atom381+( sR_R-stasR)*(atom381*atom381)*asR)+atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR))*atom381+atom381*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR)+dsR));
atom2085 = atom381*( ( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)+atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)*atom379)*atom381*atom379+atom381*( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR))*atom379;
atom2074 = atom381*( esR+atom381*( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR)*atom379);
atom2086 =  atom2085+atom2074;
atom2087 = (atom2086*atom2086);
atom2088 =  atom2087+1.0;
atom2220 = (atom2099*atom2099);
atom2089 = pow(atom2088,-(3.0/2.0));
atom2229 =  atom381*( ((atom381*atom381)*(atom381*atom381))*asR*atom379+( atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)+(atom381*atom381*atom381)*asR*atom379)*atom381)*atom379+atom381*atom2096;
atom2232 = pow(atom2088,-(5.0/2.0));
atom2234 =  2.0*atom381*atom2096*atom379+2.0*L_R*atom2220*atom2089+2.0*atom381*( ( sR_R-stasR)*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*atom381+( sR_R-stasR)*(atom381*atom381)*asR)+atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR))*atom381+atom381*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR)+dsR))+-6.0*atom2232*atom2087*L_R*atom2220+3.0*L_R*atom2089*atom2086*atom2229;
atom2236 =  atom2085+L_R*atom2089*atom2086*atom2099+atom2074;
atom2238 = pow(atom2088,-(1.0/2.0));
atom2241 =  atom2238*L_R*atom2099-atom2087*L_R*atom2089*atom2099+1.0;
atom2247 =  3.0*atom2238*L_R*atom2229+6.0000000000000000e+00*atom2232*L_R*atom2220*(atom2086*atom2086*atom2086)+-3.0000000000000000e+00*atom2087*L_R*atom2089*atom2229+-6.0000000000000000e+00*L_R*atom2220*atom2089*atom2086;
atom2248 = atom2241*atom2247;
atom2250 = (atom2236*atom2236);
atom2251 = (atom2241*atom2241);
atom2254 = -pow( atom2250+atom2251,-(3.0/2.0))*( atom2248+atom2234*atom2236);
atom2100 = -2.0*atom2089*atom2086*atom2099;
atom2257 = atom381*atom418;
atom2256 = atom381*atom421;
atom2255 = atom381*atom425;
atom2267 =  3.0*atom2255+3.0*( atom2257*atom382+atom2256)*atom382;
atom2279 = -( ( 2.0*atom2267*atom405+2.0*(atom429*atom429))*atom431+atom2100*atom430)*atom433/2.0+4.0*1.0/(atom2088*atom2088)*atom432*atom2086*atom2099;
atom2294 =  5.0000000000000000e-01*atom405*atom2279*L_R+5.0000000000000000e-01*atom429*atom434*L_R+5.0000000000000000e-01*atom429*atom2100*L_R+5.0000000000000000e-01*atom2267*atom409*L_R;
atom307 = -5.0000000000000000e-01*L_WHS;
atom319 = atom144*atom307;
atom325 = atom5*atom316;
atom328 = atom318*atom145;
atom330 = atom6*atom316;
atom333 = atom318*atom147;
atom320 = atom307*atom146;
atom2281 =  atom429+-5.0000000000000000e-01*atom2279*L_R;
atom465 =  atom330-uR_R+atom320-fsR+y+5.0000000000000000e-01*atom409*L_R+uW_R*atom146+atom333-atom390*atom382;
atom2111 =  atom405+-5.0000000000000000e-01*atom2100*L_R;
atom372 =  uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 =  bR_R+atom373;
atom441 =  atom374+atom373;
atom375 = atom374*atom372;
atom376 =  cR_R+atom375;
atom443 =  atom376+atom372*atom441;
atom462 = pow( (atom443*atom443)+1.0,-(1.0/2.0));
atom347 = atom3*atom316;
atom463 = atom462*atom443;
atom362 =  atom3*atom354+atom4;
atom2315 =  atom372*( bR_R+2.0*atom372*aR_R)+cR_R+atom375;
atom2320 =  bR_R+3.0*atom372*aR_R;
atom2321 = -2.0*atom2315*pow( (atom2315*atom2315)+1.0,-(3.0/2.0))*atom2320;
atom1075 =  2.0*atom372*aR_R+2.0*atom441;
atom321 = atom307*atom4;
atom336 = atom318*atom3;
atom445 = -atom438*atom443;
atom444 = atom443*atom440;
atom451 = pow( (atom444*atom444)+(atom445*atom445)+atom449,-(1.0/2.0));
atom454 = atom438*atom451;
atom452 = atom444*atom451;
atom453 = atom451*atom445;
atom2316 = (atom2315*atom2315);
atom2365 = pow( atom2250*atom2316+atom2251+atom2251*atom2316,-(3.0/2.0));
atom2369 = -2.0*atom2365*( atom2315*atom2250*atom2320+atom2315*atom2320*atom2251);
atom2370 = atom2369*atom438;
atom2380 =  atom444*atom2369+atom1075*atom451*atom440;
atom2375 =  atom2369*atom445-atom1075*atom438*atom451;
atom2387 = -( atom2234*atom2316*atom2236+atom2248+atom2241*atom2247*atom2316)*atom2365;
atom2390 =  atom2294*atom451+atom2387*atom438;
atom2400 =  atom444*atom2387+atom451*atom443*atom2281;
atom2395 = -atom2294*atom451*atom443+atom2387*atom445;
atom2419 =  2.0000000000000000e+00*aW_R*atom309+2.0*atom348;
atom2420 = atom2419*atom317;
atom2423 = -atom308*atom2419;
atom497 =  uW_L-lW_L;
atom498 = atom497*aW_L;
atom499 =  atom498+bW_L;
atom501 =  cW_L+atom497*atom499;
atom503 =  dW_L+atom497*atom501;
atom505 = cos(thetaW_L);
atom506 = atom503*atom505;
atom496 = sin(thetaW_L);
atom504 = -atom503*atom496;
atom564 =  sR_L-stasL;
atom566 = 1.0/( endsL-stasL);
atom567 = atom564*atom566;
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
atom603 = 2.0*atom578*atom566;
atom605 = atom581*atom566;
atom607 =  atom603*atom567+2.0*atom605;
atom609 = atom584*atom566;
atom611 =  atom607*atom567+2.0*atom609;
atom601 = atom587*atom566;
atom614 =  2.0*atom601+atom567*atom611;
atom615 = 2.0*atom614*atom590;
atom616 = pow(atom592,-(1.0/2.0));
atom618 = 1.0/(atom593*atom593);
atom617 = (1.0/2.0)*atom615*atom616;
atom619 = -atom618*atom617;
atom625 =  atom590+5.0000000000000000e-01*L_R*atom619;
atom594 = 1.0/(atom593);
atom620 = -5.0000000000000000e-01*atom614*atom594*L_R;
atom623 =  -5.0000000000000000e-01*atom590*L_R*atom619+atom620+1.0;
atom634 = (atom623*atom623);
atom642 = pow( atom634+(atom625*atom625),-(1.0/2.0));
atom531 =  atom147*atom504-atom506*atom6;
atom644 = atom625*atom642;
atom643 = atom642*atom623;
atom528 = -atom5*atom506+atom145*atom504;
atom533 =  atom498+atom499;
atom535 =  atom497*atom533+atom501;
atom538 = -atom535*atom496;
atom536 = atom535*atom505;
atom541 =  atom144+atom5*atom538+atom145*atom536;
atom545 =  atom147*atom536+atom538*atom6+atom146;
atom2155 =  ( ( ( sR_L-stasL)*atom566*( bsL+( sR_L-stasL)*atom566*asL)+csL)*( sR_L-stasL)*atom566+dsL)*atom566+atom564*( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566;
atom2156 = atom564*( atom566*( atom564*atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+dsL)+atom564*( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566)*atom566;
atom2159 = ( esL+atom564*atom566*( atom564*atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+dsL))*atom566;
atom2173 =  atom2155*atom566+( ( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566+( atom564*(atom566*atom566*atom566)*asL+( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom564*atom566)*atom564*atom566;
atom2160 =  atom2156+atom2159;
atom2174 = -2.0*atom2173*atom2160*pow( (atom2160*atom2160)+1.0,-(3.0/2.0));
atom2184 =  5.0000000000000000e-01*atom2174*L_R+atom590;
atom2458 = atom603*atom566;
atom2462 = atom607*atom566;
atom2467 = atom611*atom566;
atom2470 =  3.0*atom2467+3.0*atom567*( atom567*atom2458+atom2462);
atom2480 =  4.0*atom2173*atom2160*atom617/pow( (atom2160*atom2160)+1.0,2.0)-atom618*( ( 2.0*atom2470*atom590+2.0*(atom614*atom614))*atom616+atom615*atom2174)/2.0;
atom2482 =  atom614+5.0000000000000000e-01*L_R*atom2480;
atom2161 = (atom2160*atom2160);
atom2162 =  atom2161+1.0;
atom2484 = pow(atom2162,-(1.0/2.0));
atom2493 =  atom564*( atom564*((atom566*atom566)*(atom566*atom566))*asL+( atom564*(atom566*atom566*atom566)*asL+( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566)*atom566+( ( ( ( sR_L-stasL)*(atom566*atom566)*asL+atom566*( bsL+( sR_L-stasL)*atom566*asL))*( sR_L-stasL)*atom566+( ( sR_L-stasL)*atom566*( bsL+( sR_L-stasL)*atom566*asL)+csL)*atom566)*atom566+( sR_L-stasL)*atom566*( ( sR_L-stasL)*(atom566*atom566*atom566)*asL+( ( sR_L-stasL)*(atom566*atom566)*asL+atom566*( bsL+( sR_L-stasL)*atom566*asL))*atom566))*atom566;
atom2495 = (atom2173*atom2173);
atom2486 =  atom2173*pow( atom2161+1.0,-(3.0/2.0))*L_R*atom2161-atom2173*atom2484*L_R+1.0;
atom2504 =  atom2156-pow( pow( atom2156+atom2159,2.0)+1.0,-(3.0/2.0))*( atom2156+atom2159)*( ( sR_L-stasL)/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)+( sR_L-stasL)/pow( endsL-stasL,2.0)*asL)+1.0/( endsL-stasL)*( csL+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)))/( endsL-stasL)+( 1.0/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)+( sR_L-stasL)/pow( endsL-stasL,2.0)*asL)+( sR_L-stasL)/pow( endsL-stasL,3.0)*asL)*( sR_L-stasL)/( endsL-stasL))+( 1.0/( endsL-stasL)*( ( sR_L-stasL)/( endsL-stasL)*( csL+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL))+dsL)+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)+( sR_L-stasL)/pow( endsL-stasL,2.0)*asL)+1.0/( endsL-stasL)*( csL+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)))/( endsL-stasL))/( endsL-stasL))*L_R+atom2159;
atom2510 =  2.0*atom2155*atom566+-3.0000000000000000e+00*atom2160*L_R*pow( (atom2160*atom2160)+1.0,-(3.0/2.0))*atom2493+-2.0000000000000000e+00*atom2495*pow(atom2162,-(3.0/2.0))*L_R+6.0000000000000000e+00*atom2495*pow( atom2161+1.0,-(5.0/2.0))*L_R*atom2161+2.0*( ( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566+( atom564*(atom566*atom566*atom566)*asL+( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom564*atom566)*atom564*atom566;
atom2502 = atom2486*( -3.0000000000000000e+00*atom2484*L_R*atom2493+6.0000000000000000e+00*atom2495*atom2160*L_R*pow( (atom2160*atom2160)+1.0,-(3.0/2.0))+3.0*pow( atom2161+1.0,-(3.0/2.0))*L_R*atom2493*atom2161+-6.0*atom2495*(atom2160*atom2160*atom2160)*pow(atom2162,-(5.0/2.0))*L_R);
atom2513 = (atom2504*atom2504);
atom2514 = (atom2486*atom2486);
atom2517 = -pow( atom2513+atom2514,-(3.0/2.0))*( atom2504*atom2510+atom2502);
atom515 = atom6*atom504;
atom518 = atom506*atom147;
atom650 = -atom320+atom518+atom515+-5.0000000000000000e-01*atom594*L_R-uR_L+y-fsL+uW_L*atom146-atom567*atom575;
atom510 = atom5*atom504;
atom513 = atom506*atom145;
atom2530 =  -5.0000000000000000e-01*atom614*atom2174*L_R+-5.0000000000000000e-01*atom614*L_R*atom619+-5.0000000000000000e-01*atom2470*atom594*L_R+-5.0000000000000000e-01*atom590*L_R*atom2480;
atom557 =  uR_L-lR_L;
atom558 = aR_L*atom557;
atom559 =  bR_L+atom558;
atom626 =  atom559+atom558;
atom560 = atom559*atom557;
atom561 =  atom560+cR_L;
atom628 =  atom557*atom626+atom561;
atom647 = pow( (atom628*atom628)+1.0,-(1.0/2.0));
atom532 = atom3*atom504;
atom648 = atom647*atom628;
atom547 =  atom3*atom536+atom4;
atom521 = atom506*atom3;
atom1130 =  2.0*aR_L*atom557+2.0*atom626;
atom2553 =  atom560+( 2.0*aR_L*atom557+bR_L)*atom557+cR_L;
atom2549 =  3.0*aR_L*atom557+bR_L;
atom2557 = -2.0*atom2553*atom2549*pow( (atom2553*atom2553)+1.0,-(3.0/2.0));
atom630 = -atom623*atom628;
atom629 = atom625*atom628;
atom636 = pow( atom634+(atom629*atom629)+(atom630*atom630),-(1.0/2.0));
atom639 = atom623*atom636;
atom638 = atom630*atom636;
atom637 = atom629*atom636;
atom2554 = (atom2553*atom2553);
atom2605 = pow( atom2554*atom2514+atom2513*atom2554+atom2514,-(3.0/2.0));
atom2606 = -2.0*( atom2553*atom2549*atom2514+atom2513*atom2553*atom2549)*atom2605;
atom2609 =  atom629*atom2606+atom1130*atom625*atom636;
atom2614 =  atom630*atom2606-atom1130*atom623*atom636;
atom2617 = atom623*atom2606;
atom2624 = -atom2605*( atom2502*pow( ( bR_L+2.0*aR_L*( uR_L-lR_L))*( uR_L-lR_L)+( bR_L+aR_L*( uR_L-lR_L))*( uR_L-lR_L)+cR_L,2.0)+atom2502+atom2554*atom2504*atom2510);
atom2637 =  atom636*atom2530+atom2624*atom623;
atom2632 = -atom636*atom628*atom2530+atom630*atom2624;
atom2627 =  atom2482*atom636*atom628+atom2624*atom629;
atom2655 =  2.0000000000000000e+00*atom497*aW_L+2.0*atom533;
atom2656 = -atom2655*atom496;
atom2658 = atom2655*atom505;
atom2361 = -( atom6*atom354-atom147*atom351)*atom453+atom3*atom454*atom351+( atom145*atom351-atom5*atom354)*atom452;
atom2597 =  atom538*atom3*atom639+atom638*( atom538*atom147-atom6*atom536)-atom637*( atom5*atom536-atom538*atom145);

_dPhit_ds[0] =  atom459*atom346+atom343*atom458;
_dPhit_ds[1] =  atom347*atom463+atom462*atom346;
_dPhit_ds[2] = -atom336*atom454-atom452*( atom325+atom328)-atom453*( atom330+atom333);
_dPhit_ds[3] = atom2361;
_dPhit_ds[4] = 0.0000000000000000e+00;
_dPhit_ds[5] = 0.0000000000000000e+00;
_dPhit_ds[6] = 0.0000000000000000e+00;
_dPhit_ds[7] = 0.0000000000000000e+00;
_dPhit_ds[8] =  atom459*atom360+atom458*atom356;
_dPhit_ds[9] =  atom362*atom463+atom462*atom360;
_dPhit_ds[10] = atom2361;
_dPhit_ds[11] =  atom452*( atom145*atom2420+atom5*atom2423)+( atom2423*atom6+atom147*atom2420)*atom453+atom3*atom454*atom2420;
_dPhit_ds[12] = 0.0000000000000000e+00;
_dPhit_ds[13] = 0.0000000000000000e+00;
_dPhit_ds[14] = 0.0000000000000000e+00;
_dPhit_ds[15] = 0.0000000000000000e+00;
_dPhit_ds[16] = -atom459;
_dPhit_ds[17] = -atom462-atom463*atom443-( atom2321*atom443+atom462*atom1075)*( atom372*atom376-z+usRz-atom336-uW_R*atom4+dR_R-atom321)+atom2321*atom465;
_dPhit_ds[18] =  atom2375*atom346+atom2380*atom343+atom347*atom2370;
_dPhit_ds[19] =  atom360*atom2375+atom2380*atom356+atom362*atom2370;
_dPhit_ds[20] = 0.0000000000000000e+00;
_dPhit_ds[21] = 0.0000000000000000e+00;
_dPhit_ds[22] = 0.0000000000000000e+00;
_dPhit_ds[23] = 0.0000000000000000e+00;
_dPhit_ds[24] = -( 5.0000000000000000e-01*atom405*atom2100*L_R+atom436+1.0000000000000000e+00)*atom458+atom465*( atom2254*atom440+atom457*atom2281)-atom459*atom2111-( sR_R-atom325-uW_R*atom144-x-atom319+5.0000000000000000e-01*atom405*atom409*L_R-atom328)*( atom2254*atom438+atom457*atom2294);
_dPhit_ds[25] = -atom462*atom2111;
_dPhit_ds[26] =  atom347*atom2390+atom2395*atom346+atom2400*atom343;
_dPhit_ds[27] =  atom362*atom2390+atom2400*atom356+atom360*atom2395;
_dPhit_ds[28] = 0.0000000000000000e+00;
_dPhit_ds[29] = 0.0000000000000000e+00;
_dPhit_ds[30] = 0.0000000000000000e+00;
_dPhit_ds[31] = 0.0000000000000000e+00;
_dPhit_ds[32] = 0.0000000000000000e+00;
_dPhit_ds[33] = 0.0000000000000000e+00;
_dPhit_ds[34] = 0.0000000000000000e+00;
_dPhit_ds[35] = 0.0000000000000000e+00;
_dPhit_ds[36] =  atom531*atom644+atom643*atom528;
_dPhit_ds[37] =  atom531*atom647+atom532*atom648;
_dPhit_ds[38] = -( atom513+atom510)*atom637-atom639*atom521-atom638*( atom518+atom515);
_dPhit_ds[39] = atom2597;
_dPhit_ds[40] = 0.0000000000000000e+00;
_dPhit_ds[41] = 0.0000000000000000e+00;
_dPhit_ds[42] = 0.0000000000000000e+00;
_dPhit_ds[43] = 0.0000000000000000e+00;
_dPhit_ds[44] =  atom644*atom545+atom541*atom643;
_dPhit_ds[45] =  atom647*atom545+atom547*atom648;
_dPhit_ds[46] = atom2597;
_dPhit_ds[47] =  atom2658*atom3*atom639+( atom2658*atom145+atom5*atom2656)*atom637+atom638*( atom6*atom2656+atom2658*atom147);
_dPhit_ds[48] = 0.0000000000000000e+00;
_dPhit_ds[49] = 0.0000000000000000e+00;
_dPhit_ds[50] = 0.0000000000000000e+00;
_dPhit_ds[51] = 0.0000000000000000e+00;
_dPhit_ds[52] = -atom644;
_dPhit_ds[53] =  atom2557*atom650-atom647-atom648*atom628-( atom1130*atom647+atom2557*atom628)*( dR_L-z+usLz+atom557*atom561-atom521-uW_L*atom4+atom321);
_dPhit_ds[54] =  atom2609*atom528+atom532*atom2617+atom2614*atom531;
_dPhit_ds[55] =  atom2614*atom545+atom2609*atom541+atom547*atom2617;
_dPhit_ds[56] = 0.0000000000000000e+00;
_dPhit_ds[57] = 0.0000000000000000e+00;
_dPhit_ds[58] = 0.0000000000000000e+00;
_dPhit_ds[59] = 0.0000000000000000e+00;
_dPhit_ds[60] = -atom644*atom2184-( -5.0000000000000000e-01*atom590*atom2174*L_R+atom620+1.0000000000000000e+00)*atom643+( atom642*atom2530+atom2517*atom623)*( atom513+5.0000000000000000e-01*atom590*atom594*L_R+atom510-sR_L+x+atom144*uW_L-atom319)+( atom2482*atom642+atom625*atom2517)*atom650;
_dPhit_ds[61] = -atom647*atom2184;
_dPhit_ds[62] =  atom531*atom2632+atom2637*atom532+atom2627*atom528;
_dPhit_ds[63] =  atom541*atom2627+atom2637*atom547+atom545*atom2632;

return _dPhit_ds;
}

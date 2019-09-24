/*----------Gammac.c lib3D_MEC exported-----------*/

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

#include "Gammac.h"

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
double atom5;
double atom316;
double atom317;
double atom6;
double atom4;
double atom318;
double atom145;
double atom325;
double atom328;
double atom348;
double atom350;
double atom354;
double atom351;
double atom2358;
double atom3;
double atom144;
double atom2339;
double atom147;
double atom346;
double atom372;
double atom373;
double atom374;
double atom441;
double atom375;
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
double atom417;
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
double atom443;
double atom440;
double atom409;
double atom436;
double atom438;
double atom445;
double atom444;
double atom451;
double atom452;
double atom330;
double atom333;
double atom146;
double atom2337;
double atom343;
double atom2354;
double atom453;
double atom2350;
double atom336;
double atom2335;
double atom454;
double atom2419;
double atom2420;
double atom2408;
double atom356;
double atom2423;
double atom2411;
double atom2414;
double atom360;
double atom326;
double atom307;
double atom319;
double atom2108;
double atom2109;
double atom331;
double atom320;
double atom2061;
double atom2065;
double atom321;
double atom2085;
double atom2074;
double atom2086;
double atom2087;
double atom2088;
double atom2095;
double atom2096;
double atom2089;
double atom2099;
double atom2236;
double atom2315;
double atom2250;
double atom2316;
double atom2238;
double atom2241;
double atom2251;
double atom2228;
double atom2229;
double atom2232;
double atom2220;
double atom2247;
double atom2365;
double atom2387;
double atom2100;
double atom2257;
double atom2256;
double atom2255;
double atom2267;
double atom2291;
double atom2279;
double atom2293;
double atom2294;
double atom1076;
double atom2129;
double atom2067;
double atom2075;
double atom2834;
double atom2836;
double atom2838;
double atom2841;
double atom2844;
double atom2845;
double atom2848;
double atom2869;
double atom2080;
double atom2849;
double atom2083;
double atom2884;
double atom2113;
double atom2115;
double atom2117;
double atom2116;
double atom2118;
double atom2119;
double atom2121;
double atom2120;
double atom2122;
double atom2124;
double atom1075;
double atom2320;
double atom2369;
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
double atom602;
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
double atom594;
double atom620;
double atom557;
double atom558;
double atom559;
double atom626;
double atom560;
double atom623;
double atom628;
double atom630;
double atom625;
double atom629;
double atom636;
double atom497;
double atom498;
double atom499;
double atom501;
double atom503;
double atom505;
double atom506;
double atom2139;
double atom533;
double atom535;
double atom536;
double atom2647;
double atom496;
double atom504;
double atom2573;
double atom518;
double atom516;
double atom638;
double atom511;
double atom513;
double atom2571;
double atom2182;
double atom2644;
double atom637;
double atom521;
double atom2576;
double atom2651;
double atom639;
double atom2655;
double atom2658;
double atom538;
double atom2595;
double atom2656;
double atom545;
double atom2588;
double atom541;
double atom2592;
double atom515;
double atom528;
double atom2187;
double atom2189;
double atom2186;
double atom2188;
double atom510;
double atom531;
double atom2193;
double atom2195;
double atom2192;
double atom2194;
double atom2154;
double atom2155;
double atom2156;
double atom2159;
double atom2173;
double atom2160;
double atom2174;
double atom2553;
double atom2161;
double atom2162;
double atom2484;
double atom2486;
double atom2554;
double atom2514;
double atom2504;
double atom2513;
double atom2549;
double atom2605;
double atom2606;
double atom1130;
double atom2197;
double atom2191;
double atom2202;
double atom2458;
double atom2462;
double atom2467;
double atom2470;
double atom2527;
double atom2480;
double atom2529;
double atom2530;
double atom2493;
double atom2495;
double atom2163;
double atom2502;
double atom2624;
double atom3014;
double atom2147;
double atom2991;
double atom2993;
double atom2995;
double atom2998;
double atom3001;
double atom3016;
double atom3023;
double atom3022;
double atom3003;
double atom3009;
double atom3029;
double atom3032;
double atom3045;

double * _Gammac = NULL;
void Init_Gammac ( ) 
{
    _Gammac = malloc ( Gammac_n_rows * Gammac_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Gammac_n_rows * Gammac_n_cols ; i++ ) {_Gammac[i]=0.0;}
  }
}

void Done_Gammac ( ) 
{
if (_Gammac != NULL) 
free (_Gammac ); 
_Gammac = NULL; 
}


double * Gammac ()
{
if ( _Gammac == NULL )
 {
    _Gammac = malloc ( Gammac_n_rows * Gammac_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Gammac_n_rows * Gammac_n_cols ; i++ ) {_Gammac[i]=0.0;}
  }
 }

atom309 =  uW_R-lW_R;
atom310 = aW_R*atom309;
atom311 =  bW_R+atom310;
atom313 =  atom309*atom311+cW_R;
atom308 = sin(thetaW_R);
atom315 =  dW_R+atom313*atom309;
atom5 = cos(c);
atom316 = -atom308*atom315;
atom317 = cos(thetaW_R);
atom6 = sin(c);
atom4 = sin(a);
atom318 = atom315*atom317;
atom145 = atom6*atom4;
atom325 = atom5*atom316;
atom328 = atom318*atom145;
atom348 =  atom310+atom311;
atom350 =  atom313+atom309*atom348;
atom354 = atom350*atom317;
atom351 = -atom308*atom350;
atom2358 =  atom145*atom351-atom5*atom354;
atom3 = cos(a);
atom144 = -atom6*atom3;
atom2339 = -atom144*atom316;
atom147 = -atom5*atom4;
atom346 = -atom318*atom6+atom147*atom316;
atom372 =  uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 =  bR_R+atom373;
atom441 =  atom374+atom373;
atom375 = atom374*atom372;
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
atom417 = atom393*atom381;
atom418 = 2.0*atom417;
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
atom443 =  cR_R+atom375+atom372*atom441;
atom440 =  atom405+-5.0000000000000000e-01*atom434*L_R;
atom409 = 1.0/(atom408);
atom436 = 5.0000000000000000e-01*atom429*atom409*L_R;
atom438 =  5.0000000000000000e-01*atom405*atom434*L_R+atom436+1.0;
atom445 = -atom438*atom443;
atom444 = atom443*atom440;
atom451 = pow( (atom438*atom438)+(atom444*atom444)+(atom445*atom445),-(1.0/2.0));
atom452 = atom444*atom451;
atom330 = atom6*atom316;
atom333 = atom318*atom147;
atom146 = atom5*atom3;
atom2337 = -atom316*atom146;
atom343 =  atom145*atom316-atom318*atom5;
atom2354 = -atom6*atom354+atom147*atom351;
atom453 = atom451*atom445;
atom2350 = atom3*atom351;
atom336 = atom318*atom3;
atom2335 = -atom4*atom316;
atom454 = atom438*atom451;
atom2419 =  2.0000000000000000e+00*aW_R*atom309+2.0*atom348;
atom2420 = atom2419*atom317;
atom2408 = -atom4*atom354+atom3;
atom356 =  atom144+atom5*atom351+atom145*atom354;
atom2423 = -atom308*atom2419;
atom2411 = -atom354*atom146+atom147;
atom2414 = -atom144*atom354+atom145;
atom360 =  atom6*atom351+atom147*atom354+atom146;
atom326 = uW_R*atom144;
atom307 = -5.0000000000000000e-01*L_WHS;
atom319 = atom144*atom307;
atom2108 = atom147*atom307;
atom2109 = -atom318*atom146+uW_R*atom147+atom2108;
atom331 = uW_R*atom146;
atom320 = atom307*atom146;
atom2061 = atom145*atom307;
atom2065 =  atom2061+uW_R*atom145-atom318*atom144;
atom321 = atom307*atom4;
atom2085 = atom381*( ( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)+atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)*atom379)*atom381*atom379+atom381*( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR))*atom379;
atom2074 = atom381*( esR+atom381*( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR)*atom379);
atom2086 =  atom2085+atom2074;
atom2087 = (atom2086*atom2086);
atom2088 =  atom2087+1.0;
atom2095 = ( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*atom381+( sR_R-stasR)*(atom381*atom381)*asR)+atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR))*atom381;
atom2096 =  atom2095+( atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)+(atom381*atom381*atom381)*asR*atom379)*atom381*atom379;
atom2089 = pow(atom2088,-(3.0/2.0));
atom2099 =  atom381*atom2096*atom379+atom381*( ( sR_R-stasR)*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*atom381+( sR_R-stasR)*(atom381*atom381)*asR)+atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR))*atom381+atom381*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR)+dsR));
atom2236 =  atom2085+L_R*atom2089*atom2086*atom2099+atom2074;
atom2315 =  atom372*( bR_R+2.0*atom372*aR_R)+cR_R+atom375;
atom2250 = (atom2236*atom2236);
atom2316 = (atom2315*atom2315);
atom2238 = pow(atom2088,-(1.0/2.0));
atom2241 =  atom2238*L_R*atom2099-atom2087*L_R*atom2089*atom2099+1.0;
atom2251 = (atom2241*atom2241);
atom2228 = atom381*atom2096;
atom2229 =  atom381*( ((atom381*atom381)*(atom381*atom381))*asR*atom379+( atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)+(atom381*atom381*atom381)*asR*atom379)*atom381)*atom379+atom2228;
atom2232 = pow(atom2088,-(5.0/2.0));
atom2220 = (atom2099*atom2099);
atom2247 =  3.0*atom2238*L_R*atom2229+6.0000000000000000e+00*atom2232*L_R*atom2220*(atom2086*atom2086*atom2086)+-3.0000000000000000e+00*atom2087*L_R*atom2089*atom2229+-6.0000000000000000e+00*L_R*atom2220*atom2089*atom2086;
atom2365 = pow( atom2250*atom2316+atom2251+atom2251*atom2316,-(3.0/2.0));
atom2387 = -( atom2241*atom2247*atom2316+( 2.0*atom381*atom2096*atom379+2.0*L_R*atom2220*atom2089+2.0*atom381*( ( sR_R-stasR)*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*atom381+( sR_R-stasR)*(atom381*atom381)*asR)+atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR))*atom381+atom381*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR)+dsR))+-6.0*atom2232*atom2087*L_R*atom2220+3.0*L_R*atom2089*atom2086*atom2229)*atom2316*atom2236+atom2241*atom2247)*atom2365;
atom2100 = -2.0*atom2089*atom2086*atom2099;
atom2257 = atom381*atom418;
atom2256 = atom381*atom421;
atom2255 = atom381*atom425;
atom2267 =  3.0*atom2255+3.0*( atom2257*atom382+atom2256)*atom382;
atom2291 = 5.0000000000000000e-01*atom429*atom2100*L_R;
atom2279 = -( ( 2.0*atom2267*atom405+2.0*(atom429*atom429))*atom431+atom2100*atom430)*atom433/2.0+4.0*1.0/(atom2088*atom2088)*atom432*atom2086*atom2099;
atom2293 =  atom2291+5.0000000000000000e-01*atom2267*atom409*L_R;
atom2294 =  5.0000000000000000e-01*atom405*atom2279*L_R+atom2293+5.0000000000000000e-01*atom429*atom434*L_R;
atom1076 = atom3*atom307;
atom2129 = -duR_R*atom443+dthetaW_R*atom3*atom316+duW_R*( atom3*atom354+atom4)+dz+( uW_R*atom3-atom318*atom4+atom1076)*da;
atom2067 =  bsR+atom381*asR*atom379;
atom2075 = atom381*atom2067;
atom2834 =  atom393*atom381*atom379+atom2075;
atom2836 = (atom381*atom381);
atom2838 =  atom417+atom2836*asR;
atom2841 = atom381*( atom2836*asR*atom379+atom2075);
atom2844 =  atom381*atom2834+atom381*atom2838*atom379+atom2841;
atom2845 = atom381*atom2844*atom379;
atom2848 = atom381*atom2834*atom379;
atom2869 = (atom381*atom381*atom381);
atom2080 = atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379);
atom2849 =  atom2080+atom2848;
atom2083 = atom381*( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR);
atom2884 =  -2.0*( atom381*( atom2095+atom381*( atom381*( csR+atom381*atom2067*atom379)+atom2848)+atom2845)+atom2228+atom381*( atom381*atom2844+atom381*( atom381*atom2838+atom2869*asR)*atom379+( atom2869*asR*atom379+atom2841)*atom381)*atom379)*atom2089*atom2086+-2.0*atom2089*( atom381*( atom2083+atom381*atom2849*atom379)+atom381*( atom381*atom2849+( atom2080+atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)*atom379)*atom381+atom2845)*atom379+atom381*( ( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)+atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)*atom379)*atom381*atom379+atom2083))*atom2099+12.0*atom2232*(atom2086*atom2086)*(atom2099*atom2099);
atom2113 = atom2065*da;
atom2115 = dthetaW_R*atom343;
atom2117 = -dc*( atom330+atom320+atom331+atom333);
atom2116 = duW_R*atom356;
atom2118 = -dsR_R*( 5.0000000000000000e-01*atom405*atom2100*L_R+atom436+1.0000000000000000e+00)+atom2113+atom2115+atom2117+dx+atom2116;
atom2119 = dthetaW_R*atom346;
atom2121 = ( atom325+atom319+atom326+atom328)*dc;
atom2120 = atom2109*da;
atom2122 = atom360*duW_R;
atom2124 =  atom2119+atom2121-( atom405+-5.0000000000000000e-01*atom2100*L_R)*dsR_R-duR_R+atom2120+atom2122+dy;
atom1075 =  2.0*atom372*aR_R+2.0*atom441;
atom2320 =  bR_R+3.0*atom372*aR_R;
atom2369 = -2.0*atom2365*( atom2315*atom2250*atom2320+atom2315*atom2320*atom2251);
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
atom602 = atom578*atom566;
atom603 = 2.0*atom602;
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
atom594 = 1.0/(atom593);
atom620 = -5.0000000000000000e-01*atom614*atom594*L_R;
atom557 =  uR_L-lR_L;
atom558 = aR_L*atom557;
atom559 =  bR_L+atom558;
atom626 =  atom559+atom558;
atom560 = atom559*atom557;
atom623 =  -5.0000000000000000e-01*atom590*L_R*atom619+atom620+1.0;
atom628 =  atom560+atom557*atom626+cR_L;
atom630 = -atom623*atom628;
atom625 =  atom590+5.0000000000000000e-01*L_R*atom619;
atom629 = atom625*atom628;
atom636 = pow( (atom623*atom623)+(atom629*atom629)+(atom630*atom630),-(1.0/2.0));
atom497 =  uW_L-lW_L;
atom498 = atom497*aW_L;
atom499 =  atom498+bW_L;
atom501 =  cW_L+atom497*atom499;
atom503 =  dW_L+atom497*atom501;
atom505 = cos(thetaW_L);
atom506 = atom503*atom505;
atom2139 =  atom145*uW_L-atom2061-atom506*atom144;
atom533 =  atom498+atom499;
atom535 =  atom497*atom533+atom501;
atom536 = atom535*atom505;
atom2647 =  atom147-atom536*atom146;
atom496 = sin(thetaW_L);
atom504 = -atom503*atom496;
atom2573 = -atom146*atom504;
atom518 = atom506*atom147;
atom516 = uW_L*atom146;
atom638 = atom630*atom636;
atom511 = atom144*uW_L;
atom513 = atom506*atom145;
atom2571 = -atom144*atom504;
atom2182 = -atom506*atom146+atom147*uW_L-atom2108;
atom2644 = -atom144*atom536+atom145;
atom637 = atom629*atom636;
atom521 = atom506*atom3;
atom2576 = -atom4*atom504;
atom2651 = -atom4*atom536+atom3;
atom639 = atom623*atom636;
atom2655 =  2.0000000000000000e+00*atom497*aW_L+2.0*atom533;
atom2658 = atom2655*atom505;
atom538 = -atom535*atom496;
atom2595 = atom538*atom3;
atom2656 = -atom2655*atom496;
atom545 =  atom147*atom536+atom538*atom6+atom146;
atom2588 = -atom5*atom536+atom538*atom145;
atom541 =  atom144+atom5*atom538+atom145*atom536;
atom2592 =  atom538*atom147-atom6*atom536;
atom515 = atom6*atom504;
atom528 = -atom5*atom506+atom145*atom504;
atom2187 = atom541*duW_L;
atom2189 = ( atom320-atom518-atom515-atom516)*dc;
atom2186 = dthetaW_L*atom528;
atom2188 = atom2139*da;
atom510 = atom5*atom504;
atom531 =  atom147*atom504-atom506*atom6;
atom2193 = ( atom511+atom513+atom510-atom319)*dc;
atom2195 = dthetaW_L*atom531;
atom2192 = da*atom2182;
atom2194 = atom545*duW_L;
atom2154 = atom564*( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566;
atom2155 =  ( ( ( sR_L-stasL)*atom566*( bsL+( sR_L-stasL)*atom566*asL)+csL)*( sR_L-stasL)*atom566+dsL)*atom566+atom2154;
atom2156 = atom564*( atom566*( atom564*atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+dsL)+atom564*( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566)*atom566;
atom2159 = ( esL+atom564*atom566*( atom564*atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+dsL))*atom566;
atom2173 =  atom2155*atom566+( ( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566+( atom564*(atom566*atom566*atom566)*asL+( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom564*atom566)*atom564*atom566;
atom2160 =  atom2156+atom2159;
atom2174 = -2.0*atom2173*atom2160*pow( (atom2160*atom2160)+1.0,-(3.0/2.0));
atom2553 =  atom560+( 2.0*aR_L*atom557+bR_L)*atom557+cR_L;
atom2161 = (atom2160*atom2160);
atom2162 =  atom2161+1.0;
atom2484 = pow(atom2162,-(1.0/2.0));
atom2486 =  atom2173*pow( atom2161+1.0,-(3.0/2.0))*L_R*atom2161-atom2173*atom2484*L_R+1.0;
atom2554 = (atom2553*atom2553);
atom2514 = (atom2486*atom2486);
atom2504 =  atom2156-pow( pow( atom2156+atom2159,2.0)+1.0,-(3.0/2.0))*( atom2156+atom2159)*( ( sR_L-stasL)/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)+( sR_L-stasL)/pow( endsL-stasL,2.0)*asL)+1.0/( endsL-stasL)*( csL+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)))/( endsL-stasL)+( 1.0/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)+( sR_L-stasL)/pow( endsL-stasL,2.0)*asL)+( sR_L-stasL)/pow( endsL-stasL,3.0)*asL)*( sR_L-stasL)/( endsL-stasL))+( 1.0/( endsL-stasL)*( ( sR_L-stasL)/( endsL-stasL)*( csL+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL))+dsL)+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)+( sR_L-stasL)/pow( endsL-stasL,2.0)*asL)+1.0/( endsL-stasL)*( csL+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)))/( endsL-stasL))/( endsL-stasL))*L_R+atom2159;
atom2513 = (atom2504*atom2504);
atom2549 =  3.0*aR_L*atom557+bR_L;
atom2605 = pow( atom2554*atom2514+atom2513*atom2554+atom2514,-(3.0/2.0));
atom2606 = -2.0*( atom2553*atom2549*atom2514+atom2513*atom2553*atom2549)*atom2605;
atom1130 =  2.0*aR_L*atom557+2.0*atom626;
atom2197 =  atom2193+atom2195-duR_L+atom2192+dy+dsR_L*( -5.0000000000000000e-01*atom2174*L_R-atom590)+atom2194;
atom2191 =  atom2187+atom2189+atom2186+atom2188+dx-dsR_L*( -5.0000000000000000e-01*atom590*atom2174*L_R+atom620+1.0000000000000000e+00);
atom2202 =  ( atom3*atom536+atom4)*duW_L-( atom506*atom4-atom3*uW_L+atom1076)*da+dz+dthetaW_L*atom3*atom504-duR_L*atom628;
atom2458 = atom603*atom566;
atom2462 = atom607*atom566;
atom2467 = atom611*atom566;
atom2470 =  3.0*atom2467+3.0*atom567*( atom567*atom2458+atom2462);
atom2527 = -5.0000000000000000e-01*atom614*atom2174*L_R;
atom2480 =  4.0*atom2173*atom2160*atom617/pow( (atom2160*atom2160)+1.0,2.0)-atom618*( ( 2.0*atom2470*atom590+2.0*(atom614*atom614))*atom616+atom615*atom2174)/2.0;
atom2529 =  atom2527+-5.0000000000000000e-01*atom2470*atom594*L_R;
atom2530 =  atom2529+-5.0000000000000000e-01*atom614*L_R*atom619+-5.0000000000000000e-01*atom590*L_R*atom2480;
atom2493 =  atom564*( atom564*((atom566*atom566)*(atom566*atom566))*asL+( atom564*(atom566*atom566*atom566)*asL+( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566)*atom566+( ( ( ( sR_L-stasL)*(atom566*atom566)*asL+atom566*( bsL+( sR_L-stasL)*atom566*asL))*( sR_L-stasL)*atom566+( ( sR_L-stasL)*atom566*( bsL+( sR_L-stasL)*atom566*asL)+csL)*atom566)*atom566+( sR_L-stasL)*atom566*( ( sR_L-stasL)*(atom566*atom566*atom566)*asL+( ( sR_L-stasL)*(atom566*atom566)*asL+atom566*( bsL+( sR_L-stasL)*atom566*asL))*atom566))*atom566;
atom2495 = (atom2173*atom2173);
atom2163 = pow(atom2162,-(3.0/2.0));
atom2502 = atom2486*( -3.0000000000000000e+00*atom2484*L_R*atom2493+6.0000000000000000e+00*atom2495*atom2160*L_R*pow( (atom2160*atom2160)+1.0,-(3.0/2.0))+3.0*pow( atom2161+1.0,-(3.0/2.0))*L_R*atom2493*atom2161+-6.0*atom2495*(atom2160*atom2160*atom2160)*pow(atom2162,-(5.0/2.0))*L_R);
atom2624 = -atom2605*( atom2502*pow( ( bR_L+2.0*aR_L*( uR_L-lR_L))*( uR_L-lR_L)+( bR_L+aR_L*( uR_L-lR_L))*( uR_L-lR_L)+cR_L,2.0)+atom2502+( 2.0*atom2155*atom566+-3.0000000000000000e+00*atom2160*L_R*pow( (atom2160*atom2160)+1.0,-(3.0/2.0))*atom2493+6.0000000000000000e+00*atom2495*pow( atom2161+1.0,-(5.0/2.0))*L_R*atom2161+2.0*( ( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566+( atom564*(atom566*atom566*atom566)*asL+( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom564*atom566)*atom564*atom566+-2.0000000000000000e+00*atom2163*atom2495*L_R)*atom2554*atom2504);
atom3014 = atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL);
atom2147 = ( bsL+atom564*atom566*asL)*atom566;
atom2991 =  atom564*atom578*atom566+atom2147;
atom2993 = (atom566*atom566);
atom2995 =  atom2993*asL+atom602;
atom2998 = ( atom564*atom2993*asL+atom2147)*atom566;
atom3001 =  atom2991*atom566+atom564*atom566*atom2995+atom2998;
atom3016 = ( atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566+atom3014)*atom566;
atom3023 = atom564*atom2991*atom566;
atom3022 =  atom3001*atom564*atom566+atom3016;
atom3003 = (atom566*atom566*atom566);
atom3009 =  atom3003*atom564*asL+atom2998;
atom3029 =  atom3023+atom3014;
atom3032 = atom566*( atom564*atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+dsL);
atom3045 =  12.0*(atom2173*atom2173)*(atom2160*atom2160)*pow( (atom2160*atom2160)+1.0,-(5.0/2.0))+-2.0*atom2163*atom2173*( atom566*( atom2154+atom3032)+( atom3029*atom564*atom566+atom3032)*atom566+atom564*( atom3022+atom3029*atom566)*atom566)+-2.0*atom2163*atom2160*( ( ( atom3023+( ( sR_L-stasL)*atom566*( bsL+( sR_L-stasL)*atom566*asL)+csL)*atom566)*atom566+atom3022)*atom566+( atom3016+atom564*atom3009*atom566)*atom566+( atom3009*atom566+atom3001*atom566+atom564*atom566*( atom566*atom2995+atom3003*asL))*atom564*atom566);

_Gammac[0] =  dc*( atom452*( atom2119+atom2121+atom2120+atom2122)-( atom2113+atom2115+atom2117+atom2116)*atom453)-dsR_R*( atom2118*( atom444*atom2387+( atom429+-5.0000000000000000e-01*atom2279*L_R)*atom451*atom443)-atom452*dsR_R*( atom2291+5.0000000000000000e-01*atom405*L_R*atom2884+atom2293)+( atom2294*atom451+atom2387*atom438)*atom2129-atom2124*( atom2294*atom451*atom443-atom2387*atom445)-dsR_R*( atom429+-5.0000000000000000e-01*L_R*atom2884)*atom453)-( ( atom2369*atom445-atom1075*atom438*atom451)*atom2124-atom1075*duR_R*atom454+atom2118*( atom444*atom2369+atom1075*atom451*atom440)+atom2369*atom438*atom2129)*duR_R-( atom452*( atom2414*da+atom2358*dthetaW_R-atom360*dc+duW_R*( atom145*atom2420+atom5*atom2423))+( duW_R*atom3*atom2420+dthetaW_R*atom2350+da*atom2408)*atom454+( ( atom2423*atom6+atom147*atom2420)*duW_R+atom2354*dthetaW_R+dc*atom356+da*atom2411)*atom453)*duW_R-( atom454*( da*atom2335+duW_R*atom2350-atom336*dthetaW_R)-atom452*( dc*atom346-atom2358*duW_R-atom2339*da+( atom325+atom328)*dthetaW_R)-( dthetaW_R*( atom330+atom333)-atom2337*da-atom2354*duW_R-dc*atom343)*atom453)*dthetaW_R-da*( atom452*( atom2414*duW_R+atom2339*dthetaW_R-atom2109*dc-da*( atom319+atom326+atom328))-( ( atom336+uW_R*atom4+atom321)*da-dthetaW_R*atom2335-duW_R*atom2408)*atom454-atom453*( da*( atom320+atom331+atom333)-duW_R*atom2411-atom2337*dthetaW_R-atom2065*dc));
_Gammac[1] =  dsR_L*( atom638*( atom614+5.0000000000000000e-01*atom3045*L_R)*dsR_L-( ( atom614+5.0000000000000000e-01*L_R*atom2480)*atom636*atom628+atom2624*atom629)*atom2191+atom2197*( atom636*atom628*atom2530-atom630*atom2624)-( atom636*atom2530+atom2624*atom623)*atom2202+atom637*dsR_L*( atom2527+-5.0000000000000000e-01*atom3045*atom590*L_R+atom2529))+dthetaW_L*( ( dthetaW_L*( atom513+atom510)+atom531*dc-atom2588*duW_L-atom2571*da)*atom637-atom638*( dc*atom528-dthetaW_L*( atom518+atom515)+da*atom2573+atom2592*duW_L)-( atom2595*duW_L+da*atom2576-dthetaW_L*atom521)*atom639)+( atom637*( atom2193+atom2195+atom2192+atom2194)-atom638*( atom2187+atom2189+atom2186+atom2188))*dc-( atom2191*( atom629*atom2606+atom1130*atom625*atom636)+atom2197*( atom630*atom2606-atom1130*atom623*atom636)+atom2202*atom623*atom2606-atom1130*duR_L*atom639)*duR_L+da*( ( ( atom521+uW_L*atom4-atom321)*da-atom2651*duW_L-dthetaW_L*atom2576)*atom639+atom637*( ( atom511+atom513-atom319)*da-atom2644*duW_L-dthetaW_L*atom2571+atom2182*dc)-atom638*( da*( atom320-atom518-atom516)+dthetaW_L*atom2573+atom2139*dc+atom2647*duW_L))-( atom639*( dthetaW_L*atom2595+da*atom2651+atom2658*atom3*duW_L)+atom638*( ( atom6*atom2656+atom2658*atom147)*duW_L+atom541*dc+dthetaW_L*atom2592+atom2647*da)+atom637*( ( atom2658*atom145+atom5*atom2656)*duW_L+dthetaW_L*atom2588+atom2644*da-atom545*dc))*duW_L;

return _Gammac;
}

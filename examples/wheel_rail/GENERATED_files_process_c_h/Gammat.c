/*----------Gammat.c lib3D_MEC exported-----------*/

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

#include "Gammat.h"

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
double atom2095;
double atom2096;
double atom2099;
double atom2085;
double atom2074;
double atom2086;
double atom2087;
double atom2088;
double atom2220;
double atom2089;
double atom2228;
double atom2229;
double atom2232;
double atom2234;
double atom2236;
double atom2238;
double atom2242;
double atom2241;
double atom2247;
double atom2248;
double atom2250;
double atom2251;
double atom2252;
double atom2249;
double atom2253;
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
double atom409;
double atom436;
double atom2254;
double atom438;
double atom440;
double atom449;
double atom2100;
double atom2257;
double atom2259;
double atom2256;
double atom2263;
double atom2255;
double atom2267;
double atom2291;
double atom2275;
double atom2276;
double atom2271;
double atom2274;
double atom2279;
double atom2293;
double atom457;
double atom2294;
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
double atom330;
double atom331;
double atom317;
double atom4;
double atom318;
double atom147;
double atom333;
double atom320;
double atom334;
double atom2297;
double atom2060;
double atom144;
double atom325;
double atom326;
double atom145;
double atom328;
double atom329;
double atom319;
double atom2281;
double atom2104;
double atom2284;
double atom3129;
double atom459;
double atom458;
double atom2063;
double atom2061;
double atom2065;
double atom2106;
double atom2108;
double atom2109;
double atom3133;
double atom345;
double atom346;
double atom342;
double atom343;
double atom3125;
double atom348;
double atom350;
double atom351;
double atom352;
double atom354;
double atom355;
double atom356;
double atom357;
double atom359;
double atom360;
double atom3121;
double atom1068;
double atom2419;
double atom2423;
double atom2420;
double atom2426;
double atom2430;
double atom2411;
double atom2414;
double atom3139;
double atom2358;
double atom2354;
double atom3157;
double atom3177;
double atom3114;
double atom3303;
double atom2067;
double atom2075;
double atom2834;
double atom2836;
double atom2838;
double atom2841;
double atom2844;
double atom2845;
double atom2848;
double atom2865;
double atom2869;
double atom2871;
double atom2874;
double atom2877;
double atom2880;
double atom2080;
double atom2849;
double atom2083;
double atom2857;
double atom2854;
double atom2858;
double atom3285;
double atom3266;
double atom3265;
double atom3274;
double atom3294;
double atom2832;
double atom2884;
double atom3301;
double atom3263;
double atom3308;
double atom3260;
double atom3211;
double atom3232;
double atom3192;
double atom3201;
double atom3187;
double atom3210;
double atom3249;
double atom3216;
double atom3221;
double atom3252;
double atom3258;
double atom3313;
double atom2111;
double atom3319;
double atom3321;
double atom465;
double atom3327;
double atom2893;
double atom3165;
double atom3147;
double atom2768;
double atom2339;
double atom2337;
double atom3143;
double atom2344;
double atom2346;
double atom372;
double atom373;
double atom374;
double atom441;
double atom375;
double atom376;
double atom443;
double atom462;
double atom2335;
double atom463;
double atom3353;
double atom336;
double atom2313;
double atom2315;
double atom2320;
double atom2321;
double atom1072;
double atom1073;
double atom1075;
double atom2326;
double atom347;
double atom3380;
double atom2350;
double atom3375;
double atom3340;
double atom2408;
double atom3357;
double atom361;
double atom362;
double atom3392;
double atom2421;
double atom3342;
double atom3346;
double atom3398;
double atom1103;
double atom1076;
double atom3365;
double atom2316;
double atom2318;
double atom3404;
double atom3407;
double atom3411;
double atom321;
double atom337;
double atom3418;
double atom3422;
double atom3416;
double atom3344;
double atom2364;
double atom2365;
double atom2368;
double atom2369;
double atom445;
double atom444;
double atom2372;
double atom451;
double atom2375;
double atom2377;
double atom2380;
double atom3455;
double atom453;
double atom452;
double atom488;
double atom3443;
double atom3451;
double atom3438;
double atom2392;
double atom2386;
double atom2387;
double atom2395;
double atom2397;
double atom2400;
double atom3447;
double atom3548;
double atom3549;
double atom3592;
double atom3593;
double atom3597;
double atom3601;
double atom3604;
double atom3609;
double atom3566;
double atom3565;
double atom3550;
double atom3556;
double atom3561;
double atom3568;
double atom3574;
double atom3572;
double atom3571;
double atom3577;
double atom3558;
double atom3559;
double atom2370;
double atom3513;
double atom3542;
double atom3489;
double atom3618;
double atom3663;
double atom3675;
double atom3670;
double atom3665;
double atom2390;
double atom3506;
double atom3478;
double atom3535;
double atom3628;
double atom3630;
double atom3634;
double atom3645;
double atom3650;
double atom3636;
double atom3642;
double atom454;
double atom3529;
double atom3472;
double atom3500;
double atom3544;
double atom3462;
double atom489;
double atom3697;
double atom3684;
double atom3693;
double atom3689;
double atom3728;
double atom3719;
double atom3705;
double atom3747;
double atom3748;
double atom3752;
double atom3736;
double atom3744;
double atom497;
double atom498;
double atom499;
double atom501;
double atom503;
double atom505;
double atom506;
double atom2179;
double atom565;
double atom564;
double atom566;
double atom567;
double atom578;
double atom569;
double atom581;
double atom602;
double atom603;
double atom605;
double atom607;
double atom571;
double atom584;
double atom609;
double atom611;
double atom573;
double atom587;
double atom601;
double atom575;
double atom590;
double atom592;
double atom593;
double atom614;
double atom2154;
double atom2155;
double atom2156;
double atom2159;
double atom2173;
double atom2160;
double atom615;
double atom2174;
double atom2458;
double atom2460;
double atom2462;
double atom2465;
double atom2467;
double atom2470;
double atom616;
double atom2474;
double atom618;
double atom2477;
double atom2457;
double atom617;
double atom2480;
double atom619;
double atom625;
double atom594;
double atom620;
double atom623;
double atom634;
double atom2482;
double atom642;
double atom2161;
double atom2162;
double atom2484;
double atom2487;
double atom2493;
double atom2497;
double atom2495;
double atom2498;
double atom2486;
double atom2501;
double atom2163;
double atom2504;
double atom2510;
double atom2502;
double atom2513;
double atom2514;
double atom2515;
double atom2512;
double atom2516;
double atom2517;
double atom2182;
double atom2520;
double atom2136;
double atom2527;
double atom2529;
double atom2530;
double atom2139;
double atom2533;
double atom3836;
double atom643;
double atom644;
double atom3802;
double atom496;
double atom504;
double atom2571;
double atom2573;
double atom3828;
double atom511;
double atom513;
double atom518;
double atom516;
double atom2923;
double atom533;
double atom535;
double atom536;
double atom2647;
double atom2644;
double atom3832;
double atom538;
double atom2592;
double atom2588;
double atom3847;
double atom529;
double atom531;
double atom526;
double atom528;
double atom3810;
double atom3851;
double atom515;
double atom2581;
double atom510;
double atom2579;
double atom539;
double atom537;
double atom541;
double atom543;
double atom542;
double atom545;
double atom3863;
double atom514;
double atom2178;
double atom519;
double atom2135;
double atom3818;
double atom3041;
double atom2151;
double atom3014;
double atom2147;
double atom2991;
double atom2993;
double atom2995;
double atom2999;
double atom2998;
double atom2992;
double atom3001;
double atom3016;
double atom3023;
double atom2152;
double atom3022;
double atom3025;
double atom3026;
double atom3003;
double atom3006;
double atom3008;
double atom3009;
double atom3007;
double atom3010;
double atom3012;
double atom3018;
double atom3028;
double atom3029;
double atom3032;
double atom3039;
double atom3036;
double atom3040;
double atom3045;
double atom4039;
double atom3881;
double atom3880;
double atom3889;
double atom4023;
double atom3876;
double atom3898;
double atom2456;
double atom3908;
double atom4029;
double atom4034;
double atom4020;
double atom3914;
double atom3945;
double atom3947;
double atom2165;
double atom3931;
double atom3940;
double atom3965;
double atom3968;
double atom2166;
double atom3987;
double atom4003;
double atom3963;
double atom4012;
double atom2184;
double atom3911;
double atom3910;
double atom650;
double atom3873;
double atom3047;
double atom3799;
double atom1123;
double atom2655;
double atom2656;
double atom2658;
double atom2664;
double atom2660;
double atom3814;
double atom557;
double atom558;
double atom559;
double atom626;
double atom560;
double atom561;
double atom628;
double atom647;
double atom521;
double atom648;
double atom2595;
double atom4089;
double atom2576;
double atom4067;
double atom2551;
double atom2553;
double atom2549;
double atom2557;
double atom1127;
double atom1128;
double atom1130;
double atom2560;
double atom532;
double atom4081;
double atom4051;
double atom4057;
double atom522;
double atom2651;
double atom4071;
double atom1146;
double atom4063;
double atom2667;
double atom546;
double atom547;
double atom4096;
double atom4053;
double atom4140;
double atom4049;
double atom2554;
double atom4112;
double atom2556;
double atom4113;
double atom4119;
double atom4123;
double atom4109;
double atom4107;
double atom2604;
double atom2605;
double atom2623;
double atom2624;
double atom630;
double atom629;
double atom636;
double atom4326;
double atom4257;
double atom4329;
double atom4337;
double atom4340;
double atom2620;
double atom4352;
double atom4356;
double atom2629;
double atom4342;
double atom4348;
double atom2632;
double atom2627;
double atom4149;
double atom2637;
double atom4173;
double atom2601;
double atom2606;
double atom4368;
double atom4256;
double atom4381;
double atom2611;
double atom4274;
double atom4270;
double atom4273;
double atom4377;
double atom2598;
double atom4279;
double atom4283;
double atom4280;
double atom4372;
double atom4207;
double atom4231;
double atom2609;
double atom2614;
double atom2617;
double atom4213;
double atom637;
double atom638;
double atom639;
double atom4186;
double atom673;
double atom674;
double atom4224;
double atom4158;
double atom4162;
double atom4179;
double atom4200;
double atom4166;
double atom4253;
double atom4237;
double atom4255;
double atom4153;
double atom4259;
double atom4258;
double atom4265;
double atom4276;
double atom4285;
double atom4267;
double atom4299;
double atom4317;
double atom4309;
double atom4314;
double atom4301;
double atom4306;
double atom4470;
double atom4437;
double atom4406;
double atom4424;
double atom4402;
double atom4418;
double atom4394;
double atom4443;
double atom4444;
double atom4446;
double atom4463;
double atom4398;

double * _Gammat = NULL;
void Init_Gammat ( ) 
{
    _Gammat = malloc ( Gammat_n_rows * Gammat_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Gammat_n_rows * Gammat_n_cols ; i++ ) {_Gammat[i]=0.0;}
  }
}

void Done_Gammat ( ) 
{
if (_Gammat != NULL) 
free (_Gammat ); 
_Gammat = NULL; 
}


double * Gammat ()
{
if ( _Gammat == NULL )
 {
    _Gammat = malloc ( Gammat_n_rows * Gammat_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Gammat_n_rows * Gammat_n_cols ; i++ ) {_Gammat[i]=0.0;}
  }
 }

atom381 = 1.0/( endsR-stasR);
atom379 =  sR_R-stasR;
atom2095 = ( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*atom381+( sR_R-stasR)*(atom381*atom381)*asR)+atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR))*atom381;
atom2096 =  atom2095+( atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)+(atom381*atom381*atom381)*asR*atom379)*atom381*atom379;
atom2099 =  atom381*atom2096*atom379+atom381*( ( sR_R-stasR)*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*atom381+( sR_R-stasR)*(atom381*atom381)*asR)+atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR))*atom381+atom381*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR)+dsR));
atom2085 = atom381*( ( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)+atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)*atom379)*atom381*atom379+atom381*( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR))*atom379;
atom2074 = atom381*( esR+atom381*( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR)*atom379);
atom2086 =  atom2085+atom2074;
atom2087 = (atom2086*atom2086);
atom2088 =  atom2087+1.0;
atom2220 = (atom2099*atom2099);
atom2089 = pow(atom2088,-(3.0/2.0));
atom2228 = atom381*atom2096;
atom2229 =  atom381*( ((atom381*atom381)*(atom381*atom381))*asR*atom379+( atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)+(atom381*atom381*atom381)*asR*atom379)*atom381)*atom379+atom2228;
atom2232 = pow(atom2088,-(5.0/2.0));
atom2234 =  2.0*atom381*atom2096*atom379+2.0*L_R*atom2220*atom2089+2.0*atom381*( ( sR_R-stasR)*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*atom381+( sR_R-stasR)*(atom381*atom381)*asR)+atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR))*atom381+atom381*( ( sR_R-stasR)*atom381*( ( bsR+( sR_R-stasR)*atom381*asR)*( sR_R-stasR)*atom381+csR)+dsR))+-6.0*atom2232*atom2087*L_R*atom2220+3.0*L_R*atom2089*atom2086*atom2229;
atom2236 =  atom2085+L_R*atom2089*atom2086*atom2099+atom2074;
atom2238 = pow(atom2088,-(1.0/2.0));
atom2242 = (atom2086*atom2086*atom2086);
atom2241 =  atom2238*L_R*atom2099-atom2087*L_R*atom2089*atom2099+1.0;
atom2247 =  6.0000000000000000e+00*atom2232*atom2242*L_R*atom2220+3.0*atom2238*L_R*atom2229+-3.0000000000000000e+00*atom2087*L_R*atom2089*atom2229+-6.0000000000000000e+00*L_R*atom2220*atom2089*atom2086;
atom2248 = atom2241*atom2247;
atom2250 = (atom2236*atom2236);
atom2251 = (atom2241*atom2241);
atom2252 =  atom2250+atom2251;
atom2249 =  atom2248+atom2234*atom2236;
atom2253 = pow(atom2252,-(3.0/2.0));
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
atom409 = 1.0/(atom408);
atom436 = 5.0000000000000000e-01*atom429*atom409*L_R;
atom2254 = -atom2249*atom2253;
atom438 =  5.0000000000000000e-01*atom405*atom434*L_R+atom436+1.0;
atom440 =  atom405+-5.0000000000000000e-01*atom434*L_R;
atom449 = (atom438*atom438);
atom2100 = -2.0*atom2089*atom2086*atom2099;
atom2257 = atom381*atom418;
atom2259 = 3.0*atom2257;
atom2256 = atom381*atom421;
atom2263 =  atom2259*atom382+3.0*atom2256;
atom2255 = atom381*atom425;
atom2267 =  3.0*atom2255+atom382*atom2263;
atom2291 = 5.0000000000000000e-01*atom429*atom2100*L_R;
atom2275 = 1.0/(atom2088*atom2088);
atom2276 = -4.0*atom2275*atom2086*atom2099;
atom2271 =  2.0*atom2267*atom405+2.0*(atom429*atom429);
atom2274 =  atom2100*atom430/2.0+atom2271*atom431/2.0;
atom2279 = -atom2274*atom433-atom432*atom2276;
atom2293 =  atom2291+5.0000000000000000e-01*atom2267*atom409*L_R;
atom457 = pow( (atom440*atom440)+atom449,-(1.0/2.0));
atom2294 =  5.0000000000000000e-01*atom405*atom2279*L_R+atom2293+5.0000000000000000e-01*atom429*atom434*L_R;
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
atom330 = atom6*atom316;
atom331 = uW_R*atom146;
atom317 = cos(thetaW_R);
atom4 = sin(a);
atom318 = atom315*atom317;
atom147 = -atom5*atom4;
atom333 = atom318*atom147;
atom320 = atom307*atom146;
atom334 =  atom330+atom331+atom333;
atom2297 =  atom2254*atom438+atom457*atom2294;
atom2060 = -atom320-atom334;
atom144 = -atom6*atom3;
atom325 = atom5*atom316;
atom326 = uW_R*atom144;
atom145 = atom6*atom4;
atom328 = atom318*atom145;
atom329 =  atom325+atom326+atom328;
atom319 = atom144*atom307;
atom2281 =  atom429+-5.0000000000000000e-01*atom2279*L_R;
atom2104 =  atom329+atom319;
atom2284 =  atom2254*atom440+atom457*atom2281;
atom3129 =  atom2104*atom2284+atom2297*atom2060;
atom459 = atom457*atom440;
atom458 = atom457*atom438;
atom2063 = -atom318*atom144;
atom2061 = atom145*atom307;
atom2065 =  atom2061+atom2063+uW_R*atom145;
atom2106 = -atom318*atom146;
atom2108 = atom147*atom307;
atom2109 =  atom2106+uW_R*atom147+atom2108;
atom3133 = -atom2109*atom458+atom2065*atom459;
atom345 = atom147*atom316;
atom346 = -atom318*atom6+atom345;
atom342 = atom145*atom316;
atom343 =  atom342-atom318*atom5;
atom3125 = -atom458*atom346+atom459*atom343;
atom348 =  atom310+atom311;
atom350 =  atom313+atom309*atom348;
atom351 = -atom308*atom350;
atom352 = atom5*atom351;
atom354 = atom350*atom317;
atom355 = atom145*atom354;
atom356 =  atom355+atom144+atom352;
atom357 = atom6*atom351;
atom359 = atom147*atom354;
atom360 =  atom357+atom359+atom146;
atom3121 =  atom459*atom356-atom360*atom458;
atom1068 = 2.0000000000000000e+00*aW_R;
atom2419 =  atom309*atom1068+2.0*atom348;
atom2423 = -atom308*atom2419;
atom2420 = atom2419*atom317;
atom2426 =  atom2423*atom6+atom147*atom2420;
atom2430 =  atom145*atom2420+atom5*atom2423;
atom2411 = -atom354*atom146+atom147;
atom2414 = -atom144*atom354+atom145;
atom3139 =  atom2414*atom458+atom459*atom2411;
atom2358 =  atom145*atom351-atom5*atom354;
atom2354 = -atom6*atom354+atom147*atom351;
atom3157 =  atom459*atom2354+atom2358*atom458;
atom3177 =  atom2297*atom356+atom360*atom2284;
atom3114 = dsR_R*atom2284;
atom3303 = 5.0000000000000000e-01*atom429*atom2279*L_R;
atom2067 =  bsR+atom381*asR*atom379;
atom2075 = atom381*atom2067;
atom2834 =  atom393*atom381*atom379+atom2075;
atom2836 = (atom381*atom381);
atom2838 =  atom417+atom2836*asR;
atom2841 = atom381*( atom2836*asR*atom379+atom2075);
atom2844 =  atom381*atom2834+atom381*atom2838*atom379+atom2841;
atom2845 = atom381*atom2844*atom379;
atom2848 = atom381*atom2834*atom379;
atom2865 =  atom2095+atom381*( atom381*( csR+atom381*atom2067*atom379)+atom2848)+atom2845;
atom2869 = (atom381*atom381*atom381);
atom2871 =  atom381*atom2838+atom2869*asR;
atom2874 = ( atom2869*asR*atom379+atom2841)*atom381;
atom2877 =  atom381*atom2844+atom2874+atom381*atom2871*atom379;
atom2880 =  atom381*atom2865+atom2228+atom381*atom2877*atom379;
atom2080 = atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379);
atom2849 =  atom2080+atom2848;
atom2083 = atom381*( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR);
atom2857 = atom381*( atom2083+atom381*atom2849*atom379);
atom2854 =  atom381*( atom381*atom2849+( atom2080+atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)*atom379)*atom381+atom2845)*atom379+atom381*( ( atom381*( csR+( bsR+atom381*asR*atom379)*atom381*atom379)+atom381*( (atom381*atom381)*asR*atom379+( bsR+atom381*asR*atom379)*atom381)*atom379)*atom381*atom379+atom2083);
atom2858 =  atom2857+atom2854;
atom3285 = -atom2274*atom2276;
atom3266 = atom381*atom2259;
atom3265 = atom381*atom2263;
atom3274 =  4.0*atom3265+4.0*atom3266*atom382;
atom3294 = (1.0/2.0)*atom2271*atom2100;
atom2832 = -6.0*atom2232*atom2086*atom2099;
atom2884 =  -2.0*atom2832*atom2086*atom2099+-2.0*atom2880*atom2089*atom2086+-2.0*atom2858*atom2089*atom2099;
atom3301 = -atom432*( 32.0*1.0/(atom2088*atom2088*atom2088)*(atom2086*atom2086)*(atom2099*atom2099)+-4.0*atom2880*atom2275*atom2086+-4.0*atom2858*atom2275*atom2099)-( ( 2.0*atom429*atom2267+2.0*atom405*atom3274+48.0*atom2229*atom2099)*atom431+atom430*atom2884+4.0*atom3294)*atom433/2.0+2.0*atom3285;
atom3263 = 5.0000000000000000e-01*atom2267*atom2100*L_R;
atom3308 =  5.0000000000000000e-01*atom3301*atom405*L_R+5.0000000000000000e-01*atom429*L_R*atom2884+2.0*atom3303+2.0*atom3263+5.0000000000000000e-01*atom409*atom3274*L_R+5.0000000000000000e-01*atom2267*atom434*L_R;
atom3260 = atom2254*atom2294;
atom3211 = 4.0*atom2086*atom2099;
atom3232 = -atom2880*atom2087*L_R*atom2089+atom2880*atom2238*L_R+atom2100*L_R*atom2099-atom3211*L_R*atom2089*atom2099-atom2087*atom2832*L_R*atom2099;
atom3192 = ((atom381*atom381)*(atom381*atom381));
atom3201 =  atom381*( atom381*atom2871+atom3192*asR)*atom379+atom381*( atom2874+atom3192*asR*atom379)+atom381*atom2877;
atom3187 = 6.0*atom2229*atom2099;
atom3210 = -10.0*pow(atom2088,-(7.0/2.0))*atom2086*atom2099;
atom3249 =  -6.0000000000000000e+00*atom3187*L_R*atom2089*atom2086+6.0000000000000000e+00*atom3210*atom2242*L_R*atom2220+-3.0000000000000000e+00*atom2087*L_R*atom2089*atom3201+3.0*atom2238*L_R*atom3201+6.0000000000000000e+00*atom2232*atom3187*atom2242*L_R+3.6000000000000000e+01*atom2232*atom2087*L_R*atom2220*atom2099+3.0*atom2100*L_R*atom2229+-3.0000000000000000e+00*atom3211*L_R*atom2089*atom2229+-3.0000000000000000e+00*atom2087*atom2832*L_R*atom2229+-6.0000000000000000e+00*atom2858*L_R*atom2220*atom2089+-6.0000000000000000e+00*atom2832*L_R*atom2220*atom2086;
atom3216 =  2.0*atom381*atom2865+3.0*L_R*atom2089*atom3201*atom2086+2.0000000000000000e+00*atom381*atom2096+-6.0*atom2232*atom3211*L_R*atom2220+3.0*atom2858*L_R*atom2089*atom2229+2.0*atom381*atom2877*atom379+2.0*atom3187*L_R*atom2089+2.0*atom2832*L_R*atom2220+-6.0*atom2232*atom2087*atom3187*L_R+3.0*atom2832*L_R*atom2086*atom2229+-6.0*atom3210*atom2087*L_R*atom2220;
atom3221 =  atom2858*L_R*atom2089*atom2099+atom2880*L_R*atom2089*atom2086+atom2857+atom2854+atom2832*L_R*atom2086*atom2099;
atom3252 =  atom3232*atom2247+atom3249*atom2241;
atom3258 = -atom2253*( atom3252+atom2234*atom3221+atom3216*atom2236)+3.0*pow(atom2252,-(5.0/2.0))*(atom2249*atom2249);
atom3313 = -atom2297*( 5.0000000000000000e-01*atom405*atom2100*L_R+atom436+1.0000000000000000e+00);
atom2111 =  atom405+-5.0000000000000000e-01*atom2100*L_R;
atom3319 =  atom2267+-5.0000000000000000e-01*atom3301*L_R;
atom3321 = atom2254*atom2281;
atom465 = -uR_R+atom320+atom334-fsR+y+5.0000000000000000e-01*atom409*L_R-atom390*atom382;
atom3327 = -atom2111*atom2284;
atom2893 =  atom429+-5.0000000000000000e-01*L_R*atom2884;
atom3165 =  atom2297*atom343+atom2284*atom346;
atom3147 =  atom2109*atom2284+atom2065*atom2297;
atom2768 = -atom320-atom331-atom333;
atom2339 = -atom144*atom316;
atom2337 = -atom316*atom146;
atom3143 =  atom2337*atom459+atom2339*atom458;
atom2344 = -atom330-atom333;
atom2346 = -atom325-atom328;
atom372 =  uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 =  bR_R+atom373;
atom441 =  atom374+atom373;
atom375 = atom374*atom372;
atom376 =  cR_R+atom375;
atom443 =  atom376+atom372*atom441;
atom462 = pow( (atom443*atom443)+1.0,-(1.0/2.0));
atom2335 = -atom4*atom316;
atom463 = atom462*atom443;
atom3353 =  atom2335*atom463+atom2337*atom462;
atom336 = atom318*atom3;
atom2313 =  bR_R+2.0*atom372*aR_R;
atom2315 =  atom2313*atom372+cR_R+atom375;
atom2320 =  bR_R+3.0*atom372*aR_R;
atom2321 = -2.0*atom2315*pow( (atom2315*atom2315)+1.0,-(3.0/2.0))*atom2320;
atom1072 = 2.0*aR_R;
atom1073 = atom372*atom1072;
atom1075 =  atom1073+2.0*atom441;
atom2326 =  atom2321*atom443+atom462*atom1075;
atom347 = atom3*atom316;
atom3380 =  atom2326*atom347+atom2321*atom346;
atom2350 = atom3*atom351;
atom3375 =  atom463*atom2350+atom462*atom2354;
atom3340 = atom462*atom343;
atom2408 = -atom4*atom354+atom3;
atom3357 =  atom462*atom2411+atom463*atom2408;
atom361 = atom3*atom354;
atom362 =  atom4+atom361;
atom3392 =  atom2326*atom362+atom2321*atom360;
atom2421 = atom3*atom2420;
atom3342 = atom462*atom356;
atom3346 = atom2104*atom2321;
atom3398 = -atom2321*atom2111;
atom1103 = -atom318*atom4;
atom1076 = atom3*atom307;
atom3365 =  ( uW_R*atom3+atom1103+atom1076)*atom2326+atom2321*atom2109;
atom2316 = (atom2315*atom2315);
atom2318 = pow( atom2316+1.0,-(3.0/2.0));
atom3404 =  atom2313+atom1073+atom441;
atom3407 = 3.0000000000000000e+00*aR_R;
atom3411 =  -2.0*atom2318*atom2315*atom3407+-2.0*atom2318*atom3404*atom2320+12.0*(atom2315*atom2315)*pow( (atom2315*atom2315)+1.0,-(5.0/2.0))*(atom2320*atom2320);
atom321 = atom307*atom4;
atom337 =  atom336+uW_R*atom4;
atom3418 = atom2321*atom1075;
atom3422 = 3.0*atom1072;
atom3416 = -atom2326*atom443;
atom3344 = atom2065*atom462;
atom2364 =  atom2250*atom2316+atom2251+atom2251*atom2316;
atom2365 = pow(atom2364,-(3.0/2.0));
atom2368 =  atom2315*atom2250*atom2320+atom2315*atom2320*atom2251;
atom2369 = -2.0*atom2365*atom2368;
atom445 = -atom438*atom443;
atom444 = atom443*atom440;
atom2372 = -atom1075*atom438;
atom451 = pow( (atom444*atom444)+(atom445*atom445)+atom449,-(1.0/2.0));
atom2375 =  atom2369*atom445+atom2372*atom451;
atom2377 = atom1075*atom440;
atom2380 =  atom451*atom2377+atom444*atom2369;
atom3455 =  atom2375*atom343-atom2380*atom346;
atom453 = atom451*atom445;
atom452 = atom444*atom451;
atom488 =  atom452*atom343+atom453*atom346;
atom3443 =  atom2358*atom453-atom452*atom2354;
atom3451 =  atom2339*atom453-atom2337*atom452;
atom3438 = -atom2344*atom452+atom2346*atom453;
atom2392 = -atom2294*atom443;
atom2386 =  atom2234*atom2316*atom2236+atom2248+atom2241*atom2247*atom2316;
atom2387 = -atom2365*atom2386;
atom2395 =  atom2387*atom445+atom451*atom2392;
atom2397 = atom443*atom2281;
atom2400 =  atom444*atom2387+atom451*atom2397;
atom3447 =  atom343*atom2395-atom2400*atom346;
atom3548 = pow(atom2364,-(5.0/2.0));
atom3549 = -6.0*atom2368*atom3548;
atom3592 =  -2.0*atom2365*( atom2315*atom2250*atom3407+atom2250*atom3404*atom2320+atom2315*atom3407*atom2251+atom3404*atom2320*atom2251)+-2.0*atom3549*atom2368;
atom3593 = atom438*atom3592;
atom3597 = atom2369*atom2377;
atom3601 =  atom3422*atom451*atom440+2.0*atom3597+atom444*atom3592;
atom3604 = atom2369*atom2372;
atom3609 = -atom3422*atom438*atom451+atom3592*atom445+2.0*atom3604;
atom3566 = atom2369*atom2397;
atom3565 = atom1075*atom451*atom2281;
atom3550 = 4.0*atom2315*atom2320;
atom3556 = -atom2386*atom3549-atom2365*( atom2241*atom3550*atom2247+atom2234*atom3550*atom2236);
atom3561 = atom2387*atom2377;
atom3568 =  atom3566+atom3561+atom444*atom3556+atom3565;
atom3574 = atom2387*atom2372;
atom3572 = -atom1075*atom2294*atom451;
atom3571 = atom2369*atom2392;
atom3577 =  atom3572+atom3574+atom3571+atom3556*atom445;
atom3558 = atom2369*atom2294;
atom3559 =  atom438*atom3556+atom3558;
atom2370 = atom2369*atom438;
atom3513 =  atom2346*atom2380-atom336*atom2370+atom2344*atom2375;
atom3542 =  atom2354*atom2375+atom2370*atom2350+atom2358*atom2380;
atom3489 =  atom2370*atom2335+atom2339*atom2380+atom2337*atom2375;
atom3618 = -3.0*atom2386*atom3548;
atom3663 =  -4.0*atom2365*( atom2315*atom2241*atom2320*atom2247+atom2315*atom2234*atom2320*atom2236)+-2.0*atom3618*atom2368;
atom3675 =  atom3572+atom445*atom3663+atom3574+atom3571;
atom3670 =  atom444*atom3663+atom3566+atom3561+atom3565;
atom3665 =  atom3558+atom438*atom3663;
atom2390 =  atom2294*atom451+atom2387*atom438;
atom3506 =  atom2346*atom2400-atom336*atom2390+atom2344*atom2395;
atom3478 =  atom2337*atom2395+atom2339*atom2400+atom2390*atom2335;
atom3535 =  atom2358*atom2400+atom2354*atom2395+atom2390*atom2350;
atom3628 = -atom3618*atom2386-( atom3216*atom2316*atom2236+atom2234*atom3221*atom2316+atom3249*atom2241*atom2316+atom3252+atom3232*atom2247*atom2316)*atom2365;
atom3630 = atom2387*atom2294;
atom3634 =  atom438*atom3628+atom3308*atom451+2.0*atom3630;
atom3645 = atom2387*atom2392;
atom3650 =  atom3628*atom445+2.0*atom3645-atom3308*atom451*atom443;
atom3636 = atom2387*atom2397;
atom3642 =  2.0*atom3636+atom451*atom443*atom3319+atom444*atom3628;
atom454 = atom438*atom451;
atom3529 = -( atom6*atom2420-atom2423*atom147)*atom453+atom2423*atom3*atom454+atom452*( atom2423*atom145-atom5*atom2420);
atom3472 = -atom454*atom351*atom4-atom351*atom453*atom146-atom452*atom144*atom351;
atom3500 = -( atom357+atom359)*atom453-atom454*atom361-atom452*( atom355+atom352);
atom3544 =  atom3500*dthetaW_R+da*atom3472+atom3535*dsR_R+duW_R*atom3529+atom3443*dc+atom3542*duR_R;
atom3462 = -atom2106*atom453-atom454*atom1103-atom452*atom2063;
atom489 = atom347*atom454;
atom3697 = -atom452*atom2426+atom2430*atom453;
atom3684 =  atom2395*atom356-atom360*atom2400;
atom3693 =  atom2375*atom356-atom360*atom2380;
atom3689 =  atom2414*atom453-atom452*atom2411;
atom3728 = -atom454*atom2420*atom4-atom2420*atom453*atom146-atom452*atom144*atom2420;
atom3719 =  atom2414*atom2380+atom2375*atom2411+atom2370*atom2408;
atom3705 =  atom2414*atom2400+atom2395*atom2411+atom2390*atom2408;
atom3747 = 3.0*atom1068;
atom3748 = atom3747*atom317;
atom3752 = -atom308*atom3747;
atom3736 =  atom2400*atom2430+atom2421*atom2390+atom2426*atom2395;
atom3744 =  atom2380*atom2430+atom2426*atom2375+atom2421*atom2370;
atom497 =  uW_L-lW_L;
atom498 = atom497*aW_L;
atom499 =  atom498+bW_L;
atom501 =  cW_L+atom497*atom499;
atom503 =  dW_L+atom497*atom501;
atom505 = cos(thetaW_L);
atom506 = atom503*atom505;
atom2179 = -atom506*atom146;
atom565 =  endsL-stasL;
atom564 =  sR_L-stasL;
atom566 = 1.0/(atom565);
atom567 = atom564*atom566;
atom578 = atom566*asL;
atom569 =  bsL+atom567*asL;
atom581 =  atom567*atom578+atom569*atom566;
atom602 = atom578*atom566;
atom603 = 2.0*atom602;
atom605 = atom581*atom566;
atom607 =  atom603*atom567+2.0*atom605;
atom571 =  atom567*atom569+csL;
atom584 =  atom571*atom566+atom581*atom567;
atom609 = atom584*atom566;
atom611 =  atom607*atom567+2.0*atom609;
atom573 =  atom567*atom571+dsL;
atom587 =  atom573*atom566+atom584*atom567;
atom601 = atom587*atom566;
atom575 =  esL+atom567*atom573;
atom590 =  atom575*atom566+atom567*atom587;
atom592 =  (atom590*atom590)+1.0;
atom593 = pow(atom592,(1.0/2.0));
atom614 =  2.0*atom601+atom567*atom611;
atom2154 = atom564*( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566;
atom2155 =  ( ( ( sR_L-stasL)*atom566*( bsL+( sR_L-stasL)*atom566*asL)+csL)*( sR_L-stasL)*atom566+dsL)*atom566+atom2154;
atom2156 = atom564*( atom566*( atom564*atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+dsL)+atom564*( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566)*atom566;
atom2159 = ( esL+atom564*atom566*( atom564*atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+dsL))*atom566;
atom2173 =  atom2155*atom566+( ( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566+( atom564*(atom566*atom566*atom566)*asL+( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom564*atom566)*atom564*atom566;
atom2160 =  atom2156+atom2159;
atom615 = 2.0*atom614*atom590;
atom2174 = -2.0*atom2173*atom2160*pow( (atom2160*atom2160)+1.0,-(3.0/2.0));
atom2458 = atom603*atom566;
atom2460 = 3.0*atom2458;
atom2462 = atom607*atom566;
atom2465 =  atom567*atom2460+3.0*atom2462;
atom2467 = atom611*atom566;
atom2470 =  atom567*atom2465+3.0*atom2467;
atom616 = pow(atom592,-(1.0/2.0));
atom2474 =  2.0*atom2470*atom590+2.0*(atom614*atom614);
atom618 = 1.0/(atom593*atom593);
atom2477 =  atom616*atom2474/2.0+atom615*atom2174/2.0;
atom2457 = -4.0*atom2173*atom2160/pow( (atom2160*atom2160)+1.0,2.0);
atom617 = (1.0/2.0)*atom615*atom616;
atom2480 = -atom2457*atom617-atom618*atom2477;
atom619 = -atom618*atom617;
atom625 =  atom590+5.0000000000000000e-01*L_R*atom619;
atom594 = 1.0/(atom593);
atom620 = -5.0000000000000000e-01*atom614*atom594*L_R;
atom623 =  -5.0000000000000000e-01*atom590*L_R*atom619+atom620+1.0;
atom634 = (atom623*atom623);
atom2482 =  atom614+5.0000000000000000e-01*L_R*atom2480;
atom642 = pow( atom634+(atom625*atom625),-(1.0/2.0));
atom2161 = (atom2160*atom2160);
atom2162 =  atom2161+1.0;
atom2484 = pow(atom2162,-(1.0/2.0));
atom2487 = ( ( ( ( sR_L-stasL)*(atom566*atom566)*asL+atom566*( bsL+( sR_L-stasL)*atom566*asL))*( sR_L-stasL)*atom566+( ( sR_L-stasL)*atom566*( bsL+( sR_L-stasL)*atom566*asL)+csL)*atom566)*atom566+( sR_L-stasL)*atom566*( ( sR_L-stasL)*(atom566*atom566*atom566)*asL+( ( sR_L-stasL)*(atom566*atom566)*asL+atom566*( bsL+( sR_L-stasL)*atom566*asL))*atom566))*atom566;
atom2493 =  atom2487+atom564*( atom564*((atom566*atom566)*(atom566*atom566))*asL+( atom564*(atom566*atom566*atom566)*asL+( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566)*atom566;
atom2497 = (atom2160*atom2160*atom2160);
atom2495 = (atom2173*atom2173);
atom2498 = pow(atom2162,-(5.0/2.0));
atom2486 =  atom2173*pow( atom2161+1.0,-(3.0/2.0))*L_R*atom2161-atom2173*atom2484*L_R+1.0;
atom2501 =  -3.0000000000000000e+00*atom2484*L_R*atom2493+6.0000000000000000e+00*atom2495*atom2160*L_R*pow( (atom2160*atom2160)+1.0,-(3.0/2.0))+3.0*pow( atom2161+1.0,-(3.0/2.0))*L_R*atom2493*atom2161+-6.0*atom2497*atom2495*L_R*atom2498;
atom2163 = pow(atom2162,-(3.0/2.0));
atom2504 =  atom2156-pow( pow( atom2156+atom2159,2.0)+1.0,-(3.0/2.0))*( atom2156+atom2159)*( ( sR_L-stasL)/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)+( sR_L-stasL)/pow( endsL-stasL,2.0)*asL)+1.0/( endsL-stasL)*( csL+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)))/( endsL-stasL)+( 1.0/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)+( sR_L-stasL)/pow( endsL-stasL,2.0)*asL)+( sR_L-stasL)/pow( endsL-stasL,3.0)*asL)*( sR_L-stasL)/( endsL-stasL))+( 1.0/( endsL-stasL)*( ( sR_L-stasL)/( endsL-stasL)*( csL+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL))+dsL)+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*( ( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)+( sR_L-stasL)/pow( endsL-stasL,2.0)*asL)+1.0/( endsL-stasL)*( csL+( sR_L-stasL)*( ( sR_L-stasL)/( endsL-stasL)*asL+bsL)/( endsL-stasL)))/( endsL-stasL))/( endsL-stasL))*L_R+atom2159;
atom2510 =  2.0*atom2155*atom566+-3.0000000000000000e+00*atom2160*L_R*pow( (atom2160*atom2160)+1.0,-(3.0/2.0))*atom2493+6.0000000000000000e+00*atom2495*pow( atom2161+1.0,-(5.0/2.0))*L_R*atom2161+2.0*( ( atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom566+( atom564*(atom566*atom566*atom566)*asL+( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566)*atom564*atom566)*atom564*atom566+-2.0000000000000000e+00*atom2163*atom2495*L_R;
atom2502 = atom2486*atom2501;
atom2513 = (atom2504*atom2504);
atom2514 = (atom2486*atom2486);
atom2515 =  atom2513+atom2514;
atom2512 =  atom2504*atom2510+atom2502;
atom2516 = pow(atom2515,-(3.0/2.0));
atom2517 = -atom2512*atom2516;
atom2182 =  atom2179+atom147*uW_L-atom2108;
atom2520 =  atom2482*atom642+atom625*atom2517;
atom2136 = -atom506*atom144;
atom2527 = -5.0000000000000000e-01*atom614*atom2174*L_R;
atom2529 =  atom2527+-5.0000000000000000e-01*atom2470*atom594*L_R;
atom2530 =  atom2529+-5.0000000000000000e-01*atom614*L_R*atom619+-5.0000000000000000e-01*atom590*L_R*atom2480;
atom2139 =  atom145*uW_L-atom2061+atom2136;
atom2533 =  atom642*atom2530+atom2517*atom623;
atom3836 =  atom2182*atom2520+atom2139*atom2533;
atom643 = atom642*atom623;
atom644 = atom625*atom642;
atom3802 = -atom2182*atom643+atom2139*atom644;
atom496 = sin(thetaW_L);
atom504 = -atom503*atom496;
atom2571 = -atom144*atom504;
atom2573 = -atom146*atom504;
atom3828 =  atom2571*atom643+atom644*atom2573;
atom511 = atom144*uW_L;
atom513 = atom506*atom145;
atom518 = atom506*atom147;
atom516 = uW_L*atom146;
atom2923 =  atom320-atom518-atom516;
atom533 =  atom498+atom499;
atom535 =  atom497*atom533+atom501;
atom536 = atom535*atom505;
atom2647 =  atom147-atom536*atom146;
atom2644 = -atom144*atom536+atom145;
atom3832 =  atom2647*atom644+atom2644*atom643;
atom538 = -atom535*atom496;
atom2592 =  atom538*atom147-atom6*atom536;
atom2588 = -atom5*atom536+atom538*atom145;
atom3847 =  atom2588*atom643+atom644*atom2592;
atom529 = atom147*atom504;
atom531 = -atom506*atom6+atom529;
atom526 = atom145*atom504;
atom528 = -atom5*atom506+atom526;
atom3810 = -atom531*atom643+atom644*atom528;
atom3851 =  atom2533*atom528+atom531*atom2520;
atom515 = atom6*atom504;
atom2581 = -atom518-atom515;
atom510 = atom5*atom504;
atom2579 = -atom513-atom510;
atom539 = atom5*atom538;
atom537 = atom145*atom536;
atom541 =  atom539+atom144+atom537;
atom543 = atom538*atom6;
atom542 = atom147*atom536;
atom545 =  atom543+atom542+atom146;
atom3863 =  atom541*atom2533+atom545*atom2520;
atom514 =  atom511+atom513+atom510;
atom2178 = -atom319+atom514;
atom519 =  atom518+atom515+atom516;
atom2135 =  atom320-atom519;
atom3818 =  atom2178*atom2520+atom2135*atom2533;
atom3041 = -6.0*atom2173*atom2160*pow( (atom2160*atom2160)+1.0,-(5.0/2.0));
atom2151 = atom564*( atom564*(atom566*atom566)*asL+( bsL+atom564*atom566*asL)*atom566)*atom566;
atom3014 = atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL);
atom2147 = ( bsL+atom564*atom566*asL)*atom566;
atom2991 =  atom564*atom578*atom566+atom2147;
atom2993 = (atom566*atom566);
atom2995 =  atom2993*asL+atom602;
atom2999 = atom564*atom566*atom2995;
atom2998 = ( atom564*atom2993*asL+atom2147)*atom566;
atom2992 = atom2991*atom566;
atom3001 =  atom2992+atom2999+atom2998;
atom3016 = ( atom2151+atom3014)*atom566;
atom3023 = atom564*atom2991*atom566;
atom2152 = ( ( sR_L-stasL)*atom566*( bsL+( sR_L-stasL)*atom566*asL)+csL)*atom566;
atom3022 =  atom3001*atom564*atom566+atom3016;
atom3025 = ( atom3023+atom2152)*atom566;
atom3026 =  atom3022+atom3025;
atom3003 = (atom566*atom566*atom566);
atom3006 =  atom566*atom2995+atom3003*asL;
atom3008 = atom3003*atom564*asL;
atom3009 =  atom3008+atom2998;
atom3007 = atom3006*atom564*atom566;
atom3010 = atom3009*atom566;
atom3012 =  atom3001*atom566+atom3007+atom3010;
atom3018 =  atom3016+atom564*atom3009*atom566;
atom3028 =  atom3018*atom566+atom3026*atom566+atom3012*atom564*atom566;
atom3029 =  atom3023+atom3014;
atom3032 = atom566*( atom564*atom566*( atom564*( bsL+atom564*atom566*asL)*atom566+csL)+dsL);
atom3039 = ( atom3029*atom564*atom566+atom3032)*atom566;
atom3036 =  atom566*( atom2154+atom3032)+atom564*( atom3022+atom3029*atom566)*atom566;
atom3040 =  atom3039+atom3036;
atom3045 =  -2.0*atom2173*atom2160*atom3041+-2.0*atom2163*atom2160*atom3028+-2.0*atom3040*atom2163*atom2173;
atom4039 = -( -5.0000000000000000e-01*atom590*atom2174*L_R+atom620+1.0000000000000000e+00)*atom2533;
atom3881 = atom2460*atom566;
atom3880 = atom2465*atom566;
atom3889 =  4.0*atom3880+4.0*atom567*atom3881;
atom4023 = -5.0000000000000000e-01*atom2470*atom2174*L_R;
atom3876 = (1.0/2.0)*atom2174*atom2474;
atom3898 = -atom2457*atom2477;
atom2456 = 1.0/(atom2162*atom2162);
atom3908 =  2.0*atom3898-( 32.0*(atom2173*atom2173)*(atom2160*atom2160)/pow( (atom2160*atom2160)+1.0,3.0)+-4.0*atom2160*atom2456*atom3028+-4.0*atom3040*atom2173*atom2456)*atom617-atom618*( atom615*atom3045+4.0*atom3876+( 2.0*atom614*atom2470+2.0*atom590*atom3889+48.0*atom2173*atom2493)*atom616)/2.0;
atom4029 = -5.0000000000000000e-01*atom614*L_R*atom2480;
atom4034 =  -5.0000000000000000e-01*atom3908*atom590*L_R+-5.0000000000000000e-01*atom2470*L_R*atom619+2.0*atom4023+-5.0000000000000000e-01*atom614*atom3045*L_R+2.0*atom4029+-5.0000000000000000e-01*atom594*atom3889*L_R;
atom4020 = atom2517*atom2530;
atom3914 = 4.0*atom2173*atom2160;
atom3945 = 6.0*atom2173*atom2493;
atom3947 = -10.0*atom2173*atom2160*pow( (atom2160*atom2160)+1.0,-(7.0/2.0));
atom2165 = ( ( sR_L-stasL)*(atom566*atom566)*asL+atom566*( bsL+( sR_L-stasL)*atom566*asL))*atom566;
atom3931 = ((atom566*atom566)*(atom566*atom566));
atom3940 =  atom566*( ( atom2992+atom2165+atom2999)*atom566+atom3007+( atom2165+atom3008)*atom566)+( atom564*atom3931*asL+atom3010)*atom566+atom564*( atom3006*atom566+atom3931*asL)*atom566;
atom3965 =  1.0/(atom565*atom565)*asL+atom602;
atom3968 =  atom2992+atom2165+atom564*atom3965*atom566;
atom2166 = 1.0/(atom565*atom565*atom565);
atom3987 = -atom2163*atom2160*L_R*( atom2487+( atom564*( atom2166*asL+atom3965*atom566)*atom566+( atom2165+atom564*atom2166*asL)*atom566+atom3968*atom566)*atom564*atom566+( atom564*atom3968*atom566+( atom2151+atom2152)*atom566+atom3025)*atom566)-atom3040*atom2163*atom2173*L_R+atom3039+atom3036-atom2173*atom2160*atom3041*L_R;
atom4003 =  6.0000000000000000e+00*atom2495*atom3947*L_R*atom2161+6.0000000000000000e+00*atom3914*atom2495*L_R*atom2498+6.0000000000000000e+00*atom3945*L_R*atom2498*atom2161+-3.0000000000000000e+00*atom2163*atom2160*L_R*atom3940+-2.0000000000000000e+00*atom2163*atom3945*L_R+2.0000000000000000e+00*atom3018*atom566+2.0*atom3026*atom566+-3.0000000000000000e+00*atom2160*atom3041*L_R*atom2493+2.0*atom3012*atom564*atom566+-3.0000000000000000e+00*atom3040*atom2163*L_R*atom2493+-2.0000000000000000e+00*atom2495*atom3041*L_R;
atom3963 =  atom2501*( atom2173*atom3041*L_R*atom2161-atom2173*atom2174*L_R-atom2484*atom3028*L_R+atom2163*atom3028*L_R*atom2161+atom3914*atom2163*atom2173*L_R)+( 3.0*atom2163*L_R*atom3940*atom2161+-6.0*atom2497*atom2495*atom3947*L_R+3.0*atom3041*L_R*atom2493*atom2161+-3.0000000000000000e+00*atom2174*L_R*atom2493+6.0000000000000000e+00*atom2163*atom3945*atom2160*L_R+3.0*atom3914*atom2163*L_R*atom2493+-6.0*atom2497*atom3945*L_R*atom2498+-3.0000000000000000e+00*atom2484*L_R*atom3940+-36.0*atom2173*atom2495*L_R*atom2498*atom2161+6.0000000000000000e+00*atom3040*atom2163*atom2495*L_R+6.0000000000000000e+00*atom2495*atom2160*atom3041*L_R)*atom2486;
atom4012 =  3.0*pow(atom2515,-(5.0/2.0))*(atom2512*atom2512)-( atom4003*atom2504+atom3963+atom2510*atom3987)*atom2516;
atom2184 =  5.0000000000000000e-01*atom2174*L_R+atom590;
atom3911 = atom2482*atom2517;
atom3910 =  atom2470+5.0000000000000000e-01*atom3908*L_R;
atom650 = -atom320+-5.0000000000000000e-01*atom594*L_R-uR_L+y-fsL+atom519-atom567*atom575;
atom3873 = -atom2520*atom2184;
atom3047 =  atom614+5.0000000000000000e-01*atom3045*L_R;
atom3799 = atom2520*dsR_L;
atom1123 = 2.0000000000000000e+00*aW_L;
atom2655 =  2.0*atom533+atom1123*atom497;
atom2656 = -atom2655*atom496;
atom2658 = atom2655*atom505;
atom2664 =  atom6*atom2656+atom2658*atom147;
atom2660 =  atom2658*atom145+atom5*atom2656;
atom3814 = -atom545*atom643+atom541*atom644;
atom557 =  uR_L-lR_L;
atom558 = aR_L*atom557;
atom559 =  bR_L+atom558;
atom626 =  atom559+atom558;
atom560 = atom559*atom557;
atom561 =  atom560+cR_L;
atom628 =  atom557*atom626+atom561;
atom647 = pow( (atom628*atom628)+1.0,-(1.0/2.0));
atom521 = atom506*atom3;
atom648 = atom647*atom628;
atom2595 = atom538*atom3;
atom4089 =  atom2595*atom648+atom647*atom2592;
atom2576 = -atom4*atom504;
atom4067 =  atom647*atom2573+atom2576*atom648;
atom2551 =  2.0*aR_L*atom557+bR_L;
atom2553 =  atom560+atom2551*atom557+cR_L;
atom2549 =  3.0*aR_L*atom557+bR_L;
atom2557 = -2.0*atom2553*atom2549*pow( (atom2553*atom2553)+1.0,-(3.0/2.0));
atom1127 = 2.0*aR_L;
atom1128 = atom1127*atom557;
atom1130 =  2.0*atom626+atom1128;
atom2560 =  atom1130*atom647+atom2557*atom628;
atom532 = atom3*atom504;
atom4081 =  atom531*atom2557+atom2560*atom532;
atom4051 = atom647*atom528;
atom4057 = atom2139*atom647;
atom522 =  atom521+uW_L*atom4;
atom2651 = -atom4*atom536+atom3;
atom4071 =  atom2651*atom648+atom2647*atom647;
atom1146 = -atom506*atom4;
atom4063 =  atom2560*( atom1146+atom3*uW_L-atom1076)+atom2557*atom2182;
atom2667 = atom2658*atom3;
atom546 = atom3*atom536;
atom547 =  atom546+atom4;
atom4096 =  atom2557*atom545+atom2560*atom547;
atom4053 = atom541*atom647;
atom4140 = -atom2557*atom2184;
atom4049 = atom2557*atom2178;
atom2554 = (atom2553*atom2553);
atom4112 =  atom2551+atom626+atom1128;
atom2556 = pow( atom2554+1.0,-(3.0/2.0));
atom4113 = 3.0000000000000000e+00*aR_L;
atom4119 =  -2.0*atom2553*atom4113*atom2556+-2.0*atom4112*atom2556*atom2549+12.0*(atom2553*atom2553)*(atom2549*atom2549)*pow( (atom2553*atom2553)+1.0,-(5.0/2.0));
atom4123 = -atom2560*atom628;
atom4109 = atom1130*atom2557;
atom4107 = 3.0*atom1127;
atom2604 =  atom2554*atom2514+atom2513*atom2554+atom2514;
atom2605 = pow(atom2604,-(3.0/2.0));
atom2623 =  atom2502*pow( ( bR_L+2.0*aR_L*( uR_L-lR_L))*( uR_L-lR_L)+( bR_L+aR_L*( uR_L-lR_L))*( uR_L-lR_L)+cR_L,2.0)+atom2502+atom2554*atom2504*atom2510;
atom2624 = -atom2605*atom2623;
atom630 = -atom623*atom628;
atom629 = atom625*atom628;
atom636 = pow( atom634+(atom629*atom629)+(atom630*atom630),-(1.0/2.0));
atom4326 = atom2624*atom2530;
atom4257 = pow(atom2604,-(5.0/2.0));
atom4329 = -3.0*atom4257*atom2623;
atom4337 = -atom2605*( atom2554*atom3963+atom3963+atom4003*atom2554*atom2504+atom2554*atom2510*atom3987)-atom4329*atom2623;
atom4340 =  2.0*atom4326+atom4337*atom623+atom636*atom4034;
atom2620 = atom2482*atom628;
atom4352 = atom2624*atom2620;
atom4356 =  atom636*atom3910*atom628+2.0*atom4352+atom4337*atom629;
atom2629 = -atom628*atom2530;
atom4342 = atom2624*atom2629;
atom4348 =  2.0*atom4342-atom636*atom4034*atom628+atom630*atom4337;
atom2632 =  atom2629*atom636+atom630*atom2624;
atom2627 =  atom2620*atom636+atom2624*atom629;
atom4149 = -atom531*atom2627+atom2632*atom528;
atom2637 =  atom636*atom2530+atom2624*atom623;
atom4173 =  atom2632*atom2573+atom2571*atom2627+atom2637*atom2576;
atom2601 =  atom2553*atom2549*atom2514+atom2513*atom2553*atom2549;
atom2606 = -2.0*atom2605*atom2601;
atom4368 =  -4.0*atom2605*( atom2504*atom2553*atom2510*atom2549+atom2486*atom2501*atom2553*atom2549)+-2.0*atom4329*atom2601;
atom4256 = atom2606*atom2530;
atom4381 =  atom4256+atom4368*atom623;
atom2611 = -atom1130*atom623;
atom4274 = -atom1130*atom636*atom2530;
atom4270 = atom2624*atom2611;
atom4273 = atom2629*atom2606;
atom4377 =  atom630*atom4368+atom4274+atom4273+atom4270;
atom2598 = atom1130*atom625;
atom4279 = atom1130*atom2482*atom636;
atom4283 = atom2624*atom2598;
atom4280 = atom2620*atom2606;
atom4372 =  atom4368*atom629+atom4279+atom4283+atom4280;
atom4207 =  atom2581*atom2632-atom2637*atom521+atom2627*atom2579;
atom4231 =  atom2632*atom2592+atom2637*atom2595+atom2588*atom2627;
atom2609 =  atom629*atom2606+atom2598*atom636;
atom2614 =  atom630*atom2606+atom2611*atom636;
atom2617 = atom623*atom2606;
atom4213 =  atom2609*atom2579-atom521*atom2617+atom2614*atom2581;
atom637 = atom629*atom636;
atom638 = atom630*atom636;
atom639 = atom623*atom636;
atom4186 = -atom1146*atom639-atom637*atom2136-atom638*atom2179;
atom673 =  atom531*atom638+atom637*atom528;
atom674 = atom532*atom639;
atom4224 = -( atom539+atom537)*atom637-atom638*( atom543+atom542)-atom546*atom639;
atom4158 =  atom638*atom2579-atom2581*atom637;
atom4162 =  atom2571*atom638-atom637*atom2573;
atom4179 =  atom2614*atom2573+atom2576*atom2617+atom2609*atom2571;
atom4200 = -atom538*atom639*atom4-atom638*atom538*atom146-atom538*atom637*atom144;
atom4166 = -atom637*atom2592+atom2588*atom638;
atom4253 =  atom3*atom2656*atom639-atom638*( atom2658*atom6-atom147*atom2656)+atom637*( atom145*atom2656-atom5*atom2658);
atom4237 =  atom2614*atom2592+atom2617*atom2595+atom2609*atom2588;
atom4255 =  atom4253*duW_L+atom4200*da+dthetaW_L*atom4224+atom4237*duR_L+atom4166*dc+dsR_L*atom4231;
atom4153 =  atom2614*atom528-atom2609*atom531;
atom4259 = 4.0*atom2553*atom2549;
atom4258 = -6.0*atom4257*atom2601;
atom4265 = -atom4258*atom2623-atom2605*( atom4259*atom2502+atom4259*atom2504*atom2510);
atom4276 =  atom630*atom4265+atom4274+atom4273+atom4270;
atom4285 =  atom629*atom4265+atom4279+atom4283+atom4280;
atom4267 =  atom4256+atom623*atom4265;
atom4299 =  -2.0*atom4258*atom2601+-2.0*atom2605*( atom2513*atom2553*atom4113+atom2553*atom4113*atom2514+atom4112*atom2513*atom2549+atom4112*atom2549*atom2514);
atom4317 = atom623*atom4299;
atom4309 = atom2611*atom2606;
atom4314 = -atom4107*atom623*atom636+atom630*atom4299+2.0*atom4309;
atom4301 = atom2598*atom2606;
atom4306 =  atom629*atom4299+atom4107*atom625*atom636+2.0*atom4301;
atom4470 =  atom2667*atom2637+atom2660*atom2627+atom2664*atom2632;
atom4437 =  atom2647*atom2632+atom2644*atom2627+atom2637*atom2651;
atom4406 = -atom2627*atom545+atom541*atom2632;
atom4424 =  atom2617*atom2651+atom2614*atom2647+atom2609*atom2644;
atom4402 =  atom638*atom2644-atom2647*atom637;
atom4418 = -atom2658*atom638*atom146-atom2658*atom639*atom4-atom2658*atom637*atom144;
atom4394 =  atom638*atom2660-atom637*atom2664;
atom4443 = 3.0*atom1123;
atom4444 = -atom4443*atom496;
atom4446 = atom4443*atom505;
atom4463 =  atom2667*atom2617+atom2614*atom2664+atom2609*atom2660;
atom4398 = -atom2609*atom545+atom2614*atom541;

_Gammat[0] = -dsR_R*( dy*atom2284-dsR_R*( atom2893*atom459+-2.0*atom3313+-2.0*atom3327+( atom438*atom3258+atom457*atom3308+2.0*atom3260)*( sR_R-atom329-x-atom319+5.0000000000000000e-01*atom405*atom409*L_R)-atom465*( atom3258*atom440+atom457*atom3319+2.0*atom3321)+( atom2291+5.0000000000000000e-01*atom405*L_R*atom2884+atom2293)*atom458)+atom3177*duW_R+atom3129*dc+atom3147*da-duR_R*atom2284+dthetaW_R*atom3165+atom2297*dx)-duW_R*( dsR_R*atom3177+dthetaW_R*atom3157+atom3121*dc+( atom2430*atom458+atom459*atom2426)*duW_R+atom3139*da)-dy*atom3114-atom2297*dsR_R*dx-da*( dthetaW_R*atom3143-da*( atom458*( atom319+atom326+atom328)-atom459*atom2768)+atom3147*dsR_R+atom3139*duW_R+atom3133*dc)+duR_R*atom3114-dc*( dsR_R*atom3129-dc*( atom2104*atom458-atom459*atom2060)+atom3133*da+atom3125*dthetaW_R+atom3121*duW_R)-dthetaW_R*( ( atom2346*atom458+atom2344*atom459)*dthetaW_R+atom3125*dc+dsR_R*atom3165+duW_R*atom3157+da*atom3143);
_Gammat[1] = -atom2321*duR_R*dy+dsR_R*( atom462*atom2893*dsR_R-atom3398*duR_R)-duR_R*( duR_R*( -2.0000000000000000e+00*atom2321+atom465*atom3411+2.0*atom3416-( atom3411*atom443+atom462*atom3422+2.0*atom3418)*( atom372*atom376-z+usRz+dR_R-atom321-atom337)-atom1075*atom463)+atom3365*da+atom3346*dc+dsR_R*atom3398+atom2321*dy+atom2326*dz+atom3380*dthetaW_R+duW_R*atom3392)-da*( duW_R*atom3357+atom3365*duR_R+atom3353*dthetaW_R-da*( ( atom321+atom337)*atom463-atom462*atom2768)+atom3344*dc)-atom2326*duR_R*dz-( dc*atom3340+atom3380*duR_R-dthetaW_R*( atom336*atom463-atom2344*atom462)+atom3375*duW_R+atom3353*da)*dthetaW_R-( da*atom3357+dc*atom3342+duW_R*( atom2421*atom463+atom462*atom2426)+duR_R*atom3392+atom3375*dthetaW_R)*duW_R-( atom3344*da+dthetaW_R*atom3340+atom462*atom2060*dc+duW_R*atom3342+atom3346*duR_R)*dc;
_Gammat[2] = -dsR_R*( dsR_R*( atom3634*atom347+atom3650*atom346+atom3642*atom343)+( atom3665*atom347+atom3670*atom343+atom346*atom3675)*duR_R+atom3535*duW_R+atom3447*dc+atom3506*dthetaW_R+da*atom3478)-dthetaW_R*( duR_R*atom3513+atom3506*dsR_R+da*atom3462+atom3438*dc-( atom489+atom488)*dthetaW_R+atom3500*duW_R)-( atom3447*dsR_R+duW_R*atom3443-dc*atom488+da*atom3451+duR_R*atom3455+atom3438*dthetaW_R)*dc-( dc*atom3451+duW_R*atom3472+dthetaW_R*atom3462+dsR_R*atom3478+duR_R*atom3489-da*( atom345*atom453+atom452*atom342+atom489))*da-duR_R*( atom3455*dc+( atom3568*atom343+atom3559*atom347+atom3577*atom346)*dsR_R+atom3542*duW_R+dthetaW_R*atom3513+atom3489*da+duR_R*( atom3601*atom343+atom3593*atom347+atom3609*atom346))-atom3544*duW_R;
_Gammat[3] = -dsR_R*( dsR_R*( atom3634*atom362+atom3642*atom356+atom360*atom3650)+dc*atom3684+duR_R*( atom3665*atom362+atom3670*atom356+atom360*atom3675)+atom3535*dthetaW_R+duW_R*atom3736+atom3705*da)-atom3544*dthetaW_R-( dsR_R*atom3736+da*atom3728+duR_R*atom3744+dthetaW_R*atom3529+atom3697*dc+duW_R*( atom3*atom454*atom3748+atom452*( atom145*atom3748+atom5*atom3752)+( atom147*atom3748+atom3752*atom6)*atom453))*duW_R-( dsR_R*atom3705+duW_R*atom3728+atom3689*dc-da*( atom362*atom454+atom453*( atom359+atom146)+( atom355+atom144)*atom452)+duR_R*atom3719+dthetaW_R*atom3472)*da-( duW_R*atom3697-( atom360*atom453+atom452*atom356)*dc+dsR_R*atom3684+atom3689*da+dthetaW_R*atom3443+duR_R*atom3693)*dc-( dc*atom3693+atom3542*dthetaW_R+duR_R*( atom360*atom3609+atom3593*atom362+atom3601*atom356)+atom3744*duW_R+da*atom3719+( atom3559*atom362+atom3577*atom360+atom3568*atom356)*dsR_R)*duR_R;
_Gammat[4] = -( atom3818*dsR_L+dthetaW_L*atom3810+atom3814*duW_L+da*atom3802+( atom2135*atom644-atom2178*atom643)*dc)*dc-dy*atom3799-dthetaW_L*( atom3851*dsR_L+dthetaW_L*( atom2579*atom643+atom2581*atom644)+da*atom3828+atom3847*duW_L+atom3810*dc)-( ( atom644*atom2664+atom2660*atom643)*duW_L+dc*atom3814+atom3832*da+dthetaW_L*atom3847+atom3863*dsR_L)*duW_L-dsR_L*dx*atom2533-( atom3818*dc+dx*atom2533+atom3863*duW_L+atom2520*dy-atom2520*duR_L+da*atom3836+dsR_L*( 2.0*atom3873+( 5.0000000000000000e-01*atom590*atom594*L_R-sR_L+x-atom319+atom514)*( atom642*atom4034+atom4012*atom623+2.0*atom4020)-atom3047*atom644+atom650*( atom642*atom3910+2.0*atom3911+atom625*atom4012)-( atom2527+-5.0000000000000000e-01*atom3045*atom590*L_R+atom2529)*atom643+2.0*atom4039)+dthetaW_L*atom3851)*dsR_L+duR_L*atom3799-da*( ( atom2923*atom644-( atom511+atom513-atom319)*atom643)*da+dc*atom3802+atom3836*dsR_L+atom3832*duW_L+dthetaW_L*atom3828);
_Gammat[5] =  dsR_L*( atom3047*atom647*dsR_L-duR_L*atom4140)-dthetaW_L*( da*atom4067+dthetaW_L*( atom2581*atom647-atom521*atom648)+atom4089*duW_L+duR_L*atom4081+atom4051*dc)-( atom4057*da+atom2135*atom647*dc+atom4049*duR_L+atom4053*duW_L+dthetaW_L*atom4051)*dc-( dthetaW_L*atom4089+( atom647*atom2664+atom2667*atom648)*duW_L+duR_L*atom4096+atom4071*da+dc*atom4053)*duW_L-atom2560*dz*duR_L-da*( atom4063*duR_L+atom4071*duW_L-da*( ( atom522-atom321)*atom648-atom2923*atom647)+atom4057*dc+dthetaW_L*atom4067)-atom2557*duR_L*dy-( dsR_L*atom4140+( -2.0000000000000000e+00*atom2557+2.0*atom4123-atom1130*atom648-( dR_L-z-atom522+usLz+atom557*atom561+atom321)*( atom4119*atom628+2.0*atom4109+atom4107*atom647)+atom4119*atom650)*duR_L+atom4049*dc+dthetaW_L*atom4081+atom2557*dy+atom4063*da+atom4096*duW_L+atom2560*dz)*duR_L;
_Gammat[6] = -dthetaW_L*( dsR_L*atom4207+dc*atom4158+atom4186*da+duR_L*atom4213+atom4224*duW_L-( atom673+atom674)*dthetaW_L)-( atom4166*duW_L+atom4153*duR_L-atom673*dc+dthetaW_L*atom4158+da*atom4162+dsR_L*atom4149)*dc-da*( dc*atom4162+atom4200*duW_L+dthetaW_L*atom4186+atom4179*duR_L-( atom638*atom529+atom637*atom526+atom674)*da+atom4173*dsR_L)-atom4255*duW_L-( ( atom531*atom4377+atom4372*atom528+atom532*atom4381)*duR_L+da*atom4173+dthetaW_L*atom4207+( atom4356*atom528+atom532*atom4340+atom531*atom4348)*dsR_L+atom4231*duW_L+dc*atom4149)*dsR_L-duR_L*( dthetaW_L*atom4213+atom4179*da+atom4237*duW_L+atom4153*dc+( atom531*atom4276+atom4267*atom532+atom4285*atom528)*dsR_L+duR_L*( atom4317*atom532+atom531*atom4314+atom528*atom4306));
_Gammat[7] = -da*( dthetaW_L*atom4200+dc*atom4402-da*( atom547*atom639+atom638*( atom542+atom146)+( atom144+atom537)*atom637)+atom4418*duW_L+dsR_L*atom4437+duR_L*atom4424)-dsR_L*( da*atom4437+atom4470*duW_L+( atom545*atom4348+atom541*atom4356+atom547*atom4340)*dsR_L+atom4406*dc+( atom541*atom4372+atom547*atom4381+atom545*atom4377)*duR_L+dthetaW_L*atom4231)-( atom4394*duW_L+dthetaW_L*atom4166-( atom638*atom545+atom541*atom637)*dc+da*atom4402+duR_L*atom4398+atom4406*dsR_L)*dc-( ( atom545*atom4314+atom541*atom4306+atom4317*atom547)*duR_L+dc*atom4398+atom4463*duW_L+( atom541*atom4285+atom545*atom4276+atom4267*atom547)*dsR_L+da*atom4424+atom4237*dthetaW_L)*duR_L-( atom4463*duR_L+atom4470*dsR_L+( ( atom5*atom4444+atom4446*atom145)*atom637+atom4446*atom3*atom639+atom638*( atom4446*atom147+atom6*atom4444))*duW_L+atom4418*da+atom4394*dc+atom4253*dthetaW_L)*duW_L-dthetaW_L*atom4255;

return _Gammat;
}

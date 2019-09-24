/*----------MQ.c lib3D_MEC exported-----------*/

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

#include "MQ.h"

#define x q[ 0 ]
#define y q[ 1 ]
#define z q[ 2 ]
#define a q[ 3 ]
#define b q[ 4 ]
#define c q[ 5 ]
#define a1 q[ 6 ]
#define a2 q[ 7 ]
#define a3 q[ 8 ]
#define a4 q[ 9 ]
#define a5 q[ 10 ]
#define a6 q[ 11 ]
#define b1 q[ 12 ]
#define b2 q[ 13 ]
#define b3 q[ 14 ]
#define b4 q[ 15 ]
#define b5 q[ 16 ]
#define b6 q[ 17 ]
#define s1 q[ 18 ]
#define s2 q[ 19 ]
#define s3 q[ 20 ]
#define s4 q[ 21 ]
#define s5 q[ 22 ]
#define s6 q[ 23 ]
#define dx dq[ 0 ]
#define dy dq[ 1 ]
#define dz dq[ 2 ]
#define da dq[ 3 ]
#define dB dq[ 4 ]
#define dc dq[ 5 ]
#define da1 dq[ 6 ]
#define da2 dq[ 7 ]
#define da3 dq[ 8 ]
#define da4 dq[ 9 ]
#define da5 dq[ 10 ]
#define da6 dq[ 11 ]
#define dB1 dq[ 12 ]
#define dB2 dq[ 13 ]
#define dB3 dq[ 14 ]
#define dB4 dq[ 15 ]
#define dB5 dq[ 16 ]
#define dB6 dq[ 17 ]
#define ds1 dq[ 18 ]
#define ds2 dq[ 19 ]
#define ds3 dq[ 20 ]
#define ds4 dq[ 21 ]
#define ds5 dq[ 22 ]
#define ds6 dq[ 23 ]
#define ddx ddq[ 0 ]
#define ddy ddq[ 1 ]
#define ddz ddq[ 2 ]
#define dda ddq[ 3 ]
#define ddB ddq[ 4 ]
#define ddc ddq[ 5 ]
#define dda1 ddq[ 6 ]
#define dda2 ddq[ 7 ]
#define dda3 ddq[ 8 ]
#define dda4 ddq[ 9 ]
#define dda5 ddq[ 10 ]
#define dda6 ddq[ 11 ]
#define ddB1 ddq[ 12 ]
#define ddB2 ddq[ 13 ]
#define ddB3 ddq[ 14 ]
#define ddB4 ddq[ 15 ]
#define ddB5 ddq[ 16 ]
#define ddB6 ddq[ 17 ]
#define dds1 ddq[ 18 ]
#define dds2 ddq[ 19 ]
#define dds3 ddq[ 20 ]
#define dds4 ddq[ 21 ]
#define dds5 ddq[ 22 ]
#define dds6 ddq[ 23 ]
#define g param[ 0 ]
#define R param[ 1 ]
#define r param[ 2 ]
#define L param[ 3 ]
#define e param[ 4 ]
#define mP param[ 5 ]
#define mxP param[ 6 ]
#define myP param[ 7 ]
#define mzP param[ 8 ]
#define IxxP param[ 9 ]
#define IxyP param[ 10 ]
#define IyyP param[ 11 ]
#define IxzP param[ 12 ]
#define IzzP param[ 13 ]
#define IyzP param[ 14 ]
#define m1 param[ 15 ]
#define mx1 param[ 16 ]
#define my1 param[ 17 ]
#define mz1 param[ 18 ]
#define Ixx1 param[ 19 ]
#define Ixy1 param[ 20 ]
#define Iyy1 param[ 21 ]
#define Ixz1 param[ 22 ]
#define Izz1 param[ 23 ]
#define Iyz1 param[ 24 ]
#define m2 param[ 25 ]
#define mx2 param[ 26 ]
#define my2 param[ 27 ]
#define mz2 param[ 28 ]
#define Ixx2 param[ 29 ]
#define Ixy2 param[ 30 ]
#define Iyy2 param[ 31 ]
#define Ixz2 param[ 32 ]
#define Izz2 param[ 33 ]
#define Iyz2 param[ 34 ]
#define m3 param[ 35 ]
#define mx3 param[ 36 ]
#define my3 param[ 37 ]
#define mz3 param[ 38 ]
#define Ixx3 param[ 39 ]
#define Ixy3 param[ 40 ]
#define Iyy3 param[ 41 ]
#define Ixz3 param[ 42 ]
#define Izz3 param[ 43 ]
#define Iyz3 param[ 44 ]
#define m4 param[ 45 ]
#define mx4 param[ 46 ]
#define my4 param[ 47 ]
#define mz4 param[ 48 ]
#define Ixx4 param[ 49 ]
#define Ixy4 param[ 50 ]
#define Iyy4 param[ 51 ]
#define Ixz4 param[ 52 ]
#define Izz4 param[ 53 ]
#define Iyz4 param[ 54 ]
#define m5 param[ 55 ]
#define mx5 param[ 56 ]
#define my5 param[ 57 ]
#define mz5 param[ 58 ]
#define Ixx5 param[ 59 ]
#define Ixy5 param[ 60 ]
#define Iyy5 param[ 61 ]
#define Ixz5 param[ 62 ]
#define Izz5 param[ 63 ]
#define Iyz5 param[ 64 ]
#define m6 param[ 65 ]
#define mx6 param[ 66 ]
#define my6 param[ 67 ]
#define mz6 param[ 68 ]
#define Ixx6 param[ 69 ]
#define Ixy6 param[ 70 ]
#define Iyy6 param[ 71 ]
#define Ixz6 param[ 72 ]
#define Izz6 param[ 73 ]
#define Iyz6 param[ 74 ]
#define Fs1 param[ 75 ]
#define Fs2 param[ 76 ]
#define Fs3 param[ 77 ]
#define Fs4 param[ 78 ]
#define Fs5 param[ 79 ]
#define Fs6 param[ 80 ]
#define FS001 param[ 81 ]
#define FSa11 param[ 82 ]
#define FSb11 param[ 83 ]
#define FSa21 param[ 84 ]
#define FSb21 param[ 85 ]
#define FS002 param[ 86 ]
#define FSa12 param[ 87 ]
#define FSb12 param[ 88 ]
#define FSa22 param[ 89 ]
#define FSb22 param[ 90 ]
#define FS003 param[ 91 ]
#define FSa13 param[ 92 ]
#define FSb13 param[ 93 ]
#define FSa23 param[ 94 ]
#define FSb23 param[ 95 ]
#define FS004 param[ 96 ]
#define FSa14 param[ 97 ]
#define FSb14 param[ 98 ]
#define FSa24 param[ 99 ]
#define FSb24 param[ 100 ]
#define FS005 param[ 101 ]
#define FSa15 param[ 102 ]
#define FSb15 param[ 103 ]
#define FSa25 param[ 104 ]
#define FSb25 param[ 105 ]
#define FS006 param[ 106 ]
#define FSa16 param[ 107 ]
#define FSb16 param[ 108 ]
#define FSa26 param[ 109 ]
#define FSb26 param[ 110 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define lambda3 unknowns[ 2 ]
#define lambda4 unknowns[ 3 ]
#define lambda5 unknowns[ 4 ]
#define lambda6 unknowns[ 5 ]
#define lambda7 unknowns[ 6 ]
#define lambda8 unknowns[ 7 ]
#define lambda9 unknowns[ 8 ]
#define lambda10 unknowns[ 9 ]
#define lambda11 unknowns[ 10 ]
#define lambda12 unknowns[ 11 ]
#define lambda13 unknowns[ 12 ]
#define lambda14 unknowns[ 13 ]
#define lambda15 unknowns[ 14 ]
#define lambda16 unknowns[ 15 ]
#define lambda17 unknowns[ 16 ]
#define lambda18 unknowns[ 17 ]

double atom38;
double atom39;
double atom40;
double atom37;
double atom47;
double atom48;
double atom2480;
double atom2477;
double atom2483;
double atom2466;
double atom2470;
double atom2467;
double atom2474;
double atom2558;
double atom2473;
double atom2555;
double atom2561;
double atom41;
double atom288;
double atom42;
double atom44;
double atom43;
double atom54;
double atom51;
double atom2529;
double atom70;
double atom46;
double atom45;
double atom60;
double atom57;
double atom2528;
double atom75;
double atom289;
double atom1532;
double atom1535;
double atom2492;
double atom2489;
double atom2486;
double atom2567;
double atom2564;
double atom2570;
double atom65;
double atom2498;
double atom2495;
double atom2501;
double atom2579;
double atom2576;
double atom2573;
double atom307;
double atom302;
double atom297;
double atom77;
double atom76;
double atom1539;
double atom3645;
double atom3642;
double atom2656;
double atom2645;
double atom2624;
double atom2627;
double atom2628;
double atom2685;
double atom2644;
double atom2684;
double atom2683;
double atom79;
double atom80;
double atom82;
double atom81;
double atom85;
double atom86;
double atom2697;
double atom2796;
double atom2807;
double atom2698;
double atom2785;
double atom2784;
double atom2795;
double atom83;
double atom84;
double atom100;
double atom89;
double atom101;
double atom104;
double atom103;
double atom106;
double atom105;
double atom110;
double atom109;
double atom113;
double atom125;
double atom107;
double atom108;
double atom124;
double atom2843;
double atom2931;
double atom2844;
double atom2930;
double atom2953;
double atom2942;
double atom2941;
double atom127;
double atom128;
double atom130;
double atom129;
double atom148;
double atom149;
double atom2989;
double atom3112;
double atom3101;
double atom2990;
double atom3090;
double atom3089;
double atom3100;
double atom131;
double atom133;
double atom135;
double atom144;
double atom134;
double atom147;
double atom159;
double atom141;
double atom165;
double atom138;
double atom132;
double atom154;
double atom166;
double atom168;
double atom169;
double atom171;
double atom170;
double atom189;
double atom188;
double atom175;
double atom173;
double atom181;
double atom172;
double atom178;
double atom194;
double atom187;
double atom206;
double atom184;
double atom174;
double atom199;
double atom205;
double atom3148;
double atom3260;
double atom3271;
double atom3149;
double atom3249;
double atom3248;
double atom3259;
double atom208;
double atom209;
double atom211;
double atom210;
double atom228;
double atom229;
double atom213;
double atom215;
double atom224;
double atom214;
double atom227;
double atom239;
double atom221;
double atom245;
double atom212;
double atom218;
double atom234;
double atom246;
double atom3308;
double atom3419;
double atom3418;
double atom3307;
double atom3408;
double atom3407;
double atom3430;
double atom249;
double atom248;
double atom250;
double atom269;
double atom251;
double atom268;
double atom3467;
double atom3566;
double atom3466;
double atom3567;
double atom3578;
double atom3577;
double atom3589;
double atom255;
double atom267;
double atom254;
double atom264;
double atom279;
double atom253;
double atom285;
double atom261;
double atom258;
double atom252;
double atom274;
double atom286;
double atom2735;
double atom2738;
double atom2741;
double atom2881;
double atom2884;
double atom2887;
double atom3043;
double atom3046;
double atom3040;
double atom3202;
double atom3205;
double atom3199;
double atom3358;
double atom3361;
double atom3364;
double atom3523;
double atom3517;
double atom3520;
double atom2506;
double atom2509;
double atom2514;
double atom2517;
double atom2522;
double atom2525;
double atom339;
double atom316;
double atom649;
double atom2710;
double atom763;
double atom2856;
double atom877;
double atom3002;
double atom1001;
double atom3161;
double atom1125;
double atom3320;
double atom1249;
double atom3479;
double atom2704;
double atom2850;
double atom2996;
double atom3155;
double atom3314;
double atom3473;

double * _MQ = NULL;
void Init_MQ ( ) 
{
    _MQ = malloc ( MQ_n_rows * MQ_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < MQ_n_rows * MQ_n_cols ; i++ ) {_MQ[i]=0.0;}
  }
}

void Done_MQ ( ) 
{
if (_MQ != NULL) 
free (_MQ ); 
_MQ = NULL; 
}


double * MQ ()
{
if ( _MQ == NULL )
 {
    _MQ = malloc ( MQ_n_rows * MQ_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < MQ_n_rows * MQ_n_cols ; i++ ) {_MQ[i]=0.0;}
  }
 }

atom38 = sin(c);
atom39 = cos(b);
atom40 = sin(b);
atom37 = cos(c);
atom47 = atom39*atom37;
atom48 = -atom38*atom39;
atom2480 =  atom47*mzP-mxP*atom40;
atom2477 =  myP*atom40-atom48*mzP;
atom2483 =  mxP*atom48-atom47*myP;
atom2466 = atom39*da;
atom2470 =  atom38*dB+atom2466*atom37;
atom2467 = da*atom40;
atom2474 =  dc+atom2467;
atom2558 =  atom2470*atom40-atom47*atom2474;
atom2473 =  dB*atom37-atom2466*atom38;
atom2555 = -atom2473*atom40+atom2474*atom48;
atom2561 =  atom47*atom2473-atom48*atom2470;
atom41 = cos(a);
atom288 = dc*atom40;
atom42 = sin(a);
atom44 = -atom42*atom39;
atom43 = atom42*atom40;
atom54 =  atom41*atom37-atom38*atom43;
atom51 =  atom43*atom37+atom41*atom38;
atom2529 = -atom41*atom288;
atom70 =  mxP*atom51+atom44*mzP+myP*atom54;
atom46 = atom41*atom39;
atom45 = -atom41*atom40;
atom60 = -atom38*atom45+atom42*atom37;
atom57 =  atom45*atom37+atom42*atom38;
atom2528 = atom288*atom42;
atom75 =  mxP*atom57+atom60*myP+atom46*mzP;
atom289 = dc*atom39;
atom1532 =  atom41*dB-atom42*atom289;
atom1535 =  atom42*dB+atom41*atom289;
atom2492 =  mxP*atom54-myP*atom51;
atom2489 = -mxP*atom44+mzP*atom51;
atom2486 = -atom54*mzP+atom44*myP;
atom2567 = -atom2474*atom51+atom44*atom2470;
atom2564 =  atom2474*atom54-atom44*atom2473;
atom2570 = -atom54*atom2470+atom2473*atom51;
atom65 =  mzP*atom40+atom47*mxP+myP*atom48;
atom2498 =  atom57*mzP-mxP*atom46;
atom2495 =  myP*atom46-atom60*mzP;
atom2501 =  atom60*mxP-atom57*myP;
atom2579 =  atom57*atom2473-atom60*atom2470;
atom2576 =  atom46*atom2470-atom57*atom2474;
atom2573 = -atom46*atom2473+atom60*atom2474;
atom307 =  IyzP*atom48+atom47*IxzP+IzzP*atom40;
atom302 =  atom48*IyyP+IyzP*atom40+atom47*IxyP;
atom297 =  IxyP*atom48+IxxP*atom47+atom40*IxzP;
atom77 = g*atom65;
atom76 = -atom70*g;
atom1539 =  atom44*atom77+atom76*atom40;
atom3645 =  atom77*atom54+atom48*atom76;
atom3642 =  atom47*atom76+atom77*atom51;
atom2656 = -IyzP*atom2470;
atom2645 = atom2473*IxzP;
atom2624 =  dc*atom2473-dB*atom2467*atom37;
atom2627 = -dc*atom2470+atom38*dB*atom2467;
atom2628 = atom2466*dB;
atom2685 =  atom2473*( IyyP*atom2470-IxyP*atom2473)+atom2624*IxzP+IzzP*atom2628-( IxxP*atom2473-IxyP*atom2470)*atom2470+IyzP*atom2627-atom2474*( atom2656+atom2645);
atom2644 = -atom2474*IxyP;
atom2684 =  IyyP*atom2627-( atom2644-atom2656)*atom2473+IxyP*atom2624+atom2474*( atom2474*IxzP-IzzP*atom2470)+atom2628*IyzP-( atom2470*IxzP-IxxP*atom2474)*atom2470;
atom2683 =  atom2628*IxzP+( atom2644+atom2645)*atom2470-( atom2474*IyyP-IyzP*atom2473)*atom2473+IxxP*atom2624+IxyP*atom2627+atom2474*( IzzP*atom2473-atom2474*IyzP);
atom79 = cos(b1);
atom80 = sin(b1);
atom82 = sin(a1);
atom81 = cos(a1);
atom85 = -atom80*atom81;
atom86 = atom81*atom79;
atom2697 = da1*atom79;
atom2796 = Ixz1*dB1;
atom2807 = -atom2697*Iyz1;
atom2698 = atom80*da1;
atom2785 = dB1*atom2697;
atom2784 = -atom2698*dB1;
atom2795 = -atom2698*Ixy1;
atom83 = atom80*atom82;
atom84 = -atom82*atom79;
atom100 = -g*( atom84*mz1+atom81*my1+mx1*atom83);
atom89 =  mx1*atom79+atom80*mz1;
atom101 = g*atom89;
atom104 = sin(b2);
atom103 = cos(b2);
atom106 = sin(a2);
atom105 = cos(a2);
atom110 = atom105*atom103;
atom109 = -atom104*atom105;
atom113 =  atom104*mz2+mx2*atom103;
atom125 = g*atom113;
atom107 = atom104*atom106;
atom108 = -atom106*atom103;
atom124 = -( atom105*my2+atom108*mz2+mx2*atom107)*g;
atom2843 = da2*atom103;
atom2931 = dB2*atom2843;
atom2844 = atom104*da2;
atom2930 = -dB2*atom2844;
atom2953 = -Iyz2*atom2843;
atom2942 = dB2*Ixz2;
atom2941 = -Ixy2*atom2844;
atom127 = cos(b3);
atom128 = sin(b3);
atom130 = sin(a3);
atom129 = cos(a3);
atom148 = -atom128*atom129;
atom149 = atom127*atom129;
atom2989 = atom127*da3;
atom3112 = -atom2989*Iyz3;
atom3101 = Ixz3*dB3;
atom2990 = atom128*da3;
atom3090 = atom2989*dB3;
atom3089 = -atom2990*dB3;
atom3100 = -atom2990*Ixy3;
atom131 = (1.0/2.0)*pow(3.0,(1.0/2.0));
atom133 = atom131*atom130;
atom135 = (1.0/2.0)*atom130;
atom144 =  atom131*atom127-atom135*atom128;
atom134 = -(1.0/2.0)*atom129;
atom147 =  atom127*atom135+atom131*atom128;
atom159 =  my3*atom134+atom144*mx3+atom147*mz3;
atom141 = -atom128/2.0+atom127*atom133;
atom165 = -atom159*g;
atom138 = -atom127/2.0-atom128*atom133;
atom132 = -atom131*atom129;
atom154 =  atom138*mx3+atom132*my3+atom141*mz3;
atom166 = g*atom154;
atom168 = cos(b4);
atom169 = sin(b4);
atom171 = sin(a4);
atom170 = cos(a4);
atom189 = atom170*atom168;
atom188 = -atom169*atom170;
atom175 = (1.0/2.0)*atom171;
atom173 = atom131*atom171;
atom181 = -atom169/2.0+atom173*atom168;
atom172 = -atom131*atom170;
atom178 = -atom173*atom169-atom168/2.0;
atom194 =  atom172*my4+mz4*atom181+atom178*mx4;
atom187 =  atom131*atom169+atom175*atom168;
atom206 = g*atom194;
atom184 = -atom175*atom169+atom131*atom168;
atom174 = -(1.0/2.0)*atom170;
atom199 =  mx4*atom184+mz4*atom187+atom174*my4;
atom205 = -atom199*g;
atom3148 = da4*atom168;
atom3260 = Ixz4*dB4;
atom3271 = -atom3148*Iyz4;
atom3149 = atom169*da4;
atom3249 = atom3148*dB4;
atom3248 = -dB4*atom3149;
atom3259 = -Ixy4*atom3149;
atom208 = cos(b5);
atom209 = sin(b5);
atom211 = sin(a5);
atom210 = cos(a5);
atom228 = -atom209*atom210;
atom229 = atom210*atom208;
atom213 = -atom131*atom211;
atom215 = (1.0/2.0)*atom211;
atom224 = -atom209*atom215-atom131*atom208;
atom214 = -(1.0/2.0)*atom210;
atom227 =  atom215*atom208-atom131*atom209;
atom239 =  mz5*atom227+atom224*mx5+my5*atom214;
atom221 = -atom209/2.0+atom213*atom208;
atom245 = -atom239*g;
atom212 = atom131*atom210;
atom218 = -atom209*atom213-atom208/2.0;
atom234 =  mx5*atom218+mz5*atom221+atom212*my5;
atom246 = g*atom234;
atom3308 = atom209*da5;
atom3419 = Ixz5*dB5;
atom3418 = -atom3308*Ixy5;
atom3307 = da5*atom208;
atom3408 = atom3307*dB5;
atom3407 = -atom3308*dB5;
atom3430 = -Iyz5*atom3307;
atom249 = sin(b6);
atom248 = cos(b6);
atom250 = cos(a6);
atom269 = atom250*atom248;
atom251 = sin(a6);
atom268 = -atom250*atom249;
atom3467 = da6*atom249;
atom3566 = -atom3467*dB6;
atom3466 = da6*atom248;
atom3567 = atom3466*dB6;
atom3578 = Ixz6*dB6;
atom3577 = -atom3467*Ixy6;
atom3589 = -Iyz6*atom3466;
atom255 = (1.0/2.0)*atom251;
atom267 =  atom248*atom255-atom131*atom249;
atom254 = -(1.0/2.0)*atom250;
atom264 = -atom255*atom249-atom131*atom248;
atom279 =  atom254*my6+atom264*mx6+mz6*atom267;
atom253 = -atom131*atom251;
atom285 = -atom279*g;
atom261 =  atom253*atom248-atom249/2.0;
atom258 = -atom253*atom249-atom248/2.0;
atom252 = atom131*atom250;
atom274 =  atom261*mz6+atom252*my6+mx6*atom258;
atom286 = atom274*g;
atom2735 =  atom2698*atom82-dB1*atom86;
atom2738 = -atom2698*atom85+atom2697*atom86;
atom2741 =  atom85*dB1-atom2697*atom82;
atom2881 =  atom2844*atom106-dB2*atom110;
atom2884 = -atom109*atom2844+atom110*atom2843;
atom2887 =  atom109*dB2-atom106*atom2843;
atom3043 = -atom2990*atom148+atom2989*atom149;
atom3046 =  atom148*dB3-atom2989*atom130;
atom3040 =  atom2990*atom130-atom149*dB3;
atom3202 =  atom3148*atom189-atom188*atom3149;
atom3205 =  atom188*dB4-atom3148*atom171;
atom3199 =  atom171*atom3149-atom189*dB4;
atom3358 = -dB5*atom229+atom211*atom3308;
atom3361 = -atom3308*atom228+atom3307*atom229;
atom3364 =  dB5*atom228-atom211*atom3307;
atom3523 =  atom268*dB6-atom3466*atom251;
atom3517 = -dB6*atom269+atom3467*atom251;
atom3520 = -atom268*atom3467+atom3466*atom269;
atom2506 =  atom47*atom2477+atom2483*atom40+atom48*atom2480;
atom2509 =  atom2480*atom37+atom38*atom2477;
atom2514 =  atom48*atom2489+atom2486*atom47+atom2492*atom40;
atom2517 =  atom2489*atom37+atom2486*atom38;
atom2522 =  atom2501*atom40+atom48*atom2498+atom47*atom2495;
atom2525 =  atom2498*atom37+atom38*atom2495;
atom339 =  atom38*atom297+atom302*atom37;
atom316 =  atom38*IxzP+IyzP*atom37;
atom649 =  Ixy1*atom79+atom80*Iyz1;
atom2710 = -atom80*( atom85*my1-mx1*atom82)-( atom82*mz1-my1*atom86)*atom79;
atom763 =  atom104*Iyz2+Ixy2*atom103;
atom2856 =  ( my2*atom110-atom106*mz2)*atom103+atom104*( mx2*atom106-atom109*my2);
atom877 =  atom127*Ixy3+atom128*Iyz3;
atom3002 = -atom127*( atom130*mz3-my3*atom149)-atom128*( my3*atom148-mx3*atom130);
atom1001 =  atom169*Iyz4+Ixy4*atom168;
atom3161 =  atom169*( mx4*atom171-my4*atom188)+( atom189*my4-mz4*atom171)*atom168;
atom1125 =  Iyz5*atom209+Ixy5*atom208;
atom3320 = -( mz5*atom211-my5*atom229)*atom208+atom209*( atom211*mx5-my5*atom228);
atom1249 =  Iyz6*atom249+atom248*Ixy6;
atom3479 =  ( atom269*my6-mz6*atom251)*atom248+( atom251*mx6-atom268*my6)*atom249;
atom2704 = -mx1*atom86+atom85*mz1;
atom2850 =  atom109*mz2-mx2*atom110;
atom2996 =  atom148*mz3-mx3*atom149;
atom3155 =  mz4*atom188-mx4*atom189;
atom3314 =  mz5*atom228-mx5*atom229;
atom3473 = -mx6*atom269+atom268*mz6;

_MQ[0] = -mP;
_MQ[1] = 0.0;
_MQ[2] = 0.0;
_MQ[3] = -atom2506;
_MQ[4] = -atom2509;
_MQ[5] = -atom2483;
_MQ[6] = 0.0;
_MQ[7] = 0.0;
_MQ[8] = 0.0;
_MQ[9] = 0.0;
_MQ[10] = 0.0;
_MQ[11] = 0.0;
_MQ[12] = 0.0;
_MQ[13] = 0.0;
_MQ[14] = 0.0;
_MQ[15] = 0.0;
_MQ[16] = 0.0;
_MQ[17] = 0.0;
_MQ[18] = 0.0;
_MQ[19] = 0.0;
_MQ[20] = 0.0;
_MQ[21] = 0.0;
_MQ[22] = 0.0;
_MQ[23] = 0.0;
_MQ[24] = 0.0;
_MQ[25] = -mP;
_MQ[26] = 0.0;
_MQ[27] = -atom2514;
_MQ[28] = -atom2517;
_MQ[29] = -atom2492;
_MQ[30] = 0.0;
_MQ[31] = 0.0;
_MQ[32] = 0.0;
_MQ[33] = 0.0;
_MQ[34] = 0.0;
_MQ[35] = 0.0;
_MQ[36] = 0.0;
_MQ[37] = 0.0;
_MQ[38] = 0.0;
_MQ[39] = 0.0;
_MQ[40] = 0.0;
_MQ[41] = 0.0;
_MQ[42] = 0.0;
_MQ[43] = 0.0;
_MQ[44] = 0.0;
_MQ[45] = 0.0;
_MQ[46] = 0.0;
_MQ[47] = 0.0;
_MQ[48] = 0.0;
_MQ[49] = 0.0;
_MQ[50] = -mP;
_MQ[51] = -atom2522;
_MQ[52] = -atom2525;
_MQ[53] = -atom2501;
_MQ[54] = 0.0;
_MQ[55] = 0.0;
_MQ[56] = 0.0;
_MQ[57] = 0.0;
_MQ[58] = 0.0;
_MQ[59] = 0.0;
_MQ[60] = 0.0;
_MQ[61] = 0.0;
_MQ[62] = 0.0;
_MQ[63] = 0.0;
_MQ[64] = 0.0;
_MQ[65] = 0.0;
_MQ[66] = 0.0;
_MQ[67] = 0.0;
_MQ[68] = 0.0;
_MQ[69] = 0.0;
_MQ[70] = 0.0;
_MQ[71] = 0.0;
_MQ[72] = -atom2506;
_MQ[73] = -atom2514;
_MQ[74] = -atom2522;
_MQ[75] = -atom307*atom40-atom47*atom297-atom302*atom48;
_MQ[76] = -atom339;
_MQ[77] = -atom307;
_MQ[78] = 0.0;
_MQ[79] = 0.0;
_MQ[80] = 0.0;
_MQ[81] = 0.0;
_MQ[82] = 0.0;
_MQ[83] = 0.0;
_MQ[84] = 0.0;
_MQ[85] = 0.0;
_MQ[86] = 0.0;
_MQ[87] = 0.0;
_MQ[88] = 0.0;
_MQ[89] = 0.0;
_MQ[90] = 0.0;
_MQ[91] = 0.0;
_MQ[92] = 0.0;
_MQ[93] = 0.0;
_MQ[94] = 0.0;
_MQ[95] = 0.0;
_MQ[96] = -atom2509;
_MQ[97] = -atom2517;
_MQ[98] = -atom2525;
_MQ[99] = -atom339;
_MQ[100] = -( IyyP*atom37+IxyP*atom38)*atom37-( IxxP*atom38+IxyP*atom37)*atom38;
_MQ[101] = -atom316;
_MQ[102] = 0.0;
_MQ[103] = 0.0;
_MQ[104] = 0.0;
_MQ[105] = 0.0;
_MQ[106] = 0.0;
_MQ[107] = 0.0;
_MQ[108] = 0.0;
_MQ[109] = 0.0;
_MQ[110] = 0.0;
_MQ[111] = 0.0;
_MQ[112] = 0.0;
_MQ[113] = 0.0;
_MQ[114] = 0.0;
_MQ[115] = 0.0;
_MQ[116] = 0.0;
_MQ[117] = 0.0;
_MQ[118] = 0.0;
_MQ[119] = 0.0;
_MQ[120] = -atom2483;
_MQ[121] = -atom2492;
_MQ[122] = -atom2501;
_MQ[123] = -atom307;
_MQ[124] = -atom316;
_MQ[125] = -IzzP;
_MQ[126] = 0.0;
_MQ[127] = 0.0;
_MQ[128] = 0.0;
_MQ[129] = 0.0;
_MQ[130] = 0.0;
_MQ[131] = 0.0;
_MQ[132] = 0.0;
_MQ[133] = 0.0;
_MQ[134] = 0.0;
_MQ[135] = 0.0;
_MQ[136] = 0.0;
_MQ[137] = 0.0;
_MQ[138] = 0.0;
_MQ[139] = 0.0;
_MQ[140] = 0.0;
_MQ[141] = 0.0;
_MQ[142] = 0.0;
_MQ[143] = 0.0;
_MQ[144] = 0.0;
_MQ[145] = 0.0;
_MQ[146] = 0.0;
_MQ[147] = 0.0;
_MQ[148] = 0.0;
_MQ[149] = 0.0;
_MQ[150] = -atom79*( Ixz1*atom80+Ixx1*atom79)-atom80*( atom80*Izz1+Ixz1*atom79);
_MQ[151] = 0.0;
_MQ[152] = 0.0;
_MQ[153] = 0.0;
_MQ[154] = 0.0;
_MQ[155] = 0.0;
_MQ[156] = -atom649;
_MQ[157] = 0.0;
_MQ[158] = 0.0;
_MQ[159] = 0.0;
_MQ[160] = 0.0;
_MQ[161] = 0.0;
_MQ[162] = -atom2710;
_MQ[163] = 0.0;
_MQ[164] = 0.0;
_MQ[165] = 0.0;
_MQ[166] = 0.0;
_MQ[167] = 0.0;
_MQ[168] = 0.0;
_MQ[169] = 0.0;
_MQ[170] = 0.0;
_MQ[171] = 0.0;
_MQ[172] = 0.0;
_MQ[173] = 0.0;
_MQ[174] = 0.0;
_MQ[175] = -atom104*( Ixz2*atom103+atom104*Izz2)-( Ixx2*atom103+atom104*Ixz2)*atom103;
_MQ[176] = 0.0;
_MQ[177] = 0.0;
_MQ[178] = 0.0;
_MQ[179] = 0.0;
_MQ[180] = 0.0;
_MQ[181] = -atom763;
_MQ[182] = 0.0;
_MQ[183] = 0.0;
_MQ[184] = 0.0;
_MQ[185] = 0.0;
_MQ[186] = 0.0;
_MQ[187] = -atom2856;
_MQ[188] = 0.0;
_MQ[189] = 0.0;
_MQ[190] = 0.0;
_MQ[191] = 0.0;
_MQ[192] = 0.0;
_MQ[193] = 0.0;
_MQ[194] = 0.0;
_MQ[195] = 0.0;
_MQ[196] = 0.0;
_MQ[197] = 0.0;
_MQ[198] = 0.0;
_MQ[199] = 0.0;
_MQ[200] = -atom127*( Ixz3*atom128+atom127*Ixx3)-( atom128*Izz3+atom127*Ixz3)*atom128;
_MQ[201] = 0.0;
_MQ[202] = 0.0;
_MQ[203] = 0.0;
_MQ[204] = 0.0;
_MQ[205] = 0.0;
_MQ[206] = -atom877;
_MQ[207] = 0.0;
_MQ[208] = 0.0;
_MQ[209] = 0.0;
_MQ[210] = 0.0;
_MQ[211] = 0.0;
_MQ[212] = -atom3002;
_MQ[213] = 0.0;
_MQ[214] = 0.0;
_MQ[215] = 0.0;
_MQ[216] = 0.0;
_MQ[217] = 0.0;
_MQ[218] = 0.0;
_MQ[219] = 0.0;
_MQ[220] = 0.0;
_MQ[221] = 0.0;
_MQ[222] = 0.0;
_MQ[223] = 0.0;
_MQ[224] = 0.0;
_MQ[225] = -( Ixx4*atom168+atom169*Ixz4)*atom168-atom169*( atom169*Izz4+Ixz4*atom168);
_MQ[226] = 0.0;
_MQ[227] = 0.0;
_MQ[228] = 0.0;
_MQ[229] = 0.0;
_MQ[230] = 0.0;
_MQ[231] = -atom1001;
_MQ[232] = 0.0;
_MQ[233] = 0.0;
_MQ[234] = 0.0;
_MQ[235] = 0.0;
_MQ[236] = 0.0;
_MQ[237] = -atom3161;
_MQ[238] = 0.0;
_MQ[239] = 0.0;
_MQ[240] = 0.0;
_MQ[241] = 0.0;
_MQ[242] = 0.0;
_MQ[243] = 0.0;
_MQ[244] = 0.0;
_MQ[245] = 0.0;
_MQ[246] = 0.0;
_MQ[247] = 0.0;
_MQ[248] = 0.0;
_MQ[249] = 0.0;
_MQ[250] = -atom209*( atom209*Izz5+Ixz5*atom208)-( Ixx5*atom208+atom209*Ixz5)*atom208;
_MQ[251] = 0.0;
_MQ[252] = 0.0;
_MQ[253] = 0.0;
_MQ[254] = 0.0;
_MQ[255] = 0.0;
_MQ[256] = -atom1125;
_MQ[257] = 0.0;
_MQ[258] = 0.0;
_MQ[259] = 0.0;
_MQ[260] = 0.0;
_MQ[261] = 0.0;
_MQ[262] = -atom3320;
_MQ[263] = 0.0;
_MQ[264] = 0.0;
_MQ[265] = 0.0;
_MQ[266] = 0.0;
_MQ[267] = 0.0;
_MQ[268] = 0.0;
_MQ[269] = 0.0;
_MQ[270] = 0.0;
_MQ[271] = 0.0;
_MQ[272] = 0.0;
_MQ[273] = 0.0;
_MQ[274] = 0.0;
_MQ[275] = -( Ixz6*atom248+Izz6*atom249)*atom249-atom248*( Ixz6*atom249+Ixx6*atom248);
_MQ[276] = 0.0;
_MQ[277] = 0.0;
_MQ[278] = 0.0;
_MQ[279] = 0.0;
_MQ[280] = 0.0;
_MQ[281] = -atom1249;
_MQ[282] = 0.0;
_MQ[283] = 0.0;
_MQ[284] = 0.0;
_MQ[285] = 0.0;
_MQ[286] = 0.0;
_MQ[287] = -atom3479;
_MQ[288] = 0.0;
_MQ[289] = 0.0;
_MQ[290] = 0.0;
_MQ[291] = 0.0;
_MQ[292] = 0.0;
_MQ[293] = 0.0;
_MQ[294] = -atom649;
_MQ[295] = 0.0;
_MQ[296] = 0.0;
_MQ[297] = 0.0;
_MQ[298] = 0.0;
_MQ[299] = 0.0;
_MQ[300] = -Iyy1;
_MQ[301] = 0.0;
_MQ[302] = 0.0;
_MQ[303] = 0.0;
_MQ[304] = 0.0;
_MQ[305] = 0.0;
_MQ[306] = -atom2704;
_MQ[307] = 0.0;
_MQ[308] = 0.0;
_MQ[309] = 0.0;
_MQ[310] = 0.0;
_MQ[311] = 0.0;
_MQ[312] = 0.0;
_MQ[313] = 0.0;
_MQ[314] = 0.0;
_MQ[315] = 0.0;
_MQ[316] = 0.0;
_MQ[317] = 0.0;
_MQ[318] = 0.0;
_MQ[319] = -atom763;
_MQ[320] = 0.0;
_MQ[321] = 0.0;
_MQ[322] = 0.0;
_MQ[323] = 0.0;
_MQ[324] = 0.0;
_MQ[325] = -Iyy2;
_MQ[326] = 0.0;
_MQ[327] = 0.0;
_MQ[328] = 0.0;
_MQ[329] = 0.0;
_MQ[330] = 0.0;
_MQ[331] = -atom2850;
_MQ[332] = 0.0;
_MQ[333] = 0.0;
_MQ[334] = 0.0;
_MQ[335] = 0.0;
_MQ[336] = 0.0;
_MQ[337] = 0.0;
_MQ[338] = 0.0;
_MQ[339] = 0.0;
_MQ[340] = 0.0;
_MQ[341] = 0.0;
_MQ[342] = 0.0;
_MQ[343] = 0.0;
_MQ[344] = -atom877;
_MQ[345] = 0.0;
_MQ[346] = 0.0;
_MQ[347] = 0.0;
_MQ[348] = 0.0;
_MQ[349] = 0.0;
_MQ[350] = -Iyy3;
_MQ[351] = 0.0;
_MQ[352] = 0.0;
_MQ[353] = 0.0;
_MQ[354] = 0.0;
_MQ[355] = 0.0;
_MQ[356] = -atom2996;
_MQ[357] = 0.0;
_MQ[358] = 0.0;
_MQ[359] = 0.0;
_MQ[360] = 0.0;
_MQ[361] = 0.0;
_MQ[362] = 0.0;
_MQ[363] = 0.0;
_MQ[364] = 0.0;
_MQ[365] = 0.0;
_MQ[366] = 0.0;
_MQ[367] = 0.0;
_MQ[368] = 0.0;
_MQ[369] = -atom1001;
_MQ[370] = 0.0;
_MQ[371] = 0.0;
_MQ[372] = 0.0;
_MQ[373] = 0.0;
_MQ[374] = 0.0;
_MQ[375] = -Iyy4;
_MQ[376] = 0.0;
_MQ[377] = 0.0;
_MQ[378] = 0.0;
_MQ[379] = 0.0;
_MQ[380] = 0.0;
_MQ[381] = -atom3155;
_MQ[382] = 0.0;
_MQ[383] = 0.0;
_MQ[384] = 0.0;
_MQ[385] = 0.0;
_MQ[386] = 0.0;
_MQ[387] = 0.0;
_MQ[388] = 0.0;
_MQ[389] = 0.0;
_MQ[390] = 0.0;
_MQ[391] = 0.0;
_MQ[392] = 0.0;
_MQ[393] = 0.0;
_MQ[394] = -atom1125;
_MQ[395] = 0.0;
_MQ[396] = 0.0;
_MQ[397] = 0.0;
_MQ[398] = 0.0;
_MQ[399] = 0.0;
_MQ[400] = -Iyy5;
_MQ[401] = 0.0;
_MQ[402] = 0.0;
_MQ[403] = 0.0;
_MQ[404] = 0.0;
_MQ[405] = 0.0;
_MQ[406] = -atom3314;
_MQ[407] = 0.0;
_MQ[408] = 0.0;
_MQ[409] = 0.0;
_MQ[410] = 0.0;
_MQ[411] = 0.0;
_MQ[412] = 0.0;
_MQ[413] = 0.0;
_MQ[414] = 0.0;
_MQ[415] = 0.0;
_MQ[416] = 0.0;
_MQ[417] = 0.0;
_MQ[418] = 0.0;
_MQ[419] = -atom1249;
_MQ[420] = 0.0;
_MQ[421] = 0.0;
_MQ[422] = 0.0;
_MQ[423] = 0.0;
_MQ[424] = 0.0;
_MQ[425] = -Iyy6;
_MQ[426] = 0.0;
_MQ[427] = 0.0;
_MQ[428] = 0.0;
_MQ[429] = 0.0;
_MQ[430] = 0.0;
_MQ[431] = -atom3473;
_MQ[432] = 0.0;
_MQ[433] = 0.0;
_MQ[434] = 0.0;
_MQ[435] = 0.0;
_MQ[436] = 0.0;
_MQ[437] = 0.0;
_MQ[438] = -atom2710;
_MQ[439] = 0.0;
_MQ[440] = 0.0;
_MQ[441] = 0.0;
_MQ[442] = 0.0;
_MQ[443] = 0.0;
_MQ[444] = -atom2704;
_MQ[445] = 0.0;
_MQ[446] = 0.0;
_MQ[447] = 0.0;
_MQ[448] = 0.0;
_MQ[449] = 0.0;
_MQ[450] = -m1;
_MQ[451] = 0.0;
_MQ[452] = 0.0;
_MQ[453] = 0.0;
_MQ[454] = 0.0;
_MQ[455] = 0.0;
_MQ[456] = 0.0;
_MQ[457] = 0.0;
_MQ[458] = 0.0;
_MQ[459] = 0.0;
_MQ[460] = 0.0;
_MQ[461] = 0.0;
_MQ[462] = 0.0;
_MQ[463] = -atom2856;
_MQ[464] = 0.0;
_MQ[465] = 0.0;
_MQ[466] = 0.0;
_MQ[467] = 0.0;
_MQ[468] = 0.0;
_MQ[469] = -atom2850;
_MQ[470] = 0.0;
_MQ[471] = 0.0;
_MQ[472] = 0.0;
_MQ[473] = 0.0;
_MQ[474] = 0.0;
_MQ[475] = -m2;
_MQ[476] = 0.0;
_MQ[477] = 0.0;
_MQ[478] = 0.0;
_MQ[479] = 0.0;
_MQ[480] = 0.0;
_MQ[481] = 0.0;
_MQ[482] = 0.0;
_MQ[483] = 0.0;
_MQ[484] = 0.0;
_MQ[485] = 0.0;
_MQ[486] = 0.0;
_MQ[487] = 0.0;
_MQ[488] = -atom3002;
_MQ[489] = 0.0;
_MQ[490] = 0.0;
_MQ[491] = 0.0;
_MQ[492] = 0.0;
_MQ[493] = 0.0;
_MQ[494] = -atom2996;
_MQ[495] = 0.0;
_MQ[496] = 0.0;
_MQ[497] = 0.0;
_MQ[498] = 0.0;
_MQ[499] = 0.0;
_MQ[500] = -m3;
_MQ[501] = 0.0;
_MQ[502] = 0.0;
_MQ[503] = 0.0;
_MQ[504] = 0.0;
_MQ[505] = 0.0;
_MQ[506] = 0.0;
_MQ[507] = 0.0;
_MQ[508] = 0.0;
_MQ[509] = 0.0;
_MQ[510] = 0.0;
_MQ[511] = 0.0;
_MQ[512] = 0.0;
_MQ[513] = -atom3161;
_MQ[514] = 0.0;
_MQ[515] = 0.0;
_MQ[516] = 0.0;
_MQ[517] = 0.0;
_MQ[518] = 0.0;
_MQ[519] = -atom3155;
_MQ[520] = 0.0;
_MQ[521] = 0.0;
_MQ[522] = 0.0;
_MQ[523] = 0.0;
_MQ[524] = 0.0;
_MQ[525] = -m4;
_MQ[526] = 0.0;
_MQ[527] = 0.0;
_MQ[528] = 0.0;
_MQ[529] = 0.0;
_MQ[530] = 0.0;
_MQ[531] = 0.0;
_MQ[532] = 0.0;
_MQ[533] = 0.0;
_MQ[534] = 0.0;
_MQ[535] = 0.0;
_MQ[536] = 0.0;
_MQ[537] = 0.0;
_MQ[538] = -atom3320;
_MQ[539] = 0.0;
_MQ[540] = 0.0;
_MQ[541] = 0.0;
_MQ[542] = 0.0;
_MQ[543] = 0.0;
_MQ[544] = -atom3314;
_MQ[545] = 0.0;
_MQ[546] = 0.0;
_MQ[547] = 0.0;
_MQ[548] = 0.0;
_MQ[549] = 0.0;
_MQ[550] = -m5;
_MQ[551] = 0.0;
_MQ[552] = 0.0;
_MQ[553] = 0.0;
_MQ[554] = 0.0;
_MQ[555] = 0.0;
_MQ[556] = 0.0;
_MQ[557] = 0.0;
_MQ[558] = 0.0;
_MQ[559] = 0.0;
_MQ[560] = 0.0;
_MQ[561] = 0.0;
_MQ[562] = 0.0;
_MQ[563] = -atom3479;
_MQ[564] = 0.0;
_MQ[565] = 0.0;
_MQ[566] = 0.0;
_MQ[567] = 0.0;
_MQ[568] = 0.0;
_MQ[569] = -atom3473;
_MQ[570] = 0.0;
_MQ[571] = 0.0;
_MQ[572] = 0.0;
_MQ[573] = 0.0;
_MQ[574] = 0.0;
_MQ[575] = -m6;
_MQ[576] = -dB*( atom2529*atom70-atom2528*atom75)+mzP*( atom2555*atom2473-atom2558*atom2470)-( atom70*atom1532+atom1535*atom75)*da+mxP*( atom2474*atom2558-atom2473*atom2561)+myP*( atom2561*atom2470-atom2474*atom2555);
_MQ[577] =  dB*( atom2529*atom65-atom289*atom75)-( atom2470*atom2567-atom2564*atom2473)*mzP-mxP*( atom2473*atom2570-atom2474*atom2567)-( atom2474*atom2564-atom2470*atom2570)*myP+da*atom1532*atom65;
_MQ[578] =  myP*( atom2579*atom2470-atom2474*atom2573)+( atom70*atom289-atom2528*atom65)*dB-mxP*( atom2579*atom2473-atom2474*atom2576)+atom1535*da*atom65+g*mP-( atom2576*atom2470-atom2573*atom2473)*mzP;
_MQ[579] = -atom47*atom3642-atom40*atom1539+atom47*atom2683+atom40*atom2685+atom2684*atom48-atom48*atom3645;
_MQ[580] =  atom2684*atom37-atom37*atom3645+atom38*atom2683-atom38*atom3642;
_MQ[581] =  atom2685-atom1539;
_MQ[582] = -( atom101*atom83+atom100*atom79)*atom79+atom80*( dB1*( atom2697*Iyy1-dB1*Ixy1)+Ixz1*atom2784+( Ixy1*atom2697-dB1*Ixx1)*atom2697-atom2698*( atom2796+atom2807)+atom2785*Izz1)-atom80*( atom80*atom100+atom84*atom101)-( atom2698*( atom2698*Iyz1-dB1*Izz1)-atom2785*Ixz1-Ixx1*atom2784-( atom2796+atom2795)*atom2697+dB1*( atom2698*Iyy1-dB1*Iyz1))*atom79;
_MQ[583] =  atom104*( Ixz2*atom2930-( atom2953+atom2942)*atom2844-( dB2*Ixx2-Ixy2*atom2843)*atom2843+atom2931*Izz2-dB2*( dB2*Ixy2-Iyy2*atom2843))+( Ixx2*atom2930+( dB2*Izz2-atom2844*Iyz2)*atom2844+Ixz2*atom2931+( atom2942+atom2941)*atom2843+dB2*( dB2*Iyz2-atom2844*Iyy2))*atom103-( atom125*atom107+atom124*atom103)*atom103-atom104*( atom108*atom125+atom104*atom124);
_MQ[584] = -atom127*( atom138*atom165+atom144*atom166)+atom128*( atom3090*Izz3+Ixz3*atom3089+atom2989*( Ixy3*atom2989-Ixx3*dB3)-( atom3112+atom3101)*atom2990+( atom2989*Iyy3-Ixy3*dB3)*dB3)+atom127*( atom3090*Ixz3+Ixx3*atom3089-( atom2990*Iyy3-Iyz3*dB3)*dB3+atom2989*( atom3101+atom3100)-atom2990*( atom2990*Iyz3-Izz3*dB3))-atom128*( atom147*atom166+atom141*atom165);
_MQ[585] =  atom169*( atom3249*Izz4+atom3248*Ixz4-atom3148*( Ixx4*dB4-atom3148*Ixy4)-( Ixy4*dB4-Iyy4*atom3148)*dB4-( atom3260+atom3271)*atom3149)-atom169*( atom205*atom181+atom187*atom206)+( atom3148*( atom3259+atom3260)+atom3248*Ixx4-( Iyy4*atom3149-dB4*Iyz4)*dB4-( Iyz4*atom3149-Izz4*dB4)*atom3149+atom3249*Ixz4)*atom168-( atom178*atom205+atom206*atom184)*atom168;
_MQ[586] = -atom209*( atom227*atom246+atom221*atom245)+atom209*( atom3407*Ixz5+atom3408*Izz5-( Ixx5*dB5-atom3307*Ixy5)*atom3307+( Iyy5*atom3307-Ixy5*dB5)*dB5-( atom3430+atom3419)*atom3308)-( atom218*atom245+atom224*atom246)*atom208+atom208*( atom3407*Ixx5+( atom3419+atom3418)*atom3307+atom3408*Ixz5+atom3308*( Izz5*dB5-Iyz5*atom3308)-( Iyy5*atom3308-Iyz5*dB5)*dB5);
_MQ[587] = -( atom285*atom258+atom264*atom286)*atom248+( dB6*( Iyy6*atom3466-dB6*Ixy6)+Ixz6*atom3566-atom3466*( Ixx6*dB6-atom3466*Ixy6)+atom3567*Izz6-atom3467*( atom3578+atom3589))*atom249-( atom285*atom261+atom267*atom286)*atom249+( Ixz6*atom3567-atom3467*( atom3467*Iyz6-dB6*Izz6)+( Iyz6*dB6-atom3467*Iyy6)*dB6+atom3466*( atom3578+atom3577)+Ixx6*atom3566)*atom248;
_MQ[588] =  atom2697*( atom2698*Ixx1-Ixz1*atom2697)+atom2785*Iyz1+atom2784*Ixy1-atom101*atom81+atom2698*( atom2698*Ixz1-Izz1*atom2697)+dB1*( atom2807-atom2795);
_MQ[589] = -( Izz2*atom2843-Ixz2*atom2844)*atom2844-( Ixz2*atom2843-Ixx2*atom2844)*atom2843+dB2*( atom2953-atom2941)+atom2930*Ixy2+atom2931*Iyz2-atom105*atom125;
_MQ[590] = -atom2990*( Izz3*atom2989-atom2990*Ixz3)-atom166*atom134+( atom3112-atom3100)*dB3+atom2989*( atom2990*Ixx3-Ixz3*atom2989)-atom165*atom132+Ixy3*atom3089+atom3090*Iyz3;
_MQ[591] = -( atom3148*Izz4-Ixz4*atom3149)*atom3149+( Ixx4*atom3149-Ixz4*atom3148)*atom3148+atom3248*Ixy4-atom172*atom205+atom3249*Iyz4-dB4*( atom3259-atom3271)-atom206*atom174;
_MQ[592] = -atom212*atom245+atom3407*Ixy5-atom3307*( Ixz5*atom3307-atom3308*Ixx5)-atom246*atom214+( atom3430-atom3418)*dB5-atom3308*( Izz5*atom3307-atom3308*Ixz5)+Iyz5*atom3408;
_MQ[593] = -atom285*atom252+Ixy6*atom3566-atom254*atom286+dB6*( atom3589-atom3577)+atom3466*( atom3467*Ixx6-atom3466*Ixz6)+atom3467*( atom3467*Ixz6-atom3466*Izz6)+Iyz6*atom3567;
_MQ[594] =  ( atom2698*atom2738-dB1*atom2741)*mx1-( atom2698*atom2735-atom2697*atom2741)*my1+dB1*da1*atom82*atom89+mz1*( dB1*atom2735-atom2697*atom2738)+g*m1;
_MQ[595] =  ( dB2*atom2881-atom2884*atom2843)*mz2+my2*( atom2887*atom2843-atom2881*atom2844)+mx2*( atom2884*atom2844-dB2*atom2887)+g*m2+dB2*da2*atom113*atom106;
_MQ[596] =  da3*( atom159*atom133*dB3-atom135*atom154*dB3)+mx3*( atom2990*atom3043-atom3046*dB3)+( atom3040*dB3-atom3043*atom2989)*mz3+( atom3046*atom2989-atom2990*atom3040)*my3+m3*g;
_MQ[597] = -mx4*( atom3205*dB4-atom3202*atom3149)+mz4*( atom3199*dB4-atom3202*atom3148)-( atom3199*atom3149-atom3205*atom3148)*my4+m4*g+da4*( atom199*atom173*dB4-atom175*atom194*dB4);
_MQ[598] =  ( atom3361*atom3308-dB5*atom3364)*mx5+m5*g-mz5*( atom3361*atom3307-atom3358*dB5)+da5*( atom213*atom239*dB5-atom215*atom234*dB5)-( atom3358*atom3308-atom3307*atom3364)*my5;
_MQ[599] =  da6*( atom279*atom253*dB6-atom274*atom255*dB6)-( atom3467*atom3517-atom3466*atom3523)*my6-( atom3520*atom3466-atom3517*dB6)*mz6-( dB6*atom3523-atom3467*atom3520)*mx6+m6*g;

return _MQ;
}

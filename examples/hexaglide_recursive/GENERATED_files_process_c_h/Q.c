/*----------Q.c lib3D_MEC exported-----------*/

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

#include "Q.h"

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
double atom2466;
double atom37;
double atom2470;
double atom40;
double atom2467;
double atom47;
double atom2474;
double atom2558;
double atom2473;
double atom48;
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
double atom2567;
double atom2564;
double atom2570;
double atom65;
double atom2579;
double atom2576;
double atom2573;
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
double atom2697;
double atom80;
double atom2796;
double atom2807;
double atom2698;
double atom2785;
double atom2784;
double atom2795;
double atom82;
double atom83;
double atom81;
double atom84;
double atom100;
double atom89;
double atom101;
double atom103;
double atom104;
double atom113;
double atom106;
double atom125;
double atom107;
double atom105;
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
double atom2989;
double atom128;
double atom3112;
double atom3101;
double atom2990;
double atom3090;
double atom3089;
double atom3100;
double atom131;
double atom130;
double atom133;
double atom135;
double atom144;
double atom129;
double atom134;
double atom147;
double atom159;
double atom141;
double atom165;
double atom138;
double atom132;
double atom154;
double atom166;
double atom169;
double atom171;
double atom175;
double atom168;
double atom173;
double atom181;
double atom170;
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
double atom209;
double atom211;
double atom213;
double atom208;
double atom215;
double atom224;
double atom210;
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
double atom3467;
double atom3566;
double atom248;
double atom3466;
double atom3567;
double atom3578;
double atom3577;
double atom3589;
double atom251;
double atom255;
double atom267;
double atom250;
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
double atom86;
double atom2735;
double atom85;
double atom2738;
double atom2741;
double atom110;
double atom2881;
double atom109;
double atom2884;
double atom2887;
double atom149;
double atom148;
double atom3043;
double atom3046;
double atom3040;
double atom189;
double atom188;
double atom3202;
double atom3205;
double atom3199;
double atom229;
double atom3358;
double atom228;
double atom3361;
double atom3364;
double atom268;
double atom3523;
double atom269;
double atom3517;
double atom3520;

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

atom38 = sin(c);
atom39 = cos(b);
atom2466 = atom39*da;
atom37 = cos(c);
atom2470 =  atom38*dB+atom2466*atom37;
atom40 = sin(b);
atom2467 = da*atom40;
atom47 = atom39*atom37;
atom2474 =  dc+atom2467;
atom2558 =  atom2470*atom40-atom47*atom2474;
atom2473 =  dB*atom37-atom2466*atom38;
atom48 = -atom38*atom39;
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
atom2567 = -atom2474*atom51+atom44*atom2470;
atom2564 =  atom2474*atom54-atom44*atom2473;
atom2570 = -atom54*atom2470+atom2473*atom51;
atom65 =  mzP*atom40+atom47*mxP+myP*atom48;
atom2579 =  atom57*atom2473-atom60*atom2470;
atom2576 =  atom46*atom2470-atom57*atom2474;
atom2573 = -atom46*atom2473+atom60*atom2474;
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
atom2697 = da1*atom79;
atom80 = sin(b1);
atom2796 = Ixz1*dB1;
atom2807 = -atom2697*Iyz1;
atom2698 = atom80*da1;
atom2785 = dB1*atom2697;
atom2784 = -atom2698*dB1;
atom2795 = -atom2698*Ixy1;
atom82 = sin(a1);
atom83 = atom80*atom82;
atom81 = cos(a1);
atom84 = -atom82*atom79;
atom100 = -g*( atom84*mz1+atom81*my1+mx1*atom83);
atom89 =  mx1*atom79+atom80*mz1;
atom101 = g*atom89;
atom103 = cos(b2);
atom104 = sin(b2);
atom113 =  atom104*mz2+mx2*atom103;
atom106 = sin(a2);
atom125 = g*atom113;
atom107 = atom104*atom106;
atom105 = cos(a2);
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
atom2989 = atom127*da3;
atom128 = sin(b3);
atom3112 = -atom2989*Iyz3;
atom3101 = Ixz3*dB3;
atom2990 = atom128*da3;
atom3090 = atom2989*dB3;
atom3089 = -atom2990*dB3;
atom3100 = -atom2990*Ixy3;
atom131 = (1.0/2.0)*pow(3.0,(1.0/2.0));
atom130 = sin(a3);
atom133 = atom131*atom130;
atom135 = (1.0/2.0)*atom130;
atom144 =  atom131*atom127-atom135*atom128;
atom129 = cos(a3);
atom134 = -(1.0/2.0)*atom129;
atom147 =  atom127*atom135+atom131*atom128;
atom159 =  my3*atom134+atom144*mx3+atom147*mz3;
atom141 = -atom128/2.0+atom127*atom133;
atom165 = -atom159*g;
atom138 = -atom127/2.0-atom128*atom133;
atom132 = -atom131*atom129;
atom154 =  atom138*mx3+atom132*my3+atom141*mz3;
atom166 = g*atom154;
atom169 = sin(b4);
atom171 = sin(a4);
atom175 = (1.0/2.0)*atom171;
atom168 = cos(b4);
atom173 = atom131*atom171;
atom181 = -atom169/2.0+atom173*atom168;
atom170 = cos(a4);
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
atom209 = sin(b5);
atom211 = sin(a5);
atom213 = -atom131*atom211;
atom208 = cos(b5);
atom215 = (1.0/2.0)*atom211;
atom224 = -atom209*atom215-atom131*atom208;
atom210 = cos(a5);
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
atom3467 = da6*atom249;
atom3566 = -atom3467*dB6;
atom248 = cos(b6);
atom3466 = da6*atom248;
atom3567 = atom3466*dB6;
atom3578 = Ixz6*dB6;
atom3577 = -atom3467*Ixy6;
atom3589 = -Iyz6*atom3466;
atom251 = sin(a6);
atom255 = (1.0/2.0)*atom251;
atom267 =  atom248*atom255-atom131*atom249;
atom250 = cos(a6);
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
atom86 = atom81*atom79;
atom2735 =  atom2698*atom82-dB1*atom86;
atom85 = -atom80*atom81;
atom2738 = -atom2698*atom85+atom2697*atom86;
atom2741 =  atom85*dB1-atom2697*atom82;
atom110 = atom105*atom103;
atom2881 =  atom2844*atom106-dB2*atom110;
atom109 = -atom104*atom105;
atom2884 = -atom109*atom2844+atom110*atom2843;
atom2887 =  atom109*dB2-atom106*atom2843;
atom149 = atom127*atom129;
atom148 = -atom128*atom129;
atom3043 = -atom2990*atom148+atom2989*atom149;
atom3046 =  atom148*dB3-atom2989*atom130;
atom3040 =  atom2990*atom130-atom149*dB3;
atom189 = atom170*atom168;
atom188 = -atom169*atom170;
atom3202 =  atom3148*atom189-atom188*atom3149;
atom3205 =  atom188*dB4-atom3148*atom171;
atom3199 =  atom171*atom3149-atom189*dB4;
atom229 = atom210*atom208;
atom3358 = -dB5*atom229+atom211*atom3308;
atom228 = -atom209*atom210;
atom3361 = -atom3308*atom228+atom3307*atom229;
atom3364 =  dB5*atom228-atom211*atom3307;
atom268 = -atom250*atom249;
atom3523 =  atom268*dB6-atom3466*atom251;
atom269 = atom250*atom248;
atom3517 = -dB6*atom269+atom3467*atom251;
atom3520 = -atom268*atom3467+atom3466*atom269;

_Q[0] = -dB*( atom2529*atom70-atom2528*atom75)+mzP*( atom2555*atom2473-atom2558*atom2470)-( atom70*atom1532+atom1535*atom75)*da+mxP*( atom2474*atom2558-atom2473*atom2561)+myP*( atom2561*atom2470-atom2474*atom2555);
_Q[1] =  dB*( atom2529*atom65-atom289*atom75)-( atom2470*atom2567-atom2564*atom2473)*mzP-mxP*( atom2473*atom2570-atom2474*atom2567)-( atom2474*atom2564-atom2470*atom2570)*myP+da*atom1532*atom65;
_Q[2] =  myP*( atom2579*atom2470-atom2474*atom2573)+( atom70*atom289-atom2528*atom65)*dB-mxP*( atom2579*atom2473-atom2474*atom2576)+atom1535*da*atom65+g*mP-( atom2576*atom2470-atom2573*atom2473)*mzP;
_Q[3] = -atom47*atom3642-atom40*atom1539+atom47*atom2683+atom40*atom2685+atom2684*atom48-atom48*atom3645;
_Q[4] =  atom2684*atom37-atom37*atom3645+atom38*atom2683-atom38*atom3642;
_Q[5] =  atom2685-atom1539;
_Q[6] = -( atom101*atom83+atom100*atom79)*atom79+atom80*( dB1*( atom2697*Iyy1-dB1*Ixy1)+Ixz1*atom2784+( Ixy1*atom2697-dB1*Ixx1)*atom2697-atom2698*( atom2796+atom2807)+atom2785*Izz1)-atom80*( atom80*atom100+atom84*atom101)-( atom2698*( atom2698*Iyz1-dB1*Izz1)-atom2785*Ixz1-Ixx1*atom2784-( atom2796+atom2795)*atom2697+dB1*( atom2698*Iyy1-dB1*Iyz1))*atom79;
_Q[7] =  atom104*( Ixz2*atom2930-( atom2953+atom2942)*atom2844-( dB2*Ixx2-Ixy2*atom2843)*atom2843+atom2931*Izz2-dB2*( dB2*Ixy2-Iyy2*atom2843))+( Ixx2*atom2930+( dB2*Izz2-atom2844*Iyz2)*atom2844+Ixz2*atom2931+( atom2942+atom2941)*atom2843+dB2*( dB2*Iyz2-atom2844*Iyy2))*atom103-( atom125*atom107+atom124*atom103)*atom103-atom104*( atom108*atom125+atom104*atom124);
_Q[8] = -atom127*( atom138*atom165+atom144*atom166)+atom128*( atom3090*Izz3+Ixz3*atom3089+atom2989*( Ixy3*atom2989-Ixx3*dB3)-( atom3112+atom3101)*atom2990+( atom2989*Iyy3-Ixy3*dB3)*dB3)+atom127*( atom3090*Ixz3+Ixx3*atom3089-( atom2990*Iyy3-Iyz3*dB3)*dB3+atom2989*( atom3101+atom3100)-atom2990*( atom2990*Iyz3-Izz3*dB3))-atom128*( atom147*atom166+atom141*atom165);
_Q[9] =  atom169*( atom3249*Izz4+atom3248*Ixz4-atom3148*( Ixx4*dB4-atom3148*Ixy4)-( Ixy4*dB4-Iyy4*atom3148)*dB4-( atom3260+atom3271)*atom3149)-atom169*( atom205*atom181+atom187*atom206)+( atom3148*( atom3259+atom3260)+atom3248*Ixx4-( Iyy4*atom3149-dB4*Iyz4)*dB4-( Iyz4*atom3149-Izz4*dB4)*atom3149+atom3249*Ixz4)*atom168-( atom178*atom205+atom206*atom184)*atom168;
_Q[10] = -atom209*( atom227*atom246+atom221*atom245)+atom209*( atom3407*Ixz5+atom3408*Izz5-( Ixx5*dB5-atom3307*Ixy5)*atom3307+( Iyy5*atom3307-Ixy5*dB5)*dB5-( atom3430+atom3419)*atom3308)-( atom218*atom245+atom224*atom246)*atom208+atom208*( atom3407*Ixx5+( atom3419+atom3418)*atom3307+atom3408*Ixz5+atom3308*( Izz5*dB5-Iyz5*atom3308)-( Iyy5*atom3308-Iyz5*dB5)*dB5);
_Q[11] = -( atom285*atom258+atom264*atom286)*atom248+( dB6*( Iyy6*atom3466-dB6*Ixy6)+Ixz6*atom3566-atom3466*( Ixx6*dB6-atom3466*Ixy6)+atom3567*Izz6-atom3467*( atom3578+atom3589))*atom249-( atom285*atom261+atom267*atom286)*atom249+( Ixz6*atom3567-atom3467*( atom3467*Iyz6-dB6*Izz6)+( Iyz6*dB6-atom3467*Iyy6)*dB6+atom3466*( atom3578+atom3577)+Ixx6*atom3566)*atom248;
_Q[12] =  atom2697*( atom2698*Ixx1-Ixz1*atom2697)+atom2785*Iyz1+atom2784*Ixy1-atom101*atom81+atom2698*( atom2698*Ixz1-Izz1*atom2697)+dB1*( atom2807-atom2795);
_Q[13] = -( Izz2*atom2843-Ixz2*atom2844)*atom2844-( Ixz2*atom2843-Ixx2*atom2844)*atom2843+dB2*( atom2953-atom2941)+atom2930*Ixy2+atom2931*Iyz2-atom105*atom125;
_Q[14] = -atom2990*( Izz3*atom2989-atom2990*Ixz3)-atom166*atom134+( atom3112-atom3100)*dB3+atom2989*( atom2990*Ixx3-Ixz3*atom2989)-atom165*atom132+Ixy3*atom3089+atom3090*Iyz3;
_Q[15] = -( atom3148*Izz4-Ixz4*atom3149)*atom3149+( Ixx4*atom3149-Ixz4*atom3148)*atom3148+atom3248*Ixy4-atom172*atom205+atom3249*Iyz4-dB4*( atom3259-atom3271)-atom206*atom174;
_Q[16] = -atom212*atom245+atom3407*Ixy5-atom3307*( Ixz5*atom3307-atom3308*Ixx5)-atom246*atom214+( atom3430-atom3418)*dB5-atom3308*( Izz5*atom3307-atom3308*Ixz5)+Iyz5*atom3408;
_Q[17] = -atom285*atom252+Ixy6*atom3566-atom254*atom286+dB6*( atom3589-atom3577)+atom3466*( atom3467*Ixx6-atom3466*Ixz6)+atom3467*( atom3467*Ixz6-atom3466*Izz6)+Iyz6*atom3567;
_Q[18] =  ( atom2698*atom2738-dB1*atom2741)*mx1-( atom2698*atom2735-atom2697*atom2741)*my1+dB1*da1*atom82*atom89+mz1*( dB1*atom2735-atom2697*atom2738)+g*m1;
_Q[19] =  ( dB2*atom2881-atom2884*atom2843)*mz2+my2*( atom2887*atom2843-atom2881*atom2844)+mx2*( atom2884*atom2844-dB2*atom2887)+g*m2+dB2*da2*atom113*atom106;
_Q[20] =  da3*( atom159*atom133*dB3-atom135*atom154*dB3)+mx3*( atom2990*atom3043-atom3046*dB3)+( atom3040*dB3-atom3043*atom2989)*mz3+( atom3046*atom2989-atom2990*atom3040)*my3+m3*g;
_Q[21] = -mx4*( atom3205*dB4-atom3202*atom3149)+mz4*( atom3199*dB4-atom3202*atom3148)-( atom3199*atom3149-atom3205*atom3148)*my4+m4*g+da4*( atom199*atom173*dB4-atom175*atom194*dB4);
_Q[22] =  ( atom3361*atom3308-dB5*atom3364)*mx5+m5*g-mz5*( atom3361*atom3307-atom3358*dB5)+da5*( atom213*atom239*dB5-atom215*atom234*dB5)-( atom3358*atom3308-atom3307*atom3364)*my5;
_Q[23] =  da6*( atom279*atom253*dB6-atom274*atom255*dB6)-( atom3467*atom3517-atom3466*atom3523)*my6-( atom3520*atom3466-atom3517*dB6)*mz6-( dB6*atom3523-atom3467*atom3520)*mx6+m6*g;

return _Q;
}

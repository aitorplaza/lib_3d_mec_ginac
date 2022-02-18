/*----------Knew.c lib3D_MEC exported-----------*/

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

#include "Knew.h"

#define a1 q[ 0 ]
#define a2 q[ 1 ]
#define a3 q[ 2 ]
#define a4 q[ 3 ]
#define a5 q[ 4 ]
#define a6 q[ 5 ]
#define da1 dq[ 0 ]
#define da2 dq[ 1 ]
#define da3 dq[ 2 ]
#define da4 dq[ 3 ]
#define da5 dq[ 4 ]
#define da6 dq[ 5 ]
#define dda1 ddq[ 0 ]
#define dda2 ddq[ 1 ]
#define dda3 ddq[ 2 ]
#define dda4 ddq[ 3 ]
#define dda5 ddq[ 4 ]
#define dda6 ddq[ 5 ]
#define g param[ 0 ]
#define d3 param[ 1 ]
#define r3 param[ 2 ]
#define d4 param[ 3 ]
#define r4 param[ 4 ]
#define m1 param[ 5 ]
#define mx1 param[ 6 ]
#define my1 param[ 7 ]
#define mz1 param[ 8 ]
#define Ixx1 param[ 9 ]
#define Ixy1 param[ 10 ]
#define Ixz1 param[ 11 ]
#define Iyy1 param[ 12 ]
#define Iyz1 param[ 13 ]
#define Izz1 param[ 14 ]
#define m2 param[ 15 ]
#define mx2 param[ 16 ]
#define my2 param[ 17 ]
#define mz2 param[ 18 ]
#define Ixx2 param[ 19 ]
#define Ixy2 param[ 20 ]
#define Ixz2 param[ 21 ]
#define Iyy2 param[ 22 ]
#define Iyz2 param[ 23 ]
#define Izz2 param[ 24 ]
#define m3 param[ 25 ]
#define mx3 param[ 26 ]
#define my3 param[ 27 ]
#define mz3 param[ 28 ]
#define Ixx3 param[ 29 ]
#define Ixy3 param[ 30 ]
#define Ixz3 param[ 31 ]
#define Iyy3 param[ 32 ]
#define Iyz3 param[ 33 ]
#define Izz3 param[ 34 ]
#define m4 param[ 35 ]
#define mx4 param[ 36 ]
#define my4 param[ 37 ]
#define mz4 param[ 38 ]
#define Ixx4 param[ 39 ]
#define Ixy4 param[ 40 ]
#define Ixz4 param[ 41 ]
#define Iyy4 param[ 42 ]
#define Iyz4 param[ 43 ]
#define Izz4 param[ 44 ]
#define m5 param[ 45 ]
#define mx5 param[ 46 ]
#define my5 param[ 47 ]
#define mz5 param[ 48 ]
#define Ixx5 param[ 49 ]
#define Ixy5 param[ 50 ]
#define Ixz5 param[ 51 ]
#define Iyy5 param[ 52 ]
#define Iyz5 param[ 53 ]
#define Izz5 param[ 54 ]
#define m6 param[ 55 ]
#define mx6 param[ 56 ]
#define my6 param[ 57 ]
#define mz6 param[ 58 ]
#define Ixx6 param[ 59 ]
#define Ixy6 param[ 60 ]
#define Ixz6 param[ 61 ]
#define Iyy6 param[ 62 ]
#define Iyz6 param[ 63 ]
#define Izz6 param[ 64 ]
#define Ma1 param[ 65 ]
#define Ma2 param[ 66 ]
#define Ma3 param[ 67 ]
#define Ma4 param[ 68 ]
#define Ma5 param[ 69 ]
#define Ma6 param[ 70 ]
#define FS001 param[ 71 ]
#define FSa11 param[ 72 ]
#define FSb11 param[ 73 ]
#define FSa21 param[ 74 ]
#define FSb21 param[ 75 ]
#define FSa31 param[ 76 ]
#define FSb31 param[ 77 ]
#define FSa41 param[ 78 ]
#define FSb41 param[ 79 ]
#define FS002 param[ 80 ]
#define FSa12 param[ 81 ]
#define FSb12 param[ 82 ]
#define FSa22 param[ 83 ]
#define FSb22 param[ 84 ]
#define FSa32 param[ 85 ]
#define FSb32 param[ 86 ]
#define FSa42 param[ 87 ]
#define FSb42 param[ 88 ]
#define FS003 param[ 89 ]
#define FSa13 param[ 90 ]
#define FSb13 param[ 91 ]
#define FSa23 param[ 92 ]
#define FSb23 param[ 93 ]
#define FSa33 param[ 94 ]
#define FSb33 param[ 95 ]
#define FSa43 param[ 96 ]
#define FSb43 param[ 97 ]
#define FS004 param[ 98 ]
#define FSa14 param[ 99 ]
#define FSb14 param[ 100 ]
#define FSa24 param[ 101 ]
#define FSb24 param[ 102 ]
#define FSa34 param[ 103 ]
#define FSb34 param[ 104 ]
#define FSa44 param[ 105 ]
#define FSb44 param[ 106 ]
#define FS005 param[ 107 ]
#define FSa15 param[ 108 ]
#define FSb15 param[ 109 ]
#define FSa25 param[ 110 ]
#define FSb25 param[ 111 ]
#define FSa35 param[ 112 ]
#define FSb35 param[ 113 ]
#define FSa45 param[ 114 ]
#define FSb45 param[ 115 ]
#define FS006 param[ 116 ]
#define FSa16 param[ 117 ]
#define FSb16 param[ 118 ]
#define FSa26 param[ 119 ]
#define FSb26 param[ 120 ]
#define FSa36 param[ 121 ]
#define FSb36 param[ 122 ]
#define FSa46 param[ 123 ]
#define FSb46 param[ 124 ]
#define g param[ 125 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define lambda3 unknowns[ 2 ]
#define lambda4 unknowns[ 3 ]
#define lambda5 unknowns[ 4 ]
#define lambda6 unknowns[ 5 ]

double atom35;
double atom36;
double atom5436;
double atom5435;
double atom3537;
double atom5416;
double atom5420;
double atom3538;
double atom5417;
double atom5421;
double atom5433;
double atom5425;
double atom5431;
double atom5426;
double atom5422;
double atom8905;
double atom5423;
double atom57;
double atom59;
double atom58;
double atom5548;
double atom3607;
double atom5432;
double atom5549;
double atom3610;
double atom5552;
double atom5555;
double atom8914;
double atom5547;
double atom8920;
double atom888;
double atom5512;
double atom5511;
double atom5524;
double atom5525;
double atom5526;
double atom5508;
double atom5527;
double atom5521;
double atom5535;
double atom8933;
double atom8935;
double atom8937;
double atom8926;
double atom5523;
double atom5528;
double atom5537;
double atom8924;
double atom5531;
double atom5522;
double atom5538;
double atom5533;
double atom5529;
double atom5530;
double atom8951;
double atom5536;
double atom5534;
double atom8966;
double atom8975;
double atom8986;
double atom8988;
double atom8987;
double atom8989;
double atom8990;
double atom8984;
double atom9008;
double atom9025;
double atom9026;
double atom9028;
double atom81;
double atom5702;
double atom5700;
double atom80;
double atom5705;
double atom5708;
double atom9038;
double atom9039;
double atom9040;
double atom9042;
double atom5701;
double atom9048;
double atom9049;
double atom9058;
double atom5663;
double atom5664;
double atom5677;
double atom5676;
double atom5678;
double atom5660;
double atom5673;
double atom5679;
double atom5687;
double atom9080;
double atom9081;
double atom5675;
double atom5680;
double atom5689;
double atom9090;
double atom9067;
double atom9068;
double atom9070;
double atom9072;
double atom9074;
double atom5681;
double atom5682;
double atom5685;
double atom9113;
double atom5683;
double atom5674;
double atom5690;
double atom9100;
double atom9104;
double atom9106;
double atom9102;
double atom9122;
double atom5688;
double atom5686;
double atom9143;
double atom5684;
double atom9152;
double atom9132;
double atom9133;
double atom9136;
double atom9163;
double atom9168;
double atom9160;
double atom9172;
double atom9176;
double atom9187;
double atom9196;
double atom9198;
double atom9210;
double atom9221;
double atom9224;
double atom9222;
double atom9226;
double atom9219;
double atom115;
double atom114;
double atom5819;
double atom5822;
double atom9235;
double atom9237;
double atom9239;
double atom9242;
double atom9240;
double atom9251;
double atom9246;
double atom9248;
double atom9260;
double atom5790;
double atom5789;
double atom5802;
double atom5803;
double atom5804;
double atom5786;
double atom5799;
double atom5805;
double atom5813;
double atom9268;
double atom9270;
double atom5806;
double atom5801;
double atom5815;
double atom9273;
double atom9278;
double atom9283;
double atom9275;
double atom9276;
double atom9293;
double atom9287;
double atom9289;
double atom9302;
double atom5811;
double atom5807;
double atom5808;
double atom9312;
double atom5800;
double atom5809;
double atom5816;
double atom9333;
double atom9329;
double atom9315;
double atom9317;
double atom9323;
double atom9342;
double atom5810;
double atom5812;
double atom5814;
double atom9352;
double atom9355;
double atom9361;
double atom9357;
double atom9371;
double atom9367;
double atom9380;
double atom9390;
double atom9394;
double atom9396;
double atom9397;
double atom9412;
double atom9414;
double atom9416;
double atom9408;
double atom9427;
double atom9431;
double atom9433;
double atom9442;
double atom9447;
double atom9450;
double atom9444;
double atom9461;
double atom9465;
double atom9468;
double atom9477;
double atom9480;
double atom9478;
double atom9482;
double atom9486;
double atom9488;
double atom9490;
double atom153;
double atom152;
double atom5933;
double atom5936;
double atom9507;
double atom9501;
double atom9503;
double atom9509;
double atom9510;
double atom9512;
double atom9521;
double atom9517;
double atom9530;
double atom9552;
double atom9559;
double atom9561;
double atom5903;
double atom5904;
double atom5917;
double atom5916;
double atom5918;
double atom5900;
double atom5913;
double atom5919;
double atom5927;
double atom9540;
double atom9541;
double atom5915;
double atom5920;
double atom5929;
double atom9543;
double atom9546;
double atom9547;
double atom9549;
double atom9565;
double atom9554;
double atom9555;
double atom9575;
double atom9571;
double atom9584;
double atom5925;
double atom5921;
double atom5922;
double atom9595;
double atom5923;
double atom5914;
double atom5930;
double atom9597;
double atom9601;
double atom9627;
double atom9623;
double atom9636;
double atom9612;
double atom9603;
double atom9617;
double atom9607;
double atom9608;
double atom5926;
double atom5928;
double atom9647;
double atom5924;
double atom9649;
double atom9653;
double atom9655;
double atom9671;
double atom9675;
double atom9657;
double atom9658;
double atom9660;
double atom9665;
double atom9684;
double atom9695;
double atom9699;
double atom9701;
double atom9705;
double atom9707;
double atom9692;
double atom9697;
double atom9720;
double atom9716;
double atom9722;
double atom9726;
double atom9730;
double atom9732;
double atom9752;
double atom9743;
double atom9748;
double atom9754;
double atom9745;
double atom9764;
double atom9766;
double atom9772;
double atom9775;
double atom9777;
double atom9768;
double atom9799;
double atom9789;
double atom9795;
double atom9801;
double atom9791;
double atom9812;
double atom9813;
double atom9815;
double atom9827;
double atom9810;
double atom9817;
double atom9823;
double atom9829;
double atom9819;
double atom9852;
double atom9858;
double atom9864;
double atom9870;
double atom9892;
double atom9901;
double atom9910;
double atom9917;
double atom9919;
double atom9939;
double atom9948;
double atom9957;
double atom9966;
double atom9846;
double atom9847;
double atom9848;
double atom9874;
double atom9877;
double atom9880;
double atom9882;
double atom9885;
double atom9888;
double atom9921;
double atom9924;
double atom9926;
double atom9929;
double atom9932;
double atom9935;
double atom9970;
double atom9973;
double atom9976;
double atom9979;
double atom9982;
double atom9985;

double * _Knew = NULL;
void Init_Knew ( ) 
{
    _Knew = malloc ( Knew_n_rows * Knew_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Knew_n_rows * Knew_n_cols ; i++ ) {_Knew[i]=0.0;}
  }
}

void Done_Knew ( ) 
{
if (_Knew != NULL) 
free (_Knew ); 
_Knew = NULL; 
}


double * Knew ()
{
if ( _Knew == NULL )
 {
    _Knew = malloc ( Knew_n_rows * Knew_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Knew_n_rows * Knew_n_cols ; i++ ) {_Knew[i]=0.0;}
  }
 }

atom35 = cos(a2);
atom36 = sin(a2);
atom5436 = atom35*g;
atom5435 = atom36*g;
atom3537 = -atom35*da1;
atom5416 = da2*atom3537;
atom5420 = -atom36*dda1+atom5416;
atom3538 = atom36*da1;
atom5417 = da2*atom3538;
atom5421 = -atom35*dda1+atom5417;
atom5433 = -atom5421-atom5417;
atom5425 = -atom3538*atom3537;
atom5431 =  atom5425+dda2;
atom5426 = (atom3538*atom3538);
atom5422 = (da2*da2);
atom8905 =  da2+atom3537;
atom5423 = (atom3537*atom3537);
atom57 =  a3+a2;
atom59 = sin(atom57);
atom58 = cos(atom57);
atom5548 =  r3*( atom5421-atom5417)-d3*( atom5423+atom5422)+atom5435;
atom3607 =  atom59*atom36+atom58*atom35;
atom5432 =  atom5416-atom5420;
atom5549 =  atom5431*d3+atom5436+r3*atom5432;
atom3610 =  atom58*atom36-atom35*atom59;
atom5552 =  atom5548*atom3607-atom5549*atom3610;
atom5555 =  atom5548*atom3610+atom3607*atom5549;
atom8914 =  atom5552*atom3607+atom3610*atom5555;
atom5547 = -r3*( atom5423+atom5426)+atom5433*d3;
atom8920 = -atom5552*atom3610+atom3607*atom5555;
atom888 = da3;
atom5512 =  atom888+da2;
atom5511 =  atom3607*atom3537-atom3538*atom3610;
atom5524 = (atom5512*atom5512);
atom5525 = (atom5511*atom5511);
atom5526 = -atom5524-atom5525;
atom5508 = -atom3537*atom3610-atom3538*atom3607;
atom5527 = atom5511*atom5508;
atom5521 =  dda3+dda2;
atom5535 =  atom5527+atom5521;
atom8933 = atom3607*atom5535;
atom8935 = -atom5526*atom3610+atom8933;
atom8937 = -atom5547*atom3610;
atom8926 = atom5535*atom3610;
atom5523 = -atom888*atom5508+atom5421*atom3607+atom3610*atom5420;
atom5528 = atom5512*atom5508;
atom5537 = -atom5523+atom5528;
atom8924 = -atom5547*atom3607;
atom5531 = atom5512*atom5511;
atom5522 =  atom3607*atom5420-atom5421*atom3610+atom888*atom5511;
atom5538 =  atom5531+atom5522;
atom5533 =  atom5527-atom5521;
atom5529 = (atom5508*atom5508);
atom5530 = -atom5529-atom5524;
atom8951 =  atom3607*atom5530-atom3610*atom5533;
atom5536 =  atom5531-atom5522;
atom5534 =  atom5523+atom5528;
atom8966 = -atom5534*atom3610+atom5536*atom3607;
atom8975 =  atom5511*da2+atom5511*da3+( atom35*atom3610-atom36*atom3607)*dda1;
atom8986 = -da3*atom5508;
atom8988 = -atom5508*da2;
atom8987 = -dda1*( atom36*atom3610+atom35*atom3607);
atom8989 =  atom8986+atom8988+atom8987;
atom8990 =  atom8989-atom5528;
atom8984 =  atom8975+atom5531;
atom9008 = -atom5529+atom5524;
atom9025 =  atom5512+atom5511;
atom9026 = -atom5508*atom9025;
atom9028 = atom5511*atom9025;
atom81 = sin(a4);
atom5702 =  atom5547-atom5538*r4+d4*atom5537;
atom5700 =  atom5552+atom5526*d4-r4*atom5533;
atom80 = cos(a4);
atom5705 =  atom81*atom5702+atom5700*atom80;
atom5708 =  atom5702*atom80-atom81*atom5700;
atom9038 = atom5708*atom80;
atom9039 =  atom5705*atom81+atom9038;
atom9040 = -atom9039*d4;
atom9042 = -atom9039*r4;
atom5701 = -atom5530*r4+d4*atom5535+atom5555;
atom9048 = -atom81*atom5708;
atom9049 =  atom5705*atom80+atom9048;
atom9058 = -atom9049*atom3610+atom3607*atom5701;
atom5663 =  atom5512*atom80-atom81*atom5508;
atom5664 =  da4-atom5511;
atom5677 = (atom5663*atom5663);
atom5676 = (atom5664*atom5664);
atom5678 = -atom5677-atom5676;
atom5660 =  atom5508*atom80+atom81*atom5512;
atom5673 = -atom5523+dda4;
atom5679 = atom5660*atom5663;
atom5687 =  atom5673+atom5679;
atom9080 = -atom81*atom5687;
atom9081 =  atom5678*atom80+atom9080;
atom5675 = -atom81*atom5522-atom5660*da4+atom5521*atom80;
atom5680 = atom5660*atom5664;
atom5689 = -atom5675+atom5680;
atom9090 = -atom3610*atom9081-atom3607*atom5689;
atom9067 = atom80*atom5687;
atom9068 =  atom9067+atom81*atom5678;
atom9070 = -atom9068*d4-atom5708;
atom9072 = -atom81*atom5701;
atom9074 = -atom9068*r4+atom9072;
atom5681 = (atom5660*atom5660);
atom5682 = -atom5676-atom5681;
atom5685 = -atom5673+atom5679;
atom9113 = -atom81*atom5682+atom5685*atom80;
atom5683 = atom5664*atom5663;
atom5674 =  da4*atom5663+atom80*atom5522+atom81*atom5521;
atom5690 =  atom5683+atom5674;
atom9100 =  atom5682*atom80+atom81*atom5685;
atom9104 = -atom80*atom5701;
atom9106 =  atom9104-atom9100*r4;
atom9102 =  atom5705-d4*atom9100;
atom9122 = -atom5690*atom3607-atom3610*atom9113;
atom5688 =  atom5683-atom5674;
atom5686 =  atom5675+atom5680;
atom9143 =  atom5686*atom80-atom81*atom5688;
atom5684 = -atom5677-atom5681;
atom9152 = -atom5684*atom3607-atom3610*atom9143;
atom9132 =  atom81*atom5686+atom5688*atom80;
atom9133 = -d4*atom9132;
atom9136 = -atom9039-atom9132*r4;
atom9163 =  atom5674*atom80-atom81*atom5680;
atom9168 = atom5679*atom3610;
atom9160 = atom3607*atom5679;
atom9172 = -atom5677+atom5681;
atom9176 = -atom80*atom5689-atom5690*atom81;
atom9187 = -atom5683*atom80-atom5675*atom81;
atom9196 =  atom5676-atom5681;
atom9198 = -atom81*atom9196+atom9067;
atom9210 = -atom81*atom5673-atom5676*atom80;
atom9221 =  atom5664+atom5663;
atom9224 = -atom5660*atom9221;
atom9222 = atom9221*atom5663;
atom9226 =  atom9222*atom80-atom81*atom9224;
atom9219 =  atom5675+atom5673;
atom115 = sin(a5);
atom114 = cos(a5);
atom5819 =  atom115*atom5701+atom5705*atom114;
atom5822 = -atom5705*atom115+atom114*atom5701;
atom9235 = -atom5822*atom115;
atom9237 =  atom9235+atom5819*atom114;
atom9239 =  atom81*atom9237+atom9038;
atom9242 = -atom9239*r4;
atom9240 = -d4*atom9239;
atom9251 =  atom9237*atom80+atom9048;
atom9246 = -atom114*atom5822;
atom9248 = -atom5819*atom115+atom9246;
atom9260 = -atom9248*atom3607-atom9251*atom3610;
atom5790 =  da5+atom5663;
atom5789 = -atom114*atom5664-atom5660*atom115;
atom5802 = (atom5790*atom5790);
atom5803 = (atom5789*atom5789);
atom5804 = -atom5802-atom5803;
atom5786 = -atom115*atom5664+atom114*atom5660;
atom5799 =  atom5675+dda5;
atom5805 = atom5789*atom5786;
atom5813 =  atom5799+atom5805;
atom9268 = -atom115*atom5813;
atom9270 =  atom114*atom5804+atom9268;
atom5806 = atom5786*atom5790;
atom5801 = -da5*atom5786-atom114*atom5673-atom115*atom5674;
atom5815 =  atom5806-atom5801;
atom9273 =  atom81*atom9270+atom5815*atom80;
atom9278 = atom115*atom5708;
atom9283 =  atom80*atom9278-r4*atom9273-atom81*atom5822;
atom9275 = atom114*atom5708;
atom9276 = -atom9275-d4*atom9273;
atom9293 =  atom9270*atom80-atom81*atom5815;
atom9287 = -atom114*atom5813;
atom9289 = -atom115*atom5804+atom9287;
atom9302 = -atom9289*atom3607-atom9293*atom3610;
atom5811 = -atom5799+atom5805;
atom5807 = (atom5786*atom5786);
atom5808 = -atom5807-atom5802;
atom9312 =  atom114*atom5811-atom115*atom5808;
atom5800 = -atom115*atom5673+atom5789*da5+atom114*atom5674;
atom5809 = atom5789*atom5790;
atom5816 =  atom5800+atom5809;
atom9333 =  atom9312*atom80-atom81*atom5816;
atom9329 = -atom115*atom5811-atom114*atom5808;
atom9315 =  atom81*atom9312+atom5816*atom80;
atom9317 = -d4*atom9315+atom9278;
atom9323 = -atom9315*r4+atom5819*atom81+atom9275*atom80;
atom9342 = -atom9329*atom3607-atom9333*atom3610;
atom5810 = -atom5807-atom5803;
atom5812 =  atom5806+atom5801;
atom5814 = -atom5800+atom5809;
atom9352 = -atom5814*atom115+atom114*atom5812;
atom9355 =  atom81*atom9352+atom80*atom5810;
atom9361 = -atom9355*r4+atom9248*atom80;
atom9357 = -d4*atom9355+atom9237;
atom9371 =  atom9352*atom80-atom81*atom5810;
atom9367 = -atom5812*atom115-atom114*atom5814;
atom9380 = -atom3607*atom9367-atom3610*atom9371;
atom9390 = -atom5800*atom115-atom114*atom5806;
atom9394 =  atom114*atom5800-atom115*atom5806;
atom9396 = atom81*atom5805;
atom9397 =  atom9394*atom80+atom9396;
atom9412 = -atom115*atom5816-atom114*atom5815;
atom9414 =  atom5807-atom5803;
atom9416 =  atom80*atom9412-atom81*atom9414;
atom9408 = -atom114*atom5816+atom5815*atom115;
atom9427 =  atom115*atom5809-atom114*atom5801;
atom9431 = -atom114*atom5809-atom115*atom5801;
atom9433 =  atom9431*atom80-atom9396;
atom9442 = -atom5807+atom5802;
atom9447 = -atom9287-atom9442*atom115;
atom9450 =  atom9447*atom80+atom81*atom5814;
atom9444 =  atom9268-atom114*atom9442;
atom9461 =  atom5802*atom115-atom114*atom5799;
atom9465 = -atom114*atom5802-atom115*atom5799;
atom9468 =  atom9465*atom80-atom81*atom5806;
atom9477 =  atom5789+atom5790;
atom9480 = atom5789*atom9477;
atom9478 = -atom9477*atom5786;
atom9482 = -atom115*atom9480-atom114*atom9478;
atom9486 =  atom114*atom9480-atom115*atom9478;
atom9488 =  atom5799+atom5801;
atom9490 = -atom81*atom9488+atom9486*atom80;
atom153 = sin(a6);
atom152 = cos(a6);
atom5933 =  atom153*atom5708+atom5819*atom152;
atom5936 =  atom152*atom5708-atom5819*atom153;
atom9507 =  atom152*atom5936+atom153*atom5933;
atom9501 = -atom5936*atom153+atom152*atom5933;
atom9503 =  atom9235+atom114*atom9501;
atom9509 =  atom80*atom9507+atom81*atom9503;
atom9510 = -d4*atom9509;
atom9512 = -r4*atom9509;
atom9521 =  atom80*atom9503-atom81*atom9507;
atom9517 = -atom115*atom9501+atom9246;
atom9530 = -atom9517*atom3607-atom9521*atom3610;
atom9552 = -atom5822*atom153;
atom9559 =  atom114*atom9552+atom115*atom5936;
atom9561 = atom5822*atom152;
atom5903 =  atom152*atom5790-atom5786*atom153;
atom5904 = -atom5789+da6;
atom5917 = (atom5903*atom5903);
atom5916 = (atom5904*atom5904);
atom5918 = -atom5917-atom5916;
atom5900 =  atom152*atom5786+atom5790*atom153;
atom5913 =  dda6-atom5801;
atom5919 = atom5900*atom5903;
atom5927 =  atom5913+atom5919;
atom9540 = -atom5927*atom153;
atom9541 =  atom152*atom5918+atom9540;
atom5915 =  atom152*atom5799-atom5800*atom153-atom5900*da6;
atom5920 = atom5900*atom5904;
atom5929 = -atom5915+atom5920;
atom9543 =  atom115*atom5929+atom114*atom9541;
atom9546 = atom5927*atom152;
atom9547 =  atom153*atom5918+atom9546;
atom9549 =  atom81*atom9543+atom9547*atom80;
atom9565 = -atom81*atom9561+atom9559*atom80-r4*atom9549;
atom9554 = -atom115*atom9552+atom114*atom5936;
atom9555 = -atom9554-d4*atom9549;
atom9575 =  atom9543*atom80-atom81*atom9547;
atom9571 =  atom114*atom5929-atom115*atom9541;
atom9584 = -atom9571*atom3607-atom9575*atom3610;
atom5925 = -atom5913+atom5919;
atom5921 = (atom5900*atom5900);
atom5922 = -atom5921-atom5916;
atom9595 =  atom152*atom5925-atom5922*atom153;
atom5923 = atom5904*atom5903;
atom5914 =  atom5799*atom153+atom5800*atom152+da6*atom5903;
atom5930 =  atom5923+atom5914;
atom9597 =  atom114*atom9595+atom5930*atom115;
atom9601 =  atom152*atom5922+atom5925*atom153;
atom9627 =  atom9597*atom80-atom81*atom9601;
atom9623 = -atom115*atom9595+atom114*atom5930;
atom9636 = -atom9623*atom3607-atom3610*atom9627;
atom9612 = -atom115*atom5933-atom114*atom9561;
atom9603 =  atom81*atom9597+atom80*atom9601;
atom9617 =  atom9612*atom80-atom81*atom9552-r4*atom9603;
atom9607 = -atom114*atom5933+atom115*atom9561;
atom9608 = -atom9607-d4*atom9603;
atom5926 =  atom5915+atom5920;
atom5928 =  atom5923-atom5914;
atom9647 =  atom152*atom5926-atom153*atom5928;
atom5924 = -atom5921-atom5917;
atom9649 =  atom115*atom5924+atom114*atom9647;
atom9653 =  atom5926*atom153+atom152*atom5928;
atom9655 =  atom80*atom9653+atom81*atom9649;
atom9671 =  atom114*atom5924-atom115*atom9647;
atom9675 =  atom80*atom9649-atom81*atom9653;
atom9657 = atom115*atom9507;
atom9658 = -atom9657-d4*atom9655;
atom9660 = -atom114*atom9507;
atom9665 = -atom81*atom9501+atom9660*atom80-r4*atom9655;
atom9684 = -atom9675*atom3610-atom9671*atom3607;
atom9695 =  atom152*atom5914-atom5920*atom153;
atom9699 = -atom115*atom5919;
atom9701 =  atom9699+atom114*atom9695;
atom9705 =  atom152*atom5920+atom153*atom5914;
atom9707 =  atom9701*atom80-atom81*atom9705;
atom9692 = -atom114*atom5919;
atom9697 = -atom115*atom9695+atom9692;
atom9720 = -atom152*atom5929-atom5930*atom153;
atom9716 =  atom5921-atom5917;
atom9722 = -atom115*atom9720+atom114*atom9716;
atom9726 =  atom114*atom9720+atom115*atom9716;
atom9730 =  atom5930*atom152-atom153*atom5929;
atom9732 =  atom80*atom9726-atom81*atom9730;
atom9752 =  atom5915*atom152-atom5923*atom153;
atom9743 = -atom5915*atom153-atom5923*atom152;
atom9748 =  atom114*atom9743-atom9699;
atom9754 = -atom81*atom9752+atom9748*atom80;
atom9745 = -atom115*atom9743-atom9692;
atom9764 = -atom5921+atom5916;
atom9766 = -atom153*atom9764+atom9546;
atom9772 = -atom115*atom5928+atom114*atom9766;
atom9775 =  atom152*atom9764-atom9540;
atom9777 =  atom9772*atom80-atom81*atom9775;
atom9768 = -atom114*atom5928-atom115*atom9766;
atom9799 =  atom152*atom5913-atom153*atom5916;
atom9789 = -atom152*atom5916-atom153*atom5913;
atom9795 =  atom114*atom9789+atom115*atom5920;
atom9801 =  atom80*atom9795-atom81*atom9799;
atom9791 =  atom114*atom5920-atom9789*atom115;
atom9812 =  atom5904+atom5903;
atom9813 = atom9812*atom5903;
atom9815 = -atom9812*atom5900;
atom9827 =  atom152*atom9815+atom9813*atom153;
atom9810 =  atom5915+atom5913;
atom9817 =  atom152*atom9813-atom9815*atom153;
atom9823 =  atom9810*atom115+atom114*atom9817;
atom9829 = -atom81*atom9827+atom9823*atom80;
atom9819 =  atom9810*atom114-atom9817*atom115;
atom9852 =  atom9049*r4+d4*atom5701;
atom9858 =  r4*atom9081-atom9104-d4*atom5689;
atom9864 = -atom5690*d4+atom9072+r4*atom9113;
atom9870 =  atom9049+r4*atom9143-d4*atom5684;
atom9892 =  atom9251*r4-atom9248*d4;
atom9901 =  atom81*atom9278+atom9293*r4-atom9289*d4+atom5822*atom80;
atom9910 = -atom5819*atom80+atom9333*r4+atom81*atom9275-atom9329*d4;
atom9917 =  atom81*atom9248+r4*atom9371-d4*atom9367;
atom9919 = -atom80*atom5805;
atom9939 = -atom9517*d4+atom9521*r4;
atom9948 = -d4*atom9571+atom80*atom9561+atom81*atom9559+atom9575*r4;
atom9957 =  atom81*atom9612-atom9623*d4+atom9552*atom80+r4*atom9627;
atom9966 = -d4*atom9671+atom81*atom9660+atom80*atom9501+atom9675*r4;
atom9846 =  atom5529-atom5525;
atom9847 =  atom8975-atom5531;
atom9848 =  atom8986+atom8988+dda3+dda2+atom8987;
atom9874 =  atom81*atom5674+atom5680*atom80;
atom9877 = -atom81*atom5689+atom5690*atom80;
atom9880 =  atom5675*atom80-atom81*atom5683;
atom9882 =  atom9196*atom80-atom9080;
atom9885 =  atom5673*atom80-atom81*atom5676;
atom9888 =  atom81*atom9222+atom9224*atom80;
atom9921 =  atom81*atom9394+atom9919;
atom9924 =  atom9414*atom80+atom81*atom9412;
atom9926 = -atom9919+atom81*atom9431;
atom9929 = -atom5814*atom80+atom81*atom9447;
atom9932 =  atom5806*atom80+atom81*atom9465;
atom9935 =  atom9488*atom80+atom81*atom9486;
atom9970 =  atom81*atom9701+atom9705*atom80;
atom9973 =  atom81*atom9726+atom9730*atom80;
atom9976 =  atom9752*atom80+atom81*atom9748;
atom9979 =  atom81*atom9772+atom9775*atom80;
atom9982 =  atom81*atom9795+atom9799*atom80;
atom9985 =  atom81*atom9823+atom80*atom9827;

_Knew[54] = dda1;
_Knew[67] = atom5436;
_Knew[73] = -atom5435;
_Knew[78] = -atom35*atom5435+atom36*atom5436;
_Knew[84] = -atom36*atom5420+atom35*atom5417;
_Knew[85] = -atom5425;
_Knew[90] = -atom35*( atom5416+atom5420)+atom36*atom5433;
_Knew[91] = -atom5423+atom5426;
_Knew[96] =  atom36*atom5416-atom35*atom5421;
_Knew[97] = atom5425;
_Knew[102] =  atom35*( atom5426-atom5422)-atom5431*atom36;
_Knew[103] = -atom5432;
_Knew[108] =  atom36*atom5422-atom35*dda2;
_Knew[109] = -atom5417;
_Knew[114] = -atom8905*atom36*atom3537-atom8905*atom35*atom3538;
_Knew[115] =  atom5421+dda2;
_Knew[120] =  r3*atom36*atom8920-atom35*( r3*atom8914-atom5547*d3);
_Knew[121] = atom8920*d3;
_Knew[126] = -atom35*( ( atom8926+atom5526*atom3607)*r3+atom8924-atom5537*d3)-( atom8937-r3*atom8935)*atom36;
_Knew[127] =  d3*atom8935+atom5555;
_Knew[128] = atom5555;
_Knew[132] = -atom35*( atom8937+r3*( atom5530*atom3610+atom3607*atom5533)-atom5538*d3)+atom36*( atom8924+atom8951*r3);
_Knew[133] = -atom5552+atom8951*d3;
_Knew[134] = -atom5552;
_Knew[138] =  atom36*( atom8920+r3*atom8966)-atom35*( r3*( atom5534*atom3607+atom5536*atom3610)+( atom5529+atom5525)*d3+atom8914);
_Knew[139] = atom8966*d3;
_Knew[144] = -atom36*( atom5528*atom3610+atom8975*atom3607)-atom35*( atom3607*atom5528-atom8975*atom3610);
_Knew[145] = -atom5527;
_Knew[146] = -atom5527;
_Knew[150] =  atom35*( atom8990*atom3610-atom3607*atom8984)-( atom8990*atom3607+atom3610*atom8984)*atom36;
_Knew[151] = atom9846;
_Knew[152] = atom9846;
_Knew[156] =  atom36*( atom5531*atom3607-atom8989*atom3610)-atom35*( atom5531*atom3610+atom8989*atom3607);
_Knew[157] = atom5527;
_Knew[158] = atom5527;
_Knew[162] = -atom36*( atom9008*atom3610+atom8933)-atom35*( atom9008*atom3607-atom8926);
_Knew[163] = atom9847;
_Knew[164] = atom9847;
_Knew[168] = -( atom5521*atom3610-atom5524*atom3607)*atom36-( atom5521*atom3607+atom5524*atom3610)*atom35;
_Knew[169] = atom5528;
_Knew[170] = atom5528;
_Knew[174] = -atom36*( atom9028*atom3607+atom3610*atom9026)-( atom3607*atom9026-atom9028*atom3610)*atom35;
_Knew[175] = atom9848;
_Knew[176] = atom9848;
_Knew[180] = -atom35*( r3*( atom9049*atom3607+atom3610*atom5701)-atom9042*atom3610+atom3607*atom9040-atom9039*d3)-( atom3610*atom9040+atom9042*atom3607-r3*atom9058)*atom36;
_Knew[181] =  d3*atom9058+atom9852;
_Knew[182] = atom9852;
_Knew[186] = -atom36*( atom9074*atom3607-r3*atom9090+atom9070*atom3610)+atom35*( atom9074*atom3610-r3*( atom3607*atom9081-atom3610*atom5689)+atom9068*d3-atom3607*atom9070);
_Knew[187] =  atom9858+atom9090*d3;
_Knew[188] = atom9858;
_Knew[189] = atom5708;
_Knew[192] =  atom36*( r3*atom9122-atom9106*atom3607-atom9102*atom3610)-atom35*( r3*( atom3607*atom9113-atom5690*atom3610)-atom9100*d3+atom9102*atom3607-atom9106*atom3610);
_Knew[193] =  d3*atom9122+atom9864;
_Knew[194] = atom9864;
_Knew[195] = -atom5705;
_Knew[198] = -atom36*( atom3610*atom9133+atom3607*atom9136-r3*atom9152)-atom35*( r3*( atom3607*atom9143-atom5684*atom3610)-atom3610*atom9136+atom3607*atom9133-atom9132*d3);
_Knew[199] =  atom9152*d3+atom9870;
_Knew[200] = atom9870;
_Knew[204] = -( atom9160-atom3610*atom9163)*atom35-( atom3607*atom9163+atom9168)*atom36;
_Knew[205] = atom9874;
_Knew[206] = atom9874;
_Knew[207] = -atom5679;
_Knew[210] = -atom36*( atom3607*atom9176-atom3610*atom9172)+atom35*( atom3607*atom9172+atom3610*atom9176);
_Knew[211] = atom9877;
_Knew[212] = atom9877;
_Knew[213] = atom9172;
_Knew[216] = -atom36*( atom3607*atom9187-atom9168)+atom35*( atom9160+atom3610*atom9187);
_Knew[217] = atom9880;
_Knew[218] = atom9880;
_Knew[219] = atom5679;
_Knew[222] = -atom36*( atom5688*atom3610+atom3607*atom9198)-( atom5688*atom3607-atom3610*atom9198)*atom35;
_Knew[223] = atom9882;
_Knew[224] = atom9882;
_Knew[225] = -atom5688;
_Knew[228] =  atom35*( atom5680*atom3607+atom9210*atom3610)-( atom9210*atom3607-atom5680*atom3610)*atom36;
_Knew[229] = atom9885;
_Knew[230] = atom9885;
_Knew[231] = atom5680;
_Knew[234] = -( atom3607*atom9226-atom9219*atom3610)*atom36+atom35*( atom9219*atom3607+atom3610*atom9226);
_Knew[235] = atom9888;
_Knew[236] = atom9888;
_Knew[237] = atom9219;
_Knew[240] =  atom35*( atom9242*atom3610-r3*( atom9251*atom3607-atom9248*atom3610)-atom9240*atom3607+atom9239*d3)-atom36*( atom9242*atom3607-r3*atom9260+atom9240*atom3610);
_Knew[241] =  atom9260*d3+atom9892;
_Knew[242] = atom9892;
_Knew[246] = -atom36*( atom9283*atom3607+atom3610*atom9276-r3*atom9302)+atom35*( atom9283*atom3610-atom3607*atom9276+d3*atom9273-r3*( atom9293*atom3607-atom9289*atom3610));
_Knew[247] =  atom9901+atom9302*d3;
_Knew[248] = atom9901;
_Knew[249] = atom9275;
_Knew[250] = atom5822;
_Knew[252] =  atom35*( atom9323*atom3610+r3*( atom9329*atom3610-atom3607*atom9333)+atom9315*d3-atom9317*atom3607)-atom36*( atom9323*atom3607-r3*atom9342+atom9317*atom3610);
_Knew[253] =  atom9342*d3+atom9910;
_Knew[254] = atom9910;
_Knew[255] = -atom9278;
_Knew[256] = -atom5819;
_Knew[258] = -( atom3610*atom9357+atom3607*atom9361-r3*atom9380)*atom36-atom35*( r3*( atom3607*atom9371-atom3610*atom9367)-atom9361*atom3610+atom3607*atom9357-atom9355*d3);
_Knew[259] =  atom9380*d3+atom9917;
_Knew[260] = atom9917;
_Knew[261] = -atom9237;
_Knew[264] = -atom36*( atom9397*atom3607-atom9390*atom3610)+atom35*( atom9397*atom3610+atom9390*atom3607);
_Knew[265] = atom9921;
_Knew[266] = atom9921;
_Knew[267] = atom9390;
_Knew[268] = -atom5805;
_Knew[270] =  atom35*( atom3607*atom9408+atom3610*atom9416)-atom36*( atom3607*atom9416-atom3610*atom9408);
_Knew[271] = atom9924;
_Knew[272] = atom9924;
_Knew[273] = atom9408;
_Knew[274] = atom9414;
_Knew[276] =  atom36*( atom9427*atom3610-atom3607*atom9433)+( atom9427*atom3607+atom9433*atom3610)*atom35;
_Knew[277] = atom9926;
_Knew[278] = atom9926;
_Knew[279] = atom9427;
_Knew[280] = atom5805;
_Knew[282] = -( atom9450*atom3607-atom9444*atom3610)*atom36+atom35*( atom9444*atom3607+atom9450*atom3610);
_Knew[283] = atom9929;
_Knew[284] = atom9929;
_Knew[285] = atom9444;
_Knew[286] = -atom5814;
_Knew[288] =  atom35*( atom3607*atom9461+atom9468*atom3610)-atom36*( atom9468*atom3607-atom3610*atom9461);
_Knew[289] = atom9932;
_Knew[290] = atom9932;
_Knew[291] = atom9461;
_Knew[292] = atom5806;
_Knew[294] =  atom35*( atom3607*atom9482+atom9490*atom3610)-( atom9490*atom3607-atom3610*atom9482)*atom36;
_Knew[295] = atom9935;
_Knew[296] = atom9935;
_Knew[297] = atom9482;
_Knew[298] = atom9488;
_Knew[300] =  atom36*( r3*atom9530-atom3607*atom9512-atom9510*atom3610)+atom35*( r3*( atom9517*atom3610-atom9521*atom3607)+d3*atom9509+atom3610*atom9512-atom9510*atom3607);
_Knew[301] =  atom9530*d3+atom9939;
_Knew[302] = atom9939;
_Knew[306] =  atom35*( atom9549*d3+atom9565*atom3610-r3*( atom9575*atom3607-atom9571*atom3610)-atom3607*atom9555)-( atom9555*atom3610-r3*atom9584+atom3607*atom9565)*atom36;
_Knew[307] =  atom9948+atom9584*d3;
_Knew[308] = atom9948;
_Knew[309] = atom9554;
_Knew[310] = atom9561;
_Knew[311] = atom5936;
_Knew[312] =  atom35*( d3*atom9603-atom9608*atom3607-r3*( atom3607*atom9627-atom9623*atom3610)+atom3610*atom9617)+atom36*( r3*atom9636-atom9608*atom3610-atom3607*atom9617);
_Knew[313] =  atom9957+d3*atom9636;
_Knew[314] = atom9957;
_Knew[315] = atom9607;
_Knew[316] = atom9552;
_Knew[317] = -atom5933;
_Knew[318] =  atom35*( r3*( atom9671*atom3610-atom9675*atom3607)+d3*atom9655+atom9665*atom3610-atom9658*atom3607)+atom36*( r3*atom9684-atom9658*atom3610-atom9665*atom3607);
_Knew[319] =  atom9966+atom9684*d3;
_Knew[320] = atom9966;
_Knew[321] = atom9657;
_Knew[322] = atom9501;
_Knew[324] =  atom35*( atom9707*atom3610+atom9697*atom3607)-( atom3607*atom9707-atom9697*atom3610)*atom36;
_Knew[325] = atom9970;
_Knew[326] = atom9970;
_Knew[327] = atom9697;
_Knew[328] = atom9705;
_Knew[329] = -atom5919;
_Knew[330] =  atom35*( atom9722*atom3607+atom9732*atom3610)-( atom9732*atom3607-atom9722*atom3610)*atom36;
_Knew[331] = atom9973;
_Knew[332] = atom9973;
_Knew[333] = atom9722;
_Knew[334] = atom9730;
_Knew[335] = atom9716;
_Knew[336] = -( atom3607*atom9754-atom9745*atom3610)*atom36+atom35*( atom3607*atom9745+atom3610*atom9754);
_Knew[337] = atom9976;
_Knew[338] = atom9976;
_Knew[339] = atom9745;
_Knew[340] = atom9752;
_Knew[341] = atom5919;
_Knew[342] =  atom35*( atom9777*atom3610+atom9768*atom3607)-( atom3607*atom9777-atom9768*atom3610)*atom36;
_Knew[343] = atom9979;
_Knew[344] = atom9979;
_Knew[345] = atom9768;
_Knew[346] = atom9775;
_Knew[347] = -atom5928;
_Knew[348] =  atom35*( atom9791*atom3607+atom3610*atom9801)-( atom3607*atom9801-atom9791*atom3610)*atom36;
_Knew[349] = atom9982;
_Knew[350] = atom9982;
_Knew[351] = atom9791;
_Knew[352] = atom9799;
_Knew[353] = atom5920;
_Knew[354] =  atom35*( atom3607*atom9819+atom9829*atom3610)-( atom9829*atom3607-atom3610*atom9819)*atom36;
_Knew[355] = atom9985;
_Knew[356] = atom9985;
_Knew[357] = atom9819;
_Knew[358] = atom9827;
_Knew[359] = atom9810;

return _Knew;
}

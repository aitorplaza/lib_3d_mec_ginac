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
double atom48;
double atom37;
double atom47;
double atom3790;
double atom40;
double atom3787;
double atom3784;
double atom3747;
double atom3748;
double atom3749;
double atom3873;
double atom3870;
double atom3876;
double atom288;
double atom42;
double atom41;
double atom46;
double atom45;
double atom60;
double atom57;
double atom417;
double atom75;
double atom44;
double atom43;
double atom51;
double atom54;
double atom70;
double atom418;
double atom289;
double atom292;
double atom295;
double atom3796;
double atom3793;
double atom3799;
double atom65;
double atom3885;
double atom3882;
double atom3879;
double atom3808;
double atom3805;
double atom3802;
double atom3888;
double atom3891;
double atom3894;
double atom3756;
double atom3758;
double atom3843;
double atom3753;
double atom3755;
double atom3751;
double atom3752;
double atom3768;
double atom3779;
double atom3771;
double atom3763;
double atom3781;
double atom76;
double atom77;
double atom2856;
double atom3765;
double atom3762;
double atom3760;
double atom3777;
double atom3774;
double atom3938;
double atom3937;
double atom3992;
double atom80;
double atom79;
double atom835;
double atom838;
double atom840;
double atom82;
double atom81;
double atom85;
double atom86;
double atom975;
double atom986;
double atom4004;
double atom104;
double atom103;
double atom1132;
double atom1134;
double atom1129;
double atom105;
double atom110;
double atom106;
double atom109;
double atom1264;
double atom1266;
double atom4104;
double atom128;
double atom127;
double atom1433;
double atom1435;
double atom1430;
double atom130;
double atom129;
double atom148;
double atom149;
double atom135;
double atom131;
double atom134;
double atom159;
double atom165;
double atom133;
double atom132;
double atom154;
double atom166;
double atom1584;
double atom1586;
double atom4204;
double atom169;
double atom168;
double atom1748;
double atom1753;
double atom1751;
double atom171;
double atom170;
double atom189;
double atom188;
double atom1902;
double atom4318;
double atom1910;
double atom175;
double atom174;
double atom199;
double atom205;
double atom173;
double atom172;
double atom194;
double atom206;
double atom209;
double atom208;
double atom2067;
double atom2069;
double atom2064;
double atom211;
double atom210;
double atom229;
double atom228;
double atom215;
double atom214;
double atom239;
double atom245;
double atom213;
double atom212;
double atom234;
double atom246;
double atom2218;
double atom2220;
double atom4432;
double atom248;
double atom249;
double atom2380;
double atom2385;
double atom2383;
double atom251;
double atom250;
double atom268;
double atom269;
double atom253;
double atom252;
double atom274;
double atom286;
double atom255;
double atom254;
double atom279;
double atom285;
double atom2529;
double atom2540;
double atom4546;
double atom89;
double atom113;
double atom4041;
double atom4141;
double atom1426;
double atom4255;
double atom4369;
double atom1744;
double atom2060;
double atom4483;
double atom4597;
double atom2376;
double atom3829;
double atom3814;
double atom3832;
double atom3820;
double atom3835;
double atom3826;
double atom3841;
double atom839;
double atom4019;
double atom1133;
double atom4119;
double atom1434;
double atom4219;
double atom1752;
double atom4333;
double atom2068;
double atom4447;
double atom2384;
double atom4561;
double atom4013;
double atom4113;
double atom4213;
double atom4327;
double atom4441;
double atom4555;

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
atom48 = -atom38*atom39;
atom37 = cos(c);
atom47 = atom39*atom37;
atom3790 =  mxP*atom48-myP*atom47;
atom40 = sin(b);
atom3787 = -mxP*atom40+mzP*atom47;
atom3784 = -atom48*mzP+myP*atom40;
atom3747 = atom39*da;
atom3748 = da*atom40;
atom3749 =  atom3748+dc;
atom3873 =  atom3747*atom40-atom3749*atom47;
atom3870 =  atom48*atom3749-dB*atom40;
atom3876 = -atom48*atom3747+dB*atom47;
atom288 = dc*atom40;
atom42 = sin(a);
atom41 = cos(a);
atom46 = atom39*atom41;
atom45 = -atom40*atom41;
atom60 = -atom38*atom45+atom42*atom37;
atom57 =  atom45*atom37+atom42*atom38;
atom417 = atom288*atom42;
atom75 =  mxP*atom57+atom46*mzP+myP*atom60;
atom44 = -atom42*atom39;
atom43 = atom42*atom40;
atom51 =  atom38*atom41+atom43*atom37;
atom54 =  atom37*atom41-atom38*atom43;
atom70 =  myP*atom54+mzP*atom44+mxP*atom51;
atom418 = -atom288*atom41;
atom289 = dc*atom39;
atom292 =  dB*atom41-atom42*atom289;
atom295 =  atom289*atom41+atom42*dB;
atom3796 = -mxP*atom44+atom51*mzP;
atom3793 = -atom54*mzP+myP*atom44;
atom3799 = -myP*atom51+mxP*atom54;
atom65 =  mzP*atom40+mxP*atom47+myP*atom48;
atom3885 = -atom54*atom3747+dB*atom51;
atom3882 = -atom51*atom3749+atom3747*atom44;
atom3879 = -dB*atom44+atom54*atom3749;
atom3808 =  mxP*atom60-myP*atom57;
atom3805 = -mxP*atom46+mzP*atom57;
atom3802 = -mzP*atom60+atom46*myP;
atom3888 = -atom46*dB+atom3749*atom60;
atom3891 =  atom46*atom3747-atom3749*atom57;
atom3894 =  dB*atom57-atom3747*atom60;
atom3756 = atom37*IxzP;
atom3758 =  atom3756-atom38*IyzP;
atom3843 =  atom39*atom3758+IzzP*atom40;
atom3753 = IxyP*atom37;
atom3755 =  atom3753-atom38*IyyP;
atom3751 = -atom38*IxyP;
atom3752 =  IxxP*atom37+atom3751;
atom3768 = -atom38*atom3755+atom37*atom3752;
atom3779 = -IzzP*atom38+atom3756;
atom3771 =  atom37*atom3755+atom38*atom3752;
atom3763 = atom38*IxzP;
atom3781 =  IzzP*atom37+atom3763;
atom76 = -atom70*g;
atom77 = g*atom65;
atom2856 =  atom76*atom40+atom77*atom44;
atom3765 =  IyzP*atom37+atom3763;
atom3762 =  IyyP*atom37-atom3751;
atom3760 =  IxxP*atom38+atom3753;
atom3777 =  atom3762*atom37+atom38*atom3760;
atom3774 =  atom3760*atom37-atom38*atom3762;
atom3938 = dB*atom3747;
atom3937 = -atom3748*dB;
atom3992 =  atom3749*( atom3765*atom3747-atom3758*dB)+atom3937*atom3779+IzzP*atom3938-( atom3768*dB-atom3774*atom3747)*atom3747-( atom3771*dB-atom3777*atom3747)*dB;
atom80 = sin(b1);
atom79 = cos(b1);
atom835 = Ixz1*atom80;
atom838 = atom80*Izz1;
atom840 = Ixz1*atom79;
atom82 = sin(a1);
atom81 = cos(a1);
atom85 = -atom80*atom81;
atom86 = atom81*atom79;
atom975 = Izz1*atom79;
atom986 =  atom975-atom80*Ixy1;
atom4004 = -( atom80*Ixx1-atom840)*atom79+atom80*( atom975-atom835);
atom104 = sin(b2);
atom103 = cos(b2);
atom1132 = atom104*Izz2;
atom1134 = Ixz2*atom103;
atom1129 = atom104*Ixz2;
atom105 = cos(a2);
atom110 = atom105*atom103;
atom106 = sin(a2);
atom109 = -atom104*atom105;
atom1264 = Izz2*atom103;
atom1266 =  atom1264-atom104*Ixy2;
atom4104 = -atom104*( atom1129-atom1264)+( atom1134-atom104*Ixx2)*atom103;
atom128 = sin(b3);
atom127 = cos(b3);
atom1433 = atom128*Izz3;
atom1435 = Ixz3*atom127;
atom1430 = atom128*Ixz3;
atom130 = sin(a3);
atom129 = cos(a3);
atom148 = -atom128*atom129;
atom149 = atom129*atom127;
atom135 = (1.0/2.0)*atom130;
atom131 = (1.0/2.0)*pow(3.0,(1.0/2.0));
atom134 = -(1.0/2.0)*atom129;
atom159 =  mz3*( atom128*atom131+atom135*atom127)-( atom135*atom128-atom131*atom127)*mx3+atom134*my3;
atom165 = -atom159*g;
atom133 = atom130*atom131;
atom132 = -atom129*atom131;
atom154 = -mx3*( 2.0*atom128*atom133+atom127)/2.0+mz3*( 2.0*atom133*atom127-atom128)/2.0+atom132*my3;
atom166 = g*atom154;
atom1584 = Izz3*atom127;
atom1586 = -atom128*Ixy3+atom1584;
atom4204 = -atom128*( atom1430-atom1584)+( atom1435-atom128*Ixx3)*atom127;
atom169 = sin(b4);
atom168 = cos(b4);
atom1748 = atom169*Ixz4;
atom1753 = Ixz4*atom168;
atom1751 = atom169*Izz4;
atom171 = sin(a4);
atom170 = cos(a4);
atom189 = atom170*atom168;
atom188 = -atom169*atom170;
atom1902 = atom168*Izz4;
atom4318 =  ( atom1753-atom169*Ixx4)*atom168-atom169*( atom1748-atom1902);
atom1910 = -atom169*Ixy4+atom1902;
atom175 = (1.0/2.0)*atom171;
atom174 = -(1.0/2.0)*atom170;
atom199 =  mz4*( atom175*atom168+atom169*atom131)+( atom168*atom131-atom175*atom169)*mx4+atom174*my4;
atom205 = -g*atom199;
atom173 = atom171*atom131;
atom172 = -atom170*atom131;
atom194 =  atom172*my4-mz4*( atom169+-2.0*atom168*atom173)/2.0-mx4*( 2.0*atom169*atom173+atom168)/2.0;
atom206 = g*atom194;
atom209 = sin(b5);
atom208 = cos(b5);
atom2067 = atom209*Izz5;
atom2069 = Ixz5*atom208;
atom2064 = Ixz5*atom209;
atom211 = sin(a5);
atom210 = cos(a5);
atom229 = atom208*atom210;
atom228 = -atom209*atom210;
atom215 = (1.0/2.0)*atom211;
atom214 = -(1.0/2.0)*atom210;
atom239 =  mz5*( atom215*atom208-atom131*atom209)+my5*atom214-( atom215*atom209+atom208*atom131)*mx5;
atom245 = -atom239*g;
atom213 = -atom211*atom131;
atom212 = atom131*atom210;
atom234 =  my5*atom212-( atom208+2.0*atom209*atom213)*mx5/2.0-mz5*( atom209+-2.0*atom208*atom213)/2.0;
atom246 = g*atom234;
atom2218 = atom208*Izz5;
atom2220 = -Ixy5*atom209+atom2218;
atom4432 = -( atom2064-atom2218)*atom209+atom208*( atom2069-Ixx5*atom209);
atom248 = cos(b6);
atom249 = sin(b6);
atom2380 = Ixz6*atom249;
atom2385 = Ixz6*atom248;
atom2383 = atom249*Izz6;
atom251 = sin(a6);
atom250 = cos(a6);
atom268 = -atom249*atom250;
atom269 = atom248*atom250;
atom253 = -atom251*atom131;
atom252 = atom131*atom250;
atom274 = -( atom248+2.0*atom249*atom253)*mx6/2.0+mz6*( 2.0*atom248*atom253-atom249)/2.0+atom252*my6;
atom286 = g*atom274;
atom255 = (1.0/2.0)*atom251;
atom254 = -(1.0/2.0)*atom250;
atom279 =  atom254*my6-mz6*( atom249*atom131-atom248*atom255)-( atom248*atom131+atom255*atom249)*mx6;
atom285 = -g*atom279;
atom2529 = atom248*Izz6;
atom2540 =  atom2529-atom249*Ixy6;
atom4546 =  atom248*( atom2385-Ixx6*atom249)+atom249*( atom2529-atom2380);
atom89 =  atom80*mz1+mx1*atom79;
atom113 =  mx2*atom103+atom104*mz2;
atom4041 = -da1*atom82+dB1*atom85;
atom4141 = -da2*atom106+dB2*atom109;
atom1426 = dB3*atom130;
atom4255 =  dB3*atom148-da3*atom130;
atom4369 = -da4*atom171+atom188*dB4;
atom1744 = atom171*dB4;
atom2060 = atom211*dB5;
atom4483 =  atom228*dB5-atom211*da5;
atom4597 =  dB6*atom268-atom251*da6;
atom2376 = atom251*dB6;
atom3829 =  atom3790*atom40-( atom38*atom3787-atom3784*atom37)*atom39;
atom3814 =  atom38*atom3784+atom3787*atom37;
atom3832 = -( atom38*atom3796-atom3793*atom37)*atom39+atom3799*atom40;
atom3820 =  atom3796*atom37+atom38*atom3793;
atom3835 = -( atom38*atom3805-atom3802*atom37)*atom39+atom3808*atom40;
atom3826 =  atom38*atom3802+atom3805*atom37;
atom3841 =  atom40*atom3781+atom3771*atom39;
atom839 =  Ixy1*atom79+atom838;
atom4019 = -( atom82*mz1-my1*atom86)*atom79+atom80*( mx1*atom82-my1*atom85);
atom1133 =  atom1132+Ixy2*atom103;
atom4119 =  ( my2*atom110-atom106*mz2)*atom103-atom104*( my2*atom109-mx2*atom106);
atom1434 =  Ixy3*atom127+atom1433;
atom4219 = -( mz3*atom130-atom149*my3)*atom127-atom128*( atom148*my3-mx3*atom130);
atom1752 =  atom168*Ixy4+atom1751;
atom4333 =  ( atom189*my4-mz4*atom171)*atom168-atom169*( atom188*my4-atom171*mx4);
atom2068 =  atom2067+Ixy5*atom208;
atom4447 = -( my5*atom228-atom211*mx5)*atom209+( my5*atom229-atom211*mz5)*atom208;
atom2384 =  atom248*Ixy6+atom2383;
atom4561 =  ( atom251*mx6-atom268*my6)*atom249+( atom269*my6-atom251*mz6)*atom248;
atom4013 =  mz1*atom85-mx1*atom86;
atom4113 = -mx2*atom110+mz2*atom109;
atom4213 = -mx3*atom149+mz3*atom148;
atom4327 = -atom189*mx4+mz4*atom188;
atom4441 = -mx5*atom229+mz5*atom228;
atom4555 =  mz6*atom268-mx6*atom269;

_MQ[0] = -mP;
_MQ[3] = -atom3829;
_MQ[4] = -atom3814;
_MQ[5] = -atom3790;
_MQ[25] = -mP;
_MQ[27] = -atom3832;
_MQ[28] = -atom3820;
_MQ[29] = -atom3799;
_MQ[50] = -mP;
_MQ[51] = -atom3835;
_MQ[52] = -atom3826;
_MQ[53] = -atom3808;
_MQ[72] = -atom3829;
_MQ[73] = -atom3832;
_MQ[74] = -atom3835;
_MQ[75] = -atom3843*atom40-atom39*( atom3768*atom39+atom3779*atom40);
_MQ[76] = -atom3841;
_MQ[77] = -atom3843;
_MQ[96] = -atom3814;
_MQ[97] = -atom3820;
_MQ[98] = -atom3826;
_MQ[99] = -atom3841;
_MQ[100] = -atom3777;
_MQ[101] = -atom3765;
_MQ[120] = -atom3790;
_MQ[121] = -atom3799;
_MQ[122] = -atom3808;
_MQ[123] = -atom3843;
_MQ[124] = -atom3765;
_MQ[125] = -IzzP;
_MQ[150] = -( Ixx1*atom79+atom835)*atom79-atom80*( atom838+atom840);
_MQ[156] = -atom839;
_MQ[162] = -atom4019;
_MQ[175] = -( atom1129+Ixx2*atom103)*atom103-atom104*( atom1132+atom1134);
_MQ[181] = -atom1133;
_MQ[187] = -atom4119;
_MQ[200] = -( Ixx3*atom127+atom1430)*atom127-atom128*( atom1433+atom1435);
_MQ[206] = -atom1434;
_MQ[212] = -atom4219;
_MQ[225] = -( atom1748+Ixx4*atom168)*atom168-atom169*( atom1753+atom1751);
_MQ[231] = -atom1752;
_MQ[237] = -atom4333;
_MQ[250] = -atom208*( atom208*Ixx5+atom2064)-( atom2067+atom2069)*atom209;
_MQ[256] = -atom2068;
_MQ[262] = -atom4447;
_MQ[275] = -( atom2385+atom2383)*atom249-atom248*( atom2380+atom248*Ixx6);
_MQ[281] = -atom2384;
_MQ[287] = -atom4561;
_MQ[294] = -atom839;
_MQ[300] = -Iyy1;
_MQ[306] = -atom4013;
_MQ[319] = -atom1133;
_MQ[325] = -Iyy2;
_MQ[331] = -atom4113;
_MQ[344] = -atom1434;
_MQ[350] = -Iyy3;
_MQ[356] = -atom4213;
_MQ[369] = -atom1752;
_MQ[375] = -Iyy4;
_MQ[381] = -atom4327;
_MQ[394] = -atom2068;
_MQ[400] = -Iyy5;
_MQ[406] = -atom4441;
_MQ[419] = -atom2384;
_MQ[425] = -Iyy6;
_MQ[431] = -atom4555;
_MQ[438] = -atom4019;
_MQ[444] = -atom4013;
_MQ[450] = -m1;
_MQ[463] = -atom4119;
_MQ[469] = -atom4113;
_MQ[475] = -m2;
_MQ[488] = -atom4219;
_MQ[494] = -atom4213;
_MQ[500] = -m3;
_MQ[513] = -atom4333;
_MQ[519] = -atom4327;
_MQ[525] = -m4;
_MQ[538] = -atom4447;
_MQ[544] = -atom4441;
_MQ[550] = -m5;
_MQ[563] = -atom4561;
_MQ[569] = -atom4555;
_MQ[575] = -m6;
_MQ[576] = -dB*( atom70*atom418-atom417*atom75)-mxP*( dB*atom3876-atom3873*atom3749)-mzP*( atom3873*atom3747-dB*atom3870)-( atom295*atom75+atom70*atom292)*da-( atom3870*atom3749-atom3747*atom3876)*myP;
_MQ[577] =  da*atom65*atom292-( atom289*atom75-atom418*atom65)*dB-( atom3879*atom3749-atom3885*atom3747)*myP+mxP*( atom3882*atom3749-atom3885*dB)-mzP*( atom3882*atom3747-dB*atom3879);
_MQ[578] =  ( atom70*atom289-atom417*atom65)*dB+atom295*da*atom65-( atom3891*atom3747-atom3888*dB)*mzP+( atom3891*atom3749-atom3894*dB)*mxP+( atom3894*atom3747-atom3888*atom3749)*myP+g*mP;
_MQ[579] = -atom2856*atom40-( atom3747*( atom3774*atom3749-dB*atom3779)+( atom3765*atom3749-IzzP*dB)*atom3749-atom3768*atom3937-atom3938*atom3758+dB*( atom3777*atom3749-dB*atom3781))*atom39+atom3992*atom40-atom39*( atom39*atom76+atom77*atom43);
_MQ[580] =  atom3765*atom3938+atom3774*atom3937-( IzzP*atom3747-atom3758*atom3749)*atom3749+atom3747*( atom3768*atom3749-atom3747*atom3779)-atom77*atom41+dB*( atom3771*atom3749-atom3747*atom3781);
_MQ[581] =  atom3992-atom2856;
_MQ[582] =  dB1*da1*atom4004+(dB1*dB1)*atom986+g*( atom81*my1+atom80*mx1*atom82-atom82*mz1*atom79);
_MQ[583] =  atom1266*(dB2*dB2)+atom4104*dB2*da2-( atom106*atom103*mz2-atom105*my2-atom104*mx2*atom106)*g;
_MQ[584] =  dB3*atom4204*da3+atom165/2.0+(dB3*dB3)*atom1586-atom166*atom131;
_MQ[585] =  atom1910*(dB4*dB4)-atom206*atom131+atom205/2.0+da4*atom4318*dB4;
_MQ[586] =  atom4432*da5*dB5+atom245/2.0+atom2220*(dB5*dB5)+atom246*atom131;
_MQ[587] =  atom286*atom131+atom4546*da6*dB6+(dB6*dB6)*atom2540+atom285/2.0;
_MQ[588] = -(da1*da1)*atom4004-dB1*da1*atom986-g*atom81*atom89;
_MQ[589] = -g*atom105*atom113-atom4104*(da2*da2)-atom1266*dB2*da2;
_MQ[590] = -atom165*atom132-atom166*atom134-atom4204*(da3*da3)-dB3*da3*atom1586;
_MQ[591] = -atom172*atom205-(da4*da4)*atom4318-atom206*atom174-da4*atom1910*dB4;
_MQ[592] = -atom4432*(da5*da5)-atom212*atom245-atom2220*da5*dB5-atom246*atom214;
_MQ[593] = -atom4546*(da6*da6)-atom254*atom286-atom252*atom285-da6*dB6*atom2540;
_MQ[594] = -mx1*dB1*atom4041+da1*my1*atom4041-( (dB1*dB1)*atom86+(da1*da1)*atom86)*mz1+dB1*da1*atom82*atom89+g*m1;
_MQ[595] =  atom4141*da2*my2-( (da2*da2)*atom110+(dB2*dB2)*atom110)*mz2-dB2*atom4141*mx2+g*m2+dB2*da2*atom113*atom106;
_MQ[596] =  da3*my3*atom4255-da3*( atom1426*atom154+-2.0*atom159*atom1426*atom131)/2.0-dB3*mx3*atom4255-mz3*( (da3*da3)*atom149+(dB3*dB3)*atom149)+g*m3;
_MQ[597] =  da4*atom4369*my4-( atom189*(dB4*dB4)+(da4*da4)*atom189)*mz4+( 2.0*atom1744*atom131*atom199-atom194*atom1744)*da4/2.0-atom4369*mx4*dB4+g*m4;
_MQ[598] =  my5*da5*atom4483-atom4483*mx5*dB5-da5*( 2.0*atom2060*atom239*atom131+atom2060*atom234)/2.0+g*m5-( atom229*(dB5*dB5)+(da5*da5)*atom229)*mz5;
_MQ[599] =  da6*atom4597*my6-mz6*( atom269*(dB6*dB6)+(da6*da6)*atom269)-mx6*atom4597*dB6-( 2.0*atom2376*atom279*atom131+atom2376*atom274)*da6/2.0+g*m6;

return _MQ;
}

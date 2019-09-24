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
#define alfa param[ 5 ]
#define mP param[ 6 ]
#define mxP param[ 7 ]
#define myP param[ 8 ]
#define mzP param[ 9 ]
#define IxxP param[ 10 ]
#define IxyP param[ 11 ]
#define IyyP param[ 12 ]
#define IxzP param[ 13 ]
#define IzzP param[ 14 ]
#define IyzP param[ 15 ]
#define m1 param[ 16 ]
#define mx1 param[ 17 ]
#define my1 param[ 18 ]
#define mz1 param[ 19 ]
#define Ixx1 param[ 20 ]
#define Ixy1 param[ 21 ]
#define Iyy1 param[ 22 ]
#define Ixz1 param[ 23 ]
#define Izz1 param[ 24 ]
#define Iyz1 param[ 25 ]
#define m2 param[ 26 ]
#define mx2 param[ 27 ]
#define my2 param[ 28 ]
#define mz2 param[ 29 ]
#define Ixx2 param[ 30 ]
#define Ixy2 param[ 31 ]
#define Iyy2 param[ 32 ]
#define Ixz2 param[ 33 ]
#define Izz2 param[ 34 ]
#define Iyz2 param[ 35 ]
#define m3 param[ 36 ]
#define mx3 param[ 37 ]
#define my3 param[ 38 ]
#define mz3 param[ 39 ]
#define Ixx3 param[ 40 ]
#define Ixy3 param[ 41 ]
#define Iyy3 param[ 42 ]
#define Ixz3 param[ 43 ]
#define Izz3 param[ 44 ]
#define Iyz3 param[ 45 ]
#define m4 param[ 46 ]
#define mx4 param[ 47 ]
#define my4 param[ 48 ]
#define mz4 param[ 49 ]
#define Ixx4 param[ 50 ]
#define Ixy4 param[ 51 ]
#define Iyy4 param[ 52 ]
#define Ixz4 param[ 53 ]
#define Izz4 param[ 54 ]
#define Iyz4 param[ 55 ]
#define m5 param[ 56 ]
#define mx5 param[ 57 ]
#define my5 param[ 58 ]
#define mz5 param[ 59 ]
#define Ixx5 param[ 60 ]
#define Ixy5 param[ 61 ]
#define Iyy5 param[ 62 ]
#define Ixz5 param[ 63 ]
#define Izz5 param[ 64 ]
#define Iyz5 param[ 65 ]
#define m6 param[ 66 ]
#define mx6 param[ 67 ]
#define my6 param[ 68 ]
#define mz6 param[ 69 ]
#define Ixx6 param[ 70 ]
#define Ixy6 param[ 71 ]
#define Iyy6 param[ 72 ]
#define Ixz6 param[ 73 ]
#define Izz6 param[ 74 ]
#define Iyz6 param[ 75 ]
#define Fs1 param[ 76 ]
#define Fs2 param[ 77 ]
#define Fs3 param[ 78 ]
#define Fs4 param[ 79 ]
#define Fs5 param[ 80 ]
#define Fs6 param[ 81 ]
#define FS001 param[ 82 ]
#define FSa11 param[ 83 ]
#define FSb11 param[ 84 ]
#define FSa21 param[ 85 ]
#define FSb21 param[ 86 ]
#define FS002 param[ 87 ]
#define FSa12 param[ 88 ]
#define FSb12 param[ 89 ]
#define FSa22 param[ 90 ]
#define FSb22 param[ 91 ]
#define FS003 param[ 92 ]
#define FSa13 param[ 93 ]
#define FSb13 param[ 94 ]
#define FSa23 param[ 95 ]
#define FSb23 param[ 96 ]
#define FS004 param[ 97 ]
#define FSa14 param[ 98 ]
#define FSb14 param[ 99 ]
#define FSa24 param[ 100 ]
#define FSb24 param[ 101 ]
#define FS005 param[ 102 ]
#define FSa15 param[ 103 ]
#define FSb15 param[ 104 ]
#define FSa25 param[ 105 ]
#define FSb25 param[ 106 ]
#define FS006 param[ 107 ]
#define FSa16 param[ 108 ]
#define FSb16 param[ 109 ]
#define FSa26 param[ 110 ]
#define FSb26 param[ 111 ]
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

double atom43;
double atom39;
double atom42;
double atom44;
double atom40;
double atom45;
double atom56;
double atom53;
double atom41;
double atom46;
double atom292;
double atom72;
double atom4194;
double atom48;
double atom47;
double atom62;
double atom59;
double atom77;
double atom4193;
double atom293;
double atom1493;
double atom1490;
double atom4132;
double atom4139;
double atom50;
double atom4131;
double atom4138;
double atom4220;
double atom4135;
double atom49;
double atom4223;
double atom4226;
double atom67;
double atom4232;
double atom4229;
double atom4235;
double atom4241;
double atom4244;
double atom4238;
double atom4292;
double atom4289;
double atom4293;
double atom4310;
double atom4309;
double atom4348;
double atom4321;
double atom4349;
double atom4350;
double atom78;
double atom79;
double atom1497;
double atom5262;
double atom5259;
double atom81;
double atom3157;
double atom82;
double atom4464;
double atom4453;
double atom3163;
double atom3164;
double atom3204;
double atom4452;
double atom91;
double atom84;
double atom103;
double atom85;
double atom86;
double atom83;
double atom102;
double atom105;
double atom3239;
double atom3284;
double atom106;
double atom3243;
double atom3244;
double atom4602;
double atom4591;
double atom4590;
double atom108;
double atom110;
double atom109;
double atom107;
double atom126;
double atom115;
double atom127;
double atom0;
double atom132;
double atom1;
double atom134;
double atom129;
double atom3;
double atom130;
double atom142;
double atom139;
double atom131;
double atom133;
double atom155;
double atom136;
double atom167;
double atom145;
double atom135;
double atom148;
double atom160;
double atom166;
double atom2592;
double atom4753;
double atom4742;
double atom2586;
double atom2587;
double atom2642;
double atom4741;
double atom170;
double atom172;
double atom169;
double atom174;
double atom182;
double atom171;
double atom173;
double atom179;
double atom195;
double atom176;
double atom207;
double atom185;
double atom175;
double atom188;
double atom200;
double atom206;
double atom2747;
double atom4904;
double atom4893;
double atom2740;
double atom2741;
double atom2796;
double atom4892;
double atom213;
double atom212;
double atom215;
double atom210;
double atom217;
double atom209;
double atom214;
double atom211;
double atom218;
double atom219;
double atom228;
double atom231;
double atom243;
double atom222;
double atom249;
double atom216;
double atom225;
double atom238;
double atom250;
double atom2890;
double atom2955;
double atom2901;
double atom2902;
double atom5055;
double atom5044;
double atom5043;
double atom253;
double atom252;
double atom3045;
double atom5206;
double atom5195;
double atom3053;
double atom3108;
double atom3054;
double atom5194;
double atom255;
double atom259;
double atom257;
double atom265;
double atom254;
double atom256;
double atom262;
double atom278;
double atom271;
double atom290;
double atom258;
double atom268;
double atom283;
double atom289;
double atom87;
double atom4402;
double atom88;
double atom4396;
double atom4399;
double atom112;
double atom4534;
double atom111;
double atom4537;
double atom4540;
double atom150;
double atom149;
double atom4688;
double atom4685;
double atom4691;
double atom190;
double atom189;
double atom4839;
double atom4836;
double atom4842;
double atom233;
double atom232;
double atom4990;
double atom4987;
double atom4993;
double atom273;
double atom5138;
double atom272;
double atom5141;
double atom5144;

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

atom43 = cos(a);
atom39 = cos(c);
atom42 = sin(b);
atom44 = sin(a);
atom40 = sin(c);
atom45 = atom42*atom44;
atom56 =  atom43*atom39-atom40*atom45;
atom53 =  atom43*atom40+atom39*atom45;
atom41 = cos(b);
atom46 = -atom44*atom41;
atom292 = atom42*dc;
atom72 =  mxP*atom53+myP*atom56+mzP*atom46;
atom4194 = -atom292*atom43;
atom48 = atom43*atom41;
atom47 = -atom42*atom43;
atom62 = -atom40*atom47+atom39*atom44;
atom59 =  atom39*atom47+atom44*atom40;
atom77 =  atom62*myP+mxP*atom59+atom48*mzP;
atom4193 = atom292*atom44;
atom293 = dc*atom41;
atom1493 =  dB*atom44+atom43*atom293;
atom1490 = -atom44*atom293+atom43*dB;
atom4132 = atom42*da;
atom4139 =  dc+atom4132;
atom50 = -atom40*atom41;
atom4131 = da*atom41;
atom4138 =  atom39*dB-atom4131*atom40;
atom4220 = -atom42*atom4138+atom4139*atom50;
atom4135 =  atom4131*atom39+dB*atom40;
atom49 = atom39*atom41;
atom4223 =  atom42*atom4135-atom49*atom4139;
atom4226 = -atom4135*atom50+atom49*atom4138;
atom67 =  atom42*mzP+atom49*mxP+myP*atom50;
atom4232 = -atom4139*atom53+atom4135*atom46;
atom4229 = -atom4138*atom46+atom4139*atom56;
atom4235 =  atom53*atom4138-atom4135*atom56;
atom4241 = -atom59*atom4139+atom4135*atom48;
atom4244 =  atom59*atom4138-atom4135*atom62;
atom4238 = -atom48*atom4138+atom62*atom4139;
atom4292 =  dB*atom40*atom4132-atom4135*dc;
atom4289 =  dc*atom4138-atom39*dB*atom4132;
atom4293 = atom4131*dB;
atom4310 = IxzP*atom4138;
atom4309 = -atom4139*IxyP;
atom4348 =  ( atom4310+atom4309)*atom4135-( atom4139*IyyP-IyzP*atom4138)*atom4138+IxzP*atom4293-( atom4139*IyzP-IzzP*atom4138)*atom4139+atom4292*IxyP+atom4289*IxxP;
atom4321 = -atom4135*IyzP;
atom4349 = -atom4135*( IxzP*atom4135-IxxP*atom4139)+atom4292*IyyP+atom4289*IxyP+( IxzP*atom4139-atom4135*IzzP)*atom4139+atom4293*IyzP-( atom4309-atom4321)*atom4138;
atom4350 =  ( atom4135*IxyP-IxxP*atom4138)*atom4135-( IxyP*atom4138-atom4135*IyyP)*atom4138+IzzP*atom4293+atom4292*IyzP-atom4139*( atom4310+atom4321)+atom4289*IxzP;
atom78 = -g*atom72;
atom79 = g*atom67;
atom1497 =  atom42*atom78+atom79*atom46;
atom5262 =  atom50*atom78+atom79*atom56;
atom5259 =  atom49*atom78+atom79*atom53;
atom81 = cos(b1);
atom3157 = atom81*da1;
atom82 = sin(b1);
atom4464 = -Iyz1*atom3157;
atom4453 = Ixz1*dB1;
atom3163 = -da1*atom82;
atom3164 = atom3163*dB1;
atom3204 = dB1*atom3157;
atom4452 = atom3163*Ixy1;
atom91 =  atom81*mx1+atom82*mz1;
atom84 = sin(a1);
atom103 = g*atom91;
atom85 = atom82*atom84;
atom86 = -atom81*atom84;
atom83 = cos(a1);
atom102 = -( mx1*atom85+atom86*mz1+atom83*my1)*g;
atom105 = cos(b2);
atom3239 = atom105*da2;
atom3284 = dB2*atom3239;
atom106 = sin(b2);
atom3243 = -da2*atom106;
atom3244 = atom3243*dB2;
atom4602 = -atom3239*Iyz2;
atom4591 = Ixz2*dB2;
atom4590 = atom3243*Ixy2;
atom108 = sin(a2);
atom110 = -atom105*atom108;
atom109 = atom106*atom108;
atom107 = cos(a2);
atom126 = -g*( mz2*atom110+atom107*my2+mx2*atom109);
atom115 =  atom105*mx2+mz2*atom106;
atom127 = g*atom115;
atom0 = 2.0*alfa;
atom132 = sin(a3);
atom1 = sin(atom0);
atom134 = atom132*atom1;
atom129 = cos(b3);
atom3 = cos(atom0);
atom130 = sin(b3);
atom142 =  atom3*atom130+atom134*atom129;
atom139 = -atom134*atom130+atom129*atom3;
atom131 = cos(a3);
atom133 = -atom131*atom1;
atom155 =  atom139*mx3+atom142*mz3+atom133*my3;
atom136 = -atom3*atom132;
atom167 = g*atom155;
atom145 =  atom129*atom1-atom130*atom136;
atom135 = atom3*atom131;
atom148 =  atom129*atom136+atom130*atom1;
atom160 =  atom135*my3+mx3*atom145+mz3*atom148;
atom166 = -g*atom160;
atom2592 = da3*atom129;
atom4753 = -Iyz3*atom2592;
atom4742 = Ixz3*dB3;
atom2586 = -da3*atom130;
atom2587 = atom2586*dB3;
atom2642 = dB3*atom2592;
atom4741 = atom2586*Ixy3;
atom170 = sin(b4);
atom172 = sin(a4);
atom169 = cos(b4);
atom174 = atom172*atom1;
atom182 =  atom170*atom3+atom169*atom174;
atom171 = cos(a4);
atom173 = -atom171*atom1;
atom179 =  atom3*atom169-atom170*atom174;
atom195 =  atom182*mz4+atom173*my4+atom179*mx4;
atom176 = -atom3*atom172;
atom207 = g*atom195;
atom185 =  atom169*atom1-atom176*atom170;
atom175 = atom3*atom171;
atom188 =  atom176*atom169+atom170*atom1;
atom200 =  atom175*my4+mz4*atom188+mx4*atom185;
atom206 = -g*atom200;
atom2747 = da4*atom169;
atom4904 = -Iyz4*atom2747;
atom4893 = Ixz4*dB4;
atom2740 = -da4*atom170;
atom2741 = dB4*atom2740;
atom2796 = dB4*atom2747;
atom4892 = atom2740*Ixy4;
atom213 = 4.0000000000000000e+00*alfa;
atom212 = sin(a5);
atom215 = sin(atom213);
atom210 = sin(b5);
atom217 = atom212*atom215;
atom209 = cos(b5);
atom214 = cos(atom213);
atom211 = cos(a5);
atom218 = atom211*atom214;
atom219 = -atom214*atom212;
atom228 = -atom210*atom219+atom209*atom215;
atom231 =  atom209*atom219+atom210*atom215;
atom243 =  my5*atom218+atom228*mx5+mz5*atom231;
atom222 = -atom210*atom217+atom209*atom214;
atom249 = -g*atom243;
atom216 = -atom211*atom215;
atom225 =  atom209*atom217+atom210*atom214;
atom238 =  my5*atom216+atom222*mx5+mz5*atom225;
atom250 = g*atom238;
atom2890 = atom209*da5;
atom2955 = dB5*atom2890;
atom2901 = -atom210*da5;
atom2902 = dB5*atom2901;
atom5055 = -Iyz5*atom2890;
atom5044 = dB5*Ixz5;
atom5043 = Ixy5*atom2901;
atom253 = sin(b6);
atom252 = cos(b6);
atom3045 = atom252*da6;
atom5206 = -Iyz6*atom3045;
atom5195 = dB6*Ixz6;
atom3053 = -atom253*da6;
atom3108 = dB6*atom3045;
atom3054 = dB6*atom3053;
atom5194 = Ixy6*atom3053;
atom255 = sin(a6);
atom259 = -atom214*atom255;
atom257 = atom255*atom215;
atom265 =  atom214*atom253+atom252*atom257;
atom254 = cos(a6);
atom256 = -atom254*atom215;
atom262 = -atom257*atom253+atom214*atom252;
atom278 =  atom265*mz6+atom262*mx6+my6*atom256;
atom271 =  atom215*atom253+atom252*atom259;
atom290 = g*atom278;
atom258 = atom254*atom214;
atom268 = -atom259*atom253+atom215*atom252;
atom283 =  atom268*mx6+atom271*mz6+my6*atom258;
atom289 = -g*atom283;
atom87 = -atom82*atom83;
atom4402 = -atom84*atom3157+atom87*dB1;
atom88 = atom81*atom83;
atom4396 = -atom88*dB1-atom3163*atom84;
atom4399 =  atom88*atom3157+atom3163*atom87;
atom112 = atom105*atom107;
atom4534 = -atom3243*atom108-atom112*dB2;
atom111 = -atom106*atom107;
atom4537 =  atom112*atom3239+atom3243*atom111;
atom4540 = -atom108*atom3239+atom111*dB2;
atom150 = atom129*atom131;
atom149 = -atom130*atom131;
atom4688 =  atom2586*atom149+atom150*atom2592;
atom4685 = -dB3*atom150-atom2586*atom132;
atom4691 = -atom2592*atom132+dB3*atom149;
atom190 = atom171*atom169;
atom189 = -atom170*atom171;
atom4839 =  atom189*atom2740+atom2747*atom190;
atom4836 = -atom2740*atom172-dB4*atom190;
atom4842 = -atom2747*atom172+atom189*dB4;
atom233 = atom209*atom211;
atom232 = -atom210*atom211;
atom4990 =  atom232*atom2901+atom2890*atom233;
atom4987 = -atom212*atom2901-dB5*atom233;
atom4993 =  atom232*dB5-atom212*atom2890;
atom273 = atom254*atom252;
atom5138 = -atom255*atom3053-dB6*atom273;
atom272 = -atom254*atom253;
atom5141 =  atom3045*atom273+atom3053*atom272;
atom5144 =  dB6*atom272-atom255*atom3045;

_Q[0] = -( atom4226*atom4138-atom4223*atom4139)*mxP-( atom4135*atom4223-atom4220*atom4138)*mzP-( atom77*atom1493+atom72*atom1490)*da+myP*( atom4135*atom4226-atom4220*atom4139)+dB*( atom77*atom4193-atom72*atom4194);
_Q[1] =  atom67*atom1490*da+myP*( atom4235*atom4135-atom4139*atom4229)-mzP*( atom4135*atom4232-atom4229*atom4138)-( atom4235*atom4138-atom4232*atom4139)*mxP+dB*( atom67*atom4194-atom77*atom293);
_Q[2] =  g*mP-dB*( atom67*atom4193-atom72*atom293)-( atom4238*atom4139-atom4135*atom4244)*myP+( atom4241*atom4139-atom4244*atom4138)*mxP+atom67*da*atom1493+( atom4238*atom4138-atom4135*atom4241)*mzP;
_Q[3] =  atom42*atom4350-atom49*atom5259-atom42*atom1497+atom49*atom4348+atom50*atom4349-atom5262*atom50;
_Q[4] = -atom5259*atom40-atom5262*atom39+atom39*atom4349+atom4348*atom40;
_Q[5] = -atom1497+atom4350;
_Q[6] = -atom82*( atom82*atom102+atom86*atom103)+( ( Ixy1*atom3157-Ixx1*dB1)*atom3157+atom3204*Izz1+atom3163*( atom4464+atom4453)-( Ixy1*dB1-Iyy1*atom3157)*dB1+Ixz1*atom3164)*atom82-atom81*( atom81*atom102+atom103*atom85)+atom81*( ( atom4453+atom4452)*atom3157+Ixx1*atom3164-atom3163*( atom3163*Iyz1+Izz1*dB1)+( atom3163*Iyy1+dB1*Iyz1)*dB1+Ixz1*atom3204);
_Q[7] =  atom106*( Ixz2*atom3244+Izz2*atom3284-( Ixx2*dB2-Ixy2*atom3239)*atom3239-( Ixy2*dB2-atom3239*Iyy2)*dB2+( atom4602+atom4591)*atom3243)+atom105*( Ixz2*atom3284-atom3243*( atom3243*Iyz2+Izz2*dB2)+( atom3243*Iyy2+dB2*Iyz2)*dB2+Ixx2*atom3244+( atom4590+atom4591)*atom3239)-atom106*( atom106*atom126+atom110*atom127)-atom105*( atom105*atom126+atom127*atom109);
_Q[8] =  atom129*( atom2642*Ixz3+atom2587*Ixx3-atom2586*( Iyz3*atom2586+dB3*Izz3)+( atom4741+atom4742)*atom2592+( Iyy3*atom2586+Iyz3*dB3)*dB3)+atom130*( dB3*( Iyy3*atom2592-dB3*Ixy3)+atom2586*( atom4753+atom4742)+atom2587*Ixz3+atom2642*Izz3-( Ixx3*dB3-Ixy3*atom2592)*atom2592)-atom129*( atom139*atom166+atom167*atom145)-( atom148*atom167+atom142*atom166)*atom130;
_Q[9] =  ( Ixx4*atom2741-( dB4*Izz4+Iyz4*atom2740)*atom2740+Ixz4*atom2796+( atom4892+atom4893)*atom2747+dB4*( Iyz4*dB4+Iyy4*atom2740))*atom169-( atom179*atom206+atom207*atom185)*atom169-atom170*( atom182*atom206+atom188*atom207)+atom170*( Izz4*atom2796+( atom2747*Ixy4-Ixx4*dB4)*atom2747+Ixz4*atom2741-dB4*( dB4*Ixy4-Iyy4*atom2747)+( atom4904+atom4893)*atom2740);
_Q[10] = -atom210*( atom250*atom231+atom249*atom225)+atom210*( Ixz5*atom2902+( atom5055+atom5044)*atom2901+atom2955*Izz5+dB5*( Iyy5*atom2890-dB5*Ixy5)-atom2890*( dB5*Ixx5-atom2890*Ixy5))-atom209*( atom250*atom228+atom222*atom249)+atom209*( ( Iyy5*atom2901+Iyz5*dB5)*dB5-( dB5*Izz5+Iyz5*atom2901)*atom2901+atom2890*( atom5043+atom5044)+Ixz5*atom2955+Ixx5*atom2902);
_Q[11] = -( atom262*atom289+atom268*atom290)*atom252+( Ixz6*atom3054+( Ixy6*atom3045-dB6*Ixx6)*atom3045+atom3108*Izz6+atom3053*( atom5206+atom5195)-dB6*( Ixy6*dB6-Iyy6*atom3045))*atom253+( ( atom5195+atom5194)*atom3045+dB6*( Iyz6*dB6+Iyy6*atom3053)+atom3054*Ixx6-( dB6*Izz6+Iyz6*atom3053)*atom3053+atom3108*Ixz6)*atom252-( atom271*atom290+atom265*atom289)*atom253;
_Q[12] = -( atom3163*Ixx1+Ixz1*atom3157)*atom3157+atom3163*( Izz1*atom3157+atom3163*Ixz1)+dB1*( atom4464-atom4452)+Ixy1*atom3164+atom3204*Iyz1-atom83*atom103;
_Q[13] = -( Ixz2*atom3239+atom3243*Ixx2)*atom3239-dB2*( atom4590-atom4602)+Iyz2*atom3284-atom107*atom127+Ixy2*atom3244+atom3243*( atom3243*Ixz2+Izz2*atom3239);
_Q[14] =  atom2586*( Izz3*atom2592+Ixz3*atom2586)-atom133*atom166-atom135*atom167+Iyz3*atom2642+atom2587*Ixy3-( Ixz3*atom2592+atom2586*Ixx3)*atom2592-dB3*( atom4741-atom4753);
_Q[15] = -( Ixx4*atom2740+Ixz4*atom2747)*atom2747+Iyz4*atom2796+( atom2747*Izz4+Ixz4*atom2740)*atom2740-atom175*atom207+atom2741*Ixy4-atom173*atom206-dB4*( atom4892-atom4904);
_Q[16] =  ( Ixz5*atom2901+atom2890*Izz5)*atom2901-( Ixx5*atom2901+Ixz5*atom2890)*atom2890+Iyz5*atom2955+atom2902*Ixy5-atom249*atom216-atom250*atom218-dB5*( atom5043-atom5055);
_Q[17] =  atom3108*Iyz6+atom3053*( atom3045*Izz6+atom3053*Ixz6)-atom289*atom256-atom258*atom290+Ixy6*atom3054+dB6*( atom5206-atom5194)-( Ixz6*atom3045+atom3053*Ixx6)*atom3045;
_Q[18] =  ( atom4396*dB1-atom4399*atom3157)*mz1-mx1*( atom3163*atom4399+atom4402*dB1)+da1*atom84*dB1*atom91-Fs1+g*m1+( atom3163*atom4396+atom4402*atom3157)*my1;
_Q[19] = -Fs2+da2*dB2*atom108*atom115+mz2*( atom4534*dB2-atom4537*atom3239)+g*m2-mx2*( atom3243*atom4537+dB2*atom4540)+( atom4540*atom3239+atom3243*atom4534)*my2;
_Q[20] =  da3*( atom134*atom160*dB3-atom155*dB3*atom136)-mx3*( atom2586*atom4688+dB3*atom4691)+( atom2592*atom4691+atom4685*atom2586)*my3-mz3*( atom2592*atom4688-atom4685*dB3)+g*m3-Fs3;
_Q[21] =  ( atom4842*atom2747+atom2740*atom4836)*my4+da4*( atom200*dB4*atom174-atom176*dB4*atom195)+g*m4-mx4*( atom4839*atom2740+atom4842*dB4)-mz4*( atom4839*atom2747-dB4*atom4836)-Fs4;
_Q[22] =  my5*( atom4987*atom2901+atom2890*atom4993)-Fs5+g*m5-( atom4990*atom2890-atom4987*dB5)*mz5-( atom4990*atom2901+dB5*atom4993)*mx5+( atom243*dB5*atom217-atom238*dB5*atom219)*da5;
_Q[23] = -( atom5144*dB6+atom3053*atom5141)*mx6+mz6*( dB6*atom5138-atom5141*atom3045)+my6*( atom3053*atom5138+atom5144*atom3045)-Fs6-( dB6*atom259*atom278-dB6*atom257*atom283)*da6+g*m6;

return _Q;
}

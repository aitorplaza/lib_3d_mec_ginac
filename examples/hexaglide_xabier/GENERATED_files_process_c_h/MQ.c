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

double atom39;
double atom41;
double atom49;
double atom40;
double atom50;
double atom42;
double atom4148;
double atom4145;
double atom4142;
double atom43;
double atom44;
double atom45;
double atom56;
double atom53;
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
double atom4131;
double atom4138;
double atom4220;
double atom4135;
double atom4223;
double atom4226;
double atom4157;
double atom4154;
double atom4151;
double atom67;
double atom4232;
double atom4229;
double atom4235;
double atom4160;
double atom4163;
double atom4166;
double atom4241;
double atom4244;
double atom4238;
double atom301;
double atom306;
double atom311;
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
double atom82;
double atom81;
double atom84;
double atom83;
double atom87;
double atom88;
double atom3157;
double atom4464;
double atom4453;
double atom3163;
double atom3164;
double atom3204;
double atom4452;
double atom91;
double atom103;
double atom85;
double atom86;
double atom102;
double atom106;
double atom105;
double atom107;
double atom112;
double atom108;
double atom111;
double atom3239;
double atom3284;
double atom3243;
double atom3244;
double atom4602;
double atom4591;
double atom4590;
double atom110;
double atom109;
double atom126;
double atom115;
double atom127;
double atom130;
double atom129;
double atom132;
double atom131;
double atom149;
double atom150;
double atom0;
double atom1;
double atom134;
double atom3;
double atom142;
double atom139;
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
double atom169;
double atom172;
double atom171;
double atom189;
double atom190;
double atom174;
double atom182;
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
double atom210;
double atom209;
double atom212;
double atom211;
double atom232;
double atom233;
double atom213;
double atom215;
double atom217;
double atom214;
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
double atom255;
double atom254;
double atom272;
double atom273;
double atom3045;
double atom5206;
double atom5195;
double atom3053;
double atom3108;
double atom3054;
double atom5194;
double atom259;
double atom257;
double atom265;
double atom256;
double atom262;
double atom278;
double atom271;
double atom290;
double atom258;
double atom268;
double atom283;
double atom289;
double atom4402;
double atom4396;
double atom4399;
double atom4534;
double atom4537;
double atom4540;
double atom4688;
double atom4685;
double atom4691;
double atom4839;
double atom4836;
double atom4842;
double atom4990;
double atom4987;
double atom4993;
double atom5138;
double atom5141;
double atom5144;
double atom4171;
double atom4174;
double atom4179;
double atom4182;
double atom4187;
double atom4190;
double atom343;
double atom320;
double atom653;
double atom4373;
double atom767;
double atom4511;
double atom881;
double atom4649;
double atom1005;
double atom4800;
double atom1129;
double atom4951;
double atom1253;
double atom5102;
double atom4367;
double atom4505;
double atom4643;
double atom4794;
double atom4945;
double atom5096;

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

atom39 = cos(c);
atom41 = cos(b);
atom49 = atom39*atom41;
atom40 = sin(c);
atom50 = -atom40*atom41;
atom42 = sin(b);
atom4148 = -atom49*myP+mxP*atom50;
atom4145 = -atom42*mxP+atom49*mzP;
atom4142 = -atom50*mzP+atom42*myP;
atom43 = cos(a);
atom44 = sin(a);
atom45 = atom42*atom44;
atom56 =  atom43*atom39-atom40*atom45;
atom53 =  atom43*atom40+atom39*atom45;
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
atom4131 = da*atom41;
atom4138 =  atom39*dB-atom4131*atom40;
atom4220 = -atom42*atom4138+atom4139*atom50;
atom4135 =  atom4131*atom39+dB*atom40;
atom4223 =  atom42*atom4135-atom49*atom4139;
atom4226 = -atom4135*atom50+atom49*atom4138;
atom4157 = -myP*atom53+mxP*atom56;
atom4154 = -mxP*atom46+mzP*atom53;
atom4151 = -atom56*mzP+myP*atom46;
atom67 =  atom42*mzP+atom49*mxP+myP*atom50;
atom4232 = -atom4139*atom53+atom4135*atom46;
atom4229 = -atom4138*atom46+atom4139*atom56;
atom4235 =  atom53*atom4138-atom4135*atom56;
atom4160 =  myP*atom48-atom62*mzP;
atom4163 =  atom59*mzP-mxP*atom48;
atom4166 =  atom62*mxP-atom59*myP;
atom4241 = -atom59*atom4139+atom4135*atom48;
atom4244 =  atom59*atom4138-atom4135*atom62;
atom4238 = -atom48*atom4138+atom62*atom4139;
atom301 =  IxxP*atom49+IxyP*atom50+atom42*IxzP;
atom306 =  atom49*IxyP+atom50*IyyP+atom42*IyzP;
atom311 =  atom42*IzzP+IyzP*atom50+IxzP*atom49;
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
atom82 = sin(b1);
atom81 = cos(b1);
atom84 = sin(a1);
atom83 = cos(a1);
atom87 = -atom82*atom83;
atom88 = atom81*atom83;
atom3157 = atom81*da1;
atom4464 = -Iyz1*atom3157;
atom4453 = Ixz1*dB1;
atom3163 = -da1*atom82;
atom3164 = atom3163*dB1;
atom3204 = dB1*atom3157;
atom4452 = atom3163*Ixy1;
atom91 =  atom81*mx1+atom82*mz1;
atom103 = g*atom91;
atom85 = atom82*atom84;
atom86 = -atom81*atom84;
atom102 = -( mx1*atom85+atom86*mz1+atom83*my1)*g;
atom106 = sin(b2);
atom105 = cos(b2);
atom107 = cos(a2);
atom112 = atom105*atom107;
atom108 = sin(a2);
atom111 = -atom106*atom107;
atom3239 = atom105*da2;
atom3284 = dB2*atom3239;
atom3243 = -da2*atom106;
atom3244 = atom3243*dB2;
atom4602 = -atom3239*Iyz2;
atom4591 = Ixz2*dB2;
atom4590 = atom3243*Ixy2;
atom110 = -atom105*atom108;
atom109 = atom106*atom108;
atom126 = -g*( mz2*atom110+atom107*my2+mx2*atom109);
atom115 =  atom105*mx2+mz2*atom106;
atom127 = g*atom115;
atom130 = sin(b3);
atom129 = cos(b3);
atom132 = sin(a3);
atom131 = cos(a3);
atom149 = -atom130*atom131;
atom150 = atom129*atom131;
atom0 = 2.0*alfa;
atom1 = sin(atom0);
atom134 = atom132*atom1;
atom3 = cos(atom0);
atom142 =  atom3*atom130+atom134*atom129;
atom139 = -atom134*atom130+atom129*atom3;
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
atom169 = cos(b4);
atom172 = sin(a4);
atom171 = cos(a4);
atom189 = -atom170*atom171;
atom190 = atom171*atom169;
atom174 = atom172*atom1;
atom182 =  atom170*atom3+atom169*atom174;
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
atom210 = sin(b5);
atom209 = cos(b5);
atom212 = sin(a5);
atom211 = cos(a5);
atom232 = -atom210*atom211;
atom233 = atom209*atom211;
atom213 = 4.0000000000000000e+00*alfa;
atom215 = sin(atom213);
atom217 = atom212*atom215;
atom214 = cos(atom213);
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
atom255 = sin(a6);
atom254 = cos(a6);
atom272 = -atom254*atom253;
atom273 = atom254*atom252;
atom3045 = atom252*da6;
atom5206 = -Iyz6*atom3045;
atom5195 = dB6*Ixz6;
atom3053 = -atom253*da6;
atom3108 = dB6*atom3045;
atom3054 = dB6*atom3053;
atom5194 = Ixy6*atom3053;
atom259 = -atom214*atom255;
atom257 = atom255*atom215;
atom265 =  atom214*atom253+atom252*atom257;
atom256 = -atom254*atom215;
atom262 = -atom257*atom253+atom214*atom252;
atom278 =  atom265*mz6+atom262*mx6+my6*atom256;
atom271 =  atom215*atom253+atom252*atom259;
atom290 = g*atom278;
atom258 = atom254*atom214;
atom268 = -atom259*atom253+atom215*atom252;
atom283 =  atom268*mx6+atom271*mz6+my6*atom258;
atom289 = -g*atom283;
atom4402 = -atom84*atom3157+atom87*dB1;
atom4396 = -atom88*dB1-atom3163*atom84;
atom4399 =  atom88*atom3157+atom3163*atom87;
atom4534 = -atom3243*atom108-atom112*dB2;
atom4537 =  atom112*atom3239+atom3243*atom111;
atom4540 = -atom108*atom3239+atom111*dB2;
atom4688 =  atom2586*atom149+atom150*atom2592;
atom4685 = -dB3*atom150-atom2586*atom132;
atom4691 = -atom2592*atom132+dB3*atom149;
atom4839 =  atom189*atom2740+atom2747*atom190;
atom4836 = -atom2740*atom172-dB4*atom190;
atom4842 = -atom2747*atom172+atom189*dB4;
atom4990 =  atom232*atom2901+atom2890*atom233;
atom4987 = -atom212*atom2901-dB5*atom233;
atom4993 =  atom232*dB5-atom212*atom2890;
atom5138 = -atom255*atom3053-dB6*atom273;
atom5141 =  atom3045*atom273+atom3053*atom272;
atom5144 =  dB6*atom272-atom255*atom3045;
atom4171 =  atom49*atom4142+atom42*atom4148+atom4145*atom50;
atom4174 =  atom39*atom4145+atom40*atom4142;
atom4179 =  atom4154*atom50+atom4151*atom49+atom42*atom4157;
atom4182 =  atom4154*atom39+atom4151*atom40;
atom4187 =  atom42*atom4166+atom50*atom4163+atom49*atom4160;
atom4190 =  atom39*atom4163+atom40*atom4160;
atom343 =  atom306*atom39+atom301*atom40;
atom320 =  IxzP*atom40+atom39*IyzP;
atom653 =  atom82*Iyz1+atom81*Ixy1;
atom4373 = -atom81*( atom84*mz1-atom88*my1)-atom82*( atom87*my1-mx1*atom84);
atom767 =  atom106*Iyz2+atom105*Ixy2;
atom4511 = -atom105*( mz2*atom108-atom112*my2)+atom106*( mx2*atom108-atom111*my2);
atom881 =  Iyz3*atom130+atom129*Ixy3;
atom4649 =  atom130*( mx3*atom132-atom149*my3)-( mz3*atom132-atom150*my3)*atom129;
atom1005 =  Ixy4*atom169+Iyz4*atom170;
atom4800 =  atom169*( my4*atom190-mz4*atom172)-atom170*( atom189*my4-mx4*atom172);
atom1129 =  atom209*Ixy5+atom210*Iyz5;
atom4951 =  atom210*( atom212*mx5-my5*atom232)+atom209*( my5*atom233-mz5*atom212);
atom1253 =  Iyz6*atom253+Ixy6*atom252;
atom5102 =  atom253*( atom255*mx6-my6*atom272)+( my6*atom273-mz6*atom255)*atom252;
atom4367 = -atom88*mx1+atom87*mz1;
atom4505 = -atom112*mx2+mz2*atom111;
atom4643 = -mx3*atom150+mz3*atom149;
atom4794 = -mx4*atom190+atom189*mz4;
atom4945 =  atom232*mz5-mx5*atom233;
atom5096 = -mx6*atom273+mz6*atom272;

_MQ[0] = -mP;
_MQ[1] = 0.0;
_MQ[2] = 0.0;
_MQ[3] = -atom4171;
_MQ[4] = -atom4174;
_MQ[5] = -atom4148;
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
_MQ[27] = -atom4179;
_MQ[28] = -atom4182;
_MQ[29] = -atom4157;
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
_MQ[51] = -atom4187;
_MQ[52] = -atom4190;
_MQ[53] = -atom4166;
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
_MQ[72] = -atom4171;
_MQ[73] = -atom4179;
_MQ[74] = -atom4187;
_MQ[75] = -atom306*atom50-atom42*atom311-atom301*atom49;
_MQ[76] = -atom343;
_MQ[77] = -atom311;
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
_MQ[96] = -atom4174;
_MQ[97] = -atom4182;
_MQ[98] = -atom4190;
_MQ[99] = -atom343;
_MQ[100] = -atom39*( atom39*IyyP+IxyP*atom40)-( IxxP*atom40+atom39*IxyP)*atom40;
_MQ[101] = -atom320;
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
_MQ[120] = -atom4148;
_MQ[121] = -atom4157;
_MQ[122] = -atom4166;
_MQ[123] = -atom311;
_MQ[124] = -atom320;
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
_MQ[150] = -atom81*( atom81*Ixx1+Ixz1*atom82)-atom82*( atom82*Izz1+atom81*Ixz1);
_MQ[151] = 0.0;
_MQ[152] = 0.0;
_MQ[153] = 0.0;
_MQ[154] = 0.0;
_MQ[155] = 0.0;
_MQ[156] = -atom653;
_MQ[157] = 0.0;
_MQ[158] = 0.0;
_MQ[159] = 0.0;
_MQ[160] = 0.0;
_MQ[161] = 0.0;
_MQ[162] = -atom4373;
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
_MQ[175] = -atom106*( atom105*Ixz2+atom106*Izz2)-atom105*( atom105*Ixx2+atom106*Ixz2);
_MQ[176] = 0.0;
_MQ[177] = 0.0;
_MQ[178] = 0.0;
_MQ[179] = 0.0;
_MQ[180] = 0.0;
_MQ[181] = -atom767;
_MQ[182] = 0.0;
_MQ[183] = 0.0;
_MQ[184] = 0.0;
_MQ[185] = 0.0;
_MQ[186] = 0.0;
_MQ[187] = -atom4511;
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
_MQ[200] = -atom129*( atom129*Ixx3+Ixz3*atom130)-atom130*( atom129*Ixz3+atom130*Izz3);
_MQ[201] = 0.0;
_MQ[202] = 0.0;
_MQ[203] = 0.0;
_MQ[204] = 0.0;
_MQ[205] = 0.0;
_MQ[206] = -atom881;
_MQ[207] = 0.0;
_MQ[208] = 0.0;
_MQ[209] = 0.0;
_MQ[210] = 0.0;
_MQ[211] = 0.0;
_MQ[212] = -atom4649;
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
_MQ[225] = -atom169*( Ixx4*atom169+atom170*Ixz4)-atom170*( atom170*Izz4+Ixz4*atom169);
_MQ[226] = 0.0;
_MQ[227] = 0.0;
_MQ[228] = 0.0;
_MQ[229] = 0.0;
_MQ[230] = 0.0;
_MQ[231] = -atom1005;
_MQ[232] = 0.0;
_MQ[233] = 0.0;
_MQ[234] = 0.0;
_MQ[235] = 0.0;
_MQ[236] = 0.0;
_MQ[237] = -atom4800;
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
_MQ[250] = -atom209*( atom209*Ixx5+atom210*Ixz5)-atom210*( atom210*Izz5+atom209*Ixz5);
_MQ[251] = 0.0;
_MQ[252] = 0.0;
_MQ[253] = 0.0;
_MQ[254] = 0.0;
_MQ[255] = 0.0;
_MQ[256] = -atom1129;
_MQ[257] = 0.0;
_MQ[258] = 0.0;
_MQ[259] = 0.0;
_MQ[260] = 0.0;
_MQ[261] = 0.0;
_MQ[262] = -atom4951;
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
_MQ[275] = -( atom253*Izz6+atom252*Ixz6)*atom253-atom252*( atom252*Ixx6+Ixz6*atom253);
_MQ[276] = 0.0;
_MQ[277] = 0.0;
_MQ[278] = 0.0;
_MQ[279] = 0.0;
_MQ[280] = 0.0;
_MQ[281] = -atom1253;
_MQ[282] = 0.0;
_MQ[283] = 0.0;
_MQ[284] = 0.0;
_MQ[285] = 0.0;
_MQ[286] = 0.0;
_MQ[287] = -atom5102;
_MQ[288] = 0.0;
_MQ[289] = 0.0;
_MQ[290] = 0.0;
_MQ[291] = 0.0;
_MQ[292] = 0.0;
_MQ[293] = 0.0;
_MQ[294] = -atom653;
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
_MQ[306] = -atom4367;
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
_MQ[319] = -atom767;
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
_MQ[331] = -atom4505;
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
_MQ[344] = -atom881;
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
_MQ[356] = -atom4643;
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
_MQ[369] = -atom1005;
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
_MQ[381] = -atom4794;
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
_MQ[394] = -atom1129;
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
_MQ[406] = -atom4945;
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
_MQ[419] = -atom1253;
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
_MQ[431] = -atom5096;
_MQ[432] = 0.0;
_MQ[433] = 0.0;
_MQ[434] = 0.0;
_MQ[435] = 0.0;
_MQ[436] = 0.0;
_MQ[437] = 0.0;
_MQ[438] = -atom4373;
_MQ[439] = 0.0;
_MQ[440] = 0.0;
_MQ[441] = 0.0;
_MQ[442] = 0.0;
_MQ[443] = 0.0;
_MQ[444] = -atom4367;
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
_MQ[463] = -atom4511;
_MQ[464] = 0.0;
_MQ[465] = 0.0;
_MQ[466] = 0.0;
_MQ[467] = 0.0;
_MQ[468] = 0.0;
_MQ[469] = -atom4505;
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
_MQ[488] = -atom4649;
_MQ[489] = 0.0;
_MQ[490] = 0.0;
_MQ[491] = 0.0;
_MQ[492] = 0.0;
_MQ[493] = 0.0;
_MQ[494] = -atom4643;
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
_MQ[513] = -atom4800;
_MQ[514] = 0.0;
_MQ[515] = 0.0;
_MQ[516] = 0.0;
_MQ[517] = 0.0;
_MQ[518] = 0.0;
_MQ[519] = -atom4794;
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
_MQ[538] = -atom4951;
_MQ[539] = 0.0;
_MQ[540] = 0.0;
_MQ[541] = 0.0;
_MQ[542] = 0.0;
_MQ[543] = 0.0;
_MQ[544] = -atom4945;
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
_MQ[563] = -atom5102;
_MQ[564] = 0.0;
_MQ[565] = 0.0;
_MQ[566] = 0.0;
_MQ[567] = 0.0;
_MQ[568] = 0.0;
_MQ[569] = -atom5096;
_MQ[570] = 0.0;
_MQ[571] = 0.0;
_MQ[572] = 0.0;
_MQ[573] = 0.0;
_MQ[574] = 0.0;
_MQ[575] = -m6;
_MQ[576] = -( atom4226*atom4138-atom4223*atom4139)*mxP-( atom4135*atom4223-atom4220*atom4138)*mzP-( atom77*atom1493+atom72*atom1490)*da+myP*( atom4135*atom4226-atom4220*atom4139)+dB*( atom77*atom4193-atom72*atom4194);
_MQ[577] =  atom67*atom1490*da+myP*( atom4235*atom4135-atom4139*atom4229)-mzP*( atom4135*atom4232-atom4229*atom4138)-( atom4235*atom4138-atom4232*atom4139)*mxP+dB*( atom67*atom4194-atom77*atom293);
_MQ[578] =  g*mP-dB*( atom67*atom4193-atom72*atom293)-( atom4238*atom4139-atom4135*atom4244)*myP+( atom4241*atom4139-atom4244*atom4138)*mxP+atom67*da*atom1493+( atom4238*atom4138-atom4135*atom4241)*mzP;
_MQ[579] =  atom42*atom4350-atom49*atom5259-atom42*atom1497+atom49*atom4348+atom50*atom4349-atom5262*atom50;
_MQ[580] = -atom5259*atom40-atom5262*atom39+atom39*atom4349+atom4348*atom40;
_MQ[581] = -atom1497+atom4350;
_MQ[582] = -atom82*( atom82*atom102+atom86*atom103)+( ( Ixy1*atom3157-Ixx1*dB1)*atom3157+atom3204*Izz1+atom3163*( atom4464+atom4453)-( Ixy1*dB1-Iyy1*atom3157)*dB1+Ixz1*atom3164)*atom82-atom81*( atom81*atom102+atom103*atom85)+atom81*( ( atom4453+atom4452)*atom3157+Ixx1*atom3164-atom3163*( atom3163*Iyz1+Izz1*dB1)+( atom3163*Iyy1+dB1*Iyz1)*dB1+Ixz1*atom3204);
_MQ[583] =  atom106*( Ixz2*atom3244+Izz2*atom3284-( Ixx2*dB2-Ixy2*atom3239)*atom3239-( Ixy2*dB2-atom3239*Iyy2)*dB2+( atom4602+atom4591)*atom3243)+atom105*( Ixz2*atom3284-atom3243*( atom3243*Iyz2+Izz2*dB2)+( atom3243*Iyy2+dB2*Iyz2)*dB2+Ixx2*atom3244+( atom4590+atom4591)*atom3239)-atom106*( atom106*atom126+atom110*atom127)-atom105*( atom105*atom126+atom127*atom109);
_MQ[584] =  atom129*( atom2642*Ixz3+atom2587*Ixx3-atom2586*( Iyz3*atom2586+dB3*Izz3)+( atom4741+atom4742)*atom2592+( Iyy3*atom2586+Iyz3*dB3)*dB3)+atom130*( dB3*( Iyy3*atom2592-dB3*Ixy3)+atom2586*( atom4753+atom4742)+atom2587*Ixz3+atom2642*Izz3-( Ixx3*dB3-Ixy3*atom2592)*atom2592)-atom129*( atom139*atom166+atom167*atom145)-( atom148*atom167+atom142*atom166)*atom130;
_MQ[585] =  ( Ixx4*atom2741-( dB4*Izz4+Iyz4*atom2740)*atom2740+Ixz4*atom2796+( atom4892+atom4893)*atom2747+dB4*( Iyz4*dB4+Iyy4*atom2740))*atom169-( atom179*atom206+atom207*atom185)*atom169-atom170*( atom182*atom206+atom188*atom207)+atom170*( Izz4*atom2796+( atom2747*Ixy4-Ixx4*dB4)*atom2747+Ixz4*atom2741-dB4*( dB4*Ixy4-Iyy4*atom2747)+( atom4904+atom4893)*atom2740);
_MQ[586] = -atom210*( atom250*atom231+atom249*atom225)+atom210*( Ixz5*atom2902+( atom5055+atom5044)*atom2901+atom2955*Izz5+dB5*( Iyy5*atom2890-dB5*Ixy5)-atom2890*( dB5*Ixx5-atom2890*Ixy5))-atom209*( atom250*atom228+atom222*atom249)+atom209*( ( Iyy5*atom2901+Iyz5*dB5)*dB5-( dB5*Izz5+Iyz5*atom2901)*atom2901+atom2890*( atom5043+atom5044)+Ixz5*atom2955+Ixx5*atom2902);
_MQ[587] = -( atom262*atom289+atom268*atom290)*atom252+( Ixz6*atom3054+( Ixy6*atom3045-dB6*Ixx6)*atom3045+atom3108*Izz6+atom3053*( atom5206+atom5195)-dB6*( Ixy6*dB6-Iyy6*atom3045))*atom253+( ( atom5195+atom5194)*atom3045+dB6*( Iyz6*dB6+Iyy6*atom3053)+atom3054*Ixx6-( dB6*Izz6+Iyz6*atom3053)*atom3053+atom3108*Ixz6)*atom252-( atom271*atom290+atom265*atom289)*atom253;
_MQ[588] = -( atom3163*Ixx1+Ixz1*atom3157)*atom3157+atom3163*( Izz1*atom3157+atom3163*Ixz1)+dB1*( atom4464-atom4452)+Ixy1*atom3164+atom3204*Iyz1-atom83*atom103;
_MQ[589] = -( Ixz2*atom3239+atom3243*Ixx2)*atom3239-dB2*( atom4590-atom4602)+Iyz2*atom3284-atom107*atom127+Ixy2*atom3244+atom3243*( atom3243*Ixz2+Izz2*atom3239);
_MQ[590] =  atom2586*( Izz3*atom2592+Ixz3*atom2586)-atom133*atom166-atom135*atom167+Iyz3*atom2642+atom2587*Ixy3-( Ixz3*atom2592+atom2586*Ixx3)*atom2592-dB3*( atom4741-atom4753);
_MQ[591] = -( Ixx4*atom2740+Ixz4*atom2747)*atom2747+Iyz4*atom2796+( atom2747*Izz4+Ixz4*atom2740)*atom2740-atom175*atom207+atom2741*Ixy4-atom173*atom206-dB4*( atom4892-atom4904);
_MQ[592] =  ( Ixz5*atom2901+atom2890*Izz5)*atom2901-( Ixx5*atom2901+Ixz5*atom2890)*atom2890+Iyz5*atom2955+atom2902*Ixy5-atom249*atom216-atom250*atom218-dB5*( atom5043-atom5055);
_MQ[593] =  atom3108*Iyz6+atom3053*( atom3045*Izz6+atom3053*Ixz6)-atom289*atom256-atom258*atom290+Ixy6*atom3054+dB6*( atom5206-atom5194)-( Ixz6*atom3045+atom3053*Ixx6)*atom3045;
_MQ[594] =  ( atom4396*dB1-atom4399*atom3157)*mz1-mx1*( atom3163*atom4399+atom4402*dB1)+da1*atom84*dB1*atom91-Fs1+g*m1+( atom3163*atom4396+atom4402*atom3157)*my1;
_MQ[595] = -Fs2+da2*dB2*atom108*atom115+mz2*( atom4534*dB2-atom4537*atom3239)+g*m2-mx2*( atom3243*atom4537+dB2*atom4540)+( atom4540*atom3239+atom3243*atom4534)*my2;
_MQ[596] =  da3*( atom134*atom160*dB3-atom155*dB3*atom136)-mx3*( atom2586*atom4688+dB3*atom4691)+( atom2592*atom4691+atom4685*atom2586)*my3-mz3*( atom2592*atom4688-atom4685*dB3)+g*m3-Fs3;
_MQ[597] =  ( atom4842*atom2747+atom2740*atom4836)*my4+da4*( atom200*dB4*atom174-atom176*dB4*atom195)+g*m4-mx4*( atom4839*atom2740+atom4842*dB4)-mz4*( atom4839*atom2747-dB4*atom4836)-Fs4;
_MQ[598] =  my5*( atom4987*atom2901+atom2890*atom4993)-Fs5+g*m5-( atom4990*atom2890-atom4987*dB5)*mz5-( atom4990*atom2901+dB5*atom4993)*mx5+( atom243*dB5*atom217-atom238*dB5*atom219)*da5;
_MQ[599] = -( atom5144*dB6+atom3053*atom5141)*mx6+mz6*( dB6*atom5138-atom5141*atom3045)+my6*( atom3053*atom5138+atom5144*atom3045)-Fs6-( dB6*atom259*atom278-dB6*atom257*atom283)*da6+g*m6;

return _MQ;
}

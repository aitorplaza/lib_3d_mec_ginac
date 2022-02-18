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
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define lambda3 unknowns[ 2 ]
#define lambda4 unknowns[ 3 ]
#define lambda5 unknowns[ 4 ]
#define lambda6 unknowns[ 5 ]

double atom57;
double atom59;
double atom36;
double atom58;
double atom35;
double atom3607;
double atom3618;
double atom3791;
double atom3610;
double atom3617;
double atom3792;
double atom3845;
double atom3841;
double atom3842;
double atom3931;
double atom81;
double atom114;
double atom115;
double atom4205;
double atom95;
double atom4223;
double atom80;
double atom4193;
double atom4194;
double atom4195;
double atom4197;
double atom94;
double atom4213;
double atom4202;
double atom4204;
double atom4219;
double atom4326;
double atom4198;
double atom4221;
double atom4210;
double atom4216;
double atom4321;
double atom4207;
double atom4200;
double atom4330;
double atom2441;
double atom2439;
double atom4235;
double atom4225;
double atom4224;
double atom4230;
double atom4256;
double atom3851;
double atom4253;
double atom4250;
double atom4277;
double atom4280;
double atom532;
double atom3604;
double atom3603;
double atom271;
double atom273;
double atom3616;
double atom3613;
double atom605;
double atom603;
double atom3848;
double atom3861;
double atom3858;
double atom3864;
double atom3815;
double atom3817;
double atom3917;
double atom3838;
double atom3810;
double atom3811;
double atom3812;
double atom3814;
double atom3827;
double atom152;
double atom153;
double atom4697;
double atom4699;
double atom4705;
double atom4715;
double atom4702;
double atom4698;
double atom4694;
double atom4710;
double atom133;
double atom4736;
double atom4733;
double atom4730;
double atom4760;
double atom130;
double atom4757;
double atom4663;
double atom4670;
double atom4661;
double atom4672;
double atom4684;
double atom4665;
double atom4662;
double atom4678;
double atom4666;
double atom4689;
double atom4816;
double atom4681;
double atom4687;
double atom4673;
double atom4691;
double atom4821;
double atom4675;
double atom4668;
double atom4825;
double atom4718;
double atom4241;
double atom4742;
double atom4721;
double atom4739;
double atom4763;
double atom4766;
double atom4745;
double atom4782;
double atom3853;
double atom4259;
double atom4238;
double atom4262;
double atom4283;
double atom4286;
double atom4265;
double atom4300;
double atom3822;
double atom3840;
double atom3830;
double atom3852;
double atom3873;
double atom3870;
double atom3867;
double atom3888;
double atom3934;
double atom3627;
double atom610;
double atom3915;
double atom4338;
double atom4835;
double atom3937;
double atom3855;
double atom3854;
double atom3882;
double atom3879;
double atom3876;
double atom4244;
double atom4271;
double atom4247;
double atom4268;
double atom4292;
double atom4289;
double atom4274;
double atom4727;
double atom4724;
double atom4754;
double atom4748;
double atom4751;
double atom4769;
double atom4772;
double atom24;
double atom61;
double atom25;
double atom60;
double atom84;
double atom121;
double atom87;
double atom118;
double atom156;
double atom159;
double atom176;
double atom63;
double atom62;
double atom90;
double atom188;
double atom127;
double atom124;
double atom93;
double atom165;
double atom162;
double atom181;
double atom187;
double atom5319;
double atom5316;
double atom5313;
double atom138;
double atom150;
double atom143;
double atom149;
double atom5277;
double atom5280;
double atom5283;
double atom100;
double atom112;
double atom105;
double atom111;
double atom5253;
double atom3793;
double atom3794;
double atom4391;
double atom4924;
double atom571;
double atom4032;
double atom4033;
double atom4190;
double atom4036;
double atom4035;
double atom4189;
double atom3808;
double atom4658;
double atom5112;
double atom4392;
double atom4560;
double atom4475;
double atom4474;
double atom4655;
double atom4928;
double atom5119;
double atom894;
double atom533;
double atom898;
double atom888;
double atom891;
double atom897;
double atom896;
double atom902;
double atom927;
double atom540;
double atom895;
double atom901;
double atom911;
double atom922;
double atom930;
double atom4077;
double atom917;
double atom537;
double atom912;
double atom924;
double atom4075;
double atom5090;
double atom171;
double atom168;
double atom186;
double atom932;
double atom4078;
double atom5087;
double atom5084;
double atom4191;
double atom4659;
double atom5182;
double atom5181;
double atom5180;
double atom2286;
double atom2291;
double atom2285;
double atom1501;
double atom2288;
double atom2297;
double atom2426;
double atom2446;
double atom4953;
double atom1502;
double atom2290;
double atom2298;
double atom2294;
double atom2304;
double atom2301;
double atom2428;
double atom2449;
double atom2430;
double atom2431;
double atom2434;
double atom2436;
double atom2452;
double atom2438;
double atom5002;
double atom2459;
double atom4941;
double atom2456;
double atom4993;
double atom4932;
double atom4984;
double atom4472;
double atom5025;
double atom5028;
double atom5031;
double atom5197;
double atom5023;
double atom4464;
double atom5017;
double atom5020;
double atom5196;
double atom5036;
double atom4477;
double atom5033;
double atom5039;
double atom4108;
double atom4555;
double atom4535;
double atom148;
double atom4532;
double atom4529;
double atom4622;
double atom4621;
double atom4623;
double atom4471;
double atom4468;
double atom4030;
double atom4465;
double atom1636;
double atom1639;
double atom1645;
double atom953;
double atom1506;
double atom1635;
double atom1642;
double atom4410;
double atom952;
double atom1504;
double atom1507;
double atom1510;
double atom1513;
double atom4450;
double atom4401;
double atom1648;
double atom4443;
double atom4395;
double atom4436;
double atom4632;
double atom4473;
double atom4476;
double atom4633;
double atom4481;
double atom4031;
double atom4478;
double atom4484;
double atom39;
double atom534;
double atom546;
double atom76;
double atom573;
double atom535;
double atom38;
double atom557;
double atom3684;
double atom40;
double atom552;
double atom572;
double atom37;
double atom547;
double atom3681;
double atom3701;
double atom3708;
double atom3702;
double atom3705;
double atom68;
double atom73;
double atom3687;
double atom3779;
double atom495;
double atom3516;
double atom568;
double atom3728;
double atom3731;
double atom3727;
double atom3734;
double atom841;
double atom3597;
double atom110;
double atom1079;
double atom3979;
double atom957;
double atom4011;
double atom1080;
double atom3976;
double atom955;
double atom4006;
double atom4037;
double atom4038;
double atom4041;
double atom3985;
double atom4016;
double atom4170;
double atom4034;
double atom4169;
double atom4105;
double atom4087;
double atom4084;
double atom4081;
double atom3824;
double atom3821;
double atom3819;
double atom3836;
double atom3833;
double atom4165;
double atom5345;
double atom5388;
double atom5356;
double atom3940;
double atom3894;
double atom3632;
double atom4308;
double atom4347;
double atom4350;
double atom4795;
double atom4853;
double atom4848;
double atom4843;
double atom4858;
double atom4808;
double atom3943;
double atom4316;
double atom3900;
double atom4344;
double atom4861;
double atom151;
double atom3777;
double atom4164;
double atom4631;
double atom5192;
double atom5230;
double atom113;
double atom5250;
double atom5291;
double atom189;
double atom5329;
double atom5349;
double atom5355;
double atom5392;
double atom3946;
double atom4870;
double atom4905;
double atom4906;
double atom4907;
double atom4908;
double atom4909;
double atom4911;
double atom4912;
double atom4913;
double atom4914;
double atom4916;
double atom4917;
double atom4918;
double atom4920;

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

atom57 =  a3+a2;
atom59 = sin(atom57);
atom36 = sin(a2);
atom58 = cos(atom57);
atom35 = cos(a2);
atom3607 =  atom59*atom36+atom58*atom35;
atom3618 = atom3607*d3;
atom3791 =  d4+atom3618;
atom3610 =  atom58*atom36-atom35*atom59;
atom3617 = -atom3610*d3;
atom3792 = -atom3617-r4;
atom3845 =  atom58*atom3791-atom59*atom3792;
atom3841 = -atom58*r3;
atom3842 = r3*atom59;
atom3931 =  (atom3842*atom3842)+(atom3845*atom3845)+(atom3841*atom3841);
atom81 = sin(a4);
atom114 = cos(a5);
atom115 = sin(a5);
atom4205 = Ixz5*atom115;
atom95 = atom81*atom59;
atom4223 =  atom114*Izz5+atom4205;
atom80 = cos(a4);
atom4193 = -atom115*Ixy5;
atom4194 =  atom114*Ixx5+atom4193;
atom4195 = atom114*Ixy5;
atom4197 =  atom4195-atom115*Iyy5;
atom94 = -atom59*atom80;
atom4213 =  atom114*atom4197+atom115*atom4194;
atom4202 =  atom4195+atom115*Ixx5;
atom4204 =  atom114*Iyy5-atom4193;
atom4219 =  atom114*atom4204+atom115*atom4202;
atom4326 = -atom58*atom4219+atom94*atom4213+atom95*atom4223;
atom4198 = atom114*Ixz5;
atom4221 = -Izz5*atom115+atom4198;
atom4210 = -atom115*atom4197+atom114*atom4194;
atom4216 = -atom115*atom4204+atom114*atom4202;
atom4321 =  atom95*atom4221+atom94*atom4210-atom58*atom4216;
atom4207 =  atom114*Iyz5+atom4205;
atom4200 = -atom115*Iyz5+atom4198;
atom4330 =  atom4200*atom94-atom58*atom4207+Izz5*atom95;
atom2441 = atom115*atom80;
atom2439 = atom81*atom115;
atom4235 = -atom2439*atom3845+atom114*atom3842-atom3841*atom2441;
atom4225 = atom81*atom114;
atom4224 = atom114*atom80;
atom4230 =  atom115*atom3842+atom4224*atom3841+atom4225*atom3845;
atom4256 = -atom4230*my5+mx5*atom4235;
atom3851 =  atom80*atom3845-atom81*atom3841;
atom4253 =  mz5*atom4230-mx5*atom3851;
atom4250 = -mz5*atom4235+atom3851*my5;
atom4277 = -atom115*atom4253+atom114*atom4250;
atom4280 =  atom114*atom4253+atom115*atom4250;
atom532 = atom35*d3;
atom3604 = r3*atom36;
atom3603 = -atom35*r3;
atom271 = -atom35*Ixy2;
atom273 = -atom36*Ixy2;
atom3616 =  atom3607*atom3604+atom3603*atom3610;
atom3613 = -atom3610*atom3604+atom3603*atom3607;
atom605 = -atom59*Ixy3;
atom603 = -atom58*Ixy3;
atom3848 =  atom3841*atom80+atom81*atom3845;
atom3861 =  atom3848*mz4+atom3842*mx4;
atom3858 = -mz4*atom3851-my4*atom3842;
atom3864 =  mx4*atom3851-my4*atom3848;
atom3815 = Ixz4*atom80;
atom3817 = -atom81*Iyz4+atom3815;
atom3917 = -atom59*atom3817+atom58*Izz4;
atom3838 =  atom3815-atom81*Izz4;
atom3810 = -atom81*Ixy4;
atom3811 =  atom3810+Ixx4*atom80;
atom3812 = Ixy4*atom80;
atom3814 = -atom81*Iyy4+atom3812;
atom3827 =  atom3811*atom80-atom81*atom3814;
atom152 = cos(a6);
atom153 = sin(a6);
atom4697 = -atom81*atom152-atom4224*atom153;
atom4699 = -atom115*atom153;
atom4705 =  atom152*atom80-atom153*atom4225;
atom4715 =  atom3841*atom4697+atom4699*atom3842+atom4705*atom3845;
atom4702 =  atom152*atom4225+atom153*atom80;
atom4698 = atom115*atom152;
atom4694 =  atom4224*atom152-atom81*atom153;
atom4710 =  atom3841*atom4694+atom3842*atom4698+atom3845*atom4702;
atom133 = -atom58*atom114-atom115*atom94;
atom4736 =  atom4715*mx6-my6*atom4710;
atom4733 =  mz6*atom4710+atom4235*mx6;
atom4730 = -atom4715*mz6-my6*atom4235;
atom4760 =  atom152*atom4733+atom153*atom4730;
atom130 = -atom58*atom115+atom114*atom94;
atom4757 =  atom152*atom4730-atom4733*atom153;
atom4663 = Ixy6*atom152;
atom4670 =  atom4663+atom153*Ixx6;
atom4661 = -Ixy6*atom153;
atom4672 =  atom152*Iyy6-atom4661;
atom4684 = -atom4672*atom153+atom152*atom4670;
atom4665 =  atom4663-Iyy6*atom153;
atom4662 =  atom152*Ixx6+atom4661;
atom4678 = -atom153*atom4665+atom152*atom4662;
atom4666 = Ixz6*atom152;
atom4689 =  atom4666-Izz6*atom153;
atom4816 =  atom130*atom4678+atom95*atom4684-atom133*atom4689;
atom4681 =  atom152*atom4665+atom153*atom4662;
atom4687 =  atom4672*atom152+atom153*atom4670;
atom4673 = Ixz6*atom153;
atom4691 =  Izz6*atom152+atom4673;
atom4821 = -atom133*atom4691+atom130*atom4681+atom4687*atom95;
atom4675 =  atom152*Iyz6+atom4673;
atom4668 =  atom4666-atom153*Iyz6;
atom4825 = -atom133*Izz6+atom95*atom4675+atom130*atom4668;
atom4718 =  atom3791*atom4698-atom3792*atom4694;
atom4241 =  atom114*atom3791+atom3792*atom2441;
atom4742 =  mz6*atom4718+atom4241*mx6;
atom4721 =  atom4699*atom3791-atom3792*atom4697;
atom4739 = -my6*atom4241-mz6*atom4721;
atom4763 =  atom152*atom4739-atom4742*atom153;
atom4766 =  atom4742*atom152+atom4739*atom153;
atom4745 = -my6*atom4718+atom4721*mx6;
atom4782 =  atom4760*atom80+atom4736*atom2439+atom4757*atom4225;
atom3853 = atom81*atom3792;
atom4259 =  atom3853*my5-mz5*atom4241;
atom4238 =  atom115*atom3791-atom4224*atom3792;
atom4262 =  mz5*atom4238-atom3853*mx5;
atom4283 = -atom115*atom4262+atom114*atom4259;
atom4286 =  atom114*atom4262+atom115*atom4259;
atom4265 =  atom4241*mx5-atom4238*my5;
atom4300 =  atom4256*atom80+atom81*atom4277;
atom3822 = atom81*Ixz4;
atom3840 =  Izz4*atom80+atom3822;
atom3830 =  atom80*atom3814+atom81*atom3811;
atom3852 = -atom3792*atom80;
atom3873 =  atom3853*mx4-my4*atom3852;
atom3870 =  atom3791*mx4+mz4*atom3852;
atom3867 = -atom3853*mz4-my4*atom3791;
atom3888 =  atom3861*atom80+atom81*atom3858;
atom3934 =  atom3791*atom3842-atom3792*atom3841;
atom3627 =  atom3616*mx3-my3*atom3613;
atom610 = -Ixz3*atom59-atom58*Iyz3;
atom3915 = -atom59*atom3830+atom3840*atom58;
atom4338 =  atom4330*atom80+atom81*atom4321;
atom4835 =  atom4816*atom4225+atom2439*atom4825+atom4821*atom80;
atom3937 =  atom3841*r4+d4*atom3842;
atom3855 = -atom81*r4;
atom3854 = r4*atom80;
atom3882 =  atom3855*mx4-my4*atom3854;
atom3879 =  d4*mx4+mz4*atom3854;
atom3876 = -my4*d4-atom3855*mz4;
atom4244 =  atom115*d4+atom4224*r4;
atom4271 =  mz5*atom4244-atom3855*mx5;
atom4247 =  atom114*d4-r4*atom2441;
atom4268 = -mz5*atom4247+atom3855*my5;
atom4292 =  atom4268*atom115+atom4271*atom114;
atom4289 = -atom4271*atom115+atom4268*atom114;
atom4274 = -atom4244*my5+mx5*atom4247;
atom4727 =  atom4699*d4+r4*atom4697;
atom4724 =  r4*atom4694+d4*atom4698;
atom4754 = -my6*atom4724+atom4727*mx6;
atom4748 = -my6*atom4247-mz6*atom4727;
atom4751 =  mx6*atom4247+mz6*atom4724;
atom4769 =  atom152*atom4748-atom4751*atom153;
atom4772 =  atom152*atom4751+atom153*atom4748;
atom24 = cos(a1);
atom61 = -atom59*atom24;
atom25 = sin(a1);
atom60 = atom58*atom24;
atom84 =  atom60*atom80-atom81*atom25;
atom121 = -atom84*atom115+atom61*atom114;
atom87 = -atom80*atom25-atom81*atom60;
atom118 =  atom61*atom115+atom114*atom84;
atom156 =  atom152*atom118+atom87*atom153;
atom159 = -atom118*atom153+atom87*atom152;
atom176 = -atom121*mz6+atom156*mx6+my6*atom159;
atom63 = -atom59*atom25;
atom62 = atom58*atom25;
atom90 =  atom80*atom62+atom81*atom24;
atom188 = atom176*g;
atom127 = -atom90*atom115+atom114*atom63;
atom124 =  atom115*atom63+atom114*atom90;
atom93 = -atom81*atom62+atom24*atom80;
atom165 =  atom93*atom152-atom124*atom153;
atom162 =  atom93*atom153+atom124*atom152;
atom181 =  my6*atom165+atom162*mx6-atom127*mz6;
atom187 = -atom181*g;
atom5319 = -atom188*atom127-atom187*atom121;
atom5316 =  atom187*atom87+atom188*atom93;
atom5313 =  atom187*atom118+atom124*atom188;
atom138 =  atom121*my5+mz5*atom87+atom118*mx5;
atom150 = atom138*g;
atom143 =  atom127*my5+atom93*mz5+atom124*mx5;
atom149 = -g*atom143;
atom5277 =  atom150*atom90+atom84*atom149;
atom5280 =  atom61*atom149+atom150*atom63;
atom5283 =  atom150*atom93+atom87*atom149;
atom100 = -atom61*mz4+atom84*mx4+my4*atom87;
atom112 = atom100*g;
atom105 =  atom90*mx4+my4*atom93-mz4*atom63;
atom111 = -atom105*g;
atom5253 = -atom63*atom112-atom61*atom111;
atom3793 = -atom59*da1;
atom3794 = -atom58*da1;
atom4391 = -atom3794*atom80;
atom4924 = -atom3793*atom115-atom114*atom4391;
atom571 =  da3+da2;
atom4032 = atom571*atom80;
atom4033 = atom81*atom3793;
atom4190 =  atom4032-atom4033;
atom4036 = -atom3793*atom80;
atom4035 = atom81*atom571;
atom4189 = -atom4036+atom4035;
atom3808 = -atom3794+da4;
atom4658 =  atom114*atom3808+atom115*atom4189;
atom5112 = -da5*atom4658+atom114*da4*atom4190+da3*atom4924+atom4924*da2;
atom4392 = atom81*atom3794;
atom4560 = -atom4392*da2-atom4392*da3-da4*atom4189;
atom4475 = -atom114*atom4189;
atom4474 = -atom115*atom3808;
atom4655 = -atom4475+atom4474;
atom4928 = -atom115*atom4391+atom114*atom3793;
atom5119 =  da4*atom115*atom4190+da3*atom4928+da5*atom4655+da2*atom4928;
atom894 =  atom59*d4-atom58*r4;
atom533 = atom36*d3;
atom898 =  atom894+atom533;
atom888 = -da2+atom571;
atom891 =  atom58*d4+atom59*r4;
atom897 =  atom532+atom891;
atom896 = atom888*atom891;
atom902 =  atom896+da2*atom897;
atom927 = -atom902*atom25-atom898*da1*atom24;
atom540 = r3*atom24;
atom895 = atom888*atom894;
atom901 = -da2*atom898-atom895;
atom911 = -da1*( atom540+atom25*atom897)+atom901*atom24;
atom922 = -atom896-atom891*da2;
atom930 = -atom894*da1*atom24+atom922*atom25;
atom4077 =  atom927*da2+atom911*da1+da3*atom930;
atom917 =  atom898*da1*atom25-atom902*atom24;
atom537 = -r3*atom25;
atom912 =  atom901*atom25+( atom537+atom24*atom897)*da1;
atom924 =  atom24*atom922+atom894*da1*atom25;
atom4075 = -atom912*da1+atom924*da3+da2*atom917;
atom5090 = -atom181*atom4075+atom176*atom4077;
atom171 =  atom95*atom152-atom130*atom153;
atom168 =  atom130*atom152+atom95*atom153;
atom186 =  atom168*mx6+my6*atom171-atom133*mz6;
atom932 = -atom894*da2-atom895;
atom4078 = -atom901*da2-atom932*da3;
atom5087 =  atom186*atom4075-atom176*atom4078;
atom5084 = -atom186*atom4077+atom181*atom4078;
atom4191 =  da5+atom4190;
atom4659 =  da6+atom4658;
atom5182 =  atom4659*( atom4655*atom4675-atom4668*atom4191)-atom133*atom5090-atom127*atom5087+atom4560*atom4691-atom4655*( atom4191*atom4678-atom4655*atom4684)-atom121*atom5084+atom4689*atom5112-( atom4681*atom4191-atom4687*atom4655)*atom4191+Izz6*atom5119;
atom5181 = -atom4659*( Izz6*atom4655-atom4659*atom4668)+atom5090*atom171+atom5087*atom165+atom5112*atom4684+( atom4659*atom4681-atom4655*atom4691)*atom4191+atom5119*atom4675+atom4687*atom4560+atom5084*atom159+atom4655*( atom4659*atom4678-atom4655*atom4689);
atom5180 =  ( atom4691*atom4191-atom4659*atom4687)*atom4191+atom162*atom5087+atom168*atom5090+atom4655*( atom4689*atom4191-atom4659*atom4684)+atom5112*atom4678+atom5084*atom156+atom5119*atom4668+atom4560*atom4681+atom4659*( Izz6*atom4191-atom4659*atom4675);
atom2286 = -atom114*da6;
atom2291 =  da4-atom2286;
atom2285 = da6*atom115;
atom1501 = -atom81*da5;
atom2288 =  atom1501+atom2285*atom80;
atom2297 =  atom59*atom2288-atom58*atom2291;
atom2426 = -atom24*atom2297;
atom2446 = -atom2297*atom25;
atom4953 =  atom176*atom2446-atom181*atom2426;
atom1502 = da5*atom80;
atom2290 =  atom81*atom2285+atom1502;
atom2298 =  atom571+atom2290;
atom2294 =  atom58*atom2288+atom59*atom2291;
atom2304 =  atom2298*atom24+atom25*atom2294;
atom2301 = -atom2298*atom25+atom24*atom2294;
atom2428 = -atom58*atom2290;
atom2449 =  atom2428*atom25+atom24*atom2288;
atom2430 = -atom2288*atom25+atom24*atom2428;
atom2431 = -atom81*atom2286;
atom2434 = -atom2286*atom80;
atom2436 = -atom2285*atom59+atom58*atom2434;
atom2452 =  atom24*atom2431+atom2436*atom25;
atom2438 =  atom2436*atom24-atom2431*atom25;
atom5002 = -da4*( atom176*atom2449-atom2430*atom181)-( atom932*m6+atom4953)*da3-da1*( atom176*atom2301+atom181*atom2304)+da5*( atom181*atom2438-atom176*atom2452)-da2*( atom901*m6+atom4953);
atom2459 =  atom2434*atom59+atom58*atom2285;
atom4941 =  atom176*atom2294+atom186*atom2426;
atom2456 = -atom59*atom2290;
atom4993 =  da2*( atom927*m6-atom4941)-( atom4941-m6*atom930)*da3+( atom911*m6+atom186*atom2304)*da1-da5*( atom176*atom2459+atom186*atom2438)-da4*( atom176*atom2456+atom2430*atom186);
atom4932 = -atom2446*atom186-atom181*atom2294;
atom4984 =  da1*( atom186*atom2301-atom912*m6)-( atom4932-atom924*m6)*da3+( atom2459*atom181+atom2452*atom186)*da5+da4*( atom2456*atom181+atom2449*atom186)-da2*( atom4932-m6*atom917);
atom4472 = atom114*atom4191;
atom5025 =  atom4472+atom4699*atom4659;
atom5028 = -atom4659*atom4698-atom114*atom4655;
atom5031 = -atom4699*atom4655+atom4698*atom4191;
atom5197 = -atom58*atom5002+atom4993*atom63+mx6*( atom4659*atom5028-atom5031*atom4191)+( atom5025*atom4191-atom4655*atom5028)*mz6+atom61*atom4984+( atom5031*atom4655-atom4659*atom5025)*my6;
atom5023 = -atom4655*atom4697+atom4694*atom4191;
atom4464 = -atom2441*atom4191;
atom5017 =  atom4659*atom4697+atom4464;
atom5020 =  atom4655*atom2441-atom4659*atom4694;
atom5196 = -atom59*atom5002+atom60*atom4984+atom4993*atom62-( atom5023*atom4191-atom4659*atom5020)*mx6-( atom5020*atom4655-atom4191*atom5017)*mz6+my6*( atom5023*atom4655-atom4659*atom5017);
atom5036 =  atom4655*atom2439-atom4659*atom4702;
atom4477 = -atom2439*atom4191;
atom5033 =  atom4477+atom4659*atom4705;
atom5039 = -atom4705*atom4655+atom4191*atom4702;
atom4108 =  atom3793*da3+atom3793*da2;
atom4555 = -atom4391*da2+da4*atom4190-da3*atom4391;
atom4535 = -atom4075*atom143+atom138*atom4077;
atom148 =  mz5*atom95+atom133*my5+atom130*mx5;
atom4532 =  atom148*atom4075-atom138*atom4078;
atom4529 = -atom148*atom4077+atom4078*atom143;
atom4622 = -atom4219*atom4108+atom121*atom4529+atom127*atom4532+atom4189*( atom4210*atom4191-atom4221*atom4189)-( Izz5*atom4189-atom4200*atom4191)*atom4191+atom133*atom4535+atom4560*atom4207+atom4555*atom4216-atom3808*( atom4213*atom4191-atom4189*atom4223);
atom4621 =  atom4555*atom4210+atom4529*atom118-atom4189*( atom4221*atom3808+atom4216*atom4191)+atom124*atom4532+atom4200*atom4560-( atom4207*atom4191+Izz5*atom3808)*atom4191+atom3808*( atom4219*atom4191+atom4223*atom3808)+atom130*atom4535-atom4213*atom4108;
atom4623 = -atom4223*atom4108+atom93*atom4532+atom4221*atom4555-atom3808*( atom4213*atom3808+atom4219*atom4189)+( atom4189*atom4207+atom4200*atom3808)*atom4191+atom4529*atom87+Izz5*atom4560+atom4189*( atom4189*atom4216+atom3808*atom4210)+atom95*atom4535;
atom4471 =  atom4189*atom2441-atom4224*atom3808;
atom4468 = -atom81*atom4189-atom4224*atom4191;
atom4030 = -atom81*atom3808;
atom4465 =  atom4464+atom4030;
atom1636 = -atom58*atom1502;
atom1639 = -atom1501*atom25+atom1636*atom24;
atom1645 =  atom1501*atom24+atom1636*atom25;
atom953 = -atom58*da4;
atom1506 =  atom1501*atom59+atom953;
atom1635 = -atom24*atom1506;
atom1642 = -atom25*atom1506;
atom4410 =  atom138*atom1642-atom1635*atom143;
atom952 = atom59*da4;
atom1504 =  atom952+atom58*atom1501;
atom1507 =  atom571+atom1502;
atom1510 =  atom24*atom1504-atom1507*atom25;
atom1513 =  atom1504*atom25+atom1507*atom24;
atom4450 = -( atom932*m5+atom4410)*da3-( atom138*atom1645-atom1639*atom143)*da4-da2*( atom901*m5+atom4410)-( atom138*atom1510+atom1513*atom143)*da1;
atom4401 =  atom148*atom1635+atom138*atom1504;
atom1648 = -atom59*atom1502;
atom4443 =  da2*( atom927*m5-atom4401)-da4*( atom138*atom1648+atom148*atom1639)-( atom4401-m5*atom930)*da3+( atom911*m5+atom1513*atom148)*da1;
atom4395 = -atom1504*atom143-atom148*atom1642;
atom4436 =  da4*( atom1648*atom143+atom148*atom1645)+( atom148*atom1510-atom912*m5)*da1+da3*( atom924*m5-atom4395)-da2*( atom4395-m5*atom917);
atom4632 = -atom4450*atom59+mx5*( atom4471*atom3808+atom4468*atom4191)+atom4443*atom62-( atom4468*atom4189+atom4465*atom3808)*mz5-( atom4465*atom4191-atom4471*atom4189)*my5+atom60*atom4436;
atom4473 = -atom115*atom4191;
atom4476 =  atom4475+atom4474;
atom4633 = -( atom4472*atom4191-atom4476*atom4189)*my5-atom58*atom4450+atom63*atom4443+( atom4476*atom3808+atom4473*atom4191)*mx5+atom61*atom4436-mz5*( atom4189*atom4473+atom4472*atom3808);
atom4481 =  atom4189*atom80-atom4191*atom4225;
atom4031 = -atom3808*atom80;
atom4478 = -atom4031+atom4477;
atom4484 = -atom3808*atom4225+atom2439*atom4189;
atom39 = atom35*atom25;
atom534 = da2*atom533;
atom546 = -atom534*atom24-( atom39*d3+atom540)*da1;
atom76 = -my3*atom58-atom59*mx3;
atom573 = atom571*atom24;
atom535 = atom532*da2;
atom38 = -atom36*atom24;
atom557 =  atom38*da1*d3-atom535*atom25;
atom3684 =  da1*( atom76*atom573+m3*atom546)+atom557*m3*da2;
atom40 = -atom36*atom25;
atom552 = -da1*atom40*d3-atom535*atom24;
atom572 = -atom571*atom25;
atom37 = atom35*atom24;
atom547 =  ( atom537+atom37*d3)*da1-atom534*atom25;
atom3681 =  atom552*m3*da2-da1*( atom547*m3-atom76*atom572);
atom3701 = atom571*atom3610;
atom3708 = -atom571*atom3701;
atom3702 = -atom3607*atom571;
atom3705 = atom3702*atom571;
atom68 = -mz3*atom25+my3*atom61+atom60*mx3;
atom73 =  my3*atom63+mx3*atom62+mz3*atom24;
atom3687 = -da1*( atom573*atom73+atom68*atom572)+m3*da2*atom534;
atom3779 =  atom3702*mz3*da1+atom38*atom3681-atom35*atom3687+atom3684*atom40+my3*atom3705+mx3*( (da1*da1)*atom3610-atom3708);
atom495 =  atom36*Iyz2-atom35*Ixz2;
atom3516 =  atom36*( atom273+atom35*Ixx2)-atom35*( atom36*Iyy2+atom271);
atom568 = da2*atom534;
atom3728 =  atom557*da2+da1*atom546;
atom3731 = -atom76*atom3728+atom568*atom73;
atom3727 = -atom547*da1+atom552*da2;
atom3734 =  atom76*atom3727-atom68*atom568;
atom841 = -atom58*Ixz3+atom59*Iyz3;
atom3597 = -atom58*( atom603+atom59*Iyy3)+atom59*( atom605+atom58*Ixx3);
atom110 =  atom94*mx4+atom58*mz4+my4*atom95;
atom1079 = -atom24*atom953;
atom3979 =  atom952*atom100+atom110*atom1079;
atom957 =  atom573+atom952*atom25;
atom4011 = -da2*( atom3979-atom927*m4)+( atom911*m4+atom110*atom957)*da1+da3*( m4*atom930-atom3979);
atom1080 = -atom25*atom953;
atom3976 = -atom952*atom105-atom110*atom1080;
atom955 =  atom572+atom952*atom24;
atom4006 = -da1*( atom912*m4-atom110*atom955)-( atom3976-atom917*m4)*da2-da3*( atom3976-atom924*m4);
atom4037 =  atom4036+atom4035;
atom4038 = atom4031*atom3808;
atom4041 = -atom4030*atom3808;
atom3985 =  atom1080*atom100-atom1079*atom105;
atom4016 = -da3*( atom3985+atom932*m4)-( atom957*atom105+atom955*atom100)*da1-da2*( atom3985+atom901*m4);
atom4170 =  mz4*( (atom3793*atom3793)+(atom571*atom571))+atom63*atom4011-atom58*atom4016-atom3793*atom3808*mx4+atom61*atom4006-my4*atom571*atom3808;
atom4034 =  atom4032+atom4033;
atom4169 =  my4*( atom3793*atom4034+atom4041)-( atom4034*atom571-atom4038)*mx4-atom59*atom4016+( atom571*atom4030-atom3793*atom4031)*mz4+atom4006*atom60+atom4011*atom62;
atom4105 =  atom3794*da2+atom3794*da3;
atom4087 =  atom100*atom4077-atom4075*atom105;
atom4084 = -atom4078*atom100+atom110*atom4075;
atom4081 = -atom110*atom4077+atom4078*atom105;
atom3824 =  Iyz4*atom80+atom3822;
atom3821 = -atom3810+Iyy4*atom80;
atom3819 =  atom81*Ixx4+atom3812;
atom3836 =  atom3821*atom80+atom81*atom3819;
atom3833 =  atom80*atom3819-atom81*atom3821;
atom4165 = -atom4084*atom63+atom4105*atom3838+Izz4*atom4108+atom3793*( atom3833*atom3793-atom3827*atom571)-atom61*atom4081+atom4087*atom58-( atom571*atom3830-atom3793*atom3836)*atom571+( atom3793*atom3824-atom571*atom3817)*atom3808;
atom5345 = atom58*Ma4;
atom5388 = -Ma6*atom115;
atom5356 = atom114*Ma6;
atom3940 =  (atom3791*atom3791)+(atom3792*atom3792);
atom3894 =  atom3870*atom80+atom81*atom3867;
atom3632 =  atom3618*mx3-my3*atom3617;
atom4308 =  atom81*atom4283+atom4265*atom80;
atom4347 =  atom81*atom4200+Izz5*atom80;
atom4350 =  atom4347*atom80+atom81*( atom81*atom4210+atom4221*atom80);
atom4795 =  atom4745*atom2439+atom80*atom4766+atom4225*atom4763;
atom4853 =  Izz6*atom2439+atom80*atom4675+atom4668*atom4225;
atom4848 =  atom2439*atom4691+atom4681*atom4225+atom4687*atom80;
atom4843 =  atom4225*atom4678+atom4684*atom80+atom2439*atom4689;
atom4858 =  atom4848*atom80+atom4843*atom4225+atom4853*atom2439;
atom4808 =  atom4772*atom80+atom4769*atom4225+atom2439*atom4754;
atom3943 = -atom3792*r4+atom3791*d4;
atom4316 =  atom81*atom4289+atom4274*atom80;
atom3900 =  atom3879*atom80+atom81*atom3876;
atom4344 =  atom4223*atom80+atom81*atom4213;
atom4861 = -atom4843*atom115+atom114*atom4853;
atom151 = -m5*g;
atom3777 =  atom3734*atom24-atom3731*atom25-(da1*da1)*atom3597-atom841*da1*atom571;
atom4164 =  atom3793*( atom3827*atom3808-atom3793*atom3838)+atom4087*atom95+atom4081*atom87-( Izz4*atom3793-atom3808*atom3817)*atom3808+atom3824*atom4108-( atom3840*atom3793-atom3808*atom3830)*atom571+atom3833*atom4105+atom4084*atom93;
atom4631 =  atom81*atom4621+atom4623*atom80;
atom5192 =  atom2439*atom5182+atom80*atom5181+atom5180*atom4225;
atom5230 =  atom73*atom25*g+atom68*atom24*g;
atom113 = -m4*g;
atom5250 = -atom111*atom25+atom24*atom112;
atom5291 =  atom81*atom5277+atom5283*atom80;
atom189 = -m6*g;
atom5329 =  atom2439*atom5319+atom5313*atom4225+atom5316*atom80;
atom5349 = atom80*Ma5;
atom5355 = Ma6*atom2439;
atom5392 = atom81*atom5388;
atom3946 =  (d4*d4)+(r4*r4);
atom4870 = -atom115*atom4668+atom114*Izz6;
atom4905 = -atom130*atom4763+atom58*atom4286-atom4782-atom3915+atom133*atom4745-atom4338-atom3627-atom4835-m5*atom3934-atom58*atom3873+atom35*Iyz2-atom95*atom4766-atom3888-m6*atom3934+atom58*mz3*atom3617-atom4300-atom4283*atom94-m3*d3*atom3604-atom610+( atom3867*atom80-atom81*atom3870)*atom59+Ixz2*atom36-atom95*atom4265-m4*atom3934-atom59*mz3*atom3618;
atom4906 = -atom4782-atom3937*m4-atom3915-atom58*atom3882-atom4338-atom3627-atom4835-atom3888-atom4772*atom95+atom58*atom4292-atom130*atom4769+atom59*( atom3876*atom80-atom81*atom3879)-atom4300-atom610-atom4289*atom94-atom3937*m5+atom133*atom4754-atom3937*m6-atom4274*atom95;
atom4907 =  atom4326-atom114*atom4825-atom114*atom4736-atom3864+atom115*atom4757+atom4280-atom3917+atom115*atom4816;
atom4908 = -atom4760-atom4330-atom4821-atom4256;
atom4909 = -atom4736-atom4825;
atom4911 = -atom3894-Izz3-atom4808-m4*atom3943-atom3900-m6*atom3943-atom3632-atom4350-atom3836-atom4858-atom4795-atom4316-m5*atom3943-atom4308;
atom4912 =  atom4344+atom115*atom4763-atom114*atom4745+atom4286-atom3873-atom3824-atom4861;
atom4913 = -atom4848-atom4265-atom4347-atom4766;
atom4914 = -atom4853-atom4745;
atom4916 =  atom4344-atom3882+atom115*atom4769-atom3824-atom114*atom4754-atom4861+atom4292;
atom4917 = -atom4772-atom4274-atom4848-atom4347;
atom4918 = -atom4853-atom4754;
atom4920 =  atom115*atom4681-atom114*atom4691+atom4207;

_MQ[0] =  2.0*atom133*atom4736-Izz1+-2.0*atom4277*atom94+-2.0*atom4760*atom95-atom4821*atom95-atom4330*atom95+atom59*( atom603-atom59*Ixx3)-m6*atom3931-atom35*( atom35*Iyy2-atom273)+-2.0000000000000000e+00*atom58*( atom532*mx3-mz3*atom3613)-m5*atom3931+-2.0*atom58*atom3864+atom133*atom4825+-2.0000000000000000e+00*atom59*( atom3616*mz3-my3*atom532)-m3*( (atom3604*atom3604)+(atom3603*atom3603)+(atom532*atom532))+atom4326*atom58+atom36*( atom271-atom36*Ixx2)+2.0*atom58*atom4280+-2.0*atom130*atom4757+atom58*( atom605-atom58*Iyy3)+-2.0*atom95*atom4256+-2.0*atom59*( atom81*atom3861-atom3858*atom80)-atom58*atom3917-atom130*atom4816-m4*atom3931+atom59*( atom58*atom3838-atom3827*atom59)-atom94*atom4321;
_MQ[1] = atom4905;
_MQ[2] = atom4906;
_MQ[3] = atom4907;
_MQ[4] = atom4908;
_MQ[5] = atom4909;
_MQ[6] = atom4905;
_MQ[7] = -m4*atom3940-Izz2+-2.0*atom3894-Izz3-m5*atom3940+-2.0*atom3632-atom4350-atom3836-atom4858+-2.0*atom4795-m3*(d3*d3)-m6*atom3940+-2.0*atom4308;
_MQ[8] = atom4911;
_MQ[9] = atom4912;
_MQ[10] = atom4913;
_MQ[11] = atom4914;
_MQ[12] = atom4906;
_MQ[13] = atom4911;
_MQ[14] = -m5*atom3946-Izz3-m6*atom3946+-2.0*atom4808+-2.0*atom3900-atom4350-m4*atom3946-atom3836-atom4858+-2.0*atom4316;
_MQ[15] = atom4916;
_MQ[16] = atom4917;
_MQ[17] = atom4918;
_MQ[18] = atom4907;
_MQ[19] = atom4912;
_MQ[20] = atom4916;
_MQ[21] = -Izz4-atom4219-atom114*atom4870+atom115*(-atom115*atom4678+atom114*atom4689);
_MQ[22] = atom4920;
_MQ[23] = -atom4870;
_MQ[24] = atom4908;
_MQ[25] = atom4913;
_MQ[26] = atom4917;
_MQ[27] = atom4920;
_MQ[28] = -atom4687-Izz5;
_MQ[29] = -atom4675;
_MQ[30] = atom4909;
_MQ[31] = atom4914;
_MQ[32] = atom4918;
_MQ[33] = -atom4870;
_MQ[34] = -atom4675;
_MQ[35] = -Izz6;
_MQ[36] = -atom95*atom5283-atom58*atom4622+atom3842*atom4170-( atom4984*atom25-my6*( atom4655*atom5039-atom4659*atom5033)-atom4993*atom24+( atom5039*atom4191-atom5036*atom4659)*mx6-mz6*( atom5033*atom4191-atom5036*atom4655))*atom3845+atom95*atom4623-atom95*Ma5-atom130*atom5313+atom4633*atom3842+atom95*atom5181-atom61*atom3731-atom133*atom5182+atom4632*atom3841+atom58*atom5356+atom3779*atom3604+da1*atom571*atom3597-atom94*atom5277-atom58*atom5253+atom133*atom5319+atom130*atom5180-atom59*( atom3817*atom4108+atom3827*atom4105+atom4084*atom90+atom4087*atom94-atom3793*( atom3833*atom3808-atom571*atom3838)+atom84*atom4081-atom571*( atom3836*atom3808-atom3840*atom571)+atom3808*( Izz4*atom571-atom3824*atom3808))+atom59*( atom60*atom111+atom112*atom62)-atom63*atom3734-atom532*( my3*da1*atom571-atom3684*atom24+mz3*(da1*da1)+atom25*atom3681)+atom58*( atom68*atom3728-atom3727*atom73)+atom4169*atom3841-Ma1+atom4165*atom58-( mx4*( atom4037*atom571+atom4041)+( atom3793*atom4030+atom4031*atom571)*mz4-atom24*atom4011+atom4006*atom25-my4*( atom4038+atom4037*atom3793))*atom3845+atom495*(da2*da2)+atom3841*atom5196+atom81*atom59*Ma5-atom3603*( atom3687*atom36-my3*atom3708-atom37*atom3681+mz3*da1*atom3701-atom39*atom3684+( (da1*da1)*atom3607-atom3705)*mx3)+atom4621*atom94-atom5388*atom94+Ma6*atom133+( ( atom4189*atom4484-atom4478*atom4191)*my5-atom4436*atom25-mz5*( atom4189*atom4481+atom4478*atom3808)+atom4443*atom24+mx5*( atom4481*atom4191+atom3808*atom4484))*atom3845+atom841*(atom571*atom571)-atom5316*atom95+atom3516*da2*da1+atom3842*atom5197+atom58*atom5280;
_MQ[37] =  atom4633*atom3791+atom151*atom897-atom5291+atom5192-atom3792*atom5196+atom3779*d3+atom189*atom897-atom532*m3*g-atom5230-atom5392-( atom38*my2-mz2*atom25+atom37*mx2)*atom24*g+atom3791*atom5197-atom3792*atom4169+atom3777+atom4164+atom3791*atom4170-( atom39*mx2+atom40*my2+mz2*atom24)*atom25*g-atom5329-atom495*da2*da1-atom3792*atom4632-atom5250-atom5355+atom113*atom897-atom3516*(da1*da1)-Ma2+atom4631;
_MQ[38] =  atom4632*r4-atom5291+atom5192-Ma3+d4*atom4170-atom5230-atom5392+atom4633*d4+atom891*atom151+atom5196*r4+atom3777+atom891*atom189+atom4164-atom5329+atom113*atom891+d4*atom5197-atom5250-atom5355+atom4169*r4+atom4631;
_MQ[39] =  atom4165-atom5180*atom115+atom114*atom5182-atom114*atom5319+atom115*atom5313-Ma4+atom5280-atom4622-atom5253;
_MQ[40] = -atom5316+atom4623-atom5283+atom5181-Ma5;
_MQ[41] = -Ma6+atom5182-atom5319;

return _MQ;
}

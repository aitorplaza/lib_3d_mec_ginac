/*----------M.c lib3D_MEC exported-----------*/

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

#include "M.h"

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
double atom3616;
double atom3613;
double atom3848;
double atom3861;
double atom3858;
double atom3864;
double atom3815;
double atom3917;
double atom3810;
double atom3811;
double atom3812;
double atom3814;
double atom152;
double atom153;
double atom4697;
double atom4699;
double atom4715;
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
double atom3940;
double atom3894;
double atom3632;
double atom3836;
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
double atom3824;
double atom4344;
double atom4861;
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

double * _M = NULL;
void Init_M ( ) 
{
    _M = malloc ( M_n_rows * M_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < M_n_rows * M_n_cols ; i++ ) {_M[i]=0.0;}
  }
}

void Done_M ( ) 
{
if (_M != NULL) 
free (_M ); 
_M = NULL; 
}


double * M ()
{
if ( _M == NULL )
 {
    _M = malloc ( M_n_rows * M_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < M_n_rows * M_n_cols ; i++ ) {_M[i]=0.0;}
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
atom4321 =  atom95*atom4221+atom94*atom4210+( atom115*atom4204-atom114*atom4202)*atom58;
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
atom3616 =  atom3607*atom3604+atom3603*atom3610;
atom3613 = -atom3610*atom3604+atom3603*atom3607;
atom3848 =  atom3841*atom80+atom81*atom3845;
atom3861 =  atom3848*mz4+atom3842*mx4;
atom3858 = -mz4*atom3851-my4*atom3842;
atom3864 =  mx4*atom3851-my4*atom3848;
atom3815 = Ixz4*atom80;
atom3917 =  ( atom81*Iyz4-atom3815)*atom59+atom58*Izz4;
atom3810 = -atom81*Ixy4;
atom3811 =  atom3810+Ixx4*atom80;
atom3812 = Ixy4*atom80;
atom3814 = -atom81*Iyy4+atom3812;
atom152 = cos(a6);
atom153 = sin(a6);
atom4697 = -atom81*atom152-atom4224*atom153;
atom4699 = -atom115*atom153;
atom4715 =  atom3841*atom4697+atom4699*atom3842+( atom152*atom80-atom153*atom4225)*atom3845;
atom4698 = atom115*atom152;
atom4694 =  atom4224*atom152-atom81*atom153;
atom4710 =  ( atom152*atom4225+atom153*atom80)*atom3845+atom3841*atom4694+atom3842*atom4698;
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
atom3852 = -atom3792*atom80;
atom3873 =  atom3853*mx4-my4*atom3852;
atom3870 =  atom3791*mx4+mz4*atom3852;
atom3867 = -atom3853*mz4-my4*atom3791;
atom3888 =  atom3861*atom80+atom81*atom3858;
atom3934 =  atom3791*atom3842-atom3792*atom3841;
atom3627 =  atom3616*mx3-my3*atom3613;
atom610 = -Ixz3*atom59-atom58*Iyz3;
atom3915 = -atom59*( atom80*atom3814+atom81*atom3811)+atom58*( Izz4*atom80+atom3822);
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
atom3940 =  (atom3791*atom3791)+(atom3792*atom3792);
atom3894 =  atom3870*atom80+atom81*atom3867;
atom3632 =  atom3618*mx3-my3*atom3617;
atom3836 =  atom81*( atom81*Ixx4+atom3812)-( atom3810-Iyy4*atom80)*atom80;
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
atom3824 =  Iyz4*atom80+atom3822;
atom4344 =  atom4223*atom80+atom81*atom4213;
atom4861 = -atom4843*atom115+atom114*atom4853;
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

_M[0] =  2.0*atom133*atom4736-Izz1-( atom58*Ixy3+atom59*Ixx3)*atom59+-2.0*atom4277*atom94-atom58*( atom59*Ixy3+atom58*Iyy3)+-2.0*atom4760*atom95-atom4821*atom95-atom4330*atom95-atom36*( atom35*Ixy2+atom36*Ixx2)-m6*atom3931+-2.0000000000000000e+00*atom58*( atom532*mx3-mz3*atom3613)-m5*atom3931+-2.0*atom58*atom3864+atom133*atom4825+atom59*( atom58*( atom3815-atom81*Izz4)-atom59*( atom3811*atom80-atom81*atom3814))+-2.0000000000000000e+00*atom59*( atom3616*mz3-my3*atom532)-m3*( (atom3604*atom3604)+(atom3603*atom3603)+(atom532*atom532))+atom4326*atom58+2.0*atom58*atom4280+-2.0*atom130*atom4757+-2.0*atom95*atom4256+-2.0*atom59*( atom81*atom3861-atom3858*atom80)-atom58*atom3917-atom130*atom4816-m4*atom3931-atom35*( atom36*Ixy2+atom35*Iyy2)-atom94*atom4321;
_M[1] = atom4905;
_M[2] = atom4906;
_M[3] = atom4907;
_M[4] = atom4908;
_M[5] = atom4909;
_M[6] = atom4905;
_M[7] = -m4*atom3940-Izz2+-2.0*atom3894-Izz3-m5*atom3940+-2.0*atom3632-atom4350-atom3836-atom4858+-2.0*atom4795-m3*(d3*d3)-m6*atom3940+-2.0*atom4308;
_M[8] = atom4911;
_M[9] = atom4912;
_M[10] = atom4913;
_M[11] = atom4914;
_M[12] = atom4906;
_M[13] = atom4911;
_M[14] = -m5*atom3946-Izz3-m6*atom3946+-2.0*atom4808+-2.0*atom3900-atom4350-m4*atom3946-atom3836-atom4858+-2.0*atom4316;
_M[15] = atom4916;
_M[16] = atom4917;
_M[17] = atom4918;
_M[18] = atom4907;
_M[19] = atom4912;
_M[20] = atom4916;
_M[21] = -Izz4-atom4219-atom114*atom4870+atom115*(-atom115*atom4678+atom114*atom4689);
_M[22] = atom4920;
_M[23] = -atom4870;
_M[24] = atom4908;
_M[25] = atom4913;
_M[26] = atom4917;
_M[27] = atom4920;
_M[28] = -atom4687-Izz5;
_M[29] = -atom4675;
_M[30] = atom4909;
_M[31] = atom4914;
_M[32] = atom4918;
_M[33] = -atom4870;
_M[34] = -atom4675;
_M[35] = -Izz6;

return _M;
}

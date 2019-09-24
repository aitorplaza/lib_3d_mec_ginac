/*----------MQrec.c lib3D_MEC exported-----------*/

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

#include "MQrec.h"

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

double atom57;
double atom58;
double atom35;
double atom59;
double atom36;
double atom2582;
double atom2576;
double atom2579;
double atom2575;
double atom81;
double atom2585;
double atom4606;
double atom4602;
double atom299;
double atom80;
double atom5474;
double atom152;
double atom5521;
double atom115;
double atom2588;
double atom114;
double atom5476;
double atom153;
double atom5510;
double atom5524;
double atom5485;
double atom5487;
double atom5478;
double atom5497;
double atom5514;
double atom5529;
double atom5533;
double atom5501;
double atom5538;
double atom5541;
double atom5492;
double atom5506;
double atom5544;
double atom5560;
double atom5562;
double atom5644;
double atom5634;
double atom5647;
double atom5615;
double atom5705;
double atom5582;
double atom5590;
double atom5687;
double atom2589;
double atom2832;
double atom2864;
double atom5724;
double atom2590;
double atom2831;
double atom5730;
double atom847;
double atom1444;
double atom1447;
double atom5735;
double atom5728;
double atom5738;
double atom848;
double atom5741;
double atom5745;
double atom2865;
double atom5749;
double atom5753;
double atom5754;
double atom5758;
double atom5762;
double atom5763;
double atom5766;
double atom5769;
double atom5781;
double atom5776;
double atom5783;
double atom5785;
double atom513;
double atom1467;
double atom5827;
double atom1472;
double atom5832;
double atom878;
double atom5850;
double atom873;
double atom1477;
double atom5819;
double atom868;
double atom5835;
double atom510;
double atom5839;
double atom5854;
double atom516;
double atom5863;
double atom5804;
double atom5805;
double atom5790;
double atom5795;
double atom5798;
double atom5875;
double atom2866;
double atom2867;
double atom5891;
double atom5896;
double atom5898;
double atom5902;
double atom5904;
double atom5907;
double atom5883;
double atom5888;
double atom5910;
double atom5920;
double atom5922;
double atom5956;
double atom5961;
double atom5964;
double atom5948;
double atom5991;
double atom5979;
double atom5968;
double atom5983;
double atom5934;
double atom5935;
double atom5929;
double atom5930;
double atom6001;
double atom3687;
double atom6015;
double atom3688;
double atom6019;
double atom6034;
double atom6010;
double atom6022;
double atom6025;
double atom6044;
double atom6040;
double atom6080;
double atom3817;
double atom3812;
double atom6060;
double atom6055;
double atom3821;
double atom6050;
double atom6058;
double atom6036;
double atom6063;
double atom6068;
double atom6070;
double atom6090;
double atom6092;
double atom6095;
double atom6087;
double atom6088;
double atom6097;
double atom6101;
double atom6103;
double atom3836;
double atom3833;
double atom3890;
double atom6122;
double atom3839;
double atom6117;
double atom6124;
double atom6128;
double atom6132;
double atom6134;
double atom6111;
double atom6107;
double atom6144;
double atom6170;
double atom6172;
double atom6151;
double atom6152;
double atom6155;
double atom6176;
double atom6179;
double atom6181;
double atom6161;
double atom6157;
double atom6191;
double atom2449;
double atom2450;
double atom4467;
double atom4435;
double atom4502;
double atom4652;
double atom443;
double atom4503;
double atom4499;
double atom4651;
double atom4664;
double atom4665;
double atom2486;
double atom2485;
double atom4648;
double atom5125;
double atom4667;
double atom5119;
double atom5137;
double atom4668;
double atom4517;
double atom4514;
double atom4515;
double atom4516;
double atom2487;
double atom5108;
double atom4436;
double atom5111;
double atom5113;
double atom5114;
double atom4521;
double atom5120;
double atom4518;
double atom5126;
double atom5131;
double atom5132;
double atom5134;
double atom4778;
double atom4774;
double atom4891;
double atom4888;
double atom4905;
double atom4909;
double atom5150;
double atom4777;
double atom5153;
double atom4892;
double atom5177;
double atom4908;
double atom5171;
double atom4911;
double atom4519;
double atom4520;
double atom5159;
double atom5162;
double atom5165;
double atom4797;
double atom4793;
double atom4790;
double atom4795;
double atom5184;
double atom5188;
double atom4791;
double atom4794;
double atom5193;
double atom5203;
double atom5218;
double atom4904;
double atom4907;
double atom5226;
double atom5206;
double atom5214;
double atom5229;
double atom5232;
double atom4669;
double atom4671;
double atom5254;
double atom5256;
double atom4581;
double atom4612;
double atom4585;
double atom4590;
double atom4741;
double atom4736;
double atom4959;
double atom4969;
double atom5362;
double atom4964;
double atom5351;
double atom4855;
double atom4850;
double atom5365;
double atom4845;
double atom5329;
double atom5330;
double atom5378;
double atom4731;
double atom5393;
double atom5404;
double atom5408;
double atom4462;
double atom4577;
double atom4580;
double atom4617;
double atom5423;
double atom5432;
double atom5276;
double atom5284;
double atom5295;
double atom5296;
double atom4465;
double atom5446;
double atom6215;
double atom6224;
double atom6233;
double atom6242;
double atom4623;
double atom5467;
double atom5879;
double atom6005;
double atom6084;
double atom6148;
double atom6195;
double atom6216;
double atom6225;
double atom6234;
double atom6243;

double * _MQrec = NULL;
void Init_MQrec ( ) 
{
    _MQrec = malloc ( MQrec_n_rows * MQrec_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < MQrec_n_rows * MQrec_n_cols ; i++ ) {_MQrec[i]=0.0;}
  }
}

void Done_MQrec ( ) 
{
if (_MQrec != NULL) 
free (_MQrec ); 
_MQrec = NULL; 
}


double * MQrec ()
{
if ( _MQrec == NULL )
 {
    _MQrec = malloc ( MQrec_n_rows * MQrec_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < MQrec_n_rows * MQrec_n_cols ; i++ ) {_MQrec[i]=0.0;}
  }
 }

atom57 =  a3+a2;
atom58 = cos(atom57);
atom35 = cos(a2);
atom59 = sin(atom57);
atom36 = sin(a2);
atom2582 = -atom35*atom59+atom58*atom36;
atom2576 = r3*atom36;
atom2579 =  atom59*atom36+atom58*atom35;
atom2575 = -atom35*r3;
atom81 = sin(a4);
atom2585 =  atom2579*atom2575-atom2582*atom2576;
atom4606 = -atom36*atom2579+atom35*atom2582;
atom4602 = -atom36*atom2582-atom35*atom2579;
atom299 = atom35*d3;
atom80 = cos(a4);
atom5474 = -atom4606*r4+atom299-atom4602*d4;
atom152 = cos(a6);
atom5521 =  atom80*atom5474-atom81*atom2585;
atom115 = sin(a5);
atom2588 =  atom2579*atom2576+atom2582*atom2575;
atom114 = cos(a5);
atom5476 =  atom81*atom5474+atom2585*atom80;
atom153 = sin(a6);
atom5510 =  atom114*atom5476+atom115*atom2588;
atom5524 = -atom153*atom5510+atom152*atom5521;
atom5485 = atom4606*atom80;
atom5487 =  atom114*atom5485+atom4602*atom115;
atom5478 = -atom81*atom4606;
atom5497 =  atom5478*atom153+atom152*atom5487;
atom5514 = -atom115*atom5485+atom114*atom4602;
atom5529 = -mz6*atom5497+m6*atom5524-mx6*atom5514;
atom5533 =  atom152*atom5510+atom5521*atom153;
atom5501 =  atom5478*atom152-atom153*atom5487;
atom5538 =  my6*atom5514+mz6*atom5501+m6*atom5533;
atom5541 =  mz5*atom5514+atom5538*atom152-atom5478*my5+m5*atom5510-atom153*atom5529;
atom5492 = -atom115*atom5476+atom114*atom2588;
atom5506 =  m5*atom5492-mz5*atom5487-my6*atom5497+m6*atom5492+atom5478*mx5+atom5501*mx6;
atom5544 =  m4*atom5476-atom115*atom5506+atom114*atom5541+atom4602*my4+mz4*atom5478;
atom5560 =  atom5487*my5-mz4*atom5485-atom4602*mx4-mx5*atom5514+atom5538*atom153+m4*atom5521+m5*atom5521+atom152*atom5529;
atom5562 =  atom5560*atom80+atom81*atom5544;
atom5644 =  atom5497*Ixy6+mz6*atom5533-Iyz6*atom5514+atom5501*Iyy6+mx6*atom5492;
atom5634 = -my6*atom5492-Ixz6*atom5514+atom5501*Ixy6-mz6*atom5524+Ixx6*atom5497;
atom5647 =  Ixx5*atom5487-mz5*atom5492-atom5644*atom153+Ixz5*atom5478+Ixy5*atom5514+atom152*atom5634+atom5521*my5;
atom5615 =  Iyy5*atom5514+atom5487*Ixy5+atom5478*Iyz5-atom5521*mx5-atom5501*Iyz6-Ixz6*atom5497+mz5*atom5510+my6*atom5533-atom5524*mx6+Izz6*atom5514;
atom5705 =  atom4606*Ixy3-mx3*atom299+my4*atom5476-mx4*atom5521+Izz4*atom4602+atom5647*atom115-atom5562*d4+atom4602*Iyy3+mz3*atom2585+atom5615*atom114-Ixz4*atom5485-atom5478*Iyz4;
atom5582 =  atom114*atom5506+m4*atom2588-mz3*atom4606-atom5485*my4+atom5478*mx4+atom115*atom5541+m3*atom2588;
atom5590 =  m3*atom2585+atom5544*atom80-atom81*atom5560+mz3*atom4602;
atom5687 =  atom4602*Ixy3-mz3*atom2588-atom5562*r4+atom81*( atom4602*Iyz4-Izz5*atom5478-Iyz5*atom5514-atom5634*atom153-atom5478*Iyy4-mx4*atom2588-Ixz5*atom5487-mz4*atom5476-atom5485*Ixy4-mx5*atom5492-atom5644*atom152+atom5510*my5)+Ixx3*atom4606+atom299*my3-( mz4*atom5521-atom5478*Ixy4+atom2588*my4-Ixx4*atom5485+atom5615*atom115-atom114*atom5647+Ixz4*atom4602)*atom80;
atom2589 = -atom2582*d3;
atom2832 = -atom2589-r4;
atom2864 = -atom2832*atom80;
atom5724 = mz4*atom80;
atom2590 = atom2579*d3;
atom2831 =  d4+atom2590;
atom5730 =  atom114*atom2831-atom2864*atom115;
atom847 = atom81*atom114;
atom1444 =  atom152*atom847+atom153*atom80;
atom1447 = -atom847*atom153+atom152*atom80;
atom5735 =  my6*atom1444-atom1447*mx6;
atom5728 = -mz5*atom847+mx5*atom80;
atom5738 =  m5*atom5730+atom5728+m6*atom5730-atom5735;
atom848 = -atom81*atom115;
atom5741 =  atom115*atom2831+atom114*atom2864;
atom5745 = -atom80*my5+atom848*mz5;
atom2865 = atom81*atom2832;
atom5749 = -atom5741*atom153+atom2865*atom152;
atom5753 = -mz6*atom1444-atom848*mx6;
atom5754 =  atom5753+atom5749*m6;
atom5758 =  atom2865*atom153+atom152*atom5741;
atom5762 =  atom1447*mz6+atom848*my6;
atom5763 =  atom5762+m6*atom5758;
atom5766 = -atom5754*atom153+m5*atom5741+atom5745+atom152*atom5763;
atom5769 =  atom114*atom5766+m4*atom2864-atom115*atom5738+atom5724;
atom5781 = -atom81*mz4;
atom5776 = -atom848*mx5+atom847*my5;
atom5783 =  atom152*atom5754+atom5781+atom153*atom5763+atom2865*m5+atom5776+atom2865*m4;
atom5785 =  atom80*atom5783+atom81*atom5769;
atom513 =  atom81*Ixy4+Iyy4*atom80;
atom1467 =  atom1447*Ixy6-atom848*Ixz6+atom1444*Ixx6;
atom5827 = -my6*atom5730-atom5749*mz6+atom1467;
atom1472 = -atom848*Iyz6+atom1444*Ixy6+atom1447*Iyy6;
atom5832 =  mz6*atom5758+atom1472+mx6*atom5730;
atom878 =  Izz5*atom80+atom848*Iyz5+Ixz5*atom847;
atom5850 =  mx4*atom2831+atom513+atom5832*atom152+atom878+mx5*atom5730+atom5827*atom153-atom5741*my5+mz4*atom2864;
atom873 =  atom80*Iyz5+atom847*Ixy5+atom848*Iyy5;
atom1477 =  atom1447*Iyz6+Ixz6*atom1444-atom848*Izz6;
atom5819 =  my6*atom5758+mz5*atom5741-atom2865*mx5-atom1477-atom5749*mx6+atom873;
atom868 =  atom848*Ixy5+atom847*Ixx5+Ixz5*atom80;
atom5835 = -mz5*atom5730+atom152*atom5827+atom2865*my5-atom5832*atom153+atom868;
atom510 =  atom81*Ixx4+atom80*Ixy4;
atom5839 = -atom115*atom5819-atom2865*mz4-my4*atom2831+atom510+atom114*atom5835;
atom5854 =  Ixz3+atom5839*atom80-atom81*atom5850-mz3*atom2590-r4*atom5785;
atom516 =  Iyz4*atom80+atom81*Ixz4;
atom5863 =  atom114*atom5819-d4*atom5785+atom2864*my4+mz3*atom2589-atom2865*mx4-atom516+Iyz3+atom5835*atom115;
atom5804 =  atom5769*atom80-atom81*atom5783;
atom5805 =  atom5804+m3*atom2589-my3;
atom5790 =  atom81*my4-mx4*atom80;
atom5795 = -atom115*atom5766-m4*atom2831-atom114*atom5738+atom5790;
atom5798 =  mx3+m3*atom2590-atom5795;
atom5875 =  atom5798*atom2579-atom2582*atom5805;
atom2866 = r4*atom80;
atom2867 = -atom81*r4;
atom5891 =  atom115*d4+atom114*atom2866;
atom5896 =  atom2867*atom152-atom5891*atom153;
atom5898 =  atom5753+m6*atom5896;
atom5902 =  atom5891*atom152+atom2867*atom153;
atom5904 =  atom5762+m6*atom5902;
atom5907 = -atom153*atom5898+atom5904*atom152+atom5891*m5+atom5745;
atom5883 =  atom114*d4-atom115*atom2866;
atom5888 =  atom5883*m6+atom5728+atom5883*m5-atom5735;
atom5910 = -atom5888*atom115+atom114*atom5907+m4*atom2866+atom5724;
atom5920 =  atom2867*m4+atom152*atom5898+atom2867*m5+atom5781+atom5904*atom153+atom5776;
atom5922 =  atom81*atom5910+atom5920*atom80;
atom5956 =  atom1467-mz6*atom5896-atom5883*my6;
atom5961 =  mz6*atom5902+atom1472+atom5883*mx6;
atom5964 = -atom5883*mz5+atom2867*my5-atom153*atom5961+atom152*atom5956+atom868;
atom5948 =  my6*atom5902-atom1477+mz5*atom5891-atom5896*mx6+atom873-atom2867*mx5;
atom5991 =  atom114*atom5948+atom115*atom5964-atom516-atom2867*mx4+Iyz3-atom5922*d4+atom2866*my4;
atom5979 =  atom513+mz4*atom2866-atom5891*my5+atom878+atom5883*mx5+d4*mx4+atom152*atom5961+atom153*atom5956;
atom5968 = -atom115*atom5948-d4*my4+atom114*atom5964+atom510-atom2867*mz4;
atom5983 =  Ixz3-atom5922*r4-atom81*atom5979+atom5968*atom80;
atom5934 =  atom5910*atom80-atom81*atom5920;
atom5935 = -my3+atom5934;
atom5929 = -m4*d4-atom115*atom5907+atom5790-atom114*atom5888;
atom5930 =  mx3-atom5929;
atom6001 =  atom2579*atom5930-atom2582*atom5935;
atom3687 = -atom115*atom152;
atom6015 = -mz6*atom3687+atom114*mx6;
atom3688 = atom115*atom153;
atom6019 =  atom3688*mz6-atom114*my6;
atom6034 = -atom115*my5+atom152*atom6015+mx4+atom114*mx5+atom6019*atom153;
atom6010 = -my6*atom3687+mz5*atom115+atom3688*mx6;
atom6022 = -atom153*atom6015+atom6019*atom152-atom114*mz5;
atom6025 =  atom114*atom6022-atom6010*atom115-my4;
atom6044 =  atom6025*atom80-atom81*atom6034;
atom6040 = -atom115*atom6022-atom114*atom6010;
atom6080 = -atom6044*atom2582-atom2579*atom6040;
atom3817 =  atom114*Iyz6+atom3688*Iyy6+atom3687*Ixy6;
atom3812 =  atom114*Ixz6+atom3687*Ixx6+atom3688*Ixy6;
atom6060 =  atom3817*atom152-atom114*Iyz5-Ixz5*atom115+Iyz4+atom3812*atom153;
atom6055 = -atom114*Ixy5+atom3812*atom152-atom3817*atom153-atom115*Ixx5;
atom3821 = atom114*Izz6;
atom6050 = -atom115*Ixy5-Ixz6*atom3687-atom3821-atom3688*Iyz6-atom114*Iyy5;
atom6058 =  Ixz4-atom6050*atom115+atom114*atom6055;
atom6036 =  atom6034*atom80+atom81*atom6025;
atom6063 = -atom81*atom6060+atom6058*atom80-atom6036*r4;
atom6068 =  Izz4-atom115*atom6055-atom114*atom6050;
atom6070 = -atom6036*d4-atom6068;
atom6090 = -mz6*atom153;
atom6092 = mz6*atom152;
atom6095 = -atom6090*atom153+atom6092*atom152-my5;
atom6087 = -atom152*mx6+my6*atom153;
atom6088 = -atom6087+mx5;
atom6097 =  atom114*atom6095-atom115*atom6088;
atom6101 =  atom6092*atom153+atom152*atom6090;
atom6103 =  atom80*atom6101+atom81*atom6097;
atom3836 =  atom152*Iyy6+atom153*Ixy6;
atom3833 =  atom153*Ixx6+atom152*Ixy6;
atom3890 = -atom3836*atom152-Izz5-atom153*atom3833;
atom6122 =  Ixz5-atom3836*atom153+atom152*atom3833;
atom3839 =  Ixz6*atom153+atom152*Iyz6;
atom6117 =  Iyz5-atom3839;
atom6124 = -atom115*atom6117+atom114*atom6122;
atom6128 =  atom81*atom3890-r4*atom6103+atom6124*atom80;
atom6132 = -atom114*atom6117-atom115*atom6122;
atom6134 = -d4*atom6103-atom6132;
atom6111 = -atom81*atom6101+atom6097*atom80;
atom6107 = -atom115*atom6095-atom114*atom6088;
atom6144 = -atom6111*atom2582-atom2579*atom6107;
atom6170 =  Ixz6*atom152-atom153*Iyz6;
atom6172 =  atom114*atom6170+Izz6*atom115;
atom6151 = -my6*atom152-atom153*mx6;
atom6152 = atom6151*atom114;
atom6155 = -atom6087*atom80+atom81*atom6152;
atom6176 = -atom81*atom3839-r4*atom6155+atom6172*atom80;
atom6179 = -atom115*atom6170+atom3821;
atom6181 = -atom6179-d4*atom6155;
atom6161 =  atom6152*atom80+atom81*atom6087;
atom6157 = -atom6151*atom115;
atom6191 = -atom2582*atom6161-atom6157*atom2579;
atom2449 = -atom36*da1;
atom2450 = -atom35*da1;
atom4467 =  Iyz2*atom2450+Ixz2*atom2449+da2*Izz2;
atom4435 = -atom36*g;
atom4502 =  atom2579*atom2450+atom2582*atom2449;
atom4652 = -atom4502+da4;
atom443 = da3;
atom4503 =  atom443+da2;
atom4499 =  atom2579*atom2449-atom2582*atom2450;
atom4651 =  atom4503*atom80-atom81*atom4499;
atom4664 = (atom4652*atom4652);
atom4665 = (atom4651*atom4651);
atom2486 = da2*atom2450;
atom2485 = da2*atom2449;
atom4648 =  atom81*atom4503+atom4499*atom80;
atom5125 = -atom2485*atom2579+atom2582*atom2486-atom443*atom4499;
atom4667 = atom4651*atom4648;
atom5119 =  atom2485*atom2582+atom4502*atom443+atom2579*atom2486;
atom5137 = -da4*atom4648-atom81*atom5119;
atom4668 = atom4648*atom4652;
atom4517 = atom4502*atom4499;
atom4514 = (atom4503*atom4503);
atom4515 = (atom4502*atom4502);
atom4516 = -atom4514-atom4515;
atom2487 = (atom2450*atom2450);
atom5108 =  atom4435-( (da2*da2)+atom2487)*d3;
atom4436 = -atom35*g;
atom5111 =  atom4436+d3*atom2450*atom2449;
atom5113 = -atom5111*atom2582+atom2579*atom5108;
atom5114 =  d4*atom4516-atom4517*r4+atom5113;
atom4521 = atom4502*atom4503;
atom5120 =  atom5119+atom4521;
atom4518 = atom4499*atom4503;
atom5126 = -atom5125+atom4518;
atom5131 = -r3*( (atom2449*atom2449)+atom2487)+2.0*atom2485*d3;
atom5132 =  atom5126*d4-r4*atom5120+atom5131;
atom5134 =  atom81*atom5132+atom5114*atom80;
atom4778 =  da5+atom4651;
atom4774 = -atom115*atom4652+atom114*atom4648;
atom4891 = -atom4774*atom153+atom152*atom4778;
atom4888 =  atom4774*atom152+atom153*atom4778;
atom4905 = (atom4891*atom4891);
atom4909 = (atom4888*atom4888);
atom5150 =  da4*atom4651+atom5119*atom80;
atom4777 = -atom115*atom4648-atom114*atom4652;
atom5153 =  atom114*atom5150+atom115*atom5125+da5*atom4777;
atom4892 =  da6-atom4777;
atom5177 = -da6*atom4888+atom5137*atom152-atom5153*atom153;
atom4908 = atom4892*atom4888;
atom5171 =  da6*atom4891+atom5153*atom152+atom5137*atom153;
atom4911 = atom4892*atom4891;
atom4519 = (atom4499*atom4499);
atom4520 = -atom4514-atom4519;
atom5159 =  atom5111*atom2579+atom2582*atom5108;
atom5162 =  atom5159+atom4517*d4-r4*atom4520;
atom5165 =  atom114*atom5162-atom115*atom5134;
atom4797 = atom4777*atom4778;
atom4793 = atom4774*atom4777;
atom4790 = (atom4778*atom4778);
atom4795 = (atom4774*atom4774);
atom5184 =  ( atom4905+atom4909)*mz6-mz5*( atom5153-atom4797)-my6*( atom5171+atom4911)+m6*atom5165-( atom4790+atom4795)*my5+m5*atom5165+( atom5177-atom4908)*mx6+( atom5137+atom4793)*mx5;
atom5188 =  atom114*atom5134+atom115*atom5162;
atom4791 = (atom4777*atom4777);
atom4794 = atom4774*atom4778;
atom5193 = -atom115*atom5150+atom114*atom5125-atom4774*da5;
atom5203 = -atom81*atom5114+atom5132*atom80;
atom5218 =  atom5203*atom153+atom5188*atom152;
atom4904 = (atom4892*atom4892);
atom4907 = atom4891*atom4888;
atom5226 =  ( atom5177+atom4908)*mz6-( atom4905+atom4904)*mx6+m6*atom5218+my6*( atom5193+atom4907);
atom5206 = -atom5188*atom153+atom152*atom5203;
atom5214 = -my6*( atom4909+atom4904)+atom5206*m6-mx6*( atom5193-atom4907)-mz6*( atom5171-atom4911);
atom5229 =  atom152*atom5226-( atom5137-atom4793)*my5-( atom4791+atom4790)*mx5+mz5*( atom4794+atom5193)-atom153*atom5214+atom5188*m5;
atom5232 = -atom5184*atom115+atom114*atom5229-mx4*( atom4664+atom4665)+mz4*( atom5137+atom4668)+( atom5125+atom4667)*my4+m4*atom5134;
atom4669 = (atom4648*atom4648);
atom4671 = atom4651*atom4652;
atom5254 =  m4*atom5203+atom153*atom5226+m5*atom5203-( atom4669+atom4664)*my4-( atom5125-atom4667)*mx4-mz5*( atom4791+atom4795)+( atom5153+atom4797)*my5+atom152*atom5214+( atom4794-atom5193)*mx5-mz4*( atom5150-atom4671);
atom5256 =  atom80*atom5254+atom5232*atom81;
atom4581 = atom4499*Ixy3;
atom4612 =  atom4502*Ixx3-atom4581;
atom4585 =  atom4502*Iyy3+atom4581+atom4503*Iyz3;
atom4590 =  Ixz3*atom4499+atom4503*Izz3+atom4502*Iyz3;
atom4741 =  Ixz4*atom4648+Izz4*atom4652+atom4651*Iyz4;
atom4736 =  atom4648*Ixy4+atom4651*Iyy4+Iyz4*atom4652;
atom4959 =  atom4888*Ixx6+atom4891*Ixy6+atom4892*Ixz6;
atom4969 =  atom4892*Izz6+atom4891*Iyz6+Ixz6*atom4888;
atom5362 =  atom5171*Ixy6+mz6*atom5218+atom4959*atom4892-atom4969*atom4888-atom5193*Iyz6+atom5165*mx6+atom5177*Iyy6;
atom4964 =  atom4888*Ixy6+atom4891*Iyy6+atom4892*Iyz6;
atom5351 = -Ixz6*atom5193+atom5177*Ixy6-mz6*atom5206+atom5171*Ixx6+atom4969*atom4891-my6*atom5165-atom4892*atom4964;
atom4855 =  Izz5*atom4778+atom4777*Iyz5+atom4774*Ixz5;
atom4850 =  atom4774*Ixy5+atom4778*Iyz5+atom4777*Iyy5;
atom5365 =  atom4855*atom4777-atom153*atom5362+atom5351*atom152+atom5153*Ixx5+atom5193*Ixy5+Ixz5*atom5137+atom5203*my5-atom4850*atom4778-mz5*atom5165;
atom4845 =  atom4777*Ixy5+Ixz5*atom4778+atom4774*Ixx5;
atom5329 =  atom5206*mx6+atom5177*Iyz6-my6*atom5218+atom5171*Ixz6-Izz6*atom5193-atom4959*atom4891+atom4888*atom4964;
atom5330 =  atom5137*Iyz5+atom5153*Ixy5+atom5193*Iyy5-atom5203*mx5-atom5329-atom4774*atom4855+atom4845*atom4778+atom5188*mz5;
atom5378 = -atom4736*atom4652-Ixz4*atom5125-atom5162*my4+atom4741*atom4651+atom5137*Ixy4-atom115*atom5330-mz4*atom5203+atom5150*Ixx4+atom114*atom5365;
atom4731 =  Ixz4*atom4652+atom4648*Ixx4+atom4651*Ixy4;
atom5393 =  Izz5*atom5137+atom152*atom5362-atom4777*atom4845+atom4774*atom4850-atom5188*my5+atom5165*mx5+atom5153*Ixz5+atom5193*Iyz5+atom5351*atom153;
atom5404 =  atom5393+atom5137*Iyy4+mz4*atom5134+atom4652*atom4731-atom4741*atom4648-Iyz4*atom5125+atom5150*Ixy4+mx4*atom5162;
atom5408 =  my3*atom5131-atom81*atom5404+atom80*atom5378-atom4503*atom4585-atom5256*r4+atom4612*da2+atom4502*atom4590+atom4612*da3-mz3*atom5159;
atom4462 =  Ixy2*atom2450+Ixx2*atom2449+da2*Ixz2;
atom4577 = atom4502*Ixy3;
atom4580 =  atom4577+Ixx3*atom4499+Ixz3*atom4503;
atom4617 =  atom4577-Iyy3*atom4499;
atom5423 =  atom4736*atom4648-atom4651*atom4731+atom5203*mx4-atom114*atom5330-Izz4*atom5125-atom5134*my4+Ixz4*atom5150+atom5137*Iyz4-atom115*atom5365;
atom5432 = -atom5256*d4-atom4499*atom4590+atom4580*atom4503+atom4617*da3+atom4617*da2+mz3*atom5113-mx3*atom5131-atom5423;
atom5276 =  ( atom5150+atom4671)*my4-atom115*atom5229-mz4*( atom4669+atom4665)-mx4*( atom5137-atom4668)-atom5184*atom114-m4*atom5162;
atom5284 = -mz3*( atom5119-atom4521)+atom4517*mx3+my3*atom4520+m3*atom5159-atom5276;
atom5295 = -atom81*atom5254+atom5232*atom80;
atom5296 =  mx3*atom4516+m3*atom5113+atom4517*my3+mz3*( atom5125+atom4518)+atom5295;
atom4465 =  da2*Iyz2+Ixy2*atom2449+Iyy2*atom2450;
atom5446 =  atom2579*atom5284-atom5296*atom2582;
atom6215 =  atom80*atom5979+atom81*atom5968-d4*atom5929+Izz3+r4*atom5934;
atom6224 =  atom6060*atom80+atom81*atom6058+atom6044*r4-d4*atom6040;
atom6233 = -atom3890*atom80-d4*atom6107+atom6111*r4+atom81*atom6124;
atom6242 =  r4*atom6161+atom80*atom3839-atom6157*d4+atom81*atom6172;
atom4623 = -atom4499*Iyz3+Ixz3*atom4502;
atom5467 =  atom4623*da2+atom5404*atom80+atom5295*r4+atom4499*atom4585+atom81*atom5378+atom4623*da3-atom5113*my3+atom5159*mx3-d4*atom5276-atom4502*atom4580;
atom5879 = -atom36*( atom2582*atom5863-r3*atom5875+atom5854*atom2579+Ixz2)-atom35*( atom2579*atom5863+Iyz2+r3*( atom2579*atom5805+atom2582*atom5798)-atom5854*atom2582-d3*atom5785);
atom6005 =  atom36*( r3*atom6001-atom5991*atom2582-atom5983*atom2579)+atom35*( atom5922*d3-r3*( atom2582*atom5930+atom5935*atom2579)-atom5991*atom2579+atom5983*atom2582);
atom6084 = -atom36*( atom6063*atom2579-r3*atom6080+atom2582*atom6070)+atom35*( atom6063*atom2582-r3*( atom6044*atom2579-atom2582*atom6040)-atom2579*atom6070+atom6036*d3);
atom6148 =  atom36*( r3*atom6144-atom2579*atom6128-atom6134*atom2582)-atom35*( r3*( atom6111*atom2579-atom2582*atom6107)-atom2582*atom6128-d3*atom6103+atom6134*atom2579);
atom6195 = -atom36*( atom2582*atom6181+atom2579*atom6176-r3*atom6191)+( atom2582*atom6176-atom2579*atom6181+atom6155*d3-r3*( atom2579*atom6161-atom6157*atom2582))*atom35;
atom6216 =  atom6215+d3*atom6001;
atom6225 =  atom6224+d3*atom6080;
atom6234 =  atom6233+atom6144*d3;
atom6243 =  atom6242+atom6191*d3;

_MQrec[0] =  atom35*( atom5687*atom2582-r3*( atom2582*atom5582+atom2579*atom5590)+atom35*Iyy2-atom2579*atom5705+atom36*Ixy2+d3*( m3*atom299+atom5562-atom4602*mx3+atom4606*my3))+Izz1-atom36*( atom5687*atom2579+r3*( atom2582*atom5590-atom2579*atom5582)-atom36*Ixx2+atom2582*atom5705-atom35*Ixy2);
_MQrec[1] = atom5879;
_MQrec[2] = atom6005;
_MQrec[3] = atom6084;
_MQrec[4] = atom6148;
_MQrec[5] = atom6195;
_MQrec[6] = atom5879;
_MQrec[7] = -d4*atom5795+atom5875*d3+atom81*atom5839+atom5804*r4+atom80*atom5850+Izz2+mx3*atom2590-atom2589*my3+Izz3;
_MQrec[8] = atom6216;
_MQrec[9] = atom6225;
_MQrec[10] = atom6234;
_MQrec[11] = atom6243;
_MQrec[12] = atom6005;
_MQrec[13] = atom6216;
_MQrec[14] = atom6215;
_MQrec[15] = atom6224;
_MQrec[16] = atom6233;
_MQrec[17] = atom6242;
_MQrec[18] = atom6084;
_MQrec[19] = atom6225;
_MQrec[20] = atom6224;
_MQrec[21] = atom6068;
_MQrec[22] = atom6132;
_MQrec[23] = atom6179;
_MQrec[24] = atom6148;
_MQrec[25] = atom6234;
_MQrec[26] = atom6233;
_MQrec[27] = atom6132;
_MQrec[28] = -atom3890;
_MQrec[29] = atom3839;
_MQrec[30] = atom6195;
_MQrec[31] = atom6243;
_MQrec[32] = atom6242;
_MQrec[33] = atom6179;
_MQrec[34] = atom3839;
_MQrec[35] = Izz6;
_MQrec[36] = -( Ixx2*atom2486-atom4465*da2-atom4436*mz2+atom2579*atom5408+atom4467*atom2450+atom2582*atom5432-atom2485*Ixy2-r3*atom5446)*atom36-atom35*( atom4435*mz2+r3*( atom2582*atom5284+atom5296*atom2579)+Ixy2*atom2486+da2*atom4462-( atom5256+atom5126*mx3+atom5120*my3+m3*atom5131-mz3*( atom4519+atom4515))*d3-Iyy2*atom2485-atom2582*atom5408-atom4467*atom2449+atom2579*atom5432);
_MQrec[37] =  atom5467-atom4462*atom2450+atom2486*Ixz2-atom2485*Iyz2+atom4465*atom2449-atom4435*my2+atom4436*mx2+atom5446*d3;
_MQrec[38] = atom5467;
_MQrec[39] = atom5423;
_MQrec[40] = atom5393;
_MQrec[41] = atom5329;

return _MQrec;
}

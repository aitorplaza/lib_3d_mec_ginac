/*----------Mrec.c lib3D_MEC exported-----------*/

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

#include "Mrec.h"

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
double atom2579;
double atom4602;
double atom115;
double atom4606;
double atom80;
double atom114;
double atom5485;
double atom5487;
double atom81;
double atom5478;
double atom299;
double atom5474;
double atom2576;
double atom2575;
double atom2585;
double atom5476;
double atom2588;
double atom5492;
double atom152;
double atom153;
double atom5497;
double atom5501;
double atom5506;
double atom5521;
double atom5510;
double atom5524;
double atom5514;
double atom5529;
double atom5533;
double atom5538;
double atom5541;
double atom5582;
double atom5560;
double atom5544;
double atom5590;
double atom5562;
double atom5644;
double atom5634;
double atom5647;
double atom5615;
double atom5705;
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
double atom6215;
double atom6224;
double atom6233;
double atom6242;
double atom5879;
double atom6005;
double atom6084;
double atom6148;
double atom6195;
double atom6216;
double atom6225;
double atom6234;
double atom6243;

double * _Mrec = NULL;
void Init_Mrec ( ) 
{
    _Mrec = malloc ( Mrec_n_rows * Mrec_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Mrec_n_rows * Mrec_n_cols ; i++ ) {_Mrec[i]=0.0;}
  }
}

void Done_Mrec ( ) 
{
if (_Mrec != NULL) 
free (_Mrec ); 
_Mrec = NULL; 
}


double * Mrec ()
{
if ( _Mrec == NULL )
 {
    _Mrec = malloc ( Mrec_n_rows * Mrec_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Mrec_n_rows * Mrec_n_cols ; i++ ) {_Mrec[i]=0.0;}
  }
 }

atom57 =  a3+a2;
atom58 = cos(atom57);
atom35 = cos(a2);
atom59 = sin(atom57);
atom36 = sin(a2);
atom2582 = -atom35*atom59+atom58*atom36;
atom2579 =  atom59*atom36+atom58*atom35;
atom4602 = -atom36*atom2582-atom35*atom2579;
atom115 = sin(a5);
atom4606 = -atom36*atom2579+atom35*atom2582;
atom80 = cos(a4);
atom114 = cos(a5);
atom5485 = atom4606*atom80;
atom5487 =  atom114*atom5485+atom4602*atom115;
atom81 = sin(a4);
atom5478 = -atom81*atom4606;
atom299 = atom35*d3;
atom5474 = -atom4606*r4+atom299-atom4602*d4;
atom2576 = r3*atom36;
atom2575 = -atom35*r3;
atom2585 =  atom2579*atom2575-atom2582*atom2576;
atom5476 =  atom81*atom5474+atom2585*atom80;
atom2588 =  atom2579*atom2576+atom2582*atom2575;
atom5492 = -atom115*atom5476+atom114*atom2588;
atom152 = cos(a6);
atom153 = sin(a6);
atom5497 =  atom5478*atom153+atom152*atom5487;
atom5501 =  atom5478*atom152-atom153*atom5487;
atom5506 =  m5*atom5492-mz5*atom5487-my6*atom5497+m6*atom5492+atom5478*mx5+atom5501*mx6;
atom5521 =  atom80*atom5474-atom81*atom2585;
atom5510 =  atom114*atom5476+atom115*atom2588;
atom5524 = -atom153*atom5510+atom152*atom5521;
atom5514 = -atom115*atom5485+atom114*atom4602;
atom5529 = -mz6*atom5497+m6*atom5524-mx6*atom5514;
atom5533 =  atom152*atom5510+atom5521*atom153;
atom5538 =  my6*atom5514+mz6*atom5501+m6*atom5533;
atom5541 =  mz5*atom5514+atom5538*atom152-atom5478*my5+m5*atom5510-atom153*atom5529;
atom5582 =  atom114*atom5506+m4*atom2588-mz3*atom4606-atom5485*my4+atom5478*mx4+atom115*atom5541+m3*atom2588;
atom5560 =  atom5487*my5-mz4*atom5485-atom4602*mx4-mx5*atom5514+atom5538*atom153+m4*atom5521+m5*atom5521+atom152*atom5529;
atom5544 =  m4*atom5476-atom115*atom5506+atom114*atom5541+atom4602*my4+mz4*atom5478;
atom5590 =  m3*atom2585+atom5544*atom80-atom81*atom5560+mz3*atom4602;
atom5562 =  atom5560*atom80+atom81*atom5544;
atom5644 =  atom5497*Ixy6+mz6*atom5533-Iyz6*atom5514+atom5501*Iyy6+mx6*atom5492;
atom5634 = -my6*atom5492-Ixz6*atom5514+atom5501*Ixy6-mz6*atom5524+Ixx6*atom5497;
atom5647 =  Ixx5*atom5487-mz5*atom5492-atom5644*atom153+Ixz5*atom5478+Ixy5*atom5514+atom152*atom5634+atom5521*my5;
atom5615 =  Iyy5*atom5514+atom5487*Ixy5+atom5478*Iyz5-atom5521*mx5-atom5501*Iyz6-Ixz6*atom5497+mz5*atom5510+my6*atom5533-atom5524*mx6+Izz6*atom5514;
atom5705 =  atom4606*Ixy3-mx3*atom299+my4*atom5476-mx4*atom5521+Izz4*atom4602+atom5647*atom115-atom5562*d4+atom4602*Iyy3+mz3*atom2585+atom5615*atom114-Ixz4*atom5485-atom5478*Iyz4;
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
atom6215 =  atom80*atom5979+atom81*atom5968-d4*atom5929+Izz3+r4*atom5934;
atom6224 =  atom6060*atom80+atom81*atom6058+atom6044*r4-d4*atom6040;
atom6233 = -atom3890*atom80-d4*atom6107+atom6111*r4+atom81*atom6124;
atom6242 =  r4*atom6161+atom80*atom3839-atom6157*d4+atom81*atom6172;
atom5879 = -atom36*( atom2582*atom5863-r3*atom5875+atom5854*atom2579+Ixz2)-atom35*( atom2579*atom5863+Iyz2+r3*( atom2579*atom5805+atom2582*atom5798)-atom5854*atom2582-d3*atom5785);
atom6005 =  atom36*( r3*atom6001-atom5991*atom2582-atom5983*atom2579)+atom35*( atom5922*d3-r3*( atom2582*atom5930+atom5935*atom2579)-atom5991*atom2579+atom5983*atom2582);
atom6084 = -atom36*( atom6063*atom2579-r3*atom6080+atom2582*atom6070)+atom35*( atom6063*atom2582-r3*( atom6044*atom2579-atom2582*atom6040)-atom2579*atom6070+atom6036*d3);
atom6148 =  atom36*( r3*atom6144-atom2579*atom6128-atom6134*atom2582)-atom35*( r3*( atom6111*atom2579-atom2582*atom6107)-atom2582*atom6128-d3*atom6103+atom6134*atom2579);
atom6195 = -atom36*( atom2582*atom6181+atom2579*atom6176-r3*atom6191)+( atom2582*atom6176-atom2579*atom6181+atom6155*d3-r3*( atom2579*atom6161-atom6157*atom2582))*atom35;
atom6216 =  atom6215+d3*atom6001;
atom6225 =  atom6224+d3*atom6080;
atom6234 =  atom6233+atom6144*d3;
atom6243 =  atom6242+atom6191*d3;

_Mrec[0] =  atom35*( atom5687*atom2582-r3*( atom2582*atom5582+atom2579*atom5590)+atom35*Iyy2-atom2579*atom5705+atom36*Ixy2+d3*( m3*atom299+atom5562-atom4602*mx3+atom4606*my3))+Izz1-atom36*( atom5687*atom2579+r3*( atom2582*atom5590-atom2579*atom5582)-atom36*Ixx2+atom2582*atom5705-atom35*Ixy2);
_Mrec[1] = atom5879;
_Mrec[2] = atom6005;
_Mrec[3] = atom6084;
_Mrec[4] = atom6148;
_Mrec[5] = atom6195;
_Mrec[6] = atom5879;
_Mrec[7] = -d4*atom5795+atom5875*d3+atom81*atom5839+atom5804*r4+atom80*atom5850+Izz2+mx3*atom2590-atom2589*my3+Izz3;
_Mrec[8] = atom6216;
_Mrec[9] = atom6225;
_Mrec[10] = atom6234;
_Mrec[11] = atom6243;
_Mrec[12] = atom6005;
_Mrec[13] = atom6216;
_Mrec[14] = atom6215;
_Mrec[15] = atom6224;
_Mrec[16] = atom6233;
_Mrec[17] = atom6242;
_Mrec[18] = atom6084;
_Mrec[19] = atom6225;
_Mrec[20] = atom6224;
_Mrec[21] = atom6068;
_Mrec[22] = atom6132;
_Mrec[23] = atom6179;
_Mrec[24] = atom6148;
_Mrec[25] = atom6234;
_Mrec[26] = atom6233;
_Mrec[27] = atom6132;
_Mrec[28] = -atom3890;
_Mrec[29] = atom3839;
_Mrec[30] = atom6195;
_Mrec[31] = atom6243;
_Mrec[32] = atom6242;
_Mrec[33] = atom6179;
_Mrec[34] = atom3839;
_Mrec[35] = Izz6;

return _Mrec;
}

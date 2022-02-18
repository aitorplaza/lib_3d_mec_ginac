/*----------Mrecsubs.c lib3D_MEC exported-----------*/

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

#include "Mrecsubs.h"

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
double atom57;
double atom59;
double atom58;
double atom3607;
double atom3610;
double atom5612;
double atom5616;
double atom3603;
double atom3604;
double atom3613;
double atom532;
double atom81;
double atom6494;
double atom80;
double atom6497;
double atom6537;
double atom6502;
double atom6504;
double atom3616;
double atom115;
double atom114;
double atom6526;
double atom6507;
double atom6530;
double atom152;
double atom153;
double atom6509;
double atom6513;
double atom6540;
double atom6552;
double atom6593;
double atom6603;
double atom6500;
double atom6632;
double atom6622;
double atom6635;
double atom6647;
double atom6554;
double atom6545;
double atom6581;
double atom6522;
double atom6557;
double atom6565;
double atom6583;
double atom6650;
double atom6664;
double atom6687;
double atom6688;
double atom6694;
double atom6713;
double atom6717;
double atom6724;
double atom6725;
double atom6734;
double atom3617;
double atom3792;
double atom3852;
double atom6788;
double atom3853;
double atom3618;
double atom3791;
double atom6759;
double atom6779;
double atom2439;
double atom4225;
double atom4702;
double atom6776;
double atom6781;
double atom4705;
double atom6767;
double atom6771;
double atom6772;
double atom6763;
double atom6784;
double atom6745;
double atom6749;
double atom6753;
double atom6756;
double atom6790;
double atom6793;
double atom6797;
double atom6804;
double atom6911;
double atom6912;
double atom6899;
double atom6902;
double atom6905;
double atom6806;
double atom3840;
double atom6851;
double atom6852;
double atom6841;
double atom6842;
double atom6830;
double atom6855;
double atom6820;
double atom6814;
double atom6815;
double atom6824;
double atom6859;
double atom6862;
double atom3819;
double atom6868;
double atom6877;
double atom3821;
double atom6882;
double atom6883;
double atom6889;
double atom6921;
double atom3854;
double atom6931;
double atom6939;
double atom3855;
double atom6950;
double atom6989;
double atom6944;
double atom6994;
double atom7019;
double atom7020;
double atom6997;
double atom6977;
double atom6981;
double atom7009;
double atom6952;
double atom6946;
double atom6970;
double atom6955;
double atom6936;
double atom6960;
double atom6972;
double atom7025;
double atom7001;
double atom7003;
double atom7039;
double atom7040;
double atom7034;
double atom7035;
double atom7049;
double atom4699;
double atom7066;
double atom4698;
double atom7070;
double atom7073;
double atom7061;
double atom7133;
double atom7085;
double atom7076;
double atom7137;
double atom7087;
double atom4869;
double atom7092;
double atom7093;
double atom7105;
double atom7099;
double atom7108;
double atom7111;
double atom7112;
double atom7117;
double atom7122;
double atom7123;
double atom7127;
double atom7146;
double atom7161;
double atom7159;
double atom7170;
double atom7156;
double atom7157;
double atom7164;
double atom7166;
double atom7198;
double atom7194;
double atom7207;
double atom7172;
double atom4670;
double atom4672;
double atom7176;
double atom4673;
double atom4691;
double atom7174;
double atom7178;
double atom7179;
double atom7183;
double atom4921;
double atom7188;
double atom7217;
double atom7218;
double atom7221;
double atom4668;
double atom7227;
double atom4675;
double atom7232;
double atom4870;
double atom7223;
double atom7240;
double atom7236;
double atom7249;
double atom8855;
double atom7265;
double atom7276;
double atom7285;
double atom7294;
double atom7302;

double * _Mrecsubs = NULL;
void Init_Mrecsubs ( ) 
{
    _Mrecsubs = malloc ( Mrecsubs_n_rows * Mrecsubs_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Mrecsubs_n_rows * Mrecsubs_n_cols ; i++ ) {_Mrecsubs[i]=0.0;}
  }
}

void Done_Mrecsubs ( ) 
{
if (_Mrecsubs != NULL) 
free (_Mrecsubs ); 
_Mrecsubs = NULL; 
}


double * Mrecsubs ()
{
if ( _Mrecsubs == NULL )
 {
    _Mrecsubs = malloc ( Mrecsubs_n_rows * Mrecsubs_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Mrecsubs_n_rows * Mrecsubs_n_cols ; i++ ) {_Mrecsubs[i]=0.0;}
  }
 }

atom35 = cos(a2);
atom36 = sin(a2);
atom57 =  a3+a2;
atom59 = sin(atom57);
atom58 = cos(atom57);
atom3607 =  atom59*atom36+atom58*atom35;
atom3610 =  atom58*atom36-atom35*atom59;
atom5612 =  atom35*atom3610-atom36*atom3607;
atom5616 = -atom36*atom3610-atom35*atom3607;
atom3603 = -atom35*r3;
atom3604 = r3*atom36;
atom3613 = -atom3610*atom3604+atom3603*atom3607;
atom532 = atom35*d3;
atom81 = sin(a4);
atom6494 =  atom532-d4*atom5616-atom5612*r4;
atom80 = cos(a4);
atom6497 =  atom3613*atom80+atom81*atom6494;
atom6537 =  atom6494*atom80-atom81*atom3613;
atom6502 = -atom81*atom5612;
atom6504 = atom5612*atom80;
atom3616 =  atom3607*atom3604+atom3603*atom3610;
atom115 = sin(a5);
atom114 = cos(a5);
atom6526 =  atom3616*atom115+atom114*atom6497;
atom6507 =  atom114*atom6504+atom115*atom5616;
atom6530 =  atom114*atom5616-atom115*atom6504;
atom152 = cos(a6);
atom153 = sin(a6);
atom6509 =  atom152*atom6507+atom6502*atom153;
atom6513 =  atom6502*atom152-atom6507*atom153;
atom6540 =  atom6537*atom153+atom6526*atom152;
atom6552 = -atom6526*atom153+atom6537*atom152;
atom6593 =  Izz6*atom6513+atom6552*mx6-atom6530*Izz6-my6*atom6540+Ixz6*atom6509;
atom6603 =  atom6502*Iyz5-atom6593+atom6507*Ixy5+mz5*atom6526-atom6537*mx5+atom6530*Iyy5;
atom6500 = -atom6497*atom115+atom114*atom3616;
atom6632 = -atom6530*Iyz6+mx6*atom6500+mz6*atom6540+Iyy6*atom6513+Ixy6*atom6509;
atom6622 =  Ixy6*atom6513-atom6552*mz6-atom6530*Ixz6-my6*atom6500+atom6509*Ixx6;
atom6635 = -mz5*atom6500+atom152*atom6622+atom6530*Ixy5-atom153*atom6632+atom6537*my5+atom6507*Ixx5+Ixz5*atom6502;
atom6647 =  atom6537*mx4-atom115*atom6635+Ixz4*atom6504+Izz4*atom6502-my4*atom6497-atom114*atom6603-Izz4*atom5616;
atom6554 =  atom6552*m6-mz6*atom6509-atom6530*mx6;
atom6545 =  m6*atom6540+mz6*atom6513+my6*atom6530;
atom6581 = -mz4*atom6504+atom6537*m5+atom6507*my5-atom5616*mx4+atom6537*m4+atom6545*atom153-atom6530*mx5+atom6554*atom152;
atom6522 =  atom6513*mx6-mz5*atom6507+m5*atom6500+m6*atom6500-my6*atom6509+atom6502*mx5;
atom6557 = -atom6554*atom153+atom152*atom6545+atom6530*mz5-atom6502*my5+m5*atom6526;
atom6565 =  atom6497*m4+my4*atom5616+atom114*atom6557+atom6502*mz4-atom115*atom6522;
atom6583 =  atom6581*atom80+atom81*atom6565;
atom6650 = -atom6583*d4+atom5612*Ixy3-atom532*mx3+Iyy3*atom5616-atom6647+mz3*atom3613;
atom6664 =  Ixy4*atom6502+atom114*atom6635-Ixz4*atom5616+atom6504*Ixx4-atom6537*mz4-atom115*atom6603-atom3616*my4;
atom6687 =  atom152*atom6632+atom153*atom6622+Ixz5*atom6507+atom6530*Izz5+Izz5*atom6502-atom6526*my5+mx5*atom6500;
atom6688 =  atom6502*Iyy4+atom3616*mx4+atom6687-atom5616*Iyz4+Ixy4*atom6504+atom6497*mz4;
atom6694 =  atom6664*atom80-atom3616*mz3-atom6583*r4+atom5612*Ixx3+atom5616*Ixy3-atom81*atom6688+my3*atom532;
atom6713 = -atom6502*mx4+my4*atom6504-atom115*atom6557-atom3616*m4-atom114*atom6522;
atom6717 =  atom3616*m3-atom5612*mz3-atom6713;
atom6724 = -atom81*atom6581+atom6565*atom80;
atom6725 =  m3*atom3613+atom6724+mz3*atom5616;
atom6734 = -atom6725*atom3610+atom6717*atom3607;
atom3617 = -atom3610*d3;
atom3792 = -atom3617-r4;
atom3852 = -atom3792*atom80;
atom6788 = mz4*atom80;
atom3853 = atom81*atom3792;
atom3618 = atom3607*d3;
atom3791 =  d4+atom3618;
atom6759 =  atom114*atom3852+atom115*atom3791;
atom6779 =  atom3853*atom152-atom6759*atom153;
atom2439 = atom81*atom115;
atom4225 = atom81*atom114;
atom4702 =  atom152*atom4225+atom153*atom80;
atom6776 =  atom2439*mx6-mz6*atom4702;
atom6781 =  m6*atom6779+atom6776;
atom4705 =  atom152*atom80-atom153*atom4225;
atom6767 =  atom6759*atom152+atom3853*atom153;
atom6771 = -my6*atom2439+atom4705*mz6;
atom6772 =  atom6767*m6+atom6771;
atom6763 = -mz5*atom2439-atom80*my5;
atom6784 =  atom6763+atom6772*atom152-atom153*atom6781+atom6759*m5;
atom6745 = -atom115*atom3852+atom114*atom3791;
atom6749 =  my6*atom4702-atom4705*mx6;
atom6753 = -mz5*atom4225+mx5*atom80;
atom6756 =  atom6753+m6*atom6745+m5*atom6745-atom6749;
atom6790 =  atom6788-atom115*atom6756+atom3852*m4+atom114*atom6784;
atom6793 = -atom81*mz4;
atom6797 =  atom2439*mx5+atom4225*my5;
atom6804 =  atom6797+atom152*atom6781+atom3853*m5+atom6793+atom6772*atom153+atom3853*m4;
atom6911 = -atom81*atom6804+atom6790*atom80;
atom6912 = -my3+m3*atom3617+atom6911;
atom6899 = -atom80*mx4+atom81*my4;
atom6902 = -atom114*atom6756+atom6899-atom115*atom6784-atom3791*m4;
atom6905 =  mx3-atom6902+m3*atom3618;
atom6806 =  atom6804*atom80+atom81*atom6790;
atom3840 =  Izz4*atom80+atom81*Ixz4;
atom6851 =  atom2439*Iyz6+atom4705*Iyy6+Ixy6*atom4702;
atom6852 =  atom6767*mz6+atom6851+atom6745*mx6;
atom6841 =  Ixz6*atom2439+Ixx6*atom4702+Ixy6*atom4705;
atom6842 = -mz6*atom6779-my6*atom6745+atom6841;
atom6830 = -atom2439*Ixy5+Ixx5*atom4225+Ixz5*atom80;
atom6855 =  atom6830+atom3853*my5+atom6842*atom152-atom153*atom6852-mz5*atom6745;
atom6820 =  atom80*Iyz5+atom4225*Ixy5-atom2439*Iyy5;
atom6814 =  Izz6*atom2439+Ixz6*atom4702+atom4705*Izz6;
atom6815 =  atom6814+atom6779*mx6-atom6767*my6;
atom6824 =  atom6759*mz5+atom6820-atom3853*mx5-atom6815;
atom6859 =  atom3840+atom3853*mx4-my4*atom3852-atom114*atom6824-atom115*atom6855;
atom6862 = -atom6859+mz3*atom3617-d4*atom6806+Iyz3;
atom3819 =  Ixy4*atom80+atom81*Ixx4;
atom6868 = -atom3853*mz4-atom6824*atom115-my4*atom3791+atom3819+atom114*atom6855;
atom6877 =  Izz5*atom80-Izz5*atom2439+Ixz5*atom4225;
atom3821 =  atom81*Ixy4+Iyy4*atom80;
atom6882 = -atom6759*my5+atom6745*mx5+atom152*atom6852+atom6877+atom6842*atom153;
atom6883 =  atom3821+atom3791*mx4+atom6882+mz4*atom3852;
atom6889 =  atom80*atom6868-atom81*atom6883-mz3*atom3618+Ixz3-r4*atom6806;
atom6921 =  atom6905*atom3607-atom6912*atom3610;
atom3854 = r4*atom80;
atom6931 =  atom114*d4-atom115*atom3854;
atom6939 =  atom115*d4+atom114*atom3854;
atom3855 = -atom81*r4;
atom6950 = -atom6939*atom153+atom3855*atom152;
atom6989 = -my6*atom6931-mz6*atom6950+atom6841;
atom6944 =  atom3855*atom153+atom6939*atom152;
atom6994 =  atom6944*mz6+mx6*atom6931+atom6851;
atom7019 = -atom6939*my5+atom152*atom6994+atom6989*atom153+mx5*atom6931+atom6877;
atom7020 =  atom7019+atom3821+d4*mx4+mz4*atom3854;
atom6997 =  atom6830+atom152*atom6989-mz5*atom6931-atom6994*atom153+atom3855*my5;
atom6977 =  atom6950*mx6+atom6814-my6*atom6944;
atom6981 =  mz5*atom6939-atom3855*mx5-atom6977+atom6820;
atom7009 = -atom115*atom6981+atom114*atom6997-my4*d4-atom3855*mz4+atom3819;
atom6952 =  m6*atom6950+atom6776;
atom6946 =  atom6944*m6+atom6771;
atom6970 =  atom3855*m4+atom6797+atom152*atom6952+atom6793+atom6946*atom153+m5*atom3855;
atom6955 =  atom6946*atom152+atom6763+atom6939*m5-atom6952*atom153;
atom6936 =  atom6753-atom6749+m6*atom6931+m5*atom6931;
atom6960 =  atom6788-atom115*atom6936+m4*atom3854+atom114*atom6955;
atom6972 =  atom80*atom6970+atom81*atom6960;
atom7025 =  atom80*atom7009-atom81*atom7020+Ixz3-atom6972*r4;
atom7001 =  atom3840-atom114*atom6981+atom3855*mx4-atom6997*atom115-my4*atom3854;
atom7003 = -atom6972*d4-atom7001+Iyz3;
atom7039 = -atom81*atom6970+atom6960*atom80;
atom7040 = -my3+atom7039;
atom7034 = -d4*m4-atom114*atom6936+atom6899-atom115*atom6955;
atom7035 =  mx3-atom7034;
atom7049 =  atom7035*atom3607-atom7040*atom3610;
atom4699 = -atom115*atom153;
atom7066 = -atom4699*mz6-atom114*my6;
atom4698 = atom115*atom152;
atom7070 =  atom114*mx6+mz6*atom4698;
atom7073 =  atom152*atom7066-atom153*atom7070-atom114*mz5;
atom7061 =  mz5*atom115+my6*atom4698-atom4699*mx6;
atom7133 = -atom114*atom7061-atom115*atom7073;
atom7085 =  atom152*atom7070-atom115*my5+atom7066*atom153+atom114*mx5+mx4;
atom7076 = -atom115*atom7061-my4+atom114*atom7073;
atom7137 =  atom7076*atom80-atom81*atom7085;
atom7087 =  atom7085*atom80+atom81*atom7076;
atom4869 = atom114*Izz6;
atom7092 = -atom4699*Izz6-Ixz6*atom4698+atom4869;
atom7093 = -atom115*Ixy5-atom114*Iyy5-atom7092;
atom7105 =  atom114*Iyz6-Ixy6*atom4698-atom4699*Iyy6;
atom7099 = -atom4698*Ixx6+atom114*Ixz6-Ixy6*atom4699;
atom7108 = -atom114*Ixy5-atom7105*atom153+atom152*atom7099-atom115*Ixx5;
atom7111 =  Izz4-atom114*atom7093-atom115*atom7108;
atom7112 = -atom7111-d4*atom7087;
atom7117 =  Ixz4-atom115*atom7093+atom114*atom7108;
atom7122 =  atom152*atom7105-atom114*Izz5+atom153*atom7099-Ixz5*atom115;
atom7123 =  Iyz4+atom7122;
atom7127 =  atom7117*atom80-atom7087*r4-atom81*atom7123;
atom7146 = -atom7133*atom3607-atom7137*atom3610;
atom7161 = -mz6*atom153;
atom7159 = mz6*atom152;
atom7170 =  atom7161*atom152+atom7159*atom153;
atom7156 =  my6*atom153-atom152*mx6;
atom7157 = -atom7156+mx5;
atom7164 =  atom7159*atom152-atom7161*atom153-my5;
atom7166 =  atom114*atom7164-atom7157*atom115;
atom7198 =  atom7166*atom80-atom81*atom7170;
atom7194 = -atom115*atom7164-atom114*atom7157;
atom7207 = -atom7198*atom3610-atom7194*atom3607;
atom7172 =  atom7170*atom80+atom81*atom7166;
atom4670 =  atom153*Ixx6+Ixy6*atom152;
atom4672 =  atom152*Iyy6+Ixy6*atom153;
atom7176 =  Ixz5-atom4672*atom153+atom152*atom4670;
atom4673 = Ixz6*atom153;
atom4691 =  Izz6*atom152+atom4673;
atom7174 =  Iyz5-atom4691;
atom7178 = -atom115*atom7176-atom114*atom7174;
atom7179 = -atom7178-d4*atom7172;
atom7183 =  atom114*atom7176-atom115*atom7174;
atom4921 = -atom4672*atom152-Izz5-atom153*atom4670;
atom7188 = -atom7172*r4+atom81*atom4921+atom7183*atom80;
atom7217 = -my6*atom152-atom153*mx6;
atom7218 = atom114*atom7217;
atom7221 =  atom81*atom7218-atom7156*atom80;
atom4668 =  Ixz6*atom152-atom153*Iyz6;
atom7227 =  atom114*atom4668+Izz6*atom115;
atom4675 =  atom152*Iyz6+atom4673;
atom7232 = -atom7221*r4-atom81*atom4675+atom7227*atom80;
atom4870 = -atom115*atom4668+atom4869;
atom7223 = -atom4870-atom7221*d4;
atom7240 =  atom7218*atom80+atom81*atom7156;
atom7236 = -atom115*atom7217;
atom7249 = -atom7236*atom3607-atom7240*atom3610;
atom8855 =  Izz3*atom5616+atom81*atom6664+atom6724*r4+atom5612*Ixz3-d4*atom6713+atom6688*atom80+atom3616*mx3-my3*atom3613;
atom7265 =  atom3618*mx3+Izz3+atom6883*atom80+atom81*atom6868-d4*atom6902-my3*atom3617+atom6911*r4;
atom7276 =  r4*atom7039+atom7020*atom80+Izz3+atom81*atom7009-d4*atom7034;
atom7285 =  atom7117*atom81+atom7123*atom80+atom7137*r4-d4*atom7133;
atom7294 = -d4*atom7194-atom80*atom4921+atom7198*r4+atom81*atom7183;
atom7302 =  atom7240*r4+atom80*atom4675+atom81*atom7227-d4*atom7236;

_Mrecsubs[0] =  Izz1+atom35*( atom36*Ixy2+atom35*Iyy2-atom3607*atom6650-( atom5616*mx3-atom6583-my3*atom5612-atom532*m3)*d3+atom6694*atom3610-r3*( atom6717*atom3610+atom6725*atom3607))+atom36*( atom35*Ixy2+r3*atom6734-atom6694*atom3607-atom3610*atom6650+atom36*Ixx2);
_Mrecsubs[1] =  atom8855-Ixz2*atom36+atom6734*d3-atom35*Izz2;
_Mrecsubs[2] = atom8855;
_Mrecsubs[3] = atom6647;
_Mrecsubs[4] = atom6687;
_Mrecsubs[5] = atom6593;
_Mrecsubs[6] = -atom36*( Ixz2+atom6889*atom3607+atom6862*atom3610-r3*atom6921)+atom35*( d3*atom6806-r3*( atom6905*atom3610+atom6912*atom3607)-atom6862*atom3607-Iyz2+atom6889*atom3610);
_Mrecsubs[7] =  Izz2+atom6921*d3+atom7265;
_Mrecsubs[8] = atom7265;
_Mrecsubs[9] = atom6859;
_Mrecsubs[10] = atom6882;
_Mrecsubs[11] = atom6815;
_Mrecsubs[12] = -atom36*( atom7025*atom3607+atom7003*atom3610-r3*atom7049)+atom35*( atom6972*d3+atom7025*atom3610-r3*( atom7035*atom3610+atom7040*atom3607)-atom7003*atom3607);
_Mrecsubs[13] =  atom7276+atom7049*d3;
_Mrecsubs[14] = atom7276;
_Mrecsubs[15] = atom7001;
_Mrecsubs[16] = atom7019;
_Mrecsubs[17] = atom6977;
_Mrecsubs[18] =  atom35*( atom7127*atom3610-atom3607*atom7112+r3*( atom7133*atom3610-atom7137*atom3607)+atom7087*d3)+( r3*atom7146-atom3610*atom7112-atom3607*atom7127)*atom36;
_Mrecsubs[19] =  atom7285+d3*atom7146;
_Mrecsubs[20] = atom7285;
_Mrecsubs[21] = atom7111;
_Mrecsubs[22] = atom7122;
_Mrecsubs[23] = atom7092;
_Mrecsubs[24] =  ( atom7172*d3-atom7179*atom3607+atom3610*atom7188-r3*( atom7198*atom3607-atom7194*atom3610))*atom35-( atom3607*atom7188-r3*atom7207+atom7179*atom3610)*atom36;
_Mrecsubs[25] =  atom7294+atom7207*d3;
_Mrecsubs[26] = atom7294;
_Mrecsubs[27] = atom7178;
_Mrecsubs[28] = -atom4921;
_Mrecsubs[29] = atom4691;
_Mrecsubs[30] =  atom35*( r3*( atom7236*atom3610-atom7240*atom3607)+atom7232*atom3610+atom7221*d3-atom3607*atom7223)-( atom3607*atom7232-atom7249*r3+atom7223*atom3610)*atom36;
_Mrecsubs[31] =  atom7249*d3+atom7302;
_Mrecsubs[32] = atom7302;
_Mrecsubs[33] = atom4870;
_Mrecsubs[34] = atom4675;
_Mrecsubs[35] = Izz6;

return _Mrecsubs;
}

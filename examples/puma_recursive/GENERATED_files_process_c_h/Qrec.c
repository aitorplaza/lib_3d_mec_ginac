/*----------Qrec.c lib3D_MEC exported-----------*/

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

#include "Qrec.h"

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
double atom2579;
double atom2450;
double atom2582;
double atom2449;
double atom4502;
double atom4652;
double atom443;
double atom4503;
double atom80;
double atom81;
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
double atom4435;
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
double atom152;
double atom4778;
double atom115;
double atom114;
double atom4774;
double atom153;
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
double atom5295;
double atom5296;
double atom5276;
double atom5284;
double atom5446;
double atom4465;
double atom4467;
double atom5256;
double atom4577;
double atom4580;
double atom4590;
double atom4617;
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
double atom4736;
double atom4731;
double atom5423;
double atom5432;
double atom4581;
double atom4612;
double atom4585;
double atom4741;
double atom5378;
double atom5393;
double atom5404;
double atom5408;
double atom4462;
double atom4623;
double atom5467;

double * _Qrec = NULL;
void Init_Qrec ( ) 
{
    _Qrec = malloc ( Qrec_n_rows * Qrec_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Qrec_n_rows * Qrec_n_cols ; i++ ) {_Qrec[i]=0.0;}
  }
}

void Done_Qrec ( ) 
{
if (_Qrec != NULL) 
free (_Qrec ); 
_Qrec = NULL; 
}


double * Qrec ()
{
if ( _Qrec == NULL )
 {
    _Qrec = malloc ( Qrec_n_rows * Qrec_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Qrec_n_rows * Qrec_n_cols ; i++ ) {_Qrec[i]=0.0;}
  }
 }

atom57 =  a3+a2;
atom58 = cos(atom57);
atom35 = cos(a2);
atom59 = sin(atom57);
atom36 = sin(a2);
atom2579 =  atom59*atom36+atom58*atom35;
atom2450 = -atom35*da1;
atom2582 = -atom35*atom59+atom58*atom36;
atom2449 = -atom36*da1;
atom4502 =  atom2579*atom2450+atom2582*atom2449;
atom4652 = -atom4502+da4;
atom443 = da3;
atom4503 =  atom443+da2;
atom80 = cos(a4);
atom81 = sin(a4);
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
atom4435 = -atom36*g;
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
atom152 = cos(a6);
atom4778 =  da5+atom4651;
atom115 = sin(a5);
atom114 = cos(a5);
atom4774 = -atom115*atom4652+atom114*atom4648;
atom153 = sin(a6);
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
atom5295 = -atom81*atom5254+atom5232*atom80;
atom5296 =  mx3*atom4516+m3*atom5113+atom4517*my3+mz3*( atom5125+atom4518)+atom5295;
atom5276 =  ( atom5150+atom4671)*my4-atom115*atom5229-mz4*( atom4669+atom4665)-mx4*( atom5137-atom4668)-atom5184*atom114-m4*atom5162;
atom5284 = -mz3*( atom5119-atom4521)+atom4517*mx3+my3*atom4520+m3*atom5159-atom5276;
atom5446 =  atom2579*atom5284-atom5296*atom2582;
atom4465 =  da2*Iyz2+Ixy2*atom2449+Iyy2*atom2450;
atom4467 =  Iyz2*atom2450+Ixz2*atom2449+da2*Izz2;
atom5256 =  atom80*atom5254+atom5232*atom81;
atom4577 = atom4502*Ixy3;
atom4580 =  atom4577+Ixx3*atom4499+Ixz3*atom4503;
atom4590 =  Ixz3*atom4499+atom4503*Izz3+atom4502*Iyz3;
atom4617 =  atom4577-Iyy3*atom4499;
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
atom4736 =  atom4648*Ixy4+atom4651*Iyy4+Iyz4*atom4652;
atom4731 =  Ixz4*atom4652+atom4648*Ixx4+atom4651*Ixy4;
atom5423 =  atom4736*atom4648-atom4651*atom4731+atom5203*mx4-atom114*atom5330-Izz4*atom5125-atom5134*my4+Ixz4*atom5150+atom5137*Iyz4-atom115*atom5365;
atom5432 = -atom5256*d4-atom4499*atom4590+atom4580*atom4503+atom4617*da3+atom4617*da2+mz3*atom5113-mx3*atom5131-atom5423;
atom4581 = atom4499*Ixy3;
atom4612 =  atom4502*Ixx3-atom4581;
atom4585 =  atom4502*Iyy3+atom4581+atom4503*Iyz3;
atom4741 =  Ixz4*atom4648+Izz4*atom4652+atom4651*Iyz4;
atom5378 = -atom4736*atom4652-Ixz4*atom5125-atom5162*my4+atom4741*atom4651+atom5137*Ixy4-atom115*atom5330-mz4*atom5203+atom5150*Ixx4+atom114*atom5365;
atom5393 =  Izz5*atom5137+atom152*atom5362-atom4777*atom4845+atom4774*atom4850-atom5188*my5+atom5165*mx5+atom5153*Ixz5+atom5193*Iyz5+atom5351*atom153;
atom5404 =  atom5393+atom5137*Iyy4+mz4*atom5134+atom4652*atom4731-atom4741*atom4648-Iyz4*atom5125+atom5150*Ixy4+mx4*atom5162;
atom5408 =  my3*atom5131-atom81*atom5404+atom80*atom5378-atom4503*atom4585-atom5256*r4+atom4612*da2+atom4502*atom4590+atom4612*da3-mz3*atom5159;
atom4462 =  Ixy2*atom2450+Ixx2*atom2449+da2*Ixz2;
atom4623 = -atom4499*Iyz3+Ixz3*atom4502;
atom5467 =  atom4623*da2+atom5404*atom80+atom5295*r4+atom4499*atom4585+atom81*atom5378+atom4623*da3-atom5113*my3+atom5159*mx3-d4*atom5276-atom4502*atom4580;

_Qrec[0] = -( Ixx2*atom2486-atom4465*da2-atom4436*mz2+atom2579*atom5408+atom4467*atom2450+atom2582*atom5432-atom2485*Ixy2-r3*atom5446)*atom36-atom35*( atom4435*mz2+r3*( atom2582*atom5284+atom5296*atom2579)+Ixy2*atom2486+da2*atom4462-( atom5256+atom5126*mx3+atom5120*my3+m3*atom5131-mz3*( atom4519+atom4515))*d3-Iyy2*atom2485-atom2582*atom5408-atom4467*atom2449+atom2579*atom5432);
_Qrec[1] =  atom5467-atom4462*atom2450+atom2486*Ixz2-atom2485*Iyz2+atom4465*atom2449-atom4435*my2+atom4436*mx2+atom5446*d3;
_Qrec[2] = atom5467;
_Qrec[3] = atom5423;
_Qrec[4] = atom5393;
_Qrec[5] = atom5329;

return _Qrec;
}

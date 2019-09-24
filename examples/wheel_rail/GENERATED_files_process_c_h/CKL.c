/*----------CKL.c lib3D_MEC exported-----------*/

/* CMO exported */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "time_3D_mec.h"
#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
#include "gen_auxcoord.h"
#include "gen_auxvel.h"
#include "gen_auxaccel.h"
#include "param.h"
#include "unknowns.h"
#include "inputs.h"

#include "step.h"

#include "CKL.h"

#define x q[ 0 ]
#define y q[ 1 ]
#define b q[ 2 ]
#define c q[ 3 ]
#define z q[ 4 ]
#define a q[ 5 ]
#define dx dq[ 0 ]
#define dy dq[ 1 ]
#define db dq[ 2 ]
#define dc dq[ 3 ]
#define dz dq[ 4 ]
#define da dq[ 5 ]
#define ddx ddq[ 0 ]
#define ddy ddq[ 1 ]
#define ddb ddq[ 2 ]
#define ddc ddq[ 3 ]
#define ddz ddq[ 4 ]
#define dda ddq[ 5 ]
#define thetaW_R qaux[ 0 ]
#define uW_R qaux[ 1 ]
#define uR_R qaux[ 2 ]
#define sR_R qaux[ 3 ]
#define thetaW_L qaux[ 4 ]
#define uW_L qaux[ 5 ]
#define uR_L qaux[ 6 ]
#define sR_L qaux[ 7 ]
#define dthetaW_R dqaux[ 0 ]
#define duW_R dqaux[ 1 ]
#define duR_R dqaux[ 2 ]
#define dsR_R dqaux[ 3 ]
#define dthetaW_L dqaux[ 4 ]
#define duW_L dqaux[ 5 ]
#define duR_L dqaux[ 6 ]
#define dsR_L dqaux[ 7 ]
#define ddthetaW_R ddqaux[ 0 ]
#define dduW_R ddqaux[ 1 ]
#define dduR_R ddqaux[ 2 ]
#define ddsR_R ddqaux[ 3 ]
#define ddthetaW_L ddqaux[ 4 ]
#define dduW_L ddqaux[ 5 ]
#define dduR_L ddqaux[ 6 ]
#define ddsR_L ddqaux[ 7 ]
#define g param[ 0 ]
#define a_pend param[ 1 ]
#define b_pend param[ 2 ]
#define L_R param[ 3 ]
#define L_WHS param[ 4 ]
#define a_rail param[ 5 ]
#define mWHS param[ 6 ]
#define I_WHSx param[ 7 ]
#define I_WHSy param[ 8 ]
#define I_WHSz param[ 9 ]
#define tor param[ 10 ]
#define asR param[ 11 ]
#define bsR param[ 12 ]
#define csR param[ 13 ]
#define dsR param[ 14 ]
#define esR param[ 15 ]
#define fsR param[ 16 ]
#define stasR param[ 17 ]
#define endsR param[ 18 ]
#define usRz param[ 19 ]
#define aW_R param[ 20 ]
#define bW_R param[ 21 ]
#define cW_R param[ 22 ]
#define dW_R param[ 23 ]
#define lW_R param[ 24 ]
#define aR_R param[ 25 ]
#define bR_R param[ 26 ]
#define cR_R param[ 27 ]
#define dR_R param[ 28 ]
#define lR_R param[ 29 ]
#define asL param[ 30 ]
#define bsL param[ 31 ]
#define csL param[ 32 ]
#define dsL param[ 33 ]
#define esL param[ 34 ]
#define fsL param[ 35 ]
#define stasL param[ 36 ]
#define endsL param[ 37 ]
#define usLz param[ 38 ]
#define aW_L param[ 39 ]
#define bW_L param[ 40 ]
#define cW_L param[ 41 ]
#define dW_L param[ 42 ]
#define lW_L param[ 43 ]
#define aR_L param[ 44 ]
#define bR_L param[ 45 ]
#define cR_L param[ 46 ]
#define dR_L param[ 47 ]
#define lR_L param[ 48 ]
#define E_elastic param[ 49 ]
#define nu_poisson param[ 50 ]
#define G_elastic param[ 51 ]
#define aR param[ 52 ]
#define bR param[ 53 ]
#define aL param[ 54 ]
#define bL param[ 55 ]
#define C11R param[ 56 ]
#define C22R param[ 57 ]
#define C23R param[ 58 ]
#define C33R param[ 59 ]
#define C11L param[ 60 ]
#define C22L param[ 61 ]
#define C23L param[ 62 ]
#define C33L param[ 63 ]
#define y0 param[ 64 ]
#define b0 param[ 65 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define Fx_R inputs[ 0 ]
#define Fy_R inputs[ 1 ]
#define Mz_R inputs[ 2 ]
#define Fx_L inputs[ 3 ]
#define Fy_L inputs[ 4 ]
#define Mz_L inputs[ 5 ]

double atom566;
double atom567;
double atom569;
double atom571;
double atom573;
double atom578;
double atom581;
double atom584;
double atom587;
double atom590;
double atom592;
double atom593;
double atom605;
double atom609;
double atom601;
double atom614;
double atom619;
double atom625;
double atom623;
double atom634;
double atom642;
double atom9;
double atom644;
double atom10;
double atom8;
double atom11;
double atom643;
double atom1612;
double atom7;
double atom1608;
double atom13;
double atom1617;
double atom1619;
double atom1906;
double atom557;
double atom558;
double atom559;
double atom628;
double atom647;
double atom648;
double atom1620;
double atom12;
double atom1624;
double atom14;
double atom1629;
double atom1631;
double atom1907;
double atom497;
double atom503;
double atom6;
double atom4;
double atom506;
double atom145;
double atom3;
double atom144;
double atom5;
double atom504;
double atom307;
double atom922;
double atom146;
double atom147;
double atom923;
double atom984;
double atom924;
double atom981;
double atom1898;
double atom978;
double atom1889;
double atom630;
double atom629;
double atom636;
double atom637;
double atom638;
double atom639;
double atom1909;
double atom1118;
double atom1910;
double atom1899;
double atom1892;
double atom1031;
double atom1895;
double atom1902;
double atom1905;
double atom1634;
double atom1911;
double atom1637;
double atom1912;
double atom1913;
double atom1645;
double atom1914;
double atom16;
double atom1666;
double atom22;
double atom1672;
double atom28;
double atom1662;
double atom1675;
double atom1655;
double atom1657;
double atom1917;
double atom1920;
double atom1919;
double atom1922;
double atom2;
double atom1;
double atom71;
double atom156;
double atom159;
double atom72;
double atom1382;
double atom150;
double atom153;
double atom1389;
double atom1473;
double atom1376;
double atom1470;
double atom1467;
double atom1923;
double atom1685;
double atom15;
double atom34;
double atom19;
double atom40;
double atom46;
double atom25;
double atom1690;
double atom1697;
double atom1700;
double atom1926;
double atom1929;
double atom1930;
double atom1931;
double atom1932;
double atom1406;
double atom1415;
double atom1487;
double atom1410;
double atom1484;
double atom1490;
double atom1933;
double atom1713;
double atom1710;
double atom1936;
double atom1939;

double * _CKL = NULL;
void Init_CKL ( ) 
{
    _CKL = malloc ( CKL_n_rows * CKL_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKL_n_rows * CKL_n_cols ; i++ ) {_CKL[i]=0.0;}
  }
}

void Done_CKL ( ) 
{
if (_CKL != NULL) 
free (_CKL ); 
_CKL = NULL; 
}


double * CKL ()
{
if ( _CKL == NULL )
 {
    _CKL = malloc ( CKL_n_rows * CKL_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKL_n_rows * CKL_n_cols ; i++ ) {_CKL[i]=0.0;}
  }
 }

atom566 = 1.0/( endsL-stasL);
atom567 = ( sR_L-stasL)*atom566;
atom569 =  bsL+atom567*asL;
atom571 =  atom567*atom569+csL;
atom573 =  atom567*atom571+dsL;
atom578 = atom566*asL;
atom581 =  atom567*atom578+atom569*atom566;
atom584 =  atom571*atom566+atom581*atom567;
atom587 =  atom573*atom566+atom584*atom567;
atom590 =  ( esL+atom567*atom573)*atom566+atom567*atom587;
atom592 =  (atom590*atom590)+1.0;
atom593 = pow(atom592,(1.0/2.0));
atom605 = atom581*atom566;
atom609 = atom584*atom566;
atom601 = atom587*atom566;
atom614 =  2.0*( atom567*( atom605+atom567*atom578*atom566)+atom609)*atom567+2.0*atom601;
atom619 = -1.0/(atom593*atom593)*atom614*atom590*pow(atom592,-(1.0/2.0));
atom625 =  atom590+5.0000000000000000e-01*L_R*atom619;
atom623 =  -5.0000000000000000e-01*atom590*L_R*atom619+-5.0000000000000000e-01*1.0/atom593*atom614*L_R+1.0;
atom634 = (atom623*atom623);
atom642 = pow( atom634+(atom625*atom625),-(1.0/2.0));
atom9 = cos(a_pend);
atom644 = atom625*atom642;
atom10 = sin(a_pend);
atom8 = sin(b_pend);
atom11 = atom10*atom8;
atom643 = atom642*atom623;
atom1612 =  atom11*atom643+atom9*atom644;
atom7 = cos(b_pend);
atom1608 = atom7*atom643;
atom13 = -atom9*atom8;
atom1617 =  atom13*atom643+atom10*atom644;
atom1619 =  atom13*atom1617+atom1612*atom11+atom1608*atom7;
atom1906 = -C11L*aL*G_elastic*atom1619*bL;
atom557 =  uR_L-lR_L;
atom558 = aR_L*atom557;
atom559 =  bR_L+atom558;
atom628 =  atom559*atom557+cR_L+( atom559+atom558)*atom557;
atom647 = pow( (atom628*atom628)+1.0,-(1.0/2.0));
atom648 = atom647*atom628;
atom1620 = atom648*atom8;
atom12 = -atom10*atom7;
atom1624 =  atom12*atom648+atom9*atom647;
atom14 = atom9*atom7;
atom1629 =  atom647*atom10+atom14*atom648;
atom1631 =  atom1624*atom11+atom1620*atom7+atom13*atom1629;
atom1907 = -atom1631*aL*G_elastic*C22L*bL;
atom497 =  uW_L-lW_L;
atom503 =  dW_L+atom497*( atom497*( atom497*aW_L+bW_L)+cW_L);
atom6 = sin(c);
atom4 = sin(a);
atom506 = cos(thetaW_L)*atom503;
atom145 = atom6*atom4;
atom3 = cos(a);
atom144 = -atom6*atom3;
atom5 = cos(c);
atom504 = -atom503*sin(thetaW_L);
atom307 = -5.0000000000000000e-01*L_WHS;
atom922 =  atom5*atom504+atom506*atom145-atom144*atom307+atom144*uW_L;
atom146 = atom5*atom3;
atom147 = -atom5*atom4;
atom923 = -atom307*atom146+uW_L*atom146+atom506*atom147+atom6*atom504;
atom984 =  atom144*atom923-atom922*atom146;
atom924 = -atom307*atom4+uW_L*atom4+atom506*atom3;
atom981 =  atom922*atom4-atom924*atom144;
atom1898 =  atom984*atom648+atom981*atom647;
atom978 = -atom4*atom923+atom924*atom146;
atom1889 =  atom981*atom644+atom978*atom643;
atom630 = -atom623*atom628;
atom629 = atom625*atom628;
atom636 = pow( atom634+(atom629*atom629)+(atom630*atom630),-(1.0/2.0));
atom637 = atom629*atom636;
atom638 = atom630*atom636;
atom639 = atom623*atom636;
atom1909 = pow(aL*bL,(1.0/2.0));
atom1118 =  atom637*atom144+atom639*atom4+atom638*atom146;
atom1910 = -atom1631*aL*G_elastic*bL*atom1909*C23L;
atom1899 = atom647*atom922;
atom1892 =  atom644*atom922-atom923*atom643;
atom1031 = -atom5*atom924;
atom1895 =  atom644*atom1031+atom924*atom6*atom643;
atom1902 =  ( atom5*atom923-atom6*atom922)*atom648+atom647*atom1031;
atom1905 =  atom5*atom637+atom638*atom6;
atom1634 =  atom1617*atom10+atom9*atom1612;
atom1911 = -atom1634*C11L*aL*G_elastic*bL;
atom1637 =  atom1629*atom10+atom9*atom1624;
atom1912 = -aL*G_elastic*C22L*bL*atom1637;
atom1913 = -aL*G_elastic*bL*atom1909*atom1637*C23L;
atom1645 =  atom1608*atom8+atom12*atom1612+atom14*atom1617;
atom1914 = -( atom978*atom1619+atom981*atom1634+atom1645*atom984)*C11L*aL*G_elastic*bL;
atom16 = -atom6*atom7;
atom1666 =  atom637*atom7+atom639*atom8;
atom22 = -atom6*atom11+atom5*atom9;
atom1672 =  atom637*atom11+atom638*atom9+atom12*atom639;
atom28 = -atom13*atom6+atom5*atom10;
atom1662 =  atom13*atom637+atom14*atom639+atom638*atom10;
atom1675 =  ( atom28*atom3+atom14*atom4)*atom1662+atom1672*( atom22*atom3+atom12*atom4)+( atom16*atom3+atom4*atom8)*atom1666;
atom1655 =  atom1620*atom8+atom14*atom1629+atom12*atom1624;
atom1657 =  atom1655*atom984+atom1631*atom978+atom981*atom1637;
atom1917 = -atom1657*aL*G_elastic*C22L*bL+aL*G_elastic*bL*atom1909*C23L*atom1675;
atom1920 = (bL*bL);
atom1919 = (aL*aL);
atom1922 = -atom1657*aL*G_elastic*bL*atom1909*C23L-atom1920*C33L*G_elastic*atom1919*atom1675;
atom2 = sin(b);
atom1 = cos(b);
atom71 = -atom2*atom3;
atom156 =  atom1*atom6-atom2*atom147;
atom159 =  atom2*atom6+atom1*atom147;
atom72 = atom1*atom3;
atom1382 =  atom4*atom146+atom159*atom72+atom71*atom156;
atom150 = -atom2*atom145+atom5*atom1;
atom153 =  atom5*atom2+atom1*atom145;
atom1389 =  atom144*atom4+atom72*atom153+atom71*atom150;
atom1473 =  atom1389*atom923-atom1382*atom922;
atom1376 =  (atom4*atom4)+(atom71*atom71)+(atom72*atom72);
atom1470 =  atom1376*atom922-atom924*atom1389;
atom1467 =  atom924*atom1382-atom1376*atom923;
atom1923 = -C11L*aL*G_elastic*( atom1619*atom1467+atom1473*atom1645+atom1470*atom1634)*bL;
atom1685 =  atom1631*atom1467+atom1470*atom1637+atom1473*atom1655;
atom15 = atom5*atom7;
atom34 =  atom3*atom8-atom16*atom4;
atom19 =  atom5*atom11+atom9*atom6;
atom40 =  atom12*atom3-atom22*atom4;
atom46 = -atom28*atom4+atom14*atom3;
atom25 =  atom5*atom13+atom10*atom6;
atom1690 =  atom1662*( atom25*atom2+atom1*atom46)+atom1672*( atom1*atom40+atom2*atom19)+( atom2*atom15+atom34*atom1)*atom1666;
atom1697 = -( atom34*atom2-atom1*atom15)*atom1666+atom1662*( atom1*atom25-atom2*atom46)-atom1672*( atom2*atom40-atom1*atom19);
atom1700 =  atom4*atom1675+atom71*atom1697+atom72*atom1690;
atom1926 =  atom1700*aL*G_elastic*bL*atom1909*C23L-aL*G_elastic*C22L*bL*atom1685;
atom1929 = -atom1920*C33L*atom1700*G_elastic*atom1919-aL*G_elastic*bL*atom1685*atom1909*C23L;
atom1930 = -C11L*aL*G_elastic*atom1645*bL;
atom1931 = -atom1655*aL*G_elastic*C22L*bL;
atom1932 = -atom1655*aL*G_elastic*bL*atom1909*C23L;
atom1406 =  atom2*atom72+atom1*atom71;
atom1415 =  atom1*atom150+atom2*atom153;
atom1487 = -atom924*atom1415+atom1406*atom922;
atom1410 =  atom1*atom156+atom2*atom159;
atom1484 =  atom924*atom1410-atom1406*atom923;
atom1490 = -atom1410*atom922+atom923*atom1415;
atom1933 = -( atom1634*atom1487+atom1490*atom1645+atom1619*atom1484)*C11L*aL*G_elastic*bL;
atom1713 =  atom1*atom1697+atom2*atom1690;
atom1710 =  atom1487*atom1637+atom1490*atom1655+atom1631*atom1484;
atom1936 =  aL*G_elastic*bL*atom1713*atom1909*C23L-atom1710*aL*G_elastic*C22L*bL;
atom1939 = -atom1710*aL*G_elastic*bL*atom1909*C23L-atom1920*C33L*G_elastic*atom1919*atom1713;

_CKL[0] = atom1906*atom643;
_CKL[1] = atom1911*atom643;
_CKL[2] = atom1914*atom643;
_CKL[3] = atom1923*atom643;
_CKL[4] = atom1930*atom643;
_CKL[5] = atom1933*atom643;
_CKL[6] =  atom647*atom1907+atom644*atom1906;
_CKL[7] =  atom647*atom1912+atom644*atom1911;
_CKL[8] =  atom644*atom1914+atom647*atom1917;
_CKL[9] =  atom1923*atom644+atom647*atom1926;
_CKL[10] =  atom644*atom1930+atom647*atom1931;
_CKL[11] =  atom644*atom1933+atom1936*atom647;
_CKL[12] =  atom1907*atom1898+atom1889*atom1906+atom1118*atom1910;
_CKL[13] =  atom1913*atom1118+atom1912*atom1898+atom1889*atom1911;
_CKL[14] =  atom1118*atom1922+atom1889*atom1914+atom1898*atom1917;
_CKL[15] =  atom1923*atom1889+atom1926*atom1898+atom1929*atom1118;
_CKL[16] =  atom1118*atom1932+atom1931*atom1898+atom1889*atom1930;
_CKL[17] =  atom1936*atom1898+atom1889*atom1933+atom1118*atom1939;
_CKL[18] =  atom1907*atom1899+atom1910*atom639+atom1892*atom1906;
_CKL[19] =  atom1912*atom1899+atom1892*atom1911+atom1913*atom639;
_CKL[20] =  atom1892*atom1914+atom1899*atom1917+atom1922*atom639;
_CKL[21] =  atom1923*atom1892+atom1899*atom1926+atom1929*atom639;
_CKL[22] =  atom1899*atom1931+atom1892*atom1930+atom1932*atom639;
_CKL[23] =  atom1892*atom1933+atom1936*atom1899+atom639*atom1939;
_CKL[24] = atom1907*atom648;
_CKL[25] = atom1912*atom648;
_CKL[26] = atom648*atom1917;
_CKL[27] = atom1926*atom648;
_CKL[28] = atom1931*atom648;
_CKL[29] = atom1936*atom648;
_CKL[30] =  atom1905*atom1910+atom1895*atom1906+atom1902*atom1907;
_CKL[31] =  atom1905*atom1913+atom1895*atom1911+atom1902*atom1912;
_CKL[32] =  atom1902*atom1917+atom1905*atom1922+atom1895*atom1914;
_CKL[33] =  atom1923*atom1895+atom1905*atom1929+atom1902*atom1926;
_CKL[34] =  atom1895*atom1930+atom1902*atom1931+atom1905*atom1932;
_CKL[35] =  atom1905*atom1939+atom1936*atom1902+atom1895*atom1933;

return _CKL;
}

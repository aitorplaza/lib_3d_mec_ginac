/*----------CKR.c lib3D_MEC exported-----------*/

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

#include "CKR.h"

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

double atom381;
double atom382;
double atom384;
double atom386;
double atom393;
double atom396;
double atom399;
double atom388;
double atom402;
double atom405;
double atom407;
double atom416;
double atom422;
double atom426;
double atom429;
double atom408;
double atom434;
double atom440;
double atom438;
double atom449;
double atom457;
double atom9;
double atom8;
double atom13;
double atom458;
double atom459;
double atom10;
double atom1511;
double atom11;
double atom1504;
double atom7;
double atom1506;
double atom1513;
double atom1733;
double atom372;
double atom373;
double atom374;
double atom443;
double atom462;
double atom14;
double atom463;
double atom1523;
double atom12;
double atom1516;
double atom1518;
double atom1525;
double atom1734;
double atom6;
double atom3;
double atom144;
double atom307;
double atom309;
double atom315;
double atom5;
double atom316;
double atom4;
double atom318;
double atom145;
double atom779;
double atom781;
double atom844;
double atom146;
double atom147;
double atom780;
double atom841;
double atom1716;
double atom847;
double atom1725;
double atom445;
double atom444;
double atom451;
double atom454;
double atom453;
double atom452;
double atom1736;
double atom1063;
double atom1737;
double atom1726;
double atom1719;
double atom1732;
double atom894;
double atom1722;
double atom1729;
double atom1528;
double atom1738;
double atom1531;
double atom1739;
double atom1740;
double atom1539;
double atom1741;
double atom22;
double atom1566;
double atom16;
double atom1560;
double atom28;
double atom1556;
double atom1569;
double atom1549;
double atom1551;
double atom1744;
double atom1747;
double atom1746;
double atom1749;
double atom2;
double atom71;
double atom1;
double atom72;
double atom1376;
double atom150;
double atom153;
double atom1389;
double atom1392;
double atom156;
double atom159;
double atom1382;
double atom1384;
double atom1395;
double atom1750;
double atom46;
double atom25;
double atom15;
double atom34;
double atom40;
double atom19;
double atom1591;
double atom1584;
double atom1594;
double atom1579;
double atom1753;
double atom1756;
double atom1757;
double atom1758;
double atom1759;
double atom1410;
double atom1415;
double atom1421;
double atom1406;
double atom1418;
double atom1412;
double atom1760;
double atom1604;
double atom1607;
double atom1763;
double atom1766;

double * _CKR = NULL;
void Init_CKR ( ) 
{
    _CKR = malloc ( CKR_n_rows * CKR_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKR_n_rows * CKR_n_cols ; i++ ) {_CKR[i]=0.0;}
  }
}

void Done_CKR ( ) 
{
if (_CKR != NULL) 
free (_CKR ); 
_CKR = NULL; 
}


double * CKR ()
{
if ( _CKR == NULL )
 {
    _CKR = malloc ( CKR_n_rows * CKR_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKR_n_rows * CKR_n_cols ; i++ ) {_CKR[i]=0.0;}
  }
 }

atom381 = 1.0/( endsR-stasR);
atom382 = ( sR_R-stasR)*atom381;
atom384 =  bsR+atom382*asR;
atom386 =  atom382*atom384+csR;
atom393 = atom381*asR;
atom396 =  atom381*atom384+atom393*atom382;
atom399 =  atom382*atom396+atom386*atom381;
atom388 =  atom386*atom382+dsR;
atom402 =  atom399*atom382+atom381*atom388;
atom405 =  ( atom388*atom382+esR)*atom381+atom402*atom382;
atom407 =  (atom405*atom405)+1.0;
atom416 = atom381*atom396;
atom422 = atom381*atom399;
atom426 = atom381*atom402;
atom429 =  2.0*atom426+2.0*( atom422+( atom393*atom381*atom382+atom416)*atom382)*atom382;
atom408 = pow(atom407,(1.0/2.0));
atom434 = -1.0/(atom408*atom408)*atom429*atom405*pow(atom407,-(1.0/2.0));
atom440 =  atom405+-5.0000000000000000e-01*atom434*L_R;
atom438 =  5.0000000000000000e-01*1.0/atom408*atom429*L_R+5.0000000000000000e-01*atom405*atom434*L_R+1.0;
atom449 = (atom438*atom438);
atom457 = pow( (atom440*atom440)+atom449,-(1.0/2.0));
atom9 = cos(a_pend);
atom8 = sin(b_pend);
atom13 = -atom9*atom8;
atom458 = atom457*atom438;
atom459 = atom457*atom440;
atom10 = sin(a_pend);
atom1511 =  atom459*atom10+atom13*atom458;
atom11 = atom10*atom8;
atom1504 =  atom9*atom459+atom11*atom458;
atom7 = cos(b_pend);
atom1506 = atom7*atom458;
atom1513 =  atom13*atom1511+atom1504*atom11+atom1506*atom7;
atom1733 = -C11R*bR*G_elastic*atom1513*aR;
atom372 =  uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 =  bR_R+atom373;
atom443 =  atom374*atom372+cR_R+atom372*( atom374+atom373);
atom462 = pow( (atom443*atom443)+1.0,-(1.0/2.0));
atom14 = atom9*atom7;
atom463 = atom462*atom443;
atom1523 =  atom14*atom463+atom462*atom10;
atom12 = -atom10*atom7;
atom1516 =  atom462*atom9+atom12*atom463;
atom1518 = atom463*atom8;
atom1525 =  atom1516*atom11+atom1518*atom7+atom13*atom1523;
atom1734 = -bR*C22R*G_elastic*atom1525*aR;
atom6 = sin(c);
atom3 = cos(a);
atom144 = -atom6*atom3;
atom307 = -5.0000000000000000e-01*L_WHS;
atom309 =  uW_R-lW_R;
atom315 =  atom309*( cW_R+( aW_R*atom309+bW_R)*atom309)+dW_R;
atom5 = cos(c);
atom316 = -atom315*sin(thetaW_R);
atom4 = sin(a);
atom318 = atom315*cos(thetaW_R);
atom145 = atom6*atom4;
atom779 =  atom5*atom316+atom318*atom145+uW_R*atom144+atom144*atom307;
atom781 =  atom307*atom4+uW_R*atom4+atom318*atom3;
atom844 =  atom779*atom4-atom781*atom144;
atom146 = atom5*atom3;
atom147 = -atom5*atom4;
atom780 =  atom307*atom146+uW_R*atom146+atom6*atom316+atom318*atom147;
atom841 = -atom4*atom780+atom781*atom146;
atom1716 =  atom844*atom459+atom841*atom458;
atom847 =  atom144*atom780-atom779*atom146;
atom1725 =  atom463*atom847+atom844*atom462;
atom445 = -atom438*atom443;
atom444 = atom443*atom440;
atom451 = pow( (atom444*atom444)+(atom445*atom445)+atom449,-(1.0/2.0));
atom454 = atom438*atom451;
atom453 = atom451*atom445;
atom452 = atom444*atom451;
atom1736 = pow(bR*aR,(1.0/2.0));
atom1063 =  atom454*atom4+atom452*atom144+atom453*atom146;
atom1737 = -bR*atom1736*G_elastic*C23R*atom1525*aR;
atom1726 = atom462*atom779;
atom1719 = -atom458*atom780+atom459*atom779;
atom1732 =  atom6*atom453+atom5*atom452;
atom894 = -atom5*atom781;
atom1722 =  atom781*atom6*atom458+atom459*atom894;
atom1729 =  atom462*atom894+( atom5*atom780-atom6*atom779)*atom463;
atom1528 =  atom10*atom1511+atom9*atom1504;
atom1738 = -C11R*bR*atom1528*G_elastic*aR;
atom1531 =  atom10*atom1523+atom9*atom1516;
atom1739 = -bR*atom1531*C22R*G_elastic*aR;
atom1740 = -bR*atom1736*atom1531*G_elastic*C23R*aR;
atom1539 =  atom12*atom1504+atom14*atom1511+atom1506*atom8;
atom1741 = -C11R*bR*G_elastic*aR*( atom1539*atom847+atom841*atom1513+atom844*atom1528);
atom22 = -atom6*atom11+atom5*atom9;
atom1566 =  atom12*atom454+atom452*atom11+atom9*atom453;
atom16 = -atom6*atom7;
atom1560 =  atom452*atom7+atom454*atom8;
atom28 = -atom13*atom6+atom5*atom10;
atom1556 =  atom10*atom453+atom14*atom454+atom452*atom13;
atom1569 =  atom1566*( atom22*atom3+atom12*atom4)+( atom28*atom3+atom14*atom4)*atom1556+atom1560*( atom16*atom3+atom4*atom8);
atom1549 =  atom14*atom1523+atom12*atom1516+atom1518*atom8;
atom1551 =  atom844*atom1531+atom841*atom1525+atom847*atom1549;
atom1744 = -atom1551*bR*C22R*G_elastic*aR+bR*atom1736*G_elastic*atom1569*C23R*aR;
atom1747 = (aR*aR);
atom1746 = (bR*bR);
atom1749 = -C33R*atom1747*G_elastic*atom1569*atom1746-atom1551*bR*atom1736*G_elastic*C23R*aR;
atom2 = sin(b);
atom71 = -atom2*atom3;
atom1 = cos(b);
atom72 = atom1*atom3;
atom1376 =  (atom4*atom4)+(atom71*atom71)+(atom72*atom72);
atom150 = -atom2*atom145+atom5*atom1;
atom153 =  atom5*atom2+atom1*atom145;
atom1389 =  atom144*atom4+atom72*atom153+atom71*atom150;
atom1392 = -atom781*atom1389+atom1376*atom779;
atom156 =  atom1*atom6-atom2*atom147;
atom159 =  atom2*atom6+atom1*atom147;
atom1382 =  atom4*atom146+atom159*atom72+atom71*atom156;
atom1384 =  atom781*atom1382-atom1376*atom780;
atom1395 =  atom1389*atom780-atom1382*atom779;
atom1750 = -C11R*bR*G_elastic*aR*( atom1392*atom1528+atom1384*atom1513+atom1539*atom1395);
atom46 = -atom28*atom4+atom14*atom3;
atom25 =  atom5*atom13+atom10*atom6;
atom15 = atom5*atom7;
atom34 =  atom3*atom8-atom16*atom4;
atom40 =  atom12*atom3-atom22*atom4;
atom19 =  atom5*atom11+atom9*atom6;
atom1591 = -atom1566*( atom2*atom40-atom1*atom19)+( atom1*atom25-atom2*atom46)*atom1556-atom1560*( atom34*atom2-atom1*atom15);
atom1584 =  ( atom1*atom40+atom2*atom19)*atom1566+( atom25*atom2+atom1*atom46)*atom1556+atom1560*( atom2*atom15+atom34*atom1);
atom1594 =  atom1591*atom71+atom1584*atom72+atom1569*atom4;
atom1579 =  atom1384*atom1525+atom1392*atom1531+atom1395*atom1549;
atom1753 = -bR*atom1579*C22R*G_elastic*aR+atom1594*bR*atom1736*G_elastic*C23R*aR;
atom1756 = -C33R*atom1594*atom1747*G_elastic*atom1746-bR*atom1736*atom1579*G_elastic*C23R*aR;
atom1757 = -atom1539*C11R*bR*G_elastic*aR;
atom1758 = -bR*C22R*G_elastic*aR*atom1549;
atom1759 = -bR*atom1736*G_elastic*C23R*aR*atom1549;
atom1410 =  atom1*atom156+atom2*atom159;
atom1415 =  atom1*atom150+atom2*atom153;
atom1421 =  atom780*atom1415-atom1410*atom779;
atom1406 =  atom2*atom72+atom1*atom71;
atom1418 = -atom781*atom1415+atom1406*atom779;
atom1412 = -atom1406*atom780+atom781*atom1410;
atom1760 = -C11R*bR*( atom1539*atom1421+atom1412*atom1513+atom1418*atom1528)*G_elastic*aR;
atom1604 =  atom1421*atom1549+atom1412*atom1525+atom1418*atom1531;
atom1607 =  atom1584*atom2+atom1*atom1591;
atom1763 = -bR*C22R*G_elastic*atom1604*aR+bR*atom1736*G_elastic*atom1607*C23R*aR;
atom1766 = -C33R*atom1747*G_elastic*atom1607*atom1746-bR*atom1736*G_elastic*C23R*atom1604*aR;

_CKR[0] = atom458*atom1733;
_CKR[1] = atom458*atom1738;
_CKR[2] = atom1741*atom458;
_CKR[3] = atom1750*atom458;
_CKR[4] = atom1757*atom458;
_CKR[5] = atom1760*atom458;
_CKR[6] =  atom459*atom1733+atom462*atom1734;
_CKR[7] =  atom462*atom1739+atom459*atom1738;
_CKR[8] =  atom459*atom1741+atom1744*atom462;
_CKR[9] =  atom459*atom1750+atom462*atom1753;
_CKR[10] =  atom462*atom1758+atom1757*atom459;
_CKR[11] =  atom462*atom1763+atom1760*atom459;
_CKR[12] =  atom1725*atom1734+atom1063*atom1737+atom1716*atom1733;
_CKR[13] =  atom1738*atom1716+atom1740*atom1063+atom1725*atom1739;
_CKR[14] =  atom1744*atom1725+atom1741*atom1716+atom1063*atom1749;
_CKR[15] =  atom1750*atom1716+atom1725*atom1753+atom1756*atom1063;
_CKR[16] =  atom1063*atom1759+atom1758*atom1725+atom1757*atom1716;
_CKR[17] =  atom1766*atom1063+atom1760*atom1716+atom1725*atom1763;
_CKR[18] =  atom454*atom1737+atom1726*atom1734+atom1719*atom1733;
_CKR[19] =  atom1719*atom1738+atom1740*atom454+atom1739*atom1726;
_CKR[20] =  atom1744*atom1726+atom454*atom1749+atom1741*atom1719;
_CKR[21] =  atom1750*atom1719+atom1726*atom1753+atom454*atom1756;
_CKR[22] =  atom454*atom1759+atom1757*atom1719+atom1758*atom1726;
_CKR[23] =  atom1760*atom1719+atom1763*atom1726+atom1766*atom454;
_CKR[24] = atom463*atom1734;
_CKR[25] = atom1739*atom463;
_CKR[26] = atom1744*atom463;
_CKR[27] = atom463*atom1753;
_CKR[28] = atom1758*atom463;
_CKR[29] = atom1763*atom463;
_CKR[30] =  atom1732*atom1737+atom1729*atom1734+atom1722*atom1733;
_CKR[31] =  atom1739*atom1729+atom1732*atom1740+atom1722*atom1738;
_CKR[32] =  atom1732*atom1749+atom1741*atom1722+atom1744*atom1729;
_CKR[33] =  atom1729*atom1753+atom1732*atom1756+atom1750*atom1722;
_CKR[34] =  atom1757*atom1722+atom1758*atom1729+atom1732*atom1759;
_CKR[35] =  atom1763*atom1729+atom1766*atom1732+atom1760*atom1722;

return _CKR;
}

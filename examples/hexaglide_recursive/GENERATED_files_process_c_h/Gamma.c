/*----------Gamma.c lib3D_MEC exported-----------*/

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

#include "Gamma.h"

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
#define mP param[ 5 ]
#define mxP param[ 6 ]
#define myP param[ 7 ]
#define mzP param[ 8 ]
#define IxxP param[ 9 ]
#define IxyP param[ 10 ]
#define IyyP param[ 11 ]
#define IxzP param[ 12 ]
#define IzzP param[ 13 ]
#define IyzP param[ 14 ]
#define m1 param[ 15 ]
#define mx1 param[ 16 ]
#define my1 param[ 17 ]
#define mz1 param[ 18 ]
#define Ixx1 param[ 19 ]
#define Ixy1 param[ 20 ]
#define Iyy1 param[ 21 ]
#define Ixz1 param[ 22 ]
#define Izz1 param[ 23 ]
#define Iyz1 param[ 24 ]
#define m2 param[ 25 ]
#define mx2 param[ 26 ]
#define my2 param[ 27 ]
#define mz2 param[ 28 ]
#define Ixx2 param[ 29 ]
#define Ixy2 param[ 30 ]
#define Iyy2 param[ 31 ]
#define Ixz2 param[ 32 ]
#define Izz2 param[ 33 ]
#define Iyz2 param[ 34 ]
#define m3 param[ 35 ]
#define mx3 param[ 36 ]
#define my3 param[ 37 ]
#define mz3 param[ 38 ]
#define Ixx3 param[ 39 ]
#define Ixy3 param[ 40 ]
#define Iyy3 param[ 41 ]
#define Ixz3 param[ 42 ]
#define Izz3 param[ 43 ]
#define Iyz3 param[ 44 ]
#define m4 param[ 45 ]
#define mx4 param[ 46 ]
#define my4 param[ 47 ]
#define mz4 param[ 48 ]
#define Ixx4 param[ 49 ]
#define Ixy4 param[ 50 ]
#define Iyy4 param[ 51 ]
#define Ixz4 param[ 52 ]
#define Izz4 param[ 53 ]
#define Iyz4 param[ 54 ]
#define m5 param[ 55 ]
#define mx5 param[ 56 ]
#define my5 param[ 57 ]
#define mz5 param[ 58 ]
#define Ixx5 param[ 59 ]
#define Ixy5 param[ 60 ]
#define Iyy5 param[ 61 ]
#define Ixz5 param[ 62 ]
#define Izz5 param[ 63 ]
#define Iyz5 param[ 64 ]
#define m6 param[ 65 ]
#define mx6 param[ 66 ]
#define my6 param[ 67 ]
#define mz6 param[ 68 ]
#define Ixx6 param[ 69 ]
#define Ixy6 param[ 70 ]
#define Iyy6 param[ 71 ]
#define Ixz6 param[ 72 ]
#define Izz6 param[ 73 ]
#define Iyz6 param[ 74 ]
#define Fs1 param[ 75 ]
#define Fs2 param[ 76 ]
#define Fs3 param[ 77 ]
#define Fs4 param[ 78 ]
#define Fs5 param[ 79 ]
#define Fs6 param[ 80 ]
#define FS001 param[ 81 ]
#define FSa11 param[ 82 ]
#define FSb11 param[ 83 ]
#define FSa21 param[ 84 ]
#define FSb21 param[ 85 ]
#define FS002 param[ 86 ]
#define FSa12 param[ 87 ]
#define FSb12 param[ 88 ]
#define FSa22 param[ 89 ]
#define FSb22 param[ 90 ]
#define FS003 param[ 91 ]
#define FSa13 param[ 92 ]
#define FSb13 param[ 93 ]
#define FSa23 param[ 94 ]
#define FSb23 param[ 95 ]
#define FS004 param[ 96 ]
#define FSa14 param[ 97 ]
#define FSb14 param[ 98 ]
#define FSa24 param[ 99 ]
#define FSb24 param[ 100 ]
#define FS005 param[ 101 ]
#define FSa15 param[ 102 ]
#define FSb15 param[ 103 ]
#define FSa25 param[ 104 ]
#define FSb25 param[ 105 ]
#define FS006 param[ 106 ]
#define FSa16 param[ 107 ]
#define FSb16 param[ 108 ]
#define FSa26 param[ 109 ]
#define FSb26 param[ 110 ]
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
double atom37;
double atom47;
double atom38;
double atom48;
double atom1368;
double atom1369;
double atom1370;
double atom40;
double atom291;
double atom292;
double atom1941;
double atom1940;
double atom1942;
double atom80;
double atom41;
double atom42;
double atom43;
double atom52;
double atom54;
double atom49;
double atom51;
double atom1372;
double atom1371;
double atom1373;
double atom45;
double atom58;
double atom60;
double atom55;
double atom57;
double atom1736;
double atom1735;
double atom1737;
double atom44;
double atom1721;
double atom1723;
double atom1957;
double atom1956;
double atom1958;
double atom82;
double atom79;
double atom1381;
double atom81;
double atom1738;
double atom46;
double atom1732;
double atom1730;
double atom1733;
double atom1731;
double atom1734;
double atom1952;
double atom1951;
double atom1724;
double atom1722;
double atom1725;
double atom1375;
double atom1374;
double atom1376;
double atom1726;
double atom1727;
double atom1728;
double atom1975;
double atom1976;
double atom1977;
double atom1729;
double atom1382;
double atom1970;
double atom1971;
double atom1989;
double atom1389;
double atom104;
double atom1390;
double atom1746;
double atom2000;
double atom1745;
double atom106;
double atom103;
double atom1396;
double atom105;
double atom1747;
double atom1397;
double atom1744;
double atom2012;
double atom1742;
double atom1391;
double atom1743;
double atom1;
double atom0;
double atom2;
double atom3;
double atom4;
double atom5;
double atom6;
double atom1404;
double atom1405;
double atom1406;
double atom2026;
double atom2027;
double atom2028;
double atom128;
double atom129;
double atom131;
double atom1776;
double atom2035;
double atom1416;
double atom127;
double atom130;
double atom1417;
double atom2037;
double atom2060;
double atom2062;
double atom1774;
double atom1773;
double atom1775;
double atom1771;
double atom1770;
double atom1772;
double atom1408;
double atom1407;
double atom1409;
double atom2051;
double atom2050;
double atom2047;
double atom2046;
double atom2048;
double atom1418;
double atom1757;
double atom2076;
double atom2075;
double atom2072;
double atom2071;
double atom2073;
double atom1761;
double atom1760;
double atom1762;
double atom1411;
double atom1410;
double atom1412;
double atom1764;
double atom1763;
double atom1765;
double atom7;
double atom8;
double atom2091;
double atom2092;
double atom2093;
double atom1432;
double atom1431;
double atom1433;
double atom169;
double atom170;
double atom1805;
double atom2100;
double atom171;
double atom168;
double atom1444;
double atom2102;
double atom1443;
double atom2116;
double atom2115;
double atom2117;
double atom1802;
double atom1803;
double atom1804;
double atom1435;
double atom1434;
double atom1436;
double atom2112;
double atom2111;
double atom1800;
double atom1799;
double atom1801;
double atom2127;
double atom2125;
double atom1790;
double atom1789;
double atom1791;
double atom1793;
double atom1792;
double atom1794;
double atom1437;
double atom1438;
double atom1439;
double atom1786;
double atom1445;
double atom2138;
double atom2137;
double atom2142;
double atom2141;
double atom2143;
double atom209;
double atom1464;
double atom211;
double atom208;
double atom1465;
double atom2163;
double atom210;
double atom1822;
double atom2165;
double atom1458;
double atom2156;
double atom2184;
double atom2186;
double atom1821;
double atom1459;
double atom2176;
double atom1820;
double atom1466;
double atom1811;
double atom1814;
double atom1815;
double atom1460;
double atom2196;
double atom250;
double atom249;
double atom1839;
double atom2220;
double atom251;
double atom248;
double atom1486;
double atom2218;
double atom2211;
double atom1479;
double atom1485;
double atom2229;
double atom1837;
double atom1480;
double atom1838;
double atom2241;
double atom2239;
double atom1826;
double atom1487;
double atom2251;
double atom1831;
double atom1832;
double atom1481;

double * _Gamma = NULL;
void Init_Gamma ( ) 
{
    _Gamma = malloc ( Gamma_n_rows * Gamma_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Gamma_n_rows * Gamma_n_cols ; i++ ) {_Gamma[i]=0.0;}
  }
}

void Done_Gamma ( ) 
{
if (_Gamma != NULL) 
free (_Gamma ); 
_Gamma = NULL; 
}


double * Gamma ()
{
if ( _Gamma == NULL )
 {
    _Gamma = malloc ( Gamma_n_rows * Gamma_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Gamma_n_rows * Gamma_n_cols ; i++ ) {_Gamma[i]=0.0;}
  }
 }

atom39 = cos(b);
atom37 = cos(c);
atom47 = atom39*atom37;
atom38 = sin(c);
atom48 = -atom38*atom39;
atom1368 = atom47*r;
atom1369 = atom48*e;
atom1370 =  atom1368+atom1369;
atom40 = sin(b);
atom291 = -atom40*atom37;
atom292 = atom38*atom40;
atom1941 = -atom291*e;
atom1940 = atom292*r;
atom1942 =  atom1941+atom1940;
atom80 = sin(b1);
atom41 = cos(a);
atom42 = sin(a);
atom43 = atom42*atom40;
atom52 = -atom38*atom43;
atom54 =  atom52+atom41*atom37;
atom49 = atom43*atom37;
atom51 =  atom49+atom41*atom38;
atom1372 = atom54*e;
atom1371 = r*atom51;
atom1373 =  atom1372+atom1371;
atom45 = -atom41*atom40;
atom58 = -atom38*atom45;
atom60 =  atom58+atom42*atom37;
atom55 = atom45*atom37;
atom57 =  atom55+atom42*atom38;
atom1736 = atom60*r;
atom1735 = -atom57*e;
atom1737 =  atom1736+atom1735;
atom44 = -atom42*atom39;
atom1721 = atom44*atom38;
atom1723 = -atom44*atom37;
atom1957 = atom1721*r;
atom1956 = -atom1723*e;
atom1958 =  atom1957+atom1956;
atom82 = sin(a1);
atom79 = cos(b1);
atom1381 = L*atom82*atom79;
atom81 = cos(a1);
atom1738 = atom80*atom81*L;
atom46 = atom41*atom39;
atom1732 = -atom46*atom37;
atom1730 = atom38*atom46;
atom1733 = r*atom1732;
atom1731 = atom1730*e;
atom1734 =  atom1733+atom1731;
atom1952 = -atom52*e;
atom1951 = -r*atom49;
atom1724 = atom1723*r;
atom1722 = atom1721*e;
atom1725 =  atom1724+atom1722;
atom1375 = atom60*e;
atom1374 = atom57*r;
atom1376 =  atom1375+atom1374;
atom1726 = -atom51*e;
atom1727 = r*atom54;
atom1728 =  atom1726+atom1727;
atom1975 = atom1730*r;
atom1976 = -atom1732*e;
atom1977 =  atom1975+atom1976;
atom1729 = -atom80*L*atom82;
atom1382 = -atom81*L*atom79;
atom1970 = -r*atom55;
atom1971 = -atom58*e;
atom1989 = -atom1941+atom1940;
atom1389 =  atom1368-atom1369;
atom104 = sin(b2);
atom1390 = -atom1372+atom1371;
atom1746 =  atom1736-atom1735;
atom2000 =  atom1957-atom1956;
atom1745 =  atom1733-atom1731;
atom106 = sin(a2);
atom103 = cos(b2);
atom1396 = L*atom106*atom103;
atom105 = cos(a2);
atom1747 = atom104*atom105*L;
atom1397 = -atom105*L*atom103;
atom1744 = -atom104*L*atom106;
atom2012 =  atom1975-atom1976;
atom1742 =  atom1724-atom1722;
atom1391 = -atom1375+atom1374;
atom1743 = -atom1726+atom1727;
atom1 = pow(3.0,(1.0/2.0));
atom0 = -(1.0/2.0)*r;
atom2 = (1.0/2.0)*e*atom1;
atom3 =  atom0+atom2;
atom4 = -(1.0/2.0)*r*atom1;
atom5 = -(1.0/2.0)*e;
atom6 =  atom4+atom5;
atom1404 = atom47*atom3;
atom1405 = atom6*atom48;
atom1406 =  atom1404+atom1405;
atom2026 = atom292*atom3;
atom2027 = -atom291*atom6;
atom2028 =  atom2026+atom2027;
atom128 = sin(b3);
atom129 = cos(a3);
atom131 = (1.0/2.0)*atom1;
atom1776 = atom128*L*atom129;
atom2035 = atom131*atom1776;
atom1416 = -atom128*L;
atom127 = cos(b3);
atom130 = sin(a3);
atom1417 = atom127*L*atom130;
atom2037 = atom131*atom1417;
atom2060 = (1.0/2.0)*atom1417;
atom2062 = (1.0/2.0)*atom1776;
atom1774 = atom60*atom3;
atom1773 = -atom57*atom6;
atom1775 =  atom1774+atom1773;
atom1771 = atom1732*atom3;
atom1770 = atom1730*atom6;
atom1772 =  atom1771+atom1770;
atom1408 = atom6*atom54;
atom1407 = atom3*atom51;
atom1409 =  atom1408+atom1407;
atom2051 = -atom52*atom6;
atom2050 = -atom49*atom3;
atom2047 = -atom1723*atom6;
atom2046 = atom1721*atom3;
atom2048 =  atom2047+atom2046;
atom1418 = -atom127*L*atom129;
atom1757 = -atom128*L*atom130;
atom2076 = -atom6*atom58;
atom2075 = -atom55*atom3;
atom2072 = -atom1732*atom6;
atom2071 = atom1730*atom3;
atom2073 =  atom2072+atom2071;
atom1761 = atom1723*atom3;
atom1760 = atom1721*atom6;
atom1762 =  atom1761+atom1760;
atom1411 = atom60*atom6;
atom1410 = atom57*atom3;
atom1412 =  atom1411+atom1410;
atom1764 = atom3*atom54;
atom1763 = -atom6*atom51;
atom1765 =  atom1764+atom1763;
atom7 =  atom0-atom2;
atom8 =  atom4-atom5;
atom2091 = atom292*atom7;
atom2092 = -atom291*atom8;
atom2093 =  atom2091+atom2092;
atom1432 = atom8*atom48;
atom1431 = atom47*atom7;
atom1433 =  atom1432+atom1431;
atom169 = sin(b4);
atom170 = cos(a4);
atom1805 = atom169*atom170*L;
atom2100 = atom131*atom1805;
atom171 = sin(a4);
atom168 = cos(b4);
atom1444 = L*atom171*atom168;
atom2102 = atom131*atom1444;
atom1443 = -atom169*L;
atom2116 = -atom1723*atom8;
atom2115 = atom7*atom1721;
atom2117 =  atom2116+atom2115;
atom1802 = atom60*atom7;
atom1803 = -atom57*atom8;
atom1804 =  atom1802+atom1803;
atom1435 = atom8*atom54;
atom1434 = atom7*atom51;
atom1436 =  atom1435+atom1434;
atom2112 = -atom8*atom52;
atom2111 = -atom7*atom49;
atom1800 = atom1730*atom8;
atom1799 = atom7*atom1732;
atom1801 =  atom1800+atom1799;
atom2127 = (1.0/2.0)*atom1805;
atom2125 = (1.0/2.0)*atom1444;
atom1790 = atom7*atom1723;
atom1789 = atom1721*atom8;
atom1791 =  atom1790+atom1789;
atom1793 = atom7*atom54;
atom1792 = -atom8*atom51;
atom1794 =  atom1793+atom1792;
atom1437 = atom7*atom57;
atom1438 = atom60*atom8;
atom1439 =  atom1437+atom1438;
atom1786 = -atom169*L*atom171;
atom1445 = -atom170*L*atom168;
atom2138 = -atom7*atom55;
atom2137 = -atom8*atom58;
atom2142 = -atom1732*atom8;
atom2141 = atom7*atom1730;
atom2143 =  atom2142+atom2141;
atom209 = sin(b5);
atom1464 = -atom209*L;
atom211 = sin(a5);
atom208 = cos(b5);
atom1465 = atom211*L*atom208;
atom2163 = -atom131*atom1465;
atom210 = cos(a5);
atom1822 = atom209*atom210*L;
atom2165 = -atom131*atom1822;
atom1458 = -atom1432+atom1431;
atom2156 =  atom2091-atom2092;
atom2184 = (1.0/2.0)*atom1465;
atom2186 = (1.0/2.0)*atom1822;
atom1821 =  atom1802-atom1803;
atom1459 = -atom1435+atom1434;
atom2176 = -atom2116+atom2115;
atom1820 = -atom1800+atom1799;
atom1466 = -atom210*L*atom208;
atom1811 = -atom209*atom211*L;
atom1814 =  atom1790-atom1789;
atom1815 =  atom1793-atom1792;
atom1460 =  atom1437-atom1438;
atom2196 = -atom2142+atom2141;
atom250 = cos(a6);
atom249 = sin(b6);
atom1839 = atom250*L*atom249;
atom2220 = -atom1839*atom131;
atom251 = sin(a6);
atom248 = cos(b6);
atom1486 = atom251*L*atom248;
atom2218 = -atom131*atom1486;
atom2211 =  atom2026-atom2027;
atom1479 =  atom1404-atom1405;
atom1485 = -L*atom249;
atom2229 = -atom2047+atom2046;
atom1837 =  atom1771-atom1770;
atom1480 = -atom1408+atom1407;
atom1838 =  atom1774-atom1773;
atom2241 = (1.0/2.0)*atom1839;
atom2239 = (1.0/2.0)*atom1486;
atom1826 = -atom251*L*atom249;
atom1487 = -atom250*L*atom248;
atom2251 = -atom2072+atom2071;
atom1831 =  atom1761-atom1760;
atom1832 =  atom1764-atom1763;
atom1481 = -atom1411+atom1410;

_Gamma[0] =  ( atom1370*dB-dc*atom1942)*dB+(dB1*dB1)*atom80*L-( dB*atom1942-atom1370*dc)*dc;
_Gamma[1] = -( dB*atom1958-atom1737*da-dc*atom1373)*dc-( da1*atom1381+dB1*atom1738)*da1+( atom1737*dc+da*atom1373+atom1734*dB)*da-dB1*( dB1*atom1381+da1*atom1738)-( ( atom1952+atom1951)*dB-atom1734*da+dc*atom1958)*dB;
_Gamma[2] = -dB1*( dB1*atom1382-atom1729*da1)+( atom1376*da-atom1725*dB-atom1728*dc)*da+( dB1*atom1729-atom1382*da1)*da1-( dc*atom1977+atom1725*da+dB*( atom1970+atom1971))*dB+( dc*atom1376-atom1728*da-atom1977*dB)*dc;
_Gamma[3] =  dB*( atom1389*dB-dc*atom1989)+dc*( atom1389*dc-dB*atom1989)+(dB2*dB2)*atom104*L;
_Gamma[4] = -da2*( atom1396*da2+dB2*atom1747)-dB2*( dB2*atom1396+atom1747*da2)+( atom1745*dB+atom1390*da+atom1746*dc)*da+( atom1390*dc-dB*atom2000+atom1746*da)*dc+( atom1745*da+dB*( atom1952-atom1951)-dc*atom2000)*dB;
_Gamma[5] = -( atom1743*dc+atom1742*dB-atom1391*da)*da+dB2*( da2*atom1744-dB2*atom1397)+dc*( dc*atom1391-atom1743*da-dB*atom2012)-( dc*atom2012+atom1742*da+( atom1970-atom1971)*dB)*dB-da2*( da2*atom1397-dB2*atom1744);
_Gamma[6] =  ( atom1406*dB-atom2028*dc)*dB+( atom1406*dc-atom2028*dB)*dc+( da3*atom2037+atom2035*dB3)*da3+( 2.0*atom2035*da3+( atom1416+2.0*atom2037)*dB3)*dB3/2.0;
_Gamma[7] = -( ( atom131*atom1416-atom2060)*dB3-atom2062*da3)*dB3-( atom2048*dc+( atom2051+atom2050)*dB-atom1772*da)*dB+( da3*atom2060+atom2062*dB3)*da3+dc*( da*atom1775-atom2048*dB+atom1409*dc)+( atom1772*dB+dc*atom1775+atom1409*da)*da;
_Gamma[8] = -( atom1418*dB3-da3*atom1757)*dB3+( da*atom1412-atom1762*dB-atom1765*dc)*da-( atom1762*da+( atom2076+atom2075)*dB+atom2073*dc)*dB+( atom1757*dB3-da3*atom1418)*da3+( dc*atom1412-atom2073*dB-atom1765*da)*dc;
_Gamma[9] =  da4*( atom2102*da4+atom2100*dB4)+( ( 2.0*atom2102+atom1443)*dB4+2.0*da4*atom2100)*dB4/2.0+dB*( atom1433*dB-atom2093*dc)+dc*( atom1433*dc-atom2093*dB);
_Gamma[10] = -( ( atom2112+atom2111)*dB+atom2117*dc-atom1801*da)*dB-dc*( atom2117*dB-atom1804*da-dc*atom1436)+( da*atom1436+dc*atom1804+dB*atom1801)*da+da4*( da4*atom2125+dB4*atom2127)+dB4*( ( atom2125-atom131*atom1443)*dB4+da4*atom2127);
_Gamma[11] = -da*( atom1791*dB-atom1439*da+dc*atom1794)-( atom2143*dc+atom1791*da+( atom2138+atom2137)*dB)*dB+( atom1786*dB4-da4*atom1445)*da4+( atom1439*dc-atom2143*dB-atom1794*da)*dc-( atom1445*dB4-da4*atom1786)*dB4;
_Gamma[12] =  ( 2.0*da5*atom2165+( atom1464+2.0*atom2163)*dB5)*dB5/2.0-dc*( dB*atom2156-dc*atom1458)+da5*( atom2165*dB5+da5*atom2163)+( dB*atom1458-dc*atom2156)*dB;
_Gamma[13] =  dB*( ( atom2112-atom2111)*dB+atom1820*da-dc*atom2176)+da5*( da5*atom2184+atom2186*dB5)+dB5*( ( atom2184+atom131*atom1464)*dB5+da5*atom2186)-( dB*atom2176-dc*atom1459-atom1821*da)*dc+( atom1820*dB+da*atom1459+atom1821*dc)*da;
_Gamma[14] =  ( atom1460*da-dc*atom1815-atom1814*dB)*da-( dB*( atom2138-atom2137)+atom2196*dc+atom1814*da)*dB-da5*( da5*atom1466-atom1811*dB5)-dc*( atom2196*dB-atom1460*dc+atom1815*da)-( atom1466*dB5-da5*atom1811)*dB5;
_Gamma[15] =  ( dB*atom1479-atom2211*dc)*dB+da6*( da6*atom2218+atom2220*dB6)+( dc*atom1479-atom2211*dB)*dc+( ( 2.0*atom2218+atom1485)*dB6+2.0*da6*atom2220)*dB6/2.0;
_Gamma[16] =  da6*( da6*atom2239+atom2241*dB6)+dB6*( da6*atom2241+( atom131*atom1485+atom2239)*dB6)+( atom1837*dB+dc*atom1838+atom1480*da)*da-( dB*atom2229-da*atom1838-atom1480*dc)*dc+( atom1837*da+dB*( atom2051-atom2050)-dc*atom2229)*dB;
_Gamma[17] = -( dB*atom1831+atom1832*dc-atom1481*da)*da+da6*( dB6*atom1826-da6*atom1487)-( da*atom1831-( atom2076-atom2075)*dB+dc*atom2251)*dB+( da6*atom1826-atom1487*dB6)*dB6-( dB*atom2251-atom1481*dc+atom1832*da)*dc;

return _Gamma;
}

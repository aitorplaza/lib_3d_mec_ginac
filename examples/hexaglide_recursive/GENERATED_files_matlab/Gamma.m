function Gamma_ = Gamma(q,dq,time,param)

x = q( 1 ); 
y = q( 2 ); 
z = q( 3 ); 
a = q( 4 ); 
b = q( 5 ); 
c = q( 6 ); 
a1 = q( 7 ); 
a2 = q( 8 ); 
a3 = q( 9 ); 
a4 = q( 10 ); 
a5 = q( 11 ); 
a6 = q( 12 ); 
b1 = q( 13 ); 
b2 = q( 14 ); 
b3 = q( 15 ); 
b4 = q( 16 ); 
b5 = q( 17 ); 
b6 = q( 18 ); 
s1 = q( 19 ); 
s2 = q( 20 ); 
s3 = q( 21 ); 
s4 = q( 22 ); 
s5 = q( 23 ); 
s6 = q( 24 ); 

dx = dq( 1 ); 
dy = dq( 2 ); 
dz = dq( 3 ); 
da = dq( 4 ); 
dB = dq( 5 ); 
dc = dq( 6 ); 
da1 = dq( 7 ); 
da2 = dq( 8 ); 
da3 = dq( 9 ); 
da4 = dq( 10 ); 
da5 = dq( 11 ); 
da6 = dq( 12 ); 
dB1 = dq( 13 ); 
dB2 = dq( 14 ); 
dB3 = dq( 15 ); 
dB4 = dq( 16 ); 
dB5 = dq( 17 ); 
dB6 = dq( 18 ); 
ds1 = dq( 19 ); 
ds2 = dq( 20 ); 
ds3 = dq( 21 ); 
ds4 = dq( 22 ); 
ds5 = dq( 23 ); 
ds6 = dq( 24 ); 

t= time ;

g = param( 1 ); 
R = param( 2 ); 
r = param( 3 ); 
L = param( 4 ); 
e = param( 5 ); 
mP = param( 6 ); 
mxP = param( 7 ); 
myP = param( 8 ); 
mzP = param( 9 ); 
IxxP = param( 10 ); 
IxyP = param( 11 ); 
IyyP = param( 12 ); 
IxzP = param( 13 ); 
IzzP = param( 14 ); 
IyzP = param( 15 ); 
m1 = param( 16 ); 
mx1 = param( 17 ); 
my1 = param( 18 ); 
mz1 = param( 19 ); 
Ixx1 = param( 20 ); 
Ixy1 = param( 21 ); 
Iyy1 = param( 22 ); 
Ixz1 = param( 23 ); 
Izz1 = param( 24 ); 
Iyz1 = param( 25 ); 
m2 = param( 26 ); 
mx2 = param( 27 ); 
my2 = param( 28 ); 
mz2 = param( 29 ); 
Ixx2 = param( 30 ); 
Ixy2 = param( 31 ); 
Iyy2 = param( 32 ); 
Ixz2 = param( 33 ); 
Izz2 = param( 34 ); 
Iyz2 = param( 35 ); 
m3 = param( 36 ); 
mx3 = param( 37 ); 
my3 = param( 38 ); 
mz3 = param( 39 ); 
Ixx3 = param( 40 ); 
Ixy3 = param( 41 ); 
Iyy3 = param( 42 ); 
Ixz3 = param( 43 ); 
Izz3 = param( 44 ); 
Iyz3 = param( 45 ); 
m4 = param( 46 ); 
mx4 = param( 47 ); 
my4 = param( 48 ); 
mz4 = param( 49 ); 
Ixx4 = param( 50 ); 
Ixy4 = param( 51 ); 
Iyy4 = param( 52 ); 
Ixz4 = param( 53 ); 
Izz4 = param( 54 ); 
Iyz4 = param( 55 ); 
m5 = param( 56 ); 
mx5 = param( 57 ); 
my5 = param( 58 ); 
mz5 = param( 59 ); 
Ixx5 = param( 60 ); 
Ixy5 = param( 61 ); 
Iyy5 = param( 62 ); 
Ixz5 = param( 63 ); 
Izz5 = param( 64 ); 
Iyz5 = param( 65 ); 
m6 = param( 66 ); 
mx6 = param( 67 ); 
my6 = param( 68 ); 
mz6 = param( 69 ); 
Ixx6 = param( 70 ); 
Ixy6 = param( 71 ); 
Iyy6 = param( 72 ); 
Ixz6 = param( 73 ); 
Izz6 = param( 74 ); 
Iyz6 = param( 75 ); 
Fs1 = param( 76 ); 
Fs2 = param( 77 ); 
Fs3 = param( 78 ); 
Fs4 = param( 79 ); 
Fs5 = param( 80 ); 
Fs6 = param( 81 ); 
FS001 = param( 82 ); 
FSa11 = param( 83 ); 
FSb11 = param( 84 ); 
FSa21 = param( 85 ); 
FSb21 = param( 86 ); 
FS002 = param( 87 ); 
FSa12 = param( 88 ); 
FSb12 = param( 89 ); 
FSa22 = param( 90 ); 
FSb22 = param( 91 ); 
FS003 = param( 92 ); 
FSa13 = param( 93 ); 
FSb13 = param( 94 ); 
FSa23 = param( 95 ); 
FSb23 = param( 96 ); 
FS004 = param( 97 ); 
FSa14 = param( 98 ); 
FSb14 = param( 99 ); 
FSa24 = param( 100 ); 
FSb24 = param( 101 ); 
FS005 = param( 102 ); 
FSa15 = param( 103 ); 
FSb15 = param( 104 ); 
FSa25 = param( 105 ); 
FSb25 = param( 106 ); 
FS006 = param( 107 ); 
FSa16 = param( 108 ); 
FSb16 = param( 109 ); 
FSa26 = param( 110 ); 
FSb26 = param( 111 ); 

atom39 = cos(b);
atom37 = cos(c);
atom47 = atom39*atom37;
atom38 = sin(c);
atom48 = -atom38*atom39;
atom1368 = atom47*r;
atom1369 = atom48*e;
atom1370 = atom1368+atom1369;
atom40 = sin(b);
atom291 = -atom40*atom37;
atom292 = atom38*atom40;
atom1941 = -atom291*e;
atom1940 = atom292*r;
atom1942 = atom1941+atom1940;
atom80 = sin(b1);
atom41 = cos(a);
atom42 = sin(a);
atom43 = atom42*atom40;
atom52 = -atom38*atom43;
atom54 = atom52+atom41*atom37;
atom49 = atom43*atom37;
atom51 = atom49+atom41*atom38;
atom1372 = atom54*e;
atom1371 = r*atom51;
atom1373 = atom1372+atom1371;
atom45 = -atom41*atom40;
atom58 = -atom38*atom45;
atom60 = atom58+atom42*atom37;
atom55 = atom45*atom37;
atom57 = atom55+atom42*atom38;
atom1736 = atom60*r;
atom1735 = -atom57*e;
atom1737 = atom1736+atom1735;
atom44 = -atom42*atom39;
atom1721 = atom44*atom38;
atom1723 = -atom44*atom37;
atom1957 = atom1721*r;
atom1956 = -atom1723*e;
atom1958 = atom1957+atom1956;
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
atom1734 = atom1733+atom1731;
atom1952 = -atom52*e;
atom1951 = -r*atom49;
atom1724 = atom1723*r;
atom1722 = atom1721*e;
atom1725 = atom1724+atom1722;
atom1375 = atom60*e;
atom1374 = atom57*r;
atom1376 = atom1375+atom1374;
atom1726 = -atom51*e;
atom1727 = r*atom54;
atom1728 = atom1726+atom1727;
atom1975 = atom1730*r;
atom1976 = -atom1732*e;
atom1977 = atom1975+atom1976;
atom1729 = -atom80*L*atom82;
atom1382 = -atom81*L*atom79;
atom1970 = -r*atom55;
atom1971 = -atom58*e;
atom1989 = -atom1941+atom1940;
atom1389 = atom1368-atom1369;
atom104 = sin(b2);
atom1390 = -atom1372+atom1371;
atom1746 = atom1736-atom1735;
atom2000 = atom1957-atom1956;
atom1745 = atom1733-atom1731;
atom106 = sin(a2);
atom103 = cos(b2);
atom1396 = L*atom106*atom103;
atom105 = cos(a2);
atom1747 = atom104*atom105*L;
atom1397 = -atom105*L*atom103;
atom1744 = -atom104*L*atom106;
atom2012 = atom1975-atom1976;
atom1742 = atom1724-atom1722;
atom1391 = -atom1375+atom1374;
atom1743 = -atom1726+atom1727;
atom1 = sqrt(3);
atom0 = -1/2*r;
atom2 = 1/2*e*atom1;
atom3 = atom0+atom2;
atom4 = -1/2*r*atom1;
atom5 = -1/2*e;
atom6 = atom4+atom5;
atom1404 = atom47*atom3;
atom1405 = atom6*atom48;
atom1406 = atom1404+atom1405;
atom2026 = atom292*atom3;
atom2027 = -atom291*atom6;
atom2028 = atom2026+atom2027;
atom128 = sin(b3);
atom129 = cos(a3);
atom131 = 1/2*atom1;
atom1776 = atom128*L*atom129;
atom2035 = atom131*atom1776;
atom1416 = -atom128*L;
atom127 = cos(b3);
atom130 = sin(a3);
atom1417 = atom127*L*atom130;
atom2037 = atom131*atom1417;
atom2060 = 1/2*atom1417;
atom2062 = 1/2*atom1776;
atom1774 = atom60*atom3;
atom1773 = -atom57*atom6;
atom1775 = atom1774+atom1773;
atom1771 = atom1732*atom3;
atom1770 = atom1730*atom6;
atom1772 = atom1771+atom1770;
atom1408 = atom6*atom54;
atom1407 = atom3*atom51;
atom1409 = atom1408+atom1407;
atom2051 = -atom52*atom6;
atom2050 = -atom49*atom3;
atom2047 = -atom1723*atom6;
atom2046 = atom1721*atom3;
atom2048 = atom2047+atom2046;
atom1418 = -atom127*L*atom129;
atom1757 = -atom128*L*atom130;
atom2076 = -atom6*atom58;
atom2075 = -atom55*atom3;
atom2072 = -atom1732*atom6;
atom2071 = atom1730*atom3;
atom2073 = atom2072+atom2071;
atom1761 = atom1723*atom3;
atom1760 = atom1721*atom6;
atom1762 = atom1761+atom1760;
atom1411 = atom60*atom6;
atom1410 = atom57*atom3;
atom1412 = atom1411+atom1410;
atom1764 = atom3*atom54;
atom1763 = -atom6*atom51;
atom1765 = atom1764+atom1763;
atom7 = atom0-atom2;
atom8 = atom4-atom5;
atom2091 = atom292*atom7;
atom2092 = -atom291*atom8;
atom2093 = atom2091+atom2092;
atom1432 = atom8*atom48;
atom1431 = atom47*atom7;
atom1433 = atom1432+atom1431;
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
atom2117 = atom2116+atom2115;
atom1802 = atom60*atom7;
atom1803 = -atom57*atom8;
atom1804 = atom1802+atom1803;
atom1435 = atom8*atom54;
atom1434 = atom7*atom51;
atom1436 = atom1435+atom1434;
atom2112 = -atom8*atom52;
atom2111 = -atom7*atom49;
atom1800 = atom1730*atom8;
atom1799 = atom7*atom1732;
atom1801 = atom1800+atom1799;
atom2127 = 1/2*atom1805;
atom2125 = 1/2*atom1444;
atom1790 = atom7*atom1723;
atom1789 = atom1721*atom8;
atom1791 = atom1790+atom1789;
atom1793 = atom7*atom54;
atom1792 = -atom8*atom51;
atom1794 = atom1793+atom1792;
atom1437 = atom7*atom57;
atom1438 = atom60*atom8;
atom1439 = atom1437+atom1438;
atom1786 = -atom169*L*atom171;
atom1445 = -atom170*L*atom168;
atom2138 = -atom7*atom55;
atom2137 = -atom8*atom58;
atom2142 = -atom1732*atom8;
atom2141 = atom7*atom1730;
atom2143 = atom2142+atom2141;
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
atom2156 = atom2091-atom2092;
atom2184 = 1/2*atom1465;
atom2186 = 1/2*atom1822;
atom1821 = atom1802-atom1803;
atom1459 = -atom1435+atom1434;
atom2176 = -atom2116+atom2115;
atom1820 = -atom1800+atom1799;
atom1466 = -atom210*L*atom208;
atom1811 = -atom209*atom211*L;
atom1814 = atom1790-atom1789;
atom1815 = atom1793-atom1792;
atom1460 = atom1437-atom1438;
atom2196 = -atom2142+atom2141;
atom250 = cos(a6);
atom249 = sin(b6);
atom1839 = atom250*L*atom249;
atom2220 = -atom1839*atom131;
atom251 = sin(a6);
atom248 = cos(b6);
atom1486 = atom251*L*atom248;
atom2218 = -atom131*atom1486;
atom2211 = atom2026-atom2027;
atom1479 = atom1404-atom1405;
atom1485 = -L*atom249;
atom2229 = -atom2047+atom2046;
atom1837 = atom1771-atom1770;
atom1480 = -atom1408+atom1407;
atom1838 = atom1774-atom1773;
atom2241 = 1/2*atom1839;
atom2239 = 1/2*atom1486;
atom1826 = -atom251*L*atom249;
atom1487 = -atom250*L*atom248;
atom2251 = -atom2072+atom2071;
atom1831 = atom1761-atom1760;
atom1832 = atom1764-atom1763;
atom1481 = -atom1411+atom1410;

Gamma_ = [(atom1370*dB-dc*atom1942)*dB+dB1^2*atom80*L-(dB*atom1942-atom1370*dc)*dc;
-(dB*atom1958-atom1737*da-dc*atom1373)*dc-(da1*atom1381+dB1*atom1738)*da1+(atom1737*dc+da*atom1373+atom1734*dB)*da-dB1*(dB1*atom1381+da1*atom1738)-((atom1952+atom1951)*dB-atom1734*da+dc*atom1958)*dB;
-dB1*(dB1*atom1382-atom1729*da1)+(atom1376*da-atom1725*dB-atom1728*dc)*da+(dB1*atom1729-atom1382*da1)*da1-(dc*atom1977+atom1725*da+dB*(atom1970+atom1971))*dB+(dc*atom1376-atom1728*da-atom1977*dB)*dc;
dB*(atom1389*dB-dc*atom1989)+dc*(atom1389*dc-dB*atom1989)+dB2^2*atom104*L;
-da2*(atom1396*da2+dB2*atom1747)-dB2*(dB2*atom1396+atom1747*da2)+(atom1745*dB+atom1390*da+atom1746*dc)*da+(atom1390*dc-dB*atom2000+atom1746*da)*dc+(atom1745*da+dB*(atom1952-atom1951)-dc*atom2000)*dB;
-(atom1743*dc+atom1742*dB-atom1391*da)*da+dB2*(da2*atom1744-dB2*atom1397)+dc*(dc*atom1391-atom1743*da-dB*atom2012)-(dc*atom2012+atom1742*da+(atom1970-atom1971)*dB)*dB-da2*(da2*atom1397-dB2*atom1744);
(atom1406*dB-atom2028*dc)*dB+(atom1406*dc-atom2028*dB)*dc+(da3*atom2037+atom2035*dB3)*da3+1/2*(2*atom2035*da3+(atom1416+2*atom2037)*dB3)*dB3;
-((atom131*atom1416-atom2060)*dB3-atom2062*da3)*dB3-(atom2048*dc+(atom2051+atom2050)*dB-atom1772*da)*dB+(da3*atom2060+atom2062*dB3)*da3+dc*(da*atom1775-atom2048*dB+atom1409*dc)+(atom1772*dB+dc*atom1775+atom1409*da)*da;
-(atom1418*dB3-da3*atom1757)*dB3+(da*atom1412-atom1762*dB-atom1765*dc)*da-(atom1762*da+(atom2076+atom2075)*dB+atom2073*dc)*dB+(atom1757*dB3-da3*atom1418)*da3+(dc*atom1412-atom2073*dB-atom1765*da)*dc;
da4*(atom2102*da4+atom2100*dB4)+1/2*((2*atom2102+atom1443)*dB4+2*da4*atom2100)*dB4+dB*(atom1433*dB-atom2093*dc)+dc*(atom1433*dc-atom2093*dB);
-((atom2112+atom2111)*dB+atom2117*dc-atom1801*da)*dB-dc*(atom2117*dB-atom1804*da-dc*atom1436)+(da*atom1436+dc*atom1804+dB*atom1801)*da+da4*(da4*atom2125+dB4*atom2127)+dB4*((atom2125-atom131*atom1443)*dB4+da4*atom2127);
-da*(atom1791*dB-atom1439*da+dc*atom1794)-(atom2143*dc+atom1791*da+(atom2138+atom2137)*dB)*dB+(atom1786*dB4-da4*atom1445)*da4+(atom1439*dc-atom2143*dB-atom1794*da)*dc-(atom1445*dB4-da4*atom1786)*dB4;
1/2*(2*da5*atom2165+(atom1464+2*atom2163)*dB5)*dB5-dc*(dB*atom2156-dc*atom1458)+da5*(atom2165*dB5+da5*atom2163)+(dB*atom1458-dc*atom2156)*dB;
dB*((atom2112-atom2111)*dB+atom1820*da-dc*atom2176)+da5*(da5*atom2184+atom2186*dB5)+dB5*((atom2184+atom131*atom1464)*dB5+da5*atom2186)-(dB*atom2176-dc*atom1459-atom1821*da)*dc+(atom1820*dB+da*atom1459+atom1821*dc)*da;
(atom1460*da-dc*atom1815-atom1814*dB)*da-(dB*(atom2138-atom2137)+atom2196*dc+atom1814*da)*dB-da5*(da5*atom1466-atom1811*dB5)-dc*(atom2196*dB-atom1460*dc+atom1815*da)-(atom1466*dB5-da5*atom1811)*dB5;
(dB*atom1479-atom2211*dc)*dB+da6*(da6*atom2218+atom2220*dB6)+(dc*atom1479-atom2211*dB)*dc+1/2*((2*atom2218+atom1485)*dB6+2*da6*atom2220)*dB6;
da6*(da6*atom2239+atom2241*dB6)+dB6*(da6*atom2241+(atom131*atom1485+atom2239)*dB6)+(atom1837*dB+dc*atom1838+atom1480*da)*da-(dB*atom2229-da*atom1838-atom1480*dc)*dc+(atom1837*da+dB*(atom2051-atom2050)-dc*atom2229)*dB;
-(dB*atom1831+atom1832*dc-atom1481*da)*da+da6*(dB6*atom1826-da6*atom1487)-(da*atom1831-(atom2076-atom2075)*dB+dc*atom2251)*dB+(da6*atom1826-atom1487*dB6)*dB6-(dB*atom2251-atom1481*dc+atom1832*da)*dc];

%endfunction
function PhiInit_q_ = PhiInit_q(q,time,param)

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

atom38 = sin(c);
atom40 = sin(b);
atom292 = atom38*atom40;
atom37 = cos(c);
atom291 = -atom40*atom37;
atom1715 = atom292*e;
atom1714 = atom291*r;
atom39 = cos(b);
atom48 = -atom38*atom39;
atom47 = atom39*atom37;
atom1717 = r*atom48;
atom1718 = -atom47*e;
atom79 = cos(b1);
atom42 = sin(a);
atom41 = cos(a);
atom45 = -atom41*atom40;
atom60 = -atom38*atom45+atom42*atom37;
atom57 = atom45*atom37+atom42*atom38;
atom1375 = atom60*e;
atom1374 = atom57*r;
atom44 = -atom42*atom39;
atom1723 = -atom44*atom37;
atom1721 = atom44*atom38;
atom1724 = atom1723*r;
atom1722 = atom1721*e;
atom43 = atom42*atom40;
atom51 = atom43*atom37+atom41*atom38;
atom54 = atom41*atom37-atom38*atom43;
atom1726 = -atom51*e;
atom1727 = r*atom54;
atom81 = cos(a1);
atom80 = sin(b1);
atom82 = sin(a1);
atom1372 = atom54*e;
atom1371 = r*atom51;
atom46 = atom41*atom39;
atom1732 = -atom46*atom37;
atom1730 = atom38*atom46;
atom1733 = r*atom1732;
atom1731 = atom1730*e;
atom1736 = atom60*r;
atom1735 = -atom57*e;
atom103 = cos(b2);
atom105 = cos(a2);
atom104 = sin(b2);
atom106 = sin(a2);
atom1 = sqrt(3);
atom0 = -1/2*r;
atom2 = 1/2*e*atom1;
atom3 = atom0+atom2;
atom4 = -1/2*r*atom1;
atom5 = -1/2*e;
atom6 = atom4+atom5;
atom1748 = atom291*atom3;
atom1749 = atom292*atom6;
atom1751 = atom48*atom3;
atom1752 = -atom47*atom6;
atom127 = cos(b3);
atom129 = cos(a3);
atom131 = 1/2*atom1;
atom1418 = -atom127*L*atom129;
atom1755 = -atom127*L;
atom128 = sin(b3);
atom130 = sin(a3);
atom1757 = -atom128*L*atom130;
atom1411 = atom60*atom6;
atom1410 = atom57*atom3;
atom1761 = atom1723*atom3;
atom1760 = atom1721*atom6;
atom1764 = atom3*atom54;
atom1763 = -atom6*atom51;
atom1408 = atom6*atom54;
atom1407 = atom3*atom51;
atom1771 = atom1732*atom3;
atom1770 = atom1730*atom6;
atom1774 = atom60*atom3;
atom1773 = -atom57*atom6;
atom8 = atom4-atom5;
atom7 = atom0-atom2;
atom1777 = atom292*atom8;
atom1778 = atom7*atom291;
atom1781 = atom7*atom48;
atom1780 = -atom47*atom8;
atom170 = cos(a4);
atom168 = cos(b4);
atom1445 = -atom170*L*atom168;
atom169 = sin(b4);
atom171 = sin(a4);
atom1786 = -atom169*L*atom171;
atom1784 = -L*atom168;
atom1437 = atom7*atom57;
atom1438 = atom60*atom8;
atom1790 = atom7*atom1723;
atom1789 = atom1721*atom8;
atom1793 = atom7*atom54;
atom1792 = -atom8*atom51;
atom1435 = atom8*atom54;
atom1434 = atom7*atom51;
atom1800 = atom1730*atom8;
atom1799 = atom7*atom1732;
atom1802 = atom60*atom7;
atom1803 = -atom57*atom8;
atom210 = cos(a5);
atom208 = cos(b5);
atom1466 = -atom210*L*atom208;
atom209 = sin(b5);
atom211 = sin(a5);
atom1811 = -atom209*atom211*L;
atom1809 = -L*atom208;
atom250 = cos(a6);
atom248 = cos(b6);
atom1487 = -atom250*L*atom248;
atom251 = sin(a6);
atom249 = sin(b6);
atom1826 = -atom251*L*atom249;
atom1828 = -L*atom248;

PhiInit_q_ = [1.0 , 0.0 , 0.0 , 0.0 , atom1715+atom1714 , atom1717+atom1718 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , L*atom79 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , -atom1375-atom1374 , atom1724+atom1722 , atom1726+atom1727 , -atom81*L*atom79 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom80*L*atom82 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , atom1372+atom1371 , atom1733+atom1731 , atom1736+atom1735 , -L*atom82*atom79 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom80*atom81*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
1.0 , 0.0 , 0.0 , 0.0 , -atom1715+atom1714 , atom1717-atom1718 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , L*atom103 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , atom1375-atom1374 , atom1724-atom1722 , -atom1726+atom1727 , 0.0 , -atom105*L*atom103 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom104*L*atom106 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , -atom1372+atom1371 , atom1733-atom1731 , atom1736-atom1735 , 0.0 , -L*atom106*atom103 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom104*atom105*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0 , 0.0 , 0.0 , 0.0 , 0.0;
1.0 , 0.0 , 0.0 , 0.0 , atom1748+atom1749 , atom1751+atom1752 , 0.0 , 0.0 , -atom131*atom1418 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom131*atom1757+1/2*atom1755 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , -atom1411-atom1410 , atom1761+atom1760 , atom1764+atom1763 , 0.0 , 0.0 , -1/2*atom1418 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom131*atom1755+1/2*atom1757 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , atom1408+atom1407 , atom1771+atom1770 , atom1774+atom1773 , 0.0 , 0.0 , -atom127*L*atom130 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom128*L*atom129 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0 , 0.0 , 0.0 , 0.0;
1.0 , 0.0 , 0.0 , 0.0 , atom1777+atom1778 , atom1781+atom1780 , 0.0 , 0.0 , 0.0 , -atom131*atom1445 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1/2*atom1784+atom131*atom1786 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , -atom1437-atom1438 , atom1790+atom1789 , atom1793+atom1792 , 0.0 , 0.0 , 0.0 , -1/2*atom1445 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom131*atom1784+1/2*atom1786 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , atom1435+atom1434 , atom1800+atom1799 , atom1802+atom1803 , 0.0 , 0.0 , 0.0 , -L*atom171*atom168 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom169*atom170*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0 , 0.0 , 0.0;
1.0 , 0.0 , 0.0 , 0.0 , -atom1777+atom1778 , atom1781-atom1780 , 0.0 , 0.0 , 0.0 , 0.0 , atom131*atom1466 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1/2*atom1809-atom131*atom1811 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , -atom1437+atom1438 , atom1790-atom1789 , atom1793-atom1792 , 0.0 , 0.0 , 0.0 , 0.0 , -1/2*atom1466 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom1809*atom131+1/2*atom1811 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , -atom1435+atom1434 , -atom1800+atom1799 , atom1802-atom1803 , 0.0 , 0.0 , 0.0 , 0.0 , -atom211*L*atom208 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom209*atom210*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0 , 0.0;
1.0 , 0.0 , 0.0 , 0.0 , atom1748-atom1749 , atom1751-atom1752 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom131*atom1487 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1/2*atom1828-atom131*atom1826 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , atom1411-atom1410 , atom1761-atom1760 , atom1764-atom1763 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1/2*atom1487 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom131*atom1828+1/2*atom1826 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , -atom1408+atom1407 , atom1771-atom1770 , atom1774-atom1773 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom251*L*atom248 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom250*L*atom249 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0];

%endfunction
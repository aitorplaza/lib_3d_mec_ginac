function PhiInit_ = PhiInit(q,time,param)

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

atom39 = cos(b);
atom37 = cos(c);
atom47 = atom39*atom37;
atom38 = sin(c);
atom48 = -atom38*atom39;
atom1368 = atom47*r;
atom1369 = atom48*e;
atom79 = cos(b1);
atom41 = cos(a);
atom42 = sin(a);
atom40 = sin(b);
atom43 = atom42*atom40;
atom54 = atom41*atom37-atom38*atom43;
atom51 = atom43*atom37+atom41*atom38;
atom1372 = atom54*e;
atom1371 = r*atom51;
atom45 = -atom41*atom40;
atom60 = -atom38*atom45+atom42*atom37;
atom57 = atom45*atom37+atom42*atom38;
atom1375 = atom60*e;
atom1374 = atom57*r;
atom103 = cos(b2);
atom1 = sqrt(3);
atom0 = -1/2*r;
atom2 = 1/2*e*atom1;
atom3 = atom0+atom2;
atom4 = -1/2*r*atom1;
atom5 = -1/2*e;
atom6 = atom4+atom5;
atom1404 = atom47*atom3;
atom1405 = atom6*atom48;
atom1419 = -sin(b3)*L+R;
atom127 = cos(b3);
atom131 = 1/2*atom1;
atom1420 = e+atom127*L*sin(a3);
atom1408 = atom6*atom54;
atom1407 = atom3*atom51;
atom1411 = atom60*atom6;
atom1410 = atom57*atom3;
atom1446 = R-sin(b4)*L;
atom168 = cos(b4);
atom1447 = L*atom168*sin(a4)-e;
atom8 = atom4-atom5;
atom7 = atom0-atom2;
atom1432 = atom8*atom48;
atom1431 = atom47*atom7;
atom1435 = atom8*atom54;
atom1434 = atom7*atom51;
atom1437 = atom7*atom57;
atom1438 = atom60*atom8;
atom1467 = -sin(b5)*L+R;
atom208 = cos(b5);
atom1468 = sin(a5)*L*atom208+e;
atom248 = cos(b6);
atom1489 = sin(a6)*L*atom248-e;
atom1488 = -L*sin(b6)+R;

PhiInit_ = [atom1368+atom1369+sin(b1)*L+x-R;
atom1372-L*sin(a1)*atom79+y+atom1371-e;
atom1375+atom1374-s1+z+L*cos(a1)*atom79;
atom1368+sin(b2)*L-atom1369+x-R;
-L*sin(a2)*atom103-atom1372+y+atom1371+e;
-atom1375-s2+atom1374+z+L*cos(a2)*atom103;
atom1404+1/2*atom1419+atom131*atom1420+x+atom1405;
atom1408+y+atom1407+1/2*atom1420-atom131*atom1419;
atom127*L*cos(a3)-s3+atom1411+z+atom1410;
1/2*atom1446+x+atom1432+atom131*atom1447+atom1431;
atom1435+y-atom131*atom1446+atom1434+1/2*atom1447;
-s4+L*cos(a4)*atom168+atom1437+z+atom1438;
1/2*atom1467+x-atom131*atom1468-atom1432+atom1431;
-atom1435+atom131*atom1467+y+atom1434+1/2*atom1468;
-s5+atom1437+z+cos(a5)*L*atom208-atom1438;
-atom131*atom1489+atom1404+1/2*atom1488+x-atom1405;
1/2*atom1489-atom1408+y+atom131*atom1488+atom1407;
-atom1411+z+cos(a6)*L*atom248+atom1410-s6];

%endfunction

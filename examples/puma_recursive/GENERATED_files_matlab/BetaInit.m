function BetaInit_ = BetaInit(q,time,param)

a1 = q( 1 ); 
a2 = q( 2 ); 
a3 = q( 3 ); 
a4 = q( 4 ); 
a5 = q( 5 ); 
a6 = q( 6 ); 

t= time ;

g = param( 1 ); 
d3 = param( 2 ); 
r3 = param( 3 ); 
d4 = param( 4 ); 
r4 = param( 5 ); 
m1 = param( 6 ); 
mx1 = param( 7 ); 
my1 = param( 8 ); 
mz1 = param( 9 ); 
Ixx1 = param( 10 ); 
Ixy1 = param( 11 ); 
Ixz1 = param( 12 ); 
Iyy1 = param( 13 ); 
Iyz1 = param( 14 ); 
Izz1 = param( 15 ); 
m2 = param( 16 ); 
mx2 = param( 17 ); 
my2 = param( 18 ); 
mz2 = param( 19 ); 
Ixx2 = param( 20 ); 
Ixy2 = param( 21 ); 
Ixz2 = param( 22 ); 
Iyy2 = param( 23 ); 
Iyz2 = param( 24 ); 
Izz2 = param( 25 ); 
m3 = param( 26 ); 
mx3 = param( 27 ); 
my3 = param( 28 ); 
mz3 = param( 29 ); 
Ixx3 = param( 30 ); 
Ixy3 = param( 31 ); 
Ixz3 = param( 32 ); 
Iyy3 = param( 33 ); 
Iyz3 = param( 34 ); 
Izz3 = param( 35 ); 
m4 = param( 36 ); 
mx4 = param( 37 ); 
my4 = param( 38 ); 
mz4 = param( 39 ); 
Ixx4 = param( 40 ); 
Ixy4 = param( 41 ); 
Ixz4 = param( 42 ); 
Iyy4 = param( 43 ); 
Iyz4 = param( 44 ); 
Izz4 = param( 45 ); 
m5 = param( 46 ); 
mx5 = param( 47 ); 
my5 = param( 48 ); 
mz5 = param( 49 ); 
Ixx5 = param( 50 ); 
Ixy5 = param( 51 ); 
Ixz5 = param( 52 ); 
Iyy5 = param( 53 ); 
Iyz5 = param( 54 ); 
Izz5 = param( 55 ); 
m6 = param( 56 ); 
mx6 = param( 57 ); 
my6 = param( 58 ); 
mz6 = param( 59 ); 
Ixx6 = param( 60 ); 
Ixy6 = param( 61 ); 
Ixz6 = param( 62 ); 
Iyy6 = param( 63 ); 
Iyz6 = param( 64 ); 
Izz6 = param( 65 ); 
Ma1 = param( 66 ); 
Ma2 = param( 67 ); 
Ma3 = param( 68 ); 
Ma4 = param( 69 ); 
Ma5 = param( 70 ); 
Ma6 = param( 71 ); 
FS001 = param( 72 ); 
FSa11 = param( 73 ); 
FSb11 = param( 74 ); 
FSa21 = param( 75 ); 
FSb21 = param( 76 ); 
FSa31 = param( 77 ); 
FSb31 = param( 78 ); 
FSa41 = param( 79 ); 
FSb41 = param( 80 ); 
FS002 = param( 81 ); 
FSa12 = param( 82 ); 
FSb12 = param( 83 ); 
FSa22 = param( 84 ); 
FSb22 = param( 85 ); 
FSa32 = param( 86 ); 
FSb32 = param( 87 ); 
FSa42 = param( 88 ); 
FSb42 = param( 89 ); 
FS003 = param( 90 ); 
FSa13 = param( 91 ); 
FSb13 = param( 92 ); 
FSa23 = param( 93 ); 
FSb23 = param( 94 ); 
FSa33 = param( 95 ); 
FSb33 = param( 96 ); 
FSa43 = param( 97 ); 
FSb43 = param( 98 ); 
FS004 = param( 99 ); 
FSa14 = param( 100 ); 
FSb14 = param( 101 ); 
FSa24 = param( 102 ); 
FSb24 = param( 103 ); 
FSa34 = param( 104 ); 
FSb34 = param( 105 ); 
FSa44 = param( 106 ); 
FSb44 = param( 107 ); 
FS005 = param( 108 ); 
FSa15 = param( 109 ); 
FSb15 = param( 110 ); 
FSa25 = param( 111 ); 
FSb25 = param( 112 ); 
FSa35 = param( 113 ); 
FSb35 = param( 114 ); 
FSa45 = param( 115 ); 
FSb45 = param( 116 ); 
FS006 = param( 117 ); 
FSa16 = param( 118 ); 
FSb16 = param( 119 ); 
FSa26 = param( 120 ); 
FSb26 = param( 121 ); 
FSa36 = param( 122 ); 
FSb36 = param( 123 ); 
FSa46 = param( 124 ); 
FSb46 = param( 125 ); 
g = param( 126 ); 

atom2255 = 3*t;
atom2269 = -3*sin(atom2255);
atom2259 = 2*t;
atom2266 = 2*cos(atom2259);
atom2251 = 4*t;
atom2253 = 4*cos(atom2251);
atom2263 = cos(t);
atom2257 = 3*cos(atom2255);
atom2272 = -4*sin(atom2251);
atom2274 = sin(t);
atom2261 = -2*sin(atom2259);

BetaInit_ = [FSa41*atom2253+atom2263*FSa11+atom2266*FSa21+atom2261*FSb21+atom2272*FSb41-atom2274*FSb11+atom2269*FSb31+atom2257*FSa31;
atom2266*FSa22+atom2272*FSb42+atom2257*FSa32-FSb12*atom2274+atom2269*FSb32+FSa42*atom2253+FSb22*atom2261+FSa12*atom2263;
-FSb13*atom2274+atom2263*FSa13+atom2257*FSa33+FSb43*atom2272+atom2261*FSb23+FSa23*atom2266+atom2253*FSa43+atom2269*FSb33;
atom2272*FSb44+atom2257*FSa34+atom2261*FSb24+FSa24*atom2266+atom2269*FSb34+atom2263*FSa14-FSb14*atom2274+FSa44*atom2253;
atom2263*FSa15-atom2274*FSb15+FSa25*atom2266+atom2257*FSa35+FSb35*atom2269+atom2261*FSb25+FSa45*atom2253+atom2272*FSb45;
FSa46*atom2253+atom2266*FSa26+atom2272*FSb46+FSb26*atom2261+FSa16*atom2263+atom2269*FSb36-atom2274*FSb16+atom2257*FSa36];

%endfunction
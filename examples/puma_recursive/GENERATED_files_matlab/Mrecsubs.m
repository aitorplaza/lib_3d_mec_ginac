function Mrecsubs_ = Mrecsubs(q,time,param)

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

atom35 = cos(a2);
atom36 = sin(a2);
atom57 = a3+a2;
atom59 = sin(atom57);
atom58 = cos(atom57);
atom3607 = atom59*atom36+atom58*atom35;
atom3610 = atom58*atom36-atom35*atom59;
atom5612 = atom35*atom3610-atom36*atom3607;
atom5616 = -atom36*atom3610-atom35*atom3607;
atom3603 = -atom35*r3;
atom3604 = r3*atom36;
atom3613 = -atom3610*atom3604+atom3603*atom3607;
atom532 = atom35*d3;
atom81 = sin(a4);
atom6494 = atom532-d4*atom5616-atom5612*r4;
atom80 = cos(a4);
atom6497 = atom3613*atom80+atom81*atom6494;
atom6537 = atom6494*atom80-atom81*atom3613;
atom6502 = -atom81*atom5612;
atom6504 = atom5612*atom80;
atom3616 = atom3607*atom3604+atom3603*atom3610;
atom115 = sin(a5);
atom114 = cos(a5);
atom6526 = atom3616*atom115+atom114*atom6497;
atom6507 = atom114*atom6504+atom115*atom5616;
atom6530 = atom114*atom5616-atom115*atom6504;
atom152 = cos(a6);
atom153 = sin(a6);
atom6509 = atom152*atom6507+atom6502*atom153;
atom6513 = atom6502*atom152-atom6507*atom153;
atom6540 = atom6537*atom153+atom6526*atom152;
atom6552 = -atom6526*atom153+atom6537*atom152;
atom6593 = Izz6*atom6513+atom6552*mx6-atom6530*Izz6-my6*atom6540+Ixz6*atom6509;
atom6603 = atom6502*Iyz5-atom6593+atom6507*Ixy5+mz5*atom6526-atom6537*mx5+atom6530*Iyy5;
atom6500 = -atom6497*atom115+atom114*atom3616;
atom6632 = -atom6530*Iyz6+mx6*atom6500+mz6*atom6540+Iyy6*atom6513+Ixy6*atom6509;
atom6622 = Ixy6*atom6513-atom6552*mz6-atom6530*Ixz6-my6*atom6500+atom6509*Ixx6;
atom6635 = -mz5*atom6500+atom152*atom6622+atom6530*Ixy5-atom153*atom6632+atom6537*my5+atom6507*Ixx5+Ixz5*atom6502;
atom6647 = atom6537*mx4-atom115*atom6635+Ixz4*atom6504+Izz4*atom6502-my4*atom6497-atom114*atom6603-Izz4*atom5616;
atom6554 = atom6552*m6-mz6*atom6509-atom6530*mx6;
atom6545 = m6*atom6540+mz6*atom6513+my6*atom6530;
atom6581 = -mz4*atom6504+atom6537*m5+atom6507*my5-atom5616*mx4+atom6537*m4+atom6545*atom153-atom6530*mx5+atom6554*atom152;
atom6522 = atom6513*mx6-mz5*atom6507+m5*atom6500+m6*atom6500-my6*atom6509+atom6502*mx5;
atom6557 = -atom6554*atom153+atom152*atom6545+atom6530*mz5-atom6502*my5+m5*atom6526;
atom6565 = atom6497*m4+my4*atom5616+atom114*atom6557+atom6502*mz4-atom115*atom6522;
atom6583 = atom6581*atom80+atom81*atom6565;
atom6650 = -atom6583*d4+atom5612*Ixy3-atom532*mx3+Iyy3*atom5616-atom6647+mz3*atom3613;
atom6664 = Ixy4*atom6502+atom114*atom6635-Ixz4*atom5616+atom6504*Ixx4-atom6537*mz4-atom115*atom6603-atom3616*my4;
atom6687 = atom152*atom6632+atom153*atom6622+Ixz5*atom6507+atom6530*Izz5+Izz5*atom6502-atom6526*my5+mx5*atom6500;
atom6688 = atom6502*Iyy4+atom3616*mx4+atom6687-atom5616*Iyz4+Ixy4*atom6504+atom6497*mz4;
atom6694 = atom6664*atom80-atom3616*mz3-atom6583*r4+atom5612*Ixx3+atom5616*Ixy3-atom81*atom6688+my3*atom532;
atom6713 = -atom6502*mx4+my4*atom6504-atom115*atom6557-atom3616*m4-atom114*atom6522;
atom6717 = atom3616*m3-atom5612*mz3-atom6713;
atom6724 = -atom81*atom6581+atom6565*atom80;
atom6725 = m3*atom3613+atom6724+mz3*atom5616;
atom6734 = -atom6725*atom3610+atom6717*atom3607;
atom3617 = -atom3610*d3;
atom3792 = -atom3617-r4;
atom3852 = -atom3792*atom80;
atom6788 = mz4*atom80;
atom3853 = atom81*atom3792;
atom3618 = atom3607*d3;
atom3791 = d4+atom3618;
atom6759 = atom114*atom3852+atom115*atom3791;
atom6779 = atom3853*atom152-atom6759*atom153;
atom2439 = atom81*atom115;
atom4225 = atom81*atom114;
atom4702 = atom152*atom4225+atom153*atom80;
atom6776 = atom2439*mx6-mz6*atom4702;
atom6781 = m6*atom6779+atom6776;
atom4705 = atom152*atom80-atom153*atom4225;
atom6767 = atom6759*atom152+atom3853*atom153;
atom6771 = -my6*atom2439+atom4705*mz6;
atom6772 = atom6767*m6+atom6771;
atom6763 = -mz5*atom2439-atom80*my5;
atom6784 = atom6763+atom6772*atom152-atom153*atom6781+atom6759*m5;
atom6745 = -atom115*atom3852+atom114*atom3791;
atom6749 = my6*atom4702-atom4705*mx6;
atom6753 = -mz5*atom4225+mx5*atom80;
atom6756 = atom6753+m6*atom6745+m5*atom6745-atom6749;
atom6790 = atom6788-atom115*atom6756+atom3852*m4+atom114*atom6784;
atom6793 = -atom81*mz4;
atom6797 = atom2439*mx5+atom4225*my5;
atom6804 = atom6797+atom152*atom6781+atom3853*m5+atom6793+atom6772*atom153+atom3853*m4;
atom6911 = -atom81*atom6804+atom6790*atom80;
atom6912 = -my3+m3*atom3617+atom6911;
atom6899 = -atom80*mx4+atom81*my4;
atom6902 = -atom114*atom6756+atom6899-atom115*atom6784-atom3791*m4;
atom6905 = mx3-atom6902+m3*atom3618;
atom6806 = atom6804*atom80+atom81*atom6790;
atom3840 = Izz4*atom80+atom81*Ixz4;
atom6851 = atom2439*Iyz6+atom4705*Iyy6+Ixy6*atom4702;
atom6852 = atom6767*mz6+atom6851+atom6745*mx6;
atom6841 = Ixz6*atom2439+Ixx6*atom4702+Ixy6*atom4705;
atom6842 = -mz6*atom6779-my6*atom6745+atom6841;
atom6830 = -atom2439*Ixy5+Ixx5*atom4225+Ixz5*atom80;
atom6855 = atom6830+atom3853*my5+atom6842*atom152-atom153*atom6852-mz5*atom6745;
atom6820 = atom80*Iyz5+atom4225*Ixy5-atom2439*Iyy5;
atom6814 = Izz6*atom2439+Ixz6*atom4702+atom4705*Izz6;
atom6815 = atom6814+atom6779*mx6-atom6767*my6;
atom6824 = atom6759*mz5+atom6820-atom3853*mx5-atom6815;
atom6859 = atom3840+atom3853*mx4-my4*atom3852-atom114*atom6824-atom115*atom6855;
atom6862 = -atom6859+mz3*atom3617-d4*atom6806+Iyz3;
atom3819 = Ixy4*atom80+atom81*Ixx4;
atom6868 = -atom3853*mz4-atom6824*atom115-my4*atom3791+atom3819+atom114*atom6855;
atom6877 = Izz5*atom80-Izz5*atom2439+Ixz5*atom4225;
atom3821 = atom81*Ixy4+Iyy4*atom80;
atom6882 = -atom6759*my5+atom6745*mx5+atom152*atom6852+atom6877+atom6842*atom153;
atom6883 = atom3821+atom3791*mx4+atom6882+mz4*atom3852;
atom6889 = atom80*atom6868-atom81*atom6883-mz3*atom3618+Ixz3-r4*atom6806;
atom6921 = atom6905*atom3607-atom6912*atom3610;
atom3854 = r4*atom80;
atom6931 = atom114*d4-atom115*atom3854;
atom6939 = atom115*d4+atom114*atom3854;
atom3855 = -atom81*r4;
atom6950 = -atom6939*atom153+atom3855*atom152;
atom6989 = -my6*atom6931-mz6*atom6950+atom6841;
atom6944 = atom3855*atom153+atom6939*atom152;
atom6994 = atom6944*mz6+mx6*atom6931+atom6851;
atom7019 = -atom6939*my5+atom152*atom6994+atom6989*atom153+mx5*atom6931+atom6877;
atom7020 = atom7019+atom3821+d4*mx4+mz4*atom3854;
atom6997 = atom6830+atom152*atom6989-mz5*atom6931-atom6994*atom153+atom3855*my5;
atom6977 = atom6950*mx6+atom6814-my6*atom6944;
atom6981 = mz5*atom6939-atom3855*mx5-atom6977+atom6820;
atom7009 = -atom115*atom6981+atom114*atom6997-my4*d4-atom3855*mz4+atom3819;
atom6952 = m6*atom6950+atom6776;
atom6946 = atom6944*m6+atom6771;
atom6970 = atom3855*m4+atom6797+atom152*atom6952+atom6793+atom6946*atom153+m5*atom3855;
atom6955 = atom6946*atom152+atom6763+atom6939*m5-atom6952*atom153;
atom6936 = atom6753-atom6749+m6*atom6931+m5*atom6931;
atom6960 = atom6788-atom115*atom6936+m4*atom3854+atom114*atom6955;
atom6972 = atom80*atom6970+atom81*atom6960;
atom7025 = atom80*atom7009-atom81*atom7020+Ixz3-atom6972*r4;
atom7001 = atom3840-atom114*atom6981+atom3855*mx4-atom6997*atom115-my4*atom3854;
atom7003 = -atom6972*d4-atom7001+Iyz3;
atom7039 = -atom81*atom6970+atom6960*atom80;
atom7040 = -my3+atom7039;
atom7034 = -d4*m4-atom114*atom6936+atom6899-atom115*atom6955;
atom7035 = mx3-atom7034;
atom7049 = atom7035*atom3607-atom7040*atom3610;
atom4699 = -atom115*atom153;
atom7066 = -atom4699*mz6-atom114*my6;
atom4698 = atom115*atom152;
atom7070 = atom114*mx6+mz6*atom4698;
atom7073 = atom152*atom7066-atom153*atom7070-atom114*mz5;
atom7061 = mz5*atom115+my6*atom4698-atom4699*mx6;
atom7133 = -atom114*atom7061-atom115*atom7073;
atom7085 = atom152*atom7070-atom115*my5+atom7066*atom153+atom114*mx5+mx4;
atom7076 = -atom115*atom7061-my4+atom114*atom7073;
atom7137 = atom7076*atom80-atom81*atom7085;
atom7087 = atom7085*atom80+atom81*atom7076;
atom4869 = atom114*Izz6;
atom7092 = -atom4699*Izz6-Ixz6*atom4698+atom4869;
atom7093 = -atom115*Ixy5-atom114*Iyy5-atom7092;
atom7105 = atom114*Iyz6-Ixy6*atom4698-atom4699*Iyy6;
atom7099 = -atom4698*Ixx6+atom114*Ixz6-Ixy6*atom4699;
atom7108 = -atom114*Ixy5-atom7105*atom153+atom152*atom7099-atom115*Ixx5;
atom7111 = Izz4-atom114*atom7093-atom115*atom7108;
atom7112 = -atom7111-d4*atom7087;
atom7117 = Ixz4-atom115*atom7093+atom114*atom7108;
atom7122 = atom152*atom7105-atom114*Izz5+atom153*atom7099-Ixz5*atom115;
atom7123 = Iyz4+atom7122;
atom7127 = atom7117*atom80-atom7087*r4-atom81*atom7123;
atom7146 = -atom7133*atom3607-atom7137*atom3610;
atom7161 = -mz6*atom153;
atom7159 = mz6*atom152;
atom7170 = atom7161*atom152+atom7159*atom153;
atom7156 = my6*atom153-atom152*mx6;
atom7157 = -atom7156+mx5;
atom7164 = atom7159*atom152-atom7161*atom153-my5;
atom7166 = atom114*atom7164-atom7157*atom115;
atom7198 = atom7166*atom80-atom81*atom7170;
atom7194 = -atom115*atom7164-atom114*atom7157;
atom7207 = -atom7198*atom3610-atom7194*atom3607;
atom7172 = atom7170*atom80+atom81*atom7166;
atom4670 = atom153*Ixx6+Ixy6*atom152;
atom4672 = atom152*Iyy6+Ixy6*atom153;
atom7176 = Ixz5-atom4672*atom153+atom152*atom4670;
atom4673 = Ixz6*atom153;
atom4691 = Izz6*atom152+atom4673;
atom7174 = Iyz5-atom4691;
atom7178 = -atom115*atom7176-atom114*atom7174;
atom7179 = -atom7178-d4*atom7172;
atom7183 = atom114*atom7176-atom115*atom7174;
atom4921 = -atom4672*atom152-Izz5-atom153*atom4670;
atom7188 = -atom7172*r4+atom81*atom4921+atom7183*atom80;
atom7217 = -my6*atom152-atom153*mx6;
atom7218 = atom114*atom7217;
atom7221 = atom81*atom7218-atom7156*atom80;
atom4668 = Ixz6*atom152-atom153*Iyz6;
atom7227 = atom114*atom4668+Izz6*atom115;
atom4675 = atom152*Iyz6+atom4673;
atom7232 = -atom7221*r4-atom81*atom4675+atom7227*atom80;
atom4870 = -atom115*atom4668+atom4869;
atom7223 = -atom4870-atom7221*d4;
atom7240 = atom7218*atom80+atom81*atom7156;
atom7236 = -atom115*atom7217;
atom7249 = -atom7236*atom3607-atom7240*atom3610;
atom8855 = Izz3*atom5616+atom81*atom6664+atom6724*r4+atom5612*Ixz3-d4*atom6713+atom6688*atom80+atom3616*mx3-my3*atom3613;
atom7265 = atom3618*mx3+Izz3+atom6883*atom80+atom81*atom6868-d4*atom6902-my3*atom3617+atom6911*r4;
atom7276 = r4*atom7039+atom7020*atom80+Izz3+atom81*atom7009-d4*atom7034;
atom7285 = atom7117*atom81+atom7123*atom80+atom7137*r4-d4*atom7133;
atom7294 = -d4*atom7194-atom80*atom4921+atom7198*r4+atom81*atom7183;
atom7302 = atom7240*r4+atom80*atom4675+atom81*atom7227-d4*atom7236;

Mrecsubs_ = [Izz1+atom35*(atom36*Ixy2+atom35*Iyy2-atom3607*atom6650-(atom5616*mx3-atom6583-my3*atom5612-atom532*m3)*d3+atom6694*atom3610-r3*(atom6717*atom3610+atom6725*atom3607))+atom36*(atom35*Ixy2+r3*atom6734-atom6694*atom3607-atom3610*atom6650+atom36*Ixx2) , -atom36*(Ixz2+atom6889*atom3607+atom6862*atom3610-r3*atom6921)+atom35*(d3*atom6806-r3*(atom6905*atom3610+atom6912*atom3607)-atom6862*atom3607-Iyz2+atom6889*atom3610) , -atom36*(atom7025*atom3607+atom7003*atom3610-r3*atom7049)+atom35*(atom6972*d3+atom7025*atom3610-r3*(atom7035*atom3610+atom7040*atom3607)-atom7003*atom3607) , atom35*(atom7127*atom3610-atom3607*atom7112+r3*(atom7133*atom3610-atom7137*atom3607)+atom7087*d3)+(r3*atom7146-atom3610*atom7112-atom3607*atom7127)*atom36 , (atom7172*d3-atom7179*atom3607+atom3610*atom7188-r3*(atom7198*atom3607-atom7194*atom3610))*atom35-(atom3607*atom7188-r3*atom7207+atom7179*atom3610)*atom36 , atom35*(r3*(atom7236*atom3610-atom7240*atom3607)+atom7232*atom3610+atom7221*d3-atom3607*atom7223)-(atom3607*atom7232-atom7249*r3+atom7223*atom3610)*atom36;
atom8855-Ixz2*atom36+atom6734*d3-atom35*Izz2 , Izz2+atom6921*d3+atom7265 , atom7276+atom7049*d3 , atom7285+d3*atom7146 , atom7294+atom7207*d3 , atom7249*d3+atom7302;
atom8855 , atom7265 , atom7276 , atom7285 , atom7294 , atom7302;
atom6647 , atom6859 , atom7001 , atom7111 , atom7178 , atom4870;
atom6687 , atom6882 , atom7019 , atom7122 , -atom4921 , atom4675;
atom6593 , atom6815 , atom6977 , atom7092 , atom4691 , Izz6];

%endfunction

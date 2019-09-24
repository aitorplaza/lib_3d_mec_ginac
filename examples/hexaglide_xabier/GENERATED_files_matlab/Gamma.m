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
alfa = param( 6 ); 
mP = param( 7 ); 
mxP = param( 8 ); 
myP = param( 9 ); 
mzP = param( 10 ); 
IxxP = param( 11 ); 
IxyP = param( 12 ); 
IyyP = param( 13 ); 
IxzP = param( 14 ); 
IzzP = param( 15 ); 
IyzP = param( 16 ); 
m1 = param( 17 ); 
mx1 = param( 18 ); 
my1 = param( 19 ); 
mz1 = param( 20 ); 
Ixx1 = param( 21 ); 
Ixy1 = param( 22 ); 
Iyy1 = param( 23 ); 
Ixz1 = param( 24 ); 
Izz1 = param( 25 ); 
Iyz1 = param( 26 ); 
m2 = param( 27 ); 
mx2 = param( 28 ); 
my2 = param( 29 ); 
mz2 = param( 30 ); 
Ixx2 = param( 31 ); 
Ixy2 = param( 32 ); 
Iyy2 = param( 33 ); 
Ixz2 = param( 34 ); 
Izz2 = param( 35 ); 
Iyz2 = param( 36 ); 
m3 = param( 37 ); 
mx3 = param( 38 ); 
my3 = param( 39 ); 
mz3 = param( 40 ); 
Ixx3 = param( 41 ); 
Ixy3 = param( 42 ); 
Iyy3 = param( 43 ); 
Ixz3 = param( 44 ); 
Izz3 = param( 45 ); 
Iyz3 = param( 46 ); 
m4 = param( 47 ); 
mx4 = param( 48 ); 
my4 = param( 49 ); 
mz4 = param( 50 ); 
Ixx4 = param( 51 ); 
Ixy4 = param( 52 ); 
Iyy4 = param( 53 ); 
Ixz4 = param( 54 ); 
Izz4 = param( 55 ); 
Iyz4 = param( 56 ); 
m5 = param( 57 ); 
mx5 = param( 58 ); 
my5 = param( 59 ); 
mz5 = param( 60 ); 
Ixx5 = param( 61 ); 
Ixy5 = param( 62 ); 
Iyy5 = param( 63 ); 
Ixz5 = param( 64 ); 
Izz5 = param( 65 ); 
Iyz5 = param( 66 ); 
m6 = param( 67 ); 
mx6 = param( 68 ); 
my6 = param( 69 ); 
mz6 = param( 70 ); 
Ixx6 = param( 71 ); 
Ixy6 = param( 72 ); 
Iyy6 = param( 73 ); 
Ixz6 = param( 74 ); 
Izz6 = param( 75 ); 
Iyz6 = param( 76 ); 
Fs1 = param( 77 ); 
Fs2 = param( 78 ); 
Fs3 = param( 79 ); 
Fs4 = param( 80 ); 
Fs5 = param( 81 ); 
Fs6 = param( 82 ); 
FS001 = param( 83 ); 
FSa11 = param( 84 ); 
FSb11 = param( 85 ); 
FSa21 = param( 86 ); 
FSb21 = param( 87 ); 
FS002 = param( 88 ); 
FSa12 = param( 89 ); 
FSb12 = param( 90 ); 
FSa22 = param( 91 ); 
FSb22 = param( 92 ); 
FS003 = param( 93 ); 
FSa13 = param( 94 ); 
FSb13 = param( 95 ); 
FSa23 = param( 96 ); 
FSb23 = param( 97 ); 
FS004 = param( 98 ); 
FSa14 = param( 99 ); 
FSb14 = param( 100 ); 
FSa24 = param( 101 ); 
FSb24 = param( 102 ); 
FS005 = param( 103 ); 
FSa15 = param( 104 ); 
FSb15 = param( 105 ); 
FSa25 = param( 106 ); 
FSb25 = param( 107 ); 
FS006 = param( 108 ); 
FSa16 = param( 109 ); 
FSb16 = param( 110 ); 
FSa26 = param( 111 ); 
FSb26 = param( 112 ); 

atom39 = cos(c);
atom41 = cos(b);
atom49 = atom39*atom41;
atom40 = sin(c);
atom50 = -atom40*atom41;
atom1372 = atom49*r;
atom1373 = e*atom50;
atom1374 = atom1372+atom1373;
atom42 = sin(b);
atom296 = atom42*atom40;
atom295 = -atom42*atom39;
atom3796 = atom296*r;
atom3795 = -e*atom295;
atom3797 = atom3796+atom3795;
atom43 = cos(a);
atom48 = atom43*atom41;
atom3667 = atom40*atom48;
atom3669 = -atom39*atom48;
atom3668 = e*atom3667;
atom3670 = atom3669*r;
atom3671 = atom3668+atom3670;
atom44 = sin(a);
atom47 = -atom42*atom43;
atom60 = -atom40*atom47;
atom62 = atom39*atom44+atom60;
atom57 = atom39*atom47;
atom59 = atom44*atom40+atom57;
atom3673 = atom62*r;
atom3672 = -atom59*e;
atom3674 = atom3673+atom3672;
atom45 = atom42*atom44;
atom54 = -atom40*atom45;
atom56 = atom43*atom39+atom54;
atom51 = atom39*atom45;
atom53 = atom51+atom43*atom40;
atom1376 = e*atom56;
atom1375 = r*atom53;
atom1377 = atom1376+atom1375;
atom46 = -atom44*atom41;
atom3659 = atom40*atom46;
atom3661 = -atom39*atom46;
atom3810 = atom3659*r;
atom3811 = -e*atom3661;
atom3812 = atom3810+atom3811;
atom3806 = -atom51*r;
atom3805 = -atom54*e;
atom3660 = e*atom3659;
atom3662 = atom3661*r;
atom3663 = atom3660+atom3662;
atom1379 = atom62*e;
atom1378 = atom59*r;
atom1380 = atom1379+atom1378;
atom3665 = atom56*r;
atom3664 = -e*atom53;
atom3666 = atom3665+atom3664;
atom3820 = -e*atom60;
atom3821 = -atom57*r;
atom3824 = atom3667*r;
atom3825 = -e*atom3669;
atom3826 = atom3824+atom3825;
atom3835 = atom3796-atom3795;
atom1387 = atom1372-atom1373;
atom1388 = -atom1376+atom1375;
atom3680 = atom3673-atom3672;
atom3679 = -atom3668+atom3670;
atom3845 = atom3810-atom3811;
atom3854 = atom3824-atom3825;
atom3677 = -atom3660+atom3662;
atom3678 = atom3665-atom3664;
atom1389 = -atom1379+atom1378;
atom0 = 2*alfa;
atom1 = sin(atom0);
atom3 = cos(atom0);
atom2 = -e*atom1;
atom4 = atom3*r;
atom5 = atom2+atom4;
atom7 = r*atom1;
atom6 = atom3*e;
atom8 = atom7+atom6;
atom3864 = atom5*atom296;
atom3863 = -atom8*atom295;
atom3865 = atom3864+atom3863;
atom1396 = atom5*atom49;
atom1397 = atom8*atom50;
atom1398 = atom1396+atom1397;
atom3874 = -atom54*atom8;
atom3873 = -atom5*atom51;
atom3694 = atom5*atom3669;
atom3693 = atom8*atom3667;
atom3695 = atom3694+atom3693;
atom3878 = -atom3661*atom8;
atom3877 = atom5*atom3659;
atom3879 = atom3878+atom3877;
atom1400 = atom8*atom56;
atom1399 = atom5*atom53;
atom1401 = atom1400+atom1399;
atom3696 = -atom59*atom8;
atom3697 = atom5*atom62;
atom3698 = atom3696+atom3697;
atom3691 = atom5*atom56;
atom3690 = -atom8*atom53;
atom3692 = atom3691+atom3690;
atom1403 = atom62*atom8;
atom1402 = atom5*atom59;
atom1404 = atom1403+atom1402;
atom3889 = -atom8*atom3669;
atom3890 = atom5*atom3667;
atom3891 = atom3889+atom3890;
atom3688 = atom5*atom3661;
atom3687 = atom3659*atom8;
atom3689 = atom3688+atom3687;
atom3894 = -atom8*atom60;
atom3893 = -atom5*atom57;
atom9 = -atom2+atom4;
atom10 = atom7-atom6;
atom1415 = atom49*atom9;
atom1416 = atom10*atom50;
atom1417 = atom1415+atom1416;
atom3904 = atom296*atom9;
atom3903 = -atom10*atom295;
atom3905 = atom3904+atom3903;
atom1419 = atom10*atom56;
atom1418 = atom9*atom53;
atom1420 = atom1419+atom1418;
atom3715 = -atom10*atom59;
atom3714 = atom62*atom9;
atom3716 = atom3715+atom3714;
atom3712 = atom10*atom3667;
atom3711 = atom3669*atom9;
atom3713 = atom3712+atom3711;
atom3914 = -atom10*atom54;
atom3913 = -atom51*atom9;
atom3918 = -atom10*atom3661;
atom3917 = atom3659*atom9;
atom3919 = atom3918+atom3917;
atom3709 = atom56*atom9;
atom3708 = -atom10*atom53;
atom3710 = atom3709+atom3708;
atom3929 = atom3667*atom9;
atom3928 = -atom10*atom3669;
atom3930 = atom3929+atom3928;
atom1421 = atom59*atom9;
atom1422 = atom10*atom62;
atom1423 = atom1421+atom1422;
atom3706 = atom3661*atom9;
atom3705 = atom10*atom3659;
atom3707 = atom3706+atom3705;
atom3933 = -atom57*atom9;
atom3932 = -atom10*atom60;
atom3942 = atom3904-atom3903;
atom1432 = atom1415-atom1416;
atom1433 = -atom1419+atom1418;
atom3722 = -atom3715+atom3714;
atom3721 = -atom3712+atom3711;
atom3952 = -atom3918+atom3917;
atom1434 = atom1421-atom1422;
atom3720 = atom3709-atom3708;
atom3961 = atom3929-atom3928;
atom3719 = atom3706-atom3705;
atom3970 = atom3864-atom3863;
atom1447 = atom1396-atom1397;
atom1448 = -atom1400+atom1399;
atom3727 = atom3694-atom3693;
atom3728 = -atom3696+atom3697;
atom3981 = -atom3878+atom3877;
atom3725 = atom3688-atom3687;
atom3992 = -atom3889+atom3890;
atom1449 = -atom1403+atom1402;
atom3726 = atom3691-atom3690;

Gamma_ = [(atom1374*dc-atom3797*dB)*dc+dB*(atom1374*dB-atom3797*dc);
-dB*((atom3806+atom3805)*dB+dc*atom3812-atom3671*da)+dc*(atom1377*dc+da*atom3674-dB*atom3812)+da*(dc*atom3674+atom3671*dB+atom1377*da);
dc*(dc*atom1380-atom3666*da-dB*atom3826)-(atom3663*dB-da*atom1380+atom3666*dc)*da-dB*(atom3663*da+dc*atom3826+(atom3820+atom3821)*dB);
(atom1387*dB-dc*atom3835)*dB+(atom1387*dc-dB*atom3835)*dc;
(da*atom1388+atom3679*dB+dc*atom3680)*da-dB*(dB*(atom3806-atom3805)-atom3679*da+dc*atom3845)+dc*(da*atom3680-atom3845*dB+dc*atom1388);
dc*(dc*atom1389-atom3854*dB-atom3678*da)+da*(da*atom1389-atom3677*dB-atom3678*dc)-(atom3677*da-dB*(atom3820-atom3821)+atom3854*dc)*dB;
dB*(atom1398*dB-dc*atom3865)+dc*(atom1398*dc-dB*atom3865);
(atom1401*da+dB*atom3695+dc*atom3698)*da-dc*(atom3879*dB-da*atom3698-atom1401*dc)-dB*(atom3879*dc-da*atom3695+(atom3874+atom3873)*dB);
(da*atom1404-atom3689*dB-atom3692*dc)*da-(dB*atom3891-dc*atom1404+atom3692*da)*dc-dB*(dc*atom3891+dB*(atom3894+atom3893)+atom3689*da);
dc*(atom1417*dc-dB*atom3905)-dB*(dc*atom3905-atom1417*dB);
-dc*(atom3919*dB-dc*atom1420-atom3716*da)-(dB*(atom3914+atom3913)+dc*atom3919-atom3713*da)*dB+da*(da*atom1420+atom3713*dB+atom3716*dc);
-(dc*atom3710-da*atom1423+dB*atom3707)*da-((atom3933+atom3932)*dB+atom3930*dc+atom3707*da)*dB-dc*(atom3930*dB+atom3710*da-dc*atom1423);
(atom1432*dB-dc*atom3942)*dB+(atom1432*dc-dB*atom3942)*dc;
-dB*(atom3952*dc-atom3721*da-dB*(atom3914-atom3913))+dc*(atom3722*da-atom3952*dB+dc*atom1433)+(dc*atom3722+da*atom1433+atom3721*dB)*da;
-(atom3961*dB-dc*atom1434+da*atom3720)*dc-da*(dB*atom3719+dc*atom3720-da*atom1434)-dB*(atom3961*dc+dB*(atom3933-atom3932)+da*atom3719);
-(dc*atom3970-dB*atom1447)*dB-dc*(dB*atom3970-dc*atom1447);
(atom3727*da+dB*(atom3874-atom3873)-atom3981*dc)*dB+(atom3727*dB+da*atom1448+atom3728*dc)*da+(dc*atom1448-atom3981*dB+atom3728*da)*dc;
dc*(dc*atom1449-atom3992*dB-atom3726*da)-da*(atom3725*dB+atom3726*dc-da*atom1449)+dB*(dB*(atom3894-atom3893)-atom3725*da-atom3992*dc)];

%endfunction
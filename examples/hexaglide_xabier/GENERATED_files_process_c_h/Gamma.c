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
#define alfa param[ 5 ]
#define mP param[ 6 ]
#define mxP param[ 7 ]
#define myP param[ 8 ]
#define mzP param[ 9 ]
#define IxxP param[ 10 ]
#define IxyP param[ 11 ]
#define IyyP param[ 12 ]
#define IxzP param[ 13 ]
#define IzzP param[ 14 ]
#define IyzP param[ 15 ]
#define m1 param[ 16 ]
#define mx1 param[ 17 ]
#define my1 param[ 18 ]
#define mz1 param[ 19 ]
#define Ixx1 param[ 20 ]
#define Ixy1 param[ 21 ]
#define Iyy1 param[ 22 ]
#define Ixz1 param[ 23 ]
#define Izz1 param[ 24 ]
#define Iyz1 param[ 25 ]
#define m2 param[ 26 ]
#define mx2 param[ 27 ]
#define my2 param[ 28 ]
#define mz2 param[ 29 ]
#define Ixx2 param[ 30 ]
#define Ixy2 param[ 31 ]
#define Iyy2 param[ 32 ]
#define Ixz2 param[ 33 ]
#define Izz2 param[ 34 ]
#define Iyz2 param[ 35 ]
#define m3 param[ 36 ]
#define mx3 param[ 37 ]
#define my3 param[ 38 ]
#define mz3 param[ 39 ]
#define Ixx3 param[ 40 ]
#define Ixy3 param[ 41 ]
#define Iyy3 param[ 42 ]
#define Ixz3 param[ 43 ]
#define Izz3 param[ 44 ]
#define Iyz3 param[ 45 ]
#define m4 param[ 46 ]
#define mx4 param[ 47 ]
#define my4 param[ 48 ]
#define mz4 param[ 49 ]
#define Ixx4 param[ 50 ]
#define Ixy4 param[ 51 ]
#define Iyy4 param[ 52 ]
#define Ixz4 param[ 53 ]
#define Izz4 param[ 54 ]
#define Iyz4 param[ 55 ]
#define m5 param[ 56 ]
#define mx5 param[ 57 ]
#define my5 param[ 58 ]
#define mz5 param[ 59 ]
#define Ixx5 param[ 60 ]
#define Ixy5 param[ 61 ]
#define Iyy5 param[ 62 ]
#define Ixz5 param[ 63 ]
#define Izz5 param[ 64 ]
#define Iyz5 param[ 65 ]
#define m6 param[ 66 ]
#define mx6 param[ 67 ]
#define my6 param[ 68 ]
#define mz6 param[ 69 ]
#define Ixx6 param[ 70 ]
#define Ixy6 param[ 71 ]
#define Iyy6 param[ 72 ]
#define Ixz6 param[ 73 ]
#define Izz6 param[ 74 ]
#define Iyz6 param[ 75 ]
#define Fs1 param[ 76 ]
#define Fs2 param[ 77 ]
#define Fs3 param[ 78 ]
#define Fs4 param[ 79 ]
#define Fs5 param[ 80 ]
#define Fs6 param[ 81 ]
#define FS001 param[ 82 ]
#define FSa11 param[ 83 ]
#define FSb11 param[ 84 ]
#define FSa21 param[ 85 ]
#define FSb21 param[ 86 ]
#define FS002 param[ 87 ]
#define FSa12 param[ 88 ]
#define FSb12 param[ 89 ]
#define FSa22 param[ 90 ]
#define FSb22 param[ 91 ]
#define FS003 param[ 92 ]
#define FSa13 param[ 93 ]
#define FSb13 param[ 94 ]
#define FSa23 param[ 95 ]
#define FSb23 param[ 96 ]
#define FS004 param[ 97 ]
#define FSa14 param[ 98 ]
#define FSb14 param[ 99 ]
#define FSa24 param[ 100 ]
#define FSb24 param[ 101 ]
#define FS005 param[ 102 ]
#define FSa15 param[ 103 ]
#define FSb15 param[ 104 ]
#define FSa25 param[ 105 ]
#define FSb25 param[ 106 ]
#define FS006 param[ 107 ]
#define FSa16 param[ 108 ]
#define FSb16 param[ 109 ]
#define FSa26 param[ 110 ]
#define FSb26 param[ 111 ]
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
double atom41;
double atom49;
double atom40;
double atom50;
double atom1372;
double atom1373;
double atom1374;
double atom42;
double atom296;
double atom295;
double atom3796;
double atom3795;
double atom3797;
double atom43;
double atom48;
double atom3667;
double atom3669;
double atom3668;
double atom3670;
double atom3671;
double atom44;
double atom47;
double atom60;
double atom62;
double atom57;
double atom59;
double atom3673;
double atom3672;
double atom3674;
double atom45;
double atom54;
double atom56;
double atom51;
double atom53;
double atom1376;
double atom1375;
double atom1377;
double atom46;
double atom3659;
double atom3661;
double atom3810;
double atom3811;
double atom3812;
double atom3806;
double atom3805;
double atom3660;
double atom3662;
double atom3663;
double atom1379;
double atom1378;
double atom1380;
double atom3665;
double atom3664;
double atom3666;
double atom3820;
double atom3821;
double atom3824;
double atom3825;
double atom3826;
double atom3835;
double atom1387;
double atom1388;
double atom3680;
double atom3679;
double atom3845;
double atom3854;
double atom3677;
double atom3678;
double atom1389;
double atom0;
double atom1;
double atom3;
double atom2;
double atom4;
double atom5;
double atom7;
double atom6;
double atom8;
double atom3864;
double atom3863;
double atom3865;
double atom1396;
double atom1397;
double atom1398;
double atom3874;
double atom3873;
double atom3694;
double atom3693;
double atom3695;
double atom3878;
double atom3877;
double atom3879;
double atom1400;
double atom1399;
double atom1401;
double atom3696;
double atom3697;
double atom3698;
double atom3691;
double atom3690;
double atom3692;
double atom1403;
double atom1402;
double atom1404;
double atom3889;
double atom3890;
double atom3891;
double atom3688;
double atom3687;
double atom3689;
double atom3894;
double atom3893;
double atom9;
double atom10;
double atom1415;
double atom1416;
double atom1417;
double atom3904;
double atom3903;
double atom3905;
double atom1419;
double atom1418;
double atom1420;
double atom3715;
double atom3714;
double atom3716;
double atom3712;
double atom3711;
double atom3713;
double atom3914;
double atom3913;
double atom3918;
double atom3917;
double atom3919;
double atom3709;
double atom3708;
double atom3710;
double atom3929;
double atom3928;
double atom3930;
double atom1421;
double atom1422;
double atom1423;
double atom3706;
double atom3705;
double atom3707;
double atom3933;
double atom3932;
double atom3942;
double atom1432;
double atom1433;
double atom3722;
double atom3721;
double atom3952;
double atom1434;
double atom3720;
double atom3961;
double atom3719;
double atom3970;
double atom1447;
double atom1448;
double atom3727;
double atom3728;
double atom3981;
double atom3725;
double atom3992;
double atom1449;
double atom3726;

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

atom39 = cos(c);
atom41 = cos(b);
atom49 = atom39*atom41;
atom40 = sin(c);
atom50 = -atom40*atom41;
atom1372 = atom49*r;
atom1373 = e*atom50;
atom1374 =  atom1372+atom1373;
atom42 = sin(b);
atom296 = atom42*atom40;
atom295 = -atom42*atom39;
atom3796 = atom296*r;
atom3795 = -e*atom295;
atom3797 =  atom3796+atom3795;
atom43 = cos(a);
atom48 = atom43*atom41;
atom3667 = atom40*atom48;
atom3669 = -atom39*atom48;
atom3668 = e*atom3667;
atom3670 = atom3669*r;
atom3671 =  atom3668+atom3670;
atom44 = sin(a);
atom47 = -atom42*atom43;
atom60 = -atom40*atom47;
atom62 =  atom39*atom44+atom60;
atom57 = atom39*atom47;
atom59 =  atom44*atom40+atom57;
atom3673 = atom62*r;
atom3672 = -atom59*e;
atom3674 =  atom3673+atom3672;
atom45 = atom42*atom44;
atom54 = -atom40*atom45;
atom56 =  atom43*atom39+atom54;
atom51 = atom39*atom45;
atom53 =  atom51+atom43*atom40;
atom1376 = e*atom56;
atom1375 = r*atom53;
atom1377 =  atom1376+atom1375;
atom46 = -atom44*atom41;
atom3659 = atom40*atom46;
atom3661 = -atom39*atom46;
atom3810 = atom3659*r;
atom3811 = -e*atom3661;
atom3812 =  atom3810+atom3811;
atom3806 = -atom51*r;
atom3805 = -atom54*e;
atom3660 = e*atom3659;
atom3662 = atom3661*r;
atom3663 =  atom3660+atom3662;
atom1379 = atom62*e;
atom1378 = atom59*r;
atom1380 =  atom1379+atom1378;
atom3665 = atom56*r;
atom3664 = -e*atom53;
atom3666 =  atom3665+atom3664;
atom3820 = -e*atom60;
atom3821 = -atom57*r;
atom3824 = atom3667*r;
atom3825 = -e*atom3669;
atom3826 =  atom3824+atom3825;
atom3835 =  atom3796-atom3795;
atom1387 =  atom1372-atom1373;
atom1388 = -atom1376+atom1375;
atom3680 =  atom3673-atom3672;
atom3679 = -atom3668+atom3670;
atom3845 =  atom3810-atom3811;
atom3854 =  atom3824-atom3825;
atom3677 = -atom3660+atom3662;
atom3678 =  atom3665-atom3664;
atom1389 = -atom1379+atom1378;
atom0 = 2.0*alfa;
atom1 = sin(atom0);
atom3 = cos(atom0);
atom2 = -e*atom1;
atom4 = atom3*r;
atom5 =  atom2+atom4;
atom7 = r*atom1;
atom6 = atom3*e;
atom8 =  atom7+atom6;
atom3864 = atom5*atom296;
atom3863 = -atom8*atom295;
atom3865 =  atom3864+atom3863;
atom1396 = atom5*atom49;
atom1397 = atom8*atom50;
atom1398 =  atom1396+atom1397;
atom3874 = -atom54*atom8;
atom3873 = -atom5*atom51;
atom3694 = atom5*atom3669;
atom3693 = atom8*atom3667;
atom3695 =  atom3694+atom3693;
atom3878 = -atom3661*atom8;
atom3877 = atom5*atom3659;
atom3879 =  atom3878+atom3877;
atom1400 = atom8*atom56;
atom1399 = atom5*atom53;
atom1401 =  atom1400+atom1399;
atom3696 = -atom59*atom8;
atom3697 = atom5*atom62;
atom3698 =  atom3696+atom3697;
atom3691 = atom5*atom56;
atom3690 = -atom8*atom53;
atom3692 =  atom3691+atom3690;
atom1403 = atom62*atom8;
atom1402 = atom5*atom59;
atom1404 =  atom1403+atom1402;
atom3889 = -atom8*atom3669;
atom3890 = atom5*atom3667;
atom3891 =  atom3889+atom3890;
atom3688 = atom5*atom3661;
atom3687 = atom3659*atom8;
atom3689 =  atom3688+atom3687;
atom3894 = -atom8*atom60;
atom3893 = -atom5*atom57;
atom9 = -atom2+atom4;
atom10 =  atom7-atom6;
atom1415 = atom49*atom9;
atom1416 = atom10*atom50;
atom1417 =  atom1415+atom1416;
atom3904 = atom296*atom9;
atom3903 = -atom10*atom295;
atom3905 =  atom3904+atom3903;
atom1419 = atom10*atom56;
atom1418 = atom9*atom53;
atom1420 =  atom1419+atom1418;
atom3715 = -atom10*atom59;
atom3714 = atom62*atom9;
atom3716 =  atom3715+atom3714;
atom3712 = atom10*atom3667;
atom3711 = atom3669*atom9;
atom3713 =  atom3712+atom3711;
atom3914 = -atom10*atom54;
atom3913 = -atom51*atom9;
atom3918 = -atom10*atom3661;
atom3917 = atom3659*atom9;
atom3919 =  atom3918+atom3917;
atom3709 = atom56*atom9;
atom3708 = -atom10*atom53;
atom3710 =  atom3709+atom3708;
atom3929 = atom3667*atom9;
atom3928 = -atom10*atom3669;
atom3930 =  atom3929+atom3928;
atom1421 = atom59*atom9;
atom1422 = atom10*atom62;
atom1423 =  atom1421+atom1422;
atom3706 = atom3661*atom9;
atom3705 = atom10*atom3659;
atom3707 =  atom3706+atom3705;
atom3933 = -atom57*atom9;
atom3932 = -atom10*atom60;
atom3942 =  atom3904-atom3903;
atom1432 =  atom1415-atom1416;
atom1433 = -atom1419+atom1418;
atom3722 = -atom3715+atom3714;
atom3721 = -atom3712+atom3711;
atom3952 = -atom3918+atom3917;
atom1434 =  atom1421-atom1422;
atom3720 =  atom3709-atom3708;
atom3961 =  atom3929-atom3928;
atom3719 =  atom3706-atom3705;
atom3970 =  atom3864-atom3863;
atom1447 =  atom1396-atom1397;
atom1448 = -atom1400+atom1399;
atom3727 =  atom3694-atom3693;
atom3728 = -atom3696+atom3697;
atom3981 = -atom3878+atom3877;
atom3725 =  atom3688-atom3687;
atom3992 = -atom3889+atom3890;
atom1449 = -atom1403+atom1402;
atom3726 =  atom3691-atom3690;

_Gamma[0] =  ( atom1374*dc-atom3797*dB)*dc+dB*( atom1374*dB-atom3797*dc);
_Gamma[1] = -dB*( ( atom3806+atom3805)*dB+dc*atom3812-atom3671*da)+dc*( atom1377*dc+da*atom3674-dB*atom3812)+da*( dc*atom3674+atom3671*dB+atom1377*da);
_Gamma[2] =  dc*( dc*atom1380-atom3666*da-dB*atom3826)-( atom3663*dB-da*atom1380+atom3666*dc)*da-dB*( atom3663*da+dc*atom3826+( atom3820+atom3821)*dB);
_Gamma[3] =  ( atom1387*dB-dc*atom3835)*dB+( atom1387*dc-dB*atom3835)*dc;
_Gamma[4] =  ( da*atom1388+atom3679*dB+dc*atom3680)*da-dB*( dB*( atom3806-atom3805)-atom3679*da+dc*atom3845)+dc*( da*atom3680-atom3845*dB+dc*atom1388);
_Gamma[5] =  dc*( dc*atom1389-atom3854*dB-atom3678*da)+da*( da*atom1389-atom3677*dB-atom3678*dc)-( atom3677*da-dB*( atom3820-atom3821)+atom3854*dc)*dB;
_Gamma[6] =  dB*( atom1398*dB-dc*atom3865)+dc*( atom1398*dc-dB*atom3865);
_Gamma[7] =  ( atom1401*da+dB*atom3695+dc*atom3698)*da-dc*( atom3879*dB-da*atom3698-atom1401*dc)-dB*( atom3879*dc-da*atom3695+( atom3874+atom3873)*dB);
_Gamma[8] =  ( da*atom1404-atom3689*dB-atom3692*dc)*da-( dB*atom3891-dc*atom1404+atom3692*da)*dc-dB*( dc*atom3891+dB*( atom3894+atom3893)+atom3689*da);
_Gamma[9] =  dc*( atom1417*dc-dB*atom3905)-dB*( dc*atom3905-atom1417*dB);
_Gamma[10] = -dc*( atom3919*dB-dc*atom1420-atom3716*da)-( dB*( atom3914+atom3913)+dc*atom3919-atom3713*da)*dB+da*( da*atom1420+atom3713*dB+atom3716*dc);
_Gamma[11] = -( dc*atom3710-da*atom1423+dB*atom3707)*da-( ( atom3933+atom3932)*dB+atom3930*dc+atom3707*da)*dB-dc*( atom3930*dB+atom3710*da-dc*atom1423);
_Gamma[12] =  ( atom1432*dB-dc*atom3942)*dB+( atom1432*dc-dB*atom3942)*dc;
_Gamma[13] = -dB*( atom3952*dc-atom3721*da-dB*( atom3914-atom3913))+dc*( atom3722*da-atom3952*dB+dc*atom1433)+( dc*atom3722+da*atom1433+atom3721*dB)*da;
_Gamma[14] = -( atom3961*dB-dc*atom1434+da*atom3720)*dc-da*( dB*atom3719+dc*atom3720-da*atom1434)-dB*( atom3961*dc+dB*( atom3933-atom3932)+da*atom3719);
_Gamma[15] = -( dc*atom3970-dB*atom1447)*dB-dc*( dB*atom3970-dc*atom1447);
_Gamma[16] =  ( atom3727*da+dB*( atom3874-atom3873)-atom3981*dc)*dB+( atom3727*dB+da*atom1448+atom3728*dc)*da+( dc*atom1448-atom3981*dB+atom3728*da)*dc;
_Gamma[17] =  dc*( dc*atom1449-atom3992*dB-atom3726*da)-da*( atom3725*dB+atom3726*dc-da*atom1449)+dB*( dB*( atom3894-atom3893)-atom3725*da-atom3992*dc);

return _Gamma;
}

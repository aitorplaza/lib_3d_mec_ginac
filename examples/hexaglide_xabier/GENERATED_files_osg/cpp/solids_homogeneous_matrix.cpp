#ifndef __linux__
  #include <windows.h>
#endif
 
#include <osg/MatrixTransform>
#include <math.h>
#include "osg_root.h"
 
extern "C" {
extern void Init_param_values ( void );
extern void  Init_q_values ( void );
#include "param.h"
#include "inputs.h"
#include "unknowns.h"
#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
};
 
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
 
osg::Matrix MSol_PLATFORM_3D;
osg::Matrix MSol_BAR1_3D;
osg::Matrix MSol_BAR2_3D;
osg::Matrix MSol_BAR3_3D;
osg::Matrix MSol_BAR4_3D;
osg::Matrix MSol_BAR5_3D;
osg::Matrix MSol_BAR6_3D;
osg::Matrix MSol_BAR1V_3D;
osg::Matrix MSol_BAR2V_3D;
osg::Matrix MSol_BAR3V_3D;
osg::Matrix MSol_BAR4V_3D;
osg::Matrix MSol_BAR5V_3D;
osg::Matrix MSol_BAR6V_3D;
osg::Matrix MSol_BALL1A_3D;
osg::Matrix MSol_BALL2A_3D;
osg::Matrix MSol_BALL3A_3D;
osg::Matrix MSol_BALL4A_3D;
osg::Matrix MSol_BALL5A_3D;
osg::Matrix MSol_BALL6A_3D;
osg::Matrix MSol_BALL1D_3D;
osg::Matrix MSol_BALL2D_3D;
osg::Matrix MSol_BALL3D_3D;
osg::Matrix MSol_BALL4D_3D;
osg::Matrix MSol_BALL5D_3D;
osg::Matrix MSol_BALL6D_3D;
osg::Matrix MSol_BALL1C_3D;
osg::Matrix MSol_BALL2C_3D;
osg::Matrix MSol_BALL3C_3D;
osg::Matrix MSol_BALL4C_3D;
osg::Matrix MSol_BALL5C_3D;
osg::Matrix MSol_BALL6C_3D;
osg::Matrix MFra_Fra_PLATFORM_3D_draw;
osg::Matrix MFra_Fra_BAR1_3D_draw;
osg::Matrix MFra_Fra_BAR2_3D_draw;
osg::Matrix MFra_Fra_BAR3_3D_draw;
osg::Matrix MFra_Fra_BAR4_3D_draw;
osg::Matrix MFra_Fra_BAR5_3D_draw;
osg::Matrix MFra_Fra_BAR6_3D_draw;
 
void solids_homogeneous_matrix ( )
{
 
MSol_PLATFORM_3D.set
(cos(c)*cos(b), cos(c)*sin(b)*sin(a)+sin(c)*cos(a),-cos(c)*sin(b)*cos(a)+sin(a)*sin(c),0.0,
-sin(c)*cos(b), cos(c)*cos(a)-sin(b)*sin(a)*sin(c), sin(b)*sin(c)*cos(a)+cos(c)*sin(a),0.0,
sin(b),-sin(a)*cos(b),cos(a)*cos(b),0.0,
x,y,z,1.0);
MTrans_Sol_PLATFORM_3D->setMatrix(MSol_PLATFORM_3D);
 
MSol_BAR1_3D.set
(cos(b1),sin(b1)*sin(a1),-cos(a1)*sin(b1),0.0,
0.0,cos(a1),sin(a1),0.0,
sin(b1),-cos(b1)*sin(a1),cos(a1)*cos(b1),0.0,
R,e,s1,1.0);
MTrans_Sol_BAR1_3D->setMatrix(MSol_BAR1_3D);
 
MSol_BAR2_3D.set
(cos(b2),sin(b2)*sin(a2),-cos(a2)*sin(b2),0.0,
0.0,cos(a2),sin(a2),0.0,
sin(b2),-sin(a2)*cos(b2),cos(a2)*cos(b2),0.0,
R,-e,s2,1.0);
MTrans_Sol_BAR2_3D->setMatrix(MSol_BAR2_3D);
 
MSol_BAR3_3D.set
(-sin(b3)*sin(a3)*sin(2.0*alfa)+cos(2.0*alfa)*cos(b3), cos(b3)*sin(2.0*alfa)+sin(b3)*cos(2.0*alfa)*sin(a3),-sin(b3)*cos(a3),0.0,
-cos(a3)*sin(2.0*alfa),cos(a3)*cos(2.0*alfa),sin(a3),0.0,
 sin(a3)*cos(b3)*sin(2.0*alfa)+sin(b3)*cos(2.0*alfa), sin(b3)*sin(2.0*alfa)-cos(2.0*alfa)*sin(a3)*cos(b3),cos(a3)*cos(b3),0.0,
-e*sin(2.0*alfa)+cos(2.0*alfa)*R, R*sin(2.0*alfa)+cos(2.0*alfa)*e,s3,1.0);
MTrans_Sol_BAR3_3D->setMatrix(MSol_BAR3_3D);
 
MSol_BAR4_3D.set
(-sin(b4)*sin(a4)*sin(2.0*alfa)+cos(2.0*alfa)*cos(b4), cos(b4)*sin(2.0*alfa)+sin(b4)*cos(2.0*alfa)*sin(a4),-sin(b4)*cos(a4),0.0,
-cos(a4)*sin(2.0*alfa),cos(a4)*cos(2.0*alfa),sin(a4),0.0,
 cos(b4)*sin(a4)*sin(2.0*alfa)+sin(b4)*cos(2.0*alfa),-cos(2.0*alfa)*cos(b4)*sin(a4)+sin(b4)*sin(2.0*alfa),cos(a4)*cos(b4),0.0,
 e*sin(2.0*alfa)+cos(2.0*alfa)*R, R*sin(2.0*alfa)-cos(2.0*alfa)*e,s4,1.0);
MTrans_Sol_BAR4_3D->setMatrix(MSol_BAR4_3D);
 
MSol_BAR5_3D.set
( cos(4.0000000000000000e+00*alfa)*cos(b5)-sin(4.0000000000000000e+00*alfa)*sin(b5)*sin(a5), sin(b5)*cos(4.0000000000000000e+00*alfa)*sin(a5)+sin(4.0000000000000000e+00*alfa)*cos(b5),-cos(a5)*sin(b5),0.0,
-sin(4.0000000000000000e+00*alfa)*cos(a5),cos(a5)*cos(4.0000000000000000e+00*alfa),sin(a5),0.0,
 sin(b5)*cos(4.0000000000000000e+00*alfa)+sin(4.0000000000000000e+00*alfa)*sin(a5)*cos(b5),-cos(4.0000000000000000e+00*alfa)*sin(a5)*cos(b5)+sin(4.0000000000000000e+00*alfa)*sin(b5),cos(a5)*cos(b5),0.0,
-sin(4.0000000000000000e+00*alfa)*e+cos(4.0000000000000000e+00*alfa)*R, sin(4.0000000000000000e+00*alfa)*R+cos(4.0000000000000000e+00*alfa)*e,s5,1.0);
MTrans_Sol_BAR5_3D->setMatrix(MSol_BAR5_3D);
 
MSol_BAR6_3D.set
( cos(4.0000000000000000e+00*alfa)*cos(b6)-sin(4.0000000000000000e+00*alfa)*sin(b6)*sin(a6), sin(b6)*cos(4.0000000000000000e+00*alfa)*sin(a6)+sin(4.0000000000000000e+00*alfa)*cos(b6),-sin(b6)*cos(a6),0.0,
-sin(4.0000000000000000e+00*alfa)*cos(a6),cos(a6)*cos(4.0000000000000000e+00*alfa),sin(a6),0.0,
 sin(4.0000000000000000e+00*alfa)*sin(a6)*cos(b6)+sin(b6)*cos(4.0000000000000000e+00*alfa),-cos(4.0000000000000000e+00*alfa)*sin(a6)*cos(b6)+sin(4.0000000000000000e+00*alfa)*sin(b6),cos(a6)*cos(b6),0.0,
 sin(4.0000000000000000e+00*alfa)*e+cos(4.0000000000000000e+00*alfa)*R, sin(4.0000000000000000e+00*alfa)*R-cos(4.0000000000000000e+00*alfa)*e,s6,1.0);
MTrans_Sol_BAR6_3D->setMatrix(MSol_BAR6_3D);
 
MSol_BAR1V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
R,e,s1,1.0);
MTrans_Sol_BAR1V_3D->setMatrix(MSol_BAR1V_3D);
 
MSol_BAR2V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
R,-e,s2,1.0);
MTrans_Sol_BAR2V_3D->setMatrix(MSol_BAR2V_3D);
 
MSol_BAR3V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-e*sin(2.0*alfa)+cos(2.0*alfa)*R, R*sin(2.0*alfa)+cos(2.0*alfa)*e,s3,1.0);
MTrans_Sol_BAR3V_3D->setMatrix(MSol_BAR3V_3D);
 
MSol_BAR4V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 e*sin(2.0*alfa)+cos(2.0*alfa)*R, R*sin(2.0*alfa)-cos(2.0*alfa)*e,s4,1.0);
MTrans_Sol_BAR4V_3D->setMatrix(MSol_BAR4V_3D);
 
MSol_BAR5V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-sin(4.0000000000000000e+00*alfa)*e+cos(4.0000000000000000e+00*alfa)*R, sin(4.0000000000000000e+00*alfa)*R+cos(4.0000000000000000e+00*alfa)*e,s5,1.0);
MTrans_Sol_BAR5V_3D->setMatrix(MSol_BAR5V_3D);
 
MSol_BAR6V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 sin(4.0000000000000000e+00*alfa)*e+cos(4.0000000000000000e+00*alfa)*R, sin(4.0000000000000000e+00*alfa)*R-cos(4.0000000000000000e+00*alfa)*e,s6,1.0);
MTrans_Sol_BAR6V_3D->setMatrix(MSol_BAR6V_3D);
 
MSol_BALL1A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
R,e,s1,1.0);
MTrans_Sol_BALL1A_3D->setMatrix(MSol_BALL1A_3D);
 
MSol_BALL2A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
R,-e,s2,1.0);
MTrans_Sol_BALL2A_3D->setMatrix(MSol_BALL2A_3D);
 
MSol_BALL3A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-e*sin(2.0*alfa)+cos(2.0*alfa)*R, R*sin(2.0*alfa)+cos(2.0*alfa)*e,s3,1.0);
MTrans_Sol_BALL3A_3D->setMatrix(MSol_BALL3A_3D);
 
MSol_BALL4A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 e*sin(2.0*alfa)+cos(2.0*alfa)*R, R*sin(2.0*alfa)-cos(2.0*alfa)*e,s4,1.0);
MTrans_Sol_BALL4A_3D->setMatrix(MSol_BALL4A_3D);
 
MSol_BALL5A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-sin(4.0000000000000000e+00*alfa)*e+cos(4.0000000000000000e+00*alfa)*R, sin(4.0000000000000000e+00*alfa)*R+cos(4.0000000000000000e+00*alfa)*e,s5,1.0);
MTrans_Sol_BALL5A_3D->setMatrix(MSol_BALL5A_3D);
 
MSol_BALL6A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 sin(4.0000000000000000e+00*alfa)*e+cos(4.0000000000000000e+00*alfa)*R, sin(4.0000000000000000e+00*alfa)*R-cos(4.0000000000000000e+00*alfa)*e,s6,1.0);
MTrans_Sol_BALL6A_3D->setMatrix(MSol_BALL6A_3D);
 
MSol_BALL1D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 x-e*sin(c)*cos(b)+cos(c)*r*cos(b), ( cos(c)*cos(a)-sin(b)*sin(a)*sin(c))*e+y+( cos(c)*sin(b)*sin(a)+sin(c)*cos(a))*r, ( sin(b)*sin(c)*cos(a)+cos(c)*sin(a))*e+z-( cos(c)*sin(b)*cos(a)-sin(a)*sin(c))*r,1.0);
MTrans_Sol_BALL1D_3D->setMatrix(MSol_BALL1D_3D);
 
MSol_BALL2D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 x+e*sin(c)*cos(b)+cos(c)*r*cos(b),-( cos(c)*cos(a)-sin(b)*sin(a)*sin(c))*e+y+( cos(c)*sin(b)*sin(a)+sin(c)*cos(a))*r,-( sin(b)*sin(c)*cos(a)+cos(c)*sin(a))*e+z-( cos(c)*sin(b)*cos(a)-sin(a)*sin(c))*r,1.0);
MTrans_Sol_BALL2D_3D->setMatrix(MSol_BALL2D_3D);
 
MSol_BALL3D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 x-cos(c)*( e*sin(2.0*alfa)-cos(2.0*alfa)*r)*cos(b)-( cos(2.0*alfa)*e+r*sin(2.0*alfa))*sin(c)*cos(b), y+( cos(2.0*alfa)*e+r*sin(2.0*alfa))*( cos(c)*cos(a)-sin(b)*sin(a)*sin(c))-( cos(c)*sin(b)*sin(a)+sin(c)*cos(a))*( e*sin(2.0*alfa)-cos(2.0*alfa)*r), z+( cos(c)*sin(b)*cos(a)-sin(a)*sin(c))*( e*sin(2.0*alfa)-cos(2.0*alfa)*r)+( sin(b)*sin(c)*cos(a)+cos(c)*sin(a))*( cos(2.0*alfa)*e+r*sin(2.0*alfa)),1.0);
MTrans_Sol_BALL3D_3D->setMatrix(MSol_BALL3D_3D);
 
MSol_BALL4D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 x+cos(c)*( e*sin(2.0*alfa)+cos(2.0*alfa)*r)*cos(b)+( cos(2.0*alfa)*e-r*sin(2.0*alfa))*sin(c)*cos(b),-( cos(c)*cos(a)-sin(b)*sin(a)*sin(c))*( cos(2.0*alfa)*e-r*sin(2.0*alfa))+y+( e*sin(2.0*alfa)+cos(2.0*alfa)*r)*( cos(c)*sin(b)*sin(a)+sin(c)*cos(a)),-( e*sin(2.0*alfa)+cos(2.0*alfa)*r)*( cos(c)*sin(b)*cos(a)-sin(a)*sin(c))-( sin(b)*sin(c)*cos(a)+cos(c)*sin(a))*( cos(2.0*alfa)*e-r*sin(2.0*alfa))+z,1.0);
MTrans_Sol_BALL4D_3D->setMatrix(MSol_BALL4D_3D);
 
MSol_BALL5D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 x+cos(c)*( e*sin(2.0*alfa)+cos(2.0*alfa)*r)*cos(b)-( cos(2.0*alfa)*e-r*sin(2.0*alfa))*sin(c)*cos(b), ( cos(c)*cos(a)-sin(b)*sin(a)*sin(c))*( cos(2.0*alfa)*e-r*sin(2.0*alfa))+y+( e*sin(2.0*alfa)+cos(2.0*alfa)*r)*( cos(c)*sin(b)*sin(a)+sin(c)*cos(a)),-( e*sin(2.0*alfa)+cos(2.0*alfa)*r)*( cos(c)*sin(b)*cos(a)-sin(a)*sin(c))+( sin(b)*sin(c)*cos(a)+cos(c)*sin(a))*( cos(2.0*alfa)*e-r*sin(2.0*alfa))+z,1.0);
MTrans_Sol_BALL5D_3D->setMatrix(MSol_BALL5D_3D);
 
MSol_BALL6D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 x-cos(c)*( e*sin(2.0*alfa)-cos(2.0*alfa)*r)*cos(b)+( cos(2.0*alfa)*e+r*sin(2.0*alfa))*sin(c)*cos(b), y-( cos(2.0*alfa)*e+r*sin(2.0*alfa))*( cos(c)*cos(a)-sin(b)*sin(a)*sin(c))-( cos(c)*sin(b)*sin(a)+sin(c)*cos(a))*( e*sin(2.0*alfa)-cos(2.0*alfa)*r), z+( cos(c)*sin(b)*cos(a)-sin(a)*sin(c))*( e*sin(2.0*alfa)-cos(2.0*alfa)*r)-( sin(b)*sin(c)*cos(a)+cos(c)*sin(a))*( cos(2.0*alfa)*e+r*sin(2.0*alfa)),1.0);
MTrans_Sol_BALL6D_3D->setMatrix(MSol_BALL6D_3D);
 
MSol_BALL1C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-sin(b1)*L+R, L*cos(b1)*sin(a1)+e, s1-cos(a1)*L*cos(b1),1.0);
MTrans_Sol_BALL1C_3D->setMatrix(MSol_BALL1C_3D);
 
MSol_BALL2C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-L*sin(b2)+R, L*sin(a2)*cos(b2)-e,-cos(a2)*L*cos(b2)+s2,1.0);
MTrans_Sol_BALL2C_3D->setMatrix(MSol_BALL2C_3D);
 
MSol_BALL3C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-cos(2.0*alfa)*( sin(b3)*L-R)-( L*sin(a3)*cos(b3)+e)*sin(2.0*alfa),-( sin(b3)*L-R)*sin(2.0*alfa)+( L*sin(a3)*cos(b3)+e)*cos(2.0*alfa),-L*cos(a3)*cos(b3)+s3,1.0);
MTrans_Sol_BALL3C_3D->setMatrix(MSol_BALL3C_3D);
 
MSol_BALL4C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-( L*cos(b4)*sin(a4)-e)*sin(2.0*alfa)+( R-sin(b4)*L)*cos(2.0*alfa), cos(2.0*alfa)*( L*cos(b4)*sin(a4)-e)+( R-sin(b4)*L)*sin(2.0*alfa),-L*cos(a4)*cos(b4)+s4,1.0);
MTrans_Sol_BALL4C_3D->setMatrix(MSol_BALL4C_3D);
 
MSol_BALL5C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 ( R-L*sin(b5))*cos(4.0000000000000000e+00*alfa)-sin(4.0000000000000000e+00*alfa)*( e+L*sin(a5)*cos(b5)), cos(4.0000000000000000e+00*alfa)*( e+L*sin(a5)*cos(b5))+sin(4.0000000000000000e+00*alfa)*( R-L*sin(b5)),-L*cos(a5)*cos(b5)+s5,1.0);
MTrans_Sol_BALL5C_3D->setMatrix(MSol_BALL5C_3D);
 
MSol_BALL6C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 sin(4.0000000000000000e+00*alfa)*( e-L*sin(a6)*cos(b6))+cos(4.0000000000000000e+00*alfa)*( R-L*sin(b6)), sin(4.0000000000000000e+00*alfa)*( R-L*sin(b6))-( e-L*sin(a6)*cos(b6))*cos(4.0000000000000000e+00*alfa),-L*cos(a6)*cos(b6)+s6,1.0);
MTrans_Sol_BALL6C_3D->setMatrix(MSol_BALL6C_3D);
 
MFra_Fra_PLATFORM_3D_draw.set
(cos(c)*cos(b), cos(c)*sin(b)*sin(a)+sin(c)*cos(a),-cos(c)*sin(b)*cos(a)+sin(a)*sin(c),0.0,
-sin(c)*cos(b), cos(c)*cos(a)-sin(b)*sin(a)*sin(c), sin(b)*sin(c)*cos(a)+cos(c)*sin(a),0.0,
sin(b),-sin(a)*cos(b),cos(a)*cos(b),0.0,
x,y,z,1.0);
MTrans_Fra_Fra_PLATFORM_3D_draw->setMatrix(MFra_Fra_PLATFORM_3D_draw);
 
MFra_Fra_BAR1_3D_draw.set
(cos(b1),sin(b1)*sin(a1),-cos(a1)*sin(b1),0.0,
0.0,cos(a1),sin(a1),0.0,
sin(b1),-cos(b1)*sin(a1),cos(a1)*cos(b1),0.0,
R,e,s1,1.0);
MTrans_Fra_Fra_BAR1_3D_draw->setMatrix(MFra_Fra_BAR1_3D_draw);
 
MFra_Fra_BAR2_3D_draw.set
(cos(b2),sin(b2)*sin(a2),-cos(a2)*sin(b2),0.0,
0.0,cos(a2),sin(a2),0.0,
sin(b2),-sin(a2)*cos(b2),cos(a2)*cos(b2),0.0,
R,-e,s2,1.0);
MTrans_Fra_Fra_BAR2_3D_draw->setMatrix(MFra_Fra_BAR2_3D_draw);
 
MFra_Fra_BAR3_3D_draw.set
(-sin(b3)*sin(a3)*sin(2.0*alfa)+cos(2.0*alfa)*cos(b3), cos(b3)*sin(2.0*alfa)+sin(b3)*cos(2.0*alfa)*sin(a3),-sin(b3)*cos(a3),0.0,
-cos(a3)*sin(2.0*alfa),cos(a3)*cos(2.0*alfa),sin(a3),0.0,
 sin(a3)*cos(b3)*sin(2.0*alfa)+sin(b3)*cos(2.0*alfa), sin(b3)*sin(2.0*alfa)-cos(2.0*alfa)*sin(a3)*cos(b3),cos(a3)*cos(b3),0.0,
-e*sin(2.0*alfa)+cos(2.0*alfa)*R, R*sin(2.0*alfa)+cos(2.0*alfa)*e,s3,1.0);
MTrans_Fra_Fra_BAR3_3D_draw->setMatrix(MFra_Fra_BAR3_3D_draw);
 
MFra_Fra_BAR4_3D_draw.set
(-sin(b4)*sin(a4)*sin(2.0*alfa)+cos(2.0*alfa)*cos(b4), cos(b4)*sin(2.0*alfa)+sin(b4)*cos(2.0*alfa)*sin(a4),-sin(b4)*cos(a4),0.0,
-cos(a4)*sin(2.0*alfa),cos(a4)*cos(2.0*alfa),sin(a4),0.0,
 cos(b4)*sin(a4)*sin(2.0*alfa)+sin(b4)*cos(2.0*alfa),-cos(2.0*alfa)*cos(b4)*sin(a4)+sin(b4)*sin(2.0*alfa),cos(a4)*cos(b4),0.0,
 e*sin(2.0*alfa)+cos(2.0*alfa)*R, R*sin(2.0*alfa)-cos(2.0*alfa)*e,s4,1.0);
MTrans_Fra_Fra_BAR4_3D_draw->setMatrix(MFra_Fra_BAR4_3D_draw);
 
MFra_Fra_BAR5_3D_draw.set
( cos(4.0000000000000000e+00*alfa)*cos(b5)-sin(4.0000000000000000e+00*alfa)*sin(b5)*sin(a5), sin(b5)*cos(4.0000000000000000e+00*alfa)*sin(a5)+sin(4.0000000000000000e+00*alfa)*cos(b5),-cos(a5)*sin(b5),0.0,
-sin(4.0000000000000000e+00*alfa)*cos(a5),cos(a5)*cos(4.0000000000000000e+00*alfa),sin(a5),0.0,
 sin(b5)*cos(4.0000000000000000e+00*alfa)+sin(4.0000000000000000e+00*alfa)*sin(a5)*cos(b5),-cos(4.0000000000000000e+00*alfa)*sin(a5)*cos(b5)+sin(4.0000000000000000e+00*alfa)*sin(b5),cos(a5)*cos(b5),0.0,
-sin(4.0000000000000000e+00*alfa)*e+cos(4.0000000000000000e+00*alfa)*R, sin(4.0000000000000000e+00*alfa)*R+cos(4.0000000000000000e+00*alfa)*e,s5,1.0);
MTrans_Fra_Fra_BAR5_3D_draw->setMatrix(MFra_Fra_BAR5_3D_draw);
 
MFra_Fra_BAR6_3D_draw.set
( cos(4.0000000000000000e+00*alfa)*cos(b6)-sin(4.0000000000000000e+00*alfa)*sin(b6)*sin(a6), sin(b6)*cos(4.0000000000000000e+00*alfa)*sin(a6)+sin(4.0000000000000000e+00*alfa)*cos(b6),-sin(b6)*cos(a6),0.0,
-sin(4.0000000000000000e+00*alfa)*cos(a6),cos(a6)*cos(4.0000000000000000e+00*alfa),sin(a6),0.0,
 sin(4.0000000000000000e+00*alfa)*sin(a6)*cos(b6)+sin(b6)*cos(4.0000000000000000e+00*alfa),-cos(4.0000000000000000e+00*alfa)*sin(a6)*cos(b6)+sin(4.0000000000000000e+00*alfa)*sin(b6),cos(a6)*cos(b6),0.0,
 sin(4.0000000000000000e+00*alfa)*e+cos(4.0000000000000000e+00*alfa)*R, sin(4.0000000000000000e+00*alfa)*R-cos(4.0000000000000000e+00*alfa)*e,s6,1.0);
MTrans_Fra_Fra_BAR6_3D_draw->setMatrix(MFra_Fra_BAR6_3D_draw);
 
}

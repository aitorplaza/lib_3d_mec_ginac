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
#define gra param[ 111 ]
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
(cos(c)*cos(b), sin(b)*cos(c)*sin(a)+sin(c)*cos(a), sin(c)*sin(a)-sin(b)*cos(c)*cos(a),0.0,
-sin(c)*cos(b),-sin(b)*sin(c)*sin(a)+cos(c)*cos(a), cos(c)*sin(a)+sin(b)*sin(c)*cos(a),0.0,
sin(b),-cos(b)*sin(a),cos(b)*cos(a),0.0,
x,y,z,0.0);
MTrans_Sol_PLATFORM_3D->setMatrix(MSol_PLATFORM_3D);
 
MSol_BAR1_3D.set
(cos(b1),sin(a1)*sin(b1),-cos(a1)*sin(b1),0.0,
0.0,cos(a1),sin(a1),0.0,
sin(b1),-sin(a1)*cos(b1),cos(a1)*cos(b1),0.0,
R,e,s1,0.0);
MTrans_Sol_BAR1_3D->setMatrix(MSol_BAR1_3D);
 
MSol_BAR2_3D.set
(cos(b2),sin(a2)*sin(b2),-cos(a2)*sin(b2),0.0,
0.0,cos(a2),sin(a2),0.0,
sin(b2),-sin(a2)*cos(b2),cos(a2)*cos(b2),0.0,
R,-e,s2,0.0);
MTrans_Sol_BAR2_3D->setMatrix(MSol_BAR2_3D);
 
MSol_BAR3_3D.set
(-cos(b3)/2.0-pow(3.0,(1.0/2.0))*sin(b3)*sin(a3)/2.0,-sin(b3)*sin(a3)/2.0+pow(3.0,(1.0/2.0))*cos(b3)/2.0,-sin(b3)*cos(a3),0.0,
-(1.0/2.0)*pow(3.0,(1.0/2.0))*cos(a3),-(1.0/2.0)*cos(a3),sin(a3),0.0,
 pow(3.0,(1.0/2.0))*cos(b3)*sin(a3)/2.0-sin(b3)/2.0, pow(3.0,(1.0/2.0))*sin(b3)/2.0+cos(b3)*sin(a3)/2.0,cos(b3)*cos(a3),0.0,
-pow(3.0,(1.0/2.0))*e/2.0-R/2.0,-e/2.0+pow(3.0,(1.0/2.0))*R/2.0,s3,0.0);
MTrans_Sol_BAR3_3D->setMatrix(MSol_BAR3_3D);
 
MSol_BAR4_3D.set
(-cos(b4)/2.0-sin(a4)*pow(3.0,(1.0/2.0))*sin(b4)/2.0,-sin(a4)*sin(b4)/2.0+pow(3.0,(1.0/2.0))*cos(b4)/2.0,-cos(a4)*sin(b4),0.0,
-(1.0/2.0)*cos(a4)*pow(3.0,(1.0/2.0)),-(1.0/2.0)*cos(a4),sin(a4),0.0,
-sin(b4)/2.0+sin(a4)*pow(3.0,(1.0/2.0))*cos(b4)/2.0, pow(3.0,(1.0/2.0))*sin(b4)/2.0+sin(a4)*cos(b4)/2.0,cos(a4)*cos(b4),0.0,
 pow(3.0,(1.0/2.0))*e/2.0-R/2.0, e/2.0+pow(3.0,(1.0/2.0))*R/2.0,s4,0.0);
MTrans_Sol_BAR4_3D->setMatrix(MSol_BAR4_3D);
 
MSol_BAR5_3D.set
( sin(a5)*pow(3.0,(1.0/2.0))*sin(b5)/2.0-cos(b5)/2.0,-pow(3.0,(1.0/2.0))*cos(b5)/2.0-sin(a5)*sin(b5)/2.0,-cos(a5)*sin(b5),0.0,
(1.0/2.0)*cos(a5)*pow(3.0,(1.0/2.0)),-(1.0/2.0)*cos(a5),sin(a5),0.0,
-sin(a5)*pow(3.0,(1.0/2.0))*cos(b5)/2.0-sin(b5)/2.0, sin(a5)*cos(b5)/2.0-pow(3.0,(1.0/2.0))*sin(b5)/2.0,cos(a5)*cos(b5),0.0,
 pow(3.0,(1.0/2.0))*e/2.0-R/2.0,-e/2.0-pow(3.0,(1.0/2.0))*R/2.0,s5,0.0);
MTrans_Sol_BAR5_3D->setMatrix(MSol_BAR5_3D);
 
MSol_BAR6_3D.set
( pow(3.0,(1.0/2.0))*sin(b6)*sin(a6)/2.0-cos(b6)/2.0,-pow(3.0,(1.0/2.0))*cos(b6)/2.0-sin(b6)*sin(a6)/2.0,-sin(b6)*cos(a6),0.0,
(1.0/2.0)*pow(3.0,(1.0/2.0))*cos(a6),-(1.0/2.0)*cos(a6),sin(a6),0.0,
-sin(b6)/2.0-pow(3.0,(1.0/2.0))*cos(b6)*sin(a6)/2.0, cos(b6)*sin(a6)/2.0-pow(3.0,(1.0/2.0))*sin(b6)/2.0,cos(b6)*cos(a6),0.0,
-pow(3.0,(1.0/2.0))*e/2.0-R/2.0, e/2.0-pow(3.0,(1.0/2.0))*R/2.0,s6,0.0);
MTrans_Sol_BAR6_3D->setMatrix(MSol_BAR6_3D);
 
MSol_BAR1V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
R,e,s1,0.0);
MTrans_Sol_BAR1V_3D->setMatrix(MSol_BAR1V_3D);
 
MSol_BAR2V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
R,-e,s2,0.0);
MTrans_Sol_BAR2V_3D->setMatrix(MSol_BAR2V_3D);
 
MSol_BAR3V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-pow(3.0,(1.0/2.0))*e/2.0-R/2.0,-e/2.0+pow(3.0,(1.0/2.0))*R/2.0,s3,0.0);
MTrans_Sol_BAR3V_3D->setMatrix(MSol_BAR3V_3D);
 
MSol_BAR4V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 pow(3.0,(1.0/2.0))*e/2.0-R/2.0, e/2.0+pow(3.0,(1.0/2.0))*R/2.0,s4,0.0);
MTrans_Sol_BAR4V_3D->setMatrix(MSol_BAR4V_3D);
 
MSol_BAR5V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 pow(3.0,(1.0/2.0))*e/2.0-R/2.0,-e/2.0-pow(3.0,(1.0/2.0))*R/2.0,s5,0.0);
MTrans_Sol_BAR5V_3D->setMatrix(MSol_BAR5V_3D);
 
MSol_BAR6V_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-pow(3.0,(1.0/2.0))*e/2.0-R/2.0, e/2.0-pow(3.0,(1.0/2.0))*R/2.0,s6,0.0);
MTrans_Sol_BAR6V_3D->setMatrix(MSol_BAR6V_3D);
 
MSol_BALL1A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
R,e,s1,0.0);
MTrans_Sol_BALL1A_3D->setMatrix(MSol_BALL1A_3D);
 
MSol_BALL2A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
R,-e,s2,0.0);
MTrans_Sol_BALL2A_3D->setMatrix(MSol_BALL2A_3D);
 
MSol_BALL3A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-pow(3.0,(1.0/2.0))*e/2.0-R/2.0,-e/2.0+pow(3.0,(1.0/2.0))*R/2.0,s3,0.0);
MTrans_Sol_BALL3A_3D->setMatrix(MSol_BALL3A_3D);
 
MSol_BALL4A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 pow(3.0,(1.0/2.0))*e/2.0-R/2.0, e/2.0+pow(3.0,(1.0/2.0))*R/2.0,s4,0.0);
MTrans_Sol_BALL4A_3D->setMatrix(MSol_BALL4A_3D);
 
MSol_BALL5A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 pow(3.0,(1.0/2.0))*e/2.0-R/2.0,-e/2.0-pow(3.0,(1.0/2.0))*R/2.0,s5,0.0);
MTrans_Sol_BALL5A_3D->setMatrix(MSol_BALL5A_3D);
 
MSol_BALL6A_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-pow(3.0,(1.0/2.0))*e/2.0-R/2.0, e/2.0-pow(3.0,(1.0/2.0))*R/2.0,s6,0.0);
MTrans_Sol_BALL6A_3D->setMatrix(MSol_BALL6A_3D);
 
MSol_BALL1D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-sin(c)*cos(b)*e+r*cos(c)*cos(b)+x,-( sin(b)*sin(c)*sin(a)-cos(c)*cos(a))*e+y+r*( sin(b)*cos(c)*sin(a)+sin(c)*cos(a)), r*( sin(c)*sin(a)-sin(b)*cos(c)*cos(a))+z+e*( cos(c)*sin(a)+sin(b)*sin(c)*cos(a)),0.0);
MTrans_Sol_BALL1D_3D->setMatrix(MSol_BALL1D_3D);
 
MSol_BALL2D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 sin(c)*cos(b)*e+r*cos(c)*cos(b)+x, ( sin(b)*sin(c)*sin(a)-cos(c)*cos(a))*e+y+r*( sin(b)*cos(c)*sin(a)+sin(c)*cos(a)), r*( sin(c)*sin(a)-sin(b)*cos(c)*cos(a))+z-e*( cos(c)*sin(a)+sin(b)*sin(c)*cos(a)),0.0);
MTrans_Sol_BALL2D_3D->setMatrix(MSol_BALL2D_3D);
 
MSol_BALL3D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 x-cos(c)*cos(b)*( r-pow(3.0,(1.0/2.0))*e)/2.0+sin(c)*cos(b)*( r*pow(3.0,(1.0/2.0))+e)/2.0, y-( sin(b)*cos(c)*sin(a)+sin(c)*cos(a))*( r-pow(3.0,(1.0/2.0))*e)/2.0+( sin(b)*sin(c)*sin(a)-cos(c)*cos(a))*( r*pow(3.0,(1.0/2.0))+e)/2.0,-( cos(c)*sin(a)+sin(b)*sin(c)*cos(a))*( r*pow(3.0,(1.0/2.0))+e)/2.0+z-( sin(c)*sin(a)-sin(b)*cos(c)*cos(a))*( r-pow(3.0,(1.0/2.0))*e)/2.0,0.0);
MTrans_Sol_BALL3D_3D->setMatrix(MSol_BALL3D_3D);
 
MSol_BALL4D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-cos(c)*cos(b)*( r+pow(3.0,(1.0/2.0))*e)/2.0+( r*pow(3.0,(1.0/2.0))-e)*sin(c)*cos(b)/2.0+x,-( r+pow(3.0,(1.0/2.0))*e)*( sin(b)*cos(c)*sin(a)+sin(c)*cos(a))/2.0+y+( r*pow(3.0,(1.0/2.0))-e)*( sin(b)*sin(c)*sin(a)-cos(c)*cos(a))/2.0,-( r*pow(3.0,(1.0/2.0))-e)*( cos(c)*sin(a)+sin(b)*sin(c)*cos(a))/2.0+z-( sin(c)*sin(a)-sin(b)*cos(c)*cos(a))*( r+pow(3.0,(1.0/2.0))*e)/2.0,0.0);
MTrans_Sol_BALL4D_3D->setMatrix(MSol_BALL4D_3D);
 
MSol_BALL5D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-cos(c)*cos(b)*( r+pow(3.0,(1.0/2.0))*e)/2.0-( r*pow(3.0,(1.0/2.0))-e)*sin(c)*cos(b)/2.0+x,-( r+pow(3.0,(1.0/2.0))*e)*( sin(b)*cos(c)*sin(a)+sin(c)*cos(a))/2.0+y-( r*pow(3.0,(1.0/2.0))-e)*( sin(b)*sin(c)*sin(a)-cos(c)*cos(a))/2.0, ( r*pow(3.0,(1.0/2.0))-e)*( cos(c)*sin(a)+sin(b)*sin(c)*cos(a))/2.0+z-( sin(c)*sin(a)-sin(b)*cos(c)*cos(a))*( r+pow(3.0,(1.0/2.0))*e)/2.0,0.0);
MTrans_Sol_BALL5D_3D->setMatrix(MSol_BALL5D_3D);
 
MSol_BALL6D_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 x-cos(c)*cos(b)*( r-pow(3.0,(1.0/2.0))*e)/2.0-sin(c)*cos(b)*( r*pow(3.0,(1.0/2.0))+e)/2.0, y-( sin(b)*cos(c)*sin(a)+sin(c)*cos(a))*( r-pow(3.0,(1.0/2.0))*e)/2.0-( sin(b)*sin(c)*sin(a)-cos(c)*cos(a))*( r*pow(3.0,(1.0/2.0))+e)/2.0, ( cos(c)*sin(a)+sin(b)*sin(c)*cos(a))*( r*pow(3.0,(1.0/2.0))+e)/2.0+z-( sin(c)*sin(a)-sin(b)*cos(c)*cos(a))*( r-pow(3.0,(1.0/2.0))*e)/2.0,0.0);
MTrans_Sol_BALL6D_3D->setMatrix(MSol_BALL6D_3D);
 
MSol_BALL1C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-L*sin(b1)+R, sin(a1)*L*cos(b1)+e, s1-cos(a1)*L*cos(b1),0.0);
MTrans_Sol_BALL1C_3D->setMatrix(MSol_BALL1C_3D);
 
MSol_BALL2C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
-L*sin(b2)+R,-e+sin(a2)*L*cos(b2),-cos(a2)*L*cos(b2)+s2,0.0);
MTrans_Sol_BALL2C_3D->setMatrix(MSol_BALL2C_3D);
 
MSol_BALL3C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 L*sin(b3)/2.0-pow(3.0,(1.0/2.0))*( L*cos(b3)*sin(a3)+e)/2.0-R/2.0,-L*cos(b3)*sin(a3)/2.0-pow(3.0,(1.0/2.0))*( L*sin(b3)-R)/2.0-e/2.0, s3-L*cos(b3)*cos(a3),0.0);
MTrans_Sol_BALL3C_3D->setMatrix(MSol_BALL3C_3D);
 
MSol_BALL4C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 L*sin(b4)/2.0-R/2.0+( e-sin(a4)*L*cos(b4))*pow(3.0,(1.0/2.0))/2.0, e/2.0-sin(a4)*L*cos(b4)/2.0-pow(3.0,(1.0/2.0))*( L*sin(b4)-R)/2.0, s4-cos(a4)*L*cos(b4),0.0);
MTrans_Sol_BALL4C_3D->setMatrix(MSol_BALL4C_3D);
 
MSol_BALL5C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 pow(3.0,(1.0/2.0))*( sin(a5)*L*cos(b5)+e)/2.0+L*sin(b5)/2.0-R/2.0,-sin(a5)*L*cos(b5)/2.0-e/2.0+( L*sin(b5)-R)*pow(3.0,(1.0/2.0))/2.0,-cos(a5)*L*cos(b5)+s5,0.0);
MTrans_Sol_BALL5C_3D->setMatrix(MSol_BALL5C_3D);
 
MSol_BALL6C_3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 L*sin(b6)/2.0-pow(3.0,(1.0/2.0))*( e-L*cos(b6)*sin(a6))/2.0-R/2.0, pow(3.0,(1.0/2.0))*( L*sin(b6)-R)/2.0+e/2.0-L*cos(b6)*sin(a6)/2.0,-L*cos(b6)*cos(a6)+s6,0.0);
MTrans_Sol_BALL6C_3D->setMatrix(MSol_BALL6C_3D);
 
MFra_Fra_PLATFORM_3D_draw.set
(cos(c)*cos(b), sin(b)*cos(c)*sin(a)+sin(c)*cos(a), sin(c)*sin(a)-sin(b)*cos(c)*cos(a),0.0,
-sin(c)*cos(b),-sin(b)*sin(c)*sin(a)+cos(c)*cos(a), cos(c)*sin(a)+sin(b)*sin(c)*cos(a),0.0,
sin(b),-cos(b)*sin(a),cos(b)*cos(a),0.0,
x,y,z,0.0);
MTrans_Fra_Fra_PLATFORM_3D_draw->setMatrix(MFra_Fra_PLATFORM_3D_draw);
 
MFra_Fra_BAR1_3D_draw.set
(cos(b1),sin(a1)*sin(b1),-cos(a1)*sin(b1),0.0,
0.0,cos(a1),sin(a1),0.0,
sin(b1),-sin(a1)*cos(b1),cos(a1)*cos(b1),0.0,
R,e,s1,0.0);
MTrans_Fra_Fra_BAR1_3D_draw->setMatrix(MFra_Fra_BAR1_3D_draw);
 
MFra_Fra_BAR2_3D_draw.set
(cos(b2),sin(a2)*sin(b2),-cos(a2)*sin(b2),0.0,
0.0,cos(a2),sin(a2),0.0,
sin(b2),-sin(a2)*cos(b2),cos(a2)*cos(b2),0.0,
R,-e,s2,0.0);
MTrans_Fra_Fra_BAR2_3D_draw->setMatrix(MFra_Fra_BAR2_3D_draw);
 
MFra_Fra_BAR3_3D_draw.set
(-cos(b3)/2.0-pow(3.0,(1.0/2.0))*sin(b3)*sin(a3)/2.0,-sin(b3)*sin(a3)/2.0+pow(3.0,(1.0/2.0))*cos(b3)/2.0,-sin(b3)*cos(a3),0.0,
-(1.0/2.0)*pow(3.0,(1.0/2.0))*cos(a3),-(1.0/2.0)*cos(a3),sin(a3),0.0,
 pow(3.0,(1.0/2.0))*cos(b3)*sin(a3)/2.0-sin(b3)/2.0, pow(3.0,(1.0/2.0))*sin(b3)/2.0+cos(b3)*sin(a3)/2.0,cos(b3)*cos(a3),0.0,
-pow(3.0,(1.0/2.0))*e/2.0-R/2.0,-e/2.0+pow(3.0,(1.0/2.0))*R/2.0,s3,0.0);
MTrans_Fra_Fra_BAR3_3D_draw->setMatrix(MFra_Fra_BAR3_3D_draw);
 
MFra_Fra_BAR4_3D_draw.set
(-cos(b4)/2.0-sin(a4)*pow(3.0,(1.0/2.0))*sin(b4)/2.0,-sin(a4)*sin(b4)/2.0+pow(3.0,(1.0/2.0))*cos(b4)/2.0,-cos(a4)*sin(b4),0.0,
-(1.0/2.0)*cos(a4)*pow(3.0,(1.0/2.0)),-(1.0/2.0)*cos(a4),sin(a4),0.0,
-sin(b4)/2.0+sin(a4)*pow(3.0,(1.0/2.0))*cos(b4)/2.0, pow(3.0,(1.0/2.0))*sin(b4)/2.0+sin(a4)*cos(b4)/2.0,cos(a4)*cos(b4),0.0,
 pow(3.0,(1.0/2.0))*e/2.0-R/2.0, e/2.0+pow(3.0,(1.0/2.0))*R/2.0,s4,0.0);
MTrans_Fra_Fra_BAR4_3D_draw->setMatrix(MFra_Fra_BAR4_3D_draw);
 
MFra_Fra_BAR5_3D_draw.set
( sin(a5)*pow(3.0,(1.0/2.0))*sin(b5)/2.0-cos(b5)/2.0,-pow(3.0,(1.0/2.0))*cos(b5)/2.0-sin(a5)*sin(b5)/2.0,-cos(a5)*sin(b5),0.0,
(1.0/2.0)*cos(a5)*pow(3.0,(1.0/2.0)),-(1.0/2.0)*cos(a5),sin(a5),0.0,
-sin(a5)*pow(3.0,(1.0/2.0))*cos(b5)/2.0-sin(b5)/2.0, sin(a5)*cos(b5)/2.0-pow(3.0,(1.0/2.0))*sin(b5)/2.0,cos(a5)*cos(b5),0.0,
 pow(3.0,(1.0/2.0))*e/2.0-R/2.0,-e/2.0-pow(3.0,(1.0/2.0))*R/2.0,s5,0.0);
MTrans_Fra_Fra_BAR5_3D_draw->setMatrix(MFra_Fra_BAR5_3D_draw);
 
MFra_Fra_BAR6_3D_draw.set
( pow(3.0,(1.0/2.0))*sin(b6)*sin(a6)/2.0-cos(b6)/2.0,-pow(3.0,(1.0/2.0))*cos(b6)/2.0-sin(b6)*sin(a6)/2.0,-sin(b6)*cos(a6),0.0,
(1.0/2.0)*pow(3.0,(1.0/2.0))*cos(a6),-(1.0/2.0)*cos(a6),sin(a6),0.0,
-sin(b6)/2.0-pow(3.0,(1.0/2.0))*cos(b6)*sin(a6)/2.0, cos(b6)*sin(a6)/2.0-pow(3.0,(1.0/2.0))*sin(b6)/2.0,cos(b6)*cos(a6),0.0,
-pow(3.0,(1.0/2.0))*e/2.0-R/2.0, e/2.0-pow(3.0,(1.0/2.0))*R/2.0,s6,0.0);
MTrans_Fra_Fra_BAR6_3D_draw->setMatrix(MFra_Fra_BAR6_3D_draw);
 
}

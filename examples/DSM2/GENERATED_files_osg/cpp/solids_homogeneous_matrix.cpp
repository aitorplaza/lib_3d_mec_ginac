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
 
#define theta1 q[ 0 ]
#define theta2 q[ 1 ]
#define psi q[ 2 ]
#define y q[ 3 ]
#define z q[ 4 ]
#define dtheta1 dq[ 0 ]
#define dtheta2 dq[ 1 ]
#define dpsi dq[ 2 ]
#define dy dq[ 3 ]
#define dz dq[ 4 ]
#define ddtheta1 ddq[ 0 ]
#define ddtheta2 ddq[ 1 ]
#define ddpsi ddq[ 2 ]
#define ddy ddq[ 3 ]
#define ddz ddq[ 4 ]
 
#define g param[ 0 ]
#define theta1_0 param[ 1 ]
#define psi_0 param[ 2 ]
#define l1 param[ 3 ]
#define l2 param[ 4 ]
#define y0 param[ 5 ]
#define z0 param[ 6 ]
#define alpha param[ 7 ]
#define r param[ 8 ]
#define Cvis param[ 9 ]
#define mb1 param[ 10 ]
#define I1b1 param[ 11 ]
#define I2b1 param[ 12 ]
#define I3b1 param[ 13 ]
#define mb2 param[ 14 ]
#define I1b2 param[ 15 ]
#define I2b2 param[ 16 ]
#define I3b2 param[ 17 ]
#define mDisc param[ 18 ]
#define Torque inputs[ 0 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define lambda3 unknowns[ 2 ]
#define lambda4 unknowns[ 3 ]
 
osg::Matrix MSol_Arm1_3D;
osg::Matrix MSol_Arm2_3D;
osg::Matrix MSol_Plane_3D;
osg::Matrix MSol_Disc_3D;
osg::Matrix MFra_FraARM1_draw;
osg::Matrix MFra_FraARM2_draw;
osg::Matrix MFra_FraDISC_draw;
osg::Matrix MFra_FraPLANE_draw;
osg::Matrix MFra_FraABS_draw;
 
void solids_homogeneous_matrix ( )
{
 
MSol_Arm1_3D.set
(1.0,0.0,0.0,0.0,
0.0,cos(theta1),sin(theta1),0.0,
0.0,-sin(theta1),cos(theta1),0.0,
0.0,0.0,0.0,0.0);
MTrans_Sol_Arm1_3D->setMatrix(MSol_Arm1_3D);
 
MSol_Arm2_3D.set
(1.0,0.0,0.0,0.0,
0.0,-sin(-theta2)*sin(theta1)+cos(-theta2)*cos(theta1), sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1),0.0,
0.0,-sin(-theta2)*cos(theta1)-cos(-theta2)*sin(theta1),-sin(-theta2)*sin(theta1)+cos(-theta2)*cos(theta1),0.0,
0.0,l1*cos(theta1),l1*sin(theta1),0.0);
MTrans_Sol_Arm2_3D->setMatrix(MSol_Arm2_3D);
 
MSol_Plane_3D.set
(1.0,0.0,0.0,0.0,
0.0,cos(alpha),sin(alpha),0.0,
0.0,-sin(alpha),cos(alpha),0.0,
0.0,y0,z0,0.0);
MTrans_Sol_Plane_3D->setMatrix(MSol_Plane_3D);
 
MSol_Disc_3D.set
(1.0,0.0,0.0,0.0,
0.0,cos(-psi),sin(-psi),0.0,
0.0,-sin(-psi),cos(-psi),0.0,
0.0, ( l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1), sin(-theta2)*l2*cos(theta1)+( l1+cos(-theta2)*l2)*sin(theta1),0.0);
MTrans_Sol_Disc_3D->setMatrix(MSol_Disc_3D);
 
MFra_FraARM1_draw.set
(1.0,0.0,0.0,0.0,
0.0,cos(theta1),sin(theta1),0.0,
0.0,-sin(theta1),cos(theta1),0.0,
0.0,0.0,0.0,0.0);
MTrans_Fra_FraARM1_draw->setMatrix(MFra_FraARM1_draw);
 
MFra_FraARM2_draw.set
(1.0,0.0,0.0,0.0,
0.0,-sin(-theta2)*sin(theta1)+cos(-theta2)*cos(theta1), sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1),0.0,
0.0,-sin(-theta2)*cos(theta1)-cos(-theta2)*sin(theta1),-sin(-theta2)*sin(theta1)+cos(-theta2)*cos(theta1),0.0,
0.0,l1*cos(theta1),l1*sin(theta1),0.0);
MTrans_Fra_FraARM2_draw->setMatrix(MFra_FraARM2_draw);
 
MFra_FraDISC_draw.set
(1.0,0.0,0.0,0.0,
0.0,cos(-psi),sin(-psi),0.0,
0.0,-sin(-psi),cos(-psi),0.0,
0.0, ( l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1), sin(-theta2)*l2*cos(theta1)+( l1+cos(-theta2)*l2)*sin(theta1),0.0);
MTrans_Fra_FraDISC_draw->setMatrix(MFra_FraDISC_draw);
 
MFra_FraPLANE_draw.set
(1.0,0.0,0.0,0.0,
0.0,cos(alpha),sin(alpha),0.0,
0.0,-sin(alpha),cos(alpha),0.0,
0.0,y0,z0,0.0);
MTrans_Fra_FraPLANE_draw->setMatrix(MFra_FraPLANE_draw);
 
MFra_FraABS_draw.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,0.0);
MTrans_Fra_FraABS_draw->setMatrix(MFra_FraABS_draw);
 
}

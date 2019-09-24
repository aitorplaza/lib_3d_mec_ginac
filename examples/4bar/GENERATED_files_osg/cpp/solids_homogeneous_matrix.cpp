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
#define theta3 q[ 2 ]
#define dtheta1 dq[ 0 ]
#define dtheta2 dq[ 1 ]
#define dtheta3 dq[ 2 ]
#define ddtheta1 ddq[ 0 ]
#define ddtheta2 ddq[ 1 ]
#define ddtheta3 ddq[ 2 ]
 
#define g param[ 0 ]
#define l1 param[ 1 ]
#define l2 param[ 2 ]
#define l3 param[ 3 ]
#define l4 param[ 4 ]
#define m1 param[ 5 ]
#define m2 param[ 6 ]
#define m3 param[ 7 ]
#define cg1x param[ 8 ]
#define cg1z param[ 9 ]
#define cg2x param[ 10 ]
#define cg2z param[ 11 ]
#define cg3x param[ 12 ]
#define cg3z param[ 13 ]
#define I1yy param[ 14 ]
#define I2yy param[ 15 ]
#define I3yy param[ 16 ]
#define K param[ 17 ]
#define l2x param[ 18 ]
#define l2z param[ 19 ]
#define l3x param[ 20 ]
#define l3z param[ 21 ]
#define Fx2 inputs[ 0 ]
#define Fz2 inputs[ 1 ]
#define Fx3 inputs[ 2 ]
#define Fz3 inputs[ 3 ]
#define My2 inputs[ 4 ]
#define My3 inputs[ 5 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
 
osg::Matrix MFra_DFra_arm1_draw;
osg::Matrix MFra_DFra_arm2_draw;
osg::Matrix MFra_DFra_arm3_draw;
osg::Matrix MFra_FraABS_draw;
osg::Matrix MFra_FraABS2_draw;
osg::Matrix MVec_Varm1;
osg::Matrix MVec_Varm2;
osg::Matrix MVec_Varm3;
osg::Matrix MVec_Varm4;
osg::Matrix MVec_VOL2_OL3;
 
void solids_homogeneous_matrix ( )
{
 
MFra_DFra_arm1_draw.set
(cos(theta1),0.0,-sin(theta1),0.0,
0.0,1.0,0.0,0.0,
sin(theta1),0.0,cos(theta1),0.0,
0.0,0.0,0.0,0.0);
MTrans_Fra_DFra_arm1_draw->setMatrix(MFra_DFra_arm1_draw);
 
MFra_DFra_arm2_draw.set
( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1),0.0,-sin(theta1)*cos(theta2)-cos(theta1)*sin(theta2),0.0,
0.0,1.0,0.0,0.0,
 sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2),0.0, cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1),0.0,
cos(theta1)*l1,0.0,-sin(theta1)*l1,0.0);
MTrans_Fra_DFra_arm2_draw->setMatrix(MFra_DFra_arm2_draw);
 
MFra_DFra_arm3_draw.set
( cos(theta3)*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1))-sin(theta3)*( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2)),0.0,-sin(theta3)*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1))-( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2))*cos(theta3),0.0,
0.0,1.0,0.0,0.0,
 sin(theta3)*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1))+( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2))*cos(theta3),0.0, cos(theta3)*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1))-sin(theta3)*( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2)),0.0,
 cos(theta1)*( l2*cos(theta2)+l1)-l2*sin(theta2)*sin(theta1),0.0,-sin(theta1)*( l2*cos(theta2)+l1)-l2*cos(theta1)*sin(theta2),0.0);
MTrans_Fra_DFra_arm3_draw->setMatrix(MFra_DFra_arm3_draw);
 
MFra_FraABS_draw.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,0.0);
MTrans_Fra_FraABS_draw->setMatrix(MFra_FraABS_draw);
 
MFra_FraABS2_draw.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
l4,0.0,0.0,0.0);
MTrans_Fra_FraABS2_draw->setMatrix(MFra_FraABS2_draw);
 
if (pow((l1*l1),(1.0/2.0))<= 0.001 ){
MVec_Varm1.set
  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
else if (fabs(l1)<= 0.001 && 0.0<= 0.001){
MVec_Varm1.set
(0.0,0.0,0.0,0.0,
0.0,pow((l1*l1),(1.0/2.0)),0.0,0.0,
0.0,0.0,0.0,0.0,
0.0,0.0,0.0,0.0);
}
else {
MVec_Varm1.set
(cos(theta1)*l1,0.0,-sin(theta1)*l1,0.0,
0.0,l1,0.0,0.0,
sin(theta1)*pow((l1*l1),(1.0/2.0)),0.0,cos(theta1)*pow((l1*l1),(1.0/2.0)),0.0,
0.0,0.0,0.0,0.0);
}
MTrans_Vec_Varm1->setMatrix(MVec_Varm1);
 
if (pow((l2*l2),(1.0/2.0))<= 0.001 ){
MVec_Varm2.set
  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
else if (fabs(l2)<= 0.001 && 0.0<= 0.001){
MVec_Varm2.set
(0.0,0.0,0.0,0.0,
0.0,pow((l2*l2),(1.0/2.0)),0.0,0.0,
0.0,0.0,0.0,0.0,
cos(theta1)*l1,0.0,-sin(theta1)*l1,0.0);
}
else {
MVec_Varm2.set
(l2*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1)),0.0,-l2*( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2)),0.0,
0.0,l2,0.0,0.0,
pow((l2*l2),(1.0/2.0))*( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2)),0.0,pow((l2*l2),(1.0/2.0))*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1)),0.0,
cos(theta1)*l1,0.0,-sin(theta1)*l1,0.0);
}
MTrans_Vec_Varm2->setMatrix(MVec_Varm2);
 
if (pow((l3*l3),(1.0/2.0))<= 0.001 ){
MVec_Varm3.set
  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
else if (fabs(l3)<= 0.001 && 0.0<= 0.001){
MVec_Varm3.set
(0.0,0.0,0.0,0.0,
0.0,pow((l3*l3),(1.0/2.0)),0.0,0.0,
0.0,0.0,0.0,0.0,
 cos(theta1)*( l2*cos(theta2)+l1)-l2*sin(theta2)*sin(theta1),0.0,-sin(theta1)*( l2*cos(theta2)+l1)-l2*cos(theta1)*sin(theta2),0.0);
}
else {
MVec_Varm3.set
(( cos(theta3)*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1))-sin(theta3)*( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2)))*l3,0.0,-l3*( sin(theta3)*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1))+( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2))*cos(theta3)),0.0,
0.0,l3,0.0,0.0,
( sin(theta3)*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1))+( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2))*cos(theta3))*pow((l3*l3),(1.0/2.0)),0.0,( cos(theta3)*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1))-sin(theta3)*( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2)))*pow((l3*l3),(1.0/2.0)),0.0,
 cos(theta1)*( l2*cos(theta2)+l1)-l2*sin(theta2)*sin(theta1),0.0,-sin(theta1)*( l2*cos(theta2)+l1)-l2*cos(theta1)*sin(theta2),0.0);
}
MTrans_Vec_Varm3->setMatrix(MVec_Varm3);
 
if (pow((l4*l4),(1.0/2.0))<= 0.001 ){
MVec_Varm4.set
  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
else if (fabs(l4)<= 0.001 && 0.0<= 0.001){
MVec_Varm4.set
(0.0,0.0,0.0,0.0,
0.0,pow((l4*l4),(1.0/2.0)),0.0,0.0,
0.0,0.0,0.0,0.0,
0.0,0.0,0.0,0.0);
}
else {
MVec_Varm4.set
(l4,0.0,0.0,0.0,
0.0,l4,0.0,0.0,
0.0,0.0,pow((l4*l4),(1.0/2.0)),0.0,
0.0,0.0,0.0,0.0);
}
MTrans_Vec_Varm4->setMatrix(MVec_Varm4);
 
if (pow( pow( cos(theta3)*l3z-sin(theta3)*l3x,2.0)+pow( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x,2.0),(1.0/2.0))<= 0.001 ){
MVec_VOL2_OL3.set
  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
else if (fabs( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x)<= 0.001 && 0.0<= 0.001){
MVec_VOL2_OL3.set
(( cos(theta3)*l3z-sin(theta3)*l3x)*( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2)),0.0,( cos(theta3)*l3z-sin(theta3)*l3x)*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1)),0.0,
0.0,pow( pow( cos(theta3)*l3z-sin(theta3)*l3x,2.0)+pow( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x,2.0),(1.0/2.0)),0.0,0.0,
-( cos(theta3)*l3z-sin(theta3)*l3x)*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1)),0.0,( cos(theta3)*l3z-sin(theta3)*l3x)*( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2)),0.0,
-sin(theta2)*sin(theta1)*l2x+( cos(theta2)*l2x+l1)*cos(theta1),0.0,-( cos(theta2)*l2x+l1)*sin(theta1)-cos(theta1)*sin(theta2)*l2x,0.0);
}
else {
MVec_VOL2_OL3.set
( ( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1))*( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x)+( cos(theta3)*l3z-sin(theta3)*l3x)*( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2)),0.0, ( cos(theta3)*l3z-sin(theta3)*l3x)*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1))-( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2))*( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x),0.0,
0.0,pow(pow( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x,2.0),-(1.0/2.0))*pow( pow( cos(theta3)*l3z-sin(theta3)*l3x,2.0)+pow( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x,2.0),(1.0/2.0))*( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x),0.0,0.0,
 ( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2))*pow(pow( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x,2.0),(1.0/2.0))-( cos(theta3)*l3z-sin(theta3)*l3x)*pow(pow( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x,2.0),-(1.0/2.0))*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1))*( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x),0.0, ( cos(theta3)*l3z-sin(theta3)*l3x)*( sin(theta1)*cos(theta2)+cos(theta1)*sin(theta2))*pow(pow( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x,2.0),-(1.0/2.0))*( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x)+pow(pow( l3x*cos(theta3)+l2+sin(theta3)*l3z-l2x,2.0),(1.0/2.0))*( cos(theta1)*cos(theta2)-sin(theta2)*sin(theta1)),0.0,
-sin(theta2)*sin(theta1)*l2x+( cos(theta2)*l2x+l1)*cos(theta1),0.0,-( cos(theta2)*l2x+l1)*sin(theta1)-cos(theta1)*sin(theta2)*l2x,0.0);
}
MTrans_Vec_VOL2_OL3->setMatrix(MVec_VOL2_OL3);
 
}

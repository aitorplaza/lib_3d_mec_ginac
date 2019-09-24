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
 
#define rho1 q[ 0 ]
#define phi1 q[ 1 ]
#define phi2 q[ 2 ]
#define phi3 q[ 3 ]
#define theta1 q[ 4 ]
#define xp q[ 5 ]
#define yp q[ 6 ]
#define zp q[ 7 ]
#define ycdg q[ 8 ]
#define drho1 dq[ 0 ]
#define dphi1 dq[ 1 ]
#define dphi2 dq[ 2 ]
#define dphi3 dq[ 3 ]
#define dtheta1 dq[ 4 ]
#define dxp dq[ 5 ]
#define dyp dq[ 6 ]
#define dzp dq[ 7 ]
#define dycdg dq[ 8 ]
#define ddrho1 ddq[ 0 ]
#define ddphi1 ddq[ 1 ]
#define ddphi2 ddq[ 2 ]
#define ddphi3 ddq[ 3 ]
#define ddtheta1 ddq[ 4 ]
#define ddxp ddq[ 5 ]
#define ddyp ddq[ 6 ]
#define ddzp ddq[ 7 ]
#define ddycdg ddq[ 8 ]
 
#define g param[ 0 ]
#define pi param[ 1 ]
#define zcdg param[ 2 ]
#define R param[ 3 ]
#define man param[ 4 ]
#define r param[ 5 ]
#define l1 param[ 6 ]
#define l2 param[ 7 ]
#define l3 param[ 8 ]
#define d param[ 9 ]
#define le param[ 10 ]
#define cm param[ 11 ]
#define rm param[ 12 ]
#define hcdg param[ 13 ]
#define alpha param[ 14 ]
#define beta param[ 15 ]
#define Cvis1 param[ 16 ]
#define Cvis2 param[ 17 ]
#define Cvis3 param[ 18 ]
#define mPlataforma param[ 19 ]
#define mxPlataforma param[ 20 ]
#define myPlataforma param[ 21 ]
#define mzPlataforma param[ 22 ]
#define IxxPlataforma param[ 23 ]
#define IxyPlataforma param[ 24 ]
#define IyyPlataforma param[ 25 ]
#define IxzPlataforma param[ 26 ]
#define IzzPlataforma param[ 27 ]
#define IyzPlataforma param[ 28 ]
#define mRuedaIzq param[ 29 ]
#define mxRuedaIzq param[ 30 ]
#define myRuedaIzq param[ 31 ]
#define mzRuedaIzq param[ 32 ]
#define IxxRuedaIzq param[ 33 ]
#define IxyRuedaIzq param[ 34 ]
#define IyyRuedaIzq param[ 35 ]
#define IxzRuedaIzq param[ 36 ]
#define IzzRuedaIzq param[ 37 ]
#define IyzRuedaIzq param[ 38 ]
#define mRuedaDcha param[ 39 ]
#define mxRuedaDcha param[ 40 ]
#define myRuedaDcha param[ 41 ]
#define mzRuedaDcha param[ 42 ]
#define IxxRuedaDcha param[ 43 ]
#define IxyRuedaDcha param[ 44 ]
#define IyyRuedaDcha param[ 45 ]
#define IxzRuedaDcha param[ 46 ]
#define IzzRuedaDcha param[ 47 ]
#define IyzRuedaDcha param[ 48 ]
#define mEje param[ 49 ]
#define mxEje param[ 50 ]
#define myEje param[ 51 ]
#define mzEje param[ 52 ]
#define IxxEje param[ 53 ]
#define IxyEje param[ 54 ]
#define IyyEje param[ 55 ]
#define IxzEje param[ 56 ]
#define IzzEje param[ 57 ]
#define IyzEje param[ 58 ]
#define mManillar param[ 59 ]
#define mxManillar param[ 60 ]
#define myManillar param[ 61 ]
#define mzManillar param[ 62 ]
#define IxxManillar param[ 63 ]
#define IxyManillar param[ 64 ]
#define IyyManillar param[ 65 ]
#define IxzManillar param[ 66 ]
#define IzzManillar param[ 67 ]
#define IyzManillar param[ 68 ]
#define mRider param[ 69 ]
#define mxRider param[ 70 ]
#define myRider param[ 71 ]
#define mzRider param[ 72 ]
#define IxxRider param[ 73 ]
#define IxyRider param[ 74 ]
#define IyyRider param[ 75 ]
#define IxzRider param[ 76 ]
#define IzzRider param[ 77 ]
#define IyzRider param[ 78 ]
#define xp_0 param[ 79 ]
#define yp_0 param[ 80 ]
#define zp_0 param[ 81 ]
#define KMan param[ 82 ]
#define ycdg_input inputs[ 0 ]
#define MomRuedaIzq inputs[ 1 ]
#define MomRuedaDcha inputs[ 2 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define lambda3 unknowns[ 2 ]
#define lambda4 unknowns[ 3 ]
#define lambda5 unknowns[ 4 ]
 
osg::Matrix MSol_Plataforma3D;
osg::Matrix MSol_RuedaIzq3D;
osg::Matrix MSol_RuedaDcha3D;
osg::Matrix MSol_Manillar3D;
osg::Matrix MPnt_Rider3D;
osg::Matrix MFra_FraABS_draw;
osg::Matrix MSol_Ground3D;
osg::Matrix MVec_VectorP_J1;
osg::Matrix MVec_VectorP_J2;
osg::Matrix MVec_VectorP_S0;
osg::Matrix MVec_VectorP_S1;
osg::Matrix MVec_VectorP_S2;
osg::Matrix MVec_VectorO_P;
 
void solids_homogeneous_matrix ( )
{
 
MSol_Plataforma3D.set
(cos(rho1),sin(rho1),0.0,0.0,
-sin(rho1)*cos(phi1),cos(phi1)*cos(rho1),sin(phi1),0.0,
sin(rho1)*sin(phi1),-cos(rho1)*sin(phi1),cos(phi1),0.0,
xp,yp,zp,1.0);
MTrans_Sol_Plataforma3D->setMatrix(MSol_Plataforma3D);
 
MSol_RuedaIzq3D.set
(cos(rho1),sin(rho1),0.0,0.0,
sin(rho1)*( sin(phi2)*sin(phi1)-cos(phi1)*cos(phi2)),-( sin(phi2)*sin(phi1)-cos(phi1)*cos(phi2))*cos(rho1), cos(phi1)*sin(phi2)+sin(phi1)*cos(phi2),0.0,
sin(rho1)*( cos(phi1)*sin(phi2)+sin(phi1)*cos(phi2)),-cos(rho1)*( cos(phi1)*sin(phi2)+sin(phi1)*cos(phi2)),-sin(phi2)*sin(phi1)+cos(phi1)*cos(phi2),0.0,
 cos(rho1)*le/2.0+xp, yp+sin(rho1)*le/2.0,zp,1.0);
MTrans_Sol_RuedaIzq3D->setMatrix(MSol_RuedaIzq3D);
 
MSol_RuedaDcha3D.set
(cos(rho1),sin(rho1),0.0,0.0,
-( cos(phi1)*cos(phi3)-sin(phi3)*sin(phi1))*sin(rho1),( cos(phi1)*cos(phi3)-sin(phi3)*sin(phi1))*cos(rho1), cos(phi3)*sin(phi1)+cos(phi1)*sin(phi3),0.0,
sin(rho1)*( cos(phi3)*sin(phi1)+cos(phi1)*sin(phi3)),-( cos(phi3)*sin(phi1)+cos(phi1)*sin(phi3))*cos(rho1), cos(phi1)*cos(phi3)-sin(phi3)*sin(phi1),0.0,
-cos(rho1)*le/2.0+xp, yp-sin(rho1)*le/2.0,zp,1.0);
MTrans_Sol_RuedaDcha3D->setMatrix(MSol_RuedaDcha3D);
 
MSol_Manillar3D.set
(-sin(rho1)*sin(phi1)*sin(theta1)+cos(theta1)*cos(rho1), sin(rho1)*cos(theta1)+cos(rho1)*sin(phi1)*sin(theta1),-cos(phi1)*sin(theta1),0.0,
-sin(rho1)*cos(phi1),cos(phi1)*cos(rho1),sin(phi1),0.0,
 cos(rho1)*sin(theta1)+sin(rho1)*cos(theta1)*sin(phi1), sin(rho1)*sin(theta1)-cos(theta1)*cos(rho1)*sin(phi1),cos(phi1)*cos(theta1),0.0,
-sin(rho1)*cos(phi1)*cm+xp+sin(rho1)*sin(phi1)*( d-rm), yp+cos(phi1)*cm*cos(rho1)-cos(rho1)*sin(phi1)*( d-rm), zp+cm*sin(phi1)+cos(phi1)*( d-rm),1.0);
MTrans_Sol_Manillar3D->setMatrix(MSol_Manillar3D);
 
MPnt_Rider3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
 sin(rho1)*( d+zcdg)*sin(phi1)+xp-sin(rho1)*cos(phi1)*ycdg, yp+cos(phi1)*ycdg*cos(rho1)-( d+zcdg)*cos(rho1)*sin(phi1), ycdg*sin(phi1)+zp+cos(phi1)*( d+zcdg),1.0);
MTrans_Pnt_Rider3D->setMatrix(MPnt_Rider3D);
 
MFra_FraABS_draw.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,1.0);
MTrans_Fra_FraABS_draw->setMatrix(MFra_FraABS_draw);
 
MSol_Ground3D.set
(1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,1.0);
MTrans_Sol_Ground3D->setMatrix(MSol_Ground3D);
 
if (pow( (R*R)+(le*le)/4.0,(1.0/2.0))<= 0.001 ){
MVec_VectorP_J1.set
  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
else if (fabs((1.0/2.0)*le)<= 0.001 && 0.0<= 0.001){
MVec_VectorP_J1.set
(0.0,0.0,-R,0.0,
-sin(rho1)*pow( (R*R)+(le*le)/4.0,(1.0/2.0)),cos(rho1)*pow( (R*R)+(le*le)/4.0,(1.0/2.0)),0.0,0.0,
R*cos(rho1),R*sin(rho1),0.0,0.0,
xp,yp,zp,1.0);
}
else {
MVec_VectorP_J1.set
((1.0/2.0)*cos(rho1)*le,(1.0/2.0)*sin(rho1)*le,-R,0.0,
-sin(rho1)*pow((le*le),-(1.0/2.0))*pow( (R*R)+(le*le)/4.0,(1.0/2.0))*le,pow((le*le),-(1.0/2.0))*cos(rho1)*pow( (R*R)+(le*le)/4.0,(1.0/2.0))*le,0.0,0.0,
R*pow((le*le),-(1.0/2.0))*cos(rho1)*le,R*sin(rho1)*pow((le*le),-(1.0/2.0))*le,(1.0/2.0)*pow((le*le),(1.0/2.0)),0.0,
xp,yp,zp,1.0);
}
MTrans_Vec_VectorP_J1->setMatrix(MVec_VectorP_J1);
 
if (pow( (R*R)+(le*le)/4.0,(1.0/2.0))<= 0.001 ){
MVec_VectorP_J2.set
  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
else if (fabs(-(1.0/2.0)*le)<= 0.001 && 0.0<= 0.001){
MVec_VectorP_J2.set
(0.0,0.0,-R,0.0,
-sin(rho1)*pow( (R*R)+(le*le)/4.0,(1.0/2.0)),cos(rho1)*pow( (R*R)+(le*le)/4.0,(1.0/2.0)),0.0,0.0,
R*cos(rho1),R*sin(rho1),0.0,0.0,
xp,yp,zp,1.0);
}
else {
MVec_VectorP_J2.set
(-(1.0/2.0)*cos(rho1)*le,-(1.0/2.0)*sin(rho1)*le,-R,0.0,
sin(rho1)*pow((le*le),-(1.0/2.0))*pow( (R*R)+(le*le)/4.0,(1.0/2.0))*le,-pow((le*le),-(1.0/2.0))*cos(rho1)*pow( (R*R)+(le*le)/4.0,(1.0/2.0))*le,0.0,0.0,
-R*pow((le*le),-(1.0/2.0))*cos(rho1)*le,-R*sin(rho1)*pow((le*le),-(1.0/2.0))*le,(1.0/2.0)*pow((le*le),(1.0/2.0)),0.0,
xp,yp,zp,1.0);
}
MTrans_Vec_VectorP_J2->setMatrix(MVec_VectorP_J2);
 
if (pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0)+pow( cos(theta1)*man+d-rm,2.0),(1.0/2.0))<= 0.001 ){
MVec_VectorP_S0.set
  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
else if (fabs(man*sin(theta1))<= 0.001 && fabs(cm)<= 0.001){
MVec_VectorP_S0.set
(sin(rho1)*( cos(theta1)*man+d-rm)*sin(phi1),-cos(rho1)*( cos(theta1)*man+d-rm)*sin(phi1),cos(phi1)*( cos(theta1)*man+d-rm),0.0,
-sin(rho1)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0)+pow( cos(theta1)*man+d-rm,2.0),(1.0/2.0))*cos(phi1),pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0)+pow( cos(theta1)*man+d-rm,2.0),(1.0/2.0))*cos(phi1)*cos(rho1),pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0)+pow( cos(theta1)*man+d-rm,2.0),(1.0/2.0))*sin(phi1),0.0,
-cos(rho1)*( cos(theta1)*man+d-rm),-sin(rho1)*( cos(theta1)*man+d-rm),0.0,0.0,
xp,yp,zp,1.0);
}
else {
MVec_VectorP_S0.set
( sin(rho1)*( cos(theta1)*man+d-rm)*sin(phi1)-sin(rho1)*cos(phi1)*cm+man*cos(rho1)*sin(theta1),-cos(rho1)*( cos(theta1)*man+d-rm)*sin(phi1)+sin(rho1)*man*sin(theta1)+cos(phi1)*cm*cos(rho1), cos(phi1)*( cos(theta1)*man+d-rm)+cm*sin(phi1),0.0,
-sin(rho1)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0)+pow( cos(theta1)*man+d-rm,2.0),(1.0/2.0))*cos(phi1)*man*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),-(1.0/2.0))*sin(theta1)-pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0)+pow( cos(theta1)*man+d-rm,2.0),(1.0/2.0))*cm*cos(rho1)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),-(1.0/2.0)), pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0)+pow( cos(theta1)*man+d-rm,2.0),(1.0/2.0))*cos(phi1)*man*cos(rho1)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),-(1.0/2.0))*sin(theta1)-sin(rho1)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0)+pow( cos(theta1)*man+d-rm,2.0),(1.0/2.0))*cm*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),-(1.0/2.0)),pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0)+pow( cos(theta1)*man+d-rm,2.0),(1.0/2.0))*man*sin(phi1)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),-(1.0/2.0))*sin(theta1),0.0,
 sin(rho1)*sin(phi1)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),(1.0/2.0))+sin(rho1)*cos(phi1)*cm*( cos(theta1)*man+d-rm)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),-(1.0/2.0))-man*cos(rho1)*( cos(theta1)*man+d-rm)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),-(1.0/2.0))*sin(theta1),-cos(rho1)*sin(phi1)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),(1.0/2.0))-sin(rho1)*man*( cos(theta1)*man+d-rm)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),-(1.0/2.0))*sin(theta1)-cos(phi1)*cm*cos(rho1)*( cos(theta1)*man+d-rm)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),-(1.0/2.0)), cos(phi1)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),(1.0/2.0))-cm*( cos(theta1)*man+d-rm)*sin(phi1)*pow( (cm*cm)+(man*man)*pow(sin(theta1),2.0),-(1.0/2.0)),0.0,
xp,yp,zp,1.0);
}
MTrans_Vec_VectorP_S0->setMatrix(MVec_VectorP_S0);
 
if (pow( (cm*cm)+pow( cos(theta1)*man+d-rm-r*sin(theta1),2.0)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0))<= 0.001 ){
MVec_VectorP_S1.set
  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
else if (fabs( cos(theta1)*r+man*sin(theta1))<= 0.001 && fabs(cm)<= 0.001){
MVec_VectorP_S1.set
(sin(rho1)*( cos(theta1)*man+d-rm-r*sin(theta1))*sin(phi1),-( cos(theta1)*man+d-rm-r*sin(theta1))*cos(rho1)*sin(phi1),cos(phi1)*( cos(theta1)*man+d-rm-r*sin(theta1)),0.0,
-sin(rho1)*cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm-r*sin(theta1),2.0)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0)),cos(phi1)*cos(rho1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm-r*sin(theta1),2.0)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0)),sin(phi1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm-r*sin(theta1),2.0)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0)),0.0,
-( cos(theta1)*man+d-rm-r*sin(theta1))*cos(rho1),-sin(rho1)*( cos(theta1)*man+d-rm-r*sin(theta1)),0.0,0.0,
xp,yp,zp,1.0);
}
else {
MVec_VectorP_S1.set
( sin(rho1)*( cos(theta1)*man+d-rm-r*sin(theta1))*sin(phi1)+cos(rho1)*( cos(theta1)*r+man*sin(theta1))-sin(rho1)*cos(phi1)*cm, sin(rho1)*( cos(theta1)*r+man*sin(theta1))+cos(phi1)*cm*cos(rho1)-( cos(theta1)*man+d-rm-r*sin(theta1))*cos(rho1)*sin(phi1), cos(phi1)*( cos(theta1)*man+d-rm-r*sin(theta1))+cm*sin(phi1),0.0,
-pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),-(1.0/2.0))*cm*cos(rho1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm-r*sin(theta1),2.0)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0))-sin(rho1)*cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),-(1.0/2.0))*pow( (cm*cm)+pow( cos(theta1)*man+d-rm-r*sin(theta1),2.0)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0))*( cos(theta1)*r+man*sin(theta1)), cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),-(1.0/2.0))*cos(rho1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm-r*sin(theta1),2.0)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0))*( cos(theta1)*r+man*sin(theta1))-sin(rho1)*pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),-(1.0/2.0))*cm*pow( (cm*cm)+pow( cos(theta1)*man+d-rm-r*sin(theta1),2.0)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0)),pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),-(1.0/2.0))*sin(phi1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm-r*sin(theta1),2.0)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0))*( cos(theta1)*r+man*sin(theta1)),0.0,
-pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),-(1.0/2.0))*( cos(theta1)*man+d-rm-r*sin(theta1))*cos(rho1)*( cos(theta1)*r+man*sin(theta1))+sin(rho1)*pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0))*sin(phi1)+sin(rho1)*cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),-(1.0/2.0))*( cos(theta1)*man+d-rm-r*sin(theta1))*cm,-pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0))*cos(rho1)*sin(phi1)-cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),-(1.0/2.0))*( cos(theta1)*man+d-rm-r*sin(theta1))*cm*cos(rho1)-sin(rho1)*pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),-(1.0/2.0))*( cos(theta1)*man+d-rm-r*sin(theta1))*( cos(theta1)*r+man*sin(theta1)), cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),(1.0/2.0))-pow( (cm*cm)+pow( cos(theta1)*r+man*sin(theta1),2.0),-(1.0/2.0))*( cos(theta1)*man+d-rm-r*sin(theta1))*cm*sin(phi1),0.0,
xp,yp,zp,1.0);
}
MTrans_Vec_VectorP_S1->setMatrix(MVec_VectorP_S1);
 
if (pow( (cm*cm)+pow( cos(theta1)*man+d-rm+r*sin(theta1),2.0)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0))<= 0.001 ){
MVec_VectorP_S2.set
  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
else if (fabs(-cos(theta1)*r+man*sin(theta1))<= 0.001 && fabs(cm)<= 0.001){
MVec_VectorP_S2.set
(sin(rho1)*( cos(theta1)*man+d-rm+r*sin(theta1))*sin(phi1),-cos(rho1)*( cos(theta1)*man+d-rm+r*sin(theta1))*sin(phi1),cos(phi1)*( cos(theta1)*man+d-rm+r*sin(theta1)),0.0,
-sin(rho1)*cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm+r*sin(theta1),2.0)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0)),cos(phi1)*cos(rho1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm+r*sin(theta1),2.0)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0)),sin(phi1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm+r*sin(theta1),2.0)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0)),0.0,
-cos(rho1)*( cos(theta1)*man+d-rm+r*sin(theta1)),-sin(rho1)*( cos(theta1)*man+d-rm+r*sin(theta1)),0.0,0.0,
xp,yp,zp,1.0);
}
else {
MVec_VectorP_S2.set
( sin(rho1)*( cos(theta1)*man+d-rm+r*sin(theta1))*sin(phi1)-( cos(theta1)*r-man*sin(theta1))*cos(rho1)-sin(rho1)*cos(phi1)*cm,-cos(rho1)*( cos(theta1)*man+d-rm+r*sin(theta1))*sin(phi1)-sin(rho1)*( cos(theta1)*r-man*sin(theta1))+cos(phi1)*cm*cos(rho1), cos(phi1)*( cos(theta1)*man+d-rm+r*sin(theta1))+cm*sin(phi1),0.0,
-pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),-(1.0/2.0))*cm*cos(rho1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm+r*sin(theta1),2.0)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0))+sin(rho1)*( cos(theta1)*r-man*sin(theta1))*cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),-(1.0/2.0))*pow( (cm*cm)+pow( cos(theta1)*man+d-rm+r*sin(theta1),2.0)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0)),-( cos(theta1)*r-man*sin(theta1))*cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),-(1.0/2.0))*cos(rho1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm+r*sin(theta1),2.0)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0))-sin(rho1)*pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),-(1.0/2.0))*cm*pow( (cm*cm)+pow( cos(theta1)*man+d-rm+r*sin(theta1),2.0)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0)),-( cos(theta1)*r-man*sin(theta1))*pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),-(1.0/2.0))*sin(phi1)*pow( (cm*cm)+pow( cos(theta1)*man+d-rm+r*sin(theta1),2.0)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0)),0.0,
 sin(rho1)*pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0))*sin(phi1)+sin(rho1)*cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),-(1.0/2.0))*cm*( cos(theta1)*man+d-rm+r*sin(theta1))+( cos(theta1)*r-man*sin(theta1))*pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),-(1.0/2.0))*cos(rho1)*( cos(theta1)*man+d-rm+r*sin(theta1)),-cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),-(1.0/2.0))*cm*cos(rho1)*( cos(theta1)*man+d-rm+r*sin(theta1))+sin(rho1)*( cos(theta1)*r-man*sin(theta1))*pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),-(1.0/2.0))*( cos(theta1)*man+d-rm+r*sin(theta1))-pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0))*cos(rho1)*sin(phi1), cos(phi1)*pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),(1.0/2.0))-pow( (cm*cm)+pow( cos(theta1)*r-man*sin(theta1),2.0),-(1.0/2.0))*cm*( cos(theta1)*man+d-rm+r*sin(theta1))*sin(phi1),0.0,
xp,yp,zp,1.0);
}
MTrans_Vec_VectorP_S2->setMatrix(MVec_VectorP_S2);
 
if (pow( (yp*yp)+(xp*xp)+(zp*zp),(1.0/2.0))<= 0.001 ){
MVec_VectorO_P.set
  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
}
else if (fabs(xp)<= 0.001 && fabs(yp)<= 0.001){
MVec_VectorO_P.set
(0.0,0.0,zp,0.0,
0.0,pow( (yp*yp)+(xp*xp)+(zp*zp),(1.0/2.0)),0.0,0.0,
-zp,0.0,0.0,0.0,
0.0,0.0,0.0,1.0);
}
else {
MVec_VectorO_P.set
(xp,yp,zp,0.0,
-yp*pow( (yp*yp)+(xp*xp)+(zp*zp),(1.0/2.0))*pow( (yp*yp)+(xp*xp),-(1.0/2.0)),pow( (yp*yp)+(xp*xp)+(zp*zp),(1.0/2.0))*pow( (yp*yp)+(xp*xp),-(1.0/2.0))*xp,0.0,0.0,
-pow( (yp*yp)+(xp*xp),-(1.0/2.0))*zp*xp,-yp*pow( (yp*yp)+(xp*xp),-(1.0/2.0))*zp,pow( (yp*yp)+(xp*xp),(1.0/2.0)),0.0,
0.0,0.0,0.0,1.0);
}
MTrans_Vec_VectorO_P->setMatrix(MVec_VectorO_P);
 
}

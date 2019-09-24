// ----------------------------------------
// 	Geometric and Kinematic Model
// ----------------------------------------

// -----------------
// 	INTPUT
// -----------------
// The inputs of the funtion are:
//	-> (ox,oy,oz)    	= OC = the location of the centre of the wheel
//	-> (eyrx,eyry,eyrz)  = EYR = the direction of a vector orthogonal to the wheel plane
//	-> (vcx,vcy,vcz) 	= VC = the velocity vector of the centre of the wheel
//	-> (omx,omy,omz)		= OW = the angular velocity vector of the wheel
//
// -----------------
// 	OUTPUT
// -----------------
// This function calculates, for a flat ground:
//	-> (opx,opy,opz) = OP = the wheel-ground contact point location
//	-> lambda  = the distance from wheel centre to ground
//	-> gamma   = the camber angle of the wheel
//	-> alpha   = the slip angle
//	-> sx      = the longitudinal slip


#include <stdio.h>
#include <math.h>


// void geom_kin_model(double *pOC,double *pEYR,double *pVC,double *pOW,double *pOP,double Lambda,double Sx, double Alpha, double Gamma)
void geom_kin_model(double * Kinematics_Wheels,int pos_w ,double * Kin_Data)
{

#define vcrit 0.0
  
#define ocx Kinematics_Wheels[0+pos_w]
#define ocy Kinematics_Wheels[1+pos_w]
#define ocz Kinematics_Wheels[2+pos_w]

#define eyrx Kinematics_Wheels[3+pos_w]
#define eyry Kinematics_Wheels[4+pos_w]
#define eyrz Kinematics_Wheels[5+pos_w]

#define vcx Kinematics_Wheels[6+pos_w]
#define vcy Kinematics_Wheels[7+pos_w]
#define vcz Kinematics_Wheels[8+pos_w]

#define omx Kinematics_Wheels[9+pos_w]
#define omy Kinematics_Wheels[10+pos_w]
#define omz Kinematics_Wheels[11+pos_w]

#define r   Kinematics_Wheels[12+pos_w]


#define opx 		Kin_Data[0]
#define opy 		Kin_Data[1]
#define opz 		Kin_Data[2]

#define exGx 	Kin_Data[3]
#define exGy 	Kin_Data[4]
#define exGz 	Kin_Data[5]

#define eyGx 	Kin_Data[6]
#define eyGy 	Kin_Data[7]
#define eyGz 	Kin_Data[8]

#define ezGx 	Kin_Data[9]
#define ezGy 	Kin_Data[10]
#define ezGz 	Kin_Data[11]

#define Lambda  	Kin_Data[12]
#define Gamma 	Kin_Data[13]
#define Alpha 	Kin_Data[14]
#define Sx 		Kin_Data[15]
#define R		Kin_Data[16]

double u2v2 = pow(eyrx,2.0)+pow(eyry,2.0);
opx=ocx+(ocz*eyrx*eyrz)/u2v2;
opy=ocy+(ocz*eyry*eyrz)/u2v2;
opz=0.0;

Lambda=-ocz/pow(u2v2,0.5);

Gamma=asin(eyrz);

double projx = (vcx*eyry-vcy*eyrx)/pow(u2v2,0.5);
double projy = vcx*eyrx + vcy*eyry + vcz*eyrz;

Alpha = -atan2(projy,projx);

double vx=(vcx*eyry-vcy*eyrx)/pow(u2v2,0.5);
double omr=Lambda*(omx*eyrx+omy*eyry+omz*eyrz);

// Slip angle in percentage
Sx=-((vx+omr)/(fabs(omr)+vcrit))*100.0;

printf("omr: %2.5f\n",omr);
printf("vx: %2.5f\n",vx);
printf("Sx: %2.5f\n",Sx);


printf("eyGx is: %3.10f\n",eyGx);
printf("eyGy is: %3.10f\n",eyGy);
printf("eyGz is: %3.10f\n",eyGz);


eyGx=eyrx/pow(u2v2,0.5);
eyGy=eyry/pow(u2v2,0.5);
eyGz=0;

exGx= eyry/pow(u2v2,0.5);
exGy=-eyrx/pow(u2v2,0.5);
exGz=0.0;

ezGx=0;
ezGy=0;
ezGz=1;

R=r;

}

// ----------------------------------------
// 	Geometric and Kinematic Model
// ----------------------------------------

// -----------------
// 	INTPUT
// -----------------
// The inputs of the funtion are:
//	-> (x,y,z)    = OC = the location of the centre of the wheel
//	-> (u,v,w)    =	EYR = the direction of a vector orthogonal to the wheel plane
//	-> (vx,vy,vz) = VC = the velocity vector of the centre of the wheel
//	-> (ox,oy,oz) = OW = the angular velocity vector of the wheel
//
// -----------------
// 	OUTPUT
// -----------------
// This function calculates, for a flat ground:
//	-> (a,b,0) = OP = the wheel-ground contact point location
//	-> lambda  = the distance from wheel centre to ground
//	-> gamma   = the camber angle of the wheel
//	-> alpha   = the slip angle
//	-> sx      = the longitudinal slip


#include <stdio.h>
#include <math.h>


// The fictitious velocity to avoid singularity when Omega(wheel) is zero.
static double vc=0.1;


void geom_kin_model(double *pOC,double *pEYR,double *pVC,double *pOW,double *pOP,double Lambda,double Sx, double Alpha, double Gamma)
{

double u2v2 = pow(pEYR[0],2.0)+pow(pEYR[1],2.0);
pOP[0]=pOC[0]+(pOC[2]*pEYR[0]*pEYR[2])/u2v2;
pOP[1]=pOC[1]+(pOC[2]*pEYR[1]*pEYR[2])/u2v2;

Lambda=-pOC[2]/pow(u2v2,0.5);

Gamma=asin(pEYR[2]);

//double sinAlpha = pow(vz*vz*u2v2+u*u*vy*vy+v*v*vx*vx-2*u*v*vx*vy,0.5)/pow(u2v2,0.5)/pow(vx*vx+vy*vy+vz*vz,0.5);
double sinAlpha = pow(pVC[2]*pVC[2]*u2v2+pEYR[0]*pEYR[0]*pVC[1]*pVC[1]+pEYR[1]*pEYR[1]*pVC[0]*pVC[0]-2*pEYR[0]*pEYR[1]*pVC[0]*pVC[1],0.5)/pow(u2v2,0.5)/pow(pVC[0]*pVC[0]+pVC[1]*pVC[1]+pVC[2]*pVC[2],0.5);
Alpha=asin(sinAlpha);


double vx=(pVC[0]*pEYR[1]-pVC[1]*pEYR[0])/pow(u2v2,0.5);
double omr=Lambda*(pOW[0]*pEYR[0]+pOW[1]*pEYR[1]+pOW[2]*pEYR[2]);

Sx=(vx-omr)/(omr+vc);

}

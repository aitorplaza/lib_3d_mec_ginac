#include <stdio.h>
#include <math.h>

//COEFFICIENT MATRIXES

static double A1[3][8]=
{         //1       2       3      4       5        6        7        8
	{-22.1,   1011,   1078,   1.82,  0.208,   0.000,  -0.354,   0.707}, //Fy
	{-2.72,  -2.28,  -1.86,  -2.73,  0.110,  -0.070,   0.643,  -4.04}, //Mz
	{-21.3,   1144,   49.6,   226,   0.069,  -0.006,   0.056,   0.486} //Fx
}; 

static double A2[2][5]=
{        //1        2       3       4       5
	{0.028,   0.000,  14.8,   0.022,  0.000}, //Fy
	{0.015,  -0.066,  0.945,  0.030,  0.070} //Mz
};

//FY, MZ AND FX FUNCTIONS

void tyre_model(double Fz,double Gamma,double Alpha,double Sigma,double *pFx,double *pFy,double *pMz)
{
	//LATERAL FORCE FY

	//Stiffness, shape, peak and curvature factors

	double C=1.30;
	double D=A1[0][0]*(Fz*Fz)+A1[0][1]*Fz;
	double BCD=A1[0][2]*sin(A1[0][3]*atan(A1[0][4]*Fz));
	double B=BCD/(C*D);
	double E=A1[0][5]*(Fz*Fz)+A1[0][6]*Fz+A1[0][7];

	//Factors are affected by camber angle (Gamma) given in degrees
	
	double Sh=A2[0][0]*Gamma;
	double Sv=(A2[0][1]*(Fz*Fz)+A2[0][2]*Fz)*Gamma;
	double BB=A2[0][3]*fabs(Gamma)*B*(-1);

	//Lateral force is a function of the shape factors and slip angle (Alpha)

	double fi=(1-E)*(Alpha+Sh)+(E/B)*atan(B*(Alpha+Sh));
	*pFy=D*sin(C*atan(B*fi))+Sv;

	//ALIGNING MOMENT MZ

	//Stiffness, shape, peak and curvature factors

	C=2.40;
	D=A1[1][0]*(Fz*Fz)+A1[1][1]*Fz;
	BCD=(A1[1][2]*(Fz*Fz)+A1[1][3]*Fz)/exp(A1[1][4]*Fz);
	B=BCD/(C*D);
	E=A1[1][5]*(Fz*Fz)+A1[1][6]*Fz+A1[1][7];

	//Factors are affected by camber angle (Gamma) given in degrees

	Sh=A2[1][0]*Gamma;
	Sv=(A2[1][1]*(Fz*Fz)+A2[1][2]*Fz)*Gamma;
	BB=A2[1][3]*fabs(Gamma)*B*(-1);
	double EE=(E/(1-A2[1][4]*fabs(Gamma)))-E;

	//Aligning moment is a function of the shape factors and slip angle (Alpha)

	fi=(1-E)*(Alpha+Sh)+(E/B)*atan(B*(Alpha+Sh));
	*pMz=D*sin(C*atan(B*fi))+Sv;
	
	//LONGITUDINAL FORCE FX
	
	//Stiffness, shape, peak and curvature factors
	C=1.65;
	D=A1[2][0]*(Fz*Fz)+A1[2][1]*Fz;
	BCD=(A1[2][2]*Fz*Fz+A1[2][3]*Fz)/exp(A1[2][4]*Fz);
	B=BCD/(C*D);
	E=A1[2][5]*(Fz*Fz)+A1[2][6]*Fz+A1[2][7];

	//Longitudinal force is a function of the shape factors and the percent longitudinal slip (Sigma)

	fi=(1-E)*(Sigma)+(E/B)*atan(B*Sigma);
	*pFx=D*sin(C*atan(B*fi));

}

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

static double kz=1900;// N/m
static double cz=500.0;// N/m


//FY, MZ AND FX FUNCTIONS

void tyre_model(double * Kin_Data, double * inputs, int fxpos, double * contact_vel, int wpos) 
{

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
	
	double Fx;
	double Fy;
	double Fz;	// Fz  Fz in kN
	double FzN;	// FzN Fz in N
	double Mz;
	
	//VERTICAL FORCE FZ
	if (R>-Lambda)
	{
		FzN=kz*(R+Lambda)-cz*contact_vel[wpos+2];
		Fz=FzN*0.001;
		printf("Fz rueda[%1.1f]=%1.5f\n",wpos/3.0+1,FzN);

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
		Fy=D*sin(C*atan(B*fi))+Sv;


		
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
		
		Mz=D*sin(C*atan(B*fi))+Sv;
		
		//LONGITUDINAL FORCE FX
		//Stiffness, shape, peak and curvature factors
		C=1.65;
		D=A1[2][0]*(Fz*Fz)+A1[2][1]*Fz;
		BCD=(A1[2][2]*Fz*Fz+A1[2][3]*Fz)/exp(A1[2][4]*Fz);
		B=BCD/(C*D);
		E=A1[2][5]*(Fz*Fz)+A1[2][6]*Fz+A1[2][7];

		//Longitudinal force is a function of the shape factors and the percent longitudinal slip (Sx)

		fi=(1-E)*(Sx)+(E/B)*atan(B*Sx);
		Fx=D*sin(C*atan(B*fi));
		printf("Fx rueda[%1.1f]=%1.5f\n",wpos/3.0+1,Fx);

	}
	else
	{
		FzN=0.0;
		Fz=0.0;
		Fx=0.0;
		Fy=0.0;
		Mz=0.0;
	}


// 	inputs[fxpos+3]=Fx*exGx+Fy*eyGx+Fz*ezGx;
// 	inputs[fxpos+4]=Fx*exGy+Fy*eyGy+Fz*ezGºy;
// 	inputs[fxpos+5]=Fx*exGz+Fy*eyGz+Fz*ezGz;
// 
// 	inputs[fxpos+6]=Mz*ezGx;
// 	inputs[fxpos+7]=Mz*ezGy;
// 	inputs[fxpos+8]=Mz*ezGz;

// 	printf("Fx is: %3.10f\n",Fx);

// 	printf("The vertical force inside tyremodel is: %3.10f\n",inputs[fxpos+2]);

	inputs[fxpos+0]=opx;
	inputs[fxpos+1]=opy;
	inputs[fxpos+2]=opz;

	inputs[fxpos+3]=Fx*exGx+FzN*ezGx;
	inputs[fxpos+4]=Fx*exGy+FzN*ezGy;
	inputs[fxpos+5]=Fx*exGz+FzN*ezGz;

	inputs[fxpos+6]=0.0;
	inputs[fxpos+7]=0.0;
	inputs[fxpos+8]=0.0;
	
// 	inputs[fxpos+6]=Mz*ezGx;
// 	inputs[fxpos+7]=Mz*ezGy;
// 	inputs[fxpos+8]=Mz*ezGz;
	
	
// 	inputs[fxpos+3]=Fx*exGx+Fy*eyGx+FzN*ezGx;
// 	inputs[fxpos+4]=Fx*exGy+Fy*eyGy+FzN*ezGy;
// 	inputs[fxpos+5]=Fx*exGz+Fy*eyGz+FzN*ezGz;

// 	inputs[fxpos+6]=Mz*ezGx;
// 	inputs[fxpos+7]=Mz*ezGy;
// 	inputs[fxpos+8]=Mz*ezGz;

}

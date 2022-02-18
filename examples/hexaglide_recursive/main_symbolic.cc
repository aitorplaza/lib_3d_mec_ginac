#include <fstream>
#include "lib_3d_mec_ginac/lib_3d_mec_ginac.h"
#include <ginac/ginac.h>
#include <sstream>

//*****************************************************************************************************************
// 	PLEASE AlWAYS DEFINE ORDER & MAPLE & METHOD
// 	DEFINED IN "globals.h" + "compilation line or with #define"

// 	#define METHOD VIRTUAL_POWER or #define METHOD LAGRANGE  // or complilation line -DORDER=CMO or -DORDER=RMO
// 	#define ORDER CMO or #define ORDER RMO  // or complilation line -DORDER=CMO or -DORDER=RMO
// 	#define MAPLE MAPLE_ON or #define MAPLE MAPLE_OFF  // or complilation line -DMAPLE=MAPLE_ON -DMAPLE=MAPLE_OFF

// 	IF METHOD = 1 ==> VIRTUAL_POWER & IF METHOD = 0 ==> LAGRANGE
// 	IF ORDER  = 1 ==> CMO           & IF ORDER  = 0 ==> RMO
// 	IF MAPLE  = 1 ==> MAPLE_ON      & IF MAPLE  = 0 ==> MAPLE_OFF
//*****************************************************************************************************************
#ifdef LAG	
	# define METHOD LAGRANGE
#endif

#ifdef V_P
	# define METHOD VIRTUAL_POWER
#endif
//*****************************************************************************************************************
#ifdef Q
	#define PROBLEM_TYPE "Q"
#endif
#ifdef Z
	#define PROBLEM_TYPE "Z"
#endif
#ifdef I3AL_Q
	#define PROBLEM_TYPE "I3AL_Q"
#endif
#ifdef I3AL_Z
	#define PROBLEM_TYPE "I3AL_Z"
#endif
#ifdef ALL
	#define PROBLEM_TYPE "ALL"
#endif
//*****************************************************************************************************************


using namespace GiNaC;
using namespace std;
	
// SYSTEM DEFINITION
// *****************************************************************************************************************	

void printError2(const char* arg){
	printf("%s\n", arg);
}	
	
#ifdef PROCEDURE
int C_EXPORT_AS_PROCEDURE=1;
#else
int C_EXPORT_AS_PROCEDURE=0;
#endif


int main(int argc, char *argv[]) {

// *****************************************************************************************************************	
cout << " " << endl;
cout << "************************************************" << endl;
cout << "*             Hexaglide Platform               *" << endl;
cout << "************************************************" << endl;
cout << " " << endl;
system("date");
cout << " " << endl;
// *****************************************************************************************************************	

if (argc!=3){
        printf("Error: The program %s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\n",argv[0]);
        exit(1);
    }

if (0==strcmp(argv[1],"DOWN")){
    gravity=DOWN;
    cout << "Gravity DOWN" << endl;
}
else{
    if (0==strcmp(argv[1],"UP")){
        gravity=UP;
        cout << "Gravity UP" << endl;
    }
    else
    {
        printf("Error: The program %s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\n",argv[0]);
        exit(1);
    }
}

if (0==strcmp(argv[2],"YES")){
        atomization=YES;
        cout << "Atomize YES" << endl;
}
else{

    if (0==strcmp(argv[2],"NO")){
        atomization=NO;
        cout << "Atomize NO" << endl;
    }
    else
    {
        printf("Error: The program %s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\n",argv[0]);
        exit(1);
    }
}

// ************************************************************************************************

	double integration_time=strtod(argv[1], NULL);
	double delta_t= strtod(argv[2], NULL);
	long int k,steps;
	
	printf("integration_time %g delta_t %g\n", integration_time, delta_t);

// ************************************************************************************************
//	System definition
// ************************************************************************************************

	System sys(&printError2);

// ************************************************************************************************
//	TIME DEFINITION
// ************************************************************************************************
        symbol_numeric t=sys.get_Time_Symbol ( );

// ************************************************************************************************
//	Coordinate definition
// ************************************************************************************************

	// Coordinates of the centre of the platform
	symbol_numeric x = *sys.new_Coordinate("x","dx","ddx", 0.0 , 0.0 , 0.0);
	symbol_numeric y = *sys.new_Coordinate("y","dy","ddy", 0.0 , 0.0 , 0.0);
	symbol_numeric z = *sys.new_Coordinate("z","dz","ddz", 5.0 , 0.0 , 0.0);

	// Rotation of the platform
	symbol_numeric a = *sys.new_Coordinate("a","da","dda", 0.0 , 0.0 , 0.0);
	symbol_numeric b = *sys.new_Coordinate("b","dB","ddB", 0.0 , 0.0 , 0.0);
	symbol_numeric c = *sys.new_Coordinate("c","dc","ddc", 0.0 , 0.0 , 0.0);

	// First Rotation of the down bars w.r.t. axis X
	symbol_numeric a1 = *sys.new_Coordinate("a1","da1","dda1",  0.0 , 0.0 , 0.0);
	symbol_numeric a2 = *sys.new_Coordinate("a2","da2","dda2",  0.0 , 0.0 , 0.0);
	symbol_numeric a3 = *sys.new_Coordinate("a3","da3","dda3",  0.0 , 0.0 , 0.0);
	symbol_numeric a4 = *sys.new_Coordinate("a4","da4","dda4",  0.0 , 0.0 , 0.0);
	symbol_numeric a5 = *sys.new_Coordinate("a5","da5","dda5",  0.0 , 0.0 , 0.0);
	symbol_numeric a6 = *sys.new_Coordinate("a6","da6","dda6",  0.0 , 0.0 , 0.0);

	// First Rotation of the down bars w.r.t. axis Z
// 	symbol_numeric a1 = *sys.new_Coordinate("a1","da1","dda1", -0.3335 , 0.0 , 0.0);
// 	symbol_numeric a2 = *sys.new_Coordinate("a2","da2","dda2",  0.3335 , 0.0 , 0.0);
// 	symbol_numeric a3 = *sys.new_Coordinate("a3","da3","dda3", -0.3335 , 0.0 , 0.0);
// 	symbol_numeric a4 = *sys.new_Coordinate("a4","da4","dda4",  0.3335 , 0.0 , 0.0);
// 	symbol_numeric a5 = *sys.new_Coordinate("a5","da5","dda5", -0.3335 , 0.0 , 0.0);
// 	symbol_numeric a6 = *sys.new_Coordinate("a6","da6","dda6",  0.3335 , 0.0 , 0.0);

	// Second Rotation of the down bars
	symbol_numeric b1 = *sys.new_Coordinate("b1","dB1","ddB1", 0.481 , 0.0 , 0.0);
	symbol_numeric b2 = *sys.new_Coordinate("b2","dB2","ddB2", 0.481 , 0.0 , 0.0);
	symbol_numeric b3 = *sys.new_Coordinate("b3","dB3","ddB3", 0.481 , 0.0 , 0.0);
	symbol_numeric b4 = *sys.new_Coordinate("b4","dB4","ddB4", 0.481 , 0.0 , 0.0);
	symbol_numeric b5 = *sys.new_Coordinate("b5","dB5","ddB5", 0.481 , 0.0 , 0.0);
	symbol_numeric b6 = *sys.new_Coordinate("b6","dB6","ddB6", 0.481 , 0.0 , 0.0);
   
	// Translation of the up bars w.r.t. the down bars
	symbol_numeric s1 = *sys.new_Coordinate("s1","ds1","dds1", 1.0 , 0.0 , 0.0);
	symbol_numeric s2 = *sys.new_Coordinate("s2","ds2","dds2", 1.0 , 0.0 , 0.0);
	symbol_numeric s3 = *sys.new_Coordinate("s3","ds3","dds3", 1.0 , 0.0 , 0.0);
	symbol_numeric s4 = *sys.new_Coordinate("s4","ds4","dds4", 1.0 , 0.0 , 0.0);
	symbol_numeric s5 = *sys.new_Coordinate("s5","ds5","dds5", 1.0 , 0.0 , 0.0);
	symbol_numeric s6 = *sys.new_Coordinate("s6","ds6","dds6", 1.0 , 0.0 , 0.0);

	// Velocities
	symbol_numeric *dx=sys.get_Velocity("dx");
	symbol_numeric *dy=sys.get_Velocity("dy");
	symbol_numeric *dz=sys.get_Velocity("dz");

	symbol_numeric *da=sys.get_Velocity("da");
	symbol_numeric *dB=sys.get_Velocity("dB");
	symbol_numeric *dc=sys.get_Velocity("dc");

	symbol_numeric *da1=sys.get_Velocity("da1");
	symbol_numeric *da2=sys.get_Velocity("da2");
	symbol_numeric *da3=sys.get_Velocity("da3");
	symbol_numeric *da4=sys.get_Velocity("da4");
	symbol_numeric *da5=sys.get_Velocity("da5");
	symbol_numeric *da6=sys.get_Velocity("da6");

	symbol_numeric *dB1=sys.get_Velocity("dB1");
	symbol_numeric *dB2=sys.get_Velocity("dB2");
	symbol_numeric *dB3=sys.get_Velocity("dB3");
	symbol_numeric *dB4=sys.get_Velocity("dB4");
	symbol_numeric *dB5=sys.get_Velocity("dB5");
	symbol_numeric *dB6=sys.get_Velocity("dB6");

	symbol_numeric *ds1=sys.get_Velocity("ds1");
	symbol_numeric *ds2=sys.get_Velocity("ds2");
	symbol_numeric *ds3=sys.get_Velocity("ds3");
	symbol_numeric *ds4=sys.get_Velocity("ds4");
	symbol_numeric *ds5=sys.get_Velocity("ds5");
	symbol_numeric *ds6=sys.get_Velocity("ds6");

	// Accelerations
	symbol_numeric *ddx=sys.get_Acceleration("ddx");
	symbol_numeric *ddy=sys.get_Acceleration("ddy");
	symbol_numeric *ddz=sys.get_Acceleration("ddz");

	symbol_numeric *dda=sys.get_Acceleration("dda");
	symbol_numeric *ddB=sys.get_Acceleration("ddB");
	symbol_numeric *ddc=sys.get_Acceleration("ddc");

	symbol_numeric *dda1=sys.get_Acceleration("dda1");
	symbol_numeric *dda2=sys.get_Acceleration("dda2");
	symbol_numeric *dda3=sys.get_Acceleration("dda3");
	symbol_numeric *dda4=sys.get_Acceleration("dda4");
	symbol_numeric *dda5=sys.get_Acceleration("dda5");
	symbol_numeric *dda6=sys.get_Acceleration("dda6");

	symbol_numeric *ddB1=sys.get_Acceleration("ddB1");
	symbol_numeric *ddB2=sys.get_Acceleration("ddB2");
	symbol_numeric *ddB3=sys.get_Acceleration("ddB3");
	symbol_numeric *ddB4=sys.get_Acceleration("ddB4");
	symbol_numeric *ddB5=sys.get_Acceleration("ddB5");
	symbol_numeric *ddB6=sys.get_Acceleration("ddB6");

	symbol_numeric *dds1=sys.get_Acceleration("dds1");
	symbol_numeric *dds2=sys.get_Acceleration("dds2");
	symbol_numeric *dds3=sys.get_Acceleration("dds3");
	symbol_numeric *dds4=sys.get_Acceleration("dds4");
	symbol_numeric *dds5=sys.get_Acceleration("dds5");
	symbol_numeric *dds6=sys.get_Acceleration("dds6");


// ************************************************************************************************
//	Initial Position Additional Constraint Equations
// ************************************************************************************************

	lst coord_indep_init;
	lst vel_indep_init;

//	coord_indep_init = (x-0.0),(y-0.0),(z-5.0),(a-0.0),(b-0.0),(c-0.0);


// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	// Fixed Platform Radius
	symbol_numeric R = *sys.new_Parameter("R",0.484);

	// Moving Platform Radius
	symbol_numeric r = *sys.new_Parameter("r",0.073085);

	// Length of the bars
	symbol_numeric L = *sys.new_Parameter("L",1.0);

	// Excentricity of the columns
	symbol_numeric e = *sys.new_Parameter("e",0.136508/2.0);

	// 60 degrees angle
	//symbol_numeric alfa = *sys.new_Parameter("alfa",3.14159/3.0);
	ex alfa1 =unatomize_ex(numeric(1,3)*Pi);
    ex alfa2 =unatomize_ex(numeric(2,3)*Pi);
    ex alfa4 =unatomize_ex(numeric(4,3)*Pi);
// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

	sys.new_Base("B0P","xyz",1,0,0,a);
	sys.new_Base("BAP","B0P",0,1,0,b);
	sys.new_Base("BP","BAP", 0,0,1,c);

	sys.new_Base("B01","xyz",0,0,1,0.0);
	sys.new_Base("B02","xyz",0,0,1,alfa2);
	sys.new_Base("B03","xyz",0,0,1,alfa4);
    


// 	First rotation w.r.t. axis X
	sys.new_Base("BA1","B01",1,0,0,a1);
	sys.new_Base("BA2","B01",1,0,0,a2);
	sys.new_Base("BA3","B02",1,0,0,a3);
	sys.new_Base("BA4","B02",1,0,0,a4);
	sys.new_Base("BA5","B03",1,0,0,a5);
	sys.new_Base("BA6","B03",1,0,0,a6);

// 	First rotation w.r.t. axis Z
// 	sys.new_Base("BA1","B01",0,0,1,a1);
// 	sys.new_Base("BA2","B01",0,0,1,a2);
// 	sys.new_Base("BA3","B02",0,0,1,a3);
// 	sys.new_Base("BA4","B02",0,0,1,a4);
// 	sys.new_Base("BA5","B03",0,0,1,a5);
// 	sys.new_Base("BA6","B03",0,0,1,a6);

	sys.new_Base("B1","BA1",0,1,0,b1);
	sys.new_Base("B2","BA2",0,1,0,b2);
	sys.new_Base("B3","BA3",0,1,0,b3);
	sys.new_Base("B4","BA4",0,1,0,b4);
	sys.new_Base("B5","BA5",0,1,0,b5);
	sys.new_Base("B6","BA6",0,1,0,b6);


// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	Vector3D OP = *sys.new_Vector3D("OP",x,y,z,"xyz");
	
	Vector3D OA1 = *sys.new_Vector3D("OA1",R, e,s1,"B01");
	Vector3D OA2 = *sys.new_Vector3D("OA2",R,-e,s2,"B01");
	Vector3D OA3 = *sys.new_Vector3D("OA3",R, e,s3,"B02");
	Vector3D OA4 = *sys.new_Vector3D("OA4",R,-e,s4,"B02");
	Vector3D OA5 = *sys.new_Vector3D("OA5",R, e,s5,"B03");
	Vector3D OA6 = *sys.new_Vector3D("OA6",R,-e,s6,"B03");

// 	Vector3D OA1 = *sys.new_Vector3D("OA1",R, e,s1,"B01");
// 	Vector3D OA2 = *sys.new_Vector3D("OA2",R,-e,s2,"B02");
// 	Vector3D OA3 = *sys.new_Vector3D("OA3",R, e,s3,"B03");
// 	Vector3D OA4 = *sys.new_Vector3D("OA4",R,-e,s4,"B04");
// 	Vector3D OA5 = *sys.new_Vector3D("OA5",R, e,s5,"B05");
// 	Vector3D OA6 = *sys.new_Vector3D("OA6",R,-e,s6,"B06");

	Vector3D A1C1 = *sys.new_Vector3D("A1C1",0,0,-L,"B1");
	Vector3D A2C2 = *sys.new_Vector3D("A2C2",0,0,-L,"B2");
	Vector3D A3C3 = *sys.new_Vector3D("A3C3",0,0,-L,"B3");
	Vector3D A4C4 = *sys.new_Vector3D("A4C4",0,0,-L,"B4");
	Vector3D A5C5 = *sys.new_Vector3D("A5C5",0,0,-L,"B5");
	Vector3D A6C6 = *sys.new_Vector3D("A6C6",0,0,-L,"B6");
	
	Vector3D PD1 = *sys.new_Vector3D("PD1",r*1,+e,0	,"BP");
	Vector3D PD2 = *sys.new_Vector3D("PD2",r*1,-e,0	,"BP");
    ex c2alpha = unatomize_ex(cos(alfa2));
    ex s2alpha = unatomize_ex(sin(alfa4));
	//~ Vector3D PD3 = *sys.new_Vector3D("PD3",r*cos(2*alfa)-e*sin(2*alfa),r*sin(2*alfa)+e*cos(2*alfa),0,"BP");
	//~ Vector3D PD4 = *sys.new_Vector3D("PD4",r*cos(2*alfa)+e*sin(2*alfa),r*sin(2*alfa)-e*cos(2*alfa),0,"BP");
	//~ Vector3D PD5 = *sys.new_Vector3D("PD5",r*cos(2*alfa)+e*sin(2*alfa),-r*sin(2*alfa)+e*cos(2*alfa),0,"BP");
	//~ Vector3D PD6 = *sys.new_Vector3D("PD6",r*cos(2*alfa)-e*sin(2*alfa),-r*sin(2*alfa)-e*cos(2*alfa),0,"BP");
    Vector3D PD3 = *sys.new_Vector3D("PD3",r*c2alpha-e*s2alpha, r*s2alpha+e*c2alpha,0,"BP");
	Vector3D PD4 = *sys.new_Vector3D("PD4",r*c2alpha+e*s2alpha, r*s2alpha-e*c2alpha,0,"BP");
	Vector3D PD5 = *sys.new_Vector3D("PD5",r*c2alpha+e*s2alpha,-r*s2alpha+e*c2alpha,0,"BP");
	Vector3D PD6 = *sys.new_Vector3D("PD6",r*c2alpha-e*s2alpha,-r*s2alpha-e*c2alpha,0,"BP");    
    

// 	Vector3D PD1 = *sys.new_Vector3D("PD1",r,0,0,"BP1");
// 	Vector3D PD2 = *sys.new_Vector3D("PD2",r,0,0,"BP2");
// 	Vector3D PD3 = *sys.new_Vector3D("PD3",r,0,0,"BP3");
// 	Vector3D PD4 = *sys.new_Vector3D("PD4",r,0,0,"BP4");
// 	Vector3D PD5 = *sys.new_Vector3D("PD5",r,0,0,"BP5");
// 	Vector3D PD6 = *sys.new_Vector3D("PD6",r,0,0,"BP6");

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * P = sys.new_Point("P","O",&OP);

	Point * A1 = sys.new_Point("A1","O",&OA1);
	Point * A2 = sys.new_Point("A2","O",&OA2);
	Point * A3 = sys.new_Point("A3","O",&OA3);
	Point * A4 = sys.new_Point("A4","O",&OA4);
	Point * A5 = sys.new_Point("A5","O",&OA5);
	Point * A6 = sys.new_Point("A6","O",&OA6);

	Point * C1 = sys.new_Point("C1","A1",&A1C1);
	Point * C2 = sys.new_Point("C2","A2",&A2C2);
	Point * C3 = sys.new_Point("C3","A3",&A3C3);
	Point * C4 = sys.new_Point("C4","A4",&A4C4);
	Point * C5 = sys.new_Point("C5","A5",&A5C5);
	Point * C6 = sys.new_Point("C6","A6",&A6C6);

	Point * D1 = sys.new_Point("D1","P",&PD1);
	Point * D2 = sys.new_Point("D2","P",&PD2);
	Point * D3 = sys.new_Point("D3","P",&PD3);
	Point * D4 = sys.new_Point("D4","P",&PD4);
	Point * D5 = sys.new_Point("D5","P",&PD5);
	Point * D6 = sys.new_Point("D6","P",&PD6);






// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Inertial parameters of the PLATFORM
    	symbol_numeric  mP = *sys.new_Parameter("mP",6.6970);
	symbol_numeric  mxP = *sys.new_Parameter("mxP",0.07);		//aproximado 
    	symbol_numeric  myP = *sys.new_Parameter("myP",0.07);		//aproximado 
	symbol_numeric  mzP = *sys.new_Parameter("mzP",-0.035572*6.6970);
	
    	symbol_numeric  IxxP = *sys.new_Parameter("IxxP",0.028319);
	symbol_numeric  IxyP = *sys.new_Parameter("IxyP",0.0007);	//aproximado 
    	symbol_numeric  IyyP = *sys.new_Parameter("IyyP",0.028319);
	symbol_numeric  IxzP = *sys.new_Parameter("IxzP",0.0003);	//aproximado 
    	symbol_numeric  IzzP = *sys.new_Parameter("IzzP",0.038045);
	symbol_numeric  IyzP = *sys.new_Parameter("IyzP",0.0003);	//aproximado 

// suma de la masa de la barra y de la del carro
#define MB 2.9369+2.867

// masa por vector posicion del CdG
#define MXB 0.03	//aproximado 
#define MYB 0.03	//aproximado 
#define MZB -1.4685
// #define MZB -0.5*2.9369

#define IXXB 1.0435
#define IXYB 0.0003		// valor calculado simplificando a un cilindro con R=0.01metros
#define IYYB 1.0435
#define IXZB 0.014		// valor calculado simplificando a un cilindro con R=0.01metros
#define IZZB 0.0022722		// valor del modelo de Roberto
#define IYZB 0.014		// valor calculado simplificando a un cilindro con R=0.01metros

	// Inertial parameters of the BAR1
    	symbol_numeric  m1 = *sys.new_Parameter("m1",MB);
	symbol_numeric  mx1 = *sys.new_Parameter("mx1",MXB);
    	symbol_numeric  my1 = *sys.new_Parameter("my1",MYB);
	symbol_numeric  mz1 = *sys.new_Parameter("mz1",MZB);
    	symbol_numeric  Ixx1 = *sys.new_Parameter("Ixx1",IXXB);
	symbol_numeric  Ixy1 = *sys.new_Parameter("Ixy1",IXYB);
    	symbol_numeric  Iyy1 = *sys.new_Parameter("Iyy1",IYYB);
	symbol_numeric  Ixz1 = *sys.new_Parameter("Ixz1",IXZB);
    	symbol_numeric  Izz1 = *sys.new_Parameter("Izz1",IZZB);
	symbol_numeric  Iyz1 = *sys.new_Parameter("Iyz1",IYZB);
	
	// Inertial parameters of the BAR2
    	symbol_numeric  m2 = *sys.new_Parameter("m2",MB);
	symbol_numeric  mx2 = *sys.new_Parameter("mx2",MXB);
    	symbol_numeric  my2 = *sys.new_Parameter("my2",MYB);
	symbol_numeric  mz2 = *sys.new_Parameter("mz2",MZB);
    	symbol_numeric  Ixx2 = *sys.new_Parameter("Ixx2",IXXB);
	symbol_numeric  Ixy2 = *sys.new_Parameter("Ixy2",IXYB);
    	symbol_numeric  Iyy2 = *sys.new_Parameter("Iyy2",IYYB);
	symbol_numeric  Ixz2 = *sys.new_Parameter("Ixz2",IXZB);
    	symbol_numeric  Izz2 = *sys.new_Parameter("Izz2",IZZB);
	symbol_numeric  Iyz2 = *sys.new_Parameter("Iyz2",IYZB);

	// Inertial parameters of the BAR3
    	symbol_numeric  m3 = *sys.new_Parameter("m3",MB);
	symbol_numeric  mx3 = *sys.new_Parameter("mx3",MXB);
    	symbol_numeric  my3 = *sys.new_Parameter("my3",MYB);
	symbol_numeric  mz3 = *sys.new_Parameter("mz3",MZB);
    	symbol_numeric  Ixx3 = *sys.new_Parameter("Ixx3",IXXB);
	symbol_numeric  Ixy3 = *sys.new_Parameter("Ixy3",IXYB);
    	symbol_numeric  Iyy3 = *sys.new_Parameter("Iyy3",IYYB);
	symbol_numeric  Ixz3 = *sys.new_Parameter("Ixz3",IXZB);
    	symbol_numeric  Izz3 = *sys.new_Parameter("Izz3",IZZB);
	symbol_numeric  Iyz3 = *sys.new_Parameter("Iyz3",IYZB);

	// Inertial parameters of the BAR4
    	symbol_numeric  m4 = *sys.new_Parameter("m4",MB);
	symbol_numeric  mx4 = *sys.new_Parameter("mx4",MXB);
    	symbol_numeric  my4 = *sys.new_Parameter("my4",MYB);
	symbol_numeric  mz4 = *sys.new_Parameter("mz4",MZB);
    	symbol_numeric  Ixx4 = *sys.new_Parameter("Ixx4",IXXB);
	symbol_numeric  Ixy4 = *sys.new_Parameter("Ixy4",IXYB);
    	symbol_numeric  Iyy4 = *sys.new_Parameter("Iyy4",IYYB);
	symbol_numeric  Ixz4 = *sys.new_Parameter("Ixz4",IXZB);
    	symbol_numeric  Izz4 = *sys.new_Parameter("Izz4",IZZB);
	symbol_numeric  Iyz4 = *sys.new_Parameter("Iyz4",IYZB);

	// Inertial parameters of the BAR5
    	symbol_numeric  m5 = *sys.new_Parameter("m5",MB);
	symbol_numeric  mx5 = *sys.new_Parameter("mx5",MXB);
    	symbol_numeric  my5 = *sys.new_Parameter("my5",MYB);
	symbol_numeric  mz5 = *sys.new_Parameter("mz5",MZB);
    	symbol_numeric  Ixx5 = *sys.new_Parameter("Ixx5",IXXB);
	symbol_numeric  Ixy5 = *sys.new_Parameter("Ixy5",IXYB);
    	symbol_numeric  Iyy5 = *sys.new_Parameter("Iyy5",IYYB);
	symbol_numeric  Ixz5 = *sys.new_Parameter("Ixz5",IXZB);
    	symbol_numeric  Izz5 = *sys.new_Parameter("Izz5",IZZB);
	symbol_numeric  Iyz5 = *sys.new_Parameter("Iyz5",IYZB);

	// Inertial parameters of the BAR6
    	symbol_numeric  m6 = *sys.new_Parameter("m6",MB);
	symbol_numeric  mx6 = *sys.new_Parameter("mx6",MXB);
    	symbol_numeric  my6 = *sys.new_Parameter("my6",MYB);
	symbol_numeric  mz6 = *sys.new_Parameter("mz6",MZB);
    	symbol_numeric  Ixx6 = *sys.new_Parameter("Ixx6",IXXB);
	symbol_numeric  Ixy6 = *sys.new_Parameter("Ixy6",IXYB);
    	symbol_numeric  Iyy6 = *sys.new_Parameter("Iyy6",IYYB);
	symbol_numeric  Ixz6 = *sys.new_Parameter("Ixz6",IXZB);
    	symbol_numeric  Izz6 = *sys.new_Parameter("Izz6",IZZB);
	symbol_numeric  Iyz6 = *sys.new_Parameter("Iyz6",IYZB);

// 	// Inertial parameters of the PLATFORM
//     	symbol_numeric  mP = *sys.new_Parameter("mP",6.6970);
// 	symbol_numeric  mxP = *sys.new_Parameter("mxP",0.0);
//     	symbol_numeric  myP = *sys.new_Parameter("myP",0.0);
// 	symbol_numeric  mzP = *sys.new_Parameter("mzP",-0.035572*6.6970);
//     	symbol_numeric  IxxP = *sys.new_Parameter("IxxP",0.038045);
// 	symbol_numeric  IxyP = *sys.new_Parameter("IxyP",0.0);
//     	symbol_numeric  IyyP = *sys.new_Parameter("IyyP",0.028319);
// 	symbol_numeric  IxzP = *sys.new_Parameter("IxzP",0.0);
//     	symbol_numeric  IzzP = *sys.new_Parameter("IzzP",0.028319);
// 	symbol_numeric  IyzP = *sys.new_Parameter("IyzP",0.0);
// 
// 	// Inertial parameters of the BAR1
//     	symbol_numeric  m1 = *sys.new_Parameter("m1",2.9369+2.867);
// 	symbol_numeric  mx1 = *sys.new_Parameter("mx1",-0.5*2.9369);
//     	symbol_numeric  my1 = *sys.new_Parameter("my1",0.0);
// 	symbol_numeric  mz1 = *sys.new_Parameter("mz1",0.0);
//     	symbol_numeric  Ixx1 = *sys.new_Parameter("Ixx1",0.0022722);
// 	symbol_numeric  Ixy1 = *sys.new_Parameter("Ixy1",0.0);
//     	symbol_numeric  Iyy1 = *sys.new_Parameter("Iyy1",1.0435);
// 	symbol_numeric  Ixz1 = *sys.new_Parameter("Ixz1",0.0);
//     	symbol_numeric  Izz1 = *sys.new_Parameter("Izz1",1.0435);
// 	symbol_numeric  Iyz1 = *sys.new_Parameter("Iyz1",0.0);
// 	
// 
// 	// Inertial parameters of the BAR2
//     	symbol_numeric  m2 = *sys.new_Parameter("m2",2.9369+2.867);
// 	symbol_numeric  mx2 = *sys.new_Parameter("mx2",-0.5*2.9369);
//     	symbol_numeric  my2 = *sys.new_Parameter("my2",0.0);
// 	symbol_numeric  mz2 = *sys.new_Parameter("mz2",0.0);
//     	symbol_numeric  Ixx2 = *sys.new_Parameter("Ixx2",0.0022722);
// 	symbol_numeric  Ixy2 = *sys.new_Parameter("Ixy2",0.0);
//     	symbol_numeric  Iyy2 = *sys.new_Parameter("Iyy2",1.0435);
// 	symbol_numeric  Ixz2 = *sys.new_Parameter("Ixz2",0.0);
//     	symbol_numeric  Izz2 = *sys.new_Parameter("Izz2",1.0435);
// 	symbol_numeric  Iyz2 = *sys.new_Parameter("Iyz2",0.0);
// 
// 	// Inertial parameters of the BAR3
//     	symbol_numeric  m3 = *sys.new_Parameter("m3",2.9369+2.867);
// 	symbol_numeric  mx3 = *sys.new_Parameter("mx3",-0.5*2.9369);
//     	symbol_numeric  my3 = *sys.new_Parameter("my3",0.0);
// 	symbol_numeric  mz3 = *sys.new_Parameter("mz3",0.0);
//     	symbol_numeric  Ixx3 = *sys.new_Parameter("Ixx3",0.0022722);
// 	symbol_numeric  Ixy3 = *sys.new_Parameter("Ixy3",0.0);
//     	symbol_numeric  Iyy3 = *sys.new_Parameter("Iyy3",1.0435);
// 	symbol_numeric  Ixz3 = *sys.new_Parameter("Ixz3",0.0);
//     	symbol_numeric  Izz3 = *sys.new_Parameter("Izz3",1.0435);
// 	symbol_numeric  Iyz3 = *sys.new_Parameter("Iyz3",0.0);
// 	
// 	// Inertial parameters of the BAR4
//     	symbol_numeric  m4 = *sys.new_Parameter("m4",2.9369+2.867);
// 	symbol_numeric  mx4 = *sys.new_Parameter("mx4",-0.5*2.9369);
//     	symbol_numeric  my4 = *sys.new_Parameter("my4",0.0);
// 	symbol_numeric  mz4 = *sys.new_Parameter("mz4",0.0);
//     	symbol_numeric  Ixx4 = *sys.new_Parameter("Ixx4",0.0022722);
// 	symbol_numeric  Ixy4 = *sys.new_Parameter("Ixy4",0.0);
//     	symbol_numeric  Iyy4 = *sys.new_Parameter("Iyy4",1.0435);
// 	symbol_numeric  Ixz4 = *sys.new_Parameter("Ixz4",0.0);
//     	symbol_numeric  Izz4 = *sys.new_Parameter("Izz4",1.0435);
// 	symbol_numeric  Iyz4 = *sys.new_Parameter("Iyz4",0.0);
// 
// 	// Inertial parameters of the BAR5
//     	symbol_numeric  m5 = *sys.new_Parameter("m5",2.9369+2.867);
// 	symbol_numeric  mx5 = *sys.new_Parameter("mx5",-0.5*2.9369);
//     	symbol_numeric  my5 = *sys.new_Parameter("my5",0.0);
// 	symbol_numeric  mz5 = *sys.new_Parameter("mz5",0.0);
//     	symbol_numeric  Ixx5 = *sys.new_Parameter("Ixx5",0.0022722);
// 	symbol_numeric  Ixy5 = *sys.new_Parameter("Ixy5",0.0);
//     	symbol_numeric  Iyy5 = *sys.new_Parameter("Iyy5",1.0435);
// 	symbol_numeric  Ixz5 = *sys.new_Parameter("Ixz5",0.0);
//     	symbol_numeric  Izz5 = *sys.new_Parameter("Izz5",1.0435);
// 	symbol_numeric  Iyz5 = *sys.new_Parameter("Iyz5",0.0);
// 
// 	// Inertial parameters of the BAR6
//     	symbol_numeric  m6 = *sys.new_Parameter("m6",2.9369+2.867);
// 	symbol_numeric  mx6 = *sys.new_Parameter("mx6",-0.5*2.9369);
//     	symbol_numeric  my6 = *sys.new_Parameter("my6",0.0);
// 	symbol_numeric  mz6 = *sys.new_Parameter("mz6",0.0);
//     	symbol_numeric  Ixx6 = *sys.new_Parameter("Ixx6",0.0022722);
// 	symbol_numeric  Ixy6 = *sys.new_Parameter("Ixy6",0.0);
//     	symbol_numeric  Iyy6 = *sys.new_Parameter("Iyy6",1.0435);
// 	symbol_numeric  Ixz6 = *sys.new_Parameter("Ixz6",0.0);
//     	symbol_numeric  Izz6 = *sys.new_Parameter("Izz6",1.0435);
// 	symbol_numeric  Iyz6 = *sys.new_Parameter("Iyz6",0.0);
	

	Vector3D P_GP= *sys.new_Vector3D("P_GP",mxP/mP,myP/mP,mzP/mP,"BP");

	Vector3D A1_G1= *sys.new_Vector3D("A1_G1",mx1/m1,my1/m1,mz1/m1,"B1");
	Vector3D A2_G2= *sys.new_Vector3D("A2_G2",mx2/m2,my2/m2,mz2/m2,"B2");
	Vector3D A3_G3= *sys.new_Vector3D("A3_G3",mx3/m3,my3/m3,mz3/m3,"B3");
	Vector3D A4_G4= *sys.new_Vector3D("A4_G4",mx4/m4,my4/m4,mz4/m4,"B4");
	Vector3D A5_G5= *sys.new_Vector3D("A5_G5",mx5/m5,my5/m5,mz5/m5,"B5");
	Vector3D A6_G6= *sys.new_Vector3D("A6_G6",mx6/m6,my6/m6,mz6/m6,"B6");

	//Inertia Tensors

// -----------------------------------------------------------------------
	Tensor3D IP = *sys.new_Tensor3D("IP",	(ex)IxxP,(ex)IxyP,(ex)IxzP,
						(ex)IxyP,(ex)IyyP,(ex)IyzP,
						(ex)IxzP,(ex)IyzP,(ex)IzzP,"BP");
// -----------------------------------------------------------------------
    	Tensor3D I1 = *sys.new_Tensor3D("I1",	(ex)Ixx1,(ex)Ixy1,(ex)Ixz1,
						(ex)Ixy1,(ex)Iyy1,(ex)Iyz1,
						(ex)Ixz1,(ex)Iyz1,(ex)Izz1,"B1");
// -----------------------------------------------------------------------
    	Tensor3D I2 = *sys.new_Tensor3D("I2",	(ex)Ixx2,(ex)Ixy2,(ex)Ixz2,
						(ex)Ixy2,(ex)Iyy2,(ex)Iyz2,
						(ex)Ixz2,(ex)Iyz2,(ex)Izz2,"B2");
// -----------------------------------------------------------------------
    	Tensor3D I3 = *sys.new_Tensor3D("I3",	(ex)Ixx3,(ex)Ixy3,(ex)Ixz3,
						(ex)Ixy3,(ex)Iyy3,(ex)Iyz3,
						(ex)Ixz3,(ex)Iyz3,(ex)Izz3,"B3");
// -----------------------------------------------------------------------
    	Tensor3D I4 = *sys.new_Tensor3D("I4",	(ex)Ixx4,(ex)Ixy4,(ex)Ixz4,
						(ex)Ixy4,(ex)Iyy4,(ex)Iyz4,
						(ex)Ixz4,(ex)Iyz4,(ex)Izz4,"B4");
// -----------------------------------------------------------------------
    	Tensor3D I5 = *sys.new_Tensor3D("I5",	(ex)Ixx5,(ex)Ixy5,(ex)Ixz5,
						(ex)Ixy5,(ex)Iyy5,(ex)Iyz5,
						(ex)Ixz5,(ex)Iyz5,(ex)Izz5,"B5");
// -----------------------------------------------------------------------
    	Tensor3D I6 = *sys.new_Tensor3D("I6",	(ex)Ixx6,(ex)Ixy6,(ex)Ixz6,
						(ex)Ixy6,(ex)Iyy6,(ex)Iyz6,
						(ex)Ixz6,(ex)Iyz6,(ex)Izz6,"B6");
// -----------------------------------------------------------------------

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_P = sys.new_Frame("Fra_P","P","BP");
	
	Frame * Fra_1= sys.new_Frame("Fra_1","A1","B1");
	Frame * Fra_2= sys.new_Frame("Fra_2","A2","B2");
	Frame * Fra_3= sys.new_Frame("Fra_3","A3","B3");
	Frame * Fra_4= sys.new_Frame("Fra_4","A4","B4");
	Frame * Fra_5= sys.new_Frame("Fra_5","A5","B5");
	Frame * Fra_6= sys.new_Frame("Fra_6","A6","B6");


// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	Solid * PLATFORM = sys.new_Solid("PLATFORM","P","BP","mP","P_GP","IP");
	
	Solid * BAR1 = sys.new_Solid("BAR1","A1","B1","m1","A1_G1","I1");
	Solid * BAR2 = sys.new_Solid("BAR2","A2","B2","m2","A2_G2","I2");
	Solid * BAR3 = sys.new_Solid("BAR3","A3","B3","m3","A3_G3","I3");
	Solid * BAR4 = sys.new_Solid("BAR4","A4","B4","m4","A4_G4","I4");
	Solid * BAR5 = sys.new_Solid("BAR5","A5","B5","m5","A5_G5","I5");
	Solid * BAR6 = sys.new_Solid("BAR6","A6","B6","m6","A6_G6","I6");

// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

        Drawing3D * PLATFORM_3D = sys.new_Drawing3D("PLATFORM_3D", "P", "BP" ,"./solids/plataforma_R05.stl",1,0,0,0.6);
        PLATFORM_3D->set_scale(0.1);

        Drawing3D * BAR1_3D = sys.new_Drawing3D("BAR1_3D", BAR1,"./solids/barra_mz.stl" ,1,0,0,1.0);	//BAR1D_3D->set_scale(0.5);
        Drawing3D * BAR2_3D = sys.new_Drawing3D("BAR2_3D", BAR2,"./solids/barra_mz.stl" ,1,0,0,1.0);
        Drawing3D * BAR3_3D = sys.new_Drawing3D("BAR3_3D", BAR3,"./solids/barra_mz.stl" ,1,0,0,1.0);
        Drawing3D * BAR4_3D = sys.new_Drawing3D("BAR4_3D", BAR4,"./solids/barra_mz.stl" ,1,0,0,1.0);
        Drawing3D * BAR5_3D = sys.new_Drawing3D("BAR5_3D", BAR5,"./solids/barra_mz.stl" ,1,0,0,1.0);
        Drawing3D * BAR6_3D = sys.new_Drawing3D("BAR6_3D", BAR6,"./solids/barra_mz.stl" ,1,0,0,1.0);

        Drawing3D * BAR1V_3D = sys.new_Drawing3D("BAR1V_3D",  "A1", "xyz" ,"./solids/barra_mz.stl" ,1,0,0,1.0);	//BAR1D_3D->set_scale(0.5);
        Drawing3D * BAR2V_3D = sys.new_Drawing3D("BAR2V_3D",  "A2", "xyz" ,"./solids/barra_mz.stl" ,1,0,0,1.0);
        Drawing3D * BAR3V_3D = sys.new_Drawing3D("BAR3V_3D",  "A3", "xyz" ,"./solids/barra_mz.stl" ,1,0,0,1.0);
        Drawing3D * BAR4V_3D = sys.new_Drawing3D("BAR4V_3D",  "A4", "xyz" ,"./solids/barra_mz.stl" ,1,0,0,1.0);
        Drawing3D * BAR5V_3D = sys.new_Drawing3D("BAR5V_3D",  "A5", "xyz" ,"./solids/barra_mz.stl" ,1,0,0,1.0);
        Drawing3D * BAR6V_3D = sys.new_Drawing3D("BAR6V_3D",  "A6", "xyz" ,"./solids/barra_mz.stl" ,1,0,0,1.0);

	Drawing3D * BALL1A_3D = sys.new_Drawing3D("BALL1A_3D", "A1", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL2A_3D = sys.new_Drawing3D("BALL2A_3D", "A2", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL3A_3D = sys.new_Drawing3D("BALL3A_3D", "A3", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL4A_3D = sys.new_Drawing3D("BALL4A_3D", "A4", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL5A_3D = sys.new_Drawing3D("BALL5A_3D", "A5", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL6A_3D = sys.new_Drawing3D("BALL6A_3D", "A6", "xyz" ,"./solids/bola.stl",0,0,1,1.0);

	Drawing3D * BALL1D_3U = sys.new_Drawing3D("BALL1D_3D", "D1", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL2D_3U = sys.new_Drawing3D("BALL2D_3D", "D2", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL3D_3U = sys.new_Drawing3D("BALL3D_3D", "D3", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL4D_3U = sys.new_Drawing3D("BALL4D_3D", "D4", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL5D_3U = sys.new_Drawing3D("BALL5D_3D", "D5", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL6D_3U = sys.new_Drawing3D("BALL6D_3D", "D6", "xyz" ,"./solids/bola.stl",0,0,1,1.0);

	Drawing3D * BALL1C_3U = sys.new_Drawing3D("BALL1C_3D", "C1", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL2C_3U = sys.new_Drawing3D("BALL2C_3D", "C2", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL3C_3U = sys.new_Drawing3D("BALL3C_3D", "C3", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL4C_3U = sys.new_Drawing3D("BALL4C_3D", "C4", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL5C_3U = sys.new_Drawing3D("BALL5C_3D", "C5", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
	Drawing3D * BALL6C_3U = sys.new_Drawing3D("BALL6C_3D", "C6", "xyz" ,"./solids/bola.stl",0,0,1,1.0);

        Drawing3D * Fra_PLATFORM_3D = sys.new_Drawing3D("Fra_PLATFORM_3D","Fra_P",0.1);
        Drawing3D * Fra_BAR1_3D = sys.new_Drawing3D("Fra_BAR1_3D","Fra_1",0.1);
        Drawing3D * Fra_BAR2_3D = sys.new_Drawing3D("Fra_BAR2_3D","Fra_2",0.1);
        Drawing3D * Fra_BAR3_3D = sys.new_Drawing3D("Fra_BAR3_3D","Fra_3",0.1);
        Drawing3D * Fra_BAR4_3D = sys.new_Drawing3D("Fra_BAR4_3D","Fra_4",0.1);
        Drawing3D * Fra_BAR5_3D = sys.new_Drawing3D("Fra_BAR5_3D","Fra_5",0.1);
        Drawing3D * Fra_BAR6_3D = sys.new_Drawing3D("Fra_BAR6_3D","Fra_6",0.1);

// 	Drawing3D * Suelo3D = sys.new_Drawing3D("Suelo3D", "O", "xyz" ,"./solids/ground.stl",0,1,0,1.0);
// 	Suelo3D->set_scale(0.1);



// ************************************************************************************************
//	Forces Definition
// ************************************************************************************************

	symbol_numeric Fs1 = *sys.new_Parameter("Fs1",0.0);
	symbol_numeric Fs2 = *sys.new_Parameter("Fs2",0.0);
	symbol_numeric Fs3 = *sys.new_Parameter("Fs3",0.0);
	symbol_numeric Fs4 = *sys.new_Parameter("Fs4",0.0);
	symbol_numeric Fs5 = *sys.new_Parameter("Fs5",0.0);
	symbol_numeric Fs6 = *sys.new_Parameter("Fs6",0.0);

	Vector3D F1 = *sys.new_Vector3D("F1",0.0,0.0,Fs1, "xyz");	
	Vector3D F2 = *sys.new_Vector3D("F2",0.0,0.0,Fs2, "xyz");	
	Vector3D F3 = *sys.new_Vector3D("F3",0.0,0.0,Fs3, "xyz");	
	Vector3D F4 = *sys.new_Vector3D("F4",0.0,0.0,Fs4, "xyz");	
	Vector3D F5 = *sys.new_Vector3D("F5",0.0,0.0,Fs5, "xyz");	
	Vector3D F6 = *sys.new_Vector3D("F6",0.0,0.0,Fs6, "xyz");	

	Vector3D M1 = *sys.new_Vector3D("M1",0.0,0.0,0.0, "xyz");
	Vector3D M2 = *sys.new_Vector3D("M2",0.0,0.0,0.0, "xyz");
	Vector3D M3 = *sys.new_Vector3D("M3",0.0,0.0,0.0, "xyz");
	Vector3D M4 = *sys.new_Vector3D("M4",0.0,0.0,0.0, "xyz");
	Vector3D M5 = *sys.new_Vector3D("M5",0.0,0.0,0.0, "xyz");
	Vector3D M6 = *sys.new_Vector3D("M6",0.0,0.0,0.0, "xyz");

	
	

// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * GravityP = sys.Gravity_Wrench("PLATFORM");
	Wrench3D * Gravity1 = sys.Gravity_Wrench("BAR1");
	Wrench3D * Gravity2 = sys.Gravity_Wrench("BAR2");
	Wrench3D * Gravity3 = sys.Gravity_Wrench("BAR3");
	Wrench3D * Gravity4 = sys.Gravity_Wrench("BAR4");	
	Wrench3D * Gravity5 = sys.Gravity_Wrench("BAR5");
	Wrench3D * Gravity6 = sys.Gravity_Wrench("BAR6");

	//	Inertia
	Wrench3D * Inertia_P = sys.Inertia_Wrench("PLATFORM");
	Wrench3D * Inertia_1 = sys.Inertia_Wrench("BAR1");
	Wrench3D * Inertia_2 = sys.Inertia_Wrench("BAR2");
	Wrench3D * Inertia_3 = sys.Inertia_Wrench("BAR3");
	Wrench3D * Inertia_4 = sys.Inertia_Wrench("BAR4");
	Wrench3D * Inertia_5 = sys.Inertia_Wrench("BAR5");
	Wrench3D * Inertia_6 = sys.Inertia_Wrench("BAR6");
	
	//	External Moments
	//~ Wrench3D * WExternalAction1 = sys.new_Wrench3D ( "WExternalAction1", F1, M1, A1 , BAR1 , "Constitutive") ;
	//~ Wrench3D * WExternalAction2 = sys.new_Wrench3D ( "WExternalAction2", F2, M2, A2 , BAR2 , "Constitutive") ;
	//~ Wrench3D * WExternalAction3 = sys.new_Wrench3D ( "WExternalAction3", F3, M3, A3 , BAR3 , "Constitutive") ;
	//~ Wrench3D * WExternalAction4 = sys.new_Wrench3D ( "WExternalAction4", F4, M4, A4 , BAR4 , "Constitutive") ;
	//~ Wrench3D * WExternalAction5 = sys.new_Wrench3D ( "WExternalAction5", F5, M5, A5 , BAR5 , "Constitutive") ;
	//~ Wrench3D * WExternalAction6 = sys.new_Wrench3D ( "WExternalAction6", F6, M6, A6 , BAR6 , "Constitutive") ;

// 	Wrench3D * WExternalReaction1 = sys.new_Wrench3D ( "WExternalReaction1", -F1, M1, A1 , BAR1D , "Constitutive") ;
// 	Wrench3D * WExternalReaction2 = sys.new_Wrench3D ( "WExternalReaction2", -F2, M2, A2 , BAR2D , "Constitutive") ;
// 	Wrench3D * WExternalReaction3 = sys.new_Wrench3D ( "WExternalReaction3", -F3, M3, A3 , BAR3D , "Constitutive") ;
// 	Wrench3D * WExternalReaction4 = sys.new_Wrench3D ( "WExternalReaction4", -F4, M4, A4 , BAR4D , "Constitutive") ;
// 	Wrench3D * WExternalReaction5 = sys.new_Wrench3D ( "WExternalReaction5", -F5, M5, A5 , BAR5D , "Constitutive") ;
// 	Wrench3D * WExternalReaction6 = sys.new_Wrench3D ( "WExternalReaction6", -F6, M6, A6 , BAR6D , "Constitutive") ;

		
    symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");
    symbol_numeric lambda2  = *sys.new_Joint_Unknown("lambda2");
    symbol_numeric lambda3  = *sys.new_Joint_Unknown("lambda3");
    symbol_numeric lambda4  = *sys.new_Joint_Unknown("lambda4");
    symbol_numeric lambda5  = *sys.new_Joint_Unknown("lambda5");
    symbol_numeric lambda6  = *sys.new_Joint_Unknown("lambda6");
    symbol_numeric lambda7  = *sys.new_Joint_Unknown("lambda7");
    symbol_numeric lambda8  = *sys.new_Joint_Unknown("lambda8");
    symbol_numeric lambda9  = *sys.new_Joint_Unknown("lambda9");
    symbol_numeric lambda10 = *sys.new_Joint_Unknown("lambda10");
    symbol_numeric lambda11 = *sys.new_Joint_Unknown("lambda11");
    symbol_numeric lambda12 = *sys.new_Joint_Unknown("lambda12");
    symbol_numeric lambda13 = *sys.new_Joint_Unknown("lambda13");
    symbol_numeric lambda14 = *sys.new_Joint_Unknown("lambda14");
    symbol_numeric lambda15 = *sys.new_Joint_Unknown("lambda15");
    symbol_numeric lambda16 = *sys.new_Joint_Unknown("lambda16");
    symbol_numeric lambda17 = *sys.new_Joint_Unknown("lambda17");
    symbol_numeric lambda18 = *sys.new_Joint_Unknown("lambda18");

/*
	symbol_numeric lambda19 = *sys.new_Joint_Unknown("lambda19");
	symbol_numeric lambda20 = *sys.new_Joint_Unknown("lambda20");    
	symbol_numeric lambda21 = *sys.new_Joint_Unknown("lambda21");
	symbol_numeric lambda22 = *sys.new_Joint_Unknown("lambda22");
	symbol_numeric lambda23 = *sys.new_Joint_Unknown("lambda23");
	symbol_numeric lambda24 = *sys.new_Joint_Unknown("lambda24");
//*/
// ************************************************************************************************
// 	Vectors needed to take diferent Jacobians
// ************************************************************************************************

	cout << "Vectors needed to take diferent Jacobians" << endl;

	Matrix q = sys.Coordinates();
	Matrix dq = sys.Velocities();
	Matrix ddq = sys.Accelerations();
//	Matrix epsilon = sys.Joint_Unknowns();
	Matrix pars = sys.Parameters();
//	Matrix inps = sys.Inputs();
//	Matrix unks = sys.Joint_Unknowns();

// ************************************************************************************************
// 	 Parameters for the Trajectory optimization 
// ************************************************************************************************
// // Constante term of the Fourier Series
// 	symbol_numeric  FS001 = *sys.new_Parameter("FS001",1.00);
// 	symbol_numeric  FS002 = *sys.new_Parameter("FS002",1.00);
// 	symbol_numeric  FS003 = *sys.new_Parameter("FS003",1.00);
// 	symbol_numeric  FS004 = *sys.new_Parameter("FS004",1.00);
// 	symbol_numeric  FS005 = *sys.new_Parameter("FS005",1.00);
// 	symbol_numeric  FS006 = *sys.new_Parameter("FS006",1.00);
// 
// // First harmonic of the Fourier Series	
// 	symbol_numeric  FSa11 = *sys.new_Parameter("FSa11",0.30);
// 	symbol_numeric  FSb11 = *sys.new_Parameter("FSb11",0.00);
// 	symbol_numeric  FSa12 = *sys.new_Parameter("FSa12",0.30);
// 	symbol_numeric  FSb12 = *sys.new_Parameter("FSb12",0.00);
// 	symbol_numeric  FSa13 = *sys.new_Parameter("FSa13",0.30);
// 	symbol_numeric  FSb13 = *sys.new_Parameter("FSb13",0.00);
// 	symbol_numeric  FSa14 = *sys.new_Parameter("FSa14",0.30);
// 	symbol_numeric  FSb14 = *sys.new_Parameter("FSb14",0.00);
// 	symbol_numeric  FSa15 = *sys.new_Parameter("FSa15",0.30);
// 	symbol_numeric  FSb15 = *sys.new_Parameter("FSb15",0.00);
// 	symbol_numeric  FSa16 = *sys.new_Parameter("FSa16",0.30);
// 	symbol_numeric  FSb16 = *sys.new_Parameter("FSb16",0.00);
// 
// // Second harmonic of the Fourier Series	
// 	symbol_numeric  FSa21 = *sys.new_Parameter("FSa21",0.30);
// 	symbol_numeric  FSb21 = *sys.new_Parameter("FSb21",0.00);
// 	symbol_numeric  FSa22 = *sys.new_Parameter("FSa22",0.30);
// 	symbol_numeric  FSb22 = *sys.new_Parameter("FSb22",0.00);
// 	symbol_numeric  FSa23 = *sys.new_Parameter("FSa23",0.30);
// 	symbol_numeric  FSb23 = *sys.new_Parameter("FSb23",0.00);
// 	symbol_numeric  FSa24 = *sys.new_Parameter("FSa24",0.30);
// 	symbol_numeric  FSb24 = *sys.new_Parameter("FSb24",0.00);
// 	symbol_numeric  FSa25 = *sys.new_Parameter("FSa25",0.30);
// 	symbol_numeric  FSb25 = *sys.new_Parameter("FSb25",0.00);
// 	symbol_numeric  FSa26 = *sys.new_Parameter("FSa26",0.30);
// 	symbol_numeric  FSb26 = *sys.new_Parameter("FSb26",0.00);
// 	

	

// 	---------------------------------------------
// 	ESTIMATION TRAJECTORY
// 	---------------------------------------------
// // Values of the parameters for the optimized trajectory: TRAJ_ML_ml_m084
// 	symbol_numeric FS001 = *sys.new_Parameter("FS001",1.9176124396);
// 	symbol_numeric FSa11 = *sys.new_Parameter("FSa11",0.0226724983);
// 	symbol_numeric FSb11 = *sys.new_Parameter("FSb11",0.0416346333);
// 	symbol_numeric FSa21 = *sys.new_Parameter("FSa21",-0.1841114295);
// 	symbol_numeric FSb21 = *sys.new_Parameter("FSb21",0.0447631002);
// 	symbol_numeric FS002 = *sys.new_Parameter("FS002",1.8990381325);
// 	symbol_numeric FSa12 = *sys.new_Parameter("FSa12",0.0086371247);
// 	symbol_numeric FSb12 = *sys.new_Parameter("FSb12",0.0073324005);
// 	symbol_numeric FSa22 = *sys.new_Parameter("FSa22",-0.1875818896);
// 	symbol_numeric FSb22 = *sys.new_Parameter("FSb22",0.0310683222);
// 	symbol_numeric FS003 = *sys.new_Parameter("FS003",1.8567910645);
// 	symbol_numeric FSa13 = *sys.new_Parameter("FSa13",0.0299989761);
// 	symbol_numeric FSb13 = *sys.new_Parameter("FSb13",-0.0043179374);
// 	symbol_numeric FSa23 = *sys.new_Parameter("FSa23",0.1646537896);
// 	symbol_numeric FSb23 = *sys.new_Parameter("FSb23",-0.1149177430);
// 	symbol_numeric FS004 = *sys.new_Parameter("FS004",1.8823671182);
// 	symbol_numeric FSa14 = *sys.new_Parameter("FSa14",0.0208017276);
// 	symbol_numeric FSb14 = *sys.new_Parameter("FSb14",0.0666648932);
// 	symbol_numeric FSa24 = *sys.new_Parameter("FSa24",0.0809601471);
// 	symbol_numeric FSb24 = *sys.new_Parameter("FSb24",-0.1254737693);
// 	symbol_numeric FS005 = *sys.new_Parameter("FS005",1.8783444785);
// 	symbol_numeric FSa15 = *sys.new_Parameter("FSa15",0.0467704622);
// 	symbol_numeric FSb15 = *sys.new_Parameter("FSb15",-0.0978437330);
// 	symbol_numeric FSa25 = *sys.new_Parameter("FSa25",0.1473298825);
// 	symbol_numeric FSb25 = *sys.new_Parameter("FSb25",-0.0598144637);
// 	symbol_numeric FS006 = *sys.new_Parameter("FS006",1.8905386390);
// 	symbol_numeric FSa16 = *sys.new_Parameter("FSa16",0.0436547324);
// 	symbol_numeric FSb16 = *sys.new_Parameter("FSb16",-0.1035253812);
// 	symbol_numeric FSa26 = *sys.new_Parameter("FSa26",0.1423708535);
// 	symbol_numeric FSb26 = *sys.new_Parameter("FSb26",-0.0786870709);
	

// 	---------------------------------------------
// 	VALIDATION TRAJECTORY
// 	---------------------------------------------

// // Values of the parameters for the optimized trajectory: TRAJ_ML_ml_m080
// 	symbol_numeric FS001 = *sys.new_Parameter("FS001",1.9080371527);
// 	symbol_numeric FSa11 = *sys.new_Parameter("FSa11",-0.1352305446);
// 	symbol_numeric FSb11 = *sys.new_Parameter("FSb11",-0.1401947800);
// 	symbol_numeric FSa21 = *sys.new_Parameter("FSa21",-0.0186864160);
// 	symbol_numeric FSb21 = *sys.new_Parameter("FSb21",0.0240366372);
// 	symbol_numeric FS002 = *sys.new_Parameter("FS002",1.9473207034);
// 	symbol_numeric FSa12 = *sys.new_Parameter("FSa12",-0.1793505318);
// 	symbol_numeric FSb12 = *sys.new_Parameter("FSb12",-0.1310727942);
// 	symbol_numeric FSa22 = *sys.new_Parameter("FSa22",0.0073479498);
// 	symbol_numeric FSb22 = *sys.new_Parameter("FSb22",0.0450815167);
// 	symbol_numeric FS003 = *sys.new_Parameter("FS003",1.8463389502);
// 	symbol_numeric FSa13 = *sys.new_Parameter("FSa13",0.0011891211);
// 	symbol_numeric FSb13 = *sys.new_Parameter("FSb13",0.0031705871);
// 	symbol_numeric FSa23 = *sys.new_Parameter("FSa23",-0.1891751252);
// 	symbol_numeric FSb23 = *sys.new_Parameter("FSb23",-0.1448732967);
// 	symbol_numeric FS004 = *sys.new_Parameter("FS004",1.8875074820);
// 	symbol_numeric FSa14 = *sys.new_Parameter("FSa14",-0.0172847689);
// 	symbol_numeric FSb14 = *sys.new_Parameter("FSb14",-0.0097797205);
// 	symbol_numeric FSa24 = *sys.new_Parameter("FSa24",-0.2152239771);
// 	symbol_numeric FSb24 = *sys.new_Parameter("FSb24",-0.0848605420);
// 	symbol_numeric FS005 = *sys.new_Parameter("FS005",1.8376580872);
// 	symbol_numeric FSa15 = *sys.new_Parameter("FSa15",-0.0257523283);
// 	symbol_numeric FSb15 = *sys.new_Parameter("FSb15",-0.0049409193);
// 	symbol_numeric FSa25 = *sys.new_Parameter("FSa25",-0.1501138620);
// 	symbol_numeric FSb25 = *sys.new_Parameter("FSb25",-0.0070740629);
// 	symbol_numeric FS006 = *sys.new_Parameter("FS006",1.8415872247);
// 	symbol_numeric FSa16 = *sys.new_Parameter("FSa16",-0.0581898337);
// 	symbol_numeric FSb16 = *sys.new_Parameter("FSb16",-0.0329098780);
// 	symbol_numeric FSa26 = *sys.new_Parameter("FSa26",-0.1298693243);
// 	symbol_numeric FSb26 = *sys.new_Parameter("FSb26",-0.0313180415);
	
// Values of the parameters for the optimized trajectory: TRAJ_NLCONS3_COND_1103
	symbol_numeric FS001 = *sys.new_Parameter("FS001",1.9613765199);
	symbol_numeric FSa11 = *sys.new_Parameter("FSa11",-0.0336754822);
	symbol_numeric FSb11 = *sys.new_Parameter("FSb11",-0.0045098281);
	symbol_numeric FSa21 = *sys.new_Parameter("FSa21",-0.7689754014);
	symbol_numeric FSb21 = *sys.new_Parameter("FSb21",-0.3676786608);
	symbol_numeric FS002 = *sys.new_Parameter("FS002",1.9728988349);
	symbol_numeric FSa12 = *sys.new_Parameter("FSa12",-0.0776022728);
	symbol_numeric FSb12 = *sys.new_Parameter("FSb12",0.0878965485);
	symbol_numeric FSa22 = *sys.new_Parameter("FSa22",-0.8047741847);
	symbol_numeric FSb22 = *sys.new_Parameter("FSb22",-0.3329241081);
	symbol_numeric FS003 = *sys.new_Parameter("FS003",2.0079006745);
	symbol_numeric FSa13 = *sys.new_Parameter("FSa13",0.0017356238);
	symbol_numeric FSb13 = *sys.new_Parameter("FSb13",-0.0125723870);
	symbol_numeric FSa23 = *sys.new_Parameter("FSa23",-0.9313791467);
	symbol_numeric FSb23 = *sys.new_Parameter("FSb23",-0.0854105280);
	symbol_numeric FS004 = *sys.new_Parameter("FS004",1.9590377182);
	symbol_numeric FSa14 = *sys.new_Parameter("FSa14",0.0321935700);
	symbol_numeric FSb14 = *sys.new_Parameter("FSb14",0.0260634883);
	symbol_numeric FSa24 = *sys.new_Parameter("FSa24",-0.8812003190);
	symbol_numeric FSb24 = *sys.new_Parameter("FSb24",-0.0810686908);
	symbol_numeric FS005 = *sys.new_Parameter("FS005",2.0517043902);
	symbol_numeric FSa15 = *sys.new_Parameter("FSa15",-0.0806290115);
	symbol_numeric FSb15 = *sys.new_Parameter("FSb15",0.0269593209);
	symbol_numeric FSa25 = *sys.new_Parameter("FSa25",-0.8362234813);
	symbol_numeric FSb25 = *sys.new_Parameter("FSb25",-0.0882052295);
	symbol_numeric FS006 = *sys.new_Parameter("FS006",2.0439796766);
	symbol_numeric FSa16 = *sys.new_Parameter("FSa16",-0.0743009398);
	symbol_numeric FSb16 = *sys.new_Parameter("FSb16",0.0568773438);
	symbol_numeric FSa26 = *sys.new_Parameter("FSa26",-0.8597040139);
	symbol_numeric FSb26 = *sys.new_Parameter("FSb26",-0.0348242605);





// ************************************************************************************************
// 	 Kinematic Equations 
// ************************************************************************************************
	//~ Vector3D eq1 = OA1+A1C1-OP-PD1;
	//~ Vector3D eq2 = OA2+A2C2-OP-PD2;
	//~ Vector3D eq3 = OA3+A3C3-OP-PD3;
	//~ Vector3D eq4 = OA4+A4C4-OP-PD4;
	//~ Vector3D eq5 = OA5+A5C5-OP-PD5;
	//~ Vector3D eq6 = OA6+A6C6-OP-PD6;
    Vector3D eq1 = sys.Position_Vector(C1,D1);
    Vector3D eq2 = sys.Position_Vector(C2,D2);
    Vector3D eq3 = sys.Position_Vector(C3,D3);
    Vector3D eq4 = sys.Position_Vector(C4,D4);   
    Vector3D eq5 = sys.Position_Vector(C5,D5);
    Vector3D eq6 = sys.Position_Vector(C6,D6);   

	Matrix Phi(18,1);
	Phi(0 ,0)=eq1(0,0);
	Phi(1 ,0)=eq1(1,0);
	Phi(2 ,0)=eq1(2,0);
	Phi(3 ,0)=eq2(0,0);
	Phi(4 ,0)=eq2(1,0);
	Phi(5 ,0)=eq2(2,0);
	Phi(6 ,0)=eq3(0,0);
	Phi(7 ,0)=eq3(1,0);
	Phi(8 ,0)=eq3(2,0);
	Phi(9 ,0)=eq4(0,0);
	Phi(10,0)=eq4(1,0);
	Phi(11,0)=eq4(2,0);
	Phi(12,0)=eq5(0,0);
	Phi(13,0)=eq5(1,0);
	Phi(14,0)=eq5(2,0);
	Phi(15,0)=eq6(0,0);
	Phi(16,0)=eq6(1,0);
	Phi(17,0)=eq6(2,0);
    

/*
double	kons=1.0;

	Phi(18,0)=s1-kons*(FS001	+FSa11*sin(t)+FSb11*cos(t)	+FSa21*sin(2*t)+FSb21*cos(2*t));
	Phi(19,0)=s2-kons*(FS002	+FSa12*sin(t)+FSb12*cos(t)	+FSa22*sin(2*t)+FSb22*cos(2*t));
	Phi(20,0)=s3-kons*(FS003	+FSa13*sin(t)+FSb13*cos(t)	+FSa23*sin(2*t)+FSb23*cos(2*t));
	Phi(21,0)=s4-kons*(FS004	+FSa14*sin(t)+FSb14*cos(t)	+FSa24*sin(2*t)+FSb24*cos(2*t));
	Phi(22,0)=s5-kons*(FS005	+FSa15*sin(t)+FSb15*cos(t)	+FSa25*sin(2*t)+FSb25*cos(2*t));
	Phi(23,0)=s6-kons*(FS006	+FSa16*sin(t)+FSb16*cos(t)	+FSa26*sin(2*t)+FSb26*cos(2*t));
//*/

/*

 	Phi(18,0)=x;
 	Phi(19,0)=y;
 	Phi(20,0)=z-5.0;
 	Phi(21,0)=a-(FS001+FSa11*sin(t)+FSb11*cos(t));
 	Phi(22,0)=b-(FS002+FSa12*sin(t)+FSb12*cos(t));
 	Phi(23,0)=c;
//*/
	//Matrix dPhiNH(0,1);

	cout << "Non-linear Constraint Inequalities" << endl;
	
	Vector3D ezp = *sys.new_Vector3D("ezp",0,0,1,"BP");
	
	Vector3D ezb1 = *sys.new_Vector3D("ezb1",0,0,1,"B1");
	Vector3D ezb2 = *sys.new_Vector3D("ezb2",0,0,1,"B2");
	Vector3D ezb3 = *sys.new_Vector3D("ezb3",0,0,1,"B3");
	Vector3D ezb4 = *sys.new_Vector3D("ezb4",0,0,1,"B4");
	Vector3D ezb5 = *sys.new_Vector3D("ezb5",0,0,1,"B5");
	Vector3D ezb6 = *sys.new_Vector3D("ezb6",0,0,1,"B6");
	
	Matrix NolinPhi(6,1);
	NolinPhi(0,0)=ezp*ezb1;
	NolinPhi(1,0)=ezp*ezb2;
	NolinPhi(2,0)=ezp*ezb3;
	NolinPhi(3,0)=ezp*ezb4;
	NolinPhi(4,0)=ezp*ezb5;
	NolinPhi(5,0)=ezp*ezb6;

	lst new_atom_list_NolinPhi, new_exp_list_NolinPhi;        
	matrix_list_optimize (NolinPhi, new_atom_list_NolinPhi, new_exp_list_NolinPhi);
	sys.export_Matrix_C("NolinPhi","_NolinPhi",NolinPhi, new_atom_list_NolinPhi, new_exp_list_NolinPhi ,ORDER);
	
	sys.export_function_MATLAB("NolinPhi", "NolinPhi_", NolinPhi, new_atom_list_NolinPhi, new_exp_list_NolinPhi);

// 	sys.export_function_MATLAB_SYMPY("NolinPhi2", "NolinPhi2_", unatomize(NolinPhi));

// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************


	Matrix Dynamic_Equations = sys.GenForceSys("ALL");
	//cout<<Dynamic_Equations<<endl;

	lst inertial_parameters;

	inertial_parameters =	{mP, mxP, myP, mzP, IxxP, IxyP, IyyP, IxzP, IyzP, IzzP,
				m1, mx1, my1, mz1, Ixx1, Ixy1, Iyy1, Ixz1, Iyz1, Izz1,
				m2, mx2, my2, mz2, Ixx2, Ixy2, Iyy2, Ixz2, Iyz2, Izz2,
				m3, mx3, my3, mz3, Ixx3, Ixy3, Iyy3, Ixz3, Iyz3, Izz3,
				m4, mx4, my4, mz4, Ixx4, Ixy4, Iyy4, Ixz4, Iyz4, Izz4,
				m5, mx5, my5, mz5, Ixx5, Ixy5, Iyy5, Ixz5, Iyz5, Izz5,
				m6, mx6, my6, mz6, Ixx6, Ixy6, Iyy6, Ixz6, Iyz6, Izz6};

// 	syms 	mP mxP myP mzP IxxP IxyP IyyP IxzP IyzP IzzP m1 mx1 my1 mz1 Ixx1 Ixy1 Iyy1 Ixz1 Iyz1 Izz1 m2 mx2 my2 mz2 Ixx2 Ixy2 Iyy2 Ixz2 Iyz2 Izz2 m3 mx3 my3 mz3 Ixx3 Ixy3 Iyy3 Ixz3 Iyz3 Izz3 m4 mx4 my4 mz4 Ixx4 Ixy4 Iyy4 Ixz4 Iyz4 Izz4 m5 mx5 my5 mz5 Ixx5 Ixy5 Iyy5 Ixz5 Iyz5 Izz5 m6 mx6 my6 mz6 Ixx6 Ixy6 Iyy6 Ixz6 Iyz6 Izz6 real;
		
//psym=[mP;mxP;myP;mzP;IxxP;IxyP;IyyP;IxzP;IyzP;IzzP;m1;mx1;my1;mz1;Ixx1;Ixy1;Iyy1;Ixz1;Iyz1;Izz1;m2;mx2;my2;mz2;Ixx2;Ixy2;Iyy2;Ixz2;Iyz2;Izz2;m3;mx3;my3;mz3;Ixx3;Ixy3;Iyy3;Ixz3;Iyz3;Izz3;m4;mx4;my4;mz4;Ixx4;Ixy4;Iyy4;Ixz4;Iyz4;Izz4;m5;mx5;my5;mz5;Ixx5;Ixy5;Iyy5;Ixz5;Iyz5;Izz5;m6;mx6;my6;mz6;Ixx6;Ixy6;Iyy6;Ixz6;Iyz6;Izz6];

	Matrix M_inertial_parameters=Matrix(inertial_parameters.nops(),1,inertial_parameters);
	//~ Matrix W = sys.jacobian(Dynamic_Equations.transpose(),M_inertial_parameters);
	//~ Matrix Phiq= sys.jacobian(Phi.transpose(),q);
//~ 
	//~ 
         //~ cout << "pnum=["<< endl;
	//~ for (int i=0;i<inertial_parameters.nops();i++){
	  //~ symbol_numeric aux=ex_to<symbol_numeric>(inertial_parameters.op(i));
	    //~ cout << aux.get_value() << ";" << endl;
	//~ }
         //~ cout << "];"<< endl;
//~ 
	//~ cout << "psym=["<< endl;
	//~ for (int i=0;i<inertial_parameters.nops();i++){
	  //~ cout << inertial_parameters.op(i) << ";" << endl;
	//~ }
         //~ cout << "];"<< endl;
//~ 
//~ // 	cout << "Exporting MATLAB functions with SYMPY" << endl;
	//~ //sys.export_function_MATLAB_SYMPY("Phiq_optim","Phiq_optim_",Phiq);
//~ // 	sys.export_function_MATLAB_SYMPY("W_optim","W_optim_",W);
	 //~ 
	//~ cout << "Exporting Matrix W" << endl;
	//~ lst new_atom_list_W, new_exp_list_W;        
	//~ matrix_list_optimize (W, new_atom_list_W, new_exp_list_W);
	//~ sys.export_Matrix_C("W","_W",W, new_atom_list_W, new_exp_list_W ,ORDER);
	//~ sys.export_function_MATLAB("W", "W_", W, new_atom_list_W, new_exp_list_W);
//~ 
	//~ cout << "Exporting MATLAB functions" << endl;
	//~ sys.export_init_function_MATLAB();


// ************************************************************************************************
// 	Output Vector
// ************************************************************************************************

	cout << "Output Vector" << endl;

	Matrix Output(1,1);
	Output(0,0)=0;
	sys.new_Matrix("Output",Output);

// ************************************************************************************************
// 	Energy Equations
// ************************************************************************************************

	cout << "Energy Equations" << endl;

	Matrix Energy(1,1);
	Energy(0,0)=0;
	sys.new_Matrix("Energy",Energy);


// ************************************************************************************************
// 	Matrix Calculation 	
// ************************************************************************************************
	
        cout << "Matrix Calculation" << endl;
//	sys.Matrix_Calculation(coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);
//	sys.Matrix_Calculation(Phi, coord_indep_init, vel_indep_init, Dynamic_Equations, sys, METHOD, PROBLEM_TYPE,dPhiNH);
	sys.Matrix_Calculation(Phi, coord_indep_init, vel_indep_init,  sys, METHOD);
    
// ************************************************************************************************
// 	Export C code for Direct Simulation 
// ************************************************************************************************

	cout << "Export C code for Direct Simulation " << endl;

    sys.export_Dynamic_Simulation(sys, ORDER , MAPLE);

// ************************************************************************************************
// 	Indep-Dep Jaconians
// ************************************************************************************************
    lst ind;
    lst dep;
	//~ ind = s1,s2,s3,s4,s5,s6;
    dep = {x,y,z,a,b,c,a1,a2,a3,a4,a5,a6,b1,b2,b3,b4,b5,b6};

    ind= {*ds1,*ds2,*ds3,*ds4,*ds5,*ds6};
    dep = {*dx,*dy,*dz,*da,*dB,*dc,*da1,*da2,*da3,*da4,*da5,*da6,*dB1,*dB2,*dB3,*dB4,*dB5,*dB6};
    
    Matrix dPhi = sys.Dt(Phi);
    
    
    Matrix vel_dz=Matrix(ind.nops(),1,ind);
    Matrix vel_dd=Matrix(dep.nops(),1,dep);


    
    Matrix dPhi_dz= sys.jacobian(dPhi.transpose(),vel_dz);
    Matrix dPhi_dd= sys.jacobian(dPhi.transpose(),vel_dd);

    
    lst new_atom_list_dPhi_dz, new_exp_list_dPhi_dz;        
    matrix_list_optimize (dPhi_dz, new_atom_list_dPhi_dz, new_exp_list_dPhi_dz);
    lst new_atom_list_dPhi_dd, new_exp_list_dPhi_dd;        
    matrix_list_optimize (dPhi_dd, new_atom_list_dPhi_dd, new_exp_list_dPhi_dd);   
    
    sys.export_function_MATLAB("dPhi_dz", "dPhi_dz_", dPhi_dz, new_atom_list_dPhi_dz, new_exp_list_dPhi_dz,"q,time,param");
    sys.export_function_MATLAB("dPhi_dd", "dPhi_dd_", dPhi_dd, new_atom_list_dPhi_dd, new_exp_list_dPhi_dd,"q,time,param");



// ************************************************************************************************
// 	Recursive Dynamics
// ************************************************************************************************

symbol_numeric  gra = *sys.new_Parameter("gra",9.8);
sys.export_environment_m (  );

// FORWARD ITERATION

gravity =  UP;
Vector3D OMEGA0  = *sys.new_Vector3D("OMEGA0",0,0,0,"xyz") ;
Vector3D dOMEGA0 = sys.Dt(OMEGA0,Base_xyz );
Matrix U0 (3,3); U0(0,0) = 0; U0(0,1) = 0;U0(0,2) = 0; U0(1,0) = 0; U0(1,1) = 0; U0(1,2) = 0; U0(2,0) = 0; U0(2,1) = 0; U0(2,2) = 0;
Vector3D dV0 = *sys.new_Vector3D("dV0",0,0,gra,"xyz") ;


// SOLID PLATFORM
// *****************************************************************************************************
Vector3D OMEGA0__1  = OMEGA0.in_Base(sys.get_Base ("B0P"));
Vector3D OMEGA01 = sys.Angular_Velocity(Base_xyz,sys.get_Base ("B0P"));
Vector3D OMEGA1 = OMEGA0__1 + OMEGA01;
Vector3D dOMEGA1 =  dOMEGA0.in_Base(sys.get_Base ("B0P")) + sys.dt(OMEGA01) + (OMEGA1^OMEGA01);

Vector3D OMEGA1__2  = OMEGA1.in_Base(sys.get_Base ("BAP"));
Vector3D OMEGA12 = sys.Angular_Velocity(sys.get_Base ("B0P"),sys.get_Base ("BAP"));
Vector3D OMEGA2 = OMEGA1__2 + OMEGA12;
Vector3D dOMEGA2 =  dOMEGA1.in_Base(sys.get_Base ("BAP")) + sys.dt(OMEGA12) + (OMEGA2^OMEGA12);

Vector3D OMEGA2__P  = OMEGA2.in_Base(sys.get_Base ("BP"));
Vector3D OMEGA2P = sys.Angular_Velocity(sys.get_Base ("BAP"),sys.get_Base ("BP"));
Vector3D OMEGAP = OMEGA2__P + OMEGA2P;
Vector3D dOMEGAP =  dOMEGA2.in_Base(sys.get_Base ("BP")) + sys.dt(OMEGA2P) + (OMEGAP^OMEGA2P);

Matrix UPP =  dOMEGAP.skew() + OMEGAP.skew()*OMEGAP.skew();

Vector3D VP = sys.Velocity_Vector(Frame_abs,P);
Vector3D dVP = dV0 + sys.Dt(VP,Frame_abs);
//Vector3D dVP = (sys.Dt(sys.Velocity_Vector(Frame_abs,P),Frame_abs)).in_Base(sys.get_Base ("BP"));


Vector3D DP= *sys.new_Vector3D("DP",mxP,myP,mzP,"BP");
Vector3D UPdP(UPP*DP, DP.get_Base() );
UPdP.set_System ( &sys );

Vector3D ifiP = mP*dVP + UPdP;
Vector3D iniP = sys.dt(IP*OMEGAP) + (OMEGAP ^ (IP* OMEGAP)) + (DP ^ dVP);

Vector3D VP__P = VP.in_Base(sys.get_Base ("BP"));

Matrix eqfP = (mP*dVP).transpose() * sys.jacobian(VP.transpose(),dq) + UPdP.transpose()*sys.jacobian(VP__P.transpose(),dq);
Matrix eqnP = iniP.transpose() *sys.jacobian(OMEGAP.transpose(),dq);

Matrix eqP =eqfP + eqnP;
//cout << unatomize(eqP)<<endl;
//Matrix eqP2 = ifiP .transpose()*sys.jacobian(VP__P.transpose(),dq); cout << unatomize(eqP2)<<endl;
//Matrix eqP3 =  (mP*dVP + UPdP.in_Base(Base_xyz)).transpose()*sys.jacobian(VP__P.transpose(),dq); cout << unatomize(eqP3)<<endl;

//BAR1
// *****************************************************************************************************
Vector3D OMEGA0__BA1  = OMEGA0.in_Base(sys.get_Base ("BA1"));
Vector3D OMEGA0BA1 = sys.Angular_Velocity(Base_xyz,sys.get_Base ("BA1"));
Vector3D OMEGABA1 = OMEGA0__BA1 + OMEGA0BA1;
Vector3D dOMEGABA1 =  dOMEGA0.in_Base(sys.get_Base ("BA1")) + sys.dt(OMEGA0BA1) + (OMEGABA1^OMEGA0BA1);

Vector3D OMEGABA1__B1  = OMEGABA1.in_Base(sys.get_Base ("B1"));
Vector3D OMEGABA1B1 = sys.Angular_Velocity(sys.get_Base ("BA1"),sys.get_Base ("B1"));
Vector3D OMEGAB1 = OMEGABA1__B1  + OMEGABA1B1;
Vector3D dOMEGAB1 =  dOMEGABA1.in_Base(sys.get_Base ("B1")) + sys.dt(OMEGABA1B1) + (OMEGAB1^OMEGABA1B1);

Matrix U1 =  dOMEGAB1.skew() + OMEGAB1.skew()*OMEGAB1.skew();

Vector3D V1 = sys.Velocity_Vector(Frame_abs,A1);
Vector3D dV1 = dV0 + sys.Dt(V1,Frame_abs);

Vector3D DBar1= *sys.new_Vector3D("DBar1",mx1,my1,mz1,"B1");
Vector3D U1d1(U1*DBar1, DBar1.get_Base() );
U1d1.set_System ( &sys );

Vector3D ifi1 = m1*dV1 + U1d1;
Vector3D ini1 = sys.dt(I1*OMEGAB1) + (OMEGAB1 ^ (I1* OMEGAB1)) + (DBar1 ^ dV1);

Vector3D V1__B1 = V1.in_Base(sys.get_Base ("B1"));
Matrix eqf1 = (m1*dV1).transpose() * sys.jacobian(V1.transpose(),dq) + U1d1.transpose()*sys.jacobian(V1__B1.transpose(),dq);
Matrix eqn1 = ini1.transpose() *sys.jacobian(OMEGAB1.transpose(),dq);

Matrix eqB1 =eqf1 + eqn1;


//BAR2
// *****************************************************************************************************
Vector3D OMEGA0__BA2  = OMEGA0.in_Base(sys.get_Base ("BA2"));
Vector3D OMEGA0BA2 = sys.Angular_Velocity(Base_xyz,sys.get_Base ("BA2"));
Vector3D OMEGABA2 = OMEGA0__BA2 + OMEGA0BA2;
Vector3D dOMEGABA2 =  dOMEGA0.in_Base(sys.get_Base ("BA2")) + sys.dt(OMEGA0BA2) + (OMEGABA2^OMEGA0BA2);

Vector3D OMEGABA2__B2  = OMEGABA2.in_Base(sys.get_Base ("B2"));
Vector3D OMEGABA2B2 = sys.Angular_Velocity(sys.get_Base ("BA2"),sys.get_Base ("B2"));
Vector3D OMEGAB2 = OMEGABA2__B2  + OMEGABA2B2;
Vector3D dOMEGAB2 =  dOMEGABA2.in_Base(sys.get_Base ("B2")) + sys.dt(OMEGABA2B2) + (OMEGAB2^OMEGABA2B2);

Matrix U2 =  dOMEGAB2.skew() + OMEGAB2.skew()*OMEGAB2.skew();

Vector3D V2 = sys.Velocity_Vector(Frame_abs,A2);
Vector3D dV2 = dV0 + sys.Dt(V2,Frame_abs);

Vector3D DBar2= *sys.new_Vector3D("DBar2",mx2,my2,mz2,"B2");
Vector3D U2d2(U2*DBar2, DBar2.get_Base() );
U2d2.set_System ( &sys );

Vector3D ifi2 = m2*dV2 + U2d2;
Vector3D ini2 = sys.dt(I2*OMEGAB2) + (OMEGAB2 ^ (I2* OMEGAB2)) + (DBar2 ^ dV2);

Vector3D V2__B2 = V2.in_Base(sys.get_Base ("B2"));
Matrix eqf2 = (m2*dV2).transpose() * sys.jacobian(V2.transpose(),dq) + U2d2.transpose()*sys.jacobian(V2__B2.transpose(),dq);
Matrix eqn2 = ini2.transpose() *sys.jacobian(OMEGAB2.transpose(),dq);

Matrix eqB2 =eqf2 + eqn2;


//BAR3
// *****************************************************************************************************
Vector3D OMEGA0__BA3  = OMEGA0.in_Base(sys.get_Base ("BA3"));
Vector3D OMEGA0BA3 = sys.Angular_Velocity(Base_xyz,sys.get_Base ("BA3"));
Vector3D OMEGABA3 = OMEGA0__BA3 + OMEGA0BA3;
Vector3D dOMEGABA3 =  dOMEGA0.in_Base(sys.get_Base ("BA3")) + sys.dt(OMEGA0BA3) + (OMEGABA3^OMEGA0BA3);

Vector3D OMEGABA3__B3  = OMEGABA3.in_Base(sys.get_Base ("B3"));
Vector3D OMEGABA3B3 = sys.Angular_Velocity(sys.get_Base ("BA3"),sys.get_Base ("B3"));
Vector3D OMEGAB3 = OMEGABA3__B3  + OMEGABA3B3;
Vector3D dOMEGAB3 =  dOMEGABA3.in_Base(sys.get_Base ("B3")) + sys.dt(OMEGABA3B3) + (OMEGAB3^OMEGABA3B3);

Matrix U3 =  dOMEGAB3.skew() + OMEGAB3.skew()*OMEGAB3.skew();

Vector3D V3 = sys.Velocity_Vector(Frame_abs,A3);
Vector3D dV3 = dV0 + sys.Dt(V3,Frame_abs);

Vector3D DBar3= *sys.new_Vector3D("DBar3",mx3,my3,mz3,"B3");
Vector3D U3d3(U3*DBar3, DBar3.get_Base() );
U3d3.set_System ( &sys );

Vector3D ifi3 = m3*dV3 + U3d3;
Vector3D ini3 = sys.dt(I3*OMEGAB3) + (OMEGAB3 ^ (I3* OMEGAB3)) + (DBar3 ^ dV3);

Vector3D V3__B3 = V3.in_Base(sys.get_Base ("B3"));
Matrix eqf3 = (m3*dV3).transpose() * sys.jacobian(V3.transpose(),dq) + U3d3.transpose()*sys.jacobian(V3__B3.transpose(),dq);
Matrix eqn3 = ini3.transpose() *sys.jacobian(OMEGAB3.transpose(),dq);

Matrix eqB3 =eqf3 + eqn3;




//BAR4
// *****************************************************************************************************
Vector3D OMEGA0__BA4  = OMEGA0.in_Base(sys.get_Base ("BA4"));
Vector3D OMEGA0BA4 = sys.Angular_Velocity(Base_xyz,sys.get_Base ("BA4"));
Vector3D OMEGABA4 = OMEGA0__BA4 + OMEGA0BA4;
Vector3D dOMEGABA4 =  dOMEGA0.in_Base(sys.get_Base ("BA4")) + sys.dt(OMEGA0BA4) + (OMEGABA4^OMEGA0BA4);

Vector3D OMEGABA4__B4  = OMEGABA4.in_Base(sys.get_Base ("B4"));
Vector3D OMEGABA4B4 = sys.Angular_Velocity(sys.get_Base ("BA4"),sys.get_Base ("B4"));
Vector3D OMEGAB4 = OMEGABA4__B4  + OMEGABA4B4;
Vector3D dOMEGAB4 =  dOMEGABA4.in_Base(sys.get_Base ("B4")) + sys.dt(OMEGABA4B4) + (OMEGAB4^OMEGABA4B4);

Matrix U4 =  dOMEGAB4.skew() + OMEGAB4.skew()*OMEGAB4.skew();

Vector3D V4 = sys.Velocity_Vector(Frame_abs,A4);
Vector3D dV4 =dV0 +  sys.Dt(V4,Frame_abs);

Vector3D DBar4= *sys.new_Vector3D("DBar4",mx4,my4,mz4,"B4");
Vector3D U4d4(U4*DBar4, DBar4.get_Base() );
U4d4.set_System ( &sys );


Vector3D ifi4 = m4*dV4 + U4d4;
Vector3D ini4 = sys.dt(I4*OMEGAB4) + (OMEGAB4 ^ (I4* OMEGAB4)) + (DBar4 ^ dV4);


Vector3D V4__B4 = V4.in_Base(sys.get_Base ("B4"));
Matrix eqf4 = (m4*dV4).transpose() * sys.jacobian(V4.transpose(),dq) + U4d4.transpose()*sys.jacobian(V4__B4.transpose(),dq);
Matrix eqn4 = ini4.transpose() *sys.jacobian(OMEGAB4.transpose(),dq);

Matrix eqB4 =eqf4 + eqn4;





//BAR5
// *****************************************************************************************************
Vector3D OMEGA0__BA5  = OMEGA0.in_Base(sys.get_Base ("BA5"));
Vector3D OMEGA0BA5 = sys.Angular_Velocity(Base_xyz,sys.get_Base ("BA5"));
Vector3D OMEGABA5 = OMEGA0__BA5 + OMEGA0BA5;
Vector3D dOMEGABA5 =  dOMEGA0.in_Base(sys.get_Base ("BA5")) + sys.dt(OMEGA0BA5) + (OMEGABA5^OMEGA0BA5);

Vector3D OMEGABA5__B5  = OMEGABA5.in_Base(sys.get_Base ("B5"));
Vector3D OMEGABA5B5 = sys.Angular_Velocity(sys.get_Base ("BA5"),sys.get_Base ("B5"));
Vector3D OMEGAB5 = OMEGABA5__B5  + OMEGABA5B5;
Vector3D dOMEGAB5 =  dOMEGABA5.in_Base(sys.get_Base ("B5")) + sys.dt(OMEGABA5B5) + (OMEGAB5^OMEGABA5B5);

Matrix U5 =  dOMEGAB5.skew() + OMEGAB5.skew()*OMEGAB5.skew();

Vector3D V5 = sys.Velocity_Vector(Frame_abs,A5);
Vector3D dV5 =dV0 +  sys.Dt(V5,Frame_abs);

Vector3D DBar5= *sys.new_Vector3D("DBar5",mx5,my5,mz5,"B5");
Vector3D U5d5(U5*DBar5, DBar5.get_Base() );
U5d5.set_System ( &sys );


Vector3D ifi5 = m5*dV5 + U5d5;
Vector3D ini5 = sys.dt(I5*OMEGAB5) + (OMEGAB5 ^ (I5* OMEGAB5)) + (DBar5 ^ dV5);


Vector3D V5__B5 = V5.in_Base(sys.get_Base ("B5"));
Matrix eqf5 = (m5*dV5).transpose() * sys.jacobian(V5.transpose(),dq) + U5d5.transpose()*sys.jacobian(V5__B5.transpose(),dq);
Matrix eqn5 = ini5.transpose() *sys.jacobian(OMEGAB5.transpose(),dq);

Matrix eqB5 =eqf5 + eqn5;





//BAR6
// *****************************************************************************************************
Vector3D OMEGA0__BA6  = OMEGA0.in_Base(sys.get_Base ("BA6"));
Vector3D OMEGA0BA6 = sys.Angular_Velocity(Base_xyz,sys.get_Base ("BA6"));
Vector3D OMEGABA6 = OMEGA0__BA6 + OMEGA0BA6;
Vector3D dOMEGABA6 =  dOMEGA0.in_Base(sys.get_Base ("BA6")) + sys.dt(OMEGA0BA6) + (OMEGABA6^OMEGA0BA6);

Vector3D OMEGABA6__B6  = OMEGABA6.in_Base(sys.get_Base ("B6"));
Vector3D OMEGABA6B6 = sys.Angular_Velocity(sys.get_Base ("BA6"),sys.get_Base ("B6"));
Vector3D OMEGAB6 = OMEGABA6__B6  + OMEGABA6B6;
Vector3D dOMEGAB6 =  dOMEGABA6.in_Base(sys.get_Base ("B6")) + sys.dt(OMEGABA6B6) + (OMEGAB6^OMEGABA6B6);

Matrix U6 =  dOMEGAB6.skew() + OMEGAB6.skew()*OMEGAB6.skew();


Vector3D V6 = sys.Velocity_Vector(Frame_abs,A6);
Vector3D dV6 =dV0 +  sys.Dt(V6,Frame_abs);

Vector3D DBar6= *sys.new_Vector3D("DBar6",mx6,my6,mz6,"B6");
Vector3D U6d6(U6*DBar6, DBar6.get_Base() );
U6d6.set_System ( &sys );


Vector3D ifi6 = m6*dV6 + U6d6;
Vector3D ini6 = sys.dt(I6*OMEGAB6) + (OMEGAB6 ^ (I6* OMEGAB6)) + (DBar6 ^ dV6);


Vector3D V6__B6 = V6.in_Base(sys.get_Base ("B6"));
Matrix eqf6 = (m6*dV6).transpose() * sys.jacobian(V6.transpose(),dq) + U6d6.transpose()*sys.jacobian(V6__B6.transpose(),dq);
Matrix eqn6 = ini6.transpose() *sys.jacobian(OMEGAB6.transpose(),dq);

Matrix eqB6 =eqf6 + eqn6;



gravity = DOWN;

Matrix eq = (eqP + eqB1 + eqB2 + eqB3 +eqB4 + eqB5 + eqB6).transpose();

//~ lst new_atom_list_eq, new_exp_list_eq;        
//~ matrix_list_optimize (eq, new_atom_list_eq, new_exp_list_eq);
//~ sys.export_Matrix_C("eq","_eq",eq, new_atom_list_eq, new_exp_list_eq ,ORDER);
//~ sys.export_function_MATLAB("eq", "eq_", eq, new_atom_list_eq, new_exp_list_eq);

vector < symbol_numeric * > Accelerations  = sys.get_Accelerations();

Matrix Qrec=zero_substitution(eq,Accelerations);
lst new_atom_list_Qrec, new_exp_list_Qrec;        
matrix_list_optimize (Qrec, new_atom_list_Qrec, new_exp_list_Qrec);
sys.export_function_MATLAB("Qrec", "Qrec_", Qrec, new_atom_list_Qrec, new_exp_list_Qrec, "q,dq,time,param,inputs");

Matrix Mrec = sys.jacobian(eq.transpose(),ddq,1);

lst new_atom_list_Mrec, new_exp_list_Mrec;        
matrix_list_optimize (Mrec, new_atom_list_Mrec, new_exp_list_Mrec);
sys.export_function_MATLAB("Mrec", "Mrec_", Mrec, new_atom_list_Mrec, new_exp_list_Mrec,"q,time,param");


Matrix MQrec = Matrix("MQrec",1,2,&Mrec,&Qrec);
lst new_atom_list_MQrec, new_exp_list_MQrec;        
matrix_list_optimize (MQrec, new_atom_list_MQrec, new_exp_list_MQrec);
sys.export_function_MATLAB("MQrec", "MQrec_", MQrec, new_atom_list_MQrec, new_exp_list_MQrec, "q,dq,time,param,inputs");



//~ Matrix Mo   = *sys.get_Matrix( "M" );
//~ Matrix Qo   = *sys.get_Matrix( "Q" );
//~ Matrix Deq2 =  -Mo *ddq + Qo;
//~ lst new_atom_list_Deq2, new_exp_list_Deq2;        
//~ matrix_list_optimize (Deq2, new_atom_list_Deq2, new_exp_list_Deq2);
//~ sys.export_function_MATLAB("Deq2", "Deq2_", Deq2, new_atom_list_Deq2, new_exp_list_Deq2);




//cout << unatomize(Qo -Qrec )<<endl;

// ************************************************************************************************
// 	Substituions 
// ************************************************************************************************    
sys.export_init_function_MATLAB();

Matrix Mo   = Mrec;
Matrix Qo   = Qrec;
Matrix MQo  = MQrec;
Matrix Ko   = sys.jacobian(eq.transpose(),M_inertial_parameters);
Matrix WPhio= eq;


Matrix Mnew = Mo;
Matrix Qnew = Qo;
Matrix MQnew = MQo;
Matrix Knew = Ko;
Matrix WPhinew = eq;

lst new_atom_list_Mnew, new_exp_list_Mnew;        
matrix_list_optimize (Mnew, new_atom_list_Mnew, new_exp_list_Mnew);
sys.export_function_MATLAB("Mnew", "Mnew_", Mnew, new_atom_list_Mnew, new_exp_list_Mnew,"q,time,param");

lst new_atom_list_Qnew, new_exp_list_Qnew;        
matrix_list_optimize (Qnew, new_atom_list_Qnew, new_exp_list_Qnew);
sys.export_function_MATLAB("Qnew", "Qnew_", Qnew, new_atom_list_Qnew, new_exp_list_Qnew, "q,dq,time,param,inputs"); 
    
 
lst new_atom_list_MQnew, new_exp_list_MQnew;        
matrix_list_optimize (MQnew, new_atom_list_MQnew, new_exp_list_MQnew);
sys.export_function_MATLAB("MQnew", "MQnew_", MQnew, new_atom_list_MQnew, new_exp_list_MQnew, "q,dq,time,param,inputs");

lst new_atom_list_Knew, new_exp_list_Knew;        
matrix_list_optimize (Knew, new_atom_list_Knew, new_exp_list_Knew);
sys.export_function_MATLAB("Knew", "Knew_", Knew, new_atom_list_Knew, new_exp_list_Knew,"q,dq,ddq,unknowns,time,param,inputs");

lst new_atom_list_WPhinew, new_exp_list_WPhinew;        
matrix_list_optimize (WPhinew, new_atom_list_WPhinew, new_exp_list_WPhinew);
sys.export_function_MATLAB("WPhinew", "WPhinew_", WPhinew, new_atom_list_WPhinew, new_exp_list_WPhinew,"q,dq,ddq,unknowns,time,param,inputs");


cout << "symb = "<< "FULL"<<endl;
cout <<"M atom = " << new_atom_list_Mnew.nops()<<endl;
int ex;
ex = system("python op_counter.py Mnew.m");

cout <<"Q atom = " << new_atom_list_Qnew.nops()<<endl;
ex = system("python op_counter.py Qnew.m");

cout <<"MQ atom = " << new_atom_list_MQnew.nops()<<endl;
ex = system("python op_counter.py MQnew.m");

cout <<"K atom = " << new_atom_list_Knew.nops()<<endl;
ex = system("python op_counter.py Knew.m");

cout <<"WPhi atom = " << new_atom_list_WPhinew.nops()<<endl;
ex = system("python op_counter.py WPhinew.m");

//int ke = system("octave -q mrank_indep.m");
cout<<endl;


vector < symbol_numeric * > v1;


// ele
/*
v1.push_back( &mxP );
v1.push_back( &mz2 );
v1.push_back( &Ixx4 );
v1.push_back( &Iyy4 );
v1.push_back( &Iyy5 );
v1.push_back( &m3 );
v1.push_back( &m6 );
v1.push_back( &Ixx5 );
v1.push_back( &Ixy6 );
v1.push_back( &Ixy3 );
v1.push_back( &Ixy2 );
v1.push_back( &Ixy5 );
v1.push_back( &Ixy4 );
v1.push_back( &Ixy1 );
v1.push_back( &Izz6 );
v1.push_back( &Izz2 );
v1.push_back( &Izz3 );
v1.push_back( &Izz5 );
v1.push_back( &Izz1 );
v1.push_back( &Izz4 );
v1.push_back( &Iyz3 );
v1.push_back( &Iyz5 );
v1.push_back( &Iyz2 );
v1.push_back( &Ixz5 );
v1.push_back( &Iyz6 );
v1.push_back( &Ixz3 );
v1.push_back( &Iyz4 );
v1.push_back( &Iyz1 );
v1.push_back( &Ixz1 );
v1.push_back( &IyzP );
v1.push_back( &Ixz6 );
v1.push_back( &IxzP );
v1.push_back( &Ixz2 );
v1.push_back( &Ixz4 );
v1.push_back( &mx2 );
v1.push_back( &mx6 );
v1.push_back( &my6 );
v1.push_back( &mx3 );
v1.push_back( &my2 );
v1.push_back( &mx1 );
v1.push_back( &my4 );
v1.push_back( &mx5 );
v1.push_back( &mx4 );
v1.push_back( &Ixx2 );
v1.push_back( &Iyy2 );
v1.push_back( &mz4 );
v1.push_back( &my5 );
v1.push_back( &my3 );
v1.push_back( &my1 );
v1.push_back( &mz5 );
v1.push_back( &Iyy3 );
v1.push_back( &Ixx3 );
v1.push_back( &IxyP );
v1.push_back( &IxxP );
v1.push_back( &Iyy6 );
v1.push_back( &IyyP );
v1.push_back( &Ixx6 );
v1.push_back( &mzP );
v1.push_back( &m1 );
v1.push_back( &Ixx1 );
v1.push_back( &Iyy1 );
v1.push_back( &myP );
v1.push_back( &mz3 );
v1.push_back( &IzzP );
v1.push_back( &m2 );
v1.push_back( &mz6 );
v1.push_back( &m5 );
v1.push_back( &mz1 );
v1.push_back( &m4 );
v1.push_back( &mP );
//*/


//add
/*
v1.push_back( &Iyy5 );
v1.push_back( &Ixx2 );
v1.push_back( &Ixx6 );
v1.push_back( &Ixx5 );
v1.push_back( &Iyy3 );
v1.push_back( &Iyy6 );
v1.push_back( &Iyy2 );
v1.push_back( &Ixx4 );
v1.push_back( &Iyy4 );
v1.push_back( &Ixx3 );
v1.push_back( &mxP );
v1.push_back( &Ixy6 );
v1.push_back( &Ixy3 );
v1.push_back( &Ixy1 );
v1.push_back( &Ixy4 );
v1.push_back( &Ixy2 );
v1.push_back( &Ixy5 );
v1.push_back( &Izz5 );
v1.push_back( &Izz3 );
v1.push_back( &Izz6 );
v1.push_back( &Izz1 );
v1.push_back( &Izz4 );
v1.push_back( &Ixz2 );
v1.push_back( &Iyz6 );
v1.push_back( &Iyz2 );
v1.push_back( &Ixz5 );
v1.push_back( &Iyz3 );
v1.push_back( &myP );
v1.push_back( &Izz2 );
v1.push_back( &Ixz3 );
v1.push_back( &IyzP );
v1.push_back( &Iyz4 );
v1.push_back( &Iyz1 );
v1.push_back( &Ixz1 );
v1.push_back( &IxzP );
v1.push_back( &Ixz6 );
v1.push_back( &Iyz5 );
v1.push_back( &Ixz4 );
v1.push_back( &mx2 );
v1.push_back( &my2 );
v1.push_back( &my6 );
v1.push_back( &mx4 );
v1.push_back( &my3 );
v1.push_back( &mz3 );
v1.push_back( &mz5 );
v1.push_back( &my5 );
v1.push_back( &my4 );
v1.push_back( &my1 );
v1.push_back( &mx5 );
v1.push_back( &mx3 );
v1.push_back( &IxyP );
v1.push_back( &mx6 );
v1.push_back( &Iyy1 );
v1.push_back( &m1 );
v1.push_back( &IxxP );
v1.push_back( &IyyP );
v1.push_back( &Ixx1 );
v1.push_back( &m6 );
v1.push_back( &mz4 );
v1.push_back( &m2 );
v1.push_back( &mx1 );
v1.push_back( &mzP );
v1.push_back( &m3 );
v1.push_back( &mz6 );
v1.push_back( &mz2 );
v1.push_back( &m5 );
v1.push_back( &mz1 );
v1.push_back( &m4 );
v1.push_back( &IzzP );
v1.push_back( &mP );
//*/

//qr
/*
v1.push_back( &mP );
v1.push_back( &m6 );
v1.push_back( &m2 );
v1.push_back( &Ixx1 );
v1.push_back( &Ixx3 );
v1.push_back( &m4 );
v1.push_back( &Ixx5 );
v1.push_back( &Ixx6 );
v1.push_back( &Ixx2 );
v1.push_back( &Izz5 );
v1.push_back( &Iyy3 );
v1.push_back( &Ixx4 );
v1.push_back( &Izz6 );
v1.push_back( &Iyy5 );
v1.push_back( &Izz2 );
v1.push_back( &Izz3 );
v1.push_back( &Ixy6 );
v1.push_back( &Iyy1 );
v1.push_back( &Ixy2 );
v1.push_back( &Iyy6 );
v1.push_back( &Iyz5 );
v1.push_back( &Iyz3 );
v1.push_back( &Iyy4 );
v1.push_back( &Iyy2 );
v1.push_back( &Izz1 );
v1.push_back( &Iyz2 );
v1.push_back( &Iyz6 );
v1.push_back( &Ixy4 );
v1.push_back( &Ixy3 );
v1.push_back( &Iyz1 );
v1.push_back( &m1 );
v1.push_back( &Ixy5 );
v1.push_back( &Izz4 );
v1.push_back( &Ixz6 );
v1.push_back( &Ixz3 );
v1.push_back( &Ixz2 );
v1.push_back( &Ixz5 );
v1.push_back( &mz3 );
v1.push_back( &Iyz4 );
v1.push_back( &Ixy1 );
v1.push_back( &mz5 );
v1.push_back( &Ixz1 );
v1.push_back( &Ixz4 );
v1.push_back( &m5 );
v1.push_back( &mx6 );
v1.push_back( &mx3 );
v1.push_back( &mz4 );
v1.push_back( &mz2 );
v1.push_back( &m3 );
v1.push_back( &mx2 );
v1.push_back( &mx5 );
v1.push_back( &mz6 );
v1.push_back( &mz1 );
v1.push_back( &mx4 );
v1.push_back( &mx1 );
v1.push_back( &my5 );
v1.push_back( &my1 );
v1.push_back( &my3 );
v1.push_back( &my6 );
v1.push_back( &my2 );
v1.push_back( &my4 );
v1.push_back( &IyyP );
v1.push_back( &mzP );
v1.push_back( &mxP );
v1.push_back( &myP );
v1.push_back( &IzzP );
v1.push_back( &IxxP );
v1.push_back( &IyzP );
v1.push_back( &IxyP );
v1.push_back( &IxzP );
//*/


//L1
//*
v1.push_back( &Iyy4 );
v1.push_back( &Iyy1 );
v1.push_back( &Ixx1 );
v1.push_back( &Ixx4 );
v1.push_back( &Ixx2 );
v1.push_back( &Iyy2 );
v1.push_back( &Ixx3 );
v1.push_back( &Ixx5 );
v1.push_back( &Iyy3 );
v1.push_back( &Iyy5 );
v1.push_back( &Iyy6 );
v1.push_back( &Ixx6 );
v1.push_back( &Ixy4 );
v1.push_back( &Ixy1 );
v1.push_back( &Ixy6 );
v1.push_back( &IxzP );
v1.push_back( &IyzP );
v1.push_back( &Ixy2 );
v1.push_back( &Ixy5 );
v1.push_back( &Ixy3 );
v1.push_back( &IxyP );
v1.push_back( &Izz3 );
v1.push_back( &Izz6 );
v1.push_back( &Izz4 );
v1.push_back( &Izz5 );
v1.push_back( &Izz1 );
v1.push_back( &Izz2 );
v1.push_back( &Iyz3 );
v1.push_back( &Iyz2 );
v1.push_back( &Iyz5 );
v1.push_back( &Ixz2 );
v1.push_back( &Ixz1 );
v1.push_back( &Iyz4 );
v1.push_back( &Ixz5 );
v1.push_back( &Iyz1 );
v1.push_back( &Ixz4 );
v1.push_back( &Iyz6 );
v1.push_back( &Ixz6 );
v1.push_back( &Ixz3 );
v1.push_back( &mx6 );
v1.push_back( &mx2 );
v1.push_back( &mx1 );
v1.push_back( &mx4 );
v1.push_back( &my2 );
v1.push_back( &my5 );
v1.push_back( &my4 );
v1.push_back( &my6 );
v1.push_back( &my3 );
v1.push_back( &my1 );
v1.push_back( &mx5 );
v1.push_back( &mx3 );
v1.push_back( &IyyP );
v1.push_back( &IxxP );
v1.push_back( &myP );
v1.push_back( &mxP );
v1.push_back( &IzzP );
v1.push_back( &mzP );
v1.push_back( &mz5 );
v1.push_back( &mz6 );
v1.push_back( &mz3 );
v1.push_back( &mz2 );
v1.push_back( &mz4 );
v1.push_back( &mz1 );
v1.push_back( &m5 );
v1.push_back( &m3 );
v1.push_back( &m6 );
v1.push_back( &m2 );
v1.push_back( &m4 );
v1.push_back( &m1 );
v1.push_back( &mP );
//*/



//~ lst kaka;
//~ kaka = {IzzP,IxxP,IyyP,IxzP};

//~ vector < symbol_numeric * > v3;
//~ cout <<"kaka= " << ex_to<symbol>(kaka[1])<<endl;
//~ symbol_numeric sym_j;
//~ sym_j = ex_to<symbol>(kaka[1]);
//~ v3.push_back( &sym_j );
//~ Matrix kakaka = zero_substitution(Mo,v3);

vector < symbol_numeric * > v2; 
for (int k = 0;k<v1.size(); k++) {
v2.push_back( v1[k]);

    
Matrix Mnew = zero_substitution(Mo,v2);
Matrix Qnew = zero_substitution(Qo,v2);
Matrix MQnew = zero_substitution(MQo,v2);
//Matrix Knew= zero_substitution(Ko,v2);
Matrix WPhinew= zero_substitution(WPhio,v2);

lst new_atom_list_Mnew, new_exp_list_Mnew;        
matrix_list_optimize (Mnew, new_atom_list_Mnew, new_exp_list_Mnew);
sys.export_function_MATLAB("Mnew", "Mnew_", Mnew, new_atom_list_Mnew, new_exp_list_Mnew,"q,time,param");

lst new_atom_list_Qnew, new_exp_list_Qnew;        
matrix_list_optimize (Qnew, new_atom_list_Qnew, new_exp_list_Qnew);
sys.export_function_MATLAB("Qnew", "Qnew_", Qnew, new_atom_list_Qnew, new_exp_list_Qnew, "q,dq,time,param,inputs"); 
    
 
lst new_atom_list_MQnew, new_exp_list_MQnew;        
matrix_list_optimize (MQnew, new_atom_list_MQnew, new_exp_list_MQnew);
sys.export_function_MATLAB("MQnew", "MQnew_", MQnew, new_atom_list_MQnew, new_exp_list_MQnew, "q,dq,time,param,inputs");

//~ lst new_atom_list_Knew, new_exp_list_Knew;        
//~ matrix_list_optimize (Knew, new_atom_list_Knew, new_exp_list_Knew);
//~ sys.export_function_MATLAB("Knew", "Knew_", Knew, new_atom_list_Knew, new_exp_list_Knew,"q,dq,ddq,unknowns,time,param,inputs");

lst new_atom_list_WPhinew, new_exp_list_WPhinew;        
matrix_list_optimize (WPhinew, new_atom_list_WPhinew, new_exp_list_WPhinew);
sys.export_function_MATLAB("WPhinew", "WPhinew_", WPhinew, new_atom_list_WPhinew, new_exp_list_WPhinew,"q,dq,ddq,unknowns,time,param,inputs");

  
int e;

cout << "symb = "<< v1[k]->get_name()<<endl;

cout <<"M atom = " << new_atom_list_Mnew.nops()<<endl;
e = system("python op_counter.py Mnew.m");

cout <<"Q atom = " << new_atom_list_Qnew.nops()<<endl;
e = system("python op_counter.py Qnew.m");

cout <<"MQ atom = " << new_atom_list_MQnew.nops()<<endl;
e = system("python op_counter.py MQnew.m");

//cout <<"K atom = " << new_atom_list_Knew.nops()<<endl;
//e = system("python op_counter.py Knew.m");

cout <<"WPhi atom = " << new_atom_list_WPhinew.nops()<<endl;
ex = system("python op_counter.py WPhinew.m");

//e = system("octave -q mrank_indep.m");

cout<<endl;
} 







// ************************************************************************************************
// 	Export Point, Base and Frame Diagrams 
// ************************************************************************************************
#ifdef GRAPHVIZ 
	cout << "Export Point, Base and Frame Diagrams" << endl;

	sys.export_Graphviz_dot (  );

	//Generate eps figure
    	system("dot -Tps   base_diagram.dot -o plain_base_diagram.eps");
    	system("latex base_diagram.tex");
    	system("dvips base_diagram.dvi -o base_diagram.eps");
	//Generate figure eps
    	system("dot -Tps   point_diagram.dot -o plain_point_diagram.eps");
     	system("latex point_diagram.tex");
    	system("dvips point_diagram.dvi -o point_diagram.eps");
	//Generate eps figure
    	system("dot -Tps   frame_diagram.dot -o plain_frame_diagram.eps");
    	system("latex frame_diagram.tex");
    	system("dvips base_diagram.dvi -o base_diagram.eps");
#endif



// ************************************************************************************************
//	Export MATLAB environment vector 
// ************************************************************************************************

	//~ cout << "Export ENVIRONMENT file " << endl;

	//~ sys.export_environment_m (  );


// ************************************************************************************************
//	Export config.ini file
// ************************************************************************************************

	cout << "Export config.ini file " << endl;

	sys.export_config_ini (  );

// ************************************************************************************************
//	Export C++ code for Openscenegraph
// ************************************************************************************************

	cout << "Export C++ code for Openscenegraph." << endl;

	sys.export_open_scene_graph ( );

// ************************************************************************************************
//	Export State File
// ************************************************************************************************

	cout << "Export State File" << endl;

    	lst state;

//     	state = x,*dx,*ddx,y,*dy,*ddy,z,*dz,*ddz,a,*da,*dda,b,*dB,*ddB,c,*dc,*ddc,r,*dr,*ddr,t1,*dt1,*ddt1,t2,*dt2,*ddt2,t3,*dt3,*ddt3 ;
    	state = {x,*dx,*ddx,y,*dy,*ddy,z,*dz,*ddz,a,*da,*dda,b,*dB,*ddB,c,*dc,*ddc,
		a1,*da1,*dda1,b1,*dB1,*ddB1,s1,*ds1,*dds1,
		a2,*da2,*dda2,b2,*dB2,*ddB2,s2,*ds2,*dds2,
		a3,*da3,*dda3,b3,*dB3,*ddB3,s3,*ds3,*dds3,
		a4,*da4,*dda4,b4,*dB4,*ddB4,s4,*ds4,*dds4,
		a5,*da5,*dda5,b5,*dB5,*ddB5,s5,*ds5,*dds5,
		a6,*da6,*dda6,b6,*dB6,*ddB6,s6,*ds6,*dds6};

	sys.export_write_data_file_C(state);


// ************************************************************************************************
//	Export grphics.gnuplot
// ************************************************************************************************

	cout << "Export GNUPLOT file" << endl;
        sys.export_gnuplot ( state );

// ************************************************************************************************
//	Summary
// ************************************************************************************************

                                     	cout << "" << endl;
                                     	cout << "***********************************************" << endl;
                                     	cout << "** COMPILED WITH OPTIONS                     **" << endl;
                                     	cout << "***********************************************" << endl;
if ( METHOD == LAGRANGE)            {	cout << "** Dynamic equations ===> LAGRANGE           **" << endl;	}
else 	if ( METHOD == VIRTUAL_POWER) {	cout << "** Dynamic equations ===> VIRTUAL_POWER      **" << endl;	}
if ( ORDER == CMO)                  {	cout << "** Matrix Order      ===> Col_MO             **" << endl;	}
else 	if ( ORDER == RMO)            {	cout << "** Matrix Order      ===> Row_MO             **" << endl;	}
if ( MAPLE == MAPLE_OFF)            {	cout << "** Maple             ===> OFF                **" << endl;	}
else 	if ( MAPLE == MAPLE_ON)       {	cout << "** Maple             ===> ON                 **" << endl;	}
                                     	cout << "***********************************************" << endl;



// ************************************************************************************************
//	END program
// ************************************************************************************************

return 0;

}


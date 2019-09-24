/*
export PKG_CONFIG_PATH=`pwd`/../../../lib/pkgconfig
export LD_LIBRARY_PATH=`pwd`/../../../lib
g++ -o main_train_proto main_train_proto.cc `pkg-config --cflags --libs lib_3d_mec_ginac-1.1 ginac gsl`
./main_train_proto DOWN NO
*/

#include <fstream>
#include "lib_3d_mec_ginac/lib_3d_mec_ginac.h"
#include <math.h>
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

using namespace std;
	
void printError(const char* arg){	printf("%s\n", arg);}	

#ifdef PROCEDURE
int C_EXPORT_AS_PROCEDURE=1;
#else
int C_EXPORT_AS_PROCEDURE=0;
#endif

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

int main(int argc, char *argv[]) {

// *****************************************************************************************************************	
cout << " " << endl;
cout << "************************************************" << endl;
cout << "*             TRAIN-PROTOTYPE                  *" << endl;
cout << "************************************************" << endl;
cout << " " << endl;
system("date");
cout << " " << endl;
// *****************************************************************************************************************
	
if (argc!=3){ printf("Error: The program %s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\n",argv[0]);	exit(1); }
	
if (0==strcmp(argv[1],"DOWN")){ gravity=DOWN; cout << "DOWN" << endl;}
else{
	if (0==strcmp(argv[1],"UP")){	gravity=UP; cout << "UP" << endl;	}
	else	{		printf("Error: The program %s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\n",argv[0]);		exit(1);	}
}

if (0==strcmp(argv[2],"YES")){ atomization=YES; cout << "YES" << endl;}
else{
	if (0==strcmp(argv[2],"NO")){ atomization=NO; cout << "NO" << endl;}
	else	{ printf("Error: The program %s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\n",argv[0]);	exit(1);}
}

double integration_time=strtod(argv[1], NULL);
double delta_t= strtod(argv[2], NULL);
long int k,steps;
	
printf("integration_time %g delta_t %g\n", integration_time, delta_t);

// SYSTEM DEFINITION
// ************************************************************************************************
	System sys(&printError);cout << "" << endl;
// ************************************************************************************************
// ************************************************************************************************
// 3d_mec MODEL - PROTOTYPE ARESSE_TRAIN
// ************************************************************************************************
// Roberto Yoldi April-2012

#ifdef LAG	
	# define METHOD LAGRANGE
#endif

#ifdef V_P
	# define METHOD VIRTUAL_POWER
#endif

// GENERALISED COORDINATES DEFINITION
// ************************************************************************************************
// Independent
// ------------------------------------------------------------------------------------------------

symbol_numeric a1    = *sys.new_Coordinate  ("a1","da1","dda1", 0.0 , 0.0 , 0.0); // Gyroscope (solid 1) vs Inertial reference rotation. ROLL
symbol_numeric a1_0  = *sys.new_Parameter   ("a1_0"		,0.0);
symbol_numeric da1_0 = *sys.new_Parameter   ("da1_0"	,0.0);
symbol_numeric *da1  =  sys.get_Velocity    ("da1");
symbol_numeric *dda1 =  sys.get_Acceleration("dda1");

symbol_numeric a2    = *sys.new_Coordinate  ("a2","da2","dda2", 0.0 , 0.0 , 0.0); // Road-Chassis (Solid 2) vs Gyroscope rotation. PITH
symbol_numeric a2_0  = *sys.new_Parameter   ("a2_0"		,0.0);
symbol_numeric da2_0 = *sys.new_Parameter   ("da2_0"	,0.0);
symbol_numeric *da2  =  sys.get_Velocity    ("da2");
symbol_numeric *dda2 =  sys.get_Acceleration("dda2");

symbol_numeric a5    = *sys.new_Coordinate  ("a5","da5","dda5", 0.0 , 0.0 , 0.0); // Wheel (solid 5) rotation vs Wheel-Chassis.
symbol_numeric a5_0  = *sys.new_Parameter   ("a5_0"		,0.0);
symbol_numeric da5_0 = *sys.new_Parameter   ("da5_0"	,0.0);
symbol_numeric *da5  =  sys.get_Velocity    ("da5");
symbol_numeric *dda5 =  sys.get_Acceleration("dda5");

symbol_numeric a6    = *sys.new_Coordinate  ("a6","da6","dda6", 0.0 , 0.0 , 0.0); // Mass (solid 6) rotation vs Road-Chassis rotation.
symbol_numeric a6_0  = *sys.new_Parameter   ("a6_0"		,0.0);
symbol_numeric da6_0 = *sys.new_Parameter   ("da6_0"	,0.0);
symbol_numeric *da6  =  sys.get_Velocity    ("da6");
symbol_numeric *dda6 =  sys.get_Acceleration("dda6");

# ifdef SLIP

	// Independent ===> coord a3 ==indep
	// ------------------------------------------------------------------------------------------------
symbol_numeric a3    = *sys.new_Coordinate  ("a3","da3","dda3", 0.0 , 0.0 , 0.0); // Road (solid 3) rotation vs Road-Chassis.
symbol_numeric a3_0  = *sys.new_Parameter   ("a3_0"		,0.0);
symbol_numeric da3_0 = *sys.new_Parameter   ("da3_0"	,0.0);
symbol_numeric *da3  =  sys.get_Velocity    ("da3");
symbol_numeric *dda3 =  sys.get_Acceleration("dda3");

lst coord_indep_init; coord_indep_init	= (a1-a1_0),(a2-a2_0),(a5-a5_0),(a6-a6_0),(a3-a3_0);
lst vel_indep_init; vel_indep_init	= (*da1-da1_0),(*da2-da2_0),(*da5-da5_0),(*da6-da6_0),(*da3-da3_0);
//lst vel_indep_init;   vel_indep_init		= -da1_0,-da2_0,-da5_0,-da6_0,-da3_0;

# else

lst coord_indep_init; coord_indep_init	= (a1-a1_0),(a2-a2_0),(a5-a5_0),(a6-a6_0);
lst vel_indep_init; vel_indep_init	= (*da1-da1_0),(*da2-da2_0),(*da5-da5_0),(*da6-da6_0);
//lst vel_indep_init;   vel_indep_init		= -da1_0,-da2_0,-da5_0,-da6_0;

	// Dependent ===> coord a3 ==dep
	// ------------------------------------------------------------------------------------------------
symbol_numeric a3    = *sys.new_Coordinate  ("a3","da3","dda3", 0.0 , 0.0 , 0.0); // Road (solid 3) rotation vs Road-Chassis.
symbol_numeric *da3  =  sys.get_Velocity    ("da3");
symbol_numeric *dda3 =  sys.get_Acceleration("dda3");

#endif

// Dependent
// ------------------------------------------------------------------------------------------------
symbol_numeric a4    = *sys.new_Coordinate  ("a4","da4","dda4", 0.0 , 0.0 , 0.0); // Wheel-Chassis (solid 4) vs Road-Chassis rotation.
symbol_numeric *da4  =  sys.get_Velocity    ("da4");
symbol_numeric *dda4 =  sys.get_Acceleration("dda4");

symbol_numeric a7    = *sys.new_Coordinate  ("a7","da7","dda7", 0.0 , 0.0 , 0.0); // Motor rotation. Rotor vs. Stator.
symbol_numeric *da7  =  sys.get_Velocity    ("da7");
symbol_numeric *dda7 =  sys.get_Acceleration("dda7");

// ------------------------------------------------------------------------------------------------
	Matrix q 			 		= sys.Coordinates();
	Matrix dq 		 		= sys.Velocities();
	Matrix ddq 		 		= sys.Accelerations();

  vector < symbol_numeric * > Coordinates 		= sys.get_Coordinates();
  vector < symbol_numeric * > Velocities 			= sys.get_Velocities();
  vector < symbol_numeric * > Accelerations		= sys.get_Accelerations();

// KINEMATICAL PARAMETERS. STRUCTURE DIDMENSIONS & KINEMATIC CONSTANTS
// ************************************************************************************************
// Data from CAD
	symbol_numeric Sp	= *sys.new_Parameter("Sp",0.0900);
	symbol_numeric Lp	= *sys.new_Parameter("Lp",0.4325);
	symbol_numeric Ln	= *sys.new_Parameter("Ln",0.3848);
	symbol_numeric Ww	= *sys.new_Parameter("Ww",0.6500);
	symbol_numeric W 	= *sys.new_Parameter("W" ,0.3650);
	symbol_numeric Hn	= *sys.new_Parameter("Hn",0.6100);
	symbol_numeric Hi	= *sys.new_Parameter("Hi",0.2626);
	symbol_numeric Hs	= *sys.new_Parameter("Hs",0.2294);
	symbol_numeric Hb	= *sys.new_Parameter("Hb",0.4825);
	symbol_numeric Rw 	= *sys.new_Parameter("Rw",0.0750);
	symbol_numeric Rr 	= *sys.new_Parameter("Rr",0.0750);
	symbol_numeric Rx 	= *sys.new_Parameter("Rx",0.1550);
	symbol_numeric Bx 	= *sys.new_Parameter("Bx",0.0570);
	symbol_numeric Mx 	= *sys.new_Parameter("Mx",0.2318);
	symbol_numeric Si 	= *sys.new_Parameter("Si",0.4000);
	symbol_numeric Ss 	= *sys.new_Parameter("Ss",0.3427);
	ex     Hm	= Hb - Rw - Rr;

	// Lm, Zm posicion del eje del motor. Respecto eje vertical por centro de la cruz.
	symbol_numeric Lm	= *sys.new_Parameter("Lm",0.3000); //**** PONER VALORES DEL CAD CUANDO ESTEN DISPONIBLES ****
	symbol_numeric Zm	= *sys.new_Parameter("Zm",0.1000); //**** PONER VALORES DEL CAD CUANDO ESTEN DISPONIBLES ****

	symbol_numeric SR	= *sys.new_Parameter("SR",0.020);
	symbol_numeric VS	= *sys.new_Parameter("VS",1.000);

	symbol_numeric af1 	= *sys.new_Parameter("af1",3.14159265358979/12);
	symbol_numeric af2 	= *sys.new_Parameter("af2",3.14159265358979/4);

	symbol_numeric W1 	= *sys.new_Parameter("W1",3.14159265358979/4);
	symbol_numeric W2 	= *sys.new_Parameter("W2",3.14159265358979/2);
	symbol_numeric W3 	= *sys.new_Parameter("W3",0.0);
	symbol_numeric W4 	= *sys.new_Parameter("W4",3.14159265358979);
	symbol_numeric W5 	= *sys.new_Parameter("W5",3.14159265358979);

// Dynamic parameters

//	symbol_numeric  K_C = *sys.new_Parameter("K_C",1.0);
	symbol_numeric  Cvis_a1 = *sys.new_Parameter("Cvis_a1",1.0*1.0);
	symbol_numeric  Cvis_a2 = *sys.new_Parameter("Cvis_a2",1.0*1.0);
	symbol_numeric  Cvis_a3 = *sys.new_Parameter("Cvis_a3",1.0*1.0);
//	symbol_numeric  Cvis_a4 = *sys.new_Parameter("Cvis_a4",1.0*1.0);
	symbol_numeric  Cvis_a5 = *sys.new_Parameter("Cvis_a5",1.0*1.0);
	symbol_numeric  Cvis_a6 = *sys.new_Parameter("Cvis_a6",50.0*1.0);
	symbol_numeric  Cvis_a7 = *sys.new_Parameter("Cvis_a7",1.0*1.0);

//	symbol_numeric  K_K = *sys.new_Parameter("K_K",1.0);
	symbol_numeric Ki		= *sys.new_Parameter("Ki",161000*1.0);
	symbol_numeric Li0	= *sys.new_Parameter("Li0",0.0500);
	symbol_numeric Li		= *sys.new_Parameter("Li",0.0400);

	symbol_numeric Ks		= *sys.new_Parameter("Ks",161000*1.0);
	symbol_numeric Ls0	= *sys.new_Parameter("Ls0",0.0500);
	symbol_numeric Ls		= *sys.new_Parameter("Ls",0.0400);

	symbol_numeric Kt		= *sys.new_Parameter("Kt",161000*0.1);
	symbol_numeric L0		= *sys.new_Parameter("L0",0.0500);
// L = L0 - ((mx6 * g) / (k * (Ln + Ss)));
	symbol_numeric L		= *sys.new_Parameter("L",(0.0500 - (((1.1543302E+01 * (+1.6951865E-03 -	(-0.3848))) * 9.8) / (161000 * (0.3848 + 0.3427)))));

	symbol_numeric Ds		= *sys.new_Parameter("Ds",0.3200);
//Di = Hi + Hs - Ds - L;
	symbol_numeric Di		= *sys.new_Parameter("Di",(0.2294 + 0.2626 - 0.3200 - (0.0500 - (((1.1543302E+01 * (+1.6951865E-03 -	(-0.3848))) * 9.8) / (161000 * (0.3848 + 0.3427))))));

	symbol_numeric Ratio		= *sys.new_Parameter("Ratio",7.0);

// ************************************************************************************************
// KINEMATICS
// ************************************************************************************************

// Bases
// ------------------------------------------------------------------------------------------------
 	sys.new_Base("B1","xyz",0,1,0, a1);
 	sys.new_Base("B2","B1" ,1,0,0, a2);
 	sys.new_Base("B3","B2" ,1,0,0, a3);
 	sys.new_Base("B4","B2" ,0,1,0, a4);
 	sys.new_Base("B5","B4" ,1,0,0, a5);
 	sys.new_Base("B6","B2" ,0,1,0, a6);
 	sys.new_Base("B7","B4" ,0,0,1, a7);

// Vectors
// ------------------------------------------------------------------------------------------------
	Vector3D OO_OO = *sys.new_Vector3D("OO_OO",0.0,0.0,0.0,"xyz");
	Vector3D OO_O1 = *sys.new_Vector3D("OO_O1",0.0,0.0,0.0,"xyz");
	Vector3D O1_O2 = *sys.new_Vector3D("O1_O2",0.0,0.0,+Sp,"B1");
	Vector3D O2_O3 = *sys.new_Vector3D("O2_O3",+Rx,0.0,-(Sp+Hb),"B2");
	Vector3D O2_O4 = *sys.new_Vector3D("O2_O4",-Ln,0.0,-(Sp+Hi),"B2");
	Vector3D O4_O5 = *sys.new_Vector3D("O4_O5",(Ln+Rx),0.0,-(Hm-Hi),"B4");
	Vector3D O2_O6 = *sys.new_Vector3D("O2_O6",-Ln,0.0,+(Hs-Sp),"B2");
	Vector3D O4_O7 = *sys.new_Vector3D("O4_O7",(Ln-Lm),Zm,-(Hm-Hi),"B4");

// POINTS AT SOLID #

	Vector3D O2_A2 	= *sys.new_Vector3D("O2_A2",-Lp,0.0,-(Sp+Hn),"B2");
	Vector3D A2_Z2	= *sys.new_Vector3D("A2_Z2",+(Lp+Lp),0.0,0.0,"B2");
	Vector3D A2_M2 	= *sys.new_Vector3D("A2_M2",+(Si+Lp),0.0,0.0,"B2");
	Vector3D O3_A3 	= *sys.new_Vector3D("O3_A3",-(Bx+Rx),0.0,0.0,"B3");
	Vector3D O4_Z4 	= *sys.new_Vector3D("O4_Z4",+(Lp+Ln),0.0,0.0,"B4");
	Vector3D O4_M4 	= *sys.new_Vector3D("O4_M4",+(Si+Ln),0.0,0.0,"B4");
	Vector3D O4_D4 	= *sys.new_Vector3D("O4_D4",+(Ss+Ln),0.0,0.0,"B4");
	Vector3D D4_MS4 = *sys.new_Vector3D("D4_MS4",0.0,0.0,+Di,"B4");
	Vector3D O5_A5 	= *sys.new_Vector3D("O5_A5",-(Mx+Rx),0.0,0.0,"B5");
	Vector3D O6_Z6 	= *sys.new_Vector3D("O6_Z6",+(Lp+Ln),0.0,0.0,"B6");
	Vector3D O6_D6 	= *sys.new_Vector3D("O6_D6",+(Ss+Ln),0.0,0.0,"B6");
	Vector3D D6_MS6 = *sys.new_Vector3D("D6_MS6",0.0,0.0,-Ds,"B6");

	Vector3D O3_PG3 = *sys.new_Vector3D("O3_PG3",0.0,0.0,+Rr,"B2");
	Vector3D O5_PG5 = *sys.new_Vector3D("O5_PG5",0.0,0.0,-Rw,"B4");

	Vector3D B2_010 = *sys.new_Vector3D("B2_010",0.0,1.0,0.0,"B2");
	Vector3D B2_001 = *sys.new_Vector3D("B2_001",0.0,0.0,1.0,"B2");

// Points
// ------------------------------------------------------------------------------------------------
	Point * O1 = sys.new_Point("O1","O",&OO_O1);
	Point * O2 = sys.new_Point("O2","O1",&O1_O2);
	Point * O3 = sys.new_Point("O3","O2",&O2_O3);
	Point * O4 = sys.new_Point("O4","O2",&O2_O4);
	Point * O5 = sys.new_Point("O5","O4",&O4_O5);
	Point * O6 = sys.new_Point("O6","O2",&O2_O6);
	Point * O7 = sys.new_Point("O7","O4",&O4_O7);

	Point * A2 = sys.new_Point("A2","O2",&O2_A2);
	Point * M2 = sys.new_Point("M2","A2",&A2_M2);	//Points M2 & M4 Spring assy.
	Point * M4 = sys.new_Point("M4","O4",&O4_M4);
	Point * D4 = sys.new_Point("D4","O4",&O4_D4);
	Point * MS4 = sys.new_Point("MS4","D4",&D4_MS4);	//Points MS4 & MS6 Spring assy.
	Point * D6 = sys.new_Point("D6","O6",&O6_D6);
	Point * MS6 = sys.new_Point("MS6","D6",&D6_MS6);

	Point * PG3 = sys.new_Point("PG3","O3",&O3_PG3);
	Point * PG5 = sys.new_Point("PG5","O5",&O5_PG5);

// Define Frames
// ------------------------------------------------------------------------------------------------

	Frame_abs -> set_scale(0.1);

	Frame * R1 = sys.new_Frame("R1","O1","B1", 0.1);
	Frame * R2 = sys.new_Frame("R2","O2","B2", 0.1);
	Frame * R3 = sys.new_Frame("R3","O3","B3", 0.1);
	Frame * R4 = sys.new_Frame("R4","O4","B4", 0.1);
	Frame * R5 = sys.new_Frame("R5","O5","B5", 0.1);
	Frame * R6 = sys.new_Frame("R6","O6","B6", 0.1);
	Frame * R7 = sys.new_Frame("R7","O7","B7", 0.1);

//	Solid * System::new_Solid ( string name , string s_Point , string s_Base, string s_file,  numeric r, numeric g, numeric b, numeric alpha ){


/*
	Solid * S1 = sys.new_Solid("S1","O1","B1","./solids/sol1.osg",1,0,0,0.8);
	Solid * S2 = sys.new_Solid("S2","O2","B2","./solids/sol2.osg",0,1,0,0.5);
	Solid * S3 = sys.new_Solid("S3","O3","B3","./solids/sol3.osg",0,0,1,1.0);
	Solid * S4 = sys.new_Solid("S4","O4","B4","./solids/sol4.osg",1,1,0,0.2);
	Solid * S5 = sys.new_Solid("S5","O5","B5","./solids/sol5.osg",1,0,1,1.0);
	Solid * S6 = sys.new_Solid("S6","O6","B6","./solids/sol6.osg",0,1,1,0.2);
	Solid * S7 = sys.new_Solid("S7","O7","B7","./solids/sol7.osg",1,1,1,1.0);
*/




// Absolute position vectors
// ------------------------------------------------------------------------------------------------
//	Vector3D OO_O1 = sys.Position_Vector("O","O1");
	Vector3D OO_O2 = sys.Position_Vector("O","O2");
	Vector3D OO_O3 = sys.Position_Vector("O","O3");
	Vector3D OO_O4 = sys.Position_Vector("O","O4");
	Vector3D OO_O5 = sys.Position_Vector("O","O5");
	Vector3D OO_O6 = sys.Position_Vector("O","O6");
	Vector3D OO_O7 = sys.Position_Vector("O","O7");

	Vector3D OO_M2 = sys.Position_Vector("O","M2");
	Vector3D OO_M4 = sys.Position_Vector("O","M4");
	Vector3D OO_MS4 = sys.Position_Vector("O","MS4");
	Vector3D OO_MS6 = sys.Position_Vector("O","MS6");

	Vector3D OO_PG3 = sys.Position_Vector("O","PG3");
	Vector3D OO_PG5 = sys.Position_Vector("O","PG5");

	Vector3D MS4_MS6 = sys.Position_Vector("MS4","MS6");
	Vector3D PG3_PG5 = sys.Position_Vector("PG3","PG5");
	
// Absolute vel. & accel.
// ------------------------------------------------------------------------------------------------
	Vector3D VabsO1 = sys.Dt(OO_O1,"abs");
	Vector3D VabsO2 = sys.Dt(OO_O2,"abs");
	Vector3D VabsO3 = sys.Dt(OO_O3,"abs");
	Vector3D VabsO4 = sys.Dt(OO_O4,"abs");
	Vector3D VabsO5 = sys.Dt(OO_O5,"abs");
	Vector3D VabsO6 = sys.Dt(OO_O6,"abs");
	Vector3D VabsO7 = sys.Dt(OO_O7,"abs");

	Vector3D AabsO1 = sys.Dt(VabsO1,"abs");
	Vector3D AabsO2 = sys.Dt(VabsO2,"abs");
	Vector3D AabsO3 = sys.Dt(VabsO3,"abs");
	Vector3D AabsO4 = sys.Dt(VabsO4,"abs");
	Vector3D AabsO5 = sys.Dt(VabsO5,"abs");
	Vector3D AabsO6 = sys.Dt(VabsO6,"abs");
	Vector3D AabsO7 = sys.Dt(VabsO7,"abs");

// Angular Velocities
// ------------------------------------------------------------------------------------------------
	Vector3D Omega0 = sys.Angular_Velocity("xyz","xyz");
	Vector3D Omega1 = sys.Angular_Velocity("xyz","B1");
	Vector3D Omega2 = sys.Angular_Velocity("xyz","B2");
	Vector3D Omega3 = sys.Angular_Velocity("xyz","B3");
	Vector3D Omega4 = sys.Angular_Velocity("xyz","B4");
	Vector3D Omega5 = sys.Angular_Velocity("xyz","B5");
	Vector3D Omega6 = sys.Angular_Velocity("xyz","B6");
	Vector3D Omega7 = sys.Angular_Velocity("xyz","B7");

	Vector3D Omega1_2 = sys.Angular_Velocity("B1","B2");
	Vector3D Omega2_3 = sys.Angular_Velocity("B2","B3");
	Vector3D Omega2_5 = sys.Angular_Velocity("B2","B5");

	Vector3D Alfa2_3 = sys.Angular_Acceleration("B2","B3");
	Vector3D Alfa2_5 = sys.Angular_Acceleration("B2","B5");

// Kinematic calculations
// ------------------------------------------------------------------------------------------------
	Vector3D O2_O5 = sys.Position_Vector("O2","O5");

	Vector3D VR2_O3 	= sys.Dt(O2_O3,"B2");
	Vector3D VR2_P3		= VR2_O3 + (Omega2_3 ^ O3_PG3);
	Vector3D VR2_O5 	= sys.Dt(O2_O5,"B2");
	Vector3D VR2_P5 	= VR2_O5 + (Omega2_5 ^ O5_PG5);

	Vector3D AR2_O3 	=	sys.Dt(VR2_O3,"B2");
	Vector3D AR2_P3_n =	(Omega2_3 ^ (Omega2_3 ^ O3_PG3));
	Vector3D AR2_P3_t =	(Alfa2_3 ^ O3_PG3);
	Vector3D AR2_P3		=	AR2_O3 + AR2_P3_n + AR2_P3_t;

	Vector3D AR2_O5 	=	sys.Dt(VR2_O5,"B2");
	Vector3D AR2_P5_n =	(Omega2_5 ^ (Omega2_5 ^ O5_PG5));
	Vector3D AR2_P5_t =	(Alfa2_5 ^ O5_PG5);
	Vector3D AR2_P5		=	AR2_O5 + AR2_P5_n + AR2_P5_t;

	Vector3D VabsM2 	= sys.Dt(OO_M2,"abs");
	Vector3D VabsM4		= sys.Dt(OO_M4,"abs");
	Vector3D VabsMS4		= sys.Dt(OO_MS4,"abs");
	Vector3D VabsMS6		= sys.Dt(OO_MS6,"abs");

	Vector3D VabsPG3	= sys.Dt(OO_PG3,"abs");
	Vector3D VabsPG5	= sys.Dt(OO_PG5,"abs");

	Vector3D VabsP3 	= sys.Dt(OO_O3,"abs") + (Omega3 ^ O3_PG3);
	Vector3D VabsP5 	= sys.Dt(OO_O5,"abs") + (Omega5 ^ O5_PG5);

	Vector3D VrelP3_P5 	= VabsP5 - VabsP3;

// ************************************************************************************************
// DYNAMICS
// ************************************************************************************************

// Dynamical Parameter Definition
// ------------------------------------------------------------------------------------------------
	// Dynamic Parameters of Bar 1
symbol_numeric  m1 = *sys.new_Parameter("m1",9.6676570E-00);
symbol_numeric  mx1 = *sys.new_Parameter("mx1",9.6676570E-00 * (+3.1468184E-04 -	(+0.0000)));
symbol_numeric  my1 = *sys.new_Parameter("my1",9.6676570E-00 * (-4.6322712E-04 -	(+0.0000)));
symbol_numeric  mz1 = *sys.new_Parameter("mz1",9.6676570E-00 * (+3.8007545E-02 -	(+0.0000)) );
symbol_numeric  Ixx1 = *sys.new_Parameter("Ixx1",+9.6622045E-01 + 9.6676570E-00 * (pow((-4.6322712E-04 -	(+0.0000)),2.0)+pow((+3.8007545E-02 -	(+0.0000)),2.0)));
symbol_numeric  Ixy1 = *sys.new_Parameter("Ixy1",-9.6717981E-07 - 9.6676570E-00 * ((+3.1468184E-04 -	(+0.0000))  *(-4.6322712E-04 -	(+0.0000))  ));
symbol_numeric  Ixz1 = *sys.new_Parameter("Ixz1",-1.5818274E-04 - 9.6676570E-00 * ((+3.1468184E-04 -	(+0.0000))  *(+3.8007545E-02 -	(+0.0000))  ));
symbol_numeric  Iyy1 = *sys.new_Parameter("Iyy1",+3.4517226E-01 + 9.6676570E-00 * (pow((+3.1468184E-04 -	(+0.0000)),2.0)+pow((+3.8007545E-02 -	(+0.0000)),2.0)));
symbol_numeric  Iyz1 = *sys.new_Parameter("Iyz1",-1.7021186E-04 - 9.6676570E-00 * ((-4.6322712E-04 -	(+0.0000))  *(+3.8007545E-02 -	(+0.0000))  ));		
symbol_numeric  Izz1 = *sys.new_Parameter("Izz1",+1.2621684E+00 + 9.6676570E-00 * (pow((+3.1468184E-04 -	(+0.0000)),2.0)+pow((-4.6322712E-04 -	(+0.0000)),2.0)));

	// Dynamic Parameters of Bar 2
symbol_numeric  m2 = *sys.new_Parameter("m2",3.9817384E+01);
symbol_numeric  mx2 = *sys.new_Parameter("mx2",3.9817384E+01 * (+7.4441072E-02 -	(+0.0000)));
symbol_numeric  my2 = *sys.new_Parameter("my2",3.9817384E+01 * (+3.2374109E-04 -	(+0.0000)));
symbol_numeric  mz2 = *sys.new_Parameter("mz2",3.9817384E+01 * (-4.4448598E-01 -	(+0.0900)));
symbol_numeric  Ixx2 = *sys.new_Parameter("Ixx2",+3.4371996E+00 + 3.9817384E+01 * (pow((+3.2374109E-04 -	(+0.0000)),2.0)+pow((-4.4448598E-01 -	(+0.0900)),2.0)));
symbol_numeric  Ixy2 = *sys.new_Parameter("Ixy2",+4.9170998E-03 - 3.9817384E+01 * ((+7.4441072E-02 -	(+0.0000))  *(+3.2374109E-04 -	(+0.0000))  ));
symbol_numeric  Ixz2 = *sys.new_Parameter("Ixz2",+4.0363785E-01 - 3.9817384E+01 * ((+7.4441072E-02 -	(+0.0000))  *(-4.4448598E-01 -	(+0.0900))  ));	
symbol_numeric  Iyy2 = *sys.new_Parameter("Iyy2",+6.5136166E+00 + 3.9817384E+01 * (pow((+7.4441072E-02 -	(+0.0000)),2.0)+pow((-4.4448598E-01 -	(+0.0900)),2.0)));
symbol_numeric  Iyz2 = *sys.new_Parameter("Iyz2",-1.6499419E-03 - 3.9817384E+01 * ((+3.2374109E-04 -	(+0.0000))  *(-4.4448598E-01 -	(+0.0900))  ));	
symbol_numeric  Izz2 = *sys.new_Parameter("Izz2",+4.3862389E+00 + 3.9817384E+01 * (pow((+7.4441072E-02 -	(+0.0000)),2.0)+pow((+3.2374109E-04 -	(+0.0000)),2.0)));

	// Dynamic Parameters of Bar 3
symbol_numeric  m3 = *sys.new_Parameter("m3",5.9558960E+00);
symbol_numeric  mx3 = *sys.new_Parameter("mx3",5.9558960E+00 * (+1.4695089E-01 -	(+0.1550)));
symbol_numeric  my3 = *sys.new_Parameter("my3",5.9558960E+00 * (+8.7976133E-06 -	(+0.0000)));
symbol_numeric  mz3 = *sys.new_Parameter("mz3",5.9558960E+00 * (-4.8279441E-01 -	(-0.4825)));
symbol_numeric  Ixx3 = *sys.new_Parameter("Ixx3",+1.0136931E-02 + 5.9558960E+00 * (pow((+8.7976133E-06 -	(+0.0000)),2.0)+pow((-4.8279441E-01 -	(-0.4825)),2.0)));
symbol_numeric  Ixy3 = *sys.new_Parameter("Ixy3",+1.3857334E-05 - 5.9558960E+00 * ((+1.4695089E-01 -	(+0.1550))  *(+8.7976133E-06 -	(+0.0000))  ));
symbol_numeric  Ixz3 = *sys.new_Parameter("Ixz3",-4.2223407E-06 - 5.9558960E+00 * ((+1.4695089E-01 -	(+0.1550))  *(-4.8279441E-01 -	(-0.4825))  ));
symbol_numeric  Iyy3 = *sys.new_Parameter("Iyy3",+8.4531364E-02 + 5.9558960E+00 * (pow((+1.4695089E-01 -	(+0.1550)),2.0)+pow((-4.8279441E-01 -	(-0.4825)),2.0)));
symbol_numeric  Iyz3 = *sys.new_Parameter("Iyz3",+1.3045386E-06 - 5.9558960E+00 * ((+8.7976133E-06 -	(+0.0000))  *(-4.8279441E-01 -	(-0.4825))  ));		
symbol_numeric  Izz3 = *sys.new_Parameter("Izz3",+8.4530535E-02 + 5.9558960E+00 * (pow((+1.4695089E-01 -	(+0.1550)),2.0)+pow((+8.7976133E-06 -	(+0.0000)),2.0)));

	// Dynamic Parameters of Bar 4
symbol_numeric  m4 = *sys.new_Parameter("m4",3.0096650E+01);
symbol_numeric  mx4 = *sys.new_Parameter("mx4",3.0096650E+01 * (-1.1368957E-01 -	(-0.3848)));
symbol_numeric  my4 = *sys.new_Parameter("my4",3.0096650E+01 * (+2.1208222E-02 -	(+0.0000)));
symbol_numeric  mz4 = *sys.new_Parameter("mz4",3.0096650E+01 * (-2.2992162E-01 -	(-0.2626)));
symbol_numeric  Ixx4 = *sys.new_Parameter("Ixx4",+7.3795017E-01 + 3.0096650E+01 * (pow((+2.1208222E-02 -	(+0.0000)),2.0)+pow((-2.2992162E-01 -	(-0.2626)),2.0)));
symbol_numeric  Ixy4 = *sys.new_Parameter("Ixy4",+7.5389739E-02 - 3.0096650E+01 * ((-1.1368957E-01 -	(-0.3848))  *(+2.1208222E-02 -	(+0.0000))  ));
symbol_numeric  Ixz4 = *sys.new_Parameter("Ixz4",+1.0735597E-01 - 3.0096650E+01 * ((-1.1368957E-01 -	(-0.3848))  *(-2.2992162E-01 -	(-0.2626))  ));	
symbol_numeric  Iyy4 = *sys.new_Parameter("Iyy4",+1.9455706E+00 + 3.0096650E+01 * (pow((-1.1368957E-01 -	(-0.3848)),2.0)+pow((-2.2992162E-01 -	(-0.2626)),2.0)));
symbol_numeric  Iyz4 = *sys.new_Parameter("Iyz4",-5.9818181E-02 - 3.0096650E+01 * ((+2.1208222E-02 -	(+0.0000))  *(-2.2992162E-01 -	(-0.2626))  ));	
symbol_numeric  Izz4 = *sys.new_Parameter("Izz4",+1.9115995E+00 + 3.0096650E+01 * (pow((-1.1368957E-01 -	(-0.3848)),2.0)+pow((+2.1208222E-02 -	(+0.0000)),2.0)));

	// Dynamic Parameters of Bar 5
symbol_numeric  m5 = *sys.new_Parameter("m5",5.9935295E+00);
symbol_numeric  mx5 = *sys.new_Parameter("mx5",5.9935295E+00 * (+3.4069777E-02 -	(+0.1550)));
symbol_numeric  my5 = *sys.new_Parameter("my5",5.9935295E+00 * (-8.3998698E-05 -	(+0.0000)));
symbol_numeric  mz5 = *sys.new_Parameter("mz5",5.9935295E+00 * (-3.3219413E-01 -	(-0.3325)));
symbol_numeric  Ixx5 = *sys.new_Parameter("Ixx5",+1.0233319E-02 + 5.9935295E+00 * (pow((-8.3998698E-05 -	(+0.0000)),2.0)+pow((-3.3219413E-01 -	(-0.3325)),2.0)));
symbol_numeric  Ixy5 = *sys.new_Parameter("Ixy5",-1.2319444E-04 - 5.9935295E+00 * ((+3.4069777E-02 -	(+0.1550))  *(-8.3998698E-05 -	(+0.0000))  ));
symbol_numeric  Ixz5 = *sys.new_Parameter("Ixz5",-2.5817770E-07 - 5.9935295E+00 * ((+3.4069777E-02 -	(+0.1550))  *(-3.3219413E-01 -	(-0.3325))  ));	
symbol_numeric  Iyy5 = *sys.new_Parameter("Iyy5",+1.7641985E-01 + 5.9935295E+00 * (pow((+3.4069777E-02 -	(+0.1550)),2.0)+pow((-3.3219413E-01 -	(-0.3325)),2.0)));
symbol_numeric  Iyz5 = *sys.new_Parameter("Iyz5",+1.3534583E-06 - 5.9935295E+00 * ((-8.3998698E-05 -	(+0.0000))  *(-3.3219413E-01 -	(-0.3325))  ));
symbol_numeric  Izz5 = *sys.new_Parameter("Izz5",+1.7641394E-01 + 5.9935295E+00 * (pow((+3.4069777E-02 -	(+0.1550)),2.0)+pow((-8.3998698E-05 -	(+0.0000)),2.0)));

	// Dynamic Parameters of Bar 6
symbol_numeric  m6 = *sys.new_Parameter("m6",1.1543302E+01);
symbol_numeric  mx6 = *sys.new_Parameter("mx6",1.1543302E+01 * (+1.6951865E-03 -	(-0.3848)));
symbol_numeric  my6 = *sys.new_Parameter("my6",1.1543302E+01 * (-0.0000000E+00 -	(+0.0000)));
symbol_numeric  mz6 = *sys.new_Parameter("mz6",1.1543302E+01 * (+1.8654568E-01 -	(+0.2294)));
symbol_numeric  Ixx6 = *sys.new_Parameter("Ixx6",+3.7529484E-01 + 1.1543302E+01 * (pow((-0.0000000E+00 -	(+0.0000)),2.0)+pow((+1.8654568E-01 -	(+0.2294)),2.0)));
symbol_numeric  Ixy6 = *sys.new_Parameter("Ixy6",-0.0000000E+00 - 1.1543302E+01 * ((+1.6951865E-03 -	(-0.3848))  *(-0.0000000E+00 -	(+0.0000))  ));
symbol_numeric  Ixz6 = *sys.new_Parameter("Ixz6",+1.7104997E-01 - 1.1543302E+01 * ((+1.6951865E-03 -	(-0.3848))  *(+1.8654568E-01 -	(+0.2294))  ));	
symbol_numeric  Iyy6 = *sys.new_Parameter("Iyy6",+1.1578711E+00 + 1.1543302E+01 * (pow((+1.6951865E-03 -	(-0.3848)),2.0)+pow((+1.8654568E-01 -	(+0.2294)),2.0)));
symbol_numeric  Iyz6 = *sys.new_Parameter("Iyz6",-0.0000000E+00 - 1.1543302E+01 * ((-0.0000000E+00 -	(+0.0000))  *(+1.8654568E-01 -	(+0.2294))  ));	
symbol_numeric  Izz6 = *sys.new_Parameter("Izz6",+1.3162802E+00 + 1.1543302E+01 * (pow((+1.6951865E-03 -	(-0.3848)),2.0)+pow((-0.0000000E+00 -	(+0.0000)),2.0)));

	// Dynamic Parameters of Bar 7 **** PONER VALORES DEL CAD CUANDO ESTEN DISPONIBLES ****
symbol_numeric  m7 = *sys.new_Parameter("m7",1.0E+00);
symbol_numeric  mx7 = *sys.new_Parameter("mx7",1.0E+00);
symbol_numeric  my7 = *sys.new_Parameter("my7",1.0E+00);
symbol_numeric  mz7 = *sys.new_Parameter("mz7",1.0E+00);
symbol_numeric  Ixx7 = *sys.new_Parameter("Ixx7",1.0E+00);
symbol_numeric  Ixy7 = *sys.new_Parameter("Ixy7",0.0);
symbol_numeric  Ixz7 = *sys.new_Parameter("Ixz7",0.0);	
symbol_numeric  Iyy7 = *sys.new_Parameter("Iyy7",1.0E+00);
symbol_numeric  Iyz7 = *sys.new_Parameter("Iyz7",0.0);
symbol_numeric  Izz7 = *sys.new_Parameter("Izz7",1.0E+00);

// Inertia Tensor Definition
// ------------------------------------------------------------------------------------------------
	// Inertia Tensor of Bar 1
	Tensor3D  I1_O1 = *sys.new_Tensor3D("I1_O1",	(ex)Ixx1,	(ex)Ixy1,	(ex)Ixz1,
																								(ex)Ixy1,	(ex)Iyy1,	(ex)Iyz1,
																								(ex)Ixz1,	(ex)Iyz1,	(ex)Izz1,	"B1");

	// Inertia Tensor of Bar 2
	Tensor3D  I2_O2 = *sys.new_Tensor3D("I2_O2",	(ex)Ixx2,	(ex)Ixy2,	(ex)Ixz2,
																								(ex)Ixy2,	(ex)Iyy2,	(ex)Iyz2,
																								(ex)Ixz2,	(ex)Iyz2,	(ex)Izz2,	"B2");

	// Inertia Tensor of Bar 3
	Tensor3D  I3_O3 = *sys.new_Tensor3D("I3_O3",	(ex)Ixx3,	(ex)Ixy3,	(ex)Ixz3,
																								(ex)Ixy3,	(ex)Iyy3,	(ex)Iyz3,
																								(ex)Ixz3,	(ex)Iyz3,	(ex)Izz3,	"B3");

	// Inertia Tensor of Bar 4
	Tensor3D  I4_O4 = *sys.new_Tensor3D("I4_O4",	(ex)Ixx4,	(ex)Ixy4,	(ex)Ixz4,
																								(ex)Ixy4,	(ex)Iyy4,	(ex)Iyz4,
																								(ex)Ixz4,	(ex)Iyz4,	(ex)Izz4,	"B4");

	// Inertia Tensor of Bar 5
	Tensor3D  I5_O5 = *sys.new_Tensor3D("I5_O5",	(ex)Ixx5,	(ex)Ixy5,	(ex)Ixz5,
																								(ex)Ixy5,	(ex)Iyy5,	(ex)Iyz5,
																								(ex)Ixz5,	(ex)Iyz5,	(ex)Izz5,	"B5");

	// Inertia Tensor of Bar 6
	Tensor3D  I6_O6 = *sys.new_Tensor3D("I6_O6",	(ex)Ixx6,	(ex)Ixy6,	(ex)Ixz6,
																								(ex)Ixy6,	(ex)Iyy6,	(ex)Iyz6,
																								(ex)Ixz6,	(ex)Iyz6,	(ex)Izz6,	"B6");

	// Inertia Tensor of Bar 7
	Tensor3D  I7_O7 = *sys.new_Tensor3D("I7_O7",	(ex)Ixx7,	(ex)Ixy7,	(ex)Ixz7,
																								(ex)Ixy7,	(ex)Iyy7,	(ex)Iyz7,
																								(ex)Ixz7,	(ex)Iyz7,	(ex)Izz7,	"B7");

// Center of Gravity Points Definition
// ------------------------------------------------------------------------------------------------
	// Vectors
	Vector3D O1_G1 = *sys.new_Vector3D("O1_G1",mx1/m1,my1/m1,mz1/m1,"B1");
	Vector3D O2_G2 = *sys.new_Vector3D("O2_G2",mx2/m2,my2/m2,mz2/m2,"B2");
	Vector3D O3_G3 = *sys.new_Vector3D("O3_G3",mx3/m3,my3/m3,mz3/m3,"B3");
	Vector3D O4_G4 = *sys.new_Vector3D("O4_G4",mx4/m4,my4/m4,mz4/m4,"B4");
	Vector3D O5_G5 = *sys.new_Vector3D("O5_G5",mx5/m5,my5/m5,mz5/m5,"B5");
	Vector3D O6_G6 = *sys.new_Vector3D("O6_G6",mx6/m6,my6/m6,mz6/m6,"B6");
	Vector3D O7_G7 = *sys.new_Vector3D("O7_G7",mx7/m7,my7/m7,mz7/m7,"B7");

	// Points
	Point * G1 = sys.new_Point("G1","O1",&O1_G1);
	Point * G2 = sys.new_Point("G2","O2",&O2_G2);
	Point * G3 = sys.new_Point("G3","O3",&O3_G3);
	Point * G4 = sys.new_Point("G4","O4",&O4_G4);
	Point * G5 = sys.new_Point("G5","O5",&O5_G5);
	Point * G6 = sys.new_Point("G6","O6",&O6_G6);
	Point * G7 = sys.new_Point("G7","O7",&O7_G7);

	// Absolute position Vector of G
	Vector3D OO_G1 = sys.Position_Vector("O","G1");
	Vector3D OO_G2 = sys.Position_Vector("O","G2");
	Vector3D OO_G3 = sys.Position_Vector("O","G3");
	Vector3D OO_G4 = sys.Position_Vector("O","G4");
	Vector3D OO_G5 = sys.Position_Vector("O","G5");
	Vector3D OO_G6 = sys.Position_Vector("O","G6");
	Vector3D OO_G7 = sys.Position_Vector("O","G7");

	// Define Velocity and Acceleration of Center of Gravity Points
	Vector3D VabsG1 = sys.Dt(OO_G1,"abs");
	Vector3D AabsG1 = sys.Dt(VabsG1,"abs");

	Vector3D VabsG2 = sys.Dt(OO_G2,"abs");
	Vector3D AabsG2 = sys.Dt(VabsG2,"abs");

	Vector3D VabsG3 = sys.Dt(OO_G3,"abs");
	Vector3D AabsG3 = sys.Dt(VabsG3,"abs");

	Vector3D VabsG4 = sys.Dt(OO_G4,"abs");
	Vector3D AabsG4 = sys.Dt(VabsG4,"abs");

	Vector3D VabsG5 = sys.Dt(OO_G5,"abs");
	Vector3D AabsG5 = sys.Dt(VabsG5,"abs");

	Vector3D VabsG6 = sys.Dt(OO_G6,"abs");
	Vector3D AabsG6 = sys.Dt(VabsG6,"abs");

	Vector3D VabsG7 = sys.Dt(OO_G7,"abs");
	Vector3D AabsG7 = sys.Dt(VabsG7,"abs");

	Solid * S1 = sys.new_Solid("S1","O1","B1","m1","O1_G1","I1_O1","./solids/sol1.osg",1,0,0,0.8);
	Solid * S2 = sys.new_Solid("S2","O2","B2","m2","O2_G2","I2_O2","./solids/sol2.osg",0,1,0,0.5);
	Solid * S3 = sys.new_Solid("S3","O3","B3","m3","O3_G3","I3_O3","./solids/sol3.osg",0,0,1,1.0);
	Solid * S4 = sys.new_Solid("S4","O4","B4","m4","O4_G4","I4_O4","./solids/sol4.osg",1,1,0,0.2);
	Solid * S5 = sys.new_Solid("S5","O5","B5","m5","O5_G5","I5_O5","./solids/sol5.osg",1,0,1,1.0);
	Solid * S6 = sys.new_Solid("S6","O6","B6","m6","O6_G6","I6_O6","./solids/sol6.osg",0,1,1,0.2);
	Solid * S7 = sys.new_Solid("S7","O7","B7","m7","O7_G7","I7_O7","./solids/sol7.stl",1,1,1,1.0);

//*************************************************************************************************
//*************************************************************************************************
//#define SLIP // Comment this line for Non_Slip conditions
//*************************************************************************************************
//*************************************************************************************************
#ifdef SLIP

#ifdef LAG
	symbol_numeric lambda1		= *sys.new_Joint_Unknown("lambda1",0.0);
	symbol_numeric lambda2		= *sys.new_Joint_Unknown("lambda2",0.0);

	cout << "" << endl;
	cout << "Option not defined. Lagangre and Slip not available." << endl;
	cout << "" << endl;
	return 0;
	// to define this option V*Fe=Phi_qT*lambda. Then include in din eq.
#endif

#ifdef V_P
	// Joint Unknown Definition
	// Contact forces between solid 4 and 5. Defined Actuating on solid 5.
	symbol_numeric T5 			= *sys.new_Joint_Unknown("T5");
	Vector3D T_54 = *sys.new_Vector3D("T_54",T5,0,0,"B4");	// Torsor.
	// Contact forces between solid 3 and 5. Defined Actuating on solid 3.
	symbol_numeric Fn = *sys.new_Joint_Unknown("Fn");
	Vector3D F_E_53   = *sys.new_Vector3D("F_E_53",0,0,-Fn,"B2");	// Torsor.
	// Tang. Force. Defined actuating on solid 3.
	ex VR 						= (VrelP3_P5 * B2_010);

	symbol_numeric mu								= *sys.new_Parameter("mu"		,0.1000);
	symbol_numeric grad_V0_mu				= *sys.new_Parameter("grad"	,5.0000);
	ex     V0	= mu / grad_V0_mu;	// gradient not too steep or integration problems

	ex Ft 						= (step(VR - V0) - (1 - step(VR + V0))) * (mu * Fn) + (step(VR + V0) - step(VR - V0)) * (mu * Fn * (VR / V0));
	Vector3D F_T_53 	= *sys.new_Vector3D("F_T_53",0,Ft,0,"B2");	// Torsor.
#endif

	// ************************************************************************************************
	// KINEMATIC EQUATIONS
	// ************************************************************************************************
	ex constr_eq_set_1 = a5*Ratio-a7;	// Reductor
	ex constr_eq_set_2 = PG3_PG5 * B2_001;	// Solo condicion de contacto

	Matrix Phi(2,1,&constr_eq_set_1,&constr_eq_set_2);

#else

#ifdef LAG	
	symbol_numeric lambda1	= *sys.new_Joint_Unknown("lambda1",0.0);
	symbol_numeric lambda2	= *sys.new_Joint_Unknown("lambda2",0.0);
	symbol_numeric lambda3	= *sys.new_Joint_Unknown("lambda3",0.0);
#endif

#ifdef V_P
	// Joint Unknown Definition
	// Contact forces between solid 4 and 5. Defined Actuating on solid 5.
	symbol_numeric T5 			= *sys.new_Joint_Unknown("T5");
	Vector3D T_54 = *sys.new_Vector3D("T_54",T5,0,0,"B4");	// Torsor.
	// Contact forces between solid 3 and 5. Defined Actuating on solid 3.
	symbol_numeric Fn 			= *sys.new_Joint_Unknown("Fn");
	symbol_numeric Ft 			= *sys.new_Joint_Unknown("Ft");
	Vector3D F_E_53 = *sys.new_Vector3D("F_E_53",0,Ft,Fn,"B2");	// Torsor.
	// Tang. Force. Defined actuating on solid 3.
	Vector3D F_T_53 	= *sys.new_Vector3D("F_T_53",0,0,0,"B2");	// Torsor.
#endif

	// ************************************************************************************************
	// KINEMATIC EQUATIONS
	// ************************************************************************************************
	ex constr_eq_set_1 = a5*Ratio-a7;	// Reductor
	ex constr_eq_set_2 = PG3_PG5 * B2_001;	// Condicion de contacto
	ex constr_eq_set_3 = -a3*Rr-a5*Rw;			// Condicion de no deliz.

	Matrix Phi(3,1,&constr_eq_set_1,&constr_eq_set_2,&constr_eq_set_3);

#endif
Matrix Init				((q.rows() - Phi.rows()),1	,coord_indep_init);
Matrix Init_t			((q.rows() - Phi.rows()),1	,vel_indep_init);
// ************************************************************************************************
// ************************************************************************************************


// ------------------------------------------------------------------------------------------------
// EXTERNAL FORCES-TORQUES APPLIED TO THE HUB
// ------------------------------------------------------------------------------------------------
	symbol_numeric Tm 		= *sys.new_Input("Tm",0.0); // Tm pos if q5 pos on axis 1 B5. Defined actuating on 5.
	symbol_numeric Tb 		= *sys.new_Input("Tb",0.0);	// Tb pos if q3 pos on axis 1 B3. Defined actuating on 3.


// Constitutive Forces and moments Definition
// ------------------------------------------------------------------------------------------------
	// External forces and moments
// Fc pos if spring pushing wheel against road. Defined actuating on 2.
	ex Fc 						=	+Ks*(Ls0-Ls)-Ki*(Li0-Li);
	Vector3D F_spring	= *sys.new_Vector3D("F_spring",0,0,Fc,"B2");

// Fs pos if pushing mass upwards. Defined actuating on 6.
	ex			LL				= pow((MS4_MS6 * MS4_MS6),0.5);	// F on spring function of position of spring endings.
	Vector3D F_susp		= (Kt*(L0-LL)/LL) * (MS4_MS6);		// F on spring diretion of spring.

// Friction
	Vector3D MV_S1 = -Cvis_a1* sys.Angular_Velocity("xyz" ,"B1" );
	Vector3D MV_S2 = -Cvis_a2* sys.Angular_Velocity("B1" ,"B2" );

	Vector3D MV_S3 = -Cvis_a3* sys.Angular_Velocity("B2" ,"B3" );
	Vector3D MV_S5 = -Cvis_a5* sys.Angular_Velocity("B4" ,"B5" );

	Vector3D MV_S6 = -Cvis_a6* sys.Angular_Velocity("B2" ,"B6" );

	Vector3D MV_S7 = -Cvis_a7* sys.Angular_Velocity("B4" ,"B7" );

// Motor and brake
	Vector3D T_motor	= *sys.new_Vector3D("T_motor",0,0,Tm,"B7");
	Vector3D T_brake	= *sys.new_Vector3D("T_brake",Tb,0,0,"B3");

	// Gravity vectors
	Vector3D F_G_1 = *sys.new_Vector3D("F_G_1",0,0,-m1 * (*g),"xyz");
	Vector3D F_G_2 = *sys.new_Vector3D("F_G_2",0,0,-m2 * (*g),"xyz");
	Vector3D F_G_3 = *sys.new_Vector3D("F_G_3",0,0,-m3 * (*g),"xyz");
	Vector3D F_G_4 = *sys.new_Vector3D("F_G_4",0,0,-m4 * (*g),"xyz");
	Vector3D F_G_5 = *sys.new_Vector3D("F_G_5",0,0,-m5 * (*g),"xyz");
	Vector3D F_G_6 = *sys.new_Vector3D("F_G_6",0,0,-m6 * (*g),"xyz");
	Vector3D F_G_7 = *sys.new_Vector3D("F_G_7",0,0,-m7 * (*g),"xyz");

	// Inertia Forces
	Vector3D F_I_O1 = -m1 * AabsG1;
	Vector3D F_I_O2 = -m2 * AabsG2;
	Vector3D F_I_O3 = -m3 * AabsG3;
	Vector3D F_I_O4 = -m4 * AabsG4;
	Vector3D F_I_O5 = -m5 * AabsG5;
	Vector3D F_I_O6 = -m6 * AabsG6;
	Vector3D F_I_O7 = -m7 * AabsG7;

	// Angular moment and Inertia Moment
	Vector3D H1_O1 = I1_O1 * Omega1;
	Vector3D H2_O2 = I2_O2 * Omega2;
	Vector3D H3_O3 = I3_O3 * Omega3;
	Vector3D H4_O4 = I4_O4 * Omega4;
	Vector3D H5_O5 = I5_O5 * Omega5;
	Vector3D H6_O6 = I6_O6 * Omega6;
	Vector3D H7_O7 = I7_O7 * Omega7;

	Vector3D M_I_O1 = -sys.Dt(H1_O1,"xyz") - ((m1 * O1_G1) ^ AabsO1);
	Vector3D M_I_O2 = -sys.Dt(H2_O2,"xyz") - ((m2 * O2_G2) ^ AabsO2);
	Vector3D M_I_O3 = -sys.Dt(H3_O3,"xyz") - ((m3 * O3_G3) ^ AabsO3);
	Vector3D M_I_O4 = -sys.Dt(H4_O4,"xyz") - ((m4 * O4_G4) ^ AabsO4);
	Vector3D M_I_O5 = -sys.Dt(H5_O5,"xyz") - ((m5 * O5_G5) ^ AabsO5);
	Vector3D M_I_O6 = -sys.Dt(H6_O6,"xyz") - ((m6 * O6_G6) ^ AabsO6);
	Vector3D M_I_O7 = -sys.Dt(H7_O7,"xyz") - ((m7 * O7_G7) ^ AabsO7);

// ************************************************************************************************
	Matrix parameters														= sys.Parameters();
  vector < symbol_numeric * > Parameters 			= sys.get_Parameters();
	Matrix unknown 															= sys.Joint_Unknowns();
  vector < symbol_numeric * > Joint_Unknowns 	= sys.get_Joint_Unknowns();
	Matrix input 																= sys.Inputs();
  vector < symbol_numeric * > Inputs		 			= sys.get_Inputs();

// ************************************************************************************************
//	Define Torsors	
// ************************************************************************************************
//#define TORSOR

#ifdef TORSOR
	cout << "Define Torsors" << endl;
	Vector3D M_Zero = *sys.new_Vector3D("M_Zero",0,0,0,"xyz");
	Vector3D F_Zero = *sys.new_Vector3D("F_Zero",0,0,0,"xyz");

	//	Gravity

	Torsor3D * Gravity_S1 = sys.Gravity_Torsor("S1");
	Torsor3D * Gravity_S2 = sys.Gravity_Torsor("S2");
	Torsor3D * Gravity_S3 = sys.Gravity_Torsor("S3");
	Torsor3D * Gravity_S4 = sys.Gravity_Torsor("S4");
	Torsor3D * Gravity_S5 = sys.Gravity_Torsor("S5");
	Torsor3D * Gravity_S6 = sys.Gravity_Torsor("S6");
	Torsor3D * Gravity_S7 = sys.Gravity_Torsor("S7");

	//	Inertia
	Torsor3D * Inertia_S1 = sys.Inertia_Torsor("S1");
	Torsor3D * Inertia_S2 = sys.Inertia_Torsor("S2");
	Torsor3D * Inertia_S3 = sys.Inertia_Torsor("S3");
	Torsor3D * Inertia_S4 = sys.Inertia_Torsor("S4");
	Torsor3D * Inertia_S5 = sys.Inertia_Torsor("S5");
	Torsor3D * Inertia_S6 = sys.Inertia_Torsor("S6");
	Torsor3D * Inertia_S7 = sys.Inertia_Torsor("S7");


	//	Constitutive ===> State
	Torsor3D * F_spring_2 = sys.new_Torsor3D ( "F_spring_2",  F_spring,  M_Zero, M2 , S2 , "Constitutive") ;
	Torsor3D * F_spring_4 = sys.new_Torsor3D ( "F_spring_4", -F_spring, -M_Zero, M4 , S4 , "Constitutive") ;
	Torsor3D * F_susp_6 = sys.new_Torsor3D ( "F_susp_6",  F_susp,  M_Zero, MS6 , S6 , "Constitutive") ;
	Torsor3D * F_susp_4 = sys.new_Torsor3D ( "F_susp_4", -F_susp, -M_Zero, MS4 , S4 , "Constitutive") ;

	//	External ===> Inputs
	Torsor3D * T_motor_7 = sys.new_Torsor3D ( "T_motor_7",  F_Zero,  T_motor, G7 , S7 , "External") ;
	Torsor3D * T_motor_4 = sys.new_Torsor3D ( "T_motor_4", -F_Zero, -T_motor, G4 , S4 , "External") ;

	Torsor3D * T_brake_3 = sys.new_Torsor3D ( "T_brake_3",  F_Zero,  T_brake, G3 , S3 , "External") ;
	Torsor3D * T_brake_2 = sys.new_Torsor3D ( "T_brake_2", -F_Zero, -T_brake, G2 , S2 , "External") ;

	//	Joints ===> Unkonwns

	Torsor3D * T_54_5 = sys.new_Torsor3D ( "T_54_5",  F_Zero,  T_54, G5 , S5 , "Joint") ;
	Torsor3D * T_54_4 = sys.new_Torsor3D ( "T_54_4", -F_Zero, -T_54, G4 , S4 , "Joint") ;

	Torsor3D * F_E_53_3 = sys.new_Torsor3D ( "F_E_53_3",  F_E_53,  M_Zero, PG3 , S3 , "Joint") ;
	Torsor3D * F_E_53_5 = sys.new_Torsor3D ( "F_E_53_5", -F_E_53, -M_Zero, PG5 , S5 , "Joint") ;

	Torsor3D * F_T_53_3 = sys.new_Torsor3D ( "F_T_53_3",  F_T_53,  M_Zero, PG3 , S3 , "Joint") ;
	Torsor3D * F_T_53_5 = sys.new_Torsor3D ( "F_T_53_5", -F_T_53, -M_Zero, PG5 , S5 , "Joint") ;

	Matrix Dynamic_Equations = -sys.GenForceSys("ALL");
//	Matrix D_E = -sys.GenForceSys("ALL");
#endif
// ************************************************************************************************
// DYNAMIC EQUATIONS
// ************************************************************************************************

#ifndef TORSOR
cout << "Dynamic Equations" << endl;

// Dynamic Equations
// ------------------------------------------------------------------------------------------------

Matrix Dynamic_Equations(7,1);	// As many dyn.eq. as gen.coordinates (q1...q7 here)  

for (int i=0; (i < dq.rows()); ++i) {
 symbol_numeric dq_i;
 dq_i=ex_to<symbol_numeric>(dq(i,0));
 Dynamic_Equations (i,0) = 
// 	Inertial Forces and Torques
	  F_I_O1 * sys.diff(VabsO1,dq_i) + M_I_O1 * sys.diff(Omega1,dq_i)
	+ F_I_O2 * sys.diff(VabsO2,dq_i) + M_I_O2 * sys.diff(Omega2,dq_i)
	+ F_I_O3 * sys.diff(VabsO3,dq_i) + M_I_O3 * sys.diff(Omega3,dq_i)
	+ F_I_O4 * sys.diff(VabsO4,dq_i) + M_I_O4 * sys.diff(Omega4,dq_i)
	+ F_I_O5 * sys.diff(VabsO5,dq_i) + M_I_O5 * sys.diff(Omega5,dq_i)
	+ F_I_O6 * sys.diff(VabsO6,dq_i) + M_I_O6 * sys.diff(Omega6,dq_i)
	+ F_I_O7 * sys.diff(VabsO7,dq_i) + M_I_O7 * sys.diff(Omega7,dq_i)

// 	Gravitational Forces
	+ F_G_1 * sys.diff(VabsG1,dq_i)
	+ F_G_2 * sys.diff(VabsG2,dq_i)
	+ F_G_3 * sys.diff(VabsG3,dq_i)
	+ F_G_4 * sys.diff(VabsG4,dq_i)
	+ F_G_5 * sys.diff(VabsG5,dq_i)
	+ F_G_6 * sys.diff(VabsG6,dq_i)
	+ F_G_7 * sys.diff(VabsG7,dq_i)

// 	Constitutive Forces and Torques
	+ F_spring * sys.diff(VabsM2,dq_i) - F_spring * sys.diff(VabsM4,dq_i)
	+ F_susp * sys.diff(VabsMS6,dq_i) - F_susp * sys.diff(VabsMS4,dq_i)
	+ T_motor * sys.diff(Omega7,dq_i)	- T_motor * sys.diff(Omega4,dq_i)
	+ T_brake * sys.diff(Omega3,dq_i)	- T_brake * sys.diff(Omega2,dq_i)

	+ MV_S1 * sys.diff(Omega1,dq_i)	- MV_S1 * sys.diff(Omega0,dq_i)
	+ MV_S2 * sys.diff(Omega2,dq_i)	- MV_S2 * sys.diff(Omega1,dq_i)

	+ MV_S3 * sys.diff(Omega3,dq_i)	- MV_S3 * sys.diff(Omega2,dq_i)
	+ MV_S5 * sys.diff(Omega5,dq_i)	- MV_S5 * sys.diff(Omega4,dq_i)

	+ MV_S6 * sys.diff(Omega6,dq_i)	- MV_S6 * sys.diff(Omega2,dq_i)

	+ MV_S7 * sys.diff(Omega7,dq_i)	- MV_S7 * sys.diff(Omega4,dq_i)

// Adding equations for CLOSED din-eq.

#ifdef V_P
// 	Joint Forces
	+ T_54 * sys.diff(Omega5,dq_i)	- T_54 * sys.diff(Omega4,dq_i)
	+ F_E_53 * sys.diff(VabsP3,dq_i) - F_E_53 * sys.diff(VabsP5,dq_i)
	+ F_T_53 * sys.diff(VabsP3,dq_i) - F_T_53 * sys.diff(VabsP5,dq_i)
#endif

#ifdef LAG
//	Closed dyn eq in Lagrange solution would be....
//	+ lambda1 * Phi_q(0,i)
//	+ lambda1 * Phi_q(1,i)
#endif
	;
}
Dynamic_Equations 			= - Dynamic_Equations;			//So that MASS matrix will be positive definite as is standard practice.

#endif

//Dynamic_Equations 			=  Dynamic_Equations - D_E;
//cout << "Dynamic Equations" << endl;cout << Dynamic_Equations << endl;cout << "" << endl;
//return 0;

// ************************************************************************************************
// Output Vector
// ************************************************************************************************

    cout << "Output Vector" << endl;
    Vector3D ez = *sys.new_Vector3D("ez",0,0,1,"xyz");

    ex Total_Energy =
        // Kinetic and Potential energy
        // ----------------------------
	      + numeric(1,2)*m1*(VabsG1*VabsG1) + numeric(1,2)* Omega1*(H1_O1-m1*(O1_G1^(Omega1^O1_G1))) + m1*(*g)*OO_G1*ez
        + numeric(1,2)*m2*(VabsG2*VabsG2) + numeric(1,2)* Omega2*(H2_O2-m2*(O2_G2^(Omega2^O2_G2))) + m2*(*g)*OO_G2*ez
        + numeric(1,2)*m3*(VabsG3*VabsG3) + numeric(1,2)* Omega3*(H3_O3-m3*(O3_G3^(Omega3^O3_G3))) + m3*(*g)*OO_G3*ez
        + numeric(1,2)*m4*(VabsG4*VabsG4) + numeric(1,2)* Omega4*(H4_O4-m4*(O4_G4^(Omega4^O4_G4))) + m4*(*g)*OO_G4*ez
        + numeric(1,2)*m5*(VabsG5*VabsG5) + numeric(1,2)* Omega5*(H5_O5-m5*(O5_G5^(Omega5^O5_G5))) + m5*(*g)*OO_G5*ez
        + numeric(1,2)*m6*(VabsG6*VabsG6) + numeric(1,2)* Omega6*(H6_O6-m6*(O6_G6^(Omega6^O6_G6))) + m6*(*g)*OO_G6*ez
        + numeric(1,2)*m7*(VabsG7*VabsG7) + numeric(1,2)* Omega7*(H7_O7-m7*(O7_G7^(Omega7^O7_G7))) + m7*(*g)*OO_G7*ez
        // Elastic potential energy
        // ------------------------
        + numeric(1,2)*Kt*((L0-LL)*(L0-LL));

Matrix Output(Coordinates.size()+Velocities.size()+Joint_Unknowns.size()+1,1);
for (int i=0; (i < Coordinates.size());    ++i){Output(i,0)                                      =*Coordinates[i];}
for (int i=0; (i < Velocities.size());     ++i){Output(Coordinates.size()+i,0)                   =*Velocities[i];}
for (int i=0; (i < Joint_Unknowns.size()); ++i){Output(Coordinates.size()+Velocities.size()+i,0) =*Joint_Unknowns[i];}

Output(Coordinates.size()+Velocities.size()+Joint_Unknowns.size(),0) = Total_Energy; //Total_Energy


Matrix Energy(1,1,&Total_Energy );
* sys.new_Matrix("Output",Output );
* sys.new_Matrix("Energy",Energy );

sys.export_Output(sys, ORDER , MAPLE);

// ************************************************************************************************
// MATRIX CALCULATION
// ************************************************************************************************
//# define PROBLEM_TYPE "Q"
//# define PROBLEM_TYPE "Z"
//# define PROBLEM_TYPE "I3AL_Q"
//# define PROBLEM_TYPE "I3AL_Z"
//# define PROBLEM_TYPE "ALL"

#ifndef PROBLEM_TYPE
	#define PROBLEM_TYPE "ALL"
#endif

cout << "Matrix Calculation" << endl;
sys.Matrix_Calculation(Phi, coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);
// ************************************************************************************************
// Export C code for Direct Simulation 
// ************************************************************************************************
cout << "Export C code for Direct Simulation" << endl;
sys.export_Dynamic_Simulation                       (sys, ORDER , MAPLE, PROBLEM_TYPE);
// ************************************************************************************************
/*
Matrix Qd_d = *sys.get_Matrix ( "Qd_d" );
cout << "Qd_d" << endl;cout << Qd_d << endl;cout << "" << endl;
Matrix PhiInit_q = *sys.get_Matrix ( "PhiInit_q" );
cout << "PhiInit_q" << endl;cout << PhiInit_q << endl;cout << "" << endl;
*/
// ************************************************************************************************

lst state;

	state = a1,a2,*da1,*da2;
	sys.export_write_data_file_C(state);
//	sys.export_write_data_file_H();

/*
lst accel;
	accel = *dda1,*dda2;
*/

/*
l =	Sp,Lp,Ln,Ww,W,Hn,Hi,Hs,Hb,Rw,Rr,Rx,Bx,Mx,Si,Ss,SR,VS,g,af1,af2,W1,W2,W3,W4,W5,Ki,Li0,Li,Ls0,Ls,L0,L,Ds,Di,
a1,a2,a5,a6,a3,a4,
*da1,*dda1,*da2,*dda2,*dda4,*da5,*dda5,*da6,*dda6,*da3,*dda3,*da4;
*/
//	l = a1,a2,a3,a4,a5,a6,*da1,*da2,*da3,*da4,*da5,*da6,*dda1,*dda2;

// ************************************************************************************************
/*
Matrix Q = *sys.get_Matrix ( "Q" );
Matrix Q_q = sys.jacobian(Q.transpose() ,q);
sys.export_function_MATLAB("Q_q", "Q_q_", Q_q);
Matrix Q_dq = sys.jacobian(Q.transpose() ,dq);
sys.export_function_MATLAB("Q_dq", "Q_dq_", Q_dq);
*/
// ************************************************************************************************
// ************************************************************************************************
//  Export Point, Base and Frame Diagrams 
// ************************************************************************************************
// ************************************************************************************************

/*---------begin  Graphviz export---------*/
#ifdef GRAPHVIZ 

cout << "GRAPHVIZ defined" << endl;
sys.export_Graphviz_dot (  );

//Generate eps figure
system("dot -Tps   base_diagram.dot -o plain_base_diagram.eps");system("latex base_diagram.tex");system("dvips base_diagram.dvi -o base_diagram.eps");
//Generate figure eps
system("dot -Tps   point_diagram.dot -o plain_point_diagram.eps");system("latex point_diagram.tex");system("dvips point_diagram.dvi -o point_diagram.eps");
//Generate eps figure
system("dot -Tps   frame_diagram.dot -o plain_frame_diagram.eps");system("latex frame_diagram.tex");system("dvips base_diagram.dvi -o base_diagram.eps");

#endif
/*---------end  Graphviz export---------*/

// ************************************************************************************************
/*---------begin write q, dq, ddq, epsilon, parameters to environment.m---------*/
cout << "Create enviromment.m " << endl;
sys.export_environment_m (  );
/*---------end write q, dq, ddq, epsilon, parameters to environment.m---------*/
// ************************************************************************************************
// ************************************************************************************************
// Openscenegraph
// ************************************************************************************************
//The solids must be in /solids directory.
cout << "Export OpenSceneGraph files " << endl;
sys.export_open_scene_graph ();
// ************************************************************************************************

// ************************************************************************************************
//	Export grphics.gnuplot
// ************************************************************************************************
// ************************************************************************************************

	cout << "Export GNUPLOT file" << endl;
	sys.export_gnuplot ( state );
//	sys.export_gnuplot ( state );

// OPTIONS
                                     cout << "" << endl;
                                     cout << "***********************************************" << endl;
                                     cout << "** COMPILED WITH OPTIONS                     **" << endl;
                                     cout << "***********************************************" << endl;
if ( METHOD == LAGRANGE)            {cout << "** Dynamic equations ===> LAGRANGE           **" << endl;	}
else 	if ( METHOD == VIRTUAL_POWER) {cout << "** Dynamic equations ===> VIRTUAL_POWER      **" << endl;	}
if ( ORDER == CMO)                  {cout << "** Matrix Order      ===> CMO                **" << endl;	}
else 	if ( ORDER == RMO)            {cout << "** Matrix Order      ===> RMO                **" << endl;	}
if ( MAPLE == MAPLE_OFF)            {cout << "** Maple             ===> OFF                **" << endl;	}
else 	if ( MAPLE == MAPLE_ON)       {cout << "** Maple             ===> ON                 **" << endl;	}
                                     cout << "***********************************************" << endl;
                                     cout << "** OTHER OPTIONS                             **" << endl;
                                     cout << "***********************************************" << endl;
#ifdef SLIP           
                                     cout << "** SLIP IN CONTACT POINT WHEEL-ROAD          **" << endl;
#endif
#ifndef SLIP
                                     cout << "** ROLLING IN CONTACT POINT WHEEL-ROAD       **" << endl;
#endif
                                     cout << "***********************************************" << endl;
                                     cout << "" << endl;
// ************************************************************************************************

#ifdef RELEASE_1
	sys.export_write_state_file_header_C(state);
	sys.export_write_state_file_C(state);

	sys.export_var_def_H();
	sys.export_var_init_C();
	sys.export_var_def_C();

	sys.export_gen_coord_vect_def_H();
	sys.export_gen_coord_vect_init_C();

	sys.export_gen_vel_vect_def_H();
	sys.export_gen_vel_vect_init_C();

	sys.export_gen_accel_vect_def_H();
	sys.export_gen_accel_vect_init_C();

	sys.export_param_vect_def_H();
	sys.export_param_vect_init_C();

	sys.export_inputs_vect_def_H();
	sys.export_inputs_vect_init_C();

	sys.export_unknowns_vect_def_H();
	sys.export_unknowns_vect_init_C();
#endif

return 0;

}



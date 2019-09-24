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
cout << "*             Puma Serial Robot                *" << endl;
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

	// Rotation angles from root to leaf
	symbol_numeric a1 = *sys.new_Coordinate("a1","da1","dda1", 0.0 , 0.0 , 0.0);
	symbol_numeric a2 = *sys.new_Coordinate("a2","da2","dda2", 0.0 , 0.0 , 0.0);
	symbol_numeric a3 = *sys.new_Coordinate("a3","da3","dda3", 0.0 , 0.0 , 0.0);
	symbol_numeric a4 = *sys.new_Coordinate("a4","da4","dda4", 0.0 , 0.0 , 0.0);
	symbol_numeric a5 = *sys.new_Coordinate("a5","da5","dda5", 0.0 , 0.0 , 0.0);
	symbol_numeric a6 = *sys.new_Coordinate("a6","da6","dda6", 0.0 , 0.0 , 0.0);

	// Velocities
	symbol_numeric *da1=sys.get_Velocity("da1");
	symbol_numeric *da2=sys.get_Velocity("da2");
	symbol_numeric *da3=sys.get_Velocity("da3");
	symbol_numeric *da4=sys.get_Velocity("da4");
	symbol_numeric *da5=sys.get_Velocity("da5");
	symbol_numeric *da6=sys.get_Velocity("da6");

	// Accelerations
	symbol_numeric *dda1=sys.get_Acceleration("dda1");
	symbol_numeric *dda2=sys.get_Acceleration("dda2");
	symbol_numeric *dda3=sys.get_Acceleration("dda3");
	symbol_numeric *dda4=sys.get_Acceleration("dda4");
	symbol_numeric *dda5=sys.get_Acceleration("dda5");
	symbol_numeric *dda6=sys.get_Acceleration("dda6");


// ************************************************************************************************
//	Initial Position Additional Constraint Equations
// ************************************************************************************************

	lst coord_indep_init;
	lst vel_indep_init;

//	coord_indep_init = (x-0.0),(y-0.0),(z-5.0),(a-0.0),(b-0.0),(c-0.0);


// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	
	// Longitud del humero
	symbol_numeric d3 = *sys.new_Parameter("d3",0.4318);

	// Desplazamiento lateral del codo
	symbol_numeric r3 = *sys.new_Parameter("r3",-0.14909);

	// Longitud del antebrazo
	symbol_numeric d4 = *sys.new_Parameter("d4",-0.02032);

	// Longitud del antebrazo
	symbol_numeric r4 = *sys.new_Parameter("r4",-0.4318);
	
	// Numero pi/2 para que las bases concuerden con Denavit-Hartenberg
	symbol_numeric mypi2 = *sys.new_Parameter("mypi2",1.57079632679490);

	

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************


	sys.new_Base("B1","xyz", 0,0,1,a1);		// Rotation wrt z0-z1
	sys.new_Base("B2a","B1", 1,0,0,-mypi2);		// Rotation wrt x1
	sys.new_Base("B2","B2a", 0,0,1,a2);		// Rotation wrt z2
	sys.new_Base("B3","B2a", 0,0,1,a2+a3);		// Rotation wrt z2-z3 (directly from B2a)
	sys.new_Base("B4a","B3", 1,0,0,mypi2);		// Rotation wrt x3
	sys.new_Base("B4","B4a", 0,0,1,a4);		// Rotation wrt z4
	sys.new_Base("B5a","B4", 1,0,0,-mypi2);		// Rotation wrt x4
	sys.new_Base("B5","B5a", 0,0,1,a5);		// Rotation wrt z5
	sys.new_Base("B6a","B5", 1,0,0,mypi2);		// Rotation wrt x5
	sys.new_Base("B6","B6a", 0,0,1,a6);		// Rotation wrt z6


// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	Vector3D OP1  = *sys.new_Vector3D("OP1a", 0, 0,0,"xyz") + *sys.new_Vector3D("OP1b", 0,0,0, "B1");
	Vector3D P1P2 = *sys.new_Vector3D("P1P2a",0, 0,0,"B1")  + *sys.new_Vector3D("P1P2b",0,0,0, "B2");
	Vector3D P2P3 = *sys.new_Vector3D("P2P3a",0, 0,0,"B2")  + *sys.new_Vector3D("P2P3b",0,0,0, "B3");
	Vector3D P3P4 = *sys.new_Vector3D("P3P4a",d3,0,0,"B3")  + *sys.new_Vector3D("P3P4b",0,0,r3,"B4");
	Vector3D P4P5 = *sys.new_Vector3D("P4P5a",d4,0,0,"B4")  + *sys.new_Vector3D("P4P5b",0,0,r4,"B5");
	Vector3D P5P6 = *sys.new_Vector3D("P5P6a",0, 0,0,"B5")  + *sys.new_Vector3D("P5P6b",0,0,0, "B6");
	
// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * P1 = sys.new_Point("P1","O", &OP1);
	Point * P2 = sys.new_Point("P2","P1",&P1P2);
	Point * P3 = sys.new_Point("P3","P2",&P2P3);
	Point * P4 = sys.new_Point("P4","P3",&P3P4);
	Point * P5 = sys.new_Point("P5","P4",&P4P5);
	Point * P6 = sys.new_Point("P6","P5",&P5P6);

// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Inertial parameters of the BAR1
	symbol_numeric  m1 = *sys.new_Parameter("m1",1.0);
	symbol_numeric  mx1 = *sys.new_Parameter("mx1",0.0);
	symbol_numeric  my1 = *sys.new_Parameter("my1",0.0);
	symbol_numeric  mz1 = *sys.new_Parameter("mz1",0.0);
	symbol_numeric  Ixx1 = *sys.new_Parameter("Ixx1",1.0);
	symbol_numeric  Ixy1 = *sys.new_Parameter("Ixy1",0.0);
	symbol_numeric  Iyy1 = *sys.new_Parameter("Iyy1",1.0);
	symbol_numeric  Ixz1 = *sys.new_Parameter("Ixz1",0.0);
	symbol_numeric  Izz1 = *sys.new_Parameter("Izz1",1.0);
	symbol_numeric  Iyz1 = *sys.new_Parameter("Iyz1",0.0);


	// Inertial parameters of the BAR2
	symbol_numeric  m2 = *sys.new_Parameter("m2",1.0);
	symbol_numeric  mx2 = *sys.new_Parameter("mx2",0.0);
	symbol_numeric  my2 = *sys.new_Parameter("my2",0.0);
	symbol_numeric  mz2 = *sys.new_Parameter("mz2",0.0);
	symbol_numeric  Ixx2 = *sys.new_Parameter("Ixx2",1.1);
	symbol_numeric  Ixy2 = *sys.new_Parameter("Ixy2",0.0);
	symbol_numeric  Iyy2 = *sys.new_Parameter("Iyy2",1.0);
	symbol_numeric  Ixz2 = *sys.new_Parameter("Ixz2",0.0);
	symbol_numeric  Izz2 = *sys.new_Parameter("Izz2",1.0);
	symbol_numeric  Iyz2 = *sys.new_Parameter("Iyz2",0.0);

	// Inertial parameters of the BAR3
	symbol_numeric  m3 = *sys.new_Parameter("m3",1.0);
	symbol_numeric  mx3 = *sys.new_Parameter("mx3",0.0);
	symbol_numeric  my3 = *sys.new_Parameter("my3",0.0);
	symbol_numeric  mz3 = *sys.new_Parameter("mz3",0.0);
	symbol_numeric  Ixx3 = *sys.new_Parameter("Ixx3",1.0);
	symbol_numeric  Ixy3 = *sys.new_Parameter("Ixy3",0.0);
	symbol_numeric  Iyy3 = *sys.new_Parameter("Iyy3",1.0);
	symbol_numeric  Ixz3 = *sys.new_Parameter("Ixz3",0.0);
	symbol_numeric  Izz3 = *sys.new_Parameter("Izz3",1.0);
	symbol_numeric  Iyz3 = *sys.new_Parameter("Iyz3",0.0);

	// Inertial parameters of the BAR4
	symbol_numeric  m4 = *sys.new_Parameter("m4",1.0);
	symbol_numeric  mx4 = *sys.new_Parameter("mx4",0.25);
	symbol_numeric  my4 = *sys.new_Parameter("my4",0.0);
	symbol_numeric  mz4 = *sys.new_Parameter("mz4",0.0);
	symbol_numeric  Ixx4 = *sys.new_Parameter("Ixx4",1.0);
	symbol_numeric  Ixy4 = *sys.new_Parameter("Ixy4",0.0);
	symbol_numeric  Iyy4 = *sys.new_Parameter("Iyy4",1.0);
	symbol_numeric  Ixz4 = *sys.new_Parameter("Ixz4",0.0);
	symbol_numeric  Izz4 = *sys.new_Parameter("Izz4",1.0);
	symbol_numeric  Iyz4 = *sys.new_Parameter("Iyz4",0.0);

	// Inertial parameters of the BAR5
	symbol_numeric  m5 = *sys.new_Parameter("m5",1.0);
	symbol_numeric  mx5 = *sys.new_Parameter("mx5",0.25);
	symbol_numeric  my5 = *sys.new_Parameter("my5",0.0);
	symbol_numeric  mz5 = *sys.new_Parameter("mz5",0.0);
	symbol_numeric  Ixx5 = *sys.new_Parameter("Ixx5",1.0);
	symbol_numeric  Ixy5 = *sys.new_Parameter("Ixy5",0.0);
	symbol_numeric  Iyy5 = *sys.new_Parameter("Iyy5",1.0);
	symbol_numeric  Ixz5 = *sys.new_Parameter("Ixz5",0.0);
	symbol_numeric  Izz5 = *sys.new_Parameter("Izz5",1.0);
	symbol_numeric  Iyz5 = *sys.new_Parameter("Iyz5",0.0);

	// Inertial parameters of the BAR6
	symbol_numeric  m6 = *sys.new_Parameter("m6",1.0);
	symbol_numeric  mx6 = *sys.new_Parameter("mx6",0.25);
	symbol_numeric  my6 = *sys.new_Parameter("my6",0.0);
	symbol_numeric  mz6 = *sys.new_Parameter("mz6",0.0);
	symbol_numeric  Ixx6 = *sys.new_Parameter("Ixx6",1.0);
	symbol_numeric  Ixy6 = *sys.new_Parameter("Ixy6",0.0);
	symbol_numeric  Iyy6 = *sys.new_Parameter("Iyy6",1.0);
	symbol_numeric  Ixz6 = *sys.new_Parameter("Ixz6",0.0);
	symbol_numeric  Izz6 = *sys.new_Parameter("Izz6",1.0);
	symbol_numeric  Iyz6 = *sys.new_Parameter("Iyz6",0.0);

	Vector3D P1_G1= *sys.new_Vector3D("P1_G1",mx1/m1,my1/m1,mz1/m1,"B1");
	Vector3D P2_G2= *sys.new_Vector3D("P2_G2",mx2/m2,my2/m2,mz2/m2,"B2");
	Vector3D P3_G3= *sys.new_Vector3D("P3_G3",mx3/m3,my3/m3,mz3/m3,"B3");
	Vector3D P4_G4= *sys.new_Vector3D("P4_G4",mx4/m4,my4/m4,mz4/m4,"B4");
	Vector3D P5_G5= *sys.new_Vector3D("P5_G5",mx5/m5,my5/m5,mz5/m5,"B5");
	Vector3D P6_G6= *sys.new_Vector3D("P6_G6",mx6/m6,my6/m6,mz6/m6,"B6");

	//Inertia Tensors

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

	Frame * Fra_0= sys.new_Frame("Fra_0","O","xyz");
	Frame * Fra_1= sys.new_Frame("Fra_1","P1","B1");
	Frame * Fra_2= sys.new_Frame("Fra_2","P2","B2");
	Frame * Fra_3= sys.new_Frame("Fra_3","P3","B3");
	Frame * Fra_4= sys.new_Frame("Fra_4","P4","B4");
	Frame * Fra_5= sys.new_Frame("Fra_5","P5","B5");
	Frame * Fra_6= sys.new_Frame("Fra_6","P6","B6");


// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	Solid * BAR1 = sys.new_Solid("BAR1","P1","B1","m1","P1_G1","I1");
	Solid * BAR2 = sys.new_Solid("BAR2","P2","B2","m2","P2_G2","I2");
	Solid * BAR3 = sys.new_Solid("BAR3","P3","B3","m3","P3_G3","I3");
	Solid * BAR4 = sys.new_Solid("BAR4","P4","B4","m4","P4_G4","I4");
	Solid * BAR5 = sys.new_Solid("BAR5","P5","B5","m5","P5_G5","I5");
	Solid * BAR6 = sys.new_Solid("BAR6","P6","B6","m6","P6_G6","I6");

// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

	Drawing3D * BAR0_3D = sys.new_Drawing3D("BAR0_3D", "O", "xyz" ,"./solids/solid_0.stl",0,1,0,0.5);
// 	Drawing3D * BAR1_3D = sys.new_Drawing3D("BAR1_3D", BAR1,"./solids/solid_1.stl" ,1,0,0,0.5);
// 	Drawing3D * BAR2_3D = sys.new_Drawing3D("BAR2_3D", BAR2,"./solids/solid_2.stl" ,1,0,0,0.5);
// 	Drawing3D * BAR3_3D = sys.new_Drawing3D("BAR3_3D", BAR3,"./solids/solid_3.stl" ,1,0,0,0.5);
// 	Drawing3D * BAR4_3D = sys.new_Drawing3D("BAR4_3D", BAR4,"./solids/solid_1.stl" ,1,0,0,0.5);
// 	Drawing3D * BAR5_3D = sys.new_Drawing3D("BAR5_3D", BAR5,"./solids/solid_2.stl" ,1,0,0,0.5);
// 	Drawing3D * BAR6_3D = sys.new_Drawing3D("BAR6_3D", BAR6,"./solids/solid_3.stl" ,1,0,0,0.5);

//         Drawing3D * BAR4_3D = sys.new_Drawing3D("BAR4_3D", BAR4,"./solids/barra_mz.stl" ,1,0,0,1.0);
//         Drawing3D * BAR5_3D = sys.new_Drawing3D("BAR5_3D", BAR5,"./solids/barra_mz.stl" ,1,0,0,1.0);
//         Drawing3D * BAR6_3D = sys.new_Drawing3D("BAR6_3D", BAR6,"./solids/barra_mz.stl" ,1,0,0,1.0);

// 	Drawing3D * BALL1A_3D = sys.new_Drawing3D("BALL1A_3D", "A1", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
// 	Drawing3D * BALL2A_3D = sys.new_Drawing3D("BALL2A_3D", "A2", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
// 	Drawing3D * BALL3A_3D = sys.new_Drawing3D("BALL3A_3D", "A3", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
// 	Drawing3D * BALL4A_3D = sys.new_Drawing3D("BALL4A_3D", "A4", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
// 	Drawing3D * BALL5A_3D = sys.new_Drawing3D("BALL5A_3D", "A5", "xyz" ,"./solids/bola.stl",0,0,1,1.0);
// 	Drawing3D * BALL6A_3D = sys.new_Drawing3D("BALL6A_3D", "A6", "xyz" ,"./solids/bola.stl",0,0,1,1.0);

        Drawing3D * Fra_BAR0_3D = sys.new_Drawing3D("Fra_BAR0_3D","Fra_0",0.1);
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

	symbol_numeric Ma1 = *sys.new_Parameter("Ma1",0.0);
	symbol_numeric Ma2 = *sys.new_Parameter("Ma2",0.0);
	symbol_numeric Ma3 = *sys.new_Parameter("Ma3",0.0);
	symbol_numeric Ma4 = *sys.new_Parameter("Ma4",0.0);
	symbol_numeric Ma5 = *sys.new_Parameter("Ma5",0.0);
	symbol_numeric Ma6 = *sys.new_Parameter("Ma6",0.0);

	Vector3D F1 = *sys.new_Vector3D("F1",0.0,0.0,0.0, "xyz");	
	Vector3D F2 = *sys.new_Vector3D("F2",0.0,0.0,0.0, "xyz");	
	Vector3D F3 = *sys.new_Vector3D("F3",0.0,0.0,0.0, "xyz");	
	Vector3D F4 = *sys.new_Vector3D("F4",0.0,0.0,0.0, "xyz");	
	Vector3D F5 = *sys.new_Vector3D("F5",0.0,0.0,0.0, "xyz");	
	Vector3D F6 = *sys.new_Vector3D("F6",0.0,0.0,0.0, "xyz");	

	Vector3D M1 = *sys.new_Vector3D("M1",0.0,0.0,Ma1, "B1");
	Vector3D M2 = *sys.new_Vector3D("M2",0.0,0.0,Ma2, "B2");
	Vector3D M3 = *sys.new_Vector3D("M3",0.0,0.0,Ma3, "B3");
	Vector3D M4 = *sys.new_Vector3D("M4",0.0,0.0,Ma4, "B4");
	Vector3D M5 = *sys.new_Vector3D("M5",0.0,0.0,Ma5, "B5");
	Vector3D M6 = *sys.new_Vector3D("M6",0.0,0.0,Ma6, "B6");

	
	
/**/
// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

// 	//	Gravity
	Wrench3D * Gravity1 = sys.Gravity_Wrench("BAR1");
	Wrench3D * Gravity2 = sys.Gravity_Wrench("BAR2");
	Wrench3D * Gravity3 = sys.Gravity_Wrench("BAR3");
	Wrench3D * Gravity4 = sys.Gravity_Wrench("BAR4");	
	Wrench3D * Gravity5 = sys.Gravity_Wrench("BAR5");
	Wrench3D * Gravity6 = sys.Gravity_Wrench("BAR6");
// 
	//	Inertia
	Wrench3D * Inertia_1 = sys.Inertia_Wrench("BAR1");
	Wrench3D * Inertia_2 = sys.Inertia_Wrench("BAR2");
	Wrench3D * Inertia_3 = sys.Inertia_Wrench("BAR3");
	Wrench3D * Inertia_4 = sys.Inertia_Wrench("BAR4");
	Wrench3D * Inertia_5 = sys.Inertia_Wrench("BAR5");
	Wrench3D * Inertia_6 = sys.Inertia_Wrench("BAR6");
	
	//	External Moments
	Wrench3D * WExternalAction1 = sys.new_Wrench3D ( "WExternalAction1", F1, M1, P1 , BAR1 , "Constitutive") ;
	Wrench3D * WExternalAction2 = sys.new_Wrench3D ( "WExternalAction2", F2, M2, P2 , BAR2 , "Constitutive") ;
	Wrench3D * WExternalAction3 = sys.new_Wrench3D ( "WExternalAction3", F3, M3, P3 , BAR3 , "Constitutive") ;
	Wrench3D * WExternalAction4 = sys.new_Wrench3D ( "WExternalAction4", F4, M4, P4 , BAR4 , "Constitutive") ;
	Wrench3D * WExternalAction5 = sys.new_Wrench3D ( "WExternalAction5", F5, M5, P5 , BAR5 , "Constitutive") ;
	Wrench3D * WExternalAction6 = sys.new_Wrench3D ( "WExternalAction6", F6, M6, P6 , BAR6 , "Constitutive") ;

// 	Wrench3D * WExternalReaction1 = sys.new_Wrench3D ( "WExternalReaction1", -F1, -M1, P1 , GROUND , "Constitutive") ;
	Wrench3D * WExternalReaction2 = sys.new_Wrench3D ( "WExternalReaction2", -F2, -M2, P2 , BAR1 , "Constitutive") ;
	Wrench3D * WExternalReaction3 = sys.new_Wrench3D ( "WExternalReaction3", -F3, -M3, P3 , BAR2 , "Constitutive") ;
	Wrench3D * WExternalReaction4 = sys.new_Wrench3D ( "WExternalReaction4", -F4, -M4, P4 , BAR3 , "Constitutive") ;
	Wrench3D * WExternalReaction5 = sys.new_Wrench3D ( "WExternalReaction5", -F5, -M5, P5 , BAR4 , "Constitutive") ;
	Wrench3D * WExternalReaction6 = sys.new_Wrench3D ( "WExternalReaction6", -F6, -M6, P6 , BAR5 , "Constitutive") ;


	symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");
	symbol_numeric lambda2  = *sys.new_Joint_Unknown("lambda2");
	symbol_numeric lambda3  = *sys.new_Joint_Unknown("lambda3");
	symbol_numeric lambda4  = *sys.new_Joint_Unknown("lambda4");
	symbol_numeric lambda5  = *sys.new_Joint_Unknown("lambda5");
	symbol_numeric lambda6  = *sys.new_Joint_Unknown("lambda6");

	
// ************************************************************************************************
// 	Vectors needed to take diferent Jacobians
// ************************************************************************************************

	cout << "Vectors needed to take diferent Jacobians" << endl;

	Matrix q = sys.Coordinates();
	Matrix dq = sys.Velocities();
	Matrix ddq = sys.Accelerations();
	Matrix pars = sys.Parameters();
// 	Matrix inps = sys.Inputs();
	Matrix unks = sys.Joint_Unknowns();

// ************************************************************************************************
// 	 Parameters for the Trajectory optimization 
// ************************************************************************************************
// // Constante term of the Fourier Series
// 	symbol_numeric  FS001 = *sys.new_Parameter("FS001",0.0);
// 	symbol_numeric  FS002 = *sys.new_Parameter("FS002",0.0);
// 	symbol_numeric  FS003 = *sys.new_Parameter("FS003",0.0);
// 
// // First harmonic of the Fourier Series	
// 	symbol_numeric  FSa11 = *sys.new_Parameter("FSa11",0.0);
// 	symbol_numeric  FSb11 = *sys.new_Parameter("FSb11",0.0);
// 	symbol_numeric  FSa12 = *sys.new_Parameter("FSa12",0.0);
// 	symbol_numeric  FSb12 = *sys.new_Parameter("FSb12",0.0);
// 	symbol_numeric  FSa13 = *sys.new_Parameter("FSa13",0.0);
// 	symbol_numeric  FSb13 = *sys.new_Parameter("FSb13",0.0);
// 
// // Second harmonic of the Fourier Series	
// 	symbol_numeric  FSa21 = *sys.new_Parameter("FSa21",0.0);
// 	symbol_numeric  FSb21 = *sys.new_Parameter("FSb21",0.0);
// 	symbol_numeric  FSa22 = *sys.new_Parameter("FSa22",0.0);
// 	symbol_numeric  FSb22 = *sys.new_Parameter("FSb22",0.0);
// 	symbol_numeric  FSa23 = *sys.new_Parameter("FSa23",0.0);
// 	symbol_numeric  FSb23 = *sys.new_Parameter("FSb23",0.0);
// 	
// // Third harmonic of the Fourier Series	
// 	symbol_numeric  FSa31 = *sys.new_Parameter("FSa31",0.0);
// 	symbol_numeric  FSb31 = *sys.new_Parameter("FSb31",0.0);
// 	symbol_numeric  FSa32 = *sys.new_Parameter("FSa32",0.0);
// 	symbol_numeric  FSb32 = *sys.new_Parameter("FSb32",0.0);
// 	symbol_numeric  FSa33 = *sys.new_Parameter("FSa33",0.0);
// 	symbol_numeric  FSb33 = *sys.new_Parameter("FSb33",0.0);
// 
// // Fourth harmonic of the Fourier Series	
// 	symbol_numeric  FSa41 = *sys.new_Parameter("FSa41",0.0);
// 	symbol_numeric  FSb41 = *sys.new_Parameter("FSb41",0.0);
// 	symbol_numeric  FSa42 = *sys.new_Parameter("FSa42",0.0);
// 	symbol_numeric  FSb42 = *sys.new_Parameter("FSb42",0.0);
// 	symbol_numeric  FSa43 = *sys.new_Parameter("FSa43",0.0);
// 	symbol_numeric  FSb43 = *sys.new_Parameter("FSb43",0.0);

// Values of the parameters for the optimized trajectory: TRAJ_NLCONS2_ML_ml_m149
	symbol_numeric FS001 = *sys.new_Parameter("FS001",0.6365715072);
	symbol_numeric FSa11 = *sys.new_Parameter("FSa11",0.0421179283);
	symbol_numeric FSb11 = *sys.new_Parameter("FSb11",0.1465004093);
	symbol_numeric FSa21 = *sys.new_Parameter("FSa21",0.5200953551);
	symbol_numeric FSb21 = *sys.new_Parameter("FSb21",0.8297717954);
	symbol_numeric FSa31 = *sys.new_Parameter("FSa31",-0.0909767976);
	symbol_numeric FSb31 = *sys.new_Parameter("FSb31",-0.0815749102);
	symbol_numeric FSa41 = *sys.new_Parameter("FSa41",0.0657586756);
	symbol_numeric FSb41 = *sys.new_Parameter("FSb41",0.0318478862);
	symbol_numeric FS002 = *sys.new_Parameter("FS002",2.1949678247);
	symbol_numeric FSa12 = *sys.new_Parameter("FSa12",0.1687813287);
	symbol_numeric FSb12 = *sys.new_Parameter("FSb12",0.0469472610);
	symbol_numeric FSa22 = *sys.new_Parameter("FSa22",0.0573899833);
	symbol_numeric FSb22 = *sys.new_Parameter("FSb22",0.6226686578);
	symbol_numeric FSa32 = *sys.new_Parameter("FSa32",0.5921716784);
	symbol_numeric FSb32 = *sys.new_Parameter("FSb32",-0.0312226589);
	symbol_numeric FSa42 = *sys.new_Parameter("FSa42",-0.0549076395);
	symbol_numeric FSb42 = *sys.new_Parameter("FSb42",0.1115301384);
	symbol_numeric FS003 = *sys.new_Parameter("FS003",0.9093536459);
	symbol_numeric FSa13 = *sys.new_Parameter("FSa13",0.0584208743);
	symbol_numeric FSb13 = *sys.new_Parameter("FSb13",0.2168007101);
	symbol_numeric FSa23 = *sys.new_Parameter("FSa23",0.0195034247);
	symbol_numeric FSb23 = *sys.new_Parameter("FSb23",0.1537680058);
	symbol_numeric FSa33 = *sys.new_Parameter("FSa33",0.1092459085);
	symbol_numeric FSb33 = *sys.new_Parameter("FSb33",0.0310536896);
	symbol_numeric FSa43 = *sys.new_Parameter("FSa43",0.1551979982);
	symbol_numeric FSb43 = *sys.new_Parameter("FSb43",0.3504625854);

	symbol_numeric FS004 = *sys.new_Parameter("FS004",0.6365715072);
	symbol_numeric FSa14 = *sys.new_Parameter("FSa14",0.0421179283);
	symbol_numeric FSb14 = *sys.new_Parameter("FSb14",0.1465004093);
	symbol_numeric FSa24 = *sys.new_Parameter("FSa24",0.5200953551);
	symbol_numeric FSb24 = *sys.new_Parameter("FSb24",0.8297717954);
	symbol_numeric FSa34 = *sys.new_Parameter("FSa34",-0.0909767976);
	symbol_numeric FSb34 = *sys.new_Parameter("FSb34",-0.0815749102);
	symbol_numeric FSa44 = *sys.new_Parameter("FSa44",0.0657586756);
	symbol_numeric FSb44 = *sys.new_Parameter("FSb44",0.0318478862);
	symbol_numeric FS005 = *sys.new_Parameter("FS005",2.1949678247);
	symbol_numeric FSa15 = *sys.new_Parameter("FSa15",0.1687813287);
	symbol_numeric FSb15 = *sys.new_Parameter("FSb15",0.0469472610);
	symbol_numeric FSa25 = *sys.new_Parameter("FSa25",0.0573899833);
	symbol_numeric FSb25 = *sys.new_Parameter("FSb25",0.6226686578);
	symbol_numeric FSa35 = *sys.new_Parameter("FSa35",0.5921716784);
	symbol_numeric FSb35 = *sys.new_Parameter("FSb35",-0.0312226589);
	symbol_numeric FSa45 = *sys.new_Parameter("FSa45",-0.0549076395);
	symbol_numeric FSb45 = *sys.new_Parameter("FSb45",0.1115301384);
	symbol_numeric FS006 = *sys.new_Parameter("FS006",0.9093536459);
	symbol_numeric FSa16 = *sys.new_Parameter("FSa16",0.0584208743);
	symbol_numeric FSb16 = *sys.new_Parameter("FSb16",0.2168007101);
	symbol_numeric FSa26 = *sys.new_Parameter("FSa26",0.0195034247);
	symbol_numeric FSb26 = *sys.new_Parameter("FSb26",0.1537680058);
	symbol_numeric FSa36 = *sys.new_Parameter("FSa36",0.1092459085);
	symbol_numeric FSb36 = *sys.new_Parameter("FSb36",0.0310536896);
	symbol_numeric FSa46 = *sys.new_Parameter("FSa46",0.1551979982);
	symbol_numeric FSb46 = *sys.new_Parameter("FSb46",0.3504625854);
	
// ************************************************************************************************
// 	 Kinematic Equations 
// ************************************************************************************************
	cout << "Kinematic Equations = " << endl;

	Matrix Phi(6,1);

	
	Phi(0,0)=a1-(FS001	+FSa11*sin(t)+FSb11*cos(t)	+FSa21*sin(2*t)+FSb21*cos(2*t)	+FSa31*sin(3*t)+FSb31*cos(3*t)	+FSa41*sin(4*t)+FSb41*cos(4*t));
	Phi(1,0)=a2-(FS002	+FSa12*sin(t)+FSb12*cos(t)	+FSa22*sin(2*t)+FSb22*cos(2*t)	+FSa32*sin(3*t)+FSb32*cos(3*t)	+FSa42*sin(4*t)+FSb42*cos(4*t));
	Phi(2,0)=a3-(FS003	+FSa13*sin(t)+FSb13*cos(t)	+FSa23*sin(2*t)+FSb23*cos(2*t)	+FSa33*sin(3*t)+FSb33*cos(3*t)	+FSa43*sin(4*t)+FSb43*cos(4*t));

	Phi(3,0)=a4-(FS004	+FSa14*sin(t)+FSb14*cos(t)	+FSa24*sin(2*t)+FSb24*cos(2*t)	+FSa34*sin(3*t)+FSb34*cos(3*t)	+FSa44*sin(4*t)+FSb44*cos(4*t));
	Phi(4,0)=a5-(FS005	+FSa15*sin(t)+FSb15*cos(t)	+FSa25*sin(2*t)+FSb25*cos(2*t)	+FSa35*sin(3*t)+FSb35*cos(3*t)	+FSa45*sin(4*t)+FSb45*cos(4*t));
	Phi(5,0)=a6-(FS006	+FSa16*sin(t)+FSb16*cos(t)	+FSa26*sin(2*t)+FSb26*cos(2*t)	+FSa36*sin(3*t)+FSb36*cos(3*t)	+FSa46*sin(4*t)+FSb46*cos(4*t));

// 	Phi(0,0)=a1-(FS001	+FSa11*sin(t)+FSb11*cos(t)	+FSa21*sin(2*t)+FSb21*cos(2*t));
// 	Phi(1,0)=a2-(FS002	+FSa12*sin(t)+FSb12*cos(t)	+FSa22*sin(2*t)+FSb22*cos(2*t));
// 	Phi(2,0)=a3-(FS003	+FSa13*sin(t)+FSb13*cos(t)	+FSa23*sin(2*t)+FSb23*cos(2*t));
	
// 	Phi(3,0)=a4-(FS004	+FSa14*sin(t)+FSb14*cos(t)	+FSa24*sin(2*t)+FSb24*cos(2*t));
// 	Phi(4,0)=a5-(FS005	+FSa15*sin(t)+FSb15*cos(t)	+FSa25*sin(2*t)+FSb25*cos(2*t));
// 	Phi(5,0)=a6-(FS006	+FSa16*sin(t)+FSb16*cos(t)	+FSa26*sin(2*t)+FSb26*cos(2*t));

// 	Matrix dPhiNH(0,1);

// 	cout << "Non-linear Constraint Inequalities" << endl;
// 	
// 	Vector3D ezp = *sys.new_Vector3D("ezp",0,0,1,"BP");
// 	
// 	Vector3D ezb1 = *sys.new_Vector3D("ezb1",0,0,1,"B1");
// 	Vector3D ezb2 = *sys.new_Vector3D("ezb2",0,0,1,"B2");
// 	Vector3D ezb3 = *sys.new_Vector3D("ezb3",0,0,1,"B3");
// 	Vector3D ezb4 = *sys.new_Vector3D("ezb4",0,0,1,"B4");
// 	Vector3D ezb5 = *sys.new_Vector3D("ezb5",0,0,1,"B5");
// 	Vector3D ezb6 = *sys.new_Vector3D("ezb6",0,0,1,"B6");
// 	
// 	Matrix NolinPhi(6,1);
// 	NolinPhi(0,0)=ezp*ezb1;
// 	NolinPhi(1,0)=ezp*ezb2;
// 	NolinPhi(2,0)=ezp*ezb3;
// 	NolinPhi(3,0)=ezp*ezb4;
// 	NolinPhi(4,0)=ezp*ezb5;
// 	NolinPhi(5,0)=ezp*ezb6;
// 
// 	lst new_atom_list_NolinPhi, new_exp_list_NolinPhi;        
// 	matrix_list_optimize (NolinPhi, new_atom_list_NolinPhi, new_exp_list_NolinPhi);
// 	sys.export_Matrix_C("NolinPhi","_NolinPhi",NolinPhi, new_atom_list_NolinPhi, new_exp_list_NolinPhi ,ORDER);
// 	
// 	sys.export_function_MATLAB("NolinPhi", "NolinPhi_", NolinPhi, new_atom_list_NolinPhi, new_exp_list_NolinPhi);
// 
// 	sys.export_function_MATLAB_SYMPY("NolinPhi2", "NolinPhi2_", unatomize(NolinPhi));

// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************

	cout << "Dynamic Equations = " << endl;

	Matrix Dynamic_Equations = sys.GenForceSys("ALL");
	//cout<<Dynamic_Equations<<endl;

	lst inertial_parameters;

	inertial_parameters =	m1, mx1, my1, mz1, Ixx1, Ixy1, Iyy1, Ixz1, Iyz1, Izz1,
				m2, mx2, my2, mz2, Ixx2, Ixy2, Iyy2, Ixz2, Iyz2, Izz2,
				m3, mx3, my3, mz3, Ixx3, Ixy3, Iyy3, Ixz3, Iyz3, Izz3,
				m4, mx4, my4, mz4, Ixx4, Ixy4, Iyy4, Ixz4, Iyz4, Izz4,
				m5, mx5, my5, mz5, Ixx5, Ixy5, Iyy5, Ixz5, Iyz5, Izz5,
				m6, mx6, my6, mz6, Ixx6, Ixy6, Iyy6, Ixz6, Iyz6, Izz6;

// 	syms 	m1 mx1 my1 mz1 Ixx1 Ixy1 Iyy1 Ixz1 Iyz1 Izz1 m2 mx2 my2 mz2 Ixx2 Ixy2 Iyy2 Ixz2 Iyz2 Izz2 m3 mx3 my3 mz3 Ixx3 Ixy3 Iyy3 Ixz3 Iyz3 Izz3 m4 mx4 my4 mz4 Ixx4 Ixy4 Iyy4 Ixz4 Iyz4 Izz4 m5 mx5 my5 mz5 Ixx5 Ixy5 Iyy5 Ixz5 Iyz5 Izz5 m6 mx6 my6 mz6 Ixx6 Ixy6 Iyy6 Ixz6 Iyz6 Izz6 real;
		
//psym=[m1;mx1;my1;mz1;Ixx1;Ixy1;Iyy1;Ixz1;Iyz1;Izz1;m2;mx2;my2;mz2;Ixx2;Ixy2;Iyy2;Ixz2;Iyz2;Izz2;m3;mx3;my3;mz3;Ixx3;Ixy3;Iyy3;Ixz3;Iyz3;Izz3;m4;mx4;my4;mz4;Ixx4;Ixy4;Iyy4;Ixz4;Iyz4;Izz4;m5;mx5;my5;mz5;Ixx5;Ixy5;Iyy5;Ixz5;Iyz5;Izz5;m6;mx6;my6;mz6;Ixx6;Ixy6;Iyy6;Ixz6;Iyz6;Izz6];

	cout << "W and Phiq Matrix Calculation= " << endl;

	Matrix M_inertial_parameters=Matrix(inertial_parameters.nops(),1,inertial_parameters);
	Matrix W = sys.jacobian(Dynamic_Equations.transpose(),M_inertial_parameters);
	Matrix Phiq= sys.jacobian(Phi.transpose(),q);

	
//          cout << "pnum=["<< endl;
// 	for (int i=0;i<inertial_parameters.nops();i++){
// 	  symbol_numeric aux=ex_to<symbol_numeric>(inertial_parameters.op(i));
// 	    cout << aux.get_value() << ";" << endl;
// 	}
//          cout << "];"<< endl;
// 
// 	cout << "psym=["<< endl;
// 	for (int i=0;i<inertial_parameters.nops();i++){
// 	  cout << inertial_parameters.op(i) << ";" << endl;
// 	}
//          cout << "];"<< endl;

// 	cout << "Exporting MATLAB functions with SYMPY" << endl;
	//sys.export_function_MATLAB_SYMPY("Phiq_optim","Phiq_optim_",Phiq);
// 	sys.export_function_MATLAB_SYMPY("W_optim","W_optim_",W);
	 
	cout << "Exporting Matrix W" << endl;
	lst new_atom_list_W, new_exp_list_W;        
	matrix_list_optimize (W, new_atom_list_W, new_exp_list_W);
	sys.export_Matrix_C("W","_W",W, new_atom_list_W, new_exp_list_W ,ORDER);
	sys.export_function_MATLAB("W", "W_", W, new_atom_list_W, new_exp_list_W);

	cout << "Exporting MATLAB functions" << endl;
	sys.export_init_function_MATLAB();


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
	
// 	Usa (necesita que estén definidas) las ecuaciones dinámicas y deriva respecto a qpp y necesita que estén definidos los torsores de inercia
// 	sys.Matrix_Calculation(Phi, coord_indep_init, vel_indep_init, Dynamic_Equations, sys, METHOD);
	
// 	Calcula las matrices M y Q sin las ecuaciones de la dinámica
	sys.Matrix_Calculation( Phi, coord_indep_init, vel_indep_init, sys, METHOD);

// ************************************************************************************************
// 	Export C code for Direct Simulation 
// ************************************************************************************************

	cout << "Export C code for Direct Simulation " << endl;
	sys.export_Dynamic_Simulation(sys, ORDER , MAPLE);
        
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

	cout << "Export ENVIRONMENT file " << endl;

	sys.export_environment_m (  );


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

    	state = 	a1,*da1,*dda1,
		a2,*da2,*dda2,
		a3,*da3,*dda3;
// 		a4,*da4,*dda4,
// 		a5,*da5,*dda5,
// 		a6,*da6,*dda6;

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


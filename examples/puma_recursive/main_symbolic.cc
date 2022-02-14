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
	//symbol_numeric mypi2 = *sys.new_Parameter("mypi2",1.57079632679490);
    //symbol_numeric mypi2 = *sys.new_Parameter("mypi2",1.57079632679490);
	
    ex mypi2 = numeric(1,2)*Pi;

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************


	sys.new_Base("B1","xyz", 0,0,1,a1);		// Rotation wrt z0-z1
	sys.new_Base("B2a","B1", 1,0,0,-mypi2);	// Rotation wrt x1
	sys.new_Base("B2","B2a", 0,0,1,a2);		// Rotation wrt z2
	sys.new_Base("B3","B2a", 0,0,1,a2+a3);	// Rotation wrt z2-z3 (directly from B2a)
	sys.new_Base("B4a","B3", 1,0,0,mypi2);	// Rotation wrt x3
	sys.new_Base("B4","B4a", 0,0,1,a4);		// Rotation wrt z4
	sys.new_Base("B5a","B4", 1,0,0,-mypi2);	// Rotation wrt x4
	sys.new_Base("B5","B5a", 0,0,1,a5);		// Rotation wrt z5
	sys.new_Base("B6a","B5", 1,0,0,mypi2);	// Rotation wrt x5
	sys.new_Base("B6","B6a", 0,0,1,a6);		// Rotation wrt z6


// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

// 	Vector3D OP1  = *sys.new_Vector3D("OP1a", 0, 0,0,"xyz") + *sys.new_Vector3D("OP1b", 0,0,0, "B1");
// 	Vector3D P1P2 = *sys.new_Vector3D("P1P2a",0, 0,0,"B1")  + *sys.new_Vector3D("P1P2b",0,0,0, "B2");
// 	Vector3D P2P3 = *sys.new_Vector3D("P2P3a",0, 0,0,"B2")  + *sys.new_Vector3D("P2P3b",0,0,0, "B3");
// 	Vector3D P3P4 = *sys.new_Vector3D("P3P4a",d3,0,0,"B3")  + *sys.new_Vector3D("P3P4b",0,0,r3,"B4");
// 	Vector3D P4P5 = *sys.new_Vector3D("P4P5a",d4,0,0,"B4")  + *sys.new_Vector3D("P4P5b",0,0,r4,"B5");
// 	Vector3D P5P6 = *sys.new_Vector3D("P5P6a",0, 0,0,"B5")  + *sys.new_Vector3D("P5P6b",0,0,0, "B6");

	Vector3D OP1  = *sys.new_Vector3D("OP1", 0,   0,  0,"xyz") ;
	Vector3D P1P2 = *sys.new_Vector3D("P1P2",0,   0,  0,"B1")  ;
	Vector3D P2P3 = *sys.new_Vector3D("P2P3",d3,  0, r3,"B2")  ;
	Vector3D P3P4 = *sys.new_Vector3D("P3P4",d4,-r4,  0,"B3")  ;
	Vector3D P4P5 = *sys.new_Vector3D("P4P5",0,   0,  0,"B4")  ;
	Vector3D P5P6 = *sys.new_Vector3D("P5P6",0,   0,  0,"B5")  ;

	
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
	symbol_numeric  m1 = *sys.new_Parameter("m1",10.521);
	symbol_numeric  mx1 = *sys.new_Parameter("mx1",0.0);
	symbol_numeric  my1 = *sys.new_Parameter("my1",-0.56813);
	symbol_numeric  mz1 = *sys.new_Parameter("mz1",0.0);
	symbol_numeric  Ixx1 = *sys.new_Parameter("Ixx1",1.64268);
	symbol_numeric  Ixy1 = *sys.new_Parameter("Ixy1",0.0);
	symbol_numeric  Ixz1 = *sys.new_Parameter("Ixz1",0.0);
	symbol_numeric  Iyy1 = *sys.new_Parameter("Iyy1",0.5091);
	symbol_numeric  Iyz1 = *sys.new_Parameter("Iyz1",0.0);
	symbol_numeric  Izz1 = *sys.new_Parameter("Izz1",1.64268);

	// Inertial parameters of the BAR2
	symbol_numeric  m2 = *sys.new_Parameter("m2",15.781);
	symbol_numeric  mx2 = *sys.new_Parameter("mx2",2.20618);
	symbol_numeric  my2 = *sys.new_Parameter("my2",0.2);
	symbol_numeric  mz2 = *sys.new_Parameter("mz2",2.35279);
	symbol_numeric  Ixx2 = *sys.new_Parameter("Ixx2",0.84058);
	symbol_numeric  Ixy2 = *sys.new_Parameter("Ixy2",0.2);
	symbol_numeric  Ixz2 = *sys.new_Parameter("Ixz2",-0.32892);
	symbol_numeric  Iyy2 = *sys.new_Parameter("Iyy2",8.7375);
	symbol_numeric  Iyz2 = *sys.new_Parameter("Iyz2",0.4);
	symbol_numeric  Izz2 = *sys.new_Parameter("Izz2",8.57562);

	// Inertial parameters of the BAR3
	symbol_numeric  m3 = *sys.new_Parameter("m3",8.767);
	symbol_numeric  mx3 = *sys.new_Parameter("mx3",-0.00281);
	symbol_numeric  my3 = *sys.new_Parameter("my3",-1.7271);
	symbol_numeric  mz3 = *sys.new_Parameter("mz3",0.0);
	symbol_numeric  Ixx3 = *sys.new_Parameter("Ixx3",3.71704);
	symbol_numeric  Ixy3 = *sys.new_Parameter("Ixy3",-0.00055);
	symbol_numeric  Ixz3 = *sys.new_Parameter("Ixz3",0.002);
	symbol_numeric  Iyy3 = *sys.new_Parameter("Iyy3",0.3009);
	symbol_numeric  Iyz3 = *sys.new_Parameter("Iyz3",0.002);
	symbol_numeric  Izz3 = *sys.new_Parameter("Izz3",3.71704);

	// Inertial parameters of the BAR4
	symbol_numeric  m4 = *sys.new_Parameter("m4",1.052);
	symbol_numeric  mx4 = *sys.new_Parameter("mx4",0.03);
	symbol_numeric  my4 = *sys.new_Parameter("my4",0.06);
	symbol_numeric  mz4 = *sys.new_Parameter("mz4",-0.05996);
	symbol_numeric  Ixx4 = *sys.new_Parameter("Ixx4",0.18442);
	symbol_numeric  Ixy4 = *sys.new_Parameter("Ixy4",0.0001);
	symbol_numeric  Ixz4 = *sys.new_Parameter("Ixz4",0.0);
	symbol_numeric  Iyy4 = *sys.new_Parameter("Iyy4",0.18442);
	symbol_numeric  Iyz4 = *sys.new_Parameter("Iyz4",0.0001);
	symbol_numeric  Izz4 = *sys.new_Parameter("Izz4",0.1273);

	// Inertial parameters of the BAR5
	symbol_numeric  m5 = *sys.new_Parameter("m5",1.052);
	symbol_numeric  mx5 = *sys.new_Parameter("mx5",0.004);
	symbol_numeric  my5 = *sys.new_Parameter("my5",-0.00736);
	symbol_numeric  mz5 = *sys.new_Parameter("mz5",0.005);
	symbol_numeric  Ixx5 = *sys.new_Parameter("Ixx5",0.07355);
	symbol_numeric  Ixy5 = *sys.new_Parameter("Ixy5",0.0001);
	symbol_numeric  Ixz5 = *sys.new_Parameter("Ixz5",0.0001);
	symbol_numeric  Iyy5 = *sys.new_Parameter("Iyy5",0.0735);
	symbol_numeric  Iyz5 = *sys.new_Parameter("Iyz5",0.0001);
	symbol_numeric  Izz5 = *sys.new_Parameter("Izz5",0.12735);

	// Inertial parameters of the BAR6
	symbol_numeric  m6 = *sys.new_Parameter("m6",0.351);
	symbol_numeric  mx6 = *sys.new_Parameter("mx6",0.01);
	symbol_numeric  my6 = *sys.new_Parameter("my6",0.02);
	symbol_numeric  mz6 = *sys.new_Parameter("mz6",0.01308);
	symbol_numeric  Ixx6 = *sys.new_Parameter("Ixx6",0.00759);
	symbol_numeric  Ixy6 = *sys.new_Parameter("Ixy6",0.0002);
	symbol_numeric  Ixz6 = *sys.new_Parameter("Ixz6",0.0002);
	symbol_numeric  Iyy6 = *sys.new_Parameter("Iyy6",0.00759);
	symbol_numeric  Iyz6 = *sys.new_Parameter("Iyz6",0.0002);
	symbol_numeric  Izz6 = *sys.new_Parameter("Izz6",0.0141);

	Vector3D P1_G1= *sys.new_Vector3D("P1_G1",mx1/m1,my1/m1,mz1/m1,"B1");
	Vector3D P2_G2= *sys.new_Vector3D("P2_G2",mx2/m2,my2/m2,mz2/m2,"B2");
	Vector3D P3_G3= *sys.new_Vector3D("P3_G3",mx3/m3,my3/m3,mz3/m3,"B3");
	Vector3D P4_G4= *sys.new_Vector3D("P4_G4",mx4/m4,my4/m4,mz4/m4,"B4");
	Vector3D P5_G5= *sys.new_Vector3D("P5_G5",mx5/m5,my5/m5,mz5/m5,"B5");
	Vector3D P6_G6= *sys.new_Vector3D("P6_G6",mx6/m6,my6/m6,mz6/m6,"B6");

// 	-----------------------------------------------------------------------
// 	-----------------------------------------------------------------------
// 	THE INERTIAL PARAMETERS IDENTIFIED IN THE THESIS OF FRANCESC BENIMELLI.
// 	SOME OF THE PARAMETERS ARE ZERO.
// 	-----------------------------------------------------------------------
// 	-----------------------------------------------------------------------
// 	// Inertial parameters of the BAR1
// 	symbol_numeric  m1 = *sys.new_Parameter("m1",10.521);
// 	symbol_numeric  mx1 = *sys.new_Parameter("mx1",0.0);
// 	symbol_numeric  my1 = *sys.new_Parameter("my1",-0.56813);
// 	symbol_numeric  mz1 = *sys.new_Parameter("mz1",0.0);
// 	symbol_numeric  Ixx1 = *sys.new_Parameter("Ixx1",1.64268);
// 	symbol_numeric  Ixy1 = *sys.new_Parameter("Ixy1",0.0);
// 	symbol_numeric  Ixz1 = *sys.new_Parameter("Ixz1",0.0);
// 	symbol_numeric  Iyy1 = *sys.new_Parameter("Iyy1",0.5091);
// 	symbol_numeric  Iyz1 = *sys.new_Parameter("Iyz1",0.0);
// 	symbol_numeric  Izz1 = *sys.new_Parameter("Izz1",1.64268);
// 
// 	// Inertial parameters of the BAR2
// 	symbol_numeric  m2 = *sys.new_Parameter("m2",15.781);
// 	symbol_numeric  mx2 = *sys.new_Parameter("mx2",2.20618);
// 	symbol_numeric  my2 = *sys.new_Parameter("my2",0.0);
// 	symbol_numeric  mz2 = *sys.new_Parameter("mz2",2.35279);
// 	symbol_numeric  Ixx2 = *sys.new_Parameter("Ixx2",0.84058);
// 	symbol_numeric  Ixy2 = *sys.new_Parameter("Ixy2",0.0);
// 	symbol_numeric  Ixz2 = *sys.new_Parameter("Ixz2",-0.32892);
// 	symbol_numeric  Iyy2 = *sys.new_Parameter("Iyy2",8.7375);
// 	symbol_numeric  Iyz2 = *sys.new_Parameter("Iyz2",0.0);
// 	symbol_numeric  Izz2 = *sys.new_Parameter("Izz2",8.57562);
// 
// 	// Inertial parameters of the BAR3
// 	symbol_numeric  m3 = *sys.new_Parameter("m3",8.767);
// 	symbol_numeric  mx3 = *sys.new_Parameter("mx3",-0.00281);
// 	symbol_numeric  my3 = *sys.new_Parameter("my3",-1.7271);
// 	symbol_numeric  mz3 = *sys.new_Parameter("mz3",0.0);
// 	symbol_numeric  Ixx3 = *sys.new_Parameter("Ixx3",3.71704);
// 	symbol_numeric  Ixy3 = *sys.new_Parameter("Ixy3",-0.00055);
// 	symbol_numeric  Ixz3 = *sys.new_Parameter("Ixz3",0.0);
// 	symbol_numeric  Iyy3 = *sys.new_Parameter("Iyy3",0.3009);
// 	symbol_numeric  Iyz3 = *sys.new_Parameter("Iyz3",0.0);
// 	symbol_numeric  Izz3 = *sys.new_Parameter("Izz3",3.71704);
// 
// 	// Inertial parameters of the BAR4
// 	symbol_numeric  m4 = *sys.new_Parameter("m4",1.052);
// 	symbol_numeric  mx4 = *sys.new_Parameter("mx4",0.0);
// 	symbol_numeric  my4 = *sys.new_Parameter("my4",0.0);
// 	symbol_numeric  mz4 = *sys.new_Parameter("mz4",-0.05996);
// 	symbol_numeric  Ixx4 = *sys.new_Parameter("Ixx4",0.18442);
// 	symbol_numeric  Ixy4 = *sys.new_Parameter("Ixy4",0.0);
// 	symbol_numeric  Ixz4 = *sys.new_Parameter("Ixz4",0.0);
// 	symbol_numeric  Iyy4 = *sys.new_Parameter("Iyy4",0.18442);
// 	symbol_numeric  Iyz4 = *sys.new_Parameter("Iyz4",0.0);
// 	symbol_numeric  Izz4 = *sys.new_Parameter("Izz4",0.1273);
// 
// 	// Inertial parameters of the BAR5
// 	symbol_numeric  m5 = *sys.new_Parameter("m5",1.052);
// 	symbol_numeric  mx5 = *sys.new_Parameter("mx5",0.0);
// 	symbol_numeric  my5 = *sys.new_Parameter("my5",-0.00736);
// 	symbol_numeric  mz5 = *sys.new_Parameter("mz5",0.0);
// 	symbol_numeric  Ixx5 = *sys.new_Parameter("Ixx5",0.07355);
// 	symbol_numeric  Ixy5 = *sys.new_Parameter("Ixy5",0.0);
// 	symbol_numeric  Ixz5 = *sys.new_Parameter("Ixz5",0.0);
// 	symbol_numeric  Iyy5 = *sys.new_Parameter("Iyy5",0.0735);
// 	symbol_numeric  Iyz5 = *sys.new_Parameter("Iyz5",0.0);
// 	symbol_numeric  Izz5 = *sys.new_Parameter("Izz5",0.12735);
// 
// 	// Inertial parameters of the BAR6
// 	symbol_numeric  m6 = *sys.new_Parameter("m6",0.351);
// 	symbol_numeric  mx6 = *sys.new_Parameter("mx6",0.0);
// 	symbol_numeric  my6 = *sys.new_Parameter("my6",0.0);
// 	symbol_numeric  mz6 = *sys.new_Parameter("mz6",0.01308);
// 	symbol_numeric  Ixx6 = *sys.new_Parameter("Ixx6",0.00759);
// 	symbol_numeric  Ixy6 = *sys.new_Parameter("Ixy6",0.0);
// 	symbol_numeric  Ixz6 = *sys.new_Parameter("Ixz6",0.0);
// 	symbol_numeric  Iyy6 = *sys.new_Parameter("Iyy6",0.00759);
// 	symbol_numeric  Iyz6 = *sys.new_Parameter("Iyz6",0.0);
// 	symbol_numeric  Izz6 = *sys.new_Parameter("Izz6",0.0141);
// 
// 	Vector3D P1_G1= *sys.new_Vector3D("P1_G1",mx1/m1,my1/m1,mz1/m1,"B1");
// 	Vector3D P2_G2= *sys.new_Vector3D("P2_G2",mx2/m2,my2/m2,mz2/m2,"B2");
// 	Vector3D P3_G3= *sys.new_Vector3D("P3_G3",mx3/m3,my3/m3,mz3/m3,"B3");
// 	Vector3D P4_G4= *sys.new_Vector3D("P4_G4",mx4/m4,my4/m4,mz4/m4,"B4");
// 	Vector3D P5_G5= *sys.new_Vector3D("P5_G5",mx5/m5,my5/m5,mz5/m5,"B5");
// 	Vector3D P6_G6= *sys.new_Vector3D("P6_G6",mx6/m6,my6/m6,mz6/m6,"B6");

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

	//Drawing3D * BAR0_3D = sys.new_Drawing3D("BAR0_3D", "O", "xyz" ,"./solids/puma_link1.stl",0,1,0,0.5);
 	//Drawing3D * BAR1_3D = sys.new_Drawing3D("BAR1_3D", BAR1,"./solids/puma_link2.stl" ,1,0,0,0.5);
 	//Drawing3D * BAR2_3D = sys.new_Drawing3D("BAR2_3D", BAR2,"./solids/puma_link3.stl" ,1,0,0,0.5);
 	//Drawing3D * BAR3_3D = sys.new_Drawing3D("BAR3_3D", BAR3,"./solids/solid_3.stl" ,1,0,0,0.5);
 	//Drawing3D * BAR4_3D = sys.new_Drawing3D("BAR4_3D", BAR4,"./solids/solid_1.stl" ,1,0,0,0.5);
 	//Drawing3D * BAR5_3D = sys.new_Drawing3D("BAR5_3D", BAR5,"./solids/solid_2.stl" ,1,0,0,0.5);
 	//Drawing3D * BAR6_3D = sys.new_Drawing3D("BAR6_3D", BAR6,"./solids/solid_3.stl" ,1,0,0,0.5);







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

// Values of the parameters for the optimized trajectory: TRAJ_NLCONS3_COND_ml_m288_cond_007_detmax_0276_tr_579461_F
	symbol_numeric FS001 = *sys.new_Parameter("FS001",0.0014785881);
	symbol_numeric FSa11 = *sys.new_Parameter("FSa11",0.0772103847);
	symbol_numeric FSb11 = *sys.new_Parameter("FSb11",-0.0422727128);
	symbol_numeric FSa21 = *sys.new_Parameter("FSa21",0.1185062166);
	symbol_numeric FSb21 = *sys.new_Parameter("FSb21",0.2490842835);
	symbol_numeric FSa31 = *sys.new_Parameter("FSa31",0.0160130460);
	symbol_numeric FSb31 = *sys.new_Parameter("FSb31",-0.6035003875);
	symbol_numeric FSa41 = *sys.new_Parameter("FSa41",-0.3734069362);
	symbol_numeric FSb41 = *sys.new_Parameter("FSb41",0.0129732280);
	symbol_numeric FS002 = *sys.new_Parameter("FS002",0.4654803324);
	symbol_numeric FSa12 = *sys.new_Parameter("FSa12",0.0088854952);
	symbol_numeric FSb12 = *sys.new_Parameter("FSb12",0.1920407194);
	symbol_numeric FSa22 = *sys.new_Parameter("FSa22",-0.3873523313);
	symbol_numeric FSb22 = *sys.new_Parameter("FSb22",-0.1105241080);
	symbol_numeric FSa32 = *sys.new_Parameter("FSa32",0.5153370186);
	symbol_numeric FSb32 = *sys.new_Parameter("FSb32",0.0769221848);
	symbol_numeric FSa42 = *sys.new_Parameter("FSa42",0.3625104022);
	symbol_numeric FSb42 = *sys.new_Parameter("FSb42",-0.5777986794);
	symbol_numeric FS003 = *sys.new_Parameter("FS003",0.5237817800);
	symbol_numeric FSa13 = *sys.new_Parameter("FSa13",-0.1569219959);
	symbol_numeric FSb13 = *sys.new_Parameter("FSb13",-0.1406806629);
	symbol_numeric FSa23 = *sys.new_Parameter("FSa23",0.3347473681);
	symbol_numeric FSb23 = *sys.new_Parameter("FSb23",-0.0804270311);
	symbol_numeric FSa33 = *sys.new_Parameter("FSa33",-0.3319395857);
	symbol_numeric FSb33 = *sys.new_Parameter("FSb33",0.2922779707);
	symbol_numeric FSa43 = *sys.new_Parameter("FSa43",0.1780271484);
	symbol_numeric FSb43 = *sys.new_Parameter("FSb43",-0.1064029430);
	symbol_numeric FS004 = *sys.new_Parameter("FS004",-0.1300356659);
	symbol_numeric FSa14 = *sys.new_Parameter("FSa14",-0.1697189719);
	symbol_numeric FSb14 = *sys.new_Parameter("FSb14",-0.2150556436);
	symbol_numeric FSa24 = *sys.new_Parameter("FSa24",-0.0020729891);
	symbol_numeric FSb24 = *sys.new_Parameter("FSb24",-0.0004944441);
	symbol_numeric FSa34 = *sys.new_Parameter("FSa34",-0.0014969756);
	symbol_numeric FSb34 = *sys.new_Parameter("FSb34",0.0006950233);
	symbol_numeric FSa44 = *sys.new_Parameter("FSa44",-0.0000296446);
	symbol_numeric FSb44 = *sys.new_Parameter("FSb44",0.0000631730);
	symbol_numeric FS005 = *sys.new_Parameter("FS005",0.0000018753);
	symbol_numeric FSa15 = *sys.new_Parameter("FSa15",0.0000008765);
	symbol_numeric FSb15 = *sys.new_Parameter("FSb15",0.0000001033);
	symbol_numeric FSa25 = *sys.new_Parameter("FSa25",0.0000026831);
	symbol_numeric FSb25 = *sys.new_Parameter("FSb25",0.0000015967);
	symbol_numeric FSa35 = *sys.new_Parameter("FSa35",0.0000010124);
	symbol_numeric FSb35 = *sys.new_Parameter("FSb35",0.0000013374);
	symbol_numeric FSa45 = *sys.new_Parameter("FSa45",0.0000008808);
	symbol_numeric FSb45 = *sys.new_Parameter("FSb45",0.0000007891);
	symbol_numeric FS006 = *sys.new_Parameter("FS006",0.0000040158);
	symbol_numeric FSa16 = *sys.new_Parameter("FSa16",0.0000019405);
	symbol_numeric FSb16 = *sys.new_Parameter("FSb16",0.0000007031);
	symbol_numeric FSa26 = *sys.new_Parameter("FSa26",0.0000017516);
	symbol_numeric FSb26 = *sys.new_Parameter("FSb26",0.0000017049);
	symbol_numeric FSa36 = *sys.new_Parameter("FSa36",0.0000030302);
	symbol_numeric FSb36 = *sys.new_Parameter("FSb36",0.0000030832);
	symbol_numeric FSa46 = *sys.new_Parameter("FSa46",0.0000014203);
	symbol_numeric FSb46 = *sys.new_Parameter("FSb46",0.0000001722);




	
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

	cout << "Dynamic Equations " << endl;

	//Matrix Dynamic_Equations = sys.GenForceSys("ALL");

	lst inertial_parameters;

	inertial_parameters =	{
                            m1, mx1, my1, mz1, Ixx1, Ixy1, Iyy1, Ixz1, Iyz1, Izz1,
                            m2, mx2, my2, mz2, Ixx2, Ixy2, Iyy2, Ixz2, Iyz2, Izz2,
                            m3, mx3, my3, mz3, Ixx3, Ixy3, Iyy3, Ixz3, Iyz3, Izz3,
                            m4, mx4, my4, mz4, Ixx4, Ixy4, Iyy4, Ixz4, Iyz4, Izz4,
                            m5, mx5, my5, mz5, Ixx5, Ixy5, Iyy5, Ixz5, Iyz5, Izz5,
                            m6, mx6, my6, mz6, Ixx6, Ixy6, Iyy6, Ixz6, Iyz6, Izz6
                            };

// 	syms 	m1 mx1 my1 mz1 Ixx1 Ixy1 Ixz1 Iyy1 Iyz1 Izz1 m2 mx2 my2 mz2 Ixx2 Ixy2 Ixz2 Iyy2 Iyz2 Izz2 m3 mx3 my3 mz3 Ixx3 Ixy3 Ixz3 Iyy3 Iyz3 Izz3 m4 mx4 my4 mz4 Ixx4 Ixy4 Ixz4 Iyy4 Iyz4 Izz4 m5 mx5 my5 mz5 Ixx5 Ixy5 Ixz5 Iyy5 Iyz5 Izz5 m6 mx6 my6 mz6 Ixx6 Ixy6 Ixz6 Iyy6 Iyz6 Izz6 real;



	Matrix M_inertial_parameters=Matrix(inertial_parameters.nops(),1,inertial_parameters);
	//Matrix W = sys.jacobian(Dynamic_Equations.transpose(),M_inertial_parameters);




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
// 	Recursive
// ************************************************************************************************

symbol_numeric  g = *sys.new_Parameter("g",9.8);
// FORWARD ITERATION

gravity =  UP;

Vector3D OMEGA0  = *sys.new_Vector3D("OMEGA0",0,0,0,"xyz") ;
Vector3D dOMEGA0 = sys.Dt(OMEGA0,Base_xyz );
Matrix U0 (3,3); U0(0,0) = 0; U0(0,1) = 0;U0(0,2) = 0; U0(1,0) = 0; U0(1,1) = 0; U0(1,2) = 0; U0(2,0) = 0; U0(2,1) = 0; U0(2,2) = 0;
Vector3D dV0 = *sys.new_Vector3D("dV0",0,0,-g,"xyz") ;


// SOLID 1
Vector3D OMEGA0__1  = OMEGA0.in_Base(BAR1->get_Base());
Vector3D OMEGA01 = sys.Angular_Velocity(Base_xyz,BAR1->get_Base());
Vector3D OMEGA1 = OMEGA0__1 + OMEGA01;
Vector3D dOMEGA1 =  dOMEGA0.in_Base(BAR1->get_Base()) + sys.dt(OMEGA01) + (OMEGA1^OMEGA01);
Matrix U1 =  dOMEGA1.skew() + OMEGA1.skew()*OMEGA1.skew();
gravity=DOWN;Vector3D r01 = sys.Position_Vector(Point_O,P1);gravity =  UP;
Vector3D U0r01(U0*r01, r01.get_Base() );
U0r01.set_System ( &sys );
 
Vector3D dV1 = (dV0 + U0r01).in_Base(BAR1->get_Base());// + 0;
//Vector3D m1U1r1G1(m1*U0*P1_G1, P1_G1.get_Base() );
//m1U1r1G1.set_System ( &sys ); 
Vector3D D1= *sys.new_Vector3D("D1",mx1,my1,mz1,"B1");
Vector3D U1d1(U1*D1, D1.get_Base() );
U1d1.set_System ( &sys ); 
Vector3D ifi1 = m1*dV1 + U1d1;
Vector3D ini1 = I1*dOMEGA1 + (OMEGA1 ^ (I1* OMEGA1))+ (D1^ dV1);





// SOLID 2
Vector3D OMEGA1__2  = OMEGA1.in_Base(BAR2->get_Base());
Vector3D OMEGA21 = sys.Angular_Velocity(BAR1->get_Base(),BAR2->get_Base());  
Vector3D OMEGA2 = OMEGA1__2 + OMEGA21;
Vector3D dOMEGA2 =  dOMEGA1.in_Base(BAR2->get_Base()) + sys.dt(OMEGA21) + (OMEGA2^OMEGA21);
Matrix U2 =  dOMEGA2.skew() + OMEGA2.skew()*OMEGA2.skew();
gravity=DOWN;Vector3D r12 = sys.Position_Vector(P1,P2);gravity =  UP;
Vector3D U1r12(U1*r12, r12.get_Base() );
U1r12.set_System ( &sys ); 
Vector3D dV2 = (dV1 + U1r12).in_Base(BAR2->get_Base());
//Vector3D m2U2r2G2(U2*P2_G2, P2_G2.get_Base() );
//m2U2r2G2.set_System ( &sys );
Vector3D D2= *sys.new_Vector3D("D2",mx2,my2,mz2,"B2");
Vector3D U2d2(U2*D2, D2.get_Base() );
U2d2.set_System ( &sys );
//Vector3D ifi2 = m2*dV2 +m2U2r2G2;
//Vector3D ini2 = I2*dOMEGA2 + (OMEGA2 ^ (I2* OMEGA2)) + ((m2*P2_G2)^ dV2);
Vector3D ifi2 = m2*dV2 +U2d2;
Vector3D ini2 = I2*dOMEGA2 + (OMEGA2 ^ (I2* OMEGA2)) + (D2^ dV2);

// SOLID 3
Vector3D OMEGA2__3  = OMEGA2.in_Base(BAR3->get_Base());
Vector3D OMEGA32 = (sys.Angular_Velocity(BAR2->get_Base(),BAR3->get_Base())).in_Base(BAR3->get_Base()); 
Vector3D OMEGA3 = OMEGA2__3 + OMEGA32;
Vector3D dOMEGA3 =  dOMEGA2.in_Base(BAR3->get_Base()) + sys.dt(OMEGA32) + (OMEGA3^OMEGA32);
Matrix U3 =  dOMEGA3.skew() + OMEGA3.skew()*OMEGA3.skew();
gravity=DOWN;Vector3D r23 = sys.Position_Vector(P2,P3);gravity =  UP;
Vector3D U2r23(U2*r23, r23.get_Base() );
U2r23.set_System ( &sys ); 
Vector3D dV3 = (dV2 + U2r23).in_Base(BAR3->get_Base());
//Vector3D m3U3r3G3(m3*U3*P3_G3, P3_G3.get_Base() );
//m3U3r3G3.set_System ( &sys ); 
//Vector3D ifi3 = m3*dV3 +m3U3r3G3;
//Vector3D ini3 = sys.dt(I3*OMEGA3) + (OMEGA3 ^ (I3* OMEGA3)) + ((m3*P3_G3)^ dV3);
Vector3D D3= *sys.new_Vector3D("d3",mx3,my3,mz3,"B3");
Vector3D U3d3(U3*D3, D3.get_Base() );
U3d3.set_System ( &sys );
Vector3D ifi3 = m3*dV3 +U3d3;
Vector3D ini3 = sys.dt(I3*OMEGA3) + (OMEGA3 ^ (I3* OMEGA3)) + (D3^ dV3);


// SOLID 4
Vector3D OMEGA3__4  = OMEGA3.in_Base(BAR4->get_Base());
Vector3D OMEGA43 = (sys.Angular_Velocity(BAR3->get_Base(),BAR4->get_Base())).in_Base(BAR4->get_Base()); 
Vector3D OMEGA4 = OMEGA3__4 + OMEGA43;
Vector3D dOMEGA4 =  dOMEGA3.in_Base(BAR4->get_Base()) + sys.dt(OMEGA43) + (OMEGA4^OMEGA43);
Matrix U4 =  dOMEGA4.skew() + OMEGA4.skew()*OMEGA4.skew();
gravity=DOWN;Vector3D r34 = sys.Position_Vector(P3,P4);gravity =  UP;
Vector3D U3r34(U3*r34, r34.get_Base() );
U3r34.set_System ( &sys ); 
Vector3D dV4 = (dV3 + U3r34).in_Base(BAR4->get_Base());
//Vector3D m4U4r4G4(m4*U4*P4_G4, P4_G4.get_Base() );
//m4U4r4G4.set_System ( &sys ); 
//Vector3D ifi4 = m4*dV4 +m4U4r4G4;
//Vector3D ini4 = I4*dOMEGA4 + (OMEGA4 ^ (I4* OMEGA4))+ ((m4*P4_G4)^ dV4);
Vector3D D4= *sys.new_Vector3D("D4",mx4,my4,mz4,"B4");
Vector3D U4d4(U4*D4, D4.get_Base() );
U4d4.set_System ( &sys );
Vector3D ifi4 = m4*dV4 +U4d4;
Vector3D ini4 = I4*dOMEGA4 + (OMEGA4 ^ (I4* OMEGA4))+ (D4^ dV4);



// SOLID 5
Vector3D OMEGA4__5  = OMEGA4.in_Base(BAR5->get_Base());
Vector3D OMEGA54 =  sys.Angular_Velocity(BAR4->get_Base(),BAR5->get_Base()); 
Vector3D OMEGA5 = OMEGA4__5 + OMEGA54;
Vector3D dOMEGA5 =  dOMEGA4.in_Base(BAR5->get_Base()) + sys.dt(OMEGA54) + (OMEGA5^OMEGA54);
Matrix U5 =  dOMEGA5.skew() + OMEGA5.skew()*OMEGA5.skew();
gravity=DOWN;Vector3D r45 = sys.Position_Vector(P4,P5);gravity =  UP;
Vector3D U4r45(U4*r45, r45.get_Base() );
U4r45.set_System ( &sys ); 
Vector3D dV5 = (dV4 + U4r45).in_Base(BAR5->get_Base());
//Vector3D m5U5r5G5(m5*U5*P5_G5, P5_G5.get_Base() );
//m5U5r5G5.set_System ( &sys ); 
//Vector3D ifi5 = m5*dV5 +m5U5r5G5;
//Vector3D ini5 = I5*dOMEGA5 + (OMEGA5 ^ (I5* OMEGA5))+ ((m5*P5_G5)^ dV5);
Vector3D D5= *sys.new_Vector3D("D5",mx5,my5,mz5,"B5");
Vector3D U5d5(U5*D5, D5.get_Base() );
U5d5.set_System ( &sys );
Vector3D ifi5 = m5*dV5 +U5d5;
Vector3D ini5 = I5*dOMEGA5 + (OMEGA5 ^ (I5* OMEGA5))+ (D5^ dV5);



// SOLID 6
Vector3D OMEGA5__6  = OMEGA5.in_Base(BAR6->get_Base());
Vector3D OMEGA65 =  sys.Angular_Velocity(BAR5->get_Base(),BAR6->get_Base());
Vector3D OMEGA6 = OMEGA5__6 + OMEGA65;
Vector3D dOMEGA6 =  dOMEGA5.in_Base(BAR6->get_Base()) + sys.dt(OMEGA65) + (OMEGA6^OMEGA65);
Matrix U6 =  dOMEGA6.skew() + OMEGA6.skew()*OMEGA6.skew();
gravity=DOWN;Vector3D r56 = sys.Position_Vector(P5,P6);gravity =  UP;
Vector3D U5r56(U5*r56, r56.get_Base() );
U5r56.set_System ( &sys ); 
Vector3D dV6 = (dV5 + U5r56).in_Base(BAR6->get_Base());
//Vector3D m6U6r6G6(m6*U6*P6_G6, P6_G6.get_Base() );
//m6U6r6G6.set_System ( &sys ); 
//Vector3D ifi6 = m6*dV6 + m6U6r6G6;
//Vector3D ini6 = I6*dOMEGA6 + (OMEGA6 ^ (I6* OMEGA6))+ ((m6*P6_G6)^ dV6);
Vector3D D6= *sys.new_Vector3D("D6",mx6,my6,mz6,"B6");
Vector3D U6d6(U6*D6, D6.get_Base() );
U6d6.set_System ( &sys );
Vector3D ifi6 = m6*dV6 +U6d6;
Vector3D ini6 = I6*dOMEGA6 + (OMEGA6 ^ (I6* OMEGA6))+ (D6^ dV6);

gravity=DOWN;






// BACKWARD ITERATION
Vector3D fi7 =*sys.new_Vector3D("fi7",0,0,0,BAR6->get_Base()->get_name()) ;
Vector3D ni7 =*sys.new_Vector3D("ni7",0,0,0,BAR6->get_Base()->get_name()) ;

// SOLID 6
Vector3D fi6 = fi7.in_Base(BAR6->get_Base()) + ifi6;
Vector3D ni6 = ni7.in_Base(BAR6->get_Base()) + ini6 ; // + P5P7 ^fi7

// SOLID 5
Vector3D fi5 = fi6.in_Base(BAR5->get_Base()) + ifi5;
Vector3D ni5 = ni6.in_Base(BAR5->get_Base()) + ini5  + (P5P6 ^fi6.in_Base(BAR5->get_Base()) ); 

// SOLID 4
Vector3D fi4 = fi5.in_Base(BAR4->get_Base()) + ifi4;
Vector3D ni4 = ni5.in_Base(BAR4->get_Base()) + ini4  + (P4P5 ^fi5.in_Base(BAR4->get_Base()) ); 

// SOLID 3
Vector3D fi3 = fi4.in_Base(BAR3->get_Base()) + ifi3;
Vector3D ni3 = ni4.in_Base(BAR3->get_Base()) + ini3  + (P3P4 ^fi4.in_Base(BAR3->get_Base()) ); 


// SOLID 2
Vector3D fi2 = fi3.in_Base(BAR2->get_Base()) + ifi2;
Vector3D ni2 = ni3.in_Base(BAR2->get_Base()) + ini2  + (P2P3 ^fi3.in_Base(BAR2->get_Base()) ); 


// SOLID 1
Vector3D fi1 = fi2.in_Base(BAR1->get_Base()) + ifi1;
Vector3D ni1 = ni2.in_Base(BAR1->get_Base()) + ini1  + (P1P2 ^fi2.in_Base(BAR1->get_Base()) ); 




Matrix OMEGA01_dq = sys.jacobian(OMEGA01.transpose(),dq);
Matrix OMEGA21_dq = sys.jacobian(OMEGA21.transpose(),dq);
Matrix OMEGA32_dq = sys.jacobian(OMEGA32.transpose(),dq);
Matrix OMEGA43_dq = sys.jacobian(OMEGA43.transpose(),dq);
Matrix OMEGA54_dq = sys.jacobian(OMEGA54.transpose(),dq);
Matrix OMEGA65_dq = sys.jacobian(OMEGA65.transpose(),dq);





//~ cout << fi1<<endl;
//~ cout << ni1<<endl;
//~ cout << OMEGA01<<endl;
//~ cout <<"------------------------" <<endl;
//~ cout << fi2<<endl;
//~ cout << ni2<<endl;
//~ cout << OMEGA21<<endl;
//~ cout <<"------------------------" <<endl;
//~ cout << fi3<<endl;
//~ cout << ni3<<endl;
//~ cout << OMEGA32<<endl;
//~ cout <<"------------------------" <<endl;
//~ cout << fi4<<endl;
//~ cout << ni4<<endl;
//~ cout << OMEGA43<<endl;
//~ cout <<"------------------------" <<endl;
//~ cout << fi5<<endl;
//~ cout << ni5<<endl;
//~ cout << OMEGA54<<endl;
//~ cout <<"------------------------" <<endl;
//~ cout << fi6<<endl;
//~ cout << ni6<<endl;
//~ cout << OMEGA65<<endl;
//~ cout <<"------------------------" <<endl;


Matrix eq = ni1.transpose() * OMEGA01_dq +
            ni2.transpose() * OMEGA21_dq +
            ni3.transpose() * OMEGA32_dq +
            ni4.transpose() * OMEGA43_dq +
            ni5.transpose() * OMEGA54_dq +
            ni6.transpose() * OMEGA65_dq;

eq = eq.transpose();
//~ lst new_atom_list_eq, new_exp_list_eq;        
//~ matrix_list_optimize (eq, new_atom_list_eq, new_exp_list_eq);
//~ sys.export_Matrix_C("eq","_eq",eq, new_atom_list_eq, new_exp_list_eq ,ORDER);
//~ sys.export_function_MATLAB("eq", "eq_", eq, new_atom_list_eq, new_exp_list_eq);


vector < symbol_numeric * > Accelerations  = sys.get_Accelerations();
Matrix Qrec=zero_substitution(eq,Accelerations);
lst new_atom_list_Qrec, new_exp_list_Qrec;        
matrix_list_optimize (Qrec, new_atom_list_Qrec, new_exp_list_Qrec);
sys.export_Matrix_C("Qrec","_Qrec",Qrec, new_atom_list_Qrec, new_exp_list_Qrec ,ORDER);
sys.export_function_MATLAB("Qrec", "Qrec_", Qrec, new_atom_list_Qrec, new_exp_list_Qrec,"q,dq,time,param");


Matrix Mrec = sys.jacobian(eq.transpose(),ddq,1);

lst new_atom_list_Mrec, new_exp_list_Mrec;        
matrix_list_optimize (Mrec, new_atom_list_Mrec, new_exp_list_Mrec);
sys.export_Matrix_C("Mrec","_Mrec",Mrec, new_atom_list_Mrec, new_exp_list_Mrec ,ORDER);
sys.export_function_MATLAB("Mrec", "Mrec_", Mrec, new_atom_list_Mrec, new_exp_list_Mrec,"q,time,param");


Matrix MQrec = Matrix("MQrec",1,2,&Mrec,&Qrec);
lst new_atom_list_MQrec, new_exp_list_MQrec;        
matrix_list_optimize (MQrec, new_atom_list_MQrec, new_exp_list_MQrec);
sys.export_Matrix_C("MQrec","_MQrec",MQrec, new_atom_list_MQrec, new_exp_list_MQrec ,ORDER);
sys.export_function_MATLAB("MQrec", "MQrec_", MQrec, new_atom_list_MQrec, new_exp_list_MQrec,"q,dq,time,param");



vector < symbol_numeric * > ddq1; ddq1.push_back( dda2 );ddq1.push_back( dda3 );ddq1.push_back( dda4 );ddq1.push_back( dda5 );ddq1.push_back( dda6 );
vector < symbol_numeric * > ddq2;ddq2.push_back( dda1 );ddq2.push_back( dda3 );ddq2.push_back( dda4 );ddq2.push_back( dda5 );ddq2.push_back( dda6 );
vector < symbol_numeric * > ddq3;ddq3.push_back( dda1 );ddq3.push_back( dda2 );ddq3.push_back( dda4 );ddq3.push_back( dda5 );ddq3.push_back( dda6 );
vector < symbol_numeric * > ddq4;ddq4.push_back( dda1 );ddq4.push_back( dda2 );ddq4.push_back( dda3 );ddq4.push_back( dda5 );ddq4.push_back( dda6 );
vector < symbol_numeric * > ddq5;ddq5.push_back( dda1 );ddq5.push_back( dda2 );ddq5.push_back( dda3 );ddq5.push_back( dda4 );ddq5.push_back( dda6 );
vector < symbol_numeric * > ddq6;ddq6.push_back( dda1 );ddq6.push_back( dda2 );ddq6.push_back( dda3 );ddq6.push_back( dda4 );ddq6.push_back( dda5 );

Matrix Mrecsubs (6,6);
vector < symbol_numeric * > Velocities = sys.get_Velocities();
Matrix Mddq =zero_substitution(eq,Velocities);
vector < symbol_numeric * > vg;vg.push_back( &g );
Mddq =recursive_substitution(Mddq, vg,0);

Matrix Mdd1 = zero_substitution(Mddq,ddq1);
Matrix Mdd2 = zero_substitution(Mddq,ddq2);
Matrix Mdd3 = zero_substitution(Mddq,ddq3);
Matrix Mdd4 = zero_substitution(Mddq,ddq4);
Matrix Mdd5 = zero_substitution(Mddq,ddq5);
Matrix Mdd6 = zero_substitution(Mddq,ddq6);


vector < symbol_numeric * > vdda1; vdda1.push_back( dda1 );
vector < symbol_numeric * > vdda2; vdda2.push_back( dda2 );
vector < symbol_numeric * > vdda3; vdda3.push_back( dda3 );
vector < symbol_numeric * > vdda4; vdda4.push_back( dda4 );
vector < symbol_numeric * > vdda5; vdda5.push_back( dda5 );
vector < symbol_numeric * > vdda6; vdda6.push_back( dda6 );
Mrecsubs.set_col(0,recursive_substitution(Mdd1, vdda1,1));
Mrecsubs.set_col(1,recursive_substitution(Mdd2, vdda2,1));
Mrecsubs.set_col(2,recursive_substitution(Mdd3, vdda3,1));
Mrecsubs.set_col(3,recursive_substitution(Mdd4, vdda4,1));
Mrecsubs.set_col(4,recursive_substitution(Mdd5, vdda5,1));
Mrecsubs.set_col(5,recursive_substitution(Mdd6, vdda6,1));



lst new_atom_list_Mrecsubs, new_exp_list_Mrecsubs;        
matrix_list_optimize (Mrecsubs, new_atom_list_Mrecsubs, new_exp_list_Mrecsubs);
sys.export_Matrix_C("Mrecsubs","_Mrecsubs",Mrecsubs, new_atom_list_Mrecsubs, new_exp_list_Mrecsubs ,ORDER);
sys.export_function_MATLAB("Mrecsubs", "Mrecsubs_", Mrecsubs, new_atom_list_Mrecsubs, new_exp_list_Mrecsubs,"q,time,param");

Matrix MQrecsubs = Matrix("MQrecsubs",1,2,&Mrecsubs,&Qrec);
lst new_atom_list_MQrecsubs, new_exp_list_MQrecsubs;        
matrix_list_optimize (MQrecsubs, new_atom_list_MQrecsubs, new_exp_list_MQrecsubs);
sys.export_Matrix_C("MQrecsubs","_MQrecsubs",MQrecsubs, new_atom_list_MQrecsubs, new_exp_list_MQrecsubs ,ORDER);
sys.export_function_MATLAB("MQrecsubs", "MQrecsubs_", MQrecsubs, new_atom_list_MQrecsubs, new_exp_list_MQrecsubs,"q,dq,time,param");

Matrix Mkaka   = *sys.get_Matrix( "M" );
Matrix Qkaka   = *sys.get_Matrix( "Q" );
//cout << unatomize_ex(Qrec (5,0)+Qkaka(5,0))<<endl;




// ************************************************************************************************
// 	Substituions 
// ************************************************************************************************ 


cout << "KPhi  Calculation " << endl;   
sys.export_init_function_MATLAB();


Matrix Mo   = *sys.get_Matrix( "M" );
Matrix Qo   = *sys.get_Matrix( "Q" );
Matrix MQo  = *sys.get_Matrix( "MQ" );
Matrix Ko   = sys.jacobian(eq.transpose(),M_inertial_parameters);


vector < symbol_numeric * > vtau;
vtau.push_back( &Ma1 );vtau.push_back( &Ma2 );vtau.push_back( &Ma3 );
vtau.push_back( &Ma4 );vtau.push_back( &Ma5 );vtau.push_back( &Ma6 );
//Matrix Dynamic_Equations = Mo*ddq-Qo;
//WPhio= zero_substitution(Dynamic_Equations,vtau);
Matrix WPhio= zero_substitution(eq,vtau);


Matrix Mnew = Mo;
Matrix Qnew = Qo;
Matrix MQnew = MQo;
Matrix Knew = Ko;
//Matrix WPhinew = eq;
Matrix WPhinew = WPhio;




lst new_atom_list_Mnew, new_exp_list_Mnew;        
matrix_list_optimize (Mnew, new_atom_list_Mnew, new_exp_list_Mnew);
sys.export_Matrix_C("Mnew","_Mnew",Mnew, new_atom_list_Mnew, new_exp_list_Mnew ,ORDER);
sys.export_function_MATLAB("Mnew", "Mnew_", Mnew, new_atom_list_Mnew, new_exp_list_Mnew,"q,time,param");

lst new_atom_list_Qnew, new_exp_list_Qnew;        
matrix_list_optimize (Qnew, new_atom_list_Qnew, new_exp_list_Qnew);
sys.export_Matrix_C("Qnew","_Qnew",Qnew, new_atom_list_Qnew, new_exp_list_Qnew ,ORDER);
sys.export_function_MATLAB("Qnew", "Qnew_", Qnew, new_atom_list_Qnew, new_exp_list_Qnew,"q,dq,time,param"); 
    
 
lst new_atom_list_MQnew, new_exp_list_MQnew;        
matrix_list_optimize (MQnew, new_atom_list_MQnew, new_exp_list_MQnew);
sys.export_Matrix_C("MQnew","_MQnew",MQnew, new_atom_list_MQnew, new_exp_list_MQnew ,ORDER);
sys.export_function_MATLAB("MQnew", "MQnew_", MQnew, new_atom_list_MQnew, new_exp_list_MQnew,"q,dq,time,param");

lst new_atom_list_Knew, new_exp_list_Knew;        
matrix_list_optimize (Knew, new_atom_list_Knew, new_exp_list_Knew);
sys.export_Matrix_C("Knew","_Knew",Knew, new_atom_list_Knew, new_exp_list_Knew ,ORDER);
sys.export_function_MATLAB("Knew", "Knew_", Knew, new_atom_list_Knew, new_exp_list_Knew,"q,dq,ddq,time,param");

lst new_atom_list_WPhinew, new_exp_list_WPhinew;        
matrix_list_optimize (WPhinew, new_atom_list_WPhinew, new_exp_list_WPhinew);
sys.export_Matrix_C("WPhinew","_WPhinew",WPhinew, new_atom_list_WPhinew, new_exp_list_WPhinew ,ORDER);
sys.export_function_MATLAB("WPhinew", "WPhinew_", WPhinew, new_atom_list_WPhinew, new_exp_list_WPhinew,"q,dq,ddq,time,param");

lst new_atom_list_M_inertial_parameters, new_exp_list_M_inertial_parameters;        
matrix_list_optimize (M_inertial_parameters, new_atom_list_M_inertial_parameters, new_exp_list_M_inertial_parameters);
sys.export_Matrix_C("M_inertial_parameters","_M_inertial_parameters",M_inertial_parameters, new_atom_list_M_inertial_parameters, new_exp_list_M_inertial_parameters ,ORDER);
sys.export_function_MATLAB("M_inertial_parameters", "M_inertial_parameters_", M_inertial_parameters, new_atom_list_M_inertial_parameters, new_exp_list_M_inertial_parameters,"param");

//sys.export_environment_m (  );return 0;

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

//int ke = system("octave -q mrank.m");
cout<<endl;


vector < symbol_numeric * > v1;


// Elemin
//*
v1.push_back( &mz5 );
v1.push_back( &mx3 );
v1.push_back( &mx2 );
v1.push_back( &Ixx5 );
v1.push_back( &my3 );
v1.push_back( &Izz4 );
v1.push_back( &Iyy4 );
v1.push_back( &m5 );
v1.push_back( &m6 );
v1.push_back( &Iyy3 );
v1.push_back( &my5 );
v1.push_back( &Ixx2 );
v1.push_back( &Izz1 );
v1.push_back( &Ixy4 );
v1.push_back( &Iyz3 );
v1.push_back( &Ixz3 );
v1.push_back( &Ixz4 );
v1.push_back( &Iyz4 );
v1.push_back( &Ixy5 );
v1.push_back( &Iyz5 );
v1.push_back( &Ixz5 );
v1.push_back( &Ixy3 );
v1.push_back( &Ixz6 );
v1.push_back( &Ixy6 );
v1.push_back( &Iyz6 );
v1.push_back( &Ixy2 );
v1.push_back( &Iyz2 );
v1.push_back( &m4 );
v1.push_back( &my2 );
v1.push_back( &mz3 );
v1.push_back( &Ixz2 );
v1.push_back( &mx5 );
v1.push_back( &Ixx4 );
v1.push_back( &Izz5 );
v1.push_back( &mx4 );
v1.push_back( &Iyy2 );
v1.push_back( &mz4 );
v1.push_back( &Izz6 );
v1.push_back( &Izz2 );
v1.push_back( &Ixx3 );
v1.push_back( &mz6 );
v1.push_back( &Iyy5 );
v1.push_back( &my4 );
v1.push_back( &mx6 );
v1.push_back( &my6 );
v1.push_back( &Ixx6 );
v1.push_back( &Iyy6 );
v1.push_back( &Izz3 );
v1.push_back( &m3 );
//*/

// ADD
/*
v1.push_back( &mz3 );
v1.push_back( &Iyy6 );
v1.push_back( &mz4 );
v1.push_back( &Iyy3 );
v1.push_back( &mx3 );
v1.push_back( &Ixx6 );
v1.push_back( &m6 );
v1.push_back( &mz5 );
v1.push_back( &Iyy2 );
v1.push_back( &Iyy5 );
v1.push_back( &Izz2 );
v1.push_back( &Ixx4 );
v1.push_back( &my5 );
v1.push_back( &m5 );
v1.push_back( &Ixy3 );
v1.push_back( &Ixy4 );
v1.push_back( &Iyz3 );
v1.push_back( &Ixz3 );
v1.push_back( &Ixz4 );
v1.push_back( &Iyz4 );
v1.push_back( &Ixy5 );
v1.push_back( &Iyz5 );
v1.push_back( &Ixz5 );
v1.push_back( &Ixz6 );
v1.push_back( &Ixy6 );
v1.push_back( &Iyz6 );
v1.push_back( &Ixy2 );
v1.push_back( &Ixx2 );
v1.push_back( &Iyz2 );
v1.push_back( &Ixx5 );
v1.push_back( &m4 );
v1.push_back( &my2 );
v1.push_back( &Izz1 );
v1.push_back( &mx5 );
v1.push_back( &Iyy4 );
v1.push_back( &mx4 );
v1.push_back( &Ixz2 );
v1.push_back( &Ixx3 );
v1.push_back( &Izz6 );
v1.push_back( &my3 );
v1.push_back( &Izz4 );
v1.push_back( &my4 );
v1.push_back( &mx2 );
v1.push_back( &mz6 );
v1.push_back( &mx6 );
v1.push_back( &my6 );
v1.push_back( &Izz3 );
v1.push_back( &Izz5 );
v1.push_back( &m3 );
//*/


//QR
/*
v1.push_back( &m5 );
v1.push_back( &m6 );
v1.push_back( &mz3 );
v1.push_back( &Iyy2 );
v1.push_back( &Iyy3 );
v1.push_back( &m3 );
v1.push_back( &m4 );
v1.push_back( &Ixx4 );
v1.push_back( &mz4 );
v1.push_back( &mz5 );
v1.push_back( &Izz3 );
v1.push_back( &mz6 );
v1.push_back( &Izz5 );
v1.push_back( &Ixx2 );
v1.push_back( &Ixx3 );
v1.push_back( &Ixy2 );
v1.push_back( &Izz2 );
v1.push_back( &Izz1 );
v1.push_back( &Iyz2 );
v1.push_back( &Ixz2 );
v1.push_back( &Ixy3 );
v1.push_back( &Iyz3 );
v1.push_back( &Ixz3 );
v1.push_back( &my2 );
v1.push_back( &Izz4 );
v1.push_back( &mx2 );
v1.push_back( &mx3 );
v1.push_back( &my3 );
v1.push_back( &Iyy4 );
v1.push_back( &Ixy4 );
v1.push_back( &Iyy5 );
v1.push_back( &Ixz4 );
v1.push_back( &Iyz4 );
v1.push_back( &Ixx5 );
v1.push_back( &mx4 );
v1.push_back( &Ixy5 );
v1.push_back( &my4 );
v1.push_back( &Ixz5 );
v1.push_back( &Iyz5 );
v1.push_back( &Ixx6 );
v1.push_back( &Iyy6 );
v1.push_back( &mx5 );
v1.push_back( &my5 );
v1.push_back( &Izz6 );
v1.push_back( &Ixz6 );
v1.push_back( &Iyz6 );
v1.push_back( &Ixy6 );
v1.push_back( &mx6 );
v1.push_back( &my6 );
//*/

vector < symbol_numeric * > v2;
   
for (int k = 0;k<v1.size(); k++) {
v2.push_back( v1[k]);
    
Matrix Mnew = zero_substitution(Mo,v2);
Matrix Qnew = zero_substitution(Qo,v2);
Matrix MQnew = zero_substitution(MQo,v2);
Matrix Knew= zero_substitution(Ko,v2);
Matrix WPhinew= zero_substitution(WPhio,v2);

lst new_atom_list_Mnew, new_exp_list_Mnew;        
matrix_list_optimize (Mnew, new_atom_list_Mnew, new_exp_list_Mnew);
sys.export_Matrix_C("Mnew","_Mnew",Mnew, new_atom_list_Mnew, new_exp_list_Mnew ,ORDER);
sys.export_function_MATLAB("Mnew", "Mnew_", Mnew, new_atom_list_Mnew, new_exp_list_Mnew);

lst new_atom_list_Qnew, new_exp_list_Qnew;        
matrix_list_optimize (Qnew, new_atom_list_Qnew, new_exp_list_Qnew);
sys.export_Matrix_C("Qnew","_Qnew",Qnew, new_atom_list_Qnew, new_exp_list_Qnew ,ORDER);
sys.export_function_MATLAB("Qnew", "Qnew_", Qnew, new_atom_list_Qnew, new_exp_list_Qnew); 
    

lst new_atom_list_MQnew, new_exp_list_MQnew;        
matrix_list_optimize (MQnew, new_atom_list_MQnew, new_exp_list_MQnew);
sys.export_Matrix_C("MQnew","_MQnew",MQnew, new_atom_list_MQnew, new_exp_list_MQnew ,ORDER);
sys.export_function_MATLAB("MQnew", "MQnew_", MQnew, new_atom_list_MQnew, new_exp_list_MQnew); 

lst new_atom_list_Knew, new_exp_list_Knew;        
matrix_list_optimize (Knew, new_atom_list_Knew, new_exp_list_Knew);
sys.export_Matrix_C("Knew","_Knew",Knew, new_atom_list_Knew, new_exp_list_Knew ,ORDER);
sys.export_function_MATLAB("Knew", "Knew_", Knew, new_atom_list_Knew, new_exp_list_Knew);

lst new_atom_list_WPhinew, new_exp_list_WPhinew;        
matrix_list_optimize (WPhinew, new_atom_list_WPhinew, new_exp_list_WPhinew);
sys.export_Matrix_C("WPhinew","_WPhinew",WPhinew, new_atom_list_WPhinew, new_exp_list_WPhinew ,ORDER);
sys.export_function_MATLAB("WPhinew", "WPhinew_", WPhinew, new_atom_list_WPhinew, new_exp_list_WPhinew);

  
int e;

cout << "symb = "<< v1[k]->get_name()<<endl;

cout <<"M atom = " << new_atom_list_Mnew.nops()<<endl;
e = system("python op_counter.py Mnew.m");

cout <<"Q atom = " << new_atom_list_Qnew.nops()<<endl;
e = system("python op_counter.py Qnew.m");

cout <<"MQ atom = " << new_atom_list_MQnew.nops()<<endl;
e = system("python op_counter.py MQnew.m");

cout <<"K atom = " << new_atom_list_Knew.nops()<<endl;
e = system("python op_counter.py Knew.m");

cout <<"WPhi atom = " << new_atom_list_WPhinew.nops()<<endl;
ex = system("python op_counter.py WPhinew.m");

//e = system("octave -q mrank.m");

cout<<endl;
} 


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

    	state = 	{a1,*da1,*dda1, a2,*da2,*dda2, a3,*da3,*dda3};
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


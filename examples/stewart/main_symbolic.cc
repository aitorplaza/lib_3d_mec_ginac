#include <fstream>
#include "lib_3d_mec_ginac/lib_3d_mec_ginac.h"
#include <ginac/ginac.h>
#include <sstream>
#include <ctime>
#include <sys/time.h>
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
cout << "*             Stewart Platform                 *" << endl;
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
        symbol_numeric tim=sys.get_Time_Symbol ( );

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

	// First Rotation of the down bars
	symbol_numeric a1 = *sys.new_Coordinate("a1","da1","dda1", 0.0 , 0.0 , 0.0);
	symbol_numeric a2 = *sys.new_Coordinate("a2","da2","dda2", 0.0 , 0.0 , 0.0);
	symbol_numeric a3 = *sys.new_Coordinate("a3","da3","dda3", 0.0 , 0.0 , 0.0);
	symbol_numeric a4 = *sys.new_Coordinate("a4","da4","dda4", 0.0 , 0.0 , 0.0);
	symbol_numeric a5 = *sys.new_Coordinate("a5","da5","dda5", 0.0 , 0.0 , 0.0);
	symbol_numeric a6 = *sys.new_Coordinate("a6","da6","dda6", 0.0 , 0.0 , 0.0);

	// Second Rotation of the down bars
	symbol_numeric b1 = *sys.new_Coordinate("b1","dB1","ddB1", -0.60 , 0.0 , 0.0);
	symbol_numeric b2 = *sys.new_Coordinate("b2","dB2","ddB2", -0.60 , 0.0 , 0.0);
	symbol_numeric b3 = *sys.new_Coordinate("b3","dB3","ddB3", -0.60 , 0.0 , 0.0);
	symbol_numeric b4 = *sys.new_Coordinate("b4","dB4","ddB4", -0.60 , 0.0 , 0.0);
	symbol_numeric b5 = *sys.new_Coordinate("b5","dB5","ddB5", -0.60 , 0.0 , 0.0);
	symbol_numeric b6 = *sys.new_Coordinate("b6","dB6","ddB6", -0.60 , 0.0 , 0.0);

	// Translation of the up bars w.r.t. the down bars
	symbol_numeric s1 = *sys.new_Coordinate("s1","ds1","dds1", 7.0 , 0.0 , 0.0);
	symbol_numeric s2 = *sys.new_Coordinate("s2","ds2","dds2", 7.0 , 0.0 , 0.0);
	symbol_numeric s3 = *sys.new_Coordinate("s3","ds3","dds3", 7.0 , 0.0 , 0.0);
	symbol_numeric s4 = *sys.new_Coordinate("s4","ds4","dds4", 7.0 , 0.0 , 0.0);
	symbol_numeric s5 = *sys.new_Coordinate("s5","ds5","dds5", 7.0 , 0.0 , 0.0);
	symbol_numeric s6 = *sys.new_Coordinate("s6","ds6","dds6", 7.0 , 0.0 , 0.0);

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
	symbol_numeric L = *sys.new_Parameter("L",7.0);

	// Moving Platform Radius
	symbol_numeric R = *sys.new_Parameter("R",2.0);

	// 60 degrees angle
	symbol_numeric alfa = *sys.new_Parameter("alfa",3.14159/3.0);
	
// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

 	sys.new_Base("B0P","xyz",1,0,0,a);
 	sys.new_Base("BAP","B0P",0,1,0,b);
 	sys.new_Base("BP","BAP", 0,0,1,c);

 	sys.new_Base("BP1","BP",0,0,1,1.0*alfa);
 	sys.new_Base("BP2","BP",0,0,1,1.0*alfa);
 	sys.new_Base("BP3","BP",0,0,1,3.0*alfa);
 	sys.new_Base("BP4","BP",0,0,1,3.0*alfa);
 	sys.new_Base("BP5","BP",0,0,1,5.0*alfa);
 	sys.new_Base("BP6","BP",0,0,1,5.0*alfa);

 	sys.new_Base("B01","xyz",0,0,1,0.0*alfa);
 	sys.new_Base("B02","xyz",0,0,1,2.0*alfa);
 	sys.new_Base("B03","xyz",0,0,1,2.0*alfa);
 	sys.new_Base("B04","xyz",0,0,1,4.0*alfa);
 	sys.new_Base("B05","xyz",0,0,1,4.0*alfa);
 	sys.new_Base("B06","xyz",0,0,1,6.0*alfa);

 	sys.new_Base("BA1","B01",1,0,0,a1);
 	sys.new_Base("BA2","B02",1,0,0,a2);
 	sys.new_Base("BA3","B03",1,0,0,a3);
 	sys.new_Base("BA4","B04",1,0,0,a4);
 	sys.new_Base("BA5","B05",1,0,0,a5);
 	sys.new_Base("BA6","B06",1,0,0,a6);

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
	
	Vector3D OA1 = *sys.new_Vector3D("OA1",L,0,0,"B01");
	Vector3D OA2 = *sys.new_Vector3D("OA2",L,0,0,"B02");
	Vector3D OA3 = *sys.new_Vector3D("OA3",L,0,0,"B03");
	Vector3D OA4 = *sys.new_Vector3D("OA4",L,0,0,"B04");
	Vector3D OA5 = *sys.new_Vector3D("OA5",L,0,0,"B05");
	Vector3D OA6 = *sys.new_Vector3D("OA6",L,0,0,"B06");

	Vector3D A1C1 = *sys.new_Vector3D("A1C1",0,0,s1,"B1");
	Vector3D A2C2 = *sys.new_Vector3D("A2C2",0,0,s2,"B2");
	Vector3D A3C3 = *sys.new_Vector3D("A3C3",0,0,s3,"B3");
	Vector3D A4C4 = *sys.new_Vector3D("A4C4",0,0,s4,"B4");
	Vector3D A5C5 = *sys.new_Vector3D("A5C5",0,0,s5,"B5");
	Vector3D A6C6 = *sys.new_Vector3D("A6C6",0,0,s6,"B6");
	
	Vector3D PD1 = *sys.new_Vector3D("PD1",R,0,0,"BP1");
	Vector3D PD2 = *sys.new_Vector3D("PD2",R,0,0,"BP2");
	Vector3D PD3 = *sys.new_Vector3D("PD3",R,0,0,"BP3");
	Vector3D PD4 = *sys.new_Vector3D("PD4",R,0,0,"BP4");
	Vector3D PD5 = *sys.new_Vector3D("PD5",R,0,0,"BP5");
	Vector3D PD6 = *sys.new_Vector3D("PD6",R,0,0,"BP6");


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
    	symbol_numeric  mP = *sys.new_Parameter("mP",100.0);
	symbol_numeric  mxP = *sys.new_Parameter("mxP",0.0);
    	symbol_numeric  myP = *sys.new_Parameter("myP",0.0);
	symbol_numeric  mzP = *sys.new_Parameter("mzP",0.0);
    	symbol_numeric  IxxP = *sys.new_Parameter("IxxP",100.0);
	symbol_numeric  IxyP = *sys.new_Parameter("IxyP",0.0);
    	symbol_numeric  IyyP = *sys.new_Parameter("IyyP",100.0);
	symbol_numeric  IxzP = *sys.new_Parameter("IxzP",0.0);
    	symbol_numeric  IzzP = *sys.new_Parameter("IzzP",200.0);
	symbol_numeric  IyzP = *sys.new_Parameter("IyzP",0.0);

	// Inertial parameters of the BAR1D
    	symbol_numeric  m1D = *sys.new_Parameter("m1D",100.0);
	symbol_numeric  mx1D = *sys.new_Parameter("mx1D",0.0);
    	symbol_numeric  my1D = *sys.new_Parameter("my1D",0.0);
	symbol_numeric  mz1D = *sys.new_Parameter("mz1D",0.0);
    	symbol_numeric  Ixx1D = *sys.new_Parameter("Ixx1D",100.0);
	symbol_numeric  Ixy1D = *sys.new_Parameter("Ixy1D",0.0);
    	symbol_numeric  Iyy1D = *sys.new_Parameter("Iyy1D",100.0);
	symbol_numeric  Ixz1D = *sys.new_Parameter("Ixz1D",0.0);
    	symbol_numeric  Izz1D = *sys.new_Parameter("Izz1D",200.0);
	symbol_numeric  Iyz1D = *sys.new_Parameter("Iyz1D",0.0);

	// Inertial parameters of the BAR1U
    	symbol_numeric  m1U = *sys.new_Parameter("m1U",100.0);
	symbol_numeric  mx1U = *sys.new_Parameter("mx1U",0.0);
    	symbol_numeric  my1U = *sys.new_Parameter("my1U",0.0);
	symbol_numeric  mz1U = *sys.new_Parameter("mz1U",0.0);
    	symbol_numeric  Ixx1U = *sys.new_Parameter("Ixx1U",100.0);
	symbol_numeric  Ixy1U = *sys.new_Parameter("Ixy1U",0.0);
    	symbol_numeric  Iyy1U = *sys.new_Parameter("Iyy1U",100.0);
	symbol_numeric  Ixz1U = *sys.new_Parameter("Ixz1U",0.0);
    	symbol_numeric  Izz1U = *sys.new_Parameter("Izz1U",200.0);
	symbol_numeric  Iyz1U = *sys.new_Parameter("Iyz1U",0.0);
	
	// Inertial parameters of the BAR2D
    	symbol_numeric  m2D = *sys.new_Parameter("m2D",100.0);
	symbol_numeric  mx2D = *sys.new_Parameter("mx2D",0.0);
    	symbol_numeric  my2D = *sys.new_Parameter("my2D",0.0);
	symbol_numeric  mz2D = *sys.new_Parameter("mz2D",0.0);
    	symbol_numeric  Ixx2D = *sys.new_Parameter("Ixx2D",100.0);
	symbol_numeric  Ixy2D = *sys.new_Parameter("Ixy2D",0.0);
    	symbol_numeric  Iyy2D = *sys.new_Parameter("Iyy2D",100.0);
	symbol_numeric  Ixz2D = *sys.new_Parameter("Ixz2D",0.0);
    	symbol_numeric  Izz2D = *sys.new_Parameter("Izz2D",200.0);
	symbol_numeric  Iyz2D = *sys.new_Parameter("Iyz2D",0.0);

	// Inertial parameters of the BAR2U
    	symbol_numeric  m2U = *sys.new_Parameter("m2U",100.0);
	symbol_numeric  mx2U = *sys.new_Parameter("mx2U",0.0);
    	symbol_numeric  my2U = *sys.new_Parameter("my2U",0.0);
	symbol_numeric  mz2U = *sys.new_Parameter("mz2U",0.0);
    	symbol_numeric  Ixx2U = *sys.new_Parameter("Ixx2U",100.0);
	symbol_numeric  Ixy2U = *sys.new_Parameter("Ixy2U",0.0);
    	symbol_numeric  Iyy2U = *sys.new_Parameter("Iyy2U",100.0);
	symbol_numeric  Ixz2U = *sys.new_Parameter("Ixz2U",0.0);
    	symbol_numeric  Izz2U = *sys.new_Parameter("Izz2U",200.0);
	symbol_numeric  Iyz2U = *sys.new_Parameter("Iyz2U",0.0);

	// Inertial parameters of the BAR3D
    	symbol_numeric  m3D = *sys.new_Parameter("m3D",100.0);
	symbol_numeric  mx3D = *sys.new_Parameter("mx3D",0.0);
    	symbol_numeric  my3D = *sys.new_Parameter("my3D",0.0);
	symbol_numeric  mz3D = *sys.new_Parameter("mz3D",0.0);
    	symbol_numeric  Ixx3D = *sys.new_Parameter("Ixx3D",100.0);
	symbol_numeric  Ixy3D = *sys.new_Parameter("Ixy3D",0.0);
    	symbol_numeric  Iyy3D = *sys.new_Parameter("Iyy3D",100.0);
	symbol_numeric  Ixz3D = *sys.new_Parameter("Ixz3D",0.0);
    	symbol_numeric  Izz3D = *sys.new_Parameter("Izz3D",200.0);
	symbol_numeric  Iyz3D = *sys.new_Parameter("Iyz3D",0.0);

	// Inertial parameters of the BAR3U
    	symbol_numeric  m3U = *sys.new_Parameter("m3U",100.0);
	symbol_numeric  mx3U = *sys.new_Parameter("mx3U",0.0);
    	symbol_numeric  my3U = *sys.new_Parameter("my3U",0.0);
	symbol_numeric  mz3U = *sys.new_Parameter("mz3U",0.0);
    	symbol_numeric  Ixx3U = *sys.new_Parameter("Ixx3U",100.0);
	symbol_numeric  Ixy3U = *sys.new_Parameter("Ixy3U",0.0);
    	symbol_numeric  Iyy3U = *sys.new_Parameter("Iyy3U",100.0);
	symbol_numeric  Ixz3U = *sys.new_Parameter("Ixz3U",0.0);
    	symbol_numeric  Izz3U = *sys.new_Parameter("Izz3U",200.0);
	symbol_numeric  Iyz3U = *sys.new_Parameter("Iyz3U",0.0);
	
	// Inertial parameters of the BAR4D
    	symbol_numeric  m4D = *sys.new_Parameter("m4D",100.0);
	symbol_numeric  mx4D = *sys.new_Parameter("mx4D",0.0);
    	symbol_numeric  my4D = *sys.new_Parameter("my4D",0.0);
	symbol_numeric  mz4D = *sys.new_Parameter("mz4D",0.0);
    	symbol_numeric  Ixx4D = *sys.new_Parameter("Ixx4D",100.0);
	symbol_numeric  Ixy4D = *sys.new_Parameter("Ixy4D",0.0);
    	symbol_numeric  Iyy4D = *sys.new_Parameter("Iyy4D",100.0);
	symbol_numeric  Ixz4D = *sys.new_Parameter("Ixz4D",0.0);
    	symbol_numeric  Izz4D = *sys.new_Parameter("Izz4D",200.0);
	symbol_numeric  Iyz4D = *sys.new_Parameter("Iyz4D",0.0);

	// Inertial parameters of the BAR4U
    	symbol_numeric  m4U = *sys.new_Parameter("m4U",100.0);
	symbol_numeric  mx4U = *sys.new_Parameter("mx4U",0.0);
    	symbol_numeric  my4U = *sys.new_Parameter("my4U",0.0);
	symbol_numeric  mz4U = *sys.new_Parameter("mz4U",0.0);
    	symbol_numeric  Ixx4U = *sys.new_Parameter("Ixx4U",100.0);
	symbol_numeric  Ixy4U = *sys.new_Parameter("Ixy4U",0.0);
    	symbol_numeric  Iyy4U = *sys.new_Parameter("Iyy4U",100.0);
	symbol_numeric  Ixz4U = *sys.new_Parameter("Ixz4U",0.0);
    	symbol_numeric  Izz4U = *sys.new_Parameter("Izz4U",200.0);
	symbol_numeric  Iyz4U = *sys.new_Parameter("Iyz4U",0.0);

		// Inertial parameters of the BAR5D
    	symbol_numeric  m5D = *sys.new_Parameter("m5D",100.0);
	symbol_numeric  mx5D = *sys.new_Parameter("mx5D",0.0);
    	symbol_numeric  my5D = *sys.new_Parameter("my5D",0.0);
	symbol_numeric  mz5D = *sys.new_Parameter("mz5D",0.0);
    	symbol_numeric  Ixx5D = *sys.new_Parameter("Ixx5D",100.0);
	symbol_numeric  Ixy5D = *sys.new_Parameter("Ixy5D",0.0);
    	symbol_numeric  Iyy5D = *sys.new_Parameter("Iyy5D",100.0);
	symbol_numeric  Ixz5D = *sys.new_Parameter("Ixz5D",0.0);
    	symbol_numeric  Izz5D = *sys.new_Parameter("Izz5D",200.0);
	symbol_numeric  Iyz5D = *sys.new_Parameter("Iyz5D",0.0);

	// Inertial parameters of the BAR5U
    	symbol_numeric  m5U = *sys.new_Parameter("m5U",100.0);
	symbol_numeric  mx5U = *sys.new_Parameter("mx5U",0.0);
    	symbol_numeric  my5U = *sys.new_Parameter("my5U",0.0);
	symbol_numeric  mz5U = *sys.new_Parameter("mz5U",0.0);
    	symbol_numeric  Ixx5U = *sys.new_Parameter("Ixx5U",100.0);
	symbol_numeric  Ixy5U = *sys.new_Parameter("Ixy5U",0.0);
    	symbol_numeric  Iyy5U = *sys.new_Parameter("Iyy5U",100.0);
	symbol_numeric  Ixz5U = *sys.new_Parameter("Ixz5U",0.0);
    	symbol_numeric  Izz5U = *sys.new_Parameter("Izz5U",200.0);
	symbol_numeric  Iyz5U = *sys.new_Parameter("Iyz5U",0.0);

	// Inertial parameters of the BAR6D
    	symbol_numeric  m6D = *sys.new_Parameter("m6D",100.0);
	symbol_numeric  mx6D = *sys.new_Parameter("mx6D",0.0);
    	symbol_numeric  my6D = *sys.new_Parameter("my6D",0.0);
	symbol_numeric  mz6D = *sys.new_Parameter("mz6D",0.0);
    	symbol_numeric  Ixx6D = *sys.new_Parameter("Ixx6D",100.0);
	symbol_numeric  Ixy6D = *sys.new_Parameter("Ixy6D",0.0);
    	symbol_numeric  Iyy6D = *sys.new_Parameter("Iyy6D",100.0);
	symbol_numeric  Ixz6D = *sys.new_Parameter("Ixz6D",0.0);
    	symbol_numeric  Izz6D = *sys.new_Parameter("Izz6D",200.0);
	symbol_numeric  Iyz6D = *sys.new_Parameter("Iyz6D",0.0);

	// Inertial parameters of the BAR6U
    	symbol_numeric  m6U = *sys.new_Parameter("m6U",100.0);
	symbol_numeric  mx6U = *sys.new_Parameter("mx6U",0.0);
    	symbol_numeric  my6U = *sys.new_Parameter("my6U",0.0);
	symbol_numeric  mz6U = *sys.new_Parameter("mz6U",0.0);
    	symbol_numeric  Ixx6U = *sys.new_Parameter("Ixx6U",100.0);
	symbol_numeric  Ixy6U = *sys.new_Parameter("Ixy6U",0.0);
    	symbol_numeric  Iyy6U = *sys.new_Parameter("Iyy6U",100.0);
	symbol_numeric  Ixz6U = *sys.new_Parameter("Ixz6U",0.0);
    	symbol_numeric  Izz6U = *sys.new_Parameter("Izz6U",200.0);
	symbol_numeric  Iyz6U = *sys.new_Parameter("Iyz6U",0.0);
	

	Vector3D P_GP= *sys.new_Vector3D("P_GP",mxP/mP,myP/mP,mzP/mP,"BP");

	Vector3D A1_G1D= *sys.new_Vector3D("A1_G1D",mx1D/m1D,my1D/m1D,mz1D/m1D,"B1");
	Vector3D C1_G1U= *sys.new_Vector3D("C1_G1U",mx1U/m1U,my1U/m1U,mz1U/m1U,"B1");

	Vector3D A2_G2D= *sys.new_Vector3D("A2_G2D",mx2D/m2D,my2D/m2D,mz2D/m2D,"B2");
	Vector3D C2_G2U= *sys.new_Vector3D("C2_G2U",mx2U/m2U,my2U/m2U,mz2U/m2U,"B2");

	Vector3D A3_G3D= *sys.new_Vector3D("A3_G3D",mx3D/m3D,my3D/m3D,mz3D/m3D,"B3");
	Vector3D C3_G3U= *sys.new_Vector3D("C3_G3U",mx3U/m3U,my3U/m3U,mz3U/m3U,"B3");

	Vector3D A4_G4D= *sys.new_Vector3D("A4_G4D",mx4D/m4D,my4D/m4D,mz4D/m4D,"B4");
	Vector3D C4_G4U= *sys.new_Vector3D("C4_G4U",mx4U/m4U,my4U/m4U,mz4U/m4U,"B4");

	Vector3D A5_G5D= *sys.new_Vector3D("A5_G5D",mx5D/m5D,my5D/m5D,mz5D/m5D,"B5");
	Vector3D C5_G5U= *sys.new_Vector3D("C5_G5U",mx5U/m5U,my5U/m5U,mz5U/m5U,"B5");

	Vector3D A6_G6D= *sys.new_Vector3D("A6_G6D",mx6D/m6D,my6D/m6D,mz6D/m6D,"B6");
	Vector3D C6_G6U= *sys.new_Vector3D("C6_G6U",mx6U/m6U,my6U/m6U,mz6U/m6U,"B6");

	//Inertia Tensors

// -----------------------------------------------------------------------
	Tensor3D IP = *sys.new_Tensor3D("IP",	(ex)IxxP,(ex)IxyP,(ex)IxzP,
							(ex)IxyP,(ex)IyyP,(ex)IyzP,
							(ex)IxzP,(ex)IyzP,(ex)IzzP,"BP");

// -----------------------------------------------------------------------
    	Tensor3D I1D = *sys.new_Tensor3D("I1D",	(ex)Ixx1D,(ex)Ixy1D,(ex)Ixz1D,
							(ex)Ixy1D,(ex)Iyy1D,(ex)Iyz1D,
							(ex)Ixz1D,(ex)Iyz1D,(ex)Izz1D,"B1");

    	Tensor3D I1U = *sys.new_Tensor3D("I1U",	(ex)Ixx1U,(ex)Ixy1U,(ex)Ixz1U,
							(ex)Ixy1U,(ex)Iyy1U,(ex)Iyz1U,
							(ex)Ixz1U,(ex)Iyz1U,(ex)Izz1U,"B1");
// -----------------------------------------------------------------------
    	Tensor3D I2D = *sys.new_Tensor3D("I2D",	(ex)Ixx2D,(ex)Ixy2D,(ex)Ixz2D,
							(ex)Ixy2D,(ex)Iyy2D,(ex)Iyz2D,
							(ex)Ixz2D,(ex)Iyz2D,(ex)Izz2D,"B2");

    	Tensor3D I2U = *sys.new_Tensor3D("I2U",	(ex)Ixx2U,(ex)Ixy2U,(ex)Ixz2U,
							(ex)Ixy2U,(ex)Iyy2U,(ex)Iyz2U,
							(ex)Ixz2U,(ex)Iyz2U,(ex)Izz2U,"B2");
// -----------------------------------------------------------------------
    	Tensor3D I3D = *sys.new_Tensor3D("I3D",	(ex)Ixx3D,(ex)Ixy3D,(ex)Ixz3D,
							(ex)Ixy3D,(ex)Iyy3D,(ex)Iyz3D,
							(ex)Ixz3D,(ex)Iyz3D,(ex)Izz3D,"B3");

    	Tensor3D I3U = *sys.new_Tensor3D("I3U",	(ex)Ixx3U,(ex)Ixy3U,(ex)Ixz3U,
							(ex)Ixy3U,(ex)Iyy3U,(ex)Iyz3U,
							(ex)Ixz3U,(ex)Iyz3U,(ex)Izz3U,"B3");
// -----------------------------------------------------------------------
    	Tensor3D I4D = *sys.new_Tensor3D("I4D",	(ex)Ixx4D,(ex)Ixy4D,(ex)Ixz4D,
							(ex)Ixy4D,(ex)Iyy4D,(ex)Iyz4D,
							(ex)Ixz4D,(ex)Iyz4D,(ex)Izz4D,"B4");

    	Tensor3D I4U = *sys.new_Tensor3D("I4U",	(ex)Ixx4U,(ex)Ixy4U,(ex)Ixz4U,
							(ex)Ixy4U,(ex)Iyy4U,(ex)Iyz4U,
							(ex)Ixz4U,(ex)Iyz4U,(ex)Izz4U,"B4");
// -----------------------------------------------------------------------
    	Tensor3D I5D = *sys.new_Tensor3D("I5D",	(ex)Ixx5D,(ex)Ixy5D,(ex)Ixz5D,
							(ex)Ixy5D,(ex)Iyy5D,(ex)Iyz5D,
							(ex)Ixz5D,(ex)Iyz5D,(ex)Izz5D,"B5");

    	Tensor3D I5U = *sys.new_Tensor3D("I5U",	(ex)Ixx5U,(ex)Ixy5U,(ex)Ixz5U,
							(ex)Ixy5U,(ex)Iyy5U,(ex)Iyz5U,
							(ex)Ixz5U,(ex)Iyz5U,(ex)Izz5U,"B5");
// -----------------------------------------------------------------------
    	Tensor3D I6D = *sys.new_Tensor3D("I6D",	(ex)Ixx6D,(ex)Ixy6D,(ex)Ixz6D,
							(ex)Ixy6D,(ex)Iyy6D,(ex)Iyz6D,
							(ex)Ixz6D,(ex)Iyz6D,(ex)Izz6D,"B6");

    	Tensor3D I6U = *sys.new_Tensor3D("I6U",	(ex)Ixx6U,(ex)Ixy6U,(ex)Ixz6U,
							(ex)Ixy6U,(ex)Iyy6U,(ex)Iyz6U,
							(ex)Ixz6U,(ex)Iyz6U,(ex)Izz6U,"B6");
// -----------------------------------------------------------------------

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_P = sys.new_Frame("Fra_P","P","BP");
	
	Frame * Fra_1D= sys.new_Frame("Fra_1D","A1","B1");
	Frame * Fra_1U= sys.new_Frame("Fra_1U","C1","B1");

	Frame * Fra_2D= sys.new_Frame("Fra_2D","A2","B2");
	Frame * Fra_2U= sys.new_Frame("Fra_2U","C2","B2");

	Frame * Fra_3D= sys.new_Frame("Fra_3D","A3","B3");
	Frame * Fra_3U= sys.new_Frame("Fra_3U","C3","B3");

	Frame * Fra_4D= sys.new_Frame("Fra_4D","A4","B4");
	Frame * Fra_4U= sys.new_Frame("Fra_4U","C4","B4");

	Frame * Fra_5D= sys.new_Frame("Fra_5D","A5","B5");
	Frame * Fra_5U= sys.new_Frame("Fra_5U","C5","B5");

	Frame * Fra_6D= sys.new_Frame("Fra_6D","A6","B6");
	Frame * Fra_6U= sys.new_Frame("Fra_6U","C6","B6");


// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	Solid * PLATFORM = sys.new_Solid("PLATFORM","P","BP","mP","P_GP","IP");
	Solid * BAR1D = sys.new_Solid("BAR1D","A1","B1","m1D","A1_G1D","I1D");
	Solid * BAR1U = sys.new_Solid("BAR1U","C1","B1","m1U","C1_G1U","I1U");

	Solid * BAR2D = sys.new_Solid("BAR2D","A2","B2","m2D","A2_G2D","I2D");
	Solid * BAR2U = sys.new_Solid("BAR2U","C2","B2","m2U","C2_G2U","I2U");

	Solid * BAR3D = sys.new_Solid("BAR3D","A3","B3","m3D","A3_G3D","I3D");
	Solid * BAR3U = sys.new_Solid("BAR3U","C3","B3","m3U","C3_G3U","I3U");

	Solid * BAR4D = sys.new_Solid("BAR4D","A4","B4","m4D","A4_G4D","I4D");
	Solid * BAR4U = sys.new_Solid("BAR4U","C4","B4","m4U","C4_G4U","I4U");

	Solid * BAR5D = sys.new_Solid("BAR5D","A5","B5","m5D","A5_G5D","I5D");
	Solid * BAR5U = sys.new_Solid("BAR5U","C5","B5","m5U","C5_G5U","I5U");

	Solid * BAR6D = sys.new_Solid("BAR6D","A6","B6","m6D","A6_G6D","I6D");
	Solid * BAR6U = sys.new_Solid("BAR6U","C6","B6","m6U","C6_G6U","I6U");




// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

        Drawing3D * PLATFORM_3D = sys.new_Drawing3D("PLATFORM_3D", "P", "BP" ,"./solids/plataforma_R2.stl",1,0,0,0.6);

        Drawing3D * BAR1D_3D = sys.new_Drawing3D("BAR1D_3D", BAR1D,"./solids/barra_z.stl" ,1,0,0,1.0);	//BAR1D_3D->set_scale(0.5);
        Drawing3D * BAR1U_3D = sys.new_Drawing3D("BAR1U_3D", BAR1U,"./solids/barra_mz.stl",0,1,0,1.0);

        Drawing3D * BAR2D_3D = sys.new_Drawing3D("BAR2D_3D", BAR2D,"./solids/barra_z.stl" ,1,0,0,1.0);
        Drawing3D * BAR2U_3D = sys.new_Drawing3D("BAR2U_3D", BAR2U,"./solids/barra_mz.stl",0,1,0,1.0);

        Drawing3D * BAR3D_3D = sys.new_Drawing3D("BAR3D_3D", BAR3D,"./solids/barra_z.stl" ,1,0,0,1.0);
        Drawing3D * BAR3U_3D = sys.new_Drawing3D("BAR3U_3D", BAR3U,"./solids/barra_mz.stl",0,1,0,1.0);
        
        Drawing3D * BAR4D_3D = sys.new_Drawing3D("BAR4D_3D", BAR4D,"./solids/barra_z.stl" ,1,0,0,1.0);
        Drawing3D * BAR4U_3D = sys.new_Drawing3D("BAR4U_3D", BAR4U,"./solids/barra_mz.stl",0,1,0,1.0);

        Drawing3D * BAR5D_3D = sys.new_Drawing3D("BAR5D_3D", BAR5D,"./solids/barra_z.stl" ,1,0,0,1.0);
        Drawing3D * BAR5U_3D = sys.new_Drawing3D("BAR5U_3D", BAR5U,"./solids/barra_mz.stl",0,1,0,1.0);

        Drawing3D * BAR6D_3D = sys.new_Drawing3D("BAR6D_3D", BAR6D,"./solids/barra_z.stl" ,1,0,0,1.0);
        Drawing3D * BAR6U_3D = sys.new_Drawing3D("BAR6U_3D", BAR6U,"./solids/barra_mz.stl",0,1,0,1.0);


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

    Drawing3D * Fra_PLATFORM_3D = sys.new_Drawing3D("Fra_PLATFORM_3D","Fra_P",1.0);
    Drawing3D * Fra_BAR1D_3D = sys.new_Drawing3D("Fra_BAR1D_3D","Fra_1D",1.0);
    Drawing3D * Fra_BAR2D_3D = sys.new_Drawing3D("Fra_BAR2D_3D","Fra_2D",1.0);
    Drawing3D * Fra_BAR3D_3D = sys.new_Drawing3D("Fra_BAR3D_3D","Fra_3D",1.0);
    Drawing3D * Fra_BAR4D_3D = sys.new_Drawing3D("Fra_BAR4D_3D","Fra_4D",1.0);
    Drawing3D * Fra_BAR5D_3D = sys.new_Drawing3D("Fra_BAR5D_3D","Fra_5D",1.0);
    Drawing3D * Fra_BAR6D_3D = sys.new_Drawing3D("Fra_BAR6D_3D","Fra_6D",1.0);

	Drawing3D * Suelo3D = sys.new_Drawing3D("Suelo3D", "O", "xyz" ,"./solids/ground.stl",0,1,0,1.0);	Suelo3D->set_scale(2);




// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

//	cout << "Joint Unknown Definition" << endl;


/*
// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

	cout << "Input Vector" << endl;

	symbol_numeric FBlockx = *sys.new_Input("FBlockx",0.0);
	symbol_numeric MPendulumy = *sys.new_Input("MPendulumy",0.0);

	Vector3D FBlock = *sys.new_Vector3D("FBlock",FBlockx,0,0,"BBlock");
	Vector3D MBlock = *sys.new_Vector3D("MBlock",0,0,0, "BBlock");
	Vector3D FPendulum = *sys.new_Vector3D("FPendulum",0,0,0,"BPendulum");
	Vector3D MPendulum = *sys.new_Vector3D("MPendulum",0,MPendulumy,0, "BPendulum");

/*/
// ************************************************************************************************
//	Forces Definition
// ************************************************************************************************

	symbol_numeric Fs1 = *sys.new_Parameter("Fs1",0.0);
	symbol_numeric Fs2 = *sys.new_Parameter("Fs2",0.0);
	symbol_numeric Fs3 = *sys.new_Parameter("Fs3",0.0);
	symbol_numeric Fs4 = *sys.new_Parameter("Fs4",0.0);
	symbol_numeric Fs5 = *sys.new_Parameter("Fs5",0.0);
	symbol_numeric Fs6 = *sys.new_Parameter("Fs6",0.0);

	Vector3D F1 = *sys.new_Vector3D("F1",0.0,0.0,Fs1, "B1");	
	Vector3D F2 = *sys.new_Vector3D("F2",0.0,0.0,Fs2, "B2");	
	Vector3D F3 = *sys.new_Vector3D("F3",0.0,0.0,Fs3, "B3");	
	Vector3D F4 = *sys.new_Vector3D("F4",0.0,0.0,Fs4, "B4");	
	Vector3D F5 = *sys.new_Vector3D("F5",0.0,0.0,Fs5, "B5");	
	Vector3D F6 = *sys.new_Vector3D("F6",0.0,0.0,Fs6, "B6");	

	Vector3D M1 = *sys.new_Vector3D("M1",0.0,0.0,0.0, "B1");
	Vector3D M2 = *sys.new_Vector3D("M2",0.0,0.0,0.0, "B2");
	Vector3D M3 = *sys.new_Vector3D("M3",0.0,0.0,0.0, "B3");
	Vector3D M4 = *sys.new_Vector3D("M4",0.0,0.0,0.0, "B4");
	Vector3D M5 = *sys.new_Vector3D("M5",0.0,0.0,0.0, "B5");
	Vector3D M6 = *sys.new_Vector3D("M6",0.0,0.0,0.0, "B6");

	
	
/**/
// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * GravityP = sys.Gravity_Wrench("PLATFORM");
	Wrench3D * Gravity1D = sys.Gravity_Wrench("BAR1D");
	Wrench3D * Gravity1U = sys.Gravity_Wrench("BAR1U");

	Wrench3D * Gravity2D = sys.Gravity_Wrench("BAR2D");
	Wrench3D * Gravity2U = sys.Gravity_Wrench("BAR2U");

	Wrench3D * Gravity3D = sys.Gravity_Wrench("BAR3D");
	Wrench3D * Gravity3U = sys.Gravity_Wrench("BAR3U");

	Wrench3D * Gravity4D = sys.Gravity_Wrench("BAR4D");
	Wrench3D * Gravity4U = sys.Gravity_Wrench("BAR4U");
	
	Wrench3D * Gravity5D = sys.Gravity_Wrench("BAR5D");
	Wrench3D * Gravity5U = sys.Gravity_Wrench("BAR5U");

	Wrench3D * Gravity6D = sys.Gravity_Wrench("BAR6D");
	Wrench3D * Gravity6U = sys.Gravity_Wrench("BAR6U");

	//	Inertia
	/*	
	Wrench3D * Inertia_P = sys.Inertia_Wrench("PLATFORM");

	Wrench3D * Inertia_1D = sys.Inertia_Wrench("BAR1D");
	Wrench3D * Inertia_1U = sys.Inertia_Wrench("BAR1U");

	Wrench3D * Inertia_2D = sys.Inertia_Wrench("BAR2D");
	Wrench3D * Inertia_2U = sys.Inertia_Wrench("BAR2U");

	Wrench3D * Inertia_3D = sys.Inertia_Wrench("BAR3D");
	Wrench3D * Inertia_3U = sys.Inertia_Wrench("BAR3U");

	Wrench3D * Inertia_4D = sys.Inertia_Wrench("BAR4D");
	Wrench3D * Inertia_4U = sys.Inertia_Wrench("BAR4U");

	Wrench3D * Inertia_5D = sys.Inertia_Wrench("BAR5D");
	Wrench3D * Inertia_5U = sys.Inertia_Wrench("BAR5U");

	Wrench3D * Inertia_6D = sys.Inertia_Wrench("BAR6D");
	Wrench3D * Inertia_6U = sys.Inertia_Wrench("BAR6U");
    */
	
	//	External Moments
	Wrench3D * WExternalAction1 = sys.new_Wrench3D ( "WExternalAction1", F1, M1, C1 , BAR1U , "Constitutive") ;
	Wrench3D * WExternalAction2 = sys.new_Wrench3D ( "WExternalAction2", F2, M2, C2 , BAR2U , "Constitutive") ;
	Wrench3D * WExternalAction3 = sys.new_Wrench3D ( "WExternalAction3", F3, M3, C3 , BAR3U , "Constitutive") ;
	Wrench3D * WExternalAction4 = sys.new_Wrench3D ( "WExternalAction4", F4, M4, C4 , BAR4U , "Constitutive") ;
	Wrench3D * WExternalAction5 = sys.new_Wrench3D ( "WExternalAction5", F5, M5, C5 , BAR5U , "Constitutive") ;
	Wrench3D * WExternalAction6 = sys.new_Wrench3D ( "WExternalAction6", F6, M6, C6 , BAR6U , "Constitutive") ;

// 	Wrench3D * WExternalReaction1 = sys.new_Wrench3D ( "WExternalReaction1", -F1, M1, A1 , BAR1D , "Constitutive") ;
// 	Wrench3D * WExternalReaction2 = sys.new_Wrench3D ( "WExternalReaction2", -F2, M2, A2 , BAR2D , "Constitutive") ;
// 	Wrench3D * WExternalReaction3 = sys.new_Wrench3D ( "WExternalReaction3", -F3, M3, A3 , BAR3D , "Constitutive") ;
// 	Wrench3D * WExternalReaction4 = sys.new_Wrench3D ( "WExternalReaction4", -F4, M4, A4 , BAR4D , "Constitutive") ;
// 	Wrench3D * WExternalReaction5 = sys.new_Wrench3D ( "WExternalReaction5", -F5, M5, A5 , BAR5D , "Constitutive") ;
// 	Wrench3D * WExternalReaction6 = sys.new_Wrench3D ( "WExternalReaction6", -F6, M6, A6 , BAR6D , "Constitutive") ;

		
//*
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
//*/

//*
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
// 	 Kinematic Equations 
// ************************************************************************************************
	cout << "Kinematic Equations" << endl;
	//~ Vector3D eq1 = OA1+A1C1-OP-PD1;
	//~ Vector3D eq2 = OA2+A2C2-OP-PD2;
	//~ Vector3D eq3 = OA3+A3C3-OP-PD3;
	//~ Vector3D eq4 = OA4+A4C4-OP-PD4;
	//~ Vector3D eq5 = OA5+A5C5-OP-PD5;
	//~ Vector3D eq6 = OA6+A6C6-OP-PD6;
    
    Vector3D eq1 =sys.Position_Vector ( C1 , D1 ) ;
    Vector3D eq2 =sys.Position_Vector ( C2 , D2 ) ;
    Vector3D eq3 =sys.Position_Vector ( C3 , D3 ) ;
    Vector3D eq4 =sys.Position_Vector ( C4 , D4 ) ;
    Vector3D eq5 =sys.Position_Vector ( C5 , D5 ) ;
    Vector3D eq6 =sys.Position_Vector ( C6 , D6 ) ;

	Matrix Phi(24,1);
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
	Phi(17,0)=eq6(2,0);//*/

/*
	Phi(18,0)=s1-7.0-0.5*sin(t);
	Phi(19,0)=s2-7.0-0.5*sin(t);
	Phi(20,0)=s3-7.0-0.5*sin(t);
	Phi(21,0)=s4-7.0-0.5*sin(t);
	Phi(22,0)=s5-7.0-0.5*sin(t);
	Phi(23,0)=s6-7.0-0.5*sin(t);
//*/

//*
 	Phi(18,0)=x;
 	Phi(19,0)=y;
 	Phi(20,0)=z-5.0;
 	Phi(21,0)=a-0.5*sin(5.0*tim);
 	Phi(22,0)=b-0.5*cos(5.0*tim);
 	Phi(23,0)=c;
//*/


// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************
	cout << "Dynamic Equations" << endl;

	//Matrix Dynamic_Equations = sys.GenForceSys("ALL");
	//cout<<Dynamic_Equations<<endl;

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
	//sys.Matrix_Calculation(Phi, coord_indep_init, vel_indep_init, Dynamic_Equations, sys, METHOD);
    
	sys.Matrix_Calculation(Phi, coord_indep_init, vel_indep_init,  sys, METHOD);

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

//     	state = x,*dx,*ddx,y,*dy,*ddy,z,*dz,*ddz,a,*da,*dda,b,*dB,*ddB,c,*dc,*ddc,r,*dr,*ddr,t1,*dt1,*ddt1,t2,*dt2,*ddt2,t3,*dt3,*ddt3 ;
    	state = x,*dx,*ddx,y,*dy,*ddy,z,*dz,*ddz,a,*da,*dda,b,*dB,*ddB,c,*dc,*ddc,
		a1,*da1,*dda1,b1,*dB1,*ddB1,s1,*ds1,*dds1,
		a2,*da2,*dda2,b2,*dB2,*ddB2,s2,*ds2,*dds2,
		a3,*da3,*dda3,b3,*dB3,*ddB3,s3,*ds3,*dds3,
		a4,*da4,*dda4,b4,*dB4,*ddB4,s4,*ds4,*dds4,
		a5,*da5,*dda5,b5,*dB5,*ddB5,s5,*ds5,*dds5,
		a6,*da6,*dda6,b6,*dB6,*ddB6,s6,*ds6,*dds6;

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


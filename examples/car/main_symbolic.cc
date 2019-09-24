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
cout << "*             ILTIS Benchmark                  *" << endl;
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
//	Chassi
// ************************************************************************************************

// ************************************************************************************************
//	Coordinate definition
// ************************************************************************************************

// Translation of chassi
	symbol_numeric L01 = *sys.new_Coordinate("L01","dL01","ddL01",0.0, 0.0 , 0.0);
	symbol_numeric L02 = *sys.new_Coordinate("L02","dL02","ddL02",0.0, 0.0 , 0.0);
	symbol_numeric L03 = *sys.new_Coordinate("L03","dL03","ddL03",0.0, 0.0 , 0.0);
//Rotation of chassi
	symbol_numeric alpha01 = *sys.new_Coordinate("alpha01","dalpha01","ddalpha01",0.0, 0.0 , 0.0);
	symbol_numeric alpha02 = *sys.new_Coordinate("alpha02","dalpha02","ddalpha02",0.0, 0.0 , 0.0);
	symbol_numeric alpha03 = *sys.new_Coordinate("alpha03","dalpha03","ddalpha03",0.0, 0.0 , 0.0);
//Coordinates of center of gravity


     
	symbol_numeric *dL01=sys.get_Velocity("dL01");
	symbol_numeric *dL02=sys.get_Velocity("dL02");
	symbol_numeric *dL03=sys.get_Velocity("dL03");

	symbol_numeric *dalpha01=sys.get_Velocity("dalpha01");
	symbol_numeric *dalpha02=sys.get_Velocity("dalpha02");
	symbol_numeric *dalpha03=sys.get_Velocity("dalpha03");

	symbol_numeric *ddL01=sys.get_Acceleration("ddL01");
	symbol_numeric *ddL02=sys.get_Acceleration("ddL02");
	symbol_numeric *ddL03=sys.get_Acceleration("ddL03");

	symbol_numeric *ddalpha01=sys.get_Acceleration("ddalpha01");
	symbol_numeric *ddalpha02=sys.get_Acceleration("ddalpha02");
	symbol_numeric *ddalpha03=sys.get_Acceleration("ddalpha03");

	lst coord_indep_init;
	lst vel_indep_init;

//	coord_indep_init = (alpha01-0),(alpha02-0),(alpha03-0),(L01-0),(L02-0),(L03-0);

// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************
	//distance to the front
//symbol_numeric L01 = *sys.new_Parameter("L01",0.0);
//symbol_numeric L02 = *sys.new_Parameter("L02",0.0);
//symbol_numeric L03 = *sys.new_Parameter("L03",0.0);



	symbol_numeric L04 = *sys.new_Parameter("L04",0.94);
	//distance to the rear
	symbol_numeric L05 = *sys.new_Parameter("L05",-1.047);



	//gravity constant
	//symbol_numeric g =*sys.new_Parameter("g",9.81);
	//distance from origin in y direction
	//symbol_numeric L06 = *sys.new_Parameter("L06",0.0);



// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

 	sys.new_Base("BCHASSI01","xyz",1,0,0,alpha01);
 	sys.new_Base("BCHASSI02","BCHASSI01",0,1,0,alpha02);
 	sys.new_Base("BCHASSI03","BCHASSI02",0,0,1,alpha03);


// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	Vector3D O_A01Chassi = *sys.new_Vector3D("O_A01Chassi",L01,L02,L03,"xyz");
	

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * A01_Chassi = sys.new_Point("A01_Chassi","O",&O_A01Chassi);	
	
	
// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	
	// Dynamic Parameters of Chassi
    	symbol_numeric mChassi = *sys.new_Parameter("mChassi",1260.0);

	symbol_numeric mxChassi = *sys.new_Parameter("mxChassi",0.0);	
    	symbol_numeric myChassi = *sys.new_Parameter("myChassi",0.0);
	symbol_numeric mzChassi = *sys.new_Parameter("mzChassi",0.0);

    	symbol_numeric IxxChassi = *sys.new_Parameter("IxxChassi",539.374);
	symbol_numeric IxyChassi = *sys.new_Parameter("IxyChassi",0.0);
    	symbol_numeric IyyChassi = *sys.new_Parameter("IyyChassi",1999.374);
	symbol_numeric IxzChassi = *sys.new_Parameter("IxzChassi",0.0);
    	symbol_numeric IzzChassi = *sys.new_Parameter("IzzChassi",1640.0);
	symbol_numeric IyzChassi = *sys.new_Parameter("IyzChassi",0.0);

	
	//Gravity Center Vectors    

	Vector3D A01Chassi_GChassi= *sys.new_Vector3D("A01Chassi_GChassi",mxChassi/mChassi,myChassi/mChassi,mzChassi/mChassi,"BCHASSI03");
	
	

	//Inertia Tensors

    	Tensor3D IChassi_A = *sys.new_Tensor3D("IChassi_A",(ex) IxxChassi,(ex)IxyChassi,(ex)IxzChassi,(ex)IxyChassi,(ex)IyyChassi,(ex)IyzChassi,(ex)IxzChassi,(ex)IyzChassi,(ex)IzzChassi,"BCHASSI03");
    	
// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	
	Frame * Fra_Chassi01 = sys.new_Frame("Fra_Chassi01","A01_Chassi","BCHASSI03");



// ************************************************************************************************
//	Define Solids
// ************************************************************************************************
	
	
	Solid * Chassi = sys.new_Solid("Chassi","A01_Chassi","BCHASSI03","mChassi","A01Chassi_GChassi","IChassi_A");
      



// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************
	
     //   Drawing3D * Chassi3D = sys.new_Drawing3D("Chassi3D", "Chassi","./solids/ch2.stl",1,0,0,0.35);		
       

// ************************************************************************************************
//	Front Left Part
// ************************************************************************************************

// ************************************************************************************************
//	Coordinate definition
// ************************************************************************************************
	
	//A-arm angle
	symbol_numeric betha11 = *sys.new_Coordinate("betha11","dbetha11","ddbetha11",0.0, 0.0 , 0.0);
	// Leaf-spring angle
	symbol_numeric betha12 = *sys.new_Coordinate("betha12","dbetha12","ddbetha12",0.0, 0.0 , 0.0);
	
	//Shock Absorber angle 1
	symbol_numeric betha15 = *sys.new_Coordinate("betha15","dbetha15","ddbetha15",0.0, 0.0 , 0.0);	
	//Shock Absorber angle 2
	symbol_numeric betha16 = *sys.new_Coordinate("betha16","dbetha16","ddbetha16",0.0, 0.0 , 0.0);
	//Shock Absorber movement
	symbol_numeric L111 = *sys.new_Coordinate("L111","dL111","ddL111",0.0, 0.0 , 0.0);
	//Tie-rod chassi movement
	symbol_numeric L18 = *sys.new_Coordinate("L18","dL18","ddL18",0.0, 0.0 , 0.0);
	//Tie-rod angle 1
	symbol_numeric betha13 = *sys.new_Coordinate("betha13","dbetha13","ddbetha13",0.0, 0.0 , 0.0);
	//Tie-rod angle 2
	symbol_numeric betha14 = *sys.new_Coordinate("betha14","dbetha14","ddbetha14",0.0, 0.0 , 0.0);
	//Hub translation x
	symbol_numeric L11 = *sys.new_Coordinate("L11","dL11","ddL11",0.97, 0.0 , 0.0);
	//Hub translation y
	symbol_numeric L12 = *sys.new_Coordinate("L12","dL12","ddL12",0.615, 0.0 , 0.0);
	//Hub translation z
	symbol_numeric L13 = *sys.new_Coordinate("L13","dL13","ddL13",0.356, 0.0 , 0.0);
	//Hub angle 1
	symbol_numeric alpha11 = *sys.new_Coordinate("alpha11","dalpha11","ddalpha11",0.0, 0.0 , 0.0);
	//Hub angle 2
	symbol_numeric alpha12 = *sys.new_Coordinate("alpha12","dalpha12","ddalpha12",0.0, 0.0 , 0.0);
	//Hub angle 3
	symbol_numeric alpha13 = *sys.new_Coordinate("alpha13","dalpha13","ddalpha13",0.0, 0.0 , 0.0);
	//Wheel rotation
	symbol_numeric alpha14 = *sys.new_Coordinate("alpha14","dalpha14","ddalpha14",0.0, 0.0 , 0.0);


	//Velocity
	symbol_numeric *dbetha11=sys.get_Velocity("dbetha11");
	symbol_numeric *dbetha12=sys.get_Velocity("dbetha12");

	symbol_numeric *dbetha15=sys.get_Velocity("dbetha15");
	symbol_numeric *dbetha16=sys.get_Velocity("dbetha16");
	symbol_numeric *dL111=sys.get_Velocity("dL111");
	symbol_numeric *dL18=sys.get_Velocity("dL18");
	symbol_numeric *dbetha13=sys.get_Velocity("dbetha13");
	symbol_numeric *dbetha14=sys.get_Velocity("dbetha14");
	symbol_numeric *dL11=sys.get_Velocity("dL11");
	symbol_numeric *dL12=sys.get_Velocity("dL12");
	symbol_numeric *dL13=sys.get_Velocity("dL13");
	symbol_numeric *dalpha11=sys.get_Velocity("dalpha11");
	symbol_numeric *dalpha12=sys.get_Velocity("dalpha12");
	symbol_numeric *dalpha13=sys.get_Velocity("dalpha13");
	symbol_numeric *dalpha14=sys.get_Velocity("dalpha14");
	
	//Acceleration
	symbol_numeric *ddbetha11=sys.get_Acceleration("ddbetha11");
	symbol_numeric *ddbetha12=sys.get_Acceleration("ddbetha12");

	symbol_numeric *ddbetha15=sys.get_Acceleration("ddbetha15");
	symbol_numeric *ddbetha16=sys.get_Acceleration("ddbetha16");
	symbol_numeric *ddL111=sys.get_Acceleration("ddL111");
	symbol_numeric *ddL18=sys.get_Acceleration("ddL18");
	symbol_numeric *ddbetha13=sys.get_Acceleration("ddbetha13");
	symbol_numeric *ddbetha14=sys.get_Acceleration("ddbetha14");
	symbol_numeric *ddL11=sys.get_Acceleration("ddL11");
	symbol_numeric *ddL12=sys.get_Acceleration("ddL12");
	symbol_numeric *ddL13=sys.get_Acceleration("ddL13");
	symbol_numeric *ddalpha11=sys.get_Acceleration("ddalpha11");
	symbol_numeric *ddalpha12=sys.get_Acceleration("ddalpha12");
	symbol_numeric *ddalpha13=sys.get_Acceleration("ddalpha13");
	symbol_numeric *ddalpha14=sys.get_Acceleration("ddalpha14");


	

	


// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************
	
	// WHEELS 
	// Radius of the wheels
	symbol_numeric R = *sys.new_Parameter("R",1.0);

	
	//A-arm
	//A-arm lenght
	symbol_numeric L14 = *sys.new_Parameter("L14",0.32140006);
	//A-arm connection to chassi x
	symbol_numeric L141 = *sys.new_Parameter("L141",0.97);
	//A-arm connection to chassi y
	symbol_numeric L142 = *sys.new_Parameter("L142",0.259);
	//A-arm connection to chassi z
	symbol_numeric L143 = *sys.new_Parameter("L143",0.302);
	//A-arm and shock absorber connextion x
	symbol_numeric L144 = *sys.new_Parameter("L144",0.075);
	//A-arm and shock absorber connextion y
	symbol_numeric L145 = *sys.new_Parameter("L145",-0.241);
	//A-arm and shock absorber connextion Z
	symbol_numeric L146 = *sys.new_Parameter("L146",-0.061);
	
	//Leaf-spring
	//Leaf sprign lenght
	symbol_numeric L16 = *sys.new_Parameter("L16",0.33664707);
	//Leaf spring connection to chassi x
	symbol_numeric L161 = *sys.new_Parameter("L161",0.97);
	//Leaf spring connection to chassi y
	symbol_numeric L162 = *sys.new_Parameter("L162",0.1585);
	//Leaf spring connection to chassi z
	symbol_numeric L163 = *sys.new_Parameter("L163",0.600);

	//Shock absorber
	//Shock absorber lenght of part 1
	symbol_numeric L15 = *sys.new_Parameter("L15",0.220278233);
	//Shock absorber lenght of part 2
	symbol_numeric L151 = *sys.new_Parameter("L151",0.2937043107);	
	//Shock absorber connection to the chassi x
	symbol_numeric L152 = *sys.new_Parameter("L152",1.045);	
	//Shock absorber connection to the chassi y
	symbol_numeric L153 = *sys.new_Parameter("L153",0.297);
	//Shock absorber connection to the chassi z
	symbol_numeric L154 = *sys.new_Parameter("L154",0.632);	

	//Tie-rod
	//Tie rod lenght
//symbol_numeric L18 = *sys.new_Parameter("L18",0.0);
	symbol_numeric L17 = *sys.new_Parameter("L17",0.384246015);
	//Tie-rod movement point x
	symbol_numeric L171 = *sys.new_Parameter("L171",0.83);
	//Tie-rod movement point z
	symbol_numeric L173 = *sys.new_Parameter("L173",0.600);
	//Tie-rod connection to chassi y
	symbol_numeric L172 = *sys.new_Parameter("L172",0.07);

	//Hub
	//Hub center x

	
	//Connection point of hub and A-arm y
	symbol_numeric L191 = *sys.new_Parameter("L191",-0.043);
	//Connection point of hub and A-arm z
	symbol_numeric L192 = *sys.new_Parameter("L192",-0.127);
	
	//Connection point of hub and Leaf-spring y
	symbol_numeric L193 = *sys.new_Parameter("L193",-0.127);
	//Connection point of hub and Leaf-spring z
	symbol_numeric L194 = *sys.new_Parameter("L194",0.175);

	//Connection point of hub and Tie-rod x
	symbol_numeric L195 = *sys.new_Parameter("L195",-0.14);
	//Connection point of hub and Tie-rod y
	symbol_numeric L196 = *sys.new_Parameter("L196",-0.167);
	//Connection point of hub and Tie-rod z
	symbol_numeric L197 = *sys.new_Parameter("L197",0.175);

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************


	//A-arm
 	sys.new_Base("BARM11","BCHASSI03",1,0,0,-betha11);
	//Leaf-spring
 	sys.new_Base("BLS11","BCHASSI03",1,0,0,-betha12);
	//Schock-Absorber
 	sys.new_Base("BSA11","BCHASSI03",1,0,0,-betha15);
	sys.new_Base("BSA12","BSA11",0,0,1,-betha16);
	//Tie-rod
 	sys.new_Base("BTR11","BCHASSI03",1,0,0,betha13);
	sys.new_Base("BTR12","BTR11",0,0,1,betha14);
	//Hub
 	sys.new_Base("BHUB11","xyz",1,0,0,alpha11);
 	sys.new_Base("BHUB12","BHUB11",0,1,0,alpha12);
	sys.new_Base("BHUB13","BHUB12",0,0,1,alpha13);
	//Wheel
	sys.new_Base("BHUB14","BHUB13",0,1,0,alpha14);

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	//Connection points to chassi
	//A-rm	
	Vector3D A01_B11AARM = *sys.new_Vector3D("A01_B11AARM",L141,L142,L143,"BCHASSI03");
	//Leaf spring
	Vector3D A01_B12LS = *sys.new_Vector3D("A01_B12LS",L161,L162,L163,"BCHASSI03");
	//Shock absorber
	Vector3D A01_B13SA = *sys.new_Vector3D("A01_B13SA",L152,L153,L154,"BCHASSI03");
	//Tie-rod
	Vector3D A01_B15TR = *sys.new_Vector3D("A01_B15TR",L171,L18,L173,"BCHASSI03");
	Vector3D B15_B14TR = *sys.new_Vector3D("B15_B14TR",0,L172,0,"BCHASSI03");

	//End points of parts
	//A-arm
	Vector3D B11_E11AARM = *sys.new_Vector3D("B11_E11AARM",0,L14,0,"BARM11");
	//Leaf-spring
	Vector3D B12_E12LS = *sys.new_Vector3D("B12_E12LS",0,L16,0,"BLS11");
	//Schock absorber
	Vector3D B13_E14SA = *sys.new_Vector3D("B13_E14SA",0,L15,0,"BSA12");
	Vector3D B13_E13SA = *sys.new_Vector3D("B13_E13SA",0,L111,0,"BSA12");
	Vector3D E13_E15SA = *sys.new_Vector3D("E13_E15SA",0,L151,0,"BSA12");
	//Tie-rod
	Vector3D B14_E16TR = *sys.new_Vector3D("B14_E16TR",0,L17,0,"BTR12");
	

	//Additional points
	//Schock absorber connection point with A-arm
	Vector3D E11_E112AARM = *sys.new_Vector3D("E11_E112AARM",L144,L145,L146,"BARM11");
	//Distance from leaf spring and damper
	Vector3D E12_E121LS = *sys.new_Vector3D("E12_E121LS",0.0,0.0,0.145-(L16*sin(betha12)),"BCHASSI03");	
//L162+cos(betha12)
	//Hub
	//Center point of hub
	Vector3D O_C11HUB = *sys.new_Vector3D("O_C11HUB",L11,L12,L13,"xyz");

	//Connection point with A-arm
	Vector3D C11_D11HUB = *sys.new_Vector3D("C11_D11HUB",0,L191,L192,"BHUB13");
	//Connection point with Leaf spring
	Vector3D C11_D12HUB = *sys.new_Vector3D("C11_D12HUB",0,L193,L194,"BHUB13");
	//Connection with Tie-rod
	Vector3D C11_D13HUB = *sys.new_Vector3D("C11_D13HUB",L195,L196,L197,"BHUB13");
	

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	//Connection points to chassi
	//A-arm
	Point * B11 = sys.new_Point("B11","A01_Chassi",&A01_B11AARM);
	//Leaf-spring	
	Point * B12 = sys.new_Point("B12","A01_Chassi",&A01_B12LS);
	//Shock-Absorber
	Point * B13 = sys.new_Point("B13","A01_Chassi",&A01_B13SA);
	//Tie-rod
	Point * B15 = sys.new_Point("B15","A01_Chassi",&A01_B15TR);
	Point * B14 = sys.new_Point("B14","B15",&B15_B14TR);

	//End points
	//A-arm
	Point * E11 = sys.new_Point("E11","B11",&B11_E11AARM);
	//Leaf-spring	
	Point * E12 = sys.new_Point("E12","B12",&B12_E12LS);
	//Shock absorber
	Point * E13 = sys.new_Point("E13","B13",&B13_E13SA);
	Point * E14 = sys.new_Point("E14","B13",&B13_E14SA);
	Point * E15 = sys.new_Point("E15","E13",&E13_E15SA);	
	//Tie-rod
	Point * E16 = sys.new_Point("E16","B14",&B14_E16TR);

	//Additional points
	//Shock absorber connection point with A-arm
	Point * E112 = sys.new_Point("E112","E11",&E11_E112AARM);
	//Bumper point
	Point * E121 = sys.new_Point("E121","A01_Chassi",&E12_E121LS);

	//Hub
	//Hub center point
	Point * C11 = sys.new_Point("C11","O",&O_C11HUB);
	//Hub connection to A-arm
	Point * D11 = sys.new_Point("D11","C11",&C11_D11HUB);
	//Hub connection to Leaf spring
	Point * D12 = sys.new_Point("D12","C11",&C11_D12HUB);
	//Hub connection to Tie-rod
	Point * D13 = sys.new_Point("D13","C11",&C11_D13HUB);	


// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************
	// Viscosity
       	symbol_numeric  Cvis11 = *sys.new_Parameter("Cvis11",0.8);
	// Torsion spring
       	symbol_numeric  K11 = *sys.new_Parameter("K11",1.0);
	
	// Dynamic Parameters of A-arm
    	symbol_numeric  mAarm11 = *sys.new_Parameter("mAarm11",6.0);

	symbol_numeric  mxAarm11 = *sys.new_Parameter("mxAarm11",0.0);	
    	symbol_numeric  myAarm11 = *sys.new_Parameter("myAarm11",0.0);
	symbol_numeric  mzAarm11 = *sys.new_Parameter("mzAarm11",0.0);

    	symbol_numeric  IxxAarm11 = *sys.new_Parameter("IxxAarm11",0.1990525);
	symbol_numeric  IxyAarm11 = *sys.new_Parameter("IxyAarm11",0.0);
    	symbol_numeric  IyyAarm11 = *sys.new_Parameter("IyyAarm11",0.023235);
	symbol_numeric  IxzAarm11 = *sys.new_Parameter("IxzAarm11",0.0);
    	symbol_numeric  IzzAarm11 = *sys.new_Parameter("IzzAarm11",0.2158175);
	symbol_numeric  IyzAarm11 = *sys.new_Parameter("IyzAarm11",0.0);

	// Dynamic Parameters of Leaf spring
    	symbol_numeric  mLS11 = *sys.new_Parameter("mLS11",1.0);

	symbol_numeric  mxLS11 = *sys.new_Parameter("mxLS11",0.0);	
    	symbol_numeric  myLS11 = *sys.new_Parameter("myLS11",0.0);
	symbol_numeric  mzLS11 = *sys.new_Parameter("mzLS11",0.0);

    	symbol_numeric  IxxLS11 = *sys.new_Parameter("IxxLS11",1.0);
	symbol_numeric  IxyLS11 = *sys.new_Parameter("IxyLS11",0.0);
    	symbol_numeric  IyyLS11 = *sys.new_Parameter("IyyLS11",1.0);
	symbol_numeric  IxzLS11 = *sys.new_Parameter("IxzLS11",0.0);
    	symbol_numeric  IzzLS11 = *sys.new_Parameter("IzzLS11",1.0);
	symbol_numeric  IyzLS11 = *sys.new_Parameter("IyzLS11",0.0);

/*	// Dynamic Parameters of Leaf spring Chassi part
    	symbol_numeric  mLS12 = *sys.new_Parameter("mLS12",1.0);

	symbol_numeric  mxLS12 = *sys.new_Parameter("mxLS12",0.0);	
    	symbol_numeric  myLS12 = *sys.new_Parameter("myLS12",0.0);
	symbol_numeric  mzLS12 = *sys.new_Parameter("mzLS12",0.0);

    	symbol_numeric  IxxLS12 = *sys.new_Parameter("IxxLS12",1.0);
	symbol_numeric  IxyLS12 = *sys.new_Parameter("IxyLS12",0.0);
    	symbol_numeric  IyyLS12 = *sys.new_Parameter("IyyLS12",1.0);
	symbol_numeric  IxzLS12 = *sys.new_Parameter("IxzLS12",0.0);
    	symbol_numeric  IzzLS12 = *sys.new_Parameter("IzzLS12",1.0);
	symbol_numeric  IyzLS12 = *sys.new_Parameter("IyzLS12",0.0);
*/
	// Dynamic Parameters of Shock absorber part 1
    	symbol_numeric  mSA11 = *sys.new_Parameter("mSA11",1.0);

	symbol_numeric  mxSA11 = *sys.new_Parameter("mxSA11",0.0);	
    	symbol_numeric  mySA11 = *sys.new_Parameter("mySA11",0.0);
	symbol_numeric  mzSA11 = *sys.new_Parameter("mzSA11",0.0);

    	symbol_numeric  IxxSA11 = *sys.new_Parameter("IxxSA11",1.0);
	symbol_numeric  IxySA11 = *sys.new_Parameter("IxySA11",0.0);
    	symbol_numeric  IyySA11 = *sys.new_Parameter("IyySA11",1.0);
	symbol_numeric  IxzSA11 = *sys.new_Parameter("IxzSA11",0.0);
    	symbol_numeric  IzzSA11 = *sys.new_Parameter("IzzSA11",1.0);
	symbol_numeric  IyzSA11 = *sys.new_Parameter("IyzSA11",0.0);

	// Dynamic Parameters of Shock absorber part 2
    	symbol_numeric  mSA12 = *sys.new_Parameter("mSA12",1.0);

	symbol_numeric  mxSA12 = *sys.new_Parameter("mxSA12",0.0);	
    	symbol_numeric  mySA12 = *sys.new_Parameter("mySA12",0.0);
	symbol_numeric  mzSA12 = *sys.new_Parameter("mzSA12",0.0);

    	symbol_numeric  IxxSA12 = *sys.new_Parameter("IxxSA12",1.0);
	symbol_numeric  IxySA12 = *sys.new_Parameter("IxySA12",0.0);
    	symbol_numeric  IyySA12 = *sys.new_Parameter("IyySA12",1.0);
	symbol_numeric  IxzSA12 = *sys.new_Parameter("IxzSA12",0.0);
    	symbol_numeric  IzzSA12 = *sys.new_Parameter("IzzSA12",1.0);
	symbol_numeric  IyzSA12 = *sys.new_Parameter("IyzSA12",0.0);

	// Dynamic Parameters of Tie-rod
    	symbol_numeric  mTR11 = *sys.new_Parameter("mTR11",100.0);

	symbol_numeric  mxTR11 = *sys.new_Parameter("mxTR11",0.0);	
    	symbol_numeric  myTR11 = *sys.new_Parameter("myTR11",0.0);
	symbol_numeric  mzTR11 = *sys.new_Parameter("mzTR11",0.0);

    	symbol_numeric  IxxTR11 = *sys.new_Parameter("IxxTR11",1.0);
	symbol_numeric  IxyTR11 = *sys.new_Parameter("IxyTR11",0.0);
    	symbol_numeric  IyyTR11 = *sys.new_Parameter("IyyTR11",1.0);
	symbol_numeric  IxzTR11 = *sys.new_Parameter("IxzTR11",0.0);
    	symbol_numeric  IzzTR11 = *sys.new_Parameter("IzzTR11",1.0);
	symbol_numeric  IyzTR11 = *sys.new_Parameter("IyzTR11",0.0);

	// Dynamic Parameters of Hub
    	symbol_numeric  mHUB11 = *sys.new_Parameter("mHUB11",19.117);

	symbol_numeric  mxHUB11 = *sys.new_Parameter("mxHUB11",0.0);	
    	symbol_numeric  myHUB11 = *sys.new_Parameter("myHUB11",0.0);
	symbol_numeric  mzHUB11 = *sys.new_Parameter("mzHUB11",0.0);

    	symbol_numeric  IxxHUB11 = *sys.new_Parameter("IxxHUB11",1.0);
	symbol_numeric  IxyHUB11 = *sys.new_Parameter("IxyHUB11",0.0);
    	symbol_numeric  IyyHUB11 = *sys.new_Parameter("IyyHUB11",1.0);
	symbol_numeric  IxzHUB11 = *sys.new_Parameter("IxzHUB11",0.0);
    	symbol_numeric  IzzHUB11 = *sys.new_Parameter("IzzHUB11",1.0);
	symbol_numeric  IyzHUB11 = *sys.new_Parameter("IyzHUB11",0.0);

	// Dynamic Parameters of Wheel
    	symbol_numeric  mWH11 = *sys.new_Parameter("mWH11",38.23);

	symbol_numeric  mxWH11 = *sys.new_Parameter("mxWH11",0.0);	
    	symbol_numeric  myWH11 = *sys.new_Parameter("myWH11",0.0);
	symbol_numeric  mzWH11 = *sys.new_Parameter("mzWH11",0.0);

    	symbol_numeric  IxxWH11 = *sys.new_Parameter("IxxWH11",1.2402);
	symbol_numeric  IxyWH11 = *sys.new_Parameter("IxyWH11",0.0);
    	symbol_numeric  IyyWH11 = *sys.new_Parameter("IyyWH11",1.908);
	symbol_numeric  IxzWH11 = *sys.new_Parameter("IxzWH11",0.0);
    	symbol_numeric  IzzWH11 = *sys.new_Parameter("IzzWH11",1.2402);
	symbol_numeric  IyzWH11 = *sys.new_Parameter("IyzWH11",0.0);

	//Gravity Center Vectors    

	Vector3D B11Arm11_GArm11= *sys.new_Vector3D("B11Arm11_GArm11",mxAarm11/mAarm11,myAarm11/mAarm11,mzAarm11/mAarm11,"BARM11");
	Vector3D B12LS11_GLS11= *sys.new_Vector3D("B12LS11_GLS11",mxLS11/mLS11,myLS11/mLS11,mzLS11/mLS11,"BLS11");

//	Vector3D B12LS11_GLS12= *sys.new_Vector3D("B12LS12_GLS12",mxLS12/mLS12,myLS12/mLS12,mzLS12/mLS12,"BCHASSI03");

	Vector3D B13SA11_GSA11= *sys.new_Vector3D("B13SA11_GSA11",mxSA11/mSA11,mySA11/mSA11,mzSA11/mSA11,"BSA12");
	Vector3D E13SA12_GSA12= *sys.new_Vector3D("E13SA12_GSA12",mxSA12/mSA12,mySA12/mSA12,mzSA12/mSA12,"BSA12");
	Vector3D B14TR11_GTR11= *sys.new_Vector3D("B14TR11_GTR11",mxTR11/mTR11,myTR11/mTR11,mzTR11/mTR11,"BTR12");
	Vector3D C11HUB11_GHUB11= *sys.new_Vector3D("C11HUB11_GHUB11",mxHUB11/mHUB11,myHUB11/mHUB11,mzHUB11/mHUB11,"BHUB13");
	Vector3D C11WH11_GWH11= *sys.new_Vector3D("C11WH11_GWH11",mxWH11/mWH11,myWH11/mWH11,mzWH11/mWH11,"BHUB14");


	//Inertia Tensors

    	Tensor3D IAarm11 = *sys.new_Tensor3D("IAarm11",(ex)IxxAarm11,(ex)IxyAarm11,(ex)IxzAarm11,(ex)IxyAarm11,(ex)IyyAarm11,(ex)IyzAarm11,(ex)IxzAarm11,(ex)IyzAarm11,(ex)IzzAarm11,"BARM11");
    	Tensor3D ILS11 = *sys.new_Tensor3D("ILS11",(ex)IxxLS11,(ex)IxyLS11,(ex)IxzLS11,(ex)IxyLS11,(ex)IyyLS11,(ex)IyzLS11,(ex)IxzLS11,(ex)IyzLS11,(ex)IzzLS11,"BLS11");


//Tensor3D ILS12 = *sys.new_Tensor3D("ILS12",(ex)IxxLS12,(ex)IxyLS12,(ex)IxzLS12,(ex)IxyLS12,(ex)IyyLS12,(ex)IyzLS12,(ex)IxzLS12,(ex)IyzLS12,(ex)IzzLS12,"BCHASSI03");




    	Tensor3D ISA11 = *sys.new_Tensor3D("ISA11",(ex)IxxSA11,(ex)IxySA11,(ex)IxzSA11,(ex)IxySA11,(ex)IyySA11,(ex)IyzSA11,(ex)IxzSA11,(ex)IyzSA11,(ex)IzzSA11,"BSA12");
    	Tensor3D ISA12 = *sys.new_Tensor3D("ISA12",(ex)IxxSA12,(ex)IxySA12,(ex)IxzSA12,(ex)IxySA12,(ex)IyySA12,(ex)IyzSA12,(ex)IxzSA12,(ex)IyzSA12,(ex)IzzSA12,"BSA12");
    	Tensor3D ITR11 = *sys.new_Tensor3D("ITR11",(ex)IxxTR11,(ex)IxyTR11,(ex)IxzTR11,(ex)IxyTR11,(ex)IyyTR11,(ex)IyzTR11,(ex)IxzTR11,(ex)IyzTR11,(ex)IzzTR11,"BTR12");
    	Tensor3D IHUB11 = *sys.new_Tensor3D("IHUB11",(ex)IxxHUB11,(ex)IxyHUB11,(ex)IxzHUB11,(ex)IxyHUB11,(ex)IyyHUB11,(ex)IyzHUB11,(ex)IxzHUB11,(ex)IyzHUB11,(ex)IzzHUB11,"BHUB13");
    	Tensor3D IWH11 = *sys.new_Tensor3D("IWH11",(ex)IxxWH11,(ex)IxyWH11,(ex)IxzWH11,(ex)IxyWH11,(ex)IyyWH11,(ex)IyzWH11,(ex)IxzWH11,(ex)IyzWH11,(ex)IzzWH11,"BHUB14");

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Aarm11 = sys.new_Frame("Fra_Aarm11","B11","BARM11");
	Frame * Fra_LS11 = sys.new_Frame("Fra_LS11","B12","BLS11");
	Frame * Fra_SA12 = sys.new_Frame("Fra_SA12","B13","BSA12");
	Frame * Fra_TR12 = sys.new_Frame("Fra_TR12","B14","BTR12");


	Frame * Fra_HUB13 = sys.new_Frame("Fra_HUB13","C11","BHUB13");
	Frame * Fra_WH11 = sys.new_Frame("Fra_WH11","C11","BHUB14");

// ************************************************************************************************
//	Define Solids
// ************************************************************************************************
	
	
	Solid * Aarm11 = sys.new_Solid("Aarm11","B11","BARM11","mAarm11","B11Arm11_GArm11","IAarm11");
	Solid * LS11 = sys.new_Solid("LS11","B12","BLS11","mLS11","B12LS11_GLS11","ILS11");


	//Solid * LS12 = sys.new_Solid("LS12","E121","BCHASSI03","mLS12","B12LS12_GLS12","ILS12");


	Solid * SA11 = sys.new_Solid("SA11","B13","BSA12","mSA11","B13SA11_GSA11","ISA11");
	Solid * SA12 = sys.new_Solid("SA12","E13","BSA12","mSA12","E13SA12_GSA12","ISA12");	
	Solid * TR11 = sys.new_Solid("TR11","B14","BTR12","mTR11","B14TR11_GTR11","ITR11");
	Solid * HUB11 = sys.new_Solid("HUB11","C11","BHUB13","mHUB11","C11HUB11_GHUB11","IHUB11");
	Solid * WH11 = sys.new_Solid("WH11","C11","BHUB14","mWH11","C11WH11_GWH11","IWH11");
      



// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************
	
        Drawing3D * Aarm113D = sys.new_Drawing3D("Aarm113D", "Aarm11","./solids/aarm11.stl",1,0,0,1);
         Drawing3D * LS113D = sys.new_Drawing3D("LS113D", "LS11","./solids/LS11.stl",1,0,0,1);
       Drawing3D * TR113D = sys.new_Drawing3D("TR113D", "TR11","./solids/TR11.stl",1,0,0,1);
        Drawing3D * SA113D = sys.new_Drawing3D("SA113D", "SA11","./solids/SA11.stl",1,0,0,0.5);
        Drawing3D * SA123D = sys.new_Drawing3D("SA123D", "SA12","./solids/SA12.stl",1,0,0,1);
        Drawing3D * HUB113D = sys.new_Drawing3D("HUB113D", "HUB11","./solids/hub11.stl",1,0,0,1);
     //   Drawing3D * WH113D = sys.new_Drawing3D("WH113D", "WH11","./solids/wh21.stl",1,0,0,1);

  // ************************************************************************************************
//	Front Right Part
// ************************************************************************************************

// ************************************************************************************************
//	Coordinate definition
// ************************************************************************************************
	
	//A-arm angle
	symbol_numeric betha21 = *sys.new_Coordinate("betha21","dbetha21","ddbetha21",0, 0.0 , 0.0);
	// Leaf-spring angle
	symbol_numeric betha22 = *sys.new_Coordinate("betha22","dbetha22","ddbetha22",0, 0.0 , 0.0);

	//Shock Absorber angle 1
	symbol_numeric betha25 = *sys.new_Coordinate("betha25","dbetha25","ddbetha25",0, 0.0 , 0.0);	
	//Shock Absorber angle 2
	symbol_numeric betha26 = *sys.new_Coordinate("betha26","dbetha26","ddbetha26",0.0, 0.0 , 0.0);
	//Shock Absorber movement
	symbol_numeric L211 = *sys.new_Coordinate("L211","dL211","ddL211",0, 0.0 , 0.0);

	//Tie-rod angle 1
	symbol_numeric betha23 = *sys.new_Coordinate("betha23","dbetha23","ddbetha23",0, 0.0 , 0.0);
	//Tie-rod angle 2
	symbol_numeric betha24 = *sys.new_Coordinate("betha24","dbetha24","ddbetha24",0, 0.0 , 0.0);
	//Hub translation x
	symbol_numeric L21 = *sys.new_Coordinate("L21","dL21","ddL21",0.97, 0.0 , 0.0);
	//Hub translation y
	symbol_numeric L22 = *sys.new_Coordinate("L22","dL22","ddL22",-0.615, 0.0 , 0.0);
	//Hub translation z
	symbol_numeric L23 = *sys.new_Coordinate("L23","dL23","ddL23",0.356, 0.0 , 0.0);
	//Hub angle 1
	symbol_numeric alpha21 = *sys.new_Coordinate("alpha21","dalpha21","ddalpha21",0, 0.0 , 0.0);
	//Hub angle 2
	symbol_numeric alpha22 = *sys.new_Coordinate("alpha22","dalpha22","ddalpha22",0, 0.0 , 0.0);
	//Hub angle 3
	symbol_numeric alpha23 = *sys.new_Coordinate("alpha23","dalpha23","ddalpha23",0, 0.0 , 0.0);
	//Wheel rotation
	symbol_numeric alpha24 = *sys.new_Coordinate("alpha24","dalpha24","ddalpha24",0, 0.0 , 0.0);


	//Velocity
	symbol_numeric *dbetha21=sys.get_Velocity("dbetha21");
	symbol_numeric *dbetha22=sys.get_Velocity("dbetha22");
	
	symbol_numeric *dbetha25=sys.get_Velocity("dbetha25");
	symbol_numeric *dbetha26=sys.get_Velocity("dbetha26");
	symbol_numeric *dL211=sys.get_Velocity("dL211");

	symbol_numeric *dbetha23=sys.get_Velocity("dbetha23");
	symbol_numeric *dbetha24=sys.get_Velocity("dbetha24");
	symbol_numeric *dL21=sys.get_Velocity("dL21");
	symbol_numeric *dL22=sys.get_Velocity("dL22");
	symbol_numeric *dL23=sys.get_Velocity("dL23");
	symbol_numeric *dalpha21=sys.get_Velocity("dalpha21");
	symbol_numeric *dalpha22=sys.get_Velocity("dalpha22");
	symbol_numeric *dalpha23=sys.get_Velocity("dalpha23");
	symbol_numeric *dalpha24=sys.get_Velocity("dalpha24");
	
	//Acceleration
	symbol_numeric *ddbetha21=sys.get_Acceleration("ddbetha21");
	symbol_numeric *ddbetha22=sys.get_Acceleration("ddbetha22");

	symbol_numeric *ddbetha25=sys.get_Acceleration("ddbetha25");
	symbol_numeric *ddbetha26=sys.get_Acceleration("ddbetha26");
	symbol_numeric *ddL211=sys.get_Acceleration("ddL211");

	symbol_numeric *ddbetha23=sys.get_Acceleration("ddbetha23");
	symbol_numeric *ddbetha24=sys.get_Acceleration("ddbetha24");
	symbol_numeric *ddL21=sys.get_Acceleration("ddL21");
	symbol_numeric *ddL22=sys.get_Acceleration("ddL22");
	symbol_numeric *ddL23=sys.get_Acceleration("ddL23");
	symbol_numeric *ddalpha21=sys.get_Acceleration("ddalpha21");
	symbol_numeric *ddalpha22=sys.get_Acceleration("ddalpha22");
	symbol_numeric *ddalpha23=sys.get_Acceleration("ddalpha23");
	symbol_numeric *ddalpha24=sys.get_Acceleration("ddalpha24");

// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************
	//A-arm
	//A-arm lenght
	symbol_numeric L24 = *sys.new_Parameter("L24",-0.32140006);
	//A-arm connection to chassi x
	symbol_numeric L241 = *sys.new_Parameter("L241",0.97);
	//A-arm connection to chassi y
	symbol_numeric L242 = *sys.new_Parameter("L242",-0.259);
	//A-arm connection to chassi z
	symbol_numeric L243 = *sys.new_Parameter("L243",0.302);
	//A-arm and shock absorber connextion x
	symbol_numeric L244 = *sys.new_Parameter("L244",0.075);
	//A-arm and shock absorber connextion y
	symbol_numeric L245 = *sys.new_Parameter("L245",0.241);
	//A-arm and shock absorber connextion Z
	symbol_numeric L246 = *sys.new_Parameter("L246",-0.061);
	
	//Leaf-spring
	//Leaf sprign lenght
	symbol_numeric L26 = *sys.new_Parameter("L26",-0.33664707);
	//Leaf spring connection to chassi x
	symbol_numeric L261 = *sys.new_Parameter("L261",0.97);
	//Leaf spring connection to chassi y
	symbol_numeric L262 = *sys.new_Parameter("L262",-0.1585);
	//Leaf spring connection to chassi z
	symbol_numeric L263 = *sys.new_Parameter("L263",0.600);

	//Shock absorber
	//Shock absorber lenght of part 1
	symbol_numeric L25 = *sys.new_Parameter("L25",-0.220278233);
	//Shock absorber lenght of part 2
	symbol_numeric L251 = *sys.new_Parameter("L251",-0.2937043107);	
	//Shock absorber connection to the chassi x
	symbol_numeric L252 = *sys.new_Parameter("L252",1.045);	
	//Shock absorber connection to the chassi y
	symbol_numeric L253 = *sys.new_Parameter("L253",-0.297);
	//Shock absorber connection to the chassi z
	symbol_numeric L254 = *sys.new_Parameter("L254",0.632);	

	//Tie-rod
	//Tie rod lenght
	symbol_numeric L27 = *sys.new_Parameter("L27",-0.384246015);
	//Tie-rod connection to chassi y
	symbol_numeric L272 = *sys.new_Parameter("L272",-0.07);

	//Hub

	
	//Connection point of hub and A-arm y
	symbol_numeric L291 = *sys.new_Parameter("L291",0.043);
	//Connection point of hub and A-arm z
	symbol_numeric L292 = *sys.new_Parameter("L292",-0.127);
	
	//Connection point of hub and Leaf-spring y
	symbol_numeric L293 = *sys.new_Parameter("L293",0.127);
	//Connection point of hub and Leaf-spring z
	symbol_numeric L294 = *sys.new_Parameter("L294",0.175);

	//Connection point of hub and Tie-rod x
	symbol_numeric L295 = *sys.new_Parameter("L295",-0.14);
	//Connection point of hub and Tie-rod y
	symbol_numeric L296 = *sys.new_Parameter("L296",0.167);
	//Connection point of hub and Tie-rod z
	symbol_numeric L297 = *sys.new_Parameter("L297",0.175);

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************



	//A-arm
 	sys.new_Base("BARM21","BCHASSI03",1,0,0,betha21);
	//Leaf-spring
 	sys.new_Base("BLS21","BCHASSI03",1,0,0,betha22);
	//Schock-Absorber
 	sys.new_Base("BSA21","BCHASSI03",1,0,0,betha25);
	sys.new_Base("BSA22","BSA21",0,0,1,betha26);
	//Tie-rod
 	sys.new_Base("BTR21","BCHASSI03",1,0,0,betha23);
	sys.new_Base("BTR22","BTR21",0,0,1,betha24);
	//Hub
 	sys.new_Base("BHUB21","xyz",1,0,0,alpha21);
 	sys.new_Base("BHUB22","BHUB21",0,1,0,alpha22);
	sys.new_Base("BHUB23","BHUB22",0,0,1,alpha23);
	//Wheel
	sys.new_Base("BHUB24","BHUB23",0,1,0,alpha24);

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	//Connection points to chassi
	//A-rm	
	Vector3D A01_B21AARM = *sys.new_Vector3D("A01_B21AARM",L241,L242,L243,"BCHASSI03");
	//Leaf spring
	Vector3D A01_B22LS = *sys.new_Vector3D("A01_B22LS",L261,L262,L263,"BCHASSI03");
	//Shock absorber
	Vector3D A01_B23SA = *sys.new_Vector3D("A01_B23SA",L252,L253,L254,"BCHASSI03");
	//Tie-rod
	
	Vector3D B15_B24TR = *sys.new_Vector3D("B15_B24TR",0,L272,0,"BCHASSI03");

	//End points of parts
	//A-arm
	Vector3D B21_E21AARM = *sys.new_Vector3D("B21_E21AARM",0,L24,0,"BARM21");
	//Leaf-spring
	Vector3D B22_E22LS = *sys.new_Vector3D("B22_E22LS",0,L26,0,"BLS21");
	//Schock absorber
	Vector3D B23_E24SA = *sys.new_Vector3D("B23_E24SA",0,L25,0,"BSA22");
	Vector3D B23_E23SA = *sys.new_Vector3D("B23_E23SA",0,L211,0,"BSA22");
	Vector3D E23_E25SA = *sys.new_Vector3D("E23_E25SA",0,L251,0,"BSA22");
	//Tie-rod
	Vector3D B24_E26TR = *sys.new_Vector3D("B24_E26TR",0,L27,0,"BTR22");
	

	//Additional points
	//Schock absorber connection point with A-arm
	Vector3D E21_E212AARM = *sys.new_Vector3D("E21_E212AARM",L244,L245,L246,"BARM21");
	//Distance from leaf spring and damper
	Vector3D E22_E221LS = *sys.new_Vector3D("E22_E221LS",0,0,0.145-(L26*sin(betha22)),"BCHASSI03");	

	//Hub
	//Center point of hub
	Vector3D O_C21HUB = *sys.new_Vector3D("O_C21HUB",L21,L22,L23,"xyz");
	//Connection point with A-arm
	Vector3D C21_D21HUB = *sys.new_Vector3D("C21_D11HUB",0,L291,L292,"BHUB23");
	//Connection point with Leaf spring
	Vector3D C21_D22HUB = *sys.new_Vector3D("C21_D22HUB",0,L293,L294,"BHUB23");
	//Connection with Tie-rod
	Vector3D C21_D23HUB = *sys.new_Vector3D("C21_D23HUB",L295,L296,L297,"BHUB23");
	

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	//Connection points to chassi
	//A-arm
	Point * B21 = sys.new_Point("B21","A01_Chassi",&A01_B21AARM);
	//Leaf-spring	
	Point * B22 = sys.new_Point("B22","A01_Chassi",&A01_B22LS);
	//Shock-Absorber
	Point * B23 = sys.new_Point("B23","A01_Chassi",&A01_B23SA);
	//Tie-rod
	
	Point * B24 = sys.new_Point("B24","B15",&B15_B24TR);

	//End points
	//A-arm
	Point * E21 = sys.new_Point("E21","B21",&B21_E21AARM);
	//Leaf-spring	
	Point * E22 = sys.new_Point("E22","B22",&B22_E22LS);
	//Shock absorber
	Point * E23 = sys.new_Point("E23","B23",&B23_E23SA);
	Point * E24 = sys.new_Point("E24","B23",&B23_E24SA);
	Point * E25 = sys.new_Point("E25","E23",&E23_E25SA);	
	//Tie-rod
	Point * E26 = sys.new_Point("E26","B24",&B24_E26TR);

	//Additional points
	//Shock absorber connection point with A-arm
	Point * E212 = sys.new_Point("E212","E21",&E21_E212AARM);
	//Bumper point
	Point * E221 = sys.new_Point("E221","E22",&E22_E221LS);

	//Hub
	//Hub center point
	Point * C21 = sys.new_Point("C21","O",&O_C21HUB);
	//Hub connection to A-arm
	Point * D21 = sys.new_Point("D21","C21",&C21_D21HUB);
	//Hub connection to Leaf spring
	Point * D22 = sys.new_Point("D22","C21",&C21_D22HUB);
	//Hub connection to Tie-rod
	Point * D23 = sys.new_Point("D23","C21",&C21_D23HUB);	

// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Viscosity
       	symbol_numeric  Cvis21 = *sys.new_Parameter("Cvis21",0.8);
	// Torsion spring
       	symbol_numeric  K21 = *sys.new_Parameter("K21",1.0);
	
	// Dynamic Parameters of A-arm
    	symbol_numeric  mAarm21 = *sys.new_Parameter("mAarm21",6.0);

	symbol_numeric  mxAarm21 = *sys.new_Parameter("mxAarm21",0.0);	
    	symbol_numeric  myAarm21 = *sys.new_Parameter("myAarm21",0.0);
	symbol_numeric  mzAarm21 = *sys.new_Parameter("mzAarm21",0.);

    	symbol_numeric  IxxAarm21 = *sys.new_Parameter("IxxAarm21",0.1990525);
	symbol_numeric  IxyAarm21 = *sys.new_Parameter("IxyAarm21",0.0);
    	symbol_numeric  IyyAarm21 = *sys.new_Parameter("IyyAarm21",0.023235);
	symbol_numeric  IxzAarm21 = *sys.new_Parameter("IxzAarm21",0.0);
    	symbol_numeric  IzzAarm21 = *sys.new_Parameter("IzzAarm21",0.2158175);
	symbol_numeric  IyzAarm21 = *sys.new_Parameter("IyzAarm21",0.0);

	// Dynamic Parameters of Leaf spring
    	symbol_numeric  mLS21 = *sys.new_Parameter("mLS21",1.0);

	symbol_numeric  mxLS21 = *sys.new_Parameter("mxLS21",0.0);	
    	symbol_numeric  myLS21 = *sys.new_Parameter("myLS21",0.0);
	symbol_numeric  mzLS21 = *sys.new_Parameter("mzLS21",0.0);

    	symbol_numeric  IxxLS21 = *sys.new_Parameter("IxxLS21",1.0);
	symbol_numeric  IxyLS21 = *sys.new_Parameter("IxyLS21",0.0);
    	symbol_numeric  IyyLS21 = *sys.new_Parameter("IyyLS21",1.0);
	symbol_numeric  IxzLS21 = *sys.new_Parameter("IxzLS21",0.0);
    	symbol_numeric  IzzLS21 = *sys.new_Parameter("IzzLS21",1.0);
	symbol_numeric  IyzLS21 = *sys.new_Parameter("IyzLS21",0.0);

	// Dynamic Parameters of Shock absorber part 1
    	symbol_numeric  mSA21 = *sys.new_Parameter("mSA21",1.0);

	symbol_numeric  mxSA21 = *sys.new_Parameter("mxSA21",0.0);	
    	symbol_numeric  mySA21 = *sys.new_Parameter("mySA21",0.0);
	symbol_numeric  mzSA21 = *sys.new_Parameter("mzSA21",0.0);

    	symbol_numeric  IxxSA21 = *sys.new_Parameter("IxxSA21",1.0);
	symbol_numeric  IxySA21 = *sys.new_Parameter("IxySA21",0.0);
    	symbol_numeric  IyySA21 = *sys.new_Parameter("IyySA21",1.0);
	symbol_numeric  IxzSA21 = *sys.new_Parameter("IxzSA21",0.0);
    	symbol_numeric  IzzSA21 = *sys.new_Parameter("IzzSA21",1.0);
	symbol_numeric  IyzSA21 = *sys.new_Parameter("IyzSA21",0.0);

	// Dynamic Parameters of Shock absorber part 2
    	symbol_numeric  mSA22 = *sys.new_Parameter("mSA22",1.0);

	symbol_numeric  mxSA22 = *sys.new_Parameter("mxSA22",0.0);	
    	symbol_numeric  mySA22 = *sys.new_Parameter("mySA22",0.0);
	symbol_numeric  mzSA22 = *sys.new_Parameter("mzSA22",0.0);

    	symbol_numeric  IxxSA22 = *sys.new_Parameter("IxxSA22",1.0);
	symbol_numeric  IxySA22 = *sys.new_Parameter("IxySA22",0.0);
    	symbol_numeric  IyySA22 = *sys.new_Parameter("IyySA22",1.0);
	symbol_numeric  IxzSA22 = *sys.new_Parameter("IxzSA22",0.0);
    	symbol_numeric  IzzSA22 = *sys.new_Parameter("IzzSA22",1.0);
	symbol_numeric  IyzSA22 = *sys.new_Parameter("IyzSA22",0.0);

	// Dynamic Parameters of Tie-rod
    	symbol_numeric  mTR21 = *sys.new_Parameter("mTR21",100.0);

	symbol_numeric  mxTR21 = *sys.new_Parameter("mxTR21",0.0);	
    	symbol_numeric  myTR21 = *sys.new_Parameter("myTR21",0.0);
	symbol_numeric  mzTR21 = *sys.new_Parameter("mzTR21",0.0);

    	symbol_numeric  IxxTR21 = *sys.new_Parameter("IxxTR21",1.0);
	symbol_numeric  IxyTR21 = *sys.new_Parameter("IxyTR21",0.0);
    	symbol_numeric  IyyTR21 = *sys.new_Parameter("IyyTR21",1.0);
	symbol_numeric  IxzTR21 = *sys.new_Parameter("IxzTR21",0.0);
    	symbol_numeric  IzzTR21 = *sys.new_Parameter("IzzTR21",1.0);
	symbol_numeric  IyzTR21 = *sys.new_Parameter("IyzTR21",0.0);

	// Dynamic Parameters of Hub
    	symbol_numeric  mHUB21 = *sys.new_Parameter("mHUB21",19.117);

	symbol_numeric  mxHUB21 = *sys.new_Parameter("mxHUB21",0.0);	
    	symbol_numeric  myHUB21 = *sys.new_Parameter("myHUB21",0.0);
	symbol_numeric  mzHUB21 = *sys.new_Parameter("mzHUB21",0.0);

    	symbol_numeric  IxxHUB21 = *sys.new_Parameter("IxxHUB21",1.0);
	symbol_numeric  IxyHUB21 = *sys.new_Parameter("IxyHUB21",0.0);
    	symbol_numeric  IyyHUB21 = *sys.new_Parameter("IyyHUB21",1.0);
	symbol_numeric  IxzHUB21 = *sys.new_Parameter("IxzHUB21",0.0);
    	symbol_numeric  IzzHUB21 = *sys.new_Parameter("IzzHUB21",1.0);
	symbol_numeric  IyzHUB21 = *sys.new_Parameter("IyzHUB21",0.0);

	// Dynamic Parameters of Wheel
    	symbol_numeric  mWH21 = *sys.new_Parameter("mWH21",38.23);

	symbol_numeric  mxWH21 = *sys.new_Parameter("mxWH21",0.0);	
    	symbol_numeric  myWH21 = *sys.new_Parameter("myWH21",0.0);
	symbol_numeric  mzWH21 = *sys.new_Parameter("mzWH21",0.0);

    	symbol_numeric  IxxWH21 = *sys.new_Parameter("IxxWH21",1.2402);
	symbol_numeric  IxyWH21 = *sys.new_Parameter("IxyWH21",0.0);
    	symbol_numeric  IyyWH21 = *sys.new_Parameter("IyyWH21",1.908);
	symbol_numeric  IxzWH21 = *sys.new_Parameter("IxzWH21",0.0);
    	symbol_numeric  IzzWH21 = *sys.new_Parameter("IzzWH21",1.2402);
	symbol_numeric  IyzWH21 = *sys.new_Parameter("IyzWH21",0.0);

	//Gravity Center Vectors    

	Vector3D B21Arm21_GArm21= *sys.new_Vector3D("B21Arm21_GArm21",mxAarm21/mAarm21,myAarm21/mAarm21,mzAarm21/mAarm21,"BARM21");
	Vector3D B22LS21_GLS21= *sys.new_Vector3D("B22LS21_GLS21",mxLS21/mLS21,myLS21/mLS21,mzLS21/mLS21,"BLS21");
	Vector3D B23SA21_GSA21= *sys.new_Vector3D("B23SA21_GSA21",mxSA21/mSA21,mySA21/mSA21,mzSA21/mSA21,"BSA22");
	Vector3D E23SA22_GSA22= *sys.new_Vector3D("E23SA22_GSA22",mxSA22/mSA22,mySA22/mSA22,mzSA22/mSA22,"BSA22");
	Vector3D B24TR21_GTR21= *sys.new_Vector3D("B24TR21_GTR21",mxTR21/mTR21,myTR21/mTR21,mzTR21/mTR21,"BTR22");
	Vector3D C21HUB21_GHUB21= *sys.new_Vector3D("C21HUB21_GHUB21",mxHUB21/mHUB21,myHUB21/mHUB21,mzHUB21/mHUB21,"BHUB23");
	Vector3D C21WH21_GWH21= *sys.new_Vector3D("C21WH21_GWH21",mxWH21/mWH21,myWH21/mWH21,mzWH21/mWH21,"BHUB24");


	//Inertia Tensors

    	Tensor3D IAarm21 = *sys.new_Tensor3D("IAarm21",(ex)IxxAarm21,(ex)IxyAarm21,(ex)IxzAarm21,(ex)IxyAarm21,(ex)IyyAarm21,(ex)IyzAarm21,(ex)IxzAarm21,(ex)IyzAarm21,(ex)IzzAarm21,"BARM21");
    	Tensor3D ILS21 = *sys.new_Tensor3D("ILS21",(ex)IxxLS21,(ex)IxyLS21,(ex)IxzLS21,(ex)IxyLS21,(ex)IyyLS21,(ex)IyzLS21,(ex)IxzLS21,(ex)IyzLS21,(ex)IzzLS21,"BLS21");
    	Tensor3D ISA21 = *sys.new_Tensor3D("ISA21",(ex)IxxSA21,(ex)IxySA21,(ex)IxzSA21,(ex)IxySA21,(ex)IyySA21,(ex)IyzSA21,(ex)IxzSA21,(ex)IyzSA21,(ex)IzzSA21,"BSA22");
    	Tensor3D ISA22 = *sys.new_Tensor3D("ISA22",(ex)IxxSA22,(ex)IxySA22,(ex)IxzSA22,(ex)IxySA22,(ex)IyySA22,(ex)IyzSA22,(ex)IxzSA22,(ex)IyzSA22,(ex)IzzSA22,"BSA22");
    	Tensor3D ITR21 = *sys.new_Tensor3D("ITR21",(ex)IxxTR21,(ex)IxyTR21,(ex)IxzTR21,(ex)IxyTR21,(ex)IyyTR21,(ex)IyzTR21,(ex)IxzTR21,(ex)IyzTR21,(ex)IzzTR21,"BTR22");
    	Tensor3D IHUB21 = *sys.new_Tensor3D("IHUB21",(ex)IxxHUB21,(ex)IxyHUB21,(ex)IxzHUB21,(ex)IxyHUB21,(ex)IyyHUB21,(ex)IyzHUB21,(ex)IxzHUB21,(ex)IyzHUB21,(ex)IzzHUB21,"BHUB23");
    	Tensor3D IWH21 = *sys.new_Tensor3D("IWH21",(ex)IxxWH21,(ex)IxyWH21,(ex)IxzWH21,(ex)IxyWH21,(ex)IyyWH21,(ex)IyzWH21,(ex)IxzWH21,(ex)IyzWH21,(ex)IzzWH21,"BHUB24");

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Aarm21 = sys.new_Frame("Fra_Aarm21","B21","BARM21");
	Frame * Fra_LS21 = sys.new_Frame("Fra_LS21","B22","BLS21");

	Frame * Fra_SA22 = sys.new_Frame("Fra_SA22","B23","BSA22");

	Frame * Fra_TR22 = sys.new_Frame("Fra_TR22","B24","BTR22");
	Frame * Fra_HUB23 = sys.new_Frame("Fra_HUB23","C21","BHUB23");
	Frame * Fra_WH21 = sys.new_Frame("Fra_WH21","C21","BHUB24");


// ************************************************************************************************
//	Define Solids
// ************************************************************************************************
	
	
	Solid * Aarm21 = sys.new_Solid("Aarm21","B21","BARM21","mAarm21","B21Arm21_GArm21","IAarm21");
	Solid * LS21 = sys.new_Solid("LS21","B22","BLS21","mLS21","B22LS21_GLS21","ILS21");
	Solid * SA21 = sys.new_Solid("SA21","B23","BSA22","mSA21","B23SA21_GSA21","ISA21");
	Solid * SA22 = sys.new_Solid("SA22","E23","BSA22","mSA22","E23SA22_GSA22","ISA22");	
	Solid * TR21 = sys.new_Solid("TR21","B24","BTR22","mTR21","B24TR21_GTR21","ITR21");
	Solid * HUB21 = sys.new_Solid("HUB21","C21","BHUB23","mHUB21","C21HUB21_GHUB21","IHUB21");
	Solid * WH21 = sys.new_Solid("WH21","C21","BHUB24","mWH21","C21WH21_GWH21","IWH21");

// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************
      
	Drawing3D * Aarm213D = sys.new_Drawing3D("Aarm213D", "Aarm21","./solids/aarm21.stl",1,0,0,1);
        Drawing3D * LS213D = sys.new_Drawing3D("LS213D", "LS21","./solids/LS21.stl",1,0,0,1);
        Drawing3D * TR213D = sys.new_Drawing3D("TR213D", "TR21","./solids/TR21.stl",1,0,0,1);
        Drawing3D * SA213D = sys.new_Drawing3D("SA213D", "SA21","./solids/SA21.stl",1,0,0,0.5);
        Drawing3D * SA223D = sys.new_Drawing3D("SA223D", "SA22","./solids/SA22.stl",1,0,0,1);
        Drawing3D * HUB213D = sys.new_Drawing3D("HUB213D", "HUB21","./solids/hub21.stl",1,0,0,1);
	//Drawing3D * WH213D = sys.new_Drawing3D("WH213D", "WH21","./solids/wh11.stl",1,0,0,1);


// ************************************************************************************************
//	Rear Left Part
// ************************************************************************************************

// ************************************************************************************************
//	Coordinate definition
// ************************************************************************************************
	
	//A-arm angle
	symbol_numeric betha31 = *sys.new_Coordinate("betha31","dbetha31","ddbetha31",0, 0.0 , 0.0);
	// Leaf-spring angle
	symbol_numeric betha32 = *sys.new_Coordinate("betha32","dbetha32","ddbetha32",0, 0.0 , 0.0);
	
	//Shock Absorber angle 1
	symbol_numeric betha35 = *sys.new_Coordinate("betha35","dbetha35","ddbetha35",0, 0.0 , 0.0);	
	//Shock Absorber angle 2
	symbol_numeric betha36 = *sys.new_Coordinate("betha36","dbetha36","ddbetha36",0, 0.0 , 0.0);
	//Shock Absorber movement
	symbol_numeric L311 = *sys.new_Coordinate("L311","dL311","ddL311",0, 0.0 , 0.0);
	//Tie-rod chassi movement

	//Tie-rod angle 1
	symbol_numeric betha33 = *sys.new_Coordinate("betha33","dbetha33","ddbetha33",0, 0.0 , 0.0);
	//Tie-rod angle 2
	symbol_numeric betha34 = *sys.new_Coordinate("betha34","dbetha34","ddbetha34",0, 0.0 , 0.0);
	//Hub translation x
	symbol_numeric L31 = *sys.new_Coordinate("L31","dL31","ddL31",-1.047, 0.0 , 0.0);
	//Hub translation y
	symbol_numeric L32 = *sys.new_Coordinate("L32","dL32","ddL32",0.615, 0.0 , 0.0);
	//Hub translation z
	symbol_numeric L33 = *sys.new_Coordinate("L33","dL33","ddL33",0.356, 0.0 , 0.0);
	//Hub angle 1
	symbol_numeric alpha31 = *sys.new_Coordinate("alpha31","dalpha31","ddalpha31",0, 0.0 , 0.0);
	//Hub angle 2
	symbol_numeric alpha32 = *sys.new_Coordinate("alpha32","dalpha32","ddalpha32",0, 0.0 , 0.0);
	//Hub angle 3
	symbol_numeric alpha33 = *sys.new_Coordinate("alpha33","dalpha33","ddalpha33",0, 0.0 , 0.0);
	//Wheel rotation
	symbol_numeric alpha34 = *sys.new_Coordinate("alpha34","dalpha34","ddalpha34",0, 0.0 , 0.0);


	//Velocity
	symbol_numeric *dbetha31=sys.get_Velocity("dbetha31");
	symbol_numeric *dbetha32=sys.get_Velocity("dbetha32");

	symbol_numeric *dbetha35=sys.get_Velocity("dbetha35");
	symbol_numeric *dbetha36=sys.get_Velocity("dbetha36");
	symbol_numeric *dL311=sys.get_Velocity("dL311");

	symbol_numeric *dbetha33=sys.get_Velocity("dbetha33");
	symbol_numeric *dbetha34=sys.get_Velocity("dbetha34");
	symbol_numeric *dL31=sys.get_Velocity("dL31");
	symbol_numeric *dL32=sys.get_Velocity("dL32");
	symbol_numeric *dL33=sys.get_Velocity("dL33");
	symbol_numeric *dalpha31=sys.get_Velocity("dalpha31");
	symbol_numeric *dalpha32=sys.get_Velocity("dalpha32");
	symbol_numeric *dalpha33=sys.get_Velocity("dalpha33");
	symbol_numeric *dalpha34=sys.get_Velocity("dalpha34");
	
	//Acceleration
	symbol_numeric *ddbetha31=sys.get_Acceleration("ddbetha31");
	symbol_numeric *ddbetha32=sys.get_Acceleration("ddbetha32");

	symbol_numeric *ddbetha35=sys.get_Acceleration("ddbetha35");
	symbol_numeric *ddbetha36=sys.get_Acceleration("ddbetha36");
	symbol_numeric *ddL311=sys.get_Acceleration("ddL311");
	
	symbol_numeric *ddbetha33=sys.get_Acceleration("ddbetha33");
	symbol_numeric *ddbetha34=sys.get_Acceleration("ddbetha34");
	symbol_numeric *ddL31=sys.get_Acceleration("ddL31");
	symbol_numeric *ddL32=sys.get_Acceleration("ddL32");
	symbol_numeric *ddL33=sys.get_Acceleration("ddL33");
	symbol_numeric *ddalpha31=sys.get_Acceleration("ddalpha31");
	symbol_numeric *ddalpha32=sys.get_Acceleration("ddalpha32");
	symbol_numeric *ddalpha33=sys.get_Acceleration("ddalpha33");
	symbol_numeric *ddalpha34=sys.get_Acceleration("ddalpha34");

// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************
	//A-arm
	//A-arm lenght
	symbol_numeric L34 = *sys.new_Parameter("L34",0.32140006);
	//A-arm connection to chassi x
	symbol_numeric L341 = *sys.new_Parameter("L341",-1.047);
	//A-arm connection to chassi y
	symbol_numeric L342 = *sys.new_Parameter("L342",0.259);
	//A-arm connection to chassi z
	symbol_numeric L343 = *sys.new_Parameter("L343",0.302);
	//A-arm and shock absorber connextion x
	symbol_numeric L344 = *sys.new_Parameter("L344",-0.075);
	//A-arm and shock absorber connextion y
	symbol_numeric L345 = *sys.new_Parameter("L345",-0.241);
	//A-arm and shock absorber connextion Z
	symbol_numeric L346 = *sys.new_Parameter("L346",-0.061);
	
	//Leaf-spring
	//Leaf sprign lenght
	symbol_numeric L36 = *sys.new_Parameter("L36",0.33664707);
	//Leaf spring connection to chassi x
	symbol_numeric L361 = *sys.new_Parameter("L361",-1.047);
	//Leaf spring connection to chassi y
	symbol_numeric L362 = *sys.new_Parameter("L362",0.1585);
	//Leaf spring connection to chassi z
	symbol_numeric L363 = *sys.new_Parameter("L363",0.600);

	//Shock absorber
	//Shock absorber lenght of part 1
	symbol_numeric L35 = *sys.new_Parameter("L35",0.220278233);
	//Shock absorber lenght of part 2
	symbol_numeric L351 = *sys.new_Parameter("L351",0.2937043107);	
	//Shock absorber connection to the chassi x
	symbol_numeric L352 = *sys.new_Parameter("L352",-1.122);	
	//Shock absorber connection to the chassi y
	symbol_numeric L353 = *sys.new_Parameter("L353",0.297);
	//Shock absorber connection to the chassi z
	symbol_numeric L354 = *sys.new_Parameter("L354",0.632);	

	//Tie-rod
	//Tie rod lenght
	symbol_numeric L37 = *sys.new_Parameter("L37",0.384246015);
	//Tie-rod movement point x
	symbol_numeric L371 = *sys.new_Parameter("L371",-0.907);
	//Tie-rod movement point z
	symbol_numeric L373 = *sys.new_Parameter("L373",0.600);
	//Tie-rod connection to chassi y
	symbol_numeric L372 = *sys.new_Parameter("L372",0.07);

	//Hub
	//Hub center x
	symbol_numeric L3911 = *sys.new_Parameter("L3911",1.047);	
	//Hub center y
	symbol_numeric L3912 = *sys.new_Parameter("L3912",0.615);
	//Hub center z
	symbol_numeric L3913 = *sys.new_Parameter("L3913",0.356);
	
	//Connection point of hub and A-arm y
	symbol_numeric L391 = *sys.new_Parameter("L391",-0.043);
	//Connection point of hub and A-arm z
	symbol_numeric L392 = *sys.new_Parameter("L392",-0.127);
	
	//Connection point of hub and Leaf-spring y
	symbol_numeric L393 = *sys.new_Parameter("L393",-0.127);
	//Connection point of hub and Leaf-spring z
	symbol_numeric L394 = *sys.new_Parameter("L394",0.175);

	//Connection point of hub and Tie-rod x
	symbol_numeric L395 = *sys.new_Parameter("L395",0.14);
	//Connection point of hub and Tie-rod y
	symbol_numeric L396 = *sys.new_Parameter("L396",-0.167);
	//Connection point of hub and Tie-rod z
	symbol_numeric L397 = *sys.new_Parameter("L397",0.175);


// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************


	//A-arm
 	sys.new_Base("BARM31","BCHASSI03",1,0,0,-betha31);
	//Leaf-spring
 	sys.new_Base("BLS31","BCHASSI03",1,0,0,-betha32);
	//Schock-Absorber
 	sys.new_Base("BSA31","BCHASSI03",1,0,0,-betha35);
	sys.new_Base("BSA32","BSA31",0,0,1,-betha36);
	//Tie-rod
 	sys.new_Base("BTR31","BCHASSI03",1,0,0,betha33);
	sys.new_Base("BTR32","BTR31",0,0,1,betha34);
	//Hub
 	sys.new_Base("BHUB31","xyz",1,0,0,alpha31);
 	sys.new_Base("BHUB32","BHUB31",0,1,0,alpha32);
	sys.new_Base("BHUB33","BHUB32",0,0,1,alpha33);
	//Wheel
	sys.new_Base("BHUB34","BHUB33",0,1,0,alpha34);

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	//Connection points to chassi
	//A-rm	
	Vector3D A01_B31AARM = *sys.new_Vector3D("A01_B31AARM",L341,L342,L343,"BCHASSI03");
	//Leaf spring
	Vector3D A01_B32LS = *sys.new_Vector3D("A01_B32LS",L361,L362,L363,"BCHASSI03");
	//Shock absorber
	Vector3D A01_B33SA = *sys.new_Vector3D("A01_B33SA",L352,L353,L354,"BCHASSI03");
	//Tie-rod
	Vector3D A01_B35TR = *sys.new_Vector3D("A01_B35TR",L371,0,L373,"BCHASSI03");
	Vector3D B35_B34TR = *sys.new_Vector3D("B35_B34TR",0,L372,0,"BCHASSI03");

	//End points of parts
	//A-arm
	Vector3D B31_E31AARM = *sys.new_Vector3D("B31_E31AARM",0,L34,0,"BARM31");
	//Leaf-spring
	Vector3D B32_E32LS = *sys.new_Vector3D("B32_E32LS",0,L36,0,"BLS31");
	//Schock absorber
	Vector3D B33_E34SA = *sys.new_Vector3D("B33_E34SA",0,L35,0,"BSA32");
	Vector3D B33_E33SA = *sys.new_Vector3D("B33_E33SA",0,L311,0,"BSA32");
	Vector3D E33_E35SA = *sys.new_Vector3D("E33_E35SA",0,L351,0,"BSA32");
	//Tie-rod
	Vector3D B34_E36TR = *sys.new_Vector3D("B34_E36TR",0,L37,0,"BTR32");
	

	//Additional points
	//Schock absorber connection point with A-arm
	Vector3D E31_E312AARM = *sys.new_Vector3D("E31_E312AARM",L344,L345,L346,"BARM31");
	//Distance from leaf spring and damper
	Vector3D E32_E321LS = *sys.new_Vector3D("E32_E321LS",0,0,0.145-(L36*sin(betha32)),"BCHASSI03");	

	//Hub
	//Center point of hub
	Vector3D O_C31HUB = *sys.new_Vector3D("O_C31HUB",L31,L32,L33,"BHUB33");
	//Connection point with A-arm
	Vector3D C31_D31HUB = *sys.new_Vector3D("C31_D31HUB",0,L391,L392,"BHUB33");
	//Connection point with Leaf spring
	Vector3D C31_D32HUB = *sys.new_Vector3D("C31_D32HUB",0,L393,L394,"BHUB33");
	//Connection with Tie-rod
	Vector3D C31_D33HUB = *sys.new_Vector3D("C31_D33HUB",L395,L396,L397,"BHUB33");
	

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	//Connection points to chassi
	//A-arm
	Point * B31 = sys.new_Point("B31","A01_Chassi",&A01_B31AARM);
	//Leaf-spring	
	Point * B32 = sys.new_Point("B32","A01_Chassi",&A01_B32LS);
	//Shock-Absorber
	Point * B33 = sys.new_Point("B33","A01_Chassi",&A01_B33SA);
	//Tie-rod
	Point * B35 = sys.new_Point("B35","A01_Chassi",&A01_B35TR);
	Point * B34 = sys.new_Point("B34","B35",&B35_B34TR);

	//End points
	//A-arm
	Point * E31 = sys.new_Point("E31","B31",&B31_E31AARM);
	//Leaf-spring	
	Point * E32 = sys.new_Point("E32","B32",&B32_E32LS);
	//Shock absorber
	Point * E33 = sys.new_Point("E33","B33",&B33_E33SA);
	Point * E34 = sys.new_Point("E34","B33",&B33_E34SA);
	Point * E35 = sys.new_Point("E35","E33",&E33_E35SA);	
	//Tie-rod
	Point * E36 = sys.new_Point("E36","B34",&B34_E36TR);

	//Additional points
	//Shock absorber connection point with A-arm
	Point * E312 = sys.new_Point("E312","E31",&E31_E312AARM);
	//Bumper point
	Point * E321 = sys.new_Point("E321","E32",&E32_E321LS);

	//Hub
	//Hub center point
	Point * C31 = sys.new_Point("C31","O",&O_C31HUB);
	//Hub connection to A-arm
	Point * D31 = sys.new_Point("D31","C31",&C31_D31HUB);
	//Hub connection to Leaf spring
	Point * D32 = sys.new_Point("D32","C31",&C31_D32HUB);
	//Hub connection to Tie-rod
	Point * D33 = sys.new_Point("D33","C31",&C31_D33HUB);	


// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Viscosity
       	symbol_numeric  Cvis31 = *sys.new_Parameter("Cvis31",0.8);
	// Torsion spring
       	symbol_numeric  K31 = *sys.new_Parameter("K31",1.0);
	
	// Dynamic Parameters of A-arm
    	symbol_numeric  mAarm31 = *sys.new_Parameter("mAarm31",6.0);

	symbol_numeric  mxAarm31 = *sys.new_Parameter("mxAarm31",0.0);	
    	symbol_numeric  myAarm31 = *sys.new_Parameter("myAarm31",0.0);
	symbol_numeric  mzAarm31 = *sys.new_Parameter("mzAarm31",0.0);

    	symbol_numeric  IxxAarm31 = *sys.new_Parameter("IxxAarm31",0.199055);
	symbol_numeric  IxyAarm31 = *sys.new_Parameter("IxyAarm31",0.0);
    	symbol_numeric  IyyAarm31 = *sys.new_Parameter("IyyAarm31",0.023235);
	symbol_numeric  IxzAarm31 = *sys.new_Parameter("IxzAarm31",0.0);
    	symbol_numeric  IzzAarm31 = *sys.new_Parameter("IzzAarm31",0.2158175);
	symbol_numeric  IyzAarm31 = *sys.new_Parameter("IyzAarm31",0.0);

	// Dynamic Parameters of Leaf spring
    	symbol_numeric  mLS31 = *sys.new_Parameter("mLS31",1.0);

	symbol_numeric  mxLS31 = *sys.new_Parameter("mxLS31",0.0);	
    	symbol_numeric  myLS31 = *sys.new_Parameter("myLS31",0.0);
	symbol_numeric  mzLS31 = *sys.new_Parameter("mzLS31",0.0);

    	symbol_numeric  IxxLS31 = *sys.new_Parameter("IxxLS31",1.0);
	symbol_numeric  IxyLS31 = *sys.new_Parameter("IxyLS31",0.0);
    	symbol_numeric  IyyLS31 = *sys.new_Parameter("IyyLS31",1.0);
	symbol_numeric  IxzLS31 = *sys.new_Parameter("IxzLS31",0.0);
    	symbol_numeric  IzzLS31 = *sys.new_Parameter("IzzLS31",1.0);
	symbol_numeric  IyzLS31 = *sys.new_Parameter("IyzLS31",0.0);

	// Dynamic Parameters of Shock absorber part 1
    	symbol_numeric  mSA31 = *sys.new_Parameter("mSA31",1.0);

	symbol_numeric  mxSA31 = *sys.new_Parameter("mxSA31",0.0);	
    	symbol_numeric  mySA31 = *sys.new_Parameter("mySA31",0.0);
	symbol_numeric  mzSA31 = *sys.new_Parameter("mzSA31",0.0);

    	symbol_numeric  IxxSA31 = *sys.new_Parameter("IxxSA31",1.0);
	symbol_numeric  IxySA31 = *sys.new_Parameter("IxySA31",0.0);
    	symbol_numeric  IyySA31 = *sys.new_Parameter("IyySA31",1.0);
	symbol_numeric  IxzSA31 = *sys.new_Parameter("IxzSA31",0.0);
    	symbol_numeric  IzzSA31 = *sys.new_Parameter("IzzSA31",1.0);
	symbol_numeric  IyzSA31 = *sys.new_Parameter("IyzSA31",0.0);

	// Dynamic Parameters of Shock absorber part 2
    	symbol_numeric  mSA32 = *sys.new_Parameter("mSA32",1.0);

	symbol_numeric  mxSA32 = *sys.new_Parameter("mxSA32",0.0);	
    	symbol_numeric  mySA32 = *sys.new_Parameter("mySA32",0.0);
	symbol_numeric  mzSA32 = *sys.new_Parameter("mzSA32",0.0);

    	symbol_numeric  IxxSA32 = *sys.new_Parameter("IxxSA32",1.0);
	symbol_numeric  IxySA32 = *sys.new_Parameter("IxySA32",0.0);
    	symbol_numeric  IyySA32 = *sys.new_Parameter("IyySA32",1.0);
	symbol_numeric  IxzSA32 = *sys.new_Parameter("IxzSA32",0.0);
    	symbol_numeric  IzzSA32 = *sys.new_Parameter("IzzSA32",1.0);
	symbol_numeric  IyzSA32 = *sys.new_Parameter("IyzSA32",0.0);

	// Dynamic Parameters of Tie-rod
    	symbol_numeric  mTR31 = *sys.new_Parameter("mTR31",1.0);

	symbol_numeric  mxTR31 = *sys.new_Parameter("mxTR31",0.0);	
    	symbol_numeric  myTR31 = *sys.new_Parameter("myTR31",0.0);
	symbol_numeric  mzTR31 = *sys.new_Parameter("mzTR31",0.0);

    	symbol_numeric  IxxTR31 = *sys.new_Parameter("IxxTR31",1.0);
	symbol_numeric  IxyTR31 = *sys.new_Parameter("IxyTR31",0.0);
    	symbol_numeric  IyyTR31 = *sys.new_Parameter("IyyTR31",1.0);
	symbol_numeric  IxzTR31 = *sys.new_Parameter("IxzTR31",0.0);
    	symbol_numeric  IzzTR31 = *sys.new_Parameter("IzzTR31",1.0);
	symbol_numeric  IyzTR31 = *sys.new_Parameter("IyzTR31",0.0);

	// Dynamic Parameters of Hub
    	symbol_numeric  mHUB31 = *sys.new_Parameter("mHUB31",19.117);

	symbol_numeric  mxHUB31 = *sys.new_Parameter("mxHUB31",0.0);	
    	symbol_numeric  myHUB31 = *sys.new_Parameter("myHUB31",0.0);
	symbol_numeric  mzHUB31 = *sys.new_Parameter("mzHUB31",0.0);

    	symbol_numeric  IxxHUB31 = *sys.new_Parameter("IxxHUB31",1.0);
	symbol_numeric  IxyHUB31 = *sys.new_Parameter("IxyHUB31",0.0);
    	symbol_numeric  IyyHUB31 = *sys.new_Parameter("IyyHUB31",1.0);
	symbol_numeric  IxzHUB31 = *sys.new_Parameter("IxzHUB31",0.0);
    	symbol_numeric  IzzHUB31 = *sys.new_Parameter("IzzHUB31",1.0);
	symbol_numeric  IyzHUB31 = *sys.new_Parameter("IyzHUB31",0.0);

	// Dynamic Parameters of Wheel
    	symbol_numeric  mWH31 = *sys.new_Parameter("mWH31",38.23);

	symbol_numeric  mxWH31 = *sys.new_Parameter("mxWH31",0.0);	
    	symbol_numeric  myWH31 = *sys.new_Parameter("myWH31",0.0);
	symbol_numeric  mzWH31 = *sys.new_Parameter("mzWH31",0.0);

    	symbol_numeric  IxxWH31 = *sys.new_Parameter("IxxWH31",1.2402);
	symbol_numeric  IxyWH31 = *sys.new_Parameter("IxyWH31",0.0);
    	symbol_numeric  IyyWH31 = *sys.new_Parameter("IyyWH31",1.908);
	symbol_numeric  IxzWH31 = *sys.new_Parameter("IxzWH31",0.0);
    	symbol_numeric  IzzWH31 = *sys.new_Parameter("IzzWH31",1.2402);
	symbol_numeric  IyzWH31 = *sys.new_Parameter("IyzWH31",0.0);

	//Gravity Center Vectors    

	Vector3D B31Arm31_GArm31= *sys.new_Vector3D("B31Arm31_GArm31",mxAarm31/mAarm31,myAarm31/mAarm31,mzAarm31/mAarm31,"BARM31");
	Vector3D B32LS31_GLS31= *sys.new_Vector3D("B32LS31_GLS31",mxLS31/mLS31,myLS31/mLS31,mzLS31/mLS31,"BLS31");
	Vector3D B33SA31_GSA31= *sys.new_Vector3D("B33SA31_GSA31",mxSA31/mSA31,mySA31/mSA31,mzSA31/mSA31,"BSA32");
	Vector3D E33SA32_GSA32= *sys.new_Vector3D("E33SA32_GSA32",mxSA32/mSA32,mySA32/mSA32,mzSA32/mSA32,"BSA32");
	Vector3D B34TR31_GTR31= *sys.new_Vector3D("B34TR31_GTR31",mxTR31/mTR31,myTR31/mTR31,mzTR31/mTR31,"BTR32");
	Vector3D C31HUB31_GHUB31= *sys.new_Vector3D("C31HUB31_GHUB31",mxHUB31/mHUB31,myHUB31/mHUB31,mzHUB31/mHUB31,"BHUB33");
	Vector3D C31WH31_GWH31= *sys.new_Vector3D("C31WH31_GWH31",mxWH31/mWH31,myWH31/mWH31,mzWH31/mWH31,"BHUB34");


	//Inertia Tensors

    	Tensor3D IAarm31 = *sys.new_Tensor3D("IAarm31",(ex)IxxAarm31,(ex)IxyAarm31,(ex)IxzAarm31,(ex)IxyAarm31,(ex)IyyAarm31,(ex)IyzAarm31,(ex)IxzAarm31,(ex)IyzAarm31,(ex)IzzAarm31,"BARM31");
    	Tensor3D ILS31 = *sys.new_Tensor3D("ILS31",(ex)IxxLS31,(ex)IxyLS31,(ex)IxzLS31,(ex)IxyLS31,(ex)IyyLS31,(ex)IyzLS31,(ex)IxzLS31,(ex)IyzLS31,(ex)IzzLS31,"BLS31");
    	Tensor3D ISA31 = *sys.new_Tensor3D("ISA31",(ex)IxxSA31,(ex)IxySA31,(ex)IxzSA31,(ex)IxySA31,(ex)IyySA31,(ex)IyzSA31,(ex)IxzSA31,(ex)IyzSA31,(ex)IzzSA31,"BSA32");
    	Tensor3D ISA32 = *sys.new_Tensor3D("ISA32",(ex)IxxSA32,(ex)IxySA32,(ex)IxzSA32,(ex)IxySA32,(ex)IyySA32,(ex)IyzSA32,(ex)IxzSA32,(ex)IyzSA32,(ex)IzzSA32,"BSA32");
    	Tensor3D ITR31 = *sys.new_Tensor3D("ITR31",(ex)IxxTR31,(ex)IxyTR31,(ex)IxzTR31,(ex)IxyTR31,(ex)IyyTR31,(ex)IyzTR31,(ex)IxzTR31,(ex)IyzTR31,(ex)IzzTR31,"BTR32");
    	Tensor3D IHUB31 = *sys.new_Tensor3D("IHUB31",(ex)IxxHUB31,(ex)IxyHUB31,(ex)IxzHUB31,(ex)IxyHUB31,(ex)IyyHUB31,(ex)IyzHUB31,(ex)IxzHUB31,(ex)IyzHUB31,(ex)IzzHUB31,"BHUB33");
    	Tensor3D IWH31 = *sys.new_Tensor3D("IWH31",(ex)IxxWH31,(ex)IxyWH31,(ex)IxzWH31,(ex)IxyWH31,(ex)IyyWH31,(ex)IyzWH31,(ex)IxzWH31,(ex)IyzWH31,(ex)IzzWH31,"BHUB34");

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Aarm31 = sys.new_Frame("Fra_Aarm31","B31","BARM31");
	Frame * Fra_LS31 = sys.new_Frame("Fra_LS31","B32","BLS31");

	Frame * Fra_SA32 = sys.new_Frame("Fra_SA32","B33","BSA32");

	Frame * Fra_TR32 = sys.new_Frame("Fra_TR32","B34","BTR32");

	Frame * Fra_HUB33 = sys.new_Frame("Fra_HUB33","C31","BHUB33");
	Frame * Fra_WH31 = sys.new_Frame("Fra_WH31","C31","BHUB34");


// ************************************************************************************************
//	Define Solids
// ************************************************************************************************
	
	
	Solid * Aarm31 = sys.new_Solid("Aarm31","B31","BARM31","mAarm31","B31Arm31_GArm31","IAarm31");
	Solid * LS31 = sys.new_Solid("LS31","B32","BLS31","mLS31","B32LS31_GLS31","ILS31");
	Solid * SA31 = sys.new_Solid("SA31","B33","BSA32","mSA31","B33SA31_GSA31","ISA31");
	Solid * SA32 = sys.new_Solid("SA32","E33","BSA32","mSA32","E33SA32_GSA32","ISA32");	
	Solid * TR31 = sys.new_Solid("TR31","B34","BTR32","mTR31","B34TR31_GTR31","ITR31");
	Solid * HUB31 = sys.new_Solid("HUB31","C31","BHUB33","mHUB31","C31HUB31_GHUB31","IHUB31");
	Solid * WH31 = sys.new_Solid("WH31","C31","BHUB34","mWH31","C31WH31_GWH31","IWH31");
      



// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************
        Drawing3D * Aarm313D = sys.new_Drawing3D("Aarm313D", "Aarm31","./solids/aarm31.stl",1,0,0,1);
        Drawing3D * LS313D = sys.new_Drawing3D("LS313D", "LS31","./solids/LS31.stl",1,0,0,1);
        Drawing3D * TR313D = sys.new_Drawing3D("TR313D", "TR31","./solids/TR31.stl",1,0,0,1);
        Drawing3D * SA313D = sys.new_Drawing3D("SA313D", "SA31","./solids/SA31.stl",1,0,0,0.5);
        Drawing3D * SA323D = sys.new_Drawing3D("SA323D", "SA32","./solids/SA32.stl",1,0,0,1);
	Drawing3D * HUB313D = sys.new_Drawing3D("HUB313D", "HUB31","./solids/hub31.stl",1,0,0,1);
	//Drawing3D * WH313D = sys.new_Drawing3D("WH313D", "WH31","./solids/wh41.stl",1,0,0,1);


// ************************************************************************************************
//	Rear Right Part
// ************************************************************************************************

// ************************************************************************************************
//	Coordinate definition
// ************************************************************************************************
	
	//A-arm angle
	symbol_numeric betha41 = *sys.new_Coordinate("betha41","dbetha41","ddbetha41",0, 0.0 , 0.0);
	// Leaf-spring angle
	symbol_numeric betha42 = *sys.new_Coordinate("betha42","dbetha42","ddbetha42",0, 0.0 , 0.0);
	
	//Shock Absorber angle 1
	symbol_numeric betha45 = *sys.new_Coordinate("betha45","dbetha45","ddbetha45",0, 0.0 , 0.0);	
	//Shock Absorber angle 2
	symbol_numeric betha46 = *sys.new_Coordinate("betha46","dbetha46","ddbetha46",0, 0.0 , 0.0);
	//Shock Absorber movement
	symbol_numeric L411 = *sys.new_Coordinate("L411","dL411","ddL411",0, 0.0 , 0.0);
	
	//Tie-rod angle 1
	symbol_numeric betha43 = *sys.new_Coordinate("betha43","dbetha43","ddbetha43",0, 0.0 , 0.0);
	//Tie-rod angle 2
	symbol_numeric betha44 = *sys.new_Coordinate("betha44","dbetha44","ddbetha44",0, 0.0 , 0.0);
	//Hub translation x
	symbol_numeric L41 = *sys.new_Coordinate("L41","dL41","ddL41",-1.047, 0.0 , 0.0);
	//Hub translation y
	symbol_numeric L42 = *sys.new_Coordinate("L42","dL42","ddL42",-0.615, 0.0 , 0.0);
	//Hub translation z
	symbol_numeric L43 = *sys.new_Coordinate("L43","dL43","ddL43",0.356, 0.0 , 0.0);
	//Hub angle 1
	symbol_numeric alpha41 = *sys.new_Coordinate("alpha41","dalpha41","ddalpha41",0, 0.0 , 0.0);
	//Hub angle 2
	symbol_numeric alpha42 = *sys.new_Coordinate("alpha42","dalpha42","ddalpha42",0, 0.0 , 0.0);
	//Hub angle 3
	symbol_numeric alpha43 = *sys.new_Coordinate("alpha43","dalpha43","ddalpha43",0, 0.0 , 0.0);
	//Wheel rotation
	symbol_numeric alpha44 = *sys.new_Coordinate("alpha44","dalpha44","ddalpha44",0, 0.0 , 0.0);


	//Velocity
	symbol_numeric *dbetha41=sys.get_Velocity("dbetha41");
	symbol_numeric *dbetha42=sys.get_Velocity("dbetha42");
	
	symbol_numeric *dbetha45=sys.get_Velocity("dbetha45");
	symbol_numeric *dbetha46=sys.get_Velocity("dbetha46");
	symbol_numeric *dL411=sys.get_Velocity("dL411");
	
	symbol_numeric *dbetha43=sys.get_Velocity("dbetha43");
	symbol_numeric *dbetha44=sys.get_Velocity("dbetha44");
	symbol_numeric *dL41=sys.get_Velocity("dL41");
	symbol_numeric *dL42=sys.get_Velocity("dL42");
	symbol_numeric *dL43=sys.get_Velocity("dL43");
	symbol_numeric *dalpha41=sys.get_Velocity("dalpha41");
	symbol_numeric *dalpha42=sys.get_Velocity("dalpha42");
	symbol_numeric *dalpha43=sys.get_Velocity("dalpha43");
	symbol_numeric *dalpha44=sys.get_Velocity("dalpha44");
	
	//Acceleration
	symbol_numeric *ddbetha41=sys.get_Acceleration("ddbetha41");
	symbol_numeric *ddbetha42=sys.get_Acceleration("ddbetha42");

	symbol_numeric *ddbetha45=sys.get_Acceleration("ddbetha45");
	symbol_numeric *ddbetha46=sys.get_Acceleration("ddbetha46");
	symbol_numeric *ddL411=sys.get_Acceleration("ddL411");

	symbol_numeric *ddbetha43=sys.get_Acceleration("ddbetha43");
	symbol_numeric *ddbetha44=sys.get_Acceleration("ddbetha44");
	symbol_numeric *ddL41=sys.get_Acceleration("ddL41");
	symbol_numeric *ddL42=sys.get_Acceleration("ddL42");
	symbol_numeric *ddL43=sys.get_Acceleration("ddL43");
	symbol_numeric *ddalpha41=sys.get_Acceleration("ddalpha41");
	symbol_numeric *ddalpha42=sys.get_Acceleration("ddalpha42");
	symbol_numeric *ddalpha43=sys.get_Acceleration("ddalpha43");
	symbol_numeric *ddalpha44=sys.get_Acceleration("ddalpha44");

// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************
	//A-arm
	//A-arm lenght
	symbol_numeric L44 = *sys.new_Parameter("L44",-0.32140006);
	//A-arm connection to chassi x
	symbol_numeric L441 = *sys.new_Parameter("L441",-1.047);
	//A-arm connection to chassi y
	symbol_numeric L442 = *sys.new_Parameter("L442",-0.259);
	//A-arm connection to chassi z
	symbol_numeric L443 = *sys.new_Parameter("L443",0.302);
	//A-arm and shock absorber connextion x
	symbol_numeric L444 = *sys.new_Parameter("L444",-0.075);
	//A-arm and shock absorber connextion y
	symbol_numeric L445 = *sys.new_Parameter("L445",0.241);
	//A-arm and shock absorber connextion Z
	symbol_numeric L446 = *sys.new_Parameter("L446",-0.061);
	
	//Leaf-spring
	//Leaf sprign lenght
	symbol_numeric L46 = *sys.new_Parameter("L46",-0.33664707);
	//Leaf spring connection to chassi x
	symbol_numeric L461 = *sys.new_Parameter("L461",-1.047);
	//Leaf spring connection to chassi y
	symbol_numeric L462 = *sys.new_Parameter("L462",-0.1585);
	//Leaf spring connection to chassi z
	symbol_numeric L463 = *sys.new_Parameter("L463",0.600);

	//Shock absorber
	//Shock absorber lenght of part 1
	symbol_numeric L45 = *sys.new_Parameter("L45",-0.220278233);
	//Shock absorber lenght of part 2
	symbol_numeric L451 = *sys.new_Parameter("L451",-0.2937043107);	
	//Shock absorber connection to the chassi x
	symbol_numeric L452 = *sys.new_Parameter("L452",-1.122);	
	//Shock absorber connection to the chassi y
	symbol_numeric L453 = *sys.new_Parameter("L453",-0.297);
	//Shock absorber connection to the chassi z
	symbol_numeric L454 = *sys.new_Parameter("L454",0.632);	

	//Tie-rod
	//Tie rod lenght
	symbol_numeric L47 = *sys.new_Parameter("L47",-0.384246015);
	//Tie-rod movement point x
	symbol_numeric L471 = *sys.new_Parameter("L471",-0.907);
	//Tie-rod movement point z
	symbol_numeric L473 = *sys.new_Parameter("L473",0.600);
	//Tie-rod connection to chassi y
	symbol_numeric L472 = *sys.new_Parameter("L472",-0.07);

	//Hub
	//Hub center x
	symbol_numeric L4911 = *sys.new_Parameter("L4911",-1.047);	
	//Hub center y
	symbol_numeric L4912 = *sys.new_Parameter("L4912",-0.615);
	//Hub center z
	symbol_numeric L4913 = *sys.new_Parameter("L4913",0.356);
	
	//Connection point of hub and A-arm y
	symbol_numeric L491 = *sys.new_Parameter("L491",0.043);
	//Connection point of hub and A-arm z
	symbol_numeric L492 = *sys.new_Parameter("L492",-0.127);
	
	//Connection point of hub and Leaf-spring y
	symbol_numeric L493 = *sys.new_Parameter("L493",0.127);
	//Connection point of hub and Leaf-spring z
	symbol_numeric L494 = *sys.new_Parameter("L494",0.175);

	//Connection point of hub and Tie-rod x
	symbol_numeric L495 = *sys.new_Parameter("L495",0.14);
	//Connection point of hub and Tie-rod y
	symbol_numeric L496 = *sys.new_Parameter("L496",0.167);
	//Connection point of hub and Tie-rod z
	symbol_numeric L497 = *sys.new_Parameter("L497",0.175);

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************
// ************************************************************************************************
//	Define Bases
// ************************************************************************************************



	//A-arm
 	sys.new_Base("BARM41","BCHASSI03",1,0,0,betha41);
	//Leaf-spring
 	sys.new_Base("BLS41","BCHASSI03",1,0,0,betha42);
	//Schock-Absorber
 	sys.new_Base("BSA41","BCHASSI03",1,0,0,betha45);
	sys.new_Base("BSA42","BSA41",0,0,1,betha46);
	//Tie-rod
 	sys.new_Base("BTR41","BCHASSI03",1,0,0,betha43);
	sys.new_Base("BTR42","BTR41",0,0,1,betha44);
	//Hub
 	sys.new_Base("BHUB41","xyz",1,0,0,alpha41);
 	sys.new_Base("BHUB42","BHUB41",0,1,0,alpha42);
	sys.new_Base("BHUB43","BHUB42",0,0,1,alpha43);
	//Wheel
	sys.new_Base("BHUB44","BHUB43",0,1,0,alpha44);



// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	//Connection points to chassi
	//A-rm	
	Vector3D A01_B41AARM = *sys.new_Vector3D("A01_B41AARM",L441,L442,L443,"BCHASSI03");
	//Leaf spring
	Vector3D A01_B42LS = *sys.new_Vector3D("A01_B42LS",L461,L462,L463,"BCHASSI03");
	//Shock absorber
	Vector3D A01_B43SA = *sys.new_Vector3D("A01_B43SA",L452,L453,L454,"BCHASSI03");
	//Tie-rod
	Vector3D A01_B45TR = *sys.new_Vector3D("A01_B45TR",L471,0,L473,"BCHASSI03");
	Vector3D B45_B44TR = *sys.new_Vector3D("B45_B44TR",0,L472,0,"BCHASSI03");

	//End points of parts
	//A-arm
	Vector3D B41_E41AARM = *sys.new_Vector3D("B41_E21AARM",0,L46,0,"BARM41");
	//Leaf-spring
	Vector3D B42_E42LS = *sys.new_Vector3D("B42_E42LS",0,L46,0,"BLS41");
	//Schock absorber
	Vector3D B43_E44SA = *sys.new_Vector3D("B43_E44SA",0,L45,0,"BSA42");
	Vector3D B43_E43SA = *sys.new_Vector3D("B43_E43SA",0,L411,0,"BSA42");
	Vector3D E43_E45SA = *sys.new_Vector3D("E43_E45SA",0,L451,0,"BSA42");
	//Tie-rod
	Vector3D B44_E46TR = *sys.new_Vector3D("B44_E46TR",0,L47,0,"BTR42");
	

	//Additional points
	//Schock absorber connection point with A-arm
	Vector3D E41_E412AARM = *sys.new_Vector3D("E41_E412AARM",L444,L445,L446,"BARM41");
	//Distance from leaf spring and damper
	Vector3D E42_E421LS = *sys.new_Vector3D("E42_E421LS",0,0,0.145-(L46*sin(betha42)),"BCHASSI03");
	//Hub
	//Center point of hub
	Vector3D O_C41HUB = *sys.new_Vector3D("O_C41HUB",L41,L42,L43,"xyz");
	//Connection point with A-arm
	Vector3D C41_D41HUB = *sys.new_Vector3D("C41_D41HUB",0,L491,L492,"BHUB43");
	//Connection point with Leaf spring
	Vector3D C41_D42HUB = *sys.new_Vector3D("C41_D42HUB",0,L493,L494,"BHUB43");
	//Connection with Tie-rod
	Vector3D C41_D43HUB = *sys.new_Vector3D("C41_D43HUB",L495,L496,L497,"BHUB43");

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	//Connection points to chassi
	//A-arm
	Point * B41 = sys.new_Point("B41","A01_Chassi",&A01_B41AARM);
	//Leaf-spring	
	Point * B42 = sys.new_Point("B42","A01_Chassi",&A01_B42LS);
	//Shock-Absorber
	Point * B43 = sys.new_Point("B43","A01_Chassi",&A01_B43SA);
	//Tie-rod
	Point * B45 = sys.new_Point("B45","A01_Chassi",&A01_B45TR);
	Point * B44 = sys.new_Point("B44","B45",&B45_B44TR);

	//End points
	//A-arm
	Point * E41 = sys.new_Point("E41","B41",&B41_E41AARM);
	//Leaf-spring	
	Point * E42 = sys.new_Point("E42","B42",&B42_E42LS);
	//Shock absorber
	Point * E43 = sys.new_Point("E43","B43",&B43_E43SA);
	Point * E44 = sys.new_Point("E44","B43",&B43_E44SA);
	Point * E45 = sys.new_Point("E45","E43",&E43_E45SA);	
	//Tie-rod
	Point * E46 = sys.new_Point("E46","B44",&B44_E46TR);

	//Additional points
	//Shock absorber connection point with A-arm
	Point * E412 = sys.new_Point("E412","E41",&E41_E412AARM);
	//Bumper point
	Point * E421 = sys.new_Point("E421","E42",&E42_E421LS);

	//Hub
	//Hub center point
	Point * C41 = sys.new_Point("C41","O",&O_C41HUB);
	//Hub connection to A-arm
	Point * D41 = sys.new_Point("D41","C41",&C41_D41HUB);
	//Hub connection to Leaf spring
	Point * D42 = sys.new_Point("D42","C41",&C41_D42HUB);
	//Hub connection to Tie-rod
	Point * D43 = sys.new_Point("D43","C41",&C41_D43HUB);	

// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Viscosity
       	symbol_numeric  Cvis41 = *sys.new_Parameter("Cvis41",0.8);
	// Torsion spring
       	symbol_numeric  K41 = *sys.new_Parameter("K41",1.0);
	
	// Dynamic Parameters of A-arm
    	symbol_numeric  mAarm41 = *sys.new_Parameter("mAarm41",6.0);

	symbol_numeric  mxAarm41 = *sys.new_Parameter("mxAarm41",0.0);	
    	symbol_numeric  myAarm41 = *sys.new_Parameter("myAarm41",0.0);
	symbol_numeric  mzAarm41 = *sys.new_Parameter("mzAarm41",0.0);

    	symbol_numeric  IxxAarm41 = *sys.new_Parameter("IxxAarm41",0.1990525);
	symbol_numeric  IxyAarm41 = *sys.new_Parameter("IxyAarm41",0.0);
    	symbol_numeric  IyyAarm41 = *sys.new_Parameter("IyyAarm41",0.023235);
	symbol_numeric  IxzAarm41 = *sys.new_Parameter("IxzAarm41",0.0);
    	symbol_numeric  IzzAarm41 = *sys.new_Parameter("IzzAarm41",0.2158175);
	symbol_numeric  IyzAarm41 = *sys.new_Parameter("IyzAarm41",0.0);

	// Dynamic Parameters of Leaf spring
    	symbol_numeric  mLS41 = *sys.new_Parameter("mLS41",1.0);

	symbol_numeric  mxLS41 = *sys.new_Parameter("mxLS41",0.0);	
    	symbol_numeric  myLS41 = *sys.new_Parameter("myLS41",0.0);
	symbol_numeric  mzLS41 = *sys.new_Parameter("mzLS41",0.0);

    	symbol_numeric  IxxLS41 = *sys.new_Parameter("IxxLS41",1.0);
	symbol_numeric  IxyLS41 = *sys.new_Parameter("IxyLS41",0.0);
    	symbol_numeric  IyyLS41 = *sys.new_Parameter("IyyLS41",1.0);
	symbol_numeric  IxzLS41 = *sys.new_Parameter("IxzLS41",0.0);
    	symbol_numeric  IzzLS41 = *sys.new_Parameter("IzzLS41",1.0);
	symbol_numeric  IyzLS41 = *sys.new_Parameter("IyzLS41",0.0);

	// Dynamic Parameters of Shock absorber part 1
    	symbol_numeric  mSA41 = *sys.new_Parameter("mSA41",1.0);

	symbol_numeric  mxSA41 = *sys.new_Parameter("mxSA41",0.0);	
    	symbol_numeric  mySA41 = *sys.new_Parameter("mySA41",0.0);
	symbol_numeric  mzSA41 = *sys.new_Parameter("mzSA41",0.0);

    	symbol_numeric  IxxSA41 = *sys.new_Parameter("IxxSA41",1.0);
	symbol_numeric  IxySA41 = *sys.new_Parameter("IxySA41",0.0);
    	symbol_numeric  IyySA41 = *sys.new_Parameter("IyySA41",1.0);
	symbol_numeric  IxzSA41 = *sys.new_Parameter("IxzSA41",0.0);
    	symbol_numeric  IzzSA41 = *sys.new_Parameter("IzzSA41",1.0);
	symbol_numeric  IyzSA41 = *sys.new_Parameter("IyzSA41",0.0);

	// Dynamic Parameters of Shock absorber part 2
    	symbol_numeric  mSA42 = *sys.new_Parameter("mSA42",1.0);

	symbol_numeric  mxSA42 = *sys.new_Parameter("mxSA42",0.0);	
    	symbol_numeric  mySA42 = *sys.new_Parameter("mySA42",0.0);
	symbol_numeric  mzSA42 = *sys.new_Parameter("mzSA42",0.0);

    	symbol_numeric  IxxSA42 = *sys.new_Parameter("IxxSA42",1.0);
	symbol_numeric  IxySA42 = *sys.new_Parameter("IxySA42",0.0);
    	symbol_numeric  IyySA42 = *sys.new_Parameter("IyySA42",1.0);
	symbol_numeric  IxzSA42 = *sys.new_Parameter("IxzSA42",0.0);
    	symbol_numeric  IzzSA42 = *sys.new_Parameter("IzzSA42",1.0);
	symbol_numeric  IyzSA42 = *sys.new_Parameter("IyzSA42",0.0);

	// Dynamic Parameters of Tie-rod
    	symbol_numeric  mTR41 = *sys.new_Parameter("mTR41",1.0);

	symbol_numeric  mxTR41 = *sys.new_Parameter("mxTR41",0.0);	
    	symbol_numeric  myTR41 = *sys.new_Parameter("myTR41",0.0);
	symbol_numeric  mzTR41 = *sys.new_Parameter("mzTR41",0.0);

    	symbol_numeric  IxxTR41 = *sys.new_Parameter("IxxTR41",1.0);
	symbol_numeric  IxyTR41 = *sys.new_Parameter("IxyTR41",0.0);
    	symbol_numeric  IyyTR41 = *sys.new_Parameter("IyyTR41",1.0);
	symbol_numeric  IxzTR41 = *sys.new_Parameter("IxzTR41",0.0);
    	symbol_numeric  IzzTR41 = *sys.new_Parameter("IzzTR41",1.0);
	symbol_numeric  IyzTR41 = *sys.new_Parameter("IyzTR41",0.0);

	// Dynamic Parameters of Hub
    	symbol_numeric  mHUB41 = *sys.new_Parameter("mHUB41",19.117);

	symbol_numeric  mxHUB41 = *sys.new_Parameter("mxHUB41",0.0);	
    	symbol_numeric  myHUB41 = *sys.new_Parameter("myHUB41",0.0);
	symbol_numeric  mzHUB41 = *sys.new_Parameter("mzHUB41",0.0);

    	symbol_numeric  IxxHUB41 = *sys.new_Parameter("IxxHUB41",1.0);
	symbol_numeric  IxyHUB41 = *sys.new_Parameter("IxyHUB41",0.0);
    	symbol_numeric  IyyHUB41 = *sys.new_Parameter("IyyHUB41",1.0);
	symbol_numeric  IxzHUB41 = *sys.new_Parameter("IxzHUB41",0.0);
    	symbol_numeric  IzzHUB41 = *sys.new_Parameter("IzzHUB41",1.0);
	symbol_numeric  IyzHUB41 = *sys.new_Parameter("IyzHUB41",0.0);

	// Dynamic Parameters of Wheel
    	symbol_numeric  mWH41 = *sys.new_Parameter("mWH41",38.23);

	symbol_numeric  mxWH41 = *sys.new_Parameter("mxWH41",0.0);	
    	symbol_numeric  myWH41 = *sys.new_Parameter("myWH41",0.0);
	symbol_numeric  mzWH41 = *sys.new_Parameter("mzWH41",0.0);

    	symbol_numeric  IxxWH41 = *sys.new_Parameter("IxxWH41",1.2402);
	symbol_numeric  IxyWH41 = *sys.new_Parameter("IxyWH41",0.0);
    	symbol_numeric  IyyWH41 = *sys.new_Parameter("IyyWH41",1.908);
	symbol_numeric  IxzWH41 = *sys.new_Parameter("IxzWH41",0.0);
    	symbol_numeric  IzzWH41 = *sys.new_Parameter("IzzWH41",1.2402);
	symbol_numeric  IyzWH41 = *sys.new_Parameter("IyzWH41",0.0);

	//Gravity Center Vectors    

	Vector3D B41Arm41_GArm41= *sys.new_Vector3D("B41Arm41_GArm41",mxAarm41/mAarm41,myAarm41/mAarm41,mzAarm41/mAarm41,"BARM41");
	Vector3D B42LS41_GLS41= *sys.new_Vector3D("B42LS41_GLS41",mxLS41/mLS41,myLS41/mLS41,mzLS41/mLS41,"BLS41");
	Vector3D B43SA41_GSA41= *sys.new_Vector3D("B43SA41_GSA41",mxSA41/mSA41,mySA41/mSA41,mzSA41/mSA41,"BSA42");
	Vector3D E43SA42_GSA42= *sys.new_Vector3D("E43SA42_GSA42",mxSA42/mSA42,mySA42/mSA42,mzSA42/mSA42,"BSA42");
	Vector3D B44TR41_GTR41= *sys.new_Vector3D("B44TR41_GTR41",mxTR41/mTR41,myTR41/mTR41,mzTR41/mTR41,"BTR42");
	Vector3D C41HUB41_GHUB41= *sys.new_Vector3D("C41HUB41_GHUB41",mxHUB41/mHUB41,myHUB41/mHUB41,mzHUB41/mHUB41,"BHUB43");
	Vector3D C41WH41_GWH41= *sys.new_Vector3D("C41WH41_GWH41",mxWH41/mWH41,myWH41/mWH41,mzWH41/mWH41,"BHUB44");


	//Inertia Tensors

    	Tensor3D IAarm41 = *sys.new_Tensor3D("IAarm41",(ex)IxxAarm41,(ex)IxyAarm41,(ex)IxzAarm41,(ex)IxyAarm41,(ex)IyyAarm41,(ex)IyzAarm41,(ex)IxzAarm41,(ex)IyzAarm41,(ex)IzzAarm41,"BARM41");
    	Tensor3D ILS41 = *sys.new_Tensor3D("ILS41",(ex)IxxLS41,(ex)IxyLS41,(ex)IxzLS41,(ex)IxyLS41,(ex)IyyLS41,(ex)IyzLS41,(ex)IxzLS41,(ex)IyzLS41,(ex)IzzLS41,"BLS41");
    	Tensor3D ISA41 = *sys.new_Tensor3D("ISA41",(ex)IxxSA41,(ex)IxySA41,(ex)IxzSA41,(ex)IxySA41,(ex)IyySA41,(ex)IyzSA41,(ex)IxzSA41,(ex)IyzSA41,(ex)IzzSA41,"BSA42");
    	Tensor3D ISA42 = *sys.new_Tensor3D("ISA42",(ex)IxxSA42,(ex)IxySA42,(ex)IxzSA42,(ex)IxySA42,(ex)IyySA42,(ex)IyzSA42,(ex)IxzSA42,(ex)IyzSA42,(ex)IzzSA42,"BSA42");
    	Tensor3D ITR41 = *sys.new_Tensor3D("ITR41",(ex)IxxTR41,(ex)IxyTR41,(ex)IxzTR41,(ex)IxyTR41,(ex)IyyTR41,(ex)IyzTR41,(ex)IxzTR41,(ex)IyzTR41,(ex)IzzTR41,"BTR42");
    	Tensor3D IHUB41 = *sys.new_Tensor3D("IHUB41",(ex)IxxHUB41,(ex)IxyHUB41,(ex)IxzHUB41,(ex)IxyHUB41,(ex)IyyHUB41,(ex)IyzHUB41,(ex)IxzHUB41,(ex)IyzHUB41,(ex)IzzHUB41,"BHUB43");
    	Tensor3D IWH41 = *sys.new_Tensor3D("IWH41",(ex)IxxWH41,(ex)IxyWH41,(ex)IxzWH41,(ex)IxyWH41,(ex)IyyWH41,(ex)IyzWH41,(ex)IxzWH41,(ex)IyzWH41,(ex)IzzWH41,"BHUB44");


// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Aarm41 = sys.new_Frame("Fra_Aarm41","B41","BARM41");
	Frame * Fra_LS41 = sys.new_Frame("Fra_LS41","B42","BLS41");
	
	Frame * Fra_SA42 = sys.new_Frame("Fra_SA42","B43","BSA42");
	
	Frame * Fra_TR42 = sys.new_Frame("Fra_TR42","B44","BTR42");
	
	Frame * Fra_HUB43 = sys.new_Frame("Fra_HUB43","C41","BHUB43");
	Frame * Fra_WH41 = sys.new_Frame("Fra_WH41","C41","BHUB44");

// ************************************************************************************************
//	Define Solids
// ************************************************************************************************
	

	
	Solid * Aarm41 = sys.new_Solid("Aarm41","B41","BARM41","mAarm41","B41Arm41_GArm41","IAarm41");
	Solid * LS41 = sys.new_Solid("LS41","B42","BLS41","mLS41","B42LS41_GLS41","ILS41");
	Solid * SA41 = sys.new_Solid("SA41","B43","BSA42","mSA41","B43SA41_GSA41","ISA41");
	Solid * SA42 = sys.new_Solid("SA42","E43","BSA42","mSA42","E43SA42_GSA42","ISA42");	
	Solid * TR41 = sys.new_Solid("TR41","B44","BTR42","mTR41","B44TR41_GTR41","ITR41");
	Solid * HUB41 = sys.new_Solid("HUB41","C41","BHUB43","mHUB41","C41HUB41_GHUB41","IHUB41");
	Solid * WH41 = sys.new_Solid("WH41","C41","BHUB44","mWH41","C41WH41_GWH41","IWH41");

// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

        Drawing3D * Aarm413D = sys.new_Drawing3D("Aarm413D", "Aarm41","./solids/aarm41.stl",1,0,0,1);
        Drawing3D * LS413D = sys.new_Drawing3D("LS413D", "LS41","./solids/LS41.stl",1,0,0,1);
        Drawing3D * TR413D = sys.new_Drawing3D("TR413D", "TR41","./solids/TR41.stl",1,0,0,1);
        Drawing3D * SA413D = sys.new_Drawing3D("SA413D", "SA41","./solids/SA41.stl",1,0,0,0.5);
        Drawing3D * SA423D = sys.new_Drawing3D("SA423D", "SA42","./solids/SA42.stl",1,0,0,1);

	Drawing3D * HUB413D = sys.new_Drawing3D("HUB413D", "HUB41","./solids/hub41.stl",1,0,0,1);
//	Drawing3D * WH413D = sys.new_Drawing3D("WH413D", "WH41","./solids/wh31.stl",1,0,0,1);


	symbol_numeric alpha010 = *sys.new_Parameter("alpha010",0.0);
	symbol_numeric alpha020 = *sys.new_Parameter("alpha020",0.0);
	symbol_numeric alpha030 = *sys.new_Parameter("alpha030",0.0);
	symbol_numeric L010 = *sys.new_Parameter("L010",0.0);
	symbol_numeric L020 = *sys.new_Parameter("L020",0.0);
	symbol_numeric L030 = *sys.new_Parameter("L030",0.0);
	symbol_numeric L180 = *sys.new_Parameter("L180",0.0);
	symbol_numeric betha120 = *sys.new_Parameter("betha120",0.0);
	symbol_numeric betha220 = *sys.new_Parameter("betha220",0.0);
	symbol_numeric betha320 = *sys.new_Parameter("betha320",0.02);
	symbol_numeric betha420 = *sys.new_Parameter("betha420",0.02);
	



coord_indep_init = (alpha01-alpha010),(alpha02-alpha020),(alpha03-alpha030),(L01-L010),(L02-L020),(L03-L030),(L18-L180),(betha12-betha120),(betha22+betha220),(betha32-betha320),(betha42-betha420);

// ************************************************************************************************
// 	Point drawing
// ************************************************************************************************
	Drawing3D * ContactPoint1_3D = sys.new_Drawing3D("ContactPoint1_3D","B15", "BCHASSI03" ,"./solids/spheremmx10.stl",1,0,1,0.6);
cout << "1 " << endl;

	Drawing3D * ContactPoint2_3D = sys.new_Drawing3D("ContactPoint2_3D","E11", "BARM11" ,"./solids/copy of spheremmx10.stl",0,0,1,0.6);
cout << "2 " << endl;
	Drawing3D * ContactPoint3_3D = sys.new_Drawing3D("ContactPoint3_3D","E12", "BLS11" ,"./solids/another copy of spheremmx10.stl",0.5,0,0.5,0.6);
cout << "3 " << endl;
	Drawing3D * ContactPoint4_3D = sys.new_Drawing3D("ContactPoint4_3D","E13", "BSA12" ,"./solids/third copy of spheremmx10.stl",0,0.5,0.5,0.6);
cout << " 4" << endl;
	Drawing3D * ContactPoint5_3D = sys.new_Drawing3D("ContactPoint5_3D","E14", "BSA12" ,"./solids/4th copy of spheremmx10.stl",0,0.5,0.5,0.6);
cout << "5 " << endl;
	Drawing3D * ContactPoint6_3D = sys.new_Drawing3D("ContactPoint6_3D","E15", "BSA12" ,"./solids/5th copy of spheremmx10.stl",0,0.5,0.5,0.6);
cout << "6 " << endl;
	Drawing3D * ContactPoint7_3D = sys.new_Drawing3D("ContactPoint7_3D","E112", "BARM11" ,"./solids/6th copy of spheremmx10.stl",0.5,0.5,1,0.6);
cout << " 7" << endl;
	//Drawing3D * ContactPoint8_3D = sys.new_Drawing3D("ContactPoint8_3D","E121", "BLS11" ,"./solids/7th copy of spheremmx10.stl",0.5,0.5,1,0.6);
cout << " 8" << endl;
	Drawing3D * ContactPoint9_3D = sys.new_Drawing3D("ContactPoint9_3D","D11", "BHUB13" ,"./solids/8th copy of spheremmx10.stl",0,0,1,0.6);
cout << " 9" << endl;
	Drawing3D * ContactPoint10_3D = sys.new_Drawing3D("ContactPoint10_3D","D12", "BHUB13" ,"./solids/9th copy of spheremmx10.stl",0,0,1,0.6);
cout << " 10" << endl;
	Drawing3D * ContactPoint11_3D = sys.new_Drawing3D("ContactPoint11_3D","D13", "BHUB13" ,"./solids/10th copy of spheremmx10.stl",0,0,1,0.6);
cout << " 11" << endl;
	Drawing3D * ContactPoint12_3D = sys.new_Drawing3D("ContactPoint12_3D","C11", "BHUB13" ,"./solids/11th copy of spheremmx10.stl",1,1,1,0.6);


	
	Drawing3D * ContactPoint14_3D = sys.new_Drawing3D("ContactPoint14_3D","E21", "BARM21" ,"./solids/12th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint15_3D = sys.new_Drawing3D("ContactPoint15_3D","E22", "BLS21" ,"./solids/13th copy of spheremmx10.stl",0.5,0,0.5,0.6);
	Drawing3D * ContactPoint16_3D = sys.new_Drawing3D("ContactPoint16_3D","E23", "BSA22" ,"./solids/14th copy of spheremmx10.stl",0,0.5,0.5,0.6);
	Drawing3D * ContactPoint17_3D = sys.new_Drawing3D("ContactPoint17_3D","E24", "BSA22" ,"./solids/15th copy of spheremmx10.stl",0,0.5,0.5,0.6);
	Drawing3D * ContactPoint18_3D = sys.new_Drawing3D("ContactPoint18_3D","E25", "BSA22" ,"./solids/16th copy of spheremmx10.stl",0,0.5,0.5,0.6);
	Drawing3D * ContactPoint19_3D = sys.new_Drawing3D("ContactPoint19_3D","E212", "BARM21" ,"./solids/17th copy of spheremmx10.stl",0.5,0.5,1,0.6);
	Drawing3D * ContactPoint20_3D = sys.new_Drawing3D("ContactPoint20_3D","E221", "BLS21" ,"./solids/18th copy of spheremmx10.stl",0.5,0.5,1,0.6);
	Drawing3D * ContactPoint21_3D = sys.new_Drawing3D("ContactPoint21_3D","D21", "BHUB23" ,"./solids/19th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint22_3D = sys.new_Drawing3D("ContactPoint22_3D","D22", "BHUB23" ,"./solids/20th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint23_3D = sys.new_Drawing3D("ContactPoint23_3D","D23", "BHUB23" ,"./solids/21th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint24_3D = sys.new_Drawing3D("ContactPoint24_3D","C21", "BHUB23" ,"./solids/22th copy of spheremmx10.stl",1,1,1,0.6);
cout << "13 " << endl;
	Drawing3D * ContactPoint25_3D = sys.new_Drawing3D("ContactPoint25_3D","B35", "BCHASSI03" ,"./solids/23th copy of spheremmx10.stl",1,0,1,0.6);
	Drawing3D * ContactPoint26_3D = sys.new_Drawing3D("ContactPoint26_3D","E31", "BARM31" ,"./solids/24th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint27_3D = sys.new_Drawing3D("ContactPoint27_3D","E32", "BLS31" ,"./solids/25th copy of spheremmx10.stl",0.5,0,0.5,0.6);
	Drawing3D * ContactPoint28_3D = sys.new_Drawing3D("ContactPoint28_3D","E33", "BSA32" ,"./solids/26th copy of spheremmx10.stl",0,0.5,0.5,0.6);
	Drawing3D * ContactPoint29_3D = sys.new_Drawing3D("ContactPoint29_3D","E34", "BSA32" ,"./solids/27th copy of spheremmx10.stl",0,0.5,0.5,0.6);
	Drawing3D * ContactPoint30_3D = sys.new_Drawing3D("ContactPoint30_3D","E35", "BSA32" ,"./solids/28th copy of spheremmx10.stl",0,0.5,0.5,0.6);
	Drawing3D * ContactPoint31_3D = sys.new_Drawing3D("ContactPoint31_3D","E312", "BARM31" ,"./solids/29th copy of spheremmx10.stl",0.5,0.5,1,0.6);
	Drawing3D * ContactPoint32_3D = sys.new_Drawing3D("ContactPoint32_3D","E321", "BLS31" ,"./solids/30th copy of spheremmx10.stl",0.5,0.5,1,0.6);
	Drawing3D * ContactPoint33_3D = sys.new_Drawing3D("ContactPoint33_3D","D31", "BHUB33" ,"./solids/31th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint34_3D = sys.new_Drawing3D("ContactPoint34_3D","D32", "BHUB33" ,"./solids/32th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint35_3D = sys.new_Drawing3D("ContactPoint35_3D","D33", "BHUB33" ,"./solids/33th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint36_3D = sys.new_Drawing3D("ContactPoint36_3D","C31", "BHUB33" ,"./solids/34th copy of spheremmx10.stl",1,1,1,0.6);
cout << "14 " << endl;

	Drawing3D * ContactPoint38_3D = sys.new_Drawing3D("ContactPoint38_3D","E41", "BARM41" ,"./solids/35th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint39_3D = sys.new_Drawing3D("ContactPoint39_3D","E42", "BLS41" ,"./solids/36th copy of spheremmx10.stl",0.5,0,0.5,0.6);
	Drawing3D * ContactPoint40_3D = sys.new_Drawing3D("ContactPoint40_3D","E43", "BSA42" ,"./solids/37th copy of spheremmx10.stl",0,0.5,0.5,0.6);
	Drawing3D * ContactPoint41_3D = sys.new_Drawing3D("ContactPoint41_3D","E44", "BSA42" ,"./solids/38th copy of spheremmx10.stl",0,0.5,0.5,0.6);
	Drawing3D * ContactPoint42_3D = sys.new_Drawing3D("ContactPoint42_3D","E45", "BSA42" ,"./solids/39th copy of spheremmx10.stl",0,0.5,0.5,0.6);
	Drawing3D * ContactPoint43_3D = sys.new_Drawing3D("ContactPoint43_3D","E412", "BARM41" ,"./solids/40th copy of spheremmx10.stl",0.5,0.5,1,0.6);
	Drawing3D * ContactPoint44_3D = sys.new_Drawing3D("ContactPoint44_3D","E421", "BLS41" ,"./solids/41th copy of spheremmx10.stl",0.5,0.5,1,0.6);
	Drawing3D * ContactPoint45_3D = sys.new_Drawing3D("ContactPoint45_3D","D41", "BHUB43" ,"./solids/42th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint46_3D = sys.new_Drawing3D("ContactPoint46_3D","D42", "BHUB43" ,"./solids/43th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint47_3D = sys.new_Drawing3D("ContactPoint47_3D","D43", "BHUB43" ,"./solids/44th copy of spheremmx10.stl",0,0,1,0.6);
	Drawing3D * ContactPoint48_3D = sys.new_Drawing3D("ContactPoint48_3D","C41", "BHUB43" ,"./solids/45th copy of spheremmx10.stl",1,1,1,0.6);
cout << " 12" << endl;

        Drawing3D * Fra_Chassi3D = sys.new_Drawing3D("Fra_Chassi3D","Fra_Chassi01",0.09);

        Drawing3D * Fra_Arm113D = sys.new_Drawing3D("Fra_Arm113D","Fra_Aarm11",0.09);
        Drawing3D * Fra_LS113D = sys.new_Drawing3D("Fra_LS113D","Fra_LS11",0.09);
        Drawing3D * Fra_SA123D = sys.new_Drawing3D("Fra_SA123D","Fra_SA12",0.09);
        Drawing3D * Fra_TR123D = sys.new_Drawing3D("Fra_TR123D","Fra_TR12",0.09);
        Drawing3D * Fra_HUB133D = sys.new_Drawing3D("Fra_HUB133D","Fra_HUB13",0.09);
        Drawing3D * Fra_WH113D = sys.new_Drawing3D("Fra_WH113D","Fra_WH11",0.09);


        Drawing3D * Fra_Arm213D = sys.new_Drawing3D("Fra_Arm213D","Fra_Aarm21",0.09);
        Drawing3D * Fra_LS213D = sys.new_Drawing3D("Fra_LS213D","Fra_LS21",0.09);
        Drawing3D * Fra_SA223D = sys.new_Drawing3D("Fra_SA223D","Fra_SA22",0.09);
        Drawing3D * Fra_TR223D = sys.new_Drawing3D("Fra_TR223D","Fra_TR22",0.09);
        Drawing3D * Fra_HUB233D = sys.new_Drawing3D("Fra_HUB233D","Fra_HUB23",0.09);
        Drawing3D * Fra_WH213D = sys.new_Drawing3D("Fra_WH213D","Fra_WH21",0.09);

        Drawing3D * Fra_Arm313D = sys.new_Drawing3D("Fra_Arm313D","Fra_Aarm31",0.09);
        Drawing3D * Fra_LS313D = sys.new_Drawing3D("Fra_LS313D","Fra_LS31",0.09);
        Drawing3D * Fra_SA323D = sys.new_Drawing3D("Fra_SA323D","Fra_SA32",0.09);
        Drawing3D * Fra_TR323D = sys.new_Drawing3D("Fra_TR323D","Fra_TR32",0.09);
        Drawing3D * Fra_HUB333D = sys.new_Drawing3D("Fra_HUB333D","Fra_HUB33",0.09);
        Drawing3D * Fra_WH313D = sys.new_Drawing3D("Fra_WH313D","Fra_WH31",0.09);

        Drawing3D * Fra_Arm413D = sys.new_Drawing3D("Fra_Arm413D","Fra_Aarm41",0.09);
        Drawing3D * Fra_LS413D = sys.new_Drawing3D("Fra_LS413D","Fra_LS41",0.09);
        Drawing3D * Fra_SA423D = sys.new_Drawing3D("Fra_SA423D","Fra_SA42",0.09);
        Drawing3D * Fra_TR423D = sys.new_Drawing3D("Fra_TR423D","Fra_TR42",0.09);
        Drawing3D * Fra_HUB433D = sys.new_Drawing3D("Fra_HUB433D","Fra_HUB43",0.09);
        Drawing3D * Fra_WH413D = sys.new_Drawing3D("Fra_WH413D","Fra_WH41",0.09);



// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

	cout << "Input Vector" << endl;

	//symbol_numeric FBlockx = *sys.new_Input("FBlockx",0.0);
	//symbol_numeric MPendulumy = *sys.new_Input("MPendulumy",0.0);

	//Vector3D FBlock = *sys.new_Vector3D("FBlock",FBlockx,0,0,"BBlock");
	//Vector3D MBlock = *sys.new_Vector3D("MBlock",0,0,0, "BBlock");
	//Vector3D FPendulum = *sys.new_Vector3D("FPendulum",0,0,0,"BPendulum");
	//Vector3D MPendulum = *sys.new_Vector3D("MPendulum",0,MPendulumy,0, "BPendulum");


// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************
 

//	Vector3D FK_LS11 = *sys.new_Vector3D("FK_LS11",0,0,,"BCHASSI03");

// 	Vector3D FK_LS11 = *sys.new_Vector3D("FK_LS11",0.0,0.0,K11*(0.145-(L16*sin(betha12))),"BCHASSI03");
// 	Vector3D MK_LS11 = *sys.new_Vector3D("MK_LS11",0.0,0.0,0.0, "BCHASSI03");

// 	Vector3D FK_LS21 = *sys.new_Vector3D("FK_LS21",0.0,0.0,K21*(0.145-(L26*sin(betha22))),"BCHASSI03");
// 	Vector3D MK_LS21 = *sys.new_Vector3D("MK_LS21",0.0,0.0,0.0, "BCHASSI03");

// 	Vector3D FK_LS31 = *sys.new_Vector3D("FK_LS31",0.0,0.0,K31*(0.145-(L36*sin(betha32))),"BCHASSI03");
// 	Vector3D MK_LS31 = *sys.new_Vector3D("MK_LS31",0.0,0.0,0.0, "BCHASSI03");

// 	Vector3D FK_LS41 = *sys.new_Vector3D("FK_LS41",0.0,0.0,K41*(0.145-(L46*sin(betha42))),"BCHASSI03");
// 	Vector3D MK_LS41 = *sys.new_Vector3D("MK_LS41",0.0,0.0,0.0, "BCHASSI03");

// 	Modified Wrenches
	Vector3D FK_LS11 = *sys.new_Vector3D("FK_LS11",0.0,0.0,0.0,"BCHASSI03");
	Vector3D MK_LS11 = *sys.new_Vector3D("MK_LS11",K11*betha12,0.0,0.0, "BCHASSI03");

	Vector3D FK_LS21 = *sys.new_Vector3D("FK_LS21",0.0,0.0,0.0,"BCHASSI03");
	Vector3D MK_LS21 = *sys.new_Vector3D("MK_LS21",K21*betha22,0.0,0.0, "BCHASSI03");

	Vector3D FK_LS31 = *sys.new_Vector3D("FK_LS31",0.0,0.0,0.0,"BCHASSI03");
	Vector3D MK_LS31 = *sys.new_Vector3D("MK_LS31",K31*betha32,0.0,0.0, "BCHASSI03");

	Vector3D FK_LS41 = *sys.new_Vector3D("FK_LS41",0.0,0.0,0.0,"BCHASSI03");
	Vector3D MK_LS41 = *sys.new_Vector3D("MK_LS41",-K41*betha42,0.0,0.0, "BCHASSI03");

	
	
	
	Vector3D FV_SA11 = -Cvis11 *( sys.Velocity_Vector("Fra_SA12" ,"E15", "SA12" ));
	Vector3D MV_SA11= *sys.new_Vector3D("MV_SA11",0.0,0.0,0.0,"BSA12");
	
	Vector3D FV_SA21 = -Cvis21 *( sys.Velocity_Vector("Fra_SA22" ,"E25", "SA22" ));
	Vector3D MV_SA21= *sys.new_Vector3D("MV_SA21",0.0,0.0,0.0,"BSA22");

	Vector3D FV_SA31 = -Cvis31 *( sys.Velocity_Vector("Fra_SA32" ,"E35", "SA32" ));
	Vector3D MV_SA31= *sys.new_Vector3D("MV_SA31",0.0,0.0,0.0,"BSA32");

	Vector3D FV_SA41 = -Cvis41 *( sys.Velocity_Vector("Fra_SA42" ,"E45", "SA42" ));
	Vector3D MV_SA41= *sys.new_Vector3D("MV_SA41",0.0,0.0,0.0,"BSA42");


		// Coordinates of the contact points
		symbol_numeric x1 = *sys.new_Input("x1",0.0);
		symbol_numeric y1 = *sys.new_Input("y1",0.0);
		symbol_numeric z1 = *sys.new_Input("z1",0.0);

		symbol_numeric F1x = *sys.new_Input("F1x",0.0);
		symbol_numeric F1y = *sys.new_Input("F1y",0.0);
		symbol_numeric F1z = *sys.new_Input("F1z",0.0);
		
		symbol_numeric M1x = *sys.new_Input("M1x",0.0);
		symbol_numeric M1y = *sys.new_Input("M1y",0.0);
		symbol_numeric M1z = *sys.new_Input("M1z",0.0);
		
		

		symbol_numeric x2 = *sys.new_Input("x2",0.0);
		symbol_numeric y2 = *sys.new_Input("y2",0.0);
		symbol_numeric z2 = *sys.new_Input("z2",0.0);

		symbol_numeric F2x = *sys.new_Input("F2x",0.0);
		symbol_numeric F2y = *sys.new_Input("F2y",0.0);
		symbol_numeric F2z = *sys.new_Input("F2z",0.0);
		
		symbol_numeric M2x = *sys.new_Input("M2x",0.0);
		symbol_numeric M2y = *sys.new_Input("M2y",0.0);
		symbol_numeric M2z = *sys.new_Input("M2z",0.0);
		
		
		
		symbol_numeric x3 = *sys.new_Input("x3",0.0);
		symbol_numeric y3 = *sys.new_Input("y3",0.0);
		symbol_numeric z3 = *sys.new_Input("z3",0.0);

		symbol_numeric F3x = *sys.new_Input("F3x",0.0);
		symbol_numeric F3y = *sys.new_Input("F3y",0.0);
		symbol_numeric F3z = *sys.new_Input("F3z",0.0);
		
		symbol_numeric M3x = *sys.new_Input("M3x",0.0);
		symbol_numeric M3y = *sys.new_Input("M3y",0.0);
		symbol_numeric M3z = *sys.new_Input("M3z",0.0);
		
		

		symbol_numeric x4 = *sys.new_Input("x4",0.0);
		symbol_numeric y4 = *sys.new_Input("y4",0.0);
		symbol_numeric z4 = *sys.new_Input("z4",0.0);

		symbol_numeric F4x = *sys.new_Input("F4x",0.0);
		symbol_numeric F4y = *sys.new_Input("F4y",0.0);
		symbol_numeric F4z = *sys.new_Input("F4z",0.0);

		symbol_numeric M4x = *sys.new_Input("M4x",0.0);
		symbol_numeric M4y = *sys.new_Input("M4y",0.0);
		symbol_numeric M4z = *sys.new_Input("M4z",0.0);
		
		

		Vector3D O_P1 = *sys.new_Vector3D("OP1",x1,y1,z1, "xyz");	
		Vector3D O_P2 = *sys.new_Vector3D("OP2",x2,y2,z2, "xyz");	
		Vector3D O_P3 = *sys.new_Vector3D("OP3",x3,y3,z3, "xyz");
		Vector3D O_P4 = *sys.new_Vector3D("OP4",x4,y4,z4, "xyz");	

		Point * P1 = sys.new_Point("P1","O",&O_P1);
		Point * P2 = sys.new_Point("P2","O",&O_P2);
		Point * P3 = sys.new_Point("P3","O",&O_P3);
		Point * P4 = sys.new_Point("P4","O",&O_P4);

		Drawing3D * ContactPointWheel1_3D = sys.new_Drawing3D("ContactPointWheel1_3D", "P1", "xyz" ,"./solids/bola.stl",0,0,1,0.6);		
		Drawing3D * ContactPointWheel2_3D = sys.new_Drawing3D("ContactPointWheel2_3D", "P2", "xyz" ,"./solids/bola.stl",0,0,1,0.6);		
		Drawing3D * ContactPointWheel3_3D = sys.new_Drawing3D("ContactPointWheel3_3D", "P3", "xyz" ,"./solids/bola.stl",0,0,1,0.6);		
		Drawing3D * ContactPointWheel4_4D = sys.new_Drawing3D("ContactPointWheel4_3D", "P4", "xyz" ,"./solids/bola.stl",0,0,1,0.6);		

	
		Vector3D V_abs_C1 = sys.Dt(O_C11HUB,"xyz");
		Vector3D V_abs_C2 = sys.Dt(O_C21HUB,"xyz");
		Vector3D V_abs_C3 = sys.Dt(O_C31HUB,"xyz");
		Vector3D V_abs_C4 = sys.Dt(O_C41HUB,"xyz");

		Vector3D OM_abs_W1 = sys.Angular_Velocity("xyz","BHUB14");
		Vector3D OM_abs_W2 = sys.Angular_Velocity("xyz","BHUB24");
		Vector3D OM_abs_W3 = sys.Angular_Velocity("xyz","BHUB34");
		Vector3D OM_abs_W4 = sys.Angular_Velocity("xyz","BHUB44");

		Vector3D V_abs_P1 = V_abs_C1 + (OM_abs_W1^(O_P1-O_C11HUB));
		Vector3D V_abs_P2 = V_abs_C2 + (OM_abs_W2^(O_P2-O_C21HUB));
		Vector3D V_abs_P3 = V_abs_C3 + (OM_abs_W3^(O_P3-O_C31HUB));
		Vector3D V_abs_P4 = V_abs_C4 + (OM_abs_W4^(O_P4-O_C41HUB));

		Vector3D eyR1 = *sys.new_Vector3D("eyR1",0,1,0,"BHUB14");
		Vector3D eyR2 = *sys.new_Vector3D("eyR2",0,1,0,"BHUB24");
		Vector3D eyR3 = *sys.new_Vector3D("eyR3",0,1,0,"BHUB34");
		Vector3D eyR4 = *sys.new_Vector3D("eyR4",0,1,0,"BHUB44");

		
		Vector3D FGround1 = *sys.new_Vector3D("FGround1",F1x,F1y,F1z, "xyz");	
		Vector3D FGround2 = *sys.new_Vector3D("FGround2",F2x,F2y,F2z, "xyz");
		Vector3D FGround3 = *sys.new_Vector3D("FGround3",F3x,F3y,F3z, "xyz");
		Vector3D FGround4 = *sys.new_Vector3D("FGround4",F4x,F4y,F4z, "xyz");

		Vector3D MGround1 = *sys.new_Vector3D("MGround1",M1x,M1y,M1z, "xyz");
		Vector3D MGround2 = *sys.new_Vector3D("MGround2",M2x,M2y,M2z, "xyz");
		Vector3D MGround3 = *sys.new_Vector3D("MGround3",M3x,M3y,M3z, "xyz");
		Vector3D MGround4 = *sys.new_Vector3D("MGround4",M4x,M4y,M4z, "xyz");

		Vector3D VZERO_xyz = *sys.new_Vector3D("VZERO_xyz",0,0,0, "xyz");

		Vector3D eyR1_xyz = eyR1 + VZERO_xyz;
		Vector3D eyR2_xyz = eyR2 + VZERO_xyz;
		Vector3D eyR3_xyz = eyR3 + VZERO_xyz;
		Vector3D eyR4_xyz = eyR4 + VZERO_xyz;

		Vector3D O_CWheel1_xyz = O_C11HUB + VZERO_xyz;
		Vector3D O_CWheel2_xyz = O_C21HUB + VZERO_xyz;
		Vector3D O_CWheel3_xyz = O_C31HUB + VZERO_xyz;
		Vector3D O_CWheel4_xyz = O_C41HUB + VZERO_xyz;

		Vector3D V_abs_C1_xyz = V_abs_C1 + VZERO_xyz;
		Vector3D V_abs_C2_xyz = V_abs_C2 + VZERO_xyz;
		Vector3D V_abs_C3_xyz = V_abs_C3 + VZERO_xyz;
		Vector3D V_abs_C4_xyz = V_abs_C4 + VZERO_xyz;

		Vector3D OM_abs_W1_xyz = OM_abs_W1 + VZERO_xyz;
		Vector3D OM_abs_W2_xyz = OM_abs_W2 + VZERO_xyz;
		Vector3D OM_abs_W3_xyz = OM_abs_W3 + VZERO_xyz;
		Vector3D OM_abs_W4_xyz = OM_abs_W4 + VZERO_xyz;

		Vector3D V_abs_P1_xyz = V_abs_P1 + VZERO_xyz;
		Vector3D V_abs_P2_xyz = V_abs_P2 + VZERO_xyz;
		Vector3D V_abs_P3_xyz = V_abs_P3 + VZERO_xyz;
		Vector3D V_abs_P4_xyz = V_abs_P4 + VZERO_xyz;
	

		Matrix Kinematics_Wheels(13,4);

		// Matrix for the Kinematics of Wheel 1
		Kinematics_Wheels(0,0)=O_CWheel1_xyz(0,0);
		Kinematics_Wheels(1,0)=O_CWheel1_xyz(1,0);
		Kinematics_Wheels(2,0)=O_CWheel1_xyz(2,0);

		Kinematics_Wheels(3,0)=eyR1_xyz(0,0);
		Kinematics_Wheels(4,0)=eyR1_xyz(1,0);
		Kinematics_Wheels(5,0)=eyR1_xyz(2,0);

		Kinematics_Wheels(6,0)=V_abs_C1_xyz(0,0);
		Kinematics_Wheels(7,0)=V_abs_C1_xyz(1,0);
		Kinematics_Wheels(8,0)=V_abs_C1_xyz(2,0);

		Kinematics_Wheels(9,0) =OM_abs_W1_xyz(0,0);
		Kinematics_Wheels(10,0)=OM_abs_W1_xyz(1,0);
		Kinematics_Wheels(11,0)=OM_abs_W1_xyz(2,0);
		Kinematics_Wheels(12,0)=R;		
		

		// Matrix for the Kinematics of Wheel 2
		Kinematics_Wheels(0,1)=O_CWheel2_xyz(0,0);
		Kinematics_Wheels(1,1)=O_CWheel2_xyz(1,0);
		Kinematics_Wheels(2,1)=O_CWheel2_xyz(2,0);

		Kinematics_Wheels(3,1)=eyR2_xyz(0,0);
		Kinematics_Wheels(4,1)=eyR2_xyz(1,0);
		Kinematics_Wheels(5,1)=eyR2_xyz(2,0);

		Kinematics_Wheels(6,1)=V_abs_C2_xyz(0,0);
		Kinematics_Wheels(7,1)=V_abs_C2_xyz(1,0);
		Kinematics_Wheels(8,1)=V_abs_C2_xyz(2,0);

		Kinematics_Wheels(9,1) =OM_abs_W2_xyz(0,0);
		Kinematics_Wheels(10,1)=OM_abs_W2_xyz(1,0);
		Kinematics_Wheels(11,1)=OM_abs_W2_xyz(2,0);
		Kinematics_Wheels(12,1)=R;		
		
		
		// Matrix for the Kinematics of Wheel 3
		Kinematics_Wheels(0,2)=O_CWheel3_xyz(0,0);
		Kinematics_Wheels(1,2)=O_CWheel3_xyz(1,0);
		Kinematics_Wheels(2,2)=O_CWheel3_xyz(2,0);

		Kinematics_Wheels(3,2)=eyR3_xyz(0,0);
		Kinematics_Wheels(4,2)=eyR3_xyz(1,0);
		Kinematics_Wheels(5,2)=eyR3_xyz(2,0);

		Kinematics_Wheels(6,2)=V_abs_C3_xyz(0,0);
		Kinematics_Wheels(7,2)=V_abs_C3_xyz(1,0);
		Kinematics_Wheels(8,2)=V_abs_C3_xyz(2,0);

		Kinematics_Wheels(9,2) =OM_abs_W3_xyz(0,0);
		Kinematics_Wheels(10,2)=OM_abs_W3_xyz(1,0);
		Kinematics_Wheels(11,2)=OM_abs_W3_xyz(2,0);
		Kinematics_Wheels(12,2)=R;		
		
		
		// Matrix for the Kinematics of Wheel 4
		Kinematics_Wheels(0,3)=O_CWheel4_xyz(0,0);
		Kinematics_Wheels(1,3)=O_CWheel4_xyz(1,0);
		Kinematics_Wheels(2,3)=O_CWheel4_xyz(2,0);

		Kinematics_Wheels(3,3)=eyR4_xyz(0,0);
		Kinematics_Wheels(4,3)=eyR4_xyz(1,0);
		Kinematics_Wheels(5,3)=eyR4_xyz(2,0);

		Kinematics_Wheels(6,3)=V_abs_C4_xyz(0,0);
		Kinematics_Wheels(7,3)=V_abs_C4_xyz(1,0);
		Kinematics_Wheels(8,3)=V_abs_C4_xyz(2,0);

		Kinematics_Wheels(9,3) =OM_abs_W4_xyz(0,0);
		Kinematics_Wheels(10,3)=OM_abs_W4_xyz(1,0);
		Kinematics_Wheels(11,3)=OM_abs_W4_xyz(2,0);
		Kinematics_Wheels(12,3)=R;		

		// Matrix for the Contact point of the Wheels
		Matrix ContactPointVelocity(3,4);

		ContactPointVelocity(0,0)=V_abs_P1_xyz(0,0);
		ContactPointVelocity(1,0)=V_abs_P1_xyz(1,0);
		ContactPointVelocity(2,0)=V_abs_P1_xyz(2,0);

		ContactPointVelocity(0,1)=V_abs_P2_xyz(0,0);
		ContactPointVelocity(1,1)=V_abs_P2_xyz(1,0);
		ContactPointVelocity(2,1)=V_abs_P2_xyz(2,0);

		ContactPointVelocity(0,2)=V_abs_P3_xyz(0,0);
		ContactPointVelocity(1,2)=V_abs_P3_xyz(1,0);
		ContactPointVelocity(2,2)=V_abs_P3_xyz(2,0);

		ContactPointVelocity(0,3)=V_abs_P4_xyz(0,0);
		ContactPointVelocity(1,3)=V_abs_P4_xyz(1,0);
		ContactPointVelocity(2,3)=V_abs_P4_xyz(2,0);

		lst mylist;

		sys.export_Matrix_C	("Kinematics_Wheels"     ,"_Kinematics_Wheels"     ,Kinematics_Wheels     ,mylist     ,1);
		sys.export_Matrix_C	("ContactPointVelocity"  ,"_ContactPointVelocity"  ,ContactPointVelocity  ,mylist     ,1);

// sys.export_Matrix_MAPLE ("Kinematics_Wheels"     ,"_Kinematics_Wheels"     ,Kinematics_Wheels);
// system("maple Kinematics_Wheels.mpl > Kinematics_Wheels.log && bash ./replace.bash Kinematics_Wheels_maple_include.c Kinematics_Wheels_maple_include.c &");
	

// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	//Wrench3D * Gravity_Chassi = sys.Gravity_Wrench("Chassi");

/*	Wrench3D * Gravity_Aarm11 = sys.Gravity_Wrench("Aarm11");
	Wrench3D * Gravity_LS11 = sys.Gravity_Wrench("LS11");
	Wrench3D * Gravity_SA11 = sys.Gravity_Wrench("SA11");
	Wrench3D * Gravity_SA12 = sys.Gravity_Wrench("SA12");
	Wrench3D * Gravity_TR11 = sys.Gravity_Wrench("TR11");
	Wrench3D * Gravity_HUB11 = sys.Gravity_Wrench("HUB11");
	Wrench3D * Gravity_WH11 = sys.Gravity_Wrench("WH11");

	Wrench3D * Gravity_Aarm21 = sys.Gravity_Wrench("Aarm21");
	Wrench3D * Gravity_LS21 = sys.Gravity_Wrench("LS21");
	Wrench3D * Gravity_SA21 = sys.Gravity_Wrench("SA21");
	Wrench3D * Gravity_SA22 = sys.Gravity_Wrench("SA22");
	Wrench3D * Gravity_TR21 = sys.Gravity_Wrench("TR21");
	Wrench3D * Gravity_HUB21 = sys.Gravity_Wrench("HUB21");
	Wrench3D * Gravity_WH21 = sys.Gravity_Wrench("WH21");

	Wrench3D * Gravity_Aarm31 = sys.Gravity_Wrench("Aarm31");
	Wrench3D * Gravity_LS31 = sys.Gravity_Wrench("LS31");
	Wrench3D * Gravity_SA31 = sys.Gravity_Wrench("SA31");
	Wrench3D * Gravity_SA32 = sys.Gravity_Wrench("SA32");
	Wrench3D * Gravity_TR31 = sys.Gravity_Wrench("TR31");
	Wrench3D * Gravity_HUB31 = sys.Gravity_Wrench("HUB31");
	Wrench3D * Gravity_WH31 = sys.Gravity_Wrench("WH31");

	Wrench3D * Gravity_Aarm41 = sys.Gravity_Wrench("Aarm41");
	Wrench3D * Gravity_LS41 = sys.Gravity_Wrench("LS41");
	Wrench3D * Gravity_SA41 = sys.Gravity_Wrench("SA41");
	Wrench3D * Gravity_SA42 = sys.Gravity_Wrench("SA42");
	Wrench3D * Gravity_TR41 = sys.Gravity_Wrench("TR41");
	Wrench3D * Gravity_HUB41 = sys.Gravity_Wrench("HUB41");
	Wrench3D * Gravity_WH41 = sys.Gravity_Wrench("WH41");

*/
	//	Inertia
	Wrench3D * Inertia_Chassi = sys.Inertia_Wrench("Chassi");
	
// 	Wrench3D * Inertia_Aarm11 = sys.Inertia_Wrench("Aarm11");
// 	Wrench3D * Inertia_LS11 = sys.Inertia_Wrench("LS11");
// 	Wrench3D * Inertia_SA11 = sys.Inertia_Wrench("SA11");
// 	Wrench3D * Inertia_SA12 = sys.Inertia_Wrench("SA12");
// 	Wrench3D * Inertia_TR11 = sys.Inertia_Wrench("TR11");
// 	Wrench3D * Inertia_HUB11 = sys.Inertia_Wrench("HUB11");
	Wrench3D * Inertia_WH11 = sys.Inertia_Wrench("WH11");

// 	Wrench3D * Inertia_Aarm21 = sys.Inertia_Wrench("Aarm21");
// 	Wrench3D * Inertia_LS21 = sys.Inertia_Wrench("LS21");
// 	Wrench3D * Inertia_SA21 = sys.Inertia_Wrench("SA21");
// 	Wrench3D * Inertia_SA22 = sys.Inertia_Wrench("SA22");
// 	Wrench3D * Inertia_TR21 = sys.Inertia_Wrench("TR21");
// 	Wrench3D * Inertia_HUB21 = sys.Inertia_Wrench("HUB21");
	Wrench3D * Inertia_WH21 = sys.Inertia_Wrench("WH21");

// 	Wrench3D * Inertia_Aarm31 = sys.Inertia_Wrench("Aarm31");
// 	Wrench3D * Inertia_LS31 = sys.Inertia_Wrench("LS31");
// 	Wrench3D * Inertia_SA31 = sys.Inertia_Wrench("SA31");
// 	Wrench3D * Inertia_SA32 = sys.Inertia_Wrench("SA32");
// 	Wrench3D * Inertia_TR31 = sys.Inertia_Wrench("TR31");
// 	Wrench3D * Inertia_HUB31 = sys.Inertia_Wrench("HUB31");
	Wrench3D * Inertia_WH31 = sys.Inertia_Wrench("WH31");

// 	Wrench3D * Inertia_Aarm41 = sys.Inertia_Wrench("Aarm41");
// 	Wrench3D * Inertia_LS41 = sys.Inertia_Wrench("LS41");
// 	Wrench3D * Inertia_SA41 = sys.Inertia_Wrench("SA41");
// 	Wrench3D * Inertia_SA42 = sys.Inertia_Wrench("SA42");
// 	Wrench3D * Inertia_TR41 = sys.Inertia_Wrench("TR41");
// 	Wrench3D * Inertia_HUB41 = sys.Inertia_Wrench("HUB41");
	Wrench3D * Inertia_WH41 = sys.Inertia_Wrench("WH41");



cout << "1st" << endl;


	//	Constitutive
// 	Wrench3D * Constitutive_LS11_AC = sys.new_Wrench3D ( "Constitutive_LS11_AC", FK_LS11, MK_LS11 , E12 , LS11 , "Constitutive") ;
// 	Wrench3D * Constitutive_LS12_REAC = sys.new_Wrench3D ( "Constitutive_LS12_REAC", -FK_LS11, -MK_LS11 , E12 , Chassi , "Constitutive") ;

// 	Wrench3D * Constitutive_SA11_AC = sys.new_Wrench3D ( "Constitutive_SA11_AC", FV_SA11, MV_SA11, E14 , SA11 , "Constitutive") ;
// 	Wrench3D * Constitutive_SA11_REAC = sys.new_Wrench3D ( "Constitutive_SA11_REAC", -FV_SA11, -MV_SA11, E14 , SA12 , "Constitutive") ;

// 	Wrench3D * Constitutive_LS21_AC = sys.new_Wrench3D ( "Constitutive_LS21_AC", FK_LS21, MK_LS21 , E22 , LS21 , "Constitutive") ;
// 	Wrench3D * Constitutive_LS22_REAC = sys.new_Wrench3D ( "Constitutive_LS22_REAC", -FK_LS21, -MK_LS21 , E22 , Chassi , "Constitutive") ;

// 	Wrench3D * Constitutive_SA21_AC = sys.new_Wrench3D ( "Constitutive_SA21_AC", FV_SA21, MV_SA21, E24 , SA21 , "Constitutive") ;
// 	Wrench3D * Constitutive_SA21_REAC = sys.new_Wrench3D ( "Constitutive_SA21_REAC", -FV_SA21, -MV_SA21, E24 , SA22 , "Constitutive") ;

	Wrench3D * Constitutive_LS31_AC = sys.new_Wrench3D ( "Constitutive_LS31_AC", FK_LS31, MK_LS31 , E32 , LS31 , "Constitutive") ;
	Wrench3D * Constitutive_LS32_REAC = sys.new_Wrench3D ( "Constitutive_LS32_REAC", -FK_LS31, -MK_LS31 , E32 , Chassi , "Constitutive") ;

// 	Wrench3D * Constitutive_SA31_AC = sys.new_Wrench3D ( "Constitutive_SA31_AC", FV_SA31, MV_SA31, E34 , SA31 , "Constitutive") ;
// 	Wrench3D * Constitutive_SA31_REAC = sys.new_Wrench3D ( "Constitutive_SA31_REAC", -FV_SA31, -MV_SA31, E34 , SA32 , "Constitutive") ;

	Wrench3D * Constitutive_LS41_AC = sys.new_Wrench3D ( "Constitutive_LS41_AC", FK_LS41, MK_LS41 , E42 , LS41 , "Constitutive") ;
	Wrench3D * Constitutive_LS42_REAC = sys.new_Wrench3D ( "Constitutive_LS42_REAC", -FK_LS41, -MK_LS41 , E42 , Chassi , "Constitutive") ;

// 	Wrench3D * Constitutive_SA41_AC = sys.new_Wrench3D ( "Constitutive_SA41_AC", FV_SA41, MV_SA41, E44 , SA41 , "Constitutive") ;
// 	Wrench3D * Constitutive_SA41_REAC = sys.new_Wrench3D ( "Constitutive_SA41_REAC", -FV_SA41, -MV_SA41, E44 , SA42 , "Constitutive") ;

// 	Wrench3D * WGround1 = sys.new_Wrench3D ( "WGround1", FGround1, MGround1, P1 , WH11 , "Constitutive") ;
// 	Wrench3D * WGround2 = sys.new_Wrench3D ( "WGround2", FGround2, MGround2, P2 , WH21 , "Constitutive") ;
// 	Wrench3D * WGround3 = sys.new_Wrench3D ( "WGround3", FGround3, MGround3, P3 , WH31 , "Constitutive") ;
// 	Wrench3D * WGround4 = sys.new_Wrench3D ( "WGround4", FGround4, MGround4, P4 , WH41 , "Constitutive") ;

	//	External
// ************************************************************************************************
// 	JOint UNknowns
// 	
cout << "10nd" << endl;

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
    symbol_numeric lambda19 = *sys.new_Joint_Unknown("lambda19");
    symbol_numeric lambda20 = *sys.new_Joint_Unknown("lambda20");    
    symbol_numeric lambda21 = *sys.new_Joint_Unknown("lambda21");
    symbol_numeric lambda22 = *sys.new_Joint_Unknown("lambda22");
    symbol_numeric lambda23 = *sys.new_Joint_Unknown("lambda23");
    symbol_numeric lambda24 = *sys.new_Joint_Unknown("lambda24");
    symbol_numeric lambda25 = *sys.new_Joint_Unknown("lambda25");
    symbol_numeric lambda26 = *sys.new_Joint_Unknown("lambda26");
    symbol_numeric lambda27 = *sys.new_Joint_Unknown("lambda27");
    symbol_numeric lambda28 = *sys.new_Joint_Unknown("lambda28");
    symbol_numeric lambda29 = *sys.new_Joint_Unknown("lambda29");
    symbol_numeric lambda30 = *sys.new_Joint_Unknown("lambda30");
    symbol_numeric lambda31 = *sys.new_Joint_Unknown("lambda31");
    symbol_numeric lambda32 = *sys.new_Joint_Unknown("lambda32");
    symbol_numeric lambda33 = *sys.new_Joint_Unknown("lambda33");
    symbol_numeric lambda34 = *sys.new_Joint_Unknown("lambda34");
    symbol_numeric lambda35 = *sys.new_Joint_Unknown("lambda35");
    symbol_numeric lambda36 = *sys.new_Joint_Unknown("lambda36");
    symbol_numeric lambda37 = *sys.new_Joint_Unknown("lambda37");
    symbol_numeric lambda38 = *sys.new_Joint_Unknown("lambda38");  
    symbol_numeric lambda39 = *sys.new_Joint_Unknown("lambda39");
    symbol_numeric lambda40 = *sys.new_Joint_Unknown("lambda40");
    symbol_numeric lambda41  = *sys.new_Joint_Unknown("lambda41");
    symbol_numeric lambda42  = *sys.new_Joint_Unknown("lambda42");
    symbol_numeric lambda43  = *sys.new_Joint_Unknown("lambda43");
    symbol_numeric lambda44  = *sys.new_Joint_Unknown("lambda44");
    symbol_numeric lambda45  = *sys.new_Joint_Unknown("lambda45");
    symbol_numeric lambda46  = *sys.new_Joint_Unknown("lambda46");
    symbol_numeric lambda47  = *sys.new_Joint_Unknown("lambda47");
    symbol_numeric lambda48  = *sys.new_Joint_Unknown("lambda48");
//     symbol_numeric lambda49  = *sys.new_Joint_Unknown("lambda49");
//     symbol_numeric lambda50 = *sys.new_Joint_Unknown("lambda50");
//     symbol_numeric lambda51 = *sys.new_Joint_Unknown("lambda51");
//     symbol_numeric lambda52 = *sys.new_Joint_Unknown("lambda52");




// ************************************************************************************************
// 	Vectors needed to take diferent Jacobians
// ************************************************************************************************
	cout << "9nd" << endl;
	cout << "Vectors needed to take diferent Jacobians" << endl;

	Matrix q = sys.Coordinates();
	Matrix dq = sys.Velocities();
	Matrix ddq = sys.Accelerations();
	Matrix epsilon = sys.Joint_Unknowns();
	Matrix pars = sys.Parameters();
	Matrix inps = sys.Inputs();
	Matrix unks = sys.Joint_Unknowns();

// ************************************************************************************************
// 	 Kinematic Equations 
// ************************************************************************************************
	cout << "Kinematic Equations" << endl;
cout << "8nd" << endl;
	
	Vector3D eq1 = O_A01Chassi+A01_B11AARM+B11_E11AARM-O_C11HUB-C11_D11HUB;
	Vector3D eq2 = O_A01Chassi+A01_B12LS+B12_E12LS-O_C11HUB-C11_D12HUB;
	Vector3D eq3 = O_A01Chassi+A01_B15TR+B15_B14TR+B14_E16TR-O_C11HUB-C11_D13HUB;
	Vector3D eq4 = A01_B11AARM+B11_E11AARM+E11_E112AARM-A01_B13SA-B13_E13SA-E13_E15SA;

	Vector3D eq5 = O_A01Chassi+A01_B21AARM+B21_E21AARM-O_C21HUB-C21_D21HUB;
	Vector3D eq6 = O_A01Chassi+A01_B22LS+B22_E22LS-O_C21HUB-C21_D22HUB;
	Vector3D eq7 = O_A01Chassi+A01_B15TR+B15_B24TR+B24_E26TR-O_C21HUB-C21_D23HUB;
	Vector3D eq8 = A01_B21AARM+B21_E21AARM+E21_E212AARM-A01_B23SA-B23_E23SA-E23_E25SA;

	Vector3D eq9 = O_A01Chassi+A01_B31AARM+B31_E31AARM-O_C31HUB-C31_D31HUB;
	Vector3D eq10 = O_A01Chassi+A01_B32LS+B32_E32LS-O_C31HUB-C31_D32HUB;
	Vector3D eq11 = O_A01Chassi+A01_B35TR+B35_B34TR+B34_E36TR-O_C31HUB-C31_D33HUB;
	Vector3D eq12 = A01_B31AARM+B31_E31AARM+E31_E312AARM-A01_B33SA-B33_E33SA-E33_E35SA;

	Vector3D eq13 = O_A01Chassi+A01_B41AARM+B41_E41AARM-O_C41HUB-C41_D41HUB;
	Vector3D eq14 = O_A01Chassi+A01_B42LS+B42_E42LS-O_C41HUB-C41_D42HUB;
	Vector3D eq15 = O_A01Chassi+A01_B45TR+B45_B44TR+B44_E46TR-O_C41HUB-C41_D43HUB;
	Vector3D eq16 = A01_B41AARM+B41_E41AARM+E41_E412AARM-A01_B43SA-B43_E43SA-E43_E45SA;

cout << "7nd" << endl;
	Matrix Phi(48,1);
	//Matrix dPhiNH(0,1);
    //    Phi(0,0)=pow(B13_E13SA*B13_E13SA,0.5)-L111;
	Phi(0,0)=eq1(0,0);
	Phi(1,0)=eq1(1,0);
	Phi(2,0)=eq1(2,0);
	Phi(3,0)=eq2(0,0);
	Phi(4,0)=eq2(1,0);
	Phi(5,0)=eq2(2,0);
	Phi(6,0)=eq3(0,0);
	Phi(7,0)=eq3(1,0);
	Phi(8,0)=eq3(2,0);
	Phi(9,0)=eq4(0,0);
	Phi(10,0)=eq4(1,0);
	Phi(11,0)=eq4(2,0);
	//Phi(13,0)=pow(B23_E23SA*B23_E23SA,0.5)-L211;
	Phi(12,0)=eq5(0,0);
	Phi(13,0)=eq5(1,0);
	Phi(14,0)=eq5(2,0);
	Phi(15,0)=eq6(0,0);
	Phi(16,0)=eq6(1,0);
	Phi(17,0)=eq6(2,0);
	Phi(18,0)=eq7(0,0);
	Phi(19,0)=eq7(1,0);
	Phi(20,0)=eq7(2,0);
	Phi(21,0)=eq8(0,0);
	Phi(22,0)=eq8(1,0);
	Phi(23,0)=eq8(2,0);
	//Phi(26,0)=pow(B33_E33SA*B33_E33SA,0.5)-L311;
	Phi(24,0)=eq9(0,0);
	Phi(25,0)=eq9(1,0);
	Phi(26,0)=eq9(2,0);
	Phi(27,0)=eq10(0,0);
	Phi(28,0)=eq10(1,0);
	Phi(29,0)=eq10(2,0);
	Phi(30,0)=eq11(0,0);
	Phi(31,0)=eq11(1,0);
	Phi(32,0)=eq11(2,0);
	Phi(33,0)=eq12(0,0);
	Phi(34,0)=eq12(1,0);
	Phi(35,0)=eq12(2,0);
	//Phi39,0)=pow(B43_E43SA*B43_E43SA,0.5)-L411;
	Phi(36,0)=eq13(0,0);
	Phi(37,0)=eq13(1,0);
	Phi(38,0)=eq13(2,0);
	Phi(39,0)=eq14(0,0);
	Phi(40,0)=eq14(1,0);
	Phi(41,0)=eq14(2,0);
	Phi(42,0)=eq15(0,0);
	Phi(43,0)=eq15(1,0);
	Phi(44,0)=eq15(2,0);
	Phi(45,0)=eq16(0,0);
	Phi(46,0)=eq16(1,0);
	Phi(47,0)=eq16(2,0);
	//Phi(48,0)=tetha-tetha_0


// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************
cout << "6nd" << endl;
	cout << "Dynamic Equations" << endl;

	Matrix Dynamic_Equations = sys.GenForceSys("ALL");
	//cout<<Dynamic_Equations<<endl;

// ************************************************************************************************
// 	Output Vector
// ************************************************************************************************
cout << "5" << endl;
	cout << "Output Vector" << endl;

	Matrix Output(1,1);
	Output(0,0)=0;
	sys.new_Matrix("Output",Output);

// ************************************************************************************************
// 	Energy Equations
// ************************************************************************************************
cout << "3rd" << endl;
	cout << "Energy Equations" << endl;

	Matrix Energy(1,1);
	Energy(0,0)=0;
	sys.new_Matrix("Energy",Energy);
cout << "4th" << endl;

// ************************************************************************************************
// 	Matrix Calculation 	
// ************************************************************************************************
	
        cout << "Matrix Calculation" << endl;
      //  sys.Matrix_Calculation(coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);
	sys.Matrix_Calculation(Phi, coord_indep_init, vel_indep_init, Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);


// ************************************************************************************************
// 	Export C code for Direct Simulation 
// ************************************************************************************************

	cout << "Export C code for Direct Simulation " << endl;

        sys.export_Dynamic_Simulation(sys, ORDER , MAPLE, PROBLEM_TYPE);
	//sys.export_Dynamic_Simulation_Common_and_Kinematics(sys, ORDER , MAPLE);
	//sys.export_Dynamic_Simulation_q(sys, ORDER , MAPLE);
	//sys.export_Dynamic_Simulation_z(sys, ORDER , MAPLE);

	sys.export_Output(sys, ORDER , MAPLE);
        
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

	//cout << "Export State File" << endl;

    	lst state;

    	state =  L01, L02, L03, *dL01, *dL02, *dL03, *ddL01, *ddL02, *ddL03, alpha01, alpha02, alpha03, betha11, L111, /*L18,*/ betha12, betha15, betha16, betha13, betha14, alpha11, alpha12, alpha13, alpha14, L11, L12, L13, betha21, betha22, betha25, betha26, betha23, betha24, L211, L21, L22, L23, alpha21, alpha22, alpha23, alpha24, betha31, betha32, betha35, betha36, betha33, betha34, alpha31, alpha32, alpha33, alpha34, L311, L31, L32, L33, betha41, betha42, betha45, betha46, betha43, betha44, alpha41, alpha42, alpha43, alpha44, L411, L41, L42, L43, *dalpha01, *dalpha02, *dalpha03, *dbetha11, *dL111, /**dL18,*/ *dbetha12, *dbetha15, *dbetha16, *dbetha13, *dbetha14, *dalpha11, *dalpha12, *dalpha13, *dalpha14, *dL11, *dL12, *dL13, *dbetha21, *dbetha22, *dbetha25, *dbetha26, *dbetha23, *dbetha24, *dL211, *dL21, *dL22, *dL23, *dalpha21, *dalpha22, *dalpha23, *dalpha24, *dbetha31, *dbetha32, *dbetha35, *dbetha36, *dbetha33, *dbetha34, *dalpha31, *dalpha32, *dalpha33, *dalpha34, *dL311, *dL31, *dL32, *dL33, *
dbetha41, *dbetha42, *dbetha45, *dbetha46, *dbetha43, *dbetha44, *dalpha41, *dalpha42, *dalpha43, *dalpha44, *dL411, *dL41, *dL42, *dL43, *ddalpha01, *ddalpha02, *ddalpha03, *ddbetha11, *ddL111,/* *ddL18,*/ *ddbetha15, *ddbetha16, *ddbetha13, *ddbetha14, *ddalpha11, *ddalpha12, *ddalpha13, *ddalpha14, *ddL11, *ddL12, *ddL13, *ddbetha21, *ddbetha22, *ddbetha25, *ddbetha26, *ddbetha23, *ddbetha24, *ddL211, *ddL21, *ddL22, *ddL23, *ddalpha21, *ddalpha22, *ddalpha23, *ddalpha24, *ddbetha31, *ddbetha32, *ddbetha35, *ddbetha36, *ddbetha33, *ddbetha34, *ddalpha31, *ddalpha32, *ddalpha33, *ddalpha34, *ddL311, *ddL31, *ddL32, *ddL33, *ddbetha41, *ddbetha42, *ddbetha45, *ddbetha46, *ddbetha43, *ddbetha44, *ddalpha41, *ddalpha42, *ddalpha43, *ddalpha44, *ddL411, *ddL41, *ddL42, *ddL43;

/* L01, L02, L03,, *dL01, *dL02, *dL03, *ddL01, *ddL02, *ddL03
, *ddL19, *ddbetha12, *dbetha12 , *dL19, L19,, L29, L28, L21, L22, L23 L39, L38, L49, L48, *dbetha11, *dalpha11, *dalpha12, *dalpha13, *dalpha14, *dL11, *dL12, *dL13, *dL01, *dL02, *dL03, *dalpha01, *dalpha02, *dalpha03, *dL29, *dL28, *dL39, *dL38, *dL49, *dL48, *ddL01, *ddL02, *ddL03, *ddalpha01, *ddalpha02, *ddalpha03, *ddbetha11, *ddalpha11, *ddalpha12, *ddalpha13, *ddalpha14, *ddL11, *ddL12, *ddL13, *ddL29, *ddL28, *ddL39, *ddL38, *ddL49, *ddL48;        * , */

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


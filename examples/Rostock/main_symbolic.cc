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
cout << "*                   Rostock                    *" << endl;
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
//	Coordinate definition
// ************************************************************************************************

	symbol_numeric rho1 = *sys.new_Coordinate("rho1","drho1","ddrho1", 0.4 , 0.0 , 0.0);
	symbol_numeric rho2 = *sys.new_Coordinate("rho2","drho2","ddrho2", 0.4 , 0.0 , 0.0);
	symbol_numeric rho3 = *sys.new_Coordinate("rho3","drho3","ddrho3", 0.4 , 0.0 , 0.0);

	symbol_numeric phi1 = *sys.new_Coordinate("phi1","dphi1","ddphi1", 0.0 , 0.0 , 0.0);
	symbol_numeric phi2 = *sys.new_Coordinate("phi2","dphi2","ddphi2", 0.0 , 0.0 , 0.0);
	symbol_numeric phi3 = *sys.new_Coordinate("phi3","dphi3","ddphi3", 0.0 , 0.0 , 0.0);

	symbol_numeric theta1 = *sys.new_Coordinate("theta1","dtheta1","ddtheta1", 0.0, 0.0 , 0.0);
	symbol_numeric theta2 = *sys.new_Coordinate("theta2","dtheta2","ddtheta2", 0.0, 0.0 , 0.0);
	symbol_numeric theta3 = *sys.new_Coordinate("theta3","dtheta3","ddtheta3", 0.0, 0.0 , 0.0);

	symbol_numeric xp = *sys.new_Coordinate("xp","dxp","ddxp", 0.0, 0.0 , 0.0);
	symbol_numeric yp = *sys.new_Coordinate("yp","dyp","ddyp", 0.0, 0.0 , 0.0);
	symbol_numeric zp = *sys.new_Coordinate("zp","dzp","ddzp", 0.1, 0.0 , 0.0);

      
	symbol_numeric *drho1=sys.get_Velocity("drho1");
	symbol_numeric *drho2=sys.get_Velocity("drho2");
	symbol_numeric *drho3=sys.get_Velocity("drho3");

	symbol_numeric *dphi1=sys.get_Velocity("dphi1");
	symbol_numeric *dphi2=sys.get_Velocity("dphi2");
	symbol_numeric *dphi3=sys.get_Velocity("dphi3");

	symbol_numeric *dtheta1=sys.get_Velocity("dtheta1");
	symbol_numeric *dtheta2=sys.get_Velocity("dtheta2");
	symbol_numeric *dtheta3=sys.get_Velocity("dtheta3");

	symbol_numeric *dxp=sys.get_Velocity("dxp");
	symbol_numeric *dyp=sys.get_Velocity("dyp");
	symbol_numeric *dzp=sys.get_Velocity("dzp");

	symbol_numeric *ddrho1=sys.get_Acceleration("ddrho1");
	symbol_numeric *ddrho2=sys.get_Acceleration("ddrho2");
	symbol_numeric *ddrho3=sys.get_Acceleration("ddrho3");

	symbol_numeric *ddphi1=sys.get_Acceleration("ddphi1");
	symbol_numeric *ddphi2=sys.get_Acceleration("ddphi2");
	symbol_numeric *ddphi3=sys.get_Acceleration("ddphi3");

	symbol_numeric *ddtheta1=sys.get_Acceleration("ddtheta1");
	symbol_numeric *ddtheta2=sys.get_Acceleration("ddtheta2");
	symbol_numeric *ddtheta3=sys.get_Acceleration("ddtheta3");

	symbol_numeric *ddxp=sys.get_Acceleration("ddxp");
	symbol_numeric *ddyp=sys.get_Acceleration("ddyp");
	symbol_numeric *ddzp=sys.get_Acceleration("ddzp");

	lst coord_indep_init;
	lst vel_indep_init;
	
// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	symbol_numeric R  = *sys.new_Parameter("R",0.15);
	symbol_numeric r  = *sys.new_Parameter("r",0.03);
	symbol_numeric l1 = *sys.new_Parameter("l1",0.25);
	symbol_numeric l2 = *sys.new_Parameter("l2",0.25);
	symbol_numeric l3 = *sys.new_Parameter("l3",0.25);
	symbol_numeric alpha = *sys.new_Parameter("alpha",2.09439510239); //120º=2/3*pi
	symbol_numeric beta = *sys.new_Parameter("beta",-2.09439510239); 

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

 	sys.new_Base("BB1c","xyz",0,0,1,alpha);
	sys.new_Base("BB2c","xyz",0,0,1,beta);
	sys.new_Base("BB3c","xyz",0,0,1,0);

	sys.new_Base("BB1a","BB1c",1,0,0,phi1);
	sys.new_Base("BB2a","BB2c",1,0,0,phi2);
	sys.new_Base("BB3a","BB3c",1,0,0,phi3);

	sys.new_Base("BB1","BB1a",0,0,1,theta1);
	sys.new_Base("BB2","BB2a",0,0,1,theta2);
	sys.new_Base("BB3","BB3a",0,0,1,theta3);
cout << "base = "<< sys.Rotation_Matrix(sys.get_Base("BB3a"),sys.get_Base("BB3"))<<endl;

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	Vector3D O_A1 = *sys.new_Vector3D("O_A1",0,R,0,"BB1c"); 
	Vector3D O_A2 = *sys.new_Vector3D("O_A2",0,R,0,"BB2c"); 
	Vector3D O_A3 = *sys.new_Vector3D("O_A3",0,R,0,"BB3c");

	Vector3D A1_B1 = *sys.new_Vector3D("A1_B1",0,0,rho1,"BB1c"); 
	Vector3D A2_B2 = *sys.new_Vector3D("A2_B2",0,0,rho2,"BB2c"); 
	Vector3D A3_B3 = *sys.new_Vector3D("A3_B3",0,0,rho3,"BB3c"); 

	Vector3D B1_C1 = *sys.new_Vector3D("B1_C1",0,-l1,0,"BB1"); 
	Vector3D B2_C2 = *sys.new_Vector3D("B2_C2",0,-l2,0,"BB2"); 
	Vector3D B3_C3 = *sys.new_Vector3D("B3_C3",0,-l3,0,"BB3");

	Vector3D P_C1 = *sys.new_Vector3D("P_C1",0,r,0,"BB1c"); 
	Vector3D P_C2 = *sys.new_Vector3D("P_C2",0,r,0,"BB2c"); 
	Vector3D P_C3 = *sys.new_Vector3D("P_C3",0,r,0,"BB3c"); 

	Vector3D O_P = *sys.new_Vector3D("O_P",xp,yp,zp,"xyz");

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * A1 = sys.new_Point("A1","O",&O_A1);
	Point * A2 = sys.new_Point("A2","O",&O_A2);
	Point * A3 = sys.new_Point("A3","O",&O_A3);

	Point * B1 = sys.new_Point("B1","A1",&A1_B1);
	Point * B2 = sys.new_Point("B2","A2",&A2_B2);
	Point * B3 = sys.new_Point("B3","A3",&A3_B3);

	Point * C1 = sys.new_Point("C1","B1",&B1_C1);
	Point * C2 = sys.new_Point("C2","B2",&B2_C2);
	Point * C3 = sys.new_Point("C3","B3",&B3_C3);

	Point * P = sys.new_Point("P","O",&O_P);


// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Viscosity
       	symbol_numeric  Cvis = *sys.new_Parameter("Cvis",0.8);

	// Dynamic Parameters of Carrier (all three carriers are identical)

    	symbol_numeric  mCarrier = *sys.new_Parameter("mCarrier",1.0);

	symbol_numeric  mxCarrier = *sys.new_Parameter("mxCarrier",0.0);
    	symbol_numeric  myCarrier = *sys.new_Parameter("myCarrier",0.0);
	symbol_numeric  mzCarrier = *sys.new_Parameter("mzCarrier",0.0);

    	symbol_numeric  IxxCarrier = *sys.new_Parameter("IxxCarrier",1.0);
	symbol_numeric  IxyCarrier = *sys.new_Parameter("IxyCarrier",0.0);
    	symbol_numeric  IyyCarrier = *sys.new_Parameter("IyyCarrier",1.0);
	symbol_numeric  IxzCarrier = *sys.new_Parameter("IxzCarrier",0.0);
    	symbol_numeric  IzzCarrier = *sys.new_Parameter("IzzCarrier",1.0);
	symbol_numeric  IyzCarrier = *sys.new_Parameter("IyzCarrier",0.0);

	// Dynamic Parameters of Rod 1

    	symbol_numeric  mRod1 = *sys.new_Parameter("mRod1",1.0);

	symbol_numeric  mxRod1 = *sys.new_Parameter("mxRod1",0.0);
    	symbol_numeric  myRod1 = *sys.new_Parameter("myRod1",0.0);
	symbol_numeric  mzRod1 = *sys.new_Parameter("mzRod1",0.0);

    	symbol_numeric  IxxRod1 = *sys.new_Parameter("IxxRod1",1.0);
	symbol_numeric  IxyRod1 = *sys.new_Parameter("IxyRod1",0.0);
    	symbol_numeric  IyyRod1 = *sys.new_Parameter("IyyRod1",5.0);
	symbol_numeric  IxzRod1 = *sys.new_Parameter("IxzRod1",0.0);
    	symbol_numeric  IzzRod1 = *sys.new_Parameter("IzzRod1",1.0);
	symbol_numeric  IyzRod1 = *sys.new_Parameter("IyzRod1",0.0);

	// Dynamic Parameters of Rod 2

    	symbol_numeric  mRod2 = *sys.new_Parameter("mRod2",1.0);

	symbol_numeric  mxRod2 = *sys.new_Parameter("mxRod2",0.0);
    	symbol_numeric  myRod2 = *sys.new_Parameter("myRod2",0.0);
	symbol_numeric  mzRod2 = *sys.new_Parameter("mzRod2",0.0);

    symbol_numeric  IxxRod2 = *sys.new_Parameter("IxxRod2",1.0);
	symbol_numeric  IxyRod2 = *sys.new_Parameter("IxyRod2",0.0);
    symbol_numeric  IyyRod2 = *sys.new_Parameter("IyyRod2",1.0);
	symbol_numeric  IxzRod2 = *sys.new_Parameter("IxzRod2",0.0);
    symbol_numeric  IzzRod2 = *sys.new_Parameter("IzzRod2",1.0);
	symbol_numeric  IyzRod2 = *sys.new_Parameter("IyzRod2",0.0);

	// Dynamic Parameters of Rod 3

    symbol_numeric  mRod3 = *sys.new_Parameter("mRod3",1.0);

	symbol_numeric  mxRod3 = *sys.new_Parameter("mxRod3",0.0);
    symbol_numeric  myRod3 = *sys.new_Parameter("myRod3",0.0);
	symbol_numeric  mzRod3 = *sys.new_Parameter("mzRod3",0.0);

    symbol_numeric  IxxRod3 = *sys.new_Parameter("IxxRod3",1.0);
	symbol_numeric  IxyRod3 = *sys.new_Parameter("IxyRod3",0.0);
    symbol_numeric  IyyRod3 = *sys.new_Parameter("IyyRod3",1.0);
	symbol_numeric  IxzRod3 = *sys.new_Parameter("IxzRod3",0.0);
    symbol_numeric  IzzRod3 = *sys.new_Parameter("IzzRod3",1.0);
	symbol_numeric  IyzRod3 = *sys.new_Parameter("IyzRod3",0.0);

	// Dynamic Parameters of Header or Platform

    symbol_numeric  mHeader = *sys.new_Parameter("mHeader",1.0);

	symbol_numeric  mxHeader = *sys.new_Parameter("mxHeader",0.0);
    symbol_numeric  myHeader = *sys.new_Parameter("myHeader",0.0);
	symbol_numeric  mzHeader = *sys.new_Parameter("mzHeader",0.0);

    symbol_numeric  IxxHeader = *sys.new_Parameter("IxxHeader",1.0);
	symbol_numeric  IxyHeader = *sys.new_Parameter("IxyHeader",0.0);
    symbol_numeric  IyyHeader = *sys.new_Parameter("IyyHeader",1.0);
	symbol_numeric  IxzHeader = *sys.new_Parameter("IxzHeader",0.0);
    symbol_numeric  IzzHeader = *sys.new_Parameter("IzzHeader",1.0);
	symbol_numeric  IyzHeader = *sys.new_Parameter("IyzHeader",0.0);

	//Gravity Center Vectors    

	Vector3D B1_GCarrier1= *sys.new_Vector3D("B1_GCarrier1",mxCarrier/mCarrier,myCarrier/mCarrier,mzCarrier/mCarrier,"BB1c");
	Vector3D B2_GCarrier2= *sys.new_Vector3D("B2_GCarrier2",mxCarrier/mCarrier,myCarrier/mCarrier,mzCarrier/mCarrier,"BB2c");
	Vector3D B3_GCarrier3= *sys.new_Vector3D("B3_GCarrier3",mxCarrier/mCarrier,myCarrier/mCarrier,mzCarrier/mCarrier,"BB3c");
	
	Vector3D B1_GRod1= *sys.new_Vector3D("B1_GRod1",0,-l1/2,0,"BB1");
	Vector3D B2_GRod2= *sys.new_Vector3D("B2_GRod2",0,-l2/2,0,"BB2");
	Vector3D B3_GRod3= *sys.new_Vector3D("B3_GRod3",0,-l3/2,0,"BB3");

	Vector3D P_GHeader= *sys.new_Vector3D("P_GHeader",0,0,0,"xyz");

	//Inertia Tensors		
	
    Tensor3D ICarrier1 = *sys.new_Tensor3D("ICarrier1",(ex)IxxCarrier,(ex)IxyCarrier,(ex)IxzCarrier,(ex)IxyCarrier,(ex)IyyCarrier,(ex)IyzCarrier,(ex)IxzCarrier,(ex)IyzCarrier,(ex)IzzCarrier,"BB1c");

	Tensor3D ICarrier2 = *sys.new_Tensor3D("ICarrier2",(ex)IxxCarrier,(ex)IxyCarrier,(ex)IxzCarrier,(ex)IxyCarrier,(ex)IyyCarrier,(ex)IyzCarrier,(ex)IxzCarrier,(ex)IyzCarrier,(ex)IzzCarrier,"BB2c"); 

	Tensor3D ICarrier3 = *sys.new_Tensor3D("ICarrier3",(ex)IxxCarrier,(ex)IxyCarrier,(ex)IxzCarrier,(ex)IxyCarrier,(ex)IyyCarrier,(ex)IyzCarrier,(ex)IxzCarrier,(ex)IyzCarrier,(ex)IzzCarrier,"BB3c"); 


	Tensor3D IRod1 = *sys.new_Tensor3D("IRod1",(ex)IxxRod1,(ex)IxyRod1,(ex)IxzRod1,(ex)IxyRod1,(ex)IyyRod1,(ex)IyzRod1,(ex)IxzRod1,(ex)IyzRod1,(ex)IzzRod1,"BB1");

	Tensor3D IRod2 = *sys.new_Tensor3D("IRod2",(ex)IxxRod2,(ex)IxyRod2,(ex)IxzRod2,(ex)IxyRod2,(ex)IyyRod2,(ex)IyzRod2,(ex)IxzRod2,(ex)IyzRod2,(ex)IzzRod2,"BB2");

	Tensor3D IRod3 = *sys.new_Tensor3D("IRod3",(ex)IxxRod3,(ex)IxyRod3,(ex)IxzRod3,(ex)IxyRod3,(ex)IyyRod3,(ex)IyzRod3,(ex)IxzRod3,(ex)IyzRod3,(ex)IzzRod3,"BB3");

	Tensor3D IHeader = *sys.new_Tensor3D("IHeader",(ex)IxxHeader,(ex)IxyHeader,(ex)IxzHeader,(ex)IxyHeader,(ex)IyyHeader,(ex)IyzHeader,(ex)IxzHeader,(ex)IyzHeader,(ex)IzzHeader,"xyz");

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Carrier1 = sys.new_Frame("Fra_Carrier1","B1","BB1c");
	Frame * Fra_Carrier2 = sys.new_Frame("Fra_Carrier2","B2","BB2c");
	Frame * Fra_Carrier3 = sys.new_Frame("Fra_Carrier3","B3","BB3c");

	Frame * Fra_Rod1 = sys.new_Frame("Fra_Rod1","B1","BB1");
	Frame * Fra_Rod2 = sys.new_Frame("Fra_Rod2","B2","BB2");
	Frame * Fra_Rod3 = sys.new_Frame("Fra_Rod3","B3","BB3");

	Frame * Fra_Header = sys.new_Frame("Fra_Header","P","xyz");

// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	Solid * Carrier1 = sys.new_Solid("Carrier1","B1","BB1c","mCarrier","B1_GCarrier1","ICarrier1");
	Solid * Carrier2 = sys.new_Solid("Carrier2","B2","BB2c","mCarrier","B2_GCarrier2","ICarrier2");
	Solid * Carrier3 = sys.new_Solid("Carrier3","B3","BB3c","mCarrier","B3_GCarrier3","ICarrier3");

	Solid * Rod1 = sys.new_Solid("Rod1","B1","BB1","mRod1","B1_GRod1","IRod1");
	Solid * Rod2 = sys.new_Solid("Rod2","B2","BB2","mRod2","B2_GRod2","IRod2");
	Solid * Rod3 = sys.new_Solid("Rod3","B3","BB3","mRod3","B3_GRod3","IRod3");

	Solid * Header = sys.new_Solid("Header","P","xyz","mHeader","P_GHeader","IHeader");



// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

	Drawing3D * Ground3D = sys.new_Drawing3D("Ground3D", "O", "xyz","./solids/body.osgt");

	Drawing3D * Carrier13D = sys.new_Drawing3D("Carrier13D", Carrier1,"./solids/carriage.osgt");
	Drawing3D * Carrier23D = sys.new_Drawing3D("Carrier23D", Carrier2,"./solids/carriage.osgt");
	Drawing3D * Carrier33D = sys.new_Drawing3D("Carrier33D", Carrier3,"./solids/carriage.osgt");

	Drawing3D * Rod13D = sys.new_Drawing3D("Rod13D", Rod1,"./solids/rod.osgt");
	Drawing3D * Rod23D = sys.new_Drawing3D("Rod23D", Rod2,"./solids/rod.osgt");
	Drawing3D * Rod33D = sys.new_Drawing3D("Rod33D", Rod3,"./solids/rod.osgt");

	Drawing3D * Header3D = sys.new_Drawing3D("Header3D", Header,"./solids/header.osgt");	
	
        Drawing3D * FraHeader = sys.new_Drawing3D( "FraHeader" , Fra_Header, 0.1 );
        Drawing3D * PointA1 = sys.new_Drawing3D( "PointA1" , A1, 0.05 );
 
	
/*


	//Pruebas	
	//Vector3D O_Prueba= *sys.new_Vector3D("O_Prueba",x,0,0 ,"xyz");
	Vector3D O_Prueba= sys.Position_Vector("O","E");

	Point * Point1 = sys.new_Point("Point1","O",&O_Prueba);	
        Drawing3D * PointPend = sys.new_Drawing3D("PointPend",Point1,0.03);	


        Drawing3D * VectorPrueba = sys.new_Drawing3D("VectorPrueba",&O_Prueba,Point_O);   
        Drawing3D * VectorPend = sys.new_Drawing3D("VectorPend",&OPendulum_GPendulum,E,1.0,0.0,1.0,1.0);   
*/
// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

	cout << "Joint Unknown Definition" << endl;
/*	symbol_numeric lambda1 = *sys.new_Joint_Unknown("lambda1");
	symbol_numeric lambda2 = *sys.new_Joint_Unknown("lambda2");
	symbol_numeric lambda3 = *sys.new_Joint_Unknown("lambda3");
	symbol_numeric lambda4 = *sys.new_Joint_Unknown("lambda4");
	symbol_numeric lambda5 = *sys.new_Joint_Unknown("lambda5");
	symbol_numeric lambda6 = *sys.new_Joint_Unknown("lambda6");
	symbol_numeric lambda7 = *sys.new_Joint_Unknown("lambda7");
	symbol_numeric lambda8 = *sys.new_Joint_Unknown("lambda8");
	symbol_numeric lambda9 = *sys.new_Joint_Unknown("lambda9");
*/

// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

	cout << "Input Vector" << endl;
/*
	symbol_numeric FCarrier1z = *sys.new_Input("FCarrier1z",0.0);
	symbol_numeric FCarrier2z = *sys.new_Input("FCarrier2z",0.0);
	symbol_numeric FCarrier3z = *sys.new_Input("FCarrier3z",0.0);

	Vector3D FCarrier1 = *sys.new_Vector3D("FCarrier",0,0,FCarrier1z,"BB1c");
	Vector3D MCarrier1 = *sys.new_Vector3D("MCarrier",0,0,0, "BB1c");

	Vector3D FCarrier2 = *sys.new_Vector3D("FCarrier2",0,0,FCarrier2z,"BB2c");
	Vector3D MCarrier2 = *sys.new_Vector3D("MCarrier2",0,0,0, "BB2c");

	Vector3D FCarrier3 = *sys.new_Vector3D("FCarrier3",0,0,FCarrier3z,"BB3c");
	Vector3D MCarrier3 = *sys.new_Vector3D("MCarrier3",0,0,0, "BB3c");

	symbol_numeric FBlockx = *sys.new_Input("FBlockx",0.0);
	symbol_numeric MPendulumy = *sys.new_Input("MPendulumy",0.0);

	Vector3D FBlock = *sys.new_Vector3D("FBlock",FBlockx,0,0,"BBlock");
	Vector3D MBlock = *sys.new_Vector3D("MBlock",0,0,0, "BBlock");
	Vector3D FPendulum = *sys.new_Vector3D("FPendulum",0,0,0,"BPendulum");
	Vector3D MPendulum = *sys.new_Vector3D("MPendulum",0,MPendulumy,0, "BPendulum");
*/

// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************
        symbol_numeric xp_0 = *sys.new_Parameter("xp_0",0.0);
        symbol_numeric yp_0 = *sys.new_Parameter("yp_0",0.0);
        symbol_numeric zp_0 = *sys.new_Parameter("zp_0",0.0);
/*
	Vector3D FV_Carrier1 = -Cvis * sys.Velocity_Vector("abs" ,"B1", "Carrier1" );
	Vector3D MV_Carrier1 = *sys.new_Vector3D("MV_Carrier1",0,0,0,"BB1c");

	Vector3D FV_Carrier2 = -Cvis * sys.Velocity_Vector("abs" ,"B2", "Carrier2" );
	Vector3D MV_Carrier2 = *sys.new_Vector3D("MV_Carrier2",0,0,0,"BB2c");

	Vector3D FV_Carrier3 = -Cvis * sys.Velocity_Vector("abs" ,"B1", "Carrier3" );
	Vector3D MV_Carrier3 = *sys.new_Vector3D("MV_Carrier3",0,0,0,"BB3c");
*/
// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * Gravity_Carrier1 = sys.Gravity_Wrench("Carrier1");
	Wrench3D * Gravity_Carrier2 = sys.Gravity_Wrench("Carrier2");
	Wrench3D * Gravity_Carrier3 = sys.Gravity_Wrench("Carrier3");

	Wrench3D * Gravity_Rod1 = sys.Gravity_Wrench("Rod1");
	Wrench3D * Gravity_Rod2 = sys.Gravity_Wrench("Rod2");
	Wrench3D * Gravity_Rod3 = sys.Gravity_Wrench("Rod3");

	Wrench3D * Gravity_Header = sys.Gravity_Wrench("Header");

	//	Inertia
	Wrench3D * Inertia_Carrier1 = sys.Inertia_Wrench("Carrier1");
	Wrench3D * Inertia_Carrier2 = sys.Inertia_Wrench("Carrier2");
	Wrench3D * Inertia_Carrier3 = sys.Inertia_Wrench("Carrier3");

	Wrench3D * Inertia_Rod1 = sys.Inertia_Wrench("Rod1");
	Wrench3D * Inertia_Rod2 = sys.Inertia_Wrench("Rod2");
	Wrench3D * Inertia_Rod3 = sys.Inertia_Wrench("Rod3");

	Wrench3D * Inertia_Header = sys.Inertia_Wrench("Header");
/*
	//	Constitutive
	Wrench3D * Viscosity1 = sys.new_Wrench3D ( "Viscosity1", FV_Carrier1, MV_Carrier1, B1 , Carrier1 , "Constitutive") ;
	Wrench3D * Viscosity2 = sys.new_Wrench3D ( "Viscosity2", FV_Carrier2, MV_Carrier2, B2 , Carrier2 , "Constitutive") ;
	Wrench3D * Viscosity3 = sys.new_Wrench3D ( "Viscosity3", FV_Carrier3, MV_Carrier3, B3 , Carrier3 , "Constitutive") ;

	//	External
	Wrench3D * Carrier1_Impulse = sys.new_Wrench3D ( "Carrier1_Impulse", FCarrier1, MCarrier1, B1 , Carrier1 , "External");
	Wrench3D * Carrier2_Impulse = sys.new_Wrench3D ( "Carrier2_Impulse", FCarrier2, MCarrier2, B2 , Carrier2 , "External");
	Wrench3D * Carrier3_Impulse = sys.new_Wrench3D ( "Carrier3_Impulse", FCarrier3, MCarrier3, B3 , Carrier3 , "External");
*/

// ************************************************************************************************
// 	Vectors needed to take diferent Jacobians
// ************************************************************************************************

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
	//Vector3D O_C1= O_A1 + A1_B1 + B1_C1;
	Vector3D O_C1= sys.Position_Vector("O","C1");
	Vector3D O_C2= sys.Position_Vector("O","C2");
	Vector3D O_C3= sys.Position_Vector("O","C3");
cout << " O_C1= "<< O_C1<<endl;
cout << " O_C2= "<< O_C2<<endl;

	Drawing3D * VectorO_P = sys.new_Drawing3D("VectorO_P",&O_P,Point_O,1.0,0.0,1.0,1.0);

	Drawing3D * VectorO_C1 = sys.new_Drawing3D("VectorO_C1",&O_C1,Point_O,1.0,0.0,1.0,1.0);
	Drawing3D * VectorP_C1 = sys.new_Drawing3D("VectorP_C1",&P_C1,P,1.0,0.0,1.0,1.0);

	Drawing3D * VectorO_C2 = sys.new_Drawing3D("VectorO_C2",&O_C2,Point_O,0.0,0.0,1.0,1.0);
	Drawing3D * VectorP_C2 = sys.new_Drawing3D("VectorP_C2",&P_C2,P,0.0,0.0,1.0,1.0);

	Drawing3D * VectorO_C3 = sys.new_Drawing3D("VectorO_C3",&O_C3,Point_O,0.0,1.0,0.0,1.0);
	Drawing3D * VectorP_C3 = sys.new_Drawing3D("VectorP_C3",&P_C3,P,0.0,1.0,0.0,1.0);

	Matrix Phi(9,1);
	Phi(0,0) = O_C1(0,0) - O_P(0,0) - P_C1(0,0);
	Phi(1,0) = O_C1(1,0) - O_P(1,0) - P_C1(1,0);
	Phi(2,0) = O_C1(2,0) - O_P(2,0) - P_C1(2,0);
	Phi(3,0) = O_C2(0,0) - O_P(0,0) - P_C2(0,0);
	Phi(4,0) = O_C2(1,0) - O_P(1,0) - P_C2(1,0);
	Phi(5,0) = O_C2(2,0) - O_P(2,0) - P_C2(2,0);
	Phi(6,0) = O_C3(0,0) - O_P(0,0) - P_C3(0,0);
	Phi(7,0) = O_C3(1,0) - O_P(1,0) - P_C3(1,0);
	Phi(8,0) = O_C3(2,0) - O_P(2,0) - P_C3(2,0);
cout << Phi << endl;

// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************

	cout << "Dynamic Equations" << endl;

	Matrix Dynamic_Equations = sys.GenForceSys("ALL");


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
	// With restrictions (Phi)        
	//sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);
	// Without restrictions (no Phi)
	sys.Matrix_Calculation(coord_indep_init, vel_indep_init, Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);


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

	cout << "Export State File" << endl;

    	lst state;

    	state = rho1, rho2, rho3, xp, yp, zp, *drho1, *drho2, *drho3, *dxp, *dyp, *dzp, *ddrho1, *ddrho2, *ddrho3, *ddxp, *ddyp, *ddzp;
//   	state = rho1, rho2, rho3, phi1, phi2, phi3, theta1, theta2, theta3, xp, yp, zp, *drho1, *drho2, *drho3, *dphi1, *dphi2, *dphi3, *dtheta1, *dtheta2, *dtheta3, *dxp, *dyp, *dzp, *ddrho1, *ddrho2, *ddrho3, *ddphi1, *ddphi2, *ddphi3, *ddtheta1, *ddtheta2, *ddtheta3, *ddxp, *ddyp, *ddzp;
 //   	state = x , theta, *dx, *dtheta, *ddx, *ddtheta;

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


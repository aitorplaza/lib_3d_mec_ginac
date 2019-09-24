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
//	Coordinate definition Segway
// ************************************************************************************************

	symbol_numeric pi = *sys.new_Parameter("pi",3.14159265358979);
#define PI 3.14159265358979
	symbol_numeric rho1 = *sys.new_Coordinate("rho1","drho1","ddrho1", 0.4 , 0.0 , 0.0);//rho giro plataforma en torno a z
	symbol_numeric rho2 = *sys.new_Coordinate("rho2","drho2","ddrho2", 0.4 , 0.0 , 0.0);
	symbol_numeric rho3 = *sys.new_Coordinate("rho3","drho3","ddrho3", 0.4 , 0.0 , 0.0);

	symbol_numeric phi1 = *sys.new_Coordinate("phi1","dphi1","ddphi1", 0.5 , 0.0 , 0.0);//phi manillar en torno a x
	symbol_numeric phi2 = *sys.new_Coordinate("phi2","dphi2","ddphi2", 0.5 , 0.0 , 0.0);
	symbol_numeric phi3 = *sys.new_Coordinate("phi3","dphi3","ddphi3", 0.5 , 0.0 , 0.0);

	symbol_numeric theta1 = *sys.new_Coordinate("theta1","dtheta1","ddtheta1", 0.6, 0.0 , 0.0);//theta1 giro plataforma en torno a y
	symbol_numeric theta2 = *sys.new_Coordinate("theta2","dtheta2","ddtheta2", 0.0, 0.0 , 0.0);//theta2 giro rueda izq
	symbol_numeric theta3 = *sys.new_Coordinate("theta3","dtheta3","ddtheta3", 0.0, 0.0 , 0.0);//theta3 giro rueda dcha

	symbol_numeric xp = *sys.new_Coordinate("xp","dxp","ddxp", 2.0, 0.0 , 0.0);
	symbol_numeric yp = *sys.new_Coordinate("yp","dyp","ddyp", 2.0, 0.0 , 0.0);
	symbol_numeric zp = *sys.new_Coordinate("zp","dzp","ddzp", 0.20, 0.0 , 0.0);

      
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
//	Kinematical parameter definition Segway
// ************************************************************************************************

	symbol_numeric R  = *sys.new_Parameter("R",0.15);	//Radio rueda
	symbol_numeric r  = *sys.new_Parameter("r",0.60);	//Longitud mitad manillar
	symbol_numeric l1 = *sys.new_Parameter("l1",0.35);	//Longitud mitad plataforma segway
	symbol_numeric l2 = *sys.new_Parameter("l2",1.20);	//Altura manillar
	symbol_numeric l3 = *sys.new_Parameter("l3",0.45);	//Anchura plataforma
	symbol_numeric d = *sys.new_Parameter("d",0.20);	//Altura plataforma segway
	symbol_numeric alpha = *sys.new_Parameter("alpha",2.0/3.0*PI); //120º=2/3*PI
	symbol_numeric beta = *sys.new_Parameter("beta",-2.0/3.0*PI); 

// ************************************************************************************************
// 	 KINEMATICS Segway
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

	sys.new_Base("BB1c","xyz",0,1,0,theta1);	//Sigue el cabeceo de la plataforma
	sys.new_Base("BB2c","xyz",0,1,0,theta2);	//Sigue el giro rueda izq
	sys.new_Base("BB3c","xyz",0,1,0,theta3);	//Sigue el giro rueda dcha

 	sys.new_Base("BB1a","BB1c",0,0,1,rho1); 	//Sigue el cabeceo + el guiñada del manillar 
	sys.new_Base("BB2a","BB2c",0,0,1,0); 	
	sys.new_Base("BB3a","BB3c",0,0,1,0); 

	sys.new_Base("xyz","BB0c",0,0,1,rho1);		//Sigue su guiñada
	sys.new_Base("BB1","BB1a",1,0,0,phi1);		//Sigue el cabeceo + el guiñada del manilla + giro del manillar
	sys.new_Base("BB2","BB2a",1,0,0,0);
	sys.new_Base("BB3","BB3a",1,0,0,0);
	
cout << "base = "<< sys.Rotation_Matrix(sys.get_Base("BB3a"),sys.get_Base("BB3"))<<endl; //Sale por pantalla la base

// ************************************************************************************************
//	Define Vectors 
// ************************************************************************************************

	Vector3D O_P = *sys.new_Vector3D("O_P",xp,yp,zp,"xyz");		//Origen a punto del Segway

	Vector3D P_A1 = *sys.new_Vector3D("P_A1",0,0,0,"BB1a");	 	//Origen de referencia en el Segway
	Vector3D P_A2 = *sys.new_Vector3D("P_A2",0,l1,0,"BB2a");	//De origen hasta rueda izq 
	Vector3D P_A3 = *sys.new_Vector3D("P_A3",0,-l1,0,"BB3a");	//De origen dcho hasta rueda dcha 

	Vector3D A1_B1 = *sys.new_Vector3D("A1_B1",0,0,d,"xyz"); 	//De P_A1 hasta su proyeccion en el suelo
	Vector3D A2_B2 = *sys.new_Vector3D("A2_B2",0,0,-R,"xyz"); 	//De centro rueda izq hasta punto contacto
	Vector3D A3_B3 = *sys.new_Vector3D("A3_B3",0,0,-R,"xyz"); 	//De centro rueda dcha hasta punto contacto

        Vector3D A1_B1L = *sys.new_Vector3D("A1_B1L",l3,0,0,"BB1a");	//De P_A1 a parte delantera central (rotula manillar)
        Vector3D A1_B1R = *sys.new_Vector3D("A1_B1R",-l3,0,0,"BB1a");	//De P_A1 a parte trasera central de la plataforma
        Vector3D A2_B2L = *sys.new_Vector3D("A2_B2L",l3,0,0,"BB2a");	//De eje izq a parte delantera izq de la plataforma
        Vector3D A2_B2R = *sys.new_Vector3D("A2_B2R",-l3,0,0,"BB2a");	//De eje izq a parte trasera izq de la plataforma
        Vector3D A3_B3L = *sys.new_Vector3D("A3_B3L",l3,0,0,"BB3a");	//De eje dcho a parte delantera fcha de la plataforma
        Vector3D A3_B3R = *sys.new_Vector3D("A3_B3R",-l3,0,0,"BB3a");	//De eje dcho a parte trasera fcha de la plataforma

        Vector3D B1L_C1 = *sys.new_Vector3D("B1L_C1",0,0,l2,"BB1");	//Rótula-centro manillar
	Vector3D B1L_C2 = *sys.new_Vector3D("B1L_C2",0,r,l2,"BB2");	//Rótula-extremo izq manillar 
	Vector3D B1L_C3 = *sys.new_Vector3D("B1L_C3",0,-r,l2,"BB3");	//Rótula-extremo dcho manillar

	Vector3D P_C1 = *sys.new_Vector3D("P_C1",l3,0,l2,"BB1");  	
	Vector3D P_C2 = *sys.new_Vector3D("P_C2",l3,l2,r,"BB2"); 
	Vector3D P_C3 = *sys.new_Vector3D("P_C3",l3,l2,-r,"BB3"); 


// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * P = sys.new_Point("P","O",&O_P);	

	Point * A1 = sys.new_Point("A1","P",&P_A1);
	Point * A2 = sys.new_Point("A2","P",&P_A2);
	Point * A3 = sys.new_Point("A3","P",&P_A3);

	Point * B1 = sys.new_Point("B1","A1",&A1_B1);
	Point * B3 = sys.new_Point("B3","A3",&A3_B3);
	Point * B2 = sys.new_Point("B2","A2",&A2_B2);

        Point * B1L = sys.new_Point("B1L","A1",&A1_B1L);
        Point * B1R = sys.new_Point("B1R","A1",&A1_B1R);
	Point * B2L = sys.new_Point("B2L","A2",&A2_B2L);
        Point * B2R = sys.new_Point("B2R","A2",&A2_B2R);
        Point * B3L = sys.new_Point("B3L","A3",&A3_B3L);
        Point * B3R = sys.new_Point("B3R","A3",&A3_B3R);

	Point * C1 = sys.new_Point("C1","B1L",&B1L_C1);
	Point * C2 = sys.new_Point("C2","B1L",&B1L_C2);
	Point * C3 = sys.new_Point("C3","B1L",&B1L_C3);



// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Viscosity
       	symbol_numeric  Cvis1 = *sys.new_Parameter("Cvis1",8.0);
        symbol_numeric  Cvis2 = *sys.new_Parameter("Cvis2",18.0);
        symbol_numeric  Cvis3 = *sys.new_Parameter("Cvis3",8.0);

	// Dynamic Parameters of Manillar

    	symbol_numeric  mManillar = *sys.new_Parameter("mManillar",1.0);

	symbol_numeric  mxManillar = *sys.new_Parameter("mxManillar",0.0);
    	symbol_numeric  myManillar = *sys.new_Parameter("myManillar",0.0);
	symbol_numeric  mzManillar = *sys.new_Parameter("mzManillar",0.0);

    	symbol_numeric  IxxManillar = *sys.new_Parameter("IxxManillar",1.0);
	symbol_numeric  IxyManillar = *sys.new_Parameter("IxyManillar",0.0);
    	symbol_numeric  IyyManillar = *sys.new_Parameter("IyyManillar",1.0);
	symbol_numeric  IxzManillar = *sys.new_Parameter("IxzManillar",0.0);
    	symbol_numeric  IzzManillar = *sys.new_Parameter("IzzManillar",1.0);
	symbol_numeric  IyzManillar = *sys.new_Parameter("IyzManillar",0.0);

	// Dynamic Parameters of Rueda 1

    	symbol_numeric  mRueda1 = *sys.new_Parameter("mRueda1",1.0);

	symbol_numeric  mxRueda1 = *sys.new_Parameter("mxRueda1",0.0);
    	symbol_numeric  myRueda1 = *sys.new_Parameter("myRueda1",0.0);
	symbol_numeric  mzRueda1 = *sys.new_Parameter("mzRueda1",0.0);

    	symbol_numeric  IxxRueda1 = *sys.new_Parameter("IxxRueda1",1.0);
	symbol_numeric  IxyRueda1 = *sys.new_Parameter("IxyRueda1",0.0);
    	symbol_numeric  IyyRueda1 = *sys.new_Parameter("IyyRueda1",5.0);
	symbol_numeric  IxzRueda1 = *sys.new_Parameter("IxzRueda1",0.0);
    	symbol_numeric  IzzRueda1 = *sys.new_Parameter("IzzRueda1",1.0);
	symbol_numeric  IyzRueda1 = *sys.new_Parameter("IyzRueda1",0.0);

	// Dynamic Parameters of Rueda 2

    	symbol_numeric  mRueda2 = *sys.new_Parameter("mRueda2",1.0);

	symbol_numeric  mxRueda2 = *sys.new_Parameter("mxRueda2",0.0);
    	symbol_numeric  myRueda2 = *sys.new_Parameter("myRueda2",0.0);
	symbol_numeric  mzRueda2 = *sys.new_Parameter("mzRueda2",0.0);

    symbol_numeric  IxxRueda2 = *sys.new_Parameter("IxxRueda2",1.0);
	symbol_numeric  IxyRueda2 = *sys.new_Parameter("IxyRueda2",0.0);
    symbol_numeric  IyyRueda2 = *sys.new_Parameter("IyyRueda2",1.0);
	symbol_numeric  IxzRueda2 = *sys.new_Parameter("IxzRueda2",0.0);
    symbol_numeric  IzzRueda2 = *sys.new_Parameter("IzzRueda2",1.0);
	symbol_numeric  IyzRueda2 = *sys.new_Parameter("IyzRueda2",0.0);

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

	// Dynamic Parameters of Platform

    symbol_numeric  mPlatform = *sys.new_Parameter("mPlatform",1.0);

	symbol_numeric  mxPlatform = *sys.new_Parameter("mxPlatform",0.0);
    symbol_numeric  myPlatform = *sys.new_Parameter("myPlatform",0.0);
	symbol_numeric  mzPlatform = *sys.new_Parameter("mzPlatform",0.0);

    symbol_numeric  IxxPlatform = *sys.new_Parameter("IxxPlatform",1.0);
	symbol_numeric  IxyPlatform = *sys.new_Parameter("IxyPlatform",0.0);
    symbol_numeric  IyyPlatform = *sys.new_Parameter("IyyPlatform",1.0);
	symbol_numeric  IxzPlatform = *sys.new_Parameter("IxzPlatform",0.0);
    symbol_numeric  IzzPlatform = *sys.new_Parameter("IzzPlatform",1.0);
	symbol_numeric  IyzPlatform = *sys.new_Parameter("IyzPlatform",0.0);

	//Gravity Center Vectors    

	Vector3D B1_GManillar1= *sys.new_Vector3D("B1_GManillar1",mxManillar/mManillar,myManillar/mManillar,mzManillar/mManillar,"BB1c");
	Vector3D B2_GManillar2= *sys.new_Vector3D("B2_GManillar2",mxManillar/mManillar,myManillar/mManillar,mzManillar/mManillar,"BB2c");
	Vector3D B3_GManillar3= *sys.new_Vector3D("B3_GManillar3",mxManillar/mManillar,myManillar/mManillar,mzManillar/mManillar,"BB3c");
	
	Vector3D B1L_GRueda1L= *sys.new_Vector3D("B1L_GRueda1L",0,-l1/2,0,"BB1");
	Vector3D B1L_GRueda1R= *sys.new_Vector3D("B1R_GRueda1R",0,-l1/2,0,"BB1");
	//Vector3D B1_GRueda1= *sys.new_Vector3D("B1_GRueda1",0,-l1/2,0,"BB1");
	Vector3D B2L_GRueda2L= *sys.new_Vector3D("B2L_GRueda2L",0,-l2/2,0,"BB2");
	Vector3D B2R_GRueda2R= *sys.new_Vector3D("B2R_GRueda2R",0,-l2/2,0,"BB2");
	//Vector3D B2_GRueda2= *sys.new_Vector3D("B2_GRueda2",0,-l2/2,0,"BB2");
	Vector3D B3L_GRod3L= *sys.new_Vector3D("B3L_GRod3L",0,-l3/2,0,"BB3");
	Vector3D B3R_GRod3R= *sys.new_Vector3D("B3R_GRod3R",0,-l3/2,0,"BB3");
	//Vector3D B3_GRod3= *sys.new_Vector3D("B3_GRod3",0,-l3/2,0,"BB3");

	Vector3D P_GPlatform= *sys.new_Vector3D("P_GPlatform",0,0,0,"xyz");

	//Inertia Tensors		
	
    Tensor3D IManillar1 = *sys.new_Tensor3D("IManillar1",(ex)IxxManillar,(ex)IxyManillar,(ex)IxzManillar,(ex)IxyManillar,(ex)IyyManillar,(ex)IyzManillar,(ex)IxzManillar,(ex)IyzManillar,(ex)IzzManillar,"BB1c");

	Tensor3D IManillar2 = *sys.new_Tensor3D("IManillar2",(ex)IxxManillar,(ex)IxyManillar,(ex)IxzManillar,(ex)IxyManillar,(ex)IyyManillar,(ex)IyzManillar,(ex)IxzManillar,(ex)IyzManillar,(ex)IzzManillar,"BB2c"); 

	Tensor3D IManillar3 = *sys.new_Tensor3D("IManillar3",(ex)IxxManillar,(ex)IxyManillar,(ex)IxzManillar,(ex)IxyManillar,(ex)IyyManillar,(ex)IyzManillar,(ex)IxzManillar,(ex)IyzManillar,(ex)IzzManillar,"BB3c"); 


	Tensor3D IRueda1 = *sys.new_Tensor3D("IRueda1",(ex)IxxRueda1,(ex)IxyRueda1,(ex)IxzRueda1,(ex)IxyRueda1,(ex)IyyRueda1,(ex)IyzRueda1,(ex)IxzRueda1,(ex)IyzRueda1,(ex)IzzRueda1,"BB1");

	Tensor3D IRueda2 = *sys.new_Tensor3D("IRueda2",(ex)IxxRueda2,(ex)IxyRueda2,(ex)IxzRueda2,(ex)IxyRueda2,(ex)IyyRueda2,(ex)IyzRueda2,(ex)IxzRueda2,(ex)IyzRueda2,(ex)IzzRueda2,"BB2");

	Tensor3D IRod3 = *sys.new_Tensor3D("IRod3",(ex)IxxRod3,(ex)IxyRod3,(ex)IxzRod3,(ex)IxyRod3,(ex)IyyRod3,(ex)IyzRod3,(ex)IxzRod3,(ex)IyzRod3,(ex)IzzRod3,"BB3");

	Tensor3D IPlatform = *sys.new_Tensor3D("IPlatform",(ex)IxxPlatform,(ex)IxyPlatform,(ex)IxzPlatform,(ex)IxyPlatform,(ex)IyyPlatform,(ex)IyzPlatform,(ex)IxzPlatform,(ex)IyzPlatform,(ex)IzzPlatform,"xyz");

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Manillar1 = sys.new_Frame("Fra_Manillar1","B1","BB1c");
	Frame * Fra_Manillar2 = sys.new_Frame("Fra_Manillar2","B2","BB2c");
	Frame * Fra_Manillar3 = sys.new_Frame("Fra_Manillar3","B3","BB3c");

	Frame * Fra_Rueda1 = sys.new_Frame("Fra_Rueda1","B1","BB1");
	Frame * Fra_Rueda2 = sys.new_Frame("Fra_Rueda2","B2","BB2");
	Frame * Fra_Rod3 = sys.new_Frame("Fra_Rod3","B3","BB3");

	Frame * Fra_Platform = sys.new_Frame("Fra_Platform","P","xyz");

// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	//Solid * RuedaIzq =
	//Solid * RuedaDcha =
	//Solid * Plataforma =
	//Solid * Manillar =
	Solid * Manillar1 = sys.new_Solid("Manillar1","B1","BB1c","mManillar","B1_GManillar1","IManillar1");
	Solid * Manillar2 = sys.new_Solid("Manillar2","B2","BB2c","mManillar","B2_GManillar2","IManillar2");
	Solid * Manillar3 = sys.new_Solid("Manillar3","B3","BB3c","mManillar","B3_GManillar3","IManillar3");

	Solid * Rueda1L = sys.new_Solid("Rueda1L","B1L","BB1","mRueda1","B1L_GRueda1L","IRueda1");
	Solid * Rueda1R = sys.new_Solid("Rueda1R","B1R","BB1","mRueda1","B1R_GRueda1R","IRueda1");
	Solid * Rueda2L = sys.new_Solid("Rueda2L","B2L","BB2","mRueda2","B2L_GRueda2L","IRueda2");
	Solid * Rueda2R = sys.new_Solid("Rueda2R","B2R","BB2","mRueda2","B2R_GRueda2R","IRueda2");
	Solid * Rod3L = sys.new_Solid("Rod3L","B3L","BB3","mRod3","B3L_GRod3L","IRod3");
	Solid * Rod3R = sys.new_Solid("Rod3R","B3R","BB3","mRod3","B3R_GRod3R","IRod3");

	Solid * Platform = sys.new_Solid("Platform","P","xyz","mPlatform","P_GPlatform","IPlatform");



// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

	Drawing3D * Ground3D = sys.new_Drawing3D("Ground3D", "O", "xyz","./solids/body.osgt");

	Drawing3D * Manillar13D = sys.new_Drawing3D("Manillar13D", Manillar1,"./solids/carriage.osgt");
	Drawing3D * Manillar23D = sys.new_Drawing3D("Manillar23D", Manillar2,"./solids/carriage.osgt");
	Drawing3D * Manillar33D = sys.new_Drawing3D("Manillar33D", Manillar3,"./solids/carriage.osgt");

	Drawing3D * Rueda1L3D = sys.new_Drawing3D("Rueda1L3D", Rueda1L,"./solids/rod.osgt");
	Drawing3D * Rueda1R3D = sys.new_Drawing3D("Rueda1R3D", Rueda1R,"./solids/rod.osgt");
	Drawing3D * Rueda2L3D = sys.new_Drawing3D("Rueda2L3D", Rueda2L,"./solids/rod.osgt");
	Drawing3D * Rueda2R3D = sys.new_Drawing3D("Rueda2R3D", Rueda2R,"./solids/rod.osgt");
	Drawing3D * Rod3L3D = sys.new_Drawing3D("Rod3L3D", Rod3L,"./solids/rod.osgt");
	Drawing3D * Rod3R3D = sys.new_Drawing3D("Rod3R3D", Rod3R,"./solids/rod.osgt");

	Drawing3D * Platform3D = sys.new_Drawing3D("Platform3D", Platform,"./solids/header.osgt");	
	
        //Drawing3D * FraPlatform = sys.new_Drawing3D( "FraPlatform" , Fra_Platform, 0.1 );

 
	
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
	symbol_numeric lambda1 = *sys.new_Joint_Unknown("lambda1");
	symbol_numeric lambda2 = *sys.new_Joint_Unknown("lambda2");
	symbol_numeric lambda3 = *sys.new_Joint_Unknown("lambda3");
	symbol_numeric lambda4 = *sys.new_Joint_Unknown("lambda4");
	symbol_numeric lambda5 = *sys.new_Joint_Unknown("lambda5");
	symbol_numeric lambda6 = *sys.new_Joint_Unknown("lambda6");
	symbol_numeric lambda7 = *sys.new_Joint_Unknown("lambda7");
	symbol_numeric lambda8 = *sys.new_Joint_Unknown("lambda8");
	symbol_numeric lambda9 = *sys.new_Joint_Unknown("lambda9");


// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

	cout << "Input Vector" << endl;

	symbol_numeric FManillar1z = *sys.new_Input("FManillar1z",0.0);
	symbol_numeric FManillar2z = *sys.new_Input("FManillar2z",0.0);
	symbol_numeric FManillar3z = *sys.new_Input("FManillar3z",0.0);

	Vector3D FManillar1 = *sys.new_Vector3D("FManillar1",0,0,FManillar1z,"BB1c");
	Vector3D MManillar1 = *sys.new_Vector3D("MManillar1",0,0,0, "BB1c");

	Vector3D FManillar2 = *sys.new_Vector3D("FManillar2",0,0,FManillar2z,"BB2c");
	Vector3D MManillar2 = *sys.new_Vector3D("MManillar2",0,0,0, "BB2c");

	Vector3D FManillar3 = *sys.new_Vector3D("FManillar3",0,0,FManillar3z,"BB3c");
	Vector3D MManillar3 = *sys.new_Vector3D("MManillar3",0,0,0, "BB3c");


// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************
        symbol_numeric xp_0 = *sys.new_Parameter("xp_0",0.0);
        symbol_numeric yp_0 = *sys.new_Parameter("yp_0",0.0);
        symbol_numeric zp_0 = *sys.new_Parameter("zp_0",0.0);

	Vector3D FV_Manillar1 = -Cvis1 * sys.Velocity_Vector("abs" ,"B1", "Manillar1" );
	Vector3D MV_Manillar1 = *sys.new_Vector3D("MV_Manillar1",0,0,0,"BB1c");

	Vector3D FV_Manillar2 = -Cvis2 * sys.Velocity_Vector("abs" ,"B2", "Manillar2" );
	Vector3D MV_Manillar2 = *sys.new_Vector3D("MV_Manillar2",0,0,0,"BB2c");

	Vector3D FV_Manillar3 = -Cvis3 * sys.Velocity_Vector("abs" ,"B3", "Manillar3" );
	Vector3D MV_Manillar3 = *sys.new_Vector3D("MV_Manillar3",0,0,0,"BB3c");

// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * Gravity_Manillar1 = sys.Gravity_Wrench("Manillar1");
	Wrench3D * Gravity_Manillar2 = sys.Gravity_Wrench("Manillar2");
	Wrench3D * Gravity_Manillar3 = sys.Gravity_Wrench("Manillar3");

	Wrench3D * Gravity_Rueda1L = sys.Gravity_Wrench("Rueda1L");
	Wrench3D * Gravity_Rueda1R = sys.Gravity_Wrench("Rueda1R");
	Wrench3D * Gravity_Rueda2L = sys.Gravity_Wrench("Rueda2L");
	Wrench3D * Gravity_Rueda2R = sys.Gravity_Wrench("Rueda2R");
	Wrench3D * Gravity_Rod3L = sys.Gravity_Wrench("Rod3L");
	Wrench3D * Gravity_Rod3R = sys.Gravity_Wrench("Rod3R");

	Wrench3D * Gravity_Platform = sys.Gravity_Wrench("Platform");

	//	Inertia
	Wrench3D * Inertia_Manillar1 = sys.Inertia_Wrench("Manillar1");
	Wrench3D * Inertia_Manillar2 = sys.Inertia_Wrench("Manillar2");
	Wrench3D * Inertia_Manillar3 = sys.Inertia_Wrench("Manillar3");

	Wrench3D * Inertia_Rueda1L = sys.Inertia_Wrench("Rueda1L");
	Wrench3D * Inertia_Rueda1R = sys.Inertia_Wrench("Rueda1R");
	Wrench3D * Inertia_Rueda2L = sys.Inertia_Wrench("Rueda2L");
	Wrench3D * Inertia_Rueda2R = sys.Inertia_Wrench("Rueda2R");
	Wrench3D * Inertia_Rod3L = sys.Inertia_Wrench("Rod3L");
	Wrench3D * Inertia_Rod3R = sys.Inertia_Wrench("Rod3R");

	Wrench3D * Inertia_Platform = sys.Inertia_Wrench("Platform");

	//	Constitutive
	Wrench3D * Viscosity1 = sys.new_Wrench3D ( "Viscosity1", FV_Manillar1, MV_Manillar1, B1 , Manillar1 , "Constitutive") ;
	Wrench3D * Viscosity2 = sys.new_Wrench3D ( "Viscosity2", FV_Manillar2, MV_Manillar2, B2 , Manillar2 , "Constitutive") ;
	Wrench3D * Viscosity3 = sys.new_Wrench3D ( "Viscosity3", FV_Manillar3, MV_Manillar3, B3 , Manillar3 , "Constitutive") ;

	//	External
	Wrench3D * Manillar1_Impulse = sys.new_Wrench3D ( "Manillar1_Impulse", FManillar1, MManillar1, B1 , Manillar1 , "External");
	Wrench3D * Manillar2_Impulse = sys.new_Wrench3D ( "Manillar2_Impulse", FManillar2, MManillar2, B2 , Manillar2 , "External");
	Wrench3D * Manillar3_Impulse = sys.new_Wrench3D ( "Manillar3_Impulse", FManillar3, MManillar3, B3 , Manillar3 , "External");


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
	//Vector3D O_C1= P_A1 + A1_B1 + B1_C1;


	Vector3D O_C1= sys.Position_Vector("O","C1");
	Vector3D O_C2= sys.Position_Vector("O","C2");
	Vector3D O_C3= sys.Position_Vector("O","C3");
cout << " O_C1= "<< O_C1<<endl;
cout << " O_C2= "<< O_C2<<endl;

	Drawing3D * VectorP_A1 = sys.new_Drawing3D("VectorP_A1",&P_A1,Point_O,1.0,0.0,1.0,1.0);

	Drawing3D * VectorO_C1 = sys.new_Drawing3D("VectorO_C1",&O_C1,Point_O,1.0,0.0,1.0,1.0);
	//Drawing3D * VectorB2_B2L = sys.new_Drawing3D("VectorB2_B2L",&B2_B2L,B2,1.0,0.0,1.0,1.0);

	Drawing3D * VectorO_C2 = sys.new_Drawing3D("VectorO_C2",&O_C2,Point_O,0.0,0.0,1.0,1.0);
	//Drawing3D * VectorP_C2 = sys.new_Drawing3D("VectorP_C2",&P_C2,P,0.0,0.0,1.0,1.0);

	Drawing3D * VectorO_C3 = sys.new_Drawing3D("VectorO_C3",&O_C3,Point_O,0.0,1.0,0.0,1.0);
	//Drawing3D * VectorP_C3 = sys.new_Drawing3D("VectorP_C3",&P_C3,P,0.0,1.0,0.0,1.0);

	//Drawing3D * VectorB1_B1R = sys.new_Drawing3D("VectorB1_B1R",&B1_B1R,B1R,0.0,0.0,1.0,1.0);
	//Vector3D PHI1 = P_A1 + A1_B1+ B1_B1L + B1L_C1L - (O_P + P_C1 + C1_C1L);
	//Vector3D PHI1R = P_A1 + A1_B1+ B1_B1R + B1R_C1R - (O_P + P_C1 + C1_C1R);
	Vector3D PHI1 = O_C1 - O_P - P_C1;
	Vector3D PHI2 = O_C2 - O_P - P_C2;
	Vector3D PHI3 = O_C3 - O_P - P_C3;
	Matrix Phi(9,1);
	Phi(0,0) = PHI1 (0,0);
	Phi(1,0) = PHI1 (1,0);
	Phi(2,0) = PHI1 (2,0);
	Phi(3,0) = PHI2 (0,0);
	Phi(4,0) = PHI2 (1,0);
	Phi(5,0) = PHI2 (2,0);
	Phi(6,0) = PHI3 (0,0);
	Phi(7,0) = PHI3 (1,0);
	Phi(8,0) = PHI3 (2,0);

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
	sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);
	// Without restrictions (no Phi)
	//sys.Matrix_Calculation(coord_indep_init, vel_indep_init, Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);


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


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

	symbol_numeric pi = *sys.new_Parameter("pi",3.14159265358979);
#define PI 3.14159265358979
	symbol_numeric rho1 = *sys.new_Coordinate("rho1","drho1","ddrho1", 0.4 , 0.0 , 0.0);//cooerdenadas de las rueda 1
	symbol_numeric rho2 = *sys.new_Coordinate("rho2","drho2","ddrho2", 0.4 , 0.0 , 0.0);//coordenadas de la rueda2


	symbol_numeric phi1 = *sys.new_Coordinate("phi1","dphi1","ddphi1", 0.0 , 0.0 , 0.0);//cabeceo de la base
	symbol_numeric phi2 = *sys.new_Coordinate("phi2","dphi2","ddphi2", 0.5 , 0.0 , 0.0);//giro en z de la base

	symbol_numeric theta1 = *sys.new_Coordinate("theta1","dtheta1","ddtheta1", 0.0, 0.0 , 0.0); //giro del manillar


	symbol_numeric xp = *sys.new_Coordinate("xp","dxp","ddxp", 0.0, 0.0 , 0.0);//coodenadas del centro plataforma
	symbol_numeric yp = *sys.new_Coordinate("yp","dyp","ddyp", 0.0, 0.0 , 0.0);
	symbol_numeric zp = *sys.new_Coordinate("zp","dzp","ddzp", 0.0, 0.0 , 0.0);

      
	symbol_numeric *drho1=sys.get_Velocity("drho1");//velocidades rueda1
	symbol_numeric *drho2=sys.get_Velocity("drho2");//velocidades rueda2


	symbol_numeric *dphi1=sys.get_Velocity("dphi1");//velovidades  cabeceo plataforma
    symbol_numeric *dphi2=sys.get_Velocity("dphi2");//velovidades giro  plataforma	

	symbol_numeric *dtheta1=sys.get_Velocity("dtheta1");//velocidades manillar
	


	symbol_numeric *dxp=sys.get_Velocity("dxp");//velocidades centro plataforma
	symbol_numeric *dyp=sys.get_Velocity("dyp");
	symbol_numeric *dzp=sys.get_Velocity("dzp");

	symbol_numeric *ddrho1=sys.get_Acceleration("ddrho1");//aceleracion ruedas
	symbol_numeric *ddrho2=sys.get_Acceleration("ddrho2");


	symbol_numeric *ddphi1=sys.get_Acceleration("ddphi1");//aceleracion plataforma
	symbol_numeric *ddphi2=sys.get_Acceleration("ddphi2");//aceleracion plataforma
	

	symbol_numeric *ddtheta1=sys.get_Acceleration("ddtheta1");// aceleracion manillar
	

	symbol_numeric *ddxp=sys.get_Acceleration("ddxp");//aceleracion cdm
	symbol_numeric *ddyp=sys.get_Acceleration("ddyp");
	symbol_numeric *ddzp=sys.get_Acceleration("ddzp");

	lst coord_indep_init;
	lst vel_indep_init;
	
// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	symbol_numeric R  = *sys.new_Parameter("R",0.15); //radio de la rueda
	symbol_numeric h  = *sys.new_Parameter("r",0.3);//altura de la plataforma
	symbol_numeric l1 = *sys.new_Parameter("l1",0.25);//anchura de la plataforma
	symbol_numeric l2 = *sys.new_Parameter("l2",0.25);//longitud de la plataforma
	symbol_numeric l3 = *sys.new_Parameter("l3",0.25);//espesor de la plataforma
	symbol_numeric d = *sys.new_Parameter("d",0.022);
	symbol_numeric alpha = *sys.new_Parameter("alpha",2.0/3.0*PI); //120º=2/3*PI
	symbol_numeric beta = *sys.new_Parameter("beta",-2.0/3.0*PI); 

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

 
	sys.new_Base("Plataforma1","xyz",0,0,1,pi/2);//defino primera base plataforma
	sys.new_Base("Plataforma2","Plataforma1",0,1,0,pi/8);//defino segunda base plataforma

    sys.new_Base("RUEDA1","Plataforma1",0,1,0,0);//defino base rueda1
	sys.new_Base("RUEDA2","Plataforma1",0,1,0,0);//defino base rueda 2	

	sys.new_Base("Manillar","Plataforma2",1,0,0,pi/8);//defino base manillar
	
cout << "base = "<< sys.Rotation_Matrix(sys.get_Base("BB3a"),sys.get_Base("BB3"))<<endl;

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	Vector3D P_R1= *sys.new_Vector3D("P_R1",0,l2,0,"Plataforma1"); //Vector origen rueda 1
	Vector3D P_R2 = *sys.new_Vector3D("P_R2",0,-l2,0,"Plataforma1"); //vector origen rueda 2 
	Vector3D P_M = *sys.new_Vector3D("P_M",0,0,R,"Plataforma2");//vector origen centro del manillar
	
	Vector3D O_R1= *sys.new_Vector3D("O_R1",0,l2,0,"Plataforma1");//origen rueda1
	Vector3D O_R2= *sys.new_Vector3D("O_R2",0,-l2,0,"Plataforma1");//origen rueda2
	
	
	Vector3D R1_C1= *sys.new_Vector3D("R1_C1",R,0,0,"Plataforma2");//esquina drcah superior plataforma
	Vector3D R1_C2= *sys.new_Vector3D("R1_C2",-R,0,0,"Plataforma2");//esquina drcah inferiro plataforma
	Vector3D R2_D1= *sys.new_Vector3D("R2_D1",R,0,0,"Plataforma2");//esquina izquierda sup plataforma
	Vector3D R2_D2= *sys.new_Vector3D("R2_D2",-R,0,0,"Plataforma2");//esquina izquierd inf plataforma
	
	Vector3D C1_D1= *sys.new_Vector3D("C1_D1",0,-2*l2,0,"Plataforma2");//origen rueda2
	Vector3D C2_D2= *sys.new_Vector3D("C2_D2",0,-2*l2,0,"Plataforma2");//origen rueda2
	
	Vector3D R1_J1 = *sys.new_Vector3D("R1_J1",0,0,-R,"RUEDA1");//vector centro rueda pto contacto
	Vector3D R2_J2 = *sys.new_Vector3D("R2_J2",0, 0,-R,"RUEDA2");//vector centro rueda pto contacto
    Vector3D O_M= *sys.new_Vector3D("O_M",0,0,l2,"Manillar"); //EJE MANILLAR
    Vector3D M_M1= *sys.new_Vector3D("M_M1",0,R,0,"Manillar"); //MANILLAR
    Vector3D M_M2= *sys.new_Vector3D("M_M2",0,-R,0,"Manillar"); //MANILLAR
    
    Vector3D O_J1= *sys.new_Vector3D("O_J1",0,l2,-l2,"xyz"); //origen rueda1
    Vector3D O_J2= *sys.new_Vector3D("O_J2",0,-l2,-l2,"xyz"); //origen rueda1
    
    
  
     
	//Vector3D P_B = *sys.new_Vector3D("P_B",0,0,theta1,"Plataforma"); //vector centro manillar

         

	Vector3D O_P = *sys.new_Vector3D("O_P",xp,yp,zp,"xyz");

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	Point * P = sys.new_Point("P","O",&O_P);
	Point * R1 = sys.new_Point("R1","O",&O_R1); // definir centro rueda 1
	Point * R2 = sys.new_Point("R2","O",&O_R2); //defino centro rueda2
	Point * M = sys.new_Point("M","O",&O_M);  // CENTRO MANILLAR

	Point * J1 = sys.new_Point("J1","R1",&R1_J1);//Pto cto suelo
	Point * J2 = sys.new_Point("J2","R2",&R2_J2);//Pto cto suelo


   	Point * M1 = sys.new_Point("M1","M",&M_M1);//Pto cto suelo
	Point * M2 = sys.new_Point("M2","M",&M_M2);//Pto cto suelo
	
	Point * C1 = sys.new_Point("C1","R1",&R1_C1);//Pto cto suelo
	Point * C2 = sys.new_Point("C2","R1",&R1_C2);//Pto cto suelo
	
	Point * D1 = sys.new_Point("D1","R2",&R2_D1);//Pto cto suelo
	Point * D2 = sys.new_Point("D2","R2",&R2_D2);//Pto cto suelo



// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Viscosity
       	symbol_numeric  Cvis1 = *sys.new_Parameter("Cvis1",8.0);
        symbol_numeric  Cvis2 = *sys.new_Parameter("Cvis2",18.0);
        symbol_numeric  Cvis3 = *sys.new_Parameter("Cvis3",8.0);

	// Dynamic Parameters of Carrier (all three carriers are identical) (MANILLAR)

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

	// Dynamic Parameters of Rod 1(rueda1)

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

	// Dynamic Parameters of Rod 2(rueda2)

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

	//Vector3D M_GCarrier1= *sys.new_Vector3D("B1_GCarrier1",mxCarrier/mCarrier,myCarrier/mCarrier,mzCarrier/mCarrier,"Plataforma");
	//Vector3D B2_GCarrier2= *sys.new_Vector3D("B2_GCarrier2",mxCarrier/mCarrier,myCarrier/mCarrier,mzCarrier/mCarrier,"BB2c");
	//Vector3D B3_GCarrier3= *sys.new_Vector3D("B3_GCarrier3",mxCarrier/mCarrier,myCarrier/mCarrier,mzCarrier/mCarrier,"BB3c");
	
	Vector3D C1_GRod1= *sys.new_Vector3D("C1_GRod1",0,0,0,"RUEDA1");
	Vector3D C2_GRod2= *sys.new_Vector3D("C2_GRod2",0,0,0,"RUEDA2");
	//Vector3D B1_GRod1= *sys.new_Vector3D("B1_GRod1",0,-l1/2,0,"BB1");
	Vector3D M_GRodM= *sys.new_Vector3D("M_GRodM",0,0,l2/2,"Manillar");
	Vector3D P_GHeader= *sys.new_Vector3D("P_GHeader",0,0,0,"Plataforma2");

	//Inertia Tensors		
	
    Tensor3D ICarrier = *sys.new_Tensor3D("ICarrier",(ex)IxxCarrier,(ex)IxyCarrier,(ex)IxzCarrier,(ex)IxyCarrier,(ex)IyyCarrier,(ex)IyzCarrier,(ex)IxzCarrier,(ex)IyzCarrier,(ex)IzzCarrier,"Manillar");

	Tensor3D IRod1 = *sys.new_Tensor3D("IRod1",(ex)IxxRod1,(ex)IxyRod1,(ex)IxzRod1,(ex)IxyRod1,(ex)IyyRod1,(ex)IyzRod1,(ex)IxzRod1,(ex)IyzRod1,(ex)IzzRod1,"RUEDA1");

	Tensor3D IRod2 = *sys.new_Tensor3D("IRod2",(ex)IxxRod2,(ex)IxyRod2,(ex)IxzRod2,(ex)IxyRod2,(ex)IyyRod2,(ex)IyzRod2,(ex)IxzRod2,(ex)IyzRod2,(ex)IzzRod2,"RUEDA2");

	Tensor3D IHeader = *sys.new_Tensor3D("IHeader",(ex)IxxHeader,(ex)IxyHeader,(ex)IxzHeader,(ex)IxyHeader,(ex)IyyHeader,(ex)IyzHeader,(ex)IxzHeader,(ex)IyzHeader,(ex)IzzHeader,"Plataforma2");

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Carrier = sys.new_Frame("Fra_manillar","M","Manillar");
	Frame * Fra_Rod1 = sys.new_Frame("Fra_Rod1","R1","RUEDA1");
	Frame * Fra_Rod2 = sys.new_Frame("Fra_Rod2","R2","RUEDA2");
	

	Frame * Fra_Header = sys.new_Frame("Fra_Header","P","Plataforma2");

// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	//Solid * Carrier1 = sys.new_Solid("Carrier1","B1","BB1c","mCarrier","B1_GCarrier1","ICarrier1");
	//Solid * Carrier2 = sys.new_Solid("Carrier2","B2","BB2c","mCarrier","B2_GCarrier2","ICarrier2");
	//Solid * Carrier3 = sys.new_Solid("Carrier3","B3","BB3c","mCarrier","B3_GCarrier3","ICarrier3");
	
	
	Solid * Carrier = sys.new_Solid("Carrier","M","Manillar","mCarrier","M_GRodM","ICarrier");
	
	Solid * Rod1 = sys.new_Solid("Rod1","R1","RUEDA1","mRod1","C1_GRod1","IRod1");
	Solid * Rod2 = sys.new_Solid("Rod2","R2","RUEDA2","mRod2","C2_GRod2","IRod2");
	
	Solid * Header = sys.new_Solid("Header","O","Plataforma1","mHeader","P_GHeader","IHeader");



// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

	//Drawing3D * Ground3D = sys.new_Drawing3D("Ground3D", "O", "xyz","./solids/body.osgt");

	//Drawing3D * Carrier13D = sys.new_Drawing3D("Carrier13D", Carrier1,"./solids/carriage.osgt");
	//Drawing3D * Carrier23D = sys.new_Drawing3D("Carrier23D", Carrier2,"./solids/carriage.osgt");
	//Drawing3D * Carrier33D = sys.new_Drawing3D("Carrier33D", Carrier3,"./solids/carriage.osgt");

	Drawing3D * Carrier3D = sys.new_Drawing3D("Carrier3D", Carrier,"./solids/carriage.osgt");
	Drawing3D * Rod13D = sys.new_Drawing3D("Rod13D", Rod1,"./solids/Manillar.osg");
	Drawing3D * Rod23D = sys.new_Drawing3D("Rod23D", Rod2,"./solids/rod.osgt");
	Drawing3D * Header3D = sys.new_Drawing3D("Header3D", Header,"./solids/header.osgt");	
	
        //Drawing3D * FraHeader = sys.new_Drawing3D( "FraHeader" , Fra_Header, 0.1 );

 
	
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
//	Joint Unknown Definition  NO SE QUE HACE
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
// 	Input Vector  REPASAR
// ************************************************************************************************

	cout << "Input Vector" << endl;

	symbol_numeric FCarrier1z = *sys.new_Input("FCarrier1z",0.0);
	symbol_numeric FCarrier2z = *sys.new_Input("FCarrier2z",0.0);
	symbol_numeric FCarrier3z = *sys.new_Input("FCarrier3z",0.0);

	Vector3D FCarrier1 = *sys.new_Vector3D("FCarrier1",0,0,FCarrier1z,"Plataforma2");
	Vector3D MCarrier1 = *sys.new_Vector3D("MCarrier1",0,0,0, "Plataforma2");

	//Vector3D FCarrier2 = *sys.new_Vector3D("FCarrier2",0,0,FCarrier2z,"Plataforma2");
	//Vector3D MCarrier2 = *sys.new_Vector3D("MCarrier2",0,0,0, "Plataforma2");

	//Vector3D FCarrier3 = *sys.new_Vector3D("FCarrier3",0,0,FCarrier3z,"Plataforma2");
	//Vector3D MCarrier3 = *sys.new_Vector3D("MCarrier3",0,0,0, "Plataforma2");


// ************************************************************************************************
//	Force and Momentum Definition  REPASAR
// ************************************************************************************************
        symbol_numeric xp_0 = *sys.new_Parameter("xp_0",0.0);
        symbol_numeric yp_0 = *sys.new_Parameter("yp_0",0.0);
        symbol_numeric zp_0 = *sys.new_Parameter("zp_0",0.0);

	//Vector3D FV_Carrier1 = -Cvis1 * sys.Velocity_Vector("abs" ,"M", "Carrier1" );
	//Vector3D MV_Carrier1 = *sys.new_Vector3D("MV_Carrier1",0,0,0,"BB1c");

	//Vector3D FV_Carrier2 = -Cvis2 * sys.Velocity_Vector("abs" ,"B2", "Carrier2" );
	//Vector3D MV_Carrier2 = *sys.new_Vector3D("MV_Carrier2",0,0,0,"BB2c");

	//Vector3D FV_Carrier3 = -Cvis3 * sys.Velocity_Vector("abs" ,"B3", "Carrier3" );
	//Vector3D MV_Carrier3 = *sys.new_Vector3D("MV_Carrier3",0,0,0,"BB3c");

// ************************************************************************************************
//	Define Wrenches	REPASAR
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * Gravity_Carrier= sys.Gravity_Wrench("Carrier");
	Wrench3D * Gravity_Rod1= sys.Gravity_Wrench("Rod1");
	Wrench3D * Gravity_Rod2 = sys.Gravity_Wrench("Rod2");
	Wrench3D * Gravity_Header = sys.Gravity_Wrench("Header");

	//	Inertia
	Wrench3D * Inertia_Carrier = sys.Inertia_Wrench("Carrier");
	Wrench3D * Inertia_Rod1 = sys.Inertia_Wrench("Rod1");
	Wrench3D * Inertia_Rod2 = sys.Inertia_Wrench("Rod2");
	Wrench3D * Inertia_Header = sys.Inertia_Wrench("Header");

	//	Constitutive
	//Wrench3D * Viscosity1 = sys.new_Wrench3D ( "Viscosity1", FV_Carrier1, MV_Carrier1, B1 , Carrier1 , "Constitutive") ;
	
	//	External
	//Wrench3D * Carrier1_Impulse = sys.new_Wrench3D ( "Carrier1_Impulse", FCarrier1, MCarrier1, B1 , Carrier1 , "External");



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


	//Vector3D R1_J1= sys.Position_Vector("R1","J1");
	//Vector3D O_R2= sys.Position_Vector("O","R2");
	//Vector3D O_M= sys.Position_Vector("O","M");
cout << " O_R1= "<< O_R1<<endl;
cout << " O_R2= "<< O_R2<<endl;

	Drawing3D * VectorO_P = sys.new_Drawing3D("VectorO_P",&O_P,Point_O,1.0,0.0,1.0,1.0);

	Drawing3D * VectorO_R2 = sys.new_Drawing3D("VectorO_R2",&O_R2,Point_O,0.0,0.0,1.0,1.0);
	Drawing3D * VectorO_R1 = sys.new_Drawing3D("VectorO_R1",&O_R1,Point_O,1.0,0.0,1.0,1.0);
	Drawing3D * VectorR1_J1 = sys.new_Drawing3D("VectorR1_J1",&R1_J1,R1,1.0,0.0,1.0,1.0);
	Drawing3D * VectorR2_J2 = sys.new_Drawing3D("VectorR2_J2",&R2_J2,R2,1.0,0.0,1.0,1.0);
	Drawing3D * VectorO_M = sys.new_Drawing3D("VectorO_M",&O_M,Point_O,1.0,0.0,1.0,1.0);
	
	Drawing3D * VectorM_M1 = sys.new_Drawing3D("VectorM_M1",&M_M1,M,1.0,0.0,1.0,1.0);//mainllar
	Drawing3D * VectorM_M2 = sys.new_Drawing3D("VectorM_M2",&M_M2,M,1.0,0.0,1.0,1.0);//manillar
	
	
	Drawing3D * VectorR1_C1 = sys.new_Drawing3D("VectorR1_C1",&R1_C1,R1,1.0,0.0,1.0,1.0);
	Drawing3D * VectorR1_C2 = sys.new_Drawing3D("VectorR1_C2",&R1_C2,R1,1.0,0.0,1.0,1.0);
    Drawing3D * VectorR2_D2 = sys.new_Drawing3D("VectorR2_D2",&R2_D2,R2,1.0,0.0,1.0,1.0);
	Drawing3D * VectorR2_D1 = sys.new_Drawing3D("VectorR2_D1",&R2_D1,R2,1.0,0.0,1.0,1.0);
	
	Drawing3D * VectorC1_D1 = sys.new_Drawing3D("VectorC1_D1",&C1_D1,C1,1.0,0.0,1.0,1.0);
	Drawing3D * VectorC2_D2 = sys.new_Drawing3D("VectorC2_D2",&C2_D2,C2,1.0,0.0,1.0,1.0);
	
	
	
	//Drawing3D * VectorO_J1 = sys.new_Drawing3D("VectorO_J1",&O_J1,Point_O,1.0,0.0,1.0,1.0);
	//Drawing3D * VectorO_J2 = sys.new_Drawing3D("VectorO_J2",&O_J2,Point_O,1.0,0.0,1.0,1.0);
	
	
	//Drawing3D * VectorP_R1 = sys.new_Drawing3D("VectorP_R1",&P_R1,P,1.0,0.0,1.0,1.0);

	//Drawing3D * VectorP_R2 = sys.new_Drawing3D("VectorP_R2",&P_R2,P,0.0,0.0,1.0,1.0);

	//Drawing3D * VectorO_M = sys.new_Drawing3D("VectorO_M",&O_M,Point_O,0.0,1.0,0.0,1.0);
	//Drawing3D * VectorP_M = sys.new_Drawing3D("VectorP_M",&P_M,P,1.0,1.0,0.0,1.0);

	//Vector3D PHI1 = O_A1 + A1_B1+ B1_B1L + B1L_C1L - (O_P + P_C1 + C1_C1L);
	//Vector3D PHI1R = O_A1 + A1_B1+ B1_B1R + B1R_C1R - (O_P + P_C1 + C1_C1R);
	Vector3D PHI1 = O_R1 - O_P - P_R1;
	Vector3D PHI2 = O_R2 - O_P - P_R2;
	Vector3D PHI3 = O_M - O_P - P_M;
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

    	state = rho1, rho2, xp, yp, zp, *drho1, *drho2, *dxp, *dyp, *dzp, *ddrho1, *ddrho2, *ddxp, *ddyp, *ddzp;
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


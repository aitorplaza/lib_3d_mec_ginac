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
	symbol_numeric rho1 = *sys.new_Coordinate("rho1","drho1","ddrho1", 0.0 , 0.0 , 0.0);//cabeceo de la base
	symbol_numeric rho2 = *sys.new_Coordinate("rho2","drho2","ddrho2", 0.4 , 0.0 , 0.0);//coordenadas de la rueda 1
	symbol_numeric rho3 = *sys.new_Coordinate("rho3","drho3","ddrho3", 0.4 , 0.0 , 0.0);//cooerdenadas de las rueda 2

	symbol_numeric phi1 = *sys.new_Coordinate("phi1","dphi1","ddphi1", 0.5 , 0.0 , 0.0);//giro en z de la base

	symbol_numeric theta1 = *sys.new_Coordinate("theta1","dtheta1","ddtheta1", 0.0, 0.0 , 0.0); //giro del manillar


	symbol_numeric xp = *sys.new_Coordinate("xp","dxp","ddxp", 0.0, 0.0 , 0.0);//coodenadas del centro plataforma
	symbol_numeric yp = *sys.new_Coordinate("yp","dyp","ddyp", 0.0, 0.0 , 0.0);
	symbol_numeric zp = *sys.new_Coordinate("zp","dzp","ddzp", 0.0, 0.0 , 0.0);

      	symbol_numeric *drho1=sys.get_Velocity("drho1");//velovidades  cabeceo plataforma
	symbol_numeric *drho2=sys.get_Velocity("drho2");//velocidades rueda 1
	symbol_numeric *drho3=sys.get_Velocity("drho3");//velocidades rueda 2

    	symbol_numeric *dphi1=sys.get_Velocity("dphi1");//velovidades giro  plataforma	

	symbol_numeric *dtheta1=sys.get_Velocity("dtheta1");//velocidades manillar
	


	symbol_numeric *dxp=sys.get_Velocity("dxp");//velocidades centro plataforma
	symbol_numeric *dyp=sys.get_Velocity("dyp");
	symbol_numeric *dzp=sys.get_Velocity("dzp");

	symbol_numeric *ddrho1=sys.get_Acceleration("ddrho1");
	symbol_numeric *ddrho2=sys.get_Acceleration("ddrho2");
	symbol_numeric *ddrho3=sys.get_Acceleration("ddrho3");

	symbol_numeric *ddphi1=sys.get_Acceleration("ddphi1");//aceleracion plataforma
	
	symbol_numeric *ddtheta1=sys.get_Acceleration("ddtheta1");// aceleracion manillar
	

	symbol_numeric *ddxp=sys.get_Acceleration("ddxp");//aceleracion cdm
	symbol_numeric *ddyp=sys.get_Acceleration("ddyp");
	symbol_numeric *ddzp=sys.get_Acceleration("ddzp");

	lst coord_indep_init;
	lst vel_indep_init;
	
// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	symbol_numeric R  = *sys.new_Parameter("R",200); //radio de la rueda
	symbol_numeric h  = *sys.new_Parameter("r",0.30);//altura de la plataforma
	symbol_numeric l1 = *sys.new_Parameter("l1",300);//anchura de la plataforma
	symbol_numeric l2 = *sys.new_Parameter("l2",350);//longitud de la plataforma
	symbol_numeric l3 = *sys.new_Parameter("l3",600);//espesor de la plataforma
	symbol_numeric d = *sys.new_Parameter("d",0.022);
	symbol_numeric alpha = *sys.new_Parameter("alpha",2.0/3.0*PI); //120º=2/3*PI
	symbol_numeric beta = *sys.new_Parameter("beta",-2.0/3.0*PI); 

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

 
	sys.new_Base("Plataforma1","xyz",0,0,1,0);//defino primera base plataforma
	sys.new_Base("Plataforma2","Plataforma1",0,1,0,0);//defino segunda base plataforma

   	sys.new_Base("RUEDA1","xyz",0,0,1,pi/2);//defino base rueda1
	sys.new_Base("RUEDA2","xyz",0,0,1,-pi/2);//defino base rueda 2	

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
	Vector3D O_M = *sys.new_Vector3D("O_M",0,0,l2,"Manillar"); //EJE MANILLAR
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
	Point * R1 = sys.new_Point("R1","O",&O_R1); // definir centro Eje 1
	Point * R2 = sys.new_Point("R2","O",&O_R2); //defino centro Eje2
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

	// Dynamic Parameters of Manillar (all three Manillars are identical) (MANILLAR)

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

	// Dynamic Parameters of Eje 

    	symbol_numeric  mEje = *sys.new_Parameter("mEje",1.0);

	symbol_numeric  mxEje = *sys.new_Parameter("mxEje",0.0);
    	symbol_numeric  myEje = *sys.new_Parameter("myEje",0.0);
	symbol_numeric  mzEje = *sys.new_Parameter("mzEje",0.0);

    	symbol_numeric  IxxEje = *sys.new_Parameter("IxxEje",1.0);
	symbol_numeric  IxyEje = *sys.new_Parameter("IxyEje",0.0);
    	symbol_numeric  IyyEje = *sys.new_Parameter("IyyEje",5.0);
	symbol_numeric  IxzEje = *sys.new_Parameter("IxzEje",0.0);
    	symbol_numeric  IzzEje = *sys.new_Parameter("IzzEje",1.0);
	symbol_numeric  IyzEje = *sys.new_Parameter("IyzEje",0.0);


	// Dynamic Parameters of Rueda 1(rueda1)

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

	// Dynamic Parameters of Rueda 2(rueda2)

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

	

	// Dynamic Parameters of Plataforma or Platform

    symbol_numeric  mPlataforma = *sys.new_Parameter("mPlataforma",1.0);

	symbol_numeric  mxPlataforma = *sys.new_Parameter("mxPlataforma",0.0);
    symbol_numeric  myPlataforma = *sys.new_Parameter("myPlataforma",0.0);
	symbol_numeric  mzPlataforma = *sys.new_Parameter("mzPlataforma",0.0);

    symbol_numeric  IxxPlataforma = *sys.new_Parameter("IxxPlataforma",1.0);
	symbol_numeric  IxyPlataforma = *sys.new_Parameter("IxyPlataforma",0.0);
    symbol_numeric  IyyPlataforma = *sys.new_Parameter("IyyPlataforma",1.0);
	symbol_numeric  IxzPlataforma = *sys.new_Parameter("IxzPlataforma",0.0);
    symbol_numeric  IzzPlataforma = *sys.new_Parameter("IzzPlataforma",1.0);
	symbol_numeric  IyzPlataforma = *sys.new_Parameter("IyzPlataforma",0.0);

	//Gravity Center Vectors    

	//Vector3D M_GCarrier1= *sys.new_Vector3D("B1_GCarrier1",mxCarrier/mCarrier,myCarrier/mCarrier,mzCarrier/mCarrier,"Plataforma");
	//Vector3D B2_GCarrier2= *sys.new_Vector3D("B2_GCarrier2",mxCarrier/mCarrier,myCarrier/mCarrier,mzCarrier/mCarrier,"BB2c");
	//Vector3D B3_GCarrier3= *sys.new_Vector3D("B3_GCarrier3",mxCarrier/mCarrier,myCarrier/mCarrier,mzCarrier/mCarrier,"BB3c");
	
	Vector3D C1_GRueda1= *sys.new_Vector3D("C1_GRueda1",0,0,0,"RUEDA1");
	Vector3D C2_GRueda2= *sys.new_Vector3D("C2_GRueda2",0,0,0,"RUEDA2");
	Vector3D P_GEje=*sys.new_Vector3D("P_GEje" ,0,0,0,"Plataforma2");
	//Vector3D B1_GRod1= *sys.new_Vector3D("B1_GRod1",0,-l1/2,0,"BB1");
	Vector3D M_GRuedaM= *sys.new_Vector3D("M_GRuedaM",0,0,l2/2,"Manillar");
	Vector3D P_GPlataforma= *sys.new_Vector3D("P_GPlataforma",0,0,0,"Plataforma2");

	//Inertia Tensors		
	
    Tensor3D IManillar = *sys.new_Tensor3D("IManillar",(ex)IxxManillar,(ex)IxyManillar,(ex)IxzManillar,(ex)IxyManillar,(ex)IyyManillar,(ex)IyzManillar,(ex)IxzManillar,(ex)IyzManillar,(ex)IzzManillar,"Manillar");


	Tensor3D IEje = *sys.new_Tensor3D("IEje",(ex)IxxEje,(ex)IxyEje,(ex)IxzEje,(ex)IxyEje,(ex)IyyEje,(ex)IyzEje,(ex)IxzEje,(ex)IyzEje,(ex)IzzEje,"Plataforma2");

	Tensor3D IRueda1 = *sys.new_Tensor3D("IRueda1",(ex)IxxRueda1,(ex)IxyRueda1,(ex)IxzRueda1,(ex)IxyRueda1,(ex)IyyRueda1,(ex)IyzRueda1,(ex)IxzRueda1,(ex)IyzRueda1,(ex)IzzRueda1,"RUEDA1");

	Tensor3D IRueda2 = *sys.new_Tensor3D("IRueda2",(ex)IxxRueda2,(ex)IxyRueda2,(ex)IxzRueda2,(ex)IxyRueda2,(ex)IyyRueda2,(ex)IyzRueda2,(ex)IxzRueda2,(ex)IyzRueda2,(ex)IzzRueda2,"RUEDA2");

	Tensor3D IPlataforma = *sys.new_Tensor3D("IPlataforma",(ex)IxxPlataforma,(ex)IxyPlataforma,(ex)IxzPlataforma,(ex)IxyPlataforma,(ex)IyyPlataforma,(ex)IyzPlataforma,(ex)IxzPlataforma,(ex)IyzPlataforma,(ex)IzzPlataforma,"Plataforma2");

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Manillar = sys.new_Frame("Fra_Manillar","M","Manillar");
	Frame * Fra_Eje = sys.new_Frame("Fra_Eje","P","Plataforma2");
	Frame * Fra_Rueda1 = sys.new_Frame("Fra_Rueda1","R1","RUEDA1");
	Frame * Fra_Rueda2 = sys.new_Frame("Fra_Rueda2","R2","RUEDA2");
	

	Frame * Fra_Plataforma = sys.new_Frame("Fra_Plataforma","P","Plataforma2");

// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	//Solid * Carrier1 = sys.new_Solid("Carrier1","B1","BB1c","mCarrier","B1_GCarrier1","ICarrier1");
	//Solid * Carrier2 = sys.new_Solid("Carrier2","B2","BB2c","mCarrier","B2_GCarrier2","ICarrier2");
	//Solid * Carrier3 = sys.new_Solid("Carrier3","B3","BB3c","mCarrier","B3_GCarrier3","ICarrier3");
	
	
	Solid * Manillar = sys.new_Solid("Manillar","O","Manillar","mManillar","M_GRuedaM","IManillar");
	Solid * Eje = sys.new_Solid("Eje","P","Plataforma2","mEje","P_GEje","IEje");
	Solid * Rueda1 = sys.new_Solid("Rueda1","R1","RUEDA1","mRueda1","C1_GRueda1","IRueda1");
	Solid * Rueda2 = sys.new_Solid("Rueda2","R2","RUEDA2","mRueda2","C2_GRueda2","IRueda2");
	
	Solid * Plataforma = sys.new_Solid("Plataforma","R2","RUEDA1","mPlataforma","P_GPlataforma","IPlataforma");



// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

	//Drawing3D * Ground3D = sys.new_Drawing3D("Ground3D", "O", "xyz","./solids/body.osgt");

	//Drawing3D * Carrier13D = sys.new_Drawing3D("Carrier13D", Carrier1,"./solids/carriage.osgt");
	//Drawing3D * Carrier23D = sys.new_Drawing3D("Carrier23D", Carrier2,"./solids/carriage.osgt");
	//Drawing3D * Carrier33D = sys.new_Drawing3D("Carrier33D", Carrier3,"./solids/carriage.osgt");

	Drawing3D * Manillar3D = sys.new_Drawing3D("Manillar3D", Manillar,"./solids/Manillar.osg");
	Drawing3D * Eje3D = sys.new_Drawing3D("Eje3D", Eje,"./solids/eje.osg");
	Drawing3D * Rueda13D = sys.new_Drawing3D("Rueda13D", Rueda1,"./solids/Rueda.osg");
	Drawing3D * Rueda23D = sys.new_Drawing3D("Rueda23D", Rueda2,"./solids/Rueda.osg");
	Drawing3D * Plataforma3D = sys.new_Drawing3D("Plataforma3D", Plataforma,"./solids/Plataforma.osg");	
	
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


// ************************************************************************************************
// 	Input Vector  REPASAR
// ************************************************************************************************

	cout << "Input Vector" << endl;

	symbol_numeric FManillar1z = *sys.new_Input("FManillar1z",0.0);
	symbol_numeric FManillar2z = *sys.new_Input("FManillar2z",0.0);
	symbol_numeric FManillar3z = *sys.new_Input("FManillar3z",0.0);

	Vector3D FManillar1 = *sys.new_Vector3D("FManillar1",0,0,FManillar1z,"Plataforma2");
	Vector3D MManillar1 = *sys.new_Vector3D("MManillar1",0,0,0, "Plataforma2");

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
	Wrench3D * Gravity_Manillar= sys.Gravity_Wrench("Manillar");
	Wrench3D * Gravity_Rueda1= sys.Gravity_Wrench("Rueda1");
	Wrench3D * Gravity_Rueda2 = sys.Gravity_Wrench("Rueda2");
	Wrench3D * Gravity_Plataforma = sys.Gravity_Wrench("Plataforma");

	//	Inertia
	Wrench3D * Inertia_Manillar = sys.Inertia_Wrench("Manillar");
	Wrench3D * Inertia_Rueda1 = sys.Inertia_Wrench("Rueda1");
	Wrench3D * Inertia_Rueda2 = sys.Inertia_Wrench("Rueda2");
	Wrench3D * Inertia_Plataforma = sys.Inertia_Wrench("Plataforma");

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

	//Vector3D rho1 = O_A1 + A1_B1+ B1_B1L + B1L_C1L - (O_P + P_C1 + C1_C1L);
	//Vector3D rho1R = O_A1 + A1_B1+ B1_B1R + B1R_C1R - (O_P + P_C1 + C1_C1R);
	Vector3D rho1 = O_R1 - O_P - P_R1;
	Vector3D phi1 = O_R2 - O_P - P_R2;
	Vector3D PHI3 = O_M - O_P - P_M;
	Matrix Phi(9,1);
	Phi(0,0) = rho1 (0,0);
	Phi(1,0) = rho1 (1,0);
	Phi(2,0) = rho1 (2,0);
	Phi(3,0) = phi1 (0,0);
	Phi(4,0) = phi1 (1,0);
	Phi(5,0) = phi1 (2,0);
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

    	state = rho3, rho2, xp, yp, zp, *drho3, *drho2, *dxp, *dyp, *dzp, *ddrho3, *ddrho2, *ddxp, *ddyp, *ddzp;
//   	state = rho3, rho2, rho3, rho1, phi1, phi3, theta1, theta2, theta3, xp, yp, zp, *drho3, *drho2, *drho3, *drho1, *dphi1, *dphi3, *dtheta1, *dtheta2, *dtheta3, *dxp, *dyp, *dzp, *ddrho3, *ddrho2, *ddrho3, *ddrho1, *ddphi1, *ddphi3, *ddtheta1, *ddtheta2, *ddtheta3, *ddxp, *ddyp, *ddzp;
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


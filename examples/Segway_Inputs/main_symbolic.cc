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
cout << "*                   Segway                     *" << endl;
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
	symbol_numeric rho1 = *sys.new_Coordinate("rho1","drho1","ddrho1", 0.0 , 0.0 , 0.0); //Giro eje en z

	symbol_numeric phi1 = *sys.new_Coordinate("phi1","dphi1","ddphi1", 0.0 , 0.0 , 0.0); //Cabeceo plataforma
	symbol_numeric phi2 = *sys.new_Coordinate("phi2","dphi2","ddphi2", 0.0 , 0.0 , 0.0); //Giro rueda izq
	symbol_numeric phi3 = *sys.new_Coordinate("phi3","dphi3","ddphi3", 0.0 , 0.0 , 0.0); //Giro rueda dcha

	symbol_numeric theta1 = *sys.new_Coordinate("theta1","dtheta1","ddtheta1", 0.5 , 0.0 , 0.0); //Giro manillar

	symbol_numeric xp = *sys.new_Coordinate("xp","dxp","ddxp", 0.0, 0.0 , 0.0);
	symbol_numeric yp = *sys.new_Coordinate("yp","dyp","ddyp", 0.0, 0.0 , 0.0);
	symbol_numeric zp = *sys.new_Coordinate("zp","dzp","ddzp", 0.0, 0.0 , 0.0);

	symbol_numeric ycdg = *sys.new_Coordinate("ycdg","dycdg","ddycdg", -1.205 , 0.0 , 0.0);
	symbol_numeric zcdg = *sys.new_Parameter("zcdg", 0.0);

	symbol_numeric ycdg_input  = *sys.new_Input("ycdg_input", 0.0);

	symbol_numeric *drho1=sys.get_Velocity("drho1");

	symbol_numeric *dphi1=sys.get_Velocity("dphi1");
	symbol_numeric *dphi2=sys.get_Velocity("dphi2");
	symbol_numeric *dphi3=sys.get_Velocity("dphi3");

	symbol_numeric *dtheta1=sys.get_Velocity("dtheta1");

	symbol_numeric *dxp=sys.get_Velocity("dxp");
	symbol_numeric *dyp=sys.get_Velocity("dyp");
	symbol_numeric *dzp=sys.get_Velocity("dzp");

	symbol_numeric *dycdg=sys.get_Velocity("dycdg");

	symbol_numeric *ddrho1=sys.get_Acceleration("ddrho1");

	symbol_numeric *ddphi1=sys.get_Acceleration("ddphi1");
	symbol_numeric *ddphi2=sys.get_Acceleration("ddphi2");
	symbol_numeric *ddphi3=sys.get_Acceleration("ddphi3");

	symbol_numeric *ddtheta1=sys.get_Acceleration("ddtheta1");

	symbol_numeric *ddxp=sys.get_Acceleration("ddxp");
	symbol_numeric *ddyp=sys.get_Acceleration("ddyp");
	symbol_numeric *ddzp=sys.get_Acceleration("ddzp");

	symbol_numeric *ddycdg=sys.get_Acceleration("ddycdg");



	lst coord_indep_init;
	lst vel_indep_init;
	
// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	symbol_numeric R  = *sys.new_Parameter("R",0.200); //Radio rueda
	symbol_numeric man  = *sys.new_Parameter("man",1.200);//Altura manillar
	symbol_numeric r  = *sys.new_Parameter("r",0.300); //Radio manillar
	symbol_numeric l1 = *sys.new_Parameter("l1",0.680); //Longitud plataforma
	symbol_numeric l2 = *sys.new_Parameter("l2",0.500);  //Anchura plataforma
	symbol_numeric l3 = *sys.new_Parameter("l3",0.145);  //Altura plataforma
	symbol_numeric d = *sys.new_Parameter("d",0.050); //Distancia superficie plataforma - eje
	symbol_numeric le = *sys.new_Parameter("le",0.750); //Longitud eje
	symbol_numeric cm = *sys.new_Parameter("cm",0.180); //Centro eje-manillar (horizontal)
	symbol_numeric rm = *sys.new_Parameter("rm",0.010); //Rebaje manillar (vertical)
	symbol_numeric hcdg = *sys.new_Parameter("hcdg",1.18); //Rebaje manillar (vertical)
	symbol_numeric alpha = *sys.new_Parameter("alpha",2.0/3.0*PI); //120º=2/3*PI
	symbol_numeric beta = *sys.new_Parameter("beta",-2.0/3.0*PI); 

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************
	
 	sys.new_Base("B_Eje","xyz",0,0,1,rho1); //Sigue al eje en plano xy

	sys.new_Base("B_Plataforma","B_Eje",1,0,0,phi1); //Sigue cabeceo plataforma;
	sys.new_Base("B_RuedaIzq","B_Plataforma",1,0,0,phi2); //Rueda izq
	sys.new_Base("B_RuedaDcha","B_Plataforma",1,0,0,phi3); //Rueda dcha

	sys.new_Base("B_Manillar","B_Plataforma",0,1,0,theta1);

cout << "base = "<< sys.Rotation_Matrix(sys.get_Base("B_Plataforma"),sys.get_Base("B_Manillar"))<<endl;

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	Vector3D O_P = *sys.new_Vector3D("O_P",xp,yp,zp,"xyz");

	Vector3D P_A1 = *sys.new_Vector3D("P_A1",le/2,0,0,"B_Eje");  //Extremo izq eje
	Vector3D P_A2 = *sys.new_Vector3D("P_A2",-le/2,0,0,"B_Eje"); //Extremo dcho eje
	
	Vector3D A1_J1 = *sys.new_Vector3D("A1_J1",0,0,-R,"B_Eje"); //Ptos de contacto rueda-suelo
	Vector3D A2_J2 = *sys.new_Vector3D("A2_J2",0,0,-R,"B_Eje");
 
	Vector3D P_C = *sys.new_Vector3D("P_C",0,0,d,"B_Plataforma"); //Centro superficie plataforma

	Vector3D C_CDG = *sys.new_Vector3D("C_CDG",0,ycdg,zcdg,"B_Plataforma");

	Vector3D C_MAN = *sys.new_Vector3D("C_MAN",0,cm,-rm,"B_Plataforma"); //-10mm en z
        Vector3D MAN_S0 = *sys.new_Vector3D("MAN_S0",0,0,man,"B_Manillar"); //Centro manillar
        Vector3D S0_S1 = *sys.new_Vector3D("S0_S1",r,0,0,"B_Manillar"); //Extremo izq manillar
        Vector3D S0_S2 = *sys.new_Vector3D("S0_S2",-r,0,0,"B_Manillar"); //Extremo dcho manillar


// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * P = sys.new_Point("P","O",&O_P);

	Point * A1 = sys.new_Point("A1","P",&P_A1);
	Point * A2 = sys.new_Point("A2","P",&P_A2);

	Point * J1 = sys.new_Point("J1","A1",&A1_J1);
	Point * J2 = sys.new_Point("J2","A2",&A2_J2);

	Point * C = sys.new_Point("C","P",&P_C);

        Point * MAN = sys.new_Point("MAN","C",&C_MAN);


	Point * S0 = sys.new_Point("S0","MAN",&MAN_S0);
	Point * S1 = sys.new_Point("S1","S0",&S0_S1);
	Point * S2 = sys.new_Point("S2","S0",&S0_S2);

	Point * CDG = sys.new_Point("CDG","C",&C_CDG);

// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Viscosity
       	symbol_numeric  Cvis1 = *sys.new_Parameter("Cvis1",1.0);
        symbol_numeric  Cvis2 = *sys.new_Parameter("Cvis2",1.0);
        symbol_numeric  Cvis3 = *sys.new_Parameter("Cvis3",1.0);

	// Dynamic Parameters of Plataforma (all three Plataformas are identical)

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

	// Dynamic Parameters of Rueda 1

    	symbol_numeric  mRuedaIzq = *sys.new_Parameter("mRuedaIzq",1.0);

	symbol_numeric  mxRuedaIzq = *sys.new_Parameter("mxRuedaIzq",0.0);
    	symbol_numeric  myRuedaIzq = *sys.new_Parameter("myRuedaIzq",0.0);
	symbol_numeric  mzRuedaIzq = *sys.new_Parameter("mzRuedaIzq",0.0);

    	symbol_numeric  IxxRuedaIzq = *sys.new_Parameter("IxxRuedaIzq",1.0);
	symbol_numeric  IxyRuedaIzq = *sys.new_Parameter("IxyRuedaIzq",0.0);
    	symbol_numeric  IyyRuedaIzq = *sys.new_Parameter("IyyRuedaIzq",5.0);
	symbol_numeric  IxzRuedaIzq = *sys.new_Parameter("IxzRuedaIzq",0.0);
    	symbol_numeric  IzzRuedaIzq = *sys.new_Parameter("IzzRuedaIzq",1.0);
	symbol_numeric  IyzRuedaIzq = *sys.new_Parameter("IyzRuedaIzq",0.0);

	// Dynamic Parameters of Rueda 2

    	symbol_numeric  mRuedaDcha = *sys.new_Parameter("mRuedaDcha",1.0);

	symbol_numeric  mxRuedaDcha = *sys.new_Parameter("mxRuedaDcha",0.0);
    	symbol_numeric  myRuedaDcha = *sys.new_Parameter("myRuedaDcha",0.0);
	symbol_numeric  mzRuedaDcha = *sys.new_Parameter("mzRuedaDcha",0.0);

	symbol_numeric  IxxRuedaDcha = *sys.new_Parameter("IxxRuedaDcha",1.0);
	symbol_numeric  IxyRuedaDcha = *sys.new_Parameter("IxyRuedaDcha",0.0);
	symbol_numeric  IyyRuedaDcha = *sys.new_Parameter("IyyRuedaDcha",1.0);
	symbol_numeric  IxzRuedaDcha = *sys.new_Parameter("IxzRuedaDcha",0.0);
	symbol_numeric  IzzRuedaDcha = *sys.new_Parameter("IzzRuedaDcha",1.0);
	symbol_numeric  IyzRuedaDcha = *sys.new_Parameter("IyzRuedaDcha",0.0);

	// Dynamic Parameters of Eje

	symbol_numeric  mEje = *sys.new_Parameter("mEje",1.0);

	symbol_numeric  mxEje = *sys.new_Parameter("mxEje",0.0);
	symbol_numeric  myEje = *sys.new_Parameter("myEje",0.0);
	symbol_numeric  mzEje = *sys.new_Parameter("mzEje",1.0);

	symbol_numeric  IxxEje = *sys.new_Parameter("IxxEje",1.0);
	symbol_numeric  IxyEje = *sys.new_Parameter("IxyEje",0.0);
	symbol_numeric  IyyEje = *sys.new_Parameter("IyyEje",1.0);
	symbol_numeric  IxzEje = *sys.new_Parameter("IxzEje",0.0);
	symbol_numeric  IzzEje = *sys.new_Parameter("IzzEje",1.0);
	symbol_numeric  IyzEje = *sys.new_Parameter("IyzEje",0.0);

	// Dynamic Parameters of Manillar

	symbol_numeric  mManillar = *sys.new_Parameter("mManillar",1.0);

	symbol_numeric  mxManillar = *sys.new_Parameter("mxManillar",1.0);
	symbol_numeric  myManillar = *sys.new_Parameter("myManillar",1.0);
	symbol_numeric  mzManillar = *sys.new_Parameter("mzManillar",1.0);

	symbol_numeric  IxxManillar = *sys.new_Parameter("IxxManillar",1.0);
	symbol_numeric  IxyManillar = *sys.new_Parameter("IxyManillar",0.0);
	symbol_numeric  IyyManillar = *sys.new_Parameter("IyyManillar",1.0);
	symbol_numeric  IxzManillar = *sys.new_Parameter("IxzManillar",0.0);
	symbol_numeric  IzzManillar = *sys.new_Parameter("IzzManillar",1.0);
	symbol_numeric  IyzManillar = *sys.new_Parameter("IyzManillar",0.0);

	// Dynamic Parameters of Rider

	symbol_numeric  mRider = *sys.new_Parameter("mRider",1.0);

	symbol_numeric  mxRider = *sys.new_Parameter("mxRider",1.0);
	symbol_numeric  myRider = *sys.new_Parameter("myRider",1.0);
	symbol_numeric  mzRider = *sys.new_Parameter("mzRider",1.0);

	symbol_numeric  IxxRider = *sys.new_Parameter("IxxRider",1.0);
	symbol_numeric  IxyRider = *sys.new_Parameter("IxyRider",0.0);
	symbol_numeric  IyyRider = *sys.new_Parameter("IyyRider",1.0);
	symbol_numeric  IxzRider = *sys.new_Parameter("IxzRider",0.0);
	symbol_numeric  IzzRider = *sys.new_Parameter("IzzRider",1.0);
	symbol_numeric  IyzRider = *sys.new_Parameter("IyzRider",0.0);

	//Gravity Center Vectors    

	Vector3D P_GPlataforma= *sys.new_Vector3D("P_GPlataforma",mxPlataforma/mPlataforma,myPlataforma/mPlataforma,mzPlataforma/mPlataforma,"B_Plataforma");

	Vector3D A1_GRuedaIzq= *sys.new_Vector3D("A1_GRuedaIzq",0,0,0,"B_RuedaIzq");
	Vector3D A2_GRuedaDcha= *sys.new_Vector3D("A2_GRuedaDcha",0,0,0,"B_RuedaDcha");
	Vector3D P_GEje= *sys.new_Vector3D("P_GEje",0,0,0,"B_Eje");

	Vector3D M_GManillar= *sys.new_Vector3D("M_GManillar",0,0,man/2,"B_Manillar");
	
	Vector3D CDG_GRider= *sys.new_Vector3D("CDG_GRider",mxRider/mRider,myRider/mRider,mzRider/mRider,"B_Plataforma");


	//Inertia Tensors		
	
	Tensor3D IPlataforma = *sys.new_Tensor3D("IPlataforma",(ex)IxxPlataforma,(ex)IxyPlataforma,(ex)IxzPlataforma,(ex)IxyPlataforma,(ex)IyyPlataforma,(ex)IyzPlataforma,(ex)IxzPlataforma,(ex)IyzPlataforma,(ex)IzzPlataforma,"B_Plataforma");

	Tensor3D IRuedaIzq = *sys.new_Tensor3D("IRuedaIzq",(ex)IxxRuedaIzq,(ex)IxyRuedaIzq,(ex)IxzRuedaIzq,(ex)IxyRuedaIzq,(ex)IyyRuedaIzq,(ex)IyzRuedaIzq,(ex)IxzRuedaIzq,(ex)IyzRuedaIzq,(ex)IzzRuedaIzq,"B_RuedaIzq");

	Tensor3D IRuedaDcha = *sys.new_Tensor3D("IRuedaDcha",(ex)IxxRuedaDcha,(ex)IxyRuedaDcha,(ex)IxzRuedaDcha,(ex)IxyRuedaDcha,(ex)IyyRuedaDcha,(ex)IyzRuedaDcha,(ex)IxzRuedaDcha,(ex)IyzRuedaDcha,(ex)IzzRuedaDcha,"B_RuedaDcha");

	Tensor3D IEje = *sys.new_Tensor3D("IEje",(ex)IxxEje,(ex)IxyEje,(ex)IxzEje,(ex)IxyEje,(ex)IyyEje,(ex)IyzEje,(ex)IxzEje,(ex)IyzEje,(ex)IzzEje,"B_Eje");

	Tensor3D IManillar = *sys.new_Tensor3D("IManillar",(ex)IxxManillar,(ex)IxyManillar,(ex)IxzManillar,(ex)IxyManillar,(ex)IyyManillar,(ex)IyzManillar,(ex)IxzManillar,(ex)IyzManillar,(ex)IzzManillar,"B_Manillar");

	Tensor3D IRider = *sys.new_Tensor3D("IRider",(ex)IxxRider,(ex)IxyRider,(ex)IxzRider,(ex)IxyRider,(ex)IyyRider,(ex)IyzRider,(ex)IxzRider,(ex)IyzRider,(ex)IzzRider,"B_Plataforma");

// ************************************************************************************************
//	Define Frames
// **********************************************************************************************
	Frame * Fra_Plataforma = sys.new_Frame("Fra_Plataforma","P","B_Plataforma");

	Frame * Fra_RuedaIzq = sys.new_Frame("Fra_RuedaIzq","A1","B_RuedaIzq");
	Frame * Fra_RuedaDcha = sys.new_Frame("Fra_RuedaDcha","A2","B_RuedaDcha");
	Frame * Fra_Eje = sys.new_Frame("Fra_Eje","P","B_Eje");

	Frame * Fra_Manillar = sys.new_Frame("Fra_Manillar","MAN","B_Manillar");

	Frame * Fra_Rider = sys.new_Frame("Fra_Rider","CDG","B_Plataforma");


// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	Solid * Plataforma = sys.new_Solid("Plataforma","P","B_Plataforma","mPlataforma","P_GPlataforma","IPlataforma");
	
	Solid * RuedaIzq = sys.new_Solid("RuedaIzq","A1","B_RuedaIzq","mRuedaIzq","A1_GRuedaIzq","IRuedaIzq");
	Solid * RuedaDcha = sys.new_Solid("RuedaDcha","A2","B_RuedaDcha","mRuedaDcha","A2_GRuedaDcha","IRuedaDcha");

	//Solid * Eje = sys.new_Solid("Eje","P","B_Eje","mEje","P_GEje","IEje");
	
	Solid * Manillar = sys.new_Solid("Manillar","MAN","B_Manillar","mManillar","M_GManillar","IManillar");

	Solid * Rider = sys.new_Solid("Rider","CDG","B_Plataforma","mRider","CDG_GRider","IRider");


// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

	Drawing3D * Plataforma3D = sys.new_Drawing3D("Plataforma3D", Plataforma,"./solids/Plataformam.stl");

	Drawing3D * RuedaIzq3D = sys.new_Drawing3D("RuedaIzq3D", RuedaIzq,"./solids/Rueda1m.stl");
	Drawing3D * RuedaDcha3D = sys.new_Drawing3D("RuedaDcha3D", RuedaDcha,"./solids/Rueda2m.stl");
	//Drawing3D * Eje3D = sys.new_Drawing3D("Eje3D", Eje,"./solids/Ejem.stl");

	Drawing3D * Manillar3D = sys.new_Drawing3D("Manillar3D", Manillar,"./solids/Manillarm.stl");	
        //Drawing3D * FraHeader = sys.new_Drawing3D( "FraHeader" , Fra_Header, 0.1 );

	Drawing3D * Rider3D = sys.new_Drawing3D("Rider3D",CDG,0.1,1.0,1.0,0.0,1.0);

	Drawing3D * FraABS = sys.new_Drawing3D("FraABS",Frame_abs,0.1);

	Drawing3D * Ground3D = sys.new_Drawing3D("Ground3D", "O", "xyz","./solids/ground.stl");

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


// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

	cout << "Input Vector" << endl;
	symbol_numeric MomRuedaIzq = *sys.new_Input("MomRuedaIzq",0.0);
	symbol_numeric MomRuedaDcha = *sys.new_Input("MomRuedaDcha",0.0);

	//symbol_numeric FManillarx = *sys.new_Input("FManillarx",0.0);

	Vector3D MRuedaIzq = *sys.new_Vector3D("MRuedaIzq",MomRuedaIzq,0,0, "B_RuedaIzq");
	Vector3D MRuedaDcha = *sys.new_Vector3D("MRuedaDcha",MomRuedaDcha,0,0, "B_RuedaDcha");

	//Vector3D MCarrier1 = *sys.new_Vector3D("MCarrier1",0,0,0, "BB1c");
	//Vector3D FManillar = *sys.new_Vector3D("FManillar",FManillarx,0,0,"B_Manillar");

// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************
        symbol_numeric xp_0 = *sys.new_Parameter("xp_0",0.0);
        symbol_numeric yp_0 = *sys.new_Parameter("yp_0",0.0);
        symbol_numeric zp_0 = *sys.new_Parameter("zp_0",0.0);
	symbol_numeric KMan = *sys.new_Parameter("KMan",4);
	Vector3D M_Muelle = *sys.new_Vector3D("M_Muelle",0,-theta1,0,"B_Manillar");

	Vector3D FV_RuedaIzq = *sys.new_Vector3D("FV_RuedaIzq",0,0,0,"B_RuedaIzq");
	Vector3D MV_RuedaIzq = -Cvis1 * sys.Angular_Velocity("Fra_Plataforma" , "Fra_RuedaIzq" );

	Vector3D FV_RuedaDcha = *sys.new_Vector3D("FV_RuedaDcha",0,0,0,"B_RuedaDcha");
	Vector3D MV_RuedaDcha = -Cvis2 * sys.Angular_Velocity("Fra_Plataforma" , "Fra_RuedaDcha" );

	Vector3D F_Manillar =*sys.new_Vector3D("F_Manillar",0,0,0,"B_Manillar");
	Vector3D M_Manillar = KMan * M_Muelle -Cvis3 * sys.Angular_Velocity("Fra_Plataforma" , "Fra_Manillar" );

/*
	Vector3D FV_Carrier3 = -Cvis3 * sys.Velocity_Vector("abs" ,"B3", "Carrier3" );
	Vector3D MV_Carrier3 = *sys.new_Vector3D("MV_Carrier3",0,0,0,"BB3c"); */

// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * Gravity_Plataforma = sys.Gravity_Wrench("Plataforma");

	Wrench3D * Gravity_RuedaIzq = sys.Gravity_Wrench("RuedaIzq");
	Wrench3D * Gravity_RuedaDcha = sys.Gravity_Wrench("RuedaDcha");
	//Wrench3D * Gravity_Eje = sys.Gravity_Wrench("Eje");

	Wrench3D * Gravity_Manillar = sys.Gravity_Wrench("Manillar");

	Wrench3D * Gravity_Rider = sys.Gravity_Wrench("Rider");

	//	Inertia
	Wrench3D * Inertia_Plataforma = sys.Inertia_Wrench("Plataforma");

	Wrench3D * Inertia_RuedaIzq = sys.Inertia_Wrench("RuedaIzq");
	Wrench3D * Inertia_RuedaDcha = sys.Inertia_Wrench("RuedaDcha");
	//Wrench3D * Inertia_Eje = sys.Inertia_Wrench("Eje");

	Wrench3D * Inertia_Manillar = sys.Inertia_Wrench("Manillar");

	Wrench3D * Inertia_Rider = sys.Inertia_Wrench("Rider");

	//	Constitutive
	Wrench3D * Viscosity1 = sys.new_Wrench3D ( "Viscosity1", FV_RuedaIzq, MV_RuedaIzq, A1 , RuedaIzq , "Constitutive") ;
	Wrench3D * Viscosity2 = sys.new_Wrench3D ( "Viscosity2", FV_RuedaDcha, MV_RuedaDcha, A2 , RuedaDcha , "Constitutive") ;
	Wrench3D * Viscosity1react = sys.new_Wrench3D ( "Viscosity1react", -FV_RuedaIzq, -MV_RuedaIzq, A1 , Plataforma , "Constitutive") ;
	Wrench3D * Viscosity2react = sys.new_Wrench3D ( "Viscosity2react", -FV_RuedaDcha, -MV_RuedaDcha, A2 , Plataforma , "Constitutive") ;
	Wrench3D * MuelleManillar = sys.new_Wrench3D ( "MuelleManillar", F_Manillar, M_Manillar, MAN , Manillar , "Constitutive") ;
	Wrench3D * MuelleManillarreact = sys.new_Wrench3D ( "MuelleManillarreact", -F_Manillar, -M_Manillar, MAN , Plataforma , "Constitutive") ;
	//Wrench3D * Viscosity3 = sys.new_Wrench3D ( "Viscosity3", FV_Carrier3, MV_Carrier3, B3 , Carrier3 , "Constitutive") ;

	//	External
	Wrench3D * MotorIzq = sys.new_Wrench3D ( "MotorIzq", FV_RuedaIzq, MRuedaIzq, A1 , RuedaIzq , "External") ;
	Wrench3D * MotorDcha = sys.new_Wrench3D ( "MotorDcha", FV_RuedaDcha, MRuedaDcha, A2 , RuedaDcha , "External") ;
	/*Wrench3D * Carrier1_Impulse = sys.new_Wrench3D ( "Carrier1_Impulse", FCarrier1, MCarrier1, B1 , Carrier1 , "External");
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

	//Vector3D O_M= O_P + P_M + B1_C1;

	Vector3D P_J1= sys.Position_Vector("P","J1");
	Vector3D P_J2= sys.Position_Vector("P","J2");
	Vector3D P_S0= sys.Position_Vector("P","S0");
	Vector3D P_S1= sys.Position_Vector("P","S1");
	Vector3D P_S2= sys.Position_Vector("P","S2");

	cout << " O_J1= "<< P_J1 << endl;
	cout << " O_J2= "<< P_J2 << endl;
	cout << " P_S0= "<< P_S0 << endl;
	cout << " P_S1= "<< P_S1 << endl;
	cout << " P_S2= "<< P_S2 << endl;
	cout << " O_P= "<< O_P << endl;

	Drawing3D * VectorP_J1 = sys.new_Drawing3D("VectorP_J1",&P_J1,P,1.0,0.0,1.0,1.0);
	Drawing3D * VectorP_J2 = sys.new_Drawing3D("VectorP_J2",&P_J2,P,1.0,0.0,1.0,1.0);
	Drawing3D * VectorP_S0 = sys.new_Drawing3D("VectorP_S0",&P_S0,P,1.0,0.0,1.0,1.0);
	Drawing3D * VectorP_S1 = sys.new_Drawing3D("VectorP_S1",&P_S1,P,0.0,1.0,0.0,1.0);
	Drawing3D * VectorP_S2 = sys.new_Drawing3D("VectorP_S2",&P_S2,P,0.0,1.0,0.0,1.0);
	Drawing3D * VectorO_P = sys.new_Drawing3D("VectorO_P",&O_P,Point_O,1.0,0.0,1.0,1.0);

	//Vector3D PHI1 = O_A1 + A1_B1+ B1_B1L + B1L_C1L - (O_P + P_C1 + C1_C1L);
	//Vector3D PHI1R = O_A1 + A1_B1+ B1_B1R + B1R_C1R - (O_P + P_C1 + C1_C1R);
	//Vector3D PHI1 = O_C1 - O_P - P_C1;
	//Vector3D PHI2 = O_C2 - O_P - P_C2;
	//Vector3D PHI3 = O_C3 - O_P - P_C3;*/


  	Matrix Phi(2,1);
	Phi(0,0) = zp-R;
	Phi(1,0) = ycdg-ycdg_input; //Ecuacion geomertrica del cdg ???

	Matrix dPhi_NH(3,1);
	Vector3D V_J1_R1 = sys.Velocity_Vector (Frame_abs , J1, RuedaIzq );
	Vector3D V_J2_R2 = sys.Velocity_Vector (Frame_abs , J2, RuedaDcha );
	Vector3D e1 = *sys.new_Vector3D("e1",1,0,0, "B_Eje");
	Vector3D e2 = *sys.new_Vector3D("e2",0,1,0, "B_Eje");
	
cout << " dPhi_NH= "<< dPhi_NH << endl;

	dPhi_NH(0,0) = V_J1_R1*e1;
	dPhi_NH(1,0) = V_J1_R1*e2;
	//dPhi_NH(2,0) = V_J2_R2*e1;
	dPhi_NH(2,0) = V_J2_R2*e2;

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
        sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , sys, METHOD, dPhi_NH);     
	//sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE,dPhi_NH);
	// Without restrictions (no Phi)
	//sys.Matrix_Calculation(coord_indep_init, vel_indep_init, Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);


// ************************************************************************************************
// 	Export C code for Direct Simulation 
// ************************************************************************************************

	cout << "Export C code for Direct Simulation " << endl;

        //sys.export_Dynamic_Simulation(sys, ORDER , MAPLE, PROBLEM_TYPE);
	//sys.export_Dynamic_Simulation_Common_and_Kinematics(sys, ORDER , MAPLE);
	//sys.export_Dynamic_Simulation_q(sys, ORDER , MAPLE);
	//sys.export_Dynamic_Simulation_z(sys, ORDER , MAPLE);
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

    	state = rho1, phi1, phi2, phi3, theta1, xp, yp, zp, *drho1, *dphi1, *dphi2, *dphi3, *dtheta1, *dxp, *dyp, *dzp, *ddrho1, *ddphi1, *ddphi2, *ddphi3, *ddtheta1, *ddxp, *ddyp, *ddzp;
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



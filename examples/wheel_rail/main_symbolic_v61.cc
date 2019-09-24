/*
//cp ../common_code/* .
touch atom_def.c
export LD_LIBRARY_PATH=`pwd`/../../../lib/
export PKG_CONFIG_PATH=`pwd`/../../../lib/pkgconfig
g++ -o main_DSM main_DSM.cc `pkg-config --cflags --libs lib_3d_mec_ginac-1.1 ginac cln gsl`

./main_DSM DOWN NO
*/

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

//	Define METHOD
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
cout << "*    Wheel - Rail Contact                      *" << endl;
cout << "*    v 6.1 with splines and Kalker             *" << endl;
cout << "*    rail with splines                         *" << endl;
cout << "*    Aitor Plaza Mar 2016                      *" << endl;
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

// ************************************************************************************************
//	System definition
// ************************************************************************************************

	System sys(&printError2);


// ************************************************************************************************
//	Coordinate definition
// ************************************************************************************************

    //WHEEL SET
    //Indep
    symbol_numeric x = *sys.new_Coordinate("x","dx","ddx",0.0 ,0.0,0.0);
    symbol_numeric y = *sys.new_Coordinate("y","dy","ddy",0.0 ,0.0,0.0);
    symbol_numeric b = *sys.new_Coordinate("b","db","ddb",0.0 ,0.0,0.0);
    symbol_numeric c = *sys.new_Coordinate("c","dc","ddc",0.0 ,0.0,0.0);
    
    //Dep
    symbol_numeric z = *sys.new_Coordinate("z","dz","ddz",0.5 ,0.0,0.0);
    symbol_numeric a = *sys.new_Coordinate("a","da","dda",0.0 ,0.0,0.0);   
    
    

    symbol_numeric *dx=sys.get_Velocity("dx");
    symbol_numeric *dy=sys.get_Velocity("dy");
    symbol_numeric *dz=sys.get_Velocity("dz");
    symbol_numeric *da=sys.get_Velocity("da");
    symbol_numeric *db=sys.get_Velocity("db");
    symbol_numeric *dc=sys.get_Velocity("dc");

    symbol_numeric *ddx=sys.get_Acceleration("ddx");
    symbol_numeric *ddy=sys.get_Acceleration("ddy");
    symbol_numeric *ddz=sys.get_Acceleration("ddz");
    symbol_numeric *dda=sys.get_Acceleration("dda");
    symbol_numeric *ddb=sys.get_Acceleration("ddb");
    symbol_numeric *ddc=sys.get_Acceleration("ddc");

    lst coord_indep_init;
    lst vel_indep_init;

    //coord_indep_init = x, y ,b+0.0;
    //vel_indep_init	= *dx-0.648644 ,*dy, *db-1.29572;

// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************


    //symbol_numeric b_pend = *sys.new_Parameter("b_pend",0.05);
    //symbol_numeric L_R = *sys.new_Parameter("L_R",2*1);
    //symbol_numeric LWHS= *sys.new_Parameter("L_WHS",2*1);

    // Real wheel-set
    symbol_numeric a_pend = *sys.new_Parameter("a_pend",0.0);
    symbol_numeric b_pend = *sys.new_Parameter("b_pend",0.0);
    symbol_numeric L_R = *sys.new_Parameter("L_R",1+0.035+0.035);//ancho FEVE https://es.wikipedia.org/wiki/Ancho_de_v%C3%ADa
    symbol_numeric LWHS= *sys.new_Parameter("L_WHS",0.930+0.068+0.068+0.004);

    symbol_numeric a_rail = *sys.new_Parameter("a_rail",0.0);// da problemas



// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************
    //sys.new_Base("B_Rail","xyz",0,0,0, a_pend);//Base Rail
    sys.new_Base("B_Raila","xyz",1,0,0, a_pend);//Base Rail
    sys.new_Base("B_Rail","B_Raila",0,1,0, b_pend);//Base Rail

    sys.new_Base("B_RailL","B_Rail",0,0,0, 0);//Base Rail
    sys.new_Base("B_RailR","B_Rail",0,0,0,0);//Base Rail
    //sys.new_Base("B_RailL","B_Rail",1,0,0, a_rail);//Base Rail
    //sys.new_Base("B_RailR","B_Rail",1,0,0,-a_rail);//Base Rail
    
    sys.new_Base("B_WHSc","B_Rail",0,0,1,c);
    sys.new_Base("B_WHSa","B_WHSc",1,0,0,a);
    sys.new_Base("B_WHS","B_WHSa",0,1,0,b);
    //sys.new_Base("B_WHS","B_Rail",0,1,0,b);

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

    Vector3D O_PRailR = *sys.new_Vector3D("O_PRailR",0,-L_R/2.0,0,"B_Rail");
    Vector3D O_PRailL = *sys.new_Vector3D("O_PRailL",0, L_R/2.0,0,"B_Rail");
    
    Vector3D O_PWHS = *sys.new_Vector3D("O_PWHS",x,y,z,"B_Rail");



// ************************************************************************************************
//	Define Points
// ************************************************************************************************

    Point * P_RailR = sys.new_Point("P_RailR","O",&O_PRailR);
    Point * P_RailL = sys.new_Point("P_RailL","O",&O_PRailL);
    
    Point * P_WHS   = sys.new_Point("P_WHS","O",&O_PWHS);



// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************





    symbol_numeric  mWHS = *sys.new_Parameter("mWHS",1222.0);
    symbol_numeric  I_WHSx = *sys.new_Parameter("I_WHSx",376.60);
    symbol_numeric  I_WHSy = *sys.new_Parameter("I_WHSy",79.60);
    symbol_numeric  I_WHSz = *sys.new_Parameter("I_WHSz",376.60);


    Vector3D OWHS_GWHS= *sys.new_Vector3D("OWHS_GWHS",0,0,0,"B_WHS");
    //Vector3D OWHSR_GWHSR= *sys.new_Vector3D("OWHSR_GWHSR",0,0,0,"B_WHS");
    //Vector3D OWHSL_GWHSL= *sys.new_Vector3D("OWHSL_GWHSL",0,0,0,"B_WHS");
    Tensor3D IWHS = *sys.new_Tensor3D("IWHS",(ex)I_WHSx,(ex)0,(ex)0,(ex)0,(ex)I_WHSy,(ex)0,(ex)0,(ex)0,(ex)I_WHSz,"B_WHS");



// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

    Frame * Fra_Rail = sys.new_Frame("Fra_Rail","O","B_Rail");
    Frame * Fra_WHS  = sys.new_Frame("Fra_WHS","P_WHS","B_WHS");



// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

    Solid * WHS   = sys.new_Solid("WHS","P_WHS","B_WHS","mWHS","OWHS_GWHS","IWHS");


// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

    Drawing3D * D_WHS  = sys.new_Drawing3D("D_WHS","WHS","./solids/wheel_set.stl",1,0,0,0.2);
    Drawing3D * D_Rail = sys.new_Drawing3D("D_Rail","O","B_Rail","./solids/rail_down_m.stl",1,0,1,0.2);

    /*
    Drawing3D * D_WHS   = sys.new_Drawing3D("D_WHS","WHS","./solids/axe.stl",1,0,0,0.3);
    Drawing3D * D_WHS_R = sys.new_Drawing3D("D_WHS_R","P_WHSR","B_WHS","./solids/disc.stl",1,0,0,0.3);
    Drawing3D * D_WHS_L = sys.new_Drawing3D("D_WHS_L","P_WHSL","B_WHS","./solids/disc.stl",1,0,0,0.3);

    Drawing3D * D_RailR = sys.new_Drawing3D("D_RailR","P_RailR","B_Rail","./solids/rail.stl",0,0,1,0.3);
    Drawing3D * D_RailL = sys.new_Drawing3D("D_RailL","P_RailL","B_Rail","./solids/rail.stl",0,0,1,0.3);
    */
    Drawing3D * D_FraABS = sys.new_Drawing3D("D_FraABS",Frame_abs,0.5);
    Drawing3D * D_FraWHS = sys.new_Drawing3D("D_FraWHS",Fra_WHS,0.5);


// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

    cout << "Joint Unknown Definition" << endl;

    //~ symbol_numeric lambda1 = *sys.new_Joint_Unknown("lambda1");
    //~ symbol_numeric lambda2 = *sys.new_Joint_Unknown("lambda2");
    //~ symbol_numeric lambda3 = *sys.new_Joint_Unknown("lambda3");
    //~ symbol_numeric lambda4 = *sys.new_Joint_Unknown("lambda4");
    //~ symbol_numeric lambda5 = *sys.new_Joint_Unknown("lambda5");
    //~ symbol_numeric lambda6 = *sys.new_Joint_Unknown("lambda6");
    //~ symbol_numeric lambda7 = *sys.new_Joint_Unknown("lambda7");
    //~ symbol_numeric lambda8 = *sys.new_Joint_Unknown("lambda8");
    //~ symbol_numeric lambda9 = *sys.new_Joint_Unknown("lambda9");
    //~ symbol_numeric lambda10 = *sys.new_Joint_Unknown("lambda10");



// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

    cout << "Input Vector" << endl;

    symbol_numeric tor = *sys.new_Parameter("tor",0.0);//100.0
    //symbol_numeric torque = *sys.new_Input("torque",00.0);

    symbol_numeric Fx_R = *sys.new_Input("Fx_R",0.0);
    symbol_numeric Fy_R = *sys.new_Input("Fy_R",0.0);
    symbol_numeric Mz_R = *sys.new_Input("Mz_R",0.0);
    symbol_numeric Fx_L = *sys.new_Input("Fx_L",0.0);
    symbol_numeric Fy_L = *sys.new_Input("Fy_L",0.0);
    symbol_numeric Mz_L = *sys.new_Input("Mz_L",0.0);

// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************




// ************************************************************************************************
//	Define Wrenches
// ************************************************************************************************

    cout << "Define Wrenches" << endl;

    //	Gravity
    Wrench3D * Gravity_WHS = sys.Gravity_Wrench("WHS");

    //	Inertia
    Wrench3D * Inertia_WHS = sys.Inertia_Wrench("WHS");

    //	Constitutive

    //	External

    Vector3D F_WHS = *sys.new_Vector3D("F_WHS",0,0,0,"B_WHS");
    //Vector3D M_WHS = *sys.new_Vector3D("M_WHS",0,torque,0, "B_WHS");
    Vector3D M_WHS = *sys.new_Vector3D("M_WHS",0,tor,0, "B_WHS");


    Wrench3D * Momentum = sys.new_Wrench3D ( "Momentum", F_WHS, M_WHS , P_WHS , WHS , "External") ;



// ************************************************************************************************
// 	 Kinematic Equations
// ************************************************************************************************
    cout << "Kinematic Equations" << endl;
    
    Matrix Phi(10,1);
    
    
    symbol_numeric asR = *sys.new_Parameter("asR",0.0);//spline's coefficients R rail ppsition
    symbol_numeric bsR = *sys.new_Parameter("bsR",0.0);
    symbol_numeric csR = *sys.new_Parameter("csR",0.0);
    symbol_numeric dsR = *sys.new_Parameter("dsR",0.0);
    symbol_numeric esR = *sys.new_Parameter("esR",0.0);
    symbol_numeric fsR = *sys.new_Parameter("fsR",0.0);    
    symbol_numeric stasR = *sys.new_Parameter("stasR",0.0);
    symbol_numeric endsR = *sys.new_Parameter("endsR",10.0);
    symbol_numeric usRz = *sys.new_Parameter("usRz",0.0); 
   
    //Right
    Vector3D PWHS_PWHSR = *sys.new_Vector3D("PWHS_PWHSR",0,-LWHS/2.0,0,"B_WHSa");
    Point * P_WHSR  = sys.new_Point("P_WHSR","P_WHS",&PWHS_PWHSR);

    symbol_numeric thetaW_R = *sys.new_AuxCoordinate("thetaW_R","dthetaW_R","ddthetaW_R",0.0,0.0,0.0);
    symbol_numeric uW_R = *sys.new_AuxCoordinate("uW_R","duW_R","dduW_R",-0.0,0.0,0.0);
    //symbol_numeric *dthetaW_R=sys.get_Velocity("dthetaW_R");
    //symbol_numeric *duW_R=sys.get_Velocity("duW_R");
    
    
    
    symbol_numeric aW_R = *sys.new_Parameter("aW_R",0.0);//spline's coefficients
    symbol_numeric bW_R = *sys.new_Parameter("bW_R",0.0);
    symbol_numeric cW_R = *sys.new_Parameter("cW_R",-0.1);
    symbol_numeric dW_R = *sys.new_Parameter("dW_R",-0.5);
    symbol_numeric lW_R = *sys.new_Parameter("lW_R",0.0);//size of the spline
    
 
    ex sW_R = uW_R - lW_R;
    ex splineW_R  = dW_R + sW_R * ( cW_R + sW_R * (bW_R + sW_R * aW_R ) );
    Vector3D fW_R  = *sys.new_Vector3D("fW_R",-splineW_R*sin(thetaW_R),uW_R,splineW_R*cos(thetaW_R),"B_WHSa");
    Vector3D rW_R  = sys.Position_Vector("O","P_WHSR")+fW_R;
    Vector3D t1W_R = sys.diff ( rW_R , thetaW_R);
    Vector3D t2W_R = sys.diff ( rW_R , uW_R);
    Vector3D nW_R  = t1W_R^t2W_R;


    symbol_numeric uR_R = *sys.new_AuxCoordinate("uR_R","duR_R","dduR_R", -0.0 ,0.0,0.0);
    symbol_numeric sR_R = *sys.new_AuxCoordinate("sR_R","dsR_R","ddsR_R", 0.0 ,0.0,0.0);

    //~ symbol_numeric aR_R = *sys.new_Parameter("aR_R",0.066403345669996e+3);//spline's coefficients right rail profile
    //~ symbol_numeric bR_R = *sys.new_Parameter("bR_R",-0.001998816728350e+3);
    //~ symbol_numeric cR_R = *sys.new_Parameter("cR_R",0.000000000000000e+3);
    //~ symbol_numeric dR_R = *sys.new_Parameter("dR_R",0.000159000000000e+3);
    //~ symbol_numeric lR_R = *sys.new_Parameter("lR_R",0.005); //size of the spline

    symbol_numeric aR_R = *sys.new_Parameter("aR_R",0.0);//spline's coefficients right rail profile
    symbol_numeric bR_R = *sys.new_Parameter("bR_R",-20.0);
    symbol_numeric cR_R = *sys.new_Parameter("cR_R",0.0);
    symbol_numeric dR_R = *sys.new_Parameter("dR_R",0.10);
    symbol_numeric lR_R = *sys.new_Parameter("lR_R",0.00); //size of the spline


    
    ex wR_R = atomize_ex (uR_R - lR_R);
    ex splineR_R   = atomize_ex (dR_R + wR_R * ( cR_R + wR_R * (bR_R + wR_R * aR_R ) ));
    Vector3D fR_R  = *sys.new_Vector3D("fR_R",0,uR_R,splineR_R,"B_RailR");
    
    
    ex slR_R = atomize_ex ((sR_R - stasR)/(endsR-stasR));
    ex spS_R   =  atomize_ex (fsR + slR_R * ( esR + slR_R * (dsR + slR_R * ( csR + slR_R * (bsR + slR_R * asR ) ) )) );

    ex dspS_Rx = sys.diff ( sR_R , sR_R);
    ex dspS_Ry = sys.diff ( spS_R, sR_R);
    ex dspS_R_mod = atomize_ex(sqrt(dspS_Rx*dspS_Rx + dspS_Ry*dspS_Ry));
    
    Vector3D pR_R  = *sys.new_Vector3D("pR_R",sR_R + (L_R/2.0) * dspS_Ry / dspS_R_mod , spS_R - (L_R/2.0) *dspS_Rx/dspS_R_mod ,0.0,"B_RailR");
    Vector3D irrR_R  = *sys.new_Vector3D("irrR_R",0.0, 0.0 ,usRz,"B_RailR");

    Vector3D rR_R  = pR_R + fR_R + irrR_R;
    //Vector3D pR_R  = *sys.new_Vector3D("pR_R",sR_R, 0.0 ,0.0,"B_RailR");
    //Vector3D rR_R  = sys.Position_Vector("O","P_RailR") + pR_R + fR_R;

    
    Vector3D t1R_R = sys.diff ( rR_R , sR_R); 
    Vector3D t2R_R = sys.diff ( rR_R , uR_R);
    Vector3D nR_R  = t1R_R^t2R_R;

    //normal and tangent unitary vectors at contact point
    Vector3D u_nR_R  = ( 1 /sqrt( nR_R * nR_R )) * nR_R;
    Vector3D u_t1R_R = ( 1 /sqrt( t1R_R * t1R_R )) * t1R_R;
    Vector3D u_t2R_R = ( 1 /sqrt( t2R_R * t2R_R )) * t2R_R;


    Point * PWcon_R    = sys.new_Point("PWcon_R","O",&rW_R);
    Point * PRcon_R    = sys.new_Point("PRcon_R","O",&rR_R);
    Vector3D VPconRW_R = sys.Position_Vector("PRcon_R","PWcon_R");


    Vector3D FKALKER_R = (Fx_R* u_t1R_R) + (Fy_R * u_t2R_R);
    Vector3D MKALKER_R = Mz_R * u_nR_R;


    Wrench3D * FKalker_R = sys.new_Wrench3D ( "FKalker_R", FKALKER_R, MKALKER_R , PWcon_R, WHS , "External") ;

    Phi(0,0) = u_t1R_R * (VPconRW_R);
    Phi(1,0) = u_t2R_R * (VPconRW_R);
    Phi(2,0) = u_nR_R  * (VPconRW_R);
    Phi(3,0) = u_nR_R*t1W_R;
    Phi(4,0) = u_nR_R*t2W_R;

    //~ symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");
    //~ symbol_numeric lambda2  = *sys.new_Joint_Unknown("lambda2");
    //~ symbol_numeric lambda3  = *sys.new_Joint_Unknown("lambda3");
    //~ symbol_numeric lambda4  = *sys.new_Joint_Unknown("lambda4");
    //~ symbol_numeric lambda5  = *sys.new_Joint_Unknown("lambda5");
    

    //~ Phi(0,0) = u_nR_R  * (VPconRW_R);
    //~ Phi(1,0) = u_nR_R*t1W_R;
    //~ Phi(2,0) = u_nR_R*t2W_R;
//~ 
    //~ symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");
    //~ symbol_numeric lambda2  = *sys.new_Joint_Unknown("lambda2");
    //~ symbol_numeric lambda3  = *sys.new_Joint_Unknown("lambda3");
 
    


 // ************************************************************************************************
    symbol_numeric asL = *sys.new_Parameter("asL",0.0);//spline's coefficients R rail ppsition
    symbol_numeric bsL = *sys.new_Parameter("bsL",0.0);
    symbol_numeric csL = *sys.new_Parameter("csL",0.0);
    symbol_numeric dsL = *sys.new_Parameter("dsL",0.0);
    symbol_numeric esL = *sys.new_Parameter("esL",0.0);
    symbol_numeric fsL = *sys.new_Parameter("fsL",0.0);    
    symbol_numeric stasL = *sys.new_Parameter("stasL",0.0);
    symbol_numeric endsL = *sys.new_Parameter("endsL",10.0);
    symbol_numeric usLz = *sys.new_Parameter("usLz",0.0);


    //Left
    Vector3D PWHS_PWHSL = *sys.new_Vector3D("PWHS_PWHSL",0,LWHS/2.0,0,"B_WHSa");
    Point * P_WHSL  = sys.new_Point("P_WHSL","P_WHS",&PWHS_PWHSL);

    symbol_numeric thetaW_L = *sys.new_AuxCoordinate("thetaW_L","dthetaW_L","ddthetaW_L",0.0,0.0,0.0);
    symbol_numeric uW_L = *sys.new_AuxCoordinate("uW_L","duW_L","dduW_L",0.0,0.0,0.0);


    //~ symbol_numeric aW_L = *sys.new_Parameter("aW_L",0.006456790834618e+4);//spline's coefficients
    //~ symbol_numeric bW_L = *sys.new_Parameter("bW_L",-0.000002379249587e+4);
    //~ symbol_numeric cW_L = *sys.new_Parameter("cW_L",0.000000893613412e+4);
    //~ symbol_numeric dW_L = *sys.new_Parameter("dW_L",-0.000050000000000e+4);
    //~ symbol_numeric lW_L = *sys.new_Parameter("lW_L",0.01);//size of the spline
    
    symbol_numeric aW_L = *sys.new_Parameter("aW_L",0.0);//spline's coefficients
    symbol_numeric bW_L = *sys.new_Parameter("bW_L",0.0);
    symbol_numeric cW_L = *sys.new_Parameter("cW_L",0.1);
    symbol_numeric dW_L = *sys.new_Parameter("dW_L",-0.5);
    symbol_numeric lW_L = *sys.new_Parameter("lW_L",0.0);
    
 

    ex sW_L = uW_L - lW_L;
    ex splineW_L  =   dW_L + sW_L * ( cW_L + sW_L * (bW_L + sW_L * aW_L ) );
    Vector3D fW_L = *sys.new_Vector3D("fW_L",-splineW_L*sin(thetaW_L),uW_L,splineW_L*cos(thetaW_L),"B_WHSa");
    Vector3D rW_L = sys.Position_Vector("O","P_WHSL")+fW_L;
    Vector3D t1W_L= sys.diff ( rW_L , thetaW_L);
    Vector3D t2W_L= sys.diff ( rW_L , uW_L);
    Vector3D nW_L = t1W_L^t2W_L;



    symbol_numeric uR_L = *sys.new_AuxCoordinate("uR_L","duR_L","dduR_L", 0.0 ,0.0,0.0);
    symbol_numeric sR_L = *sys.new_AuxCoordinate("sR_L","dsR_L","ddsR_L", 0.0 ,0.0,0.0);

    //~ symbol_numeric aR_L = *sys.new_Parameter("aR_L",0.066403345669996e+3);//spline's coefficients right wheel
    //~ symbol_numeric bR_L = *sys.new_Parameter("bR_L",-0.001998816728350e+3);
    //~ symbol_numeric cR_L = *sys.new_Parameter("cR_L",0.000000000000000e+3);
    //~ symbol_numeric dR_L = *sys.new_Parameter("dR_L",0.000159000000000e+3);
    //~ symbol_numeric lR_L = *sys.new_Parameter("lR_L",0.005); //size of the spline
    
    symbol_numeric aR_L = *sys.new_Parameter("aR_L",0.0);//spline's coefficients left rail profile
    symbol_numeric bR_L = *sys.new_Parameter("bR_L",-20.0);
    symbol_numeric cR_L = *sys.new_Parameter("cR_L",0.0);
    symbol_numeric dR_L = *sys.new_Parameter("dR_L",0.1);
    symbol_numeric lR_L = *sys.new_Parameter("lR_L",0.0);
    

   
        
    ex wR_L = atomize_ex(uR_L - lR_L);
    ex splineR_L   =   atomize_ex(dR_L + wR_L * ( cR_L + wR_L * (bR_L + wR_L * aR_L ) ));
    Vector3D fR_L = *sys.new_Vector3D("fR_L",0,uR_L,splineR_L,"B_RailL");
    
  
    
    ex slR_L = atomize_ex((sR_L - stasL)/(endsL-stasL));
    ex spS_L   = atomize_ex(fsL + slR_L * ( esL + slR_L * (dsL + slR_L * ( csL + slR_L * (bsL + slR_L * asL ) ) )));
    
    
    ex dspS_Lx = sys.diff ( sR_L , sR_L);
    ex dspS_Ly = sys.diff ( spS_L, sR_L);
    ex dspS_L_mod = atomize_ex(sqrt(dspS_Lx*dspS_Lx + dspS_Ly*dspS_Ly));    
    Vector3D pR_L  = *sys.new_Vector3D("pR_L",sR_L - (L_R/2.0) * dspS_Ly/dspS_L_mod , spS_L + (L_R/2.0) *dspS_Lx/dspS_L_mod ,0.0,"B_RailL");
    Vector3D irrR_L  = *sys.new_Vector3D("rrR_L",0.0,0.0,usLz,"B_RailL");
    
    Vector3D rR_L  = pR_L+ fR_L + irrR_L;
    //Vector3D pR_L  = *sys.new_Vector3D("pR_L",sR_L , 0.0,0.0,"B_RailL");
    //Vector3D rR_L  = sys.Position_Vector("O","P_RailL") + pR_L+ fR_L;

    Vector3D t1R_L = sys.diff ( rR_L , sR_L);
    Vector3D t2R_L = sys.diff ( rR_L , uR_L);
    Vector3D nR_L  = t1R_L^t2R_L;

    //normal and tangent unitary vectors at contact point
    Vector3D u_nR_L  = ( 1 /sqrt( nR_L * nR_L )) * nR_L;
    Vector3D u_t1R_L = ( 1 /sqrt( t1R_L * t1R_L )) * t1R_L;
    Vector3D u_t2R_L = ( 1 /sqrt( t2R_L * t2R_L )) * t2R_L;


    Point * PWcon_L    = sys.new_Point("PWcon_L","O",&rW_L);
    Point * PRcon_L    = sys.new_Point("PRcon_L","O",&rR_L);
    Vector3D VPconRW_L = sys.Position_Vector("PRcon_L","PWcon_L");

    Vector3D FKALKER_L = (Fx_L* u_t1R_L) + (Fy_L * u_t2R_L);
    Vector3D MKALKER_L = Mz_L * u_nR_L;


    Wrench3D * FKalker_L = sys.new_Wrench3D ( "FKalker_L", FKALKER_L, MKALKER_L , PWcon_L, WHS , "External") ;

    Phi(5,0) = u_t1R_L * (VPconRW_L);
    Phi(6,0) = u_t2R_L * (VPconRW_L);
    Phi(7,0) = u_nR_L  * (VPconRW_L);
    Phi(8,0) = u_nR_L  * t1W_L;
    Phi(9,0) = u_nR_L  * t2W_L;

    //~ symbol_numeric lambda6  = *sys.new_Joint_Unknown("lambda6");
    //~ symbol_numeric lambda7  = *sys.new_Joint_Unknown("lambda7");
    //~ symbol_numeric lambda8  = *sys.new_Joint_Unknown("lambda8");
    //~ symbol_numeric lambda9  = *sys.new_Joint_Unknown("lambda9");
    //~ symbol_numeric lambda10 = *sys.new_Joint_Unknown("lambda10");

    //~ Phi(3,0) = u_nR_L  * (VPconRW_L);
    //~ Phi(4,0) = u_nR_L  * t1W_L;
    //~ Phi(5,0) = u_nR_L  * t2W_L;
//~ 
    //~ symbol_numeric lambda4  = *sys.new_Joint_Unknown("lambda4");
    //~ symbol_numeric lambda5  = *sys.new_Joint_Unknown("lambda5");
    //~ symbol_numeric lambda6  = *sys.new_Joint_Unknown("lambda6");

// ************************************************************************************************
//~ symbol_numeric tim=sys.get_Time_Symbol ( );
//~ Phi(10,0) = 0.01*sin(tim/10.0) - a_pend;
//~ symbol_numeric lambda11 = *sys.new_Joint_Unknown("lambda11");

// ************************************************************************************************



    Drawing3D * D_Fkalk_L = sys.new_Drawing3D("D_Fkalk_L",&FKALKER_L,PRcon_L);
    Drawing3D * D_Fkalk_R = sys.new_Drawing3D("D_Fkalk_R",&FKALKER_R,PRcon_R);
    D_Fkalk_L->set_scale(0.01);
    D_Fkalk_R->set_scale(0.01);
    
    Drawing3D * D_u_t1R_L = sys.new_Drawing3D("D_u_t1R_L",&u_t1R_L,PRcon_L);
    Drawing3D * D_u_t2R_L = sys.new_Drawing3D("D_u_t2R_L",&u_t2R_L,PRcon_L);   
    Drawing3D * D_u_nR_L = sys.new_Drawing3D("D_u_nR_L",&u_nR_L,PRcon_L);
    
    Drawing3D * D_u_t1R_R = sys.new_Drawing3D("D_u_t1R_R",&u_t1R_R,PRcon_R); 
    Drawing3D * D_u_t2R_R = sys.new_Drawing3D("D_u_t2R_R",&u_t2R_R,PRcon_R);   
    Drawing3D * D_u_nR_R = sys.new_Drawing3D("D_u_nR_R",&u_nR_R,PRcon_R);    







// ************************************************************************************************
// 	Vectors needed to take diferent Jacobians
// ************************************************************************************************

    cout << "Vectors needed to take diferent Jacobians" << endl;

    Matrix q = sys.Coordinates();
    Matrix dq = sys.Velocities();
    Matrix ddq = sys.Accelerations();
    Matrix qaux = sys.Aux_Coordinates();   
    Matrix dqaux = sys.Aux_Velocities();
    Matrix epsilon = sys.Joint_Unknowns();
    Matrix pars = sys.Parameters();
    Matrix inps = sys.Inputs();
    Matrix unks = sys.Joint_Unknowns();
    
    
    
// ************************************************************************************************
// 	Dynamic Equations
// ************************************************************************************************

    cout << "Dynamic Equations" << endl;

    Matrix Dynamic_Equations = sys.GenForceSys("ALL");


    symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");
    symbol_numeric lambda2  = *sys.new_Joint_Unknown("lambda2");
// ************************************************************************************************
// 	Output Vector
// ************************************************************************************************


    Matrix Output(20,1);
    Vector3D eR = *sys.new_Vector3D("eR",0,1,0,"B_WHSa");
    ex rho_R = abs(sqrt(fW_R(0,0)*fW_R(0,0) + fW_R(2,0)*fW_R(2,0)));
    ex cryW_R = rho_R / sqrt(1-(u_nR_R*eR)*(u_nR_R*eR)) ;
    //ex cryW_R = rho_R * sqrt(1-(u_nR_R*eR)) ;
    ex crxW_R = abs(pow(1 + pow(sys.diff(splineW_R,uW_R),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineW_R,uW_R),uW_R));  /* Radius of Curvature rho = (1+y')^(3/2) / y'' */
    ex cryR_R = 6e+6;
    ex crxR_R = abs(pow(1 + pow(sys.diff(splineR_R,uR_R),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineR_R,uR_R),uR_R));

    Vector3D VJW_R = sys.Velocity_Vector ("abs", "PWcon_R", "WHS");
    Vector3D VCW_R = sys.Velocity_Vector ("abs", "P_WHSR", "WHS");   
    Vector3D OM_WHS = sys.Angular_Velocity("xyz","B_WHS");
    
    Output(0,0) = sqrt(lambda1*lambda1);
    //Output(0,0) = lambda1;   
    Output(1,0) = VJW_R * u_t1R_R;
    Output(2,0) = VJW_R * u_t2R_R;
    Output(3,0) = OM_WHS * u_nR_R;
    Output(4,0) = *db;
    //Vector3D RR = *sys.new_Vector3D("RR",fW_R(0,0),0,fW_R(2,0),"B_WHSa");
    //Output(5,0) = numeric(1,2)*(VCW_R.get_module() + (OM_WHS ^ RR).get_module()); 
    Output(5,0) = numeric(1,2)*(VCW_R.get_module() + (OM_WHS ^ fW_R).get_module());    
    Output(6,0) = cryW_R;
    //Output(7,0) = crxW_R;
    Output(7,0) = 1e4;   
    Output(8,0) = cryR_R;
    Output(9,0) = crxR_R;

    Vector3D eL = *sys.new_Vector3D("eL",0,1,0,"B_WHSa");
    ex rho_L = abs(sqrt(fW_L(0,0)*fW_L(0,0) + fW_L(2,0)*fW_L(2,0)));
    ex cryW_L = rho_L / sqrt(1-(u_nR_L*eL)*(u_nR_L*eL)) ;
    //ex cryW_L = rho_L * sqrt(1-(u_nR_L*eL)) ;
    //ex cryW_L = abs(sqrt(fW_L(0,0)*fW_L(0,0) + fW_L(2,0)*fW_L(2,0)));//Cambiar
    ex crxW_L = abs(pow(1 + pow(sys.diff(splineW_L,uW_L),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineW_L,uW_L),uW_L));  /* Radius of Curvature rho = (1+y')^(3/2) / y'' */
    ex cryR_L = 6e+6;
    ex crxR_L = abs(pow(1 + pow(sys.diff(splineR_L,uR_L),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineR_L,uR_L),uR_L));

    Vector3D VJW_L = sys.Velocity_Vector ("abs", "PWcon_L", "WHS");
    Vector3D VCW_L = sys.Velocity_Vector ("abs", "P_WHSL", "WHS");   

    Output(10,0) = sqrt(lambda2*lambda2);
    //Output(10,0) = lambda4;
    Output(11,0) = VJW_L * u_t1R_L;
    Output(12,0) = VJW_L * u_t2R_L;
    Output(13,0) = OM_WHS * u_nR_L;
    Output(14,0) = *db;
    //Vector3D RL = *sys.new_Vector3D("RL",fW_L(0,0),0,fW_L(2,0),"B_WHSa");
    //Output(15,0) = numeric(1,2)*(VCW_L.get_module() + (OM_WHS ^ RL).get_module());
    Output(15,0) = numeric(1,2)*(VCW_L.get_module() + (OM_WHS ^ fW_L).get_module());
    Output(16,0) = cryW_L;
    //Output(17,0) = crxW_L;
    Output(17,0) = 1e4;    
    Output(18,0) = cryR_L;
    Output(19,0) = crxR_L;

    sys.new_Matrix("Output",Output);


// ************************************************************************************************
// 	Energy Equations
// ************************************************************************************************

    cout << "Energy Equations" << endl;

    Matrix Energy(1,1);
    Energy(0,0)=1;
    sys.new_Matrix("Energy",Energy);



// ************************************************************************************************
// 	KALKER
// ************************************************************************************************
    // KALKER
    symbol_numeric E_elastic = *sys.new_Parameter("E_elastic",210.0e+9);       // MPa
    symbol_numeric nu_poisson = *sys.new_Parameter("nu_poisson",0.27);       // Steel
    symbol_numeric G_elastic = *sys.new_Parameter("G_elastic",1.4384e+11);   // G = E/(2*(1-nu)); % MPa

    // hertz ellipse parameters
    symbol_numeric aR = *sys.new_Parameter("aR",0.0);
    symbol_numeric bR = *sys.new_Parameter("bR",0.0);
    symbol_numeric aL = *sys.new_Parameter("aL",0.0);
    symbol_numeric bL = *sys.new_Parameter("bL",0.0);    
    
    
    // Kalker's coefficients
    symbol_numeric C11R = *sys.new_Parameter("C11R",0.0);
    symbol_numeric C22R = *sys.new_Parameter("C22R",0.0);
    symbol_numeric C23R = *sys.new_Parameter("C23R",0.0);
    symbol_numeric C33R = *sys.new_Parameter("C33R",0.0);
    
    symbol_numeric C11L = *sys.new_Parameter("C11L",0.0);
    symbol_numeric C22L = *sys.new_Parameter("C22L",0.0);
    symbol_numeric C23L = *sys.new_Parameter("C23L",0.0);
    symbol_numeric C33L = *sys.new_Parameter("C33L",0.0);  
    
    Matrix D_R(3,3);
    ex GabR = G_elastic*aR*bR;
    D_R(0,0) = GabR * C11R; D_R(0,1) = 0;                        D_R(0,2) = 0;
    D_R(1,0) = 0;           D_R(1,1) = GabR * C22R;              D_R(1,2) = GabR * sqrt(aR*bR)*C23R;
    D_R(2,0) = 0;           D_R(2,1) =-GabR * sqrt(aR*bR)*C23R;  D_R(2,2) = GabR * aR*bR*C33R;
    
    Matrix D_L(3,3);
    ex GabL = G_elastic*aL*bL;
    D_L(0,0) = GabL * C11L; D_L(0,1) = 0;                        D_L(0,2) = 0;
    D_L(1,0) = 0;           D_L(1,1) = GabL * C22L;              D_L(1,2) = GabL * sqrt(aL*bL)*C23L;
    D_L(2,0) = 0;           D_L(2,1) =-GabL * sqrt(aL*bL)*C23L;  D_L(2,2) = GabL * aL*bL*C33L;   
    
        


// ************************************************************************************************
// 	Matrix Calculation
// ************************************************************************************************
    symbol_numeric y0 = *sys.new_Parameter("y0",0.0);
    symbol_numeric b0 = *sys.new_Parameter("b0",0.0);    
    //coord_indep_init = y+y0 ,b+b0;
    //vel_indep_init	= *dx-0.648644 ,*dy, *db-1.29572;
    
    
    cout << "Matrix Calculation" << endl;
    //sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD,  dPhiNH);

    //sys.Matrix_Calculation(Phi,coord_indep_init, vel_indep_init, sys, METHOD);
    sys.Matrix_Calculation(coord_indep_init, vel_indep_init, sys, METHOD);

// ************************************************************************************************
// 	Kalker NEW
// ************************************************************************************************   
    cout <<"CKalker Calculating and Exporting"<<endl; 
    
    Matrix Qo   = *sys.get_Matrix( "Q" );
    
    lst kalker_forcesR, kalker_forcesL;
	kalker_forcesR =Fx_R,Fy_R,Mz_R;
 	kalker_forcesL =Fx_L,Fy_L,Mz_L; 
      
    Matrix Mat_KakerForcesR = Matrix(kalker_forcesR.nops(),1,kalker_forcesR);
    Matrix Mat_KakerForcesL = Matrix(kalker_forcesL.nops(),1,kalker_forcesL);  
      
    Matrix dQ_dKFR = sys.jacobian(Qo.transpose(),Mat_KakerForcesR);
    Matrix dQ_dKFL = sys.jacobian(Qo.transpose(),Mat_KakerForcesL);  
    
    Matrix SlipR (3,1);
    SlipR (0,0) = VJW_R * u_t1R_R;
    SlipR (1,0) = VJW_R * u_t2R_R;
    SlipR (2,0) = OM_WHS * u_nR_R; 
     
    Matrix SlipL (3,1);
    SlipL (0,0) = VJW_L * u_t1R_L;
    SlipL (1,0) = VJW_L * u_t2R_L;
    SlipL (2,0) = OM_WHS * u_nR_L;
    


    Matrix CKR = dQ_dKFR * D_R*sys.jacobian(SlipR.transpose(),dq);
    Matrix CKL = dQ_dKFL * D_L*sys.jacobian(SlipL.transpose(),dq);                 

      
    lst new_atom_list_CKR, new_exp_list_CKR;
    matrix_list_optimize (CKR, new_atom_list_CKR, new_exp_list_CKR);
    sys.export_Matrix_C	("CKR","_CKR",CKR, new_atom_list_CKR, new_exp_list_CKR ,ORDER);
    sys.export_function_MATLAB("CKR", "CKR_",CKR, new_atom_list_CKR, new_exp_list_CKR,"q,qaux,dq,time,param");   
    
    lst new_atom_list_CKL, new_exp_list_CKL;
    matrix_list_optimize (CKL, new_atom_list_CKL, new_exp_list_CKL);
    sys.export_Matrix_C	("CKL","_CKL",CKL, new_atom_list_CKL, new_exp_list_CKL ,ORDER);
    sys.export_function_MATLAB("CKL", "CKL_",CKL, new_atom_list_CKL, new_exp_list_CKL,"q,qaux,dq,time,param");     
    

                  
    

// sustituir las fuerzas de kalker (inputs) por cero en Q y exportar el nuevo Q (Q2)

    vector < symbol_numeric * > fk;
    fk.push_back( &Fx_R );fk.push_back( &Fy_R );fk.push_back( &Mz_R );
    fk.push_back( &Fx_L );fk.push_back( &Fy_L );fk.push_back( &Mz_L );
    
    
    for (int i=0; (i < Qo.rows()); ++i) {
        Qo(i,0) = recursive_substitution (Qo(i,0),fk , 0); 
    } 


    lst new_atom_list_Delta, new_exp_list_Delta;
    matrix_list_optimize (Qo, new_atom_list_Delta,new_exp_list_Delta);
    sys.export_Matrix_C	("Delta","_Delta",Qo, new_atom_list_Delta, new_exp_list_Delta ,ORDER);
    sys.export_function_MATLAB("Delta", "Delta_",Qo, new_atom_list_Delta, new_exp_list_Delta,"q,qaux,dq,time,param,inputs"); 


// ************************************************************************************************
// 	New Phis
// ************************************************************************************************
cout <<" Phic and Phit calculating and exporting"<<endl; 

Matrix Phic (2,1);

Phic(0,0) = Phi(2,0);
Phic(1,0) = Phi(7,0);

//~ symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");
//~ symbol_numeric lambda2  = *sys.new_Joint_Unknown("lambda2");


Matrix Phit (8,1);
Phit(0,0) = Phi(0,0);
Phit(1,0) = Phi(1,0);
Phit(2,0) = Phi(3,0);
Phit(3,0) = Phi(4,0);
Phit(4,0) = Phi(5,0);
Phit(5,0) = Phi(6,0);
Phit(6,0) = Phi(8,0);
Phit(7,0) = Phi(9,0);



//Matrix dPhic = sys.Dt(Phic);
Matrix dPhic (2,1);
dPhic(0,0) = u_nR_R * sys.dt(VPconRW_R);
dPhic(1,0) = u_nR_L * sys.dt(VPconRW_L);

Matrix dPhit = sys.Dt(Phit);  
//~ Matrix dPhit (8,1);
//~ dPhit(0,0) = u_t1R_R * sys.dt(VPconRW_R);
//~ dPhit(1,0) = u_t2R_R * sys.dt(VPconRW_R);
//~ dPhit(2,0) = sys.dt(u_nR_R*t1W_R);
//~ dPhit(3,0) = sys.dt(u_nR_R*t2W_R);
//~ dPhit(4,0) = u_t1R_L * sys.dt(VPconRW_L);
//~ dPhit(5,0) = u_t2R_L * sys.dt(VPconRW_L);
//~ dPhit(6,0) = sys.dt(u_nR_L  * t1W_L);
//~ dPhit(7,0) = sys.dt(u_nR_L  * t2W_L);  



Matrix ddPhic = sys.Dt(dPhic);

Matrix Betac  = -dPhic;

vector < symbol_numeric * > Velocities = sys.get_Velocities();
vector < symbol_numeric * > Aux_Velocities = sys.get_AuxVelocities();
for (int i=0; (i < dPhic.rows()); ++i) {
    Betac(i,0) = recursive_substitution (Betac(i,0),Velocities , 0);
    Betac(i,0) = recursive_substitution (Betac(i,0),Aux_Velocities , 0);
}	
 
Matrix Gammac  = -ddPhic;


vector < symbol_numeric * > Accelerations      = sys.get_Accelerations();
vector < symbol_numeric * > Aux_Accelerations  = sys.get_AuxAccelerations();
for (int i=0; (i < Gammac.rows()); ++i) {
    Gammac(i,0) = recursive_substitution (Gammac(i,0),Accelerations , 0);
    Gammac(i,0) = recursive_substitution (Gammac(i,0),Aux_Accelerations , 0);
}
 

Matrix dPhic_dq =  sys.jacobian(dPhic.transpose(), dq);
Matrix dPhit_ds =  sys.jacobian(dPhit.transpose(), dqaux);


lst new_atom_list_Phic, new_exp_list_Phic;
matrix_list_optimize (Phic, new_atom_list_Phic,new_exp_list_Phic);
sys.export_Matrix_C	("Phic","_Phic",Phic, new_atom_list_Phic, new_exp_list_Phic ,ORDER);
sys.export_function_MATLAB("Phic", "Phic_",Phic, new_atom_list_Phic, new_exp_list_Phic,"q,qaux,time,param"); 

lst new_atom_list_Phit, new_exp_list_Phit;
matrix_list_optimize (Phit, new_atom_list_Phit,new_exp_list_Phit);
sys.export_Matrix_C	("Phit","_Phit",Phit, new_atom_list_Phit, new_exp_list_Phit ,ORDER);
sys.export_function_MATLAB("Phit", "Phit_",Phit, new_atom_list_Phit, new_exp_list_Phit,"q,qaux,time,param"); 


lst new_atom_list_Betac, new_exp_list_Betac;
matrix_list_optimize (Betac, new_atom_list_Betac,new_exp_list_Betac);
sys.export_Matrix_C	("Betac","_Betac",Betac, new_atom_list_Betac, new_exp_list_Betac ,ORDER);
sys.export_function_MATLAB("Betac", "Betac_",Betac, new_atom_list_Betac, new_exp_list_Betac,"q,dq,time,param"); 

lst new_atom_list_Gammac, new_exp_list_Gammac;
matrix_list_optimize (Gammac, new_atom_list_Gammac,new_exp_list_Gammac);
sys.export_Matrix_C	("Gammac","_Gammac",Gammac, new_atom_list_Gammac, new_exp_list_Gammac ,ORDER);
sys.export_function_MATLAB("Gammac", "Gammac_",Gammac, new_atom_list_Gammac, new_exp_list_Gammac,"q,qaux,dq,dqaux,time,param"); 

lst new_atom_list_dPhic_dq, new_exp_list_dPhic_dq;
matrix_list_optimize (dPhic_dq, new_atom_list_dPhic_dq,new_exp_list_dPhic_dq);
sys.export_Matrix_C	("dPhic_dq","_dPhic_dq",dPhic_dq, new_atom_list_dPhic_dq, new_exp_list_dPhic_dq ,ORDER);
sys.export_function_MATLAB("dPhic_dq", "dPhic_dq_",dPhic_dq, new_atom_list_dPhic_dq, new_exp_list_dPhic_dq,"q,qaux,time,param"); 

lst new_atom_list_dPhit_ds, new_exp_list_dPhit_ds;
matrix_list_optimize (dPhit_ds, new_atom_list_dPhit_ds,new_exp_list_dPhit_ds);
sys.export_Matrix_C	("dPhit_ds","_dPhit_ds",dPhit_ds, new_atom_list_dPhit_ds, new_exp_list_dPhit_ds ,ORDER);
sys.export_function_MATLAB("dPhit_ds", "dPhit_ds_",dPhit_ds, new_atom_list_dPhit_ds, new_exp_list_dPhit_ds,"q,qaux,time,param"); 



Matrix ddPhit = sys.Dt(dPhit);
Matrix Gammat  = -ddPhit;
for (int i=0; (i < Gammat.rows()); ++i) {
    Gammat(i,0) = recursive_substitution (Gammat(i,0),Accelerations , 0);
    Gammat(i,0) = recursive_substitution (Gammat(i,0),Aux_Accelerations , 0);
}
Matrix dPhic_ds =  sys.jacobian(dPhic.transpose(), dqaux);
Matrix dPhit_dq =  sys.jacobian(dPhit.transpose(), dq);

lst new_atom_list_dPhic_ds, new_exp_list_dPhic_ds;
matrix_list_optimize (dPhic_ds, new_atom_list_dPhic_ds,new_exp_list_dPhic_ds);
sys.export_Matrix_C	("dPhic_ds","_dPhic_ds",dPhic_ds, new_atom_list_dPhic_ds, new_exp_list_dPhic_ds ,ORDER);
sys.export_function_MATLAB("dPhic_ds", "dPhic_d_s",dPhic_ds, new_atom_list_dPhic_ds, new_exp_list_dPhic_ds,"q,qaux,time,param"); 

lst new_atom_list_dPhit_dq, new_exp_list_dPhit_dq;
matrix_list_optimize (dPhit_dq, new_atom_list_dPhit_dq,new_exp_list_dPhit_dq);
sys.export_Matrix_C	("dPhit_dq","_dPhit_dq",dPhit_dq, new_atom_list_dPhit_dq, new_exp_list_dPhit_dq ,ORDER);
sys.export_function_MATLAB("dPhit_dq", "dPhit_dq_",dPhit_dq, new_atom_list_dPhit_dq, new_exp_list_dPhit_dq,"q,qaux,time,param"); 


lst new_atom_list_Gammat, new_exp_list_Gammat;
matrix_list_optimize (Gammat, new_atom_list_Gammat,new_exp_list_Gammat);
sys.export_Matrix_C	("Gammat","_Gammat",Gammat, new_atom_list_Gammat, new_exp_list_Gammat ,ORDER);
sys.export_function_MATLAB("Gammat", "Gammat_",Gammat, new_atom_list_Gammat, new_exp_list_Gammat,"q,qaux,dq,dqaux,time,param"); 




// ************************************************************************************************
// 	Export C code for Direct Simulation
// ************************************************************************************************

    cout << "Export C code for Direct Simulation " << endl;

    sys.export_Dynamic_Simulation(sys, ORDER , MAPLE);


// ************************************************************************************************
cout << "Init position and velocity " << endl;


system("rm *Init*");
Matrix PhiInit  = Matrix (2,1,&Phic,&Phit);
Matrix dPhiInit  = Matrix (2,1,&dPhic,&dPhit);
Matrix PhiInit_q = sys.jacobian(PhiInit.transpose(), Matrix (2,1,&q,&qaux));
Matrix dPhiInit_dq = sys.jacobian(dPhiInit.transpose(), Matrix (2,1,&dq,&dqaux));
Matrix BetaInit  = -dPhiInit;

for (int i=0; (i < dPhiInit.rows()); ++i) {
    BetaInit(i,0) = recursive_substitution (BetaInit(i,0),Velocities , 0);
    BetaInit(i,0) = recursive_substitution (BetaInit(i,0),Aux_Velocities , 0);
} 

lst new_atom_list_PhiInit, new_exp_list_PhiInit;
matrix_list_optimize (PhiInit, new_atom_list_PhiInit,new_exp_list_PhiInit);
sys.export_Matrix_C	("PhiInit","_PhiInit",PhiInit, new_atom_list_PhiInit, new_exp_list_PhiInit ,ORDER);
sys.export_function_MATLAB("PhiInit", "PhiInit_",PhiInit, new_atom_list_PhiInit, new_exp_list_PhiInit,"q,qaux,time,param"); 


lst new_atom_list_PhiInit_q, new_exp_list_PhiInit_q;
matrix_list_optimize (PhiInit_q, new_atom_list_PhiInit_q,new_exp_list_PhiInit_q);
sys.export_Matrix_C	("PhiInit_q","_PhiInit_q",PhiInit_q, new_atom_list_PhiInit_q, new_exp_list_PhiInit_q ,ORDER);
sys.export_function_MATLAB("PhiInit_q", "PhiInit_q_",PhiInit_q, new_atom_list_PhiInit_q, new_exp_list_PhiInit_q,"q,qaux,time,param"); 

lst new_atom_list_dPhiInit_dq, new_exp_list_dPhiInit_dq;
matrix_list_optimize (dPhiInit_dq, new_atom_list_dPhiInit_dq,new_exp_list_dPhiInit_dq);
sys.export_Matrix_C	("dPhiInit_dq","_dPhiInit_dq",dPhiInit_dq, new_atom_list_dPhiInit_dq, new_exp_list_dPhiInit_dq ,ORDER);
sys.export_function_MATLAB("dPhiInit_dq", "dPhiInit_dq_",dPhiInit_dq, new_atom_list_dPhiInit_dq, new_exp_list_dPhiInit_dq,"q,qaux,time,param"); 

lst new_atom_list_BetaInit, new_exp_list_BetaInit;
matrix_list_optimize (BetaInit, new_atom_list_BetaInit,new_exp_list_BetaInit);
sys.export_Matrix_C	("BetaInit","_BetaInit",BetaInit, new_atom_list_BetaInit, new_exp_list_BetaInit ,ORDER);
sys.export_function_MATLAB("BetaInit", "BetaInit_",BetaInit, new_atom_list_BetaInit, new_exp_list_BetaInit,"q,qaux,time,param"); 

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

    //sys.export_config_ini (  );

// ************************************************************************************************
//	Export C++ code for Openscenegraph
// ************************************************************************************************

    cout << "Export C++ code for Openscenegraph." << endl;

    //sys.export_open_scene_graph ( );


// ************************************************************************************************
//	Export State File
// ************************************************************************************************

    cout << "Export State File" << endl;

    lst state;
    //state = *dx, *dy, *dz, *da,*db, *dc;
    state = x, y, z, a,b, c,sR_R,sR_L,*dx, *dy;    
    /*state =   x, y, z, a, b, c,theta_W_R,u_W_R,theta_W_L,u_W_L,u_R_R,x_R_R ,u_R_L,x_R_L,
              awL,bwL,cwL,dwL,xwL,awR,bwR,cwR,dwR,xwR,arL,brL,crL,drL,xrL,arR,brR,crR,drR,xrR,
              *dx, *dy, *dz, *da, *db, *dc, *dtheta_W_R, *du_W_R, *dtheta_W_L, *du_W_L, *du_R_R, *dx_R_R , *du_R_L, *dx_R_L
              ;*/



    sys.export_write_data_file_C(state);
    sys.export_read_data_file_C(state);
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
if ( METHOD == LAGRANGE)              {	cout << "** Dynamic equations ===> LAGRANGE           **" << endl;}
else 	if ( METHOD == VIRTUAL_POWER) {	cout << "** Dynamic equations ===> VIRTUAL_POWER      **" << endl;}
if ( ORDER == CMO)                    {	cout << "** Matrix Order      ===> Col_MO             **" << endl;}
else 	if ( ORDER == RMO)            {	cout << "** Matrix Order      ===> Row_MO             **" << endl;}
if ( MAPLE == MAPLE_OFF)              {	cout << "** Maple             ===> OFF                **" << endl;}
else 	if ( MAPLE == MAPLE_ON)       {	cout << "** Maple             ===> ON                 **" << endl;}
                                     	cout << "***********************************************" << endl;



// ************************************************************************************************
//	END program
// ************************************************************************************************

return 0;

}

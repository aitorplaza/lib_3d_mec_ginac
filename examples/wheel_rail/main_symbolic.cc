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
cout << "*    v 1.0 Without  slipping                   *" << endl;
cout << "*    Aitor Plaza Dic 2012                      *" << endl;
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
    symbol_numeric x = *sys.new_Coordinate("x","dx","ddx",0.0 ,0.0,0.0);
    symbol_numeric y = *sys.new_Coordinate("y","dy","ddy",0.0 ,0.0,0.0);
    symbol_numeric z = *sys.new_Coordinate("z","dz","ddz",0.0 ,0.0,0.0);
    symbol_numeric a = *sys.new_Coordinate("a","da","dda",0.0 ,0.0,0.0);
    symbol_numeric b = *sys.new_Coordinate("b","db","ddb",0.0 ,0.0,0.0);
    symbol_numeric c = *sys.new_Coordinate("c","dc","ddc",0.0 ,0.0,0.0);

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

    //~ coord_indep_init =x, y, z, a, b, c;
    //~ vel_indep_init	=*dx, *dy, *dz, *da, *db, *dc;

// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************


	symbol_numeric b_pend = *sys.new_Parameter("b_pend",0.1);
	symbol_numeric L_R = *sys.new_Parameter("L_R",2.0);
	symbol_numeric LWHS= *sys.new_Parameter("LWHS",2.0);
	
// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************
    
    sys.new_Base("B_WHSc","xyz",0,0,1,c);
    sys.new_Base("B_WHSa","B_WHSc",1,0,0,a);
    sys.new_Base("B_WHS","B_WHSa",0,1,0,b);
   
    

    sys.new_Base("B_Rail","xyz",0,1,0, b_pend);//Base Rail

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

    Vector3D O_PRailR = *sys.new_Vector3D("O_PRailR",0,-L_R/2.0,0,"B_Rail");
    Vector3D O_PRailL = *sys.new_Vector3D("O_PRailL",0, L_R/2.0,0,"B_Rail");
    Vector3D O_PWHS = *sys.new_Vector3D("O_PWHS",x,y,z,"xyz");
    Vector3D PWHS_PWHSR = *sys.new_Vector3D("PWHS_PWHSR",0,-LWHS/2.0,0,"B_WHSa");
    Vector3D PWHS_PWHSL = *sys.new_Vector3D("PWHS_PWHSL",0, LWHS/2.0,0,"B_WHSa");

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
 
    Point * P_RailR = sys.new_Point("P_RailR","O",&O_PRailR);
    Point * P_RailL = sys.new_Point("P_RailL","O",&O_PRailL);
    Point * P_WHS   = sys.new_Point("P_WHS","O",&O_PWHS);
    Point * P_WHSR  = sys.new_Point("P_WHSR","P_WHS",&PWHS_PWHSR);
    Point * P_WHSL  = sys.new_Point("P_WHSL","P_WHS",&PWHS_PWHSL);
    
// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************



    symbol_numeric  mWHS = *sys.new_Parameter("mWHS",1.0);

    Vector3D OWHS_GWHS= *sys.new_Vector3D("OWHS_GWHS",0,0,0,"B_WHS");
    Vector3D OWHSR_GWHSR= *sys.new_Vector3D("OWHSR_GWHSR",0,0,0,"B_WHS");
    Vector3D OWHSL_GWHSL= *sys.new_Vector3D("OWHSL_GWHSL",0,0,0,"B_WHS");
    Tensor3D IWHS = *sys.new_Tensor3D("IWHS",(ex)1,(ex)0,(ex)0,(ex)0,(ex)1,(ex)0,(ex)0,(ex)0,(ex)1,"B_WHS");


   
// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Rail = sys.new_Frame("Fra_Rail","O","B_Rail");
	Frame * Fra_WHS  = sys.new_Frame("Fra_WHS","P_WHS","B_WHS");
	Frame * Fra_WHSR = sys.new_Frame("Fra_WHSR","P_WHSR","B_WHS");
	Frame * Fra_WHSL = sys.new_Frame("Fra_WHSL","P_WHSL","B_WHS");

	Frame_abs->set_scale(0.5);


// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	Solid * WHS   = sys.new_Solid("WHS","P_WHS","B_WHS","mWHS","OWHS_GWHS","IWHS","./solids/axe.stl",1,0,0,1.0);

	//Solid * WHS_R = sys.new_Solid("WHS_R","P_WHSR","B_WHS","mWHS","OWHSR_GWHSR","IWHS","./solids/disc.stl",1,0,0,0.8);
	//Solid * WHS_L = sys.new_Solid("WHS_L","P_WHSL","B_WHS","mWHS","OWHSR_GWHSR","IWHS","./solids/disc.stl",1,0,0,0.8);
	Solid * WHS_R = sys.new_Solid("WHS_R","P_WHSR","B_WHS","./solids/disc.stl",1,0,0,0.8);
	Solid * WHS_L = sys.new_Solid("WHS_L","P_WHSL","B_WHS","./solids/disc.stl",1,0,0,0.8);
	

	Solid * RailR = sys.new_Solid("RailR","P_RailR","B_Rail","./solids/rail.stl",1,0,1,1.0);
	Solid * RailL = sys.new_Solid("RailL","P_RailL","B_Rail","./solids/rail.stl",1,0,1,1.0);

// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

	cout << "Joint Unknown Definition" << endl;
	#if METHOD == LAGRANGE 
 
	symbol_numeric lambda1 = *sys.new_Joint_Unknown("lambda1");
	symbol_numeric lambda2 = *sys.new_Joint_Unknown("lambda2");
	symbol_numeric lambda3 = *sys.new_Joint_Unknown("lambda3");
	symbol_numeric lambda4 = *sys.new_Joint_Unknown("lambda4");
	symbol_numeric lambda5 = *sys.new_Joint_Unknown("lambda5");
	symbol_numeric lambda6 = *sys.new_Joint_Unknown("lambda6");
	symbol_numeric lambda7 = *sys.new_Joint_Unknown("lambda7");
	symbol_numeric lambda8 = *sys.new_Joint_Unknown("lambda8");
	symbol_numeric lambda9 = *sys.new_Joint_Unknown("lambda9");
	symbol_numeric lambda10 = *sys.new_Joint_Unknown("lambda10");
	symbol_numeric lambda11 = *sys.new_Joint_Unknown("lambda11");
	symbol_numeric lambda12 = *sys.new_Joint_Unknown("lambda12");
	symbol_numeric lambda13 = *sys.new_Joint_Unknown("lambda13");
	//~ symbol_numeric lambda14 = *sys.new_Joint_Unknown("lambda14");
	
	#endif
// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

	cout << "Input Vector" << endl;


// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************


// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;


	//	Gravity
	Wrench3D * Gravity_WHS = sys.Gravity_Wrench("WHS");
	//~ Wrench3D * Gravity_WHSR = sys.Gravity_Wrench("WHS_R");
	//~ Wrench3D * Gravity_WHSL = sys.Gravity_Wrench("WHS_L");

	//	Inertia
	Wrench3D * Inertia_WHS = sys.Inertia_Wrench("WHS");
	//~ Wrench3D * Inertia_WHSR = sys.Inertia_Wrench("WHS_R");
	//~ Wrench3D * Inertia_WHSL = sys.Inertia_Wrench("WHS_L");
	//	Constitutive


	//	Constraint

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
	
    symbol_numeric R = *sys.new_Parameter("R",1.0);
    symbol_numeric r = *sys.new_Parameter("r",0.99);
    symbol_numeric L = *sys.new_Parameter("L",0.1);
    symbol_numeric r_R = *sys.new_Parameter("r_R",0.1);
    
    symbol_numeric theta_W_R = *sys.new_Coordinate("theta_W_R","dtheta_W_R","ddtheta_W_R",0.0,0.0,0.0);
    symbol_numeric *dtheta_W_R=sys.get_Velocity("dtheta_W_R");
    symbol_numeric *ddtheta_W_R=sys.get_Acceleration("ddtheta_W_R");
    symbol_numeric y_W_R = *sys.new_Coordinate("y_W_R","dy_W_R","ddy_W_R",0.0 ,0.0,0.0);
    symbol_numeric *dy_W_R=sys.get_Velocity("dy_W_R");
    symbol_numeric *ddy_W_R=sys.get_Acceleration("ddy_W_R");
    
    symbol_numeric theta_W_L = *sys.new_Coordinate("theta_W_L","dtheta_W_L","ddtheta_W_L",0.0,0.0,0.0);
    symbol_numeric *dtheta_W_L=sys.get_Velocity("dtheta_W_L");
    symbol_numeric *ddtheta_W_L=sys.get_Acceleration("ddtheta_W_L");
    symbol_numeric y_W_L = *sys.new_Coordinate("y_W_L","dy_W_L","ddy_W_L",0.0 ,0.0,0.0);
    symbol_numeric *dy_W_L=sys.get_Velocity("dy_W_L");
    symbol_numeric *ddy_W_L=sys.get_Acceleration("ddy_W_L");
    
    symbol_numeric theta_R_R = *sys.new_Coordinate("theta_R_R","dtheta_R_R","ddtheta_R_R",0.0,0.0,0.0);
    symbol_numeric *dtheta_R_R=sys.get_Velocity("dtheta_R_R");
    symbol_numeric *ddtheta_R_R=sys.get_Acceleration("ddtheta_R_R");
    symbol_numeric x_R_R = *sys.new_Coordinate("x_R_R","dx_R_R","ddx_R_R",0.0,0.0,0.0);
    symbol_numeric *dx_R_R=sys.get_Velocity("dx_R_R");
    symbol_numeric *ddx_R_R=sys.get_Acceleration("ddx_R_R");

    symbol_numeric theta_R_L = *sys.new_Coordinate("theta_R_L","dtheta_R_L","ddtheta_R_L",0.0,0.0,0.0);
    symbol_numeric *dtheta_R_L=sys.get_Velocity("dtheta_R_L");
    symbol_numeric *ddtheta_R_L=sys.get_Acceleration("ddtheta_R_L");
    symbol_numeric x_R_L= *sys.new_Coordinate("x_R_L","dx_R_L","ddx_R_L",0.0,0.0,0.0);
    symbol_numeric *dx_R_L=sys.get_Velocity("dx_R_L");
    symbol_numeric *ddx_R_L=sys.get_Acceleration("ddx_R_L");



    //~ ex f_r=-R;
    ex f_r = -y_W_R*((R-r)/L)-((R+r)/2.0);
    Vector3D fWHSR = *sys.new_Vector3D("fWHSR",-f_r*sin(theta_W_R),y_W_R,f_r*cos(theta_W_R),"B_WHSa");
    Vector3D r_WHSR = sys.Position_Vector("O","P_WHSR")+fWHSR;
    Vector3D t1_WHSR= sys.diff ( r_WHSR , theta_W_R);
    Vector3D t2_WHSR= sys.diff ( r_WHSR , y_W_R);
    Vector3D n_WHSR = t1_WHSR^t2_WHSR;

    //~ ex f_l=-R;
    ex f_l = y_W_L*((R-r)/L)-((R+r)/2.0);
    Vector3D fWHSL = *sys.new_Vector3D("fWHSL",-f_l*sin(theta_W_L),y_W_L,f_l*cos(theta_W_L),"B_WHSa");
    Vector3D r_WHSL = sys.Position_Vector("O","P_WHSL")+fWHSL;
    Vector3D t1_WHSL= sys.diff ( r_WHSL , theta_W_L);
    Vector3D t2_WHSL= sys.diff ( r_WHSL , y_W_L);
    Vector3D n_WHSL = t1_WHSL^t2_WHSL;


    Vector3D f_RAILR = *sys.new_Vector3D("r_RAILR",x_R_R,r_R*sin(theta_R_R),r_R*cos(theta_R_R),"B_Rail");
    //~ Vector3D f_RAILR = *sys.new_Vector3D("f_RAILR",x_R_R,0.0,r_R,"B_Rail");
    Vector3D r_RAILR = sys.Position_Vector("O","P_RailR")+f_RAILR;
    Vector3D t1_RAILR = sys.diff ( r_RAILR , x_R_R);
    Vector3D t2_RAILR = sys.diff ( r_RAILR , theta_R_R);
    Vector3D n_RAILR = t1_RAILR^t2_RAILR;


    Vector3D f_RAILL = *sys.new_Vector3D("r_RAILL",x_R_L,r_R*sin(theta_R_L),r_R*cos(theta_R_L),"B_Rail");
    //~ Vector3D f_RAILL = *sys.new_Vector3D("f_RAILL",x_R_L,0.0,r_R,"B_Rail");
    Vector3D r_RAILL = sys.Position_Vector("O","P_RailL")+f_RAILL; 
    Vector3D t1_RAILL = sys.diff ( r_RAILL , x_R_L);
    Vector3D t2_RAILL = sys.diff ( r_RAILL , theta_R_L);
    Vector3D n_RAILL = t1_RAILL^t2_RAILL;  


	//Phi
   	Matrix Phi(10,1);

	Phi(0,0)=(r_WHSR-r_RAILR)(0,0);
	Phi(1,0)=(r_WHSR-r_RAILR)(1,0);
	Phi(2,0)=(r_WHSR-r_RAILR)(2,0);

	//~ Phi(3,0)=n_WHSR*t1_RAILR;
	//~ Phi(4,0)=n_WHSR*t2_RAILR;
	Phi(3,0)=n_RAILR*t1_WHSR;
	Phi(4,0)=n_RAILR*t2_WHSR;


	Phi(5,0)=(r_WHSL-r_RAILL)(0,0);
	Phi(6,0)=(r_WHSL-r_RAILL)(1,0);
	Phi(7,0)=(r_WHSL-r_RAILL)(2,0);

	//~ Phi(8,0)=n_WHSL*t1_RAILL;
	//~ Phi(9,0)=n_WHSL*t2_RAILL;
	Phi(8,0)=n_RAILL*t1_WHSL;
	Phi(9,0)=n_RAILL*t2_WHSL;
	
    Point * P_con_L   = sys.new_Point("P_con_L","O",&r_WHSL);
    Point * P_con_R   = sys.new_Point("P_con_R","O",&r_WHSR);
	Vector3D vel_PcL = sys.Velocity_Vector (Frame_abs , P_con_L, WHS);
	Vector3D vel_PcR = sys.Velocity_Vector (Frame_abs , P_con_R, WHS);

	//dPhiNH
   	Matrix dPhiNH(3,1);
        dPhiNH(0,0)=vel_PcL * t1_WHSL;
        dPhiNH(1,0)=vel_PcR * t1_WHSR;
        dPhiNH(2,0)=vel_PcR * t2_WHSR;




	coord_indep_init = x,y,b,c-0.05;
	vel_indep_init	=*db;




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
    sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE, dPhiNH);

    //sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);

// ************************************************************************************************
// 	Export C code for Direct Simulation 
// ************************************************************************************************

	cout << "Export C code for Direct Simulation " << endl;

    sys.export_Dynamic_Simulation(sys, ORDER , MAPLE, PROBLEM_TYPE);

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
	//~ state = x, y, z, a, b, c;
state = x, b,  *dx, *db;

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


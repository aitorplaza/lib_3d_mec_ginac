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
cout << "*    Dinámica de Sitemas Multicuerpo           *" << endl;
#ifdef DISC 
cout << "*    Disco                                     *" << endl;
#else
cout << "*    Elipse                                    *" << endl;
#endif
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


	symbol_numeric theta1 = *sys.new_Coordinate("theta1","dtheta1","ddtheta1", 1.05 , 0.0 , 0.0);
  	symbol_numeric theta2 = *sys.new_Coordinate("theta2","dtheta2","ddtheta2", 0.0 ,0.0 , 0.0);  
	symbol_numeric psi = *sys.new_Coordinate("psi","dpsi","ddpsi", 0.0 , 0.0 , 0.0);

	symbol_numeric y = *sys.new_AuxCoordinate("y","dy","ddy",2.1769,0,0);
	symbol_numeric z = *sys.new_AuxCoordinate("z","dz","ddz",-0.13019,0,0);

    // Initial positions and velocities
	symbol_numeric theta1_0 = *sys.new_Parameter("theta1_0",1.5);
	//symbol_numeric dtheta1_0 = *sys.new_Parameter("dtheta1_0",INITIAL_DTHETA1);
	symbol_numeric psi_0 = *sys.new_Parameter("psi_0",0.0);

	symbol_numeric *dtheta1=sys.get_Velocity("dtheta1");
	symbol_numeric *dtheta2=sys.get_Velocity("dtheta2");
	symbol_numeric *dpsi=sys.get_Velocity("dpsi");
	symbol_numeric *dy=sys.get_AuxVelocity("dy");
	symbol_numeric *dz=sys.get_AuxVelocity("dz");


	symbol_numeric *ddtheta1=sys.get_Acceleration("ddtheta1");
	symbol_numeric *ddtheta2=sys.get_Acceleration("ddtheta2");
	symbol_numeric *ddpsi=sys.get_Acceleration("ddpsi");
	symbol_numeric *ddy=sys.get_AuxAcceleration("ddy");
	symbol_numeric *ddz=sys.get_AuxAcceleration("ddz");

	lst coord_indep_init;
	lst vel_indep_init;

	coord_indep_init = (theta1-theta1_0), (psi-psi_0);
	//vel_indep_init	= (*dtheta1-dtheta1_0);

	
// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************


	symbol_numeric l1 = *sys.new_Parameter("l1",0.5);
	symbol_numeric l2 = *sys.new_Parameter("l2",1.5);
	symbol_numeric y0 = *sys.new_Parameter("y0",1.5);
	symbol_numeric z0 = *sys.new_Parameter("z0",-0.5);
	symbol_numeric alpha = *sys.new_Parameter("alpha",0.5);

	#ifdef DISC
	symbol_numeric r = *sys.new_Parameter("r",0.5);
	#elif defined ELLIPSE
    	symbol_numeric  b = *sys.new_Parameter("b",0.5);
    	symbol_numeric  a = *sys.new_Parameter("a",0.7);
	#endif

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

    sys.new_Base("B_ARM1" ,"xyz",1,0,0, theta1); //Base arm1
    //sys.new_Base("B_ARM2" ,"xyz",1,0,0, -theta2);//Base arm2    
    sys.new_Base("B_ARM2" ,"B_ARM1",1,0,0, -theta2);//Base arm2
    sys.new_Base("B_DISC" ,"xyz",1,0,0, -psi);   //Base disc
    sys.new_Base("B_PLANE","xyz",1,0,0, alpha);  //Base plane


// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

    Vector3D OA = *sys.new_Vector3D("OA",0,l1,0,"B_ARM1");
    Vector3D AG = *sys.new_Vector3D("AG",0,l2,0,"B_ARM2");
    Vector3D O_O1= *sys.new_Vector3D("O_O1",0,y0,z0,"xyz");
    Vector3D O_P = *sys.new_Vector3D("O_P",0,y,z,"xyz");


// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
    Point * A = sys.new_Point("A","O",&OA);//OArm2
    Point * G = sys.new_Point("G","A",&AG);//ODisc
    Point * O1 = sys.new_Point("O1","O",&O_O1);//OPlane
    Point * P = sys.new_Point("P","O1",&O_P);



// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************
	//viscosity
    symbol_numeric  Cvis = *sys.new_Parameter("Cvis",0.2);

    // Dynamic Parameters of Arm1

    symbol_numeric  mb1 = *sys.new_Parameter("mb1",1.0);

    symbol_numeric  I1b1 = *sys.new_Parameter("I1b1",0.1);
    symbol_numeric  I2b1 = *sys.new_Parameter("I2b1",0.1);
    symbol_numeric  I3b1 = *sys.new_Parameter("I3b1",0.1);
        
    Vector3D OArm1_GArm1= *sys.new_Vector3D("OArm1_GArm1",0,l1/2,0,"B_ARM1");

    Tensor3D IArm1 = *sys.new_Tensor3D("IArm1",(ex)I1b1,(ex)0,(ex)0,(ex)0,(ex)I2b1,(ex)0,(ex)0,(ex)0,(ex)I3b1,"B_ARM1");

    // Dynamic Parameters of Arm2

    symbol_numeric  mb2 = *sys.new_Parameter("mb2",1.0);

    symbol_numeric  I1b2 = *sys.new_Parameter("I1b2",0.1);
    symbol_numeric  I2b2 = *sys.new_Parameter("I2b2",0.1);
    symbol_numeric  I3b2 = *sys.new_Parameter("I3b2",0.1);
    
    Vector3D OArm2_GArm2= *sys.new_Vector3D("OArm2_GArm2",0,l2/2,0,"B_ARM2");

    Tensor3D IArm2 = *sys.new_Tensor3D("IArm2",(ex)I1b2,(ex)0,(ex)0,(ex)0,(ex)I2b2,(ex)0,(ex)0,(ex)0,(ex)I3b2,"B_ARM2");

    // Dynamic Parameters of Disc
    #ifdef DISC 
    symbol_numeric  mDisc = *sys.new_Parameter("mDisc",1.0);

    ex IDisc1=(1.0/2.0)*(r*r)*mDisc;
    ex IDisc2=(1.0/4.0)*(r*r)*mDisc;
    ex IDisc3=(1.0/4.0)*(r*r)*mDisc;

    Vector3D ODisc_GDisc= *sys.new_Vector3D("ODisc_GDisc",0,0,0,"B_DISC");

    Tensor3D IDisc = *sys.new_Tensor3D("IDisc",(ex)IDisc1,(ex)0,(ex)0,(ex)0,(ex)IDisc2,(ex)0,(ex)0,(ex)0,(ex)IDisc3,"B_DISC");

    // Dynamic Parameters of Disc
    #elif defined ELLIPSE
    symbol_numeric  mEllipse = *sys.new_Parameter("mEllipse",1.0);

    ex IEllipse1=(1.0/4.0)*(a*a+b*b)*mEllipse ;
    ex IEllipse2=(1.0/4.0)*(a*a)*mEllipse;
    ex IEllipse3=(1.0/4.0)*(b*b)*mEllipse;

    Vector3D OEllipse_GEllipse= *sys.new_Vector3D("OEllipse_GEllipse",0,0,0,"B_DISC");

    Tensor3D IEllipse = *sys.new_Tensor3D("IEllipse",(ex)IEllipse1,(ex)0,(ex)0,(ex)0,(ex)IEllipse2,(ex)0,(ex)0,(ex)0,(ex)IEllipse3,"B_DISC");
	#endif



// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Arm1 = sys.new_Frame("Fra_Arm1","O","B_ARM1");
	Frame * Fra_Arm2=sys.new_Frame("Fra_Arm2","A","B_ARM2");
	Frame * Fra_Disc=sys.new_Frame("Fra_Disc","G","B_DISC");
	Frame * Fra_Plane=sys.new_Frame("Fra_Plane","O1","B_PLANE");


// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	Solid * Arm1 = sys.new_Solid("Arm1","O","B_ARM1","mb1","OArm1_GArm1","IArm1");
	Solid * Arm2 = sys.new_Solid("Arm2","A","B_ARM2","mb2","OArm2_GArm2","IArm2");
	#ifdef DISC 
	Solid * Disc = sys.new_Solid("Disc","G","B_DISC","mDisc","ODisc_GDisc","IDisc");
	#elif defined ELLIPSE
	Solid * Ellipse = sys.new_Solid("Ellipse","G","B_DISC","mEllipse","OEllipse_GEllipse","IEllipse");
	#endif

// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

        Drawing3D * Arm1_3D = sys.new_Drawing3D("Arm1_3D","Arm1","./solids/arm1.stl",1,0,0,1.0);
        Drawing3D * Arm2_3D = sys.new_Drawing3D("Arm2_3D","Arm2","./solids/arm2.stl",1,0,0,1.0);
        Drawing3D * Plane_3D = sys.new_Drawing3D("Plane_3D","O1","B_PLANE","./solids/plane.stl",1,0,1,1.0);
	#ifdef DISC 
        Drawing3D * Disc_3D = sys.new_Drawing3D("Disc_3D","Disc","./solids/disc.stl",0,0,1,1.0);
	#elif defined ELLIPSE
        Drawing3D * Ellipse_3D = sys.new_Drawing3D("Ellipse_3D","Ellipse","./solids/ellipse.stl",0,0,1,1.0);
	#endif


        Drawing3D * FraARM1 = sys.new_Drawing3D("FraARM1",Fra_Arm1,0.1);
        Drawing3D * FraARM2 = sys.new_Drawing3D("FraARM2",Fra_Arm2,0.1);
        Drawing3D * FraDISC = sys.new_Drawing3D("FraDISC",Fra_Disc,0.1);
        Drawing3D * FraPLANE = sys.new_Drawing3D("FraPLANE",Fra_Plane,0.1);
        Drawing3D * FraABS = sys.new_Drawing3D("FraABS",Frame_abs,0.5);
Vector3D O_Prueba= sys.Position_Vector("O","P");
//~ cout <<" O_Prueba= " <<O_Prueba <<endl;
Drawing3D * VectorPrueba = sys.new_Drawing3D("VectorPrueba",&O_Prueba,Point_O,1,1,0,1.0);   
// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

	cout << "Joint Unknown Definition" << endl;

	#if METHOD == LAGRANGE 
	symbol_numeric lambda1 = *sys.new_Joint_Unknown("lambda1");
	symbol_numeric lambda2 = *sys.new_Joint_Unknown("lambda2");
	symbol_numeric lambda3 = *sys.new_Joint_Unknown("lambda3");
	symbol_numeric lambda4 = *sys.new_Joint_Unknown("lambda4");
	#endif

	#if METHOD == VIRTUAL_POWER
	//Link Ground - Arm1
	symbol_numeric Fsb12 = *sys.new_Joint_Unknown("Fsb12");
	symbol_numeric Fsb13 = *sys.new_Joint_Unknown("Fsb13");

	//Link Arm1 - Arm2
	symbol_numeric Fb1b22 = *sys.new_Joint_Unknown("Fb1b22");
	symbol_numeric Fb1b23 = *sys.new_Joint_Unknown("Fb1b23");

	//Link Arm2 - disc/ellipse
	symbol_numeric Fb2d2 = *sys.new_Joint_Unknown("Fb2d2");
	symbol_numeric Fb2d3 = *sys.new_Joint_Unknown("Fb2d3");

	//Link Plane - disc/ellipse
	symbol_numeric Fsd2  = *sys.new_Joint_Unknown("Fsd2");
	symbol_numeric Fsd3  = *sys.new_Joint_Unknown("Fsd3");
	#endif

// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

	cout << "Input Vector" << endl;

	symbol_numeric Torque = *sys.new_Input("Torque",0.0);

	Vector3D FArm1 = *sys.new_Vector3D("FArm1",0,0,0,"xyz");
	Vector3D MArm1 = *sys.new_Vector3D("MArm1",Torque,0,0,"xyz");


// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************

	//Viscosity 
	Vector3D MV_Arm1 = -Cvis* sys.Angular_Velocity("xyz" ,"B_ARM1" );
	Vector3D FK_Arm1 = *sys.new_Vector3D("FK_arm1",0,0,0, "xyz");

	#if METHOD == VIRTUAL_POWER
	//Link Ground - Arm1	
	Vector3D Fsb1 = *sys.new_Vector3D("Fsb1",0,Fsb12,Fsb13,"xyz");
	Vector3D Msb1 = *sys.new_Vector3D("Msb1",0,0,0, "xyz");

	//Link Arm1 - Arm2
	Vector3D Fb1b2 = *sys.new_Vector3D("Fb1b2",0,Fb1b22,Fb1b23,"B_ARM1");
	Vector3D Mb1b2 = *sys.new_Vector3D("Mb1b2",0,0,0, "B_ARM1");

	//Link Arm2 - Disc
	Vector3D Fb2d = *sys.new_Vector3D("Fb2d",0,Fb2d2,Fb2d3,"B_ARM2");
	Vector3D Mb2d = *sys.new_Vector3D("Mb2d",0,0,0,"B_ARM2");

	//Link Plane - Disc/Ellipse
	Vector3D Fsd = *sys.new_Vector3D("Fsd",0,Fsd2,Fsd3,"B_PLANE");
	Vector3D Msd = *sys.new_Vector3D("Msd",0,0,0,"B_PLANE");
	#endif

// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;


	//	Gravity
	Wrench3D * Gravity_Arm1 = sys.Gravity_Wrench("Arm1");
	Wrench3D * Gravity_Arm2 = sys.Gravity_Wrench("Arm2");
	#ifdef DISC
	  Wrench3D * Gravity_Disc = sys.Gravity_Wrench("Disc");
	#elif defined ELLIPSE
	  Wrench3D * Gravity_Ellipse = sys.Gravity_Wrench("Ellipse");
	#endif

	//	Inertia
	Wrench3D * Inertia_Arm1 = sys.Inertia_Wrench("Arm1");
	Wrench3D * Inertia_Arm2 = sys.Inertia_Wrench("Arm2");
	#ifdef DISC
	  Wrench3D * Inertia_Disc = sys.Inertia_Wrench("Disc");
	#elif defined ELLIPSE
	  Wrench3D * Inertia_Ellipse = sys.Inertia_Wrench("Ellipse");
	#endif


	//	Constitutive
	Wrench3D * Viscosity_arm1 = sys.new_Wrench3D ( "Viscosity", FK_Arm1, MV_Arm1, Point_O , Arm1 , "Constitutive") ;

	//	Constraint
	#if METHOD == VIRTUAL_POWER

	  Wrench3D * ground_arm1 = sys.new_Wrench3D ( "ground_arm1",Fsb1, Msb1, Point_O , Arm1 , "Constraint") ;

	  //Action-reaction
	  Wrench3D * arm1_arm2 = sys.new_Wrench3D ( "arm1_arm2", Fb1b2, Mb1b2 , A , Arm1 , Arm2 ,"Constraint") ;

	  #ifdef DISC
	  Wrench3D * arm2_disc = sys.new_Wrench3D ( "arm2_disc", Fb2d, Mb2d, G , Arm2 ,Disc,  "Constraint") ;
	  Wrench3D * plane_disc = sys.new_Wrench3D ( "plane_disc", Fsd, Msd, P , Plane, Disc, "Constraint") ;
	  #elif defined ELLIPSE
	  Wrench3D * arm2_ellipse = sys.new_Wrench3D ( "arm2_ellipse", Fb2d, Mb2d, G , Arm2 ,Ellipse,  "Constraint") ;
	  Wrench3D * plane_ellipse = sys.new_Wrench3D ( "plane_ellipse", Fsd, Msd, P , Plane, Ellipse, "Constraint") ;
	  #endif

	#endif

	//	External
	Wrench3D * Arm1_Impulse = sys.new_Wrench3D ( "Arm1_Impulse", FArm1, MArm1, Point_O, Arm1 , "External") ;

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


	//Auxiliary vetors
	Vector3D norm_plane = *sys.new_Vector3D("norm_plane",0,0,1,"B_PLANE");
	Vector3D tan_plane = *sys.new_Vector3D("tan_plane",0,1,0,"B_PLANE");

	Vector3D G_P = sys.Position_Vector("G","P");


	#ifdef DISC
	ex curve_eq= (G_P * G_P)-(r*r);         
	#elif defined ELLIPSE
	ex Elipse1= 1;
	ex Elipse2= 1/(a*a);
	ex Elipse3= 1/(b*b);
	Tensor3D MElipse = *sys.new_Tensor3D("MElipse",(ex)Elipse1,(ex)0,(ex)0,(ex)0,(ex)Elipse2,(ex)0,(ex)0,(ex)0,(ex)Elipse3,"B_DISC");
	ex curve_eq= (G_P * (MElipse * G_P))-1; 
	#endif

	ex aux1= sys.diff ( curve_eq , y);
	ex aux2= sys.diff ( curve_eq , z);

  
	Vector3D normal = * sys.new_Vector3D("normal",0,aux1,aux2,"xyz");

	//Phi
   	Matrix Phi(3,1);
	Phi(0,0)=curve_eq;
	Phi(1,0)=sys.Position_Vector("O1","P") * norm_plane ;
	Phi(2,0)=normal*tan_plane;


	//No-Slip Equations
	#ifdef DISC
	Vector3D vel_P = sys.Velocity_Vector (Frame_abs , P, Disc);
	#elif defined ELLIPSE
	Vector3D vel_P = sys.Velocity_Vector (Frame_abs , P, Ellipse);
	#endif

   	Matrix dPhiNH(1,1);
	dPhiNH(0,0)= vel_P * tan_plane;
    

// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************

	cout << "Dynamic Equations" << endl;

	Matrix Dynamic_Equations = sys.GenForceSys("ALL");
    //~ Matrix Dynamic_Equations(0,0);

// ************************************************************************************************
// 	Output Vector
// ************************************************************************************************
	cout << "Output Vector" << endl;

	Matrix Output(4,1);
	Output(0,0)=lambda1;
	Output(1,0)=lambda2;
	Output(2,0)=lambda3;
	Output(3,0)=lambda4;
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

    sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, dPhiNH);
        
        
// ************************************************************************************************
// 	Export C code for Direct Simulation 
// ************************************************************************************************

	cout << "Export C code for Direct Simulation " << endl;

    sys.export_Dynamic_Simulation(sys, ORDER , MAPLE);


    cout <<"atomos = " << atoms.size()<<endl;

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

	#if METHOD == LAGRANGE
	//state = theta1, theta2, psi, y, z, *dtheta1, *dtheta2, *dpsi, *ddtheta1, *ddtheta2, *ddpsi, lambda1,lambda2,lambda3,lambda4;
	state = theta1, theta2, psi,y,z;
	#endif
	#if METHOD == VIRTUAL_POWER
    	state = theta1, theta2, psi, y, z, *dtheta1, *dtheta2, *dpsi, *ddtheta1, *ddtheta2, *ddpsi, Fsb12, Fsb13, Fb1b22, Fb1b23, Fb2d2, Fb2d3, Fsd2, Fsd3;
	#endif

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


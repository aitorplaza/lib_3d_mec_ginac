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
	printf("}	
	
#ifdef PROCEDURE
int C_EXPORT_AS_PROCEDURE=1;
#else
int C_EXPORT_AS_PROCEDURE=0;
#endif


int main(int argc, char *argv[]) {

// *****************************************************************************************************************	
cout << " " << endl;
cout << "************************************************" << endl;
cout << "*             Puma Serial Robot                *" << endl;
cout << "************************************************" << endl;
cout << " " << endl;
system("date");
cout << " " << endl;
// *****************************************************************************************************************	

if (argc!=3){
        printf("Error: The program         exit(1);
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
        printf("Error: The program         exit(1);
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
        printf("Error: The program         exit(1);
    }
}

// ************************************************************************************************

	double integration_time=strtod(argv[1], NULL);
	double delta_t= strtod(argv[2], NULL);
	long int k,steps;
	
	printf("integration_time 
// ************************************************************************************************
//	System definition
// ************************************************************************************************

	System sys(&printError2);

// ************************************************************************************************
//	TIME DEFINITION
// ************************************************************************************************
        symbol_numeric t=sys.get_Time_Symbol ( );

// ************************************************************************************************
//	Coordinate definition
// ************************************************************************************************

	// Rotation angles from root to leaf
	symbol_numeric q1 = *sys.new_Coordinate("q1","dq1","ddq1", 0.0 , 0.0 , 0.0);
	symbol_numeric q2 = *sys.new_Coordinate("q2","dq2","ddq2", 0.0 , 0.0 , 0.0);

	// Velocities
	symbol_numeric *dq1=sys.get_Velocity("dq1");
	symbol_numeric *dq2=sys.get_Velocity("dq2");

	// Accelerations
	symbol_numeric *ddq1=sys.get_Acceleration("ddq1");
	symbol_numeric *ddq2=sys.get_Acceleration("ddq2");


// ************************************************************************************************
//	Initial Position Additional Constraint Equations
// ************************************************************************************************

	lst coord_indep_init;
	lst vel_indep_init;

//	coord_indep_init = (q1-0.0),(q2-0.0);


// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	
	// Geometric Parameters
	symbol_numeric a1 = *sys.new_Parameter("a1",0);
	symbol_numeric b1 = *sys.new_Parameter("b1",0);
	symbol_numeric c1 = *sys.new_Parameter("c1",0);
	symbol_numeric a2 = *sys.new_Parameter("a2",0);
	symbol_numeric b2 = *sys.new_Parameter("b2",0);
	symbol_numeric c2 = *sys.new_Parameter("c2",0);



// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************


	sys.new_Base("B0" ,"xyz", 0,0,1,0);		// Creating a base fixed to the ground
	sys.new_Base("B1a","B0" , 1,0,0,b1);	// Rotation wrt x0
	sys.new_Base("B1" ,"B1a", 0,0,1,q1);	// Rotation wrt z1
	sys.new_Base("B2a","B1" , 1,0,0,b2);	// Rotation wrt x1
	sys.new_Base("B2" ,"B2a", 0,0,1,q2);	// Rotation wrt z2


// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	Vector3D P0P1  = *sys.new_Vector3D("P0P1a",a1, 0,0,"B0") + *sys.new_Vector3D("P0P1b", 0,0,c1, "B1");
	Vector3D P1P2  = *sys.new_Vector3D("P1P2a",a2, 0,0,"B1") + *sys.new_Vector3D("P1P2b", 0,0,c2, "B2");
	
// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * P1 = sys.new_Point("P1","P0", &P0P1);
	Point * P2 = sys.new_Point("P2","P1", &P1P2);

// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Inertial parameters of the Solid 1
	symbol_numeric  m1   = *sys.new_Parameter("m1",  1.0);
	symbol_numeric  mx1  = *sys.new_Parameter("mx1", 0.0);
	symbol_numeric  my1  = *sys.new_Parameter("my1", 0.0);
	symbol_numeric  mz1  = *sys.new_Parameter("mz1", 0.0);
	symbol_numeric  Ixx1 = *sys.new_Parameter("Ixx1",1.0);
	symbol_numeric  Ixy1 = *sys.new_Parameter("Ixy1",0.0);
	symbol_numeric  Ixz1 = *sys.new_Parameter("Ixz1",0.0);
	symbol_numeric  Iyy1 = *sys.new_Parameter("Iyy1",1.0);
	symbol_numeric  Iyz1 = *sys.new_Parameter("Iyz1",0.0);
	symbol_numeric  Izz1 = *sys.new_Parameter("Izz1",1.0);


	// Inertial parameters of the Solid 2
	symbol_numeric  m2   = *sys.new_Parameter("m2",  1.0);
	symbol_numeric  mx2  = *sys.new_Parameter("mx2", 0.0);
	symbol_numeric  my2  = *sys.new_Parameter("my2", 0.0);
	symbol_numeric  mz2  = *sys.new_Parameter("mz2", 0.0);
	symbol_numeric  Ixx2 = *sys.new_Parameter("Ixx2",1.0);
	symbol_numeric  Ixy2 = *sys.new_Parameter("Ixy2",0.0);
	symbol_numeric  Ixz2 = *sys.new_Parameter("Ixz2",0.0);
	symbol_numeric  Iyy2 = *sys.new_Parameter("Iyy2",1.0);
	symbol_numeric  Iyz2 = *sys.new_Parameter("Iyz2",0.0);
	symbol_numeric  Izz2 = *sys.new_Parameter("Izz2",1.0);


// ************************************************************************************************
//	Center of Gravity Vectors
// ************************************************************************************************

	Vector3D P1G1= *sys.new_Vector3D("P1G1",mx1/m1,my1/m1,mz1/m1,"B1");
	Vector3D P2G2= *sys.new_Vector3D("P2G2",mx2/m2,my2/m2,mz2/m2,"B2");

// ************************************************************************************************
//	Inertia Tensors
// ************************************************************************************************

    	Tensor3D I1 = *sys.new_Tensor3D("I1",	(ex)Ixx1,(ex)Ixy1,(ex)Ixz1,
						(ex)Ixy1,(ex)Iyy1,(ex)Iyz1,
						(ex)Ixz1,(ex)Iyz1,(ex)Izz1,"B1");
// -----------------------------------------------------------------------
    	Tensor3D I2 = *sys.new_Tensor3D("I2",	(ex)Ixx2,(ex)Ixy2,(ex)Ixz2,
						(ex)Ixy2,(ex)Iyy2,(ex)Iyz2,
						(ex)Ixz2,(ex)Iyz2,(ex)Izz2,"B2");
// -----------------------------------------------------------------------

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_0= sys.new_Frame("Fra_0","P0","B0");
	Frame * Fra_1= sys.new_Frame("Fra_1","P1","B1");
	Frame * Fra_2= sys.new_Frame("Fra_2","P2","B2");


// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	Solid * BAR1 = sys.new_Solid("BAR1","P1","B1","m1","P1G1","I1");
	Solid * BAR2 = sys.new_Solid("BAR2","P2","B2","m2","P2G2","I2");

// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

//	Drawing3D * BAR1_3D = sys.new_Drawing3D("BAR1_3D", BAR1,"./solids/solid_1.stl" ,1,0,0,0.5);
//	Drawing3D * BAR2_3D = sys.new_Drawing3D("BAR2_3D", BAR2,"./solids/solid_2.stl" ,1,0,0,0.5);
	Drawing3D * Fra_BAR0_3D = sys.new_Drawing3D("Fra_BAR0_3D","Fra_0",0.1);
	Drawing3D * Fra_BAR1_3D = sys.new_Drawing3D("Fra_BAR1_3D","Fra_1",0.1);
	Drawing3D * Fra_BAR2_3D = sys.new_Drawing3D("Fra_BAR2_3D","Fra_2",0.1);



// ************************************************************************************************
//	Forces Definition
// ************************************************************************************************

	symbol_numeric Ma1 = *sys.new_Parameter("Ma1",0.0);
	symbol_numeric Ma2 = *sys.new_Parameter("Ma2",0.0);

	Vector3D F1 = *sys.new_Vector3D("F1",0.0,0.0,0.0, "B1");	
	Vector3D F2 = *sys.new_Vector3D("F2",0.0,0.0,0.0, "B2");	

	Vector3D M1 = *sys.new_Vector3D("M1",0.0,0.0,Ma1, "B1");
	Vector3D M2 = *sys.new_Vector3D("M2",0.0,0.0,Ma2, "B2");

// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

// 	//	Gravity
	Wrench3D * Gravity1 = sys.Gravity_Wrench("BAR1");
	Wrench3D * Gravity2 = sys.Gravity_Wrench("BAR2");
// 
	//	Inertia
	Wrench3D * Inertia_1 = sys.Inertia_Wrench("BAR1");
	Wrench3D * Inertia_2 = sys.Inertia_Wrench("BAR2");
	
	//	External Moments
	Wrench3D * WExternalAction1 = sys.new_Wrench3D ( "WExternalAction1", F1, M1, P1 , BAR1 , "Constitutive");
	Wrench3D * WExternalAction2 = sys.new_Wrench3D ( "WExternalAction2", F2, M2, P2 , BAR2 , "Constitutive");
	
	Wrench3D * WExternalReaction2 = sys.new_Wrench3D ( "WExternalReaction2", -F2, -M2, P2 , BAR1 , "Constitutive") ;


	symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");
	symbol_numeric lambda2  = *sys.new_Joint_Unknown("lambda2");
	symbol_numeric lambda3  = *sys.new_Joint_Unknown("lambda3");
	symbol_numeric lambda4  = *sys.new_Joint_Unknown("lambda4");
	symbol_numeric lambda5  = *sys.new_Joint_Unknown("lambda5");
	symbol_numeric lambda6  = *sys.new_Joint_Unknown("lambda6");


// ************************************************************************************************
// 	Vectors needed to take diferent Jacobians
// ************************************************************************************************

	cout << "Vectors needed to take diferent Jacobians" << endl;

	Matrix q = sys.Coordinates();
	Matrix dq = sys.Velocities();
	Matrix ddq = sys.Accelerations();
	Matrix pars = sys.Parameters();
// 	Matrix inps = sys.Inputs();
	Matrix unks = sys.Joint_Unknowns();

// ************************************************************************************************
// 	 Parameters for the Trajectory optimization 
// ************************************************************************************************
// // Constante term of the Fourier Series
 	symbol_numeric  FS001 = *sys.new_Parameter("FS001",0.0);
 	symbol_numeric  FS002 = *sys.new_Parameter("FS002",0.0);

// Harmonic number 1 of the Fourier Series	
 	symbol_numeric  FSa11 = *sys.new_Parameter("FSa11",0.0);
 	symbol_numeric  FSb11 = *sys.new_Parameter("FSb11",0.0);
 	symbol_numeric  FSa12 = *sys.new_Parameter("FSa12",0.0);
 	symbol_numeric  FSb12 = *sys.new_Parameter("FSb12",0.0);

// Harmonic number 2 of the Fourier Series	
 	symbol_numeric  FSa21 = *sys.new_Parameter("FSa21",0.0);
 	symbol_numeric  FSb21 = *sys.new_Parameter("FSb21",0.0);
 	symbol_numeric  FSa22 = *sys.new_Parameter("FSa22",0.0);
 	symbol_numeric  FSb22 = *sys.new_Parameter("FSb22",0.0);

// Harmonic number 3 of the Fourier Series	
 	symbol_numeric  FSa31 = *sys.new_Parameter("FSa31",0.0);
 	symbol_numeric  FSb31 = *sys.new_Parameter("FSb31",0.0);
 	symbol_numeric  FSa32 = *sys.new_Parameter("FSa32",0.0);
 	symbol_numeric  FSb32 = *sys.new_Parameter("FSb32",0.0);



// ************************************************************************************************
// 	 Kinematic Equations 
// ************************************************************************************************
	cout << "Kinematic Equations = " << endl;

	Matrix Phi(2,1);

	
 	Phi(0,0)=q1-(FS001 	+FSa11*sin(1*t)+FSb11*cos(1*t)	+FSa21*sin(2*t)+FSb21*cos(2*t)	+FSa31*sin(3*t)+FSb31*cos(3*t));
 	Phi(1,0)=q2-(FS002 	+FSa12*sin(1*t)+FSb12*cos(1*t)	+FSa22*sin(2*t)+FSb22*cos(2*t)	+FSa32*sin(3*t)+FSb32*cos(3*t));

// 	Matrix dPhiNH(0,1);


// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************

	cout << "Dynamic Equations = " << endl;

	Matrix Dynamic_Equations = sys.GenForceSys("ALL");
	//cout<<Dynamic_Equations<<endl;

	lst inertial_parameters;

	inertial_parameters =
							m1, mx1, my1, mz1, Ixx1, Ixy1, Ixz1, Iyy1, Iyz1, Izz1,
							m2, mx2, my2, mz2, Ixx2, Ixy2, Ixz2, Iyy2, Iyz2, Izz2;


	cout << "W and Phiq Matrix Calculation= " << endl;

	Matrix M_inertial_parameters=Matrix(inertial_parameters.nops(),1,inertial_parameters);
	Matrix W = sys.jacobian(Dynamic_Equations.transpose(),M_inertial_parameters);
	Matrix Phiq= sys.jacobian(Phi.transpose(),q);

	
	cout << "Exporting Matrix W" << endl;
	lst new_atom_list_W, new_exp_list_W;        
	matrix_list_optimize (W, new_atom_list_W, new_exp_list_W);
	sys.export_Matrix_C("W","_W",W, new_atom_list_W, new_exp_list_W ,ORDER);
	sys.export_function_MATLAB("W", "W_", W, new_atom_list_W, new_exp_list_W);

	cout << "Exporting MATLAB functions" << endl;
	sys.export_init_function_MATLAB();


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
	
// 	Usa (necesita que estén definidas) las ecuaciones dinámicas y deriva respecto a qpp y necesita que estén definidos los torsores de inercia
// 	sys.Matrix_Calculation(Phi, coord_indep_init, vel_indep_init, Dynamic_Equations, sys, METHOD);
	
// 	Calcula las matrices M y Q sin las ecuaciones de la dinámica
	sys.Matrix_Calculation( Phi, coord_indep_init, vel_indep_init, sys, METHOD);

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

    	state = 	a1,*da1,*dda1,
		a2,*da2,*dda2,
		a3,*da3,*dda3;
// 		a4,*da4,*dda4,
// 		a5,*da5,*dda5,
// 		a6,*da6,*dda6;

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

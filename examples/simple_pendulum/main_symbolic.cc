/*
//cp ../common_code/* .
touch atom_def.c
export LD_LIBRARY_PATH=`pwd`/../../../lib/
export PKG_CONFIG_PATH=`pwd`/../../../lib/pkgconfig
g++ -o main_Block_Pendulum main_Block_Pendulum.cc `pkg-config --cflags --libs lib_3d_mec_ginac-1.1 ginac cln gsl`

./main_Block_Pendulum DOWN NO
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
cout << "*             Simple  Pendulum                 *" << endl;
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

	symbol_numeric theta = *sys.new_Coordinate("theta","dtheta","ddtheta", 0.0 , 0.0 , 0.0);

	symbol_numeric theta_0 = *sys.new_Parameter("theta_0",3.0);
	symbol_numeric dtheta_0 = *sys.new_Parameter("dtheta_0",0.0);

	symbol_numeric *dtheta=sys.get_Velocity("dtheta");

	symbol_numeric *ddtheta=sys.get_Acceleration("ddtheta");

	lst coord_indep_init;
	lst vel_indep_init;

	coord_indep_init = (theta-theta_0);
	vel_indep_init	= (*dtheta-dtheta_0);


// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	symbol_numeric l = *sys.new_Parameter("l",1);


// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

 	sys.new_Base("BPendulum","xyz",0,1,0,-theta);

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	Vector3D O_OPendulum = *sys.new_Vector3D("O_OPendulum",0,0,0,"xyz");

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * OPendulum= sys.new_Point("OPendulum","O",&O_OPendulum);


// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Viscosity
       	symbol_numeric  Cvis = *sys.new_Parameter("Cvis",0.8);

	// Torsion spring
       	symbol_numeric  K = *sys.new_Parameter("K",1.0);


	// Dynamic Parameters of Pendulum

    	symbol_numeric  mPen = *sys.new_Parameter("mPen",1.0);
    	symbol_numeric  Iyy = *sys.new_Parameter("Iyy",1.0);
	//ex Iyy=(l*l)*mPen;

	//Gravity Center Vectors    

	Vector3D OPendulum_GPendulum= *sys.new_Vector3D("OPendulum_GPendulum",0,0,-l,"BPendulum");


	//Inertia Tensors

	Tensor3D IPendulum_OP = *sys.new_Tensor3D("IPendulum_OP",0,0,0,0,Iyy,0,0,0,0,"BPendulum");

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************


	Frame * Fra_Pendulum=sys.new_Frame("Fra_Pendulum","OPendulum","BPendulum");


// ************************************************************************************************
//	Define Solids
// ************************************************************************************************


	Solid * Pendulum = sys.new_Solid("Pendulum","OPendulum" ,"BPendulum" ,"mPen","OPendulum_GPendulum","IPendulum_OP");

// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

        Drawing3D * FraABS = sys.new_Drawing3D("FraABS",Frame_abs,0.5);
        Drawing3D * FraPENDULUM = sys.new_Drawing3D("FraPENDULUM",Fra_Pendulum,0.1);

        //Drawing3D * Pendulum3D = sys.new_Drawing3D("Pendulum3D","Pendulum","./solids/pendulum.stl",0,1,0,0.8);	

	Point * Point1 = sys.new_Point("Point1","OPendulum",&OPendulum_GPendulum);	
        Drawing3D * PointPend = sys.new_Drawing3D("PointPend",Point1,0.1,1.0,1.0,0.0,1.0);

// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

	cout << "Joint Unknown Definition" << endl;



// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

	cout << "Input Vector" << endl;

	//symbol_numeric MPendulumy = *sys.new_Input("MPendulumy",0.0);

	//Vector3D FPendulum = *sys.new_Vector3D("FPendulum",0,0,0,"BPendulum");
	//Vector3D MPendulum = *sys.new_Vector3D("MPendulum",0,MPendulumy,0, "BPendulum");


// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************

	//Vector3D FK_BlockPend = *sys.new_Vector3D("FK_BlockPend",0,0,0, "BBlock");
	//Vector3D MK_BlockPend = *sys.new_Vector3D("MK_BlockPend",0,K*(theta-theta_0),0, "BBlock");

	//Vector3D FV_BlockGuide = -Cvis * sys.Velocity_Vector("abs" ,"A", "Block" );
	//Vector3D MV_BlockGuide= *sys.new_Vector3D("MV_BlockGuide",0,0,0,"xyz");


// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * Gravity_Pendulum = sys.Gravity_Wrench("Pendulum");


	//	Inertia
	Wrench3D * Inertia_Pendulum = sys.Inertia_Wrench("Pendulum");


	//	Constitutive
	//Wrench3D * Viscosity = sys.new_Wrench3D ( "Viscosity", FV_BlockGuide, MV_BlockGuide, A , Block , "Constitutive") ;
	//Wrench3D * Torsional_Pendulum = sys.new_Wrench3D ( "Torsional_Pendulum ", FK_BlockPend , MK_BlockPend , E , Pendulum , "Constitutive") ;

	//	External
	//Wrench3D * Pendulum_Impulse = sys.new_Wrench3D ( "Pendulum_Impulse", FPendulum, MPendulum, E , Pendulum , "External") ;
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
	//Matrix Phi(0,1);
	//Matrix dPhiNH(0,1);

// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************

	cout << "Dynamic Equations" << endl;

	Matrix Dynamic_Equations = sys.GenForceSys("ALL");
	//cout<<Dynamic_Equations<<endl;

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

        sys.Matrix_Calculation(coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);

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

    	state = theta,*dtheta, *ddtheta;

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

cout<<Dynamic_Equations<<endl;

// ************************************************************************************************
//	END program
// ************************************************************************************************

return 0;

}


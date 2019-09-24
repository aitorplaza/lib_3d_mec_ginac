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
cout << "*              Double Pendulum                 *" << endl;
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
        #define INITIAL_THETA1 3.1416/2.0
        #define INITIAL_THETA2 3.1416/2.0
        #define INITIAL_DTHETA1 0.0
        #define INITIAL_DTHETA2 0.0

	// theta1 = 0 with Pendulum1 vertical down	
	symbol_numeric theta1 = *sys.new_Coordinate("theta1","dtheta1","ddtheta1", 3.141592/2.0 ,0.0 , 0.0);
	// theta2 = 0 with Pendulum2 aligned with Pendulum1	
	symbol_numeric theta2 = *sys.new_Coordinate("theta2","dtheta2","ddtheta2", 3.141592/2.0 , 0.0 , 0.0);

	symbol_numeric theta1_0 = *sys.new_Parameter("theta1_0",3.141592/2.0);
	symbol_numeric dtheta1_0 = *sys.new_Parameter("dtheta1_0",0.0);
	symbol_numeric theta2_0 = *sys.new_Parameter("theta2_0",3.141592/2.0);
	symbol_numeric dtheta2_0 = *sys.new_Parameter("dtheta2_0",0.0);

	symbol_numeric *dtheta1=sys.get_Velocity("dtheta1");
	symbol_numeric *dtheta2=sys.get_Velocity("dtheta2");

	symbol_numeric *ddtheta1=sys.get_Acceleration("ddtheta1");
	symbol_numeric *ddtheta2=sys.get_Acceleration("ddtheta2");

	lst coord_indep_init;
	lst vel_indep_init;

	//coord_indep_init = (theta1-theta1_0), (theta2-theta2_0);
	//vel_indep_init	= (*dtheta1-dtheta1_0),(*dtheta2-dtheta2_0);



// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	// Pendulum length
	symbol_numeric l1 = *sys.new_Parameter("l1",1.0);
	symbol_numeric l2 = *sys.new_Parameter("l2",1.0);


// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

  	sys.new_Base("BPendulum1","xyz",0,1,0,-theta1);
  	//sys.new_Base("BPendulum2","BPendulum1",0,1,0,-theta2);
    sys.new_Base("BPendulum2","xyz",0,1,0,-theta2);

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************


	Vector3D O_OPendulum1=*sys.new_Vector3D("O_OPendulum1",0,0,0,"BPendulum1");
	Vector3D OPend1_OPend2=*sys.new_Vector3D("OPen1_OPend2",0,0,-l1,"BPendulum1");


// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * OPendulum1= sys.new_Point("OPendulum1","O",&O_OPendulum1);
	Point * OPendulum2= sys.new_Point("OPendulum2","OPendulum1",&OPend1_OPend2);


// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Viscosity
       	symbol_numeric  Cvis1 = *sys.new_Parameter("Cvis1",0.3);
       	symbol_numeric  Cvis2 = *sys.new_Parameter("Cvis2",0.3);

	// Torsion spring
       	symbol_numeric  K1 = *sys.new_Parameter("K1",0.0);
       	symbol_numeric  thetaK1 = *sys.new_Parameter("thetaK1",0.0);
       	symbol_numeric  K2 = *sys.new_Parameter("K2",0.0);
       	symbol_numeric  thetaK2 = *sys.new_Parameter("thetaK2",0.0);

	// Dynamic Parameters of Pendulum
		// The mass is supposed to be concentrated at the end of each pendulum
    	symbol_numeric  m1 = *sys.new_Parameter("m1",1.0);
    	symbol_numeric  m2 = *sys.new_Parameter("m2",1.0);

	ex I1=(l1*l1)*m1;
	ex I2=(l2*l2)*m2;

	//Gravity Center Vectors    

	Vector3D OPendulum1_GPendulum1= *sys.new_Vector3D("OPendulum1_GPendulum1",0,0,-l1,"BPendulum1");

	Vector3D OPendulum2_GPendulum2= *sys.new_Vector3D("OPendulum2_GPendulum2",0,0,-l2,"BPendulum2");

	//Inertia Tensors
    	Tensor3D IPendulum1_OP1 = *sys.new_Tensor3D("IPendulum1_OP1",(ex)0,(ex)0,(ex)0,(ex)0,(ex)I1,(ex)0,(ex)0,(ex)0,(ex)0,"BPendulum1");
	Tensor3D IPendulum2_OP2 = *sys.new_Tensor3D("IPendulum2_OP2",(ex)0,(ex)0,(ex)0,(ex)0,(ex)I2,(ex)0,(ex)0,(ex)0,(ex)0,"BPendulum2");
 
// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Pendulum1=sys.new_Frame("Fra_Pendulum1","OPendulum1","BPendulum1");
	Frame * Fra_Pendulum2=sys.new_Frame("Fra_Pendulum2","OPendulum2","BPendulum2");

// ************************************************************************************************
//	Define Solids
// ************************************************************************************************


	Solid * Pendulum1 = sys.new_Solid("Pendulum1","OPendulum1" ,"BPendulum1" ,"m1","OPendulum1_GPendulum1","IPendulum1_OP1");
	Solid * Pendulum2 = sys.new_Solid("Pendulum2","OPendulum2" ,"BPendulum2" ,"m2","OPendulum2_GPendulum2","IPendulum2_OP2");


// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

        Drawing3D * Pendulum1_3D = sys.new_Drawing3D("Pendulum1_3D","Pendulum1","./solids/pendulum.stl",0,1,0,0.8);	
        Drawing3D * Pendulum2_3D = sys.new_Drawing3D("Pendulum2_3D","Pendulum2","./solids/pendulum.stl",0,1,0,0.8);	

        Drawing3D * FraPENDULUM1 = sys.new_Drawing3D("FraPENDULUM1",Fra_Pendulum1,0.1);
        Drawing3D * FraPENDULUM2 = sys.new_Drawing3D("FraPENDULUM2",Fra_Pendulum2,0.1);
        Drawing3D * FraABS = sys.new_Drawing3D("FraABS",Frame_abs,0.5);


// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

	cout << "Joint Unknown Definition" << endl;



// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

	cout << "Input Vector" << endl;

	symbol_numeric MPendulum1y = *sys.new_Input("MPendulum1y",0.0);

	Vector3D FPendulum1 = *sys.new_Vector3D("FPendulum1",0,0,0,"BPendulum1");
	Vector3D MPendulum1 = *sys.new_Vector3D("MPendulum1",0,MPendulum1y,0, "BPendulum1");


// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************

	Vector3D FK_GroundPend1 = *sys.new_Vector3D("FK_GroundPend1",0,0,0, "xyz");
	Vector3D MK_GroundPend1 = *sys.new_Vector3D("MK_GroundPend1",0,K1*(theta1-thetaK1),0, "xyz");

	Vector3D FK_GroundPend2 = *sys.new_Vector3D("FK_GroundPend2",0,0,0, "BPendulum1");
	Vector3D MK_GroundPend2 = *sys.new_Vector3D("MK_GroundPend2",0,K2*(theta2-thetaK2),0, "BPendulum1");

	Vector3D FV_GroundPend1 = *sys.new_Vector3D("FV_GroundPend1",0,0,0,"xyz");
	Vector3D MV_GroundPend1= -Cvis1 * sys.Angular_Velocity("xyz" , "BPendulum1" );

	Vector3D FV_Pend1Pend2 = *sys.new_Vector3D("FV_Pend1Pend2",0,0,0,"BPendulum1");
	Vector3D MV_Pend1Pend2= -Cvis2 * sys.Angular_Velocity("BPendulum1" , "BPendulum2" );


// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * Gravity_Pendulum1 = sys.Gravity_Wrench("Pendulum1");
	Wrench3D * Gravity_Pendulum2 = sys.Gravity_Wrench("Pendulum2");

	//	Inertia
	Wrench3D * Inertia_Pendulum1 = sys.Inertia_Wrench("Pendulum1");
	Wrench3D * Inertia_Pendulum2 = sys.Inertia_Wrench("Pendulum2");

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
	//Matrix Dynamic_Equations = sys.GenForceSys("ALL");


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

    //sys.Matrix_Calculation(coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD);
    sys.Matrix_Calculation(coord_indep_init , vel_indep_init , sys, METHOD);
    
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

    	state = theta1, theta2, *dtheta1, *dtheta2, *ddtheta1, *ddtheta2;

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


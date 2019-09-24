/*
//cp ../common_code/* .
touch atom_def.c
export LD_LIBRARY_PATH=`pwd`/../../../lib/
export PKG_CONFIG_PATH=`pwd`/../../../lib/pkgconfig
g++ -o main_symbolic main_symbolic.cc `pkg-config --cflags --libs lib_3d_mec_ginac-1.1 ginac cln gsl`

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
cout << "*            Dzhanibekov effect                *" << endl;
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

	symbol_numeric psi = *sys.new_Coordinate("psi","dpsi","ddpsi", 0.0 , 0.0 , 0.0);
	symbol_numeric theta = *sys.new_Coordinate("theta","dtheta","ddtheta", 0.0 , 0.0 , 0.0);
	symbol_numeric phi = *sys.new_Coordinate("phi","dphi","ddphi", 0.0 , 0.0 , 0.0);


	symbol_numeric dpsi_0 = *sys.new_Parameter("dpsi_0",0.0001);
	symbol_numeric dtheta_0 = *sys.new_Parameter("dtheta_0",3.0);
	symbol_numeric dphi_0 = *sys.new_Parameter("dphi_0",0.0);

	symbol_numeric *dpsi=sys.get_Velocity("dpsi");
	symbol_numeric *dtheta=sys.get_Velocity("dtheta");
	symbol_numeric *dphi=sys.get_Velocity("dphi");


	symbol_numeric *ddpsi=sys.get_Acceleration("ddpsi");
	symbol_numeric *ddtheta=sys.get_Acceleration("ddtheta");
	symbol_numeric *ddphi=sys.get_Acceleration("ddphi");

	lst coord_indep_init;
	lst vel_indep_init;

	coord_indep_init =psi, theta, phi;
	vel_indep_init	= (*dpsi-dpsi_0),(*dtheta-dtheta_0),(*dphi-dphi_0);


// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	
// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

 	sys.new_Base("Base1","xyz",1,0,0,psi);
 	sys.new_Base("Base2","Base1",0,0,1,phi);
 	sys.new_Base("Base3","Base2",0,1,0,theta);

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************


// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	

// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************
    	
	symbol_numeric  a = *sys.new_Parameter("a",1.0);
    	symbol_numeric  b = *sys.new_Parameter("b",2.0);
    	symbol_numeric  c = *sys.new_Parameter("c",3.0);

	//Gravity Center Vectors    

	Vector3D O_G= *sys.new_Vector3D("O_G",0,0,0,"Base3");

	// Dynamic Parameters of Pendulum

    	symbol_numeric  mass = *sys.new_Parameter("mass",1.0);

        #ifdef Ellipsoid
    	ex  Ixx = (1.0/5.0)*(b*b+c*c)*mass;
    	ex  Iyy = (1.0/5.0)*(a*a+c*c)*mass;
    	ex  Izz = (1.0/5.0)*(a*a+b*b)*mass;
	Tensor3D I = *sys.new_Tensor3D("I",(ex)Ixx,0,0,0,(ex)Iyy,0,0,0,(ex)Izz,"Base3");
        #endif

        #ifdef Tobject 
    	symbol_numeric Ixx  = *sys.new_Parameter("Ixx",2.0);
    	symbol_numeric Iyy  = *sys.new_Parameter("Iyy",4.0);
    	symbol_numeric Izz  = *sys.new_Parameter("Izz",6.0);

	Tensor3D I = *sys.new_Tensor3D("I",Ixx,0,0,0,Iyy,0,0,0,Izz,"Base3");
        #endif








// ************************************************************************************************
//	Define Frames
// ************************************************************************************************


	Frame * Fra=sys.new_Frame("Fra","O","Base3");



// ************************************************************************************************
//	Define Solids
// ************************************************************************************************


	Solid * Sol= sys.new_Solid("Sol","O","Base3","mass","O_G","I");


// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

        #ifdef Ellipsoid
        Drawing3D * Block3D = sys.new_Drawing3D("Block3D",Sol,"./solids/ellipsoid.stl",0,1,0,1.0);	
        #endif
        #ifdef Tobject 
        Drawing3D * Block3D = sys.new_Drawing3D("Block3D",Sol,"./solids/Tobject.stl",0,1,0,1.0);	
        #endif


        Drawing3D * Fra3D = sys.new_Drawing3D("Fra3D","Fra",0.5);		
        Drawing3D * FraABS = sys.new_Drawing3D("FraABS",Frame_abs,0.8);


// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

	cout << "Joint Unknown Definition" << endl;



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



	//	Inertia
	Wrench3D * Inertia_Solid = sys.Inertia_Wrench("Sol");


	//	Constitutive



	//	External

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

	//# define PROBLEM_TYPE "Q"
	//# define PROBLEM_TYPE "Z"
	//# define PROBLEM_TYPE "I3AL_Q"
	//# define PROBLEM_TYPE "I3AL_Z"
	//# define PROBLEM_TYPE "ALL"

    sys.Matrix_Calculation(coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD);

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

    	state = psi,theta,phi, *dpsi, *dtheta,*dphi,*ddpsi, *ddtheta, *ddphi;

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


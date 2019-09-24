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
cout << "*             Block - Pendulum                 *" << endl;
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

	symbol_numeric x = *sys.new_Coordinate("x","dx","ddx", 0.0 , 0.0 , 0.0);
	symbol_numeric theta = *sys.new_Coordinate("theta","dtheta","ddtheta", 3.141592/2.0, 0.0 , 0.0);

      
	symbol_numeric *dx=sys.get_Velocity("dx");
	symbol_numeric *dtheta=sys.get_Velocity("dtheta");

	symbol_numeric *ddx=sys.get_Acceleration("ddx");
	symbol_numeric *ddtheta=sys.get_Acceleration("ddtheta");

	lst coord_indep_init;//coord_indep_init = x-1.0;
	lst vel_indep_init;

// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	symbol_numeric d = *sys.new_Parameter("d",0.5);
	symbol_numeric h = *sys.new_Parameter("h",0.5);

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

 	sys.new_Base("BBlock","xyz",0,0,0,0); 	sys.new_Base("BPendulum","BBlock",0,1,0,-theta);


// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	Vector3D O_OBlock = *sys.new_Vector3D("O_OBlock",x,0,h,"xyz");
	Vector3D OBlock_A = *sys.new_Vector3D("OBlock_A",0,0,-h,"BBlock");

	Vector3D OBlock_E = *sys.new_Vector3D("OBlock_E",0,-d,0,"BBlock");
	Vector3D E_OPendulum=*sys.new_Vector3D("E_OPendulum",0,0,0,"BPendulum");

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * OBlock = sys.new_Point("OBlock","O",&O_OBlock);
	Point * A = sys.new_Point("A","OBlock",&OBlock_A);
	Point * E = sys.new_Point("E","OBlock",&OBlock_E);
	Point * OPendulum= sys.new_Point("OPendulum","E",&E_OPendulum);


// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Viscosity
    symbol_numeric  Cvis = *sys.new_Parameter("Cvis",0.8);

	// Torsion spring
    symbol_numeric  K = *sys.new_Parameter("K",1.0);

	// Dynamic Parameters of Block
    symbol_numeric  mBlock = *sys.new_Parameter("mBlock",1.0);

    symbol_numeric  mxBlock = *sys.new_Parameter("mxBlock",0.0);
    symbol_numeric  myBlock = *sys.new_Parameter("myBlock",0.0);
    symbol_numeric  mzBlock = *sys.new_Parameter("mzBlock",0.0);

    symbol_numeric  IxxBlock = *sys.new_Parameter("IxxBlock",1.0);
    symbol_numeric  IxyBlock = *sys.new_Parameter("IxyBlock",0.0);
    symbol_numeric  IyyBlock = *sys.new_Parameter("IyyBlock",1.0);
    symbol_numeric  IxzBlock = *sys.new_Parameter("IxzBlock",0.0);
    symbol_numeric  IzzBlock = *sys.new_Parameter("IzzBlock",1.0);
    symbol_numeric  IyzBlock = *sys.new_Parameter("IyzBlock",0.0);

	// Dynamic Parameters of Pendulum

    symbol_numeric  mPendulum = *sys.new_Parameter("mPendulum",1.0);
    symbol_numeric  lPendulum = *sys.new_Parameter("lPendulum",1.0);
    
    symbol_numeric  mxPendulum = *sys.new_Parameter("mxPendulum",0.0);
    symbol_numeric  myPendulum = *sys.new_Parameter("myPendulum",0.0);
    symbol_numeric  mzPendulum = *sys.new_Parameter("mzPendulum",-1.0);

    symbol_numeric  IxxPendulum = *sys.new_Parameter("IxxPendulum",0.0);
    symbol_numeric  IxyPendulum = *sys.new_Parameter("IxyPendulum",0.0);
    symbol_numeric  IyyPendulum = *sys.new_Parameter("IyyPendulum",5.0);
    symbol_numeric  IxzPendulum = *sys.new_Parameter("IxzPendulum",0.0);
    symbol_numeric  IzzPendulum = *sys.new_Parameter("IzzPendulum",0.0);
    symbol_numeric  IyzPendulum = *sys.new_Parameter("IyzPendulum",0.0);


	//Gravity Center Vectors    

	Vector3D OBlock_GBlock= *sys.new_Vector3D("OBlock_GBlock",mxBlock/mBlock,myBlock/mBlock,mzBlock/mBlock,"BBlock");
	Vector3D OPendulum_GPendulum= *sys.new_Vector3D("OPendulum_GPendulum",0,0,-lPendulum,"BPendulum");


	//Inertia Tensors
    Tensor3D IBlock = *sys.new_Tensor3D("IBlock",(ex)IxxBlock,(ex)0,(ex)0,(ex)0,(ex)IyyBlock,(ex)0,(ex)0,(ex)0,(ex)IzzBlock,"BBlock");
    Tensor3D IPendulum_OP = *sys.new_Tensor3D("IPendulum_OP",(ex)IxxPendulum,(ex)0,(ex)0,(ex)0,(ex)IyyPendulum,(ex)0,(ex)0,(ex)0,(ex)IzzPendulum,"BPendulum");


// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Block = sys.new_Frame("Fra_Block","OBlock","BBlock");
	Frame * Fra_Pendulum=sys.new_Frame("Fra_Pendulum","OPendulum","BPendulum");



// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

    Solid * Block = sys.new_Solid("Block","OBlock","BBlock","mBlock","OBlock_GBlock","IBlock");
    Solid * Pendulum = sys.new_Solid("Pendulum","OPendulum" ,"BPendulum" ,"mPendulum","OPendulum_GPendulum","IPendulum_OP");



// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

    Drawing3D * Block3D = sys.new_Drawing3D("Block3D", Block,"./solids/block.stl",1,0,0,0.6);		
    Drawing3D * Pendulum3D = sys.new_Drawing3D("Pendulum3D","Pendulum","./solids/pendulum.stl",0,1,0,0.6);	
	

    Drawing3D * FraBLOCK = sys.new_Drawing3D("FraBLOCK","Fra_Block",0.5);		
    Drawing3D * FraPENDULUM = sys.new_Drawing3D("FraPENDULUM",Fra_Pendulum,0.5);
    Drawing3D * FraABS = sys.new_Drawing3D("FraABS",Frame_abs,0.05);

// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

	cout << "Joint Unknown Definition" << endl;



// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

	cout << "Input Vector" << endl;

	symbol_numeric FBlockx = *sys.new_Input("FBlockx",0.0);
	symbol_numeric MPendulumy = *sys.new_Input("MPendulumy",0.0);

	Vector3D FBlock = *sys.new_Vector3D("FBlock",FBlockx,0,0,"BBlock");
	Vector3D MBlock = *sys.new_Vector3D("MBlock",0,0,0, "BBlock");
	Vector3D FPendulum = *sys.new_Vector3D("FPendulum",0,0,0,"BPendulum");
	Vector3D MPendulum = *sys.new_Vector3D("MPendulum",0,MPendulumy,0, "BPendulum");


// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************
    symbol_numeric theta_0 = *sys.new_Parameter("theta_0",2.0);

	Vector3D FK_BlockPend = *sys.new_Vector3D("FK_BlockPend",0,0,0, "BBlock");
	Vector3D MK_BlockPend = *sys.new_Vector3D("MK_BlockPend",0,K*(theta-theta_0),0, "BBlock");

	Vector3D FV_BlockGuide = -Cvis * sys.Velocity_Vector("abs" ,"A", "Block" );
	Vector3D MV_BlockGuide= *sys.new_Vector3D("MV_BlockGuide",0,0,0,"xyz");

// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * Gravity_Block = sys.Gravity_Wrench("Block");
	Wrench3D * Gravity_Pendulum = sys.Gravity_Wrench("Pendulum");


	//	Inertia
	Wrench3D * Inertia_Block = sys.Inertia_Wrench("Block");
	Wrench3D * Inertia_Pendulum = sys.Inertia_Wrench("Pendulum");


	//	Constitutive
	Wrench3D * Viscosity = sys.new_Wrench3D ( "Viscosity", FV_BlockGuide, MV_BlockGuide, A , Block , "Constitutive") ;
	Wrench3D * Torsional_Block = sys.new_Wrench3D ( "Torsional_Block", - FK_BlockPend , - MK_BlockPend , E , Block , "Constitutive") ;
	Wrench3D * Torsional_Pendulum = sys.new_Wrench3D ( "Torsional_Pendulum ", FK_BlockPend , MK_BlockPend , E , Pendulum , "Constitutive") ;

	//	External
	Wrench3D * Block_Impulse = sys.new_Wrench3D ( "Block_Impulse", FBlock, MBlock, OBlock , Block , "External") ;
	Wrench3D * Pendulum_Impulse = sys.new_Wrench3D ( "Pendulum_Impulse", FPendulum, MPendulum, E , Pendulum , "External") ;

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

	//~ Matrix Dynamic_Equations = sys.GenForceSys("ALL");
         
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
    //~ sys.Matrix_Calculation(coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD);
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

    	state = x , theta, *dx, *dtheta, *ddx, *ddtheta;

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


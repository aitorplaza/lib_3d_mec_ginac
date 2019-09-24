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
cout << "*             Four-bar linkage                  *" << endl;
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



    //#define ABS
    #define REL
    
    //abs
    #ifdef ABS 
	symbol_numeric theta1 = *sys.new_Coordinate("theta1","dtheta1","ddtheta1", -3.141592/2.0 ,0.0 , 0.0);
	symbol_numeric theta2 = *sys.new_Coordinate("theta2","dtheta2","ddtheta2", 0.0 , 0.0 , 0.0);
  	symbol_numeric theta3 = *sys.new_Coordinate("theta3","dtheta3","ddtheta3", +3.141592/2.0 , 0.0 , 0.0);  
    //rel
    #elif defined REL
	symbol_numeric theta1 = *sys.new_Coordinate("theta1","dtheta1","ddtheta1", -3.141592/2.0 ,0.0 , 0.0);
	symbol_numeric theta2 = *sys.new_Coordinate("theta2","dtheta2","ddtheta2", +3.141592/2.0, 0.0 , 0.0);
  	symbol_numeric theta3 = *sys.new_Coordinate("theta3","dtheta3","ddtheta3", +3.141592/2.0 , 0.0 , 0.0); 
    #endif 
     
	symbol_numeric *dtheta1=sys.get_Velocity("dtheta1");
	symbol_numeric *dtheta2=sys.get_Velocity("dtheta2");
 	symbol_numeric *dtheta3=sys.get_Velocity("dtheta3");   

	symbol_numeric *ddtheta1=sys.get_Acceleration("ddtheta1");
	symbol_numeric *ddtheta2=sys.get_Acceleration("ddtheta2");
  	symbol_numeric *ddtheta3=sys.get_Acceleration("ddtheta3");
  

	lst coord_indep_init;
	lst vel_indep_init;

	coord_indep_init.append(theta1+INITIAL_THETA1 );
	//vel_indep_init.append(*dtheta1-INITIAL_DTHETA1);
        //vel_indep_init.append(*dtheta2-INITIAL_DTHETA2);




// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	// Pendulum length
	symbol_numeric l1 = *sys.new_Parameter("l1",0.4);
	symbol_numeric l2 = *sys.new_Parameter("l2",2.0);
 	symbol_numeric l3 = *sys.new_Parameter("l3",1.2);   
 	symbol_numeric l4 = *sys.new_Parameter("l4",1.6); 

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

  	sys.new_Base("Barm1","xyz",0,1,0,theta1);
    #ifdef REL 
  	sys.new_Base("Barm2","Barm1",0,1,0,theta2);//rel
  	sys.new_Base("Barm3","Barm2",0,1,0,theta3);//rel
    #elif defined ABS
   	sys.new_Base("Barm2","xyz",0,1,0,theta2);//abs
  	sys.new_Base("Barm3","xyz",0,1,0,theta3); //abs  
    #endif

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************
	Vector3D O_A=*sys.new_Vector3D("O_A",l1,0,0,"Barm1");
    Vector3D A_B=*sys.new_Vector3D("A_B",l2,0,0,"Barm2");
    Vector3D B_C=*sys.new_Vector3D("B_C",l3,0,0,"Barm3");   
	Vector3D O_O2=*sys.new_Vector3D("O_O2",l4,0,0,"xyz");



// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * OA= sys.new_Point("OA","O",&O_A);
    Point * OB= sys.new_Point("OB","OA",&A_B);
    Point * OC= sys.new_Point("OC","OB",&B_C);
    Point * O2= sys.new_Point("O2","O",&O_O2);            
        

// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************






	// Dynamic Parameters of Pendulum
    symbol_numeric  m1 = *sys.new_Parameter("m1",1.0);
    symbol_numeric  m2 = *sys.new_Parameter("m2",1.0);
    symbol_numeric  m3 = *sys.new_Parameter("m3",1.0);   
     
    
    
 	//Gravity Center Vectors       
    symbol_numeric  cg1x = *sys.new_Parameter("cg1x",0.2);  
    symbol_numeric  cg1z = *sys.new_Parameter("cg1z",0.1); 
    symbol_numeric  cg2x = *sys.new_Parameter("cg2x",1.0);  
    symbol_numeric  cg2z = *sys.new_Parameter("cg2z",0.1);   
    symbol_numeric  cg3x = *sys.new_Parameter("cg3x",0.6);  
    symbol_numeric  cg3z = *sys.new_Parameter("cg3z",0.1); 
      
	Vector3D Oarm1_Garm1= *sys.new_Vector3D("Oarm1_Garm1",cg1x,0,cg1z,"Barm1");
	Vector3D Oarm2_Garm2= *sys.new_Vector3D("Oarm2_Garm2",cg2x,0,cg2z,"Barm2");
	Vector3D Oarm3_Garm3= *sys.new_Vector3D("Oarm3_Garm3",cg3x,0,cg3z,"Barm3");
    
	//Inertia Tensors
    symbol_numeric  I1yy = *sys.new_Parameter("I1yy",1.0);  
    symbol_numeric  I2yy = *sys.new_Parameter("I2yy",1.0);
    symbol_numeric  I3yy = *sys.new_Parameter("I3yy",1.0);     
    
    //~ Tensor3D Iarm1 = *sys.new_Tensor3D("Iarm1",(ex)m1*(cg1z*cg1z),(ex)0,(ex)(-cg1x*cg1z),(ex)0,(ex)I1yy + m1*(cg1x*cg1x+cg1z*cg1z ),(ex)0,(ex)(-cg1x*cg1z),(ex)0,(ex)m1*(cg1x*cg1x),"Barm1") ;
    //~ Tensor3D Iarm2 = *sys.new_Tensor3D("Iarm2",(ex)m2*(cg2z*cg2z),(ex)0,(ex)(-cg2x*cg2z),(ex)0,(ex)I2yy + m2*(cg2x*cg2x+cg2z*cg2z ),(ex)0,(ex)(-cg2x*cg2z),(ex)0,(ex)m2*(cg2x*cg2x),"Barm2") ;
    //~ Tensor3D Iarm3 = *sys.new_Tensor3D("Iarm3",(ex)m3*(cg3z*cg3z),(ex)0,(ex)(-cg3x*cg3z),(ex)0,(ex)I3yy + m3*(cg3x*cg3x+cg3z*cg3z ),(ex)0,(ex)(-cg3x*cg3z),(ex)0,(ex)m3*(cg3x*cg3x),"Barm3") ;

    Tensor3D Iarm1 = *sys.new_Tensor3D("Iarm1",(ex)0,(ex)0,(ex)0,(ex)0,(ex)I1yy,(ex)0,(ex)0,(ex)0,(ex)0,"Barm1") ;
    Tensor3D Iarm2 = *sys.new_Tensor3D("Iarm2",(ex)0,(ex)0,(ex)0,(ex)0,(ex)I2yy,(ex)0,(ex)0,(ex)0,(ex)0,"Barm2") ;
    Tensor3D Iarm3 = *sys.new_Tensor3D("Iarm3",(ex)0,(ex)0,(ex)0,(ex)0,(ex)I3yy,(ex)0,(ex)0,(ex)0,(ex)0,"Barm3") ;

  


    //Drawing3D * VOarm1_Garm1= sys.new_Drawing3D("VOarm1_Garm1",&Oarm1_Garm1,Point_O,1,1,0,1.0);
    //Drawing3D * VOarm2_Garm2= sys.new_Drawing3D("VOarm2_Garm2",&Oarm2_Garm2,OA,1,1,0,1.0);
    //Drawing3D * VOarm3_Garm3= sys.new_Drawing3D("VOarm3_Garm3",&Oarm3_Garm3,OB,1,1,0,1.0);
 
// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_arm1=sys.new_Frame("Fra_arm1","O","Barm1");
	Frame * Fra_arm2=sys.new_Frame("Fra_arm2","OA","Barm2");
	Frame * Fra_arm3=sys.new_Frame("Fra_arm3","OB","Barm3");
 	Frame * Fra_ABS2=sys.new_Frame("Fra_ABS2","O2","xyz");   
    
// ************************************************************************************************
//	Define Solids
// ************************************************************************************************


	Solid * arm1 = sys.new_Solid("arm1","O"  ,"Barm1" ,"m1","Oarm1_Garm1","Iarm1");
	Solid * arm2 = sys.new_Solid("arm2","OA" ,"Barm2" ,"m2","Oarm2_Garm2","Iarm2");
	Solid * arm3 = sys.new_Solid("arm3","OB" ,"Barm3" ,"m3","Oarm3_Garm3","Iarm3");
    
// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

    Drawing3D * DFra_arm1 = sys.new_Drawing3D("DFra_arm1",Fra_arm1,0.2);
    Drawing3D * DFra_arm2 = sys.new_Drawing3D("DFra_arm2",Fra_arm2,0.2);
    Drawing3D * DFra_arm3 = sys.new_Drawing3D("DFra_arm3",Fra_arm3,0.2);               
    Drawing3D * FraABS = sys.new_Drawing3D("FraABS",Frame_abs,0.2);
    Drawing3D * FraABS2 = sys.new_Drawing3D("FraABS2",Fra_ABS2,0.2);

    Drawing3D * Varm1 = sys.new_Drawing3D("Varm1",&O_A,Point_O);
    Drawing3D * Varm2 = sys.new_Drawing3D("Varm2",&A_B,OA);
    Drawing3D * Varm3 = sys.new_Drawing3D("Varm3",&B_C,OB);       
    Drawing3D * Varm4 = sys.new_Drawing3D("Varm4",&O_O2,Point_O);

        

// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

	cout << "Joint Unknown Definition" << endl;
    symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");
    symbol_numeric lambda2  = *sys.new_Joint_Unknown("lambda2");


// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************

	cout << "Input Vector" << endl;

	symbol_numeric Fx2 = *sys.new_Input("Fx2",0.0);
	symbol_numeric Fz2 = *sys.new_Input("Fz2",0.0);    
	symbol_numeric Fx3 = *sys.new_Input("Fx3",0.0);    
	symbol_numeric Fz3 = *sys.new_Input("Fz3",0.0);
 	symbol_numeric My2 = *sys.new_Input("My2",0.0);    
	symbol_numeric My3 = *sys.new_Input("My3",0.0);   
        

	Vector3D Fext2 = *sys.new_Vector3D("Fext2",Fx2,0,Fz2,"xyz");
	Vector3D Fext3 = *sys.new_Vector3D("Fext3",Fx3,0,Fz3,"xyz");    
	Vector3D Mext2 = *sys.new_Vector3D("Mext2",0,My2,0,"xyz");
 	Vector3D Mext3 = *sys.new_Vector3D("Mext3",0,My3,0,"xyz");
    
         
// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************
	// Spring
   	symbol_numeric  K = *sys.new_Parameter("K",50.0);
    
    
    symbol_numeric  l2x = *sys.new_Parameter("l2x",1.0);  
    symbol_numeric  l2z = *sys.new_Parameter("l2z",0.1); 
    symbol_numeric  l3x = *sys.new_Parameter("l3x",0.5);  
    symbol_numeric  l3z = *sys.new_Parameter("l3z",0.1);    
      
	Vector3D Oarm2_L2= *sys.new_Vector3D("Oarm2_L2",l2x,0,0,"Barm2");
	Vector3D Oarm3_L3= *sys.new_Vector3D("Oarm3_L3",l3x,0,l3z,"Barm3");
    Point * OL2= sys.new_Point("OL2","OA",&Oarm2_L2);
    Point * OL3= sys.new_Point("OL3","OB",&Oarm3_L3);  
    
    Vector3D OL2_OL3 = sys.Position_Vector("OL2","OL3");
    Vector3D FK = K*OL2_OL3;
    Vector3D MK = *sys.new_Vector3D("MK_GroundPend1",0,0,0, "xyz");


    Drawing3D * VOL2_OL3= sys.new_Drawing3D("VOL2_OL3",&OL2_OL3,OL2,1,1,0,1.0);

// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * Gravity_Arm1 = sys.Gravity_Wrench("arm1");
	Wrench3D * Gravity_Arm2 = sys.Gravity_Wrench("arm2");    
	Wrench3D * Gravity_Arm3 = sys.Gravity_Wrench("arm3");
	//	Inertia
	Wrench3D * Inertia_Arm1 = sys.Inertia_Wrench("arm1");
	Wrench3D * Inertia_Arm2 = sys.Inertia_Wrench("arm2");    
 	Wrench3D * Inertia_Arm3 = sys.Inertia_Wrench("arm3");   

	//	Constitutive
	Wrench3D * SpringA = sys.new_Wrench3D ( "SpringA", FK , MK , OL2 , arm2, "Constitutive") ;
	Wrench3D * SpringR = sys.new_Wrench3D ( "SpringR", -FK , -MK , OL3 , arm3, "Constitutive") ;
    
	//	External
	Wrench3D * FMext2 = sys.new_Wrench3D ( "FMext2", Fext2, Mext2, OA , arm2 , "External") ;
	Wrench3D * FMext3 = sys.new_Wrench3D ( "FMext3", Fext3, Mext3, OB , arm3 , "External") ;
    

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
	//Vector3D eq = O_A + A_B + B_C - O_O2;
    //Vector3D eq = (O_A + (A_B + B_C)) - O_O2;
    Vector3D eq = sys.Position_Vector ( O2 , OC ) ;
    
	Matrix Phi(2,1);
	Phi(0,0) = eq(0,0);
	Phi(1,0) = eq(2,0);

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

    //~ sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD);
    sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , sys, METHOD);

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

    	state = {theta1, theta2, theta3};

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


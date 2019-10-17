/*
 
//cp -r ../common_MAIN/ .

export PKG_CONFIG_PATH=`pwd`/../../../lib/pkgconfig
export LD_LIBRARY_PATH=`pwd`/../../../lib
g++ -std=c++11 -o main_symbolic main_symbolic.cc `pkg-config --cflags --libs lib_3d_mec_ginac ginac`

main_symbolic DOWN YES

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
	#define METHOD LAGRANGE
#endif

#ifdef V_P
	#define METHOD VIRTUAL_POWER
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
    #define ABS
    //#define REL

	symbol_numeric theta1 = *sys.new_Coordinate("theta1", -3.141592/6.0, 0.0 );
	symbol_numeric theta2 = *sys.new_Coordinate("theta2", -2*3.141592/6.0, 0.0 );
  	symbol_numeric theta3 = *sys.new_Coordinate("theta3", -3*3.141592/6.0, 0.0 );  
     
	symbol_numeric *dtheta1=sys.get_Velocity("dtheta1");
	symbol_numeric *dtheta2=sys.get_Velocity("dtheta2");
 	symbol_numeric *dtheta3=sys.get_Velocity("dtheta3");

	symbol_numeric *ddtheta1=sys.get_Acceleration("ddtheta1");
	symbol_numeric *ddtheta2=sys.get_Acceleration("ddtheta2");
  	symbol_numeric *ddtheta3=sys.get_Acceleration("ddtheta3");

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

#ifdef REL
  	sys.new_Base("BArm1","xyz",0,1,0,theta1);
   	sys.new_Base("BArm2","BArm1",0,1,0,theta2);
  	sys.new_Base("BArm3","BArm2",0,1,0,theta3);
#else
  	sys.new_Base("BArm1","xyz",0,1,0,theta1);
   	sys.new_Base("BArm2","xyz",0,1,0,theta2);
  	sys.new_Base("BArm3","xyz",0,1,0,theta3);
#endif

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************
	Vector3D OA=*sys.new_Vector3D("OA",l1,0,0,"BArm1");
    Vector3D AB=*sys.new_Vector3D("AB",l2,0,0,"BArm2");
    Vector3D BC=*sys.new_Vector3D("BC",l3,0,0,"BArm3");   
	Vector3D OO2=*sys.new_Vector3D("OO2",l4,0,0,"xyz");

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * A= sys.new_Point("A","O",&OA);
    Point * B= sys.new_Point("B","A",&AB);
    Point * C= sys.new_Point("C","B",&BC);
    Point * O2= sys.new_Point("O2","O",&OO2);            
        

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
      
	Vector3D OArm1_GArm1= *sys.new_Vector3D("OArm1_GArm1",cg1x,0,cg1z,"BArm1");
	Vector3D OArm2_GArm2= *sys.new_Vector3D("OArm2_GArm2",cg2x,0,cg2z,"BArm2");
	Vector3D OArm3_GArm3= *sys.new_Vector3D("OArm3_GArm3",cg3x,0,cg3z,"BArm3");
    
	//Inertia Tensors
    symbol_numeric  I1yy = *sys.new_Parameter("I1yy",1.0);  
    symbol_numeric  I2yy = *sys.new_Parameter("I2yy",1.0);
    symbol_numeric  I3yy = *sys.new_Parameter("I3yy",1.0);     
    
    //~ Tensor3D I_Arm1 = *sys.new_Tensor3D("I_Arm1",(ex)m1*(cg1z*cg1z),(ex)0,(ex)(-cg1x*cg1z),(ex)0,(ex)I1yy + m1*(cg1x*cg1x+cg1z*cg1z ),(ex)0,(ex)(-cg1x*cg1z),(ex)0,(ex)m1*(cg1x*cg1x),"BArm1") ;
    //~ Tensor3D I_Arm2 = *sys.new_Tensor3D("I_Arm2",(ex)m2*(cg2z*cg2z),(ex)0,(ex)(-cg2x*cg2z),(ex)0,(ex)I2yy + m2*(cg2x*cg2x+cg2z*cg2z ),(ex)0,(ex)(-cg2x*cg2z),(ex)0,(ex)m2*(cg2x*cg2x),"BArm2") ;
    //~ Tensor3D I_Arm3 = *sys.new_Tensor3D("I_Arm3",(ex)m3*(cg3z*cg3z),(ex)0,(ex)(-cg3x*cg3z),(ex)0,(ex)I3yy + m3*(cg3x*cg3x+cg3z*cg3z ),(ex)0,(ex)(-cg3x*cg3z),(ex)0,(ex)m3*(cg3x*cg3x),"BArm3") ;

    Tensor3D I_Arm1 = *sys.new_Tensor3D("I_Arm1",(ex)0,(ex)0,(ex)0,(ex)0,(ex)I1yy,(ex)0,(ex)0,(ex)0,(ex)0,"BArm1") ;
    Tensor3D I_Arm2 = *sys.new_Tensor3D("I_Arm2",(ex)0,(ex)0,(ex)0,(ex)0,(ex)I2yy,(ex)0,(ex)0,(ex)0,(ex)0,"BArm2") ;
    Tensor3D I_Arm3 = *sys.new_Tensor3D("I_Arm3",(ex)0,(ex)0,(ex)0,(ex)0,(ex)I3yy,(ex)0,(ex)0,(ex)0,(ex)0,"BArm3") ;

    //Drawing3D * VOArm1_GArm1= sys.new_Drawing3D("VOArm1_GArm1",&OArm1_GArm1,Point_O,1,1,0,1.0);
    //Drawing3D * VOArm2_GArm2= sys.new_Drawing3D("VOArm2_GArm2",&OArm2_GArm2,A,1,1,0,1.0);
    //Drawing3D * VOArm3_GArm3= sys.new_Drawing3D("VOArm3_GArm3",&OArm3_GArm3,B,1,1,0,1.0);
 
// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * FArm1=sys.new_Frame("FArm1","O","BArm1");
	Frame * FArm2=sys.new_Frame("FArm2","A","BArm2");
	Frame * FArm3=sys.new_Frame("FArm3","B","BArm3");
 	Frame * Fra_ABS2=sys.new_Frame("Fra_ABS2","O2","xyz");   
    
// ************************************************************************************************
//	Define Solids
// ************************************************************************************************


	Solid * Arm1 = sys.new_Solid("Arm1","O"  ,"BArm1" ,"m1","OArm1_GArm1","I_Arm1");
	Solid * Arm2 = sys.new_Solid("Arm2","A" ,"BArm2" ,"m2","OArm2_GArm2","I_Arm2");
	Solid * Arm3 = sys.new_Solid("Arm3","B" ,"BArm3" ,"m3","OArm3_GArm3","I_Arm3");
    
// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

    Drawing3D * DFArm1 = sys.new_Drawing3D("DFArm1",FArm1,0.2);
    Drawing3D * DFArm2 = sys.new_Drawing3D("DFArm2",FArm2,0.2);
    Drawing3D * DFArm3 = sys.new_Drawing3D("DFArm3",FArm3,0.2);               
    Drawing3D * FraABS = sys.new_Drawing3D("FraABS",Frame_abs,0.2);
    Drawing3D * FraABS2 = sys.new_Drawing3D("FraABS2",Fra_ABS2,0.2);

    Drawing3D * VArm1 = sys.new_Drawing3D("VArm1",&OA,Point_O);
    Drawing3D * VArm2 = sys.new_Drawing3D("VArm2",&AB,A);
    Drawing3D * VArm3 = sys.new_Drawing3D("VArm3",&BC,B);       
    Drawing3D * VArm4 = sys.new_Drawing3D("VArm4",&OO2,Point_O);

        

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
    //symbol_numeric  l2z = *sys.new_Parameter("l2z",0.1); 
    symbol_numeric  l3x = *sys.new_Parameter("l3x",0.5);  
    symbol_numeric  l3z = *sys.new_Parameter("l3z",0.1);    
      
	Vector3D OArm2_L2= *sys.new_Vector3D("OArm2_L2",l2x,0,0,"BArm2");
	Vector3D OArm3_L3= *sys.new_Vector3D("OArm3_L3",l3x,0,l3z,"BArm3");
    Point * OL2= sys.new_Point("OL2","A",&OArm2_L2);
    Point * OL3= sys.new_Point("OL3","B",&OArm3_L3);  
    
    Vector3D OL2_OL3 = sys.Position_Vector("OL2","OL3");
    Vector3D FK = K*OL2_OL3;
    Vector3D MK = *sys.new_Vector3D("MK_GroundPend1",0,0,0, "xyz");

    Drawing3D * VOL2_OL3= sys.new_Drawing3D("VOL2_OL3",&OL2_OL3,OL2,1,1,0,1.0);

// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * Gravity_Arm1 = sys.Gravity_Wrench("Arm1");
	Wrench3D * Gravity_Arm2 = sys.Gravity_Wrench("Arm2");    
	Wrench3D * Gravity_Arm3 = sys.Gravity_Wrench("Arm3");
	//	Inertia
	Wrench3D * Inertia_Arm1 = sys.Inertia_Wrench("Arm1");
	Wrench3D * Inertia_Arm2 = sys.Inertia_Wrench("Arm2");    
 	Wrench3D * Inertia_Arm3 = sys.Inertia_Wrench("Arm3");

	//	Constitutive
	Wrench3D * SpringA = sys.new_Wrench3D ( "SpringA", FK , MK , OL2 , Arm2, "Constitutive") ;
	Wrench3D * SpringR = sys.new_Wrench3D ( "SpringR", -FK , -MK , OL3 , Arm3, "Constitutive") ;
    
	//	External
	Wrench3D * FMext2 = sys.new_Wrench3D ( "FMext2", Fext2, Mext2, A , Arm2 , "External") ;
	Wrench3D * FMext3 = sys.new_Wrench3D ( "FMext3", Fext3, Mext3, B , Arm3 , "External") ;
       
    // Arm1
    Wrench3D Sum_Wrenches_Arm1 = *Inertia_Arm1 + *Gravity_Arm1;
    Wrench3D Sum_Wrenches_Arm2 = *Inertia_Arm2 + *Gravity_Arm2 + *SpringA + *FMext2;
    Wrench3D Sum_Wrenches_Arm3 = *Inertia_Arm3 + *Gravity_Arm3 - *SpringA + *FMext3;
    
    cout << unatomize(Sum_Wrenches_Arm1) << endl;
    cout << unatomize(Sum_Wrenches_Arm2) << endl;
    cout << unatomize(Sum_Wrenches_Arm3) << endl;
    
    Wrench3D  Twist_Arm1 = sys.Twist("Arm1");
	Wrench3D  Twist_Arm2 = sys.Twist("Arm2");    
 	Wrench3D  Twist_Arm3 = sys.Twist("Arm3");

    cout << unatomize(Twist_Arm1) << endl;
    cout << unatomize(Twist_Arm2) << endl;
    cout << unatomize(Twist_Arm3) << endl;
    
    cout << unatomize(Sum_Wrenches_Arm1*Twist_Arm1) << endl << endl;
    cout << unatomize(Sum_Wrenches_Arm2*Twist_Arm2) << endl << endl;
    cout << unatomize(Sum_Wrenches_Arm3*Twist_Arm3) << endl << endl;

// ************************************************************************************************
// 	Vectors needed to take diferent Jacobians
// ************************************************************************************************

	cout << "Vectors needed to take diferent Jacobians" << endl;

	Matrix q = sys.Coordinates();
	Matrix q_aux = sys.Aux_Coordinates();
	Matrix dq = sys.Velocities();
	Matrix dq_aux = sys.Aux_Velocities();
	Matrix ddq = sys.Accelerations();
	Matrix ddq_aux = sys.Aux_Accelerations();
	Matrix epsilon = sys.Joint_Unknowns();
	Matrix param = sys.Parameters();
	Matrix input = sys.Inputs();

// ************************************************************************************************
// 	 Kinematic Equations Phi Phi_init dPhi_init
// ************************************************************************************************
	cout << "%Kinematic Equations" << endl;	
	
    Vector3D O2C = sys.Position_Vector ( O2 , C );
    Vector3D e_x = *sys.new_Vector3D("e_x",1,0,0,"xyz");
    Vector3D e_z = *sys.new_Vector3D("e_z",0,0,1,"xyz");

	Matrix Phi(2,1);
	Phi(0,0) = O2C * e_x;
	Phi(1,0) = O2C * e_z;
	cout << "Phi2 =" << unatomize(Phi) << endl;
	
	cout<<" %dPhi Calculating"<<endl;
    Matrix dPhi_aux = sys.Dt(Phi);
    Matrix dPhiNH(0,1);
    Matrix dPhi = Matrix (2,1,&dPhi_aux,&dPhiNH);
    cout<<  "dPhi2=" << unatomize(dPhi) <<endl;
    
    cout<<" %ddPhi Calculating"<<endl;
    Matrix ddPhi  = sys.Dt(dPhi);
    cout<<  "ddPhi2=" << unatomize(ddPhi) <<endl;
    
    cout<<" %beta Calculating"<<endl;
    Matrix beta  = -dPhi;
    beta = subs(beta,dq , 0);
    beta = subs(beta,dq_aux , 0);
    cout<<  "beta2=" << unatomize(beta) <<endl;
    
    cout<<" %Phi_q Calculating"<<endl;
    Matrix Phi_q  = sys.jacobian(Phi.transpose() ,Matrix (2,1,&q,&q_aux));
    cout<<  "Phi_q2=" << unatomize(Phi_q) <<endl;

    cout<<" %dPhi_dq Calculating"<<endl;
    Matrix dPhi_dq =  sys.jacobian(dPhi.transpose() ,Matrix (2,1,&dq,&dq_aux));//if dqaux == 0 then  Matrix (2,1,&dq,&dqaux)) = dq
    cout<<  "dPhi_dq2=" << unatomize(dPhi_dq) <<endl;
    
    cout<<" %gamma Calculating"<<endl;
    Matrix gamma  = -ddPhi;
    gamma = subs (gamma,ddq , 0);
    gamma = subs (gamma,ddq_aux , 0);
    cout << "gamma2 =" << unatomize(gamma) <<endl;
	
	#define INITIAL_THETA1 3.1416/2.0
    #define INITIAL_DTHETA1 0.0
	
    Matrix Phi_init(1,1);
    Phi_init(0,0)=theta1+INITIAL_THETA1;
 
    Matrix dPhi_init(1,1);
    dPhi_init(0,0)=*dtheta1+INITIAL_DTHETA1;

// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************

	cout << "%Dynamic Equations Virtual Power or Lagrange" << endl;

	Matrix Dyn_eq_VP(3,1);
	 
	Dyn_eq_VP(0,0) = Sum_Wrenches_Arm1*sys.diff(Twist_Arm1,dq(0,0))+Sum_Wrenches_Arm2*sys.diff(Twist_Arm2,dq(0,0))+Sum_Wrenches_Arm3*sys.diff(Twist_Arm3,dq(0,0));
	Dyn_eq_VP(1,0) = Sum_Wrenches_Arm1*sys.diff(Twist_Arm1,dq(1,0))+Sum_Wrenches_Arm2*sys.diff(Twist_Arm2,dq(1,0))+Sum_Wrenches_Arm3*sys.diff(Twist_Arm3,dq(1,0));
	Dyn_eq_VP(2,0) = Sum_Wrenches_Arm1*sys.diff(Twist_Arm1,dq(2,0))+Sum_Wrenches_Arm2*sys.diff(Twist_Arm2,dq(2,0))+Sum_Wrenches_Arm3*sys.diff(Twist_Arm3,dq(2,0));
	
	Dyn_eq_VP=-Dyn_eq_VP;
	
	cout << "Dyn_eq_VP =" << unatomize(Dyn_eq_VP) << endl;
	

// ************************************************************************************************
// 	Output Vector
// ************************************************************************************************

	cout << "%Output Vector" << endl;

	Matrix Output(0,1);
	//Output(0,0)=0;
	sys.new_Matrix("Output",Output);

    cout << "Output =" << unatomize(Output) << endl;

// ************************************************************************************************
// 	Energy Equations
// ************************************************************************************************

	cout << "%Energy Equations" << endl;

	Matrix Energy(0,1);
	//Energy(0,0)=0;
	sys.new_Matrix("Energy",Energy);

    cout << "Energy =" << unatomize(Output) << endl;
    
    Matrix Dyn_eq_VP_open = Dyn_eq_VP;

	//method == VIRTUAL_POWER
    Dyn_eq_VP_open = subs (Dyn_eq_VP_open, epsilon , 0);        
    
    cout << "Dyn_eq_VP_open2=" << unatomize(Dyn_eq_VP_open) << endl;
    
    Matrix Dyn_eq_L=Dyn_eq_VP;
    
    //method == LAGRANGE
	//Dyn_eq_VP_open = Dyn_eq_VP;

    cout<<" %M_qq and delta_q Calculating by differentation"<<endl;
    Matrix M_qq = sys.jacobian(Dyn_eq_VP_open.transpose() ,ddq,1); //M is symmetric
    //Matrix M_qq = sys.jacobian(Dyn_eq_VP_open.transpose() ,ddq);

    Matrix delta_q = - Dyn_eq_VP_open;
    delta_q = subs (delta_q, ddq , 0);
    delta_q = subs (delta_q, ddq_aux , 0);
       
    cout<<  "M_qq2=" << unatomize(M_qq) <<endl;
    cout<<  "delta_q2=" <<unatomize(delta_q) <<endl;
    
    cout<<" %Phi_init Calculating"<<endl;
    Phi_init = Matrix (2,1,&Phi,&Phi_init);
    cout<<  "Phi_init2=" << unatomize(Phi_init) <<endl;
    
    cout<<" %dPhi_init Calculating"<<endl;
    dPhi_init       = Matrix (2,1,&dPhi,&dPhi_init);
    cout<< "dPhi_init2=" << unatomize(dPhi_init) <<endl;

    cout<<" %Phi_init_q Calculating"<<endl;
    //Matrix Phi_init_q       = jacobian(PhiInit.transpose(), q);
    Matrix Phi_init_q       = sys.jacobian(Phi_init.transpose(), Matrix (2,1,&q,&q_aux));//if qaux == 0 then  Matrix (2,1,&q,&qaux)) = q
    cout<< "Phi_init_q2=" << unatomize(Phi_init_q) <<endl;

    cout<<" %dPhi_init_dq Calculating"<<endl;
    //Matrix dPhi_init_dq     = jacobian(dPhiInit.transpose() ,dq);
    Matrix dPhi_init_dq     = sys.jacobian(dPhi_init.transpose() ,Matrix (2,1,&dq,&dq_aux));//if dqaux == 0 then  Matrix (2,1,&dq,&dqaux)) = dq
    cout<<  "dPhi_init_dq2=" << unatomize(dPhi_init_dq) <<endl;

    cout<<" %beta_init Calculating"<<endl;
    Matrix beta_init  = -dPhi_init;
    
    beta_init = subs (beta_init,dq , 0);
    beta_init = subs (beta_init,ddq_aux , 0);
    cout<<  "beta_init2=" << unatomize(beta_init) <<endl;

//%% Dynamic Equilibrium Equations
//%----Begin Edit----
//Extra_Dyn_Eq_eq=[dtheta1;
    //ddtheta1];
//%----End Edit----

//%% Virtual Power or Lagrange
    //%%  Equilibrium problem "a la" Virtual Power or Lagrange
    //Dyn_Eq_eq_VP=[Dyn_eq_L;
        //ddPhi;
        //dPhi;
        //Phi;
        //Extra_Dyn_Eq_eq];


    ex ex_dtheta1=*dtheta1;
    ex ex_ddtheta1=*ddtheta1;
    Matrix Extra_Dyn_Eq_eq= Matrix(2,1,&ex_dtheta1,&ddtheta1);
    Matrix Dyn_Eq_eq_VP=Matrix(5,1,&Dyn_eq_L,&ddPhi,&dPhi,&Phi,&Extra_Dyn_Eq_eq);
    cout<<  "Dyn_Eq_eq_VP2=" << unatomize(Dyn_Eq_eq_VP) <<endl;
    
    
    sys.export_function_MATLAB("Phi_", "Phi_out", Phi,"q,t,param");
    sys.export_function_MATLAB("Phi_q_", "Phi_q_out", Phi_q, "q,t,param");
    sys.export_function_MATLAB("dPhi_dq_", "dPhi_dq_out", dPhi_dq, "time,param");
    sys.export_function_MATLAB("beta_", "beta_out", beta, "q,t,param");
    sys.export_function_MATLAB("gamma_", "gamma_out", gamma,  "q,dq,t,param");
    sys.export_function_MATLAB("Phi_init_" ,"Phi_init_out" ,Phi_init, "q,t,param");
    sys.export_function_MATLAB("Phi_init_q_","Phi_init_q_out",Phi_init_q, "q,t,param");
    sys.export_function_MATLAB("dPhi_init_dq_" ,"dPhi_init_dq_out" ,dPhi_init_dq, "q,t,param");
    sys.export_function_MATLAB("beta_init_" ,"beta_init_out" ,beta_init, "q,t,param");
    sys.export_function_MATLAB("M_qq_", "M_qq_out", M_qq, "q,t,param");
    sys.export_function_MATLAB("delta_q_", "delta_q_out", delta_q, "q,dq,t,param");
    //sys.export_function_MATLAB("Mdelta", "Mdelta_", Mdelta,  "time,param,inputs");
    //sys.export_function_MATLAB("output", "output_", output, "unknowns,time,param,inputs");
    //sys.export_function_MATLAB("energy", "energy_", energy, "time,param");

    //sys.export_Dynamic_Simulation(sys, ORDER , MAPLE);

//// ************************************************************************************************
//// 	Export Point, Base and Frame Diagrams 
//// ************************************************************************************************
//#ifdef GRAPHVIZ
	//cout << "Export Point, Base and Frame Diagrams" << endl;

	//sys.export_Graphviz_dot (  );

	////Generate eps figure
    	//system("dot -Tps   base_diagram.dot -o plain_base_diagram.eps");
    	//system("latex base_diagram.tex");
    	//system("dvips base_diagram.dvi -o base_diagram.eps");
	////Generate figure eps
    	//system("dot -Tps   point_diagram.dot -o plain_point_diagram.eps");
     	//system("latex point_diagram.tex");
    	//system("dvips point_diagram.dvi -o point_diagram.eps");
	////Generate eps figure
    	//system("dot -Tps   frame_diagram.dot -o plain_frame_diagram.eps");
    	//system("latex frame_diagram.tex");
    	//system("dvips base_diagram.dvi -o base_diagram.eps");
//#endif


//// ************************************************************************************************
////	Export MATLAB environment vector 
//// ************************************************************************************************

	//cout << "Export ENVIRONMENT file " << endl;

	//sys.export_environment_m (  );


//// ************************************************************************************************
////	Export config.ini file
//// ************************************************************************************************

	//cout << "Export config.ini file " << endl;

	//sys.export_config_ini (  );

//// ************************************************************************************************
////	Export C++ code for Openscenegraph
//// ************************************************************************************************

	//cout << "Export C++ code for Openscenegraph." << endl;
	//sys.export_open_scene_graph ( );

//// ************************************************************************************************
////	Export State File
//// ************************************************************************************************

	//cout << "Export State File" << endl;

    	//lst state;

    	//state = {theta1, theta2, theta3};

        //sys.export_write_data_file_C(state);
        //sys.export_read_data_file_C(state);


//// ************************************************************************************************
////	Export grphics.gnuplot
//// ************************************************************************************************

	//cout << "Export GNUPLOT file" << endl;
    //sys.export_gnuplot ( state );
       
   

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


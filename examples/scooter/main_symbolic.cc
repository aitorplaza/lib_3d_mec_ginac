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
	symbol_numeric y = *sys.new_Coordinate("y","dy","ddy", 0.0 , 0.0 , 0.0);
    symbol_numeric alpha = *sys.new_Coordinate("alpha","dalpha","ddalpha", 0.0 , 0.0 , 0.0);
    symbol_numeric phi = *sys.new_Coordinate("phi","dphi","ddphi", 0.0 , 0.0 , 0.0);
	symbol_numeric theta = *sys.new_Coordinate("theta","dtheta","ddtheta", 0.0 , 0.0 , 0.0);
	symbol_numeric epsilon = *sys.new_Coordinate("epsilon","depsilon","ddepsilon", 0.0 , 0.0 , 0.0);
	symbol_numeric phih = *sys.new_Coordinate("phih","dphih","ddphih", 0.0 , 0.0 , 0.0);
	symbol_numeric psi_B = *sys.new_Coordinate("psi_B","dpsi_B","ddpsi_B", 0.0 , 0.0 , 0.0);
	symbol_numeric psi_FL = *sys.new_Coordinate("psi_FL","dpsi_FL","ddpsi_FL", 0.0 , 0.0 , 0.0);
	symbol_numeric psi_FR = *sys.new_Coordinate("psi_FR","dpsi_FR","ddpsi_FR", 0.0 , 0.0 , 0.0);
	symbol_numeric psi_JL = *sys.new_Coordinate("psi_JL","dpsi_JL","ddpsi_JL", 0.0 , 0.0 , 0.0);
	symbol_numeric psi_JR = *sys.new_Coordinate("psi_JR","dpsi_JR","ddpsi_JR", 0.0 , 0.0 , 0.0);

	symbol_numeric rho_L = *sys.new_Coordinate("rho_L","drho_L","ddrho_L", 0.0 , 0.0 , 0.0);
	symbol_numeric rho_R = *sys.new_Coordinate("rho_R ","drho_R","ddrho_R", 0.0 , 0.0 , 0.0);



	// Velocities
	symbol_numeric *dx         = sys.get_Velocity("dx");
	symbol_numeric *dy         = sys.get_Velocity("dy");
 	symbol_numeric *dalpha     = sys.get_Velocity("dalpha");
	symbol_numeric *dphi       = sys.get_Velocity("dphi");   
 	symbol_numeric *dtheta     = sys.get_Velocity("dtheta");
	symbol_numeric *depsilon   = sys.get_Velocity("depsilon");
 	symbol_numeric *dphih      = sys.get_Velocity("dphih");
	symbol_numeric *dpsi_B     = sys.get_Velocity("dpsi_B");      
 	symbol_numeric *dpsi_FL    = sys.get_Velocity("dpsi_FL");
	symbol_numeric *dpsi_FR    = sys.get_Velocity("dpsi_FR");
 	symbol_numeric *dpsi_JL    = sys.get_Velocity("dpsi_JL");
	symbol_numeric *dpsi_JR    = sys.get_Velocity("dpsi_JR");      
 	symbol_numeric *drho_L     = sys.get_Velocity("drho_L");
	symbol_numeric *drho_R     = sys.get_Velocity("drho_R");
   
    

	// Accelerations
    symbol_numeric *ddx         = sys.get_Acceleration("ddx");
	symbol_numeric *ddy         = sys.get_Acceleration("ddy");
 	symbol_numeric *ddalpha     = sys.get_Acceleration("ddalpha");
	symbol_numeric *ddphi       = sys.get_Acceleration("ddphi");   
 	symbol_numeric *ddtheta     = sys.get_Acceleration("ddtheta");
	symbol_numeric *ddepsilon   = sys.get_Acceleration("ddepsilon");
 	symbol_numeric *ddphih      = sys.get_Acceleration("ddphih");
	symbol_numeric *ddpsi_B     = sys.get_Acceleration("ddpsi_B");      
 	symbol_numeric *ddpsi_FL    = sys.get_Acceleration("ddpsi_FL");
	symbol_numeric *ddpsi_FR    = sys.get_Acceleration("ddpsi_FR");
 	symbol_numeric *ddpsi_JL    = sys.get_Acceleration("ddpsi_JL");
	symbol_numeric *ddpsi_JR    = sys.get_Acceleration("ddpsi_JR");      
 	symbol_numeric *ddrho_L     = sys.get_Acceleration("ddrho_L");
	symbol_numeric *ddrho_R     = sys.get_Acceleration("ddrho_R");

	lst coord_indep_init;
	lst vel_indep_init;

// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

 	symbol_numeric R       = *sys.new_Parameter("R",0.5);
 	symbol_numeric lBC     = *sys.new_Parameter("lBC",3.0);
 	symbol_numeric lCD     = *sys.new_Parameter("lCD",3.0);
 	symbol_numeric larm    = *sys.new_Parameter("larm",0.5);
 	symbol_numeric lBG_Cha = *sys.new_Parameter("lBG_Cha",1.5);


// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

 	sys.new_Base("B123",    "xyz",0,0,1,phi);
 	sys.new_Base("B123p",   "B123",0,1,0,alpha);
 	sys.new_Base("B123pp",  "B123p",1,0,0,theta);
 	sys.new_Base("B123ppp",   "B123pp",0,0,1,phih);
 	sys.new_Base("B123pppp",   "B123ppp",0,1,0,epsilon);

 	sys.new_Base("B_Wheel_FL",   "B123ppp",1,0,0,psi_FL);
 	sys.new_Base("B_Wheel_FR",   "B123ppp",1,0,0,psi_FR);
    
 	sys.new_Base("B_Wheel_B",   "B123p",1,0,0,psi_B);
        
 	sys.new_Base("B_JL",   "B123ppp",1,0,0,psi_JL);
 	sys.new_Base("B_JR",   "B123ppp",1,0,0,psi_JR);



// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************



	Vector3D O_JWheelB = *sys.new_Vector3D("O_JWheelB",x,y,0,"xyz");
	Vector3D JWheelB_OWheelB = *sys.new_Vector3D("JWheelB_OWheelB",0,0,R,"B123p");
 	Vector3D OWheelB_C = *sys.new_Vector3D("OWheelB_C",0,lBC,0,"B123pp");   
  	Vector3D C_D = *sys.new_Vector3D("C_D",0,0,-lCD,"B123pp"); 
    
      
   	Vector3D D_DL = *sys.new_Vector3D("D_DL",-larm,0,0,"B123pppp");   
   	Vector3D D_DR = *sys.new_Vector3D("D_DR",+larm,0,0,"B123pppp"); 
    
    Vector3D DL_OWheelFL = *sys.new_Vector3D("DL_OWheelFL",0,0,-rho_L,"B123pp"); 
    Vector3D DR_OWheelFR = *sys.new_Vector3D("DR_OWheelFR",0,0,-rho_R,"B123pp"); 
     
    Vector3D OWheelFL_JL = *sys.new_Vector3D("OWheelFL_JL",0,0,-R,"B_JL"); 
    Vector3D OWheelFR_JR = *sys.new_Vector3D("OWheelFR_JR",0,0,-R,"B_JR"); 
    
    
    Vector3D JL_JWheelFL = *sys.new_Vector3D("JL_JWheelFL",0,R,0,"B_Wheel_FL");   //???????????????????????
    Vector3D JR_JWheelFR = *sys.new_Vector3D("JR_JWheelFR",0,R,0,"B_Wheel_FR");    //???????????????????????     
    
    
    
    Vector3D xB123=*sys.new_Vector3D("xB123",1,0,0,"B123");
    Vector3D yB123=*sys.new_Vector3D("yB123",0,1,0,"B123");
    Vector3D zB123=*sys.new_Vector3D("zB123",0,0,1,"B123");
      
// ************************************************************************************************
//	Define Points
// ************************************************************************************************

    Point * J_Wheel_B = sys.new_Point("J_Wheel_B","O",&O_JWheelB);
    Point * O_Wheel_B = sys.new_Point("O_Wheel_B","J_Wheel_B",&JWheelB_OWheelB);
    
    Point * C = sys.new_Point("C","O_Wheel_B",&OWheelB_C);
    Point * D = sys.new_Point("D","C",&C_D);

    Point * D_L = sys.new_Point("D_L","D",&D_DL);
    Point * D_R = sys.new_Point("D_R","D",&D_DR);

    Point * O_Wheel_FL = sys.new_Point("O_Wheel_FL","D_L",&DL_OWheelFL);
    Point * O_Wheel_FR = sys.new_Point("O_Wheel_FR","D_R",&DR_OWheelFR);

    Point * JL = sys.new_Point("JL","O_Wheel_FL",&OWheelFL_JL);
    Point * JR = sys.new_Point("JR","O_Wheel_FR",&OWheelFR_JR);   
    
    Point * J_Wheel_FL = sys.new_Point("J_Wheel_FL","O_Wheel_FL",&JL_JWheelFL);
    Point * J_Wheel_FR = sys.new_Point("J_Wheel_FR","O_Wheel_FR",&JR_JWheelFR); 




// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************
    symbol_numeric  mCha = *sys.new_Parameter("mCha",1.0);
    symbol_numeric  mWheel_B = *sys.new_Parameter("mWheel_B",1.0);
    symbol_numeric  mWheel_FR = *sys.new_Parameter("mWheel_FR",1.0); 
    symbol_numeric  mWheel_FL = *sys.new_Parameter("mWheel_FL",1.0);
    symbol_numeric  mHand = *sys.new_Parameter("mHand",0.0); 
    symbol_numeric  mArm = *sys.new_Parameter("mArm",1.0);    
    
    

    Vector3D OmCha_GmCha = *sys.new_Vector3D("OmCha_GmCha",0,lBG_Cha,0,"B123pp");
    symbol_numeric  I1Cha = *sys.new_Parameter("I1Cha",1.0); 
    symbol_numeric  I2Cha = *sys.new_Parameter("I2Cha",1.0); 
    symbol_numeric  I3Cha = *sys.new_Parameter("I3Cha",1.0); 
    Tensor3D ICha = *sys.new_Tensor3D("ICha",(ex)I1Cha,(ex)0,(ex)0,(ex)0,(ex)I2Cha,(ex)0,(ex)0,(ex)0,(ex)I3Cha,"B123pp") ;
    	

    Vector3D OmWheel_B_GmWheel_B = *sys.new_Vector3D("OmWheel_B_GmWheel_B",0,0,0,"B_Wheel_B");
    symbol_numeric  I1Wheel_B = *sys.new_Parameter("I1Wheel_B",1.0); 
    symbol_numeric  I2Wheel_B = *sys.new_Parameter("I2Wheel_B",0.5); 
    symbol_numeric  I3Wheel_B = *sys.new_Parameter("I3Wheel_B",0.5); 
    Tensor3D IWheel_B = *sys.new_Tensor3D("IWheel_B",(ex)I1Wheel_B,(ex)0,(ex)0,(ex)0,(ex)I2Wheel_B,(ex)0,(ex)0,(ex)0,(ex)I3Wheel_B,"B_Wheel_B") ;

    Vector3D OmWheel_FR_GmWheel_FR = *sys.new_Vector3D("OmWheel_FR_GmWheel_FR",0,0,0,"B_Wheel_FR");
    symbol_numeric  I1Wheel_FR = *sys.new_Parameter("I1Wheel_FR",1.0); 
    symbol_numeric  I2Wheel_FR = *sys.new_Parameter("I2Wheel_FR",0.5); 
    symbol_numeric  I3Wheel_FR = *sys.new_Parameter("I3Wheel_FR",0.5); 
    Tensor3D IWheel_FR = *sys.new_Tensor3D("IWheel_FR",(ex)I1Wheel_FR,(ex)0,(ex)0,(ex)0,(ex)I2Wheel_FR,(ex)0,(ex)0,(ex)0,(ex)I3Wheel_FR,"B_Wheel_FR") ;

    Vector3D OmWheel_FL_GmWheel_FL = *sys.new_Vector3D("OmWheel_FL_GmWheel_FL",0,0,0,"B_Wheel_FL");
    symbol_numeric  I1Wheel_FL = *sys.new_Parameter("I1Wheel_FL",1.0); 
    symbol_numeric  I2Wheel_FL = *sys.new_Parameter("I2Wheel_FL",0.5); 
    symbol_numeric  I3Wheel_FL = *sys.new_Parameter("I3Wheel_FL",0.5); 
    Tensor3D IWheel_FL = *sys.new_Tensor3D("IWheel_FL",(ex)I1Wheel_FL,(ex)0,(ex)0,(ex)0,(ex)I2Wheel_FL,(ex)0,(ex)0,(ex)0,(ex)I3Wheel_FL,"B_Wheel_FL") ;

    Vector3D OmHand_GmHand = *sys.new_Vector3D("OmHand_GmHand",0,0,0,"B123ppp");
    symbol_numeric  I1Hand = *sys.new_Parameter("I1Hand",0.0); 
    symbol_numeric  I2Hand = *sys.new_Parameter("I2Hand",0.0); 
    symbol_numeric  I3Hand = *sys.new_Parameter("I3Hand",0.0); 
    Tensor3D IHand = *sys.new_Tensor3D("IHand",(ex)I1Hand,(ex)0,(ex)0,(ex)0,(ex)I2Hand,(ex)0,(ex)0,(ex)0,(ex)I3Hand,"B123ppp") ;
    
    
    Vector3D OmArm_GmArm = *sys.new_Vector3D("OmArm_GmArm",0,0,0,"B123pppp");
    symbol_numeric  I1Arm = *sys.new_Parameter("I1Arm",1.0); 
    symbol_numeric  I2Arm = *sys.new_Parameter("I2Arm",1.0); 
    symbol_numeric  I3Arm = *sys.new_Parameter("I3Arm",1.0); 
    Tensor3D IArm = *sys.new_Tensor3D("IArm",(ex)I1Arm,(ex)0,(ex)0,(ex)0,(ex)I2Arm,(ex)0,(ex)0,(ex)0,(ex)I3Arm,"B123pppp") ;
// ************************************************************************************************
//	Define Frames
// ************************************************************************************************



// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	Solid * Cha = sys.new_Solid("Cha","O_Wheel_B","B123pp","mCha","OmCha_GmCha","ICha");
	Solid * Wheel_B = sys.new_Solid("Wheel_B","O_Wheel_B","B_Wheel_B","mWheel_B","OmWheel_B_GmWheel_B","IWheel_B");    
	Solid * Wheel_FR = sys.new_Solid("Wheel_FR","O_Wheel_FR","B_Wheel_FR","mWheel_FR","OmWheel_FR_GmWheel_FR","IWheel_FR"); 
 	Solid * Wheel_FL = sys.new_Solid("Wheel_FL","O_Wheel_FL","B_Wheel_FL","mWheel_FL","OmWheel_FL_GmWheel_FL","IWheel_FL"); 
	Solid * Hand = sys.new_Solid("Hand","O_Wheel_B","B123ppp","mHand","OmHand_GmHand","IHand");
    Solid * Arm = sys.new_Solid("Arm","O_Wheel_B","B123pppp","mArm","OmArm_GmArm","IArm");           

// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

    //Drawing3D * Chassi3D = sys.new_Drawing3D("Chassi3D", "OChassi", "BChassi" ,"./solids/T_shape.stl",1,0,0,0.6);


// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

//	cout << "Joint Unknown Definition" << endl;


    symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");
    symbol_numeric lambda2  = *sys.new_Joint_Unknown("lambda2");
    symbol_numeric lambda3  = *sys.new_Joint_Unknown("lambda3");
    symbol_numeric lambda4  = *sys.new_Joint_Unknown("lambda4");   
    symbol_numeric lambda5  = *sys.new_Joint_Unknown("lambda5");
    symbol_numeric lambda6  = *sys.new_Joint_Unknown("lambda6");   
    symbol_numeric lambda7  = *sys.new_Joint_Unknown("lambda7");
    symbol_numeric lambda8  = *sys.new_Joint_Unknown("lambda8");   
    symbol_numeric lambda9  = *sys.new_Joint_Unknown("lambda9");
    symbol_numeric lambda10 = *sys.new_Joint_Unknown("lambda10");   
    //~ symbol_numeric lambda11 = *sys.new_Joint_Unknown("lambda11");
    //~ symbol_numeric lambda12 = *sys.new_Joint_Unknown("lambda12");    
    
    
    
    
    
/*
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

/*/
// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************

    Vector3D VZeros = *sys.new_Vector3D("VZeros",0,0,0, "B123");

    symbol_numeric k_rho       = *sys.new_Parameter("k_rho",1.0);
    symbol_numeric c_rho       = *sys.new_Parameter("c_rho",1.0);  
    symbol_numeric c_phih       = *sys.new_Parameter("c_phih",1.0);
    symbol_numeric k_epsilon       = *sys.new_Parameter("k_epsilon",1.0); 
    symbol_numeric c_epsilon       = *sys.new_Parameter("c_epsilon",1.0);
    symbol_numeric rho0       = *sys.new_Parameter("rho0",1.0); 
    
    //{MD_Hand_Cha}B123pp:=c_phih*dphih*{[0,0,1]}B123pp
    Vector3D  MD_Hand_Cha =  c_phih * (* dphih) *zB123;
    
    // {FS_leg_arm_L}B123ppp:=-k_rho*(rho_L-rho0)*{[0,0,1]}B123ppp
    // {FD_leg_arm_L}B123ppp:=-c_rho*drho_L*{[0,0,1]}B123ppp
    Vector3D   FS_leg_arm_L =  -k_rho*(rho_L-rho0) *zB123;
    Vector3D   FD_leg_arm_L =  -c_rho*(*drho_L)* zB123;    

    // {FS_leg_arm_R}B123ppp:=-k_rho*(rho_R-rho0)*{[0,0,1]}B123ppp
    // {FD_leg_arm_R}B123ppp:=-c_rho*drho_R*{[0,0,1]}B123ppp
    Vector3D   FS_leg_arm_R =  -k_rho*(rho_R-rho0) *zB123;
    Vector3D   FD_leg_arm_R =  -c_rho*(*drho_R)* zB123; 

    //  {MS_arm_Hand}B123ppp:=k_epsilon*(epsilon)*{[0,1,0]}B123ppp
    // {MD_arm_Hand}B123ppp:=c_epsilon*(depsilon)*{[0,1,0]}B123ppp	
    Vector3D    MS_arm_Hand = k_epsilon*(epsilon)* zB123;
    Vector3D    MD_arm_Hand = c_epsilon*(*depsilon)* zB123;    
    
    
// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * Gravity_Chassi = sys.Gravity_Wrench("Cha");
	Wrench3D * Gravity_Wheel1 = sys.Gravity_Wrench("Wheel_B");
	Wrench3D * Gravity_Wheel2 = sys.Gravity_Wrench("Wheel_FL");
	Wrench3D * Gravity_Wheel3 = sys.Gravity_Wrench("Wheel_FR");


	//	Inertia
	Wrench3D * Inertia_Chassi = sys.Inertia_Wrench("Cha");
	Wrench3D * Inertia_Wheel1 = sys.Inertia_Wrench("Wheel_B");
	Wrench3D * Inertia_Wheel2 = sys.Inertia_Wrench("Wheel_FL");
	Wrench3D * Inertia_Wheel3 = sys.Inertia_Wrench("Wheel_FR");

	//	Constitutive
	Wrench3D * AFS_leg_arm_L = sys.new_Wrench3D ( "AFS_leg_arm_L", FS_leg_arm_L, VZeros, O_Wheel_FL , Wheel_FL , "Constitutive") ;
    Wrench3D * ADS_leg_arm_L = sys.new_Wrench3D ( "ADS_leg_arm_L", FD_leg_arm_L, VZeros, O_Wheel_FL , Wheel_FL , "Constitutive") ;
	Wrench3D * RFS_leg_arm_L = sys.new_Wrench3D ( "RFS_leg_arm_L", -FS_leg_arm_L, VZeros, D_L , Cha , "Constitutive") ;
    Wrench3D * RDS_leg_arm_L = sys.new_Wrench3D ( "RDS_leg_arm_L", -FD_leg_arm_L, VZeros, D_L , Cha , "Constitutive") ;


	Wrench3D * AFS_leg_arm_R = sys.new_Wrench3D ( "AFS_leg_arm_R", FS_leg_arm_R, VZeros, O_Wheel_FR , Wheel_FR , "Constitutive") ;
    Wrench3D * ADS_leg_arm_R = sys.new_Wrench3D ( "ADS_leg_arm_R", FD_leg_arm_R, VZeros, O_Wheel_FR , Wheel_FR , "Constitutive") ;
	Wrench3D * RFS_leg_arm_R = sys.new_Wrench3D ( "RFS_leg_arm_R", -FS_leg_arm_R, VZeros, D_R , Cha , "Constitutive") ;
    Wrench3D * RDS_leg_arm_R = sys.new_Wrench3D ( "RDS_leg_arm_R", -FD_leg_arm_R, VZeros, D_R , Cha , "Constitutive") ;

	Wrench3D * AMD_Hand_Cha  = sys.new_Wrench3D ( "AMD_Hand_Cha", VZeros, MD_Hand_Cha, C , Hand , "Constitutive") ;
    Wrench3D * RMD_Hand_Cha  = sys.new_Wrench3D ( "RMD_Hand_Cha", VZeros, -MD_Hand_Cha, C , Cha , "Constitutive") ;


	Wrench3D * AMS_arm_Hand  = sys.new_Wrench3D ( "AMS_arm_Hand", VZeros, MS_arm_Hand, D , Arm , "Constitutive") ;
	Wrench3D * RMS_arm_Hand  = sys.new_Wrench3D ( "RMS_arm_Hand", VZeros, -MS_arm_Hand, D , Hand , "Constitutive") ;    
 	Wrench3D * AMD_arm_Hand  = sys.new_Wrench3D ( "AMD_arm_Hand", VZeros, MD_arm_Hand, D , Arm , "Constitutive") ;
	Wrench3D * RMD_arm_Hand  = sys.new_Wrench3D ( "RMD_arm_Hand", VZeros, -MD_arm_Hand, D , Hand , "Constitutive") ;    
    
	//	External




// ************************************************************************************************
// 	Vectors needed to take diferent Jacobians
// ************************************************************************************************

	cout << "Vectors needed to take diferent Jacobians" << endl;

	Matrix q = sys.Coordinates();
	Matrix dq = sys.Velocities();
	Matrix ddq = sys.Accelerations();
//	Matrix epsilon = sys.Joint_Unknowns();
	Matrix pars = sys.Parameters();
//	Matrix inps = sys.Inputs();
//	Matrix unks = sys.Joint_Unknowns();

// ************************************************************************************************
// 	 Kinematic Equations 
// ************************************************************************************************
	cout << "Kinematic Equations" << endl;

    Vector3D JL_tangent=*sys.new_Vector3D("JL_tangent",0,1,0,"B_JL");
    Vector3D JR_tangent=*sys.new_Vector3D("JR_tangent",0,1,0,"B_JR");
    


    
    ex eq1 = sys.Position_Vector ( J_Wheel_B ,JL ) * zB123 ;
    ex eq2 = JL_tangent * zB123 ;    
    ex eq3 = sys.Position_Vector ( J_Wheel_B ,JR ) * zB123 ;
    ex eq4 = JR_tangent * zB123 ;  
    
    
       
	Matrix Phi(4,1);
	Phi(0,0)  = eq1;
	Phi(1,0)  = eq2;  
 	Phi(2,0)  = eq3;  
	Phi(3,0)  = eq4;
   
    
    Vector3D VJ_Wheel_FL =  sys.Velocity_Vector ( "abs" , "JL", "Wheel_FL" ) ;
    Vector3D VJ_Wheel_FR =  sys.Velocity_Vector ( "abs" , "JR", "Wheel_FR" ) ;
    Vector3D VJ_Wheel_B =  sys.Velocity_Vector ( "abs" , "J_Wheel_B", "Wheel_B" ) ;   

   //~ V(J_Wheel_FL):=D(P(O,O_Wheel_FL),abs)+OM(abs,Wheel_FL)^P(O_Wheel_FL,JL)
//~ 
//~ V(J_Wheel_FR):=D(P(O,O_Wheel_FR),abs)+OM(abs,Wheel_FR)^P(O_Wheel_FR,JR)
//~ 
//~ V(J_Wheel_B):=D(P(O,O_Wheel_B),abs)+OM(abs,Wheel_B)^P(O_Wheel_B,J_Wheel_B) 
    
    
//~ {V(J_Wheel_FL)}B123*{[1,0,0]}B123=0
//~ {V(J_Wheel_FL)}B123*{[0,1,0]}B123=0
//~ {V(J_Wheel_FR)}B123*{[1,0,0]}B123=0
//~ {V(J_Wheel_FR)}B123*{[0,1,0]}B123=0
//~ {V(J_Wheel_B)}B123*{[1,0,0]}B123=0
//~ {V(J_Wheel_B)}B123*{[0,1,0]}B123=0  
    
    
    Matrix dPhiNH(6,1);
    dPhiNH(0,0)  = VJ_Wheel_FL * xB123;
    dPhiNH(1,0)  = VJ_Wheel_FL * yB123 ;   
    dPhiNH(2,0)  = VJ_Wheel_FR * xB123;  
    dPhiNH(3,0)  = VJ_Wheel_FR * yB123 ; 
    dPhiNH(4,0)  = VJ_Wheel_B * xB123;;     
    dPhiNH(5,0)  = VJ_Wheel_B * yB123 ;        
 
 cout << "Phi " << endl;
 cout << unatomize(Phi) <<endl;
 cout << "dPhiNH " << endl;
 cout << unatomize(dPhiNH) <<endl;  

// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************

	cout << "Dynamic Equations" << endl;

	Matrix Dynamic_Equations = sys.GenForceSys("ALL");
	cout<<unatomize (Dynamic_Equations) <<endl;

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

    sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , sys, METHOD, dPhiNH);

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

    	//state = x,*dx,*ddx,y,*dy,*ddy,z,*dz,*ddz,a,*da,*dda,b,*db,*ddb,c,*dc,*ddc,r,*dr,*ddr,t1,*dt1,*ddt1,t2,*dt2,*ddt2,t3,*dt3,*ddt3 ;

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


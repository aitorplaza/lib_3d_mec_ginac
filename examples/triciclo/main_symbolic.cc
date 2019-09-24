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

	// Coordinates of the centre of the rear axel
	symbol_numeric x = *sys.new_Coordinate("x","dx","ddx", 0.0 , 0.0 , 0.0);
	symbol_numeric y = *sys.new_Coordinate("y","dy","ddy", 0.0 , 0.0 , 0.0);
	symbol_numeric z = *sys.new_Coordinate("z","dz","ddz", 0.0 , 0.0 , 0.0);

	// Rotation of the chassi
	symbol_numeric a = *sys.new_Coordinate("a","da","dda", 0.0 , 0.0 , 0.0);
	symbol_numeric b = *sys.new_Coordinate("b","db","ddb", 0.0 , 0.0 , 0.0);
	symbol_numeric c = *sys.new_Coordinate("c","dc","ddc", 0.0 , 0.0 , 0.0);

	// Rotation of the steering wheel
	symbol_numeric r = *sys.new_Coordinate("r","dr","ddr", 0.0 , 0.0 , 0.0);

	// Rotation of the front wheel
	symbol_numeric t1 = *sys.new_Coordinate("t1","dt1","ddt1", 0.0 , 0.0 , 0.0);

	// Rotation of the rear left wheel
	symbol_numeric t2 = *sys.new_Coordinate("t2","dt2","ddt2", 0.0 , 0.0 , 0.0);

	// Rotation of the rear right wheel
	symbol_numeric t3 = *sys.new_Coordinate("t3","dt3","ddt3", 0.0 , 0.0 , 0.0);


	// Velocities
	symbol_numeric *dx=sys.get_Velocity("dx");
	symbol_numeric *dy=sys.get_Velocity("dy");
	symbol_numeric *dz=sys.get_Velocity("dz");

	symbol_numeric *da=sys.get_Velocity("da");
	symbol_numeric *db=sys.get_Velocity("db");
	symbol_numeric *dc=sys.get_Velocity("dc");

	symbol_numeric *dr=sys.get_Velocity("dr");

	symbol_numeric *dt1=sys.get_Velocity("dt1");
	symbol_numeric *dt2=sys.get_Velocity("dt2");
	symbol_numeric *dt3=sys.get_Velocity("dt3");

	// Accelerations
	symbol_numeric *ddx=sys.get_Acceleration("ddx");
	symbol_numeric *ddy=sys.get_Acceleration("ddy");
	symbol_numeric *ddz=sys.get_Acceleration("ddz");

	symbol_numeric *dda=sys.get_Acceleration("dda");
	symbol_numeric *ddb=sys.get_Acceleration("ddb");
	symbol_numeric *ddc=sys.get_Acceleration("ddc");

	symbol_numeric *ddr=sys.get_Acceleration("ddr");

	symbol_numeric *ddt1=sys.get_Acceleration("ddt1");
	symbol_numeric *ddt2=sys.get_Acceleration("ddt2");
	symbol_numeric *ddt3=sys.get_Acceleration("ddt3");

	lst coord_indep_init;
	lst vel_indep_init;

// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	// rear axis width
	symbol_numeric W = *sys.new_Parameter("W",4.0);

	// nominal distance between axels
	symbol_numeric L = *sys.new_Parameter("L",4.0);

	// distance from point P to point G of the chassis
	symbol_numeric Lx = *sys.new_Parameter("Lx",1.0);
	symbol_numeric Lz = *sys.new_Parameter("Lz",0.5);

	// Radius of the wheels
	symbol_numeric R = *sys.new_Parameter("R",1.0);

	// Thickness of the wheels
	//symbol_numeric e = *sys.new_Parameter("e",0.5);

// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************

 	sys.new_Base("Baux1",    "xyz",0,0,1,c);
 	sys.new_Base("Baux2",  "Baux1",0,1,0,b);
 	sys.new_Base("BChassi","Baux2",1,0,0,a);

 	sys.new_Base("BFork","BChassi",0,0,1,r);

 	sys.new_Base("BWheel1","BFork",  0,1,0,t1);
 	sys.new_Base("BWheel2","BChassi",0,1,0,t2);
 	sys.new_Base("BWheel3","BChassi",0,1,0,t3);

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	Vector3D VZeroChassi = *sys.new_Vector3D("VZeroChassi",0,0,0,"BChassi");
	Vector3D VZeroWheel1 = *sys.new_Vector3D("VZeroWheel1",0,0,0,"BWheel1");
	Vector3D VZeroWheel2 = *sys.new_Vector3D("VZeroWheel2",0,0,0,"BWheel2");
	Vector3D VZeroWheel3 = *sys.new_Vector3D("VZeroWheel3",0,0,0,"BWheel3");

	Vector3D O_OChassi = *sys.new_Vector3D("O_OChassi",x,y,z,"xyz");
	Vector3D OChassi_CChassi = *sys.new_Vector3D("OChassi_CChassi",Lx,0,Lz,"BChassi");

	Vector3D OChassi_CWheel1 = *sys.new_Vector3D("OChassi_CWheel1",L,   0.0,0.0,"BChassi");
	Vector3D OChassi_CWheel2 = *sys.new_Vector3D("OChassi_CWheel2",0,-W*0.5,0.0,"BChassi");
	Vector3D OChassi_CWheel3 = *sys.new_Vector3D("OChassi_CWheel3",0, W*0.5,0.0,"BChassi");
	
	Vector3D O_CWheel1 = O_OChassi+OChassi_CWheel1;
	Vector3D O_CWheel2 = O_OChassi+OChassi_CWheel2;
	Vector3D O_CWheel3 = O_OChassi+OChassi_CWheel3;

// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * OChassi = sys.new_Point("OChassi","O",&O_OChassi);
	Point * CChassi = sys.new_Point("CChassi","OChassi",&OChassi_CChassi);

	Point * CWheel1 = sys.new_Point("CWheel1","OChassi",&OChassi_CWheel1);
	Point * CWheel2 = sys.new_Point("CWheel2","OChassi",&OChassi_CWheel2);
	Point * CWheel3 = sys.new_Point("CWheel3","OChassi",&OChassi_CWheel3);


// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// gravity constant
//	symbol_numeric g = *sys.new_Parameter("g",10.0);

	// tyre spring constant in z direction
	symbol_numeric kz = *sys.new_Parameter("kz",1000.0);
	symbol_numeric cz = *sys.new_Parameter("cz",10.0);

	// tyre model constant in x direction
	symbol_numeric kx = *sys.new_Parameter("kx",100.0);

	// tyre model constant in y direction
	symbol_numeric ky = *sys.new_Parameter("ky",100.0);

	// Inertial parameters of the Chassi
    	symbol_numeric  mChassi = *sys.new_Parameter("mChassi",1.0);

	//symbol_numeric  mxChassi = *sys.new_Parameter("mxChassi",0.0);
    	//symbol_numeric  myChassi = *sys.new_Parameter("myChassi",0.0);
	//symbol_numeric  mzChassi = *sys.new_Parameter("mzChassi",0.0);

    	symbol_numeric  IxxChassi = *sys.new_Parameter("IxxChassi",1.0);
	symbol_numeric  IxyChassi = *sys.new_Parameter("IxyChassi",0.0);
    	symbol_numeric  IyyChassi = *sys.new_Parameter("IyyChassi",1.0);
	symbol_numeric  IxzChassi = *sys.new_Parameter("IxzChassi",0.0);
    	symbol_numeric  IzzChassi = *sys.new_Parameter("IzzChassi",1.0);
	symbol_numeric  IyzChassi = *sys.new_Parameter("IyzChassi",0.0);


	// Inertial Parameters of Wheel1
    	symbol_numeric  mWheel1 = *sys.new_Parameter("mWheel1",1.0);
	//symbol_numeric  mxWheel1 = *sys.new_Parameter("mxWheel1",0.0);
    	//symbol_numeric  myWheel1 = *sys.new_Parameter("myWheel1",0.0);
	//symbol_numeric  mzWheel1 = *sys.new_Parameter("mzWheel1",0.0);
    	symbol_numeric  IxxWheel1 = *sys.new_Parameter("IxxWheel1",1.0);
	symbol_numeric  IxyWheel1 = *sys.new_Parameter("IxyWheel1",0.0);
    	symbol_numeric  IyyWheel1 = *sys.new_Parameter("IyyWheel1",1.0);
	symbol_numeric  IxzWheel1 = *sys.new_Parameter("IxzWheel1",0.0);
    	symbol_numeric  IzzWheel1 = *sys.new_Parameter("IzzWheel1",1.0);
	symbol_numeric  IyzWheel1 = *sys.new_Parameter("IyzWheel1",0.0);

	// Inertial Parameters of Wheel2
    	symbol_numeric  mWheel2 = *sys.new_Parameter("mWheel2",1.0);
	//symbol_numeric  mxWheel2 = *sys.new_Parameter("mxWheel2",0.0);
    	//symbol_numeric  myWheel2 = *sys.new_Parameter("myWheel2",0.0);
	//symbol_numeric  mzWheel2 = *sys.new_Parameter("mzWheel2",0.0);
    	symbol_numeric  IxxWheel2 = *sys.new_Parameter("IxxWheel2",1.0);
	symbol_numeric  IxyWheel2 = *sys.new_Parameter("IxyWheel2",0.0);
    	symbol_numeric  IyyWheel2 = *sys.new_Parameter("IyyWheel2",1.0);
	symbol_numeric  IxzWheel2 = *sys.new_Parameter("IxzWheel2",0.0);
    	symbol_numeric  IzzWheel2 = *sys.new_Parameter("IzzWheel2",1.0);
	symbol_numeric  IyzWheel2 = *sys.new_Parameter("IyzWheel2",0.0);

	// Inertial Parameters of Wheel3
    	symbol_numeric  mWheel3 = *sys.new_Parameter("mWheel3",1.0);
	//symbol_numeric  mxWheel3 = *sys.new_Parameter("mxWheel3",0.0);
    	//symbol_numeric  myWheel3 = *sys.new_Parameter("myWheel3",0.0);
	//symbol_numeric  mzWheel3 = *sys.new_Parameter("mzWheel3",0.0);
    	symbol_numeric  IxxWheel3 = *sys.new_Parameter("IxxWheel3",1.0);
	symbol_numeric  IxyWheel3 = *sys.new_Parameter("IxyWheel3",0.0);
    	symbol_numeric  IyyWheel3 = *sys.new_Parameter("IyyWheel3",1.0);
	symbol_numeric  IxzWheel3 = *sys.new_Parameter("IxzWheel3",0.0);
    	symbol_numeric  IzzWheel3 = *sys.new_Parameter("IzzWheel3",1.0);
	symbol_numeric  IyzWheel3 = *sys.new_Parameter("IyzWheel3",0.0);


	//Gravity Center Vectors    

	//Vector3D OChassi_GChassi= *sys.new_Vector3D("OChassi_GChassi",mxChassi/mChassi,myChassi/mChassi,mzChassi/mChassi,"BChassi");
	//Vector3D CWheel1_GWheel1= *sys.new_Vector3D("CWheel1_GWheel1",mxWheel1/mWheel1,myWheel1/mWheel1,mzWheel1/mWheel1,"BWheel1");
	//Vector3D CWheel2_GWheel2= *sys.new_Vector3D("CWheel2_GWheel2",mxWheel2/mWheel2,myWheel2/mWheel2,mzWheel2/mWheel2,"BWheel2");
	//Vector3D CWheel3_GWheel3= *sys.new_Vector3D("CWheel3_GWheel3",mxWheel3/mWheel3,myWheel3/mWheel3,mzWheel3/mWheel3,"BWheel3");

	//Inertia Tensors

    	Tensor3D IChassi = *sys.new_Tensor3D("IChassi",	(ex)IxxChassi,(ex)IxyChassi,(ex)IxzChassi,
							(ex)IxyChassi,(ex)IyyChassi,(ex)IyzChassi,
							(ex)IxzChassi,(ex)IyzChassi,(ex)IzzChassi,"BChassi");

    	Tensor3D IWheel1 = *sys.new_Tensor3D("IWheel1",	(ex)IxxWheel1,(ex)IxyWheel1,(ex)IxzWheel1,
							(ex)IxyWheel1,(ex)IyyWheel1,(ex)IyzWheel1,
							(ex)IxzWheel1,(ex)IyzWheel1,(ex)IzzWheel1,"BWheel1");

    	Tensor3D IWheel2 = *sys.new_Tensor3D("IWheel2",	(ex)IxxWheel2,(ex)IxyWheel2,(ex)IxzWheel2,
							(ex)IxyWheel2,(ex)IyyWheel2,(ex)IyzWheel2,
							(ex)IxzWheel2,(ex)IyzWheel2,(ex)IzzWheel2,"BWheel2");

    	Tensor3D IWheel3 = *sys.new_Tensor3D("IWheel3",	(ex)IxxWheel3,(ex)IxyWheel3,(ex)IxzWheel3,
							(ex)IxyWheel3,(ex)IyyWheel3,(ex)IyzWheel3,
							(ex)IxzWheel3,(ex)IyzWheel3,(ex)IzzWheel3,"BWheel3");


// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_Chassi = sys.new_Frame("Fra_Chassi","CChassi","BChassi");
	Frame * Fra_Wheel1 = sys.new_Frame("Fra_Wheel1","CWheel1","BWheel1");
	Frame * Fra_Wheel2 = sys.new_Frame("Fra_Wheel2","CWheel2","BWheel2");
	Frame * Fra_Wheel3 = sys.new_Frame("Fra_Wheel3","CWheel3","BWheel3");



// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	Solid * Chassi = sys.new_Solid("Chassi","CChassi","BChassi","mChassi","VZeroChassi","IChassi");
	Solid * Wheel1 = sys.new_Solid("Wheel1","CWheel1","BWheel1","mWheel1","VZeroWheel1","IWheel1");
	Solid * Wheel2 = sys.new_Solid("Wheel2","CWheel2","BWheel2","mWheel2","VZeroWheel2","IWheel2");
	Solid * Wheel3 = sys.new_Solid("Wheel3","CWheel3","BWheel3","mWheel3","VZeroWheel3","IWheel3");



// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

        Drawing3D * Chassi3D = sys.new_Drawing3D("Chassi3D", "OChassi", "BChassi" ,"./solids/T_shape.stl",1,0,0,0.6);

        Drawing3D * Wheel13D = sys.new_Drawing3D("Wheel13D", Wheel1,"./solids/cylinder_y.stl",1,0,0,0.6);	//Wheel13D->set_scale(0.5);
        Drawing3D * Wheel23D = sys.new_Drawing3D("Wheel23D", Wheel2,"./solids/cylinder_y.stl",1,0,0,0.6);	//Wheel23D->set_scale(0.5);
        Drawing3D * Wheel33D = sys.new_Drawing3D("Wheel33D", Wheel3,"./solids/cylinder_y.stl",1,0,0,0.6);	//Wheel33D->set_scale(0.5);

        Drawing3D * Fra_Chassi3D = sys.new_Drawing3D("Fra_Chassi3D","Fra_Chassi",1.0);
        Drawing3D * Fra_Wheel13D = sys.new_Drawing3D("Fra_Wheel13D","Fra_Wheel1",1.0);
        Drawing3D * Fra_Wheel23D = sys.new_Drawing3D("Fra_Wheel23D","Fra_Wheel2",1.0);
        Drawing3D * Fra_Wheel33D = sys.new_Drawing3D("Fra_Wheel33D","Fra_Wheel3",1.0);

//        Drawing3D * FraPENDULUM = sys.new_Drawing3D("FraPENDULUM",Fra_Pendulum,0.5);
//        Drawing3D * FraABS = sys.new_Drawing3D("FraABS",Frame_abs,0.05);
//        Drawing3D * prueba = sys.new_Drawing3D("prueba", "OBlock", "BPendulum" ,"./solids/block.stl",0,1,1,0.6);		

//	//Pruebas	
//	//Vector3D O_Prueba= *sys.new_Vector3D("O_Prueba",x,0,0 ,"xyz");
//	Vector3D O_Prueba= sys.Position_Vector("O","E");
//
//	Point * Point1 = sys.new_Point("Point1","O",&O_Prueba);	
//        Drawing3D * PointPend = sys.new_Drawing3D("PointPend",Point1,0.03);	
//
//
//        Drawing3D * VectorPrueba = sys.new_Drawing3D("VectorPrueba",&O_Prueba,Point_O);   
//        Drawing3D * VectorPend = sys.new_Drawing3D("VectorPend",&OPendulum_GPendulum,E,1.0,0.0,1.0,1.0);   

// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

//	cout << "Joint Unknown Definition" << endl;


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

        	// Coordinates of the contact points
        	symbol_numeric x1 = *sys.new_Parameter("x1",0.0);
        	symbol_numeric y1 = *sys.new_Parameter("y1",0.0);
        	symbol_numeric z1 = *sys.new_Parameter("z1",0.0);

        	symbol_numeric x2 = *sys.new_Parameter("x2",0.0);
        	symbol_numeric y2 = *sys.new_Parameter("y2",0.0);
        	symbol_numeric z2 = *sys.new_Parameter("z2",0.0);

        	symbol_numeric x3 = *sys.new_Parameter("x3",0.0);
        	symbol_numeric y3 = *sys.new_Parameter("y3",0.0);
        	symbol_numeric z3 = *sys.new_Parameter("z3",0.0);

	Vector3D O_P1 = *sys.new_Vector3D("OP1",x1,y1,z1, "xyz");	
	Vector3D O_P2 = *sys.new_Vector3D("OP2",x2,y2,z2, "xyz");	
	Vector3D O_P3 = *sys.new_Vector3D("OP3",x3,y3,z3, "xyz");	
	
	Point * P1 = sys.new_Point("P1","O",&O_P1);
	Point * P2 = sys.new_Point("P2","O",&O_P2);
	Point * P3 = sys.new_Point("P3","O",&O_P3);

	Vector3D V_abs_C1 = sys.Dt(O_CWheel1,"xyz");
	Vector3D V_abs_C2 = sys.Dt(O_CWheel2,"xyz");
	Vector3D V_abs_C3 = sys.Dt(O_CWheel3,"xyz");
	
	Vector3D OM_abs_W1 = sys.Angular_Velocity("xyz","BWheel1");
	Vector3D OM_abs_W2 = sys.Angular_Velocity("xyz","BWheel2");
	Vector3D OM_abs_W3 = sys.Angular_Velocity("xyz","BWheel3");

	Vector3D V_abs_P1 = V_abs_C1 + OM_abs_W1^(O_P1-O_CWheel1);
	Vector3D V_abs_P2 = V_abs_C2 + OM_abs_W2^(O_P2-O_CWheel2);
	Vector3D V_abs_P3 = V_abs_C3 + OM_abs_W3^(O_P3-O_CWheel3);

        Vector3D eyR1 = *sys.new_Vector3D("eyR1",0,1,0,"BFork");
        Vector3D eyR2 = *sys.new_Vector3D("eyR2",0,1,0,"BChassi");
        Vector3D eyR3 = *sys.new_Vector3D("eyR3",0,1,0,"BChassi");

	symbol_numeric F1x = *sys.new_Input("F1x",0.0);
	symbol_numeric F1y = *sys.new_Input("F1y",0.0);
	symbol_numeric F1z = *sys.new_Input("F1z",0.0);
	
	symbol_numeric F2x = *sys.new_Input("F2x",0.0);
	symbol_numeric F2y = *sys.new_Input("F2y",0.0);
	symbol_numeric F2z = *sys.new_Input("F2z",0.0);

	symbol_numeric F3x = *sys.new_Input("F3x",0.0);
	symbol_numeric F3y = *sys.new_Input("F3y",0.0);
	symbol_numeric F3z = *sys.new_Input("F3z",0.0);

	symbol_numeric M1x = *sys.new_Input("M1x",0.0);
	symbol_numeric M1y = *sys.new_Input("M1y",0.0);
	symbol_numeric M1z = *sys.new_Input("M1z",0.0);
	
	symbol_numeric M2x = *sys.new_Input("M2x",0.0);
	symbol_numeric M2y = *sys.new_Input("M2y",0.0);
	symbol_numeric M2z = *sys.new_Input("M2z",0.0);

	symbol_numeric M3x = *sys.new_Input("M3x",0.0);
	symbol_numeric M3y = *sys.new_Input("M3y",0.0);
	symbol_numeric M3z = *sys.new_Input("M3z",0.0);

	Vector3D FGround1 = *sys.new_Vector3D("FGround1",F1x,F1y,F1z, "xyz");	
	Vector3D FGround2 = *sys.new_Vector3D("FGround2",F2x,F2y,F2z, "xyz");
	Vector3D FGround3 = *sys.new_Vector3D("FGround3",F3x,F3y,F3z, "xyz");

	Vector3D MGround1 = *sys.new_Vector3D("MGround1",M1x,M1y,M1z, "xyz");
	Vector3D MGround2 = *sys.new_Vector3D("MGround2",M2x,M2y,M2z, "xyz");
	Vector3D MGround3 = *sys.new_Vector3D("MGround3",M3x,M3y,M3z, "xyz");
	
	Vector3D VZERO_xyz = *sys.new_Vector3D("VZERO_xyz",0,0,0, "xyz");

	Vector3D eyR1_xyz = eyR1 + VZERO_xyz;
	Vector3D eyR2_xyz = eyR2 + VZERO_xyz;
	Vector3D eyR3_xyz = eyR3 + VZERO_xyz;
	
	Vector3D O_CWheel1_xyz = O_CWheel1 + VZERO_xyz;
	Vector3D O_CWheel2_xyz = O_CWheel2 + VZERO_xyz;
	Vector3D O_CWheel3_xyz = O_CWheel3 + VZERO_xyz;

	Vector3D V_abs_C1_xyz = V_abs_C1 + VZERO_xyz;
	Vector3D V_abs_C2_xyz = V_abs_C2 + VZERO_xyz;
	Vector3D V_abs_C3_xyz = V_abs_C3 + VZERO_xyz;

	Vector3D OM_abs_W1_xyz = OM_abs_W1 + VZERO_xyz;
	Vector3D OM_abs_W2_xyz = OM_abs_W2 + VZERO_xyz;
	Vector3D OM_abs_W3_xyz = OM_abs_W3 + VZERO_xyz;
	
	// Matrix for the Kinematics of the 3 Wheels
	Matrix Kinematics_Wheels(12,3);

	// Matrix for the Kinematics of Wheel 1
	Kinematics_Wheels(0,0)=O_CWheel1_xyz(0,0);
	Kinematics_Wheels(1,0)=O_CWheel1_xyz(1,0);
	Kinematics_Wheels(2,0)=O_CWheel1_xyz(2,0);

	Kinematics_Wheels(3,0)=eyR1_xyz(0,0);
	Kinematics_Wheels(4,0)=eyR1_xyz(1,0);
	Kinematics_Wheels(5,0)=eyR1_xyz(2,0);

	Kinematics_Wheels(6,0)=V_abs_C1_xyz(0,0);
	Kinematics_Wheels(7,0)=V_abs_C1_xyz(1,0);
	Kinematics_Wheels(8,0)=V_abs_C1_xyz(2,0);

	Kinematics_Wheels(9,0) =OM_abs_W1_xyz(0,0);
	Kinematics_Wheels(10,0)=OM_abs_W1_xyz(1,0);
	Kinematics_Wheels(11,0)=OM_abs_W1_xyz(2,0);
	

	// Matrix for the Kinematics of Wheel 2
	Kinematics_Wheels(0,1)=O_CWheel2_xyz(0,0);
	Kinematics_Wheels(1,1)=O_CWheel2_xyz(1,0);
	Kinematics_Wheels(2,1)=O_CWheel2_xyz(2,0);

	Kinematics_Wheels(3,1)=eyR2_xyz(0,0);
	Kinematics_Wheels(4,1)=eyR2_xyz(1,0);
	Kinematics_Wheels(5,1)=eyR2_xyz(2,0);

	Kinematics_Wheels(6,1)=V_abs_C2_xyz(0,0);
	Kinematics_Wheels(7,1)=V_abs_C2_xyz(1,0);
	Kinematics_Wheels(8,1)=V_abs_C2_xyz(2,0);

	Kinematics_Wheels(9,1) =OM_abs_W2_xyz(0,0);
	Kinematics_Wheels(10,1)=OM_abs_W2_xyz(1,0);
	Kinematics_Wheels(11,1)=OM_abs_W2_xyz(2,0);

	// Matrix for the Kinematics of Wheel 3
	Kinematics_Wheels(0,2)=O_CWheel3_xyz(0,0);
	Kinematics_Wheels(1,2)=O_CWheel3_xyz(1,0);
	Kinematics_Wheels(2,2)=O_CWheel3_xyz(2,0);

	Kinematics_Wheels(3,2)=eyR3_xyz(0,0);
	Kinematics_Wheels(4,2)=eyR3_xyz(1,0);
	Kinematics_Wheels(5,2)=eyR3_xyz(2,0);

	Kinematics_Wheels(6,2)=V_abs_C3_xyz(0,0);
	Kinematics_Wheels(7,2)=V_abs_C3_xyz(1,0);
	Kinematics_Wheels(8,2)=V_abs_C3_xyz(2,0);

	Kinematics_Wheels(9,2) =OM_abs_W3_xyz(0,0);
	Kinematics_Wheels(10,2)=OM_abs_W3_xyz(1,0);
	Kinematics_Wheels(11,2)=OM_abs_W3_xyz(2,0);
	
//* sys.new_Matrix( "Kinematics_Wheels"  ,Kinematics_Wheels );
lst mylist;
	//~ sys.export_Matrix_MAPLE ("Kinematics_Wheels"     ,"_Kinematics_Wheels"     ,Kinematics_Wheels,1);
 	sys.export_Matrix_C	("Kinematics_Wheels"     ,"_Kinematics_Wheels"     ,Kinematics_Wheels     ,mylist     ,1);

	//system("maple Kinematics_Wheels.mpl > Kinematics_Wheels.log && bash ./replace.bash Kinematics_Wheels_maple_include.c Kinematics_Wheels_maple_include.c &");

// 	sys.export_Matrix_C	("Kinematics_Wheel_1"     ,"_Kinematics_Wheel_1"     ,Kinematics_Wheel_1     ,mylist     ,1);
	
/**/
// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

	//	Gravity
	Wrench3D * Gravity_Chassi = sys.Gravity_Wrench("Chassi");
	Wrench3D * Gravity_Wheel1 = sys.Gravity_Wrench("Wheel1");
	Wrench3D * Gravity_Wheel2 = sys.Gravity_Wrench("Wheel2");
	Wrench3D * Gravity_Wheel3 = sys.Gravity_Wrench("Wheel3");


	//	Inertia
	Wrench3D * Inertia_Chassi = sys.Inertia_Wrench("Chassi");
	Wrench3D * Inertia_Wheel1 = sys.Inertia_Wrench("Wheel1");
	Wrench3D * Inertia_Wheel2 = sys.Inertia_Wrench("Wheel2");
	Wrench3D * Inertia_Wheel3 = sys.Inertia_Wrench("Wheel3");

	//	Constitutive
	Wrench3D * WGround1 = sys.new_Wrench3D ( "WGround1", FGround1, MGround1, P1 , Wheel1 , "Constitutive") ;
	Wrench3D * WGround2 = sys.new_Wrench3D ( "WGround2", FGround2, MGround2, P2 , Wheel2 , "Constitutive") ;
	Wrench3D * WGround3 = sys.new_Wrench3D ( "WGround3", FGround3, MGround3, P3 , Wheel3 , "Constitutive") ;

	/*
	Wrench3D * Viscosity = sys.new_Wrench3D ( "Viscosity", FV_BlockGuide, MV_BlockGuide, A , Block , "Constitutive") ;

	Wrench3D * Torsional_Block = sys.new_Wrench3D ( "Torsional_Block", - FK_BlockPend , - MK_BlockPend , E , Block , "Constitutive") ;
	Wrench3D * Torsional_Pendulum = sys.new_Wrench3D ( "Torsional_Pendulum ", FK_BlockPend , MK_BlockPend , E , Pendulum , "Constitutive") ;

	//	External
	Wrench3D * Block_Impulse = sys.new_Wrench3D ( "Block_Impulse", FBlock, MBlock, OBlock , Block , "External") ;
	Wrench3D * Pendulum_Impulse = sys.new_Wrench3D ( "Pendulum_Impulse", FPendulum, MPendulum, E , Pendulum , "External") ;

/**/

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
	//Matrix Phi(0,1);
	//Matrix dPhiNH(0,1);

// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************

	//cout << "Dynamic Equations" << endl;

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
	//sys.Matrix_Calculation(Phi, coord_indep_init, vel_indep_init, Dynamic_Equations, sys, METHOD, PROBLEM_TYPE,dPhiNH);


// ************************************************************************************************
// 	Export C code for Direct Simulation 
// ************************************************************************************************

	cout << "Export C code for Direct Simulation " << endl;

    sys.export_Dynamic_Simulation(sys, ORDER , MAPLE, PROBLEM_TYPE);
	//sys.export_Dynamic_Simulation_Common_and_Kinematics(sys, ORDER , MAPLE);
	//sys.export_Dynamic_Simulation_q(sys, ORDER , MAPLE);
	//sys.export_Dynamic_Simulation_z(sys, ORDER , MAPLE);

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

    	state = x,*dx,*ddx,y,*dy,*ddy,z,*dz,*ddz,a,*da,*dda,b,*db,*ddb,c,*dc,*ddc,r,*dr,*ddr,t1,*dt1,*ddt1,t2,*dt2,*ddt2,t3,*dt3,*ddt3 ;

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


/*
//
export LD_LIBRARY_PATH=`pwd`/../../../lib
export PKG_CONFIG_PATH=`pwd`/../../../lib/pkgconfig
g++ -DVIRTUAL_POWER -DCol_MO -DSTANDARD -DMAPLE_ON -DNO_GRAPHVIZ -o main_hexaglidedyns main_hexaglidedyns.cc `pkg-config --cflags --libs lib_3d_mec_ginac-1.1 ginac`
*/

#include <fstream>
#include "lib_3d_mec_ginac/lib_3d_mec_ginac.h"
#include <ginac/ginac.h>

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

using namespace GiNaC; 
using namespace std;	

void printError(const char* arg){
	printf("%s\n", arg);
}

#ifdef PROCEDURE
int C_EXPORT_AS_PROCEDURE=1;
#else
int C_EXPORT_AS_PROCEDURE=0;
#endif

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

int main(int argc, char *argv[]) {

// *****************************************************************************************************************	
cout << " " << endl;
cout << "************************************************" << endl;
cout << "*             HEXAGLIDE                        *" << endl;
cout << "************************************************" << endl;
cout << " " << endl;
system("date");
cout << " " << endl;
// *****************************************************************************************************************

if (argc!=3){ printf("Error: The program %s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\n",argv[0]);	exit(1); }
	
if (0==strcmp(argv[1],"DOWN")){ gravity=DOWN; cout << "DOWN" << endl;}
else{
	if (0==strcmp(argv[1],"UP")){	gravity=UP; cout << "UP" << endl;	}
	else	{		printf("Error: The program %s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\n",argv[0]);		exit(1);	}
}

if (0==strcmp(argv[2],"YES")){ atomization=YES; cout << "YES" << endl;}
else{
	if (0==strcmp(argv[2],"NO")){ atomization=NO; cout << "NO" << endl;}
	else	{ printf("Error: The program %s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\n",argv[0]);	exit(1);}
}

double integration_time=strtod(argv[1], NULL);
double delta_t= strtod(argv[2], NULL);
long int k,steps;
	
printf("integration_time %g delta_t %g\n", integration_time, delta_t);

// ************************************************************************************************
// SYSTEM DEFINITION
// ************************************************************************************************
	System sys(&printError);cout << "" << endl;

#ifdef LAG	
	# define METHOD LAGRANGE
#endif

#ifdef V_P
	# define METHOD VIRTUAL_POWER
#endif

// Constant definitions
// ************************************************************************************************
symbol_numeric lp	= *sys.new_Parameter("lp"	,0.073085);
symbol_numeric alpha	= *sys.new_Parameter("alpha"	,2*3.141592653589793/3);
symbol_numeric e 	= *sys.new_Parameter("e"		,0.136508/2);
symbol_numeric lb 	= *sys.new_Parameter("lb"	,0.484);
symbol_numeric l 	= *sys.new_Parameter("l"		,1); // La longitud de las barras es realmente es 0.9723m pero la distancia entre centros de Kardans 1m.
symbol_numeric h 	= *sys.new_Parameter("h"		,0.881202+0.030471660239781);
symbol_numeric Klg 	= *sys.new_Parameter("Klg"	,0.01/(2*3.141592653589793)); // (translation/rotation of quides in m / rad)

symbol_numeric pi	= *sys.new_Parameter("pi"	,3.141592653589793);

// GENERALISED COORDINATES DEFINITION
// ************************************************************************************************
// Glides (position)

symbol_numeric z11 = *sys.new_Coordinate("z11","dz11","ddz11",0,0,0);
symbol_numeric z12 = *sys.new_Coordinate("z12","dz12","ddz12",0,0,0);
symbol_numeric z21 = *sys.new_Coordinate("z21","dz21","ddz21",0,0,0);
symbol_numeric z22 = *sys.new_Coordinate("z22","dz22","ddz22",0,0,0);
symbol_numeric z31 = *sys.new_Coordinate("z31","dz31","ddz31",0,0,0);
symbol_numeric z32 = *sys.new_Coordinate("z32","dz32","ddz32",0,0,0);

#ifdef STANDARD
// Bar (euler angles)
symbol_numeric phi11 		= *sys.new_Coordinate("phi11"		,"dphi11"		,"ddphi11"		,0.4,0,0);
symbol_numeric phi12 		= *sys.new_Coordinate("phi12"		,"dphi12"		,"ddphi12"		,0.4,0,0);
symbol_numeric phi21 		= *sys.new_Coordinate("phi21"		,"dphi21"		,"ddphi21"		,0.4,0,0);
symbol_numeric phi22 		= *sys.new_Coordinate("phi22"		,"dphi22"		,"ddphi22"		,0.4,0,0);
symbol_numeric phi31 		= *sys.new_Coordinate("phi31"		,"dphi31"		,"ddphi31"		,0.4,0,0);
symbol_numeric phi32 		= *sys.new_Coordinate("phi32"		,"dphi32"		,"ddphi32"		,0.4,0,0);

symbol_numeric theta11 	= *sys.new_Coordinate("theta11"	,"dtheta11"	,"ddtheta11"	,0,0,0);
symbol_numeric theta12 	= *sys.new_Coordinate("theta12"	,"dtheta12"	,"ddtheta12"	,0,0,0);
symbol_numeric theta21 	= *sys.new_Coordinate("theta21"	,"dtheta21"	,"ddtheta21"	,0,0,0);
symbol_numeric theta22 	= *sys.new_Coordinate("theta22"	,"dtheta22"	,"ddtheta22"	,0,0,0);
symbol_numeric theta31 	= *sys.new_Coordinate("theta31"	,"dtheta31"	,"ddtheta31"	,0,0,0);
symbol_numeric theta32 	= *sys.new_Coordinate("theta32"	,"dtheta32"	,"ddtheta32"	,0,0,0);
#endif

// Head (coordinates: 3 x position + 3 x angles)
symbol_numeric x 	= *sys.new_Coordinate("X"				,"dX"				,"ddX"				,0,0,0);
symbol_numeric y 	= *sys.new_Coordinate("Y"				,"dY"				,"ddY"				,0,0,0);
symbol_numeric z 	= *sys.new_Coordinate("Z"				,"dZ"				,"ddZ"				,0,0,0);
symbol_numeric phi	= *sys.new_Coordinate("phi"			,"dphi"			,"ddphi"			,0,0,0);
symbol_numeric theta	= *sys.new_Coordinate("theta"		,"dtheta"		,"ddtheta"		,0,0,0);
symbol_numeric psi	= *sys.new_Coordinate("psi"			,"dpsi"			,"ddpsi"			,0,0,0);

// Generalizated velocities definition
// ************************************************************************************************
symbol_numeric *dz11			= sys.get_Velocity("dz11");
symbol_numeric *dz12			= sys.get_Velocity("dz12");
symbol_numeric *dz21			= sys.get_Velocity("dz21");
symbol_numeric *dz22			= sys.get_Velocity("dz22");
symbol_numeric *dz31			= sys.get_Velocity("dz31");
symbol_numeric *dz32			= sys.get_Velocity("dz32");

#ifdef STANDARD
symbol_numeric *dphi11		= sys.get_Velocity("dphi11");
symbol_numeric *dphi12		= sys.get_Velocity("dphi12");
symbol_numeric *dphi21		= sys.get_Velocity("dphi21");
symbol_numeric *dphi22		= sys.get_Velocity("dphi22");
symbol_numeric *dphi31		= sys.get_Velocity("dphi31");
symbol_numeric *dphi32		= sys.get_Velocity("dphi32");

symbol_numeric *dtheta11	= sys.get_Velocity("dtheta11");
symbol_numeric *dtheta12	= sys.get_Velocity("dtheta12");
symbol_numeric *dtheta21	= sys.get_Velocity("dtheta21");
symbol_numeric *dtheta22	= sys.get_Velocity("dtheta22");
symbol_numeric *dtheta31	= sys.get_Velocity("dtheta31");
symbol_numeric *dtheta32	= sys.get_Velocity("dtheta32");
#endif

symbol_numeric *dx				= sys.get_Velocity("dX");
symbol_numeric *dy				= sys.get_Velocity("dY");
symbol_numeric *dz				= sys.get_Velocity("dZ");
symbol_numeric *dphi			= sys.get_Velocity("dphi");
symbol_numeric *dtheta		= sys.get_Velocity("dtheta");
symbol_numeric *dpsi			= sys.get_Velocity("dpsi");

// Generalizated acceleration definition
// ************************************************************************************************
symbol_numeric *ddz11			= sys.get_Acceleration("ddz11");
symbol_numeric *ddz12			= sys.get_Acceleration("ddz12");
symbol_numeric *ddz21			= sys.get_Acceleration("ddz21");
symbol_numeric *ddz22			= sys.get_Acceleration("ddz22");
symbol_numeric *ddz31			= sys.get_Acceleration("ddz31");
symbol_numeric *ddz32			= sys.get_Acceleration("ddz32");

#ifdef STANDARD
symbol_numeric *ddphi11		= sys.get_Acceleration("ddphi11");
symbol_numeric *ddphi12		= sys.get_Acceleration("ddphi12");
symbol_numeric *ddphi21		= sys.get_Acceleration("ddphi21");
symbol_numeric *ddphi22		= sys.get_Acceleration("ddphi22");
symbol_numeric *ddphi31		= sys.get_Acceleration("ddphi31");
symbol_numeric *ddphi32		= sys.get_Acceleration("ddphi32");

symbol_numeric *ddtheta11	= sys.get_Acceleration("ddtheta11");
symbol_numeric *ddtheta12	= sys.get_Acceleration("ddtheta12");
symbol_numeric *ddtheta21	= sys.get_Acceleration("ddtheta21");
symbol_numeric *ddtheta22	= sys.get_Acceleration("ddtheta22");
symbol_numeric *ddtheta31	= sys.get_Acceleration("ddtheta31");
symbol_numeric *ddtheta32	= sys.get_Acceleration("ddtheta32");
#endif

symbol_numeric *ddx				= sys.get_Acceleration("ddX");
symbol_numeric *ddy				= sys.get_Acceleration("ddY");
symbol_numeric *ddz				= sys.get_Acceleration("ddZ");
symbol_numeric *ddphi			= sys.get_Acceleration("ddphi");
symbol_numeric *ddtheta		= sys.get_Acceleration("ddtheta");
symbol_numeric *ddpsi			= sys.get_Acceleration("ddpsi");

// ************************************************************************************************
// Initial Position - Velocity
// ************************************************************************************************
symbol_numeric z11_0  = *sys.new_Parameter   ("z11_0"		,0.0);
symbol_numeric dz11_0 = *sys.new_Parameter   ("dz11_0"	,0.0);

symbol_numeric z12_0  = *sys.new_Parameter   ("z12_0"		,0.0);
symbol_numeric dz12_0 = *sys.new_Parameter   ("dz12_0"	,0.0);

symbol_numeric z21_0  = *sys.new_Parameter   ("z21_0"		,0.0);
symbol_numeric dz21_0 = *sys.new_Parameter   ("dz21_0"	,0.0);

symbol_numeric z22_0  = *sys.new_Parameter   ("z22_0"		,0.0);
symbol_numeric dz22_0 = *sys.new_Parameter   ("dz22_0"	,0.0);

symbol_numeric z31_0  = *sys.new_Parameter   ("z31_0"		,0.0);
symbol_numeric dz31_0 = *sys.new_Parameter   ("dz31_0"	,0.0);

symbol_numeric z32_0  = *sys.new_Parameter   ("z32_0"		,0.0);
symbol_numeric dz32_0 = *sys.new_Parameter   ("dz32_0"	,0.0);

lst coord_indep_init; coord_indep_init	= (z11-z11_0),(z12-z12_0),(z21-z21_0),(z22-z22_0),(z31-z31_0),(z32-z32_0);
lst vel_indep_init;   vel_indep_init		= (*dz11-dz11_0),(*dz12-dz12_0),(*dz21-dz21_0),(*dz22-dz22_0),(*dz31-dz31_0),(*dz32-dz32_0);
// ************************************************************************************************
// KINEMATICS
// ************************************************************************************************
// Bases
// ------------------------------------------------------------------------------------------------
Base B123 	= *sys.new_Base ("Base1"	,"xyz"				,0,0,1	,phi );
Base B123p 	= *sys.new_Base ("Base2"	,"Base1"			,0,1,0	,theta );
Base B123pp	= *sys.new_Base ("Base3"	,"Base2"			,1,0,0	,psi );

sys.new_Base	("x'y'z'"	,"xyz",0,0,1,+alpha);
sys.new_Base	("x''y''z''"	,"xyz",0,0,1,-alpha);

// Husillos
Base Br11 	= *sys.new_Base ("Br11"		,"xyz"				,0,0,1	,z11/Klg);
Base Br12 	= *sys.new_Base ("Br12"		,"xyz"				,0,0,1	,z12/Klg);
Base Br21 	= *sys.new_Base ("Br21"		,"x'y'z'"			,0,0,1	,z21/Klg);
Base Br22		= *sys.new_Base ("Br22"		,"x'y'z'"			,0,0,1	,z22/Klg);
Base Br31 	= *sys.new_Base ("Br31"		,"x''y''z''"	,0,0,1	,z31/Klg);
Base Br32 	= *sys.new_Base ("Br32"		,"x''y''z''"	,0,0,1	,z32/Klg);

// Vectors
// ------------------------------------------------------------------------------------------------
Vector3D OOp 			= *sys.new_Vector3D("OOp"			,x,y,z			,"xyz");
	
Vector3D OpA11 		= *sys.new_Vector3D("OpA11"		,lp*1,+e,0	,"Base3");
Vector3D OpA12 		= *sys.new_Vector3D("OpA12"		,lp*1,-e,0	,"Base3");

Vector3D OpA21 		= *sys.new_Vector3D("OpA21"		,lp*cos(alpha)-e*sin(alpha),lp*sin(alpha)+e*cos(alpha),0	,"Base3");
Vector3D OpA22 		= *sys.new_Vector3D("OpA22"		,lp*cos(alpha)+e*sin(alpha),lp*sin(alpha)-e*cos(alpha),0	,"Base3");

Vector3D OpA31 		= *sys.new_Vector3D("OpA31"		,lp*cos(alpha)+e*sin(alpha),-lp*sin(alpha)+e*cos(alpha),0	,"Base3");
Vector3D OpA32 		= *sys.new_Vector3D("OpA32"		,lp*cos(alpha)-e*sin(alpha),-lp*sin(alpha)-e*cos(alpha),0	,"Base3");

Vector3D OB11 		= *sys.new_Vector3D("OB11"		,lb,e,z11+h		,"xyz");
Vector3D OO11 		= *sys.new_Vector3D("OO11"		,lb,e,0				,"xyz");
Vector3D OB12 		= *sys.new_Vector3D("OB12"		,lb,-e,z12+h	,"xyz");
Vector3D OO12 		= *sys.new_Vector3D("OO12"		,lb,-e,0			,"xyz");

Vector3D OB21 		= *sys.new_Vector3D("OB21"		,lb,e,z21+h		,"x'y'z'");
Vector3D OO21 		= *sys.new_Vector3D("OO21"		,lb,e,0				,"x'y'z'");
Vector3D OB22 		= *sys.new_Vector3D("OB22"		,lb,-e,z22+h	,"x'y'z'");
Vector3D OO22 		= *sys.new_Vector3D("OO22"		,lb,-e,0			,"x'y'z'");

Vector3D OB31 		= *sys.new_Vector3D("OB31"		,lb,e,z31+h		,"x''y''z''");
Vector3D OO31 		= *sys.new_Vector3D("OO31"		,lb,e,0				,"x''y''z''");
Vector3D OB32 		= *sys.new_Vector3D("OB32"		,lb,-e,z32+h	,"x''y''z''");
Vector3D OO32 		= *sys.new_Vector3D("OO32"		,lb,-e,0			,"x''y''z''");

// Points
// ------------------------------------------------------------------------------------------------
Point * Op 		= sys.new_Point("Op"		,"O"		,&OOp);

Point * A11 	= sys.new_Point("A11"		,"Op"		,&OpA11);
Point * A12 	= sys.new_Point("A12"		,"Op"		,&OpA12);

Point * A21 	= sys.new_Point("A21"		,"Op"		,&OpA21);
Point * A22 	= sys.new_Point("A22"		,"Op"		,&OpA22);

Point * A31 	= sys.new_Point("A31"		,"Op"		,&OpA31);
Point * A32 	= sys.new_Point("A32"		,"Op"		,&OpA32);

Point * B11 	= sys.new_Point("B11"		,"O"		,&OB11);
Point * O11 	= sys.new_Point("O11"		,"O"		,&OO11);

Point * B12 	= sys.new_Point("B12"		,"O"		,&OB12);
Point * O12 	= sys.new_Point("O12"		,"O"		,&OO12);

Point * B21 	= sys.new_Point("B21"		,"O"		,&OB21);
Point * O21 	= sys.new_Point("O21"		,"O"		,&OO21);

Point * B22 	= sys.new_Point("B22"		,"O"		,&OB22);
Point * O22		= sys.new_Point("O22"		,"O"		,&OO22);

Point * B31 	= sys.new_Point("B31"		,"O"		,&OB31);
Point * O31 	= sys.new_Point("O31"		,"O"		,&OO31);

Point * B32 	= sys.new_Point("B32"		,"O"		,&OB32); 
Point * O32 	= sys.new_Point("O32"		,"O"		,&OO32);

Vector3D OA11 		= sys.Position_Vector("O"		,"A11");
Vector3D OA12 		= sys.Position_Vector("O"		,"A12");
Vector3D OA21 		= sys.Position_Vector("O"		,"A21");
Vector3D OA22 		= sys.Position_Vector("O"		,"A22");
Vector3D OA31 		= sys.Position_Vector("O"		,"A31");
Vector3D OA32 		= sys.Position_Vector("O"		,"A32");

// Define Frames
// ------------------------------------------------------------------------------------------------

	Frame * R = sys.new_Frame("R","O","xyz");
	Frame * R3 = sys.new_Frame("R3","Op","Base3");
	Frame * Rr11 = sys.new_Frame("Rr11","B11","xyz");
	Frame * Rr12 = sys.new_Frame("Rr12","B12","xyz");
	Frame * Rr21 = sys.new_Frame("Rr21","B21","x'y'z'");
	Frame * Rr22 = sys.new_Frame("Rr22","B22","x'y'z'");
	Frame * Rr31 = sys.new_Frame("Rr31","B31","x''y''z''");
	Frame * Rr32 = sys.new_Frame("Rr32","B32","x''y''z''");

	Drawing3D * FraABS = sys.new_Drawing3D("FraABS",Frame_abs,0.1);
	Drawing3D * FraR = sys.new_Drawing3D("FraR",R,0.1);
	Drawing3D * FraR3 = sys.new_Drawing3D("FraR3",R3,0.1);
	Drawing3D * FraRr11 = sys.new_Drawing3D("FraRr11",Rr11,0.1);
	Drawing3D * FraRr12 = sys.new_Drawing3D("FraRr12",Rr12,0.1);
	Drawing3D * FraRr21 = sys.new_Drawing3D("FraRr21",Rr21,0.1);
	Drawing3D * FraRr22 = sys.new_Drawing3D("FraRr22",Rr22,0.1);
	Drawing3D * FraRr31 = sys.new_Drawing3D("FraRr31",Rr31,0.1);
	Drawing3D * FraRr32 = sys.new_Drawing3D("FraRr32",Rr32,0.1);





	Drawing3D * Estructura   = sys.new_Drawing3D("Estructura"  ,"O","xyz","./solids/Estructura.osg",0.5,0,0,0.3);
	Drawing3D * Cabeza       = sys.new_Drawing3D("Cabeza"      ,"Op","Base3","./solids/Cabeza.osg",1.0,0,0,1.0);
	Drawing3D * Carro11      = sys.new_Drawing3D("Carro11"     ,"B11","xyz","./solids/Carro.osg",0,1.0,0,1.0);
	Drawing3D * Carro12      = sys.new_Drawing3D("Carro12"     ,"B12","xyz","./solids/Carro.osg",0,1.0,0,1.0);
	Drawing3D * Carro21      = sys.new_Drawing3D("Carro21"     ,"B21","x'y'z'","./solids/Carro.osg",0,1.0,0,1.0);
	Drawing3D * Carro22      = sys.new_Drawing3D("Carro22"     ,"B22","x'y'z'","./solids/Carro.osg",0,1.0,0,1.0);
	Drawing3D * Carro31      = sys.new_Drawing3D("Carro31"     ,"B31","x''y''z''","./solids/Carro.osg",0,1.0,0,1.0);
	Drawing3D * Carro32      = sys.new_Drawing3D("Carro32"     ,"B32","x''y''z''","./solids/Carro.osg",0,1.0,0,1.0);

#ifdef STANDARD

// Bases
// ------------------------------------------------------------------------------------------------
// De la base xyz salen Bb1 y Bb2 (Basebrazo1 y Basebrazo2). primero se construyen las auxiliares Bb11a
Base Bb11a 	= *sys.new_Base ("Bb11a"	,"xyz"				,0,1,0	,phi11);
Base Bb11 	= *sys.new_Base ("Bb11"		,"Bb11a"			,1,0,0	,theta11);
Base Bb12a 	= *sys.new_Base ("Bb12a"	,"xyz"				,0,1,0	,phi12);
Base Bb12 	= *sys.new_Base ("Bb12"		,"Bb12a"			,1,0,0	,theta12);

// De la base x'y'z' salen Bb3 y Bb4
Base Bb21a 	= *sys.new_Base ("Bb21a"	,"x'y'z'"			,0,1,0	,phi21);
Base Bb21 	= *sys.new_Base ("Bb21"		,"Bb21a"			,1,0,0	,theta21);
Base Bb22a 	= *sys.new_Base ("Bb22a"	,"x'y'z'"			,0,1,0	,phi22);
Base Bb22 	= *sys.new_Base ("Bb22"		,"Bb22a"			,1,0,0	,theta22);

// De la base x'y'z' salen Bb31 y Bb32
Base Bb31a 	= *sys.new_Base ("Bb31a"	,"x''y''z''"	,0,1,0	,phi31);
Base Bb31 	= *sys.new_Base ("Bb31"		,"Bb31a"			,1,0,0	,theta31);
Base Bb32a 	= *sys.new_Base ("Bb32a"	,"x''y''z''"	,0,1,0	,phi32);
Base Bb32 	= *sys.new_Base ("Bb32"		,"Bb32a"			,1,0,0	,theta32);

// Vectors
// ------------------------------------------------------------------------------------------------
Vector3D B11A11b	= *sys.new_Vector3D("B11A11b"	,0,0,-l		,"Bb11");
Vector3D B12A12b	= *sys.new_Vector3D("B12A12b"	,0,0,-l		,"Bb12");
Vector3D B21A21b	= *sys.new_Vector3D("B21A21b"	,0,0,-l		,"Bb21");
Vector3D B22A22b	= *sys.new_Vector3D("B22A22b"	,0,0,-l		,"Bb22");
Vector3D B31A31b	= *sys.new_Vector3D("B31A31b"	,0,0,-l		,"Bb31");
Vector3D B32A32b	= *sys.new_Vector3D("B32A32b"	,0,0,-l		,"Bb32");

// Points
// ------------------------------------------------------------------------------------------------
Point * A11b	= sys.new_Point("A11b"	,"B11"	,&B11A11b);
Point * A12b	= sys.new_Point("A12b"	,"B12"	,&B12A12b);
Point * A21b	= sys.new_Point("A21b"	,"B21"	,&B21A21b);
Point * A22b	= sys.new_Point("A22b"	,"B22"	,&B22A22b);
Point * A31b	= sys.new_Point("A31b"	,"B31"	,&B31A31b);
Point * A32b	= sys.new_Point("A32b"	,"B32"	,&B32A32b);

Vector3D OA11b		= sys.Position_Vector("O"		,"A11b");
Vector3D OA12b		= sys.Position_Vector("O"		,"A12b");
Vector3D OA21b 		= sys.Position_Vector("O"		,"A21b");
Vector3D OA22b 		= sys.Position_Vector("O"		,"A22b");
Vector3D OA31b 		= sys.Position_Vector("O"		,"A31b");
Vector3D OA32b 		= sys.Position_Vector("O"		,"A32b");

Vector3D A11A11b	= sys.Position_Vector("A11"	,"A11b");
Vector3D A12A12b	= sys.Position_Vector("A12"	,"A12b");
Vector3D A21A21b	= sys.Position_Vector("A21"	,"A21b");
Vector3D A22A22b	= sys.Position_Vector("A22"	,"A22b");
Vector3D A31A31b	= sys.Position_Vector("A31"	,"A31b");
Vector3D A32A32b	= sys.Position_Vector("A32"	,"A32b");

// Define Frames
// ------------------------------------------------------------------------------------------------

Frame * Rb11 = sys.new_Frame("Rb11","A11","Bb11");
Frame * Rb12 = sys.new_Frame("Rb12","A12","Bb12");
Frame * Rb21 = sys.new_Frame("Rb21","A21","Bb21");
Frame * Rb22 = sys.new_Frame("Rb22","A22","Bb22");
Frame * Rb31 = sys.new_Frame("Rb31","A31","Bb31");
Frame * Rb32 = sys.new_Frame("Rb32","A32","Bb32");

Drawing3D * FraRb11 = sys.new_Drawing3D("FraRb11",Rb11,0.1);
Drawing3D * FraRb12 = sys.new_Drawing3D("FraRb12",Rb12,0.1);
Drawing3D * FraRb21 = sys.new_Drawing3D("FraRb21",Rb21,0.1);
Drawing3D * FraRb22 = sys.new_Drawing3D("FraRb22",Rb22,0.1);
Drawing3D * FraRb31 = sys.new_Drawing3D("FraRb31",Rb31,0.1);
Drawing3D * FraRb32 = sys.new_Drawing3D("FraRb32",Rb32,0.1);

Drawing3D * Barra11      = sys.new_Drawing3D("Barra11"     ,"A11","Bb11","./solids/Barra.osg",0.5,0.5,0.5,1.0);
Drawing3D * Barra12      = sys.new_Drawing3D("Barra12"     ,"A12","Bb12","./solids/Barra.osg",0.5,0.5,0.5,1.0);
Drawing3D * Barra21      = sys.new_Drawing3D("Barra21"     ,"A21","Bb21","./solids/Barra.osg",0.5,0.5,0.5,1.0);
Drawing3D * Barra22      = sys.new_Drawing3D("Barra22"     ,"A22","Bb22","./solids/Barra.osg",0.5,0.5,0.5,1.0);
Drawing3D * Barra31      = sys.new_Drawing3D("Barra31"     ,"A31","Bb31","./solids/Barra.osg",0.5,0.5,0.5,1.0);
Drawing3D * Barra32      = sys.new_Drawing3D("Barra32"     ,"A32","Bb32","./solids/Barra.osg",0.5,0.5,0.5,1.0);

#endif

// ************************************************************************************************
// DYNAMICS
// ************************************************************************************************

// Real Parameters from CAD, catalogs and weight measurement data.
// ************************************************************************************************
//symbol_numeric g	= *sys.new_Parameter("g"	,9.81*1.0);	// m/s^2
//symbol_numeric g	= *sys.new_Parameter("g"	,0.00);	// m/s^2

symbol_numeric Ka	= *sys.new_Parameter("Ka"	,0.8);			// (intensity/tension of motor in A / V)
symbol_numeric Kb	= *sys.new_Parameter("Kb"	,0.51);			// (torque/intensity of motor in N m / A)

// Viscous friction estimation at carriages 1/6*mass * g / (1 cm/s)(7.184/6+2.765+1.813)*9.81/(1/100)= 5.6656e+03
// ------------------------------------------------------------------------------------------------
symbol_numeric  c11 = *sys.new_Parameter("c11"	,5.6656e+03);
symbol_numeric  c12 = *sys.new_Parameter("c12"	,5.6656e+03);
symbol_numeric  c21 = *sys.new_Parameter("c21"	,5.6656e+03);
symbol_numeric  c22 = *sys.new_Parameter("c22"	,5.6656e+03);
symbol_numeric  c31 = *sys.new_Parameter("c31"	,5.6656e+03);
symbol_numeric  c32 = *sys.new_Parameter("c32"	,5.6656e+03);

// Dynamic Parameter Definition
//
#ifdef STANDARD 
symbol_numeric mzp	= *sys.new_Parameter("mzp"	,-0.035572*6.6970);	// kg m
symbol_numeric mp		= *sys.new_Parameter("mp"		,6.6970); 					// kg

symbol_numeric mz11	= *sys.new_Parameter("mz11"	,-0.5*2.9369); 			// kg m
symbol_numeric m11	= *sys.new_Parameter("m11"	,2.9369); 					// kg

symbol_numeric mz12 = *sys.new_Parameter("mz12"	,-0.5*2.9369); 			// kg m
symbol_numeric m12	= *sys.new_Parameter("m12"	,2.9369); 					// kg

symbol_numeric mz21 = *sys.new_Parameter("mz21"	,-0.5*2.9369); 			// kg m
symbol_numeric m21	= *sys.new_Parameter("m21"	,2.9369); 					// kg

symbol_numeric mz22 = *sys.new_Parameter("mz22"	,-0.5*2.9369); 			// kg m
symbol_numeric m22	= *sys.new_Parameter("m22"	,2.9369); 					// kg

symbol_numeric mz31 = *sys.new_Parameter("mz31"	,-0.5*2.9369); 			// kg m
symbol_numeric m31	= *sys.new_Parameter("m31"	,2.9369); 					// kg

symbol_numeric mz32 = *sys.new_Parameter("mz32"	,-0.5*2.9369); 			// kg m
symbol_numeric m32	= *sys.new_Parameter("m32"	,2.9369); 					// kg

symbol_numeric mc11 = *sys.new_Parameter("mc11"	,2.867); // kg 
symbol_numeric mc12 = *sys.new_Parameter("mc12"	,2.867); // kg
symbol_numeric mc21 = *sys.new_Parameter("mc21"	,2.867); // kg
symbol_numeric mc22 = *sys.new_Parameter("mc22"	,2.867); // kg
symbol_numeric mc31 = *sys.new_Parameter("mc31"	,2.867); // kg
symbol_numeric mc32 = *sys.new_Parameter("mc32"	,2.867); // kg

symbol_numeric  I_P_11 		= *sys.new_Parameter("I_P_11"	,0.028319); 		// kg m^2
symbol_numeric  I_P_22 		= *sys.new_Parameter("I_P_22"	,0.028319); 		// kg m^2
symbol_numeric  I_P_33 		= *sys.new_Parameter("I_P_33"	,0.038045);		// kg m^2

symbol_numeric  I_B11_11	= *sys.new_Parameter("I_B11_11"	,1.0435); 		// kg m^2
symbol_numeric  I_B11_22 	= *sys.new_Parameter("I_B11_22"	,1.0435); 		// kg m^2
symbol_numeric  I_B11_33	= *sys.new_Parameter("I_B11_33"	,0.0022722); 		// kg m^2

symbol_numeric  I_B12_11 	= *sys.new_Parameter("I_B12_11"	,1.0435); 		// kg m^2
symbol_numeric  I_B12_22 	= *sys.new_Parameter("I_B12_22"	,1.0435); 		// kg m^2
symbol_numeric  I_B12_33 	= *sys.new_Parameter("I_B12_33"	,0.0022722);		// kg m^2
	
symbol_numeric  I_B21_11 	= *sys.new_Parameter("I_B21_11"	,1.0435); 		// kg m^2
symbol_numeric  I_B21_22 	= *sys.new_Parameter("I_B21_22"	,1.0435); 		// kg m^2
symbol_numeric  I_B21_33 	= *sys.new_Parameter("I_B21_33"	,0.0022722); 		// kg m^2

symbol_numeric  I_B22_11 	= *sys.new_Parameter("I_B22_11"	,1.0435); 		// kg m^2
symbol_numeric  I_B22_22 	= *sys.new_Parameter("I_B22_22"	,1.0435); 		// kg m^2
symbol_numeric  I_B22_33 	= *sys.new_Parameter("I_B22_33"	,0.0022722); 		// kg m^2

symbol_numeric  I_B31_11 	= *sys.new_Parameter("I_B31_11"	,1.0435); 		// kg m^2
symbol_numeric  I_B31_22 	= *sys.new_Parameter("I_B31_22"	,1.0435); 		// kg m^2
symbol_numeric  I_B31_33 	= *sys.new_Parameter("I_B31_33"	,0.0022722); 		// kg m^2

symbol_numeric  I_B32_11 	= *sys.new_Parameter("I_B32_11"	,1.0435); 		// kg m^2
symbol_numeric  I_B32_22 	= *sys.new_Parameter("I_B32_22"	,1.0435); 		// kg m^2
symbol_numeric  I_B32_33 	= *sys.new_Parameter("I_B32_33"	,0.0022722); 		// kg m^2

symbol_numeric  I_R 			= *sys.new_Parameter("I_R"			,0.00013168);	// kg m^2
#endif

#ifdef REDUCED
//Inertial Properties (bars removed)

/*	Bars can be removed without altering the kinetics, using the inertia tranfer concept.
Data
lp = 0.073085; e = 0.136508/2; l = 1; m11 = 2.9369;
I_B11_11 = 1.0435; mc11 = 2.867; mp = 6.6970; I_P_11 = 0.028319; I_P_33 = 0.038045

Procedure (inertia trasfer)
We cosidered the mas replaced by a mass mb at its center and two mases ma at the tips. 

ma*l^2+mb*l^2/4=I_B11_11 ; 2*ma+mb=m11
ma=(I_B11_11-m11*l^2/4)/(l^2-2*l^2/4) = 0.61855
mb=m11-2*ma

Mass ma, at the joint with the carriage can be transferred to the carriage

new_m11 = m11 - 2*ma = m11 - 1.2371

then 
mass_transfer_to_carriage=ma 

""""""new_mc11 = mc11 +  ma = mc11 +  0.61855 """"""

finally the new_mij can be transfered to the head, this will leave the bar
completelly inertialess.

mass_transfer_to_head = ma 

""""""new_mp = mp + 6 * ma = mp + 3.7113 """""

In this way we can completelly neglect the body bar.But the mass transferred to the head, will
affect not only the head mass but also the new moments of inertia.

So the change needed to remove the dynamics of the bar are:

1.- new_carriage_mass = 
		""""""new_mc11 = mc11 +  ma = mc11 + 0.61855""""""

2.- new_head_mass = 
		""""""new_mp = mp + 6 * ma = mp + 3.7113 """""

3.- new_head_first_inertia_moments = no change

4.- new_head_inertia_moments_cil_axis = 
		""""""new_I_P_33 = I_P_33 + 6 * ma * (lp^2+e^2) = I_P_33 + 0.0371130955325733 """""""

5.- new_head_inertia_moments_out_cil_axis = 
		""""""new_I_P_11 = I_P_11 + 6 * ma * lp^2 = I_P_33 + 0.0198236017471425"""""""

6.- Bar gets replaced by a mass at its center mb
*/

	symbol mzp = *sys.new_Parameter("mzp",-0.035572*6.6970); // kg m
	symbol mp =  *sys.new_Parameter("mp",6.6970+3.7113); // kg

//	symbol mz11 = *sys.new_Parameter("mz11",-0.5*2.9369); // kg m
	symbol m11 =  *sys.new_Parameter("m11",2.9369-1.2371); // kg

//	symbol mz12 = *sys.new_Parameter("mz12",-0.5*2.9369); // kg m
	symbol m12 =  *sys.new_Parameter("m12",2.9369-1.2371); // kg

//	symbol mz21 = *sys.new_Parameter("mz21",-0.5*2.9369); // kg m
	symbol m21 =  *sys.new_Parameter("m21",2.9369-1.2371); // kg

//	symbol mz22 = *sys.new_Parameter("mz22",-0.5*2.9369); // kg m
	symbol m22 =  *sys.new_Parameter("m22",2.9369-1.2371); // kg

//	symbol mz31 = *sys.new_Parameter("mz31",-0.5*2.9369); // kg m
	symbol m31 =  *sys.new_Parameter("m31",2.9369-1.2371); // kg

//	symbol mz32 = *sys.new_Parameter("mz32",-0.5*2.9369); // kg m
	symbol m32 =  *sys.new_Parameter("m32",2.9369-1.2371); // kg
	
	symbol mc11 = *sys.new_Parameter("mc11",2.867+0.61855); // kg 
	symbol mc12 = *sys.new_Parameter("mc12",2.867+0.61855); // kg
	symbol mc21 = *sys.new_Parameter("mc21",2.867+0.61855); // kg
	symbol mc22 = *sys.new_Parameter("mc22",2.867+0.61855); // kg
	symbol mc31 = *sys.new_Parameter("mc31",2.867+0.61855); // kg
	symbol mc32 = *sys.new_Parameter("mc32",2.867+0.61855); // kg

	symbol  I_P_11 = *sys.new_Parameter("I_P_11",0.028319+0.0198236017471425); // kg m^2
	symbol  I_P_22 = *sys.new_Parameter("I_P_22",0.028319+0.0198236017471425); // kg m^2
	symbol  I_P_33 = *sys.new_Parameter("I_P_33",0.038045+0.0371130955325733); // kg m^2

	symbol  I_R = *sys.new_Parameter("I_R",0.00013168); // kg m^2

#endif

// Joint Unknown Definition
//

#ifdef STANDARD

#ifdef V_P 
symbol_numeric  Fe11x = *sys.new_Joint_Unknown("Fe11x");
symbol_numeric  Fe11y = *sys.new_Joint_Unknown("Fe11y");
symbol_numeric  Fe11z = *sys.new_Joint_Unknown("Fe11z");

symbol_numeric  Fe12x = *sys.new_Joint_Unknown("Fe12x");
symbol_numeric  Fe12y = *sys.new_Joint_Unknown("Fe12y");
symbol_numeric  Fe12z = *sys.new_Joint_Unknown("Fe12z");

symbol_numeric  Fe21x = *sys.new_Joint_Unknown("Fe21x");
symbol_numeric  Fe21y = *sys.new_Joint_Unknown("Fe21y");
symbol_numeric  Fe21z = *sys.new_Joint_Unknown("Fe21z");

symbol_numeric  Fe22x = *sys.new_Joint_Unknown("Fe22x");
symbol_numeric  Fe22y = *sys.new_Joint_Unknown("Fe22y");
symbol_numeric  Fe22z = *sys.new_Joint_Unknown("Fe22z");

symbol_numeric  Fe31x = *sys.new_Joint_Unknown("Fe31x");
symbol_numeric  Fe31y = *sys.new_Joint_Unknown("Fe31y");
symbol_numeric  Fe31z = *sys.new_Joint_Unknown("Fe31z");

symbol_numeric  Fe32x = *sys.new_Joint_Unknown("Fe32x");
symbol_numeric  Fe32y = *sys.new_Joint_Unknown("Fe32y");
symbol_numeric  Fe32z = *sys.new_Joint_Unknown("Fe32z");
#endif

#ifdef LAG
symbol_numeric  lambda11x = *sys.new_Joint_Unknown("lambda11x");
symbol_numeric  lambda11y = *sys.new_Joint_Unknown("lambda11y");
symbol_numeric  lambda11z = *sys.new_Joint_Unknown("lambda11z");

symbol_numeric  lambda12x = *sys.new_Joint_Unknown("lambda12x");
symbol_numeric  lambda12y = *sys.new_Joint_Unknown("lambda12y");
symbol_numeric  lambda12z = *sys.new_Joint_Unknown("lambda12z");

symbol_numeric  lambda21x = *sys.new_Joint_Unknown("lambda21x");
symbol_numeric  lambda21y = *sys.new_Joint_Unknown("lambda21y");
symbol_numeric  lambda21z = *sys.new_Joint_Unknown("lambda21z");

symbol_numeric  lambda22x = *sys.new_Joint_Unknown("lambda22x");
symbol_numeric  lambda22y = *sys.new_Joint_Unknown("lambda22y");
symbol_numeric  lambda22z = *sys.new_Joint_Unknown("lambda22z");

symbol_numeric  lambda31x = *sys.new_Joint_Unknown("lambda31x");
symbol_numeric  lambda31y = *sys.new_Joint_Unknown("lambda31y");
symbol_numeric  lambda31z = *sys.new_Joint_Unknown("lambda31z");

symbol_numeric  lambda32x = *sys.new_Joint_Unknown("lambda32x");
symbol_numeric  lambda32y = *sys.new_Joint_Unknown("lambda32y");
symbol_numeric  lambda32z = *sys.new_Joint_Unknown("lambda32z");
#endif 

#endif 

#ifdef REDUCED
//In the reduced model without bars, the forze that appears in the virtual power equations is
//That aligned with the bar

#ifdef V_P 
symbol_numeric  FeB11 = *sys.new_Joint_Unknown("FeB11");
symbol_numeric  FeB12 = *sys.new_Joint_Unknown("FeB12");
symbol_numeric  FeB21 = *sys.new_Joint_Unknown("FeB21");
symbol_numeric  FeB22 = *sys.new_Joint_Unknown("FeB22");
symbol_numeric  FeB31 = *sys.new_Joint_Unknown("FeB31");
symbol_numeric  FeB32 = *sys.new_Joint_Unknown("FeB32");
#endif

#ifdef LAG
symbol_numeric  lambda11 = *sys.new_Joint_Unknown("lambda11");
symbol_numeric  lambda12 = *sys.new_Joint_Unknown("lambda12");
symbol_numeric  lambda21 = *sys.new_Joint_Unknown("lambda21");
symbol_numeric  lambda22 = *sys.new_Joint_Unknown("lambda22");
symbol_numeric  lambda31 = *sys.new_Joint_Unknown("lambda31");
symbol_numeric  lambda32 = *sys.new_Joint_Unknown("lambda32");
//They are goig to play of lagrange multipliers, for the equations that keep the lenghts
//of the bars constant, then their meaning l^2P=cte, 2*l*dl*lambda=real_force *dl,
// lambda=real_forze/2*l.
#endif 

#endif 

// kinematics: Points G, Position Vector, abs.vel, abs.accel, abs.angular vel.
// ------------------------------------------------------------------------------------------------
// Vector que va desde Op origen referencia plataforma hasta c.g. plataforma.
	Vector3D OpGp 	= *sys.new_Vector3D("OpGp"	,0,0,mzp/mp		,"Base3");

// Vector que va desde B11 origen referencia plataforma hasta c.g. barra. Idem paratodo Bij
#ifdef STANDARD
	Vector3D B11G11 = *sys.new_Vector3D("B11G11",0,0,mz11/m11	,"Bb11"); 	
	Vector3D B12G12 = *sys.new_Vector3D("B12G12",0,0,mz12/m12	,"Bb12"); 
	Vector3D B21G21 = *sys.new_Vector3D("B21G21",0,0,mz21/m21	,"Bb21");
	Vector3D B22G22 = *sys.new_Vector3D("B22G22",0,0,mz22/m22	,"Bb22");
	Vector3D B31G31 = *sys.new_Vector3D("B31G31",0,0,mz31/m31	,"Bb31");
	Vector3D B32G32 = *sys.new_Vector3D("B32G32",0,0,mz32/m32	,"Bb32");
#endif

#ifdef REDUCED
	Vector3D B11G11 = ex(1/2)*sys.Position_Vector("B11","A11");
	Vector3D B12G12 = ex(1/2)*sys.Position_Vector("B12","A12");
	Vector3D B21G21 = ex(1/2)*sys.Position_Vector("B21","A21");
	Vector3D B22G22 = ex(1/2)*sys.Position_Vector("B22","A22");
	Vector3D B31G31 = ex(1/2)*sys.Position_Vector("B31","A31");
	Vector3D B32G32 = ex(1/2)*sys.Position_Vector("B32","A32");
//WARNING BUG: sys.Position_Vector devuelve vectores, mientras que sys.Position_Vector devuelve punteros
// Habría que homogeneizar el resultado de este tipo de funciones en lib_3dmec
#endif

	Point * Gp 	= sys.new_Point("Gp"	,"Op"		,&OpGp);	
	Point * G11 = sys.new_Point("G11"	,"B11"	,&B11G11);
	Point * G12 = sys.new_Point("G12"	,"B12"	,&B12G12);
	Point * G21 = sys.new_Point("G21"	,"B21"	,&B21G21);
	Point * G22 = sys.new_Point("G22"	,"B22"	,&B22G22);
	Point * G31 = sys.new_Point("G31"	,"B31"	,&B31G31);
	Point * G32 = sys.new_Point("G32"	,"B32"	,&B32G32);

	Vector3D OGp 	= sys.Position_Vector("O"	,"Gp");
	Vector3D OG11 = sys.Position_Vector("O"	,"G11");
	Vector3D OG12 = sys.Position_Vector("O"	,"G12");
	Vector3D OG21 = sys.Position_Vector("O"	,"G21");
	Vector3D OG22 = sys.Position_Vector("O"	,"G22");
	Vector3D OG31 = sys.Position_Vector("O"	,"G31");
	Vector3D OG32 = sys.Position_Vector("O"	,"G32");

	Vector3D VabsOp		= sys.Dt(OOp		,"xyz");
	Vector3D VabsGp		= sys.Dt(OGp		,"xyz");	
	Vector3D VabsG11 	= sys.Dt(OG11		,"xyz");
	Vector3D VabsG12 	= sys.Dt(OG12		,"xyz");
	Vector3D VabsG21 	= sys.Dt(OG21		,"xyz");
	Vector3D VabsG22 	= sys.Dt(OG22		,"xyz");
	Vector3D VabsG31 	= sys.Dt(OG31		,"xyz");
	Vector3D VabsG32 	= sys.Dt(OG32		,"xyz"); 

	Vector3D VabsA11 = sys.Dt(OA11	,"xyz");
	Vector3D VabsA12 = sys.Dt(OA12	,"xyz");
	Vector3D VabsA21 = sys.Dt(OA21	,"xyz");
	Vector3D VabsA22 = sys.Dt(OA22	,"xyz");
	Vector3D VabsA31 = sys.Dt(OA31	,"xyz");
	Vector3D VabsA32 = sys.Dt(OA32	,"xyz");

	Vector3D VabsB11 = sys.Dt(OB11	,"xyz");
	Vector3D VabsB12 = sys.Dt(OB12	,"xyz");
	Vector3D VabsB21 = sys.Dt(OB21	,"xyz");
	Vector3D VabsB22 = sys.Dt(OB22	,"xyz");
	Vector3D VabsB31 = sys.Dt(OB31	,"xyz");
	Vector3D VabsB32 = sys.Dt(OB32	,"xyz");

	Vector3D AabsOp	 = sys.Dt(VabsOp	,"xyz");
	Vector3D AabsGp	 = sys.Dt(VabsGp	,"xyz");	
	Vector3D AabsG11 = sys.Dt(VabsG11	,"xyz");	
	Vector3D AabsG12 = sys.Dt(VabsG12	,"xyz");	
	Vector3D AabsG21 = sys.Dt(VabsG21	,"xyz");	
	Vector3D AabsG22 = sys.Dt(VabsG22	,"xyz");	
	Vector3D AabsG31 = sys.Dt(VabsG31	,"xyz");	
	Vector3D AabsG32 = sys.Dt(VabsG32	,"xyz");

	Vector3D AabsB11 = sys.Dt(VabsB11	,"xyz");
	Vector3D AabsB12 = sys.Dt(VabsB12	,"xyz");
	Vector3D AabsB21 = sys.Dt(VabsB21	,"xyz");
	Vector3D AabsB22 = sys.Dt(VabsB22	,"xyz");
	Vector3D AabsB31 = sys.Dt(VabsB31	,"xyz");
	Vector3D AabsB32 = sys.Dt(VabsB32	,"xyz");

	Vector3D OmP	 = sys.Angular_Velocity("xyz"				,"Base3");
	Vector3D OmR11 = sys.Angular_Velocity("xyz"				,"Br11");
	Vector3D OmR12 = sys.Angular_Velocity("xyz"				,"Br12");
	Vector3D OmR21 = sys.Angular_Velocity("x'y'z'"		,"Br21");
	Vector3D OmR22 = sys.Angular_Velocity("x'y'z'"		,"Br22");
	Vector3D OmR31 = sys.Angular_Velocity("x''y''z''"	,"Br31");
	Vector3D OmR32 = sys.Angular_Velocity("x''y''z''"	,"Br32");

#ifdef STANDARD
	Vector3D VabsA11b = sys.Dt(OA11b	,"xyz");
	Vector3D VabsA12b = sys.Dt(OA12b	,"xyz");
	Vector3D VabsA21b = sys.Dt(OA21b	,"xyz");
	Vector3D VabsA22b = sys.Dt(OA22b	,"xyz");
	Vector3D VabsA31b = sys.Dt(OA31b	,"xyz");
	Vector3D VabsA32b = sys.Dt(OA32b	,"xyz");

	Vector3D OmB11 = sys.Angular_Velocity("xyz"				,"Bb11");
	Vector3D OmB12 = sys.Angular_Velocity("xyz"				,"Bb12");
	Vector3D OmB21 = sys.Angular_Velocity("x'y'z'"		,"Bb21");
	Vector3D OmB22 = sys.Angular_Velocity("x'y'z'"		,"Bb22");
	Vector3D OmB31 = sys.Angular_Velocity("x''y''z''"	,"Bb31");
	Vector3D OmB32 = sys.Angular_Velocity("x''y''z''"	,"Bb32");
#endif

// Inertia
// ------------------------------------------------------------------------------------------------
	Vector3D F_I_P	 = -mp 	* AabsGp;
	Vector3D F_I_B11 = -m11 * AabsG11;
	Vector3D F_I_B12 = -m12 * AabsG12;
	Vector3D F_I_B21 = -m21 * AabsG21;
	Vector3D F_I_B22 = -m22 * AabsG22;
	Vector3D F_I_B31 = -m31 * AabsG31;
	Vector3D F_I_B32 = -m32 * AabsG32;

	Vector3D F_I_C11 = -mc11 * AabsB11;
	Vector3D F_I_C12 = -mc12 * AabsB12;
	Vector3D F_I_C21 = -mc21 * AabsB21;
	Vector3D F_I_C22 = -mc22 * AabsB22;
	Vector3D F_I_C31 = -mc31 * AabsB31;
	Vector3D F_I_C32 = -mc32 * AabsB32;

//Second moments of inertia of bars 1/3 m * l^2 perpendicular to the bar and in the tip
// ------------------------------------------------------------------------------------------------
	Tensor3D  I_P 	= *sys.new_Tensor3D("I_P"		,I_P_11,(ex)0,(ex)0,(ex)0,I_P_22,(ex)0,(ex)0,(ex)0,I_P_33				,"Base3");

	Vector3D H_P	 = I_P 		* OmP;

	Vector3D H_R11 = I_R 		* OmR11;
	Vector3D H_R12 = I_R 		* OmR12;
	Vector3D H_R21 = I_R 		* OmR21;
	Vector3D H_R22 = I_R 		* OmR22;
	Vector3D H_R31 = I_R 		* OmR31;
	Vector3D H_R32 = I_R 		* OmR32;

	Vector3D M_I_P	 = -sys.Dt(H_P ,"xyz")	- mp 	* (sys.Position_Vector(Op,Gp)^AabsOp);

	Vector3D M_I_R11 = -sys.Dt(H_R11,"xyz");
	Vector3D M_I_R12 = -sys.Dt(H_R12,"xyz");
	Vector3D M_I_R21 = -sys.Dt(H_R21,"xyz");
	Vector3D M_I_R22 = -sys.Dt(H_R22,"xyz");
	Vector3D M_I_R31 = -sys.Dt(H_R31,"xyz");
	Vector3D M_I_R32 = -sys.Dt(H_R32,"xyz");

#ifdef STANDARD
	Tensor3D  I_B11 = *sys.new_Tensor3D("I_B11"	,I_B11_11,(ex)0,(ex)0,(ex)0,I_B11_22,(ex)0,(ex)0,(ex)0,I_B11_33	,"Bb11");
	Tensor3D  I_B12 = *sys.new_Tensor3D("I_B12"	,I_B12_11,(ex)0,(ex)0,(ex)0,I_B12_22,(ex)0,(ex)0,(ex)0,I_B12_33	,"Bb12");
	Tensor3D  I_B21 = *sys.new_Tensor3D("I_B21"	,I_B21_11,(ex)0,(ex)0,(ex)0,I_B21_22,(ex)0,(ex)0,(ex)0,I_B21_33	,"Bb21");
	Tensor3D  I_B22 = *sys.new_Tensor3D("I_B22"	,I_B22_11,(ex)0,(ex)0,(ex)0,I_B22_22,(ex)0,(ex)0,(ex)0,I_B22_33	,"Bb22");
	Tensor3D  I_B31 = *sys.new_Tensor3D("I_B31"	,I_B31_11,(ex)0,(ex)0,(ex)0,I_B31_22,(ex)0,(ex)0,(ex)0,I_B31_33	,"Bb31");
	Tensor3D  I_B32 = *sys.new_Tensor3D("I_B32"	,I_B32_11,(ex)0,(ex)0,(ex)0,I_B32_22,(ex)0,(ex)0,(ex)0,I_B32_33	,"Bb32");

	Vector3D H_B11 = I_B11 	* OmB11;
	Vector3D H_B12 = I_B12 	* OmB12;
	Vector3D H_B21 = I_B21 	* OmB21;
	Vector3D H_B22 = I_B22 	* OmB22;
	Vector3D H_B31 = I_B31 	* OmB31;
	Vector3D H_B32 = I_B32 	* OmB32;

	Vector3D M_I_B11 = -sys.Dt(H_B11,"xyz") - m11 * (sys.Position_Vector(B11,G11)^AabsB11);
	Vector3D M_I_B12 = -sys.Dt(H_B12,"xyz") - m12 * (sys.Position_Vector(B12,G12)^AabsB12);
	Vector3D M_I_B21 = -sys.Dt(H_B21,"xyz") - m21 * (sys.Position_Vector(B21,G21)^AabsB21);
	Vector3D M_I_B22 = -sys.Dt(H_B22,"xyz") - m22 * (sys.Position_Vector(B22,G22)^AabsB22);
	Vector3D M_I_B31 = -sys.Dt(H_B31,"xyz") - m31 * (sys.Position_Vector(B31,G31)^AabsB31);
	Vector3D M_I_B32 = -sys.Dt(H_B32,"xyz") - m32 * (sys.Position_Vector(B32,G32)^AabsB32);
#endif

// Vectores de la fuerza de gravedad
// ------------------------------------------------------------------------------------------------
	Vector3D e_z 			= *sys.new_Vector3D("e_z"			,0,0,1					,"xyz");
	Vector3D e_zp 		= *sys.new_Vector3D("e_zp"		,0,0,1					,"x'y'z'");
	Vector3D e_zpp		= *sys.new_Vector3D("e_zpp"		,0,0,1					,"x''y''z''");
	
	Vector3D F_G_P 		= *sys.new_Vector3D("mp*g"		,0,0,-mp * ( * g)		,"xyz");

	Vector3D F_G_B11	= *sys.new_Vector3D("m11*g"		,0,0,-m11 * ( * g)		,"xyz");
	Vector3D F_G_B12 	= *sys.new_Vector3D("m12*g"		,0,0,-m12 * ( * g)		,"xyz");
	Vector3D F_G_B21	= *sys.new_Vector3D("m21*g"		,0,0,-m21 * ( * g)		,"xyz");
	Vector3D F_G_B22 	= *sys.new_Vector3D("m22*g"		,0,0,-m22 * ( * g)		,"xyz");
	Vector3D F_G_B31 	= *sys.new_Vector3D("m31*g"		,0,0,-m31 * ( * g)		,"xyz");
	Vector3D F_G_B32 	= *sys.new_Vector3D("m32*g"		,0,0,-m32 * ( * g)		,"xyz");

	Vector3D F_G_C11 	= *sys.new_Vector3D("mc11*g"	,0,0,-mc11 * ( * g)	,"xyz");
	Vector3D F_G_C12 	= *sys.new_Vector3D("mc12*g"	,0,0,-mc12 * ( * g)	,"xyz");
	Vector3D F_G_C21	= *sys.new_Vector3D("mc21*g"	,0,0,-mc21 * ( * g)	,"xyz");
	Vector3D F_G_C22 	= *sys.new_Vector3D("mc22*g"	,0,0,-mc22 * ( * g)	,"xyz");
	Vector3D F_G_C31	= *sys.new_Vector3D("mc31*g"	,0,0,-mc31 * ( * g)	,"xyz");
	Vector3D F_G_C32 	= *sys.new_Vector3D("mc32*g"	,0,0,-mc32 * ( * g)	,"xyz");

// Vectores fuerzas de enlace
// ------------------------------------------------------------------------------------------------
// Fuerza que ejerce el brazo sobre la plataforma
#ifdef V_P 

#ifdef STANDARD 
	Vector3D Fe11		= *sys.new_Vector3D("Fe11"	,Fe11x,Fe11y,Fe11z	,"Bb11"); 
	Vector3D Fe12		= *sys.new_Vector3D("Fe12"	,Fe12x,Fe12y,Fe12z	,"Bb12");
	Vector3D Fe21		= *sys.new_Vector3D("Fe21"	,Fe21x,Fe21y,Fe21z	,"Bb21");
	Vector3D Fe22		= *sys.new_Vector3D("Fe22"	,Fe22x,Fe22y,Fe22z	,"Bb22");
	Vector3D Fe31		= *sys.new_Vector3D("Fe31"	,Fe31x,Fe31y,Fe31z	,"Bb31");
	Vector3D Fe32		= *sys.new_Vector3D("Fe32"	,Fe32x,Fe32y,Fe32z	,"Bb32");
#endif

#ifdef REDUCED 
	Vector3D Fe11		= (FeB11/l) * sys.Position_Vector("B11","A11");
	Vector3D Fe12		= (FeB12/l) * sys.Position_Vector("B12","A12");
	Vector3D Fe21		= (FeB21/l) * sys.Position_Vector("B21","A21");
	Vector3D Fe22		= (FeB22/l) * sys.Position_Vector("B22","A22");
	Vector3D Fe31		= (FeB31/l) * sys.Position_Vector("B31","A31");
	Vector3D Fe32		= (FeB32/l) * sys.Position_Vector("B32","A32");
#endif

#endif

// Motor Torque:
// ------------------------------------------------------------------------------------------------
/*
	symbol_numeric  Ma11z = *sys.new_Input("Ma11z"	,0.090077*1.0);
	symbol_numeric  Ma12z = *sys.new_Input("Ma12z"	,0.090077*1.0);
	symbol_numeric  Ma21z = *sys.new_Input("Ma21z"	,0.090077*1.0);
	symbol_numeric  Ma22z = *sys.new_Input("Ma22z"	,0.090077*1.0);
	symbol_numeric  Ma31z = *sys.new_Input("Ma31z"	,0.090077*1.0);
	symbol_numeric  Ma32z = *sys.new_Input("Ma32z"	,0.090077*1.0);
*/

	symbol_numeric  Ma11z = *sys.new_Input("Ma11z"	,0.0);
	symbol_numeric  Ma12z = *sys.new_Input("Ma12z"	,0.0);
	symbol_numeric  Ma21z = *sys.new_Input("Ma21z"	,0.0);
	symbol_numeric  Ma22z = *sys.new_Input("Ma22z"	,0.0);
	symbol_numeric  Ma31z = *sys.new_Input("Ma31z"	,0.0);
	symbol_numeric  Ma32z = *sys.new_Input("Ma32z"	,0.0);

	Vector3D Ma11 = *sys.new_Vector3D("Ma11"	,0,0,Ma11z	,"xyz");	
	Vector3D Ma12 = *sys.new_Vector3D("Ma12"	,0,0,Ma12z	,"xyz");	
	Vector3D Ma21 = *sys.new_Vector3D("Ma21"	,0,0,Ma21z	,"x'y'z'");	
	Vector3D Ma22 = *sys.new_Vector3D("Ma22"	,0,0,Ma22z	,"x'y'z'");	
	Vector3D Ma31 = *sys.new_Vector3D("Ma31"	,0,0,Ma31z	,"x''y''z''");	
	Vector3D Ma32 = *sys.new_Vector3D("Ma32"	,0,0,Ma32z	,"x''y''z''");	

// ************************************************************************************************
// KINEMATIC EQUATIONS
// ************************************************************************************************

#ifdef STANDARD 
Vector3D constr_eq_set_1 = OA11-OA11b;
Vector3D constr_eq_set_2 = OA12-OA12b;
Vector3D constr_eq_set_3 = OA21-OA21b;
Vector3D constr_eq_set_4 = OA22-OA22b;
Vector3D constr_eq_set_5 = OA31-OA31b;
Vector3D constr_eq_set_6 = OA32-OA32b;

Matrix Phi(6,1,&constr_eq_set_1,&constr_eq_set_2,&constr_eq_set_3,&constr_eq_set_4,&constr_eq_set_5,&constr_eq_set_6);
#endif

#ifdef REDUCED 
	ex constr_eq_set_11=atomize_ex(atomize_ex(sys.Position_Vector("B11","A11")*sys.Position_Vector("B11","A11"))-atomize_ex(l*l));
	ex constr_eq_set_12=atomize_ex(atomize_ex(sys.Position_Vector("B12","A12")*sys.Position_Vector("B12","A12"))-atomize_ex(l*l));
	ex constr_eq_set_21=atomize_ex(atomize_ex(sys.Position_Vector("B21","A21")*sys.Position_Vector("B21","A21"))-atomize_ex(l*l));
	ex constr_eq_set_22=atomize_ex(atomize_ex(sys.Position_Vector("B22","A22")*sys.Position_Vector("B22","A22"))-atomize_ex(l*l));
	ex constr_eq_set_31=atomize_ex(atomize_ex(sys.Position_Vector("B31","A31")*sys.Position_Vector("B31","A31"))-atomize_ex(l*l));
	ex constr_eq_set_32=atomize_ex(atomize_ex(sys.Position_Vector("B32","A32")*sys.Position_Vector("B32","A32"))-atomize_ex(l*l));

	Matrix Phi(6,1,&constr_eq_set_11,&constr_eq_set_12,&constr_eq_set_21,&constr_eq_set_22,&constr_eq_set_31,&constr_eq_set_32);
#endif


// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
// DYNAMIC EQUATIONS
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

	Matrix q 					= sys.Coordinates();
	Matrix dq 				= sys.Velocities();
	Matrix ddq 				= sys.Accelerations();
	Matrix epsilon		= sys.Joint_Unknowns();
	Matrix parameters	= sys.Parameters();
	Matrix input 			= sys.Inputs();

// ************************************************************************************************

  vector < symbol_numeric * > Coordinates 		= sys.get_Coordinates();
  vector < symbol_numeric * > Velocities 			= sys.get_Velocities();
  vector < symbol_numeric * > Accelerations		= sys.get_Accelerations();
  vector < symbol_numeric * > Joint_Unknowns 	= sys.get_Joint_Unknowns();
  vector < symbol_numeric * > Parameters 			= sys.get_Parameters();
  vector < symbol_numeric * > Inputs		 			= sys.get_Inputs();


// ************************************************************************************************
// Dynamic equations
// ************************************************************************************************
Matrix Dynamic_Equations(dq.rows(),1);

for (int i=0; (i < dq.rows()); ++i) {

	symbol_numeric dq_i;
	dq_i=ex_to<symbol_numeric>(dq(i,0));

	Dynamic_Equations (i,0) = 

  F_I_P  	* sys.diff(VabsOp		,dq_i) + M_I_P	 * sys.diff(OmP		,dq_i) 
+ F_I_B11 * sys.diff(VabsB11	,dq_i)
+ F_I_B12 * sys.diff(VabsB12	,dq_i)
+ F_I_B21 * sys.diff(VabsB21	,dq_i)
+ F_I_B22 * sys.diff(VabsB22	,dq_i)
+ F_I_B31 * sys.diff(VabsB31	,dq_i)
+ F_I_B32 * sys.diff(VabsB32	,dq_i)

#ifdef STANDARD
+ M_I_B11 * sys.diff(OmB11	,dq_i)
+ M_I_B12 * sys.diff(OmB12	,dq_i)
+ M_I_B21 * sys.diff(OmB21	,dq_i)
+ M_I_B22 * sys.diff(OmB22	,dq_i)
+ M_I_B31 * sys.diff(OmB31	,dq_i)
+ M_I_B32 * sys.diff(OmB32	,dq_i)
#endif

+ F_I_C11 * sys.diff(VabsB11	,dq_i) 
+ F_I_C12 * sys.diff(VabsB12	,dq_i) 
+ F_I_C21 * sys.diff(VabsB21	,dq_i)
+ F_I_C22 * sys.diff(VabsB22	,dq_i)
+ F_I_C31 * sys.diff(VabsB31	,dq_i)
+ F_I_C32 * sys.diff(VabsB32	,dq_i)

+ M_I_R11 * sys.diff(OmR11	,dq_i)
+ M_I_R12 * sys.diff(OmR12	,dq_i)
+ M_I_R21 * sys.diff(OmR21	,dq_i)
+ M_I_R22 * sys.diff(OmR22	,dq_i)
+ M_I_R31 * sys.diff(OmR31	,dq_i)
+ M_I_R32 * sys.diff(OmR32	,dq_i)

+ Ma11 * sys.diff(OmR11	,dq_i) 
+ Ma12 * sys.diff(OmR12	,dq_i) 
+ Ma21 * sys.diff(OmR21	,dq_i) 
+ Ma22 * sys.diff(OmR22	,dq_i) 
+ Ma31 * sys.diff(OmR31	,dq_i) 
+ Ma32 * sys.diff(OmR32	,dq_i)

+ F_G_P 	* sys.diff(VabsGp		,dq_i) 
+ F_G_B11 * sys.diff(VabsG11	,dq_i) 
+ F_G_B12 * sys.diff(VabsG12	,dq_i) 
+ F_G_B21 * sys.diff(VabsG21	,dq_i) 
+ F_G_B22 * sys.diff(VabsG22	,dq_i) 
+ F_G_B31 * sys.diff(VabsG31	,dq_i) 
+ F_G_B32 * sys.diff(VabsG32	,dq_i)

+ F_G_C11 * sys.diff(VabsB11	,dq_i) 
+ F_G_C12 * sys.diff(VabsB12	,dq_i) 
+ F_G_C21 * sys.diff(VabsB21	,dq_i) 
+ F_G_C22 * sys.diff(VabsB22	,dq_i) 
+ F_G_C31 * sys.diff(VabsB31	,dq_i) 
+ F_G_C32 * sys.diff(VabsB32	,dq_i)

//Faltan los contrapesos, aportan inercia al movimiento de los carros, y restan a la gravedad.

#ifdef V_P

	#ifdef STANDARD
	+ Fe11 * sys.diff(VabsA11b	,dq_i) - Fe11 * sys.diff(VabsA11	,dq_i)
	+ Fe12 * sys.diff(VabsA12b	,dq_i) - Fe12 * sys.diff(VabsA12	,dq_i) 
	+ Fe21 * sys.diff(VabsA21b	,dq_i) - Fe21 * sys.diff(VabsA21	,dq_i) 
	+ Fe22 * sys.diff(VabsA22b	,dq_i) - Fe22 * sys.diff(VabsA22	,dq_i) 
	+ Fe31 * sys.diff(VabsA31b	,dq_i) - Fe31 * sys.diff(VabsA31	,dq_i) 
	+ Fe32 * sys.diff(VabsA32b	,dq_i) - Fe32 * sys.diff(VabsA32	,dq_i)
	#endif

	#ifdef REDUCED
	+ Fe11 * sys.diff(VabsB11	,dq_i) - Fe11 * sys.diff(VabsA11	,dq_i)
	+ Fe12 * sys.diff(VabsB12	,dq_i) - Fe12 * sys.diff(VabsA12	,dq_i) 
	+ Fe21 * sys.diff(VabsB21	,dq_i) - Fe21 * sys.diff(VabsA21	,dq_i) 
	+ Fe22 * sys.diff(VabsB22	,dq_i) - Fe22 * sys.diff(VabsA22	,dq_i) 
	+ Fe31 * sys.diff(VabsB31	,dq_i) - Fe31 * sys.diff(VabsA31	,dq_i) 
	+ Fe32 * sys.diff(VabsB32	,dq_i) - Fe32 * sys.diff(VabsA32	,dq_i)
	// Preguntar a Javier
	// Caso STANDARD ===> + Fe11 * sys.diff(VabsA11b	,dq_i) - Fe11 * sys.diff(VabsA11	,dq_i)
	// Cuidado, interpretar BIEN sentifo de Fe..... en la situacion REDUCED
	#endif

#endif

+ (-c11)*(*dz11) * e_z		*sys.diff(VabsB11	,dq_i)
+ (-c12)*(*dz12) * e_z		*sys.diff(VabsB12	,dq_i)
+ (-c21)*(*dz21) * e_zp		*sys.diff(VabsB21	,dq_i)
+ (-c22)*(*dz22) * e_zp		*sys.diff(VabsB22	,dq_i)
+ (-c31)*(*dz31) * e_zpp	*sys.diff(VabsB31	,dq_i)
+ (-c32)*(*dz32) * e_zpp	*sys.diff(VabsB32	,dq_i);

// Stil No Friction
// +Fr1*sys.diff(VabsB1,dq_i) +Fr2*sys.diff(VabsB2,dq_i) +Fr3*sys.diff(VabsB3,dq_i)
// +Fr4*sys.diff(VabsB4,dq_i) +Fr5*sys.diff(VabsB5,dq_i) +Fr6*sys.diff(VabsB6,dq_i)

}


#ifdef LAG
for (int i=0; (i < dq.rows()); ++i) {

	symbol_numeric dq_i;
	dq_i=ex_to<symbol_numeric>(dq(i,0));

	Dynamic_Equations (i,0) = Dynamic_Equations (i,0);
/*
	#ifdef STANDARD
	+ lambda11x * Phi_q(0,i)  + lambda11y * Phi_q(1,i)  + lambda11z * Phi_q(2,i)
	+ lambda12x * Phi_q(3,i)  + lambda12y * Phi_q(4,i)  + lambda12z * Phi_q(5,i)
	+ lambda21x * Phi_q(6,i)  + lambda21y * Phi_q(7,i)  + lambda21z * Phi_q(8,i)
	+ lambda22x * Phi_q(9,i) 	+ lambda22y * Phi_q(10,i) + lambda22z * Phi_q(11,i)
	+ lambda31x * Phi_q(12,i) + lambda31y * Phi_q(13,i) + lambda31z * Phi_q(14,i)
	+ lambda32x * Phi_q(15,i) + lambda32y * Phi_q(16,i) + lambda32z * Phi_q(17,i)	;
	#endif

	#ifdef REDUCED
	+ lambda11 * Phi_q(0,i)
	+ lambda12 * Phi_q(1,i)
	+ lambda21 * Phi_q(2,i)
	+ lambda22 * Phi_q(3,i)
	+ lambda31 * Phi_q(4,i)
	+ lambda32 * Phi_q(5,i);
	#endif
*/
}
#endif

// ************************************************************************************************
// Output Vector
// ************************************************************************************************

    cout << "Output Vector" << endl;
    Vector3D ez = *sys.new_Vector3D("ez",0,0,1,"xyz");

    ex Total_Energy = 0.0;

    Matrix Output(Coordinates.size()+Velocities.size()+Joint_Unknowns.size()+1,1);
    for (int i=0; (i < Coordinates.size());    ++i){Output(i,0)=*Coordinates[i];}
    for (int i=0; (i < Velocities.size());     ++i){Output(Coordinates.size()+i,0)=*Velocities[i];}
    for (int i=0; (i < Joint_Unknowns.size()); ++i){Output(Coordinates.size()+Velocities.size()+i,0)=*Joint_Unknowns[i];}

    Output(Coordinates.size()+Velocities.size()+Joint_Unknowns.size(),0) = Total_Energy; //Total_Energy

Matrix Energy(1,1,&Total_Energy );

* sys.new_Matrix("Output",Output );
* sys.new_Matrix("Energy",Energy );

sys.export_Output(sys, ORDER , MAPLE);

// ************************************************************************************************
// MATRIX CALCULATION
// ************************************************************************************************
//# define PROBLEM_TYPE "Q"
//# define PROBLEM_TYPE "Z"
//# define PROBLEM_TYPE "I3AL_Q"
//# define PROBLEM_TYPE "I3AL_Z"
//# define PROBLEM_TYPE "ALL"

#ifndef PROBLEM_TYPE
	#define PROBLEM_TYPE "ALL"
#endif

cout << "Matrix Calculation" << endl;
sys.Matrix_Calculation(Phi, coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);
// ************************************************************************************************
// Export C code for Direct Simulation 
// ************************************************************************************************
cout << "Export C code for Direct Simulation" << endl;
sys.export_Dynamic_Simulation                       (sys, ORDER , MAPLE, PROBLEM_TYPE);
// ************************************************************************************************

#ifdef STANDARD
	lst wite_list;
	wite_list =	l,				lp,					pi,					alpha,		e,					lb,						h,
							x,				*dx,				*ddx,				y,				*dy,				*ddy,					z,				*dz,				*ddz,
							phi,			*dphi,			*ddphi,			theta,		*dtheta,		*ddtheta,			psi,			*dpsi,			*ddpsi,
							z11,			*dz11,			*ddz11,			z12,			*dz12,			*ddz12,
							z21,			*dz21,			*ddz21,			z22,			*dz22,			*ddz22,
							z31,			*dz31,			*ddz31,			z32,			*dz32,			*ddz32,
							phi11,		*dphi11,		*ddphi11,		phi12,		*dphi12,		*ddphi12,
							phi21,		*dphi21,		*ddphi21,		phi22,		*dphi22,		*ddphi22,
							phi31,		*dphi31,		*ddphi31,		phi32,		*dphi32,		*ddphi32,
							theta11,	*dtheta11,	*ddtheta11,	theta12,	*dtheta12,	*ddtheta12,
							theta21,	*dtheta21,	*ddtheta21,	theta22,	*dtheta22,	*ddtheta22,
							theta31,	*dtheta31,	*ddtheta31,	theta32,	*dtheta32,	*ddtheta32;
#endif

#ifdef REDUCED
	lst wite_list;
	wite_list =	l,				lp,					pi,					alpha,		e,					lb,						h,
							x,				*dx,				*ddx,				y,				*dy,				*ddy,					z,				*dz,				*ddz,
							phi,			*dphi,			*ddphi,			theta,		*dtheta,		*ddtheta,			psi,			*dpsi,			*ddpsi,
							z11,			*dz11,			*ddz11,			z12,			*dz12,			*ddz12,
							z21,			*dz21,			*ddz21,			z22,			*dz22,			*ddz22,
							z31,			*dz31,			*ddz31,			z32,			*dz32,			*ddz32;
#endif
	lst list_q;
//	list_q =		x,y,z,phi,theta,psi,z11,z12,z21,z22,z31,z32;
//	list_q =		x,z,z11,*dx,*dz,*dz11,*ddx,*ddz,*ddz11;		
	list_q =		x,z11,z,*dz11,*dz;
//	list_q =		Ma11z,Ma12z,Ma21z,Ma22z,Ma31z,Ma32z		;

	sys.export_write_data_file_C(list_q);
//	sys.export_write_data_file_H();
// ************************************************************************************************
// ************************************************************************************************
//  Export Point, Base and Frame Diagrams 
// ************************************************************************************************
// ************************************************************************************************

/*---------begin  Graphviz export---------*/
#ifdef GRAPHVIZ 

cout << "GRAPHVIZ defined" << endl;
sys.export_Graphviz_dot (  );

//Generate eps figure
system("dot -Tps   base_diagram.dot -o plain_base_diagram.eps");system("latex base_diagram.tex");system("dvips base_diagram.dvi -o base_diagram.eps");
//Generate figure eps
system("dot -Tps   point_diagram.dot -o plain_point_diagram.eps");system("latex point_diagram.tex");system("dvips point_diagram.dvi -o point_diagram.eps");
//Generate eps figure
system("dot -Tps   frame_diagram.dot -o plain_frame_diagram.eps");system("latex frame_diagram.tex");system("dvips base_diagram.dvi -o base_diagram.eps");

#endif
/*---------end  Graphviz export---------*/

// ************************************************************************************************
/*---------begin write q, dq, ddq, epsilon, parameters to environment.m---------*/
sys.export_environment_m (  );
/*---------end write q, dq, ddq, epsilon, parameters to environment.m---------*/
// ************************************************************************************************
// ************************************************************************************************

// ************************************************************************************************
// Openscenegraph
// ************************************************************************************************
//The solids must be in /solids directory and the name of each solid must be Sol*.3ds (where * is the name of the asociated frame)

cout << "Export OpenSceneGraph files " << endl;
sys.export_open_scene_graph ();
// ************************************************************************************************
// ************************************************************************************************

// ************************************************************************************************
//	Export grphics.gnuplot
// ************************************************************************************************
// ************************************************************************************************

	cout << "Export GNUPLOT file" << endl;
	sys.export_gnuplot ( list_q );
//	sys.export_gnuplot ( state );

// OPTIONS
                                     cout << "" << endl;
                                     cout << "***********************************************" << endl;
                                     cout << "** COMPILED WITH OPTIONS                     **" << endl;
                                     cout << "***********************************************" << endl;
if ( METHOD == LAGRANGE)            {cout << "** Dynamic equations ===> LAGRANGE           **" << endl;	}
else 	if ( METHOD == VIRTUAL_POWER) {cout << "** Dynamic equations ===> VIRTUAL_POWER      **" << endl;	}
if ( ORDER == CMO)                  {cout << "** Matrix Order      ===> CMO                **" << endl;	}
else 	if ( ORDER == RMO)            {cout << "** Matrix Order      ===> RMO                **" << endl;	}
if ( MAPLE == MAPLE_OFF)            {cout << "** Maple             ===> OFF                **" << endl;	}
else 	if ( MAPLE == MAPLE_ON)       {cout << "** Maple             ===> ON                 **" << endl;	}
//if ( COORD == STANDARD)             {cout << "** Coord             ===> STANDARD           **" << endl;	}
//else 	if ( COORD == REDUCED)        {cout << "** Coord             ===> REDUCED            **" << endl;	}
                                     cout << "***********************************************" << endl;
                                     cout << "** OTHER OPTIONS                             **" << endl;
                                     cout << "***********************************************" << endl;
#ifdef SLIP           
                                     cout << "** SLIP IN CONTACT POINT WHEEL-ROAD          **" << endl;
#endif
#ifndef SLIP
                                     cout << "** ROLLING IN CONTACT POINT WHEEL-ROAD       **" << endl;
#endif
                                     cout << "***********************************************" << endl;
                                     cout << "" << endl;
// ************************************************************************************************
#ifdef RELEASE_1
	sys.export_write_state_file_header_C(list_q);
	sys.export_write_state_file_C(list_q);

	sys.export_var_def_H();
	sys.export_var_init_C();
	sys.export_var_def_C();

	sys.export_gen_coord_vect_def_H();
	sys.export_gen_coord_vect_init_C();

	sys.export_gen_vel_vect_def_H();
	sys.export_gen_vel_vect_init_C();

	sys.export_gen_accel_vect_def_H();
	sys.export_gen_accel_vect_init_C();

	sys.export_param_vect_def_H();
	sys.export_param_vect_init_C();

	sys.export_inputs_vect_def_H();
	sys.export_inputs_vect_init_C();

	sys.export_unknowns_vect_def_H();
	sys.export_unknowns_vect_init_C();
#endif
return 0;

}



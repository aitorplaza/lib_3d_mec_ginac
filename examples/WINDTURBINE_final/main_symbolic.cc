#include <fstream>
#include "lib_3d_mec_ginac/lib_3d_mec_ginac.h"
#include <ginac/ginac.h>
#include <sstream>

// If ALIGNED is defined the LSS and the HSS are aligned
// If ALIGNED is NOT defined, the LSS and the HSS are NOT aligned and lengths as L4y and L4z are NOT zero.
// #define ALIGNED

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

// ------------------------------------------------------------------------------------------------
cout << " " << endl;
cout << "************************************************" << endl;
cout << "*             Wind_turbine 8.9                 *" << endl;
cout << "************************************************" << endl;
cout << " " << endl;
system("date");
cout << " " << endl;
// ------------------------------------------------------------------------------------------------

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

double integration_time=strtod(argv[1], NULL);
    double delta_t= strtod(argv[2], NULL);
    long int k,steps;


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//System definition
    System sys(&printError2);

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//Coordinate definition

    // The names of the coordinates will be defined as follows:
    // xi,yi,zi,ai,bi,ci for the 3 relative translations and 3 relative rotations
    // of solid i w.r.t. a previous solid j (j<i)


//  Independent
// ------------------------------------------------------------------------------------------------
//  // solid 1
//  symbol_numeric x1 = *sys.new_Coordinate("x1","dx1","ddx1", 0,0,0);
//  symbol_numeric y1 = *sys.new_Coordinate("y1","dy1","ddy1", 0,0,0);
//  symbol_numeric z1 = *sys.new_Coordinate("z1","dz1","ddz1", 0,0,0);
//  symbol_numeric a1 = *sys.new_Coordinate("a1","da1","dda1", 0,0,0);
//  symbol_numeric b1 = *sys.new_Coordinate("b1","db1","ddb1", 0,0,0);
//  symbol_numeric c1 = *sys.new_Coordinate("c1","dc1","ddc1", 0,0,0);

    // solid 2
    symbol_numeric x2 = *sys.new_Coordinate("x2","dx2","ddx2", 0,0,0);
    symbol_numeric y2 = *sys.new_Coordinate("y2","dy2","ddy2", 0,0,0);
//  symbol_numeric z2 = *sys.new_Coordinate("z2","dz2","ddz2", 0,0,0);
//  symbol_numeric a2 = *sys.new_Coordinate("a2","da2","dda2", 0,0,0);
//  symbol_numeric b2 = *sys.new_Coordinate("b2","db2","ddb2", 0,0,0);
    symbol_numeric c2 = *sys.new_Coordinate("c2","dc2","ddc2", 0,0,0);

    // solid 3
    symbol_numeric x3 = *sys.new_Coordinate("x3","dx3","ddx3", 0,0,0);
    symbol_numeric y3 = *sys.new_Coordinate("y3","dy3","ddy3", 0,0,0);
    symbol_numeric z3 = *sys.new_Coordinate("z3","dz3","ddz3", 0,0,0);
    symbol_numeric a3 = *sys.new_Coordinate("a3","da3","dda3", 0,0,0);
    symbol_numeric b3 = *sys.new_Coordinate("b3","db3","ddb3", 0,0,0);
    symbol_numeric c3 = *sys.new_Coordinate("c3","dc3","ddc3", 0,0,0);

    // solid 4
    symbol_numeric x4 = *sys.new_Coordinate("x4","dx4","ddx4", 0,0,0);
    symbol_numeric y4 = *sys.new_Coordinate("y4","dy4","ddy4", 0,0,0);
    symbol_numeric z4 = *sys.new_Coordinate("z4","dz4","ddz4", 0,0,0);
    symbol_numeric a4 = *sys.new_Coordinate("a4","da4","dda4", 0,0,0);
    symbol_numeric b4 = *sys.new_Coordinate("b4","db4","ddb4", 0,0,0);
    symbol_numeric c4 = *sys.new_Coordinate("c4","dc4","ddc4", 0,0,0);

    // solid 5
    symbol_numeric x5 = *sys.new_Coordinate("x5","dx5","ddx5", 0,0,0);
    symbol_numeric y5 = *sys.new_Coordinate("y5","dy5","ddy5", 0,0,0);
    symbol_numeric z5 = *sys.new_Coordinate("z5","dz5","ddz5", 0,0,0);
    //symbol_numeric a5 = *sys.new_Coordinate("a5","da5","dda5", 0,0,0);
    symbol_numeric b5 = *sys.new_Coordinate("b5","db5","ddb5", 0,0,0);
    symbol_numeric c5 = *sys.new_Coordinate("c5","dc5","ddc5", 0,0,0);
 
    // solid 6
//  symbol_numeric x6 = *sys.new_Coordinate("x6","dx6","ddx6", 0,0,0);
//  symbol_numeric y6 = *sys.new_Coordinate("y6","dy6","ddy6", 0,0,0);
//  symbol_numeric z6 = *sys.new_Coordinate("z6","dz6","ddz6", 0,0,0);
    symbol_numeric a6 = *sys.new_Coordinate("a6","da6","dda6", 0,0,0);
    symbol_numeric b6 = *sys.new_Coordinate("b6","db6","ddb6", 0,0,0);
    symbol_numeric c6 = *sys.new_Coordinate("c6","dc6","ddc6", 0,0,0);

    // solid 7
//  symbol_numeric x7 = *sys.new_Coordinate("x7","dx7","ddx7", 0,0,0);
//  symbol_numeric y7 = *sys.new_Coordinate("y7","dy7","ddy7", 0,0,0);
//  symbol_numeric z7 = *sys.new_Coordinate("z7","dz7","ddz7", 0,0,0);
    symbol_numeric a7 = *sys.new_Coordinate("a7","da7","dda7", 0,0,0);
//  symbol_numeric b7 = *sys.new_Coordinate("b7","db7","ddb7", 0,0,0);
//  symbol_numeric c7 = *sys.new_Coordinate("c7","dc7","ddc7", 0,0,0);


// ------------------------------------------------------------------------------------------------
//GEAR-BOX solids
// ------------------------------------------------------------------------------------------------

//  Gearbox SUN 
    symbol_numeric xSun = *sys.new_Coordinate("xSun","dxSun","ddxSun", 0,0,0);
    symbol_numeric ySun = *sys.new_Coordinate("ySun","dySun","ddySun", 0,0,0);
    symbol_numeric zSun = *sys.new_Coordinate("zSun","dzSun","ddzSun", 0,0,0);
    //symbol_numeric aSun = *sys.new_Coordinate("aSun","daSun","ddaSun", 0,0,0);
    symbol_numeric bSun = *sys.new_Coordinate("bSun","dbSun","ddbSun", 0,0,0);
    symbol_numeric cSun = *sys.new_Coordinate("cSun","dcSun","ddcSun", 0,0,0);
    

  //  Gearbox Planet1
    symbol_numeric xPla1 = *sys.new_Coordinate("xPla1","dxPla1","ddxPla1", 0,0,0);
    symbol_numeric yPla1 = *sys.new_Coordinate("yPla1","dyPla1","ddyPla1", 0,0,0);
    symbol_numeric zPla1 = *sys.new_Coordinate("zPla1","dzPla1","ddzPla1", 0,0,0);
    //symbol_numeric aPla1 = *sys.new_Coordinate("aPla1","daPla1","ddaPla1", 0,0,0);
    symbol_numeric bPla1 = *sys.new_Coordinate("bPla1","dbPla1","ddbPla1", 0,0,0);
    symbol_numeric cPla1 = *sys.new_Coordinate("cPla1","dcPla1","ddcPla1", 0,0,0);  

    //  Gearbox Planet2
    symbol_numeric xPla2 = *sys.new_Coordinate("xPla2","dxPla2","ddxPla2", 0,0,0);
    symbol_numeric yPla2 = *sys.new_Coordinate("yPla2","dyPla2","ddyPla2", 0,0,0);
    symbol_numeric zPla2 = *sys.new_Coordinate("zPla2","dzPla2","ddzPla2", 0,0,0);
    //symbol_numeric aPla2 = *sys.new_Coordinate("aPla2","daPla2","ddaPla2", 0,0,0);
    symbol_numeric bPla2 = *sys.new_Coordinate("bPla2","dbPla2","ddbPla2", 0,0,0);
    symbol_numeric cPla2 = *sys.new_Coordinate("cPla2","dcPla2","ddcPla2", 0,0,0);  
    
    
    //  Gearbox Planet3
    symbol_numeric xPla3 = *sys.new_Coordinate("xPla3","dxPla3","ddxPla3", 0,0,0);
    symbol_numeric yPla3 = *sys.new_Coordinate("yPla3","dyPla3","ddyPla3", 0,0,0);
    symbol_numeric zPla3 = *sys.new_Coordinate("zPla3","dzPla3","ddzPla3", 0,0,0);
    //symbol_numeric aPla3 = *sys.new_Coordinate("aPla3","daPla3","ddaPla3", 0,0,0);
    symbol_numeric bPla3 = *sys.new_Coordinate("bPla3","dbPla3","ddbPla3", 0,0,0);
    symbol_numeric cPla3 = *sys.new_Coordinate("cPla3","dcPla3","ddcPla3", 0,0,0);
    
     //  Gearbox Second Stage
    symbol_numeric xSecSt = *sys.new_Coordinate("xSecSt","dxSecSt","ddxSecSt", 0,0,0);
    symbol_numeric ySecSt = *sys.new_Coordinate("ySecSt","dySecSt","ddySecSt", 0,0,0); 
    symbol_numeric zSecSt = *sys.new_Coordinate("zSecSt","dzSecSt","ddzSecSt", 0,0,0);
    //symbol_numeric aSecSt = *sys.new_Coordinate("aSecSt","daSecSt","ddaSecSt", 0,0,0);
    symbol_numeric bSecSt = *sys.new_Coordinate("bSecSt","dbSecSt","ddbSecSt", 0,0,0);
    symbol_numeric cSecSt = *sys.new_Coordinate("cSecSt","dcSecSt","ddcSecSt", 0,0,0);   
    
//  Dependent
// ------------------------------------------------------------------------------------------------
    symbol_numeric aSun = *sys.new_Coordinate("aSun","daSun","ddaSun", 0,0,0);
    symbol_numeric aPla1 = *sys.new_Coordinate("aPla1","daPla1","ddaPla1", 0,0,0);
    symbol_numeric aPla2 = *sys.new_Coordinate("aPla2","daPla2","ddaPla2", 0,0,0);
    symbol_numeric aPla3 = *sys.new_Coordinate("aPla3","daPla3","ddaPla3", 0,0,0);
    symbol_numeric aSecSt = *sys.new_Coordinate("aSecSt","daSecSt","ddaSecSt", 0,0,0);
    symbol_numeric a5 = *sys.new_Coordinate("a5","da5","dda5", 0,0,0);


// ------------------------------------------------------------------------------------------------
    // Solid 2
    symbol_numeric *dx2=sys.get_Velocity("dx2");    symbol_numeric *dy2=sys.get_Velocity("dy2");
    symbol_numeric *dc2=sys.get_Velocity("dc2");

    // Solid 3
    symbol_numeric *dx3=sys.get_Velocity("dx3");    symbol_numeric *dy3=sys.get_Velocity("dy3");    symbol_numeric *dz3=sys.get_Velocity("dz3");
    symbol_numeric *da3=sys.get_Velocity("da3");    symbol_numeric *db3=sys.get_Velocity("db3");    symbol_numeric *dc3=sys.get_Velocity("dc3");

    // Solid 4
    symbol_numeric *dx4=sys.get_Velocity("dx4");    symbol_numeric *dy4=sys.get_Velocity("dy4");    symbol_numeric *dz4=sys.get_Velocity("dz4");
    symbol_numeric *da4=sys.get_Velocity("da4");    symbol_numeric *db4=sys.get_Velocity("db4");    symbol_numeric *dc4=sys.get_Velocity("dc4");

    // Solid 5
    symbol_numeric *dx5=sys.get_Velocity("dx5");    symbol_numeric *dy5=sys.get_Velocity("dy5");    symbol_numeric *dz5=sys.get_Velocity("dz5");
    symbol_numeric *da5=sys.get_Velocity("da5");    symbol_numeric *db5=sys.get_Velocity("db5");    symbol_numeric *dc5=sys.get_Velocity("dc5");

    // Solid 6
    symbol_numeric *da6=sys.get_Velocity("da6");    symbol_numeric *db6=sys.get_Velocity("db6");    symbol_numeric *dc6=sys.get_Velocity("dc6");

    // Solid 7
    symbol_numeric *da7=sys.get_Velocity("da7");
    
    // Solid Sun
    symbol_numeric *dxSun=sys.get_Velocity("dxSun");    symbol_numeric *dySun=sys.get_Velocity("dySun");    symbol_numeric *dzSun=sys.get_Velocity("dzSun");
    symbol_numeric *daSun=sys.get_Velocity("daSun");    symbol_numeric *dbSun=sys.get_Velocity("dbSun");    symbol_numeric *dcSun=sys.get_Velocity("dcSun");
    
    // Solid Pla1
    symbol_numeric *dxPla1=sys.get_Velocity("dxPla1");    symbol_numeric *dyPla1=sys.get_Velocity("dyPla1");    symbol_numeric *dzPla1=sys.get_Velocity("dzPla1");
    symbol_numeric *daPla1=sys.get_Velocity("daPla1");    symbol_numeric *dbPla1=sys.get_Velocity("dbPla1");    symbol_numeric *dcPla1=sys.get_Velocity("dcPla1");
    
    // Solid Pla2
    symbol_numeric *dxPla2=sys.get_Velocity("dxPla2");    symbol_numeric *dyPla2=sys.get_Velocity("dyPla2");    symbol_numeric *dzPla2=sys.get_Velocity("dzPla2");
    symbol_numeric *daPla2=sys.get_Velocity("daPla2");    symbol_numeric *dbPla2=sys.get_Velocity("dbPla2");    symbol_numeric *dcPla2=sys.get_Velocity("dcPla2");
    
    // Solid Pla3
    symbol_numeric *dxPla3=sys.get_Velocity("dxPla3");    symbol_numeric *dyPla3=sys.get_Velocity("dyPla3");    symbol_numeric *dzPla3=sys.get_Velocity("dzPla3");
    symbol_numeric *daPla3=sys.get_Velocity("daPla3");    symbol_numeric *dbPla3=sys.get_Velocity("dbPla3");    symbol_numeric *dcPla3=sys.get_Velocity("dcPla3");
    
     // Solid SecSt
    symbol_numeric *dxSecSt=sys.get_Velocity("dxSecSt");    symbol_numeric *dySecSt=sys.get_Velocity("dySecSt");    symbol_numeric *dzSecSt=sys.get_Velocity("dzSecSt");
    symbol_numeric *daSecSt=sys.get_Velocity("daSecSt");    symbol_numeric *dbSecSt=sys.get_Velocity("dbSecSt");    symbol_numeric *dcSecSt=sys.get_Velocity("dcSecSt");   
   
    // Solid 2
    symbol_numeric *ddx2=sys.get_Acceleration("ddx2");    symbol_numeric *ddy2=sys.get_Acceleration("ddy2");
    symbol_numeric *ddc2=sys.get_Acceleration("ddc2");

    // Solid 3
    symbol_numeric *ddx3=sys.get_Acceleration("ddx3");    symbol_numeric *ddy3=sys.get_Acceleration("ddy3");    symbol_numeric *ddz3=sys.get_Acceleration("ddz3");
    symbol_numeric *dda3=sys.get_Acceleration("dda3");    symbol_numeric *ddb3=sys.get_Acceleration("ddb3");    symbol_numeric *ddc3=sys.get_Acceleration("ddc3");

    // Solid 4
    symbol_numeric *ddx4=sys.get_Acceleration("ddx4");    symbol_numeric *ddy4=sys.get_Acceleration("ddy4");    symbol_numeric *ddz4=sys.get_Acceleration("ddz4");
    symbol_numeric *dda4=sys.get_Acceleration("dda4");    symbol_numeric *ddb4=sys.get_Acceleration("ddb4");    symbol_numeric *ddc4=sys.get_Acceleration("ddc4");

    // Solid 5
    symbol_numeric *ddx5=sys.get_Acceleration("ddx5");    symbol_numeric *ddy5=sys.get_Acceleration("ddy5");    symbol_numeric *ddz5=sys.get_Acceleration("ddz5");
    symbol_numeric *dda5=sys.get_Acceleration("dda5");    symbol_numeric *ddb5=sys.get_Acceleration("ddb5");    symbol_numeric *ddc5=sys.get_Acceleration("ddc5");

    // Solid 6
    symbol_numeric *dda6=sys.get_Acceleration("dda6");    symbol_numeric *ddb6=sys.get_Acceleration("ddb6");    symbol_numeric *ddc6=sys.get_Acceleration("ddc6");

    // Solid 7
    symbol_numeric *dda7=sys.get_Acceleration("dda7");

    // Solid Sun
    symbol_numeric *ddxSun=sys.get_Acceleration("ddxSun");    symbol_numeric *ddySun=sys.get_Acceleration("ddySun");    symbol_numeric *ddzSun=sys.get_Acceleration("ddzSun");
    symbol_numeric *ddaSun=sys.get_Acceleration("ddaSun");    symbol_numeric *ddbSun=sys.get_Acceleration("ddbSun");    symbol_numeric *ddcSun=sys.get_Acceleration("ddcSun");

    // Solid Pla1
    symbol_numeric *ddxPla1=sys.get_Acceleration("ddxPla1");    symbol_numeric *ddyPla1=sys.get_Acceleration("ddyPla1");    symbol_numeric *ddzPla1=sys.get_Acceleration("ddzPla1");
    symbol_numeric *ddaPla1=sys.get_Acceleration("ddaPla1");    symbol_numeric *ddbPla1=sys.get_Acceleration("ddbPla1");    symbol_numeric *ddcPla1=sys.get_Acceleration("ddcPla1");
        
    // Solid Pla2
    symbol_numeric *ddxPla2=sys.get_Acceleration("ddxPla2");    symbol_numeric *ddyPla2=sys.get_Acceleration("ddyPla2");    symbol_numeric *ddzPla2=sys.get_Acceleration("ddzPla2");
    symbol_numeric *ddaPla2=sys.get_Acceleration("ddaPla2");    symbol_numeric *ddbPla2=sys.get_Acceleration("ddbPla2");    symbol_numeric *ddcPla2=sys.get_Acceleration("ddcPla2");
    
    // Solid Pla3
    symbol_numeric *ddxPla3=sys.get_Acceleration("ddxPla3");    symbol_numeric *ddyPla3=sys.get_Acceleration("ddyPla3");    symbol_numeric *ddzPla3=sys.get_Acceleration("ddzPla3");
    symbol_numeric *ddaPla3=sys.get_Acceleration("ddaPla3");    symbol_numeric *ddbPla3=sys.get_Acceleration("ddbPla3");    symbol_numeric *ddcPla3=sys.get_Acceleration("ddcPla3");
    
     // Solid SecSt
    symbol_numeric *ddxSecSt=sys.get_Acceleration("ddxSecSt");    symbol_numeric *ddySecSt=sys.get_Acceleration("ddySecSt");    symbol_numeric *ddzSecSt=sys.get_Acceleration("ddzSecSt");
    symbol_numeric *ddaSecSt=sys.get_Acceleration("ddaSecSt");    symbol_numeric *ddbSecSt=sys.get_Acceleration("ddbSecSt");    symbol_numeric *ddcSecSt=sys.get_Acceleration("ddcSecSt");   
    


        // Initial positions and velocities

        lst coord_indep_init;
        lst vel_indep_init;

	coord_indep_init = x2,y2,c2,x3,y3,z3,a3,b3,c3,x4,y4,z4,a4,b4,c4,x5,y5,z5,b5,c5,a6,b6,c6,a7,xSun,ySun,zSun,bSun,cSun,xPla1,yPla1,zPla1,bPla1,cPla1,xPla2,yPla2,zPla2,bPla2,cPla2,xPla3,yPla3,zPla3,bPla3,cPla3,xSecSt,ySecSt,zSecSt,bSecSt,cSecSt;
	vel_indep_init	= *dx2,*dy2,*dc2,*dx3,*dy3,*dz3,*da3,*db3,*dc3,*dx4,*dy4,*dz4,*da4,*db4,*dc4,*dx5,*dy5,*dz5,*db5,*dc5,*da6,*db6,*dc6,*da7,*dxSun,*dySun,*dzSun,*dbSun,*dcSun,*dxPla1,*dyPla1,*dzPla1,*dbPla1,*dcPla1,*dxPla2,*dyPla2,*dzPla2,*dbPla2,*dcPla2,*dxPla3,*dyPla3,*dzPla3,*dbPla3,*dcPla3,*dxSecSt,*dySecSt,*dzSecSt,*dbSecSt,*dcSecSt;
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//Kinematical parameter definition

    // Solid 2
    // -------
    // Distance between Origin of the nacelle (O2, at the center of yaw Bearing) and the main Bearing (B1)
    symbol_numeric L2x = *sys.new_Parameter("L2x",1.0);
//  symbol_numeric L2y = *sys.new_Parameter("L2y",3.0);
    symbol_numeric L2z = *sys.new_Parameter("L2z",2.0);

    // Distance between Origin of the nacelle (O2, at the center of yaw Bearing) and the silent-blocks
    // The first group of silent-blocks (the two silent-blocks of the gear-box)
    symbol_numeric LS2x1 = *sys.new_Parameter("LS2x1",1.5);
    symbol_numeric LS2y1 = *sys.new_Parameter("LS2y1",1.0);
    symbol_numeric LS2z1 = *sys.new_Parameter("LS2z1",1.0);

    // The second group of silent-blocks (the four silent-blocks of the generator)
    #ifdef ALIGNED
        symbol_numeric LS2x2 = *sys.new_Parameter("LS2x2",4.0);
        symbol_numeric LS2x3 = *sys.new_Parameter("LS2x3",6.0);
        symbol_numeric LS2y2 = *sys.new_Parameter("LS2y2",1.0);
        symbol_numeric LS2y3 = *sys.new_Parameter("LS2y3",1.0);
        symbol_numeric LS2z2 = *sys.new_Parameter("LS2z2",1.0);
    #else
        symbol_numeric LS2x2 = *sys.new_Parameter("LS2x2",4.0);
        symbol_numeric LS2x3 = *sys.new_Parameter("LS2x3",6.0);
        symbol_numeric LS2y2 = *sys.new_Parameter("LS2y2",1.5);
        symbol_numeric LS2y3 = *sys.new_Parameter("LS2y3",0.5);
        symbol_numeric LS2z2 = *sys.new_Parameter("LS2z2",1.0);
    #endif

    // Distance between Origin of the nacelle (O2, at the center of yaw Bearing)
    // and the Brake point (in the HHS)
    #ifdef ALIGNED
        symbol_numeric LB2x = *sys.new_Parameter("LB2x",2.5);
        symbol_numeric LB2y = *sys.new_Parameter("LB2y",0.5);
        symbol_numeric LB2z = *sys.new_Parameter("LB2z",2.0);
    #else
        symbol_numeric LB2x = *sys.new_Parameter("LB2x",2.5);
        symbol_numeric LB2y = *sys.new_Parameter("LB2y",1.0);
        symbol_numeric LB2z = *sys.new_Parameter("LB2z",2.5);
    #endif

    // Structural Pitch inclination of the Nacell
    symbol_numeric b2 = *sys.new_Parameter("b2",5.0*3.141592654/180);

    // Solid 3
    // -------
    // Distance between main Bearing (B1) and Origin of the Rotor (O3)
    symbol_numeric L3x1 = *sys.new_Parameter("L3x1",2.0);

    // Distance between main Bearing (B1) and connection of LSS to the gear-box (Bearing2)
    symbol_numeric L3x2 = *sys.new_Parameter("L3x2",2.0);

    // Solid 4
    // -------
    // Distance between connection of LSS to the gear-box (O4) and connection of HSS to gear-box (Bearing3)
    #ifdef ALIGNED
        symbol_numeric L4x = *sys.new_Parameter("L4x",1.0);
        symbol_numeric L4y = *sys.new_Parameter("L4y",0.0);
        symbol_numeric L4z = *sys.new_Parameter("L4z",0.0);
    #else
        symbol_numeric L4x = *sys.new_Parameter("L4x",1.0);
        symbol_numeric L4y = *sys.new_Parameter("L4y",0.5);
        symbol_numeric L4z = *sys.new_Parameter("L4z",0.5);
    #endif

    // Distance between connection of LSS to the gear-box (O4) and supporting silent-blocks
    symbol_numeric LS4x = *sys.new_Parameter("LS4x",0.5);   // L4Sx is common for the two silent-blocks
    symbol_numeric LS4y = *sys.new_Parameter("LS4y",1.0);   // L4Sy is the half distance between silent-blocks
    symbol_numeric LS4z = *sys.new_Parameter("LS4z",1.0);   // L4Sz is common for the two silent-blocks

    // Kinematic relationship between the omegas of LSS and HSS: (  OMEGA(HHS) - OMEGA(GEARBOX) = KKIN*(OMEGA(LSS) - OMEGA(GEARBOX))  )
    //symbol_numeric KKIN = *sys.new_Parameter("KKIN",13.0);

    // Solid 5
    // -------
    // Distance from the coupling point of solid 5 (O5) to the connection of HSS to GEAR-BOX (Bearing3S5)
    symbol_numeric L6x = *sys.new_Parameter("L6x",1.0);

    // Distance from the coupling point of solid 5 (O5) to the braking point (FF)
    symbol_numeric LB5x = *sys.new_Parameter("LB5x",0.5);
    symbol_numeric LB5y = *sys.new_Parameter("LB5y",0.5);

    // Solid 6
    // -------

    // Solid 7
    // -------
    // Distance from the coupling point of solid 7 (O7) to the silent-blocks
    symbol_numeric LS7x1 = *sys.new_Parameter("LS7x1",1.0);
    symbol_numeric LS7x2 = *sys.new_Parameter("LS7x2",3.0);
    symbol_numeric LS7y1 = *sys.new_Parameter("LS7y1",1.0);
    symbol_numeric LS7y2 = *sys.new_Parameter("LS7y2",1.0);
    #ifdef ALIGNED
        symbol_numeric LS7z = *sys.new_Parameter("LS7z",1.0);
    #else
        symbol_numeric LS7z = *sys.new_Parameter("LS7z",1.5);
    #endif

    // Gravity constant
    // ----------------
    //symbol_numeric g = *sys.new_Parameter("g",9.8);

    //GearBox Kinematical paremeters
    symbol_numeric LGx1 = *sys.new_Parameter("LGx1",0.25);
    symbol_numeric LGx2 = *sys.new_Parameter("LGx2",0.4);   
    symbol_numeric LGx3 = *sys.new_Parameter("LGx3",0.5);
    symbol_numeric LGx4 = *sys.new_Parameter("LGx4",1.0);
    symbol_numeric LGx5 = *sys.new_Parameter("LGx5",0.5);
    symbol_numeric LGx6 = *sys.new_Parameter("LGx6",1.0);
    symbol_numeric LGx7 = *sys.new_Parameter("LGx7",0.5);  
    symbol_numeric LGx8 = *sys.new_Parameter("LGx8",1.0);//same as L4x    
    
    symbol_numeric LGr1 = *sys.new_Parameter("LGr1",0.25); 
    
    symbol_numeric LGy1 = *sys.new_Parameter("LGy1",0.25);   
    symbol_numeric LGz1 = *sys.new_Parameter("LGz1",0.25);   
      
    symbol_numeric LGy2 = *sys.new_Parameter("LGy2",0.5);//same as L4y
    symbol_numeric LGz2 = *sys.new_Parameter("LGz2",0.5); //same as L4z


    //Teeth number
    symbol_numeric Z_Ring = *sys.new_Parameter("Z_Ring",89);
    symbol_numeric Z_Sun = *sys.new_Parameter("Z_Sun",16);
    symbol_numeric Z_Pla = *sys.new_Parameter("Z_Pla",36);
    symbol_numeric Z_SecSt1 = *sys.new_Parameter("Z_SecSt1",90);//Atached to Sun solid
    symbol_numeric Z_SecSt2 = *sys.new_Parameter("Z_SecSt2",22);//Atached to SecSt solid
    symbol_numeric Z_ThiSt1 = *sys.new_Parameter("Z_ThiSt1",91);//Atached to SecSt solid
    symbol_numeric Z_ThiSt2 = *sys.new_Parameter("Z_ThiSt2",25);//Atached to 5 solid


// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
// ------------------------------------------------ KINEMATICS--------------------------------------
// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------

//Define Bases

    // -----------------------------------------------
    // ORIENTATION OF SOLID 2
    // -----------------------------------------------
    // Rotation of the Nacelle w.r.t. the Tower
    sys.new_Base("B2","xyz",0,0,1, c2);

    // Structural Pitch Rotation of the Nacelle (constant inclination)
    sys.new_Base("B2a","B2",0,1,0, b2);


    // -----------------------------------------------
    // ORIENTATION OF SOLID 3   (Euler Angles YZX)
    // -----------------------------------------------
    // Pitch Rotation of the Rotor axis w.r.t. auxiliary base B2a (Euler Angles YZX)
    sys.new_Base("B3a","B2a",0,1,0, b3);

    // Yaw Rotation of the Rotor axis w.r.t. auxiliary base B3a (Euler Angles YZX)
    sys.new_Base("B3b","B3a",0,0,1, c3);

    // Spin (roll) Rotation of the Rotor axis w.r.t. auxiliary base B3b (Euler Angles YZX)
    sys.new_Base("B3","B3b",1,0,0, a3); // B3 is the base of the LSS


    // -----------------------------------------------
    // ORIENTATION OF SOLID 4   (Euler Angles YZX)
    // -----------------------------------------------
    // Pitch rotation of the gear-box w.r.t. the auxiliary base B2a (Y) (Euler Angles YZX)
    sys.new_Base("B4a","B2a",0,1,0, b4);

    // Yaw rotation of the gear-box w.r.t. the auxiliary base B4a (Z) (Euler Angles YZX)
    sys.new_Base("B4b","B4a",0,0,1, c4);

    // Roll rotation of the gear-box w.r.t. the auxiliary base B4b (X) (Euler Angles YZX)
    sys.new_Base("B4","B4b",1,0,0, a4); // B4 is the base of the Gear-Box


    // -----------------------------------------------
    // ORIENTATION OF SOLID 5   (Euler Angles YZX)
    // -----------------------------------------------
    // Pitch rotation of the HSS w.r.t. the auxiliary base B2a (Y) (Euler Angles YZX)
    sys.new_Base("B5a","B2a",0,1,0, b5);

    // Yaw rotation of the HSS w.r.t. the auxiliary base B5a (Z) (Euler Angles YZX)
    sys.new_Base("B5b","B5a",0,0,1, c5);

    // Spin (roll) rotation of the HSS w.r.t. the auxiliary base B5b (X) (Euler Angles YZX)
    sys.new_Base("B5","B5b",1,0,0, a5); // B5 is the base of the HSS


    // -----------------------------------------------
    // ORIENTATION OF SOLID 6   (Euler Angles YZX)
    // -----------------------------------------------
    // Pitch rotation of the Generator w.r.t. the Nacelle (Y)
    sys.new_Base("B6a","B2a",0,1,0, b6);
    // Yaw rotation of the Generator w.r.t. the Nacelle (Z)
    sys.new_Base("B6b","B6a",0,0,1, c6);
    // Spin (roll) rotation of the Generator w.r.t. the Nacelle (X)
    sys.new_Base("B6","B6b",1,0,0, a6);


    // -----------------------------------------------
    // ORIENTATION OF SOLID 7   (Euler Angles X)
    // -----------------------------------------------
    // Spin (roll) rotation of the Stator w.r.t. the Generator (X)
    sys.new_Base("B7","B6b",1,0,0, a7);

    // -----------------------------------------------
    // ORIENTATION OF GEARBOX SUN   (Euler Angles X)
    // -----------------------------------------------
    // Spin (roll) rotation of the Stator w.r.t. the SUN (X)    

    // Pitch rotation of the  w.r.t. the auxiliary base B4 (Y) (Euler Angles YZX)
    sys.new_Base("BSuna","B4",0,1,0, bSun);
    // Yaw rotation of the Sun gear w.r.t. the auxiliary base BSuna (Z) (Euler Angles YZX)
    sys.new_Base("BSunb","BSuna",0,0,1, cSun);
    // Roll rotation of the Sun gear w.r.t. the auxiliary base BSunb (X) (Euler Angles YZX)
    sys.new_Base("BSun","BSunb",1,0,0, aSun); 

    // -----------------------------------------------
    // ORIENTATION OF GEARBOX PLANETS   (Euler Angles X)
    // -----------------------------------------------
    // Spin (roll) rotation of the Stator w.r.t. the SUN (X)    

    // Pitch rotation of the  w.r.t. the auxiliary base B4 (Y) (Euler Angles YZX)
    sys.new_Base("BPla1a","B3",0,1,0, bPla1);
    // Yaw rotation of the Pla1 gear w.r.t. the auxiliary base BPla1a (Z) (Euler Angles YZX)
    sys.new_Base("BPla1b","BPla1a",0,0,1, cPla1);
    // Roll rotation of the Pla1 gear w.r.t. the auxiliary base BPla1b (X) (Euler Angles YZX)
    sys.new_Base("BPla1","BPla1b",1,0,0, aPla1);
    
    // Pitch rotation of the  w.r.t. the auxiliary base B4 (Y) (Euler Angles YZX)
    sys.new_Base("BPla2a","B3",0,1,0, bPla2);
    // Yaw rotation of the Pla2 gear w.r.t. the auxiliary base BPla2a (Z) (Euler Angles YZX)
    sys.new_Base("BPla2b","BPla2a",0,0,1, cPla2);
    // Roll rotation of the Pla2 gear w.r.t. the auxiliary base BPla2b (X) (Euler Angles YZX)
    sys.new_Base("BPla2","BPla2b",1,0,0, aPla2);
    
    // Pitch rotation of the  w.r.t. the auxiliary base B4 (Y) (Euler Angles YZX)
    sys.new_Base("BPla3a","B3",0,1,0, bPla3);
    // Yaw rotation of the Pla3 gear w.r.t. the auxiliary base BPla3a (Z) (Euler Angles YZX)
    sys.new_Base("BPla3b","BPla3a",0,0,1, cPla3);
    // Roll rotation of the Pla3 gear w.r.t. the auxiliary base BPla3b (X) (Euler Angles YZX)
    sys.new_Base("BPla3","BPla3b",1,0,0, aPla3); 
    
    // -----------------------------------------------
    // ORIENTATION OF GEARBOX SECOND STARGE SOLID   (Euler Angles X)
    // -----------------------------------------------
    // Spin (roll) rotation of the Stator w.r.t. the SecSt (X)    

    // Pitch rotation of the  w.r.t. the auxiliary base B4 (Y) (Euler Angles YZX)
    sys.new_Base("BSecSta","B4",0,1,0, bSecSt);
    // Yaw rotation of the SecSt gear w.r.t. the auxiliary base BSecSta (Z) (Euler Angles YZX)
    sys.new_Base("BSecStb","BSecSta",0,0,1, cSecSt);
    // Roll rotation of the SecSt gear w.r.t. the auxiliary base BSecStb (X) (Euler Angles YZX)
    sys.new_Base("BSecSt","BSecStb",1,0,0, aSecSt);  
    
   
  
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//Define Vectors


    // Vector AA_Bearing goes from (still undefined) point AA to Bearing

    Vector3D OO_O1 = *sys.new_Vector3D("OO_O1",0,0,0,"xyz");
    Vector3D O1_O2 = *sys.new_Vector3D("O1_O2",x2,y2,0,"xyz");
    Vector3D O2_Bearing1S2 = *sys.new_Vector3D("O2_Bearing1S2",-L2x,0,L2z,"B2a");
    Vector3D Bearing1S2_Bearing1S3 = *sys.new_Vector3D("Bearing1S2_Bearing1S3",x3,y3,z3,"B2a");//B2a or B2?
    Vector3D Bearing1S3_O3 = *sys.new_Vector3D("Bearing1S3_O3",0,0,0,"B3");

    Vector3D O3_Bearing2S3 = *sys.new_Vector3D("O3_Bearing2S3",L3x2,0,0,"B3");
    Vector3D Bearing2S3_Bearing2S4 = *sys.new_Vector3D("Bearing2S3_Bearing2S4",x4,y4,z4,"B3");
    Vector3D Bearing2S4_O4 = *sys.new_Vector3D("Bearing2S4_O4",0,0,0,"B4");

    Vector3D O4_SilentBlock1S4  = *sys.new_Vector3D("O4_SilentBlock1S4" ,LS4x,LS4y,-LS4z,"B4");
    Vector3D O4_SilentBlock2S4  = *sys.new_Vector3D("O4_SilentBlock2S4" ,LS4x,-LS4y,-LS4z,"B4");

    Vector3D O4_Bearing3S4 = *sys.new_Vector3D("O4_Bearing3S4",L4x,L4y,L4z,"B4"); 
    Vector3D Bearing3S4_Bearing3S5 = *sys.new_Vector3D("Bearing3S4_Bearing3S5",x5,y5,z5,"B4");
    Vector3D Bearing3S5_O5 = *sys.new_Vector3D("Bearing3S5_O5",0,0,0,"B5");

//  Vector3D O5_O6  = *sys.new_Vector3D("O5_O6" ,x6,y6,z6,"B5");
    Vector3D O5_O6  = *sys.new_Vector3D("O5_O6" ,L6x,0,0,"B5");

    Vector3D O6_O7  = *sys.new_Vector3D("O6_O7" ,0,0,0,"B6");

    Vector3D O7_SilentBlock3S7  = *sys.new_Vector3D("O7_SilentBlock3S7" ,LS7x1, LS7y1,-LS7z,"B7");
    Vector3D O7_SilentBlock4S7  = *sys.new_Vector3D("O7_SilentBlock4S7" ,LS7x1,-LS7y2,-LS7z,"B7");
    Vector3D O7_SilentBlock5S7  = *sys.new_Vector3D("O7_SilentBlock5S7" ,LS7x2, LS7y1,-LS7z,"B7");
    Vector3D O7_SilentBlock6S7  = *sys.new_Vector3D("O7_SilentBlock6S7" ,LS7x2,-LS7y2,-LS7z,"B7");

    // Position vectors of the silent-blocks attached to solid 2
    Vector3D O2_SilentBlock1S2  = *sys.new_Vector3D("O2_SilentBlock1S2" ,LS2x1, LS2y1,LS2z1,"B2a");
    Vector3D O2_SilentBlock2S2  = *sys.new_Vector3D("O2_SilentBlock2S2" ,LS2x1,-LS2y1,LS2z1,"B2a");

    Vector3D O2_SilentBlock3S2  = *sys.new_Vector3D("O2_SilentBlock3S2" ,LS2x2, LS2y2,LS2z2,"B2a");
    Vector3D O2_SilentBlock4S2  = *sys.new_Vector3D("O2_SilentBlock4S2" ,LS2x2,-LS2y3,LS2z2,"B2a");
    Vector3D O2_SilentBlock5S2  = *sys.new_Vector3D("O2_SilentBlock5S2" ,LS2x3, LS2y2,LS2z2,"B2a");
    Vector3D O2_SilentBlock6S2  = *sys.new_Vector3D("O2_SilentBlock6S2" ,LS2x3,-LS2y3,LS2z2,"B2a");

    // Position vector of the Brake location attached to solid 4 and
    // Position vector of the Brake location attached to solid 5
    Vector3D O4_BrakeS4  = *sys.new_Vector3D("O4_BrakeS4" ,L4x+LB5x, L4y+LB5y,L4z,"B2a");
    Vector3D O5_BrakeS5  = *sys.new_Vector3D("O5_BrakeS5" ,LB5x,LB5y,0,"B2a");

    // Position vector of the Sun (Gearbox) location attached to solid 4
    Vector3D O4_GBBearing4S4 = *sys.new_Vector3D("O4_GBBearing4S4",LGx2,0,0,"B4");
    Vector3D O4_GBBearing5S4 = *sys.new_Vector3D("O4_GBBearing5S4",LGx3,0,0,"B4");
    Vector3D O4_GBBearing6S4 = *sys.new_Vector3D("O4_GBBearing6S4",LGx4,0,0,"B4");
    Vector3D GBBearing5S4_GBBearing5Sun = *sys.new_Vector3D("GBBearing5S4_GBBearing5Sun",xSun,ySun,zSun,"B4");
    Vector3D GBBearing5Sun_OSun = *sys.new_Vector3D("GBBearing5Sun_OSun",0,0,0,"BSun"); 
    Vector3D Osun_GBBearing6Sun = *sys.new_Vector3D("Osun_GBBearing6Sun",LGx4-LGx3,0,0,"BSun");  

    // Position vector of the Planets (Gearbox) location attached to solid 3
    Vector3D O3_GBBearing1S3 = *sys.new_Vector3D("O3_GBBearing1S3",L3x2+LGx1,0,LGr1,"B3");
    Vector3D O3_GBBearing2S3 = *sys.new_Vector3D("O3_GBBearing2S3",L3x2+LGx1,LGr1*cos(7*Pi/6),LGr1*sin(7*Pi/6),"B3");
    Vector3D O3_GBBearing3S3 = *sys.new_Vector3D("O3_GBBearing3S3",L3x2+LGx1,LGr1*cos(-Pi/6),LGr1*sin(-Pi/6),"B3");  

    Vector3D GBBearing1S3_GBBearing1Pla1 = *sys.new_Vector3D("GBBearing1S3_GBBearing1Pla1",xPla1,yPla1,zPla1,"B3");
    Vector3D GBBearing2S3_GBBearing2Pla2 = *sys.new_Vector3D("GBBearing2S3_GBBearing2Pla2",xPla2,yPla2,zPla2,"B3");
    Vector3D GBBearing3S3_GBBearing3Pla3 = *sys.new_Vector3D("GBBearing3S3_GBBearing3Pla3",xPla3,yPla3,zPla3,"B3");

    Vector3D GBBearing1Pla1_OPla1 = *sys.new_Vector3D("GBBearing1Pla1_OPla1",0,0,0,"BPla1");
    Vector3D GBBearing2Pla2_OPla2 = *sys.new_Vector3D("GBBearing2Pla2_OPla2",0,0,0,"BPla2");   
    Vector3D GBBearing3Pla3_OPla3 = *sys.new_Vector3D("GBBearing3Pla3_OPla3",0,0,0,"BPla3");  

    Vector3D O3_GBBearing4S3 = *sys.new_Vector3D("O3_GBBearing4S3",L3x2+LGx2,0,0,"B3"); 

    
    // Position vector of the 2nd and 3rd stages (Gearbox) location attached to solid 4
    Vector3D O4_GBBearing7S4 = *sys.new_Vector3D("O4_GBBearing7S4",LGx5,LGy1,LGz1,"B4");
    Vector3D O4_GBBearing8S4 = *sys.new_Vector3D("O4_GBBearing8S4",LGx6,LGy1,LGz1,"B4");
    Vector3D O4_GBBearing9S4 = *sys.new_Vector3D("O4_GBBearing9S4",LGx7,LGy2,LGz2,"B4");
    Vector3D GBBearing7S4_GBBearing7SecSt = *sys.new_Vector3D("GBBearing7S4_GBBearing7SecSt",xSecSt,ySecSt,zSecSt,"B4");
    Vector3D GBBearing7SecSt_OSecSt = *sys.new_Vector3D("GBBearing7SecSt_OSecSt",0,0,0,"BSecSt"); 
    Vector3D OSecSt_GBBearing8SecSt = *sys.new_Vector3D("OSecSt_GBBearing8SecSt",LGx6-LGx5,0,0,"BSecSt"); 
    Vector3D O5_GBBearing9S5 = *sys.new_Vector3D("O5_GBBearing9S5",-(L4x-LGx7),0,0,"B5");      
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//Define Points

    Point * O1 = sys.new_Point("O1","O",&OO_O1);
    Point * O2 = sys.new_Point("O2","O1",&O1_O2);
    
    Point * Bearing1S2 = sys.new_Point("Bearing1S2","O2",&O2_Bearing1S2);
    Point * Bearing1S3 = sys.new_Point("Bearing1S3","Bearing1S2",&Bearing1S2_Bearing1S3);
    Point * O3 = sys.new_Point("O3","Bearing1S3",&Bearing1S3_O3);

    Point * Bearing2S3 = sys.new_Point("Bearing2S3","O3",&O3_Bearing2S3);
    Point * Bearing2S4 = sys.new_Point("Bearing2S4","Bearing2S3",&Bearing2S3_Bearing2S4);
    Point * O4 = sys.new_Point("O4","Bearing2S4",&Bearing2S4_O4);


    //Point * Bearing2S3 = sys.new_Point("Bearing2S3","Bearing1S2",&Bearing1_Bearing2S3);
    //Point * O4 = sys.new_Point("O4","Bearing2S3",&Bearing2S3_O4);

    Point * Bearing3S4 = sys.new_Point("Bearing3S4","O4",&O4_Bearing3S4);  //same as GBearing10
    Point * Bearing3S5 = sys.new_Point("Bearing3S5","Bearing3S4",&Bearing3S4_Bearing3S5);
    Point * O5 = sys.new_Point("O5","Bearing3S5",&Bearing3S5_O5);
    Point * O6 = sys.new_Point("O6","O5",&O5_O6);
    Point * O7 = sys.new_Point("O7","O6",&O6_O7);

    // Silent-block positions w.r.t. Gear-Box and Stator solids
    Point * SilentBlock1S4 = sys.new_Point("SilentBlock1S4","O4",&O4_SilentBlock1S4);
    Point * SilentBlock2S4 = sys.new_Point("SilentBlock2S4","O4",&O4_SilentBlock2S4);

    Point * SilentBlock3S7 = sys.new_Point("SilentBlock3S7","O7",&O7_SilentBlock3S7);
    Point * SilentBlock4S7 = sys.new_Point("SilentBlock4S7","O7",&O7_SilentBlock4S7);
    Point * SilentBlock5S7 = sys.new_Point("SilentBlock5S7","O7",&O7_SilentBlock5S7);
    Point * SilentBlock6S7 = sys.new_Point("SilentBlock6S7","O7",&O7_SilentBlock6S7);

    // Silent-blocks positions w.r.t. Nacelle solid
    Point * SilentBlock1S2 = sys.new_Point("SilentBlock1S2","O2",&O2_SilentBlock1S2);
    Point * SilentBlock2S2 = sys.new_Point("SilentBlock2S2","O2",&O2_SilentBlock2S2);
    Point * SilentBlock3S2 = sys.new_Point("SilentBlock3S2","O2",&O2_SilentBlock3S2);
    Point * SilentBlock4S2 = sys.new_Point("SilentBlock4S2","O2",&O2_SilentBlock4S2);
    Point * SilentBlock5S2 = sys.new_Point("SilentBlock5S2","O2",&O2_SilentBlock5S2);
    Point * SilentBlock6S2 = sys.new_Point("SilentBlock6S2","O2",&O2_SilentBlock6S2);

    // Brakes
    Point * BrakeS4 = sys.new_Point("BrakeS4","O4",&O4_BrakeS4);
    Point * BrakeS5 = sys.new_Point("BrakeS5","O5",&O5_BrakeS5);

    //GearBox
    Point * GBBearing4S3 = sys.new_Point("GBBearing4S3","O3",&O3_GBBearing4S3);//attached to solid 3
    Point * GBBearing4S4 = sys.new_Point("GBBearing4S4","O4",&O4_GBBearing4S4);
    Point * GBBearing5S4 = sys.new_Point("GBBearing5S4","O4",&O4_GBBearing5S4);
    Point * GBBearing6S4 = sys.new_Point("GBBearing6S4","O4",&O4_GBBearing6S4);
    
    // Sun
    Point * GBBearing5Sun = sys.new_Point("GBBearing5Sun","GBBearing5S4",&GBBearing5S4_GBBearing5Sun);
    Point * OSun = sys.new_Point("OSun","GBBearing5Sun",&GBBearing5Sun_OSun);    
    Point * GBBearing6Sun = sys.new_Point("GBBearing6Sun","OSun",&Osun_GBBearing6Sun);

    //Planets
    Point * GBBearing1S3 = sys.new_Point("GBBearing1S3","O3",&O3_GBBearing1S3);
    Point * GBBearing2S3 = sys.new_Point("GBBearing2S3","O3",&O3_GBBearing2S3);
    Point * GBBearing3S3 = sys.new_Point("GBBearing3S3","O3",&O3_GBBearing3S3);
    Point * GBBearing1Pla1 = sys.new_Point("GBBearing1Pla1","GBBearing1S3",&GBBearing1S3_GBBearing1Pla1);  
    Point * GBBearing2Pla2 = sys.new_Point("GBBearing2Pla2","GBBearing2S3",&GBBearing2S3_GBBearing2Pla2);   
    Point * GBBearing3Pla3 = sys.new_Point("GBBearing3Pla3","GBBearing3S3",&GBBearing3S3_GBBearing3Pla3);
    Point * OPla1 = sys.new_Point("OPla1","GBBearing1Pla1",&GBBearing1Pla1_OPla1); 
    Point * OPla2 = sys.new_Point("OPla2","GBBearing2Pla2",&GBBearing2Pla2_OPla2);     
    Point * OPla3 = sys.new_Point("OPla3","GBBearing3Pla3",&GBBearing3Pla3_OPla3);   
    
    //Second Stage
    Point * GBBearing7S4 = sys.new_Point("GBBearing7S4","O4",&O4_GBBearing7S4);
    Point * GBBearing8S4 = sys.new_Point("GBBearing8S4","O4",&O4_GBBearing8S4);
    Point * GBBearing7SecSt = sys.new_Point("GBBearing7SecSt","GBBearing7S4",&GBBearing7S4_GBBearing7SecSt);
    Point * OSecSt = sys.new_Point("OSecSt","GBBearing7SecSt",&GBBearing7SecSt_OSecSt);    
    Point * GBBearing8SecSt = sys.new_Point("GBBearing8SecSt","OSecSt",&OSecSt_GBBearing8SecSt);   
  
    //Third Stage
    Point * GBBearing9S4 = sys.new_Point("GBBearing9S4","O4",&O4_GBBearing9S4);
    Point * GBBearing9S5 = sys.new_Point("GBBearing9S5","O5",&O5_GBBearing9S5);

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//  Define position vectors
//  Vector3D OO_O1 = sys.Position_Vector("O","O1");
    Vector3D OO_O2 = sys.Position_Vector("O","O2");
    Vector3D OO_O3 = sys.Position_Vector("O","O3");
    Vector3D OO_O4 = sys.Position_Vector("O","O4");
    Vector3D OO_O5 = sys.Position_Vector("O","O5");
    Vector3D OO_O6 = sys.Position_Vector("O","O6");
    Vector3D OO_O7 = sys.Position_Vector("O","O7");
    Vector3D OO_OSun = sys.Position_Vector("O","OSun");
    Vector3D OO_OPla1 = sys.Position_Vector("O","OPla1");  
    Vector3D OO_OPla2 = sys.Position_Vector("O","OPla2");     
    Vector3D OO_OPla3 = sys.Position_Vector("O","OPla3");    
    Vector3D OO_OSecSt = sys.Position_Vector("O","OSecSt");    

    
    Vector3D OO_Bearing1S2 = sys.Position_Vector("O","Bearing1S2");
    Vector3D OO_Bearing1S3 = sys.Position_Vector("O","Bearing1S3");

    Vector3D OO_Bearing2S3 = sys.Position_Vector("O","Bearing2S3");
    Vector3D OO_Bearing2S4 = sys.Position_Vector("O","Bearing2S4");
    
    Vector3D OO_Bearing3S4 = sys.Position_Vector("O","Bearing3S4");
    Vector3D OO_Bearing3S5 = sys.Position_Vector("O","Bearing3S5");

    Vector3D SilentBlock1S4_SilentBlock1S2 = sys.Position_Vector("SilentBlock1S4","SilentBlock1S2");
    Vector3D SilentBlock2S4_SilentBlock2S2 = sys.Position_Vector("SilentBlock2S4","SilentBlock2S2");
    Vector3D SilentBlock3S7_SilentBlock3S2 = sys.Position_Vector("SilentBlock3S7","SilentBlock3S2");
    Vector3D SilentBlock4S7_SilentBlock4S2 = sys.Position_Vector("SilentBlock4S7","SilentBlock4S2");
    Vector3D SilentBlock5S7_SilentBlock5S2 = sys.Position_Vector("SilentBlock5S7","SilentBlock5S2");
    Vector3D SilentBlock6S7_SilentBlock6S2 = sys.Position_Vector("SilentBlock6S7","SilentBlock6S2");

    Vector3D OO_BrakeS5  = sys.Position_Vector("O","BrakeS5" );
    Vector3D OO_BrakeS4  = sys.Position_Vector("O","BrakeS4" );
    Vector3D BrakeS4_BrakeS5 = sys.Position_Vector("BrakeS4","BrakeS5" );


    
    Vector3D OO_GBBearing1S3 = sys.Position_Vector("O","GBBearing1S3");   
    Vector3D OO_GBBearing2S3 = sys.Position_Vector("O","GBBearing2S3");
    Vector3D OO_GBBearing3S3 = sys.Position_Vector("O","GBBearing3S3");
    Vector3D OO_GBBearing4S3 = sys.Position_Vector("O","GBBearing4S3");
    Vector3D OO_GBBearing5S4 = sys.Position_Vector("O","GBBearing5S4");
    Vector3D OO_GBBearing6S4 = sys.Position_Vector("O","GBBearing6S4");
    Vector3D OO_GBBearing7S4 = sys.Position_Vector("O","GBBearing7S4");
    Vector3D OO_GBBearing8S4 = sys.Position_Vector("O","GBBearing8S4");
    Vector3D OO_GBBearing9S4 = sys.Position_Vector("O","GBBearing9S4");


    Vector3D OO_GBBearing1Pla1 = sys.Position_Vector("O","GBBearing1Pla1");  
    Vector3D OO_GBBearing2Pla2 = sys.Position_Vector("O","GBBearing2Pla2");   
    Vector3D OO_GBBearing3Pla3 = sys.Position_Vector("O","GBBearing3Pla3");
    Vector3D OO_GBBearing4S4 = sys.Position_Vector("O","GBBearing4S4");
    Vector3D OO_GBBearing5Sun = sys.Position_Vector("O","GBBearing5Sun");
    Vector3D OO_GBBearing6Sun = sys.Position_Vector("O","GBBearing6Sun");
    Vector3D OO_GBBearing7SecSt = sys.Position_Vector("O","GBBearing7SecSt");
    Vector3D OO_GBBearing8SecSt = sys.Position_Vector("O","GBBearing8SecSt");
    Vector3D OO_GBBearing9S5 = sys.Position_Vector("O","GBBearing9S5");

    Vector3D GBBearing4S3_GBBearing4S4 = sys.Position_Vector("GBBearing4S3","GBBearing4S4");
    Vector3D GBBearing6S4_GBBearing6Sun = sys.Position_Vector("GBBearing6S4","GBBearing6Sun");
    Vector3D GBBearing8S4_GBBearing8SecSt = sys.Position_Vector("GBBearing8S4","GBBearing8SecSt");
    Vector3D GBBearing9S4_GBBearing9S5 = sys.Position_Vector("GBBearing9S4","GBBearing9S5");

//  Define absolute points Velocities
//  Vector3D VabsO1 = sys.Dt(OO_O1,"xyz");
    Vector3D VabsO2 = sys.Dt(OO_O2,"xyz");
    Vector3D VabsO3 = sys.Dt(OO_O3,"xyz");
    Vector3D VabsO4 = sys.Dt(OO_O4,"xyz");
    Vector3D VabsO5 = sys.Dt(OO_O5,"xyz");
    Vector3D VabsO6 = sys.Dt(OO_O6,"xyz");
    Vector3D VabsO7 = sys.Dt(OO_O7,"xyz");
    Vector3D VabsOSun = sys.Dt(OO_OSun,"xyz");
    Vector3D VabsOPla1 = sys.Dt(OO_OPla1,"xyz");  
    Vector3D VabsOPla2 = sys.Dt(OO_OPla2,"xyz");   
    Vector3D VabsOPla3 = sys.Dt(OO_OPla3,"xyz");   
    Vector3D VabsOSecSt = sys.Dt(OO_OSecSt,"xyz");

    Vector3D VabsBearing1S2 = sys.Dt(OO_Bearing1S2,"xyz");
    Vector3D VabsBearing1S3 = sys.Dt(OO_Bearing1S3,"xyz");

    Vector3D VabsBearing2S3 = sys.Dt(OO_Bearing2S3,"xyz");
    Vector3D VabsBearing2S4 = sys.Dt(OO_Bearing2S4,"xyz");

    Vector3D VabsBearing3S4 = sys.Dt(OO_Bearing3S4,"xyz");
    Vector3D VabsBearing3S5 = sys.Dt(OO_Bearing3S5,"xyz");

    Vector3D VrelBearing1S2_Bearing1S3 = sys.Dt(Bearing1S2_Bearing1S3,"B2a");
    Vector3D VrelBearing2S3_Bearing2S4 = sys.Dt(Bearing2S3_Bearing2S4,"B3");
    Vector3D VrelBearing3S4_Bearing3S5 = sys.Dt(Bearing3S4_Bearing3S5,"B4");

    Vector3D VrelO1_O2 = sys.Dt(O1_O2,"xyz");

    Vector3D VrelSilentBlock1S4 = sys.Dt(SilentBlock1S4_SilentBlock1S2,"B2a");
    Vector3D VrelSilentBlock2S4 = sys.Dt(SilentBlock2S4_SilentBlock2S2,"B2a");
    Vector3D VrelSilentBlock3S7 = sys.Dt(SilentBlock3S7_SilentBlock3S2,"B2a");
    Vector3D VrelSilentBlock4S7 = sys.Dt(SilentBlock4S7_SilentBlock4S2,"B2a");
    Vector3D VrelSilentBlock5S7 = sys.Dt(SilentBlock5S7_SilentBlock5S2,"B2a");
    Vector3D VrelSilentBlock6S7 = sys.Dt(SilentBlock6S7_SilentBlock6S2,"B2a");

    Vector3D VrelSilentBlock1S4_abs = sys.Dt(SilentBlock1S4_SilentBlock1S2,"xyz");
    Vector3D VrelSilentBlock2S4_abs = sys.Dt(SilentBlock2S4_SilentBlock2S2,"xyz");
    Vector3D VrelSilentBlock3S7_abs = sys.Dt(SilentBlock3S7_SilentBlock3S2,"xyz");
    Vector3D VrelSilentBlock4S7_abs = sys.Dt(SilentBlock4S7_SilentBlock4S2,"xyz");
    Vector3D VrelSilentBlock5S7_abs = sys.Dt(SilentBlock5S7_SilentBlock5S2,"xyz");
    Vector3D VrelSilentBlock6S7_abs = sys.Dt(SilentBlock6S7_SilentBlock6S2,"xyz");


    //Vector3D VabsBrakeS5  = sys.Dt(OO_BrakeS5 ,"xyz");
    //Vector3D VabsBrakeS4  = sys.Dt(OO_BrakeS4 ,"xyz");
    Vector3D VrelBrakeS4_BrakeS5 = sys.Dt(BrakeS4_BrakeS5,"B4");

    
    Vector3D VabsGBBearing1S3 = sys.Dt(OO_GBBearing1S3 ,"xyz");
    Vector3D VabsGBBearing2S3 = sys.Dt(OO_GBBearing2S3 ,"xyz");
    Vector3D VabsGBBearing3S3 = sys.Dt(OO_GBBearing3S3 ,"xyz");
    Vector3D VabsGBBearing4S3 = sys.Dt(OO_GBBearing4S3 ,"xyz");
    Vector3D VabsGBBearing5S4 = sys.Dt(OO_GBBearing5S4 ,"xyz");
    Vector3D VabsGBBearing6S4 = sys.Dt(OO_GBBearing6S4 ,"xyz");
    Vector3D VabsGBBearing7S4 = sys.Dt(OO_GBBearing7S4 ,"xyz");
    Vector3D VabsGBBearing8S4 = sys.Dt(OO_GBBearing8S4 ,"xyz");
    Vector3D VabsGBBearing9S4 = sys.Dt(OO_GBBearing9S4 ,"xyz");
   
    Vector3D VrelGBBearing1S3_GBBearing1Pla1 = sys.Dt(GBBearing1S3_GBBearing1Pla1,"B3");   
    Vector3D VrelGBBearing2S3_GBBearing2Pla2 = sys.Dt(GBBearing2S3_GBBearing2Pla2,"B3");  
    Vector3D VrelGBBearing3S3_GBBearing3Pla3 = sys.Dt(GBBearing3S3_GBBearing3Pla3,"B3"); 
    Vector3D VrelGBBearing4S3_GBBearing4S4 = sys.Dt(GBBearing4S3_GBBearing4S4,"B3");
    Vector3D VrelGBBearing5S4_GBBearing5Sun = sys.Dt(GBBearing5S4_GBBearing5Sun,"B4");
    Vector3D VrelGBBearing6S4_GBBearing6Sun = sys.Dt(GBBearing6S4_GBBearing6Sun,"B4");
    Vector3D VrelGBBearing7S4_GBBearing7SecSt = sys.Dt(GBBearing7S4_GBBearing7SecSt,"B4"); 
    Vector3D VrelGBBearing8S4_GBBearing8SecSt = sys.Dt(GBBearing8S4_GBBearing8SecSt,"B4"); 
    Vector3D VrelGBBearing9S4_GBBearing9S5 = sys.Dt(GBBearing9S4_GBBearing9S5,"B4");   

    Vector3D VrelBearing1S2_Bearing1S3_abs = sys.Dt(Bearing1S2_Bearing1S3,"xyz");
    Vector3D VrelBearing2S3_Bearing2S4_abs = sys.Dt(Bearing2S3_Bearing2S4,"xyz");
    Vector3D VrelBearing3S4_Bearing3S5_abs = sys.Dt(Bearing3S4_Bearing3S5,"xyz");
    Vector3D VrelGBBearing1S3_GBBearing1Pla1_abs = sys.Dt(GBBearing1S3_GBBearing1Pla1,"xyz");
    Vector3D VrelGBBearing2S3_GBBearing2Pla2_abs = sys.Dt(GBBearing2S3_GBBearing2Pla2,"xyz");
    Vector3D VrelGBBearing3S3_GBBearing3Pla3_abs = sys.Dt(GBBearing3S3_GBBearing3Pla3,"xyz");
    Vector3D VrelGBBearing4S3_GBBearing4S4_abs = sys.Dt(GBBearing4S3_GBBearing4S4,"xyz");
    Vector3D VrelGBBearing5S4_GBBearing5Sun_abs = sys.Dt(GBBearing5S4_GBBearing5Sun,"xyz");
    Vector3D VrelGBBearing6S4_GBBearing6Sun_abs = sys.Dt(GBBearing6S4_GBBearing6Sun,"xyz");
    Vector3D VrelGBBearing7S4_GBBearing7SecSt_abs = sys.Dt(GBBearing7S4_GBBearing7SecSt,"xyz");
    Vector3D VrelGBBearing8S4_GBBearing8SecSt_abs = sys.Dt(GBBearing8S4_GBBearing8SecSt,"xyz");
    Vector3D VrelGBBearing9S4_GBBearing9S5_abs = sys.Dt(GBBearing9S4_GBBearing9S5,"xyz");

    Vector3D VabsGBBearing1Pla1 = sys.Dt(OO_GBBearing1Pla1 ,"xyz");
    Vector3D VabsGBBearing2Pla2 = sys.Dt(OO_GBBearing2Pla2 ,"xyz");
    Vector3D VabsGBBearing3Pla3 = sys.Dt(OO_GBBearing3Pla3 ,"xyz");
    Vector3D VabsGBBearing4S4 = sys.Dt(OO_GBBearing4S4 ,"xyz");
    Vector3D VabsGBBearing5Sun = sys.Dt(OO_GBBearing5Sun ,"xyz");
    Vector3D VabsGBBearing6Sun  = sys.Dt(OO_GBBearing6Sun ,"xyz");
    Vector3D VabsGBBearing7SecSt  = sys.Dt(OO_GBBearing7SecSt ,"xyz"); 
    Vector3D VabsGBBearing8SecSt  = sys.Dt(OO_GBBearing8SecSt ,"xyz"); 
    Vector3D VabsGBBearing9S5  = sys.Dt(OO_GBBearing9S5 ,"xyz");

//  Vector3D AabsO1 = sys.Dt(VabsO1,"xyz");
    Vector3D AabsO2 = sys.Dt(VabsO2,"xyz");
    Vector3D AabsO3 = sys.Dt(VabsO3,"xyz");
    Vector3D AabsO4 = sys.Dt(VabsO4,"xyz");
    Vector3D AabsO5 = sys.Dt(VabsO5,"xyz");
    Vector3D AabsO6 = sys.Dt(VabsO6,"xyz");
    Vector3D AabsO7 = sys.Dt(VabsO7,"xyz");
    Vector3D AabsOSun = sys.Dt(VabsOSun,"xyz");
    Vector3D AabsOPla1 = sys.Dt(VabsOPla1,"xyz");    
    Vector3D AabsOPla2 = sys.Dt(VabsOPla2,"xyz");   
    Vector3D AabsOPla3 = sys.Dt(VabsOPla3,"xyz"); 
    Vector3D AabsOSecSt = sys.Dt(VabsOSecSt,"xyz"); 


    Vector3D OMrelB3B2 = sys.Angular_Velocity("B2a","B3");
    Vector3D OMrelB4B3 = sys.Angular_Velocity("B2a","B4")-sys.Angular_Velocity("B2a","B3");
    Vector3D OMrelB5B4 = sys.Angular_Velocity("B2a","B5")-sys.Angular_Velocity("B2a","B4");
    Vector3D OMrelB6B5 =  sys.Angular_Velocity("B2a","B6") - sys.Angular_Velocity("B2a","B5");
    Vector3D OMrelBSunB4 = sys.Angular_Velocity("B4","BSun");
    Vector3D OMrelBPla1B3 = sys.Angular_Velocity("B3","BPla1");
    Vector3D OMrelBPla2B3 = sys.Angular_Velocity("B3","BPla2");
    Vector3D OMrelBPla3B3 = sys.Angular_Velocity("B3","BPla3");
    Vector3D OMrelBSecStB4 = sys.Angular_Velocity("B4","BSecSt");
 
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//Define Frames
//  Frame * R1=sys.new_Frame("R1","O1","B1");
    Frame * R2=sys.new_Frame("R2","O2","B2a"); //Change B2 and Ba2
    Frame * R3=sys.new_Frame("R3","O3","B3");
    Frame * R4=sys.new_Frame("R4","O4","B4");
    Frame * R5=sys.new_Frame("R5","O5","B5");
    Frame * R6=sys.new_Frame("R6","O6","B6");
    Frame * R7=sys.new_Frame("R7","O7","B7");
    Frame * RSun=sys.new_Frame("RSun","OSun","BSun");
    Frame * RPla1=sys.new_Frame("RPla1","OPla1","BPla1");
    Frame * RPla2=sys.new_Frame("RPla2","OPla2","BPla2");
    Frame * RPla3=sys.new_Frame("RPla3","OPla3","BPla3");
    Frame * RSecSt=sys.new_Frame("RSecSt","OSecSt","BSecSt");
//Frames are needed. One solid, one frame

//Define Drawings

    Drawing3D  * D_R2 = sys.new_Drawing3D ("R2","O2","B2a","./solids/SolR2.stl",1.0,0.0,0.0,1.0); 
    Drawing3D  * D_R3 = sys.new_Drawing3D ("R3","O3","B3","./solids/SolR3.stl",0.0,1.0,0.0,1.0);
    Drawing3D  * D_R4 = sys.new_Drawing3D ("R4","O4","B4","./solids/SolR4.stl",1.0,1.0,0.0,1.0);
    Drawing3D  * D_R5 = sys.new_Drawing3D ("R5","O5","B5","./solids/SolR5.stl",1.0,0.0,1.0,1.0);
    Drawing3D  * D_R6 = sys.new_Drawing3D ("R6","O6","B6","./solids/SolR6.stl",0.0,1.0,0.0,1.0);
    Drawing3D  * D_R7 = sys.new_Drawing3D ("R7","O7","B7","./solids/SolR7.stl",0.0,0.0,1.0,1.0);
    Drawing3D  * D_RSun = sys.new_Drawing3D ("RSun","OSun","BSun","./solids/SolRSun.stl",1.0,0.4,0.4,1.0);
    Drawing3D  * D_RPla1 = sys.new_Drawing3D ("RPla1","OPla1","BPla1","./solids/SolRPla1.stl",0.4,0.8,0.8,1.0);
    Drawing3D  * D_RPla2 = sys.new_Drawing3D ("RPla2","OPla2","BPla2","./solids/SolRPla2.stl",0.4,0.8,0.8,1.0);
    Drawing3D  * D_RPla3 = sys.new_Drawing3D ("RPla3","OPla3","BPla3","./solids/SolRPla3.stl",0.4,0.8,0.8,1.0);
    Drawing3D  * D_RSecSt = sys.new_Drawing3D ("RSecSt","OSecSt","BSecSt","./solids/SolRSecSt.stl",0.4,0.6,0.2,1.0);



// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
// ------------------------------------------------ DYNAMICS  --------------------------------------
// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------

//Dynamical Parameter Definition

//  // Dynamic Parameters of Bar 1
//  symbol_numeric  m1 = *sys.new_Parameter("m1",1.0);  symbol_numeric  mx1 = *sys.new_Parameter("mx1",0.0);
//  symbol_numeric  my1 = *sys.new_Parameter("my1",0.0);    symbol_numeric  mz1 = *sys.new_Parameter("mz1",0.0);
//  symbol_numeric  Ixx1 = *sys.new_Parameter("Ixx1",1.0);  symbol_numeric  Ixy1 = *sys.new_Parameter("Ixy1",0.0);
//  symbol_numeric  Iyy1 = *sys.new_Parameter("Iyy1",1.0);  symbol_numeric  Ixz1 = *sys.new_Parameter("Ixz1",0.0);
//  symbol_numeric  Izz1 = *sys.new_Parameter("Izz1",1.0);  symbol_numeric  Iyz1 = *sys.new_Parameter("Iyz1",0.0);

    // Dynamic Parameters of Bar 2
    symbol_numeric  m2 = *sys.new_Parameter("m2",1.0);  symbol_numeric  mx2 = *sys.new_Parameter("mx2",0.0);
    symbol_numeric  my2 = *sys.new_Parameter("my2",0.0);    symbol_numeric  mz2 = *sys.new_Parameter("mz2",0.0);
    symbol_numeric  Ixx2 = *sys.new_Parameter("Ixx2",1.0);  symbol_numeric  Ixy2 = *sys.new_Parameter("Ixy2",0.0);
    symbol_numeric  Iyy2 = *sys.new_Parameter("Iyy2",1.0);  symbol_numeric  Ixz2 = *sys.new_Parameter("Ixz2",0.0);
    symbol_numeric  Izz2 = *sys.new_Parameter("Izz2",1.0);  symbol_numeric  Iyz2 = *sys.new_Parameter("Iyz2",0.0);

    // Dynamic Parameters of Bar 3
    symbol_numeric  m3 = *sys.new_Parameter("m3",1.0);  symbol_numeric  mx3 = *sys.new_Parameter("mx3",0.0);
    symbol_numeric  my3 = *sys.new_Parameter("my3",0.0);    symbol_numeric  mz3 = *sys.new_Parameter("mz3",0.0);
    symbol_numeric  Ixx3 = *sys.new_Parameter("Ixx3",1.0);  symbol_numeric  Ixy3 = *sys.new_Parameter("Ixy3",0.0);
    symbol_numeric  Iyy3 = *sys.new_Parameter("Iyy3",1.0);  symbol_numeric  Ixz3 = *sys.new_Parameter("Ixz3",0.0);
    symbol_numeric  Izz3 = *sys.new_Parameter("Izz3",1.0);  symbol_numeric  Iyz3 = *sys.new_Parameter("Iyz3",0.0);

    // Dynamic Parameters of Bar 4
    symbol_numeric  m4 = *sys.new_Parameter("m4",1.0);  symbol_numeric  mx4 = *sys.new_Parameter("mx4",0.0);
    symbol_numeric  my4 = *sys.new_Parameter("my4",0.0);    symbol_numeric  mz4 = *sys.new_Parameter("mz4",0.0);
    symbol_numeric  Ixx4 = *sys.new_Parameter("Ixx4",1.0);  symbol_numeric  Ixy4 = *sys.new_Parameter("Ixy4",0.0);
    symbol_numeric  Iyy4 = *sys.new_Parameter("Iyy4",1.0);  symbol_numeric  Ixz4 = *sys.new_Parameter("Ixz4",0.0);
    symbol_numeric  Izz4 = *sys.new_Parameter("Izz4",1.0);  symbol_numeric  Iyz4 = *sys.new_Parameter("Iyz4",0.0);

    // Dynamic Parameters of Bar 5
    symbol_numeric  m5 = *sys.new_Parameter("m5",1.0);  symbol_numeric  mx5 = *sys.new_Parameter("mx5",0.0);
    symbol_numeric  my5 = *sys.new_Parameter("my5",0.0);    symbol_numeric  mz5 = *sys.new_Parameter("mz5",0.0);
    symbol_numeric  Ixx5 = *sys.new_Parameter("Ixx5",1.0);  symbol_numeric  Ixy5 = *sys.new_Parameter("Ixy5",0.0);
    symbol_numeric  Iyy5 = *sys.new_Parameter("Iyy5",1.0);  symbol_numeric  Ixz5 = *sys.new_Parameter("Ixz5",0.0);
    symbol_numeric  Izz5 = *sys.new_Parameter("Izz5",1.0);  symbol_numeric  Iyz5 = *sys.new_Parameter("Iyz5",0.0);

    // Dynamic Parameters of Bar 6
    symbol_numeric  m6 = *sys.new_Parameter("m6",1.0);  symbol_numeric  mx6 = *sys.new_Parameter("mx6",0.0);
    symbol_numeric  my6 = *sys.new_Parameter("my6",0.0);    symbol_numeric  mz6 = *sys.new_Parameter("mz6",0.0);
    symbol_numeric  Ixx6 = *sys.new_Parameter("Ixx6",1.0);  symbol_numeric  Ixy6 = *sys.new_Parameter("Ixy6",0.0);
    symbol_numeric  Iyy6 = *sys.new_Parameter("Iyy6",1.0);  symbol_numeric  Ixz6 = *sys.new_Parameter("Ixz6",0.0);
    symbol_numeric  Izz6 = *sys.new_Parameter("Izz6",1.0);  symbol_numeric  Iyz6 = *sys.new_Parameter("Iyz6",0.0);

    // Dynamic Parameters of Bar 7
    symbol_numeric  m7 = *sys.new_Parameter("m7",1.0);  symbol_numeric  mx7 = *sys.new_Parameter("mx7",0.0);
    symbol_numeric  my7 = *sys.new_Parameter("my7",0.0);    symbol_numeric  mz7 = *sys.new_Parameter("mz7",0.0);
    symbol_numeric  Ixx7 = *sys.new_Parameter("Ixx7",1.0);  symbol_numeric  Ixy7 = *sys.new_Parameter("Ixy7",0.0);
    symbol_numeric  Iyy7 = *sys.new_Parameter("Iyy7",1.0);  symbol_numeric  Ixz7 = *sys.new_Parameter("Ixz7",0.0);
    symbol_numeric  Izz7 = *sys.new_Parameter("Izz7",1.0);  symbol_numeric  Iyz7 = *sys.new_Parameter("Iyz7",0.0);


    // Dynamic Parameters of Sun (GearBox)
    symbol_numeric  mSun = *sys.new_Parameter("mSun",1.0);  symbol_numeric  mxSun = *sys.new_Parameter("mxSun",0.0);
    symbol_numeric  mySun = *sys.new_Parameter("mySun",0.0);    symbol_numeric  mzSun = *sys.new_Parameter("mzSun",0.0);
    symbol_numeric  IxxSun = *sys.new_Parameter("IxxSun",1.0);  symbol_numeric  IxySun = *sys.new_Parameter("IxySun",0.0);
    symbol_numeric  IyySun = *sys.new_Parameter("IyySun",1.0);  symbol_numeric  IxzSun = *sys.new_Parameter("IxzSun",0.0);
    symbol_numeric  IzzSun = *sys.new_Parameter("IzzSun",1.0);  symbol_numeric  IyzSun = *sys.new_Parameter("IyzSun",0.0);

    // Dynamic Parameters of the Planets (GearBox)
    symbol_numeric  mPla1 = *sys.new_Parameter("mPla1",0.1);  symbol_numeric  mxPla1 = *sys.new_Parameter("mxPla1",0.0);
    symbol_numeric  myPla1 = *sys.new_Parameter("myPla1",0.0);    symbol_numeric  mzPla1 = *sys.new_Parameter("mzPla1",0.0);
    symbol_numeric  IxxPla1 = *sys.new_Parameter("IxxPla1",1.0);  symbol_numeric  IxyPla1 = *sys.new_Parameter("IxyPla1",0.0);
    symbol_numeric  IyyPla1 = *sys.new_Parameter("IyyPla1",1.0);  symbol_numeric  IxzPla1 = *sys.new_Parameter("IxzPla1",0.0);
    symbol_numeric  IzzPla1 = *sys.new_Parameter("IzzPla1",1.0);  symbol_numeric  IyzPla1 = *sys.new_Parameter("IyzPla1",0.0);

    symbol_numeric  mPla2 = *sys.new_Parameter("mPla2",0.1);  symbol_numeric  mxPla2 = *sys.new_Parameter("mxPla2",0.0);
    symbol_numeric  myPla2 = *sys.new_Parameter("myPla2",0.0);    symbol_numeric  mzPla2 = *sys.new_Parameter("mzPla2",0.0);
    symbol_numeric  IxxPla2 = *sys.new_Parameter("IxxPla2",1.0);  symbol_numeric  IxyPla2 = *sys.new_Parameter("IxyPla2",0.0);
    symbol_numeric  IyyPla2 = *sys.new_Parameter("IyyPla2",1.0);  symbol_numeric  IxzPla2 = *sys.new_Parameter("IxzPla2",0.0);
    symbol_numeric  IzzPla2 = *sys.new_Parameter("IzzPla2",1.0);  symbol_numeric  IyzPla2 = *sys.new_Parameter("IyzPla2",0.0);
    
    symbol_numeric  mPla3 = *sys.new_Parameter("mPla3",0.1);  symbol_numeric  mxPla3 = *sys.new_Parameter("mxPla3",0.0);
    symbol_numeric  myPla3 = *sys.new_Parameter("myPla3",0.0);    symbol_numeric  mzPla3 = *sys.new_Parameter("mzPla3",0.0);
    symbol_numeric  IxxPla3 = *sys.new_Parameter("IxxPla3",1.0);  symbol_numeric  IxyPla3 = *sys.new_Parameter("IxyPla3",0.0);
    symbol_numeric  IyyPla3 = *sys.new_Parameter("IyyPla3",1.0);  symbol_numeric  IxzPla3 = *sys.new_Parameter("IxzPla3",0.0);
    symbol_numeric  IzzPla3 = *sys.new_Parameter("IzzPla3",1.0);  symbol_numeric  IyzPla3 = *sys.new_Parameter("IyzPla3",0.0);

    // Dynamic Parameters of the Second Stage (GearBox)
    symbol_numeric  mSecSt = *sys.new_Parameter("mSecSt",1.0);  symbol_numeric  mxSecSt = *sys.new_Parameter("mxSecSt",0.0);
    symbol_numeric  mySecSt = *sys.new_Parameter("mySecSt",0.0);    symbol_numeric  mzSecSt = *sys.new_Parameter("mzSecSt",0.0);
    symbol_numeric  IxxSecSt = *sys.new_Parameter("IxxSecSt",1.0);  symbol_numeric  IxySecSt = *sys.new_Parameter("IxySecSt",0.0);
    symbol_numeric  IyySecSt = *sys.new_Parameter("IyySecSt",1.0);  symbol_numeric  IxzSecSt = *sys.new_Parameter("IxzSecSt",0.0);
    symbol_numeric  IzzSecSt = *sys.new_Parameter("IzzSecSt",1.0);  symbol_numeric  IyzSecSt = *sys.new_Parameter("IyzSecSt",0.0);


// -------------------------------------------------------------------------------------------------


//Inertia Tensor Definition

//  // Inertia Tensor of Bar 1
//  Tensor3D  I1_O1 = *sys.new_Tensor3D("I1_O1",    (ex)Ixx1,   (ex)Ixy1,   (ex)Ixz1,
//                          (ex)Ixy1,   (ex)Iyy1,   (ex)Iyz1,
//                          (ex)Ixz1,   (ex)Iyz1,   (ex)Izz1,   "B1");

    // Inertia Tensor of Bar 2
    Tensor3D  I2_O2 = *sys.new_Tensor3D("I2_O2",    (ex)Ixx2,   (ex)Ixy2,   (ex)Ixz2,
                            (ex)Ixy2,   (ex)Iyy2,   (ex)Iyz2,
                            (ex)Ixz2,   (ex)Iyz2,   (ex)Izz2,   "B2");

    // Inertia Tensor of Bar 3
    Tensor3D  I3_O3 = *sys.new_Tensor3D("I3_O3",    (ex)Ixx3,   (ex)Ixy3,   (ex)Ixz3,
                            (ex)Ixy3,   (ex)Iyy3,   (ex)Iyz3,
                            (ex)Ixz3,   (ex)Iyz3,   (ex)Izz3,   "B3");

    // Inertia Tensor of Bar 4
    Tensor3D  I4_O4 = *sys.new_Tensor3D("I4_O4",    (ex)Ixx4,   (ex)Ixy4,   (ex)Ixz4,
                            (ex)Ixy4,   (ex)Iyy4,   (ex)Iyz4,
                            (ex)Ixz4,   (ex)Iyz4,   (ex)Izz4,   "B4");

    // Inertia Tensor of Bar 5
    Tensor3D  I5_O5 = *sys.new_Tensor3D("I5_O5",    (ex)Ixx5,   (ex)Ixy5,   (ex)Ixz5,
                            (ex)Ixy5,   (ex)Iyy5,   (ex)Iyz5,
                            (ex)Ixz5,   (ex)Iyz5,   (ex)Izz5,   "B5");

    // Inertia Tensor of Bar 6
    Tensor3D  I6_O6 = *sys.new_Tensor3D("I6_O6",    (ex)Ixx6,   (ex)Ixy6,   (ex)Ixz6,
                            (ex)Ixy6,   (ex)Iyy6,   (ex)Iyz6,
                            (ex)Ixz6,   (ex)Iyz6,   (ex)Izz6,   "B6");

    // Inertia Tensor of Bar 7
    Tensor3D  I7_O7 = *sys.new_Tensor3D("I7_O7",    (ex)Ixx7,   (ex)Ixy7,   (ex)Ixz7,
                            (ex)Ixy7,   (ex)Iyy7,   (ex)Iyz7,
                            (ex)Ixz7,   (ex)Iyz7,   (ex)Izz7,   "B7");


    // Inertia Tensor of Sun (GearBox)
    Tensor3D  ISun_OSun = *sys.new_Tensor3D("ISun_OSun",    (ex)IxxSun,   (ex)IxySun,   (ex)IxzSun,
                            (ex)IxySun,   (ex)IyySun,   (ex)IyzSun,
                            (ex)IxzSun,   (ex)IyzSun,   (ex)IzzSun,   "BSun");

    // Inertia Tensor of Planets (GearBox)
    Tensor3D  IPla1_OPla1 = *sys.new_Tensor3D("IPla1_OPla1",    (ex)IxxPla1,   (ex)IxyPla1,   (ex)IxzPla1,
                            (ex)IxyPla1,   (ex)IyyPla1,   (ex)IyzPla1,
                            (ex)IxzPla1,   (ex)IyzPla1,   (ex)IzzPla1,   "BPla1");

    Tensor3D  IPla2_OPla2 = *sys.new_Tensor3D("IPla2_OPla2",    (ex)IxxPla2,   (ex)IxyPla2,   (ex)IxzPla2,
                            (ex)IxyPla2,   (ex)IyyPla2,   (ex)IyzPla2,
                            (ex)IxzPla2,   (ex)IyzPla2,   (ex)IzzPla2,   "BPla2");
    
    Tensor3D  IPla3_OPla3 = *sys.new_Tensor3D("IPla3_OPla3",    (ex)IxxPla3,   (ex)IxyPla3,   (ex)IxzPla3,
                            (ex)IxyPla3,   (ex)IyyPla3,   (ex)IyzPla3,
                            (ex)IxzPla3,   (ex)IyzPla3,   (ex)IzzPla3,   "BPla3");

    // Inertia Tensor of Second Stage (GearBox)
    Tensor3D  ISecSt_OSecSt = *sys.new_Tensor3D("ISecSt_OSecSt",    (ex)IxxSecSt,   (ex)IxySecSt,   (ex)IxzSecSt,
                            (ex)IxySecSt,   (ex)IyySecSt,   (ex)IyzSecSt,
                            (ex)IxzSecSt,   (ex)IyzSecSt,   (ex)IzzSecSt,   "BSecSt");

                         
// -------------------------------------------------------------------------------------------------

//Center of Gravity Points Definition

    // Vectors
//  Vector3D O1_G1 = *sys.new_Vector3D("O1_G1",mx1/m1,my1/m1,mz1/m1,"B1");
    Vector3D O2_G2 = *sys.new_Vector3D("O2_G2",mx2/m2,my2/m2,mz2/m2,"B2");  //B2 or B2a??????????????????????????????
    Vector3D O3_G3 = *sys.new_Vector3D("O3_G3",mx3/m3,my3/m3,mz3/m3,"B3");
    Vector3D O4_G4 = *sys.new_Vector3D("O4_G4",mx4/m4,my4/m4,mz4/m4,"B4");
    Vector3D O5_G5 = *sys.new_Vector3D("O5_G5",mx5/m5,my5/m5,mz5/m5,"B5");
    Vector3D O6_G6 = *sys.new_Vector3D("O6_G6",mx6/m6,my6/m6,mz6/m6,"B6");
    Vector3D O7_G7 = *sys.new_Vector3D("O7_G7",mx7/m7,my7/m7,mz7/m7,"B7");
    Vector3D OSun_GSun = *sys.new_Vector3D("OSun_GSun",mxSun/mSun,mySun/mSun,mzSun/mSun,"BSun");
    Vector3D OPla1_GPla1 = *sys.new_Vector3D("OPla1_GPla1",mxPla1/mPla1,myPla1/mPla1,mzPla1/mPla1,"BPla1");
    Vector3D OPla2_GPla2 = *sys.new_Vector3D("OPla2_GPla2",mxPla2/mPla2,myPla2/mPla2,mzPla2/mPla2,"BPla2");
    Vector3D OPla3_GPla3 = *sys.new_Vector3D("OPla3_GPla3",mxPla3/mPla3,myPla3/mPla3,mzPla3/mPla3,"BPla3");
    Vector3D OSecSt_GSecSt = *sys.new_Vector3D("OSecSt_GSecSt",mxSecSt/mSecSt,mySecSt/mSecSt,mzSecSt/mSecSt,"BSecSt");


    // Points
//  Point * G1 = sys.new_Point("G1","O1",&O1_G1);
    Point * G2 = sys.new_Point("G2","O2",&O2_G2);
    Point * G3 = sys.new_Point("G3","O3",&O3_G3);
    Point * G4 = sys.new_Point("G4","O4",&O4_G4);
    Point * G5 = sys.new_Point("G5","O5",&O5_G5);
    Point * G6 = sys.new_Point("G6","O6",&O6_G6);
    Point * G7 = sys.new_Point("G7","O7",&O7_G7);
    Point * GSun = sys.new_Point("GSun","OSun",&OSun_GSun);
    Point * GPla1 = sys.new_Point("GPla1","OPla1",&OPla1_GPla1);
    Point * GPla2 = sys.new_Point("GPla2","OPla2",&OPla2_GPla2);
    Point * GPla3 = sys.new_Point("GPla3","OPla3",&OPla3_GPla3);
    Point * GSecSt = sys.new_Point("GSecSt","OSecSt",&OSecSt_GSecSt);



    // Absolute position Vector of G
//  Vector3D OO_G1 = sys.Position_Vector("O","G1");
    Vector3D OO_G2 = sys.Position_Vector("O","G2");
    Vector3D OO_G3 = sys.Position_Vector("O","G3");
    Vector3D OO_G4 = sys.Position_Vector("O","G4");
    Vector3D OO_G5 = sys.Position_Vector("O","G5");
    Vector3D OO_G6 = sys.Position_Vector("O","G6");
    Vector3D OO_G7 = sys.Position_Vector("O","G7");
    Vector3D OO_GSun = sys.Position_Vector("O","GSun");
    Vector3D OO_GPla1 = sys.Position_Vector("O","GPla1");
    Vector3D OO_GPla2 = sys.Position_Vector("O","GPla2");  
    Vector3D OO_GPla3 = sys.Position_Vector("O","GPla3");
    Vector3D OO_GSecSt = sys.Position_Vector("O","GSecSt");



//Define Velocity and Acceleration of Center of Gravity Points
// -----------------------------------------------------------

//  Vector3D VabsG1 = sys.Dt(OO_G1,"xyz");
//  Vector3D AabsG1 = sys.Dt(VabsG1,"xyz");

    Vector3D VabsG2 = sys.Dt(OO_G2,"xyz");
    Vector3D AabsG2 = sys.Dt(VabsG2,"xyz");

    Vector3D VabsG3 = sys.Dt(OO_G3,"xyz");
    Vector3D AabsG3 = sys.Dt(VabsG3,"xyz");

    Vector3D VabsG4 = sys.Dt(OO_G4,"xyz");
    Vector3D AabsG4 = sys.Dt(VabsG4,"xyz");

    Vector3D VabsG5 = sys.Dt(OO_G5,"xyz");
    Vector3D AabsG5 = sys.Dt(VabsG5,"xyz");

    Vector3D VabsG6 = sys.Dt(OO_G6,"xyz");
    Vector3D AabsG6 = sys.Dt(VabsG6,"xyz");

    Vector3D VabsG7 = sys.Dt(OO_G7,"xyz");
    Vector3D AabsG7 = sys.Dt(VabsG7,"xyz");

    Vector3D VabsGSun = sys.Dt(OO_GSun,"xyz");
    Vector3D AabsGSun = sys.Dt(VabsGSun,"xyz");

    Vector3D VabsGPla1 = sys.Dt(OO_GPla1,"xyz");
    Vector3D AabsGPla1 = sys.Dt(VabsGPla1,"xyz");
    Vector3D VabsGPla2 = sys.Dt(OO_GPla2,"xyz");
    Vector3D AabsGPla2 = sys.Dt(VabsGPla2,"xyz");
    Vector3D VabsGPla3 = sys.Dt(OO_GPla3,"xyz");
    Vector3D AabsGPla3 = sys.Dt(VabsGPla3,"xyz");
    
    Vector3D VabsGSecSt = sys.Dt(OO_GSecSt,"xyz");
    Vector3D AabsGSecSt = sys.Dt(VabsGSecSt,"xyz");

// Inertia Forces
//  Vector3D Fi_O1 = -m1*AabsG1;
    Vector3D Fi_O2 = -m2*AabsG2;
    Vector3D Fi_O3 = -m3*AabsG3;
    Vector3D Fi_O4 = -m4*AabsG4;
    Vector3D Fi_O5 = -m5*AabsG5;
    Vector3D Fi_O6 = -m6*AabsG6;
    Vector3D Fi_O7 = -m7*AabsG7;
    Vector3D Fi_OSun = -mSun*AabsGSun;
    Vector3D Fi_OPla1 = -mPla1*AabsGPla1;
    Vector3D Fi_OPla2 = -mPla2*AabsGPla2;
    Vector3D Fi_OPla3 = -mPla3*AabsGPla3;
    Vector3D Fi_OSecSt = -mSecSt*AabsGSecSt;

//Angular Velocities
//  Vector3D Omega1 = sys.Angular_Velocity("xyz","B1");
    Vector3D Omega2 = sys.Angular_Velocity("xyz","B2");
    Vector3D Omega3 = sys.Angular_Velocity("xyz","B3");
    Vector3D Omega4 = sys.Angular_Velocity("xyz","B4");
    Vector3D Omega5 = sys.Angular_Velocity("xyz","B5");
    Vector3D Omega6 = sys.Angular_Velocity("xyz","B6");
    Vector3D Omega7 = sys.Angular_Velocity("xyz","B7");
    Vector3D OmegaSun = sys.Angular_Velocity("xyz","BSun");
    Vector3D OmegaPla1 = sys.Angular_Velocity("xyz","BPla1");    
    Vector3D OmegaPla2 = sys.Angular_Velocity("xyz","BPla2");    
    Vector3D OmegaPla3 = sys.Angular_Velocity("xyz","BPla3");
    Vector3D OmegaSecSt = sys.Angular_Velocity("xyz","BSecSt");

//Angular moment and Inertia Moment
//  Vector3D H1_O1 = I1_O1 * Omega1;
    Vector3D H2_O2 = I2_O2 * Omega2;
    Vector3D H3_O3 = I3_O3 * Omega3;
    Vector3D H4_O4 = I4_O4 * Omega4;
    Vector3D H5_O5 = I5_O5 * Omega5;
    Vector3D H6_O6 = I6_O6 * Omega6;
    Vector3D H7_O7 = I7_O7 * Omega7;
    Vector3D HSun_OSun = ISun_OSun * OmegaSun;
    Vector3D HPla1_OPla1 = IPla1_OPla1 * OmegaPla1;  
    Vector3D HPla2_OPla2 = IPla2_OPla2 * OmegaPla2; 
    Vector3D HPla3_OPla3 = IPla3_OPla3 * OmegaPla3;
    Vector3D HSecSt_OSecSt = ISecSt_OSecSt * OmegaSecSt;    

//  Vector3D Mi_O1 = -sys.Dt(H1_O1,"xyz") - ((m1*O1_G1)^AabsO1);
    Vector3D Mi_O2 = -sys.Dt(H2_O2,"xyz") - ((m2*O2_G2)^AabsO2);
    Vector3D Mi_O3 = -sys.Dt(H3_O3,"xyz") - ((m3*O3_G3)^AabsO3);
    Vector3D Mi_O4 = -sys.Dt(H4_O4,"xyz") - ((m4*O4_G4)^AabsO4);
    Vector3D Mi_O5 = -sys.Dt(H5_O5,"xyz") - ((m5*O5_G5)^AabsO5);
    Vector3D Mi_O6 = -sys.Dt(H6_O6,"xyz") - ((m6*O6_G6)^AabsO6);
    Vector3D Mi_O7 = -sys.Dt(H7_O7,"xyz") - ((m7*O7_G7)^AabsO7);
    Vector3D Mi_OSun = -sys.Dt(HSun_OSun,"xyz") - ((mSun*OSun_GSun)^AabsOSun);
    Vector3D Mi_OPla1 = -sys.Dt(HPla1_OPla1,"xyz") - ((mPla1*OPla1_GPla1)^AabsOPla1);    
    Vector3D Mi_OPla2 = -sys.Dt(HPla2_OPla2,"xyz") - ((mPla2*OPla2_GPla2)^AabsOPla2);    
    Vector3D Mi_OPla3 = -sys.Dt(HPla3_OPla3,"xyz") - ((mPla3*OPla3_GPla3)^AabsOPla3);    
    Vector3D Mi_OSecSt = -sys.Dt(HSecSt_OSecSt,"xyz") - ((mSecSt*OSecSt_GSecSt)^AabsOSecSt);    

//Constitutive Forces and moments Definition

    // Parameters for the forces and moments definitions
    // ----------------------------

// ---------------------------------------------------------------------------------------------------------------------
// Bearing STIFFNESS-DAMPING (JOINT 1-2)
// ---------------------------------------------------------------------------------------------------------------------
    // Translational stiffness of the Yaw Bearing
    symbol_numeric KF12x = *sys.new_Parameter("KF12x",10000.0);
    symbol_numeric KF12y = *sys.new_Parameter("KF12y",10000.0);

    // Translational Stiffness Tensor of the Yaw Bearing
    Tensor3D  KF12 = *sys.new_Tensor3D("KF12",  (ex)KF12x,  0,  0,
                            0,  (ex)KF12y,  0,
                            0,      0,  0,  "xyz");

    // Translational Damping of the Yaw Bearing
    symbol_numeric CF12x = *sys.new_Parameter("CF12x",3.0);
    symbol_numeric CF12y = *sys.new_Parameter("CF12y",3.0);

    // Translational Damping Tensor of the Yaw Bearing
    Tensor3D  CF12 = *sys.new_Tensor3D("CF12",  (ex)CF12x,  0,  0,
                            0,  (ex)CF12y,  0,
                            0,      0,  0,  "xyz");

    // Rotational stiffness of the Yaw Bearing when locked
    symbol_numeric KM12z = *sys.new_Parameter("KM12z",220.0);
    symbol_numeric CM12z = *sys.new_Parameter("CM12z",30.0);

// ------------------------------------------------------------------------------------------------------------------------
// SILENT-BLOCKS STIFFNESS-DAMPING (SOLIDS 2-4)
// ------------------------------------------------------------------------------------------------------------------------
    // Translational stiffness of the silent-blocks between Gear-Box and Nacelle
    symbol_numeric KF24x = *sys.new_Parameter("KF24x",10000.0);
    symbol_numeric KF24y = *sys.new_Parameter("KF24y",10000.0);
    symbol_numeric KF24z = *sys.new_Parameter("KF24z",10000.0);

    // Translational Stiffness Tensor of the silent-blocks between Gear-Box and Nacelle
    Tensor3D  KF24 = *sys.new_Tensor3D("KF24",  (ex)KF24x,  0,  0,
                            0,  (ex)KF24y,  0,
                            0,  0,  (ex)KF24z,  "B2a");

    // Translational damping of the silent-blocks between Gear-Box and Nacelle
    symbol_numeric CF24x = *sys.new_Parameter("CF24x",3.0);
    symbol_numeric CF24y = *sys.new_Parameter("CF24y",3.0);
    symbol_numeric CF24z = *sys.new_Parameter("CF24z",3.0);

    //Translational Damping Tensor of the silent-blocks between Gear-Box and Nacelle
    Tensor3D  CF24 = *sys.new_Tensor3D("CF24",  (ex)CF24x,  0,  0,
                            0,  (ex)CF24y,  0,
                            0,  0,  (ex)CF24z,  "B2a");

// ------------------------------------------------------------------------------------------------------------------------
// SILENT-BLOCKS STIFFNESS-DAMPING (SOLIDS 2-7)
// ------------------------------------------------------------------------------------------------------------------------
    // Translational stiffness of the silent-blocks between Stator and Nacelle
    symbol_numeric KF27x = *sys.new_Parameter("KF27x",10000.0);
    symbol_numeric KF27y = *sys.new_Parameter("KF27y",10000.0);
    symbol_numeric KF27z = *sys.new_Parameter("KF27z",10000.0);

    // Translational Stiffness Tensor of silent-blocks between Stator and Nacelle
    Tensor3D  KF27 = *sys.new_Tensor3D("KF27",  (ex)KF27x,  0,  0,
                            0,  (ex)KF27y,  0,
                            0,  0,  (ex)KF27z,  "B2a");

    // Translational damping of the silent-blocks between Stator and Nacelle
    symbol_numeric CF27x = *sys.new_Parameter("CF27x",3.0);
    symbol_numeric CF27y = *sys.new_Parameter("CF27y",3.0);
    symbol_numeric CF27z = *sys.new_Parameter("CF27z",3.0);

    //Translational Damping Tensor of silent-blocks between Stator and Nacelle
    Tensor3D  CF27 = *sys.new_Tensor3D("CF27",  (ex)CF27x,  0,  0,
                            0,  (ex)CF27y,  0,
                            0,  0,  (ex)CF27z,  "B2a");

// ------------------------------------------------------------------------------------------------------------------------
// Bearing1 STIFFNESS-DAMPING (SOLIDS 2-3)
// ------------------------------------------------------------------------------------------------------------------------
    // Translational stiffness of the coupling between NACELLE and LSS
    symbol_numeric KFBearing1x = *sys.new_Parameter("KFBearing1x",1000.0);
    symbol_numeric KFBearing1y = *sys.new_Parameter("KFBearing1y",1000.0);
    symbol_numeric KFBearing1z = *sys.new_Parameter("KFBearing1z",1000.0);

    // Translational Stiffness Tensor of the coupling between NACELLE and LSS
    Tensor3D  KFBearing1 = *sys.new_Tensor3D("KFBearing1",  (ex)KFBearing1x,  0,  0,
                            0,  (ex)KFBearing1y,  0,
                            0,  0,  (ex)KFBearing1z,  "B2a");

    // Translational damping of the coupling between NACELLE and LSS
    symbol_numeric CFBearing1x = *sys.new_Parameter("CFBearing1x",3.0);
    symbol_numeric CFBearing1y = *sys.new_Parameter("CFBearing1y",3.0);
    symbol_numeric CFBearing1z = *sys.new_Parameter("CFBearing1z",3.0);

    // Translational damping Tensor of the coupling between NACELLE and LSS
    Tensor3D  CFBearing1 = *sys.new_Tensor3D("CFBearing1",  (ex)CFBearing1x,  0,  0,
                            0,  (ex)CFBearing1y,  0,
                            0,  0,  (ex)CFBearing1z,  "B2a");

    // Rotational stiffness of the coupling between NACELLE and LSS
    //symbol_numeric KMBearing1x = *sys.new_Parameter("KMBearing1x", 0.0);  // This must be zero because there is a DOF there.
    symbol_numeric KMBearing1y = *sys.new_Parameter("KMBearing1y",1000.0);
    symbol_numeric KMBearing1z = *sys.new_Parameter("KMBearing1z",1000.0);
    //Rotational Stiffness Tensor of the coupling between NACELLE and LSS   
    Tensor3D  KMBearing1 = *sys.new_Tensor3D("KMBearing1",  0,      0,  0,
                            0,  (ex)KMBearing1y,  0,
                            0,  0,  (ex)KMBearing1z,  "B2a");

    // Rotational damping of the coupling between NACELLE and LSS
    //symbol_numeric CMBearing1x = *sys.new_Parameter("CMBearing1x",0.0);       // This must be zero because there is a DOF there.
    symbol_numeric CMBearing1y = *sys.new_Parameter("CMBearing1y",3.0);
    symbol_numeric CMBearing1z = *sys.new_Parameter("CMBearing1z",3.0);

    //Rotational Damping Tensor of the coupling between NACELLE and LSS
    Tensor3D  CMBearing1 = *sys.new_Tensor3D("CMBearing1",  0,      0,  0,
                            0,  (ex)CMBearing1y,  0,
                            0,  0,  (ex)CMBearing1z,  "B2a");
// ------------------------------------------------------------------------------------------------------------------------
// Bearing2 STIFFNESS-DAMPING (SOLIDS 3-4) 
// ------------------------------------------------------------------------------------------------------------------------
    // Translational stiffness of the coupling between LSS and GEARBOX
    symbol_numeric KFBearing2x = *sys.new_Parameter("KFBearing2x",1000.0);
    symbol_numeric KFBearing2y = *sys.new_Parameter("KFBearing2y",1000.0);
    symbol_numeric KFBearing2z = *sys.new_Parameter("KFBearing2z",1000.0);

    // Translational Stiffness Tensor of the coupling between LSS and GEARBOX
    Tensor3D  KFBearing2 = *sys.new_Tensor3D("KFBearing2",  (ex)KFBearing2x,  0,  0,
                            0,  (ex)KFBearing2y,  0,
                            0,  0,  (ex)KFBearing2z,  "B3");

    // Translational damping of the coupling between LSS and GEARBOX
    symbol_numeric CFBearing2x = *sys.new_Parameter("CFBearing2x",3.0);
    symbol_numeric CFBearing2y = *sys.new_Parameter("CFBearing2y",3.0);
    symbol_numeric CFBearing2z = *sys.new_Parameter("CFBearing2z",3.0);

    // Translational damping Tensor of the coupling between LSS and GEARBOX
    Tensor3D  CFBearing2 = *sys.new_Tensor3D("CFBearing2",  (ex)CFBearing2x,  0,  0,
                            0,  (ex)CFBearing2y,  0,
                            0,  0,  (ex)CFBearing2z,  "B3");

    // Rotational stiffness of the coupling between LSS and GEARBOX
    //symbol_numeric KMBearing2x = *sys.new_Parameter("KMBearing2x", 0.0);  // This must be zero because there is a DOF there.
    symbol_numeric KMBearing2y = *sys.new_Parameter("KMBearing2y",1000.0);
    symbol_numeric KMBearing2z = *sys.new_Parameter("KMBearing2z",1000.0);

    // Rotational damping of the coupling between LSS and GEARBOX
    //symbol_numeric CMBearing2x = *sys.new_Parameter("CMBearing2x",0.0);       // This must be zero because there is a DOF there.
    symbol_numeric CMBearing2y = *sys.new_Parameter("CMBearing2y",3.0);
    symbol_numeric CMBearing2z = *sys.new_Parameter("CMBearing2z",3.0);

    //Rotational Damping Tensor of the coupling between LSS and GEARBOX
    Tensor3D  CMBearing2 = *sys.new_Tensor3D("CMBearing2",  0,      0,  0,
                            0,  (ex)CMBearing2y,  0,
                            0,  0,  (ex)CMBearing2z,  "B3");

// ------------------------------------------------------------------------------------------------------------------------
// GBBearing4 STIFFNESS-DAMPING (SOLIDS 3-4)
// ------------------------------------------------------------------------------------------------------------------------
    // Translational stiffness of the coupling between LSS and GEARBOX
    symbol_numeric KFGBBearing4x = *sys.new_Parameter("KFGBBearing4x",1000.0);
    symbol_numeric KFGBBearing4y = *sys.new_Parameter("KFGBBearing4y",1000.0);
    symbol_numeric KFGBBearing4z = *sys.new_Parameter("KFGBBearing4z",1000.0);

    // Translational Stiffness Tensor of the coupling between LSS and GEARBOX
    Tensor3D  KFGBBearing4 = *sys.new_Tensor3D("KFGBBearing4",  (ex)KFGBBearing4x,  0,  0,
                            0,  (ex)KFGBBearing4y,  0,
                            0,  0,  (ex)KFGBBearing4z,  "B3");

    // Translational damping of the coupling between LSS and GEARBOX
    symbol_numeric CFGBBearing4x = *sys.new_Parameter("CFGBBearing4x",3.0);
    symbol_numeric CFGBBearing4y = *sys.new_Parameter("CFGBBearing4y",3.0);
    symbol_numeric CFGBBearing4z = *sys.new_Parameter("CFGBBearing4z",3.0);

    // Translational damping Tensor of the coupling between LSS and GEARBOX
    Tensor3D  CFGBBearing4 = *sys.new_Tensor3D("CFGBBearing4",  (ex)CFGBBearing4x,  0,  0,
                            0,  (ex)CFGBBearing4y,  0,
                            0,  0,  (ex)CFGBBearing4z,  "B3");

    // Rotational stiffness of the coupling between LSS and GEARBOX
    //symbol_numeric KMGBBearing4x = *sys.new_Parameter("KMGBBearing4x", 0.0);  // This must be zero because there is a DOF there.
    symbol_numeric KMGBBearing4y = *sys.new_Parameter("KMGBBearing4y",1000.0);
    symbol_numeric KMGBBearing4z = *sys.new_Parameter("KMGBBearing4z",1000.0);

    // Rotational damping of the coupling between LSS and GEARBOX
    //symbol_numeric CMGBBearing4x = *sys.new_Parameter("CMGBBearing4x",0.0);       // This must be zero because there is a DOF there.
    symbol_numeric CMGBBearing4y = *sys.new_Parameter("CMGBBearing4y",3.0);
    symbol_numeric CMGBBearing4z = *sys.new_Parameter("CMGBBearing4z",3.0);

    //Rotational Damping Tensor of the coupling between LSS and GEARBOX
    Tensor3D  CMGBBearing4 = *sys.new_Tensor3D("CMGBBearing4",  0,      0,  0,
                            0,  (ex)CMGBBearing4y,  0,
                            0,  0,  (ex)CMGBBearing4z,  "B3");
// --------------------------------------------------------------------------------
// Bearing3 STIFFNESS-DAMPING (SOLIDS 4-5)
// --------------------------------------------------------------------------------
    // Translational stiffness of the coupling between GEARBOX and HHS
    symbol_numeric KFBearing3x = *sys.new_Parameter("KFBearing3x",1000.0);
    symbol_numeric KFBearing3y = *sys.new_Parameter("KFBearing3y",1000.0);
    symbol_numeric KFBearing3z = *sys.new_Parameter("KFBearing3z",1000.0);

    // Translational Stiffness Tensor of the coupling between GEARBOX and HHS
    Tensor3D  KFBearing3 = *sys.new_Tensor3D("KFBearing3",  (ex)KFBearing3x,  0,  0,
                            0,  (ex)KFBearing3y,  0,
                            0,  0,  (ex)KFBearing3z,  "B4");

    // Translational damping of the coupling between GEARBOX and HHS
    symbol_numeric CFBearing3x = *sys.new_Parameter("CFBearing3x",3.0);
    symbol_numeric CFBearing3y = *sys.new_Parameter("CFBearing3y",3.0);
    symbol_numeric CFBearing3z = *sys.new_Parameter("CFBearing3z",3.0);

    // Translational damping Tensor of the coupling between GEARBOX and HHS
    Tensor3D  CFBearing3 = *sys.new_Tensor3D("CFBearing3",  (ex)CFBearing3x,  0,  0,
                            0,  (ex)CFBearing3y,  0,
                            0,  0,  (ex)CFBearing3z,  "B4");

    // Rotational stiffness of the coupling between GEARBOX and HHS
    //symbol_numeric KMBearing3x = *sys.new_Parameter("KMBearing3x", 0.0);  // This must be zero because there is a DOF there.
    symbol_numeric KMBearing3y = *sys.new_Parameter("KMBearing3y",1000.0);
    symbol_numeric KMBearing3z = *sys.new_Parameter("KMBearing3z",1000.0);

    // Rotational damping of the coupling between GEARBOX and HHS
    //symbol_numeric CMBearing3x = *sys.new_Parameter("CMBearing3x",0.0);       // This must be zero because there is a DOF there.
    symbol_numeric CMBearing3y = *sys.new_Parameter("CMBearing3y",3.0);
    symbol_numeric CMBearing3z = *sys.new_Parameter("CMBearing3z",3.0);

    //Rotational Damping Tensor of the coupling between GEARBOX and HHS
    Tensor3D  CMBearing3 = *sys.new_Tensor3D("CMBearing3",  0,      0,  0,
                            0,  (ex)CMBearing3y,  0,
                            0,  0,  (ex)CMBearing3z,  "B4");

// --------------------------------------------------------------------------------
// GBBearing9 STIFFNESS-DAMPING (SOLIDS 4-5)
// --------------------------------------------------------------------------------
    // Translational stiffness of the coupling between GEARBOX and HHS
    symbol_numeric KFGBBearing9x = *sys.new_Parameter("KFGBBearing9x",1000.0);
    symbol_numeric KFGBBearing9y = *sys.new_Parameter("KFGBBearing9y",1000.0);
    symbol_numeric KFGBBearing9z = *sys.new_Parameter("KFGBBearing9z",1000.0);

    // Translational Stiffness Tensor of the coupling between GEARBOX and HHS
    Tensor3D  KFGBBearing9 = *sys.new_Tensor3D("KFGBBearing9",  (ex)KFGBBearing9x,  0,  0,
                            0,  (ex)KFGBBearing9y,  0,
                            0,  0,  (ex)KFGBBearing9z,  "B4");

    // Translational damping of the coupling between GEARBOX and HHS
    symbol_numeric CFGBBearing9x = *sys.new_Parameter("CFGBBearing9x",3.0);
    symbol_numeric CFGBBearing9y = *sys.new_Parameter("CFGBBearing9y",3.0);
    symbol_numeric CFGBBearing9z = *sys.new_Parameter("CFGBBearing9z",3.0);

    // Translational damping Tensor of the coupling between GEARBOX and HHS
    Tensor3D  CFGBBearing9 = *sys.new_Tensor3D("CFGBBearing9",  (ex)CFGBBearing9x,  0,  0,
                            0,  (ex)CFGBBearing9y,  0,
                            0,  0,  (ex)CFGBBearing9z,  "B4");

    // Rotational stiffness of the coupling between GEARBOX and HHS
    //symbol_numeric KMGBBearing9x = *sys.new_Parameter("KMGBBearing9x", 0.0);  // This must be zero because there is a DOF there.
    symbol_numeric KMGBBearing9y = *sys.new_Parameter("KMGBBearing9y",1000.0);
    symbol_numeric KMGBBearing9z = *sys.new_Parameter("KMGBBearing9z",1000.0);

    // Rotational damping of the coupling between GEARBOX and HHS
    //symbol_numeric CM45x = *sys.new_Parameter("CM45x",0.0);       // This must be zero because there is a DOF there.
    symbol_numeric CMGBBearing9y = *sys.new_Parameter("CMGBBearing9y",3.0);
    symbol_numeric CMGBBearing9z = *sys.new_Parameter("CMGBBearing9z",3.0);

    //Rotational Damping Tensor of the coupling between GEARBOX and HHS
    Tensor3D  CMGBBearing9 = *sys.new_Tensor3D("CMGBBearing9",  0,      0,  0,
                            0,  (ex)CMGBBearing9y,  0,
                            0,  0,  (ex)CMGBBearing9z,  "B4");

// --------------------------------------------------------------------------------
// COUPLING STIFFNESS-DAMPING (SOLIDS 5-6)
// --------------------------------------------------------------------------------
    // Rotational stiffness of the coupling between HSS and Generator
    symbol_numeric KM56x = *sys.new_Parameter("KM56x",1000.0);
    symbol_numeric KM56y = *sys.new_Parameter("KM56y",1000.0);
    symbol_numeric KM56z = *sys.new_Parameter("KM56z",1000.0);

    // Rotational damping of the coupling between HSS and Generator
    symbol_numeric CM56x = *sys.new_Parameter("CM56x",3.0);
    symbol_numeric CM56y = *sys.new_Parameter("CM56y",3.0);
    symbol_numeric CM56z = *sys.new_Parameter("CM56z",3.0);

    //Rotational Damping Tensor of the coupling between HSS and Generator
    Tensor3D  CM56 = *sys.new_Tensor3D("CM56",  (ex)CM56x,  0,  0,
                            0,  (ex)CM56y,  0,
                            0,  0,  (ex)CM56z,  "B5");

// --------------------------------------------------------------------------------
// GBBearing5 STIFFNESS-DAMPING (SOLIDS 4-Sun)
// --------------------------------------------------------------------------------
    // Translational stiffness of the coupling between GEARBOX and Sun
    symbol_numeric KFGBBearing5x = *sys.new_Parameter("KFGBBearing5x",1000.0);
    symbol_numeric KFGBBearing5y = *sys.new_Parameter("KFGBBearing5y",1000.0);
    symbol_numeric KFGBBearing5z = *sys.new_Parameter("KFGBBearing5z",1000.0);

    // Translational Stiffness Tensor of the coupling between GEARBOX and Sun
    Tensor3D  KFGBBearing5 = *sys.new_Tensor3D("KFGBBearing5",  (ex)KFGBBearing5x,  0,  0,
                            0,  (ex)KFGBBearing5y,  0,
                            0,  0,  (ex)KFGBBearing5z,  "B4");

    // Translational damping of the coupling between GEARBOX and Sun
    symbol_numeric CFGBBearing5x = *sys.new_Parameter("CFGBBearing5x",3.0);
    symbol_numeric CFGBBearing5y = *sys.new_Parameter("CFGBBearing5y",3.0);
    symbol_numeric CFGBBearing5z = *sys.new_Parameter("CFGBBearing5z",3.0);

    // Translational damping Tensor of the coupling between GEARBOX and Sun
    Tensor3D  CFGBBearing5 = *sys.new_Tensor3D("CFGBBearing5",  (ex)CFGBBearing5x,  0,  0,
                            0,  (ex)CFGBBearing5y,  0,
                            0,  0,  (ex)CFGBBearing5z,  "B4");

    // Rotational stiffness of the coupling between GEARBOX and Sun
    //symbol_numeric KMGBBearing5x = *sys.new_Parameter("KMGBBearing5x", 0.0);  
    symbol_numeric KMGBBearing5y = *sys.new_Parameter("KMGBBearing5y",1000.0);
    symbol_numeric KMGBBearing5z = *sys.new_Parameter("KMGBBearing5z",1000.0);

    // Rotational Stiffness Tensor of the coupling between GEARBOX and Sun
    Tensor3D  KMGBBearing5 = *sys.new_Tensor3D("KMGBBearing5",  0,  0,  0,
                            0,  (ex)KMGBBearing5y,  0,
                            0,  0,  (ex)KMGBBearing5z,  "B4");

    // Rotational damping of the coupling between GEARBOX and Sun
    //symbol_numeric CMGBBearing5x = *sys.new_Parameter("CMGBBearing5x",3.0);       
    symbol_numeric CMGBBearing5y = *sys.new_Parameter("CMGBBearing5y",3.0);
    symbol_numeric CMGBBearing5z = *sys.new_Parameter("CMGBBearing5z",3.0);

    //Rotational Damping Tensor of the coupling between GEARBOX and Sun
    Tensor3D  CMGBBearing5 = *sys.new_Tensor3D("CMGBBearing5", 0 ,      0,  0,
                            0,  (ex)CMGBBearing5y,  0,
                            0,  0,  (ex)CMGBBearing5z,  "B4");
// --------------------------------------------------------------------------------
// GBBearing6 STIFFNESS-DAMPING (SOLIDS 4-Sun)
// --------------------------------------------------------------------------------
    // Translational stiffness of the coupling between GEARBOX and Sun
    symbol_numeric KFGBBearing6x = *sys.new_Parameter("KFGBBearing6x",1000.0);
    symbol_numeric KFGBBearing6y = *sys.new_Parameter("KFGBBearing6y",1000.0);
    symbol_numeric KFGBBearing6z = *sys.new_Parameter("KFGBBearing6z",1000.0);

    // Translational Stiffness Tensor of the coupling between GEARBOX and Sun
    Tensor3D  KFGBBearing6 = *sys.new_Tensor3D("KFGBBearing6",  (ex)KFGBBearing6x,  0,  0,
                            0,  (ex)KFGBBearing6y,  0,
                            0,  0,  (ex)KFGBBearing6z,  "B4");

    // Translational damping of the coupling between GEARBOX and Sun
    symbol_numeric CFGBBearing6x = *sys.new_Parameter("CFGBBearing6x",3.0);
    symbol_numeric CFGBBearing6y = *sys.new_Parameter("CFGBBearing6y",3.0);
    symbol_numeric CFGBBearing6z = *sys.new_Parameter("CFGBBearing6z",3.0);

    // Translational damping Tensor of the coupling between GEARBOX and Sun
    Tensor3D  CFGBBearing6 = *sys.new_Tensor3D("CFGBBearing6",  (ex)CFGBBearing6x,  0,  0,
                            0,  (ex)CFGBBearing6y,  0,
                            0,  0,  (ex)CFGBBearing6z,  "B4");

    // Rotational stiffness of the coupling between GEARBOX and Sun
    //symbol_numeric KMGBBearing6x = *sys.new_Parameter("KMGBBearing6x", 0.0);  
    symbol_numeric KMGBBearing6y = *sys.new_Parameter("KMGBBearing6y",1000.0);
    symbol_numeric KMGBBearing6z = *sys.new_Parameter("KMGBBearing6z",1000.0);

    // Rotational Stiffness Tensor of the coupling between GEARBOX and Sun
    Tensor3D  KMGBBearing6 = *sys.new_Tensor3D("KMGBBearing6",  0,  0,  0,
                            0,  (ex)KMGBBearing6y,  0,
                            0,  0,  (ex)KMGBBearing6z,  "B4");

    // Rotational damping of the coupling between GEARBOX and Sun
    //symbol_numeric CMGBBearing6x = *sys.new_Parameter("CMGBBearing6x",3.0);       
    symbol_numeric CMGBBearing6y = *sys.new_Parameter("CMGBBearing6y",3.0);
    symbol_numeric CMGBBearing6z = *sys.new_Parameter("CMGBBearing6z",3.0);

    //Rotational Damping Tensor of the coupling between GEARBOX and Sun
    Tensor3D  CMGBBearing6 = *sys.new_Tensor3D("CMGBBearing6", 0 ,      0,  0,
                            0,  (ex)CMGBBearing6y,  0,
                            0,  0,  (ex)CMGBBearing6z,  "B4");

// --------------------------------------------------------------------------------
// GBBearing1 STIFFNESS-DAMPING (SOLIDS 3-Pla1)
// --------------------------------------------------------------------------------
    // Translational stiffness of the coupling between GEARBOX and Pla1
    symbol_numeric KFGBBearing1x = *sys.new_Parameter("KFGBBearing1x",1000.0);
    symbol_numeric KFGBBearing1y = *sys.new_Parameter("KFGBBearing1y",1000.0);
    symbol_numeric KFGBBearing1z = *sys.new_Parameter("KFGBBearing1z",1000.0);

    // Translational Stiffness Tensor of the coupling between GEARBOX and Pla1
    Tensor3D  KFGBBearing1 = *sys.new_Tensor3D("KFGBBearing1",  (ex)KFGBBearing1x,  0,  0,
                            0,  (ex)KFGBBearing1y,  0,
                            0,  0,  (ex)KFGBBearing1z,  "B3");

    // Translational damping of the coupling between GEARBOX and Pla1
    symbol_numeric CFGBBearing1x = *sys.new_Parameter("CFGBBearing1x",3.0);
    symbol_numeric CFGBBearing1y = *sys.new_Parameter("CFGBBearing1y",3.0);
    symbol_numeric CFGBBearing1z = *sys.new_Parameter("CFGBBearing1z",3.0);

    // Translational damping Tensor of the coupling between GEARBOX and Pla1
    Tensor3D  CFGBBearing1 = *sys.new_Tensor3D("CFGBBearing1",  (ex)CFGBBearing1x,  0,  0,
                            0,  (ex)CFGBBearing1y,  0,
                            0,  0,  (ex)CFGBBearing1z,  "B3");

    // Rotational stiffness of the coupling between GEARBOX and Pla1
    //symbol_numeric KMGBBearing1x = *sys.new_Parameter("KMGBBearing1x", 0.0);  
    symbol_numeric KMGBBearing1y = *sys.new_Parameter("KMGBBearing1y",1000.0);
    symbol_numeric KMGBBearing1z = *sys.new_Parameter("KMGBBearing1z",1000.0);

    // Rotational Stiffness Tensor of the coupling between GEARBOX and Pla1
    Tensor3D  KMGBBearing1 = *sys.new_Tensor3D("KMGBBearing1",  0,  0,  0,
                            0,  (ex)KMGBBearing1y,  0,
                            0,  0,  (ex)KMGBBearing1z,  "B3");

    // Rotational damping of the coupling between GEARBOX and Pla1
    //symbol_numeric CMGBBearing1x = *sys.new_Parameter("CMGBBearing1x",3.0);       
    symbol_numeric CMGBBearing1y = *sys.new_Parameter("CMGBBearing1y",3.0);
    symbol_numeric CMGBBearing1z = *sys.new_Parameter("CMGBBearing1z",3.0);

    //Rotational Damping Tensor of the coupling between GEARBOX and Pla1
    Tensor3D  CMGBBearing1 = *sys.new_Tensor3D("CMGBBearing1", 0 ,      0,  0,
                            0,  (ex)CMGBBearing1y,  0,
                            0,  0,  (ex)CMGBBearing1z,  "B3");

// --------------------------------------------------------------------------------
// GBBearing2 STIFFNESS-DAMPING (SOLIDS 3-Pla2)
// --------------------------------------------------------------------------------
    // Translational stiffness of the coupling between GEARBOX and Pla2
    symbol_numeric KFGBBearing2x = *sys.new_Parameter("KFGBBearing2x",1000.0);
    symbol_numeric KFGBBearing2y = *sys.new_Parameter("KFGBBearing2y",1000.0);
    symbol_numeric KFGBBearing2z = *sys.new_Parameter("KFGBBearing2z",1000.0);

    // Translational Stiffness Tensor of the coupling between GEARBOX and Pla2
    Tensor3D  KFGBBearing2 = *sys.new_Tensor3D("KFGBBearing2",  (ex)KFGBBearing2x,  0,  0,
                            0,  (ex)KFGBBearing2y,  0,
                            0,  0,  (ex)KFGBBearing2z,  "B3");

    // Translational damping of the coupling between GEARBOX and Pla2
    symbol_numeric CFGBBearing2x = *sys.new_Parameter("CFGBBearing2x",3.0);
    symbol_numeric CFGBBearing2y = *sys.new_Parameter("CFGBBearing2y",3.0);
    symbol_numeric CFGBBearing2z = *sys.new_Parameter("CFGBBearing2z",3.0);

    // Translational damping Tensor of the coupling between GEARBOX and Pla2
    Tensor3D  CFGBBearing2 = *sys.new_Tensor3D("CFGBBearing2",  (ex)CFGBBearing2x,  0,  0,
                            0,  (ex)CFGBBearing2y,  0,
                            0,  0,  (ex)CFGBBearing2z,  "B3");

    // Rotational stiffness of the coupling between GEARBOX and Pla2
    //symbol_numeric KMGBBearing2x = *sys.new_Parameter("KMGBBearing2x", 0.0);  
    symbol_numeric KMGBBearing2y = *sys.new_Parameter("KMGBBearing2y",1000.0);
    symbol_numeric KMGBBearing2z = *sys.new_Parameter("KMGBBearing2z",1000.0);

    // Rotational Stiffness Tensor of the coupling between GEARBOX and Pla2
    Tensor3D  KMGBBearing2 = *sys.new_Tensor3D("KMGBBearing2",  0,  0,  0,
                            0,  (ex)KMGBBearing2y,  0,
                            0,  0,  (ex)KMGBBearing2z,  "B3");

    // Rotational damping of the coupling between GEARBOX and Pla2
    //symbol_numeric CMGBBearing2x = *sys.new_Parameter("CMGBBearing2x",3.0);       
    symbol_numeric CMGBBearing2y = *sys.new_Parameter("CMGBBearing2y",3.0);
    symbol_numeric CMGBBearing2z = *sys.new_Parameter("CMGBBearing2z",3.0);

    //Rotational Damping Tensor of the coupling between GEARBOX and Pla2
    Tensor3D  CMGBBearing2 = *sys.new_Tensor3D("CMGBBearing2", 0 ,      0,  0,
                            0,  (ex)CMGBBearing2y,  0,
                            0,  0,  (ex)CMGBBearing2z,  "B3");


// --------------------------------------------------------------------------------
// GBBearing3 STIFFNESS-DAMPING (SOLIDS 3-Pla3)
// --------------------------------------------------------------------------------
    // Translational stiffness of the coupling between GEARBOX and Pla3
    symbol_numeric KFGBBearing3x = *sys.new_Parameter("KFGBBearing3x",1000.0);
    symbol_numeric KFGBBearing3y = *sys.new_Parameter("KFGBBearing3y",1000.0);
    symbol_numeric KFGBBearing3z = *sys.new_Parameter("KFGBBearing3z",1000.0);

    // Translational Stiffness Tensor of the coupling between GEARBOX and Pla3
    Tensor3D  KFGBBearing3 = *sys.new_Tensor3D("KFGBBearing3",  (ex)KFGBBearing3x,  0,  0,
                            0,  (ex)KFGBBearing3y,  0,
                            0,  0,  (ex)KFGBBearing3z,  "B3");

    // Translational damping of the coupling between GEARBOX and Pla3
    symbol_numeric CFGBBearing3x = *sys.new_Parameter("CFGBBearing3x",3.0);
    symbol_numeric CFGBBearing3y = *sys.new_Parameter("CFGBBearing3y",3.0);
    symbol_numeric CFGBBearing3z = *sys.new_Parameter("CFGBBearing3z",3.0);

    // Translational damping Tensor of the coupling between GEARBOX and Pla3
    Tensor3D  CFGBBearing3 = *sys.new_Tensor3D("CFGBBearing3",  (ex)CFGBBearing3x,  0,  0,
                            0,  (ex)CFGBBearing3y,  0,
                            0,  0,  (ex)CFGBBearing3z,  "B3");

    // Rotational stiffness of the coupling between GEARBOX and Pla3
    //symbol_numeric KMGBBearing3x = *sys.new_Parameter("KMGBBearing3x", 0.0);  
    symbol_numeric KMGBBearing3y = *sys.new_Parameter("KMGBBearing3y",1000.0);
    symbol_numeric KMGBBearing3z = *sys.new_Parameter("KMGBBearing3z",1000.0);

    // Rotational Stiffness Tensor of the coupling between GEARBOX and Pla3
    Tensor3D  KMGBBearing3 = *sys.new_Tensor3D("KMGBBearing3",  0,  0,  0,
                            0,  (ex)KMGBBearing3y,  0,
                            0,  0,  (ex)KMGBBearing3z,  "B3");

    // Rotational damping of the coupling between GEARBOX and Pla3
    //symbol_numeric CMGBBearing3x = *sys.new_Parameter("CMGBBearing3x",3.0);       
    symbol_numeric CMGBBearing3y = *sys.new_Parameter("CMGBBearing3y",3.0);
    symbol_numeric CMGBBearing3z = *sys.new_Parameter("CMGBBearing3z",3.0);

    //Rotational Damping Tensor of the coupling between GEARBOX and Pla3
    Tensor3D  CMGBBearing3 = *sys.new_Tensor3D("CMGBBearing3", 0 ,      0,  0,
                            0,  (ex)CMGBBearing3y,  0,
                            0,  0,  (ex)CMGBBearing3z,  "B3");

// --------------------------------------------------------------------------------
// GBBearing7 STIFFNESS-DAMPING (SOLIDS 4-SecSt)
// --------------------------------------------------------------------------------
    // Translational stiffness of the coupling between GEARBOX and SecSt
    symbol_numeric KFGBBearing7x = *sys.new_Parameter("KFGBBearing7x",1000.0);
    symbol_numeric KFGBBearing7y = *sys.new_Parameter("KFGBBearing7y",1000.0);
    symbol_numeric KFGBBearing7z = *sys.new_Parameter("KFGBBearing7z",1000.0);

    // Translational Stiffness Tensor of the coupling between GEARBOX and SecSt
    Tensor3D  KFGBBearing7 = *sys.new_Tensor3D("KFGBBearing7",  (ex)KFGBBearing7x,  0,  0,
                            0,  (ex)KFGBBearing7y,  0,
                            0,  0,  (ex)KFGBBearing7z,  "B4");

    // Translational damping of the coupling between GEARBOX and SecSt
    symbol_numeric CFGBBearing7x = *sys.new_Parameter("CFGBBearing7x",3.0);
    symbol_numeric CFGBBearing7y = *sys.new_Parameter("CFGBBearing7y",3.0);
    symbol_numeric CFGBBearing7z = *sys.new_Parameter("CFGBBearing7z",3.0);

    // Translational damping Tensor of the coupling between GEARBOX and SecSt
    Tensor3D  CFGBBearing7 = *sys.new_Tensor3D("CFGBBearing7",  (ex)CFGBBearing7x,  0,  0,
                            0,  (ex)CFGBBearing7y,  0,
                            0,  0,  (ex)CFGBBearing7z,  "B4");

    // Rotational stiffness of the coupling between GEARBOX and SecSt
    //symbol_numeric KMGBBearing7x = *sys.new_Parameter("KMGBBearing7x", 0.0);  
    symbol_numeric KMGBBearing7y = *sys.new_Parameter("KMGBBearing7y",1000.0);
    symbol_numeric KMGBBearing7z = *sys.new_Parameter("KMGBBearing7z",1000.0);

    // Rotational Stiffness Tensor of the coupling between GEARBOX and SecSt
    Tensor3D  KMGBBearing7 = *sys.new_Tensor3D("KMGBBearing7",  0,  0,  0,
                            0,  (ex)KMGBBearing7y,  0,
                            0,  0,  (ex)KMGBBearing7z,  "B4");

    // Rotational damping of the coupling between GEARBOX and SecSt
    //symbol_numeric CMGBBearing7x = *sys.new_Parameter("CMGBBearing7x",3.0);       
    symbol_numeric CMGBBearing7y = *sys.new_Parameter("CMGBBearing7y",3.0);
    symbol_numeric CMGBBearing7z = *sys.new_Parameter("CMGBBearing7z",3.0);

    //Rotational Damping Tensor of the coupling between GEARBOX and SecSt
    Tensor3D  CMGBBearing7 = *sys.new_Tensor3D("CMGBBearing7", 0 ,      0,  0,
                            0,  (ex)CMGBBearing7y,  0,
                            0,  0,  (ex)CMGBBearing7z,  "B4");
// --------------------------------------------------------------------------------
// Bearing STIFFNESS-DAMPING (SOLIDS 4-SecSt) Second Bearing aka GBBearing8
// --------------------------------------------------------------------------------
    // Translational stiffness of the coupling between GEARBOX and SecSt
    symbol_numeric KFGBBearing8x = *sys.new_Parameter("KFGBBearing8x",1000.0);
    symbol_numeric KFGBBearing8y = *sys.new_Parameter("KFGBBearing8y",1000.0);
    symbol_numeric KFGBBearing8z = *sys.new_Parameter("KFGBBearing8z",1000.0);

    // Translational Stiffness Tensor of the coupling between GEARBOX and SecSt
    Tensor3D  KFGBBearing8 = *sys.new_Tensor3D("KFGBBearing8",  (ex)KFGBBearing8x,  0,  0,
                            0,  (ex)KFGBBearing8y,  0,
                            0,  0,  (ex)KFGBBearing8z,  "B4");

    // Translational damping of the coupling between GEARBOX and SecSt
    symbol_numeric CFGBBearing8x = *sys.new_Parameter("CFGBBearing8x",3.0);
    symbol_numeric CFGBBearing8y = *sys.new_Parameter("CFGBBearing8y",3.0);
    symbol_numeric CFGBBearing8z = *sys.new_Parameter("CFGBBearing8z",3.0);

    // Translational damping Tensor of the coupling between GEARBOX and SecSt
    Tensor3D  CFGBBearing8 = *sys.new_Tensor3D("CFGBBearing8",  (ex)CFGBBearing8x,  0,  0,
                            0,  (ex)CFGBBearing8y,  0,
                            0,  0,  (ex)CFGBBearing8z,  "B4");

    // Rotational stiffness of the coupling between GEARBOX and SecSt
    //symbol_numeric KMGBBearing8x = *sys.new_Parameter("KMGBBearing8x", 0.0);  
    symbol_numeric KMGBBearing8y = *sys.new_Parameter("KMGBBearing8y",1000.0);
    symbol_numeric KMGBBearing8z = *sys.new_Parameter("KMGBBearing8z",1000.0);

    // Rotational Stiffness Tensor of the coupling between GEARBOX and SecSt
    Tensor3D  KMGBBearing8 = *sys.new_Tensor3D("KMGBBearing8",  0,  0,  0,
                            0,  (ex)KMGBBearing8y,  0,
                            0,  0,  (ex)KMGBBearing8z,  "B4");

    // Rotational damping of the coupling between GEARBOX and SecSt
    //symbol_numeric CMGBBearing8x = *sys.new_Parameter("CMGBBearing8x",3.0);       
    symbol_numeric CMGBBearing8y = *sys.new_Parameter("CMGBBearing8y",3.0);
    symbol_numeric CMGBBearing8z = *sys.new_Parameter("CMGBBearing8z",3.0);

    //Rotational Damping Tensor of the coupling between GEARBOX and SecSt
    Tensor3D  CMGBBearing8 = *sys.new_Tensor3D("CMGBBearing8", 0 ,      0,  0,
                            0,  (ex)CMGBBearing8y,  0,
                            0,  0,  (ex)CMGBBearing8z,  "B4");
// -----------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// EXTERNAL FORCES-TORQUES APPLIED TO THE HUB
// --------------------------------------------------------------------------------
    // External force and torque exerted on the Hub (remove when rotor model exist)
    symbol_numeric FHUBx = *sys.new_Input("FHUBx",0.0);
    symbol_numeric FHUBy = *sys.new_Input("FHUBy",0.0);
    symbol_numeric FHUBz = *sys.new_Input("FHUBz",0.0);

    symbol_numeric MHUBx = *sys.new_Input("MHUBx",0.0);
    symbol_numeric MHUBy = *sys.new_Input("MHUBy",0.0);
    symbol_numeric MHUBz = *sys.new_Input("MHUBz",0.0);

    // External Brake Force (applied on the HSS)
    symbol_numeric FBRAz = *sys.new_Input("FBRAz",0.0);

    // Torque between Generator and Stator (applied on the Stator)
    symbol_numeric TGENx = *sys.new_Input("TGENx",0.0);



    // External forces and moments
    // ----------------------------

    // Auxiliary unitary vectors for rotational stiffnesses
    Vector3D e2z = *sys.new_Vector3D("e2z",0,0,1,"B2");
    Vector3D e5x = *sys.new_Vector3D("e5x",1,0,0,"B5");

    Vector3D e2ax = *sys.new_Vector3D("e2ax",1,0,0,"B2a");
    Vector3D e2ay = *sys.new_Vector3D("e2ay",0,1,0,"B2a");
    Vector3D e2az = *sys.new_Vector3D("e2az",0,0,1,"B2a");

    Vector3D e3x = *sys.new_Vector3D("e3x",1,0,0,"B3");
    Vector3D e3y = *sys.new_Vector3D("e3y",0,1,0,"B3");
    Vector3D e3z = *sys.new_Vector3D("e3z",0,0,1,"B3");

    Vector3D e4x = *sys.new_Vector3D("e4x",1,0,0,"B4");
    Vector3D e4y = *sys.new_Vector3D("e4y",0,1,0,"B4");
    Vector3D e4z = *sys.new_Vector3D("e4z",0,0,1,"B4");


    // Gravity vectors
//  Vector3D F_grav_1 = *sys.new_Vector3D("F_grav_1",0,0,-m1 * g,"xyz");
    Vector3D F_grav_2 = *sys.new_Vector3D("F_grav_2",0,0,-m2 * (*g),"xyz");
    Vector3D F_grav_3 = *sys.new_Vector3D("F_grav_3",0,0,-m3 * (*g),"xyz");
    Vector3D F_grav_4 = *sys.new_Vector3D("F_grav_4",0,0,-m4 * (*g),"xyz");
    Vector3D F_grav_5 = *sys.new_Vector3D("F_grav_5",0,0,-m5 * (*g),"xyz");
    Vector3D F_grav_6 = *sys.new_Vector3D("F_grav_6",0,0,-m6 * (*g),"xyz");
    Vector3D F_grav_7 = *sys.new_Vector3D("F_grav_7",0,0,-m7 * (*g),"xyz");
    Vector3D F_grav_Sun = *sys.new_Vector3D("F_grav_Sun",0,0,-mSun * (*g),"xyz");
    Vector3D F_grav_Pla1 = *sys.new_Vector3D("F_grav_Pla1",0,0,-mPla1 * (*g),"xyz");    
    Vector3D F_grav_Pla2 = *sys.new_Vector3D("F_grav_Pla2",0,0,-mPla2 * (*g),"xyz");    
    Vector3D F_grav_Pla3 = *sys.new_Vector3D("F_grav_Pla3",0,0,-mPla3 * (*g),"xyz");    
    Vector3D F_grav_SecSt = *sys.new_Vector3D("F_grav_SecSt",0,0,-mSecSt * (*g),"xyz");

//----------------------------------------------------------------------------------------
    // Spring-damper force in the Yaw Bearing of the Nacelle
    Vector3D KCF12 =  -(KF12 * O1_O2 + CF12*VrelO1_O2);

    // Spring-damper torque in the Yaw Bearing of the Nacelle
    Vector3D KCM12 = - KM12z*c2* e2z - CM12z * Omega2;

//----------------------------------------------------------------------------------------
    // Spring-damper torque in the coupling between the NACELLE and LSS  ---> Bearing1
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES ( -1 << b3,c3,b4,c4 << 1 )
    Vector3D KCMBearing1 =  - KMBearing1y*(b3)*e2ay - KMBearing1z*(c3)*e2az  - CMBearing1*OMrelB3B2;
    // Spring-damper force in the coupling between the LSS and GEARBOX
    Vector3D KCFBearing1 =  -(KFBearing1 * Bearing1S2_Bearing1S3+ CFBearing1*VrelBearing1S2_Bearing1S3);

//----------------------------------------------------------------------------------------
    // Spring-damper torque in the coupling between the LSS and GEARBOX  ---> Bearing2
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES ( -1 << b3,c3,b4,c4 << 1 )
    Vector3D KCMBearing2 =  - KMBearing2y*(b4-b3)*e2ay - KMBearing2z*(c4-c3)*e2az  - CMBearing2*OMrelB4B3;
    // Spring-damper force in the coupling between the LSS and GEARBOX
    Vector3D KCFBearing2 =  -(KFBearing2 * Bearing2S3_Bearing2S4+ CFBearing2*VrelBearing2S3_Bearing2S4);

    // Spring-damper torque in the coupling between the LSS and GEARBOX  ---> GBBearing4
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES ( -1 << b3,c3,b4,c4 << 1 )
    Vector3D KCMGBBearing4 =  - KMGBBearing4y*(b4-b3)*e2ay - KMGBBearing4z*(c4-c3)*e2az  - CMGBBearing4*OMrelB4B3;  
    // Spring-damper force in the coupling between the LSS and GEARBOX
    Vector3D KCFGBBearing4 =  -(KFGBBearing4 * GBBearing4S3_GBBearing4S4+ CFGBBearing4*VrelGBBearing4S3_GBBearing4S4);

//----------------------------------------------------------------------------------------
    // Spring-damper torque in the coupling between the GEARBOX and the HHS ---> Bearing3
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES ( -1 << b4,c4,b5,c5 << 1 )
    Vector3D KCMBearing3 =  - KMBearing3y*(b5-b4)*e2ay - KMBearing3z*(c5-c4)*e2az  - CMBearing3*OMrelB5B4;

    // Spring-damper force in the coupling between the GEARBOX and the HHS
    Vector3D KCFBearing3 =  -(KFBearing3 * Bearing3S4_Bearing3S5 + CFBearing3*VrelBearing3S4_Bearing3S5);

    // Spring-damper torque in the coupling between the GEARBOX and the HHS ---> GBBearing9
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES ( -1 << b4,c4,b5,c5 << 1 )
    Vector3D KCMGBBearing9 =  - KMGBBearing9y*(b5-b4)*e2ay - KMGBBearing9z*(c5-c4)*e2az  - CMGBBearing9*OMrelB5B4;

    // Spring-damper force in the coupling between the GEARBOX and the HHS
    Vector3D KCFGBBearing9 =  -(KFGBBearing9 * GBBearing9S4_GBBearing9S5 + CFGBBearing9*VrelGBBearing9S4_GBBearing9S5);

//----------------------------------------------------------------------------------------
    // Spring-damper torque in the coupling between the HHS and the Generator
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES ( -1 << b6,c6,b5,c5 << 1 )
    Vector3D KCM56 = - KM56x*(a6-a5)* e2ax - KM56y*(b6-b5)* e2ay - KM56z*(c6-c5)* e2az - CM56*OMrelB6B5;
//----------------------------------------------------------------------------------------

// Spring-damper torques and forces in GEARBOX
//----------------------------------------------------------------------------------------
    // Spring-damper torque in the coupling between the GEARBOX and the Sun ---> GBBearing5
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES 
    Vector3D KCMGBBearing5 =  - KMGBBearing5y*(bSun)*e4y - KMGBBearing5z*(cSun)*e4z  - CMGBBearing5*OMrelBSunB4;
    // Spring-damper force in the coupling between the GEARBOX and the Sun
    Vector3D KCFGBBearing5 =  -(KFGBBearing5 * GBBearing5S4_GBBearing5Sun + CFGBBearing5*VrelGBBearing5S4_GBBearing5Sun);

    // Spring-damper torque in the coupling between the GEARBOX and the Sun ---> GBBearing6
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES 
    Vector3D KCMGBBearing6 =  - KMGBBearing6y*(bSun)*e4y - KMGBBearing6z*(cSun)*e4z  - CMGBBearing6*OMrelBSunB4;
    // Spring-damper force in the coupling between the GEARBOX and the Sun
    Vector3D KCFGBBearing6 =  -(KFGBBearing6 * GBBearing6S4_GBBearing6Sun + CFGBBearing6*VrelGBBearing6S4_GBBearing6Sun);
//----------------------------------------------------------------------------------------
    // Spring-damper torque in the coupling between the SOLID3 and the PLA1 ---> GBBearing1
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES 
    Vector3D KCMGBBearing1 =  - KMGBBearing1y*(bPla1)*e3y - KMGBBearing1z*(cPla1)*e3z  - CMGBBearing1*OMrelBPla1B3;
    // Spring-damper force in the coupling between the GEARBOX and the Pla1
    Vector3D KCFGBBearing1 =  -(KFGBBearing1 * GBBearing1S3_GBBearing1Pla1 + CFGBBearing1*VrelGBBearing1S3_GBBearing1Pla1);

    // Spring-damper torque in the coupling between the SOLID3 and the Pla2 ---> GBBearing2
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES 
    Vector3D KCMGBBearing2 =  - KMGBBearing2y*(bPla2)*e3y - KMGBBearing2z*(cPla2)*e3z  - CMGBBearing2*OMrelBPla2B3;
    // Spring-damper force in the coupling between the GEARBOX and the Pla2
    Vector3D KCFGBBearing2 =  -(KFGBBearing2 * GBBearing2S3_GBBearing2Pla2 + CFGBBearing2*VrelGBBearing2S3_GBBearing2Pla2);

    // Spring-damper torque in the coupling between the SOLID3 and the Pla3 ---> GBBearing3
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES 
    Vector3D KCMGBBearing3 =  - KMGBBearing3y*(bPla3)*e3y - KMGBBearing3z*(cPla3)*e3z  - CMGBBearing3*OMrelBPla3B3;
    // Spring-damper force in the coupling between the GEARBOX and the Pla3
    Vector3D KCFGBBearing3 =  -(KFGBBearing3 * GBBearing3S3_GBBearing3Pla3 + CFGBBearing3*VrelGBBearing3S3_GBBearing3Pla3);
//----------------------------------------------------------------------------------------
    // Spring-damper torque in the coupling between the GEARBOX and the SecSt ---> GBBearing7
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES 
    Vector3D KCMGBBearing7 =  - KMGBBearing7y*(bSecSt)*e4y - KMGBBearing7z*(cSecSt)*e4z  - CMGBBearing7*OMrelBSecStB4;
    // Spring-damper force in the coupling between the GEARBOX and the SecSt
    Vector3D KCFGBBearing7 =  -(KFGBBearing7 * GBBearing7S4_GBBearing7SecSt + CFGBBearing7*VrelGBBearing7S4_GBBearing7SecSt);

    // Spring-damper torque in the coupling between the GEARBOX and the SecSt ---> GBBearing8
    // WARNNING !!! THIS IS ONLY VALID FOR SMALL ROTATIONAL ANGLES 
    Vector3D KCMGBBearing8 =  - KMGBBearing8y*(bSecSt)*e4y - KMGBBearing8z*(cSecSt)*e4z  - CMGBBearing8*OMrelBSecStB4;
    // Spring-damper force in the coupling between the GEARBOX and the SecSt
    Vector3D KCFGBBearing8 =  -(KFGBBearing8 * GBBearing8S4_GBBearing8SecSt + CFGBBearing8*VrelGBBearing8S4_GBBearing8SecSt);

//---------------------------------------------------------------------------------------

    // External forces and torques exerted on the Hub
    Vector3D FHUB = *sys.new_Vector3D("FHUB",FHUBx,FHUBy,FHUBz,"xyz");
    Vector3D MHUB = *sys.new_Vector3D("MHUB",MHUBx,MHUBy,MHUBz,"xyz");

    // External Brake force exterted on the HHS Brake part (positive FBRAz*LB5y -> positive braking torque)
    Vector3D FBRA = *sys.new_Vector3D("FBRA",0,0,-FBRAz,"B2a");

    // Internal Generator-Stator torque exterted on the Stator
    Vector3D TGEN = *sys.new_Vector3D("TGEN",TGENx,0,0,"B6");

    // Action-Reaction forces of the silent-blocks (exerted on the Gear-Box and Stator respectively)
    Vector3D FS1 = KF24 * SilentBlock1S4_SilentBlock1S2 + CF24 * VrelSilentBlock1S4;
    Vector3D FS2 = KF24 * SilentBlock2S4_SilentBlock2S2 + CF24 * VrelSilentBlock2S4;
    Vector3D FS3 = KF27 * SilentBlock3S7_SilentBlock3S2 + CF27 * VrelSilentBlock3S7;
    Vector3D FS4 = KF27 * SilentBlock4S7_SilentBlock4S2 + CF27 * VrelSilentBlock4S7;
    Vector3D FS5 = KF27 * SilentBlock5S7_SilentBlock5S2 + CF27 * VrelSilentBlock5S7;
    Vector3D FS6 = KF27 * SilentBlock6S7_SilentBlock6S2 + CF27 * VrelSilentBlock6S7;

// -----------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// EXTERNAL FORCES-TORQUES APPLIED TO THE BEARINGS
// --------------------------------------------------------------------------------

    // External force and torque --> Bearing1
    symbol_numeric FBearing1x = *sys.new_Input("FBearing1x",0.0);
    symbol_numeric FBearing1y = *sys.new_Input("FBearing1y",0.0);
    symbol_numeric FBearing1z = *sys.new_Input("FBearing1z",0.0);
    symbol_numeric MBearing1x = *sys.new_Input("MBearing1x",0.0);
    symbol_numeric MBearing1y = *sys.new_Input("MBearing1y",0.0);
    symbol_numeric MBearing1z = *sys.new_Input("MBearing1z",0.0);
    
    Vector3D FBearing1 = *sys.new_Vector3D("FBearing1",FBearing1x,FBearing1y,FBearing1z,"B2");
    Vector3D MBearing1 = *sys.new_Vector3D("MBearing1",MBearing1x,MBearing1y,MBearing1z,"B2");

    // External force and torque --> Bearing2
    symbol_numeric FBearing2x = *sys.new_Input("FBearing2x",0.0);
    symbol_numeric FBearing2y = *sys.new_Input("FBearing2y",0.0);
    symbol_numeric FBearing2z = *sys.new_Input("FBearing2z",0.0);
    symbol_numeric MBearing2x = *sys.new_Input("MBearing2x",0.0);
    symbol_numeric MBearing2y = *sys.new_Input("MBearing2y",0.0);
    symbol_numeric MBearing2z = *sys.new_Input("MBearing2z",0.0);
    
    Vector3D FBearing2 = *sys.new_Vector3D("FBearing2",FBearing2x,FBearing2y,FBearing2z,"B3");
    Vector3D MBearing2 = *sys.new_Vector3D("MBearing2",MBearing2x,MBearing2y,MBearing2z,"B3");

    // External force and torque --> Bearing3
    symbol_numeric FBearing3x = *sys.new_Input("FBearing3x",0.0);
    symbol_numeric FBearing3y = *sys.new_Input("FBearing3y",0.0);
    symbol_numeric FBearing3z = *sys.new_Input("FBearing3z",0.0);
    symbol_numeric MBearing3x = *sys.new_Input("MBearing3x",0.0);
    symbol_numeric MBearing3y = *sys.new_Input("MBearing3y",0.0); 
    symbol_numeric MBearing3z = *sys.new_Input("MBearing3z",0.0);
    
    Vector3D FBearing3 = *sys.new_Vector3D("FBearing3",FBearing3x,FBearing3y,FBearing3z,"B4");
    Vector3D MBearing3 = *sys.new_Vector3D("MBearing3",MBearing3x,MBearing3y,MBearing3z,"B4");

    // External force and torque --> GBBearing1
    symbol_numeric FGBBearing1x = *sys.new_Input("FGBBearing1x",0.0);
    symbol_numeric FGBBearing1y = *sys.new_Input("FGBBearing1y",0.0);
    symbol_numeric FGBBearing1z = *sys.new_Input("FGBBearing1z",0.0);
    symbol_numeric MGBBearing1x = *sys.new_Input("MGBBearing1x",0.0);
    symbol_numeric MGBBearing1y = *sys.new_Input("MGBBearing1y",0.0);
    symbol_numeric MGBBearing1z = *sys.new_Input("MGBBearing1z",0.0);
    
    Vector3D FGBBearing1 = *sys.new_Vector3D("FGBBearing1",FGBBearing1x,FGBBearing1y,FGBBearing1z,"B3");
    Vector3D MGBBearing1 = *sys.new_Vector3D("MGBBearing1",MGBBearing1x,MGBBearing1y,MGBBearing1z,"B3");

    // External force and torque --> GBBearing2
    symbol_numeric FGBBearing2x = *sys.new_Input("FGBBearing2x",0.0);
    symbol_numeric FGBBearing2y = *sys.new_Input("FGBBearing2y",0.0);
    symbol_numeric FGBBearing2z = *sys.new_Input("FGBBearing2z",0.0);
    symbol_numeric MGBBearing2x = *sys.new_Input("MGBBearing2x",0.0);
    symbol_numeric MGBBearing2y = *sys.new_Input("MGBBearing2y",0.0);
    symbol_numeric MGBBearing2z = *sys.new_Input("MGBBearing2z",0.0);
    
    Vector3D FGBBearing2 = *sys.new_Vector3D("FGBBearing2",FGBBearing2x,FGBBearing2y,FGBBearing2z,"B3");
    Vector3D MGBBearing2 = *sys.new_Vector3D("MGBBearing2",MGBBearing2x,MGBBearing2y,MGBBearing2z,"B3");

    // External force and torque --> GBBearing3
    symbol_numeric FGBBearing3x = *sys.new_Input("FGBBearing3x",0.0);
    symbol_numeric FGBBearing3y = *sys.new_Input("FGBBearing3y",0.0);
    symbol_numeric FGBBearing3z = *sys.new_Input("FGBBearing3z",0.0);
    symbol_numeric MGBBearing3x = *sys.new_Input("MGBBearing3x",0.0);
    symbol_numeric MGBBearing3y = *sys.new_Input("MGBBearing3y",0.0);
    symbol_numeric MGBBearing3z = *sys.new_Input("MGBBearing3z",0.0);
    
    Vector3D FGBBearing3 = *sys.new_Vector3D("FGBBearing3",FGBBearing3x,FGBBearing3y,FGBBearing3z,"B3");
    Vector3D MGBBearing3 = *sys.new_Vector3D("MGBBearing3",MGBBearing3x,MGBBearing3y,MGBBearing3z,"B3");

    // External force and torque --> GBBearing4
    symbol_numeric FGBBearing4x = *sys.new_Input("FGBBearing4x",0.0);
    symbol_numeric FGBBearing4y = *sys.new_Input("FGBBearing4y",0.0);
    symbol_numeric FGBBearing4z = *sys.new_Input("FGBBearing4z",0.0);
    symbol_numeric MGBBearing4x = *sys.new_Input("MGBBearing4x",0.0);
    symbol_numeric MGBBearing4y = *sys.new_Input("MGBBearing4y",0.0);
    symbol_numeric MGBBearing4z = *sys.new_Input("MGBBearing4z",0.0);
    
    Vector3D FGBBearing4 = *sys.new_Vector3D("FGBBearing4",FGBBearing4x,FGBBearing4y,FGBBearing4z,"B3");
    Vector3D MGBBearing4 = *sys.new_Vector3D("MGBBearing4",MGBBearing4x,MGBBearing4y,MGBBearing4z,"B3");

    // External force and torque --> GBBearing5
    symbol_numeric FGBBearing5x = *sys.new_Input("FGBBearing5x",0.0);
    symbol_numeric FGBBearing5y = *sys.new_Input("FGBBearing5y",0.0);
    symbol_numeric FGBBearing5z = *sys.new_Input("FGBBearing5z",0.0);
    symbol_numeric MGBBearing5x = *sys.new_Input("MGBBearing5x",0.0);
    symbol_numeric MGBBearing5y = *sys.new_Input("MGBBearing5y",0.0);
    symbol_numeric MGBBearing5z = *sys.new_Input("MGBBearing5z",0.0);
    
    Vector3D FGBBearing5 = *sys.new_Vector3D("FGBBearing5",FGBBearing5x,FGBBearing5y,FGBBearing5z,"B4");
    Vector3D MGBBearing5 = *sys.new_Vector3D("MGBBearing5",MGBBearing5x,MGBBearing5y,MGBBearing5z,"B4");

    // External force and torque --> GBBearing6
    symbol_numeric FGBBearing6x = *sys.new_Input("FGBBearing6x",0.0);
    symbol_numeric FGBBearing6y = *sys.new_Input("FGBBearing6y",0.0);
    symbol_numeric FGBBearing6z = *sys.new_Input("FGBBearing6z",0.0);
    symbol_numeric MGBBearing6x = *sys.new_Input("MGBBearing6x",0.0);
    symbol_numeric MGBBearing6y = *sys.new_Input("MGBBearing6y",0.0);
    symbol_numeric MGBBearing6z = *sys.new_Input("MGBBearing6z",0.0);
    
    Vector3D FGBBearing6 = *sys.new_Vector3D("FGBBearing6",FGBBearing6x,FGBBearing6y,FGBBearing6z,"B4");
    Vector3D MGBBearing6 = *sys.new_Vector3D("MGBBearing6",MGBBearing6x,MGBBearing6y,MGBBearing6z,"B4");

    // External force and torque --> GBBearing7
    symbol_numeric FGBBearing7x = *sys.new_Input("FGBBearing7x",0.0);
    symbol_numeric FGBBearing7y = *sys.new_Input("FGBBearing7y",0.0);
    symbol_numeric FGBBearing7z = *sys.new_Input("FGBBearing7z",0.0);
    symbol_numeric MGBBearing7x = *sys.new_Input("MGBBearing7x",0.0);
    symbol_numeric MGBBearing7y = *sys.new_Input("MGBBearing7y",0.0);
    symbol_numeric MGBBearing7z = *sys.new_Input("MGBBearing7z",0.0);
    
    Vector3D FGBBearing7 = *sys.new_Vector3D("FGBBearing7",FGBBearing7x,FGBBearing7y,FGBBearing7z,"B4");
    Vector3D MGBBearing7 = *sys.new_Vector3D("MGBBearing7",MGBBearing7x,MGBBearing7y,MGBBearing7z,"B4");

    // External force and torque --> GBBearing8
    symbol_numeric FGBBearing8x = *sys.new_Input("FGBBearing8x",0.0);
    symbol_numeric FGBBearing8y = *sys.new_Input("FGBBearing8y",0.0);
    symbol_numeric FGBBearing8z = *sys.new_Input("FGBBearing8z",0.0);
    symbol_numeric MGBBearing8x = *sys.new_Input("MGBBearing8x",0.0);
    symbol_numeric MGBBearing8y = *sys.new_Input("MGBBearing8y",0.0);
    symbol_numeric MGBBearing8z = *sys.new_Input("MGBBearing8z",0.0);
    
    Vector3D FGBBearing8 = *sys.new_Vector3D("FGBBearing8",FGBBearing8x,FGBBearing8y,FGBBearing8z,"B4");
    Vector3D MGBBearing8 = *sys.new_Vector3D("MGBBearing8",MGBBearing8x,MGBBearing8y,MGBBearing8z,"B4");

    // External force and torque --> GBBearing9
    symbol_numeric FGBBearing9x = *sys.new_Input("FGBBearing9x",0.0);
    symbol_numeric FGBBearing9y = *sys.new_Input("FGBBearing9y",0.0);
    symbol_numeric FGBBearing9z = *sys.new_Input("FGBBearing9z",0.0);
    symbol_numeric MGBBearing9x = *sys.new_Input("MGBBearing9x",0.0);
    symbol_numeric MGBBearing9y = *sys.new_Input("MGBBearing9y",0.0);
    symbol_numeric MGBBearing9z = *sys.new_Input("MGBBearing9z",0.0);
    
    Vector3D FGBBearing9 = *sys.new_Vector3D("FGBBearing9",FGBBearing9x,FGBBearing9y,FGBBearing9z,"B4");
    Vector3D MGBBearing9 = *sys.new_Vector3D("MGBBearing9",MGBBearing9x,MGBBearing9y,MGBBearing9z,"B4");
// -----------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------


    cout << "Vectors needed to take diferent Jacobians" << endl;
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------- Vectors needed to take diferent Jacobians-----------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    symbol_numeric lambda1= *sys.new_Joint_Unknown("lambda1",0.0);
    symbol_numeric lambda2= *sys.new_Joint_Unknown("lambda2",0.0);
    symbol_numeric lambda3= *sys.new_Joint_Unknown("lambda3",0.0);
    symbol_numeric lambda4= *sys.new_Joint_Unknown("lambda4",0.0);
    symbol_numeric lambda5= *sys.new_Joint_Unknown("lambda5",0.0);
    symbol_numeric lambda6= *sys.new_Joint_Unknown("lambda6",0.0);


   cout << "Kinematic Equations" << endl;
// -----------------------------------------------------------------------------------------------
// ----------------------------------- Kinematic Equations ---------------------------------------
// -----------------------------------------------------------------------------------------------    

    ex R_Car = LGr1; //Planet Carrier
    ex R_Pla = R_Car * Z_Pla/(Z_Pla + Z_Sun); // Planets
    ex R_Sun = R_Car * Z_Sun/(Z_Pla + Z_Sun); //Sun 
    ex R_Ring  = R_Car + R_Pla; // Ring 
    ex L_Sun_SecSt = sqrt(LGy1*LGy1+LGz1*LGz1); 
    ex R_SecSt_1 = L_Sun_SecSt * Z_SecSt1/(Z_SecSt1 + Z_SecSt2);
    ex R_SecSt_2 = L_Sun_SecSt * Z_SecSt2/(Z_SecSt1 + Z_SecSt2);
    ex L_SecSt_ThiSt = sqrt((LGy2-LGy1)*(LGy2-LGy1)+(LGz2-LGz1)*(LGz2-LGz1)); 
    ex R_ThiSt_1 = L_SecSt_ThiSt * Z_ThiSt1 / (Z_ThiSt1 + Z_ThiSt2);
    ex R_ThiSt_2 = L_SecSt_ThiSt * Z_ThiSt2 / (Z_ThiSt1 + Z_ThiSt2);


    Matrix Phi(6,1);
    Phi(0,0) = R_Ring*(a4-a4) - R_Car*(a3-a4) - R_Pla*(a3+aPla1-a4);
    Phi(1,0) = R_Ring*(a4-a4) - R_Car*(a3-a4) - R_Pla*(a3+aPla2-a4);
    Phi(2,0) = R_Ring*(a4-a4) - R_Car*(a3-a4) - R_Pla*(a3+aPla3-a4);
    Phi(3,0) = R_Sun*aSun - R_Car*(a3-a4) + R_Pla*(a3+aPla1-a4);
    Phi(4,0) = R_SecSt_1*aSun + R_SecSt_2*aSecSt;
    Phi(5,0) = R_ThiSt_1*aSecSt + R_ThiSt_2*(a5-a4);



    cout << "Vectors needed to take diferent Jacobians" << endl;
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------- Vectors needed to take diferent Jacobians-----------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


    Matrix q = sys.Coordinates();
    Matrix dq = sys.Velocities();
    Matrix ddq = sys.Accelerations();
    Matrix pars = sys.Parameters();
    Matrix inps = sys.Inputs();
    Matrix unks = sys.Joint_Unknowns();


   cout << "Dynamic Equations" << endl;
// -----------------------------------------------------------------------------------------------
// ----------------------------------- Dynamic Equations -----------------------------------------
// -----------------------------------------------------------------------------------------------

    Matrix Dynamic_Equations(dq.rows(),1);

	for (int i=0; (i < dq.rows()); ++i) {
 	symbol_numeric dq_i;
 	dq_i=ex_to<symbol_numeric>(dq(i,0));
 	Dynamic_Equations (i,0) = 0

//    Inertial Forces and Torques
    + Fi_O2 * sys.diff(VabsO2,dq_i) + Mi_O2 * sys.diff(Omega2,dq_i)
    + Fi_O3 * sys.diff(VabsO3,dq_i) + Mi_O3 * sys.diff(Omega3,dq_i)
    + Fi_O4 * sys.diff(VabsO4,dq_i) + Mi_O4 * sys.diff(Omega4,dq_i)
    + Fi_O5 * sys.diff(VabsO5,dq_i) + Mi_O5 * sys.diff(Omega5,dq_i)
    + Fi_O6 * sys.diff(VabsO6,dq_i) + Mi_O6 * sys.diff(Omega6,dq_i)
    + Fi_O7 * sys.diff(VabsO7,dq_i) + Mi_O7 * sys.diff(Omega7,dq_i)
    + Fi_OSun * sys.diff(VabsOSun,dq_i) + Mi_OSun * sys.diff(OmegaSun,dq_i)
    + Fi_OPla1 * sys.diff(VabsOPla1,dq_i) + Mi_OPla1 * sys.diff(OmegaPla1,dq_i)   
    + Fi_OPla2 * sys.diff(VabsOPla2,dq_i) + Mi_OPla2 * sys.diff(OmegaPla2,dq_i)   
    + Fi_OPla3 * sys.diff(VabsOPla3,dq_i) + Mi_OPla3 * sys.diff(OmegaPla3,dq_i)
    + Fi_OSecSt * sys.diff(VabsOSecSt,dq_i) + Mi_OSecSt * sys.diff(OmegaSecSt,dq_i)

//  Gravitational Forces
    + F_grav_2 * sys.diff(VabsG2,dq_i)
    + F_grav_3 * sys.diff(VabsG3,dq_i)
    + F_grav_4 * sys.diff(VabsG4,dq_i)
    + F_grav_5 * sys.diff(VabsG5,dq_i)
    + F_grav_6 * sys.diff(VabsG6,dq_i)
    + F_grav_7 * sys.diff(VabsG7,dq_i)
    + F_grav_Sun * sys.diff(VabsGSun,dq_i)
    + F_grav_Pla1 * sys.diff(VabsGPla1,dq_i)    
    + F_grav_Pla2 * sys.diff(VabsGPla2,dq_i)    
    + F_grav_Pla3 * sys.diff(VabsGPla3,dq_i)   
    + F_grav_SecSt * sys.diff(VabsGSecSt,dq_i) 

//  Spring damper on the translation of the YAW Bearing of the Nacelle
    + KCF12 * sys.diff(VabsO2,dq_i) //- KCF12 * sys.diff(VabsO1,dq_i)
//  Spring damper on the YAW Bearing of the Nacelle
    + KCM12 * sys.diff(Omega2,dq_i) //- KCM12 * sys.diff(Omega1,dq_i)

//------------------------------------------------------------------------
//  Spring damper on the translation coupling between the NACELLE and the LSS
    + KCFBearing1 * sys.diff(VrelBearing1S2_Bearing1S3_abs,dq_i)
//  Spring damper on the rotation coupling between the NACELLE and the LSS
    + KCMBearing1 * sys.diff(OMrelB3B2,dq_i)

//-------------------------------------------------------------------------
//  Spring damper on the translation coupling between the GEARBOX (SOLID4) and the HHS
    + KCFBearing2 * sys.diff(VrelBearing2S3_Bearing2S4_abs,dq_i)
//  Spring damper on the rotation coupling between the GEARBOX (SOLID4) and the HHS
    + KCMBearing2 * sys.diff(OMrelB4B3,dq_i)

//  Spring damper on the translation coupling between the GEARBOX (SOLID4) and the HHS
    + KCFGBBearing4 * sys.diff( VrelGBBearing4S3_GBBearing4S4_abs,dq_i) 
//  Spring damper on the rotation coupling between the GEARBOX (SOLID4) and the HHS
    + KCMGBBearing4 * sys.diff(OMrelB4B3,dq_i) 

//-------------------------------------------------------------------------
//  Spring damper on the translation coupling between the GEARBOX (SOLID4) and the HHS
    + KCFBearing3 * sys.diff(VrelBearing3S4_Bearing3S5_abs,dq_i) 
//  Spring damper on the rotation coupling between the GEARBOX (SOLID4) and the HHS
    + KCMBearing3 * sys.diff(OMrelB5B4,dq_i)

//  Spring damper on the translation coupling between the GEARBOX (SOLID4) and the HHS
    + KCFGBBearing9 * sys.diff(VrelGBBearing9S4_GBBearing9S5_abs,dq_i)
//  Spring damper on the rotation coupling between the GEARBOX (SOLID4) and the HHS
    + KCMGBBearing9 * sys.diff(OMrelB5B4,dq_i)

//-------------------------------------------------------------------------
//  Spring damper on the rotation coupling between the HHS and the Generator
//    + KCM56 * sys.diff(Omega6,dq_i) - KCM56 * sys.diff(Omega5,dq_i)
    + KCM56 * sys.diff(OMrelB6B5,dq_i) 

//-------------------------------------------------------------------------
//  Spring damper on the translation coupling between the GEARBOX (SOLID4) and the Sun
    + KCFGBBearing5 * sys.diff(VrelGBBearing5S4_GBBearing5Sun_abs,dq_i)
//  Spring damper on the rotation coupling between the GEARBOX (SOLID4) and the Sun
    + KCMGBBearing5 * sys.diff(OMrelBSunB4,dq_i)

//  Spring damper on the translation coupling between the GEARBOX (SOLID4) and the Sun
    + KCFGBBearing6 * sys.diff(VrelGBBearing6S4_GBBearing6Sun_abs,dq_i)
//  Spring damper on the rotation coupling between the GEARBOX (SOLID4) and the Sun
    + KCMGBBearing6 * sys.diff(OMrelBSunB4,dq_i)

//-------------------------------------------------------------------------
//  Spring damper on the translation coupling between the SOLID3 and the Pla1
    + KCFGBBearing1 * sys.diff(VrelGBBearing1S3_GBBearing1Pla1_abs,dq_i)
//  Spring damper on the rotation coupling between the SOLID3 and the Pla1
    + KCMGBBearing1 * sys.diff(OMrelBPla1B3,dq_i) 

//-------------------------------------------------------------------------
//  Spring damper on the translation coupling between the SOLID3 and the Pla2
    + KCFGBBearing2 * sys.diff(VrelGBBearing2S3_GBBearing2Pla2_abs,dq_i)
//  Spring damper on the rotation coupling between the SOLID3 and the Pla2
    + KCMGBBearing2 * sys.diff(OMrelBPla2B3,dq_i)

//-------------------------------------------------------------------------
//  Spring damper on the translation coupling between the SOLID3 and the Pla3
    + KCFGBBearing3 * sys.diff(VrelGBBearing3S3_GBBearing3Pla3_abs,dq_i)
//  Spring damper on the rotation coupling between the SOLID3 and the Pla3
    + KCMGBBearing3 * sys.diff(OMrelBPla3B3,dq_i)

//-------------------------------------------------------------------------
//  Spring damper on the translation coupling between the GEARBOX (SOLID4) and the SecSt
    + KCFGBBearing7 * sys.diff(VrelGBBearing7S4_GBBearing7SecSt_abs,dq_i)
//  Spring damper on the rotation coupling between the GEARBOX (SOLID4) and the SecSt
    + KCMGBBearing7 * sys.diff(OMrelBSecStB4,dq_i)

//  Spring damper on the translation coupling between the GEARBOX (SOLID4) and the SecSt
    + KCFGBBearing8 * sys.diff(VrelGBBearing8S4_GBBearing8SecSt_abs,dq_i)
//  Spring damper on the rotation coupling between the GEARBOX (SOLID4) and the SecSt
    + KCMGBBearing8 * sys.diff(OMrelBSecStB4,dq_i)

//-------------------------------------------------------------------------
//  Action-Reaction forces in the silent-blocks
    // The sign MUST be negative for FS_j to be coherent with the relative velocity VrelSilentBlock_j
    - FS1 * sys.diff(VrelSilentBlock1S4_abs,dq_i)
    - FS2 * sys.diff(VrelSilentBlock2S4_abs,dq_i)
    - FS3 * sys.diff(VrelSilentBlock3S7_abs,dq_i)
    - FS4 * sys.diff(VrelSilentBlock4S7_abs,dq_i)   
    - FS5 * sys.diff(VrelSilentBlock5S7_abs,dq_i)
    - FS6 * sys.diff(VrelSilentBlock6S7_abs,dq_i)

//  Action-Reaction Torque between the generator and stator
    + TGEN * sys.diff(Omega7,dq_i) - TGEN * sys.diff(Omega6,dq_i)

//  Wind Forces and Torques on the Hub (remove when the aerodynamic model is present)
    + FHUB * sys.diff(VabsO3,dq_i) + MHUB * sys.diff(Omega3,dq_i)

//  Brake Force and Torque on the HHS
    //+ FBRA * sys.diff(VabsBrakeS5,dq_i)- FBRA * sys.diff(VabsBrakeS4,dq_i)
     + FBRA * sys.diff(VrelBrakeS4_BrakeS5,dq_i)
//-------------------------------------------------------------------------
// External forces and torques

    // External force and torque --> Bearing1
    + FBearing1 * sys.diff(VrelBearing1S2_Bearing1S3_abs,dq_i) + MBearing1 * sys.diff(OMrelB3B2,dq_i)

    // External force and torque --> Bearing2
    + FBearing2 * sys.diff(VrelBearing2S3_Bearing2S4_abs,dq_i) + MBearing2 * sys.diff(OMrelB4B3,dq_i)

    // External force and torque --> Bearing3
    + FBearing3 * sys.diff(VrelBearing3S4_Bearing3S5_abs,dq_i) + MBearing3 * sys.diff(OMrelB5B4,dq_i)

   // External force and torque --> GBBearing1
    + FGBBearing1 * sys.diff(VrelGBBearing1S3_GBBearing1Pla1_abs,dq_i) + MGBBearing1 * sys.diff(OMrelBPla1B3,dq_i)

   // External force and torque --> GBBearing2
    + FGBBearing2 * sys.diff(VrelGBBearing2S3_GBBearing2Pla2_abs,dq_i) + MGBBearing2 * sys.diff(OMrelBPla2B3,dq_i)

   // External force and torque --> GBBearing3
    + FGBBearing3 * sys.diff(VrelGBBearing3S3_GBBearing3Pla3_abs,dq_i) + MGBBearing3 * sys.diff(OMrelBPla3B3,dq_i)

   // External force and torque --> GBBearing4
    + FGBBearing4 * sys.diff(VrelGBBearing4S3_GBBearing4S4_abs,dq_i) + MGBBearing4 * sys.diff(OMrelB4B3,dq_i)

   // External force and torque --> GBBearing5
    + FGBBearing5 * sys.diff(VrelGBBearing5S4_GBBearing5Sun_abs,dq_i) + MGBBearing5 * sys.diff(OMrelBSunB4,dq_i)

   // External force and torque --> GBBearing6
    + FGBBearing6 * sys.diff(VrelGBBearing6S4_GBBearing6Sun_abs,dq_i) + MGBBearing6 * sys.diff(OMrelBSunB4,dq_i)

   // External force and torque --> GBBearing7
    + FGBBearing7 * sys.diff(VrelGBBearing7S4_GBBearing7SecSt_abs,dq_i) + MGBBearing7 * sys.diff(OMrelBSecStB4,dq_i)

   // External force and torque --> GBBearing8
    + FGBBearing8 * sys.diff(VrelGBBearing8S4_GBBearing8SecSt_abs,dq_i) + MGBBearing8 * sys.diff(OMrelBSecStB4,dq_i)

   // External force and torque --> GBBearing9
    + FGBBearing9 * sys.diff(VrelGBBearing9S4_GBBearing9S5_abs,dq_i) + MGBBearing9 * sys.diff(OMrelB5B4,dq_i)
    ;
}

    cout << "Output Vector" << endl;
// -----------------------------------------------------------------------------------------------
// ----------------------------------- Output Vector ------------------------------------------
// -----------------------------------------------------------------------------------------------

    //Vector3D ez = *sys.new_Vector3D("ez",0,0,1,"xyz");

	cout << "Energy Equations" << endl;
	Matrix Energy(1,1);
	Energy(0,0)=0;
	sys.new_Matrix("Energy",Energy);


/*        vector < symbol_numeric * > Coordinates = sys.get_Coordinates();
        vector < symbol_numeric * > Velocities = sys.get_Velocities();
        vector < symbol_numeric * > Accelerations = sys.get_Accelerations();
        vector < symbol_numeric * > Joint_Unknowns = sys.get_Joint_Unknowns();*/

/*    Matrix Output(Coordinates.size()+Velocities.size()+Joint_Unknowns.size()+3,1);
    for (int i=0; (i < Coordinates.size()); ++i){
        Output(i,0)=*Coordinates[i];
        }

    for (int i=0; (i < Velocities.size()); ++i){
        Output(Coordinates.size()+i,0)=*Velocities[i];
        }

    Output(Coordinates.size()+Velocities.size(),0) = lambda1; //Joint Unknowns
    Output(Coordinates.size()+Velocities.size()+1,0) = Total_Energy; //Total_Energy
    Output(Coordinates.size()+Velocities.size()+2,0) = *da3; //angular velocity of the LSS in the shaft direction
    Output(Coordinates.size()+Velocities.size()+3,0) = *da5; //angular velocity of the HSS in the shaft direction*/

    Matrix Output(6,1); 
    Output(0,0) = a3; 
    Output(1,0) = a5;
    Output(2,0) = *da3; //angular velocity of the LSS in the shaft direction
    Output(3,0) = *da5; //angular velocity of the HSS in the shaft direction
    Output(4,0) = a5/a3; 
    Output(5,0) = *da5/(*da3); 
    sys.new_Matrix("Output",Output);

// -----------------------------------------------------------------------------------------------
// ----------------------------------- Matrix Calculation ----------------------------------------
// -----------------------------------------------------------------------------------------------

	cout << "Matrix Calculation" << endl;

        //sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);
        sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations,sys, METHOD);


// ************************************************************************************************
// 	Export C code for Direct Simulation 
// ************************************************************************************************

	cout << "Export C code for Direct Simulation " << endl;
    sys.export_Dynamic_Simulation(sys, ORDER , MAPLE);
    
    //sys.export_Dynamic_Simulation(sys, ORDER , MAPLE, PROBLEM_TYPE);

	//sys.export_Output(sys, ORDER , MAPLE);

// -----------------------------------------------------------------------------------------------
// --------------------------- Export Point, Base and Frame Diagrams -------------------------------
// -----------------------------------------------------------------------------------------------

        #ifdef GRAPHVIZ 
	cout << "Export Point, Base and Frame Diagrams" << endl;

	sys.export_Graphviz_dot (  );

    	system("dot -Tps   base_diagram.dot -o plain_base_diagram.eps");
    	system("latex base_diagram.tex");
    	system("dvips base_diagram.dvi -o base_diagram.eps");

    	system("dot -Tps   point_diagram.dot -o plain_point_diagram.eps");
     	system("latex point_diagram.tex");
    	system("dvips point_diagram.dvi -o point_diagram.eps");

    	system("dot -Tps   frame_diagram.dot -o plain_frame_diagram.eps");
    	system("latex frame_diagram.tex");
    	system("dvips base_diagram.dvi -o base_diagram.eps");
        #endif


//-----------------------------------------------------------------------------------------------
//--------------------------- Export environment vector -------------------------------
//-----------------------------------------------------------------------------------------------

	cout << "Export ENVIRONMENT file " << endl;

	sys.export_environment_m (  );


// ------------------------------------------------------------------------------------------------
//---------------------Export C++ code for Openscenegraph --------------------------------------------
// ------------------------------------------------------------------------------------------------

	cout << "Export OpenSceneGraph files " << endl;

	sys.export_open_scene_graph ( );
// ------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/*    lst l;

    l = b2,L2x,L2z,L3x1,L3x2,L4x,L4y,L4z,L6x,
        LS4x,LS4y,LS4z,LS7x1,LS7x2,LS7y1,LS7y2,LS7z,
        LS2x1,LS2y1,LS2z1,LS2x2,LS2x3,LS2y2,LS2y3,LS2z2,
	LGx1,LGx2,LGx3,LGx4,LGx5,LGx6,LGx7,LGx8,
        LGy1,LGy2,LGz1,LGz2,LGr1,
        Z_Ring,Z_Sun,Z_Pla,Z_SecSt1,Z_SecSt2, Z_ThiSt1,Z_ThiSt2,

   l =  x2,*dx2,*ddx2,      y2,*dy2,*ddy2,      c2,*dc2,*ddc2,
        a3,*da3,*dda3,      b3,*db3,*ddb3,      c3,*dc3,*ddc3,      a3,*da3,*dda3,      b3,*db3,*ddb3,      c3,*dc3,*ddc3,
        x4,*dx4,*ddx4,      y4,*dy4,*ddy4,      z4,*dz4,*ddz4,      a4,*da4,*dda4,      b4,*db4,*ddb4,      c4,*dc4,*ddc4,
        x5,*dx5,*ddx5,      y5,*dy5,*ddy5,      z5,*dz5,*ddz5,      a5,*da5,*dda5,      b5,*db5,*ddb5,      c5,*dc5,*ddc5,
        a6,*da6,*dda6,      b6,*db6,*ddb6,      c6,*dc6,*ddc6,
        a7,*da7,*dda7,

        xSun,*dxSun,*ddxSun,      ySun,*dySun,*ddySun,      zSun,*dzSun,*ddzSun,      aSun,*daSun,*ddaSun,      bSun,*dbSun,*ddbSun,      cSun,*dcSun,*ddcSun,  
        xPla1,*dxPla1,*ddxPla1,   yPla1,*dyPla1,*ddyPla1,   zPla1,*dzPla1,*ddzPla1,   aPla1,*daPla1,*ddaPla1,   bPla1,*dbPla1,*ddbPla1,   cPla1,*dcPla1,*ddcPla1,
        xPla2,*dxPla2,*ddxPla2,   yPla2,*dyPla2,*ddyPla2,   zPla2,*dzPla2,*ddzPla2,   aPla2,*daPla2,*ddaPla2,   bPla2,*dbPla2,*ddbPla2,   cPla2,*dcPla2,*ddcPla2,
        xPla3,*dxPla3,*ddxPla3,   yPla3,*dyPla3,*ddyPla3,   zPla3,*dzPla3,*ddzPla3,   aPla3,*daPla3,*ddaPla3,   bPla3,*dbPla3,*ddbPla3,   cPla3,*dcPla3,*ddcPla3,      
        xSecSt,*dxSecSt,*ddxSecSt,   ySecSt,*dySecSt,*ddySecSt,   zSecSt,*dzSecSt,*ddzSecSt,   aSecSt,*daSecSt,*ddaSecSt,   bSecSt,*dbSecSt,*ddbSecSt,   cSecSt,*dcSecSt,*ddcSecSt,           

        FHUBx,FHUBy,FHUBz,MHUBx,MHUBy,MHUBz,FBRAz,TGENx;*/

        lst state;
        state =  a3,a5,*da3,*da5,*dda3,*dda5,
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
return 0;
}
  

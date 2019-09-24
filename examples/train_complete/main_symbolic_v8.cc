// ************************************************************************************************
// TRAIN ARESSE model developed with lib_3D_mec
// ************************************************************************************************
//
// Aitor Plaza November 2012 
//
//
// ************************************************************************************************


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

#ifdef PROCEDURE
    int C_EXPORT_AS_PROCEDURE=1;
#else
    int C_EXPORT_AS_PROCEDURE=0;
#endif
//*****************************************************************************************************************


using namespace GiNaC;
using namespace std;
	
// SYSTEM DEFINITION
// *****************************************************************************************************************	

void printError2(const char* arg){
	printf("%s\n", arg);
}	
	
    int main(int argc, char *argv[]) {

// *****************************************************************************************************************	

    cout << " " << endl;
    cout << "********************************************************" << endl;
    cout << "*             Train                                    *" << endl;
    cout << "*             COMPLETE v7 SPLINES & KALKER             *" << endl;
    cout << "********************************************************" << endl;
    cout << "      _____                 . . . . . o o o o o        " << endl;
    cout << "    __|[_]|__ ___________ _______    ____      o       " << endl;
    cout << "   |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.     " << endl;
    cout << "  _|________|_[_________]_[________]_|__|________)<    " << endl;
    cout << "    oo    oo ' oo     oo ' oo    oo ' oo 0000---oo     " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "*******************************************************" << endl;      
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
//	System definition
// ************************************************************************************************

     System sys(&printError2);


// ************************************************************************************************
//	Coordinate definition
// ************************************************************************************************
    symbol_numeric xWAG = *sys.new_Coordinate("xWAG","dxWAG","ddxWAG", 0.001,0.0,0.0);
    symbol_numeric yWAG = *sys.new_Coordinate("yWAG","dyWAG","ddyWAG", 0.0,0.0,0.0);
    symbol_numeric zWAG = *sys.new_Coordinate("zWAG","dzWAG","ddzWAG", 0.73962,0.0,0.0);
    symbol_numeric aWAG = *sys.new_Coordinate("aWAG","daWAG","ddaWAG", 0.0,0.0,0.0);
    symbol_numeric bWAG = *sys.new_Coordinate("bWAG","dbWAG","ddbWAG",-0.002,0.0,0.0);
    symbol_numeric cWAG = *sys.new_Coordinate("cWAG","dcWAG","ddcWAG",-0.0,0.0,0.0);

    symbol_numeric *dxWAG = sys.get_Velocity("dxWAG");
    symbol_numeric *dyWAG = sys.get_Velocity("dyWAG");
    symbol_numeric *dzWAG = sys.get_Velocity("dzWAG");
    symbol_numeric *daWAG = sys.get_Velocity("daWAG");
    symbol_numeric *dbWAG = sys.get_Velocity("dbWAG");
    symbol_numeric *dcWAG = sys.get_Velocity("dcWAG");

    symbol_numeric *ddxWAG = sys.get_Acceleration("ddxWAG");
    symbol_numeric *ddyWAG = sys.get_Acceleration("ddyWAG");
    symbol_numeric *ddzWAG = sys.get_Acceleration("ddzWAG");
    symbol_numeric *ddaWAG = sys.get_Acceleration("ddaWAG");
    symbol_numeric *ddbWAG = sys.get_Acceleration("ddbWAG");
    symbol_numeric *ddcWAG = sys.get_Acceleration("ddcWAG");

  
    // =====================================================================================================================================================================================
    // REAR SLIDER coordinates RSLD
    // =====================================================================================================================================================================================

    symbol_numeric cRSLD = *sys.new_Coordinate("cRSLD","dcRSLD","ddcRSLD",0.0 ,0.0,0.0);
    symbol_numeric *dcRSLD=sys.get_Velocity("dcRSLD");
    symbol_numeric *ddcRSLD=sys.get_Acceleration("ddcRSLD");
    // =====================================================================================================================================================================================
    // FRONT SLIDER coordinates FSLD
    // =====================================================================================================================================================================================

    symbol_numeric cFSLD = *sys.new_Coordinate("cFSLD","dcFSLD","ddcFSLD",0.0 ,0.0,0.0);
    symbol_numeric *dcFSLD=sys.get_Velocity("dcFSLD");
    symbol_numeric *ddcFSLD=sys.get_Acceleration("ddcFSLD");   



    
    // =====================================================================================================================================================================================
    // REAR BOGIE coordinates RBOG
    // =====================================================================================================================================================================================


    symbol_numeric zRBOG = *sys.new_Coordinate("zRBOG","dzRBOG","ddzRBOG",-0.124118,0.0,0.0);
    symbol_numeric aRBOG = *sys.new_Coordinate("aRBOG","daRBOG","ddaRBOG", 0.0,0.0,0.0);
    symbol_numeric bRBOG = *sys.new_Coordinate("bRBOG","dbRBOG","ddbRBOG", 0.002,0.0,0.0);

    symbol_numeric *dzRBOG=sys.get_Velocity("dzRBOG");
    symbol_numeric *daRBOG=sys.get_Velocity("daRBOG");
    symbol_numeric *dbRBOG=sys.get_Velocity("dbRBOG");

    symbol_numeric *ddzRBOG=sys.get_Acceleration("ddzRBOG");
    symbol_numeric *ddaRBOG=sys.get_Acceleration("ddaRBOG");
    symbol_numeric *ddbRBOG=sys.get_Acceleration("ddbRBOG");

 
    // =====================================================================================================================================================================================
    // FRONT BOGIE coordinates FBOG
    // =====================================================================================================================================================================================


    symbol_numeric zFBOG = *sys.new_Coordinate("zFBOG","dzFBOG","ddzFBOG",-0.1301,0.0,0.0);
    symbol_numeric aFBOG = *sys.new_Coordinate("aFBOG","daFBOG","ddaFBOG", 0.00,0.0,0.0);
    symbol_numeric bFBOG = *sys.new_Coordinate("bFBOG","dbFBOG","ddbFBOG", 0.002,0.0,0.0);

    symbol_numeric *dzFBOG=sys.get_Velocity("dzFBOG");
    symbol_numeric *daFBOG=sys.get_Velocity("daFBOG");
    symbol_numeric *dbFBOG=sys.get_Velocity("dbFBOG");

    symbol_numeric *ddzFBOG=sys.get_Acceleration("ddzFBOG");
    symbol_numeric *ddaFBOG=sys.get_Acceleration("ddaFBOG");
    symbol_numeric *ddbFBOG=sys.get_Acceleration("ddbFBOG");

   
    // =====================================================================================================================================================================================
    // REAR BOGIE WHEELSET coordinates
    // =====================================================================================================================================================================================

    //FRONT WHEELSET (RWHSF)

    symbol_numeric zRWHSF = *sys.new_Coordinate("zRWHSF","dzRWHSF","ddzRWHSF",0.0534323,0.0,0.0);
    symbol_numeric aRWHSF = *sys.new_Coordinate("aRWHSF","daRWHSF","ddaRWHSF",0.0,0.0,0.0);
    symbol_numeric bRWHSF = *sys.new_Coordinate("bRWHSF","dbRWHSF","ddbRWHSF",0.048187,0.0,0.0);
    
    symbol_numeric *dzRWHSF=sys.get_Velocity("dzRWHSF"); symbol_numeric *daRWHSF=sys.get_Velocity("daRWHSF"); symbol_numeric *dbRWHSF=sys.get_Velocity("dbRWHSF");
    symbol_numeric *ddzRWHSF=sys.get_Acceleration("ddzRWHSF"); symbol_numeric *ddaRWHSF=sys.get_Acceleration("ddaRWHSF"); symbol_numeric *ddbRWHSF=sys.get_Acceleration("ddbRWHSF");
 
    //REAR WHEELSET (RWHSR)

    symbol_numeric zRWHSR = *sys.new_Coordinate("zRWHSR","dzRWHSR","ddzRWHSR",0.0535459,0.0,0.0);
    symbol_numeric aRWHSR = *sys.new_Coordinate("aRWHSR","daRWHSR","ddaRWHSR",0.0,0.0,0.0);
    symbol_numeric bRWHSR = *sys.new_Coordinate("bRWHSR","dbRWHSR","ddbRWHSR",0.048187,0.0,0.0);

    symbol_numeric *dzRWHSR=sys.get_Velocity("dzRWHSR"); symbol_numeric *daRWHSR=sys.get_Velocity("daRWHSR"); symbol_numeric *dbRWHSR=sys.get_Velocity("dbRWHSR");
    symbol_numeric *ddzRWHSR=sys.get_Acceleration("ddzRWHSR"); symbol_numeric *ddaRWHSR=sys.get_Acceleration("ddaRWHSR"); symbol_numeric *ddbRWHSR=sys.get_Acceleration("ddbRWHSR");

    // =====================================================================================================================================================================================
    // FRONT BOGIE WHEELSET coordinates
    // =====================================================================================================================================================================================

    //FRONT WHEELSET (FWHSF)

    symbol_numeric zFWHSF = *sys.new_Coordinate("zFWHSF","dzFWHSF","ddzFWHSF",0.03959,0.0,0.0);
    symbol_numeric aFWHSF = *sys.new_Coordinate("aFWHSF","daFWHSF","ddaFWHSF",0.0,0.0,0.0);
    symbol_numeric bFWHSF = *sys.new_Coordinate("bFWHSF","dbFWHSF","ddbFWHSF",-0.064208,0.0,0.0);
    
    symbol_numeric *dzFWHSF=sys.get_Velocity("dzFWHSF"); symbol_numeric *daFWHSF=sys.get_Velocity("daFWHSF"); symbol_numeric *dbFWHSF=sys.get_Velocity("dbFWHSF");
    symbol_numeric *ddzFWHSF=sys.get_Acceleration("ddzFWHSF"); symbol_numeric *ddaFWHSF=sys.get_Acceleration("ddaFWHSF"); symbol_numeric *ddbFWHSF=sys.get_Acceleration("ddbFWHSF");
 
    //REAR WHEELSET (FWHSR)

    symbol_numeric zFWHSR = *sys.new_Coordinate("zFWHSR","dzFWHSR","ddzFWHSR",0.039711,0.0,0.0);
    symbol_numeric aFWHSR = *sys.new_Coordinate("aFWHSR","daFWHSR","ddaFWHSR",0.0,0.0,0.0);
    symbol_numeric bFWHSR = *sys.new_Coordinate("bFWHSR","dbFWHSR","ddbFWHSR",-0.064208,0.0,0.0);

    symbol_numeric *dzFWHSR=sys.get_Velocity("dzFWHSR"); symbol_numeric *daFWHSR=sys.get_Velocity("daFWHSR"); symbol_numeric *dbFWHSR=sys.get_Velocity("dbFWHSR");
    symbol_numeric *ddzFWHSR=sys.get_Acceleration("ddzFWHSR"); symbol_numeric *ddaFWHSR=sys.get_Acceleration("ddaFWHSR"); symbol_numeric *ddbFWHSR=sys.get_Acceleration("ddbFWHSR");


    // =====================================================================================================================================================================================
    // REAR BOGIE AXLE-BOXES coordinates
    // =====================================================================================================================================================================================

    //FRONT LEFT AXLEBOX (RAXBFL)
    symbol_numeric bRAXBFL = *sys.new_Coordinate("bRAXBFL","dbRAXBFL","ddbRAXBFL",0.0 ,0.0,0.0);
    symbol_numeric *dbRAXBFL=sys.get_Velocity("dbRAXBFL");
    symbol_numeric *ddbRAXBFL=sys.get_Acceleration("ddbRAXBFL");

    //FRONT RIGTH AXLEBOX (RAXBFR)
    symbol_numeric bRAXBFR = *sys.new_Coordinate("bRAXBFR","dbRAXBFR","ddbRAXBFR",0.0 ,0.0,0.0);
    symbol_numeric *dbRAXBFR=sys.get_Velocity("dbRAXBFR");
    symbol_numeric *ddbRAXBFR=sys.get_Acceleration("ddbRAXBFR");

    //REAR LEFT AXLEBOX (RAXBRL)
    symbol_numeric bRAXBRL = *sys.new_Coordinate("bRAXBRL","dbRAXBRL","ddbRAXBRL",0.0 ,0.0,0.0);
    symbol_numeric *dbRAXBRL=sys.get_Velocity("dbRAXBRL");
    symbol_numeric *ddbRAXBRL=sys.get_Acceleration("ddbRAXBRL");

    //REAR RIGTH AXLEBOX (RAXBRR)
    symbol_numeric bRAXBRR = *sys.new_Coordinate("bRAXBRR","dbRAXBRR","ddbRAXBRR",0.0 ,0.0,0.0);
    symbol_numeric *dbRAXBRR=sys.get_Velocity("dbRAXBRR");
    symbol_numeric *ddbRAXBRR=sys.get_Acceleration("ddbRAXBRR");


    // =====================================================================================================================================================================================
    // FRONT BOGIE AXLE-BOXES coordinates
    // =====================================================================================================================================================================================

    //FRONT LEFT AXLEBOX (FAXBFL)
    symbol_numeric bFAXBFL = *sys.new_Coordinate("bFAXBFL","dbFAXBFL","ddbFAXBFL",0.0 ,0.0,0.0);
    symbol_numeric *dbFAXBFL=sys.get_Velocity("dbFAXBFL");
    symbol_numeric *ddbFAXBFL=sys.get_Acceleration("ddbFAXBFL");

    //FRONT RIGTH AXLEBOX (FAXBFR)
    symbol_numeric bFAXBFR = *sys.new_Coordinate("bFAXBFR","dbFAXBFR","ddbFAXBFR",0.0 ,0.0,0.0);
    symbol_numeric *dbFAXBFR=sys.get_Velocity("dbFAXBFR");
    symbol_numeric *ddbFAXBFR=sys.get_Acceleration("ddbFAXBFR");

    //REAR LEFT AXLEBOX (FAXBRL)
    symbol_numeric bFAXBRL = *sys.new_Coordinate("bFAXBRL","dbFAXBRL","ddbFAXBRL",0.0 ,0.0,0.0);
    symbol_numeric *dbFAXBRL=sys.get_Velocity("dbFAXBRL");
    symbol_numeric *ddbFAXBRL=sys.get_Acceleration("ddbFAXBRL");

    //REAR RIGTH AXLEBOX (FAXBRR)
    symbol_numeric bFAXBRR = *sys.new_Coordinate("bFAXBRR","dbFAXBRR","ddbFAXBRR",0.0 ,0.0,0.0);
    symbol_numeric *dbFAXBRR=sys.get_Velocity("dbFAXBRR");
    symbol_numeric *ddbFAXBRR=sys.get_Acceleration("ddbFAXBRR");



    // =====================================================================================================================================================================================
    // REAR BOGIE MOTOR coordinates
    // =====================================================================================================================================================================================

    //FRONT RMOTOR (RMOTF)
    symbol_numeric xRMOTF = *sys.new_Coordinate("xRMOTF","dxRMOTF","ddxRMOTF",-0.0,0.0,0.0);
    symbol_numeric yRMOTF = *sys.new_Coordinate("yRMOTF","dyRMOTF","ddyRMOTF", 0.0 ,0.0,0.0);
    symbol_numeric zRMOTF = *sys.new_Coordinate("zRMOTF","dzRMOTF","ddzRMOTF",-0.022297,0.0,0.0);
    symbol_numeric bRMOTF = *sys.new_Coordinate("bRMOTF","dbRMOTF","ddbRMOTF", 0.004414,0.0,0.0);

    symbol_numeric *dxRMOTF=sys.get_Velocity("dxRMOTF");
    symbol_numeric *dyRMOTF=sys.get_Velocity("dyRMOTF");
    symbol_numeric *dzRMOTF=sys.get_Velocity("dzRMOTF");
    symbol_numeric *dbRMOTF=sys.get_Velocity("dbRMOTF");

    symbol_numeric *ddxRMOTF=sys.get_Acceleration("ddxRMOTF");
    symbol_numeric *ddyRMOTF=sys.get_Acceleration("ddyRMOTF");
    symbol_numeric *ddzRMOTF=sys.get_Acceleration("ddzRMOTF");
    symbol_numeric *ddbRMOTF=sys.get_Acceleration("ddbRMOTF");

    //REAR RMOTOR (RMOTR)
    symbol_numeric xRMOTR = *sys.new_Coordinate("xRMOTR","dxRMOTR","ddxRMOTR",-0.0,0.0,0.0);
    symbol_numeric yRMOTR = *sys.new_Coordinate("yRMOTR","dyRMOTR","ddyRMOTR", 0.0 ,0.0,0.0);
    symbol_numeric zRMOTR = *sys.new_Coordinate("zRMOTR","dzRMOTR","ddzRMOTR",-0.022297,0.0,0.0);
    symbol_numeric bRMOTR = *sys.new_Coordinate("bRMOTR","dbRMOTR","ddbRMOTR",-0.0044414,0.0,0.0);

    symbol_numeric *dxRMOTR=sys.get_Velocity("dxRMOTR");
    symbol_numeric *dyRMOTR=sys.get_Velocity("dyRMOTR");
    symbol_numeric *dzRMOTR=sys.get_Velocity("dzRMOTR");
    symbol_numeric *dbRMOTR=sys.get_Velocity("dbRMOTR");

    symbol_numeric *ddxRMOTR=sys.get_Acceleration("ddxRMOTR");
    symbol_numeric *ddyRMOTR=sys.get_Acceleration("ddyRMOTR");
    symbol_numeric *ddzRMOTR=sys.get_Acceleration("ddzRMOTR");
    symbol_numeric *ddbRMOTR=sys.get_Acceleration("ddbRMOTR");

    //FRONT ROTOR (RROTF)
    symbol_numeric bRROTF = *sys.new_Coordinate("bRROTF","dbRROTF","ddbRROTF",-0.204795 ,0.0,0.0);
    symbol_numeric *dbRROTF=sys.get_Velocity("dbRROTF");
    symbol_numeric *ddbRROTF=sys.get_Acceleration("ddbRROTF");
    
    //REAR RROTOR (RROTR)   
    symbol_numeric bRROTR = *sys.new_Coordinate("bRROTR","dbRROTR","ddbRROTR",-0.204795,0.0,0.0);
    symbol_numeric *dbRROTR=sys.get_Velocity("dbRROTR");
    symbol_numeric *ddbRROTR=sys.get_Acceleration("ddbRROTR");    


    // =====================================================================================================================================================================================
    // LISTS OF COORDINATES 
    // =====================================================================================================================================================================================
 
    lst coord_indep_init;
    lst vel_indep_init;




// ************************************************************************************************************************************************************************************************
// ************************************************************************************************************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************************************************************************************************************
// ************************************************************************************************************************************************************************************************

    //In meters, 

    //symbol_numeric L_R = *sys.new_Parameter("L_R",1+0.035+0.035);//ancho FEVE https://es.wikipedia.org/wiki/Ancho_de_v%C3%ADa
    //symbol_numeric LWHS= *sys.new_Parameter("L_WHS",0.930+0.068+0.068+0.00);
    
    symbol_numeric L_OBOG_OAXBy  = *sys.new_Parameter("L_OBOG_OAXBy",0.815);
    symbol_numeric L_OBOG_OAXBz  = *sys.new_Parameter("L_OBOG_OAXBz",0.075+0.122182);

    symbol_numeric L_OBOG_OSUSPy  = *sys.new_Parameter("L_OBOG_OSUSPy",0.815);
    symbol_numeric L_OBOG_OSUSPx  = *sys.new_Parameter("L_OBOG_OSUSPx",0.5);
    symbol_numeric L_OBOG_OSUSPz  = *sys.new_Parameter("L_OBOG_OSUSPz",0.122182);

    symbol_numeric L_OBOG_OWHS    = *sys.new_Parameter("L_OBOG_OWHS",1.0925);
    
    symbol_numeric L_OBOG_P1BOG   = *sys.new_Parameter("L_OBOG_P1BOG",0.3525);//cambiar distancia hasta el punto de anclaje del motor, no hasta el eje de las ruedas
   
    symbol_numeric L_MOT          = *sys.new_Parameter("L_MOT",0.396);
    symbol_numeric L_GEAR         = *sys.new_Parameter("L_GEAR",0.344);//cambiar tamano del motor (L_OBOG_P1BOG + LMOT+ L_GEAR= 1.0925)
    symbol_numeric L_AXB1         = *sys.new_Parameter("L_AXB1",0.265+0.250);//cambiar 
    symbol_numeric L_AXB2         = *sys.new_Parameter("L_AXB2",0.092);//cambiar ?????
    symbol_numeric L_SUSP         = *sys.new_Parameter("L_SUSP",0.269); 
    //symbol_numeric L_WHS          = *sys.new_Parameter("L_WHS",0.815);     
    symbol_numeric L_WHS          = *sys.new_Parameter("L_WHS",0.930+0.068+0.068+0.004);//1.0660
    symbol_numeric L_RAIL         = *sys.new_Parameter("L_RAIL",1+0.035+0.035);//ancho FEVE https://es.wikipedia.org/wiki/Ancho_de_v%C3%ADa
    symbol_numeric L_WAG          = *sys.new_Parameter("L_WAG",9.500);     

    symbol_numeric L_SUSPBEAM1     = *sys.new_Parameter("L_SUSPBEAM1",0.5); //En verdad son 0.485
    symbol_numeric L_SUSPBEAM2     = *sys.new_Parameter("L_SUSPBEAM2",0.170);
    
    symbol_numeric L_SLDx         = *sys.new_Parameter("L_SLDx",0.170);  
    symbol_numeric L_SLDy         = *sys.new_Parameter("L_SLDy",0.815);
    
    symbol_numeric b_pend = *sys.new_Parameter("b_pend",0.05);
    symbol_numeric a_pend = *sys.new_Parameter("a_pend",0.0);

    //symbol_numeric L_O_ORAIL= *sys.new_Parameter("L_O_ORAIL",0.815);
    
    symbol_numeric  L0_1 = *sys.new_Parameter("L0_1",0.310);
    symbol_numeric  L0_2 = *sys.new_Parameter("L0_2",0.378);

    
// ************************************************************************************************************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************************************************************************************************************

// ************************************************************************************************************************************************************************************************
//	Define Bases
// ************************************************************************************************************************************************************************************************
    // RAIL BASE 
    //sys.new_Base("B_RAIL","xyz",0,0,0,0);//Base Rail
    sys.new_Base("B_RAIL","xyz",0,1,0, b_pend);//Base Rail
    //sys.new_Base("B_RAIL","xyz",1,0,0, a_pend);
    
    // WAGON BASE   
    sys.new_Base("B_WAG_c","B_RAIL",0,0,1,cWAG);
    sys.new_Base("B_WAG_a","B_WAG_c",1,0,0,aWAG);
    sys.new_Base("B_WAG","B_WAG_a",0,1,0,bWAG);
     
    // REAR BOGIE SLIDER BASE   
    sys.new_Base("B_RSLD","B_WAG",0,0,1,cRSLD);
    
    // FRONT BOGIE SLIDER BASE   
    sys.new_Base("B_FSLD","B_WAG",0,0,1,cFSLD);   
    
    // REAR BOGIE BASE   
    sys.new_Base("B_RBOG_b","B_RSLD",0,1,0,bRBOG);
    sys.new_Base("B_RBOG","B_RBOG_b",1,0,0,aRBOG);
    
    // FRONT BOGIE BASE   
    sys.new_Base("B_FBOG_b","B_FSLD",0,1,0,bFBOG);
    sys.new_Base("B_FBOG","B_FBOG_b",1,0,0,aFBOG);   
    
    // RWHSF BASE   
    sys.new_Base("B_RWHSF_a","B_RBOG" ,1,0,0,aRWHSF);
    sys.new_Base("B_RWHSF","B_RWHSF_a",0,1,0,bRWHSF);
    // RWHSR BASE   
    sys.new_Base("B_RWHSR_a","B_RBOG" ,1,0,0,aRWHSR);
    sys.new_Base("B_RWHSR","B_RWHSR_a",0,1,0,bRWHSR);

    // FWHSF BASE   
    sys.new_Base("B_FWHSF_a","B_FBOG" ,1,0,0,aFWHSF);
    sys.new_Base("B_FWHSF","B_FWHSF_a",0,1,0,bFWHSF);
    // FWHSR BASE   
    sys.new_Base("B_FWHSR_a","B_FBOG" ,1,0,0,aFWHSR);
    sys.new_Base("B_FWHSR","B_FWHSR_a",0,1,0,bFWHSR);
    
    // RAXBFL BASE   
    sys.new_Base("B_RAXBFL","B_RWHSF_a",0,1,0,bRAXBFL);
    // RAXBFR BASE   
    sys.new_Base("B_RAXBFR","B_RWHSF_a",0,1,0,bRAXBFR);
    // RAXBRL BASE   
    sys.new_Base("B_RAXBRL","B_RWHSR_a",0,1,0,bRAXBRL);
    // RAXBRR BASE   
    sys.new_Base("B_RAXBRR","B_RWHSR_a",0,1,0,bRAXBRR);

    // FAXBFL BASE   
    sys.new_Base("B_FAXBFL","B_FWHSF_a",0,1,0,bFAXBFL);
    // FAXBFR BASE   
    sys.new_Base("B_FAXBFR","B_FWHSF_a",0,1,0,bFAXBFR);
    // FAXBRL BASE   
    sys.new_Base("B_FAXBRL","B_FWHSR_a",0,1,0,bFAXBRL);
    // FAXBRR BASE   
    sys.new_Base("B_FAXBRR","B_FWHSR_a",0,1,0,bFAXBRR);

    // RMOTF BASE   
    sys.new_Base("B_RMOTF","B_RWHSF_a",0,1,0,bRMOTF);
    // RMOTR BASE   
    sys.new_Base("B_RMOTR","B_RWHSR_a",0,1,0,bRMOTR);
    // RROTF BASE   
    sys.new_Base("B_RROTF","B_RWHSF_a",0,1,0,bRROTF);
    // RROTR BASE   
    sys.new_Base("B_RROTR","B_RWHSR_a",0,1,0,bRROTR); 

// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

    Vector3D O_OWAG    = *sys.new_Vector3D("O_OWAG",xWAG,yWAG,zWAG,"B_RAIL");
    //Vector3D O_OWAG    = *sys.new_Vector3D("O_OWAG",xWAG,yWAG,zWAG,"xyz");



    
    Vector3D OWAG_ORSLD  = *sys.new_Vector3D("OWAG_ORSLD",-L_WAG/2,0,0,"B_WAG"); 
    Vector3D OWAG_OFSLD  = *sys.new_Vector3D("OWAG_OFSLD", L_WAG/2,0,0,"B_WAG"); 

    Vector3D ORSLD_ORBOG   = *sys.new_Vector3D("ORSLD_ORBOG",0,0,zRBOG,"B_RSLD"); 
    Vector3D OFSLD_OFBOG   = *sys.new_Vector3D("OFSLD_OFBOG",0,0,zFBOG,"B_FSLD"); 
   
    Vector3D ORBOG_S1RBOG  = *sys.new_Vector3D("ORBOG_S1RBOG", L_OBOG_P1BOG,0,0,"B_RBOG"); //S1 boggie ->SILENTBLOCK motor1 union point at RBOG
    Vector3D ORBOG_S2RBOG  = *sys.new_Vector3D("ORBOG_S2RBOG",-L_OBOG_P1BOG,0,0,"B_RBOG"); //S2 boggie ->SILENTBLOCK motor2 union point at RBOG

    Vector3D ORMOTF_ORROTF  = *sys.new_Vector3D("ORMOTF_ORROTF", L_MOT,0,0,"B_RMOTF"); // distance between the silenblock and the center of the rotor
    Vector3D ORMOTR_ORROTR  = *sys.new_Vector3D("ORMOTR_ORROTR",-L_MOT,0,0,"B_RMOTR"); 

    Vector3D ORBOG_ORWHSF   = *sys.new_Vector3D("ORBOG_ORWHSF", L_OBOG_OWHS,0,zRWHSF,"B_RBOG"); // distance between the center of the bogie and the center of the whell set 
    Vector3D ORBOG_ORWHSR   = *sys.new_Vector3D("ORBOG_ORWHSR",-L_OBOG_OWHS,0,zRWHSR,"B_RBOG");

   
    Vector3D OFBOG_OFWHSF   = *sys.new_Vector3D("OFBOG_OFWHSF", L_OBOG_OWHS,0,zFWHSF,"B_FBOG"); 
    Vector3D OFBOG_OFWHSR   = *sys.new_Vector3D("OFBOG_OFWHSR",-L_OBOG_OWHS,0,zFWHSR,"B_FBOG"); 

    
      
    Vector3D ORBOG_P1FL  = *sys.new_Vector3D("ORBOG_P1FL", L_OBOG_OWHS+L_AXB1/2, L_OBOG_OAXBy,L_OBOG_OAXBz,"B_RBOG");
    Vector3D ORBOG_P2FL  = *sys.new_Vector3D("ORBOG_P2FL", L_OBOG_OWHS-L_AXB1/2, L_OBOG_OAXBy,L_OBOG_OAXBz,"B_RBOG");
    Vector3D ORBOG_P1FR  = *sys.new_Vector3D("ORBOG_P1FR", L_OBOG_OWHS+L_AXB1/2,-L_OBOG_OAXBy,L_OBOG_OAXBz,"B_RBOG");
    Vector3D ORBOG_P2FR  = *sys.new_Vector3D("ORBOG_P2FR", L_OBOG_OWHS-L_AXB1/2,-L_OBOG_OAXBy,L_OBOG_OAXBz,"B_RBOG");
    Vector3D ORBOG_P1RL  = *sys.new_Vector3D("ORBOG_P1RL",-L_OBOG_OWHS+L_AXB1/2, L_OBOG_OAXBy,L_OBOG_OAXBz,"B_RBOG");
    Vector3D ORBOG_P2RL  = *sys.new_Vector3D("ORBOG_P2RL",-L_OBOG_OWHS-L_AXB1/2, L_OBOG_OAXBy,L_OBOG_OAXBz,"B_RBOG");
    Vector3D ORBOG_P1RR  = *sys.new_Vector3D("ORBOG_P1RR",-L_OBOG_OWHS+L_AXB1/2,-L_OBOG_OAXBy,L_OBOG_OAXBz,"B_RBOG");
    Vector3D ORBOG_P2RR  = *sys.new_Vector3D("ORBOG_P2RR",-L_OBOG_OWHS-L_AXB1/2,-L_OBOG_OAXBy,L_OBOG_OAXBz,"B_RBOG");

    Vector3D ORBOG_P3FL  = *sys.new_Vector3D("ORBOG_P3FL", L_OBOG_OSUSPx, L_OBOG_OSUSPy,L_OBOG_OSUSPz,"B_RBOG");
    Vector3D ORBOG_P3RL  = *sys.new_Vector3D("ORBOG_P3RL",-L_OBOG_OSUSPx, L_OBOG_OSUSPy,L_OBOG_OSUSPz,"B_RBOG");   
    Vector3D ORBOG_P3FR  = *sys.new_Vector3D("ORBOG_P3FR", L_OBOG_OSUSPx,-L_OBOG_OSUSPy,L_OBOG_OSUSPz,"B_RBOG");  
    Vector3D ORBOG_P3RR  = *sys.new_Vector3D("ORBOG_P3RR",-L_OBOG_OSUSPx,-L_OBOG_OSUSPy,L_OBOG_OSUSPz,"B_RBOG");  
    
    Vector3D RBOG_P3FL_P4FL  = *sys.new_Vector3D("RBOG_P3FL_P4FL",0,0,-L_SUSP,"B_RBOG");    
    Vector3D RBOG_P3RL_P4RL  = *sys.new_Vector3D("RBOG_P3RL_P4RL",0,0,-L_SUSP,"B_RBOG");    
    Vector3D RBOG_P3FR_P4FR  = *sys.new_Vector3D("RBOG_P3FR_P4FR",0,0,-L_SUSP,"B_RBOG");     
    Vector3D RBOG_P3RR_P4RR  = *sys.new_Vector3D("RBOG_P3RR_P4RR",0,0,-L_SUSP,"B_RBOG"); 
    
    Vector3D RBOG_P4FL_P5FL  = *sys.new_Vector3D("RBOG_P4FL_P5FL",-(L_SUSPBEAM1-L_SUSPBEAM2),0,0,"B_RBOG");    
    Vector3D RBOG_P4RL_P5RL  = *sys.new_Vector3D("RBOG_P4RL_P5RL",  L_SUSPBEAM1-L_SUSPBEAM2 ,0,0,"B_RBOG");
    Vector3D RBOG_P4FR_P5FR  = *sys.new_Vector3D("RBOG_P4FR_P5FR",-(L_SUSPBEAM1-L_SUSPBEAM2),0,0,"B_RBOG");    
    Vector3D RBOG_P4RR_P5RR  = *sys.new_Vector3D("RBOG_P4RR_P5RR",  L_SUSPBEAM1-L_SUSPBEAM2 ,0,0,"B_RBOG");
    
    Vector3D RBOG_P5FL_P6FL  = *sys.new_Vector3D("RBOG_P5FL_P6FL",0,0,L0_2,"B_RBOG");    
    Vector3D RBOG_P5RL_P6RL  = *sys.new_Vector3D("RBOG_P5RL_P6RL",0,0,L0_2,"B_RBOG");
    Vector3D RBOG_P5FR_P6FR  = *sys.new_Vector3D("RBOG_P5FR_P6FR",0,0,L0_2,"B_RBOG");    
    Vector3D RBOG_P5RR_P6RR  = *sys.new_Vector3D("RBOG_P5RR_P6RR",0,0,L0_2,"B_RBOG");
    
    Vector3D OFBOG_P1FL  = *sys.new_Vector3D("OFBOG_P1FL", L_OBOG_OWHS+L_AXB1/2, L_OBOG_OAXBy,L_OBOG_OAXBz,"B_FBOG");
    Vector3D OFBOG_P2FL  = *sys.new_Vector3D("OFBOG_P2FL", L_OBOG_OWHS-L_AXB1/2, L_OBOG_OAXBy,L_OBOG_OAXBz,"B_FBOG");
    Vector3D OFBOG_P1FR  = *sys.new_Vector3D("OFBOG_P1FR", L_OBOG_OWHS+L_AXB1/2,-L_OBOG_OAXBy,L_OBOG_OAXBz,"B_FBOG");
    Vector3D OFBOG_P2FR  = *sys.new_Vector3D("OFBOG_P2FR", L_OBOG_OWHS-L_AXB1/2,-L_OBOG_OAXBy,L_OBOG_OAXBz,"B_FBOG");
    Vector3D OFBOG_P1RL  = *sys.new_Vector3D("OFBOG_P1RL",-L_OBOG_OWHS+L_AXB1/2, L_OBOG_OAXBy,L_OBOG_OAXBz,"B_FBOG");
    Vector3D OFBOG_P2RL  = *sys.new_Vector3D("OFBOG_P2RL",-L_OBOG_OWHS-L_AXB1/2, L_OBOG_OAXBy,L_OBOG_OAXBz,"B_FBOG");
    Vector3D OFBOG_P1RR  = *sys.new_Vector3D("OFBOG_P1RR",-L_OBOG_OWHS+L_AXB1/2,-L_OBOG_OAXBy,L_OBOG_OAXBz,"B_FBOG");
    Vector3D OFBOG_P2RR  = *sys.new_Vector3D("OFBOG_P2RR",-L_OBOG_OWHS-L_AXB1/2,-L_OBOG_OAXBy,L_OBOG_OAXBz,"B_FBOG");

    Vector3D OFBOG_P3FL  = *sys.new_Vector3D("OFBOG_P3FL", L_OBOG_OSUSPx, L_OBOG_OSUSPy,L_OBOG_OSUSPz,"B_FBOG");
    Vector3D OFBOG_P3RL  = *sys.new_Vector3D("OFBOG_P3RL",-L_OBOG_OSUSPx, L_OBOG_OSUSPy,L_OBOG_OSUSPz,"B_FBOG");   
    Vector3D OFBOG_P3FR  = *sys.new_Vector3D("OFBOG_P3FR", L_OBOG_OSUSPx,-L_OBOG_OSUSPy,L_OBOG_OSUSPz,"B_FBOG");  
    Vector3D OFBOG_P3RR  = *sys.new_Vector3D("OFBOG_P3RR",-L_OBOG_OSUSPx,-L_OBOG_OSUSPy,L_OBOG_OSUSPz,"B_FBOG");  
    
    Vector3D FBOG_P3FL_P4FL  = *sys.new_Vector3D("FBOG_P3FL_P4FL",0,0,-L_SUSP,"B_FBOG");    
    Vector3D FBOG_P3RL_P4RL  = *sys.new_Vector3D("FBOG_P3RL_P4RL",0,0,-L_SUSP,"B_FBOG");    
    Vector3D FBOG_P3FR_P4FR  = *sys.new_Vector3D("FBOG_P3FR_P4FR",0,0,-L_SUSP,"B_FBOG");     
    Vector3D FBOG_P3RR_P4RR  = *sys.new_Vector3D("FBOG_P3RR_P4RR",0,0,-L_SUSP,"B_FBOG"); 
    
    Vector3D FBOG_P4FL_P5FL  = *sys.new_Vector3D("FBOG_P4FL_P5FL",-(L_SUSPBEAM1-L_SUSPBEAM2),0,0,"B_FBOG");    
    Vector3D FBOG_P4RL_P5RL  = *sys.new_Vector3D("FBOG_P4RL_P5RL",  L_SUSPBEAM1-L_SUSPBEAM2 ,0,0,"B_FBOG");
    Vector3D FBOG_P4FR_P5FR  = *sys.new_Vector3D("FBOG_P4FR_P5FR",-(L_SUSPBEAM1-L_SUSPBEAM2),0,0,"B_FBOG");    
    Vector3D FBOG_P4RR_P5RR  = *sys.new_Vector3D("FBOG_P4RR_P5RR",  L_SUSPBEAM1-L_SUSPBEAM2 ,0,0,"B_FBOG");
    
    Vector3D FBOG_P5FL_P6FL  = *sys.new_Vector3D("FBOG_P5FL_P6FL",0,0,L0_2,"B_FBOG");    
    Vector3D FBOG_P5RL_P6RL  = *sys.new_Vector3D("FBOG_P5RL_P6RL",0,0,L0_2,"B_FBOG");
    Vector3D FBOG_P5FR_P6FR  = *sys.new_Vector3D("FBOG_P5FR_P6FR",0,0,L0_2,"B_FBOG");    
    Vector3D FBOG_P5RR_P6RR  = *sys.new_Vector3D("FBOG_P5RR_P6RR",0,0,L0_2,"B_FBOG");



    Vector3D S1RBOG_ORMOTF  = *sys.new_Vector3D("S1RBOG_ORMOTF",xRMOTF,yRMOTF,zRMOTF,"B_RBOG");
    Vector3D S2RBOG_ORMOTR  = *sys.new_Vector3D("S2RBOG_ORMOTR",xRMOTR,yRMOTR,zRMOTR,"B_RBOG");
    
    Vector3D ORWHSF_ORAXBFL = *sys.new_Vector3D("ORWHSF_ORAXBFL",0, L_OBOG_OAXBy,0,"B_RWHSF"); 
    Vector3D ORWHSF_ORAXBFR = *sys.new_Vector3D("ORWHSF_ORAXBFR",0,-L_OBOG_OAXBy,0,"B_RWHSF"); 
    Vector3D ORWHSR_ORAXBRL = *sys.new_Vector3D("ORWHSR_ORAXBRL",0, L_OBOG_OAXBy,0,"B_RWHSR");    
    Vector3D ORWHSR_ORAXBRR = *sys.new_Vector3D("ORWHSR_ORAXBRR",0,-L_OBOG_OAXBy,0,"B_RWHSR"); 
    
    Vector3D OFWHSF_OFAXBFL = *sys.new_Vector3D("OFWHSF_OFAXBFL",0, L_OBOG_OAXBy,0,"B_FWHSF"); 
    Vector3D OFWHSF_OFAXBFR = *sys.new_Vector3D("OFWHSF_OFAXBFR",0,-L_OBOG_OAXBy,0,"B_FWHSF"); 
    Vector3D OFWHSR_OFAXBRL = *sys.new_Vector3D("OFWHSR_OFAXBRL",0, L_OBOG_OAXBy,0,"B_FWHSR");    
    Vector3D OFWHSR_OFAXBRR = *sys.new_Vector3D("OFWHSR_OFAXBRR",0,-L_OBOG_OAXBy,0,"B_FWHSR");   
    

    Vector3D ORAXBFL_P1RAXBFL  = *sys.new_Vector3D("ORAXBFL_P1RAXBFL",  L_AXB1/2,0,-L_AXB2+L0_1,"B_RAXBFL");
    Vector3D ORAXBFL_P2RAXBFL  = *sys.new_Vector3D("ORAXBFL_P2RAXBFL", -L_AXB1/2,0,-L_AXB2+L0_1,"B_RAXBFL");
    Vector3D ORAXBFL_P11RAXBFL = *sys.new_Vector3D("ORAXBFL_P11RAXBFL", L_AXB1/2,0,-L_AXB2,"B_RAXBFL"); //just for drawing the springs
    Vector3D ORAXBFL_P21RAXBFL = *sys.new_Vector3D("ORAXBFL_P21RAXBFL",-L_AXB1/2,0,-L_AXB2,"B_RAXBFL"); 

    Vector3D ORAXBFR_P1RAXBFR  = *sys.new_Vector3D("ORAXBFR_P1RAXBFR",  L_AXB1/2,0,-L_AXB2+L0_1,"B_RAXBFR"); 
    Vector3D ORAXBFR_P2RAXBFR  = *sys.new_Vector3D("ORAXBFR_P2RAXBFR", -L_AXB1/2,0,-L_AXB2+L0_1,"B_RAXBFR");
    Vector3D ORAXBFR_P11RAXBFR = *sys.new_Vector3D("ORAXBFR_P11RAXBFR", L_AXB1/2,0,-L_AXB2,"B_RAXBFR"); 
    Vector3D ORAXBFR_P21RAXBFR = *sys.new_Vector3D("ORAXBFR_P21RAXBFR",-L_AXB1/2,0,-L_AXB2,"B_RAXBFR");

    Vector3D ORAXBRL_P1RAXBRL  = *sys.new_Vector3D("ORAXBRL_P1RAXBRL", L_AXB1/2,0,-L_AXB2+L0_1,"B_RAXBRL"); 
    Vector3D ORAXBRL_P2RAXBRL  = *sys.new_Vector3D("ORAXBRL_P2RAXBRL",-L_AXB1/2,0,-L_AXB2+L0_1,"B_RAXBRL");
    Vector3D ORAXBRL_P11RAXBRL = *sys.new_Vector3D("ORAXBRL_P11RAXBRL", L_AXB1/2,0,-L_AXB2,"B_RAXBRL"); 
    Vector3D ORAXBRL_P21RAXBRL = *sys.new_Vector3D("ORAXBRL_P21RAXBRL",-L_AXB1/2,0,-L_AXB2,"B_RAXBRL");    

    Vector3D ORAXBRR_P1RAXBRR  = *sys.new_Vector3D("ORAXBRR_P1RAXBRR",  L_AXB1/2,0,-L_AXB2+L0_1,"B_RAXBRR"); 
    Vector3D ORAXBRR_P2RAXBRR  = *sys.new_Vector3D("ORAXBRR_P2RAXBRR", -L_AXB1/2,0,-L_AXB2+L0_1,"B_RAXBRR");
    Vector3D ORAXBRR_P11RAXBRR = *sys.new_Vector3D("ORAXBRR_P11RAXBRR", L_AXB1/2,0,-L_AXB2,"B_RAXBRR"); 
    Vector3D ORAXBRR_P21RAXBRR = *sys.new_Vector3D("ORAXBRR_P21RAXBRR",-L_AXB1/2,0,-L_AXB2,"B_RAXBRR");    
    
    
    Vector3D OFAXBFL_P1FAXBFL  = *sys.new_Vector3D("OFAXBFL_P1FAXBFL",  L_AXB1/2,0,-L_AXB2+L0_1,"B_FAXBFL");
    Vector3D OFAXBFL_P2FAXBFL  = *sys.new_Vector3D("OFAXBFL_P2FAXBFL", -L_AXB1/2,0,-L_AXB2+L0_1,"B_FAXBFL");
    Vector3D OFAXBFL_P11FAXBFL = *sys.new_Vector3D("OFAXBFL_P11FAXBFL", L_AXB1/2,0,-L_AXB2,"B_FAXBFL"); //just for drawing the springs
    Vector3D OFAXBFL_P21FAXBFL = *sys.new_Vector3D("OFAXBFL_P21FAXBFL",-L_AXB1/2,0,-L_AXB2,"B_FAXBFL"); 

    Vector3D OFAXBFR_P1FAXBFR  = *sys.new_Vector3D("OFAXBFR_P1FAXBFR",  L_AXB1/2,0,-L_AXB2+L0_1,"B_FAXBFR"); 
    Vector3D OFAXBFR_P2FAXBFR  = *sys.new_Vector3D("OFAXBFR_P2FAXBFR", -L_AXB1/2,0,-L_AXB2+L0_1,"B_FAXBFR");
    Vector3D OFAXBFR_P11FAXBFR = *sys.new_Vector3D("OFAXBFR_P11FAXBFR", L_AXB1/2,0,-L_AXB2,"B_FAXBFR"); 
    Vector3D OFAXBFR_P21FAXBFR = *sys.new_Vector3D("OFAXBFR_P21FAXBFR",-L_AXB1/2,0,-L_AXB2,"B_FAXBFR");

    Vector3D OFAXBRL_P1FAXBRL  = *sys.new_Vector3D("OFAXBRL_P1FAXBRL",  L_AXB1/2,0,-L_AXB2+L0_1,"B_FAXBRL"); 
    Vector3D OFAXBRL_P2FAXBRL  = *sys.new_Vector3D("OFAXBRL_P2FAXBRL", -L_AXB1/2,0,-L_AXB2+L0_1,"B_FAXBRL");
    Vector3D OFAXBRL_P11FAXBRL = *sys.new_Vector3D("OFAXBRL_P11FAXBRL", L_AXB1/2,0,-L_AXB2,"B_FAXBRL"); 
    Vector3D OFAXBRL_P21FAXBRL = *sys.new_Vector3D("OFAXBRL_P21FAXBRL",-L_AXB1/2,0,-L_AXB2,"B_FAXBRL");    

    Vector3D OFAXBRR_P1FAXBRR  = *sys.new_Vector3D("OFAXBRR_P1FAXBRR",  L_AXB1/2,0,-L_AXB2+L0_1,"B_FAXBRR"); 
    Vector3D OFAXBRR_P2FAXBRR  = *sys.new_Vector3D("OFAXBRR_P2FAXBRR", -L_AXB1/2,0,-L_AXB2+L0_1,"B_FAXBRR");
    Vector3D OFAXBRR_P11FAXBRR = *sys.new_Vector3D("OFAXBRR_P11FAXBRR", L_AXB1/2,0,-L_AXB2,"B_FAXBRR"); 
    Vector3D OFAXBRR_P21FAXBRR = *sys.new_Vector3D("OFAXBRR_P21FAXBRR",-L_AXB1/2,0,-L_AXB2,"B_FAXBRR"); 
    
    
    Vector3D ORSLD_PFL = *sys.new_Vector3D("ORSLD_PFL", L_SLDx, L_SLDy,0,"B_RSLD");
    Vector3D ORSLD_PRL = *sys.new_Vector3D("ORSLD_PRL",-L_SLDx, L_SLDy,0,"B_RSLD");    
    Vector3D ORSLD_PFR = *sys.new_Vector3D("ORSLD_PFR", L_SLDx,-L_SLDy,0,"B_RSLD");    
    Vector3D ORSLD_PRR = *sys.new_Vector3D("ORSLD_PRR",-L_SLDx,-L_SLDy,0,"B_RSLD"); 

    Vector3D OFSLD_PFL = *sys.new_Vector3D("OFSLD_PFL", L_SLDx, L_SLDy,0,"B_FSLD");
    Vector3D OFSLD_PRL = *sys.new_Vector3D("OFSLD_PRL",-L_SLDx, L_SLDy,0,"B_FSLD");    
    Vector3D OFSLD_PFR = *sys.new_Vector3D("OFSLD_PFR", L_SLDx,-L_SLDy,0,"B_FSLD");    
    Vector3D OFSLD_PRR = *sys.new_Vector3D("OFSLD_PRR",-L_SLDx,-L_SLDy,0,"B_FSLD");   
    
// ************************************************************************************************************************************************************************************************
//	Define Points
// ************************************************************************************************************************************************************************************************

    
    Point * O_WAG   = sys.new_Point("O_WAG","O",&O_OWAG);



    Point * O_RSLD  = sys.new_Point("O_RSLD","O_WAG",&OWAG_ORSLD); 
    Point * O_FSLD  = sys.new_Point("O_FSLD","O_WAG",&OWAG_OFSLD); 

    Point * O_RBOG   = sys.new_Point("O_RBOG","O_RSLD",&ORSLD_ORBOG);   
    Point * O_FBOG   = sys.new_Point("O_FBOG","O_FSLD",&OFSLD_OFBOG);   

    Point * P1_RBOG  = sys.new_Point("P1_RBOG","O_RBOG",&ORBOG_S1RBOG);
    Point * P2_RBOG  = sys.new_Point("P2_RBOG","O_RBOG",&ORBOG_S2RBOG);

    Point * O_RMOTF  = sys.new_Point("O_RMOTF","P1_RBOG",&S1RBOG_ORMOTF);  
    Point * O_RMOTR  = sys.new_Point("O_RMOTR","P2_RBOG",&S2RBOG_ORMOTR); 
    
    Point * O_RROTF  = sys.new_Point("O_RROTF","O_RMOTF",&ORMOTF_ORROTF);  
    Point * O_RROTR  = sys.new_Point("O_RROTR","O_RMOTR",&ORMOTR_ORROTR);

    Point * O_RWHSF  = sys.new_Point("O_RWHSF","O_RBOG",&ORBOG_ORWHSF); 
    Point * O_RWHSR  = sys.new_Point("O_RWHSR","O_RBOG",&ORBOG_ORWHSR);

    Point * O_FWHSF  = sys.new_Point("O_FWHSF","O_FBOG",&OFBOG_OFWHSF); 
    Point * O_FWHSR  = sys.new_Point("O_FWHSR","O_FBOG",&OFBOG_OFWHSR); 

    Point * O_RAXBFL = sys.new_Point("O_RAXBFL","O_RWHSF",&ORWHSF_ORAXBFL);
    Point * O_RAXBFR = sys.new_Point("O_RAXBFR","O_RWHSF",&ORWHSF_ORAXBFR);
    Point * O_RAXBRL = sys.new_Point("O_RAXBRL","O_RWHSR",&ORWHSR_ORAXBRL);
    Point * O_RAXBRR = sys.new_Point("O_RAXBRR","O_RWHSR",&ORWHSR_ORAXBRR);

    Point * O_FAXBFL = sys.new_Point("O_FAXBFL","O_FWHSF",&OFWHSF_OFAXBFL);
    Point * O_FAXBFR = sys.new_Point("O_FAXBFR","O_FWHSF",&OFWHSF_OFAXBFR);
    Point * O_FAXBRL = sys.new_Point("O_FAXBRL","O_FWHSR",&OFWHSR_OFAXBRL);
    Point * O_FAXBRR = sys.new_Point("O_FAXBRR","O_FWHSR",&OFWHSR_OFAXBRR);

    Point * P1_RAXBFL  = sys.new_Point("P1_RAXBFL" ,"O_RAXBFL",&ORAXBFL_P1RAXBFL);
    Point * P2_RAXBFL  = sys.new_Point("P2_RAXBFL" ,"O_RAXBFL",&ORAXBFL_P2RAXBFL);
    Point * P11_RAXBFL = sys.new_Point("P11_RAXBFL","O_RAXBFL",&ORAXBFL_P11RAXBFL);
    Point * P21_RAXBFL = sys.new_Point("P21_RAXBFL","O_RAXBFL",&ORAXBFL_P21RAXBFL);    
    
    Point * P1_RAXBFR  = sys.new_Point("P1_RAXBFR" ,"O_RAXBFR",&ORAXBFR_P1RAXBFR);
    Point * P2_RAXBFR  = sys.new_Point("P2_RAXBFR" ,"O_RAXBFR",&ORAXBFR_P2RAXBFR);
    Point * P11_RAXBFR = sys.new_Point("P11_RAXBFR","O_RAXBFR",&ORAXBFR_P11RAXBFR);
    Point * P21_RAXBFR = sys.new_Point("P21_RAXBFR","O_RAXBFR",&ORAXBFR_P21RAXBFR);

    Point * P1_RAXBRL  = sys.new_Point("P1_RAXBRL" ,"O_RAXBRL",&ORAXBRL_P1RAXBRL);
    Point * P2_RAXBRL  = sys.new_Point("P2_RAXBRL" ,"O_RAXBRL",&ORAXBRL_P2RAXBRL);
    Point * P11_RAXBRL = sys.new_Point("P11_RAXBRL","O_RAXBRL",&ORAXBRL_P11RAXBRL);
    Point * P21_RAXBRL = sys.new_Point("P21_RAXBRL","O_RAXBRL",&ORAXBRL_P21RAXBRL);
    Point * P1_RAXBRR  = sys.new_Point("P1_RAXBRR" ,"O_RAXBRR",&ORAXBRR_P1RAXBRR);
    Point * P2_RAXBRR  = sys.new_Point("P2_RAXBRR" ,"O_RAXBRR",&ORAXBRR_P2RAXBRR);
    Point * P11_RAXBRR = sys.new_Point("P11_RAXBRR","O_RAXBRR",&ORAXBRR_P11RAXBRR);
    Point * P21_RAXBRR = sys.new_Point("P21_RAXBRR","O_RAXBRR",&ORAXBRR_P21RAXBRR);   
    
    
    Point * P1_FAXBFL  = sys.new_Point("P1_FAXBFL" ,"O_FAXBFL",&OFAXBFL_P1FAXBFL);
    Point * P2_FAXBFL  = sys.new_Point("P2_FAXBFL" ,"O_FAXBFL",&OFAXBFL_P2FAXBFL);
    Point * P11_FAXBFL = sys.new_Point("P11_FAXBFL","O_FAXBFL",&OFAXBFL_P11FAXBFL);
    Point * P21_FAXBFL = sys.new_Point("P21_FAXBFL","O_FAXBFL",&OFAXBFL_P21FAXBFL);    
    
    Point * P1_FAXBFR  = sys.new_Point("P1_FAXBFR" ,"O_FAXBFR",&OFAXBFR_P1FAXBFR);
    Point * P2_FAXBFR  = sys.new_Point("P2_FAXBFR" ,"O_FAXBFR",&OFAXBFR_P2FAXBFR);
    Point * P11_FAXBFR = sys.new_Point("P11_FAXBFR","O_FAXBFR",&OFAXBFR_P11FAXBFR);
    Point * P21_FAXBFR = sys.new_Point("P21_FAXBFR","O_FAXBFR",&OFAXBFR_P21FAXBFR);

    Point * P1_FAXBRL  = sys.new_Point("P1_FAXBRL" ,"O_FAXBRL",&OFAXBRL_P1FAXBRL);
    Point * P2_FAXBRL  = sys.new_Point("P2_FAXBRL" ,"O_FAXBRL",&OFAXBRL_P2FAXBRL);
    Point * P11_FAXBRL = sys.new_Point("P11_FAXBRL","O_FAXBRL",&OFAXBRL_P11FAXBRL);
    Point * P21_FAXBRL = sys.new_Point("P21_FAXBRL","O_FAXBRL",&OFAXBRL_P21FAXBRL);

    Point * P1_FAXBRR  = sys.new_Point("P1_FAXBRR" ,"O_FAXBRR",&OFAXBRR_P1FAXBRR);
    Point * P2_FAXBRR  = sys.new_Point("P2_FAXBRR" ,"O_FAXBRR",&OFAXBRR_P2FAXBRR);
    Point * P11_FAXBRR = sys.new_Point("P11_FAXBRR","O_FAXBRR",&OFAXBRR_P11FAXBRR);
    Point * P21_FAXBRR = sys.new_Point("P21_FAXBRR","O_FAXBRR",&OFAXBRR_P21FAXBRR);   
    

    Point * P1FL_RBOG = sys.new_Point("P1FL_RBOG","O_RBOG",&ORBOG_P1FL);
    Point * P1FR_RBOG = sys.new_Point("P1FR_RBOG","O_RBOG",&ORBOG_P1FR);
    Point * P1RL_RBOG = sys.new_Point("P1RL_RBOG","O_RBOG",&ORBOG_P1RL);
    Point * P1RR_RBOG = sys.new_Point("P1RR_RBOG","O_RBOG",&ORBOG_P1RR);

    Point * P2FL_RBOG = sys.new_Point("P2FL_RBOG","O_RBOG",&ORBOG_P2FL);
    Point * P2FR_RBOG = sys.new_Point("P2FR_RBOG","O_RBOG",&ORBOG_P2FR);
    Point * P2RL_RBOG = sys.new_Point("P2RL_RBOG","O_RBOG",&ORBOG_P2RL);
    Point * P2RR_RBOG = sys.new_Point("P2RR_RBOG","O_RBOG",&ORBOG_P2RR);

    Point * P3FL_RBOG = sys.new_Point("P3FL_RBOG","O_RBOG",&ORBOG_P3FL);
    Point * P3FR_RBOG = sys.new_Point("P3FR_RBOG","O_RBOG",&ORBOG_P3FR);
    Point * P3RL_RBOG = sys.new_Point("P3RL_RBOG","O_RBOG",&ORBOG_P3RL);
    Point * P3RR_RBOG = sys.new_Point("P3RR_RBOG","O_RBOG",&ORBOG_P3RR);

    Point * P4FL_RBOG = sys.new_Point("P4FL_RBOG","P3FL_RBOG",&RBOG_P3FL_P4FL);
    Point * P4FR_RBOG = sys.new_Point("P4FR_RBOG","P3FR_RBOG",&RBOG_P3FR_P4FR);
    Point * P4RL_RBOG = sys.new_Point("P4RL_RBOG","P3RL_RBOG",&RBOG_P3RL_P4RL);
    Point * P4RR_RBOG = sys.new_Point("P4RR_RBOG","P3RR_RBOG",&RBOG_P3RR_P4RR);
    
    Point * P5FL_RBOG = sys.new_Point("P5FL_RBOG","P4FL_RBOG",&RBOG_P4FL_P5FL);  
    Point * P5FR_RBOG = sys.new_Point("P5FR_RBOG","P4FR_RBOG",&RBOG_P4FR_P5FR);  
    Point * P5RL_RBOG = sys.new_Point("P5RL_RBOG","P4RL_RBOG",&RBOG_P4RL_P5RL);  
    Point * P5RR_RBOG = sys.new_Point("P5RR_RBOG","P4RR_RBOG",&RBOG_P4RR_P5RR); 

    Point * P6FL_RBOG = sys.new_Point("P6FL_RBOG","P5FL_RBOG",&RBOG_P5FL_P6FL);  
    Point * P6FR_RBOG = sys.new_Point("P6FR_RBOG","P5FR_RBOG",&RBOG_P5FR_P6FR);  
    Point * P6RL_RBOG = sys.new_Point("P6RL_RBOG","P5RL_RBOG",&RBOG_P5RL_P6RL);  
    Point * P6RR_RBOG = sys.new_Point("P6RR_RBOG","P5RR_RBOG",&RBOG_P5RR_P6RR);   

  



    Point * P1FL_FBOG = sys.new_Point("P1FL_FBOG","O_FBOG",&OFBOG_P1FL);
    Point * P1FR_FBOG = sys.new_Point("P1FR_FBOG","O_FBOG",&OFBOG_P1FR);
    Point * P1RL_FBOG = sys.new_Point("P1RL_FBOG","O_FBOG",&OFBOG_P1RL);
    Point * P1RR_FBOG = sys.new_Point("P1RR_FBOG","O_FBOG",&OFBOG_P1RR);

    Point * P2FL_FBOG = sys.new_Point("P2FL_FBOG","O_FBOG",&OFBOG_P2FL);
    Point * P2FR_FBOG = sys.new_Point("P2FR_FBOG","O_FBOG",&OFBOG_P2FR);
    Point * P2RL_FBOG = sys.new_Point("P2RL_FBOG","O_FBOG",&OFBOG_P2RL);
    Point * P2RR_FBOG = sys.new_Point("P2RR_FBOG","O_FBOG",&OFBOG_P2RR);

    Point * P3FL_FBOG = sys.new_Point("P3FL_FBOG","O_FBOG",&OFBOG_P3FL);
    Point * P3FR_FBOG = sys.new_Point("P3FR_FBOG","O_FBOG",&OFBOG_P3FR);
    Point * P3RL_FBOG = sys.new_Point("P3RL_FBOG","O_FBOG",&OFBOG_P3RL);
    Point * P3RR_FBOG = sys.new_Point("P3RR_FBOG","O_FBOG",&OFBOG_P3RR);

    Point * P4FL_FBOG = sys.new_Point("P4FL_FBOG","P3FL_FBOG",&FBOG_P3FL_P4FL);
    Point * P4FR_FBOG = sys.new_Point("P4FR_FBOG","P3FR_FBOG",&FBOG_P3FR_P4FR);
    Point * P4RL_FBOG = sys.new_Point("P4RL_FBOG","P3RL_FBOG",&FBOG_P3RL_P4RL);
    Point * P4RR_FBOG = sys.new_Point("P4RR_FBOG","P3RR_FBOG",&FBOG_P3RR_P4RR);
    
    Point * P5FL_FBOG = sys.new_Point("P5FL_FBOG","P4FL_FBOG",&FBOG_P4FL_P5FL);  
    Point * P5FR_FBOG = sys.new_Point("P5FR_FBOG","P4FR_FBOG",&FBOG_P4FR_P5FR);  
    Point * P5RL_FBOG = sys.new_Point("P5RL_FBOG","P4RL_FBOG",&FBOG_P4RL_P5RL);  
    Point * P5RR_FBOG = sys.new_Point("P5RR_FBOG","P4RR_FBOG",&FBOG_P4RR_P5RR); 

    Point * P6FL_FBOG = sys.new_Point("P6FL_FBOG","P5FL_FBOG",&FBOG_P5FL_P6FL);  
    Point * P6FR_FBOG = sys.new_Point("P6FR_FBOG","P5FR_FBOG",&FBOG_P5FR_P6FR);  
    Point * P6RL_FBOG = sys.new_Point("P6RL_FBOG","P5RL_FBOG",&FBOG_P5RL_P6RL);  
    Point * P6RR_FBOG = sys.new_Point("P6RR_FBOG","P5RR_FBOG",&FBOG_P5RR_P6RR);  
    

    Vector3D RBOG_P4FL_ORSUSPBEAML =  0.5 * sys.Position_Vector("P4FL_RBOG","P4RL_RBOG");
    Vector3D RBOG_P4FR_ORSUSPBEAMR =  0.5 * sys.Position_Vector("P4FR_RBOG","P4RR_RBOG");
   
    Point * O_RSUSPBEAML = sys.new_Point("O_RSUSPBEAML","P4FL_RBOG",&RBOG_P4FL_ORSUSPBEAML);
    Point * O_RSUSPBEAMR = sys.new_Point("O_RSUSPBEAMR","P4FR_RBOG",&RBOG_P4FR_ORSUSPBEAMR);
 
    Vector3D FBOG_P4FL_OFSUSPBEAML =  0.5 * sys.Position_Vector("P4FL_FBOG","P4RL_FBOG");
    Vector3D FBOG_P4FR_OFSUSPBEAMR =  0.5 * sys.Position_Vector("P4FR_FBOG","P4RR_FBOG");
   
    Point * O_FSUSPBEAML = sys.new_Point("O_FSUSPBEAML","P4FL_FBOG",&FBOG_P4FL_OFSUSPBEAML);
    Point * O_FSUSPBEAMR = sys.new_Point("O_FSUSPBEAMR","P4FR_FBOG",&FBOG_P4FR_OFSUSPBEAMR);  
    


    Point * PFL_RSLD = sys.new_Point("PFL_RSLD","O_RSLD",&ORSLD_PFL);
    Point * PRL_RSLD = sys.new_Point("PRL_RSLD","O_RSLD",&ORSLD_PRL);
    Point * PFR_RSLD = sys.new_Point("PFR_RSLD","O_RSLD",&ORSLD_PFR);
    Point * PRR_RSLD = sys.new_Point("PRR_RSLD","O_RSLD",&ORSLD_PRR);    
    
    Point * PFL_FSLD = sys.new_Point("PFL_FSLD","O_FSLD",&OFSLD_PFL);
    Point * PRL_FSLD = sys.new_Point("PRL_FSLD","O_FSLD",&OFSLD_PRL);
    Point * PFR_FSLD = sys.new_Point("PFR_FSLD","O_FSLD",&OFSLD_PFR);
    Point * PRR_FSLD = sys.new_Point("PRR_FSLD","O_FSLD",&OFSLD_PRR);    


// ************************************************************************************************************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************************************************************************************************************
    // MAIN BODY WAGON
    symbol_numeric  m_WAG  = *sys.new_Parameter("m_WAG",22608.0);
    symbol_numeric  I_WAGx = *sys.new_Parameter("I_WAGx",7800.0);  // INVENTADOS
    symbol_numeric  I_WAGy = *sys.new_Parameter("I_WAGy",53079.0);
    symbol_numeric  I_WAGz = *sys.new_Parameter("I_WAGz",17000.0);
 
    symbol_numeric  xCGWAG = *sys.new_Parameter("xCGWAG",-0.1372);    
    symbol_numeric  yCGWAG = *sys.new_Parameter("yCGWAG",0.0); 
    symbol_numeric  zCGWAG = *sys.new_Parameter("zCGWAG",3.5); 


    Vector3D OWAG_GWAG = *sys.new_Vector3D("OWAG_GWAG",(ex)xCGWAG,0,(ex)zCGWAG,"B_WAG");
    Tensor3D I_WAG = *sys.new_Tensor3D("I_WAG",(ex)I_WAGx+m_WAG*(zCGWAG*zCGWAG),(ex)0,(ex)(-xCGWAG*zCGWAG),
                                               (ex)0,(ex)I_WAGy +m_WAG*(zCGWAG*zCGWAG+xCGWAG*xCGWAG), (ex)0,
                                               (ex)(-xCGWAG*zCGWAG),(ex)0,(ex)I_WAGz +m_WAG * (xCGWAG*xCGWAG) ,"B_WAG"); 

    // BOGIE (check this values)
    symbol_numeric  G_BOGz = *sys.new_Parameter("G_BOGz",0.281);// Calculado por Carmen
    symbol_numeric  m_BOG = *sys.new_Parameter("m_BOG",1507.86);
    symbol_numeric  I_BOGx = *sys.new_Parameter("I_BOGx",716.90);
    symbol_numeric  I_BOGy = *sys.new_Parameter("I_BOGy",1738.30);
    symbol_numeric  I_BOGz = *sys.new_Parameter("I_BOGz",2347.30);


    Vector3D ORBOG_GRBOG= *sys.new_Vector3D("ORBOG_GRBOG",0,0,G_BOGz,"B_RBOG");
    Tensor3D I_RBOG = *sys.new_Tensor3D("I_RBOG",(ex)I_BOGx,(ex)0,(ex)0,(ex)0,(ex)I_BOGy,(ex)0,(ex)0,(ex)0,(ex)I_BOGz,"B_RBOG");
    Vector3D OFBOG_GFBOG= *sys.new_Vector3D("OFBOG_GFBOG",0,0,G_BOGz,"B_FBOG");
    Tensor3D I_FBOG = *sys.new_Tensor3D("I_FBOG",(ex)I_BOGx,(ex)0,(ex)0,(ex)0,(ex)I_BOGy,(ex)0,(ex)0,(ex)0,(ex)I_BOGz,"B_FBOG");


    // MOTORS
    symbol_numeric  m_MOT = *sys.new_Parameter("m_MOT",568.80);
    symbol_numeric  I_MOTx = *sys.new_Parameter("I_MOTx",49.30);
    symbol_numeric  I_MOTy = *sys.new_Parameter("I_MOTy",139.10);
    symbol_numeric  I_MOTz = *sys.new_Parameter("I_MOTz",6.69);  
    // ROTORS
    symbol_numeric  m_ROT = *sys.new_Parameter("m_ROT",568.80);
    symbol_numeric  I_ROTx = *sys.new_Parameter("I_ROTx",17.70);
    symbol_numeric  I_ROTy = *sys.new_Parameter("I_ROTy",1.7); 
    symbol_numeric  I_ROTz = *sys.new_Parameter("I_ROTz",17.70);

    // RMOTF 
    Vector3D ORMOTF_GRMOTF= *sys.new_Vector3D("ORMOTF_GRMOTF",0,0,0,"B_RMOTF");  
    Tensor3D I_RMOTF = *sys.new_Tensor3D("I_RMOTF",(ex)I_MOTx,(ex)0,(ex)0,(ex)0,(ex)I_MOTy,(ex)0,(ex)0,(ex)0,(ex)I_MOTz,"B_RMOTF");
    // RMOTR
    Vector3D ORMOTR_GRMOTR= *sys.new_Vector3D("ORMOTR_GRMOTR",0,0,0,"B_RMOTR");  
    Tensor3D I_RMOTR = *sys.new_Tensor3D("I_RMOTR",(ex)I_MOTx,(ex)0,(ex)0,(ex)0,(ex)I_MOTy,(ex)0,(ex)0,(ex)0,(ex)I_MOTz,"B_RMOTR");

    // RROTF 
    Vector3D ORROTF_GRROTF= *sys.new_Vector3D("ORROTF_GRROTF",0,0,0,"B_RROTF");  
    Tensor3D I_RROTF = *sys.new_Tensor3D("I_RROTF",(ex)I_ROTx,(ex)0,(ex)0,(ex)0,(ex)I_ROTy,(ex)0,(ex)0,(ex)0,(ex)I_ROTz,"B_RROTF");
    // RROTR
    Vector3D ORROTR_GRROTR= *sys.new_Vector3D("ORROTR_GRROTR",0,0,0,"B_RROTR");  
    Tensor3D I_RROTR = *sys.new_Tensor3D("I_RROTR",(ex)I_ROTx,(ex)0,(ex)0,(ex)0,(ex)I_ROTy,(ex)0,(ex)0,(ex)0,(ex)I_ROTz,"B_RROTR");



    symbol_numeric  m_WHS = *sys.new_Parameter("m_WHS",1222.0);
    symbol_numeric  I_WHSx = *sys.new_Parameter("I_WHSx",376.60);
    symbol_numeric  I_WHSy = *sys.new_Parameter("I_WHSy",79.60);
    symbol_numeric  I_WHSz = *sys.new_Parameter("I_WHSz",376.60);
    symbol_numeric  I_CORy = *sys.new_Parameter("I_CORy",6.136481); // corona del engranaje
    // RWHSF 
    Vector3D ORWHSF_GRWHSF= *sys.new_Vector3D("ORWHSF_GRWHSF",0,0,0,"B_RWHSF"); 
    Tensor3D I_RWHSF = *sys.new_Tensor3D("I_RWHSF",(ex)I_WHSx,(ex)0,(ex)0,(ex)0,(ex)I_WHSy + (ex)I_CORy,(ex)0,(ex)0,(ex)0,(ex)I_WHSz,"B_RWHSF");
    // RWHSR
    Vector3D ORWHSR_GRWHSR= *sys.new_Vector3D("ORWHSR_GRWHSR",0,0,0,"B_RWHSR");    
    Tensor3D I_RWHSR = *sys.new_Tensor3D("I_RWHSR",(ex)I_WHSx,(ex)0,(ex)0,(ex)0,(ex)I_WHSy + (ex)I_CORy,(ex)0,(ex)0,(ex)0,(ex)I_WHSz,"B_RWHSR");
    // FWHSF 
    Vector3D OFWHSF_GFWHSF= *sys.new_Vector3D("OFWHSF_GFWHSF",0,0,0,"B_FWHSF"); 
    Tensor3D I_FWHSF = *sys.new_Tensor3D("I_FWHSF",(ex)I_WHSx,(ex)0,(ex)0,(ex)0,(ex)I_WHSy,(ex)0,(ex)0,(ex)0,(ex)I_WHSz,"B_FWHSF");
    // FWHSR
    Vector3D OFWHSR_GFWHSR= *sys.new_Vector3D("OFWHSR_GFWHSR",0,0,0,"B_FWHSR");    
    Tensor3D I_FWHSR = *sys.new_Tensor3D("I_FWHSR",(ex)I_WHSx,(ex)0,(ex)0,(ex)0,(ex)I_WHSy,(ex)0,(ex)0,(ex)0,(ex)I_WHSz,"B_FWHSR");




    // AXELBOXES (The four are dynamicaly identical)(check this values)
    symbol_numeric  m_AXB = *sys.new_Parameter("m_AXB",67.72);
    symbol_numeric  I_AXBx = *sys.new_Parameter("I_AXBx",0.96);
    symbol_numeric  I_AXBy = *sys.new_Parameter("I_AXBy",4.57);
    symbol_numeric  I_AXBz = *sys.new_Parameter("I_AXBz",4.29);
    
    // RAXBFL
    Vector3D ORAXBFL_GRAXBFL= *sys.new_Vector3D("ORAXBFL_GRAXBFL",0,0,0,"B_RAXBFL");  //???   
    Tensor3D I_RAXBFL = *sys.new_Tensor3D("I_RAXBFL",(ex)I_AXBx,(ex)0,(ex)0,(ex)0,(ex)I_AXBy,(ex)0,(ex)0,(ex)0,(ex)I_AXBz,"B_RAXBFL");
    // AXBFR
    Vector3D ORAXBFR_GRAXBFR= *sys.new_Vector3D("ORAXBFR_GRAXBFR",0,0,0,"B_RAXBFR");  //???   
    Tensor3D I_RAXBFR = *sys.new_Tensor3D("I_RAXBFR",(ex)I_AXBx,(ex)0,(ex)0,(ex)0,(ex)I_AXBy,(ex)0,(ex)0,(ex)0,(ex)I_AXBz,"B_RAXBFR");  
    // AXBRL
    Vector3D ORAXBRL_GRAXBRL= *sys.new_Vector3D("ORAXBRL_GRAXBRL",0,0,0,"B_RAXBRL");  //???   
    Tensor3D I_RAXBRL = *sys.new_Tensor3D("I_RAXBRL",(ex)I_AXBx,(ex)0,(ex)0,(ex)0,(ex)I_AXBy,(ex)0,(ex)0,(ex)0,(ex)I_AXBz,"B_RAXBRL");
    // AXBRR
    Vector3D ORAXBRR_GRAXBRR= *sys.new_Vector3D("ORAXBRR_GRAXBRR",0,0,0,"B_RAXBRR");  //???   
    Tensor3D I_RAXBRR = *sys.new_Tensor3D("I_RAXBRR",(ex)I_AXBx,(ex)0,(ex)0,(ex)0,(ex)I_AXBy,(ex)0,(ex)0,(ex)0,(ex)I_AXBz,"B_RAXBRR"); 

    // AXBFL
    Vector3D OFAXBFL_FGAXBFL= *sys.new_Vector3D("OFAXBFL_GFAXBFL",0,0,0,"B_FAXBFL");  //???   
    Tensor3D I_FAXBFL = *sys.new_Tensor3D("I_FAXBFL",(ex)I_AXBx,(ex)0,(ex)0,(ex)0,(ex)I_AXBy,(ex)0,(ex)0,(ex)0,(ex)I_AXBz,"B_FAXBFL");
    // AXBFR
    Vector3D OFAXBFR_GFAXBFR= *sys.new_Vector3D("OFAXBFR_GFAXBFR",0,0,0,"B_FAXBFR");  //???   
    Tensor3D I_FAXBFR = *sys.new_Tensor3D("I_FAXBFR",(ex)I_AXBx,(ex)0,(ex)0,(ex)0,(ex)I_AXBy,(ex)0,(ex)0,(ex)0,(ex)I_AXBz,"B_FAXBFR");  
    // AXBRL
    Vector3D OFAXBRL_GFAXBRL= *sys.new_Vector3D("OFAXBRL_GFAXBRL",0,0,0,"B_FAXBRL");  //???   
    Tensor3D I_FAXBRL = *sys.new_Tensor3D("I_FAXBRL",(ex)I_AXBx,(ex)0,(ex)0,(ex)0,(ex)I_AXBy,(ex)0,(ex)0,(ex)0,(ex)I_AXBz,"B_FAXBRL");
    // AXBRR
    Vector3D OFAXBRR_GFAXBRR= *sys.new_Vector3D("OFAXBRR_GFAXBRR",0,0,0,"B_FAXBRR");  //???   
    Tensor3D I_FAXBRR = *sys.new_Tensor3D("I_FAXBRR",(ex)I_AXBx,(ex)0,(ex)0,(ex)0,(ex)I_AXBy,(ex)0,(ex)0,(ex)0,(ex)I_AXBz,"B_FAXBRR"); 


    // SLIDER 
    symbol_numeric  m_SLD = *sys.new_Parameter("m_SLD",461.0);
    symbol_numeric  I_SLDx = *sys.new_Parameter("I_SLDx",216.40);
    symbol_numeric  I_SLDy = *sys.new_Parameter("I_SLDy",25.90);
    symbol_numeric  I_SLDz = *sys.new_Parameter("I_SLDz",232.10);
   
    
    Tensor3D I_RSLD = *sys.new_Tensor3D("I_RSLD",(ex)I_SLDx,(ex)0,(ex)0,(ex)0,(ex)I_SLDy,(ex)0,(ex)0,(ex)0,(ex)I_SLDz,"B_RSLD");
    Vector3D ORSLD_GRSLD= *sys.new_Vector3D("ORSLD_GRSLD",0,0,0,"B_RSLD"); 
    
    Tensor3D I_FSLD = *sys.new_Tensor3D("I_FSLD",(ex)I_SLDx,(ex)0,(ex)0,(ex)0,(ex)I_SLDy,(ex)0,(ex)0,(ex)0,(ex)I_SLDz,"B_FSLD");
    Vector3D OFSLD_GFSLD= *sys.new_Vector3D("OFSLD_GFSLD",0,0,0,"B_FSLD");   
    

    
// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

    Frame * R_WAG    = sys.new_Frame("R_WAG","O_WAG","B_WAG");
    Frame * R_RBOG   = sys.new_Frame("R_RBOG","O_RBOG","B_RBOG");
    Frame * R_FBOG   = sys.new_Frame("R_FBOG","O_FBOG","B_FBOG");
    Frame * R_RAIL   = sys.new_Frame("R_RAIL","O","B_RAIL");

    Frame * R_FWHSR   = sys.new_Frame("R_FWHSR","O_FWHSR","B_FWHSR");    
    Frame * R_FWHSF   = sys.new_Frame("R_FWHSF","O_FWHSF","B_FWHSF"); 

    Frame * R_RWHSR   = sys.new_Frame("R_RWHSR","O_RWHSR","B_RWHSR");    
    Frame * R_RWHSF   = sys.new_Frame("R_RWHSF","O_RWHSF","B_RWHSF");   

// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

    Solid * WAG   = sys.new_Solid("WAG","O_WAG","B_WAG","m_WAG","OWAG_GWAG","I_WAG");
    
    Solid * RBOG   = sys.new_Solid("RBOG","O_RBOG","B_RBOG","m_BOG","ORBOG_GRBOG","I_RBOG");
    Solid * RWHSF  = sys.new_Solid("RWHSF","O_RWHSF","B_RWHSF","m_WHS","ORWHSF_GRWHSF","I_RWHSF");
    Solid * RWHSR  = sys.new_Solid("RWHSR","O_RWHSR","B_RWHSR","m_WHS","ORWHSR_GRWHSR","I_RWHSR");
    Solid * RAXBFL = sys.new_Solid("RAXBFL","O_RAXBFL","B_RAXBFL","m_AXB","ORAXBFL_GRAXBFL","I_RAXBFL");  
    Solid * RAXBFR = sys.new_Solid("RAXBFR","O_RAXBFR","B_RAXBFR","m_AXB","ORAXBFR_GRAXBFR","I_RAXBFR");  
    Solid * RAXBRL = sys.new_Solid("RAXBRL","O_RAXBRL","B_RAXBRL","m_AXB","ORAXBRL_GRAXBRL","I_RAXBRL");  
    Solid * RAXBRR = sys.new_Solid("RAXBRR","O_RAXBRR","B_RAXBRR","m_AXB","ORAXBRR_GRAXBRR","I_RAXBRR");
    Solid * RSLD   = sys.new_Solid("RSLD","O_RSLD","B_RSLD","m_SLD","ORSLD_GRSLD","I_RSLD");
    Solid * RMOTF  = sys.new_Solid("RMOTF","O_RMOTF","B_RMOTF","m_MOT","ORMOTF_GRMOTF","I_RMOTF");
    Solid * RMOTR  = sys.new_Solid("RMOTR","O_RMOTR","B_RMOTR","m_MOT","ORMOTR_GRMOTR","I_RMOTR");
    Solid * RROTF  = sys.new_Solid("RROTF","O_RROTF","B_RROTF","m_ROT","ORROTF_GRROTF","I_RROTF");
    Solid * RROTR  = sys.new_Solid("RROTR","O_RROTR","B_RROTR","m_ROT","ORROTR_GRROTR","I_RROTR");
 
    Solid * FBOG   = sys.new_Solid("FBOG","O_FBOG","B_FBOG","m_BOG","OFBOG_GFBOG","I_FBOG");
    Solid * FWHSF  = sys.new_Solid("FWHSF","O_FWHSF","B_FWHSF","m_WHS","OFWHSF_GFWHSF","I_FWHSF");
    Solid * FWHSR  = sys.new_Solid("FWHSR","O_FWHSR","B_FWHSR","m_WHS","OFWHSR_GFWHSR","I_FWHSR");
    Solid * FAXBFL = sys.new_Solid("FAXBFL","O_FAXBFL","B_FAXBFL","m_AXB","OFAXBFL_GFAXBFL","I_FAXBFL");  
    Solid * FAXBFR = sys.new_Solid("FAXBFR","O_FAXBFR","B_FAXBFR","m_AXB","OFAXBFR_GFAXBFR","I_FAXBFR");  
    Solid * FAXBRL = sys.new_Solid("FAXBRL","O_FAXBRL","B_FAXBRL","m_AXB","OFAXBRL_GFAXBRL","I_FAXBRL");  
    Solid * FAXBRR = sys.new_Solid("FAXBRR","O_FAXBRR","B_FAXBRR","m_AXB","OFAXBRR_GFAXBRR","I_FAXBRR");
    Solid * FSLD   = sys.new_Solid("FSLD","O_FSLD","B_FSLD","m_SLD","OFSLD_GFSLD","I_FSLD");



    //SOLIDS WITHOUT DYNAMICS 


// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

    Drawing3D * FraR_WAG = sys.new_Drawing3D("FraR_WAG",R_WAG,1.0);
    Drawing3D * FraR_RBOG = sys.new_Drawing3D("FraR_RBOG",R_RBOG,0.5);
    Drawing3D * FraR_FBOG = sys.new_Drawing3D("FraR_FBOG",R_FBOG,0.5);
    Drawing3D * FraR_RAIL = sys.new_Drawing3D("FraR_RAIL",R_RAIL,0.5);
    Drawing3D * FraABS = sys.new_Drawing3D("FraABS",Frame_abs,1);

    Drawing3D * FraFWHSR = sys.new_Drawing3D("FraFWHSR",R_FWHSR,0.5);
    Drawing3D * FraFWHSF = sys.new_Drawing3D("FraFWHSF",R_FWHSF,0.5);
    Drawing3D * FraRWHSR = sys.new_Drawing3D("FraRWHSR",R_RWHSR,0.51);
    Drawing3D * FraRWHSF = sys.new_Drawing3D("FraRWHSF",R_RWHSF,0.5);
 


    Drawing3D * D_WAG   = sys.new_Drawing3D ("D_WAG","WAG","./solids/wagon.stl",1,1,0,1.0);
    
    Drawing3D * D_RBOG   = sys.new_Drawing3D ("D_RBOG","RBOG","./solids/bogie_m.stl",0,0,1,1.0);
    Drawing3D * D_RWHSF  = sys.new_Drawing3D ("D_RWHSF","RWHSF","./solids/eje_m.stl",0,1,1,1.0);
    Drawing3D * D_RWHSR  = sys.new_Drawing3D ("D_RWHSR","RWHSR","./solids/eje_m.stl",0,1,1,1.0);
    Drawing3D * D_RAXBFL = sys.new_Drawing3D ("D_RAXBFL","RAXBFL","./solids/axlebox_left_m.stl",1,0,0,1.0);  
    Drawing3D * D_RAXBFR = sys.new_Drawing3D ("D_RAXBFR","RAXBFR","./solids/axlebox_rigth_m.stl",1,0,0,1.0);  
    Drawing3D * D_RAXBRL = sys.new_Drawing3D ("D_RAXBRL","RAXBRL","./solids/axlebox_left_m.stl",1,0,0,1.0);  
    Drawing3D * D_RAXBRR = sys.new_Drawing3D ("D_RAXBRR","RAXBRR","./solids/axlebox_rigth_m.stl",1,0,0,1.0);
    Drawing3D * D_RSLD   = sys.new_Drawing3D ("D_RSLD","RSLD","./solids/slider.stl",0,1,0,1.0);
    Drawing3D * D_RMOTF  = sys.new_Drawing3D ("D_RMOTF","RMOTF","./solids/carcasa_eje_motor_F.stl",1,0,1,1.0);
    Drawing3D * D_RMOTR  = sys.new_Drawing3D ("D_RMOTR","RMOTR","./solids/carcasa_eje_motor_R.stl",1,0,1,1.0);
    Drawing3D * D_RROTF  = sys.new_Drawing3D ("D_RROTF","RROTF","./solids/eje_motor_02.stl",0,1,0.5,1.0);
    Drawing3D * D_RROTR  = sys.new_Drawing3D ("D_RROTR","RROTR","./solids/eje_motor_02.stl",0,1,0.5,1.0);
 
    Drawing3D * D_FBOG   = sys.new_Drawing3D ("D_FBOG","FBOG","./solids/bogie_m.stl",0,0,1,1.0);
    Drawing3D * D_FWHSF  = sys.new_Drawing3D ("D_FWHSF","FWHSF","./solids/eje_m.stl",0,1,1,1.0);
    Drawing3D * D_FWHSR  = sys.new_Drawing3D ("D_FWHSR","FWHSR","./solids/eje_m.stl",0,1,1,1.0);
    Drawing3D * D_FAXBFL = sys.new_Drawing3D ("D_FAXBFL","FAXBFL","./solids/axlebox_left_m.stl",1,0,0,1.0);  
    Drawing3D * D_FAXBFR = sys.new_Drawing3D ("D_FAXBFR","FAXBFR","./solids/axlebox_rigth_m.stl",1,0,0,1.0);  
    Drawing3D * D_FAXBRL = sys.new_Drawing3D ("D_FAXBRL","FAXBRL","./solids/axlebox_left_m.stl",1,0,0,1.0);  
    Drawing3D * D_FAXBRR = sys.new_Drawing3D ("D_FAXBRR","FAXBRR","./solids/axlebox_rigth_m.stl",1,0,0,1.0);
    Drawing3D * D_FSLD   = sys.new_Drawing3D ("D_FSLD","FSLD","./solids/slider.stl",0,1,0,1.0);


    //DRAW SOLIDS WITHOUT DYNAMICS 
    Drawing3D * D_RAIL  = sys.new_Drawing3D("D_RAIL","O","B_RAIL","./solids/rail_down_m.stl",0.5,0.5,0.5,1.0);
    
    Drawing3D * D_RAXBFL1  = sys.new_Drawing3D("D_RAXBFL1","P11_RAXBFL","B_RAXBFL","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_RAXBFL2  = sys.new_Drawing3D("D_RAXBFL2","P21_RAXBFL","B_RAXBFL","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_RAXBFR1  = sys.new_Drawing3D("D_RAXBFR1","P11_RAXBFR","B_RAXBFR","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_RAXBFR2  = sys.new_Drawing3D("D_RAXBFR2","P21_RAXBFR","B_RAXBFR","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_RAXBRL1  = sys.new_Drawing3D("D_RAXBRL1","P11_RAXBRL","B_RAXBRL","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_RAXBRL2  = sys.new_Drawing3D("D_RAXBRL2","P21_RAXBRL","B_RAXBRL","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_RAXBRR1  = sys.new_Drawing3D("D_RAXBRR1","P11_RAXBRR","B_RAXBRR","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_RAXBRR2  = sys.new_Drawing3D("D_RAXBRR2","P21_RAXBRR","B_RAXBRR","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_RSUSPFL  = sys.new_Drawing3D("D_RSUSPFL","P3FL_RBOG","B_RBOG","./solids/suspender.stl",0,0,1,1.0);
    Drawing3D * D_RSUSPFR  = sys.new_Drawing3D("D_RSUSPFR","P3FR_RBOG","B_RBOG","./solids/suspender.stl",0,0,1,1.0);
    Drawing3D * D_RSUSPRL  = sys.new_Drawing3D("D_RSUSPRL","P3RL_RBOG","B_RBOG","./solids/suspender.stl",0,0,1,1.0);
    Drawing3D * D_RSUSPRR  = sys.new_Drawing3D("D_RSUSPRR","P3RR_RBOG","B_RBOG","./solids/suspender.stl",0,0,1,1.0);
    Drawing3D * D_RSUSPBEAML  = sys.new_Drawing3D("D_RSUSPBEAML","O_RSUSPBEAML","B_RBOG","./solids/suspender_beam.stl",0,0,1,1.0);
    Drawing3D * D_RSUSPBEAMR  = sys.new_Drawing3D("D_RSUSPBEAMR","O_RSUSPBEAMR","B_RBOG","./solids/suspender_beam.stl",0,0,1,1.0);
    Drawing3D * D_RSPRING2FL  = sys.new_Drawing3D("D_RSPRING2FL","P5FL_RBOG","B_RBOG","./solids/spring2.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_RSPRING2RL  = sys.new_Drawing3D("D_RSPRING2RL","P5RL_RBOG","B_RBOG","./solids/spring2.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_RSPRING2FR  = sys.new_Drawing3D("D_RSPRING2FR","P5FR_RBOG","B_RBOG","./solids/spring2.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_RSPRING2RR  = sys.new_Drawing3D("D_RSPRING2RR","P5RR_RBOG","B_RBOG","./solids/spring2.stl",0.5,0.5,0.5,1.0);

    Drawing3D * D_FAXBFL1  = sys.new_Drawing3D("D_FAXBFL1","P11_FAXBFL","B_FAXBFL","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_FAXBFL2  = sys.new_Drawing3D("D_FAXBFL2","P21_FAXBFL","B_FAXBFL","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_FAXBFR1  = sys.new_Drawing3D("D_FAXBFR1","P11_FAXBFR","B_FAXBFR","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_FAXBFR2  = sys.new_Drawing3D("D_FAXBFR2","P21_FAXBFR","B_FAXBFR","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_FAXBRL1  = sys.new_Drawing3D("D_FAXBRL1","P11_FAXBRL","B_FAXBRL","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_FAXBRL2  = sys.new_Drawing3D("D_FAXBRL2","P21_FAXBRL","B_FAXBRL","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_FAXBRR1  = sys.new_Drawing3D("D_FAXBRR1","P11_FAXBRR","B_FAXBRR","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_FAXBRR2  = sys.new_Drawing3D("D_FAXBRR2","P21_FAXBRR","B_FAXBRR","./solids/spring_m.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_FSUSPFL  = sys.new_Drawing3D("D_FSUSPFL","P3FL_FBOG","B_FBOG","./solids/suspender.stl",0,0,1,1.0);
    Drawing3D * D_FSUSPFR  = sys.new_Drawing3D("D_FSUSPFR","P3FR_FBOG","B_FBOG","./solids/suspender.stl",0,0,1,1.0);
    Drawing3D * D_FSUSPRL  = sys.new_Drawing3D("D_FSUSPRL","P3RL_FBOG","B_FBOG","./solids/suspender.stl",0,0,1,1.0);
    Drawing3D * D_FSUSPRR  = sys.new_Drawing3D("D_FSUSPRR","P3RR_FBOG","B_FBOG","./solids/suspender.stl",0,0,1,1.0);
    Drawing3D * D_FSUSPBEAML  = sys.new_Drawing3D("D_FSUSPBEAML","O_FSUSPBEAML","B_FBOG","./solids/suspender_beam.stl",0,0,1,1.0);
    Drawing3D * D_FSUSPBEAMR  = sys.new_Drawing3D("D_FSUSPBEAMR","O_FSUSPBEAMR","B_FBOG","./solids/suspender_beam.stl",0,0,1,1.0);
    Drawing3D * D_FSPRING2FL  = sys.new_Drawing3D("D_FSPRING2FL","P5FL_FBOG","B_FBOG","./solids/spring2.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_FSPRING2RL  = sys.new_Drawing3D("D_FSPRING2RL","P5RL_FBOG","B_FBOG","./solids/spring2.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_FSPRING2FR  = sys.new_Drawing3D("D_FSPRING2FR","P5FR_FBOG","B_FBOG","./solids/spring2.stl",0.5,0.5,0.5,1.0);
    Drawing3D * D_FSPRING2RR  = sys.new_Drawing3D("D_FSPRING2RR","P5RR_FBOG","B_FBOG","./solids/spring2.stl",0.5,0.5,0.5,1.0);   



// ************************************************************************************************
//	Joint Unknown Definition
// ************************************************************************************************

    cout << "Joint Unknown Definition" << endl;
    




// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************


    cout << "Input Vector" << endl;

    // Motors    
    symbol_numeric T_RMOTF = *sys.new_Input("T_RMOTF",100.0);
    symbol_numeric T_RMOTR = *sys.new_Input("T_RMOTR",100.0);

 
    // Breaks
    symbol_numeric T_FBRKF = *sys.new_Input("T_FBRKF",0.0);
    symbol_numeric T_FBRKR = *sys.new_Input("T_FBRKR",0.0);

    symbol_numeric T_RBRKF = *sys.new_Input("T_RBRKF",0.0);
    symbol_numeric T_RBRKR = *sys.new_Input("T_RBRKR",0.0);



   // Kalker Forces BOGIE-WHEELSET-SIDE (RRL =  REAR BOGIE - REAR WHELLSET- LEFT WHEEL)



   symbol_numeric Fx_RFR = *sys.new_Input("Fx_RFR",0.0);
   symbol_numeric Fy_RFR = *sys.new_Input("Fy_RFR",0.0);
   symbol_numeric Mz_RFR = *sys.new_Input("Mz_RFR",0.0);

   symbol_numeric Fx_RFL = *sys.new_Input("Fx_RFL",0.0);
   symbol_numeric Fy_RFL = *sys.new_Input("Fy_RFL",0.0);
   symbol_numeric Mz_RFL = *sys.new_Input("Mz_RFL",0.0);

   symbol_numeric Fx_RRR = *sys.new_Input("Fx_RRR",0.0);
   symbol_numeric Fy_RRR = *sys.new_Input("Fy_RRR",0.0);
   symbol_numeric Mz_RRR = *sys.new_Input("Mz_RRR",0.0);  

   symbol_numeric Fx_RRL = *sys.new_Input("Fx_RRL",0.0);
   symbol_numeric Fy_RRL = *sys.new_Input("Fy_RRL",0.0);
   symbol_numeric Mz_RRL = *sys.new_Input("Mz_RRL",0.0);

   symbol_numeric Fx_FRR = *sys.new_Input("Fx_FRR",0.0);
   symbol_numeric Fy_FRR = *sys.new_Input("Fy_FRR",0.0);
   symbol_numeric Mz_FRR = *sys.new_Input("Mz_FRR",0.0);  

   symbol_numeric Fx_FRL = *sys.new_Input("Fx_FRL",0.0);
   symbol_numeric Fy_FRL = *sys.new_Input("Fy_FRL",0.0);
   symbol_numeric Mz_FRL = *sys.new_Input("Mz_FRL",0.0); 

   symbol_numeric Fx_FFR = *sys.new_Input("Fx_FFR",0.0);
   symbol_numeric Fy_FFR = *sys.new_Input("Fy_FFR",0.0);
   symbol_numeric Mz_FFR = *sys.new_Input("Mz_FFR",0.0);

   symbol_numeric Fx_FFL = *sys.new_Input("Fx_FFL",0.0);
   symbol_numeric Fy_FFL = *sys.new_Input("Fy_FFL",0.0);
   symbol_numeric Mz_FFL = *sys.new_Input("Mz_FFL",0.0);

  
// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************   

    cout << "Force and Momentum Definition" << endl;

    // Motors
    // ************************************************************************************************  
    Vector3D F_RMOTF = *sys.new_Vector3D("F_RMOTF",0,0,0,"B_RROTF");
    Vector3D M_RMOTF = *sys.new_Vector3D("M_RMOTF",0,T_RMOTF,0, "B_RROTF");
    Vector3D F_RMOTR = *sys.new_Vector3D("F_RMOTR",0,0,0,"B_RROTR");
    Vector3D M_RMOTR = *sys.new_Vector3D("M_RMOTR",0,T_RMOTR,0, "B_RROTR");
 
    // Breaks
    // ************************************************************************************************  
    Vector3D F_FBRKF = *sys.new_Vector3D("F_FBRKF",0,0,0,"B_FWHSF");
    Vector3D M_FBRKF = *sys.new_Vector3D("M_FBRKF",0,T_FBRKF,0,"B_FWHSF");
    Vector3D F_FBRKR = *sys.new_Vector3D("F_FBRKR",0,0,0,"B_FWHSR");
    Vector3D M_FBRKR = *sys.new_Vector3D("M_FBRKR",0,T_FBRKR,0, "B_FWHSR");
   
    Vector3D F_RBRKF = *sys.new_Vector3D("F_RBRKF",0,0,0,"B_RWHSF");
    Vector3D M_RBRKF = *sys.new_Vector3D("M_RBRKF",0,T_RBRKF,0,"B_RWHSF");
    Vector3D F_RBRKR = *sys.new_Vector3D("F_RBRKR",0,0,0,"B_RWHSR");
    Vector3D M_RBRKR = *sys.new_Vector3D("M_RBRKR",0,T_RBRKR,0, "B_RWHSR");


    //SilentBlock in MOTORS Definition only in REAR BOGIE
    // ************************************************************************************************
    cout << "SilentBlock in MOTORS Definition" << endl;
	
    symbol_numeric  K_SSl = *sys.new_Parameter("K_SSl",500000.0);
    symbol_numeric  C_SSl = *sys.new_Parameter("C_SSl",5000.0);
    symbol_numeric  C_SSr = *sys.new_Parameter("C_SSr",5000.0);
    symbol_numeric  K_SSr = *sys.new_Parameter("K_SSr",500000.0);
    
    Vector3D F_S_RMOTF = K_SSl * sys.Position_Vector("P1_RBOG","O_RMOTF") + C_SSl * sys.Velocity_Vector("R_RBOG" ,"O_RMOTF");//, "MOTF" );
    Vector3D M_S_RMOTF = *sys.new_Vector3D("M_S_RMOTF",0,K_SSr*bRMOTF,0,"B_RBOG")+C_SSr * sys.Angular_Velocity("B_RBOG","B_RMOTF");

    Wrench3D * SBA_RMOTF = sys.new_Wrench3D ( "SBA_RMOTF", -F_S_RMOTF, -M_S_RMOTF , O_RMOTF , RMOTF , "Constitutive") ;
    Wrench3D * SBR_RMOTF = sys.new_Wrench3D ( "SBR_RMOTF",  F_S_RMOTF,  M_S_RMOTF , P1_RBOG , RBOG  , "Constitutive") ;

    Vector3D F_S_RMOTR = K_SSl * sys.Position_Vector("P2_RBOG","O_RMOTR") + C_SSl * sys.Velocity_Vector("R_RBOG" ,"O_RMOTR");//r4, "MOTR" );
    Vector3D M_S_RMOTR = *sys.new_Vector3D("M_S_RMOTR",0,K_SSr*bRMOTR,0, "B_RBOG")+ C_SSr * sys.Angular_Velocity("B_RBOG","B_RMOTR");

    Wrench3D * SBA_RMOTR = sys.new_Wrench3D ( "SBA_RMOTR", - F_S_RMOTR, -M_S_RMOTR , O_RMOTR , RMOTR , "Constitutive") ;
    Wrench3D * SBR_RMOTR = sys.new_Wrench3D ( "SBR_RMOTR",   F_S_RMOTR,  M_S_RMOTR , P2_RBOG , RBOG  , "Constitutive") ;


    //Linear stiffness model for a messing pair of spur gears only in REAR BOGIE
    // ************************************************************************************************
    cout << "Linear stiffness model for a messing pair of spur gears" << endl;

    symbol_numeric  Kgear = *sys.new_Parameter("Kgear",1000000.0);
    symbol_numeric  Cgear = *sys.new_Parameter("Cgear",10000);
    symbol_numeric  alpha_gear = *sys.new_Parameter("alpha_gear",0.34907); // 20º
    ex Kgear_eff =  Kgear * cos(alpha_gear); // K_gear effective
    ex Cgear_eff =  Cgear * cos(alpha_gear); // C_gear effective 
    
    symbol_numeric  zROT = *sys.new_Parameter("zROT",16.0);
    symbol_numeric  zWHS = *sys.new_Parameter("zWHS",68.0);  

    ex Rb_ROT = L_GEAR*(zROT/(zROT+zWHS)); 
    ex Rb_WHS = L_GEAR*(zWHS/(zROT+zWHS)); 

    ex uF = Rb_ROT * bRROTF + Rb_WHS * bRWHSF;
    ex uR = Rb_ROT * bRROTR + Rb_WHS * bRWHSR;

    ex vF = sys.dt(uF);
    ex vR = sys.dt(uR);   

    Vector3D ezF = *sys.new_Vector3D("ezF",0,0,1,"B_RMOTF");
    Vector3D ezR = *sys.new_Vector3D("ezR",0,0,-1,"B_RMOTR");
    
    Vector3D F_RGEARF =  (Kgear_eff * uF) * ezF + (Cgear_eff * vF) * ezF; 
    Vector3D F_RGEARR =  (Kgear_eff * uR) * ezR + (Cgear_eff * vR) * ezR;

    Vector3D M_RGEARF  = *sys.new_Vector3D("M_RGEARF",0,0,0, "B_RROTF");
    Vector3D M_RGEARR  = *sys.new_Vector3D("M_RGEARR",0,0,0, "B_RROTR");
    
    Vector3D ORROTF_PRROTF =  (Rb_ROT / (Rb_ROT+Rb_WHS)) * sys.Position_Vector("O_RROTF","O_RWHSF");
    Vector3D ORROTR_PRROTR =  (Rb_ROT / (Rb_ROT+Rb_WHS)) * sys.Position_Vector("O_RROTR","O_RWHSR");

    Point * P_RGEARF = sys.new_Point("P_RGEARF","O_RROTF",&ORROTF_PRROTF);
    Point * P_RGEARR = sys.new_Point("P_RGEARR","O_RROTR",&ORROTR_PRROTR);
    
    Wrench3D * TA_RGEARF= sys.new_Wrench3D ( "TA_RGEARF", -F_RGEARF, -M_RGEARF, P_RGEARF ,RWHSF  , "Constitutive") ;
    Wrench3D * TR_RGEARF= sys.new_Wrench3D ( "TR_RGEARF",  F_RGEARF,  M_RGEARF, P_RGEARF ,RROTF  , "Constitutive") ;
    Wrench3D * TA_RGEARR= sys.new_Wrench3D ( "TA_RGEARR", -F_RGEARR, -M_RGEARR, P_RGEARR ,RWHSR  , "Constitutive") ;
    Wrench3D * TR_RGEARR= sys.new_Wrench3D ( "TR_RGEARR",  F_RGEARR,  M_RGEARR, P_RGEARR ,RROTR  , "Constitutive") ;
    
    
    
    
	
    // Prymary suspension   (with C or not?????)
    // ************************************************************************************************ 
    //symbol_numeric  K_S1 = *sys.new_Parameter("K_S1",1000000.0);
    //symbol_numeric  K_S1 = *sys.new_Parameter("K_S1",226500.0);  //Carmen 
    symbol_numeric  K_S1 = *sys.new_Parameter("K_S1",261954); //Ingeteam 26.73kg/mm * 9.8 * 1000    
    symbol_numeric  C_S1 = *sys.new_Parameter("C_S1",5000.0);

    Vector3D F1_RAXBFL =  K_S1 * sys.Position_Vector("P1FL_RBOG","P1_RAXBFL") + C_S1 * sys.Dt(sys.Position_Vector("P1FL_RBOG","P1_RAXBFL"),"B_RAXBFL");
    Vector3D F2_RAXBFL =  K_S1 * sys.Position_Vector("P2FL_RBOG","P2_RAXBFL") + C_S1 * sys.Dt(sys.Position_Vector("P2FL_RBOG","P2_RAXBFL"),"B_RAXBFL");
    Vector3D M_RAXBFL  = *sys.new_Vector3D("M_RAXBFL",0,0,0, "B_RAXBFL");
    
    Vector3D F1_RAXBFR =  K_S1 * sys.Position_Vector("P1FR_RBOG","P1_RAXBFR") + C_S1 * sys.Dt(sys.Position_Vector("P1FR_RBOG","P1_RAXBFR"),"B_RAXBFR");
    Vector3D F2_RAXBFR =  K_S1 * sys.Position_Vector("P2FR_RBOG","P2_RAXBFR") + C_S1 * sys.Dt(sys.Position_Vector("P2FR_RBOG","P2_RAXBFR"),"B_RAXBFR");
    Vector3D M_RAXBFR  = *sys.new_Vector3D("M_RAXBFR",0,0,0, "B_RAXBFR");

    Vector3D F1_RAXBRL =  K_S1 * sys.Position_Vector("P1RL_RBOG","P1_RAXBRL") + C_S1 * sys.Dt(sys.Position_Vector("P1RL_RBOG","P1_RAXBRL"),"B_RAXBRL");
    Vector3D F2_RAXBRL =  K_S1 * sys.Position_Vector("P2RL_RBOG","P2_RAXBRL") + C_S1 * sys.Dt(sys.Position_Vector("P2RL_RBOG","P2_RAXBRL"),"B_RAXBRL");
    Vector3D M_RAXBRL  = *sys.new_Vector3D("M_RAXBRL",0,0,0, "B_RAXBRL");

    Vector3D F1_RAXBRR =  K_S1 * sys.Position_Vector("P1RR_RBOG","P1_RAXBRR") + C_S1 * sys.Dt(sys.Position_Vector("P1RR_RBOG","P1_RAXBRR"),"B_RAXBRR");
    Vector3D F2_RAXBRR =  K_S1 * sys.Position_Vector("P2RR_RBOG","P2_RAXBRR") + C_S1 * sys.Dt(sys.Position_Vector("P2RR_RBOG","P2_RAXBRR"),"B_RAXBRR");
    Vector3D M_RAXBRR  = *sys.new_Vector3D("M_RAXBRR",0,0,0, "B_RAXBRR");



    Wrench3D * TA1_RAXBFL= sys.new_Wrench3D ( "TA1_RAXBFL",-F1_RAXBFL , -M_RAXBFL, P1_RAXBFL ,RAXBFL , "Constitutive") ;
    Wrench3D * TR1_RAXBFL= sys.new_Wrench3D ( "TR1_RAXBFL", F1_RAXBFL ,  M_RAXBFL, P1FL_RBOG ,RBOG , "Constitutive") ;
    Wrench3D * TA2_RAXBFL= sys.new_Wrench3D ( "TA2_RAXBFL",-F2_RAXBFL , -M_RAXBFL, P2_RAXBFL ,RAXBFL , "Constitutive") ;
    Wrench3D * TR2_RAXBFL= sys.new_Wrench3D ( "TR2_RAXBFL", F2_RAXBFL ,  M_RAXBFL, P2FL_RBOG ,RBOG , "Constitutive") ;
	
    Wrench3D * TA1_RAXBFR= sys.new_Wrench3D ( "TA1_RAXBFR",-F1_RAXBFR , -M_RAXBFR, P1_RAXBFR ,RAXBFR , "Constitutive") ;
    Wrench3D * TR1_RAXBFR= sys.new_Wrench3D ( "TR1_RAXBFR", F1_RAXBFR ,  M_RAXBFR, P1FR_RBOG ,RBOG , "Constitutive") ;
    Wrench3D * TA2_RAXBFR= sys.new_Wrench3D ( "TA2_RAXBFR",-F2_RAXBFR , -M_RAXBFR, P2_RAXBFR ,RAXBFR , "Constitutive") ;
    Wrench3D * TR2_RAXBFR= sys.new_Wrench3D ( "TR2_RAXBFR", F2_RAXBFR ,  M_RAXBFR, P2FR_RBOG ,RBOG , "Constitutive") ;

    Wrench3D * TA1_RAXBRL= sys.new_Wrench3D ( "TA1_RAXBRL",-F1_RAXBRL , -M_RAXBRL, P1_RAXBRL ,RAXBRL , "Constitutive") ;
    Wrench3D * TR1_RAXBRL= sys.new_Wrench3D ( "TR1_RAXBRL", F1_RAXBRL ,  M_RAXBRL, P1RL_RBOG ,RBOG , "Constitutive") ;
    Wrench3D * TA2_RAXBRL= sys.new_Wrench3D ( "TA2_RAXBRL",-F2_RAXBRL , -M_RAXBRL, P2_RAXBRL ,RAXBRL , "Constitutive") ;
    Wrench3D * TR2_RAXBRL= sys.new_Wrench3D ( "TR2_RAXBRL", F2_RAXBRL ,  M_RAXBRL, P2RL_RBOG ,RBOG , "Constitutive") ;
	
    Wrench3D * TA1_RAXBRR= sys.new_Wrench3D ( "TA1_RAXBRR",-F1_RAXBRR , -M_RAXBRR, P1_RAXBRR ,RAXBRR , "Constitutive") ;
    Wrench3D * TR1_RAXBRR= sys.new_Wrench3D ( "TR1_RAXBRR", F1_RAXBRR ,  M_RAXBRR, P1RR_RBOG ,RBOG , "Constitutive") ;
    Wrench3D * TA2_RAXBRR= sys.new_Wrench3D ( "TA2_RAXBRR",-F2_RAXBRR , -M_RAXBRR, P2_RAXBRR ,RAXBRR , "Constitutive") ;
    Wrench3D * TR2_RAXBRR= sys.new_Wrench3D ( "TR2_RAXBRR", F2_RAXBRR ,  M_RAXBRR, P2RR_RBOG ,RBOG , "Constitutive") ;



    Vector3D F1_FAXBFL =  K_S1 * sys.Position_Vector("P1FL_FBOG","P1_FAXBFL") + C_S1 * sys.Dt(sys.Position_Vector("P1FL_FBOG","P1_FAXBFL"),"B_FAXBFL");
    Vector3D F2_FAXBFL =  K_S1 * sys.Position_Vector("P2FL_FBOG","P2_FAXBFL") + C_S1 * sys.Dt(sys.Position_Vector("P2FL_FBOG","P2_FAXBFL"),"B_FAXBFL");
    Vector3D M_FAXBFL  = *sys.new_Vector3D("M_FAXBFL",0,0,0, "B_FAXBFL");
    
    Vector3D F1_FAXBFR =  K_S1 * sys.Position_Vector("P1FR_FBOG","P1_FAXBFR") + C_S1 * sys.Dt(sys.Position_Vector("P1FR_FBOG","P1_FAXBFR"),"B_FAXBFR");
    Vector3D F2_FAXBFR =  K_S1 * sys.Position_Vector("P2FR_FBOG","P2_FAXBFR") + C_S1 * sys.Dt(sys.Position_Vector("P2FR_FBOG","P2_FAXBFR"),"B_FAXBFR");
    Vector3D M_FAXBFR  = *sys.new_Vector3D("M_FAXBFR",0,0,0, "B_FAXBFR");

    Vector3D F1_FAXBRL =  K_S1 * sys.Position_Vector("P1RL_FBOG","P1_FAXBRL") + C_S1 * sys.Dt(sys.Position_Vector("P1RL_FBOG","P1_FAXBRL"),"B_FAXBRL");
    Vector3D F2_FAXBRL =  K_S1 * sys.Position_Vector("P2RL_FBOG","P2_FAXBRL") + C_S1 * sys.Dt(sys.Position_Vector("P2RL_FBOG","P2_FAXBRL"),"B_FAXBRL");
    Vector3D M_FAXBRL  = *sys.new_Vector3D("M_FAXBRL",0,0,0, "B_FAXBRL");

    Vector3D F1_FAXBRR =  K_S1 * sys.Position_Vector("P1RR_FBOG","P1_FAXBRR") + C_S1 * sys.Dt(sys.Position_Vector("P1RR_FBOG","P1_FAXBRR"),"B_FAXBRR");
    Vector3D F2_FAXBRR =  K_S1 * sys.Position_Vector("P2RR_FBOG","P2_FAXBRR") + C_S1 * sys.Dt(sys.Position_Vector("P2RR_FBOG","P2_FAXBRR"),"B_FAXBRR");
    Vector3D M_FAXBRR  = *sys.new_Vector3D("M_FAXBRR",0,0,0, "B_FAXBRR");



    Wrench3D * TA1_FAXBFL= sys.new_Wrench3D ( "TA1_FAXBFL",-F1_FAXBFL , -M_FAXBFL, P1_FAXBFL ,FAXBFL , "Constitutive") ;
    Wrench3D * TR1_FAXBFL= sys.new_Wrench3D ( "TR1_FAXBFL", F1_FAXBFL ,  M_FAXBFL, P1FL_FBOG ,FBOG , "Constitutive") ;
    Wrench3D * TA2_FAXBFL= sys.new_Wrench3D ( "TA2_FAXBFL",-F2_FAXBFL , -M_FAXBFL, P2_FAXBFL ,FAXBFL , "Constitutive") ;
    Wrench3D * TR2_FAXBFL= sys.new_Wrench3D ( "TR2_FAXBFL", F2_FAXBFL ,  M_FAXBFL, P2FL_FBOG ,FBOG , "Constitutive") ;
	
    Wrench3D * TA1_FAXBFR= sys.new_Wrench3D ( "TA1_FAXBFR",-F1_FAXBFR , -M_FAXBFR, P1_FAXBFR ,FAXBFR , "Constitutive") ;
    Wrench3D * TR1_FAXBFR= sys.new_Wrench3D ( "TR1_FAXBFR", F1_FAXBFR ,  M_FAXBFR, P1FR_FBOG ,FBOG , "Constitutive") ;
    Wrench3D * TA2_FAXBFR= sys.new_Wrench3D ( "TA2_FAXBFR",-F2_FAXBFR , -M_FAXBFR, P2_FAXBFR ,FAXBFR , "Constitutive") ;
    Wrench3D * TR2_FAXBFR= sys.new_Wrench3D ( "TR2_FAXBFR", F2_FAXBFR ,  M_FAXBFR, P2FR_FBOG ,FBOG , "Constitutive") ;


    Wrench3D * TA1_FAXBRL= sys.new_Wrench3D ( "TA1_FAXBRL",-F1_FAXBRL , -M_FAXBRL, P1_FAXBRL ,FAXBRL , "Constitutive") ;
    Wrench3D * TR1_FAXBRL= sys.new_Wrench3D ( "TR1_FAXBRL", F1_FAXBRL ,  M_FAXBRL, P1RL_FBOG ,FBOG , "Constitutive") ;
    Wrench3D * TA2_FAXBRL= sys.new_Wrench3D ( "TA2_FAXBRL",-F2_FAXBRL , -M_FAXBRL, P2_FAXBRL ,FAXBRL , "Constitutive") ;
    Wrench3D * TR2_FAXBRL= sys.new_Wrench3D ( "TR2_FAXBRL", F2_FAXBRL ,  M_FAXBRL, P2RL_FBOG ,FBOG , "Constitutive") ;
	
    Wrench3D * TA1_FAXBRR= sys.new_Wrench3D ( "TA1_FAXBRR",-F1_FAXBRR , -M_FAXBRR, P1_FAXBRR ,FAXBRR , "Constitutive") ;
    Wrench3D * TR1_FAXBRR= sys.new_Wrench3D ( "TR1_FAXBRR", F1_FAXBRR ,  M_FAXBRR, P1RR_FBOG ,FBOG , "Constitutive") ;
    Wrench3D * TA2_FAXBRR= sys.new_Wrench3D ( "TA2_FAXBRR",-F2_FAXBRR , -M_FAXBRR, P2_FAXBRR ,FAXBRR , "Constitutive") ;
    Wrench3D * TR2_FAXBRR= sys.new_Wrench3D ( "TR2_FAXBRR", F2_FAXBRR ,  M_FAXBRR, P2RR_FBOG ,FBOG , "Constitutive") ;







    // Secondary suspension
    // ************************************************************************************************ 

    symbol_numeric  K_S2 = *sys.new_Parameter("K_S2",277046);//Ingeteam 28.27kg/mm*9.8*1000    
    symbol_numeric  C_S2 = *sys.new_Parameter("C_S2",5000.0);  
    
    
    Vector3D F_RSLDFL =  K_S2 * sys.Position_Vector("PFL_RSLD","P6FL_RBOG") + C_S2 * sys.Dt(sys.Position_Vector("PFL_RSLD","P6FL_RBOG"),"B_RBOG");
    Vector3D F_RSLDRL =  K_S2 * sys.Position_Vector("PRL_RSLD","P6RL_RBOG") + C_S2 * sys.Dt(sys.Position_Vector("PRL_RSLD","P6RL_RBOG"),"B_RBOG");
    Vector3D F_RSLDFR =  K_S2 * sys.Position_Vector("PFR_RSLD","P6FR_RBOG") + C_S2 * sys.Dt(sys.Position_Vector("PFR_RSLD","P6FR_RBOG"),"B_RBOG");
    Vector3D F_RSLDRR =  K_S2 * sys.Position_Vector("PRR_RSLD","P6RR_RBOG") + C_S2 * sys.Dt(sys.Position_Vector("PRR_RSLD","P6RR_RBOG"),"B_RBOG");  

  
    Vector3D M_RSLD  = *sys.new_Vector3D("M_RSLDL",0,0,0, "B_RBOG");
     
    Wrench3D * TA_RSLDFL= sys.new_Wrench3D ( "TA_RSLDFL",-F_RSLDFL , -M_RSLD, P6FL_RBOG ,RBOG , "Constitutive") ;
    Wrench3D * TR_RSLDFL= sys.new_Wrench3D ( "TR_RSLDFL", F_RSLDFL ,  M_RSLD, PFL_RSLD  ,RSLD , "Constitutive") ; 
    Wrench3D * TA_RSLDRL= sys.new_Wrench3D ( "TA_RSLDRL",-F_RSLDRL , -M_RSLD, P6RL_RBOG ,RBOG , "Constitutive") ; 
    Wrench3D * TR_RSLDRL= sys.new_Wrench3D ( "TR_RSLDRL", F_RSLDRL ,  M_RSLD, PRL_RSLD  ,RSLD , "Constitutive") ;

    Wrench3D * TA_RSLDFR= sys.new_Wrench3D ( "TA_RSLDFR",-F_RSLDFR , -M_RSLD, P6FR_RBOG ,RBOG , "Constitutive") ;
    Wrench3D * TR_RSLDFR= sys.new_Wrench3D ( "TR_RSLDFR", F_RSLDFR ,  M_RSLD, PFR_RSLD  ,RSLD , "Constitutive") ; 
    Wrench3D * TA_RSLDRR= sys.new_Wrench3D ( "TA_RSLDRR",-F_RSLDRR , -M_RSLD, P6RR_RBOG ,RBOG , "Constitutive") ; 
    Wrench3D * TR_RSLDRR= sys.new_Wrench3D ( "TR_RSLDRR", F_RSLDRR ,  M_RSLD, PRR_RSLD  ,RSLD , "Constitutive") ;




    Vector3D F_FSLDFL =  K_S2 * sys.Position_Vector("PFL_FSLD","P6FL_FBOG") + C_S2 * sys.Dt(sys.Position_Vector("PFL_FSLD","P6FL_FBOG"),"B_FBOG");
    Vector3D F_FSLDRL =  K_S2 * sys.Position_Vector("PRL_FSLD","P6RL_FBOG") + C_S2 * sys.Dt(sys.Position_Vector("PRL_FSLD","P6RL_FBOG"),"B_FBOG");
    Vector3D F_FSLDFR =  K_S2 * sys.Position_Vector("PFR_FSLD","P6FR_FBOG") + C_S2 * sys.Dt(sys.Position_Vector("PFR_FSLD","P6FR_FBOG"),"B_FBOG");
    Vector3D F_FSLDRR =  K_S2 * sys.Position_Vector("PRR_FSLD","P6RR_FBOG") + C_S2 * sys.Dt(sys.Position_Vector("PRR_FSLD","P6RR_FBOG"),"B_FBOG");  

  
    Vector3D M_FSLD  = *sys.new_Vector3D("M_FSLDL",0,0,0, "B_FBOG");
     //~ 
    Wrench3D * TA_FSLDFL= sys.new_Wrench3D ( "TA_FSLDFL",-F_FSLDFL , -M_FSLD, P6FL_FBOG ,FBOG , "Constitutive") ;
    Wrench3D * TR_FSLDFL= sys.new_Wrench3D ( "TR_FSLDFL", F_FSLDFL ,  M_FSLD, PFL_FSLD  ,FSLD , "Constitutive") ; 
    Wrench3D * TA_FSLDRL= sys.new_Wrench3D ( "TA_FSLDRL",-F_FSLDRL , -M_FSLD, P6RL_FBOG ,FBOG , "Constitutive") ; 
    Wrench3D * TR_FSLDRL= sys.new_Wrench3D ( "TR_FSLDRL", F_FSLDRL ,  M_FSLD, PRL_FSLD  ,FSLD , "Constitutive") ;

    Wrench3D * TA_FSLDFR= sys.new_Wrench3D ( "TA_FSLDFR",-F_FSLDFR , -M_FSLD, P6FR_FBOG ,FBOG , "Constitutive") ;
    Wrench3D * TR_FSLDFR= sys.new_Wrench3D ( "TR_FSLDFR", F_FSLDFR ,  M_FSLD, PFR_FSLD  ,FSLD , "Constitutive") ; 
    Wrench3D * TA_FSLDRR= sys.new_Wrench3D ( "TA_FSLDRR",-F_FSLDRR , -M_FSLD, P6RR_FBOG ,FBOG , "Constitutive") ; 
    Wrench3D * TR_FSLDRR= sys.new_Wrench3D ( "TR_FSLDRR", F_FSLDRR ,  M_FSLD, PRR_FSLD  ,FSLD , "Constitutive") ;





// ************************************************************************************************
//	Define Gravity and Inertia Wrenches	
// ************************************************************************************************

    cout << "Define Gravity and Inertia Wrenches" << endl;

    //	Gravity    
    
    Wrench3D * Gravity_WAG   = sys.Gravity_Wrench("WAG");
    
    Wrench3D * Gravity_RBOG   = sys.Gravity_Wrench("RBOG");   
    Wrench3D * Gravity_RMOTF  = sys.Gravity_Wrench("RMOTF");
    Wrench3D * Gravity_RMOTR  = sys.Gravity_Wrench("RMOTR");
    Wrench3D * Gravity_RROTF  = sys.Gravity_Wrench("RROTF");
    Wrench3D * Gravity_RROTR  = sys.Gravity_Wrench("RROTR"); 
    Wrench3D * Gravity_RWHSF  = sys.Gravity_Wrench("RWHSF");    
    Wrench3D * Gravity_RWHSR  = sys.Gravity_Wrench("RWHSR"); 
    Wrench3D * Gravity_RAXBFL = sys.Gravity_Wrench("RAXBFL");
    Wrench3D * Gravity_RAXBFR = sys.Gravity_Wrench("RAXBFR");
    Wrench3D * Gravity_RAXBRL = sys.Gravity_Wrench("RAXBRL");
    Wrench3D * Gravity_RAXBRR = sys.Gravity_Wrench("RAXBRR");
    Wrench3D * Gravity_RSLD   = sys.Gravity_Wrench("RSLD");

    Wrench3D * Gravity_FBOG   = sys.Gravity_Wrench("FBOG");   
    Wrench3D * Gravity_FWHSF  = sys.Gravity_Wrench("FWHSF");    
    Wrench3D * Gravity_FWHSR  = sys.Gravity_Wrench("FWHSR"); 
    Wrench3D * Gravity_FAXBFL = sys.Gravity_Wrench("FAXBFL");
    Wrench3D * Gravity_FAXBFR = sys.Gravity_Wrench("FAXBFR");
    Wrench3D * Gravity_FAXBRL = sys.Gravity_Wrench("FAXBRL");
    Wrench3D * Gravity_FAXBRR = sys.Gravity_Wrench("FAXBRR");
    Wrench3D * Gravity_FSLD   = sys.Gravity_Wrench("FSLD");
    
    
    //	Inertia    
    //~ Wrench3D * Inertia_WAG   = sys.Inertia_Wrench("WAG");
    //~ 
    //~ Wrench3D * Inertia_RBOG   = sys.Inertia_Wrench("RBOG");
    //~ Wrench3D * Inertia_RMOTF  = sys.Inertia_Wrench("RMOTF");
    //~ Wrench3D * Inertia_RMOTR  = sys.Inertia_Wrench("RMOTR");
    //~ Wrench3D * Inertia_RROTF  = sys.Inertia_Wrench("RROTF");
    //~ Wrench3D * Inertia_RROTR  = sys.Inertia_Wrench("RROTR");     
    //~ Wrench3D * Inertia_RWHSF  = sys.Inertia_Wrench("RWHSF");   
    //~ Wrench3D * Inertia_RWHSR  = sys.Inertia_Wrench("RWHSR");   
    //~ Wrench3D * Inertia_RAXBFL = sys.Inertia_Wrench("RAXBFL");
    //~ Wrench3D * Inertia_RAXBFR = sys.Inertia_Wrench("RAXBFR");
    //~ Wrench3D * Inertia_RAXBRL = sys.Inertia_Wrench("RAXBRL");
    //~ Wrench3D * Inertia_RAXBRR = sys.Inertia_Wrench("RAXBRR");
    //~ Wrench3D * Inertia_RSLD   = sys.Inertia_Wrench("RSLD");
    //~ 
    //~ Wrench3D * Inertia_FBOG   = sys.Inertia_Wrench("FBOG");
    //~ Wrench3D * Inertia_FWHSF  = sys.Inertia_Wrench("FWHSF");   
    //~ Wrench3D * Inertia_FWHSR  = sys.Inertia_Wrench("FWHSR");   
    //~ Wrench3D * Inertia_FAXBFL = sys.Inertia_Wrench("FAXBFL");
    //~ Wrench3D * Inertia_FAXBFR = sys.Inertia_Wrench("FAXBFR");
    //~ Wrench3D * Inertia_FAXBRL = sys.Inertia_Wrench("FAXBRL");
    //~ Wrench3D * Inertia_FAXBRR = sys.Inertia_Wrench("FAXBRR");
    //~ Wrench3D * Inertia_FSLD   = sys.Inertia_Wrench("FSLD");
    //	Constitutive

    //	External
    Wrench3D * RMOTF_Torque = sys.new_Wrench3D ( "RMOTF_Torque",F_RMOTF ,M_RMOTF , O_RROTF , RMOTF ,RROTF, "External") ;
    Wrench3D * RMOTR_Torque = sys.new_Wrench3D ( "RMOTR_Torque",F_RMOTR ,M_RMOTR , O_RROTR , RMOTR ,RROTR, "External") ;
	
	
	


// ************************************************************************************************
// 	 Kinematic Equations 
// ************************************************************************************************


// ************************************************************************************************
//      Contact Wheel - Rail
// ************************************************************************************************

    Matrix Phi(40,1);


    Vector3D O_PRailL = *sys.new_Vector3D("O_PRailL",0,  L_RAIL/2.0,0,"B_RAIL");
    Vector3D O_PRailR = *sys.new_Vector3D("O_PRailR",0, -L_RAIL/2.0,0,"B_RAIL");

    Point * O_RailL = sys.new_Point("O_RailL","O",&O_PRailL);
    Point * O_RailR = sys.new_Point("O_RailR","O",&O_PRailR);

    //REAR BOGIE
    // ************************************************************************************************

cout << " RFR " <<endl;
    //REAR BOGIE, FRONT SIDE, RIGHT WHEEL RFR
    Vector3D ORWHSF_OWRFR   = *sys.new_Vector3D("ORWHSF_OWRFR", 0,-L_WHS/2.0,0,"B_RWHSF_a");     
    Point * O_WRFR  = sys.new_Point("O_WRFR","O_RWHSF",&ORWHSF_OWRFR);

    symbol_numeric thetaW_RFR = *sys.new_AuxCoordinate("thetaW_RFR","dthetaW_RFR","ddthetaW_RFR",0.0,0.0,0.0);
    symbol_numeric uW_RFR = *sys.new_AuxCoordinate("uW_RFR","duW_RFR","dduW_RFR",0.0,0.0,0.0);

  
    symbol_numeric aW_RFR = *sys.new_Parameter("aW_RFR",0.0);//spline's coefficients
    symbol_numeric bW_RFR = *sys.new_Parameter("bW_RFR",0.0);
    symbol_numeric cW_RFR = *sys.new_Parameter("cW_RFR",-0.1);
    symbol_numeric dW_RFR = *sys.new_Parameter("dW_RFR",-0.5);
    symbol_numeric lW_RFR = *sys.new_Parameter("lW_RFR",0.0);//size of the spline    
    

    ex sW_RFR = uW_RFR - lW_RFR;
    ex splineW_RFR =   dW_RFR + sW_RFR * ( cW_RFR + sW_RFR * (bW_RFR + sW_RFR * aW_RFR ) );
    Vector3D fW_RFR = *sys.new_Vector3D("fW_RFR",-splineW_RFR*sin(thetaW_RFR),uW_RFR,splineW_RFR*cos(thetaW_RFR),"B_RWHSF_a");
    Vector3D rW_RFR = sys.Position_Vector("O","O_WRFR")+fW_RFR;
    Vector3D t1W_RFR= sys.diff ( rW_RFR , thetaW_RFR);
    Vector3D t2W_RFR= sys.diff ( rW_RFR , uW_RFR);
    Vector3D nW_RFR = t1W_RFR^t2W_RFR;

    symbol_numeric uR_RFR = *sys.new_AuxCoordinate("uR_RFR","duR_RFR","dduR_RFR", 0.0 ,0.0,0.0);
    symbol_numeric xR_RFR = *sys.new_AuxCoordinate("xR_RFR","dxR_RFR","ddxR_RFR", -3.65595 ,0.0,0.0);

   
    symbol_numeric aR_RFR = *sys.new_Parameter("aR_RFR",0.0);//spline's coefficients right wheel
    symbol_numeric bR_RFR = *sys.new_Parameter("bR_RFR",-20.0);
    symbol_numeric cR_RFR = *sys.new_Parameter("cR_RFR",0.0);
    symbol_numeric dR_RFR = *sys.new_Parameter("dR_RFR",0.1);
    symbol_numeric lR_RFR = *sys.new_Parameter("lR_RFR",0.0); //size of the spline    
    

    ex sR_RFR = uR_RFR - lR_RFR;
    ex splineR_RFR =   dR_RFR + sR_RFR * ( cR_RFR + sR_RFR * (bR_RFR + sR_RFR * aR_RFR ) );
    Vector3D fR_RFR = *sys.new_Vector3D("fR_RFR",xR_RFR,uR_RFR,splineR_RFR,"B_RAIL");
    Vector3D rR_RFR = sys.Position_Vector("O","O_RailR")+fR_RFR;
    Vector3D t1R_RFR= sys.diff ( rR_RFR , xR_RFR);
    Vector3D t2R_RFR= sys.diff ( rR_RFR , uR_RFR);
    Vector3D nR_RFR = t1R_RFR^t2R_RFR;

    //normal and tangent unitary vectors at contact point
    Vector3D u_nW_RFR =( 1 /sqrt( nW_RFR * nW_RFR )) * nW_RFR;
    Vector3D u_t1W_RFR =( 1 /sqrt( t1W_RFR * t1W_RFR )) * t1W_RFR;
    Vector3D u_t2W_RFR =( 1 /sqrt( t2W_RFR * t2W_RFR )) * t2W_RFR;   
    Vector3D u_nR_RFR =( 1 /sqrt( nR_RFR * nR_RFR )) * nR_RFR;
    Vector3D u_t1R_RFR =( 1 /sqrt( t1R_RFR * t1R_RFR )) * t1R_RFR;
    Vector3D u_t2R_RFR =( 1 /sqrt( t2R_RFR * t2R_RFR )) * t2R_RFR;


    Point * PWcon_RFR   = sys.new_Point("PWcon_RFR","O",&rW_RFR);
    Point * PRcon_RFR   = sys.new_Point("PRcon_RFR","O",&rR_RFR);
    Vector3D VPconRW_RFR = sys.Position_Vector("PRcon_RFR","PWcon_RFR");


    Vector3D FKALKER_RFR = (Fx_RFR* u_t1R_RFR) + (Fy_RFR * u_t2R_RFR);
    Vector3D MKALKER_RFR = Mz_RFR * u_nR_RFR;


    Wrench3D * FKalker_RFR = sys.new_Wrench3D ( "FKalker_RFR", FKALKER_RFR, MKALKER_RFR , PWcon_RFR, RWHSF , "External") ;
    
    Phi(0,0) = u_t1R_RFR * (VPconRW_RFR);
    Phi(1,0) = u_t2R_RFR * (VPconRW_RFR);
    Phi(2,0) = u_nR_RFR  * (VPconRW_RFR);
    Phi(3,0) = u_nR_RFR*t1W_RFR;
    Phi(4,0) = u_nR_RFR*t2W_RFR;

    //~ symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");
    //~ symbol_numeric lambda2  = *sys.new_Joint_Unknown("lambda2");
    //~ symbol_numeric lambda3  = *sys.new_Joint_Unknown("lambda3");
    //~ symbol_numeric lambda4  = *sys.new_Joint_Unknown("lambda4");
    //~ symbol_numeric lambda5  = *sys.new_Joint_Unknown("lambda5");
    
  
    cout << " RFL " <<endl;
    // ************************************************************************************************
    //REAR BOGIE, FRONT SIDE, LEFT WHEEL RFL

    Vector3D ORWHSF_OWRFL   = *sys.new_Vector3D("ORWHSF_OWRFL", 0,+L_WHS/2.0,0,"B_RWHSF_a"); 
    Point * O_WRFL  = sys.new_Point("O_WRFL","O_RWHSF",&ORWHSF_OWRFL);

    symbol_numeric thetaW_RFL = *sys.new_AuxCoordinate("thetaW_RFL","dthetaW_RFL","ddthetaW_RFL",0.0,0.0,0.0);
    symbol_numeric uW_RFL = *sys.new_AuxCoordinate("uW_RFL","duW_RFL","dduW_RFL",0.0,0.0,0.0);

    symbol_numeric aW_RFL = *sys.new_Parameter("aW_RFL",0.0);//spline's coefficients
    symbol_numeric bW_RFL = *sys.new_Parameter("bW_RFL",0.0);
    symbol_numeric cW_RFL = *sys.new_Parameter("cW_RFL",0.1);
    symbol_numeric dW_RFL = *sys.new_Parameter("dW_RFL",-0.5);
    symbol_numeric lW_RFL = *sys.new_Parameter("lW_RFL",0.0);//size of the spline

    ex sW_RFL = uW_RFL - lW_RFL;
    ex splineW_RFL =   dW_RFL + sW_RFL * ( cW_RFL + sW_RFL * (bW_RFL + sW_RFL * aW_RFL ) );
    Vector3D fW_RFL = *sys.new_Vector3D("fW_RFL",-splineW_RFL*sin(thetaW_RFL),uW_RFL,splineW_RFL*cos(thetaW_RFL),"B_RWHSF_a");
    Vector3D rW_RFL = sys.Position_Vector("O","O_WRFL")+fW_RFL;
    Vector3D t1W_RFL= sys.diff ( rW_RFL , thetaW_RFL);
    Vector3D t2W_RFL= sys.diff ( rW_RFL , uW_RFL);
    Vector3D nW_RFL = t1W_RFL^t2W_RFL;

    symbol_numeric uR_RFL = *sys.new_AuxCoordinate("uR_RFL","duR_RFL","dduR_RFL", 0.0 ,0.0,0.0);
    symbol_numeric xR_RFL = *sys.new_AuxCoordinate("xR_RFL","dxR_RFL","ddxR_RFL", -3.65595 ,0.0,0.0);

    symbol_numeric aR_RFL = *sys.new_Parameter("aR_RFL",0.0);//spline's coefficients 
    symbol_numeric bR_RFL = *sys.new_Parameter("bR_RFL",-20.0);
    symbol_numeric cR_RFL = *sys.new_Parameter("cR_RFL",0.0);
    symbol_numeric dR_RFL = *sys.new_Parameter("dR_RFL",0.1);
    symbol_numeric lR_RFL = *sys.new_Parameter("lR_RFL",0.0); //size of the spline 

    ex sR_RFL = uR_RFL - lR_RFL;
    ex splineR_RFL =   dR_RFL + sR_RFL * ( cR_RFL + sR_RFL * (bR_RFL + sR_RFL * aR_RFL ) );
    Vector3D fR_RFL = *sys.new_Vector3D("fR_RFL",xR_RFL,uR_RFL,splineR_RFL,"B_RAIL");
    Vector3D rR_RFL = sys.Position_Vector("O","O_RailL")+fR_RFL;
    Vector3D t1R_RFL= sys.diff ( rR_RFL , xR_RFL);
    Vector3D t2R_RFL= sys.diff ( rR_RFL , uR_RFL);
    Vector3D nR_RFL = t1R_RFL^t2R_RFL;

    //normal and tangent unitary vectors at contact point
    Vector3D u_nW_RFL  = ( 1 /sqrt( nW_RFL * nW_RFL )) * nW_RFL;
    Vector3D u_t1W_RFL = ( 1 /sqrt( t1W_RFL * t1W_RFL )) * t1W_RFL;
    Vector3D u_t2W_RFL = ( 1 /sqrt( t2W_RFL * t2W_RFL )) * t2W_RFL;   
    Vector3D u_nR_RFL  = ( 1 /sqrt( nR_RFL * nR_RFL )) * nR_RFL;
    Vector3D u_t1R_RFL = ( 1 /sqrt( t1R_RFL * t1R_RFL )) * t1R_RFL;
    Vector3D u_t2R_RFL = ( 1 /sqrt( t2R_RFL * t2R_RFL )) * t2R_RFL;

    Point * PWcon_RFL   = sys.new_Point("PWcon_RFL","O",&rW_RFL);
    Point * PRcon_RFL   = sys.new_Point("PRcon_RFL","O",&rR_RFL);
    Vector3D VPconRW_RFL = sys.Position_Vector("PRcon_RFL","PWcon_RFL");


    Vector3D FKALKER_RFL = (Fx_RFL* u_t1R_RFL) + (Fy_RFL * u_t2R_RFL);
    Vector3D MKALKER_RFL = Mz_RFL * u_nR_RFL;

    Wrench3D * FKalker_RFL = sys.new_Wrench3D ( "FKalker_RFL", FKALKER_RFL, MKALKER_RFL , PWcon_RFL, RWHSF , "External") ;

    Phi(5,0) = u_t1R_RFL * VPconRW_RFL;
    Phi(6,0) = u_t2R_RFL * VPconRW_RFL;
    Phi(7,0) = u_nR_RFL  * VPconRW_RFL;
    Phi(8,0) = u_nR_RFL * t1W_RFL;
    Phi(9,0) = u_nR_RFL * t2W_RFL;

    //~ symbol_numeric lambda6   = *sys.new_Joint_Unknown("lambda6");
    //~ symbol_numeric lambda7   = *sys.new_Joint_Unknown("lambda7");
    //~ symbol_numeric lambda8   = *sys.new_Joint_Unknown("lambda8");
    //~ symbol_numeric lambda9   = *sys.new_Joint_Unknown("lambda9");
    //~ symbol_numeric lambda10  = *sys.new_Joint_Unknown("lambda10");


cout << " RRR" <<endl;
    // ************************************************************************************************
    //REAR BOGIE, REAR SIDE, RIGHT WHEEL RRR

    Vector3D ORWHSR_OWRRR   = *sys.new_Vector3D("ORWHSR_OWRRR", 0,-L_WHS/2.0,0,"B_RWHSR_a"); 
    Point * O_WRRR  = sys.new_Point("O_WRRR","O_RWHSR",&ORWHSR_OWRRR);

    symbol_numeric thetaW_RRR = *sys.new_AuxCoordinate("thetaW_RRR","dthetaW_RRR","ddthetaW_RRR",0.0,0.0,0.0);
    symbol_numeric uW_RRR = *sys.new_AuxCoordinate("uW_RRR","duW_RRR","dduW_RRR",0.0,0.0,0.0);

    symbol_numeric aW_RRR = *sys.new_Parameter("aW_RRR",0.0);//spline's coefficients
    symbol_numeric bW_RRR = *sys.new_Parameter("bW_RRR",0.0);
    symbol_numeric cW_RRR = *sys.new_Parameter("cW_RRR",-0.1);
    symbol_numeric dW_RRR = *sys.new_Parameter("dW_RRR",-0.5);
    symbol_numeric lW_RRR = *sys.new_Parameter("lW_RRR",0.0);//size of the spline

    ex sW_RRR = uW_RRR - lW_RRR;
    ex splineW_RRR =   dW_RRR + sW_RRR * ( cW_RRR + sW_RRR * (bW_RRR + sW_RRR * aW_RRR ) );
    Vector3D fW_RRR = *sys.new_Vector3D("fW_RRR",-splineW_RRR*sin(thetaW_RRR),uW_RRR,splineW_RRR*cos(thetaW_RRR),"B_RWHSR_a");
    Vector3D rW_RRR = sys.Position_Vector("O","O_WRRR")+fW_RRR;
    Vector3D t1W_RRR= sys.diff ( rW_RRR , thetaW_RRR);
    Vector3D t2W_RRR= sys.diff ( rW_RRR , uW_RRR);
    Vector3D nW_RRR = t1W_RRR^t2W_RRR;



    symbol_numeric uR_RRR = *sys.new_AuxCoordinate("uR_RRR","duR_RRR","dduR_RRR", 0.0,0.0,0.0);
    symbol_numeric xR_RRR = *sys.new_AuxCoordinate("xR_RRR","dxR_RRR","ddxR_RRR", -5.84095 ,0.0,0.0);

    symbol_numeric aR_RRR = *sys.new_Parameter("aR_RRR",0.0);//spline's coefficients right wheel
    symbol_numeric bR_RRR = *sys.new_Parameter("bR_RRR",-20.0);
    symbol_numeric cR_RRR = *sys.new_Parameter("cR_RRR",0.0);
    symbol_numeric dR_RRR = *sys.new_Parameter("dR_RRR",0.1);
    symbol_numeric lR_RRR = *sys.new_Parameter("lR_RRR",0.0); //size of the spline 

    ex sR_RRR = uR_RRR - lR_RRR;
    ex splineR_RRR =   dR_RRR + sR_RRR * ( cR_RRR + sR_RRR * (bR_RRR + sR_RRR * aR_RRR ) );
    Vector3D fR_RRR = *sys.new_Vector3D("fR_RRR",xR_RRR,uR_RRR,splineR_RRR,"B_RAIL");
    Vector3D rR_RRR = sys.Position_Vector("O","O_RailR")+fR_RRR;
    Vector3D t1R_RRR= sys.diff ( rR_RRR , xR_RRR);
    Vector3D t2R_RRR= sys.diff ( rR_RRR , uR_RRR);
    Vector3D nR_RRR = t1R_RRR^t2R_RRR;

    //normal and tangent unitary vectors at contact point
    Vector3D u_nW_RRR = ( 1 /sqrt( nW_RRR * nW_RRR )) * nW_RRR;
    Vector3D u_t1W_RRR =( 1 /sqrt( t1W_RRR * t1W_RRR )) * t1W_RRR;
    Vector3D u_t2W_RRR =( 1 /sqrt( t2W_RRR * t2W_RRR )) * t2W_RRR;    
    Vector3D u_nR_RRR = ( 1 /sqrt( nR_RRR * nR_RRR )) * nR_RRR;
    Vector3D u_t1R_RRR =( 1 /sqrt( t1R_RRR * t1R_RRR )) * t1R_RRR;
    Vector3D u_t2R_RRR =( 1 /sqrt( t2R_RRR * t2R_RRR )) * t2R_RRR;

    Point * PWcon_RRR   = sys.new_Point("PWcon_RRR","O",&rW_RRR);
    Point * PRcon_RRR   = sys.new_Point("PRcon_RRR","O",&rR_RRR);
    Vector3D VPconRW_RRR= sys.Position_Vector("PRcon_RRR","PWcon_RRR");
    
    Phi(10,0) = u_t1R_RRR * (VPconRW_RRR);
    Phi(11,0) = u_t2R_RRR * (VPconRW_RRR);
    Phi(12,0) = u_nR_RRR  * (VPconRW_RRR);
    Phi(13,0) = u_nR_RRR * t1W_RRR;
    Phi(14,0) = u_nR_RRR * t2W_RRR;


    
    Vector3D FKALKER_RRR = (Fx_RRR* u_t1R_RRR) + (Fy_RRR * u_t2R_RRR);
    Vector3D MKALKER_RRR = Mz_RRR * u_nR_RRR;

    Wrench3D * FKalker_RRR = sys.new_Wrench3D ( "FKalker_RRR", FKALKER_RRR, MKALKER_RRR , PWcon_RRR, RWHSR , "External") ;

    //~ symbol_numeric lambda11 = *sys.new_Joint_Unknown("lambda11");
    //~ symbol_numeric lambda12 = *sys.new_Joint_Unknown("lambda12");
    //~ symbol_numeric lambda13 = *sys.new_Joint_Unknown("lambda13");
    //~ symbol_numeric lambda14 = *sys.new_Joint_Unknown("lambda14");
    //~ symbol_numeric lambda15 = *sys.new_Joint_Unknown("lambda15");


cout << " RRL" <<endl;
    // ************************************************************************************************
    //REAR BOGIE, REAR SIDE, LEFT WHEEL RRL

    Vector3D ORWHSR_OWRRL   = *sys.new_Vector3D("ORWHSR_OWRRL", 0,+L_WHS/2.0,0,"B_RWHSR_a"); 
    Point * O_WRRL  = sys.new_Point("O_WRRL","O_RWHSR",&ORWHSR_OWRRL);

    symbol_numeric thetaW_RRL = *sys.new_AuxCoordinate("thetaW_RRL","dthetaW_RRL","ddthetaW_RRL",0.0,0.0,0.0);
    symbol_numeric uW_RRL = *sys.new_AuxCoordinate("uW_RRL","duW_RRL","dduW_RRL",0.0,0.0,0.0);

    symbol_numeric aW_RRL = *sys.new_Parameter("aW_RRL",0.0);//spline's coefficients
    symbol_numeric bW_RRL = *sys.new_Parameter("bW_RRL",0.0);
    symbol_numeric cW_RRL = *sys.new_Parameter("cW_RRL",0.1);
    symbol_numeric dW_RRL = *sys.new_Parameter("dW_RRL",-0.5);
    symbol_numeric lW_RRL = *sys.new_Parameter("lW_RRL",0.0);//size of the spline

    ex sW_RRL = uW_RRL - lW_RRL;
    ex splineW_RRL =   dW_RRL + sW_RRL * ( cW_RRL + sW_RRL * (bW_RRL + sW_RRL * aW_RRL ) );
    Vector3D fW_RRL = *sys.new_Vector3D("fW_RRL",-splineW_RRL*sin(thetaW_RRL),uW_RRL,splineW_RRL*cos(thetaW_RRL),"B_RWHSR_a");
    Vector3D rW_RRL = sys.Position_Vector("O","O_WRRL")+fW_RRL;
    Vector3D t1W_RRL= sys.diff ( rW_RRL , thetaW_RRL);
    Vector3D t2W_RRL= sys.diff ( rW_RRL , uW_RRL);
    Vector3D nW_RRL = t1W_RRL^t2W_RRL;

    symbol_numeric uR_RRL = *sys.new_AuxCoordinate("uR_RRL","duR_RRL","dduR_RRL", 0.0,0.0,0.0);
    symbol_numeric xR_RRL = *sys.new_AuxCoordinate("xR_RRL","dxR_RRL","ddxR_RRL", -5.84095 ,0.0,0.0);

    symbol_numeric aR_RRL = *sys.new_Parameter("aR_RRL",0.0);//spline's coefficients left wheel
    symbol_numeric bR_RRL = *sys.new_Parameter("bR_RRL",-20.0);
    symbol_numeric cR_RRL = *sys.new_Parameter("cR_RRL",0.0);
    symbol_numeric dR_RRL = *sys.new_Parameter("dR_RRL",0.1);
    symbol_numeric lR_RRL = *sys.new_Parameter("lR_RRL",0.0); //size of the spline 

    ex sR_RRL = uR_RRL - lR_RRL;
    ex splineR_RRL =   dR_RRL + sR_RRL * ( cR_RRL + sR_RRL * (bR_RRL + sR_RRL * aR_RRL ) );
    Vector3D fR_RRL= *sys.new_Vector3D("fR_RRL",xR_RRL,uR_RRL,splineR_RRL,"B_RAIL");
    Vector3D rR_RRL = sys.Position_Vector("O","O_RailL")+fR_RRL;
    Vector3D t1R_RRL= sys.diff ( rR_RRL , xR_RRL);
    Vector3D t2R_RRL= sys.diff ( rR_RRL , uR_RRL);
    Vector3D nR_RRL = t1R_RRL^t2R_RRL;

    //normal and tangent unitary vectors at contact point
    Vector3D u_nW_RRL =( 1 /sqrt( nW_RRL * nW_RRL )) * nW_RRL;
    Vector3D u_t1W_RRL =( 1 /sqrt( t1W_RRL * t1W_RRL )) * t1W_RRL;
    Vector3D u_t2W_RRL =( 1 /sqrt( t2W_RRL * t2W_RRL )) * t2W_RRL;    
    Vector3D u_nR_RRL =( 1 /sqrt( nR_RRL * nR_RRL )) * nR_RRL;
    Vector3D u_t1R_RRL =( 1 /sqrt( t1R_RRL * t1R_RRL )) * t1R_RRL;
    Vector3D u_t2R_RRL =( 1 /sqrt( t2R_RRL * t2R_RRL )) * t2R_RRL;

    Point * PWcon_RRL   = sys.new_Point("PWcon_RRL","O",&rW_RRL);
    Point * PRcon_RRL   = sys.new_Point("PRcon_RRL","O",&rR_RRL);
    Vector3D VPconRW_RRL= sys.Position_Vector("PRcon_RRL","PWcon_RRL");
    
    Phi(15,0) = u_t1R_RRL * VPconRW_RRL;
    Phi(16,0) = u_t2R_RRL * VPconRW_RRL;
    Phi(17,0) = u_nR_RRL  * VPconRW_RRL;
    Phi(18,0) = u_nR_RRL * t1W_RRL;
    Phi(19,0) = u_nR_RRL * t2W_RRL;

    Vector3D FKALKER_RRL = (Fx_RRL* u_t1R_RRL) + (Fy_RRL * u_t2R_RRL);
    Vector3D MKALKER_RRL = Mz_RRL * u_nR_RRL;

    Wrench3D * FKalker_RRL = sys.new_Wrench3D ( "FKalker_RRL", FKALKER_RRL, MKALKER_RRL , PWcon_RRL, RWHSR , "External") ;

    //~ symbol_numeric lambda16 = *sys.new_Joint_Unknown("lambda16");
    //~ symbol_numeric lambda17 = *sys.new_Joint_Unknown("lambda17");
    //~ symbol_numeric lambda18 = *sys.new_Joint_Unknown("lambda18");
    //~ symbol_numeric lambda19 = *sys.new_Joint_Unknown("lambda19");
    //~ symbol_numeric lambda20 = *sys.new_Joint_Unknown("lambda20");  

cout << " FFR" <<endl;   
    // ************************************************************************************************
    // FRONT BOGIE, FRONT SIDE, RIGHT WHEEL FFR
    Vector3D OFWHSF_OWFFR   = *sys.new_Vector3D("OFWHSF_OWFFR", 0,-L_WHS/2.0,0,"B_FWHSF_a"); 
    Point * O_WFFR  = sys.new_Point("O_WFFR","O_FWHSF",&OFWHSF_OWFFR);

    symbol_numeric thetaW_FFR = *sys.new_AuxCoordinate("thetaW_FFR","dthetaW_FFR","ddthetaW_FFR",0.0,0.0,0.0);
    symbol_numeric uW_FFR = *sys.new_AuxCoordinate("uW_FFR","duW_FFR","dduW_FFR",0.0,0.0,0.0);

    symbol_numeric aW_FFR = *sys.new_Parameter("aW_FFR",0.0);//spline's coefficients
    symbol_numeric bW_FFR = *sys.new_Parameter("bW_FFR",0.0);
    symbol_numeric cW_FFR = *sys.new_Parameter("cW_FFR",-0.1);
    symbol_numeric dW_FFR = *sys.new_Parameter("dW_FFR",-0.5);
    symbol_numeric lW_FFR = *sys.new_Parameter("lW_FFR",0.0);//size of the spline

    ex sW_FFR = uW_FFR - lW_FFR;
    ex splineW_FFR =   dW_FFR + sW_FFR * ( cW_FFR + sW_FFR * (bW_FFR + sW_FFR * aW_FFR ) );
    Vector3D fW_FFR = *sys.new_Vector3D("fW_FFR",-splineW_FFR*sin(thetaW_FFR),uW_FFR,splineW_FFR*cos(thetaW_FFR),"B_FWHSF_a");
    Vector3D rW_FFR = sys.Position_Vector("O","O_WFFR")+fW_FFR;
    Vector3D t1W_FFR= sys.diff ( rW_FFR , thetaW_FFR);
    Vector3D t2W_FFR= sys.diff ( rW_FFR , uW_FFR);
    Vector3D nW_FFR = t1W_FFR^t2W_FFR;



    symbol_numeric uR_FFR = *sys.new_AuxCoordinate("uR_FFR","duR_FFR","dduR_FFR", 0.0,0.0,0.0);
    symbol_numeric xR_FFR = *sys.new_AuxCoordinate("xR_FFR","dxR_FFR","ddxR_FFR", 5.84404 ,0.0,0.0);

    symbol_numeric aR_FFR = *sys.new_Parameter("aR_FFR",0.0);//spline's coefficients right wheel
    symbol_numeric bR_FFR = *sys.new_Parameter("bR_FFR",-20.0);
    symbol_numeric cR_FFR = *sys.new_Parameter("cR_FFR",0.0);
    symbol_numeric dR_FFR = *sys.new_Parameter("dR_FFR",0.1);
    symbol_numeric lR_FFR = *sys.new_Parameter("lR_FFR",0.0); //size of the spline 

    ex sR_FFR = uR_FFR - lR_FFR;
    ex splineR_FFR =   dR_FFR + sR_FFR * ( cR_FFR + sR_FFR * (bR_FFR + sR_FFR * aR_FFR ) );
    Vector3D fR_FFR = *sys.new_Vector3D("fR_FFR",xR_FFR,uR_FFR,splineR_FFR,"B_RAIL");
    Vector3D rR_FFR = sys.Position_Vector("O","O_RailR")+fR_FFR;
    Vector3D t1R_FFR= sys.diff ( rR_FFR , xR_FFR);
    Vector3D t2R_FFR= sys.diff ( rR_FFR , uR_FFR);
    Vector3D nR_FFR = t1R_FFR^t2R_FFR;

    //normal and tangent unitary vectors at contact point
    Vector3D u_nW_FFR = ( 1 /sqrt( nW_FFR * nW_FFR )) * nW_FFR;
    Vector3D u_t1W_FFR =( 1 /sqrt( t1W_FFR * t1W_FFR )) * t1W_FFR;
    Vector3D u_t2W_FFR =( 1 /sqrt( t2W_FFR * t2W_FFR )) * t2W_FFR;    
    Vector3D u_nR_FFR = ( 1 /sqrt( nR_FFR * nR_FFR )) * nR_FFR;
    Vector3D u_t1R_FFR =( 1 /sqrt( t1R_FFR * t1R_FFR )) * t1R_FFR;
    Vector3D u_t2R_FFR =( 1 /sqrt( t2R_FFR * t2R_FFR )) * t2R_FFR;

    
    Point * PWcon_FFR   = sys.new_Point("PWcon_FFR","O",&rW_FFR);
    Point * PRcon_FFR   = sys.new_Point("PRcon_FFR","O",&rR_FFR);
    Vector3D VPconRW_FFR= sys.Position_Vector("PRcon_FFR","PWcon_FFR");
    
    Phi(20,0) = u_t1R_FFR * VPconRW_FFR;
    Phi(21,0) = u_t2R_FFR * VPconRW_FFR;
    Phi(22,0) = u_nR_FFR  * VPconRW_FFR;
    Phi(23,0) = u_nR_FFR * t1W_FFR;
    Phi(24,0) = u_nR_FFR * t2W_FFR;


    Vector3D FKALKER_FFR = (Fx_FFR* u_t1R_FFR) + (Fy_FFR * u_t2R_FFR);
    Vector3D MKALKER_FFR = Mz_FFR * u_nR_FFR;

    Wrench3D * FKalker_FFR = sys.new_Wrench3D ( "FKalker_FFR", FKALKER_FFR, MKALKER_FFR , PWcon_FFR, FWHSF , "External") ;

    //~ symbol_numeric lambda21 = *sys.new_Joint_Unknown("lambda21");
    //~ symbol_numeric lambda22 = *sys.new_Joint_Unknown("lambda22");
    //~ symbol_numeric lambda23 = *sys.new_Joint_Unknown("lambda23");
    //~ symbol_numeric lambda24 = *sys.new_Joint_Unknown("lambda24");
    //~ symbol_numeric lambda25 = *sys.new_Joint_Unknown("lambda25");


cout << " FFL" <<endl;
    // ************************************************************************************************
    // FRONT BOGIE, FRONT SIDE, LEFT WHEEL FFL

    Vector3D OFWHSF_OWFFL   = *sys.new_Vector3D("OFWHSF_OWFFL", 0,L_WHS/2.0,0,"B_FWHSF_a"); 
    Point * O_WFFL  = sys.new_Point("O_WFFL","O_FWHSF",&OFWHSF_OWFFL);

    symbol_numeric thetaW_FFL = *sys.new_AuxCoordinate("thetaW_FFL","dthetaW_FFL","ddthetaW_FFL",0.0,0.0,0.0);
    symbol_numeric uW_FFL = *sys.new_AuxCoordinate("uW_FFL","duW_FFL","dduW_FFL",0.0,0.0,0.0);

    symbol_numeric aW_FFL = *sys.new_Parameter("aW_FFL",0.0);//spline's coefficients
    symbol_numeric bW_FFL = *sys.new_Parameter("bW_FFL",0.0);
    symbol_numeric cW_FFL = *sys.new_Parameter("cW_FFL",0.1);
    symbol_numeric dW_FFL = *sys.new_Parameter("dW_FFL",-0.5);
    symbol_numeric lW_FFL = *sys.new_Parameter("lW_FFL",0.0);//size of the spline
 
    ex sW_FFL = uW_FFL - lW_FFL;
    ex splineW_FFL =   dW_FFL + sW_FFL * ( cW_FFL + sW_FFL * (bW_FFL + sW_FFL * aW_FFL ) );
    Vector3D fW_FFL = *sys.new_Vector3D("fW_FFL",-splineW_FFL*sin(thetaW_FFL),uW_FFL,splineW_FFL*cos(thetaW_FFL),"B_FWHSF_a");
    Vector3D rW_FFL = sys.Position_Vector("O","O_WFFL")+fW_FFL;
    Vector3D t1W_FFL= sys.diff ( rW_FFL , thetaW_FFL);
    Vector3D t2W_FFL= sys.diff ( rW_FFL , uW_FFL);
    Vector3D nW_FFL = t1W_FFL^t2W_FFL;



    symbol_numeric uR_FFL = *sys.new_AuxCoordinate("uR_FFL","duR_FFL","dduR_FFL", 0.0,0.0,0.0);
    symbol_numeric xR_FFL = *sys.new_AuxCoordinate("xR_FFL","dxR_FFL","ddxR_FFL", 5.84404 ,0.0,0.0);

    symbol_numeric aR_FFL = *sys.new_Parameter("aR_FFL",0.0);//spline's coefficients 
    symbol_numeric bR_FFL = *sys.new_Parameter("bR_FFL",-20.0);
    symbol_numeric cR_FFL = *sys.new_Parameter("cR_FFL",0.0);
    symbol_numeric dR_FFL = *sys.new_Parameter("dR_FFL",0.1);
    symbol_numeric lR_FFL = *sys.new_Parameter("lR_FFL",0.0); //size of the spline 

    ex sR_FFL = uR_FFL - lR_FFL;
    ex splineR_FFL =   dR_FFL + sR_FFL * ( cR_FFL + sR_FFL * (bR_FFL + sR_FFL * aR_FFL ) );
    Vector3D fR_FFL = *sys.new_Vector3D("fR_FFL",xR_FFL,uR_FFL,splineR_FFL,"B_RAIL");
    Vector3D rR_FFL = sys.Position_Vector("O","O_RailL")+fR_FFL;
    Vector3D t1R_FFL= sys.diff ( rR_FFL , xR_FFL);
    Vector3D t2R_FFL= sys.diff ( rR_FFL , uR_FFL);
    Vector3D nR_FFL = t1R_FFL^t2R_FFL;

    //normal and tangent unitary vectors at contact point
    Vector3D u_nW_FFL =( 1 /sqrt( nW_FFL * nW_FFL )) * nW_FFL;
    Vector3D u_t1W_FFL =( 1 /sqrt( t1W_FFL * t1W_FFL )) * t1W_FFL;
    Vector3D u_t2W_FFL =( 1 /sqrt( t2W_FFL * t2W_FFL )) * t2W_FFL;    
    Vector3D u_nR_FFL =( 1 /sqrt( nR_FFL * nR_FFL )) * nR_FFL;
    Vector3D u_t1R_FFL =( 1 /sqrt( t1R_FFL * t1R_FFL )) * t1R_FFL;
    Vector3D u_t2R_FFL =( 1 /sqrt( t2R_FFL * t2R_FFL )) * t2R_FFL;

    Point * PWcon_FFL   = sys.new_Point("PWcon_FFL","O",&rW_FFL);
    Point * PRcon_FFL   = sys.new_Point("PRcon_FFL","O",&rR_FFL);
    Vector3D VPconRW_FFL= sys.Position_Vector("PRcon_FFL","PWcon_FFL");
    
    Phi(25,0) = u_t1R_FFL * VPconRW_FFL;
    Phi(26,0) = u_t2R_FFL * VPconRW_FFL;
    Phi(27,0) = u_nR_FFL  * VPconRW_FFL;
    Phi(28,0) = u_nR_FFL * t1W_FFL;
    Phi(29,0) = u_nR_FFL * t2W_FFL;


    Vector3D FKALKER_FFL = (Fx_FFL* u_t1R_FFL) + (Fy_FFL * u_t2R_FFL);
    Vector3D MKALKER_FFL = Mz_FFL * u_nR_FFL;

    Wrench3D * FKalker_FFL = sys.new_Wrench3D ( "FKalker_FFL", FKALKER_FFL, MKALKER_FFL , PWcon_FFL, FWHSF , "External") ;

    //~ symbol_numeric lambda26 = *sys.new_Joint_Unknown("lambda26");
    //~ symbol_numeric lambda27 = *sys.new_Joint_Unknown("lambda27");
    //~ symbol_numeric lambda28 = *sys.new_Joint_Unknown("lambda28");
    //~ symbol_numeric lambda29 = *sys.new_Joint_Unknown("lambda29");
    //~ symbol_numeric lambda30 = *sys.new_Joint_Unknown("lambda30");
    
cout << " FRR " <<endl;
    // ************************************************************************************************
    // FRONT BOGIE, REAR SIDE, RIGHT WHEEL FRR

    Vector3D OFWHSR_OWFRR   = *sys.new_Vector3D("OFWHSR_OWFRR", 0,-L_WHS/2.0,0,"B_FWHSR_a"); 
    Point * O_WFRR  = sys.new_Point("O_WFRR","O_FWHSR",&OFWHSR_OWFRR);

    symbol_numeric thetaW_FRR = *sys.new_AuxCoordinate("thetaW_FRR","dthetaW_FRR","ddthetaW_FRR",0.0,0.0,0.0);
    symbol_numeric uW_FRR = *sys.new_AuxCoordinate("uW_FRR","duW_FRR","dduW_FRR",0.0,0.0,0.0);

    symbol_numeric aW_FRR = *sys.new_Parameter("aW_FRR",0.0);//spline's coefficients
    symbol_numeric bW_FRR = *sys.new_Parameter("bW_FRR",0.0);
    symbol_numeric cW_FRR = *sys.new_Parameter("cW_FRR",-0.1);
    symbol_numeric dW_FRR = *sys.new_Parameter("dW_FRR",-0.5);
    symbol_numeric lW_FRR = *sys.new_Parameter("lW_FRR",0.0);//size of the spline

    ex sW_FRR = uW_FRR - lW_FRR;
    ex splineW_FRR =   dW_FRR + sW_FRR * ( cW_FRR + sW_FRR * (bW_FRR + sW_FRR * aW_FRR ) );
    Vector3D fW_FRR = *sys.new_Vector3D("fW_FRR",-splineW_FRR*sin(thetaW_FRR),uW_FRR,splineW_FRR*cos(thetaW_FRR),"B_FWHSR_a");
    Vector3D rW_FRR = sys.Position_Vector("O","O_WFRR")+fW_FRR;
    Vector3D t1W_FRR= sys.diff ( rW_FRR , thetaW_FRR);
    Vector3D t2W_FRR= sys.diff ( rW_FRR , uW_FRR);
    Vector3D nW_FRR = t1W_FRR^t2W_FRR;



    symbol_numeric uR_FRR = *sys.new_AuxCoordinate("uR_FRR","duR_FRR","dduR_FRR", 0.0 ,0.0,0.0);
    symbol_numeric xR_FRR = *sys.new_AuxCoordinate("xR_FRR","dxR_FRR","ddxR_FRR", 3.65904,0.0,0.0);

    symbol_numeric aR_FRR = *sys.new_Parameter("aR_FRR",0.0);//spline's coefficients right wheel
    symbol_numeric bR_FRR = *sys.new_Parameter("bR_FRR",-20.0);
    symbol_numeric cR_FRR = *sys.new_Parameter("cR_FRR",0.0);
    symbol_numeric dR_FRR = *sys.new_Parameter("dR_FRR",0.1);
    symbol_numeric lR_FRR = *sys.new_Parameter("lR_FRR",0.0); //size of the spline 

    ex sR_FRR = uR_FRR - lR_FRR;
    ex splineR_FRR =   dR_FRR + sR_FRR * ( cR_FRR + sR_FRR * (bR_FRR + sR_FRR * aR_FRR ) );
    Vector3D fR_FRR = *sys.new_Vector3D("fR_FRR",xR_FRR,uR_FRR,splineR_FRR,"B_RAIL");
    Vector3D rR_FRR = sys.Position_Vector("O","O_RailR")+fR_FRR;
    Vector3D t1R_FRR= sys.diff ( rR_FRR , xR_FRR);
    Vector3D t2R_FRR= sys.diff ( rR_FRR , uR_FRR);
    Vector3D nR_FRR = t1R_FRR^t2R_FRR;

    //normal and tangent unitary vectors at contact point
    Vector3D u_nW_FRR =( 1 /sqrt( nW_FRR * nW_FRR )) * nW_FRR;
    Vector3D u_t1W_FRR =( 1 /sqrt( t1W_FRR * t1W_FRR )) * t1W_FRR;
    Vector3D u_t2W_FRR =( 1 /sqrt( t2W_FRR * t2W_FRR )) * t2W_FRR;    
    Vector3D u_nR_FRR =( 1 /sqrt( nR_FRR * nR_FRR )) * nR_FRR;
    Vector3D u_t1R_FRR =( 1 /sqrt( t1R_FRR * t1R_FRR )) * t1R_FRR;
    Vector3D u_t2R_FRR =( 1 /sqrt( t2R_FRR * t2R_FRR )) * t2R_FRR;

    Point * PWcon_FRR   = sys.new_Point("PWcon_FRR","O",&rW_FRR);
    Point * PRcon_FRR   = sys.new_Point("PRcon_FRR","O",&rR_FRR);
    Vector3D VPconRW_FRR= sys.Position_Vector("PRcon_FRR","PWcon_FRR");
    
    Phi(30,0) = u_t1R_FRR * VPconRW_FRR;
    Phi(31,0) = u_t2R_FRR * VPconRW_FRR;
    Phi(32,0) = u_nR_FRR  * VPconRW_FRR;
    Phi(33,0) = u_nR_FRR * t1W_FRR;
    Phi(34,0) = u_nR_FRR * t2W_FRR;

    Point * Pcon_FRR   = sys.new_Point("Pcon_FRR","O",&rW_FRR);

    Vector3D FKALKER_FRR = (Fx_FRR* u_t1R_FRR) + (Fy_FRR * u_t2R_FRR);
    Vector3D MKALKER_FRR = Mz_FRR * u_nR_FRR;

    Wrench3D * FKalker_FRR = sys.new_Wrench3D ( "FKalker_FRR", FKALKER_FRR, MKALKER_FRR , PWcon_FRR, FWHSR , "External") ;

    //~ symbol_numeric lambda31 = *sys.new_Joint_Unknown("lambda31");
    //~ symbol_numeric lambda32 = *sys.new_Joint_Unknown("lambda32");
    //~ symbol_numeric lambda33 = *sys.new_Joint_Unknown("lambda33");
    //~ symbol_numeric lambda34 = *sys.new_Joint_Unknown("lambda34");
    //~ symbol_numeric lambda35 = *sys.new_Joint_Unknown("lambda35");
    
    
cout << " FRL" <<endl; 
    // ************************************************************************************************
    // FRONT BOGIE, REAR SIDE, LEFT WHEEL FRL

    Vector3D OFWHSR_OWFRL   = *sys.new_Vector3D("OFWHSR_OWFRL", 0,L_WHS/2.0,0,"B_FWHSR_a"); 
    Point * O_WFRL  = sys.new_Point("O_WFRL","O_FWHSR",&OFWHSR_OWFRL);

    symbol_numeric thetaW_FRL = *sys.new_AuxCoordinate("thetaW_FRL","dthetaW_FRL","ddthetaW_FRL",0.0,0.0,0.0);
    symbol_numeric uW_FRL = *sys.new_AuxCoordinate("uW_FRL","duW_FRL","dduW_FRL",0.0,0.0,0.0);

    symbol_numeric aW_FRL = *sys.new_Parameter("aW_FRL",0.0);//spline's coefficients
    symbol_numeric bW_FRL = *sys.new_Parameter("bW_FRL",0.0);
    symbol_numeric cW_FRL = *sys.new_Parameter("cW_FRL",0.1);
    symbol_numeric dW_FRL = *sys.new_Parameter("dW_FRL",-0.5);
    symbol_numeric lW_FRL = *sys.new_Parameter("lW_FRL",0.0);//size of the spline
 
    ex sW_FRL = uW_FRL - lW_FRL;
    ex splineW_FRL =   dW_FRL + sW_FRL * ( cW_FRL + sW_FRL * (bW_FRL + sW_FRL * aW_FRL ) );
    Vector3D fW_FRL = *sys.new_Vector3D("fW_FRL",-splineW_FRL*sin(thetaW_FRL),uW_FRL,splineW_FRL*cos(thetaW_FRL),"B_FWHSR_a");
    Vector3D rW_FRL = sys.Position_Vector("O","O_WFRL")+fW_FRL;
    Vector3D t1W_FRL= sys.diff ( rW_FRL , thetaW_FRL);
    Vector3D t2W_FRL= sys.diff ( rW_FRL , uW_FRL);
    Vector3D nW_FRL = t1W_FRL^t2W_FRL;



    symbol_numeric uR_FRL = *sys.new_AuxCoordinate("uR_FRL","duR_FRL","dduR_FRL", 0.0,0.0,0.0);
    symbol_numeric xR_FRL = *sys.new_AuxCoordinate("xR_FRL","dxR_FRL","ddxR_FRL", 3.65904 ,0.0,0.0);

    symbol_numeric aR_FRL = *sys.new_Parameter("aR_FRL",0.0);//spline's coefficients 
    symbol_numeric bR_FRL = *sys.new_Parameter("bR_FRL",-20.0);
    symbol_numeric cR_FRL = *sys.new_Parameter("cR_FRL",0.0);
    symbol_numeric dR_FRL = *sys.new_Parameter("dR_FRL",0.1);
    symbol_numeric lR_FRL = *sys.new_Parameter("lR_FRL",0.0); //size of the spline 

    ex sR_FRL = uR_FRL - lR_FRL;
    ex splineR_FRL =   dR_FRL + sR_FRL * ( cR_FRL + sR_FRL * (bR_FRL + sR_FRL * aR_FRL ) );
    Vector3D fR_FRL = *sys.new_Vector3D("fR_FRL",xR_FRL,uR_FRL,splineR_FRL,"B_RAIL");
    Vector3D rR_FRL = sys.Position_Vector("O","O_RailL")+fR_FRL;
    Vector3D t1R_FRL= sys.diff ( rR_FRL , xR_FRL);
    Vector3D t2R_FRL= sys.diff ( rR_FRL , uR_FRL);
    Vector3D nR_FRL = t1R_FRL^t2R_FRL;

    //normal and tangent unitary vectors at contact point
    Vector3D u_nW_FRL =( 1 /sqrt( nW_FRL * nW_FRL )) * nW_FRL;
    Vector3D u_t1W_FRL =( 1 /sqrt( t1W_FRL * t1W_FRL )) * t1W_FRL;
    Vector3D u_t2W_FRL =( 1 /sqrt( t2W_FRL * t2W_FRL )) * t2W_FRL;    
    Vector3D u_nR_FRL =( 1 /sqrt( nR_FRL * nR_FRL )) * nR_FRL;
    Vector3D u_t1R_FRL =( 1 /sqrt( t1R_FRL * t1R_FRL )) * t1R_FRL;
    Vector3D u_t2R_FRL =( 1 /sqrt( t2R_FRL * t2R_FRL )) * t2R_FRL;

    Point * PWcon_FRL   = sys.new_Point("PWcon_FRL","O",&rW_FRL);
    Point * PRcon_FRL   = sys.new_Point("PRcon_FRL","O",&rR_FRL);
    Vector3D VPconRW_FRL= sys.Position_Vector("PRcon_FRL","PWcon_FRL");
    
    Phi(35,0) = u_t1R_FRL * VPconRW_FRL;
    Phi(36,0) = u_t2R_FRL * VPconRW_FRL;
    Phi(37,0) = u_nR_FRL  * VPconRW_FRL;
    Phi(38,0) = u_nR_FRL * t1W_FRL;
    Phi(39,0) = u_nR_FRL * t2W_FRL;


    Vector3D FKALKER_FRL = (Fx_FRL * u_t1R_FRL) + (Fy_FRL * u_t2R_FRL);
    Vector3D MKALKER_FRL = Mz_FRL * u_nR_FRL;

    Wrench3D * FKalker_FRL = sys.new_Wrench3D ( "FKalker_FRL", FKALKER_FRL, MKALKER_FRL , PWcon_FRL, FWHSR , "External") ;

    //~ symbol_numeric lambda36 = *sys.new_Joint_Unknown("lambda36");
    //~ symbol_numeric lambda37 = *sys.new_Joint_Unknown("lambda37");
    //~ symbol_numeric lambda38 = *sys.new_Joint_Unknown("lambda38");  
    //~ symbol_numeric lambda39 = *sys.new_Joint_Unknown("lambda39");
    //~ symbol_numeric lambda40 = *sys.new_Joint_Unknown("lambda40");

    // ************************************************************************************************

// ************************************************************************************************
// 	Vectors needed to take diferent Jacobians
// ************************************************************************************************

    cout << "Vectors needed to take diferent Jacobians" << endl;

    Matrix q = sys.Coordinates();
    Matrix dq = sys.Velocities();
    Matrix ddq = sys.Accelerations();
    Matrix qaux = sys.Aux_Coordinates();   
    Matrix dqaux = sys.Aux_Velocities();
    Matrix epsilon = sys.Joint_Unknowns();
    Matrix pars = sys.Parameters();
    Matrix inps = sys.Inputs();
    Matrix unks = sys.Joint_Unknowns();



// ************************************************************************************************
// 	New Phi c and t
// ************************************************************************************************

    cout << "Phic and Phit" << endl;
    
    Matrix Phic (8,1);

    Phic(0,0) = Phi(2,0);
    Phic(1,0) = Phi(7,0);
    Phic(2,0) = Phi(12,0);
    Phic(3,0) = Phi(17,0);
    Phic(4,0) = Phi(22,0);
    Phic(5,0) = Phi(27,0);
    Phic(6,0) = Phi(32,0);
    Phic(7,0) = Phi(37,0);
    
    symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");
    symbol_numeric lambda2  = *sys.new_Joint_Unknown("lambda2");
    symbol_numeric lambda3  = *sys.new_Joint_Unknown("lambda3");
    symbol_numeric lambda4  = *sys.new_Joint_Unknown("lambda4");
    symbol_numeric lambda5  = *sys.new_Joint_Unknown("lambda5"); 
    symbol_numeric lambda6  = *sys.new_Joint_Unknown("lambda6");
    symbol_numeric lambda7  = *sys.new_Joint_Unknown("lambda7");
    symbol_numeric lambda8  = *sys.new_Joint_Unknown("lambda8"); 
       
    Matrix Phit (32,1);
    Phit(0,0) =  Phi(0,0);
    Phit(1,0) =  Phi(1,0);    
    Phit(2,0) =  Phi(3,0);    
    Phit(3,0) =  Phi(4,0);    
    Phit(4,0) =  Phi(5,0);   
    Phit(5,0) =  Phi(6,0);   
    Phit(6,0) =  Phi(8,0);
    Phit(7,0) =  Phi(9,0);
    Phit(8,0) =  Phi(10,0);   
    Phit(9,0) =  Phi(11,0);   
    Phit(10,0) = Phi(13,0);   
    Phit(11,0) = Phi(14,0);   
    Phit(12,0) = Phi(15,0); 
    Phit(13,0) = Phi(16,0);  
    Phit(14,0) = Phi(18,0);      
    Phit(15,0) = Phi(19,0);     
    Phit(16,0) = Phi(20,0);   
    Phit(17,0) = Phi(21,0);  
    Phit(18,0) = Phi(23,0);      
    Phit(19,0) = Phi(24,0);      
    Phit(20,0) = Phi(25,0);       
    Phit(21,0) = Phi(26,0);      
    Phit(22,0) = Phi(28,0);     
    Phit(23,0) = Phi(29,0);      
    Phit(24,0) = Phi(30,0);      
    Phit(25,0) = Phi(31,0);     
    Phit(26,0) = Phi(33,0);  
    Phit(27,0) = Phi(34,0);  
    Phit(28,0) = Phi(35,0);      
    Phit(29,0) = Phi(36,0);      
    Phit(30,0) = Phi(38,0);       
    Phit(31,0) = Phi(39,0);      

    Matrix dPhic = sys.Dt(Phic);
    Matrix dPhit = sys.Dt(Phit);    

    Matrix ddPhic = sys.Dt(dPhic);

    Matrix Betac  = -dPhic;

    vector < symbol_numeric * > Velocities = sys.get_Velocities();
    vector < symbol_numeric * > Aux_Velocities = sys.get_AuxVelocities();
    for (int i=0; (i < dPhic.rows()); ++i) {
        Betac(i,0) = recursive_substitution (Betac(i,0),Velocities , 0);
        Betac(i,0) = recursive_substitution (Betac(i,0),Aux_Velocities , 0);
    }	
 
    Matrix Gammac  = -ddPhic;

    vector < symbol_numeric * > Accelerations      = sys.get_Accelerations();
    vector < symbol_numeric * > Aux_Accelerations  = sys.get_AuxAccelerations();
    for (int i=0; (i < Gammac.rows()); ++i) {
        Gammac(i,0) = recursive_substitution (Gammac(i,0),Accelerations , 0);
        Gammac(i,0) = recursive_substitution (Gammac(i,0),Aux_Accelerations , 0);
    }
 
 
    
    Matrix dPhic_dq =  sys.jacobian(dPhic.transpose() ,dq);
    Matrix dPhit_ds =  sys.jacobian(dPhit.transpose() ,dqaux);
    
    lst new_atom_list_Phic, new_exp_list_Phic;
    matrix_list_optimize (Phic, new_atom_list_Phic,new_exp_list_Phic);
    sys.export_Matrix_C	("Phic","_Phic",Phic, new_atom_list_Phic, new_exp_list_Phic ,ORDER);
    sys.export_function_MATLAB("Phic", "Phic_",Phic, new_atom_list_Phic, new_exp_list_Phic,"q,qaux,time,param"); 

    lst new_atom_list_Phit, new_exp_list_Phit;
    matrix_list_optimize (Phit, new_atom_list_Phit,new_exp_list_Phit);
    sys.export_Matrix_C	("Phit","_Phit",Phit, new_atom_list_Phit, new_exp_list_Phit ,ORDER);
    sys.export_function_MATLAB("Phit", "Phit_",Phit, new_atom_list_Phit, new_exp_list_Phit,"q,qaux,time,param"); 

    lst new_atom_list_Betac, new_exp_list_Betac;
    matrix_list_optimize (Betac, new_atom_list_Betac,new_exp_list_Betac);
    sys.export_Matrix_C	("Betac","_Betac",Betac, new_atom_list_Betac, new_exp_list_Betac ,ORDER);
    sys.export_function_MATLAB("Betac", "Betac_",Betac, new_atom_list_Betac, new_exp_list_Betac,"q,qaux,time,param"); 
 
    lst new_atom_list_Gammac, new_exp_list_Gammac;
    matrix_list_optimize (Gammac, new_atom_list_Gammac,new_exp_list_Gammac);
    sys.export_Matrix_C	("Gammac","_Gammac",Gammac, new_atom_list_Gammac, new_exp_list_Gammac ,ORDER);
    sys.export_function_MATLAB("Gammac", "Gammac_",Gammac, new_atom_list_Gammac, new_exp_list_Gammac,"q,qaux,dq,dqaux,time,param"); 

    lst new_atom_list_dPhic_dq, new_exp_list_dPhic_dq;
    matrix_list_optimize (dPhic_dq, new_atom_list_dPhic_dq,new_exp_list_dPhic_dq);
    sys.export_Matrix_C	("dPhic_dq","_dPhic_dq",dPhic_dq, new_atom_list_dPhic_dq, new_exp_list_dPhic_dq ,ORDER);
    sys.export_function_MATLAB("dPhic_dq", "dPhic_dq_",dPhic_dq, new_atom_list_dPhic_dq, new_exp_list_dPhic_dq,"q,qaux,time,param"); 

    lst new_atom_list_dPhit_ds, new_exp_list_dPhit_ds;
    matrix_list_optimize (dPhit_ds, new_atom_list_dPhit_ds,new_exp_list_dPhit_ds);
    sys.export_Matrix_C	("dPhit_ds","_dPhit_ds",dPhit_ds, new_atom_list_dPhit_ds, new_exp_list_dPhit_ds ,ORDER);
    sys.export_function_MATLAB("dPhit_ds", "dPhit_ds_",dPhit_ds, new_atom_list_dPhit_ds, new_exp_list_dPhit_ds,"q,qaux,time,param"); 
    
    
    
// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************

    cout << "Dynamic Equations" << endl;

    //Matrix Dynamic_Equations = sys.GenForceSys("ALL");
    //Matrix Dynamic_Equations(0,0);

// ************************************************************************************************
// 	Output Vector
// ************************************************************************************************

    cout << "Output Vector" << endl;


    Matrix Output(80,1);

    //REAR BOGIE, FRONT SIDE, RIGHT WHEEL RFR
    Vector3D eRFR = *sys.new_Vector3D("eRFR",0,1,0,"B_RWHSF");
    ex rho_RFR = abs(sqrt(fW_RFR(0,0)*fW_RFR(0,0) + fW_RFR(2,0)*fW_RFR(2,0)));
    ex cryW_RFR = rho_RFR * sqrt(1-(u_nR_RFR*eRFR)*(u_nR_RFR*eRFR)) ;
    ex crxW_RFR = abs(pow(1 + pow(sys.diff(splineW_RFR,uW_RFR),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineW_RFR,uW_RFR),uW_RFR));  /* Radius of Curvature rho = (1+y')^(3/2) / y'' */
    ex cryR_RFR = 6e+6;
    ex crxR_RFR = abs(pow(1 + pow(sys.diff(splineR_RFR,uR_RFR),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineR_RFR,uR_RFR),uR_RFR));


    Vector3D VJW_RFR = sys.Velocity_Vector ("abs", "PWcon_RFR", "RWHSF");
    Vector3D VCW_RFR = sys.Velocity_Vector ("abs", "O_WRFR", "RWHSF");   
    Vector3D OM_RWHSF = sys.Angular_Velocity("xyz","B_RWHSF");

    Output(0,0) = sqrt(lambda1*lambda1);
    Output(1,0) = VJW_RFR * u_t1R_RFR;
    Output(2,0) = VJW_RFR * u_t2R_RFR;
    Output(3,0) = OM_RWHSF * u_nR_RFR;
    Output(4,0) = *dbRWHSF;
    Output(5,0) = numeric(1,2)*(VCW_RFR.get_module() + (OM_RWHSF ^ fW_RFR).get_module());
    Output(6,0) = cryW_RFR;
    //Output(7,0) = crxW_RFR;
    Output(7,0) = 1e4; 
    Output(8,0) = cryR_RFR;
    Output(9,0) = crxR_RFR;


    //REAR BOGIE, FRONT SIDE, LEFT WHEEL RFL
    Vector3D eRFL = *sys.new_Vector3D("eRFL",0,1,0,"B_RWHSF");
    ex rho_RFL = abs(sqrt(fW_RFL(0,0)*fW_RFL(0,0) + fW_RFL(2,0)*fW_RFL(2,0)));
    ex cryW_RFL = rho_RFL / sqrt(1-(u_nR_RFL*eRFL)*(u_nR_RFL*eRFL)) ;
    ex crxW_RFL = abs(pow(1 + pow(sys.diff(splineW_RFL,uW_RFL),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineW_RFL,uW_RFL),uW_RFL));  /* Radius of Curvature rho = (1+y')^(3/2) / y'' */
    ex cryR_RFL = 6e+6;
    ex crxR_RFL = abs(pow(1 + pow(sys.diff(splineR_RFL,uR_RFL),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineR_RFL,uR_RFL),uR_RFL));
    
    Vector3D VJW_RFL = sys.Velocity_Vector ("abs", "PWcon_RFL", "RWHSF");
    Vector3D VCW_RFL = sys.Velocity_Vector ("abs", "O_WRFL", "RWHSF");   
    //Vector3D OM_RWHSF = sys.Angular_Velocity("xyz","B_RWHSF");

    Output(10,0) = sqrt(lambda2*lambda2);
    Output(11,0) = VJW_RFL * u_t1R_RFL;    
    Output(12,0) = VJW_RFL * u_t2R_RFL;
    Output(13,0) = OM_RWHSF * u_nR_RFL;
    Output(14,0) = *dbRWHSF;
    Output(15,0) = numeric(1,2)*(VCW_RFL.get_module() + (OM_RWHSF ^ fW_RFL).get_module()); 
    Output(16,0) = cryW_RFL;
    //Output(17,0) = crxW_RFL;
    Output(17,0) = 1e4;
    Output(18,0) = cryR_RFL;
    Output(19,0) = crxR_RFL;

    //REAR BOGIE, REAR SIDE, RIGHT WHEEL RRR
    Vector3D eRRR = *sys.new_Vector3D("eRRR",0,1,0,"B_RWHSR");
    ex rho_RRR = abs(sqrt(fW_RRR(0,0)*fW_RRR(0,0) + fW_RRR(2,0)*fW_RRR(2,0)));
    ex cryW_RRR = rho_RRR / sqrt(1-(u_nR_RRR*eRRR)*(u_nR_RRR*eRRR)) ;    
    ex crxW_RRR = abs(pow(1 + pow(sys.diff(splineW_RRR,uW_RRR),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineW_RRR,uW_RRR),uW_RRR));  /* Radius of Curvature rho = (1+y')^(3/2) / y'' */
    ex cryR_RRR = 6e+6;
    ex crxR_RRR = abs(pow(1 + pow(sys.diff(splineR_RRR,uR_RRR),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineR_RRR,uR_RRR),uR_RRR));

    Vector3D VJW_RRR = sys.Velocity_Vector ("abs", "PWcon_RRR", "RWHSR");
    Vector3D VCW_RRR = sys.Velocity_Vector ("abs", "O_WRRR", "RWHSR");   
    Vector3D OM_RWHSR = sys.Angular_Velocity("xyz","B_RWHSR");   
    
    
    Output(20,0) = sqrt(lambda3*lambda3);
    Output(21,0) = VJW_RRR * u_t1R_RRR; 
    Output(22,0) = VJW_RRR * u_t2R_RRR;
    Output(23,0) = OM_RWHSR * u_nR_RRR;
    Output(24,0) = *dbRWHSR;
    Output(25,0) = numeric(1,2)*(VCW_RRR.get_module() + (OM_RWHSR ^ fW_RRR).get_module()); 
    Output(26,0) = cryW_RRR;
    //Output(27,0) = crxW_RRR;
    Output(27,0) = 1e4;
    Output(28,0) = cryR_RRR;
    Output(29,0) = crxR_RRR;



    //REAR BOGIE, REAR SIDE, LEFT WHEEL RRL
    Vector3D eRRL = *sys.new_Vector3D("eRRL",0,1,0,"B_RWHSR");
    ex rho_RRL = abs(sqrt(fW_RRL(0,0)*fW_RRL(0,0) + fW_RRL(2,0)*fW_RRL(2,0)));
    ex cryW_RRL = rho_RRL / sqrt(1-(u_nR_RRL*eRRL)*(u_nR_RRL*eRRL)) ;      
    ex crxW_RRL = abs(pow(1 + pow(sys.diff(splineW_RRL,uW_RRL),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineW_RRL,uW_RRL),uW_RRL));  /* Radius of Curvature rho = (1+y')^(3/2) / y'' */
    ex cryR_RRL = 6e+6;
    ex crxR_RRL = abs(pow(1 + pow(sys.diff(splineR_RRL,uR_RRL),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineR_RRL,uR_RRL),uR_RRL));
    
    Vector3D VJW_RRL = sys.Velocity_Vector ("abs", "PWcon_RRL", "RWHSR");
    Vector3D VCW_RRL = sys.Velocity_Vector ("abs", "O_WRRL", "RWHSR");   
    //Vector3D OM_RWHSR = sys.Angular_Velocity("xyz","B_RWHSR");  
    
    Output(30,0) = sqrt(lambda4*lambda4);
    Output(31,0) = VJW_RRL * u_t1R_RRL; 
    Output(32,0) = VJW_RRL * u_t2R_RRL;
    Output(33,0) = OM_RWHSR * u_nR_RRL;
    Output(34,0) = *dbRWHSR;
    Output(35,0) = numeric(1,2)*(VCW_RRL.get_module() + (OM_RWHSR ^ fW_RRL).get_module()); 
    Output(36,0) = cryW_RRL;
    //Output(37,0) = crxW_RRL;
    Output(37,0) = 1e4;
    Output(38,0) = cryR_RRL;
    Output(39,0) = crxR_RRL;

    //FRONT BOGIE, FRONT SIDE, RIGHT WHEEL FFR
    Vector3D eFFR = *sys.new_Vector3D("eFFR",0,1,0,"B_FWHSF");
    ex rho_FFR = abs(sqrt(fW_FFR(0,0)*fW_FFR(0,0) + fW_FFR(2,0)*fW_FFR(2,0)));
    ex cryW_FFR = rho_FFR / sqrt(1-(u_nR_FFR*eFFR)*(u_nR_FFR*eFFR)) ;     
    ex crxW_FFR = abs(pow(1 + pow(sys.diff(splineW_FFR,uW_FFR),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineW_FFR,uW_FFR),uW_FFR));  /* Radius of Curvature rho = (1+y')^(3/2) / y'' */
    ex cryR_FFR = 6e+6;
    ex crxR_FFR = abs(pow(1 + pow(sys.diff(splineR_FFR,uR_FFR),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineR_FFR,uR_FFR),uR_FFR));

    Vector3D VJW_FFR = sys.Velocity_Vector ("abs", "PWcon_FFR", "FWHSF");
    Vector3D VCW_FFR = sys.Velocity_Vector ("abs", "O_WFFR", "FWHSF");   
    Vector3D OM_FWHSF = sys.Angular_Velocity("xyz","B_FWHSF");

    Output(40,0) = sqrt(lambda5*lambda5);
    Output(41,0) = VJW_FFR * u_t1R_FFR; 
    Output(42,0) = VJW_FFR * u_t2R_FFR;
    Output(43,0) = OM_FWHSF * u_nR_FFR;
    Output(44,0) = *dbFWHSF;
    Output(45,0) = numeric(1,2)*(VCW_FFR.get_module() + (OM_FWHSF ^ fW_FFR).get_module());
    Output(46,0) = cryW_FFR;
    //Output(47,0) = crxW_FFR;
    Output(47,0) = 1e4;
    Output(48,0) = cryR_FFR;
    Output(49,0) = crxR_FFR;



    //FRONT BOGIE, FRONT SIDE, LEFT WHEEL FFL
    Vector3D eFFL = *sys.new_Vector3D("eFFL",0,1,0,"B_FWHSF");
    ex rho_FFL = abs(sqrt(fW_FFL(0,0)*fW_FFL(0,0) + fW_FFL(2,0)*fW_FFL(2,0)));
    ex cryW_FFL = rho_FFL / sqrt(1-(u_nR_FFL*eFFL)*(u_nR_FFL*eFFL)) ; 
    ex crxW_FFL = abs(pow(1 + pow(sys.diff(splineW_FFL,uW_FFL),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineW_FFL,uW_FFL),uW_FFL));  /* Radius of Curvature rho = (1+y')^(3/2) / y'' */
    ex cryR_FFL = 6e+6;
    ex crxR_FFL = abs(pow(1 + pow(sys.diff(splineR_FFL,uR_FFL),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineR_FFL,uR_FFL),uR_FFL));

    Vector3D VJW_FFL = sys.Velocity_Vector ("abs", "PWcon_FFL", "FWHSF");
    Vector3D VCW_FFL = sys.Velocity_Vector ("abs", "O_WFFL", "FWHSF");   
    //Vector3D OM_FWHSF = sys.Angular_Velocity("xyz","B_FWHSF");


    Output(50,0) = sqrt(lambda6*lambda6);
    Output(51,0) = VJW_FFL * u_t1R_FFL;  
    Output(52,0) = VJW_FFL * u_t2R_FFL;
    Output(53,0) = OM_FWHSF * u_nR_FFL;
    Output(54,0) = *dbFWHSF;
    Output(55,0) = numeric(1,2)*(VCW_FFL.get_module() + (OM_FWHSF ^ fW_FFL).get_module());  
    Output(56,0) = cryW_FFL;
    //Output(57,0) = crxW_FFL;
    Output(57,0) = 1e4;
    Output(58,0) = cryR_FFL;
    Output(59,0) = crxR_FFL;


    //FRONT BOGIE, REAR SIDE, RIGHT WHEEL FRR
    Vector3D eFRR = *sys.new_Vector3D("eFRR",0,1,0,"B_FWHSR");
    ex rho_FRR = abs(sqrt(fW_FRR(0,0)*fW_FRR(0,0) + fW_FRR(2,0)*fW_FRR(2,0)));
    ex cryW_FRR = rho_FRR / sqrt(1-(u_nR_FRR*eFRR)*(u_nR_FRR*eFRR)) ;     
    ex crxW_FRR = abs(pow(1 + pow(sys.diff(splineW_FRR,uW_FRR),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineW_FRR,uW_FRR),uW_FRR));  /* Radius of Curvature rho = (1+y')^(3/2) / y'' */
    ex cryR_FRR = 6e+6;
    ex crxR_FRR = abs(pow(1 + pow(sys.diff(splineR_FRR,uR_FRR),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineR_FRR,uR_FRR),uR_FRR));
    
    Vector3D VJW_FRR = sys.Velocity_Vector ("abs", "PWcon_FRR", "FWHSR");
    Vector3D VCW_FRR = sys.Velocity_Vector ("abs", "O_WFRR", "FWHSR");   
    Vector3D OM_FWHSR = sys.Angular_Velocity("xyz","B_FWHSR");
    
    Output(60,0) = sqrt(lambda7*lambda7);
    Output(61,0) = VJW_FRR * u_t1R_FRR; 
    Output(62,0) = VJW_FRR * u_t2R_FRR;
    Output(63,0) = OM_FWHSR * u_nR_FRR;
    Output(64,0) = *dbFWHSR;
    Output(65,0) = numeric(1,2)*(VCW_FRR.get_module() + (OM_FWHSR ^ fW_FRR).get_module());  
    Output(66,0) = cryW_FRR;
    //Output(67,0) = crxW_FRR;
    Output(67,0) = 1e4;    
    Output(68,0) = cryR_FRR;
    Output(69,0) = crxR_FRR;



    //FRONT BOGIE, REAR SIDE, LEFT WHEEL FRL
    Vector3D eFRL = *sys.new_Vector3D("eFRL",0,1,0,"B_FWHSR");
    ex rho_FRL = abs(sqrt(fW_FRL(0,0)*fW_FRL(0,0) + fW_FRL(2,0)*fW_FRL(2,0)));
    ex cryW_FRL = rho_FRL / sqrt(1-(u_nR_FRL*eFRL)*(u_nR_FRL*eFRL)) ;  
    ex crxW_FRL = abs(pow(1 + pow(sys.diff(splineW_FRL,uW_FRL),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineW_FRL,uW_FRL),uW_FRL));  /* Radius of Curvature rho = (1+y')^(3/2) / y'' */
    ex cryR_FRL = 6e+6;
    ex crxR_FRL = abs(pow(1 + pow(sys.diff(splineR_FRL,uR_FRL),2.0),(3.0/2.0))) / abs(sys.diff(sys.diff(splineR_FRL,uR_FRL),uR_FRL));

    Vector3D VJW_FRL = sys.Velocity_Vector ("abs", "PWcon_FRL", "FWHSR");
    Vector3D VCW_FRL = sys.Velocity_Vector ("abs", "O_WFRL", "FWHSR");   
    //Vector3D OM_FWHSR = sys.Angular_Velocity("xyz","B_FWHSR");

    Output(70,0) = sqrt(lambda8*lambda8);
    Output(71,0) = VJW_FRL * u_t1R_FRL;
    Output(72,0) = VJW_FRL * u_t2R_FRL;
    Output(73,0) = OM_FWHSR * u_nR_FRL;
    Output(74,0) = *dbFWHSR;
    Output(75,0) = numeric(1,2)*(VCW_FRL.get_module() + (OM_FWHSR ^ fW_FRL).get_module());  
    Output(76,0) = cryW_FRL;
    //Output(77,0) = crxW_FRL;
    Output(77,0) = 1e4;    
    Output(78,0) = cryR_FRL;
    Output(79,0) = crxR_RRL;

    sys.new_Matrix("Output",Output);

// ************************************************************************************************
// 	Matrix Calculation 	
// ************************************************************************************************
    cout << "Matrix Calculation" << endl;
    sys.Matrix_Calculation(coord_indep_init , vel_indep_init , sys, METHOD);
    //~ sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD);

// ************************************************************************************************
// 	KALKER
// ************************************************************************************************
    // KALKER
    
    Matrix Delta   = *sys.get_Matrix( "Q" );
    
    symbol_numeric E_elastic = *sys.new_Parameter("E_elastic",210.0e+9);       // MPa
    symbol_numeric nu_poisson = *sys.new_Parameter("nu_poisson",0.27);       // Steel
    symbol_numeric G_elastic = *sys.new_Parameter("G_elastic",1.4384e+11);   // G = E/(2*(1-nu)); % MPa
    
    
    //RFR ************************************************************************************************************
    cout << "Kalker RFR"<<endl;
    symbol_numeric aRFR = *sys.new_Parameter("aRFR",0.0);
    symbol_numeric bRFR = *sys.new_Parameter("bRFR",0.0);
    
    symbol_numeric C11RFR = *sys.new_Parameter("C11RFR",0.0);
    symbol_numeric C22RFR = *sys.new_Parameter("C22RFR",0.0);
    symbol_numeric C23RFR = *sys.new_Parameter("C23RFR",0.0);
    symbol_numeric C33RFR = *sys.new_Parameter("C33RFR",0.0);
    
    Matrix D_RFR(3,3);
    ex GabRFR = G_elastic*aRFR*bRFR;
    D_RFR(0,0) = GabRFR * C11RFR; D_RFR(0,1) = 0;                                D_RFR(0,2) = 0;
    D_RFR(1,0) = 0;               D_RFR(1,1) = GabRFR * C22RFR;                  D_RFR(1,2) = GabRFR * sqrt(aRFR*bRFR)*C23RFR;
    D_RFR(2,0) = 0;               D_RFR(2,1) =-GabRFR * sqrt(aRFR*bRFR)*C23RFR;  D_RFR(2,2) = GabRFR * aRFR*bRFR*C33RFR;
    
    Matrix SlipRFR (3,1);
    SlipRFR (0,0) = VJW_RFR * u_t1R_RFR;
    SlipRFR (1,0) = VJW_RFR * u_t2R_RFR;
    SlipRFR (2,0) = OM_RWHSF * u_nR_RFR; 
    
    lst kalker_forcesRFR;
    kalker_forcesRFR = Fx_RFR,Fy_RFR,Mz_RFR;
    Matrix Mat_KakerForcesRFR = Matrix(kalker_forcesRFR.nops(),1,kalker_forcesRFR);
    Matrix dQ_dKFRFR = sys.jacobian(Delta.transpose(),Mat_KakerForcesRFR);
    
    Matrix CKRFR = dQ_dKFRFR * D_RFR * sys.jacobian(SlipRFR.transpose(),dq);
             
    lst new_atom_list_CKRFR, new_exp_list_CKRFR;
    matrix_list_optimize (CKRFR, new_atom_list_CKRFR, new_exp_list_CKRFR);
    sys.export_Matrix_C	("CKRFR","_CKRFR",CKRFR, new_atom_list_CKRFR, new_exp_list_CKRFR ,ORDER);
    sys.export_function_MATLAB("CKRFR", "CKRFR_",CKRFR, new_atom_list_CKRFR, new_exp_list_CKRFR,"q,qaux,dq,time,param");   


    //RFL ************************************************************************************************************
    cout << "Kalker RFL"<<endl;
    symbol_numeric aRFL = *sys.new_Parameter("aRFL",0.0);
    symbol_numeric bRFL = *sys.new_Parameter("bRFL",0.0);
    
    symbol_numeric C11RFL = *sys.new_Parameter("C11RFL",0.0);
    symbol_numeric C22RFL = *sys.new_Parameter("C22RFL",0.0);
    symbol_numeric C23RFL = *sys.new_Parameter("C23RFL",0.0);
    symbol_numeric C33RFL = *sys.new_Parameter("C33RFL",0.0);
    
    Matrix D_RFL(3,3);
    ex GabRFL = G_elastic*aRFL*bRFL;
    D_RFL(0,0) = GabRFL * C11RFL; D_RFL(0,1) = 0;                                D_RFL(0,2) = 0;
    D_RFL(1,0) = 0;               D_RFL(1,1) = GabRFL * C22RFL;                  D_RFL(1,2) = GabRFL * sqrt(aRFL*bRFL)*C23RFL;
    D_RFL(2,0) = 0;               D_RFL(2,1) =-GabRFL * sqrt(aRFL*bRFL)*C23RFL;  D_RFL(2,2) = GabRFL * aRFL*bRFL*C33RFL;
    
    Matrix SlipRFL (3,1);
    SlipRFL (0,0) = VJW_RFL * u_t1R_RFL;
    SlipRFL (1,0) = VJW_RFL * u_t2R_RFL;
    SlipRFL (2,0) = OM_RWHSF * u_nR_RFL; 
    
    lst kalker_forcesRFL;
    kalker_forcesRFL =Fx_RFL,Fy_RFL,Mz_RFL;
    Matrix Mat_KakerForcesRFL = Matrix(kalker_forcesRFL.nops(),1,kalker_forcesRFL);
    Matrix dQ_dKFRFL = sys.jacobian(Delta.transpose(),Mat_KakerForcesRFL);
    
    Matrix CKRFL = dQ_dKFRFL * D_RFL*sys.jacobian(SlipRFL.transpose(),dq);
             
    lst new_atom_list_CKRFL, new_exp_list_CKRFL;
    matrix_list_optimize (CKRFL, new_atom_list_CKRFL, new_exp_list_CKRFL);
    sys.export_Matrix_C	("CKRFL","_CKRFL",CKRFL, new_atom_list_CKRFL, new_exp_list_CKRFL ,ORDER);
    sys.export_function_MATLAB("CKRFL", "CKRFL_",CKRFL, new_atom_list_CKRFL, new_exp_list_CKRFL,"q,qaux,dq,time,param"); 


    //RRR ************************************************************************************************************
    cout << "Kalker RRR"<<endl;
    symbol_numeric aRRR = *sys.new_Parameter("aRRR",0.0);
    symbol_numeric bRRR = *sys.new_Parameter("bRRR",0.0);
    
    symbol_numeric C11RRR = *sys.new_Parameter("C11RRR",0.0);
    symbol_numeric C22RRR = *sys.new_Parameter("C22RRR",0.0);
    symbol_numeric C23RRR = *sys.new_Parameter("C23RRR",0.0);
    symbol_numeric C33RRR = *sys.new_Parameter("C33RRR",0.0);
    
    Matrix D_RRR(3,3);
    ex GabRRR = G_elastic*aRRR*bRRR;
    D_RRR(0,0) = GabRRR * C11RRR; D_RRR(0,1) = 0;                                D_RRR(0,2) = 0;
    D_RRR(1,0) = 0;               D_RRR(1,1) = GabRRR * C22RRR;                  D_RRR(1,2) = GabRRR * sqrt(aRRR*bRRR)*C23RRR;
    D_RRR(2,0) = 0;               D_RRR(2,1) =-GabRRR * sqrt(aRRR*bRRR)*C23RRR;  D_RRR(2,2) = GabRRR * aRRR*bRRR*C33RRR;
    
    Matrix SlipRRR (3,1);
    SlipRRR (0,0) = VJW_RRR * u_t1R_RRR;
    SlipRRR (1,0) = VJW_RRR * u_t2R_RRR;
    SlipRRR (2,0) = OM_RWHSR * u_nR_RRR; 
    
    lst kalker_forcesRRR;
    kalker_forcesRRR =Fx_RRR,Fy_RRR,Mz_RRR;
    Matrix Mat_KakerForcesRRR = Matrix(kalker_forcesRRR.nops(),1,kalker_forcesRRR);
    Matrix dQ_dKFRRR = sys.jacobian(Delta.transpose(),Mat_KakerForcesRRR);
    
    Matrix CKRRR = dQ_dKFRRR * D_RRR*sys.jacobian(SlipRRR.transpose(),dq);
             
    lst new_atom_list_CKRRR, new_exp_list_CKRRR;
    matrix_list_optimize (CKRRR, new_atom_list_CKRRR, new_exp_list_CKRRR);
    sys.export_Matrix_C	("CKRRR","_CKRRR",CKRRR, new_atom_list_CKRRR, new_exp_list_CKRRR ,ORDER);
    sys.export_function_MATLAB("CKRRR", "CKRRR_",CKRRR, new_atom_list_CKRRR, new_exp_list_CKRRR,"q,qaux,dq,time,param"); 



    //RRL ************************************************************************************************************
    cout << "Kalker RRL"<<endl;
    symbol_numeric aRRL = *sys.new_Parameter("aRRL",0.0);
    symbol_numeric bRRL = *sys.new_Parameter("bRRL",0.0);
    
    symbol_numeric C11RRL = *sys.new_Parameter("C11RRL",0.0);
    symbol_numeric C22RRL = *sys.new_Parameter("C22RRL",0.0);
    symbol_numeric C23RRL = *sys.new_Parameter("C23RRL",0.0);
    symbol_numeric C33RRL = *sys.new_Parameter("C33RRL",0.0);
    
    Matrix D_RRL(3,3);
    ex GabRRL = G_elastic*aRRL*bRRL;
    D_RRL(0,0) = GabRRL * C11RRL; D_RRL(0,1) = 0;                                D_RRL(0,2) = 0;
    D_RRL(1,0) = 0;               D_RRL(1,1) = GabRRL * C22RRL;                  D_RRL(1,2) = GabRRL * sqrt(aRRL*bRRL)*C23RRL;
    D_RRL(2,0) = 0;               D_RRL(2,1) =-GabRRL * sqrt(aRRL*bRRL)*C23RRL;  D_RRL(2,2) = GabRRL * aRRL*bRRL*C33RRL;
    
    Matrix SlipRRL (3,1);
    SlipRRL (0,0) = VJW_RRL * u_t1R_RRL;
    SlipRRL (1,0) = VJW_RRL * u_t2R_RRL;
    SlipRRL (2,0) = OM_RWHSR * u_nR_RRL; 
    
    lst kalker_forcesRRL;
    kalker_forcesRRL =Fx_RRL,Fy_RRL,Mz_RRL;
    Matrix Mat_KakerForcesRRL = Matrix(kalker_forcesRRL.nops(),1,kalker_forcesRRL);
    Matrix dQ_dKFRRL = sys.jacobian(Delta.transpose(),Mat_KakerForcesRRL);
    
    Matrix CKRRL = dQ_dKFRRL * D_RRL*sys.jacobian(SlipRRL.transpose(),dq);
             
    lst new_atom_list_CKRRL, new_exp_list_CKRRL;
    matrix_list_optimize (CKRRL, new_atom_list_CKRRL, new_exp_list_CKRRL);
    sys.export_Matrix_C	("CKRRL","_CKRRL",CKRRL, new_atom_list_CKRRL, new_exp_list_CKRRL ,ORDER);
    sys.export_function_MATLAB("CKRRL", "CKRRL_",CKRRL, new_atom_list_CKRRL, new_exp_list_CKRRL,"q,qaux,dq,time,param");     
    
    
    
    //FFR ************************************************************************************************************
    cout << "Kalker FFR"<<endl;
    symbol_numeric aFFR = *sys.new_Parameter("aFFR",0.0);
    symbol_numeric bFFR = *sys.new_Parameter("bFFR",0.0);
    
    symbol_numeric C11FFR = *sys.new_Parameter("C11FFR",0.0);
    symbol_numeric C22FFR = *sys.new_Parameter("C22FFR",0.0);
    symbol_numeric C23FFR = *sys.new_Parameter("C23FFR",0.0);
    symbol_numeric C33FFR = *sys.new_Parameter("C33FFR",0.0);
    
    Matrix D_FFR(3,3);
    ex GabFFR = G_elastic*aFFR*bFFR;
    D_FFR(0,0) = GabFFR * C11FFR; D_FFR(0,1) = 0;                                D_FFR(0,2) = 0;
    D_FFR(1,0) = 0;               D_FFR(1,1) = GabFFR * C22FFR;                  D_FFR(1,2) = GabFFR * sqrt(aFFR*bFFR)*C23FFR;
    D_FFR(2,0) = 0;               D_FFR(2,1) =-GabFFR * sqrt(aFFR*bFFR)*C23FFR;  D_FFR(2,2) = GabFFR * aFFR*bFFR*C33FFR;
    
    Matrix SlipFFR (3,1);
    SlipFFR (0,0) = VJW_FFR * u_t1R_FFR;
    SlipFFR (1,0) = VJW_FFR * u_t2R_FFR;
    SlipFFR (2,0) = OM_FWHSF * u_nR_FFR; 
    
    lst kalker_forcesFFR;
    kalker_forcesFFR =Fx_FFR,Fy_FFR,Mz_FFR;
    Matrix Mat_KakerForcesFFR = Matrix(kalker_forcesFFR.nops(),1,kalker_forcesFFR);
    Matrix dQ_dKFFFR = sys.jacobian(Delta.transpose(),Mat_KakerForcesFFR);
    
    Matrix CKFFR = dQ_dKFFFR * D_FFR*sys.jacobian(SlipFFR.transpose(),dq);
             
    lst new_atom_list_CKFFR, new_exp_list_CKFFR;
    matrix_list_optimize (CKFFR, new_atom_list_CKFFR, new_exp_list_CKFFR);
    sys.export_Matrix_C	("CKFFR","_CKFFR",CKFFR, new_atom_list_CKFFR, new_exp_list_CKFFR ,ORDER);
    sys.export_function_MATLAB("CKFFR", "CKFFR_",CKFFR, new_atom_list_CKFFR, new_exp_list_CKFFR,"q,qaux,dq,time,param");     
    
    
    
    //FFL ************************************************************************************************************
    cout << "Kalker FFL"<<endl;
    symbol_numeric aFFL = *sys.new_Parameter("aFFL",0.0);
    symbol_numeric bFFL = *sys.new_Parameter("bFFL",0.0);
    
    symbol_numeric C11FFL = *sys.new_Parameter("C11FFL",0.0);
    symbol_numeric C22FFL = *sys.new_Parameter("C22FFL",0.0);
    symbol_numeric C23FFL = *sys.new_Parameter("C23FFL",0.0);
    symbol_numeric C33FFL = *sys.new_Parameter("C33FFL",0.0);
    
    Matrix D_FFL(3,3);
    ex GabFFL = G_elastic*aFFL*bFFL;
    D_FFL(0,0) = GabFFL * C11FFL; D_FFL(0,1) = 0;                                D_FFL(0,2) = 0;
    D_FFL(1,0) = 0;               D_FFL(1,1) = GabFFL * C22FFL;                  D_FFL(1,2) = GabFFL * sqrt(aFFL*bFFL)*C23FFL;
    D_FFL(2,0) = 0;               D_FFL(2,1) =-GabFFL * sqrt(aFFL*bFFL)*C23FFL;  D_FFL(2,2) = GabFFL * aFFL*bFFL*C33FFL;
    
    Matrix SlipFFL (3,1);
    SlipFFL (0,0) = VJW_FFL * u_t1R_FFL;
    SlipFFL (1,0) = VJW_FFL * u_t2R_FFL;
    SlipFFL (2,0) = OM_FWHSF * u_nR_FFL; 
    
    lst kalker_forcesFFL;
    kalker_forcesFFL =Fx_FFL,Fy_FFL,Mz_FFL;
    Matrix Mat_KakerForcesFFL = Matrix(kalker_forcesFFL.nops(),1,kalker_forcesFFL);
    Matrix dQ_dKFFFL = sys.jacobian(Delta.transpose(),Mat_KakerForcesFFL);
    
    Matrix CKFFL = dQ_dKFFFL * D_FFL*sys.jacobian(SlipFFL.transpose(),dq);
             
    lst new_atom_list_CKFFL, new_exp_list_CKFFL;
    matrix_list_optimize (CKFFL, new_atom_list_CKFFL, new_exp_list_CKFFL);
    sys.export_Matrix_C	("CKFFL","_CKFFL",CKFFL, new_atom_list_CKFFL, new_exp_list_CKFFL ,ORDER);
    sys.export_function_MATLAB("CKFFL", "CKFFL_",CKFFL, new_atom_list_CKFFL, new_exp_list_CKFFL,"q,qaux,dq,time,param");     
   
    
    
    //FRR ************************************************************************************************************
    cout << "Kalker FRR"<<endl;
    symbol_numeric aFRR = *sys.new_Parameter("aFRR",0.0);
    symbol_numeric bFRR = *sys.new_Parameter("bFRR",0.0);
    
    symbol_numeric C11FRR = *sys.new_Parameter("C11FRR",0.0);
    symbol_numeric C22FRR = *sys.new_Parameter("C22FRR",0.0);
    symbol_numeric C23FRR = *sys.new_Parameter("C23FRR",0.0);
    symbol_numeric C33FRR = *sys.new_Parameter("C33FRR",0.0);
    
    Matrix D_FRR(3,3);
    ex GabFRR = G_elastic*aFRR*bFRR;
    D_FRR(0,0) = GabFRR * C11FRR; D_FRR(0,1) = 0;                                D_FRR(0,2) = 0;
    D_FRR(1,0) = 0;               D_FRR(1,1) = GabFRR * C22FRR;                  D_FRR(1,2) = GabFRR * sqrt(aFRR*bFRR)*C23FRR;
    D_FRR(2,0) = 0;               D_FRR(2,1) =-GabFRR * sqrt(aFRR*bFRR)*C23FRR;  D_FRR(2,2) = GabFRR * aFRR*bFRR*C33FRR;
    
    Matrix SlipFRR (3,1);
    SlipFRR (0,0) = VJW_FRR * u_t1R_FRR;
    SlipFRR (1,0) = VJW_FRR * u_t2R_FRR;
    SlipFRR (2,0) = OM_FWHSR * u_nR_FRR; 
    
    lst kalker_forcesFRR;
    kalker_forcesFRR =Fx_FRR,Fy_FRR,Mz_FRR;
    Matrix Mat_KakerForcesFRR = Matrix(kalker_forcesFRR.nops(),1,kalker_forcesFRR);
    Matrix dQ_dKFFRR = sys.jacobian(Delta.transpose(),Mat_KakerForcesFRR);
    
    Matrix CKFRR = dQ_dKFFRR * D_FRR*sys.jacobian(SlipFRR.transpose(),dq);
             
    lst new_atom_list_CKFRR, new_exp_list_CKFRR;
    matrix_list_optimize (CKFRR, new_atom_list_CKFRR, new_exp_list_CKFRR);
    sys.export_Matrix_C	("CKFRR","_CKFRR",CKFRR, new_atom_list_CKFRR, new_exp_list_CKFRR ,ORDER);
    sys.export_function_MATLAB("CKFRR", "CKFRR_",CKFRR, new_atom_list_CKFRR, new_exp_list_CKFRR,"q,qaux,dq,time,param");      
    
    
    
    //FRL ************************************************************************************************************   
    cout << "Kalker FRL"<<endl;
    symbol_numeric aFRL = *sys.new_Parameter("aFRL",0.0);
    symbol_numeric bFRL = *sys.new_Parameter("bFRL",0.0);
    
    symbol_numeric C11FRL = *sys.new_Parameter("C11FRL",0.0);
    symbol_numeric C22FRL = *sys.new_Parameter("C22FRL",0.0);
    symbol_numeric C23FRL = *sys.new_Parameter("C23FRL",0.0);
    symbol_numeric C33FRL = *sys.new_Parameter("C33FRL",0.0);
    
    Matrix D_FRL(3,3);
    ex GabFRL = G_elastic*aFRL*bFRL;
    D_FRL(0,0) = GabFRL * C11FRL; D_FRL(0,1) = 0;                                D_FRL(0,2) = 0;
    D_FRL(1,0) = 0;               D_FRL(1,1) = GabFRL * C22FRL;                  D_FRL(1,2) = GabFRL * sqrt(aFRL*bFRL)*C23FRL;
    D_FRL(2,0) = 0;               D_FRL(2,1) =-GabFRL * sqrt(aFRL*bFRL)*C23FRL;  D_FRL(2,2) = GabFRL * aFRL*bFRL*C33FRL;
    
    Matrix SlipFRL (3,1);
    SlipFRL (0,0) = VJW_FRL * u_t1R_FRL;
    SlipFRL (1,0) = VJW_FRL * u_t2R_FRL;
    SlipFRL (2,0) = OM_FWHSR * u_nR_FRL; 
    
    lst kalker_forcesFRL;
    kalker_forcesFRL =Fx_FRL,Fy_FRL,Mz_FRL;
    Matrix Mat_KakerForcesFRL = Matrix(kalker_forcesFRL.nops(),1,kalker_forcesFRL);
    Matrix dQ_dKFFRL = sys.jacobian(Delta.transpose(),Mat_KakerForcesFRL);
    
    Matrix CKFRL = dQ_dKFFRL * D_FRL*sys.jacobian(SlipFRL.transpose(),dq);
             
    lst new_atom_list_CKFRL, new_exp_list_CKFRL;
    matrix_list_optimize (CKFRL, new_atom_list_CKFRL, new_exp_list_CKFRL);
    sys.export_Matrix_C	("CKFRL","_CKFRL",CKFRL, new_atom_list_CKFRL, new_exp_list_CKFRL ,ORDER);
    sys.export_function_MATLAB("CKFRL", "CKFRL_",CKFRL, new_atom_list_CKFRL, new_exp_list_CKFRL,"q,qaux,dq,time,param");     


// sustituir las fuerzas de kalker (inputs) por cero en Q y exportar el nuevo Q (Q2)

    vector < symbol_numeric * > fk;
    fk.push_back( &Fx_RFR );fk.push_back( &Fy_RFR );fk.push_back( &Mz_RFR );
    fk.push_back( &Fx_RFL );fk.push_back( &Fy_RFL );fk.push_back( &Mz_RFL );
    fk.push_back( &Fx_RRR );fk.push_back( &Fy_RRR );fk.push_back( &Mz_RRR );
    fk.push_back( &Fx_RRL );fk.push_back( &Fy_RRL );fk.push_back( &Mz_RRL );    
    fk.push_back( &Fx_FFR );fk.push_back( &Fy_FFR );fk.push_back( &Mz_FFR );
    fk.push_back( &Fx_FFL );fk.push_back( &Fy_FFL );fk.push_back( &Mz_FFL );
    fk.push_back( &Fx_FRR );fk.push_back( &Fy_FRR );fk.push_back( &Mz_FRR );
    fk.push_back( &Fx_FRL );fk.push_back( &Fy_FRL );fk.push_back( &Mz_FRL );   
       
    for (int i=0; (i < Delta.rows()); ++i) {
        Delta(i,0) = recursive_substitution (Delta(i,0),fk , 0); 
    } 


    lst new_atom_list_Delta, new_exp_list_Delta;
    matrix_list_optimize (Delta, new_atom_list_Delta,new_exp_list_Delta);
    sys.export_Matrix_C	("Delta","_Delta",Delta, new_atom_list_Delta, new_exp_list_Delta ,ORDER);
    sys.export_function_MATLAB("Delta", "Delta_",Delta, new_atom_list_Delta, new_exp_list_Delta,"q,qaux,dq,time,param,inputs"); 
    
    
// ************************************************************************************************
// 	Energy Equations
// ************************************************************************************************

    cout << "Energy Equations" << endl;

    Matrix Energy(1,1);
    Energy(0,0)=0;
    sys.new_Matrix("Energy",Energy);



// ************************************************************************************************
// 	Export C code for Direct Simulation 
// ************************************************************************************************

    cout << "Export C code for Direct Simulation " << endl;
    sys.export_Dynamic_Simulation(sys, ORDER , MAPLE); 
    
// ************************************************************************************************
cout << "Init position and velocity " << endl;


system("rm *Init*");
Matrix PhiInit  = Matrix (2,1,&Phic,&Phit);
Matrix dPhiInit  = Matrix (2,1,&dPhic,&dPhit);
Matrix PhiInit_q = sys.jacobian(PhiInit.transpose(), Matrix (2,1,&q,&qaux));
Matrix dPhiInit_dq = sys.jacobian(dPhiInit.transpose(), Matrix (2,1,&dq,&dqaux));
Matrix BetaInit  = -dPhiInit;

for (int i=0; (i < dPhiInit.rows()); ++i) {
    BetaInit(i,0) = recursive_substitution (BetaInit(i,0),Velocities , 0);
    BetaInit(i,0) = recursive_substitution (BetaInit(i,0),Aux_Velocities , 0);
} 

lst new_atom_list_PhiInit, new_exp_list_PhiInit;
matrix_list_optimize (PhiInit, new_atom_list_PhiInit,new_exp_list_PhiInit);
sys.export_Matrix_C	("PhiInit","_PhiInit",PhiInit, new_atom_list_PhiInit, new_exp_list_PhiInit ,ORDER);
sys.export_function_MATLAB("PhiInit", "PhiInit_",PhiInit, new_atom_list_PhiInit, new_exp_list_PhiInit,"q,qaux,time,param"); 


lst new_atom_list_PhiInit_q, new_exp_list_PhiInit_q;
matrix_list_optimize (PhiInit_q, new_atom_list_PhiInit_q,new_exp_list_PhiInit_q);
sys.export_Matrix_C	("PhiInit_q","_PhiInit_q",PhiInit_q, new_atom_list_PhiInit_q, new_exp_list_PhiInit_q ,ORDER);
sys.export_function_MATLAB("PhiInit_q", "PhiInit_q_",PhiInit_q, new_atom_list_PhiInit_q, new_exp_list_PhiInit_q,"q,qaux,time,param"); 

lst new_atom_list_dPhiInit_dq, new_exp_list_dPhiInit_dq;
matrix_list_optimize (dPhiInit_dq, new_atom_list_dPhiInit_dq,new_exp_list_dPhiInit_dq);
sys.export_Matrix_C	("dPhiInit_dq","_dPhiInit_dq",dPhiInit_dq, new_atom_list_dPhiInit_dq, new_exp_list_dPhiInit_dq ,ORDER);
sys.export_function_MATLAB("dPhiInit_dq", "dPhiInit_dq_",dPhiInit_dq, new_atom_list_dPhiInit_dq, new_exp_list_dPhiInit_dq,"q,qaux,time,param"); 

lst new_atom_list_BetaInit, new_exp_list_BetaInit;
matrix_list_optimize (BetaInit, new_atom_list_BetaInit,new_exp_list_BetaInit);
sys.export_Matrix_C	("BetaInit","_BetaInit",BetaInit, new_atom_list_BetaInit, new_exp_list_BetaInit ,ORDER);
sys.export_function_MATLAB("BetaInit", "BetaInit_",BetaInit, new_atom_list_BetaInit, new_exp_list_BetaInit,"q,qaux,time,param");     
    

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
        state = xWAG , yWAG , zWAG , aWAG , bWAG , cWAG,bRWHSF,bRWHSR,bFWHSR,bFWHSF; 
    	//~ state = xWAG , yWAG , zWAG , aWAG , bWAG , cWAG , cRSLD , cFSLD , zRBOG , aRBOG , bRBOG , zFBOG , aFBOG , bFBOG , zRWHSF , aRWHSF , bRWHSF , zRWHSR , aRWHSR , bRWHSR , zFWHSF , aFWHSF , bFWHSF , zFWHSR , aFWHSR , bFWHSR ,
                //~ bRAXBFL , bRAXBFR , bRAXBRL , bRAXBRR , bFAXBFL , bFAXBFR , bFAXBRL , bFAXBRR ,
                //~ xRMOTF , yRMOTF , zRMOTF , bRMOTF , xRMOTR , yRMOTR , zRMOTR , bRMOTR , bRROTF , bRROTR,
                //~ thetaW_RFR, uW_RFR, uR_RFR, xR_RFR, thetaW_RFL, uW_RFL, uR_RFL, xR_RFL, thetaW_RRR, uW_RRR, uR_RRR, xR_RRR, thetaW_RRL, uW_RRL, uR_RRL, xR_RRL, thetaW_FFR, uW_FFR, uR_FFR, xR_FFR, thetaW_FRR, uW_FFL, uR_FFL, xR_FFL, thetaW_FRR, uW_FRR, uR_FRR, xR_FRR, thetaW_FRL, uW_FRL, uR_FRL, xR_FRL                
                //~ ; 

        sys.export_write_data_file_C(state);

// ************************************************************************************************
//	Export grphics.gnuplot
// ************************************************************************************************

	cout << "Export GNUPLOT file" << endl;
    sys.export_gnuplot ( state );


cout <<endl;
cout <<"atomos = " << atoms.size()<<endl<<endl;
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


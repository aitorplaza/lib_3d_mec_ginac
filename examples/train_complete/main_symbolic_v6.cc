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
    cout << "*             Train - Aresse                           *" << endl;
    cout << "*             COMPLETE v6 GOOD                         *" << endl;
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
    symbol_numeric xWAG = *sys.new_Coordinate("xWAG","dxWAG","ddxWAG", 0.002173454984843,0.0,0.0);
    symbol_numeric yWAG = *sys.new_Coordinate("yWAG","dyWAG","ddyWAG", 0.000000000376902,0.0,0.0);
    symbol_numeric zWAG = *sys.new_Coordinate("zWAG","dzWAG","ddzWAG", 0.661014257906143,0.0,0.0);
    symbol_numeric aWAG = *sys.new_Coordinate("aWAG","daWAG","ddaWAG",-0.000000003687361,0.0,0.0);
    symbol_numeric bWAG = *sys.new_Coordinate("bWAG","dbWAG","ddbWAG",-0.002093129064892,0.0,0.0);
    symbol_numeric cWAG = *sys.new_Coordinate("cWAG","dcWAG","ddcWAG",-0.000000000656998,0.0,0.0);

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


    symbol_numeric zRBOG = *sys.new_Coordinate("zRBOG","dzRBOG","ddzRBOG",-0.124099654800027,0.0,0.0);
    symbol_numeric aRBOG = *sys.new_Coordinate("aRBOG","daRBOG","ddaRBOG", 0.000000002624182,0.0,0.0);
    symbol_numeric bRBOG = *sys.new_Coordinate("bRBOG","dbRBOG","ddbRBOG", 0.002041160116411,0.0,0.0);

    symbol_numeric *dzRBOG=sys.get_Velocity("dzRBOG");
    symbol_numeric *daRBOG=sys.get_Velocity("daRBOG");
    symbol_numeric *dbRBOG=sys.get_Velocity("dbRBOG");

    symbol_numeric *ddzRBOG=sys.get_Acceleration("ddzRBOG");
    symbol_numeric *ddaRBOG=sys.get_Acceleration("ddaRBOG");
    symbol_numeric *ddbRBOG=sys.get_Acceleration("ddbRBOG");

 
    // =====================================================================================================================================================================================
    // FRONT BOGIE coordinates FBOG
    // =====================================================================================================================================================================================


    symbol_numeric zFBOG = *sys.new_Coordinate("zFBOG","dzFBOG","ddzFBOG",-0.13014624550219,0.0,0.0);
    symbol_numeric aFBOG = *sys.new_Coordinate("aFBOG","daFBOG","ddaFBOG", 0.000000002218847,0.0,0.0);
    symbol_numeric bFBOG = *sys.new_Coordinate("bFBOG","dbFBOG","ddbFBOG", 0.002039849527966,0.0,0.0);

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

    symbol_numeric zRWHSF = *sys.new_Coordinate("zRWHSF","dzRWHSF","ddzRWHSF",0.053443379425869,0.0,0.0);
    symbol_numeric aRWHSF = *sys.new_Coordinate("aRWHSF","daRWHSF","ddaRWHSF",0.000000001358710,0.0,0.0);
    symbol_numeric bRWHSF = *sys.new_Coordinate("bRWHSF","dbRWHSF","ddbRWHSF",0.004359712322614,0.0,0.0);
    
    symbol_numeric *dzRWHSF=sys.get_Velocity("dzRWHSF"); symbol_numeric *daRWHSF=sys.get_Velocity("daRWHSF"); symbol_numeric *dbRWHSF=sys.get_Velocity("dbRWHSF");
    symbol_numeric *ddzRWHSF=sys.get_Acceleration("ddzRWHSF"); symbol_numeric *ddaRWHSF=sys.get_Acceleration("ddaRWHSF"); symbol_numeric *ddbRWHSF=sys.get_Acceleration("ddbRWHSF");
 
    //REAR WHEELSET (RWHSR)

    symbol_numeric zRWHSR = *sys.new_Coordinate("zRWHSR","dzRWHSR","ddzRWHSR",0.053556931578402,0.0,0.0);
    symbol_numeric aRWHSR = *sys.new_Coordinate("aRWHSR","daRWHSR","ddaRWHSR",0.000000001381110,0.0,0.0);
    symbol_numeric bRWHSR = *sys.new_Coordinate("bRWHSR","dbRWHSR","ddbRWHSR",0.004359218052315,0.0,0.0);

    symbol_numeric *dzRWHSR=sys.get_Velocity("dzRWHSR"); symbol_numeric *daRWHSR=sys.get_Velocity("daRWHSR"); symbol_numeric *dbRWHSR=sys.get_Velocity("dbRWHSR");
    symbol_numeric *ddzRWHSR=sys.get_Acceleration("ddzRWHSR"); symbol_numeric *ddaRWHSR=sys.get_Acceleration("ddaRWHSR"); symbol_numeric *ddbRWHSR=sys.get_Acceleration("ddbRWHSR");

    // =====================================================================================================================================================================================
    // FRONT BOGIE WHEELSET coordinates
    // =====================================================================================================================================================================================

    //FRONT WHEELSET (FWHSF)

    symbol_numeric zFWHSF = *sys.new_Coordinate("zFWHSF","dzFWHSF","ddzFWHSF",0.039603813451902,0.0,0.0);
    symbol_numeric aFWHSF = *sys.new_Coordinate("aFWHSF","daFWHSF","ddaFWHSF",0.000000001279279,0.0,0.0);
    symbol_numeric bFWHSF = *sys.new_Coordinate("bFWHSF","dbFWHSF","ddbFWHSF",0.004373068542307,0.0,0.0);
    
    symbol_numeric *dzFWHSF=sys.get_Velocity("dzFWHSF"); symbol_numeric *daFWHSF=sys.get_Velocity("daFWHSF"); symbol_numeric *dbFWHSF=sys.get_Velocity("dbFWHSF");
    symbol_numeric *ddzFWHSF=sys.get_Acceleration("ddzFWHSF"); symbol_numeric *ddaFWHSF=sys.get_Acceleration("ddaFWHSF"); symbol_numeric *ddbFWHSF=sys.get_Acceleration("ddbFWHSF");
 
    //REAR WHEELSET (FWHSR)

    symbol_numeric zFWHSR = *sys.new_Coordinate("zFWHSR","dzFWHSR","ddzFWHSR",0.039720229240195,0.0,0.0);
    symbol_numeric aFWHSR = *sys.new_Coordinate("aFWHSR","daFWHSR","ddaFWHSR",0.000000001040224,0.0,0.0);
    symbol_numeric bFWHSR = *sys.new_Coordinate("bFWHSR","dbFWHSR","ddbFWHSR",0.004373404786612,0.0,0.0);

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
    symbol_numeric xRMOTF = *sys.new_Coordinate("xRMOTF","dxRMOTF","ddxRMOTF",-0.000001027461190,0.0,0.0);
    symbol_numeric yRMOTF = *sys.new_Coordinate("yRMOTF","dyRMOTF","ddyRMOTF", 0.000000000100701 ,0.0,0.0);
    symbol_numeric zRMOTF = *sys.new_Coordinate("zRMOTF","dzRMOTF","ddzRMOTF",-0.022298643617830,0.0,0.0);
    symbol_numeric bRMOTF = *sys.new_Coordinate("bRMOTF","dbRMOTF","ddbRMOTF", 0.004415102135735,0.0,0.0);

    symbol_numeric *dxRMOTF=sys.get_Velocity("dxRMOTF");
    symbol_numeric *dyRMOTF=sys.get_Velocity("dyRMOTF");
    symbol_numeric *dzRMOTF=sys.get_Velocity("dzRMOTF");
    symbol_numeric *dbRMOTF=sys.get_Velocity("dbRMOTF");

    symbol_numeric *ddxRMOTF=sys.get_Acceleration("ddxRMOTF");
    symbol_numeric *ddyRMOTF=sys.get_Acceleration("ddyRMOTF");
    symbol_numeric *ddzRMOTF=sys.get_Acceleration("ddzRMOTF");
    symbol_numeric *ddbRMOTF=sys.get_Acceleration("ddbRMOTF");

    //REAR RMOTOR (RMOTR)
    symbol_numeric xRMOTR = *sys.new_Coordinate("xRMOTR","dxRMOTR","ddxRMOTR",-0.000001027375578,0.0,0.0);
    symbol_numeric yRMOTR = *sys.new_Coordinate("yRMOTR","dyRMOTR","ddyRMOTR", 0.000000000101921 ,0.0,0.0);
    symbol_numeric zRMOTR = *sys.new_Coordinate("zRMOTR","dzRMOTR","ddzRMOTR",-0.022298578469500,0.0,0.0);
    symbol_numeric bRMOTR = *sys.new_Coordinate("bRMOTR","dbRMOTR","ddbRMOTR",-0.004415075578217,0.0,0.0);

    symbol_numeric *dxRMOTR=sys.get_Velocity("dxRMOTR");
    symbol_numeric *dyRMOTR=sys.get_Velocity("dyRMOTR");
    symbol_numeric *dzRMOTR=sys.get_Velocity("dzRMOTR");
    symbol_numeric *dbRMOTR=sys.get_Velocity("dbRMOTR");

    symbol_numeric *ddxRMOTR=sys.get_Acceleration("ddxRMOTR");
    symbol_numeric *ddyRMOTR=sys.get_Acceleration("ddyRMOTR");
    symbol_numeric *ddzRMOTR=sys.get_Acceleration("ddzRMOTR");
    symbol_numeric *ddbRMOTR=sys.get_Acceleration("ddbRMOTR");

    //FRONT ROTOR (RROTF)
    symbol_numeric bRROTF = *sys.new_Coordinate("bRROTF","dbRROTF","ddbRROTF",-0.018528797724848 ,0.0,0.0);
    symbol_numeric *dbRROTF=sys.get_Velocity("dbRROTF");
    symbol_numeric *ddbRROTF=sys.get_Acceleration("ddbRROTF");
    
    //REAR RROTOR (RROTR)   
    symbol_numeric bRROTR = *sys.new_Coordinate("bRROTR","dbRROTR","ddbRROTR",-0.018526697072451,0.0,0.0);
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

    //In meters, change stl files
    
    
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
    symbol_numeric L_WHS          = *sys.new_Parameter("L_WHS",0.815);     
    symbol_numeric L_WAG          = *sys.new_Parameter("L_WAG",9.500);     

    symbol_numeric L_SUSPBEAM1     = *sys.new_Parameter("L_SUSPBEAM1",0.5); //En verdad son 0.485
    symbol_numeric L_SUSPBEAM2     = *sys.new_Parameter("L_SUSPBEAM2",0.170);
    
    symbol_numeric L_SLDx         = *sys.new_Parameter("L_SLDx",0.170);  
    symbol_numeric L_SLDy         = *sys.new_Parameter("L_SLDy",0.815);
    
    symbol_numeric b_pend = *sys.new_Parameter("b_pend",0.0);
    symbol_numeric a_pend = *sys.new_Parameter("a_pend",0.0);

    symbol_numeric L_O_ORAIL= *sys.new_Parameter("L_O_ORAIL",0.815);
    
    symbol_numeric  L0_1 = *sys.new_Parameter("L0_1",0.310);
    symbol_numeric  L0_2 = *sys.new_Parameter("L0_2",0.378);

    
// ************************************************************************************************************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************************************************************************************************************

// ************************************************************************************************************************************************************************************************
//	Define Bases
// ************************************************************************************************************************************************************************************************
    // RAIL BASE 
    sys.new_Base("B_RAIL","xyz",0,0,0,0);//Base Rail
    //sys.new_Base("B_RAIL","xyz",0,1,0, b_pend);//Base Rail
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

    Vector3D ORMOTF_ORROTF  = *sys.new_Vector3D("ORMOTF_ORROTF", L_MOT,0,0,"B_RMOTF"); 
    Vector3D ORMOTR_ORROTR  = *sys.new_Vector3D("ORMOTR_ORROTR",-L_MOT,0,0,"B_RMOTR"); 

    Vector3D ORBOG_ORWHSF   = *sys.new_Vector3D("ORBOG_ORWHSF", L_OBOG_OWHS,0,zRWHSF,"B_RBOG"); 
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
    symbol_numeric lambda11 = *sys.new_Joint_Unknown("lambda11");
    symbol_numeric lambda12 = *sys.new_Joint_Unknown("lambda12");
    symbol_numeric lambda13 = *sys.new_Joint_Unknown("lambda13");
    symbol_numeric lambda14 = *sys.new_Joint_Unknown("lambda14");
    symbol_numeric lambda15 = *sys.new_Joint_Unknown("lambda15");
    symbol_numeric lambda16 = *sys.new_Joint_Unknown("lambda16");
    symbol_numeric lambda17 = *sys.new_Joint_Unknown("lambda17");
    symbol_numeric lambda18 = *sys.new_Joint_Unknown("lambda18");
    symbol_numeric lambda19 = *sys.new_Joint_Unknown("lambda19");
    symbol_numeric lambda20 = *sys.new_Joint_Unknown("lambda20");    
    symbol_numeric lambda21 = *sys.new_Joint_Unknown("lambda21");
    symbol_numeric lambda22 = *sys.new_Joint_Unknown("lambda22");
    symbol_numeric lambda23 = *sys.new_Joint_Unknown("lambda23");
    symbol_numeric lambda24 = *sys.new_Joint_Unknown("lambda24");
    symbol_numeric lambda25 = *sys.new_Joint_Unknown("lambda25");
    symbol_numeric lambda26 = *sys.new_Joint_Unknown("lambda26");
    symbol_numeric lambda27 = *sys.new_Joint_Unknown("lambda27");
    symbol_numeric lambda28 = *sys.new_Joint_Unknown("lambda28");
    symbol_numeric lambda29 = *sys.new_Joint_Unknown("lambda29");
    symbol_numeric lambda30 = *sys.new_Joint_Unknown("lambda30");
    symbol_numeric lambda31 = *sys.new_Joint_Unknown("lambda31");
    symbol_numeric lambda32 = *sys.new_Joint_Unknown("lambda32");
    symbol_numeric lambda33 = *sys.new_Joint_Unknown("lambda33");
    symbol_numeric lambda34 = *sys.new_Joint_Unknown("lambda34");
    symbol_numeric lambda35 = *sys.new_Joint_Unknown("lambda35");
    symbol_numeric lambda36 = *sys.new_Joint_Unknown("lambda36");
    symbol_numeric lambda37 = *sys.new_Joint_Unknown("lambda37");
    symbol_numeric lambda38 = *sys.new_Joint_Unknown("lambda38");  
    symbol_numeric lambda39 = *sys.new_Joint_Unknown("lambda39");
    symbol_numeric lambda40 = *sys.new_Joint_Unknown("lambda40"); 


// ************************************************************************************************
// 	Input Vector
// ************************************************************************************************


    cout << "Input Vector" << endl;
    
    symbol_numeric T_RMOTF = *sys.new_Input("T_RMOTF",0.0);
    symbol_numeric T_RMOTR = *sys.new_Input("T_RMOTR",0.0);

    Vector3D F_RMOTF = *sys.new_Vector3D("F_RMOTF",0,0,0,"B_RROTF");
    Vector3D M_RMOTF = *sys.new_Vector3D("M_RMOTF",0,T_RMOTF,0, "B_RROTF");
    Vector3D F_RMOTR = *sys.new_Vector3D("F_RMOTR",0,0,0,"B_RROTR");
    Vector3D M_RMOTR = *sys.new_Vector3D("M_RMOTR",0,T_RMOTR,0, "B_RROTR");
 
    // mu/V_sip 
    symbol_numeric mu_V_RRF = *sys.new_Input("mu_V_RRF",0.0);
    symbol_numeric mu_V_RLF = *sys.new_Input("mu_V_RLF",0.0);
    symbol_numeric mu_V_RRR = *sys.new_Input("mu_V_RRR",0.0);
    symbol_numeric mu_V_RLR = *sys.new_Input("mu_V_RLR",0.0);
    symbol_numeric mu_V_FRF = *sys.new_Input("mu_V_FRF",0.0);
    symbol_numeric mu_V_FLF = *sys.new_Input("mu_V_FLF",0.0);
    symbol_numeric mu_V_FRR = *sys.new_Input("mu_V_FRR",0.0);
    symbol_numeric mu_V_FLR = *sys.new_Input("mu_V_FLR",0.0);  
    
    // Normal forces
    symbol_numeric N_RRF = *sys.new_Input("N_RRF",0.0);
    symbol_numeric N_RLF = *sys.new_Input("N_RLF",0.0);
    symbol_numeric N_RRR = *sys.new_Input("N_RRR",0.0);
    symbol_numeric N_RLR = *sys.new_Input("N_RLR",0.0);  
    symbol_numeric N_FRF = *sys.new_Input("N_FRF",0.0);
    symbol_numeric N_FLF = *sys.new_Input("N_FLF",0.0);
    symbol_numeric N_FRR = *sys.new_Input("N_FRR",0.0);
    symbol_numeric N_FLR = *sys.new_Input("N_FLR",0.0);


   // Breaks
   symbol_numeric T_FBRKF = *sys.new_Input("T_FBRKF",0.0);
   symbol_numeric T_FBRKR = *sys.new_Input("T_FBRKR",0.0);
   Vector3D F_FBRKF = *sys.new_Vector3D("F_FBRKF",0,0,0,"B_FWHSF");
   Vector3D M_FBRKF = *sys.new_Vector3D("M_FBRKF",0,T_FBRKF,0,"B_FWHSF");
   Vector3D F_FBRKR = *sys.new_Vector3D("F_FBRKR",0,0,0,"B_FWHSR");
   Vector3D M_FBRKR = *sys.new_Vector3D("M_FBRKR",0,T_FBRKR,0, "B_FWHSR");
   
   
   symbol_numeric T_RBRKF = *sys.new_Input("T_RBRKF",0.0);
   symbol_numeric T_RBRKR = *sys.new_Input("T_RBRKR",0.0);
   Vector3D F_RBRKF = *sys.new_Vector3D("F_RBRKF",0,0,0,"B_RWHSF");
   Vector3D M_RBRKF = *sys.new_Vector3D("M_RBRKF",0,T_RBRKF,0,"B_RWHSF");
   Vector3D F_RBRKR = *sys.new_Vector3D("F_RBRKR",0,0,0,"B_RWHSR");
   Vector3D M_RBRKR = *sys.new_Vector3D("M_RBRKR",0,T_RBRKR,0, "B_RWHSR");
   
   
   
   
// ************************************************************************************************
//	Force and Momentum Definition
// ************************************************************************************************   

 cout << "Force and Momentum Definition" << endl;

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
    Wrench3D * Inertia_WAG   = sys.Inertia_Wrench("WAG");
    
    Wrench3D * Inertia_RBOG   = sys.Inertia_Wrench("RBOG");
    Wrench3D * Inertia_RMOTF  = sys.Inertia_Wrench("RMOTF");
    Wrench3D * Inertia_RMOTR  = sys.Inertia_Wrench("RMOTR");
    Wrench3D * Inertia_RROTF  = sys.Inertia_Wrench("RROTF");
    Wrench3D * Inertia_RROTR  = sys.Inertia_Wrench("RROTR");     
    Wrench3D * Inertia_RWHSF  = sys.Inertia_Wrench("RWHSF");   
    Wrench3D * Inertia_RWHSR  = sys.Inertia_Wrench("RWHSR");   
    Wrench3D * Inertia_RAXBFL = sys.Inertia_Wrench("RAXBFL");
    Wrench3D * Inertia_RAXBFR = sys.Inertia_Wrench("RAXBFR");
    Wrench3D * Inertia_RAXBRL = sys.Inertia_Wrench("RAXBRL");
    Wrench3D * Inertia_RAXBRR = sys.Inertia_Wrench("RAXBRR");
    Wrench3D * Inertia_RSLD   = sys.Inertia_Wrench("RSLD");
    
    Wrench3D * Inertia_FBOG   = sys.Inertia_Wrench("FBOG");
    Wrench3D * Inertia_FWHSF  = sys.Inertia_Wrench("FWHSF");   
    Wrench3D * Inertia_FWHSR  = sys.Inertia_Wrench("FWHSR");   
    Wrench3D * Inertia_FAXBFL = sys.Inertia_Wrench("FAXBFL");
    Wrench3D * Inertia_FAXBFR = sys.Inertia_Wrench("FAXBFR");
    Wrench3D * Inertia_FAXBRL = sys.Inertia_Wrench("FAXBRL");
    Wrench3D * Inertia_FAXBRR = sys.Inertia_Wrench("FAXBRR");
    Wrench3D * Inertia_FSLD   = sys.Inertia_Wrench("FSLD");
    //	Constitutive

    //	External
	Wrench3D * RMOTF_Torque = sys.new_Wrench3D ( "RMOTF_Torque",F_RMOTF ,M_RMOTF , O_RROTF , RMOTF ,RROTF, "External") ;
	Wrench3D * RMOTR_Torque = sys.new_Wrench3D ( "RMOTR_Torque",F_RMOTR ,M_RMOTR , O_RROTR , RMOTR ,RROTR, "External") ;
	
	
	
// ************************************************************************************************
// 	Vectors needed to take diferent Jacobians
// ************************************************************************************************

    cout << "Vectors needed to take diferent Jacobians" << endl;

    Matrix q = sys.Coordinates();
    Matrix dq = sys.Velocities();
    Matrix ddq = sys.Accelerations();
    Matrix pars = sys.Parameters();
    Matrix inps = sys.Inputs();
    Matrix unks = sys.Joint_Unknowns();

// ************************************************************************************************
// 	 Kinematic Equations 
// ************************************************************************************************


// ************************************************************************************************
//      Contact Wheel - Rail
// ************************************************************************************************
    //symbol_numeric Rw = *sys.new_Parameter("Rw",0.625);
    //symbol_numeric rw = *sys.new_Parameter("rw",0.610);
    symbol_numeric Rw = *sys.new_Parameter("Rw",0.425);
    symbol_numeric rw = *sys.new_Parameter("rw",0.415);

    symbol_numeric Lw = *sys.new_Parameter("Lw",0.13);
    symbol_numeric rR = *sys.new_Parameter("rR",0.160);
    
    symbol_numeric RthetaWRF = *sys.new_Coordinate("RthetaWRF","dRthetaWRF","ddRthetaWRF",0.004307743382025,0.0,0.0);
    symbol_numeric RyWRF = *sys.new_Coordinate("RyWRF","dRyWRF","ddRyWRF",0.012271436702701,0.0,0.0);
    symbol_numeric RthetaWLF = *sys.new_Coordinate("RthetaWLF","dRthetaWLF","ddRthetaWLF",0.004307743366241,0.0,0.0);
    symbol_numeric RyWLF = *sys.new_Coordinate("RyWLF","dRyWLF","ddRyWLF",-0.012271442940415,0.0,0.0);

    symbol_numeric RthetaWRR = *sys.new_Coordinate("RthetaWRR","dRthetaWRR","ddRthetaWRR",0.004307249111727,0.0,0.0);
    symbol_numeric RyWRR = *sys.new_Coordinate("RyWRR","dRyWRR","ddRyWRR",0.012271436465370,0.0,0.0);
    symbol_numeric RthetaWLR = *sys.new_Coordinate("RthetaWLR","dRthetaWLR","ddRthetaWLR",0.004307249095943,0.0,0.0);
    symbol_numeric RyWLR = *sys.new_Coordinate("RyWLR","dRyWLR","ddRyWLR",-0.012271443177746,0.0,0.0);

    symbol_numeric RthetaRRF = *sys.new_Coordinate("RthetaRRF","dRthetaRRF","ddRthetaRRF",  0.076771890975407,0.0,0.0);
    symbol_numeric RxRRF = *sys.new_Coordinate("RxRRF","dRxRRF","ddRxRRF", -3.655059162240242 ,0.0,0.0);
    symbol_numeric RthetaRLF = *sys.new_Coordinate("RthetaRLF","dRthetaRLF","ddRthetaRLF",-0.076771891564149 ,0.0,0.0);
    symbol_numeric RxRLF= *sys.new_Coordinate("RxRLF","dRxRLF","ddRxRLF",-3.655059162082171 ,0.0,0.0);

    symbol_numeric RthetaRRR = *sys.new_Coordinate("RthetaRRR","dRthetaRRR","ddRthetaRRR",  0.076771890953007 ,0.0,0.0);
    symbol_numeric RxRRR = *sys.new_Coordinate("RxRRR","dRxRRR","ddRxRRR", -5.840059165190834 ,0.0,0.0);
    symbol_numeric RthetaRLR = *sys.new_Coordinate("RthetaRLR","dRthetaRLR","ddRthetaRLR", -0.076771891586549,0.0,0.0);
    symbol_numeric RxRLR= *sys.new_Coordinate("RxRLR","dRxRLR","ddRxRLR", -5.840059165032765,0.0,0.0);

    symbol_numeric FthetaWRF = *sys.new_Coordinate("FthetaWRF","dFthetaWRF","ddFthetaWRF",0.004319788921094,0.0,0.0);
    symbol_numeric FyWRF = *sys.new_Coordinate("FyWRF","dFyWRF","ddFyWRF",  0.012271441865376,0.0,0.0);
    symbol_numeric FthetaWLF = *sys.new_Coordinate("FthetaWLF","dFthetaWLF","ddFthetaWLF", 0.004319789089669,0.0,0.0);
    symbol_numeric FyWLF = *sys.new_Coordinate("FyWLF","dFyWLF","ddFyWLF", -0.012271437777739,0.0,0.0);

    symbol_numeric FthetaWRR = *sys.new_Coordinate("FthetaWRR","dFthetaWRR","ddFthetaWRR", 0.004320125165400,0.0,0.0);
    symbol_numeric FyWRR = *sys.new_Coordinate("FyWRR","dFyWRR","ddFyWRR", 0.012271444398169,0.0,0.0);
    symbol_numeric FthetaWLR = *sys.new_Coordinate("FthetaWLR","dFthetaWLR","ddFthetaWLR",0.004320125333973,0.0,0.0);
    symbol_numeric FyWLR = *sys.new_Coordinate("FyWLR","dFyWLR","ddFyWLR",-0.012271435244947,0.0,0.0);

    symbol_numeric FthetaRRF = *sys.new_Coordinate("FthetaRRF","dFthetaRRF","ddFthetaRRF",0.076771891462682 ,0.0,0.0);
    symbol_numeric FxRRF = *sys.new_Coordinate("FxRRF","dFxRRF","ddFxRRF",5.844933351574941 ,0.0,0.0);
    symbol_numeric FthetaRLF = *sys.new_Coordinate("FthetaRLF","dFthetaRLF","ddFthetaRLF", -0.076771891076874 ,0.0,0.0);
    symbol_numeric FxRLF= *sys.new_Coordinate("FxRLF","dFxRLF","ddFxRLF", 5.844933349886748,0.0,0.0);

    symbol_numeric FthetaRRR = *sys.new_Coordinate("FthetaRRR","dFthetaRRR","ddFthetaRRR", 0.076771891701738 ,0.0,0.0);
    symbol_numeric FxRRR = *sys.new_Coordinate("FxRRR","dFxRRR","ddFxRRR", 3.659933348473641,0.0,0.0);
    symbol_numeric FthetaRLR = *sys.new_Coordinate("FthetaRLR","dFthetaRLR","ddFthetaRLR", -0.076771890837819,0.0,0.0);
    symbol_numeric FxRLR= *sys.new_Coordinate("FxRLR","dFxRLR","ddFxRLR", 3.659933346785468,0.0,0.0);   
    
    
    
    
 
    //~ symbol_numeric thetaWRF = *sys.new_AuxCoordinate("thetaWRF","dthetaWRF","ddthetaWRF",0.0,0.0,0.0);
    //~ symbol_numeric yWRF = *sys.new_AuxCoordinate("yWRF","dyWRF","ddyWRF",0.0 ,0.0,0.0);
    //~ symbol_numeric thetaWLF = *sys.new_AuxCoordinate("thetaWLF","dthetaWLF","ddthetaWLF",0.0,0.0,0.0);
    //~ symbol_numeric yWLF = *sys.new_AuxCoordinate("yWLF","dyWLF","ddyWLF",0.0 ,0.0,0.0);
//~ 
    //~ symbol_numeric thetaWRR = *sys.new_AuxCoordinate("thetaWRR","dthetaWRR","ddthetaWRR",0.0,0.0,0.0);
    //~ symbol_numeric yWRR = *sys.new_AuxCoordinate("yWRR","dyWRR","ddyWRR",0.0 ,0.0,0.0);
    //~ symbol_numeric thetaWLR = *sys.new_AuxCoordinate("thetaWLR","dthetaWLR","ddthetaWLR",0.0,0.0,0.0);
    //~ symbol_numeric yWLR = *sys.new_AuxCoordinate("yWLR","dyWLR","ddyWLR",0.0 ,0.0,0.0);
//~ 
    //~ symbol_numeric thetaRRF = *sys.new_AuxCoordinate("thetaRRF","dthetaRRF","ddthetaRRF",0.0,0.0,0.0);
    //~ symbol_numeric xRRF = *sys.new_AuxCoordinate("xRRF","dxRRF","ddxRRF",0.0,0.0,0.0);
    //~ symbol_numeric thetaRLF = *sys.new_AuxCoordinate("thetaRLF","dthetaRLF","ddthetaRLF",0.0,0.0,0.0);
    //~ symbol_numeric xRLF= *sys.new_AuxCoordinate("xRLF","dxRLF","ddxRLF",0.0,0.0,0.0);
//~ 
    //~ symbol_numeric thetaRRR = *sys.new_AuxCoordinate("thetaRRR","dthetaRRR","ddthetaRRR",0.0,0.0,0.0);
    //~ symbol_numeric xRRR = *sys.new_AuxCoordinate("xRRR","dxRRR","ddxRRR",0.0,0.0,0.0);
    //~ symbol_numeric thetaRLR = *sys.new_AuxCoordinate("thetaRLR","dthetaRLR","ddthetaRLR",0.0,0.0,0.0);
    //~ symbol_numeric xRLR= *sys.new_AuxCoordinate("xRLR","dxRLR","ddxRLR",0.0,0.0,0.0);
   
   

    //RAIL POINTS
    Vector3D O_ORAILR = *sys.new_Vector3D("O_ORAILR",0,-L_O_ORAIL,0,"B_RAIL");
    Point * P_RailR  = sys.new_Point("P_RailR","O",&O_ORAILR);
    Vector3D O_ORAILL = *sys.new_Vector3D("O_ORAILL",0,L_O_ORAIL,0,"B_RAIL");
    Point * P_RailL  = sys.new_Point("P_RailL","O",&O_ORAILL);
    
    
    // REAR BOGIE
    // =======================================================================================================
    // FRONT RIGTH WHEEL and RAIL
    ex f_RRF = -RyWRF*((Rw-rw)/Lw)-((Rw+rw)/2.0);
    Vector3D OPRWHF_ORWHSRF = *sys.new_Vector3D("OPRWHF_ORWHSRF",0,-L_OBOG_OAXBy,0,"B_RWHSF");
    Point * O_RWHSRF  = sys.new_Point("O_RWHSRF","O_RWHSF",&OPRWHF_ORWHSRF);
    Vector3D fRWHSRF = *sys.new_Vector3D("fRWHSRF",-f_RRF*sin(RthetaWRF),RyWRF,f_RRF*cos(RthetaWRF),"B_RWHSF");
    Vector3D r_RWHSRF = sys.Position_Vector("O","O_RWHSRF")+fRWHSRF;
    Vector3D t1_RWHSRF= sys.diff ( r_RWHSRF , RthetaWRF);
    Vector3D t2_RWHSRF= sys.diff ( r_RWHSRF , RyWRF);
    Vector3D n_RWHSRF = t1_RWHSRF^t2_RWHSRF;



    Vector3D f_RRAILRF = *sys.new_Vector3D("f_RRAILRF",RxRRF,rR*sin(RthetaRRF),rR*cos(RthetaRRF),"B_RAIL");
    Vector3D r_RRAILRF = sys.Position_Vector("O","P_RailR")+f_RRAILRF;
    Vector3D t1_RRAILRF = sys.diff ( r_RRAILRF , RxRRF);
    Vector3D t2_RRAILRF = sys.diff ( r_RRAILRF , RthetaRRF);
    Vector3D n_RRAILRF = t1_RRAILRF^t2_RRAILRF;
    

    // FRONT LEFT WHEEL and RAIL
    ex f_RLF = RyWLF*((Rw-rw)/Lw)-((Rw+rw)/2.0);
    Vector3D OPRWHF_ORWHSLF = *sys.new_Vector3D("OPRWHF_ORWHSLF",0,L_OBOG_OAXBy,0,"B_RWHSF");
    Point * O_RWHSLF  = sys.new_Point("O_RWHSLF","O_RWHSF",&OPRWHF_ORWHSLF);
    Vector3D fRWHSLF = *sys.new_Vector3D("fRWHSLF",-f_RLF*sin(RthetaWLF),RyWLF,f_RLF*cos(RthetaWLF),"B_RWHSF");
    Vector3D r_RWHSLF = sys.Position_Vector("O","O_RWHSLF")+fRWHSLF;
    Vector3D t1_RWHSLF= sys.diff ( r_RWHSLF , RthetaWLF);
    Vector3D t2_RWHSLF= sys.diff ( r_RWHSLF , RyWLF);
    Vector3D n_RWHSLF = t1_RWHSLF^t2_RWHSLF;

    Vector3D f_RRAILLF = *sys.new_Vector3D("f_RRAILLF",RxRLF,rR*sin(RthetaRLF),rR*cos(RthetaRLF),"B_RAIL");
    Vector3D r_RRAILLF = sys.Position_Vector("O","P_RailL")+f_RRAILLF;
    Vector3D t1_RRAILLF = sys.diff ( r_RRAILLF , RxRLF);
    Vector3D t2_RRAILLF = sys.diff ( r_RRAILLF , RthetaRLF);
    Vector3D n_RRAILLF = t1_RRAILLF^t2_RRAILLF;  
    
    // REAR RIGTH WHEEL and RAIL
    ex f_RRR = -RyWRR*((Rw-rw)/Lw)-((Rw+rw)/2.0);
    Vector3D OPRWHR_ORWHSRR = *sys.new_Vector3D("OPRWHR_ORWHSRR",0,-L_OBOG_OAXBy,0,"B_RWHSR");
    Point * O_RWHSRR  = sys.new_Point("O_RWHSRR","O_RWHSR",&OPRWHR_ORWHSRR);
    Vector3D fRWHSRR = *sys.new_Vector3D("fRWHSRR",-f_RRR*sin(RthetaWRR),RyWRR,f_RRR*cos(RthetaWRR),"B_RWHSR");
    Vector3D r_RWHSRR = sys.Position_Vector("O","O_RWHSRR")+fRWHSRR;
    Vector3D t1_RWHSRR= sys.diff ( r_RWHSRR , RthetaWRR);
    Vector3D t2_RWHSRR= sys.diff ( r_RWHSRR , RyWRR);
    Vector3D n_RWHSRR = t1_RWHSRR^t2_RWHSRR;

    Vector3D f_RRAILRR = *sys.new_Vector3D("f_RRAILRR",RxRRR,rR*sin(RthetaRRR),rR*cos(RthetaRRR),"B_RAIL");
    Vector3D r_RRAILRR = sys.Position_Vector("O","P_RailR")+f_RRAILRR;
    Vector3D t1_RRAILRR = sys.diff ( r_RRAILRR , RxRRR);
    Vector3D t2_RRAILRR = sys.diff ( r_RRAILRR , RthetaRRR);
    Vector3D n_RRAILRR = t1_RRAILRR^t2_RRAILRR;

 
 
    // REAR LEFT WHEEL and RAIL
    ex f_RLR = RyWLR*((Rw-rw)/Lw)-((Rw+rw)/2.0);
    Vector3D OPRWHR_ORWHSLR = *sys.new_Vector3D("OPRWHR_ORWHSLR",0,L_OBOG_OAXBy,0,"B_RWHSR");
    Point * O_RWHSLR  = sys.new_Point("O_RWHSLR","O_RWHSR",&OPRWHR_ORWHSLR);
    Vector3D fRWHSLR = *sys.new_Vector3D("fRWHSLR",-f_RLR*sin(RthetaWLR),RyWLR,f_RLR*cos(RthetaWLR),"B_RWHSR");
    Vector3D r_RWHSLR = sys.Position_Vector("O","O_RWHSLR")+fRWHSLR;
    Vector3D t1_RWHSLR= sys.diff ( r_RWHSLR , RthetaWLR);
    Vector3D t2_RWHSLR= sys.diff ( r_RWHSLR , RyWLR);
    Vector3D n_RWHSLR = t1_RWHSLR^t2_RWHSLR;

    Vector3D f_RRAILLR = *sys.new_Vector3D("f_RRAILLR",RxRLR,rR*sin(RthetaRLR),rR*cos(RthetaRLR),"B_RAIL");
    Vector3D r_RRAILLR = sys.Position_Vector("O","P_RailL")+f_RRAILLR;
    Vector3D t1_RRAILLR = sys.diff ( r_RRAILLR , RxRLR);
    Vector3D t2_RRAILLR = sys.diff ( r_RRAILLR , RthetaRLR);
    Vector3D n_RRAILLR = t1_RRAILLR^t2_RRAILLR; 


    // FRONT BOGIE
    // =======================================================================================================
    // FRONT RIGTH WHEEL and RAIL
    ex f_FRF = -FyWRF*((Rw-rw)/Lw)-((Rw+rw)/2.0);
    Vector3D OPFWHF_OFWHSRF = *sys.new_Vector3D("OPFWHF_OFWHSRF",0,-L_OBOG_OAXBy,0,"B_FWHSF");
    Point * O_FWHSRF  = sys.new_Point("O_FWHSRF","O_FWHSF",&OPFWHF_OFWHSRF);
    Vector3D fFWHSRF = *sys.new_Vector3D("fFWHSRF",-f_FRF*sin(FthetaWRF),FyWRF,f_FRF*cos(FthetaWRF),"B_FWHSF");
    Vector3D r_FWHSRF = sys.Position_Vector("O","O_FWHSRF")+fFWHSRF;
    Vector3D t1_FWHSRF= sys.diff ( r_FWHSRF , FthetaWRF);
    Vector3D t2_FWHSRF= sys.diff ( r_FWHSRF , FyWRF);
    Vector3D n_FWHSRF = t1_FWHSRF^t2_FWHSRF;

    Vector3D f_FRAILRF = *sys.new_Vector3D("f_FRAILRF",FxRRF,rR*sin(FthetaRRF),rR*cos(FthetaRRF),"B_RAIL");
    Vector3D r_FRAILRF = sys.Position_Vector("O","P_RailR")+f_FRAILRF;
    Vector3D t1_FRAILRF = sys.diff ( r_FRAILRF , FxRRF);
    Vector3D t2_FRAILRF = sys.diff ( r_FRAILRF , FthetaRRF);
    Vector3D n_FRAILRF = t1_FRAILRF^t2_FRAILRF;

    // FRONT LEFT WHEEL and RAIL
    ex f_FLF = FyWLF*((Rw-rw)/Lw)-((Rw+rw)/2.0);
    Vector3D OPFWHF_OFWHSLF = *sys.new_Vector3D("OPFWHF_OFWHSLF",0,L_OBOG_OAXBy,0,"B_FWHSF");
    Point * O_FWHSLF  = sys.new_Point("O_FWHSLF","O_FWHSF",&OPFWHF_OFWHSLF);
    Vector3D fFWHSLF = *sys.new_Vector3D("fFWHSLF",-f_FLF*sin(FthetaWLF),FyWLF,f_FLF*cos(FthetaWLF),"B_FWHSF");
    Vector3D r_FWHSLF = sys.Position_Vector("O","O_FWHSLF")+fFWHSLF;
    Vector3D t1_FWHSLF= sys.diff ( r_FWHSLF , FthetaWLF);
    Vector3D t2_FWHSLF= sys.diff ( r_FWHSLF , FyWLF);
    Vector3D n_FWHSLF = t1_FWHSLF^t2_FWHSLF;

    Vector3D f_FRAILLF = *sys.new_Vector3D("r_FRAILLF",FxRLF,rR*sin(FthetaRLF),rR*cos(FthetaRLF),"B_RAIL");
    Vector3D r_FRAILLF = sys.Position_Vector("O","P_RailL")+f_FRAILLF;
    Vector3D t1_FRAILLF = sys.diff ( r_FRAILLF , FxRLF);
    Vector3D t2_FRAILLF = sys.diff ( r_FRAILLF , FthetaRLF);
    Vector3D n_FRAILLF = t1_FRAILLF^t2_FRAILLF;  
    
    // REAR RIGTH WHEEL and RAIL
    ex f_FRR = -FyWRR*((Rw-rw)/Lw)-((Rw+rw)/2.0);
    Vector3D OPFWHR_OFWHSRR = *sys.new_Vector3D("OPFWHR_OFWHSRR",0,-L_OBOG_OAXBy,0,"B_FWHSR");
    Point * O_FWHSRR  = sys.new_Point("O_FWHSRR","O_FWHSR",&OPFWHR_OFWHSRR);
    Vector3D fFWHSRR = *sys.new_Vector3D("fFWHSRR",-f_FRR*sin(FthetaWRR),FyWRR,f_FRR*cos(FthetaWRR),"B_FWHSR");
    Vector3D r_FWHSRR = sys.Position_Vector("O","O_FWHSRR")+fFWHSRR;
    Vector3D t1_FWHSRR= sys.diff ( r_FWHSRR , FthetaWRR);
    Vector3D t2_FWHSRR= sys.diff ( r_FWHSRR , FyWRR);
    Vector3D n_FWHSRR = t1_FWHSRR^t2_FWHSRR;

    Vector3D f_FRAILRR = *sys.new_Vector3D("r_FRAILRR",FxRRR,rR*sin(FthetaRRR),rR*cos(FthetaRRR),"B_RAIL");
    Vector3D r_FRAILRR = sys.Position_Vector("O","P_RailR")+f_FRAILRR;
    Vector3D t1_FRAILRR = sys.diff ( r_FRAILRR , FxRRR);
    Vector3D t2_FRAILRR = sys.diff ( r_FRAILRR , FthetaRRR);
    Vector3D n_FRAILRR = t1_FRAILRR^t2_FRAILRR;

 
 
    // REAR LEFT WHEEL and RAIL
    ex f_FLR = FyWLR*((Rw-rw)/Lw)-((Rw+rw)/2.0);
    Vector3D OPFWHR_OFWHSLR = *sys.new_Vector3D("OPFWHR_OFWHSLR",0,L_OBOG_OAXBy,0,"B_FWHSR");
    Point * O_FWHSLR  = sys.new_Point("O_FWHSLR","O_FWHSR",&OPFWHR_OFWHSLR);
    Vector3D fFWHSLR = *sys.new_Vector3D("fFWHSLR",-f_FLR*sin(FthetaWLR),FyWLR,f_FLR*cos(FthetaWLR),"B_FWHSR");
    Vector3D r_FWHSLR = sys.Position_Vector("O","O_FWHSLR")+fFWHSLR;
    Vector3D t1_FWHSLR= sys.diff ( r_FWHSLR , FthetaWLR);
    Vector3D t2_FWHSLR= sys.diff ( r_FWHSLR , FyWLR);
    Vector3D n_FWHSLR = t1_FWHSLR^t2_FWHSLR;

    Vector3D f_FRAILLR = *sys.new_Vector3D("r_FRAILLR",FxRLR,rR*sin(FthetaRLR),rR*cos(FthetaRLR),"B_RAIL");
    Vector3D r_FRAILLR = sys.Position_Vector("O","P_RailL")+f_FRAILLR;
    Vector3D t1_FRAILLR = sys.diff ( r_FRAILLR , FxRLR);
    Vector3D t2_FRAILLR = sys.diff ( r_FRAILLR , FthetaRLR);
    Vector3D n_FRAILLR = t1_FRAILLR^t2_FRAILLR; 

// ************************************************************************************************


    cout << "Kinematic Equations" << endl;
    
    Matrix Phi(40,1);


    // REAR BOGIE
    //FRONT WHEELSET 
    Phi(0,0) = (r_RWHSRF-r_RRAILRF)(0,0);
    Phi(1,0) = (r_RWHSRF-r_RRAILRF)(1,0);
    Phi(2,0) = (r_RWHSRF-r_RRAILRF)(2,0);

    Phi(3,0) = (r_RWHSLF-r_RRAILLF)(0,0);
    Phi(4,0) = (r_RWHSLF-r_RRAILLF)(1,0);
    Phi(5,0) = (r_RWHSLF-r_RRAILLF)(2,0);

    Phi(6,0) = n_RRAILRF*t1_RWHSRF;
    Phi(7,0) = n_RRAILRF*t2_RWHSRF;

    Phi(8,0) = n_RRAILLF*t1_RWHSLF;
    Phi(9,0) = n_RRAILLF*t2_RWHSLF;

    //REAR WHEELSET 
    Phi(10,0) = (r_RWHSRR-r_RRAILRR)(0,0);
    Phi(11,0) = (r_RWHSRR-r_RRAILRR)(1,0);
    Phi(12,0) = (r_RWHSRR-r_RRAILRR)(2,0);
    
    Phi(13,0) = (r_RWHSLR-r_RRAILLR)(0,0);
    Phi(14,0) = (r_RWHSLR-r_RRAILLR)(1,0);
    Phi(15,0) = (r_RWHSLR-r_RRAILLR)(2,0);
    
    Phi(16,0) = n_RRAILRR*t1_RWHSRR;
    Phi(17,0) = n_RRAILRR*t2_RWHSRR;
    
    Phi(18,0) = n_RRAILLR*t1_RWHSLR;
    Phi(19,0) = n_RRAILLR*t2_RWHSLR;
    
    //FRONT BOGIE
    //FRONT WHEELSET 
    Phi(20,0) = (r_FWHSRF-r_FRAILRF)(0,0);
    Phi(21,0) = (r_FWHSRF-r_FRAILRF)(1,0);
    Phi(22,0) = (r_FWHSRF-r_FRAILRF)(2,0);

    Phi(23,0) = (r_FWHSLF-r_FRAILLF)(0,0);
    Phi(24,0) = (r_FWHSLF-r_FRAILLF)(1,0);
    Phi(25,0) = (r_FWHSLF-r_FRAILLF)(2,0);

    Phi(26,0) = n_FRAILRF*t1_FWHSRF;
    Phi(27,0) = n_FRAILRF*t2_FWHSRF;

    Phi(28,0) = n_FRAILLF*t1_FWHSLF;
    Phi(29,0) = n_FRAILLF*t2_FWHSLF;

    //REAR WHEELSET 
    Phi(30,0) = (r_FWHSRR-r_FRAILRR)(0,0);
    Phi(31,0) = (r_FWHSRR-r_FRAILRR)(1,0);
    Phi(32,0) = (r_FWHSRR-r_FRAILRR)(2,0);
    
    Phi(33,0) = (r_FWHSLR-r_FRAILLR)(0,0);
    Phi(34,0) = (r_FWHSLR-r_FRAILLR)(1,0);
    Phi(35,0) = (r_FWHSLR-r_FRAILLR)(2,0);
    
    Phi(36,0) = n_FRAILRR*t1_FWHSRR;
    Phi(37,0) = n_FRAILRR*t2_FWHSRR;
    
    Phi(38,0) = n_FRAILLR*t1_FWHSLR;
    Phi(39,0) = n_FRAILLR*t2_FWHSLR; 
    


 
    Point * Pcontact_RLF   = sys.new_Point("Pcontact_RLF","O",&r_RWHSLF);
    Point * Pcontact_RRF   = sys.new_Point("Pcontact_RRF","O",&r_RWHSRF);  
    Point * Pcontact_RLR   = sys.new_Point("Pcontact_RLR","O",&r_RWHSLR);
    Point * Pcontact_RRR   = sys.new_Point("Pcontact_RRR","O",&r_RWHSRR);   
    
    Point * Pcontact_FLF   = sys.new_Point("Pcontact_FLF","O",&r_FWHSLF);
    Point * Pcontact_FRF   = sys.new_Point("Pcontact_FRF","O",&r_FWHSRF);  
    Point * Pcontact_FLR   = sys.new_Point("Pcontact_FLR","O",&r_FWHSLR);
    Point * Pcontact_FRR   = sys.new_Point("Pcontact_FRR","O",&r_FWHSRR);  
    
    

    Vector3D vel_Pc_RLF = sys.Velocity_Vector (Frame_abs , Pcontact_RLF, RWHSF);
    Vector3D vel_Pc_RRF = sys.Velocity_Vector (Frame_abs , Pcontact_RRF, RWHSF);
    Vector3D vel_Pc_RLR = sys.Velocity_Vector (Frame_abs , Pcontact_RLR, RWHSR);
    Vector3D vel_Pc_RRR = sys.Velocity_Vector (Frame_abs , Pcontact_RRR, RWHSR);
	
    Vector3D vel_Pc_FLF = sys.Velocity_Vector (Frame_abs , Pcontact_FLF, FWHSF);
    Vector3D vel_Pc_FRF = sys.Velocity_Vector (Frame_abs , Pcontact_FRF, FWHSF);
    Vector3D vel_Pc_FLR = sys.Velocity_Vector (Frame_abs , Pcontact_FLR, FWHSR);
    Vector3D vel_Pc_FRR = sys.Velocity_Vector (Frame_abs , Pcontact_FRR,FWHSR);	
	
	
    ex mod_vel_Pc_RLF = sqrt( vel_Pc_RLF * vel_Pc_RLF );
    ex mod_vel_Pc_RRF = sqrt( vel_Pc_RRF * vel_Pc_RRF );
    ex mod_vel_Pc_RLR = sqrt( vel_Pc_RLR * vel_Pc_RLR );
    ex mod_vel_Pc_RRR = sqrt( vel_Pc_RRR * vel_Pc_RRR );


    ex mod_vel_Pc_FLF = sqrt( vel_Pc_FLF * vel_Pc_FLF );
    ex mod_vel_Pc_FRF = sqrt( vel_Pc_FRF * vel_Pc_FRF );
    ex mod_vel_Pc_FLR = sqrt( vel_Pc_FLR * vel_Pc_FLR );
    ex mod_vel_Pc_FRR = sqrt( vel_Pc_FRR * vel_Pc_FRR );


 
    Vector3D F_FricRRF= (-mu_V_RRF * N_RRF) * vel_Pc_RRF;
    Vector3D F_FricRLF= (-mu_V_RLF * N_RLF) * vel_Pc_RLF;
    Vector3D F_FricRRR= (-mu_V_RRR * N_RRR) * vel_Pc_RRR;
    Vector3D F_FricRLR= (-mu_V_RLR * N_RLR) * vel_Pc_RLR;
    
     
    Vector3D F_FricFRF= (-mu_V_FRF * N_FRF) * vel_Pc_FRF;
    Vector3D F_FricFLF= (-mu_V_FLF * N_FLF) * vel_Pc_FLF;
    Vector3D F_FricFRR= (-mu_V_FRR * N_FRR) * vel_Pc_FRR;
    Vector3D F_FricFLR= (-mu_V_FLR * N_FLR) * vel_Pc_FLR;
    
    
    Vector3D M_FricRF  = *sys.new_Vector3D("M_FricRF",0,0,0, "B_RWHSF");
    Vector3D M_FricRR  = *sys.new_Vector3D("M_FricRR",0,0,0, "B_RWHSR");
    
    Vector3D M_FricFF  = *sys.new_Vector3D("M_FricFF",0,0,0, "B_FWHSF");
    Vector3D M_FricFR  = *sys.new_Vector3D("M_FricFR",0,0,0, "B_FWHSR");
	
    Wrench3D * FrictionRLF = sys.new_Wrench3D ( "FrictionRLF", F_FricRLF, M_FricRF , Pcontact_RLF, RWHSF , "Constitutive") ;
    Wrench3D * FrictionRRF = sys.new_Wrench3D ( "FrictionRRF", F_FricRRF, M_FricRF , Pcontact_RRF, RWHSF , "Constitutive") ;	
    Wrench3D * FrictionRLR = sys.new_Wrench3D ( "FrictionRLR", F_FricRLR, M_FricRR , Pcontact_RLR, RWHSR , "Constitutive") ;
    Wrench3D * FrictionRRR = sys.new_Wrench3D ( "FrictionRRR", F_FricRRR, M_FricRR , Pcontact_RRR, RWHSR , "Constitutive") ;	

    Wrench3D * FrictionFLF = sys.new_Wrench3D ( "FrictionFLF", F_FricFLF, M_FricFF , Pcontact_FLF, FWHSF , "Constitutive") ;
    Wrench3D * FrictionFRF = sys.new_Wrench3D ( "FrictionFRF", F_FricFRF, M_FricFF , Pcontact_FRF, FWHSF , "Constitutive") ;	
    Wrench3D * FrictionFLR = sys.new_Wrench3D ( "FrictionFLR", F_FricFLR, M_FricFR , Pcontact_FLR, FWHSR , "Constitutive") ;
    Wrench3D * FrictionFRR = sys.new_Wrench3D ( "FrictionFRR", F_FricFRR, M_FricFR , Pcontact_FRR, FWHSR , "Constitutive") ;











    /*
     * coord = 41
     * Phi = 20
     * dPhiNH = 0
     * dPhi = Phi +   dPhiNH = 20 ==>>  20  lambda
     * coord_indep = coord - Phi = 41 - 20 = 21
     * vel_indep = coord - ( Phi + dPhiNH) = 41 - 20 = 21
    */
    //~ coord_indep_init = //44
      //~ xWAG-0.0, yWAG-0.0,zWAG-0.705,aWAG-0.0,bWAG+0.0011,cWAG-0.0
    //~ , cRSLD-0.0
    //~ , cFSLD-0.0
    //~ , zRBOG+0.1272, aRBOG-0.0 , bRBOG-0.0011 
    //~ , zFBOG+0.1272, aFBOG-0.0 , bFBOG-0.0011   
    //~ , xRMOTF-0.0, yRMOTF-0.0, zRMOTF+0.022,bRMOTF+0.0044 
    //~ , xRMOTR-0.0, yRMOTR-0.0, zRMOTR+0.022,bRMOTR+0.0044
    //~ , bRROTF
    //~ , bRROTR
    //~ ,/*zRWHSF-0.0514 ,aRWHSF-0.0,*/ bRWHSF-0.0 
    //~ ,/*zRWHSR-0.0514 ,aRWHSR-0.0,*/ bRWHSR-0.0
    //~ ,/*zFWHSF-0.0514 ,aFWHSF-0.0,*/ bFWHSF-0.0 
    //~ ,/*zFWHSR-0.0514 ,aFWHSR-0.0,*/ bFWHSR-0.0
    //~ , bRAXBFL-0.0
    //~ , bRAXBFR-0.0
    //~ , bRAXBRL+0.0
    //~ , bRAXBRR+0.0
    //~ , bFAXBFL-0.0
    //~ , bFAXBFR-0.0
    //~ , bFAXBRL-0.0
    //~ , bFAXBRR-0.0 
    //~ ;
    //~ 
    //~ vel_indep_init	=  //44
      //~ *dxWAG-0.0, *dyWAG-0.0,*dzWAG-0.0,*daWAG-0.0,*dbWAG-0.0,*dcWAG-0.0
    //~ , *dcRSLD-0.0
    //~ , *dcFSLD-0.0
    //~ , *dzRBOG-0.0, *daRBOG-0.0 , *dbRBOG-0.0
    //~ , *dzFBOG-0.0, *daFBOG-0.0 , *dbFBOG-0.0  
    //~ , *dxRMOTF-5.55e-5, *dyRMOTF-0.0, *dzRMOTF-0.0314,*dbRMOTF-0.0 
    //~ , *dxRMOTR-5.55e-5, *dyRMOTR-0.0, *dzRMOTR-0.0314,*dbRMOTR-0.0 
    //~ , *dbRROTF
    //~ , *dbRROTR
    //~ ,/* *dzRWHSF-0.0514 ,*daRWHSF-0.0,*/ *dbRWHSF-0.0 
    //~ ,/* *dzRWHSR-0.0514 ,*daRWHSR-0.0,*/ *dbRWHSR-0.0
    //~ ,/* *dzFWHSF-0.0514 ,*daFWHSF-0.0,*/ *dbFWHSF-0.0 
    //~ ,/* *dzFWHSR-0.0514 ,*daFWHSR-0.0,*/ *dbFWHSR-0.0
    //~ , *dbRAXBFL-0.0123
    //~ , *dbRAXBFR-0.0123
    //~ , *dbRAXBRL+0.0123
    //~ , *dbRAXBRR+0.0123
    //~ , *dbFAXBFL-0.0
    //~ , *dbFAXBFR-0.0
    //~ , *dbFAXBRL-0.0
    //~ , *dbFAXBRR-0.0   
    //~ ;

// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************

    cout << "Dynamic Equations" << endl;

    Matrix Dynamic_Equations = sys.GenForceSys("ALL");


// ************************************************************************************************
// 	Output Vector
// ************************************************************************************************

    cout << "Output Vector" << endl;


    Matrix Output(20,1);
    Output(0,0)=mod_vel_Pc_RRF;
    Output(1,0)=mod_vel_Pc_RLF;
    Output(2,0)=mod_vel_Pc_RRR;
    Output(3,0)=mod_vel_Pc_RLR;

    Output(4,0)=mod_vel_Pc_FRF;
    Output(5,0)=mod_vel_Pc_FLF;
    Output(6,0)=mod_vel_Pc_FRR;
    Output(7,0)=mod_vel_Pc_FLR;
    
    Output(8,0) =sqrt(lambda1*lambda1   + lambda2*lambda2   + lambda3*lambda3);
    Output(9,0) =sqrt(lambda4*lambda4   + lambda5*lambda5   + lambda6*lambda6);
    Output(10,0)=sqrt(lambda11*lambda11 + lambda12*lambda12 + lambda13*lambda13);
    Output(11,0)=sqrt(lambda14*lambda14 + lambda15*lambda15 + lambda16*lambda16);
     
    Output(12,0)=sqrt(lambda21*lambda21 + lambda22*lambda22 + lambda23*lambda23);
    Output(13,0)=sqrt(lambda24*lambda24 + lambda25*lambda25 + lambda26*lambda26);
    Output(14,0)=sqrt(lambda31*lambda31 + lambda32*lambda32 + lambda33*lambda33);
    Output(15,0)=sqrt(lambda34*lambda34 + lambda35*lambda35 + lambda36*lambda36);   
    
    Output(16,0)=sqrt(fRWHSRF(0,0)*fRWHSRF(0,0)+fRWHSRF(1,0)*fRWHSRF(1,0)+fRWHSRF(2,0)*fRWHSRF(2,0));
    Output(17,0)=fRWHSRF(0,0);
    Output(18,0)=fRWHSRF(1,0);
    Output(19,0)=fRWHSRF(2,0);

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
    sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE);
    //~ sys.Matrix_Calculation(Phi,coord_indep_init , vel_indep_init , Dynamic_Equations, sys, METHOD, PROBLEM_TYPE,dPhiNH);

// ************************************************************************************************
// 	Export C code for Direct Simulation 
// ************************************************************************************************

    cout << "Export C code for Direct Simulation " << endl;

    sys.export_Dynamic_Simulation(sys, ORDER , MAPLE, PROBLEM_TYPE);
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

    	state = xWAG, bWAG;

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


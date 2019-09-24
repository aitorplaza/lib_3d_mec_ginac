


//*****************************************************************************************************************
// 	THIS FILE HAS BEEN GENERATED AUTOMATICALLY BY THE MATLAB SCRIPT DH_generated_main_symbolic.m            
//*****************************************************************************************************************



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
cout << "***********************************************************" << endl;
cout << "*  Denavit-Hartenberg Serial Chain with 100 solids.       *" << endl;
cout << "***********************************************************" << endl;
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
//	TIME DEFINITION
// ************************************************************************************************
        symbol_numeric t=sys.get_Time_Symbol ( );

// ************************************************************************************************
//	Coordinate definition
// ************************************************************************************************

	// Rotation angles from root to leaf
	symbol_numeric q1 = *sys.new_Coordinate("q1","dq1","ddq1", 0.0 , 0.0 , 0.0);
	symbol_numeric q2 = *sys.new_Coordinate("q2","dq2","ddq2", 0.0 , 0.0 , 0.0);
	symbol_numeric q3 = *sys.new_Coordinate("q3","dq3","ddq3", 0.0 , 0.0 , 0.0);
	symbol_numeric q4 = *sys.new_Coordinate("q4","dq4","ddq4", 0.0 , 0.0 , 0.0);
	symbol_numeric q5 = *sys.new_Coordinate("q5","dq5","ddq5", 0.0 , 0.0 , 0.0);
	symbol_numeric q6 = *sys.new_Coordinate("q6","dq6","ddq6", 0.0 , 0.0 , 0.0);
	symbol_numeric q7 = *sys.new_Coordinate("q7","dq7","ddq7", 0.0 , 0.0 , 0.0);
	symbol_numeric q8 = *sys.new_Coordinate("q8","dq8","ddq8", 0.0 , 0.0 , 0.0);
	symbol_numeric q9 = *sys.new_Coordinate("q9","dq9","ddq9", 0.0 , 0.0 , 0.0);
	symbol_numeric q10 = *sys.new_Coordinate("q10","dq10","ddq10", 0.0 , 0.0 , 0.0);
	symbol_numeric q11 = *sys.new_Coordinate("q11","dq11","ddq11", 0.0 , 0.0 , 0.0);
	symbol_numeric q12 = *sys.new_Coordinate("q12","dq12","ddq12", 0.0 , 0.0 , 0.0);
	symbol_numeric q13 = *sys.new_Coordinate("q13","dq13","ddq13", 0.0 , 0.0 , 0.0);
	symbol_numeric q14 = *sys.new_Coordinate("q14","dq14","ddq14", 0.0 , 0.0 , 0.0);
	symbol_numeric q15 = *sys.new_Coordinate("q15","dq15","ddq15", 0.0 , 0.0 , 0.0);
	symbol_numeric q16 = *sys.new_Coordinate("q16","dq16","ddq16", 0.0 , 0.0 , 0.0);
	symbol_numeric q17 = *sys.new_Coordinate("q17","dq17","ddq17", 0.0 , 0.0 , 0.0);
	symbol_numeric q18 = *sys.new_Coordinate("q18","dq18","ddq18", 0.0 , 0.0 , 0.0);
	symbol_numeric q19 = *sys.new_Coordinate("q19","dq19","ddq19", 0.0 , 0.0 , 0.0);
	symbol_numeric q20 = *sys.new_Coordinate("q20","dq20","ddq20", 0.0 , 0.0 , 0.0);
	symbol_numeric q21 = *sys.new_Coordinate("q21","dq21","ddq21", 0.0 , 0.0 , 0.0);
	symbol_numeric q22 = *sys.new_Coordinate("q22","dq22","ddq22", 0.0 , 0.0 , 0.0);
	symbol_numeric q23 = *sys.new_Coordinate("q23","dq23","ddq23", 0.0 , 0.0 , 0.0);
	symbol_numeric q24 = *sys.new_Coordinate("q24","dq24","ddq24", 0.0 , 0.0 , 0.0);
	symbol_numeric q25 = *sys.new_Coordinate("q25","dq25","ddq25", 0.0 , 0.0 , 0.0);
	symbol_numeric q26 = *sys.new_Coordinate("q26","dq26","ddq26", 0.0 , 0.0 , 0.0);
	symbol_numeric q27 = *sys.new_Coordinate("q27","dq27","ddq27", 0.0 , 0.0 , 0.0);
	symbol_numeric q28 = *sys.new_Coordinate("q28","dq28","ddq28", 0.0 , 0.0 , 0.0);
	symbol_numeric q29 = *sys.new_Coordinate("q29","dq29","ddq29", 0.0 , 0.0 , 0.0);
	symbol_numeric q30 = *sys.new_Coordinate("q30","dq30","ddq30", 0.0 , 0.0 , 0.0);
	symbol_numeric q31 = *sys.new_Coordinate("q31","dq31","ddq31", 0.0 , 0.0 , 0.0);
	symbol_numeric q32 = *sys.new_Coordinate("q32","dq32","ddq32", 0.0 , 0.0 , 0.0);
	symbol_numeric q33 = *sys.new_Coordinate("q33","dq33","ddq33", 0.0 , 0.0 , 0.0);
	symbol_numeric q34 = *sys.new_Coordinate("q34","dq34","ddq34", 0.0 , 0.0 , 0.0);
	symbol_numeric q35 = *sys.new_Coordinate("q35","dq35","ddq35", 0.0 , 0.0 , 0.0);
	symbol_numeric q36 = *sys.new_Coordinate("q36","dq36","ddq36", 0.0 , 0.0 , 0.0);
	symbol_numeric q37 = *sys.new_Coordinate("q37","dq37","ddq37", 0.0 , 0.0 , 0.0);
	symbol_numeric q38 = *sys.new_Coordinate("q38","dq38","ddq38", 0.0 , 0.0 , 0.0);
	symbol_numeric q39 = *sys.new_Coordinate("q39","dq39","ddq39", 0.0 , 0.0 , 0.0);
	symbol_numeric q40 = *sys.new_Coordinate("q40","dq40","ddq40", 0.0 , 0.0 , 0.0);
	symbol_numeric q41 = *sys.new_Coordinate("q41","dq41","ddq41", 0.0 , 0.0 , 0.0);
	symbol_numeric q42 = *sys.new_Coordinate("q42","dq42","ddq42", 0.0 , 0.0 , 0.0);
	symbol_numeric q43 = *sys.new_Coordinate("q43","dq43","ddq43", 0.0 , 0.0 , 0.0);
	symbol_numeric q44 = *sys.new_Coordinate("q44","dq44","ddq44", 0.0 , 0.0 , 0.0);
	symbol_numeric q45 = *sys.new_Coordinate("q45","dq45","ddq45", 0.0 , 0.0 , 0.0);
	symbol_numeric q46 = *sys.new_Coordinate("q46","dq46","ddq46", 0.0 , 0.0 , 0.0);
	symbol_numeric q47 = *sys.new_Coordinate("q47","dq47","ddq47", 0.0 , 0.0 , 0.0);
	symbol_numeric q48 = *sys.new_Coordinate("q48","dq48","ddq48", 0.0 , 0.0 , 0.0);
	symbol_numeric q49 = *sys.new_Coordinate("q49","dq49","ddq49", 0.0 , 0.0 , 0.0);
	symbol_numeric q50 = *sys.new_Coordinate("q50","dq50","ddq50", 0.0 , 0.0 , 0.0);
	symbol_numeric q51 = *sys.new_Coordinate("q51","dq51","ddq51", 0.0 , 0.0 , 0.0);
	symbol_numeric q52 = *sys.new_Coordinate("q52","dq52","ddq52", 0.0 , 0.0 , 0.0);
	symbol_numeric q53 = *sys.new_Coordinate("q53","dq53","ddq53", 0.0 , 0.0 , 0.0);
	symbol_numeric q54 = *sys.new_Coordinate("q54","dq54","ddq54", 0.0 , 0.0 , 0.0);
	symbol_numeric q55 = *sys.new_Coordinate("q55","dq55","ddq55", 0.0 , 0.0 , 0.0);
	symbol_numeric q56 = *sys.new_Coordinate("q56","dq56","ddq56", 0.0 , 0.0 , 0.0);
	symbol_numeric q57 = *sys.new_Coordinate("q57","dq57","ddq57", 0.0 , 0.0 , 0.0);
	symbol_numeric q58 = *sys.new_Coordinate("q58","dq58","ddq58", 0.0 , 0.0 , 0.0);
	symbol_numeric q59 = *sys.new_Coordinate("q59","dq59","ddq59", 0.0 , 0.0 , 0.0);
	symbol_numeric q60 = *sys.new_Coordinate("q60","dq60","ddq60", 0.0 , 0.0 , 0.0);
	symbol_numeric q61 = *sys.new_Coordinate("q61","dq61","ddq61", 0.0 , 0.0 , 0.0);
	symbol_numeric q62 = *sys.new_Coordinate("q62","dq62","ddq62", 0.0 , 0.0 , 0.0);
	symbol_numeric q63 = *sys.new_Coordinate("q63","dq63","ddq63", 0.0 , 0.0 , 0.0);
	symbol_numeric q64 = *sys.new_Coordinate("q64","dq64","ddq64", 0.0 , 0.0 , 0.0);
	symbol_numeric q65 = *sys.new_Coordinate("q65","dq65","ddq65", 0.0 , 0.0 , 0.0);
	symbol_numeric q66 = *sys.new_Coordinate("q66","dq66","ddq66", 0.0 , 0.0 , 0.0);
	symbol_numeric q67 = *sys.new_Coordinate("q67","dq67","ddq67", 0.0 , 0.0 , 0.0);
	symbol_numeric q68 = *sys.new_Coordinate("q68","dq68","ddq68", 0.0 , 0.0 , 0.0);
	symbol_numeric q69 = *sys.new_Coordinate("q69","dq69","ddq69", 0.0 , 0.0 , 0.0);
	symbol_numeric q70 = *sys.new_Coordinate("q70","dq70","ddq70", 0.0 , 0.0 , 0.0);
	symbol_numeric q71 = *sys.new_Coordinate("q71","dq71","ddq71", 0.0 , 0.0 , 0.0);
	symbol_numeric q72 = *sys.new_Coordinate("q72","dq72","ddq72", 0.0 , 0.0 , 0.0);
	symbol_numeric q73 = *sys.new_Coordinate("q73","dq73","ddq73", 0.0 , 0.0 , 0.0);
	symbol_numeric q74 = *sys.new_Coordinate("q74","dq74","ddq74", 0.0 , 0.0 , 0.0);
	symbol_numeric q75 = *sys.new_Coordinate("q75","dq75","ddq75", 0.0 , 0.0 , 0.0);
	symbol_numeric q76 = *sys.new_Coordinate("q76","dq76","ddq76", 0.0 , 0.0 , 0.0);
	symbol_numeric q77 = *sys.new_Coordinate("q77","dq77","ddq77", 0.0 , 0.0 , 0.0);
	symbol_numeric q78 = *sys.new_Coordinate("q78","dq78","ddq78", 0.0 , 0.0 , 0.0);
	symbol_numeric q79 = *sys.new_Coordinate("q79","dq79","ddq79", 0.0 , 0.0 , 0.0);
	symbol_numeric q80 = *sys.new_Coordinate("q80","dq80","ddq80", 0.0 , 0.0 , 0.0);
	symbol_numeric q81 = *sys.new_Coordinate("q81","dq81","ddq81", 0.0 , 0.0 , 0.0);
	symbol_numeric q82 = *sys.new_Coordinate("q82","dq82","ddq82", 0.0 , 0.0 , 0.0);
	symbol_numeric q83 = *sys.new_Coordinate("q83","dq83","ddq83", 0.0 , 0.0 , 0.0);
	symbol_numeric q84 = *sys.new_Coordinate("q84","dq84","ddq84", 0.0 , 0.0 , 0.0);
	symbol_numeric q85 = *sys.new_Coordinate("q85","dq85","ddq85", 0.0 , 0.0 , 0.0);
	symbol_numeric q86 = *sys.new_Coordinate("q86","dq86","ddq86", 0.0 , 0.0 , 0.0);
	symbol_numeric q87 = *sys.new_Coordinate("q87","dq87","ddq87", 0.0 , 0.0 , 0.0);
	symbol_numeric q88 = *sys.new_Coordinate("q88","dq88","ddq88", 0.0 , 0.0 , 0.0);
	symbol_numeric q89 = *sys.new_Coordinate("q89","dq89","ddq89", 0.0 , 0.0 , 0.0);
	symbol_numeric q90 = *sys.new_Coordinate("q90","dq90","ddq90", 0.0 , 0.0 , 0.0);
	symbol_numeric q91 = *sys.new_Coordinate("q91","dq91","ddq91", 0.0 , 0.0 , 0.0);
	symbol_numeric q92 = *sys.new_Coordinate("q92","dq92","ddq92", 0.0 , 0.0 , 0.0);
	symbol_numeric q93 = *sys.new_Coordinate("q93","dq93","ddq93", 0.0 , 0.0 , 0.0);
	symbol_numeric q94 = *sys.new_Coordinate("q94","dq94","ddq94", 0.0 , 0.0 , 0.0);
	symbol_numeric q95 = *sys.new_Coordinate("q95","dq95","ddq95", 0.0 , 0.0 , 0.0);
	symbol_numeric q96 = *sys.new_Coordinate("q96","dq96","ddq96", 0.0 , 0.0 , 0.0);
	symbol_numeric q97 = *sys.new_Coordinate("q97","dq97","ddq97", 0.0 , 0.0 , 0.0);
	symbol_numeric q98 = *sys.new_Coordinate("q98","dq98","ddq98", 0.0 , 0.0 , 0.0);
	symbol_numeric q99 = *sys.new_Coordinate("q99","dq99","ddq99", 0.0 , 0.0 , 0.0);
	symbol_numeric q100 = *sys.new_Coordinate("q100","dq100","ddq100", 0.0 , 0.0 , 0.0);

	// Velocities
	symbol_numeric *dq1=sys.get_Velocity("dq1");
	symbol_numeric *dq2=sys.get_Velocity("dq2");
	symbol_numeric *dq3=sys.get_Velocity("dq3");
	symbol_numeric *dq4=sys.get_Velocity("dq4");
	symbol_numeric *dq5=sys.get_Velocity("dq5");
	symbol_numeric *dq6=sys.get_Velocity("dq6");
	symbol_numeric *dq7=sys.get_Velocity("dq7");
	symbol_numeric *dq8=sys.get_Velocity("dq8");
	symbol_numeric *dq9=sys.get_Velocity("dq9");
	symbol_numeric *dq10=sys.get_Velocity("dq10");
	symbol_numeric *dq11=sys.get_Velocity("dq11");
	symbol_numeric *dq12=sys.get_Velocity("dq12");
	symbol_numeric *dq13=sys.get_Velocity("dq13");
	symbol_numeric *dq14=sys.get_Velocity("dq14");
	symbol_numeric *dq15=sys.get_Velocity("dq15");
	symbol_numeric *dq16=sys.get_Velocity("dq16");
	symbol_numeric *dq17=sys.get_Velocity("dq17");
	symbol_numeric *dq18=sys.get_Velocity("dq18");
	symbol_numeric *dq19=sys.get_Velocity("dq19");
	symbol_numeric *dq20=sys.get_Velocity("dq20");
	symbol_numeric *dq21=sys.get_Velocity("dq21");
	symbol_numeric *dq22=sys.get_Velocity("dq22");
	symbol_numeric *dq23=sys.get_Velocity("dq23");
	symbol_numeric *dq24=sys.get_Velocity("dq24");
	symbol_numeric *dq25=sys.get_Velocity("dq25");
	symbol_numeric *dq26=sys.get_Velocity("dq26");
	symbol_numeric *dq27=sys.get_Velocity("dq27");
	symbol_numeric *dq28=sys.get_Velocity("dq28");
	symbol_numeric *dq29=sys.get_Velocity("dq29");
	symbol_numeric *dq30=sys.get_Velocity("dq30");
	symbol_numeric *dq31=sys.get_Velocity("dq31");
	symbol_numeric *dq32=sys.get_Velocity("dq32");
	symbol_numeric *dq33=sys.get_Velocity("dq33");
	symbol_numeric *dq34=sys.get_Velocity("dq34");
	symbol_numeric *dq35=sys.get_Velocity("dq35");
	symbol_numeric *dq36=sys.get_Velocity("dq36");
	symbol_numeric *dq37=sys.get_Velocity("dq37");
	symbol_numeric *dq38=sys.get_Velocity("dq38");
	symbol_numeric *dq39=sys.get_Velocity("dq39");
	symbol_numeric *dq40=sys.get_Velocity("dq40");
	symbol_numeric *dq41=sys.get_Velocity("dq41");
	symbol_numeric *dq42=sys.get_Velocity("dq42");
	symbol_numeric *dq43=sys.get_Velocity("dq43");
	symbol_numeric *dq44=sys.get_Velocity("dq44");
	symbol_numeric *dq45=sys.get_Velocity("dq45");
	symbol_numeric *dq46=sys.get_Velocity("dq46");
	symbol_numeric *dq47=sys.get_Velocity("dq47");
	symbol_numeric *dq48=sys.get_Velocity("dq48");
	symbol_numeric *dq49=sys.get_Velocity("dq49");
	symbol_numeric *dq50=sys.get_Velocity("dq50");
	symbol_numeric *dq51=sys.get_Velocity("dq51");
	symbol_numeric *dq52=sys.get_Velocity("dq52");
	symbol_numeric *dq53=sys.get_Velocity("dq53");
	symbol_numeric *dq54=sys.get_Velocity("dq54");
	symbol_numeric *dq55=sys.get_Velocity("dq55");
	symbol_numeric *dq56=sys.get_Velocity("dq56");
	symbol_numeric *dq57=sys.get_Velocity("dq57");
	symbol_numeric *dq58=sys.get_Velocity("dq58");
	symbol_numeric *dq59=sys.get_Velocity("dq59");
	symbol_numeric *dq60=sys.get_Velocity("dq60");
	symbol_numeric *dq61=sys.get_Velocity("dq61");
	symbol_numeric *dq62=sys.get_Velocity("dq62");
	symbol_numeric *dq63=sys.get_Velocity("dq63");
	symbol_numeric *dq64=sys.get_Velocity("dq64");
	symbol_numeric *dq65=sys.get_Velocity("dq65");
	symbol_numeric *dq66=sys.get_Velocity("dq66");
	symbol_numeric *dq67=sys.get_Velocity("dq67");
	symbol_numeric *dq68=sys.get_Velocity("dq68");
	symbol_numeric *dq69=sys.get_Velocity("dq69");
	symbol_numeric *dq70=sys.get_Velocity("dq70");
	symbol_numeric *dq71=sys.get_Velocity("dq71");
	symbol_numeric *dq72=sys.get_Velocity("dq72");
	symbol_numeric *dq73=sys.get_Velocity("dq73");
	symbol_numeric *dq74=sys.get_Velocity("dq74");
	symbol_numeric *dq75=sys.get_Velocity("dq75");
	symbol_numeric *dq76=sys.get_Velocity("dq76");
	symbol_numeric *dq77=sys.get_Velocity("dq77");
	symbol_numeric *dq78=sys.get_Velocity("dq78");
	symbol_numeric *dq79=sys.get_Velocity("dq79");
	symbol_numeric *dq80=sys.get_Velocity("dq80");
	symbol_numeric *dq81=sys.get_Velocity("dq81");
	symbol_numeric *dq82=sys.get_Velocity("dq82");
	symbol_numeric *dq83=sys.get_Velocity("dq83");
	symbol_numeric *dq84=sys.get_Velocity("dq84");
	symbol_numeric *dq85=sys.get_Velocity("dq85");
	symbol_numeric *dq86=sys.get_Velocity("dq86");
	symbol_numeric *dq87=sys.get_Velocity("dq87");
	symbol_numeric *dq88=sys.get_Velocity("dq88");
	symbol_numeric *dq89=sys.get_Velocity("dq89");
	symbol_numeric *dq90=sys.get_Velocity("dq90");
	symbol_numeric *dq91=sys.get_Velocity("dq91");
	symbol_numeric *dq92=sys.get_Velocity("dq92");
	symbol_numeric *dq93=sys.get_Velocity("dq93");
	symbol_numeric *dq94=sys.get_Velocity("dq94");
	symbol_numeric *dq95=sys.get_Velocity("dq95");
	symbol_numeric *dq96=sys.get_Velocity("dq96");
	symbol_numeric *dq97=sys.get_Velocity("dq97");
	symbol_numeric *dq98=sys.get_Velocity("dq98");
	symbol_numeric *dq99=sys.get_Velocity("dq99");
	symbol_numeric *dq100=sys.get_Velocity("dq100");

	// Accelerations
	symbol_numeric *ddq1=sys.get_Acceleration("ddq1");
	symbol_numeric *ddq2=sys.get_Acceleration("ddq2");
	symbol_numeric *ddq3=sys.get_Acceleration("ddq3");
	symbol_numeric *ddq4=sys.get_Acceleration("ddq4");
	symbol_numeric *ddq5=sys.get_Acceleration("ddq5");
	symbol_numeric *ddq6=sys.get_Acceleration("ddq6");
	symbol_numeric *ddq7=sys.get_Acceleration("ddq7");
	symbol_numeric *ddq8=sys.get_Acceleration("ddq8");
	symbol_numeric *ddq9=sys.get_Acceleration("ddq9");
	symbol_numeric *ddq10=sys.get_Acceleration("ddq10");
	symbol_numeric *ddq11=sys.get_Acceleration("ddq11");
	symbol_numeric *ddq12=sys.get_Acceleration("ddq12");
	symbol_numeric *ddq13=sys.get_Acceleration("ddq13");
	symbol_numeric *ddq14=sys.get_Acceleration("ddq14");
	symbol_numeric *ddq15=sys.get_Acceleration("ddq15");
	symbol_numeric *ddq16=sys.get_Acceleration("ddq16");
	symbol_numeric *ddq17=sys.get_Acceleration("ddq17");
	symbol_numeric *ddq18=sys.get_Acceleration("ddq18");
	symbol_numeric *ddq19=sys.get_Acceleration("ddq19");
	symbol_numeric *ddq20=sys.get_Acceleration("ddq20");
	symbol_numeric *ddq21=sys.get_Acceleration("ddq21");
	symbol_numeric *ddq22=sys.get_Acceleration("ddq22");
	symbol_numeric *ddq23=sys.get_Acceleration("ddq23");
	symbol_numeric *ddq24=sys.get_Acceleration("ddq24");
	symbol_numeric *ddq25=sys.get_Acceleration("ddq25");
	symbol_numeric *ddq26=sys.get_Acceleration("ddq26");
	symbol_numeric *ddq27=sys.get_Acceleration("ddq27");
	symbol_numeric *ddq28=sys.get_Acceleration("ddq28");
	symbol_numeric *ddq29=sys.get_Acceleration("ddq29");
	symbol_numeric *ddq30=sys.get_Acceleration("ddq30");
	symbol_numeric *ddq31=sys.get_Acceleration("ddq31");
	symbol_numeric *ddq32=sys.get_Acceleration("ddq32");
	symbol_numeric *ddq33=sys.get_Acceleration("ddq33");
	symbol_numeric *ddq34=sys.get_Acceleration("ddq34");
	symbol_numeric *ddq35=sys.get_Acceleration("ddq35");
	symbol_numeric *ddq36=sys.get_Acceleration("ddq36");
	symbol_numeric *ddq37=sys.get_Acceleration("ddq37");
	symbol_numeric *ddq38=sys.get_Acceleration("ddq38");
	symbol_numeric *ddq39=sys.get_Acceleration("ddq39");
	symbol_numeric *ddq40=sys.get_Acceleration("ddq40");
	symbol_numeric *ddq41=sys.get_Acceleration("ddq41");
	symbol_numeric *ddq42=sys.get_Acceleration("ddq42");
	symbol_numeric *ddq43=sys.get_Acceleration("ddq43");
	symbol_numeric *ddq44=sys.get_Acceleration("ddq44");
	symbol_numeric *ddq45=sys.get_Acceleration("ddq45");
	symbol_numeric *ddq46=sys.get_Acceleration("ddq46");
	symbol_numeric *ddq47=sys.get_Acceleration("ddq47");
	symbol_numeric *ddq48=sys.get_Acceleration("ddq48");
	symbol_numeric *ddq49=sys.get_Acceleration("ddq49");
	symbol_numeric *ddq50=sys.get_Acceleration("ddq50");
	symbol_numeric *ddq51=sys.get_Acceleration("ddq51");
	symbol_numeric *ddq52=sys.get_Acceleration("ddq52");
	symbol_numeric *ddq53=sys.get_Acceleration("ddq53");
	symbol_numeric *ddq54=sys.get_Acceleration("ddq54");
	symbol_numeric *ddq55=sys.get_Acceleration("ddq55");
	symbol_numeric *ddq56=sys.get_Acceleration("ddq56");
	symbol_numeric *ddq57=sys.get_Acceleration("ddq57");
	symbol_numeric *ddq58=sys.get_Acceleration("ddq58");
	symbol_numeric *ddq59=sys.get_Acceleration("ddq59");
	symbol_numeric *ddq60=sys.get_Acceleration("ddq60");
	symbol_numeric *ddq61=sys.get_Acceleration("ddq61");
	symbol_numeric *ddq62=sys.get_Acceleration("ddq62");
	symbol_numeric *ddq63=sys.get_Acceleration("ddq63");
	symbol_numeric *ddq64=sys.get_Acceleration("ddq64");
	symbol_numeric *ddq65=sys.get_Acceleration("ddq65");
	symbol_numeric *ddq66=sys.get_Acceleration("ddq66");
	symbol_numeric *ddq67=sys.get_Acceleration("ddq67");
	symbol_numeric *ddq68=sys.get_Acceleration("ddq68");
	symbol_numeric *ddq69=sys.get_Acceleration("ddq69");
	symbol_numeric *ddq70=sys.get_Acceleration("ddq70");
	symbol_numeric *ddq71=sys.get_Acceleration("ddq71");
	symbol_numeric *ddq72=sys.get_Acceleration("ddq72");
	symbol_numeric *ddq73=sys.get_Acceleration("ddq73");
	symbol_numeric *ddq74=sys.get_Acceleration("ddq74");
	symbol_numeric *ddq75=sys.get_Acceleration("ddq75");
	symbol_numeric *ddq76=sys.get_Acceleration("ddq76");
	symbol_numeric *ddq77=sys.get_Acceleration("ddq77");
	symbol_numeric *ddq78=sys.get_Acceleration("ddq78");
	symbol_numeric *ddq79=sys.get_Acceleration("ddq79");
	symbol_numeric *ddq80=sys.get_Acceleration("ddq80");
	symbol_numeric *ddq81=sys.get_Acceleration("ddq81");
	symbol_numeric *ddq82=sys.get_Acceleration("ddq82");
	symbol_numeric *ddq83=sys.get_Acceleration("ddq83");
	symbol_numeric *ddq84=sys.get_Acceleration("ddq84");
	symbol_numeric *ddq85=sys.get_Acceleration("ddq85");
	symbol_numeric *ddq86=sys.get_Acceleration("ddq86");
	symbol_numeric *ddq87=sys.get_Acceleration("ddq87");
	symbol_numeric *ddq88=sys.get_Acceleration("ddq88");
	symbol_numeric *ddq89=sys.get_Acceleration("ddq89");
	symbol_numeric *ddq90=sys.get_Acceleration("ddq90");
	symbol_numeric *ddq91=sys.get_Acceleration("ddq91");
	symbol_numeric *ddq92=sys.get_Acceleration("ddq92");
	symbol_numeric *ddq93=sys.get_Acceleration("ddq93");
	symbol_numeric *ddq94=sys.get_Acceleration("ddq94");
	symbol_numeric *ddq95=sys.get_Acceleration("ddq95");
	symbol_numeric *ddq96=sys.get_Acceleration("ddq96");
	symbol_numeric *ddq97=sys.get_Acceleration("ddq97");
	symbol_numeric *ddq98=sys.get_Acceleration("ddq98");
	symbol_numeric *ddq99=sys.get_Acceleration("ddq99");
	symbol_numeric *ddq100=sys.get_Acceleration("ddq100");


// ************************************************************************************************
//	Initial Position Additional Constraint Equations
// ************************************************************************************************

	lst coord_indep_init;
	lst vel_indep_init;

//	coord_indep_init = (q1-0.0),(q2-0.0),(q3-0.0),(q4-0.0),(q5-0.0),(q6-0.0),(q7-0.0),(q8-0.0),(q9-0.0),(q10-0.0),(q11-0.0),(q12-0.0),(q13-0.0),(q14-0.0),(q15-0.0),(q16-0.0),(q17-0.0),(q18-0.0),(q19-0.0),(q20-0.0),(q21-0.0),(q22-0.0),(q23-0.0),(q24-0.0),(q25-0.0),(q26-0.0),(q27-0.0),(q28-0.0),(q29-0.0),(q30-0.0),(q31-0.0),(q32-0.0),(q33-0.0),(q34-0.0),(q35-0.0),(q36-0.0),(q37-0.0),(q38-0.0),(q39-0.0),(q40-0.0),(q41-0.0),(q42-0.0),(q43-0.0),(q44-0.0),(q45-0.0),(q46-0.0),(q47-0.0),(q48-0.0),(q49-0.0),(q50-0.0),(q51-0.0),(q52-0.0),(q53-0.0),(q54-0.0),(q55-0.0),(q56-0.0),(q57-0.0),(q58-0.0),(q59-0.0),(q60-0.0),(q61-0.0),(q62-0.0),(q63-0.0),(q64-0.0),(q65-0.0),(q66-0.0),(q67-0.0),(q68-0.0),(q69-0.0),(q70-0.0),(q71-0.0),(q72-0.0),(q73-0.0),(q74-0.0),(q75-0.0),(q76-0.0),(q77-0.0),(q78-0.0),(q79-0.0),(q80-0.0),(q81-0.0),(q82-0.0),(q83-0.0),(q84-0.0),(q85-0.0),(q86-0.0),(q87-0.0),(q88-0.0),(q89-0.0),(q90-0.0),(q91-0.0),(q92-0.0),(q93-0.0),(q94-0.0),(q95-0.0),(q96-0.0),(q97-0.0),(q98-0.0),(q99-0.0),(q100-0.0);


// ************************************************************************************************
//	Kinematical parameter definition
// ************************************************************************************************

	
	// Geometric Parameters
	symbol_numeric a1 = *sys.new_Parameter("a1",0.00000);
	symbol_numeric b1 = *sys.new_Parameter("b1",1.57080);
	symbol_numeric c1 = *sys.new_Parameter("c1",0.00000);
	symbol_numeric a2 = *sys.new_Parameter("a2",1.00000);
	symbol_numeric b2 = *sys.new_Parameter("b2",0.00000);
	symbol_numeric c2 = *sys.new_Parameter("c2",0.00000);
	symbol_numeric a3 = *sys.new_Parameter("a3",1.00000);
	symbol_numeric b3 = *sys.new_Parameter("b3",0.00000);
	symbol_numeric c3 = *sys.new_Parameter("c3",0.00000);
	symbol_numeric a4 = *sys.new_Parameter("a4",1.00000);
	symbol_numeric b4 = *sys.new_Parameter("b4",0.00000);
	symbol_numeric c4 = *sys.new_Parameter("c4",0.00000);
	symbol_numeric a5 = *sys.new_Parameter("a5",1.00000);
	symbol_numeric b5 = *sys.new_Parameter("b5",0.00000);
	symbol_numeric c5 = *sys.new_Parameter("c5",0.00000);
	symbol_numeric a6 = *sys.new_Parameter("a6",1.00000);
	symbol_numeric b6 = *sys.new_Parameter("b6",0.00000);
	symbol_numeric c6 = *sys.new_Parameter("c6",0.00000);
	symbol_numeric a7 = *sys.new_Parameter("a7",1.00000);
	symbol_numeric b7 = *sys.new_Parameter("b7",0.00000);
	symbol_numeric c7 = *sys.new_Parameter("c7",0.00000);
	symbol_numeric a8 = *sys.new_Parameter("a8",1.00000);
	symbol_numeric b8 = *sys.new_Parameter("b8",0.00000);
	symbol_numeric c8 = *sys.new_Parameter("c8",0.00000);
	symbol_numeric a9 = *sys.new_Parameter("a9",1.00000);
	symbol_numeric b9 = *sys.new_Parameter("b9",0.00000);
	symbol_numeric c9 = *sys.new_Parameter("c9",0.00000);
	symbol_numeric a10 = *sys.new_Parameter("a10",1.00000);
	symbol_numeric b10 = *sys.new_Parameter("b10",0.00000);
	symbol_numeric c10 = *sys.new_Parameter("c10",0.00000);
	symbol_numeric a11 = *sys.new_Parameter("a11",1.00000);
	symbol_numeric b11 = *sys.new_Parameter("b11",0.00000);
	symbol_numeric c11 = *sys.new_Parameter("c11",0.00000);
	symbol_numeric a12 = *sys.new_Parameter("a12",1.00000);
	symbol_numeric b12 = *sys.new_Parameter("b12",0.00000);
	symbol_numeric c12 = *sys.new_Parameter("c12",0.00000);
	symbol_numeric a13 = *sys.new_Parameter("a13",1.00000);
	symbol_numeric b13 = *sys.new_Parameter("b13",0.00000);
	symbol_numeric c13 = *sys.new_Parameter("c13",0.00000);
	symbol_numeric a14 = *sys.new_Parameter("a14",1.00000);
	symbol_numeric b14 = *sys.new_Parameter("b14",0.00000);
	symbol_numeric c14 = *sys.new_Parameter("c14",0.00000);
	symbol_numeric a15 = *sys.new_Parameter("a15",1.00000);
	symbol_numeric b15 = *sys.new_Parameter("b15",0.00000);
	symbol_numeric c15 = *sys.new_Parameter("c15",0.00000);
	symbol_numeric a16 = *sys.new_Parameter("a16",1.00000);
	symbol_numeric b16 = *sys.new_Parameter("b16",0.00000);
	symbol_numeric c16 = *sys.new_Parameter("c16",0.00000);
	symbol_numeric a17 = *sys.new_Parameter("a17",1.00000);
	symbol_numeric b17 = *sys.new_Parameter("b17",0.00000);
	symbol_numeric c17 = *sys.new_Parameter("c17",0.00000);
	symbol_numeric a18 = *sys.new_Parameter("a18",1.00000);
	symbol_numeric b18 = *sys.new_Parameter("b18",0.00000);
	symbol_numeric c18 = *sys.new_Parameter("c18",0.00000);
	symbol_numeric a19 = *sys.new_Parameter("a19",1.00000);
	symbol_numeric b19 = *sys.new_Parameter("b19",0.00000);
	symbol_numeric c19 = *sys.new_Parameter("c19",0.00000);
	symbol_numeric a20 = *sys.new_Parameter("a20",1.00000);
	symbol_numeric b20 = *sys.new_Parameter("b20",0.00000);
	symbol_numeric c20 = *sys.new_Parameter("c20",0.00000);
	symbol_numeric a21 = *sys.new_Parameter("a21",1.00000);
	symbol_numeric b21 = *sys.new_Parameter("b21",0.00000);
	symbol_numeric c21 = *sys.new_Parameter("c21",0.00000);
	symbol_numeric a22 = *sys.new_Parameter("a22",1.00000);
	symbol_numeric b22 = *sys.new_Parameter("b22",0.00000);
	symbol_numeric c22 = *sys.new_Parameter("c22",0.00000);
	symbol_numeric a23 = *sys.new_Parameter("a23",1.00000);
	symbol_numeric b23 = *sys.new_Parameter("b23",0.00000);
	symbol_numeric c23 = *sys.new_Parameter("c23",0.00000);
	symbol_numeric a24 = *sys.new_Parameter("a24",1.00000);
	symbol_numeric b24 = *sys.new_Parameter("b24",0.00000);
	symbol_numeric c24 = *sys.new_Parameter("c24",0.00000);
	symbol_numeric a25 = *sys.new_Parameter("a25",1.00000);
	symbol_numeric b25 = *sys.new_Parameter("b25",0.00000);
	symbol_numeric c25 = *sys.new_Parameter("c25",0.00000);
	symbol_numeric a26 = *sys.new_Parameter("a26",1.00000);
	symbol_numeric b26 = *sys.new_Parameter("b26",0.00000);
	symbol_numeric c26 = *sys.new_Parameter("c26",0.00000);
	symbol_numeric a27 = *sys.new_Parameter("a27",1.00000);
	symbol_numeric b27 = *sys.new_Parameter("b27",0.00000);
	symbol_numeric c27 = *sys.new_Parameter("c27",0.00000);
	symbol_numeric a28 = *sys.new_Parameter("a28",1.00000);
	symbol_numeric b28 = *sys.new_Parameter("b28",0.00000);
	symbol_numeric c28 = *sys.new_Parameter("c28",0.00000);
	symbol_numeric a29 = *sys.new_Parameter("a29",1.00000);
	symbol_numeric b29 = *sys.new_Parameter("b29",0.00000);
	symbol_numeric c29 = *sys.new_Parameter("c29",0.00000);
	symbol_numeric a30 = *sys.new_Parameter("a30",1.00000);
	symbol_numeric b30 = *sys.new_Parameter("b30",0.00000);
	symbol_numeric c30 = *sys.new_Parameter("c30",0.00000);
	symbol_numeric a31 = *sys.new_Parameter("a31",1.00000);
	symbol_numeric b31 = *sys.new_Parameter("b31",0.00000);
	symbol_numeric c31 = *sys.new_Parameter("c31",0.00000);
	symbol_numeric a32 = *sys.new_Parameter("a32",1.00000);
	symbol_numeric b32 = *sys.new_Parameter("b32",0.00000);
	symbol_numeric c32 = *sys.new_Parameter("c32",0.00000);
	symbol_numeric a33 = *sys.new_Parameter("a33",1.00000);
	symbol_numeric b33 = *sys.new_Parameter("b33",0.00000);
	symbol_numeric c33 = *sys.new_Parameter("c33",0.00000);
	symbol_numeric a34 = *sys.new_Parameter("a34",1.00000);
	symbol_numeric b34 = *sys.new_Parameter("b34",0.00000);
	symbol_numeric c34 = *sys.new_Parameter("c34",0.00000);
	symbol_numeric a35 = *sys.new_Parameter("a35",1.00000);
	symbol_numeric b35 = *sys.new_Parameter("b35",0.00000);
	symbol_numeric c35 = *sys.new_Parameter("c35",0.00000);
	symbol_numeric a36 = *sys.new_Parameter("a36",1.00000);
	symbol_numeric b36 = *sys.new_Parameter("b36",0.00000);
	symbol_numeric c36 = *sys.new_Parameter("c36",0.00000);
	symbol_numeric a37 = *sys.new_Parameter("a37",1.00000);
	symbol_numeric b37 = *sys.new_Parameter("b37",0.00000);
	symbol_numeric c37 = *sys.new_Parameter("c37",0.00000);
	symbol_numeric a38 = *sys.new_Parameter("a38",1.00000);
	symbol_numeric b38 = *sys.new_Parameter("b38",0.00000);
	symbol_numeric c38 = *sys.new_Parameter("c38",0.00000);
	symbol_numeric a39 = *sys.new_Parameter("a39",1.00000);
	symbol_numeric b39 = *sys.new_Parameter("b39",0.00000);
	symbol_numeric c39 = *sys.new_Parameter("c39",0.00000);
	symbol_numeric a40 = *sys.new_Parameter("a40",1.00000);
	symbol_numeric b40 = *sys.new_Parameter("b40",0.00000);
	symbol_numeric c40 = *sys.new_Parameter("c40",0.00000);
	symbol_numeric a41 = *sys.new_Parameter("a41",1.00000);
	symbol_numeric b41 = *sys.new_Parameter("b41",0.00000);
	symbol_numeric c41 = *sys.new_Parameter("c41",0.00000);
	symbol_numeric a42 = *sys.new_Parameter("a42",1.00000);
	symbol_numeric b42 = *sys.new_Parameter("b42",0.00000);
	symbol_numeric c42 = *sys.new_Parameter("c42",0.00000);
	symbol_numeric a43 = *sys.new_Parameter("a43",1.00000);
	symbol_numeric b43 = *sys.new_Parameter("b43",0.00000);
	symbol_numeric c43 = *sys.new_Parameter("c43",0.00000);
	symbol_numeric a44 = *sys.new_Parameter("a44",1.00000);
	symbol_numeric b44 = *sys.new_Parameter("b44",0.00000);
	symbol_numeric c44 = *sys.new_Parameter("c44",0.00000);
	symbol_numeric a45 = *sys.new_Parameter("a45",1.00000);
	symbol_numeric b45 = *sys.new_Parameter("b45",0.00000);
	symbol_numeric c45 = *sys.new_Parameter("c45",0.00000);
	symbol_numeric a46 = *sys.new_Parameter("a46",1.00000);
	symbol_numeric b46 = *sys.new_Parameter("b46",0.00000);
	symbol_numeric c46 = *sys.new_Parameter("c46",0.00000);
	symbol_numeric a47 = *sys.new_Parameter("a47",1.00000);
	symbol_numeric b47 = *sys.new_Parameter("b47",0.00000);
	symbol_numeric c47 = *sys.new_Parameter("c47",0.00000);
	symbol_numeric a48 = *sys.new_Parameter("a48",1.00000);
	symbol_numeric b48 = *sys.new_Parameter("b48",0.00000);
	symbol_numeric c48 = *sys.new_Parameter("c48",0.00000);
	symbol_numeric a49 = *sys.new_Parameter("a49",1.00000);
	symbol_numeric b49 = *sys.new_Parameter("b49",0.00000);
	symbol_numeric c49 = *sys.new_Parameter("c49",0.00000);
	symbol_numeric a50 = *sys.new_Parameter("a50",1.00000);
	symbol_numeric b50 = *sys.new_Parameter("b50",0.00000);
	symbol_numeric c50 = *sys.new_Parameter("c50",0.00000);
	symbol_numeric a51 = *sys.new_Parameter("a51",1.00000);
	symbol_numeric b51 = *sys.new_Parameter("b51",0.00000);
	symbol_numeric c51 = *sys.new_Parameter("c51",0.00000);
	symbol_numeric a52 = *sys.new_Parameter("a52",1.00000);
	symbol_numeric b52 = *sys.new_Parameter("b52",0.00000);
	symbol_numeric c52 = *sys.new_Parameter("c52",0.00000);
	symbol_numeric a53 = *sys.new_Parameter("a53",1.00000);
	symbol_numeric b53 = *sys.new_Parameter("b53",0.00000);
	symbol_numeric c53 = *sys.new_Parameter("c53",0.00000);
	symbol_numeric a54 = *sys.new_Parameter("a54",1.00000);
	symbol_numeric b54 = *sys.new_Parameter("b54",0.00000);
	symbol_numeric c54 = *sys.new_Parameter("c54",0.00000);
	symbol_numeric a55 = *sys.new_Parameter("a55",1.00000);
	symbol_numeric b55 = *sys.new_Parameter("b55",0.00000);
	symbol_numeric c55 = *sys.new_Parameter("c55",0.00000);
	symbol_numeric a56 = *sys.new_Parameter("a56",1.00000);
	symbol_numeric b56 = *sys.new_Parameter("b56",0.00000);
	symbol_numeric c56 = *sys.new_Parameter("c56",0.00000);
	symbol_numeric a57 = *sys.new_Parameter("a57",1.00000);
	symbol_numeric b57 = *sys.new_Parameter("b57",0.00000);
	symbol_numeric c57 = *sys.new_Parameter("c57",0.00000);
	symbol_numeric a58 = *sys.new_Parameter("a58",1.00000);
	symbol_numeric b58 = *sys.new_Parameter("b58",0.00000);
	symbol_numeric c58 = *sys.new_Parameter("c58",0.00000);
	symbol_numeric a59 = *sys.new_Parameter("a59",1.00000);
	symbol_numeric b59 = *sys.new_Parameter("b59",0.00000);
	symbol_numeric c59 = *sys.new_Parameter("c59",0.00000);
	symbol_numeric a60 = *sys.new_Parameter("a60",1.00000);
	symbol_numeric b60 = *sys.new_Parameter("b60",0.00000);
	symbol_numeric c60 = *sys.new_Parameter("c60",0.00000);
	symbol_numeric a61 = *sys.new_Parameter("a61",1.00000);
	symbol_numeric b61 = *sys.new_Parameter("b61",0.00000);
	symbol_numeric c61 = *sys.new_Parameter("c61",0.00000);
	symbol_numeric a62 = *sys.new_Parameter("a62",1.00000);
	symbol_numeric b62 = *sys.new_Parameter("b62",0.00000);
	symbol_numeric c62 = *sys.new_Parameter("c62",0.00000);
	symbol_numeric a63 = *sys.new_Parameter("a63",1.00000);
	symbol_numeric b63 = *sys.new_Parameter("b63",0.00000);
	symbol_numeric c63 = *sys.new_Parameter("c63",0.00000);
	symbol_numeric a64 = *sys.new_Parameter("a64",1.00000);
	symbol_numeric b64 = *sys.new_Parameter("b64",0.00000);
	symbol_numeric c64 = *sys.new_Parameter("c64",0.00000);
	symbol_numeric a65 = *sys.new_Parameter("a65",1.00000);
	symbol_numeric b65 = *sys.new_Parameter("b65",0.00000);
	symbol_numeric c65 = *sys.new_Parameter("c65",0.00000);
	symbol_numeric a66 = *sys.new_Parameter("a66",1.00000);
	symbol_numeric b66 = *sys.new_Parameter("b66",0.00000);
	symbol_numeric c66 = *sys.new_Parameter("c66",0.00000);
	symbol_numeric a67 = *sys.new_Parameter("a67",1.00000);
	symbol_numeric b67 = *sys.new_Parameter("b67",0.00000);
	symbol_numeric c67 = *sys.new_Parameter("c67",0.00000);
	symbol_numeric a68 = *sys.new_Parameter("a68",1.00000);
	symbol_numeric b68 = *sys.new_Parameter("b68",0.00000);
	symbol_numeric c68 = *sys.new_Parameter("c68",0.00000);
	symbol_numeric a69 = *sys.new_Parameter("a69",1.00000);
	symbol_numeric b69 = *sys.new_Parameter("b69",0.00000);
	symbol_numeric c69 = *sys.new_Parameter("c69",0.00000);
	symbol_numeric a70 = *sys.new_Parameter("a70",1.00000);
	symbol_numeric b70 = *sys.new_Parameter("b70",0.00000);
	symbol_numeric c70 = *sys.new_Parameter("c70",0.00000);
	symbol_numeric a71 = *sys.new_Parameter("a71",1.00000);
	symbol_numeric b71 = *sys.new_Parameter("b71",0.00000);
	symbol_numeric c71 = *sys.new_Parameter("c71",0.00000);
	symbol_numeric a72 = *sys.new_Parameter("a72",1.00000);
	symbol_numeric b72 = *sys.new_Parameter("b72",0.00000);
	symbol_numeric c72 = *sys.new_Parameter("c72",0.00000);
	symbol_numeric a73 = *sys.new_Parameter("a73",1.00000);
	symbol_numeric b73 = *sys.new_Parameter("b73",0.00000);
	symbol_numeric c73 = *sys.new_Parameter("c73",0.00000);
	symbol_numeric a74 = *sys.new_Parameter("a74",1.00000);
	symbol_numeric b74 = *sys.new_Parameter("b74",0.00000);
	symbol_numeric c74 = *sys.new_Parameter("c74",0.00000);
	symbol_numeric a75 = *sys.new_Parameter("a75",1.00000);
	symbol_numeric b75 = *sys.new_Parameter("b75",0.00000);
	symbol_numeric c75 = *sys.new_Parameter("c75",0.00000);
	symbol_numeric a76 = *sys.new_Parameter("a76",1.00000);
	symbol_numeric b76 = *sys.new_Parameter("b76",0.00000);
	symbol_numeric c76 = *sys.new_Parameter("c76",0.00000);
	symbol_numeric a77 = *sys.new_Parameter("a77",1.00000);
	symbol_numeric b77 = *sys.new_Parameter("b77",0.00000);
	symbol_numeric c77 = *sys.new_Parameter("c77",0.00000);
	symbol_numeric a78 = *sys.new_Parameter("a78",1.00000);
	symbol_numeric b78 = *sys.new_Parameter("b78",0.00000);
	symbol_numeric c78 = *sys.new_Parameter("c78",0.00000);
	symbol_numeric a79 = *sys.new_Parameter("a79",1.00000);
	symbol_numeric b79 = *sys.new_Parameter("b79",0.00000);
	symbol_numeric c79 = *sys.new_Parameter("c79",0.00000);
	symbol_numeric a80 = *sys.new_Parameter("a80",1.00000);
	symbol_numeric b80 = *sys.new_Parameter("b80",0.00000);
	symbol_numeric c80 = *sys.new_Parameter("c80",0.00000);
	symbol_numeric a81 = *sys.new_Parameter("a81",1.00000);
	symbol_numeric b81 = *sys.new_Parameter("b81",0.00000);
	symbol_numeric c81 = *sys.new_Parameter("c81",0.00000);
	symbol_numeric a82 = *sys.new_Parameter("a82",1.00000);
	symbol_numeric b82 = *sys.new_Parameter("b82",0.00000);
	symbol_numeric c82 = *sys.new_Parameter("c82",0.00000);
	symbol_numeric a83 = *sys.new_Parameter("a83",1.00000);
	symbol_numeric b83 = *sys.new_Parameter("b83",0.00000);
	symbol_numeric c83 = *sys.new_Parameter("c83",0.00000);
	symbol_numeric a84 = *sys.new_Parameter("a84",1.00000);
	symbol_numeric b84 = *sys.new_Parameter("b84",0.00000);
	symbol_numeric c84 = *sys.new_Parameter("c84",0.00000);
	symbol_numeric a85 = *sys.new_Parameter("a85",1.00000);
	symbol_numeric b85 = *sys.new_Parameter("b85",0.00000);
	symbol_numeric c85 = *sys.new_Parameter("c85",0.00000);
	symbol_numeric a86 = *sys.new_Parameter("a86",1.00000);
	symbol_numeric b86 = *sys.new_Parameter("b86",0.00000);
	symbol_numeric c86 = *sys.new_Parameter("c86",0.00000);
	symbol_numeric a87 = *sys.new_Parameter("a87",1.00000);
	symbol_numeric b87 = *sys.new_Parameter("b87",0.00000);
	symbol_numeric c87 = *sys.new_Parameter("c87",0.00000);
	symbol_numeric a88 = *sys.new_Parameter("a88",1.00000);
	symbol_numeric b88 = *sys.new_Parameter("b88",0.00000);
	symbol_numeric c88 = *sys.new_Parameter("c88",0.00000);
	symbol_numeric a89 = *sys.new_Parameter("a89",1.00000);
	symbol_numeric b89 = *sys.new_Parameter("b89",0.00000);
	symbol_numeric c89 = *sys.new_Parameter("c89",0.00000);
	symbol_numeric a90 = *sys.new_Parameter("a90",1.00000);
	symbol_numeric b90 = *sys.new_Parameter("b90",0.00000);
	symbol_numeric c90 = *sys.new_Parameter("c90",0.00000);
	symbol_numeric a91 = *sys.new_Parameter("a91",1.00000);
	symbol_numeric b91 = *sys.new_Parameter("b91",0.00000);
	symbol_numeric c91 = *sys.new_Parameter("c91",0.00000);
	symbol_numeric a92 = *sys.new_Parameter("a92",1.00000);
	symbol_numeric b92 = *sys.new_Parameter("b92",0.00000);
	symbol_numeric c92 = *sys.new_Parameter("c92",0.00000);
	symbol_numeric a93 = *sys.new_Parameter("a93",1.00000);
	symbol_numeric b93 = *sys.new_Parameter("b93",0.00000);
	symbol_numeric c93 = *sys.new_Parameter("c93",0.00000);
	symbol_numeric a94 = *sys.new_Parameter("a94",1.00000);
	symbol_numeric b94 = *sys.new_Parameter("b94",0.00000);
	symbol_numeric c94 = *sys.new_Parameter("c94",0.00000);
	symbol_numeric a95 = *sys.new_Parameter("a95",1.00000);
	symbol_numeric b95 = *sys.new_Parameter("b95",0.00000);
	symbol_numeric c95 = *sys.new_Parameter("c95",0.00000);
	symbol_numeric a96 = *sys.new_Parameter("a96",1.00000);
	symbol_numeric b96 = *sys.new_Parameter("b96",0.00000);
	symbol_numeric c96 = *sys.new_Parameter("c96",0.00000);
	symbol_numeric a97 = *sys.new_Parameter("a97",1.00000);
	symbol_numeric b97 = *sys.new_Parameter("b97",0.00000);
	symbol_numeric c97 = *sys.new_Parameter("c97",0.00000);
	symbol_numeric a98 = *sys.new_Parameter("a98",1.00000);
	symbol_numeric b98 = *sys.new_Parameter("b98",0.00000);
	symbol_numeric c98 = *sys.new_Parameter("c98",0.00000);
	symbol_numeric a99 = *sys.new_Parameter("a99",1.00000);
	symbol_numeric b99 = *sys.new_Parameter("b99",0.00000);
	symbol_numeric c99 = *sys.new_Parameter("c99",0.00000);
	symbol_numeric a100 = *sys.new_Parameter("a100",1.00000);
	symbol_numeric b100 = *sys.new_Parameter("b100",0.00000);
	symbol_numeric c100 = *sys.new_Parameter("c100",0.00000);



// ************************************************************************************************
// 	 KINEMATICS
// ************************************************************************************************

// ************************************************************************************************
//	Define Bases
// ************************************************************************************************


	sys.new_Base("B0" ,"xyz", 0,0,1,0);	// Creating a base fixed to the ground
	sys.new_Base("B1a","B0" , 1,0,0,b1);	// Rotation wrt x0
	sys.new_Base("B1" ,"B1a", 0,0,1,q1);	// Rotation wrt z1
	sys.new_Base("B2a","B1" , 1,0,0,b2);	// Rotation wrt x1
	sys.new_Base("B2" ,"B1a", 0,0,1,q2);	// Rotation wrt z2
	sys.new_Base("B3a","B2" , 1,0,0,b3);	// Rotation wrt x2
	sys.new_Base("B3" ,"B1a", 0,0,1,q3);	// Rotation wrt z3
	sys.new_Base("B4a","B3" , 1,0,0,b4);	// Rotation wrt x3
	sys.new_Base("B4" ,"B1a", 0,0,1,q4);	// Rotation wrt z4
	sys.new_Base("B5a","B4" , 1,0,0,b5);	// Rotation wrt x4
	sys.new_Base("B5" ,"B1a", 0,0,1,q5);	// Rotation wrt z5
	sys.new_Base("B6a","B5" , 1,0,0,b6);	// Rotation wrt x5
	sys.new_Base("B6" ,"B1a", 0,0,1,q6);	// Rotation wrt z6
	sys.new_Base("B7a","B6" , 1,0,0,b7);	// Rotation wrt x6
	sys.new_Base("B7" ,"B1a", 0,0,1,q7);	// Rotation wrt z7
	sys.new_Base("B8a","B7" , 1,0,0,b8);	// Rotation wrt x7
	sys.new_Base("B8" ,"B1a", 0,0,1,q8);	// Rotation wrt z8
	sys.new_Base("B9a","B8" , 1,0,0,b9);	// Rotation wrt x8
	sys.new_Base("B9" ,"B1a", 0,0,1,q9);	// Rotation wrt z9
	sys.new_Base("B10a","B9" , 1,0,0,b10);	// Rotation wrt x9
	sys.new_Base("B10" ,"B1a", 0,0,1,q10);	// Rotation wrt z10
	sys.new_Base("B11a","B10" , 1,0,0,b11);	// Rotation wrt x10
	sys.new_Base("B11" ,"B1a", 0,0,1,q11);	// Rotation wrt z11
	sys.new_Base("B12a","B11" , 1,0,0,b12);	// Rotation wrt x11
	sys.new_Base("B12" ,"B1a", 0,0,1,q12);	// Rotation wrt z12
	sys.new_Base("B13a","B12" , 1,0,0,b13);	// Rotation wrt x12
	sys.new_Base("B13" ,"B1a", 0,0,1,q13);	// Rotation wrt z13
	sys.new_Base("B14a","B13" , 1,0,0,b14);	// Rotation wrt x13
	sys.new_Base("B14" ,"B1a", 0,0,1,q14);	// Rotation wrt z14
	sys.new_Base("B15a","B14" , 1,0,0,b15);	// Rotation wrt x14
	sys.new_Base("B15" ,"B1a", 0,0,1,q15);	// Rotation wrt z15
	sys.new_Base("B16a","B15" , 1,0,0,b16);	// Rotation wrt x15
	sys.new_Base("B16" ,"B1a", 0,0,1,q16);	// Rotation wrt z16
	sys.new_Base("B17a","B16" , 1,0,0,b17);	// Rotation wrt x16
	sys.new_Base("B17" ,"B1a", 0,0,1,q17);	// Rotation wrt z17
	sys.new_Base("B18a","B17" , 1,0,0,b18);	// Rotation wrt x17
	sys.new_Base("B18" ,"B1a", 0,0,1,q18);	// Rotation wrt z18
	sys.new_Base("B19a","B18" , 1,0,0,b19);	// Rotation wrt x18
	sys.new_Base("B19" ,"B1a", 0,0,1,q19);	// Rotation wrt z19
	sys.new_Base("B20a","B19" , 1,0,0,b20);	// Rotation wrt x19
	sys.new_Base("B20" ,"B1a", 0,0,1,q20);	// Rotation wrt z20
	sys.new_Base("B21a","B20" , 1,0,0,b21);	// Rotation wrt x20
	sys.new_Base("B21" ,"B1a", 0,0,1,q21);	// Rotation wrt z21
	sys.new_Base("B22a","B21" , 1,0,0,b22);	// Rotation wrt x21
	sys.new_Base("B22" ,"B1a", 0,0,1,q22);	// Rotation wrt z22
	sys.new_Base("B23a","B22" , 1,0,0,b23);	// Rotation wrt x22
	sys.new_Base("B23" ,"B1a", 0,0,1,q23);	// Rotation wrt z23
	sys.new_Base("B24a","B23" , 1,0,0,b24);	// Rotation wrt x23
	sys.new_Base("B24" ,"B1a", 0,0,1,q24);	// Rotation wrt z24
	sys.new_Base("B25a","B24" , 1,0,0,b25);	// Rotation wrt x24
	sys.new_Base("B25" ,"B1a", 0,0,1,q25);	// Rotation wrt z25
	sys.new_Base("B26a","B25" , 1,0,0,b26);	// Rotation wrt x25
	sys.new_Base("B26" ,"B1a", 0,0,1,q26);	// Rotation wrt z26
	sys.new_Base("B27a","B26" , 1,0,0,b27);	// Rotation wrt x26
	sys.new_Base("B27" ,"B1a", 0,0,1,q27);	// Rotation wrt z27
	sys.new_Base("B28a","B27" , 1,0,0,b28);	// Rotation wrt x27
	sys.new_Base("B28" ,"B1a", 0,0,1,q28);	// Rotation wrt z28
	sys.new_Base("B29a","B28" , 1,0,0,b29);	// Rotation wrt x28
	sys.new_Base("B29" ,"B1a", 0,0,1,q29);	// Rotation wrt z29
	sys.new_Base("B30a","B29" , 1,0,0,b30);	// Rotation wrt x29
	sys.new_Base("B30" ,"B1a", 0,0,1,q30);	// Rotation wrt z30
	sys.new_Base("B31a","B30" , 1,0,0,b31);	// Rotation wrt x30
	sys.new_Base("B31" ,"B1a", 0,0,1,q31);	// Rotation wrt z31
	sys.new_Base("B32a","B31" , 1,0,0,b32);	// Rotation wrt x31
	sys.new_Base("B32" ,"B1a", 0,0,1,q32);	// Rotation wrt z32
	sys.new_Base("B33a","B32" , 1,0,0,b33);	// Rotation wrt x32
	sys.new_Base("B33" ,"B1a", 0,0,1,q33);	// Rotation wrt z33
	sys.new_Base("B34a","B33" , 1,0,0,b34);	// Rotation wrt x33
	sys.new_Base("B34" ,"B1a", 0,0,1,q34);	// Rotation wrt z34
	sys.new_Base("B35a","B34" , 1,0,0,b35);	// Rotation wrt x34
	sys.new_Base("B35" ,"B1a", 0,0,1,q35);	// Rotation wrt z35
	sys.new_Base("B36a","B35" , 1,0,0,b36);	// Rotation wrt x35
	sys.new_Base("B36" ,"B1a", 0,0,1,q36);	// Rotation wrt z36
	sys.new_Base("B37a","B36" , 1,0,0,b37);	// Rotation wrt x36
	sys.new_Base("B37" ,"B1a", 0,0,1,q37);	// Rotation wrt z37
	sys.new_Base("B38a","B37" , 1,0,0,b38);	// Rotation wrt x37
	sys.new_Base("B38" ,"B1a", 0,0,1,q38);	// Rotation wrt z38
	sys.new_Base("B39a","B38" , 1,0,0,b39);	// Rotation wrt x38
	sys.new_Base("B39" ,"B1a", 0,0,1,q39);	// Rotation wrt z39
	sys.new_Base("B40a","B39" , 1,0,0,b40);	// Rotation wrt x39
	sys.new_Base("B40" ,"B1a", 0,0,1,q40);	// Rotation wrt z40
	sys.new_Base("B41a","B40" , 1,0,0,b41);	// Rotation wrt x40
	sys.new_Base("B41" ,"B1a", 0,0,1,q41);	// Rotation wrt z41
	sys.new_Base("B42a","B41" , 1,0,0,b42);	// Rotation wrt x41
	sys.new_Base("B42" ,"B1a", 0,0,1,q42);	// Rotation wrt z42
	sys.new_Base("B43a","B42" , 1,0,0,b43);	// Rotation wrt x42
	sys.new_Base("B43" ,"B1a", 0,0,1,q43);	// Rotation wrt z43
	sys.new_Base("B44a","B43" , 1,0,0,b44);	// Rotation wrt x43
	sys.new_Base("B44" ,"B1a", 0,0,1,q44);	// Rotation wrt z44
	sys.new_Base("B45a","B44" , 1,0,0,b45);	// Rotation wrt x44
	sys.new_Base("B45" ,"B1a", 0,0,1,q45);	// Rotation wrt z45
	sys.new_Base("B46a","B45" , 1,0,0,b46);	// Rotation wrt x45
	sys.new_Base("B46" ,"B1a", 0,0,1,q46);	// Rotation wrt z46
	sys.new_Base("B47a","B46" , 1,0,0,b47);	// Rotation wrt x46
	sys.new_Base("B47" ,"B1a", 0,0,1,q47);	// Rotation wrt z47
	sys.new_Base("B48a","B47" , 1,0,0,b48);	// Rotation wrt x47
	sys.new_Base("B48" ,"B1a", 0,0,1,q48);	// Rotation wrt z48
	sys.new_Base("B49a","B48" , 1,0,0,b49);	// Rotation wrt x48
	sys.new_Base("B49" ,"B1a", 0,0,1,q49);	// Rotation wrt z49
	sys.new_Base("B50a","B49" , 1,0,0,b50);	// Rotation wrt x49
	sys.new_Base("B50" ,"B1a", 0,0,1,q50);	// Rotation wrt z50
	sys.new_Base("B51a","B50" , 1,0,0,b51);	// Rotation wrt x50
	sys.new_Base("B51" ,"B1a", 0,0,1,q51);	// Rotation wrt z51
	sys.new_Base("B52a","B51" , 1,0,0,b52);	// Rotation wrt x51
	sys.new_Base("B52" ,"B1a", 0,0,1,q52);	// Rotation wrt z52
	sys.new_Base("B53a","B52" , 1,0,0,b53);	// Rotation wrt x52
	sys.new_Base("B53" ,"B1a", 0,0,1,q53);	// Rotation wrt z53
	sys.new_Base("B54a","B53" , 1,0,0,b54);	// Rotation wrt x53
	sys.new_Base("B54" ,"B1a", 0,0,1,q54);	// Rotation wrt z54
	sys.new_Base("B55a","B54" , 1,0,0,b55);	// Rotation wrt x54
	sys.new_Base("B55" ,"B1a", 0,0,1,q55);	// Rotation wrt z55
	sys.new_Base("B56a","B55" , 1,0,0,b56);	// Rotation wrt x55
	sys.new_Base("B56" ,"B1a", 0,0,1,q56);	// Rotation wrt z56
	sys.new_Base("B57a","B56" , 1,0,0,b57);	// Rotation wrt x56
	sys.new_Base("B57" ,"B1a", 0,0,1,q57);	// Rotation wrt z57
	sys.new_Base("B58a","B57" , 1,0,0,b58);	// Rotation wrt x57
	sys.new_Base("B58" ,"B1a", 0,0,1,q58);	// Rotation wrt z58
	sys.new_Base("B59a","B58" , 1,0,0,b59);	// Rotation wrt x58
	sys.new_Base("B59" ,"B1a", 0,0,1,q59);	// Rotation wrt z59
	sys.new_Base("B60a","B59" , 1,0,0,b60);	// Rotation wrt x59
	sys.new_Base("B60" ,"B1a", 0,0,1,q60);	// Rotation wrt z60
	sys.new_Base("B61a","B60" , 1,0,0,b61);	// Rotation wrt x60
	sys.new_Base("B61" ,"B1a", 0,0,1,q61);	// Rotation wrt z61
	sys.new_Base("B62a","B61" , 1,0,0,b62);	// Rotation wrt x61
	sys.new_Base("B62" ,"B1a", 0,0,1,q62);	// Rotation wrt z62
	sys.new_Base("B63a","B62" , 1,0,0,b63);	// Rotation wrt x62
	sys.new_Base("B63" ,"B1a", 0,0,1,q63);	// Rotation wrt z63
	sys.new_Base("B64a","B63" , 1,0,0,b64);	// Rotation wrt x63
	sys.new_Base("B64" ,"B1a", 0,0,1,q64);	// Rotation wrt z64
	sys.new_Base("B65a","B64" , 1,0,0,b65);	// Rotation wrt x64
	sys.new_Base("B65" ,"B1a", 0,0,1,q65);	// Rotation wrt z65
	sys.new_Base("B66a","B65" , 1,0,0,b66);	// Rotation wrt x65
	sys.new_Base("B66" ,"B1a", 0,0,1,q66);	// Rotation wrt z66
	sys.new_Base("B67a","B66" , 1,0,0,b67);	// Rotation wrt x66
	sys.new_Base("B67" ,"B1a", 0,0,1,q67);	// Rotation wrt z67
	sys.new_Base("B68a","B67" , 1,0,0,b68);	// Rotation wrt x67
	sys.new_Base("B68" ,"B1a", 0,0,1,q68);	// Rotation wrt z68
	sys.new_Base("B69a","B68" , 1,0,0,b69);	// Rotation wrt x68
	sys.new_Base("B69" ,"B1a", 0,0,1,q69);	// Rotation wrt z69
	sys.new_Base("B70a","B69" , 1,0,0,b70);	// Rotation wrt x69
	sys.new_Base("B70" ,"B1a", 0,0,1,q70);	// Rotation wrt z70
	sys.new_Base("B71a","B70" , 1,0,0,b71);	// Rotation wrt x70
	sys.new_Base("B71" ,"B1a", 0,0,1,q71);	// Rotation wrt z71
	sys.new_Base("B72a","B71" , 1,0,0,b72);	// Rotation wrt x71
	sys.new_Base("B72" ,"B1a", 0,0,1,q72);	// Rotation wrt z72
	sys.new_Base("B73a","B72" , 1,0,0,b73);	// Rotation wrt x72
	sys.new_Base("B73" ,"B1a", 0,0,1,q73);	// Rotation wrt z73
	sys.new_Base("B74a","B73" , 1,0,0,b74);	// Rotation wrt x73
	sys.new_Base("B74" ,"B1a", 0,0,1,q74);	// Rotation wrt z74
	sys.new_Base("B75a","B74" , 1,0,0,b75);	// Rotation wrt x74
	sys.new_Base("B75" ,"B1a", 0,0,1,q75);	// Rotation wrt z75
	sys.new_Base("B76a","B75" , 1,0,0,b76);	// Rotation wrt x75
	sys.new_Base("B76" ,"B1a", 0,0,1,q76);	// Rotation wrt z76
	sys.new_Base("B77a","B76" , 1,0,0,b77);	// Rotation wrt x76
	sys.new_Base("B77" ,"B1a", 0,0,1,q77);	// Rotation wrt z77
	sys.new_Base("B78a","B77" , 1,0,0,b78);	// Rotation wrt x77
	sys.new_Base("B78" ,"B1a", 0,0,1,q78);	// Rotation wrt z78
	sys.new_Base("B79a","B78" , 1,0,0,b79);	// Rotation wrt x78
	sys.new_Base("B79" ,"B1a", 0,0,1,q79);	// Rotation wrt z79
	sys.new_Base("B80a","B79" , 1,0,0,b80);	// Rotation wrt x79
	sys.new_Base("B80" ,"B1a", 0,0,1,q80);	// Rotation wrt z80
	sys.new_Base("B81a","B80" , 1,0,0,b81);	// Rotation wrt x80
	sys.new_Base("B81" ,"B1a", 0,0,1,q81);	// Rotation wrt z81
	sys.new_Base("B82a","B81" , 1,0,0,b82);	// Rotation wrt x81
	sys.new_Base("B82" ,"B1a", 0,0,1,q82);	// Rotation wrt z82
	sys.new_Base("B83a","B82" , 1,0,0,b83);	// Rotation wrt x82
	sys.new_Base("B83" ,"B1a", 0,0,1,q83);	// Rotation wrt z83
	sys.new_Base("B84a","B83" , 1,0,0,b84);	// Rotation wrt x83
	sys.new_Base("B84" ,"B1a", 0,0,1,q84);	// Rotation wrt z84
	sys.new_Base("B85a","B84" , 1,0,0,b85);	// Rotation wrt x84
	sys.new_Base("B85" ,"B1a", 0,0,1,q85);	// Rotation wrt z85
	sys.new_Base("B86a","B85" , 1,0,0,b86);	// Rotation wrt x85
	sys.new_Base("B86" ,"B1a", 0,0,1,q86);	// Rotation wrt z86
	sys.new_Base("B87a","B86" , 1,0,0,b87);	// Rotation wrt x86
	sys.new_Base("B87" ,"B1a", 0,0,1,q87);	// Rotation wrt z87
	sys.new_Base("B88a","B87" , 1,0,0,b88);	// Rotation wrt x87
	sys.new_Base("B88" ,"B1a", 0,0,1,q88);	// Rotation wrt z88
	sys.new_Base("B89a","B88" , 1,0,0,b89);	// Rotation wrt x88
	sys.new_Base("B89" ,"B1a", 0,0,1,q89);	// Rotation wrt z89
	sys.new_Base("B90a","B89" , 1,0,0,b90);	// Rotation wrt x89
	sys.new_Base("B90" ,"B1a", 0,0,1,q90);	// Rotation wrt z90
	sys.new_Base("B91a","B90" , 1,0,0,b91);	// Rotation wrt x90
	sys.new_Base("B91" ,"B1a", 0,0,1,q91);	// Rotation wrt z91
	sys.new_Base("B92a","B91" , 1,0,0,b92);	// Rotation wrt x91
	sys.new_Base("B92" ,"B1a", 0,0,1,q92);	// Rotation wrt z92
	sys.new_Base("B93a","B92" , 1,0,0,b93);	// Rotation wrt x92
	sys.new_Base("B93" ,"B1a", 0,0,1,q93);	// Rotation wrt z93
	sys.new_Base("B94a","B93" , 1,0,0,b94);	// Rotation wrt x93
	sys.new_Base("B94" ,"B1a", 0,0,1,q94);	// Rotation wrt z94
	sys.new_Base("B95a","B94" , 1,0,0,b95);	// Rotation wrt x94
	sys.new_Base("B95" ,"B1a", 0,0,1,q95);	// Rotation wrt z95
	sys.new_Base("B96a","B95" , 1,0,0,b96);	// Rotation wrt x95
	sys.new_Base("B96" ,"B1a", 0,0,1,q96);	// Rotation wrt z96
	sys.new_Base("B97a","B96" , 1,0,0,b97);	// Rotation wrt x96
	sys.new_Base("B97" ,"B1a", 0,0,1,q97);	// Rotation wrt z97
	sys.new_Base("B98a","B97" , 1,0,0,b98);	// Rotation wrt x97
	sys.new_Base("B98" ,"B1a", 0,0,1,q98);	// Rotation wrt z98
	sys.new_Base("B99a","B98" , 1,0,0,b99);	// Rotation wrt x98
	sys.new_Base("B99" ,"B1a", 0,0,1,q99);	// Rotation wrt z99
	sys.new_Base("B100a","B99" , 1,0,0,b100);	// Rotation wrt x99
	sys.new_Base("B100" ,"B1a", 0,0,1,q100);	// Rotation wrt z100


// ************************************************************************************************
//	Define Vectors
// ************************************************************************************************

	Vector3D VZERO  = *sys.new_Vector3D("VZERO",0, 0,0,"xyz");

	Vector3D P0P1  = *sys.new_Vector3D("P0P1a",a1, 0,0,"B0") + *sys.new_Vector3D("P0P1b", 0,0,c1, "B1");
	Vector3D P1P2  = *sys.new_Vector3D("P1P2a",a2, 0,0,"B1") + *sys.new_Vector3D("P1P2b", 0,0,c2, "B2");
	Vector3D P2P3  = *sys.new_Vector3D("P2P3a",a3, 0,0,"B2") + *sys.new_Vector3D("P2P3b", 0,0,c3, "B3");
	Vector3D P3P4  = *sys.new_Vector3D("P3P4a",a4, 0,0,"B3") + *sys.new_Vector3D("P3P4b", 0,0,c4, "B4");
	Vector3D P4P5  = *sys.new_Vector3D("P4P5a",a5, 0,0,"B4") + *sys.new_Vector3D("P4P5b", 0,0,c5, "B5");
	Vector3D P5P6  = *sys.new_Vector3D("P5P6a",a6, 0,0,"B5") + *sys.new_Vector3D("P5P6b", 0,0,c6, "B6");
	Vector3D P6P7  = *sys.new_Vector3D("P6P7a",a7, 0,0,"B6") + *sys.new_Vector3D("P6P7b", 0,0,c7, "B7");
	Vector3D P7P8  = *sys.new_Vector3D("P7P8a",a8, 0,0,"B7") + *sys.new_Vector3D("P7P8b", 0,0,c8, "B8");
	Vector3D P8P9  = *sys.new_Vector3D("P8P9a",a9, 0,0,"B8") + *sys.new_Vector3D("P8P9b", 0,0,c9, "B9");
	Vector3D P9P10  = *sys.new_Vector3D("P9P10a",a10, 0,0,"B9") + *sys.new_Vector3D("P9P10b", 0,0,c10, "B10");
	Vector3D P10P11  = *sys.new_Vector3D("P10P11a",a11, 0,0,"B10") + *sys.new_Vector3D("P10P11b", 0,0,c11, "B11");
	Vector3D P11P12  = *sys.new_Vector3D("P11P12a",a12, 0,0,"B11") + *sys.new_Vector3D("P11P12b", 0,0,c12, "B12");
	Vector3D P12P13  = *sys.new_Vector3D("P12P13a",a13, 0,0,"B12") + *sys.new_Vector3D("P12P13b", 0,0,c13, "B13");
	Vector3D P13P14  = *sys.new_Vector3D("P13P14a",a14, 0,0,"B13") + *sys.new_Vector3D("P13P14b", 0,0,c14, "B14");
	Vector3D P14P15  = *sys.new_Vector3D("P14P15a",a15, 0,0,"B14") + *sys.new_Vector3D("P14P15b", 0,0,c15, "B15");
	Vector3D P15P16  = *sys.new_Vector3D("P15P16a",a16, 0,0,"B15") + *sys.new_Vector3D("P15P16b", 0,0,c16, "B16");
	Vector3D P16P17  = *sys.new_Vector3D("P16P17a",a17, 0,0,"B16") + *sys.new_Vector3D("P16P17b", 0,0,c17, "B17");
	Vector3D P17P18  = *sys.new_Vector3D("P17P18a",a18, 0,0,"B17") + *sys.new_Vector3D("P17P18b", 0,0,c18, "B18");
	Vector3D P18P19  = *sys.new_Vector3D("P18P19a",a19, 0,0,"B18") + *sys.new_Vector3D("P18P19b", 0,0,c19, "B19");
	Vector3D P19P20  = *sys.new_Vector3D("P19P20a",a20, 0,0,"B19") + *sys.new_Vector3D("P19P20b", 0,0,c20, "B20");
	Vector3D P20P21  = *sys.new_Vector3D("P20P21a",a21, 0,0,"B20") + *sys.new_Vector3D("P20P21b", 0,0,c21, "B21");
	Vector3D P21P22  = *sys.new_Vector3D("P21P22a",a22, 0,0,"B21") + *sys.new_Vector3D("P21P22b", 0,0,c22, "B22");
	Vector3D P22P23  = *sys.new_Vector3D("P22P23a",a23, 0,0,"B22") + *sys.new_Vector3D("P22P23b", 0,0,c23, "B23");
	Vector3D P23P24  = *sys.new_Vector3D("P23P24a",a24, 0,0,"B23") + *sys.new_Vector3D("P23P24b", 0,0,c24, "B24");
	Vector3D P24P25  = *sys.new_Vector3D("P24P25a",a25, 0,0,"B24") + *sys.new_Vector3D("P24P25b", 0,0,c25, "B25");
	Vector3D P25P26  = *sys.new_Vector3D("P25P26a",a26, 0,0,"B25") + *sys.new_Vector3D("P25P26b", 0,0,c26, "B26");
	Vector3D P26P27  = *sys.new_Vector3D("P26P27a",a27, 0,0,"B26") + *sys.new_Vector3D("P26P27b", 0,0,c27, "B27");
	Vector3D P27P28  = *sys.new_Vector3D("P27P28a",a28, 0,0,"B27") + *sys.new_Vector3D("P27P28b", 0,0,c28, "B28");
	Vector3D P28P29  = *sys.new_Vector3D("P28P29a",a29, 0,0,"B28") + *sys.new_Vector3D("P28P29b", 0,0,c29, "B29");
	Vector3D P29P30  = *sys.new_Vector3D("P29P30a",a30, 0,0,"B29") + *sys.new_Vector3D("P29P30b", 0,0,c30, "B30");
	Vector3D P30P31  = *sys.new_Vector3D("P30P31a",a31, 0,0,"B30") + *sys.new_Vector3D("P30P31b", 0,0,c31, "B31");
	Vector3D P31P32  = *sys.new_Vector3D("P31P32a",a32, 0,0,"B31") + *sys.new_Vector3D("P31P32b", 0,0,c32, "B32");
	Vector3D P32P33  = *sys.new_Vector3D("P32P33a",a33, 0,0,"B32") + *sys.new_Vector3D("P32P33b", 0,0,c33, "B33");
	Vector3D P33P34  = *sys.new_Vector3D("P33P34a",a34, 0,0,"B33") + *sys.new_Vector3D("P33P34b", 0,0,c34, "B34");
	Vector3D P34P35  = *sys.new_Vector3D("P34P35a",a35, 0,0,"B34") + *sys.new_Vector3D("P34P35b", 0,0,c35, "B35");
	Vector3D P35P36  = *sys.new_Vector3D("P35P36a",a36, 0,0,"B35") + *sys.new_Vector3D("P35P36b", 0,0,c36, "B36");
	Vector3D P36P37  = *sys.new_Vector3D("P36P37a",a37, 0,0,"B36") + *sys.new_Vector3D("P36P37b", 0,0,c37, "B37");
	Vector3D P37P38  = *sys.new_Vector3D("P37P38a",a38, 0,0,"B37") + *sys.new_Vector3D("P37P38b", 0,0,c38, "B38");
	Vector3D P38P39  = *sys.new_Vector3D("P38P39a",a39, 0,0,"B38") + *sys.new_Vector3D("P38P39b", 0,0,c39, "B39");
	Vector3D P39P40  = *sys.new_Vector3D("P39P40a",a40, 0,0,"B39") + *sys.new_Vector3D("P39P40b", 0,0,c40, "B40");
	Vector3D P40P41  = *sys.new_Vector3D("P40P41a",a41, 0,0,"B40") + *sys.new_Vector3D("P40P41b", 0,0,c41, "B41");
	Vector3D P41P42  = *sys.new_Vector3D("P41P42a",a42, 0,0,"B41") + *sys.new_Vector3D("P41P42b", 0,0,c42, "B42");
	Vector3D P42P43  = *sys.new_Vector3D("P42P43a",a43, 0,0,"B42") + *sys.new_Vector3D("P42P43b", 0,0,c43, "B43");
	Vector3D P43P44  = *sys.new_Vector3D("P43P44a",a44, 0,0,"B43") + *sys.new_Vector3D("P43P44b", 0,0,c44, "B44");
	Vector3D P44P45  = *sys.new_Vector3D("P44P45a",a45, 0,0,"B44") + *sys.new_Vector3D("P44P45b", 0,0,c45, "B45");
	Vector3D P45P46  = *sys.new_Vector3D("P45P46a",a46, 0,0,"B45") + *sys.new_Vector3D("P45P46b", 0,0,c46, "B46");
	Vector3D P46P47  = *sys.new_Vector3D("P46P47a",a47, 0,0,"B46") + *sys.new_Vector3D("P46P47b", 0,0,c47, "B47");
	Vector3D P47P48  = *sys.new_Vector3D("P47P48a",a48, 0,0,"B47") + *sys.new_Vector3D("P47P48b", 0,0,c48, "B48");
	Vector3D P48P49  = *sys.new_Vector3D("P48P49a",a49, 0,0,"B48") + *sys.new_Vector3D("P48P49b", 0,0,c49, "B49");
	Vector3D P49P50  = *sys.new_Vector3D("P49P50a",a50, 0,0,"B49") + *sys.new_Vector3D("P49P50b", 0,0,c50, "B50");
	Vector3D P50P51  = *sys.new_Vector3D("P50P51a",a51, 0,0,"B50") + *sys.new_Vector3D("P50P51b", 0,0,c51, "B51");
	Vector3D P51P52  = *sys.new_Vector3D("P51P52a",a52, 0,0,"B51") + *sys.new_Vector3D("P51P52b", 0,0,c52, "B52");
	Vector3D P52P53  = *sys.new_Vector3D("P52P53a",a53, 0,0,"B52") + *sys.new_Vector3D("P52P53b", 0,0,c53, "B53");
	Vector3D P53P54  = *sys.new_Vector3D("P53P54a",a54, 0,0,"B53") + *sys.new_Vector3D("P53P54b", 0,0,c54, "B54");
	Vector3D P54P55  = *sys.new_Vector3D("P54P55a",a55, 0,0,"B54") + *sys.new_Vector3D("P54P55b", 0,0,c55, "B55");
	Vector3D P55P56  = *sys.new_Vector3D("P55P56a",a56, 0,0,"B55") + *sys.new_Vector3D("P55P56b", 0,0,c56, "B56");
	Vector3D P56P57  = *sys.new_Vector3D("P56P57a",a57, 0,0,"B56") + *sys.new_Vector3D("P56P57b", 0,0,c57, "B57");
	Vector3D P57P58  = *sys.new_Vector3D("P57P58a",a58, 0,0,"B57") + *sys.new_Vector3D("P57P58b", 0,0,c58, "B58");
	Vector3D P58P59  = *sys.new_Vector3D("P58P59a",a59, 0,0,"B58") + *sys.new_Vector3D("P58P59b", 0,0,c59, "B59");
	Vector3D P59P60  = *sys.new_Vector3D("P59P60a",a60, 0,0,"B59") + *sys.new_Vector3D("P59P60b", 0,0,c60, "B60");
	Vector3D P60P61  = *sys.new_Vector3D("P60P61a",a61, 0,0,"B60") + *sys.new_Vector3D("P60P61b", 0,0,c61, "B61");
	Vector3D P61P62  = *sys.new_Vector3D("P61P62a",a62, 0,0,"B61") + *sys.new_Vector3D("P61P62b", 0,0,c62, "B62");
	Vector3D P62P63  = *sys.new_Vector3D("P62P63a",a63, 0,0,"B62") + *sys.new_Vector3D("P62P63b", 0,0,c63, "B63");
	Vector3D P63P64  = *sys.new_Vector3D("P63P64a",a64, 0,0,"B63") + *sys.new_Vector3D("P63P64b", 0,0,c64, "B64");
	Vector3D P64P65  = *sys.new_Vector3D("P64P65a",a65, 0,0,"B64") + *sys.new_Vector3D("P64P65b", 0,0,c65, "B65");
	Vector3D P65P66  = *sys.new_Vector3D("P65P66a",a66, 0,0,"B65") + *sys.new_Vector3D("P65P66b", 0,0,c66, "B66");
	Vector3D P66P67  = *sys.new_Vector3D("P66P67a",a67, 0,0,"B66") + *sys.new_Vector3D("P66P67b", 0,0,c67, "B67");
	Vector3D P67P68  = *sys.new_Vector3D("P67P68a",a68, 0,0,"B67") + *sys.new_Vector3D("P67P68b", 0,0,c68, "B68");
	Vector3D P68P69  = *sys.new_Vector3D("P68P69a",a69, 0,0,"B68") + *sys.new_Vector3D("P68P69b", 0,0,c69, "B69");
	Vector3D P69P70  = *sys.new_Vector3D("P69P70a",a70, 0,0,"B69") + *sys.new_Vector3D("P69P70b", 0,0,c70, "B70");
	Vector3D P70P71  = *sys.new_Vector3D("P70P71a",a71, 0,0,"B70") + *sys.new_Vector3D("P70P71b", 0,0,c71, "B71");
	Vector3D P71P72  = *sys.new_Vector3D("P71P72a",a72, 0,0,"B71") + *sys.new_Vector3D("P71P72b", 0,0,c72, "B72");
	Vector3D P72P73  = *sys.new_Vector3D("P72P73a",a73, 0,0,"B72") + *sys.new_Vector3D("P72P73b", 0,0,c73, "B73");
	Vector3D P73P74  = *sys.new_Vector3D("P73P74a",a74, 0,0,"B73") + *sys.new_Vector3D("P73P74b", 0,0,c74, "B74");
	Vector3D P74P75  = *sys.new_Vector3D("P74P75a",a75, 0,0,"B74") + *sys.new_Vector3D("P74P75b", 0,0,c75, "B75");
	Vector3D P75P76  = *sys.new_Vector3D("P75P76a",a76, 0,0,"B75") + *sys.new_Vector3D("P75P76b", 0,0,c76, "B76");
	Vector3D P76P77  = *sys.new_Vector3D("P76P77a",a77, 0,0,"B76") + *sys.new_Vector3D("P76P77b", 0,0,c77, "B77");
	Vector3D P77P78  = *sys.new_Vector3D("P77P78a",a78, 0,0,"B77") + *sys.new_Vector3D("P77P78b", 0,0,c78, "B78");
	Vector3D P78P79  = *sys.new_Vector3D("P78P79a",a79, 0,0,"B78") + *sys.new_Vector3D("P78P79b", 0,0,c79, "B79");
	Vector3D P79P80  = *sys.new_Vector3D("P79P80a",a80, 0,0,"B79") + *sys.new_Vector3D("P79P80b", 0,0,c80, "B80");
	Vector3D P80P81  = *sys.new_Vector3D("P80P81a",a81, 0,0,"B80") + *sys.new_Vector3D("P80P81b", 0,0,c81, "B81");
	Vector3D P81P82  = *sys.new_Vector3D("P81P82a",a82, 0,0,"B81") + *sys.new_Vector3D("P81P82b", 0,0,c82, "B82");
	Vector3D P82P83  = *sys.new_Vector3D("P82P83a",a83, 0,0,"B82") + *sys.new_Vector3D("P82P83b", 0,0,c83, "B83");
	Vector3D P83P84  = *sys.new_Vector3D("P83P84a",a84, 0,0,"B83") + *sys.new_Vector3D("P83P84b", 0,0,c84, "B84");
	Vector3D P84P85  = *sys.new_Vector3D("P84P85a",a85, 0,0,"B84") + *sys.new_Vector3D("P84P85b", 0,0,c85, "B85");
	Vector3D P85P86  = *sys.new_Vector3D("P85P86a",a86, 0,0,"B85") + *sys.new_Vector3D("P85P86b", 0,0,c86, "B86");
	Vector3D P86P87  = *sys.new_Vector3D("P86P87a",a87, 0,0,"B86") + *sys.new_Vector3D("P86P87b", 0,0,c87, "B87");
	Vector3D P87P88  = *sys.new_Vector3D("P87P88a",a88, 0,0,"B87") + *sys.new_Vector3D("P87P88b", 0,0,c88, "B88");
	Vector3D P88P89  = *sys.new_Vector3D("P88P89a",a89, 0,0,"B88") + *sys.new_Vector3D("P88P89b", 0,0,c89, "B89");
	Vector3D P89P90  = *sys.new_Vector3D("P89P90a",a90, 0,0,"B89") + *sys.new_Vector3D("P89P90b", 0,0,c90, "B90");
	Vector3D P90P91  = *sys.new_Vector3D("P90P91a",a91, 0,0,"B90") + *sys.new_Vector3D("P90P91b", 0,0,c91, "B91");
	Vector3D P91P92  = *sys.new_Vector3D("P91P92a",a92, 0,0,"B91") + *sys.new_Vector3D("P91P92b", 0,0,c92, "B92");
	Vector3D P92P93  = *sys.new_Vector3D("P92P93a",a93, 0,0,"B92") + *sys.new_Vector3D("P92P93b", 0,0,c93, "B93");
	Vector3D P93P94  = *sys.new_Vector3D("P93P94a",a94, 0,0,"B93") + *sys.new_Vector3D("P93P94b", 0,0,c94, "B94");
	Vector3D P94P95  = *sys.new_Vector3D("P94P95a",a95, 0,0,"B94") + *sys.new_Vector3D("P94P95b", 0,0,c95, "B95");
	Vector3D P95P96  = *sys.new_Vector3D("P95P96a",a96, 0,0,"B95") + *sys.new_Vector3D("P95P96b", 0,0,c96, "B96");
	Vector3D P96P97  = *sys.new_Vector3D("P96P97a",a97, 0,0,"B96") + *sys.new_Vector3D("P96P97b", 0,0,c97, "B97");
	Vector3D P97P98  = *sys.new_Vector3D("P97P98a",a98, 0,0,"B97") + *sys.new_Vector3D("P97P98b", 0,0,c98, "B98");
	Vector3D P98P99  = *sys.new_Vector3D("P98P99a",a99, 0,0,"B98") + *sys.new_Vector3D("P98P99b", 0,0,c99, "B99");
	Vector3D P99P100  = *sys.new_Vector3D("P99P100a",a100, 0,0,"B99") + *sys.new_Vector3D("P99P100b", 0,0,c100, "B100");
	
// ************************************************************************************************
//	Define Points
// ************************************************************************************************
	
	Point * P0 = sys.new_Point("P0","O", &VZERO);

	Point * P1 = sys.new_Point("P1","P0", &P0P1);
	Point * P2 = sys.new_Point("P2","P1", &P1P2);
	Point * P3 = sys.new_Point("P3","P2", &P2P3);
	Point * P4 = sys.new_Point("P4","P3", &P3P4);
	Point * P5 = sys.new_Point("P5","P4", &P4P5);
	Point * P6 = sys.new_Point("P6","P5", &P5P6);
	Point * P7 = sys.new_Point("P7","P6", &P6P7);
	Point * P8 = sys.new_Point("P8","P7", &P7P8);
	Point * P9 = sys.new_Point("P9","P8", &P8P9);
	Point * P10 = sys.new_Point("P10","P9", &P9P10);
	Point * P11 = sys.new_Point("P11","P10", &P10P11);
	Point * P12 = sys.new_Point("P12","P11", &P11P12);
	Point * P13 = sys.new_Point("P13","P12", &P12P13);
	Point * P14 = sys.new_Point("P14","P13", &P13P14);
	Point * P15 = sys.new_Point("P15","P14", &P14P15);
	Point * P16 = sys.new_Point("P16","P15", &P15P16);
	Point * P17 = sys.new_Point("P17","P16", &P16P17);
	Point * P18 = sys.new_Point("P18","P17", &P17P18);
	Point * P19 = sys.new_Point("P19","P18", &P18P19);
	Point * P20 = sys.new_Point("P20","P19", &P19P20);
	Point * P21 = sys.new_Point("P21","P20", &P20P21);
	Point * P22 = sys.new_Point("P22","P21", &P21P22);
	Point * P23 = sys.new_Point("P23","P22", &P22P23);
	Point * P24 = sys.new_Point("P24","P23", &P23P24);
	Point * P25 = sys.new_Point("P25","P24", &P24P25);
	Point * P26 = sys.new_Point("P26","P25", &P25P26);
	Point * P27 = sys.new_Point("P27","P26", &P26P27);
	Point * P28 = sys.new_Point("P28","P27", &P27P28);
	Point * P29 = sys.new_Point("P29","P28", &P28P29);
	Point * P30 = sys.new_Point("P30","P29", &P29P30);
	Point * P31 = sys.new_Point("P31","P30", &P30P31);
	Point * P32 = sys.new_Point("P32","P31", &P31P32);
	Point * P33 = sys.new_Point("P33","P32", &P32P33);
	Point * P34 = sys.new_Point("P34","P33", &P33P34);
	Point * P35 = sys.new_Point("P35","P34", &P34P35);
	Point * P36 = sys.new_Point("P36","P35", &P35P36);
	Point * P37 = sys.new_Point("P37","P36", &P36P37);
	Point * P38 = sys.new_Point("P38","P37", &P37P38);
	Point * P39 = sys.new_Point("P39","P38", &P38P39);
	Point * P40 = sys.new_Point("P40","P39", &P39P40);
	Point * P41 = sys.new_Point("P41","P40", &P40P41);
	Point * P42 = sys.new_Point("P42","P41", &P41P42);
	Point * P43 = sys.new_Point("P43","P42", &P42P43);
	Point * P44 = sys.new_Point("P44","P43", &P43P44);
	Point * P45 = sys.new_Point("P45","P44", &P44P45);
	Point * P46 = sys.new_Point("P46","P45", &P45P46);
	Point * P47 = sys.new_Point("P47","P46", &P46P47);
	Point * P48 = sys.new_Point("P48","P47", &P47P48);
	Point * P49 = sys.new_Point("P49","P48", &P48P49);
	Point * P50 = sys.new_Point("P50","P49", &P49P50);
	Point * P51 = sys.new_Point("P51","P50", &P50P51);
	Point * P52 = sys.new_Point("P52","P51", &P51P52);
	Point * P53 = sys.new_Point("P53","P52", &P52P53);
	Point * P54 = sys.new_Point("P54","P53", &P53P54);
	Point * P55 = sys.new_Point("P55","P54", &P54P55);
	Point * P56 = sys.new_Point("P56","P55", &P55P56);
	Point * P57 = sys.new_Point("P57","P56", &P56P57);
	Point * P58 = sys.new_Point("P58","P57", &P57P58);
	Point * P59 = sys.new_Point("P59","P58", &P58P59);
	Point * P60 = sys.new_Point("P60","P59", &P59P60);
	Point * P61 = sys.new_Point("P61","P60", &P60P61);
	Point * P62 = sys.new_Point("P62","P61", &P61P62);
	Point * P63 = sys.new_Point("P63","P62", &P62P63);
	Point * P64 = sys.new_Point("P64","P63", &P63P64);
	Point * P65 = sys.new_Point("P65","P64", &P64P65);
	Point * P66 = sys.new_Point("P66","P65", &P65P66);
	Point * P67 = sys.new_Point("P67","P66", &P66P67);
	Point * P68 = sys.new_Point("P68","P67", &P67P68);
	Point * P69 = sys.new_Point("P69","P68", &P68P69);
	Point * P70 = sys.new_Point("P70","P69", &P69P70);
	Point * P71 = sys.new_Point("P71","P70", &P70P71);
	Point * P72 = sys.new_Point("P72","P71", &P71P72);
	Point * P73 = sys.new_Point("P73","P72", &P72P73);
	Point * P74 = sys.new_Point("P74","P73", &P73P74);
	Point * P75 = sys.new_Point("P75","P74", &P74P75);
	Point * P76 = sys.new_Point("P76","P75", &P75P76);
	Point * P77 = sys.new_Point("P77","P76", &P76P77);
	Point * P78 = sys.new_Point("P78","P77", &P77P78);
	Point * P79 = sys.new_Point("P79","P78", &P78P79);
	Point * P80 = sys.new_Point("P80","P79", &P79P80);
	Point * P81 = sys.new_Point("P81","P80", &P80P81);
	Point * P82 = sys.new_Point("P82","P81", &P81P82);
	Point * P83 = sys.new_Point("P83","P82", &P82P83);
	Point * P84 = sys.new_Point("P84","P83", &P83P84);
	Point * P85 = sys.new_Point("P85","P84", &P84P85);
	Point * P86 = sys.new_Point("P86","P85", &P85P86);
	Point * P87 = sys.new_Point("P87","P86", &P86P87);
	Point * P88 = sys.new_Point("P88","P87", &P87P88);
	Point * P89 = sys.new_Point("P89","P88", &P88P89);
	Point * P90 = sys.new_Point("P90","P89", &P89P90);
	Point * P91 = sys.new_Point("P91","P90", &P90P91);
	Point * P92 = sys.new_Point("P92","P91", &P91P92);
	Point * P93 = sys.new_Point("P93","P92", &P92P93);
	Point * P94 = sys.new_Point("P94","P93", &P93P94);
	Point * P95 = sys.new_Point("P95","P94", &P94P95);
	Point * P96 = sys.new_Point("P96","P95", &P95P96);
	Point * P97 = sys.new_Point("P97","P96", &P96P97);
	Point * P98 = sys.new_Point("P98","P97", &P97P98);
	Point * P99 = sys.new_Point("P99","P98", &P98P99);
	Point * P100 = sys.new_Point("P100","P99", &P99P100);

// ************************************************************************************************
//	Dynamical Parameter Definition
// ************************************************************************************************

	// Inertial parameters of the Solid 1
	symbol_numeric  m1   = *sys.new_Parameter("m1",  1.0);
	symbol_numeric  mx1  = *sys.new_Parameter("mx1", 0.0);
	symbol_numeric  my1  = *sys.new_Parameter("my1", 0.0);
	symbol_numeric  mz1  = *sys.new_Parameter("mz1", 0.0);
	symbol_numeric  Ixx1 = *sys.new_Parameter("Ixx1",1.0);
	symbol_numeric  Ixy1 = *sys.new_Parameter("Ixy1",0.0);
	symbol_numeric  Ixz1 = *sys.new_Parameter("Ixz1",0.0);
	symbol_numeric  Iyy1 = *sys.new_Parameter("Iyy1",1.0);
	symbol_numeric  Iyz1 = *sys.new_Parameter("Iyz1",0.0);
	symbol_numeric  Izz1 = *sys.new_Parameter("Izz1",1.0);


	// Inertial parameters of the Solid 2
	symbol_numeric  m2   = *sys.new_Parameter("m2",  1.0);
	symbol_numeric  mx2  = *sys.new_Parameter("mx2", 0.0);
	symbol_numeric  my2  = *sys.new_Parameter("my2", 0.0);
	symbol_numeric  mz2  = *sys.new_Parameter("mz2", 0.0);
	symbol_numeric  Ixx2 = *sys.new_Parameter("Ixx2",1.0);
	symbol_numeric  Ixy2 = *sys.new_Parameter("Ixy2",0.0);
	symbol_numeric  Ixz2 = *sys.new_Parameter("Ixz2",0.0);
	symbol_numeric  Iyy2 = *sys.new_Parameter("Iyy2",1.0);
	symbol_numeric  Iyz2 = *sys.new_Parameter("Iyz2",0.0);
	symbol_numeric  Izz2 = *sys.new_Parameter("Izz2",1.0);


	// Inertial parameters of the Solid 3
	symbol_numeric  m3   = *sys.new_Parameter("m3",  1.0);
	symbol_numeric  mx3  = *sys.new_Parameter("mx3", 0.0);
	symbol_numeric  my3  = *sys.new_Parameter("my3", 0.0);
	symbol_numeric  mz3  = *sys.new_Parameter("mz3", 0.0);
	symbol_numeric  Ixx3 = *sys.new_Parameter("Ixx3",1.0);
	symbol_numeric  Ixy3 = *sys.new_Parameter("Ixy3",0.0);
	symbol_numeric  Ixz3 = *sys.new_Parameter("Ixz3",0.0);
	symbol_numeric  Iyy3 = *sys.new_Parameter("Iyy3",1.0);
	symbol_numeric  Iyz3 = *sys.new_Parameter("Iyz3",0.0);
	symbol_numeric  Izz3 = *sys.new_Parameter("Izz3",1.0);


	// Inertial parameters of the Solid 4
	symbol_numeric  m4   = *sys.new_Parameter("m4",  1.0);
	symbol_numeric  mx4  = *sys.new_Parameter("mx4", 0.0);
	symbol_numeric  my4  = *sys.new_Parameter("my4", 0.0);
	symbol_numeric  mz4  = *sys.new_Parameter("mz4", 0.0);
	symbol_numeric  Ixx4 = *sys.new_Parameter("Ixx4",1.0);
	symbol_numeric  Ixy4 = *sys.new_Parameter("Ixy4",0.0);
	symbol_numeric  Ixz4 = *sys.new_Parameter("Ixz4",0.0);
	symbol_numeric  Iyy4 = *sys.new_Parameter("Iyy4",1.0);
	symbol_numeric  Iyz4 = *sys.new_Parameter("Iyz4",0.0);
	symbol_numeric  Izz4 = *sys.new_Parameter("Izz4",1.0);


	// Inertial parameters of the Solid 5
	symbol_numeric  m5   = *sys.new_Parameter("m5",  1.0);
	symbol_numeric  mx5  = *sys.new_Parameter("mx5", 0.0);
	symbol_numeric  my5  = *sys.new_Parameter("my5", 0.0);
	symbol_numeric  mz5  = *sys.new_Parameter("mz5", 0.0);
	symbol_numeric  Ixx5 = *sys.new_Parameter("Ixx5",1.0);
	symbol_numeric  Ixy5 = *sys.new_Parameter("Ixy5",0.0);
	symbol_numeric  Ixz5 = *sys.new_Parameter("Ixz5",0.0);
	symbol_numeric  Iyy5 = *sys.new_Parameter("Iyy5",1.0);
	symbol_numeric  Iyz5 = *sys.new_Parameter("Iyz5",0.0);
	symbol_numeric  Izz5 = *sys.new_Parameter("Izz5",1.0);


	// Inertial parameters of the Solid 6
	symbol_numeric  m6   = *sys.new_Parameter("m6",  1.0);
	symbol_numeric  mx6  = *sys.new_Parameter("mx6", 0.0);
	symbol_numeric  my6  = *sys.new_Parameter("my6", 0.0);
	symbol_numeric  mz6  = *sys.new_Parameter("mz6", 0.0);
	symbol_numeric  Ixx6 = *sys.new_Parameter("Ixx6",1.0);
	symbol_numeric  Ixy6 = *sys.new_Parameter("Ixy6",0.0);
	symbol_numeric  Ixz6 = *sys.new_Parameter("Ixz6",0.0);
	symbol_numeric  Iyy6 = *sys.new_Parameter("Iyy6",1.0);
	symbol_numeric  Iyz6 = *sys.new_Parameter("Iyz6",0.0);
	symbol_numeric  Izz6 = *sys.new_Parameter("Izz6",1.0);


	// Inertial parameters of the Solid 7
	symbol_numeric  m7   = *sys.new_Parameter("m7",  1.0);
	symbol_numeric  mx7  = *sys.new_Parameter("mx7", 0.0);
	symbol_numeric  my7  = *sys.new_Parameter("my7", 0.0);
	symbol_numeric  mz7  = *sys.new_Parameter("mz7", 0.0);
	symbol_numeric  Ixx7 = *sys.new_Parameter("Ixx7",1.0);
	symbol_numeric  Ixy7 = *sys.new_Parameter("Ixy7",0.0);
	symbol_numeric  Ixz7 = *sys.new_Parameter("Ixz7",0.0);
	symbol_numeric  Iyy7 = *sys.new_Parameter("Iyy7",1.0);
	symbol_numeric  Iyz7 = *sys.new_Parameter("Iyz7",0.0);
	symbol_numeric  Izz7 = *sys.new_Parameter("Izz7",1.0);


	// Inertial parameters of the Solid 8
	symbol_numeric  m8   = *sys.new_Parameter("m8",  1.0);
	symbol_numeric  mx8  = *sys.new_Parameter("mx8", 0.0);
	symbol_numeric  my8  = *sys.new_Parameter("my8", 0.0);
	symbol_numeric  mz8  = *sys.new_Parameter("mz8", 0.0);
	symbol_numeric  Ixx8 = *sys.new_Parameter("Ixx8",1.0);
	symbol_numeric  Ixy8 = *sys.new_Parameter("Ixy8",0.0);
	symbol_numeric  Ixz8 = *sys.new_Parameter("Ixz8",0.0);
	symbol_numeric  Iyy8 = *sys.new_Parameter("Iyy8",1.0);
	symbol_numeric  Iyz8 = *sys.new_Parameter("Iyz8",0.0);
	symbol_numeric  Izz8 = *sys.new_Parameter("Izz8",1.0);


	// Inertial parameters of the Solid 9
	symbol_numeric  m9   = *sys.new_Parameter("m9",  1.0);
	symbol_numeric  mx9  = *sys.new_Parameter("mx9", 0.0);
	symbol_numeric  my9  = *sys.new_Parameter("my9", 0.0);
	symbol_numeric  mz9  = *sys.new_Parameter("mz9", 0.0);
	symbol_numeric  Ixx9 = *sys.new_Parameter("Ixx9",1.0);
	symbol_numeric  Ixy9 = *sys.new_Parameter("Ixy9",0.0);
	symbol_numeric  Ixz9 = *sys.new_Parameter("Ixz9",0.0);
	symbol_numeric  Iyy9 = *sys.new_Parameter("Iyy9",1.0);
	symbol_numeric  Iyz9 = *sys.new_Parameter("Iyz9",0.0);
	symbol_numeric  Izz9 = *sys.new_Parameter("Izz9",1.0);


	// Inertial parameters of the Solid 10
	symbol_numeric  m10   = *sys.new_Parameter("m10",  1.0);
	symbol_numeric  mx10  = *sys.new_Parameter("mx10", 0.0);
	symbol_numeric  my10  = *sys.new_Parameter("my10", 0.0);
	symbol_numeric  mz10  = *sys.new_Parameter("mz10", 0.0);
	symbol_numeric  Ixx10 = *sys.new_Parameter("Ixx10",1.0);
	symbol_numeric  Ixy10 = *sys.new_Parameter("Ixy10",0.0);
	symbol_numeric  Ixz10 = *sys.new_Parameter("Ixz10",0.0);
	symbol_numeric  Iyy10 = *sys.new_Parameter("Iyy10",1.0);
	symbol_numeric  Iyz10 = *sys.new_Parameter("Iyz10",0.0);
	symbol_numeric  Izz10 = *sys.new_Parameter("Izz10",1.0);


	// Inertial parameters of the Solid 11
	symbol_numeric  m11   = *sys.new_Parameter("m11",  1.0);
	symbol_numeric  mx11  = *sys.new_Parameter("mx11", 0.0);
	symbol_numeric  my11  = *sys.new_Parameter("my11", 0.0);
	symbol_numeric  mz11  = *sys.new_Parameter("mz11", 0.0);
	symbol_numeric  Ixx11 = *sys.new_Parameter("Ixx11",1.0);
	symbol_numeric  Ixy11 = *sys.new_Parameter("Ixy11",0.0);
	symbol_numeric  Ixz11 = *sys.new_Parameter("Ixz11",0.0);
	symbol_numeric  Iyy11 = *sys.new_Parameter("Iyy11",1.0);
	symbol_numeric  Iyz11 = *sys.new_Parameter("Iyz11",0.0);
	symbol_numeric  Izz11 = *sys.new_Parameter("Izz11",1.0);


	// Inertial parameters of the Solid 12
	symbol_numeric  m12   = *sys.new_Parameter("m12",  1.0);
	symbol_numeric  mx12  = *sys.new_Parameter("mx12", 0.0);
	symbol_numeric  my12  = *sys.new_Parameter("my12", 0.0);
	symbol_numeric  mz12  = *sys.new_Parameter("mz12", 0.0);
	symbol_numeric  Ixx12 = *sys.new_Parameter("Ixx12",1.0);
	symbol_numeric  Ixy12 = *sys.new_Parameter("Ixy12",0.0);
	symbol_numeric  Ixz12 = *sys.new_Parameter("Ixz12",0.0);
	symbol_numeric  Iyy12 = *sys.new_Parameter("Iyy12",1.0);
	symbol_numeric  Iyz12 = *sys.new_Parameter("Iyz12",0.0);
	symbol_numeric  Izz12 = *sys.new_Parameter("Izz12",1.0);


	// Inertial parameters of the Solid 13
	symbol_numeric  m13   = *sys.new_Parameter("m13",  1.0);
	symbol_numeric  mx13  = *sys.new_Parameter("mx13", 0.0);
	symbol_numeric  my13  = *sys.new_Parameter("my13", 0.0);
	symbol_numeric  mz13  = *sys.new_Parameter("mz13", 0.0);
	symbol_numeric  Ixx13 = *sys.new_Parameter("Ixx13",1.0);
	symbol_numeric  Ixy13 = *sys.new_Parameter("Ixy13",0.0);
	symbol_numeric  Ixz13 = *sys.new_Parameter("Ixz13",0.0);
	symbol_numeric  Iyy13 = *sys.new_Parameter("Iyy13",1.0);
	symbol_numeric  Iyz13 = *sys.new_Parameter("Iyz13",0.0);
	symbol_numeric  Izz13 = *sys.new_Parameter("Izz13",1.0);


	// Inertial parameters of the Solid 14
	symbol_numeric  m14   = *sys.new_Parameter("m14",  1.0);
	symbol_numeric  mx14  = *sys.new_Parameter("mx14", 0.0);
	symbol_numeric  my14  = *sys.new_Parameter("my14", 0.0);
	symbol_numeric  mz14  = *sys.new_Parameter("mz14", 0.0);
	symbol_numeric  Ixx14 = *sys.new_Parameter("Ixx14",1.0);
	symbol_numeric  Ixy14 = *sys.new_Parameter("Ixy14",0.0);
	symbol_numeric  Ixz14 = *sys.new_Parameter("Ixz14",0.0);
	symbol_numeric  Iyy14 = *sys.new_Parameter("Iyy14",1.0);
	symbol_numeric  Iyz14 = *sys.new_Parameter("Iyz14",0.0);
	symbol_numeric  Izz14 = *sys.new_Parameter("Izz14",1.0);


	// Inertial parameters of the Solid 15
	symbol_numeric  m15   = *sys.new_Parameter("m15",  1.0);
	symbol_numeric  mx15  = *sys.new_Parameter("mx15", 0.0);
	symbol_numeric  my15  = *sys.new_Parameter("my15", 0.0);
	symbol_numeric  mz15  = *sys.new_Parameter("mz15", 0.0);
	symbol_numeric  Ixx15 = *sys.new_Parameter("Ixx15",1.0);
	symbol_numeric  Ixy15 = *sys.new_Parameter("Ixy15",0.0);
	symbol_numeric  Ixz15 = *sys.new_Parameter("Ixz15",0.0);
	symbol_numeric  Iyy15 = *sys.new_Parameter("Iyy15",1.0);
	symbol_numeric  Iyz15 = *sys.new_Parameter("Iyz15",0.0);
	symbol_numeric  Izz15 = *sys.new_Parameter("Izz15",1.0);


	// Inertial parameters of the Solid 16
	symbol_numeric  m16   = *sys.new_Parameter("m16",  1.0);
	symbol_numeric  mx16  = *sys.new_Parameter("mx16", 0.0);
	symbol_numeric  my16  = *sys.new_Parameter("my16", 0.0);
	symbol_numeric  mz16  = *sys.new_Parameter("mz16", 0.0);
	symbol_numeric  Ixx16 = *sys.new_Parameter("Ixx16",1.0);
	symbol_numeric  Ixy16 = *sys.new_Parameter("Ixy16",0.0);
	symbol_numeric  Ixz16 = *sys.new_Parameter("Ixz16",0.0);
	symbol_numeric  Iyy16 = *sys.new_Parameter("Iyy16",1.0);
	symbol_numeric  Iyz16 = *sys.new_Parameter("Iyz16",0.0);
	symbol_numeric  Izz16 = *sys.new_Parameter("Izz16",1.0);


	// Inertial parameters of the Solid 17
	symbol_numeric  m17   = *sys.new_Parameter("m17",  1.0);
	symbol_numeric  mx17  = *sys.new_Parameter("mx17", 0.0);
	symbol_numeric  my17  = *sys.new_Parameter("my17", 0.0);
	symbol_numeric  mz17  = *sys.new_Parameter("mz17", 0.0);
	symbol_numeric  Ixx17 = *sys.new_Parameter("Ixx17",1.0);
	symbol_numeric  Ixy17 = *sys.new_Parameter("Ixy17",0.0);
	symbol_numeric  Ixz17 = *sys.new_Parameter("Ixz17",0.0);
	symbol_numeric  Iyy17 = *sys.new_Parameter("Iyy17",1.0);
	symbol_numeric  Iyz17 = *sys.new_Parameter("Iyz17",0.0);
	symbol_numeric  Izz17 = *sys.new_Parameter("Izz17",1.0);


	// Inertial parameters of the Solid 18
	symbol_numeric  m18   = *sys.new_Parameter("m18",  1.0);
	symbol_numeric  mx18  = *sys.new_Parameter("mx18", 0.0);
	symbol_numeric  my18  = *sys.new_Parameter("my18", 0.0);
	symbol_numeric  mz18  = *sys.new_Parameter("mz18", 0.0);
	symbol_numeric  Ixx18 = *sys.new_Parameter("Ixx18",1.0);
	symbol_numeric  Ixy18 = *sys.new_Parameter("Ixy18",0.0);
	symbol_numeric  Ixz18 = *sys.new_Parameter("Ixz18",0.0);
	symbol_numeric  Iyy18 = *sys.new_Parameter("Iyy18",1.0);
	symbol_numeric  Iyz18 = *sys.new_Parameter("Iyz18",0.0);
	symbol_numeric  Izz18 = *sys.new_Parameter("Izz18",1.0);


	// Inertial parameters of the Solid 19
	symbol_numeric  m19   = *sys.new_Parameter("m19",  1.0);
	symbol_numeric  mx19  = *sys.new_Parameter("mx19", 0.0);
	symbol_numeric  my19  = *sys.new_Parameter("my19", 0.0);
	symbol_numeric  mz19  = *sys.new_Parameter("mz19", 0.0);
	symbol_numeric  Ixx19 = *sys.new_Parameter("Ixx19",1.0);
	symbol_numeric  Ixy19 = *sys.new_Parameter("Ixy19",0.0);
	symbol_numeric  Ixz19 = *sys.new_Parameter("Ixz19",0.0);
	symbol_numeric  Iyy19 = *sys.new_Parameter("Iyy19",1.0);
	symbol_numeric  Iyz19 = *sys.new_Parameter("Iyz19",0.0);
	symbol_numeric  Izz19 = *sys.new_Parameter("Izz19",1.0);


	// Inertial parameters of the Solid 20
	symbol_numeric  m20   = *sys.new_Parameter("m20",  1.0);
	symbol_numeric  mx20  = *sys.new_Parameter("mx20", 0.0);
	symbol_numeric  my20  = *sys.new_Parameter("my20", 0.0);
	symbol_numeric  mz20  = *sys.new_Parameter("mz20", 0.0);
	symbol_numeric  Ixx20 = *sys.new_Parameter("Ixx20",1.0);
	symbol_numeric  Ixy20 = *sys.new_Parameter("Ixy20",0.0);
	symbol_numeric  Ixz20 = *sys.new_Parameter("Ixz20",0.0);
	symbol_numeric  Iyy20 = *sys.new_Parameter("Iyy20",1.0);
	symbol_numeric  Iyz20 = *sys.new_Parameter("Iyz20",0.0);
	symbol_numeric  Izz20 = *sys.new_Parameter("Izz20",1.0);


	// Inertial parameters of the Solid 21
	symbol_numeric  m21   = *sys.new_Parameter("m21",  1.0);
	symbol_numeric  mx21  = *sys.new_Parameter("mx21", 0.0);
	symbol_numeric  my21  = *sys.new_Parameter("my21", 0.0);
	symbol_numeric  mz21  = *sys.new_Parameter("mz21", 0.0);
	symbol_numeric  Ixx21 = *sys.new_Parameter("Ixx21",1.0);
	symbol_numeric  Ixy21 = *sys.new_Parameter("Ixy21",0.0);
	symbol_numeric  Ixz21 = *sys.new_Parameter("Ixz21",0.0);
	symbol_numeric  Iyy21 = *sys.new_Parameter("Iyy21",1.0);
	symbol_numeric  Iyz21 = *sys.new_Parameter("Iyz21",0.0);
	symbol_numeric  Izz21 = *sys.new_Parameter("Izz21",1.0);


	// Inertial parameters of the Solid 22
	symbol_numeric  m22   = *sys.new_Parameter("m22",  1.0);
	symbol_numeric  mx22  = *sys.new_Parameter("mx22", 0.0);
	symbol_numeric  my22  = *sys.new_Parameter("my22", 0.0);
	symbol_numeric  mz22  = *sys.new_Parameter("mz22", 0.0);
	symbol_numeric  Ixx22 = *sys.new_Parameter("Ixx22",1.0);
	symbol_numeric  Ixy22 = *sys.new_Parameter("Ixy22",0.0);
	symbol_numeric  Ixz22 = *sys.new_Parameter("Ixz22",0.0);
	symbol_numeric  Iyy22 = *sys.new_Parameter("Iyy22",1.0);
	symbol_numeric  Iyz22 = *sys.new_Parameter("Iyz22",0.0);
	symbol_numeric  Izz22 = *sys.new_Parameter("Izz22",1.0);


	// Inertial parameters of the Solid 23
	symbol_numeric  m23   = *sys.new_Parameter("m23",  1.0);
	symbol_numeric  mx23  = *sys.new_Parameter("mx23", 0.0);
	symbol_numeric  my23  = *sys.new_Parameter("my23", 0.0);
	symbol_numeric  mz23  = *sys.new_Parameter("mz23", 0.0);
	symbol_numeric  Ixx23 = *sys.new_Parameter("Ixx23",1.0);
	symbol_numeric  Ixy23 = *sys.new_Parameter("Ixy23",0.0);
	symbol_numeric  Ixz23 = *sys.new_Parameter("Ixz23",0.0);
	symbol_numeric  Iyy23 = *sys.new_Parameter("Iyy23",1.0);
	symbol_numeric  Iyz23 = *sys.new_Parameter("Iyz23",0.0);
	symbol_numeric  Izz23 = *sys.new_Parameter("Izz23",1.0);


	// Inertial parameters of the Solid 24
	symbol_numeric  m24   = *sys.new_Parameter("m24",  1.0);
	symbol_numeric  mx24  = *sys.new_Parameter("mx24", 0.0);
	symbol_numeric  my24  = *sys.new_Parameter("my24", 0.0);
	symbol_numeric  mz24  = *sys.new_Parameter("mz24", 0.0);
	symbol_numeric  Ixx24 = *sys.new_Parameter("Ixx24",1.0);
	symbol_numeric  Ixy24 = *sys.new_Parameter("Ixy24",0.0);
	symbol_numeric  Ixz24 = *sys.new_Parameter("Ixz24",0.0);
	symbol_numeric  Iyy24 = *sys.new_Parameter("Iyy24",1.0);
	symbol_numeric  Iyz24 = *sys.new_Parameter("Iyz24",0.0);
	symbol_numeric  Izz24 = *sys.new_Parameter("Izz24",1.0);


	// Inertial parameters of the Solid 25
	symbol_numeric  m25   = *sys.new_Parameter("m25",  1.0);
	symbol_numeric  mx25  = *sys.new_Parameter("mx25", 0.0);
	symbol_numeric  my25  = *sys.new_Parameter("my25", 0.0);
	symbol_numeric  mz25  = *sys.new_Parameter("mz25", 0.0);
	symbol_numeric  Ixx25 = *sys.new_Parameter("Ixx25",1.0);
	symbol_numeric  Ixy25 = *sys.new_Parameter("Ixy25",0.0);
	symbol_numeric  Ixz25 = *sys.new_Parameter("Ixz25",0.0);
	symbol_numeric  Iyy25 = *sys.new_Parameter("Iyy25",1.0);
	symbol_numeric  Iyz25 = *sys.new_Parameter("Iyz25",0.0);
	symbol_numeric  Izz25 = *sys.new_Parameter("Izz25",1.0);


	// Inertial parameters of the Solid 26
	symbol_numeric  m26   = *sys.new_Parameter("m26",  1.0);
	symbol_numeric  mx26  = *sys.new_Parameter("mx26", 0.0);
	symbol_numeric  my26  = *sys.new_Parameter("my26", 0.0);
	symbol_numeric  mz26  = *sys.new_Parameter("mz26", 0.0);
	symbol_numeric  Ixx26 = *sys.new_Parameter("Ixx26",1.0);
	symbol_numeric  Ixy26 = *sys.new_Parameter("Ixy26",0.0);
	symbol_numeric  Ixz26 = *sys.new_Parameter("Ixz26",0.0);
	symbol_numeric  Iyy26 = *sys.new_Parameter("Iyy26",1.0);
	symbol_numeric  Iyz26 = *sys.new_Parameter("Iyz26",0.0);
	symbol_numeric  Izz26 = *sys.new_Parameter("Izz26",1.0);


	// Inertial parameters of the Solid 27
	symbol_numeric  m27   = *sys.new_Parameter("m27",  1.0);
	symbol_numeric  mx27  = *sys.new_Parameter("mx27", 0.0);
	symbol_numeric  my27  = *sys.new_Parameter("my27", 0.0);
	symbol_numeric  mz27  = *sys.new_Parameter("mz27", 0.0);
	symbol_numeric  Ixx27 = *sys.new_Parameter("Ixx27",1.0);
	symbol_numeric  Ixy27 = *sys.new_Parameter("Ixy27",0.0);
	symbol_numeric  Ixz27 = *sys.new_Parameter("Ixz27",0.0);
	symbol_numeric  Iyy27 = *sys.new_Parameter("Iyy27",1.0);
	symbol_numeric  Iyz27 = *sys.new_Parameter("Iyz27",0.0);
	symbol_numeric  Izz27 = *sys.new_Parameter("Izz27",1.0);


	// Inertial parameters of the Solid 28
	symbol_numeric  m28   = *sys.new_Parameter("m28",  1.0);
	symbol_numeric  mx28  = *sys.new_Parameter("mx28", 0.0);
	symbol_numeric  my28  = *sys.new_Parameter("my28", 0.0);
	symbol_numeric  mz28  = *sys.new_Parameter("mz28", 0.0);
	symbol_numeric  Ixx28 = *sys.new_Parameter("Ixx28",1.0);
	symbol_numeric  Ixy28 = *sys.new_Parameter("Ixy28",0.0);
	symbol_numeric  Ixz28 = *sys.new_Parameter("Ixz28",0.0);
	symbol_numeric  Iyy28 = *sys.new_Parameter("Iyy28",1.0);
	symbol_numeric  Iyz28 = *sys.new_Parameter("Iyz28",0.0);
	symbol_numeric  Izz28 = *sys.new_Parameter("Izz28",1.0);


	// Inertial parameters of the Solid 29
	symbol_numeric  m29   = *sys.new_Parameter("m29",  1.0);
	symbol_numeric  mx29  = *sys.new_Parameter("mx29", 0.0);
	symbol_numeric  my29  = *sys.new_Parameter("my29", 0.0);
	symbol_numeric  mz29  = *sys.new_Parameter("mz29", 0.0);
	symbol_numeric  Ixx29 = *sys.new_Parameter("Ixx29",1.0);
	symbol_numeric  Ixy29 = *sys.new_Parameter("Ixy29",0.0);
	symbol_numeric  Ixz29 = *sys.new_Parameter("Ixz29",0.0);
	symbol_numeric  Iyy29 = *sys.new_Parameter("Iyy29",1.0);
	symbol_numeric  Iyz29 = *sys.new_Parameter("Iyz29",0.0);
	symbol_numeric  Izz29 = *sys.new_Parameter("Izz29",1.0);


	// Inertial parameters of the Solid 30
	symbol_numeric  m30   = *sys.new_Parameter("m30",  1.0);
	symbol_numeric  mx30  = *sys.new_Parameter("mx30", 0.0);
	symbol_numeric  my30  = *sys.new_Parameter("my30", 0.0);
	symbol_numeric  mz30  = *sys.new_Parameter("mz30", 0.0);
	symbol_numeric  Ixx30 = *sys.new_Parameter("Ixx30",1.0);
	symbol_numeric  Ixy30 = *sys.new_Parameter("Ixy30",0.0);
	symbol_numeric  Ixz30 = *sys.new_Parameter("Ixz30",0.0);
	symbol_numeric  Iyy30 = *sys.new_Parameter("Iyy30",1.0);
	symbol_numeric  Iyz30 = *sys.new_Parameter("Iyz30",0.0);
	symbol_numeric  Izz30 = *sys.new_Parameter("Izz30",1.0);


	// Inertial parameters of the Solid 31
	symbol_numeric  m31   = *sys.new_Parameter("m31",  1.0);
	symbol_numeric  mx31  = *sys.new_Parameter("mx31", 0.0);
	symbol_numeric  my31  = *sys.new_Parameter("my31", 0.0);
	symbol_numeric  mz31  = *sys.new_Parameter("mz31", 0.0);
	symbol_numeric  Ixx31 = *sys.new_Parameter("Ixx31",1.0);
	symbol_numeric  Ixy31 = *sys.new_Parameter("Ixy31",0.0);
	symbol_numeric  Ixz31 = *sys.new_Parameter("Ixz31",0.0);
	symbol_numeric  Iyy31 = *sys.new_Parameter("Iyy31",1.0);
	symbol_numeric  Iyz31 = *sys.new_Parameter("Iyz31",0.0);
	symbol_numeric  Izz31 = *sys.new_Parameter("Izz31",1.0);


	// Inertial parameters of the Solid 32
	symbol_numeric  m32   = *sys.new_Parameter("m32",  1.0);
	symbol_numeric  mx32  = *sys.new_Parameter("mx32", 0.0);
	symbol_numeric  my32  = *sys.new_Parameter("my32", 0.0);
	symbol_numeric  mz32  = *sys.new_Parameter("mz32", 0.0);
	symbol_numeric  Ixx32 = *sys.new_Parameter("Ixx32",1.0);
	symbol_numeric  Ixy32 = *sys.new_Parameter("Ixy32",0.0);
	symbol_numeric  Ixz32 = *sys.new_Parameter("Ixz32",0.0);
	symbol_numeric  Iyy32 = *sys.new_Parameter("Iyy32",1.0);
	symbol_numeric  Iyz32 = *sys.new_Parameter("Iyz32",0.0);
	symbol_numeric  Izz32 = *sys.new_Parameter("Izz32",1.0);


	// Inertial parameters of the Solid 33
	symbol_numeric  m33   = *sys.new_Parameter("m33",  1.0);
	symbol_numeric  mx33  = *sys.new_Parameter("mx33", 0.0);
	symbol_numeric  my33  = *sys.new_Parameter("my33", 0.0);
	symbol_numeric  mz33  = *sys.new_Parameter("mz33", 0.0);
	symbol_numeric  Ixx33 = *sys.new_Parameter("Ixx33",1.0);
	symbol_numeric  Ixy33 = *sys.new_Parameter("Ixy33",0.0);
	symbol_numeric  Ixz33 = *sys.new_Parameter("Ixz33",0.0);
	symbol_numeric  Iyy33 = *sys.new_Parameter("Iyy33",1.0);
	symbol_numeric  Iyz33 = *sys.new_Parameter("Iyz33",0.0);
	symbol_numeric  Izz33 = *sys.new_Parameter("Izz33",1.0);


	// Inertial parameters of the Solid 34
	symbol_numeric  m34   = *sys.new_Parameter("m34",  1.0);
	symbol_numeric  mx34  = *sys.new_Parameter("mx34", 0.0);
	symbol_numeric  my34  = *sys.new_Parameter("my34", 0.0);
	symbol_numeric  mz34  = *sys.new_Parameter("mz34", 0.0);
	symbol_numeric  Ixx34 = *sys.new_Parameter("Ixx34",1.0);
	symbol_numeric  Ixy34 = *sys.new_Parameter("Ixy34",0.0);
	symbol_numeric  Ixz34 = *sys.new_Parameter("Ixz34",0.0);
	symbol_numeric  Iyy34 = *sys.new_Parameter("Iyy34",1.0);
	symbol_numeric  Iyz34 = *sys.new_Parameter("Iyz34",0.0);
	symbol_numeric  Izz34 = *sys.new_Parameter("Izz34",1.0);


	// Inertial parameters of the Solid 35
	symbol_numeric  m35   = *sys.new_Parameter("m35",  1.0);
	symbol_numeric  mx35  = *sys.new_Parameter("mx35", 0.0);
	symbol_numeric  my35  = *sys.new_Parameter("my35", 0.0);
	symbol_numeric  mz35  = *sys.new_Parameter("mz35", 0.0);
	symbol_numeric  Ixx35 = *sys.new_Parameter("Ixx35",1.0);
	symbol_numeric  Ixy35 = *sys.new_Parameter("Ixy35",0.0);
	symbol_numeric  Ixz35 = *sys.new_Parameter("Ixz35",0.0);
	symbol_numeric  Iyy35 = *sys.new_Parameter("Iyy35",1.0);
	symbol_numeric  Iyz35 = *sys.new_Parameter("Iyz35",0.0);
	symbol_numeric  Izz35 = *sys.new_Parameter("Izz35",1.0);


	// Inertial parameters of the Solid 36
	symbol_numeric  m36   = *sys.new_Parameter("m36",  1.0);
	symbol_numeric  mx36  = *sys.new_Parameter("mx36", 0.0);
	symbol_numeric  my36  = *sys.new_Parameter("my36", 0.0);
	symbol_numeric  mz36  = *sys.new_Parameter("mz36", 0.0);
	symbol_numeric  Ixx36 = *sys.new_Parameter("Ixx36",1.0);
	symbol_numeric  Ixy36 = *sys.new_Parameter("Ixy36",0.0);
	symbol_numeric  Ixz36 = *sys.new_Parameter("Ixz36",0.0);
	symbol_numeric  Iyy36 = *sys.new_Parameter("Iyy36",1.0);
	symbol_numeric  Iyz36 = *sys.new_Parameter("Iyz36",0.0);
	symbol_numeric  Izz36 = *sys.new_Parameter("Izz36",1.0);


	// Inertial parameters of the Solid 37
	symbol_numeric  m37   = *sys.new_Parameter("m37",  1.0);
	symbol_numeric  mx37  = *sys.new_Parameter("mx37", 0.0);
	symbol_numeric  my37  = *sys.new_Parameter("my37", 0.0);
	symbol_numeric  mz37  = *sys.new_Parameter("mz37", 0.0);
	symbol_numeric  Ixx37 = *sys.new_Parameter("Ixx37",1.0);
	symbol_numeric  Ixy37 = *sys.new_Parameter("Ixy37",0.0);
	symbol_numeric  Ixz37 = *sys.new_Parameter("Ixz37",0.0);
	symbol_numeric  Iyy37 = *sys.new_Parameter("Iyy37",1.0);
	symbol_numeric  Iyz37 = *sys.new_Parameter("Iyz37",0.0);
	symbol_numeric  Izz37 = *sys.new_Parameter("Izz37",1.0);


	// Inertial parameters of the Solid 38
	symbol_numeric  m38   = *sys.new_Parameter("m38",  1.0);
	symbol_numeric  mx38  = *sys.new_Parameter("mx38", 0.0);
	symbol_numeric  my38  = *sys.new_Parameter("my38", 0.0);
	symbol_numeric  mz38  = *sys.new_Parameter("mz38", 0.0);
	symbol_numeric  Ixx38 = *sys.new_Parameter("Ixx38",1.0);
	symbol_numeric  Ixy38 = *sys.new_Parameter("Ixy38",0.0);
	symbol_numeric  Ixz38 = *sys.new_Parameter("Ixz38",0.0);
	symbol_numeric  Iyy38 = *sys.new_Parameter("Iyy38",1.0);
	symbol_numeric  Iyz38 = *sys.new_Parameter("Iyz38",0.0);
	symbol_numeric  Izz38 = *sys.new_Parameter("Izz38",1.0);


	// Inertial parameters of the Solid 39
	symbol_numeric  m39   = *sys.new_Parameter("m39",  1.0);
	symbol_numeric  mx39  = *sys.new_Parameter("mx39", 0.0);
	symbol_numeric  my39  = *sys.new_Parameter("my39", 0.0);
	symbol_numeric  mz39  = *sys.new_Parameter("mz39", 0.0);
	symbol_numeric  Ixx39 = *sys.new_Parameter("Ixx39",1.0);
	symbol_numeric  Ixy39 = *sys.new_Parameter("Ixy39",0.0);
	symbol_numeric  Ixz39 = *sys.new_Parameter("Ixz39",0.0);
	symbol_numeric  Iyy39 = *sys.new_Parameter("Iyy39",1.0);
	symbol_numeric  Iyz39 = *sys.new_Parameter("Iyz39",0.0);
	symbol_numeric  Izz39 = *sys.new_Parameter("Izz39",1.0);


	// Inertial parameters of the Solid 40
	symbol_numeric  m40   = *sys.new_Parameter("m40",  1.0);
	symbol_numeric  mx40  = *sys.new_Parameter("mx40", 0.0);
	symbol_numeric  my40  = *sys.new_Parameter("my40", 0.0);
	symbol_numeric  mz40  = *sys.new_Parameter("mz40", 0.0);
	symbol_numeric  Ixx40 = *sys.new_Parameter("Ixx40",1.0);
	symbol_numeric  Ixy40 = *sys.new_Parameter("Ixy40",0.0);
	symbol_numeric  Ixz40 = *sys.new_Parameter("Ixz40",0.0);
	symbol_numeric  Iyy40 = *sys.new_Parameter("Iyy40",1.0);
	symbol_numeric  Iyz40 = *sys.new_Parameter("Iyz40",0.0);
	symbol_numeric  Izz40 = *sys.new_Parameter("Izz40",1.0);


	// Inertial parameters of the Solid 41
	symbol_numeric  m41   = *sys.new_Parameter("m41",  1.0);
	symbol_numeric  mx41  = *sys.new_Parameter("mx41", 0.0);
	symbol_numeric  my41  = *sys.new_Parameter("my41", 0.0);
	symbol_numeric  mz41  = *sys.new_Parameter("mz41", 0.0);
	symbol_numeric  Ixx41 = *sys.new_Parameter("Ixx41",1.0);
	symbol_numeric  Ixy41 = *sys.new_Parameter("Ixy41",0.0);
	symbol_numeric  Ixz41 = *sys.new_Parameter("Ixz41",0.0);
	symbol_numeric  Iyy41 = *sys.new_Parameter("Iyy41",1.0);
	symbol_numeric  Iyz41 = *sys.new_Parameter("Iyz41",0.0);
	symbol_numeric  Izz41 = *sys.new_Parameter("Izz41",1.0);


	// Inertial parameters of the Solid 42
	symbol_numeric  m42   = *sys.new_Parameter("m42",  1.0);
	symbol_numeric  mx42  = *sys.new_Parameter("mx42", 0.0);
	symbol_numeric  my42  = *sys.new_Parameter("my42", 0.0);
	symbol_numeric  mz42  = *sys.new_Parameter("mz42", 0.0);
	symbol_numeric  Ixx42 = *sys.new_Parameter("Ixx42",1.0);
	symbol_numeric  Ixy42 = *sys.new_Parameter("Ixy42",0.0);
	symbol_numeric  Ixz42 = *sys.new_Parameter("Ixz42",0.0);
	symbol_numeric  Iyy42 = *sys.new_Parameter("Iyy42",1.0);
	symbol_numeric  Iyz42 = *sys.new_Parameter("Iyz42",0.0);
	symbol_numeric  Izz42 = *sys.new_Parameter("Izz42",1.0);


	// Inertial parameters of the Solid 43
	symbol_numeric  m43   = *sys.new_Parameter("m43",  1.0);
	symbol_numeric  mx43  = *sys.new_Parameter("mx43", 0.0);
	symbol_numeric  my43  = *sys.new_Parameter("my43", 0.0);
	symbol_numeric  mz43  = *sys.new_Parameter("mz43", 0.0);
	symbol_numeric  Ixx43 = *sys.new_Parameter("Ixx43",1.0);
	symbol_numeric  Ixy43 = *sys.new_Parameter("Ixy43",0.0);
	symbol_numeric  Ixz43 = *sys.new_Parameter("Ixz43",0.0);
	symbol_numeric  Iyy43 = *sys.new_Parameter("Iyy43",1.0);
	symbol_numeric  Iyz43 = *sys.new_Parameter("Iyz43",0.0);
	symbol_numeric  Izz43 = *sys.new_Parameter("Izz43",1.0);


	// Inertial parameters of the Solid 44
	symbol_numeric  m44   = *sys.new_Parameter("m44",  1.0);
	symbol_numeric  mx44  = *sys.new_Parameter("mx44", 0.0);
	symbol_numeric  my44  = *sys.new_Parameter("my44", 0.0);
	symbol_numeric  mz44  = *sys.new_Parameter("mz44", 0.0);
	symbol_numeric  Ixx44 = *sys.new_Parameter("Ixx44",1.0);
	symbol_numeric  Ixy44 = *sys.new_Parameter("Ixy44",0.0);
	symbol_numeric  Ixz44 = *sys.new_Parameter("Ixz44",0.0);
	symbol_numeric  Iyy44 = *sys.new_Parameter("Iyy44",1.0);
	symbol_numeric  Iyz44 = *sys.new_Parameter("Iyz44",0.0);
	symbol_numeric  Izz44 = *sys.new_Parameter("Izz44",1.0);


	// Inertial parameters of the Solid 45
	symbol_numeric  m45   = *sys.new_Parameter("m45",  1.0);
	symbol_numeric  mx45  = *sys.new_Parameter("mx45", 0.0);
	symbol_numeric  my45  = *sys.new_Parameter("my45", 0.0);
	symbol_numeric  mz45  = *sys.new_Parameter("mz45", 0.0);
	symbol_numeric  Ixx45 = *sys.new_Parameter("Ixx45",1.0);
	symbol_numeric  Ixy45 = *sys.new_Parameter("Ixy45",0.0);
	symbol_numeric  Ixz45 = *sys.new_Parameter("Ixz45",0.0);
	symbol_numeric  Iyy45 = *sys.new_Parameter("Iyy45",1.0);
	symbol_numeric  Iyz45 = *sys.new_Parameter("Iyz45",0.0);
	symbol_numeric  Izz45 = *sys.new_Parameter("Izz45",1.0);


	// Inertial parameters of the Solid 46
	symbol_numeric  m46   = *sys.new_Parameter("m46",  1.0);
	symbol_numeric  mx46  = *sys.new_Parameter("mx46", 0.0);
	symbol_numeric  my46  = *sys.new_Parameter("my46", 0.0);
	symbol_numeric  mz46  = *sys.new_Parameter("mz46", 0.0);
	symbol_numeric  Ixx46 = *sys.new_Parameter("Ixx46",1.0);
	symbol_numeric  Ixy46 = *sys.new_Parameter("Ixy46",0.0);
	symbol_numeric  Ixz46 = *sys.new_Parameter("Ixz46",0.0);
	symbol_numeric  Iyy46 = *sys.new_Parameter("Iyy46",1.0);
	symbol_numeric  Iyz46 = *sys.new_Parameter("Iyz46",0.0);
	symbol_numeric  Izz46 = *sys.new_Parameter("Izz46",1.0);


	// Inertial parameters of the Solid 47
	symbol_numeric  m47   = *sys.new_Parameter("m47",  1.0);
	symbol_numeric  mx47  = *sys.new_Parameter("mx47", 0.0);
	symbol_numeric  my47  = *sys.new_Parameter("my47", 0.0);
	symbol_numeric  mz47  = *sys.new_Parameter("mz47", 0.0);
	symbol_numeric  Ixx47 = *sys.new_Parameter("Ixx47",1.0);
	symbol_numeric  Ixy47 = *sys.new_Parameter("Ixy47",0.0);
	symbol_numeric  Ixz47 = *sys.new_Parameter("Ixz47",0.0);
	symbol_numeric  Iyy47 = *sys.new_Parameter("Iyy47",1.0);
	symbol_numeric  Iyz47 = *sys.new_Parameter("Iyz47",0.0);
	symbol_numeric  Izz47 = *sys.new_Parameter("Izz47",1.0);


	// Inertial parameters of the Solid 48
	symbol_numeric  m48   = *sys.new_Parameter("m48",  1.0);
	symbol_numeric  mx48  = *sys.new_Parameter("mx48", 0.0);
	symbol_numeric  my48  = *sys.new_Parameter("my48", 0.0);
	symbol_numeric  mz48  = *sys.new_Parameter("mz48", 0.0);
	symbol_numeric  Ixx48 = *sys.new_Parameter("Ixx48",1.0);
	symbol_numeric  Ixy48 = *sys.new_Parameter("Ixy48",0.0);
	symbol_numeric  Ixz48 = *sys.new_Parameter("Ixz48",0.0);
	symbol_numeric  Iyy48 = *sys.new_Parameter("Iyy48",1.0);
	symbol_numeric  Iyz48 = *sys.new_Parameter("Iyz48",0.0);
	symbol_numeric  Izz48 = *sys.new_Parameter("Izz48",1.0);


	// Inertial parameters of the Solid 49
	symbol_numeric  m49   = *sys.new_Parameter("m49",  1.0);
	symbol_numeric  mx49  = *sys.new_Parameter("mx49", 0.0);
	symbol_numeric  my49  = *sys.new_Parameter("my49", 0.0);
	symbol_numeric  mz49  = *sys.new_Parameter("mz49", 0.0);
	symbol_numeric  Ixx49 = *sys.new_Parameter("Ixx49",1.0);
	symbol_numeric  Ixy49 = *sys.new_Parameter("Ixy49",0.0);
	symbol_numeric  Ixz49 = *sys.new_Parameter("Ixz49",0.0);
	symbol_numeric  Iyy49 = *sys.new_Parameter("Iyy49",1.0);
	symbol_numeric  Iyz49 = *sys.new_Parameter("Iyz49",0.0);
	symbol_numeric  Izz49 = *sys.new_Parameter("Izz49",1.0);


	// Inertial parameters of the Solid 50
	symbol_numeric  m50   = *sys.new_Parameter("m50",  1.0);
	symbol_numeric  mx50  = *sys.new_Parameter("mx50", 0.0);
	symbol_numeric  my50  = *sys.new_Parameter("my50", 0.0);
	symbol_numeric  mz50  = *sys.new_Parameter("mz50", 0.0);
	symbol_numeric  Ixx50 = *sys.new_Parameter("Ixx50",1.0);
	symbol_numeric  Ixy50 = *sys.new_Parameter("Ixy50",0.0);
	symbol_numeric  Ixz50 = *sys.new_Parameter("Ixz50",0.0);
	symbol_numeric  Iyy50 = *sys.new_Parameter("Iyy50",1.0);
	symbol_numeric  Iyz50 = *sys.new_Parameter("Iyz50",0.0);
	symbol_numeric  Izz50 = *sys.new_Parameter("Izz50",1.0);


	// Inertial parameters of the Solid 51
	symbol_numeric  m51   = *sys.new_Parameter("m51",  1.0);
	symbol_numeric  mx51  = *sys.new_Parameter("mx51", 0.0);
	symbol_numeric  my51  = *sys.new_Parameter("my51", 0.0);
	symbol_numeric  mz51  = *sys.new_Parameter("mz51", 0.0);
	symbol_numeric  Ixx51 = *sys.new_Parameter("Ixx51",1.0);
	symbol_numeric  Ixy51 = *sys.new_Parameter("Ixy51",0.0);
	symbol_numeric  Ixz51 = *sys.new_Parameter("Ixz51",0.0);
	symbol_numeric  Iyy51 = *sys.new_Parameter("Iyy51",1.0);
	symbol_numeric  Iyz51 = *sys.new_Parameter("Iyz51",0.0);
	symbol_numeric  Izz51 = *sys.new_Parameter("Izz51",1.0);


	// Inertial parameters of the Solid 52
	symbol_numeric  m52   = *sys.new_Parameter("m52",  1.0);
	symbol_numeric  mx52  = *sys.new_Parameter("mx52", 0.0);
	symbol_numeric  my52  = *sys.new_Parameter("my52", 0.0);
	symbol_numeric  mz52  = *sys.new_Parameter("mz52", 0.0);
	symbol_numeric  Ixx52 = *sys.new_Parameter("Ixx52",1.0);
	symbol_numeric  Ixy52 = *sys.new_Parameter("Ixy52",0.0);
	symbol_numeric  Ixz52 = *sys.new_Parameter("Ixz52",0.0);
	symbol_numeric  Iyy52 = *sys.new_Parameter("Iyy52",1.0);
	symbol_numeric  Iyz52 = *sys.new_Parameter("Iyz52",0.0);
	symbol_numeric  Izz52 = *sys.new_Parameter("Izz52",1.0);


	// Inertial parameters of the Solid 53
	symbol_numeric  m53   = *sys.new_Parameter("m53",  1.0);
	symbol_numeric  mx53  = *sys.new_Parameter("mx53", 0.0);
	symbol_numeric  my53  = *sys.new_Parameter("my53", 0.0);
	symbol_numeric  mz53  = *sys.new_Parameter("mz53", 0.0);
	symbol_numeric  Ixx53 = *sys.new_Parameter("Ixx53",1.0);
	symbol_numeric  Ixy53 = *sys.new_Parameter("Ixy53",0.0);
	symbol_numeric  Ixz53 = *sys.new_Parameter("Ixz53",0.0);
	symbol_numeric  Iyy53 = *sys.new_Parameter("Iyy53",1.0);
	symbol_numeric  Iyz53 = *sys.new_Parameter("Iyz53",0.0);
	symbol_numeric  Izz53 = *sys.new_Parameter("Izz53",1.0);


	// Inertial parameters of the Solid 54
	symbol_numeric  m54   = *sys.new_Parameter("m54",  1.0);
	symbol_numeric  mx54  = *sys.new_Parameter("mx54", 0.0);
	symbol_numeric  my54  = *sys.new_Parameter("my54", 0.0);
	symbol_numeric  mz54  = *sys.new_Parameter("mz54", 0.0);
	symbol_numeric  Ixx54 = *sys.new_Parameter("Ixx54",1.0);
	symbol_numeric  Ixy54 = *sys.new_Parameter("Ixy54",0.0);
	symbol_numeric  Ixz54 = *sys.new_Parameter("Ixz54",0.0);
	symbol_numeric  Iyy54 = *sys.new_Parameter("Iyy54",1.0);
	symbol_numeric  Iyz54 = *sys.new_Parameter("Iyz54",0.0);
	symbol_numeric  Izz54 = *sys.new_Parameter("Izz54",1.0);


	// Inertial parameters of the Solid 55
	symbol_numeric  m55   = *sys.new_Parameter("m55",  1.0);
	symbol_numeric  mx55  = *sys.new_Parameter("mx55", 0.0);
	symbol_numeric  my55  = *sys.new_Parameter("my55", 0.0);
	symbol_numeric  mz55  = *sys.new_Parameter("mz55", 0.0);
	symbol_numeric  Ixx55 = *sys.new_Parameter("Ixx55",1.0);
	symbol_numeric  Ixy55 = *sys.new_Parameter("Ixy55",0.0);
	symbol_numeric  Ixz55 = *sys.new_Parameter("Ixz55",0.0);
	symbol_numeric  Iyy55 = *sys.new_Parameter("Iyy55",1.0);
	symbol_numeric  Iyz55 = *sys.new_Parameter("Iyz55",0.0);
	symbol_numeric  Izz55 = *sys.new_Parameter("Izz55",1.0);


	// Inertial parameters of the Solid 56
	symbol_numeric  m56   = *sys.new_Parameter("m56",  1.0);
	symbol_numeric  mx56  = *sys.new_Parameter("mx56", 0.0);
	symbol_numeric  my56  = *sys.new_Parameter("my56", 0.0);
	symbol_numeric  mz56  = *sys.new_Parameter("mz56", 0.0);
	symbol_numeric  Ixx56 = *sys.new_Parameter("Ixx56",1.0);
	symbol_numeric  Ixy56 = *sys.new_Parameter("Ixy56",0.0);
	symbol_numeric  Ixz56 = *sys.new_Parameter("Ixz56",0.0);
	symbol_numeric  Iyy56 = *sys.new_Parameter("Iyy56",1.0);
	symbol_numeric  Iyz56 = *sys.new_Parameter("Iyz56",0.0);
	symbol_numeric  Izz56 = *sys.new_Parameter("Izz56",1.0);


	// Inertial parameters of the Solid 57
	symbol_numeric  m57   = *sys.new_Parameter("m57",  1.0);
	symbol_numeric  mx57  = *sys.new_Parameter("mx57", 0.0);
	symbol_numeric  my57  = *sys.new_Parameter("my57", 0.0);
	symbol_numeric  mz57  = *sys.new_Parameter("mz57", 0.0);
	symbol_numeric  Ixx57 = *sys.new_Parameter("Ixx57",1.0);
	symbol_numeric  Ixy57 = *sys.new_Parameter("Ixy57",0.0);
	symbol_numeric  Ixz57 = *sys.new_Parameter("Ixz57",0.0);
	symbol_numeric  Iyy57 = *sys.new_Parameter("Iyy57",1.0);
	symbol_numeric  Iyz57 = *sys.new_Parameter("Iyz57",0.0);
	symbol_numeric  Izz57 = *sys.new_Parameter("Izz57",1.0);


	// Inertial parameters of the Solid 58
	symbol_numeric  m58   = *sys.new_Parameter("m58",  1.0);
	symbol_numeric  mx58  = *sys.new_Parameter("mx58", 0.0);
	symbol_numeric  my58  = *sys.new_Parameter("my58", 0.0);
	symbol_numeric  mz58  = *sys.new_Parameter("mz58", 0.0);
	symbol_numeric  Ixx58 = *sys.new_Parameter("Ixx58",1.0);
	symbol_numeric  Ixy58 = *sys.new_Parameter("Ixy58",0.0);
	symbol_numeric  Ixz58 = *sys.new_Parameter("Ixz58",0.0);
	symbol_numeric  Iyy58 = *sys.new_Parameter("Iyy58",1.0);
	symbol_numeric  Iyz58 = *sys.new_Parameter("Iyz58",0.0);
	symbol_numeric  Izz58 = *sys.new_Parameter("Izz58",1.0);


	// Inertial parameters of the Solid 59
	symbol_numeric  m59   = *sys.new_Parameter("m59",  1.0);
	symbol_numeric  mx59  = *sys.new_Parameter("mx59", 0.0);
	symbol_numeric  my59  = *sys.new_Parameter("my59", 0.0);
	symbol_numeric  mz59  = *sys.new_Parameter("mz59", 0.0);
	symbol_numeric  Ixx59 = *sys.new_Parameter("Ixx59",1.0);
	symbol_numeric  Ixy59 = *sys.new_Parameter("Ixy59",0.0);
	symbol_numeric  Ixz59 = *sys.new_Parameter("Ixz59",0.0);
	symbol_numeric  Iyy59 = *sys.new_Parameter("Iyy59",1.0);
	symbol_numeric  Iyz59 = *sys.new_Parameter("Iyz59",0.0);
	symbol_numeric  Izz59 = *sys.new_Parameter("Izz59",1.0);


	// Inertial parameters of the Solid 60
	symbol_numeric  m60   = *sys.new_Parameter("m60",  1.0);
	symbol_numeric  mx60  = *sys.new_Parameter("mx60", 0.0);
	symbol_numeric  my60  = *sys.new_Parameter("my60", 0.0);
	symbol_numeric  mz60  = *sys.new_Parameter("mz60", 0.0);
	symbol_numeric  Ixx60 = *sys.new_Parameter("Ixx60",1.0);
	symbol_numeric  Ixy60 = *sys.new_Parameter("Ixy60",0.0);
	symbol_numeric  Ixz60 = *sys.new_Parameter("Ixz60",0.0);
	symbol_numeric  Iyy60 = *sys.new_Parameter("Iyy60",1.0);
	symbol_numeric  Iyz60 = *sys.new_Parameter("Iyz60",0.0);
	symbol_numeric  Izz60 = *sys.new_Parameter("Izz60",1.0);


	// Inertial parameters of the Solid 61
	symbol_numeric  m61   = *sys.new_Parameter("m61",  1.0);
	symbol_numeric  mx61  = *sys.new_Parameter("mx61", 0.0);
	symbol_numeric  my61  = *sys.new_Parameter("my61", 0.0);
	symbol_numeric  mz61  = *sys.new_Parameter("mz61", 0.0);
	symbol_numeric  Ixx61 = *sys.new_Parameter("Ixx61",1.0);
	symbol_numeric  Ixy61 = *sys.new_Parameter("Ixy61",0.0);
	symbol_numeric  Ixz61 = *sys.new_Parameter("Ixz61",0.0);
	symbol_numeric  Iyy61 = *sys.new_Parameter("Iyy61",1.0);
	symbol_numeric  Iyz61 = *sys.new_Parameter("Iyz61",0.0);
	symbol_numeric  Izz61 = *sys.new_Parameter("Izz61",1.0);


	// Inertial parameters of the Solid 62
	symbol_numeric  m62   = *sys.new_Parameter("m62",  1.0);
	symbol_numeric  mx62  = *sys.new_Parameter("mx62", 0.0);
	symbol_numeric  my62  = *sys.new_Parameter("my62", 0.0);
	symbol_numeric  mz62  = *sys.new_Parameter("mz62", 0.0);
	symbol_numeric  Ixx62 = *sys.new_Parameter("Ixx62",1.0);
	symbol_numeric  Ixy62 = *sys.new_Parameter("Ixy62",0.0);
	symbol_numeric  Ixz62 = *sys.new_Parameter("Ixz62",0.0);
	symbol_numeric  Iyy62 = *sys.new_Parameter("Iyy62",1.0);
	symbol_numeric  Iyz62 = *sys.new_Parameter("Iyz62",0.0);
	symbol_numeric  Izz62 = *sys.new_Parameter("Izz62",1.0);


	// Inertial parameters of the Solid 63
	symbol_numeric  m63   = *sys.new_Parameter("m63",  1.0);
	symbol_numeric  mx63  = *sys.new_Parameter("mx63", 0.0);
	symbol_numeric  my63  = *sys.new_Parameter("my63", 0.0);
	symbol_numeric  mz63  = *sys.new_Parameter("mz63", 0.0);
	symbol_numeric  Ixx63 = *sys.new_Parameter("Ixx63",1.0);
	symbol_numeric  Ixy63 = *sys.new_Parameter("Ixy63",0.0);
	symbol_numeric  Ixz63 = *sys.new_Parameter("Ixz63",0.0);
	symbol_numeric  Iyy63 = *sys.new_Parameter("Iyy63",1.0);
	symbol_numeric  Iyz63 = *sys.new_Parameter("Iyz63",0.0);
	symbol_numeric  Izz63 = *sys.new_Parameter("Izz63",1.0);


	// Inertial parameters of the Solid 64
	symbol_numeric  m64   = *sys.new_Parameter("m64",  1.0);
	symbol_numeric  mx64  = *sys.new_Parameter("mx64", 0.0);
	symbol_numeric  my64  = *sys.new_Parameter("my64", 0.0);
	symbol_numeric  mz64  = *sys.new_Parameter("mz64", 0.0);
	symbol_numeric  Ixx64 = *sys.new_Parameter("Ixx64",1.0);
	symbol_numeric  Ixy64 = *sys.new_Parameter("Ixy64",0.0);
	symbol_numeric  Ixz64 = *sys.new_Parameter("Ixz64",0.0);
	symbol_numeric  Iyy64 = *sys.new_Parameter("Iyy64",1.0);
	symbol_numeric  Iyz64 = *sys.new_Parameter("Iyz64",0.0);
	symbol_numeric  Izz64 = *sys.new_Parameter("Izz64",1.0);


	// Inertial parameters of the Solid 65
	symbol_numeric  m65   = *sys.new_Parameter("m65",  1.0);
	symbol_numeric  mx65  = *sys.new_Parameter("mx65", 0.0);
	symbol_numeric  my65  = *sys.new_Parameter("my65", 0.0);
	symbol_numeric  mz65  = *sys.new_Parameter("mz65", 0.0);
	symbol_numeric  Ixx65 = *sys.new_Parameter("Ixx65",1.0);
	symbol_numeric  Ixy65 = *sys.new_Parameter("Ixy65",0.0);
	symbol_numeric  Ixz65 = *sys.new_Parameter("Ixz65",0.0);
	symbol_numeric  Iyy65 = *sys.new_Parameter("Iyy65",1.0);
	symbol_numeric  Iyz65 = *sys.new_Parameter("Iyz65",0.0);
	symbol_numeric  Izz65 = *sys.new_Parameter("Izz65",1.0);


	// Inertial parameters of the Solid 66
	symbol_numeric  m66   = *sys.new_Parameter("m66",  1.0);
	symbol_numeric  mx66  = *sys.new_Parameter("mx66", 0.0);
	symbol_numeric  my66  = *sys.new_Parameter("my66", 0.0);
	symbol_numeric  mz66  = *sys.new_Parameter("mz66", 0.0);
	symbol_numeric  Ixx66 = *sys.new_Parameter("Ixx66",1.0);
	symbol_numeric  Ixy66 = *sys.new_Parameter("Ixy66",0.0);
	symbol_numeric  Ixz66 = *sys.new_Parameter("Ixz66",0.0);
	symbol_numeric  Iyy66 = *sys.new_Parameter("Iyy66",1.0);
	symbol_numeric  Iyz66 = *sys.new_Parameter("Iyz66",0.0);
	symbol_numeric  Izz66 = *sys.new_Parameter("Izz66",1.0);


	// Inertial parameters of the Solid 67
	symbol_numeric  m67   = *sys.new_Parameter("m67",  1.0);
	symbol_numeric  mx67  = *sys.new_Parameter("mx67", 0.0);
	symbol_numeric  my67  = *sys.new_Parameter("my67", 0.0);
	symbol_numeric  mz67  = *sys.new_Parameter("mz67", 0.0);
	symbol_numeric  Ixx67 = *sys.new_Parameter("Ixx67",1.0);
	symbol_numeric  Ixy67 = *sys.new_Parameter("Ixy67",0.0);
	symbol_numeric  Ixz67 = *sys.new_Parameter("Ixz67",0.0);
	symbol_numeric  Iyy67 = *sys.new_Parameter("Iyy67",1.0);
	symbol_numeric  Iyz67 = *sys.new_Parameter("Iyz67",0.0);
	symbol_numeric  Izz67 = *sys.new_Parameter("Izz67",1.0);


	// Inertial parameters of the Solid 68
	symbol_numeric  m68   = *sys.new_Parameter("m68",  1.0);
	symbol_numeric  mx68  = *sys.new_Parameter("mx68", 0.0);
	symbol_numeric  my68  = *sys.new_Parameter("my68", 0.0);
	symbol_numeric  mz68  = *sys.new_Parameter("mz68", 0.0);
	symbol_numeric  Ixx68 = *sys.new_Parameter("Ixx68",1.0);
	symbol_numeric  Ixy68 = *sys.new_Parameter("Ixy68",0.0);
	symbol_numeric  Ixz68 = *sys.new_Parameter("Ixz68",0.0);
	symbol_numeric  Iyy68 = *sys.new_Parameter("Iyy68",1.0);
	symbol_numeric  Iyz68 = *sys.new_Parameter("Iyz68",0.0);
	symbol_numeric  Izz68 = *sys.new_Parameter("Izz68",1.0);


	// Inertial parameters of the Solid 69
	symbol_numeric  m69   = *sys.new_Parameter("m69",  1.0);
	symbol_numeric  mx69  = *sys.new_Parameter("mx69", 0.0);
	symbol_numeric  my69  = *sys.new_Parameter("my69", 0.0);
	symbol_numeric  mz69  = *sys.new_Parameter("mz69", 0.0);
	symbol_numeric  Ixx69 = *sys.new_Parameter("Ixx69",1.0);
	symbol_numeric  Ixy69 = *sys.new_Parameter("Ixy69",0.0);
	symbol_numeric  Ixz69 = *sys.new_Parameter("Ixz69",0.0);
	symbol_numeric  Iyy69 = *sys.new_Parameter("Iyy69",1.0);
	symbol_numeric  Iyz69 = *sys.new_Parameter("Iyz69",0.0);
	symbol_numeric  Izz69 = *sys.new_Parameter("Izz69",1.0);


	// Inertial parameters of the Solid 70
	symbol_numeric  m70   = *sys.new_Parameter("m70",  1.0);
	symbol_numeric  mx70  = *sys.new_Parameter("mx70", 0.0);
	symbol_numeric  my70  = *sys.new_Parameter("my70", 0.0);
	symbol_numeric  mz70  = *sys.new_Parameter("mz70", 0.0);
	symbol_numeric  Ixx70 = *sys.new_Parameter("Ixx70",1.0);
	symbol_numeric  Ixy70 = *sys.new_Parameter("Ixy70",0.0);
	symbol_numeric  Ixz70 = *sys.new_Parameter("Ixz70",0.0);
	symbol_numeric  Iyy70 = *sys.new_Parameter("Iyy70",1.0);
	symbol_numeric  Iyz70 = *sys.new_Parameter("Iyz70",0.0);
	symbol_numeric  Izz70 = *sys.new_Parameter("Izz70",1.0);


	// Inertial parameters of the Solid 71
	symbol_numeric  m71   = *sys.new_Parameter("m71",  1.0);
	symbol_numeric  mx71  = *sys.new_Parameter("mx71", 0.0);
	symbol_numeric  my71  = *sys.new_Parameter("my71", 0.0);
	symbol_numeric  mz71  = *sys.new_Parameter("mz71", 0.0);
	symbol_numeric  Ixx71 = *sys.new_Parameter("Ixx71",1.0);
	symbol_numeric  Ixy71 = *sys.new_Parameter("Ixy71",0.0);
	symbol_numeric  Ixz71 = *sys.new_Parameter("Ixz71",0.0);
	symbol_numeric  Iyy71 = *sys.new_Parameter("Iyy71",1.0);
	symbol_numeric  Iyz71 = *sys.new_Parameter("Iyz71",0.0);
	symbol_numeric  Izz71 = *sys.new_Parameter("Izz71",1.0);


	// Inertial parameters of the Solid 72
	symbol_numeric  m72   = *sys.new_Parameter("m72",  1.0);
	symbol_numeric  mx72  = *sys.new_Parameter("mx72", 0.0);
	symbol_numeric  my72  = *sys.new_Parameter("my72", 0.0);
	symbol_numeric  mz72  = *sys.new_Parameter("mz72", 0.0);
	symbol_numeric  Ixx72 = *sys.new_Parameter("Ixx72",1.0);
	symbol_numeric  Ixy72 = *sys.new_Parameter("Ixy72",0.0);
	symbol_numeric  Ixz72 = *sys.new_Parameter("Ixz72",0.0);
	symbol_numeric  Iyy72 = *sys.new_Parameter("Iyy72",1.0);
	symbol_numeric  Iyz72 = *sys.new_Parameter("Iyz72",0.0);
	symbol_numeric  Izz72 = *sys.new_Parameter("Izz72",1.0);


	// Inertial parameters of the Solid 73
	symbol_numeric  m73   = *sys.new_Parameter("m73",  1.0);
	symbol_numeric  mx73  = *sys.new_Parameter("mx73", 0.0);
	symbol_numeric  my73  = *sys.new_Parameter("my73", 0.0);
	symbol_numeric  mz73  = *sys.new_Parameter("mz73", 0.0);
	symbol_numeric  Ixx73 = *sys.new_Parameter("Ixx73",1.0);
	symbol_numeric  Ixy73 = *sys.new_Parameter("Ixy73",0.0);
	symbol_numeric  Ixz73 = *sys.new_Parameter("Ixz73",0.0);
	symbol_numeric  Iyy73 = *sys.new_Parameter("Iyy73",1.0);
	symbol_numeric  Iyz73 = *sys.new_Parameter("Iyz73",0.0);
	symbol_numeric  Izz73 = *sys.new_Parameter("Izz73",1.0);


	// Inertial parameters of the Solid 74
	symbol_numeric  m74   = *sys.new_Parameter("m74",  1.0);
	symbol_numeric  mx74  = *sys.new_Parameter("mx74", 0.0);
	symbol_numeric  my74  = *sys.new_Parameter("my74", 0.0);
	symbol_numeric  mz74  = *sys.new_Parameter("mz74", 0.0);
	symbol_numeric  Ixx74 = *sys.new_Parameter("Ixx74",1.0);
	symbol_numeric  Ixy74 = *sys.new_Parameter("Ixy74",0.0);
	symbol_numeric  Ixz74 = *sys.new_Parameter("Ixz74",0.0);
	symbol_numeric  Iyy74 = *sys.new_Parameter("Iyy74",1.0);
	symbol_numeric  Iyz74 = *sys.new_Parameter("Iyz74",0.0);
	symbol_numeric  Izz74 = *sys.new_Parameter("Izz74",1.0);


	// Inertial parameters of the Solid 75
	symbol_numeric  m75   = *sys.new_Parameter("m75",  1.0);
	symbol_numeric  mx75  = *sys.new_Parameter("mx75", 0.0);
	symbol_numeric  my75  = *sys.new_Parameter("my75", 0.0);
	symbol_numeric  mz75  = *sys.new_Parameter("mz75", 0.0);
	symbol_numeric  Ixx75 = *sys.new_Parameter("Ixx75",1.0);
	symbol_numeric  Ixy75 = *sys.new_Parameter("Ixy75",0.0);
	symbol_numeric  Ixz75 = *sys.new_Parameter("Ixz75",0.0);
	symbol_numeric  Iyy75 = *sys.new_Parameter("Iyy75",1.0);
	symbol_numeric  Iyz75 = *sys.new_Parameter("Iyz75",0.0);
	symbol_numeric  Izz75 = *sys.new_Parameter("Izz75",1.0);


	// Inertial parameters of the Solid 76
	symbol_numeric  m76   = *sys.new_Parameter("m76",  1.0);
	symbol_numeric  mx76  = *sys.new_Parameter("mx76", 0.0);
	symbol_numeric  my76  = *sys.new_Parameter("my76", 0.0);
	symbol_numeric  mz76  = *sys.new_Parameter("mz76", 0.0);
	symbol_numeric  Ixx76 = *sys.new_Parameter("Ixx76",1.0);
	symbol_numeric  Ixy76 = *sys.new_Parameter("Ixy76",0.0);
	symbol_numeric  Ixz76 = *sys.new_Parameter("Ixz76",0.0);
	symbol_numeric  Iyy76 = *sys.new_Parameter("Iyy76",1.0);
	symbol_numeric  Iyz76 = *sys.new_Parameter("Iyz76",0.0);
	symbol_numeric  Izz76 = *sys.new_Parameter("Izz76",1.0);


	// Inertial parameters of the Solid 77
	symbol_numeric  m77   = *sys.new_Parameter("m77",  1.0);
	symbol_numeric  mx77  = *sys.new_Parameter("mx77", 0.0);
	symbol_numeric  my77  = *sys.new_Parameter("my77", 0.0);
	symbol_numeric  mz77  = *sys.new_Parameter("mz77", 0.0);
	symbol_numeric  Ixx77 = *sys.new_Parameter("Ixx77",1.0);
	symbol_numeric  Ixy77 = *sys.new_Parameter("Ixy77",0.0);
	symbol_numeric  Ixz77 = *sys.new_Parameter("Ixz77",0.0);
	symbol_numeric  Iyy77 = *sys.new_Parameter("Iyy77",1.0);
	symbol_numeric  Iyz77 = *sys.new_Parameter("Iyz77",0.0);
	symbol_numeric  Izz77 = *sys.new_Parameter("Izz77",1.0);


	// Inertial parameters of the Solid 78
	symbol_numeric  m78   = *sys.new_Parameter("m78",  1.0);
	symbol_numeric  mx78  = *sys.new_Parameter("mx78", 0.0);
	symbol_numeric  my78  = *sys.new_Parameter("my78", 0.0);
	symbol_numeric  mz78  = *sys.new_Parameter("mz78", 0.0);
	symbol_numeric  Ixx78 = *sys.new_Parameter("Ixx78",1.0);
	symbol_numeric  Ixy78 = *sys.new_Parameter("Ixy78",0.0);
	symbol_numeric  Ixz78 = *sys.new_Parameter("Ixz78",0.0);
	symbol_numeric  Iyy78 = *sys.new_Parameter("Iyy78",1.0);
	symbol_numeric  Iyz78 = *sys.new_Parameter("Iyz78",0.0);
	symbol_numeric  Izz78 = *sys.new_Parameter("Izz78",1.0);


	// Inertial parameters of the Solid 79
	symbol_numeric  m79   = *sys.new_Parameter("m79",  1.0);
	symbol_numeric  mx79  = *sys.new_Parameter("mx79", 0.0);
	symbol_numeric  my79  = *sys.new_Parameter("my79", 0.0);
	symbol_numeric  mz79  = *sys.new_Parameter("mz79", 0.0);
	symbol_numeric  Ixx79 = *sys.new_Parameter("Ixx79",1.0);
	symbol_numeric  Ixy79 = *sys.new_Parameter("Ixy79",0.0);
	symbol_numeric  Ixz79 = *sys.new_Parameter("Ixz79",0.0);
	symbol_numeric  Iyy79 = *sys.new_Parameter("Iyy79",1.0);
	symbol_numeric  Iyz79 = *sys.new_Parameter("Iyz79",0.0);
	symbol_numeric  Izz79 = *sys.new_Parameter("Izz79",1.0);


	// Inertial parameters of the Solid 80
	symbol_numeric  m80   = *sys.new_Parameter("m80",  1.0);
	symbol_numeric  mx80  = *sys.new_Parameter("mx80", 0.0);
	symbol_numeric  my80  = *sys.new_Parameter("my80", 0.0);
	symbol_numeric  mz80  = *sys.new_Parameter("mz80", 0.0);
	symbol_numeric  Ixx80 = *sys.new_Parameter("Ixx80",1.0);
	symbol_numeric  Ixy80 = *sys.new_Parameter("Ixy80",0.0);
	symbol_numeric  Ixz80 = *sys.new_Parameter("Ixz80",0.0);
	symbol_numeric  Iyy80 = *sys.new_Parameter("Iyy80",1.0);
	symbol_numeric  Iyz80 = *sys.new_Parameter("Iyz80",0.0);
	symbol_numeric  Izz80 = *sys.new_Parameter("Izz80",1.0);


	// Inertial parameters of the Solid 81
	symbol_numeric  m81   = *sys.new_Parameter("m81",  1.0);
	symbol_numeric  mx81  = *sys.new_Parameter("mx81", 0.0);
	symbol_numeric  my81  = *sys.new_Parameter("my81", 0.0);
	symbol_numeric  mz81  = *sys.new_Parameter("mz81", 0.0);
	symbol_numeric  Ixx81 = *sys.new_Parameter("Ixx81",1.0);
	symbol_numeric  Ixy81 = *sys.new_Parameter("Ixy81",0.0);
	symbol_numeric  Ixz81 = *sys.new_Parameter("Ixz81",0.0);
	symbol_numeric  Iyy81 = *sys.new_Parameter("Iyy81",1.0);
	symbol_numeric  Iyz81 = *sys.new_Parameter("Iyz81",0.0);
	symbol_numeric  Izz81 = *sys.new_Parameter("Izz81",1.0);


	// Inertial parameters of the Solid 82
	symbol_numeric  m82   = *sys.new_Parameter("m82",  1.0);
	symbol_numeric  mx82  = *sys.new_Parameter("mx82", 0.0);
	symbol_numeric  my82  = *sys.new_Parameter("my82", 0.0);
	symbol_numeric  mz82  = *sys.new_Parameter("mz82", 0.0);
	symbol_numeric  Ixx82 = *sys.new_Parameter("Ixx82",1.0);
	symbol_numeric  Ixy82 = *sys.new_Parameter("Ixy82",0.0);
	symbol_numeric  Ixz82 = *sys.new_Parameter("Ixz82",0.0);
	symbol_numeric  Iyy82 = *sys.new_Parameter("Iyy82",1.0);
	symbol_numeric  Iyz82 = *sys.new_Parameter("Iyz82",0.0);
	symbol_numeric  Izz82 = *sys.new_Parameter("Izz82",1.0);


	// Inertial parameters of the Solid 83
	symbol_numeric  m83   = *sys.new_Parameter("m83",  1.0);
	symbol_numeric  mx83  = *sys.new_Parameter("mx83", 0.0);
	symbol_numeric  my83  = *sys.new_Parameter("my83", 0.0);
	symbol_numeric  mz83  = *sys.new_Parameter("mz83", 0.0);
	symbol_numeric  Ixx83 = *sys.new_Parameter("Ixx83",1.0);
	symbol_numeric  Ixy83 = *sys.new_Parameter("Ixy83",0.0);
	symbol_numeric  Ixz83 = *sys.new_Parameter("Ixz83",0.0);
	symbol_numeric  Iyy83 = *sys.new_Parameter("Iyy83",1.0);
	symbol_numeric  Iyz83 = *sys.new_Parameter("Iyz83",0.0);
	symbol_numeric  Izz83 = *sys.new_Parameter("Izz83",1.0);


	// Inertial parameters of the Solid 84
	symbol_numeric  m84   = *sys.new_Parameter("m84",  1.0);
	symbol_numeric  mx84  = *sys.new_Parameter("mx84", 0.0);
	symbol_numeric  my84  = *sys.new_Parameter("my84", 0.0);
	symbol_numeric  mz84  = *sys.new_Parameter("mz84", 0.0);
	symbol_numeric  Ixx84 = *sys.new_Parameter("Ixx84",1.0);
	symbol_numeric  Ixy84 = *sys.new_Parameter("Ixy84",0.0);
	symbol_numeric  Ixz84 = *sys.new_Parameter("Ixz84",0.0);
	symbol_numeric  Iyy84 = *sys.new_Parameter("Iyy84",1.0);
	symbol_numeric  Iyz84 = *sys.new_Parameter("Iyz84",0.0);
	symbol_numeric  Izz84 = *sys.new_Parameter("Izz84",1.0);


	// Inertial parameters of the Solid 85
	symbol_numeric  m85   = *sys.new_Parameter("m85",  1.0);
	symbol_numeric  mx85  = *sys.new_Parameter("mx85", 0.0);
	symbol_numeric  my85  = *sys.new_Parameter("my85", 0.0);
	symbol_numeric  mz85  = *sys.new_Parameter("mz85", 0.0);
	symbol_numeric  Ixx85 = *sys.new_Parameter("Ixx85",1.0);
	symbol_numeric  Ixy85 = *sys.new_Parameter("Ixy85",0.0);
	symbol_numeric  Ixz85 = *sys.new_Parameter("Ixz85",0.0);
	symbol_numeric  Iyy85 = *sys.new_Parameter("Iyy85",1.0);
	symbol_numeric  Iyz85 = *sys.new_Parameter("Iyz85",0.0);
	symbol_numeric  Izz85 = *sys.new_Parameter("Izz85",1.0);


	// Inertial parameters of the Solid 86
	symbol_numeric  m86   = *sys.new_Parameter("m86",  1.0);
	symbol_numeric  mx86  = *sys.new_Parameter("mx86", 0.0);
	symbol_numeric  my86  = *sys.new_Parameter("my86", 0.0);
	symbol_numeric  mz86  = *sys.new_Parameter("mz86", 0.0);
	symbol_numeric  Ixx86 = *sys.new_Parameter("Ixx86",1.0);
	symbol_numeric  Ixy86 = *sys.new_Parameter("Ixy86",0.0);
	symbol_numeric  Ixz86 = *sys.new_Parameter("Ixz86",0.0);
	symbol_numeric  Iyy86 = *sys.new_Parameter("Iyy86",1.0);
	symbol_numeric  Iyz86 = *sys.new_Parameter("Iyz86",0.0);
	symbol_numeric  Izz86 = *sys.new_Parameter("Izz86",1.0);


	// Inertial parameters of the Solid 87
	symbol_numeric  m87   = *sys.new_Parameter("m87",  1.0);
	symbol_numeric  mx87  = *sys.new_Parameter("mx87", 0.0);
	symbol_numeric  my87  = *sys.new_Parameter("my87", 0.0);
	symbol_numeric  mz87  = *sys.new_Parameter("mz87", 0.0);
	symbol_numeric  Ixx87 = *sys.new_Parameter("Ixx87",1.0);
	symbol_numeric  Ixy87 = *sys.new_Parameter("Ixy87",0.0);
	symbol_numeric  Ixz87 = *sys.new_Parameter("Ixz87",0.0);
	symbol_numeric  Iyy87 = *sys.new_Parameter("Iyy87",1.0);
	symbol_numeric  Iyz87 = *sys.new_Parameter("Iyz87",0.0);
	symbol_numeric  Izz87 = *sys.new_Parameter("Izz87",1.0);


	// Inertial parameters of the Solid 88
	symbol_numeric  m88   = *sys.new_Parameter("m88",  1.0);
	symbol_numeric  mx88  = *sys.new_Parameter("mx88", 0.0);
	symbol_numeric  my88  = *sys.new_Parameter("my88", 0.0);
	symbol_numeric  mz88  = *sys.new_Parameter("mz88", 0.0);
	symbol_numeric  Ixx88 = *sys.new_Parameter("Ixx88",1.0);
	symbol_numeric  Ixy88 = *sys.new_Parameter("Ixy88",0.0);
	symbol_numeric  Ixz88 = *sys.new_Parameter("Ixz88",0.0);
	symbol_numeric  Iyy88 = *sys.new_Parameter("Iyy88",1.0);
	symbol_numeric  Iyz88 = *sys.new_Parameter("Iyz88",0.0);
	symbol_numeric  Izz88 = *sys.new_Parameter("Izz88",1.0);


	// Inertial parameters of the Solid 89
	symbol_numeric  m89   = *sys.new_Parameter("m89",  1.0);
	symbol_numeric  mx89  = *sys.new_Parameter("mx89", 0.0);
	symbol_numeric  my89  = *sys.new_Parameter("my89", 0.0);
	symbol_numeric  mz89  = *sys.new_Parameter("mz89", 0.0);
	symbol_numeric  Ixx89 = *sys.new_Parameter("Ixx89",1.0);
	symbol_numeric  Ixy89 = *sys.new_Parameter("Ixy89",0.0);
	symbol_numeric  Ixz89 = *sys.new_Parameter("Ixz89",0.0);
	symbol_numeric  Iyy89 = *sys.new_Parameter("Iyy89",1.0);
	symbol_numeric  Iyz89 = *sys.new_Parameter("Iyz89",0.0);
	symbol_numeric  Izz89 = *sys.new_Parameter("Izz89",1.0);


	// Inertial parameters of the Solid 90
	symbol_numeric  m90   = *sys.new_Parameter("m90",  1.0);
	symbol_numeric  mx90  = *sys.new_Parameter("mx90", 0.0);
	symbol_numeric  my90  = *sys.new_Parameter("my90", 0.0);
	symbol_numeric  mz90  = *sys.new_Parameter("mz90", 0.0);
	symbol_numeric  Ixx90 = *sys.new_Parameter("Ixx90",1.0);
	symbol_numeric  Ixy90 = *sys.new_Parameter("Ixy90",0.0);
	symbol_numeric  Ixz90 = *sys.new_Parameter("Ixz90",0.0);
	symbol_numeric  Iyy90 = *sys.new_Parameter("Iyy90",1.0);
	symbol_numeric  Iyz90 = *sys.new_Parameter("Iyz90",0.0);
	symbol_numeric  Izz90 = *sys.new_Parameter("Izz90",1.0);


	// Inertial parameters of the Solid 91
	symbol_numeric  m91   = *sys.new_Parameter("m91",  1.0);
	symbol_numeric  mx91  = *sys.new_Parameter("mx91", 0.0);
	symbol_numeric  my91  = *sys.new_Parameter("my91", 0.0);
	symbol_numeric  mz91  = *sys.new_Parameter("mz91", 0.0);
	symbol_numeric  Ixx91 = *sys.new_Parameter("Ixx91",1.0);
	symbol_numeric  Ixy91 = *sys.new_Parameter("Ixy91",0.0);
	symbol_numeric  Ixz91 = *sys.new_Parameter("Ixz91",0.0);
	symbol_numeric  Iyy91 = *sys.new_Parameter("Iyy91",1.0);
	symbol_numeric  Iyz91 = *sys.new_Parameter("Iyz91",0.0);
	symbol_numeric  Izz91 = *sys.new_Parameter("Izz91",1.0);


	// Inertial parameters of the Solid 92
	symbol_numeric  m92   = *sys.new_Parameter("m92",  1.0);
	symbol_numeric  mx92  = *sys.new_Parameter("mx92", 0.0);
	symbol_numeric  my92  = *sys.new_Parameter("my92", 0.0);
	symbol_numeric  mz92  = *sys.new_Parameter("mz92", 0.0);
	symbol_numeric  Ixx92 = *sys.new_Parameter("Ixx92",1.0);
	symbol_numeric  Ixy92 = *sys.new_Parameter("Ixy92",0.0);
	symbol_numeric  Ixz92 = *sys.new_Parameter("Ixz92",0.0);
	symbol_numeric  Iyy92 = *sys.new_Parameter("Iyy92",1.0);
	symbol_numeric  Iyz92 = *sys.new_Parameter("Iyz92",0.0);
	symbol_numeric  Izz92 = *sys.new_Parameter("Izz92",1.0);


	// Inertial parameters of the Solid 93
	symbol_numeric  m93   = *sys.new_Parameter("m93",  1.0);
	symbol_numeric  mx93  = *sys.new_Parameter("mx93", 0.0);
	symbol_numeric  my93  = *sys.new_Parameter("my93", 0.0);
	symbol_numeric  mz93  = *sys.new_Parameter("mz93", 0.0);
	symbol_numeric  Ixx93 = *sys.new_Parameter("Ixx93",1.0);
	symbol_numeric  Ixy93 = *sys.new_Parameter("Ixy93",0.0);
	symbol_numeric  Ixz93 = *sys.new_Parameter("Ixz93",0.0);
	symbol_numeric  Iyy93 = *sys.new_Parameter("Iyy93",1.0);
	symbol_numeric  Iyz93 = *sys.new_Parameter("Iyz93",0.0);
	symbol_numeric  Izz93 = *sys.new_Parameter("Izz93",1.0);


	// Inertial parameters of the Solid 94
	symbol_numeric  m94   = *sys.new_Parameter("m94",  1.0);
	symbol_numeric  mx94  = *sys.new_Parameter("mx94", 0.0);
	symbol_numeric  my94  = *sys.new_Parameter("my94", 0.0);
	symbol_numeric  mz94  = *sys.new_Parameter("mz94", 0.0);
	symbol_numeric  Ixx94 = *sys.new_Parameter("Ixx94",1.0);
	symbol_numeric  Ixy94 = *sys.new_Parameter("Ixy94",0.0);
	symbol_numeric  Ixz94 = *sys.new_Parameter("Ixz94",0.0);
	symbol_numeric  Iyy94 = *sys.new_Parameter("Iyy94",1.0);
	symbol_numeric  Iyz94 = *sys.new_Parameter("Iyz94",0.0);
	symbol_numeric  Izz94 = *sys.new_Parameter("Izz94",1.0);


	// Inertial parameters of the Solid 95
	symbol_numeric  m95   = *sys.new_Parameter("m95",  1.0);
	symbol_numeric  mx95  = *sys.new_Parameter("mx95", 0.0);
	symbol_numeric  my95  = *sys.new_Parameter("my95", 0.0);
	symbol_numeric  mz95  = *sys.new_Parameter("mz95", 0.0);
	symbol_numeric  Ixx95 = *sys.new_Parameter("Ixx95",1.0);
	symbol_numeric  Ixy95 = *sys.new_Parameter("Ixy95",0.0);
	symbol_numeric  Ixz95 = *sys.new_Parameter("Ixz95",0.0);
	symbol_numeric  Iyy95 = *sys.new_Parameter("Iyy95",1.0);
	symbol_numeric  Iyz95 = *sys.new_Parameter("Iyz95",0.0);
	symbol_numeric  Izz95 = *sys.new_Parameter("Izz95",1.0);


	// Inertial parameters of the Solid 96
	symbol_numeric  m96   = *sys.new_Parameter("m96",  1.0);
	symbol_numeric  mx96  = *sys.new_Parameter("mx96", 0.0);
	symbol_numeric  my96  = *sys.new_Parameter("my96", 0.0);
	symbol_numeric  mz96  = *sys.new_Parameter("mz96", 0.0);
	symbol_numeric  Ixx96 = *sys.new_Parameter("Ixx96",1.0);
	symbol_numeric  Ixy96 = *sys.new_Parameter("Ixy96",0.0);
	symbol_numeric  Ixz96 = *sys.new_Parameter("Ixz96",0.0);
	symbol_numeric  Iyy96 = *sys.new_Parameter("Iyy96",1.0);
	symbol_numeric  Iyz96 = *sys.new_Parameter("Iyz96",0.0);
	symbol_numeric  Izz96 = *sys.new_Parameter("Izz96",1.0);


	// Inertial parameters of the Solid 97
	symbol_numeric  m97   = *sys.new_Parameter("m97",  1.0);
	symbol_numeric  mx97  = *sys.new_Parameter("mx97", 0.0);
	symbol_numeric  my97  = *sys.new_Parameter("my97", 0.0);
	symbol_numeric  mz97  = *sys.new_Parameter("mz97", 0.0);
	symbol_numeric  Ixx97 = *sys.new_Parameter("Ixx97",1.0);
	symbol_numeric  Ixy97 = *sys.new_Parameter("Ixy97",0.0);
	symbol_numeric  Ixz97 = *sys.new_Parameter("Ixz97",0.0);
	symbol_numeric  Iyy97 = *sys.new_Parameter("Iyy97",1.0);
	symbol_numeric  Iyz97 = *sys.new_Parameter("Iyz97",0.0);
	symbol_numeric  Izz97 = *sys.new_Parameter("Izz97",1.0);


	// Inertial parameters of the Solid 98
	symbol_numeric  m98   = *sys.new_Parameter("m98",  1.0);
	symbol_numeric  mx98  = *sys.new_Parameter("mx98", 0.0);
	symbol_numeric  my98  = *sys.new_Parameter("my98", 0.0);
	symbol_numeric  mz98  = *sys.new_Parameter("mz98", 0.0);
	symbol_numeric  Ixx98 = *sys.new_Parameter("Ixx98",1.0);
	symbol_numeric  Ixy98 = *sys.new_Parameter("Ixy98",0.0);
	symbol_numeric  Ixz98 = *sys.new_Parameter("Ixz98",0.0);
	symbol_numeric  Iyy98 = *sys.new_Parameter("Iyy98",1.0);
	symbol_numeric  Iyz98 = *sys.new_Parameter("Iyz98",0.0);
	symbol_numeric  Izz98 = *sys.new_Parameter("Izz98",1.0);


	// Inertial parameters of the Solid 99
	symbol_numeric  m99   = *sys.new_Parameter("m99",  1.0);
	symbol_numeric  mx99  = *sys.new_Parameter("mx99", 0.0);
	symbol_numeric  my99  = *sys.new_Parameter("my99", 0.0);
	symbol_numeric  mz99  = *sys.new_Parameter("mz99", 0.0);
	symbol_numeric  Ixx99 = *sys.new_Parameter("Ixx99",1.0);
	symbol_numeric  Ixy99 = *sys.new_Parameter("Ixy99",0.0);
	symbol_numeric  Ixz99 = *sys.new_Parameter("Ixz99",0.0);
	symbol_numeric  Iyy99 = *sys.new_Parameter("Iyy99",1.0);
	symbol_numeric  Iyz99 = *sys.new_Parameter("Iyz99",0.0);
	symbol_numeric  Izz99 = *sys.new_Parameter("Izz99",1.0);


	// Inertial parameters of the Solid 100
	symbol_numeric  m100   = *sys.new_Parameter("m100",  1.0);
	symbol_numeric  mx100  = *sys.new_Parameter("mx100", 0.0);
	symbol_numeric  my100  = *sys.new_Parameter("my100", 0.0);
	symbol_numeric  mz100  = *sys.new_Parameter("mz100", 0.0);
	symbol_numeric  Ixx100 = *sys.new_Parameter("Ixx100",1.0);
	symbol_numeric  Ixy100 = *sys.new_Parameter("Ixy100",0.0);
	symbol_numeric  Ixz100 = *sys.new_Parameter("Ixz100",0.0);
	symbol_numeric  Iyy100 = *sys.new_Parameter("Iyy100",1.0);
	symbol_numeric  Iyz100 = *sys.new_Parameter("Iyz100",0.0);
	symbol_numeric  Izz100 = *sys.new_Parameter("Izz100",1.0);


// ************************************************************************************************
//	Center of Gravity Vectors
// ************************************************************************************************

	Vector3D P1G1= *sys.new_Vector3D("P1G1",mx1/m1,my1/m1,mz1/m1,"B1");
	Vector3D P2G2= *sys.new_Vector3D("P2G2",mx2/m2,my2/m2,mz2/m2,"B2");
	Vector3D P3G3= *sys.new_Vector3D("P3G3",mx3/m3,my3/m3,mz3/m3,"B3");
	Vector3D P4G4= *sys.new_Vector3D("P4G4",mx4/m4,my4/m4,mz4/m4,"B4");
	Vector3D P5G5= *sys.new_Vector3D("P5G5",mx5/m5,my5/m5,mz5/m5,"B5");
	Vector3D P6G6= *sys.new_Vector3D("P6G6",mx6/m6,my6/m6,mz6/m6,"B6");
	Vector3D P7G7= *sys.new_Vector3D("P7G7",mx7/m7,my7/m7,mz7/m7,"B7");
	Vector3D P8G8= *sys.new_Vector3D("P8G8",mx8/m8,my8/m8,mz8/m8,"B8");
	Vector3D P9G9= *sys.new_Vector3D("P9G9",mx9/m9,my9/m9,mz9/m9,"B9");
	Vector3D P10G10= *sys.new_Vector3D("P10G10",mx10/m10,my10/m10,mz10/m10,"B10");
	Vector3D P11G11= *sys.new_Vector3D("P11G11",mx11/m11,my11/m11,mz11/m11,"B11");
	Vector3D P12G12= *sys.new_Vector3D("P12G12",mx12/m12,my12/m12,mz12/m12,"B12");
	Vector3D P13G13= *sys.new_Vector3D("P13G13",mx13/m13,my13/m13,mz13/m13,"B13");
	Vector3D P14G14= *sys.new_Vector3D("P14G14",mx14/m14,my14/m14,mz14/m14,"B14");
	Vector3D P15G15= *sys.new_Vector3D("P15G15",mx15/m15,my15/m15,mz15/m15,"B15");
	Vector3D P16G16= *sys.new_Vector3D("P16G16",mx16/m16,my16/m16,mz16/m16,"B16");
	Vector3D P17G17= *sys.new_Vector3D("P17G17",mx17/m17,my17/m17,mz17/m17,"B17");
	Vector3D P18G18= *sys.new_Vector3D("P18G18",mx18/m18,my18/m18,mz18/m18,"B18");
	Vector3D P19G19= *sys.new_Vector3D("P19G19",mx19/m19,my19/m19,mz19/m19,"B19");
	Vector3D P20G20= *sys.new_Vector3D("P20G20",mx20/m20,my20/m20,mz20/m20,"B20");
	Vector3D P21G21= *sys.new_Vector3D("P21G21",mx21/m21,my21/m21,mz21/m21,"B21");
	Vector3D P22G22= *sys.new_Vector3D("P22G22",mx22/m22,my22/m22,mz22/m22,"B22");
	Vector3D P23G23= *sys.new_Vector3D("P23G23",mx23/m23,my23/m23,mz23/m23,"B23");
	Vector3D P24G24= *sys.new_Vector3D("P24G24",mx24/m24,my24/m24,mz24/m24,"B24");
	Vector3D P25G25= *sys.new_Vector3D("P25G25",mx25/m25,my25/m25,mz25/m25,"B25");
	Vector3D P26G26= *sys.new_Vector3D("P26G26",mx26/m26,my26/m26,mz26/m26,"B26");
	Vector3D P27G27= *sys.new_Vector3D("P27G27",mx27/m27,my27/m27,mz27/m27,"B27");
	Vector3D P28G28= *sys.new_Vector3D("P28G28",mx28/m28,my28/m28,mz28/m28,"B28");
	Vector3D P29G29= *sys.new_Vector3D("P29G29",mx29/m29,my29/m29,mz29/m29,"B29");
	Vector3D P30G30= *sys.new_Vector3D("P30G30",mx30/m30,my30/m30,mz30/m30,"B30");
	Vector3D P31G31= *sys.new_Vector3D("P31G31",mx31/m31,my31/m31,mz31/m31,"B31");
	Vector3D P32G32= *sys.new_Vector3D("P32G32",mx32/m32,my32/m32,mz32/m32,"B32");
	Vector3D P33G33= *sys.new_Vector3D("P33G33",mx33/m33,my33/m33,mz33/m33,"B33");
	Vector3D P34G34= *sys.new_Vector3D("P34G34",mx34/m34,my34/m34,mz34/m34,"B34");
	Vector3D P35G35= *sys.new_Vector3D("P35G35",mx35/m35,my35/m35,mz35/m35,"B35");
	Vector3D P36G36= *sys.new_Vector3D("P36G36",mx36/m36,my36/m36,mz36/m36,"B36");
	Vector3D P37G37= *sys.new_Vector3D("P37G37",mx37/m37,my37/m37,mz37/m37,"B37");
	Vector3D P38G38= *sys.new_Vector3D("P38G38",mx38/m38,my38/m38,mz38/m38,"B38");
	Vector3D P39G39= *sys.new_Vector3D("P39G39",mx39/m39,my39/m39,mz39/m39,"B39");
	Vector3D P40G40= *sys.new_Vector3D("P40G40",mx40/m40,my40/m40,mz40/m40,"B40");
	Vector3D P41G41= *sys.new_Vector3D("P41G41",mx41/m41,my41/m41,mz41/m41,"B41");
	Vector3D P42G42= *sys.new_Vector3D("P42G42",mx42/m42,my42/m42,mz42/m42,"B42");
	Vector3D P43G43= *sys.new_Vector3D("P43G43",mx43/m43,my43/m43,mz43/m43,"B43");
	Vector3D P44G44= *sys.new_Vector3D("P44G44",mx44/m44,my44/m44,mz44/m44,"B44");
	Vector3D P45G45= *sys.new_Vector3D("P45G45",mx45/m45,my45/m45,mz45/m45,"B45");
	Vector3D P46G46= *sys.new_Vector3D("P46G46",mx46/m46,my46/m46,mz46/m46,"B46");
	Vector3D P47G47= *sys.new_Vector3D("P47G47",mx47/m47,my47/m47,mz47/m47,"B47");
	Vector3D P48G48= *sys.new_Vector3D("P48G48",mx48/m48,my48/m48,mz48/m48,"B48");
	Vector3D P49G49= *sys.new_Vector3D("P49G49",mx49/m49,my49/m49,mz49/m49,"B49");
	Vector3D P50G50= *sys.new_Vector3D("P50G50",mx50/m50,my50/m50,mz50/m50,"B50");
	Vector3D P51G51= *sys.new_Vector3D("P51G51",mx51/m51,my51/m51,mz51/m51,"B51");
	Vector3D P52G52= *sys.new_Vector3D("P52G52",mx52/m52,my52/m52,mz52/m52,"B52");
	Vector3D P53G53= *sys.new_Vector3D("P53G53",mx53/m53,my53/m53,mz53/m53,"B53");
	Vector3D P54G54= *sys.new_Vector3D("P54G54",mx54/m54,my54/m54,mz54/m54,"B54");
	Vector3D P55G55= *sys.new_Vector3D("P55G55",mx55/m55,my55/m55,mz55/m55,"B55");
	Vector3D P56G56= *sys.new_Vector3D("P56G56",mx56/m56,my56/m56,mz56/m56,"B56");
	Vector3D P57G57= *sys.new_Vector3D("P57G57",mx57/m57,my57/m57,mz57/m57,"B57");
	Vector3D P58G58= *sys.new_Vector3D("P58G58",mx58/m58,my58/m58,mz58/m58,"B58");
	Vector3D P59G59= *sys.new_Vector3D("P59G59",mx59/m59,my59/m59,mz59/m59,"B59");
	Vector3D P60G60= *sys.new_Vector3D("P60G60",mx60/m60,my60/m60,mz60/m60,"B60");
	Vector3D P61G61= *sys.new_Vector3D("P61G61",mx61/m61,my61/m61,mz61/m61,"B61");
	Vector3D P62G62= *sys.new_Vector3D("P62G62",mx62/m62,my62/m62,mz62/m62,"B62");
	Vector3D P63G63= *sys.new_Vector3D("P63G63",mx63/m63,my63/m63,mz63/m63,"B63");
	Vector3D P64G64= *sys.new_Vector3D("P64G64",mx64/m64,my64/m64,mz64/m64,"B64");
	Vector3D P65G65= *sys.new_Vector3D("P65G65",mx65/m65,my65/m65,mz65/m65,"B65");
	Vector3D P66G66= *sys.new_Vector3D("P66G66",mx66/m66,my66/m66,mz66/m66,"B66");
	Vector3D P67G67= *sys.new_Vector3D("P67G67",mx67/m67,my67/m67,mz67/m67,"B67");
	Vector3D P68G68= *sys.new_Vector3D("P68G68",mx68/m68,my68/m68,mz68/m68,"B68");
	Vector3D P69G69= *sys.new_Vector3D("P69G69",mx69/m69,my69/m69,mz69/m69,"B69");
	Vector3D P70G70= *sys.new_Vector3D("P70G70",mx70/m70,my70/m70,mz70/m70,"B70");
	Vector3D P71G71= *sys.new_Vector3D("P71G71",mx71/m71,my71/m71,mz71/m71,"B71");
	Vector3D P72G72= *sys.new_Vector3D("P72G72",mx72/m72,my72/m72,mz72/m72,"B72");
	Vector3D P73G73= *sys.new_Vector3D("P73G73",mx73/m73,my73/m73,mz73/m73,"B73");
	Vector3D P74G74= *sys.new_Vector3D("P74G74",mx74/m74,my74/m74,mz74/m74,"B74");
	Vector3D P75G75= *sys.new_Vector3D("P75G75",mx75/m75,my75/m75,mz75/m75,"B75");
	Vector3D P76G76= *sys.new_Vector3D("P76G76",mx76/m76,my76/m76,mz76/m76,"B76");
	Vector3D P77G77= *sys.new_Vector3D("P77G77",mx77/m77,my77/m77,mz77/m77,"B77");
	Vector3D P78G78= *sys.new_Vector3D("P78G78",mx78/m78,my78/m78,mz78/m78,"B78");
	Vector3D P79G79= *sys.new_Vector3D("P79G79",mx79/m79,my79/m79,mz79/m79,"B79");
	Vector3D P80G80= *sys.new_Vector3D("P80G80",mx80/m80,my80/m80,mz80/m80,"B80");
	Vector3D P81G81= *sys.new_Vector3D("P81G81",mx81/m81,my81/m81,mz81/m81,"B81");
	Vector3D P82G82= *sys.new_Vector3D("P82G82",mx82/m82,my82/m82,mz82/m82,"B82");
	Vector3D P83G83= *sys.new_Vector3D("P83G83",mx83/m83,my83/m83,mz83/m83,"B83");
	Vector3D P84G84= *sys.new_Vector3D("P84G84",mx84/m84,my84/m84,mz84/m84,"B84");
	Vector3D P85G85= *sys.new_Vector3D("P85G85",mx85/m85,my85/m85,mz85/m85,"B85");
	Vector3D P86G86= *sys.new_Vector3D("P86G86",mx86/m86,my86/m86,mz86/m86,"B86");
	Vector3D P87G87= *sys.new_Vector3D("P87G87",mx87/m87,my87/m87,mz87/m87,"B87");
	Vector3D P88G88= *sys.new_Vector3D("P88G88",mx88/m88,my88/m88,mz88/m88,"B88");
	Vector3D P89G89= *sys.new_Vector3D("P89G89",mx89/m89,my89/m89,mz89/m89,"B89");
	Vector3D P90G90= *sys.new_Vector3D("P90G90",mx90/m90,my90/m90,mz90/m90,"B90");
	Vector3D P91G91= *sys.new_Vector3D("P91G91",mx91/m91,my91/m91,mz91/m91,"B91");
	Vector3D P92G92= *sys.new_Vector3D("P92G92",mx92/m92,my92/m92,mz92/m92,"B92");
	Vector3D P93G93= *sys.new_Vector3D("P93G93",mx93/m93,my93/m93,mz93/m93,"B93");
	Vector3D P94G94= *sys.new_Vector3D("P94G94",mx94/m94,my94/m94,mz94/m94,"B94");
	Vector3D P95G95= *sys.new_Vector3D("P95G95",mx95/m95,my95/m95,mz95/m95,"B95");
	Vector3D P96G96= *sys.new_Vector3D("P96G96",mx96/m96,my96/m96,mz96/m96,"B96");
	Vector3D P97G97= *sys.new_Vector3D("P97G97",mx97/m97,my97/m97,mz97/m97,"B97");
	Vector3D P98G98= *sys.new_Vector3D("P98G98",mx98/m98,my98/m98,mz98/m98,"B98");
	Vector3D P99G99= *sys.new_Vector3D("P99G99",mx99/m99,my99/m99,mz99/m99,"B99");
	Vector3D P100G100= *sys.new_Vector3D("P100G100",mx100/m100,my100/m100,mz100/m100,"B100");

// ************************************************************************************************
//	Inertia Tensors
// ************************************************************************************************

    	Tensor3D I1 = *sys.new_Tensor3D("I1",	(ex)Ixx1,(ex)Ixy1,(ex)Ixz1,
						(ex)Ixy1,(ex)Iyy1,(ex)Iyz1,
						(ex)Ixz1,(ex)Iyz1,(ex)Izz1,"B1");
// -----------------------------------------------------------------------
    	Tensor3D I2 = *sys.new_Tensor3D("I2",	(ex)Ixx2,(ex)Ixy2,(ex)Ixz2,
						(ex)Ixy2,(ex)Iyy2,(ex)Iyz2,
						(ex)Ixz2,(ex)Iyz2,(ex)Izz2,"B2");
// -----------------------------------------------------------------------
    	Tensor3D I3 = *sys.new_Tensor3D("I3",	(ex)Ixx3,(ex)Ixy3,(ex)Ixz3,
						(ex)Ixy3,(ex)Iyy3,(ex)Iyz3,
						(ex)Ixz3,(ex)Iyz3,(ex)Izz3,"B3");
// -----------------------------------------------------------------------
    	Tensor3D I4 = *sys.new_Tensor3D("I4",	(ex)Ixx4,(ex)Ixy4,(ex)Ixz4,
						(ex)Ixy4,(ex)Iyy4,(ex)Iyz4,
						(ex)Ixz4,(ex)Iyz4,(ex)Izz4,"B4");
// -----------------------------------------------------------------------
    	Tensor3D I5 = *sys.new_Tensor3D("I5",	(ex)Ixx5,(ex)Ixy5,(ex)Ixz5,
						(ex)Ixy5,(ex)Iyy5,(ex)Iyz5,
						(ex)Ixz5,(ex)Iyz5,(ex)Izz5,"B5");
// -----------------------------------------------------------------------
    	Tensor3D I6 = *sys.new_Tensor3D("I6",	(ex)Ixx6,(ex)Ixy6,(ex)Ixz6,
						(ex)Ixy6,(ex)Iyy6,(ex)Iyz6,
						(ex)Ixz6,(ex)Iyz6,(ex)Izz6,"B6");
// -----------------------------------------------------------------------
    	Tensor3D I7 = *sys.new_Tensor3D("I7",	(ex)Ixx7,(ex)Ixy7,(ex)Ixz7,
						(ex)Ixy7,(ex)Iyy7,(ex)Iyz7,
						(ex)Ixz7,(ex)Iyz7,(ex)Izz7,"B7");
// -----------------------------------------------------------------------
    	Tensor3D I8 = *sys.new_Tensor3D("I8",	(ex)Ixx8,(ex)Ixy8,(ex)Ixz8,
						(ex)Ixy8,(ex)Iyy8,(ex)Iyz8,
						(ex)Ixz8,(ex)Iyz8,(ex)Izz8,"B8");
// -----------------------------------------------------------------------
    	Tensor3D I9 = *sys.new_Tensor3D("I9",	(ex)Ixx9,(ex)Ixy9,(ex)Ixz9,
						(ex)Ixy9,(ex)Iyy9,(ex)Iyz9,
						(ex)Ixz9,(ex)Iyz9,(ex)Izz9,"B9");
// -----------------------------------------------------------------------
    	Tensor3D I10 = *sys.new_Tensor3D("I10",	(ex)Ixx10,(ex)Ixy10,(ex)Ixz10,
						(ex)Ixy10,(ex)Iyy10,(ex)Iyz10,
						(ex)Ixz10,(ex)Iyz10,(ex)Izz10,"B10");
// -----------------------------------------------------------------------
    	Tensor3D I11 = *sys.new_Tensor3D("I11",	(ex)Ixx11,(ex)Ixy11,(ex)Ixz11,
						(ex)Ixy11,(ex)Iyy11,(ex)Iyz11,
						(ex)Ixz11,(ex)Iyz11,(ex)Izz11,"B11");
// -----------------------------------------------------------------------
    	Tensor3D I12 = *sys.new_Tensor3D("I12",	(ex)Ixx12,(ex)Ixy12,(ex)Ixz12,
						(ex)Ixy12,(ex)Iyy12,(ex)Iyz12,
						(ex)Ixz12,(ex)Iyz12,(ex)Izz12,"B12");
// -----------------------------------------------------------------------
    	Tensor3D I13 = *sys.new_Tensor3D("I13",	(ex)Ixx13,(ex)Ixy13,(ex)Ixz13,
						(ex)Ixy13,(ex)Iyy13,(ex)Iyz13,
						(ex)Ixz13,(ex)Iyz13,(ex)Izz13,"B13");
// -----------------------------------------------------------------------
    	Tensor3D I14 = *sys.new_Tensor3D("I14",	(ex)Ixx14,(ex)Ixy14,(ex)Ixz14,
						(ex)Ixy14,(ex)Iyy14,(ex)Iyz14,
						(ex)Ixz14,(ex)Iyz14,(ex)Izz14,"B14");
// -----------------------------------------------------------------------
    	Tensor3D I15 = *sys.new_Tensor3D("I15",	(ex)Ixx15,(ex)Ixy15,(ex)Ixz15,
						(ex)Ixy15,(ex)Iyy15,(ex)Iyz15,
						(ex)Ixz15,(ex)Iyz15,(ex)Izz15,"B15");
// -----------------------------------------------------------------------
    	Tensor3D I16 = *sys.new_Tensor3D("I16",	(ex)Ixx16,(ex)Ixy16,(ex)Ixz16,
						(ex)Ixy16,(ex)Iyy16,(ex)Iyz16,
						(ex)Ixz16,(ex)Iyz16,(ex)Izz16,"B16");
// -----------------------------------------------------------------------
    	Tensor3D I17 = *sys.new_Tensor3D("I17",	(ex)Ixx17,(ex)Ixy17,(ex)Ixz17,
						(ex)Ixy17,(ex)Iyy17,(ex)Iyz17,
						(ex)Ixz17,(ex)Iyz17,(ex)Izz17,"B17");
// -----------------------------------------------------------------------
    	Tensor3D I18 = *sys.new_Tensor3D("I18",	(ex)Ixx18,(ex)Ixy18,(ex)Ixz18,
						(ex)Ixy18,(ex)Iyy18,(ex)Iyz18,
						(ex)Ixz18,(ex)Iyz18,(ex)Izz18,"B18");
// -----------------------------------------------------------------------
    	Tensor3D I19 = *sys.new_Tensor3D("I19",	(ex)Ixx19,(ex)Ixy19,(ex)Ixz19,
						(ex)Ixy19,(ex)Iyy19,(ex)Iyz19,
						(ex)Ixz19,(ex)Iyz19,(ex)Izz19,"B19");
// -----------------------------------------------------------------------
    	Tensor3D I20 = *sys.new_Tensor3D("I20",	(ex)Ixx20,(ex)Ixy20,(ex)Ixz20,
						(ex)Ixy20,(ex)Iyy20,(ex)Iyz20,
						(ex)Ixz20,(ex)Iyz20,(ex)Izz20,"B20");
// -----------------------------------------------------------------------
    	Tensor3D I21 = *sys.new_Tensor3D("I21",	(ex)Ixx21,(ex)Ixy21,(ex)Ixz21,
						(ex)Ixy21,(ex)Iyy21,(ex)Iyz21,
						(ex)Ixz21,(ex)Iyz21,(ex)Izz21,"B21");
// -----------------------------------------------------------------------
    	Tensor3D I22 = *sys.new_Tensor3D("I22",	(ex)Ixx22,(ex)Ixy22,(ex)Ixz22,
						(ex)Ixy22,(ex)Iyy22,(ex)Iyz22,
						(ex)Ixz22,(ex)Iyz22,(ex)Izz22,"B22");
// -----------------------------------------------------------------------
    	Tensor3D I23 = *sys.new_Tensor3D("I23",	(ex)Ixx23,(ex)Ixy23,(ex)Ixz23,
						(ex)Ixy23,(ex)Iyy23,(ex)Iyz23,
						(ex)Ixz23,(ex)Iyz23,(ex)Izz23,"B23");
// -----------------------------------------------------------------------
    	Tensor3D I24 = *sys.new_Tensor3D("I24",	(ex)Ixx24,(ex)Ixy24,(ex)Ixz24,
						(ex)Ixy24,(ex)Iyy24,(ex)Iyz24,
						(ex)Ixz24,(ex)Iyz24,(ex)Izz24,"B24");
// -----------------------------------------------------------------------
    	Tensor3D I25 = *sys.new_Tensor3D("I25",	(ex)Ixx25,(ex)Ixy25,(ex)Ixz25,
						(ex)Ixy25,(ex)Iyy25,(ex)Iyz25,
						(ex)Ixz25,(ex)Iyz25,(ex)Izz25,"B25");
// -----------------------------------------------------------------------
    	Tensor3D I26 = *sys.new_Tensor3D("I26",	(ex)Ixx26,(ex)Ixy26,(ex)Ixz26,
						(ex)Ixy26,(ex)Iyy26,(ex)Iyz26,
						(ex)Ixz26,(ex)Iyz26,(ex)Izz26,"B26");
// -----------------------------------------------------------------------
    	Tensor3D I27 = *sys.new_Tensor3D("I27",	(ex)Ixx27,(ex)Ixy27,(ex)Ixz27,
						(ex)Ixy27,(ex)Iyy27,(ex)Iyz27,
						(ex)Ixz27,(ex)Iyz27,(ex)Izz27,"B27");
// -----------------------------------------------------------------------
    	Tensor3D I28 = *sys.new_Tensor3D("I28",	(ex)Ixx28,(ex)Ixy28,(ex)Ixz28,
						(ex)Ixy28,(ex)Iyy28,(ex)Iyz28,
						(ex)Ixz28,(ex)Iyz28,(ex)Izz28,"B28");
// -----------------------------------------------------------------------
    	Tensor3D I29 = *sys.new_Tensor3D("I29",	(ex)Ixx29,(ex)Ixy29,(ex)Ixz29,
						(ex)Ixy29,(ex)Iyy29,(ex)Iyz29,
						(ex)Ixz29,(ex)Iyz29,(ex)Izz29,"B29");
// -----------------------------------------------------------------------
    	Tensor3D I30 = *sys.new_Tensor3D("I30",	(ex)Ixx30,(ex)Ixy30,(ex)Ixz30,
						(ex)Ixy30,(ex)Iyy30,(ex)Iyz30,
						(ex)Ixz30,(ex)Iyz30,(ex)Izz30,"B30");
// -----------------------------------------------------------------------
    	Tensor3D I31 = *sys.new_Tensor3D("I31",	(ex)Ixx31,(ex)Ixy31,(ex)Ixz31,
						(ex)Ixy31,(ex)Iyy31,(ex)Iyz31,
						(ex)Ixz31,(ex)Iyz31,(ex)Izz31,"B31");
// -----------------------------------------------------------------------
    	Tensor3D I32 = *sys.new_Tensor3D("I32",	(ex)Ixx32,(ex)Ixy32,(ex)Ixz32,
						(ex)Ixy32,(ex)Iyy32,(ex)Iyz32,
						(ex)Ixz32,(ex)Iyz32,(ex)Izz32,"B32");
// -----------------------------------------------------------------------
    	Tensor3D I33 = *sys.new_Tensor3D("I33",	(ex)Ixx33,(ex)Ixy33,(ex)Ixz33,
						(ex)Ixy33,(ex)Iyy33,(ex)Iyz33,
						(ex)Ixz33,(ex)Iyz33,(ex)Izz33,"B33");
// -----------------------------------------------------------------------
    	Tensor3D I34 = *sys.new_Tensor3D("I34",	(ex)Ixx34,(ex)Ixy34,(ex)Ixz34,
						(ex)Ixy34,(ex)Iyy34,(ex)Iyz34,
						(ex)Ixz34,(ex)Iyz34,(ex)Izz34,"B34");
// -----------------------------------------------------------------------
    	Tensor3D I35 = *sys.new_Tensor3D("I35",	(ex)Ixx35,(ex)Ixy35,(ex)Ixz35,
						(ex)Ixy35,(ex)Iyy35,(ex)Iyz35,
						(ex)Ixz35,(ex)Iyz35,(ex)Izz35,"B35");
// -----------------------------------------------------------------------
    	Tensor3D I36 = *sys.new_Tensor3D("I36",	(ex)Ixx36,(ex)Ixy36,(ex)Ixz36,
						(ex)Ixy36,(ex)Iyy36,(ex)Iyz36,
						(ex)Ixz36,(ex)Iyz36,(ex)Izz36,"B36");
// -----------------------------------------------------------------------
    	Tensor3D I37 = *sys.new_Tensor3D("I37",	(ex)Ixx37,(ex)Ixy37,(ex)Ixz37,
						(ex)Ixy37,(ex)Iyy37,(ex)Iyz37,
						(ex)Ixz37,(ex)Iyz37,(ex)Izz37,"B37");
// -----------------------------------------------------------------------
    	Tensor3D I38 = *sys.new_Tensor3D("I38",	(ex)Ixx38,(ex)Ixy38,(ex)Ixz38,
						(ex)Ixy38,(ex)Iyy38,(ex)Iyz38,
						(ex)Ixz38,(ex)Iyz38,(ex)Izz38,"B38");
// -----------------------------------------------------------------------
    	Tensor3D I39 = *sys.new_Tensor3D("I39",	(ex)Ixx39,(ex)Ixy39,(ex)Ixz39,
						(ex)Ixy39,(ex)Iyy39,(ex)Iyz39,
						(ex)Ixz39,(ex)Iyz39,(ex)Izz39,"B39");
// -----------------------------------------------------------------------
    	Tensor3D I40 = *sys.new_Tensor3D("I40",	(ex)Ixx40,(ex)Ixy40,(ex)Ixz40,
						(ex)Ixy40,(ex)Iyy40,(ex)Iyz40,
						(ex)Ixz40,(ex)Iyz40,(ex)Izz40,"B40");
// -----------------------------------------------------------------------
    	Tensor3D I41 = *sys.new_Tensor3D("I41",	(ex)Ixx41,(ex)Ixy41,(ex)Ixz41,
						(ex)Ixy41,(ex)Iyy41,(ex)Iyz41,
						(ex)Ixz41,(ex)Iyz41,(ex)Izz41,"B41");
// -----------------------------------------------------------------------
    	Tensor3D I42 = *sys.new_Tensor3D("I42",	(ex)Ixx42,(ex)Ixy42,(ex)Ixz42,
						(ex)Ixy42,(ex)Iyy42,(ex)Iyz42,
						(ex)Ixz42,(ex)Iyz42,(ex)Izz42,"B42");
// -----------------------------------------------------------------------
    	Tensor3D I43 = *sys.new_Tensor3D("I43",	(ex)Ixx43,(ex)Ixy43,(ex)Ixz43,
						(ex)Ixy43,(ex)Iyy43,(ex)Iyz43,
						(ex)Ixz43,(ex)Iyz43,(ex)Izz43,"B43");
// -----------------------------------------------------------------------
    	Tensor3D I44 = *sys.new_Tensor3D("I44",	(ex)Ixx44,(ex)Ixy44,(ex)Ixz44,
						(ex)Ixy44,(ex)Iyy44,(ex)Iyz44,
						(ex)Ixz44,(ex)Iyz44,(ex)Izz44,"B44");
// -----------------------------------------------------------------------
    	Tensor3D I45 = *sys.new_Tensor3D("I45",	(ex)Ixx45,(ex)Ixy45,(ex)Ixz45,
						(ex)Ixy45,(ex)Iyy45,(ex)Iyz45,
						(ex)Ixz45,(ex)Iyz45,(ex)Izz45,"B45");
// -----------------------------------------------------------------------
    	Tensor3D I46 = *sys.new_Tensor3D("I46",	(ex)Ixx46,(ex)Ixy46,(ex)Ixz46,
						(ex)Ixy46,(ex)Iyy46,(ex)Iyz46,
						(ex)Ixz46,(ex)Iyz46,(ex)Izz46,"B46");
// -----------------------------------------------------------------------
    	Tensor3D I47 = *sys.new_Tensor3D("I47",	(ex)Ixx47,(ex)Ixy47,(ex)Ixz47,
						(ex)Ixy47,(ex)Iyy47,(ex)Iyz47,
						(ex)Ixz47,(ex)Iyz47,(ex)Izz47,"B47");
// -----------------------------------------------------------------------
    	Tensor3D I48 = *sys.new_Tensor3D("I48",	(ex)Ixx48,(ex)Ixy48,(ex)Ixz48,
						(ex)Ixy48,(ex)Iyy48,(ex)Iyz48,
						(ex)Ixz48,(ex)Iyz48,(ex)Izz48,"B48");
// -----------------------------------------------------------------------
    	Tensor3D I49 = *sys.new_Tensor3D("I49",	(ex)Ixx49,(ex)Ixy49,(ex)Ixz49,
						(ex)Ixy49,(ex)Iyy49,(ex)Iyz49,
						(ex)Ixz49,(ex)Iyz49,(ex)Izz49,"B49");
// -----------------------------------------------------------------------
    	Tensor3D I50 = *sys.new_Tensor3D("I50",	(ex)Ixx50,(ex)Ixy50,(ex)Ixz50,
						(ex)Ixy50,(ex)Iyy50,(ex)Iyz50,
						(ex)Ixz50,(ex)Iyz50,(ex)Izz50,"B50");
// -----------------------------------------------------------------------
    	Tensor3D I51 = *sys.new_Tensor3D("I51",	(ex)Ixx51,(ex)Ixy51,(ex)Ixz51,
						(ex)Ixy51,(ex)Iyy51,(ex)Iyz51,
						(ex)Ixz51,(ex)Iyz51,(ex)Izz51,"B51");
// -----------------------------------------------------------------------
    	Tensor3D I52 = *sys.new_Tensor3D("I52",	(ex)Ixx52,(ex)Ixy52,(ex)Ixz52,
						(ex)Ixy52,(ex)Iyy52,(ex)Iyz52,
						(ex)Ixz52,(ex)Iyz52,(ex)Izz52,"B52");
// -----------------------------------------------------------------------
    	Tensor3D I53 = *sys.new_Tensor3D("I53",	(ex)Ixx53,(ex)Ixy53,(ex)Ixz53,
						(ex)Ixy53,(ex)Iyy53,(ex)Iyz53,
						(ex)Ixz53,(ex)Iyz53,(ex)Izz53,"B53");
// -----------------------------------------------------------------------
    	Tensor3D I54 = *sys.new_Tensor3D("I54",	(ex)Ixx54,(ex)Ixy54,(ex)Ixz54,
						(ex)Ixy54,(ex)Iyy54,(ex)Iyz54,
						(ex)Ixz54,(ex)Iyz54,(ex)Izz54,"B54");
// -----------------------------------------------------------------------
    	Tensor3D I55 = *sys.new_Tensor3D("I55",	(ex)Ixx55,(ex)Ixy55,(ex)Ixz55,
						(ex)Ixy55,(ex)Iyy55,(ex)Iyz55,
						(ex)Ixz55,(ex)Iyz55,(ex)Izz55,"B55");
// -----------------------------------------------------------------------
    	Tensor3D I56 = *sys.new_Tensor3D("I56",	(ex)Ixx56,(ex)Ixy56,(ex)Ixz56,
						(ex)Ixy56,(ex)Iyy56,(ex)Iyz56,
						(ex)Ixz56,(ex)Iyz56,(ex)Izz56,"B56");
// -----------------------------------------------------------------------
    	Tensor3D I57 = *sys.new_Tensor3D("I57",	(ex)Ixx57,(ex)Ixy57,(ex)Ixz57,
						(ex)Ixy57,(ex)Iyy57,(ex)Iyz57,
						(ex)Ixz57,(ex)Iyz57,(ex)Izz57,"B57");
// -----------------------------------------------------------------------
    	Tensor3D I58 = *sys.new_Tensor3D("I58",	(ex)Ixx58,(ex)Ixy58,(ex)Ixz58,
						(ex)Ixy58,(ex)Iyy58,(ex)Iyz58,
						(ex)Ixz58,(ex)Iyz58,(ex)Izz58,"B58");
// -----------------------------------------------------------------------
    	Tensor3D I59 = *sys.new_Tensor3D("I59",	(ex)Ixx59,(ex)Ixy59,(ex)Ixz59,
						(ex)Ixy59,(ex)Iyy59,(ex)Iyz59,
						(ex)Ixz59,(ex)Iyz59,(ex)Izz59,"B59");
// -----------------------------------------------------------------------
    	Tensor3D I60 = *sys.new_Tensor3D("I60",	(ex)Ixx60,(ex)Ixy60,(ex)Ixz60,
						(ex)Ixy60,(ex)Iyy60,(ex)Iyz60,
						(ex)Ixz60,(ex)Iyz60,(ex)Izz60,"B60");
// -----------------------------------------------------------------------
    	Tensor3D I61 = *sys.new_Tensor3D("I61",	(ex)Ixx61,(ex)Ixy61,(ex)Ixz61,
						(ex)Ixy61,(ex)Iyy61,(ex)Iyz61,
						(ex)Ixz61,(ex)Iyz61,(ex)Izz61,"B61");
// -----------------------------------------------------------------------
    	Tensor3D I62 = *sys.new_Tensor3D("I62",	(ex)Ixx62,(ex)Ixy62,(ex)Ixz62,
						(ex)Ixy62,(ex)Iyy62,(ex)Iyz62,
						(ex)Ixz62,(ex)Iyz62,(ex)Izz62,"B62");
// -----------------------------------------------------------------------
    	Tensor3D I63 = *sys.new_Tensor3D("I63",	(ex)Ixx63,(ex)Ixy63,(ex)Ixz63,
						(ex)Ixy63,(ex)Iyy63,(ex)Iyz63,
						(ex)Ixz63,(ex)Iyz63,(ex)Izz63,"B63");
// -----------------------------------------------------------------------
    	Tensor3D I64 = *sys.new_Tensor3D("I64",	(ex)Ixx64,(ex)Ixy64,(ex)Ixz64,
						(ex)Ixy64,(ex)Iyy64,(ex)Iyz64,
						(ex)Ixz64,(ex)Iyz64,(ex)Izz64,"B64");
// -----------------------------------------------------------------------
    	Tensor3D I65 = *sys.new_Tensor3D("I65",	(ex)Ixx65,(ex)Ixy65,(ex)Ixz65,
						(ex)Ixy65,(ex)Iyy65,(ex)Iyz65,
						(ex)Ixz65,(ex)Iyz65,(ex)Izz65,"B65");
// -----------------------------------------------------------------------
    	Tensor3D I66 = *sys.new_Tensor3D("I66",	(ex)Ixx66,(ex)Ixy66,(ex)Ixz66,
						(ex)Ixy66,(ex)Iyy66,(ex)Iyz66,
						(ex)Ixz66,(ex)Iyz66,(ex)Izz66,"B66");
// -----------------------------------------------------------------------
    	Tensor3D I67 = *sys.new_Tensor3D("I67",	(ex)Ixx67,(ex)Ixy67,(ex)Ixz67,
						(ex)Ixy67,(ex)Iyy67,(ex)Iyz67,
						(ex)Ixz67,(ex)Iyz67,(ex)Izz67,"B67");
// -----------------------------------------------------------------------
    	Tensor3D I68 = *sys.new_Tensor3D("I68",	(ex)Ixx68,(ex)Ixy68,(ex)Ixz68,
						(ex)Ixy68,(ex)Iyy68,(ex)Iyz68,
						(ex)Ixz68,(ex)Iyz68,(ex)Izz68,"B68");
// -----------------------------------------------------------------------
    	Tensor3D I69 = *sys.new_Tensor3D("I69",	(ex)Ixx69,(ex)Ixy69,(ex)Ixz69,
						(ex)Ixy69,(ex)Iyy69,(ex)Iyz69,
						(ex)Ixz69,(ex)Iyz69,(ex)Izz69,"B69");
// -----------------------------------------------------------------------
    	Tensor3D I70 = *sys.new_Tensor3D("I70",	(ex)Ixx70,(ex)Ixy70,(ex)Ixz70,
						(ex)Ixy70,(ex)Iyy70,(ex)Iyz70,
						(ex)Ixz70,(ex)Iyz70,(ex)Izz70,"B70");
// -----------------------------------------------------------------------
    	Tensor3D I71 = *sys.new_Tensor3D("I71",	(ex)Ixx71,(ex)Ixy71,(ex)Ixz71,
						(ex)Ixy71,(ex)Iyy71,(ex)Iyz71,
						(ex)Ixz71,(ex)Iyz71,(ex)Izz71,"B71");
// -----------------------------------------------------------------------
    	Tensor3D I72 = *sys.new_Tensor3D("I72",	(ex)Ixx72,(ex)Ixy72,(ex)Ixz72,
						(ex)Ixy72,(ex)Iyy72,(ex)Iyz72,
						(ex)Ixz72,(ex)Iyz72,(ex)Izz72,"B72");
// -----------------------------------------------------------------------
    	Tensor3D I73 = *sys.new_Tensor3D("I73",	(ex)Ixx73,(ex)Ixy73,(ex)Ixz73,
						(ex)Ixy73,(ex)Iyy73,(ex)Iyz73,
						(ex)Ixz73,(ex)Iyz73,(ex)Izz73,"B73");
// -----------------------------------------------------------------------
    	Tensor3D I74 = *sys.new_Tensor3D("I74",	(ex)Ixx74,(ex)Ixy74,(ex)Ixz74,
						(ex)Ixy74,(ex)Iyy74,(ex)Iyz74,
						(ex)Ixz74,(ex)Iyz74,(ex)Izz74,"B74");
// -----------------------------------------------------------------------
    	Tensor3D I75 = *sys.new_Tensor3D("I75",	(ex)Ixx75,(ex)Ixy75,(ex)Ixz75,
						(ex)Ixy75,(ex)Iyy75,(ex)Iyz75,
						(ex)Ixz75,(ex)Iyz75,(ex)Izz75,"B75");
// -----------------------------------------------------------------------
    	Tensor3D I76 = *sys.new_Tensor3D("I76",	(ex)Ixx76,(ex)Ixy76,(ex)Ixz76,
						(ex)Ixy76,(ex)Iyy76,(ex)Iyz76,
						(ex)Ixz76,(ex)Iyz76,(ex)Izz76,"B76");
// -----------------------------------------------------------------------
    	Tensor3D I77 = *sys.new_Tensor3D("I77",	(ex)Ixx77,(ex)Ixy77,(ex)Ixz77,
						(ex)Ixy77,(ex)Iyy77,(ex)Iyz77,
						(ex)Ixz77,(ex)Iyz77,(ex)Izz77,"B77");
// -----------------------------------------------------------------------
    	Tensor3D I78 = *sys.new_Tensor3D("I78",	(ex)Ixx78,(ex)Ixy78,(ex)Ixz78,
						(ex)Ixy78,(ex)Iyy78,(ex)Iyz78,
						(ex)Ixz78,(ex)Iyz78,(ex)Izz78,"B78");
// -----------------------------------------------------------------------
    	Tensor3D I79 = *sys.new_Tensor3D("I79",	(ex)Ixx79,(ex)Ixy79,(ex)Ixz79,
						(ex)Ixy79,(ex)Iyy79,(ex)Iyz79,
						(ex)Ixz79,(ex)Iyz79,(ex)Izz79,"B79");
// -----------------------------------------------------------------------
    	Tensor3D I80 = *sys.new_Tensor3D("I80",	(ex)Ixx80,(ex)Ixy80,(ex)Ixz80,
						(ex)Ixy80,(ex)Iyy80,(ex)Iyz80,
						(ex)Ixz80,(ex)Iyz80,(ex)Izz80,"B80");
// -----------------------------------------------------------------------
    	Tensor3D I81 = *sys.new_Tensor3D("I81",	(ex)Ixx81,(ex)Ixy81,(ex)Ixz81,
						(ex)Ixy81,(ex)Iyy81,(ex)Iyz81,
						(ex)Ixz81,(ex)Iyz81,(ex)Izz81,"B81");
// -----------------------------------------------------------------------
    	Tensor3D I82 = *sys.new_Tensor3D("I82",	(ex)Ixx82,(ex)Ixy82,(ex)Ixz82,
						(ex)Ixy82,(ex)Iyy82,(ex)Iyz82,
						(ex)Ixz82,(ex)Iyz82,(ex)Izz82,"B82");
// -----------------------------------------------------------------------
    	Tensor3D I83 = *sys.new_Tensor3D("I83",	(ex)Ixx83,(ex)Ixy83,(ex)Ixz83,
						(ex)Ixy83,(ex)Iyy83,(ex)Iyz83,
						(ex)Ixz83,(ex)Iyz83,(ex)Izz83,"B83");
// -----------------------------------------------------------------------
    	Tensor3D I84 = *sys.new_Tensor3D("I84",	(ex)Ixx84,(ex)Ixy84,(ex)Ixz84,
						(ex)Ixy84,(ex)Iyy84,(ex)Iyz84,
						(ex)Ixz84,(ex)Iyz84,(ex)Izz84,"B84");
// -----------------------------------------------------------------------
    	Tensor3D I85 = *sys.new_Tensor3D("I85",	(ex)Ixx85,(ex)Ixy85,(ex)Ixz85,
						(ex)Ixy85,(ex)Iyy85,(ex)Iyz85,
						(ex)Ixz85,(ex)Iyz85,(ex)Izz85,"B85");
// -----------------------------------------------------------------------
    	Tensor3D I86 = *sys.new_Tensor3D("I86",	(ex)Ixx86,(ex)Ixy86,(ex)Ixz86,
						(ex)Ixy86,(ex)Iyy86,(ex)Iyz86,
						(ex)Ixz86,(ex)Iyz86,(ex)Izz86,"B86");
// -----------------------------------------------------------------------
    	Tensor3D I87 = *sys.new_Tensor3D("I87",	(ex)Ixx87,(ex)Ixy87,(ex)Ixz87,
						(ex)Ixy87,(ex)Iyy87,(ex)Iyz87,
						(ex)Ixz87,(ex)Iyz87,(ex)Izz87,"B87");
// -----------------------------------------------------------------------
    	Tensor3D I88 = *sys.new_Tensor3D("I88",	(ex)Ixx88,(ex)Ixy88,(ex)Ixz88,
						(ex)Ixy88,(ex)Iyy88,(ex)Iyz88,
						(ex)Ixz88,(ex)Iyz88,(ex)Izz88,"B88");
// -----------------------------------------------------------------------
    	Tensor3D I89 = *sys.new_Tensor3D("I89",	(ex)Ixx89,(ex)Ixy89,(ex)Ixz89,
						(ex)Ixy89,(ex)Iyy89,(ex)Iyz89,
						(ex)Ixz89,(ex)Iyz89,(ex)Izz89,"B89");
// -----------------------------------------------------------------------
    	Tensor3D I90 = *sys.new_Tensor3D("I90",	(ex)Ixx90,(ex)Ixy90,(ex)Ixz90,
						(ex)Ixy90,(ex)Iyy90,(ex)Iyz90,
						(ex)Ixz90,(ex)Iyz90,(ex)Izz90,"B90");
// -----------------------------------------------------------------------
    	Tensor3D I91 = *sys.new_Tensor3D("I91",	(ex)Ixx91,(ex)Ixy91,(ex)Ixz91,
						(ex)Ixy91,(ex)Iyy91,(ex)Iyz91,
						(ex)Ixz91,(ex)Iyz91,(ex)Izz91,"B91");
// -----------------------------------------------------------------------
    	Tensor3D I92 = *sys.new_Tensor3D("I92",	(ex)Ixx92,(ex)Ixy92,(ex)Ixz92,
						(ex)Ixy92,(ex)Iyy92,(ex)Iyz92,
						(ex)Ixz92,(ex)Iyz92,(ex)Izz92,"B92");
// -----------------------------------------------------------------------
    	Tensor3D I93 = *sys.new_Tensor3D("I93",	(ex)Ixx93,(ex)Ixy93,(ex)Ixz93,
						(ex)Ixy93,(ex)Iyy93,(ex)Iyz93,
						(ex)Ixz93,(ex)Iyz93,(ex)Izz93,"B93");
// -----------------------------------------------------------------------
    	Tensor3D I94 = *sys.new_Tensor3D("I94",	(ex)Ixx94,(ex)Ixy94,(ex)Ixz94,
						(ex)Ixy94,(ex)Iyy94,(ex)Iyz94,
						(ex)Ixz94,(ex)Iyz94,(ex)Izz94,"B94");
// -----------------------------------------------------------------------
    	Tensor3D I95 = *sys.new_Tensor3D("I95",	(ex)Ixx95,(ex)Ixy95,(ex)Ixz95,
						(ex)Ixy95,(ex)Iyy95,(ex)Iyz95,
						(ex)Ixz95,(ex)Iyz95,(ex)Izz95,"B95");
// -----------------------------------------------------------------------
    	Tensor3D I96 = *sys.new_Tensor3D("I96",	(ex)Ixx96,(ex)Ixy96,(ex)Ixz96,
						(ex)Ixy96,(ex)Iyy96,(ex)Iyz96,
						(ex)Ixz96,(ex)Iyz96,(ex)Izz96,"B96");
// -----------------------------------------------------------------------
    	Tensor3D I97 = *sys.new_Tensor3D("I97",	(ex)Ixx97,(ex)Ixy97,(ex)Ixz97,
						(ex)Ixy97,(ex)Iyy97,(ex)Iyz97,
						(ex)Ixz97,(ex)Iyz97,(ex)Izz97,"B97");
// -----------------------------------------------------------------------
    	Tensor3D I98 = *sys.new_Tensor3D("I98",	(ex)Ixx98,(ex)Ixy98,(ex)Ixz98,
						(ex)Ixy98,(ex)Iyy98,(ex)Iyz98,
						(ex)Ixz98,(ex)Iyz98,(ex)Izz98,"B98");
// -----------------------------------------------------------------------
    	Tensor3D I99 = *sys.new_Tensor3D("I99",	(ex)Ixx99,(ex)Ixy99,(ex)Ixz99,
						(ex)Ixy99,(ex)Iyy99,(ex)Iyz99,
						(ex)Ixz99,(ex)Iyz99,(ex)Izz99,"B99");
// -----------------------------------------------------------------------
    	Tensor3D I100 = *sys.new_Tensor3D("I100",	(ex)Ixx100,(ex)Ixy100,(ex)Ixz100,
						(ex)Ixy100,(ex)Iyy100,(ex)Iyz100,
						(ex)Ixz100,(ex)Iyz100,(ex)Izz100,"B100");
// -----------------------------------------------------------------------

// ************************************************************************************************
//	Define Frames
// ************************************************************************************************

	Frame * Fra_0= sys.new_Frame("Fra_0","P0","B0");
	Frame * Fra_1= sys.new_Frame("Fra_1","P1","B1");
	Frame * Fra_2= sys.new_Frame("Fra_2","P2","B2");
	Frame * Fra_3= sys.new_Frame("Fra_3","P3","B3");
	Frame * Fra_4= sys.new_Frame("Fra_4","P4","B4");
	Frame * Fra_5= sys.new_Frame("Fra_5","P5","B5");
	Frame * Fra_6= sys.new_Frame("Fra_6","P6","B6");
	Frame * Fra_7= sys.new_Frame("Fra_7","P7","B7");
	Frame * Fra_8= sys.new_Frame("Fra_8","P8","B8");
	Frame * Fra_9= sys.new_Frame("Fra_9","P9","B9");
	Frame * Fra_10= sys.new_Frame("Fra_10","P10","B10");
	Frame * Fra_11= sys.new_Frame("Fra_11","P11","B11");
	Frame * Fra_12= sys.new_Frame("Fra_12","P12","B12");
	Frame * Fra_13= sys.new_Frame("Fra_13","P13","B13");
	Frame * Fra_14= sys.new_Frame("Fra_14","P14","B14");
	Frame * Fra_15= sys.new_Frame("Fra_15","P15","B15");
	Frame * Fra_16= sys.new_Frame("Fra_16","P16","B16");
	Frame * Fra_17= sys.new_Frame("Fra_17","P17","B17");
	Frame * Fra_18= sys.new_Frame("Fra_18","P18","B18");
	Frame * Fra_19= sys.new_Frame("Fra_19","P19","B19");
	Frame * Fra_20= sys.new_Frame("Fra_20","P20","B20");
	Frame * Fra_21= sys.new_Frame("Fra_21","P21","B21");
	Frame * Fra_22= sys.new_Frame("Fra_22","P22","B22");
	Frame * Fra_23= sys.new_Frame("Fra_23","P23","B23");
	Frame * Fra_24= sys.new_Frame("Fra_24","P24","B24");
	Frame * Fra_25= sys.new_Frame("Fra_25","P25","B25");
	Frame * Fra_26= sys.new_Frame("Fra_26","P26","B26");
	Frame * Fra_27= sys.new_Frame("Fra_27","P27","B27");
	Frame * Fra_28= sys.new_Frame("Fra_28","P28","B28");
	Frame * Fra_29= sys.new_Frame("Fra_29","P29","B29");
	Frame * Fra_30= sys.new_Frame("Fra_30","P30","B30");
	Frame * Fra_31= sys.new_Frame("Fra_31","P31","B31");
	Frame * Fra_32= sys.new_Frame("Fra_32","P32","B32");
	Frame * Fra_33= sys.new_Frame("Fra_33","P33","B33");
	Frame * Fra_34= sys.new_Frame("Fra_34","P34","B34");
	Frame * Fra_35= sys.new_Frame("Fra_35","P35","B35");
	Frame * Fra_36= sys.new_Frame("Fra_36","P36","B36");
	Frame * Fra_37= sys.new_Frame("Fra_37","P37","B37");
	Frame * Fra_38= sys.new_Frame("Fra_38","P38","B38");
	Frame * Fra_39= sys.new_Frame("Fra_39","P39","B39");
	Frame * Fra_40= sys.new_Frame("Fra_40","P40","B40");
	Frame * Fra_41= sys.new_Frame("Fra_41","P41","B41");
	Frame * Fra_42= sys.new_Frame("Fra_42","P42","B42");
	Frame * Fra_43= sys.new_Frame("Fra_43","P43","B43");
	Frame * Fra_44= sys.new_Frame("Fra_44","P44","B44");
	Frame * Fra_45= sys.new_Frame("Fra_45","P45","B45");
	Frame * Fra_46= sys.new_Frame("Fra_46","P46","B46");
	Frame * Fra_47= sys.new_Frame("Fra_47","P47","B47");
	Frame * Fra_48= sys.new_Frame("Fra_48","P48","B48");
	Frame * Fra_49= sys.new_Frame("Fra_49","P49","B49");
	Frame * Fra_50= sys.new_Frame("Fra_50","P50","B50");
	Frame * Fra_51= sys.new_Frame("Fra_51","P51","B51");
	Frame * Fra_52= sys.new_Frame("Fra_52","P52","B52");
	Frame * Fra_53= sys.new_Frame("Fra_53","P53","B53");
	Frame * Fra_54= sys.new_Frame("Fra_54","P54","B54");
	Frame * Fra_55= sys.new_Frame("Fra_55","P55","B55");
	Frame * Fra_56= sys.new_Frame("Fra_56","P56","B56");
	Frame * Fra_57= sys.new_Frame("Fra_57","P57","B57");
	Frame * Fra_58= sys.new_Frame("Fra_58","P58","B58");
	Frame * Fra_59= sys.new_Frame("Fra_59","P59","B59");
	Frame * Fra_60= sys.new_Frame("Fra_60","P60","B60");
	Frame * Fra_61= sys.new_Frame("Fra_61","P61","B61");
	Frame * Fra_62= sys.new_Frame("Fra_62","P62","B62");
	Frame * Fra_63= sys.new_Frame("Fra_63","P63","B63");
	Frame * Fra_64= sys.new_Frame("Fra_64","P64","B64");
	Frame * Fra_65= sys.new_Frame("Fra_65","P65","B65");
	Frame * Fra_66= sys.new_Frame("Fra_66","P66","B66");
	Frame * Fra_67= sys.new_Frame("Fra_67","P67","B67");
	Frame * Fra_68= sys.new_Frame("Fra_68","P68","B68");
	Frame * Fra_69= sys.new_Frame("Fra_69","P69","B69");
	Frame * Fra_70= sys.new_Frame("Fra_70","P70","B70");
	Frame * Fra_71= sys.new_Frame("Fra_71","P71","B71");
	Frame * Fra_72= sys.new_Frame("Fra_72","P72","B72");
	Frame * Fra_73= sys.new_Frame("Fra_73","P73","B73");
	Frame * Fra_74= sys.new_Frame("Fra_74","P74","B74");
	Frame * Fra_75= sys.new_Frame("Fra_75","P75","B75");
	Frame * Fra_76= sys.new_Frame("Fra_76","P76","B76");
	Frame * Fra_77= sys.new_Frame("Fra_77","P77","B77");
	Frame * Fra_78= sys.new_Frame("Fra_78","P78","B78");
	Frame * Fra_79= sys.new_Frame("Fra_79","P79","B79");
	Frame * Fra_80= sys.new_Frame("Fra_80","P80","B80");
	Frame * Fra_81= sys.new_Frame("Fra_81","P81","B81");
	Frame * Fra_82= sys.new_Frame("Fra_82","P82","B82");
	Frame * Fra_83= sys.new_Frame("Fra_83","P83","B83");
	Frame * Fra_84= sys.new_Frame("Fra_84","P84","B84");
	Frame * Fra_85= sys.new_Frame("Fra_85","P85","B85");
	Frame * Fra_86= sys.new_Frame("Fra_86","P86","B86");
	Frame * Fra_87= sys.new_Frame("Fra_87","P87","B87");
	Frame * Fra_88= sys.new_Frame("Fra_88","P88","B88");
	Frame * Fra_89= sys.new_Frame("Fra_89","P89","B89");
	Frame * Fra_90= sys.new_Frame("Fra_90","P90","B90");
	Frame * Fra_91= sys.new_Frame("Fra_91","P91","B91");
	Frame * Fra_92= sys.new_Frame("Fra_92","P92","B92");
	Frame * Fra_93= sys.new_Frame("Fra_93","P93","B93");
	Frame * Fra_94= sys.new_Frame("Fra_94","P94","B94");
	Frame * Fra_95= sys.new_Frame("Fra_95","P95","B95");
	Frame * Fra_96= sys.new_Frame("Fra_96","P96","B96");
	Frame * Fra_97= sys.new_Frame("Fra_97","P97","B97");
	Frame * Fra_98= sys.new_Frame("Fra_98","P98","B98");
	Frame * Fra_99= sys.new_Frame("Fra_99","P99","B99");
	Frame * Fra_100= sys.new_Frame("Fra_100","P100","B100");


// ************************************************************************************************
//	Define Solids
// ************************************************************************************************

	Solid * BAR1 = sys.new_Solid("BAR1","P1","B1","m1","P1G1","I1");
	Solid * BAR2 = sys.new_Solid("BAR2","P2","B2","m2","P2G2","I2");
	Solid * BAR3 = sys.new_Solid("BAR3","P3","B3","m3","P3G3","I3");
	Solid * BAR4 = sys.new_Solid("BAR4","P4","B4","m4","P4G4","I4");
	Solid * BAR5 = sys.new_Solid("BAR5","P5","B5","m5","P5G5","I5");
	Solid * BAR6 = sys.new_Solid("BAR6","P6","B6","m6","P6G6","I6");
	Solid * BAR7 = sys.new_Solid("BAR7","P7","B7","m7","P7G7","I7");
	Solid * BAR8 = sys.new_Solid("BAR8","P8","B8","m8","P8G8","I8");
	Solid * BAR9 = sys.new_Solid("BAR9","P9","B9","m9","P9G9","I9");
	Solid * BAR10 = sys.new_Solid("BAR10","P10","B10","m10","P10G10","I10");
	Solid * BAR11 = sys.new_Solid("BAR11","P11","B11","m11","P11G11","I11");
	Solid * BAR12 = sys.new_Solid("BAR12","P12","B12","m12","P12G12","I12");
	Solid * BAR13 = sys.new_Solid("BAR13","P13","B13","m13","P13G13","I13");
	Solid * BAR14 = sys.new_Solid("BAR14","P14","B14","m14","P14G14","I14");
	Solid * BAR15 = sys.new_Solid("BAR15","P15","B15","m15","P15G15","I15");
	Solid * BAR16 = sys.new_Solid("BAR16","P16","B16","m16","P16G16","I16");
	Solid * BAR17 = sys.new_Solid("BAR17","P17","B17","m17","P17G17","I17");
	Solid * BAR18 = sys.new_Solid("BAR18","P18","B18","m18","P18G18","I18");
	Solid * BAR19 = sys.new_Solid("BAR19","P19","B19","m19","P19G19","I19");
	Solid * BAR20 = sys.new_Solid("BAR20","P20","B20","m20","P20G20","I20");
	Solid * BAR21 = sys.new_Solid("BAR21","P21","B21","m21","P21G21","I21");
	Solid * BAR22 = sys.new_Solid("BAR22","P22","B22","m22","P22G22","I22");
	Solid * BAR23 = sys.new_Solid("BAR23","P23","B23","m23","P23G23","I23");
	Solid * BAR24 = sys.new_Solid("BAR24","P24","B24","m24","P24G24","I24");
	Solid * BAR25 = sys.new_Solid("BAR25","P25","B25","m25","P25G25","I25");
	Solid * BAR26 = sys.new_Solid("BAR26","P26","B26","m26","P26G26","I26");
	Solid * BAR27 = sys.new_Solid("BAR27","P27","B27","m27","P27G27","I27");
	Solid * BAR28 = sys.new_Solid("BAR28","P28","B28","m28","P28G28","I28");
	Solid * BAR29 = sys.new_Solid("BAR29","P29","B29","m29","P29G29","I29");
	Solid * BAR30 = sys.new_Solid("BAR30","P30","B30","m30","P30G30","I30");
	Solid * BAR31 = sys.new_Solid("BAR31","P31","B31","m31","P31G31","I31");
	Solid * BAR32 = sys.new_Solid("BAR32","P32","B32","m32","P32G32","I32");
	Solid * BAR33 = sys.new_Solid("BAR33","P33","B33","m33","P33G33","I33");
	Solid * BAR34 = sys.new_Solid("BAR34","P34","B34","m34","P34G34","I34");
	Solid * BAR35 = sys.new_Solid("BAR35","P35","B35","m35","P35G35","I35");
	Solid * BAR36 = sys.new_Solid("BAR36","P36","B36","m36","P36G36","I36");
	Solid * BAR37 = sys.new_Solid("BAR37","P37","B37","m37","P37G37","I37");
	Solid * BAR38 = sys.new_Solid("BAR38","P38","B38","m38","P38G38","I38");
	Solid * BAR39 = sys.new_Solid("BAR39","P39","B39","m39","P39G39","I39");
	Solid * BAR40 = sys.new_Solid("BAR40","P40","B40","m40","P40G40","I40");
	Solid * BAR41 = sys.new_Solid("BAR41","P41","B41","m41","P41G41","I41");
	Solid * BAR42 = sys.new_Solid("BAR42","P42","B42","m42","P42G42","I42");
	Solid * BAR43 = sys.new_Solid("BAR43","P43","B43","m43","P43G43","I43");
	Solid * BAR44 = sys.new_Solid("BAR44","P44","B44","m44","P44G44","I44");
	Solid * BAR45 = sys.new_Solid("BAR45","P45","B45","m45","P45G45","I45");
	Solid * BAR46 = sys.new_Solid("BAR46","P46","B46","m46","P46G46","I46");
	Solid * BAR47 = sys.new_Solid("BAR47","P47","B47","m47","P47G47","I47");
	Solid * BAR48 = sys.new_Solid("BAR48","P48","B48","m48","P48G48","I48");
	Solid * BAR49 = sys.new_Solid("BAR49","P49","B49","m49","P49G49","I49");
	Solid * BAR50 = sys.new_Solid("BAR50","P50","B50","m50","P50G50","I50");
	Solid * BAR51 = sys.new_Solid("BAR51","P51","B51","m51","P51G51","I51");
	Solid * BAR52 = sys.new_Solid("BAR52","P52","B52","m52","P52G52","I52");
	Solid * BAR53 = sys.new_Solid("BAR53","P53","B53","m53","P53G53","I53");
	Solid * BAR54 = sys.new_Solid("BAR54","P54","B54","m54","P54G54","I54");
	Solid * BAR55 = sys.new_Solid("BAR55","P55","B55","m55","P55G55","I55");
	Solid * BAR56 = sys.new_Solid("BAR56","P56","B56","m56","P56G56","I56");
	Solid * BAR57 = sys.new_Solid("BAR57","P57","B57","m57","P57G57","I57");
	Solid * BAR58 = sys.new_Solid("BAR58","P58","B58","m58","P58G58","I58");
	Solid * BAR59 = sys.new_Solid("BAR59","P59","B59","m59","P59G59","I59");
	Solid * BAR60 = sys.new_Solid("BAR60","P60","B60","m60","P60G60","I60");
	Solid * BAR61 = sys.new_Solid("BAR61","P61","B61","m61","P61G61","I61");
	Solid * BAR62 = sys.new_Solid("BAR62","P62","B62","m62","P62G62","I62");
	Solid * BAR63 = sys.new_Solid("BAR63","P63","B63","m63","P63G63","I63");
	Solid * BAR64 = sys.new_Solid("BAR64","P64","B64","m64","P64G64","I64");
	Solid * BAR65 = sys.new_Solid("BAR65","P65","B65","m65","P65G65","I65");
	Solid * BAR66 = sys.new_Solid("BAR66","P66","B66","m66","P66G66","I66");
	Solid * BAR67 = sys.new_Solid("BAR67","P67","B67","m67","P67G67","I67");
	Solid * BAR68 = sys.new_Solid("BAR68","P68","B68","m68","P68G68","I68");
	Solid * BAR69 = sys.new_Solid("BAR69","P69","B69","m69","P69G69","I69");
	Solid * BAR70 = sys.new_Solid("BAR70","P70","B70","m70","P70G70","I70");
	Solid * BAR71 = sys.new_Solid("BAR71","P71","B71","m71","P71G71","I71");
	Solid * BAR72 = sys.new_Solid("BAR72","P72","B72","m72","P72G72","I72");
	Solid * BAR73 = sys.new_Solid("BAR73","P73","B73","m73","P73G73","I73");
	Solid * BAR74 = sys.new_Solid("BAR74","P74","B74","m74","P74G74","I74");
	Solid * BAR75 = sys.new_Solid("BAR75","P75","B75","m75","P75G75","I75");
	Solid * BAR76 = sys.new_Solid("BAR76","P76","B76","m76","P76G76","I76");
	Solid * BAR77 = sys.new_Solid("BAR77","P77","B77","m77","P77G77","I77");
	Solid * BAR78 = sys.new_Solid("BAR78","P78","B78","m78","P78G78","I78");
	Solid * BAR79 = sys.new_Solid("BAR79","P79","B79","m79","P79G79","I79");
	Solid * BAR80 = sys.new_Solid("BAR80","P80","B80","m80","P80G80","I80");
	Solid * BAR81 = sys.new_Solid("BAR81","P81","B81","m81","P81G81","I81");
	Solid * BAR82 = sys.new_Solid("BAR82","P82","B82","m82","P82G82","I82");
	Solid * BAR83 = sys.new_Solid("BAR83","P83","B83","m83","P83G83","I83");
	Solid * BAR84 = sys.new_Solid("BAR84","P84","B84","m84","P84G84","I84");
	Solid * BAR85 = sys.new_Solid("BAR85","P85","B85","m85","P85G85","I85");
	Solid * BAR86 = sys.new_Solid("BAR86","P86","B86","m86","P86G86","I86");
	Solid * BAR87 = sys.new_Solid("BAR87","P87","B87","m87","P87G87","I87");
	Solid * BAR88 = sys.new_Solid("BAR88","P88","B88","m88","P88G88","I88");
	Solid * BAR89 = sys.new_Solid("BAR89","P89","B89","m89","P89G89","I89");
	Solid * BAR90 = sys.new_Solid("BAR90","P90","B90","m90","P90G90","I90");
	Solid * BAR91 = sys.new_Solid("BAR91","P91","B91","m91","P91G91","I91");
	Solid * BAR92 = sys.new_Solid("BAR92","P92","B92","m92","P92G92","I92");
	Solid * BAR93 = sys.new_Solid("BAR93","P93","B93","m93","P93G93","I93");
	Solid * BAR94 = sys.new_Solid("BAR94","P94","B94","m94","P94G94","I94");
	Solid * BAR95 = sys.new_Solid("BAR95","P95","B95","m95","P95G95","I95");
	Solid * BAR96 = sys.new_Solid("BAR96","P96","B96","m96","P96G96","I96");
	Solid * BAR97 = sys.new_Solid("BAR97","P97","B97","m97","P97G97","I97");
	Solid * BAR98 = sys.new_Solid("BAR98","P98","B98","m98","P98G98","I98");
	Solid * BAR99 = sys.new_Solid("BAR99","P99","B99","m99","P99G99","I99");
	Solid * BAR100 = sys.new_Solid("BAR100","P100","B100","m100","P100G100","I100");

// ************************************************************************************************
//	Define Objects to Draw
// ************************************************************************************************

//	Drawing3D * BAR1_3D = sys.new_Drawing3D("BAR1_3D", BAR1,"./solids/solid_1.stl" ,1,0,0,0.5);
//	Drawing3D * BAR2_3D = sys.new_Drawing3D("BAR2_3D", BAR2,"./solids/solid_2.stl" ,1,0,0,0.5);
//	Drawing3D * BAR3_3D = sys.new_Drawing3D("BAR3_3D", BAR3,"./solids/solid_3.stl" ,1,0,0,0.5);
//	Drawing3D * BAR4_3D = sys.new_Drawing3D("BAR4_3D", BAR4,"./solids/solid_4.stl" ,1,0,0,0.5);
//	Drawing3D * BAR5_3D = sys.new_Drawing3D("BAR5_3D", BAR5,"./solids/solid_5.stl" ,1,0,0,0.5);
//	Drawing3D * BAR6_3D = sys.new_Drawing3D("BAR6_3D", BAR6,"./solids/solid_6.stl" ,1,0,0,0.5);
//	Drawing3D * BAR7_3D = sys.new_Drawing3D("BAR7_3D", BAR7,"./solids/solid_7.stl" ,1,0,0,0.5);
//	Drawing3D * BAR8_3D = sys.new_Drawing3D("BAR8_3D", BAR8,"./solids/solid_8.stl" ,1,0,0,0.5);
//	Drawing3D * BAR9_3D = sys.new_Drawing3D("BAR9_3D", BAR9,"./solids/solid_9.stl" ,1,0,0,0.5);
//	Drawing3D * BAR10_3D = sys.new_Drawing3D("BAR10_3D", BAR10,"./solids/solid_10.stl" ,1,0,0,0.5);
//	Drawing3D * BAR11_3D = sys.new_Drawing3D("BAR11_3D", BAR11,"./solids/solid_11.stl" ,1,0,0,0.5);
//	Drawing3D * BAR12_3D = sys.new_Drawing3D("BAR12_3D", BAR12,"./solids/solid_12.stl" ,1,0,0,0.5);
//	Drawing3D * BAR13_3D = sys.new_Drawing3D("BAR13_3D", BAR13,"./solids/solid_13.stl" ,1,0,0,0.5);
//	Drawing3D * BAR14_3D = sys.new_Drawing3D("BAR14_3D", BAR14,"./solids/solid_14.stl" ,1,0,0,0.5);
//	Drawing3D * BAR15_3D = sys.new_Drawing3D("BAR15_3D", BAR15,"./solids/solid_15.stl" ,1,0,0,0.5);
//	Drawing3D * BAR16_3D = sys.new_Drawing3D("BAR16_3D", BAR16,"./solids/solid_16.stl" ,1,0,0,0.5);
//	Drawing3D * BAR17_3D = sys.new_Drawing3D("BAR17_3D", BAR17,"./solids/solid_17.stl" ,1,0,0,0.5);
//	Drawing3D * BAR18_3D = sys.new_Drawing3D("BAR18_3D", BAR18,"./solids/solid_18.stl" ,1,0,0,0.5);
//	Drawing3D * BAR19_3D = sys.new_Drawing3D("BAR19_3D", BAR19,"./solids/solid_19.stl" ,1,0,0,0.5);
//	Drawing3D * BAR20_3D = sys.new_Drawing3D("BAR20_3D", BAR20,"./solids/solid_20.stl" ,1,0,0,0.5);
//	Drawing3D * BAR21_3D = sys.new_Drawing3D("BAR21_3D", BAR21,"./solids/solid_21.stl" ,1,0,0,0.5);
//	Drawing3D * BAR22_3D = sys.new_Drawing3D("BAR22_3D", BAR22,"./solids/solid_22.stl" ,1,0,0,0.5);
//	Drawing3D * BAR23_3D = sys.new_Drawing3D("BAR23_3D", BAR23,"./solids/solid_23.stl" ,1,0,0,0.5);
//	Drawing3D * BAR24_3D = sys.new_Drawing3D("BAR24_3D", BAR24,"./solids/solid_24.stl" ,1,0,0,0.5);
//	Drawing3D * BAR25_3D = sys.new_Drawing3D("BAR25_3D", BAR25,"./solids/solid_25.stl" ,1,0,0,0.5);
//	Drawing3D * BAR26_3D = sys.new_Drawing3D("BAR26_3D", BAR26,"./solids/solid_26.stl" ,1,0,0,0.5);
//	Drawing3D * BAR27_3D = sys.new_Drawing3D("BAR27_3D", BAR27,"./solids/solid_27.stl" ,1,0,0,0.5);
//	Drawing3D * BAR28_3D = sys.new_Drawing3D("BAR28_3D", BAR28,"./solids/solid_28.stl" ,1,0,0,0.5);
//	Drawing3D * BAR29_3D = sys.new_Drawing3D("BAR29_3D", BAR29,"./solids/solid_29.stl" ,1,0,0,0.5);
//	Drawing3D * BAR30_3D = sys.new_Drawing3D("BAR30_3D", BAR30,"./solids/solid_30.stl" ,1,0,0,0.5);
//	Drawing3D * BAR31_3D = sys.new_Drawing3D("BAR31_3D", BAR31,"./solids/solid_31.stl" ,1,0,0,0.5);
//	Drawing3D * BAR32_3D = sys.new_Drawing3D("BAR32_3D", BAR32,"./solids/solid_32.stl" ,1,0,0,0.5);
//	Drawing3D * BAR33_3D = sys.new_Drawing3D("BAR33_3D", BAR33,"./solids/solid_33.stl" ,1,0,0,0.5);
//	Drawing3D * BAR34_3D = sys.new_Drawing3D("BAR34_3D", BAR34,"./solids/solid_34.stl" ,1,0,0,0.5);
//	Drawing3D * BAR35_3D = sys.new_Drawing3D("BAR35_3D", BAR35,"./solids/solid_35.stl" ,1,0,0,0.5);
//	Drawing3D * BAR36_3D = sys.new_Drawing3D("BAR36_3D", BAR36,"./solids/solid_36.stl" ,1,0,0,0.5);
//	Drawing3D * BAR37_3D = sys.new_Drawing3D("BAR37_3D", BAR37,"./solids/solid_37.stl" ,1,0,0,0.5);
//	Drawing3D * BAR38_3D = sys.new_Drawing3D("BAR38_3D", BAR38,"./solids/solid_38.stl" ,1,0,0,0.5);
//	Drawing3D * BAR39_3D = sys.new_Drawing3D("BAR39_3D", BAR39,"./solids/solid_39.stl" ,1,0,0,0.5);
//	Drawing3D * BAR40_3D = sys.new_Drawing3D("BAR40_3D", BAR40,"./solids/solid_40.stl" ,1,0,0,0.5);
//	Drawing3D * BAR41_3D = sys.new_Drawing3D("BAR41_3D", BAR41,"./solids/solid_41.stl" ,1,0,0,0.5);
//	Drawing3D * BAR42_3D = sys.new_Drawing3D("BAR42_3D", BAR42,"./solids/solid_42.stl" ,1,0,0,0.5);
//	Drawing3D * BAR43_3D = sys.new_Drawing3D("BAR43_3D", BAR43,"./solids/solid_43.stl" ,1,0,0,0.5);
//	Drawing3D * BAR44_3D = sys.new_Drawing3D("BAR44_3D", BAR44,"./solids/solid_44.stl" ,1,0,0,0.5);
//	Drawing3D * BAR45_3D = sys.new_Drawing3D("BAR45_3D", BAR45,"./solids/solid_45.stl" ,1,0,0,0.5);
//	Drawing3D * BAR46_3D = sys.new_Drawing3D("BAR46_3D", BAR46,"./solids/solid_46.stl" ,1,0,0,0.5);
//	Drawing3D * BAR47_3D = sys.new_Drawing3D("BAR47_3D", BAR47,"./solids/solid_47.stl" ,1,0,0,0.5);
//	Drawing3D * BAR48_3D = sys.new_Drawing3D("BAR48_3D", BAR48,"./solids/solid_48.stl" ,1,0,0,0.5);
//	Drawing3D * BAR49_3D = sys.new_Drawing3D("BAR49_3D", BAR49,"./solids/solid_49.stl" ,1,0,0,0.5);
//	Drawing3D * BAR50_3D = sys.new_Drawing3D("BAR50_3D", BAR50,"./solids/solid_50.stl" ,1,0,0,0.5);
//	Drawing3D * BAR51_3D = sys.new_Drawing3D("BAR51_3D", BAR51,"./solids/solid_51.stl" ,1,0,0,0.5);
//	Drawing3D * BAR52_3D = sys.new_Drawing3D("BAR52_3D", BAR52,"./solids/solid_52.stl" ,1,0,0,0.5);
//	Drawing3D * BAR53_3D = sys.new_Drawing3D("BAR53_3D", BAR53,"./solids/solid_53.stl" ,1,0,0,0.5);
//	Drawing3D * BAR54_3D = sys.new_Drawing3D("BAR54_3D", BAR54,"./solids/solid_54.stl" ,1,0,0,0.5);
//	Drawing3D * BAR55_3D = sys.new_Drawing3D("BAR55_3D", BAR55,"./solids/solid_55.stl" ,1,0,0,0.5);
//	Drawing3D * BAR56_3D = sys.new_Drawing3D("BAR56_3D", BAR56,"./solids/solid_56.stl" ,1,0,0,0.5);
//	Drawing3D * BAR57_3D = sys.new_Drawing3D("BAR57_3D", BAR57,"./solids/solid_57.stl" ,1,0,0,0.5);
//	Drawing3D * BAR58_3D = sys.new_Drawing3D("BAR58_3D", BAR58,"./solids/solid_58.stl" ,1,0,0,0.5);
//	Drawing3D * BAR59_3D = sys.new_Drawing3D("BAR59_3D", BAR59,"./solids/solid_59.stl" ,1,0,0,0.5);
//	Drawing3D * BAR60_3D = sys.new_Drawing3D("BAR60_3D", BAR60,"./solids/solid_60.stl" ,1,0,0,0.5);
//	Drawing3D * BAR61_3D = sys.new_Drawing3D("BAR61_3D", BAR61,"./solids/solid_61.stl" ,1,0,0,0.5);
//	Drawing3D * BAR62_3D = sys.new_Drawing3D("BAR62_3D", BAR62,"./solids/solid_62.stl" ,1,0,0,0.5);
//	Drawing3D * BAR63_3D = sys.new_Drawing3D("BAR63_3D", BAR63,"./solids/solid_63.stl" ,1,0,0,0.5);
//	Drawing3D * BAR64_3D = sys.new_Drawing3D("BAR64_3D", BAR64,"./solids/solid_64.stl" ,1,0,0,0.5);
//	Drawing3D * BAR65_3D = sys.new_Drawing3D("BAR65_3D", BAR65,"./solids/solid_65.stl" ,1,0,0,0.5);
//	Drawing3D * BAR66_3D = sys.new_Drawing3D("BAR66_3D", BAR66,"./solids/solid_66.stl" ,1,0,0,0.5);
//	Drawing3D * BAR67_3D = sys.new_Drawing3D("BAR67_3D", BAR67,"./solids/solid_67.stl" ,1,0,0,0.5);
//	Drawing3D * BAR68_3D = sys.new_Drawing3D("BAR68_3D", BAR68,"./solids/solid_68.stl" ,1,0,0,0.5);
//	Drawing3D * BAR69_3D = sys.new_Drawing3D("BAR69_3D", BAR69,"./solids/solid_69.stl" ,1,0,0,0.5);
//	Drawing3D * BAR70_3D = sys.new_Drawing3D("BAR70_3D", BAR70,"./solids/solid_70.stl" ,1,0,0,0.5);
//	Drawing3D * BAR71_3D = sys.new_Drawing3D("BAR71_3D", BAR71,"./solids/solid_71.stl" ,1,0,0,0.5);
//	Drawing3D * BAR72_3D = sys.new_Drawing3D("BAR72_3D", BAR72,"./solids/solid_72.stl" ,1,0,0,0.5);
//	Drawing3D * BAR73_3D = sys.new_Drawing3D("BAR73_3D", BAR73,"./solids/solid_73.stl" ,1,0,0,0.5);
//	Drawing3D * BAR74_3D = sys.new_Drawing3D("BAR74_3D", BAR74,"./solids/solid_74.stl" ,1,0,0,0.5);
//	Drawing3D * BAR75_3D = sys.new_Drawing3D("BAR75_3D", BAR75,"./solids/solid_75.stl" ,1,0,0,0.5);
//	Drawing3D * BAR76_3D = sys.new_Drawing3D("BAR76_3D", BAR76,"./solids/solid_76.stl" ,1,0,0,0.5);
//	Drawing3D * BAR77_3D = sys.new_Drawing3D("BAR77_3D", BAR77,"./solids/solid_77.stl" ,1,0,0,0.5);
//	Drawing3D * BAR78_3D = sys.new_Drawing3D("BAR78_3D", BAR78,"./solids/solid_78.stl" ,1,0,0,0.5);
//	Drawing3D * BAR79_3D = sys.new_Drawing3D("BAR79_3D", BAR79,"./solids/solid_79.stl" ,1,0,0,0.5);
//	Drawing3D * BAR80_3D = sys.new_Drawing3D("BAR80_3D", BAR80,"./solids/solid_80.stl" ,1,0,0,0.5);
//	Drawing3D * BAR81_3D = sys.new_Drawing3D("BAR81_3D", BAR81,"./solids/solid_81.stl" ,1,0,0,0.5);
//	Drawing3D * BAR82_3D = sys.new_Drawing3D("BAR82_3D", BAR82,"./solids/solid_82.stl" ,1,0,0,0.5);
//	Drawing3D * BAR83_3D = sys.new_Drawing3D("BAR83_3D", BAR83,"./solids/solid_83.stl" ,1,0,0,0.5);
//	Drawing3D * BAR84_3D = sys.new_Drawing3D("BAR84_3D", BAR84,"./solids/solid_84.stl" ,1,0,0,0.5);
//	Drawing3D * BAR85_3D = sys.new_Drawing3D("BAR85_3D", BAR85,"./solids/solid_85.stl" ,1,0,0,0.5);
//	Drawing3D * BAR86_3D = sys.new_Drawing3D("BAR86_3D", BAR86,"./solids/solid_86.stl" ,1,0,0,0.5);
//	Drawing3D * BAR87_3D = sys.new_Drawing3D("BAR87_3D", BAR87,"./solids/solid_87.stl" ,1,0,0,0.5);
//	Drawing3D * BAR88_3D = sys.new_Drawing3D("BAR88_3D", BAR88,"./solids/solid_88.stl" ,1,0,0,0.5);
//	Drawing3D * BAR89_3D = sys.new_Drawing3D("BAR89_3D", BAR89,"./solids/solid_89.stl" ,1,0,0,0.5);
//	Drawing3D * BAR90_3D = sys.new_Drawing3D("BAR90_3D", BAR90,"./solids/solid_90.stl" ,1,0,0,0.5);
//	Drawing3D * BAR91_3D = sys.new_Drawing3D("BAR91_3D", BAR91,"./solids/solid_91.stl" ,1,0,0,0.5);
//	Drawing3D * BAR92_3D = sys.new_Drawing3D("BAR92_3D", BAR92,"./solids/solid_92.stl" ,1,0,0,0.5);
//	Drawing3D * BAR93_3D = sys.new_Drawing3D("BAR93_3D", BAR93,"./solids/solid_93.stl" ,1,0,0,0.5);
//	Drawing3D * BAR94_3D = sys.new_Drawing3D("BAR94_3D", BAR94,"./solids/solid_94.stl" ,1,0,0,0.5);
//	Drawing3D * BAR95_3D = sys.new_Drawing3D("BAR95_3D", BAR95,"./solids/solid_95.stl" ,1,0,0,0.5);
//	Drawing3D * BAR96_3D = sys.new_Drawing3D("BAR96_3D", BAR96,"./solids/solid_96.stl" ,1,0,0,0.5);
//	Drawing3D * BAR97_3D = sys.new_Drawing3D("BAR97_3D", BAR97,"./solids/solid_97.stl" ,1,0,0,0.5);
//	Drawing3D * BAR98_3D = sys.new_Drawing3D("BAR98_3D", BAR98,"./solids/solid_98.stl" ,1,0,0,0.5);
//	Drawing3D * BAR99_3D = sys.new_Drawing3D("BAR99_3D", BAR99,"./solids/solid_99.stl" ,1,0,0,0.5);
//	Drawing3D * BAR100_3D = sys.new_Drawing3D("BAR100_3D", BAR100,"./solids/solid_100.stl" ,1,0,0,0.5);
	Drawing3D * Fra_BAR0_3D = sys.new_Drawing3D("Fra_BAR0_3D","Fra_0",1);
	Drawing3D * Fra_BAR1_3D = sys.new_Drawing3D("Fra_BAR1_3D","Fra_1",1);
	Drawing3D * Fra_BAR2_3D = sys.new_Drawing3D("Fra_BAR2_3D","Fra_2",1);
	Drawing3D * Fra_BAR3_3D = sys.new_Drawing3D("Fra_BAR3_3D","Fra_3",1);
	Drawing3D * Fra_BAR4_3D = sys.new_Drawing3D("Fra_BAR4_3D","Fra_4",1);
	Drawing3D * Fra_BAR5_3D = sys.new_Drawing3D("Fra_BAR5_3D","Fra_5",1);
	Drawing3D * Fra_BAR6_3D = sys.new_Drawing3D("Fra_BAR6_3D","Fra_6",1);
	Drawing3D * Fra_BAR7_3D = sys.new_Drawing3D("Fra_BAR7_3D","Fra_7",1);
	Drawing3D * Fra_BAR8_3D = sys.new_Drawing3D("Fra_BAR8_3D","Fra_8",1);
	Drawing3D * Fra_BAR9_3D = sys.new_Drawing3D("Fra_BAR9_3D","Fra_9",1);
	Drawing3D * Fra_BAR10_3D = sys.new_Drawing3D("Fra_BAR10_3D","Fra_10",1);
	Drawing3D * Fra_BAR11_3D = sys.new_Drawing3D("Fra_BAR11_3D","Fra_11",1);
	Drawing3D * Fra_BAR12_3D = sys.new_Drawing3D("Fra_BAR12_3D","Fra_12",1);
	Drawing3D * Fra_BAR13_3D = sys.new_Drawing3D("Fra_BAR13_3D","Fra_13",1);
	Drawing3D * Fra_BAR14_3D = sys.new_Drawing3D("Fra_BAR14_3D","Fra_14",1);
	Drawing3D * Fra_BAR15_3D = sys.new_Drawing3D("Fra_BAR15_3D","Fra_15",1);
	Drawing3D * Fra_BAR16_3D = sys.new_Drawing3D("Fra_BAR16_3D","Fra_16",1);
	Drawing3D * Fra_BAR17_3D = sys.new_Drawing3D("Fra_BAR17_3D","Fra_17",1);
	Drawing3D * Fra_BAR18_3D = sys.new_Drawing3D("Fra_BAR18_3D","Fra_18",1);
	Drawing3D * Fra_BAR19_3D = sys.new_Drawing3D("Fra_BAR19_3D","Fra_19",1);
	Drawing3D * Fra_BAR20_3D = sys.new_Drawing3D("Fra_BAR20_3D","Fra_20",1);
	Drawing3D * Fra_BAR21_3D = sys.new_Drawing3D("Fra_BAR21_3D","Fra_21",1);
	Drawing3D * Fra_BAR22_3D = sys.new_Drawing3D("Fra_BAR22_3D","Fra_22",1);
	Drawing3D * Fra_BAR23_3D = sys.new_Drawing3D("Fra_BAR23_3D","Fra_23",1);
	Drawing3D * Fra_BAR24_3D = sys.new_Drawing3D("Fra_BAR24_3D","Fra_24",1);
	Drawing3D * Fra_BAR25_3D = sys.new_Drawing3D("Fra_BAR25_3D","Fra_25",1);
	Drawing3D * Fra_BAR26_3D = sys.new_Drawing3D("Fra_BAR26_3D","Fra_26",1);
	Drawing3D * Fra_BAR27_3D = sys.new_Drawing3D("Fra_BAR27_3D","Fra_27",1);
	Drawing3D * Fra_BAR28_3D = sys.new_Drawing3D("Fra_BAR28_3D","Fra_28",1);
	Drawing3D * Fra_BAR29_3D = sys.new_Drawing3D("Fra_BAR29_3D","Fra_29",1);
	Drawing3D * Fra_BAR30_3D = sys.new_Drawing3D("Fra_BAR30_3D","Fra_30",1);
	Drawing3D * Fra_BAR31_3D = sys.new_Drawing3D("Fra_BAR31_3D","Fra_31",1);
	Drawing3D * Fra_BAR32_3D = sys.new_Drawing3D("Fra_BAR32_3D","Fra_32",1);
	Drawing3D * Fra_BAR33_3D = sys.new_Drawing3D("Fra_BAR33_3D","Fra_33",1);
	Drawing3D * Fra_BAR34_3D = sys.new_Drawing3D("Fra_BAR34_3D","Fra_34",1);
	Drawing3D * Fra_BAR35_3D = sys.new_Drawing3D("Fra_BAR35_3D","Fra_35",1);
	Drawing3D * Fra_BAR36_3D = sys.new_Drawing3D("Fra_BAR36_3D","Fra_36",1);
	Drawing3D * Fra_BAR37_3D = sys.new_Drawing3D("Fra_BAR37_3D","Fra_37",1);
	Drawing3D * Fra_BAR38_3D = sys.new_Drawing3D("Fra_BAR38_3D","Fra_38",1);
	Drawing3D * Fra_BAR39_3D = sys.new_Drawing3D("Fra_BAR39_3D","Fra_39",1);
	Drawing3D * Fra_BAR40_3D = sys.new_Drawing3D("Fra_BAR40_3D","Fra_40",1);
	Drawing3D * Fra_BAR41_3D = sys.new_Drawing3D("Fra_BAR41_3D","Fra_41",1);
	Drawing3D * Fra_BAR42_3D = sys.new_Drawing3D("Fra_BAR42_3D","Fra_42",1);
	Drawing3D * Fra_BAR43_3D = sys.new_Drawing3D("Fra_BAR43_3D","Fra_43",1);
	Drawing3D * Fra_BAR44_3D = sys.new_Drawing3D("Fra_BAR44_3D","Fra_44",1);
	Drawing3D * Fra_BAR45_3D = sys.new_Drawing3D("Fra_BAR45_3D","Fra_45",1);
	Drawing3D * Fra_BAR46_3D = sys.new_Drawing3D("Fra_BAR46_3D","Fra_46",1);
	Drawing3D * Fra_BAR47_3D = sys.new_Drawing3D("Fra_BAR47_3D","Fra_47",1);
	Drawing3D * Fra_BAR48_3D = sys.new_Drawing3D("Fra_BAR48_3D","Fra_48",1);
	Drawing3D * Fra_BAR49_3D = sys.new_Drawing3D("Fra_BAR49_3D","Fra_49",1);
	Drawing3D * Fra_BAR50_3D = sys.new_Drawing3D("Fra_BAR50_3D","Fra_50",1);
	Drawing3D * Fra_BAR51_3D = sys.new_Drawing3D("Fra_BAR51_3D","Fra_51",1);
	Drawing3D * Fra_BAR52_3D = sys.new_Drawing3D("Fra_BAR52_3D","Fra_52",1);
	Drawing3D * Fra_BAR53_3D = sys.new_Drawing3D("Fra_BAR53_3D","Fra_53",1);
	Drawing3D * Fra_BAR54_3D = sys.new_Drawing3D("Fra_BAR54_3D","Fra_54",1);
	Drawing3D * Fra_BAR55_3D = sys.new_Drawing3D("Fra_BAR55_3D","Fra_55",1);
	Drawing3D * Fra_BAR56_3D = sys.new_Drawing3D("Fra_BAR56_3D","Fra_56",1);
	Drawing3D * Fra_BAR57_3D = sys.new_Drawing3D("Fra_BAR57_3D","Fra_57",1);
	Drawing3D * Fra_BAR58_3D = sys.new_Drawing3D("Fra_BAR58_3D","Fra_58",1);
	Drawing3D * Fra_BAR59_3D = sys.new_Drawing3D("Fra_BAR59_3D","Fra_59",1);
	Drawing3D * Fra_BAR60_3D = sys.new_Drawing3D("Fra_BAR60_3D","Fra_60",1);
	Drawing3D * Fra_BAR61_3D = sys.new_Drawing3D("Fra_BAR61_3D","Fra_61",1);
	Drawing3D * Fra_BAR62_3D = sys.new_Drawing3D("Fra_BAR62_3D","Fra_62",1);
	Drawing3D * Fra_BAR63_3D = sys.new_Drawing3D("Fra_BAR63_3D","Fra_63",1);
	Drawing3D * Fra_BAR64_3D = sys.new_Drawing3D("Fra_BAR64_3D","Fra_64",1);
	Drawing3D * Fra_BAR65_3D = sys.new_Drawing3D("Fra_BAR65_3D","Fra_65",1);
	Drawing3D * Fra_BAR66_3D = sys.new_Drawing3D("Fra_BAR66_3D","Fra_66",1);
	Drawing3D * Fra_BAR67_3D = sys.new_Drawing3D("Fra_BAR67_3D","Fra_67",1);
	Drawing3D * Fra_BAR68_3D = sys.new_Drawing3D("Fra_BAR68_3D","Fra_68",1);
	Drawing3D * Fra_BAR69_3D = sys.new_Drawing3D("Fra_BAR69_3D","Fra_69",1);
	Drawing3D * Fra_BAR70_3D = sys.new_Drawing3D("Fra_BAR70_3D","Fra_70",1);
	Drawing3D * Fra_BAR71_3D = sys.new_Drawing3D("Fra_BAR71_3D","Fra_71",1);
	Drawing3D * Fra_BAR72_3D = sys.new_Drawing3D("Fra_BAR72_3D","Fra_72",1);
	Drawing3D * Fra_BAR73_3D = sys.new_Drawing3D("Fra_BAR73_3D","Fra_73",1);
	Drawing3D * Fra_BAR74_3D = sys.new_Drawing3D("Fra_BAR74_3D","Fra_74",1);
	Drawing3D * Fra_BAR75_3D = sys.new_Drawing3D("Fra_BAR75_3D","Fra_75",1);
	Drawing3D * Fra_BAR76_3D = sys.new_Drawing3D("Fra_BAR76_3D","Fra_76",1);
	Drawing3D * Fra_BAR77_3D = sys.new_Drawing3D("Fra_BAR77_3D","Fra_77",1);
	Drawing3D * Fra_BAR78_3D = sys.new_Drawing3D("Fra_BAR78_3D","Fra_78",1);
	Drawing3D * Fra_BAR79_3D = sys.new_Drawing3D("Fra_BAR79_3D","Fra_79",1);
	Drawing3D * Fra_BAR80_3D = sys.new_Drawing3D("Fra_BAR80_3D","Fra_80",1);
	Drawing3D * Fra_BAR81_3D = sys.new_Drawing3D("Fra_BAR81_3D","Fra_81",1);
	Drawing3D * Fra_BAR82_3D = sys.new_Drawing3D("Fra_BAR82_3D","Fra_82",1);
	Drawing3D * Fra_BAR83_3D = sys.new_Drawing3D("Fra_BAR83_3D","Fra_83",1);
	Drawing3D * Fra_BAR84_3D = sys.new_Drawing3D("Fra_BAR84_3D","Fra_84",1);
	Drawing3D * Fra_BAR85_3D = sys.new_Drawing3D("Fra_BAR85_3D","Fra_85",1);
	Drawing3D * Fra_BAR86_3D = sys.new_Drawing3D("Fra_BAR86_3D","Fra_86",1);
	Drawing3D * Fra_BAR87_3D = sys.new_Drawing3D("Fra_BAR87_3D","Fra_87",1);
	Drawing3D * Fra_BAR88_3D = sys.new_Drawing3D("Fra_BAR88_3D","Fra_88",1);
	Drawing3D * Fra_BAR89_3D = sys.new_Drawing3D("Fra_BAR89_3D","Fra_89",1);
	Drawing3D * Fra_BAR90_3D = sys.new_Drawing3D("Fra_BAR90_3D","Fra_90",1);
	Drawing3D * Fra_BAR91_3D = sys.new_Drawing3D("Fra_BAR91_3D","Fra_91",1);
	Drawing3D * Fra_BAR92_3D = sys.new_Drawing3D("Fra_BAR92_3D","Fra_92",1);
	Drawing3D * Fra_BAR93_3D = sys.new_Drawing3D("Fra_BAR93_3D","Fra_93",1);
	Drawing3D * Fra_BAR94_3D = sys.new_Drawing3D("Fra_BAR94_3D","Fra_94",1);
	Drawing3D * Fra_BAR95_3D = sys.new_Drawing3D("Fra_BAR95_3D","Fra_95",1);
	Drawing3D * Fra_BAR96_3D = sys.new_Drawing3D("Fra_BAR96_3D","Fra_96",1);
	Drawing3D * Fra_BAR97_3D = sys.new_Drawing3D("Fra_BAR97_3D","Fra_97",1);
	Drawing3D * Fra_BAR98_3D = sys.new_Drawing3D("Fra_BAR98_3D","Fra_98",1);
	Drawing3D * Fra_BAR99_3D = sys.new_Drawing3D("Fra_BAR99_3D","Fra_99",1);
	Drawing3D * Fra_BAR100_3D = sys.new_Drawing3D("Fra_BAR100_3D","Fra_100",1);



// ************************************************************************************************
//	Forces Definition
// ************************************************************************************************

//	symbol_numeric Ma1 = *sys.new_Parameter("Ma1",0.0);
//	symbol_numeric Ma2 = *sys.new_Parameter("Ma2",0.0);
//	symbol_numeric Ma3 = *sys.new_Parameter("Ma3",0.0);
//	symbol_numeric Ma4 = *sys.new_Parameter("Ma4",0.0);
//	symbol_numeric Ma5 = *sys.new_Parameter("Ma5",0.0);
//	symbol_numeric Ma6 = *sys.new_Parameter("Ma6",0.0);
//	symbol_numeric Ma7 = *sys.new_Parameter("Ma7",0.0);
//	symbol_numeric Ma8 = *sys.new_Parameter("Ma8",0.0);
//	symbol_numeric Ma9 = *sys.new_Parameter("Ma9",0.0);
//	symbol_numeric Ma10 = *sys.new_Parameter("Ma10",0.0);
//	symbol_numeric Ma11 = *sys.new_Parameter("Ma11",0.0);
//	symbol_numeric Ma12 = *sys.new_Parameter("Ma12",0.0);
//	symbol_numeric Ma13 = *sys.new_Parameter("Ma13",0.0);
//	symbol_numeric Ma14 = *sys.new_Parameter("Ma14",0.0);
//	symbol_numeric Ma15 = *sys.new_Parameter("Ma15",0.0);
//	symbol_numeric Ma16 = *sys.new_Parameter("Ma16",0.0);
//	symbol_numeric Ma17 = *sys.new_Parameter("Ma17",0.0);
//	symbol_numeric Ma18 = *sys.new_Parameter("Ma18",0.0);
//	symbol_numeric Ma19 = *sys.new_Parameter("Ma19",0.0);
//	symbol_numeric Ma20 = *sys.new_Parameter("Ma20",0.0);
//	symbol_numeric Ma21 = *sys.new_Parameter("Ma21",0.0);
//	symbol_numeric Ma22 = *sys.new_Parameter("Ma22",0.0);
//	symbol_numeric Ma23 = *sys.new_Parameter("Ma23",0.0);
//	symbol_numeric Ma24 = *sys.new_Parameter("Ma24",0.0);
//	symbol_numeric Ma25 = *sys.new_Parameter("Ma25",0.0);
//	symbol_numeric Ma26 = *sys.new_Parameter("Ma26",0.0);
//	symbol_numeric Ma27 = *sys.new_Parameter("Ma27",0.0);
//	symbol_numeric Ma28 = *sys.new_Parameter("Ma28",0.0);
//	symbol_numeric Ma29 = *sys.new_Parameter("Ma29",0.0);
//	symbol_numeric Ma30 = *sys.new_Parameter("Ma30",0.0);
//	symbol_numeric Ma31 = *sys.new_Parameter("Ma31",0.0);
//	symbol_numeric Ma32 = *sys.new_Parameter("Ma32",0.0);
//	symbol_numeric Ma33 = *sys.new_Parameter("Ma33",0.0);
//	symbol_numeric Ma34 = *sys.new_Parameter("Ma34",0.0);
//	symbol_numeric Ma35 = *sys.new_Parameter("Ma35",0.0);
//	symbol_numeric Ma36 = *sys.new_Parameter("Ma36",0.0);
//	symbol_numeric Ma37 = *sys.new_Parameter("Ma37",0.0);
//	symbol_numeric Ma38 = *sys.new_Parameter("Ma38",0.0);
//	symbol_numeric Ma39 = *sys.new_Parameter("Ma39",0.0);
//	symbol_numeric Ma40 = *sys.new_Parameter("Ma40",0.0);
//	symbol_numeric Ma41 = *sys.new_Parameter("Ma41",0.0);
//	symbol_numeric Ma42 = *sys.new_Parameter("Ma42",0.0);
//	symbol_numeric Ma43 = *sys.new_Parameter("Ma43",0.0);
//	symbol_numeric Ma44 = *sys.new_Parameter("Ma44",0.0);
//	symbol_numeric Ma45 = *sys.new_Parameter("Ma45",0.0);
//	symbol_numeric Ma46 = *sys.new_Parameter("Ma46",0.0);
//	symbol_numeric Ma47 = *sys.new_Parameter("Ma47",0.0);
//	symbol_numeric Ma48 = *sys.new_Parameter("Ma48",0.0);
//	symbol_numeric Ma49 = *sys.new_Parameter("Ma49",0.0);
//	symbol_numeric Ma50 = *sys.new_Parameter("Ma50",0.0);
//	symbol_numeric Ma51 = *sys.new_Parameter("Ma51",0.0);
//	symbol_numeric Ma52 = *sys.new_Parameter("Ma52",0.0);
//	symbol_numeric Ma53 = *sys.new_Parameter("Ma53",0.0);
//	symbol_numeric Ma54 = *sys.new_Parameter("Ma54",0.0);
//	symbol_numeric Ma55 = *sys.new_Parameter("Ma55",0.0);
//	symbol_numeric Ma56 = *sys.new_Parameter("Ma56",0.0);
//	symbol_numeric Ma57 = *sys.new_Parameter("Ma57",0.0);
//	symbol_numeric Ma58 = *sys.new_Parameter("Ma58",0.0);
//	symbol_numeric Ma59 = *sys.new_Parameter("Ma59",0.0);
//	symbol_numeric Ma60 = *sys.new_Parameter("Ma60",0.0);
//	symbol_numeric Ma61 = *sys.new_Parameter("Ma61",0.0);
//	symbol_numeric Ma62 = *sys.new_Parameter("Ma62",0.0);
//	symbol_numeric Ma63 = *sys.new_Parameter("Ma63",0.0);
//	symbol_numeric Ma64 = *sys.new_Parameter("Ma64",0.0);
//	symbol_numeric Ma65 = *sys.new_Parameter("Ma65",0.0);
//	symbol_numeric Ma66 = *sys.new_Parameter("Ma66",0.0);
//	symbol_numeric Ma67 = *sys.new_Parameter("Ma67",0.0);
//	symbol_numeric Ma68 = *sys.new_Parameter("Ma68",0.0);
//	symbol_numeric Ma69 = *sys.new_Parameter("Ma69",0.0);
//	symbol_numeric Ma70 = *sys.new_Parameter("Ma70",0.0);
//	symbol_numeric Ma71 = *sys.new_Parameter("Ma71",0.0);
//	symbol_numeric Ma72 = *sys.new_Parameter("Ma72",0.0);
//	symbol_numeric Ma73 = *sys.new_Parameter("Ma73",0.0);
//	symbol_numeric Ma74 = *sys.new_Parameter("Ma74",0.0);
//	symbol_numeric Ma75 = *sys.new_Parameter("Ma75",0.0);
//	symbol_numeric Ma76 = *sys.new_Parameter("Ma76",0.0);
//	symbol_numeric Ma77 = *sys.new_Parameter("Ma77",0.0);
//	symbol_numeric Ma78 = *sys.new_Parameter("Ma78",0.0);
//	symbol_numeric Ma79 = *sys.new_Parameter("Ma79",0.0);
//	symbol_numeric Ma80 = *sys.new_Parameter("Ma80",0.0);
//	symbol_numeric Ma81 = *sys.new_Parameter("Ma81",0.0);
//	symbol_numeric Ma82 = *sys.new_Parameter("Ma82",0.0);
//	symbol_numeric Ma83 = *sys.new_Parameter("Ma83",0.0);
//	symbol_numeric Ma84 = *sys.new_Parameter("Ma84",0.0);
//	symbol_numeric Ma85 = *sys.new_Parameter("Ma85",0.0);
//	symbol_numeric Ma86 = *sys.new_Parameter("Ma86",0.0);
//	symbol_numeric Ma87 = *sys.new_Parameter("Ma87",0.0);
//	symbol_numeric Ma88 = *sys.new_Parameter("Ma88",0.0);
//	symbol_numeric Ma89 = *sys.new_Parameter("Ma89",0.0);
//	symbol_numeric Ma90 = *sys.new_Parameter("Ma90",0.0);
//	symbol_numeric Ma91 = *sys.new_Parameter("Ma91",0.0);
//	symbol_numeric Ma92 = *sys.new_Parameter("Ma92",0.0);
//	symbol_numeric Ma93 = *sys.new_Parameter("Ma93",0.0);
//	symbol_numeric Ma94 = *sys.new_Parameter("Ma94",0.0);
//	symbol_numeric Ma95 = *sys.new_Parameter("Ma95",0.0);
//	symbol_numeric Ma96 = *sys.new_Parameter("Ma96",0.0);
//	symbol_numeric Ma97 = *sys.new_Parameter("Ma97",0.0);
//	symbol_numeric Ma98 = *sys.new_Parameter("Ma98",0.0);
//	symbol_numeric Ma99 = *sys.new_Parameter("Ma99",0.0);
//	symbol_numeric Ma100 = *sys.new_Parameter("Ma100",0.0);

	Vector3D F1 = *sys.new_Vector3D("F1",0.0,0.0,0.0, "B1");	
	Vector3D F2 = *sys.new_Vector3D("F2",0.0,0.0,0.0, "B2");	
	Vector3D F3 = *sys.new_Vector3D("F3",0.0,0.0,0.0, "B3");	
	Vector3D F4 = *sys.new_Vector3D("F4",0.0,0.0,0.0, "B4");	
	Vector3D F5 = *sys.new_Vector3D("F5",0.0,0.0,0.0, "B5");	
	Vector3D F6 = *sys.new_Vector3D("F6",0.0,0.0,0.0, "B6");	
	Vector3D F7 = *sys.new_Vector3D("F7",0.0,0.0,0.0, "B7");	
	Vector3D F8 = *sys.new_Vector3D("F8",0.0,0.0,0.0, "B8");	
	Vector3D F9 = *sys.new_Vector3D("F9",0.0,0.0,0.0, "B9");	
	Vector3D F10 = *sys.new_Vector3D("F10",0.0,0.0,0.0, "B10");	
	Vector3D F11 = *sys.new_Vector3D("F11",0.0,0.0,0.0, "B11");	
	Vector3D F12 = *sys.new_Vector3D("F12",0.0,0.0,0.0, "B12");	
	Vector3D F13 = *sys.new_Vector3D("F13",0.0,0.0,0.0, "B13");	
	Vector3D F14 = *sys.new_Vector3D("F14",0.0,0.0,0.0, "B14");	
	Vector3D F15 = *sys.new_Vector3D("F15",0.0,0.0,0.0, "B15");	
	Vector3D F16 = *sys.new_Vector3D("F16",0.0,0.0,0.0, "B16");	
	Vector3D F17 = *sys.new_Vector3D("F17",0.0,0.0,0.0, "B17");	
	Vector3D F18 = *sys.new_Vector3D("F18",0.0,0.0,0.0, "B18");	
	Vector3D F19 = *sys.new_Vector3D("F19",0.0,0.0,0.0, "B19");	
	Vector3D F20 = *sys.new_Vector3D("F20",0.0,0.0,0.0, "B20");	
	Vector3D F21 = *sys.new_Vector3D("F21",0.0,0.0,0.0, "B21");	
	Vector3D F22 = *sys.new_Vector3D("F22",0.0,0.0,0.0, "B22");	
	Vector3D F23 = *sys.new_Vector3D("F23",0.0,0.0,0.0, "B23");	
	Vector3D F24 = *sys.new_Vector3D("F24",0.0,0.0,0.0, "B24");	
	Vector3D F25 = *sys.new_Vector3D("F25",0.0,0.0,0.0, "B25");	
	Vector3D F26 = *sys.new_Vector3D("F26",0.0,0.0,0.0, "B26");	
	Vector3D F27 = *sys.new_Vector3D("F27",0.0,0.0,0.0, "B27");	
	Vector3D F28 = *sys.new_Vector3D("F28",0.0,0.0,0.0, "B28");	
	Vector3D F29 = *sys.new_Vector3D("F29",0.0,0.0,0.0, "B29");	
	Vector3D F30 = *sys.new_Vector3D("F30",0.0,0.0,0.0, "B30");	
	Vector3D F31 = *sys.new_Vector3D("F31",0.0,0.0,0.0, "B31");	
	Vector3D F32 = *sys.new_Vector3D("F32",0.0,0.0,0.0, "B32");	
	Vector3D F33 = *sys.new_Vector3D("F33",0.0,0.0,0.0, "B33");	
	Vector3D F34 = *sys.new_Vector3D("F34",0.0,0.0,0.0, "B34");	
	Vector3D F35 = *sys.new_Vector3D("F35",0.0,0.0,0.0, "B35");	
	Vector3D F36 = *sys.new_Vector3D("F36",0.0,0.0,0.0, "B36");	
	Vector3D F37 = *sys.new_Vector3D("F37",0.0,0.0,0.0, "B37");	
	Vector3D F38 = *sys.new_Vector3D("F38",0.0,0.0,0.0, "B38");	
	Vector3D F39 = *sys.new_Vector3D("F39",0.0,0.0,0.0, "B39");	
	Vector3D F40 = *sys.new_Vector3D("F40",0.0,0.0,0.0, "B40");	
	Vector3D F41 = *sys.new_Vector3D("F41",0.0,0.0,0.0, "B41");	
	Vector3D F42 = *sys.new_Vector3D("F42",0.0,0.0,0.0, "B42");	
	Vector3D F43 = *sys.new_Vector3D("F43",0.0,0.0,0.0, "B43");	
	Vector3D F44 = *sys.new_Vector3D("F44",0.0,0.0,0.0, "B44");	
	Vector3D F45 = *sys.new_Vector3D("F45",0.0,0.0,0.0, "B45");	
	Vector3D F46 = *sys.new_Vector3D("F46",0.0,0.0,0.0, "B46");	
	Vector3D F47 = *sys.new_Vector3D("F47",0.0,0.0,0.0, "B47");	
	Vector3D F48 = *sys.new_Vector3D("F48",0.0,0.0,0.0, "B48");	
	Vector3D F49 = *sys.new_Vector3D("F49",0.0,0.0,0.0, "B49");	
	Vector3D F50 = *sys.new_Vector3D("F50",0.0,0.0,0.0, "B50");	
	Vector3D F51 = *sys.new_Vector3D("F51",0.0,0.0,0.0, "B51");	
	Vector3D F52 = *sys.new_Vector3D("F52",0.0,0.0,0.0, "B52");	
	Vector3D F53 = *sys.new_Vector3D("F53",0.0,0.0,0.0, "B53");	
	Vector3D F54 = *sys.new_Vector3D("F54",0.0,0.0,0.0, "B54");	
	Vector3D F55 = *sys.new_Vector3D("F55",0.0,0.0,0.0, "B55");	
	Vector3D F56 = *sys.new_Vector3D("F56",0.0,0.0,0.0, "B56");	
	Vector3D F57 = *sys.new_Vector3D("F57",0.0,0.0,0.0, "B57");	
	Vector3D F58 = *sys.new_Vector3D("F58",0.0,0.0,0.0, "B58");	
	Vector3D F59 = *sys.new_Vector3D("F59",0.0,0.0,0.0, "B59");	
	Vector3D F60 = *sys.new_Vector3D("F60",0.0,0.0,0.0, "B60");	
	Vector3D F61 = *sys.new_Vector3D("F61",0.0,0.0,0.0, "B61");	
	Vector3D F62 = *sys.new_Vector3D("F62",0.0,0.0,0.0, "B62");	
	Vector3D F63 = *sys.new_Vector3D("F63",0.0,0.0,0.0, "B63");	
	Vector3D F64 = *sys.new_Vector3D("F64",0.0,0.0,0.0, "B64");	
	Vector3D F65 = *sys.new_Vector3D("F65",0.0,0.0,0.0, "B65");	
	Vector3D F66 = *sys.new_Vector3D("F66",0.0,0.0,0.0, "B66");	
	Vector3D F67 = *sys.new_Vector3D("F67",0.0,0.0,0.0, "B67");	
	Vector3D F68 = *sys.new_Vector3D("F68",0.0,0.0,0.0, "B68");	
	Vector3D F69 = *sys.new_Vector3D("F69",0.0,0.0,0.0, "B69");	
	Vector3D F70 = *sys.new_Vector3D("F70",0.0,0.0,0.0, "B70");	
	Vector3D F71 = *sys.new_Vector3D("F71",0.0,0.0,0.0, "B71");	
	Vector3D F72 = *sys.new_Vector3D("F72",0.0,0.0,0.0, "B72");	
	Vector3D F73 = *sys.new_Vector3D("F73",0.0,0.0,0.0, "B73");	
	Vector3D F74 = *sys.new_Vector3D("F74",0.0,0.0,0.0, "B74");	
	Vector3D F75 = *sys.new_Vector3D("F75",0.0,0.0,0.0, "B75");	
	Vector3D F76 = *sys.new_Vector3D("F76",0.0,0.0,0.0, "B76");	
	Vector3D F77 = *sys.new_Vector3D("F77",0.0,0.0,0.0, "B77");	
	Vector3D F78 = *sys.new_Vector3D("F78",0.0,0.0,0.0, "B78");	
	Vector3D F79 = *sys.new_Vector3D("F79",0.0,0.0,0.0, "B79");	
	Vector3D F80 = *sys.new_Vector3D("F80",0.0,0.0,0.0, "B80");	
	Vector3D F81 = *sys.new_Vector3D("F81",0.0,0.0,0.0, "B81");	
	Vector3D F82 = *sys.new_Vector3D("F82",0.0,0.0,0.0, "B82");	
	Vector3D F83 = *sys.new_Vector3D("F83",0.0,0.0,0.0, "B83");	
	Vector3D F84 = *sys.new_Vector3D("F84",0.0,0.0,0.0, "B84");	
	Vector3D F85 = *sys.new_Vector3D("F85",0.0,0.0,0.0, "B85");	
	Vector3D F86 = *sys.new_Vector3D("F86",0.0,0.0,0.0, "B86");	
	Vector3D F87 = *sys.new_Vector3D("F87",0.0,0.0,0.0, "B87");	
	Vector3D F88 = *sys.new_Vector3D("F88",0.0,0.0,0.0, "B88");	
	Vector3D F89 = *sys.new_Vector3D("F89",0.0,0.0,0.0, "B89");	
	Vector3D F90 = *sys.new_Vector3D("F90",0.0,0.0,0.0, "B90");	
	Vector3D F91 = *sys.new_Vector3D("F91",0.0,0.0,0.0, "B91");	
	Vector3D F92 = *sys.new_Vector3D("F92",0.0,0.0,0.0, "B92");	
	Vector3D F93 = *sys.new_Vector3D("F93",0.0,0.0,0.0, "B93");	
	Vector3D F94 = *sys.new_Vector3D("F94",0.0,0.0,0.0, "B94");	
	Vector3D F95 = *sys.new_Vector3D("F95",0.0,0.0,0.0, "B95");	
	Vector3D F96 = *sys.new_Vector3D("F96",0.0,0.0,0.0, "B96");	
	Vector3D F97 = *sys.new_Vector3D("F97",0.0,0.0,0.0, "B97");	
	Vector3D F98 = *sys.new_Vector3D("F98",0.0,0.0,0.0, "B98");	
	Vector3D F99 = *sys.new_Vector3D("F99",0.0,0.0,0.0, "B99");	
	Vector3D F100 = *sys.new_Vector3D("F100",0.0,0.0,0.0, "B100");	

// ************************************************************************************************
//	DAMPING Definition
// ************************************************************************************************
	double c=1.0;
	Vector3D M1 = *sys.new_Vector3D("M1",0.0,0.0,-c*(*dq1-*dq2), "B1");
	Vector3D M2 = *sys.new_Vector3D("M2",0.0,0.0,-c*(2**dq2-*dq1-*dq3), "B2");
	Vector3D M3 = *sys.new_Vector3D("M3",0.0,0.0,-c*(2**dq3-*dq2-*dq4), "B3");
	Vector3D M4 = *sys.new_Vector3D("M4",0.0,0.0,-c*(2**dq4-*dq3-*dq5), "B4");
	Vector3D M5 = *sys.new_Vector3D("M5",0.0,0.0,-c*(2**dq5-*dq4-*dq6), "B5");
	Vector3D M6 = *sys.new_Vector3D("M6",0.0,0.0,-c*(2**dq6-*dq5-*dq7), "B6");
	Vector3D M7 = *sys.new_Vector3D("M7",0.0,0.0,-c*(2**dq7-*dq6-*dq8), "B7");
	Vector3D M8 = *sys.new_Vector3D("M8",0.0,0.0,-c*(2**dq8-*dq7-*dq9), "B8");
	Vector3D M9 = *sys.new_Vector3D("M9",0.0,0.0,-c*(2**dq9-*dq8-*dq10), "B9");
	Vector3D M10 = *sys.new_Vector3D("M10",0.0,0.0,-c*(2**dq10-*dq9-*dq11), "B10");
	Vector3D M11 = *sys.new_Vector3D("M11",0.0,0.0,-c*(2**dq11-*dq10-*dq12), "B11");
	Vector3D M12 = *sys.new_Vector3D("M12",0.0,0.0,-c*(2**dq12-*dq11-*dq13), "B12");
	Vector3D M13 = *sys.new_Vector3D("M13",0.0,0.0,-c*(2**dq13-*dq12-*dq14), "B13");
	Vector3D M14 = *sys.new_Vector3D("M14",0.0,0.0,-c*(2**dq14-*dq13-*dq15), "B14");
	Vector3D M15 = *sys.new_Vector3D("M15",0.0,0.0,-c*(2**dq15-*dq14-*dq16), "B15");
	Vector3D M16 = *sys.new_Vector3D("M16",0.0,0.0,-c*(2**dq16-*dq15-*dq17), "B16");
	Vector3D M17 = *sys.new_Vector3D("M17",0.0,0.0,-c*(2**dq17-*dq16-*dq18), "B17");
	Vector3D M18 = *sys.new_Vector3D("M18",0.0,0.0,-c*(2**dq18-*dq17-*dq19), "B18");
	Vector3D M19 = *sys.new_Vector3D("M19",0.0,0.0,-c*(2**dq19-*dq18-*dq20), "B19");
	Vector3D M20 = *sys.new_Vector3D("M20",0.0,0.0,-c*(2**dq20-*dq19-*dq21), "B20");
	Vector3D M21 = *sys.new_Vector3D("M21",0.0,0.0,-c*(2**dq21-*dq20-*dq22), "B21");
	Vector3D M22 = *sys.new_Vector3D("M22",0.0,0.0,-c*(2**dq22-*dq21-*dq23), "B22");
	Vector3D M23 = *sys.new_Vector3D("M23",0.0,0.0,-c*(2**dq23-*dq22-*dq24), "B23");
	Vector3D M24 = *sys.new_Vector3D("M24",0.0,0.0,-c*(2**dq24-*dq23-*dq25), "B24");
	Vector3D M25 = *sys.new_Vector3D("M25",0.0,0.0,-c*(2**dq25-*dq24-*dq26), "B25");
	Vector3D M26 = *sys.new_Vector3D("M26",0.0,0.0,-c*(2**dq26-*dq25-*dq27), "B26");
	Vector3D M27 = *sys.new_Vector3D("M27",0.0,0.0,-c*(2**dq27-*dq26-*dq28), "B27");
	Vector3D M28 = *sys.new_Vector3D("M28",0.0,0.0,-c*(2**dq28-*dq27-*dq29), "B28");
	Vector3D M29 = *sys.new_Vector3D("M29",0.0,0.0,-c*(2**dq29-*dq28-*dq30), "B29");
	Vector3D M30 = *sys.new_Vector3D("M30",0.0,0.0,-c*(2**dq30-*dq29-*dq31), "B30");
	Vector3D M31 = *sys.new_Vector3D("M31",0.0,0.0,-c*(2**dq31-*dq30-*dq32), "B31");
	Vector3D M32 = *sys.new_Vector3D("M32",0.0,0.0,-c*(2**dq32-*dq31-*dq33), "B32");
	Vector3D M33 = *sys.new_Vector3D("M33",0.0,0.0,-c*(2**dq33-*dq32-*dq34), "B33");
	Vector3D M34 = *sys.new_Vector3D("M34",0.0,0.0,-c*(2**dq34-*dq33-*dq35), "B34");
	Vector3D M35 = *sys.new_Vector3D("M35",0.0,0.0,-c*(2**dq35-*dq34-*dq36), "B35");
	Vector3D M36 = *sys.new_Vector3D("M36",0.0,0.0,-c*(2**dq36-*dq35-*dq37), "B36");
	Vector3D M37 = *sys.new_Vector3D("M37",0.0,0.0,-c*(2**dq37-*dq36-*dq38), "B37");
	Vector3D M38 = *sys.new_Vector3D("M38",0.0,0.0,-c*(2**dq38-*dq37-*dq39), "B38");
	Vector3D M39 = *sys.new_Vector3D("M39",0.0,0.0,-c*(2**dq39-*dq38-*dq40), "B39");
	Vector3D M40 = *sys.new_Vector3D("M40",0.0,0.0,-c*(2**dq40-*dq39-*dq41), "B40");
	Vector3D M41 = *sys.new_Vector3D("M41",0.0,0.0,-c*(2**dq41-*dq40-*dq42), "B41");
	Vector3D M42 = *sys.new_Vector3D("M42",0.0,0.0,-c*(2**dq42-*dq41-*dq43), "B42");
	Vector3D M43 = *sys.new_Vector3D("M43",0.0,0.0,-c*(2**dq43-*dq42-*dq44), "B43");
	Vector3D M44 = *sys.new_Vector3D("M44",0.0,0.0,-c*(2**dq44-*dq43-*dq45), "B44");
	Vector3D M45 = *sys.new_Vector3D("M45",0.0,0.0,-c*(2**dq45-*dq44-*dq46), "B45");
	Vector3D M46 = *sys.new_Vector3D("M46",0.0,0.0,-c*(2**dq46-*dq45-*dq47), "B46");
	Vector3D M47 = *sys.new_Vector3D("M47",0.0,0.0,-c*(2**dq47-*dq46-*dq48), "B47");
	Vector3D M48 = *sys.new_Vector3D("M48",0.0,0.0,-c*(2**dq48-*dq47-*dq49), "B48");
	Vector3D M49 = *sys.new_Vector3D("M49",0.0,0.0,-c*(2**dq49-*dq48-*dq50), "B49");
	Vector3D M50 = *sys.new_Vector3D("M50",0.0,0.0,-c*(2**dq50-*dq49-*dq51), "B50");
	Vector3D M51 = *sys.new_Vector3D("M51",0.0,0.0,-c*(2**dq51-*dq50-*dq52), "B51");
	Vector3D M52 = *sys.new_Vector3D("M52",0.0,0.0,-c*(2**dq52-*dq51-*dq53), "B52");
	Vector3D M53 = *sys.new_Vector3D("M53",0.0,0.0,-c*(2**dq53-*dq52-*dq54), "B53");
	Vector3D M54 = *sys.new_Vector3D("M54",0.0,0.0,-c*(2**dq54-*dq53-*dq55), "B54");
	Vector3D M55 = *sys.new_Vector3D("M55",0.0,0.0,-c*(2**dq55-*dq54-*dq56), "B55");
	Vector3D M56 = *sys.new_Vector3D("M56",0.0,0.0,-c*(2**dq56-*dq55-*dq57), "B56");
	Vector3D M57 = *sys.new_Vector3D("M57",0.0,0.0,-c*(2**dq57-*dq56-*dq58), "B57");
	Vector3D M58 = *sys.new_Vector3D("M58",0.0,0.0,-c*(2**dq58-*dq57-*dq59), "B58");
	Vector3D M59 = *sys.new_Vector3D("M59",0.0,0.0,-c*(2**dq59-*dq58-*dq60), "B59");
	Vector3D M60 = *sys.new_Vector3D("M60",0.0,0.0,-c*(2**dq60-*dq59-*dq61), "B60");
	Vector3D M61 = *sys.new_Vector3D("M61",0.0,0.0,-c*(2**dq61-*dq60-*dq62), "B61");
	Vector3D M62 = *sys.new_Vector3D("M62",0.0,0.0,-c*(2**dq62-*dq61-*dq63), "B62");
	Vector3D M63 = *sys.new_Vector3D("M63",0.0,0.0,-c*(2**dq63-*dq62-*dq64), "B63");
	Vector3D M64 = *sys.new_Vector3D("M64",0.0,0.0,-c*(2**dq64-*dq63-*dq65), "B64");
	Vector3D M65 = *sys.new_Vector3D("M65",0.0,0.0,-c*(2**dq65-*dq64-*dq66), "B65");
	Vector3D M66 = *sys.new_Vector3D("M66",0.0,0.0,-c*(2**dq66-*dq65-*dq67), "B66");
	Vector3D M67 = *sys.new_Vector3D("M67",0.0,0.0,-c*(2**dq67-*dq66-*dq68), "B67");
	Vector3D M68 = *sys.new_Vector3D("M68",0.0,0.0,-c*(2**dq68-*dq67-*dq69), "B68");
	Vector3D M69 = *sys.new_Vector3D("M69",0.0,0.0,-c*(2**dq69-*dq68-*dq70), "B69");
	Vector3D M70 = *sys.new_Vector3D("M70",0.0,0.0,-c*(2**dq70-*dq69-*dq71), "B70");
	Vector3D M71 = *sys.new_Vector3D("M71",0.0,0.0,-c*(2**dq71-*dq70-*dq72), "B71");
	Vector3D M72 = *sys.new_Vector3D("M72",0.0,0.0,-c*(2**dq72-*dq71-*dq73), "B72");
	Vector3D M73 = *sys.new_Vector3D("M73",0.0,0.0,-c*(2**dq73-*dq72-*dq74), "B73");
	Vector3D M74 = *sys.new_Vector3D("M74",0.0,0.0,-c*(2**dq74-*dq73-*dq75), "B74");
	Vector3D M75 = *sys.new_Vector3D("M75",0.0,0.0,-c*(2**dq75-*dq74-*dq76), "B75");
	Vector3D M76 = *sys.new_Vector3D("M76",0.0,0.0,-c*(2**dq76-*dq75-*dq77), "B76");
	Vector3D M77 = *sys.new_Vector3D("M77",0.0,0.0,-c*(2**dq77-*dq76-*dq78), "B77");
	Vector3D M78 = *sys.new_Vector3D("M78",0.0,0.0,-c*(2**dq78-*dq77-*dq79), "B78");
	Vector3D M79 = *sys.new_Vector3D("M79",0.0,0.0,-c*(2**dq79-*dq78-*dq80), "B79");
	Vector3D M80 = *sys.new_Vector3D("M80",0.0,0.0,-c*(2**dq80-*dq79-*dq81), "B80");
	Vector3D M81 = *sys.new_Vector3D("M81",0.0,0.0,-c*(2**dq81-*dq80-*dq82), "B81");
	Vector3D M82 = *sys.new_Vector3D("M82",0.0,0.0,-c*(2**dq82-*dq81-*dq83), "B82");
	Vector3D M83 = *sys.new_Vector3D("M83",0.0,0.0,-c*(2**dq83-*dq82-*dq84), "B83");
	Vector3D M84 = *sys.new_Vector3D("M84",0.0,0.0,-c*(2**dq84-*dq83-*dq85), "B84");
	Vector3D M85 = *sys.new_Vector3D("M85",0.0,0.0,-c*(2**dq85-*dq84-*dq86), "B85");
	Vector3D M86 = *sys.new_Vector3D("M86",0.0,0.0,-c*(2**dq86-*dq85-*dq87), "B86");
	Vector3D M87 = *sys.new_Vector3D("M87",0.0,0.0,-c*(2**dq87-*dq86-*dq88), "B87");
	Vector3D M88 = *sys.new_Vector3D("M88",0.0,0.0,-c*(2**dq88-*dq87-*dq89), "B88");
	Vector3D M89 = *sys.new_Vector3D("M89",0.0,0.0,-c*(2**dq89-*dq88-*dq90), "B89");
	Vector3D M90 = *sys.new_Vector3D("M90",0.0,0.0,-c*(2**dq90-*dq89-*dq91), "B90");
	Vector3D M91 = *sys.new_Vector3D("M91",0.0,0.0,-c*(2**dq91-*dq90-*dq92), "B91");
	Vector3D M92 = *sys.new_Vector3D("M92",0.0,0.0,-c*(2**dq92-*dq91-*dq93), "B92");
	Vector3D M93 = *sys.new_Vector3D("M93",0.0,0.0,-c*(2**dq93-*dq92-*dq94), "B93");
	Vector3D M94 = *sys.new_Vector3D("M94",0.0,0.0,-c*(2**dq94-*dq93-*dq95), "B94");
	Vector3D M95 = *sys.new_Vector3D("M95",0.0,0.0,-c*(2**dq95-*dq94-*dq96), "B95");
	Vector3D M96 = *sys.new_Vector3D("M96",0.0,0.0,-c*(2**dq96-*dq95-*dq97), "B96");
	Vector3D M97 = *sys.new_Vector3D("M97",0.0,0.0,-c*(2**dq97-*dq96-*dq98), "B97");
	Vector3D M98 = *sys.new_Vector3D("M98",0.0,0.0,-c*(2**dq98-*dq97-*dq99), "B98");
	Vector3D M99 = *sys.new_Vector3D("M99",0.0,0.0,-c*(2**dq99-*dq98-*dq100), "B99");
	Vector3D M100 = *sys.new_Vector3D("M100",0.0,0.0,-c*(*dq100-*dq99), "B100");
//	Vector3D M1 = *sys.new_Vector3D("M1",0.0,0.0,Ma1, "B1");
//	Vector3D M2 = *sys.new_Vector3D("M2",0.0,0.0,Ma2, "B2");
//	Vector3D M3 = *sys.new_Vector3D("M3",0.0,0.0,Ma3, "B3");
//	Vector3D M4 = *sys.new_Vector3D("M4",0.0,0.0,Ma4, "B4");
//	Vector3D M5 = *sys.new_Vector3D("M5",0.0,0.0,Ma5, "B5");
//	Vector3D M6 = *sys.new_Vector3D("M6",0.0,0.0,Ma6, "B6");
//	Vector3D M7 = *sys.new_Vector3D("M7",0.0,0.0,Ma7, "B7");
//	Vector3D M8 = *sys.new_Vector3D("M8",0.0,0.0,Ma8, "B8");
//	Vector3D M9 = *sys.new_Vector3D("M9",0.0,0.0,Ma9, "B9");
//	Vector3D M10 = *sys.new_Vector3D("M10",0.0,0.0,Ma10, "B10");
//	Vector3D M11 = *sys.new_Vector3D("M11",0.0,0.0,Ma11, "B11");
//	Vector3D M12 = *sys.new_Vector3D("M12",0.0,0.0,Ma12, "B12");
//	Vector3D M13 = *sys.new_Vector3D("M13",0.0,0.0,Ma13, "B13");
//	Vector3D M14 = *sys.new_Vector3D("M14",0.0,0.0,Ma14, "B14");
//	Vector3D M15 = *sys.new_Vector3D("M15",0.0,0.0,Ma15, "B15");
//	Vector3D M16 = *sys.new_Vector3D("M16",0.0,0.0,Ma16, "B16");
//	Vector3D M17 = *sys.new_Vector3D("M17",0.0,0.0,Ma17, "B17");
//	Vector3D M18 = *sys.new_Vector3D("M18",0.0,0.0,Ma18, "B18");
//	Vector3D M19 = *sys.new_Vector3D("M19",0.0,0.0,Ma19, "B19");
//	Vector3D M20 = *sys.new_Vector3D("M20",0.0,0.0,Ma20, "B20");
//	Vector3D M21 = *sys.new_Vector3D("M21",0.0,0.0,Ma21, "B21");
//	Vector3D M22 = *sys.new_Vector3D("M22",0.0,0.0,Ma22, "B22");
//	Vector3D M23 = *sys.new_Vector3D("M23",0.0,0.0,Ma23, "B23");
//	Vector3D M24 = *sys.new_Vector3D("M24",0.0,0.0,Ma24, "B24");
//	Vector3D M25 = *sys.new_Vector3D("M25",0.0,0.0,Ma25, "B25");
//	Vector3D M26 = *sys.new_Vector3D("M26",0.0,0.0,Ma26, "B26");
//	Vector3D M27 = *sys.new_Vector3D("M27",0.0,0.0,Ma27, "B27");
//	Vector3D M28 = *sys.new_Vector3D("M28",0.0,0.0,Ma28, "B28");
//	Vector3D M29 = *sys.new_Vector3D("M29",0.0,0.0,Ma29, "B29");
//	Vector3D M30 = *sys.new_Vector3D("M30",0.0,0.0,Ma30, "B30");
//	Vector3D M31 = *sys.new_Vector3D("M31",0.0,0.0,Ma31, "B31");
//	Vector3D M32 = *sys.new_Vector3D("M32",0.0,0.0,Ma32, "B32");
//	Vector3D M33 = *sys.new_Vector3D("M33",0.0,0.0,Ma33, "B33");
//	Vector3D M34 = *sys.new_Vector3D("M34",0.0,0.0,Ma34, "B34");
//	Vector3D M35 = *sys.new_Vector3D("M35",0.0,0.0,Ma35, "B35");
//	Vector3D M36 = *sys.new_Vector3D("M36",0.0,0.0,Ma36, "B36");
//	Vector3D M37 = *sys.new_Vector3D("M37",0.0,0.0,Ma37, "B37");
//	Vector3D M38 = *sys.new_Vector3D("M38",0.0,0.0,Ma38, "B38");
//	Vector3D M39 = *sys.new_Vector3D("M39",0.0,0.0,Ma39, "B39");
//	Vector3D M40 = *sys.new_Vector3D("M40",0.0,0.0,Ma40, "B40");
//	Vector3D M41 = *sys.new_Vector3D("M41",0.0,0.0,Ma41, "B41");
//	Vector3D M42 = *sys.new_Vector3D("M42",0.0,0.0,Ma42, "B42");
//	Vector3D M43 = *sys.new_Vector3D("M43",0.0,0.0,Ma43, "B43");
//	Vector3D M44 = *sys.new_Vector3D("M44",0.0,0.0,Ma44, "B44");
//	Vector3D M45 = *sys.new_Vector3D("M45",0.0,0.0,Ma45, "B45");
//	Vector3D M46 = *sys.new_Vector3D("M46",0.0,0.0,Ma46, "B46");
//	Vector3D M47 = *sys.new_Vector3D("M47",0.0,0.0,Ma47, "B47");
//	Vector3D M48 = *sys.new_Vector3D("M48",0.0,0.0,Ma48, "B48");
//	Vector3D M49 = *sys.new_Vector3D("M49",0.0,0.0,Ma49, "B49");
//	Vector3D M50 = *sys.new_Vector3D("M50",0.0,0.0,Ma50, "B50");
//	Vector3D M51 = *sys.new_Vector3D("M51",0.0,0.0,Ma51, "B51");
//	Vector3D M52 = *sys.new_Vector3D("M52",0.0,0.0,Ma52, "B52");
//	Vector3D M53 = *sys.new_Vector3D("M53",0.0,0.0,Ma53, "B53");
//	Vector3D M54 = *sys.new_Vector3D("M54",0.0,0.0,Ma54, "B54");
//	Vector3D M55 = *sys.new_Vector3D("M55",0.0,0.0,Ma55, "B55");
//	Vector3D M56 = *sys.new_Vector3D("M56",0.0,0.0,Ma56, "B56");
//	Vector3D M57 = *sys.new_Vector3D("M57",0.0,0.0,Ma57, "B57");
//	Vector3D M58 = *sys.new_Vector3D("M58",0.0,0.0,Ma58, "B58");
//	Vector3D M59 = *sys.new_Vector3D("M59",0.0,0.0,Ma59, "B59");
//	Vector3D M60 = *sys.new_Vector3D("M60",0.0,0.0,Ma60, "B60");
//	Vector3D M61 = *sys.new_Vector3D("M61",0.0,0.0,Ma61, "B61");
//	Vector3D M62 = *sys.new_Vector3D("M62",0.0,0.0,Ma62, "B62");
//	Vector3D M63 = *sys.new_Vector3D("M63",0.0,0.0,Ma63, "B63");
//	Vector3D M64 = *sys.new_Vector3D("M64",0.0,0.0,Ma64, "B64");
//	Vector3D M65 = *sys.new_Vector3D("M65",0.0,0.0,Ma65, "B65");
//	Vector3D M66 = *sys.new_Vector3D("M66",0.0,0.0,Ma66, "B66");
//	Vector3D M67 = *sys.new_Vector3D("M67",0.0,0.0,Ma67, "B67");
//	Vector3D M68 = *sys.new_Vector3D("M68",0.0,0.0,Ma68, "B68");
//	Vector3D M69 = *sys.new_Vector3D("M69",0.0,0.0,Ma69, "B69");
//	Vector3D M70 = *sys.new_Vector3D("M70",0.0,0.0,Ma70, "B70");
//	Vector3D M71 = *sys.new_Vector3D("M71",0.0,0.0,Ma71, "B71");
//	Vector3D M72 = *sys.new_Vector3D("M72",0.0,0.0,Ma72, "B72");
//	Vector3D M73 = *sys.new_Vector3D("M73",0.0,0.0,Ma73, "B73");
//	Vector3D M74 = *sys.new_Vector3D("M74",0.0,0.0,Ma74, "B74");
//	Vector3D M75 = *sys.new_Vector3D("M75",0.0,0.0,Ma75, "B75");
//	Vector3D M76 = *sys.new_Vector3D("M76",0.0,0.0,Ma76, "B76");
//	Vector3D M77 = *sys.new_Vector3D("M77",0.0,0.0,Ma77, "B77");
//	Vector3D M78 = *sys.new_Vector3D("M78",0.0,0.0,Ma78, "B78");
//	Vector3D M79 = *sys.new_Vector3D("M79",0.0,0.0,Ma79, "B79");
//	Vector3D M80 = *sys.new_Vector3D("M80",0.0,0.0,Ma80, "B80");
//	Vector3D M81 = *sys.new_Vector3D("M81",0.0,0.0,Ma81, "B81");
//	Vector3D M82 = *sys.new_Vector3D("M82",0.0,0.0,Ma82, "B82");
//	Vector3D M83 = *sys.new_Vector3D("M83",0.0,0.0,Ma83, "B83");
//	Vector3D M84 = *sys.new_Vector3D("M84",0.0,0.0,Ma84, "B84");
//	Vector3D M85 = *sys.new_Vector3D("M85",0.0,0.0,Ma85, "B85");
//	Vector3D M86 = *sys.new_Vector3D("M86",0.0,0.0,Ma86, "B86");
//	Vector3D M87 = *sys.new_Vector3D("M87",0.0,0.0,Ma87, "B87");
//	Vector3D M88 = *sys.new_Vector3D("M88",0.0,0.0,Ma88, "B88");
//	Vector3D M89 = *sys.new_Vector3D("M89",0.0,0.0,Ma89, "B89");
//	Vector3D M90 = *sys.new_Vector3D("M90",0.0,0.0,Ma90, "B90");
//	Vector3D M91 = *sys.new_Vector3D("M91",0.0,0.0,Ma91, "B91");
//	Vector3D M92 = *sys.new_Vector3D("M92",0.0,0.0,Ma92, "B92");
//	Vector3D M93 = *sys.new_Vector3D("M93",0.0,0.0,Ma93, "B93");
//	Vector3D M94 = *sys.new_Vector3D("M94",0.0,0.0,Ma94, "B94");
//	Vector3D M95 = *sys.new_Vector3D("M95",0.0,0.0,Ma95, "B95");
//	Vector3D M96 = *sys.new_Vector3D("M96",0.0,0.0,Ma96, "B96");
//	Vector3D M97 = *sys.new_Vector3D("M97",0.0,0.0,Ma97, "B97");
//	Vector3D M98 = *sys.new_Vector3D("M98",0.0,0.0,Ma98, "B98");
//	Vector3D M99 = *sys.new_Vector3D("M99",0.0,0.0,Ma99, "B99");
//	Vector3D M100 = *sys.new_Vector3D("M100",0.0,0.0,Ma100, "B100");

// ************************************************************************************************
//	Define Wrenches	
// ************************************************************************************************

	cout << "Define Wrenches" << endl;

// 	//	Gravity
	Wrench3D * Gravity1 = sys.Gravity_Wrench("BAR1");
	Wrench3D * Gravity2 = sys.Gravity_Wrench("BAR2");
	Wrench3D * Gravity3 = sys.Gravity_Wrench("BAR3");
	Wrench3D * Gravity4 = sys.Gravity_Wrench("BAR4");
	Wrench3D * Gravity5 = sys.Gravity_Wrench("BAR5");
	Wrench3D * Gravity6 = sys.Gravity_Wrench("BAR6");
	Wrench3D * Gravity7 = sys.Gravity_Wrench("BAR7");
	Wrench3D * Gravity8 = sys.Gravity_Wrench("BAR8");
	Wrench3D * Gravity9 = sys.Gravity_Wrench("BAR9");
	Wrench3D * Gravity10 = sys.Gravity_Wrench("BAR10");
	Wrench3D * Gravity11 = sys.Gravity_Wrench("BAR11");
	Wrench3D * Gravity12 = sys.Gravity_Wrench("BAR12");
	Wrench3D * Gravity13 = sys.Gravity_Wrench("BAR13");
	Wrench3D * Gravity14 = sys.Gravity_Wrench("BAR14");
	Wrench3D * Gravity15 = sys.Gravity_Wrench("BAR15");
	Wrench3D * Gravity16 = sys.Gravity_Wrench("BAR16");
	Wrench3D * Gravity17 = sys.Gravity_Wrench("BAR17");
	Wrench3D * Gravity18 = sys.Gravity_Wrench("BAR18");
	Wrench3D * Gravity19 = sys.Gravity_Wrench("BAR19");
	Wrench3D * Gravity20 = sys.Gravity_Wrench("BAR20");
	Wrench3D * Gravity21 = sys.Gravity_Wrench("BAR21");
	Wrench3D * Gravity22 = sys.Gravity_Wrench("BAR22");
	Wrench3D * Gravity23 = sys.Gravity_Wrench("BAR23");
	Wrench3D * Gravity24 = sys.Gravity_Wrench("BAR24");
	Wrench3D * Gravity25 = sys.Gravity_Wrench("BAR25");
	Wrench3D * Gravity26 = sys.Gravity_Wrench("BAR26");
	Wrench3D * Gravity27 = sys.Gravity_Wrench("BAR27");
	Wrench3D * Gravity28 = sys.Gravity_Wrench("BAR28");
	Wrench3D * Gravity29 = sys.Gravity_Wrench("BAR29");
	Wrench3D * Gravity30 = sys.Gravity_Wrench("BAR30");
	Wrench3D * Gravity31 = sys.Gravity_Wrench("BAR31");
	Wrench3D * Gravity32 = sys.Gravity_Wrench("BAR32");
	Wrench3D * Gravity33 = sys.Gravity_Wrench("BAR33");
	Wrench3D * Gravity34 = sys.Gravity_Wrench("BAR34");
	Wrench3D * Gravity35 = sys.Gravity_Wrench("BAR35");
	Wrench3D * Gravity36 = sys.Gravity_Wrench("BAR36");
	Wrench3D * Gravity37 = sys.Gravity_Wrench("BAR37");
	Wrench3D * Gravity38 = sys.Gravity_Wrench("BAR38");
	Wrench3D * Gravity39 = sys.Gravity_Wrench("BAR39");
	Wrench3D * Gravity40 = sys.Gravity_Wrench("BAR40");
	Wrench3D * Gravity41 = sys.Gravity_Wrench("BAR41");
	Wrench3D * Gravity42 = sys.Gravity_Wrench("BAR42");
	Wrench3D * Gravity43 = sys.Gravity_Wrench("BAR43");
	Wrench3D * Gravity44 = sys.Gravity_Wrench("BAR44");
	Wrench3D * Gravity45 = sys.Gravity_Wrench("BAR45");
	Wrench3D * Gravity46 = sys.Gravity_Wrench("BAR46");
	Wrench3D * Gravity47 = sys.Gravity_Wrench("BAR47");
	Wrench3D * Gravity48 = sys.Gravity_Wrench("BAR48");
	Wrench3D * Gravity49 = sys.Gravity_Wrench("BAR49");
	Wrench3D * Gravity50 = sys.Gravity_Wrench("BAR50");
	Wrench3D * Gravity51 = sys.Gravity_Wrench("BAR51");
	Wrench3D * Gravity52 = sys.Gravity_Wrench("BAR52");
	Wrench3D * Gravity53 = sys.Gravity_Wrench("BAR53");
	Wrench3D * Gravity54 = sys.Gravity_Wrench("BAR54");
	Wrench3D * Gravity55 = sys.Gravity_Wrench("BAR55");
	Wrench3D * Gravity56 = sys.Gravity_Wrench("BAR56");
	Wrench3D * Gravity57 = sys.Gravity_Wrench("BAR57");
	Wrench3D * Gravity58 = sys.Gravity_Wrench("BAR58");
	Wrench3D * Gravity59 = sys.Gravity_Wrench("BAR59");
	Wrench3D * Gravity60 = sys.Gravity_Wrench("BAR60");
	Wrench3D * Gravity61 = sys.Gravity_Wrench("BAR61");
	Wrench3D * Gravity62 = sys.Gravity_Wrench("BAR62");
	Wrench3D * Gravity63 = sys.Gravity_Wrench("BAR63");
	Wrench3D * Gravity64 = sys.Gravity_Wrench("BAR64");
	Wrench3D * Gravity65 = sys.Gravity_Wrench("BAR65");
	Wrench3D * Gravity66 = sys.Gravity_Wrench("BAR66");
	Wrench3D * Gravity67 = sys.Gravity_Wrench("BAR67");
	Wrench3D * Gravity68 = sys.Gravity_Wrench("BAR68");
	Wrench3D * Gravity69 = sys.Gravity_Wrench("BAR69");
	Wrench3D * Gravity70 = sys.Gravity_Wrench("BAR70");
	Wrench3D * Gravity71 = sys.Gravity_Wrench("BAR71");
	Wrench3D * Gravity72 = sys.Gravity_Wrench("BAR72");
	Wrench3D * Gravity73 = sys.Gravity_Wrench("BAR73");
	Wrench3D * Gravity74 = sys.Gravity_Wrench("BAR74");
	Wrench3D * Gravity75 = sys.Gravity_Wrench("BAR75");
	Wrench3D * Gravity76 = sys.Gravity_Wrench("BAR76");
	Wrench3D * Gravity77 = sys.Gravity_Wrench("BAR77");
	Wrench3D * Gravity78 = sys.Gravity_Wrench("BAR78");
	Wrench3D * Gravity79 = sys.Gravity_Wrench("BAR79");
	Wrench3D * Gravity80 = sys.Gravity_Wrench("BAR80");
	Wrench3D * Gravity81 = sys.Gravity_Wrench("BAR81");
	Wrench3D * Gravity82 = sys.Gravity_Wrench("BAR82");
	Wrench3D * Gravity83 = sys.Gravity_Wrench("BAR83");
	Wrench3D * Gravity84 = sys.Gravity_Wrench("BAR84");
	Wrench3D * Gravity85 = sys.Gravity_Wrench("BAR85");
	Wrench3D * Gravity86 = sys.Gravity_Wrench("BAR86");
	Wrench3D * Gravity87 = sys.Gravity_Wrench("BAR87");
	Wrench3D * Gravity88 = sys.Gravity_Wrench("BAR88");
	Wrench3D * Gravity89 = sys.Gravity_Wrench("BAR89");
	Wrench3D * Gravity90 = sys.Gravity_Wrench("BAR90");
	Wrench3D * Gravity91 = sys.Gravity_Wrench("BAR91");
	Wrench3D * Gravity92 = sys.Gravity_Wrench("BAR92");
	Wrench3D * Gravity93 = sys.Gravity_Wrench("BAR93");
	Wrench3D * Gravity94 = sys.Gravity_Wrench("BAR94");
	Wrench3D * Gravity95 = sys.Gravity_Wrench("BAR95");
	Wrench3D * Gravity96 = sys.Gravity_Wrench("BAR96");
	Wrench3D * Gravity97 = sys.Gravity_Wrench("BAR97");
	Wrench3D * Gravity98 = sys.Gravity_Wrench("BAR98");
	Wrench3D * Gravity99 = sys.Gravity_Wrench("BAR99");
	Wrench3D * Gravity100 = sys.Gravity_Wrench("BAR100");
// 
	//	Inertia
	Wrench3D * Inertia_1 = sys.Inertia_Wrench("BAR1");
	Wrench3D * Inertia_2 = sys.Inertia_Wrench("BAR2");
	Wrench3D * Inertia_3 = sys.Inertia_Wrench("BAR3");
	Wrench3D * Inertia_4 = sys.Inertia_Wrench("BAR4");
	Wrench3D * Inertia_5 = sys.Inertia_Wrench("BAR5");
	Wrench3D * Inertia_6 = sys.Inertia_Wrench("BAR6");
	Wrench3D * Inertia_7 = sys.Inertia_Wrench("BAR7");
	Wrench3D * Inertia_8 = sys.Inertia_Wrench("BAR8");
	Wrench3D * Inertia_9 = sys.Inertia_Wrench("BAR9");
	Wrench3D * Inertia_10 = sys.Inertia_Wrench("BAR10");
	Wrench3D * Inertia_11 = sys.Inertia_Wrench("BAR11");
	Wrench3D * Inertia_12 = sys.Inertia_Wrench("BAR12");
	Wrench3D * Inertia_13 = sys.Inertia_Wrench("BAR13");
	Wrench3D * Inertia_14 = sys.Inertia_Wrench("BAR14");
	Wrench3D * Inertia_15 = sys.Inertia_Wrench("BAR15");
	Wrench3D * Inertia_16 = sys.Inertia_Wrench("BAR16");
	Wrench3D * Inertia_17 = sys.Inertia_Wrench("BAR17");
	Wrench3D * Inertia_18 = sys.Inertia_Wrench("BAR18");
	Wrench3D * Inertia_19 = sys.Inertia_Wrench("BAR19");
	Wrench3D * Inertia_20 = sys.Inertia_Wrench("BAR20");
	Wrench3D * Inertia_21 = sys.Inertia_Wrench("BAR21");
	Wrench3D * Inertia_22 = sys.Inertia_Wrench("BAR22");
	Wrench3D * Inertia_23 = sys.Inertia_Wrench("BAR23");
	Wrench3D * Inertia_24 = sys.Inertia_Wrench("BAR24");
	Wrench3D * Inertia_25 = sys.Inertia_Wrench("BAR25");
	Wrench3D * Inertia_26 = sys.Inertia_Wrench("BAR26");
	Wrench3D * Inertia_27 = sys.Inertia_Wrench("BAR27");
	Wrench3D * Inertia_28 = sys.Inertia_Wrench("BAR28");
	Wrench3D * Inertia_29 = sys.Inertia_Wrench("BAR29");
	Wrench3D * Inertia_30 = sys.Inertia_Wrench("BAR30");
	Wrench3D * Inertia_31 = sys.Inertia_Wrench("BAR31");
	Wrench3D * Inertia_32 = sys.Inertia_Wrench("BAR32");
	Wrench3D * Inertia_33 = sys.Inertia_Wrench("BAR33");
	Wrench3D * Inertia_34 = sys.Inertia_Wrench("BAR34");
	Wrench3D * Inertia_35 = sys.Inertia_Wrench("BAR35");
	Wrench3D * Inertia_36 = sys.Inertia_Wrench("BAR36");
	Wrench3D * Inertia_37 = sys.Inertia_Wrench("BAR37");
	Wrench3D * Inertia_38 = sys.Inertia_Wrench("BAR38");
	Wrench3D * Inertia_39 = sys.Inertia_Wrench("BAR39");
	Wrench3D * Inertia_40 = sys.Inertia_Wrench("BAR40");
	Wrench3D * Inertia_41 = sys.Inertia_Wrench("BAR41");
	Wrench3D * Inertia_42 = sys.Inertia_Wrench("BAR42");
	Wrench3D * Inertia_43 = sys.Inertia_Wrench("BAR43");
	Wrench3D * Inertia_44 = sys.Inertia_Wrench("BAR44");
	Wrench3D * Inertia_45 = sys.Inertia_Wrench("BAR45");
	Wrench3D * Inertia_46 = sys.Inertia_Wrench("BAR46");
	Wrench3D * Inertia_47 = sys.Inertia_Wrench("BAR47");
	Wrench3D * Inertia_48 = sys.Inertia_Wrench("BAR48");
	Wrench3D * Inertia_49 = sys.Inertia_Wrench("BAR49");
	Wrench3D * Inertia_50 = sys.Inertia_Wrench("BAR50");
	Wrench3D * Inertia_51 = sys.Inertia_Wrench("BAR51");
	Wrench3D * Inertia_52 = sys.Inertia_Wrench("BAR52");
	Wrench3D * Inertia_53 = sys.Inertia_Wrench("BAR53");
	Wrench3D * Inertia_54 = sys.Inertia_Wrench("BAR54");
	Wrench3D * Inertia_55 = sys.Inertia_Wrench("BAR55");
	Wrench3D * Inertia_56 = sys.Inertia_Wrench("BAR56");
	Wrench3D * Inertia_57 = sys.Inertia_Wrench("BAR57");
	Wrench3D * Inertia_58 = sys.Inertia_Wrench("BAR58");
	Wrench3D * Inertia_59 = sys.Inertia_Wrench("BAR59");
	Wrench3D * Inertia_60 = sys.Inertia_Wrench("BAR60");
	Wrench3D * Inertia_61 = sys.Inertia_Wrench("BAR61");
	Wrench3D * Inertia_62 = sys.Inertia_Wrench("BAR62");
	Wrench3D * Inertia_63 = sys.Inertia_Wrench("BAR63");
	Wrench3D * Inertia_64 = sys.Inertia_Wrench("BAR64");
	Wrench3D * Inertia_65 = sys.Inertia_Wrench("BAR65");
	Wrench3D * Inertia_66 = sys.Inertia_Wrench("BAR66");
	Wrench3D * Inertia_67 = sys.Inertia_Wrench("BAR67");
	Wrench3D * Inertia_68 = sys.Inertia_Wrench("BAR68");
	Wrench3D * Inertia_69 = sys.Inertia_Wrench("BAR69");
	Wrench3D * Inertia_70 = sys.Inertia_Wrench("BAR70");
	Wrench3D * Inertia_71 = sys.Inertia_Wrench("BAR71");
	Wrench3D * Inertia_72 = sys.Inertia_Wrench("BAR72");
	Wrench3D * Inertia_73 = sys.Inertia_Wrench("BAR73");
	Wrench3D * Inertia_74 = sys.Inertia_Wrench("BAR74");
	Wrench3D * Inertia_75 = sys.Inertia_Wrench("BAR75");
	Wrench3D * Inertia_76 = sys.Inertia_Wrench("BAR76");
	Wrench3D * Inertia_77 = sys.Inertia_Wrench("BAR77");
	Wrench3D * Inertia_78 = sys.Inertia_Wrench("BAR78");
	Wrench3D * Inertia_79 = sys.Inertia_Wrench("BAR79");
	Wrench3D * Inertia_80 = sys.Inertia_Wrench("BAR80");
	Wrench3D * Inertia_81 = sys.Inertia_Wrench("BAR81");
	Wrench3D * Inertia_82 = sys.Inertia_Wrench("BAR82");
	Wrench3D * Inertia_83 = sys.Inertia_Wrench("BAR83");
	Wrench3D * Inertia_84 = sys.Inertia_Wrench("BAR84");
	Wrench3D * Inertia_85 = sys.Inertia_Wrench("BAR85");
	Wrench3D * Inertia_86 = sys.Inertia_Wrench("BAR86");
	Wrench3D * Inertia_87 = sys.Inertia_Wrench("BAR87");
	Wrench3D * Inertia_88 = sys.Inertia_Wrench("BAR88");
	Wrench3D * Inertia_89 = sys.Inertia_Wrench("BAR89");
	Wrench3D * Inertia_90 = sys.Inertia_Wrench("BAR90");
	Wrench3D * Inertia_91 = sys.Inertia_Wrench("BAR91");
	Wrench3D * Inertia_92 = sys.Inertia_Wrench("BAR92");
	Wrench3D * Inertia_93 = sys.Inertia_Wrench("BAR93");
	Wrench3D * Inertia_94 = sys.Inertia_Wrench("BAR94");
	Wrench3D * Inertia_95 = sys.Inertia_Wrench("BAR95");
	Wrench3D * Inertia_96 = sys.Inertia_Wrench("BAR96");
	Wrench3D * Inertia_97 = sys.Inertia_Wrench("BAR97");
	Wrench3D * Inertia_98 = sys.Inertia_Wrench("BAR98");
	Wrench3D * Inertia_99 = sys.Inertia_Wrench("BAR99");
	Wrench3D * Inertia_100 = sys.Inertia_Wrench("BAR100");
	
	//	External Moments
	Wrench3D * WExternalAction1 = sys.new_Wrench3D ( "WExternalAction1", F1, M1, P1 , BAR1 , "Constitutive");
	Wrench3D * WExternalAction2 = sys.new_Wrench3D ( "WExternalAction2", F2, M2, P2 , BAR2 , "Constitutive");
	Wrench3D * WExternalAction3 = sys.new_Wrench3D ( "WExternalAction3", F3, M3, P3 , BAR3 , "Constitutive");
	Wrench3D * WExternalAction4 = sys.new_Wrench3D ( "WExternalAction4", F4, M4, P4 , BAR4 , "Constitutive");
	Wrench3D * WExternalAction5 = sys.new_Wrench3D ( "WExternalAction5", F5, M5, P5 , BAR5 , "Constitutive");
	Wrench3D * WExternalAction6 = sys.new_Wrench3D ( "WExternalAction6", F6, M6, P6 , BAR6 , "Constitutive");
	Wrench3D * WExternalAction7 = sys.new_Wrench3D ( "WExternalAction7", F7, M7, P7 , BAR7 , "Constitutive");
	Wrench3D * WExternalAction8 = sys.new_Wrench3D ( "WExternalAction8", F8, M8, P8 , BAR8 , "Constitutive");
	Wrench3D * WExternalAction9 = sys.new_Wrench3D ( "WExternalAction9", F9, M9, P9 , BAR9 , "Constitutive");
	Wrench3D * WExternalAction10 = sys.new_Wrench3D ( "WExternalAction10", F10, M10, P10 , BAR10 , "Constitutive");
	Wrench3D * WExternalAction11 = sys.new_Wrench3D ( "WExternalAction11", F11, M11, P11 , BAR11 , "Constitutive");
	Wrench3D * WExternalAction12 = sys.new_Wrench3D ( "WExternalAction12", F12, M12, P12 , BAR12 , "Constitutive");
	Wrench3D * WExternalAction13 = sys.new_Wrench3D ( "WExternalAction13", F13, M13, P13 , BAR13 , "Constitutive");
	Wrench3D * WExternalAction14 = sys.new_Wrench3D ( "WExternalAction14", F14, M14, P14 , BAR14 , "Constitutive");
	Wrench3D * WExternalAction15 = sys.new_Wrench3D ( "WExternalAction15", F15, M15, P15 , BAR15 , "Constitutive");
	Wrench3D * WExternalAction16 = sys.new_Wrench3D ( "WExternalAction16", F16, M16, P16 , BAR16 , "Constitutive");
	Wrench3D * WExternalAction17 = sys.new_Wrench3D ( "WExternalAction17", F17, M17, P17 , BAR17 , "Constitutive");
	Wrench3D * WExternalAction18 = sys.new_Wrench3D ( "WExternalAction18", F18, M18, P18 , BAR18 , "Constitutive");
	Wrench3D * WExternalAction19 = sys.new_Wrench3D ( "WExternalAction19", F19, M19, P19 , BAR19 , "Constitutive");
	Wrench3D * WExternalAction20 = sys.new_Wrench3D ( "WExternalAction20", F20, M20, P20 , BAR20 , "Constitutive");
	Wrench3D * WExternalAction21 = sys.new_Wrench3D ( "WExternalAction21", F21, M21, P21 , BAR21 , "Constitutive");
	Wrench3D * WExternalAction22 = sys.new_Wrench3D ( "WExternalAction22", F22, M22, P22 , BAR22 , "Constitutive");
	Wrench3D * WExternalAction23 = sys.new_Wrench3D ( "WExternalAction23", F23, M23, P23 , BAR23 , "Constitutive");
	Wrench3D * WExternalAction24 = sys.new_Wrench3D ( "WExternalAction24", F24, M24, P24 , BAR24 , "Constitutive");
	Wrench3D * WExternalAction25 = sys.new_Wrench3D ( "WExternalAction25", F25, M25, P25 , BAR25 , "Constitutive");
	Wrench3D * WExternalAction26 = sys.new_Wrench3D ( "WExternalAction26", F26, M26, P26 , BAR26 , "Constitutive");
	Wrench3D * WExternalAction27 = sys.new_Wrench3D ( "WExternalAction27", F27, M27, P27 , BAR27 , "Constitutive");
	Wrench3D * WExternalAction28 = sys.new_Wrench3D ( "WExternalAction28", F28, M28, P28 , BAR28 , "Constitutive");
	Wrench3D * WExternalAction29 = sys.new_Wrench3D ( "WExternalAction29", F29, M29, P29 , BAR29 , "Constitutive");
	Wrench3D * WExternalAction30 = sys.new_Wrench3D ( "WExternalAction30", F30, M30, P30 , BAR30 , "Constitutive");
	Wrench3D * WExternalAction31 = sys.new_Wrench3D ( "WExternalAction31", F31, M31, P31 , BAR31 , "Constitutive");
	Wrench3D * WExternalAction32 = sys.new_Wrench3D ( "WExternalAction32", F32, M32, P32 , BAR32 , "Constitutive");
	Wrench3D * WExternalAction33 = sys.new_Wrench3D ( "WExternalAction33", F33, M33, P33 , BAR33 , "Constitutive");
	Wrench3D * WExternalAction34 = sys.new_Wrench3D ( "WExternalAction34", F34, M34, P34 , BAR34 , "Constitutive");
	Wrench3D * WExternalAction35 = sys.new_Wrench3D ( "WExternalAction35", F35, M35, P35 , BAR35 , "Constitutive");
	Wrench3D * WExternalAction36 = sys.new_Wrench3D ( "WExternalAction36", F36, M36, P36 , BAR36 , "Constitutive");
	Wrench3D * WExternalAction37 = sys.new_Wrench3D ( "WExternalAction37", F37, M37, P37 , BAR37 , "Constitutive");
	Wrench3D * WExternalAction38 = sys.new_Wrench3D ( "WExternalAction38", F38, M38, P38 , BAR38 , "Constitutive");
	Wrench3D * WExternalAction39 = sys.new_Wrench3D ( "WExternalAction39", F39, M39, P39 , BAR39 , "Constitutive");
	Wrench3D * WExternalAction40 = sys.new_Wrench3D ( "WExternalAction40", F40, M40, P40 , BAR40 , "Constitutive");
	Wrench3D * WExternalAction41 = sys.new_Wrench3D ( "WExternalAction41", F41, M41, P41 , BAR41 , "Constitutive");
	Wrench3D * WExternalAction42 = sys.new_Wrench3D ( "WExternalAction42", F42, M42, P42 , BAR42 , "Constitutive");
	Wrench3D * WExternalAction43 = sys.new_Wrench3D ( "WExternalAction43", F43, M43, P43 , BAR43 , "Constitutive");
	Wrench3D * WExternalAction44 = sys.new_Wrench3D ( "WExternalAction44", F44, M44, P44 , BAR44 , "Constitutive");
	Wrench3D * WExternalAction45 = sys.new_Wrench3D ( "WExternalAction45", F45, M45, P45 , BAR45 , "Constitutive");
	Wrench3D * WExternalAction46 = sys.new_Wrench3D ( "WExternalAction46", F46, M46, P46 , BAR46 , "Constitutive");
	Wrench3D * WExternalAction47 = sys.new_Wrench3D ( "WExternalAction47", F47, M47, P47 , BAR47 , "Constitutive");
	Wrench3D * WExternalAction48 = sys.new_Wrench3D ( "WExternalAction48", F48, M48, P48 , BAR48 , "Constitutive");
	Wrench3D * WExternalAction49 = sys.new_Wrench3D ( "WExternalAction49", F49, M49, P49 , BAR49 , "Constitutive");
	Wrench3D * WExternalAction50 = sys.new_Wrench3D ( "WExternalAction50", F50, M50, P50 , BAR50 , "Constitutive");
	Wrench3D * WExternalAction51 = sys.new_Wrench3D ( "WExternalAction51", F51, M51, P51 , BAR51 , "Constitutive");
	Wrench3D * WExternalAction52 = sys.new_Wrench3D ( "WExternalAction52", F52, M52, P52 , BAR52 , "Constitutive");
	Wrench3D * WExternalAction53 = sys.new_Wrench3D ( "WExternalAction53", F53, M53, P53 , BAR53 , "Constitutive");
	Wrench3D * WExternalAction54 = sys.new_Wrench3D ( "WExternalAction54", F54, M54, P54 , BAR54 , "Constitutive");
	Wrench3D * WExternalAction55 = sys.new_Wrench3D ( "WExternalAction55", F55, M55, P55 , BAR55 , "Constitutive");
	Wrench3D * WExternalAction56 = sys.new_Wrench3D ( "WExternalAction56", F56, M56, P56 , BAR56 , "Constitutive");
	Wrench3D * WExternalAction57 = sys.new_Wrench3D ( "WExternalAction57", F57, M57, P57 , BAR57 , "Constitutive");
	Wrench3D * WExternalAction58 = sys.new_Wrench3D ( "WExternalAction58", F58, M58, P58 , BAR58 , "Constitutive");
	Wrench3D * WExternalAction59 = sys.new_Wrench3D ( "WExternalAction59", F59, M59, P59 , BAR59 , "Constitutive");
	Wrench3D * WExternalAction60 = sys.new_Wrench3D ( "WExternalAction60", F60, M60, P60 , BAR60 , "Constitutive");
	Wrench3D * WExternalAction61 = sys.new_Wrench3D ( "WExternalAction61", F61, M61, P61 , BAR61 , "Constitutive");
	Wrench3D * WExternalAction62 = sys.new_Wrench3D ( "WExternalAction62", F62, M62, P62 , BAR62 , "Constitutive");
	Wrench3D * WExternalAction63 = sys.new_Wrench3D ( "WExternalAction63", F63, M63, P63 , BAR63 , "Constitutive");
	Wrench3D * WExternalAction64 = sys.new_Wrench3D ( "WExternalAction64", F64, M64, P64 , BAR64 , "Constitutive");
	Wrench3D * WExternalAction65 = sys.new_Wrench3D ( "WExternalAction65", F65, M65, P65 , BAR65 , "Constitutive");
	Wrench3D * WExternalAction66 = sys.new_Wrench3D ( "WExternalAction66", F66, M66, P66 , BAR66 , "Constitutive");
	Wrench3D * WExternalAction67 = sys.new_Wrench3D ( "WExternalAction67", F67, M67, P67 , BAR67 , "Constitutive");
	Wrench3D * WExternalAction68 = sys.new_Wrench3D ( "WExternalAction68", F68, M68, P68 , BAR68 , "Constitutive");
	Wrench3D * WExternalAction69 = sys.new_Wrench3D ( "WExternalAction69", F69, M69, P69 , BAR69 , "Constitutive");
	Wrench3D * WExternalAction70 = sys.new_Wrench3D ( "WExternalAction70", F70, M70, P70 , BAR70 , "Constitutive");
	Wrench3D * WExternalAction71 = sys.new_Wrench3D ( "WExternalAction71", F71, M71, P71 , BAR71 , "Constitutive");
	Wrench3D * WExternalAction72 = sys.new_Wrench3D ( "WExternalAction72", F72, M72, P72 , BAR72 , "Constitutive");
	Wrench3D * WExternalAction73 = sys.new_Wrench3D ( "WExternalAction73", F73, M73, P73 , BAR73 , "Constitutive");
	Wrench3D * WExternalAction74 = sys.new_Wrench3D ( "WExternalAction74", F74, M74, P74 , BAR74 , "Constitutive");
	Wrench3D * WExternalAction75 = sys.new_Wrench3D ( "WExternalAction75", F75, M75, P75 , BAR75 , "Constitutive");
	Wrench3D * WExternalAction76 = sys.new_Wrench3D ( "WExternalAction76", F76, M76, P76 , BAR76 , "Constitutive");
	Wrench3D * WExternalAction77 = sys.new_Wrench3D ( "WExternalAction77", F77, M77, P77 , BAR77 , "Constitutive");
	Wrench3D * WExternalAction78 = sys.new_Wrench3D ( "WExternalAction78", F78, M78, P78 , BAR78 , "Constitutive");
	Wrench3D * WExternalAction79 = sys.new_Wrench3D ( "WExternalAction79", F79, M79, P79 , BAR79 , "Constitutive");
	Wrench3D * WExternalAction80 = sys.new_Wrench3D ( "WExternalAction80", F80, M80, P80 , BAR80 , "Constitutive");
	Wrench3D * WExternalAction81 = sys.new_Wrench3D ( "WExternalAction81", F81, M81, P81 , BAR81 , "Constitutive");
	Wrench3D * WExternalAction82 = sys.new_Wrench3D ( "WExternalAction82", F82, M82, P82 , BAR82 , "Constitutive");
	Wrench3D * WExternalAction83 = sys.new_Wrench3D ( "WExternalAction83", F83, M83, P83 , BAR83 , "Constitutive");
	Wrench3D * WExternalAction84 = sys.new_Wrench3D ( "WExternalAction84", F84, M84, P84 , BAR84 , "Constitutive");
	Wrench3D * WExternalAction85 = sys.new_Wrench3D ( "WExternalAction85", F85, M85, P85 , BAR85 , "Constitutive");
	Wrench3D * WExternalAction86 = sys.new_Wrench3D ( "WExternalAction86", F86, M86, P86 , BAR86 , "Constitutive");
	Wrench3D * WExternalAction87 = sys.new_Wrench3D ( "WExternalAction87", F87, M87, P87 , BAR87 , "Constitutive");
	Wrench3D * WExternalAction88 = sys.new_Wrench3D ( "WExternalAction88", F88, M88, P88 , BAR88 , "Constitutive");
	Wrench3D * WExternalAction89 = sys.new_Wrench3D ( "WExternalAction89", F89, M89, P89 , BAR89 , "Constitutive");
	Wrench3D * WExternalAction90 = sys.new_Wrench3D ( "WExternalAction90", F90, M90, P90 , BAR90 , "Constitutive");
	Wrench3D * WExternalAction91 = sys.new_Wrench3D ( "WExternalAction91", F91, M91, P91 , BAR91 , "Constitutive");
	Wrench3D * WExternalAction92 = sys.new_Wrench3D ( "WExternalAction92", F92, M92, P92 , BAR92 , "Constitutive");
	Wrench3D * WExternalAction93 = sys.new_Wrench3D ( "WExternalAction93", F93, M93, P93 , BAR93 , "Constitutive");
	Wrench3D * WExternalAction94 = sys.new_Wrench3D ( "WExternalAction94", F94, M94, P94 , BAR94 , "Constitutive");
	Wrench3D * WExternalAction95 = sys.new_Wrench3D ( "WExternalAction95", F95, M95, P95 , BAR95 , "Constitutive");
	Wrench3D * WExternalAction96 = sys.new_Wrench3D ( "WExternalAction96", F96, M96, P96 , BAR96 , "Constitutive");
	Wrench3D * WExternalAction97 = sys.new_Wrench3D ( "WExternalAction97", F97, M97, P97 , BAR97 , "Constitutive");
	Wrench3D * WExternalAction98 = sys.new_Wrench3D ( "WExternalAction98", F98, M98, P98 , BAR98 , "Constitutive");
	Wrench3D * WExternalAction99 = sys.new_Wrench3D ( "WExternalAction99", F99, M99, P99 , BAR99 , "Constitutive");
	Wrench3D * WExternalAction100 = sys.new_Wrench3D ( "WExternalAction100", F100, M100, P100 , BAR100 , "Constitutive");
	
//	Wrench3D * WExternalReaction2 = sys.new_Wrench3D ( "WExternalReaction2", -F2, -M2, P2 , BAR1 , "Constitutive") ;
//	Wrench3D * WExternalReaction3 = sys.new_Wrench3D ( "WExternalReaction3", -F3, -M3, P3 , BAR2 , "Constitutive") ;
//	Wrench3D * WExternalReaction4 = sys.new_Wrench3D ( "WExternalReaction4", -F4, -M4, P4 , BAR3 , "Constitutive") ;
//	Wrench3D * WExternalReaction5 = sys.new_Wrench3D ( "WExternalReaction5", -F5, -M5, P5 , BAR4 , "Constitutive") ;
//	Wrench3D * WExternalReaction6 = sys.new_Wrench3D ( "WExternalReaction6", -F6, -M6, P6 , BAR5 , "Constitutive") ;
//	Wrench3D * WExternalReaction7 = sys.new_Wrench3D ( "WExternalReaction7", -F7, -M7, P7 , BAR6 , "Constitutive") ;
//	Wrench3D * WExternalReaction8 = sys.new_Wrench3D ( "WExternalReaction8", -F8, -M8, P8 , BAR7 , "Constitutive") ;
//	Wrench3D * WExternalReaction9 = sys.new_Wrench3D ( "WExternalReaction9", -F9, -M9, P9 , BAR8 , "Constitutive") ;
//	Wrench3D * WExternalReaction10 = sys.new_Wrench3D ( "WExternalReaction10", -F10, -M10, P10 , BAR9 , "Constitutive") ;
//	Wrench3D * WExternalReaction11 = sys.new_Wrench3D ( "WExternalReaction11", -F11, -M11, P11 , BAR10 , "Constitutive") ;
//	Wrench3D * WExternalReaction12 = sys.new_Wrench3D ( "WExternalReaction12", -F12, -M12, P12 , BAR11 , "Constitutive") ;
//	Wrench3D * WExternalReaction13 = sys.new_Wrench3D ( "WExternalReaction13", -F13, -M13, P13 , BAR12 , "Constitutive") ;
//	Wrench3D * WExternalReaction14 = sys.new_Wrench3D ( "WExternalReaction14", -F14, -M14, P14 , BAR13 , "Constitutive") ;
//	Wrench3D * WExternalReaction15 = sys.new_Wrench3D ( "WExternalReaction15", -F15, -M15, P15 , BAR14 , "Constitutive") ;
//	Wrench3D * WExternalReaction16 = sys.new_Wrench3D ( "WExternalReaction16", -F16, -M16, P16 , BAR15 , "Constitutive") ;
//	Wrench3D * WExternalReaction17 = sys.new_Wrench3D ( "WExternalReaction17", -F17, -M17, P17 , BAR16 , "Constitutive") ;
//	Wrench3D * WExternalReaction18 = sys.new_Wrench3D ( "WExternalReaction18", -F18, -M18, P18 , BAR17 , "Constitutive") ;
//	Wrench3D * WExternalReaction19 = sys.new_Wrench3D ( "WExternalReaction19", -F19, -M19, P19 , BAR18 , "Constitutive") ;
//	Wrench3D * WExternalReaction20 = sys.new_Wrench3D ( "WExternalReaction20", -F20, -M20, P20 , BAR19 , "Constitutive") ;
//	Wrench3D * WExternalReaction21 = sys.new_Wrench3D ( "WExternalReaction21", -F21, -M21, P21 , BAR20 , "Constitutive") ;
//	Wrench3D * WExternalReaction22 = sys.new_Wrench3D ( "WExternalReaction22", -F22, -M22, P22 , BAR21 , "Constitutive") ;
//	Wrench3D * WExternalReaction23 = sys.new_Wrench3D ( "WExternalReaction23", -F23, -M23, P23 , BAR22 , "Constitutive") ;
//	Wrench3D * WExternalReaction24 = sys.new_Wrench3D ( "WExternalReaction24", -F24, -M24, P24 , BAR23 , "Constitutive") ;
//	Wrench3D * WExternalReaction25 = sys.new_Wrench3D ( "WExternalReaction25", -F25, -M25, P25 , BAR24 , "Constitutive") ;
//	Wrench3D * WExternalReaction26 = sys.new_Wrench3D ( "WExternalReaction26", -F26, -M26, P26 , BAR25 , "Constitutive") ;
//	Wrench3D * WExternalReaction27 = sys.new_Wrench3D ( "WExternalReaction27", -F27, -M27, P27 , BAR26 , "Constitutive") ;
//	Wrench3D * WExternalReaction28 = sys.new_Wrench3D ( "WExternalReaction28", -F28, -M28, P28 , BAR27 , "Constitutive") ;
//	Wrench3D * WExternalReaction29 = sys.new_Wrench3D ( "WExternalReaction29", -F29, -M29, P29 , BAR28 , "Constitutive") ;
//	Wrench3D * WExternalReaction30 = sys.new_Wrench3D ( "WExternalReaction30", -F30, -M30, P30 , BAR29 , "Constitutive") ;
//	Wrench3D * WExternalReaction31 = sys.new_Wrench3D ( "WExternalReaction31", -F31, -M31, P31 , BAR30 , "Constitutive") ;
//	Wrench3D * WExternalReaction32 = sys.new_Wrench3D ( "WExternalReaction32", -F32, -M32, P32 , BAR31 , "Constitutive") ;
//	Wrench3D * WExternalReaction33 = sys.new_Wrench3D ( "WExternalReaction33", -F33, -M33, P33 , BAR32 , "Constitutive") ;
//	Wrench3D * WExternalReaction34 = sys.new_Wrench3D ( "WExternalReaction34", -F34, -M34, P34 , BAR33 , "Constitutive") ;
//	Wrench3D * WExternalReaction35 = sys.new_Wrench3D ( "WExternalReaction35", -F35, -M35, P35 , BAR34 , "Constitutive") ;
//	Wrench3D * WExternalReaction36 = sys.new_Wrench3D ( "WExternalReaction36", -F36, -M36, P36 , BAR35 , "Constitutive") ;
//	Wrench3D * WExternalReaction37 = sys.new_Wrench3D ( "WExternalReaction37", -F37, -M37, P37 , BAR36 , "Constitutive") ;
//	Wrench3D * WExternalReaction38 = sys.new_Wrench3D ( "WExternalReaction38", -F38, -M38, P38 , BAR37 , "Constitutive") ;
//	Wrench3D * WExternalReaction39 = sys.new_Wrench3D ( "WExternalReaction39", -F39, -M39, P39 , BAR38 , "Constitutive") ;
//	Wrench3D * WExternalReaction40 = sys.new_Wrench3D ( "WExternalReaction40", -F40, -M40, P40 , BAR39 , "Constitutive") ;
//	Wrench3D * WExternalReaction41 = sys.new_Wrench3D ( "WExternalReaction41", -F41, -M41, P41 , BAR40 , "Constitutive") ;
//	Wrench3D * WExternalReaction42 = sys.new_Wrench3D ( "WExternalReaction42", -F42, -M42, P42 , BAR41 , "Constitutive") ;
//	Wrench3D * WExternalReaction43 = sys.new_Wrench3D ( "WExternalReaction43", -F43, -M43, P43 , BAR42 , "Constitutive") ;
//	Wrench3D * WExternalReaction44 = sys.new_Wrench3D ( "WExternalReaction44", -F44, -M44, P44 , BAR43 , "Constitutive") ;
//	Wrench3D * WExternalReaction45 = sys.new_Wrench3D ( "WExternalReaction45", -F45, -M45, P45 , BAR44 , "Constitutive") ;
//	Wrench3D * WExternalReaction46 = sys.new_Wrench3D ( "WExternalReaction46", -F46, -M46, P46 , BAR45 , "Constitutive") ;
//	Wrench3D * WExternalReaction47 = sys.new_Wrench3D ( "WExternalReaction47", -F47, -M47, P47 , BAR46 , "Constitutive") ;
//	Wrench3D * WExternalReaction48 = sys.new_Wrench3D ( "WExternalReaction48", -F48, -M48, P48 , BAR47 , "Constitutive") ;
//	Wrench3D * WExternalReaction49 = sys.new_Wrench3D ( "WExternalReaction49", -F49, -M49, P49 , BAR48 , "Constitutive") ;
//	Wrench3D * WExternalReaction50 = sys.new_Wrench3D ( "WExternalReaction50", -F50, -M50, P50 , BAR49 , "Constitutive") ;
//	Wrench3D * WExternalReaction51 = sys.new_Wrench3D ( "WExternalReaction51", -F51, -M51, P51 , BAR50 , "Constitutive") ;
//	Wrench3D * WExternalReaction52 = sys.new_Wrench3D ( "WExternalReaction52", -F52, -M52, P52 , BAR51 , "Constitutive") ;
//	Wrench3D * WExternalReaction53 = sys.new_Wrench3D ( "WExternalReaction53", -F53, -M53, P53 , BAR52 , "Constitutive") ;
//	Wrench3D * WExternalReaction54 = sys.new_Wrench3D ( "WExternalReaction54", -F54, -M54, P54 , BAR53 , "Constitutive") ;
//	Wrench3D * WExternalReaction55 = sys.new_Wrench3D ( "WExternalReaction55", -F55, -M55, P55 , BAR54 , "Constitutive") ;
//	Wrench3D * WExternalReaction56 = sys.new_Wrench3D ( "WExternalReaction56", -F56, -M56, P56 , BAR55 , "Constitutive") ;
//	Wrench3D * WExternalReaction57 = sys.new_Wrench3D ( "WExternalReaction57", -F57, -M57, P57 , BAR56 , "Constitutive") ;
//	Wrench3D * WExternalReaction58 = sys.new_Wrench3D ( "WExternalReaction58", -F58, -M58, P58 , BAR57 , "Constitutive") ;
//	Wrench3D * WExternalReaction59 = sys.new_Wrench3D ( "WExternalReaction59", -F59, -M59, P59 , BAR58 , "Constitutive") ;
//	Wrench3D * WExternalReaction60 = sys.new_Wrench3D ( "WExternalReaction60", -F60, -M60, P60 , BAR59 , "Constitutive") ;
//	Wrench3D * WExternalReaction61 = sys.new_Wrench3D ( "WExternalReaction61", -F61, -M61, P61 , BAR60 , "Constitutive") ;
//	Wrench3D * WExternalReaction62 = sys.new_Wrench3D ( "WExternalReaction62", -F62, -M62, P62 , BAR61 , "Constitutive") ;
//	Wrench3D * WExternalReaction63 = sys.new_Wrench3D ( "WExternalReaction63", -F63, -M63, P63 , BAR62 , "Constitutive") ;
//	Wrench3D * WExternalReaction64 = sys.new_Wrench3D ( "WExternalReaction64", -F64, -M64, P64 , BAR63 , "Constitutive") ;
//	Wrench3D * WExternalReaction65 = sys.new_Wrench3D ( "WExternalReaction65", -F65, -M65, P65 , BAR64 , "Constitutive") ;
//	Wrench3D * WExternalReaction66 = sys.new_Wrench3D ( "WExternalReaction66", -F66, -M66, P66 , BAR65 , "Constitutive") ;
//	Wrench3D * WExternalReaction67 = sys.new_Wrench3D ( "WExternalReaction67", -F67, -M67, P67 , BAR66 , "Constitutive") ;
//	Wrench3D * WExternalReaction68 = sys.new_Wrench3D ( "WExternalReaction68", -F68, -M68, P68 , BAR67 , "Constitutive") ;
//	Wrench3D * WExternalReaction69 = sys.new_Wrench3D ( "WExternalReaction69", -F69, -M69, P69 , BAR68 , "Constitutive") ;
//	Wrench3D * WExternalReaction70 = sys.new_Wrench3D ( "WExternalReaction70", -F70, -M70, P70 , BAR69 , "Constitutive") ;
//	Wrench3D * WExternalReaction71 = sys.new_Wrench3D ( "WExternalReaction71", -F71, -M71, P71 , BAR70 , "Constitutive") ;
//	Wrench3D * WExternalReaction72 = sys.new_Wrench3D ( "WExternalReaction72", -F72, -M72, P72 , BAR71 , "Constitutive") ;
//	Wrench3D * WExternalReaction73 = sys.new_Wrench3D ( "WExternalReaction73", -F73, -M73, P73 , BAR72 , "Constitutive") ;
//	Wrench3D * WExternalReaction74 = sys.new_Wrench3D ( "WExternalReaction74", -F74, -M74, P74 , BAR73 , "Constitutive") ;
//	Wrench3D * WExternalReaction75 = sys.new_Wrench3D ( "WExternalReaction75", -F75, -M75, P75 , BAR74 , "Constitutive") ;
//	Wrench3D * WExternalReaction76 = sys.new_Wrench3D ( "WExternalReaction76", -F76, -M76, P76 , BAR75 , "Constitutive") ;
//	Wrench3D * WExternalReaction77 = sys.new_Wrench3D ( "WExternalReaction77", -F77, -M77, P77 , BAR76 , "Constitutive") ;
//	Wrench3D * WExternalReaction78 = sys.new_Wrench3D ( "WExternalReaction78", -F78, -M78, P78 , BAR77 , "Constitutive") ;
//	Wrench3D * WExternalReaction79 = sys.new_Wrench3D ( "WExternalReaction79", -F79, -M79, P79 , BAR78 , "Constitutive") ;
//	Wrench3D * WExternalReaction80 = sys.new_Wrench3D ( "WExternalReaction80", -F80, -M80, P80 , BAR79 , "Constitutive") ;
//	Wrench3D * WExternalReaction81 = sys.new_Wrench3D ( "WExternalReaction81", -F81, -M81, P81 , BAR80 , "Constitutive") ;
//	Wrench3D * WExternalReaction82 = sys.new_Wrench3D ( "WExternalReaction82", -F82, -M82, P82 , BAR81 , "Constitutive") ;
//	Wrench3D * WExternalReaction83 = sys.new_Wrench3D ( "WExternalReaction83", -F83, -M83, P83 , BAR82 , "Constitutive") ;
//	Wrench3D * WExternalReaction84 = sys.new_Wrench3D ( "WExternalReaction84", -F84, -M84, P84 , BAR83 , "Constitutive") ;
//	Wrench3D * WExternalReaction85 = sys.new_Wrench3D ( "WExternalReaction85", -F85, -M85, P85 , BAR84 , "Constitutive") ;
//	Wrench3D * WExternalReaction86 = sys.new_Wrench3D ( "WExternalReaction86", -F86, -M86, P86 , BAR85 , "Constitutive") ;
//	Wrench3D * WExternalReaction87 = sys.new_Wrench3D ( "WExternalReaction87", -F87, -M87, P87 , BAR86 , "Constitutive") ;
//	Wrench3D * WExternalReaction88 = sys.new_Wrench3D ( "WExternalReaction88", -F88, -M88, P88 , BAR87 , "Constitutive") ;
//	Wrench3D * WExternalReaction89 = sys.new_Wrench3D ( "WExternalReaction89", -F89, -M89, P89 , BAR88 , "Constitutive") ;
//	Wrench3D * WExternalReaction90 = sys.new_Wrench3D ( "WExternalReaction90", -F90, -M90, P90 , BAR89 , "Constitutive") ;
//	Wrench3D * WExternalReaction91 = sys.new_Wrench3D ( "WExternalReaction91", -F91, -M91, P91 , BAR90 , "Constitutive") ;
//	Wrench3D * WExternalReaction92 = sys.new_Wrench3D ( "WExternalReaction92", -F92, -M92, P92 , BAR91 , "Constitutive") ;
//	Wrench3D * WExternalReaction93 = sys.new_Wrench3D ( "WExternalReaction93", -F93, -M93, P93 , BAR92 , "Constitutive") ;
//	Wrench3D * WExternalReaction94 = sys.new_Wrench3D ( "WExternalReaction94", -F94, -M94, P94 , BAR93 , "Constitutive") ;
//	Wrench3D * WExternalReaction95 = sys.new_Wrench3D ( "WExternalReaction95", -F95, -M95, P95 , BAR94 , "Constitutive") ;
//	Wrench3D * WExternalReaction96 = sys.new_Wrench3D ( "WExternalReaction96", -F96, -M96, P96 , BAR95 , "Constitutive") ;
//	Wrench3D * WExternalReaction97 = sys.new_Wrench3D ( "WExternalReaction97", -F97, -M97, P97 , BAR96 , "Constitutive") ;
//	Wrench3D * WExternalReaction98 = sys.new_Wrench3D ( "WExternalReaction98", -F98, -M98, P98 , BAR97 , "Constitutive") ;
//	Wrench3D * WExternalReaction99 = sys.new_Wrench3D ( "WExternalReaction99", -F99, -M99, P99 , BAR98 , "Constitutive") ;
//	Wrench3D * WExternalReaction100 = sys.new_Wrench3D ( "WExternalReaction100", -F100, -M100, P100 , BAR99 , "Constitutive") ;


	symbol_numeric lambda1  = *sys.new_Joint_Unknown("lambda1");


// ************************************************************************************************
// 	Vectors needed to take diferent Jacobians
// ************************************************************************************************

	cout << "Vectors needed to take diferent Jacobians" << endl;

	Matrix q = sys.Coordinates();
	Matrix dq = sys.Velocities();
	Matrix ddq = sys.Accelerations();
	Matrix pars = sys.Parameters();
// 	Matrix inps = sys.Inputs();
	Matrix unks = sys.Joint_Unknowns();

// ************************************************************************************************
// 	 Parameters for the Trajectory optimization 
// ************************************************************************************************
// // Constante term of the Fourier Series
 	symbol_numeric  FS001 = *sys.new_Parameter("FS001",0.0);
 	symbol_numeric  FS002 = *sys.new_Parameter("FS002",0.0);
 	symbol_numeric  FS003 = *sys.new_Parameter("FS003",0.0);
 	symbol_numeric  FS004 = *sys.new_Parameter("FS004",0.0);
 	symbol_numeric  FS005 = *sys.new_Parameter("FS005",0.0);
 	symbol_numeric  FS006 = *sys.new_Parameter("FS006",0.0);
 	symbol_numeric  FS007 = *sys.new_Parameter("FS007",0.0);
 	symbol_numeric  FS008 = *sys.new_Parameter("FS008",0.0);
 	symbol_numeric  FS009 = *sys.new_Parameter("FS009",0.0);
 	symbol_numeric  FS0010 = *sys.new_Parameter("FS0010",0.0);
 	symbol_numeric  FS0011 = *sys.new_Parameter("FS0011",0.0);
 	symbol_numeric  FS0012 = *sys.new_Parameter("FS0012",0.0);
 	symbol_numeric  FS0013 = *sys.new_Parameter("FS0013",0.0);
 	symbol_numeric  FS0014 = *sys.new_Parameter("FS0014",0.0);
 	symbol_numeric  FS0015 = *sys.new_Parameter("FS0015",0.0);
 	symbol_numeric  FS0016 = *sys.new_Parameter("FS0016",0.0);
 	symbol_numeric  FS0017 = *sys.new_Parameter("FS0017",0.0);
 	symbol_numeric  FS0018 = *sys.new_Parameter("FS0018",0.0);
 	symbol_numeric  FS0019 = *sys.new_Parameter("FS0019",0.0);
 	symbol_numeric  FS0020 = *sys.new_Parameter("FS0020",0.0);
 	symbol_numeric  FS0021 = *sys.new_Parameter("FS0021",0.0);
 	symbol_numeric  FS0022 = *sys.new_Parameter("FS0022",0.0);
 	symbol_numeric  FS0023 = *sys.new_Parameter("FS0023",0.0);
 	symbol_numeric  FS0024 = *sys.new_Parameter("FS0024",0.0);
 	symbol_numeric  FS0025 = *sys.new_Parameter("FS0025",0.0);
 	symbol_numeric  FS0026 = *sys.new_Parameter("FS0026",0.0);
 	symbol_numeric  FS0027 = *sys.new_Parameter("FS0027",0.0);
 	symbol_numeric  FS0028 = *sys.new_Parameter("FS0028",0.0);
 	symbol_numeric  FS0029 = *sys.new_Parameter("FS0029",0.0);
 	symbol_numeric  FS0030 = *sys.new_Parameter("FS0030",0.0);
 	symbol_numeric  FS0031 = *sys.new_Parameter("FS0031",0.0);
 	symbol_numeric  FS0032 = *sys.new_Parameter("FS0032",0.0);
 	symbol_numeric  FS0033 = *sys.new_Parameter("FS0033",0.0);
 	symbol_numeric  FS0034 = *sys.new_Parameter("FS0034",0.0);
 	symbol_numeric  FS0035 = *sys.new_Parameter("FS0035",0.0);
 	symbol_numeric  FS0036 = *sys.new_Parameter("FS0036",0.0);
 	symbol_numeric  FS0037 = *sys.new_Parameter("FS0037",0.0);
 	symbol_numeric  FS0038 = *sys.new_Parameter("FS0038",0.0);
 	symbol_numeric  FS0039 = *sys.new_Parameter("FS0039",0.0);
 	symbol_numeric  FS0040 = *sys.new_Parameter("FS0040",0.0);
 	symbol_numeric  FS0041 = *sys.new_Parameter("FS0041",0.0);
 	symbol_numeric  FS0042 = *sys.new_Parameter("FS0042",0.0);
 	symbol_numeric  FS0043 = *sys.new_Parameter("FS0043",0.0);
 	symbol_numeric  FS0044 = *sys.new_Parameter("FS0044",0.0);
 	symbol_numeric  FS0045 = *sys.new_Parameter("FS0045",0.0);
 	symbol_numeric  FS0046 = *sys.new_Parameter("FS0046",0.0);
 	symbol_numeric  FS0047 = *sys.new_Parameter("FS0047",0.0);
 	symbol_numeric  FS0048 = *sys.new_Parameter("FS0048",0.0);
 	symbol_numeric  FS0049 = *sys.new_Parameter("FS0049",0.0);
 	symbol_numeric  FS0050 = *sys.new_Parameter("FS0050",0.0);
 	symbol_numeric  FS0051 = *sys.new_Parameter("FS0051",0.0);
 	symbol_numeric  FS0052 = *sys.new_Parameter("FS0052",0.0);
 	symbol_numeric  FS0053 = *sys.new_Parameter("FS0053",0.0);
 	symbol_numeric  FS0054 = *sys.new_Parameter("FS0054",0.0);
 	symbol_numeric  FS0055 = *sys.new_Parameter("FS0055",0.0);
 	symbol_numeric  FS0056 = *sys.new_Parameter("FS0056",0.0);
 	symbol_numeric  FS0057 = *sys.new_Parameter("FS0057",0.0);
 	symbol_numeric  FS0058 = *sys.new_Parameter("FS0058",0.0);
 	symbol_numeric  FS0059 = *sys.new_Parameter("FS0059",0.0);
 	symbol_numeric  FS0060 = *sys.new_Parameter("FS0060",0.0);
 	symbol_numeric  FS0061 = *sys.new_Parameter("FS0061",0.0);
 	symbol_numeric  FS0062 = *sys.new_Parameter("FS0062",0.0);
 	symbol_numeric  FS0063 = *sys.new_Parameter("FS0063",0.0);
 	symbol_numeric  FS0064 = *sys.new_Parameter("FS0064",0.0);
 	symbol_numeric  FS0065 = *sys.new_Parameter("FS0065",0.0);
 	symbol_numeric  FS0066 = *sys.new_Parameter("FS0066",0.0);
 	symbol_numeric  FS0067 = *sys.new_Parameter("FS0067",0.0);
 	symbol_numeric  FS0068 = *sys.new_Parameter("FS0068",0.0);
 	symbol_numeric  FS0069 = *sys.new_Parameter("FS0069",0.0);
 	symbol_numeric  FS0070 = *sys.new_Parameter("FS0070",0.0);
 	symbol_numeric  FS0071 = *sys.new_Parameter("FS0071",0.0);
 	symbol_numeric  FS0072 = *sys.new_Parameter("FS0072",0.0);
 	symbol_numeric  FS0073 = *sys.new_Parameter("FS0073",0.0);
 	symbol_numeric  FS0074 = *sys.new_Parameter("FS0074",0.0);
 	symbol_numeric  FS0075 = *sys.new_Parameter("FS0075",0.0);
 	symbol_numeric  FS0076 = *sys.new_Parameter("FS0076",0.0);
 	symbol_numeric  FS0077 = *sys.new_Parameter("FS0077",0.0);
 	symbol_numeric  FS0078 = *sys.new_Parameter("FS0078",0.0);
 	symbol_numeric  FS0079 = *sys.new_Parameter("FS0079",0.0);
 	symbol_numeric  FS0080 = *sys.new_Parameter("FS0080",0.0);
 	symbol_numeric  FS0081 = *sys.new_Parameter("FS0081",0.0);
 	symbol_numeric  FS0082 = *sys.new_Parameter("FS0082",0.0);
 	symbol_numeric  FS0083 = *sys.new_Parameter("FS0083",0.0);
 	symbol_numeric  FS0084 = *sys.new_Parameter("FS0084",0.0);
 	symbol_numeric  FS0085 = *sys.new_Parameter("FS0085",0.0);
 	symbol_numeric  FS0086 = *sys.new_Parameter("FS0086",0.0);
 	symbol_numeric  FS0087 = *sys.new_Parameter("FS0087",0.0);
 	symbol_numeric  FS0088 = *sys.new_Parameter("FS0088",0.0);
 	symbol_numeric  FS0089 = *sys.new_Parameter("FS0089",0.0);
 	symbol_numeric  FS0090 = *sys.new_Parameter("FS0090",0.0);
 	symbol_numeric  FS0091 = *sys.new_Parameter("FS0091",0.0);
 	symbol_numeric  FS0092 = *sys.new_Parameter("FS0092",0.0);
 	symbol_numeric  FS0093 = *sys.new_Parameter("FS0093",0.0);
 	symbol_numeric  FS0094 = *sys.new_Parameter("FS0094",0.0);
 	symbol_numeric  FS0095 = *sys.new_Parameter("FS0095",0.0);
 	symbol_numeric  FS0096 = *sys.new_Parameter("FS0096",0.0);
 	symbol_numeric  FS0097 = *sys.new_Parameter("FS0097",0.0);
 	symbol_numeric  FS0098 = *sys.new_Parameter("FS0098",0.0);
 	symbol_numeric  FS0099 = *sys.new_Parameter("FS0099",0.0);
 	symbol_numeric  FS00100 = *sys.new_Parameter("FS00100",0.0);

// Harmonic number 1 of the Fourier Series	
 	symbol_numeric  FSa1_1 = *sys.new_Parameter("FSa1_1",0.0);
 	symbol_numeric  FSb1_1 = *sys.new_Parameter("FSb1_1",0.0);
 	symbol_numeric  FSa1_2 = *sys.new_Parameter("FSa1_2",0.0);
 	symbol_numeric  FSb1_2 = *sys.new_Parameter("FSb1_2",0.0);
 	symbol_numeric  FSa1_3 = *sys.new_Parameter("FSa1_3",0.0);
 	symbol_numeric  FSb1_3 = *sys.new_Parameter("FSb1_3",0.0);
 	symbol_numeric  FSa1_4 = *sys.new_Parameter("FSa1_4",0.0);
 	symbol_numeric  FSb1_4 = *sys.new_Parameter("FSb1_4",0.0);
 	symbol_numeric  FSa1_5 = *sys.new_Parameter("FSa1_5",0.0);
 	symbol_numeric  FSb1_5 = *sys.new_Parameter("FSb1_5",0.0);
 	symbol_numeric  FSa1_6 = *sys.new_Parameter("FSa1_6",0.0);
 	symbol_numeric  FSb1_6 = *sys.new_Parameter("FSb1_6",0.0);
 	symbol_numeric  FSa1_7 = *sys.new_Parameter("FSa1_7",0.0);
 	symbol_numeric  FSb1_7 = *sys.new_Parameter("FSb1_7",0.0);
 	symbol_numeric  FSa1_8 = *sys.new_Parameter("FSa1_8",0.0);
 	symbol_numeric  FSb1_8 = *sys.new_Parameter("FSb1_8",0.0);
 	symbol_numeric  FSa1_9 = *sys.new_Parameter("FSa1_9",0.0);
 	symbol_numeric  FSb1_9 = *sys.new_Parameter("FSb1_9",0.0);
 	symbol_numeric  FSa1_10 = *sys.new_Parameter("FSa1_10",0.0);
 	symbol_numeric  FSb1_10 = *sys.new_Parameter("FSb1_10",0.0);
 	symbol_numeric  FSa1_11 = *sys.new_Parameter("FSa1_11",0.0);
 	symbol_numeric  FSb1_11 = *sys.new_Parameter("FSb1_11",0.0);
 	symbol_numeric  FSa1_12 = *sys.new_Parameter("FSa1_12",0.0);
 	symbol_numeric  FSb1_12 = *sys.new_Parameter("FSb1_12",0.0);
 	symbol_numeric  FSa1_13 = *sys.new_Parameter("FSa1_13",0.0);
 	symbol_numeric  FSb1_13 = *sys.new_Parameter("FSb1_13",0.0);
 	symbol_numeric  FSa1_14 = *sys.new_Parameter("FSa1_14",0.0);
 	symbol_numeric  FSb1_14 = *sys.new_Parameter("FSb1_14",0.0);
 	symbol_numeric  FSa1_15 = *sys.new_Parameter("FSa1_15",0.0);
 	symbol_numeric  FSb1_15 = *sys.new_Parameter("FSb1_15",0.0);
 	symbol_numeric  FSa1_16 = *sys.new_Parameter("FSa1_16",0.0);
 	symbol_numeric  FSb1_16 = *sys.new_Parameter("FSb1_16",0.0);
 	symbol_numeric  FSa1_17 = *sys.new_Parameter("FSa1_17",0.0);
 	symbol_numeric  FSb1_17 = *sys.new_Parameter("FSb1_17",0.0);
 	symbol_numeric  FSa1_18 = *sys.new_Parameter("FSa1_18",0.0);
 	symbol_numeric  FSb1_18 = *sys.new_Parameter("FSb1_18",0.0);
 	symbol_numeric  FSa1_19 = *sys.new_Parameter("FSa1_19",0.0);
 	symbol_numeric  FSb1_19 = *sys.new_Parameter("FSb1_19",0.0);
 	symbol_numeric  FSa1_20 = *sys.new_Parameter("FSa1_20",0.0);
 	symbol_numeric  FSb1_20 = *sys.new_Parameter("FSb1_20",0.0);
 	symbol_numeric  FSa1_21 = *sys.new_Parameter("FSa1_21",0.0);
 	symbol_numeric  FSb1_21 = *sys.new_Parameter("FSb1_21",0.0);
 	symbol_numeric  FSa1_22 = *sys.new_Parameter("FSa1_22",0.0);
 	symbol_numeric  FSb1_22 = *sys.new_Parameter("FSb1_22",0.0);
 	symbol_numeric  FSa1_23 = *sys.new_Parameter("FSa1_23",0.0);
 	symbol_numeric  FSb1_23 = *sys.new_Parameter("FSb1_23",0.0);
 	symbol_numeric  FSa1_24 = *sys.new_Parameter("FSa1_24",0.0);
 	symbol_numeric  FSb1_24 = *sys.new_Parameter("FSb1_24",0.0);
 	symbol_numeric  FSa1_25 = *sys.new_Parameter("FSa1_25",0.0);
 	symbol_numeric  FSb1_25 = *sys.new_Parameter("FSb1_25",0.0);
 	symbol_numeric  FSa1_26 = *sys.new_Parameter("FSa1_26",0.0);
 	symbol_numeric  FSb1_26 = *sys.new_Parameter("FSb1_26",0.0);
 	symbol_numeric  FSa1_27 = *sys.new_Parameter("FSa1_27",0.0);
 	symbol_numeric  FSb1_27 = *sys.new_Parameter("FSb1_27",0.0);
 	symbol_numeric  FSa1_28 = *sys.new_Parameter("FSa1_28",0.0);
 	symbol_numeric  FSb1_28 = *sys.new_Parameter("FSb1_28",0.0);
 	symbol_numeric  FSa1_29 = *sys.new_Parameter("FSa1_29",0.0);
 	symbol_numeric  FSb1_29 = *sys.new_Parameter("FSb1_29",0.0);
 	symbol_numeric  FSa1_30 = *sys.new_Parameter("FSa1_30",0.0);
 	symbol_numeric  FSb1_30 = *sys.new_Parameter("FSb1_30",0.0);
 	symbol_numeric  FSa1_31 = *sys.new_Parameter("FSa1_31",0.0);
 	symbol_numeric  FSb1_31 = *sys.new_Parameter("FSb1_31",0.0);
 	symbol_numeric  FSa1_32 = *sys.new_Parameter("FSa1_32",0.0);
 	symbol_numeric  FSb1_32 = *sys.new_Parameter("FSb1_32",0.0);
 	symbol_numeric  FSa1_33 = *sys.new_Parameter("FSa1_33",0.0);
 	symbol_numeric  FSb1_33 = *sys.new_Parameter("FSb1_33",0.0);
 	symbol_numeric  FSa1_34 = *sys.new_Parameter("FSa1_34",0.0);
 	symbol_numeric  FSb1_34 = *sys.new_Parameter("FSb1_34",0.0);
 	symbol_numeric  FSa1_35 = *sys.new_Parameter("FSa1_35",0.0);
 	symbol_numeric  FSb1_35 = *sys.new_Parameter("FSb1_35",0.0);
 	symbol_numeric  FSa1_36 = *sys.new_Parameter("FSa1_36",0.0);
 	symbol_numeric  FSb1_36 = *sys.new_Parameter("FSb1_36",0.0);
 	symbol_numeric  FSa1_37 = *sys.new_Parameter("FSa1_37",0.0);
 	symbol_numeric  FSb1_37 = *sys.new_Parameter("FSb1_37",0.0);
 	symbol_numeric  FSa1_38 = *sys.new_Parameter("FSa1_38",0.0);
 	symbol_numeric  FSb1_38 = *sys.new_Parameter("FSb1_38",0.0);
 	symbol_numeric  FSa1_39 = *sys.new_Parameter("FSa1_39",0.0);
 	symbol_numeric  FSb1_39 = *sys.new_Parameter("FSb1_39",0.0);
 	symbol_numeric  FSa1_40 = *sys.new_Parameter("FSa1_40",0.0);
 	symbol_numeric  FSb1_40 = *sys.new_Parameter("FSb1_40",0.0);
 	symbol_numeric  FSa1_41 = *sys.new_Parameter("FSa1_41",0.0);
 	symbol_numeric  FSb1_41 = *sys.new_Parameter("FSb1_41",0.0);
 	symbol_numeric  FSa1_42 = *sys.new_Parameter("FSa1_42",0.0);
 	symbol_numeric  FSb1_42 = *sys.new_Parameter("FSb1_42",0.0);
 	symbol_numeric  FSa1_43 = *sys.new_Parameter("FSa1_43",0.0);
 	symbol_numeric  FSb1_43 = *sys.new_Parameter("FSb1_43",0.0);
 	symbol_numeric  FSa1_44 = *sys.new_Parameter("FSa1_44",0.0);
 	symbol_numeric  FSb1_44 = *sys.new_Parameter("FSb1_44",0.0);
 	symbol_numeric  FSa1_45 = *sys.new_Parameter("FSa1_45",0.0);
 	symbol_numeric  FSb1_45 = *sys.new_Parameter("FSb1_45",0.0);
 	symbol_numeric  FSa1_46 = *sys.new_Parameter("FSa1_46",0.0);
 	symbol_numeric  FSb1_46 = *sys.new_Parameter("FSb1_46",0.0);
 	symbol_numeric  FSa1_47 = *sys.new_Parameter("FSa1_47",0.0);
 	symbol_numeric  FSb1_47 = *sys.new_Parameter("FSb1_47",0.0);
 	symbol_numeric  FSa1_48 = *sys.new_Parameter("FSa1_48",0.0);
 	symbol_numeric  FSb1_48 = *sys.new_Parameter("FSb1_48",0.0);
 	symbol_numeric  FSa1_49 = *sys.new_Parameter("FSa1_49",0.0);
 	symbol_numeric  FSb1_49 = *sys.new_Parameter("FSb1_49",0.0);
 	symbol_numeric  FSa1_50 = *sys.new_Parameter("FSa1_50",0.0);
 	symbol_numeric  FSb1_50 = *sys.new_Parameter("FSb1_50",0.0);
 	symbol_numeric  FSa1_51 = *sys.new_Parameter("FSa1_51",0.0);
 	symbol_numeric  FSb1_51 = *sys.new_Parameter("FSb1_51",0.0);
 	symbol_numeric  FSa1_52 = *sys.new_Parameter("FSa1_52",0.0);
 	symbol_numeric  FSb1_52 = *sys.new_Parameter("FSb1_52",0.0);
 	symbol_numeric  FSa1_53 = *sys.new_Parameter("FSa1_53",0.0);
 	symbol_numeric  FSb1_53 = *sys.new_Parameter("FSb1_53",0.0);
 	symbol_numeric  FSa1_54 = *sys.new_Parameter("FSa1_54",0.0);
 	symbol_numeric  FSb1_54 = *sys.new_Parameter("FSb1_54",0.0);
 	symbol_numeric  FSa1_55 = *sys.new_Parameter("FSa1_55",0.0);
 	symbol_numeric  FSb1_55 = *sys.new_Parameter("FSb1_55",0.0);
 	symbol_numeric  FSa1_56 = *sys.new_Parameter("FSa1_56",0.0);
 	symbol_numeric  FSb1_56 = *sys.new_Parameter("FSb1_56",0.0);
 	symbol_numeric  FSa1_57 = *sys.new_Parameter("FSa1_57",0.0);
 	symbol_numeric  FSb1_57 = *sys.new_Parameter("FSb1_57",0.0);
 	symbol_numeric  FSa1_58 = *sys.new_Parameter("FSa1_58",0.0);
 	symbol_numeric  FSb1_58 = *sys.new_Parameter("FSb1_58",0.0);
 	symbol_numeric  FSa1_59 = *sys.new_Parameter("FSa1_59",0.0);
 	symbol_numeric  FSb1_59 = *sys.new_Parameter("FSb1_59",0.0);
 	symbol_numeric  FSa1_60 = *sys.new_Parameter("FSa1_60",0.0);
 	symbol_numeric  FSb1_60 = *sys.new_Parameter("FSb1_60",0.0);
 	symbol_numeric  FSa1_61 = *sys.new_Parameter("FSa1_61",0.0);
 	symbol_numeric  FSb1_61 = *sys.new_Parameter("FSb1_61",0.0);
 	symbol_numeric  FSa1_62 = *sys.new_Parameter("FSa1_62",0.0);
 	symbol_numeric  FSb1_62 = *sys.new_Parameter("FSb1_62",0.0);
 	symbol_numeric  FSa1_63 = *sys.new_Parameter("FSa1_63",0.0);
 	symbol_numeric  FSb1_63 = *sys.new_Parameter("FSb1_63",0.0);
 	symbol_numeric  FSa1_64 = *sys.new_Parameter("FSa1_64",0.0);
 	symbol_numeric  FSb1_64 = *sys.new_Parameter("FSb1_64",0.0);
 	symbol_numeric  FSa1_65 = *sys.new_Parameter("FSa1_65",0.0);
 	symbol_numeric  FSb1_65 = *sys.new_Parameter("FSb1_65",0.0);
 	symbol_numeric  FSa1_66 = *sys.new_Parameter("FSa1_66",0.0);
 	symbol_numeric  FSb1_66 = *sys.new_Parameter("FSb1_66",0.0);
 	symbol_numeric  FSa1_67 = *sys.new_Parameter("FSa1_67",0.0);
 	symbol_numeric  FSb1_67 = *sys.new_Parameter("FSb1_67",0.0);
 	symbol_numeric  FSa1_68 = *sys.new_Parameter("FSa1_68",0.0);
 	symbol_numeric  FSb1_68 = *sys.new_Parameter("FSb1_68",0.0);
 	symbol_numeric  FSa1_69 = *sys.new_Parameter("FSa1_69",0.0);
 	symbol_numeric  FSb1_69 = *sys.new_Parameter("FSb1_69",0.0);
 	symbol_numeric  FSa1_70 = *sys.new_Parameter("FSa1_70",0.0);
 	symbol_numeric  FSb1_70 = *sys.new_Parameter("FSb1_70",0.0);
 	symbol_numeric  FSa1_71 = *sys.new_Parameter("FSa1_71",0.0);
 	symbol_numeric  FSb1_71 = *sys.new_Parameter("FSb1_71",0.0);
 	symbol_numeric  FSa1_72 = *sys.new_Parameter("FSa1_72",0.0);
 	symbol_numeric  FSb1_72 = *sys.new_Parameter("FSb1_72",0.0);
 	symbol_numeric  FSa1_73 = *sys.new_Parameter("FSa1_73",0.0);
 	symbol_numeric  FSb1_73 = *sys.new_Parameter("FSb1_73",0.0);
 	symbol_numeric  FSa1_74 = *sys.new_Parameter("FSa1_74",0.0);
 	symbol_numeric  FSb1_74 = *sys.new_Parameter("FSb1_74",0.0);
 	symbol_numeric  FSa1_75 = *sys.new_Parameter("FSa1_75",0.0);
 	symbol_numeric  FSb1_75 = *sys.new_Parameter("FSb1_75",0.0);
 	symbol_numeric  FSa1_76 = *sys.new_Parameter("FSa1_76",0.0);
 	symbol_numeric  FSb1_76 = *sys.new_Parameter("FSb1_76",0.0);
 	symbol_numeric  FSa1_77 = *sys.new_Parameter("FSa1_77",0.0);
 	symbol_numeric  FSb1_77 = *sys.new_Parameter("FSb1_77",0.0);
 	symbol_numeric  FSa1_78 = *sys.new_Parameter("FSa1_78",0.0);
 	symbol_numeric  FSb1_78 = *sys.new_Parameter("FSb1_78",0.0);
 	symbol_numeric  FSa1_79 = *sys.new_Parameter("FSa1_79",0.0);
 	symbol_numeric  FSb1_79 = *sys.new_Parameter("FSb1_79",0.0);
 	symbol_numeric  FSa1_80 = *sys.new_Parameter("FSa1_80",0.0);
 	symbol_numeric  FSb1_80 = *sys.new_Parameter("FSb1_80",0.0);
 	symbol_numeric  FSa1_81 = *sys.new_Parameter("FSa1_81",0.0);
 	symbol_numeric  FSb1_81 = *sys.new_Parameter("FSb1_81",0.0);
 	symbol_numeric  FSa1_82 = *sys.new_Parameter("FSa1_82",0.0);
 	symbol_numeric  FSb1_82 = *sys.new_Parameter("FSb1_82",0.0);
 	symbol_numeric  FSa1_83 = *sys.new_Parameter("FSa1_83",0.0);
 	symbol_numeric  FSb1_83 = *sys.new_Parameter("FSb1_83",0.0);
 	symbol_numeric  FSa1_84 = *sys.new_Parameter("FSa1_84",0.0);
 	symbol_numeric  FSb1_84 = *sys.new_Parameter("FSb1_84",0.0);
 	symbol_numeric  FSa1_85 = *sys.new_Parameter("FSa1_85",0.0);
 	symbol_numeric  FSb1_85 = *sys.new_Parameter("FSb1_85",0.0);
 	symbol_numeric  FSa1_86 = *sys.new_Parameter("FSa1_86",0.0);
 	symbol_numeric  FSb1_86 = *sys.new_Parameter("FSb1_86",0.0);
 	symbol_numeric  FSa1_87 = *sys.new_Parameter("FSa1_87",0.0);
 	symbol_numeric  FSb1_87 = *sys.new_Parameter("FSb1_87",0.0);
 	symbol_numeric  FSa1_88 = *sys.new_Parameter("FSa1_88",0.0);
 	symbol_numeric  FSb1_88 = *sys.new_Parameter("FSb1_88",0.0);
 	symbol_numeric  FSa1_89 = *sys.new_Parameter("FSa1_89",0.0);
 	symbol_numeric  FSb1_89 = *sys.new_Parameter("FSb1_89",0.0);
 	symbol_numeric  FSa1_90 = *sys.new_Parameter("FSa1_90",0.0);
 	symbol_numeric  FSb1_90 = *sys.new_Parameter("FSb1_90",0.0);
 	symbol_numeric  FSa1_91 = *sys.new_Parameter("FSa1_91",0.0);
 	symbol_numeric  FSb1_91 = *sys.new_Parameter("FSb1_91",0.0);
 	symbol_numeric  FSa1_92 = *sys.new_Parameter("FSa1_92",0.0);
 	symbol_numeric  FSb1_92 = *sys.new_Parameter("FSb1_92",0.0);
 	symbol_numeric  FSa1_93 = *sys.new_Parameter("FSa1_93",0.0);
 	symbol_numeric  FSb1_93 = *sys.new_Parameter("FSb1_93",0.0);
 	symbol_numeric  FSa1_94 = *sys.new_Parameter("FSa1_94",0.0);
 	symbol_numeric  FSb1_94 = *sys.new_Parameter("FSb1_94",0.0);
 	symbol_numeric  FSa1_95 = *sys.new_Parameter("FSa1_95",0.0);
 	symbol_numeric  FSb1_95 = *sys.new_Parameter("FSb1_95",0.0);
 	symbol_numeric  FSa1_96 = *sys.new_Parameter("FSa1_96",0.0);
 	symbol_numeric  FSb1_96 = *sys.new_Parameter("FSb1_96",0.0);
 	symbol_numeric  FSa1_97 = *sys.new_Parameter("FSa1_97",0.0);
 	symbol_numeric  FSb1_97 = *sys.new_Parameter("FSb1_97",0.0);
 	symbol_numeric  FSa1_98 = *sys.new_Parameter("FSa1_98",0.0);
 	symbol_numeric  FSb1_98 = *sys.new_Parameter("FSb1_98",0.0);
 	symbol_numeric  FSa1_99 = *sys.new_Parameter("FSa1_99",0.0);
 	symbol_numeric  FSb1_99 = *sys.new_Parameter("FSb1_99",0.0);
 	symbol_numeric  FSa1_100 = *sys.new_Parameter("FSa1_100",0.0);
 	symbol_numeric  FSb1_100 = *sys.new_Parameter("FSb1_100",0.0);



// ************************************************************************************************
// 	 Kinematic Equations 
// ************************************************************************************************
	cout << "Kinematic Equations = " << endl;

	Matrix Phi(1,1);

	
 	Phi(0,0)=q1-(FS001 	+FSa1_1*sin(1*t)+FSb1_1*cos(1*t));

// 	Matrix dPhiNH(0,1);


// ************************************************************************************************
// 	Dynamic Equations 
// ************************************************************************************************

	cout << "Dynamic Equations = " << endl;

//	Matrix Dynamic_Equations = sys.GenForceSys("ALL");
	//cout<<Dynamic_Equations<<endl;

	lst inertial_parameters;

	inertial_parameters =
							m1, mx1, my1, mz1, Ixx1, Ixy1, Ixz1, Iyy1, Iyz1, Izz1,
							m2, mx2, my2, mz2, Ixx2, Ixy2, Ixz2, Iyy2, Iyz2, Izz2,
							m3, mx3, my3, mz3, Ixx3, Ixy3, Ixz3, Iyy3, Iyz3, Izz3,
							m4, mx4, my4, mz4, Ixx4, Ixy4, Ixz4, Iyy4, Iyz4, Izz4,
							m5, mx5, my5, mz5, Ixx5, Ixy5, Ixz5, Iyy5, Iyz5, Izz5,
							m6, mx6, my6, mz6, Ixx6, Ixy6, Ixz6, Iyy6, Iyz6, Izz6,
							m7, mx7, my7, mz7, Ixx7, Ixy7, Ixz7, Iyy7, Iyz7, Izz7,
							m8, mx8, my8, mz8, Ixx8, Ixy8, Ixz8, Iyy8, Iyz8, Izz8,
							m9, mx9, my9, mz9, Ixx9, Ixy9, Ixz9, Iyy9, Iyz9, Izz9,
							m10, mx10, my10, mz10, Ixx10, Ixy10, Ixz10, Iyy10, Iyz10, Izz10,
							m11, mx11, my11, mz11, Ixx11, Ixy11, Ixz11, Iyy11, Iyz11, Izz11,
							m12, mx12, my12, mz12, Ixx12, Ixy12, Ixz12, Iyy12, Iyz12, Izz12,
							m13, mx13, my13, mz13, Ixx13, Ixy13, Ixz13, Iyy13, Iyz13, Izz13,
							m14, mx14, my14, mz14, Ixx14, Ixy14, Ixz14, Iyy14, Iyz14, Izz14,
							m15, mx15, my15, mz15, Ixx15, Ixy15, Ixz15, Iyy15, Iyz15, Izz15,
							m16, mx16, my16, mz16, Ixx16, Ixy16, Ixz16, Iyy16, Iyz16, Izz16,
							m17, mx17, my17, mz17, Ixx17, Ixy17, Ixz17, Iyy17, Iyz17, Izz17,
							m18, mx18, my18, mz18, Ixx18, Ixy18, Ixz18, Iyy18, Iyz18, Izz18,
							m19, mx19, my19, mz19, Ixx19, Ixy19, Ixz19, Iyy19, Iyz19, Izz19,
							m20, mx20, my20, mz20, Ixx20, Ixy20, Ixz20, Iyy20, Iyz20, Izz20,
							m21, mx21, my21, mz21, Ixx21, Ixy21, Ixz21, Iyy21, Iyz21, Izz21,
							m22, mx22, my22, mz22, Ixx22, Ixy22, Ixz22, Iyy22, Iyz22, Izz22,
							m23, mx23, my23, mz23, Ixx23, Ixy23, Ixz23, Iyy23, Iyz23, Izz23,
							m24, mx24, my24, mz24, Ixx24, Ixy24, Ixz24, Iyy24, Iyz24, Izz24,
							m25, mx25, my25, mz25, Ixx25, Ixy25, Ixz25, Iyy25, Iyz25, Izz25,
							m26, mx26, my26, mz26, Ixx26, Ixy26, Ixz26, Iyy26, Iyz26, Izz26,
							m27, mx27, my27, mz27, Ixx27, Ixy27, Ixz27, Iyy27, Iyz27, Izz27,
							m28, mx28, my28, mz28, Ixx28, Ixy28, Ixz28, Iyy28, Iyz28, Izz28,
							m29, mx29, my29, mz29, Ixx29, Ixy29, Ixz29, Iyy29, Iyz29, Izz29,
							m30, mx30, my30, mz30, Ixx30, Ixy30, Ixz30, Iyy30, Iyz30, Izz30,
							m31, mx31, my31, mz31, Ixx31, Ixy31, Ixz31, Iyy31, Iyz31, Izz31,
							m32, mx32, my32, mz32, Ixx32, Ixy32, Ixz32, Iyy32, Iyz32, Izz32,
							m33, mx33, my33, mz33, Ixx33, Ixy33, Ixz33, Iyy33, Iyz33, Izz33,
							m34, mx34, my34, mz34, Ixx34, Ixy34, Ixz34, Iyy34, Iyz34, Izz34,
							m35, mx35, my35, mz35, Ixx35, Ixy35, Ixz35, Iyy35, Iyz35, Izz35,
							m36, mx36, my36, mz36, Ixx36, Ixy36, Ixz36, Iyy36, Iyz36, Izz36,
							m37, mx37, my37, mz37, Ixx37, Ixy37, Ixz37, Iyy37, Iyz37, Izz37,
							m38, mx38, my38, mz38, Ixx38, Ixy38, Ixz38, Iyy38, Iyz38, Izz38,
							m39, mx39, my39, mz39, Ixx39, Ixy39, Ixz39, Iyy39, Iyz39, Izz39,
							m40, mx40, my40, mz40, Ixx40, Ixy40, Ixz40, Iyy40, Iyz40, Izz40,
							m41, mx41, my41, mz41, Ixx41, Ixy41, Ixz41, Iyy41, Iyz41, Izz41,
							m42, mx42, my42, mz42, Ixx42, Ixy42, Ixz42, Iyy42, Iyz42, Izz42,
							m43, mx43, my43, mz43, Ixx43, Ixy43, Ixz43, Iyy43, Iyz43, Izz43,
							m44, mx44, my44, mz44, Ixx44, Ixy44, Ixz44, Iyy44, Iyz44, Izz44,
							m45, mx45, my45, mz45, Ixx45, Ixy45, Ixz45, Iyy45, Iyz45, Izz45,
							m46, mx46, my46, mz46, Ixx46, Ixy46, Ixz46, Iyy46, Iyz46, Izz46,
							m47, mx47, my47, mz47, Ixx47, Ixy47, Ixz47, Iyy47, Iyz47, Izz47,
							m48, mx48, my48, mz48, Ixx48, Ixy48, Ixz48, Iyy48, Iyz48, Izz48,
							m49, mx49, my49, mz49, Ixx49, Ixy49, Ixz49, Iyy49, Iyz49, Izz49,
							m50, mx50, my50, mz50, Ixx50, Ixy50, Ixz50, Iyy50, Iyz50, Izz50,
							m51, mx51, my51, mz51, Ixx51, Ixy51, Ixz51, Iyy51, Iyz51, Izz51,
							m52, mx52, my52, mz52, Ixx52, Ixy52, Ixz52, Iyy52, Iyz52, Izz52,
							m53, mx53, my53, mz53, Ixx53, Ixy53, Ixz53, Iyy53, Iyz53, Izz53,
							m54, mx54, my54, mz54, Ixx54, Ixy54, Ixz54, Iyy54, Iyz54, Izz54,
							m55, mx55, my55, mz55, Ixx55, Ixy55, Ixz55, Iyy55, Iyz55, Izz55,
							m56, mx56, my56, mz56, Ixx56, Ixy56, Ixz56, Iyy56, Iyz56, Izz56,
							m57, mx57, my57, mz57, Ixx57, Ixy57, Ixz57, Iyy57, Iyz57, Izz57,
							m58, mx58, my58, mz58, Ixx58, Ixy58, Ixz58, Iyy58, Iyz58, Izz58,
							m59, mx59, my59, mz59, Ixx59, Ixy59, Ixz59, Iyy59, Iyz59, Izz59,
							m60, mx60, my60, mz60, Ixx60, Ixy60, Ixz60, Iyy60, Iyz60, Izz60,
							m61, mx61, my61, mz61, Ixx61, Ixy61, Ixz61, Iyy61, Iyz61, Izz61,
							m62, mx62, my62, mz62, Ixx62, Ixy62, Ixz62, Iyy62, Iyz62, Izz62,
							m63, mx63, my63, mz63, Ixx63, Ixy63, Ixz63, Iyy63, Iyz63, Izz63,
							m64, mx64, my64, mz64, Ixx64, Ixy64, Ixz64, Iyy64, Iyz64, Izz64,
							m65, mx65, my65, mz65, Ixx65, Ixy65, Ixz65, Iyy65, Iyz65, Izz65,
							m66, mx66, my66, mz66, Ixx66, Ixy66, Ixz66, Iyy66, Iyz66, Izz66,
							m67, mx67, my67, mz67, Ixx67, Ixy67, Ixz67, Iyy67, Iyz67, Izz67,
							m68, mx68, my68, mz68, Ixx68, Ixy68, Ixz68, Iyy68, Iyz68, Izz68,
							m69, mx69, my69, mz69, Ixx69, Ixy69, Ixz69, Iyy69, Iyz69, Izz69,
							m70, mx70, my70, mz70, Ixx70, Ixy70, Ixz70, Iyy70, Iyz70, Izz70,
							m71, mx71, my71, mz71, Ixx71, Ixy71, Ixz71, Iyy71, Iyz71, Izz71,
							m72, mx72, my72, mz72, Ixx72, Ixy72, Ixz72, Iyy72, Iyz72, Izz72,
							m73, mx73, my73, mz73, Ixx73, Ixy73, Ixz73, Iyy73, Iyz73, Izz73,
							m74, mx74, my74, mz74, Ixx74, Ixy74, Ixz74, Iyy74, Iyz74, Izz74,
							m75, mx75, my75, mz75, Ixx75, Ixy75, Ixz75, Iyy75, Iyz75, Izz75,
							m76, mx76, my76, mz76, Ixx76, Ixy76, Ixz76, Iyy76, Iyz76, Izz76,
							m77, mx77, my77, mz77, Ixx77, Ixy77, Ixz77, Iyy77, Iyz77, Izz77,
							m78, mx78, my78, mz78, Ixx78, Ixy78, Ixz78, Iyy78, Iyz78, Izz78,
							m79, mx79, my79, mz79, Ixx79, Ixy79, Ixz79, Iyy79, Iyz79, Izz79,
							m80, mx80, my80, mz80, Ixx80, Ixy80, Ixz80, Iyy80, Iyz80, Izz80,
							m81, mx81, my81, mz81, Ixx81, Ixy81, Ixz81, Iyy81, Iyz81, Izz81,
							m82, mx82, my82, mz82, Ixx82, Ixy82, Ixz82, Iyy82, Iyz82, Izz82,
							m83, mx83, my83, mz83, Ixx83, Ixy83, Ixz83, Iyy83, Iyz83, Izz83,
							m84, mx84, my84, mz84, Ixx84, Ixy84, Ixz84, Iyy84, Iyz84, Izz84,
							m85, mx85, my85, mz85, Ixx85, Ixy85, Ixz85, Iyy85, Iyz85, Izz85,
							m86, mx86, my86, mz86, Ixx86, Ixy86, Ixz86, Iyy86, Iyz86, Izz86,
							m87, mx87, my87, mz87, Ixx87, Ixy87, Ixz87, Iyy87, Iyz87, Izz87,
							m88, mx88, my88, mz88, Ixx88, Ixy88, Ixz88, Iyy88, Iyz88, Izz88,
							m89, mx89, my89, mz89, Ixx89, Ixy89, Ixz89, Iyy89, Iyz89, Izz89,
							m90, mx90, my90, mz90, Ixx90, Ixy90, Ixz90, Iyy90, Iyz90, Izz90,
							m91, mx91, my91, mz91, Ixx91, Ixy91, Ixz91, Iyy91, Iyz91, Izz91,
							m92, mx92, my92, mz92, Ixx92, Ixy92, Ixz92, Iyy92, Iyz92, Izz92,
							m93, mx93, my93, mz93, Ixx93, Ixy93, Ixz93, Iyy93, Iyz93, Izz93,
							m94, mx94, my94, mz94, Ixx94, Ixy94, Ixz94, Iyy94, Iyz94, Izz94,
							m95, mx95, my95, mz95, Ixx95, Ixy95, Ixz95, Iyy95, Iyz95, Izz95,
							m96, mx96, my96, mz96, Ixx96, Ixy96, Ixz96, Iyy96, Iyz96, Izz96,
							m97, mx97, my97, mz97, Ixx97, Ixy97, Ixz97, Iyy97, Iyz97, Izz97,
							m98, mx98, my98, mz98, Ixx98, Ixy98, Ixz98, Iyy98, Iyz98, Izz98,
							m99, mx99, my99, mz99, Ixx99, Ixy99, Ixz99, Iyy99, Iyz99, Izz99,
							m100, mx100, my100, mz100, Ixx100, Ixy100, Ixz100, Iyy100, Iyz100, Izz100;


//	cout << "W and Phiq Matrix Calculation= " << endl;

//	Matrix M_inertial_parameters=Matrix(inertial_parameters.nops(),1,inertial_parameters);
//	Matrix W = sys.jacobian(Dynamic_Equations.transpose(),M_inertial_parameters);
//	Matrix Phiq= sys.jacobian(Phi.transpose(),q);


//	cout << "Exporting Matrix W" << endl;
//	lst new_atom_list_W, new_exp_list_W;        
//	matrix_list_optimize (W, new_atom_list_W, new_exp_list_W);
//	sys.export_Matrix_C("W","_W",W, new_atom_list_W, new_exp_list_W ,ORDER);
//	sys.export_function_MATLAB("W", "W_", W, new_atom_list_W, new_exp_list_W);

//	cout << "Exporting MATLAB functions" << endl;
//	sys.export_init_function_MATLAB();


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
	
// 	Usa (necesita que estén definidas) las ecuaciones dinámicas y deriva respecto a qpp y necesita que estén definidos los torsores de inercia
// 	sys.Matrix_Calculation(Phi, coord_indep_init, vel_indep_init, Dynamic_Equations, sys, METHOD);
	
// 	Calcula las matrices M y Q sin las ecuaciones de la dinámica
	sys.Matrix_Calculation( Phi, coord_indep_init, vel_indep_init, sys, METHOD);

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

state = 
		q1,*dq1,*ddq1,
		q2,*dq2,*ddq2,
		q3,*dq3,*ddq3,
		q4,*dq4,*ddq4,
		q5,*dq5,*ddq5,
		q6,*dq6,*ddq6,
		q7,*dq7,*ddq7,
		q8,*dq8,*ddq8,
		q9,*dq9,*ddq9,
		q10,*dq10,*ddq10,
		q11,*dq11,*ddq11,
		q12,*dq12,*ddq12,
		q13,*dq13,*ddq13,
		q14,*dq14,*ddq14,
		q15,*dq15,*ddq15,
		q16,*dq16,*ddq16,
		q17,*dq17,*ddq17,
		q18,*dq18,*ddq18,
		q19,*dq19,*ddq19,
		q20,*dq20,*ddq20,
		q21,*dq21,*ddq21,
		q22,*dq22,*ddq22,
		q23,*dq23,*ddq23,
		q24,*dq24,*ddq24,
		q25,*dq25,*ddq25,
		q26,*dq26,*ddq26,
		q27,*dq27,*ddq27,
		q28,*dq28,*ddq28,
		q29,*dq29,*ddq29,
		q30,*dq30,*ddq30,
		q31,*dq31,*ddq31,
		q32,*dq32,*ddq32,
		q33,*dq33,*ddq33,
		q34,*dq34,*ddq34,
		q35,*dq35,*ddq35,
		q36,*dq36,*ddq36,
		q37,*dq37,*ddq37,
		q38,*dq38,*ddq38,
		q39,*dq39,*ddq39,
		q40,*dq40,*ddq40,
		q41,*dq41,*ddq41,
		q42,*dq42,*ddq42,
		q43,*dq43,*ddq43,
		q44,*dq44,*ddq44,
		q45,*dq45,*ddq45,
		q46,*dq46,*ddq46,
		q47,*dq47,*ddq47,
		q48,*dq48,*ddq48,
		q49,*dq49,*ddq49,
		q50,*dq50,*ddq50,
		q51,*dq51,*ddq51,
		q52,*dq52,*ddq52,
		q53,*dq53,*ddq53,
		q54,*dq54,*ddq54,
		q55,*dq55,*ddq55,
		q56,*dq56,*ddq56,
		q57,*dq57,*ddq57,
		q58,*dq58,*ddq58,
		q59,*dq59,*ddq59,
		q60,*dq60,*ddq60,
		q61,*dq61,*ddq61,
		q62,*dq62,*ddq62,
		q63,*dq63,*ddq63,
		q64,*dq64,*ddq64,
		q65,*dq65,*ddq65,
		q66,*dq66,*ddq66,
		q67,*dq67,*ddq67,
		q68,*dq68,*ddq68,
		q69,*dq69,*ddq69,
		q70,*dq70,*ddq70,
		q71,*dq71,*ddq71,
		q72,*dq72,*ddq72,
		q73,*dq73,*ddq73,
		q74,*dq74,*ddq74,
		q75,*dq75,*ddq75,
		q76,*dq76,*ddq76,
		q77,*dq77,*ddq77,
		q78,*dq78,*ddq78,
		q79,*dq79,*ddq79,
		q80,*dq80,*ddq80,
		q81,*dq81,*ddq81,
		q82,*dq82,*ddq82,
		q83,*dq83,*ddq83,
		q84,*dq84,*ddq84,
		q85,*dq85,*ddq85,
		q86,*dq86,*ddq86,
		q87,*dq87,*ddq87,
		q88,*dq88,*ddq88,
		q89,*dq89,*ddq89,
		q90,*dq90,*ddq90,
		q91,*dq91,*ddq91,
		q92,*dq92,*ddq92,
		q93,*dq93,*ddq93,
		q94,*dq94,*ddq94,
		q95,*dq95,*ddq95,
		q96,*dq96,*ddq96,
		q97,*dq97,*ddq97,
		q98,*dq98,*ddq98,
		q99,*dq99,*ddq99,
		q100,*dq100,*ddq100;

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

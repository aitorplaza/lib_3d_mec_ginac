% The parameter T is a table that represents the modified Denavit-Hartenberg parameters
% of the mechanism. The parameters are the ones shown in the next table as described
% in (for example): 
% Modeling, Identification and Control of Robots, Khalil and Dombre

% Table T is of size n x 4:

%	-----------------------------
% 	a	b	c	q
%	-----------------------------
% 	a_1	b_1	c_1	q_1
% 	...
% 	a_i	b_i	c_i	q_i
% 	...
% 	a_n	b_n	c_n	q_n
%	-----------------------------

% The algorithm creates the B0 base, the P0 point and the R0 reference as the ground

% H is the number of harmonics used to optimize trajectories

function DH_generate_main_symbolic(T,H);

n=size(T,1);

fid=fopen('./../../main_symbolic.cc','w');

fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'//*****************************************************************************************************************\n');
fprintf(fid,'// 	THIS FILE HAS BEEN GENERATED AUTOMATICALLY BY THE MATLAB SCRIPT DH_generated_main_symbolic.m            \n');
fprintf(fid,'//*****************************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'\n');



fprintf(fid,'#include <fstream>\n');
fprintf(fid,'#include "lib_3d_mec_ginac/lib_3d_mec_ginac.h"\n');
fprintf(fid,'#include <ginac/ginac.h>\n');
fprintf(fid,'#include <sstream>\n');
fprintf(fid,'\n');
fprintf(fid,'//*****************************************************************************************************************\n');
fprintf(fid,'// 	PLEASE AlWAYS DEFINE ORDER & MAPLE & METHOD\n');
fprintf(fid,'// 	DEFINED IN "globals.h" + "compilation line or with #define"\n');
fprintf(fid,'\n');
fprintf(fid,'// 	#define METHOD VIRTUAL_POWER or #define METHOD LAGRANGE  // or complilation line -DORDER=CMO or -DORDER=RMO\n');
fprintf(fid,'// 	#define ORDER CMO or #define ORDER RMO  // or complilation line -DORDER=CMO or -DORDER=RMO\n');
fprintf(fid,'// 	#define MAPLE MAPLE_ON or #define MAPLE MAPLE_OFF  // or complilation line -DMAPLE=MAPLE_ON -DMAPLE=MAPLE_OFF\n');
fprintf(fid,'\n');
fprintf(fid,'// 	IF METHOD = 1 ==> VIRTUAL_POWER & IF METHOD = 0 ==> LAGRANGE\n');
fprintf(fid,'// 	IF ORDER  = 1 ==> CMO           & IF ORDER  = 0 ==> RMO\n');
fprintf(fid,'// 	IF MAPLE  = 1 ==> MAPLE_ON      & IF MAPLE  = 0 ==> MAPLE_OFF\n');
fprintf(fid,'//*****************************************************************************************************************\n');
fprintf(fid,'#ifdef LAG	\n');
fprintf(fid,'	# define METHOD LAGRANGE\n');
fprintf(fid,'#endif\n');
fprintf(fid,'\n');
fprintf(fid,'#ifdef V_P\n');
fprintf(fid,'	# define METHOD VIRTUAL_POWER\n');
fprintf(fid,'#endif\n');
fprintf(fid,'//*****************************************************************************************************************\n');
fprintf(fid,'#ifdef Q\n');
fprintf(fid,'	#define PROBLEM_TYPE "Q"\n');
fprintf(fid,'#endif\n');
fprintf(fid,'#ifdef Z\n');
fprintf(fid,'	#define PROBLEM_TYPE "Z"\n');
fprintf(fid,'#endif\n');
fprintf(fid,'#ifdef I3AL_Q\n');
fprintf(fid,'	#define PROBLEM_TYPE "I3AL_Q"\n');
fprintf(fid,'#endif\n');
fprintf(fid,'#ifdef I3AL_Z\n');
fprintf(fid,'	#define PROBLEM_TYPE "I3AL_Z"\n');
fprintf(fid,'#endif\n');
fprintf(fid,'#ifdef ALL\n');
fprintf(fid,'	#define PROBLEM_TYPE "ALL"\n');
fprintf(fid,'#endif\n');
fprintf(fid,'//*****************************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'using namespace GiNaC;\n');
fprintf(fid,'using namespace std;\n');
fprintf(fid,'	\n');
fprintf(fid,'// SYSTEM DEFINITION\n');
fprintf(fid,'// *****************************************************************************************************************	\n');
fprintf(fid,'\n');
fprintf(fid,'void printError2(const char* arg){\n');
fprintf(fid,'	printf("%%s\\n", arg);\n');
fprintf(fid,'}	\n');
fprintf(fid,'	\n');
fprintf(fid,'#ifdef PROCEDURE\n');
fprintf(fid,'int C_EXPORT_AS_PROCEDURE=1;\n');
fprintf(fid,'#else\n');
fprintf(fid,'int C_EXPORT_AS_PROCEDURE=0;\n');
fprintf(fid,'#endif\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'int main(int argc, char *argv[]) {\n');
fprintf(fid,'\n');
fprintf(fid,'// *****************************************************************************************************************	\n');
fprintf(fid,'cout << " " << endl;\n');
fprintf(fid,'cout << "***********************************************************" << endl;\n');
fprintf(fid,['cout << "*  Denavit-Hartenberg Serial Chain with ',int2str(n),' solids.       *" << endl;\n']);
fprintf(fid,'cout << "***********************************************************" << endl;\n');
fprintf(fid,'cout << " " << endl;\n');
fprintf(fid,'system("date");\n');
fprintf(fid,'cout << " " << endl;\n');
fprintf(fid,'// *****************************************************************************************************************	\n');
fprintf(fid,'\n');
fprintf(fid,'if (argc!=3){\n');
fprintf(fid,'        printf("Error: The program %%s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\\n",argv[0]);\n');
fprintf(fid,'        exit(1);\n');
fprintf(fid,'    }\n');
fprintf(fid,'\n');
fprintf(fid,'if (0==strcmp(argv[1],"DOWN")){\n');
fprintf(fid,'    gravity=DOWN;\n');
fprintf(fid,'    cout << "Gravity DOWN" << endl;\n');
fprintf(fid,'}\n');
fprintf(fid,'else{\n');
fprintf(fid,'    if (0==strcmp(argv[1],"UP")){\n');
fprintf(fid,'        gravity=UP;\n');
fprintf(fid,'        cout << "Gravity UP" << endl;\n');
fprintf(fid,'    }\n');
fprintf(fid,'    else\n');
fprintf(fid,'    {\n');
fprintf(fid,'        printf("Error: The program %%s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\\n",argv[0]);\n');
fprintf(fid,'        exit(1);\n');
fprintf(fid,'    }\n');
fprintf(fid,'}\n');
fprintf(fid,'\n');
fprintf(fid,'if (0==strcmp(argv[2],"YES")){\n');
fprintf(fid,'        atomization=YES;\n');
fprintf(fid,'        cout << "Atomize YES" << endl;\n');
fprintf(fid,'}\n');
fprintf(fid,'else{\n');
fprintf(fid,'\n');
fprintf(fid,'    if (0==strcmp(argv[2],"NO")){\n');
fprintf(fid,'        atomization=NO;\n');
fprintf(fid,'        cout << "Atomize NO" << endl;\n');
fprintf(fid,'    }\n');
fprintf(fid,'    else\n');
fprintf(fid,'    {\n');
fprintf(fid,'        printf("Error: The program %%s takes two parameters: Gravity (UP/DOWN) and Atomize (YES/NO)\\n",argv[0]);\n');
fprintf(fid,'        exit(1);\n');
fprintf(fid,'    }\n');
fprintf(fid,'}\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	double integration_time=strtod(argv[1], NULL);\n');
fprintf(fid,'	double delta_t= strtod(argv[2], NULL);\n');
fprintf(fid,'	long int k,steps;\n');
fprintf(fid,'	\n');
fprintf(fid,'	printf("integration_time %%g delta_t %%g\\n", integration_time, delta_t);\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	System definition\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	System sys(&printError2);\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	TIME DEFINITION\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'        symbol_numeric t=sys.get_Time_Symbol ( );\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Coordinate definition\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');

fprintf(fid,'	// Rotation angles from root to leaf\n');
for i=1:n
	clear s;
	s=['	symbol_numeric q',int2str(i),' = *sys.new_Coordinate("q',int2str(i),'","dq',int2str(i),'","ddq',int2str(i),'", 0.0 , 0.0 , 0.0);\n'];
	fprintf(fid,s);
end
fprintf(fid,'\n');


fprintf(fid,'	// Velocities\n');
for i=1:n
	clear s;
	s=['	symbol_numeric *dq',int2str(i),'=sys.get_Velocity("dq',int2str(i),'");\n'];
	fprintf(fid,s);
end
fprintf(fid,'\n');


fprintf(fid,'	// Accelerations\n');
for i=1:n
	clear s;
	s=['	symbol_numeric *ddq',int2str(i),'=sys.get_Acceleration("ddq',int2str(i),'");\n'];
	fprintf(fid,s);
end

fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Initial Position Additional Constraint Equations\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	lst coord_indep_init;\n');
fprintf(fid,'	lst vel_indep_init;\n');
fprintf(fid,'\n');

fprintf(fid,'//	coord_indep_init = (');
for i=1:n-1
	clear s;
	s=['q',int2str(i),'-0.0),('];
	fprintf(fid,s);
end
clear s;
s=['q',int2str(n),'-0.0);\n'];
fprintf(fid,s);

fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Kinematical parameter definition\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	\n');
fprintf(fid,'	// Geometric Parameters\n');

clear s;s=['jarl',num2str(T(1,2)),'jarl'];
%disp(s)

for i=1:n
	fprintf(fid,['	symbol_numeric a',int2str(i),' = *sys.new_Parameter("a',int2str(i),'",',sprintf('%5.5f',T(i,1)),');\n']);
	fprintf(fid,['	symbol_numeric b',int2str(i),' = *sys.new_Parameter("b',int2str(i),'",',sprintf('%5.5f',T(i,2)),');\n']);
	fprintf(fid,['	symbol_numeric c',int2str(i),' = *sys.new_Parameter("c',int2str(i),'",',sprintf('%5.5f',T(i,3)),');\n']);
end
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'\n');


fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'// 	 KINEMATICS\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Define Bases\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'\n');


fprintf(fid,'	sys.new_Base("B0" ,"xyz", 0,0,1,0);\t// Creating a base fixed to the ground\n');
for i=1:n
	clear s;s=['	sys.new_Base("B',int2str(i),'a","B',int2str(i-1),'" , 1,0,0,b',int2str(i),');\t// Rotation wrt x',int2str(i-1),'\n'];fprintf(fid,s);
%  	clear s;s=['	sys.new_Base("B',int2str(i),'" ,"B',int2str(i),'a", 0,0,1,q',int2str(i),');\t// Rotation wrt z',int2str(i),'\n'];fprintf(fid,s);
	clear s;s=['	sys.new_Base("B',int2str(i),'" ,"B1a", 0,0,1,q',int2str(i),');\t// Rotation wrt z',int2str(i),'\n'];fprintf(fid,s);
end
fprintf(fid,'\n');
fprintf(fid,'\n');



fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Define Vectors\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	Vector3D VZERO  = *sys.new_Vector3D("VZERO",0, 0,0,"xyz");\n\n');

for i=1:n
	clear s;s=['	Vector3D P',int2str(i-1),'P',int2str(i),'  = *sys.new_Vector3D("P',int2str(i-1),'P',int2str(i),'a",a',int2str(i),', 0,0,"B',int2str(i-1),'") + *sys.new_Vector3D("P',int2str(i-1),'P',int2str(i),'b", 0,0,c',int2str(i),', "B',int2str(i),'");\n'];fprintf(fid,s);
end
fprintf(fid,'	\n');



fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Define Points\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'	\n');
fprintf(fid,'	Point * P0 = sys.new_Point("P0","O", &VZERO);\n\n');

for i=1:n
	clear s;s=['	Point * P',int2str(i),' = sys.new_Point("P',int2str(i),'","P',int2str(i-1),'", &P',int2str(i-1),'P',int2str(i),');\n'];
	fprintf(fid,s);
end
fprintf(fid,'\n');


fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Dynamical Parameter Definition\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');

for i=1:n
	clear s;s=['	// Inertial parameters of the Solid ',int2str(i),'\n'];					fprintf(fid,s);
	clear s;s=['	symbol_numeric  m',int2str(i),'   = *sys.new_Parameter("m',int2str(i),'",  1.0);\n'];	fprintf(fid,s);
	clear s;s=['	symbol_numeric  mx',int2str(i),'  = *sys.new_Parameter("mx',int2str(i),'", 0.0);\n'];	fprintf(fid,s);
	clear s;s=['	symbol_numeric  my',int2str(i),'  = *sys.new_Parameter("my',int2str(i),'", 0.0);\n'];	fprintf(fid,s);
	clear s;s=['	symbol_numeric  mz',int2str(i),'  = *sys.new_Parameter("mz',int2str(i),'", 0.0);\n'];	fprintf(fid,s);
	clear s;s=['	symbol_numeric  Ixx',int2str(i),' = *sys.new_Parameter("Ixx',int2str(i),'",1.0);\n'];	fprintf(fid,s);
	clear s;s=['	symbol_numeric  Ixy',int2str(i),' = *sys.new_Parameter("Ixy',int2str(i),'",0.0);\n'];	fprintf(fid,s);
	clear s;s=['	symbol_numeric  Ixz',int2str(i),' = *sys.new_Parameter("Ixz',int2str(i),'",0.0);\n'];	fprintf(fid,s);
	clear s;s=['	symbol_numeric  Iyy',int2str(i),' = *sys.new_Parameter("Iyy',int2str(i),'",1.0);\n'];	fprintf(fid,s);
	clear s;s=['	symbol_numeric  Iyz',int2str(i),' = *sys.new_Parameter("Iyz',int2str(i),'",0.0);\n'];	fprintf(fid,s);
	clear s;s=['	symbol_numeric  Izz',int2str(i),' = *sys.new_Parameter("Izz',int2str(i),'",1.0);\n'];	fprintf(fid,s);
	fprintf(fid,'\n\n');
end

fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Center of Gravity Vectors\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');

for i=1:n
	clear s;s=['	Vector3D P',int2str(i),'G',int2str(i),'= *sys.new_Vector3D("P',int2str(i),'G',int2str(i),'",mx',int2str(i),'/m',int2str(i),',my',int2str(i),'/m',int2str(i),',mz',int2str(i),'/m',int2str(i),',"B',int2str(i),'");\n'];
	fprintf(fid,s);
end
fprintf(fid,'\n');


fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Inertia Tensors\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
for i=1:n
clear s;s=['    	Tensor3D I',int2str(i),' = *sys.new_Tensor3D("I',int2str(i),'",	(ex)Ixx',int2str(i),',(ex)Ixy',int2str(i),',(ex)Ixz',int2str(i),',\n'];	
fprintf(fid,s);
clear s;s=['						(ex)Ixy',int2str(i),',(ex)Iyy',int2str(i),',(ex)Iyz',int2str(i),',\n'];
fprintf(fid,s);
clear s;s=['						(ex)Ixz',int2str(i),',(ex)Iyz',int2str(i),',(ex)Izz',int2str(i),',"B',int2str(i),'");\n'];
fprintf(fid,s);
fprintf(fid,'// -----------------------------------------------------------------------\n');
end
fprintf(fid,'\n');


fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Define Frames\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
for i=0:n
	clear s;s=['	Frame * Fra_',int2str(i),'= sys.new_Frame("Fra_',int2str(i),'","P',int2str(i),'","B',int2str(i),'");\n'];fprintf(fid,s);
end
fprintf(fid,'\n');
fprintf(fid,'\n');


fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Define Solids\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
for i=1:n
	clear s;s=['	Solid * BAR',int2str(i),' = sys.new_Solid("BAR',int2str(i),'","P',int2str(i),'","B',int2str(i),'","m',int2str(i),'","P',int2str(i),'G',int2str(i),'","I',int2str(i),'");\n'];
	fprintf(fid,s);
end
fprintf(fid,'\n');


fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Define Objects to Draw\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
for i=1:n
	clear s;s=['//\tDrawing3D * BAR',int2str(i),'_3D = sys.new_Drawing3D("BAR',int2str(i),'_3D", BAR',int2str(i),',"./solids/solid_',int2str(i),'.stl" ,1,0,0,0.5);\n'];
	fprintf(fid,s);
end

for i=0:n
	clear s;s=['\tDrawing3D * Fra_BAR',int2str(i),'_3D = sys.new_Drawing3D("Fra_BAR',int2str(i),'_3D","Fra_',int2str(i),'",1);\n'];
	fprintf(fid,s);
end
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'\n');


fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Forces Definition\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
for i=1:n
	clear s;s=['//	symbol_numeric Ma',int2str(i),' = *sys.new_Parameter("Ma',int2str(i),'",0.0);\n'];
	fprintf(fid,s);
end
fprintf(fid,'\n');
for i=1:n
	clear s;s=['	Vector3D F',int2str(i),' = *sys.new_Vector3D("F',int2str(i),'",0.0,0.0,0.0, "B',int2str(i),'");	\n'];
	fprintf(fid,s);
end
fprintf(fid,'\n');


fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	DAMPING Definition\n');
fprintf(fid,'// ************************************************************************************************\n');

fprintf(fid,'	double c=1.0;\n');

clear s;s=['	Vector3D M',int2str(1),' = *sys.new_Vector3D("M',int2str(1),'",0.0,0.0,-c*(*dq',int2str(1),'-*dq',int2str(1+1),'), "B',int2str(1),'");\n'];	fprintf(fid,s);
for i=2:n-1
	clear s;s=['	Vector3D M',int2str(i),' = *sys.new_Vector3D("M',int2str(i),'",0.0,0.0,-c*(2**dq',int2str(i),'-*dq',int2str(i-1),'-*dq',int2str(i+1),'), "B',int2str(i),'");\n'];
	fprintf(fid,s);
end
clear s;s=['	Vector3D M',int2str(n),' = *sys.new_Vector3D("M',int2str(n),'",0.0,0.0,-c*(*dq',int2str(n),'-*dq',int2str(n-1),'), "B',int2str(n),'");\n'];	fprintf(fid,s);


for i=1:n
	clear s;s=['//	Vector3D M',int2str(i),' = *sys.new_Vector3D("M',int2str(i),'",0.0,0.0,Ma',int2str(i),', "B',int2str(i),'");\n'];
	fprintf(fid,s);
end
fprintf(fid,'\n');

fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Define Wrenches	\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	cout << "Define Wrenches" << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'// 	//	Gravity\n');
for i=1:n
	clear s;s=['	Wrench3D * Gravity',int2str(i),' = sys.Gravity_Wrench("BAR',int2str(i),'");\n'];
	fprintf(fid,s);
end
fprintf(fid,'// \n');

fprintf(fid,'	//	Inertia\n');
for i=1:n
	clear s;s=['	Wrench3D * Inertia_',int2str(i),' = sys.Inertia_Wrench("BAR',int2str(i),'");\n'];
	fprintf(fid,s);
end
fprintf(fid,'	\n');


fprintf(fid,'	//	External Moments\n');
for i=1:n
	clear s;s=['	Wrench3D * WExternalAction',int2str(i),' = sys.new_Wrench3D ( "WExternalAction',int2str(i),'", F',int2str(i),', M',int2str(i),', P',int2str(i),' , BAR',int2str(i),' , "Constitutive");\n'];
	fprintf(fid,s);
end
fprintf(fid,'	\n');

for i=2:n
	clear s;s=['//	Wrench3D * WExternalReaction',int2str(i),' = sys.new_Wrench3D ( "WExternalReaction',int2str(i),'", -F',int2str(i),', -M',int2str(i),', P',int2str(i),' , BAR',int2str(i-1),' , "Constitutive") ;\n'];
	fprintf(fid,s);
end
fprintf(fid,'\n');
fprintf(fid,'\n');

%  for i=1:n
for i=1:1
	clear s;s=['	symbol_numeric lambda',int2str(i),'  = *sys.new_Joint_Unknown("lambda',int2str(i),'");\n'];
	fprintf(fid,s);

end
fprintf(fid,'\n');
fprintf(fid,'\n');


fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'// 	Vectors needed to take diferent Jacobians\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	cout << "Vectors needed to take diferent Jacobians" << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'	Matrix q = sys.Coordinates();\n');
fprintf(fid,'	Matrix dq = sys.Velocities();\n');
fprintf(fid,'	Matrix ddq = sys.Accelerations();\n');
fprintf(fid,'	Matrix pars = sys.Parameters();\n');
fprintf(fid,'// 	Matrix inps = sys.Inputs();\n');
fprintf(fid,'	Matrix unks = sys.Joint_Unknowns();\n');
fprintf(fid,'\n');



fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'// 	 Parameters for the Trajectory optimization \n');
fprintf(fid,'// ************************************************************************************************\n');

fprintf(fid,'// // Constante term of the Fourier Series\n');
for i=1:n
	clear s;s=[' 	symbol_numeric  FS00',int2str(i),' = *sys.new_Parameter("FS00',int2str(i),'",0.0);\n'];
	fprintf(fid,s);
end
fprintf(fid,'\n');

for h=1:H
	clear s;s=['// Harmonic number ',int2str(h),' of the Fourier Series	\n'];
	fprintf(fid,s);
	for i=1:n
		clear s;s=[' 	symbol_numeric  FSa',int2str(h),'_',int2str(i),' = *sys.new_Parameter("FSa',int2str(h),'_',int2str(i),'",0.0);\n'];fprintf(fid,s);
		clear s;s=[' 	symbol_numeric  FSb',int2str(h),'_',int2str(i),' = *sys.new_Parameter("FSb',int2str(h),'_',int2str(i),'",0.0);\n'];fprintf(fid,s);
	end
	fprintf(fid,'\n');
end
fprintf(fid,'\n');
fprintf(fid,'\n');


fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'// 	 Kinematic Equations \n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'	cout << "Kinematic Equations = " << endl;\n');
fprintf(fid,'\n');

%  clear s;s=['	Matrix Phi(',int2str(n),',1);\n'];
clear s;s=['	Matrix Phi(1,1);\n'];

fprintf(fid,s);
fprintf(fid,'\n');
fprintf(fid,'	\n');

%  for i=1:n
for i=1:1
	clear s;s=[' 	Phi(',int2str(i-1),',0)=q',int2str(i),'-(FS00',int2str(i),' '];fprintf(fid,s);
	for h=1:H
		clear s;s=['\t+FSa',int2str(h),'_',int2str(i),'*sin(',int2str(h),'*t)+FSb',int2str(h),'_',int2str(i),'*cos(',int2str(h),'*t)'];fprintf(fid,s);
	end
	fprintf(fid,');\n');
end

fprintf(fid,'\n');
fprintf(fid,'// 	Matrix dPhiNH(0,1);\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'// 	Dynamic Equations \n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	cout << "Dynamic Equations = " << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'//	Matrix Dynamic_Equations = sys.GenForceSys("ALL");\n');
fprintf(fid,'	//cout<<Dynamic_Equations<<endl;\n');
fprintf(fid,'\n');
fprintf(fid,'	lst inertial_parameters;\n');
fprintf(fid,'\n');

fprintf(fid,'	inertial_parameters =\n');
for i=1:n-1
	clear s;s=['\t\t\t\t\t\t\tm',int2str(i),', mx',int2str(i),', my',int2str(i),', mz',int2str(i),', Ixx',int2str(i),', Ixy',int2str(i),', Ixz',int2str(i),', Iyy',int2str(i),', Iyz',int2str(i),', Izz',int2str(i),',\n'];
	fprintf(fid,s);
end
clear s;s=['\t\t\t\t\t\t\tm',int2str(n),', mx',int2str(n),', my',int2str(n),', mz',int2str(n),', Ixx',int2str(n),', Ixy',int2str(n),', Ixz',int2str(n),', Iyy',int2str(n),', Iyz',int2str(n),', Izz',int2str(n),';\n'];
fprintf(fid,s);
fprintf(fid,'\n');

fprintf(fid,'\n');
fprintf(fid,'//	cout << "W and Phiq Matrix Calculation= " << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'//	Matrix M_inertial_parameters=Matrix(inertial_parameters.nops(),1,inertial_parameters);\n');
fprintf(fid,'//	Matrix W = sys.jacobian(Dynamic_Equations.transpose(),M_inertial_parameters);\n');
fprintf(fid,'//	Matrix Phiq= sys.jacobian(Phi.transpose(),q);\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'//	cout << "Exporting Matrix W" << endl;\n');
fprintf(fid,'//	lst new_atom_list_W, new_exp_list_W;        \n');
fprintf(fid,'//	matrix_list_optimize (W, new_atom_list_W, new_exp_list_W);\n');
fprintf(fid,'//	sys.export_Matrix_C("W","_W",W, new_atom_list_W, new_exp_list_W ,ORDER);\n');
fprintf(fid,'//	sys.export_function_MATLAB("W", "W_", W, new_atom_list_W, new_exp_list_W);\n');
fprintf(fid,'\n');
fprintf(fid,'//	cout << "Exporting MATLAB functions" << endl;\n');
fprintf(fid,'//	sys.export_init_function_MATLAB();\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'// 	Output Vector\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	cout << "Output Vector" << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'	Matrix Output(1,1);\n');
fprintf(fid,'	Output(0,0)=0;\n');
fprintf(fid,'	sys.new_Matrix("Output",Output);\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'// 	Energy Equations\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	cout << "Energy Equations" << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'	Matrix Energy(1,1);\n');
fprintf(fid,'	Energy(0,0)=0;\n');
fprintf(fid,'	sys.new_Matrix("Energy",Energy);\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'// 	Matrix Calculation 	\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'	\n');
fprintf(fid,'        cout << "Matrix Calculation" << endl;\n');
fprintf(fid,'	\n');
fprintf(fid,'// 	Usa (necesita que estén definidas) las ecuaciones dinámicas y deriva respecto a qpp y necesita que estén definidos los torsores de inercia\n');
fprintf(fid,'// 	sys.Matrix_Calculation(Phi, coord_indep_init, vel_indep_init, Dynamic_Equations, sys, METHOD);\n');
fprintf(fid,'	\n');
fprintf(fid,'// 	Calcula las matrices M y Q sin las ecuaciones de la dinámica\n');
fprintf(fid,'	sys.Matrix_Calculation( Phi, coord_indep_init, vel_indep_init, sys, METHOD);\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'// 	Export C code for Direct Simulation \n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	cout << "Export C code for Direct Simulation " << endl;\n');
fprintf(fid,'	sys.export_Dynamic_Simulation(sys, ORDER , MAPLE);\n');
fprintf(fid,'        \n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'// 	Export Point, Base and Frame Diagrams \n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'#ifdef GRAPHVIZ \n');
fprintf(fid,'	cout << "Export Point, Base and Frame Diagrams" << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'	sys.export_Graphviz_dot (  );\n');
fprintf(fid,'\n');
fprintf(fid,'	//Generate eps figure\n');
fprintf(fid,'    	system("dot -Tps   base_diagram.dot -o plain_base_diagram.eps");\n');
fprintf(fid,'    	system("latex base_diagram.tex");\n');
fprintf(fid,'    	system("dvips base_diagram.dvi -o base_diagram.eps");\n');
fprintf(fid,'	//Generate figure eps\n');
fprintf(fid,'    	system("dot -Tps   point_diagram.dot -o plain_point_diagram.eps");\n');
fprintf(fid,'     	system("latex point_diagram.tex");\n');
fprintf(fid,'    	system("dvips point_diagram.dvi -o point_diagram.eps");\n');
fprintf(fid,'	//Generate eps figure\n');
fprintf(fid,'    	system("dot -Tps   frame_diagram.dot -o plain_frame_diagram.eps");\n');
fprintf(fid,'    	system("latex frame_diagram.tex");\n');
fprintf(fid,'    	system("dvips base_diagram.dvi -o base_diagram.eps");\n');
fprintf(fid,'#endif\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Export MATLAB environment vector \n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	cout << "Export ENVIRONMENT file " << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'	sys.export_environment_m (  );\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Export config.ini file\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	cout << "Export config.ini file " << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'	sys.export_config_ini (  );\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Export C++ code for Openscenegraph\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	cout << "Export C++ code for Openscenegraph." << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'	sys.export_open_scene_graph ( );\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Export State File\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	cout << "Export State File" << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'    	lst state;\n');
fprintf(fid,'\n');

fprintf(fid,'state = \n');
for i=1:n-1
	clear s;s=['		q',int2str(i),',*dq',int2str(i),',*ddq',int2str(i),',\n'];
	fprintf(fid,s);
end
clear s;s=['		q',int2str(n),',*dq',int2str(n),',*ddq',int2str(n),';\n'];
fprintf(fid,s);

fprintf(fid,'\n');
fprintf(fid,'	sys.export_write_data_file_C(state);\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Export grphics.gnuplot\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'	cout << "Export GNUPLOT file" << endl;\n');
fprintf(fid,'        sys.export_gnuplot ( state );\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	Summary\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'                                     	cout << "" << endl;\n');
fprintf(fid,'                                     	cout << "***********************************************" << endl;\n');
fprintf(fid,'                                     	cout << "** COMPILED WITH OPTIONS                     **" << endl;\n');
fprintf(fid,'                                     	cout << "***********************************************" << endl;\n');
fprintf(fid,'if ( METHOD == LAGRANGE)            {	cout << "** Dynamic equations ===> LAGRANGE           **" << endl;	}\n');
fprintf(fid,'else 	if ( METHOD == VIRTUAL_POWER) {	cout << "** Dynamic equations ===> VIRTUAL_POWER      **" << endl;	}\n');
fprintf(fid,'if ( ORDER == CMO)                  {	cout << "** Matrix Order      ===> Col_MO             **" << endl;	}\n');
fprintf(fid,'else 	if ( ORDER == RMO)            {	cout << "** Matrix Order      ===> Row_MO             **" << endl;	}\n');
fprintf(fid,'if ( MAPLE == MAPLE_OFF)            {	cout << "** Maple             ===> OFF                **" << endl;	}\n');
fprintf(fid,'else 	if ( MAPLE == MAPLE_ON)       {	cout << "** Maple             ===> ON                 **" << endl;	}\n');
fprintf(fid,'                                     	cout << "***********************************************" << endl;\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'//	END program\n');
fprintf(fid,'// ************************************************************************************************\n');
fprintf(fid,'\n');
fprintf(fid,'return 0;\n');
fprintf(fid,'\n');
fprintf(fid,'}\n');

fclose(fid);



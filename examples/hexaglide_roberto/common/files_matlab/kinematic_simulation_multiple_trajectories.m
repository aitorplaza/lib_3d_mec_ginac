%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
addpath('./lin_alg/');
addpath('./../../GENERATED_files_matlab/');
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
warning('OFF','all');
USER_defines;
Init_variables_parameters;
COORD='COORD_DEP';
SIZE='DDL';
INTEG='EULER';
LIN='INV';
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

t_ini=0.0;
delta_t = pi/200.0;
t_end = 2*pi;

NTRAJ=12;

for traj_number=1:NTRAJ

	fprintf('Computing trajectory number %d.\n',traj_number);
	
	Init_variables_parameters;

	switch traj_number

		case 1,		s2='TRAJ_NLCONS6_COND_ml_m539_cond_0167_detmax_0520_tr_298910777_F';	kval=1.00;	% Estimation
		case 2,		s2='TRAJ_NLCONS6_COND_ml_m437_cond_0304_detmax_0421_tr_20381385_F';	kval=1.00;	% Estimation
		case 3,		s2='TRAJ_NLCONS6_COND_ml_m478_cond_0160_detmax_0461_tr_98731481_F';	kval=1.00;	% Estimation
		case 4,		s2='TRAJ_NLCONS6_COND_ml_m486_cond_0159_detmax_0468_tr_69755171_F';	kval=1.00;	% Estimation
		case 5,		s2='TRAJ_NLCONS6_COND_ml_m486_cond_0202_detmax_0468_tr_148783919_F';	kval=1.00;	% Estimation
		case 6,		s2='TRAJ_NLCONS6_COND_ml_m494_cond_0193_detmax_0476_tr_121328823_F';	kval=1.00;	% Estimation
		case 7,		s2='TRAJ_NLCONS6_COND_ml_m503_cond_0160_detmax_0484_tr_192616316_F';	kval=1.00;	% Estimation
		case 8,		s2='TRAJ_NLCONS6_COND_ml_m506_cond_0185_detmax_0488_tr_84147133_F';	kval=1.00;	% Estimation
		case 9,		s2='TRAJ_NLCONS6_COND_ml_m508_cond_0179_detmax_0488_tr_529351375_F';	kval=1.00;	% Estimation
		case 10,	s2='TRAJ_NLCONS6_COND_ml_m514_cond_0192_detmax_0496_tr_280196961_F';	kval=1.00;	% Estimation
		case 11,	s2='TRAJ_NLCONS6_COND_ml_m521_cond_0170_detmax_0503_tr_151030222_F';	kval=1.00;	% Estimation
		
		case 12,	s2='TRAJ_NLCONS6_COND_ml_m388_cond_1237_detmax_0376_tr_1740802_F';	kval=1.00;	% Validation


		otherwise
				disp('Error en la funcion objetivo al tomar el criterio')
				pause
	end
	
	s1='load ';
	s3='.txt;';
	s4='c=';
	s5=';';
	
%  	[s1,s2,s3]
%  	[s4,s2,s5]
	
	eval([s1,s2,s3]);	% load TRAJ_NLCONS3_COND_1103.txt;
	eval([s4,s2,s5]);	% c=TRAJ_NLCONS3_COND_1103;


	%  t_end=c( 1);
	FS001=kval*c( 2);
	FSa11=kval*c( 3);
	FSb11=kval*c( 4);
	FSa21=kval*c( 5);
	FSb21=kval*c( 6);
	FS002=kval*c( 7);
	FSa12=kval*c( 8);
	FSb12=kval*c( 9);
	FSa22=kval*c(10);
	FSb22=kval*c(11);
	FS003=kval*c(12);
	FSa13=kval*c(13);
	FSb13=kval*c(14);
	FSa23=kval*c(15);
	FSb23=kval*c(16);
	FS004=kval*c(17);
	FSa14=kval*c(18);
	FSb14=kval*c(19);
	FSa24=kval*c(20);
	FSb24=kval*c(21);
	FS005=kval*c(22);
	FSa15=kval*c(23);
	FSb15=kval*c(24);
	FSa25=kval*c(25);
	FSb25=kval*c(26);
	FS006=kval*c(27);
	FSa16=kval*c(28);
	FSb16=kval*c(29);
	FSa26=kval*c(30);
	FSb26=kval*c(31);

	Position_velocity_acceleration; %% Simulacion cinematica

	global DOF;
	global NPTS;

	OPTIM_defines;

	% number of degrees of freedom
	dof=DOF;

	% number of trajectory points
	npts=NPTS;


	%  Cálculo de la matriz W
	reduciendo=true;	optimizando=false;
	W_evaluation;
	
	s11=num2str(traj_number);
	s12='save W_';
	s13=' W_';
	s14=';';
	
	s15='!cp W_';
	s16='.mat ./model_reduction/';
	s17='=Wb;';
	
%  	[s13,s11,s17]
%  	[s12,s11,s13,s11,s14]
%  	[s15,s11,s16]
	
	eval([s13,s11,s17])		% W_1=Wb;
%  	eval([s12,s11,s13,s11,s14]);	% save W_1 W_1;
%  	eval([s15,s11,s16]);		% !cp W_1.mat ./model_reduction/
	
end

%  return

W_estimation=[];

W_estimation=[W_estimation;W_1];
W_estimation=[W_estimation;W_2];
W_estimation=[W_estimation;W_3];
W_estimation=[W_estimation;W_4];
W_estimation=[W_estimation;W_5];
W_estimation=[W_estimation;W_6];
W_estimation=[W_estimation;W_7];
W_estimation=[W_estimation;W_8];
W_estimation=[W_estimation;W_9];
W_estimation=[W_estimation;W_10];
W_estimation=[W_estimation;W_11];

W_validation=W_12;

save W_estimation W_estimation
save W_validation W_validation

!mv W_estimation.mat ./model_reduction
!mv W_validation.mat ./model_reduction


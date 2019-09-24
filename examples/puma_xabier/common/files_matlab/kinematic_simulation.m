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

for i=0:1

	%  estimation = 1 for estimation trajectories
	%  estimation = 0 for validation trajectories
	estimation=i;

	if estimation
		%  Estimation trajectory
		load mytra_ml335.txt;
		c=mytra_ml335;
	else
		%  Validation trajectory
		load mytra_cond_12.txt;
		c=mytra_cond_12;
	end

	%  t_end=c( 1);
	FS001=c( 2);
	FSa11=c( 3);
	FSb11=c( 4);
	FSa21=c( 5);
	FSb21=c( 6);
	FSa31=c( 7);
	FSb31=c( 8);
	FSa41=c( 9);
	FSb41=c(10);
	FS002=c(11);
	FSa12=c(12);
	FSb12=c(13);
	FSa22=c(14);
	FSb22=c(15);
	FSa32=c(16);
	FSb32=c(17);
	FSa42=c(18);
	FSb42=c(19);
	FS003=c(20);
	FSa13=c(21);
	FSb13=c(22);
	FSa23=c(23);
	FSb23=c(24);
	FSa33=c(25);
	FSb33=c(26);
	FSa43=c(27);
	FSb43=c(28);
	FS004=c(29);
	FSa14=c(30);
	FSb14=c(31);
	FSa24=c(32);
	FSb24=c(33);
	FSa34=c(34);
	FSb34=c(35);
	FSa44=c(36);
	FSb44=c(37);
	FS005=c(38);
	FSa15=c(39);
	FSb15=c(40);
	FSa25=c(41);
	FSb25=c(42);
	FSa35=c(43);
	FSb35=c(44);
	FSa45=c(45);
	FSb45=c(46);
	FS006=c(47);
	FSa16=c(48);
	FSb16=c(49);
	FSa26=c(50);
	FSb26=c(51);
	FSa36=c(52);
	FSb36=c(53);
	FSa46=c(54);
	FSb46=c(55);

	
	Position_velocity_acceleration; %% Simulacion cinematica

	figure,plot(t_all,q_all)

	global DOF;
	global NPTS;

	OPTIM_defines;

	% number of degrees of freedom
	dof=DOF;

	% number of trajectory points
	npts=NPTS;


	%  Cálculo de la matriz W
	W_evaluation;

	if estimation
		W_estimation=Wb;
		save W_estimation W_estimation;
		!cp W_estimation.mat ./model_reduction/
	else
		W_validation=Wb;
		save W_validation W_validation;
		!cp W_validation.mat ./model_reduction/
	end

end
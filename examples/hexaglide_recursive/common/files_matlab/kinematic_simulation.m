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

%  estimation = 1 for estimation trajectories
%  estimation = 0 for validation trajectories
for estimation=0:1

	if estimation
		%  Estimation trajectory
%  		load TRAJ_ML_ml_m076_cond_45ala18.txt;
%  		c=TRAJ_ML_ml_m076_cond_45ala18;
		
		load TRAJ_NLCONS3_COND_1103.txt;
		c=TRAJ_NLCONS3_COND_1103;
	else
		%  Validation trajectory
%  		load TRAJ_ML_ml_m070_cond_25ala18.txt;
%  		c=TRAJ_ML_ml_m070_cond_25ala18;
		
		load TRAJ_NLCONS3_COND_1215.txt;
		c=TRAJ_NLCONS3_COND_1215;
	end

	%  t_end=c( 1);
	FS001=c( 2);
	FSa11=c( 3);
	FSb11=c( 4);
	FSa21=c( 5);
	FSb21=c( 6);
	FS002=c( 7);
	FSa12=c( 8);
	FSb12=c( 9);
	FSa22=c(10);
	FSb22=c(11);
	FS003=c(12);
	FSa13=c(13);
	FSb13=c(14);
	FSa23=c(15);
	FSb23=c(16);
	FS004=c(17);
	FSa14=c(18);
	FSb14=c(19);
	FSa24=c(20);
	FSb24=c(21);
	FS005=c(22);
	FSa15=c(23);
	FSb15=c(24);
	FSa25=c(25);
	FSb25=c(26);
	FS006=c(27);
	FSa16=c(28);
	FSb16=c(29);
	FSa26=c(30);
	FSb26=c(31);

	Position_velocity_acceleration; %% Simulacion cinematica

	%plot(t_all,q_all)

	figure,plot(t_all,q_all(:,[19:24]))
	title('posiciones actuadores')
	figure,plot(t_all,dq_all(:,[19:24]))
	title('velocidades actuadores')
	figure,plot(t_all,ddq_all(:,[19:24]))
	title('aceleraciones actuadores')
	
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

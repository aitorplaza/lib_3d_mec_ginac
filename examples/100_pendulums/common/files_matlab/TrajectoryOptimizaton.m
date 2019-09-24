%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
addpath('./lin_alg/');
addpath('./../../GENERATED_files_matlab/');
on=1;off=0;
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
warning('OFF','all');

%  Random (date dependent) initialization of the Random number generator
rng('shuffle');

% This function creates multiple trajectories starting each iteration from a randomly obtained different starting point.
while true

	k0=pi/2;
	FS001=k0*rand(1,1);
	FS002=k0*rand(1,1);
	FS003=k0*rand(1,1);
	FS004=k0*rand(1,1);
	FS005=k0*rand(1,1);
	FS006=k0*rand(1,1);

	k1=pi/8;
	FSa11=k1*rand(1,1);
	FSb11=k1*rand(1,1);
	FSa12=k1*rand(1,1);
	FSb12=k1*rand(1,1);
	FSa13=k1*rand(1,1);
	FSb13=k1*rand(1,1);
	FSa14=k1*rand(1,1);
	FSb14=k1*rand(1,1);
	FSa15=k1*rand(1,1);
	FSb15=k1*rand(1,1);
	FSa16=k1*rand(1,1);
	FSb16=k1*rand(1,1);
	
	k2=pi/8;
	FSa21=k2*rand(1,1);
	FSb21=k2*rand(1,1);
	FSa22=k2*rand(1,1);
	FSb22=k2*rand(1,1);
	FSa23=k2*rand(1,1);
	FSb23=k2*rand(1,1);
	FSa24=k2*rand(1,1);
	FSb24=k2*rand(1,1);
	FSa25=k2*rand(1,1);
	FSb25=k2*rand(1,1);
	FSa26=k2*rand(1,1);
	FSb26=k2*rand(1,1);

	k3=pi/8;
	FSa31=k3*rand(1,1);
	FSb31=k3*rand(1,1);
	FSa32=k3*rand(1,1);
	FSb32=k3*rand(1,1);
	FSa33=k3*rand(1,1);
	FSb33=k3*rand(1,1);
	FSa34=k3*rand(1,1);
	FSb34=k3*rand(1,1);
	FSa35=k3*rand(1,1);
	FSb35=k3*rand(1,1);
	FSa36=k3*rand(1,1);
	FSb36=k3*rand(1,1);

	k4=pi/8;
	FSa41=k4*rand(1,1);
	FSb41=k4*rand(1,1);
	FSa42=k4*rand(1,1);
	FSb42=k4*rand(1,1);
	FSa43=k4*rand(1,1);
	FSb43=k4*rand(1,1);
	FSa44=k4*rand(1,1);
	FSb44=k4*rand(1,1);
	FSa45=k4*rand(1,1);
	FSb45=k4*rand(1,1);
	FSa46=k4*rand(1,1);
	FSb46=k4*rand(1,1);

        c=[FS001;FSa11;FSb11;FSa21;FSb21;FSa31;FSb31;FSa41;FSb41;...
	       FS002;FSa12;FSb12;FSa22;FSb22;FSa32;FSb32;FSa42;FSb42;...
	       FS003;FSa13;FSb13;FSa23;FSb23;FSa33;FSb33;FSa43;FSb43;...
           FS004;FSa14;FSb14;FSa24;FSb24;FSa34;FSb34;FSa44;FSb44;...
           FS005;FSa15;FSb15;FSa25;FSb25;FSa35;FSb35;FSa45;FSb45;...
           FS006;FSa16;FSb16;FSa26;FSb26;FSa36;FSb36;FSa46;FSb46];


%    try
	tic
	mainOptimW(c);
	disp('TIEMPO NECESARIO PARA LA RESOLUCION DEL PROBLEMA')
	toc
%    catch
%    	disp('HA HABIDO UN ERROR EN LA OPTIMIZACION')
%    end

end

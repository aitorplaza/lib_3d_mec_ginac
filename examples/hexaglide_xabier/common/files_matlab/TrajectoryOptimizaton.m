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

	k0=0.25;
	FS001=1.5+k0*(rand(1,1)-0.5);
	FS002=1.5+k0*(rand(1,1)-0.5);
	FS003=1.5+k0*(rand(1,1)-0.5);
	FS004=1.5+k0*(rand(1,1)-0.5);
	FS005=1.5+k0*(rand(1,1)-0.5);
	FS006=1.5+k0*(rand(1,1)-0.5);

	k1=0.05;
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
	
	k2=0.05;
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

        c=[FS001;FSa11;FSb11;FSa21;FSb21;...
        FS002;FSa12;FSb12;FSa22;FSb22;...
        FS003;FSa13;FSb13;FSa23;FSb23;...
        FS004;FSa14;FSb14;FSa24;FSb24;...
        FS005;FSa15;FSb15;FSa25;FSb25;...
        FS006;FSa16;FSb16;FSa26;FSb26];


%    try
	tic
	mainOptimW(c);
	disp('TIEMPO NECESARIO PARA LA RESOLUCION DEL PROBLEMA')
	toc
%    catch
%    	disp('HA HABIDO UN ERROR EN LA OPTIMIZACION')
%    end

end

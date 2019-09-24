function value=fobjetivo(c1,criterio)

USER_defines;
Init_variables_parameters;
COORD='COORD_DEP';
SIZE='DDL';
INTEG='EULER';
LIN='INV';

global DOF;
global NPTS;

OPTIM_defines;


% number of degrees of freedom
dof=DOF;

% number of trajectory points
npts=NPTS;

FS001=c1( 1);
FSa11=c1( 2);
FSb11=c1( 3);
FSa21=c1( 4);
FSb21=c1( 5);
FS002=c1( 6);
FSa12=c1( 7);
FSb12=c1( 8);
FSa22=c1( 9);
FSb22=c1(10);
FS003=c1(11);
FSa13=c1(12);
FSb13=c1(13);
FSa23=c1(14);
FSb23=c1(15);
FS004=c1(16);
FSa14=c1(17);
FSb14=c1(18);
FSa24=c1(19);
FSb24=c1(20);
FS005=c1(21);
FSa15=c1(22);
FSb15=c1(23);
FSa25=c1(24);
FSb25=c1(25);
FS006=c1(26);
FSa16=c1(27);
FSb16=c1(28);
FSa26=c1(29);
FSb26=c1(30);



%  % Independent q,dq,ddq of the trajectory defined by coeff
%  dt=[0:1/(npts-1.0):1];
%  [QindN,dQindN,ddQindN,dddQindN] = FourierSeries(coeff,dt,dof);

% The mount boolean variable checks if the kinematic simulation is possible
mount=true;
try
	Position_velocity_acceleration; %% Simulacion cinematica
catch
	mount=false;
end


if mount==false
	if OPTIMIZATION_CRITERION==1;
		value=	10^3;
	elseif OPTIMIZATION_CRITERION==2;
		value=  10^30;
	else
		disp('Numero de criterio de optimizacion incorrecto')
		pause
	end

else
	optimizando=true;	reduciendo=false;
	W_evaluation;


%  	Weq=equilibrate(Wb);
	Weq=Wb;

	% The objective function to minimize is the following
	switch criterio
		case 1,
			% Maximum likelihood
			M=Wb'*Wb;
			[Meq,col,row]=equilibrate(M);
			ml=-log(det(Meq))-sum(log(col))-sum(log(row));
%  			disp('valor de ml para esta evaluacion de fobjetivo es')
%  			ml
%  
%  			disp('el tiempo de una evaluacion es:')
%  			toc
%  			tic
			if isnan(ml)
				value=	10^3;
				return
			end
			value=ml;

		case 2,
			% Condition Number
			[Meq,col,row]=equilibrate(Wb);
			con=cond(Meq);
			if isnan(con)
				value=  10^4;
				return
			end
			value=con;
		case 3,
			% Criteria 3
			M=Weq'*Weq;
			detmax=-log(det(M)/max(max(M)));
			if isnan(detmax)
				value=  10^3;
				return
			end
			value=detmax;
		case 4,
			% Criteria 4
			M=Weq'*Weq;
			tr=trace(M);
			if isnan(tr)
				value=10^30
				return
			end
			value=tr;
		otherwise
			disp('Error en la funcion objetivo al tomar el criterio')
			pause
		end
end



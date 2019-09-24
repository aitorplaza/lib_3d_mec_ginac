function [C,Ceq]=nolinear_cons(c1);

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


% The mount boolean variable checks if the kinematic simulation is possible
mount=true;
try
	Position_velocity_acceleration; %% Simulacion cinematica
catch
	mount=false;
end

%  number of constraint equations
%  6 to avoid the bars to be aligned with the platform
sing_neq=6;

%  1 to avoid the center of the platform go out of the fixed hexagon (to simplify: go out of a circle)
rad_neq=1;

% Building the nonlinear constrains
if mount==false

	C=10*ones((sing_neq+rad_neq)*npts,1);
else

%  	-----------------------------------
%  		VECTORIZED MODE
%  	-----------------------------------

	ncons=0;

%  	---------------------------------------------------------
%  	Nonlinear Constraints for the platform and the bars
%  	not to be in the same plane
	% Bound for the angle
	bound=cos(pi/2.0-15.0*pi/180.0);

	% one by one step
	for i=1:npts
		C(sing_neq*(i-1)+1:sing_neq*i,1)=NolinPhi(q_all(i,:),dq_all(i,:),ddq_all(i,:));
	end
	
%  	% all time steps together
%  	C=NolinPhi_(q_all,dq_all,ddq_all);
%  %  	C=NolinPhi2_(0,param',q_all,dq_all,ddq_all);

	d=size(C,1);
	C=bound*ones(d,1)-C;

	ncons=d;


%  %  	---------------------------------------------------------
%  %  	Nonlinear Constraints for the bars not to move out
%  %  	of the fixed platform polygon
%  %  	% for each time point
%  	margin_angle=5.0*pi/180.0;
%  	
%  	a=q_all(:,7:12);
%  	amax= a-(pi/2-margin_angle)*ones(size(a));
%  	amin=-a-(pi/2-margin_angle)*ones(size(a));
%  	
%  	b=q_all(:,13:18);
%  	bmin=-b+margin_angle*ones(size(b));
%  
%  	% columnify the columns of amax, amin, bmin
%  	amax=amax(:);
%  	amin=amin(:);
%  	bmin=bmin(:);
%  
%  	C(ncons+1:ncons+size(amax,1)+size(amin,1)+size(bmin,1))=[amax;amin;bmin];
	
	
%  	---------------------------------------------------------
%  	Nonlinear Constraints for the platform not to move out
%  	of the fixed platform polygon (circumscribed circle)
%  	% for all time points
	xx=q_all(:,1);
	yy=q_all(:,2);
	
	global R r;
	C(ncons+1:ncons+size(q_all,1))=xx.^2+yy.^2-ones(size(q_all,1),1)*((R-r)*0.9)^2;
	

end


Ceq=[];



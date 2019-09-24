% This procedure concerns the calculation of the linear inequality constrains for a DOF degrees of freedom mechanisms with NH harmonics
function [A,B]=linear_cons(p);

global DOF;
global NH;
global t_end;

global LBC_C;
global UBC_C;
global LBC_V;
global UBC_V;

% coeff     Vector of coefficients (the unknowns vector)
%           [tmax,q10,a11,b11,a12,b12,...,a1m,b1m,q20,a21,b21,...]
%           tmax is the duration of a period of the Fourier series.

% 12:12:2007 Xabier Iriarte
% ---------------------------------------------------
% ---------------------------------------------------


% Procedure parameters
	%---------------------------------------
	dof=DOF;	% actuators
	b=2.0;		% bounds
	%p=75.0;	% points
	h=NH;		% harmonics
	tmax=t_end;	% Trajectory duration
	%---------------------------------------
	f=1.0/tmax;	% fundamental frequency
	pa=(2*h+1)*dof;% total parameters
	%---------------------------------------
%  	LBC_C=0.514+0.20*(0.794-0.514);	%LBC_C=0.514;	% Lower boundary condition for actuator displacement
%  	UBC_C=0.794-0.20*(0.794-0.514); %UBC_C=0.794;	% Upper boundary condition for actuator displacement
%  	LBC_V=-0.100;	% Lower boundary condition for actuator velocity	the real minimum limit is -0.125
%  	UBC_V=0.100;	% Upper boundary condition for actuator velocity	the real maximum limit is 0.125
	%---------------------------------------


% CONSTRAINS FOR ACTUATORS
% -------------------------------------
% A1: matrix of the actuator displacement constrains for all times
A1=zeros(dof*b*p,pa);
% A2: matrix of the actuator velocity constrains for all times
A2=zeros(dof*b*p,pa);

% for each time point
for i=1:p
	% Set the time (t) for the current point i
	t=(tmax/p)*(i-1);

	% for each actuator
	for j=1:dof

		% for each boundary condition
		for k=1:b	% k=1 -> LBC	k=2 -> UBC
			% The qi0 coefficients
			A1(b*dof*(i-1)+b*(j-1)+k,(2*h+1)*(j-1)+1)=(2*k-3)*1;

			% for each harmonic
			for l=1:h
				% The aij coefficients of the Fourier series of the displacements
				A1(b*dof*(i-1)+b*(j-1)+k,(2*h+1)*(j-1)+2*(l-1)+2)=(2*k-3)*(sin(2*pi*f*l*t))/(2*pi*f*l);
				% The bij coefficients of the Fourier series
				A1(b*dof*(i-1)+b*(j-1)+k,(2*h+1)*(j-1)+2*(l-1)+3)=(2*k-3)*(-cos(2*pi*f*l*t))/(2*pi*f*l);

				% The aij coefficients of the Fourier series of the velocities
				A2(b*dof*(i-1)+b*(j-1)+k,(2*h+1)*(j-1)+2*(l-1)+2)=(2*k-3)*(cos(2*pi*f*l*t));
				% The bij coefficients of the Fourier series
				A2(b*dof*(i-1)+b*(j-1)+k,(2*h+1)*(j-1)+2*(l-1)+3)=(2*k-3)*(sin(2*pi*f*l*t));

			end
		end
	end
end

% B1: RHS vector of the actuator displacement constrains for all times
B1=zeros(dof*b*p,1);
% B2: RHS vector of the actuator velocity constrains for all times
B2=zeros(dof*b*p,1);

% for each time point
for i=1:p
	% for each actuator
	for j=1:dof
	% k=1 -> LBC	k=2 -> UBC
		% For displacements
		B1(b*dof*(i-1)+b*(j-1)+1,1)=-LBC_C;
		B1(b*dof*(i-1)+b*(j-1)+2,1)= UBC_C;
		% For velocities
		B2(b*dof*(i-1)+b*(j-1)+1,1)=-LBC_V;
		B2(b*dof*(i-1)+b*(j-1)+2,1)= UBC_V;
	end
end


% Total matrix creation
A=[A1;A2;];
B=[B1;B2;];


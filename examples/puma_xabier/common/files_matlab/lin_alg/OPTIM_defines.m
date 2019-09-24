
% Optimizaton Criterion
% 1 = maximum likelihood function of W
% 2 = condition number of W
global OPTIMIZATION_CRITERION;
OPTIMIZATION_CRITERION=2;

global DOF;
DOF=6;

global NH;
NH=4;

global NPTS;
global n_points;
NPTS=n_points;

% Boundary conditions for the actuators
global LBC_C;
global UBC_C;
global LBC_V;
global UBC_V;

%---------------------------------------
LBC_C= -8*pi/10;	% Lower boundary condition for actuator displacement
UBC_C=  8*pi/10;	% Upper boundary condition for actuator displacement
LBC_V=-1.0;	% Lower boundary condition for actuator velocity
UBC_V= 1.0;	% Upper boundary condition for actuator velocity
%---------------------------------------
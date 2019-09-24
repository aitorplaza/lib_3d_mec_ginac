global t;
t_ini=0.0;
%  delta_t = 0.05;
delta_t = pi/50.0;
global t_end;
t_end = 2*pi;
n_intervals=floor(t_end/delta_t);
global n_points;
n_points=length(t_ini:delta_t:t_end);


NEWTON_RAPHSON_TOLERANCE = 1.0e-8;
NEWTON_RAPHSON_RELAXATION = 1.0;%0.2;
NEWTON_RAPHSON_MAX_ITER = 200;
NUM_NR_ITER=1;
TRAPEZOIDAL_TOLERANCE = 1.0e-8;
%TRAPEZOIDAL_TOLERANCE = 1.0e-3; % limite error para euler mejorado = trapezoidal

lambda = 0.0;
alfa = 1.0e+16;

%TIME='ON'
TIME='OFF';

on=1;
off=0;

SIZE='EMPTY';




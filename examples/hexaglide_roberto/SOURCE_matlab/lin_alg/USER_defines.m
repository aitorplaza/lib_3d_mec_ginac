global t;
t_ini=0.0;
delta_t = 0.001;
t_end = 0.1;
n_intervals=(t_end/delta_t);
n_points=n_intervals+1;

NEWTON_RAPHSON_TOLERANCE = 1.0e-8;
TRAPEZOIDAL_TOLERANCE = 1.0e-8;
%TRAPEZOIDAL_TOLERANCE = 1.0e-3; % limite error para euler mejorado = trapezoidal

lambda = 0.0;
alfa = 1.0e+12;
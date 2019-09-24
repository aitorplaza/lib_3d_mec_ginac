
global q;
global dq;
global ddq;
global param;
global unknowns;
global inputs;

time_init;	% Se define el valor del tiempo (t)
param_init;     % Se definen valores de parametros (pi, longitudes, masas, Inercias, c, k, ....)
coord_init;     % Se definen los nombres de todas las coord. Se les asignan valores iniciales.
vel_init;       % Se definen los nombres de todas las veloc. Se les asignan valores iniciales.
acc_init;       % Se definen los nombres de todas las acele. Se les asignan valores iniciales.
unknowns_init;  % Se definen los nombres de todas las fuerzas de enlace. Se les asignan valores iniciales.
%inputs_init;  	% Se definen los nombres de todas los inputs. Se les asignan valores iniciales.

param_vect_init; 	% Se define el vector param(n_param,1), y que lugar ocupa cada param dentro de ese vector. 
coord_vect_init;    % Se define el vector q(n_gen_coord,1), y que lugar ocupa cada coord. dentro de ese vector.  
vel_vect_init;      % Se define el vector dq(n_gen_vel,1), y que lugar ocupa cada vel. dentro de ese vector.  
acc_vect_init;      % Se define el vector ddq(n_gen_vel,1), y que lugar ocupa cada acc. dentro de ese vector.  
unknowns_vect_init; % Se define el vector unknowns(n_unknowns,1) de las fuerzas de enlace.
%inputs_vect_init; 	% Se define el vector inputs(n_inputs,1) de los inputs.

n_param     = length(param);
n_gen_coord = length(q);
n_gen_vel   = length(dq);
n_gen_acc   = length(ddq);
n_unknowns  = length(unknowns);
n_inputs    = length(inputs);

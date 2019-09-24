//initialize variables
var_init();

//initialize generalized coordinate, velocity and acceleration vectors
gen_coord_vect_init();
gen_vel_vect_init();
gen_accel_vect_init();

param_vect_init();

//initialize joint force unknowns
unknowns_vect_init();
inputs_vect_init();

Phi();
Phi_q();
Beta();
dPhi_dq();

PhiInit();
PhiInit_q();
dPhiInit_dq();
BetaInit();

Qgamma();
MXdPhi_dqZero();
Energy();




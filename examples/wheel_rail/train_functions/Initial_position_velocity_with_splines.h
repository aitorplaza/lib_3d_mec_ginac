extern void Initial_position_velocity_with_splines (double * q, double * s,  double *dq, double * ds, double * param);
extern int  Solve_N_R_while_with_splines(int N, int M, double * (* Vector_Eq)(), double * (* Matrix_Jac)(), double * Vector, double * Inverse, double * delta, double * param, double * BufferJT,double * BufferAUXCols, double * BufferAUXRows, double * BufferIAUXCols, double * BufferIAUXRows, int * p_vector, int * q_vector, double * BufferL, double * BufferPINV);


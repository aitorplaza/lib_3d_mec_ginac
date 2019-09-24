extern void Vect_Print    (int, double * Vector);
extern void Mat_Print     (int, int, double * Matrix);
extern void Mat_Vect_Mult (int, int, double * Matrix, double * Vector, int, double * Ans);
extern void Mat_Mat_Mult  (int, int, int, double * Mat1, double * Mat2, int, double * Ans);
extern void Mat_Trasp     (int, int, double * Mat, double * Mat_T);

extern int Mat_Inv  (int, double * J, double * InvJ);
extern int Mat_PInv (int, int, double * J, double * PInvJ);

extern int Solve_N_R       (int, int, double * Eq, double * Jac, double * Vector, double * PInv_Jac);
extern int Solve_N_R_while (int N, double * (* PhiInit)(), double * (* PhiInit_q)(), double * Vector, double * Inverse);
extern int Solve_N_R_for   (int N, double * (* PhiInit)(), double * (* PhiInit_q)(), double * Vector, int, double * Inverse);

extern int chol(int N, double * A, double * L);
extern int ldl(int N, double * A, double * L, double * D);
extern int forward_substitution(int N, double * L, double * b, double * y);
extern int backward_substitution(int N, double * U, double * y, double * x);

extern int solve_lin_sys_chol(int N, double * A, double * b, double * x);
extern int solve_lin_sys_chol_matrix(int Cols_A, double * A, int Cols_B, double * B, double * X);

extern int solve_lin_sys_ldl(int N, double * A, double * b, double * x);
extern int solve_lin_sys_ldl_matrix(int Cols_A, double * A, int Cols_B, double * B, double * X);

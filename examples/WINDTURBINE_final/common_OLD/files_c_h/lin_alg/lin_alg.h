extern void Vect_Print    (int, double * Vector);
extern void Vect_Print_Int  (int, int * Vector);
extern void Mat_Print     (int, int, double * Matrix);
extern void Mat_Vect_Mult (int, int, double * Matrix, double * Vector, int, double * Ans);
extern void Mat_Mat_Mult  (int, int, int, double * Mat1, double * Mat2, int, double * Ans);
extern void Mat_Trasp     (int, int, double * Mat, double * Mat_T);

extern int Mat_Inv  (int, double * J, double * InvJ, double * JAug);
extern int Mat_PInv (int, int, double * J, double * PInvJ, double * JT, double	* AUX_Cols, double	* AUX_Rows, double	* Inverse_AUX_Cols, double	* Inverse_AUX_Rows);

extern int Solve_N_R       (int, int, double * Eq, double * Jac, double * Vector, double * PInv_Jac, double * delta);
extern int Solve_N_R_while (int N, int M, double * (* PhiInit)(), double * (* PhiInit_q)(), double * Vector, double * Inverse, double * delta);
extern int Solve_N_R_for   (int N, int M, double * (* PhiInit)(), double * (* PhiInit_q)(), double * Vector, int, double * Inverse, double * delta);

extern int chol(int N, double * A, double * L);
extern int ldl(int N, double * A, double * L, double * D);
extern int lu(int N, double * M, double * LU, int * o, double * s, int niter);
extern int lupq(int Rows, int Cols, double * M, double * LU, int * p_vector, int * q_vector, int  niter);/*developed but not used*/
extern int Permute_Matrix_pq(int Rows, int Cols, double * LU, double * M, int * p_vector, int * q_vector);
extern int plu(int N, double * M, double * P, double * L, double * U); /* To be developed if required */

extern int forward_substitution(int N, double * L, double * b, double * y);
extern int backward_substitution(int N, double * U, double * y, double * x);
extern int forward_substitution_piv(int N, double * LU, int * o, double * b, double * y);
extern int backward_substitution_piv(int N, double * LU, int * o, double * y, double * x);
extern int forward_substitution_piv_pq(int N, double * LU, int * p_vector, int * q_vector, double * b, double * y);
extern int backward_substitution_piv_pq(int N, double * LU, int * p_vector, int * q_vector, double * y, double * x);

extern int solve_lin_sys_chol(int N, double * A, double * b, double * x, double * L, double * U, double * y);
extern int solve_lin_sys_chol_matrix(int Cols_A, double * A, int Cols_B, double * B, double * X, double * L, double * U, double * Y);

extern int solve_lin_sys_ldl(int N, double * A, double * b, double * x, double * L, double * U, double * d, double * y);
extern int solve_lin_sys_ldl_matrix(int Cols_A, double * A, int Cols_B, double * B, double * X, double * L, double * U, double * d, double * Y);

extern int solve_lin_sys_lu(int N, double * M, double * b, double * x, double * s, double * LU, double * y, int * o, int niter);
extern int solve_lin_sys_lu_matrix(int Cols_M, double * M, int Cols_B, double * B, double * X, double *s, double * LU, double * Y, int * o, int niter);

extern int solve_lin_sys_plu(int N, double * M, double * b, double * x); /* To be developed if required */
extern int solve_lin_sys_plu_matrix(int Cols_M, double * M, int Cols_B, double * B, double * X); /* To be developed if required */

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#include <stdio.h>
#include <math.h>
#include "lin_alg.h"
/*

VERY IMPORTANT

Matrixes are worked as vectors stored in CMO

*/

/* ********************************************************************************************* */
/* Vect_Print */ /* This function print a 1xJ vector - Not OK for Real Time */
/* ********************************************************************************************* */
void	Vect_Print	(int size ,double * Vector)
{
int 	j;
for (j=0; j<size; j++){
	printf(" %+.10f\n ",Vector[j]);
	}
printf(" \n\n");
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Print(START) */ /* This function print a IxJ matrix - Not OK for Real Time */
/* ********************************************************************************************* */
void	Mat_Print(int Rows, int Cols, double * Matrix)
{
int 	i, j;
for (i=0; i<Rows; i++){
	for (j=0; j<Cols; j++){
		printf(" %.10f ",Matrix[Rows*j+i]);
		}
	printf("\n");
	}
printf("\n\n");
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Vect_Mult */ /* This function multiplies Matxix(IxJ) X Vector(Jx1) = Ans(Ix1) */
/* ********************************************************************************************* */
void 	Mat_Vect_Mult(int Rows, int Cols, double * Matrix, double * Vector, int Scale, double * Ans)
{
int		i, j;
for (i=0; i<Rows; i++){
	Ans[i] = 0.0;
	for (j=0; j<Cols; j++){
		Ans[i] = Matrix[Rows*j+i] * Vector[j] + Ans[i];
		}
	Ans[i] = Ans[i] * Scale;
	}
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Mat_Mult */ /* This function multiplies Mat1(IxN) X Mat2(NxJ) = Ans(IxJ) */
/* ********************************************************************************************* */
void 	Mat_Mat_Mult(int Rows, int N, int Cols, double * Mat1, double * Mat2, int Scale, double * Ans)
{
int		i, j, k;
for (i=0; i<Rows; i++){
	for (j=0; j<Cols; j++){
		Ans[Rows*j+i] = 0.0;
		for	(k=0; k<N; k++){
			Ans[Rows*j+i] =  Mat1[Rows*k+i] * Mat2[N*j+k] + Ans[Rows*j+i];
			}
		Ans[Rows*j+i] = Ans[Rows*j+i] * Scale;
		}
	}
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Trasp */ /* This function trasposes a matrix */
/* ********************************************************************************************* */
void	Mat_Trasp(int Rows, int Cols, double * Mat, double * Mat_T)
{
int		i, j;
	for (j = 0; j < Cols; j++){
		for(i = 0; i < Rows; i++){Mat_T[j + i * Cols] = Mat[i + j * Rows];}
	}
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Inv */ /* This function inverts a N size matrix */
/* ********************************************************************************************* */
int 		Mat_Inv(int N, double * J, double * InvJ)
{
	double JAug[N*(N+N)], m, temp;
	int j, k, n;
	#define MAX_elim  1.0e-02
	#ifndef INV_TOL
		#define INV_TOL 1.0e-12
	#endif

	/* Augment the Identity matrix to the Jacobian matrix */
	for (j=0; j<N; ++j){				
		for (k=0; k<N; ++k){							/* Assign J matrix to first N columns of AugJ */
			JAug[j+k*N] = J[j+k*N];
 		}
		for(k=N; k<(2*N); ++k){							/* Assign I matrix to last N columns of AugJ */
			if (k-N == j){
				JAug[j+k*N]=1;
			}
			else{
				JAug[j+k*N]=0;
			}
		}
	}

	/* Perform Gauss elimination */
	for (k=0; k<(N-1); ++k){               				/* Pivot */
		if ((JAug[k+k*N]< MAX_elim) && (JAug[k+k*N] > -MAX_elim)){
			for (j=k+1;j<N; ++j){
				if ((JAug[j+k*N]>MAX_elim) || (JAug[j+k*N]<-MAX_elim)){
					for (n=0; n<(2*N);++n){
						temp = JAug[k+n*N];
						JAug[k+n*N] = JAug[j+n*N];
						JAug[j+n*N] = temp;
					}
				break;
				}
			}
		}
		for (j=k+1; j<N; ++j){            				/* Pivot */
			m = -JAug[j+k*N] / JAug[k+k*N];
			for (n=0; n<(2*N); ++n){
				JAug[j+n*N]=JAug[j+n*N] + m*JAug[k+n*N];	/* (Row j) + m * (Row k) */
				if ((JAug[j+n*N] < INV_TOL) && (JAug[j+n*N] > -INV_TOL)){
					JAug[j+n*N] = 0;
				}
 			}
		}
	}

	/* Normalization of Diagonal Terms */
	for (j=0; j<N; ++j){
		m=1/JAug[j+j*N];
		for(k=0; k<(2*N); ++k){
			JAug[j+k*N] = m * JAug[j+k*N];
		}
	}

	/* Perform Gauss Jordan Steps */
	for (k=(N-1); k>=0; --k){
		for(j=k-1; j>=0; --j){
			m = -JAug[j+k*N]/JAug[k+k*N];
			for (n=0; n<(2*N); ++n){
				JAug[j+n*N] = JAug[j+n*N] + m * JAug[k+n*N];
			}
		}
	}

	/* Assign last N columns of JAug to InvJ */
	for (j=0; j<N; ++j){
		for (k=0; k<N; ++k){
			InvJ[j+k*N] = JAug[j+(k+N)*N];
		}
	}
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* PInv */ /* This function returns pinv(Cols x Rows) of matrix (Rows x Cols) */
/* ********************************************************************************************* */
int 		Mat_PInv(int Rows, int Cols, double * J, double * PInvJ)
{
double		JT[Rows*Cols];
double		AUX_Cols[Cols*Cols], Inverse_AUX_Cols[Cols*Cols];
double		AUX_Rows[Rows*Rows], Inverse_AUX_Rows[Rows*Rows];

Mat_Trasp( Rows, Cols, J, JT);

if (Rows > Cols){
	Mat_Mat_Mult	(Cols, Rows, Cols, JT, J, 1, AUX_Cols);
	Mat_Inv				(Cols, AUX_Cols, Inverse_AUX_Cols);
	Mat_Mat_Mult	(Cols, Cols, Rows, Inverse_AUX_Cols, JT, 1, PInvJ);
	}

if (Rows < Cols){
	Mat_Mat_Mult	(Rows, Cols, Rows, J, JT, 1, AUX_Rows);
	Mat_Inv				(Rows, AUX_Rows, Inverse_AUX_Rows);
	Mat_Mat_Mult	(Cols, Rows, Rows, JT, Inverse_AUX_Rows, 1, PInvJ);
	}
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve_N_R(START) */
/* ********************************************************************************************* */
int			Solve_N_R(int Rows, int Cols, double * Eq, double * Jac, double * Vector, double * PInv_Jac)
{
int				i;
double	delta[Cols];
/*double	PInv_Jac[Cols*Rows];*/

if(Rows==Cols){Mat_Inv( Rows, Jac, PInv_Jac);}
if(Rows!=Cols){Mat_PInv( Rows, Cols, Jac, PInv_Jac);}
Mat_Vect_Mult(Cols, Rows, PInv_Jac, Eq, +1, delta);

for (i=0; i<Cols; i++) {					/* subtract delta from last iterations pos values */
	Vector[(i)] -= delta[i];			/* Re-calculate dep coord. */
	}
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/*  Solve_N_R_while */
/* ********************************************************************************************* */
int			Solve_N_R_while(int N, double * (* Vector_Eq)(), double * (* Matrix_Jac)(), double * Vector, double * Inverse)
{
int			iteration = 0, iterate = 1, i;
double		delta[N];
double		conv_err = 1.;

double	* _Vector_Eq;
double	* _Matrix_Jac;

#define MY_CONV_CRITERION		(1e-12) /* As eq have dim of mm^2 this implies an error of 10^-4mm */
#define FAIL_CONV_ITERATIONS	150
#define LARGE_CONV_ERROR		10000

#ifndef NEWTON_RAPHSON_TOLERANCE
#define NEWTON_RAPHSON_TOLERANCE 1.0e-16
#endif

double conv_criterion = NEWTON_RAPHSON_TOLERANCE;

while (iterate) {					/* check for large error and return error flag if no convergence */
	if ((conv_err > +LARGE_CONV_ERROR) || (conv_err < -LARGE_CONV_ERROR)) {		/* we can't converge */
		return -2;
	};

	iteration++;		/* check iteration to see if the kinematics can reach the convergence criteria */
	if (iteration > FAIL_CONV_ITERATIONS) {										/* we can't converge */
		return -5;
	}

	_Vector_Eq=Vector_Eq();
	_Matrix_Jac=Matrix_Jac();		

	Mat_Inv( N, _Matrix_Jac, Inverse);
	Mat_Vect_Mult(N, N, Inverse, _Vector_Eq, +1, delta);

	for (i=0; i<N; i++) {							/* subtract delta from last iterations pos values */
		Vector[(i)] -= delta[i];						/* Re-calculate dep coord. */
	}

	conv_err = 0.0;		
	for (i = 0; i < N; i++) {	/* determine value of conv_error (used to determine if no convergence) */
		conv_err += fabs(_Vector_Eq[i]);
	}

	iterate = 0;			/* assume iteration is done */
	for (i = 0; i < N; i++) {
		if (fabs(_Vector_Eq[i]) > conv_criterion) {				/* check if needs another iteration */
			iterate = 1;
		}
	}
}
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve_N_R_for */
/* ********************************************************************************************* */
int			Solve_N_R_for(int N, double * (* Vector_Eq)(), double * (* Matrix_Jac)(), double * Vector, int iterations, double * Inverse)
{
int				j, i;
double		delta[N];
double		conv_err = 1.;

double	* _Vector_Eq;
double	* _Matrix_Jac;

for (j = 0; j< iterations ; j++){

_Vector_Eq=Vector_Eq();
_Matrix_Jac=Matrix_Jac();		

	Mat_Inv( N, _Matrix_Jac, Inverse);
	Mat_Vect_Mult(N, N, Inverse, _Vector_Eq, +1, delta);
	for (i=0; i<N; i++) {					/* subtract delta from last iterations pos values */
		Vector[(i)] -= delta[i];			/* Re-calculate dep coord. */
	}
}
#ifdef DEBUG
conv_err = 0.0;		
for (i = 0; i < N; i++) {	/* determine value of conv_error (used to determine if no convergence) */
	conv_err += fabs(_Vector_Eq[i]);
}
#endif
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* chol */ /* Cholesky L (lower matrix) of A (real, symetric and definite positive) */
/* ********************************************************************************************* */
int chol(int N, double * A, double * L)
{
	int i, j, k, rows=N, cols=N;
  double aux;

for (i = 0; i< cols * rows ; i++){ L[i]=0.0;}

for (i = 0; i< cols ; i++){
  aux=0.0;
  for (k = 0; k< i ; k++){
    aux = aux + L[ i + k*rows ] * L[ i + k*rows ];
  }
  L[ i + i*rows ] = pow((A[ i + i*rows ] - aux),0.5);
  for (j = (i+1); j< rows ; j++){
    aux=0.0;
    for (k = 0; k< i ; k++){
      aux = aux + L[ i + k*rows ] * L[ j + k*rows ];
    }
    L[ j + i*rows ]=( A[ j + i*rows ] - aux ) / L[ i + i*rows ];
  }
}
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* ldl */ /* L (lower matrix) D (diagonal) of A (real, symetric and semi-definite positive) */
/* ********************************************************************************************* */
/* Diagonal Matrix D stored as vector D containing diagonal elements */
int ldl(int N, double * A, double * L, double * D)
{
	int i, j, k, rows=N, cols=N;
  double aux_D, aux_L;

for (i = 0; i< cols * rows ; i++){ 	L[i]=0.0;	}
for (i = 0; i< N ; i++){ 	D[i]=0.0;	}

for (i = 0; i< cols ; i++){
  aux_D=0.0;
  for (k = 0; k< i ; k++){
    aux_D = aux_D + L[ i + k*rows ] * L[ i + k*rows ] * D[ k ];
  }
  D[ i ] = A[ i + i*rows ] - aux_D;
  for (j = (i+1); j< rows ; j++){
    aux_L=0.0;
    for (k = 0; k< i ; k++){
      aux_L = aux_L + L[ j + k*rows ] * L[ i + k*rows ] * D[ k ];
    }
    L[ j + i*rows ]=( A[ j + i*rows ] - aux_L ) / D[ i ];
  }
  L[ i + i*rows]=1.0;
}
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* forward substitution */ /* L*y=b being L Lower Triangular ===> A*x=b ===> LU*x=b */
/* ********************************************************************************************* */
int forward_substitution(int N, double * L, double * b, double * y)
{
	int i, j, k, rows=N, cols=N;
  double aux;

for (i = 0; i< cols ; i++){ 	y[i]=0.0;	}

for (i = 0; i< rows ; i++){
  aux=0.0;
  for (j = 0; j< i ; j++){
    aux = aux + L[ i + j*rows] * y[j];    
  }
  y[i] = (b[i] - aux) / L[ i + i*rows];
}
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* backward substitution */ /* U*x=y being U Upper Triangular ===> A*x=b ===> LU*x=b */
/* ********************************************************************************************* */
int backward_substitution(int N, double * U, double * y, double * x)
{
	int i, j, k, rows=N, cols=N;
  double aux;

for (i = 0; i< cols ; i++){ 	x[i]=0.0;	}

for (i = rows-1; i>=0 ; i--){
  aux=0.0;
  for (j = cols-1; j>= i+1 ; j--){
    aux = aux + U[ i + j*rows] * x[j]; 
  }
  x[i] = (y[i] - aux) / U[ i + i*rows];
}
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system A*x=b, being A=sym and def pos */
/* ********************************************************************************************* */
int solve_lin_sys_chol(int N, double * A, double * b, double * x)
{
double L[N*N], U[N*N], y[N];

chol(N, A, L);
Mat_Trasp(N, N, L, U);

forward_substitution(N, L, b, y);
backward_substitution(N, U, y, x);
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system A*x=b, being A=sym and def pos */
/* ********************************************************************************************* */
int solve_lin_sys_ldl(int N, double * A, double * b, double * x)
{
double L[N*N], U[N*N], d[N], y[N];
int i;

ldl(N, A, L, d);
Mat_Trasp(N, N, L, U);

forward_substitution(N, L, b, y);
for (i = 0; i< N ; i++){ y[i] = y[i] / d[ i ]; }
backward_substitution(N, U, y, x);
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system A*X=B, being A=sym and def pos */
/* ********************************************************************************************* */
int solve_lin_sys_chol_matrix(int Cols_A, double * A, int Cols_B, double * B, double * X)
{
double L[ Cols_A * Cols_A ], U[ Cols_A * Cols_A ], Y[ Cols_A * Cols_B ];
int i;

chol(Cols_A, A, L);
Mat_Trasp(Cols_A, Cols_A, L, U);

for (i = 0; i< Cols_B ; i++){
	forward_substitution(Cols_A, L, &B[ i * Cols_A ], &Y[ i * Cols_A ]);
	backward_substitution(Cols_A, U, &Y[ i * Cols_A ], &X[ i * Cols_A ]);
}
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system A*X=B, being A=sym and def pos */
/* ********************************************************************************************* */
int solve_lin_sys_ldl_matrix(int Cols_A, double * A, int Cols_B, double * B, double * X)
{
double L[ Cols_A * Cols_A ], U[ Cols_A * Cols_A ], d[ Cols_A ], Y[ Cols_A * Cols_B ];
int i,j;

ldl(Cols_A, A, L, d);
Mat_Trasp(Cols_A, Cols_A, L, U);

for (i = 0; i< Cols_B ; i++){
	forward_substitution(Cols_A, L, &B[ i * Cols_A ], &Y[ i * Cols_A ]);
	for (j = 0; j< Cols_A ; j++){ 
		Y[ j + i * Cols_A ] = Y[ j + i * Cols_A ] / d[ j ];
	}
	backward_substitution(Cols_A, U, &Y[ i * Cols_A ], &X[ i * Cols_A ]);
}
return 0;												/* FIXME-- check divisors for 0 above */
}
/* ********************************************************************************************* */

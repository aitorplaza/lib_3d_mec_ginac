#include <stdio.h>
#include <math.h>
#include "lin_alg.h"
/*

VERY IMPORTANT

Matrixes are worked as vectors stored in CMO

*/


#ifdef MATLAB_MEX_FILE
 #define printf mexPrintf
#endif
#define PIV_TOL 1e-6

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
/* Vect_Print_int */ /* This function print a 1xJ vector of ints - Not OK for Real Time */
/* ********************************************************************************************* */
void	Vect_Print_Int	(int size ,int * Vector)
{
int 	j;
printf(" \n");
for (j=0; j<size; j++){
	printf("  %d \n",Vector[j]);
	}
printf("\n\n");
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
int 		Mat_Inv(int N, double * J, double * InvJ, double * JAug)
{
	/*double JAug[N*(N+N)];*/
  double m, temp;
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
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* PInv */ /* This function returns pinv(Cols x Rows) of matrix (Rows x Cols) */
/* ********************************************************************************************* */
int 		Mat_PInv(int Rows, int Cols, double * J, double * PInvJ, double * JT, double	* AUX_Cols, double	* AUX_Rows, double	* Inverse_AUX_Cols, double	* Inverse_AUX_Rows)
{
/*double		JT[Rows*Cols];*/
/*double		AUX_Cols[Cols*Cols], Inverse_AUX_Cols[Cols*Cols];*/
/*double		AUX_Rows[Rows*Rows], Inverse_AUX_Rows[Rows*Rows];*/
double Buffer[2*MAX(Rows,Cols)*MAX(Rows,Cols)];

Mat_Trasp( Rows, Cols, J, JT);

if (Rows > Cols){
	Mat_Mat_Mult	(Cols, Rows, Cols, JT, J, 1, AUX_Cols);
	Mat_Inv				(Cols, AUX_Cols, Inverse_AUX_Cols,Buffer);
	Mat_Mat_Mult	(Cols, Cols, Rows, Inverse_AUX_Cols, JT, 1, PInvJ);
	}

if (Rows < Cols){
	Mat_Mat_Mult	(Rows, Cols, Rows, J, JT, 1, AUX_Rows);
	Mat_Inv				(Rows, AUX_Rows, Inverse_AUX_Rows,Buffer);
	Mat_Mat_Mult	(Cols, Rows, Rows, JT, Inverse_AUX_Rows, 1, PInvJ);
	}
if (Rows == Cols){
	Mat_Inv				(Rows, AUX_Rows, PInvJ,Buffer);
	}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve_N_R(START) */
/* ********************************************************************************************* */
int			Solve_N_R(int Rows, int Cols, double * Eq, double * Jac, double * Vector, double * PInv_Jac, double * delta)
{
int				i;
/*double	delta[Cols];*/



/*double	PInv_Jac[Cols*Rows];*/

if(Rows==Cols){
    double Buffer[2*Rows*Rows];
    Mat_Inv( Rows, Jac, PInv_Jac, Buffer);}
else{
    double BufferJT[2*Rows*Cols];
    double BufferAUXCols[2*Cols*Cols];
    double BufferAUXRows[2*Rows*Rows];
    double BufferIAUXCols[2*Cols*Cols];
    double BufferIAUXRows[2*Rows*Rows];
    Mat_PInv( Rows, Cols, Jac, PInv_Jac, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows);}
Mat_Vect_Mult(Cols, Rows, PInv_Jac, Eq, +1, delta);

for (i=0; i<Cols; i++) {					/* subtract delta from last iterations pos values */
	Vector[(i)] -= delta[i];			/* Re-calculate dep coord. */
	}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/*  Solve_N_R_while */
/* ********************************************************************************************* */
int			Solve_N_R_while(int N, int M, double * (* Vector_Eq)(), double * (* Matrix_Jac)(), double * Vector, double * Inverse, double * delta)
{
int			iteration = 0, iterate = 1, i;
/*double		delta[M];*/
double		conv_err = 1.;
double	* _Vector_Eq;
double	* _Matrix_Jac;

double Buffer[2*N*N];
double BufferJT[2*N*M];
double BufferAUXCols[2*M*M];
double BufferAUXRows[2*N*N];
double BufferIAUXCols[2*M*M];
double BufferIAUXRows[2*N*N];

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

	if(N==M){
    Mat_Inv( N, _Matrix_Jac, Inverse, Buffer);}
     else{
    Mat_PInv( N, M, _Matrix_Jac, Inverse, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows);}
    
    Mat_Vect_Mult(M, N, Inverse, _Vector_Eq, +1, delta);

	for (i=0; i<M; i++) {							/* subtract delta from last iterations pos values */
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
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve_N_R_for */
/* ********************************************************************************************* */
int			Solve_N_R_for(int N, int M, double * (* Vector_Eq)(), double * (* Matrix_Jac)(), double * Vector, int iterations, double * Inverse, double * delta)
{
int				j, i;
/*double		delta[M];*/
double		conv_err = 1.;

double	* _Vector_Eq;
double	* _Matrix_Jac;

double Buffer[2*N*N];
double BufferJT[2*N*M];
double BufferAUXCols[2*M*M];
double BufferAUXRows[2*N*N];
double BufferIAUXCols[2*M*M];
double BufferIAUXRows[2*N*N];

for (j = 0; j< iterations ; j++){

_Vector_Eq=Vector_Eq();
_Matrix_Jac=Matrix_Jac();		

	if(N==M){
    Mat_Inv( N, _Matrix_Jac, Inverse, Buffer);}
     else{
    Mat_PInv( N, M, _Matrix_Jac, Inverse, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows);}

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
return 0;
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
return 0;
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
return 0;
}


/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* lu */ /* L (lower matrix) U (upper matrix) P(Permutation matrix) of M = P*U*L */
/* ********************************************************************************************* */
/*
int lu(int N, double * M, double * LU, int * o, double * s, int * niter)
{
	int i, j, k, p, tmpass, rows=N, cols=N;

  double big, dummy, factor;
  

for (i = 0; i < cols * rows ; i++){ 	LU[i]=M[i];}

for (i = 0; i < N ; i++){ 
	s[i]=fabs(LU[ i + 0*rows ]);
	for (j = 1; j < N ; j++){ 
		if (fabs(LU[ i + j*rows ]) > s[i]) {
			s[i]=fabs(LU[ i + j*rows ]);
		}
	}
}

for (k = 0; k < (N-1) ; k++){
	p = k;
	big = fabs( LU[ o[k] + k*rows ] / s[o[k]] );
	for (i = k+1; i < N ; i++){
		dummy = fabs( LU[ o[i] + k*rows ] / s[o[i]] );
		if (dummy > big){
			big = dummy;
			p = i;
		}
	}

	tmpass = o[p];
	o[p] = o[k];
	o[k] = tmpass;

	for (i = k+1; i < N ; i++){
		factor = LU[ o[i] + k*rows ] / LU[ o[k] + k*rows ];
		LU[ o[i] + k*rows ] = factor;
		for (j = k+1; j < N; j++) {
			LU[ o[i] + j*rows ] = LU[ o[i] + j*rows ] - factor * LU[ o[k] + j*rows ];
		}
	}
}
return 0;
}
*/
int lu(int N, double * M, double * LU, int * o, double * s, int niter)
{
	int i, j, k, p, tmpass, rows=N, cols=N;
  double big, dummy, factor;

for (i = 0; i < cols * rows ; i++){ LU[i]=M[i]; }

if(niter<1){ for (i = 0; i < N ; i++){o[i]=i;} } 

for (k = 0; k < (N-1) ; k++){

if (fabs(LU[o[k] + k*rows]) < PIV_TOL){

	for (i = 0; i < N ; i++){ 
		s[i]=fabs(LU[ i + 0*rows ]);
		for (j = 1; j < N ; j++){ 
			if (fabs(LU[ i + j*rows ]) > s[i]) {
				s[i]=fabs(LU[ i + j*rows ]);
			}
		}
	}
		p = k;
		big = fabs( LU[ o[k] + k*rows ] / s[o[k]] );
		for (i = k+1; i < N ; i++){
			dummy = fabs( LU[ o[i] + k*rows ] / s[o[i]] );
			if (dummy > big){
				big = dummy;
				p = i;
			}
		}

		tmpass = o[p];
		o[p] = o[k];
		o[k] = tmpass;
}
		for (i = k+1; i < N ; i++){
			factor = LU[ o[i] + k*rows ] / LU[ o[k] + k*rows ];
			LU[ o[i] + k*rows ] = factor;
			for (j = k+1; j < N; j++) {
				LU[ o[i] + j*rows ] = LU[ o[i] + j*rows ] - factor * LU[ o[k] + j*rows ];
			}
		}
	}

return 0;
}
/*for (i = 0; i < N ; i++){ 
	s[i]=fabs(LU[ i + 0*rows ]);
	for (j = 1; j < N ; j++){ 
		if (fabs(LU[ i + j*rows ]) > s[i]) {
			s[i]=fabs(LU[ i + j*rows ]);
		}
	}
}

for (k = 0; k < (N-1) ; k++){

	p = k;
	big = fabs( LU[ o[k] + k*rows ] / s[o[k]] );
	for (i = k+1; i < N ; i++){
		dummy = fabs( LU[ o[i] + k*rows ] / s[o[i]] );
		if (dummy > big){
			big = dummy;
			p = i;
		}
	}

	dummy = o[p];
	o[p] = o[k];
	o[k] = dummy;

	for (i = k+1; i < N ; i++){
		factor = LU[ o[i] + k*rows ] / LU[ o[k] + k*rows ];
		LU[ o[i] + k*rows ] = factor;
		for (j = k+1; j < N; j++) {
			LU[ o[i] + j*rows ] = LU[ o[i] + j*rows ] - factor * LU[ o[k] + j*rows ];
		}
	}
}
return 0;
}*/
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* lupq */ /*L (lower matrix) U (upper matrix) p_vector(row order),q_vector(column order) */
/* of M = perm(p_vector)*L*U*perm(q_vector) descomposition*/
/* Being perm(v) permutation matrix corresponding to order vector v */
/* Based in Algorithm 3.4.2, Matrix Computations, Golub and Van Loan. (3rd ed)*/
/* ********************************************************************************************* */
int lupq(int Rows, int Cols, double * M, double * LU, int * p_vector, int * q_vector	, int  niter)
{
int i, j, k,pivr, pivc,rows=Rows,cols=Cols,rank_matrix;
double factor, piv, big, tmp;
   

    for (i = 0; i < cols * rows ; i++){
		LU[i]=M[i];
		}

		for (k = 0; k < rows ; k++){

		if ((niter<1)||(fabs(LU[ p_vector[k] + q_vector[k]*rows]) < PIV_TOL )){ 
    big=0.0;
			 for (i = k; i < rows ; i++){ 
				 for (j = k; j < cols ; j++){ 
				 tmp = fabs( LU[p_vector[i] + q_vector[j]*rows ] );
				 if (tmp > big){
				        big = tmp;
					      pivr = i;
				        pivc = j;
				        }
		      }
			 }
    if (big > PIV_TOL){
			tmp = p_vector[pivr];
			p_vector[pivr] = p_vector[k];
			p_vector[k] = tmp;
	 		tmp = q_vector[pivc];
			q_vector[pivc] = q_vector[k];
			q_vector[k] = tmp;
     }
		}
    if (big > PIV_TOL){																					
		  for (i = k+1; i < rows ; i++){
                  factor = LU[ p_vector[i] + q_vector[k]*rows ] / LU[ p_vector[k] + q_vector[k]*rows ];
			LU[ p_vector[i] + q_vector[k]*rows ] = factor;
				for (j = k+1; j < cols; j++) {
				LU[ p_vector[i] + q_vector[j]*rows ] = LU[ p_vector[i] + q_vector[j]*rows ] - factor * LU[ p_vector[k] + q_vector[j]*rows ];
				}
		  }
     }
    else{
     rank_matrix=k-1;
     break;
    } 
   }

	if (Cols > Rows){
			   big=0.0;
				 i = rank_matrix;
					 for (k = rank_matrix+1; k < (cols-1) ; k++){ 
						 for (j = k; j < cols ; j++){ 
						 tmp = fabs( LU[p_vector[i] + q_vector[j]*rows ] );
						 if (tmp > big){
									  big = tmp;
									  pivc = j;
									  }
						 tmp = q_vector[pivc];
						 q_vector[pivc] = q_vector[k];
						 q_vector[k] = tmp;
						 }
   				 }

				 
	}
   
 return 0;
}

/* Copy
int lupq(int Rows, int Cols, double * M, double * LU, int * p_vector, int * q_vector	, int  niter)
{
int i, j, k,pivr, pivc,rows=Rows,cols=Cols,rank_matrix;
double factor, piv, big, tmp;
   

    for (i = 0; i < cols * rows ; i++){
		LU[i]=M[i];
		}

		for (k = 0; k < rows ; k++){

		if ((niter<1)||(fabs(LU[ p_vector[k] + q_vector[k]*rows]) < PIV_TOL )){ 
    big=0.0;
			 for (i = k; i < rows ; i++){ 
				 for (j = k; j < cols ; j++){ 
				 tmp = fabs( LU[p_vector[i] + q_vector[j]*rows ] );
				 if (tmp > big){
				        big = tmp;
					      pivr = i;
				        pivc = j;
				        }
		      }
			 }
    if (big > PIV_TOL){
			tmp = p_vector[pivr];
			p_vector[pivr] = p_vector[k];
			p_vector[k] = tmp;
	 		tmp = q_vector[pivc];
			q_vector[pivc] = q_vector[k];
			q_vector[k] = tmp;
     }
		}
    if (big > PIV_TOL){																					
		  for (i = k+1; i < rows ; i++){
                  factor = LU[ p_vector[i] + q_vector[k]*rows ] / LU[ p_vector[k] + q_vector[k]*rows ];
			LU[ p_vector[i] + q_vector[k]*rows ] = factor;
				for (j = k+1; j < cols; j++) {
				LU[ p_vector[i] + q_vector[j]*rows ] = LU[ p_vector[i] + q_vector[j]*rows ] - factor * LU[ p_vector[k] + q_vector[j]*rows ];
				}
		  }
     }
    else{
     rank_matrix=k-1;
     break;
    } 
   }

	if (Cols > Rows){
			   big=0.0;
				 i = rank_matrix;
					 for (k = rank_matrix+1; k < (cols-1) ; k++){ 
						 for (j = k; j < cols ; j++){ 
						 tmp = fabs( LU[p_vector[i] + q_vector[j]*rows ] );
						 if (tmp > big){
									  big = tmp;
									  pivc = j;
									  }
						 tmp = q_vector[pivc];
						 q_vector[pivc] = q_vector[k];
						 q_vector[k] = tmp;
						 }
   				 }

				 
	}
   
 return 0;
}
*/
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Permute matrix related to order row and column vectors*/
/* ********************************************************************************************* */
int Permute_Matrix_pq(int Rows, int Cols, double * LU, double * M, int * p_vector, int * q_vector)
{
int i,j;
    for (i = 0; i < Rows  ; i++){
     for (j = 0; j < Cols  ; j++){
		   M[ i + j*Rows ] = LU[ p_vector[i] + q_vector[j]*Rows ];
     }
		}
 return 0;
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
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* forward substitution */ /* L*y=b being L Lower Triangular ===> A*x=b ===> LU*x=b */
/* LU and b with pivoting according to vector o */
/* ********************************************************************************************* */
int forward_substitution_piv(int N, double * LU, int * o, double * b, double * y)
{
	int i, j, k, rows=N, cols=N;
  double aux;

for (i = 0; i< cols ; i++){ 	y[i]=0.0;	}

for (i = 0; i< rows ; i++){
  aux=b[o[i]];
  for (j = 0; j< i ; j++){
    aux = aux - LU[ o[i] + j*rows] * y[j];    
  }
  y[i] = aux;
}
return 0;
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
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* backward substitution */ /* U*x=y being U Upper Triangular ===> A*x=b ===> LU*x=b */
/* LU and b with pivoting according to vector o */
/* ********************************************************************************************* */
int backward_substitution_piv(int N, double * LU, int * o, double * y, double * x)
{
	int i, j, k, rows=N, cols=N;
  double aux;

for (i = 0; i< cols ; i++){ 	x[i]=0.0;	}

for (i = rows-1; i>=0 ; i--){
  aux=0.0;
  for (j = cols-1; j>= i+1 ; j--){
    aux = aux + LU[ o[i] + j*rows] * x[j]; 
  }
  x[i] = (y[i] - aux) / LU[ o[i] + i*rows];
}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* forward substitution */ /* L*y=b being L Lower Triangular ===> A*x=b ===> LU*x=b */
/* LU and b with pivoting according to vectors p and q */
/* ********************************************************************************************* */
int forward_substitution_piv_pq(int N, double * LU, int * p_vector, int * q_vector, double * b, double * y)
{
	int i, j, k, rows=N, cols=N;
  double aux;

for (i = 0; i< cols ; i++){ 	y[i]=0.0;	}

for (i = 0; i< rows ; i++){
  aux=b[p_vector[i]];
  for (j = 0; j< i ; j++){
    aux = aux - LU[ p_vector[i] + q_vector[j]*rows] * y[p_vector[j]];    
  }
  y[p_vector[i]] = aux;
}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* backward substitution */ /* U*x=y being U Upper Triangular ===> A*x=b ===> LU*x=b */
/* LU and b with pivoting according to vectors p and q */
/* ********************************************************************************************* */
int backward_substitution_piv_pq(int N, double * LU, int * p_vector,int * q_vector, double * y, double * x)
{
	int i, j, k, rows=N, cols=N;
  double aux;

for (i = 0; i< cols ; i++){ 	x[i]=0.0;	}

for (i = rows-1; i>=0 ; i--){
  aux=0.0;
  for (j = cols-1; j>= i+1 ; j--){
    aux = aux + LU[ p_vector[i] + q_vector[j]*rows] * x[q_vector[j]]; 
  }
  x[q_vector[i]] = (y[p_vector[i]] - aux) / LU[ p_vector[i] + q_vector[i]*rows];
}
return 0;
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system A*x=b, being A=sym and def pos */
/* ********************************************************************************************* */
int solve_lin_sys_chol(int N, double * A, double * b, double * x, double * L, double * U, double * y)
/*int solve_lin_sys_chol(int N, double * A, double * b, double * x)*/
{
/*double L[N*N], U[N*N], y[N];*/

chol(N, A, L);
Mat_Trasp(N, N, L, U);

forward_substitution(N, L, b, y);
backward_substitution(N, U, y, x);
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system A*x=b, being A=sym and def pos */
/* ********************************************************************************************* */
int solve_lin_sys_ldl(int N, double * A, double * b, double * x, double * L, double * U, double * d, double * y)
/*int solve_lin_sys_ldl(int N, double * A, double * b, double * x)*/
{
/*double L[N*N], U[N*N], d[N], y[N];*/
int i;

ldl(N, A, L, d);
Mat_Trasp(N, N, L, U);

forward_substitution(N, L, b, y);
for (i = 0; i< N ; i++){ y[i] = y[i] / d[ i ]; }
backward_substitution(N, U, y, x);
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system M*x=b, being M=def pos */
/* ********************************************************************************************* */
int solve_lin_sys_lu(int N, double * M, double * b, double * x, double * s, double * LU, double * y, int * o, int niter)
/*int solve_lin_sys_lu(int N, double * M, double * b, double * x, double * s)*/
{
/*double LU[N*N], y[N];
int o[N];*/

lu(N, M, LU, o, s, niter);
forward_substitution_piv(N, LU, o, b, y);
backward_substitution_piv(N, LU, o, y, x);
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system M*x=b, being M=def pos */
/* ********************************************************************************************* */
int solve_lin_sys_plu(int N, double * M, double * b, double * x)
{
/* Not developed but code available in matlab */
/*
double L[N*N], U[N*N], P[N*N], PT[N*N], Piv_b[N], y[N];
int i;

plu(N, M, P, L, U); ===> this function to be developed if required
Mat_Trasp(N, N, P, PT);
Mat_Vect_Mult(N, N, PT, b, +1.0, Piv_b)
forward_substitution(N, L, Piv_b, y);
backward_substitution(N, U, y, x);
return 0;	
*/
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system A*X=B, being A=sym and def pos */
/* ********************************************************************************************* */
int solve_lin_sys_chol_matrix(int Cols_A, double * A, int Cols_B, double * B, double * X, double * L, double * U, double * Y)
/*int solve_lin_sys_chol_matrix(int Cols_A, double * A, int Cols_B, double * B, double * X)*/
{
/*double L[ Cols_A * Cols_A ], U[ Cols_A * Cols_A ], Y[ Cols_A * Cols_B ];*/
int i;
chol(Cols_A, A, L);
Mat_Trasp(Cols_A, Cols_A, L, U);

for (i = 0; i< Cols_B ; i++){
	forward_substitution(Cols_A, L, &B[ i * Cols_A ], &Y[ i * Cols_A ]);
	backward_substitution(Cols_A, U, &Y[ i * Cols_A ], &X[ i * Cols_A ]);
}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system A*X=B, being A=sym and def pos */
/* ********************************************************************************************* */
int solve_lin_sys_ldl_matrix(int Cols_A, double * A, int Cols_B, double * B, double * X, double * L, double * U, double * d, double * Y)
/*int solve_lin_sys_ldl_matrix(int Cols_A, double * A, int Cols_B, double * B, double * X)*/
{
/*double L[ Cols_A * Cols_A ], U[ Cols_A * Cols_A ], d[ Cols_A ], Y[ Cols_A * Cols_B ];*/
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
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system M*X=B, being M=square */
/* ********************************************************************************************* */
int solve_lin_sys_lu_matrix(int Cols_M, double * M, int Cols_B, double * B, double * X, double * s, double * LU, double * Y, int * o, int niter)
/*int solve_lin_sys_lu_matrix(int Cols_M, double * M, int Cols_B, double * B, double * X, double * s)*/
{
/*double LU[ Cols_M * Cols_M ], Y[ Cols_M * Cols_B ];*/
/*int o[Cols_M];*/
int i;

lu(Cols_M, M, LU, o, s, niter);

for (i = 0; i< Cols_B ; i++){
	forward_substitution_piv(Cols_M, LU, o, &B[ i * Cols_M ], &Y[ i * Cols_M ]);
	backward_substitution_piv(Cols_M, LU, o, &Y[ i * Cols_M ], &X[ i * Cols_M ]);
}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system M*X=B, being M=square */
/* ********************************************************************************************* */
int solve_lin_sys_plu_matrix(int Cols_M, double * M, int Cols_B, double * B, double * X)
{
/* To be developed if required */
return 0;
}
/* ********************************************************************************************* */


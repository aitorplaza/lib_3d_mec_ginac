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
  int j;
  for (j=0; j<size; j++){
    printf(" %+.8f\n ",Vector[j]);
  }
  printf(" \n\n");
}

/* ********************************************************************************************* */
/* Vect_Print_int */ /* This function print a 1xJ vector of ints - Not OK for Real Time */
/* ********************************************************************************************* */
void	Vect_Print_Int	(int size ,int * Vector)
{
  int j;
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
  int i, j;
  for (i=0; i<Rows; i++){
    for (j=0; j<Cols; j++){
      printf(" %.6f ",Matrix[Rows*j+i]);
    }
    printf("\n");
  }
  printf("\n\n");
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Vect_Mult */ /* This function multiplies Matrix(IxJ) X Vector(Jx1) = Ans(Ix1) */
/* ********************************************************************************************* */
void 	Mat_Vect_Mult(int Rows, int Cols, double * Matrix, double * Vector, int Scale, double * Ans)
{
  int i, j;
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
/* Mat_Vect_Mult */ /* This function multiplies First Rows2 Submatrix rows of Matrix  */
/* Matrix(IxJ) X Vector(Jx1) = Ans(Ix1) */
/* ********************************************************************************************* */
void 	Mat_Vect_RMult(int Rows,int Rows2, int Cols, double * Matrix, double * Vector, int Scale, double * Ans)
{
int		i, j;
for (i=0; i<Rows2; i++){
	Ans[i] = 0.0;
	for (j=0; j<Cols; j++){
		Ans[i] = Matrix[Rows*j+i] * Vector[j] + Ans[i];
		}
	Ans[i] = Ans[i] * Scale;
	}
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Vect_Mult */ /* This function multiplies Matrix(JxI)' X Vector(Jx1) = Ans(Ix1) */
/* ********************************************************************************************* */
void 	Mat_Vect_TMult(int Rows, int Cols, double * Matrix, double * Vector, int Scale, double * Ans)
{
int		i, j;
for (i=0; i<Cols; i++){
	Ans[i] = 0.0;
	for (j=0; j<Rows; j++){
		Ans[i] = Matrix[j+i*Rows] * Vector[j] + Ans[i];
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
/* Mat_Mat_MultT */ /* This function multiplies Mat1(IxN) X Mat2(JxN)' = Ans(IxJ) */
/* ********************************************************************************************* */
void 	Mat_Mat_MultT(int Rows, int N, int Cols, double * Mat1, double * Mat2, int Scale, double * Ans)
{
int		i, j, k;
for (i=0; i<Rows; i++){
	for (j=0; j<Cols; j++){
		Ans[Rows*j+i] = 0.0;
		for	(k=0; k<N; k++){
			Ans[i+j*Rows] =  Mat1[i+k*Rows] * Mat2[j+k*N] + Ans[i+j*Rows];
			}
		Ans[Rows*j+i] = Ans[Rows*j+i] * Scale;
		}
	}
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Mat_TMult */ /* This function multiplies Mat1(NxI)' X Mat2(NxJ) = Ans(IxJ) */
/* ********************************************************************************************* */
void 	Mat_Mat_TMult(int Rows, int N, int Cols, double * Mat1, double * Mat2, int Scale, double * Ans)
{
int		i, j, k;
for (i=0; i<Rows; i++){
	for (j=0; j<Cols; j++){

		Ans[Rows*j+i] = 0.0;
		for	(k=0; k<N; k++){
			Ans[i+j*Rows] =  Mat1[k+i*N] * Mat2[N*j+k] + Ans[i+j*Rows];
			}
		Ans[Rows*j+i] = Ans[Rows*j+i] * Scale;
		}
	}
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Mat_Mult_SO */ /* This function multiplies Mat1(IxN) X Mat2(NxJ) = Ans(IxJ) */
/* For Symmetric Output (SO) . Computes only half matrix and replicates symmetric elements*/
/* ********************************************************************************************* */
void 	Mat_Mat_Mult_SO(int Rows, int N, int Cols, double * Mat1, double * Mat2, int Scale, double * Ans)
{
int		i, j, k;
for (i=0; i<Rows; i++){
	for (j=i; j<Cols; j++){
		Ans[Rows*j+i] = 0.0;
		for	(k=0; k<N; k++){
			Ans[Rows*j+i] =  Mat1[Rows*k+i] * Mat2[N*j+k] + Ans[Rows*j+i];
			}
		Ans[Rows*j+i] = Ans[Rows*j+i] * Scale;
		}
    for (j=0; j<i; j++){
    Ans[Rows*j+i] = Ans[Cols*i+j];
    }
 }
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Mat_RMult */ /* This function multiplies First Rows2 rows of Mat1(IxN) X Mat2(NxJ) = Ans(IxJ) */
/* And first Rows2 cols of Mat2 */
/* ********************************************************************************************* */
void 	Mat_Mat_RMult(int Rows,int Rows2, int N, int Cols, double * Mat1, double * Mat2, int Scale, double * Ans)
{
int		i, j, k;
for (i=0; i<Rows2; i++){
	for (j=0; j<Cols; j++){
		Ans[Rows2*j+i] = 0.0;
		for	(k=0; k<N; k++){
			Ans[Rows2*j+i] =  Mat1[Rows*k+i] * Mat2[N*j+k] + Ans[Rows2*j+i];
			}
		Ans[Rows2*j+i] = Ans[Rows2*j+i] * Scale;
		}

 }
}


/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Mat_RMult_SO */ /* This function multiplies First Rows2 rows of Mat1(IxN) X Mat2(NxJ) = Ans(IxJ) */
/* For Symmetric Output (SO) . Computes only half matrix and replicates symmetric elements*/
/* ********************************************************************************************* */
void 	Mat_Mat_RMult_SO(int Rows,int Rows2, int N, int Cols, double * Mat1, double * Mat2, int Scale, double * Ans)
{
  int i, j, k;
  for (i=0; i<Rows2; i++){
    for (j=i; j<Cols; j++){
      Ans[Rows2*j+i] = 0.0;
      for (k=0; k<N; k++){
        Ans[Rows2*j+i] =  Mat1[Rows*k+i] * Mat2[N*j+k] + Ans[Rows2*j+i];
      }
      Ans[Rows2*j+i] = Ans[Rows2*j+i] * Scale;
    }
    for (j=0; j<i; j++){
      Ans[Rows2*j+i] = Ans[Cols*i+j];
    }
  }
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Self_MultT_SO */ /* Multiplies a matrix by its transposed Mat1(IxN) X Mat1'(NxJ) = Ans(IxJ) */
/* For Symmetric Output (SO) . Computes only half matrix and replicates symmetric elements*/
/* ********************************************************************************************* */


void 	Mat_Self_MultT_SO(int Rows, int Cols, double * Mat1, int Scale, double * Ans)
{
  int i, j, k;
  for (i=0; i<Rows; i++){
    for (j=i; j<Rows; j++){
      Ans[Rows*j+i] = 0.0;
      for (k=0; k<Cols; k++){
        Ans[Rows*j+i] =  Mat1[i+k*Rows] * Mat1[j+k*Rows] + Ans[Rows*j+i];
        }
      Ans[Rows*j+i] = Ans[Rows*j+i] * Scale;
    }
    for (j=0; j<i; j++){
      Ans[i+j*Rows] = Ans[j+i*Rows] ;
    }
  }
}


/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Trasp */ /* This function trasposes a matrix */
/* ********************************************************************************************* */
void	Mat_Trasp(int Rows, int Cols, double * Mat, double * Mat_T)
{
  int i, j;
  for (j = 0; j < Cols; j++){
    for(i = 0; i < Rows; i++){Mat_T[j + i * Cols] = Mat[i + j * Rows];}
  }
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Mat_Inv */ /* This function inverts a N size matrix */
/* ********************************************************************************************* */
int Mat_Inv(int N, double * J, double * InvJ, double * JAug)
{

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
int 		Mat_PInv(int Rows, int Cols, double * J, double * PInvJ, double * JT, double * AUX_Cols, double * AUX_Rows, double * Inverse_AUX_Cols, double * Inverse_AUX_Rows, double * Buffer)
{
  Mat_Trasp( Rows, Cols, J, JT);

  if (Rows > Cols){
    Mat_Mat_Mult (Cols, Rows, Cols, JT, J, 1, AUX_Cols);
    Mat_Inv (Cols, AUX_Cols, Inverse_AUX_Cols,Buffer);
    Mat_Mat_Mult (Cols, Cols, Rows, Inverse_AUX_Cols, JT, 1, PInvJ);
    }

  if (Rows <= Cols){
    Mat_Mat_Mult (Rows, Cols, Rows, J, JT, 1, AUX_Rows);
    Mat_Inv (Rows, AUX_Rows, Inverse_AUX_Rows,Buffer);
    Mat_Mat_Mult (Cols, Rows, Rows, JT, Inverse_AUX_Rows, 1, PInvJ);
    }
  //~ if (Rows == Cols){
    //~ Mat_Inv (Rows, AUX_Rows, PInvJ,Buffer);
    //~ }
  return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* PInvLU */ /* This function returns Pinv(Cols x Rows) of a rank-deficient matrix (Rows x Cols) */
/* ********************************************************************************************* */

int Mat_PInvLU(int Rows, int Cols, double * J, double * PInvJ, double * JT, double * AUX_Cols, double * AUX_Rows, double * Inverse_AUX_Cols, double * Inverse_AUX_Rows, int * p_vector, int * q_vector, double * BufferL, double * BufferU)
{

  int i,j,rank,aux;
  /*int p_vector[Rows], q_vector[Cols];
  double BufferL[2*Rows*Rows];
  double BufferU[2*Rows*Rows];*/

  for (i = 0; i < Cols; i++){q_vector[i]=i;}
  for (i = 0; i < Rows; i++){p_vector[i]=i;}

  rank=lufp3(Rows,Rows,Cols,J,p_vector, q_vector);
  rank=0;
  for (i = 0; i < Rows ; i++){ 
    for (j = 0; j < rank ; j++){
      if (i == j){
        AUX_Rows[i+j*Rows] = 1.0;
      }
      if (i > j){
        AUX_Rows[i+j*Rows] =  J[p_vector[i] + q_vector[j]*Rows];
      }
      if (i < j){
        AUX_Rows[i+j*Rows] = 0.0;
      } 
    }
  }

  for (i = 0; i < rank ; i++){ 
    for (j = 0; j < Cols ; j++){ 
      if (i > j){
        AUX_Cols[i+j*rank] = 0.0;
      }
      else {
        AUX_Cols[i+j*rank] =  J[p_vector[i] + q_vector[j]*Rows];
      }
    }
  }
  /*Execute algorithm with L, U and rank*/
  Mat_Trasp(Rows,rank,AUX_Rows,Inverse_AUX_Cols);
  Mat_Mat_Mult(rank, Rows, rank, Inverse_AUX_Cols, AUX_Rows, +1, J);
  Mat_Inv(rank,J,AUX_Rows, BufferL);
  Mat_Mat_Mult(rank, rank, Rows, AUX_Rows , Inverse_AUX_Cols, +1, Inverse_AUX_Rows);
  Mat_Trasp(rank,Cols,AUX_Cols,J);
  Mat_Mat_Mult(rank, Cols, rank, AUX_Cols, J, +1, AUX_Rows);
  Mat_Inv(rank,AUX_Rows,AUX_Cols, BufferU);
  Mat_Mat_Mult(Cols, rank, rank, J, AUX_Cols, +1, Inverse_AUX_Cols);
  Mat_Mat_Mult(Cols, rank, Rows, Inverse_AUX_Cols, Inverse_AUX_Rows, +1, PInvJ);
  for (j = 0; j < Cols ; j++){ 
    aux=q_vector[j];
    for (i = 0; i < Cols ; i++){ 
      if (i==aux){
        AUX_Cols[i+j*Cols] = 1.0;
      }
      else {
        AUX_Cols[i+j*Cols] = 0.0;
      }
    }
  }
  for (j = 0; j < Rows ; j++){ 
    aux=p_vector[j];
      for (i = 0; i < Rows ; i++){ 
        if (i==aux){
          AUX_Rows[j+i*Rows] = 1.0;
        }
        else {
          AUX_Rows[j+i*Rows] = 0.0;
        }
      }
  }
  Mat_Mat_Mult(Cols, Cols, Rows, AUX_Cols, PInvJ, +1, Inverse_AUX_Cols);
  Mat_Mat_Mult(Cols, Rows, Rows, Inverse_AUX_Cols, AUX_Rows, +1, PInvJ);
  return 0;
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* PInvLU */ /* This function returns pinv(Cols x Rows) of a rank-deficient matrix (Rows x Cols) */
/* ********************************************************************************************* */
/*
int 		solve_lin_sys_PInvLU(int Rows, int Cols, double * J, double * JT, double * Buffer, double	* AUX_Cols, double	* AUX_Rows, double	* Inverse_AUX_Cols, double	* Inverse_AUX_Rows, double * b, double * x)
{

int i,j,rank,aux;
int p_vector[Rows], q_vector[Cols];
double sol[Cols];

for (i = 0; i < Cols; i++){q_vector[i]=i;}
for (i = 0; i < Rows; i++){p_vector[i]=i;}

rank=lufp3(Rows,Rows,Cols,J,p_vector, q_vector);
			 for (i = 0; i < Rows ; i++){ 
				 for (j = 0; j < rank ; j++){
				 	 if (i == j){
           AUX_Rows[i+j*Rows] = 1.0;
           }
				 	 if (i > j){
           AUX_Rows[i+j*Rows] =  J[p_vector[i] + q_vector[j]*Rows];
           }
				 	 if (i < j){
           AUX_Rows[i+j*Rows] = 0.0;
           } 
		      }
			  } 

			 for (i = 0; i < rank ; i++){
				 for (j = 0; j < Cols ; j++){ 
				 	 if (i > j){
           AUX_Cols[i+j*rank] = 0.0;
           }
				 	 else {
           AUX_Cols[i+j*rank] =  J[p_vector[i] + q_vector[j]*Rows];
           }
		      }
			  }

    Mat_Trasp(Rows,rank,AUX_Rows,Inverse_AUX_Cols);
    Mat_Mat_Mult(rank, Rows, rank, Inverse_AUX_Cols, AUX_Rows, +1, J);
        aux=p_vector[j];
       for (j = 0; j < Rows ; j++){ 
				 for (i = 0; i < Rows ; i++){ 
				 	 if (i==aux){
           Buffer[j+i*Rows] = 1.0;
           }
				 	 else {
           Buffer[j+i*Rows] = 0.0;
           }
		      }
			  }
    Mat_Mat_Mult(rank, Rows, Rows, Inverse_AUX_Cols , Buffer, +1, Inverse_AUX_Rows);  
    Mat_Vect_Mult(rank,Rows,Inverse_AUX_Rows,b, +1, Buffer);
    solve_lin_sys_chol(rank, J, Buffer, x, AUX_Rows, J, Inverse_AUX_Rows);
    Mat_Trasp(rank,Cols,AUX_Cols,J);
    Mat_Mat_Mult(rank, Cols, rank, AUX_Cols, J, +1, Buffer);
    solve_lin_sys_chol(rank, Buffer, x, sol, Inverse_AUX_Cols, Inverse_AUX_Rows , AUX_Rows);

        for (j = 0; j < Cols ; j++){
        aux=q_vector[j];
				 for (i = 0; i < Cols ; i++){ 
				 	 if (i==aux){
           AUX_Rows[i+j*Cols] = 1.0;
           }
				 	 else {
           AUX_Rows[i+j*Cols] = 0.0;
           }
		      }
			  }
    Mat_Mat_Mult(Cols, Cols, rank, AUX_Rows, J, +1, Buffer); 
Mat_Vect_Mult(Cols,rank, Buffer, sol, +1, x);

return 0;
}
*/
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve_N_R(START) */
/* ********************************************************************************************* */
int Solve_N_R(int Rows, int Cols, double * Eq, double * Jac, double * Vector, double * PInv_Jac, double * delta, double * BufferJT,double * BufferAUXCols, double * BufferAUXRows, double * BufferIAUXCols, double * BufferIAUXRows, int * p_vector, int * q_vector, double * BufferL, double * BufferPINV)
{
int				i;

if(Rows==Cols){
    Mat_Inv( Rows, Jac, PInv_Jac, BufferJT);}
else{
    /*double BufferJT[2*Rows*Cols];
    double BufferAUXCols[2*Cols*Cols];
    double BufferAUXRows[2*Rows*Rows];
    double BufferIAUXCols[2*Cols*Cols];
    double BufferIAUXRows[2*Rows*Rows];*/
    #ifndef ROBUST_NR
    Mat_PInv( Rows, Cols, Jac, PInv_Jac, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows, BufferPINV);
    #else
    Mat_PInvLU( Rows, Cols, Jac, PInv_Jac, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows, p_vector, q_vector, BufferL, BufferPINV);
    #endif
    }
    Mat_Vect_Mult(Cols, Rows, PInv_Jac, Eq, +1, delta);

for (i=0; i<Cols; i++) {				/* subtract delta from last iterations pos values */
	Vector[(i)] -= delta[i];			/* Re-calculate dep coord. */
	}
return 0;
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/*  Solve_N_R_while */
/* ********************************************************************************************* */
int Solve_N_R_while(int N, int M, double * (* Vector_Eq)(), double * (* Matrix_Jac)(), double * Vector, double * Inverse, double * delta, double * BufferJT,double * BufferAUXCols, double * BufferAUXRows, double * BufferIAUXCols, double * BufferIAUXRows, int * p_vector, int * q_vector, double * BufferL, double * BufferPINV)
{
  int			iteration = 0, iterate = 1, i;
  /*double		delta[M];*/
  double	conv_err = 1.;
  double	* _Vector_Eq;
  double	* _Matrix_Jac;

/*double Buffer[2*N*N];
double BufferJT[2*N*M];
double BufferAUXCols[2*M*M];
double BufferAUXRows[2*N*N];
double BufferIAUXCols[2*M*M];
double BufferIAUXRows[2*N*N];*/

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
      #ifndef ROBUST_INIT_SOLVER
      Mat_Inv( N, _Matrix_Jac, Inverse, BufferJT);
      #else
      Mat_PInvLU( N, M, _Matrix_Jac, Inverse, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows, p_vector, q_vector, BufferL, BufferPINV);
      #endif
      }
    else{
      #ifndef ROBUST_INIT_SOLVER
      Mat_PInv( N, M, _Matrix_Jac, Inverse, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows,BufferPINV);
      #else
      Mat_PInvLU( N, M, _Matrix_Jac, Inverse, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows, p_vector, q_vector, BufferL, BufferPINV);
      #endif
    }
    
    Mat_Vect_Mult(M, N, Inverse, _Vector_Eq, +1, delta);

    for (i=0; i<M; i++)
    {                                      /* subtract delta from last iterations pos values */
      Vector[(i)] -= delta[i];             /* Re-calculate dep coord. */
    }

    conv_err = 0.0;		
    for (i = 0; i < N; i++) {	/* determine value of conv_error (used to determine if no convergence) */
      conv_err += fabs(_Vector_Eq[i]);
    }

    iterate = 0;                                           /* assume iteration is done */
    for (i = 0; i < N; i++) {
      if (fabs(_Vector_Eq[i]) > conv_criterion) {          /* check if needs another iteration */
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
/*int			Solve_N_R_for(int N, int M, double * (* Vector_Eq)(), double * (* Matrix_Jac)(), double * Vector, int iterations, double * Inverse, double * delta)
{
int				j, i;
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
	for (i=0; i<N; i++) {					
		Vector[(i)] -= delta[i];			
	}
}
#ifdef DEBUG
conv_err = 0.0;		
for (i = 0; i < N; i++) {	
	conv_err += fabs(_Vector_Eq[i]);
}
#endif
return 0;
}*/
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





/* ********************************************************************************************* */
/* ********************************************************************************************* */
/* lufp3 */
/* Full submatrix pivot permutation of matrix M generating order vectors p and q  */
/* Pivoting only in top (1 to Rows2) rows and full column submatrix without rank determination */
/* Returns LUpq into input matrix */
/* ********************************************************************************************* */

int lufp3(int Rows, int Rows2, int Cols, double * LUpq, int * p_vector, int * q_vector)
{
int i, j, k, pivr=0, pivc=0, rank, tmpi;
double factor, big, tmp;
  rank = Rows ;  
  for (k = 0; k < Rows ; k++){
    big=0.0;
    if (k < Rows2){
      for (i = k; i < Rows2 ; i++){ 
        for (j = k; j < Cols ; j++){ 
          tmp = fabs( LUpq[p_vector[i] + q_vector[j]*Rows ] );
          if (tmp > big){
            big = tmp;
            pivr = i;
            pivc = j;
          }
        }
      }
    }
    else {
      for (i = k; i < Rows ; i++){ 
        for (j = k; j < Cols ; j++){ 
          tmp = fabs( LUpq[p_vector[i] + q_vector[j]*Rows ] );
            if (tmp > big){
              big = tmp;
              pivr = i;
              pivc = j;
          }
        }
      }
    }
    if (big > PIV_TOL){
      tmpi = p_vector[pivr];
      p_vector[pivr] = p_vector[k];
      p_vector[k] = tmpi;
      tmpi = q_vector[pivc];
      q_vector[pivc] = q_vector[k];
      q_vector[k] = tmpi;
    }
    if (big > PIV_TOL){																	
      for (i = k+1; i < Rows ; i++){
        factor = LUpq[ p_vector[i] + q_vector[k]*Rows ] / LUpq[ p_vector[k] + q_vector[k]*Rows ];
        LUpq[ p_vector[i] + q_vector[k]*Rows ] = factor;
        for (j = k+1; j < Cols; j++) {
          LUpq[ p_vector[i] + q_vector[j]*Rows ] = LUpq[ p_vector[i] + q_vector[j]*Rows ] - factor * LUpq[ p_vector[k] + q_vector[j]*Rows ];
        }
      }
    }
    else {
      rank=k;
      break;
    }
  }
  return rank;
}

/* ********************************************************************************************* */
/* ********************************************************************************************* */
/* lufp4 */
/* Full pivot permutation on each crossing row and column, generating order vectors p and q  */
/* Pivoting only in top (1 to Rows2) rows and full columns submatrix without rank determination*/
/* Returns LUpq into input matrix */
/* ********************************************************************************************* */

int lufp4(int Rows, int Rows2, int Cols, double * LUpq, int * p_vector, int * q_vector)
{
  int i, j, k,pivr, pivc, rank, tmpi;
  double factor, big, tmp;
  rank = Rows ;
  for (k = 0; k < Rows ; k++){
    if(fabs( LUpq[p_vector[k] + q_vector[k]*Rows ] ) < PIV_TOL){
      big=0.0;
      if (k < Rows2){
        for (i = k; i < Rows2 ; i++){ 
          tmp = fabs( LUpq[p_vector[i] + q_vector[k]*Rows ] );
          if (tmp > big){
            big = tmp;
            pivr = i;
            pivc = k;
          }
        }
        for (j = k; j < Cols ; j++){ 
          tmp = fabs( LUpq[p_vector[k] + q_vector[j]*Rows ] );
          if (tmp > big){
            big = tmp;
            pivr = k;
            pivc = j;
          }
        }
      }
      else {
        for (i = k; i < Rows ; i++){ 
          tmp = fabs( LUpq[p_vector[i] + q_vector[k]*Rows ] );
          if (tmp > big){
            big = tmp;
            pivr = i;
            pivc = k;
          }
        }
        for (j = k; j < Cols ; j++){ 
          tmp = fabs( LUpq[p_vector[k] + q_vector[j]*Rows ] );
          if (tmp > big){
            big = tmp;
            pivr = k;
            pivc = j;
          }
        }
      }
      if (big > PIV_TOL){
        tmpi = p_vector[pivr];
        p_vector[pivr] = p_vector[k];
        p_vector[k] = tmpi;
        tmpi = q_vector[pivc];
        q_vector[pivc] = q_vector[k];
        q_vector[k] = tmpi;
      }
    }
    else {
      big = fabs( LUpq[p_vector[k] + q_vector[k]*Rows ] );
    }
    if (big > PIV_TOL){																	
      for (i = k+1; i < Rows ; i++){
        factor = LUpq[ p_vector[i] + q_vector[k]*Rows ] / LUpq[ p_vector[k] + q_vector[k]*Rows ];
        LUpq[ p_vector[i] + q_vector[k]*Rows ] = factor;
        for (j = k+1; j < Cols; j++) {
          LUpq[ p_vector[i] + q_vector[j]*Rows ] = LUpq[ p_vector[i] + q_vector[j]*Rows ] - factor * LUpq[ p_vector[k] + q_vector[j]*Rows ];
        }
      }
    }
    else {
      rank=k;
      break;
    }
  }

  return rank;
}


/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* forward substitution */ /* L*y=b being L Lower Triangular ===> A*x=b ===> LU*x=b */
/* ********************************************************************************************* */
int forward_substitution(int N, double * L, double * b, double * y)
{
	int i, j, rows=N;
  double aux;

for (i = 0; i< rows ; i++){ 	y[i]=0.0;	}

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
	int i, j, rows=N;
  double aux;

for (i = 0; i< rows ; i++){ 	y[i]=0.0;	}

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
	int i, j, rows=N, cols=N;
  double aux;

for (i = 0; i< rows ; i++){ 	x[i]=0.0;	}

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
	int i, j, rows=N, cols=N;
  double aux;

for (i = 0; i< rows ; i++){ 	x[i]=0.0;	}

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
/* LU may have more total Rows than used Rows2 */
/* ********************************************************************************************* */
int forward_substitution_LU_pq_x(int Rows,int Rows2, double * LU, int * p_vector, int * q_vector, double * b, double * y)
{
	int i, j;
  double aux;

for (i = 0; i< Rows2 ; i++){
  aux=b[p_vector[i]];
  for (j = 0; j< i ; j++){
    aux = aux - LU[i + j*Rows] * y[j];    
  }
  y[i] = aux;
}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* backward substitution */ /* U*x=y being U Upper Triangular ===> A*x=b ===> LU*x=b */
/* LU and b with pivoting according to vectors p and q */
/* LU may have more total Rows than used Rows2 */
/* ********************************************************************************************* */
int backward_substitution_LU_pq_x(int Rows,int Rows2, double * LU, int * p_vector,int * q_vector, double * y, double * x)
{
	int i, j;
  double aux;

for (i = Rows2-1; i>=0 ; i--){
  aux=0.0;
  for (j = Rows2-1; j>= i+1 ; j--){
    aux = aux + LU[ i + j*Rows] * x[j]; 
  }
  x[i] = (y[i] - aux) / LU[i + i*Rows];
}

return 0;
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* forward substitution */ /* L*y=b being L Lower Triangular ===> A*x=b ===> LU*x=b */
/* LU and b with pivoting according to vectors p and q */
/* LU may have more total Rows than used Rows2 */
/* ********************************************************************************************* */
int forward_substitution_LU_pq_q(int Rows,int Rows2, double * LU, int * p_vector, int * q_vector, double * b, double * y)
{
	int i, j;
  double aux;

for (i = 0; i< Rows2 ; i++){ 	y[i]=0.0;	}

for (i = 0; i< Rows2 ; i++){
  aux=b[p_vector[i]];
  for (j = 0; j< i ; j++){
    aux = aux - LU[i + j*Rows] * y[j];    
  }
  y[i] = aux;
}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* backward substitution */ /* U*x=y being U Upper Triangular ===> A*x=b ===> LU*x=b */
/* LU and b with pivoting according to vectors p and q */
/* LU may have more total Rows than used Rows2 */
/* ********************************************************************************************* */
int backward_substitution_LU_pq_q(int Rows,int Rows2, double * LU, int * p_vector,int * q_vector, double * y, double * x)
{
	int i, j;
  double aux;

for (i = 0; i< Rows2 ; i++){ 	x[i]=0.0;	}

for (i = Rows2-1; i>=0 ; i--){
  aux=0.0;
  for (j = Rows2-1; j>= i+1 ; j--){
    aux = aux + LU[ i + j*Rows] * x[q_vector[j]]; 
  }
  x[q_vector[i]] = (y[i] - aux) / LU[i + i*Rows];
}

return 0;
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* forward substitution */ /* L*y=b being L Lower Triangular ===> A*x=b ===> LU*x=b */
/* LU and b with pivoting according to vectors p and q */
/* LU may have more total Rows than used Rows2 */
/* ********************************************************************************************* */
int forward_substitution_LUpq_pq_x(int Rows,int Rows2, double * LUpq, int * p_vector, int * q_vector, double * b, double * y)
{
	int i, j;
  double aux;

/*for (i = 0; i< Rows2 ; i++){ 	y[i]=0.0;	}*/

for (i = 0; i< Rows2 ; i++){
  aux=b[p_vector[i]];
  for (j = 0; j< i ; j++){
    aux = aux - LUpq[p_vector[i] + q_vector[j]*Rows] * y[j];    
  }
  y[i] = aux;
}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* backward substitution */ /* U*x=y being U Upper Triangular ===> A*x=b ===> LU*x=b */
/* LU and b with pivoting according to vectors p and q */
/* LU may have more total Rows than used Rows2 */
/* ********************************************************************************************* */
int backward_substitution_LUpq_pq_x(int Rows,int Rows2, double * LUpq, int * p_vector,int * q_vector, double * y, double * x)
{
	int i, j;
  double aux;

/*for (i = 0; i< Rows2 ; i++){ 	x[i]=0.0;	}*/

for (i = Rows2-1; i>=0 ; i--){
  aux=0.0;
  for (j = Rows2-1; j>= i+1 ; j--){
    aux = aux + LUpq[p_vector[i] + q_vector[j]*Rows] * x[j]; 
  }
  x[i] = (y[i] - aux) / LUpq[p_vector[i] + q_vector[i]*Rows];
}

return 0;
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* forward substitution */ /* L*y=b being L Lower Triangular ===> A*x=b ===> LU*x=b */
/* LU and b with pivoting according to vectors p and q */
/* LU may have more total Rows than used Rows2 */
/* ********************************************************************************************* */
int forward_substitution_LUpq_pq_q(int Rows,int Rows2, double * LUpq, int * p_vector, int * q_vector, double * b, double * y)
{
	int i, j;
  double aux;

/*for (i = 0; i< Rows2 ; i++){ 	y[i]=0.0;	}*/

for (i = 0; i< Rows2 ; i++){
  aux=b[p_vector[i]];
  for (j = 0; j< i ; j++){
    aux = aux - LUpq[p_vector[i] + q_vector[j]*Rows]* y[j];    
  }
  y[i] = aux;
}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* backward substitution */ /* U*x=y being U Upper Triangular ===> A*x=b ===> LU*x=b */
/* LU and b with pivoting according to vectors p and q */
/* LU may have more total Rows than used Rows2 */
/* ********************************************************************************************* */
int backward_substitution_LUpq_pq_q(int Rows,int Rows2, double * LUpq, int * p_vector,int * q_vector, double * y, double * x)
{
	int i, j;
  double aux;

/*for (i = 0; i< Rows2 ; i++){ 	x[i]=0.0;	}*/

for (i = Rows2-1; i>=0 ; i--){
  aux=0.0;
  for (j = Rows2-1; j>= i+1 ; j--){
    aux = aux + LUpq[p_vector[i] + q_vector[j]*Rows] * x[q_vector[j]]; 
  }
  x[q_vector[i]] = (y[i] - aux) / LUpq[p_vector[i] + q_vector[i]*Rows];
}

return 0;
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* forward substitution */ /* U'*y=b being U Upper Triangular ===> A*x=b ===> (LU)'*x=b          */
/* LU       with pivoting according to vectors p and q                                           */
/* LU may have more total Rows than used Rows2                                                   */
/* ********************************************************************************************* */
int forward_substitution_LUpq_T_pq_q(int Rows,int Rows2, double * LUpq, int * p_vector, int * q_vector, double * b, double * y)
{
  int i, j;
  double aux;
for (j = 0; j< Rows2 ; j++){
  aux=0.0;
  for (i = 0; i< j ; i++){
    aux = aux + LUpq[p_vector[i] + q_vector[j]*Rows] * y[i];    
  }
  //y[j] = (b[q_vector[j]]- aux) / LUpq[p_vector[j] + q_vector[j]*Rows] ;
  y[j] = (b[j]- aux) / LUpq[p_vector[j] + q_vector[j]*Rows] ;
}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* backward substitution */ /* L'*x=y being L Lower Triangular ===> A*x=b ===> (LU)'*x=b         */
/* LU       with pivoting according to vectors p and q                                           */
/* LU may have more total Rows than used Rows2                                                   */
/* ********************************************************************************************* */
int backward_substitution_LUpq_T_pq_q(int Rows,int Rows2, double * LUpq, int * p_vector,int * q_vector, double * y, double * x)
{
  int i, j;
  double aux;

for (j = Rows2-1; j>=0 ; j--){
  aux=0.0;
  for (i = Rows2-1; i> j ; i--){
    aux = aux + LUpq[p_vector[i] + q_vector[j]* Rows] * x[p_vector[i]]; 
    //aux = aux + LUpq[p_vector[i] + q_vector[j]* Rows] * x[i]; 
  }
  x[p_vector[j]] =y[j] - aux ;
  //x[i] =y[j] - aux ;
}

return 0;
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* backward substitution specific for calculating A of indep. coord. algorithm*/
/* Ud * A = -Uz */
/* LU and b with pivoting according to vectors p and q */
/* LU may have more total Rows than used Rows2 */
/* ********************************************************************************************* */
int backward_substitution_LU_pq_A(int Rows,int Rows2, double * LU, int * p_vector,int * q_vector, double * y, double * x)
{
	int i, j;
  double aux;

/*for (i = 0; i< Rows2 ; i++){ 	x[i]=0.0;	}*/

for (i = Rows2-1; i>=0 ; i--){
  aux=0.0;
  for (j = Rows2-1; j>= i+1 ; j--){
    aux = aux + LU[ i + j*Rows] * x[j]; 
  }
  x[i] = (-y[i] - aux) / LU[i + i*Rows];
}

return 0;
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* backward substitution specific for calculating A of indep. coord. algorithm*/
/* Ud * A = -Uz */
/* LU and b with pivoting according to vectors p and q */
/* LU may have more total Rows than used Rows2 */
/* ********************************************************************************************* */
int backward_substitution_LUpq_pq_A(int Rows,int Rows2, double * LUpq, int * p_vector,int * q_vector, double * y, double * x)
{
  int i, j;
  double aux;

/*for (i = 0; i< Rows2 ; i++){ 	x[i]=0.0;	}*/

for (i = Rows2-1; i>=0 ; i--){
  aux=0.0;
  for (j = Rows2-1; j>= i+1 ; j--){
    aux = aux + LUpq[p_vector[i] + q_vector[j]*Rows] * x[j]; 
  }
  x[i] = (-y[p_vector[i]] - aux) / LUpq[p_vector[i] + q_vector[i]*Rows];
}

return 0;
}

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system A*x=b, being A=sym and def pos */
/* ********************************************************************************************* */
int solve_lin_sys_chol(int N, double * A, double * b, double * x, double * L, double * U, double * y)

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
/*int solve_lin_sys_plu(int N, double * M, double * b, double * x)
{  */
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
}*/
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
	//forward_substitution_piv(Cols_M, LU, o, &B[ i * Cols_M ], &Y[ i * Cols_M ]);
	//backward_substitution_piv(Cols_M, LU, o, &Y[ i * Cols_M ], &X[ i * Cols_M ]);
	forward_substitution_piv (Cols_M, LU, o, B, Y);
	backward_substitution_piv(Cols_M, LU, o, Y, X);
}
return 0;
}
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Solve linear system M*X=B, being M=square */
/* ********************************************************************************************* */
int solve_lin_sys_plu_matrix(int Cols_M, double * M, double * B, double * X, double * BufferY, int * p_vector, int * q_vector)
{
  lufp4(Cols_M,Cols_M, Cols_M, M, p_vector, q_vector);
  forward_substitution_LUpq_pq_q (Cols_M,Cols_M, M, p_vector, q_vector, B, BufferY);
  backward_substitution_LUpq_pq_q(Cols_M,Cols_M, M, p_vector, q_vector, BufferY, X);
return 0;
}
/* ********************************************************************************************* */


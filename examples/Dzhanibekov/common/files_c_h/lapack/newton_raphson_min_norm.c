/*=========================================================
 * matrixDivide.c - Example for illustrating how to use
 * LAPACK within a C MEX-file.
 *
 * X = matrixDivide(A,B) computes the solution to a
 * system of linear equations A * X = B
 * using LAPACK routine DGESV, where
 * A is an N-by-N matrix
 * X and B are N-by-1 matrices.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 2009 The MathWorks, Inc.
 *=======================================================*/
/* $Revision: 1.1.6.2 $ $Date: 2009/05/18 19:50:18 $ */

#ifdef MATLAB_MEX_FILE
    #define printf mexPrintf
#endif 

#define min(a,b) ((a)>(b) ? (b) : (a))
#define max(a,b) ((a)<(b) ? (b) : (a))


#if !defined(_WIN32)
#define dgelsd dgelsd_
#define dgemv dgemv_
#define daxpy daxpy_
#define dnrm2 dnrm2_
#endif

#if defined(__MINGW32__)
#define dgelsd dgelsd_
#define dgemv dgemv_
#define daxpy daxpy_
#define dnrm2 dnrm2_
#endif

extern double dnrm2(int *n,double *x,int *incx);

/*check this*/
extern void dgelsd ( int *m , int *n , int *nrhs,double *a , int *lda , double *b , int *ldb , double *s , double *rcond , int *rank , double *work , int *lwork , int *iwork , int *info);
extern void daxpy ( int *n , double *alpha , double *dx , int *incx , double *dy , int *incy);
extern void dgemv ( char *trans , int *m , int *n , double *alpha ,  double *a , int *lda , double *x , int *incx , double *beta , double *y , int *incy);
/* #include "mex.h"
//#include "blas.h"
//#include "lapack.h"
*/

#include "stdlib.h"
#include "math.h"
#include <stdio.h>
#include <string.h>

//#include "print_mat.h"

#ifndef NEWTON_RAPHSON_TOLERANCE
#define NEWTON_RAPHSON_TOLERANCE 1.0e-16
#endif

/* Auxiliary routines prototypes */
/* extern void print_matrix( char* desc, int m, int n, double* a, int lda );*/

int minimum_norm_solution(int ma, int na, double * A, int nrhs, double * B, double *X);

int minimum_norm_correction(int ma, int na, double * A, double * B, double *X);


/* A is ma*na, nrhs are allowed, X is na*nrhs and B is ma*nrhs. X gets the output and A gets rewriten */

int minimum_norm_solution(int ma, int na, double * A, int nrhs, double * B, double * X) {
    double *s, rcond, *work, wkopt;
    int rank, lwork, info;
    int * iwork;
    int max_m_n;    
    double * AA;
    max_m_n=max(ma,na);

    /* AA is a copy of A, for the subroutine not to modify A    */
    AA = (double*)malloc( ma*na*sizeof(double) );
    memcpy(AA, A, ma*na*sizeof(double));
    memcpy(X, B, max_m_n*nrhs*sizeof(double));

    iwork = (int *)malloc( (3*min(ma,na)*( max( 0, (int)( log( min(ma,na)/(25+1) )/log(2) )+1 ) )+11*min(ma,na))*sizeof(int) );
    
    s = (double*)malloc( min(ma,na)*sizeof(double) );

    //rcond=1.0e-12;
    rcond=-1.0;

    /* Query and allocate the optimal workspace */
    lwork = -1;


    info=0;
    //dgelsd( &ma, &na, &nrhs, AA, &ma, X, &na, s, &rcond, &rank, &wkopt, &lwork, iwork, &info );
    dgelsd( &ma, &na, &nrhs, AA, &ma, X, &max_m_n , s, &rcond, &rank, &wkopt, &lwork, iwork, &info );
    lwork = (int)wkopt;

    work = (double*)malloc( lwork*sizeof(double) );

    //memcpy(X, B, ma*nrhs*sizeof(double));
    //memcpy(X, B, na*nrhs*sizeof(double));

    /* Solve the equations A*X = B */  /*  X=pinv(A)*B  */  /* Calling LAPACK */
    //dgelsd( &ma, &na, &nrhs, AA, &ma, X, &na, s, &rcond, &rank, work  , &lwork, iwork, &info);
    dgelsd( &ma, &na, &nrhs, AA, &ma, X,&max_m_n , s, &rcond, &rank, work  , &lwork, iwork, &info);
     /* Free workspace */
     free( (void*)work );
     free( (void*)s );
     free( (void*)iwork );
     free( (void*)AA);

     return info;

}



int minimum_norm_correction(int ma, int na, double * A, double * B, double * X) {
    /* Gives X+Delta X, where Delta X is the minimum norm solution of A * Deta X = B - A * X */
    /* A is a matrix and B is a vector */
    /* A * X = b is suposed to be a constraint equation and X+Deta_X
       the closest vector to X that satisfies the constraint */

    double done=1.0,dminusone=-1.0;
    int error=0;
    double * Delta_X;

    //int  maxmbna=max(ma,na);
    int ione=1;

    /*  -A * X + B -> B  */
    dgemv("N",&ma, &na, &dminusone, A, &ma, X, &ione, &done, B, &ione);

    Delta_X= (double *) malloc( na*1*sizeof(double) );

    /*  pinv(A) * B -> Delta_X */
/*  error=minimum_norm_solution(ma, na, A, 1, B, Delta_X);  */
    minimum_norm_solution(ma, na, A, 1, B, Delta_X);

    /*  Delta_X + X -> X  */
    daxpy(&na,&done,Delta_X,&ione,X,&ione);

    if (error != 0)
        return error;

}

int newton_raphson_min_norm (int ma, int na,
                 double * (* A)(),
                 double * (* b)(),
                 double * q)
{
      int i;
      int maxiterations=100;
      double underrelaxation=-0.9;
//      double tolerance=1.0e-8;
//printf("NEWTON_RAPHSON_TOLERANCE=%.16f\n",NEWTON_RAPHSON_TOLERANCE);

      double * J=NULL;

      double * Phi=NULL;

      double * Delta_q=NULL;
      int ione=1;

      J=(* A)();

      Phi=(* b)();

      Delta_q = (double*)malloc( na*sizeof(double) );

      minimum_norm_solution(ma, na, J, 1, Phi, Delta_q);

      daxpy(&ma,&underrelaxation,Delta_q,&ione,q,&ione);

    for (i=0; (dnrm2(&na,Delta_q,&ione)>NEWTON_RAPHSON_TOLERANCE)&(i<maxiterations);i++)
     {
      J=(* A)();

      Phi=(* b)();

      minimum_norm_solution(ma, na, J, 1, Phi, Delta_q);

      daxpy(&na,&underrelaxation,Delta_q,&ione,q,&ione);

//  printf("norma = %g;\t",dnrm2(&na,Delta_q,&ione) );
//  printf("iteracion %d\n",i);

     }


      free( (void *)Delta_q );

      if (i<maxiterations)
        return 0;
      else
        return 1;

}

int newton_raphson_min_norm_once (int ma, int na,
                 double * (* A)(),
                 double * (* b)(),
                 double * q)
{
      int i;
      int maxiterations=100;
      double underrelaxation=-1.0;

      double * J=NULL;

      double * Phi=NULL;

      double * Delta_q=NULL;
      int ione=1;
      i=1;
      J=(* A)();

      Phi=(* b)();


      Delta_q = (double*)malloc( na*sizeof(double) );

      minimum_norm_solution(ma, na, J, 1, Phi, Delta_q);

      daxpy(&ma,&underrelaxation,Delta_q,&ione,q,&ione);

      free( (void *)Delta_q );

      if (i<maxiterations)
        return 0;
      else
        return 1;

}

//int main (void) {printf("NEWTON_RAPHSON_TOLERANCE=%.16f\n",NEWTON_RAPHSON_TOLERANCE);}
//int main(){printf("NEWTON_RAPHSON_TOLERANCE=%f\n",NEWTON_RAPHSON_TOLERANCE);}

/* ********************************************************************************************* */
#ifdef __EXTERNAL
 #include "external_def.h"
#endif


#include "defines.h"
#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"
#include "lin_alg.h"
#include "Declare_Variables.h"

#include "get_spline_coefs.h"
#include "breaks_rail.h"
#include "breaks_wheelL.h"
#include "breaks_wheelR.h"
#include "coefs_rail.h"
#include "coefs_wheelL.h"
#include "coefs_wheelR.h"


#define param_wheelL 8
#define param_wheelR 13
#define param_railL 18
#define param_railR 23

void Initial_position_velocity_with_splines (double * q, double *dq, double * param)
{
int i;
/* Correction pos */
_PhiInit=PhiInit();
_PhiInit_q=PhiInit_q();
Solve_N_R_while_with_splines(PhiInit_q_n_rows,PhiInit_q_n_cols,&PhiInit, &PhiInit_q, q, _Inv_PhiInit_q, Bufferd, param,BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, p_vector, q_vector, BufferL, BufferPINV);

/* Correction vel */
if ( PhiInit_q_n_rows == dPhiInit_dq_n_rows ) {
  Mat_Vect_Mult(PhiInit_q_n_rows, PhiInit_q_n_cols, _PhiInit_q, dq, +1, AUX_V_Init);
  _BetaInit=BetaInit();
  for (i = 0; i < PhiInit_q_n_rows; i++){ AUX_V_Init[i] = _BetaInit[i] - AUX_V_Init[i];	}
  Mat_Vect_Mult(PhiInit_q_n_cols, PhiInit_q_n_rows, _Inv_PhiInit_q, AUX_V_Init, 1, correction_dq);
  for (i = 0; i < PhiInit_q_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	}
}
else {    
  _dPhiInit_dq =dPhiInit_dq();
  Mat_Vect_Mult(dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, dq, +1, AUX_V_Init);
  _BetaInit=BetaInit();
  for (i = 0; i < dPhiInit_dq_n_rows; i++){ AUX_V_Init[i] = _BetaInit[i] - AUX_V_Init[i];	}
  #ifndef ROBUST_INIT_SOLVER
    Mat_PInv(dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, _Inv_dPhiInit_dq, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, BufferPINV);
  #else
    Mat_PInvLU(dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, _Inv_dPhiInit_dq, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, p_vector, q_vector, BufferL, BufferU);
  #endif
  Mat_Vect_Mult(dPhiInit_dq_n_cols, dPhiInit_dq_n_rows, _Inv_dPhiInit_dq, AUX_V_Init, 1, correction_dq);
  for (i = 0; i < dPhiInit_dq_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	}
}

#ifdef TRI_LU
  #ifdef DDL
    for (i = 0; i < MXdPhi_dqZero_n_rows; i++){qv[i]=i;}
    for (i = 0; i < MXdPhi_dqZero_n_rows; i++){pv[i]=i;}
  #endif
  #ifdef DDQ
    for (i = 0; i < M_n_rows; i++){qv[i]=i;}
    for (i = 0; i < M_n_rows; i++){pv[i]=i;}
  #endif
#endif


#ifdef COORD_IND
  for (i = 0; i < dPhi_dq_n_cols; i++){perm_vel[i]=i;}
  for (i = 0; i < dPhi_dq_n_rows; i++){p_vector[i]=i;}
#endif 
}


/* ********************************************************************************************* */
/*  Solve_N_R_while_splines */ 
/* ********************************************************************************************* */

int Solve_N_R_while_with_splines(int N, int M, double * (* Vector_Eq)(), double * (* Matrix_Jac)(), double * Vector, double * Inverse, double * delta,double * param ,  double * BufferJT,double * BufferAUXCols, double * BufferAUXRows, double * BufferIAUXCols, double * BufferIAUXRows, int * p_vector, int * q_vector, double * BufferL, double * BufferPINV)
{
  int			iteration = 0, iterate = 1, i;
  /*double		delta[M];*/
  double	conv_err = 1.;
  double	* _Vector_Eq;
  double	* _Matrix_Jac;

  #define MY_CONV_CRITERION		(1e-12) /* As eq have dim of mm^2 this implies an error of 10^-4mm */
  #define FAIL_CONV_ITERATIONS	150
  #define LARGE_CONV_ERROR		10000

  #ifndef NEWTON_RAPHSON_TOLERANCE
  #define NEWTON_RAPHSON_TOLERANCE 1.0e-16
  #endif

  double conv_criterion = NEWTON_RAPHSON_TOLERANCE;

  _coefs_rail = coefs_rail();
  _breaks_rail = breaks_rail();
  _coefs_wheelL = coefs_wheelL();
  _breaks_wheelL = breaks_wheelL();
  _coefs_wheelR = coefs_wheelR();
  _breaks_wheelR = breaks_wheelR();

  while (iterate) {					/* check for large error and return error flag if no convergence */
    if ((conv_err > +LARGE_CONV_ERROR) || (conv_err < -LARGE_CONV_ERROR)) {		/* we can't converge */
      return -2;
    };

    iteration++;		/* check iteration to see if the kinematics can reach the convergence criteria */
    if (iteration > FAIL_CONV_ITERATIONS) {										/* we can't converge */
      return -5;
    }

    get_spline_coefs (param, param_wheelL, _coefs_wheelL, _breaks_wheelL, Vector[ 9 ], breaks_wheelL_n_cols, coefs_wheelL_n_rows);
    get_spline_coefs (param, param_wheelR, _coefs_wheelR, _breaks_wheelR, Vector[ 7 ], breaks_wheelR_n_cols, coefs_wheelR_n_rows);
    get_spline_coefs (param, param_railL , _coefs_rail,   _breaks_rail, Vector[ 12 ], breaks_rail_n_cols, coefs_rail_n_rows);
    get_spline_coefs (param, param_railR , _coefs_rail,   _breaks_rail, Vector[ 10 ], breaks_rail_n_cols, coefs_rail_n_rows);

    /*_Vector_Eq=Vector_Eq();*/
    /*_Matrix_Jac=Matrix_Jac();*/
    _Matrix_Jac=dPhiInit_dq();
    _Vector_Eq=PhiInit();

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









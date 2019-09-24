/* ********************************************************************************************* */
#ifdef __EXTERNAL
 #include "external_def.h"
#endif


#include "defines.h"
#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"
#include "lin_alg.h"


#include "get_spline_coefs.h"
#include "breaks_rail.h"
#include "breaks_wheelL.h"
#include "breaks_wheelR.h"
#include "coefs_rail.h"
#include "coefs_wheelL.h"
#include "coefs_wheelR.h"
#include "gen_auxcoord.h"
#include "gen_auxvel.h"
#include "gen_auxaccel.h"


int iterations_NR = NR_ITER ;
int i,j,k, iter, ti , mrank, niter;
double ddqunknowns[n_unknowns+n_gen_accel];
double AUX_V_Init[PhiInit_q_n_rows];
double BufferJT[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_cols];
double BufferAUXCols[2*dPhiInit_dq_n_cols*dPhiInit_dq_n_cols];
double BufferAUXRows[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
double BufferIAUXCols[2*dPhiInit_dq_n_cols*dPhiInit_dq_n_cols];
double BufferIAUXRows[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
double BufferPINV[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];    
double Bufferd[PhiInit_q_n_cols];
double BufferL[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
double BufferU[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
double _Inv_PhiInit_q[PhiInit_q_n_rows * PhiInit_q_n_cols];
int p_vector[dPhiInit_dq_n_rows], q_vector[dPhiInit_dq_n_cols];
double	correction_dq[dPhi_dq_n_cols];
double _Inv_dPhiInit_dq[dPhiInit_dq_n_rows * dPhiInit_dq_n_cols];
int perm_vel[MAX(Phi_q_n_cols,dPhi_dq_n_cols)];


void Initial_position_velocity_with_splines (double * q, double * s,  double *dq, double * ds, double * param)
{
int i;
/* Correction pos */
_PhiInit=PhiInit();
_PhiInit_q=PhiInit_q();
double qs[n_gen_coord + n_gen_auxcoord ];
double		deltaq[PhiInit_q_n_cols];

for (i = 0; i < n_gen_coord; i++){qs[i]=q[i];}
for (i = 0; i < n_gen_auxcoord; i++){qs[n_gen_coord + i]=s[i];}

//~ double conv_err = 0.0;
//~ conv_err =  module(PhiInit_n_rows,_PhiInit);
//~ 
 //~ 
//~ printf("conv_err = %f\n", conv_err);	
//~ 
//~ while (conv_err > 1.0e-8){
//~ 
    //~ Mat_PInv( PhiInit_q_n_rows,PhiInit_q_n_cols, _PhiInit_q, _Inv_PhiInit_q, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows,BufferPINV);
    //~ Mat_Vect_Mult(PhiInit_q_n_cols,PhiInit_q_n_rows , _Inv_PhiInit_q,_PhiInit , +1, deltaq);
//~ 
    //~ for (i=0; i<n_gen_coord + n_gen_auxcoord; i++){
      //~ qs[(i)] -= deltaq[i];             
    //~ }
    //~ PhiInit();
    //~ PhiInit_q();
//~ 
    //~ conv_err =  module(PhiInit_n_cols,_PhiInit);
//~ 
//~ }








/* Correction vel */
//~ if ( PhiInit_q_n_rows == dPhiInit_dq_n_rows ) {
  //~ Mat_Vect_Mult(PhiInit_q_n_rows, PhiInit_q_n_cols, _PhiInit_q, dq, +1, AUX_V_Init);
  //~ _BetaInit=BetaInit();
  //~ for (i = 0; i < PhiInit_q_n_rows; i++){ AUX_V_Init[i] = _BetaInit[i] - AUX_V_Init[i];	}
  //~ Mat_Vect_Mult(PhiInit_q_n_cols, PhiInit_q_n_rows, _Inv_PhiInit_q, AUX_V_Init, 1, correction_dq);
  //~ for (i = 0; i < PhiInit_q_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	}
//~ }
//~ else {    
  //~ _dPhiInit_dq =dPhiInit_dq();
  //~ Mat_Vect_Mult(dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, dq, +1, AUX_V_Init);
  //~ _BetaInit=BetaInit();
  //~ for (i = 0; i < dPhiInit_dq_n_rows; i++){ AUX_V_Init[i] = _BetaInit[i] - AUX_V_Init[i];	}
  //~ #ifndef ROBUST_INIT_SOLVER
    //~ Mat_PInv(dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, _Inv_dPhiInit_dq, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, BufferPINV);
  //~ #else
    //~ Mat_PInvLU(dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, _Inv_dPhiInit_dq, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, p_vector, q_vector, BufferL, BufferU);
  //~ #endif
  //~ Mat_Vect_Mult(dPhiInit_dq_n_cols, dPhiInit_dq_n_rows, _Inv_dPhiInit_dq, AUX_V_Init, 1, correction_dq);
  //~ for (i = 0; i < dPhiInit_dq_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	}
//~ }

//~ #ifdef TRI_LU
  //~ #ifdef DDL
    //~ for (i = 0; i < MXdPhi_dqZero_n_rows; i++){qv[i]=i;}
    //~ for (i = 0; i < MXdPhi_dqZero_n_rows; i++){pv[i]=i;}
  //~ #endif
  //~ #ifdef DDQ
    //~ for (i = 0; i < M_n_rows; i++){qv[i]=i;}
    //~ for (i = 0; i < M_n_rows; i++){pv[i]=i;}
  //~ #endif
//~ #endif
//~ 
//~ 
//~ #ifdef COORD_IND
  //~ for (i = 0; i < dPhi_dq_n_cols; i++){perm_vel[i]=i;}
  //~ for (i = 0; i < dPhi_dq_n_rows; i++){p_vector[i]=i;}
//~ #endif 
}


/* ********************************************************************************************* */
/*  Solve_N_R_while_splines */ 
/* ********************************************************************************************* */

int Solve_N_R_while_with_splines(int N, int M, double * (* Vector_Eq)(), double * (* Matrix_Jac)(), double * Vector, double * Inverse, double * delta,double * param ,  double * BufferJT,double * BufferAUXCols, double * BufferAUXRows, double * BufferIAUXCols, double * BufferIAUXRows, int * p_vector, int * q_vector, double * BufferL, double * BufferPINV)
{
  int			iteration = 0, iterate = 1, i;
  double		deltaq[M];
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



  while (iterate) {					/* check for large error and return error flag if no convergence */
    if ((conv_err > +LARGE_CONV_ERROR) || (conv_err < -LARGE_CONV_ERROR)) {		/* we can't converge */
      return -2;
    };

    iteration++;		/* check iteration to see if the kinematics can reach the convergence criteria */
    if (iteration > FAIL_CONV_ITERATIONS) {										/* we can't converge */
      return -5;
    }

    //============================================
    // With profile defined using splines
    //============================================
    //~ _coefs_rail = coefs_rail();
    //~ _breaks_rail = breaks_rail();
    //~ _coefs_wheelL = coefs_wheelL();
    //~ _breaks_wheelL = breaks_wheelL();
    //~ _coefs_wheelR = coefs_wheelR();
    //~ _breaks_wheelR = breaks_wheelR();    
    //~ 
    //~ #include "spline_wheel_and_rail_profile.c"
    //============================================


    //~ _Vector_Eq=Vector_Eq();
    //~ _Matrix_Jac=Matrix_Jac();
    _Matrix_Jac = PhiInit_q();
    _Vector_Eq = PhiInit();


    Mat_PInv( N, M, _Matrix_Jac, Inverse, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows,BufferPINV);

    Mat_Vect_Mult(M, N, Inverse, _Vector_Eq, +1, deltaq);

    for (i=0; i<M; i++)
    {                                      /* subtract delta from last iterations pos values */
      Vector[(i)] -= deltaq[i];             /* Re-calculate dep coord. */
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






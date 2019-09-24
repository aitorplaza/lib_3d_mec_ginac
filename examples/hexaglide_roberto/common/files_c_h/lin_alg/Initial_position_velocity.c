/* ********************************************************************************************* */
#ifdef __EXTERNAL
 #include "external_def.h"
#endif


#ifdef TRI
  #ifndef TRI_LU
   #define TRI_LDL
  #endif
#endif

#include "defines.h"
#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"
#include "lin_alg.h"
#include "Declare_Variables.h"


void Initial_position_velocity (double * q, double *dq)
{
int i;
/* Correction pos */
_PhiInit=PhiInit();
_PhiInit_q=PhiInit_q();
Solve_N_R_while(PhiInit_q_n_rows,PhiInit_q_n_cols,&PhiInit, &PhiInit_q, q, _Inv_PhiInit_q, Bufferd, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, p_vector, q_vector, BufferL, BufferPINV);

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

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


void Initial_position_velocity (double * q, double *dq)
{

/* ********************************************************************************************* */
/* Coord q */

int i;

	/* Correction pos */
	_PhiInit=PhiInit();
	_PhiInit_q=PhiInit_q();
    double Bufferd[PhiInit_q_n_cols];
	Solve_N_R_while(PhiInit_q_n_rows,PhiInit_q_n_cols,&PhiInit, &PhiInit_q, q, _Inv_PhiInit_q, Bufferd);

	/* Correction vel */

	if ( PhiInit_q_n_rows == dPhiInit_dq_n_rows ) {
 	    Mat_Vect_Mult(PhiInit_q_n_rows, PhiInit_q_n_cols, _PhiInit_q, dq, +1, AUX_V_dep_1);
		_BetaInit=BetaInit();
		for (i = 0; i < PhiInit_q_n_rows; i++){ AUX_V_dep_1[i] = _BetaInit[i] - AUX_V_dep_1[i];	}
		Mat_Vect_Mult(PhiInit_q_n_cols, PhiInit_q_n_rows, _Inv_PhiInit_q, AUX_V_dep_1, 1, correction_dq);
		for (i = 0; i < PhiInit_q_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	}
	}
		else{
            double BufferJT[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_cols];
            double BufferAUXCols[2*dPhiInit_dq_n_cols*dPhiInit_dq_n_cols];
            double BufferAUXRows[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
            double BufferIAUXCols[2*dPhiInit_dq_n_cols*dPhiInit_dq_n_cols];
            double BufferIAUXRows[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];

			_dPhiInit_dq =dPhiInit_dq();
			Mat_Vect_Mult(dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, dq, +1, AUX_V_dep_1);
			_BetaInit=BetaInit();
			for (i = 0; i < dPhiInit_dq_n_rows; i++){ AUX_V_dep_1[i] = _BetaInit[i] - AUX_V_dep_1[i];	}
			Mat_PInv(dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, _Inv_dPhiInit_dq, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows);
			Mat_Vect_Mult(dPhiInit_dq_n_cols, dPhiInit_dq_n_rows, _Inv_dPhiInit_dq, AUX_V_dep_1, 1, correction_dq);
			for (i = 0; i < dPhiInit_dq_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	}
		}

#ifdef COORD_IND
    double Buffer[2*Phi_d_n_cols*Phi_d_n_cols];
    Phi_d();
    Phi_z();
    Mat_Inv( Phi_d_n_rows, _Phi_d, _Inv_Phi_d, Buffer);
#endif



}

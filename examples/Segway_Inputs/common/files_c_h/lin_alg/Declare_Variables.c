#ifdef __EXTERNAL
 #include "external_def.h"
#endif

#ifndef NR_ITER
  #define NR_ITER 1
#endif

#include "Declare_Variables.h"
#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"


int iterations_NR = NR_ITER ;
int i,j,k, iter, ti , mrank, niter;
double ddqunknowns[n_unknowns+n_gen_accel];
double AUX_V_Init[dPhiInit_dq_n_rows];
double BufferJT[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_cols];
double BufferAUXCols[2*dPhiInit_dq_n_cols*dPhiInit_dq_n_cols];
double BufferAUXRows[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
double BufferIAUXCols[2*dPhiInit_dq_n_cols*dPhiInit_dq_n_cols];
double BufferIAUXRows[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
double BufferPINV[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];    
double Bufferd[PhiInit_q_n_cols];
double BufferL[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
double BufferU[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];

/* ********************************************************************************************* */
/* Coord q */
#ifdef COORD_DEP
int p_vector[dPhiInit_dq_n_rows], q_vector[dPhiInit_dq_n_cols];
	#ifdef DDL
		#ifdef INV
		double _INV_MX_aux[MXdPhi_dqZero_n_rows * MXdPhi_dqZero_n_cols];
		double Buffer[2*MXdPhi_dqZero_n_cols*MXdPhi_dqZero_n_cols];
		#endif
		#ifdef TRI_LDL
		    double Buffer3L_LDL[MXdPhi_dqZero_n_rows*MXdPhi_dqZero_n_rows];
		    double Buffer3U_LDL[MXdPhi_dqZero_n_rows*MXdPhi_dqZero_n_rows];
		    double Buffer3d_LDL[MXdPhi_dqZero_n_rows];
		    double Buffer3y_LDL[MXdPhi_dqZero_n_rows];
		#endif
		#ifdef TRI_LU
                    double Buffery_LU[Qgamma_n_rows];
                    int    qv[MXdPhi_dqZero_n_cols],  pv[MXdPhi_dqZero_n_cols];
		#endif
	#endif
	#ifdef DDQ
		double _INV_M_aux[M_n_rows * M_n_cols];
		double aux_ddq1[n_gen_accel], aux_ddq2[n_gen_accel];
		double aux_dPhi_dq_T[ M_n_rows * dPhi_dq_n_rows ];
		double bb[ dPhi_dq_n_rows ];
		double AA[ dPhi_dq_n_rows * dPhi_dq_n_rows ], INV_AA[ dPhi_dq_n_rows * dPhi_dq_n_rows ];
		double Buffer[2*M_n_rows*M_n_rows];
		#ifdef TRI
		  double Buffer3L_LDL[M_n_rows*M_n_rows];
			double Buffer3U_LDL[M_n_rows*M_n_rows];
			double Buffer3d_LDL[M_n_rows];
			double Buffer3y_LDL[M_n_rows];
			double BufferY_LDLM[M_n_rows*Phi_q_n_rows];
		#endif
		#ifdef TRI_LU
                    double Buffery_LU[Gamma_n_rows];
                    int    qv[M_n_cols],  pv[M_n_cols];
		#endif

	#endif
	double	AUX_V_dep_1[dPhi_dq_n_rows];
	double	correction_dq[dPhi_dq_n_cols];
	double _Inv_PhiInit_q[PhiInit_q_n_rows * PhiInit_q_n_cols];
	double _Inv_dPhiInit_dq[dPhiInit_dq_n_rows * dPhiInit_dq_n_cols];
	double _Inv_Phi_q[Phi_q_n_rows * Phi_q_n_cols];
	double _Inv_dPhi_dq[dPhi_dq_n_rows * dPhi_dq_n_cols];
	double Trasp_Phi_q[ Phi_q_n_rows * Phi_q_n_cols ];
	double Trasp_dPhi_dq[ dPhi_dq_n_rows * dPhi_dq_n_cols ];

  double AUX_pos[ Phi_q_n_rows * Phi_q_n_rows ];
  double aux_pos[ Phi_q_n_rows ];
  double pinv_aux_pos[ Phi_q_n_cols ];
  double AUX_vel[ dPhi_dq_n_rows * dPhi_dq_n_rows ];
  double aux_vel[ dPhi_dq_n_rows ];
  double pinv_aux_vel[ dPhi_dq_n_cols ];
  double BufferL_LDL[dPhi_dq_n_rows*dPhi_dq_n_rows];
  double BufferU_LDL[dPhi_dq_n_rows*dPhi_dq_n_rows];
  double Bufferd_LDL[dPhi_dq_n_rows];
  double Buffery_LDL[dPhi_dq_n_rows];
	
#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND
  double correction_dq[dPhi_dq_n_cols];
  double _Inv_PhiInit_q[PhiInit_q_n_rows * PhiInit_q_n_cols];
  double _Inv_dPhiInit_dq[dPhiInit_dq_n_rows * dPhiInit_dq_n_cols];
  double _Inv_Phi_q[Phi_q_n_rows * Phi_q_n_cols];
  double _Inv_dPhi_dq[dPhi_dq_n_rows * dPhi_dq_n_cols];
  //double AUX_V_dep_1[MAX(Phi_n_rows,dPhi_dq_n_rows)],AUX_V_dep_2[MAX(Phi_n_rows,dPhi_dq_n_rows)];
  double AUX_V_dep_1[n_vel_dep],AUX_V_dep_2[MAX(Phi_n_rows,dPhi_dq_n_rows)];  
  double AUX_V_indep_1[MAX(n_coord_indep,n_vel_indep)],AUX_V_indep_2[MAX(n_coord_indep,n_vel_indep)];
  double AUX_M_indep_dep_1[MAX(n_coord_indep,n_vel_indep)*MAX(Phi_n_rows,n_vel_dep)] , AUX_M_indep_dep_2[MAX(n_coord_indep,n_vel_indep)*MAX(Phi_n_rows,dPhi_dq_n_rows)];
  double AUX_M_indep_indep_1[MAX(n_coord_indep,n_vel_indep)*MAX(n_coord_indep,n_vel_indep)],AUX_M_indep_indep_2[MAX(n_coord_indep,n_vel_indep)*MAX(n_coord_indep,n_vel_indep)];
  double INV_AUX_M_indep_indep[MAX(n_coord_indep,n_vel_indep)*MAX(n_coord_indep,n_vel_indep)];
  double A[n_vel_dep*n_vel_indep];
  //double A[MAX(Phi_n_rows,dPhi_dq_n_rows)*MAX(n_coord_indep,n_vel_indep)];
  double b[MAX(Phi_n_rows,dPhi_dq_n_rows)], c[MAX(Phi_n_rows,dPhi_dq_n_rows)];
  double _MZ[MAX(n_coord_indep,n_vel_indep)*MAX(n_coord_indep,n_vel_indep)];
  double _QZ[MAX(n_coord_indep,n_vel_indep)];
  double LU[MAX(Phi_q_n_rows,dPhi_dq_n_rows)*MAX(Phi_q_n_cols,dPhi_dq_n_cols)],LUpq[MAX(Phi_q_n_rows,dPhi_dq_n_rows)*MAX(Phi_q_n_cols,dPhi_dq_n_cols)], Y[MAX(Phi_q_n_rows,dPhi_dq_n_rows) * MAX(Phi_q_n_cols,dPhi_dq_n_cols)];
  double yq[n_coord_dep],ydq[n_vel_dep],yddq[n_vel_dep],y[MAX(Phi_q_n_cols,dPhi_dq_n_cols)];
  double aux_dq[n_gen_vel],aux_ddq[n_gen_accel], aux_dq_dep[n_vel_dep];
  int i_ini ,j_ini ,i ,o[MAX(Phi_n_rows,dPhi_dq_n_rows)],p_vector[MAX(Phi_q_n_rows,dPhi_dq_n_rows)], q_vector[MAX(Phi_q_n_cols,dPhi_dq_n_cols)], perm_vel[MAX(Phi_q_n_cols,dPhi_dq_n_cols)];
  double AUX_L_dep[1*n_vel_dep],AUX_L_indep[1*n_vel_dep],b_aux[n_vel_dep*1], yL[n_vel_dep*1];
#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
#ifdef TRAPEZOIDAL
  double tqn[n_gen_coord], tqn1[n_gen_coord],delta_q[n_gen_coord] ;
  double tdqn[n_gen_vel], tdqn1[n_gen_vel], delta_dq[n_gen_vel];
  double tddqn[n_gen_accel], tddqn1[n_gen_accel];
  double sum_error_pos;
  double sum_error_vel;
  double error;
#endif
/* ********************************************************************************************* */


#ifdef __EXTERNAL
 #include "external_def.h"
#endif

#define n_coord_dep Phi_n_rows
#define n_coord_indep (n_gen_coord-n_coord_dep)
#define n_vel_dep Beta_n_rows
#define n_vel_indep (n_gen_vel-n_vel_dep)
#define n_accel_dep Gamma_n_rows
#define n_accel_indep (n_gen_accel-n_accel_dep)

#define MIN(a,b) (((a)<(b))?(a):(b))/*new*/
#define MAX(a,b) (((a)>(b))?(a):(b))/*new*/

#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"

extern int iterations_NR;
extern int i, j, k, iter, ti, mrank, niter;
extern double ddqunknowns[n_unknowns+n_gen_accel];
extern double AUX_V_Init[PhiInit_q_n_rows];
extern double BufferJT[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_cols];
extern double BufferAUXCols[2*dPhiInit_dq_n_cols*dPhiInit_dq_n_cols];
extern double BufferAUXRows[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
extern double BufferIAUXCols[2*dPhiInit_dq_n_cols*dPhiInit_dq_n_cols];
extern double BufferIAUXRows[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
extern double BufferPINV[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];    
extern double Bufferd[PhiInit_q_n_cols];
extern double BufferL[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
extern double BufferU[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
//extern double	* q;
//extern double	* dq;

/* ********************************************************************************************* */
/* Coord q */
#ifdef COORD_DEP
extern int p_vector[dPhiInit_dq_n_rows], q_vector[dPhiInit_dq_n_cols];
	#ifdef DDL
		#ifdef INV
		extern double _INV_MX_aux[MXdPhi_dqZero_n_rows * MXdPhi_dqZero_n_cols];
		extern double Buffer[2*MXdPhi_dqZero_n_cols*MXdPhi_dqZero_n_cols];
		#endif
		#ifdef TRI_LDL
		    extern double Buffer3L_LDL[MXdPhi_dqZero_n_rows*MXdPhi_dqZero_n_rows];
		    extern double Buffer3U_LDL[MXdPhi_dqZero_n_rows*MXdPhi_dqZero_n_rows];
		    extern double Buffer3d_LDL[MXdPhi_dqZero_n_rows];
		    extern double Buffer3y_LDL[MXdPhi_dqZero_n_rows];
		#endif
		#ifdef TRI_LU
                    extern double Buffery_LU[Qgamma_n_rows];
                    extern int    qv[MXdPhi_dqZero_n_cols],  pv[MXdPhi_dqZero_n_cols];
		#endif
	#endif
	#ifdef DDQ
		extern double _INV_M_aux[M_n_rows * M_n_cols];
		extern double aux_ddq1[n_gen_accel], aux_ddq2[n_gen_accel];
		extern double aux_dPhi_dq_T[ M_n_rows * dPhi_dq_n_rows ];
		extern double bb[ dPhi_dq_n_rows ];
		extern double AA[ dPhi_dq_n_rows * dPhi_dq_n_rows ], INV_AA[ dPhi_dq_n_rows * dPhi_dq_n_rows ];
		extern double Buffer[2*M_n_rows*M_n_rows];
		#ifdef TRI
		    extern double Buffer3L_LDL[M_n_rows*M_n_rows];
			extern double Buffer3U_LDL[M_n_rows*M_n_rows];
			extern double Buffer3d_LDL[M_n_rows];
			extern double Buffer3y_LDL[M_n_rows];
			extern double BufferY_LDLM[M_n_rows*Phi_q_n_rows];
		#endif
		#ifdef TRI_LU
                    extern double Buffery_LU[Gamma_n_rows];
                    extern int    qv[M_n_cols],  pv[M_n_cols];
		#endif
	#endif

  extern double	AUX_V_dep_1[dPhi_dq_n_rows];
  extern double	correction_dq[dPhi_dq_n_cols];
  extern double _Inv_PhiInit_q[PhiInit_q_n_rows * PhiInit_q_n_cols];/*new*/
  extern double _Inv_dPhiInit_dq[dPhiInit_dq_n_rows * dPhiInit_dq_n_cols];/*new*/
  extern double _Inv_Phi_q[Phi_q_n_rows * Phi_q_n_cols];
  extern double _Inv_dPhi_dq[dPhi_dq_n_rows * dPhi_dq_n_cols];
  extern double Trasp_Phi_q[ Phi_q_n_rows * Phi_q_n_cols ];
  extern double Trasp_dPhi_dq[ dPhi_dq_n_rows * dPhi_dq_n_cols ];
	
  extern double AUX_pos[ Phi_q_n_rows * Phi_q_n_rows ];
  extern double aux_pos[ Phi_q_n_rows ];
  extern double pinv_aux_pos[ Phi_q_n_cols ];
  extern double AUX_vel[ dPhi_dq_n_rows * dPhi_dq_n_rows ];
  extern double aux_vel[ dPhi_dq_n_rows ];
  extern double pinv_aux_vel[ dPhi_dq_n_cols ];
  extern double BufferL_LDL[dPhi_dq_n_rows*dPhi_dq_n_rows];
  extern double BufferU_LDL[dPhi_dq_n_rows*dPhi_dq_n_rows];
  extern double Bufferd_LDL[dPhi_dq_n_rows];
  extern double Buffery_LDL[dPhi_dq_n_rows];
#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND
  extern double	correction_dq[dPhi_dq_n_cols];
  extern double _Inv_PhiInit_q[PhiInit_q_n_rows * PhiInit_q_n_cols];
  extern double _Inv_dPhiInit_dq[dPhiInit_dq_n_rows * dPhiInit_dq_n_cols];
  extern double _Inv_Phi_q[Phi_q_n_rows * Phi_q_n_cols];
  extern double _Inv_dPhi_dq[dPhi_dq_n_rows * dPhi_dq_n_cols];
  //extern double AUX_V_dep_1[MAX(Phi_n_rows,dPhi_dq_n_rows)],AUX_V_dep_2[MAX(Phi_n_rows,dPhi_dq_n_rows)];
  extern double AUX_V_dep_1[n_vel_dep],AUX_V_dep_2[MAX(Phi_n_rows,dPhi_dq_n_rows)];  
  extern double AUX_V_indep_1[MAX(n_coord_indep,n_vel_indep)],AUX_V_indep_2[MAX(n_coord_indep,n_vel_indep)];
  extern double AUX_M_indep_dep_1[MAX(n_coord_indep,n_vel_indep)*MAX(Phi_n_rows,n_vel_dep)] , AUX_M_indep_dep_2[MAX(n_coord_indep,n_vel_indep)*MAX(Phi_n_rows,dPhi_dq_n_rows)];
  extern double AUX_M_indep_indep_1[MAX(n_coord_indep,n_vel_indep)*MAX(n_coord_indep,n_vel_indep)],AUX_M_indep_indep_2[MAX(n_coord_indep,n_vel_indep)*MAX(n_coord_indep,n_vel_indep)];
  extern double INV_AUX_M_indep_indep[MAX(n_coord_indep,n_vel_indep)*MAX(n_coord_indep,n_vel_indep)];
  extern double A[n_vel_dep*n_vel_indep];
  //extern double A[MAX(Phi_n_rows,dPhi_dq_n_rows)*MAX(n_coord_indep,n_vel_indep)];
  extern double b[MAX(Phi_n_rows,dPhi_dq_n_rows)], c[MAX(Phi_n_rows,dPhi_dq_n_rows)];
  extern double _MZ[MAX(n_coord_indep,n_vel_indep)*MAX(n_coord_indep,n_vel_indep)];
  extern double _QZ[MAX(n_coord_indep,n_vel_indep)];
  extern double LU[MAX(Phi_q_n_rows,dPhi_dq_n_rows)*MAX(Phi_q_n_cols,dPhi_dq_n_cols)],LUpq[MAX(Phi_q_n_rows,dPhi_dq_n_rows)*MAX(Phi_q_n_cols,dPhi_dq_n_cols)], Y[MAX(Phi_q_n_rows,dPhi_dq_n_rows) * MAX(Phi_q_n_cols,dPhi_dq_n_cols)];
  extern double yq[n_coord_dep],ydq[n_vel_dep],yddq[n_vel_dep],y[MAX(Phi_q_n_cols,dPhi_dq_n_cols)];
  extern double aux_dq[n_gen_vel],aux_ddq[n_gen_accel], aux_dq_dep[n_vel_dep];
  extern int i_ini ,j_ini ,i ,o[MAX(Phi_n_rows,dPhi_dq_n_rows)],p_vector[MAX(Phi_q_n_rows,dPhi_dq_n_rows)], q_vector[MAX(Phi_q_n_cols,dPhi_dq_n_cols)],  perm_vel[MAX(Phi_q_n_cols,dPhi_dq_n_cols)];
  extern double AUX_L_dep[1*n_vel_dep],AUX_L_indep[1*n_vel_dep],b_aux[n_vel_dep*1], yL[n_vel_dep*1];
#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
#ifdef TRAPEZOIDAL
  extern double tqn[n_gen_coord], tqn1[n_gen_coord],delta_q[n_gen_coord] ;
  extern double tdqn[n_gen_vel], tdqn1[n_gen_vel], delta_dq[n_gen_vel];
  extern double tddqn[n_gen_accel], tddqn1[n_gen_accel];
  extern double sum_error_pos ;
  extern double sum_error_vel ;
  extern double error         ;
#endif
/* ********************************************************************************************* */


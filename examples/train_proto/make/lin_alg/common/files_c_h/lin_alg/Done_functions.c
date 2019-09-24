#ifdef COORD_DEP

#ifndef DDL
	#ifndef DDQ
		#define DDQ
	#endif
#endif

/* FREE Includes_Init_q.c */
Done_PhiInit (  );
Done_PhiInit_q (  );
Done_BetaInit (  ) ;
Done_dPhiInit_dq (  );

/* FREE Includes_q.c */
Done_Phi (  );
Done_Beta (  ) ;
Done_Gamma (  );
Done_Phi_q (  );
Done_dPhi_dq (  );

#ifdef DDL
	Done_Qgamma (  );
	Done_MXdPhi_dqZero (  );
#endif

#ifdef DDQ
	Done_Q (  );
	Done_M (  );
#endif

	#ifdef I3AL
		Done_M (  );
		Done_Q (  );
		Done_Q_q (  );
		Done_Q_dq (  );
	#endif

#endif

#ifdef COORD_IND

/* FREE Includes_Init_z.c */
Done_Phi (  );
Done_Phi_z (  );
Done_Phi_d (  );
Done_Beta (  ) ;

/* FREE Includes_z.c */
Done_Phi (  );
Done_Beta (  ) ;
Done_Phi_z (  );
Done_Phi_d (  );
Done_Gamma (  );
Done_Qz (  );
Done_Qd (  );
Done_Mzz (  );
Done_Mzd (  );
Done_Mdd (  );

	#ifdef I3AL
		Done_Qz_z (  );
		Done_Qz_dz (  );
	#endif

#endif

#ifdef __EXTERNAL
 #include "external_def.h"
#endif

#ifdef COORD_DEP


/* FREE Includes_Init_q.c */
Init_PhiInit (  );
Init_PhiInit_q (  );
Init_BetaInit (  ) ;
Init_dPhiInit_dq (  );

/* FREE Includes_q.c */
Init_Phi (  );
Init_Beta (  ) ;
Init_Phi_q (  );
Init_dPhi_dq (  );

#ifdef DDL
	Init_Qgamma (  );
	Init_MXdPhi_dqZero (  );
#endif

#ifdef DDQ
	Init_Q (  );
	Init_M (  );
	Init_Gamma (  );
#endif

	#ifdef I3AL
		Init_M (  );
		Init_Q (  );
		Init_Q_q (  );
		Init_Q_dq (  );
		Init_Gamma (  );
	#endif

#endif

#ifdef COORD_IND

/* FREE Includes_Init_z.c */
Init_Phi (  );
Init_Phi_z (  );
Init_Phi_d (  );
Init_Beta (  ) ;

/* FREE Includes_z.c */
Init_Phi (  );
Init_Beta (  ) ;
Init_Phi_z (  );
Init_Phi_d (  );
Init_Gamma (  );
Init_Qz (  );
Init_Qd (  );
Init_Mzz (  );
Init_Mzd (  );
Init_Mdd (  );

	#ifdef I3AL
		Init_Qz_z (  );
		Init_Qz_dz (  );
	#endif

#endif

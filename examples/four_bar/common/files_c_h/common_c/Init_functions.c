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

Init_Phi (  );
Init_Beta (  ) ;
Init_Phi_q (  );
Init_dPhi_dq (  );
Init_Q (  );
Init_M (  );
Init_MQ (  );
Init_Gamma (  );

#endif

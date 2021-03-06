/* ********************************************************************************************* */
/* Coord q */
#ifdef COORD_DEP

#include "Phi.h"
#include "Beta.h"

#include "Phi_q.h"
#include "dPhi_dq.h"

#ifdef DDL
	#include "Qgamma.h"
	#include "MXdPhi_dqZero.h"
#endif

#ifdef DDQ
	#include "Q.h"
	#include "M.h"
	#include "Gamma.h"
#endif

	#ifdef I3AL
		#include "M.h"
		#include "Q.h"
		#include "Q_q.h"
		#include "Q_dq.h"
		#include "Gamma.h"
	#endif

#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND

#include "Phi.h"
#include "Beta.h"
#include "Phi_q.h"
#include "dPhi_dq.h"
#include "Gamma.h"
#include "Q.h"
#include "M.h"
#include "Gamma.h"

#endif
/* ********************************************************************************************* */

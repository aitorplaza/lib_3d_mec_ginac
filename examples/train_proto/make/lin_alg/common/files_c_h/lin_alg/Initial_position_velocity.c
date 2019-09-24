/* ********************************************************************************************* */
//#include "Includes_variables_parameters.h"
/* ********************************************************************************************* */
void Initial_position_velocity (double * q, double *dq)
{

/* Coord q */
#ifdef COORD_DEP
	Initial_position_velocity_q (q,dq);
#endif

/* Coord z */
#ifdef COORD_IND
	Initial_position_velocity_z (q,dq);
#endif

}

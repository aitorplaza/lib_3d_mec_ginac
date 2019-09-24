/* ALLOCATE MEMORY variables anad parameters */
Init_t ( ); /* Include initial value t=0.0 */
Init_param ( );
Init_q ( );
Init_dq ( );
Init_ddq ( );
Init_unknowns ( );

#ifdef INPUTS
  Init_inputs ( );
#endif

/* INITIAL VALUES variables anad parameters */
Init_param_values ( );
Init_q_values ( ); 
Init_dq_values ( ); 
Init_ddq_values ( );
Init_unknowns_values ( );

#ifdef INPUTS
  Init_inputs_values ( );
#endif

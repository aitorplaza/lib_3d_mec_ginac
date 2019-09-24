/* ALLOCATE MEMORY variables anad parameters */
Init_t ( ); /* Include initial value t=0.0 */
Init_param ( );
Init_q ( );
Init_dq ( );
Init_ddq ( );
/*#ifdef UNKNOWNS*/
  Init_unknowns ( );
/*#endif*/
#ifdef INPUTS
  Init_inputs ( );
#endif

/* INITIAL VALUES variables anad parameters */
Init_param_values ( );
Init_q_values ( ); 
Init_dq_values ( ); 
Init_ddq_values ( );
/*#ifdef UNKNOWNS*/
  Init_unknowns_values ( );
/*#endif*/
#ifdef INPUTS
  Init_inputs_values ( );
#endif

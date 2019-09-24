// ------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------

	// Position Correction (obtained q does not have to satisfy geometric constraints)
	// newton_raphson_min_norm (int ma, int na,double * (* A)(),double * (* b)(),double * q);		
	newton_raphson_min_norm(n_gen_coord,n_gen_coord,&PhiInit_q,&PhiInit,q);

	// Velocity Correction (obtained dq does not have to satisfy velocity constraints)
	_BetaInit=BetaInit();
	_dPhiInit_dq =dPhiInit_dq ();

	//    minimum_norm_correction(n_unknowns,n_gen_coord,_PhiInit_q,_PhiInit_t,dq);
    	minimum_norm_correction(n_gen_coord,n_gen_vel,_dPhiInit_dq,_BetaInit,dq);

// ------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------

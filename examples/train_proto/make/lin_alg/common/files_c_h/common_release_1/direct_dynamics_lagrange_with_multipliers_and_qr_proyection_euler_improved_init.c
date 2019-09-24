    //Solve Direct Dynamic problem using Runge Kutta and qr projection of constraints for estabilization
    //and Lagrange equation with multipliers. Dynamical system of equations are the dynamical equations
    //augmented with the constraint equations for accelerations.

// ------------------------------------------------------------------------------------------

    // Position Correction (obtained q does not have to satisfy geometric constraints)
    // newton_raphson_min_norm (int ma, int na,double * (* A)(),double * (* b)(),double * q);		
    //newton_raphson_min_norm(n_gen_coord,n_gen_coord,&PhiInit_q,&PhiInit,q);
    newton_raphson_min_norm(PhiInit_q_n_rows,PhiInit_q_n_cols,&PhiInit_q,&PhiInit,q);

    // Velocity Correction (obtained dq does not have to satisfy velocity constraints)
    _BetaInit=BetaInit();
    _dPhiInit_dq =dPhiInit_dq ();

    //minimum_norm_correction(n_unknowns,n_gen_coord,_PhiInit_q,_PhiInit_t,dq);
    //minimum_norm_correction(n_gen_coord,n_gen_vel,_dPhiInit_dq,_BetaInit,dq);
    minimum_norm_correction(dPhiInit_dq_n_rows,dPhiInit_dq_n_cols,_dPhiInit_dq,_BetaInit,dq);

// ------------------------------------------------------------------------------------------

    size_t i;

    //double * ddqunknowns;
    //ddqunknowns = malloc ( (n_unknowns+n_gen_accel) * sizeof(double) );


    double * ddqunknowns;
    ddqunknowns =(double*) malloc ( (n_unknowns+n_gen_accel) * sizeof(double) );

// --------------------------
// integration euler modified
// --------------------------
      printf("**************************************************************************\n");
      printf("* Using lagrange with multipliers and qr proyection euler improved method \n");
      printf("* Delta t = %lf seconds \n",delta_t);
      #ifndef  OSG
      printf("* Integration_time = %lf seconds \n",integration_time);
      #endif
      printf("* Precision = %lf\n",tolerance);
      printf("***************************************************************************\n");
      FILE * state_file = fopen("state.dat", "w");
      write_state_file_header(state_file);

// ------------------------------------------------------------------------------------------
//       With  OpenSceneGraph
// ------------------------------------------------------------------------------------------
         #ifdef OSG 
         //Initialization of Timers
         osg::Timer *globalHighResTimer=osg::Timer::instance();
         osg::Timer_t t_ini;
         osg::Timer_t t_fin;
         //osg::Timer_t SleepTime;
         long long SleepTime;

         while (true){
         if (running==true){
         //Get start time
         t_ini=globalHighResTimer->tick();

// ------------------------------------------------------------------------------------------
//      No  OpenSceneGraph
// ------------------------------------------------------------------------------------------
         #else 
         steps=ceil(integration_time/delta_t);
         printf("t = %g, %ld of %ld\n",t,k,steps);
         for (k=1; k<=steps; k++){
         #endif
// ------------------------------------------------------------------------------------------


        //***********************************************
        //One Step Integration
        //***********************************************

        // Dynamic problem. Unknowns are generalized accelerations ddq and lagrange multipliers unknowns
	_Qgamma=Qgamma();
        _MXdPhi_dqZero=MXdPhi_dqZero();

        // solve the system     _MPhi_qTPhi_qZero*ddqunknowns=_Qgamma
        // --------------------------------------------------------        
	//minimum_norm_solution(n_gen_accel+n_unknowns, n_gen_accel+n_unknowns,_MXdPhi_dqZero, 1,_Qgamma,ddqunknowns);
        minimum_norm_solution(MXdPhi_dqZero_n_rows, MXdPhi_dqZero_n_cols , _MXdPhi_dqZero, 1,_Qgamma,ddqunknowns);

        for (i=0; i<n_gen_accel; i++){  ddq[i]=ddqunknowns[i];    }
        for (i=0; i<n_unknowns; i++){ unknowns[i]=ddqunknowns[n_gen_accel+i]; }

        write_state_file(state_file);

        // Note at this point, time, state (q, dq), generalized accelerations (ddq) and joint
        // action unknowns (unknowns) are consistent with Dynamic Equations and Constraints except for numerical errors.

        // Position Actualization
        // q=q+dq*delta_t+1/2*ddq*delta_t*delta_t;
        for (i=0;i< n_gen_coord;i++){ q[i]+=(0.5*ddq[i]*delta_t + dq[i])*delta_t; }
        // Velocity Actualization
        // dq=dq+ddq*delta_t;
        for (i=0;i< n_gen_vel;i++){ dq[i]+=ddq[i]*delta_t; }
        // Time actualization
        t=t+delta_t;

        #ifdef UNKNOWNS
	// Position Correction (obtained q does not have to satisfy geometric constraints)
	_Phi_q=Phi_q();
	_Phi=Phi();

	//newton_raphson_min_norm_once(n_unknowns,n_gen_coord,&Phi_q,&Phi,q);
        newton_raphson_min_norm_once(Phi_q_n_rows,Phi_q_n_cols,&Phi_q,&Phi,q);

	// Velocity Correction (obtained dq does not have to satisfy velocity constraints)
	_dPhi_dq=dPhi_dq();
	_Beta=Beta();

        minimum_norm_correction(dPhi_dq_n_rows,dPhi_dq_n_cols,_dPhi_dq,_Beta,dq);
        //minimum_norm_correction(n_unknowns,n_gen_vel,_dPhi_dq,_Beta,dq);
        #endif

        //***********************************************

// ------------------------------------------------------------------------------------------
//       With  OpenSceneGraph
// ------------------------------------------------------------------------------------------
        #ifdef OSG
        //Sleep thread
        t_fin=globalHighResTimer->tick(); 
        SleepTime=1000000*delta_t-globalHighResTimer->delta_u(t_ini,t_fin);
        if(SleepTime>0) {OpenThreads::Thread::microSleep(SleepTime);}
        else {cout << "Slower than Real-Time by (us): " << -SleepTime << endl;}
        }
        else{//if not running
          OpenThreads::Thread::microSleep(1000000*delta_t);
        }
        #endif
// ------------------------------------------------------------------------------------------
    }


    fclose(state_file);
    
    free(ddqunknowns);




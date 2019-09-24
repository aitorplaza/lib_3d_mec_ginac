    //Solve Direct Dynamic problem using Runge Kutta and qr projection of constraints for estabilization
    //and Lagrange equation with multipliers. Dynamical system of equations are the dynamical equations
    //augmented with the constraint equations for accelerations.

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

    // Auxiliary iterators
    size_t i;
    long int iter;


    // Creation of auxiliary vectors
    double * qn;    qn  = (double*)malloc ( n_gen_coord * sizeof(double) );
    double * dqn;   dqn = (double*)malloc ( n_gen_coord * sizeof(double) );

    double * qaux;  qaux  = (double*)malloc ( n_gen_coord * sizeof(double) );
    double * dqaux; dqaux = (double*)malloc ( n_gen_coord * sizeof(double) );

    double * eq;    eq  = (double*)malloc ( n_gen_coord * sizeof(double) );
    double * edq;   edq  = (double*)malloc ( n_gen_coord * sizeof(double) );

    double * k1q;   k1q  = (double*)malloc ( n_gen_coord * sizeof(double) );
    double * k1dq;  k1dq = (double*)malloc ( n_gen_coord * sizeof(double) );

    double * k2q;   k2q  = (double*)malloc ( n_gen_coord * sizeof(double) );
    double * k2dq;  k2dq = (double*)malloc ( n_gen_coord * sizeof(double) );

    //double * ddqunknowns; ddqunknowns = malloc ( (n_unknowns+n_gen_accel) * sizeof(double) );

    double * ddqunknowns;
    ddqunknowns =(double*) malloc ( (n_unknowns+n_gen_accel) * sizeof(double) );

    int n_coord = n_gen_coord;
    int n_l= n_unknowns;
    int ione=1;
    double dmone= - 1.0;
//	  double trapezoidal_tolerance=1.0e-8;

#ifndef TRAPEZOIDAL_TOLERANCE
#define TRAPEZOIDAL_TOLERANCE 1.0e-8
#endif

// --------------------------
// integration trapezoidal
// --------------------------
      printf("*****************************************************************\n");
      printf("* Integrating with lagrange with multipliers trapezoidal method \n");
      printf("* Delta t = %lf seconds \n",delta_t);
      #ifndef  OSG
      printf("* Integration_time = %lf seconds \n",integration_time);
      #endif
      printf("* Precision = %lf\n",TRAPEZOIDAL_TOLERANCE);
      printf("*****************************************************************\n");
      
      //FILE * state_file = fopen("state.dat", "w");
      FILE * state_file = fopen(output_file_name, "w");      
      write_data_file_header(state_file);

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
       //printf("t = %g, %ld of %ld\n",t,k,steps);
       for (k=1; k<=steps; k++){
       #endif
// ------------------------------------------------------------------------------------------


       // copying q and dq to auxiliary vectors
       memcpy(qn,   q,   n_gen_coord*sizeof(double));
       memcpy(dqn, dq,   n_gen_vel*sizeof(double));
       memcpy(qaux, q,   n_gen_coord*sizeof(double));
       memcpy(dqaux, dq, n_gen_vel*sizeof(double));


       // Calculation of the accelerations
       _Qgamma=Qgamma();
       _MXdPhi_dqZero=MXdPhi_dqZero();
       //printf("MXdPhi_dqZero_n_rows %d\n",MXdPhi_dqZero_n_rows);
       //printf("MXdPhi_dqZero_n_cols %d\n",MXdPhi_dqZero_n_cols);
       //printf("Qgamma_n_rows %d\n",Qgamma_n_rows);
       //printf("n_gen_accel+n_unknowns %d\n",n_gen_accel+n_unknowns);
       // solve the system     _MXdPhi_dqZero*ddqunknowns=_Qgamma
       // --------------------------------------------------------
       minimum_norm_solution(MXdPhi_dqZero_n_rows, MXdPhi_dqZero_n_cols , _MXdPhi_dqZero, 1, _Qgamma,ddqunknowns);
       //minimum_norm_solution(n_gen_accel+n_unknowns, n_gen_accel+n_unknowns,_MXdPhi_dqZero, 1,_Qgamma,ddqunknowns);

       for (i=0; i<n_gen_accel; i++){  ddq[i]=ddqunknowns[i];    }
       for (i=0; i<n_unknowns; i++){ unknowns[i]=ddqunknowns[n_gen_accel+i]; }

       write_data_file(state_file);

       // Calculation of K1
       memcpy(k1q,   dq,   n_gen_coord*sizeof(double));
       memcpy(k1dq, ddq,   n_gen_coord*sizeof(double));

       // first iteration of the current time step
       // calculation of the new q and dq
       for (i=0; i<n_gen_coord; i++) {
           q[i] = qn[i] + delta_t*( k1q[i]  );
           dq[i]=dqn[i] + delta_t*( k1dq[i] );
       }

       // Calculation of the error between q and qaux in current (first) iteration
       memcpy(eq,   q,   n_gen_coord*sizeof(double));
       daxpy(&n_coord,&dmone, qaux,&ione, eq,&ione);
       memcpy(edq,   dq,   n_gen_coord*sizeof(double));
       daxpy(&n_coord,&dmone,dqaux,&ione,edq,&ione);

       iter=0;

       // warning: the total error is calculated as norm(eq)+norm(edq) and not norm( (eq,edq) )
       while ((dnrm2(&n_coord,eq,&ione)+dnrm2(&n_coord,edq,&ione))>TRAPEZOIDAL_TOLERANCE){

            memcpy(qaux, q,   n_gen_coord*sizeof(double));
            memcpy(dqaux, dq, n_gen_coord*sizeof(double));

            // Calculation of the accelerations
            _Qgamma=Qgamma();
            _MXdPhi_dqZero=MXdPhi_dqZero();

            // solve the system     _MXdPhi_dqZero*ddqunknowns=_Qgamma
            // --------------------------------------------------------

            //minimum_norm_solution(n_gen_accel+n_unknowns, n_gen_accel+n_unknowns,_MXdPhi_dqZero, 1,_Qgamma,ddqunknowns);
            minimum_norm_solution(MXdPhi_dqZero_n_rows, MXdPhi_dqZero_n_cols,_MXdPhi_dqZero, 1,_Qgamma,ddqunknowns);

            for (i=0; i<n_gen_accel; i++){  ddq[i]=ddqunknowns[i];    }
            for (i=0; i<n_unknowns; i++){ unknowns[i]=ddqunknowns[n_gen_accel+i]; }


            // Calculation of K2
            memcpy(k2q,   dq,   n_gen_coord*sizeof(double));
            memcpy(k2dq, ddq,   n_gen_coord*sizeof(double));

            for (i=0; i<n_gen_coord; i++) {
                q[i] = qn[i] + 0.5*delta_t*( k1q[i]  +  k2q[i] );
                dq[i]=dqn[i] + 0.5*delta_t*( k1dq[i] + k2dq[i] );
            }

            // Calculation of the error between q and qaux in current iteration
            memcpy(eq,   q,   n_gen_coord*sizeof(double));
            daxpy(&n_coord,&dmone,qaux,&ione,eq,&ione);
            memcpy(edq,   dq,   n_gen_coord*sizeof(double));
            daxpy(&n_coord,&dmone,dqaux,&ione,edq,&ione);

            iter++;

       }
       // time actualization
       t=t+delta_t;

       #ifdef UNKNOWNS

       // Position Correction (obtained q does not have to satisfy geometric constraints)
       //_Phi_q=Phi_q();
       //_Phi=Phi();

       //newton_raphson_min_norm_once(n_unknowns,n_gen_coord,&Phi_q,&Phi,q);
      newton_raphson_min_norm_once(Phi_q_n_rows,Phi_q_n_cols,&Phi_q,&Phi,q);

       // Velocity Correction (obtained dq does not have to satisfy velocity constraints)
       _dPhi_dq=dPhi_dq();
       _Beta=Beta();
       //minimum_norm_correction(n_unknowns,n_gen_vel,_dPhi_dq,_Beta,dq);	
       minimum_norm_correction(dPhi_dq_n_rows,dPhi_dq_n_cols,_dPhi_dq,_Beta,dq);
       #endif

//       _Phi=Phi();
//       _Energy=Energy();
//        printf("%g,%g,%16.16g,%ld;\n",t,dnrm2(&n_l,_Phi,&ione),_Energy_Equations[0],iter);
   

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

    free( (void*)qn);
    free( (void*)dqn);
    free( (void*)qaux);
    free( (void*)dqaux);
    free( (void*)eq);
    free( (void*)edq);
    free( (void*)k1q);
    free( (void*)k1dq);
    free( (void*)k2q);
    free( (void*)k2dq);





#ifdef __EXTERNAL
 #include "external_def.h"
#endif

     #ifndef TRAPEZOIDAL_TOLERANCE
      #define TRAPEZOIDAL_TOLERANCE 1.0e-8
      #endif

      //Splines
      _coefs_rail = coefs_rail();
      _breaks_rail = breaks_rail();
      _coefs_wheelL = coefs_wheelL();
      _breaks_wheelL = breaks_wheelL();
      _coefs_wheelR = coefs_wheelR();
      _breaks_wheelR = breaks_wheelR();


      // Kalker Tables
      _Table_Hertz = Table_Hertz();
      _Table_Kalker = Table_Kalker();

      // without splines
      //Initial_position_velocity(q,dq);

      Initial_position_velocity_with_splines(q,quax,dq,dqaux,param);


      #include "Solve_Dynamics.c" /* ddq for t=0 */

      //#include "kalkers_forces_calculation.c"/* Forces for t=0 */

      //printf ("1\n");Vect_Print    (n_inputs, inputs);

      #include "information_text.c"   /* Information that will be shown in the screen*/

      #ifndef TIME_ON
       FILE * data_file = fopen(output_file_name, "w");
       write_data_file_header(data_file);
       write_data_file(data_file);
      #endif
// ------------------------------------------------------------------------------------------
//       With  OpenSceneGraph
// ------------------------------------------------------------------------------------------
         #ifdef OSG
           //Initialization of Timers
           osg::Timer *globalHighResTimer=osg::Timer::instance();
           osg::Timer_t t_ini;
           osg::Timer_t t_fin;
           long long SleepTime;

           while (true){
             if (running==true){
             //Get start time
             t_ini=globalHighResTimer->tick();
         #endif
// ------------------------------------------------------------------------------------------
//     	No  OpenSceneGraph
// ------------------------------------------------------------------------------------------
         #ifndef OSG
           #ifdef TIME_ON
            start = timestamp();
           #endif
           long int k_iter;
           for (k_iter=1; k_iter<=steps; k_iter++){
         #endif
// ------------------------------------------------------------------------------------------
//      Choose integrator
// ------------------------------------------------------------------------------------------

    struct timeval total1, total2, splines1, splines2,trap1, trap2, trap3, trap4 ;
    gettimeofday(&total1, NULL);


    #ifdef EULER
       one_step_euler(delta_t,q,dq);
    #endif
    #ifdef TRAPEZOIDAL
        #include "Integration_Trapezoidal.c"
        #include "Projection.c"
        #include "Solve_Dynamics.c"
        //~ one_step_trapezoidal(delta_t,q,dq);
    #endif

    //~ printf ("=====================================\n");
    //~ Vect_Print    (n_inputs, inputs);
    //~ Vect_Print    (Output_n_rows, _Output);
    //~ Vect_Print    (n_gen_vel, dq);
    //============================================
    // With profile defined using splines
    //============================================

    //#include "spline_wheel_and_rail_profile.c"     // REalizar antes de corregir, esto sería lo mejor

    //============================================

    //============================================
    // Force as function od sliping velocity
    //============================================
    //  #include "mu_div_mod_vel_sliding_vel.c"// change code in main_symbolic.cc
    //============================================

    //============================================
    // Kalker's forces
    //============================================
    #include "kalkers_forces_calculation.c"// change code in main_symbolic.cc
    //============================================


     #ifndef TIME_ON
        t=t+delta_t;
        write_data_file(data_file);
     #endif




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

// ------------------------------------------------------------------------------------------
//     	No  OpenSceneGraph
// ------------------------------------------------------------------------------------------
        #ifndef OSG
          #ifdef TIME_ON
            end = timestamp();
          #endif
        #endif
 // ------------------------------------------------------------------------------------------

        #ifndef TIME_ON
           fclose(data_file);
        #endif

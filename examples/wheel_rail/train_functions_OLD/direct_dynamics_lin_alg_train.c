#ifdef __EXTERNAL
 #include "external_def.h"
#endif

     #ifndef TRAPEZOIDAL_TOLERANCE
      #define TRAPEZOIDAL_TOLERANCE 1.0e-8
      #endif
      
      // without splines
      //~ Initial_position_velocity(q,dq);
      
      // with splines
      Initial_position_velocity_with_splines(q,dq,param);


      #include "Solve_Dynamics.c" /* ddq for t=0 */

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
           for (k=1; k<=steps; k++){
         #endif
// ------------------------------------------------------------------------------------------
//      Choose integrator
// ------------------------------------------------------------------------------------------



     #ifdef EULER
       one_step_euler(delta_t,q,dq);
     #endif
     #ifdef TRAPEZOIDAL
       one_step_trapezoidal(delta_t,q,dq);
     #endif



     //============================================
     // With profile defined using splines
     //============================================
     #include "spline_wheel_and_rail_profile.c"     // REalizar antes de corregir, esto sería lo mejor
     //============================================ 

     //============================================
     // Force as function od sliping velocity
     //============================================
    //  #include "mu_div_mod_vel_sliding_vel.c"// change code in main_symbolic.cc
     //============================================

     //============================================    
     // Kalker's forces => To develop
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





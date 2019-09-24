#ifdef __EXTERNAL
 #include "external_def.h"
#endif

     #ifndef TRAPEZOIDAL_TOLERANCE
      #define TRAPEZOIDAL_TOLERANCE 1.0e-8
      #endif

      Initial_position_velocity(q,dq);

      #include "Solve_Dynamics.c" /* ddq for t=0 */

      #include "information_text.c"   /* Information that will be shown in the screen*/
 
      #ifndef TIME_ON
       FILE * data_file = fopen(output_file_name, "w");
       write_data_file_header(data_file);
       write_data_file(data_file);
      #endif
/* ------------------------------------------------------------------------------------------
       With  OpenSceneGraph
 ------------------------------------------------------------------------------------------*/
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
/* ------------------------------------------------------------------------------------------
     	No  OpenSceneGraph
 ------------------------------------------------------------------------------------------*/
         #ifndef OSG 
           #ifdef TIME_ON
            start = timestamp();
           #endif
           for (k=1; k<=steps; k++){
         #endif
/* ------------------------------------------------------------------------------------------
      Choose integrator
 ------------------------------------------------------------------------------------------*/

     #ifdef EULER
       one_step_euler(delta_t,q,dq);
     #endif
     #ifdef TRAPEZOIDAL
       one_step_trapezoidal_train(delta_t,q,dq);
     #endif

		   
		   
		   
		   
double Kin_Data1[17];
double Kin_Data2[17];
double Kin_Data3[17];
double Kin_Data4[17];


_Kinematics_Wheels = Kinematics_Wheels();  

printf("------------------------------------------------\n");

geom_kin_model(_Kinematics_Wheels, 0,Kin_Data1);
geom_kin_model(_Kinematics_Wheels,13,Kin_Data2);
geom_kin_model(_Kinematics_Wheels,26,Kin_Data3);
geom_kin_model(_Kinematics_Wheels,39,Kin_Data4);

inputs[0]=Kin_Data1[0];
inputs[1]=Kin_Data1[1];
inputs[2]=Kin_Data1[2];

inputs[ 9]=Kin_Data2[0];
inputs[10]=Kin_Data2[1];
inputs[11]=Kin_Data2[2];

inputs[18]=Kin_Data3[0];
inputs[19]=Kin_Data3[1];
inputs[20]=Kin_Data3[2];

inputs[27]=Kin_Data4[0];
inputs[28]=Kin_Data4[1];
inputs[29]=Kin_Data4[2];



printf("Inputs[ 0]: %1.3f\n",inputs[ 0]);
printf("Inputs[ 1]: %1.3f\n",inputs[ 1]);
printf("Inputs[ 2]: %1.3f\n",inputs[ 2]);

printf("Inputs[ 9]: %1.3f\n",inputs[ 9]);
printf("Inputs[10]: %1.3f\n",inputs[10]);
printf("Inputs[11]: %1.3f\n",inputs[11]);

printf("Inputs[18]: %1.3f\n",inputs[18]);
printf("Inputs[19]: %1.3f\n",inputs[19]);
printf("Inputs[20]: %1.3f\n",inputs[20]);

printf("Inputs[27]: %1.3f\n",inputs[27]);
printf("Inputs[28]: %1.3f\n",inputs[28]);
printf("Inputs[29]: %1.3f\n",inputs[29]);

_ContactPointVelocity = ContactPointVelocity();

// inputs calculation for wheel 1
tyre_model(Kin_Data1,inputs,0,_ContactPointVelocity,0); 	  
// inputs calculation for wheel 2
tyre_model(Kin_Data2,inputs,9,_ContactPointVelocity,3); 
// inputs calculation for wheel 3
tyre_model(Kin_Data3,inputs,18,_ContactPointVelocity,6); 
// inputs calculation for wheel 4
tyre_model(Kin_Data3,inputs,27,_ContactPointVelocity,9); 
		   
		   
	   
		   
           #ifndef TIME_ON
             t=t+delta_t;
             write_data_file(data_file);
           #endif

/* ------------------------------------------------------------------------------------------
       With  OpenSceneGraph
 ------------------------------------------------------------------------------------------*/
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
/* ------------------------------------------------------------------------------------------*/

        }  

/* ------------------------------------------------------------------------------------------
    	No  OpenSceneGraph
 ------------------------------------------------------------------------------------------*/
        #ifndef OSG   
          #ifdef TIME_ON
            end = timestamp();
          #endif
        #endif          
 /* -----------------------------------------------------------------------------------------*/

        #ifndef TIME_ON
           fclose(data_file);
        #endif





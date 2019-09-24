#ifdef __EXTERNAL
 #include "external_def.h"
#endif


    printf("**************************************************************************\n");
    printf("* state.dat  Animation \n");  
    printf("**************************************************************************\n");
    
   
    FILE * data_file;

    if((data_file = fopen(output_file_name, "r")) == NULL){
  		printf("Cannot open %s input.\n",output_file_name);
  		exit(1);
 	}
    
       
    read_data_file(data_file);
     


    //Initialization of Timers
    osg::Timer *globalHighResTimer=osg::Timer::instance();
    osg::Timer_t t_ini;
    osg::Timer_t t_fin;
    long long SleepTime;

    while (true){
        if (running==true){
            //Get start time
            t_ini=globalHighResTimer->tick();

          
            t=t+delta_t;
            fprintf(stdout,"%f\n",t);
            read_data_file(data_file);


            //Sleep thread
            t_fin=globalHighResTimer->tick(); 
            SleepTime=1000000*delta_t-globalHighResTimer->delta_u(t_ini,t_fin);

            if(SleepTime>0) {OpenThreads::Thread::microSleep(SleepTime);}
            else {cout << "Slower than Real-Time by (us): " << -SleepTime << endl;}
        }
        else{//if not running
            OpenThreads::Thread::microSleep(1000000*delta_t);
        }


    }  


       
    fclose(data_file);
       





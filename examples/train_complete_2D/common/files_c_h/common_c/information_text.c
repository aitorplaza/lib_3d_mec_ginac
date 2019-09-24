#ifdef __EXTERNAL
 #include "external_def.h"
#endif

#ifdef MATLAB_MEX_FILE
    #define printf mexPrintf
#endif 

      printf("**************************************************************************\n");
      printf("* Using LIN_ALG Math library \n");
      #ifdef COORD_DEP
        #ifdef EULER
        printf("* Using EULER explicit method with Dependent Coordinates \n");
        #endif
        #ifdef TRAPEZOIDAL
        printf("* Using TRAPEZOIDAL implicit method with Dependent Coordinates \n");
        #endif
        #ifdef TRI
        printf("* and LDL decomposition for solving linear systems \n");
        #endif
      #endif
      #ifdef COORD_IND
        #ifdef EULER
        printf("* Using EULER explicit method with Independent Velocity Formalism \n");
        #endif
        #ifdef TRAPEZOIDAL
        printf("* Using TRAPEZOIDAL implicit method with Independent Velocity Formalism \n");
        #endif
        printf("* and LU Full Pivot decomposition for coordinate partitioning and solving linear systems \n");
      #endif
      #ifdef DDL
      printf("* with Simple Formalism \n");
      #endif
      #ifdef DDQ
      printf("* with Udwadia Formalism \n");
      #endif
      #ifdef INV
      printf("* and Inverse \n");
      #endif
      printf("* Delta t = %g seconds \n",delta_t);
      #ifndef  OSG
      printf("* Integration_time = %g seconds \n",integration_time);
      #endif
      #ifdef TRAPEZOIDAL
      printf("* Precision Trapezoidal = %g\n",TRAPEZOIDAL_TOLERANCE);
      #endif
      printf("***************************************************************************\n");

#ifdef __EXTERNAL
 #include "external_def.h"
#endif

#ifdef MATLAB_MEX_FILE
    #define printf mexPrintf
#endif 

      printf("**************************************************************************\n");
      printf("* Using LIN_ALG library \n");
      #ifdef COORD_DEP
        #ifdef EULER
        printf("* Using EULER with Dependent Coordinates \n");
        #endif
        #ifdef TRAPEZOIDAL
        printf("* Using TRAPEZOIDAL with Dependent Coordinates \n");
        #endif
	#ifdef I3AL
        printf("* Using index-3 augmented Lagrangian with Dependent Coordinates \n");
        #endif
      #endif
      #ifdef COORD_IND
        #ifdef EULER
        printf("* Using EULER with Independent Coordinates \n");
        #endif
        #ifdef TRAPEZOIDAL
        printf("* Using TRAPEZOIDAL with Independent Coordinates \n");
        #endif
	#ifdef I3AL
        printf("* Using index-3 augmented Lagrangian with Independent Coordinates \n");
        #endif
      #endif
      #ifdef DDL
      printf("* with Qgamma and MXdPhi_dqZero matrices \n");
      #endif
      #ifdef DDQ
      printf("* with Q and M matrices \n");
      #endif
      #ifdef TRI
      printf("* and Cholesky decomposition \n");
      #endif
      #ifdef INV
      printf("* and Inverse \n");
      #endif
      printf("* Delta t = %g seconds \n",delta_t);
      #ifndef  OSG
      printf("* Integration_time = %g seconds \n",integration_time);
      #endif
      printf("* Precision = %g\n",TRAPEZOIDAL_TOLERANCE);
      printf("***************************************************************************\n");

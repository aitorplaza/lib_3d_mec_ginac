#define OSG
#define TIME_OFF

#include <osg/Node>
#include <osg/Group>

#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

#include <osgText/Text>
#include <osgText/Font>

#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include "solids_homogeneous_matrix.h"
#include "osg_read_file.h"
#include "osg_root.h"
#include "osg_state.h"

#include <math.h>
#include <iostream> 
#include <stdio.h>
#include <string.h>

/* ********************************************************************************************* */

extern "C" {
#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"
//#include "one_step.h"


#include "read_config_file.h"
extern void read_config_file(void);

#ifdef ANIMATION
   #include "read_data_file.h"
#else 
   #include "write_data_file.h"
#endif

#ifdef LAPACK
  #include "newton_raphson_min_norm.h"
  extern double dnrm2(int *n,double *x,int *incx);
  extern double daxpy(int * n_coord, double * dmone, double *qaux, int * ione, double * edq, int * ione2);
#endif

#ifdef LIN_ALG
  #include "Declare_Variables.h"
  #include "lin_alg.h"
  #include "timestamp.c"

  extern void Initial_position_velocity (double * q, double *dq);
   
  #ifdef EULER
    extern void one_step_euler (double delta_t, double * q, double *dq);
  #endif
  #ifdef TRAPEZOIDAL
    extern void one_step_trapezoidal (double delta_t, double * q, double *dq);
  #endif
#endif
/* ********************************************************************************************* */

/* ********************************************************************************************* */

//#include "print_mat.h"
//#include "atom_def.c"
//#include "step.c"
//#include "Energy.h"
};









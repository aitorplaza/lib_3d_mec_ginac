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



extern "C" {
extern void Init_t ( ); 
extern void Init_param ( );
extern void Init_q ( );
extern void Init_dq ( );
extern void Init_ddq ( );
extern void Init_unknowns ( );
extern void Init_inputs ( );

extern void Init_param_values ( void );
extern void Init_q_values(void );
extern void Init_dq_values (void ); 
extern void Init_ddq_values (void );
extern void Init_unknowns_values(void);
extern void Init_inputs_values(void);

extern void Init_PhiInit (  );
extern void Init_PhiInit_q (  );
extern void Init_BetaInit (  ) ;
extern void Init_dPhiInit_dq (  );

extern void Init_Phi (   );
extern void Init_Beta (  ) ;
extern void Init_Phi_q (  );
extern void Init_dPhi_dq (  );

extern void Init_Qgamma (  );
extern void Init_MXdPhi_dqZero (  );

extern void read_config_file(void);

extern double dnrm2(int *n,double *x,int *incx);
extern double daxpy(int * n_coord, double * dmone, double *qaux, int * ione, double * edq, int * ione2);


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "time.h"
#include "param.h"

#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"

#include "unknowns.h"
#include "inputs.h"


#include "Phi.h"
#include "Phi_q.h"
#include "Beta.h"
#include "dPhi_dq.h"

#include "PhiInit.h"
#include "PhiInit_q.h"
#include "BetaInit.h"
#include "dPhiInit_dq.h"


#include "Qgamma.h"
#include "MXdPhi_dqZero.h"

#include "write_data_file.h"
#include "read_config_file.h"

//#include "print_mat.h"

//#include "atom_def.c"
#include "step.c"

#include "newton_raphson_min_norm.h"

//#include "Energy.h"
};









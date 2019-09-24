/*
./compilenumericOSG.bash

g++ -o animated_osg animated_osg.cc var_def.o var_init.o gen_coord_vect_def.o gen_coord_vect_init.o gen_vel_vect_def.o gen_vel_vect_init.o gen_accel_vect_def.o gen_accel_vect_init.o param_vect_def.o param_vect_init.o unknowns_vect_def.o unknowns_vect_init.o inputs_vect_def.o inputs_vect_init.o Phi.o PhiInit.o Phi_t.o PhiInit_t.o minus_PhiInit_t.o minus_Phi_t.o Phi_q.o PhiInit_q.o Energy.o Qgamma.o MXdPhi_dqZero.o write_state_file.o write_state_file_header.o newton_raphson_min_norm.o print_mat.o Output.o solids_homogeneous_matrix.o osg_read_file.o osg_root.o osg_state.o -lOpenThreads -losg -losgDB -losgUtil -losgViewer -lm -lblas -llapack

./animated_osg 1.0 0.001 1e-8

*/
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

#include "defines.h"

#if !defined(_WIN32)
//#define dgelsd dgelsd_
//#define dgemv dgemv_
#define daxpy daxpy_
#define dnrm2 dnrm2_
#endif

#if defined(__MINGW32__)
#define dgelsd dgelsd_
#define dgemv dgemv_
#define daxpy daxpy_
#define dnrm2 dnrm2_
#endif

#define OSG

//*********************************************************************************
extern "C" {
extern void  var_init(void);

extern void gen_coord_vect_init(void);
extern void gen_vel_vect_init(void);
extern void gen_accel_vect_init(void);

extern void param_vect_init(void);

extern void unknowns_vect_init(void);
extern void inputs_vect_init(void);

extern void read_config_file(void);

extern double * Phi(void);
extern double * Phi_q(void);
extern double * Beta(void);
extern double * dPhi_dq(void);

extern double * PhiInit(void);
extern double * PhiInit_q(void);
extern double * dPhiInit_dq(void);
extern double * BetaInit(void);

extern double * Qgamma(void);
extern double * MXdPhi_dqZero(void);
extern double * Energy(void);


extern double dnrm2(int *n,double *x,int *incx);
extern double daxpy(int * n_coord, double * dmone, double *qaux, int * ione, double * edq, int * ione2);


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "var_def.h"
#include "param_vect_def.h"
#include "gen_coord_vect_def.h"
#include "gen_vel_vect_def.h"
#include "gen_accel_vect_def.h"
#include "unknowns_vect_def.h"
#include "inputs_vect_def.h"

#include "Phi.h"
#include "Phi_q.h"
#include "Beta.h"
#include "dPhi_dq.h"

#include "PhiInit.h"
#include "PhiInit_q.h"
#include "dPhiInit_dq.h"
#include "BetaInit.h"

#include "Qgamma.h"
#include "MXdPhi_dqZero.h"
#include "write_state_file_header.h"
#include "write_state_file.h"
#include "read_config_file.h"

#include "print_mat.h"

#include "atom_def.c"
#include "step.c"

#include "newton_raphson_min_norm.h"

#include "Energy.h"
};
//*********************************************************************************
using namespace std;
using namespace osg;
//*********************************************************************************
bool running=false;
//*********************************************************************************

Group * startupScene()
{
osg_read_file ();       
osg_root();
osg_state();
solids_homogeneous_matrix ();
return root;
}

//*********************************************************************************
// DynamicsThread
//*********************************************************************************
class DynamicsThread : public OpenThreads::Thread
	{
	double delta_t;
	double tolerance;

	public:
	   DynamicsThread() : OpenThreads::Thread()
	   {
	      // do something
	   }
	    
	   virtual void run()
	   {
	       OpenThreads::SetProcessorAffinityOfCurrentThread(3);

                //Initialization
		#include "inicializate_functions.c" 

		//cout<<param[8]<<endl;
		read_config_file();
		//cout<<param[8]<<endl;

		//Choose Integrator
		#ifdef EULER
		#include "direct_dynamics_lagrange_with_multipliers_and_qr_proyection_euler_improved_init.c"
		#endif

		#ifdef TRAPEZOIDAL
		#include "direct_dynamics_lagrange_with_multipliers_trapezoidal_init.c"
		#endif

               //Destruction
	   }

	   char * set_argv ( char *argv[] )
		{
		delta_t= strtod(argv[1], NULL);
		tolerance= strtod(argv[2], NULL);
		}

	};
//*********************************************************************************
class KeyboardEventHandler : public osgGA::GUIEventHandler
{
public:

    KeyboardEventHandler()
    {}

    virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&)
    {
        switch (ea.getEventType())
        {
        case(osgGA::GUIEventAdapter::KEYDOWN):
            {
                switch (ea.getKey())
                {
                case(osgGA::GUIEventAdapter::KEY_Return):
			running=!running;
                    return true;
		#ifdef INPUTS
                case 'q':
			inputs[0]=+2.5;
                    return true;
                case 'a':
			inputs[0]=-2.5;
                    return true;
                case 'w':
			inputs[1]=+10;
                    return true;
                case 's':
			inputs[1]=-10;
                    return true;
		#endif
                }
            }
        case(osgGA::GUIEventAdapter::KEYUP):
            {
                switch (ea.getKey())
                {
		#ifdef INPUTS	
                case 'q':
			inputs[0]=0;
                    return true;
                case 'a':
			inputs[0]=0;
                    return true;
                case 'w':
			inputs[1]=0;
                    return true;
                case 's':
			inputs[1]=0;
                    return true;
		#endif
                }
            }


        default:
            break;

        }	
        return false;
    }
};

//*********************************************************************************
//	main program
//*********************************************************************************
osgViewer::Viewer* viewer;


main(int argc, char *argv[]) {

if (argc!=3){
cout << "Error: The program "<<  argv[0] <<" takes two parameters: " << argv[0] << " delta_t newton-raphson-precision"<<endl;
    return 0;
}

double delta_t= strtod(argv[1], NULL);
double tolerance= strtod(argv[2], NULL);


#include "inicializate_functions.c" 

Group *scene = startupScene();

viewer = new osgViewer::Viewer();
viewer->setUpViewInWindow(0,0,1024,768);

viewer->setSceneData(scene);
viewer->setCameraManipulator(new osgGA::TrackballManipulator);
viewer->addEventHandler(new KeyboardEventHandler());
viewer->realize();

//Set color
osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
camera->setClearColor(osg::Vec4(1.0f,1.0f,1.0f,1.0f));

//Set window NAME
typedef osgViewer::Viewer::Windows Windows;
Windows windows;
viewer->getWindows(windows);
windows[0]->setWindowName(argv[0]);


//Set Dynamics Thread
DynamicsThread *DynThread = new DynamicsThread();
DynThread -> set_argv (argv);
DynThread -> start();

OpenThreads::SetProcessorAffinityOfCurrentThread(2);

//Set frame refresh time
osg::Timer *globalHighResTimer=osg::Timer::instance();
osg::Timer_t t_osg_ini;
osg::Timer_t t_osg_fin;
float update_frame = 0.04;//In seconds



while (!viewer->done()) {
//cout <<"Time = "<< t<<endl;	

	
t_osg_ini=globalHighResTimer->tick();
solids_homogeneous_matrix ();
t_osg_fin=globalHighResTimer->tick();

viewer->frame();

OpenThreads::Thread::microSleep(1000000*update_frame-globalHighResTimer->delta_u(t_osg_ini,t_osg_fin)); 


}

free(q);
free(dq);
free(ddq);

if(unknowns!=NULL)
  free(unknowns);
if(inputs!=NULL)
  free(inputs);
if(param!=NULL)
  free(param);

return 0;
}
//*********************************************************************************


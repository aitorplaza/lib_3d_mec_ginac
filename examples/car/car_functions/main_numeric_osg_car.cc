
#ifdef LAPACK
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
#endif
 
#include "defines.h"
#include "Includes_osg.h"

//*********************************************************************************

// Includes TRICICLE
extern "C" {
#include "Kinematics_Wheels.h"
#include "Geom_Kin_Model_plane.h"
#include "TyreModel.h"
#include "ContactPointVelocity.h"
}


//*********************************************************************************
using namespace std;
using namespace osg;
//*********************************************************************************
bool running=false;
const char * output_file_name="state.dat";
//*********************************************************************************

//*********************************************************************************
// DynamicsThread
//*********************************************************************************
class DynamicsThread : public OpenThreads::Thread
	{
	double delta_t;
	public:
	   DynamicsThread() : OpenThreads::Thread()
	   {
	      // do something

	   }

	   virtual void run()
	   {
	        OpenThreads::SetProcessorAffinityOfCurrentThread(3);
                //Initialization

		read_config_file();

		//Choose Integrator
		#ifdef LAPACK
		  #ifdef EULER
		   #include "direct_dynamics_lagrange_with_multipliers_and_qr_proyection_euler_improved_init.c"
		  #endif

		  #ifdef TRAPEZOIDAL
		   #include "direct_dynamics_lagrange_with_multipliers_trapezoidal_init.c"
		  #endif
		#endif

		#ifdef LIN_ALG
		  #include "direct_dynamics_lin_alg_car.c"
		#endif
               
	   }

	   char * set_argv ( char *argv[] )
		{
		delta_t= strtod(argv[1], NULL);
		}

	};
//*********************************************************************************
#include "KeyboardEventHandler.c"
//*********************************************************************************
//	main program
//*********************************************************************************
osgViewer::Viewer* viewer;

Group * startupScene()
{
osg_read_file ();       
osg_root();
osg_state();
solids_homogeneous_matrix ();

return root;
}

int main(int argc, char *argv[]) {

if (argc!=2){
cout << "Error: The program "<<  argv[0] <<" takes one parameter: " << argv[0] << " delta_t"<<endl;
    return 0;
}

double delta_t= strtod(argv[1], NULL);

#include "Init_variables_parameters.c"
#include "Init_functions.c"


// Initialize TRICICLE functions
Init_Kinematics_Wheels ( ); 
Init_ContactPointVelocity ( ) ;



Group *scene = startupScene();

viewer = new osgViewer::Viewer();
viewer->setUpViewInWindow(0,0,800,600);

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

t_osg_ini=globalHighResTimer->tick();
solids_homogeneous_matrix ();
t_osg_fin=globalHighResTimer->tick();

viewer->frame();

OpenThreads::Thread::microSleep(1000000*update_frame-globalHighResTimer->delta_u(t_osg_ini,t_osg_fin)); 


}
cout << "Simulation total time: "<< t << " seconds."<<endl;

DynThread -> cancel();

//delete DynThread;

#include "Done_variables_parameters.c"
#include "Done_functions.c"

return 0;
}

//*********************************************************************************


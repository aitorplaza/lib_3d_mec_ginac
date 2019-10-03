#define S_FUNCTION_NAME  osg_c_s_func
#define S_FUNCTION_LEVEL 2

#ifndef __linux__
#include <windows.h>
#endif

#ifdef __WIN32__
#define WIN32_LEAN_AND_MEAN
#endif

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include "simstruc.h"

#include <math.h>

#include "osg_root.h"
#include "osg_read_file.h"
#include "solids_homogeneous_matrix.h"
#include "osg_state.h"

extern "C" {
extern void Init_param_values ( void );
extern void Init_q_values ( void );
#include "param.h"
#include "gen_coord.h"
};


osgViewer::Viewer* viewer;

static void mdlInitializeSizes(SimStruct *S)
{
    int_T nInputPorts = 1, i;
    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch will be reported by Simulink */
    }
    
    ssSetNumContStates(S, 0);/*nuevo*/
    ssSetNumDiscStates(S, 0);/*nuevo*/

    if (!ssSetNumInputPorts(S, nInputPorts)) return;
    for (i=0; i<nInputPorts; i++)
    {
        ssSetInputPortWidth(S, i, DYNAMICALLY_SIZED);
        ssSetInputPortDirectFeedThrough(S, i, 1);
    }

    ssSetNumOutputPorts(S,0);

    ssSetNumSampleTimes(S, 1);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    /* Patxi removed this for using accelerated: SS_OPTION_USE_TLC_WITH_ACCELERATOR | */
    ssSetOptions(S,
                 SS_OPTION_WORKS_WITH_CODE_REUSE |
                 SS_OPTION_EXCEPTION_FREE_CODE |
                 SS_OPTION_SIM_VIEWING_DEVICE);
}



static void mdlInitializeSampleTimes(SimStruct *S)
{

    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);

}


static void mdlOutputs(SimStruct *S, int_T tid)
{
 /*InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
    real_T       *y = ssGetOutputPortRealSignal(S,0);
    int_T nPortWidth = ssGetInputPortWidth(S,0);
    int_T idxSignal;
    for (idxSignal = 0; idxSignal < nPortWidth; idxSignal++)
    {                  
    y[idxSignal] = *uPtrs[idxSignal];
    }*/
}

#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  static void mdlInitializeConditions(SimStruct *S)
  {
        Init_param();
        Init_q();
        Init_param_values();
        Init_q_values();

  }
#endif /* MDL_INITIALIZE_CONDITIONS */



#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  static void mdlStart(SimStruct *S)
  {

       osg_read_file ();      

	/*Could be good check if the files exit.*/
   
       osg_root();
       osg_state();

      viewer = new osgViewer::Viewer();
      if (viewer)
      {
          osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
          traits->x = 100;
          traits->y = 100;
          traits->width = 1024;
          traits->height = 768;
          traits->windowDecoration = true;
          traits->doubleBuffer = true;
          traits->sharedContext = 0;
          traits->windowName = "Open Scene Graph";
          
          osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
          osg::ref_ptr<osg::Camera> camera = viewer->getCamera();

          camera->setClearColor(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
          camera->setGraphicsContext(gc.get());
          camera->setViewport(new osg::Viewport(0,0, traits->width, traits->height));
          GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
          camera->setDrawBuffer(buffer);
          camera->setReadBuffer(buffer);

          osgUtil::Optimizer optimizer;
          optimizer.optimize(root);

          viewer->setSceneData(root);


          viewer->setCameraManipulator( new osgGA::TrackballManipulator );

          viewer->realize();
                  
      }
}
#endif /*  MDL_START */

#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
static void mdlUpdate(SimStruct *S, int_T tid)
    {                  
        if (!viewer->done())
        {
            int_T idxSignal;                  
            InputRealPtrsType uPtrs;
            int_T nPortWidth;
            nPortWidth = ssGetInputPortWidth(S,0);
            uPtrs = ssGetInputPortRealSignalPtrs(S,0);
            for (idxSignal = 0; idxSignal < nPortWidth; idxSignal++)
            {                  
            q[idxSignal] = *uPtrs[idxSignal];
            }
        solids_homogeneous_matrix ();

        viewer->frame(); 
      }
  }
#endif /* MDL_UPDATE */



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  static void mdlDerivatives(SimStruct *S)
  {

  }
#endif /* MDL_DERIVATIVES */



static void mdlTerminate(SimStruct *S)
{
   if (viewer)
   {
        delete viewer;
   }
       
}


#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif

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
#include "param.h"
#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
#include "unknowns.h"
#include "inputs.h"

#include "read_config_file.h"
extern void read_config_file(void);
}

using namespace std;
using namespace osg;

osgViewer::Viewer* viewer;

Group * startupScene()
{
osg_read_file ();       
osg_root();
osg_state();
solids_homogeneous_matrix ();
return root;
}


int main()
{

Init_param ( );
Init_q ( );
Init_dq ( );
Init_ddq ( );
Init_unknowns ( );
Init_inputs ( );

Init_param_values ( );
Init_q_values ( ); 
Init_dq_values ( ); 
Init_ddq_values ( ); 
Init_unknowns_values ( );
Init_inputs_values ( );

Group *scene = startupScene();

viewer = new osgViewer::Viewer();
viewer->setUpViewInWindow(0,0,1024,768);

viewer->setSceneData(scene);
viewer->setCameraManipulator(new osgGA::TrackballManipulator);
viewer->realize();

//Set color
osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
camera->setClearColor(osg::Vec4(1.0f,1.0f,1.0f,1.0f));

//Set window NAME
typedef osgViewer::Viewer::Windows Windows;
Windows windows;
viewer->getWindows(windows);
windows[0]->setWindowName("Static model");

while (!viewer->done()) {
viewer->frame();
}

#include "Done_variables_parameters.c"

return 0;

}


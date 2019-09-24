/*
gcc -c gen_coord_vect_def.c gen_coord_vect_init.c param_vect_def.c param_vect_init.c

g++ -c solids_homogeneous_matrix.cpp osg_read_file.cpp osg_root.cpp osg_state.cpp 

g++ -o modelo_osg modelo_osg.cc gen_coord_vect_def.o gen_coord_vect_init.o param_vect_init.o param_vect_def.o solids_homogeneous_matrix.o osg_read_file.o osg_root.o osg_state.o -lOpenThreads -losg -losgDB -losgUtil -losgViewer

*/

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

#include "solids_homogeneous_matrix.h"
#include "osg_read_file.h"
#include "osg_root.h"

#include <math.h>

extern "C" {
extern void param_vect_init ( void );
extern void gen_coord_vect_init ( void );
#include "param_vect_def.h"
#include "gen_coord_vect_def.h"
};

int main()
{

gen_coord_vect_init ();
param_vect_init ();

//Files
osg_read_file ();       

//q[2]=1;  

//Root tree
osg_root();

//Homogeneous Matrix
solids_homogeneous_matrix ();
	
osgViewer::Viewer visor;
visor.setSceneData(root);
			
return visor.run();
}


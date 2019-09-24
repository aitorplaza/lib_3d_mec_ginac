#ifndef __linux__
  #include <windows.h>
#endif
 
#include <osg/Group>
#include <osg/Geode>
#include <osg/MatrixTransform>
 
#include "solids_homogeneous_matrix.h"
#include "osg_read_file.h"
#include "osg_state.h"



osg::Group* root;

void osg_root ()
{
osg_state();

	
root = new osg::Group;
}

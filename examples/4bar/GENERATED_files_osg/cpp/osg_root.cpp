#ifndef __linux__
  #include <windows.h>
#endif
 
#include <osg/Group>
#include <osg/Geode>
#include <osg/MatrixTransform>
 
#include "solids_homogeneous_matrix.h"
#include "osg_read_file.h"
#include "osg_state.h"

osg::MatrixTransform* MTrans_Fra_DFra_arm1_draw;
osg::MatrixTransform* MTrans_Fra_DFra_arm2_draw;
osg::MatrixTransform* MTrans_Fra_DFra_arm3_draw;
osg::MatrixTransform* MTrans_Fra_FraABS_draw;
osg::MatrixTransform* MTrans_Fra_FraABS2_draw;
osg::MatrixTransform* MTrans_Vec_Varm1;
osg::MatrixTransform* MTrans_Vec_Varm2;
osg::MatrixTransform* MTrans_Vec_Varm3;
osg::MatrixTransform* MTrans_Vec_Varm4;
osg::MatrixTransform* MTrans_Vec_VOL2_OL3;

osg::Group* Fra_DFra_arm1_draw_axis;
osg::Group* Fra_DFra_arm2_draw_axis;
osg::Group* Fra_DFra_arm3_draw_axis;
osg::Group* Fra_FraABS_draw_axis;
osg::Group* Fra_FraABS2_draw_axis;
osg::Group* Vec_Varm1_axis;
osg::Group* Vec_Varm2_axis;
osg::Group* Vec_Varm3_axis;
osg::Group* Vec_Varm4_axis;
osg::Group* Vec_VOL2_OL3_axis;

osg::Group* root;

void osg_root ()
{
osg_state();

Fra_DFra_arm1_draw_axis = new osg::Group;
Fra_DFra_arm1_draw_axis -> addChild(Fra_DFra_arm1_draw);
MTrans_Fra_DFra_arm1_draw = new osg::MatrixTransform(MFra_DFra_arm1_draw);
MTrans_Fra_DFra_arm1_draw->addChild(Fra_DFra_arm1_draw);
	
Fra_DFra_arm2_draw_axis = new osg::Group;
Fra_DFra_arm2_draw_axis -> addChild(Fra_DFra_arm2_draw);
MTrans_Fra_DFra_arm2_draw = new osg::MatrixTransform(MFra_DFra_arm2_draw);
MTrans_Fra_DFra_arm2_draw->addChild(Fra_DFra_arm2_draw);
	
Fra_DFra_arm3_draw_axis = new osg::Group;
Fra_DFra_arm3_draw_axis -> addChild(Fra_DFra_arm3_draw);
MTrans_Fra_DFra_arm3_draw = new osg::MatrixTransform(MFra_DFra_arm3_draw);
MTrans_Fra_DFra_arm3_draw->addChild(Fra_DFra_arm3_draw);
	
Fra_FraABS_draw_axis = new osg::Group;
Fra_FraABS_draw_axis -> addChild(Fra_FraABS_draw);
MTrans_Fra_FraABS_draw = new osg::MatrixTransform(MFra_FraABS_draw);
MTrans_Fra_FraABS_draw->addChild(Fra_FraABS_draw);
	
Fra_FraABS2_draw_axis = new osg::Group;
Fra_FraABS2_draw_axis -> addChild(Fra_FraABS2_draw);
MTrans_Fra_FraABS2_draw = new osg::MatrixTransform(MFra_FraABS2_draw);
MTrans_Fra_FraABS2_draw->addChild(Fra_FraABS2_draw);
	
Vec_Varm1_axis = new osg::Group;
Vec_Varm1_axis -> addChild(Vec_Varm1);
MTrans_Vec_Varm1 = new osg::MatrixTransform(MVec_Varm1);
MTrans_Vec_Varm1->addChild(Vec_Varm1);
	
Vec_Varm2_axis = new osg::Group;
Vec_Varm2_axis -> addChild(Vec_Varm2);
MTrans_Vec_Varm2 = new osg::MatrixTransform(MVec_Varm2);
MTrans_Vec_Varm2->addChild(Vec_Varm2);
	
Vec_Varm3_axis = new osg::Group;
Vec_Varm3_axis -> addChild(Vec_Varm3);
MTrans_Vec_Varm3 = new osg::MatrixTransform(MVec_Varm3);
MTrans_Vec_Varm3->addChild(Vec_Varm3);
	
Vec_Varm4_axis = new osg::Group;
Vec_Varm4_axis -> addChild(Vec_Varm4);
MTrans_Vec_Varm4 = new osg::MatrixTransform(MVec_Varm4);
MTrans_Vec_Varm4->addChild(Vec_Varm4);
	
Vec_VOL2_OL3_axis = new osg::Group;
Vec_VOL2_OL3_axis -> addChild(Vec_VOL2_OL3);
MTrans_Vec_VOL2_OL3 = new osg::MatrixTransform(MVec_VOL2_OL3);
MTrans_Vec_VOL2_OL3->addChild(Vec_VOL2_OL3);
	
	
root = new osg::Group;
root->addChild(MTrans_Fra_DFra_arm1_draw);
root->addChild(MTrans_Fra_DFra_arm2_draw);
root->addChild(MTrans_Fra_DFra_arm3_draw);
root->addChild(MTrans_Fra_FraABS_draw);
root->addChild(MTrans_Fra_FraABS2_draw);
root->addChild(MTrans_Vec_Varm1);
root->addChild(MTrans_Vec_Varm2);
root->addChild(MTrans_Vec_Varm3);
root->addChild(MTrans_Vec_Varm4);
root->addChild(MTrans_Vec_VOL2_OL3);
}

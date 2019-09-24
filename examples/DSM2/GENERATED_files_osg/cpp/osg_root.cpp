#ifndef __linux__
  #include <windows.h>
#endif
 
#include <osg/Group>
#include <osg/Geode>
#include <osg/MatrixTransform>
 
#include "solids_homogeneous_matrix.h"
#include "osg_read_file.h"
#include "osg_state.h"

osg::MatrixTransform* MTrans_Sol_Arm1_3D;
osg::MatrixTransform* MTrans_Sol_Arm2_3D;
osg::MatrixTransform* MTrans_Sol_Plane_3D;
osg::MatrixTransform* MTrans_Sol_Disc_3D;
osg::MatrixTransform* MTrans_Fra_FraARM1_draw;
osg::MatrixTransform* MTrans_Fra_FraARM2_draw;
osg::MatrixTransform* MTrans_Fra_FraDISC_draw;
osg::MatrixTransform* MTrans_Fra_FraPLANE_draw;
osg::MatrixTransform* MTrans_Fra_FraABS_draw;

osg::Group* Sol_Arm1_3D_axis;
osg::Group* Sol_Arm2_3D_axis;
osg::Group* Sol_Plane_3D_axis;
osg::Group* Sol_Disc_3D_axis;
osg::Group* Fra_FraARM1_draw_axis;
osg::Group* Fra_FraARM2_draw_axis;
osg::Group* Fra_FraDISC_draw_axis;
osg::Group* Fra_FraPLANE_draw_axis;
osg::Group* Fra_FraABS_draw_axis;

osg::Group* root;

void osg_root ()
{
osg_state();

Sol_Arm1_3D_axis = new osg::Group;
Sol_Arm1_3D_axis->addChild(Sol_Arm1_3D);
Sol_Arm1_3D_axis->addChild(axis);
MTrans_Sol_Arm1_3D = new osg::MatrixTransform(MSol_Arm1_3D);
MTrans_Sol_Arm1_3D->addChild(Sol_Arm1_3D_axis);
	
Sol_Arm2_3D_axis = new osg::Group;
Sol_Arm2_3D_axis->addChild(Sol_Arm2_3D);
Sol_Arm2_3D_axis->addChild(axis);
MTrans_Sol_Arm2_3D = new osg::MatrixTransform(MSol_Arm2_3D);
MTrans_Sol_Arm2_3D->addChild(Sol_Arm2_3D_axis);
	
Sol_Plane_3D_axis = new osg::Group;
Sol_Plane_3D_axis->addChild(Sol_Plane_3D);
Sol_Plane_3D_axis->addChild(axis);
MTrans_Sol_Plane_3D = new osg::MatrixTransform(MSol_Plane_3D);
MTrans_Sol_Plane_3D->addChild(Sol_Plane_3D_axis);
	
Sol_Disc_3D_axis = new osg::Group;
Sol_Disc_3D_axis->addChild(Sol_Disc_3D);
Sol_Disc_3D_axis->addChild(axis);
MTrans_Sol_Disc_3D = new osg::MatrixTransform(MSol_Disc_3D);
MTrans_Sol_Disc_3D->addChild(Sol_Disc_3D_axis);
	
Fra_FraARM1_draw_axis = new osg::Group;
Fra_FraARM1_draw_axis -> addChild(Fra_FraARM1_draw);
MTrans_Fra_FraARM1_draw = new osg::MatrixTransform(MFra_FraARM1_draw);
MTrans_Fra_FraARM1_draw->addChild(Fra_FraARM1_draw);
	
Fra_FraARM2_draw_axis = new osg::Group;
Fra_FraARM2_draw_axis -> addChild(Fra_FraARM2_draw);
MTrans_Fra_FraARM2_draw = new osg::MatrixTransform(MFra_FraARM2_draw);
MTrans_Fra_FraARM2_draw->addChild(Fra_FraARM2_draw);
	
Fra_FraDISC_draw_axis = new osg::Group;
Fra_FraDISC_draw_axis -> addChild(Fra_FraDISC_draw);
MTrans_Fra_FraDISC_draw = new osg::MatrixTransform(MFra_FraDISC_draw);
MTrans_Fra_FraDISC_draw->addChild(Fra_FraDISC_draw);
	
Fra_FraPLANE_draw_axis = new osg::Group;
Fra_FraPLANE_draw_axis -> addChild(Fra_FraPLANE_draw);
MTrans_Fra_FraPLANE_draw = new osg::MatrixTransform(MFra_FraPLANE_draw);
MTrans_Fra_FraPLANE_draw->addChild(Fra_FraPLANE_draw);
	
Fra_FraABS_draw_axis = new osg::Group;
Fra_FraABS_draw_axis -> addChild(Fra_FraABS_draw);
MTrans_Fra_FraABS_draw = new osg::MatrixTransform(MFra_FraABS_draw);
MTrans_Fra_FraABS_draw->addChild(Fra_FraABS_draw);
	
	
root = new osg::Group;
root->addChild(MTrans_Sol_Arm1_3D);
root->addChild(MTrans_Sol_Arm2_3D);
root->addChild(MTrans_Sol_Plane_3D);
root->addChild(MTrans_Sol_Disc_3D);
root->addChild(MTrans_Fra_FraARM1_draw);
root->addChild(MTrans_Fra_FraARM2_draw);
root->addChild(MTrans_Fra_FraDISC_draw);
root->addChild(MTrans_Fra_FraPLANE_draw);
root->addChild(MTrans_Fra_FraABS_draw);
}

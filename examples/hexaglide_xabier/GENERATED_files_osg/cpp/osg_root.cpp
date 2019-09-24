#ifndef __linux__
  #include <windows.h>
#endif
 
#include <osg/Group>
#include <osg/Geode>
#include <osg/MatrixTransform>
 
#include "solids_homogeneous_matrix.h"
#include "osg_read_file.h"
#include "osg_state.h"

osg::MatrixTransform* MTrans_Sol_PLATFORM_3D;
osg::MatrixTransform* MTrans_Sol_BAR1_3D;
osg::MatrixTransform* MTrans_Sol_BAR2_3D;
osg::MatrixTransform* MTrans_Sol_BAR3_3D;
osg::MatrixTransform* MTrans_Sol_BAR4_3D;
osg::MatrixTransform* MTrans_Sol_BAR5_3D;
osg::MatrixTransform* MTrans_Sol_BAR6_3D;
osg::MatrixTransform* MTrans_Sol_BAR1V_3D;
osg::MatrixTransform* MTrans_Sol_BAR2V_3D;
osg::MatrixTransform* MTrans_Sol_BAR3V_3D;
osg::MatrixTransform* MTrans_Sol_BAR4V_3D;
osg::MatrixTransform* MTrans_Sol_BAR5V_3D;
osg::MatrixTransform* MTrans_Sol_BAR6V_3D;
osg::MatrixTransform* MTrans_Sol_BALL1A_3D;
osg::MatrixTransform* MTrans_Sol_BALL2A_3D;
osg::MatrixTransform* MTrans_Sol_BALL3A_3D;
osg::MatrixTransform* MTrans_Sol_BALL4A_3D;
osg::MatrixTransform* MTrans_Sol_BALL5A_3D;
osg::MatrixTransform* MTrans_Sol_BALL6A_3D;
osg::MatrixTransform* MTrans_Sol_BALL1D_3D;
osg::MatrixTransform* MTrans_Sol_BALL2D_3D;
osg::MatrixTransform* MTrans_Sol_BALL3D_3D;
osg::MatrixTransform* MTrans_Sol_BALL4D_3D;
osg::MatrixTransform* MTrans_Sol_BALL5D_3D;
osg::MatrixTransform* MTrans_Sol_BALL6D_3D;
osg::MatrixTransform* MTrans_Sol_BALL1C_3D;
osg::MatrixTransform* MTrans_Sol_BALL2C_3D;
osg::MatrixTransform* MTrans_Sol_BALL3C_3D;
osg::MatrixTransform* MTrans_Sol_BALL4C_3D;
osg::MatrixTransform* MTrans_Sol_BALL5C_3D;
osg::MatrixTransform* MTrans_Sol_BALL6C_3D;
osg::MatrixTransform* MTrans_Fra_Fra_PLATFORM_3D_draw;
osg::MatrixTransform* MTrans_Fra_Fra_BAR1_3D_draw;
osg::MatrixTransform* MTrans_Fra_Fra_BAR2_3D_draw;
osg::MatrixTransform* MTrans_Fra_Fra_BAR3_3D_draw;
osg::MatrixTransform* MTrans_Fra_Fra_BAR4_3D_draw;
osg::MatrixTransform* MTrans_Fra_Fra_BAR5_3D_draw;
osg::MatrixTransform* MTrans_Fra_Fra_BAR6_3D_draw;

osg::Group* Sol_PLATFORM_3D_axis;
osg::Group* Sol_BAR1_3D_axis;
osg::Group* Sol_BAR2_3D_axis;
osg::Group* Sol_BAR3_3D_axis;
osg::Group* Sol_BAR4_3D_axis;
osg::Group* Sol_BAR5_3D_axis;
osg::Group* Sol_BAR6_3D_axis;
osg::Group* Sol_BAR1V_3D_axis;
osg::Group* Sol_BAR2V_3D_axis;
osg::Group* Sol_BAR3V_3D_axis;
osg::Group* Sol_BAR4V_3D_axis;
osg::Group* Sol_BAR5V_3D_axis;
osg::Group* Sol_BAR6V_3D_axis;
osg::Group* Sol_BALL1A_3D_axis;
osg::Group* Sol_BALL2A_3D_axis;
osg::Group* Sol_BALL3A_3D_axis;
osg::Group* Sol_BALL4A_3D_axis;
osg::Group* Sol_BALL5A_3D_axis;
osg::Group* Sol_BALL6A_3D_axis;
osg::Group* Sol_BALL1D_3D_axis;
osg::Group* Sol_BALL2D_3D_axis;
osg::Group* Sol_BALL3D_3D_axis;
osg::Group* Sol_BALL4D_3D_axis;
osg::Group* Sol_BALL5D_3D_axis;
osg::Group* Sol_BALL6D_3D_axis;
osg::Group* Sol_BALL1C_3D_axis;
osg::Group* Sol_BALL2C_3D_axis;
osg::Group* Sol_BALL3C_3D_axis;
osg::Group* Sol_BALL4C_3D_axis;
osg::Group* Sol_BALL5C_3D_axis;
osg::Group* Sol_BALL6C_3D_axis;
osg::Group* Fra_Fra_PLATFORM_3D_draw_axis;
osg::Group* Fra_Fra_BAR1_3D_draw_axis;
osg::Group* Fra_Fra_BAR2_3D_draw_axis;
osg::Group* Fra_Fra_BAR3_3D_draw_axis;
osg::Group* Fra_Fra_BAR4_3D_draw_axis;
osg::Group* Fra_Fra_BAR5_3D_draw_axis;
osg::Group* Fra_Fra_BAR6_3D_draw_axis;

osg::Group* root;

void osg_root ()
{
osg_state();

Sol_PLATFORM_3D_axis = new osg::Group;
Sol_PLATFORM_3D_axis->addChild(Sol_PLATFORM_3D);
Sol_PLATFORM_3D_axis->addChild(axis);
MTrans_Sol_PLATFORM_3D = new osg::MatrixTransform(MSol_PLATFORM_3D);
MTrans_Sol_PLATFORM_3D->addChild(Sol_PLATFORM_3D_axis);
	
Sol_BAR1_3D_axis = new osg::Group;
Sol_BAR1_3D_axis->addChild(Sol_BAR1_3D);
Sol_BAR1_3D_axis->addChild(axis);
MTrans_Sol_BAR1_3D = new osg::MatrixTransform(MSol_BAR1_3D);
MTrans_Sol_BAR1_3D->addChild(Sol_BAR1_3D_axis);
	
Sol_BAR2_3D_axis = new osg::Group;
Sol_BAR2_3D_axis->addChild(Sol_BAR2_3D);
Sol_BAR2_3D_axis->addChild(axis);
MTrans_Sol_BAR2_3D = new osg::MatrixTransform(MSol_BAR2_3D);
MTrans_Sol_BAR2_3D->addChild(Sol_BAR2_3D_axis);
	
Sol_BAR3_3D_axis = new osg::Group;
Sol_BAR3_3D_axis->addChild(Sol_BAR3_3D);
Sol_BAR3_3D_axis->addChild(axis);
MTrans_Sol_BAR3_3D = new osg::MatrixTransform(MSol_BAR3_3D);
MTrans_Sol_BAR3_3D->addChild(Sol_BAR3_3D_axis);
	
Sol_BAR4_3D_axis = new osg::Group;
Sol_BAR4_3D_axis->addChild(Sol_BAR4_3D);
Sol_BAR4_3D_axis->addChild(axis);
MTrans_Sol_BAR4_3D = new osg::MatrixTransform(MSol_BAR4_3D);
MTrans_Sol_BAR4_3D->addChild(Sol_BAR4_3D_axis);
	
Sol_BAR5_3D_axis = new osg::Group;
Sol_BAR5_3D_axis->addChild(Sol_BAR5_3D);
Sol_BAR5_3D_axis->addChild(axis);
MTrans_Sol_BAR5_3D = new osg::MatrixTransform(MSol_BAR5_3D);
MTrans_Sol_BAR5_3D->addChild(Sol_BAR5_3D_axis);
	
Sol_BAR6_3D_axis = new osg::Group;
Sol_BAR6_3D_axis->addChild(Sol_BAR6_3D);
Sol_BAR6_3D_axis->addChild(axis);
MTrans_Sol_BAR6_3D = new osg::MatrixTransform(MSol_BAR6_3D);
MTrans_Sol_BAR6_3D->addChild(Sol_BAR6_3D_axis);
	
Sol_BAR1V_3D_axis = new osg::Group;
Sol_BAR1V_3D_axis->addChild(Sol_BAR1V_3D);
Sol_BAR1V_3D_axis->addChild(axis);
MTrans_Sol_BAR1V_3D = new osg::MatrixTransform(MSol_BAR1V_3D);
MTrans_Sol_BAR1V_3D->addChild(Sol_BAR1V_3D_axis);
	
Sol_BAR2V_3D_axis = new osg::Group;
Sol_BAR2V_3D_axis->addChild(Sol_BAR2V_3D);
Sol_BAR2V_3D_axis->addChild(axis);
MTrans_Sol_BAR2V_3D = new osg::MatrixTransform(MSol_BAR2V_3D);
MTrans_Sol_BAR2V_3D->addChild(Sol_BAR2V_3D_axis);
	
Sol_BAR3V_3D_axis = new osg::Group;
Sol_BAR3V_3D_axis->addChild(Sol_BAR3V_3D);
Sol_BAR3V_3D_axis->addChild(axis);
MTrans_Sol_BAR3V_3D = new osg::MatrixTransform(MSol_BAR3V_3D);
MTrans_Sol_BAR3V_3D->addChild(Sol_BAR3V_3D_axis);
	
Sol_BAR4V_3D_axis = new osg::Group;
Sol_BAR4V_3D_axis->addChild(Sol_BAR4V_3D);
Sol_BAR4V_3D_axis->addChild(axis);
MTrans_Sol_BAR4V_3D = new osg::MatrixTransform(MSol_BAR4V_3D);
MTrans_Sol_BAR4V_3D->addChild(Sol_BAR4V_3D_axis);
	
Sol_BAR5V_3D_axis = new osg::Group;
Sol_BAR5V_3D_axis->addChild(Sol_BAR5V_3D);
Sol_BAR5V_3D_axis->addChild(axis);
MTrans_Sol_BAR5V_3D = new osg::MatrixTransform(MSol_BAR5V_3D);
MTrans_Sol_BAR5V_3D->addChild(Sol_BAR5V_3D_axis);
	
Sol_BAR6V_3D_axis = new osg::Group;
Sol_BAR6V_3D_axis->addChild(Sol_BAR6V_3D);
Sol_BAR6V_3D_axis->addChild(axis);
MTrans_Sol_BAR6V_3D = new osg::MatrixTransform(MSol_BAR6V_3D);
MTrans_Sol_BAR6V_3D->addChild(Sol_BAR6V_3D_axis);
	
Sol_BALL1A_3D_axis = new osg::Group;
Sol_BALL1A_3D_axis->addChild(Sol_BALL1A_3D);
Sol_BALL1A_3D_axis->addChild(axis);
MTrans_Sol_BALL1A_3D = new osg::MatrixTransform(MSol_BALL1A_3D);
MTrans_Sol_BALL1A_3D->addChild(Sol_BALL1A_3D_axis);
	
Sol_BALL2A_3D_axis = new osg::Group;
Sol_BALL2A_3D_axis->addChild(Sol_BALL2A_3D);
Sol_BALL2A_3D_axis->addChild(axis);
MTrans_Sol_BALL2A_3D = new osg::MatrixTransform(MSol_BALL2A_3D);
MTrans_Sol_BALL2A_3D->addChild(Sol_BALL2A_3D_axis);
	
Sol_BALL3A_3D_axis = new osg::Group;
Sol_BALL3A_3D_axis->addChild(Sol_BALL3A_3D);
Sol_BALL3A_3D_axis->addChild(axis);
MTrans_Sol_BALL3A_3D = new osg::MatrixTransform(MSol_BALL3A_3D);
MTrans_Sol_BALL3A_3D->addChild(Sol_BALL3A_3D_axis);
	
Sol_BALL4A_3D_axis = new osg::Group;
Sol_BALL4A_3D_axis->addChild(Sol_BALL4A_3D);
Sol_BALL4A_3D_axis->addChild(axis);
MTrans_Sol_BALL4A_3D = new osg::MatrixTransform(MSol_BALL4A_3D);
MTrans_Sol_BALL4A_3D->addChild(Sol_BALL4A_3D_axis);
	
Sol_BALL5A_3D_axis = new osg::Group;
Sol_BALL5A_3D_axis->addChild(Sol_BALL5A_3D);
Sol_BALL5A_3D_axis->addChild(axis);
MTrans_Sol_BALL5A_3D = new osg::MatrixTransform(MSol_BALL5A_3D);
MTrans_Sol_BALL5A_3D->addChild(Sol_BALL5A_3D_axis);
	
Sol_BALL6A_3D_axis = new osg::Group;
Sol_BALL6A_3D_axis->addChild(Sol_BALL6A_3D);
Sol_BALL6A_3D_axis->addChild(axis);
MTrans_Sol_BALL6A_3D = new osg::MatrixTransform(MSol_BALL6A_3D);
MTrans_Sol_BALL6A_3D->addChild(Sol_BALL6A_3D_axis);
	
Sol_BALL1D_3D_axis = new osg::Group;
Sol_BALL1D_3D_axis->addChild(Sol_BALL1D_3D);
Sol_BALL1D_3D_axis->addChild(axis);
MTrans_Sol_BALL1D_3D = new osg::MatrixTransform(MSol_BALL1D_3D);
MTrans_Sol_BALL1D_3D->addChild(Sol_BALL1D_3D_axis);
	
Sol_BALL2D_3D_axis = new osg::Group;
Sol_BALL2D_3D_axis->addChild(Sol_BALL2D_3D);
Sol_BALL2D_3D_axis->addChild(axis);
MTrans_Sol_BALL2D_3D = new osg::MatrixTransform(MSol_BALL2D_3D);
MTrans_Sol_BALL2D_3D->addChild(Sol_BALL2D_3D_axis);
	
Sol_BALL3D_3D_axis = new osg::Group;
Sol_BALL3D_3D_axis->addChild(Sol_BALL3D_3D);
Sol_BALL3D_3D_axis->addChild(axis);
MTrans_Sol_BALL3D_3D = new osg::MatrixTransform(MSol_BALL3D_3D);
MTrans_Sol_BALL3D_3D->addChild(Sol_BALL3D_3D_axis);
	
Sol_BALL4D_3D_axis = new osg::Group;
Sol_BALL4D_3D_axis->addChild(Sol_BALL4D_3D);
Sol_BALL4D_3D_axis->addChild(axis);
MTrans_Sol_BALL4D_3D = new osg::MatrixTransform(MSol_BALL4D_3D);
MTrans_Sol_BALL4D_3D->addChild(Sol_BALL4D_3D_axis);
	
Sol_BALL5D_3D_axis = new osg::Group;
Sol_BALL5D_3D_axis->addChild(Sol_BALL5D_3D);
Sol_BALL5D_3D_axis->addChild(axis);
MTrans_Sol_BALL5D_3D = new osg::MatrixTransform(MSol_BALL5D_3D);
MTrans_Sol_BALL5D_3D->addChild(Sol_BALL5D_3D_axis);
	
Sol_BALL6D_3D_axis = new osg::Group;
Sol_BALL6D_3D_axis->addChild(Sol_BALL6D_3D);
Sol_BALL6D_3D_axis->addChild(axis);
MTrans_Sol_BALL6D_3D = new osg::MatrixTransform(MSol_BALL6D_3D);
MTrans_Sol_BALL6D_3D->addChild(Sol_BALL6D_3D_axis);
	
Sol_BALL1C_3D_axis = new osg::Group;
Sol_BALL1C_3D_axis->addChild(Sol_BALL1C_3D);
Sol_BALL1C_3D_axis->addChild(axis);
MTrans_Sol_BALL1C_3D = new osg::MatrixTransform(MSol_BALL1C_3D);
MTrans_Sol_BALL1C_3D->addChild(Sol_BALL1C_3D_axis);
	
Sol_BALL2C_3D_axis = new osg::Group;
Sol_BALL2C_3D_axis->addChild(Sol_BALL2C_3D);
Sol_BALL2C_3D_axis->addChild(axis);
MTrans_Sol_BALL2C_3D = new osg::MatrixTransform(MSol_BALL2C_3D);
MTrans_Sol_BALL2C_3D->addChild(Sol_BALL2C_3D_axis);
	
Sol_BALL3C_3D_axis = new osg::Group;
Sol_BALL3C_3D_axis->addChild(Sol_BALL3C_3D);
Sol_BALL3C_3D_axis->addChild(axis);
MTrans_Sol_BALL3C_3D = new osg::MatrixTransform(MSol_BALL3C_3D);
MTrans_Sol_BALL3C_3D->addChild(Sol_BALL3C_3D_axis);
	
Sol_BALL4C_3D_axis = new osg::Group;
Sol_BALL4C_3D_axis->addChild(Sol_BALL4C_3D);
Sol_BALL4C_3D_axis->addChild(axis);
MTrans_Sol_BALL4C_3D = new osg::MatrixTransform(MSol_BALL4C_3D);
MTrans_Sol_BALL4C_3D->addChild(Sol_BALL4C_3D_axis);
	
Sol_BALL5C_3D_axis = new osg::Group;
Sol_BALL5C_3D_axis->addChild(Sol_BALL5C_3D);
Sol_BALL5C_3D_axis->addChild(axis);
MTrans_Sol_BALL5C_3D = new osg::MatrixTransform(MSol_BALL5C_3D);
MTrans_Sol_BALL5C_3D->addChild(Sol_BALL5C_3D_axis);
	
Sol_BALL6C_3D_axis = new osg::Group;
Sol_BALL6C_3D_axis->addChild(Sol_BALL6C_3D);
Sol_BALL6C_3D_axis->addChild(axis);
MTrans_Sol_BALL6C_3D = new osg::MatrixTransform(MSol_BALL6C_3D);
MTrans_Sol_BALL6C_3D->addChild(Sol_BALL6C_3D_axis);
	
Fra_Fra_PLATFORM_3D_draw_axis = new osg::Group;
Fra_Fra_PLATFORM_3D_draw_axis -> addChild(Fra_Fra_PLATFORM_3D_draw);
MTrans_Fra_Fra_PLATFORM_3D_draw = new osg::MatrixTransform(MFra_Fra_PLATFORM_3D_draw);
MTrans_Fra_Fra_PLATFORM_3D_draw->addChild(Fra_Fra_PLATFORM_3D_draw);
	
Fra_Fra_BAR1_3D_draw_axis = new osg::Group;
Fra_Fra_BAR1_3D_draw_axis -> addChild(Fra_Fra_BAR1_3D_draw);
MTrans_Fra_Fra_BAR1_3D_draw = new osg::MatrixTransform(MFra_Fra_BAR1_3D_draw);
MTrans_Fra_Fra_BAR1_3D_draw->addChild(Fra_Fra_BAR1_3D_draw);
	
Fra_Fra_BAR2_3D_draw_axis = new osg::Group;
Fra_Fra_BAR2_3D_draw_axis -> addChild(Fra_Fra_BAR2_3D_draw);
MTrans_Fra_Fra_BAR2_3D_draw = new osg::MatrixTransform(MFra_Fra_BAR2_3D_draw);
MTrans_Fra_Fra_BAR2_3D_draw->addChild(Fra_Fra_BAR2_3D_draw);
	
Fra_Fra_BAR3_3D_draw_axis = new osg::Group;
Fra_Fra_BAR3_3D_draw_axis -> addChild(Fra_Fra_BAR3_3D_draw);
MTrans_Fra_Fra_BAR3_3D_draw = new osg::MatrixTransform(MFra_Fra_BAR3_3D_draw);
MTrans_Fra_Fra_BAR3_3D_draw->addChild(Fra_Fra_BAR3_3D_draw);
	
Fra_Fra_BAR4_3D_draw_axis = new osg::Group;
Fra_Fra_BAR4_3D_draw_axis -> addChild(Fra_Fra_BAR4_3D_draw);
MTrans_Fra_Fra_BAR4_3D_draw = new osg::MatrixTransform(MFra_Fra_BAR4_3D_draw);
MTrans_Fra_Fra_BAR4_3D_draw->addChild(Fra_Fra_BAR4_3D_draw);
	
Fra_Fra_BAR5_3D_draw_axis = new osg::Group;
Fra_Fra_BAR5_3D_draw_axis -> addChild(Fra_Fra_BAR5_3D_draw);
MTrans_Fra_Fra_BAR5_3D_draw = new osg::MatrixTransform(MFra_Fra_BAR5_3D_draw);
MTrans_Fra_Fra_BAR5_3D_draw->addChild(Fra_Fra_BAR5_3D_draw);
	
Fra_Fra_BAR6_3D_draw_axis = new osg::Group;
Fra_Fra_BAR6_3D_draw_axis -> addChild(Fra_Fra_BAR6_3D_draw);
MTrans_Fra_Fra_BAR6_3D_draw = new osg::MatrixTransform(MFra_Fra_BAR6_3D_draw);
MTrans_Fra_Fra_BAR6_3D_draw->addChild(Fra_Fra_BAR6_3D_draw);
	
	
root = new osg::Group;
root->addChild(MTrans_Sol_PLATFORM_3D);
root->addChild(MTrans_Sol_BAR1_3D);
root->addChild(MTrans_Sol_BAR2_3D);
root->addChild(MTrans_Sol_BAR3_3D);
root->addChild(MTrans_Sol_BAR4_3D);
root->addChild(MTrans_Sol_BAR5_3D);
root->addChild(MTrans_Sol_BAR6_3D);
root->addChild(MTrans_Sol_BAR1V_3D);
root->addChild(MTrans_Sol_BAR2V_3D);
root->addChild(MTrans_Sol_BAR3V_3D);
root->addChild(MTrans_Sol_BAR4V_3D);
root->addChild(MTrans_Sol_BAR5V_3D);
root->addChild(MTrans_Sol_BAR6V_3D);
root->addChild(MTrans_Sol_BALL1A_3D);
root->addChild(MTrans_Sol_BALL2A_3D);
root->addChild(MTrans_Sol_BALL3A_3D);
root->addChild(MTrans_Sol_BALL4A_3D);
root->addChild(MTrans_Sol_BALL5A_3D);
root->addChild(MTrans_Sol_BALL6A_3D);
root->addChild(MTrans_Sol_BALL1D_3D);
root->addChild(MTrans_Sol_BALL2D_3D);
root->addChild(MTrans_Sol_BALL3D_3D);
root->addChild(MTrans_Sol_BALL4D_3D);
root->addChild(MTrans_Sol_BALL5D_3D);
root->addChild(MTrans_Sol_BALL6D_3D);
root->addChild(MTrans_Sol_BALL1C_3D);
root->addChild(MTrans_Sol_BALL2C_3D);
root->addChild(MTrans_Sol_BALL3C_3D);
root->addChild(MTrans_Sol_BALL4C_3D);
root->addChild(MTrans_Sol_BALL5C_3D);
root->addChild(MTrans_Sol_BALL6C_3D);
root->addChild(MTrans_Fra_Fra_PLATFORM_3D_draw);
root->addChild(MTrans_Fra_Fra_BAR1_3D_draw);
root->addChild(MTrans_Fra_Fra_BAR2_3D_draw);
root->addChild(MTrans_Fra_Fra_BAR3_3D_draw);
root->addChild(MTrans_Fra_Fra_BAR4_3D_draw);
root->addChild(MTrans_Fra_Fra_BAR5_3D_draw);
root->addChild(MTrans_Fra_Fra_BAR6_3D_draw);
}

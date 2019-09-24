#include <osg/Group>
#include <osg/Geode>
#include <osg/MatrixTransform>
 
#include "solids_homogeneous_matrix.h"
#include "osg_read_file.h"
#include "osg_state.h"

osg::MatrixTransform* MTrans_Sol_Plataforma3D;
osg::MatrixTransform* MTrans_Sol_RuedaIzq3D;
osg::MatrixTransform* MTrans_Sol_RuedaDcha3D;
osg::MatrixTransform* MTrans_Sol_Manillar3D;
osg::MatrixTransform* MTrans_Pnt_Rider3D;
osg::MatrixTransform* MTrans_Fra_FraABS_draw;
osg::MatrixTransform* MTrans_Sol_Ground3D;
osg::MatrixTransform* MTrans_Vec_VectorP_J1;
osg::MatrixTransform* MTrans_Vec_VectorP_J2;
osg::MatrixTransform* MTrans_Vec_VectorP_S0;
osg::MatrixTransform* MTrans_Vec_VectorP_S1;
osg::MatrixTransform* MTrans_Vec_VectorP_S2;
osg::MatrixTransform* MTrans_Vec_VectorO_P;

osg::Group* Sol_Plataforma3D_axis;
osg::Group* Sol_RuedaIzq3D_axis;
osg::Group* Sol_RuedaDcha3D_axis;
osg::Group* Sol_Manillar3D_axis;
osg::Group* Pnt_Rider3D_axis;
osg::Group* Fra_FraABS_draw_axis;
osg::Group* Sol_Ground3D_axis;
osg::Group* Vec_VectorP_J1_axis;
osg::Group* Vec_VectorP_J2_axis;
osg::Group* Vec_VectorP_S0_axis;
osg::Group* Vec_VectorP_S1_axis;
osg::Group* Vec_VectorP_S2_axis;
osg::Group* Vec_VectorO_P_axis;

osg::Group* root;

void osg_root ()
{
osg_state();

Sol_Plataforma3D_axis = new osg::Group;
Sol_Plataforma3D_axis->addChild(Sol_Plataforma3D);
Sol_Plataforma3D_axis->addChild(axis);
MTrans_Sol_Plataforma3D = new osg::MatrixTransform(MSol_Plataforma3D);
MTrans_Sol_Plataforma3D->addChild(Sol_Plataforma3D_axis);
	
Sol_RuedaIzq3D_axis = new osg::Group;
Sol_RuedaIzq3D_axis->addChild(Sol_RuedaIzq3D);
Sol_RuedaIzq3D_axis->addChild(axis);
MTrans_Sol_RuedaIzq3D = new osg::MatrixTransform(MSol_RuedaIzq3D);
MTrans_Sol_RuedaIzq3D->addChild(Sol_RuedaIzq3D_axis);
	
Sol_RuedaDcha3D_axis = new osg::Group;
Sol_RuedaDcha3D_axis->addChild(Sol_RuedaDcha3D);
Sol_RuedaDcha3D_axis->addChild(axis);
MTrans_Sol_RuedaDcha3D = new osg::MatrixTransform(MSol_RuedaDcha3D);
MTrans_Sol_RuedaDcha3D->addChild(Sol_RuedaDcha3D_axis);
	
Sol_Manillar3D_axis = new osg::Group;
Sol_Manillar3D_axis->addChild(Sol_Manillar3D);
Sol_Manillar3D_axis->addChild(axis);
MTrans_Sol_Manillar3D = new osg::MatrixTransform(MSol_Manillar3D);
MTrans_Sol_Manillar3D->addChild(Sol_Manillar3D_axis);
	
Pnt_Rider3D_axis = new osg::Group;
Pnt_Rider3D_axis -> addChild(Pnt_Rider3D);
MTrans_Pnt_Rider3D = new osg::MatrixTransform(MPnt_Rider3D);
MTrans_Pnt_Rider3D->addChild(Pnt_Rider3D);
	
Fra_FraABS_draw_axis = new osg::Group;
Fra_FraABS_draw_axis -> addChild(Fra_FraABS_draw);
MTrans_Fra_FraABS_draw = new osg::MatrixTransform(MFra_FraABS_draw);
MTrans_Fra_FraABS_draw->addChild(Fra_FraABS_draw);
	
Sol_Ground3D_axis = new osg::Group;
Sol_Ground3D_axis->addChild(Sol_Ground3D);
Sol_Ground3D_axis->addChild(axis);
MTrans_Sol_Ground3D = new osg::MatrixTransform(MSol_Ground3D);
MTrans_Sol_Ground3D->addChild(Sol_Ground3D_axis);
	
Vec_VectorP_J1_axis = new osg::Group;
Vec_VectorP_J1_axis -> addChild(Vec_VectorP_J1);
MTrans_Vec_VectorP_J1 = new osg::MatrixTransform(MVec_VectorP_J1);
MTrans_Vec_VectorP_J1->addChild(Vec_VectorP_J1);
	
Vec_VectorP_J2_axis = new osg::Group;
Vec_VectorP_J2_axis -> addChild(Vec_VectorP_J2);
MTrans_Vec_VectorP_J2 = new osg::MatrixTransform(MVec_VectorP_J2);
MTrans_Vec_VectorP_J2->addChild(Vec_VectorP_J2);
	
Vec_VectorP_S0_axis = new osg::Group;
Vec_VectorP_S0_axis -> addChild(Vec_VectorP_S0);
MTrans_Vec_VectorP_S0 = new osg::MatrixTransform(MVec_VectorP_S0);
MTrans_Vec_VectorP_S0->addChild(Vec_VectorP_S0);
	
Vec_VectorP_S1_axis = new osg::Group;
Vec_VectorP_S1_axis -> addChild(Vec_VectorP_S1);
MTrans_Vec_VectorP_S1 = new osg::MatrixTransform(MVec_VectorP_S1);
MTrans_Vec_VectorP_S1->addChild(Vec_VectorP_S1);
	
Vec_VectorP_S2_axis = new osg::Group;
Vec_VectorP_S2_axis -> addChild(Vec_VectorP_S2);
MTrans_Vec_VectorP_S2 = new osg::MatrixTransform(MVec_VectorP_S2);
MTrans_Vec_VectorP_S2->addChild(Vec_VectorP_S2);
	
Vec_VectorO_P_axis = new osg::Group;
Vec_VectorO_P_axis -> addChild(Vec_VectorO_P);
MTrans_Vec_VectorO_P = new osg::MatrixTransform(MVec_VectorO_P);
MTrans_Vec_VectorO_P->addChild(Vec_VectorO_P);
	
	
root = new osg::Group;
root->addChild(MTrans_Sol_Plataforma3D);
root->addChild(MTrans_Sol_RuedaIzq3D);
root->addChild(MTrans_Sol_RuedaDcha3D);
root->addChild(MTrans_Sol_Manillar3D);
root->addChild(MTrans_Pnt_Rider3D);
root->addChild(MTrans_Fra_FraABS_draw);
root->addChild(MTrans_Sol_Ground3D);
root->addChild(MTrans_Vec_VectorP_J1);
root->addChild(MTrans_Vec_VectorP_J2);
root->addChild(MTrans_Vec_VectorP_S0);
root->addChild(MTrans_Vec_VectorP_S1);
root->addChild(MTrans_Vec_VectorP_S2);
root->addChild(MTrans_Vec_VectorO_P);
}

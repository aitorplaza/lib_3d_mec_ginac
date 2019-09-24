#ifndef __linux__
  #include <windows.h>
#endif

#include <osg/Geode>
#include <osg/Material>
#include <osg/BlendFunc>

#include "osg_read_file.h"

void osg_state ()
{

osg::StateSet* State_Arm1_3D = Sol_Arm1_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialArm1_3D = new osg::Material;
materialArm1_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_Arm1_3D->setAttributeAndModes( materialArm1_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_Arm1_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_Arm1_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_Arm2_3D = Sol_Arm2_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialArm2_3D = new osg::Material;
materialArm2_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_Arm2_3D->setAttributeAndModes( materialArm2_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_Arm2_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_Arm2_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_Plane_3D = Sol_Plane_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialPlane_3D = new osg::Material;
materialPlane_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,1,1.0));
State_Plane_3D->setAttributeAndModes( materialPlane_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_Plane_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_Plane_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_Disc_3D = Sol_Disc_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialDisc_3D = new osg::Material;
materialDisc_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_Disc_3D->setAttributeAndModes( materialDisc_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_Disc_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_Disc_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

}

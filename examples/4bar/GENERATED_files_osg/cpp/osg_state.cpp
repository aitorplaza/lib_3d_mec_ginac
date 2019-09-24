#ifndef __linux__
  #include <windows.h>
#endif

#include <osg/Geode>
#include <osg/Material>
#include <osg/BlendFunc>

#include "osg_read_file.h"

void osg_state ()
{

osg::StateSet* State_Varm1 = Vec_Varm1->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialVarm1 = new osg::Material;
materialVarm1->setDiffuse(osg::Material::FRONT,osg::Vec4(1.0,0.0,0.0,1.0));
State_Varm1->setAttributeAndModes( materialVarm1.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_Varm1->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_Varm1->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_Varm2 = Vec_Varm2->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialVarm2 = new osg::Material;
materialVarm2->setDiffuse(osg::Material::FRONT,osg::Vec4(1.0,0.0,0.0,1.0));
State_Varm2->setAttributeAndModes( materialVarm2.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_Varm2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_Varm2->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_Varm3 = Vec_Varm3->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialVarm3 = new osg::Material;
materialVarm3->setDiffuse(osg::Material::FRONT,osg::Vec4(1.0,0.0,0.0,1.0));
State_Varm3->setAttributeAndModes( materialVarm3.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_Varm3->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_Varm3->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_Varm4 = Vec_Varm4->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialVarm4 = new osg::Material;
materialVarm4->setDiffuse(osg::Material::FRONT,osg::Vec4(1.0,0.0,0.0,1.0));
State_Varm4->setAttributeAndModes( materialVarm4.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_Varm4->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_Varm4->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_VOL2_OL3 = Vec_VOL2_OL3->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialVOL2_OL3 = new osg::Material;
materialVOL2_OL3->setDiffuse(osg::Material::FRONT,osg::Vec4(1,1,0,1.0));
State_VOL2_OL3->setAttributeAndModes( materialVOL2_OL3.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_VOL2_OL3->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_VOL2_OL3->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

}

#ifndef __linux__
  #include <windows.h>
#endif

#include <osg/Geode>
#include <osg/Material>
#include <osg/BlendFunc>

#include "osg_read_file.h"

void osg_state ()
{

osg::StateSet* State_PLATFORM_3D = Sol_PLATFORM_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialPLATFORM_3D = new osg::Material;
materialPLATFORM_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,0.5999999999999999778));
State_PLATFORM_3D->setAttributeAndModes( materialPLATFORM_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_PLATFORM_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_PLATFORM_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR1_3D = Sol_BAR1_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR1_3D = new osg::Material;
materialBAR1_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR1_3D->setAttributeAndModes( materialBAR1_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR1_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR1_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR2_3D = Sol_BAR2_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR2_3D = new osg::Material;
materialBAR2_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR2_3D->setAttributeAndModes( materialBAR2_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR2_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR2_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR3_3D = Sol_BAR3_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR3_3D = new osg::Material;
materialBAR3_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR3_3D->setAttributeAndModes( materialBAR3_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR3_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR3_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR4_3D = Sol_BAR4_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR4_3D = new osg::Material;
materialBAR4_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR4_3D->setAttributeAndModes( materialBAR4_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR4_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR4_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR5_3D = Sol_BAR5_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR5_3D = new osg::Material;
materialBAR5_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR5_3D->setAttributeAndModes( materialBAR5_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR5_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR5_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR6_3D = Sol_BAR6_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR6_3D = new osg::Material;
materialBAR6_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR6_3D->setAttributeAndModes( materialBAR6_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR6_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR6_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR1V_3D = Sol_BAR1V_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR1V_3D = new osg::Material;
materialBAR1V_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR1V_3D->setAttributeAndModes( materialBAR1V_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR1V_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR1V_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR2V_3D = Sol_BAR2V_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR2V_3D = new osg::Material;
materialBAR2V_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR2V_3D->setAttributeAndModes( materialBAR2V_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR2V_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR2V_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR3V_3D = Sol_BAR3V_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR3V_3D = new osg::Material;
materialBAR3V_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR3V_3D->setAttributeAndModes( materialBAR3V_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR3V_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR3V_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR4V_3D = Sol_BAR4V_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR4V_3D = new osg::Material;
materialBAR4V_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR4V_3D->setAttributeAndModes( materialBAR4V_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR4V_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR4V_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR5V_3D = Sol_BAR5V_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR5V_3D = new osg::Material;
materialBAR5V_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR5V_3D->setAttributeAndModes( materialBAR5V_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR5V_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR5V_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BAR6V_3D = Sol_BAR6V_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBAR6V_3D = new osg::Material;
materialBAR6V_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_BAR6V_3D->setAttributeAndModes( materialBAR6V_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BAR6V_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BAR6V_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL1A_3D = Sol_BALL1A_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL1A_3D = new osg::Material;
materialBALL1A_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL1A_3D->setAttributeAndModes( materialBALL1A_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL1A_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL1A_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL2A_3D = Sol_BALL2A_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL2A_3D = new osg::Material;
materialBALL2A_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL2A_3D->setAttributeAndModes( materialBALL2A_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL2A_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL2A_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL3A_3D = Sol_BALL3A_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL3A_3D = new osg::Material;
materialBALL3A_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL3A_3D->setAttributeAndModes( materialBALL3A_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL3A_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL3A_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL4A_3D = Sol_BALL4A_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL4A_3D = new osg::Material;
materialBALL4A_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL4A_3D->setAttributeAndModes( materialBALL4A_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL4A_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL4A_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL5A_3D = Sol_BALL5A_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL5A_3D = new osg::Material;
materialBALL5A_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL5A_3D->setAttributeAndModes( materialBALL5A_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL5A_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL5A_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL6A_3D = Sol_BALL6A_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL6A_3D = new osg::Material;
materialBALL6A_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL6A_3D->setAttributeAndModes( materialBALL6A_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL6A_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL6A_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL1D_3D = Sol_BALL1D_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL1D_3D = new osg::Material;
materialBALL1D_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL1D_3D->setAttributeAndModes( materialBALL1D_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL1D_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL1D_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL2D_3D = Sol_BALL2D_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL2D_3D = new osg::Material;
materialBALL2D_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL2D_3D->setAttributeAndModes( materialBALL2D_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL2D_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL2D_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL3D_3D = Sol_BALL3D_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL3D_3D = new osg::Material;
materialBALL3D_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL3D_3D->setAttributeAndModes( materialBALL3D_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL3D_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL3D_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL4D_3D = Sol_BALL4D_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL4D_3D = new osg::Material;
materialBALL4D_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL4D_3D->setAttributeAndModes( materialBALL4D_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL4D_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL4D_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL5D_3D = Sol_BALL5D_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL5D_3D = new osg::Material;
materialBALL5D_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL5D_3D->setAttributeAndModes( materialBALL5D_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL5D_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL5D_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL6D_3D = Sol_BALL6D_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL6D_3D = new osg::Material;
materialBALL6D_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL6D_3D->setAttributeAndModes( materialBALL6D_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL6D_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL6D_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL1C_3D = Sol_BALL1C_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL1C_3D = new osg::Material;
materialBALL1C_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL1C_3D->setAttributeAndModes( materialBALL1C_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL1C_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL1C_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL2C_3D = Sol_BALL2C_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL2C_3D = new osg::Material;
materialBALL2C_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL2C_3D->setAttributeAndModes( materialBALL2C_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL2C_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL2C_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL3C_3D = Sol_BALL3C_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL3C_3D = new osg::Material;
materialBALL3C_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL3C_3D->setAttributeAndModes( materialBALL3C_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL3C_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL3C_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL4C_3D = Sol_BALL4C_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL4C_3D = new osg::Material;
materialBALL4C_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL4C_3D->setAttributeAndModes( materialBALL4C_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL4C_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL4C_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL5C_3D = Sol_BALL5C_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL5C_3D = new osg::Material;
materialBALL5C_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL5C_3D->setAttributeAndModes( materialBALL5C_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL5C_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL5C_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_BALL6C_3D = Sol_BALL6C_3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialBALL6C_3D = new osg::Material;
materialBALL6C_3D->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_BALL6C_3D->setAttributeAndModes( materialBALL6C_3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_BALL6C_3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_BALL6C_3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

}

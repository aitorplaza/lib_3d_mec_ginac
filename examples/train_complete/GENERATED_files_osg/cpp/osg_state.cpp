#ifndef __linux__
  #include <windows.h>
#endif

#include <osg/Geode>
#include <osg/Material>
#include <osg/BlendFunc>

#include "osg_read_file.h"

void osg_state ()
{

osg::StateSet* State_D_WAG = Sol_D_WAG->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_WAG = new osg::Material;
materialD_WAG->setDiffuse(osg::Material::FRONT,osg::Vec4(1,1,0,1.0));
State_D_WAG->setAttributeAndModes( materialD_WAG.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_WAG->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_WAG->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RBOG = Sol_D_RBOG->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RBOG = new osg::Material;
materialD_RBOG->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_RBOG->setAttributeAndModes( materialD_RBOG.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RBOG->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RBOG->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RWHSF = Sol_D_RWHSF->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RWHSF = new osg::Material;
materialD_RWHSF->setDiffuse(osg::Material::FRONT,osg::Vec4(0,1,1,1.0));
State_D_RWHSF->setAttributeAndModes( materialD_RWHSF.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RWHSF->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RWHSF->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RWHSR = Sol_D_RWHSR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RWHSR = new osg::Material;
materialD_RWHSR->setDiffuse(osg::Material::FRONT,osg::Vec4(0,1,1,1.0));
State_D_RWHSR->setAttributeAndModes( materialD_RWHSR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RWHSR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RWHSR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBFL = Sol_D_RAXBFL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBFL = new osg::Material;
materialD_RAXBFL->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_D_RAXBFL->setAttributeAndModes( materialD_RAXBFL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBFL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBFL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBFR = Sol_D_RAXBFR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBFR = new osg::Material;
materialD_RAXBFR->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_D_RAXBFR->setAttributeAndModes( materialD_RAXBFR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBFR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBFR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBRL = Sol_D_RAXBRL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBRL = new osg::Material;
materialD_RAXBRL->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_D_RAXBRL->setAttributeAndModes( materialD_RAXBRL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBRL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBRL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBRR = Sol_D_RAXBRR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBRR = new osg::Material;
materialD_RAXBRR->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_D_RAXBRR->setAttributeAndModes( materialD_RAXBRR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBRR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBRR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RSLD = Sol_D_RSLD->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RSLD = new osg::Material;
materialD_RSLD->setDiffuse(osg::Material::FRONT,osg::Vec4(0,1,0,1.0));
State_D_RSLD->setAttributeAndModes( materialD_RSLD.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RSLD->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RSLD->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RMOTF = Sol_D_RMOTF->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RMOTF = new osg::Material;
materialD_RMOTF->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,1,1.0));
State_D_RMOTF->setAttributeAndModes( materialD_RMOTF.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RMOTF->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RMOTF->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RMOTR = Sol_D_RMOTR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RMOTR = new osg::Material;
materialD_RMOTR->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,1,1.0));
State_D_RMOTR->setAttributeAndModes( materialD_RMOTR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RMOTR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RMOTR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RROTF = Sol_D_RROTF->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RROTF = new osg::Material;
materialD_RROTF->setDiffuse(osg::Material::FRONT,osg::Vec4(0,1,0.5,1.0));
State_D_RROTF->setAttributeAndModes( materialD_RROTF.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RROTF->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RROTF->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RROTR = Sol_D_RROTR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RROTR = new osg::Material;
materialD_RROTR->setDiffuse(osg::Material::FRONT,osg::Vec4(0,1,0.5,1.0));
State_D_RROTR->setAttributeAndModes( materialD_RROTR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RROTR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RROTR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FBOG = Sol_D_FBOG->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FBOG = new osg::Material;
materialD_FBOG->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_FBOG->setAttributeAndModes( materialD_FBOG.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FBOG->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FBOG->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FWHSF = Sol_D_FWHSF->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FWHSF = new osg::Material;
materialD_FWHSF->setDiffuse(osg::Material::FRONT,osg::Vec4(0,1,1,1.0));
State_D_FWHSF->setAttributeAndModes( materialD_FWHSF.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FWHSF->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FWHSF->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FWHSR = Sol_D_FWHSR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FWHSR = new osg::Material;
materialD_FWHSR->setDiffuse(osg::Material::FRONT,osg::Vec4(0,1,1,1.0));
State_D_FWHSR->setAttributeAndModes( materialD_FWHSR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FWHSR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FWHSR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBFL = Sol_D_FAXBFL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBFL = new osg::Material;
materialD_FAXBFL->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_D_FAXBFL->setAttributeAndModes( materialD_FAXBFL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBFL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBFL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBFR = Sol_D_FAXBFR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBFR = new osg::Material;
materialD_FAXBFR->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_D_FAXBFR->setAttributeAndModes( materialD_FAXBFR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBFR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBFR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBRL = Sol_D_FAXBRL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBRL = new osg::Material;
materialD_FAXBRL->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_D_FAXBRL->setAttributeAndModes( materialD_FAXBRL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBRL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBRL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBRR = Sol_D_FAXBRR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBRR = new osg::Material;
materialD_FAXBRR->setDiffuse(osg::Material::FRONT,osg::Vec4(1,0,0,1.0));
State_D_FAXBRR->setAttributeAndModes( materialD_FAXBRR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBRR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBRR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FSLD = Sol_D_FSLD->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FSLD = new osg::Material;
materialD_FSLD->setDiffuse(osg::Material::FRONT,osg::Vec4(0,1,0,1.0));
State_D_FSLD->setAttributeAndModes( materialD_FSLD.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FSLD->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FSLD->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAIL = Sol_D_RAIL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAIL = new osg::Material;
materialD_RAIL->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RAIL->setAttributeAndModes( materialD_RAIL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAIL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAIL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBFL1 = Sol_D_RAXBFL1->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBFL1 = new osg::Material;
materialD_RAXBFL1->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RAXBFL1->setAttributeAndModes( materialD_RAXBFL1.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBFL1->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBFL1->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBFL2 = Sol_D_RAXBFL2->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBFL2 = new osg::Material;
materialD_RAXBFL2->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RAXBFL2->setAttributeAndModes( materialD_RAXBFL2.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBFL2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBFL2->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBFR1 = Sol_D_RAXBFR1->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBFR1 = new osg::Material;
materialD_RAXBFR1->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RAXBFR1->setAttributeAndModes( materialD_RAXBFR1.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBFR1->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBFR1->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBFR2 = Sol_D_RAXBFR2->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBFR2 = new osg::Material;
materialD_RAXBFR2->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RAXBFR2->setAttributeAndModes( materialD_RAXBFR2.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBFR2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBFR2->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBRL1 = Sol_D_RAXBRL1->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBRL1 = new osg::Material;
materialD_RAXBRL1->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RAXBRL1->setAttributeAndModes( materialD_RAXBRL1.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBRL1->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBRL1->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBRL2 = Sol_D_RAXBRL2->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBRL2 = new osg::Material;
materialD_RAXBRL2->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RAXBRL2->setAttributeAndModes( materialD_RAXBRL2.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBRL2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBRL2->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBRR1 = Sol_D_RAXBRR1->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBRR1 = new osg::Material;
materialD_RAXBRR1->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RAXBRR1->setAttributeAndModes( materialD_RAXBRR1.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBRR1->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBRR1->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RAXBRR2 = Sol_D_RAXBRR2->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RAXBRR2 = new osg::Material;
materialD_RAXBRR2->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RAXBRR2->setAttributeAndModes( materialD_RAXBRR2.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RAXBRR2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RAXBRR2->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RSUSPFL = Sol_D_RSUSPFL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RSUSPFL = new osg::Material;
materialD_RSUSPFL->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_RSUSPFL->setAttributeAndModes( materialD_RSUSPFL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RSUSPFL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RSUSPFL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RSUSPFR = Sol_D_RSUSPFR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RSUSPFR = new osg::Material;
materialD_RSUSPFR->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_RSUSPFR->setAttributeAndModes( materialD_RSUSPFR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RSUSPFR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RSUSPFR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RSUSPRL = Sol_D_RSUSPRL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RSUSPRL = new osg::Material;
materialD_RSUSPRL->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_RSUSPRL->setAttributeAndModes( materialD_RSUSPRL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RSUSPRL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RSUSPRL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RSUSPRR = Sol_D_RSUSPRR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RSUSPRR = new osg::Material;
materialD_RSUSPRR->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_RSUSPRR->setAttributeAndModes( materialD_RSUSPRR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RSUSPRR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RSUSPRR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RSUSPBEAML = Sol_D_RSUSPBEAML->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RSUSPBEAML = new osg::Material;
materialD_RSUSPBEAML->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_RSUSPBEAML->setAttributeAndModes( materialD_RSUSPBEAML.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RSUSPBEAML->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RSUSPBEAML->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RSUSPBEAMR = Sol_D_RSUSPBEAMR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RSUSPBEAMR = new osg::Material;
materialD_RSUSPBEAMR->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_RSUSPBEAMR->setAttributeAndModes( materialD_RSUSPBEAMR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RSUSPBEAMR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RSUSPBEAMR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RSPRING2FL = Sol_D_RSPRING2FL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RSPRING2FL = new osg::Material;
materialD_RSPRING2FL->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RSPRING2FL->setAttributeAndModes( materialD_RSPRING2FL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RSPRING2FL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RSPRING2FL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RSPRING2RL = Sol_D_RSPRING2RL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RSPRING2RL = new osg::Material;
materialD_RSPRING2RL->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RSPRING2RL->setAttributeAndModes( materialD_RSPRING2RL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RSPRING2RL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RSPRING2RL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RSPRING2FR = Sol_D_RSPRING2FR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RSPRING2FR = new osg::Material;
materialD_RSPRING2FR->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RSPRING2FR->setAttributeAndModes( materialD_RSPRING2FR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RSPRING2FR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RSPRING2FR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_RSPRING2RR = Sol_D_RSPRING2RR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_RSPRING2RR = new osg::Material;
materialD_RSPRING2RR->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_RSPRING2RR->setAttributeAndModes( materialD_RSPRING2RR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_RSPRING2RR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_RSPRING2RR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBFL1 = Sol_D_FAXBFL1->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBFL1 = new osg::Material;
materialD_FAXBFL1->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FAXBFL1->setAttributeAndModes( materialD_FAXBFL1.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBFL1->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBFL1->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBFL2 = Sol_D_FAXBFL2->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBFL2 = new osg::Material;
materialD_FAXBFL2->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FAXBFL2->setAttributeAndModes( materialD_FAXBFL2.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBFL2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBFL2->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBFR1 = Sol_D_FAXBFR1->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBFR1 = new osg::Material;
materialD_FAXBFR1->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FAXBFR1->setAttributeAndModes( materialD_FAXBFR1.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBFR1->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBFR1->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBFR2 = Sol_D_FAXBFR2->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBFR2 = new osg::Material;
materialD_FAXBFR2->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FAXBFR2->setAttributeAndModes( materialD_FAXBFR2.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBFR2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBFR2->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBRL1 = Sol_D_FAXBRL1->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBRL1 = new osg::Material;
materialD_FAXBRL1->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FAXBRL1->setAttributeAndModes( materialD_FAXBRL1.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBRL1->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBRL1->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBRL2 = Sol_D_FAXBRL2->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBRL2 = new osg::Material;
materialD_FAXBRL2->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FAXBRL2->setAttributeAndModes( materialD_FAXBRL2.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBRL2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBRL2->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBRR1 = Sol_D_FAXBRR1->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBRR1 = new osg::Material;
materialD_FAXBRR1->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FAXBRR1->setAttributeAndModes( materialD_FAXBRR1.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBRR1->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBRR1->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FAXBRR2 = Sol_D_FAXBRR2->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FAXBRR2 = new osg::Material;
materialD_FAXBRR2->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FAXBRR2->setAttributeAndModes( materialD_FAXBRR2.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FAXBRR2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FAXBRR2->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FSUSPFL = Sol_D_FSUSPFL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FSUSPFL = new osg::Material;
materialD_FSUSPFL->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_FSUSPFL->setAttributeAndModes( materialD_FSUSPFL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FSUSPFL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FSUSPFL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FSUSPFR = Sol_D_FSUSPFR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FSUSPFR = new osg::Material;
materialD_FSUSPFR->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_FSUSPFR->setAttributeAndModes( materialD_FSUSPFR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FSUSPFR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FSUSPFR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FSUSPRL = Sol_D_FSUSPRL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FSUSPRL = new osg::Material;
materialD_FSUSPRL->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_FSUSPRL->setAttributeAndModes( materialD_FSUSPRL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FSUSPRL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FSUSPRL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FSUSPRR = Sol_D_FSUSPRR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FSUSPRR = new osg::Material;
materialD_FSUSPRR->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_FSUSPRR->setAttributeAndModes( materialD_FSUSPRR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FSUSPRR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FSUSPRR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FSUSPBEAML = Sol_D_FSUSPBEAML->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FSUSPBEAML = new osg::Material;
materialD_FSUSPBEAML->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_FSUSPBEAML->setAttributeAndModes( materialD_FSUSPBEAML.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FSUSPBEAML->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FSUSPBEAML->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FSUSPBEAMR = Sol_D_FSUSPBEAMR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FSUSPBEAMR = new osg::Material;
materialD_FSUSPBEAMR->setDiffuse(osg::Material::FRONT,osg::Vec4(0,0,1,1.0));
State_D_FSUSPBEAMR->setAttributeAndModes( materialD_FSUSPBEAMR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FSUSPBEAMR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FSUSPBEAMR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FSPRING2FL = Sol_D_FSPRING2FL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FSPRING2FL = new osg::Material;
materialD_FSPRING2FL->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FSPRING2FL->setAttributeAndModes( materialD_FSPRING2FL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FSPRING2FL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FSPRING2FL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FSPRING2RL = Sol_D_FSPRING2RL->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FSPRING2RL = new osg::Material;
materialD_FSPRING2RL->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FSPRING2RL->setAttributeAndModes( materialD_FSPRING2RL.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FSPRING2RL->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FSPRING2RL->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FSPRING2FR = Sol_D_FSPRING2FR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FSPRING2FR = new osg::Material;
materialD_FSPRING2FR->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FSPRING2FR->setAttributeAndModes( materialD_FSPRING2FR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FSPRING2FR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FSPRING2FR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_D_FSPRING2RR = Sol_D_FSPRING2RR->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialD_FSPRING2RR = new osg::Material;
materialD_FSPRING2RR->setDiffuse(osg::Material::FRONT,osg::Vec4(0.5,0.5,0.5,1.0));
State_D_FSPRING2RR->setAttributeAndModes( materialD_FSPRING2RR.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_D_FSPRING2RR->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_D_FSPRING2RR->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

}

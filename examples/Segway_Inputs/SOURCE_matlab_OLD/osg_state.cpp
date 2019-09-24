#include <osg/Geode>
#include <osg/Material>
#include <osg/BlendFunc>

#include "osg_read_file.h"

void osg_state ()
{

osg::StateSet* State_Rider3D = Pnt_Rider3D->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialRider3D = new osg::Material;
materialRider3D->setDiffuse(osg::Material::FRONT,osg::Vec4(1.0,1.0,0.0,1.0));
State_Rider3D->setAttributeAndModes( materialRider3D.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_Rider3D->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_Rider3D->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_VectorP_J1 = Vec_VectorP_J1->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialVectorP_J1 = new osg::Material;
materialVectorP_J1->setDiffuse(osg::Material::FRONT,osg::Vec4(1.0,0.0,1.0,1.0));
State_VectorP_J1->setAttributeAndModes( materialVectorP_J1.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_VectorP_J1->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_VectorP_J1->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_VectorP_J2 = Vec_VectorP_J2->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialVectorP_J2 = new osg::Material;
materialVectorP_J2->setDiffuse(osg::Material::FRONT,osg::Vec4(1.0,0.0,1.0,1.0));
State_VectorP_J2->setAttributeAndModes( materialVectorP_J2.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_VectorP_J2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_VectorP_J2->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_VectorP_S0 = Vec_VectorP_S0->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialVectorP_S0 = new osg::Material;
materialVectorP_S0->setDiffuse(osg::Material::FRONT,osg::Vec4(1.0,0.0,1.0,1.0));
State_VectorP_S0->setAttributeAndModes( materialVectorP_S0.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_VectorP_S0->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_VectorP_S0->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_VectorP_S1 = Vec_VectorP_S1->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialVectorP_S1 = new osg::Material;
materialVectorP_S1->setDiffuse(osg::Material::FRONT,osg::Vec4(0.0,1.0,0.0,1.0));
State_VectorP_S1->setAttributeAndModes( materialVectorP_S1.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_VectorP_S1->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_VectorP_S1->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_VectorP_S2 = Vec_VectorP_S2->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialVectorP_S2 = new osg::Material;
materialVectorP_S2->setDiffuse(osg::Material::FRONT,osg::Vec4(0.0,1.0,0.0,1.0));
State_VectorP_S2->setAttributeAndModes( materialVectorP_S2.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_VectorP_S2->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_VectorP_S2->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

osg::StateSet* State_VectorO_P = Vec_VectorO_P->getOrCreateStateSet();
osg::ref_ptr<osg::Material> materialVectorO_P = new osg::Material;
materialVectorO_P->setDiffuse(osg::Material::FRONT,osg::Vec4(1.0,0.0,1.0,1.0));
State_VectorO_P->setAttributeAndModes( materialVectorO_P.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
State_VectorO_P->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
State_VectorO_P->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));

}

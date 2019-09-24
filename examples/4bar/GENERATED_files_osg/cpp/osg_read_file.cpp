#ifndef __linux__
  #include <windows.h>
#endif
 
#include <osg/Geode>
#include <osgDB/ReadFile>
 
osg::Geode* axis;
osg::Geode* Fra_DFra_arm1_draw;
osg::Geode* Fra_DFra_arm2_draw;
osg::Geode* Fra_DFra_arm3_draw;
osg::Geode* Fra_FraABS_draw;
osg::Geode* Fra_FraABS2_draw;
osg::Geode* Vec_Varm1;
osg::Geode* Vec_Varm2;
osg::Geode* Vec_Varm3;
osg::Geode* Vec_Varm4;
osg::Geode* Vec_VOL2_OL3;
 
void osg_read_file ()
{
Fra_DFra_arm1_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.2000000000000000111].scale");
Fra_DFra_arm2_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.2000000000000000111].scale");
Fra_DFra_arm3_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.2000000000000000111].scale");
Fra_FraABS_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.2000000000000000111].scale");
Fra_FraABS2_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.2000000000000000111].scale");
Vec_Varm1 = (osg::Geode*) osgDB::readNodeFile("./vector.osg.[1.0].scale");
Vec_Varm2 = (osg::Geode*) osgDB::readNodeFile("./vector.osg.[1.0].scale");
Vec_Varm3 = (osg::Geode*) osgDB::readNodeFile("./vector.osg.[1.0].scale");
Vec_Varm4 = (osg::Geode*) osgDB::readNodeFile("./vector.osg.[1.0].scale");
Vec_VOL2_OL3 = (osg::Geode*) osgDB::readNodeFile("./vector.osg.[1.0].scale");
}

#ifndef __linux__
  #include <windows.h>
#endif
 
#include <osg/Geode>
#include <osgDB/ReadFile>
 
osg::Geode* axis;
osg::Geode* Sol_Arm1_3D;
osg::Geode* Sol_Arm2_3D;
osg::Geode* Sol_Plane_3D;
osg::Geode* Sol_Disc_3D;
osg::Geode* Fra_FraARM1_draw;
osg::Geode* Fra_FraARM2_draw;
osg::Geode* Fra_FraDISC_draw;
osg::Geode* Fra_FraPLANE_draw;
osg::Geode* Fra_FraABS_draw;
 
void osg_read_file ()
{
Sol_Arm1_3D = (osg::Geode*) osgDB::readNodeFile("./solids/arm1.stl.[1].scale");
Sol_Arm2_3D = (osg::Geode*) osgDB::readNodeFile("./solids/arm2.stl.[1].scale");
Sol_Plane_3D = (osg::Geode*) osgDB::readNodeFile("./solids/plane.stl.[1].scale");
Sol_Disc_3D = (osg::Geode*) osgDB::readNodeFile("./solids/disc.stl.[1].scale");
Fra_FraARM1_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
Fra_FraARM2_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
Fra_FraDISC_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
Fra_FraPLANE_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
Fra_FraABS_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.5].scale");
}

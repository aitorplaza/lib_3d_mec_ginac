#ifndef __linux__
  #include <windows.h>
#endif
 
#include <osg/Geode>
#include <osgDB/ReadFile>
 
osg::Geode* axis;
osg::Geode* Sol_PLATFORM_3D;
osg::Geode* Sol_BAR1_3D;
osg::Geode* Sol_BAR2_3D;
osg::Geode* Sol_BAR3_3D;
osg::Geode* Sol_BAR4_3D;
osg::Geode* Sol_BAR5_3D;
osg::Geode* Sol_BAR6_3D;
osg::Geode* Sol_BAR1V_3D;
osg::Geode* Sol_BAR2V_3D;
osg::Geode* Sol_BAR3V_3D;
osg::Geode* Sol_BAR4V_3D;
osg::Geode* Sol_BAR5V_3D;
osg::Geode* Sol_BAR6V_3D;
osg::Geode* Sol_BALL1A_3D;
osg::Geode* Sol_BALL2A_3D;
osg::Geode* Sol_BALL3A_3D;
osg::Geode* Sol_BALL4A_3D;
osg::Geode* Sol_BALL5A_3D;
osg::Geode* Sol_BALL6A_3D;
osg::Geode* Sol_BALL1D_3D;
osg::Geode* Sol_BALL2D_3D;
osg::Geode* Sol_BALL3D_3D;
osg::Geode* Sol_BALL4D_3D;
osg::Geode* Sol_BALL5D_3D;
osg::Geode* Sol_BALL6D_3D;
osg::Geode* Sol_BALL1C_3D;
osg::Geode* Sol_BALL2C_3D;
osg::Geode* Sol_BALL3C_3D;
osg::Geode* Sol_BALL4C_3D;
osg::Geode* Sol_BALL5C_3D;
osg::Geode* Sol_BALL6C_3D;
osg::Geode* Fra_Fra_PLATFORM_3D_draw;
osg::Geode* Fra_Fra_BAR1_3D_draw;
osg::Geode* Fra_Fra_BAR2_3D_draw;
osg::Geode* Fra_Fra_BAR3_3D_draw;
osg::Geode* Fra_Fra_BAR4_3D_draw;
osg::Geode* Fra_Fra_BAR5_3D_draw;
osg::Geode* Fra_Fra_BAR6_3D_draw;
 
void osg_read_file ()
{
Sol_PLATFORM_3D = (osg::Geode*) osgDB::readNodeFile("./solids/plataforma_R05.stl.[0.10000000000000000555].scale");
Sol_BAR1_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BAR2_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BAR3_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BAR4_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BAR5_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BAR6_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BAR1V_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BAR2V_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BAR3V_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BAR4V_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BAR5V_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BAR6V_3D = (osg::Geode*) osgDB::readNodeFile("./solids/barra_mz.stl.[1].scale");
Sol_BALL1A_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL2A_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL3A_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL4A_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL5A_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL6A_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL1D_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL2D_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL3D_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL4D_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL5D_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL6D_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL1C_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL2C_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL3C_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL4C_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL5C_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Sol_BALL6C_3D = (osg::Geode*) osgDB::readNodeFile("./solids/bola.stl.[1].scale");
Fra_Fra_PLATFORM_3D_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
Fra_Fra_BAR1_3D_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
Fra_Fra_BAR2_3D_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
Fra_Fra_BAR3_3D_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
Fra_Fra_BAR4_3D_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
Fra_Fra_BAR5_3D_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
Fra_Fra_BAR6_3D_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
}

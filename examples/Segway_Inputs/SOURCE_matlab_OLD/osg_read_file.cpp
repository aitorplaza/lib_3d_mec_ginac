#include <osg/Geode>
#include <osgDB/ReadFile>
 
osg::Geode* axis;
osg::Geode* Sol_Plataforma3D;
osg::Geode* Sol_RuedaIzq3D;
osg::Geode* Sol_RuedaDcha3D;
osg::Geode* Sol_Manillar3D;
osg::Geode* Pnt_Rider3D;
osg::Geode* Fra_FraABS_draw;
osg::Geode* Sol_Ground3D;
osg::Geode* Vec_VectorP_J1;
osg::Geode* Vec_VectorP_J2;
osg::Geode* Vec_VectorP_S0;
osg::Geode* Vec_VectorP_S1;
osg::Geode* Vec_VectorP_S2;
osg::Geode* Vec_VectorO_P;
 
void osg_read_file ()
{
Sol_Plataforma3D = (osg::Geode*) osgDB::readNodeFile("./solids/Plataformam.stl");
Sol_RuedaIzq3D = (osg::Geode*) osgDB::readNodeFile("./solids/Rueda1m.stl");
Sol_RuedaDcha3D = (osg::Geode*) osgDB::readNodeFile("./solids/Rueda2m.stl");
Sol_Manillar3D = (osg::Geode*) osgDB::readNodeFile("./solids/Manillarm.stl");
Pnt_Rider3D = (osg::Geode*) osgDB::readNodeFile("./point.osg.[0.10000000000000000555].scale");
Fra_FraABS_draw = (osg::Geode*) osgDB::readNodeFile("./axes.osg.[0.10000000000000000555].scale");
Sol_Ground3D = (osg::Geode*) osgDB::readNodeFile("./solids/ground.stl");
Vec_VectorP_J1 = (osg::Geode*) osgDB::readNodeFile("./vector.osg.[1.0].scale");
Vec_VectorP_J2 = (osg::Geode*) osgDB::readNodeFile("./vector.osg.[1.0].scale");
Vec_VectorP_S0 = (osg::Geode*) osgDB::readNodeFile("./vector.osg.[1.0].scale");
Vec_VectorP_S1 = (osg::Geode*) osgDB::readNodeFile("./vector.osg.[1.0].scale");
Vec_VectorP_S2 = (osg::Geode*) osgDB::readNodeFile("./vector.osg.[1.0].scale");
Vec_VectorO_P = (osg::Geode*) osgDB::readNodeFile("./vector.osg.[1.0].scale");
}

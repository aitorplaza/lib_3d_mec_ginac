#include "Frame.h"
#include "System.h"
#include "Globals.h"


void Frame::init (string name , Point * point , Base * base, numeric scale ) {

	this-> name = name;
	this-> point = point;
	this-> base = base;
	this-> scale = scale;
	OpenGLTransformMatrix[0]=1.0;
	OpenGLTransformMatrix[1]=0.0;
	OpenGLTransformMatrix[2]=0.0;
	OpenGLTransformMatrix[3]=0.0;
	OpenGLTransformMatrix[4]=0.0;
	OpenGLTransformMatrix[5]=1.0;
	OpenGLTransformMatrix[6]=0.0;
	OpenGLTransformMatrix[7]=0.0;
	OpenGLTransformMatrix[8]=0.0;
	OpenGLTransformMatrix[9]=0.0;
	OpenGLTransformMatrix[10]=1.0;
	OpenGLTransformMatrix[11]=0.0;
	OpenGLTransformMatrix[12]=0.0;
	OpenGLTransformMatrix[13]=0.0;
	OpenGLTransformMatrix[14]=0.0;
	OpenGLTransformMatrix[15]=1.0;

}

/*
General Frame's constructor
*/
Frame::Frame (  ){
	init ( "" , NULL , NULL,0);
}
/*
Constructor without name , Point and Base
*/
Frame::Frame (  Point* point , Base* base){
	init ( "" , point , base, 1);
}

/*
Constructor with name , Point and Base
*/
Frame::Frame ( string name , Point* point , Base* base){
	init ( name , point , base, 1);
}
/*
Constructor with name , Point and Base
*/
Frame::Frame ( string name , Point* point , Base* base, numeric scale){
	init ( name , point , base, scale);
}
/*
Return the Point of this Frame
*/
Point * Frame::get_Point ( void ) {
	return point;
}


/*
Return the Base of this Frame
*/
Base * Frame::get_Base ( void ) {
	return base;
}


/*
Return the Name of this Frame
*/
string Frame::get_name ( void ) {
	return name;
}

/*
Return the Scale of this Frame
*/
numeric Frame::get_scale ( void ) {
	return scale;
}
/*
Put the Point of this Frame
*/
void Frame::set_Point ( Point * new_point ) {
	point = new_point;
}


/*
Put the Base of this Frame
*/
void Frame::set_Base ( Base * new_base ) {
	base = new_base;
}


/*
Put the name of this Frame
*/
void Frame::set_name ( string new_name ){
	name = new_name;
}


GLdouble * Frame::get_absOpenGLTransformMatrix(){
	std::cout << "Still to have implemented GLdouble * Frame::get_absOpenGLTransformMatrix()" << std::endl;
	return OpenGLTransformMatrix;
}


/*
Destructor
*/
Frame::~Frame ( void ) {}


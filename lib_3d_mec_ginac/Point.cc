#include "Point.h"
#include "System.h"

using std::string;


/* 
Point's general constructor
*/
Point::Point ( void ) {
	this-> name = "";
	this-> previous_point = NULL;
	this-> position_vector = NULL;
}


/*
Constructor with name, previous_Point and previous_Vector
*/
Point::Point ( string name , Point * previous_point , Vector3D * position_vector ) {
	this-> name = name;
	this-> previous_point = previous_point;
	this-> position_vector = position_vector;
} 


/*
Return the previous_Point of this Point
*/
Point * Point::get_Previous_Point ( void ) {
	return previous_point;
}


/*
Return the position_Vector of this Point
*/
Vector3D * Point::get_Position_Vector ( void ) {
	return position_vector;
}


/*
Return the Point name
*/
string Point::get_name ( void ) {
	return name;
}


/*
Put the Point name 
*/
void Point::set_name ( string new_name ) {
	name = new_name;
}


/*
Destructor
*/
Point::~Point ( void ) {}


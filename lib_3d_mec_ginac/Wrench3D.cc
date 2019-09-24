#include "Wrench3D.h"
#include "System.h"
#include "Globals.h"


void Wrench3D::init (string name, Vector3D F, Vector3D M , Point * P, Solid * Sol, string type ){
	this-> name = name;
	this-> F = F;
	this-> M = M;
	this-> P = P;
	this-> Sol = Sol;
	this-> type = type;
}

/*
General Wrench's constructor
*/
Wrench3D::Wrench3D ( void ){
	init ( "" , NULL , NULL, NULL, NULL, "");

}

/*
Wrench's constructor
*/
Wrench3D::Wrench3D (string name, Vector3D F, Vector3D M , Point * P, Solid * Sol, string type ){
	init ( name , F, M, P, Sol, type);
}

/*
Return the Name of this Wrench
*/
string Wrench3D::get_name ( void ) {
	return name;
}

/*
Return the Force Vector of this Wrench
*/
Vector3D Wrench3D::get_Force ( void ) {
	return F;
}

/*
Return the Force Vector of this Wrench
*/
Vector3D Wrench3D::get_Momentum ( void ) {
	return M;
}
/*
Return the Point of this Wrench
*/
Point * Wrench3D::get_Point ( void ) {
	return P;
}

/*
Return the Point of this Frame
*/
Solid * Wrench3D::get_Solid ( void ) {
	return Sol;
}

/*
Return the  type of this Wrench
*/
string Wrench3D::get_Type ( void ) {
	return type;
}
/*
Destructor
*/
Wrench3D::~Wrench3D ( void ) {}

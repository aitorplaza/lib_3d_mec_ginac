#include "Solid.h"
#include "Frame.h"
#include "System.h"
#include "Globals.h"

//using GiNaC::ex;


void Solid::init( string name , Point * point , Base * base, symbol_numeric * new_mass , Vector3D * new_CM, Tensor3D * new_IT, Point * new_G){

	this-> mass = new_mass;
	this-> CM = new_CM;
	this-> IT = new_IT;
	this-> G = new_G;
}


/*
General Solid constructor
*/
Solid::Solid ( void ) : Frame ( ){
	mass=NULL;
	CM=NULL;
	IT=NULL;
	G = NULL;
}

/*
Constructor with name , Point , Base, mass, Center of mass vector and Inertia Tensor
*/
Solid::Solid ( string name , Point* point ,Base* base, symbol_numeric *new_mass , Vector3D* new_CM , Tensor3D* new_IT, Point * new_G): Frame (  name ,  point ,  base){
 init( name , point , base, new_mass, new_CM, new_IT,new_G);
}

/*
Return the center of mass vector
*/
Vector3D * Solid::get_CM ( void ){
	try {
	if ( CM == NULL )throw 1;
	return CM;   
	}catch ( int e ) {
        outError ( "ERR -  The Center of Mass Vector is not defined" );
	}
}

/*
Return the Inertia Tensor
*/
Tensor3D * Solid::get_IT ( void ){
	try {
	if ( IT == NULL )throw 1;
	return IT;   
	}catch ( int e ) {
        outError ( "ERR -  The Inertia Tensor is not defined" );
	}
}

/*
Return the mass
*/
symbol_numeric * Solid::get_mass ( void ){	
	try {
	if ( mass == NULL )throw 1;
	return mass;   
	}catch ( int e ) {
        outError ( "ERR -  The mass is not defined" );
	}
}
/*
Return MassCenter Point
*/
Point * Solid::get_G(void){
	return G;
}

/*
Destructor
*/
Solid::~Solid ( void ) {};


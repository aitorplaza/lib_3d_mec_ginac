#include "Drawing3D.h"
#include "System.h"
#include "Globals.h"


void Drawing3D::init ( string name, string type, Point * point , Base * base){
	this-> name = name;
	this-> type = type;
	this-> P = point;
	this-> B = base;
	this-> file = "";
	//this-> color = 0,0,0,1;
	//this-> color = 9 ,9 ,9 ,9 ;
	this-> color.append( 9 ); this-> color.append( 9 );this-> color.append( 9 );this-> color.append( 9 );
    this-> scale = 1;
}

/*
General DRAWING3D constructor
*/
Drawing3D::Drawing3D ( void ){
	init ( "" ,"", NULL , NULL);

}

/*
DRAWING3 constructor
*/		
Drawing3D::Drawing3D ( string name, string type, Point * P , Base * B){
        init ( name, type, P , B);
}

/*
Return the name
*/
string Drawing3D::get_name ( void ){	
	return name;   
}

/*
Set the file
*/
void Drawing3D::set_file ( string new_file){	
	file = new_file;  
}

/*
Set the vector
*/
void Drawing3D::set_vector ( Vector3D new_vector){	
	V = new_vector;  
}
/*
Set the vector
*/
Vector3D Drawing3D::get_vector ( void){	
	return V;  
}




/*
Set the color and transparency
*/
void Drawing3D::set_color ( lst new_color){	
	color = new_color;  
}

/*
Set the scale
*/
void Drawing3D::set_scale (numeric new_scale){	
	scale = new_scale;  
}

/*
Return the file
*/
string Drawing3D::get_file ( void ){	
	return file;  
}

/*
Return the color and transparency
*/
lst Drawing3D::get_color ( void ){	
	return color;  
}

/*
Return the type
*/
string Drawing3D::get_type ( void ){	
	return type;  
}

/*
Return the point
*/
Point * Drawing3D::get_Point ( void ) {
	return P;
}


/*
Return the Base
*/
Base * Drawing3D::get_Base ( void ) {
	return B;
}

/*
Return the scale
*/
numeric Drawing3D::get_scale ( void ) {
	return scale;
}






/*
Destructor
*/
Drawing3D::~Drawing3D ( void ) {}

#include "Wrench3D.h"
#include "System.h"
#include "Globals.h"


void Wrench3D::init (string name, Vector3D F, Vector3D M , Point * P, Solid * Sol, string type, System * system ){
	this-> name = name;
	this-> F = F;
	this-> M = M;
	this-> P = P;
	this-> Sol = Sol;
	this-> type = type;
	this-> system = system; 
}

/*
General Wrench's constructor
*/
Wrench3D::Wrench3D ( void ){
	init ( "" , NULL , NULL, NULL, NULL, "", NULL);
}

/*
Wrench's constructor
*/
Wrench3D::Wrench3D (string name, Vector3D F, Vector3D M , Point * P, Solid * Sol, string type ){
	init ( name , F, M, P, Sol, type, F.get_System ( ));
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
Vector3D Wrench3D::get_Moment ( void ) {
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
Set Vector3D System
*/
void Wrench3D::set_System ( System * new_system ) {
	system = new_system;
}

/* 
Unatomize Wrench3D
*/
Wrench3D Wrench3D::unatomize ( void ){
	    Wrench3D Wrench3DOut;
	    //if  ( atomization == NO ){
	        //Wrench3DOut=*this;
	        //return Wrench3DOut;
	    //}
	    Wrench3DOut=*this;
	    Wrench3DOut.F = ::unatomize ( this->F  );
	    Wrench3DOut.M = ::unatomize ( this->M  );
	    return Wrench3DOut;
}

/*
Sum of two Wrench3D
*/
Wrench3D Wrench3D::at_Point ( Point * PointB ) {
	
Wrench3D WrenchSol; 

WrenchSol.system = this->system; 
WrenchSol.F = this->F;
WrenchSol.M = this->M+(this->system->Position_Vector( PointB, this->P )^this->F);
WrenchSol.P = PointB ;    

return WrenchSol;
}


/*
Sum of two Wrench3D
*/
Wrench3D operator + ( const Wrench3D & Wrench3DA , const Wrench3D & Wrench3DB ){
	
Wrench3D WrenchSol; 

WrenchSol.system = Wrench3DA.system; 

Point * reducedPoint = WrenchSol.system-> Reduced_Point ( Wrench3DA.P , Wrench3DB.P );

WrenchSol.P=reducedPoint;

Vector3D MA_tras=Wrench3DA.M+(WrenchSol.system->Position_Vector( reducedPoint, Wrench3DA.P )^Wrench3DA.F);
Vector3D MB_tras=Wrench3DB.M+(WrenchSol.system->Position_Vector( reducedPoint, Wrench3DB.P )^Wrench3DB.F);

WrenchSol.F = Wrench3DA.F + Wrench3DB.F ;
WrenchSol.M = MA_tras + MB_tras ;

return WrenchSol;
}

/*
Diference of two Wrench3D
*/
Wrench3D operator - ( const Wrench3D & Wrench3DA , const Wrench3D & Wrench3DB ){
	
Wrench3D WrenchSol; 

WrenchSol.system = Wrench3DA.system; 

Point * reducedPoint = WrenchSol.system-> Reduced_Point ( Wrench3DA.P , Wrench3DB.P );

WrenchSol.P=reducedPoint;

Vector3D MA_tras=Wrench3DA.M+(WrenchSol.system->Position_Vector( reducedPoint, Wrench3DA.P )^Wrench3DA.F);
Vector3D MB_tras=Wrench3DB.M+(WrenchSol.system->Position_Vector( reducedPoint, Wrench3DB.P )^Wrench3DB.F);

WrenchSol.F = Wrench3DA.F - Wrench3DB.F ;
WrenchSol.M = MA_tras - MB_tras ;

return WrenchSol;
}

/* 
Negation of a Wrench3D
*/
Wrench3D operator - ( const Wrench3D & Wrench3DA ) {
	
Wrench3D WrenchSol;

WrenchSol.system = Wrench3DA.system; 

WrenchSol.F=-Wrench3DA.F;
WrenchSol.M=-Wrench3DA.M;

return WrenchSol;
}

ex operator * ( const Wrench3D & Wrench3DA , const Wrench3D & Wrench3DB ){
System * sys = Wrench3DA.system; 

Point * reducedPoint = sys-> Reduced_Point ( Wrench3DA.P , Wrench3DB.P );

Vector3D MA_tras=Wrench3DA.M+(sys->Position_Vector( reducedPoint, Wrench3DA.P )^Wrench3DA.F);
Vector3D MB_tras=Wrench3DB.M+(sys->Position_Vector( reducedPoint, Wrench3DB.P )^Wrench3DB.F);

return Wrench3DA.F * MB_tras + MA_tras * Wrench3DB.F;
}

Wrench3D operator * ( const Wrench3D & Wrench3DA , const ex & expression ){
	
Wrench3D WrenchSol;

WrenchSol = Wrench3DA; 

WrenchSol.F= expression*WrenchSol.F;
WrenchSol.M= expression*WrenchSol.M;

return WrenchSol;
}

Wrench3D operator * ( const ex & expression , const Wrench3D & Wrench3DA ){

Wrench3D WrenchSol;

WrenchSol = Wrench3DA; 

WrenchSol.F= expression*WrenchSol.F;
WrenchSol.M= expression*WrenchSol.M;

return WrenchSol;
}


/* 
Output of one Vectors3D
*/
ostream& operator << ( ostream& os , const Wrench3D & Wrench3DA ){
	
	os << Wrench3DA.name << "=" << endl;       
	os << Wrench3DA.F;
	os << Wrench3DA.M; 
	os << Wrench3DA.P->get_name(); 
	os << endl; 
	return os;  
}

/*
Destructor
*/
Wrench3D::~Wrench3D ( void ) {}

#include "Vector3D.h"
#include "Base.h"
#include "System.h"
#include "Frame.h"
#include "Globals.h"


using GiNaC::ex;
using GiNaC::relational;
using GiNaC::matrix;
using GiNaC::wildcard;
using std::ostream;
using std::string;
using std::exception;


/* 
Method that initialize the Vector3D atributes
 */
void Vector3D::init ( string name , matrix mat , Base * base , System * system ){
	try{
		if ( ( mat.rows () != 3 ) or ( mat.cols () != 1 ) ) throw 1; 
		this-> system = system; 
		this-> base = base; 
	}catch ( int i ) {
		this-> name = ""; 
		matrix empty; 
		this-> mat = empty; 
		this-> base = NULL; 
		this-> system = NULL; 
		outError ( "ERR - Incompatble dimensions in Vector3D" ); 
	}
}

/* 
Constructor with name and Base
The dafault matrix is a 3x1 with 0's
*/
Vector3D::Vector3D ( string name , Base * base ) : Matrix ( name , 3 , 1 ){
	this-> base = base; 
}


/* 
Constructor with name , matrix and Base
The matrix should have 3 rows and 1 col
*/
Vector3D::Vector3D ( string name , Matrix mat , Base * base ) : Matrix ( name , mat ){
	init ( name , mat.get_matrix () , base , NULL ); 
}


/* 
Constructor with name , Matrix , Base and System
*/
Vector3D::Vector3D ( string name , Matrix mat , Base * base , System * system ) : Matrix ( name , mat ){
	init ( name , mat.get_matrix () , base , system ); 
}


/* 
Constructor with name , matrix , Base ( this name ) and System
*/
Vector3D::Vector3D ( string name , Matrix mat , string base_name , System * system ) : Matrix ( name , mat ){
	init ( name , mat.get_matrix () , system-> get_Base ( base_name ) , system ); 
}


/* 
Constructor with name , three ex and Base
*/
Vector3D::Vector3D ( string name , ex expression1 , ex expression2 , ex expression3 , Base * base ) : Matrix ( name , 3 , 1 , & expression1 , & expression2 , & expression3 ){
	this-> base = base; 
}


/* 
Constructor with name , three ex , Base and System
*/
Vector3D::Vector3D ( string name , ex expression1 , ex expression2 , ex expression3 , Base * base , System * system ) : Matrix ( name , 3 , 1 , & expression1 , & expression2 , & expression3 ){
	this-> system = system; 
	this-> base = base; 
}


/* 
Constructor with three ex , Base and System
*/
Vector3D::Vector3D ( ex expression1 , ex expression2 , ex expression3 , Base * base , System * system ) : Matrix ( 3 , 1 , & expression1 , & expression2 , & expression3 ){
	this-> system = system; 
	this-> base = base; 
}


/* 
Constructor with name , three ex , Base ( this name ) and System
*/
Vector3D::Vector3D ( string name , ex expression1 , ex expression2 , ex expression3 , string base_name , System * system ) : Matrix ( name , 3 , 1 , & expression1 , & expression2 , & expression3 ){
	this-> system = system; 
	this-> base = system-> get_Base ( base_name ); 
}


/* 
Vectro3D general constructor
*/
Vector3D::Vector3D ( void ) : Matrix ( 3 , 1 ){
	//name = "";
	base = NULL;
}

/* 
Constructor with Base
Default 3x1 matrix with 0'system
*/
Vector3D::Vector3D ( Base * base ) : Matrix ( 3 , 1 ){
	this-> base = base; 
}


/* 
Constructor with matrix and Base
*/
Vector3D::Vector3D ( Matrix mat , Base * base ) : Matrix ( mat ){
	init ( "" , mat.get_matrix () , base , NULL ); 
}


/* 
Constructor with matrix , Base and System
*/
Vector3D::Vector3D ( Matrix mat , Base * base , System * system ) : Matrix ( mat ){
	init ( "" , mat.get_matrix () , base , system ); 
}


/* 
Constructor with matrix , Base ( this name ) and System
*/
Vector3D::Vector3D ( Matrix mat , string base_name , System * system ) : Matrix ( mat ){
	init ( "" , mat.get_matrix () , system-> get_Base ( base_name ) , system ); 
}


/* 
Return the Base of Vector3D
*/
Base * Vector3D::get_Base ( void ) {
	return base; 
}

/* 
Return the Module of Vector3D
*/
ex Vector3D::get_module ( void ) {
	Vector3D aux = * this; 
        return sqrt(aux(0,0)*aux(0,0) + aux(1,0)*aux(1,0) + aux(2,0)*aux(2,0)); 
}


/* 
Put the Base of Vector3D
*/
void Vector3D::set_Base ( Base * new_base ){
	base = new_base; 
}

/* 
Put one System in this Vector3D
*/
void Vector3D::set_System ( System * new_system ) {
	system = new_system;
}


/* 
Return the System of this Vector3D
*/
System * Vector3D::get_System ( void ) {
	return system;
}

/* 
Return the Nameof this Vector3D
*/
string Vector3D::get_Name ( void ) {
	return name;
}
/* 
Return the Nameof this Vector3D
*/
void Vector3D::set_Name ( string s_name ) {
	name = s_name;
}

/* 
Returns the vector as a skew matrix
*/
Matrix Vector3D::skew (void){
   Vector3D Vaux = * this;
   //~ Matrix Maux ( 3 , 3 , lst ( 0             , (ex)(-Vaux(2,0)) , (ex)Vaux(1,0)     ,
                             //~ (ex)Vaux(2,0)   , 0                , (ex)(-Vaux(0,0))  , 
                             //~ (ex)(-Vaux(1,0)), (ex)Vaux(0,0)    , 0                 ) );   
   
   lst laux;
   laux.append( 0 )                ; laux.append( (ex)(-Vaux(2,0)) ) ; laux.append( (ex)Vaux(1,0) );
   laux.append( (ex)Vaux(2,0) )    ; laux.append( 0 )                ; laux.append( (ex)(-Vaux(0,0)) );  
   laux.append( (ex)(-Vaux(1,0)) ) ; laux.append( (ex)Vaux(0,0) )    ; laux.append(0  );   
   
   Matrix Maux ( 3 , 3 , laux );
   return Maux;
}

/* 
Returns the vector representated in another base
*/
Vector3D Vector3D::change_Base (Base * new_base){
    Vector3D Vaux = * this;
    System * sys = Vaux.system; 
    Matrix a = sys-> Rotation_Matrix ( new_base , Vaux.base ) * ( Matrix )Vaux;  
    Vector3D vectorSol( a , new_base ); 
	vectorSol.set_System ( sys ); 
	return vectorSol; 
}



/* 
Return the derivate of Vector3D's Frame
*/
//Vector3D Vector3D::Dt ( Frame * frame ){
//	return Dt ( frame-> get_Base () ); 
//}


/* 
Return the derivate of Vector3D's Base
*/
//Vector3D Vector3D::Dt ( Base * base ){
//	Vector3D aux ( "" , system-> Dt ( * this ) , this-> base , system ); 
//	Vector3D aux2 = system-> Angular_Velocity ( base , this-> base ); 
//	return aux + ( aux2 ^ * this ); 
//}

/* 
Method that substitute the expresions indicates in the relational form.
*/
Vector3D Vector3D::subs ( relational relation ){
	Vector3D sol = * this; 
	Vector3D aux = unatomize ( * this ); 
	ex le = relation.lhs (); 
	ex rig = relation.rhs (); 
	for ( int i = 0 ; i < rows () ; i ++ )
		for ( int j = 0 ; j < cols () ; j ++ ){
			sol ( i , j ) = aux ( i , j ).subs ( le + wild ( 1 ) == rig + wild ( 1 ) ); 
			sol ( i , j ) = aux ( i , j ).subs ( le == rig ); 
		}
	return atomize ( sol ); 
}


/* 
Method that make the Vector3D operations calculums
*/
Vector3D Vector3D::Operations ( const Vector3D & Vector3DA , const Vector3D & Vector3DB , const int flag ){
	try{
		if ( ( Vector3DA.system == NULL ) or ( Vector3DB.system == NULL ) ) throw 1; 
		System * sys = Vector3DA.system; 
        
        Base * reducebase = sys-> Reduced_Base ( Vector3DA.base , Vector3DB.base ); 

		/* Use Matrix objects for make these operations */
		Matrix a = sys-> Rotation_Matrix ( reducebase , Vector3DA.base ) * ( Matrix )Vector3DA; 
		Vector3D vectorAux1 ( a , reducebase ); 

		a = sys-> Rotation_Matrix ( reducebase , Vector3DB.base ) * ( Matrix )Vector3DB; 
		Vector3D vectorAux2 ( a , reducebase ); 

		if ( flag == 1 )// + 
            a = ( Matrix )vectorAux1 + ( Matrix )vectorAux2 ;
		else if ( flag == 2 )//-
            a = ( Matrix )vectorAux1 - ( Matrix )vectorAux2 ;
		else if ( flag == 3 ){//^
			a ( 0 , 0 ) = atomize_ex ( atomize_ex ( vectorAux1 ( 1 , 0 ) * vectorAux2 ( 2 , 0 ) ) - atomize_ex ( vectorAux1 ( 2 , 0 ) * vectorAux2 ( 1 , 0 ) ) ); 
			a ( 1 , 0 ) = atomize_ex ( atomize_ex ( -vectorAux1 ( 0 , 0 ) * vectorAux2 ( 2 , 0 ) ) + atomize_ex ( vectorAux1 ( 2 , 0 ) * vectorAux2 ( 0 , 0 ) ) ); 
			a ( 2 , 0 ) = atomize_ex ( atomize_ex ( vectorAux1 ( 0 , 0 ) * vectorAux2 ( 1 , 0 ) ) - atomize_ex ( vectorAux1 ( 1 , 0 ) * vectorAux2 ( 0 , 0 ) ) ); 
		}
		
		Vector3D vectorSol ( a , reducebase ); 
		vectorSol.set_System ( sys ); 
		return vectorSol; 
        
	}catch ( exception & p ) {
		outError ( "ERR - Unexpected error building Vector3D" ); 
	}catch ( int i ){
		outError ( "ERR- At Vector3D Vector3D::Operations: The system associated to the vector is NULL" ); 
	}
	Vector3D vacio; 
	return vacio; 

}


/* 
Sum of two Vectors3D
*/
Vector3D operator + ( const Vector3D & Vector3DA , const Vector3D & Vector3DB ){
    Matrix VA = (Matrix) Vector3DA;
    Matrix VB = (Matrix) Vector3DB;
    
    if (VA(0,0) == 0 && VA(1,0)== 0   && VA(2,0)== 0)
        return Vector3DB;
        
    if (VB(0,0) == 0 && VB(1,0)== 0   && VB(2,0)== 0)
        return Vector3DA;
        
	return Vector3D::Operations ( Vector3DA , Vector3DB , 1 ); 
}


/* 
Diference of two Vectors3D
*/
Vector3D operator - ( const Vector3D & Vector3DA , const Vector3D & Vector3DB ){
    Matrix VA = (Matrix) Vector3DA;
    Matrix VB = (Matrix) Vector3DB;
    
    if (VA(0,0) == 0 && VA(1,0)== 0   && VA(2,0)== 0)
        return Vector3DB;
        
    if (VB(0,0) == 0 && VB(1,0)== 0   && VB(2,0)== 0)
        return Vector3DA;
            
	return Vector3D::Operations ( Vector3DA , Vector3DB , 2 ); 
}


/* 
Vectorial multiplication of two Vectors3D
*/
Vector3D operator ^ ( const Vector3D & Vector3DA , const Vector3D & Vector3DB ){
	return Vector3D::Operations ( Vector3DA , Vector3DB , 3 ); 
}


/* 
Negate one Vectors3D
*/
Vector3D operator - ( const Vector3D & Vector3DA ) {
	try{
		Matrix aux ( Vector3DA.mat.rows () , Vector3DA.mat.cols () ); 
		Matrix result ( aux - ( Matrix )Vector3DA );
		Vector3D VectorSol ( Vector3DA.name , result , Vector3DA.base , Vector3DA.system );  
		return VectorSol; 
	}catch ( exception & p ) {
		outError ( "ERR - Unexpected error in in operator - of Vector3D" ); 
		Vector3D empty; 
		return empty; 
	}
}


/* 
Scalar multiplication between two Vectors3D
*/
ex operator * ( const Vector3D & Vector3DA , const Vector3D & Vector3DB ){
	try{
		System * sys = Vector3DA.system; 

		Base * reducebase = sys-> Reduced_Base ( Vector3DA.base , Vector3DB.base ); 

		/* Do the next for transform the Vectors3D to a common Basis */
		Matrix vectorAux1 = ( Matrix )sys-> Rotation_Matrix ( reducebase , Vector3DA.base ) * ( Matrix )Vector3DA; 

		Matrix vectorAux2 = ( Matrix )sys-> Rotation_Matrix ( reducebase , Vector3DB.base ) * ( Matrix )Vector3DB; 

		vectorAux1 = vectorAux1.transpose (); 
		ex expression = ( vectorAux1 * vectorAux2 ) ( 0 , 0 ); 
		return atomize_ex ( expression ); 
	}catch ( exception & p ) {
		outError ( "ERR - Unexpected error in in operator * of Vector3D" ); 
		ex vacio; 
		return vacio; 
	}catch ( int i ){
		outError ( "ERR- Vectors3D with incompatibles Systems" ); 
		ex vacio; 
		return vacio; 
	}
}


/* 
Multiplication between one ex and one Vector3D
*/
Vector3D operator * ( const ex & expression , const Vector3D & Vector3DA ){
	Vector3D Vector3DB = Vector3DA;
	try{
		for ( int i = 0 ; i < Vector3DB.mat.rows () ; i ++ ){
 			for ( int j = 0 ; j < Vector3DB.mat.cols () ; j ++ ){
 			Vector3DB.mat ( i , j ) = atomize_ex ( expression * Vector3DB.mat ( i , j ) ); 
			}
 		}
		return Vector3DB; 
	}catch ( exception & p ) {
 		outError ( "ERR - Multiplication between ex and Vector3D" ); 
		Vector3D empty; 
		return empty; 
	}
}


/* 
Multiplication between one Vector3D and one ex
*/
Vector3D operator * ( const Vector3D & Vector3DA , const ex & expression ){
	return expression * Vector3DA; 
}


/* 
Output of one Vectors3D
*/
ostream & operator << ( ostream & os , const Vector3D & vectorA ){
	try{
		if ( vectorA.name == "ERROR" ) throw 1; 
		//os << "...%" << vectorA.name << "{\n["; 
        os << vectorA.name << "{\n[";
		for ( int i = 0 ; i < vectorA.mat.rows () ; i ++ ){
 			for ( int j = 0 ; j < vectorA.mat.cols () ; j ++ ){
 			os << vectorA.mat ( i , j ); 
				if ( j < vectorA.mat.cols ()-1 )os << " , "; 
				else 
					if ( ( j == vectorA.mat.cols ()-1 ) && ( ( i == vectorA.mat.rows ()-1 ) ) ) os << ""; 
					else os << "; \n"; 
			}
 		}
		os << "]\n}"; 
 		//os << "]\n%}";        
		os << vectorA.base-> get_name (); 
        os << endl; 
		return os; 
	}catch ( exception & p ) {
		outError ( "ERR - Unexpected error in out of Vector3D" ); 
		return os; 
	}catch ( int e ){
		return os; 
	}
}


/*
Class destructor
*/
Vector3D::~Vector3D () {}


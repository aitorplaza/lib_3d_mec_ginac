#include "Tensor3D.h"
#include "System.h"
#include "Globals.h"

using GiNaC::ex;
using GiNaC::relational;
using GiNaC::matrix;
using GiNaC::wildcard;
using std::ostream;
using std::string;
using std::exception;


/*
Tensor3D's general constructor
*/
Tensor3D::Tensor3D () {}


/*
Method that initialize the Tensor3D atributes
*/
void Tensor3D::init ( string name , matrix mat , Base * base , System * system ) {
	try{
		if ( ( mat.rows () != 3 ) or ( mat.cols () != 3 ) ) throw 1;
		this-> system = system;
		this-> base = base;
	}catch ( int i ) {
		outError ( "ERR - Tensor3D with bad dimensions , must be 3x3" );
		matrix erase;
		this-> mat = erase;
		this-> system = NULL;
		this-> base = NULL;
		this-> name = "";
	}
}


/*
Constructor with name , Matrix and Base
The matrix should have ones dimensions of 3x3
*/
Tensor3D::Tensor3D ( string name , Matrix * mat , Base * base ) : Matrix ( name , * mat ) {
	init ( name , mat-> get_matrix () , base , NULL );
}

/*
Constructor Matrix and Base
The matrix should have ones dimensions of 3x3
*/
Tensor3D::Tensor3D ( Matrix mat , Base * base ) : Matrix ( " ", mat ) {
	init ( "" , mat.get_matrix () , base , NULL );
}


/*
Constructor Matrix, Base and System
The matrix should have ones dimensions of 3x3
*/
Tensor3D::Tensor3D ( Matrix mat , Base * base, System * system ) : Matrix ( " ", mat ) {
	init ( "" , mat.get_matrix () , base , system );
}

/*
Constructor with name , nine ex ( for make a matrix with 3x3 dimensions ) and Base
*/
Tensor3D::Tensor3D ( string name , ex exp1 , ex exp2 , ex exp3 , ex exp4 , ex exp5 , ex exp6 , ex exp7 , ex exp8 , ex exp9 , Base * base ) : Matrix ( name , 3 , 3 , & exp1 , & exp2 , & exp3 , & exp4 , & exp5 , & exp6 , & exp7 , & exp8 , & exp9 ) {
	this-> base = base;
}


/*
Constructor with name , Matrix , Base and System
*/
Tensor3D::Tensor3D ( string name , Matrix  mat , Base * base , System * system ) : Matrix ( name , mat ) {
	init ( name , mat.get_matrix () , base , system );
}


/*
Constructor with name , nine ex ( for make a matrix with 3x3 dimensions ) , Base and System
*/
Tensor3D::Tensor3D ( string name , ex exp1 , ex exp2 , ex exp3 , ex exp4 , ex exp5 , ex exp6 , ex exp7 , ex exp8 , ex exp9 , Base * base , System * system ) : Matrix ( name , 3 , 3 , & exp1 , & exp2 , & exp3 , & exp4 , & exp5 , & exp6 , & exp7 , & exp8 , & exp9 ) {
	this-> base = base;
	this-> system = system;
}


/*
Put the Base of this Tensor3D
*/
void Tensor3D::set_Base ( Base * new_base ) {
	base = new_base;
}


/*
Return the Base of this Tensor3D
*/
Base * Tensor3D::get_Base () {
	return base;
}

/*
Put one System in this Tensor3D
*/
void Tensor3D::set_System ( System * new_system ) {
	system = new_system;
}


/*
Return the System of this Tensor3D
*/
System * Tensor3D::get_System ( void ) {
	return system;
}
/*
Put one Name in this Tensor3D
*/

void Tensor3D::set_Name ( string new_name ) {
	name = new_name;
}


/*
Returns the Tensor representated in another base
*/
Tensor3D Tensor3D::in_Base (Base * new_base){
    Tensor3D Taux = * this;
    System * sys = Taux.system;
    Matrix a = sys-> Rotation_Matrix ( new_base , Taux.base ) * ( Matrix )Taux * sys-> Rotation_Matrix ( Taux.base , new_base );
    Tensor3D TensorSol ( a , new_base );
    TensorSol.set_System ( sys );
	return TensorSol;

}


/*
Method that substitute the expressions indicates in the relational form.
*/
Tensor3D Tensor3D::subs ( relational relation ) {
	Tensor3D sol = * this;
	Tensor3D aux = unatomize ( * this );
	ex le = relation.lhs ();
	ex rig = relation.rhs ();
	for ( int i = 0 ; i < rows () ; i++ )
		for ( int j = 0 ; j < cols () ; j++ ) {
			sol ( i , j ) = aux ( i , j ).subs ( le+wild ( 1 ) == rig+wild ( 1 ) );
			sol ( i , j ) = aux ( i , j ).subs ( le == rig );
		}
	return atomize ( sol );
}


/*
Method that make the Tensor3D operations calculums
*/
Tensor3D Tensor3D::Operations ( const Tensor3D & Tensor3DA , const Tensor3D & Tensor3DB , const int flag ) {
	try{
		if ( ( Tensor3DA.system == NULL ) or ( Tensor3DB.system == NULL ) ) throw 1;
		System * sys = Tensor3DA.system;

		Base * reducebase = sys-> Reduced_Base ( Tensor3DA.base , Tensor3DB.base );

		/* Do the next for transform the Tensors3D to a common Basis */

		Matrix a = sys-> Rotation_Matrix ( reducebase , Tensor3DA.base ) * ( Matrix )Tensor3DA * sys-> Rotation_Matrix ( Tensor3DA.base , reducebase );
		Tensor3D Tensor3DAux1 ( a , reducebase );

		a = sys-> Rotation_Matrix ( reducebase , Tensor3DB.base ) * ( Matrix )Tensor3DB * sys-> Rotation_Matrix ( Tensor3DB.base , reducebase );
		Tensor3D Tensor3DAux2 ( a , reducebase );

		if ( flag == 1 )//+
			a = ( Matrix )Tensor3DAux1 + ( Matrix )Tensor3DAux2;
		else if ( flag == 2 )//-
			a = ( Matrix )Tensor3DAux1 - ( Matrix )Tensor3DAux2;
		else if ( flag == 2 )//*
			a = ( Matrix )Tensor3DAux1 * ( Matrix )Tensor3DAux2;

		Tensor3D tensorSol ( a  , reducebase );
		tensorSol.set_System ( sys );
		return tensorSol;
	}catch ( exception & p ) {
		outError ( "ERR - Unexpected error in operatorions between Tensor3Ds" );
		Tensor3D vacio;
		return vacio;
	}
	catch ( int i ) {
		outError ( "Tensors3D with invalid Systems" );
		Tensor3D vacio;
		return vacio;
	}
}


/*
Method that make the  operations calculates between Tensor3D and expressions
*/
Tensor3D Tensor3D::Operations ( const Tensor3D & Tensor3DA , const ex & expression , int flag ) {
	try{
		Tensor3D sol;
		if ( flag == 1 ) {//expression * Matrix
			matrix aux ( Tensor3DA.mat.rows () , Tensor3DA.mat.cols () );
			for ( int i = 0; i < aux.rows () ;  i++ )
    				for ( int j = 0; j < aux.cols () ;  j++ )
          				aux ( i , j ) = expression * Tensor3DA.mat ( i , j );
			Tensor3D result ( Tensor3DA.name , aux , Tensor3DA.base, Tensor3DA.system);
			sol = result;
		}
		else if ( flag == 2 ) {//Matrix * expression
			matrix aux ( Tensor3DA.mat.rows () , Tensor3DA.mat.cols () );
			for ( int i = 0; i < aux.rows () ;  i++ )
    				for ( int j = 0; j < aux.cols () ;  j++ )
          				aux ( i , j ) = Tensor3DA.mat ( i , j ) * expression;
			Tensor3D result ( Tensor3DA.name , aux , Tensor3DA.base, Tensor3DA.system);
			sol = result;
		}
		return sol;
	}catch ( exception & p ) {
		outError ( "ERR - Failure in Matrix operation" );
		Tensor3D empty;
		return empty;
	}
}



/*
Sum betweewn two Tensor3D
*/
Tensor3D operator + ( const Tensor3D & Tensor3DA , const Tensor3D & Tensor3DB ) {
		return Tensor3D::Operations ( Tensor3DA , Tensor3DB , 1 );
}


/*
Diference between two Tensor3D
*/
Tensor3D operator - ( const Tensor3D & Tensor3DA , const Tensor3D & Tensor3DB ) {
		return Tensor3D::Operations ( Tensor3DA , Tensor3DB , 2 );
}


/*
Multiplication betweewn two Tensor3D
*/
Tensor3D operator * ( const Tensor3D & Tensor3DA , const Tensor3D & Tensor3DB ) {
		return Tensor3D::Operations ( Tensor3DA , Tensor3DB , 3 );
}


/*
Multiplication betweewn one Tensor3D and one Vector3D
*/
Vector3D operator * ( const Tensor3D & Tensor3DA , Vector3D & VectorB ) {
	try{
		if ( ( Tensor3DA.system == NULL ) or ( VectorB.get_System () == NULL ) ) throw 1;
		System * sys = Tensor3DA.system;

		Base * reducebase = sys-> Reduced_Base ( Tensor3DA.base , VectorB.get_Base () );

		/* Do the next for transform the Tensors3D to a common Basis */
		Matrix a = sys-> Rotation_Matrix ( reducebase , Tensor3DA.base ) * ( Matrix )Tensor3DA * sys-> Rotation_Matrix ( Tensor3DA.base , reducebase );
		Tensor3D Tensor3DAux1 ( a , reducebase );

		a = sys-> Rotation_Matrix ( reducebase , VectorB.get_Base () ) * ( Matrix )VectorB;
		Vector3D VectorAux2 ( a , reducebase );

		a = ( Matrix )Tensor3DAux1 * ( Matrix )VectorAux2;
		Vector3D VectorSol ( a , reducebase );
		VectorSol.set_System ( sys );
		return VectorSol;
	}catch ( exception & p ) {
		outError ( "ERR - Unexpected error in operator * of Tensor3D" );
		Vector3D vacio;
		return vacio;
	}
	catch ( int i ) {
		outError ( "Tensors3D with invalid Systems" );
		Vector3D vacio;
		return vacio;
	}
}


/*
Multiplication between one ex and one Matrix
*/
Tensor3D operator * ( const ex & expression , const Tensor3D & Tensor3DA ) {
	return Tensor3D::Operations ( Tensor3DA , expression , 1 );
}


/*
Multiplication between one Matrix and one ex
*/
Tensor3D operator * ( const Tensor3D & Tensor3DA , const ex & expression ) {
	return Tensor3D::Operations ( Tensor3DA , expression , 2 );
}


/*
Tensor3D output
*/
ostream & operator << ( ostream & os , const Tensor3D & Tensor3DA ) {
	try{
		if ( Tensor3DA.name == "ERROR" ) throw 1;
		os << "...%" << Tensor3DA.name << "{\n[";

		for ( int i = 0; i < Tensor3DA.mat.rows ( ) ; i++ ) {
 			for ( int j = 0; j < Tensor3DA.mat.cols ( ) ; j++ ) {
 			os << Tensor3DA.mat ( i , j );
				if ( j < Tensor3DA.mat.cols ()-1 )os << " , ";
				else
					if ( ( j == Tensor3DA.mat.cols ()-1 ) && ( ( i == Tensor3DA.mat.rows ()-1 ) ) ) os << "";
					else os << ";\n";
			}
 		}
		os << "]\n%}";
		os << Tensor3DA.base-> get_name ();
		return os;
	}catch ( exception & p ) {
		outError ( "ERR - Unexpected error in out of Tensor3D" );
		return os;
	}catch ( int e ) {
		//cout << "ERR-out - Inexistent Tensor3D\n";
		return os;
	}
}


/*
Destructor
*/
Tensor3D::~Tensor3D ( void ) {}

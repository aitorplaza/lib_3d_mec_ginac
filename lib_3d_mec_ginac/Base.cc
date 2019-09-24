#include "Base.h"
#include "System.h"
#include "Globals.h"

using GiNaC::ex;
using GiNaC::lst;
using std::string;

/*
Method that initialize the Base atributes
*/

void Base::init ( string name , Base * previous_base , Matrix rotation_tupla , ex rotation_angle , System * system ){
	try{
		if  ( ( rotation_tupla.rows () != 3 ) or ( rotation_tupla.cols () != 1 ) ) throw 1;
		this-> name = name;
		this-> rotation_tupla = atomize ( rotation_tupla );
		this-> rotation_angle = rotation_angle;
 		this-> previous_base = previous_base;
		this-> system = system;
	}catch  ( int i ) {
		outError ( "ERR - Bad dimensions in rotation_matrix in Base's constructor" );
	}
}

/*
Constructor with name , previous_base , rotation_tupla and rotation_angle
The dimensions of the rotation tupla should be 3x1
*/
Base::Base  ( string name , Base * previous_base , Matrix rotation_tupla , ex rotation_angle ) {
	init  ( name , previous_base , rotation_tupla , rotation_angle , NULL );
}


/*
Constructor with name , previous_base , rotation_angle and three ex for compose a 3x1 Matrix
*/
Base::Base  ( string name , Base * previous_base , ex expression1 , ex expression2 , ex expression3 , ex rotation_angle ) {
	
    lst laux;

    laux.append(expression1);
    laux.append(expression2);
    laux.append(expression3);  
     
    Matrix Mat  ( 3 , 1 , laux);
    
    init ( name  , previous_base , Mat , rotation_angle , NULL );
    //init ( name  , previous_base , Matrix ( 3 , 1 , lst ( expression1 , expression2 , expression3 ) ) , rotation_angle , NULL );
}


/*
Constructor with name , previous_base , rotation_tupla , rotation_angle and System
The dimensions of the rotation tupla should be 3x1
*/
Base::Base  ( string name , Base * previous_base , Matrix rotation_tupla , ex rotation_angle , System * system ) {
	init ( name , previous_base , rotation_tupla , rotation_angle , system );
}


/*
Method that transforms the euler parameter to rotation matrix
*/
Matrix Base::euler_parameter_to_rotation_matrix ( Matrix phi , ex expression ) {

	Matrix aux = phi.transpose () * phi;

	//ex expresion1 = atomize_ex ( cos ( atomize_ex ( expression * aux ( 0 , 0 ) ) ) );
    ex expresion1 = atomize_ex ( cos (  expression * aux ( 0 , 0 ) ) );
	//Matrix A  ( 3 , 3 , lst ( 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 ) );
	//Matrix B  ( 3 , 3 , lst ( 0 , -phi ( 2 , 0 ) , phi ( 1 , 0 ) , phi ( 2 , 0 ) , 0 , -phi ( 0 , 0 ) , -phi ( 1 , 0 ) , phi ( 0 , 0 ) , 0 ) );
	
    lst lauxA, lauxB;
    
    lauxA.append(1);lauxA.append(0);lauxA.append(0);
    lauxA.append(0);lauxA.append(1);lauxA.append(0);   
    lauxA.append(0);lauxA.append(0);lauxA.append(1);
     
    lauxB.append(0);               lauxB.append(-phi ( 2 , 0 ) )  ;lauxB.append( phi ( 1 , 0 ));
    lauxB.append(phi ( 2 , 0 ) );  lauxB.append(0);               lauxB.append( -phi ( 0 , 0 ));   
    lauxB.append( -phi ( 1 , 0 )); lauxB.append(phi ( 0 , 0 ));   lauxB.append( 0);
        
    Matrix A  ( 3 , 3 , lauxA);
    Matrix B  ( 3 , 3 , lauxB);
    
    //ex expresion3 = atomize_ex ( sin ( atomize_ex ( expression* ( aux ( 0 , 0 ) ) ) ) );
    ex expresion3 = atomize_ex ( sin (  expression* ( aux ( 0 , 0 ) ) ) );
	Matrix C = B.transpose ();

	//ex expresion2 = atomize_ex ( 1-cos ( atomize_ex ( expression* ( aux ( 0 , 0 ) ) ) ) );
	//return	A * expresion1 + expresion2 * phi * phi.transpose () - expresion3 * C;
	return	expresion1 * (A - (phi * phi.transpose ()))+ (phi * phi.transpose ()) - expresion3 * C;
}


/*
Method that transform the euler parameter to angular velocity
*/
Matrix Base::euler_parameter_to_angular_velocity ( Matrix phi , ex expression ) {
	//return Matrix ( 3 , 1 , lst ( system-> dt ( expression ) * phi ( 0 , 0 ) , system-> dt ( expression ) * phi ( 1 , 0 ) , system-> dt ( expression ) * phi ( 2 , 0 ) ) );
    
    lst laux;
    
    laux.append( system-> dt ( expression ) * phi ( 0 , 0 ) );
    laux.append( system-> dt ( expression ) * phi ( 1 , 0 ) );
    laux.append( system-> dt ( expression ) * phi ( 2 , 0 ) );
     
    return Matrix ( 3 , 1 ,laux);
        
}


/*
Method that calculate the rotation matrix
*/
Matrix Base::rotation_matrix  () {
	return euler_parameter_to_rotation_matrix ( rotation_tupla , rotation_angle );
}


/*
Method that return the angular velocity
*/
Vector3D Base::angular_velocity  (){
    //if (gravity == DOWN){
        return Vector3D ( euler_parameter_to_angular_velocity ( rotation_tupla , rotation_angle ) , previous_base );
    //} 
    //else {
    //    return Vector3D ( euler_parameter_to_angular_velocity ( rotation_tupla , rotation_angle ) , this );
    //}
}


/*
Method that return the angular acceleration
*/
Vector3D Base::angular_acceleration  (){
    return system-> dt(angular_velocity());
}



/*
Return the name of this Base
*/
string Base::get_name () {
	return name;
}


/*
Return the rotation_tupla of this Base
*/
Matrix Base::get_Rotation_Tupla () {
	return rotation_tupla;
}


/*
Return the rotation_angle of this Base
*/
ex Base::get_Rotation_Angle () {
	return rotation_angle;
}


/*
Return the previous_base of this Base
*/
Base* Base::get_Previous_Base () {
	return previous_base;
}


/*
Put the previous_base of this Base
*/
void Base::set_Previous_Base ( Base * new_previous_base ) {
	previous_base = new_previous_base;
}


/*
Put the name of this Base
*/
void Base::set_name ( string new_name ) {
	name = new_name;
}


/*
Put the System of this Base
*/
void Base::set_System ( System * new_system ){
	system = new_system;
}


/*
Destructor method of Base's class
*/
Base::~Base ( void ){}


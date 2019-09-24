/******************************/
/* ADDED to solve csrc_double */
/******************************/
#include <ctime>
#include <time.h>
#include <sys/time.h>

#include <math.h>
#include <iostream>
#include <ginac/ginac.h>

int GetDecimalPlaces(double dbVal)
{
  static const int MAX_DP = 10;
  static const double THRES = pow(0.1, MAX_DP);
  if (dbVal == 0.0)
    return 0;
    int nDecimal = 0;
    while (dbVal - floor(dbVal) > THRES && nDecimal < MAX_DP)
    {
      dbVal *= 10.0;
      nDecimal++;
    }
    return nDecimal;
}

using namespace std;
using namespace GiNaC;

class print_myformat : public print_dflt
{
GINAC_DECLARE_PRINT_CONTEXT(print_myformat, print_dflt)
public:
print_myformat(std::ostream & os, unsigned opt = 0)
: print_dflt(os, opt) {}
};

print_myformat::print_myformat() : print_dflt(std::cout) {}

GINAC_IMPLEMENT_PRINT_CONTEXT(print_myformat, print_dflt)


void print_power_as_myformat(const power& p, const print_myformat& c, unsigned level)
{
  c.s << "pow(";
  p.op(0).print(c);
  c.s << ",";
  p.op(1).print(c);
  c.s << ")";
}
void print_numeric_as_myformat(const numeric& p,const print_myformat & c, unsigned level) 
{
     
  if (p.is_rational() && p.denom() == 1) {
    c.s << setiosflags(ios::fixed) << (p.numer()) << ".0" ;
  }
  else if ( p.is_rational() && p.denom() != 1){
    c.s << setiosflags(ios::fixed) <<(p.numer()) <<".0/" <<(p.denom()) << ".0" ;
  }
  else
    c.s << setiosflags(ios::fixed) <<  (p.numer()).to_double();
}

//~ void print_absolute_as_myformat(const numeric::abs& p,const print_myformat & c, unsigned level) 
//~ {
    //~ 
//~ }




/******************************/
/* ADDED to solve csrc_double */
/******************************/

#include "System.h"
#include "Globals.h"

#include <string>
#include <fstream>
#include <sstream>

using GiNaC::ex;
using GiNaC::matrix;
using GiNaC::symbol;
using GiNaC::lst;
using GiNaC::numeric;
using GiNaC::csrc_double;
using GiNaC::ex_to;
using GiNaC::mul;
using GiNaC::add;
using GiNaC::is_a;
using std::string;
using std::exception;
using std::vector;
using std::ofstream;
using std::endl;
using std::ostringstream;


/*
External objets from Globals
*/
int gravity;
void ( * outError )( const char * );
vector < atom > atoms;
exhashmap < ex > atom_hashmap(10^5);
//~ exhashmap < ex > atom_hashmap;

vector < symbol_numeric > exclude_atoms;

Point * Point_O;
Base * Base_xyz;
Frame * Frame_abs;
Solid * Ground;
symbol_numeric * g;

/*
Default printError function, can be overriden in system constructor.
*/
void printError(const char* arg){
        printf("%s\n", arg);
}


/*
System's general constructor
*/
void System::init ( void ( * func )( const char * ) ) {
    /*Create the "xyz" Base and push back this in the Bases vector*/
    Base_xyz = new ( Base );
    symbol x ( "x" );
    Matrix AuxMatrix ( 3 , 1 );
    Base bxyz ( "xyz" , NULL , AuxMatrix , x );
    bxyz.set_System ( this );
    * Base_xyz = bxyz;
    Bases.push_back ( Base_xyz );/*Default Base*/

    /*Create the "O" Point and push back this in the Points vector*/
    Point_O = new ( Point );
    Vector3D vaux ( Base_xyz );
    Point p ( "O" , NULL , & vaux );
    * Point_O = p;
    Points.push_back ( Point_O );/*Default Point*/

    /*Create the "abs" Frame and push back this in the Frames vector*/
    Frame_abs = new ( Frame );
    Frame fabs ( "abs" , Point_O , Base_xyz );
    * Frame_abs = fabs;
    Frames.push_back ( Frame_abs );/*Default Frame*/

    /*Create the "Ground" Solid and push back this in the Solids vector*/
    //Ground = new ( Solid );	
    //Vector3D* CM_ground = new_Vector3D("CM_ground" ,0,0,0,Base_xyz) ;
    //Tensor3D * IT_ground =  new_Tensor3D ("IT_ground", ex(1) , ex(0) , ex(0) , ex(0) , ex(1) , ex(0) , ex(0) , ex(0) , ex(1) , Base_xyz);
    //Solid solaux("Ground", Point_O,Base_xyz,0,CM_ground,IT_ground,Point_O,"ground.stl",1.0,0.0,0.0,0.0 );
    //* Ground= solaux;
    //Solids.push_back ( Ground );/*Default Solid*/

    /*Create the "grav" Parameter and push back this in the parameters vector*/
    g = new ( symbol_numeric);
    symbol_numeric  grav_aux ("g",9.8);
    * g = grav_aux;
    parameters.push_back(g);

    /*Create "t" (time)*/
    t.set_name ( "t" );
    outError = func;

}


/*
System's general constructor
*/
System::System ( void ) {
    init ( & printError );
}


/*
Constructor and error function
*/
System::System ( void ( * func )( const char * ) ) {
    init ( func );
}


/*
Create a new coordinate, velocity and acceleration in the system and the values of the coordinate, velocity and acceleration
*/
symbol_numeric * System::new_Coordinate ( symbol_numeric * coordinate , symbol_numeric * velocity , symbol_numeric * acceleration ) {
    coordinates.push_back ( coordinate );
    velocities.push_back ( velocity );
    accelerations.push_back ( acceleration );

    return coordinate;
}


/*
Create a new coordinate, velocity and acceleration in the system and the values of the coordinate, velocity and acceleration
*/
symbol_numeric * System::new_Coordinate ( string coordinate_name , string velocity_name , string acceleration_name , numeric coordinate_value , numeric velocity_value , numeric acceleration_value ) {
/*  symbol_numeric * coordinate = new ( symbol_numeric );
    symbol_numeric * velocity = new ( symbol_numeric );
    symbol_numeric * acceleration = new ( symbol_numeric );
*/
    symbol_numeric * coordinate = new  symbol_numeric ( coordinate_name , coordinate_value);
    symbol_numeric * velocity = new  symbol_numeric ( velocity_name , velocity_value);
    symbol_numeric * acceleration = new  symbol_numeric ( acceleration_name , acceleration_value);

/*  symbol_numeric coordinate_aux ( coordinate_name , coordinate_value);
    * coordinate = coordinate_aux;
    symbol_numeric velocity_aux ( velocity_name , velocity_value);
    * velocity = velocity_aux;
    symbol_numeric acceleration_aux ( acceleration_name , acceleration_value);
    * acceleration = acceleration_aux;
*/
    return new_Coordinate ( coordinate , velocity , acceleration );
}

symbol_numeric * System::new_Coordinate ( string coordinate_name , string velocity_name , string acceleration_name , string coordinate_name_tex , string velocity_name_tex , string acceleration_name_tex , numeric coordinate_value , numeric velocity_value , numeric acceleration_value ) {
/*  symbol_numeric * coordinate = new ( symbol_numeric );
    symbol_numeric * velocity = new ( symbol_numeric );
    symbol_numeric * acceleration = new ( symbol_numeric );
*/
    symbol_numeric * coordinate = new  symbol_numeric (coordinate_name , coordinate_name_tex, coordinate_value);
    symbol_numeric * velocity = new  symbol_numeric ( velocity_name , velocity_name_tex, velocity_value);
    symbol_numeric * acceleration = new  symbol_numeric ( acceleration_name , acceleration_name_tex, acceleration_value);

/*  symbol_numeric coordinate_aux ( coordinate_name , coordinate_name_tex, coordinate_value);
    * coordinate = coordinate_aux;
    symbol_numeric velocity_aux ( velocity_name , velocity_name_tex, velocity_value);
    * velocity = velocity_aux;
    symbol_numeric acceleration_aux ( acceleration_name , acceleration_name_tex, acceleration_value);
    * acceleration = acceleration_aux;
*/
    return new_Coordinate ( coordinate , velocity , acceleration );
}


/*
Create a new coordinate, velocity and acceleration in the system and the values of the coordinate, velocity and acceleration
The name of the velocity and the acceleration is auto-generated
*/
symbol_numeric * System::new_Coordinate ( string coordinate_name , numeric coordinate_value , numeric velocity_value , numeric acceleration_value ) {
    string velocity_name = "d" + coordinate_name;
    string acceleration_name = "dd" + coordinate_name;

    return new_Coordinate ( coordinate_name , velocity_name , acceleration_name , coordinate_value , velocity_value , acceleration_value );
}

symbol_numeric * System::new_Coordinate ( string coordinate_name , string coordinate_name_tex , numeric coordinate_value , numeric velocity_value , numeric acceleration_value ) {
    string velocity_name = "d" + coordinate_name;
    string acceleration_name = "dd" + coordinate_name;
    string velocity_name_tex = "\\dot{" + coordinate_name_tex + "}";
    string acceleration_name_tex = "\\ddot{" + coordinate_name_tex + "}";

    return new_Coordinate ( coordinate_name , velocity_name , acceleration_name , coordinate_name_tex , velocity_name_tex , acceleration_name_tex , coordinate_value , velocity_value , acceleration_value );
}

/*
Method for introduce new coordinates , velocities and accelerations in these correspondent vectors
Only to introduce the name of the corrdenate; The velocity and the acceleration ara atomatically generated
*/
symbol_numeric * System::new_Coordinate ( string coordinate_name ) {
    return new_Coordinate ( coordinate_name , 0.0 , 0.0 , 0.0 );
}


/*coordinates
Method for introduce new coordinates , velocities and accelerations in these correspondent vectors
Only to introduce the name of the corrdenate and the value; The velocity and the acceleration ara atomatically generated
*/
symbol_numeric * System::new_Coordinate ( string coordinate_name , numeric coordinate_value ) {
    return new_Coordinate ( coordinate_name , coordinate_value , 0.0 , 0.0 );
}


/*
Method for introduce new coordinates , velocities and accelerations in these correspondent vectors
Only to introduce the name of the corrdenate and the value; The velocity and the acceleration ara atomatically generated
*/
symbol_numeric * System::new_Coordinate ( string coordinate_name , numeric coordinate_value , numeric velocity_value ) {
    return new_Coordinate ( coordinate_name , coordinate_value , velocity_value , 0.0 );
}


/*
Create a new AUXILIAR coordinate, velocity and acceleration in the system and the values of the coordinate, velocity and acceleration
*/
symbol_numeric * System::new_AuxCoordinate ( symbol_numeric * aux_coordinate , symbol_numeric * aux_velocity , symbol_numeric * aux_acceleration ) {
    aux_coordinates.push_back ( aux_coordinate );
    aux_velocities.push_back ( aux_velocity );
    aux_accelerations.push_back ( aux_acceleration );

    return aux_coordinate;
}
/*
Create a new AUXILIAR coordinate, velocity and acceleration in the system and the values of the coordinate, velocity and acceleration
*/
symbol_numeric * System::new_AuxCoordinate ( string aux_coordinate_name , string aux_velocity_name , string aux_acceleration_name , numeric aux_coordinate_value , numeric aux_velocity_value , numeric aux_acceleration_value ) {

    symbol_numeric * aux_coordinate = new  symbol_numeric ( aux_coordinate_name , aux_coordinate_value);
    symbol_numeric * aux_velocity = new  symbol_numeric ( aux_velocity_name , aux_velocity_value);
    symbol_numeric * aux_acceleration = new  symbol_numeric ( aux_acceleration_name , aux_acceleration_value);

    return new_AuxCoordinate ( aux_coordinate , aux_velocity , aux_acceleration );
}

/*
Methods to for introduce new parameters in the System
*/
symbol_numeric * System::new_Parameter ( symbol_numeric * parameter ) {
    parameters.push_back ( parameter );

    return parameter;
}


symbol_numeric * System::new_Parameter ( string parameter_name , numeric parameter_value ) {
    symbol_numeric * parameter = new symbol_numeric ( parameter_name , parameter_value);

    return new_Parameter ( parameter );
}


symbol_numeric * System::new_Parameter ( string parameter_name , string parameter_name_tex , numeric parameter_value ) {
    symbol_numeric * parameter = new symbol_numeric ( parameter_name , parameter_name_tex, parameter_value);

    return new_Parameter ( parameter );
}


symbol_numeric * System::new_Parameter ( string parameter_name ) {
    return new_Parameter ( parameter_name , 0.0 );
}


symbol_numeric * System::new_Parameter ( string parameter_name , string parameter_name_tex) {
    return new_Parameter ( parameter_name , parameter_name_tex, 0.0 );
}


/*
Methods to introduce new joint unknowns
*/
symbol_numeric * System::new_Joint_Unknown ( symbol_numeric * joint_unknown ) {
    unknowns.push_back ( joint_unknown );

    return joint_unknown;
}


symbol_numeric * System::new_Joint_Unknown ( string joint_unknown_name , numeric joint_unknown_value ) {
    symbol_numeric * joint_unknown = new symbol_numeric ( joint_unknown_name , joint_unknown_value);

    return new_Joint_Unknown ( joint_unknown );
}


symbol_numeric * System::new_Joint_Unknown ( string joint_unknown_name , string joint_unknown_name_tex , numeric joint_unknown_value ) {
    symbol_numeric * joint_unknown = new symbol_numeric ( joint_unknown_name , joint_unknown_name_tex, joint_unknown_value);

    return new_Joint_Unknown ( joint_unknown );
}


symbol_numeric * System::new_Joint_Unknown ( string joint_unknown_name ) {
    return new_Joint_Unknown ( joint_unknown_name , 0.0 );
}


symbol_numeric * System::new_Joint_Unknown ( string joint_unknown_name , string joint_unknown_name_tex) {
    return new_Joint_Unknown ( joint_unknown_name , joint_unknown_name_tex, 0.0 );
}


/*
Methods to introduce new system inputs
*/
symbol_numeric * System::new_Input ( symbol_numeric * input ) {
    inputs.push_back ( input );

    return input;
}


symbol_numeric * System::new_Input ( string input_name , numeric input_value ) {
    symbol_numeric * input = new symbol_numeric ( input_name , input_value);

    return new_Input ( input );
}


symbol_numeric * System::new_Input ( string input_name , string input_name_tex , numeric input_value ) {
    symbol_numeric * input = new symbol_numeric ( input_name , input_name_tex, input_value);

    return new_Input ( input );
}


symbol_numeric * System::new_Input ( string input_name ) {
    return new_Input ( input_name , 0.0 );
}


symbol_numeric * System::new_Input ( string input_name , string input_name_tex) {
    return new_Input ( input_name , input_name_tex, 0.0 );
}

/*
Function that return the search symbol in the System in one vector
*/
template <class T>
T Search_Object ( vector < T> vect , string name ) {
    /*This function returns a pointer*/
    int i = 0;
    bool encontrado = false;
    
    while ( ( i < vect.size () ) and ( encontrado == false ) ){
        if ( name != vect[i]-> get_name () )
            i++;
        else encontrado = true;
    }
    if ( encontrado == true ){
        return vect[i];
    }    
    else{
        return NULL;
    }
}


/*
Method for introduce one Base in the System
*/
void System::new_Base ( Base * BaseA ) {
    try{
        if ( Search_Object ( Bases , BaseA-> get_name () ) != NULL )throw 1;
        Bases.push_back ( BaseA );
    }catch ( exception & p ) {
        outError ( "ERR -  Base not build" );
    }catch ( int e ) {
		outError ( (string("ERR - Name of Base ") + BaseA-> get_name () + string(" already used ")).c_str() );
    }
}


/*
Method for build a new Base in the System
*/
Base * System::new_Base ( string name , Base * previous_base , Matrix rotation_tupla , ex rotation_angle ) {
    try{
		
        if ( Search_Object ( Bases , name ) != NULL ) throw 1;
        if ( Search_Object ( Bases , previous_base-> get_name () ) == NULL ) throw 2;  
   
        Base * baux = new ( Base );
        Base aux ( name , get_Base ( previous_base-> get_name () ) , rotation_tupla , rotation_angle );
        aux.set_System ( this );
        * baux = aux;
        Bases.push_back ( baux );
        return baux;
    }catch ( exception & p ) {
        outError ( "ERR -  Base not build" );
    }catch ( int e ) {
		if (e==1)       {outError ( (string("ERR - Name of base ") + name + string(" already used ")).c_str() );}
		else if (e==2) {outError ( (string("ERR - The base ") + previous_base-> get_name () + string (" used to define ") + name + string("base  does not exist ")).c_str() );}
    }
}


/*
Method for build a new Base in the System
*/
Base * System::new_Base ( string name , string previous_base_name , Matrix rotation_tupla , ex rotation_angle ) {
	try{
	    if ( Search_Object ( Bases , previous_base_name ) == NULL ) throw 1;
        return new_Base ( name , get_Base ( previous_base_name ) , rotation_tupla , rotation_angle );
    } catch ( int e ) { 
    	if (e==1) {outError ( (string("ERR - The base ") + previous_base_name + string (" used to define ") + name + string(" base does not exist ")).c_str() );}
    }		  
}

 
/*
Method for build a new Base in the System
*/
Base * System::new_Base ( string name , string previous_base_name , ex expression1 , ex expression2 , ex expression3 , ex rotation_angle ) {
	try{
	    if ( Search_Object ( Bases , previous_base_name ) == NULL ) throw 1;
        lst laux;
        laux.append( expression1 ); 
        laux.append( expression2 );       
        laux.append( expression3 );        
        Matrix m_new (  3 , 1 ,laux);
        //Matrix m_new (  3 , 1 , lst ( expression1 , expression2 , expression3 ) );
        return new_Base ( name , get_Base ( previous_base_name ) , m_new , rotation_angle );
    } catch ( int e ) { 
    	if (e==1) {outError ( (string("ERR - The base ") + previous_base_name + string (" used to define ") + name + string(" base does not exist ")).c_str() );}
    }
}


/*
Method for build a new Vector3D in the System
*/
Vector3D * System::new_Vector3D ( string name , Matrix mat , Base * base ) {
    try{
        if ( Search_Object ( Vectors , name ) != NULL )throw 1;
        if ( Search_Object ( Bases , base-> get_name () ) == NULL ) throw 2;  

        Vector3D * vaux = new ( Vector3D );
        Vector3D aux ( name , mat , base , this );
        * vaux = aux;
        Vectors.push_back ( vaux );
        return vaux;
    }catch ( exception & p ) {
        outError ( "ERR -  Vector3D not build" );
    }catch ( int e ) {
		if (e==1)             {outError ( (string("ERR - Name of Vector ") + name + string(" already used ")).c_str() );}
		else if (e==2)       {outError ( (string("ERR - The base ") + base->get_name() + string (" used to define ") + name + string(" vector does not exist ")).c_str() );}
    }
}


/*
Method for build a new Vector3D in the System
*/
Vector3D * System::new_Vector3D ( string name , Matrix mat , string base_name ) {
	try{
        if ( Search_Object ( Bases , base_name ) == NULL ) throw 1;  
        return new_Vector3D ( name , mat , get_Base ( base_name ) );
    }catch ( int e ) {
		if (e==1)             {outError ( (string("ERR - The base ") + base_name + string (" used to define ") + name + string(" vector does not exist ")).c_str() );}
    }
}


/*
Method for build a new Vector3D in the System
*/
Vector3D * System::new_Vector3D ( string name , ex expression1 , ex expression2 , ex expression3 , Base * base ) {
	try{
        if ( Search_Object ( Bases , base-> get_name () ) == NULL ) throw 1;  
        lst laux;
        laux.append( expression1 ); 
        laux.append( expression2 );       
        laux.append( expression3 );        
        return new_Vector3D ( name , Matrix ( 3 , 1 , laux ) , base );
        //return new_Vector3D ( name , Matrix ( 3 , 1 , lst ( expression1 , expression2 , expression3 ) ) , base );
    }catch ( int e ) {
		if (e==1) {outError ( (string("ERR - The base ") + base-> get_name () + string (" used to define ") + name + string(" vector does not exist ")).c_str() );}
    }
}


/*
Method for build a new Vector3D in the System
*/
Vector3D * System::new_Vector3D ( string name , ex expression1 , ex expression2 , ex expression3 , string base_name ) {
	try{
        if ( Search_Object ( Bases , base_name ) == NULL ) throw 1;
        lst laux;
        laux.append( expression1 ); 
        laux.append( expression2 );       
        laux.append( expression3 );     
        return new_Vector3D ( name , Matrix ( 3 , 1 , laux ) , get_Base ( base_name ) );        
        //return new_Vector3D ( name , Matrix ( 3 , 1 , lst ( expression1 , expression2 , expression3 ) ) , get_Base ( base_name ) );
    }catch ( int e ) {
		if (e==1) {outError ( (string("ERR - The base ") + base_name + string (" used to define ") + name + string(" vector does not exist ")).c_str() );}
    }
}


/*
Method for build a new Vector3D in the System
*/
Vector3D * System::new_Vector3D ( string name , Matrix * mat , string base_name ) {
	try{
        if ( Search_Object ( Bases , base_name ) == NULL ) throw 1;  
        if ( Search_Object ( Matrixs , mat->get_name () ) == NULL ) throw 2; 
        return new_Vector3D ( name , * mat , get_Base ( base_name ) );
    }catch ( int e ) {
		if (e==1)             {outError ( (string("ERR - The base ") + base_name + string (" used to define ") + name + string(" vector does not exist ")).c_str() );}
		else if (e==2)       {outError ( (string("ERR - The matrix ") + mat->get_name () + string (" used to define ") + name + string(" vector does not exist ")).c_str() );}
    }
    
}


/*
Method for build a new Tensor3D in the System
*/
Tensor3D * System::new_Tensor3D ( string name , Matrix * mat , Base * base ) {
    try{
        if ( Search_Object ( Tensors , name ) != NULL )throw 1;
        if ( Search_Object ( Bases ,base->get_name () ) == NULL ) throw 2;  
        Tensor3D * taux = new ( Tensor3D );
        Tensor3D aux ( name , mat , base );
        aux.set_System ( this );
        * taux = aux;
        Tensors.push_back ( taux );
        return taux;
    }catch ( exception & p ) {
        outError ( "ERR -  Tensor3D not build" );
    }catch ( int e ) {
       if (e==1)             {outError ( (string("ERR - Name of Tensor3D ") + name + string(" already used.")).c_str() );}
       else if (e==2)       {outError ( (string("ERR - The base ") + base->get_name () + string (" used to define ") + name + string(" tensor does not exist ")).c_str() );}
    }
}


/*
Method for build a new Tensor3D in the System
*/
Tensor3D * System::new_Tensor3D ( string name , ex exp1 , ex exp2 , ex exp3 , ex exp4 , ex exp5 , ex exp6 , ex exp7 , ex exp8 , ex exp9 , Base * base ) {
	try{
        if ( Search_Object ( Bases ,base->get_name () ) == NULL ) throw 1;
        lst laux;
        laux.append( exp1 ); laux.append( exp2 );laux.append( exp3 );
        laux.append( exp4 ); laux.append( exp5 );laux.append( exp6 );
        laux.append( exp7 ); laux.append( exp9 );laux.append( exp9 );   
        Matrix m ( 3 , 3 , laux);
        //Matrix m ( 3 , 3 , lst ( exp1 , exp2 , exp3 , exp4 , exp5 , exp6 , exp7 , exp8 , exp9 ) );
        return new_Tensor3D ( name , & m , base );
    }catch ( int e ) {
       if (e==1) {outError ( (string("ERR - The base ") + base->get_name () + string (" used to define ") + name + string(" tensor does not exist ")).c_str() );}           
    }        
}


/*
Method for build a new Tensor3D in the System
*/
Tensor3D * System::new_Tensor3D ( string name , ex exp1 , ex exp2 , ex exp3 , ex exp4 , ex exp5 , ex exp6 , ex exp7 , ex exp8 , ex exp9 , string s_Base ) {
   try{
       if ( Search_Object ( Bases , s_Base ) == NULL )throw 1;
        lst laux;
        laux.append( exp1 ); laux.append( exp2 );laux.append( exp3 );
        laux.append( exp4 ); laux.append( exp5 );laux.append( exp6 );
        laux.append( exp7 ); laux.append( exp9 );laux.append( exp9 );   
        Matrix m ( 3 , 3 , laux);
        //Matrix m ( 3 , 3 , lst ( exp1 , exp2 , exp3 , exp4 , exp5 , exp6 , exp7 , exp8 , exp9 ) );
       return new_Tensor3D ( name , & m , get_Base ( s_Base ) );
    }catch ( exception & p ) {
        outError ( "ERR -  Tensor3D not build" );
    }catch ( int e ) {
        if (e==1) {outError ( (string("ERR - The base ") + s_Base + string (" used to define ") + name + string(" tensor does not exist ")).c_str() );}
	}
}


/*
Method for build a new Point in the System
*/
Point * System::new_Point ( string name , Point * p , Vector3D * v ) {
    try{
        if ( Search_Object ( Points , name ) != NULL )throw 1;
        if ( Search_Object ( Points , p->get_name() ) == NULL )throw 2;
        //~ if ( Search_Object ( Vectors ,v->get_name() ) == NULL )throw 3; not all the vector are in "Vectors"
        Point * paux = new ( Point );
        Point aux ( name , p , v );
        * paux = aux;
        Points.push_back ( paux );
        return paux;
    }catch ( exception & p ) {
        outError ( "ERR -  Point not build" );
    }catch ( int e ) {
        if (e==1) {outError ( (string("ERR - Name of Point ") + name + string(" already used ")).c_str() );}
        else if (e==2) {outError ( (string("ERR - The point ") + p->get_name() + string (" used to define ") + name + string(" point does not exist ")).c_str() );}
        //~ else if (e==3) {outError ( (string("ERR - The vector ") + v->get_name() + string (" used to define ") + name + string(" point does not exist ")).c_str() );}       
    }
}

/*
Method for build a new Point in the System
*/
Point * System::new_Point ( string name , string p , Vector3D * v ) {   
    try{
        if ( Search_Object ( Points , p ) == NULL )throw 1;
        return new_Point ( name , get_Point ( p ) , v );
    }catch ( int e ) {
        if (e==1) {outError ( (string("ERR - The point ") + p + string (" used to define ") + name + string(" point does not exist ")).c_str() );}
	}
}


/*
Method for build a new Point in the System
*/
Point * System::new_Point ( string name , string p , ex exp1 , ex exp2 , ex exp3 , string s_base  ) {   
    try{
        if ( Search_Object ( Points , p ) == NULL )throw 1;
        Vector3D * vaux = new ( Vector3D );
        Vector3D aux ( ( ex ) exp1 , ( ex ) exp2 , ( ex ) exp3 , get_Base ( s_base ) , this );
        * vaux = aux;
        return new_Point ( name , get_Point ( p ) , vaux );
    }catch ( int e ) {
        if (e==1) {outError ( (string("ERR - The point ") + p + string (" used to define ") + name + string(" point does not exist ")).c_str() );}
	}
}



/*
Method for build a new Frame in the System
*/
Frame * System::new_Frame ( string name , Point * p , Base * base) {
    try{
        if ( Search_Object ( Frames , name ) != NULL )throw 1;
        if ( Search_Object ( Points , p->get_name() ) == NULL )throw 2;
        if ( Search_Object ( Bases ,  base->get_name() ) == NULL )throw 3;
        Frame * faux = new ( Frame );
        Frame aux ( name , p , base);
        * faux = aux;
        Frames.push_back ( faux );
        return faux;
    }catch ( exception & p ) {
        outError ( "ERR -  Frame not build" );
    }catch ( int e ) {
		if (e==1) {outError ( (string("ERR - Name of Frame ") + name + string(" already used ")).c_str() );}
        else if (e==2) {outError ( (string("ERR - The point ") + p->get_name() + string (" used to define ") + name + string(" frame does not exist ")).c_str() );}       
        else if (e==3) {outError ( (string("ERR - The bse ") + base->get_name() + string (" used to define ") + name + string(" frame does not exist ")).c_str() );}       
    }
}
/*
Method for build a new Frame in the System
*/
Frame * System::new_Frame ( string name , string s_Point , string s_Base) {
    try{
        if ( Search_Object ( Points , s_Point ) == NULL )throw 1;
        if ( Search_Object ( Bases , s_Base ) == NULL )throw 2;
        return new_Frame ( name , get_Point ( s_Point ) , get_Base ( s_Base ) ); 
    }catch ( int e ) {
	    if (e==1) {outError ( (string("ERR - The point ") + s_Point + string(" used to define ") + name + string(" frame is not defined.")).c_str() );}
        else if (e==2) {outError ( (string("ERR - The base ") + s_Base + string(" used to define ") + name + string(" frame is not defined.")).c_str() );}
    }
}
/*
Method for build a new VectorE  in the System with objects
*/
VectorE  * System::new_VectorE ( string name ) {
    try{
        if ( Search_Object ( VectorEs  , name ) != NULL )throw 1;
        VectorE * veaux = new ( VectorE );
        VectorE aux ( name  );
        * veaux = aux;
        VectorEs.push_back ( veaux );
        return veaux;
    }catch ( exception & p ) {
        outError ( "ERR -  VectorE  not build" );
    }catch ( int e ) {
        if (e==1) {outError ( "ERR -  Name of VectorE  already used" );}
    }
}

/*
Method for build a new Solid in the System with objects
*/
Solid * System::new_Solid ( string name , Point * p , Base * base, symbol_numeric * new_mass , Vector3D * new_CM, Tensor3D * new_IT) {
    try{
        if ( Search_Object ( Solids , name ) != NULL )throw 1;
        //if ( new_IT->get_Base ( ) != base ) throw 2;
        if ( new_IT->get_Base ( ) != base ) {cout <<"   Warning: " + new_IT->get_name() + " Intertia Tensor is not fixed to " +name + " solid" <<endl;};
        if ( new_CM->get_Base ( ) != base ) {cout <<"   Warning: " + new_CM->get_name() + " Intertia Center Vector is not fixed to " +name + " solid" <<endl;};
        //if ( new_CM->get_Base ( ) != base )  throw 3;
        if ( Search_Object ( Points , p->get_name() ) == NULL )throw 4;
        if ( Search_Object ( Bases , base->get_name() ) == NULL )throw 5;
        if ( Search_Object ( parameters , new_mass->get_name() ) == NULL )throw 6;
        if ( Search_Object ( Vectors , new_CM->get_name() ) == NULL )throw 7;
        if ( Search_Object ( Tensors , new_IT->get_name() ) == NULL )throw 8;
        
        string s1="G"+name;
        Point* new_G = new_Point(s1 ,p,new_CM);

        Solid * saux = new ( Solid );
        Solid aux ( name , p , base, new_mass, new_CM, new_IT, new_G);
        * saux = aux;
        Solids.push_back ( saux );
        return saux;
    }catch ( exception & p ) {
        outError ( "ERR -  Solid not build" );
    }catch ( int e ) {
        if (e==1) {outError ( "ERR -  Name of Solid already used" );}
        else if (e==2){outError ( "ERR -  Intertia Tensor is not fixed to the solid" );}
        else if (e==3){outError ( "ERR -  Intertia Center Vector is not fixed to the solid " );}
        else if (e==4) {outError ( (string("ERR - The point ") + p->get_name() + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        else if (e==5) {outError ( (string("ERR - The base ") + base->get_name() + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        else if (e==6) {outError ( (string("ERR - The Parameter ") + new_mass->get_name() + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        else if (e==7) {outError ( (string("ERR - The vector ") + new_CM->get_name() + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        else if (e==8) {outError ( (string("ERR - The tensor ") + new_IT->get_name() + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
    }
 }
/*
Method for build a new Solid in the System with strings
*/
Solid * System::new_Solid ( string name , string s_Point , string s_Base, string s_mass , string s_CM, string s_IT){	
    try{
        if ( Search_Object ( Points , s_Point ) == NULL )throw 1;
        if ( Search_Object ( Bases , s_Base ) == NULL )throw 2;
        if ( Search_Object ( parameters , s_mass ) == NULL )throw 3;
        if ( Search_Object ( Vectors , s_CM ) == NULL )throw 4;
        if ( Search_Object ( Tensors , s_IT ) == NULL )throw 5;
        return new_Solid ( name , get_Point ( s_Point ) ,get_Base ( s_Base ) ,get_Parameter ( s_mass) , get_Vector3D (s_CM), get_Tensor3D (s_IT));
    }catch ( int e ) {
	if (e==1) {outError ( (string("ERR - The point ") + s_Point + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        else if (e==2) {outError ( (string("ERR - The base ") + s_Base + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        else if (e==3) {outError ( (string("ERR - The parameter ") + s_mass + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        else if (e==4) {outError ( (string("ERR - The vector ") + s_CM + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        else if (e==5) {outError ( (string("ERR - The tensor ") + s_IT + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
    }
}

/*
Method for build a new Solid in the System with strings
*/
Solid * System::new_Solid ( string name , string s_Point , string s_Base, symbol_numeric * new_mass, string s_CM, string s_IT){	
    try{
        if ( Search_Object ( Points , s_Point ) == NULL )throw 1;
        if ( Search_Object ( Bases , s_Base ) == NULL )throw 2;
        //if ( Search_Object ( parameters , s_mass ) == NULL )throw 3;
        if ( Search_Object ( Vectors , s_CM ) == NULL )throw 4;
        if ( Search_Object ( Tensors , s_IT ) == NULL )throw 5;
        return new_Solid ( name , get_Point ( s_Point ) ,get_Base ( s_Base ) ,new_mass , get_Vector3D (s_CM), get_Tensor3D (s_IT));
    }catch ( int e ) {
	if (e==1) {outError ( (string("ERR - The point ") + s_Point + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        else if (e==2) {outError ( (string("ERR - The base ") + s_Base + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        //else if (e==3) {outError ( (string("ERR - The parameter ") + s_mass + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        else if (e==4) {outError ( (string("ERR - The vector ") + s_CM + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
        else if (e==5) {outError ( (string("ERR - The tensor ") + s_IT + string(" used to define ") + name + string(" solid is not defined.")).c_str() );}
    }
}



/*
Method for build a new Wrench in the System
*/
Wrench3D * System::new_Wrench3D ( string name, Vector3D F, Vector3D M , Point * P, Solid * Sol , string type) {
    try{
      if ( Search_Object ( Wrenches , name ) != NULL )throw 1;
      //if ( (type != string("inertia")) && (type != string("constitutive")) && (type != string("joint")) && (type != string("external"))) throw 2;
      Wrench3D * taux = new ( Wrench3D );
      Wrench3D aux ( name , F , M, P, Sol, type);
      * taux = aux;
      Wrenches.push_back ( taux );
      return taux;
    }catch ( exception & p ) {
      outError ( "ERR -  Wrench3D not build" );
    }catch ( int e ) {
       if (e==1) {outError ( (string("ERR - Name of Wrench3D ") + name + string(" already used ")).c_str() );}
       //else if (e==2){outError ( "ERR -  Wrench type not defined or incorrectly defined. It must be: inertia, constitutive, joint or external." );}
    }
}
/*
Method for build a new wrench in the System
*/
Wrench3D * System::new_Wrench3D ( string name , string s_F , string s_M, string s_P, string s_Sol, string type) {
    return new_Wrench3D ( name , *get_Vector3D(s_F) , *get_Vector3D(s_M) , get_Point ( s_P ) , get_Solid ( s_Sol ), type );
}

/*
Method for build a new wrench in the System
*/
Wrench3D * System::new_Wrench3D(string s_name, ex f1, ex f2, ex f3, string s_baseF, ex m1, ex m2, ex m3, string s_baseM, string s_P, string s_Sol, string type ){
    Vector3D * Fvaux = new ( Vector3D );
    Vector3D * Mvaux = new ( Vector3D );
    Vector3D Faux ( ( ex ) f1 , ( ex ) f2 , ( ex ) f3 , get_Base ( s_baseF ) , this );
    * Fvaux = Faux;
    Vector3D Maux ( ( ex ) m1 , ( ex ) m2 , ( ex ) m3 , get_Base ( s_baseM ) , this );
    * Mvaux = Maux;
    return new_Wrench3D ( s_name , Faux, Maux , get_Point ( s_P ) , get_Solid ( s_Sol ), type );    
}




/*
Method for build a new wrench in the System with 2 solids
*/
Wrench3D * System::new_Wrench3D ( string name, Vector3D F, Vector3D M , Point * P, Solid * Sol1 , Solid * Sol2 , string type) {

    string name_action=name+"_action";
    string name_reaction=name+"_reaction";

    new_Wrench3D ( name_action, F, M , P, Sol2 , type);
    new_Wrench3D ( name_reaction, -F, -M , P, Sol1 , type);
}

/*
Method for build a new wrench in the System with 2 solids
*/
Wrench3D * System::new_Wrench3D ( string name , string s_F , string s_M, string s_P, string s_Sol1, string s_Sol2, string type) {
    return new_Wrench3D ( name , *get_Vector3D(s_F) , *get_Vector3D(s_M) , get_Point ( s_P ) , get_Solid ( s_Sol1 ), get_Solid ( s_Sol2 ),type );
}

/*
Method for build a new wrench in the System with 2 solids
*/
Wrench3D * System::new_Wrench3D(string s_name, ex f1, ex f2, ex f3, string s_baseF, ex m1, ex m2, ex m3, string s_baseM, string s_P, string s_Sol1, string s_Sol2, string type ){
    Vector3D * Fvaux = new ( Vector3D );
    Vector3D * Mvaux = new ( Vector3D );
    Vector3D Faux ( ( ex ) f1 , ( ex ) f2 , ( ex ) f3 , get_Base ( s_baseF ) , this );
    * Fvaux = Faux;
    Vector3D Maux ( ( ex ) m1 , ( ex ) m2 , ( ex ) m3 , get_Base ( s_baseM ) , this );
    * Mvaux = Maux;
    
    string name_action = s_name+"_action";
    string name_reaction = s_name+"_reaction";
    
    new_Wrench3D ( name_action,    Faux,  Maux , get_Point ( s_P ), get_Solid ( s_Sol2 ) , type);
    new_Wrench3D ( name_reaction, -Faux, -Maux , get_Point ( s_P ), get_Solid ( s_Sol1 ) , type);
       
}

/*
Method for build a new Draw in the System with Solid object
*/
Drawing3D * System::new_Drawing3D (  string s_name , Solid * Sol, string file_name, numeric r, numeric g,numeric b,numeric alpha  ) {
    try{
      string name = s_name;
      string type = "Solid";
      Point * P = Sol-> get_Point();
      Base * B = Sol-> get_Base();

      if ( Search_Object ( Drawings , s_name ) != NULL )throw 1;
      if ( Search_Object ( Solids , Sol->get_name() ) == NULL )throw 2;
      
      Drawing3D * daux = new ( Drawing3D );
      Drawing3D aux ( name, type, P, B);

      aux.set_file(file_name);
      lst new_color;
      new_color.append(r); new_color.append(g); new_color.append(b); new_color.append(alpha);
      aux.set_color(new_color);
      //aux.set_color(lst(r,g,b,alpha));
      * daux = aux;
      Drawings.push_back ( daux );
      return daux;
    }catch ( exception & p ) {
      outError ( "ERR -  Drawing3D not build" );
    }catch ( int e ) {
	   if (e==1) {outError ( (string("ERR - The Drawing3D ") + s_name + string(" is already in the Drawing3D structure ")).c_str() );    }
       else if (e==2) {outError ( (string("ERR - The solid ") + Sol->get_name() + string(" used to define ") + s_name + string(" drawings is not defined.")).c_str() );}
    }

}
/*
Method for build a new Draw in the System with Solid object
*/
Drawing3D * System::new_Drawing3D (  string s_name , string s_Sol, string file_name, numeric r, numeric g,numeric b,numeric alpha  ) {
    return new_Drawing3D ( s_name, get_Solid(s_Sol), file_name, r, g, b, alpha  ); 
}



/*
Method for build a new Draw in the System with data
*/
Drawing3D * System::new_Drawing3D (string s_name, string s_point , string s_base ,string file_name, numeric r, numeric g,numeric b,numeric alpha) {
    try{
      string type = "Solid";
      string name = s_name;

        if ( Search_Object ( Drawings , s_name ) != NULL )throw 1;
        if ( Search_Object ( Points , s_point ) == NULL )throw 2;
        if ( Search_Object ( Bases , s_base ) == NULL )throw 3;
    

        Drawing3D * daux = new ( Drawing3D );
        Drawing3D aux ( name, type, get_Point ( s_point ) , get_Base( s_base ));

        aux.set_file(file_name);
        lst new_color;
        new_color.append(r); new_color.append(g); new_color.append(b); new_color.append(alpha);
        aux.set_color(new_color);
        //aux.set_color( lst (r,g,b,alpha) );
        
        * daux = aux;
        Drawings.push_back ( daux );
        return daux;
    }catch ( exception & p ) {
        outError ( "ERR -  Drawing3D not build" );
    }catch ( int e ) {
        if (e==1) {outError ( (string("ERR - The Drawing3D") + s_name + string(" is already in the Drawing3D structure ")).c_str() );    }
    	else if (e==2) {outError ( (string("ERR - The point ") + s_point + string(" used to define ") + s_name + string(" Drawing3D is not defined.")).c_str() );}
        else if (e==3) {outError ( (string("ERR - The base ") + s_base + string(" used to define ") + s_name + string(" Drawing3D is not defined.")).c_str() );}
    }
}


/*
Method for build a new Draw in the System with Solid object without color
*/
Drawing3D * System::new_Drawing3D (  string s_name , Solid * Sol, string file_name) {
    return new_Drawing3D ( s_name, Sol, file_name, 9, 9, 9, 9 ); 
}

/*
Method for build a new Draw in the System with Solid object without color
*/
Drawing3D * System::new_Drawing3D (  string s_name , string s_Sol, string file_name ) {
    return new_Drawing3D ( s_name, get_Solid(s_Sol), file_name, 9, 9, 9, 9 ); 
}

/*
Method for build a new Draw in the System with data without color
*/
Drawing3D * System::new_Drawing3D (string s_name, string s_point , string s_base ,string file_name) {
    return new_Drawing3D (s_name, s_point , s_base , file_name, 9, 9, 9, 9);
}

/*
Method for build a new Draw in the System with Frame object
*/
Drawing3D * System::new_Drawing3D ( string s_name ,  Frame * Fra, numeric scale ) {
    try{
      string name = s_name + "_draw";
      string type = "Frame";
      Point * P = Fra -> get_Point();
      Base * B = Fra -> get_Base();

      if ( Search_Object ( Drawings , name ) != NULL )throw 1;
      if ( Search_Object ( Frames , Fra->get_name() ) == NULL )throw 2;

      Drawing3D * daux = new ( Drawing3D );
      Drawing3D aux ( name, type, P, B);

      aux.set_scale(scale);

      * daux = aux;
      Drawings.push_back ( daux );
      return daux;
    }catch ( exception & p ) {
      outError ( "ERR -  Drawing3D not build" );
    }catch ( int e ) {
       if (e==1) {outError ( (string("ERR - The Drawing3D ") + s_name + string(" is already in the Drawing3D structure ")).c_str() );    }
       else if (e==2) {outError ( (string("ERR - The frame ") + Fra->get_name() + string(" used to define ") + s_name + string(" drawings is not defined.")).c_str() );}

    }
}

/*
Method for build a new Draw in the System with Frame object
*/
Drawing3D * System::new_Drawing3D ( string s_name ,  string s_Fra, numeric scale ) {
    return new_Drawing3D ( s_name ,get_Frame( s_Fra), scale );
}


/*
Method for build a new Draw in the System with Point object
*/
Drawing3D * System::new_Drawing3D ( string s_name ,  Point * Pnt, numeric scale, numeric r, numeric g,numeric b,numeric alpha ) {
    try{
      string name = s_name;
      string type = "Point";

      if ( Search_Object ( Drawings , name ) != NULL )throw 1;
      if ( Search_Object ( Points , Pnt->get_name() ) == NULL )throw 2;

      Drawing3D * daux = new ( Drawing3D );
      Drawing3D aux ( name, type, Pnt, Base_xyz);
      lst new_color;
      new_color.append(r); new_color.append(g); new_color.append(b); new_color.append(alpha);
      aux.set_color(new_color);
      //aux.set_color( lst (r,g,b,alpha));
      aux.set_scale(scale);

      * daux = aux;
      Drawings.push_back ( daux );
      return daux;
    }catch ( exception & p ) {
      outError ( "ERR -  Drawing3D not build" );
    }catch ( int e ) {
	if (e==1) {outError ( (string("ERR - The Drawing3D ") + s_name + string(" is already in the Drawing3D structure ")).c_str() );    }
	else if (e==2) {outError ( (string("ERR - The point ") + Pnt->get_name() + string(" used to define ") + s_name + string(" drawings is not defined.")).c_str() );}
    }
}

Drawing3D * System::new_Drawing3D (  string s_name , Point * Pnt, numeric scale) {
    return new_Drawing3D (s_name , Pnt, scale, 0.2, 1.0 , 1.0, 1.0 );
}

/*
Method for build a new Draw in the System with Vector object
*/       
Drawing3D * System::new_Drawing3D ( string s_name , Vector3D * Vec, Point * Pnt, numeric r, numeric g,numeric b,numeric alpha) {
    try{

      string name = s_name;
      string type = "Vector";

      if ( Search_Object ( Drawings , name ) != NULL )throw 1;
      if ( Search_Object ( Points , Pnt->get_name() ) == NULL )throw 1;      
      Base * B = Vec-> get_Base();


      Drawing3D * daux = new ( Drawing3D );
      Drawing3D aux ( name, type, Pnt, B);

      ex mod =  Vec -> get_module();
      aux.set_vector(*Vec);
      aux.set_scale(1.0);

      lst new_color;
      new_color.append(r); new_color.append(g); new_color.append(b); new_color.append(alpha);
      aux.set_color(new_color);
      //aux.set_color( lst (r,g,b,alpha));

      * daux = aux;
      Drawings.push_back ( daux );
      return daux;
    }catch ( exception & p ) {
      outError ( "ERR -  Drawing3D not build" );
    }catch ( int e ) {
       if (e==1) {outError ( (string("ERR - The Vector ") + s_name + string(" is already in the Drawing3D structure ")).c_str() );    }
       else if (e==2) {outError ( (string("ERR - The point ") + Pnt->get_name() + string(" used to define ") + s_name + string(" drawings is not defined.")).c_str() );}

    }

}


Drawing3D * System::new_Drawing3D (string s_name ,  Vector3D * Vec, Point * Pnt) {
	try{
        if ( Search_Object ( Points , Pnt->get_name() ) == NULL )throw 1;   
        return new_Drawing3D (s_name, Vec, Pnt , 1.0, 0.0, 0.0, 1.0  ); 
    }catch ( int e ) {
       if (e==1) {outError ( (string("ERR - The point ") + Pnt->get_name() + string(" used to define ") + s_name + string(" drawings is not defined.")).c_str() );}
    }
}
/*
Method for build a new Matrix in the System
*/
Matrix * System::new_Matrix ( string name , Matrix m_new ) {
    try{
        if ( Search_Object ( Matrixs , name ) != NULL ) throw 1;
        Matrix * maux = new ( Matrix );
        m_new.set_name ( name );
        * maux = m_new;
        Matrixs.push_back ( maux );
        return maux;
    }catch ( exception & p ) {
        outError ( "ERR -  Matrix not build" );
    }catch ( int e ) {
		outError ( (string("ERR - Name of Matrix ") + name + string(" already used ")).c_str() );
    }
}


/*
Method for build a new Matrix in the System
*/
Matrix * System::new_Matrix ( Matrix * m ) {
    Matrixs.push_back ( m );
}


/*
Method for assign the symbol corresponding at time
*/
void System::set_Time_Symbol ( symbol_numeric time ) {
    this-> t = time;
}


/*
Method for return the symbol time
*/
symbol_numeric System::get_Time_Symbol ( void ) {
    return t;
}


/*
Return the coordinates's vector
*/
vector < symbol_numeric * > System::get_Coordinates ( void ) {
    return coordinates;
}


/*
Return the velocities's vector
*/
vector < symbol_numeric * > System::get_Velocities ( void ) {
    return velocities;
}


/*
Return the accelerations's vector
*/
vector < symbol_numeric * > System::get_Accelerations ( void ) {
    return accelerations;
}

/*
Return the auxiliar coordinates's vector
*/
vector < symbol_numeric * > System::get_AuxCoordinates ( void ) {
    return aux_coordinates;
}


/*
Return the auxiliar velocities's vector
*/
vector < symbol_numeric * > System::get_AuxVelocities ( void ) {
    return aux_velocities;
}


/*
Return the auxiliar accelerations's vector
*/
vector < symbol_numeric * > System::get_AuxAccelerations ( void ) {
    return aux_accelerations;
}

/*
Return the parameters's vector
*/
vector < symbol_numeric * > System::get_Parameters ( void ) {
    return parameters;
}


/*
Return the unknowns's vector
*/
vector < symbol_numeric * > System::get_Joint_Unknowns ( void ) {
    return unknowns;
}

/*
Return the inputs's vector
*/
vector < symbol_numeric * > System::get_Inputs ( void ) {
    return inputs;
}


/*
Return the Bases's vector
*/
vector < Base * > System::get_Bases ( void ) {
    return Bases;
}


/*
Return the Matrix's vector
*/
vector < Matrix * > System::get_Matrixs ( void ) {
    return Matrixs;
}


/*
Return the Frame's vector
*/
vector < Frame * > System::get_Frames ( void ) {
    return Frames;
}

/*
Return the Solid's vector
*/
vector < Solid * > System::get_Solids ( void ) {
    return Solids;
}

/*
Return the Wrench3D's vector
*/
vector < Wrench3D * > System::get_Wrenches ( void ) {
    return Wrenches;
}

/*
Return the Drawings3D's vector
*/
vector < Drawing3D * > System::get_Drawings ( void ) {
    return Drawings;
}

/*
Return the Vector3D's vector
*/
vector < Vector3D * > System::get_Vectors ( void ) {
    return Vectors;
}


/*
Return the Tensor3D's vector
*/
vector < Tensor3D * > System::get_Tensors ( void ) {
    return Tensors;
}


/*
Return the Point's vector
*/
vector < Point * > System::get_Points ( void ) {
    return Points;
}


/*
Return the pointer of one coordinate by name
*/
symbol_numeric * System::get_Coordinate ( string name ) {
    try {
        symbol_numeric * q = Search_Object ( coordinates , name );
        if ( q == NULL) throw 1;
        else return q;
    } catch (int e) {
        outError ( (string("ERR - The coordinate ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}


/*
Return the pointer of one velocity by name
*/
symbol_numeric * System::get_Velocity ( string name ) {
    try {
        symbol_numeric * dq = Search_Object ( velocities , name );
        if ( dq == NULL) throw 1;
        else return dq;
    } catch (int e) {
		outError ( (string("ERR - The velocity ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}


/*
Return the pointer of one acceleration by name
*/
symbol_numeric * System::get_Acceleration ( string name ) {
    try {
        symbol_numeric * ddq = Search_Object ( accelerations , name );
        if ( ddq == NULL) throw 1;
        else return ddq;
    } catch (int e) {
		outError ( (string("ERR - The acceleration ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}

/*
Return the pointer of one auxiliar coordinate by name
*/
symbol_numeric * System::get_AuxCoordinate ( string name ) {
    try {
        symbol_numeric * qaux = Search_Object ( aux_coordinates , name );
        if ( qaux == NULL) throw 1;
        else return qaux;
    } catch (int e) {
        outError ( (string("ERR - The auxiliar coordinate ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}


/*
Return the pointer of one velocity by name
*/
symbol_numeric * System::get_AuxVelocity ( string name ) {
    try {
        symbol_numeric * dqaux = Search_Object ( aux_velocities , name );
        if ( dqaux == NULL) throw 1;
        else return dqaux;
    } catch (int e) {
		outError ( (string("ERR - The auxiliar velocity ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}


/*
Return the pointer of one acceleration by name
*/
symbol_numeric * System::get_AuxAcceleration ( string name ) {
    try {
        symbol_numeric * ddqaux= Search_Object ( aux_accelerations , name );
        if ( ddqaux == NULL) throw 1;
        else return ddqaux;
    } catch (int e) {
		outError ( (string("ERR - The auxiliar acceleration ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}
/*
Return the pointer of one parameter by name
*/
symbol_numeric * System::get_Parameter ( string name ) {
    try {
        symbol_numeric * p = Search_Object ( parameters , name );
        if ( p == NULL) throw 1;
        else return p;
    } catch (int e) {
        outError ( (string("ERR - The Parameter ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}


/*
Return the pointer of one Unknown by name
*/
symbol_numeric * System::get_Unknown ( string name ) {
    try {
        symbol_numeric * u = Search_Object ( unknowns , name );
        if ( u == NULL) throw 1;
        else return u;
    } catch (int e) {
        outError ( (string("ERR - The Unknowkn ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}

/*
Return the pointer of one input by name
*/
symbol_numeric * System::get_Input ( string name ) {
    try {
        symbol_numeric * i = Search_Object ( inputs , name );
        if ( i == NULL) throw 1;
        else return i;
    } catch (int e) {
        outError ( (string("ERR - The Input ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}

/*
Return the pointer of one Base by name
*/
Base * System::get_Base ( string name ) {
    try {
        Base * b = Search_Object ( Bases , name );
        if ( b == NULL) throw 1;
        else return b;
    } catch (int e) {
		string("ERR - The base ") + name + string("does not exist");
        //outError ( "ERR - The Base does not exist" );
        return NULL;
    }
}


/*
Return the pointer of one Frame by name
*/
Frame * System::get_Frame ( string name ) {
    try {
        Frame * f = Search_Object ( Frames , name );
        if ( f == NULL) throw 1;
        else return f;
    } catch (int e) {
        outError ( (string("ERR - The Frame ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}
/*
Return the pointer of one Solid by name
*/
Solid * System::get_Solid ( string name ) {
    try {
        Solid * s = Search_Object ( Solids , name );
        if ( s == NULL) throw 1;
        else return s;
    } catch (int e) {
        outError ( (string("ERR - The Solid ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}

/*
Return the pointer of one Wrench3D by name
*/
Wrench3D * System::get_Wrench3D ( string name ) {
    try {
        Wrench3D * t = Search_Object ( Wrenches , name );
        if ( t == NULL) throw 1;
        else return t;
    } catch (int e) {
        outError ( (string("ERR - The Wrench3D ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}

/*
Return the pointer of one Drawing3D by name
*/
Drawing3D * System::get_Drawing3D ( string name ) {
    try {
        Drawing3D * d = Search_Object ( Drawings , name );
        if ( d == NULL) throw 1;
        else return d;
    } catch (int e) {
        outError ( (string("ERR - The Drawings3D ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}


/*
Return the pointer of one Vector3D by name
*/;
Vector3D * System::get_Vector3D ( string name ) {
    try {
        Vector3D * v = Search_Object ( Vectors , name );
        if ( v == NULL) throw 1;
        else return v;
    } catch (int e) {
        outError ( (string("ERR - The Vector3D ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}
/*
Return the pointer of one Tensor by name
*/;
Tensor3D * System::get_Tensor3D ( string name ) {
    try {
        Tensor3D * t = Search_Object ( Tensors , name );
        if ( t == NULL) throw 1;
        else return t;
    } catch (int e) {
        outError ( (string("ERR - The Tensor3D ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}

/*
Return the pointer of one Matrix by name
*/

Matrix * System::get_Matrix ( string name ) {
    try {
        Matrix * m = Search_Object ( Matrixs , name );
        if ( m == NULL) throw 1;
        else return m;
    } catch (int e) {
        outError ( (string("ERR - The Matrix ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}


/*
Return the pointer of one Point by name
*/
Point * System::get_Point ( string name ) {
    try {
        Point * p = Search_Object ( Points , name );
        if ( p == NULL) throw 1;
        else return p;
    } catch (int e) {
        outError ( (string("ERR - The Point ") + name + string(" does not exist")).c_str() );
        return NULL;
    }
}

/*
Method that it said us if one Base is more near that other of the Base xyz
*/
int System::Bases_Position ( Base * BaseA , Base * BaseB ) {
    Base * bauxA = BaseA;
    int find = 0;
    while ( ( BaseA-> get_name () != "xyz" ) && ( find == 0 ) ) {
        BaseA = get_Base ( BaseA-> get_Previous_Base ()-> get_name () );
        if ( BaseA == BaseB )find = 1;
    }
    BaseA = bauxA;
    return find;/*If return 0 , BaseA is more near of Base xyz than BaseB, else return 1*/
}


/*
Return the pointer of one Base result of reduce two Bases ( these common base in the tree )
*/
Base * System::Reduced_Base ( Base * BaseA , Base * BaseB ) {
    Base * bauxA = BaseA;
    Base * bauxB = BaseB;

    vector < Base * > ramaA;
    vector < Base * > ramaB;

    ramaA.push_back ( BaseA );
    ramaB.push_back ( BaseB );

    while ( BaseA-> get_name() != "xyz" ) {
        ramaA.push_back ( get_Base ( BaseA-> get_Previous_Base ()->get_name () ) );
        BaseA = get_Base ( BaseA-> get_Previous_Base ()-> get_name () );
    }
    while ( BaseB-> get_name () != "xyz" ){
        ramaB.push_back ( BaseB-> get_Previous_Base () );
        BaseB = get_Base ( BaseB-> get_Previous_Base ()-> get_name() );
    }

    int i;
    vector < Base * > ramaAaux;
    vector < Base * > ramaBaux;
    
    for ( i = ramaA.size () - 1 ; i >= 0 ; i-- ){
        ramaAaux.push_back ( ramaA.back () );
        ramaA.pop_back ();
    }

    for ( i = ramaB.size () - 1 ; i >= 0 ; i-- ){
        ramaBaux.push_back ( ramaB.back () );
        ramaB.pop_back ();
    }


    /*Now run this vectors in pairs and stop when these pairs are'n equals*/

    Base * b;
   
    if ( gravity == DOWN ){
    int encontrado = 0;
    i = 0;
    while (( i < ramaAaux.size () ) and ( i < ramaBaux.size () ) and ( encontrado == 0 ) ){
        if ( ramaAaux[i]-> get_name () == ramaBaux[i]-> get_name () )
            i++;
        else encontrado=1;
    }
    
    b = ramaAaux[i-1];
    }
    else if ( gravity == UP ){
        //~ if (ramaAaux.size ()>=ramaBaux.size () ){ 
            //~ i = ramaAaux.size ();
            //~ b = ramaAaux[i-1];
        //~ }
        //~ else{
            //~ i = ramaBaux.size ();
            //~ b = ramaBaux[i-1];  
        //~ }
        b = bauxB;
    }
    
    BaseA = bauxA;
    BaseB = bauxB;

    /*The Bases stays in the same arm*/
    if ( ( b == BaseA ) || ( b == BaseB ) ) {
        if ( Bases_Position ( BaseA , BaseB ) == 0 ) {
            if ( gravity == DOWN ){ return BaseA;}
            else if ( gravity == UP ) {return BaseB;}
        }else{
            if ( gravity == DOWN ) {return BaseB;}
            else if ( gravity == UP ) {return BaseA;}
        }
    }else{
        return b;
    }
}


/*
Return the pointer of one Base result of reduce two Bases ( these common base in the tree )
*/
Base * System::Reduced_Base ( string BaseA_name , string BaseB_name ) {
    return Reduced_Base ( get_Base ( BaseA_name ) , get_Base ( BaseB_name ) );
}


/*
Method that it said us if one Point is more near that other of the Point O
*/
int System::Points_Position ( Point * PointA , Point * PointB ) {
    Point * pauxA = PointA;
    int find = 0;
    while ( ( PointA-> get_name () != "O" ) && ( find == 0 ) ) {
        PointA = get_Point ( PointA-> get_Previous_Point ()-> get_name () );
        if ( PointA == PointB ) find = 1;
    }
    PointA = pauxA;
    return find;/*If return 0 , PointA is more near of Point O than PointB else return 1*/
}


/*
Return the pointer of one Point result of reduce two Points ( these common base in the tree )
*/
Point * System::Reduced_Point ( Point * PointA , Point * PointB ) {
    Point * pauxA = PointA;
    Point * pauxB = PointB;

    vector < Point * > ramaA;
    vector < Point * >ramaB;

    ramaA.push_back ( PointA );
    ramaB.push_back ( PointB );

    while ( PointA-> get_name () != "O" ) {
        ramaA.push_back ( get_Point ( PointA-> get_Previous_Point ()-> get_name () ) );
        PointA = get_Point ( PointA-> get_Previous_Point ()-> get_name () );
    }

    while ( PointB-> get_name () != "O" ) {
        ramaB.push_back ( PointB-> get_Previous_Point () );
        PointB = get_Point ( PointB-> get_Previous_Point ()-> get_name () );
    }

    int i;
    vector < Point * > ramaAaux;
    vector < Point * > ramaBaux;
    for ( i = ramaA.size () -1 ; i >= 0 ; i-- ) {
        ramaAaux.push_back ( ramaA.back () );
        ramaA.pop_back () ;
    }

    for ( i = ramaB.size () -1 ; i >= 0 ; i-- ) {
        ramaBaux.push_back ( ramaB.back () );
        ramaB.pop_back () ;
    }

    /*Now run this vectors in pairs and stop when these pairs are'n equals*/
    i = 0;
    int encontrado = 0;
    while ( ( i < ramaAaux.size () ) and ( i < ramaBaux.size () ) and ( encontrado == 0 ) )
        if ( ramaAaux[i]-> get_name () == ramaBaux[i]-> get_name () )
            i++;
        else encontrado = 1;

    PointA = pauxA;
    PointB = pauxB;

    Point * p = ramaAaux [i-1];

    /*The Points stays in the same arm*/
    if ( ( p == PointA ) || ( p == PointB ) ) {
        if ( Points_Position ( PointA , PointB ) == 0 ) {
            if ( gravity == DOWN ){ return PointA;}
            else if ( gravity == UP ) {return PointB;}
        }else{
            if ( gravity == DOWN ) {return PointB;}
            else if( gravity == UP ) {return PointA;}
        }
    }else{
        return p;
    }
}

/*
Return the pointer of one Point result of reduce two Points ( these common base in the tree )
*/
Point * System::Reduced_Point ( string PointA_name , string PointB_name ) {
    return Reduced_Point ( get_Point ( PointA_name ) , get_Point ( PointB_name ) );
}


/*
Return the pointer of the previous Point in branch from PointA to PointB (gravity down)
*/
Point * System::Pre_Point_Branch ( Point * PointA , Point * PointB ) {
    Point * pauxA = PointA;
    Point * pauxB = PointB;

    vector < Point * > ramaA;
    vector < Point * >ramaB;

    ramaA.push_back ( PointA );
    ramaB.push_back ( PointB );

    while ( PointA-> get_name () != "O" ) {
        ramaA.push_back ( get_Point ( PointA-> get_Previous_Point ()-> get_name () ) );
        PointA = get_Point ( PointA-> get_Previous_Point ()-> get_name () );
    }

    while ( PointB-> get_name () != "O" ) {
        ramaB.push_back ( PointB-> get_Previous_Point () );
        PointB = get_Point ( PointB-> get_Previous_Point ()-> get_name () );
    }

    int i;
    vector < Point * > ramaAaux;
    vector < Point * > ramaBaux;
    for ( i = ramaA.size () -1 ; i >= 0 ; i-- ) {
        ramaAaux.push_back ( ramaA.back () );
        ramaA.pop_back () ;
    }

    for ( i = ramaB.size () -1 ; i >= 0 ; i-- ) {
        ramaBaux.push_back ( ramaB.back () );
        ramaB.pop_back () ;
    }

    /*Now run this vectors in pairs and stop when these pairs are'n equals*/
    i = 0;
    int encontrado = 0;
    while ( ( i < ramaAaux.size () ) and ( i < ramaBaux.size () ) and ( encontrado == 0 ) )
        if ( ramaAaux[i]-> get_name () == ramaBaux[i]-> get_name () )
            i++;
        else encontrado = 1;

    PointA = pauxA;
    PointB = pauxB;

    Point * p = ramaAaux [i];


    if ( p == PointB ){
	return PointA;
    }

    /*The Points stays in the same arm*/
/*    if ( ( p == PointA ) || ( p == PointB ) ) {
        if ( Points_Position ( PointA , PointB ) == 0 ) {
            if ( gravity == DOWN ){ return PointA;}
            else if ( gravity == UP ) {return PointB;}
        }else{
            if ( gravity == DOWN ) {return PointB;}
            else if( gravity == UP ) {return PointA;}
        }*/
    else{
        return p;
    }
}


/*
Auxiliar method fot calculate Rotation_Matrix ( BaseA is Reduced_Base )
*/
//~ Matrix System::Rotation_Matrix_Aux ( Base * BaseA , Base * BaseB ) {
    //~ Matrix rt = BaseB-> rotation_matrix () ;
    //~ Matrix bAux;
    //~ while ( BaseB-> get_Previous_Base ()-> get_name () != BaseA-> get_name () ) {
        //~ BaseB = BaseB-> get_Previous_Base () ;
        //~ bAux = BaseB-> rotation_matrix () ;
        //~ /*rt = rt * bAux;*/
        //~ rt =  bAux * rt;
    //~ }
    //~ return rt;
//~ }


/*
Auxiliar method fot calculate Rotation_Matrix ( BaseA is Reduced_Base )
*/
Matrix System::Rec_Rotation_Matrix (  Base * BaseA , Base * BaseB ) {
    Matrix rt = BaseB-> rotation_matrix () ;
    
    if (BaseB->get_Previous_Base () !=  BaseA){
        Matrix bAux =  Rec_Rotation_Matrix (  BaseA , BaseB->get_Previous_Base () )   ;
        return bAux* rt;
    }
    else{
        return rt;
    }

}



/*
Return the Rotation Matrix between two Bases ( BaseA --> BaseB )
*/
Matrix System::Rotation_Matrix ( Base * BaseA , Base * BaseB ) {
    if ( BaseA != BaseB ) {
        Base * reducedbase = NULL;

        /*The gravity no affect here*/

        if ( gravity == UP ) {
            gravity = DOWN;
            reducedbase = Reduced_Base ( BaseA , BaseB );
            gravity = UP;
        }else
            reducedbase = Reduced_Base ( BaseA , BaseB );


        if ( reducedbase == BaseA )
            return Rec_Rotation_Matrix ( BaseA , BaseB );
            //return Rotation_Matrix_Aux ( BaseA , BaseB );
        else
            if ( reducedbase == BaseB )
                return Rec_Rotation_Matrix ( BaseB , BaseA ).transpose () ;
                //return Rotation_Matrix_Aux ( BaseB , BaseA ).transpose () ;
                
            else
                /*return Rotation_Matrix_Aux ( reducedbase , BaseB ) * Rotation_Matrix_Aux ( reducedbase , BaseA ).transpose () ;*/
                return Rec_Rotation_Matrix ( reducedbase , BaseA ).transpose () * Rec_Rotation_Matrix ( reducedbase , BaseB );
                //return Rotation_Matrix_Aux ( reducedbase , BaseA ).transpose () * Rotation_Matrix_Aux ( reducedbase , BaseB );
    }else{
        lst laux;
        laux.append(1); laux.append(0); laux.append(0);
        laux.append(0); laux.append(1); laux.append(0);        
        laux.append(0); laux.append(0); laux.append(1);        
        Matrix Aux ( 3 , 3 , laux);
        //Matrix Aux ( 3 , 3 , lst ( 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 ) );
        return Aux;
    }
}

   
/*
Return the Rotation_Matrix between two Bases ( BaseA --> BaseB )
*/

Matrix System::Rotation_Matrix  ( string base_nameA , string base_nameB ) {
    try{
        Base * BaseA = get_Base ( base_nameA );
        if ( BaseA == NULL ) {
            Frame * frame = get_Frame ( base_nameA );
            BaseA = frame-> get_Base () ;
        }

        Base * BaseB = get_Base ( base_nameB );
        if ( BaseB == NULL ) {
            Frame * frame = get_Frame ( base_nameB );
            BaseB = frame-> get_Base () ;
        }
        if ( BaseA == NULL or BaseB == NULL )throw 1;

        return Rotation_Matrix( BaseA , BaseB );
    }catch ( int i ) {
        lst laux;
        laux.append(0); laux.append(0); laux.append(0);
        laux.append(0); laux.append(0); laux.append(0);        
        laux.append(0); laux.append(0); laux.append(0);        
        Matrix Aux ( 3 , 3 , laux);
        //Matrix Aux ( 3 , 3 , lst ( 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ) );
        return Aux;
    }
}

/*
Auxiliar method fot calculate Position_Vector ( Point is reducedbase )
*/
//~ Vector3D System::Position_Vector_Aux ( Point * PointA , Point * PointB ) {
//~ 
    //~ Vector3D pv = * PointB-> get_Position_Vector ();
    //~ Vector3D vAux;
    //~ while ( PointB-> get_Previous_Point () != PointA ) {
//~ 
        //~ PointB = PointB-> get_Previous_Point ();
        //~ vAux = * PointB-> get_Position_Vector ();
//~ 
        //~ pv = pv + vAux;
    //~ }
   //~ 
    //~ return pv;
//~ }

/*
Auxiliar recursive method fot calculate Position_Vector ( Point is reducedbase )
*/
void System::Rec_Position_Vector ( Point * PointA , Point * PointB , Vector3D & Vpos ) {
    Vector3D Vaux = * PointB-> get_Position_Vector ();

    PointB = PointB-> get_Previous_Point ();
    
    if (gravity == DOWN){
        if (Vpos.get_Base() == NULL  ){
            Vpos = Vaux;
        }
        else{
            Vpos = Vpos + Vaux;   
        }

        if (PointB != PointA){
            Rec_Position_Vector ( PointA , PointB , Vpos); 
        }
        return;
    }
    else if (gravity == UP){

        if (PointB != PointA){
            Rec_Position_Vector ( PointA , PointB , Vpos);
            Vpos = Vpos + Vaux;
        }
        else{
            Vpos = Vaux;
        }
        return;
    }    
}
 
/*
Return the Position Vector between two Points ( PointA --> PointB )
*/
Vector3D System::Position_Vector ( Point * PointA , Point * PointB ) {
    if ( PointA != PointB ) {
        Point * reducedpoint = NULL;

        /*The gravity no effect here*/
        if ( gravity == UP ) {
            gravity = DOWN;
            reducedpoint = Reduced_Point ( PointA , PointB );
            gravity = UP;
        }else
            reducedpoint = Reduced_Point ( PointA , PointB );

        if ( reducedpoint == PointA ) {
            //return Position_Vector_Aux ( PointA , PointB );

            Vector3D Vout;
            Rec_Position_Vector( PointA , PointB , Vout);
            return Vout;
            
        }else if ( reducedpoint == PointB ) {
            //return - Position_Vector_Aux ( PointB , PointA );
            Vector3D Vout;
            Rec_Position_Vector( PointB , PointA , Vout);
            return -Vout;
        }else{ 
            //return Position_Vector_Aux ( reducedpoint , PointB ) - Position_Vector_Aux ( reducedpoint , PointA );
            Vector3D VoutB;
            Vector3D VoutA;
            Vector3D VoutC;
            if ( gravity == UP ) {
                gravity = DOWN;
                Rec_Position_Vector( reducedpoint , PointB , VoutB);
                Rec_Position_Vector( reducedpoint , PointA , VoutA);
                VoutC = VoutB-VoutA;
                gravity = UP;
            }else{
                Rec_Position_Vector( reducedpoint , PointB , VoutB);
                Rec_Position_Vector( reducedpoint , PointA , VoutA);
                VoutC = VoutB-VoutA;
            }
            return VoutC;
        }
    }else
        return Vector3D( Matrix ( 3 , 1 ) , Base_xyz , this);
}


/*
Return the Position Vector between two Points ( PointA --> PointB )
*/
Vector3D System::Position_Vector ( string PointA_name , string PointB_name ) {
    return Position_Vector ( get_Point ( PointA_name ) , get_Point ( PointB_name ) );
}


/*
Auxiliar method fot calculate Angular_Velocity (BaseA is Reduced_Base)
*/
//~ Vector3D System::Angular_Velocity_Aux ( Base * BaseA , Base * BaseB ) {
//~ 
    //~ Vector3D  rt = BaseB-> angular_velocity ();
//~ 
    //~ rt.set_System ( this );
    //~ Vector3D bAux ( ( ex ) 0 , ( ex ) 0 , ( ex ) 0 , BaseB , this );
    //~ while ( BaseB-> get_Previous_Base () != BaseA ) {
        //~ BaseB = BaseB-> get_Previous_Base ();
        //~ bAux = BaseB-> angular_velocity ();
        //~ bAux.set_System ( this );
        //~ rt = rt + bAux;
    //~ }
    //~ rt.set_System ( this );
    //~ return rt;
//~ }

/*
Method fot calculate Angular_Velocity with tables
*/
//~ Vector3D System::Angular_Velocity_Tables ( Base * BaseA , Base * BaseB, map  < Base*, Vector3D > &OM_abs ) {
//~ 
    //~ if (  (OM_abs[BaseB]).get_Base() != NULL) { return OM_abs[BaseB] ;}
//~ 
    //~ Vector3D  rt = BaseB-> angular_velocity ();
//~ 
    //~ rt.set_System ( this );
    //~ Vector3D bAux ( ( ex ) 0 , ( ex ) 0 , ( ex ) 0 , BaseB , this );
    //~ 
    //~ if (  (OM_abs[BaseB-> get_Previous_Base ()]).get_Base() != NULL) { cout << "rt  ="<< rt <<endl;rt = rt + OM_abs[BaseB-> get_Previous_Base ()] ;cout << "iep2"<<endl;rt.set_System ( this );return rt;}
    //~ 
    //~ while ( BaseB-> get_Previous_Base () != BaseA ) {
        //~ BaseB = BaseB-> get_Previous_Base ();
        //~ bAux = BaseB-> angular_velocity ();
        //~ bAux.set_System ( this );
        //~ rt = rt + bAux;
        //~ rt.set_System ( this );
        //~ OM_abs[BaseB] = rt;
    //~ }
    //~ rt.set_System ( this );
    //~ return rt;
//~ }



/*
Auxiliar method fot calculate Angular_Velocity (BaseA is Reduced_Base)
*/

void System::Rec_Angular_Velocity (  Base * BaseA , Base * BaseB , Vector3D & Vomega){

    Vector3D  rt = BaseB-> angular_velocity ();
    rt.set_System ( this );
    BaseB = BaseB-> get_Previous_Base ();

    if (gravity == DOWN){    
        if (Vomega.get_Base() == NULL ){
            Vomega = rt;
        }    
        else{
            Vomega = rt + Vomega ;   
        }    
        if (BaseB != BaseA ){
            Rec_Angular_Velocity ( BaseA , BaseB , Vomega); 
        }
        return;    
    }
    else if (gravity == UP){
        if (BaseB != BaseA ){
            Rec_Angular_Velocity ( BaseA , BaseB , Vomega); 
            Vomega = Vomega + rt;
        }
        else{
            Vomega = rt;
        }
        return;
    }     
}

/*
Return the Angular Velocity between two Bases ( BaseA --> BaseB )
*/
Vector3D System::Angular_Velocity ( Base * BaseA , Base * BaseB ) {
    if ( BaseA != BaseB ) {
        Base * reducedbase = NULL;

        /*Comprobe that exist the txo Bases*/
        try{

            if ( ( Search_Object ( Bases , BaseA-> get_name () ) == NULL) || ( Search_Object ( Bases , BaseB-> get_name () ) == NULL) ) throw 1;

            /*The gravity no affect here*/
            if ( gravity == UP ) {
                gravity = DOWN;
                reducedbase = Reduced_Base ( BaseA , BaseB );
                gravity = UP;
            }else
                reducedbase = Reduced_Base ( BaseA , BaseB );
                

            if ( reducedbase == BaseA ) {
                //return Angular_Velocity_Aux ( BaseA , BaseB );
                Vector3D Vout;
                Rec_Angular_Velocity ( BaseA, BaseB , Vout) ;
                return Vout;
            }else if ( reducedbase == BaseB ) {
                //return -Angular_Velocity_Aux ( BaseB , BaseA );
                Vector3D Vout;
                Rec_Angular_Velocity ( BaseB, BaseA , Vout) ;
                return -Vout;
                
            }else{
                //return Angular_Velocity_Aux ( reducedbase , BaseB )-Angular_Velocity_Aux ( reducedbase , BaseA );
                Vector3D VoutA;
                Vector3D VoutB;
                Vector3D VoutC;
                if ( gravity == UP ) {
                    
                    gravity = DOWN;
                    Rec_Angular_Velocity ( reducedbase, BaseA , VoutA) ;
                    Rec_Angular_Velocity ( reducedbase, BaseB , VoutB) ;
                    VoutC = VoutB-VoutA;
                    gravity = UP;
                }else{
                    Rec_Angular_Velocity ( reducedbase, BaseA , VoutA) ;
                    Rec_Angular_Velocity ( reducedbase, BaseB , VoutB) ;
                    VoutC = VoutB-VoutA;
                }
                return VoutC;
                
            }
            
        }catch ( int i ){
            outError ( "ERR - The two Bases don't exist in this System" );
        }

    }else
        return Vector3D ( Matrix ( 3 , 1 ) , BaseB , this );


}


/*
Return the Angular Velocity between two Bases of frames ( BaseA --> BaseB )
*/
Vector3D System::Angular_Velocity ( string base_frame_nameA , string base_frame_nameB ) {
    try{
        Base * BaseA = get_Base ( base_frame_nameA );
        if ( BaseA == NULL ) {
            Frame * frame = get_Frame ( base_frame_nameA );
            BaseA = frame-> get_Base () ;
        }

        Base * BaseB = get_Base ( base_frame_nameB );
        if ( BaseB == NULL ) {
            Frame * frame = get_Frame ( base_frame_nameB );
            BaseB = frame-> get_Base () ;
        }
        if ( BaseA == NULL or BaseB == NULL )throw 1;
//      Change made by JRos 2011/06/20 (does not it become recursive?)
//      return Angular_Velocity_Aux ( BaseA , BaseB );
        return Angular_Velocity( BaseA , BaseB );
    }catch ( int i ) {
        Vector3D empty;
        return empty;
    }
}


/*
Return the Angular Velocity tensor between two Bases ( BaseA --> BaseB )
*/
Tensor3D System::Angular_Velocity_Tensor ( Base * BaseA , Base * BaseB ) {
    try{
        if ( get_Base ( BaseA-> get_name () ) == NULL or get_Base ( BaseB-> get_name () ) == NULL )throw 1;
        Vector3D vaux = Angular_Velocity ( BaseA , BaseB );
        Matrix maux ( 3 , 3 );

        maux ( 0 , 1 ) = -vaux ( 2 , 0 );
        maux ( 0 , 2 ) = vaux ( 1 , 0 );
        maux ( 1 , 0 ) = vaux ( 2 , 0 );
        maux ( 1 , 2 ) = -vaux ( 0 , 0 );
        maux ( 2 , 0 ) = -vaux ( 1 , 0 );
        maux ( 2 , 1 ) = vaux ( 0 , 0 );

        Tensor3D sol ( "" , maux , vaux.get_Base () , this );
        return sol;
    }catch ( int i ) {
        Tensor3D empty;
        return empty;
    }
}

/*
Auxiliar method for calculate the velocity vector of PointB-PointA vector
*/
//~ Vector3D System::Velocity_Vector_Aux ( Point * PointA , Point * PointB ) {
//~ 
    //~ Point * PA = PointB;
    //~ Vector3D  V_tot = Vector3D ( "V_tot" , 0 , 0 , 0 , PointB -> get_Position_Vector () -> get_Base(),this );
//~ 
    //~ while ( PA -> get_Previous_Point () != PointA ) {
//~ 
//~ 
        //~ Point * OA = PA -> get_Previous_Point ();
        //~ //Point * OB = OA -> get_Previous_Point ();
//~ 
        //~ Vector3D * OAPA = PA -> get_Position_Vector ();
        //~ Vector3D * OBOA = OA -> get_Position_Vector ();
//~ 
        //~ Base * BA = OAPA -> get_Base();
        //~ Base * BB = OBOA -> get_Base();
//~ 
        //~ Vector3D Omega_BA_BB = Angular_Velocity(BB,BA); 
//~ 
        //~ Vector3D OA_PA = Position_Vector(OA, PA);
        //~ Vector3D VOAPA = Dt(OA_PA,BA);
//~ 
        //~ Vector3D PA_rel = Position_Vector(OA, PointB);
        //~ 
//~ 
        //~ Vector3D V_rel = VOAPA + (Omega_BA_BB ^ PA_rel);
//~ 
//~ 
        //~ V_tot = V_tot + V_rel;
//~ 
        //~ PA = PA-> get_Previous_Point ();
    //~ }
//~ 
    //~ return V_tot;
//~ }

/*
Auxiliar method for calculate the velocity vector of PointP  defined in FrameP with respecto to FrameF
*/
void System::Rec_Velocity_Vector (Frame * FrameF , Point * PointP,  Point * PointO , Vector3D & Vvel ){

    //Point * P = PointP;

    if (PointO->get_Position_Vector () == NULL ){
        PointO = PointP;
    } //first iteration 

    
    if (PointP == FrameF->get_Point()){
        Vvel = Vector3D( Matrix ( 3 , 1 ) , Base_xyz , this);
        return;
    }
    
    Point * O1 = PointO -> get_Previous_Point ();// O-1 point
    Vector3D * O1_O  = PointO-> get_Position_Vector ();
    Base * B  = O1_O  -> get_Base();



    if (O1 == FrameF->get_Point()){
        Vector3D Omega = Angular_Velocity(FrameF->get_Base(),B);
        Vector3D O1_P = Position_Vector(O1 , PointP);
        Vector3D VO1_P = Dt(*O1_O, B);
        if (Vvel.get_Base() == NULL ){
            Vvel =  VO1_P + (Omega ^ O1_P);
        }
        else{
            Vvel = (Vvel + VO1_P) + (Omega ^ O1_P);  
        }
    }
    else{
        Point * O2 = O1 -> get_Previous_Point ();// O-2 point
        Vector3D * O2_O1 = O1-> get_Position_Vector ();
        Base * B1 = O2_O1 -> get_Base();
        Vector3D Omega = Angular_Velocity(B1,B);
        Vector3D O1_P = Position_Vector(O1 , PointP);

        Vector3D VO1_O = Dt(*O1_O, B);
        
        if (gravity == UP) { Rec_Velocity_Vector (FrameF , PointP , O1, Vvel ); }
              
        if (Vvel.get_Base() == NULL ){
            Vvel = VO1_O + (Omega ^ O1_P);
        }
        else{
            Vvel = (Vvel + VO1_O) + (Omega ^ O1_P);
        }

        if (gravity == DOWN) { Rec_Velocity_Vector (FrameF , PointP , O1, Vvel ); }
        
        
    }

    

    return;    

}


/*
Return the Velocity Vector of the point PointB with respect to Frame 
*/
Vector3D System::Velocity_Vector (Frame * FrameF , Point * PointB ) {
    // OLD procedure, Dt based ==>> OK
    //Vector3D Vaux = Position_Vector(FrameF->get_Point(),PointB);
    //return Dt(Vaux,FrameF);
    
    
    
    Point * PointA = FrameF->get_Point();

    Point * reducedpoint = NULL;  
    // The gravity no effect here 
    if ( gravity == UP ) {
        gravity = DOWN;
        reducedpoint = Reduced_Point ( PointA , PointB );
        gravity = UP;
    }else
        reducedpoint = Reduced_Point ( PointA , PointB );
            
            
    if ( reducedpoint == PointA ) {
        Point * Paux = new ( Point );
        Vector3D VvelB;
        Rec_Velocity_Vector (FrameF ,PointB ,Paux, VvelB);
        return VvelB ;   
          
    }else if ( reducedpoint == PointB ) { 
        Point * Paux = new ( Point );
        Vector3D VvelA;        
        Frame FrameAux = Frame(PointB, FrameF->get_Base() );
        Rec_Velocity_Vector (&FrameAux ,PointA ,Paux, VvelA);
        return -VvelA;  

    }else{
        Point * PauxA = new ( Point );
        Point * PauxB = new ( Point );
        Vector3D VvelA;
        Vector3D VvelB;
        Vector3D VvelC;
        
        Frame FrameAux = Frame(reducedpoint, FrameF->get_Base() );
        
        if ( gravity == UP ) {
            gravity = DOWN;
            Rec_Velocity_Vector (&FrameAux, PointA ,PauxA, VvelA);
            Rec_Velocity_Vector (&FrameAux, PointB ,PauxB, VvelB);
            VvelC = VvelB - VvelA;
            gravity = UP;

        }else{
            Rec_Velocity_Vector (&FrameAux, PointA ,PauxA, VvelA);
            Rec_Velocity_Vector (&FrameAux, PointB ,PauxB, VvelB);
            VvelC = VvelB - VvelA;
        }
        
        return VvelC;
        

    }
}

/*
Return the Velocity vector
*/
Vector3D System::Velocity_Vector ( string Frame_name , string PointA_name  ) {
    return Velocity_Vector (get_Frame( Frame_name ) , get_Point ( PointA_name ) );
}

/*
Return the Velocity Vector of the point PointB respect Frame in Solid Sol
*/
Vector3D System::Velocity_Vector (Frame * Frame , Point * Point, Solid * Sol ) {

    Vector3D Omega = Angular_Velocity(Frame -> get_Base(),Sol->get_Base());
    Vector3D OSol_P = Position_Vector(Sol->get_Point(),Point );
    Vector3D Velocity;
    
    if (gravity == UP && OSol_P.get_Base() == Sol->get_Base()){
        Velocity = Velocity_Vector(Frame,Sol->get_Point() ) + (Omega ^ OSol_P );
    }else if(gravity == UP && OSol_P.get_Base() != Sol->get_Base()){
        gravity= DOWN;
        Velocity = Velocity_Vector(Frame,Sol->get_Point() ) + (Omega ^ OSol_P );
        gravity= UP;
    }else{
        Velocity = Velocity_Vector(Frame,Sol->get_Point() ) + (Omega ^ OSol_P );
    }
    
    //~ cout << "====================== "<< Sol->get_name()<<" ===================" << endl;
    //~ cout << unatomize(Velocity_Vector(Frame,Sol->get_Point() ) - Velocity_VectorOLD(Frame,Sol->get_Point() ) )<< endl;
    return Velocity;
}

/*
Return the Velocity Vector of the point PointB respect Frame in Solid Sol
*/
Vector3D System::Velocity_Vector (string Frame_name , string PointA_name, string Solid_name ) {
    return Velocity_Vector (get_Frame( Frame_name ) , get_Point ( PointA_name ), get_Solid (Solid_name) );
}


void System::Rec_Angular_Acceleration (  Base * BaseA , Base * BaseB , Vector3D & Valpha){

    Vector3D  rt = BaseB-> angular_acceleration ();
    rt.set_System ( this );
    BaseB = BaseB-> get_Previous_Base ();

    if (gravity == DOWN){    
        if (Valpha.get_Base() == NULL ){
            Valpha = rt;
        }    
        else{
            Valpha = rt + Valpha ;   
        }    
        if (BaseB != BaseA ){
            Rec_Angular_Acceleration ( BaseA , BaseB , Valpha); 
        }
        return;    
    }
    else if (gravity == UP){
        if (BaseB != BaseA ){
            Rec_Angular_Acceleration ( BaseA , BaseB , Valpha); 
            Valpha = Valpha + rt;
        }
        else{
            Valpha = rt;
        }
        return;
    }     
}


/*
Return the Angular Acceleration Vector between two Bases ( BaseA --> BaseB )
*/
Vector3D System::Angular_Acceleration  ( string base_frame_nameA , string base_frame_nameB ) {
    try{
        Base * BaseA = get_Base ( base_frame_nameA );
        if ( BaseA == NULL ) {
            Frame * frame = get_Frame ( base_frame_nameA );
            BaseA = frame-> get_Base () ;
        }

        Base * BaseB = get_Base ( base_frame_nameB );
        if ( BaseB == NULL ) {
            Frame * frame = get_Frame ( base_frame_nameB );
            BaseB = frame-> get_Base () ;
        }
        if ( BaseA == NULL or BaseB == NULL )throw 1;
            return Angular_Acceleration( BaseA , BaseB );
    }catch ( int i ) {
        Vector3D empty;
        return empty;
    }
}

/*
Return the Angular Acceleration Vector between two Bases ( BaseA --> BaseB )
*/
Vector3D System::Angular_Acceleration (  Base * BaseA , Base * BaseB ){
    return Dt ( Angular_Velocity ( BaseA , BaseB ) ,  BaseB );
    if ( BaseA != BaseB ) {
        Base * reducedbase = NULL;

        /*Comprobe that exist the two Bases*/
        try{

            if ( ( Search_Object ( Bases , BaseA-> get_name () ) == NULL) || ( Search_Object ( Bases , BaseB-> get_name () ) == NULL) ) throw 1;

            /*The gravity no affect here*/
            if ( gravity == UP ) {
                gravity = DOWN;
                reducedbase = Reduced_Base ( BaseA , BaseB );
                gravity = UP;
            }else
                reducedbase = Reduced_Base ( BaseA , BaseB );
                

            if ( reducedbase == BaseA ) {
                Vector3D Vout;
                Rec_Angular_Acceleration ( BaseA, BaseB , Vout) ;
                return Vout;
            }else if ( reducedbase == BaseB ) {
                Vector3D Vout;
                Rec_Angular_Acceleration ( BaseB, BaseA , Vout) ;
                return -Vout;
                
            }else{
                Vector3D VoutA;
                Vector3D VoutB;
                Vector3D VoutC;
                if ( gravity == UP ) {
                    
                    gravity = DOWN;
                    Rec_Angular_Acceleration ( reducedbase, BaseA , VoutA) ;
                    Rec_Angular_Acceleration ( reducedbase, BaseB , VoutB) ;
                    VoutC = VoutB-VoutA;
                    gravity = UP;
                }else{
                    Rec_Angular_Acceleration ( reducedbase, BaseA , VoutA) ;
                    Rec_Angular_Acceleration ( reducedbase, BaseB , VoutB) ;
                    VoutC = VoutB-VoutA;
                }
                return VoutC;
                
            }
            
        }catch ( int i ){
            outError ( "ERR - The two Bases don't exist in this System" );
        }

    }else
        return Vector3D ( Matrix ( 3 , 1 ) , BaseB , this );

     
}

/*
Return the Velocity Vector of the point PointB with respect to Frame 
*/
Vector3D System::Acceleration_Vector (Frame * FrameF , Point * PointB ) {
    // OLD procedure, Dt based ==>> OK
    Vector3D Vaux = Position_Vector(FrameF->get_Point(),PointB);
    
    return Dt(Dt(Vaux,FrameF),FrameF) ;
    
    //~ 
    //~ Point * PointA = FrameF->get_Point();
//~ 
    //~ Point * reducedpoint = NULL;  
    //~ // The gravity no effect here 
    //~ if ( gravity == UP ) {
        //~ gravity = DOWN;
        //~ reducedpoint = Reduced_Point ( PointA , PointB );
        //~ gravity = UP;
    //~ }else
        //~ reducedpoint = Reduced_Point ( PointA , PointB );
            //~ 
            //~ 
    //~ if ( reducedpoint == PointA ) {
        //~ Point * Paux = new ( Point );
        //~ Vector3D VvelB;
        //~ Rec_Velocity_Vector (FrameF ,PointB ,Paux, VvelB);
        //~ return VvelB ;   
          //~ 
    //~ }else if ( reducedpoint == PointB ) { 
        //~ Point * Paux = new ( Point );
        //~ Vector3D VvelA;        
        //~ Frame FrameAux = Frame(PointB, FrameF->get_Base() );
        //~ Rec_Velocity_Vector (&FrameAux ,PointA ,Paux, VvelA);
        //~ return -VvelA;  
//~ 
    //~ }else{
        //~ Point * PauxA = new ( Point );
        //~ Point * PauxB = new ( Point );
        //~ Vector3D VvelA;
        //~ Vector3D VvelB;
        //~ Vector3D VvelC;
        //~ 
        //~ Frame FrameAux = Frame(reducedpoint, FrameF->get_Base() );
        //~ 
        //~ if ( gravity == UP ) {
            //~ gravity = DOWN;
            //~ Rec_Velocity_Vector (&FrameAux, PointA ,PauxA, VvelA);
            //~ Rec_Velocity_Vector (&FrameAux, PointB ,PauxB, VvelB);
            //~ VvelC = VvelB - VvelA;
            //~ gravity = UP;
//~ 
        //~ }else{
            //~ Rec_Velocity_Vector (&FrameAux, PointA ,PauxA, VvelA);
            //~ Rec_Velocity_Vector (&FrameAux, PointB ,PauxB, VvelB);
            //~ VvelC = VvelB - VvelA;
        //~ }
        //~ 
        //~ return VvelC;
        //~ 
//~ 
    //~ }
}

/*
Return the Velocity vector
*/
Vector3D System::Acceleration_Vector ( string Frame_name , string PointA_name  ) {
    return Acceleration_Vector (get_Frame( Frame_name ) , get_Point ( PointA_name ) );
}

/*
Return the Velocity Vector of the point PointB respect Frame in Solid Sol
*/
Vector3D System::Acceleration_Vector (Frame * FrameF , Point * PointB, Solid * SolS ) {
    
    Vector3D Vaux = Position_Vector(FrameF->get_Point(),PointB);
    
    return Dt(Dt(Vaux,FrameF),FrameF) ;
    

    //~ Vector3D Omega = Angular_Velocity(Frame -> get_Base(),Sol->get_Base());
    //~ Vector3D OSol_P = Position_Vector(Sol->get_Point(),Point );
    //~ Vector3D Velocity;
    //~ 
    //~ if (gravity == UP && OSol_P.get_Base() == Sol->get_Base()){
        //~ Velocity = Velocity_Vector(Frame,Sol->get_Point() ) + (Omega ^ OSol_P );
    //~ }else if(gravity == UP && OSol_P.get_Base() != Sol->get_Base()){
        //~ gravity= DOWN;
        //~ Velocity = Velocity_Vector(Frame,Sol->get_Point() ) + (Omega ^ OSol_P );
        //~ gravity= UP;
    //~ }else{
        //~ Velocity = Velocity_Vector(Frame,Sol->get_Point() ) + (Omega ^ OSol_P );
    //~ }
//~ 
    //~ return Velocity;
}

/*
Return the Velocity Vector of the point PointB respect Frame in Solid Sol
*/
Vector3D System::Acceleration_Vector (string Frame_name , string PointA_name, string Solid_name ) {
    return Acceleration_Vector (get_Frame( Frame_name ) , get_Point ( PointA_name ), get_Solid (Solid_name) );
}




/*
Return the ex derivate
*/
ex System::dt ( ex expression ) {

        ex expression_derivative = diff ( expression ,get_Time_Symbol () ) ;
        
        for ( int i = 0; i < get_Coordinates ().size () ; i++ )
                expression_derivative =  expression_derivative +  diff ( expression , *get_Coordinates ()[i] )    * *get_Velocities ()[i]    + diff ( expression ,  *get_Velocities()[i] )    *  *get_Accelerations ()[i]   ;
        for ( int i = 0; i < get_AuxCoordinates ().size () ; i++ )
                expression_derivative =  expression_derivative +  diff ( expression , *get_AuxCoordinates ()[i] ) * *get_AuxVelocities ()[i] + diff ( expression ,  *get_AuxVelocities()[i] ) *  *get_AuxAccelerations ()[i] ;

        return expression_derivative ;

}

/*
Return the time derivate of the components of a vector3D 
*/
Vector3D System::dt ( Vector3D Vector3DA) {
    Vector3D dVector3DA ( "" , Dt ( Vector3DA ) , Vector3DA.get_Base () , this );
    return dVector3DA;
}



/*
Return the derivate of one Matrix ( derive all these ex )
*/
Matrix System::Dt ( Matrix MatrixA ) {
    Matrix aux ( MatrixA.rows () , MatrixA.cols () );
    for ( int i = 0 ; i < MatrixA.rows () ; i++ )
        for ( int j = 0 ; j < MatrixA.cols () ;j++ )
            aux ( i , j ) = dt ( MatrixA.get_matrix() ( i , j ) );
    return ( "d" + MatrixA.get_name () , aux.get_matrix () );

}


/*
Return the derivate of one Vector3D respect one Base ( derive all these ex )
*/
Vector3D System::Dt ( Vector3D Vector3DA , Base * base ) {
    Vector3D dVector3DA ( "" , Dt ( Vector3DA ) , Vector3DA.get_Base () , this );
    Vector3D omega = Angular_Velocity ( base , Vector3DA.get_Base () );
    return dVector3DA + ( omega  ^  Vector3DA );
}


/*
Return the derivate of one Vector3D respect one Frame ( derive all these ex )
*/
Vector3D System::Dt ( Vector3D Vector3DA , Frame * frame ) {
    return Dt ( Vector3DA , frame-> get_Base () );
}


/*
Return the derivate of one Vector3D respect one Frame or Base ( derive all these ex )
*/
Vector3D System::Dt ( Vector3D Vector3DA , string base_frame_name ) {
    try{
        Base * base = get_Base ( base_frame_name );
        if ( base == NULL ) {
            //outError ( "Looking for a Frame" );
            Frame * frame = get_Frame ( base_frame_name );
            if ( frame == NULL ) throw 1;
            else return Dt ( Vector3DA , frame );
        }else
            return Dt ( Vector3DA , base );
    }catch ( int i ) {
        outError ( (string("ERR - Inexsistent Base or Frame ") + base_frame_name).c_str() );
        Vector3D empty;
        return empty;
    }
}


/* 
Remove one Matrix of the System by name
*/
void System::remove_Matrix ( string matrix_name ) {
    vector < Matrix * >::iterator it;
    for ( it = Matrixs.begin () ; it != Matrixs.end () ; it++ )
        if ( ( * it )-> get_name () == matrix_name )
            Matrixs.erase ( it );
}


/*
This method check if the erase of one Vector 3D can be critical because it is referenced by other objects
*/
int System::can_Erase_Vector3D ( string vector3D_name ) {
    int i = 0;
    int encontrado = 0;
    /*See in Points vector*/
    while ( ( i < Points.size () ) and ( encontrado == 0 ) )
        if ( vector3D_name != Points[i]-> get_Position_Vector ()-> get_name () )
            i++;
        else encontrado = 1;
    if ( encontrado == 1 )return -1;

    return 1;
}


/*
Remove one Vector3D of the System by name
*/
void System::remove_Vector3D ( string vector3D_name ) {
    try{
        if ( can_Erase_Vector3D ( vector3D_name ) == -1 )throw 1;
        vector < Vector3D * >::iterator it;
        for ( it = Vectors.begin () ; it != Vectors.end () ; it++ )
            if ( ( * it )-> get_name () == vector3D_name )
                Vectors.erase ( it );
    }catch ( int e ) {
        outError ( (string("ERR -Impossible to erase Vector3D ") + vector3D_name).c_str() );
    }
}


/*
This method check if the erase of one Point can be critical because it is referenced by other objects
*/
int System::can_Erase_Point ( string point_name ) {
    int i = 0;
    int encontrado = 0;
    if ( Search_Object ( Points , point_name ) == NULL )return -1;

    /*See in Frames vector*/
    while ( ( i < Frames.size () ) and ( encontrado == 0 ) )
        if ( point_name != Frames[i]-> get_Point ()-> get_name () )
            i++;
        else encontrado = 1;
    if ( encontrado == 1 )return -1;

    return 1;

}


/*
Remove one Point of the System by name
*/
void System::remove_Point ( string point_name ) {
    try{
        if ( can_Erase_Point ( point_name ) == -1 )throw 1;
        vector < Point * >::iterator it;
        for ( it = Points.begin () ; it != Points.end () ; it++ )
            if ( ( * it )-> get_name () == point_name )
                Points.erase ( it );
    }catch ( int e ) {
        outError ( (string("ERR -Impossible to erase Point ") + point_name).c_str() );
    }
}


/*
This method check if the erase of one Base can be critical because it is referenced by other objects
*/
int System::can_Erase_Base ( string base_name ) {
    int i = 0;
    int encontrado = 0;
    /*See in Bases vector*/
    if ( Search_Object ( Bases , base_name ) == NULL )return -1;

    i = 0;
    /*See in Vectors vector*/
    while ( ( i < Vectors.size () ) and ( encontrado == 0 ) )
        if ( base_name != Vectors[i]-> get_Base ()-> get_name () )
            i++;
        else encontrado = 1;
    if ( encontrado == 1 )-1;

    i = 0;
    /*See in Tensors vector*/
    while ( ( i < Tensors.size () ) and ( encontrado == 0 ) )
        if ( base_name != Tensors[i]-> get_Base ()-> get_name () )
            i++;
        else encontrado = 1;
    if ( encontrado == 1 )return -1;

    return 1;
}


/*
Remove one Base of the System by name

*/
void System::remove_Base ( string base_name ) {
    try{
        if ( can_Erase_Point ( base_name ) == -1 )throw 1;
        vector < Base * >::iterator it;
        for ( it = Bases.begin () ; it != Bases.end () ; it++ )
            if ( ( * it )-> get_name () == base_name )
                Bases.erase ( it );
    }catch ( int e ) {
        outError ( (string("ERR -Impossible to erase Base ") + base_name).c_str() );
    }
}


/*
Return the jacobian Matrix between two Matrix taking into account if the result matrix will be symmetric or not. 
If symmetric == 1, the matrix will be symmetric
If symmetric == 0, the matrix won't be symmetric 
*/
Matrix System::jacobian ( Matrix MatrixA , Matrix MatrixB , ex symmetric ) {
    Matrix out ( MatrixA.cols () , MatrixB.rows () );
    try{
        if ( ( MatrixA.rows () == 1 ) and ( MatrixB.cols () == 1 ) ) {
            for ( int i = 0 ; i <  MatrixA.cols () ; i++ )
                for ( int j = 0;j< MatrixB.rows () ;j++ )
                    if( symmetric == 1){    
                        if (j >= i){
                            out ( i , j ) =  diff( MatrixA ( 0 , i ),  ex_to<symbol> ( unatomize_ex ( MatrixB ( j , 0 ) ) ) );
                        }
                        else{
                            out ( i , j ) = out ( j , i );
                        } 
                    } 
                    else{
                        out ( i , j ) =  diff( MatrixA ( 0 , i ),  ex_to<symbol> ( unatomize_ex ( MatrixB ( j , 0 ) ) ) );
                    }

        }else if  (( MatrixA.rows () == 0 ) and ( MatrixB.cols () == 1 ) ) {
          return out;
        }else if (( MatrixB.cols () == 1 ) and ( MatrixB.rows () == 1 )){
            Matrix out2 ( MatrixA.cols () , MatrixA.rows () );
            for ( int i = 0 ; i <  MatrixA.rows () ; i++ )
                for ( int j = 0;j< MatrixA.cols () ;j++ )
                    out2 ( i , j ) = diff( MatrixA ( i , j ),  ex_to<symbol> ( unatomize_ex ( MatrixB ( 0 , 0 ) ) ) );
            return atomize(out2);
        }
        else
          throw 1;
    }catch ( int e ) {
        outError ( "ERR - Imcompatible dimension of Matrixes or second matrix is not a matrix of symbols (first is a row second is a column)" );
    }
    out = atomize ( out );
    return out;
}

/*
Return the jacobian Matrix between two matrices when the result is not symmetric
*/
Matrix System::jacobian ( Matrix MatrixA ,Matrix MatrixB ) {
    return jacobian ( MatrixA , MatrixB, 0);
}

/*
Return the jacobian Matrix between one Matrix and one symbol
*/
Matrix System::jacobian ( Matrix MatrixA , symbol symbolA ) {
    Matrix MatrixB ( 1 , 1 );
    MatrixB ( 0 , 0 ) = symbolA;
    return jacobian ( MatrixA , MatrixB );
}


/*
Return the jacobian Matrix between one Matrix and one ex
*/
Matrix System::jacobian ( ex expression , Matrix MatrixB ) {
    Matrix MatrixA ( 1 , 1 );
    MatrixA ( 0 , 0 ) = expression;
    return jacobian ( MatrixA , MatrixB );
}


/*
Return the derivate between one ex and one symbol
*/
ex System::diff ( ex expression , symbol symbolA ) {

    if ( atomization == NO ){
        expression = unatomize_ex ( expression );
        return expression.diff ( symbolA );
    }
    else{
        // OLD 
        //expression = unatomize_ex ( expression );
        //return expression.diff ( symbolA );
        return recursive_differentiation (expression,symbolA);
    }
    
}

/*
Function that make the derivate of one object ( Matrix ,  Vector3D or Tensor3D ) respect one symbol
*/
template < class T >
T diff ( T object , symbol symbolA ) {
    
    for ( int i = 0 ; i < object.rows () ; i++ ){
        for ( int j = 0 ; j < object.cols() ; j++ ){
            object ( i , j ) = diff ( object ( i , j ) , symbolA );
        }
    }
    
    return object;
}


/*
Return the derivate between one ex with respect to one symbol
*/
ex System::diff ( ex expression , string symbol_name ) {
ex out = 0;
try {
    symbol_numeric * symbol_symbol=Search_Object ( coordinates , symbol_name );
    if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( velocities , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( accelerations , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( parameters , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_coordinates , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_velocities , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_accelerations , symbol_name );



    if (symbol_symbol==NULL) throw 1;
    
    out = diff ( expression , *symbol_symbol);
  
    return out;

    } catch (int e) {
		outError ( (string("ERR - The string") + symbol_name + string("is not a symbol (Coordinate velocity acceleration or parameter)")).c_str());
        return out;
    }

}



/*
Return the derivate of one Matrix respect one symbol

*/

Matrix System::diff(Matrix MatrixA,symbol symbolA){
    return ::diff(MatrixA,symbolA);
}

/*
Return the derivate of one Vector3D respect one symbol
*/
Vector3D System::diff(Vector3D VectorA,symbol symbolA){
    return ::diff(VectorA,symbolA);
}


/*
Return the derivate of one Tensor3D respect one symbol
*/
Tensor3D System::diff(Tensor3D TensorA,symbol symbolA){
    return ::diff(TensorA,symbolA);
}


/*
Return the derivate of one Matrix respect one symbol
*/
Matrix System::diff(Matrix MatrixA,string symbol_name){
try {
    symbol_numeric * symbol_symbol=Search_Object ( coordinates , symbol_name );
    if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( velocities , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( accelerations , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( parameters , symbol_name );
    //added by Aitor
    if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_coordinates , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_velocities , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_accelerations , symbol_name );

    if (symbol_symbol==NULL) throw 1;

    return ::diff(MatrixA,*symbol_symbol);
    
    } catch (int e) {
		outError ( (string("ERR - The string") + symbol_name + string("is not a symbol (Coordinate velocity acceleration or parameter)")).c_str());
    }
}

/*
Return the derivate of one Vector3D respect one symbol
*/
Vector3D System::diff(Vector3D VectorA,string symbol_name){
try {
    symbol_numeric * symbol_symbol=Search_Object ( coordinates , symbol_name );
    if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( velocities , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( accelerations , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( parameters , symbol_name );
    //added by Aitor
    if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_coordinates , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_velocities , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_accelerations , symbol_name );

    if (symbol_symbol==NULL) throw 1;

    return ::diff(VectorA,*symbol_symbol);
    
    } catch (int e) {
		outError ( (string("ERR - The string") + symbol_name + string("is not a symbol (Coordinate velocity acceleration or parameter)")).c_str());
    }
}


/*
Return the derivate of one Tensor3D respect one symbol
*/
Tensor3D System::diff(Tensor3D TensorA,string symbol_name){
try {
    symbol_numeric * symbol_symbol=Search_Object ( coordinates , symbol_name );
    if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( velocities , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( accelerations , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( parameters , symbol_name );
    //added by Aitor
    if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_coordinates , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_velocities , symbol_name );
    else if (symbol_symbol==NULL)
     symbol_symbol=Search_Object ( aux_accelerations , symbol_name );

    if (symbol_symbol==NULL) throw 1;

    return ::diff(TensorA,*symbol_symbol);
    
    } catch (int e) {
		outError ( (string("ERR - The string") + symbol_name + string("is not a symbol (Coordinate velocity acceleration or parameter)")).c_str());
    }
}


/*
Return one Matrix with all the symbols of one vector
*/
Matrix Matrix_Of_Symbols ( vector < symbol_numeric * > vect ) {
    Matrix aux ( vect.size () , 1 );
    for ( int i = 0 ; i <  vect.size () ; i++ ) {
        aux ( i , 0 ) = * vect[i];
    }
    return aux;
}


/*
Returns a Matrix with all the coordinates
*/
Matrix System::Coordinates ( void ) {
    return Matrix_Of_Symbols ( coordinates );
}

/*
Returns a Matrix with all the velocities
*/
Matrix System::Velocities ( void ) {
    return Matrix_Of_Symbols ( velocities );
}


/*
Returns a Matrix with all the accelerations
*/
Matrix System::Accelerations ( void ) {
    return Matrix_Of_Symbols ( accelerations );
}

/*
Returns a Matrix with all the auxiliar coordinates
*/
Matrix System::Aux_Coordinates ( void ) {
    return Matrix_Of_Symbols ( aux_coordinates );
}

/*
Returns a Matrix with all the auxiliar velocities
*/
Matrix System::Aux_Velocities ( void ) {
    return Matrix_Of_Symbols ( aux_velocities );
}


/*
Returns a Matrix with all the auxiliar accelerations
*/
Matrix System::Aux_Accelerations ( void ) {
    return Matrix_Of_Symbols ( aux_accelerations );
}

/*
Returns a Matrix with all the parameters
*/
Matrix System::Parameters ( void ) {
    return Matrix_Of_Symbols ( parameters );
}


/*
Returns a Matrix with all the unknowns
*/
Matrix System::Joint_Unknowns ( void ) {
    return Matrix_Of_Symbols ( unknowns );
}

/*
Returns a Matrix with all the inputs
*/
Matrix System::Inputs ( void ) {
    return Matrix_Of_Symbols ( inputs );
}


/*
This method evaluate one expression , substituting the variables from their value
*/
ex System::numeric_evaluate ( ex expression ) {
    try{

        /*Guardar en alguna variable la expresion desatomizada del atomo        */

        /*expression = unatomize_ex ( expression );*/

        /*Creamos un objeto de tipo exmap con las coordenadas, velocidades , aceleraciones, parametros y parametros desconocidos*/


        exmap em;
        for ( int i = 0 ; i < coordinates.size () ; i++ ) {
            em.insert(std::make_pair(* coordinates[i], coordinates[i]-> get_value()));
            em.insert(std::make_pair(* velocities[i], velocities[i]-> get_value()));
            em.insert(std::make_pair(* accelerations[i], accelerations[i]-> get_value()));
        }

        for ( int i = 0 ; i < parameters.size () ; i++ )
            em.insert(std::make_pair(* parameters[i], parameters[i]-> get_value()));

        for ( int i = 0 ; i < unknowns.size () ; i++ )
            em.insert(std::make_pair(* unknowns[i], unknowns[i]-> get_value()));

        expression = evalf ( expression.subs ( em ) );

    }catch ( exception & p ) {
        outError ( "ERR- in values evaluation" );
    }
    return expression;

}

/*
Method that evalue all the elements of one Matrix and return other Matrix
*/
Matrix System::evaluate_Matrix ( Matrix MatrixA ) {
    Matrix n ( MatrixA.rows () , MatrixA.cols () );
    try{
        ex expression;

        for ( int i = 0; i < MatrixA.rows () ; i++ )
            for ( int j = 0; j < MatrixA.cols () ; j++ ) {
                expression = numeric_evaluate ( MatrixA ( i , j ) );
                if ( !is_a<numeric> ( expression ) )throw 1;
                n ( i , j ) = ex_to<numeric> ( expression ).to_double () ;
            }
    }catch ( int i ) {
        outError ( "ERR- in values evaluation" );
    }
    return n;
}






//***********************Solid Methods********************************************
Vector3D System::get_SOL_Omega ( Solid * Sol){	
    Vector3D SOL_Omega = Angular_Velocity("xyz",Sol->get_Base()->get_name());  
    return SOL_Omega;
}
//Velcidad punto-referencia (punto, perteneciapunto, ref)
Vector3D System::get_SOL_Velocity (Solid * Sol){
    Vector3D OO_OSol = Position_Vector("O", Sol->get_Point()->get_name());
    Vector3D VabsOO_OSol = Dt(OO_OSol ,"abs");
    return VabsOO_OSol;
}

Vector3D System::get_SOL_GC_Velocity (Solid * Sol){
    Vector3D OO_OSol = Position_Vector("O", Sol->get_Point()->get_name());
    Vector3D VabsOO_OSol = Dt(OO_OSol ,"abs");
    Vector3D Omega_SOl = Angular_Velocity("xyz",Sol->get_Base()->get_name()); 
    Vector3D CM = *Sol -> get_CM();
    Vector3D GC_Velocity = VabsOO_OSol + (Omega_SOl ^ CM);
    return GC_Velocity;
}


/*
Return the Generalized Force associated to wrench
*/

Matrix System::GenForce(Wrench3D * wrench){
    Matrix dq = Velocities();
    Matrix GenForce(dq.rows(),1);
    
    if (gravity == DOWN || wrench-> get_Type () == "Gravity" || wrench-> get_Type () == "External") {
    //if (gravity == DOWN ) {    
        //Vector3D OO_P = Position_Vector("O",wrench->get_Point()->get_name());Vector3D Vel= Dt(OO_P,"xyz");
        Vector3D Vel = Velocity_Vector("abs",wrench -> get_Point() -> get_name(),wrench -> get_Solid() -> get_name() );
        Vector3D Omega = Angular_Velocity("xyz",wrench->get_Solid()->get_Base()->get_name());

        for (int i=0; (i < dq.rows()); ++i) {
            symbol_numeric dq_i;
            dq_i=ex_to<symbol_numeric>(dq(i,0));
            
            
            GenForce (i,0) = (wrench->get_Force()).change_Base(Base_xyz)* diff(Vel,dq_i) 
                           + (wrench->get_Momentum() ).change_Base(Base_xyz)* diff(Omega,dq_i);  
            //GenForce (i,0) = ( wrench->get_Force() + Vector3D( Matrix ( 3 , 1, lst(0,0,0) ) ,Base_xyz, this) ) * diff(Vel,dq_i)
            //           + ( wrench->get_Momentum()  + Vector3D( Matrix ( 3 , 1, lst(0,0,0) ) ,Base_xyz, this) )* diff(Omega,dq_i);                    
        
        }
        
        //~ Matrix Vel_dq    = jacobian(Vel.transpose(),dq);
        //~ Matrix Omega_dq  = jacobian(Omega.transpose(),dq);
        //~ 
        //~ GenForce = Vel_dq.transpose() * (wrench->get_Force()).change_Base(Vel.get_Base())
                 //~ + Omega_dq.transpose() *(wrench->get_Momentum() ).change_Base(Omega.get_Base()) ;

        
        
        
    }
    else{
        Vector3D VelUP   = Velocity_Vector("abs",wrench -> get_Point() -> get_name(),wrench -> get_Solid() -> get_name() );
        Matrix RVel_F = Rotation_Matrix (VelUP.get_Base(),   (wrench->get_Force()).get_Base());

        Vector3D OmegaUP = Angular_Velocity("xyz",wrench->get_Solid()->get_Base()->get_name());
        Matrix ROM_M  = Rotation_Matrix (OmegaUP.get_Base(), (wrench->get_Momentum()).get_Base());
 
  
        Matrix VelUP_dq    = jacobian(VelUP.transpose(),dq);
        Matrix OmegaUP_dq  = jacobian(OmegaUP.transpose(),dq);

        // GenForce = VelUP_dq.transpose() * RVel_F * (wrench->get_Force()) 
                // + OmegaUP_dq.transpose() * ROM_M * (wrench->get_Momentum()) ;
        GenForce = VelUP_dq.transpose() * (wrench->get_Force()).change_Base(VelUP.get_Base())
                 + OmegaUP_dq.transpose() * (wrench->get_Momentum()).change_Base(OmegaUP.get_Base());                 
                 
    }      

    return GenForce;
}

/*
Return the Generalized Force associated to a type of wrenches
*/
Matrix System::GenForceSys(string Wrench_type){
    int i = 0;	
    Matrix dq = Velocities();
    Matrix GF(dq.rows(),1);

    while ( i < Wrenches.size ()) {
      if ( Wrench_type == Wrenches[i]-> get_Type () || Wrench_type == "ALL")
        GF = GF + GenForce(Wrenches[i]);
        i++;
      }
    return GF;
}

/*
Return the Gravity Wrench of a Solid
*/
Wrench3D * System::Gravity_Wrench(Solid * Sol){

    string name = Sol->get_name();
    symbol_numeric mass = *Sol->get_mass();
    string s2="Gravity_Wrench_"+name;
    string s3="Gravity_Force_"+name;
    string s4="Gravity_Momen_"+name;
    
    symbol_numeric grav = *g;
    Point * B = Sol->get_Point();
    
    //~ Point * G = Sol->get_G();
    //~ Vector3D Fgrav = *new_Vector3D(s3,0,0,-grav*mass ,"xyz");
    //~ Vector3D Mgrav = *new_Vector3D(s4,0,0,0 ,"xyz");
    //~ Wrench3D* new_GravTor= new_Wrench3D (s2, Fgrav, Mgrav , G, Sol, "Gravity" );

    Vector3D Fgrav = *new_Vector3D(s3,0,0,-grav ,"xyz");
    Vector3D BG = *Sol->get_CM();
    Vector3D mBG = atomize(mass*unatomize(BG));
    Vector3D Mgrav = ( mBG ^ Fgrav );// + Vector3D( Matrix ( 3 , 1, lst(0,0,0) ) ,Base_xyz, this);
    Wrench3D* new_GravTor= new_Wrench3D (s2, mass*Fgrav, Mgrav , B, Sol, "Gravity" );

    return new_GravTor;
}

/*
Return the Inertia Wrench of a Solid
*/
Wrench3D * System::Inertia_Wrench(Solid * Sol){

    string name = Sol->get_name();
    string s2="Inertia_Wrench_"+name;
    Vector3D BG = *Sol->get_CM();
    symbol_numeric mass = *Sol->get_mass();
    Tensor3D I_B = *Sol->get_IT();

    Base * base = Sol->get_Base ();

    Point * B = Sol->get_Point();
    //Point * G = Sol->get_G();


    // Testing version
    //Vector3D VabsG = Velocity_Vector("abs",G -> get_name());
    //Old version
    //Vector3D OO_G = Position_Vector("O",G->get_name());
    //Vector3D VabsG = Dt(OO_G,"xyz");

    // Testing version
    Vector3D VabsB = Velocity_Vector("abs",B->get_name());
    //Old version
    //Vector3D O_B = Position_Vector("O",B->get_name());
    //Vector3D VabsP = Dt(O_B,"xyz");

    //Vector3D AabsG = Dt(VabsG,"xyz");
    Vector3D AabsB = Dt(VabsB,"xyz");
    
    

    Vector3D Omega = Angular_Velocity("xyz",base->get_name());
    Vector3D H_B = I_B * Omega;

    Vector3D mBG = atomize(mass*unatomize(BG));
    //Vector3D Fi = -(mass)*AabsG;
    Vector3D Fi = - mass*AabsB - (Dt(Omega,"xyz")^mBG) - (Omega^(Omega^mBG)); 
    Vector3D Mi_B = -Dt(H_B,"xyz") - (mBG^AabsB);

    Wrench3D* new_InTor= new_Wrench3D (s2, Fi, Mi_B , B, Sol, "Inertia" );
    return new_InTor;
}


/*
Return the Gravity Wrench of a Solid
*/
Wrench3D * System::Gravity_Wrench(string Solid_name){
    return Gravity_Wrench(get_Solid (Solid_name));
}

/*
Return the Inertia Wrench of a Solid
*/
Wrench3D * System::Inertia_Wrench(string Solid_name){
    return  Inertia_Wrench(get_Solid (Solid_name));
}
/*********************************************************************************************************
***************************** SYSTEM C EXPORT FUNCTIONS **************************************************
*********************************************************************************************************/


/*
Method that create a C file to export parameters
*/
void System::export_var_def_C ( void ) {
    ofstream cout;
    cout.open ( "var_def.c" );
    cout << csrc_double ;
    cout << "/*----------var_def.c lib3D_MEC expoted-----------*/" << endl << endl;
    cout << "/*----------time-----------*/" << endl << endl;
    cout << "double " << get_Time_Symbol () << ";" << endl;
    cout.close () ;
}


/*
Method that create a C file to export parameters GSL
*/
//~ void System::export_var_def_C_GSL ( void ) {
    //~ ofstream cout;
    //~ cout.open ( "var_def.c" );
    //~ cout << csrc_double ;
    //~ cout << "/*----------var_def.c lib3D_MEC expoted-----------*/" << endl << endl;
    //~ cout << "/*----------time-----------*/" << endl << endl;
//~ 
    //~ cout << "double " << get_Time_Symbol () << ";" << endl;
    //~ cout << "/*----------parameters-----------*/" << endl << endl;
    //~ for ( int i = 0 ; i < parameters.size () ; i++ )
        //~ cout << "double " << parameters[i]-> get_name () << ";" << endl;
    //~ cout.close () ;
//~ }


/*
Method that create a header C file to export parameters
*/
void System::export_var_def_H ( void ) {
    ofstream cout;
    cout.open ( "var_def.h" );
    cout << csrc_double ;
    cout << "/*----------var_def.h lib3D_MEC exported-----------*/" << endl << endl;
    cout << "/*----------time-----------*/" << endl << endl;
    cout << "extern double " << get_Time_Symbol () << ";" << endl;
    cout.close ();
}



/*
Method that create a header C file to export parameters GSL
*/
//~ void System::export_var_def_H_GSL ( void ) {
    //~ ofstream cout;
    //~ cout.open ( "var_def.h" );
    //~ cout << csrc_double ;
    //~ cout << "/*----------var_def.h lib3D_MEC exported-----------*/" << endl << endl;
    //~ cout << "/*----------time-----------*/" << endl << endl;
    //~ cout << "extern double " << get_Time_Symbol () << ";" << endl;
    //~ cout << "/*----------parameters-----------*/" << endl << endl;
    //~ for ( int i = 0 ; i < parameters.size () ; i++ )
        //~ cout << "extern double " << parameters[i]-> get_name () << ";" << endl;
    //~ cout.close ();
//~ }

/*
Method that create a C file for initialize the parameters
*/
void System::export_var_init_C ( void )
{
    ofstream cout;
    cout.open ( "var_init.c" );
    cout << csrc_double ;
    cout << "/*----------var_init.c lib3D_MEC expoted-----------*/" << endl << endl;
    cout << "#include <math.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "void var_init ( void )" << endl;
    cout << "{" << endl;
    cout << "/*----------time-----------*/" << endl << endl;
    cout <<  get_Time_Symbol () << " = " << t.get_value () << ";" << endl;
    cout << "}" << endl;
    cout.close ();
}

/*
Method that create a C file for initialize the parameters GSL
*/
//~ void System::export_var_init_C_GSL ( void )
//~ {
    //~ ofstream cout;
    //~ cout.open ( "var_init.c" );
    //~ cout << csrc_double ;
    //~ cout << "/*----------var_init.c lib3D_MEC expoted-----------*/" << endl << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ cout << "#include \"var_def.h\"" << endl;
    //~ cout << "void var_init ( void )" << endl;
    //~ cout << "{" << endl;
    //~ cout << "/*----------time-----------*/" << endl << endl;
    //~ cout <<  get_Time_Symbol () << " = " << t.get_value () << ";" << endl;
//~ //    cout << "/*----------parameters-----------*/" << endl << endl;
//~ //    for ( int i = 0 ; i < parameters.size () ; i++ )
//~ //        cout  << parameters[i]-> get_name () << " = " << parameters[i]-> get_value() << ";" << endl;
    //~ cout << "}" << endl;
    //~ cout.close ();
//~ }

/*
Method that create a C file to export time
*/
void System::export_time_C ( void ) {
    ofstream cout;
    cout.open ( "time_3D_mec.c" );
    cout << csrc_double ;
    cout << "/*----------time_3D_mec.c lib3D_MEC expoted-----------*/" << endl << endl;
    cout << "#include <math.h>" << endl;
    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "/*----------time-----------*/" << endl << endl;
    cout << "double " << get_Time_Symbol () << ";" << endl << endl;
    cout << "void Init_t ( void )" << endl;
    cout << "{" << endl;
    cout <<  get_Time_Symbol () << " = " << t.get_value () << ";" << endl;
    cout << "}" << endl;
    cout.close () ;
}

/*
Method that create a header C file to export time
*/
void System::export_time_H ( void ) {
    ofstream cout;
    cout.open ( "time_3D_mec.h" );
    cout << csrc_double ;
    cout << "/*----------time_3D_mec.h lib3D_MEC exported-----------*/" << endl << endl;
    cout << "/*----------time-----------*/" << endl << endl;
    cout << "extern double " << get_Time_Symbol () << ";" << endl;
    cout << "extern void Init_t ( void );" << endl << endl;
    cout.close ();
}

/*
Method that create a C file to export atoms
*/
void System::export_atom_def_C ( lst atom_list ) {
        ofstream cout;
        cout.open ( "atom_def.c" );
        cout << csrc_double ;
        cout << "/*----------atom_def.c lib3D_MEC exported-----------*/" << endl << endl;
        cout << "/*----------atoms-----------*/" << endl << endl;

        for ( size_t i = 0; i < atom_list.nops () ; ++i )
            cout << "double " << atom_list.op ( i )<< ";" << endl;

        cout.close ();

        cout.open ( "atom_def.h" );
        cout << csrc_double ;
        cout << "/*----------atom_def.h lib3D_MEC exported-----------*/" << endl << endl;
        cout << "/*----------atoms-----------*/" << endl << endl;

        for ( size_t i = 0; i < atom_list.nops () ; ++i )
            cout << "extern double " << atom_list.op ( i ) << ";" << endl;

        cout.close ();
}


/*
Method that create a C file to export atoms GSL
*/
//~ void System::export_atom_def_C_GSL ( lst atom_list ) {
        //~ ofstream cout;
        //~ cout.open ( "atom_def.c" );
        //~ cout << csrc_double ;
        //~ cout << "/*----------atom_def.c lib3D_MEC exported-----------*/" << endl << endl;
        //~ cout << "/*----------atoms-----------*/" << endl << endl;
//~ 
        //~ for ( size_t i = 0; i < atom_list.nops () ; ++i )
            //~ cout << "double " << atom_list.op ( i )<< ";" << endl;
//~ 
        //~ cout.close ();
//~ 
        //~ cout.open ( "atom_def.h" );
        //~ cout << csrc_double ;
        //~ cout << "/*----------atom_def.h lib3D_MEC exported-----------*/" << endl << endl;
        //~ cout << "/*----------atoms-----------*/" << endl << endl;
//~ 
        //~ for ( size_t i = 0; i < atom_list.nops () ; ++i )
            //~ cout << "extern double " << atom_list.op ( i ) << ";" << endl;
//~ 
        //~ cout.close ();
//~ }

/*
Method that create a header C file to export coordinates
*/
void System::export_gen_coord_H ( void ){
    ofstream cout;
    cout.open ( "gen_coord.h" );
    cout << csrc_double ;
    cout << "/*----------gen_coord.h lib3D_MEC expoted-----------*/" << endl << endl;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "extern double * q;" << endl;
    cout << "extern void Init_q_values ( void );" << endl;
    cout << "extern void Init_q ( void );" << endl;
    cout << "extern void Done_q( void );" << endl;
    cout << "extern void Reallocate_q( double * user_q );" << endl << endl;

    cout << "#define n_gen_coord " << coordinates.size ()<< endl;
//    cout << "/*----------Coordinates-----------*/" << endl << endl;
    cout.close () ;
}

/*
Method that create a C file for coordinates - Definition - Allocation - Initial Values - Free
*/
void System::export_gen_coord_C ( void ) {
    ofstream cout;
    cout.open ( "gen_coord.c" );
    cout << csrc_double ;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
//    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"gen_coord.h\"" << endl;
    cout << endl;

    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "#define " << coordinates[i]-> get_name () << " " << coordinates[i]-> get_value() << endl;

    cout << endl;
    cout << "double * q=NULL; " << endl<< endl;

    cout << "void Init_q_values ( void )" << endl;
    cout << "{" << endl;

    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "q[" << i << "]=" << coordinates[i]-> get_name () << ";" << endl;

    cout << "}" << endl << endl;

    cout << "void Init_q ( )" << endl;
    cout << "{" << endl;
    cout << " q = malloc ( n_gen_coord * sizeof(double) );" << endl;
    cout << " {int i;" << endl;
    cout << "  for ( i = 0 ; i < n_gen_coord ; i++ ) {q[i]=0.0;}" << endl;
    cout << " }" << endl;
    cout << "}" << endl << endl;

    cout << "void Done_q( ) " << endl;
    cout << "{" << endl;
    cout << "if ( q != NULL) " << endl;
    cout << "free ( q ); " << endl;
    cout << "q = NULL; " << endl;
    cout << "}" << endl<< endl;

    cout << "void Reallocate_q( double * user_q ) " << endl;
    cout << "{" << endl;
    cout << "q = user_q; " << endl;
    cout << "}" << endl<< endl;

    cout.close () ;
}

/*
Method that create a header C file to export coordinates
*/
void System::export_gen_coord_vect_def_H ( void ){
    ofstream cout;
    cout.open ( "gen_coord_vect_def.h" );
    cout << csrc_double ;
    cout << "/*----------gen_coord_vect_def.h lib3D_MEC expoted-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "extern double * q;" << endl;
    cout << "#define n_gen_coord " << coordinates.size () << endl;
    cout << "/*----------time-----------*/" << endl << endl;
    cout << "extern double " << get_Time_Symbol () << ";" << endl;
//    cout << "/*----------Coordinates-----------*/" << endl << endl;
    cout.close () ;
}

/*
Method that create a header C file to export coordinates for GSL
*/
//~ void System::export_gen_coord_vect_def_H_GSL ( void ){
    //~ ofstream cout;
    //~ cout.open ( "gen_coord_vect_def.h" );
    //~ cout << csrc_double ;
    //~ cout << "/*----------gen_coord_vect_def.h lib3D_MEC expoted-----------*/" << endl << endl;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ cout << "#include <gsl/gsl_vector.h>" << endl;
    //~ cout << "extern gsl_vector * q;" << endl;
    //~ cout << "#define n_gen_coord " << coordinates.size () << endl;
    //~ cout << "/*----------time-----------*/" << endl << endl;
    //~ cout << "extern double " << get_Time_Symbol () << ";" << endl;
//~ //    cout << "/*----------Coordinates-----------*/" << endl << endl;
    //~ cout.close () ;
//~ }

/*
Method that create a C file for initialize coordinates
*/
void System::export_gen_coord_vect_init_C ( void ) {
    ofstream cout;
    cout.open ( "gen_coord_vect_init.c" );
    cout << csrc_double ;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "#include \"gen_coord_vect_def.h\"" << endl;

    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "#define " << coordinates[i]-> get_name () << " " << coordinates[i]-> get_value() << endl;

    cout << "void gen_coord_vect_init ( void )" << endl;
    cout << "{" << endl;
    cout << "  if ( n_gen_coord > 0 )" << endl;
    cout << "  {" << endl;
    cout << " q = malloc ( n_gen_coord * sizeof(double) );" << endl;

    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "q[" << i << "]=" << coordinates[i]-> get_name () << ";" << endl;

    cout << "  }" << endl;
    cout << "}" << endl;
    cout.close () ;
}

/*
Method that create a C file for initialize coordinates for GSL
*/
//~ void System::export_gen_coord_vect_init_C_GSL ( void ) {
    //~ ofstream cout;
    //~ cout.open ( "gen_coord_vect_init.c" );
    //~ cout << csrc_double ;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ cout << "#include <gsl/gsl_vector.h>" << endl;
    //~ cout << "#include \"var_def.h\"" << endl;
    //~ cout << "#include \"gen_coord_vect_def.h\"" << endl;
//~ 
    //~ for ( int i = 0 ; i < coordinates.size () ; i++ )
        //~ cout << "#define " << coordinates[i]-> get_name () << " " << coordinates[i]-> get_value() << endl;
//~ 
    //~ cout << "void gen_coord_vect_init ( void )" << endl;
    //~ cout << "{" << endl;
    //~ cout << "  if ( n_gen_coord > 0 )" << endl;
    //~ cout << "  {" << endl;
    //~ cout << "  q = gsl_vector_alloc ( n_gen_coord );" << endl;
//~ 
    //~ for ( int i = 0 ; i < coordinates.size () ; i++ )
        //~ cout << "gsl_vector_set ( q , " << i << " , " << coordinates[i]-> get_name () << " );" << endl;
//~ 
    //~ cout << "  }" << endl;
    //~ cout << "}" << endl;
    //~ cout.close () ;
//~ }

/*
Method that create a header C file to export velocities
*/
void System::export_gen_vel_H ( void ){
    ofstream cout;
    cout.open ( "gen_vel.h" );
    cout << csrc_double ;
    cout << "/*----------gen_vel.h lib3D_MEC expoted-----------*/" << endl << endl;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "extern double * dq;" << endl;
    cout << "extern void Init_dq_values ( void );" << endl;
    cout << "extern void Init_dq ( void );" << endl;
    cout << "extern void Done_dq( void  );" << endl;
    cout << "extern void Reallocate_dq( double * user_dq );" << endl << endl;

    cout << "#define n_gen_vel " << velocities.size () << endl;
//    cout << "/*----------Velocities-----------*/" << endl << endl;
    cout.close () ;
}

/*
Method that create a C file for velocities - Definition - Allocation - Initial Values - Free
*/
void System::export_gen_vel_C ( void ) {
    ofstream cout;
    cout.open ( "gen_vel.c" );
    cout << csrc_double ;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
//    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"gen_vel.h\"" << endl;
    cout << endl;

    for ( int i = 0 ; i < velocities.size () ; i++ )
        cout << "#define " << velocities[i]-> get_name () << " " << velocities[i]-> get_value() << endl;

    cout << endl;
    cout << "double * dq=NULL; " << endl<< endl;

    cout << "void Init_dq_values ( void )" << endl;
    cout << "{" << endl;

    for ( int i = 0 ; i < velocities.size () ; i++ )
        cout << "dq[" << i << "]=" << velocities[i]-> get_name () << ";" << endl;

    cout << "}" << endl << endl;

    cout << "void Init_dq ( )" << endl;
    cout << "{" << endl;
    cout << " dq = malloc ( n_gen_vel * sizeof(double) );" << endl;
    cout << " {int i;" << endl;
    cout << "  for ( i = 0 ; i < n_gen_vel ; i++ ) {dq[i]=0.0;}" << endl;
    cout << " }" << endl;
    cout << "}" << endl << endl;

    cout << "void Done_dq( ) " << endl;
    cout << "{" << endl;
    cout << "if ( dq != NULL) " << endl;
    cout << "free ( dq ); " << endl;
    cout << "dq = NULL; " << endl;
    cout << "}" << endl<< endl;

    cout << "void Reallocate_dq( double * user_dq ) " << endl;
    cout << "{" << endl;
    cout << "dq = user_dq; " << endl;
    cout << "}" << endl<< endl;

    cout.close () ;
}

/*
Method that create a header C file to export velocities
*/
void System::export_gen_vel_vect_def_H ( void ) {
    ofstream cout;
    cout.open ( "gen_vel_vect_def.h" );
    cout << csrc_double ;
    cout << "/*----------gen_vel_vect_def.h lib3D_MEC expoted-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "extern double * dq;" << endl;
    cout << "#define n_gen_vel " << velocities.size () << endl;
    cout << "/*----------time-----------*/" << endl << endl;
    cout << "extern double " << get_Time_Symbol () << ";" << endl;
//    cout << "/*----------Velocities-----------*/" << endl << endl;
    cout.close () ;
}

/*
Method that create a header C file to export velocities GSL
*/
//~ void System::export_gen_vel_vect_def_H_GSL ( void ) {
    //~ ofstream cout;
    //~ cout.open ( "gen_vel_vect_def.h" );
    //~ cout << csrc_double ;
    //~ cout << "/*----------gen_vel_vect_def.h lib3D_MEC expoted-----------*/" << endl << endl;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ cout << "#include <gsl/gsl_vector.h>" << endl;
    //~ cout << "extern gsl_vector * dq;" << endl;
    //~ cout << "#define n_gen_vel " << velocities.size () << endl;
    //~ cout << "/*----------time-----------*/" << endl << endl;
    //~ cout << "extern double " << get_Time_Symbol () << ";" << endl;
    //~ //cout << "/*----------Velocities-----------*/" << endl << endl;
    //~ cout.close () ;
//~ }

/*
Method that create a C file for initializa velocities
*/
void System::export_gen_vel_vect_init_C ( void ) {
    ofstream cout;
    cout.open ( "gen_vel_vect_init.c" );
    cout << csrc_double ;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "#include \"gen_vel_vect_def.h\"" << endl;

    for ( int i = 0 ; i < velocities.size () ; i++ )
        cout << "#define " << velocities[i]-> get_name () << " " << velocities[i]-> get_value() << endl;

    cout << "void gen_vel_vect_init ( void )" << endl;
    cout << "{" << endl;
    cout << "  if ( n_gen_vel > 0 )" << endl;
    cout << "  {" << endl;
    cout << " dq = malloc  ( n_gen_vel * sizeof(double) );" << endl;

    for ( int i = 0 ; i < velocities.size () ; i++ )
        cout << "dq[" << i << "]=" << velocities[i]-> get_name ()  << ";" << endl;

    cout << "  }" << endl;
    cout << "}" << endl;
    cout.close () ;
}

/*
Method that create a C file for initializa velocities GSL
*/
//~ void System::export_gen_vel_vect_init_C_GSL ( void ) {
    //~ ofstream cout;
    //~ cout.open ( "gen_vel_vect_init.c" );
    //~ cout << csrc_double ;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ cout << "#include <gsl/gsl_vector.h>" << endl;
    //~ cout << "#include \"var_def.h\"" << endl;
    //~ cout << "#include \"gen_vel_vect_def.h\"" << endl;
//~ 
    //~ for ( int i = 0 ; i < velocities.size () ; i++ )
        //~ cout << "#define " << velocities[i]-> get_name () << " " << velocities[i]-> get_value() << endl;
//~ 
    //~ cout << "void gen_vel_vect_init ( void )" << endl;
    //~ cout << "{" << endl;
    //~ cout << "  if ( n_gen_vel > 0 )" << endl;
    //~ cout << "  {" << endl;
    //~ cout << "  dq = gsl_vector_alloc ( n_gen_vel );" << endl;
//~ 
    //~ for ( int i = 0 ; i < velocities.size () ; i++ )
        //~ cout << "gsl_vector_set ( dq , " << i << " , " << velocities[i]-> get_name () << " );" << endl;
//~ 
    //~ cout << "  }" << endl;
    //~ cout << "}" << endl;
    //~ cout.close () ;
//~ }

/*
Method that create a header C file to export accelerations
*/
void System::export_gen_accel_H ( void ){
    ofstream cout;
    cout.open ( "gen_accel.h" );
    cout << csrc_double ;
    cout << "/*----------gen_accel.h lib3D_MEC expoted-----------*/" << endl << endl;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "extern double * ddq;" << endl;
    cout << "extern void Init_ddq_values ( void );" << endl;
    cout << "extern void Init_ddq ( void );" << endl;
    cout << "extern void Done_ddq( void );" << endl;
    cout << "extern void Reallocate_ddq( double * user_ddq );" << endl << endl;

    cout << "#define n_gen_accel " << accelerations.size () << endl;
    //cout << "/*----------Accelerations-----------*/" << endl << endl;
    cout.close () ;
}

/*
Method that create a C file for velocities - Definition - Allocation - Initial Values - Free
*/
void System::export_gen_accel_C ( void ) {
    ofstream cout;
    cout.open ( "gen_accel.c" );
    cout << csrc_double ;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
//    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"gen_accel.h\"" << endl;
    cout << endl;

    for ( int i = 0 ; i < accelerations.size () ; i++ )
        cout << "#define " << accelerations[i]-> get_name () << " " << accelerations[i]-> get_value() << endl;

    cout << endl;
    cout << "double * ddq=NULL; " << endl<< endl;

    cout << "void Init_ddq_values ( void )" << endl;
    cout << "{" << endl;

    for ( int i = 0 ; i < accelerations.size () ; i++ )
        cout << "ddq[" << i << "]=" << accelerations[i]-> get_name ()  << ";" << endl;

    cout << "}" << endl << endl;

    cout << "void Init_ddq ( )" << endl;
    cout << "{" << endl;
    cout << " ddq = malloc ( n_gen_accel * sizeof(double) );" << endl;
    cout << " {int i;" << endl;
    cout << "  for ( i = 0 ; i < n_gen_accel ; i++ ) {ddq[i]=0.0;}" << endl;
    cout << " }" << endl;
    cout << "}" << endl << endl;

    cout << "void Done_ddq( ) " << endl;
    cout << "{" << endl;
    cout << "if ( ddq != NULL) " << endl;
    cout << "free ( ddq ); " << endl;
    cout << "ddq = NULL; " << endl;
    cout << "}" << endl<< endl;

    cout << "void Reallocate_ddq( double * user_ddq ) " << endl;
    cout << "{" << endl;
    cout << "ddq = user_ddq; " << endl;
    cout << "}" << endl<< endl;

    cout.close () ;
}

/*
Method that create a header C file to export accelerations
*/
void System::export_gen_accel_vect_def_H ( void ) {
    ofstream cout;
    cout.open ( "gen_accel_vect_def.h" );
    cout << csrc_double ;
    cout << "/*----------gen_accel_vect_def.h lib3D_MEC expoted-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "extern double * ddq;" << endl;
    cout << "#define n_gen_accel " << accelerations.size () << endl;
    cout << "/*----------time-----------*/" << endl << endl;
    cout << "extern double " << get_Time_Symbol () << ";" << endl;
    //cout << "/*----------Accelerations-----------*/" << endl << endl;
    cout.close () ;
}




/*
Method that create a header C file to export accelerations GSL
*/
//~ void System::export_gen_accel_vect_def_H_GSL ( void ) {
    //~ ofstream cout;
    //~ cout.open ( "gen_accel_vect_def.h" );
    //~ cout << csrc_double ;
    //~ cout << "/*----------gen_accel_vect_def.h lib3D_MEC expoted-----------*/" << endl << endl;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ cout << "#include <gsl/gsl_vector.h>" << endl;
    //~ cout << "extern gsl_vector * ddq;" << endl;
    //~ cout << "#define n_gen_accel " << accelerations.size () << endl;
    //~ cout << "/*----------time-----------*/" << endl << endl;
    //~ cout << "extern double " << get_Time_Symbol () << ";" << endl;
//~ //    cout << "/*----------Accelerations-----------*/" << endl << endl;
    //~ cout.close () ;
//~ }

/*
Method that create a C file for initialize accelerations
*/
void System::export_gen_accel_vect_init_C ( void ) {
    ofstream cout;
    cout.open ( "gen_accel_vect_init.c" );
    cout << csrc_double ;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "#include \"gen_accel_vect_def.h\"" << endl;

    for ( int i = 0 ; i < accelerations.size () ; i++ )
        cout << "#define " << accelerations[i]-> get_name () << " " << accelerations[i]-> get_value() << endl;

    cout << "void gen_accel_vect_init ( void )" << endl;
    cout << "{" << endl;
    cout << "  if ( n_gen_accel > 0 )" << endl;
    cout << "  {" << endl;
    cout << "  ddq = malloc( n_gen_accel * sizeof(double) );" << endl;

    for ( int i = 0 ; i < accelerations.size () ; i++ )
        cout << "ddq[" << i << "]=" << accelerations[i]-> get_name ()  << ";" << endl;

    cout << "  }" << endl;
    cout << "}" << endl;
    cout.close () ;
}

/*
Method that create a C file for initialize accelerations GSL
*/
//~ void System::export_gen_accel_vect_init_C_GSL ( void ) {
    //~ ofstream cout;
    //~ cout.open ( "gen_accel_vect_init.c" );
    //~ cout << csrc_double ;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ cout << "#include <gsl/gsl_vector.h>" << endl;
    //~ cout << "#include \"var_def.h\"" << endl;
    //~ cout << "#include \"gen_accel_vect_def.h\"" << endl;
//~ 
    //~ for ( int i = 0 ; i < accelerations.size () ; i++ )
        //~ cout << "#define " << accelerations[i]-> get_name () << " " << accelerations[i]-> get_value() << endl;
//~ 
    //~ cout << "void gen_accel_vect_init ( void )" << endl;
    //~ cout << "{" << endl;
    //~ cout << "  if ( n_gen_accel > 0 )" << endl;
    //~ cout << "  {" << endl;
    //~ cout << "  ddq = gsl_vector_alloc ( n_gen_accel );" << endl;
//~ 
    //~ for ( int i = 0 ; i < accelerations.size () ; i++ )
        //~ cout << "gsl_vector_set ( ddq , " << i << " , " << accelerations[i]-> get_name () << " );" << endl;
//~ 
    //~ cout << "  }" << endl;
    //~ cout << "}" << endl;
    //~ cout.close () ;
//~ }

/*
=========================================================================================================================
Methods to export auxiliar coordinates, velcities and accelerations
=========================================================================================================================
*/

/*
Method that create a header C file to export auxiliar coordinates
*/
void System::export_gen_auxcoord_H ( void ){
    ofstream cout;
    cout.open ( "gen_auxcoord.h" );
    cout << csrc_double ;
    cout << "/*----------gen_auxcoord.h lib3D_MEC expoted-----------*/" << endl << endl;
    cout << "extern double * qaux;" << endl;
    cout << "extern void Init_qaux_values ( void );" << endl;
    cout << "extern void Init_qaux ( void );" << endl;
    cout << "extern void Done_qaux( void  );" << endl;
    cout << "extern void Reallocate_qaux( double * user_qaux );" << endl << endl;

    cout << "#define n_gen_auxcoord " << aux_coordinates.size () << endl;
//    cout << "/*----------Coordinates-----------*/" << endl << endl;
    cout.close () ;
}

/*
Method that create a C file for auxliar coordinates - Definition - Allocation - Initial Values - Free
*/
void System::export_gen_auxcoord_C ( void ) {
    ofstream cout;
    cout.open ( "gen_auxcoord.c" );
    cout << csrc_double ;
    cout << "#include <stdlib.h>" << endl;
    cout << "#include \"gen_auxcoord.h\"" << endl;
    cout << endl;
    for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
        cout << "#define " << aux_coordinates[i]-> get_name () << " " << aux_coordinates[i]-> get_value() << endl;

    cout << endl;
    cout << "double * qaux=NULL; " << endl<< endl;

    cout << "void Init_qaux_values ( void )" << endl;
    cout << "{" << endl;
    for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
        cout << "qaux[" << i << "]=" << aux_coordinates[i]-> get_name () << ";" << endl;

    cout << "}" << endl << endl;

    cout << "void Init_qaux ( )" << endl;
    cout << "{" << endl;
    cout << " qaux = malloc ( n_gen_auxcoord * sizeof(double) );" << endl;
    cout << " {int i;" << endl;
    cout << "  for ( i = 0 ; i < n_gen_auxcoord ; i++ ) {qaux[i]=0.0;}" << endl;
    cout << " }" << endl;
    cout << "}" << endl << endl;

    cout << "void Done_qaux( ) " << endl;
    cout << "{" << endl;
    cout << "if ( qaux != NULL) " << endl;
    cout << "free ( qaux ); " << endl;
    cout << "qaux = NULL; " << endl;
    cout << "}" << endl<< endl;

    cout << "void Reallocate_qaux( double * user_qaux ) " << endl;
    cout << "{" << endl;
    cout << "qaux = user_qaux; " << endl;
    cout << "}" << endl<< endl;

    cout.close () ;
}

/*
Method that create a header C file to export velocities
*/
void System::export_gen_auxvel_H ( void ){
    ofstream cout;
    cout.open ( "gen_auxvel.h" );
    cout << csrc_double ;
    cout << "/*----------gen_auxvel.h lib3D_MEC expoted-----------*/" << endl << endl;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "extern double * dqaux;" << endl;
    cout << "extern void Init_dqaux_values ( void );" << endl;
    cout << "extern void Init_dqaux ( void  );" << endl;
    cout << "extern void Done_dqaux( void  );" << endl;
    cout << "extern void Reallocate_dqaux( double * user_dqaux );" << endl << endl;

    cout << "#define n_gen_auxvel " << aux_velocities.size () << endl;
//    cout << "/*----------Velocities-----------*/" << endl << endl;
    cout.close () ;
}

/*
Method that create a C file for velocities - Definition - Allocation - Initial Values - Free
*/
void System::export_gen_auxvel_C ( void ) {
    ofstream cout;
    cout.open ( "gen_auxvel.c" );
    cout << csrc_double ;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
//    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"gen_auxvel.h\"" << endl;
    cout << endl;

    for ( int i = 0 ; i < aux_velocities.size () ; i++ )
        cout << "#define " << aux_velocities[i]-> get_name () << " " << aux_velocities[i]-> get_value() << endl;

    cout << endl;
    cout << "double * dqaux=NULL; " << endl;// << endl;

    cout << "void Init_dqaux_values ( void )" << endl;
    cout << "{" << endl;

    for ( int i = 0 ; i < aux_velocities.size () ; i++ )
        cout << "dqaux[" << i << "]=" << aux_velocities[i]-> get_name () << ";" << endl;

    cout << "}" << endl << endl;

    cout << "void Init_dqaux ( )" << endl;
    cout << "{" << endl;
    cout << " dqaux = malloc ( n_gen_auxvel * sizeof(double) );" << endl;
    cout << " {int i;" << endl;
    cout << "  for ( i = 0 ; i < n_gen_auxvel ; i++ ) {dqaux[i]=0.0;}" << endl;
    cout << " }" << endl;
    cout << "}" << endl << endl;

    cout << "void Done_dqaux( ) " << endl;
    cout << "{" << endl;
    cout << "if ( dqaux != NULL) " << endl;
    cout << "free ( dqaux ); " << endl;
    cout << "dqaux = NULL; " << endl;
    cout << "}" << endl<< endl;

    cout << "void Reallocate_dqaux( double * user_dqaux ) " << endl;
    cout << "{" << endl;
    cout << "dqaux = user_dqaux; " << endl;
    cout << "}" << endl<< endl;

    cout.close () ;
}
/*
Method that create a header C file to export accelerations
*/
void System::export_gen_auxaccel_H ( void ){
    ofstream cout;
    cout.open ( "gen_auxaccel.h" );
    cout << csrc_double ;
    cout << "/*----------gen_auxaccel.h lib3D_MEC expoted-----------*/" << endl;// << endl;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "extern double * ddqaux;" << endl;
    cout << "extern void Init_ddqaux_values ( void );" << endl;
    cout << "extern void Init_ddqaux ( void );" << endl;
    cout << "extern void Done_ddqaux( void );" << endl;
    cout << "extern void Reallocate_ddqaux( double * user_ddqaux );" << endl << endl;

    cout << "#define n_gen_auxaccel " << aux_accelerations.size () << endl;
    //cout << "/*----------Accelerations-----------*/" << endl << endl;
    cout.close () ;
}

/*
Method that create a C file for velocities - Definition - Allocation - Initial Values - Free
*/
void System::export_gen_auxaccel_C ( void ) {
    ofstream cout;
    cout.open ( "gen_auxaccel.c" );
    cout << csrc_double ;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
//    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"gen_auxaccel.h\"" << endl;
    cout << endl;

    for ( int i = 0 ; i < aux_accelerations.size () ; i++ )
        cout << "#define " << aux_accelerations[i]-> get_name () << " " << aux_accelerations[i]-> get_value() << endl;

    cout << endl;
    cout << "double * ddqaux=NULL; " << endl<< endl;

    cout << "void Init_ddqaux_values ( void )" << endl;
    cout << "{" << endl;

    for ( int i = 0 ; i < aux_accelerations.size () ; i++ )
        cout << "ddqaux[" << i << "]=" << aux_accelerations[i]-> get_name ()  << ";" << endl;

    cout << "}" << endl << endl;

    cout << "void Init_ddqaux ( )" << endl;
    cout << "{" << endl;
    cout << " ddqaux = malloc ( n_gen_auxaccel * sizeof(double) );" << endl;
    cout << " {int i;" << endl;
    cout << "  for ( i = 0 ; i < n_gen_auxaccel ; i++ ) {ddqaux[i]=0.0;}" << endl;
    cout << " }" << endl;
    cout << "}" << endl << endl;

    cout << "void Done_ddqaux( ) " << endl;
    cout << "{" << endl;
    cout << "if ( ddqaux != NULL) " << endl;
    cout << "free ( ddqaux ); " << endl;
    cout << "ddqaux = NULL; " << endl;
    cout << "}" << endl<< endl;

    cout << "void Reallocate_ddqaux( double * user_ddqaux ) " << endl;
    cout << "{" << endl;
    cout << "ddqaux = user_ddqaux; " << endl;
    cout << "}" << endl<< endl;

    cout.close () ;
}

/*
=========================================================================================================================

=========================================================================================================================
*/


/*
Method that create a header C file to export parameters
*/
void System::export_param_vect_def_H ( void ) {
    ofstream cout;
    cout.open ( "param_vect_def.h" );
    cout << csrc_double ;
    cout << "/*----------param_vect_def.h lib3D_MEC expoted-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "extern double * param;" << endl;
    cout << "#define n_param " << parameters.size () << endl;
    cout << "/*----------time-----------*/" << endl << endl;
    cout << "extern double " << get_Time_Symbol () << ";" << endl;
    cout << "/*----------Parameters-----------*/" << endl << endl;
    cout.close () ;
}


/*
Method that create a C file for initialize parameters
*/
void System::export_param_vect_init_C ( void ) {
    ofstream cout;
    cout.open ( "param_vect_init.c" );
    cout << csrc_double ;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "#include \"param_vect_def.h\"" << endl;
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "#define " << parameters[i]-> get_name () << " " << parameters[i]-> get_value() << endl;

    cout << "void param_vect_init ( void )" << endl;
    cout << "{" << endl;
    cout << "  if ( n_param > 0 )" << endl;
    cout << "  {" << endl;
    cout << "  param = malloc( n_param * sizeof(double) );" << endl;
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "param[" << i << "]=" << parameters[i]-> get_name ()  << ";" << endl;

    cout << "  }" << endl;
    cout << "}" << endl;
    cout.close () ;
}

/*
Method that create a header C file to export parameters
*/
void System::export_param_H ( void ) {
    ofstream cout;
    cout.open ( "param.h" );
    cout << csrc_double ;
    cout << "/*----------param.h lib3D_MEC expoted-----------*/" << endl << endl;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "extern double * param;" << endl;
    cout << "extern void Init_param_values ( void );" << endl;
    cout << "extern void Init_param ( void );" << endl;
    cout << "extern void Done_param( void );" << endl;
    cout << "extern void Reallocate_param( double * user_param );" << endl << endl;

    cout << "#define n_param " << parameters.size () << endl;
//    cout << "/*----------Parameters-----------*/" << endl << endl;
    cout.close () ;
}


/*
Method that create a C file for initialize parameters
*/
void System::export_param_C ( void ) {
    ofstream cout;
    cout.open ( "param.c" );
    cout << csrc_double ;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
//    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"param.h\"" << endl;
    cout << endl;
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "#define " << parameters[i]-> get_name () << " " << parameters[i]-> get_value() << endl;

    cout << endl;
    cout << "double * param=NULL; " << endl<< endl;

    cout << "void Init_param_values ( void )" << endl;
    cout << "{" << endl;
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "param[" << i << "]=" << parameters[i]-> get_name ()  << ";" << endl;

    cout << "}" << endl << endl;

    cout << "void Init_param ( )" << endl;
    cout << "{" << endl;
    cout << " param = malloc ( n_param * sizeof(double) );" << endl;
    cout << " {int i;" << endl;
    cout << "  for ( i = 0 ; i < n_param ; i++ ) {param[i]=0.0;}" << endl;
    cout << " }" << endl;
    cout << "}" << endl << endl;

    cout << "void Done_param( ) " << endl;
    cout << "{" << endl;
    cout << "if ( param != NULL) " << endl;
    cout << "free ( param ); " << endl;
    cout << "param = NULL; " << endl;
    cout << "}" << endl<< endl;

    cout << "void Reallocate_param( double * user_param ) " << endl;
    cout << "{" << endl;
    cout << "param = user_param; " << endl;
    cout << "}" << endl<< endl;

    cout.close () ;
}

/*
Method that creates a C header  file to export inputs
*/
void System::export_inputs_vect_def_H ( void ) {
    ofstream cout;
    cout.open ( "inputs_vect_def.h" );
    cout << csrc_double ;
    cout << "/*----------inputs_vect_def.h lib3D_MEC exported-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "extern double * inputs;" << endl;
    cout << "#define n_inputs " << inputs.size () << endl;
    cout << "/*----------time-----------*/" << endl << endl;
    cout << "extern double " << get_Time_Symbol () << ";" << endl;
    cout << "/*----------inputs-----------*/" << endl << endl;
    cout.close () ;
}

/*
Method that creates a C file to initialize inputs
*/
void System::export_inputs_vect_init_C ( void ) {
    ofstream cout;
    cout.open ( "inputs_vect_init.c" );
    cout << csrc_double ;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "#include \"inputs_vect_def.h\"" << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "#define " << inputs[i]-> get_name () << " " << inputs[i]-> get_value() << endl;
        
    cout << "void inputs_vect_init ( void )" << endl;
    cout << "{" << endl;
    cout << "  if ( n_inputs > 0 )" << endl;
    cout << "  {" << endl;
    cout << "  inputs = malloc ( n_inputs * sizeof(double) );" << endl;

    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "inputs[" << i << "]=" << inputs[i]-> get_name ()  << ";" << endl;

    cout << "  }" << endl;
    cout << "}" << endl;
    cout.close () ;
}

/*
Method that creates a C header  file to export inputs
*/
void System::export_inputs_H ( void ) {
    ofstream cout;
    cout.open ( "inputs.h" );
    cout << csrc_double ;
    cout << "/*----------inputs.h lib3D_MEC exported-----------*/" << endl << endl;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "extern double * inputs;" << endl;
    cout << "extern void Init_inputs_values ( void );" << endl;
    cout << "extern void Init_inputs ( void  );" << endl;
    cout << "extern void Done_inputs( void );" << endl;
    cout << "extern void Reallocate_inputs( double * user_inputs );" << endl << endl;


    cout << "#define n_inputs " << inputs.size () << endl;
//    cout << "/*----------inputs-----------*/" << endl << endl;
    cout.close () ;
}

/*
Method that creates a C file to initialize inputs
*/
void System::export_inputs_C ( void ) {
    ofstream cout;
    cout.open ( "inputs.c" );
    cout << csrc_double ;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
//    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"inputs.h\"" << endl;
    cout << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "#define " << inputs[i]-> get_name () << " " << inputs[i]-> get_value() << endl;

    cout << endl;
    cout << "double * inputs=NULL; " << endl<< endl;

    cout << "void Init_inputs_values ( void )" << endl;
    cout << "{" << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "inputs[" << i << "]=" << inputs[i]-> get_name ()  << ";" << endl;
        
    cout << "}" << endl << endl;

    cout << "void Init_inputs ( )" << endl;
    cout << "{" << endl;
    cout << " inputs = malloc ( n_inputs * sizeof(double) );" << endl;
    cout << " {int i;" << endl;
    cout << "  for ( i = 0 ; i < n_inputs ; i++ ) {inputs[i]=0.0;}" << endl;
    cout << " }" << endl;
    cout << "}" << endl << endl;

    cout << "void Done_inputs( ) " << endl;
    cout << "{" << endl;
    cout << "if ( inputs != NULL) " << endl;
    cout << "free ( inputs ); " << endl;
    cout << "inputs = NULL; " << endl;
    cout << "}" << endl<< endl;

    cout << "void Reallocate_inputs( double * user_inputs ) " << endl;
    cout << "{" << endl;
    cout << "inputs = user_inputs; " << endl;
    cout << "}" << endl<< endl;

    cout.close () ;
}

/*
Method that creates a C header  file to export unknowns
*/
void System::export_unknowns_H ( void ) {
    ofstream cout;
    cout.open ( "unknowns.h" );
    cout << csrc_double ;
    cout << "/*----------unknowns.h lib3D_MEC expoted-----------*/" << endl << endl;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "extern double * unknowns;" << endl;
    cout << "extern void Init_unknowns_values ( void );" << endl;
    cout << "extern void Init_unknowns ( void );" << endl;
    cout << "extern void Done_unknowns( void );" << endl;
    cout << "extern void Reallocate_unknowns( double * user_unknowns );" << endl << endl;

    cout << "#define n_unknowns " << unknowns.size () << endl;
//    cout << "/*----------Unknowns-----------*/" << endl << endl;
    cout.close () ;
}

/*
Method that creates a C header  file to export unknowns
*/
void System::export_unknowns_vect_def_H ( void ) {
    ofstream cout;
    cout.open ( "unknowns_vect_def.h" );
    cout << csrc_double ;
    cout << "/*----------unknowns_vect_def.h lib3D_MEC expoted-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "extern double * unknowns;" << endl;
    cout << "#define n_unknowns " << unknowns.size () << endl;
    cout << "/*----------time-----------*/" << endl << endl;
    cout << "extern double " << get_Time_Symbol () << ";" << endl;
    cout << "/*----------Unknowns-----------*/" << endl << endl;
    cout.close () ;
}


/*
Method that creates a header C file to export unknowns GSL
*/
//~ void System::export_unknowns_vect_def_H_GSL ( void ) {
    //~ ofstream cout;
    //~ cout.open ( "unknowns_vect_def.h" );
    //~ cout << csrc_double ;
    //~ cout << "/*----------unknowns_vect_def.h lib3D_MEC exported-----------*/" << endl << endl;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ cout << "#include <gsl/gsl_vector.h>" << endl;
    //~ cout << "extern gsl_vector * unknowns;" << endl;
    //~ cout << "#define n_unknowns " << unknowns.size () << endl;
    //~ cout << "/*----------time-----------*/" << endl << endl;
    //~ cout << "extern double " << get_Time_Symbol () << ";" << endl;
    //~ cout << "/*----------Unknowns-----------*/" << endl << endl;
    //~ for ( int i = 0 ; i < unknowns.size () ; i++ )
        //~ cout << "extern double " << unknowns[i]-> get_name () << ";" << endl;
    //~ cout.close () ;
//~ }

/*
Method that creates a C file to initialize unknowns
*/
void System::export_unknowns_C ( void ) {
    ofstream cout;
    cout.open ( "unknowns.c" );
    cout << csrc_double ;
//    cout << "#include <stdio.h>" << endl;
//    cout << "#include <math.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
//    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"unknowns.h\"" << endl;
    cout << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "#define " << unknowns[i]-> get_name () << " " << unknowns[i]-> get_value() << endl;

    cout << endl;
    cout << "double * unknowns=NULL; " << endl<< endl;

    cout << "void Init_unknowns_values ( void )" << endl;
    cout << "{" << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "unknowns[" << i << "]=" << unknowns[i]-> get_name ()  << ";" << endl;
    cout << "}" << endl << endl;

    cout << "void Init_unknowns ( )" << endl;
    cout << "{" << endl;
    cout << "  unknowns = malloc ( n_unknowns * sizeof(double) );" << endl;
    cout << " {int i;" << endl;
    cout << "  for ( i = 0 ; i < n_unknowns ; i++ ) {unknowns[i]=0.0;}" << endl;
    cout << " }" << endl;
    cout << "}" << endl << endl;

		cout << "void Done_unknowns( ) " << endl;
		cout << "{" << endl;
		cout << "if ( unknowns != NULL) " << endl;
		cout << "free ( unknowns ); " << endl;
		cout << "unknowns = NULL; " << endl;
		cout << "}" << endl<< endl;

		cout << "void Reallocate_unknowns( double * user_unknowns ) " << endl;
		cout << "{" << endl;
		cout << "unknowns = user_unknowns; " << endl;
		cout << "}" << endl<< endl;

    cout.close () ;
}

/*
Method that creates a C file to initialize unknowns
*/
void System::export_unknowns_vect_init_C ( void ) {
    ofstream cout;
    cout.open ( "unknowns_vect_init.c" );
    cout << csrc_double ;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "#include \"unknowns_vect_def.h\"" << endl;
    cout << "#include <math.h>" << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "#define " << unknowns[i]-> get_name () << " " << unknowns[i]-> get_value() << endl;
    cout << "void unknowns_vect_init ( void )" << endl;
    cout << "{" << endl;
    cout << "  if ( n_unknowns > 0 )" << endl;
    cout << "  {" << endl;
    cout << "  unknowns = malloc ( n_unknowns * sizeof(double) );" << endl;

    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "unknowns[" << i << "]=" << unknowns[i]-> get_name ()  << ";" << endl;

    cout << "  }" << endl;
    cout << "}" << endl;
    cout.close () ;
}


/*
Method that create a C file for initialize unknowns GSL
*/
//~ void System::export_unknowns_vect_init_C_GSL ( void ) {
    //~ ofstream cout;
    //~ cout.open ( "unknowns_vect_init.c" );
    //~ cout << csrc_double ;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <gsl/gsl_vector.h>" << endl;
    //~ cout << "#include \"var_def.h\"" << endl;
    //~ cout << "#include \"unknowns_vect_def.h\"" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ for ( int i = 0 ; i < unknowns.size () ; i++ )
        //~ cout << "#define " << unknowns[i]-> get_name () << " " << unknowns[i]-> get_value() << endl;
    //~ cout << "void unknowns_vect_init ( void )" << endl;
    //~ cout << "{" << endl;
    //~ cout << "  if ( n_unknowns > 0 )" << endl;
    //~ cout << "  {" << endl;
    //~ cout << "  unknowns = gsl_vector_alloc ( n_unknowns );" << endl;
    //~ cout << "  gsl_vector_set_zero ( unknowns );" << endl;
    //~ cout << "  }" << endl;
    //~ cout << "}" << endl;
    //~ cout.close () ;
//~ }


/*
Method that create a C file
*/
void System::export_Column_Matrix_C ( string function_name , string vector_name , Matrix Col_Matrix , lst Col_Matrix_atom_list ) {
    ofstream cout;
    cout.open ( ( function_name+".c" ).c_str () );
    cout << csrc_double;
    cout << "/*----------"<< function_name <<".c lib3D_MEC exported-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "#include \"gen_coord_vect_def.h\"" << endl;
    cout << "#include \"gen_vel_vect_def.h\"" << endl;
    cout << "#include \"gen_accel_vect_def.h\"" << endl;
    cout << "#include \"param_vect_def.h\"" << endl;
    cout << "#include \"unknowns_vect_def.h\"" << endl;
    cout << "#include \"inputs_vect_def.h\"" << endl;
    cout << "#include \"" << function_name << ".h\"" << endl;
    cout << "#include \"step.h\"" << endl;
    cout << "#include <math.h>" << endl;

    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "#define " << coordinates[i]-> get_name () << " q[ " << i << " ]" << endl;
    for ( int i = 0 ; i < velocities.size () ; i++ )
        cout << "#define " << velocities[i]-> get_name () << " dq[ "<< i << " ]" << endl;
    for ( int i = 0 ; i < accelerations.size () ; i++ )
        cout << "#define " << accelerations[i]-> get_name () << " ddq[ " << i << " ]" << endl;
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "#define " << parameters[i]-> get_name () << " param[ " << i << " ]" << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "#define " << unknowns[i]-> get_name () << " unknowns[ " << i << " ]" << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "#define " << inputs[i]-> get_name () << " inputs[ " << i << " ]" << endl;

    if ( atomization == YES ) {
        lst aux_Col_Matrix_atom_list = Col_Matrix_atom_list;
        //aux_Col_Matrix_atom_list = Col_Matrix_atom_list;
        atom_list ( Col_Matrix , aux_Col_Matrix_atom_list );
        for ( int i = 0 ; i < aux_Col_Matrix_atom_list.nops () ; ++i )
            cout << "extern double " << aux_Col_Matrix_atom_list.op ( i )<< ";" << endl;
    }

    if ( 0 )
        cout << "double * " << function_name << " ( double * " << vector_name << " )" << endl;
    else{
        cout << "double * " << vector_name << " = NULL;" << endl;
        cout << "double * " << function_name << " ()" << endl;
    }
    cout << "{" << endl;
    cout << "if ( " << vector_name << " == NULL )" << endl;
    cout << " {" << endl;
    cout << "    " << vector_name << " = malloc ( "<< function_name << "_n_comp * sizeof(double));" << endl;

    vector < int > vector_aux_one;
    vector < int > vector_aux_two;

    lst Col_Matrix_atom_expression_list;
    atom_expression_list ( Col_Matrix_atom_list , Col_Matrix_atom_expression_list );

    if ( atomization == YES )
        for ( int i = 0 ; i < Col_Matrix_atom_list.nops () ; i++ )
            if ( dt ( Col_Matrix_atom_list.op ( i )) == true )
                cout << "/*constant*/ " << Col_Matrix_atom_list.op ( i ) << " = " << Col_Matrix_atom_expression_list.op ( i )<< ";" << endl;
            else
                vector_aux_one.push_back ( i );

    for ( int i = 0 ; i < Col_Matrix.rows () ; i++ )
        if ( dt ( Col_Matrix ( i , 0 ) ) == true )
            cout << vector_name << "[" << i <<"]= " << Col_Matrix ( i , 0 )<< " ;" << endl;
        else
            vector_aux_two.push_back ( i );

    cout << " }" << endl;


    if ( atomization == YES )
        for ( int i = 0 ; i < vector_aux_one.size () ; i++ )
            cout << " " << Col_Matrix_atom_list.op ( vector_aux_one.at ( i ) ) << " = " << Col_Matrix_atom_expression_list.op ( vector_aux_one.at ( i ) )<< ";" << endl;

    for ( int i = 0 ; i < vector_aux_two.size () ; i++ )
    /*  cout << "gsl_vector_set ( " << vector_name << " , " << vector_aux_two.at ( i ) <<" , " << Col_Matrix ( vector_aux_two.at ( i ) , 0 )<< " );" << endl;*/
        cout << vector_name << "[" << vector_aux_two.at ( i ) <<"]=" << Col_Matrix ( vector_aux_two.at ( i ) , 0 )<< " ;" << endl;

    cout << "return " << vector_name << ";" << endl;
    cout << "}" << endl;
    cout.close () ;
    cout.open ( ( function_name+".h" ).c_str () );
    if ( 0 )
    cout << "extern double * " << function_name << " ( double * " << vector_name << " );" << endl;
    else {
        cout << "#define " << function_name << "_n_comp " << Col_Matrix.rows () << endl;
        cout << "extern     double * " << vector_name << ";" << endl;
        cout << "extern     double * " << function_name << " () ;" << endl;
    }
    cout.close () ;
}

/*
Method that create a C file GSL
*/
//~ void System::export_Column_Matrix_C_GSL ( string function_name , string vector_name , Matrix Col_Matrix , lst Col_Matrix_atom_list ) {
    //~ ofstream cout;
    //~ cout.open ( ( function_name+".c" ).c_str () );
    //~ cout << csrc_double;
    //~ cout << "/*----------"<< function_name <<".c lib3D_MEC exported----------- */" << endl << endl;
    //~ cout << "/*For increased velocity use GSL HAVE_INLINE and GSL_RANGE_CHECK_OFF preprocesor directive to compile:*/" << endl << endl;
    //~ cout << "/* gcc -DHAVE_INLINE = 1 -DGSL_RANGE_CHECK_OFF = 1 ... --- */" << endl << endl;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <gsl/gsl_vector.h>" << endl;
    //~ cout << "#include \"var_def.h\"" << endl;
    //~ cout << "#include \"gen_coord_vect_def.h\"" << endl;
    //~ cout << "#include \"gen_vel_vect_def.h\"" << endl;
    //~ cout << "#include \"gen_accel_vect_def.h\"" << endl;
    //~ cout << "#include \"unknowns_vect_def.h\"" << endl;
    //~ cout << "#include \"inputs_vect_def.h\"" << endl;
    //~ cout << "#include \""<< function_name << ".h\"" << endl;
    //~ cout << "#include \"step.h\"" << endl;
    //~ cout << "#include <math.h>" << endl;
//~ 
    //~ for ( int i = 0 ; i < coordinates.size () ; i++ )
        //~ cout << "#define " << coordinates[i]-> get_name () << " gsl_vector_get ( q , " << i << " )" << endl;
    //~ for ( int i = 0 ; i < velocities.size () ; i++ )
        //~ cout << "#define " << velocities[i]-> get_name () << " gsl_vector_get ( dq , " << i << " )" << endl;
    //~ for ( int i = 0 ; i < accelerations.size () ; i++ )
        //~ cout << "#define " << accelerations[i]-> get_name () << " gsl_vector_get ( ddq , " << i << " )" << endl;
    //~ for ( int i = 0 ; i < unknowns.size () ; i++ )
        //~ cout << "#define " << unknowns[i]-> get_name () << " gsl_vector_get ( unknowns , " << i << " )" << endl;
    //~ for ( int i = 0 ; i < inputs.size () ; i++ )
        //~ cout << "#define " << inputs[i]-> get_name () << " gsl_vector_get ( inputs , " << i << " )" << endl;
//~ 
    //~ if ( atomization == YES ) {
        //~ lst aux_Col_Matrix_atom_list;
        //~ aux_Col_Matrix_atom_list = Col_Matrix_atom_list;
        //~ atom_list ( Col_Matrix , aux_Col_Matrix_atom_list );
        //~ for ( int i = 0 ; i < aux_Col_Matrix_atom_list.nops () ; ++i )
            //~ cout << "extern double " << aux_Col_Matrix_atom_list.op ( i )<< ";" << endl;
    //~ }
//~ 
    //~ if ( 0 )
        //~ cout << "gsl_vector * " << function_name << " ( gsl_vector * " << vector_name << " )" << endl;
    //~ else{
        //~ cout << "gsl_vector * " << vector_name << " = NULL;" << endl;
        //~ cout << "gsl_vector * " << function_name << "()" << endl;
    //~ }
    //~ cout << "{" << endl;
    //~ cout << "if ( " << vector_name << " == NULL )" << endl;
    //~ cout << " {" << endl;
    //~ cout << "    " << vector_name << " = gsl_vector_alloc ( " << function_name << "_n_comp );" << endl;
//~ 
    //~ vector < int > vector_aux_one;
    //~ vector < int > vector_aux_two;
//~ 
    //~ lst Col_Matrix_atom_expression_list;
    //~ atom_expression_list ( Col_Matrix_atom_list , Col_Matrix_atom_expression_list );
//~ 
    //~ if ( atomization == YES )
        //~ for ( int i = 0 ; i < Col_Matrix_atom_list.nops () ; i++ )
            //~ if ( dt ( Col_Matrix_atom_list.op ( i )) == true )
                //~ cout << "/*constant*/ " << Col_Matrix_atom_list.op ( i ) << " = " << Col_Matrix_atom_expression_list.op ( i )<< ";" << endl;
            //~ else
                //~ vector_aux_one.push_back ( i );
//~ 
    //~ for ( int i = 0 ; i < Col_Matrix.rows () ; i++ )
        //~ if ( dt ( Col_Matrix ( i , 0 ) ) == true )
            //~ cout << "gsl_vector_set ( " << vector_name << " , " << i <<" , " << Col_Matrix ( i , 0 )<< " );" << endl;
        //~ else
            //~ vector_aux_two.push_back ( i );
//~ 
    //~ cout << " }" << endl;
//~ 
//~ 
    //~ if ( atomization == YES )
        //~ for ( int i = 0 ; i < vector_aux_one.size () ; i++ )
            //~ cout << " " << Col_Matrix_atom_list.op ( vector_aux_one.at ( i ) ) << " = " << Col_Matrix_atom_expression_list.op ( vector_aux_one.at ( i ) )<< ";" << endl;
//~ 
    //~ for ( int i = 0 ; i < vector_aux_two.size () ; i++ )
        //~ cout << "gsl_vector_set ( " << vector_name << " , " << vector_aux_two.at ( i ) <<" , " << Col_Matrix ( vector_aux_two.at ( i ) , 0 )<< " );" << endl;
//~ 
    //~ cout << "return " << vector_name << ";" << endl;
    //~ cout << "}" << endl;
    //~ cout.close () ;
    //~ cout.open ( ( function_name+".h" ).c_str () );
    //~ if ( 0 )
    //~ cout << "extern gsl_vector * " << function_name << " ( gsl_vector * " << vector_name << " );" << endl;
    //~ else {
        //~ cout << "#define " << function_name << "_n_comp " << Col_Matrix.rows () << endl;
        //~ cout << "extern     gsl_vector * " << vector_name << ";" << endl;
        //~ cout << "extern     gsl_vector * " << function_name << "() ;" << endl;
    //~ }
    //~ cout.close () ;
//~ }


/*
Method that create a C file
*/
void System::export_Matrix_C ( string function_name , string matrix_name , Matrix Matrix , lst Matrix_atom_list ) {
    ofstream cout;
    cout.open ( ( function_name+".c" ).c_str () );
    cout << csrc_double ;
    cout << "/*----------"<< function_name <<".c lib3D_MEC exported-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <stdlib.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "#include \"gen_coord_vect_def.h\"" << endl;
    cout << "#include \"gen_vel_vect_def.h\"" << endl;
    cout << "#include \"gen_accel_vect_def.h\"" << endl;
    cout << "#include \"param_vect_def.h\"" << endl;
    cout << "#include \"unknowns_vect_def.h\"" << endl;
    cout << "#include \"inputs_vect_def.h\"" << endl;
    cout << "#include \"" << function_name << ".h\"" << endl;
    cout << "#include \"step.h\"" << endl;
    cout << "#include <math.h>" << endl;
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "#define " << coordinates[i]-> get_name () << " q[ " << i << " ]" << endl;
    for ( int i = 0 ; i < velocities.size () ; i++ )
        cout << "#define " << velocities[i]-> get_name () << " dq[ " << i << " ]" << endl;
    for ( int i = 0 ; i < accelerations.size () ; i++ )
        cout << "#define " << accelerations[i]-> get_name () << " ddq[ " << i << " ]" << endl;
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "#define " << parameters[i]-> get_name () << " param[ " << i << " ]" << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "#define " << unknowns[i]-> get_name () << " unknowns[ " << i << " ]" << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "#define " << inputs[i]-> get_name () << " inputs[ " << i << " ]" << endl;

    if ( atomization == YES ) {
        lst aux_Matrix_atom_list = Matrix_atom_list;
        //aux_Matrix_atom_list = Matrix_atom_list;
        atom_list ( Matrix , aux_Matrix_atom_list );
        for ( int i = 0; i < aux_Matrix_atom_list.nops () ; ++i )
            cout << "extern double " << aux_Matrix_atom_list.op ( i )<< ";" << endl;
    }

    if ( 0 )
        cout << "double * " << function_name << " ( double * " << matrix_name << " )" << endl;
    else {
        cout << "double * " << matrix_name << " = NULL;" << endl;
        cout << "double * " << function_name << " ()" << endl;
    }

    cout << "{" << endl;
    cout << "if ( " << matrix_name << " == NULL )" << endl;
    cout << " {" << endl;
    cout << "    " << matrix_name << " = malloc ( "<< function_name << "_n_rows * "<< function_name << "_n_cols * sizeof(double) );" << endl;
    cout << "  {int i;" << endl;
    cout << "  for ( i = 0 ; i < "<< function_name << "_n_rows * "<< function_name << "_n_cols ; i++ ) {" << matrix_name << "[i]=0.0;}" << endl;
    cout << "  }" << endl;
    vector < int > vector_aux_one;
    vector < int > vector_aux_two;
    vector < int > vector_aux_three;

    lst Matrix_atom_expression_list;
    atom_expression_list ( Matrix_atom_list , Matrix_atom_expression_list );

    if ( atomization == YES )
        for ( int i = 0 ; i < Matrix_atom_list.nops () ; i++ )
            if ( dt ( Matrix_atom_list.op ( i ) ) == true )
                cout << "/*constant*/ " << Matrix_atom_list.op ( i ) << " = " << Matrix_atom_expression_list.op ( i )<< ";" << endl;
            else
                vector_aux_one.push_back ( i );

    int k=0;
    /* Matrix written in Column-major order */
    for ( int j = 0 ; j < Matrix.cols () ; j++ )
        for ( int i = 0 ; i < Matrix.rows () ; i++ )
            if ( dt ( Matrix ( i , j ) ) == true ){
/*              cout << "gsl_matrix_set ( " << matrix_name << " , " << i <<" , " << j << " , " << Matrix ( i , j )<< " );" << endl; */
                cout << matrix_name << "[" << k << "]=" << Matrix ( i , j ) << ";" << endl;
                k++;}
            else{
                /* FIX funcionan las plantillas cuando el vector es double ?*/
                vector_aux_two.push_back ( i );
                vector_aux_three.push_back ( j );
            }

    cout << " }" << endl;


    if ( atomization == YES )
        for ( int i = 0 ; i < vector_aux_one.size () ; i++ )
            cout << " " << Matrix_atom_list.op ( vector_aux_one.at ( i ) ) << " = " << Matrix_atom_expression_list.op ( vector_aux_one.at ( i ) )<< ";" << endl;


/*  for ( int i = 0 ; i < vector_aux_two.size () ; i++ )
            cout << "gsl_matrix_set ( " << matrix_name << " , " << vector_aux_two.at ( i ) <<" , " << vector_aux_three.at ( i ) << " , " << Matrix ( vector_aux_two.at ( i ) , vector_aux_three.at ( i ) )<< " );" << endl; */

    /* Matrix written in Column-major order */
    for ( int i = 0 ; i < vector_aux_two.size () ; i++ )
            cout << matrix_name << "[" << vector_aux_two.at ( i ) + Matrix.rows ()*vector_aux_three.at ( i ) <<"]=" << Matrix ( vector_aux_two.at ( i ) , vector_aux_three.at ( i ) ) << ";" << endl;


    cout << "return " << matrix_name << ";" << endl;
    cout << "}" << endl;
    cout.close () ;
    cout.open ( ( function_name+".h" ).c_str () );
    if ( 0 )
        cout << "extern double * " << function_name << " ( double * " << matrix_name << " );" << endl;
    else {
        cout << "#define " << function_name << "_n_rows " << Matrix.rows ()  << endl;
        cout << "#define " << function_name << "_n_cols " << Matrix.cols ()  << endl;
        cout << "extern     double * " << matrix_name << ";" << endl;
        cout << "extern     double * " << function_name << " () ;" << endl;
    }
    cout.close () ;
}

/*
Method that create a C file
*/
void System::export_Matrix_C ( string function_name , string matrix_name , Matrix Matrix , lst Matrix_atom_list, lst Matrix_atom_expression_list, int order) {

    try{
        if ( (order != CMO) && (order !=RMO)  ) throw 1;
    }
    catch ( int e ) {
        outError ( "ERR -  Last parameter (int order) must be CMO  or RMO" );
    }

    extern int C_EXPORT_AS_PROCEDURE;
    ofstream cout;

    if ( C_EXPORT_AS_PROCEDURE != 1 ) {

        load_includes_defines(function_name, order);
        cout.open ( ( function_name+".c" ).c_str () , ios::app);
        //*************************************************************************************************
        //    cout << csrc_double ; /* ADDED to solve csrc_double */
        //*************************************************************************************************
        cout << dflt;
        set_print_func<power, print_myformat>(print_power_as_myformat);
        set_print_func<numeric, print_myformat>(print_numeric_as_myformat);
        //set_print_func<, print_myformat>(print_absolute_as_myformat);
        //*************************************************************************************************
        cout << "" << endl;

        if ( atomization == YES ) {        
            for ( int i = 0; i < Matrix_atom_list.nops () ; ++i )
                cout << "double " << Matrix_atom_list.op ( i )<< ";" << endl;
                
            cout << "" << endl;
        }

        if ( 0 )
            cout << "double * " << function_name << " ( double * " << matrix_name << " )" << endl;
        else {
            cout << "double * " << matrix_name << " = NULL;" << endl;

            cout << "void Init"<< matrix_name << " ( ) " << endl;
            cout << "{" << endl;
            cout << "    " << matrix_name << " = malloc ( "<< function_name << "_n_rows * "<< function_name << "_n_cols * sizeof(double) );" << endl;

            cout << "  {int i;" << endl;
            cout << "  for ( i = 0 ; i < " << function_name << "_n_rows * " << function_name << "_n_cols ; i++ ) {" << matrix_name << "[i]=0.0;}" << endl;
            cout << "  }" << endl;
            cout << "}" << endl;

            cout << "" << endl;
            cout << "void Done"<< matrix_name << " ( ) " << endl;
            cout << "{" << endl;
            cout << "if (" << matrix_name << " != NULL) " << endl;
            cout << "free (" << matrix_name << " ); " << endl;
            cout << matrix_name << " = NULL; " << endl;
            cout << "}" << endl;
            cout << "" << endl;
            cout << "" << endl;

            cout << "double * " << function_name << " ()" << endl;
        }

        cout << "{" << endl;
        cout << "if ( " << matrix_name << " == NULL )" << endl;
        cout << " {" << endl;
        cout << "    " << matrix_name << " = malloc ( "<< function_name << "_n_rows * "<< function_name << "_n_cols * sizeof(double) );" << endl;
        cout << "  {int i;" << endl;
        cout << "  for ( i = 0 ; i < "<< function_name << "_n_rows * "<< function_name << "_n_cols ; i++ ) {" << matrix_name << "[i]=0.0;}" << endl;
        cout << "  }" << endl;
        vector < int > vector_aux_one;
        vector < int > vector_aux_two;
        vector < int > vector_aux_three;

        int k=0;

        if (order==CMO && atomization == NO){
        /* Matrix written in Column-major order */
            for ( int j = 0 ; j < Matrix.cols () ; j++ )
                for ( int i = 0 ; i < Matrix.rows () ; i++ )
                    if ( dt ( Matrix ( i , j ) ) == true )
                    {
                        cout << matrix_name << "[" << k << "]=" ; ( Matrix ( i , j ) ).print(print_myformat(cout)); cout << ";" << endl;
                        //cout << matrix_name << "[" << k << "] = " << csrc_double <<  Matrix ( i , j )<< ";" << endl;
                        k++;
                    }
                    else
                    {
                        /* FIX funcionan las plantillas cuando el vector es double ?*/
                        vector_aux_two.push_back ( i );
                        vector_aux_three.push_back ( j );
                    }
        }
        else if(order==RMO && atomization == NO){
            for ( int i = 0 ; i < Matrix.rows () ; i++ )
                for ( int j = 0 ; j < Matrix.cols () ; j++ )
                    if ( dt ( Matrix ( i , j ) ) == true )
                    {
                    cout << matrix_name << "[" << k << "]=" ; ( Matrix ( i , j ) ).print(print_myformat(cout)); cout << ";" << endl;
                    //cout << matrix_name << "[" << k << "] = " << csrc_double <<  Matrix ( i , j )<< ";" << endl;                    
                    k++;
                    }
                    else
                    {
                        /* FIX funcionan las plantillas cuando el vector es double ?*/
                        vector_aux_two.push_back ( i );
                        vector_aux_three.push_back ( j );
                    }
        }

        cout << " }" << endl << endl;

        
        if ( order==CMO && atomization == YES ){
			ex AuxExp; 
            for ( int i = 0 ; i < Matrix_atom_list.nops () ; i++ ){
                cout << Matrix_atom_list.op( i )<< " = " <<  csrc_double << Matrix_atom_expression_list.op( i ) << ";" << endl;    
                //AuxExp = Matrix_atom_expression_list.op( i );
                //cout << Matrix_atom_list.op( i ) << " = " ; ( AuxExp ).print(print_myformat(cout)); cout << ";" << endl;          
            }
            cout << endl;
            k = 0 ;
            for ( int j = 0 ; j < Matrix.cols () ; j++ ){
                for ( int i = 0 ; i < Matrix.rows () ; i++ ){
                    if (Matrix ( i , j ) != 0.0 ) 
                        cout << matrix_name << "[" << k << "] = " << csrc_double << Matrix ( i , j ) << ";" << endl;
                    //cout << matrix_name << "[" << k << "]=" ; ( Matrix ( i , j ) ).print(print_myformat(cout)); cout << ";" << endl;
                    k++;
                }    
            }
            cout << endl;    
        }
        
        else if ( order==RMO && atomization == YES ){
            ex AuxExp;
            for ( int i = 0 ; i < Matrix_atom_list.nops () ; i++ ){
                cout << Matrix_atom_list.op( i )<< " = " <<  csrc_double << Matrix_atom_expression_list.op( i ) << ";" << endl;
                //AuxExp = Matrix_atom_expression_list.op( i );
                //cout << Matrix_atom_list.op( i ) << " = " ; ( AuxExp ).print(print_myformat(cout)); cout << ";" << endl;                  
            }
            cout << endl;
            k = 0 ; 
            for ( int i = 0 ; i < Matrix.rows () ; i++ ){
                for ( int j = 0 ; j < Matrix.cols () ; j++ ){
                    if (Matrix ( i , j ) != 0.0 )
                        cout << matrix_name << "[" << k << "] = " << csrc_double <<  Matrix ( i , j )<< ";" << endl;
                    //cout << matrix_name << "[" << k << "]=" ; (  Matrix ( i , j ) ).print(print_myformat(cout)); cout << ";" << endl;
                    k++;
                }
            }    
            cout << endl;   
        }

        if (order==CMO && atomization == NO){ 
            /* Matrix written in Column-major order */
            for ( int i=0; i < vector_aux_two.size () ; i++ ){    
               cout << matrix_name << "[" << vector_aux_two.at ( i ) + Matrix.rows ()*vector_aux_three.at ( i ) <<"]=" ; ( Matrix ( vector_aux_two.at ( i ) , vector_aux_three.at ( i ) ) ).print(print_myformat(cout)); cout  << ";" << endl;
            }
        }

        else if (order==RMO && atomization == NO){
            for ( int j=0; j < vector_aux_three.size () ; j++ ){
                cout << matrix_name << "[" << vector_aux_three.at ( j ) + Matrix.cols ()*vector_aux_two.at ( j ) <<"]=" ; ( Matrix ( vector_aux_two.at ( j ) , vector_aux_three.at ( j ) ) ).print(print_myformat(cout)); cout  << ";" << endl;
            }
        }

        cout << "return " << matrix_name << ";" << endl;
        cout << "}" << endl;
        cout.close () ;

        /* ----------------------------------------*/
        /* End of the C file creation procedure*/
        /* ----------------------------------------*/

        /* ----------------------------------------*/
        /* Begin of the H file creation procedure*/
        /* ----------------------------------------*/

        cout.open ( ( function_name+".h" ).c_str () );
        if ( 0 )
            cout << "extern double * " << function_name << " ( double * " << matrix_name << " );" << endl;
        else {
            cout << "#define " << function_name << "_n_rows " << Matrix.rows ()  << endl;
            cout << "#define " << function_name << "_n_cols " << Matrix.cols ()  << endl;
            cout << "extern double * " << matrix_name << ";" << endl;
            cout << "extern void Init"<< matrix_name << " ( void ); " << endl;
            cout << "extern void Done"<< matrix_name << " ( void ); " << endl;
            cout << "extern double * " << function_name << " ( void ) ;" << endl;
        }
        cout.close () ;
    }

        /* ----------------------------------------*/
        /* End of the H file creation procedure*/
        /* ----------------------------------------*/

    else {

        load_includes_defines(function_name, order);

        cout.open ( ( function_name+".c" ).c_str () , ios::app);
       //*************************************************************************************************
        cout << csrc_double ; /* ADDED to solve csrc_double */
       //*************************************************************************************************
       //cout << dflt;
       //set_print_func<power, print_myformat>(print_power_as_myformat);
       //set_print_func<numeric, print_myformat>(print_numeric_as_myformat);
       //*************************************************************************************************

        cout << "" << endl;

        cout << "double * " << matrix_name << " = NULL;" << endl;

        cout << "void Init"<< matrix_name << " ( double * " << matrix_name << " ) " << endl;
        cout << "{" << endl;
        cout << "    " << matrix_name << " = malloc ( "<< function_name << "_n_rows * "<< function_name << "_n_cols * sizeof(double) );" << endl;
        cout << "  {int i;" << endl;
        cout << "  for ( i = 0 ; i < " << function_name << "_n_rows * " << function_name << "_n_cols ; i++ ) {" << matrix_name << "[i]=0.0;}" << endl;
        cout << "  }" << endl;
        cout << "}" << endl;

        cout << "" << endl;
        cout << "void Done"<< matrix_name << " ( double * " << matrix_name << " ) " << endl;
        cout << "{" << endl;
        cout << "if (" << matrix_name << " != NULL) " << endl;
        cout << "free (" << matrix_name << " ); " << endl;
        cout << matrix_name << " = NULL; " << endl;
        cout << "}" << endl;
        cout << "" << endl;
        cout << "" << endl;


        cout << "" << endl;

        cout << "void "<< function_name << " (  double * " << matrix_name << " )" << endl;

        cout << "{" << endl;
        cout << "if ( " << matrix_name << " == NULL )" << endl;
        cout << " {" << endl;
        cout << "    " << matrix_name << " = malloc ( "<< function_name << "_n_rows * "<< function_name << "_n_cols * sizeof(double) );" << endl;
        cout << "  {int i;" << endl;
        cout << "  for ( i = 0 ; i < "<< function_name << "_n_rows * "<< function_name << "_n_cols ; i++ ) {" << matrix_name << "[i]=0.0;}" << endl;
        cout << "  }" << endl;
        vector < int > vector_aux_one;
        vector < int > vector_aux_two;
        vector < int > vector_aux_three;

        lst Matrix_atom_expression_list;
        atom_expression_list ( Matrix_atom_list , Matrix_atom_expression_list );

//        if ( atomization == YES )
//            for ( int i = 0 ; i < Matrix_atom_list.nops () ; i++ )
//                if ( dt ( Matrix_atom_list.op ( i ) ) == true )
//                    cout << "/*constant*/ " << Matrix_atom_list.op ( i ) << " = " << Matrix_atom_expression_list.op ( i )<< ";" << endl;
//                else
//                    vector_aux_one.push_back ( i );

        int k=0;

        if (order==CMO){
              /* Matrix written in Column-major order */
              for ( int j = 0 ; j < Matrix.cols () ; j++ )
                for ( int i = 0 ; i < Matrix.rows () ; i++ )
                    if ( dt ( Matrix ( i , j ) ) == true ){
//                      cout << matrix_name << "[" << k << "]=" << Matrix ( i , j ) << ";" << endl;
                        cout << matrix_name << "[" << k << "]=" ; ( Matrix ( i , j )).print(print_myformat(cout)); cout << ";" << endl;
                        k++;
                    }
                    else{
                        /* FIX funcionan las plantillas cuando el vector es double ?*/
                        vector_aux_two.push_back ( i );
                        vector_aux_three.push_back ( j );
                    }
        }
        else{
            for ( int i = 0 ; i < Matrix.rows () ; i++ )
                for ( int j = 0 ; j < Matrix.cols () ; j++ )
                    if ( dt ( Matrix ( i , j ) ) == true ){
                        //cout << matrix_name << "[" << k << "]=" << Matrix ( i , j ) << ";" << endl;
                        cout << matrix_name << "[" << k << "]=" ; ( Matrix ( i , j )).print(print_myformat(cout)); cout << ";" << endl;
                        k++;
                    }
                    else{
                        /* FIX funcionan las plantillas cuando el vector es double ?*/
                        vector_aux_two.push_back ( i );
                        vector_aux_three.push_back ( j );
                    }
        }

        cout << " }" << endl;


        if ( atomization == YES )
            for ( int i = 0 ; i < vector_aux_one.size () ; i++ )
            cout << " " << Matrix_atom_list.op ( vector_aux_one.at ( i ) ) << " = " << Matrix_atom_expression_list.op ( vector_aux_one.at ( i ) )<< ";" << endl;

        if (order==CMO){
            /* Matrix written in Column-major order */
            for ( int i = 0 ; i < vector_aux_two.size () ; i++ ){
                // cout << matrix_name << "[" << vector_aux_two.at ( i ) + Matrix.rows ()*vector_aux_three.at ( i ) <<"]=" << Matrix ( vector_aux_two.at ( i ) , vector_aux_three.at ( i ) ) << ";" << endl;
                cout << matrix_name << "[" << vector_aux_two.at ( i ) + Matrix.rows ()*vector_aux_three.at ( i ) <<"]=" ; ( Matrix ( vector_aux_two.at ( i ) , vector_aux_three.at ( i ) ) ).print(print_myformat(cout)); cout  << ";" << endl;
            }
        }
        else{
            for ( int j = 0 ; j < vector_aux_three.size () ; j++ ){
                //cout << matrix_name << "[" << vector_aux_three.at ( j ) + Matrix.cols ()*vector_aux_two.at ( j ) <<"]=" << Matrix ( vector_aux_two.at ( j ) , vector_aux_three.at ( j ) ) << ";" << endl;
                cout << matrix_name << "[" << vector_aux_three.at ( j ) + Matrix.cols ()*vector_aux_two.at ( j ) <<"]=" ; ( Matrix ( vector_aux_two.at ( j ) , vector_aux_three.at ( j ) ) ).print(print_myformat(cout)); cout  << ";" << endl;
            }
        }

        cout << "}" << endl;
        cout.close () ;

        /* ----------------------------------------*/
        /* Begin of the H file creation procedure*/
        /* ----------------------------------------*/

        cout.open ( ( function_name+".h" ).c_str () );

        if ( 0 )
            cout << "extern double * " << function_name << " ( double * " << matrix_name << " );" << endl;
        else {
            cout << "#define " << function_name << "_n_rows " << Matrix.rows ()  << endl;
            cout << "#define " << function_name << "_n_cols " << Matrix.cols ()  << endl;
            cout << "extern double * " << matrix_name << ";" << endl;
            cout << "extern void Init"<< matrix_name << " ( double * " << matrix_name << " ); " << endl;
            cout << "extern void Done"<< matrix_name << " ( double * " << matrix_name << " ); " << endl;
            cout << "extern void "<< function_name << " ( double * " << matrix_name << " ) ;" << endl;
        }
        cout.close () ;
        /* ----------------------------------------*/
        /* End of the H file creation procedure*/
        /* ----------------------------------------*/
    }


}


void System::export_Matrix_C ( string function_name , string matrix_name , Matrix Matrix , int order) {
    lst Matrix_atom_list, Matrix_atom_expression_list;
    export_Matrix_C ( function_name , matrix_name , Matrix , Matrix_atom_list, Matrix_atom_expression_list, order);
}

/*
Method that create a C file GSL
*/
//~ void System::export_Matrix_C_GSL ( string function_name , string matrix_name , Matrix Matrix , lst Matrix_atom_list ) {
    //~ ofstream cout;
    //~ cout.open ( ( function_name+".c" ).c_str () );
    //~ cout << csrc_double ;
    //~ cout << "/*----------"<< function_name <<".c lib3D_MEC exported-----------*/" << endl << endl;
    //~ cout << "/*For increased velocity use GSL HAVE_INLINE and GSL_RANGE_CHECK_OFF preprocesor directive to compile:/*" << endl << endl;
    //~ cout << "/* gcc -DHAVE_INLINE = 1 -DGSL_RANGE_CHECK_OFF = 1 ... ---*/" << endl << endl;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <gsl/gsl_matrix.h>" << endl;
    //~ cout << "#include \"var_def.h\"" << endl;
    //~ cout << "#include \"gen_coord_vect_def.h\"" << endl;
    //~ cout << "#include \"gen_vel_vect_def.h\"" << endl;
    //~ cout << "#include \"gen_accel_vect_def.h\"" << endl;
    //~ cout << "#include \"unknowns_vect_def.h\"" << endl;
    //~ cout << "#include \"inputs_vect_def.h\"" << endl;
    //~ cout << "#include \""<< function_name << ".h\"" << endl;
    //~ cout << "#include \"step.h\"" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ for ( int i = 0 ; i < coordinates.size () ; i++ )
        //~ cout << "#define " << coordinates[i]-> get_name () << " gsl_vector_get ( q , " << i << " )" << endl;
    //~ for ( int i = 0 ; i < velocities.size () ; i++ )
        //~ cout << "#define " << velocities[i]-> get_name () << " gsl_vector_get ( dq , " << i << " )" << endl;
    //~ for ( int i = 0 ; i < accelerations.size () ; i++ )
        //~ cout << "#define " << accelerations[i]-> get_name () << " gsl_vector_get ( ddq , " << i << " )" << endl;
    //~ for ( int i = 0 ; i < unknowns.size () ; i++ )
        //~ cout << "#define " << unknowns[i]-> get_name () << " gsl_vector_get ( unknowns , " << i << " )" << endl;
    //~ for ( int i = 0 ; i < inputs.size () ; i++ )
        //~ cout << "#define " << inputs[i]-> get_name () << " gsl_vector_get ( inputs , " << i << " )" << endl;
//~ 
    //~ if ( atomization == YES ) {
        //~ lst aux_Matrix_atom_list;
        //~ aux_Matrix_atom_list = Matrix_atom_list;
        //~ atom_list ( Matrix , aux_Matrix_atom_list );
        //~ for ( int i = 0; i < aux_Matrix_atom_list.nops () ; ++i )
            //~ cout << "extern double " << aux_Matrix_atom_list.op ( i )<< ";" << endl;
    //~ }
//~ 
    //~ if ( 0 )
        //~ cout << "gsl_matrix * " << function_name << " ( gsl_matrix * " << matrix_name << " )" << endl;
    //~ else {
        //~ cout << "gsl_matrix * " << matrix_name << " = NULL;" << endl;
        //~ cout << "gsl_matrix * " << function_name << " ()" << endl;
    //~ }
//~ 
    //~ cout << "{" << endl;
    //~ cout << "if ( " << matrix_name << " == NULL )" << endl;
    //~ cout << " {" << endl;
    //~ cout << "    " << matrix_name << " = gsl_matrix_alloc ( " << function_name << "_n_rows , " << function_name << "_n_cols );" << endl;
    //~ cout << "    gsl_matrix_set_zero ( " << matrix_name << " );" << endl;
//~ 
//~ 
    //~ vector < int > vector_aux_one;
    //~ vector < int > vector_aux_two;
    //~ vector < int > vector_aux_three;
//~ 
    //~ lst Matrix_atom_expression_list;
    //~ atom_expression_list ( Matrix_atom_list , Matrix_atom_expression_list );
//~ 
    //~ if ( atomization == YES )
        //~ for ( int i = 0 ; i < Matrix_atom_list.nops () ; i++ )
            //~ if ( dt ( Matrix_atom_list.op ( i ) ) == true )
                //~ cout << "/*constant*/ " << Matrix_atom_list.op ( i ) << " = " << Matrix_atom_expression_list.op ( i )<< ";" << endl;
            //~ else
                //~ vector_aux_one.push_back ( i );
//~ 
    //~ for ( int i = 0 ; i < Matrix.rows () ; i++ )
        //~ for ( int j = 0 ; j < Matrix.cols () ; j++ )
            //~ if ( dt ( Matrix ( i , j ) ) == true )
                //~ cout << "gsl_matrix_set ( " << matrix_name << " , " << i <<" , " << j << " , " << Matrix ( i , j )<< " );" << endl;
            //~ else{
                //~ vector_aux_two.push_back ( i );
                //~ vector_aux_three.push_back ( j );
            //~ }
//~ 
    //~ cout << " }" << endl;
//~ 
//~ 
    //~ if ( atomization == YES )
        //~ for ( int i = 0 ; i < vector_aux_one.size () ; i++ )
            //~ cout << " " << Matrix_atom_list.op ( vector_aux_one.at ( i ) ) << " = " << Matrix_atom_expression_list.op ( vector_aux_one.at ( i ) )<< ";" << endl;
//~ 
//~ 
    //~ for ( int i = 0 ; i < vector_aux_two.size () ; i++ )
            //~ cout << "gsl_matrix_set ( " << matrix_name << " , " << vector_aux_two.at ( i ) <<" , " << vector_aux_three.at ( i ) << " , " << Matrix ( vector_aux_two.at ( i ) , vector_aux_three.at ( i ) )<< " );" << endl;
//~ 
//~ 
    //~ cout << "return " << matrix_name << ";" << endl;
    //~ cout << "}" << endl;
    //~ cout.close () ;
    //~ cout.open ( ( function_name+".h" ).c_str () );
    //~ if ( 0 )
        //~ cout << "extern gsl_matrix * " << function_name << " ( gsl_matrix * " << matrix_name << " );" << endl;
    //~ else {
        //~ cout << "#define " << function_name << "_n_rows " << Matrix.rows () << endl;
        //~ cout << "#define " << function_name << "_n_cols " << Matrix.cols () << endl;
        //~ cout << "extern     gsl_matrix * " << matrix_name << ";" << endl;
        //~ cout << "extern     gsl_matrix * " << function_name << "() ;" << endl;
//~ 
    //~ }
    //~ cout.close () ;
//~ }


/*
Method that create a C file
*/
void System::export_write_state_file_header_C ( void ) {
    ofstream cout;
    cout.open ( "write_state_file_header.c" );
    cout << csrc_double ;
    cout << "/*----------write_state_file_header.c lib3D_MEC exported-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "void write_state_file_header ( FILE * state_file )" << endl;
    cout << "{" << endl;
    cout << "fprintf ( state_file , \"";
    cout << get_Time_Symbol () << "\t" ;
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        {cout << coordinates[i]-> get_name () << "\t" ;
         cout << velocities[i]-> get_name () << "\t" ;
         cout << accelerations[i]-> get_name () << "\t" ;}
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << parameters[i]-> get_name () << "\t" ;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << unknowns[i]-> get_name () << "\t" ;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << inputs[i]-> get_name () << "\t" ;
    cout << "\\n\" );" << endl;
    cout << "}" << endl;
    cout.close () ;
}

/*
Method that create a C file GSL
*/
//~ void System::export_write_state_file_header_C_GSL ( void ) {
    //~ ofstream cout;
    //~ cout.open ( "write_state_file_header.c" );
    //~ cout << csrc_double ;
    //~ cout << "/*----------write_state_file_header.c lib3D_MEC exported-----------*/" << endl << endl;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ cout << "#include \"var_def.h\"" << endl;
    //~ cout << "void write_state_file_header ( FILE * state_file )" << endl;
    //~ cout << "{" << endl;
    //~ cout << "fprintf ( state_file , \"";
    //~ cout << get_Time_Symbol () << "\t" ;
    //~ for ( int i = 0 ; i < coordinates.size () ; i++ )
        //~ {cout << coordinates[i]-> get_name () << "\t" ;
         //~ cout << velocities[i]-> get_name () << "\t" ;
         //~ cout << accelerations[i]-> get_name () << "\t" ;}
    //~ for ( int i = 0 ; i < parameters.size () ; i++ )
        //~ cout << parameters[i]-> get_name () << "\t" ;
    //~ for ( int i = 0 ; i < unknowns.size () ; i++ )
        //~ cout << unknowns[i]-> get_name () << "\t" ;
    //~ for ( int i = 0 ; i < inputs.size () ; i++ )
        //~ cout << inputs[i]-> get_name () << "\t" ;
    //~ cout << "\\n\" );" << endl;
    //~ cout << "}" << endl;
    //~ cout.close () ;
//~ }
//~ 

/*
Method that create a C file
*/
void System::export_write_state_file_C ( void ) {
    ofstream cout;
    cout.open ( "write_state_file.c" );
    cout << csrc_double ;
    cout << "/*----------write_state_file.c lib3D_MEC exported-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "#include \"gen_coord_vect_def.h\"" << endl;
    cout << "#include \"gen_vel_vect_def.h\"" << endl;
    cout << "#include \"gen_accel_vect_def.h\"" << endl;
    cout << "#include \"param_vect_def.h\"" << endl;
    cout << "#include \"unknowns_vect_def.h\"" << endl;
    cout << "#include \"inputs_vect_def.h\"" << endl;
    cout << "#include <math.h>" << endl;
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "#define " << coordinates[i]-> get_name () << " q[ " << i << " ]" << endl;
    for ( int i = 0 ; i < velocities.size () ; i++ )
        cout << "#define " << velocities[i]-> get_name () << " dq[ " << i << " ]" << endl;
    for ( int i = 0 ; i < accelerations.size () ; i++ )
        cout << "#define " << accelerations[i]-> get_name () << " ddq[ " << i << " ]" << endl;
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "#define " << parameters[i]-> get_name () << " param[ " << i << " ]" << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "#define " << unknowns[i]-> get_name () << " unknowns[ " << i << " ]" << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "#define " << inputs[i]-> get_name () << " inputs[ " << i << " ]" << endl;
    cout << "void write_state_file ( FILE * state_file )" << endl;
    cout << "{" << endl;
    cout << "fprintf ( state_file , \"";
    cout << "%g\t";
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        {cout << "%g\t";
         cout << "%g\t";
         cout << "%g\t";}

    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "%g\t";
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "%g\t";
    cout << "\\n\"";
    cout << " , " << get_Time_Symbol () ;
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        {cout << " , " << coordinates[i]-> get_name () ;
         cout << " , " << velocities[i]-> get_name () ;
         cout << " , " << accelerations[i]-> get_name () ;}

    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << " , " << parameters[i]-> get_name () ;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << " , " << unknowns[i]-> get_name () ;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << " , " << inputs[i]-> get_name () ;
    cout << " );" << endl;
    cout << "}" << endl;
    cout.close () ;
}


/*
Method that create a C file GSL
*/
//~ void System::export_write_state_file_C_GSL ( void ) {
    //~ ofstream cout;
    //~ cout.open ( "write_state_file.c" );
    //~ cout << csrc_double ;
    //~ cout << "/*----------write_state_file.c lib3D_MEC exported-----------*/" << endl << endl;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include \"var_def.h\"" << endl;
    //~ cout << "#include \"gen_coord_vect_def.h\"" << endl;
    //~ cout << "#include \"gen_vel_vect_def.h\"" << endl;
    //~ cout << "#include \"gen_accel_vect_def.h\"" << endl;
    //~ cout << "#include \"unknowns_vect_def.h\"" << endl;
    //~ cout << "#include \"inputs_vect_def.h\"" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ for ( int i = 0 ; i < coordinates.size () ; i++ )
        //~ {cout << "#define " << coordinates[i]-> get_name () << " gsl_vector_get ( q , " << i << " )" << endl;
         //~ cout << "#define " << velocities[i]-> get_name () << " gsl_vector_get ( dq , " << i << " )" << endl;
         //~ cout << "#define " << accelerations[i]-> get_name () << " gsl_vector_get ( ddq , " << i << " )" << endl;}
//~ 
    //~ for ( int i = 0 ; i < unknowns.size () ; i++ )
        //~ cout << "#define " << unknowns[i]-> get_name () << " gsl_vector_get ( unknowns , " << i << " )" << endl;
    //~ for ( int i = 0 ; i < inputs.size () ; i++ )
        //~ cout << "#define " << inputs[i]-> get_name () << " gsl_vector_get ( inputs , " << i << " )" << endl;
    //~ cout << "void write_state_file ( FILE * state_file )" << endl;
    //~ cout << "{" << endl;
    //~ cout << "fprintf ( state_file , \"";
    //~ cout << "%g\t";
    //~ for ( int i = 0 ; i < coordinates.size () ; i++ )
        //~ {cout << "%g\t";
         //~ cout << "%g\t";
         //~ cout << "%g\t";}
//~ 
    //~ for ( int i = 0 ; i < parameters.size () ; i++ )
        //~ cout << "%g\t";
    //~ for ( int i = 0 ; i < unknowns.size () ; i++ )
        //~ cout << "%g\t";
    //~ cout << "\\n\"";
    //~ cout << " , " << get_Time_Symbol () ;
    //~ for ( int i = 0 ; i < coordinates.size () ; i++ )
        //~ {cout << " , " << coordinates[i]-> get_name () ;
         //~ cout << " , " << velocities[i]-> get_name () ;
         //~ cout << " , " << accelerations[i]-> get_name () ;}
//~ 
    //~ for ( int i = 0 ; i < parameters.size () ; i++ )
        //~ cout << " , " << parameters[i]-> get_name () ;
    //~ for ( int i = 0 ; i < unknowns.size () ; i++ )
        //~ cout << " , " << unknowns[i]-> get_name () ;
    //~ for ( int i = 0 ; i < inputs.size () ; i++ )
        //~ cout << " , " << inputs[i]-> get_name () ;
    //~ cout << " );" << endl;
    //~ cout << "}" << endl;
    //~ cout.close () ;
//~ }

/*
Method that create a H file
*/
void System::export_write_data_file_H ( void ) {
    ofstream cout;
    cout.open ( "write_data_file.h" );
    cout << csrc_double ;
    cout << "/*----------write_data_file.h lib3D_MEC exported-----------*/" << endl << endl;

		cout << "extern void write_data_file(FILE * data_file);" << endl;

 		cout << "extern void write_data_file_header(FILE * data_file);" << endl;

    cout.close () ;
}

/*
Method that create a C file
*/
void System::export_write_data_file_C ( void ) {
    ofstream cout;
    cout.open ( "write_data_file.c" );
    cout << csrc_double ;
    cout << "/*----------write_data_file.c lib3D_MEC exported-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl << endl;

    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"gen_coord.h\"" << endl;
    cout << "#include \"gen_vel.h\"" << endl;
    cout << "#include \"gen_accel.h\"" << endl;
    if (aux_coordinates.size() > 0){
      cout << "#include \"gen_auxcoord.h\"" << endl;
      cout << "#include \"gen_auxvel.h\"" << endl;
      cout << "#include \"gen_auxaccel.h\"" << endl;    
 
    }
    cout << "#include \"param.h\"" << endl;
    cout << "#include \"unknowns.h\"" << endl;
    cout << "#include \"inputs.h\"" << endl << endl;

    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "#define " << coordinates[i]-> get_name () << " q[ " << i << " ]" << endl;
    for ( int i = 0 ; i < velocities.size () ; i++ )
        cout << "#define " << velocities[i]-> get_name () << " dq[ " << i << " ]" << endl;
    for ( int i = 0 ; i < accelerations.size () ; i++ )
        cout << "#define " << accelerations[i]-> get_name () << " ddq[ " << i << " ]" << endl;
    if (aux_coordinates.size() > 0){        
      for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
        cout << "#define " << aux_coordinates[i]-> get_name () << " qaux[ " << i << " ]" << endl;
      for ( int i = 0 ; i < aux_velocities.size () ; i++ )
        cout << "#define " << aux_velocities[i]-> get_name () << " dqaux[ " << i << " ]" << endl;
      for ( int i = 0 ; i < aux_accelerations.size () ; i++ )
        cout << "#define " <<aux_accelerations[i]-> get_name () << " ddqaux[ " << i << " ]" << endl;    
    }       
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "#define " << parameters[i]-> get_name () << " param[ " << i << " ]" << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "#define " << unknowns[i]-> get_name () << " unknowns[ " << i << " ]" << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "#define " << inputs[i]-> get_name () << " inputs[ " << i << " ]" << endl << endl;

    cout << "void write_data_file ( FILE * data_file )" << endl;
    cout << "{" << endl;
    cout << "fprintf ( data_file , \"";
    cout << "%g\t";
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        {cout << "%g\t";
         cout << "%g\t";
         cout << "%g\t";}

    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "%g\t";
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "%g\t";
    cout << "\\n\"";
    cout << " , " << get_Time_Symbol () ;
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        {cout << " , " << coordinates[i]-> get_name () ;
         cout << " , " << velocities[i]-> get_name () ;
         cout << " , " << accelerations[i]-> get_name () ;}

    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << " , " << parameters[i]-> get_name () ;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << " , " << unknowns[i]-> get_name () ;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << " , " << inputs[i]-> get_name () ;
    cout << " );" << endl;
    cout << "}" << endl << endl;

    cout << "void write_data_file_header ( FILE * data_file )" << endl;
    cout << "{" << endl;
    cout << "fprintf ( data_file , \" % ";
    
    cout << get_Time_Symbol () << "\t" ;
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        {cout << coordinates[i]-> get_name () << "\t" ;
         cout << velocities[i]-> get_name () << "\t" ;
         cout << accelerations[i]-> get_name () << "\t" ;}
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << parameters[i]-> get_name () << "\t" ;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << unknowns[i]-> get_name () << "\t" ;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << inputs[i]-> get_name () << "\t" ;
    cout << "\\n\" );" << endl;
    cout << "}" << endl << endl;

    cout.close () ;
}

/*

Method that create a C file
*/
void System::export_write_data_file_C ( lst expresion_list ) {
    ofstream cout;
    cout.open ( "write_data_file.c" );
    cout << csrc_double ;
    cout << "/*----------write_data_file.c lib3D_MEC exported-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl << endl;

    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"gen_coord.h\"" << endl;
    cout << "#include \"gen_vel.h\"" << endl;
    cout << "#include \"gen_accel.h\"" << endl;
    if (aux_coordinates.size()> 0){
       cout << "#include \"gen_auxcoord.h\"" << endl;
       cout << "#include \"gen_auxvel.h\"" << endl;
       cout << "#include \"gen_auxaccel.h\"" << endl;       
    }
    cout << "#include \"param.h\"" << endl;
    cout << "#include \"unknowns.h\"" << endl;
    cout << "#include \"inputs.h\"" << endl << endl;

    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "#define " << coordinates[i]-> get_name () << " q[ " << i << " ]" << endl;
    for ( int i = 0 ; i < velocities.size () ; i++ )
         cout << "#define " << velocities[i]-> get_name () << " dq[ " << i << " ]" << endl;
    for ( int i = 0 ; i < accelerations.size () ; i++ )
         cout << "#define " << accelerations[i]-> get_name () << " ddq[ " << i << " ]" << endl;
    if (aux_coordinates.size()> 0){     
        for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
            cout << "#define " << aux_coordinates[i]-> get_name () << " qaux[ " << i << " ]" << endl;
        for ( int i = 0 ; i < aux_velocities.size () ; i++ )
             cout << "#define " << aux_velocities[i]-> get_name () << " dqaux[ " << i << " ]" << endl;
        for ( int i = 0 ; i < aux_accelerations.size () ; i++ )
             cout << "#define " << aux_accelerations[i]-> get_name () << " ddqaux[ " << i << " ]" << endl;         
    }
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "#define " << parameters[i]-> get_name () << " param[ " << i << " ]" << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "#define " << unknowns[i]-> get_name () << " unknowns[ " << i << " ]" << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "#define " << inputs[i]-> get_name () << " inputs[ " << i << " ]" << endl << endl;

    cout << "void write_data_file ( FILE * data_file )" << endl;
    cout << "{" << endl;
    cout << "fprintf ( data_file , \"";
    cout << "%g\t";

    for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
                { cout << "%g\t"; }


    cout << "\\n\"";
    cout << " , " << get_Time_Symbol () ;

    for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
        { cout << " , " << (* k) ; }

    cout << " );" << endl;
    cout << "}" << endl << endl;

    cout << "void write_data_file_header ( FILE * data_file )" << endl;
    cout << "{" << endl;
    cout << "fprintf ( data_file , \" %% ";
    cout << get_Time_Symbol () << "\t" ;
    for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
                { cout << (* k) << "\t" ;  }

    cout << "\\n\" );" << endl;
    cout << "}" << endl;
    cout.close () ;
}

/*
Method that create a C file
*/
void System::export_write_state_file_header_C ( lst expresion_list ) {
    ofstream cout;
    cout.open ( "write_state_file_header.c" );
    cout << csrc_double ;
    cout << "/*----------write_state_file_header.c lib3D_MEC exported-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "void write_state_file_header ( FILE * state_file )" << endl;
    cout << "{" << endl;
    cout << "fprintf ( state_file , \"";
    cout << get_Time_Symbol () << "\t" ;
    for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
                { cout << (* k) << "\t" ;  }

/*  for ( int i = 0 ; i < coordinates.size () ; i++ )
        {cout << coordinates[i]-> get_name () << "\t" ;
         cout << velocities[i]-> get_name () << "\t" ;
         cout << accelerations[i]-> get_name () << "\t" ;}
    for ( int i = 0 ; i < velocities.size () ; i++ )
        cout << velocities[i]-> get_name () << "\t" ;
    for ( int i = 0 ; i < accelerations.size () ; i++ )
        cout << accelerations[i]-> get_name () << "\t" ;
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << parameters[i]-> get_name () << "\t" ;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << unknowns[i]-> get_name () << "\t" ;
*/

    cout << "\\n\" );" << endl;
    cout << "}" << endl;
    cout.close () ;
}


/*
Method that create a C file GSL
*/
//~ void System::export_write_state_file_header_C_GSL ( lst expresion_list ) {
    //~ ofstream cout;
    //~ cout.open ( "write_state_file_header.c" );
    //~ cout << csrc_double ;
    //~ cout << "/*----------write_state_file_header.c lib3D_MEC exported-----------*/" << endl << endl;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ cout << "#include \"var_def.h\"" << endl;
    //~ cout << "void write_state_file_header ( FILE * state_file )" << endl;
    //~ cout << "{" << endl;
    //~ cout << "fprintf ( state_file , \"";
    //~ cout << get_Time_Symbol () << "\t" ;
    //~ for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
                //~ { cout << (* k) << "\t" ;  }
//~ 
//~ /*  for ( int i = 0 ; i < coordinates.size () ; i++ )
        //~ {cout << coordinates[i]-> get_name () << "\t" ;
         //~ cout << velocities[i]-> get_name () << "\t" ;
         //~ cout << accelerations[i]-> get_name () << "\t" ;}
    //~ for ( int i = 0 ; i < velocities.size () ; i++ )
        //~ cout << velocities[i]-> get_name () << "\t" ;
    //~ for ( int i = 0 ; i < accelerations.size () ; i++ )
        //~ cout << accelerations[i]-> get_name () << "\t" ;
    //~ for ( int i = 0 ; i < parameters.size () ; i++ )
        //~ cout << parameters[i]-> get_name () << "\t" ;
    //~ for ( int i = 0 ; i < unknowns.size () ; i++ )
        //~ cout << unknowns[i]-> get_name () << "\t" ;
//~ */
//~ 
    //~ cout << "\\n\" );" << endl;
    //~ cout << "}" << endl;
    //~ cout.close () ;
//~ }

/*
Method that create a C file
*/
void System::export_write_state_file_C ( lst expresion_list ) {
    ofstream cout;
    cout.open ( "write_state_file.c" );
    cout << csrc_double ;
    cout << "/*----------write_state_file.c lib3D_MEC exported-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include \"var_def.h\"" << endl;
    cout << "#include \"gen_coord_vect_def.h\"" << endl;
    cout << "#include \"gen_vel_vect_def.h\"" << endl;
    cout << "#include \"gen_accel_vect_def.h\"" << endl;
    cout << "#include \"param_vect_def.h\"" << endl;
    cout << "#include \"unknowns_vect_def.h\"" << endl;
    cout << "#include \"inputs_vect_def.h\"" << endl;
    cout << "#include <math.h>" << endl;
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "#define " << coordinates[i]-> get_name () << " q[ " << i << " ]" << endl;
    for ( int i = 0 ; i < coordinates.size () ; i++ )
         cout << "#define " << velocities[i]-> get_name () << " dq[ " << i << " ]" << endl;
    for ( int i = 0 ; i < coordinates.size () ; i++ )
         cout << "#define " << accelerations[i]-> get_name () << " ddq[ " << i << " ]" << endl;

    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "#define " << parameters[i]-> get_name () << " param[ " << i << " ]" << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "#define " << unknowns[i]-> get_name () << " unknowns[ " << i << " ]" << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "#define " << inputs[i]-> get_name () << " inputs[ " << i << " ]" << endl;

    cout << "void write_state_file ( FILE * state_file )" << endl;
    cout << "{" << endl;
    cout << "fprintf ( state_file , \"";
    cout << "%g\t";

    for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
                { cout << "%g\t"; }


    cout << "\\n\"";
    cout << " , " << get_Time_Symbol () ;

    for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
        { cout << " , " << (* k) ; }

    cout << " );" << endl;
    cout << "}" << endl;
    cout.close () ;
}


/*
Method that create a C file GSL
*/
//~ void System::export_write_state_file_C_GSL ( lst expresion_list ) {
    //~ ofstream cout;
    //~ cout.open ( "write_state_file.c" );
    //~ cout << csrc_double ;
    //~ cout << "/*----------write_state_file.c lib3D_MEC exported-----------*/" << endl << endl;
    //~ cout << "#include <stdio.h>" << endl;
    //~ cout << "#include \"var_def.h\"" << endl;
    //~ cout << "#include \"gen_coord_vect_def.h\"" << endl;
    //~ cout << "#include \"gen_vel_vect_def.h\"" << endl;
    //~ cout << "#include \"gen_accel_vect_def.h\"" << endl;
    //~ cout << "#include \"unknowns_vect_def.h\"" << endl;
    //~ cout << "#include \"inputs_vect_def.h\"" << endl;
    //~ cout << "#include <math.h>" << endl;
    //~ for ( int i = 0 ; i < coordinates.size () ; i++ )
        //~ {cout << "#define " << coordinates[i]-> get_name () << " gsl_vector_get ( q , " << i << " )" << endl;
         //~ cout << "#define " << velocities[i]-> get_name () << " gsl_vector_get ( dq , " << i << " )" << endl;
         //~ cout << "#define " << accelerations[i]-> get_name () << " gsl_vector_get ( ddq , " << i << " )" << endl;}
//~ 
    //~ for ( int i = 0 ; i < parameters.size () ; i++ )
        //~ cout << "#define " << parameters[i]-> get_name () << " gsl_vector_get ( parameters , " << i << " )" << endl;
    //~ for ( int i = 0 ; i < unknowns.size () ; i++ )
        //~ cout << "#define " << unknowns[i]-> get_name () << " gsl_vector_get ( unknowns , " << i << " )" << endl;
    //~ for ( int i = 0 ; i < inputs.size () ; i++ )
        //~ cout << "#define " << inputs[i]-> get_name () << " gsl_vector_get ( inputs , " << i << " )" << endl;
//~ 
//~ 
    //~ cout << "void write_state_file ( FILE * state_file )" << endl;
    //~ cout << "{" << endl;
    //~ cout << "fprintf ( state_file , \"";
    //~ cout << "%g\t";
//~ 
    //~ for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
                //~ { cout << "%g\t"; }
//~ 
    //~ cout << "\\n\"";
    //~ cout << " , " << get_Time_Symbol () ;
//~ 
    //~ for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
        //~ { cout << " , " << (* k) ; }
//~ 
//~ 
    //~ cout << " );" << endl;
    //~ cout << "}" << endl;
    //~ cout.close () ;
//~ }


/*
Method that create a H file
*/
void System::export_read_data_file_H ( void ) {
    ofstream cout;
    cout.open ( "read_data_file.h" );
    cout << csrc_double ;
    cout << "/*----------read_data_file.h lib3D_MEC exported-----------*/" << endl << endl;

	cout << "extern void read_data_file(FILE * data_file);" << endl;

 	//~ cout << "extern void read_data_file_header(FILE * data_file);" << endl;

    cout.close () ;
}
/*

Method that create a C file
*/
void System::export_read_data_file_C ( lst expresion_list ) {
    ofstream cout;
    cout.open ( "read_data_file.c" );
    cout << csrc_double ;
    cout << "/*----------read_data_file.c lib3D_MEC exported-----------*/" << endl << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl << endl;

    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"gen_coord.h\"" << endl;
    cout << "#include \"gen_vel.h\"" << endl;
    cout << "#include \"gen_accel.h\"" << endl;
    //~ if (aux_coordinates.size()> 0){
       //~ cout << "#include \"gen_auxcoord.h\"" << endl;
       //~ cout << "#include \"gen_auxvel.h\"" << endl;
       //~ cout << "#include \"gen_auxaccel.h\"" << endl;       
    //~ }
    cout << "#include \"param.h\"" << endl;
    cout << "#include \"unknowns.h\"" << endl;
    cout << "#include \"inputs.h\"" << endl << endl;

    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "#define " << coordinates[i]-> get_name () << " q[ " << i << " ]" << endl;
    for ( int i = 0 ; i < velocities.size () ; i++ )
         cout << "#define " << velocities[i]-> get_name () << " dq[ " << i << " ]" << endl;
    for ( int i = 0 ; i < accelerations.size () ; i++ )
         cout << "#define " << accelerations[i]-> get_name () << " ddq[ " << i << " ]" << endl;
    //~ if (aux_coordinates.size()> 0){     
        //~ for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
            //~ cout << "#define " << aux_coordinates[i]-> get_name () << " qaux[ " << i << " ]" << endl;
        //~ for ( int i = 0 ; i < aux_velocities.size () ; i++ )
             //~ cout << "#define " << aux_velocities[i]-> get_name () << " dqaux[ " << i << " ]" << endl;
        //~ for ( int i = 0 ; i < aux_accelerations.size () ; i++ )
             //~ cout << "#define " << aux_accelerations[i]-> get_name () << " ddqaux[ " << i << " ]" << endl;         
    //~ }
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "#define " << parameters[i]-> get_name () << " param[ " << i << " ]" << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "#define " << unknowns[i]-> get_name () << " unknowns[ " << i << " ]" << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "#define " << inputs[i]-> get_name () << " inputs[ " << i << " ]" << endl << endl;

    cout << "void read_data_file ( FILE * data_file )" << endl;
    cout << "{" << endl;
    cout << "int reg = fscanf( data_file , \"";
    cout << "%lf\t";

    for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
                { cout << "%lf\t"; }


    cout << "\\n\"";
    cout << " , &" << get_Time_Symbol () ;

    for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
        { cout << " , &" << (* k) ; }

    cout << " );" << endl;
    cout << "}" << endl << endl;

    //~ cout << "void read_data_file_header ( FILE * data_file )" << endl;
    //~ cout << "{" << endl;
    //~ cout << "fscan ( data_file , \" %% ";
    //~ cout << get_Time_Symbol () << "\t" ;
    //~ for  ( lst::const_iterator k = expresion_list.begin () ; k != expresion_list.end () ; ++k )
                //~ { cout << (* k) << "\t" ;  }
    //~ 
    //~ cout << "\\n\" );" << endl;
    //~ cout << "}" << endl;
    cout.close () ;
    
    export_read_data_file_H ( );
}






/*********************************************************************************************************
***************************** SYSTEM MATLAB EXPORT FUNCTIONS *********************************************
*********************************************************************************************************/
void System::export_function_MATLAB(string function_name, string function_out, Matrix symbolic_matrix_function, lst Matrix_atom_list, lst Matrix_atom_expression_list, string s_in){
    
  vector<string> s_internal;
  stringstream ss(s_in); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, ',')) {
    s_internal.push_back(tok);
  }
  
  ofstream matlab_file;

  matlab_file.open( ( function_name+".m" ).c_str () ); 
  
  string s="(";
  
  for(int i = 0; i < s_internal.size(); ++i){
     if (s_internal[i] == "q"){s=s+"q,";}
     else if (s_internal[i] == "qaux"){s=s+"qaux,";}
     
     else if (s_internal[i] == "dq"){s=s+"dq,";}
     else if (s_internal[i] == "dqaux"){s=s+"dqaux,";}
     
     else if (s_internal[i] == "ddq"){s=s+"ddq,";}
     else if (s_internal[i] == "ddqaux"){s=s+"ddqaux,";}
         
     else if (s_internal[i] == "param"){s=s+"param,";}
     
     else if (s_internal[i] == "time"){s=s+"time,";}
     else if (s_internal[i] == "inputs" && inputs.size () > 0){s=s+"inputs,";}
     else if (s_internal[i] == "unknowns" && unknowns.size ()> 0 ){s=s+"unknowns,";}
     else  {s=s+s_internal[i]+",";};
  }
  if (s.size () > 0) { s.resize (s.size () - 1);} // remove last ","
  s = s + ")";

  matlab_file << "function " << function_out << " = " << function_name << s << endl;
  
  matlab_file <<  endl;
  
  
  
  for(int i = 0; i < s_internal.size(); ++i){
    if (s_internal[i] == "q"){
      for ( int i = 0 ; i < coordinates.size () ; i++ )
        matlab_file << coordinates[i]-> get_name () << " = q( " << i+1 << " ); "  << endl;
    }
    else if (s_internal[i] == "qaux"){
      for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
        matlab_file << aux_coordinates[i]-> get_name () << " = qaux( " << i+1 << " ); "  << endl;
    }    
 
    else if (s_internal[i] == "dq"){
      for ( int i = 0 ; i < velocities.size () ; i++ )
        matlab_file << velocities[i]-> get_name () << " = dq( " << i+1 << " ); "  << endl;  
    }
    else if (s_internal[i] == "dqaux"){
      for ( int i = 0 ; i < aux_velocities.size () ; i++ )
        matlab_file << aux_velocities[i]-> get_name () << " = dqaux( " << i+1 << " ); "  << endl;  
    }    
    
    else if (s_internal[i] == "ddq"){
      for ( int i = 0 ; i < accelerations.size () ; i++ )
        matlab_file << accelerations[i]-> get_name () << " = ddq( " << i+1 << " ); "  << endl;  
    }
    else if (s_internal[i] == "ddqaux"){
      for ( int i = 0 ; i < aux_accelerations.size () ; i++ )
        matlab_file << aux_accelerations[i]-> get_name () << " = ddqaux( " << i+1 << " ); "  << endl;  
    } 
    
    else if (s_internal[i] == "param"){
      for ( int i = 0 ; i < parameters.size () ; i++ )
        matlab_file << parameters[i]-> get_name () << " = param( " << i+1 << " ); "  << endl;  
    }
    else  if (s_internal[i] == "time"){
      matlab_file << get_Time_Symbol ( ) << "= time ;" << endl;
    }
    else if (s_internal[i] == "inputs"){
      for ( int i = 0 ; i < inputs.size () ; i++ )
        matlab_file << inputs[i]-> get_name () << " = inputs( " << i+1 << " ); "  << endl;  
    }    
    else if (s_internal[i] == "unknowns"){
      for ( int i = 0 ; i < unknowns.size () ; i++ )
        matlab_file << unknowns[i]-> get_name () << " = unknowns( " << i+1 << " ); "  << endl;  
    }    
    
   
    matlab_file <<  endl;

  }
  
  if (atomization == YES){
    for (int i  = 0 ; i < Matrix_atom_list.nops () ; i++ ){ 
      matlab_file << Matrix_atom_list.op( i )<< " = " <<   Matrix_atom_expression_list.op( i ) << ";" << endl;
    }
    matlab_file <<  endl;    
  }
  
  matlab_file << function_out << " = " << symbolic_matrix_function << ";" << endl;
  
  matlab_file <<  endl;
  matlab_file << "%endfunction" << endl;
  matlab_file.close();
  
  
}

void System::export_function_MATLAB(string function_name, string function_out, Matrix symbolic_matrix_function, lst Matrix_atom_list, lst Matrix_atom_expression_list){

ofstream matlab_file;

  matlab_file.open( ( function_name+".m" ).c_str () );

  if (aux_coordinates.size () == 0){
    matlab_file << "function " << function_out << " = " << function_name << "(q,dq,ddq)\n" << endl;}
  else {
    matlab_file << "function " << function_out << " = " << function_name << "(q,dq,qaux,dqaux)\n" << endl;}

  matlab_file << "global " <<  get_Time_Symbol ( ) << ";" << endl;

  for ( int i = 0 ; i < parameters.size () ; i++ )
        matlab_file << "global " << parameters[i]-> get_name () << ";" << endl;
  for ( int i = 0 ; i < coordinates.size () ; i++ )
        matlab_file << "global " << coordinates[i]-> get_name () << ";" << endl;
  for ( int i = 0 ; i < velocities.size () ; i++ )
        matlab_file << "global " << velocities[i]-> get_name () << ";" << endl;
        
  matlab_file << "if nargin == 3" << endl;
  for ( int i = 0 ; i < accelerations.size () ; i++ )
        matlab_file << "global " << accelerations[i]-> get_name () << ";" << endl; 
  matlab_file << "end" << endl;  
        
  if (aux_coordinates.size () != 0){
    for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
        matlab_file << "global " << aux_coordinates[i]-> get_name () << ";" << endl;
  }
  if (aux_velocities.size () != 0){
    for ( int i = 0 ; i < aux_velocities.size () ; i++ )
        matlab_file << "global " << aux_velocities[i]-> get_name () << ";" << endl;
  }
  for ( int i = 0 ; i < unknowns.size () ; i++ )
        matlab_file << "global " << unknowns[i]-> get_name () << ";" << endl;
  for ( int i = 0 ; i < inputs.size () ; i++ )
        matlab_file << "global " << inputs[i]-> get_name () << ";" << endl;
  
  matlab_file <<  endl;
  
  //matlab_file << "global q;" << endl;
  for ( int i = 0 ; i < coordinates.size () ; i++ )
        matlab_file << coordinates[i]-> get_name () << " = q( " << i+1 << "); "  << endl;

  if (aux_coordinates.size () != 0){
    for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
      matlab_file << aux_coordinates[i]-> get_name () << " = qaux( " << i+1 << "); "  << endl;
  }

  for ( int i = 0 ; i < velocities.size () ; i++ )
    matlab_file << velocities[i]-> get_name () << " = dq( " << i+1 << "); "  << endl;

  if (aux_velocities.size () != 0){
    for ( int i = 0 ; i < aux_velocities.size () ; i++ )
      matlab_file << aux_velocities[i]-> get_name () << " = dqaux( " << i+1 << "); "  << endl;
  }
  matlab_file << "if nargin == 3" << endl;
  for ( int i = 0 ; i < accelerations.size () ; i++ )
    matlab_file << accelerations[i]-> get_name () << " = ddq( " << i+1 << "); "  << endl; 
  matlab_file << "end" << endl; 
  
  matlab_file <<  endl;
  
  if (atomization == YES){
    for (int i  = 0 ; i < Matrix_atom_list.nops () ; i++ ){ 
      matlab_file << Matrix_atom_list.op( i )<< " = " <<   Matrix_atom_expression_list.op( i ) << ";" << endl;
    }
  matlab_file <<  endl;    
  }
  
  matlab_file << function_out << " = " << symbolic_matrix_function << ";" << endl;
  
  matlab_file <<  endl;
  matlab_file << "%endfunction" << endl;
  matlab_file.close();
}



void System::export_function_MATLAB(string function_name, string function_out, Matrix symbolic_matrix_function){
    
  lst Matrix_atom_list, Matrix_atom_expression_list;
  export_function_MATLAB(function_name, function_out, symbolic_matrix_function,Matrix_atom_list,Matrix_atom_expression_list );

}

void System::export_function_MATLAB(string function_name, string function_out, Matrix symbolic_matrix_function,string s_in){
    
  lst Matrix_atom_list, Matrix_atom_expression_list;
  export_function_MATLAB(function_name, function_out, symbolic_matrix_function,Matrix_atom_list,Matrix_atom_expression_list,s_in );

}



void System::export_function_MATLAB_SYMPY(string function_name, string function_out, Matrix symbolic_matrix_function){

  ofstream python_file;
  
  //symbolic_matrix_function = unatomize(symbolic_matrix_function);
  
  python_file.open( ( function_name+"_python.py" ).c_str () );

  python_file << "from sympy import *" << endl;
  python_file << "from sympy.parsing.sympy_parser import parse_expr" << endl;
  python_file << "#init_printing(use_unicode=True)" << endl;
  python_file << "" << endl;
  python_file << "def simple(eq):" << endl;
  python_file << "    eq = eq.replace(\"^\", \"**\")" << endl;
  python_file << "    eq1 = parse_expr(eq)" << endl;

  if (symbolic_matrix_function.cols() == 1)
	python_file << "    eq2 = str(simplify(eq1))" << endl;		// for vectors
  else
	python_file << "    eq2 = str(simplify(eq1))[1:-1]" << endl;	//  for matrices

  python_file << "    return eq2.replace(\"**\", \"^\")" << endl;

  for ( int i = 0 ; i < symbolic_matrix_function.rows () ; i++ ){
	python_file << "b" << i << "=\" ";
	for ( int j = 0 ; j < symbolic_matrix_function.cols () - 1; j++ ){
		python_file << unatomize_ex(symbolic_matrix_function(i,j)) << " , ";
	}
	python_file << unatomize_ex( symbolic_matrix_function(i,symbolic_matrix_function.cols () - 1) )<< "\"" << endl;
  }

  python_file << "" << endl;
  for ( int i = 0 ; i < symbolic_matrix_function.rows () ; i++ )
	python_file << "b" << i << "=simple(b" << i << ")" << endl;

  python_file << "" << endl;
  python_file << "" << endl;
  python_file << "f = open(\"" << function_name+"_python_exp.m\",\"w\")" << endl;
  python_file << "f.write(\"" << function_name+"_matrix" << "=[\")" << endl;
  for ( int i = 0 ; i < symbolic_matrix_function.rows () -1; i++ ){
	python_file << "f.write(b" << i << ")" << endl;
	python_file << "f.write(\";\")" << endl; 
  }
  python_file << "f.write(b" << symbolic_matrix_function.rows () -1 << ")" << endl;
  python_file << "f.write(\"" << "];\")" << endl;
  python_file << "" << endl;
  python_file << "f.close() " << endl;
  python_file.close();

  int system_return;
  string s2="python "+function_name+"_python.py";
  system_return=system(s2.c_str());
//  s2="rm -f "+function_name+"_python.py";
//  system_return=system(s2.c_str());

  ofstream matlab_file;

  matlab_file.open( ( function_name+".m" ).c_str () );

  if (aux_coordinates.size () == 0)
    matlab_file << "function " << function_name+";" << endl << endl;

  matlab_file << "syms t real;" << endl;

  for ( int i = 0 ; i < parameters.size () ; i++ )
//        matlab_file << "global " << parameters[i]-> get_name () << ";" << endl;
        matlab_file << "syms " << parameters[i]-> get_name () << " real;" << endl;

  matlab_file << "param=[";
  for ( int i = 0 ; i < parameters.size () - 1; i++ )
        matlab_file << parameters[i]-> get_name () << ",";
  matlab_file << parameters[parameters.size () - 1]-> get_name () << "];" << endl;


  for ( int i = 0 ; i < inputs.size () ; i++ )
    matlab_file << "syms " << inputs[i]-> get_name () << " real;" << endl;
  
  matlab_file << "inputs=[";
  for ( int i = 0 ; i < inputs.size () - 1; i++ )
        matlab_file << inputs[i]-> get_name () << ",";
  matlab_file << inputs[inputs.size () - 1]-> get_name () << "];" << endl; 
  
 
/*
  for ( int i = 0 ; i < coordinates.size () ; i++ )
        matlab_file << "global " << coordinates[i]-> get_name () << ";" << endl;
  for ( int i = 0 ; i < velocities.size () ; i++ )
        matlab_file << "global " << velocities[i]-> get_name () << ";" << endl;
  if (aux_coordinates.size () != 0){
    for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
        matlab_file << "global " << aux_coordinates[i]-> get_name () << ";" << endl;
  }
  if (aux_velocities.size () != 0){
    for ( int i = 0 ; i < aux_velocities.size () ; i++ )
        matlab_file << "global " << aux_velocities[i]-> get_name () << ";" << endl;
  }
  for ( int i = 0 ; i < unknowns.size () ; i++ )
        matlab_file << "global " << unknowns[i]-> get_name () << ";" << endl;
  for ( int i = 0 ; i < inputs.size () ; i++ )
        matlab_file << "global " << inputs[i]-> get_name () << ";" << endl;
//*/

  //matlab_file << "global q;" << endl;
  for ( int i = 0 ; i < coordinates.size () ; i++ )
//        matlab_file << coordinates[i]-> get_name () << " = q( " << i+1 << "); "  << endl;
	matlab_file << "syms " << coordinates[i]-> get_name () << " real; "  << endl;
  if (aux_coordinates.size () != 0){
    for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
      matlab_file << aux_coordinates[i]-> get_name () << " = qaux( " << i+1 << "); "  << endl;
  }

  matlab_file << "q=[";
  for ( int i = 0 ; i < coordinates.size () - 1; i++ )
        matlab_file << coordinates[i]-> get_name () << ",";
  matlab_file << coordinates[coordinates.size () - 1]-> get_name () << "];" << endl;

  for ( int i = 0 ; i < velocities.size () ; i++ )
  //  	matlab_file << velocities[i]-> get_name () << " = dq( " << i+1 << "); "  << endl;
	matlab_file << "syms " << velocities[i]-> get_name () << " real; "  << endl;

  matlab_file << "dq=[";
  for ( int i = 0 ; i < velocities.size () - 1; i++ )
        matlab_file << velocities[i]-> get_name () << ",";
  matlab_file << velocities[velocities.size () - 1]-> get_name () << "];" << endl;

  for ( int i = 0 ; i < accelerations.size () ; i++ )
 //   matlab_file << accelerations[i]-> get_name () << " = ddq( " << i+1 << "); "  << endl;
	matlab_file << "syms " << accelerations[i]-> get_name () << " real; "  << endl;

  matlab_file << "ddq=[";
  for ( int i = 0 ; i < accelerations.size () - 1; i++ )
        matlab_file << accelerations[i]-> get_name () << ",";
  matlab_file << accelerations[accelerations.size () - 1]-> get_name () << "];" << endl;

  if (aux_velocities.size () != 0){
    for ( int i = 0 ; i < aux_velocities.size () ; i++ )
      matlab_file << aux_velocities[i]-> get_name () << " = dqaux( " << i+1 << "); "  << endl;
  }

  matlab_file << function_name+"_python_exp;" << endl;
  matlab_file << "%endfunction" << endl;

  matlab_file << "matlabFunction(" << function_name << "_matrix,'file','"<< function_name << "_.m','vars',{t,param,inputs,q,dq,ddq});" << endl;
  matlab_file << "exit" << endl;
  matlab_file.close();

  s2="matlab -nodesktop -r "+function_name;
  system_return=system(s2.c_str());

}


void System::export_init_function_MATLAB(){
    ofstream matlab_file;
    
    matlab_file.open ("time_init.m");
    matlab_file << "global " <<  get_Time_Symbol ( ) << ";" << endl;
    matlab_file << get_Time_Symbol ( ) << " = 0.0;" << endl;
    matlab_file.close();

    matlab_file.open ("param_init.m");
    for ( int i = 0 ; i < parameters.size () ; i++ )
        matlab_file << "global " << parameters[i]-> get_name () << ";" << endl;
    for ( int i = 0 ; i < parameters.size () ; i++ )
        matlab_file << parameters[i]-> get_name () << " = " << parameters[i]-> get_value () << ";" << endl;
    matlab_file.close();

    matlab_file.open ("param_vect_init.m");
    for ( int i = 0 ; i < parameters.size () ; i++ )
        matlab_file << "global " << parameters[i]-> get_name () << ";" << endl;
    matlab_file << "global param;" << endl;
    matlab_file << "param=[" ;
    for ( int i = 0 ; i < parameters.size ()-1 ; i++ )
        matlab_file << parameters[i]-> get_name () << "," ;
    matlab_file << parameters[parameters.size ()-1]-> get_name () ;
    matlab_file <<"]';"<< endl ;
    matlab_file.close();

    matlab_file.open ("coord_init.m");
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        matlab_file << "global " << coordinates[i]-> get_name () << ";" << endl;
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        matlab_file << coordinates[i]-> get_name () << " = " << coordinates[i]-> get_value () << ";" << endl;
    matlab_file.close();

    matlab_file.open ("coord_vect_init.m");
    for ( int i = 0 ; i < coordinates.size () ; i++ )
        matlab_file << "global " << coordinates[i]-> get_name () << ";" << endl;
    matlab_file << "global q;" << endl;
    matlab_file << "q=[" ;
    for ( int i = 0 ; i < coordinates.size ()-1 ; i++ )
        matlab_file << coordinates[i]-> get_name () << "," ;
    matlab_file << coordinates[coordinates.size ()-1]-> get_name () ;
    matlab_file <<"]';"<< endl ;
    matlab_file.close() ;

    matlab_file.open ("vel_init.m");
    for ( int i = 0 ; i < velocities.size () ; i++ )
        matlab_file << "global " << velocities[i]-> get_name () << ";" << endl;
    for ( int i = 0 ; i < velocities.size () ; i++ )
        matlab_file << velocities[i]-> get_name () << " = " << velocities[i]-> get_value () << ";" << endl;
    matlab_file.close();

    matlab_file.open ("vel_vect_init.m");
    for ( int i = 0 ; i < velocities.size () ; i++ )
        matlab_file << "global " << velocities[i]-> get_name () << ";" << endl;
    matlab_file << "global dq;" << endl;
    matlab_file << "dq=[" ;
    for ( int i = 0 ; i < velocities.size ()-1 ; i++ )
        matlab_file << velocities[i]-> get_name () << "," ;
    matlab_file << velocities[velocities.size ()-1]-> get_name () ;
    matlab_file <<"]';"<< endl;
    matlab_file.close();
    
    matlab_file.open ("acc_init.m");
    for ( int i = 0 ; i < accelerations.size () ; i++ )
        matlab_file << "global " << accelerations[i]-> get_name () << ";" << endl;
    for ( int i = 0 ; i < accelerations.size () ; i++ )
        matlab_file << accelerations[i]-> get_name () << " = " << accelerations[i]-> get_value () << ";" << endl;
    matlab_file.close();

    matlab_file.open ("acc_vect_init.m");
    for ( int i = 0 ; i < accelerations.size () ; i++ )
        matlab_file << "global " << accelerations[i]-> get_name () << ";" << endl;
    matlab_file << "global ddq;" << endl;
    matlab_file << "ddq=[" ;
    for ( int i = 0 ; i < accelerations.size ()-1 ; i++ )
        matlab_file << accelerations[i]-> get_name () << "," ;
    matlab_file <<accelerations[accelerations.size ()-1]-> get_name () ;
    matlab_file <<"]';"<< endl;
    matlab_file.close();    
    

  if ( unknowns.size () != 0 ) {	
    matlab_file.open ("unknowns_init.m");
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        matlab_file << "global " << unknowns[i]-> get_name () << ";" << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        matlab_file << unknowns[i]-> get_name () << " = " << unknowns[i]-> get_value () << ";" << endl;
    matlab_file.close();

    matlab_file.open ("unknowns_vect_init.m");
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        matlab_file << "global " << unknowns[i]-> get_name () << ";" << endl;
    matlab_file << "global unknowns;" << endl;
    matlab_file << "unknowns=[" ;
    for ( int i = 0 ; i < unknowns.size ()-1 ; i++ )
        matlab_file << unknowns[i]-> get_name () << "," ;
    matlab_file << unknowns[unknowns.size ()-1]-> get_name () ;
    matlab_file <<"]';"<< endl;
    matlab_file.close();
  }

  if ( inputs.size () != 0 ) {
    matlab_file.open ("inputs_init.m");
    for ( int i = 0 ; i < inputs.size () ; i++ )
        matlab_file << "global " << inputs[i]-> get_name () << ";" << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        matlab_file << inputs[i]-> get_name () << " = " << inputs[i]-> get_value () << ";" << endl;
    matlab_file.close();

    matlab_file.open ("inputs_vect_init.m");
    for ( int i = 0 ; i < inputs.size () ; i++ )
        matlab_file << "global " << inputs[i]-> get_name () << ";" << endl;
    matlab_file << "global inputs;" << endl;
    matlab_file << "inputs=[" ;
    for ( int i = 0 ; i < inputs.size ()-1 ; i++ )
        matlab_file << inputs[i]-> get_name () << "," ;
    matlab_file << inputs[inputs.size ()-1]-> get_name () ;
    matlab_file <<"]';"<< endl;
    matlab_file.close();
  }


  if ( aux_coordinates.size () != 0 ) {
    matlab_file.open ("auxcoord_init.m");
    for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
        matlab_file << "global " << aux_coordinates[i]-> get_name () << ";" << endl;
    for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
        matlab_file << aux_coordinates[i]-> get_name () << " = " << aux_coordinates[i]-> get_value () << ";" << endl;
    matlab_file.close();

    matlab_file.open ("auxcoord_vect_init.m");
    for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
        matlab_file << "global " << aux_coordinates[i]-> get_name () << ";" << endl;
    matlab_file << "global qaux;" << endl;
    matlab_file << "qaux=[" ;
    for ( int i = 0 ; i < aux_coordinates.size ()-1 ; i++ )
        matlab_file << aux_coordinates[i]-> get_name () << "," ;
    matlab_file << aux_coordinates[aux_coordinates.size ()-1]-> get_name () ;
    matlab_file <<"]';"<< endl ;
    matlab_file.close() ;
  }

  if ( aux_velocities.size () != 0 ) {
    matlab_file.open ("auxvel_init.m");
    for ( int i = 0 ; i < aux_velocities.size () ; i++ )
        matlab_file << "global " << aux_velocities[i]-> get_name () << ";" << endl;
    for ( int i = 0 ; i < aux_velocities.size () ; i++ )
        matlab_file << aux_velocities[i]-> get_name () << " = " << aux_velocities[i]-> get_value () << ";" << endl;
    matlab_file.close();

    matlab_file.open ("auxvel_vect_init.m");
    for ( int i = 0 ; i < aux_velocities.size () ; i++ )
        matlab_file << "global " << aux_velocities[i]-> get_name () << ";" << endl;
    matlab_file << "global dqaux;" << endl;
    matlab_file << "dqaux=[" ;
    for ( int i = 0 ; i < aux_velocities.size ()-1 ; i++ )
        matlab_file << aux_velocities[i]-> get_name () << "," ;
    matlab_file << aux_velocities[aux_velocities.size ()-1]-> get_name () ;
    matlab_file <<"]';"<< endl ;
    matlab_file.close() ;
  }
}


/*********************************************************************************************************
***************************** SYSTEM MAPLE EXPORT FUNCTIONS *********************************************
*********************************************************************************************************/

void System::export_Matrix_MAPLE ( string function_name , vector < string > matrixes_names, vector < Matrix * > Exported_Matrixes, vector < string > Argument_Standard, vector < string > Argument_Matrixes, int order, int symmetric) {

    /* ----------------------------------------*/
    /* Begin of the Maple file creation procedure*/
    /* ----------------------------------------*/

    try { if ( (order != CMO) && (order !=RMO)  ) throw 1; }
    catch ( int e ) { outError ( "ERR -  Last parameter (int order) must be CMO  or RMO" ); }

    extern int C_EXPORT_AS_PROCEDURE;
    ofstream cout;

    if ( C_EXPORT_AS_PROCEDURE != 1 ) { //No procedure

        for ( int z = 0 ; z < Exported_Matrixes.size () ; z++ )
            {
            string file_name =  Exported_Matrixes[z] -> get_name ();

            string matrix_name;
            if(matrixes_names.size () > 0) {matrix_name = matrixes_names[z];}
            else {matrix_name =  "_"+Exported_Matrixes[z] -> get_name ();}

            cout.open ( ( file_name+".mpl" ).c_str () );
            //*************************************************************************************************
            //    cout << csrc_double ; /* ADDED to solve csrc_double */
            //*************************************************************************************************
            cout << dflt;
            set_print_func<power, print_myformat>(print_power_as_myformat);
            set_print_func<numeric, print_myformat>(print_numeric_as_myformat);
            //*************************************************************************************************

            cout << "with(codegen);" << endl;
            cout << "ssystem(\"rm -f ./" << file_name+"_maple_include.c\");" << endl;
            cout << "p:=proc()" << endl;

            cout << "local " << matrix_name+";" << endl;

            cout << "" << endl;

            cout <<  matrix_name+":= array(0 .. " <<  ( Exported_Matrixes[z]->rows() )* ( Exported_Matrixes[z]->cols() ) -1 << ");" << endl;

            int k=0;

            if (order==CMO)
                {
            /* Matrix written in Column-major order */
                for ( int j = 0 ; j < ( Exported_Matrixes[z]->cols() ) ; j++ )
                    for ( int i = 0 ; i < ( Exported_Matrixes[z]->rows() ) ; i++ ){
                       if( symmetric == 1){ 
                          if (i>=j){
                              cout << matrix_name << "[" << k << "]:=" ;  (( * Exported_Matrixes[z] ) ( i , j )).print(print_myformat(cout)); cout << ";" << endl;
                            }
                            else{
                              cout << matrix_name << "[" << k << "]:=" << matrix_name << "[" << j+i * Exported_Matrixes[z]->rows() << "];"<< endl;
                            }
                        }
                        else{
                           cout << matrix_name << "[" << k << "]:=" ;  (( * Exported_Matrixes[z] ) ( i , j )).print(print_myformat(cout)); cout << ";" << endl;
                        }
                        k++;
                    }
                }
            else
                {
                for ( int i = 0 ; i <  ( Exported_Matrixes[z]->rows() ); i++ )
                    for ( int j = 0 ; j < ( Exported_Matrixes[z]->cols() ) ; j++ ){
                       if( symmetric == 1){ 
                          if (j>=i){
                              cout << matrix_name << "[" << k << "]:=" ;  (( * Exported_Matrixes[z] ) ( i , j )).print(print_myformat(cout)); cout << ";" << endl;
                            }
                          else{
                            cout << matrix_name << "[" << k << "]:=" << matrix_name << "[" << i+j * Exported_Matrixes[z]->cols() << "];"<< endl;
                            }
                        }
                        else {
                           cout << matrix_name << "[" << k << "]:=" ;  (( * Exported_Matrixes[z] ) ( i , j )).print(print_myformat(cout)); cout << ";" << endl;
                        }
                        k++;
                    }
                }

            cout << "" << endl;

            //cout << "return;" << endl;    
            cout << "return " << matrix_name << ";" << endl;

            cout << "end proc;" << endl;
            cout << "C(p, optimized, precision=double, filename = \"./"<< file_name+"_maple_include.c\");" << endl;

            cout.close () ;

        }
    }

    else //Export like procedure
    {
        cout.open ( ( function_name+".mpl" ).c_str () );
        //*************************************************************************************************
        //    cout << csrc_double ; /* ADDED to solve csrc_double */
        //*************************************************************************************************
        cout << dflt;
        set_print_func<power, print_myformat>(print_power_as_myformat);
        set_print_func<numeric, print_myformat>(print_numeric_as_myformat);
        //*************************************************************************************************

        cout << "with(codegen);" << endl;
        cout << "ssystem(\"rm -f ./" << function_name+"_maple_include.c\");" << endl;
        cout << "p:=proc()" << endl;

        for ( int i = 0 ; i < Exported_Matrixes.size () ; i++ ){
            string matrix_name =  "_"+Exported_Matrixes[i] -> get_name ();
            cout << "local " << matrix_name+";" << endl;
        }

        cout << "" << endl;
        string matrix_name;
        
        for ( int z = 0 ; z < Exported_Matrixes.size () ; z++ )
            {

            matrix_name =  "_"+Exported_Matrixes[z] -> get_name ();

            cout <<  matrix_name+":= array(0 .. " <<  ( Exported_Matrixes[z]->rows() )* ( Exported_Matrixes[z]->cols() ) -1 << ");" << endl;

            int k=0;

            if (order==CMO)
            {
            /* Matrix written in Column-major order */
                for ( int j = 0 ; j < ( Exported_Matrixes[z]->cols() ) ; j++ )
                    for ( int i = 0 ; i < ( Exported_Matrixes[z]->rows() ) ; i++ ){
                        //cout << matrix_name << "[" << k << "]:=" <<  ( * Exported_Matrixes[z] ) ( i , j ) << ";" << endl;
                        if( symmetric == 1){ 
                          if (i>=j){
                              cout << matrix_name << "[" << k << "]:=" ;  (( * Exported_Matrixes[z] ) ( i , j )).print(print_myformat(cout)); cout << ";" << endl;
                            }
                            else{
                              cout << matrix_name << "[" << k << "]:=" << matrix_name << "[" << i+j * Exported_Matrixes[z]->rows() << "];"<< endl;
                            }
                        }
                        else{
                           cout << matrix_name << "[" << k << "]:=" ;  (( * Exported_Matrixes[z] ) ( i , j )).print(print_myformat(cout)); cout << ";" << endl;
                        }
                        k++;
                    }
            }
            else
            {
                for ( int i = 0 ; i <  ( Exported_Matrixes[z]->rows() ); i++ )
                    for ( int j = 0 ; j < ( Exported_Matrixes[z]->cols() ) ; j++ ){
                       if( symmetric == 1){ 
                          if (j>=i){
                              cout << matrix_name << "[" << k << "]:=" ;  (( * Exported_Matrixes[z] ) ( i , j )).print(print_myformat(cout)); cout << ";" << endl;
                            }
                          else{
                            cout << matrix_name << "[" << k << "]:=" << matrix_name << "[" << i+j * Exported_Matrixes[z]->cols() << "];"<< endl;
                            }
                        }
                        else {
                           cout << matrix_name << "[" << k << "]:=" ;  (( * Exported_Matrixes[z] ) ( i , j )).print(print_myformat(cout)); cout << ";" << endl;
                        }
                        k++;
                    }
            }

            cout << "" << endl;
            }
        //cout << "return;" << endl;   
        cout << "return " << matrix_name << ";" << endl;
        cout << "end proc;" << endl;
        cout << "C(p, optimized, precision=double, filename = \"./"<< function_name+"_maple_include.c\");" << endl;

        cout.close () ;
    }
        /* ----------------------------------------*/
        /* End of the Maple file creation procedure*/
        /* ----------------------------------------*/

//*************************************************************************************************

    /* ----------------------------------------*/
    /* Begin of the C file creation procedure*/
    /* ----------------------------------------*/
    /*
      vector < symbol_numeric * > Coordinates 		= sys.get_Coordinates();
      vector < symbol_numeric * > Velocities 			= sys.get_Velocities();
      vector < symbol_numeric * > Accelerations		= sys.get_Accelerations();
      vector < symbol_numeric * > Parameters 	    = sys.get_Parameters();
      vector < symbol_numeric * > Joint_Unknowns 	= sys.get_Joint_Unknowns();
      vector < symbol_numeric * > Inputs        	= sys.get_Inputs();
    */
    string aux_matrix_arguments;
    make_argument_matrixes_list (Argument_Matrixes, aux_matrix_arguments);

    string aux_standard_arguments;
    make_argument_standard_list (Argument_Standard, aux_standard_arguments);

    // ********
    // FUNCTION
    // ********
    if ( C_EXPORT_AS_PROCEDURE != 1 ) {

        for ( int z = 0 ; z < Exported_Matrixes.size () ; z++ ){

            string file_name =  Exported_Matrixes[z] -> get_name ();

            string matrix_name;
            if(matrixes_names.size () > 0) {matrix_name = matrixes_names[z];}
            else {matrix_name =  "_"+Exported_Matrixes[z] -> get_name ();}


            load_includes_defines(file_name, order);

            cout.open ( ( file_name+".c" ).c_str () , ios::app);
            cout << csrc_double ;
            cout << "double * " << matrix_name << " = NULL;" << endl;

            cout << "void Init"<< matrix_name << " ( ) " << endl;
            cout << " {" << endl;
            cout << "    " << matrix_name << " = malloc ( "<< file_name << "_n_rows * "<< file_name << "_n_cols * sizeof(double) );" << endl;

            cout << "  {int i;" << endl;
            cout << "  for ( i = 0 ; i < " << file_name << "_n_rows * " << file_name << "_n_cols ; i++ ) {" << matrix_name << "[i]=0.0;}" << endl;
            cout << "  }" << endl;
            cout << " }" << endl;

            cout << "" << endl;
            cout << "void Done"<< matrix_name << " ( ) " << endl;
            cout << "{" << endl;
            cout << "if (" << matrix_name << " != NULL) " << endl;
            cout << "free (" << matrix_name << " ); " << endl;
            cout << matrix_name << " = NULL; " << endl;
            cout << "}" << endl;
            cout << "" << endl;
            cout << "" << endl;


            cout << "double * " << file_name << " ()" << endl;

            cout << "{" << endl;
            cout << "if ( " << matrix_name << " == NULL )" << endl;
            cout << " {" << endl;
            cout << "    " << matrix_name << " = malloc ( "<< file_name << "_n_rows * "<< file_name << "_n_cols * sizeof(double) );" << endl;
            cout << "  {int i;" << endl;
            cout << "  for ( i = 0 ; i < " << file_name << "_n_rows * " << file_name << "_n_cols ; i++ ) {" << matrix_name << "[i]=0.0;}" << endl;
            cout << "  }" << endl;
            cout << " }" << endl;

            cout << "{" << endl;
            cout << "#include \"" << file_name+"_maple_include.c\"" << endl;
            cout << "}" << endl;

            cout << "return " << matrix_name << ";" << endl;
            cout << "}" << endl;
            cout.close () ;
            /* ----------------------------------------*/
            /* End of the C file creation procedure*/
            /* ----------------------------------------*/

            /* ----------------------------------------*/
            /* Begin of the H file creation procedure*/
            /* ----------------------------------------*/
            cout.open ( ( file_name+".h" ).c_str () );
            if ( 0 )
                cout << "extern double * " << file_name << " ( double * " << matrix_name << " );" << endl;
            else {
            cout << "#define " << file_name << "_n_rows " << ( Exported_Matrixes[z]->rows() ) << endl;
            cout << "#define " << file_name << "_n_cols " << ( Exported_Matrixes[z]->cols() ) << endl;
            cout << "extern double * " << matrix_name << ";" << endl;
            cout << "extern void Init"<< matrix_name << " ( ); " << endl;
            cout << "extern void Done"<< matrix_name << " ( ); " << endl;
            cout << "extern double * " << file_name << " ( ) ;" << endl;
            }
            cout.close () ;
            /* ----------------------------------------*/
            /* End of the H file creation procedure*/
            /* ----------------------------------------*/
        }

    }
    else{

        load_includes_defines(function_name, order);

        cout.open ( ( function_name+".c" ).c_str () , ios::app);
        cout << csrc_double ;
        cout << "" << endl;

        for ( int z = 0 ; z < Exported_Matrixes.size () ; z++ ){
            string matrix_name;
            if(matrixes_names.size () > 0) {matrix_name = matrixes_names[z];}
            else {matrix_name =  "_"+Exported_Matrixes[z] -> get_name ();}
            cout << "double * " << matrix_name << " = NULL;" << endl;

            string file_name =  Exported_Matrixes[z] -> get_name ();

            cout << "void Init"<< matrix_name << " ( double * " << matrix_name << " ) " << endl;
            cout << "{" << endl;
            cout << "    " << matrix_name << " = malloc ( "<< file_name << "_n_rows * "<< file_name << "_n_cols * sizeof(double) );" << endl;
            cout << "  {int i;" << endl;
            cout << "  for ( i = 0 ; i < " << file_name << "_n_rows * " << file_name << "_n_cols ; i++ ) {" << matrix_name << "[i]=0.0;}" << endl;
            cout << "  }" << endl;
            cout << "}" << endl;

            cout << "" << endl;
            cout << "void Done"<< matrix_name << " ( double * " << matrix_name << " ) " << endl;
            cout << "{" << endl;
            cout << "if (" << matrix_name << " != NULL) " << endl;
            cout << "free (" << matrix_name << " ); " << endl;
            cout << matrix_name << " = NULL; " << endl;
            cout << "}" << endl;
            cout << "" << endl;
            cout << "" << endl;
        }

        cout << "" << endl;

        if (aux_standard_arguments.length() > 0 && aux_matrix_arguments.length() > 0)
                cout << "void "<< function_name << " ( " << aux_standard_arguments << " , " << aux_matrix_arguments << " )" << endl;
        else {
            cout << "void "<< function_name << " ( " << aux_standard_arguments << aux_matrix_arguments << " )" << endl;
        }
        cout << "{" << endl;
        cout << "#include \"" << function_name+"_maple_include.c\"" << endl;
        cout << "}" << endl;
        cout.close () ;

        /* ----------------------------------------*/
        /* End of the C file creation procedure*/
        /* ----------------------------------------*/

        /* ----------------------------------------*/
        /* Begin of the H file creation procedure*/
        /* ----------------------------------------*/

        cout.open ( ( function_name+".h" ).c_str () );

        for ( int z = 0 ; z < Exported_Matrixes.size () ; z++ ){

            string file_name =  Exported_Matrixes[z] -> get_name ();
            string matrix_name;
            if(matrixes_names.size () > 0) {matrix_name = matrixes_names[z];}
            else {matrix_name =  "_"+Exported_Matrixes[z] -> get_name ();}

            if ( 0 )
                cout << "extern double * " << file_name << " ( double * " << matrix_name << " );" << endl;
            else {
                cout << "#define " << file_name << "_n_rows " << ( Exported_Matrixes[z]->rows() ) << endl;
                cout << "#define " << file_name << "_n_cols " << ( Exported_Matrixes[z]->cols() ) << endl;
                cout << "extern double * " << matrix_name << ";" << endl;
                cout << "extern void Init"<< matrix_name << " ( double * " << matrix_name << " ); " << endl;
                cout << "extern void Done"<< matrix_name << " ( double * " << matrix_name << " ); " << endl;
            }
        }

        if (aux_standard_arguments.length() > 0 && aux_matrix_arguments.length() > 0)
            cout << "extern void "<< function_name << " ( " << aux_standard_arguments << " , " << aux_matrix_arguments << " ) ;" << endl;
        else {
            cout << "extern void "<< function_name << " ( " << aux_standard_arguments << aux_matrix_arguments << " ) ;" << endl;
        }
        cout.close () ;
        /* ----------------------------------------*/
        /* End of the H file creation procedure*/
        /* ----------------------------------------*/

    }
    int systemRet = system("sed -i 's/+-/-/g' *.mpl");
}

//**************************************************************************************************
void System::export_Matrix_MAPLE ( string function_name , vector < string > matrixes_names, vector < Matrix * > Exported_Matrixes, vector < string > Argument_Standard, vector < string > Argument_Matrixes, int order) {
    export_Matrix_MAPLE(function_name, matrixes_names,Exported_Matrixes , Argument_Standard, Argument_Matrixes, order, 0);
}

void System::export_Matrix_MAPLE( string function_name , vector < Matrix * > Computed_Matrixes, vector < string > Argument_Standard, vector < string > Argument_Matrixes, int order,int symmetric) {
    vector < string > matrixes_names;
    export_Matrix_MAPLE(function_name, matrixes_names, Computed_Matrixes, Argument_Standard, Argument_Matrixes, order, symmetric);
}
void System::export_Matrix_MAPLE( string function_name , vector < Matrix * > Computed_Matrixes, vector < string > Argument_Standard, vector < string > Argument_Matrixes, int order) {
    vector < string > matrixes_names;
    export_Matrix_MAPLE(function_name, matrixes_names, Computed_Matrixes, Argument_Standard, Argument_Matrixes, order,0);
}

void System::export_Matrix_MAPLE( string function_name , vector < Matrix * > Computed_Matrixes, int order, int symmetric){
    vector < string > matrixes_names;
    vector < string > Argument_Standard;
    vector < string > Argument_Matrixes;
    export_Matrix_MAPLE(function_name, matrixes_names, Computed_Matrixes, Argument_Standard, Argument_Matrixes, order, symmetric);
}
void System::export_Matrix_MAPLE( string function_name , vector < Matrix * > Computed_Matrixes, int order){
    vector < string > matrixes_names;
    vector < string > Argument_Standard;
    vector < string > Argument_Matrixes;
    export_Matrix_MAPLE(function_name, matrixes_names, Computed_Matrixes, Argument_Standard, Argument_Matrixes, order,0);
}

void System::export_Matrix_MAPLE( string function_name , vector < Matrix * > Computed_Matrixes, vector < string > Argument_Standard, int order, int symmetric){
    vector < string > matrixes_names;
    vector < string > Argument_Matrixes;
    export_Matrix_MAPLE(function_name, matrixes_names, Computed_Matrixes, Argument_Standard, Argument_Matrixes, order, symmetric);
}
void System::export_Matrix_MAPLE( string function_name , vector < Matrix * > Computed_Matrixes, vector < string > Argument_Standard, int order){
    vector < string > matrixes_names;
    vector < string > Argument_Matrixes;
    export_Matrix_MAPLE(function_name, matrixes_names, Computed_Matrixes, Argument_Standard, Argument_Matrixes, order,0);
}

void System::export_Matrix_MAPLE( string function_name , string matrix_name , Matrix _Matrix, int order, int symmetric){

    vector < string > matrixes_names;
    matrixes_names.push_back( matrix_name );

    vector < Matrix * > Computed_Matrixes;
    Computed_Matrixes.push_back( &_Matrix );

    vector < string > Argument_Standard;
    vector < string > Argument_Matrixes;
    Argument_Matrixes.push_back( matrix_name );
    export_Matrix_MAPLE(function_name, matrixes_names, Computed_Matrixes, Argument_Standard, Argument_Matrixes, order, symmetric);
}
void System::export_Matrix_MAPLE( string function_name , string matrix_name , Matrix _Matrix, int order){
    vector < string > matrixes_names;
    matrixes_names.push_back( matrix_name );

    vector < Matrix * > Computed_Matrixes;
    Computed_Matrixes.push_back( &_Matrix );

    vector < string > Argument_Standard;
    vector < string > Argument_Matrixes;
    Argument_Matrixes.push_back( matrix_name );
    export_Matrix_MAPLE(function_name, matrixes_names, Computed_Matrixes, Argument_Standard, Argument_Matrixes, order,0);
}



void  System::load_includes_defines(string function_name, int order) {
/*
  vector < symbol_numeric * > Coordinates 		= sys.get_Coordinates();
  vector < symbol_numeric * > Velocities 		= sys.get_Velocities();
  vector < symbol_numeric * > Accelerations		= sys.get_Accelerations();
  vector < symbol_numeric * > Parameters 	    = sys.get_Parameters();
  vector < symbol_numeric * > Joint_Unknowns 	= sys.get_Joint_Unknowns();
  vector < symbol_numeric * > Inputs        	= sys.get_Inputs();
*/
 ofstream cout;
 cout.open ( ( function_name+".c" ).c_str () , ios::out);
    cout << csrc_double ;
    cout << "/*----------"<< function_name <<".c lib3D_MEC exported-----------*/" << endl << endl;
    if ( order == CMO )
    cout << "/* CMO exported */" << endl << endl;
    else {
    cout << "/* RMO exported */" << endl << endl;
    }
    cout << "#include <stdio.h>" << endl;
    cout << "#include <math.h>" << endl;
    cout << "#include <stdlib.h>" << endl << endl;

    cout << "#include \"time_3D_mec.h\"" << endl;
    cout << "#include \"gen_coord.h\"" << endl;
    cout << "#include \"gen_vel.h\"" << endl;
    cout << "#include \"gen_accel.h\"" << endl;
    if (aux_coordinates.size()> 0 ){
        cout << "#include \"gen_auxcoord.h\"" << endl;
        cout << "#include \"gen_auxvel.h\"" << endl;
        cout << "#include \"gen_auxaccel.h\"" << endl;
    }
    cout << "#include \"param.h\"" << endl;
    cout << "#include \"unknowns.h\"" << endl;
    cout << "#include \"inputs.h\"" << endl << endl;

    cout << "#include \"step.h\"" << endl << endl;

    cout << "#include \""<< function_name << ".h\"" << endl << endl;


    for ( int i = 0 ; i < coordinates.size () ; i++ )
        cout << "#define " << coordinates[i]-> get_name () << " q[ " << i << " ]" << endl;
    for ( int i = 0 ; i < velocities.size () ; i++ )
        cout << "#define " << velocities[i]-> get_name () << " dq[ " << i << " ]" << endl;
    for ( int i = 0 ; i < accelerations.size () ; i++ )
        cout << "#define " << accelerations[i]-> get_name () << " ddq[ " << i << " ]" << endl;
    if (aux_coordinates.size()> 0 ){    
        for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
            cout << "#define " << aux_coordinates[i]-> get_name () << " qaux[ " << i << " ]" << endl;
        for ( int i = 0 ; i < aux_velocities.size () ; i++ )
            cout << "#define " << aux_velocities[i]-> get_name () << " dqaux[ " << i << " ]" << endl;
        for ( int i = 0 ; i < aux_accelerations.size () ; i++ )
            cout << "#define " << aux_accelerations[i]-> get_name () << " ddqaux[ " << i << " ]" << endl;
     }       
        
    for ( int i = 0 ; i < parameters.size () ; i++ )
        cout << "#define " << parameters[i]-> get_name () << " param[ " << i << " ]" << endl;
    for ( int i = 0 ; i < unknowns.size () ; i++ )
        cout << "#define " << unknowns[i]-> get_name () << " unknowns[ " << i << " ]" << endl;
    for ( int i = 0 ; i < inputs.size () ; i++ )
        cout << "#define " << inputs[i]-> get_name () << " inputs[ " << i << " ]" << endl;
}


void System::make_argument_standard_list ( vector < string > Argument_Standard, string &aux) {
    for ( int i = 0 ; i < Argument_Standard.size () ; i++ ){
     if (Argument_Standard[i] == "coordinates")  { if (aux.length() > 0){aux=aux+", ";} aux = aux+"double * q ";}
     if (Argument_Standard[i] == "velocities")   { if (aux.length() > 0){aux=aux+", ";} aux = aux+"double * dq ";}
     if (Argument_Standard[i] == "accelerations"){ if (aux.length() > 0){aux=aux+", ";} aux = aux+"double * ddq ";}
     if (Argument_Standard[i] == "aux_coordinates")  { if (aux.length() > 0){aux=aux+", ";} aux = aux+"double * qaux ";}
     if (Argument_Standard[i] == "aux_velocities")   { if (aux.length() > 0){aux=aux+", ";} aux = aux+"double * dqaux ";}
     if (Argument_Standard[i] == "aux_accelerations"){ if (aux.length() > 0){aux=aux+", ";} aux = aux+"double * ddqaux ";}
     if (Argument_Standard[i] == "param")        { if (aux.length() > 0){aux=aux+", ";} aux = aux+"double * param ";}
     if (Argument_Standard[i] == "inputs")       { if (aux.length() > 0){aux=aux+", ";} aux = aux+"double * inputs ";}
     if (Argument_Standard[i] == "unknowns")     { if (aux.length() > 0){aux=aux+", ";} aux = aux+"double * unknowns ";}
    }
}

void System::make_argument_matrixes_list ( vector < string > Argument_Matrixes, string &aux) {
    for ( int i = 0 ; i < Argument_Matrixes.size () ; i++ ){
     if (aux.length() > 0){aux=aux+", ";} 
     aux = aux+"double * "+Argument_Matrixes[i]+" ";
    }
}


/*********************************************************************************************************
***************************************** DEFINE EXPORT FUNCTIONS ****************************************
*********************************************************************************************************/
void System::export_defines ( void ) {
    ofstream defines_h;
    defines_h.open("./defines.h", ios::out);
    vector < symbol_numeric * > Joint_Unknowns = get_Joint_Unknowns();
    vector < symbol_numeric * > Inputs = get_Inputs();
    Matrix Phi   = *get_Matrix( "Phi" );
    //defines_h  << "#include \"defines_extra.h\"" <<endl;
    defines_h  << "#define NEWTON_RAPHSON_TOLERANCE 1.0e-8 " <<endl;
    if (Joint_Unknowns.size() > 0){     
        defines_h  << "#define UNKNOWNS" <<endl;
    }
    if (Inputs.size() > 0){     
        defines_h  << "#define INPUTS" <<endl;
    } 
    if (Phi.rows() > 0){     
        defines_h  << "#define PHI" <<endl;
    } 
    defines_h.close();

    ofstream external_def_h;
    external_def_h.open("./external_def.h", ios::out);
    defines_h  << "/*---------begin Defines extra---------*/" <<endl;
    external_def_h.close();
}
/*********************************************************************************************************
***************************** GRAPHVIZ DOT EXPORT FUNCTIONS *********************************************
*********************************************************************************************************/
void System::export_Graphviz_dot ( void ) {
    /*---------begin  Graphviz export---------*/

    vector < Base * > Bases = get_Bases (  );

    string sub_str1="_";
    string sub_str2="\\_";

    ofstream dot_file;
    dot_file.open("base_diagram.dot", ios::out);
    dot_file << "/*---------begin  Graphviz dot output---------*/" << endl;

    dot_file << "digraph G { \n node [shape=circle]" << endl;

    for (int i=1; i < Bases.size() ; ++i){
        if (i == 1)
            {dot_file<<"xyz";}
        else
        {
            string s1=(Bases[i]->get_Previous_Base ( ))->get_name();
            dot_file << s1 ;
        }

        //  dot_file << " -> " << Bases[i]->get_name();
        dot_file << " -> \"" << Bases[i]->get_name()<<"\"";
        dot_file << " [label=\"" << "[" <<
        Bases[i]->get_Rotation_Tupla ( )(0,0) << ";" <<
        Bases[i]->get_Rotation_Tupla ( )(1,0) << ";" <<
        Bases[i]->get_Rotation_Tupla ( )(2,0) << ";" <<
        Bases[i]->get_Rotation_Angle ( ) << "]" <<
        "\"]" << endl;
    }

    dot_file << "}" << endl;

    dot_file << "/*---------end  Graphviz dot output---------*/" << endl;
    dot_file.close();

    ofstream psfrag_file;
    psfrag_file.open("./base_diagram.psfrag", ios::out);
    psfrag_file << "%---------begin  PSfrag substitutions for Graphviz dot output---------" << endl;


    psfrag_file << "\\psfrag{xyz}{$xyz$}"<< endl;

    for (int i=1; i < Bases.size() ; ++i)
        {
        string s1=Bases[i]->get_name();  

        size_t pos=s1.find(sub_str1,0);
        while(pos <= s1.size()) {
            s1.replace(pos, 1, sub_str2);
            pos++;
            pos = s1.find(sub_str1,pos+1);
        }

        psfrag_file << "\\psfrag{" << s1 <<"}{" << s1 << "}"<< endl;

        psfrag_file << " \\psfrag{" << "[" <<
        Bases[i]->get_Rotation_Tupla ( )(0,0) << ";" <<
        Bases[i]->get_Rotation_Tupla ( )(1,0) << ";" <<
        Bases[i]->get_Rotation_Tupla ( )(2,0) << ";" <<
        Bases[i]->get_Rotation_Angle ( ) << "]}{$\\left[" << latex <<
        Bases[i]->get_Rotation_Tupla ( )(0,0) << ";" <<
        Bases[i]->get_Rotation_Tupla ( )(1,0) << ";" <<
        Bases[i]->get_Rotation_Tupla ( )(2,0) << ";" <<
        Bases[i]->get_Rotation_Angle ( ) << dflt << "\\right]$}" << endl;
        }

    psfrag_file << "%---------end  PSfrag substitutions for Graphviz dot output---------" << endl;
    psfrag_file.close();



    //----------------------------------

    vector < Point * > Points = get_Points (  );

    //ofstream dot_file;
    dot_file.open("point_diagram.dot", ios::out);
    dot_file << "/*---------begin  Graphviz dot output---------*/" << endl;

    dot_file << "digraph G { \n node [shape=ellipse]" << endl;

    for (int i=1; i < Points.size() ; ++i)
        {
        if (Points[i]->get_Previous_Point ( ) !=NULL)
            {
            string s1=(Points[i]->get_Previous_Point ( ))->get_name();
            dot_file << s1 ;
            }
        else
            {dot_file<<"O";};
        dot_file << " -> \"" << Points[i]->get_name()<<"\"";
        dot_file << " [label=\"" << "[" <<
        (*(Points[i]->get_Position_Vector ( )))(0,0) << ";" <<
        (*(Points[i]->get_Position_Vector ( )))(1,0) << ";" <<
        (*(Points[i]->get_Position_Vector ( )))(2,0) << "]_" <<
        Points[i]->get_Position_Vector ( )->get_Base ()->get_name() <<
        "\"]" << endl;
        }


    dot_file << "}" << endl;

    dot_file << "/*---------end  Graphviz dot output---------*/" << endl;
    dot_file.close();

    //ofstream psfrag_file;
    psfrag_file.open("./point_diagram.psfrag", ios::out);
    psfrag_file << "%---------begin  PSfrag substitutions for Graphviz dot output---------" << endl;

    psfrag_file << "\\psfrag{O}{O}"<< endl;

    for (int i=1; i < Points.size() ; ++i)
        {
        string s1=Points[i]->get_name();

        size_t pos=s1.find(sub_str1,0);
        while(pos <= s1.size()) {
            s1.replace(pos, 1, sub_str2);
            pos++;
            pos = s1.find(sub_str1,pos+1);
        }

        psfrag_file << "\\psfrag{" << s1 <<"}{" << s1 << "}"<< endl;

        psfrag_file << " \\psfrag{" << "[" <<
        (*(Points[i]->get_Position_Vector ( )))(0,0) << ";" <<
        (*(Points[i]->get_Position_Vector ( )))(1,0) << ";" <<
        (*(Points[i]->get_Position_Vector ( )))(2,0) << "]_" <<
        Points[i]->get_Position_Vector( )->get_Base()->get_name() << "}{$\\left[" << latex <<
        (*(Points[i]->get_Position_Vector ( )))(0,0) << "," <<
        (*(Points[i]->get_Position_Vector ( )))(1,0) << "," <<
        (*(Points[i]->get_Position_Vector ( )))(2,0) << "\\right]_{" <<
        Points[i]->get_Position_Vector( )->get_Base()->get_name() << dflt << "}$}" << endl;
        }

    psfrag_file << "%---------end  PSfrag substitutions for Graphviz dot output---------" << endl;
    psfrag_file.close();



    //----------------------------------

    vector < Frame * > Frames = get_Frames (  );

    //ofstream dot_file;
    dot_file.open("frame_diagram.dot", ios::out);
    dot_file << "/*---------begin  Graphviz dot output---------*/" << endl;

    dot_file << "digraph G { "<< endl;
    dot_file << "node [shape=record]" << endl;

    for (int i=0; i < Frames.size() ; ++i)
        {
        if (i == 0)
            {
            dot_file<< "struct" << i << " [shape=record, label=\"{ abs |{ O| xyz }}\"];" << endl;
            }
        else
            {
            string s1 = Frames[i]->get_name();
            string s2 = Frames[i]->get_Point()->get_name();
            string s3 = Frames[i]->get_Base()->get_name();
            dot_file<< "struct" << i << " [shape=record, label=\"{ " << s1 << "|{ "<< s2 << "|" << s3 << " }}\"];" << endl;
            }
        }

    dot_file << "}" << endl;

    dot_file << "/*---------end  Graphviz dot output---------*/" << endl;
    dot_file.close();

    //ofstream psfrag_file;
    psfrag_file.open("./frame_diagram.psfrag", ios::out);
    psfrag_file << "%---------begin  PSfrag substitutions for Graphviz dot output---------" << endl;

    psfrag_file << "\\psfrag{XYZ}{$XYZ$}"<< endl;


    for (int i=0; i < Frames.size() ; ++i)
        {
        if (i == 0)
            {
            psfrag_file << "\\psfrag{abs}{abs}" << endl;
            psfrag_file << "\\psfrag{O}{O}" << endl;
            psfrag_file << "\\psfrag{xyz}{xyz}" << endl;
            }
        else
            {
            string s1 = Frames[i]->get_name();
            string s3 = Frames[i]->get_Point()->get_name();
            string s2 = Frames[i]->get_Base()->get_name();


            size_t pos=s1.find(sub_str1,0);
            while(pos <= s1.size()) {
                s1.replace(pos, 1, sub_str2);
                pos++;
                pos = s1.find(sub_str1,pos+1);
            }
            pos=s2.find(sub_str1,0);
            while(pos <= s2.size()) {
                s2.replace(pos, 1, sub_str2);
                pos++;
                pos = s2.find(sub_str1,pos+1);
            }
            pos=s3.find(sub_str1,0);
            while(pos <= s3.size()) {
                s3.replace(pos, 1, sub_str2);
                pos++;
                pos = s3.find(sub_str1,pos+1);
            }
            psfrag_file << "\\psfrag{" << s1 <<"}{" << s1 << "}"<< endl;
            psfrag_file << "\\psfrag{" << s2 <<"}{" << s2 << "}"<< endl;
            psfrag_file << "\\psfrag{" << s3 <<"}{" << s3 << "}"<< endl;
            }
        }

    for (int i=1; i < Bases.size() ; ++i)
         {
        string s1=Bases[i]->get_name();
        size_t pos=s1.find(sub_str1,0);

        while(pos <= s1.size()) {
            s1.replace(pos, 1, sub_str2);
            pos++;
            pos = s1.find(sub_str1,pos+1);
        }

        psfrag_file << "\\psfrag{" << s1 <<"}{" << s1 << "}"<< endl;

        psfrag_file << " \\psfrag{" << "[" <<
        Bases[i]->get_Rotation_Tupla ( )(0,0) << ";" <<
        Bases[i]->get_Rotation_Tupla ( )(1,0) << ";" <<
        Bases[i]->get_Rotation_Tupla ( )(2,0) << ";" <<
        Bases[i]->get_Rotation_Angle ( ) << "]}{$\\left[" << latex <<
        Bases[i]->get_Rotation_Tupla ( )(0,0) << ";" <<
        Bases[i]->get_Rotation_Tupla ( )(1,0) << ";" <<
        Bases[i]->get_Rotation_Tupla ( )(2,0) << ";" <<
        Bases[i]->get_Rotation_Angle ( ) << dflt << "\\right]$}" << endl;
        }

    psfrag_file << "%---------end  PSfrag substitutions for Graphviz dot output---------" << endl;
    psfrag_file.close();
}

/*---------end  Graphviz export---------*/


/*********************************************************************************************************
***************************** MATLAB ENVIRONMENT EXPORT FUNCTIONS ****************************************
*********************************************************************************************************/

void System::export_environment_m ( void ) {
/*---------begin write q, dq, ddq, epsilon, parameters to environment.m---------*/


    ofstream environment_file;
    environment_file.open("./environment.m", ios::out);

    environment_file <<  "%------------ Coordinates -------------------"  <<endl;

    for (int i=0; i < coordinates.size() ; ++i)
        {
            environment_file << *coordinates[i] << "=" << coordinates[i]->get_value() << ";" <<endl;
        }

    environment_file <<  "%------------ Velocities -------------------"  <<endl;

    for (int i=0; i < velocities.size() ; ++i)
        {
            environment_file << *velocities[i] << "=" << velocities[i]->get_value() << ";" <<endl;
        }
        
    environment_file <<  "%------------ Acelerations -------------------"  <<endl;

    for (int i=0; i < accelerations.size() ; ++i)
        {
            environment_file << *accelerations[i] << "=" << accelerations[i]->get_value() << ";" <<endl;
        }       

    environment_file <<  "%------------ Auxiliar Coordinates -------------------"  <<endl;

    for (int i=0; i < aux_coordinates.size() ; ++i)
        {
            environment_file << *aux_coordinates[i] << "=" << aux_coordinates[i]->get_value() << ";" <<endl;
        }

    environment_file <<  "%------------ Auxiliar Velocities -------------------"  <<endl;

    for (int i=0; i < aux_velocities.size() ; ++i)
        {
            environment_file << *aux_velocities[i] << "=" << aux_velocities[i]->get_value() << ";" <<endl;
        }
        
    environment_file <<  "%------------ auxiliar Acelerations -------------------"  <<endl;

    for (int i=0; i < aux_accelerations.size() ; ++i)
        {
            environment_file << *aux_accelerations[i] << "=" << aux_accelerations[i]->get_value() << ";" <<endl;
        }          
        

    environment_file <<  "%------------ Parameters -------------------"  <<endl;

    for (int i=0; i < parameters.size() ; ++i)
        {
            environment_file << *parameters[i] << "=" << parameters[i]->get_value() << ";" <<endl;
        }

    environment_file <<  "%------------ Joint_Unknowns -------------------"  <<endl;

    for (int i=0; i < unknowns.size() ; ++i)
        {
            environment_file << *unknowns[i] << "=" << unknowns[i]->get_value() << ";" <<endl;
        }

    environment_file <<  "%------------ Inputs -------------------"  <<endl;

    for (int i=0; i < inputs.size() ; ++i)
        {
            environment_file << *inputs[i] << "=" << inputs[i]->get_value() << ";" <<endl;
        }

    environment_file <<  "%------------q,dq,ddq,param , input, unknowns Vectors -------------------"  <<endl;

    environment_file <<  "q=[" ;
    for (int i=0; i < coordinates.size() ; ++i)
        {
           environment_file << *coordinates[i] << ";"  ;
        }
    environment_file << "];"  << endl;

    environment_file <<  "dq=[" ;
    for (int i=0; i < velocities.size() ; ++i)
        {
            environment_file << *velocities[i] << ";" ;
        }
    environment_file << "];"  <<endl;
    
    environment_file <<  "ddq=[" ;
    for (int i=0; i < accelerations.size() ; ++i)
        {
            environment_file << *accelerations[i] << ";" ;
        }
    environment_file << "];"  <<endl;    
    
    
    if (aux_coordinates.size () != 0){
      environment_file <<  "qaux=[" ;
      for (int i=0; i < aux_coordinates.size() ; ++i)
        {
           environment_file << *aux_coordinates[i] << ";"  ;
        }
      environment_file << "];"  << endl;

      environment_file <<  "dqaux=[" ;
      for (int i=0; i < aux_velocities.size() ; ++i)
        {
            environment_file << *aux_velocities[i] << ";" ;
        }
      environment_file << "];"  <<endl;

      environment_file <<  "ddqaux=[" ;
      for (int i=0; i < aux_accelerations.size() ; ++i)
        {
            environment_file << *aux_accelerations[i] << ";" ;
        }
      environment_file << "];"  <<endl;
    }
    
    environment_file <<  "param=[" ;
    for (int i=0; i < parameters.size() ; ++i)
        {
            environment_file << *parameters[i] <<  ";" ;
        }
    environment_file << "];"  <<endl;
    
    
    if (unknowns.size () != 0){
      environment_file <<  "unkn=[" ;
      for (int i=0; i < unknowns.size() ; ++i)
        {
            environment_file << *unknowns[i] <<  ";" ;
        }
      environment_file << "];"  <<endl;
    }
    
    if (inputs.size () != 0){
      environment_file <<  "input=[" ;
      for (int i=0; i < inputs.size() ; ++i)
        {
            environment_file << *inputs[i] <<  ";" ;
        }
      environment_file << "];"  <<endl;  
    }

    environment_file.close();
 
/*---------end write q, dq, ddq, epsilon, parameters to environment.m---------*/
}

/*********************************************************************************************************
************************************* CONFIG.INI EXPORT FUNCTIONS ****************************************
*********************************************************************************************************/
void System::export_config_ini ( void ) {
    ofstream config_file;
    config_file.open("./config.ini", ios::out);
        for (int i=0; i < parameters.size() ; ++i){
            config_file << *parameters[i] << "=" << parameters[i]->get_value() << ";" <<endl;
        }
    config_file.close();
}
/*********************************************************************************************************
***************************** SYSTEM OPENSCENEGRAPH FILES EXPORT FUNCTIONS *******************************
*********************************************************************************************************/
/*---------begin solids_homogeneous_matrix.cpp---------*/
void System::export_solids_homogeneous_matrix_cpp ( void ) {


    vector < Drawing3D * > Drawings = get_Drawings (  );

    //Vector3D Oxyz = Vector3D( Matrix ( 3 , 1 ) , Base_xyz , this);
    lst laux0;
    laux0.append(0);laux0.append(0);laux0.append(0);
    Matrix Zeros(3,1,laux0);
    //Matrix Zeros(3,1, lst( 0, 0, 0));
    
    lst laux1;
    laux0.append(1);
    Matrix Ones(1,1,laux1);
    //Matrix Ones(1,1, lst( 1 ));


    ofstream hom_matrix_file;
    hom_matrix_file.open("./solids_homogeneous_matrix.cpp", ios::out);


    hom_matrix_file << "#ifndef __linux__"  <<endl;
    hom_matrix_file << "  #include <windows.h>"  <<endl;
    hom_matrix_file << "#endif"  <<endl;
    hom_matrix_file << " "  <<endl;

    hom_matrix_file << "#include <osg/MatrixTransform>"  <<endl;
    hom_matrix_file << "#include <math.h>"  <<endl;
    hom_matrix_file << "#include \"osg_root.h\""  <<endl;
    hom_matrix_file << " "  <<endl;
    hom_matrix_file << "extern \"C\" {"  <<endl;
    hom_matrix_file << "extern void Init_param_values ( void );"  <<endl;
    hom_matrix_file << "extern void  Init_q_values ( void );"  <<endl;
    //hom_matrix_file << "extern void  Init_qaux_values ( void );"  <<endl;
    hom_matrix_file << "#include \"param.h\""  <<endl;
    hom_matrix_file << "#include \"inputs.h\""  <<endl;
    hom_matrix_file << "#include \"unknowns.h\""  <<endl;
    hom_matrix_file << "#include \"gen_coord.h\""  <<endl;
    hom_matrix_file << "#include \"gen_vel.h\""  <<endl;
    hom_matrix_file << "#include \"gen_accel.h\""  <<endl;
    //hom_matrix_file << "#include \"gen_auxcoord.h\""  <<endl;

    hom_matrix_file << "};"  <<endl;
    hom_matrix_file << " "  <<endl;

    for ( int i = 0 ; i < coordinates.size () ; i++ )
        hom_matrix_file << "#define " << coordinates[i]-> get_name () << " q[ " << i << " ]" << endl;

    for ( int i = 0 ; i < velocities.size () ; i++ )
        hom_matrix_file << "#define " << velocities[i]-> get_name () << " dq[ " << i << " ]" << endl;

    for ( int i = 0 ; i < accelerations.size () ; i++ )
        hom_matrix_file << "#define " << accelerations[i]-> get_name () << " ddq[ " << i << " ]" << endl;

    hom_matrix_file << " "  <<endl;

    /*
    for ( int i = 0 ; i < aux_coordinates.size () ; i++ )
        hom_matrix_file << "#define " << aux_coordinates[i]-> get_name () << " qaux[ " << i << " ]" << endl;

    hom_matrix_file << " "  <<endl;
    */

    for ( int i = 0 ; i < parameters.size () ; i++ )
        hom_matrix_file << "#define " << parameters[i]-> get_name () << " param[ " << i << " ]" << endl;

    for ( int i = 0 ; i < inputs.size () ; i++ )
        hom_matrix_file << "#define " << inputs[i]-> get_name () << " inputs[ " << i << " ]" << endl;

    for ( int i = 0 ; i < unknowns.size () ; i++ )
        hom_matrix_file << "#define " << unknowns[i]-> get_name () << " unknowns[ " << i << " ]" << endl;
        

    hom_matrix_file << " "  <<endl;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        string s1 = Drawings[i]->get_name();
        if (Drawings[i]->get_type() == "Solid"){
            hom_matrix_file << "osg::Matrix MSol_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
            hom_matrix_file << "osg::Matrix MFra_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
            hom_matrix_file << "osg::Matrix MPnt_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Vector"){
            hom_matrix_file << "osg::Matrix MVec_" << s1 << ";"  <<endl;
        }
    }

    hom_matrix_file << " "  <<endl;
    hom_matrix_file << "void solids_homogeneous_matrix ( )"  <<endl;
    hom_matrix_file << "{"  <<endl;
    hom_matrix_file << " "  <<endl;

    Matrix Mtrans;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        string s1 = Drawings[i]->get_name();
        Matrix Mrot=Rotation_Matrix(get_Base("xyz"),Drawings[i]->get_Base() ).transpose();
 
        if ( gravity == UP ) {
            gravity = DOWN;
            Vector3D O_P = Position_Vector("O", Drawings[i]->get_Point()->get_name());
            Mtrans=(Matrix)(O_P.change_Base(Base_xyz)).transpose();
            //Mtrans=(Matrix)(Position_Vector("O", Drawings[i]->get_Point()->get_name())+ Oxyz).transpose();
            gravity = UP;
        }
        else{
            //Mtrans=(Matrix)(Position_Vector("O", Drawings[i]->get_Point()->get_name())+ Oxyz).transpose();
            Vector3D O_P = Position_Vector("O", Drawings[i]->get_Point()->get_name());
            Mtrans=(Matrix)(O_P.change_Base(Base_xyz)).transpose();                
        }

        Matrix Mhom(2,2,&Mrot,&Zeros,&Mtrans,&Ones);


        if (Drawings[i]->get_type() == "Solid"){
            hom_matrix_file <<"MSol_" << s1 << ".set"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
            hom_matrix_file <<"MFra_" << s1 << ".set"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
            hom_matrix_file <<"MPnt_" << s1 << ".set"  <<endl;
        }

        if (Drawings[i]->get_type() == "Solid" || Drawings[i]->get_type() == "Frame" || Drawings[i]->get_type() == "Point" ){
        hom_matrix_file <<"(";
            for ( int ii = 0; ii < Mhom.rows(); ++ii){
                for ( int jj = 0; jj < Mhom.cols () ;  jj++ ) {
					hom_matrix_file << csrc_double << unatomize_ex( Mhom(ii,jj) );
					//~ hom_matrix_file << csrc_double << Mhom(ii,jj);
                    if (ii*jj < (Mhom.rows()-1) * (Mhom.cols ()-1) ) {hom_matrix_file << ",";} 
                    else {hom_matrix_file <<");";} 
                }
                hom_matrix_file << endl;
            }
        }
        if (Drawings[i]->get_type() == "Solid"){
            hom_matrix_file << "MTrans_Sol_" << s1 << "->setMatrix(MSol_" << s1 << ");"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
            hom_matrix_file << "MTrans_Fra_" << s1 << "->setMatrix(MFra_" << s1 << ");"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
            hom_matrix_file << "MTrans_Pnt_" << s1 << "->setMatrix(MPnt_" << s1 << ");"  <<endl;
        }


        if (Drawings[i]->get_type() == "Vector"){


            Vector3D vaux = Drawings[i]-> get_vector();
            ex mod = vaux.get_module();
            ex Vx = vaux(0,0);
            ex Vy = vaux(1,0);
            ex Vz = vaux(2,0);
            ex sqrt_x2_y2 = sqrt(Vx*Vx+ Vy*Vy);

            lst l_rot_y, l_rot_zy, l_scl;

            if (Vx != 0 ||  Vy != 0){////Rotation matrix [1,0,0]' to Vec
                 l_rot_zy.append(Vx / mod); l_rot_zy.append(-Vy / sqrt_x2_y2); l_rot_zy.append(- Vz * Vx / (mod * sqrt_x2_y2)); l_rot_zy.append(0);
                 l_rot_zy.append(Vy / mod); l_rot_zy.append( Vx / sqrt_x2_y2); l_rot_zy.append(- Vz * Vy / (mod * sqrt_x2_y2)); l_rot_zy.append(0);           
                 l_rot_zy.append(Vz / mod); l_rot_zy.append(0);                l_rot_zy.append(sqrt_x2_y2 / mod);               l_rot_zy.append(0);           
                 l_rot_zy.append(0);        l_rot_zy.append(0);                l_rot_zy.append(0);                              l_rot_zy.append(1);           
                 //l_rot_zy = Vx / mod,-Vy / sqrt_x2_y2,  - Vz * Vx / (mod * sqrt_x2_y2),0,
                 //           Vy / mod , Vx / sqrt_x2_y2, - Vz * Vy / (mod * sqrt_x2_y2),0,
                 //           Vz / mod , 0              ,   sqrt_x2_y2 / mod,            0,
                 //          0,         0              ,    0,                           1; 
                 l_rot_y.append(0);       l_rot_y.append(0); l_rot_y.append(-Vz/ mod); l_rot_y.append(0); 
                 l_rot_y.append(0);       l_rot_y.append(1); l_rot_y.append(0);        l_rot_y.append(0); 
                 l_rot_y.append(Vz/ mod); l_rot_y.append(0); l_rot_y.append(0);        l_rot_y.append(0);
                 l_rot_y.append(0);       l_rot_y.append(0); l_rot_y.append(0);        l_rot_y.append(1); 
                 //l_rot_y = 0,         0, -Vz/ mod, 0,
                 //          0,         1, 0,       0,
                 //          Vz/ mod,   0, 0,       0,
                 //          0,         0, 0,       1;
             }

            else if (Vx == 0 &&  Vy == 0 && Vz == 0){
                //cout << "  Be carefull => Impossible to draw" << vaux.get_name() << " = [0,0,0] vector"<<endl;
                l_rot_zy.append(1.0); l_rot_zy.append(0.0); l_rot_zy.append(0.0); l_rot_zy.append(0.0); 
                l_rot_zy.append(0.0); l_rot_zy.append(1.0); l_rot_zy.append(0.0); l_rot_zy.append(0.0); 
                l_rot_zy.append(0.0); l_rot_zy.append(0.0); l_rot_zy.append(0.0); l_rot_zy.append(0.0);
                l_rot_zy.append(0.0); l_rot_zy.append(0.0); l_rot_zy.append(0.0); l_rot_zy.append(1.0);
                //l_rot_zy = 1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0;
                
                l_rot_y.append(1.0); l_rot_y.append(0.0); l_rot_y.append(0.0); l_rot_y.append(0.0); 
                l_rot_y.append(0.0); l_rot_y.append(1.0); l_rot_y.append(0.0); l_rot_y.append(0.0); 
                l_rot_y.append(0.0); l_rot_y.append(0.0); l_rot_y.append(1.0); l_rot_y.append(0.0);
                l_rot_y.append(0.0); l_rot_y.append(0.0); l_rot_y.append(0.0); l_rot_y.append(1.0);                
                //l_rot_y = 1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0;
            }

            else {//Rotation matrix [1,0,0]' to [0,0,1]' (symbolic)
                 //l_rot_zy = 0,         0, +Vz/ mod, 0,
                 //          0,         1, 0,       0,
                 //          Vz/ mod,   0, 0,       0,
                 //          0,         0, 0,       1;
                 l_rot_zy.append(0);       l_rot_zy.append(0); l_rot_zy.append(+Vz/ mod); l_rot_zy.append(0); 
                 l_rot_zy.append(0);       l_rot_zy.append(1); l_rot_zy.append(0);        l_rot_zy.append(0); 
                 l_rot_zy.append(Vz/ mod); l_rot_zy.append(0); l_rot_zy.append(0);        l_rot_zy.append(0);
                 l_rot_zy.append(0);       l_rot_zy.append(0); l_rot_zy.append(0);        l_rot_zy.append(1); 
                 
                 l_rot_y = l_rot_zy;
            }

            //l_scl = mod, 0,    0,   0,
            //        0,   mod,  0,   0,
            //        0,   0,  mod,   0,         
            //        0,   0,     0,  1; 
            l_scl.append(mod); l_scl.append(0.0); l_scl.append(0.0); l_scl.append(0.0); 
            l_scl.append(0.0); l_scl.append(mod); l_scl.append(0.0); l_scl.append(0.0); 
            l_scl.append(0.0); l_scl.append(0.0); l_scl.append(mod); l_scl.append(0.0);
            l_scl.append(0.0); l_scl.append(0.0); l_scl.append(0.0); l_scl.append(1.0);                     
                    
                    
            Matrix H_rot_zy (4,4,l_rot_zy);
            Matrix H_rot_y  (4,4,l_rot_y);
            Matrix H_scl(4,4,l_scl);
            Matrix Mhom_zy = H_scl  * H_rot_zy.transpose() * Mhom ;
            Matrix Mhom_y  = H_scl  * H_rot_y.transpose() * Mhom;  

            //Rotation matrix when mod = 0
            hom_matrix_file  << csrc_double<<"if ("<< unatomize_ex( mod )<<"<= 0.001 ){" << endl;
            //~ hom_matrix_file <<"if ("<<  mod <<"<= 0.001 ){" << endl;            
            hom_matrix_file <<"MVec_" << s1 << ".set"  <<endl;
            hom_matrix_file <<"  (0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);" << endl;
            hom_matrix_file <<"}" << endl;

            hom_matrix_file <<csrc_double <<"else if ("<< unatomize_ex( abs(Vx) ) <<"<= 0.001 && " << unatomize_ex( abs(Vy) ) << "<= 0.001){" << endl;//Print rotation matrix [1,0,0]' to [0,0,1]'
            //~ hom_matrix_file <<"else if ("<< abs(Vx) <<"<= 0.001 && " << abs(Vy)  << "<= 0.001){" << endl;//Print rotation matrix [1,0,0]' to [0,0,1]'
            hom_matrix_file <<"MVec_" << s1 << ".set"  <<endl;
            hom_matrix_file <<"(";
                for ( int ii = 0; ii < Mhom_y.rows(); ++ii){
                    for ( int jj = 0; jj < Mhom_y.cols () ;  jj++ ) {
                        hom_matrix_file << csrc_double << unatomize_ex( Mhom_y(ii,jj) );
                        //~ hom_matrix_file << csrc_double <<  Mhom_y(ii,jj) ;                        
                        if (ii*jj < (Mhom_y.rows()-1) * (Mhom_y.cols ()-1) ) {hom_matrix_file << ",";} 
                        else {hom_matrix_file <<");";} 
                    }
                    hom_matrix_file << endl;
                }
            hom_matrix_file <<"}" << endl;

            hom_matrix_file <<"else {" << endl;//Print rotation matrix [1,0,0]' to Vec
            hom_matrix_file <<"MVec_" << s1 << ".set"  <<endl;
            hom_matrix_file <<"(";
                for ( int ii = 0; ii < Mhom_zy.rows(); ++ii){
                    for ( int jj = 0; jj < Mhom_zy.cols () ;  jj++ ) {
                        hom_matrix_file << csrc_double << unatomize_ex( Mhom_zy(ii,jj) );
                        //~ hom_matrix_file << csrc_double << Mhom_zy(ii,jj) ;                       
                        if (ii*jj < (Mhom_zy.rows()-1) * (Mhom_zy.cols ()-1) ) {hom_matrix_file << ",";} 
                        else {hom_matrix_file <<");";} 
                    }
                    hom_matrix_file << endl;
                }
            hom_matrix_file <<"}" << endl;

            hom_matrix_file << "MTrans_Vec_" << s1 << "->setMatrix(MVec_" << s1 << ");"  <<endl;
        }


        hom_matrix_file << " "  <<endl;
    }

    hom_matrix_file << "}"  <<endl;
    hom_matrix_file.close();


}
/*---------end solids_homogeneous_matrix.cpp---------*/

/*---------begin solids_homogeneous_matrix.h---------*/
void System::export_solids_homogeneous_matrix_h ( void ) {
    ofstream hom_matrix_head_file;
    hom_matrix_head_file.open("./solids_homogeneous_matrix.h", ios::out);
    hom_matrix_head_file << "void solids_homogeneous_matrix ( void );"  <<endl;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        string s1 = Drawings[i]->get_name();
        if (Drawings[i]->get_type() == "Solid"){
            hom_matrix_head_file << "extern osg::Matrix MSol_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
            hom_matrix_head_file << "extern osg::Matrix MFra_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
            hom_matrix_head_file << "extern osg::Matrix MPnt_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Vector"){
            hom_matrix_head_file << "extern osg::Matrix MVec_" << s1 << ";"  <<endl;
        }
    }

    hom_matrix_head_file.close();
}
/*---------end solids_homogeneous_matrix.h---------*/


/*---------begin osg_read_file.cpp ---------*/
void System::export_osg_read_file_cpp ( void ) {
    ofstream osg_read_file;

    osg_read_file.open("./osg_read_file.cpp", ios::out);

    osg_read_file << "#ifndef __linux__"  <<endl;
    osg_read_file << "  #include <windows.h>"  <<endl;
    osg_read_file << "#endif"  <<endl;
    osg_read_file << " "  <<endl;

    osg_read_file << "#include <osg/Geode>"  <<endl;
    osg_read_file << "#include <osgDB/ReadFile>"  <<endl;
    osg_read_file << " "  <<endl;
    osg_read_file << "osg::Geode* axis;"  <<endl;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        string s1 = Drawings[i]->get_name();
        if (Drawings[i]->get_type() == "Solid"){
            osg_read_file << "osg::Geode* Sol_"<< s1 <<";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
            osg_read_file << "osg::Geode* Fra_"<< s1 <<";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
            osg_read_file << "osg::Geode* Pnt_"<< s1 <<";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Vector"){
            osg_read_file << "osg::Geode* Vec_"<< s1 <<";"  <<endl;
        }
    }

    osg_read_file << " "  <<endl;
    osg_read_file << "void osg_read_file ()"  <<endl;
    osg_read_file << "{"  <<endl;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        string s1 = Drawings[i]->get_name();
        if (Drawings[i]->get_type() == "Solid"){
            string s_solid = Drawings[i]->get_file();
            numeric s2 = Drawings[i]->get_scale();
            //osg_read_file << "Sol_" << s1 <<" = (osg::Geode*) osgDB::readNodeFile(\"" << s_solid << "\");"  <<endl;
            osg_read_file << "Sol_" << s1 <<" = (osg::Geode*) osgDB::readNodeFile(\"" << s_solid <<".["<<s2<< "].scale\");"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
            numeric s2 = Drawings[i]->get_scale();
            osg_read_file << "Fra_" << s1 <<" = (osg::Geode*) osgDB::readNodeFile(\"./axes.osg.["<< s2 <<"].scale\");"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
            numeric s2 = Drawings[i]->get_scale();
            osg_read_file << "Pnt_" << s1 <<" = (osg::Geode*) osgDB::readNodeFile(\"./point.osg.["<< s2 <<"].scale\");"  <<endl;
        }
        if (Drawings[i]->get_type() == "Vector"){
            numeric s2 = Drawings[i]->get_scale();
            osg_read_file << "Vec_" << s1 <<" = (osg::Geode*) osgDB::readNodeFile(\"./vector.osg.["<< s2 <<"].scale\");"  <<endl;
        }

    }
    osg_read_file << "}"  <<endl;

    osg_read_file.close();
}
/*---------end osg_read_file.cpp ---------*/

/*---------begin osg_read_file.h ---------*/
void System::export_osg_read_file_h ( void ) {
    ofstream osg_read_head_file;
    osg_read_head_file.open("./osg_read_file.h", ios::out);

    osg_read_head_file << "extern void osg_read_file ( void );"  <<endl;
    osg_read_head_file << "extern osg::Geode* axis;"  <<endl;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        string s1 = Drawings[i]->get_name();
        if (Drawings[i]->get_type() == "Solid"){
        osg_read_head_file << "extern osg::Geode* Sol_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
        osg_read_head_file << "extern osg::Geode* Fra_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
        osg_read_head_file << "extern osg::Geode* Pnt_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Vector"){
        osg_read_head_file << "extern osg::Geode* Vec_" << s1 << ";"  <<endl;
        }
    }


    osg_read_head_file.close();
}
/*---------end osg_read_file.h ---------*/

/*-------------- begin osg_root.cpp ---------*/
void System::export_osg_root_cpp ( void ) {
    ofstream osg_root_file;
    osg_root_file.open("./osg_root.cpp", ios::out);

    osg_root_file << "#ifndef __linux__"  <<endl;
    osg_root_file << "  #include <windows.h>"  <<endl;
    osg_root_file << "#endif"  <<endl;
    osg_root_file << " "  <<endl;

    osg_root_file << "#include <osg/Group>"  <<endl;
    osg_root_file << "#include <osg/Geode>"  <<endl;
    osg_root_file << "#include <osg/MatrixTransform>"  <<endl;
    osg_root_file << " "  <<endl;
    osg_root_file << "#include \"solids_homogeneous_matrix.h\""  <<endl;
    osg_root_file << "#include \"osg_read_file.h\""  <<endl;
    osg_root_file << "#include \"osg_state.h\""  <<endl;
    osg_root_file << ""  <<endl;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        string s1 = Drawings[i]->get_name();
        if (Drawings[i]->get_type() == "Solid"){
            osg_root_file << "osg::MatrixTransform* MTrans_Sol_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
            osg_root_file << "osg::MatrixTransform* MTrans_Fra_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
            osg_root_file << "osg::MatrixTransform* MTrans_Pnt_" << s1 << ";"  <<endl;
        }
        if (Drawings[i]->get_type() == "Vector"){
            osg_root_file << "osg::MatrixTransform* MTrans_Vec_" << s1 << ";"  <<endl;
        }
    }

    osg_root_file << ""  <<endl;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        string s1 = Drawings[i]->get_name();
        if (Drawings[i]->get_type() == "Solid"){
            osg_root_file << "osg::Group* Sol_" << s1 << "_axis;"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
            osg_root_file << "osg::Group* Fra_" << s1 << "_axis;"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
            osg_root_file << "osg::Group* Pnt_" << s1 << "_axis;"  <<endl;
        }
        if (Drawings[i]->get_type() == "Vector"){
            osg_root_file << "osg::Group* Vec_" << s1 << "_axis;"  <<endl;
        }
    }

    osg_root_file << ""  <<endl;
    osg_root_file << "osg::Group* root;"  <<endl;
    osg_root_file << ""  <<endl;

    osg_root_file << "void osg_root ()"  <<endl;
    osg_root_file << "{"  <<endl;
    osg_root_file << "osg_state();"  <<endl;
    osg_root_file << ""  <<endl;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        string s1 = Drawings[i]->get_name();
        if (Drawings[i]->get_type() == "Solid"){
            osg_root_file << "Sol_" << s1 << "_axis = new osg::Group;"  <<endl;
            osg_root_file << "Sol_" << s1 << "_axis->addChild(Sol_" << s1 << ");"  <<endl;
            osg_root_file << "Sol_" << s1 << "_axis->addChild(axis);"  <<endl;
            osg_root_file << "MTrans_Sol_" << s1 << " = new osg::MatrixTransform(MSol_" << s1 << ");"  <<endl;
            osg_root_file << "MTrans_Sol_" << s1 << "->addChild(Sol_" << s1 << "_axis);"  <<endl;
            osg_root_file << "	"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
            osg_root_file << "Fra_" << s1 << "_axis = new osg::Group;"  <<endl;
            osg_root_file << "Fra_" << s1 << "_axis -> addChild(Fra_" << s1 << ");"  <<endl;
            osg_root_file << "MTrans_Fra_" << s1 << " = new osg::MatrixTransform(MFra_" << s1 << ");"  <<endl;
            osg_root_file << "MTrans_Fra_" << s1 << "->addChild(Fra_" << s1 << ");"  <<endl;
            osg_root_file << "	"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
            osg_root_file << "Pnt_" << s1 << "_axis = new osg::Group;"  <<endl;
            osg_root_file << "Pnt_" << s1 << "_axis -> addChild(Pnt_" << s1 << ");"  <<endl;
            osg_root_file << "MTrans_Pnt_" << s1 << " = new osg::MatrixTransform(MPnt_" << s1 << ");"  <<endl;
            osg_root_file << "MTrans_Pnt_" << s1 << "->addChild(Pnt_" << s1 << ");"  <<endl;
            osg_root_file << "	"  <<endl;
        }
        if (Drawings[i]->get_type() == "Vector"){
            osg_root_file << "Vec_" << s1 << "_axis = new osg::Group;"  <<endl;
            osg_root_file << "Vec_" << s1 << "_axis -> addChild(Vec_" << s1 << ");"  <<endl;
            osg_root_file << "MTrans_Vec_" << s1 << " = new osg::MatrixTransform(MVec_" << s1 << ");"  <<endl;
            osg_root_file << "MTrans_Vec_" << s1 << "->addChild(Vec_" << s1 << ");"  <<endl;
            osg_root_file << "	"  <<endl;
        }
    }


    osg_root_file << "	"  <<endl;

    osg_root_file << "root = new osg::Group;"  <<endl;
    //osg_root_file << "root->addChild(axis);"  <<endl;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        string s1 = Drawings[i]->get_name();
        if (Drawings[i]->get_type() == "Solid"){
            osg_root_file << "root->addChild(MTrans_Sol_" << s1 << ");"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
            osg_root_file << "root->addChild(MTrans_Fra_" << s1 << ");"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
            osg_root_file << "root->addChild(MTrans_Pnt_" << s1 << ");"  <<endl;
        }
        if (Drawings[i]->get_type() == "Vector"){
            osg_root_file << "root->addChild(MTrans_Vec_" << s1 << ");"  <<endl;
        }
    }

    osg_root_file << "}"  <<endl;

    osg_root_file.close();
}
/*-------------- end osg_root.cpp ---------*/

/*-------------- begin osg_root.h ---------*/
void System::export_osg_root_h ( void ) {
    ofstream osg_root_header_file;
    osg_root_header_file.open("./osg_root.h", ios::out);

    osg_root_header_file << "extern void osg_root ( void );"  <<endl;
    osg_root_header_file << "	"  <<endl;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        string s1 = Drawings[i]->get_name();
        if (Drawings[i]->get_type() == "Solid"){
            osg_root_header_file << "extern osg::MatrixTransform* MTrans_Sol_" << s1 << ";"  <<endl;
            osg_root_header_file << "extern osg::Group* Sol_" << s1 << "_axis;"  <<endl;
            osg_root_header_file << "	"  <<endl;
        }
        if (Drawings[i]->get_type() == "Frame"){
            osg_root_header_file << "extern osg::MatrixTransform* MTrans_Fra_" << s1 << ";"  <<endl;
            osg_root_header_file << "extern osg::Group* Fra_" << s1 << "_axis;"  <<endl;
            osg_root_header_file << "	"  <<endl;
        }
        if (Drawings[i]->get_type() == "Point"){
            osg_root_header_file << "extern osg::MatrixTransform* MTrans_Pnt_" << s1 << ";"  <<endl;
            osg_root_header_file << "extern osg::Group* Pnt_" << s1 << "_axis;"  <<endl;
            osg_root_header_file << "	"  <<endl;
        }
        if (Drawings[i]->get_type() == "Vector"){
            osg_root_header_file << "extern osg::MatrixTransform* MTrans_Vec_" << s1 << ";"  <<endl;
            osg_root_header_file << "extern osg::Group* Vec_" << s1 << "_axis;"  <<endl;
            osg_root_header_file << "	"  <<endl;
        }
    }

    osg_root_header_file << "extern osg::Group* root;"  <<endl;
    osg_root_header_file.close();
}
/*-------------- end osg_root.h ---------*/

/*------------ begin osg_state.cpp ---------*/
void System::export_osg_state_cpp ( void ) {
    ofstream osg_state_file;
    osg_state_file.open("./osg_state.cpp", ios::out);

    osg_state_file << "#ifndef __linux__"  <<endl;
    osg_state_file << "  #include <windows.h>"  <<endl;
    osg_state_file << "#endif"  <<endl;
    osg_state_file << ""  <<endl;
    osg_state_file << "#include <osg/Geode>"  <<endl;
    osg_state_file << "#include <osg/Material>"  <<endl;
    osg_state_file << "#include <osg/BlendFunc>"  <<endl;
    osg_state_file << ""  <<endl;
    osg_state_file << "#include \"osg_read_file.h\""  <<endl;
    osg_state_file << ""  <<endl;

    osg_state_file << "void osg_state ()"  <<endl;
    osg_state_file << "{"  <<endl;
    osg_state_file << ""  <<endl;

    for ( int i = 0 ; i < Drawings.size () ; i++ ){
        if (Drawings[i]->get_type() == "Solid"){
            string s1 = Drawings[i]->get_name();
            lst color = Drawings[i]->get_color();
            if  (color[0] <= 1.0 && color[1] <= 1.0 && color[2] <= 1.0 && color[3] <= 1.0 ){
              osg_state_file << "osg::StateSet* State_" << s1 << " = Sol_" << s1 << "->getOrCreateStateSet();" <<endl;
              osg_state_file << "osg::ref_ptr<osg::Material> material" << s1 << " = new osg::Material;" <<endl;
              osg_state_file << "material" << s1 << "->setDiffuse(osg::Material::FRONT,osg::Vec4("<<color[0]<<","<<color[1]<<","<<color[2]<<","<<color[3]<<"));" <<endl;
              osg_state_file << "State_" << s1 << "->setAttributeAndModes( material" << s1 << ".get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);" <<endl;
              osg_state_file << "State_" << s1 << "->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);" <<endl;
              osg_state_file << "State_" << s1 << "->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));" <<endl;
              osg_state_file << ""  <<endl;
            }
        }
        if (Drawings[i]->get_type() == "Point"){
            string s1 = Drawings[i]->get_name();
            lst color = Drawings[i]->get_color();
            osg_state_file << "osg::StateSet* State_" << s1 << " = Pnt_" << s1 << "->getOrCreateStateSet();" <<endl;
            osg_state_file << "osg::ref_ptr<osg::Material> material" << s1 << " = new osg::Material;" <<endl;
            osg_state_file << "material" << s1 << "->setDiffuse(osg::Material::FRONT,osg::Vec4("<<color[0]<<","<<color[1]<<","<<color[2]<<","<<color[3]<<"));" <<endl;
            osg_state_file << "State_" << s1 << "->setAttributeAndModes( material" << s1 << ".get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);" <<endl;
            osg_state_file << "State_" << s1 << "->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);" <<endl;
            osg_state_file << "State_" << s1 << "->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));" <<endl;
            osg_state_file << ""  <<endl;
        }
        if (Drawings[i]->get_type() == "Vector"){
            string s1 = Drawings[i]->get_name();
            lst color = Drawings[i]->get_color();

            osg_state_file << "osg::StateSet* State_" << s1 << " = Vec_" << s1 << "->getOrCreateStateSet();" <<endl;
            osg_state_file << "osg::ref_ptr<osg::Material> material" << s1 << " = new osg::Material;" <<endl;
            osg_state_file << "material" << s1 << "->setDiffuse(osg::Material::FRONT,osg::Vec4("<<color[0]<<","<<color[1]<<","<<color[2]<<","<<color[3]<<"));" <<endl;
            osg_state_file << "State_" << s1 << "->setAttributeAndModes( material" << s1 << ".get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);" <<endl;
            osg_state_file << "State_" << s1 << "->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);" <<endl;
            osg_state_file << "State_" << s1 << "->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA));" <<endl;
            osg_state_file << ""  <<endl;
        }

    }

    osg_state_file << "}"  <<endl;

    osg_state_file.close();
}

/*-------------- end osg_state.cpp ---------*/

/*------------ begin osg_state.h ---------*/
void System::export_osg_state_h ( void ) {
    ofstream osg_state_header_file;
    osg_state_header_file.open("./osg_state.h", ios::out);
    osg_state_header_file << "extern void osg_state ( void );"  <<endl;
    osg_state_header_file << " "  <<endl;
    osg_state_header_file << "extern osg::StateSet* state;"  <<endl;

    osg_state_header_file.close();
}
/*-------------- end osg_state.h ---------*/

void System::export_open_scene_graph ( void ){

    export_solids_homogeneous_matrix_cpp(  );// solids_homogeneous_matrix.cpp
    export_solids_homogeneous_matrix_h(  );// solids_homogeneous_matrix.h
    export_osg_read_file_cpp ( );// osg_read_file.cpp
    export_osg_read_file_h ( );// osg_read_file.h
    export_osg_root_cpp (  );// osg_root.cpp
    export_osg_root_h ( );// osg_root.h
    export_osg_state_cpp (  );// osg_state.cpp
    export_osg_state_h ( );// osg_state.h

}


/*********************************************************************************************************
***************************** SYSTEM GNUPLOT EXPORT FUNCTIONS ********************************************
*********************************************************************************************************/
void System::export_gnuplot ( lst expresion_list ) {
    vector < symbol_numeric * > Coordinates    = get_Coordinates();
    vector < symbol_numeric * > Velocities    = get_Velocities();
    vector < symbol_numeric * > Accelerations    = get_Accelerations();
    vector < symbol_numeric * > Joint_Unknowns = get_Joint_Unknowns();

    lst coords; 
    lst vels;
    lst accels; 
    lst unkns; 

    for (int i=0; i < Coordinates.size() ; ++i){
        for (int j=0; j < expresion_list.nops() ; ++j){
            if(*Coordinates[i]==expresion_list[j]){
                coords.append(*Coordinates[i]);
            }
        }
    }

    for (int i=0; i < Velocities.size() ; ++i){
        for (int j=0; j < expresion_list.nops() ; ++j){
            if(*Velocities[i]==expresion_list[j]){
                vels.append(*Velocities[i]);
            }
        }
    }

    for (int i=0; i < Accelerations.size() ; ++i){
        for (int j=0; j < expresion_list.nops() ; ++j){
            if(*Accelerations[i]==expresion_list[j]){
                accels.append(*Accelerations[i]);
            }
        }
    }

    for (int i=0; i < Joint_Unknowns.size() ; ++i){
        for (int j=0; j < expresion_list.nops() ; ++j){
            if(*Joint_Unknowns[i]==expresion_list[j]){
                unkns.append(*Joint_Unknowns[i]);
            }
        }
    }

    int iter_lst = 0;
    ofstream gnuplot_file;
    /*------------ begin coordinates.gnuplot ---------*/
    if (coords.nops() > 0){
        gnuplot_file.open("./coordinates.gnuplot", ios::out);
        gnuplot_file << "set xlabel \"t(s)\" "  <<endl;
        gnuplot_file << "set grid "  <<endl;
        gnuplot_file << " "  <<endl;
        gnuplot_file << "set title \"Coordinates vs time\" "  <<endl;
        gnuplot_file<<  "set ylabel \" ";
        for  ( lst::const_iterator k = coords.begin () ; k != coords.end () ; ++k ){
            gnuplot_file << *k << " "  ;
        }
        gnuplot_file << "\""  << endl;
        gnuplot_file<<  "set term postscript eps color"  <<endl;
        gnuplot_file<<  "set output \"coordinates.eps\" "  <<endl;
        gnuplot_file<<  "plot";
        int i =0;
        for (int i=0; i < coords.nops(); i++){
            gnuplot_file << "\"state.dat\" using ($1):($"<<iter_lst+2<<") title \""<<coords[i]<<"\"";
            if(i != coords.nops()-1){gnuplot_file << ",";}
            iter_lst++;
        }
        gnuplot_file << endl;
        gnuplot_file.close();
    }
    /*-------------- end coordinates.gnuplot ---------*/

    /*------------ begin velocities.gnuplot ---------*/
    if (vels.nops() > 0){
        gnuplot_file.open("./velocities.gnuplot", ios::out);
        gnuplot_file << "set xlabel \"t(s)\" "  <<endl;
        gnuplot_file << "set grid "  <<endl;
        gnuplot_file << " "  <<endl;
        gnuplot_file << "set title \"Velocities vs time\" "  <<endl;
        gnuplot_file<<  "set ylabel \" ";
        for  ( lst::const_iterator k = vels.begin () ; k != vels.end () ; ++k ){
            gnuplot_file << *k << " "  ;
        }
        gnuplot_file << "\""  << endl;
        gnuplot_file<<  "set term postscript eps color"  <<endl;
        gnuplot_file<<  "set output \"velocities.eps\" "  <<endl;
        gnuplot_file<<  "plot";
        for (int i=0; i < vels.nops(); i++){
            gnuplot_file << "\"state.dat\" using ($1):($"<<iter_lst+2<<") title \""<<vels[i]<<"\"";
            if(i != vels.nops()-1){gnuplot_file << ",";}
            iter_lst++;
        }
        gnuplot_file << endl;
        gnuplot_file.close();
    }
    /*-------------- end velocities.gnuplot ---------*/

    /*------------ begin accelerations.gnuplot ---------*/
    if (accels.nops() > 0){
        gnuplot_file.open("./accelerations.gnuplot", ios::out);
        gnuplot_file << "set xlabel \"t(s)\" "  <<endl;
        gnuplot_file << "set grid "  <<endl;
        gnuplot_file << " "  <<endl;
        gnuplot_file << "set title \"Accelerations vs time\" "  <<endl;
        gnuplot_file<<  "set ylabel \" ";
        for  ( lst::const_iterator k = accels.begin () ; k != accels.end () ; ++k ){
            gnuplot_file << *k << " "  ;
        }
        gnuplot_file << "\""  << endl;
        gnuplot_file<<  "set term postscript eps color"  <<endl;
        gnuplot_file<<  "set output \"accelerations.eps\" "  <<endl;
        gnuplot_file<<  "plot";
        for (int i=0; i < accels.nops(); i++){
            gnuplot_file << "\"state.dat\" using ($1):($"<<iter_lst+2<<") title \""<<accels[i]<<"\"";
            if(i != accels.nops()-1){gnuplot_file << ",";}
        iter_lst++;
        }
        gnuplot_file << endl;
        gnuplot_file.close();
    }
    /*-------------- end accelerations.gnuplot ---------*/

    /*------------ begin Joint_Unknowns.gnuplot ---------*/
    if (unkns.nops() > 0){
        gnuplot_file.open("./joint_unknowns.gnuplot", ios::out);
        gnuplot_file << "set xlabel \"t(s)\" "  <<endl;
        gnuplot_file << "set grid "  <<endl;
        gnuplot_file << " "  <<endl;
        gnuplot_file << "set title \"Joint_Unknowns vs time\" "  <<endl;
        gnuplot_file<<  "set ylabel \" ";
        for  ( lst::const_iterator k = unkns.begin () ; k != unkns.end () ; ++k ){
            gnuplot_file << *k << " "  ;
        }
        gnuplot_file << "\""  << endl;
        gnuplot_file<<  "set term postscript eps color"  <<endl;
        gnuplot_file<<  "set output \"joint_unknowns.eps\" "  <<endl;
        gnuplot_file<<  "plot";
        for (int i=0; i < unkns.nops(); i++){
            gnuplot_file << "\"state.dat\" using ($1):($"<<iter_lst+2<<") title \""<<unkns[i]<<"\"";
            if(i != unkns.nops()-1){gnuplot_file << ",";}
        iter_lst++;
        }
        gnuplot_file << endl;
        gnuplot_file.close();
    }
    /*-------------- end Joint_Unknowns.gnuplot ---------*/
}

/*********************************************************************************************************
***************************** SYSTEM MATRIX CALCULATION EXPORT FUNCTIONS *******************************
*********************************************************************************************************/

void System::Matrix_Calculation(Matrix &Phi, lst coord_indep_init ,lst vel_indep_init , Matrix &Dynamic_Equations, System &sys, int method, Matrix &dPhiNH){

    try{ if ( (method != LAGRANGE) && (method != VIRTUAL_POWER)  ) throw 1;}
    catch ( int e ) {outError ( "ERR -  Parameter 'int method' must be LAGRANGE or VIRTUAL_POWER" );}

    clock_t start, end;
    double time;

    ex aux;

    Matrix q          = Coordinates();
    Matrix dq         = Velocities();
    Matrix ddq        = Accelerations();
    Matrix qaux       = Aux_Coordinates();
    Matrix dqaux      = Aux_Velocities();
    Matrix ddqaux     = Aux_Accelerations();
    Matrix parameters = Parameters();
    Matrix epsilon    = Joint_Unknowns();

    vector < symbol_numeric * > Coordinates        = get_Coordinates();
    vector < symbol_numeric * > Velocities         = get_Velocities();
    vector < symbol_numeric * > Accelerations      = get_Accelerations();
    vector < symbol_numeric * > Aux_Coordinates    = get_AuxCoordinates();
    vector < symbol_numeric * > Aux_Velocities     = get_AuxVelocities();
    vector < symbol_numeric * > Aux_Accelerations  = get_AuxAccelerations();
    vector < symbol_numeric * > Parameters         = get_Parameters();
    vector < symbol_numeric * > Joint_Unknowns     = get_Joint_Unknowns();


    if (Aux_Coordinates.size()> 0 ){
        Coordinates.insert( Coordinates.end(),Aux_Coordinates.begin(), Aux_Coordinates.end() );
        Velocities.insert( Velocities.end(),Aux_Velocities.begin(), Aux_Velocities.end() );
        Accelerations.insert( Accelerations.end(),Aux_Accelerations.begin(), Aux_Accelerations.end() );
    }
     
    cout<<" dPhi Calculating"<<endl;
    Matrix dPhi_aux = Dt(Phi);
    Matrix dPhi = Matrix (2,1,&dPhi_aux,&dPhiNH);
    cout<<" ddPhi Calculating"<<endl;
    Matrix ddPhi  = Dt(dPhi);
      

    //Check sizes:+
    if( method == LAGRANGE){
        if ( Phi.rows() + dPhiNH.rows()  != Joint_Unknowns.size()){
            cout << " "<< endl;
            cout << "WARNING:"<< endl;
            cout << "  Check Phi, dPhiNH or Unknowns. The size of (Phi + dPhiNH) must be the same as the size of Unknowns "<< endl;
            cout << " "<< endl;
        }
    }
    

    cout<<" Beta Calculating"<<endl;
    Matrix Beta  = -dPhi;
    symbol_numeric *dq_j;
    for (int i=0; (i < dPhi.rows()); ++i) {
		if ( atomization == NO ){
            for (int j=0; (j < Velocities.size()); ++j) {
                dq_j=Velocities[j];
                Beta(i,0)=Beta(i,0).subs((*dq_j)==0);
            }
        }
        else{
            Beta(i,0) = recursive_substitution (Beta(i,0),Velocities , 0);
            Beta(i,0) = recursive_substitution (Beta(i,0),Aux_Velocities , 0);
        }	
    }    

    cout<<" Gamma Calculating"<<endl;
    symbol_numeric *ddq_j;
    //~ Matrix Gamma  = Dt(Beta);    
    Matrix Gamma  = -ddPhi;   
    for (int i=0; (i < Gamma.rows()); ++i) {
		if ( atomization == NO ){
            for (int j=0; (j < Accelerations.size()); ++j) {
                ddq_j=Accelerations[j];
                Gamma(i,0)=Gamma(i,0).subs((*ddq_j)==0);
            }
        }
        else{
 
            Gamma(i,0) = recursive_substitution (Gamma(i,0),Accelerations , 0);
            Gamma(i,0) = recursive_substitution (Gamma(i,0),Aux_Accelerations , 0);
        }	
    }


 
    Matrix Dynamic_Equations_open = Dynamic_Equations;
    Matrix M(ddq.rows(),ddq.rows()) ;
    Matrix Q(ddq.rows(),1);
    
    struct timeval  tv; 
    
    if  (Dynamic_Equations.rows() != 0 ) {  // uses the old method, 
    gettimeofday(&tv, NULL); double time1 =  (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
        // Dynamic_Equations ==> M * ddq + V * epsilon - Q = 0 // Dynamic_Equations_open	==> M * ddq - Q = 0
        Dynamic_Equations_open = Dynamic_Equations;

        if ( method == VIRTUAL_POWER){
            cout<<" Matrix Dynamic_Equations_open Calculating"<<endl;
            symbol_numeric *unk_j;
            for (int i=0; (i < Dynamic_Equations_open.rows()); ++i) {
                if ( atomization == NO ){
                    for (int j=0; (j < Joint_Unknowns.size()); ++j) {
                        unk_j=Joint_Unknowns[j];
                        Dynamic_Equations_open(i,0) = Dynamic_Equations_open(i,0).subs((*unk_j)==0);
                    }
                }
                else{
                    Dynamic_Equations_open(i,0) = recursive_substitution (Dynamic_Equations_open(i,0),Joint_Unknowns , 0);
                }	
            }
        }
        else if( method == LAGRANGE){
		    Matrix Dynamic_Equations_open = Dynamic_Equations;  
    	} 
        * new_Matrix( "Dynamic_Equations_open",Dynamic_Equations_open );
        
        cout<<" M and Q Calculating by differentation"<<endl;
        //M = jacobian(Dynamic_Equations_open.transpose() ,ddq,1); //M is symmetric
        M = jacobian(Dynamic_Equations_open.transpose() ,ddq); 

        Q = - Dynamic_Equations_open;
        for (int i=0; (i < Q.rows()); ++i) {
            if ( atomization == NO ){
                for (int j=0; (j < Accelerations.size()); ++j) {
                    ddq_j=Accelerations[j];
                    Q(i,0)=Q(i,0).subs((*ddq_j)==0);
                }
            }
            else{
                Q(i,0) = recursive_substitution (Q(i,0),Accelerations , 0);
            }	
        } 
    gettimeofday(&tv, NULL); double time2 =  (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;

    printf ("  M and Q OLD =========================>  %f seconds\n",(double) (time2 - time1)/1000.0);
    }
    

    * new_Matrix( "Phi"   ,Phi );
    * new_Matrix( "Beta"  ,Beta );
    * new_Matrix( "Gamma" ,Gamma );


    cout<<" Init Calculating"<<endl;
    Matrix Init (coord_indep_init.nops() , 1 ,coord_indep_init);

    cout<<" dInit Calculating"<<endl;
    Matrix dInit (vel_indep_init.nops() , 1 ,vel_indep_init);

    cout<<" PhiInit Calculating"<<endl;
    Matrix PhiInit        = Matrix (2,1,&Phi,&Init);

    cout<<" dPhiInit Calculating"<<endl;
    Matrix dPhiInit       = Matrix (2,1,&dPhi,&dInit);
        
   
    cout<<" PhiInit_q Calculating"<<endl;
    //Matrix PhiInit_q       = jacobian(PhiInit.transpose(), q);
    Matrix PhiInit_q       = jacobian(PhiInit.transpose(), Matrix (2,1,&q,&qaux));//if qaux == 0 then  Matrix (2,1,&q,&qaux)) = q

    cout<<" dPhiInit_dq Calculating"<<endl;
    //Matrix dPhiInit_dq     = jacobian(dPhiInit.transpose() ,dq);   
    Matrix dPhiInit_dq     = jacobian(dPhiInit.transpose() ,Matrix (2,1,&dq,&dqaux));//if dqaux == 0 then  Matrix (2,1,&dq,&dqaux)) = dq

    cout<<" BetaInit Calculating"<<endl;
    Matrix BetaInit  = -dPhiInit;
    for (int i=0; (i < dPhiInit.rows()); ++i) {
	    if ( atomization == NO ){
            for (int j=0; (j < Velocities.size()); ++j) {
               dq_j=Velocities[j];
               BetaInit(i,0)=BetaInit(i,0).subs((*dq_j)==0);
            }
        }
        else{
            BetaInit(i,0) = recursive_substitution (BetaInit(i,0),Velocities , 0);
            BetaInit(i,0) = recursive_substitution (BetaInit(i,0),Aux_Velocities , 0);
        }	
    }  

 
    cout<<" Phi_q Calculating"<<endl;
    //Matrix Phi_q  = jacobian(Phi.transpose() ,q);
    Matrix Phi_q  = jacobian(Phi.transpose() ,Matrix (2,1,&q,&qaux));//if qaux == 0 then  Matrix (2,1,&q,&qaux)) = q
      
    cout<<" dPhi_dq Calculating"<<endl;
    //Matrix dPhi_dq =  jacobian(dPhi.transpose() ,dq);
    Matrix dPhi_dq =  jacobian(dPhi.transpose() ,Matrix (2,1,&dq,&dqaux));//if dqaux == 0 then  Matrix (2,1,&dq,&dqaux)) = dq

        

     
    vector < Solid * > Solids = sys.get_Solids ( );
    vector < Wrench3D * > Wrenches = sys.get_Wrenches ( );
    //Matrix W(q.rows(),4*Solids.size()) ;
    
    //~ Matrix MUP(ddq.rows(),ddq.rows()) ;
    //~ Matrix QUP(ddq.rows(),1);
    
   
    if  (Dynamic_Equations.rows() == 0 ) {  // uses the new method,
        cout<<" M and Q Calculating"<<endl;
        for (int k=0; k< Solids.size(); k++) {
            symbol_numeric mass = *Solids[k]->get_mass();
            //Matrix R_IT_SOL = sys.Rotation_Matrix (Solids[k]->get_Base(),Solids[k]->get_IT()->get_Base() );
            //Matrix IT = R_IT_SOL*(*Solids[k]->get_IT())*R_IT_SOL.transpose();
            
            //Tensor3D IT = (*Solids[k]->get_IT()).change_Base(Solids[k]->get_Base());
            Vector3D BG = (*Solids[k]->get_CM()).change_Base(Solids[k]->get_Base());

            Vector3D mBG = atomize( mass * unatomize ( BG) );
            //Vector3D mBG = atomize( mass * unatomize ( BG.change_Base(Solids[k]->get_Base()) ) );

            /* -----------------------------------------------------------------------------------------------------------------*/
            //  UP
            /* -----------------------------------------------------------------------------------------------------------------*/
            gravity = UP;
            Vector3D VelBUP  = Velocity_Vector("abs",Solids[k]->get_Point() -> get_name());
            Vector3D OmSolUP = Angular_Velocity("xyz",Solids[k]->get_Base() -> get_name());
            gravity = DOWN;
            
            Tensor3D IT = (*Solids[k]->get_IT()).change_Base(OmSolUP.get_Base());

            
            Matrix VelBUP_dq   = jacobian(VelBUP.transpose(),dq);
            Matrix VelBUP_dqT  = VelBUP_dq.transpose();
            Matrix OmSolUP_dq   = jacobian(OmSolUP.transpose(),dq);
            Matrix OmSolUP_dqT  = OmSolUP_dq.transpose();            
            
            
            
            
            Matrix RVel_mBG = sys.Rotation_Matrix ( VelBUP.get_Base(), mBG.get_Base());
            Matrix RmBG_OM  = sys.Rotation_Matrix ( mBG.get_Base(),OmSolUP.get_Base() );
            
            Matrix Maux = VelBUP_dqT*RVel_mBG*mBG.skew().transpose()*RmBG_OM*OmSolUP_dq;
            Matrix MauxT = Maux.transpose();
            
            
            Matrix Maux2(ddq.rows(),ddq.rows());
            Matrix RowITColUP;
            for ( int i = 0 ; i < OmSolUP_dqT.rows () ; i++ ) {
                Matrix RowITUP = OmSolUP_dqT.get_row(i)*IT;
    		    for ( int j = i ; j < OmSolUP_dq.cols () ; j++ ) {
                    Matrix Col = OmSolUP_dq.get_col(j);
                    RowITColUP = RowITUP*Col;
                    if (i==j){ 
                        Maux2 ( i , j ) = RowITColUP(0,0);
                    }
                    else {
                        Maux2 ( i , j ) = RowITColUP(0,0);
                        Maux2 ( j , i ) = RowITColUP(0,0);
                    }
               }
            } 
   
            M = M - mass*( VelBUP_dqT*VelBUP_dq ) - (Maux + MauxT) -  Maux2;  
            
            Matrix R_BG_xyz = sys.Rotation_Matrix (Base_xyz ,mBG.get_Base()  );
            Matrix R_VelBUP_xyz = sys.Rotation_Matrix (Base_xyz ,VelBUP.get_Base()  );
            
            //Matrix VelBUP_q     = jacobian(VelBUP.transpose(),q);
            //Matrix VelBUP_t     = jacobian(VelBUP.transpose(),get_Time_Symbol ());  
            Matrix OmSolUP_q  = jacobian(OmSolUP.transpose(),q);
            Matrix OmSolUP_t  = jacobian(OmSolUP.transpose(),get_Time_Symbol ());
            
            
            Vector3D mBG_O = mBG.change_Base(Base_xyz);
            Vector3D OmSol = (Angular_Velocity(Base_xyz,Solids[k]->get_Base())).change_Base(Base_xyz);
            Vector3D VelB  = (Velocity_Vector("abs",Solids[k]->get_Point() -> get_name(), Solids[k]-> get_name() )).change_Base(Base_xyz);
            Matrix VelB_q     = jacobian(VelB.transpose(),q);
            Matrix VelB_t     = jacobian(VelB.transpose(),get_Time_Symbol ()); 
            Matrix OmSol_q    = jacobian(OmSol.transpose(),q);
            Matrix OmSol_t    = jacobian(OmSol.transpose(),get_Time_Symbol ()); 
            
            
            //Matrix QUP1 = (mass*(VelBUP_q + R_VelBUP_xyz.transpose()*VelBUP2_q) -  R_BG_VelBUP * mBG.skew()*R_BG_xyz.transpose()*(OmSolUP1_q + OmSolUP2_q)     )*dq  + mass*R_VelBUP_xyz*VelB_t -(mBG.skew())*R_VelBUP_xyz*OmSol_t ;
            Matrix QUP1 =  R_VelBUP_xyz.transpose()*( (mass*VelB_q  - (mBG_O.skew())*OmSol_q)*dq + mass*VelB_t -(mBG_O.skew())*OmSol_t);
            Matrix QUP2 = RVel_mBG * OmSolUP.skew() * OmSolUP.skew() *  mBG;
            //Matrix QUP3 = (mBG.skew())*( ( R_BG_VelBUP.transpose()*VelBUP1_q + (R_VelBUP_xyz*R_BG_VelBUP).transpose()*VelBUP2_q ) *dq + R_VelBUP_xyz*VelBUP_t   );
            Matrix QUP3 = R_BG_xyz.transpose()*((mBG_O.skew()) * ( VelB_q*dq  + VelB_t));
            Matrix QUP4 = IT * ( OmSolUP_q*dq + OmSolUP_t );
            Matrix QUP5 = (OmSolUP.skew())*IT*OmSolUP ;

            Q = Q + VelBUP_dqT * (QUP1 + QUP2)  
                  + OmSolUP_dqT * (QUP3 + QUP4 + QUP5)
                ;
            /* -----------------------------------------------------------------------------------------------------------------*/
              

            
            
            /* -----------------------------------------------------------------------------------------------------------------*/
            //  DOWN
            /* -----------------------------------------------------------------------------------------------------------------*/
            /*Vector3D mBG_O = mBG.change_Base(Base_xyz);
            Matrix R_SOL_xyz = sys.Rotation_Matrix (Base_xyz ,Solids[k]->get_Base()  ); 
            Matrix IT_O = R_SOL_xyz*IT*R_SOL_xyz.transpose();
 
            Vector3D OmSol = (Angular_Velocity(Base_xyz,Solids[k]->get_Base())).change_Base(Base_xyz);

            Vector3D VelB  = (Velocity_Vector("abs",Solids[k]->get_Point() -> get_name(), Solids[k]-> get_name() )).change_Base(Base_xyz);

            Matrix OmSol_dq  = jacobian(OmSol.transpose(),dq);
            Matrix OmSol_dqT = OmSol_dq.transpose();
            
            
            Matrix Maux2(ddq.rows(),ddq.rows());
            Matrix RowITCol;
            for ( int i = 0 ; i < OmSol_dqT.rows () ; i++ ) {
                Matrix RowIT = OmSol_dqT.get_row(i)*IT_O;
    		    for ( int j = i ; j < OmSol_dq.cols () ; j++ ) {
                    Matrix Col = OmSol_dq.get_col(j);
                    RowITCol = RowIT*Col;
                    if (i==j){ 
                        Maux2 ( i , j ) = RowITCol(0,0);
                    }
                    else {
                        Maux2 ( i , j ) = RowITCol(0,0);
                        Maux2 ( j , i ) = RowITCol(0,0);
                    }
               }
            }
            Matrix VelB_dq   = jacobian(VelB.transpose(),dq);
            Matrix VelB_dqT  = VelB_dq.transpose();
            
            Matrix Maux = VelB_dqT*(mBG_O.skew()).transpose()*OmSol_dq;
            Matrix MauxT = Maux.transpose();
            
            M = M - mass*( VelB_dqT*VelB_dq ) - (Maux + MauxT) -  Maux2;

            Matrix VelB_q     = jacobian(VelB.transpose(),q);
            Matrix VelB_t     = jacobian(VelB.transpose(),get_Time_Symbol ()); 
       
            Matrix OmSol_q    = jacobian(OmSol.transpose(),q);
            Matrix OmSol_t    = jacobian(OmSol.transpose(),get_Time_Symbol ());

            
       
            //~ Q = Q + VelB_dqT * (  (mass*VelB_q  - (mBG_O.skew())*OmSol_q)*dq + mass*VelB_t -(mBG_O.skew())*OmSol_t )
            //~ //Q = Q + VelB_dqT * (  mass*(VelB_q  * dq + VelB_t) )  + VelB_dqT * ( -mBG_O.skew() * (OmSol_q*dq + OmSol_t))
                  //~ + VelB_dqT * (OmSol.skew() * (OmSol.skew() *  mBG_O))
                  //~ + OmSolUP_dqT * IT * ( OmSolUP_q*dq + OmSolUP_t ) 
                  //~ + OmSol_dqT * (mBG_O.skew()) * ( VelB_q*dq  + VelB_t)
                  //~ + OmSolUP_dqT*(OmSolUP.skew())*IT*OmSolUP
                  //~ ;
                  
            //~ Q = Q + VelB_dqT * (  (mass*VelB_q  - (mBG_O.skew())*OmSol_q)*dq + mass*VelB_t -(mBG_O.skew())*OmSol_t + OmSol.skew() * (OmSol.skew() *  mBG_O))
                  //~ + OmSolUP_dqT * (IT * ( OmSolUP_q*dq + OmSolUP_t ) + (OmSolUP.skew())*IT*OmSolUP)
                  //~ + OmSol_dqT * (mBG_O.skew()) * ( VelB_q*dq  + VelB_t)
                  //~ ;  
            
            Matrix Q1 = (mass*VelB_q  - (mBG_O.skew())*OmSol_q)*dq + mass*VelB_t -(mBG_O.skew())*OmSol_t;
            Matrix Q2 = OmSol.skew() * OmSol.skew() *  mBG_O;
             
            Matrix Q3 = (mBG_O.skew()) * ( VelB_q*dq  + VelB_t);
            Matrix Q4 = IT_O * ( OmSol_q*dq + OmSol_t ) ;
            Matrix Q5 = (OmSol.skew())*IT_O*OmSol;

            Q = Q  + VelB_dqT * (Q1 + Q2)
                  + OmSol_dqT * (Q3 + Q4 + Q5)
                  ;
            */     
            /* -----------------------------------------------------------------------------------------------------------------*/

         
            

        }

        for (int k=0; k< Wrenches.size(); k++) {
    	    if ( Wrenches[k]-> get_Type () != "Inertia"){
                //Q = Q - GenForce(Wrenches[k]);
                gravity = UP;Q = Q - GenForce(Wrenches[k]);gravity = DOWN;
            }    
        }
    }
        
    //~ if (aux_coordinates.size()>0){
        //~ Matrix ZeroM12 = Matrix(ddq.rows(),ddqaux.rows());
        //~ Matrix ZeroM21 = Matrix(ddqaux.rows(),ddq.rows());   
        //~ Matrix ZeroM22 = Matrix(ddqaux.rows(),ddqaux.rows());
        //~ Matrix ZeroQ = Matrix(ddqaux.rows(),1);
        //~ M = Matrix(2,2,&M,&ZeroM12,&ZeroM21,&ZeroM22);
        //~ Q = Matrix(2,1,&Q,&ZeroQ);
    //~ }

    
    Matrix MQ = Matrix("MQ",1,2,&M,&Q);
        
    // Dynamic_Equations ==> M * ddq + V * epsilon - Q = 0 <===> Q = -(Dynamic_Equations-(M*ddq+V*epsilon));
    //~ if ( method == LAGRANGE){
        //~ Matrix dPhi_dqT = dPhi_dq.transpose();
        //~ Zero = Matrix(dPhi_dq.rows(),dPhi_dqT.cols());
        //~ MXdPhi_dqZero = Matrix(2,2,&M,&dPhi_dqT,&dPhi_dq,&Zero);
        //~ * new_Matrix( "dPhi_dqT" ,dPhi_dqT );
    //~ }
    //~ else if ( method == VIRTUAL_POWER){
        //~ Matrix V = jacobian(Dynamic_Equations.transpose(),epsilon);
        //~ Zero = Matrix(dPhi_dq.rows(),V.cols());
        //~ MXdPhi_dqZero = Matrix(2,2,&M,&V,&dPhi_dq,&Zero);
        //~ * new_Matrix( "V" ,V );
    //~ }
    //~ else { cout << "Define LAGRANGE or VIRTUAL_POWER" << endl; }

    * new_Matrix( "PhiInit"     ,PhiInit );
    * new_Matrix( "dPhiInit"    ,dPhiInit );
    * new_Matrix( "PhiInit_q"   ,PhiInit_q  );
    * new_Matrix( "dPhiInit_dq" ,dPhiInit_dq  );
    * new_Matrix( "BetaInit"    ,BetaInit );
    * new_Matrix( "Phi_q"       ,Phi_q );
    * new_Matrix( "dPhi_dq"     ,dPhi_dq );
    * new_Matrix( "M",M );     //* new_Matrix( "C"     ,C );//* new_Matrix( "K"     ,K );
    * new_Matrix( "Q",Q );
    * new_Matrix( "MQ",MQ );   
    //~ * new_Matrix( "Qgamma",Qgamma );
    //~ * new_Matrix( "Zero" ,Zero );
    //~ * new_Matrix( "MXdPhi_dqZero",MXdPhi_dqZero );
}


void System::Matrix_Calculation(lst coord_indep_init ,lst vel_indep_init , Matrix &Dynamic_Equations, System &sys, int method){
    Matrix Phi(0,1);
    Matrix dPhiNH(0,1);
    Matrix_Calculation(Phi,coord_indep_init ,vel_indep_init , Dynamic_Equations, sys, method, dPhiNH);
}

void System::Matrix_Calculation(Matrix &Phi,lst coord_indep_init ,lst vel_indep_init , Matrix &Dynamic_Equations, System &sys, int method){
    Matrix dPhiNH(0,1);
    Matrix_Calculation(Phi,coord_indep_init ,vel_indep_init , Dynamic_Equations, sys, method, dPhiNH);
}

void System::Matrix_Calculation(lst coord_indep_init ,lst vel_indep_init ,System &sys, int method){
    Matrix Phi(0,1);
    Matrix dPhiNH(0,1);
    Matrix Dynamic_Equations(0,1);
    Matrix_Calculation(Phi,coord_indep_init ,vel_indep_init , Dynamic_Equations, sys, method, dPhiNH);
}
void System::Matrix_Calculation(Matrix &Phi,lst coord_indep_init ,lst vel_indep_init,  System &sys, int method){
    Matrix dPhiNH(0,1);
    Matrix Dynamic_Equations(0,1);
    Matrix_Calculation(Phi,coord_indep_init ,vel_indep_init , Dynamic_Equations, sys, method, dPhiNH);
}
void System::Matrix_Calculation(Matrix &Phi, lst coord_indep_init ,lst vel_indep_init , System &sys, int method, Matrix &dPhiNH){
    Matrix Dynamic_Equations(0,1);
    Matrix_Calculation(Phi,coord_indep_init ,vel_indep_init , Dynamic_Equations, sys, method, dPhiNH);
}




void System::export_Dynamic_Simulation (System &sys, int order, int maple){
    
    try{ if ( (order != CMO) && (order != RMO)  ) throw 1;}
    catch ( int e ) {outError ( "ERR -  Parameter 'int order' must be CMO  or RMO" );}

    try{ if ( (maple != MAPLE_ON) && (maple != MAPLE_OFF)  ) throw 1;}
    catch ( int e ) {outError ( "ERR -  Parameter 'int maple' must be MAPLE_ON or MAPLE_OFF" );}
    
    export_defines(); //->"defines.h"

    export_time_H(); //->"time_3D_mec.h"
    export_time_C(); //->"time_3D_mec.c"

    //~ if (aux_coordinates.size()>0){
        //~ coordinates.insert( coordinates.end(),aux_coordinates.begin(), aux_coordinates.end() );
        //~ velocities.insert( velocities.end(),aux_velocities.begin(), aux_velocities.end() );
        //~ accelerations.insert( accelerations.end(),aux_accelerations.begin(), aux_accelerations.end() );
        //~ aux_coordinates.clear();aux_velocities.clear();aux_accelerations.clear();
    //~ }
    
    export_gen_coord_H(); //->"gen_coord.h"
    export_gen_coord_C(); //->"gen_coord.c"

    export_gen_vel_H(); //->"gen_vel.h"
    export_gen_vel_C(); //->"gen_vel.c"

    export_gen_accel_H(); //->"gen_accel.h"
    export_gen_accel_C(); //->"gen_accel.c"
    
    if (aux_coordinates.size()> 0 ){
        export_gen_auxcoord_H(); //->"gen_auxcoord.h"
        export_gen_auxcoord_C(); //->"gen_auxcoord.c"
        
        export_gen_auxvel_H(); //->"gen_auxvel.h"
        export_gen_auxvel_C(); //->"gen_auxvel.c"
        
        export_gen_auxaccel_H(); //->"gen_auxaccel.h"
        export_gen_auxaccel_C(); //->"gen_auxaccel.c"
    }
    
    export_param_H(); //->"param.h"
    export_param_C(); //->"param.c"

    export_inputs_H(); //->"inputs.h"
    export_inputs_C(); //->"inputs.c"

    export_unknowns_H(); //->"unknowns.h"
    export_unknowns_C(); //->"unknowns.c"    
    
    Matrix PhiInit       = *get_Matrix( "PhiInit" );
    Matrix dPhiInit      = *get_Matrix( "dPhiInit" );
    Matrix PhiInit_q     = *get_Matrix( "PhiInit_q" );
    Matrix dPhiInit_dq   = *get_Matrix( "dPhiInit_dq" );
    Matrix BetaInit      = *get_Matrix( "BetaInit" );
    Matrix Phi           = *get_Matrix( "Phi" );
    Matrix Beta          = *get_Matrix( "Beta" );
    Matrix Gamma         = *get_Matrix( "Gamma" );
    Matrix Phi_q         = *get_Matrix( "Phi_q" );
    Matrix dPhi_dq       = *get_Matrix( "dPhi_dq" );
    Matrix M             = *get_Matrix( "M" );
    Matrix Q             = *get_Matrix( "Q" );
    Matrix MQ             = *get_Matrix( "MQ" );    
    //Matrix MXdPhi_dqZero = *get_Matrix( "MXdPhi_dqZero" );
    //Matrix Qgamma        = *get_Matrix( "Qgamma" );
    Matrix Output        = *get_Matrix( "Output" );
    Matrix Energy        = *get_Matrix( "Energy" );    
    
    
    if ( maple == MAPLE_ON && atomization == NO ){
        
        int systemRet;
        export_Matrix_MAPLE("Phi", "_Phi", Phi, order);
        systemRet = system("maple Phi.mpl > Phi.log && bash ./replace.bash Phi_maple_include.c Phi_maple_include.c ");

        export_Matrix_MAPLE("Beta", "_Beta", Beta, order);
        systemRet = system("maple Beta.mpl > Beta.log && bash ./replace.bash Beta_maple_include.c Beta_maple_include.c ");

        export_Matrix_MAPLE("Gamma", "_Gamma", Gamma, order);
        systemRet = system("maple Gamma.mpl > Gamma.log && bash ./replace.bash Gamma_maple_include.c Gamma_maple_include.c ");
        
        export_Matrix_MAPLE("PhiInit", "_PhiInit", PhiInit, order);
        systemRet = system("maple PhiInit.mpl > PhiInit.log && bash ./replace.bash PhiInit_maple_include.c PhiInit_maple_include.c ");

        export_Matrix_MAPLE("PhiInit_q", "_PhiInit_q", PhiInit_q, order);
        systemRet = system("maple PhiInit_q.mpl > PhiInit_q.log && bash ./replace.bash PhiInit_q_maple_include.c PhiInit_q_maple_include.c ");

        export_Matrix_MAPLE("dPhiInit_dq", "_dPhiInit_dq", dPhiInit_dq, order);
        systemRet = system("maple dPhiInit_dq.mpl > dPhiInit_dq.log && bash ./replace.bash dPhiInit_dq_maple_include.c dPhiInit_dq_maple_include.c ");

        export_Matrix_MAPLE("BetaInit", "_BetaInit", BetaInit, order);
        systemRet = system("maple BetaInit.mpl > BetaInit.log && bash ./replace.bash BetaInit_maple_include.c BetaInit_maple_include.c ");

        export_Matrix_MAPLE("Phi_q", "_Phi_q", Phi_q, order);
        systemRet = system("maple Phi_q.mpl > Phi_q.log && bash ./replace.bash Phi_q_maple_include.c Phi_q_maple_include.c ");

        export_Matrix_MAPLE("dPhi_dq", "_dPhi_dq", dPhi_dq, order);
        systemRet = system("maple dPhi_dq.mpl > dPhi_dq.log && bash ./replace.bash dPhi_dq_maple_include.c dPhi_dq_maple_include.c ");

        export_Matrix_MAPLE("M", "_M", M, order,1); //This matrix will be symmetric
        systemRet = system("maple M.mpl > M.log && bash ./replace.bash M_maple_include.c M_maple_include.c ");

        export_Matrix_MAPLE("Q", "_Q", Q, order);
        systemRet = system("maple Q.mpl > Q.log && bash ./replace.bash Q_maple_include.c Q_maple_include.c ");
        
        export_Matrix_MAPLE("MQ", "_MQ", MQ, order);
        systemRet = system("maple MQ.mpl > MQ.log && bash ./replace.bash MQ_maple_include.c MQ_maple_include.c ");       

        //~ export_Matrix_MAPLE("MXdPhi_dqZero", "_MXdPhi_dqZero", MXdPhi_dqZero, order,1); //This matrix will be symmetric
        //~ systemRet = system("maple MXdPhi_dqZero.mpl > MXdPhi_dqZero.log && bash ./replace.bash MXdPhi_dqZero_maple_include.c MXdPhi_dqZero_maple_include.c &");

        //~ export_Matrix_MAPLE("Qgamma", "_Qgamma", Qgamma, order);
        //~ systemRet = system("maple Qgamma.mpl > Qgamma.log && bash ./replace.bash Qgamma_maple_include.c Qgamma_maple_include.c &");

        export_Matrix_MAPLE("Output", "_Output", Output, order);
        systemRet = system("maple Output.mpl > Output.log && bash ./replace.bash Output_maple_include.c Output_maple_include.c ");

        export_Matrix_MAPLE("Energy", "_Energy", Energy, order);
        systemRet = system("maple Energy.mpl > Energy.log && bash ./replace.bash Energy_maple_include.c Energy_maple_include.c ");
        
        systemRet = system("while [ \"$(pidof -x cmaple)\" ]; do sleep 1; done");
        systemRet = system("while [ \"$(pidof -x replace.bash)\" ]; do sleep 1; done");


        // MATLAB exportation
        export_init_function_MATLAB();
        export_function_MATLAB("Phi", "Phi_", Phi);
        export_function_MATLAB("Beta", "Beta_", Beta);
        export_function_MATLAB("Gamma", "Gamma_", Gamma);    
        export_function_MATLAB("PhiInit" ,"PhiInit_" ,PhiInit);
        export_function_MATLAB("PhiInit_q","PhiInit_q_",PhiInit_q);
        export_function_MATLAB("dPhiInit_dq" ,"dPhiInit_dq_" ,dPhiInit_dq);
        export_function_MATLAB("BetaInit" ,"BetaInit_" ,BetaInit );
        export_function_MATLAB("Phi_q", "Phi_q_", Phi_q);
        export_function_MATLAB("dPhi_dq", "dPhi_dq_", dPhi_dq);
        export_function_MATLAB("M", "M_", M);
        export_function_MATLAB("Q", "Q_", Q);
        //export_function_MATLAB("MXdPhi_dqZero", "MXdPhi_dqZero_", MXdPhi_dqZero);
        //export_function_MATLAB("Qgamma", "Qgamma_", Qgamma);
        export_function_MATLAB("Output", "Output_", Output);
        export_function_MATLAB("Energy", "Energy_", Energy);

    } 
       
    else if ( atomization == YES ){
        
        lst used_atom_list;

        cout <<" PhiInit Optimizing"<<endl;
        lst new_atom_list_PhiInit, new_exp_list_PhiInit;        
        matrix_list_optimize (PhiInit, new_atom_list_PhiInit, new_exp_list_PhiInit);
        
        cout <<" PhiInit_q Optimizing"<<endl;
        lst new_atom_list_PhiInit_q, new_exp_list_PhiInit_q;        
        matrix_list_optimize (PhiInit_q, new_atom_list_PhiInit_q, new_exp_list_PhiInit_q); 
                 
        cout <<" dPhiInit_dq Optimizing"<<endl;;        
        lst new_atom_list_dPhiInit_dq, new_exp_list_dPhiInit_dq;        
        matrix_list_optimize (dPhiInit_dq, new_atom_list_dPhiInit_dq, new_exp_list_dPhiInit_dq);
                  
        cout <<" BetaInit Optimizing"<<endl;        
        lst new_atom_list_BetaInit, new_exp_list_BetaInit;        
        matrix_list_optimize (BetaInit, new_atom_list_BetaInit, new_exp_list_BetaInit); 
               
        cout << " Phi Optimizing"<<endl;
        lst new_atom_list_Phi, new_exp_list_Phi;        
        matrix_list_optimize (Phi, new_atom_list_Phi, new_exp_list_Phi);
                
        cout << " Beta Optimizing"<<endl;        
        lst new_atom_list_Beta, new_exp_list_Beta;        
        matrix_list_optimize (Beta, new_atom_list_Beta, new_exp_list_Beta);
        
         cout << " Gamma Optimizing"<<endl;        
        lst new_atom_list_Gamma, new_exp_list_Gamma;        
        matrix_list_optimize (Gamma, new_atom_list_Gamma, new_exp_list_Gamma);
               
        cout <<" Phi_q Optimizing"<<endl;       
        lst new_atom_list_Phi_q, new_exp_list_Phi_q;        
        matrix_list_optimize (Phi_q, new_atom_list_Phi_q, new_exp_list_Phi_q); 
               
        cout <<" dPhi_dq Optimizing"<<endl;        
        lst new_atom_list_dPhi_dq, new_exp_list_dPhi_dq;        
        matrix_list_optimize (dPhi_dq, new_atom_list_dPhi_dq, new_exp_list_dPhi_dq);
        
        cout <<" M Optimizing"<<endl;        
        lst new_atom_list_M, new_exp_list_M;        
        matrix_list_optimize (M, new_atom_list_M, new_exp_list_M);
        
        cout <<" Q Optimizing"<<endl;       
        lst new_atom_list_Q, new_exp_list_Q;        
        matrix_list_optimize (Q, new_atom_list_Q, new_exp_list_Q);
        
        cout <<" MQ Optimizing"<<endl;       
        lst new_atom_list_MQ, new_exp_list_MQ;        
        matrix_list_optimize (MQ, new_atom_list_MQ, new_exp_list_MQ);
                        
        //~ cout <<" MXdPhi_dqZero Optimizing"<<endl;        
        //~ lst new_atom_list_MXdPhi_dqZero, new_exp_list_MXdPhi_dqZero;        
        //~ matrix_list_optimize (MXdPhi_dqZero, new_atom_list_MXdPhi_dqZero, new_exp_list_MXdPhi_dqZero);
                                        
        //~ cout <<" Qgamma Optimizing"<<endl;        
        //~ lst new_atom_list_Qgamma, new_exp_list_Qgamma;        
        //~ matrix_list_optimize (Qgamma, new_atom_list_Qgamma, new_exp_list_Qgamma);
                
        cout <<" Output  Optimizing"<<endl;        
        lst new_atom_list_Output, new_exp_list_Output;        
        matrix_list_optimize (Output, new_atom_list_Output, new_exp_list_Output); 
               
        cout <<" Energy  Optimizing"<<endl;        
        lst new_atom_list_Energy, new_exp_list_Energy;        
        matrix_list_optimize (Energy, new_atom_list_Energy, new_exp_list_Energy);
        
        cout <<" Code Exporting "<<endl; 
        export_Matrix_C	("PhiInit","_PhiInit",PhiInit, new_atom_list_PhiInit, new_exp_list_PhiInit ,order);
        export_Matrix_C	("PhiInit_q","_PhiInit_q",PhiInit_q, new_atom_list_PhiInit_q, new_exp_list_PhiInit_q ,order);
        export_Matrix_C	("dPhiInit_dq","_dPhiInit_dq",dPhiInit_dq, new_atom_list_dPhiInit_dq, new_exp_list_dPhiInit_dq ,order);
        export_Matrix_C	("BetaInit","_BetaInit",BetaInit, new_atom_list_BetaInit, new_exp_list_BetaInit ,order);
        export_Matrix_C	("Phi","_Phi",Phi, new_atom_list_Phi, new_exp_list_Phi ,order);
        export_Matrix_C	("Beta","_Beta",Beta, new_atom_list_Beta, new_exp_list_Beta ,order);
        export_Matrix_C	("Gamma","_Gamma",Gamma, new_atom_list_Gamma, new_exp_list_Gamma ,order);
        export_Matrix_C	("Phi_q","_Phi_q",Phi_q, new_atom_list_Phi_q, new_exp_list_Phi_q ,order);
        export_Matrix_C	("dPhi_dq","_dPhi_dq",dPhi_dq, new_atom_list_dPhi_dq, new_exp_list_dPhi_dq ,order);
        export_Matrix_C	("M","_M",M, new_atom_list_M, new_exp_list_M ,order);
        export_Matrix_C	("Q","_Q",Q, new_atom_list_Q, new_exp_list_Q ,order);
        export_Matrix_C	("MQ","_MQ",MQ, new_atom_list_MQ, new_exp_list_MQ ,order);       
        //~ export_Matrix_C	("MXdPhi_dqZero","_MXdPhi_dqZero",MXdPhi_dqZero, new_atom_list_MXdPhi_dqZero, new_exp_list_MXdPhi_dqZero ,order);
        //~ export_Matrix_C	("Qgamma","_Qgamma",Qgamma, new_atom_list_Qgamma, new_exp_list_Qgamma ,order);
        export_Matrix_C	("Output","_Output",Output, new_atom_list_Output, new_exp_list_Output ,order);
        export_Matrix_C	("Energy","_Energy",Energy, new_atom_list_Energy, new_exp_list_Energy ,order);
        
        
        // MATLAB exportation atomized
        /*
        export_init_function_MATLAB();
        export_function_MATLAB("Phi", "Phi_", Phi, new_atom_list_Phi, new_exp_list_Phi );
        export_function_MATLAB("Beta", "Beta_", Beta, new_atom_list_Beta, new_exp_list_Beta);
        export_function_MATLAB("Gamma", "Gamma_", Gamma, new_atom_list_Gamma, new_exp_list_Gamma);    
        export_function_MATLAB("PhiInit" ,"PhiInit_" ,PhiInit, new_atom_list_PhiInit, new_exp_list_PhiInit);
        export_function_MATLAB("PhiInit_q","PhiInit_q_",PhiInit_q, new_atom_list_PhiInit_q, new_exp_list_PhiInit_q);
        export_function_MATLAB("dPhiInit_dq" ,"dPhiInit_dq_" ,dPhiInit_dq, new_atom_list_dPhiInit_dq, new_exp_list_dPhiInit_dq);
        export_function_MATLAB("BetaInit" ,"BetaInit_" ,BetaInit, new_atom_list_BetaInit, new_exp_list_BetaInit  );
        export_function_MATLAB("Phi_q", "Phi_q_", Phi_q, new_atom_list_Phi_q, new_exp_list_Phi_q);
        export_function_MATLAB("dPhi_dq", "dPhi_dq_", dPhi_dq, new_atom_list_dPhi_dq, new_exp_list_dPhi_dq);
        export_function_MATLAB("M", "M_", M, new_atom_list_M, new_exp_list_M);
        export_function_MATLAB("Q", "Q_", Q, new_atom_list_Q, new_exp_list_Q);
        export_function_MATLAB("MQ", "MQ_", MQ, new_atom_list_MQ, new_exp_list_MQ);       
        //export_function_MATLAB("MXdPhi_dqZero", "MXdPhi_dqZero_", MXdPhi_dqZero, new_atom_list_MXdPhi_dqZero, new_exp_list_MXdPhi_dqZero);
        //export_function_MATLAB("Qgamma", "Qgamma_", Qgamma, new_atom_list_Qgamma, new_exp_list_Qgamma);
        export_function_MATLAB("Output", "Output_", Output, new_atom_list_Output, new_exp_list_Output);
        export_function_MATLAB("Energy", "Energy_", Energy, new_atom_list_Energy, new_exp_list_Energy);   
        */
        
        //  int acc, int tim, int inp, int unks
        export_environment_m();
        string s_q= "q,";
        string s_dq= "dq,";
        string s_ddq= "ddq,";
        if (aux_coordinates.size()>0){
          s_q = "q,qaux,";
          s_dq = "dq,dqaux,";         
          s_ddq = "ddq,ddqaux,";           
        }

        export_function_MATLAB("Phi", "Phi_", Phi, new_atom_list_Phi, new_exp_list_Phi,s_q +"time,param");
        export_function_MATLAB("Beta", "Beta_", Beta, new_atom_list_Beta, new_exp_list_Beta,s_q +"time,param");
        export_function_MATLAB("Gamma", "Gamma_", Gamma, new_atom_list_Gamma, new_exp_list_Gamma,s_q + s_dq + "time,param");    
        export_function_MATLAB("PhiInit" ,"PhiInit_" ,PhiInit, new_atom_list_PhiInit, new_exp_list_PhiInit,s_q +"time,param");
        export_function_MATLAB("PhiInit_q","PhiInit_q_",PhiInit_q, new_atom_list_PhiInit_q, new_exp_list_PhiInit_q,s_q +"time,param");
        export_function_MATLAB("dPhiInit_dq" ,"dPhiInit_dq_" ,dPhiInit_dq, new_atom_list_dPhiInit_dq, new_exp_list_dPhiInit_dq,s_q +"time,param");
        export_function_MATLAB("BetaInit" ,"BetaInit_" ,BetaInit, new_atom_list_BetaInit, new_exp_list_BetaInit,s_q +"time,param");
        export_function_MATLAB("Phi_q", "Phi_q_", Phi_q, new_atom_list_Phi_q, new_exp_list_Phi_q,s_q +"time,param");
        export_function_MATLAB("dPhi_dq", "dPhi_dq_", dPhi_dq, new_atom_list_dPhi_dq, new_exp_list_dPhi_dq,s_q +"time,param");
        export_function_MATLAB("M", "M_", M, new_atom_list_M, new_exp_list_M,"q,time,param");
        export_function_MATLAB("Q", "Q_", Q, new_atom_list_Q, new_exp_list_Q, s_q + s_dq +"time,param,inputs");
        export_function_MATLAB("MQ", "MQ_", MQ, new_atom_list_MQ, new_exp_list_MQ, s_q + s_dq + "time,param,inputs");       
        //export_function_MATLAB2("MXdPhi_dqZero", "MXdPhi_dqZero_", MXdPhi_dqZero, new_atom_list_MXdPhi_dqZero, new_exp_list_MXdPhi_dqZero"q,time,param");
        //export_function_MATLAB2("Qgamma", "Qgamma_", Qgamma, new_atom_list_Qgamma, new_exp_list_Qgamma,"q,dq,time,param,inputs");
        export_function_MATLAB("Output", "Output_", Output, new_atom_list_Output, new_exp_list_Output,s_q + s_dq + s_ddq +"unknowns,time,param,inputs");
        export_function_MATLAB("Energy", "Energy_", Energy, new_atom_list_Energy, new_exp_list_Energy,s_q + s_dq + s_ddq +"time,param"); 



        //~ cout <<" Total atoms = " << atoms.size()<<endl;
        //~ ofstream atom_file;
        //~ atom_file.open( ( "atoms.txt" ) );
        //~ for ( int i = 0 ; i < atoms.size() ; i++ ){
           //~ //cout<< atoms[i] <<" = " << atoms[i].get_expression()<<endl; 
           //~ atom_file<< atoms[i] <<" = " << atoms[i].get_expression()<<endl;
        //~ }
        //~ atom_file.close();
    }    
    else{
        cout << "Exporting without any kind of optimization" << endl;
        
        export_Matrix_C	("PhiInit","_PhiInit",PhiInit,order);
        export_Matrix_C	("PhiInit_q","_PhiInit_q",PhiInit_q,order);
        export_Matrix_C	("dPhiInit_dq","_dPhiInit_dq",dPhiInit_dq,order);
        export_Matrix_C	("BetaInit","_BetaInit",BetaInit,order);
        export_Matrix_C	("Phi","_Phi",Phi,order);
        export_Matrix_C	("Beta","_Beta",Beta,order);
        export_Matrix_C	("Gamma","_Gamma",Gamma ,order);
        export_Matrix_C	("Phi_q","_Phi_q",Phi_q,order);
        export_Matrix_C	("dPhi_dq","_dPhi_dq",dPhi_dq,order);
        export_Matrix_C	("M","_M",M,order);
        export_Matrix_C	("Q","_Q",Q ,order);
        export_Matrix_C	("MQ","_MQ",MQ ,order);        
        //export_Matrix_C	("MXdPhi_dqZero","_MXdPhi_dqZero",MXdPhi_dqZero,order);
        //export_Matrix_C	("Qgamma","_Qgamma",Qgamma, order);
        export_Matrix_C	("Output","_Output",Output, order);
        export_Matrix_C	("Energy","_Energy",Energy, order);
        
        // MATLAB exportation
        export_init_function_MATLAB();
        export_function_MATLAB("Phi", "Phi_", Phi);
        export_function_MATLAB("Beta", "Beta_", Beta);
        export_function_MATLAB("Gamma", "Gamma_", Gamma);    
        export_function_MATLAB("PhiInit" ,"PhiInit_" ,PhiInit);
        export_function_MATLAB("PhiInit_q","PhiInit_q_",PhiInit_q);
        export_function_MATLAB("dPhiInit_dq" ,"dPhiInit_dq_" ,dPhiInit_dq);
        export_function_MATLAB("BetaInit" ,"BetaInit_" ,BetaInit );
        export_function_MATLAB("Phi_q", "Phi_q_", Phi_q);
        export_function_MATLAB("dPhi_dq", "dPhi_dq_", dPhi_dq);
        export_function_MATLAB("M", "M_", M);
        export_function_MATLAB("Q", "Q_", Q);
        export_function_MATLAB("MQ", "MQ_", MQ);        
        //export_function_MATLAB("MXdPhi_dqZero", "MXdPhi_dqZero_", MXdPhi_dqZero);
        //export_function_MATLAB("Qgamma", "Qgamma_", Qgamma);
        export_function_MATLAB("Output", "Output_", Output);
        export_function_MATLAB("Energy", "Energy_", Energy);  
        
    }    

       

}
 


/*********************************************************************************************************
**************************************** DESTRUCTOR FUNCTION *********************************************
*********************************************************************************************************/

/*
System's destructor method
*/
System::~System ( void ) {}




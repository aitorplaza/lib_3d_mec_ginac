#ifndef BASE_H
#define BASE_H

#include "Vector3D.h"
#include "Matrix.h"
class System;

using GiNaC::ex;
using GiNaC::lst;
using std::string;

	class Base {

		//Atributes

    		string name;
    		Matrix rotation_tupla;
    		ex rotation_angle;
    		Base * previous_base;
		System* system;

	private:

		//Private methods

		Matrix euler_parameter_to_rotation_matrix ( Matrix phi , ex expression );
		Matrix euler_parameter_to_angular_velocity ( Matrix phi , ex expression );
		void init( string name , Base * base , Matrix rotation_tupla , ex rotation_angle , System * system );

 	public:

		//Constructors

		Base () {name="ERROR";}
		Base ( string name, Base * previous_base , Matrix rotation_tupla , ex rotation_angle );
		Base ( string name, Base * previous_base , ex expression1 , ex expression2 , ex expression3 , ex rotation_angle );
		Base ( string name, Base * previous_base , Matrix rotation_tupla , ex rotation_angle , System * system );

		//Access methods
		
		string get_name ( void );
		Matrix get_Rotation_Tupla ( void );
		Base * get_Previous_Base ( void );
		ex get_Rotation_Angle ( void );
		void set_name ( string new_name );
		void set_Previous_Base ( Base * new_previous_base );
		void set_System ( System * system );

		//Public methods

		Matrix rotation_matrix ( void );
		Vector3D angular_velocity ( void );
		Vector3D angular_acceleration ( void );
        
		//Destructor
		~Base ( void );
	};

#endif // BASE_H

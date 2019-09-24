#ifndef POINT_H
#define POINT_H

#include "Vector3D.h"
class System;

using std::string;

	class Point{

		//Atributes

		string name;
		Point * previous_point;
		Vector3D * position_vector;

	public:

		//Constructors

		Point ( void );
		Point ( string name , Point * previous_point , Vector3D * position_vector);
		Point ( string name , string previous_point_name , string position_vector_point);

		//Access methods

		Point * get_Previous_Point ( void );
		Vector3D * get_Position_Vector ( void );
		string get_name ( void );
		void set_name ( string new_name );

		//Destructors

		~Point ( void );
	};

#endif // POINT_H

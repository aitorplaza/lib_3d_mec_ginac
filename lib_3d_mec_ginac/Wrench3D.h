#ifndef TORSOR3D_H
#define TORSOR3D_H

#include "Base.h"
#include "Point.h"
#include "GL/gl.h"
#include "symbol_numeric.h"
#include "Solid.h"

#include "Matrix.h"
#include "Vector3D.h"


class Vector3D;

class System;

using std::string;

	class Wrench3D{
		//Atributes
		System * system;
		string name;
		Vector3D F;
		Vector3D M;
		Point * P;
		Solid * Sol;
		string type;

		private:
		//Private methods
		void init (string name, Vector3D F, Vector3D M , Point * P, Solid * Sol, string type, System * system);
        //static Wrench3D Operations ( const Wrench3D & Wrench3DA , const Wrench3D & Wrench3DB , const int flag );
		public:

		//Constructors

		Wrench3D ( void );		
		Wrench3D (string name, Vector3D F, Vector3D M , Point * P, Solid * Sol, string type);
 

		//Access methods
		string get_name ( void );
		Vector3D get_Force ( void );
		Vector3D get_Moment ( void );
		Point * get_Point ( void );
		Solid * get_Solid ( void );
		string get_Type ( void );
        void set_System ( System * new_system );
        
		//Utility methods
        Wrench3D unatomize ( void );
        //Operations
        Wrench3D at_Point ( Point * PointB );
		friend Wrench3D operator + ( const Wrench3D & Wrench3DA , const Wrench3D & Wrench3DB );
		friend Wrench3D operator - ( const Wrench3D & Wrench3DA , const Wrench3D & Wrench3DB );
		friend Wrench3D operator - ( const Wrench3D & Wrench3DA );
		friend ex operator * ( const Wrench3D & Wrench3DA , const Wrench3D & Wrench3DB );
		friend Wrench3D operator * ( const Wrench3D & Wrench3DA , const ex & expression );
		friend Wrench3D operator * ( const ex & expression , const Wrench3D & Wrench3DA );
		friend ostream& operator << ( ostream& os , const Wrench3D & Wrench3DA );

		//Destructor

		~Wrench3D ( void );
	};




#endif // TORSOR3D_H



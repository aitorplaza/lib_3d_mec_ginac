#ifndef TORSOR3D_H
#define TORSOR3D_H

#include "Base.h"
#include "Point.h"
#include "GL/gl.h"
#include "symbol_numeric.h"
#include "Solid.h"
class System;

using std::string;

	class Wrench3D{

		//Atributes
		string name;
		Vector3D F;
		Vector3D M;
		Point * P;
		Solid * Sol;
		string type;

		private:
		//Private methods
		void init (string name, Vector3D F, Vector3D M , Point * P, Solid * Sol, string type);

		public:

		//Constructors

		Wrench3D ( void );		
		Wrench3D (string name, Vector3D F, Vector3D M , Point * P, Solid * Sol, string type);
 

		//Access methods
		string get_name ( void );
		Vector3D get_Force ( void );
		Vector3D get_Momentum ( void );
		Point * get_Point ( void );
		Solid * get_Solid ( void );
		string get_Type ( void );

		//Utility methods



		//Destructor

		~Wrench3D ( void );
	};




#endif // TORSOR3D_H



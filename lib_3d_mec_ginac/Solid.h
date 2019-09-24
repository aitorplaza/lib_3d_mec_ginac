#ifndef SOLID_H
#define SOLID_H

#include "Base.h"
#include "Point.h"
#include "Frame.h"
//#include "Vector3D.h"
#include "Tensor3D.h"
//#include "Torsor3D.h"
#include "symbol_numeric.h"

class System;

/*using GiNaC::ex;
using std::ostream;
using std::string;*/


	class Solid : public Frame{

		//Atributes

		Vector3D * CM;
		Tensor3D * IT;
		Point * G;
		symbol_numeric * mass;

		private:
		void init ( string name , Point * point , Base * base, symbol_numeric * new_mass , Vector3D * new_CM, Tensor3D * new_IT,Point * new_G);
		//Private methods		


		public:

		//Constructors

		Solid ( void );
		//Solid ( string name , Point * point , Base * base );
		Solid ( string name , Point * point , Base * base, symbol_numeric * new_mass , Vector3D * new_CM, Tensor3D * new_IT, Point * new_G);

		//Access methods
	
		Vector3D * get_CM ( void );
		Tensor3D * get_IT ( void );
		symbol_numeric *get_mass ( void );
		Point * get_G(void);

		//Destructor

		~Solid ( void );

	};

#endif // SOLID_H

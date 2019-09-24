#ifndef FRAME_H
#define FRAME_H

#include "Base.h"
#include "Point.h"
#include "GL/gl.h"
#include "symbol_numeric.h"
class System;

using std::string;

	class Frame {

		//Atributes

		string name;
		Point * point;
		Base * base;
		numeric scale;
		GLdouble OpenGLTransformMatrix[16];

		//Private methods
		void init (string name , Point * point , Base * base, numeric scale );

	public:

		//Constructors

		Frame ( void );
		Frame ( Point * point , Base * base);		
		Frame ( string name , Point * point , Base * base);
		Frame ( string name , Point * point , Base * base, numeric scale);
		//Access methods

		Point * get_Point ( void );
		Base * get_Base ( void );
		string get_name ( void );
		numeric get_scale ( void );
		void set_Base ( Base * new_base );
		void set_Point ( Point * new_point );
		void set_name ( string new_name );

		//Utility methods

		GLdouble * get_absOpenGLTransformMatrix ();

		//Destructor

		~Frame ( void );
	};

#endif // FRAME_H

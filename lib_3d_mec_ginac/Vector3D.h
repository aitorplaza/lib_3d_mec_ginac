#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Matrix.h"
class System;
class Frame;
class Base;

using GiNaC::ex;
using GiNaC::relational;
using GiNaC::matrix;
using std::ostream;
using std::string;


	class Vector3D : public Matrix{

			//Atributes

			Base * base;
			System * system;

		private:

			//Private methods

			void init ( string name , matrix mat , Base * base , System * system );
			static Vector3D Operations ( const Vector3D & Vector3DA , const Vector3D & Vector3DB , const int flag );

		public:

			//Constructors

			//Vector3D () : Matrix () {name="NULL";}
			Vector3D ( string name , Base * base );
			Vector3D ( string name , Matrix mat , Base * base );
			Vector3D ( string name , ex exp1 , ex exp2 , ex exp3 , Base * base );
			Vector3D ( string name , Matrix mat , Base * base , System * system );
			Vector3D ( string name , ex exp1 , ex exp2 , ex exp3 , Base * base , System * system );
			Vector3D ( string name , Matrix mat , string base_name , System * system );
			Vector3D ( string name , ex exp1 , ex exp2 , ex exp3 , string base_name , System * system );

			//Constructores sin nombre
            Vector3D ( void );
			Vector3D ( Base * base );
			Vector3D ( Matrix mat , Base * base );
			Vector3D ( ex exp1 , ex exp2 , ex exp3 , Base * base );
			Vector3D ( Matrix mat , Base * base , System * system );
			Vector3D ( ex exp1 , ex exp2 , ex exp3 , Base * base , System * system );
			Vector3D ( Matrix mat , string base_name , System * system );
			Vector3D ( ex exp1 , ex exp2 , ex exp3 , string base_name , System * system );

			//Access methods

			Base * get_Base ( void );
			System * get_System ( void );
            ex get_module ( void );
			void set_Base ( Base * new_base );
			void set_System ( System * new_system );
            string get_Name ( void );
            void  set_Name ( string s_name );
            Matrix skew (void);
            Vector3D change_Base (Base * new_base);
             
			//Methods

			//Vector3D Dt ( Frame * frame );
			//Vector3D Dt ( Base * base );
			Vector3D subs ( relational relation );
            
            

			//Operations

			friend Vector3D operator + ( const Vector3D & Vector3DA , const Vector3D & Vector3DB );
			friend Vector3D operator - ( const Vector3D & Vector3DA , const Vector3D & Vector3DB );
			friend Vector3D operator - ( const Vector3D & Vector3DA );
			friend ex operator * ( const Vector3D & Vector3DA , const Vector3D & Vector3DB );
			friend Vector3D operator * ( const Vector3D & Vector3DA , const ex & expression );
			friend Vector3D operator * ( const ex & expression , const Vector3D & Vector3DA );
			friend Vector3D operator ^ ( const Vector3D & Vector3DA , const Vector3D & Vector3DB );
			friend ostream& operator << ( ostream& os , const Vector3D & Vector3DA );

			//Destructor

			~Vector3D ();
	};

#endif // VECTOR3D_H

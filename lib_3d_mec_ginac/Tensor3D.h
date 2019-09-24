#ifndef TENSOR3D_H
#define TENSOR3D_H

#include "Matrix.h"
#include "Base.h"
#include "Vector3D.h"
class System;

using GiNaC::ex;
using GiNaC::relational;
using GiNaC::matrix;
using std::ostream;
using std::string;


    class Tensor3D : public Matrix{

        //Atributes

        Base * base;
        System * system;

    private:

        //Private methods

        void init ( string name , matrix mat , Base * base , System * system );
        static Tensor3D Operations ( const Tensor3D & Tensor3DA , const Tensor3D & Tensor3DB , const int flag );
        static Tensor3D Operations ( const Tensor3D & Tensor3DA , const ex & expression , int flag );

    public:

        //Constructors

        Tensor3D () ;
        Tensor3D ( Matrix , Base * );
        Tensor3D ( Matrix mat, Base * base, System * system);  
        Tensor3D ( string name , Matrix * mat , Base * base );
        Tensor3D ( string name , ex exp1 , ex exp2 , ex exp3 , ex exp4 , ex exp5 , ex exp6 , ex exp7 , ex exp8 , ex exp9 , Base * base );
        Tensor3D ( string name , Matrix mat , Base * base , System * system );
        Tensor3D ( string name , ex exp1 , ex exp2 , ex exp3 , ex exp4 , ex exp5 , ex exp6 , ex exp7 , ex exp8 , ex exp9 , Base * base , System * system );

        //Access methods

        Base * get_Base ( void );
        System * get_System ( void );
        void set_Base ( Base * new_base );
        void set_System ( System * new_system );
        void set_Name ( string new_name );

        //Public methods

        Tensor3D subs  ( relational relation );
        Tensor3D change_Base (Base * new_base);
        
        //Operations

        friend Tensor3D operator + ( const Tensor3D & Tensor3DA , const Tensor3D & Tensor3DB );
        friend Tensor3D operator - ( const Tensor3D & Tensor3DA , const Tensor3D & Tensor3DB );
        friend Tensor3D operator * ( const Tensor3D & Tensor3DA , const Tensor3D & Tensor3DB );
        friend Vector3D operator * ( const Tensor3D & Tensor3DA , Vector3D & Vector3DA );
        friend Tensor3D operator * ( const ex & expression , const Tensor3D & Tensor3DA );
        friend Tensor3D operator * ( const Tensor3D & Tensor3DA , const ex & expression );
        friend ostream & operator << ( ostream & os , const Tensor3D & Tensor3DA );

        //Destructor

        ~Tensor3D ( void );
    };

#endif // TENSOR3D_H

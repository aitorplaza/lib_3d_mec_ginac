#ifndef VectorE_H
#define VectorE_H

//#include "Vector3D.H"
#include "GL/gl.h"
//#include "symbol_numeric.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <list>


class System;

//~ using namespace std;
using std::ostream;
using std::string;

    //template <class T>  
    class VectorE{

        //Atributes
        string name;
        list <Vector3D> VectorsList; 

                

        private:
        void init ( string name );
        //vector <T> Velems;
        //Private methods
        //void init ( string name ,string type, Point * point , Base * base);


        public:
        //Constructors

        VectorE ( void );
        VectorE ( string name);
 

        //Access methods
        //void push(T const&);  // push element 
        string get_name ( void );
        void push (Vector3D vector);    
        friend ostream& operator << ( ostream& os , const VectorE & vector );
    

        //Destructor
        ~VectorE ( void );

    };




#endif // VectorE_H



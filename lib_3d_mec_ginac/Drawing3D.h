#ifndef Drawing3D_H
#define Drawing3D_H

#include "Base.h"
#include "Point.h"
#include "GL/gl.h"
#include "symbol_numeric.h"
#include "Solid.h"
class System;

using std::string;

    class Drawing3D{

        //Atributes
        string name;
        string type;
        Vector3D V;
        Point * P;
        Base * B;
        string file;
        numeric r;
        numeric g;
        numeric b;
        numeric alpha;
        numeric scale;
        lst color;
                //ex module;//EZABATU
                

        private:
        //Private methods
        void init ( string name ,string type, Point * point , Base * base);

        public:

        //Constructors

        Drawing3D ( void );
        Drawing3D ( string name, string type, Point * P , Base * B);
 

        //Access methods
          string get_name ( void );
        void set_file ( string new_file );
        void set_color ( lst new_color );
        void set_scale ( numeric new_scale );
        string get_file ( void );
        lst get_color ( void );
        string get_type ( void );
        Point * get_Point ( void );
        Base * get_Base ( void );
        numeric get_scale ( void );
        void set_vector ( Vector3D new_vector );
        Vector3D get_vector ( void );


        //Destructor

        ~Drawing3D ( void );
    };




#endif // Drawing3D_H



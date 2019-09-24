#include "System.h"
#include "Globals.h"
#include "Vector3D.h"
//#include "Vector3D.h"
//#include <vector>
#include "VectorE.h"

//using namespace std;
using std::ostream;
using std::string;
using std::exception;
// Definición:
//~ template <class T>
//~ VectorE<T>::VectorE( void ) {
   //~ vector<T> vT;
//~ }

void VectorE::init( string name ){
    this-> name = name;

}

/*
General VectorE constructor
*/
VectorE::VectorE (  ){
	init ( "" );
}

/*
Constructor with name 
*/
VectorE::VectorE ( string name ){
	init ( name);
}


//~ void Drawing3D::init ( string name, string type, Point * point , Base * base){
	//~ this-> name = name;
	//~ this-> type = type;
	//~ this-> P = point;
	//~ this-> B = base;
	//~ this-> file = "";
	//~ //this-> color = 0,0,0,1;
	//~ this-> color = 9 ,9 ,9 ,9 ;
	//~ this-> scale = 1;
//~ }

/*
General DRAWING3D constructor
*/
//~ Drawing3D::Drawing3D ( void ){
	//~ init ( "" ,"", NULL , NULL);
//~ 
//~ }

/*
DRAWING3 constructor
*/		
//~ Drawing3D::Drawing3D ( string name, string type, Point * P , Base * B){
        //~ init ( name, type, P , B);
//~ }

//~ /*
//~ Return the name
//~ */
string VectorE::get_name ( void ){	
	return name;   
}

void VectorE::push (Vector3D vector) {
    
    if (VectorsList.size()==0){
        VectorsList.push_back(vector);
        return;
    }
    
    list <Vector3D> AuxVectorsList; 
    bool added = false;
    Vector3D vaux;
    for (std::list<Vector3D>::iterator it = VectorsList.begin(); it != VectorsList.end(); it++){

      if (it->get_Base()== vector.get_Base()){
          vaux = *it + vector;
          AuxVectorsList.push_back(vaux);
          added = true;

      }else{
          vaux = *it;
          AuxVectorsList.push_back(vaux);
      }
    }
    
    if (!added)
        AuxVectorsList.push_back(vector);
    
    VectorsList = AuxVectorsList;
   
}


//~ template <class T>
//~ void VectorE<T>::push (T const& elem) 
//~ { 
    //~ // append copy of passed element 
    //~ Velems.push_back(elem);    
//~ }



/* 
Output of one Vectors3D
*/
ostream & operator << ( ostream & os , const VectorE & vector ){
	try{
		if ( vector.name == "ERROR" ) throw 1; 

        list <Vector3D> AuxVectorsList;AuxVectorsList = vector.VectorsList;
        os << vector.name << " [[\n" << endl;
        for (std::list<Vector3D>::iterator it = AuxVectorsList.begin(); it != AuxVectorsList.end(); it++){
            os <<unatomize(*it);
            os << "\n";
        }
		os << "]]\n"; 
		return os; 
	}catch ( exception & p ) {
		outError ( "ERR - Unexpected error in out of Vector3D" ); 
		return os; 
	}catch ( int e ){
		return os; 
	}
}






/*
Destructor
*/
//~ template <class T>
//~ VectorE<T>::~VectorE( void ) {
   //~ //delete
//~ }
VectorE::~VectorE ( void ) {};

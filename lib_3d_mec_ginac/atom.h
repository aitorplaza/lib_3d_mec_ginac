#ifndef ATOM_H
#define ATOM_H

#include "symbol_numeric.h"
class System;
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

#include <ginac/ginac.h>
using namespace GiNaC;

#if (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 3)
    // make sure this does not collide with others classes' TINFOs.
    static const unsigned TINFO_atom = 666666U;
    #define ATOM_RTTI TINFO_atom
#elif (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 4) 
    #define ATOM_RTTI (&atom::tinfo_static)
#endif

//symbol t("t");

    class atom : public  symbol_numeric {

        //Atributes

        mutable ex expression;
        numeric num_references;


        lst dep_atom_list;
        int num_index;

        int constant;

		//Private methods
			
        GINAC_DECLARE_REGISTERED_CLASS ( atom , symbol_numeric);
		

    protected:

        //Protected methods

        void do_print ( const print_context & c , unsigned level = 0 ) const;

    public:

        //Constructors
        atom ( const string & s );
        atom ( const string & s , ex dS );
        atom ( const string & s , numeric v);
        atom ( const string & s , ex dS , numeric v);

        //Public Methods		

        ex derivative ( const symbol & s ) const;
        ex get_expression ();
        void inc_num_references ();
        numeric get_num_references ();
        void dec_num_references ();       

        int get_index();
        void set_index( int index );


        int is_constant (); 
        //ex subs(const exmap & m, unsigned options) const;
        
        void add_atom_to_DepAtomList( int iatom );
        void set_DepAtomList( lst list );
        lst get_DepAtomList();
 
        //Destructor
        ~atom ();
	
    };	

#endif // ATOM_H

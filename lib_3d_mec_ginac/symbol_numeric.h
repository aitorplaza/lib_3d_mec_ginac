#ifndef SYMBOL_NUMERIC_H
#define SYMBOL_NUMERIC_H

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

#include <ginac/ginac.h>
using namespace GiNaC;

#if (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 3)
	// make sure this does not collide with others classes' TINFOs.
	static const unsigned TINFO_symbol_numeric = 666666U;
	#define SYMBOL_NUMERIC_RTTI TINFO_symbol_numeric
#elif (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 4)
	#define SYMBOL_NUMERIC_RTTI (&symbol_numeric::tinfo_static)
#endif

class symbol_numeric : public symbol {


	GINAC_DECLARE_REGISTERED_CLASS ( symbol_numeric , symbol );

	protected:

		//atributes

		mutable numeric value;

		//Protected methods

        void do_print ( const print_context & c , unsigned level = 0 ) const;
		void do_print_latex ( const print_context & c , unsigned level = 0) const;
	
    
    public:

		//Constructors

		//symbol_numeric ();
	    symbol_numeric ( string s );
        symbol_numeric ( string s , numeric value);
		symbol_numeric ( string s , string s_tex);
        symbol_numeric ( string s , string s_tex, numeric value);
		symbol_numeric ( symbol s );
		symbol_numeric ( symbol s , numeric value );

		string print_TeX_name( void );

		//Access methos

		void set_value ( numeric value );
		numeric get_value ( void );

		//Destructor

		~symbol_numeric ( void );

};	

#endif // SYMBOL_NUMERIC_H

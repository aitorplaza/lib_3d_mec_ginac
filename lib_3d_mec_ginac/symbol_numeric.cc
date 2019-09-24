#include "symbol_numeric.h"


GINAC_IMPLEMENT_REGISTERED_CLASS_OPT( symbol_numeric , symbol , print_func < print_context > ( & symbol_numeric::do_print ). print_func < print_latex > ( & symbol_numeric::do_print_latex ) )


//1.-
// ctors. Make sure all of them set tinfo_key.
symbol_numeric::symbol_numeric () {
#if (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 4)
	tinfo_key = SYMBOL_NUMERIC_RTTI;
#endif
	value = 0;
}

#if (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 4)
//2.-
//archive
void symbol_numeric::archive ( archive_node & n ) const {
        inherited::archive ( n );
}


//3.-
//the unarchiving constructor.
symbol_numeric::symbol_numeric ( const archive_node & n , lst & sym_lst ) : inherited ( n , sym_lst ) {
        tinfo_key = SYMBOL_NUMERIC_RTTI;
}


//4.-
//unarchive
ex symbol_numeric::unarchive ( const archive_node & n , lst & sym_lst ) {
        return ( new symbol_numeric ( n , sym_lst ) )-> setflag ( status_flags::dynallocated );
}
#endif

//5.-
// comparison
int symbol_numeric::compare_same_type ( const basic & other ) const {
        return inherited::compare_same_type ( other );
}

/*
Constructors
*/
symbol_numeric::symbol_numeric ( symbol s ) : inherited( s ) {
	this-> value = 0;
}

symbol_numeric::symbol_numeric ( symbol s , numeric value ) : inherited ( s ) {
	this-> value = value;
}

symbol_numeric::symbol_numeric ( string s ) : inherited( s ){
	this-> value = 0;
 }

symbol_numeric::symbol_numeric ( string s , numeric value) : inherited( s ){
	this-> value = value;
}


symbol_numeric::symbol_numeric ( string s , string s_tex) : inherited( s, s_tex ){
	this-> value = 0;
 }

symbol_numeric::symbol_numeric ( string s , string s_tex, numeric value) : inherited( s, s_tex ){
	this-> value = value;
}


string symbol_numeric::print_TeX_name( void ){
return this->TeX_name;
}

//7.-
// printing
void symbol_numeric::do_print ( const print_context & c , unsigned level) const {
        inherited::do_print ( c , level );
}

void symbol_numeric::do_print_latex ( const print_context & c , unsigned level) const {
	c.s << this -> TeX_name;
       // inherited::do_print ( c , level );
}

/*
Access methos
*/
void symbol_numeric::set_value ( numeric value ){
	this-> value = value;
}

numeric symbol_numeric::get_value ( void ) {
	return this-> value;
}

/*
Destructor
*/
symbol_numeric::~symbol_numeric ( void ) {}

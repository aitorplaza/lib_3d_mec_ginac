#include "atom.h"
#include "Globals.h"
#include "System.h"
GINAC_IMPLEMENT_REGISTERED_CLASS_OPT( atom , symbol_numeric , print_func < print_context > ( & atom::do_print ) )


//1.-
// ctors. Make sure all of them set tinfo_key.
atom::atom () {
#if (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 4)
	tinfo_key = ATOM_RTTI;
#endif
	expression = 0;
	value=0;
	num_references = 1;
    dep_atom_list;                // A list of the atoms of those who depends
    num_index = 0;
    constant = 0;                 // is the atom constant 
}

#if (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 4)
//2.-
//archive
void atom::archive ( archive_node & n ) const {
        inherited::archive ( n );
}


//3.-
//the unarchiving constructor.
atom::atom ( const archive_node & n , lst & sym_lst ) : inherited ( n , sym_lst ) {
#if (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 4)
	tinfo_key = ATOM_RTTI;
#endif
}


//4.-
//unarchive
ex atom::unarchive ( const archive_node & n , lst & sym_lst ) {
        return ( new atom ( n , sym_lst ) )-> setflag ( status_flags::dynallocated );
}
#endif

//5.-
// comparison
int atom::compare_same_type ( const basic & other ) const {
        return inherited::compare_same_type ( other );
}


//6.-
//Specific constructors of the derived class

atom::atom ( const string & s ) : inherited ( s ) {
#if (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 4)
	tinfo_key = ATOM_RTTI;
#endif
	expression = 0;
	value = 0;
	num_references = 0;
}


atom::atom ( const string & s, ex dS ) : inherited ( s ) { 
#if (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 4)
	tinfo_key = ATOM_RTTI;
#endif 
	expression = dS;
	value = 0;
	num_references = 0;
}

atom::atom ( const string & s , numeric v) : inherited ( s ) {
#if (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 4)
	tinfo_key = ATOM_RTTI;
#endif
	expression = 0;
	value = v;
	num_references = 0;
}


atom::atom ( const string & s, ex dS , numeric v ) : inherited ( s ) { 
#if (GINACLIB_MAJOR_VERSION == 1) && (GINACLIB_MINOR_VERSION <= 4)
	tinfo_key = ATOM_RTTI;
#endif 
	expression = dS;
	value = v;
	num_references = 0;
}


//7.-
// printing
void atom::do_print ( const print_context & c , unsigned level) const {
        inherited::do_print ( c , level );
}


//8.-
//Finally we add the desired functionality to atom, that gets implemented through
ex atom::derivative ( const symbol & s ) const {
//	cout << s << " " << * this << endl;
        if ( compare ( s ) ){
		return atomize_ex(expression.diff ( s ));
		}
        else {
                return 1;
	}
}

//two versions of an ongoing project about optimal reevaluation of expresions
//that should only reevaluate atoms if they where changed

//ex atom::subs(const exmap & m, unsigned options) const {
//	cout << "--------------------------  "  << m << "-------------- " << expression << endl;
//	return expression.subs(m,options);
//}


//ex atom::subs(const exmap & m, unsigned options) const {
//	if (this-> reevaluation == true){
//		value = ex_to < numeric > ( expression.subs(m,options) );
//		return value;
//	}
//	else
//		return value;
//	//return expression.subs(m,options);
//}

ex atom::get_expression () {
	return expression;
}

void atom::inc_num_references () {
	num_references = num_references + 1;
}

void atom::dec_num_references () {
	num_references = num_references - 1;
}

numeric atom::get_num_references (){
	return num_references;
}

// method to add an atom to "dep_atom_list"
void atom::add_atom_to_DepAtomList( int iatom ){
        dep_atom_list.append(iatom);

}

// method to return  "dep_atom_list"
lst atom::get_DepAtomList(){
        return dep_atom_list;
}

// method tosets the "dep_atom_list"
void atom:: set_DepAtomList( lst list ){
        dep_atom_list = list;
}


// this method returns the index number of the atom
int atom::get_index(){
        return num_index; 
};

// this method sets an index number to an atom
void atom::set_index(int index){
        num_index = index;
        
};

// method that returns 1 if the antom is constan and 0 if not
// No implemented
int atom::is_constant (){
        return constant;
}
/*
Destructor
*/

atom::~atom () { }



#ifndef GLOBALS_H
#define GLOBALS_H


#include "Matrix.h"
#include "atom.h"

class System;
 
using GiNaC::ex;
using GiNaC::lst;
using GiNaC::symbol;
using std::string;
using std::vector;

#define DOWN 0
#define UP 1
#define NO 0
#define YES 1

#define RMO 0
#define CMO 1

#define MAPLE_OFF 0
#define MAPLE_ON 1

#define LAGRANGE 0
#define VIRTUAL_POWER 1

extern int atomization;//0-> work without atomization; 1-> work with atomization
extern int gravity;//0-> work with down gravity; 1-> work with up gravity
extern void  (  * outError ) (const char *  );
void printError ( char * args );


/*
Atomize/Unatomize
*/

extern vector < atom >  atoms;
//extern vector < ex >  atom_expressions;
extern vector < symbol_numeric >  exclude_atoms;
//extern exhashmap < ex > atom_hashmap;

        
ex atomize_ex ( ex e );

ex unatomize_ex ( ex e );
void atom_expression_list ( lst & , lst & );
void OPT_atom_expression_list( lst & list , lst & expression_list, exhashmap < int > &hash_list );
ex OPT_unatomize_ex( ex expression, exhashmap < int > &hashmap );
ex atom_to_expression( ex atom_ex );

lst get_atoms_list_in_exp ( ex expression  , lst & );
lst get_atoms_list_in_exp( ex expression );
lst add_atom_lists( lst list1 , lst list2 ) ;
void matrix_list_optimize ( Matrix & Mat ,lst & atom_lst, lst & expression_list);


int atoms_in_exp ( ex expression, lst & list );

int recursive_list_simplify (int i, lst & list);

ex recursive_expression_substitution (ex expression, symbol_numeric symbol, float value);
ex recursive_substitution (ex expression, vector<symbol_numeric*> & SymbolVec, float value);

ex recursive_differentiation (ex expression, symbol_numeric symbol);


void exclude_atom ( symbol_numeric symbolA );
void exclude_Coordinates_atoms ( System * system );
void exclude_Velocities_atoms ( System * system );
void exclude_Accelerations_atoms ( System * system );
void exclude_Joint_Unknowns_atoms ( System * system );


int recursive_ops_counter (ex expression);
/*
This function unatomizes a Matrix
 */
template < class T >
T unatomize ( T m ){
    if  ( atomization == NO )
        return m;
    for  ( int i = 0 ; i < m.rows () ; i++ )
        for  ( int j = 0; j < m.cols () ; j++ )
            m ( i , j ) = unatomize_ex ( m ( i , j ) );
    return m;
}


/*
This function atomize a Matrix
*/
template < class T >
T atomize ( T m ){
    if  ( atomization == NO )
        return m;
    for  ( int i = 0; i < m.rows () ; i++ )
        for  ( int j = 0 ; j < m.cols () ; j++ )
            m ( i , j ) = atomize_ex ( m ( i ,j ) );
    return m;
}


/*
This function atom_list a Matrix No funciona bien!
*/
template < class T >
lst atom_list ( T m , lst & list ){
    lst new_atom_list , aux_new_atom_list;
    //~ exhashmap < ex > lst_atom_map(atoms.size());

    if  ( atomization == NO )
        return new_atom_list;
        
    for  ( int i = 0 ; i < m.rows () ; i++ ){
        for  ( int j = 0 ; j < m.cols () ; j++ ){
            //aux_new_atom_list = all_atoms_list_ex ( m ( i , j ) , list ); // changed by Xabi & Aitor 
            aux_new_atom_list = get_atoms_list_in_exp ( m ( i , j ) , new_atom_list);
            
            //exhashmap < ex > atom_map(atoms.size());
            //~ for  ( lst::const_iterator k = aux_new_atom_list.begin () ; k != aux_new_atom_list.end () ; ++k ){
                //~ if (lst_atom_map[*k] != 1){
			        //~ new_atom_list.append (  * k );
			        //~ lst_atom_map[*k] = 1;				
			    //~ }
            //~ }
            for  ( lst::const_iterator k = aux_new_atom_list.begin () ; k != aux_new_atom_list.end () ; ++k )
                new_atom_list.append (  * k );
                
                
                

            aux_new_atom_list.remove_all ();
        }
    }
    //~ lst_atom_map.clear();

    return new_atom_list;
}


/*
This function obtains the atom_list of a Matrix, without using a general list
*/
template < class T >
lst atom_list ( T m ){
    lst new_atom_list , aux_new_atom_list;
    exhashmap < ex > lst_atom_map(atoms.size());
    
    if  ( atomization == NO )
        return new_atom_list;
    

    for  ( int i = 0 ; i < m.rows () ; i++ ){
        for  ( int j = 0 ; j < m.cols () ; j++ ){
            aux_new_atom_list = get_atoms_list_in_exp ( m ( i , j ) );
            
            for  ( lst::const_iterator k = aux_new_atom_list.begin () ; k != aux_new_atom_list.end () ; ++k ){
                if (lst_atom_map[*k] != 1){
			        new_atom_list.append (  * k );
			        lst_atom_map[*k] = 1;
			    }
            }
        }
    }

    return new_atom_list;
}





#endif

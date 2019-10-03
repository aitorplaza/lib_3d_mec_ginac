#include "Globals.h"
#include "System.h"
#include "symbol_numeric.h"

#include <sstream>
 
#define OPTIMIZED_LIST 1 /*Optimizes the output atomos list*/ 
#define OLD_ATM 0/* 1-> use old atomization*/ 
#define OLD_DIFF 0 /*1-> use old differentation*/
#define OLD_SUBS 0 /*1-> use old substitution*/

using GiNaC::ex;
using GiNaC::symbol;
using GiNaC::lst;
using GiNaC::is_a;
using GiNaC::wild;
using GiNaC::mul;
using GiNaC::subs_options;
using std::string;
using std::vector;
using std::ostringstream;


/*
This function
*/
string itoa( const long int& x ) {
    ostringstream o ;
    if ( !( o << x ) ) return "ERROR" ;
    return o.str() ;
}


/*
This function push back in exclude_atoms vector, this atom
*/
void exclude_atom( symbol_numeric atom ){
    exclude_atoms.push_back ( atom );
}



//This function push back in exclude_atoms, all the coordinates

void exclude_Coordinates_atoms ( System * system ){
    vector < symbol_numeric * > coord = system-> get_Coordinates();
    for ( int i = 0  ; i < coord.size () ; i++ )
        exclude_atoms.push_back ( * coord[i] );
}


//This function push back in exclude_atoms vector, all the velocities
void exclude_Velocities_atoms ( System * system ){
    vector < symbol_numeric * > veloc = system->get_Velocities();
    for ( int i = 0 ; i< veloc.size() ; i++ )
        exclude_atoms.push_back ( * veloc[i] );
}


//This function push back in exclude_atoms vector, all the accelerations

void exclude_Accelerations_atoms( System * system ){
    vector < symbol_numeric * > accel = system-> get_Accelerations ();
    for ( int i = 0 ; i < accel.size () ; i++ )
        exclude_atoms.push_back ( * accel[i] );
}

//This function push back in exclude_atoms vector, this atom

void exclude_Joint_Unknowns_atoms( System * system ){
    vector < symbol_numeric * > unkno = system-> get_Joint_Unknowns();
    for ( int i = 0 ; i < unkno.size () ; i++ )
        exclude_atoms.push_back ( * unkno[i] );
}


// This function returns the number of atoms in an expression, without the depending atoms
int atoms_in_exp ( ex expression, lst & list ){
    atom aux;

    if (expression.nops() == 0 && is_a < atom > ( expression )){
        aux = ex_to<atom>(expression);
        list.append(aux);
        return 0;
    }
    else if (expression.nops() == 0 && is_a < atom > ( -expression )){
        aux = ex_to<atom>(-expression);
        list.append(aux);
        return 0;    
    }
    for (const_iterator i = expression.begin(); i !=expression.end(); ++i){
        ex aux1 = *i;
        atoms_in_exp ( aux1, list );
    }
    return 0;
}
/*
This function atomizes an expression
*/
#if OLD_ATM == 0
ex atomize_ex( ex expression ){
    if ( atomization == NO )
        return expression;
    //cout <<"atoms "<<atoms.size()<<endl;    
    if (( is_a < symbol > ( expression ) ) || (is_a < symbol > ( -expression ) ))
        return expression;
    if ( is_a < numeric > ( expression ) )
        return expression;
    if ((is_a < atom > ( expression ) ) || (is_a < atom > ( -expression ) ))
        return expression;
    if ((is_a < symbol_numeric > ( expression ) ) || (is_a < symbol_numeric > ( -expression ) ))
        return expression;

    ex new_exp;
    
    if ( atom_hashmap[expression] != 0 ){
        new_exp = atom_hashmap[expression];
        return new_exp;    
    }
    else if ( atom_hashmap[-expression] != 0 ){
        new_exp = -atom_hashmap[-expression];
        return new_exp;    
    } 
       
    if  ( atom_hashmap[expression] == 0 ){
        ex a_exp = expression;
        for (const_iterator i = expression.begin(); i != expression.end(); ++i){
            new_exp =  atomize_ex(*i);
            a_exp = a_exp.subs( *i == new_exp , subs_options::algebraic );
        }
        new_exp = a_exp;
    }
    
    if (( is_a < symbol > ( new_exp ) ) || (is_a < symbol > ( -new_exp ) ))
        return new_exp;
    if ( is_a < numeric > ( new_exp ) )
        return new_exp;
    if ((is_a < atom > ( new_exp ) ) || (is_a < atom > ( -new_exp ) ))
        return new_exp;
    if ((is_a < symbol_numeric > ( new_exp ) ) || (is_a < symbol_numeric > ( -new_exp ) ))
        return new_exp;
    
    if ( atom_hashmap[new_exp] != 0 ){
        new_exp = atom_hashmap[new_exp];
        return new_exp;    
    }
    else if ( atom_hashmap[-new_exp] != 0 ){
        new_exp = -atom_hashmap[-new_exp];
        return new_exp;    
    }
    
    //atoms evolution
    
    atom a;
    if ( new_exp != 0 ) {
        a = atom ( "atom" + itoa ( atoms.size() ) , new_exp ) ;
        lst aux_list;
        atoms_in_exp ( new_exp, aux_list );
        a.set_DepAtomList(aux_list);
        a.set_index(atoms.size ());
        atoms.push_back ( a ) ;
        atom_hashmap[new_exp] = a;
        return a;
    } 
}
#endif
/*
This function unatomizes an expression
*/
#if OLD_ATM == 0
ex unatomize_ex( ex expression ) {
    if ( atomization == NO )
        return expression;

    //RECURSIVE VERSION
        
    ex new_exp;
    if ( is_a < atom > ( expression ) == 1){
        atom a = ex_to<atom>(expression);
        ex a_exp = a.get_expression ();
        new_exp =  unatomize_ex(a_exp);
    } 
    else if ( is_a < atom > ( expression )  == 0){
        if (expression.nops() > 0){
            ex a_exp = expression;
            for (const_iterator i = expression.begin(); i != expression.end(); ++i){
                new_exp =  unatomize_ex(*i);
                a_exp = a_exp.subs( *i == new_exp , subs_options::algebraic );
            }
            new_exp = a_exp;
        }
        else{
            new_exp =  expression;
        }
    }
    return new_exp;
}
#endif

/*
ORIGINAL SENTENCE
This function produces the list of atoms a expression, return is atoms in expression not contained in initial lst list, lst list in output contains 
the initial atoms in list and the previous atoms.

AITOR'S AND XABI'S INTERPRETATION
This function produces the list of atoms of an expression, it returns the atoms in the expression not contained in initial lst list.
lst list in output contains the initial atoms in the list and the previous atoms.

*/
int recursive_list_simplify (ex atom_ex , lst & list, exhashmap < ex > &hashmap){
    atom atm = ex_to<atom>(atom_ex);
    lst aux_lst = atm.get_DepAtomList();
    if ( aux_lst.nops() != 0){
        for ( int j = 0 ; j < aux_lst.nops(); ++j ) {
            recursive_list_simplify ( aux_lst.op(j) , list, hashmap);
       } 
    }
    if (hashmap[atom_ex] != 1){
        list.append (atom_ex );
        hashmap[atom_ex] = 1;				
    }
    return 0;
}

/*
This function subtitutes a symbol with a value in an expression recursively
*/
ex recursive_expression_substitution (ex expression, symbol_numeric symbol, float value){
    ex new_exp;
    ex a_exp;
    
    #if OLD_SUBS == 1
    //OLD no recursive
    new_exp = unatomize_ex(expression);
    new_exp = new_exp.subs((symbol)==value);
    return atomize_ex(new_exp);
    #endif
    
    if ( is_a < atom > ( expression ) == 1){
        atom a = ex_to<atom>(expression);
        a_exp = a.get_expression ();
        new_exp = recursive_expression_substitution (a_exp,  symbol, value);
        if (a_exp == new_exp){
            new_exp = a ;	
        }
    }
    else if ( is_a < atom > ( expression )  == 0){
        if (expression.nops() > 0){
            a_exp = expression;
            for (const_iterator i = expression.begin(); i != expression.end(); ++i){
                new_exp =  recursive_expression_substitution (*i,  symbol, value);
                a_exp = a_exp.subs( *i == new_exp , subs_options::algebraic );
            }
            new_exp = a_exp;
        }
        else{
            new_exp =  expression.subs((symbol)==value, subs_options::algebraic );
        }
    }  
    if (expression != new_exp && new_exp != 0 && is_a < atom > ( new_exp )  == 0 && is_a < atom > ( - new_exp )  == 0){
        new_exp = atomize_ex (new_exp);
    }
    
    return new_exp;
}

/*
This function subtitutes a vector of symbols with a value in an expression recursively
*/
ex recursive_substitution (ex expression, vector <symbol_numeric*> & SymbolVec, float value){
    ex new_exp;
    symbol_numeric *sym_j;
    
    #if OLD_SUBS == 1
    //OLD no recursive
    new_exp = unatomize_ex(expression);
    for (int j=0; (j < SymbolVec.size()); ++j) {
        sym_j = SymbolVec[j];
        new_exp = new_exp.subs((*sym_j)==value, subs_options::algebraic );
    }
    return atomize_ex(new_exp);
    #endif

    if ( is_a < atom > ( expression ) == 1){
        atom a = ex_to<atom>(expression);
        ex a_exp = a.get_expression ();
        new_exp = recursive_substitution (a_exp, SymbolVec, value);
        if (a_exp == new_exp){
            new_exp = a ;	
        }
    }
    else if ( is_a < atom > ( expression )  == 0){
        if (expression.nops() > 0){
            ex a_exp = expression;
            for (const_iterator i = expression.begin(); i != expression.end(); ++i){
                new_exp =  recursive_substitution (*i,  SymbolVec, value);
                a_exp = a_exp.subs( *i == new_exp , subs_options::algebraic );
            }
            new_exp = a_exp;
        }
        else{
            new_exp = expression;
            //symbol_numeric *sym_j;
            for (int j=0; (j < SymbolVec.size()); ++j) {
                sym_j = SymbolVec[j];
                if ( is_a < numeric > ( new_exp ) == 0 )
                    new_exp = new_exp.subs((*sym_j)==value, subs_options::algebraic );
            }
        }
    }  
    
    if (expression != new_exp && new_exp != 0 && is_a < atom > ( new_exp )  == 0 && is_a < atom > ( - new_exp )  == 0){
        new_exp = atomize_ex (new_exp);
    }
    
    return new_exp;
}

ex recursive_differentiation (ex expression, symbol_numeric symbol){
    
    #if OLD_DIFF == 1
    // OLD no recursive
    expression = unatomize_ex ( expression );
    return atomize_ex( expression.diff ( symbol ) );
    #endif
   
    ex new_exp;

    if ( is_a < atom > ( expression ) == 1){
        atom a = ex_to<atom>(expression);
        ex a_exp = a.get_expression ();
        new_exp = recursive_differentiation(a_exp,  symbol);
        if (a_exp == new_exp){
            new_exp = a ;	
        }
    }
    else if ( is_a < atom > ( expression )  == 0){
        ex a_exp; ex aux_ex;
        if (expression.nops() > 0){

            if ( is_a<add>(expression) == 1){
                //~ a_exp = expression;
                a_exp = 0.0;
                for (const_iterator i = expression.begin(); i != expression.end(); ++i){
                    if ( is_a<numeric>(*i) == 1){
                        a_exp = a_exp + 0.0;
                    }
                    else{
                        new_exp =  recursive_differentiation(*i,  symbol);
                        a_exp = a_exp + new_exp;
                    }
                }    
            }
            else if ( is_a<mul>(expression) == 1){
                a_exp = 0.0;
                for (const_iterator i = expression.begin(); i != expression.end(); ++i){
                    if ( is_a<numeric>(*i) == 1){
                        a_exp = a_exp + 0.0; 
                    }
                    else{
                        new_exp =  recursive_differentiation(*i,  symbol);
                        a_exp =  a_exp + ( expression / (*i) ) * new_exp;
                    }
                    
                }
            }			
            //else if ( is_a<function>(expression) == 1){
            //    a_exp =  unatomize_ex(expression).diff(symbol);
            //}
            //else if ( is_a<power>(expression) == 1){
             //   a_exp =  unatomize_ex(expression).diff(symbol);
            //}
            else  {
                a_exp =  unatomize_ex(expression).diff(symbol);
            }
            //~ else if ( is_a<numeric>(expression) == 1){
                //~ a_exp =  0.0;
            //~ } 
         						
            new_exp = a_exp;

        }
        else{
            if ( is_a<numeric>(expression) == 1){
                a_exp =  0.0;
            }    
             else{   
                a_exp =  expression.diff(symbol);
            }
            new_exp = a_exp;
        }
    }
    
    if ( is_a<numeric>(new_exp) == 0 && is_a < atom > ( new_exp )  == 0 && is_a < atom > ( - new_exp )  == 0){
        new_exp = atomize_ex (new_exp);
    }

    return new_exp;
	
}

void get_atom_list( ex expression, lst & atom_list, exhashmap < int > &atom_table ) {
        
    if ( is_a < atom > ( expression ) == 1){
        atom atm = ex_to<atom>(expression);
        ex a_exp = atm.get_expression ();
        get_atom_list(a_exp, atom_list,atom_table );
        
        if (atom_table[atm] < 1){
            atom_list.append ( atm );
        }

        atom_table[atm] =  1;
        
    } 
    else if ( is_a < atom > ( expression )  == 0){
        if (expression.nops() > 0){
            ex a_exp = expression;
            for (const_iterator i = expression.begin(); i != expression.end(); ++i){
                get_atom_list(*i, atom_list,atom_table );
            }
        }
    }

}

void get_atom_list( ex expression, lst & atom_list) {
        
    if ( is_a < atom > ( expression ) == 1){
        atom atm = ex_to<atom>(expression);
        ex a_exp = atm.get_expression ();
        get_atom_list(a_exp, atom_list);
        

        atom_list.append ( atm );


        
    } 
    else if ( is_a < atom > ( expression )  == 0){
        if (expression.nops() > 0){
            ex a_exp = expression;
            for (const_iterator i = expression.begin(); i != expression.end(); ++i){
                get_atom_list(*i, atom_list );
            }
        }
    }

}

// This function returns the atoms in an expression and the depending atoms with a general list
lst get_atoms_list_in_exp( ex expression , lst & list ){

    if ( atomization == NO )
        return list;

    exhashmap < ex > hashmap_atoms_ex(2*atoms.size());

    lst aux_list ,aux_atom_list, new_atom_list;


    lst aux_atom_ex_list;
    atoms_in_exp ( expression, aux_atom_ex_list );

    for ( int i = 0 ; i < aux_atom_ex_list.nops(); i++ ){
        int aux_int = atoms[ex_to<numeric>(aux_atom_ex_list.op(i)).to_int()].get_index();
        recursive_list_simplify(aux_int,aux_list,hashmap_atoms_ex) ;
    }

    for ( int j = 0 ; j < aux_list.nops(); ++j ) 
        aux_atom_list.append(atoms[ex_to<numeric>(aux_list.op(j)).to_int()]);
        
    for ( lst::const_iterator i = aux_atom_list.begin () ; i != aux_atom_list.end () ; ++i ) 
        if ( list.has( * i ) == 0 ){
            list.append ( * i );
            new_atom_list.append ( * i );
        }

    return new_atom_list;
}
// This function returns the atoms in an expression and the depending atoms without a general list
lst get_atoms_list_in_exp( ex expression ){

    lst aux_list ,aux_atom_ex_list;

    if ( atomization == NO )
        return aux_list;

    exhashmap < ex > hashmap_atoms_ex(2*atoms.size());
    
    atoms_in_exp ( expression, aux_atom_ex_list );

    for ( int i = 0 ; i < aux_atom_ex_list.nops(); i++ ){
        recursive_list_simplify(aux_atom_ex_list.op(i), aux_list, hashmap_atoms_ex);    
    }
    
    return aux_list;    
}




/*
This function return the expression of an atom.
*/
ex atom_to_expression( ex atom_ex ) {

    if ( atomization == NO )
        return atom_ex;
        
    atom a = ex_to<atom>(atom_ex);
    ex expression = a.get_expression();

    return expression;
}
/*
This function produces the list of expressions corresponding to the provided list of atoms.
*/
void atom_expression_list( lst & list , lst & expression_list ) {
    if ( atomization == NO )
        return;
        
    for ( int i = 0 ; i < list.nops () ; ++i ) {
        atom a = ex_to<atom>(list.op ( i ));
        expression_list.append(a.get_expression());
    }

    return;
}

//~ /*
//~ This function produces the list of expressions, removes the single atoms  and replaces them in the correspondig expression
//~ 
//~ OLD
//~ */
//~ void OPT_atom_expression_list( lst & list , lst & expression_list, exhashmap < int > &hash_list ) {
    //~ if ( atomization == NO )
        //~ return;
    //~ //exhashmap < int > ref_list(2*list.nops());
        //~ 
    //~ expression_list.remove_all ();
//~ 
    //~ for ( int i = 0 ; i < list.nops () ; ++i ) {
        //~ lst aux_lst;
        //~ atom a = ex_to<atom>(list.op ( i ));
        //~ //hash_list[a] = 0;
        //~ atoms_in_exp(a.get_expression(),aux_lst);
        //~ 
        //~ for ( int j = 0 ; j < aux_lst.nops () ; ++j ) {
            //~ atom atm = ex_to<atom>(aux_lst.op ( j ));
            //~ hash_list[atm] = hash_list[atm] + 1;
        //~ }
    //~ }
    //~ 
    //~ lst aux_lst_atm;
    //~ lst aux_lst_exp;
    //~ for ( int i = 0 ; i < list.nops () ; ++i ) {
//~ 
        //~ atom atm = ex_to<atom>(list.op ( i ));
        //~ if (hash_list[atm] > 1){
            //~ aux_lst_atm.append(atm);
            //~ ex atm_exp = atm.get_expression();
            //~ aux_lst_exp.append( OPT_unatomize_ex( atm_exp,hash_list));
        //~ }
    //~ }
//~ 
    //~ 
    //~ list = aux_lst_atm;  //simplified atoms list
    //~ expression_list = aux_lst_exp; //correspondig expressons list
    //~ //hash_list = ref_list;
    //~ return;
//~ }


void OPT_atom_expression_list( lst & list , lst & expression_list, exhashmap < int > &hash_list ) {
    if ( atomization == NO )
        return;
    //exhashmap < int > ref_list(2*list.nops());
        
    expression_list.remove_all ();

   
    lst aux_lst_atm;
    lst aux_lst_exp;
    for ( int i = 0 ; i < list.nops () ; ++i ) {

        atom atm = ex_to<atom>(list.op ( i ));
        if (hash_list[atm] > 1){
            aux_lst_atm.append(atm);
            ex atm_exp = atm.get_expression();
            aux_lst_exp.append( OPT_unatomize_ex( atm_exp,hash_list));
        }
    }

    
    list = aux_lst_atm;  //simplified atoms list
    expression_list = aux_lst_exp; //correspondig expressons list

    return;
}


/*
This function unatomizes an expression keeping the repeated according to a hash table.
*/
ex OPT_unatomize_ex( ex expression, exhashmap < int > &hashmap ) {
    if ( atomization == NO )
        return expression;
      
    ex new_exp;
    if ( is_a < atom > ( expression ) == 1){
        atom a = ex_to<atom>(expression);
        if (hashmap[a] == 1 || hashmap[a] == 0 ){
            ex a_exp = a.get_expression ();
            new_exp =  OPT_unatomize_ex(a_exp, hashmap);
        }
        else{
            new_exp = a;
        }
    } 
    else if ( is_a < atom > ( expression )  == 0){
        if (expression.nops() > 0){
            ex a_exp = expression;
            for (const_iterator i = expression.begin(); i != expression.end(); ++i){
                new_exp =  OPT_unatomize_ex(*i, hashmap);
                a_exp = a_exp.subs( *i == new_exp , subs_options::algebraic );
            }
            new_exp = a_exp;
        }
        else{
            new_exp =  expression;
        }
    }
    return new_exp;
}


/*
This function add 2 atoms lists and removes the repited atoms.
*/
lst add_atom_lists( lst list1 , lst list2 ) {
    lst result_lst;
    exhashmap < ex > hash_list(2*list1.nops() + 2*list2.nops());
    for ( int i = 0 ; i < list1.nops () ; ++i ) {
        result_lst.append(list1.op ( i ));
        hash_list[list1.op ( i )] = 1;
    }
    for ( int j = 0 ; j < list2.nops () ; ++j ) {
        
        if (hash_list[list2.op ( j )] == 0){
            result_lst.append(list2.op ( j ));
            hash_list[list2.op ( j )] = 1;
        }
    }    
    return result_lst;
}

void matrix_list_optimize ( Matrix & Mat , lst & atom_lst, lst & expression_list){

    //lst aux_lst;
    exhashmap < int > repeated_atom_list(2*atoms.size());


    atom_lst = atom_list ( Mat );
    
    //cout << "  NO OPT = > "<<Mat.get_name() << " list size = "<< atom_lst.nops () << endl;  
     #if OPTIMIZED_LIST == 0 
    atom_lst = atom_list ( Mat );
    atom_expression_list ( atom_lst , expression_list );
    #else

    lst single_atm_lst, exp_atm_lst;
    
    for ( int i = 0 ; i < atom_lst.nops () ; ++i ) {
        atom atm = ex_to<atom>(atom_lst.op ( i ));
        ex a_exp = atm.get_expression ();
        lst aux_lst;
        atoms_in_exp(a_exp, aux_lst);
        for ( int k = 0 ; k < aux_lst.nops () ; k++ ) {
            exp_atm_lst.append(aux_lst.op ( k ));
            atom atm = ex_to<atom>(aux_lst.op ( k ));
            repeated_atom_list[atm] +=  1;
        }
    }
           
    for ( int j = 0 ; j < Mat.cols () ; j++ ){
        for ( int i = 0 ; i < Mat.rows () ; i++ ){
            lst aux_atom_ex_list;
            atoms_in_exp ( Mat ( i , j ), aux_atom_ex_list );
            for ( int k = 0 ; k < aux_atom_ex_list.nops () ; k++ ) {
                exp_atm_lst.append(aux_atom_ex_list.op ( k ));
                atom atm = ex_to<atom>(aux_atom_ex_list.op ( k ));
                repeated_atom_list[atm] +=  1; 
            }
        }
    }
        
    lst zero_lst;
    single_atm_lst = add_atom_lists(zero_lst,exp_atm_lst); //quitar repetidos


    //OPT_atom_expression_list ( single_atm_lst, expression_list, repeated_atom_list );
    expression_list.remove_all ();

   
    lst aux_lst_atm;
    lst aux_lst_exp;
    for ( int i = 0 ; i < single_atm_lst.nops () ; ++i ) {

        atom atm = ex_to<atom>(single_atm_lst.op ( i ));
        if (repeated_atom_list[atm] > 1){
            aux_lst_atm.append(atm);
            ex atm_exp = atm.get_expression();
            aux_lst_exp.append( OPT_unatomize_ex( atm_exp,repeated_atom_list));
        }
    }

    atom_lst = aux_lst_atm;  //simplified atoms list
    expression_list = aux_lst_exp; //correspondig expressons list

    for ( int j = 0 ; j < Mat.cols () ; j++ ){
        for ( int i = 0 ; i < Mat.rows () ; i++ ){
        Mat ( i , j ) = OPT_unatomize_ex( Mat( i , j ), repeated_atom_list);
        }
    }
    
    #endif

    //cout << "  OPT = > "<<Mat.get_name() << " list size = "<< atom_lst.nops () << endl;


}


//~     OLD
 //~ void matrix_list_optimize ( Matrix & Mat , lst & atom_lst, lst & expression_list){
//~ 
    //~ #if OPTIMIZED_LIST == 1
        //~ //atom_lst = atom_list ( Mat );
        //~ atom_lst = atom_list ( Mat ); // mejor
        //~ 
        //~ int  counter = 0;
        //~ lst aux_exp_list;
        //~ atom_expression_list ( atom_lst , aux_exp_list );
        //~ 
        //~ for ( int j = 0 ; j < aux_exp_list.nops () ; ++j ) {
        //~ counter = counter + recursive_ops_counter (aux_exp_list.op ( j ));
        //~ }
        //~ for ( int j = 0 ; j < Mat.cols () ; j++ ){
            //~ for ( int i = 0 ; i < Mat.rows () ; i++ ){
                //~ counter = counter + recursive_ops_counter (Mat ( i , j ) );
            //~ }
        //~ }
        
        //~ cout << "  "<< Mat.get_name() << " list size = "<< atom_lst.nops()  << endl;
//~ 
        //~ exhashmap < int > repeated_atom_list(2*atom_lst.nops());
        //~ //OPT_atom_expression_list ( atom_lst , expression_list, repeated_atom_list ); 
//~ 
        //~ lst aux_list;
        //~ for ( int j = 0 ; j < Mat.cols () ; j++ ){
            //~ for ( int i = 0 ; i < Mat.rows () ; i++ ){
                //~ lst aux_atom_ex_list;
                //~ atoms_in_exp ( Mat ( i , j ), aux_atom_ex_list );
                //~ for ( int k = 0 ; k < aux_atom_ex_list.nops () ; k++ ) {
                    //~ aux_list.append(aux_atom_ex_list.op ( k )); 
                //~ }
            //~ }
        //~ }        
        //~ for ( int i = 0 ; i < aux_list.nops () ; ++i ) {
            //~ atom atm = ex_to<atom>(aux_list.op ( i ));
            //~ repeated_atom_list[atm] = repeated_atom_list[atm] + 1;
        //~ }
        //~ 
        //~ atom_lst = add_atom_lists(atom_lst,aux_list);
        //~ lst aux_lst = atom_lst; //Para contar operaciones
        //~ 
        //~ 
        //~ OPT_atom_expression_list ( atom_lst , expression_list, repeated_atom_list );
      //~ 
        //~ for ( int j = 0 ; j < Mat.cols () ; j++ ){
            //~ for ( int i = 0 ; i < Mat.rows () ; i++ ){
                //~ Mat ( i , j ) = OPT_unatomize_ex( Mat( i , j ), repeated_atom_list);
            //~ }
        //~ }
    //~ #else
        //~ atom_lst = atom_list ( Mat );
        //~ atom_expression_list ( atom_lst , expression_list );
    //~ #endif
//~ 
//~ 
//~ 
//~ counter = 0;
//~ for ( int j = 0 ; j < expression_list.nops () ; ++j ) {
//~ counter = counter + recursive_ops_counter (expression_list.op ( j ));
//~ }
//~ for ( int j = 0 ; j < Mat.cols () ; j++ ){
    //~ for ( int i = 0 ; i < Mat.rows () ; i++ ){
        //~ counter = counter + recursive_ops_counter (Mat ( i , j ) );
    //~ }
//~ }
//~ cout << "  OPT = > "<<Mat.get_name() << " list size = "<< atom_lst.nops () << endl;
//~ 
//~ 
//~ 
//~ }
    
#if OLD_ATM == 1
// ========== OLD FUNCTION FOR PROBES
/*
This function atomize an expression
*/
ex atomize_ex( ex expression ){

    
    if ( atomization == NO )
        return expression;
    //cout <<"atoms "<<atoms.size()<<endl; 
    if (( is_a < symbol > ( expression ) ) || (is_a < symbol > ( -expression ) ))
        return expression;
    if ( is_a < numeric > ( expression ) )
        return expression;
    if ((is_a < atom > ( expression ) ) || (is_a < atom > ( -expression ) ))
        return expression;
    if ((is_a < symbol_numeric > ( expression ) ) || (is_a < symbol_numeric > ( -expression ) ))
        return expression;

    //The expresion is unatomized
    //expression = unatomize_ex( expression );

    //if ( is_a < symbol > ( expression ) )
    //  return expression;
    //if ( is_a < numeric > ( expression ) )
    //  return expression;

    //Now the expression is atomized another time
    //
    
    for ( int i = 0 ; i < atoms.size() ; i++ ){
        expression = expression.subs ( atoms[i].get_expression() + wild( 1 ) == atoms[i] + wild( 1 ) , subs_options::algebraic );
        expression = expression.subs ( atoms[i].get_expression() == atoms[i] ,subs_options::algebraic );
        expression = expression.subs ( -atoms[i].get_expression() + wild( 1 ) == -atoms[i] + wild( 1 ) , subs_options::algebraic );
        expression = expression.subs ( -atoms[i].get_expression() == -atoms[i] , subs_options::algebraic );
        }
    if (( is_a < symbol > ( expression ) ) || (is_a < symbol > ( -expression ) ))
        return expression;
    if ( is_a < numeric > ( expression ) )
        return expression;
    if ((is_a < atom > ( expression ) ) || (is_a < atom > ( -expression ) ))
        return expression;
    if ((is_a < symbol_numeric > ( expression ) ) || (is_a < symbol_numeric > ( -expression ) ))
        return expression;

    atom a ;
    if ( expression != 0 ) {
        
        a = atom ( "atom" + itoa ( atoms.size() ) , expression ) ;
        lst aux_list;
        atoms_in_exp ( expression, aux_list );
        a.set_DepAtomList(aux_list);
        a.set_index(atoms.size ());
        atoms.push_back ( a ) ;
        return a;
    } 
}

/*
This function unatomize an expression
*/
ex unatomize_ex( ex expression ) {
    if ( atomization == NO )
        return expression;
    for ( int i = atoms.size () - 1 ; i >= 0 ; i-- )
            expression = expression.subs( atoms[i] == atoms[i].get_expression() , subs_options::algebraic );
    return expression;
}
#endif






/*
 * Function that counts the number of operations in an expression
*/
int recursive_ops_counter (ex expression){
    int counter;
    counter = expression.nops();
    if ( is_a<add>(expression) == 1){counter = counter-1; }
    if ( is_a<mul>(expression) == 1){counter = counter-1; }
    if ( is_a<power>(expression) == 1){counter = counter-1; return counter;}
    //~ if ( expression.nops() == 0){ return counter;}
    //if ( is<negative>(expression) == 1){cout << "negative"<< expression<<endl;;}
    for (const_iterator i = expression.begin(); i != expression.end(); ++i){
        counter =  counter + recursive_ops_counter(*i);
    }    
    return counter;
}

ex unatomize ( ex m ){
    if  ( atomization == NO )
        return m;
     m = unatomize_ex ( m  );
    return m;
}

Matrix unatomize ( Matrix m ){
    if  ( atomization == NO )
        return m;
    for  ( int i = 0 ; i < m.rows () ; i++ )
        for  ( int j = 0; j < m.cols () ; j++ )
            m ( i , j ) = unatomize_ex ( m ( i , j ) );
    return m;
}

Vector3D unatomize ( Vector3D m ){
    if  ( atomization == NO )
        return m;
    for  ( int i = 0 ; i < m.rows () ; i++ )
        for  ( int j = 0; j < m.cols () ; j++ )
            m ( i , j ) = unatomize_ex ( m ( i , j ) );
    return m;
}

Tensor3D unatomize ( Tensor3D m ){
    if  ( atomization == NO )
        return m;
    for  ( int i = 0 ; i < m.rows () ; i++ )
        for  ( int j = 0; j < m.cols () ; j++ )
            m ( i , j ) = unatomize_ex ( m ( i , j ) );
    return m;
}

Wrench3D unatomize ( Wrench3D m ){
    if  ( atomization == NO )
        return m;
    
    return m.unatomize();
}

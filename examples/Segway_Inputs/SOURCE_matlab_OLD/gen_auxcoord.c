#include <stdlib.h>
#include "gen_auxcoord.h"


double * qaux=NULL; 

void Init_qaux_values ( void )
{
}

void Init_qaux ( )
{
 qaux = malloc ( n_gen_auxcoord * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_auxcoord ; i++ ) {qaux[i]=0.0;}
 }
}

void Done_qaux( ) 
{
if ( qaux != NULL) 
free ( qaux ); 
qaux = NULL; 
}

void Reallocate_qaux( double * user_qaux ) 
{
qaux = user_qaux; 
}


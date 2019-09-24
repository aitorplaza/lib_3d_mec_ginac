#include <stdlib.h>
#include "gen_auxaccel.h"


double * ddqaux=NULL; 

void Init_ddqaux_values ( void )
{
}

void Init_ddqaux ( )
{
 ddqaux = malloc ( n_gen_auxaccel * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_auxaccel ; i++ ) {ddqaux[i]=0.0;}
 }
}

void Done_ddqaux( ) 
{
if ( ddqaux != NULL) 
free ( ddqaux ); 
ddqaux = NULL; 
}

void Reallocate_ddqaux( double * user_ddqaux ) 
{
ddqaux = user_ddqaux; 
}


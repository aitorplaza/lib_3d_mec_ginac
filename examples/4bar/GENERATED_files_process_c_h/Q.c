/*----------Q.c lib3D_MEC exported-----------*/

/* CMO exported */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "time_3D_mec.h"
#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
#include "param.h"
#include "unknowns.h"
#include "inputs.h"

#include "step.h"

#include "Q.h"

#define theta1 q[ 0 ]
#define theta2 q[ 1 ]
#define theta3 q[ 2 ]
#define dtheta1 dq[ 0 ]
#define dtheta2 dq[ 1 ]
#define dtheta3 dq[ 2 ]
#define ddtheta1 ddq[ 0 ]
#define ddtheta2 ddq[ 1 ]
#define ddtheta3 ddq[ 2 ]
#define g param[ 0 ]
#define l1 param[ 1 ]
#define l2 param[ 2 ]
#define l3 param[ 3 ]
#define l4 param[ 4 ]
#define m1 param[ 5 ]
#define m2 param[ 6 ]
#define m3 param[ 7 ]
#define cg1x param[ 8 ]
#define cg1z param[ 9 ]
#define cg2x param[ 10 ]
#define cg2z param[ 11 ]
#define cg3x param[ 12 ]
#define cg3z param[ 13 ]
#define I1yy param[ 14 ]
#define I2yy param[ 15 ]
#define I3yy param[ 16 ]
#define K param[ 17 ]
#define l2x param[ 18 ]
#define l2z param[ 19 ]
#define l3x param[ 20 ]
#define l3z param[ 21 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define Fx2 inputs[ 0 ]
#define Fz2 inputs[ 1 ]
#define Fx3 inputs[ 2 ]
#define Fz3 inputs[ 3 ]
#define My2 inputs[ 4 ]
#define My3 inputs[ 5 ]

double atom15;
double atom14;
double atom78;
double atom26;
double atom25;
double atom27;
double atom24;
double atom68;
double atom71;
double atom69;
double atom70;
double atom30;
double atom33;
double atom36;
double atom274;
double atom0;
double atom284;
double atom42;
double atom339;
double atom1;
double atom340;
double atom43;
double atom101;
double atom100;
double atom106;
double atom124;
double atom103;
double atom102;
double atom118;
double atom126;
double atom104;
double atom107;
double atom120;
double atom327;
double atom109;
double atom122;
double atom115;
double atom128;
double atom110;
double atom119;
double atom330;
double atom240;
double atom241;
double atom353;
double atom279;
double atom46;
double atom49;
double atom52;
double atom351;
double atom40;
double atom57;
double atom56;
double atom11;
double atom10;
double atom401;
double atom398;

double * _Q = NULL;
void Init_Q ( ) 
{
    _Q = malloc ( Q_n_rows * Q_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Q_n_rows * Q_n_cols ; i++ ) {_Q[i]=0.0;}
  }
}

void Done_Q ( ) 
{
if (_Q != NULL) 
free (_Q ); 
_Q = NULL; 
}


double * Q ()
{
if ( _Q == NULL )
 {
    _Q = malloc ( Q_n_rows * Q_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Q_n_rows * Q_n_cols ; i++ ) {_Q[i]=0.0;}
  }
 }

atom15 = sin(theta1);
atom14 = cos(theta1);
atom78 =  dtheta2+dtheta1;
atom26 = cos(theta2);
atom25 = m2*cg2z;
atom27 = sin(theta2);
atom24 = m2*cg2x;
atom68 = atom14*l1;
atom71 = dtheta1*atom68;
atom69 = -l1*atom15;
atom70 = dtheta1*atom69;
atom30 = -atom15*atom27+atom14*atom26;
atom33 =  atom14*atom27+atom26*atom15;
atom36 =  atom25*atom33+atom24*atom30;
atom274 = -( atom25*atom30-atom33*atom24)*dtheta1*atom71+dtheta1*atom36*atom70;
atom0 = cos(theta3);
atom284 =  atom78+dtheta3;
atom42 = cg3x*m3;
atom339 = -atom0*(atom284*atom284);
atom1 = sin(theta3);
atom340 = -(atom284*atom284)*atom1;
atom43 = cg3z*m3;
atom101 = -l2*atom27;
atom100 = l2*atom26;
atom106 = atom101*atom15;
atom124 = -atom14*atom100-atom106;
atom103 = dtheta2*atom100;
atom102 = dtheta2*atom101;
atom118 = -atom14*atom103-atom102*atom15;
atom126 =  dtheta1*atom124+atom118;
atom104 =  l1+atom100;
atom107 =  atom104*atom14+atom106;
atom120 = -atom107*dtheta1+atom118;
atom327 =  dtheta2*atom126*m3+atom120*dtheta1*m3;
atom109 = atom101*atom14;
atom122 = -atom100*atom15+atom109;
atom115 = -atom15*atom103+atom102*atom14;
atom128 = -atom115-atom122*dtheta1;
atom110 = -atom104*atom15+atom109;
atom119 =  atom110*dtheta1+atom115;
atom330 =  dtheta2*m3*atom128-dtheta1*atom119*m3;
atom240 = l1*atom27;
atom241 = -atom26*l1;
atom353 =  atom33*atom327-atom42*atom340+atom339*atom43+atom330*atom30;
atom279 =  l2-atom241;
atom46 = -atom33*atom1+atom0*atom30;
atom49 =  atom0*atom33+atom1*atom30;
atom52 =  atom49*atom43+atom42*atom46;
atom351 = -( dtheta2*atom128-dtheta1*atom119)*atom52-( atom42*atom49-atom46*atom43)*( dtheta2*atom126+atom120*dtheta1);
atom40 = atom36*g;
atom57 = -m3*g;
atom56 = atom52*g;
atom11 = -K*( l3x*atom1-atom0*l3z);
atom10 = K*( l2+atom1*l3z-l2x+atom0*l3x);
atom401 = -atom10*atom1-atom11*atom0;
atom398 =  atom11*atom1-atom0*atom10;

_Q[0] = -Fx3*atom110+Fz2*atom68-atom56-m2*g*atom68-My3-( atom33*atom330-atom42*atom339-atom30*atom327-atom340*atom43)*atom240-atom10*atom240-atom69*Fx2+atom401*( l3x+atom0*atom279-atom1*atom240)-( atom1*atom279+l3z+atom0*atom240)*atom398+atom351+( (atom78*atom78)*atom25*atom26+dtheta1*m2*atom15*atom71-(atom78*atom78)*atom24*atom27+dtheta1*m2*atom70*atom14)*l1-( m1*cg1z*atom15+m1*atom14*cg1x)*g-atom11*( atom241-l2x)+atom274+atom107*Fz3-My2-atom40-atom353*atom279+atom107*atom57;
_Q[1] =  atom11*l2x-atom56-My3-Fx3*atom122-Fz3*atom124-l2*atom353-( l2*atom1+l3z)*atom398-atom57*atom124+atom351+atom401*( l3x+l2*atom0)+atom274-My2-atom40;
_Q[2] = -atom56-My3+atom401*l3x+atom351-atom398*l3z;

return _Q;
}

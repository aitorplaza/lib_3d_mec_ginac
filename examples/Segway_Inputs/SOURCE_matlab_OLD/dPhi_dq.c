/*----------dPhi_dq.c lib3D_MEC exported-----------*/

/* CMO exported */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "time.h"
#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
#include "gen_auxcoord.h"
#include "gen_auxvel.h"
#include "gen_auxaccel.h"
#include "param.h"
#include "unknowns.h"
#include "inputs.h"

#include "step.h"

#include "dPhi_dq.h"

#define rho1 q[ 0 ]
#define phi1 q[ 1 ]
#define phi2 q[ 2 ]
#define phi3 q[ 3 ]
#define theta1 q[ 4 ]
#define xp q[ 5 ]
#define yp q[ 6 ]
#define zp q[ 7 ]
#define ycdg q[ 8 ]
#define drho1 dq[ 0 ]
#define dphi1 dq[ 1 ]
#define dphi2 dq[ 2 ]
#define dphi3 dq[ 3 ]
#define dtheta1 dq[ 4 ]
#define dxp dq[ 5 ]
#define dyp dq[ 6 ]
#define dzp dq[ 7 ]
#define dycdg dq[ 8 ]
#define ddrho1 ddq[ 0 ]
#define ddphi1 ddq[ 1 ]
#define ddphi2 ddq[ 2 ]
#define ddphi3 ddq[ 3 ]
#define ddtheta1 ddq[ 4 ]
#define ddxp ddq[ 5 ]
#define ddyp ddq[ 6 ]
#define ddzp ddq[ 7 ]
#define ddycdg ddq[ 8 ]
#define g param[ 0 ]
#define pi param[ 1 ]
#define zcdg param[ 2 ]
#define R param[ 3 ]
#define man param[ 4 ]
#define r param[ 5 ]
#define l1 param[ 6 ]
#define l2 param[ 7 ]
#define l3 param[ 8 ]
#define d param[ 9 ]
#define le param[ 10 ]
#define cm param[ 11 ]
#define rm param[ 12 ]
#define hcdg param[ 13 ]
#define alpha param[ 14 ]
#define beta param[ 15 ]
#define Cvis1 param[ 16 ]
#define Cvis2 param[ 17 ]
#define Cvis3 param[ 18 ]
#define mPlataforma param[ 19 ]
#define mxPlataforma param[ 20 ]
#define myPlataforma param[ 21 ]
#define mzPlataforma param[ 22 ]
#define IxxPlataforma param[ 23 ]
#define IxyPlataforma param[ 24 ]
#define IyyPlataforma param[ 25 ]
#define IxzPlataforma param[ 26 ]
#define IzzPlataforma param[ 27 ]
#define IyzPlataforma param[ 28 ]
#define mRuedaIzq param[ 29 ]
#define mxRuedaIzq param[ 30 ]
#define myRuedaIzq param[ 31 ]
#define mzRuedaIzq param[ 32 ]
#define IxxRuedaIzq param[ 33 ]
#define IxyRuedaIzq param[ 34 ]
#define IyyRuedaIzq param[ 35 ]
#define IxzRuedaIzq param[ 36 ]
#define IzzRuedaIzq param[ 37 ]
#define IyzRuedaIzq param[ 38 ]
#define mRuedaDcha param[ 39 ]
#define mxRuedaDcha param[ 40 ]
#define myRuedaDcha param[ 41 ]
#define mzRuedaDcha param[ 42 ]
#define IxxRuedaDcha param[ 43 ]
#define IxyRuedaDcha param[ 44 ]
#define IyyRuedaDcha param[ 45 ]
#define IxzRuedaDcha param[ 46 ]
#define IzzRuedaDcha param[ 47 ]
#define IyzRuedaDcha param[ 48 ]
#define mEje param[ 49 ]
#define mxEje param[ 50 ]
#define myEje param[ 51 ]
#define mzEje param[ 52 ]
#define IxxEje param[ 53 ]
#define IxyEje param[ 54 ]
#define IyyEje param[ 55 ]
#define IxzEje param[ 56 ]
#define IzzEje param[ 57 ]
#define IyzEje param[ 58 ]
#define mManillar param[ 59 ]
#define mxManillar param[ 60 ]
#define myManillar param[ 61 ]
#define mzManillar param[ 62 ]
#define IxxManillar param[ 63 ]
#define IxyManillar param[ 64 ]
#define IyyManillar param[ 65 ]
#define IxzManillar param[ 66 ]
#define IzzManillar param[ 67 ]
#define IyzManillar param[ 68 ]
#define mRider param[ 69 ]
#define mxRider param[ 70 ]
#define myRider param[ 71 ]
#define mzRider param[ 72 ]
#define IxxRider param[ 73 ]
#define IxyRider param[ 74 ]
#define IyyRider param[ 75 ]
#define IxzRider param[ 76 ]
#define IzzRider param[ 77 ]
#define IyzRider param[ 78 ]
#define xp_0 param[ 79 ]
#define yp_0 param[ 80 ]
#define zp_0 param[ 81 ]
#define KMan param[ 82 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define lambda3 unknowns[ 2 ]
#define lambda4 unknowns[ 3 ]
#define lambda5 unknowns[ 4 ]
#define ycdg_input inputs[ 0 ]
#define MomRuedaIzq inputs[ 1 ]
#define MomRuedaDcha inputs[ 2 ]
double * _dPhi_dq = NULL;
void Init_dPhi_dq ( ) 
 {
    _dPhi_dq = malloc ( dPhi_dq_n_rows * dPhi_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhi_dq_n_rows * dPhi_dq_n_cols ; i++ ) {_dPhi_dq[i]=0.0;}
  }
 }

void Done_dPhi_dq ( ) 
{
if (_dPhi_dq != NULL) 
free (_dPhi_dq ); 
_dPhi_dq = NULL; 
}


double * dPhi_dq ()
{
if ( _dPhi_dq == NULL )
 {
    _dPhi_dq = malloc ( dPhi_dq_n_rows * dPhi_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhi_dq_n_rows * dPhi_dq_n_cols ; i++ ) {_dPhi_dq[i]=0.0;}
  }
 }
{
#include "dPhi_dq_maple_include.c"
}
return _dPhi_dq;
}

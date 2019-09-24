/*----------unknowns.h lib3D_MEC expoted-----------*/

extern double * unknowns;
extern void Init_unknowns_values ( void );
extern void Init_unknowns ( );
extern void Done_unknowns( );
extern void Reallocate_unknowns( double * user_unknowns );

#define n_unknowns 5

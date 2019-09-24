

extern int newton_raphson_min_norm (int ma, int na,
			     double * (* A)(),
			     double * (* b)(),
			     double * q);


int minimum_norm_solution(int ma, int na, double * A, int nrhs, double * B, double *X);

int minimum_norm_correction(int ma, int na, double * A, double * B, double *X);

int newton_raphson_min_norm_once (int ma, int na,
                 double * (* A)(),
                 double * (* b)(),
                 double * q);

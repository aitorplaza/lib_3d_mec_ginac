// print matrices

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "print_mat.h"

int printf_matrix(int ma, int na, double * A, const char * name) {

	int i=0;
	int j=0;

	printf("\n%s=[\n",name);
	for (i=0;i<ma-1;i++){
		for (j=0;j<na-1;j++)
			printf("%3.16g,\t",A[j*ma+i]);

		printf("%3.16g;\n",A[(na-1)*ma+i]);
	}
	for (j=0;j<na-1;j++)
		printf("%3.16g,\t",A[j*(ma)+(ma-1)]);

	printf("%3.16g;];\n\n",A[na*ma-1]);

}


int printf_vector(int ma, double * b, const char * name){

	int i=0;

	printf("\n%s=[",name);
	for (i=0;i<ma-1 ; i++){
		printf("%3.16g; ",b[i]);
	}
	printf("%3.16g];\n\n",b[ma-1]);

}

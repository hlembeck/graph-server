#include <stdio.h>
#include <stdlib.h>

struct int_matrix{
	int m, n;
	int **mat;
};

void print_int_matrix(struct int_matrix mat);
void delete_int_matrix(struct int_matrix *mat);
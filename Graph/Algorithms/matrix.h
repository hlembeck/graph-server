#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "arr_algs.h"

void free_int_matrix(int_matrix a);
void print_int_matrix(int_matrix a);
int_matrix int_id_n(int n);

//User constructed matrix
int_matrix construct_matrix();

int_matrix make_square(int_matrix a, int lowbound);

int_matrix multiply(int_matrix a, int_matrix b);

/*
Parameters to be a matrix of two rows, corresponding to paramaters of a and b respectively.
Each row is of the form (row_start row_end column_start column_end)
*/
int_matrix multiply_recursive(int_matrix a, int_matrix b);
void multiply_recursive_helper(int_matrix a, int a_rs, int a_re, int a_cs, int a_ce, int_matrix b, int b_rs, int b_re, int b_cs, int b_ce, int_matrix *c);


int_matrix mult_Strassen(int_matrix a, int_matrix b);

char is_Monge(int_matrix a);
//Given Monge matrix a, computes returns array of leftmost minimum elements of the rows of a
int *leftmost_min(int_matrix a);
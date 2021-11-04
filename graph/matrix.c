#include "matrix.h"

void print_int_matrix(struct int_matrix matrix){
	for(int i=0;i<matrix.m;i++){
		for(int j=0;j<matrix.n;j++){
			printf("%d" , matrix.mat[i][j]);
		}
		printf("\n");
	}
	return;
}

void delete_int_matrix(struct int_matrix *matrix){
	for(int i=0;i<matrix->m;i++){
		free(matrix->mat[i]);
	}
	free(matrix->mat);
	free(matrix);
	return;
}
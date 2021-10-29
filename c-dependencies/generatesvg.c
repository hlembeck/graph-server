#include "graph.h"

int main(int argc, char **argv){
	uint32_t n =2;
	struct graph g;
	printf("test\n");
	K_n(&g, n);
	printf("test0\n");
	struct graph2 h = graph2graph2(g);
	printf("test1\n");
	/*
	int r1[2] = {0,0};
	int r2[2] = {0,0};
	int *mat[2] = {r1, r2};
	adjmatrix(h, mat);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
	*/
	return 0;
}
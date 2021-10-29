#include "graph.h"

int main(){
	int n=10;
	struct graph *g = n_cycle(n);
	struct int_matrix *matrix = adjmatrix(*g);
	print_int_matrix(*matrix);
	delete_int_matrix(matrix);
	deletegraph(g);
	return 0;
}

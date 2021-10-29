#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

struct vertex{
	struct vertex **neighbors;
	int nlen;
	int val;
};

struct graph{
	struct vertex *vertices;
	int vlen;
};

struct graph *n_cycle(int n);
struct graph *n_wheel(int n);
struct graph *n_complete(int n);
void printgraph(struct graph g);
struct int_matrix *adjmatrix(struct graph g);
void deletegraph(struct graph *g);
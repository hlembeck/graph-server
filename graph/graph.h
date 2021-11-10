#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"
#include "../file-handling/fhandling.h"

/* Common CS definition */
struct vertex{
	struct vertex **neighbors;
	int nlen;
	int val;
	int id;
};

/* A pair of non-negative integers. */
struct basicedge{
	unsigned int initial;
	unsigned int final;
};

/* Standard implimentation of a (directed) graph. Elements of vertices are expected to have id corresponding to their index. */
struct graph{
	struct vertex *vertices;
	int vlen;
};

/* A finite mathematical (undirected) graph */
struct basicgraph{
	unsigned int *vertices;
	struct basicedge *edges;
	unsigned int vlen;
	unsigned int elen;
};

struct graph *n_cycle(int n);
struct graph *n_wheel(int n);
struct graph *n_complete(int n);
void printgraph(struct graph g);
struct int_matrix *adjmatrix(struct graph g);
void deletegraph(struct graph *g);
struct basicgraph *graph2basicgraph(struct graph *g);
void deletebasicgraph(struct basicgraph *g);

void printgraphJSON(struct graph g);
void printbasicgraphJSON(struct basicgraph g);
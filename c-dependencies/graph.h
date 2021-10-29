#include <stdint.h>
#include <stdio.h>

struct vertex{
	/* nlen is length of neighbors array */
	uint32_t nlen;
	/* array of neighbors */
	struct vertex *neighbors;
	int value;
};

struct edge{
	struct vertex initial;
	struct vertex final;
};

struct graph{
	/* vlen is length of vertices array */
	uint32_t vlen;
	struct vertex *vertices;
};

/* Standard representation of a graph as a set of vertices and edges. */
struct graph2{
	struct vertex *vertices;
	struct edge *edges;
	uint32_t vlen;
	uint64_t elen;
};

/* dimensions of mat assumed to be of size g.vlen. mat must also be initialized to 0 array */
void adjmatrix(struct graph2 g, int *mat[]);
void K_n(struct graph *g, uint32_t n);
struct graph2 graph2graph2(struct graph g);

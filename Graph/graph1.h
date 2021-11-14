#include "combinatorics.h"
#include <string.h>

/* An ordered pair of integers. */
typedef struct edge1 {
	unsigned int initial;
	unsigned int final;
} directed_edge;

/*
Describes a finite mathematical (directed) graph.
IMPORTANT: Given graph1's g and h with g.n <= h.n, it follows that h contains all vertices of g.
*/
typedef struct graph1 {
	/* Set of vertices is {0,...,n-1} */
	unsigned int n;
	directed_edge *edges;
	unsigned int elen;
} graph1;

void delete_graph1(graph1 *g);
void print_graph1(graph1 g);


/*
Functions that generate graphs given a number of vertices.
*/

/* Returns pointer to a graph1 describing an n-cycle, where edges are 0->1->...->n-1->0 */
graph1 *increasing_n_cycle1(unsigned int n);

/* Complete directed graph on n vertices */
graph1 *n_complete1(unsigned int n);

/* Graph with n-1 spokes directed at 0 */
graph1 *inward_n_star1(unsigned int n);




/* Checks if g contains e as an edge */
char is_edge1(graph1 g, directed_edge e);

/* Disjoint union of g and h. This operation is commutative up to graph isomorphism. */
graph1 *sum1(graph1 g, graph1 h);

/* Union of g and h. */
graph1 *union1(graph1 g, graph1 h);

/* Checks if endpoints of edges are valid */
char is_valid1(graph1 g);
char is_simple1(graph1 g);

/* Transpose of g. */
graph1 *transpose1(graph1 g);
void clean_transpose1(graph1 *g);

/* Complement of g */
graph1 *complement1(graph1 g);

/* Assumed map points to array of size g.n */
char is_homomorphism1(graph1 g, graph1 h, unsigned int *map);

/* Assumes g and h are simple. */
char are_isomorphic1(graph1 g, graph1 h);
char are_equal1(graph1 g, graph1 h);


/* 
For server interface
*/

/* Returns JSON-style string of g */
char *graph1_JSON(graph1 g);
graph1 *graph1_from_JSON(char *json);
#include "graph2.h"


/* Neighbors are indices of vertices, instead of pointers to vertices. This improves speed of some algorithms. */
typedef struct vertex_alt{
	unsigned int *neighbors;
	unsigned int nlen;
} vertex_alt;

typedef struct graph2_alt{
	vertex_alt *vertices;
	unsigned int vlen;
} graph2_alt;

typedef struct graph2_alt_search{
	vertex_alt *vertices;
	/* value of index determines whether vertex has been visited by algorithm. Should be reset after each search. */
	unsigned char *visited;
	unsigned int vlen;
} graph2_alt_search;

graph2_alt_search *init_alt_search(graph2_alt g);
void print_graph2_alt_search(graph2_alt_search g);
void delete_graph2_alt_search(graph2_alt_search *g);

graph2_alt *graph2_alt_from_graph2(graph2 g);
graph2 *graph2_from_graph2_alt(graph2_alt g);
void delete_graph2_alt(graph2_alt *g);
void print_graph2_alt(graph2_alt g);

/* Indices of a shortest path */
unsigned int *shortest_path2_alt(graph2_alt_search g, unsigned int initial, unsigned int final, unsigned short *len);
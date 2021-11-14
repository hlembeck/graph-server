#include <string.h>
#include "graph1.h"

typedef struct vertex{
	struct vertex **neighbors;
	unsigned int nlen;
} vertex;

typedef struct graph2{
	vertex *vertices;
	unsigned int vlen;
} graph2;

typedef struct vertex_search{
	struct vertex_search **neighbors;
	unsigned int nlen;
	char visited;
} vertex_search;

typedef struct graph2_search{
	vertex_search *vertices;
	unsigned int vlen;
} graph2_search;

graph2 *graph2_from_graph1(graph1 g);
graph1 *graph1_from_graph2(graph2 g);
graph2_search *graph2_search_from_graph1(graph1 g);

void print_graph2(graph2 g);
void print_graph2_search(graph2_search g);
void delete_graph2(graph2 *g);
void delete_graph2_search(graph2_search *g);

/* Returns a maximal clique of g containing v */
vertex **init_max_clique(vertex *v, unsigned int *rlen);
vertex **maximal_clique(vertex *v, vertex **candidates, unsigned int clen, unsigned int *rlen);
void print_clique(graph2 g, vertex **clique, unsigned int clen);

void reachable_vertices2(graph2_search g, stack **s);
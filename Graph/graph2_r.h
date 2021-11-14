#include "graph1.h"

/* 'r' for 'robust' */
typedef struct vertex_r{
	struct vertex_r **neighbors;

	/* index of vertex in parent graph's vertex list */
	unsigned int v_id;
	unsigned int nlen;
	/* for traversal algorithms */
	char visited;

	/* optional weight of vertex */
	long weight;

	/* 
	Optional list of weights of edges from current vertex. 
	If unweighted, initialized to 1 
	*/
	long *edge_weights;

	/* pointer to some value, to which the vertex might refer */
	char *value;
} vertex_r;

typedef struct graph2_r{
	vertex_r *vertices;
	unsigned int vlen;
} graph2_r;

/* Unweighted graph2_r from a graph1 */
graph2_r *graph2_r_from_graph1(graph1 g);
/* Destroys barebones graph1 */
graph1 *graph1_from_graph2_r(graph2_r g);

void print_graph2_r(graph2_r g);
void delete_graph2_r(graph2_r *g);
void print_reachable_vertices2_r(graph2_r g, unsigned int initial);

vertex_r *reachable_vertices2_r(graph2_r g, unsigned int initial, unsigned int *len);
vertex_r *shortest_path2_r(graph2_r g, unsigned int initial, unsigned int final, unsigned int *len);
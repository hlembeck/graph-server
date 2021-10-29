#include "graph.h"

struct graph *n_cycle(int n){
	struct graph *g = malloc(sizeof(struct graph));
	struct vertex *v = malloc(sizeof(struct vertex)*n);
	g->vertices = v;
	g->vlen = n;
	for(int i=0;i<n;i++){
		struct vertex **nbr = malloc(sizeof(char *));
		v[i].val = i;
		v[i].nlen = 1;
		if(i!=0)
			nbr[0] = &v[i-1];
		else{
			nbr[0] = &v[n-1];
		}
		v[i].neighbors = nbr;
	}
	return g;
}

void deletegraph(struct graph *g){
	for(int i=0;i<g->vlen;i++){
		if(g->vertices[i].neighbors){
			free((g->vertices[i]).neighbors);
		}
	}
	free(g->vertices);
	free(g);
	return;
}


struct graph *n_wheel(int n){
	struct graph *g = malloc(sizeof(struct graph));
	struct vertex *v = malloc(sizeof(struct vertex)*n);
	g->vertices = v;
	g->vlen = n;
	for(int i=0;i<n;i++){
		v[i].val = i;
		v[i].nlen = 2;
		struct vertex **nbrs = malloc(sizeof(char *)*2);
		nbrs[0] = &v[0];
		if(i!=0)
			nbrs[1] = &v[i-1];
		else
			nbrs[1] = &v[n-1];
		v[i].neighbors = nbrs;
	}
	return g;
}

struct graph *n_complete(int n){
	struct graph *g = malloc(sizeof(struct graph));
	struct vertex *v = malloc(sizeof(struct vertex)*n);
	g->vertices = v;
	g->vlen = n;
	for(int i=0;i<n;i++){
		struct vertex **nbrs = malloc(sizeof(char *)*(n-1));
		v[i].val = i;
		v[i].nlen = n-1;
		v[i].neighbors = nbrs;
		for(int j=0;j<n;j++){
			if(j<i){
				nbrs[j] = &v[j];
				continue;
			}
			if(i<j){
				nbrs[j-1] = &v[j];
			}
		}
	}
	return g;
}

void printgraph(struct graph g){
	for(int i=0;i<g.vlen;i++){
		printf("Neighbors of vertex %d:", g.vertices[i].val);
		for(int j=0;j<g.vertices[i].nlen;j++){
			if(j == 0)
				printf(" %d ", g.vertices[i].neighbors[j]->val);
			else
				printf(", %d ", g.vertices[i].neighbors[j]->val);
		}
		printf("\n");
	}
	return;
}

struct int_matrix *adjmatrix(struct graph g){
	struct int_matrix *mat = malloc(sizeof(struct int_matrix));
	mat->m = g.vlen;
	mat->n = g.vlen;
	int m = g.vlen;
	int **adj = malloc(sizeof(char *)*m);
	for(int i=0;i<m;i++){
		int *row = malloc(sizeof(int)*m);
		adj[i] = row;
		for(int j=0;j<m;j++){
			adj[i][j] = 0;
		}
	}

	for(int i=0;i<m;i++){
		for(int j=0;j<g.vertices[i].nlen;j++){
			adj[i][g.vertices[i].neighbors[j]->val]++;
		}
	}
	mat->mat = adj;
	return mat;
}
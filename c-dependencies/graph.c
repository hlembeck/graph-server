#include "graph.h"

void adjmatrix(struct graph2 g, int *mat[]){
	int k,l;
	for(int i=0; i<g.elen; i++){
		for(int j=0; j<g.vlen; j++){
			if(&g.vertices[j]==&g.edges[i].initial)
				k=j;
			if(&g.vertices[j]==&g.edges[i].final)
				l=j;
		}
		mat[k][l] += 1;
	}
	return;
}

void K_n(struct graph *g, uint32_t n){
	if(n<2){
		printf("Trivial graph.\n");
		return;
	}
	struct vertex vertices[n];
	for(int i=0; i<n; i++){
		struct vertex v;
		v.value = i;
		vertices[i] = v;
	}

	for(int i=0; i<n; i++){
		struct vertex t[n-1];
		for(int j=0; j<n-1; j++){
			if(i == j){
				j++;
				continue;
			}
			t[j] = vertices[j];
		}
		vertices[i].neighbors = t;
		vertices[i].nlen = n-1;
	}
	g->vertices = vertices;
	g->vlen = n;
	return;
}

struct graph2 graph2graph2(struct graph g){
	int edgec = 0;
	for(int i=0; i<g.vlen; i++){
		edgec = edgec+g.vertices[i].nlen;
		printf("%d\n", (g.vertices[i]).nlen);
	}
	printf("%d\n", edgec);
	//struct edge edges[edgec];
	/*
	int k=0;
	for(int i=0; i<g.vlen; i++){
		printf("testg2\n");
		for(int j=0;j<g.vertices[i].nlen; j++){
			edges[k].initial = g.vertices[i];
			edges[k].final = g.vertices[i].neighbors[j];
			k++;
		}
	}
	struct graph2 h = {g.vertices , edges , g.vlen , edgec};
	*/
	struct graph2 h;
	return h;
}
#include "graph2_alt.h"

graph2_alt *graph2_alt_from_graph2(graph2 g){
	graph2_alt *ret = malloc(sizeof(graph2_alt));
	vertex_alt *vertices = malloc(sizeof(vertex_alt)*g.vlen);
	for(unsigned int i=0;i<g.vlen;i++){
		unsigned int *neighbors = malloc(sizeof(int)*g.vertices[i].nlen);
		for(unsigned int j=0;j<g.vertices[i].nlen;j++){
			for(unsigned int k=0;k<g.vlen;k++){
				if(&g.vertices[k] == g.vertices[i].neighbors[j])
					neighbors[j] = k;
			}
		}
		vertices[i].neighbors = neighbors;
		vertices[i].nlen = g.vertices[i].nlen;
	}
	ret->vertices = vertices;
	ret->vlen = g.vlen;
	return ret;
}

graph2 *graph2_from_graph2_alt(graph2_alt g){
	graph2 *ret = malloc(sizeof(graph2));
	vertex *vertices = malloc(sizeof(vertex)*g.vlen);
	for(unsigned int i=0;i<g.vlen;i++){
		vertex **neighbors = malloc(sizeof(char *)*g.vertices[i].nlen);
		for(unsigned int j=0;j<g.vertices[i].nlen;j++){
			neighbors[j] = &vertices[g.vertices[i].neighbors[j]];
		}
		vertices[i].neighbors = neighbors;
		vertices[i].nlen = g.vertices[i].nlen;
	}
	ret->vertices = vertices;
	ret->vlen = g.vlen;
	return ret;
}

void delete_graph2_alt(graph2_alt *g){
	for(unsigned int i=0;i<g->vlen;i++){
		free(g->vertices[i].neighbors);
	}
	free(g->vertices);
	free(g);
	return;
}

void print_graph2_alt(graph2_alt g){
	printf("------ Print of graph2 ------\n\n");
	for(unsigned int i=0;i<g.vlen;i++){
		printf("Neighbors of %d:", i);
		for(unsigned int j=0;j<g.vertices[i].nlen;j++){
			printf(" %d", g.vertices[i].neighbors[j]);
		}
		printf("\n");
	}
	printf("\n-----------------------------\n");
	return;
}

unsigned int *shortest_path2_alt(graph2_alt_search g, unsigned int initial, unsigned int final, unsigned short *len){
	g.visited[initial] = 1;
	unsigned int *ret=malloc(0), *temp;
	unsigned short old_len;
	vertex_alt s = g.vertices[initial];
	if(initial == final){
		*len = 1;
		ret = malloc(sizeof(int));
		*ret = initial;
		return ret;
	}

	for(unsigned int i=0;i<s.nlen;i++){
		if(s.neighbors[i] == final){
			*len = 2;
			free(ret);
			ret = malloc(sizeof(int)*2);
			ret[0] = initial;
			ret[1] = final;
			return ret;
		}

		if(!g.visited[s.neighbors[i]]){
			old_len = *len;
			temp = shortest_path2_alt(g, s.neighbors[i], final, len);
			if(*len < old_len){
				free(ret);
				ret = malloc(sizeof(int)*((*len)+1));
				memcpy(&ret[1], temp, sizeof(int)*(*len));
			}
			else{
				*len = old_len;
			}
			free(temp);
		}
	}

	if(*len < USHRT_MAX){
		ret[0] = initial;
		(*len)++;
	}
	return ret;
}

graph2_alt_search *init_alt_search(graph2_alt g){
	graph2_alt_search *ret = malloc(sizeof(graph2_alt_search));
	vertex_alt *vertices = malloc(sizeof(vertex_alt)*g.vlen);
	unsigned char *visited = malloc(g.vlen);
	memset(visited,0,g.vlen);
	ret->visited = visited;
	for(unsigned int i=0;i<g.vlen;i++){
		unsigned int *neighbors = malloc(sizeof(int)*g.vertices[i].nlen);
		memcpy(neighbors, g.vertices[i].neighbors, sizeof(int)*g.vertices[i].nlen);
		vertices[i].nlen = g.vertices[i].nlen;
		vertices[i].neighbors = neighbors;
	}
	ret->vertices = vertices;
	ret->vlen = g.vlen;
	return ret;
}

void delete_graph2_alt_search(graph2_alt_search *g){
	for(unsigned int i=0;i<g->vlen;i++){
		free(g->vertices[i].neighbors);
	}
	free(g->vertices);
	free(g->visited);
	free(g);
	return;
}

void print_graph2_alt_search(graph2_alt_search g){
	printf("------ Print of graph2 ------\n\n");
	for(unsigned int i=0;i<g.vlen;i++){
		printf("Neighbors of %d:", i);
		for(unsigned int j=0;j<g.vertices[i].nlen;j++){
			printf(" %d", g.vertices[i].neighbors[j]);
		}
		printf("\n");
	}
	printf("\n");
	for(unsigned int i=0;i<g.vlen;i++){
		printf("visited(%d): %d\n",i,g.visited[i]);
	}
	printf("\n-----------------------------\n");
	return;
}
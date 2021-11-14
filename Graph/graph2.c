#include "graph2.h"

graph2 *graph2_from_graph1(graph1 g){
	graph2 *ret = malloc(sizeof(graph2));
	vertex *vertices = malloc(sizeof(vertex)*g.n);
	int c;
	for(unsigned int i=0;i<g.n;i++){
		c=0;
		for(unsigned int j=0;j<g.elen;j++){
			if(g.edges[j].initial == i)
				c++;
		}
		vertex **neighbors = malloc(sizeof(char *)*c);
		c=0;
		for(unsigned int j=0;j<g.elen;j++){
			if(g.edges[j].initial == i){
				neighbors[c] = &vertices[g.edges[j].final];
				c++;
			}
		}
		vertices[i].neighbors = neighbors;
		vertices[i].nlen = c;
	}
	ret->vlen = g.n;
	ret->vertices = vertices;
	return ret;
}

graph2_search *graph2_search_from_graph1(graph1 g){
	graph2_search *ret = malloc(sizeof(graph2_search));
	vertex_search *vertices = malloc(sizeof(vertex_search)*g.n);
	int c;
	for(unsigned int i=0;i<g.n;i++){
		c=0;
		for(unsigned int j=0;j<g.elen;j++){
			if(g.edges[j].initial == i)
				c++;
		}
		vertex_search **neighbors = malloc(sizeof(char *)*c);
		c=0;
		for(unsigned int j=0;j<g.elen;j++){
			if(g.edges[j].initial == i){
				neighbors[c] = &vertices[g.edges[j].final];
				c++;
			}
		}
		vertices[i].neighbors = neighbors;
		vertices[i].nlen = c;
		vertices[i].visited = 0;
	}
	ret->vlen = g.n;
	ret->vertices = vertices;
	return ret;
}

graph1 *graph1_from_graph2(graph2 g){
	graph1 *ret = malloc(sizeof(graph1));
	unsigned int elen = 0;
	ret->n = g.vlen;
	for(unsigned int i=0;i<g.vlen;i++){
		elen += g.vertices[i].nlen;
	}
	directed_edge *edges = malloc(sizeof(directed_edge)*elen);
	elen = 0;
	for(unsigned int i=0;i<g.vlen;i++){
		for(unsigned int j=0;j<g.vertices[i].nlen;j++){
			edges[elen].initial = i;
			for(unsigned int k=0;k<g.vlen;k++){
				if(&g.vertices[k] == g.vertices[i].neighbors[j])
					edges[elen].final = k;
			}
			elen++;
		}
	}
	ret->edges = edges;
	ret->elen = elen;
	return ret;
}

void print_graph2(graph2 g){
	printf("------ Print of graph2 ------\n\n");
	for(unsigned int i=0;i<g.vlen;i++){
		printf("Neighbors of %d:", i);
		for(unsigned int j=0;j<g.vertices[i].nlen;j++){
			for(unsigned int k=0;k<g.vlen;k++){
				if(&g.vertices[k] == g.vertices[i].neighbors[j])
					printf(" %d", k);
			}
		}
		printf("\n");
	}
	printf("\n-----------------------------\n");
	return;
}

void print_graph2_search(graph2_search g){
	printf("------ Print of graph2_search ------\n\n");
	for(unsigned int i=0;i<g.vlen;i++){
		printf("Neighbors of %d (visited: %d):", i, g.vertices[i].visited);
		for(unsigned int j=0;j<g.vertices[i].nlen;j++){
			for(unsigned int k=0;k<g.vlen;k++){
				if(&g.vertices[k] == g.vertices[i].neighbors[j])
					printf(" %d", k);
			}
		}
		printf("\n");
	}
	printf("\n-----------------------------\n");
	return;
}

void delete_graph2(graph2 *g){
	for(unsigned int i=0;i<g->vlen;i++){
		free(g->vertices[i].neighbors);
	}
	free(g->vertices);
	free(g);
	return;
}

void delete_graph2_search(graph2_search *g){
	for(unsigned int i=0;i<g->vlen;i++){
		free(g->vertices[i].neighbors);
	}
	free(g->vertices);
	free(g);
	return;
}

/* Assumed all candidates are neighbors of v. Graph must be simple */
vertex **maximal_clique(vertex *v, vertex **candidates, unsigned int clen, unsigned int *rlen){
	vertex **ret;
	/* If no more candidates, return the last vertex v in the clique */
	if(clen == 0){
		*rlen = 1;
		ret = malloc(sizeof(char *));
		ret[0] = v;
		return ret;
	}


	vertex **t;
	unsigned int c = 0;
	for(unsigned int i=0;i<clen;i++){
		for(unsigned int j=0;j<candidates[i]->nlen;j++){
			if(candidates[0] != candidates[i]->neighbors[j])
				continue;
			for(unsigned int k=0;k<candidates[0]->nlen;k++){
				if(candidates[i] == candidates[0]->neighbors[k])
					c++;
			}
		}
	}


	vertex **new_candidates = malloc(sizeof(char *)*c);
	c = 0;
	for(unsigned int i=0;i<clen;i++){
		for(unsigned int j=0;j<candidates[i]->nlen;j++){
			if(candidates[0] != candidates[i]->neighbors[j])
				continue;
			for(unsigned int k=0;k<candidates[0]->nlen;k++){
				if(candidates[i] == candidates[0]->neighbors[k]){
					new_candidates[c] = candidates[i];
					c++;
				}
			}
		}
	}

	t = maximal_clique(candidates[0],new_candidates,c,rlen);
	free(new_candidates);
	ret = malloc(sizeof(char *)*(*rlen+1));
	ret[0] = v;
	for(unsigned int i=0;i<*rlen;i++){
		ret[i+1]=t[i];
	}
	free(t);
	*rlen+=1;
	return ret;
}

vertex **init_max_clique(vertex *v, unsigned int *rlen){
	unsigned int c = 0;
	for(unsigned int i=0;i<v->nlen;i++){
		for(unsigned int j=0;j<v->neighbors[i]->nlen;j++){
			if(v == v->neighbors[i]->neighbors[j])
				c++;
		}
	}
	vertex *init_candidates[c];
	c = 0;
	for(unsigned int i=0;i<v->nlen;i++){
		for(unsigned int j=0;j<v->neighbors[i]->nlen;j++){
			if(v == v->neighbors[i]->neighbors[j]){
				init_candidates[c] = v->neighbors[i];
				c++;
			}
		}
	}

	return maximal_clique(v, init_candidates, c, rlen);
}

void print_clique(graph2 g, vertex **clique, unsigned int clen){
	printf("------ Print of clique ------\n\n");
	printf("Vertices:");
	for(unsigned int i=0;i<clen;i++){
		for(unsigned int j=0;j<g.vlen;j++){
			if(&g.vertices[j] == clique[i])
				printf(" %d", j);
		}
	}
	printf("\n");
	printf("\n-----------------------------\n");
	return;
}

void reachable_vertices2(graph2_search g, stack **s){
	vertex_search *curr_vertex = (vertex_search *)(*s)->value;
	curr_vertex->visited = 1;
	for(unsigned int i=0;i<curr_vertex->nlen;i++){
		if(!curr_vertex->neighbors[i]->visited){
			push(s, (char *)curr_vertex->neighbors[i]);
			reachable_vertices2(g,s);
		}
	}
	return;
}
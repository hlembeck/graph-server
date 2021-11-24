#include "graph2_r.h"

graph2_r *graph2_r_from_graph1(graph1 g){
	graph2_r *ret = malloc(sizeof(graph2_r));
	vertex_r *vertices = malloc(sizeof(vertex_r)*g.n);
	unsigned int c=0;
	for(unsigned int i=0;i<g.n;i++){
		vertices[i].v_id = i;
		vertices[i].visited = 0;
		vertices[i].weight = 0;

		for(unsigned int j=0;j<g.elen;j++){
			if(g.edges[j].initial==i)
				c++;
		}

		vertex_r **neighbors = malloc(sizeof(char *)*c);
		long *edge_weights = malloc(sizeof(long)*c);
		c=0;
		for(unsigned int j=0;j<g.elen;j++){
			if(g.edges[j].initial==i){
				neighbors[c] = &vertices[g.edges[j].final];
				edge_weights[c] = 1;
				c++;
			}
		}
		vertices[i].neighbors = neighbors;
		vertices[i].nlen = c;
		vertices[i].edge_weights = edge_weights;
		c=0;
	}
	ret->vertices = vertices;
	ret->vlen = g.n;
	return ret;
}

graph1 *graph1_from_graph2_r(graph2_r g){
	graph1 *ret = malloc(sizeof(graph1));
	unsigned int elen = 0;
	for(unsigned int i=0;i<g.vlen;i++){
		elen+=g.vertices[i].nlen;
	}
	directed_edge *edges = malloc(sizeof(directed_edge)*elen);
	elen = 0;
	for(unsigned int i=0;i<g.vlen;i++){
		for(unsigned int j=0;j<g.vertices[i].nlen;j++){
			edges[elen].initial = i;
			edges[elen].final = g.vertices[i].neighbors[j]->v_id;
			elen++;
		}
	}
	ret->edges = edges;
	ret->n = g.vlen;
	ret->elen = elen;
	return ret;
}

void print_graph2_r(graph2_r g){
	printf("------ Print of graph2_r ------\n\n");
	for(unsigned int i=0;i<g.vlen;i++){
		printf("[Vertex: %d] [Visited: %d] [Weight: %ld]\n Neighbors:\n", i, g.vertices[i].visited, g.vertices[i].weight);
		for(unsigned int j=0;j<g.vertices[i].nlen;j++){
			printf("  %d -> %d (weight: %ld)\n", i, g.vertices[i].neighbors[j]->v_id, g.vertices[i].edge_weights[j]);
		}
		printf("\n");
	}
	printf("-------------------------------\n\n");
	return;
}

void delete_graph2_r(graph2_r *g){
	for(unsigned int i=0;i<g->vlen;i++){
		free(g->vertices[i].neighbors);
		free(g->vertices[i].edge_weights);
	}
	free(g->vertices);
	free(g);
	return;
}

vertex_r *reachable_vertices2_r(graph2_r g, unsigned int initial, unsigned int *len){
	*len = 0;
	vertex_r *ret=NULL;
	vertex_r v = g.vertices[initial];
	stack *s = init_stack((char *)&v);
	unsigned char visited[g.vlen];
	memset(visited, 0, g.vlen);
	while(s){
		v = *(vertex_r *)pop(&s);
		for(unsigned int i=0;i<v.nlen;i++){
			if(!visited[v.neighbors[i]->v_id]){
				push(&s,(char *)v.neighbors[i]);
				visited[v.neighbors[i]->v_id] = 1;
				(*len)++;
			}
		}
	}
	ret = malloc(sizeof(vertex_r)*(*len));
	*len = 0;
	for(unsigned int i=0;i<g.vlen;i++){
		if(visited[i]){
			ret[*len] = g.vertices[i];
			(*len)++;
		}
	}
	return ret;
}

void print_reachable_vertices2_r(graph2_r g, unsigned int initial){
	unsigned int len;
	vertex_r *list = reachable_vertices2_r(g,initial,&len);
	printf("\nVertices reachable from %d:\n", initial);
	for(unsigned int i=0;i<len;i++){
		printf(" %d", list[i].v_id);
	}
	printf("\n\n");
	free(list);
	return;
}

vertex_r *shortest_path2_r(graph2_r g, unsigned int initial, unsigned int final, unsigned int *len){
	*len = 0;
	vertex_r *ret, *v=&g.vertices[initial];
	fifo *q = init_fifo((char *)v);
	v->value = NULL;
	//v->visited records whether v has been enqueue'd
	v->visited = 1;
	while(q){
		v = (vertex_r *)deq(&q);
		if(v->v_id == final){
			ret = v;
			while(v){
				v = (vertex_r *)v->value;
				(*len)++;
			}
			v = ret;
			ret = malloc(sizeof(vertex_r)*(*len));
			for(unsigned int i=0;i<*len;i++){
				ret[(*len)-i-1] = *v;
				v = (vertex_r *)v->value;
			}
			return ret;
		}
		for(unsigned int i=0;i<v->nlen;i++){
			//ret acts as temp variable
			ret = v->neighbors[i];
			if(!ret->visited){
				ret->visited = 1;
				//u->value stores (pointer to) previous vertex
				ret->value = (char *)v;
				if(q){
					enq(q,(char *)ret);
				}
				else{
					q = init_fifo((char *)ret);
				}
			}
		}
	}
	return NULL;
}
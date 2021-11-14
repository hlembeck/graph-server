#include "graph1.h"

graph1 *sum1(graph1 g, graph1 h){
	unsigned int a = g.elen;
	unsigned int b = h.elen;
	graph1 *ret = malloc(sizeof(graph1));
	ret->n = g.n+h.n;
	directed_edge *edges = malloc(sizeof(directed_edge)*(a+b));
	for(unsigned int i=0;i<a;i++){
		edges[i] = g.edges[i];
	}
	for(unsigned int i=0;i<b;i++){
		edges[a+i].initial  = h.edges[i].initial + g.n;
		edges[a+i].final  = h.edges[i].final + g.n;
	}
	ret->edges = edges;
	ret->elen = a+b;
	return ret;
}

graph1 *union1(graph1 g, graph1 h){
	graph1 *r = malloc(sizeof(graph1));
	unsigned int overlap = 0;
	if(g.n>h.n)
		r->n = g.n;
	else
		r->n = h.n;
	for(unsigned int i=0;i<g.n;i++){
		if(is_edge1(h, g.edges[i]))
			overlap++;
	}

	directed_edge *edges = malloc(sizeof(directed_edge)*(g.elen+h.elen-overlap));
	r->elen = g.elen+h.elen-overlap;
	overlap = 0;
	for(unsigned int i=0;i<g.elen;i++){
		edges[i] = g.edges[i];
	}
	for(unsigned int i=0;i<h.elen;i++){
		if(is_edge1(g,h.edges[i])){
			overlap++;
			continue;
		}
		edges[g.elen+i-overlap] = h.edges[i];
	}
	r->edges = edges;
	return r;
}

char is_edge1(graph1 g, directed_edge e){
	for(unsigned int i=0;i<g.elen;i++){
		if((g.edges[i].initial == e.initial) && (g.edges[i].final == e.final)){
			return 1;
		}
	}
	return 0;
}

char is_valid1(graph1 g){
	for(unsigned int i=0;i<g.elen;i++){
		if(g.edges[i].initial >= g.n || g.edges[i].final >= g.n)
			return 0;
	}
	return 1;
}

char is_simple1(graph1 g){
	for(unsigned int i=0;i<g.elen;i++){
		if(g.edges[i].initial == g.edges[i].final)
			return 0;
		for(unsigned int j=0;j<g.elen;j++){
			if(i==j)
				continue;
			if((g.edges[i].initial == g.edges[j].initial) && (g.edges[i].final == g.edges[j].final))
				return 0;
		}
	}
	return 1;
}

graph1 *increasing_n_cycle1(unsigned int n){
	if(n==0){
		/* Graph on zero vertices is empty */
		return NULL;
	}

	graph1 *g = malloc(sizeof(graph1));
	g->n = n;
	if(n==1){
		/* Simple graph on one vertex has no edges */
		g->edges = NULL;
		g->elen = 0;
	}
	else{
		directed_edge *edges = malloc(sizeof(directed_edge)*n);
		for(unsigned int i=0;i<n;i++){
			if(i != n-1){
				edges[i].initial = i;
				edges[i].final = i+1;			}
			else{
				edges[i].initial = n-1;
				edges[i].final = 0;
			}
		}
		g->edges = edges;
		g->elen = n;
	}
	return g;
}

graph1 *n_complete1(unsigned int n){
	if(n==0){
		/* Graph on zero vertices is empty */
		return NULL;
	}
	graph1 *g = malloc(sizeof(graph1));
	g->n = n;
	unsigned int c = 0;
	directed_edge *edges = malloc(sizeof(directed_edge)*n*(n-1));
	for(unsigned int i=0;i<n;i++){
		for(unsigned int j=0;j<n;j++){
			if(i==j)
				continue;
			edges[c].initial = i;
			edges[c].final = j;
			c++;
		}
	}
	g->edges = edges;
	g->elen = n*(n-1);
	return g;
}

graph1 *inward_n_star1(unsigned int n){
	if(n==0){
		/* Graph on zero vertices is empty */
		return NULL;
	}
	graph1 *g = malloc(sizeof(graph1));
	g->n = n;
	directed_edge *edges = malloc(sizeof(directed_edge)*(n-1));
	for(unsigned int i=1;i<n;i++){
		edges[i-1].initial = i;
		edges[i-1].final = 0;
	}
	g->edges = edges;
	g->elen = n-1;
	return g;
}

void delete_graph1(graph1 *g){
	free(g->edges);
	free(g);
}

void print_graph1(graph1 g){
	printf("------ Print of graph1 ------\n\n");
	printf("Vertices:\n  ");
	for(unsigned int i=0;i<g.n;i++){
		if(i==g.n-1)
			printf("%d\n", i);
		else
			printf("%d , ", i);
	}
	printf("Edges:\n");
	for(unsigned int i=0;i<g.elen;i++){
		printf("  %d -> %d\n", g.edges[i].initial, g.edges[i].final);
	}
	printf("\n-----------------------------\n");
	return;
}

char *graph1_JSON(graph1 g){
	char *temp = malloc(sizeof(char)*2*USHRT_MAX);
	char *ret;
	memset(temp, '\0', USHRT_MAX*2);
	sprintf(temp, "{\"vertices\":[");
	for(unsigned int i=0;i<g.n;i++){
		if(i==g.n-1){
			sprintf(temp, "%s%d", temp, i);
			continue;
		}
		sprintf(temp, "%s%d,", temp, i);
	}
	sprintf(temp, "%s],\"edges\":[", temp);
	for(unsigned int i=0;i<g.elen;i++){
		if(i==g.elen-1){
			sprintf(temp, "%s[%d,%d]", temp, g.edges[i].initial, g.edges[i].final);
			continue;
		}
		sprintf(temp, "%s[%d,%d],", temp, g.edges[i].initial, g.edges[i].final);
	}
	sprintf(temp, "%s]}", temp);
	ret = malloc(sizeof(char)*strlen(temp));
	strcpy(ret, temp);
	free(temp);
	return ret;
}

/* Assumes json of the form {"vertices":[v1,...,vn],"edges":[[i1,f1],...,[im,fm]]} */
graph1 *graph1_from_JSON(char *json){
	graph1 *g = malloc(sizeof(graph1));
	int n = 0, i=13, t=0;
	char temp[5];
	memset(temp,'\0',5);
	directed_edge *temp_edges = malloc(sizeof(directed_edge)*USHRT_MAX);
	directed_edge *edges;
	while(1){
		if(json[i]==','){
			i++;
			n++;
			continue;
		}
		else if(json[i]==']'){
			i+=11;
			n!=0 ? n++:0;
			break;
		}
		i++;
	}
	g->n = n;
	n=0;
	while(1){
		if(json[i]=='['){
			i++;
			continue;
		}
		else if(json[i]==',' && t==0){
			i++;
			continue;
		}
		else if(json[i]=='}'){
			break;
		}
		else if(json[i]==','){
			temp_edges[n].initial = atoi(temp);
			memset(temp,'\0',5);
			t=0;
			i++;
			continue;
		}
		else if(json[i]==']'){
			temp_edges[n].final = atoi(temp);
			memset(temp,'\0',5);
			t=0;
			i++;
			n++;
			continue;
		}
		temp[t] = json[i];
		t++;
		i++;
	}
	edges = malloc(sizeof(directed_edge)*n);
	memcpy(edges, temp_edges, sizeof(directed_edge)*n);
	free(temp_edges);
	g->edges = edges;
	g->elen = n;
	return g;
}

graph1 *transpose1(graph1 g){
	graph1 *h = malloc(sizeof(graph1));
	h->n = g.n;
	h->elen = g.elen;
	directed_edge *edges = malloc(sizeof(directed_edge)*g.elen);
	for(unsigned int i=0;i<g.elen;i++){
		edges[i].initial = g.edges[i].final;
		edges[i].final = g.edges[i].initial;
	}
	h->edges = edges;
	return h;
}

void clean_transpose1(graph1 *g){
	graph1 *t;
	graph1 *h = transpose1(*g);
	*t=*g;
	*g = *h;
	free(t);
	return;
}

graph1 *complement1(graph1 g){
	graph1 *h = malloc(sizeof(graph1));
	unsigned int c=0, n=g.n;
	h->n = n;
	directed_edge *edges = malloc(sizeof(directed_edge)*(n*(n-1)-g.elen));
	for(unsigned int i=0;i<n;i++){
		for(unsigned int j=0;j<n;j++){
			if(i==j)
				continue;
			directed_edge e = {i,j};
			if(is_edge1(g,e))
				continue;
			edges[c] = e;
			c++;
		}
	}
	h->edges = edges;
	h->elen = n*(n-1)-g.elen;
	return h;
}

char is_homomorphism1(graph1 g, graph1 h, unsigned int *map){
	for(unsigned int i=0;i<g.n;i++){
		if(map[i]>=h.n){
			printf("Does not map to h.\n");
			return 0;
		}
	}
	for(unsigned int i=0;i<g.elen;i++){
		directed_edge temp = {map[g.edges[i].initial],map[g.edges[i].final]};
		if(!is_edge1(h,temp))
			return 0;

	}
	return 1;
}

char are_isomorphic1(graph1 g, graph1 h){
	if(g.n != h.n || g.elen != h.elen){
		return 0;
	}
	unsigned int **permutations = get_all_permutations(g.n);
	for(unsigned int i=0;i<factorial(g.n);i++){
		if(is_homomorphism1(g,h,permutations[i]))
			return 1;
	}
	free_all_permutations(permutations, g.n);
	return 0;
}

char are_equal1(graph1 g, graph1 h){
	if(g.n != h.n || g.elen != h.elen)
		return 0;
	for(unsigned int i=0;i<g.elen;i++){
		if(!is_edge1(h, g.edges[i]))
			return 0;
	}
	return 1;
}


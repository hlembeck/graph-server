#include "graph.h"

struct graph *n_cycle(int n){
	struct graph *g = malloc(sizeof(struct graph));
	struct vertex *v = malloc(sizeof(struct vertex)*n);
	g->vertices = v;
	g->vlen = n;
	for(int i=0;i<n;i++){
		struct vertex **nbr = malloc(sizeof(char *));
		v[i].val = i;
		v[i].id = i;
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
		v[i].id = i;
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
		v[i].id = i;
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

void printgraphJSON(struct graph g){
	printf("{vertices:[");
	for(int i=0;i<g.vlen;i++){
		if(i==g.vlen-1)
			printf("%d", g.vertices[i].id);
		else
			printf("%d,", g.vertices[i].id);
	}
	printf("],edges:[");

	printf("]}\n");
	return;
}

struct basicgraph *graph2basicgraph(struct graph *g){
	struct basicgraph *h = malloc(sizeof(struct basicgraph));
	h->vlen = g->vlen;
	unsigned int *vertices = malloc(sizeof(unsigned int)*h->vlen);
	unsigned int ecount = 0, k=0;
	for(int i=0;i<g->vlen;i++){
		ecount += g->vertices[i].nlen;
		vertices[i] = g->vertices[i].id;
	}
	h->elen = ecount;
	struct basicedge *edges= malloc(sizeof(struct basicedge)*ecount);
	for(int i=0;i<g->vlen;i++){
		for(int j=0;j<g->vertices[i].nlen;j++){
			edges[k].initial = g->vertices[i].id;
			edges[k].final = g->vertices[i].neighbors[j]->id;
			k++;
		}
	}
	h->vertices = vertices;
	h->edges = edges;
	return h;
}

void deletebasicgraph(struct basicgraph *g){
	free(g->vertices);
	free(g->edges);
	free(g);
	return;
}

void printbasicgraphJSON(struct basicgraph g){

	//char buf[16384];

	printf("HTTP/1.0 200 OK\r\n");
	printf("Server: Lem's Custom Web Server\r\n");
	printf("Connection: close\r\n");
	//printf("Content-Length: %d\r\n\r\n", 0);
	printf("Content-Type: application/json\r\n\r\n");


	printf("{vertices:[");
	for(int i=0;i<g.vlen;i++){
		if(i==g.vlen-1)
			printf("%d", g.vertices[i]);
		else
			printf("%d,", g.vertices[i]);
	}
	printf("],edges:[");
	for(int i=0;i<g.elen;i++){
		if(i==g.elen-1)
			printf("[%d,%d]", g.edges[i].initial, g.edges[i].final);
		else
			printf("[%d,%d],", g.edges[i].initial, g.edges[i].final);
	}
	printf("]}\r\n");

	/*
	sprintf(buf, "HTTP/1.0 200 OK\r\n");
	sprintf(buf, "%sServer: Lem's Custom Web Server\r\n", buf);
	sprintf(buf, "%sConnection: close\r\n", buf);
	sprintf(buf, "%sContent-Length: %d\r\n", buf, 0);
	*/
	//sprintf(buf, "%sContent-Type: %s\r\n\r\n", buf, typeheader);
	//sprintf(buf, "%sContent-Type: application/json\r\n\r\n", buf);

	/*
	sprintf(buf, "{vertices:[");
	for(int i=0;i<g.vlen;i++){
		if(i==g.vlen-1)
			sprintf(buf, "%s%d", buf, g.vertices[i]);
		else
			sprintf(buf, "%s%d,", buf, g.vertices[i]);
	}
	sprintf(buf, "%s],edges:[", buf);
	for(int i=0;i<g.elen;i++){
		if(i==g.elen-1)
			sprintf(buf, "%s[%d,%d]", buf, g.edges[i].initial, g.edges[i].final);
		else
			sprintf(buf, "%s[%d,%d],", buf, g.edges[i].initial, g.edges[i].final);
	}
	sprintf(buf, "%s]}\n", buf);
	rio_writen(STDOUT_FILENO, buf, strlen(buf));
	*/
	return;
}
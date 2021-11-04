#include "graph.h"

int main(int argc, char **argv){
	struct graph *g;
	if(argc!=3){
		printf("\nTwo arguments required for graph/main.\n\n");
	}
	int n=atoi(argv[1]);

	switch (atoi(argv[2])){
		case 0:
			g = n_cycle(n);
			break;
		case 1:
			g = n_wheel(n);
			break;
		case 2:
			g = n_complete(n);
			break;
		default:
			return 0;
	}
	struct basicgraph *h = graph2basicgraph(g);
	printbasicgraphJSON(*h);
	deletebasicgraph(h);
	deletegraph(g);
	return 0;
}

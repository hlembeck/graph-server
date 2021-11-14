#include "graph2.h"


void handle_get_graph(int n_args, char **args);

/* argv[1] to be a single character for initial switch statement, argv[2] to be single character for secondary switch. argv[3] is integer n */
int main(int argc, char **argv){
	if(4 > argc){
		return -1;
	}
	switch (argv[1][0]) {
		case 'g':
			handle_get_graph(argc, argv);
			break;
		default:
			printf("default\n\n");
	}
	return 0;
}

void handle_get_graph(int n_args, char **args){
	graph1 *g,*h,*k;
	char *json;
	unsigned int n = atoi(args[3]);
	switch(args[2][0]){
		/* k comes from notation K_n for complete graph on n vertices */
		case 'k':
			g = n_complete1(n);
			break;
		case 'c':
			g = increasing_n_cycle1(n);
			break;
		case 's':
			g = inward_n_star1(n);
	}
	json = graph1_JSON(*g);
	

	printf("HTTP/1.0 200 OK\r\n");
	printf("Server: Lem's Custom Web Server\r\n");
	printf("Connection: close\r\n");
	printf("Content-Length: %ld\r\n", strlen(json));
	printf("Content-Type: application/json\r\n\r\n");
	printf("%s", json);




	delete_graph1(g);
	return;
}
#include "graph1.h"


void handle_get_graph(int n_args, char **args);
void handle_operation(char *data);

// [\"+\",[{\"vertices\":2,\"edges\":[[0,1]]},{\"vertices\":2,\"edges\":[[0,1]]}]]

/* argv[1] to be a single character for initial switch statement, argv[2] to be single character for secondary switch. argv[3] is integer n */
int main(int argc, char **argv){
	if(argc<2){
		return -1;
	}
	switch (argv[1][0]) {
		case 'g':
			handle_get_graph(argc, argv);
			break;
		case 'o':
			handle_operation(argv[argc-1]);
			break;
		default:
			break;
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

void handle_operation(char *data){
	JSON_Object inputJSON = parseJSON(data);
	char operation = inputJSON.obj[0].value.str[0];
	graph1 *graphs[inputJSON.obj[1].value.len];
	graph1 *result = NULL;
	for(int i=0;i<inputJSON.obj[1].value.len;i++){
		graphs[i] = graph1_from_JSON_Object(inputJSON.obj[1].value.arr[i]);
	}

	switch(operation){
		case 'c':
			result = complement1(*graphs[0]);
			break;
		case '^':
			result = transpose1(*graphs[0]);
			break;
		case '+':
			result = sum1(*graphs[0],*graphs[1]);
			break;
		case 'U':
			result = union1(*graphs[0],*graphs[1]);
			break;
		case '&':
			//result = intersect1(*graphs[0],*graphs[1]);
			break;
		case '*':
			//product
			break;
	}
	print_response_JSON(parseJSON(graph1_JSON(*result)));
	for(int i=0;i<inputJSON.obj[1].value.len;i++){
		delete_graph1(graphs[i]);
	}
	delete_graph1(result);
	return;
}
#include "json.h"

int main(int argc, char **argv){
	if(argc != 2){
		printf("Run with an argument that is a JSON-formatted string.\n");
		return 0;
	}
	JSON_Object parsedInput = parseJSON(argv[1]);
	printf("\n");
	printJSON(parsedInput);
	printf("\n");
	return 0;
}
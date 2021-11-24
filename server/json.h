#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/*
This file defines a structure (JSON_Node) to represent a JSON object. This allows for easy parsing of JSON from a webclient, as well as easy compiling into JSON format for transport to the client.

A JSON string is easily represented in the form of a tree. The JSON_Node structure contains local information for a node, as well as its data. The JSON_Data structure then defines the type of associated JSON_Node, and (in the case of the node being an object '{...}'), an array of names.
*/

typedef struct JSON_Object{
	char type; // '{':Object , '[':Array , 'n':number , 's':string , 't':true , 'f':false , '\0':null
	union{
		char *str;
		char *num;
		struct JSON_Object *arr;
		struct KeyValue *obj;
	};
	int len; //length of array in union
} JSON_Object;

typedef struct KeyValue{
	char *key;
	JSON_Object value;
} KeyValue;

//Returns root node of parsed JSON tree from input[len] if successful. Otherwise returns NULL.
//input assumed to have no whitespace.
JSON_Object parseJSON(char *input);

KeyValue *getobject(char *input, int *len);
KeyValue getpair(char *input);
char *getstring(char *input, int *len);
JSON_Object *getarray(char *input, int *len);
char *getnumber(char *input, int *len);

void printJSON(JSON_Object input);
void string_from_JSON(JSON_Object input, char *buf);
void print_response_JSON(JSON_Object body);

void free_JSON_Object(JSON_Object json);
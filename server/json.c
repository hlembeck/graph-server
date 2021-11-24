#include "json.h"

JSON_Object parseJSON(char *input){
	JSON_Object result;
	if(!input)
		return result;
	int len = -1;
	switch (input[0]){
		case '{':
			result.type = '{';
			result.obj = getobject(&input[0], &len);
			result.len = len;
			break;
		case '[':
			result.type = '[';
			result.arr = getarray(&input[0], &len);
			result.len = len;
			break;
		case '"':
			result.type = 's';
			result.str = getstring(&input[1], &len);
			result.len = len;
			break;
		case 'n':
			result.type = '\0';
			break;
		case 't':
			result.type = 't';
			break;
		case 'f':
			result.type = 'f';
			break;
		default:
			result.type = 'n';
			result.num = getnumber(&input[0], &len);
			result.len = len;
			break;
	}
	return result;
}

KeyValue *getobject(char *input, int *len){
	KeyValue *result;
	int counter = 1;
	(*len) = 1;
	int curr = 0;
	int start = 1;
	int state = 0;
	while(counter){
		curr++;
		switch(input[curr]){
			case '\0':
				return NULL;
			case ',':
				if(counter==1)
					(*len)++;
				break;
			case '{':
				counter++;
				break;
			case '}':
				counter--;
				break;
			case '[':
				counter++;
				break;
			case ']':
				counter--;
				break;
		}
	}
	counter = 0;
	result = malloc(sizeof(KeyValue)*(*len));
	for(int i=1;i<curr;i++){
		if(input[i]==',' && state==0){
			result[counter] = getpair(&input[start]);
			start = i+1;
			counter++;
		}
		if(input[i]=='{' || input[i]=='[')
			state++;
		else if(input[i]=='}' || input[i]==']')
			state--;
	}
	result[counter] = getpair(&input[start]);
	return result;
}

//Called from getobject for each key/value pair. 
KeyValue getpair(char *input){
	KeyValue result;
	char *key;
	int i = 0;
	while(input[i]!=':'){
		if(input[i]=='\0'){
			printf("Input is not of JSON format.\n");
			return result;
		}
		i++;
	}
	key = malloc(sizeof(char)*(i+1));
	memcpy(key,input,i);
	key[i] = '\0';
	result.key = key;
	input = &input[i+1];
	result.value = parseJSON(input);
	return result;
}


char *getstring(char *input, int *len){
	char *result;
	char curr = input[0];
	*len = 0;
	while(curr && curr!='"'){
		curr=input[++(*len)];
	}
	if(curr=='\0'){
		*len = -1;
		return NULL;
	}
	result = malloc(sizeof(char)*((*len)+1));
	memcpy(result,input,*len);
	result[*len] = '\0';
	return result;
}

JSON_Object *getarray(char *input, int *len){
	JSON_Object *result;
	int curr=0;
	*len=1;
	int counter = 1;
	int start = 1;
	int state = 0;
	while(counter){
		curr++;
		switch(input[curr]){
			case '\0':
				return NULL;
			case ',':
				if(counter==1)
					(*len)++;
				break;
			case '[':
				counter++;
				break;
			case ']':
				counter--;
				break;
			case '{':
				counter++;
				break;
			case '}':
				counter--;
				break;
		}
	}
	counter = 0;
	result = malloc(sizeof(JSON_Object)*(*len));
	for(int i=1;i<curr;i++){
		if(input[i]==',' && state==0){
			result[counter] = parseJSON(&input[start]);
			start = i+1;
			counter++;
		}
		if(input[i]=='{' || input[i]=='[')
			state++;
		else if(input[i]=='}' || input[i]==']')
			state--;
	}
	result[counter] = parseJSON(&input[start]);
	return result;
}

char *getnumber(char *input, int *len){
	char *result;
	char curr=input[0];
	*len=0;
	while(curr!='\0' && curr!= ',' && curr!=']' && curr!='}'){
		curr=input[++(*len)];
	}
	result = malloc(sizeof(char)*((*len)+1));
	memcpy(result,input,*len);
	result[*len] = '\0';
	return result;
}

void printJSON(JSON_Object input){
	switch(input.type){
		case '{':
			printf("{");
			for(int i=0;i<input.len;i++){
				printf("%s:",input.obj[i].key);
				printJSON(input.obj[i].value);
				if(i!=input.len-1)
					printf(",");
			}
			printf("}");
			break;
		case '[':
			printf("[");
			for(int i=0;i<input.len;i++){
				printJSON(input.arr[i]);
				if(i!=input.len-1)
					printf(",");
			}
			printf("]");
			break;
		case 's':
			printf("\"%s\"",input.str);
			break;
		case 'n':
			printf("%s",input.num);
			break;
		case 't':
			printf("true");
			break;
		case 'f':
			printf("false");
			break;
		case '\0':
			printf("null");
			break;
	}
	return;
}

void string_from_JSON(JSON_Object input, char *buf){
	switch(input.type){
		case '{':
			sprintf(buf,"%s{", buf);
			for(int i=0;i<input.len;i++){
				sprintf(buf,"%s%s:", buf, input.obj[i].key);
				string_from_JSON(input.obj[i].value, buf);
				if(i!=input.len-1)
					sprintf(buf,"%s,", buf);
			}
			sprintf(buf,"%s}",buf);
			break;
		case '[':
			sprintf(buf,"%s[", buf);
			for(int i=0;i<input.len;i++){
				string_from_JSON(input.arr[i], buf);
				if(i!=input.len-1)
					sprintf(buf,"%s,", buf);
			}
			sprintf(buf,"%s]", buf);
			break;
		case 's':
			sprintf(buf,"%s\"%s\"", buf, input.str);
			break;
		case 'n':
			sprintf(buf,"%s%s", buf, input.num);
			break;
		case 't':
			sprintf(buf,"%strue", buf);
			break;
		case 'f':
			sprintf(buf,"%sfalse", buf);
			break;
		case '\0':
			sprintf(buf,"%snull", buf);
			break;
	}
	return;
}

void print_response_JSON(JSON_Object body){
	char buf[USHRT_MAX*2];
	memset(buf, '\0', USHRT_MAX*2);
	string_from_JSON(body, buf);
	printf("HTTP/1.0 200 OK\r\n");
	printf("Server: Lem's Custom Web Server\r\n");
	printf("Connection: close\r\n");
	printf("Content-Length: %ld\r\n", strlen(buf));
	printf("Content-Type: application/json\r\n\r\n");
	printf("%s", buf);
	return;
}

void free_JSON_Object(JSON_Object json){
	switch(json.type){
		case 's':
			free(json.str);
			break;
		case 'n':
			free(json.num);
			break;
		case '[':
			for(int i=0;i<json.len;i++){
				free_JSON_Object(json.arr[i]);
			}
			free(json.arr);
			break;
		case '{':
			for(int i=0;i<json.len;i++){
				free(json.obj[i].key);
				free_JSON_Object(json.obj[i].value);
			}
			free(json.obj);
			break;
	}
	return;
}
#include "http.h"


HTTP_Header *parseheader(char *header){
	HTTP_Header *result = malloc(sizeof(HTTP_Header));
	
	unsigned short len = 0;
	while(header[len] != ' '){
		len++;
	}
	char *name = malloc(len);
	memcpy(name, header, len-1);
	name[len-1] = '\0';
	result->header_name = name;
	char *data = malloc(strlen(header+len));
	strcpy(data, header+len+1);
	int i;
	if((i=strlen(header)-len-1)>0){
		data[i-1] = '\0';
	}
	result->header_data = data;
	return result;
}

HTTP_Request *parserequest(rio_t *rio){
	HTTP_Request *result = malloc(sizeof(HTTP_Request));
	char line[MAXLINE];
	HTTP_Header **headers = malloc(sizeof(char *)*MAXHEADERS);
	rio_readlineb(rio, line, MAXLINE);
	parse_request_line(line, result);
	unsigned short i = 0;
	while(rio_readlineb(rio, line, MAXLINE) > 0){
		if(strcmp(line, "\r\n") == 0)
			break;
		headers[i] = parseheader(line);
		i++;
	}
	result->headers = headers;
	result->hlen = i;
	return result;
}

void parse_request_line(char *line, HTTP_Request *hset){
	unsigned short pos, len = 0;
	while(line[len] != ' '){
		len++;
	}
	char *method = malloc(len+1);
	memcpy(method, line, len);
	method[len] = '\0';
	hset->method = method;
	pos=len+1;

	while(line[pos] != ' '){
		pos++;
	}
	char *uri = malloc(pos-len);
	memcpy(uri, line+len+1, pos-len-1);
	uri[pos-len-1] = '\0';
	hset->uri = uri;
	pos++;

	char *version = malloc(strlen(line+pos)+1);
	strcpy(version, line+pos);
	version[strlen(line)-pos-1] = '\0';
	hset->version = version;

	setquery(hset, uri);


	return;
}

void freeheader(HTTP_Header *h){
	free(h->header_name);
	free(h->header_data);
	free(h);
	return;
}

void freerequest(HTTP_Request *hset){
	free(hset->method);
	free(hset->uri);
	free(hset->version);
	for(int i=0;i<hset->hlen;i++){
		free(hset->headers[i]);
	}
	for(int i=0;i<hset->qlen;i++){
		free(hset->query[i]);
	}
	free(hset->headers);
	free(hset);
}

void printrequest(HTTP_Request *hset){
	printf("\n ---- Printing Request ---- \n");
	printf("\n%s %s %s\n", hset->method, hset->uri, hset->version);
	for(int i=0;i<hset->hlen;i++){
		printf("%s: %s\n", hset->headers[i]->header_name, hset->headers[i]->header_data);
	}
	printf("\n -------------------------- \n\n");
	print_parsed_uri(hset);
	return;
}

void writeheaders(int fd, char *filename, int filesize){
	char buf[MAXLINE], typeheader[MAXLINE];
	sprintf(buf, "HTTP/1.0 200 OK\r\n");
	sprintf(buf, "%sServer: Lem's Custom Web Server\r\n", buf);
	sprintf(buf, "%sConnection: close\r\n", buf);
	sprintf(buf, "%sContent-Length: %d\r\n", buf, filesize);
	ftype(filename, typeheader);
	sprintf(buf, "%sContent-Type: %s\r\n\r\n", buf, typeheader);
	printf("Response Headers:\n");
	printf("%s",buf);
	rio_writen(fd, buf, strlen(buf));
	return;
}

void setquery(HTTP_Request *hset, char *uri){
	char *path;
	char **query = malloc(sizeof(char *)*MAXARGS);
	unsigned short start, i=0, count=0;
	while(uri[i]!='\0'){
		if(uri[i]=='?'){
			path = malloc(i);
			memcpy(path, uri, i-1);
			path[i] = '\0';
			hset->path = path;
			count++;
			start=i++;
			continue;
		}
		if(uri[i]=='&'){
			char *arg = malloc(i-start);
			memcpy(arg, uri+start, i-start-1);
			arg[i-start-1] = '\0';
			i++;
			count++;
			continue;
		}
		i++;
	}
	if(count == 0){
		path = malloc(strlen(uri));
		strcpy(path, uri);
	}
	hset->path = path;
	hset->query = query;
	hset->qlen = count;
	return;
}

void print_parsed_uri(HTTP_Request *hset){
	printf("\n ---- Printing Parsed Uri ---- \n");
	printf("\nPath:\n    %s\n\nArguments:\n", hset->path);
	for(int i=0;i<hset->qlen;i++){
		printf("    %s\n", hset->query[i]);
	}
	printf("\n ----------------------------- \n\n");
	return;
}
#include "../file-handling/fhandling.h"

#define MAXLINE 16384
#define MAXHEADERS 64
#define MAXARGS 128

typedef struct HTTP_Header{
	char *header_name;
	char *header_data;
} HTTP_Header;

typedef struct HTTP_Request{
	char *method;
	char *uri;
	char *path;
	char **query;
	unsigned short qlen;
	unsigned short hlen;
	char *version;
	char *body;
	HTTP_Header **headers;
} HTTP_Request;

HTTP_Header *parseheader(char *header);
HTTP_Request *parserequest(rio_t *rio);
void parse_request_line(char *line, HTTP_Request *hset);
void printrequest(HTTP_Request *hset);
void writeheaders(int fd, char *filename, int filesize);
void setquery(HTTP_Request *hset, char *uri);
void print_parsed_uri(HTTP_Request *hset);

/* Free header_name, header_data */
void freeheader(HTTP_Header *h);
void freerequest(HTTP_Request *hset);
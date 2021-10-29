#include "csapp.h"


/* Must use port >1024 if not root permissions */
int main(int argc, char **argv){
	int clientfd;
	char *host, *port, buf[MAXLINE];
	rio_t rio;
	
	if(argc != 3){
		printf("Enter exactly two command line arguments. The first is host, second is port.");
		return 0;
	}
	host = argv[1];
	port = argv[2];

	clientfd = open_clientfd(host, port);
	if(clientfd == -1){
		printf("Failed to connect.\n");
		return 0;
	}
	rio_readinitb(&rio, clientfd);

	while(fgets(buf, MAXLINE, stdin) != NULL){
		rio_writen(clientfd, buf, strlen(buf));
		rio_readlineb(&rio, buf, MAXLINE);
		fputs(buf, stdout);
	}
	close(clientfd);

	return 0;
}
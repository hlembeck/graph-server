#include "csapp.h"
void echo(int connfd){
	size_t n;
	char buf[MAXLINE];
	rio_t rio;

	rio_readinitb(&rio, connfd);
	while((n=rio_readlineb(&rio, buf, MAXLINE)) != 0){
		printf("server received %d bytes \n", (int)n);
		rio_writen(connfd, buf, n);
	}
}

int main(int argc, char **argv){
	int listenfd, connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	char client_hostname[MAXLINE], client_port[MAXLINE];

	if(argc != 2){
		printf("Enter the port as an argument.");
		return 0;
	}

	listenfd = open_listenfd(argv[1]);
	while(1){
		clientlen = sizeof(struct sockaddr_storage);
		connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		getnameinfo((struct sockaddr *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
		printf("Connected to (%s, %s)\n", client_hostname, client_port);
		echo(connfd);
		close(connfd);
	}
	return 0;
}
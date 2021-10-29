#include "serverwrappers.h"
#include "fhandling.h"

void handlereq(int connfd);
void servepage(int fd, char *filename, int filesize);

int main(int argc, char **argv){
	if(argc != 2){
		printf("Please enter the port number for listening, as a command line argument.\n");
		return -1;
	}

	int listenfd, connfd;
	char hostname[MAXHP], port[MAXHP];
	struct sockaddr_storage clientaddr;
	socklen_t clientlen = sizeof(clientaddr);

	listenfd = open_listenfd(argv[1]);
	char *test = "test.none";
	char res[10];
	//memset(res, '\0', 10);
	final2char(test, '.', res);
	printf("%s\n", res);

	while(1){
		connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		getnameinfo((struct sockaddr *)&clientaddr, clientlen, hostname, MAXHP, port, MAXHP, 0);
		printf("Accepted connection from (%s,%s).\n", hostname, port);
		handlereq(connfd);
		close(connfd);
	}
}

void handlereq(int fd){
	struct stat sbuf;
	char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
	char filename[MAXLINE];
	rio_t rio;

	rio_readinitb(&rio, fd);
	rio_readlineb(&rio, buf, MAXLINE);
	printf("Request headers:\n");
	printf("%s", buf);
	sscanf(buf, "%s %s %s", method, uri, version);

	if(strcmp(uri,"/")==0){
		strcpy(filename, "public/index.html");
	}

	if(strcmp(uri,"/favicon.ico")==0){
		strcpy(filename, "public/favicon.ico");
		//return;
	}

	if(stat(filename, &sbuf)<0){
		printf("Error opening file: %i", errno);
		return;
	}
	printf("Opened file %s.\n", filename);
	printf("st_mode: %o\n", sbuf.st_mode);
	if(strcmp(filename,"public/favicon.ico")==0){
		return;
	}
	servepage(fd, filename, sbuf.st_size);
	return;
}

void servepage(int fd, char *filename, int filesize){
	int srcfd;
	char *srcp;
	char buf[MAXBUF];
	sprintf(buf, "HTTP/1.0 200 OK\r\n");
	sprintf(buf, "%sServer: Custom Web Server\r\n", buf);
	sprintf(buf, "%sConnection: closed\r\n", buf);
	sprintf(buf, "%sContent-Length: %d\r\n", buf, filesize);
	sprintf(buf, "%sContent-Type: text/html\r\n\r\n", buf);
	rio_writen(fd, buf, strlen(buf));
	printf("Response Headers:\n");
	printf("%s",buf);

	srcfd = open(filename, O_RDONLY, 0);
	srcp = mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
	close(srcfd);
	rio_writen(fd, srcp, filesize);
	printf("%s\n", srcp);
	munmap(srcp, filesize);
	return;
}
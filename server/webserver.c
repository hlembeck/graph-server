#include "serverwrappers.h"
#include "controlwrappers.h"
#include "http.h"

void handlereq(int connfd);
void servestatic(int fd, char *filename, int filesize);
void serveapplication(int fd, char *filename, int filesize);
void serveimage(int fd, char *filename, int filesize);
void servedynamic(int fd, char *filename, int filesize);
void writeheader(int fd, char *filename, int filesize);
void servenonfile(int fd, char *uri, rio_t *rio, char *method);
void parse_request(int fd, rio_t *rio);
void handleGET(HTTP_Request *hset, int fd);
void handlePOST(HTTP_Request *hset, int fd);

int main(int argc, char **argv){
	pid_t pid;
	if(argc != 2){
		printf("Please enter the port number for listening, as a command line argument.\n");
		return -1;
	}
	int listenfd, connfd;
	char hostname[MAXHP], port[MAXHP];
	struct sockaddr_storage clientaddr;
	socklen_t clientlen = sizeof(clientaddr);

	listenfd = open_listenfd(argv[1]);

	while(1){
		ReapChildren();
		connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		if(Fork()==0){
			getnameinfo((struct sockaddr *)&clientaddr, clientlen, hostname, MAXHP, port, MAXHP, 0);
			printf("Accepted connection from (%s,%s).\n", hostname, port);
			handlereq(connfd);
			close(connfd);
			exit(0);
		}
		close(connfd);
	}
}

void handlereq(int fd){
	struct stat sbuf;
	char buf[MAXLINE];
	char filename[MAXLINE];
	int ftype;
	rio_t rio;

	/* Web files (.html, .css, .js, etc.) are stored in web folder */
	strcpy(filename, "web");
	rio_readinitb(&rio, fd);
	HTTP_Request *hset = parserequest(&rio);
	printrequest(hset);
	if(strcmp(hset->method,"GET")==0){
		handleGET(hset, fd);
	}
	else{
		handlePOST(hset, fd);
	}
	freerequest(hset);
	return;
}

void handleGET(HTTP_Request *hset, int fd){
	struct stat sbuf;
	char filename[MAXLINE];
	/* Web files (.html, .css, .js, etc.) are stored in web folder */
	strcpy(filename, "web");
	if(strcmp(hset->uri,"/") == 0)
		strcat(filename, "/index.html");
	else
		strcat(filename, hset->uri);

	if(stat(filename, &sbuf)<0){
		printf("Error opening file: %i\n", errno);
		return;
	}
	printf("Opened file %s.\n", filename);
	printf("st_mode: %o\n", sbuf.st_mode);
	servestatic(fd, filename, sbuf.st_size);
}

void handlePOST(HTTP_Request *hset, int fd){
	//printf("\n\n'%s'\n\n", hset->body);
	char **argv = malloc(sizeof(char *)*(hset->qlen+2));
	argv[0] = "../Graph/server_interface";
	//argv[0] = "../graph/main";
	argv[hset->qlen+1] = NULL;
	for(int i=0;i<hset->qlen;i++){
		argv[i+1] = hset->query[i];
	}
	if(Fork()==0){
		dup2(fd, STDOUT_FILENO);
		//if(execve("../graph/main", argv, NULL)<0){
		if(execve("../Graph/server_interface", argv, NULL)<0){
			printf("Failed execve: %d\n\n", errno);
			free(argv);
			free(hset);
			exit(-1);
		}
	}
	wait(NULL);
	free(argv);
	return;
}

void servestatic(int fd, char *filename, int filesize){
	int srcfd;
	char *srcp;
	char buf[MAXBUF];

	writeheaders(fd, filename, filesize);

	srcfd = open(filename, O_RDONLY, 0);
	srcp = mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
	close(srcfd);
	rio_writen(fd, srcp, filesize);
	munmap(srcp, filesize);
	return;
}

void servenonfile(int fd, char *uri, rio_t *rio, char *method){
	return;
}

void servedynamic(int fd, char *filename, int filesize){
	return;
}
#include "serverwrappers.h"

int open_listenfd(char *port){
	struct addrinfo hints, *listp, *p;
	int listenfd, err, i=0, optval=1;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
	hints.ai_flags |= AI_NUMERICSERV;

	if((err=getaddrinfo(NULL, port, &hints, &listp))!=0){
		printf("getaddrinfo returned error %s from %i\n", gai_strerror(err), err);
	}

	for(p = listp; p; p=p->ai_next){
		printf("ITERATION %i\n", i);
		if((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) <0){
			i++;
			continue;
		}
		printf("created socket descriptor %i on iteration %i.\n", listenfd, i);
		/* configure so server listens immediately without delay */
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

		if(bind(listenfd, p->ai_addr, p->ai_addrlen) == 0){
			printf("bound on iteration %i.\n", i);
			break;
		}
		printf("failed to bind: %d\n", errno);
		close(listenfd);
		i++;
	}

	freeaddrinfo(listp);
	if(!p){
		return -1;
	}
	if(listen(listenfd, LISTENQ) < 0){
		printf("failed to listen\n");
		close(listenfd);
		return -1;
	}
	return listenfd;
}
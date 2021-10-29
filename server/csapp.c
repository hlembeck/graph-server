#include "csapp.h"

int open_clientfd(char *hostname, char *port){
	int clientfd, err;
	struct addrinfo hints, *listp, *p;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV;
	hints.ai_flags |= AI_ADDRCONFIG;
	if((err=getaddrinfo(hostname, port, &hints, &listp))!=0){
		printf("getaddrinfo returned error %s from %i\n", gai_strerror(err), err);
	}

	for(p = listp; p; p=p->ai_next){
		if((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) <0){
			continue;
		}
		printf("created socket descriptor %i\n", clientfd);
		if(connect(clientfd, p->ai_addr, p->ai_addrlen) != -1){
			break; /*Success*/
		}
		printf("failed to connect.\n");
		close(clientfd);
	}

	freeaddrinfo(listp);
	if(!p){
		return -1;
	}
	return clientfd;
}


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

ssize_t rio_writen(int fd, void *usrbuf, size_t n){
	size_t nleft = n;
	size_t nwritten;
	char *bufp = usrbuf;

	while(nleft>0){
		if((nwritten = write(fd, bufp, nleft)) <= 0){
			if(errno == EINTR){
				nwritten = 0;
			}
			else{
				return -1;
			}
		}

		nleft -= nwritten;
		bufp += nwritten;
	}
	return n;
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n){
	int cnt;

	while(rp->rio_cnt <= 0){
		rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
		if(rp->rio_cnt < 0){
			if(errno != EINTR){
				return -1;
			}
		}
		else if(rp->rio_cnt == 0){
			return 0;
		}
		else{
			rp->rio_bufptr = rp->rio_buf;
		}
	}

	cnt = n;
	if(rp->rio_cnt < n){
		cnt = rp->rio_cnt;
	}
	memcpy(usrbuf, rp->rio_bufptr, cnt);
	rp->rio_bufptr += cnt;
	rp->rio_cnt -= cnt;
	return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen){
	int n, rc;
	char c, *bufp = usrbuf;

	for(n=1; n<maxlen; n++){
		if((rc = rio_read(rp, &c, 1)) == 1){
			*bufp++ = c;
			if(c=='\n'){
				n++;
				break;
			}
		}
		else if(rc ==0){
			if(n==1){
				return 0;
			}
			break;
		}
		else{
			return -1;
		}
	}
	*bufp = 0;
	return n-1;
}

void rio_readinitb(rio_t *rp, int fd){
	rp->rio_fd = fd;
	rp->rio_cnt = 0;
	rp->rio_bufptr = rp->rio_buf;
	return;
}
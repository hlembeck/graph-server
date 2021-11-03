#include "fhandling.h"

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

void initial2char(char *in, char stop, char *out){
	for(int i=0; i<strlen(in); i++){
		if(stop == in[i])
			return;
		out[i] = in[i];
	}
	return;
}

void str_reverse(char *in){
	int len = strlen(in);
	char out[len];
	for(int i=0;i<len;i++){
		out[i]=in[len-i-1];
	}
	memcpy(in, out, len);
	return;
}

/* Replaces initial segment of out by the maximal final segment of in that does not contain stop as a character. */
void final2char(char *in, char stop, char *out){
	int len = strlen(in);
	for(int i=0; i<len; i++){
		if(stop == in[len-i-1]){
			str_reverse(out);
			return;
		}
		out[i] = in[len-i-1];
	}
	str_reverse(out);
	return;
}

void ftype(char *filename, char *out){
	char fext[RIO_BUFSIZE];
	final2char(filename, '.', fext);

	/* Content-Type: text */
	if(strcmp(fext, "html")==0){
		strcpy(out, "text/html");
	}
	//printf("\ntest1\n");
	else if(strcmp(fext, "css")==0){
		strcpy(out, "text/css");
	}
	else if(strcmp(fext, "csv")==0){
		strcpy(out, "text/csv");
	}
	else if(strcmp(fext, "xml")==0){
		strcpy(out, "text/xml");
	}

	/* Content-Type: application */
	else if(strcmp(fext, "js")==0){
		strcpy(out, "application/json");
	}
	else if(strcmp(fext, "json")==0){
		strcpy(out, "application/json");
	}
	else{
		strcpy(out, "text/plain");
	}
	memset(fext, '\0', sizeof(fext));
	/* File extension not handled */
	return;
}

void read_http_header(rio_t *rio){
	char buf[MAXLINE];
	ssize_t rlen = rio_readlineb(rio, buf, MAXLINE);
	while(rlen > 0){
		if(strcmp(buf,"\r\n\0")==0){
			printf("DONE \n");
			break;
		}
		printf("READ %ld BYTES: %s\n", rlen, buf);
		rlen = rio_readlineb(rio, buf, MAXLINE);
	}
	return;
}
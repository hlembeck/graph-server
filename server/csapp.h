#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

//addrinfo struct is in netdb
#include <netdb.h>

#define RIO_BUFSIZE 8192
#define MAXLINE 2048
#define LISTENQ 0

typedef struct {
	int rio_fd;
	int rio_cnt;
	char *rio_bufptr;
	char rio_buf[RIO_BUFSIZE];
} rio_t;

int open_clientfd(char *hostname, char *port);
int open_listenfd(char *port);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n);
void rio_readinitb(rio_t *rp, int fd);
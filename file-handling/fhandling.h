#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

#include <stdio.h>

#define RIO_BUFSIZE 2048
#define MAXLINE 16384

typedef struct {
	int rio_fd;
	int rio_cnt;
	char *rio_bufptr;
	char rio_buf[RIO_BUFSIZE];
} rio_t;

ssize_t rio_writen(int fd, void *usrbuf, size_t n);
static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n);
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
void rio_readinitb(rio_t *rp, int fd);
void initial2char(char *buf, char stop, char *res);
void str_reverse(char *in);
void final2char(char *buf, char stop, char *res);
void ftype(char *filename, char *out);
void read_http_header(rio_t *rio);
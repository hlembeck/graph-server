#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

//addrinfo struct is in netdb
#include <netdb.h>

#define MAXHP 128 /* HP means "Host/Port" */
#define MAXLINE 8192
#define MAXBUF 2048
#define LISTENQ 0

int open_listenfd(char *port);
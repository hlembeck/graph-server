#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>

pid_t Fork(void);

void ReapChildren(void);
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

pid_t Fork(void){
	pid_t pid;
	if((pid = fork())<0){
		printf("error. \n");
		return -1;
	}
}

void ReapChildren(void){
	int status;
	while(waitpid(-1, &status, WNOHANG) > 0){
		if(WIFEXITED(status))
			printf("Child process exited normally with status %d.\n", WEXITSTATUS(status));
	}
	return;
}
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char **argv, char **envp){
	int fileDescriptor;
	if((fileDescriptor=open("testFile.s", O_RDONLY, 0)) == -1){
		printf("error\n");
		return 1;
	}
	printf("success\n");
	return 0;
}
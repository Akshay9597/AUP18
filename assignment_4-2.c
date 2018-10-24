#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
	int fd;
	char command[256];
	if(argc != 2){
		printf("Please provide one filename only\n");
	}

	fd = open(argv[1],O_RDONLY);
	read(fd,command,255);

	int pid = fork();

	if ( pid == 0 ) {
	        execl("/bin/sh", "sh", "-c", command, (char *) 0);
	}
	wait(NULL);
}

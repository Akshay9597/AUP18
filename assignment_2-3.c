#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
	int fd1,fd2;
	char buf[256];

	fd1=open("in",O_RDWR);
	if(fd1 == -1){
         printf("Error opening file: %s %s\n", "in" , strerror(errno));
         return 1;
    	}

	fd2=open("out",O_RDWR);
	if(fd2 == -1){
         printf("Error opening file: %s %s\n", "out" , strerror(errno));
         return 1;
	}


	close(0);
	dup(fd1);
	close(fd1);

	close(1);
	dup(fd2);
	close(fd2);

	scanf("%s",buf);
	dprintf(2,"read from stdin: %s\n",buf);
	printf("Writing to stdout");
	read(fd2,buf,256);
	dprintf(2,"read from file: %s\n",buf);
	return 0;
}

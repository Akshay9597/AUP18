#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	int fd, i;
        
	fd = open(argv[1],O_CREAT | O_RDWR | O_TRUNC, S_IRUSR|S_IWUSR);
        if(fd == -1) {
                printf("%s",strerror(errno));
                exit(-1);
        }
	
	write(fd,"abcde",5);

	close(fd);

	fd = open(argv[1],O_APPEND|O_WRONLY);
	if(fd == -1) {
                printf("%s",strerror(errno));
                exit(-1);
	}

	lseek(fd,0,SEEK_SET);
	write(fd,"12345",5);

	close(fd);
	return 0;
}

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
	char *delim = "\n";
	char *start;


	mode_t oldmask;
  	printf("Code for kernel < 4.7.x Umask:\t%04o\n",oldmask=umask(S_IRWXG));
	umask(oldmask);

	fd1=open("/proc/self/status",O_RDONLY);
	if(fd1 == -1){
         printf("Error opening file: %s %s\n", "in" , strerror(errno));
         return 1;
    	}

	read(fd1,buf,256);
	strtok(buf,delim);
	start = strtok(NULL,delim);
	printf("Code for kernel > 4.7.x %s\n",start);
	return 0;
}

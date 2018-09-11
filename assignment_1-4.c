#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int fd, i;
	char arr[10], arr1[10];
	fd = open(argv[1],O_CREAT | O_RDWR, S_IRUSR|S_IWUSR);
	if(fd == -1) {
		printf("%s",strerror(errno));
		exit(-1);
	}
	printf("Enter 1st buffer:");
	for(i=0;i<10;i++)
		scanf("%c",&arr[i]);
	printf("\nEnter 2nd buffer:");
	for(i=0;i<10;i++)
		scanf("%c",&arr1[i]);
	write(fd,arr,10);
	lseek(fd,30,SEEK_CUR);
	write(fd,arr1,10);
	close(fd);	
	return 0;
}

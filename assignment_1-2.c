#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int offset_length = atoi(argv[2]);
	char *file_name = argv[1];
	truncate(file_name,offset_length);
}

int truncate(const char *path,off_t len){
        int fd, file_length;
	char *buff,n='\0';
	
	fd = open(path, O_RDONLY);
	if(fd == -1)
		return -1;
	file_length = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	buff = (char *)malloc(file_length);
	read(fd,buff,file_length);
	close(fd);

	if((len > file_length)) {
		fd = open(path, O_WRONLY | O_APPEND);
		if(fd == -1)
			return -1;
		for(int i = 0; i < (len - file_length); i++) {
			write(fd,&n ,1);
		}
		close(fd);	
	} else {
		fd = open(path, O_WRONLY | O_TRUNC);
		if(fd == -1)
			return -1;
		write(fd, buff,len);
		close(fd);	
	}
}

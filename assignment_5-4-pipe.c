 #include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
   
	int fd[2];
	int read_fd, write_fd;
	int pid;               

	if (pipe(fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	read_fd = fd[0];
	write_fd = fd[1];

	pid = fork();
	if (pid == 0) {

		close(read_fd);

		dup2(write_fd,1);
		
		close(write_fd);

		execl("/bin/sh", "sh", "-c", "ls", NULL);

	} else {
		char buf[2048];
		close(write_fd);

		dup2(read_fd,0);

		close(read_fd);

		execl("/bin/sh", "sh", "-c", "wc -l", NULL);

   	 }
}

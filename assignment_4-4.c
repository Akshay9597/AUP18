#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ITERATION 3
int  main(int argc, char *argv[]) {
	int fd1, fd2;
	int  iteration = ITERATION;

	uid_t uid, euid;

	uid = getuid();
	euid = geteuid();

	fd1 = open("./score_file",O_WRONLY);
	setuid(uid);
	if(fd1 == -1)
		printf("Cannot open score_file\n");
	fd2 = open("./player_file",O_WRONLY);
	if(fd2 == -1)
		printf("Cannot open player_file\n");
	setuid(euid);

	while(iteration--){
		int status = write(fd1,"writing to score",17);
		if(status == -1)
			printf("Write failed on score_file\n");
		setuid(uid);
		status = write(fd2,"test",5);
		if(status == -1)
			printf("Write failed on player_file\n");
		setuid(euid);
		printf("Iteration complete\n");
	}
	close(fd1);
	close(fd2);
	
}

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){ 

        pid_t cpid = fork(); 
	if (cpid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
        }
        if (cpid == 0) {
		sleep(2);
		printf("Child: calling exec\n");
		fflush(stdout);
		execl("/bin/sh", "sh", "-c", "sleep 6", (char *) 0);

        } else {            
		pid_t ppgid = 0;
		pid_t mypid = getpid();
		pid_t ppid  = getppid();
		printf("Parent: My pid is %d and my pgid is %d\n", getpid(), getpgid(mypid));
		ppgid = getpgid(ppid);
		printf("Parent: My parent's pid is %d and his pgid is %d\n", ppid, ppgid);
		
		pid_t c_ppgid = 0;
		pid_t oldc_pgid = getpgid(cpid);
		printf("Parent: My child's pid is %d and his pgid is %d\n", cpid, oldc_pgid);
		c_ppgid = getpgid(cpid);
		printf("Parent: Trying to change child pgid to %d\n",ppgid);
		setpgid(cpid, ppgid);  
		printf("Parent: My child's pid is %d and his pgid is %d\n", cpid, getpgid(cpid));

		sleep(4);

		printf("Parent: Trying to change child pgid to %d\n",oldc_pgid);
		setpgid(cpid, oldc_pgid);  
		printf("Parent: My child's pid is %d and his pgid is %d\n", cpid, getpgid(cpid));

                wait(NULL);
                exit(EXIT_SUCCESS);
        }
	
}

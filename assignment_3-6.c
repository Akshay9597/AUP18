#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define ROUNDS 10

int main() {
    struct timeval start_time, end_time;
    float average_getpid_time, average_fork_time;
    pid_t pid_process, main_parent_pid;

    main_parent_pid = getpid();
    average_getpid_time = 0;
    average_fork_time = 0;

    for(int i = 0; i < ROUNDS; i++) {
        gettimeofday(&start_time, NULL);
        pid_process = getpid();
        gettimeofday(&end_time, NULL);
        if(pid_process == main_parent_pid) { 
            average_getpid_time += (end_time.tv_usec - start_time.tv_usec);

            gettimeofday(&start_time, NULL);
            pid_process = fork();
            gettimeofday(&end_time, NULL);

            if(pid_process) { // Calculate only for Parent Process
                average_fork_time += (end_time.tv_usec - start_time.tv_usec);
            }
        }
    }

    if(getpid() == main_parent_pid) {
        printf("Average getpid() time: %f micro secs\n", (average_getpid_time / ROUNDS));
        printf("Average fork() time: %f micro secs\n", (average_fork_time / ROUNDS));
    }
    return 0;
}

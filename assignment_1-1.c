
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]){
    int fd;
    char temp[10];

    if(argc < 2){
        printf("Pass a file path as an argument\n");
        exit(1);
    }

    fd = open(argv[1],O_RDWR);
    if(fd == -1){
         printf("Error opening file: %s %s\n", argv[0] , strerror(errno));
         return 1;
    }
    if(read(fd,temp,10) != 10){
        printf("File size must be greater than 10 bytes.");
        return 1;
    }

    printf("%s\n",temp);
    while(read(fd,temp,1));
    // lseek(fd, 0, SEEK_END);

    if(!write(fd,"hello",5)){
         printf("Error writing file: %s %s\n", argv[0] , strerror(errno));
         return 1;
    }
    close(fd);
}

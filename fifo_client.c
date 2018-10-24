#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
   int client_to_server;
   char *myfifo1 = "./client_to_server_fifo";

   int server_to_client;
   char *myfifo2 = "./server_to_client_fifo";

   char str[BUFSIZ];
   while(1) {
   printf("Input message to server: ");
   scanf("%s", str);


   client_to_server = open(myfifo1, O_WRONLY);
   server_to_client = open(myfifo2, O_RDONLY);
   write(client_to_server, str, sizeof(str));

   sleep(2);
   system("stat ./client_to_server_fifo");
   fflush(stdout);

   perror("Write:"); 

   read(server_to_client,str,sizeof(str));

   perror("Read:"); 

   printf("...received from the server: %s\n",str);
   }
   close(client_to_server);
   close(server_to_client);


   return 0;
}

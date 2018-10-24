#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
   int client_to_server;
   char *myfifo1 = "./client_to_server_fifo";

   int server_to_client;
   char *myfifo2 = "./server_to_client_fifo";

   char buf[BUFSIZ];

   mkfifo(myfifo1, 0666);
   mkfifo(myfifo2, 0666);

   client_to_server = open(myfifo1, O_RDONLY);
   server_to_client = open(myfifo2, O_WRONLY);

   printf("Server ON.\n");

   system("stat ./client_to_server_fifo");
   fflush(stdout);
   while (1)
   {
      sleep(10);
      read(client_to_server, buf, BUFSIZ);
      
      system("stat ./client_to_server_fifo");
      fflush(stdout);

      if (strcmp("exit",buf)==0)
      {
         printf("Server OFF.\n");
         break;
      }

      else if (strcmp("",buf)!=0)
      {
         printf("Received: %s\n", buf);
         printf("Sending back...\n");
         write(server_to_client,buf,BUFSIZ);
      }

      memset(buf, 0, sizeof(buf));
   }

   close(client_to_server);
   close(server_to_client);

   unlink(myfifo1);
   unlink(myfifo2);
   return 0;
}

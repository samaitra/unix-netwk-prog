#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"

int main(void)
{
    char buf[256];
     int num, fd;
   
    mkfifo(FIFO_NAME,0666);
    
    printf("waiting for receiver...\n");
   
   fd = open(FIFO_NAME, O_WRONLY);
     
    printf("Recevier ready :Enter some message\n");
       
       while (gets(buf),!feof(stdin)) 
       {
          if ((num = write(fd, buf, strlen(buf))) == -1)
                   perror("write error");
              else
                  printf("Sender: written %d bytes\n", num);
           }
	 
	 return 0;
    }

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

    printf("Waiting for Sender...\n");
   
    fd = open(FIFO_NAME, O_RDONLY);
    
    printf("Found Sender ready....\n");

    do {
         if ((num = read(fd, buf,256)) == -1)
                  perror("read");
          else {
              buf[num] = '\0';
               printf("Receiver: read %d bytes: \"%s\"\n", num,buf);
              }
       } while (num > 0);
       
       return 0;
}

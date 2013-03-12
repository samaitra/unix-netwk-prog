#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#define FIFO_NAME "myfifo"
#define FIFO_NAME2 "myfifo2"

int main (void){

	char buf[256];
	char pbuf[256];
	int fd,fd2,num,num2;

	mkfifo(FIFO_NAME,0666);
	mkfifo(FIFO_NAME2,0666);

	printf("Waiting for sender ... \n");

	fd = open(FIFO_NAME,O_RDONLY);
    fd2 = open(FIFO_NAME2,O_WRONLY); 
	printf("FOUND Sender READY ... \n");
	do {
         if ((num = read(fd, buf,256)) == -1)
                  perror("read");
          else {
              buf[num] = '\0';
               printf("Receiver: read %d bytes: \"%s\"\n", num,buf);



               int i;
       		   int j=0;
               for(i=0;i<num;i++){

       	       if((isalpha(buf[i]))==1){

       		    pbuf[j]=buf[i];
       		    j++;

       	       }


             } 
              
             if((num2 = write(fd2,pbuf,strlen(pbuf)))== -1){
             	perror("write processed buffer");
             }else{
                  int length = strlen(pbuf);
                  printf("Sender: written %d bytes %s\n", length,pbuf);
            }

	           }
       } while (num > 0);
       
       return 0;

       

}
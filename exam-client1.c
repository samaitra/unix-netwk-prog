#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_NAME "myfifo"
#define FIFO_NAME2 "myfifo2"

int main(void){

char buf[256],pbuf[256];

int num,num2,fd,fd2;

mkfifo(FIFO_NAME,0666);
mkfifo(FIFO_NAME2,0666);



printf("waiting for receiver...\n");
   
   fd = open(FIFO_NAME, O_WRONLY);
   fd2 = open(FIFO_NAME2, O_RDONLY);
     
    printf("Recevier ready :Enter some message\n");
       
       while (gets(buf),!feof(stdin)) 
       {
          if ((num = write(fd, buf, strlen(buf))) == -1){
                   perror("write error");
              }else{
                  printf("Sender: written %d bytes\n", num);


              //do{
           		if ((num2 = read(fd2, pbuf,256))==-1){
                   	perror("read");
                   }
          		   else {
                   		pbuf[num2] = '\0';
                   		printf("Receiver: read %d bytes: \"%s\"\n", num2,pbuf);
              	}
              	  
           //}while(num2>0);
        }





        }

           

	 
	 



	 return 0;
    


    }


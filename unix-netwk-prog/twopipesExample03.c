
// 2-way communication between two  process parent and child using two PIPE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pfd1[2],pfd2[2],data, retval, status,n;
    pid_t pid;
    char buf[256];
    pipe(pfd1);                  /* Create 2 pipes */
    pipe(pfd2);

    pid = fork();                   /* Create child */

    if (pid == 0) {        //child
        close(pfd1[1]);             
        close(pfd2[0]);    
      printf("Child Process... \n");
	n=read(pfd1[0],buf,strlen(buf)); buf[n]='\0';
	printf("Child recevied %d bytes from parent: %s\n",n,buf);
	n=write(pfd2[1],buf,strlen(buf));
        printf("Child writen %d bytes \n",n);//strlen(buf));
      sleep(4);
     exit(0); 
    }
   else
    if (pid > 0) {             /* Parent */
        close(pfd1[0]);
  	  close(pfd2[1]); 
      printf("Parent Process... \n"); 
	printf("Enter Message \n");
	gets(buf); //scanf("%s",buf);
	write(pfd1[1],buf,strlen(buf));
	printf("Parent sent %d bytes data to child :%s \n",strlen(buf),buf);
	n=read(pfd2[0],buf,strlen(buf)); buf[n]='\0';
	printf("Parent Received %d byets of data :%s \n",n,buf);
      }
    wait(&status);
    return(0);
}


//Program to create a pipe,put data and read back from it in a single process
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX     256

int main()
{    int n, pid, retval, status;
    int pipefd[2];
    char buf[MAX];

retval = pipe(pipefd);
 if (retval < 0) { 
 	printf("Error in creation of pipe.\n");  
	  exit(1);
	  }
  else  printf("\nPipe created successfuly");

printf("\n Read pipefd[0]=%d, Write pipefd[1]=%d", pipefd[0],pipefd[1]);

 printf("\nEnter any  string\n"); 
       gets(buf);
   n = strlen(buf); 

write(pipefd[1],buf, n); 
   printf("\nWritten to the pipe");
   sleep(2);

 n = read(pipefd[0], buf, MAX);
   buf[n] = '\0';
 
  printf("\nRead  %d bytes from pipe: %s\n", n, buf);
   printf("Process  terminated\n"); 
 exit(0);
  }


//Message passing between two process child and parent using Pipe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX     256
static void sig_chld(int);

int main()
{    int n, pid, retval, status;
    int fd[2];
    char buf[MAX];

signal(SIGCHLD,sig_chld);
signal(SIGINT,sig_chld);

retval = pipe(fd);
 if (retval < 0) { 
         printf("Error in creation of pipe.\n");  
	  exit(1);
	  }

  pid = fork();
 
  if (pid == 0)
	     { printf("This is Child Process.......\n"); 
		 close(fd[0]);
		 printf("Enter the  string\n"); 
	       gets(buf);
	        n = strlen(buf);  // printf("Child Pid = %d\n",getpid()); 
	       printf("Child sending %d bytes to pipe: %s\n \n", n, buf);
	       
	       write(fd[1], buf, n);   sleep(2);
	     }
        else
	  {  printf("This is Parent  Process.......\n"); 
		close(fd[1]);
 		n = read(fd[0], buf, MAX);
	      buf[n] = '\0';
	     printf("Parent read %d bytes from pipe: %s\n", n, buf);
	     sleep(4);
          wait(&status);
	    printf("Now parent terminated\n"); 
 	 } 														    
      exit(0);
  }

static void sig_chld(int signo)
	{  int status;
	 if(signo==SIGCHLD)
	     { printf("SIGCHLD signal catched as Child terminated\n");
	        wait(&status);
	      }
         if(signo==SIGINT)
    	   printf("Ctrl-C signal catched\n");
        }




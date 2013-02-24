//Program to create a new  child process
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
pid_t pid, st;

pid=fork();

 if(pid==0)
	{ printf("\n I am Child process my PID=%d\n",getpid());
	  printf("\nChild process: my parent process Id =%d\n",getppid());
	  exit(0);
	}
 else if(pid>0)
        { printf("\nI am Parent process my PID=%d\n", getpid());
          printf("\n Parent process: my parent process ID=%d\n",getppid());
     	  printf("\n Parent process: my child process ID=%d\n",pid);
         exit(0);
        }
     else 
        printf("\nError as FORK() failed\n");
}



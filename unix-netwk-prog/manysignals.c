//Program to demonstrate how SIGNALs sent by parent to its child process which is catched by child or parent

#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sighup(); 
void sigint();
void sigquit();
void sigchld();


main()
{ int pid;

 signal(SIGCHLD,sigchld);

if ((pid = fork()) < 0) {
      perror("Error:fork");
              exit(1);
          }
			       
 if (pid == 0)
    {  signal(SIGHUP,sighup); 
       signal(SIGINT,sigint);
       signal(SIGQUIT, sigquit);
        for(;;); 
      }
 else 
   { printf("\nPARENT sent :SIGHUP signal\n\n");
       kill(pid,SIGHUP);
      sleep(2); 
     
       printf("\nPARENT sent : SIGINT signal \n\n");
        kill(pid,SIGINT);
      sleep(3); 
     
     printf("\nPARENT: sending SIGQUIT\n\n");
        kill(pid,SIGQUIT);
      sleep(3);
     }
  }


void sighup()
 {  signal(SIGHUP,sighup);
     printf("\nCHILD: I have received a SIGHUP\n");
     }

void sigint()
   { signal(SIGINT,sigint); 
      printf("\nCHILD: I have received a SIGINT\n");
     }

void sigquit()
    { printf("\nCHILD: I have received a SIGQUIT\n"); 
      printf("Myself Killed by My Parent Process\n");
        exit(0);
       }
void sigchld()
{  signal(SIGCHLD,sigchld);
       printf("\nParent Received SIGCHLD: Child terminated\n");
    }


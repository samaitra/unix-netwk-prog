//Program showing use of SIGNAL handler
#include <signal.h>
#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int flag = 0; 

void sig_int(int signo) {
      printf("Pressed ctrl-c");
      printf("\nReceived SIGINT signal %d\n", signo);
      	flag = 1;
     }


void sig_quit(int signo) {
    printf("Pressed ctrl-\\");
     printf("\nReceived SIGQUIT signal %d\n", signo);
             flag = 1;   //  exit(0);
	          }

 int main(void) 
  {  
     if (signal(SIGINT, sig_int) == SIG_ERR) 
          { printf("\n Cannot catch SIGINT");   
   	     exit(1); 
	     }

  signal(SIGQUIT, sig_quit); 

 printf("\nPress ctrl-C or ctrl-\\ to generate a signal... \n"); 

   while(!flag)
        pause(); /* used to sleep until a signal received */
       
        printf("Program Terminating.... \n"); 
         return 0;
 }





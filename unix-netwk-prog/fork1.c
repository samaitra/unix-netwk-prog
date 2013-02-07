//Program showing the use of getpid(),getppid() and return value from fork() call to child and parent
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
main()	
{ pid_t X;
  
 X =fork();

 if(X<0) 
   { printf("\nFORK() call failed\n"); 
     exit(-1); 
     } 
 else if (X == 0)  
     { printf("\n Inside Child Process");
       printf("\nChild Process PID=%d , Parent PPID=%d   ",getpid(),getppid()); 
       printf(" , X=%d",X);
        exit(0); 
       } 
   else 
      { //sleep(3);
       printf("\n\n Inside Parent Process");
       printf("\n Parent Process  PID=%d",getpid());
       printf(" , Parent's PPID=%d   ",getppid());
       printf(" , X=%d \n\n",X);
        exit(0); 
    }	  
  
 }


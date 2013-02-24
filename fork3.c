#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void childdie (int );

main()
{
int temp=30;
signal(SIGCHLD,childdie);
if (!fork())
     { 
	printf("Child : Ist Line::   PPID=%d  PID=%d \n",getppid() ,getpid() );
	temp=10;
	//_exit(0);
	}
   else 
      {  temp=20;
	printf("Parent: 2nd Line: PPID=%d  PID=%d \n ",getppid() ,getpid() );
	wait(NULL);
	}

       printf("Temp=%d\n",temp);
       exit(0);
    }




void childdie (int sno)
{ int status;
 if(sno==SIGCHLD)
    { printf("\nSIGCHLD signal received\n");
     wait(&status);
    }
  else 
    printf("\nSignal Received is: %d\n",sno);
   
}

//Program showing the use of wait() 
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
main()
{
pid_t valpid, st;

if(!fork())
  {
   printf("\nChild proces: %d \n",getpid());
   exit(1);
  }
 else
   { printf("\nParent Process waiting for child to die");
      valpid=wait(&st);
   sleep(4);
   printf("\nParent Process waited for child=%d", valpid);
   printf("\nIn Parent Status of terminated Child process = %d\n",WEXITSTATUS(st));
  }
}


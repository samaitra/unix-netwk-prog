 #include <stdio.h>
 #include <stdlib.h>
  #include <unistd.h>

 int main()
   {
        int pfd[2], cpid,rid;
  
      cpid=fork();
        if (!cpid) {
           printf("New Child Process Created..\n");
           printf(" PID=%d \n",getpid()); // Child PPID=%d\n",getpid(),getppid());
           printf("Child Process Executing....\n");
           printf("Child Process...Terminating..\n");
	   sleep(2);
            } 
   else 
         { printf("In Parent Process ...\n");
	   printf("PID =%d  \n",getpid());  //Parent's PPID= %d \n",getpid(),getppid());
           printf("Parent Process executing\n");  //   Waiting for child Termination....\n");
	sleep(3);
   	rid=waitpid(cpid, 0, 0); 
   printf("Pid of terminated Child:%d\n",rid);
          printf("Parent Process...Terminating..\n");
       }
    }


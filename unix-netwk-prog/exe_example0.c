#include<stdio.h>
#include<unistd.h>
main()
{

int i=20;
printf("Befor Exec() i=%d :  PID=%d \n",i,getpid());

printf("Exec Return value  %d\n",execl("ls","ls","-l",0));//wrong syntax needs execlp() or /bin/ls
       //correct above execl with the execlp() & again run it c output
//printf("%d",execl("ls","ls","-l",(char*)0));
sleep(3);
printf("After  Exec() i=%d\n",i);
}


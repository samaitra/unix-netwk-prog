//Show how to execute a new program (i.e. e2.exe)  using exec() calls
#include<stdio.h>
#include<unistd.h>
main()
{

int i=20;
printf("Befor Exec() i=%d :  PID=%d \n",i,getpid());
sleep(3);
execl("e2.exe","e2.exe",0);
printf("After  Exec() i=%d\n",i);
}


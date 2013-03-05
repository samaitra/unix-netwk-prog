#include <stdio.h>
#include <stdlib.h>
main(){

int val = 10;
 if(fork())
 	wait(&val);
 val++;
 printf("%d\n", val);
 exit(val);
 execl("/bin/ls","ls","-l", NULL);
}


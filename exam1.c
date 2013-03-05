#include <stdio.h>
#include <stdlib.h>
int x=3;
main(){
	
int st;
int pid=fork();
x=5;
if(!pid)
	PutVal();
else{
	//waitpid(pid,&st,0);
	printf("x=%d\n",x);

}
exit(1);
}

PutVal(){
	x=2*5;
}
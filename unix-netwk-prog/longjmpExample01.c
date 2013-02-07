//showing the use of setjmp() & longjmp()
#include<stdio.h>
#include <setjmp.h>
#include <signal.h>

jmp_buf  env;

main() {

 int  rval; 
  
  rval = setjmp(env); 
  
  printf("\nvalue of rval = %d\n", rval);

    if (rval != 0) 
         exit(0);
	   
 printf("\nToP to longjmp ...  \n");
   
  longjmp(env, 3); 

   printf("\nBottom to longjmp ...  \n");
  } 


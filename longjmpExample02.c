//Program to show the use of setjmp() & longjmp() to jump from functions
#include<stdio.h>
#include <setjmp.h>
#include <signal.h>

void handle_fpe(int signo);
jmp_buf env;
main( ) 
   {    int i,j,k;
	
    signal(SIGFPE,handle_fpe);

		 k=setjmp(env);
		   printf("When setjmp() returns Value of K is = %d\n", k);
                    //Once Enter denominator value as Zero for SIGFPF signals to generate
                       	printf("Enter numerator number\n");  scanf("%d",&i);
		printf("Enter denominator number\n"); scanf("%d",&j);
		printf("Division {%d/%d} is: %d\n",i,j,i/j);
		          /// longjmp(env, 2);

      }

void handle_fpe(int signo)
    {   printf("Signal handler routine called..\n");
	printf("Division by zero:Floating point exception\n");
	longjmp(env, 999);
     }    


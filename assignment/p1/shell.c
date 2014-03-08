//
//  shell.c
//  
//
//  Created by Saikat Maitra on 04/03/14.
//
//

#include <stdio.h>
#define _GNU_SOURCE     /* Get declaration of strsignal() from <string.h> */
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>

void sig_int(int);
void sig_stp(int);
int main(int argc, char *argv[]) {
	char commands[32];
	char style[32] = "sequential";
	pid_t pid;
	int rid;
	char *token;
	char *bgjob;
	signal(SIGINT, sig_int);
	signal(SIGSTOP, sig_stp);

	for(;;){

	printf("Enter command:\n");
	scanf("%s", commands);
	printf("Enter execution style, valid types are sequential(s) or parallel(p):\n");
	scanf("%s", style);

	if (style[0] == 's' || style[0] == 'S') {

		token = strtok(commands, ";");
		while (token != NULL ) {
			pid = fork();
			if (pid == 0) {

				int len = strlen(token);
				char last = token[len - 1];

				if (last == '&') {
					bgjob = strtok(token, "&");
					if (bgjob != NULL ) {
						printf("Executing command in background %s\n", token);
						execlp(bgjob, "&", NULL );
					}

				} else {
					printf("Executing command %s\n", token);
					execlp(token, token, NULL );
					}
				}

			 else {

				rid = waitpid(pid, 0, 0);
				printf("PID of terminated Child:%d\n", rid);
				token = strtok(NULL, ";");
			}
		}

	}

	if (style[0] == 'p' || style[0] == 'P') {

		token = strtok(commands, ";");
		while (token != NULL ) {
			pid = fork();
			if (pid == 0) {
				int len = strlen(token);
				char last = token[len - 1];

				if (last == '&') {
					bgjob = strtok(token, "&");
					if (bgjob != NULL ) {
						printf("Executing command in background %s\n", token);
						execlp(bgjob, "&", NULL );
					}

				} else {
					printf("Executing command %s\n", token);
					execlp(token, token, NULL );
				}

			} else {
				token = strtok(NULL, ";");
			}
		}

	    while ((rid = wait(NULL)) > 0)
	    {
	    	printf("PID of terminated Child:%d\n", rid);

	    }



	}
	}
}
void sig_int(int signo) {
      printf("Pressed ctrl-c");
      printf("\nReceived SIGINT signal %d\n", signo);

     }


void sig_stp(int signo) {
    printf("Pressed ctrl-z");
     printf("\nReceived SIGSTOP signal %d\n", signo);
}

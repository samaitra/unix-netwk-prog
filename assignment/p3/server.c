//
//  server.c
//
//
//  Created by Saikat Maitra on 04/03/14.
//
//
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <netinet/tcp.h>
#include <pthread.h>
#define MAX     256


static void *doit(void *);
void str_echo(void *);
char* tempbuf[MAX];

int main(int argc, char *argv[]) {
	int sockfd, newsockfd, portno, clilen;
	char buff[256], *ptr;
	struct sockaddr_in serv_addr, cli_addr;

	pthread_t tid;
	int n;
	const int on = 1;
	if (argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");

	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		perror("ERROR opening socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(0);
	}

	listen(sockfd, 5);

	for (;;) {
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
			perror("ERROR on accept");
		pthread_create(&tid, NULL, doit, (void *) newsockfd);

		}
	}

static void *
		doit(void *arg) {

			pthread_detach(pthread_self());
			str_echo((int) arg);
			close((int) arg);
			return (NULL );
}
void str_echo(void *arg) {

	char buff[256], *ptr;
	int n;

	n = read(arg, buff, 255);
	if (n < 0)
		printf("ERROR reading from socket");
		printf("Received  message from Client: %s\n", buff);

		char type[32];
		char *filename[32];
		char *fi[32];
		char *query[32];

		strcpy(query, strtok(buff , " \t"));
		strcpy(type, strtok(NULL, " \t"));

		if(type[0]=='N'){
			strcpy(filename , strtok(NULL, " \t"));

			strncpy(fi, filename, (strlen(filename)-1));
			}

		printf("query %s\n",query);
		printf("type %s\n",type);
		printf("filename %s\n",filename);

		char* buf[MAX];


		if(type[0]=='N'){

			int fd[2], pid,retval,rid;
			int n;
			    pipe(fd);
				pid=fork();
			        if (pid==0) {
			            dup2(fd[1],1);
			            close(fd[0]);
			            char *argv[] = { "grep", query, fi, NULL};
			            if(execvp("grep", argv)<0){
			            perror("execvp");
			            }
			        }
				else
				  {  close(fd[1]);
			         n = read(fd[0], buf, MAX);
			         buf[n] = '\0';

			         rid=waitpid(pid, 0, 0);
			         printf("Pid of terminated Child:%d\n",rid);
				  }

		}
		else if(type[0]=='Y'){

			int pfd[2], cpid,rid;
			int fd[2],cppid,rrid;

			    pipe(pfd);
				pipe(fd);
			    cpid=fork();
			        if (cpid==0) {
			            close(pfd[0]);
			            int len = strlen(tempbuf);
			            printf("tempbuf len %d\n",len);

			            write(pfd[1],tempbuf,len);
			            }
			        else
			        {

			         	 dup2(pfd[0],0);
			        	 close(pfd[1]);

			        	 cppid = fork();

			        	 if(cppid==0){

			               dup2(fd[1],1);
			        	   close(fd[0]);
			        	   char *argv[] = { "grep", query, NULL};
			        	   execvp("grep", argv);

			        	 }else{
			        		 close(fd[1]);
			        		 n = read(fd[0], buf, MAX);
			                 buf[n] = '\0';
			                 rrid=waitpid(cppid, 0, 0);
			                 printf("Pid of terminated Child:%d\n",rrid);

			        	 }

			         }

				rid=waitpid(cpid, 0, 0);
				printf("Pid of terminated Child:%d\n",rid);

		}


	strcpy(tempbuf, buf);

	n = write(arg, buf, strlen(buf));
	if (n < 0)
		perror("ERROR Received writing to socket");
	close(arg);

}






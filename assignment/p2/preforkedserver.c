//
//  preforkedserver.c
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
#include <sys/un.h>

#define SO_REUSEPORT atoi(argv[1])
#define START_SERVERS atoi(argv[2])
#define MIN_SPARE_SERVERS atoi(argv[3])
#define MAX_SPARE_SERVERS atoi(argv[4])
#define MAX_CLIENTS atoi(argv[5])
#define MAX_REQUEST_PER_CHILD atoi(argv[6])

char* Lower2Upper(char*);
void sig_int(int);
pid_t child_make(int, int, int);
static pid_t *pids;

int main(int argc, char *argv[]) {
	int sockfd, newsockfd, portno, clilen;
	char buff[256], *ptr;
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	const int on = 1;

	if (argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		perror("ERROR opening socket");

	//setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(portno); /// =htons(atoi(argv[1]));
	//setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(0);
	}

	listen(sockfd, 5);
	int i;
	pids = calloc(START_SERVERS, sizeof(pid_t));
	for (i = 0; i < START_SERVERS; i++) {
		pids[i] = child_make(i, sockfd, sizeof(serv_addr));
	}

	signal(SIGINT, sig_int);

	for (;;) {

		for(i=0;i<START_SERVERS;i++){
			sleep(10);
			int p;
			int sockfd;
			struct sockaddr_un servaddr;

			sockfd = socket(AF_LOCAL, SOCK_STREAM,0);
			bzero(&servaddr, sizeof(servaddr));
			servaddr.sun_family = AF_LOCAL;
			char *unixpath[32];
			sprintf(unixpath,"%d", pids[i]);
			strcpy(servaddr.sun_path, unixpath);

			connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

			n = write(sockfd,"req",3);
			     //if (n < 0)  printf("ERROR writing to socket\n");

		    bzero(buff,256);
			n = read(sockfd,buff,255);
			    //if (n < 0) printf("ERROR reading from socket\n");
			   printf("Number of requests handled :%s\n",buff);
			   close(sockfd);
			   int req = atoi(buff);
			   if(req>=MAX_REQUEST_PER_CHILD){
				   kill(pids[i],SIGTERM);
				   printf("Killed process pid : %ld\n",pids[i]);
				   pids[i] = child_make(i, sockfd, sizeof(serv_addr));
				   sleep(10);
				   printf ("Started process pid: %ld\n",pids[i]);
			   }
		}


		pause();

		}
}
void sig_int(int signo) {

	printf("Number of active child :%d\n",sizeof(pids));
    pid_t pid;
           int stat;
          while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
              printf("Child %d terminated\n",pid);
           return ;

}

pid_t child_make(int i, int listenfd, int addrlen) {

	pid_t pid;
	void child_main(int, int, int);

	if ((pid = fork()) > 0)
		return (pid);

	child_main(i, listenfd, addrlen);
}

void child_main(int i, int sockfd, int addrlen) {
	int newsockfd, portno, clilen;
	char buff[256], *ptr;

	struct sockaddr_in serv_addr, cli_addr;
	int n;
	const int on = 1;
	static char str[128];
	int req_handled = 0;
	printf("child %ld starting\n",(long)getpid());

	int listenfd,connfd;
	pid_t childpid;
	socklen_t clilen_unix;
	struct sockaddr_un cliaddr_unix,servaddr_unix;

	listenfd = socket(AF_LOCAL,SOCK_STREAM,0);

	bzero(&servaddr_unix,sizeof(servaddr_unix));
	servaddr_unix.sun_family = AF_LOCAL;
	char *unixpath[32];
	sprintf(unixpath,"%d", getpid());
	unlink(unixpath);
	strcpy(servaddr_unix.sun_path, unixpath);

	bind(listenfd,(struct sockaddr *)&servaddr_unix,sizeof(servaddr_unix));
	listen(listenfd,5);


	for( ; ; ){
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0)
		perror("ERROR on accept");

	//   printf("Client IP: %s\n", inet_ntoa(cli_addr.sin_addr));
	//     printf("Client Port: %hu\n", ntohs(cli_addr.sin_port));

	inet_ntop(AF_INET, &cli_addr.sin_addr, str, clilen);//inet_ntoa(cli_addr.sin_addr));
    printf("Connected Child PID: %ld\n",(long)getpid());
	printf("Connected Client IP: %s\n",str);
	printf("Connected Client Port: %hu\n", ntohs(cli_addr.sin_port) );

		bzero(buff, 256);
		n = read(newsockfd, buff, 255);
		if (n < 0)
			printf("ERROR reading from socket");
		printf("Received  message from Client: %s\n", buff);
		ptr = Lower2Upper(buff);
		n = write(newsockfd, ptr, strlen(buff));
		if (n < 0)
			perror("ERROR Received writing to socket");
		close(newsockfd);
		req_handled++;


		clilen_unix = sizeof(cliaddr_unix);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr_unix, &clilen_unix);
				if (connfd < 0)
				perror("ERROR on accept");

				if((childpid=fork())==0){
					close(listenfd);
					str_req_handled(connfd,req_handled);
					//exit(0);
				}
				close(connfd);
	}
}

char* Lower2Upper(char *str) {
	int i;
	for (i = 0; str[i]; i++)
		str[i] = toupper(str[i]);
	return str;
}

void str_req_handled(int connfd,int req){
	int n;
	char *buf[32];
	n = read(connfd,buf,32);
		if (n < 0) perror("ERROR reading from socket");
	    bzero(&buf,sizeof(buf));
	    sprintf(buf,"%d", req);
	n=write(connfd,buf,strlen(buf));
		 if (n < 0) perror("ERROR Received writing to socket");

}

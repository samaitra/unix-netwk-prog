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
#define SO_REUSEPORT atoi(argv[1])

char* space2atr(char*);
void sig_chld(int );
 
int main(int argc, char *argv[])
  {
int sockfd, newsockfd,portno,clilen;
char buff[256],*ptr;
struct sockaddr_in server_addr,client_addr;
int n;const int on = 1;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");

     }
sockfd = socket(AF_INET,SOCK_STREAM,0);
if(sockfd < 0){
	perror("Error opening socket...");
}

bzero((char *)&server_addr, sizeof(server_addr));
portno = atoi(argv[1]);
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
server_addr.sin_port = htons(portno);

if(bind(sockfd,(struct sockaddr *) &server_addr, sizeof(server_addr))<0){
	perror("Error om binding.");
	exit(0);
} 
listen(sockfd,5);

signal(SIGCHLD, sig_chld);

   for(;;)
	{ 
	   clilen = sizeof(client_addr);
           newsockfd = accept(sockfd,(struct sockaddr *) &client_addr, &clilen);
     		if (newsockfd < 0)   perror("ERROR on accept");
   
//   printf("Client IP: %s\n", inet_ntoa(cli_addr.sin_addr));
  //     printf("Client Port: %hu\n", ntohs(cli_addr.sin_port));

    printf("Connected Client IP: %s\n",inet_ntop (AF_INET, &client_addr.sin_addr, 4, NULL));//inet_ntoa(cli_addr.sin_addr));
    printf("Connected Client Port: %hu\n", ntohs(client_addr.sin_port)); 
     	int pid=fork();
	     if (pid==0)
        	  { close(sockfd);
            	    bzero(buff,256);
	           
	   n = read(newsockfd,buff,255);
           	 if (n < 0) perror("ERROR reading from socket");
       	    printf("Received  message from Client: %s\n",buff);
           ptr=space2atr(buff); 
	  n = write(newsockfd,ptr,strlen(buff)); 
	//n = write(newsockfd,"Acknowledgemnt OF  message from Server",38);
         		 if (n < 0) perror("ERROR Received writing to socket");
           close(newsockfd);
	   exit(0);
          }        
      close(newsockfd);
   } 
}

 void sig_chld(int signo){ 

 	pid_t pid;
       int stat;
      while((pid = waitpid(-1, &stat, WNOHANG)) > 0){
          printf("Child %d terminated\n",pid);
       return ; 
     }
}
char* space2atr(char *str){ 

	int i;
       for( i = 0; str[ i ]; i++){
         if(isspace(str[ i ])){
         	str[ i ]='@';
         }
     }
        return str;
}








  
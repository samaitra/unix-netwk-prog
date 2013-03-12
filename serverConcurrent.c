//Concurrent Server program using TCP socket
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
char* Lower2Upper(char*);
void sig_chld(int );
 
int main(int argc, char *argv[])
  {
     int sockfd, newsockfd, portno, clilen;
     char buff[256],*ptr;
     struct sockaddr_in serv_addr, cli_addr;
     int n;const int on = 1;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");

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

    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
              {perror("ERROR on binding");exit(0);}

     listen(sockfd,5);
    
  signal(SIGCHLD, sig_chld);
    
    for(;;)
	{ 
	   clilen = sizeof(cli_addr);
           newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
     		if (newsockfd < 0)   perror("ERROR on accept");
   
//   printf("Client IP: %s\n", inet_ntoa(cli_addr.sin_addr));
  //     printf("Client Port: %hu\n", ntohs(cli_addr.sin_port));

    printf("Connected Client IP: %s\n",inet_ntop (AF_INET, &cli_addr.sin_addr, 4, NULL));//inet_ntoa(cli_addr.sin_addr));
    printf("Connected Client Port: %hu\n", ntohs(cli_addr.sin_port)); 
     	int pid=fork();
	     if (pid==0)
        	  { close(sockfd);
            	    bzero(buff,256);
	           
	   n = read(newsockfd,buff,255);
           	 if (n < 0) error("ERROR reading from socket");
       	    printf("Received  message from Client: %s\n",buff);
           ptr=Lower2Upper(buff); 
	  n=write(newsockfd,ptr,strlen(buff)); 
	//n = write(newsockfd,"Acknowledgemnt OF  message from Server",38);
         		 if (n < 0) perror("ERROR Received writing to socket");
           close(newsockfd);
	   exit(0);
          }        
      close(newsockfd);
   } 
}

 void sig_chld(int signo)
    { pid_t pid;
       int stat;
      while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
          printf("Child %d terminated\n",pid);
       return ; 
     }

char* Lower2Upper(char *str)
     { int i;
       for( i = 0; str[ i ]; i++)
         str[ i ] = toupper( str[ i ] );
        return str;
      }



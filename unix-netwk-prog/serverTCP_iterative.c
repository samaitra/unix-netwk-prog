//Iterative Server program using TCP socket
#include <stdio.h>
#include<string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
char* Lower2Upper(char*);

int main(int argc, char *argv[])
 {
     int sockfd, newsockfd, portno, clilen;
     char buff[256],*ptr;
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");

     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        perror("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
     serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
              {perror("ERROR on binding");exit(0);}

     listen(sockfd,5);

    for(;;)
	{ 
	   clilen = sizeof(cli_addr);
           newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
     		if (newsockfd < 0)   
		       perror("ERROR on accept");
     //printf("Connected Client IP: %s\n",inet_ntoa(cli_addr.sin_addr));
     //printf("Connected Client Port: %hu\n", ntohs(cli_addr.sin_port)); 
              bzero(buff,256);
	   n = read(newsockfd,buff,255);
           	 if (n < 0) error("ERROR reading from socket");
           printf("Received  message from Client: %s\n",buff);
            ptr=Lower2Upper(buff); 
	  n=write(newsockfd,ptr,strlen(buff)); 
	//n = write(newsockfd,"Acknowledgemnt OF  message from Server",38);
         	 if (n < 0) perror("ERROR Received writing to socket");
                       
       close(newsockfd);
     } 
 exit(0);
 }

char* Lower2Upper(char *str)
     { int i;
       for( i = 0; str[ i ]; i++)
         str[ i ] = toupper( str[ i ] );
        return str;
      }



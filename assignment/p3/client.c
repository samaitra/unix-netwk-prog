//
//  client.c
//
//
//  Created by Saikat Maitra on 04/03/14.
//
//
#include <stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char *msg)
{
perror(msg);
exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *shost;
    char buff[256];

    if (argc < 3) {  fprintf(stderr,"usage %s <IP ADDRESS> <PORT>\n", argv[0]);
	  	 exit(0);
		}


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[2]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr= inet_addr(argv[1]);
   serv_addr.sin_port = htons(atoi(argv[2]));

   if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
       error("ERROR connecting");
   	   printf("Connection Established\n");
   	   printf("Query: ");
     bzero(buff,256);
    fgets(buff,255,stdin);

  n = write(sockfd,buff,strlen(buff));
     if (n < 0)  error("ERROR writing to socket");

      bzero(buff,256);
  n = read(sockfd,buff,255);
    if (n < 0) error("ERROR reading from socket");
   printf("Client:%s\n",buff);

close(sockfd);
 return 0;
}








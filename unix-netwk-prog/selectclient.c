//Client using select
#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<netdb.h>
#define MAXLINE 1024

void str_cli(FILE *fp,int sockfd);
int max(int i,int j);
int Readline(int fd, void *vptr, int maxlen);
int Writen(int fd, const void *vptr, int n);
int max(int i,int j)
{
	if(i>j)
		return i;
	else
		return j;
}

void str_cli(FILE *fp,int sockfd)
{
	int maxfdp1, stdineof;
	fd_set rset;
	char buf[MAXLINE];
	int n;

	stdineof = 0;
	FD_ZERO(&rset);

        for( ; ; )
  	   {
		if(stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;

		select(maxfdp1, &rset, NULL, NULL, NULL);

		if(FD_ISSET(sockfd, &rset))
		{
			if((n=Readline(sockfd, buf, MAXLINE)) == 0)
	 	            {	perror("str_cli: server terminated prematurely");
			     exit(1);
		            }
		       
		       //write(fileno(stdout),buf,n);
			printf("Received from server:%s\n",buf);
		}

		if(FD_ISSET(fileno(fp), &rset))
		{   
			if(( n = read(fileno(fp), buf, MAXLINE)) == 0)
			     return;
			Writen(sockfd, buf, n);
		}
	}

}


int main(int argc, char **argv)
{
        int sockfd;
        struct sockaddr_in servaddr;
        int port;
        struct hostent *shost;

        if(argc!=3)
         {
                printf("USAGE ERROR:<SERVER IP> <PORT NO>\n");
                exit(1);
          }

        if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
        {
                perror("socket:");
                exit(0);
        }
     
   /*  shost = gethostbyname(argv[1]);
         if (shost == NULL)
             { fprintf(stderr,"ERROR, no such host\n");
                  exit(0);
             }
   */
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        port = atoi(argv[2]);
        servaddr.sin_port=htons(atoi(argv[2]));  //htons(port);
        inet_pton(AF_INET, argv[1], &servaddr.sin_addr.s_addr);
        
	//bcopy((char *)shost->h_addr,(char *)&servaddr.sin_addr.s_addr,shost->h_length);

        if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
        {
                perror("connect");
                exit(0);
        }
        printf("Connection established with the server\n");

        str_cli(stdin,sockfd);

        return 0;
}
         
 int Readline(int fd, void *vptr, int maxlen)
   { int n, rc;
     char    c, *ptr;
     ptr = vptr;
    for (n = 1; n < maxlen; n++) {
        again:
        if ( (rc = read(fd, &c, 1)) == 1) {
                *ptr++ = c;
             if (c == '\n')
                     break;          
	         } else if (rc == 0) {
             *ptr = 0;
         return (n - 1);     
       } else {
             if (errno == EINTR)
               goto again;
                  return (-1);        
                }
            }
       *ptr = 0;                   
      return (n);
 }

int Writen(int fd, const void *vptr, int n)
 { int nleft,nwritten;  const char *ptr;
     ptr = vptr;
     nleft = n;
  while (nleft > 0) 
      {  if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
	    if (nwritten < 0 && errno == EINTR)
	          nwritten = 0;  
	     else
	        return (-1);    
	      }
         nleft -= nwritten;
         ptr += nwritten;
      }
   return (n);
 }

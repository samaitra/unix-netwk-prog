//Clinet program using SHUTDOWN
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<fcntl.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#define MAXLINE 1024

void str_cli(FILE *fp,int sockfd);
int max(int i,int j);

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
			if((n=read(sockfd, buf, MAXLINE)) == 0)
			{
				if(stdineof == 1)
					return;
				else
				{
					perror("str_cli: server terminated prematurely");
					exit(1);
				}
			}
			write(fileno(stdout),buf,n);
			//printf("Received from server:%s\n",buf);
		}

		if(FD_ISSET(fileno(fp), &rset))
		{
			if(( n = read(fileno(fp), buf, MAXLINE)) == 0)
			{
				stdineof = 1;
				shutdown(sockfd, SHUT_WR);
				FD_CLR(fileno(fp), &rset);
				continue;
			}

			write(sockfd, buf, n);
		}
	}

}


int main(int argc, char **argv)
{
        int sockfd;
        struct sockaddr_in servaddr;
        int port;

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

        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        port = atoi(argv[2]);
        servaddr.sin_port=htons(port);
        inet_pton(AF_INET, argv[1], &servaddr.sin_addr.s_addr);

        if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
        {
                perror("connect");
                exit(0);
        }
        printf("Connection established\n");

        str_cli(stdin,sockfd);

        return 0;
}
          

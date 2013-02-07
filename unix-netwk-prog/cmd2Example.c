//Implementaion of  ls | wc -c piping cmd
 #include <stdio.h>
 #include <stdlib.h>
  #include <unistd.h>

 int main()
   {
        int pfd[2], cpid,rid;

        pipe(pfd);
	cpid=fork();
        if (!cpid) {
             //close(1); dup(pfd[1]);       /* close normal stdout */
            dup2(pfd[1],1);   /* make stdout same as pfds[1] */
            close(pfd[0]); /*  don't need this */
        // printf("child  pid= %d\n",getpid()); 
	execlp("ls", "ls",NULL);
            } 
	else 
	  {  close(0);       /* close normal stdin */
                      dup(pfd[0]);
	   //dup2(pfd[0],0);   /* make stdin same as pfds[0] */
            close(pfd[1]); /* we don't need this */
        	//printf("parent  pid= %d\n",getpid()); 
	   execlp("wc", "wc","-c", NULL);

	rid=waitpid(cpid, 0, 0); 
	printf("Pid of terminated Child:%d\n",rid);
       }
    }


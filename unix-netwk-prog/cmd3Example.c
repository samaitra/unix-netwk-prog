//Implementation of    ls |sort |wc -l    piping cmd
 #include <stdio.h>
 #include <stdlib.h>
  #include <unistd.h>

 int main()
   {
        int pfd[2], cpid,rid,pfd2[2];

        pipe(pfd);
	cpid=fork();
     if (!cpid)
         {   pipe(pfd2);
	   if(!fork())
	     {  //close(1); dup(pfd[1]);       /* close normal stdout */
           	 dup2(pfd2[1],1);   /* make stdout same as pfd2[1] */
           	 close(pfd2[0]); /* close didn't needs */ 
		//printf("Grand child Process pid= %d\n",getpid()); 
		
		 execlp("ls", "ls",NULL);
               } 
	     else 
	 	 { // close(0);       /* close normal stdin */
            	  dup2(pfd2[0],0);   /* make stdin same as pfd2[0] */
            	  close(pfd2[1]); /* close didn't needs*/
    	  
		  dup2(pfd[1],1);  //make stdout same as pfd[1] 
	   	  close(pfd[0]);
		  //printf("Child Process pid= %d\n",getpid()); 

	   	  execlp("sort","sort",NULL);
            
		  wait(NULL);//called to handle zombies in case exec() fails
		}
	       }
	 else
	  { dup2(pfd[0],0);
	    close(pfd[1]);
	   //printf("Parent Process  pid= %d\n",getpid()); 
	   
	     execlp("wc", "wc","-l", NULL);
  	    
   		wait(NULL); //called to handle zombies in case exec() fails
	      printf("Parent terminate\n"); 
	  }
    }


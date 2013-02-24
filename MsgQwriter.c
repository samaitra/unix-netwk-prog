  //  Program to write in a message queue
  //First run this program after than MsgQreader
    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/msg.h>
  #define KEY 462462L

    struct my_msgbuf {
        long mtype;
        char mtext[200];
    };

  int main( )
    {
        struct my_msgbuf buf;
        int msqid;
        key_t key;

    if ((key = ftok("MsgQwriter.c", 'M')) == -1) {
           perror("ftok():Key creation Error ");
            exit(-1);
        }

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
          perror("Msgget() call Error");
            exit(-1);
         }
     else
        printf("\nMessage queue:%ld :created sucessfully",msqid);

   printf("\nEnter a text message:\n");
    scanf("%s",buf.mtext);
     
     buf.mtype =462; 

  /*  while( gets(buf.mtext), !feof(stdin) ) 
      {
       if (msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0) == -1)
               perror("msgsnd():ERROR"); 
	  else     
              printf("\n Message written to message queue\n");
       }
  */ 

    if (msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0) == -1)
           perror("msgsnd():ERROR");
     else     
         printf("Message written to message queue:%ld\n",msqid);
   

/*   if (msgctl(msqid, IPC_RMID, NULL) == -1)  {
          printf("\n msgctl():ERROR");
          exit(-1);
        } 
    else 
       printf("\n Message queue:%ld: destroyed\n",msqid);

*/
        return 0;
    }


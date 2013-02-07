   //Program to read from message queue
  //First run  MsgQwriter program after than this MsgQreader program
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

  int main(void)
    {
        struct my_msgbuf buf;
        int msqid;
        key_t key;

     //use same key as writer of the queue used
   if ((key = ftok("MsgQwriter.c", 'M')) == -1) {     
           perror("ftok():Key creation Error ");
              exit(-1);
         }

  if ((msqid = msgget(key, 0644)) == -1) {
           perror("Msgget(): Error");
            exit(-1);
          }
     else
        printf("Message queue:msqid:%ld\n",msqid);

 //   buf.mtype = 462; 
    printf("\n Message queue Reader ready to receive message"); 

if (msgrcv(msqid, (struct msgbuf *)&buf, sizeof(buf),462, 0) == -1)
         { printf("\n msgrcv():Error");
           exit(-1);
         }
   else 
       printf("\n Received Message from queue :%s\n",buf.mtext);
 

 /*  if (msgctl(msqid, IPC_RMID, NULL) == -1) {
         printf("\n msgctl():Error");  exit(-1);
        }
    else 
        printf("\n Message queue:%ld: destroyed\n",msqid);
  */

        return 0;
    }


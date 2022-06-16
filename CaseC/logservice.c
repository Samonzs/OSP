/* logserver.c -- implementation of the log server
 * Ali Salman 20056663@student.westernsydney.edu.au
 * COMP 30015 Operating Systems Programming
 * Practical Case Study C
 * This is the sample file with modifications
 */

#include "logservice.h"

int logServiceInit()
{
	int id;
	key_t key = KEY;

	id = msgget(key, IPC_EXCL | 0666);	/* attach process and connect to existing queue */	
		
	if (id == -1) 
	{		
		perror("msgget");
		exit(1);
	}

	return id;
}

int logMessage(int serviceId,char *message)
{
	int rv;
	struct message msg;
	msg.type = getpid(); 
	
	printf("The message is \"%s\"\n", message);

	if(strlen(message) > MSGCHARS)
	{
		printf("Cannot exceed 255 characters\n"); 
		exit(1);
	}

	strncpy(msg.message, message, MSGCHARS); 

	if(rv = (msgsnd(serviceId, &msg, sizeof(msg), 1)) == -1)  /* send msg to server for it to be recieved */
	{
		perror("msgsend");
		exit(1);
	}
	else
	{
		printf("The Process ID is %d\n", msg.type);
		printf("Message Sent Success!\n");
	} 

	return rv;
}

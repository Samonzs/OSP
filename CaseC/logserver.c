/* logserver.c -- implementation of the log server
 * Ali Salman 20056663@student.westernsydney.edu.au
 * COMP 30015 Operating Systems Programming
 * Practical Case Study C
 * This is the sample file with modifications
 */


#include <signal.h>
#include "logservice.h"

int queue_id; /* stores queue_id for use in signal handler */

void handler(int sig);

int main()
{
	struct message msg;
	key_t key = KEY;
	queue_id = msgget(key, IPC_CREAT | 0666 | IPC_EXCL); /* create if it queue doesnt exist, else not run*/		

	if (queue_id == -1) 
	{		
		perror("msgget");
		exit(1);
	}

	printf("Message queue is ready.\n");

	signal(SIGINT, handler);


	while (1)
	{		
		int rv = msgrcv(queue_id, &msg, sizeof(msg), 0, 1); /* recieve msg sent by client */
		
		if(rv != -1)
		{
			printf("%ld: %s\n", msg.type, msg.message);
		}
		else
		{
			perror("msgrcv");
		}

	}

	return 0;
}


void handler(int sig)
{
	printf("\nYou have stopped the queue, Clean up will now proceed ...\n"); /* deletes queue */

	msgctl(queue_id, IPC_RMID, NULL); 

	exit(0);
}
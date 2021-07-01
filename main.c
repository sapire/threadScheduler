#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

struct node
{
    int asciiName;
    struct node *next;
}typedef node;



/********************************/

int taskGetId()
{
	//returns a unique id

	//counter+linked list

	static int counter = 0;
	static node *front = NULL;
	if (front == NULL)
	{
		if (counter < 19*8)
		{
			return counter++;
		}
		else
		{
			//TODO: exception

		}
		
	}

	node* temp = front;
	front = front->next;
	return temp->asciiName;
}

bool taskShouldSuspend()
{
	//returns true if the task should be suspended
}

void taskSuspend()
{
	//suspends a task until released
}

void taskWait(int numOfSeconds)
{
	//suspends a task for n seconds
}

char* taskGetMem()
{
	//get the buffer
}

void taskReleaseMem()
{
	//release the buffer
}

int taskPrio()
{
	//return the priority of the task
}

void taskWake(int pid)
{
	//wake a task by its pid

	

}

/***********/

int main()
{
	printf(sizeof(char));

}
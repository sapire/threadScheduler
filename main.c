#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep()
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#define MAX_TASKS 9
#define MAX_LEN 19

typedef struct task
{
    int id; // unique id for the task
    int priority; //priority- higher = more priority. no 2 tasks share the same value for priority
    char name[19]; //unique ascii name for the task
    bool isSuspended; //true if the task is suspended, false if it is running
    struct timeval tv; //last time the task run - to know when to release the task
    int suspensionTime; //how long the task has been suspended, not sure if needed?????????
	

}task;

task* tasksArray[MAX_TASKS];
char buff[MAX_LEN]; // the buffer holds the name of the current running task

task* taskGetPointer(int id)
{
      for(int i = 0;i<MAX_TASKS;i++)
	  {
		if(tasksArray[i]->id==id)
	  	{
        	return tasksArray[i];
      	}
	  }
    return NULL;
}

char* taskGetName(int id)
{
	task* t = taskGetPointer(id);
	return t->name;
}

int taskGetId(task* taskPointer)
{
	return taskPointer->id;
	//returns a unique id

	//counter+linked list

	// static int counter = 0;
	// static node *front = NULL;
	// if (front == NULL)
	// {
	// 	if (counter < 19*8)
	// 	{
	// 		return counter++;
	// 	}
	// 	else
	// 	{
	// 		//TODO: exception

	// 	}
		
	// }

	// node* temp = front;
	// front = front->next;
	// return temp->asciiName;
}

bool taskShouldSuspend(int id)
{
	//returns true if the task should be suspended
	//all tasks should be suspeneded except for the one chosen to run at each second
	//so the task to suspend is whatever is currently in the buffer
	task* t = taskGetPointer(id);
	return strcmp(t->name, buff) == 0? true : false;

}

void taskSuspend(int id)
{
	//suspends a task until released
	// check how??? maybe sleep...
	task* t = taskGetPointer(id);

	while (t->isSuspended);
	
}



void taskWait(int numOfSeconds, int id)
{
	//suspends a task for n seconds
	// wait(numOfSeconds);
	//?????????
	
	task* t = taskGetPointer(id);
	t->isSuspended = true;
	usleep(numOfSeconds * 1000000);
	t->isSuspended = false;
	// https://stackoverflow.com/questions/10922900/is-it-possible-to-wait-a-few-seconds-before-printing-a-new-line-in-c#10923084

}

char* taskGetMem()
{
	return &buff;
	
}

void taskSetMem(char* taskName)
{
	int n = 0;
	for (n = 0; taskName != '\0'; ++n);
	strncpy(buff, taskName, n);
}

void taskReleaseMem() //TODO: 
{
	//release the buffer
	fflush(buff);
	free(buff);

}

int taskPrio(int id)
{
	//return the priority of the task
	task* t = taskGetPointer(id);
	return t->priority;
}

void taskWake(int pid) //TODO: 
{
	//wake a task by its pid

	

}

int priorityArray[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int IdArray[] = {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
char* asciiArray[] = {"task0", "task1", "task2", "task3", "task4", "task5", "task6", "task7", "task8", "task9"};
task* taskCreate(int i) // ????
{
	if (i>9 || i<0)
	{
		printf("Failure! ID must be in range of 0-9!!!");
		return -1;
	}
	
	task* t = malloc(sizeof(task));
	t->id = IdArray[i];
	t->priority = priorityArray[i];
	t->isSuspended = true;
	// t->name = asciiArray[i];
	// int n = sizeof(asciiArray[i]);
	int n = 0;
	for (n = 0; asciiArray[i] != '\0'; ++n);
	strncpy(t->name, asciiArray[i], n);
	tasksArray[i] = t;
}

/***********/

void runTask(int id)
{
	do
	{
		if(taskShouldSuspend(id))
		{
			taskSuspend(id);
		}

		char* ptr = taskGetMem();
		printf ("Cur Task is %s Last Task is %s", taskGetName(id), ptr);
		taskSetMem(taskGetName(id)); // Set New current task
		taskReleaseMem();
		taskWait(1, id); // sleep for 1 seconds
	} while (1);
	
}

int main(int argc, char* argv[])
{
	//(1) Identify the preemption points.

	//(2) Identity the queues to implement.

	//(3) Explain the queues implementation. For instance, an array or a linked list.

	//(4) Add a diagram that visualizes all the elements. (in PowerPoint/Word and the likes).

	//(5) The program accepts n as the number of threads, and p as the number of cores.
	int n = argv[1]; //number of threads
	int p = argv[2]; //number of cores

	for (int i = 0; i < n; i++)
	{
		taskCreate(i);
	}
	

	//(6) A task priority is an arbitrary number ranging from 0 to N-1. Larger priority is the larger number. No two tasks share the same priority.


}
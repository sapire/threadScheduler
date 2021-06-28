#include <stdio.h>

char* taskGetName()
{
	//returns a unique ascii name of the thread, less than 19 bytes long

}

int taskGetId()
{
	//returns a unique id
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
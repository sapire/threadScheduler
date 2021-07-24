// #pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep()
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#define MAX_TASKS 9
#define MAX_LEN 19

int IdArray[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int priorityArray[] = {9,8,7,6,5,4,3,2,1,0};
char* asciiArray[] = {"task0", "task1", "task2", "task3", "task4", "task5", "task6", "task7", "task8", "task9"};

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

void taskCreate(int i) // ????
{

  if (i>9 || i<0)
  {
    printf("Failure! ID must be in range of 0-9!!!\n");
    return;
  }

  task* t = malloc(sizeof(task));
  if (t == NULL)
  {
    printf("Error! Unable to allocate memory.\n");
      exit(0);
  }
  //printf("success allocating memory\n"); //TODO: delete
  t->id = IdArray[i];
  //printf("assigned id %d\n", t->id); //TODO: delete
  t->priority = priorityArray[i];
  //printf("assigned prio %d\n", t->priority); //TODO: delete
  t->isSuspended = true;
  //printf("assigned isSuspended\n"); //TODO: delete
  int n = 0;
  for (n = 0; n<sizeof(*asciiArray[i]); ++n);
  strncpy(t->name, asciiArray[i], n);
  //printf("assigned task name\n"); //TODO: delete
  tasksArray[i] = t;
  printf("inserted into array\n"); //TODO: delete*/
}

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
  task* t = taskGetPointer(id);
  while (t->isSuspended); //spin lock
}

int taskPrio(int id)
{
  //return the priority of the task
  task* t = taskGetPointer(id);
  //printf("%d\n", t->priority);
  return t->priority;
}

void taskWait(int numOfSeconds, int id)
{
  task* t = taskGetPointer(id);
  t->isSuspended = true;
  usleep(numOfSeconds * 1000000);
  t->isSuspended = false;
  //printf("taskWait finish");
}

int main(int argc, char* argv[])
{
	if (argc <3)
	{
		printf("Error: Should send two arguments");
		return 0;
	}
	if (argc >2)
	{
		int n = atoi(argv[1]); //number of threads
		int p = atoi(argv[2]); //number of cores
		printf("P: %d, N: %d\n", p, n); //TODO: delete
	//validateInput(); //TODO
	if (!(n>0 && n<10))
	{
		printf("Error: invalid number of threads\n");
		return 0;
	}
	if (!(p>0 && p<5))
	{
		printf("Error: invalid number of cores\n");
		return 0;
	}	
	 for (int i = 0; i < n; i++)
	 {
		 printf("Creating task number %d\n", i); //TODO: delete
		 taskCreate(i);
		 
	 }
	
	 printf("%d\n", taskGetId(taskGetPointer(0))); //TODO: delete
	 
	 taskWait(5, 1);
	 //taskSuspend(0);
	 taskPrio(0);
	 }
return 0;
}

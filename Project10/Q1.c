#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	long long Id;
	char* name;
	long long salary;
	int yearType;
	union startingYear
	{
		char hebrewYear[7];
		long long gregorianDate;
	};
}Worker;

typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
} WorkerList;

WorkerList* deleteWorstWorker(WorkerList* head);
WorkerList* addWorker(WorkerList* head, Worker* w);
void printWorker(Worker* ptrWorker);
Worker* createWorker();
void freeWorkers(WorkerList* head);
void update_worker(WorkerList* head, float percent);
int index(WorkerList* head, long unsigned id);
WorkerList* reverse(WorkerList* head);
void printAllWorkers(WorkerList* head);


void main()
{
	int i;
	Worker* ptrWorker;
	WorkerList* head = NULL;

	for (i = 0; i < 1; i++)
	{
		ptrWorker = createWorker();
		head = addWorker(head, ptrWorker);
	}
	printf("\n\n");
	printAllWorkers(head);
	head = reverse(head);
	printf("the reverse list is: \n");
	printAllWorkers(head);
	float perecent = 20.0;
	update_worker(head, perecent);
	printf("after salary increment:\n");
	printAllWorkers(head);
	freeWorkers(head);
}
void printAllWorkers(WorkerList* head)
{
	WorkerList *current;
	for (current = head; current != NULL; current = current->next) //calls the print function and prints each worker
	{
		printWorker(current->data);
	}
}

Worker* createWorker()
{
	Worker* ptrWorker = (Worker*)malloc(sizeof(Worker));// making space in the memory for a new worker  
	if (ptrWorker == NULL)
	{
		printf("malloc failed\n");
		exit(1);
	}///the code asks all the inputs 
	printf("\nplease enter your Id number:\n");
	scanf("%lld", &ptrWorker->Id);
	char name[40];
	printf("please enter your name:\n");
	scanf("%s", name);
	int lenName = strlen(name);
	char* str = (char*)malloc((lenName + 1) * sizeof(char));
	if (str == NULL)
	{
		printf("there was no space on the computer to enter your name\n");
		return NULL;
	}
	strcpy(str, name);
	ptrWorker->name = str;
	printf("please enter your salary:\n");
	scanf("%lld", &ptrWorker->salary);
	printf("Please enter your starting year as a worker here:\n");
	char temp[40];
	scanf("%s", temp);
	if (temp[0] >= '0' && temp[0] <= '9')/// we check here if the year that the user wrote is a number or a letter so we can put the input in the right string
	{
		ptrWorker->gregorianDate = atol(temp);
		ptrWorker->yearType = 1;
	}
	else
	{
		strcpy(ptrWorker->hebrewYear, temp);
		ptrWorker->yearType = 0;
	}
	return ptrWorker;/// we return now a pointer to the beginning
}

void printWorker(Worker* ptrWorker)
{
	printf("%lld  %s  %lld  ", ptrWorker->Id, ptrWorker->name, ptrWorker->salary);/// prints the id , the name and his salary
	if (ptrWorker->yearType == 1)/// if his year type is 1 we know that we are going to print a long long type number
	{
		printf("%lld\n", ptrWorker->gregorianDate);
	}
	else// if not we know his year has to be letters that we put in a char string
	{
		printf("%s\n", ptrWorker->hebrewYear);
	}
}



WorkerList* addWorker(WorkerList* head, Worker* w)
{
	WorkerList* node = (WorkerList*)malloc(sizeof(WorkerList));// making space for the pointer
	if (node == NULL)
	{
		printf("malloc failed\n");
		exit(1);
	}
	node->data = w;
	node->next = NULL;
	if (head == NULL)/// first case. only one worker
	{
		head = node;
		return head;
	}
	WorkerList *prev = NULL, *current;// we're going to organize the list from bottom to top by checking if our pointer on the salary is smaller then the pointer of type Worker on salary (our next) 
	for (current = head; current != NULL && current->data->salary < w->salary; current = current->next)
	{
		prev = current;/// if it is smaller we put in prev the pointer of current and ask again in our for loop
	}
	node->next = current;// after the loop is done our next is equal to current
	if (prev == NULL)
	{
		head = node;
	}
	else
	{
		prev->next = node;
	}
	return head;/// we turn the pointer on the head of the new list after adding in the new worker
}

int index(WorkerList* head, long unsigned id)
{
	WorkerList* current;
	int workerIndex;
	for (workerIndex = 1, current = head; current != NULL && current->data->Id != id; current = current->next)///we go threw all the workers till we find a worker that thir id is equal to the id that was asked to find
	{
		workerIndex++;
	}
	if (current == NULL)// if the pointer went threw all the workers and hasn't found a worker with the id that was asked
	{
		return -1;
	}
	return workerIndex;/// return the number of times the pointer went over a worker till he found the worker with the id that was asked from the list
}

WorkerList* deleteWorstWorker(WorkerList* head)
{
	if (head == NULL)//our list is empty
	{
		return NULL;
	}
	WorkerList* node = head->next;///our list is from bottom to top so we delete our first worker on the list
	free(head);
	return node;// we return our new head
}

WorkerList* reverse(WorkerList* head)
{
	WorkerList* current, *next, *ptr3;
	current = head;
	next = current->next;
	if (head == NULL)/// if our list is empty
	{
		return NULL;
	}
	while (next != NULL)// as long as our next isn't pointing on null
	{
		/// we use here three pointers
		ptr3 = next->next;
		next->next = current;
		current = next;
		next = ptr3;
	}
	head->next = NULL;
	head = current;
	return head;// we return our new head that was our tail in the beginning 
}

void update_worker(WorkerList* head, float percent)
{
	WorkerList* current;
	for (current = head; current != NULL; current = current->next)/// we go threw all the workers on our list
	{
		current->data->salary += (long long)((float)current->data->salary * percent / 100.0);/// we add to the salary the precent, since the salary is type long long and the percent is type float we change the answe to be long long since it goes back in the salary
	}
}

void freeWorkers(WorkerList* head)
{
	WorkerList *current, *next;
	for (current = head; current != NULL; current = next)// we go threw all the workers and delete each worker
	{
		next = current->next;
		free(current);
	}
}

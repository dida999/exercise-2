#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SIZE 6

typedef struct worker {
	unsigned long ID;
	char* name;
	unsigned long salary;

	union year {
		char hebrew[SIZE];
		unsigned long international;
	} *year;
}worker;

typedef struct WorkerList
{
	worker * data;
	struct WorkerList* next;
} WorkerList;

worker* createWorker(unsigned long id, char* name, unsigned long salary, union year* myyear, int yeartype);
void printWorker(worker* worker, int yeartype);
WorkerList * addWorker(WorkerList *head, worker * w);

void main()
{
	int yeartype = 1;
	//test data
	union year * year = "2022";

	worker* one = createWorker(001, "juan", 10, year, yeartype);
	printWorker(one, yeartype);
	worker* two = createWorker(002, "anitta", 5, year, yeartype);
	printWorker(two, yeartype);
}
//yeartype- 0=hebrew,1=international
worker* createWorker(unsigned long id, char* name, unsigned long salary, union year* year, int yeartype)
{
	worker* worker1; 
	worker1 = (worker*)malloc(sizeof(worker));
	worker1->ID = id;
	worker1->name = name;
	worker1->salary = salary;
	if (yeartype != 0)
	{
		worker1->year = year->international;
	}
	else
		worker1->year = year->hebrew;
	return worker1;
}

void printWorker(worker* worker, int yeartype)
{
	printf("id:%u \nname:%s\nsalary: %u \n",
		worker->ID, worker->name, worker->salary);
	if (yeartype != 0) { printf("year: %d", worker->year->international); }
	else printf(" year: %s\n", worker->year->hebrew);
}

WorkerList * addWorker(WorkerList *head, worker * w)
{
	WorkerList *new_list_member = (WorkerList*)malloc(sizeof(WorkerList));
	if (new_list_member==0) {
		exit(0);
	}
}
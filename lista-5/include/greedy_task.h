#ifndef GREEDY_TASK_H
#define GREEDY_TASK_H

#include <stdio.h>
#include <stdlib.h>

#define START_TIME 0
#define FINISH_TIME 11

typedef enum{
	TRUE=1, FALSE=0
}boolean;

typedef enum{ 
	START, FINISH, SIZE, CRASHES 
}task_order;

typedef struct{
	int id;
	int init;
	int end;
	int size;
	int crashes;
}task;

extern task *create_tasks(int length);
extern void print_tasks(task *tasks, int length);
extern void print_tasks_by_criterion(task *tasks, int length, task_order criterion);
extern void check_best_order(task *tasks, int length);
extern void sort_tasks(task *tasks, int length, task_order criterion);

extern task *create_tasks_PDF();

#endif

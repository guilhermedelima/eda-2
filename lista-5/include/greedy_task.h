#ifndef GREEDY_TASK_H
#define GREEDY_TASK_H

#include <stdio.h>
#include <stdlib.h>

#define START_TIME 0
#define FINISH_TIME 14

#define MAX_TASK_SIZE 5
#define TASK_CE_SIZE 11

#define N_TASK_ORDER 4
#define NONE 4

#define MAX_LOOP 200



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

extern const char *TASK_ORDER[];

extern task *create_tasks(int length);
extern void print_tasks(task *tasks, int length);
extern void print_tasks_by_criterion(task *tasks, int length, task_order criterion);
extern task_order choose_criterion(int length);
extern void sort_tasks(task *tasks, int length, task_order criterion);

extern int get_selected_tasks(task *tasks, int length, task_order criterion);

extern task *create_tasks_counterexample_crashes();
extern task *create_tasks_first_example();

#endif

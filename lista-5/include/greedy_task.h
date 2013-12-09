#ifndef GREEDY_TASK_H
#define GREEDY_TASK_H

#include <stdio.h>
#include <stdlib.h>

/* Definem o intervalo de tempo no qual as tarefas serão criados */
#define START_TIME 0
#define FINISH_TIME 14


#define MAX_TASK_SIZE 5 /* Define tamanho máximo de uma tarefa */
#define TASK_CE_SIZE 11 /* Define o número de tarefas do contra exemplo */

#define N_TASK_ORDER 4 /* Define a quantidade de critérios */
#define NONE 4 /* Constante para representar critérios empatados */

#define MAX_LOOP 1000 /* Constante que limita o número de loops para se achar o melhor critério */

/* Enum para booleano */
typedef enum{
	TRUE=1, FALSE=0
}boolean;

/* Enum que define os critérios */
typedef enum{ 
	START, FINISH, SIZE, CRASHES
}task_order;

/* Estrutura que representa uma tarefa */
typedef struct{
	int id;
	int init;
	int end;
	int size;
	int crashes;
}task;

/* Vetor de strings com os nomes dos critérios */
extern const char *TASK_ORDER[];

/* Cabeçalho das funções públicas */
extern task *create_tasks(int length);
extern void print_tasks(task *tasks, int length);
extern void print_tasks_by_criterion(task *tasks, int length, task_order criterion);

extern void sort_tasks(task *tasks, int length, task_order criterion);
extern task_order choose_criterion(int length);

#endif

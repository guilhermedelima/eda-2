#include "greedy_task.h"

task *create_tasks(int length);
void calculate_crashes(task *tasks, int length);
void print_tasks(task *tasks, int length);
void print_tasks_by_criterion(task *tasks, int length, task_order criterion);
void check_best_order(task *tasks, int length);
int check_criterion(task *tasks, int length, task_order criterion);
boolean check_compatibility(task *t, task **selected_tasks, int last_selected, task_order criterion);

task *create_tasks(int length){

	task *tasks;
	tasks = (task *) malloc(length * sizeof(task));

	int i;
	for(i=0; i<length; i++){
		tasks[i].id = i+1;

		tasks[i].init = random() % FINISH_TIME;
		tasks[i].size = 1 + (random() % (FINISH_TIME - tasks[i].init));

		tasks[i].end = tasks[i].init + tasks[i].size;
		tasks[i].crashes = 0;
	}

	calculate_crashes(tasks, length);

	return tasks;
}

void calculate_crashes(task *tasks, int length){

	int i, j;
	for(i=0; i<length-1; i++){
		for(j=i+1; j<length; j++){
			if( (tasks[j].init < tasks[i].end) && (tasks[j].end > tasks[i].init)){
				tasks[i].crashes++;
				tasks[j].crashes++;
			}
		}
	}
}

void print_tasks(task *tasks, int length){

	int i;
	for(i=0; i<length; i++){
		printf("TASK %d\n", tasks[i].id);
		printf("init: %d\n", tasks[i].init);
		printf("end: %d\n", tasks[i].end);
		printf("size: %d\n\n", tasks[i].size);
		printf("crashes: %d\n\n", tasks[i].crashes);
	}
}


void print_tasks_by_criterion(task *tasks, int length, task_order criterion){

	printf("[ ");

	int i;
	for(i=0; i<length; i++){
		switch(criterion){
			case START:	
					printf("%d ", tasks[i].init);
					break;
			case FINISH:	
					printf("%d ", tasks[i].end);
					break;
			case SIZE:
					printf("%d ", tasks[i].size);
					break;
			case CRASHES:
					printf("%d ", tasks[i].crashes);
					break;
		}
	}

	printf("]\n");
}


void check_best_order(task *tasks, int length){

	int n_selected;

	n_selected = check_criterion(tasks, length, START);
	printf("SELECTED TASKS BY START: %d\n\n", n_selected);

	n_selected = check_criterion(tasks, length, FINISH);
	printf("SELECTED TASKS BY FINISH: %d\n\n", n_selected);

	n_selected = check_criterion(tasks, length, SIZE);
	printf("SELECTED TASKS BY SIZE: %d\n\n", n_selected);

	n_selected = check_criterion(tasks, length, CRASHES);
	printf("SELECTED TASKS BY CRASHES: %d\n\n", n_selected);

}

int check_criterion(task *tasks, int length, task_order criterion){

	int i, count;
	task **selected_tasks;

	selected_tasks = (task **) calloc(length, sizeof(task*));

	sort_tasks(tasks, length, criterion);

	count=0;
	selected_tasks[count] = &tasks[0];
	printf("SELECTED TASK: %d - %d\n", selected_tasks[count]->init, selected_tasks[count]->end);

	for(i=1 ; i<length; i++){
		
		if( check_compatibility(&tasks[i], selected_tasks, count, criterion) == TRUE){
			count++;
			selected_tasks[count] = &tasks[i];
			printf("SELECTED TASK: %d - %d\n", selected_tasks[count]->init, selected_tasks[count]->end);
		}
	}

	free(selected_tasks);
	return count+1;
}


boolean check_compatibility(task *t, task **selected_tasks, int last_selected, task_order criterion){

	boolean is_compatible = FALSE;

	switch(criterion){
		case START:
		case FINISH:	
				if(t->init >= selected_tasks[last_selected]->end)
					is_compatible = TRUE;

				break;
		case SIZE:
		case CRASHES:
				is_compatible = TRUE;

				int i;
				for(i=0; i<=last_selected && is_compatible==TRUE; i++){
					if( (t->init < selected_tasks[i]->end) && (t->end > selected_tasks[i]->init) )
						is_compatible = FALSE;
				}

				break;
	}

	return is_compatible;
}


task *create_tasks_PDF(){

	task *tasks;
	tasks = (task *) malloc(8 * sizeof(task));

	tasks[0].id = 1;
	tasks[0].init = 0;
	tasks[0].end = 6;
	tasks[0].crashes = 0;

	tasks[1].id = 2;
	tasks[1].init = 1;
	tasks[1].end = 4;
	tasks[1].crashes = 0;

	tasks[2].id = 3;
	tasks[2].init = 3;
	tasks[2].end = 5;
	tasks[2].crashes = 0;

	tasks[3].id = 4;
	tasks[3].init = 3;
	tasks[3].end = 8;
	tasks[3].crashes = 0;

	tasks[4].id = 5;
	tasks[4].init = 4;
	tasks[4].end = 7;
	tasks[4].crashes = 0;
	
	tasks[5].id = 6;
	tasks[5].init = 5;
	tasks[5].end = 9;
	tasks[5].crashes = 0;

	tasks[6].id = 7;
	tasks[6].init = 6;
	tasks[6].end = 10;
	tasks[6].crashes = 0;

	tasks[7].id = 8;
	tasks[7].init = 8;
	tasks[7].end = 11;
	tasks[7].crashes = 0;

	tasks[0].size = tasks[0].end - tasks[0].init;
	tasks[1].size = tasks[1].end - tasks[1].init;
	tasks[2].size = tasks[2].end - tasks[2].init;
	tasks[3].size = tasks[3].end - tasks[3].init;
	tasks[4].size = tasks[4].end - tasks[4].init;
	tasks[5].size = tasks[5].end - tasks[5].init;
	tasks[6].size = tasks[6].end - tasks[6].init;
	tasks[7].size = tasks[7].end - tasks[7].init;

	calculate_crashes(tasks, 8);
	return tasks;
}

















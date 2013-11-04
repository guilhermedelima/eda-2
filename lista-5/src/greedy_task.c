#include "greedy_task.h"

const char *TASK_ORDER[] = {"Earliest start time", "Earliest finish time", "Shortest size", "Fewest crashes", "NONE" };


task *create_tasks(int length);
void calculate_crashes(task *tasks, int length);
void print_tasks(task *tasks, int length);
void print_tasks_by_criterion(task *tasks, int length, task_order criterion);
task_order choose_criterion(int length);
int get_selected_tasks(task *tasks, int length, task_order criterion);
boolean check_compatibility(task *t, task **selected_tasks, int last_selected, task_order criterion);

task *create_tasks(int length){

	task *tasks;
	tasks = (task *) malloc(length * sizeof(task));

	int i, size;
	for(i=0; i<length; i++){
		tasks[i].id = i+1;
		tasks[i].init = random() % FINISH_TIME;

		size = 1 + (random() % (FINISH_TIME - tasks[i].init));
		tasks[i].size = (size > MAX_TASK_SIZE) ? MAX_TASK_SIZE : size;

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


task_order choose_criterion(int length){

	int n_selected[N_TASK_ORDER] = {0};
	int count, i, max_selected;
	task *tasks;
	task_order criterion;

	for(count=0, criterion=NONE; count <= MAX_LOOP && criterion == NONE; count++){
	
		if(count < MAX_LOOP)
			tasks = create_tasks(length);
		else{
			printf("\nCounter example");
			tasks = create_tasks_counterexample_crashes();
			length = TASK_CE_SIZE;

		}

		printf("\n\nIteration %d\n", count+1);

		max_selected=0;
		for(i=0; i<N_TASK_ORDER; i++){
			n_selected[i] += get_selected_tasks(tasks, length, i);
			printf("SELECTED TASKS BY %s :%d\n", TASK_ORDER[i], n_selected[i]);

			if( n_selected[i] > max_selected ){
				max_selected = n_selected[i];
				criterion = i;
			}else if(n_selected[i] == max_selected){
				criterion = NONE;
			}
		}

		free(tasks);
	}		
	
	return criterion;
}


int get_selected_tasks(task *tasks, int length, task_order criterion){

	int i, count;
	task **selected_tasks;

	selected_tasks = (task **) calloc(length, sizeof(task*));

	sort_tasks(tasks, length, criterion);

	count=0;
	selected_tasks[count] = &tasks[0];
	//printf("SELECTED TASK: %d - %d\n", selected_tasks[count]->init, selected_tasks[count]->end);

	for(i=1 ; i<length; i++){
		
		if( check_compatibility(&tasks[i], selected_tasks, count, criterion) == TRUE){
			count++;
			selected_tasks[count] = &tasks[i];
			//printf("SELECTED TASK: %d - %d\n", selected_tasks[count]->init, selected_tasks[count]->end);
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

task *create_tasks_counterexample_crashes(){

	task *tasks;
	tasks = (task *) malloc(TASK_CE_SIZE * sizeof(task));

	tasks[0].id = 1;
	tasks[0].init = 0;
	tasks[0].end = 4;
	tasks[0].crashes = 0;

	tasks[1].id = 2;
	tasks[1].init = 3;
	tasks[1].end = 6;
	tasks[1].crashes = 0;

	tasks[2] = tasks[1];
	tasks[2].id = 3;

	tasks[3] = tasks[1];
	tasks[3].id = 4;

	tasks[4].id = 5;
	tasks[4].init = 5;
	tasks[4].end = 8;
	tasks[4].crashes = 0;

	tasks[5].id = 6;
	tasks[5].init = 7;
	tasks[5].end = 10;
	tasks[5].crashes = 0;

	tasks[6].id = 7;
	tasks[6].init = 9;
	tasks[6].end = 12;
	tasks[6].crashes = 0;

	tasks[7].id = 8;
	tasks[7].init = 11;
	tasks[7].end = 14;
	tasks[7].crashes = 0;

	tasks[8] = tasks[7];
	tasks[8].id = 9;

	tasks[9] = tasks[7];
	tasks[9].id = 10;

	tasks[10].id = 11;
	tasks[10].init = 13;
	tasks[10].end = 16;
	tasks[10].crashes = 0;

	tasks[0].size = tasks[0].end - tasks[0].init;
	tasks[1].size = tasks[1].end - tasks[1].init;
	tasks[2].size = tasks[2].end - tasks[2].init;
	tasks[3].size = tasks[3].end - tasks[3].init;
	tasks[4].size = tasks[4].end - tasks[4].init;
	tasks[5].size = tasks[5].end - tasks[5].init;
	tasks[6].size = tasks[6].end - tasks[6].init;
	tasks[7].size = tasks[7].end - tasks[7].init;
	tasks[8].size = tasks[8].end - tasks[8].init;
	tasks[9].size = tasks[9].end - tasks[9].init;
	tasks[10].size = tasks[10].end - tasks[10].init;

	calculate_crashes(tasks, TASK_CE_SIZE);
	return tasks;
}



task *create_tasks_first_example(){

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

















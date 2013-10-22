#include "greedy_task.h"
#include <time.h>


int main(int argc, char *argv[]){

	srandom(time(NULL));

	if(argc != 2){
		fprintf(stderr, "Correct usage: %s <NUMBER OF TASKS>\n", argv[0]);
		exit(-1);
	}

	int length;
	task *tasks;

	//length = atoi(argv[1]);
	//tasks = create_tasks(length);

	length=8;
	tasks = create_tasks_PDF();

	print_tasks(tasks, length);
	check_best_order(tasks, length);

	return 0;
}

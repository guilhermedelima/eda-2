#include "greedy_task.h"
#include <time.h>

/* Main que verifica o melhor critério para o interval scheduling. 
   O número de tarefas criadas para um exemplo é passado como parâmetro. 
*/
int main(int argc, char *argv[]){

	srandom(time(NULL));

	if(argc != 2){
		fprintf(stderr, "Correct usage: %s <NUMBER OF TASKS>\n", argv[0]);
		exit(-1);
	}

	int length;
	task_order criterion;

	length = atoi(argv[1]);
	
	if(length < 3){
		fprintf(stderr, "Number of tasks must be bigger than 2\n");
		exit(-1);
	}

	criterion = choose_criterion(length);
	printf("\n\nSELECTED CRITERION: %s\n", TASK_ORDER[criterion]);

	return 0;
}

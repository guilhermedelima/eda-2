#include "greedy_task.h"

/* Cabeçalho de todas as funções */
void sort_tasks(task *tasks, int length, task_order criterion);
void merge_sort_task(int init, int end, task *vec, task_order criterion);
void merge(int init, int end, int middle, task *vec, task_order criterion);
void setup_task_order(int *val_a, int *val_b, int a, int b, task *vec, task_order criterion);


/* Função que chama o algoritmo merge_sort para ordenar um conjunto de tarefas */
void sort_tasks(task *tasks, int length, task_order criterion){
	merge_sort_task(0, length-1, tasks, criterion);
}

/* Função que implementa o merge sort para um critério específico */
void merge_sort_task(int init, int end, task *vec, task_order criterion){

	if(end > init){

		int middle;
		middle = (init+end)/2;

		merge_sort_task(init, middle, vec, criterion);
		merge_sort_task(middle+1, end, vec, criterion);

		merge(init, end, middle, vec, criterion);
	}

}

/* Função que realiza o merge dos vetores de acordo com um critério específico */
void merge(int init, int end, int middle, task *vec, task_order criterion){

	int size, i, j, count_temp, k;
	int val_i, val_j;

	size = end-init + 1;
	task temp[size];

	i=init;
	j=middle+1;
	count_temp=0;

	while(i<=middle && j<=end){

		/* Ajusta os valores que serão comparados pelo algoritmo */
		setup_task_order(&val_i, &val_j, i, j, vec, criterion);

		if(val_i > val_j){
			temp[count_temp] = vec[j];
			j++;
		}else{
			temp[count_temp] = vec[i];
			i++;
		}
		count_temp++;
	}

	while(i <= middle){
		temp[count_temp] = vec[i];
		i++;
		count_temp++;
	}

	while(j <= end){
		temp[count_temp] = vec[j];
		j++;
		count_temp++;
	}

	for(k=init; k <= end; k++)
		vec[k] = temp[k-init];
}

/* Atribui os valores que serão comparados pelo merge sort de acordo com o critério passado */
void setup_task_order(int *val_a, int *val_b, int a, int b, task *vec, task_order criterion){

	switch(criterion){
		case START:	
				*val_a = vec[a].init;
				*val_b = vec[b].init;
				break;
		case FINISH:	
				*val_a = vec[a].end;
				*val_b = vec[b].end;
				break;
		case SIZE:
				*val_a = vec[a].size;
				*val_b = vec[b].size;
				break;
		case CRASHES:
				*val_a = vec[a].crashes;
				*val_b = vec[b].crashes;
				break;
	}
}








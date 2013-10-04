#include "merge_sort.h"

int *create_vector(int length){

	int *vec, i;
	vec = (int *) calloc(length, sizeof(int));

	for(i=0; i<length; i++)
		vec[i] = random() % MAX_KEY;

	return vec;
}

void print_vector(int *vec, int length){

	printf("[ ");

	int i;
	for(i=0; i<length; i++)
		printf("%d ", vec[i]);

	printf("]\n");
}


void merge_sort(int init, int end, int *vec){

	if(end > init){
		int middle;
		middle = (init+end)/2;

		merge_sort(init, middle, vec);
		merge_sort(middle+1, end, vec);

		printf("\nMERGE\n");
		printf("VECTOR A - ");
		print_vector(vec+init, middle-init+1);
		printf("VECTOR B - ");
		print_vector(vec+middle+1, end-(middle+1)+1);

		merge(init, end, middle, vec);
	
		printf("MERGE VECTOR - ");
		print_vector(vec+init, end-init+1);

	}

}


void merge(int init, int end, int middle, int *vec){

	int size;
	size = end-init + 1;	

	int temp[size];
	int i, j, count_temp, k;

	i=init;
	j=middle+1;
	count_temp=0;

	while(i <= middle && j <= end){

		if(vec[i] > vec[j]){
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














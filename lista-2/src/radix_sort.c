#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "radix_sort.h"


int *create_vector(int length){

	int *vec, i;
	
	vec = (int *) calloc(length, sizeof(int));

	for(i=0; i<length; i++)	
		vec[i] = random() % MAX_DIGIT;

	return vec;
}

void print_vector(int *vec, int length){

	printf("[");

	int i;
	for(i=0; i<length; i++)
		printf(" %d", vec[i]);

	printf(" ]\n");

}


int *radix_sort(int *vec, int length){

	int i;
	for(i=1; i<MAX_DIGIT; i*=10){
		vec = counting_sort(vec, length, i);
		//printf("On Iteration: ");
		//print_vector(vec, length);
	}	
	
	return vec;
}


int *counting_sort(int *vec, int length, int digit){

	int vec_sum[N_ELEMENT] = { 0 };
	int *vec_sort;
	int index, new_index;

	int i;
	for(i=0; i<length; i++){
		index = (vec[i] / digit) % 10 ;
		vec_sum[index]++;
	}

	for(i=1; i<N_ELEMENT; i++)
		vec_sum[i] += vec_sum[i-1];

	vec_sort = (int *) calloc(length, sizeof(int));

	for(i=length-1; i >= 0; i--){
		index = (vec[i] / digit) % 10 ;
		new_index = --vec_sum[index];
		vec_sort[new_index] = vec[i];
	}

	free(vec);

	return vec_sort;

}







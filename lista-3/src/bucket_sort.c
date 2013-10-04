#include "bucket_sort.h"

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


void radix_sort(int *vec, int length){

	bucket_sort(vec, length, MAX_DIGIT);
	//counting_sort(vec, length, MAX_DIGIT);

}


void bucket_sort(int *vec, int length, int digit){

	if(digit && length > 1){

		int b_index, b_sum;
		int *bucket_vec;
		int bucket_size[DIGITS] = { 0 };

		counting_sort(vec, length, digit);

		int i;
		for(i=0; i<length; i++){
			b_index = (vec[i]/digit) % 10;
			bucket_size[ b_index ]++;
		}

		b_sum=0;

		for(i=0; i<DIGITS; i++){
			bucket_vec = vec + b_sum;

			if(bucket_size[i] > 1){
				printf("BUCKET - ");
				print_vector(bucket_vec, bucket_size[i]);		
			}

			bucket_sort(bucket_vec, bucket_size[i], digit/10);

			b_sum += bucket_size[i];
		}

	}

}


void counting_sort(int *vec, int length, int digit){

	int vec_sum[DIGITS] = { 0 };
	int vec_sort[length];
	int index, new_index;

	int i;
	for(i=0; i<length; i++){
		index = (vec[i] / digit) % 10 ;
		vec_sum[index]++;
	}

	for(i=1; i<DIGITS; i++)
		vec_sum[i] += vec_sum[i-1];

	for(i=length-1; i >= 0; i--){
		index = (vec[i] / digit) % 10 ;
		new_index = --vec_sum[index];
		vec_sort[new_index] = vec[i];
	}

	for(i=0; i<length; i++)
		vec[i]=vec_sort[i];

}




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "radix_sort.h"

int main(int argc, char *argv[]){

	if(argc != 2){
		fprintf(stderr, "Correct Usage: %s <VECTOR_LENGTH>\n", argv[0]);
		exit(-1);
	}

	int *vec, length;
	clock_t init, end;

	length = atoi(argv[1]);
	vec = create_vector(length);
	
	//print_vector(vec, length);

	init = clock();
	vec = radix_sort(vec, length);
	end = clock();

	//print_vector(vec, length);

	printf("%f\n", (float) (end-init) / (float) CLOCKS_PER_SEC);


	return 0;
}



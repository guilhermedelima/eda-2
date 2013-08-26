#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_vec(int *vec, int length);
void b_search(int *vec, int val, int length);

int main(){

	int length, val, *vec;

	printf("Put length'vector: ");
	scanf("%d", &length);

	vec = (int *) calloc(length, sizeof(int));	
	
	int i;
	for(i=0; i<length; i++)
		scanf("%d", vec+i);	

	print_vec(vec, length);

	printf("Value to be found: ");
	scanf("%d", &val);

	b_search(vec, val, length);

	return 0;
}


void print_vec(int *vec, int length){

	int i;
	for(i=0; i<length; i++)
		printf("%d ", *(vec+i) );
}

void b_search(int *vec, int val, int length){

	int init, end, middle;

	init = 0;
	end = length-1;

	int i;
	for(i=0; end >= init; i++){

		middle = (init+end)/2;

		if( val > *(vec+middle) )
			init = middle+1;
		else if( val < *(vec+middle) )
			end = middle-1;		
		else{
			printf("\nFound value %d after %d searches\n", *(vec+middle), i+1);
			return;
		}
	}
	
	printf("I didn't find this value\n");
}

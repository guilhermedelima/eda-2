#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct{
	int value;
	int *regst;
}p_index;

int *create_vec(int length);
p_index *create_index(int *vec, int vec_length, int n_index);
void print_index_table(p_index *table, int length);
int *search(int *vec, int offset, p_index *table, int table_length, int val);
int get_index(p_index *table, int table_length, int val);

int main(int argc, char *argv[]){

	printf("%d", teste);

	if(argc != 3){
		fprintf(stderr, "Correct usage: %s <INDEX_LENGTH> <ARRAY_LENGTH>\n", argv[0]);
		exit(-1);
	}

	int vec_length = atoi(argv[2]);
	int index_length = atoi(argv[1]);

	int offset = vec_length/index_length ;

	int *vec = create_vec(vec_length);
	p_index *i_table = create_index(vec, index_length, offset);  

	print_index_table(i_table, index_length);

	char stp;
	int op;

	do{
		
		printf("Search for: ");
		scanf("%d", &op);
		
		search(vec, offset, i_table, index_length, op);

		printf("Continue ? <y/n> ");
		scanf(" %c", &stp);

	}while(stp == 'Y' || stp == 'y');

	return 0;
}


int *create_vec(int length){

	int *vec = (int *) malloc(length * sizeof(int));
	
	int i;
	for(i=0; i<length; i++)
		*(vec+i) = i;

	return vec;
}


p_index *create_index(int *vec, int index_length, int offset){

	p_index *table = (p_index *) calloc( index_length, sizeof(p_index) );
	
	int i;
	for(i=0; i<index_length; i++){
		p_index idx;
		
		idx.value = *(vec + i*offset) ;
		idx.regst = vec + i*offset;

		table[i] = idx;
	}

	return table;

}

void print_index_table(p_index *table, int length){

	int i;
	for(i=0; i<length; i++)
		printf("%d Index %d - Value: %d\n", i, (table+i)->value, *((table+i)->regst) );

}



int *search(int *vec, int offset, p_index *table, int table_length, int val){

	int index = offset * get_index(table, table_length, val);

	int i;
	for(i=0; i<offset && index>=0; i++){

		if( val == *(vec + index+i) ){
			printf("Found value %d after %d searches\n", *(vec + index+i), i);
			return vec + index+i;
		}
	}

	printf("Didn't find this value\n");
	return NULL;

}


int get_index(p_index *table, int table_length, int val){

	int i;
	for(i=0; i<table_length; i++){

		if( val < (table+i)->value )
			break;

	}
	
	return i-1;
}

void search(int *vec, int offset, p_index *table, int table_length, int val){







}




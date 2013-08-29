#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "seq_search_pk.h"

int main(int argc, char *argv[]){

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
	int n, op;

	do{
		
		printf("1-Insert || 2-Search || 3-Delete || 4-Print Vector: ");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				break;
			case 2:
				printf("Search for: ");
				scanf("%d", &n);
				search(vec, offset, i_table, index_length, n);
				break;
			case 3:
				printf("Delete value: ");
				scanf("%d", &n);
				delete(vec, offset, i_table, index_length, n);
				free(i_table);
				i_table = create_index(vec, index_length, offset);
				print_index_table(i_table, index_length);
				printf("New Vector:\n");
				print_vec(vec, vec_length);
				break;
				
		}
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


void print_vec(int *vec, int length){

	int i;
	for(i=0; i<length; i++)
		printf("%d\n", vec[i]);
}


void print_index_table(p_index *table, int length){

	int i;
	for(i=0; i<length; i++)
		printf("%d Index %d - Value: %d\n", i, (table+i)->value, *((table+i)->regst) );

}


int get_index(p_index *table, int table_length, int val){

	int i;
	for(i=0; i<table_length; i++){

		if( val < (table+i)->value )
			break;

	}
	
	return i-1;
}


void swap_int(int *a, int *b){

	int temp = *b;
	*b = *a;
	*a = temp;
}


int *search(int *vec, int offset, p_index *table, int table_length, int val){

	int index, shift;
	
	index = get_index(table, table_length, val);
	shift = offset * index;

	int *result = NULL;

	int i;
	for(i=0; i<offset && index>=0; i++){

		if( val == *(vec + shift+i) ){
			result = vec + shift+i;
			printf("Found value %d after %d searches\n", *result, i);
			break;
		}
	}

	if(!result)
		printf("Didn't find this value\n");

	return result;

}


void delete(int *vec, int offset, p_index *table, int table_length, int val){

	int index, *element;

	element = search(vec, offset, table, table_length, val);

	if(!element)
		return;

	index = get_index(table, table_length, val);

	if( (table+index)->value == val ){
		
		int val_last_index = (table + table_length-1)->value;
		delete_index(element, offset, val_last_index);

	}else
		delete_element(element);
}


void delete_element(int *element){
	*element = INT_MAX;
}

void delete_index(int *element, int offset, int val_last_index){

	int i;
	for(i=1; i<offset && *(element + i)==INT_MAX; i++)
		printf("Percorrendo %d\n", *(element + i) );

	/* - Acha um substituto para trocar
	   - Estoura a janela sendo o ultimo index
	   - Estoura a janela e troca com próximo index */

	if( i<offset ){
		swap_int(element, element+i);
		delete_element(element+i);		
	}else if( *element < val_last_index ){
		swap_int(element, element+offset);
		delete_index(element+offset, offset, val_last_index);
	}else
		delete_element(element);

}


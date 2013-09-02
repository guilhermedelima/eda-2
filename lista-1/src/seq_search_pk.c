#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seq_search_pk.h"

int main(int argc, char *argv[]){

	if(argc != 3){
		fprintf(stderr, "Correct usage: %s <INDEX_LENGTH> <VECTOR_LENGTH>\n", argv[0]);
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
		
		printf("1-Insert || 2-Search || 3-Delete || 4-Print Vector || 5-Print Index: ");
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
				i_table = rebuild_index(i_table, vec, index_length, offset);

				print_index_table(i_table, index_length);
				printf("New Vector:\n");
				print_vec(vec, vec_length);
				break;
			case 4:
				print_vec(vec, vec_length);
				break;
			case 5:
				print_index_table(i_table, index_length);
				break;
			default:
				printf("Invalid Option\n");
				
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
		vec[i] = i;

	return vec;
}

p_index *create_index(int *vec, int index_length, int offset){

	p_index *table = (p_index *) calloc( index_length, sizeof(p_index) );
	
	int i;
	for(i=0; i<index_length; i++){
		p_index idx;
		
		idx.value = vec[i*offset] ;
		idx.regst = vec + i*offset;

		table[i] = idx;
	}

	return table;

}

p_index *rebuild_index(p_index *table, int *vec, int index_length, int offset){

	free(table);
	table = create_index(vec, index_length, offset);

	return table;
}


void print_vec(int *vec, int length){

	int i;
	for(i=0; i<length; i++){
		if( vec[i] == EMPTY)
			printf("EMPTY\n");
		else
			printf("%d\n", vec[i]);
	}
}


void print_index_table(p_index *table, int length){

	int i;
	for(i=0; i<length; i++)
		printf("Index %d\n", *( (table+i)->regst) );

}

void swap_int(int *a, int *b){

	int temp = *b;
	*b = *a;
	*a = temp;
}

int get_index(p_index *table, int table_length, int val){

	int i;
	for(i=0; i<table_length; i++){

		if( val < (table+i)->value )
			break;

	}
	
	return i-1;
}


int *search(int *vec, int offset, p_index *table, int table_length, int val){

	int index, shift;
	int *result = NULL;	

	index = get_index(table, table_length, val);
	shift = offset * index;

	int i;
	for(i=0; i<offset && index>=0; i++){

		if( val == vec[shift+i] ){
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
	*element = EMPTY;
}

void delete_index(int *element, int offset, int val_last_index){

	int i;
	for(i=1; i<offset && *(element + i)==EMPTY; i++);

	/*
	   - Acha um substituto para trocar
	   - Estoura a janela e troca com próximo index 
	   - Estoura a janela sendo o ultimo index 
	*/

	if( i<offset ){

		swap_int(element, element+i);
		delete_element(element+i);
		
	}else if( *element != val_last_index ){

		int *next = element+offset;

		if( *next == val_last_index )
			val_last_index = *element;

		swap_int(element, next);
		delete_index(next, offset, val_last_index);

	}else
		delete_element(element);

}


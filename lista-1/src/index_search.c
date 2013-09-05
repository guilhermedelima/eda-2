#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index_search.h"

int *create_vec(int length){

	int *vec = (int *) malloc(length * sizeof(int));
	
	int i;
	for(i=0; i<length; i++)
		vec[i] = i;

	return vec;
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

indexed_table *create_indexed_table(int *vec, int index_length, int window_size){

	primary_index *index_list = (primary_index *) calloc( index_length, sizeof(primary_index) );
	
	int i;
	for(i=0; i<index_length; i++){
		primary_index idx;
		
		idx.value = vec[i*window_size] ;
		idx.regst = vec + i*window_size;

		index_list[i] = idx;
	}

	indexed_table *table = malloc(1 * sizeof(indexed_table));

	table->length = index_length;
	table->window_size = window_size;
	table->list = index_list;

	return table;

}

indexed_table *rebuild_indexed_table(indexed_table *table, int *vec){

	indexed_table *new_table = create_indexed_table(vec, table->length, table->window_size);

	free(table->list);
	free(table);

	return new_table;
}

void print_indexed_table(indexed_table *table){

	int i;
	for(i=0; i < table->length; i++)
		printf("Index %d\n", (table->list[i]).value ) ;

}

int *search(indexed_table *table, int val){

	int index;
	int *result = NULL;

	index = get_index(table, val);
	
	if(index >= 0){

		int *window;
		window = table->list[index].regst;

		int i;
		for(i=0; i < table->window_size; i++){
			if(val == window[i]){
				result = window+i;
				printf("Found value %d after %d searches\n", *result, i+1);
				break;		
			}
		}
	}

	if(!result)
		printf("Didn't find this value\n");

	return result;

}

int get_index(indexed_table *table, int val){

	int i;
	for(i=0; i < table->length && !(val < table->list[i].value); i++);
	
	return i-1;
}

void swap_int(int *a, int *b){

	int temp = *b;
	*b = *a;
	*a = temp;
}


/*
  Função para deletar um elemento do vetor. Utiliza-se a técnica de deixar um espaço em branco na lista.
  A remoção pode ser realizada para um elemento comum ou um índice
*/
void delete(indexed_table *table, int val){

	int index, *element;

	element = search(table, val);

	if(!element)
		return;

	index = get_index(table, val);

	if( table->list[index].value == val ){
		
		int val_last_index;
		val_last_index = table->list[table->length-1].value;

		delete_index(element, table->window_size, val_last_index);

	}else
		delete_element(element);
}

/*
 Função para efetuar remoçao de um indíce do vetor. Existem três possibilidades:
 - Acha um substituto para trocar
 - Estoura a janela e troca com próximo index 
 - Estoura a janela sendo o ultimo index 
*/
void delete_index(int *element, int window_size, int val_last_index){

	int i;
	for(i=1; i<window_size; i++){

		if( *(element + i)!=EMPTY ){
			swap_int(element, element+i);
			delete_element(element+i);
			break;
		}
	}

	if( i == window_size ){

		if( *element != val_last_index ){

			int *next = element+window_size;

			if( *next == val_last_index )
				val_last_index = *element;

			swap_int(element, next);
			delete_index(next, window_size, val_last_index);

		}else
			delete_element(element);

	}
}

void delete_element(int *element){

	*element = EMPTY;

}


void insert(indexed_table *table, int val){

	int index, *window;
	int empty_index, bigger_index, smaller_index;
	boolean found_empty, found_bigger, found_smaller;

	found_empty = FALSE;
	found_bigger = FALSE;
	found_smaller = FALSE;

	if( (index = get_index(table, val)) < 0)
		index=0;

	window = table->list[index].regst;

	int i;
	for(i=0; i<table->window_size; i++){

		if(window[i]==EMPTY && found_empty == FALSE){
			empty_index = i;
			found_empty = TRUE;
		}

		if(window[i] > val && found_bigger == FALSE){
			bigger_index = i;
			found_bigger = TRUE;
		}

		
		if(window[i] > val && found_smaller == FALSE){
			bigger_index = i;
			found_smaller = TRUE;
		}

	}
}


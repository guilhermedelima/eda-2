#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index_search.h"

vector *create_vector(int length){

	int *vec_list = (int *) malloc( (length+1) * sizeof(int));
	
	int i;
	for(i=0; i<length; i++)
		vec_list[i] = i*2;

	vec_list[i] = LAST_BLOCK;

	vector *vec = (vector *) malloc( 1 * sizeof(vector) );

	vec->length = length;
	vec->list = vec_list;

	return vec;
}

int *rebuild_vec_list(int *vec_list, int length){

	vec_list = (int *) realloc( vec_list, (length+1) * sizeof(int) );

	return vec_list;

}

void print_vec_list(int *vec_list){

	printf("[ ");

	int i;
	for(i=0; vec_list[i]!=LAST_BLOCK; i++)
		printf("%d ", vec_list[i]);

	printf("]\n");
}

indexed_table *create_indexed_table(int *vec_list, int index_length, int window_size){

	primary_index *index_list = (primary_index *) calloc( index_length, sizeof(primary_index) );
	
	int i;
	for(i=0; i<index_length; i++){
		primary_index idx;
		
		idx.value = vec_list[i*window_size] ;
		idx.regst = vec_list + i*window_size;

		index_list[i] = idx;
	}

	indexed_table *table = malloc(1 * sizeof(indexed_table));

	table->length = index_length;
	table->window_size = window_size;
	table->list = index_list;

	return table;

}

indexed_table *rebuild_indexed_table(indexed_table *table, int *vec_list){

	indexed_table *new_table = create_indexed_table(vec_list, table->length, table->window_size);

	free(table->list);
	free(table);

	return new_table;
}

void print_indexed_table(indexed_table *table){

	int i;
	for(i=0; i < table->length; i++)
		printf("Index %d\n", (table->list[i]).value ) ;

}

void swap_int(int *a, int *b){

	int temp = *b;
	*b = *a;
	*a = temp;
}


int get_index(indexed_table *table, int val){

	int i;
	for(i=0; i < table->length && !(val < table->list[i].value); i++);
	
	return i-1;
}

int check_last_index(indexed_table *table){

	int op, *last_index;

	last_index = table->list[table->length -1].regst;

	int i;
	for(i=0; last_index[i] != LAST_BLOCK; i++);

	if(i > table->window_size)
		op = INCREASE_INDEX;
	else if(!i)
		op = REMOVE_INDEX;
	else
		op = DO_NOTHING;

	return op;

}

int *search(indexed_table *table, int val){

	int index;
	int *result = NULL;

	index = get_index(table, val);
	
	if(index >= 0){

		int *window;
		window = table->list[index].regst;

		int i;
		for(i=0; i < table->window_size && window[i]!=LAST_BLOCK; i++){
			if(val == window[i]){
				result = window+i;
				printf("Found value %d after %d searches on window\n", *result, i+1);
				break;		
			}
		}
	}

	if(!result)
		printf("Didn't find this value\n");

	return result;

}

void delete(indexed_table **table, vector *vec, int val){

	int *element, op;

	element = search(*table, val);

	if(!element)
		return;

	do{
		swap_int(element, element+1);
		element = element+1;

	}while( *(element-1) != LAST_BLOCK );

	vec->length--;
	vec->list = rebuild_vec_list(vec->list, vec->length);

	op = check_last_index(*table);

	if(op == REMOVE_INDEX)
		(*table)->length--;

	*table = rebuild_indexed_table(*table, vec->list);
	
}

void insert(indexed_table **table, vector *vec, int val){

	int index, index_to_insert, *element, op;

	index = get_index(*table, val);
	
	if(index < 0)
		index_to_insert=0;
	else{

		int *window;
		window = (*table)->list[index].regst;

		int i;
		for(i=0; i < (*table)->window_size && val >= window[i] && window[i]!=LAST_BLOCK ; i++);

		index_to_insert = i + index * (*table)->window_size;
	}

	printf("Index to insert: %d\n", index_to_insert);

	vec->length++;
	vec->list = rebuild_vec_list(vec->list, vec->length);

	vec->list[vec->length] = val;
	element = (vec->list) + vec->length;	

	int i;
	for(i=vec->length; i > index_to_insert; i-- ){
		swap_int(element, element-1);
		element = element -1;
	}

	op = check_last_index(*table);

	if(op == INCREASE_INDEX)
		(*table)->length++;

	*table = rebuild_indexed_table(*table, vec->list);

}


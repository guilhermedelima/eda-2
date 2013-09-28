#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "quick_sort.h"


linked_list *create_list(){
	
	linked_list *list;

	list = (linked_list *) malloc(1 * sizeof(linked_list));
	list->head = NULL;
	list->tail = NULL;
	list->length=0;

	return list;
}

void fill_list(linked_list *list, int length){

	int i, val;
	for(i=0; i<length; i++){
		val = random() % MAX_KEY;
		insert_node(list, val);
	}

	list->length=length;
}

void insert_node(linked_list *list, int val){

	node *element, *old_head;

	element = (node *) malloc(1 * sizeof(node));
	old_head = list->head;

	element->prev = NULL;
	element->next = old_head;	
	element->value = val;	

	if(old_head)
		old_head->prev = element;
	else
		list->tail = element;

	list->head = element;

}

void print_list(linked_list *list){

	printf("[ ");

	node *temp;
	for(temp=list->head; temp; temp=temp->next)
		printf("%d ", temp->value);

	printf("]\n");

	printf("HEAD: %d\nTAIL: %d\n", list->head->value, list->tail->value);

}

void swap_nodes(node *a, node *b, linked_list *list){

	node *a_ant = a->prev;
	node *a_suc = a->next;

	node *b_ant = b->prev;
	node *b_suc = b->next;

	a->next = b_suc;
	a->prev = b_ant;

	b->next = a_suc;
	b->prev = a_ant;

	if(!a_ant)
		list->head = b;
	else
		a_ant->next = b;

	if(!a_suc)
		list->tail = b;
	else
		a_suc = b;

	if(!b_ant)
		list->head = a;
	else
		b_ant->next = a;

	if(!b_suc)
		list->tail = a;
	else
		b_suc = a;
	
}


void quick_sort(linked_list *list){

	quick_sort_partition(list->head, list->tail, list->length, list);	

}

void quick_sort_partition(node *init, node *end, int offset, linked_list *list){

	order_partition(init, end, offset, list);



}

void order_partition(node *init, node *end, int offset, linked_list *list){

	int median;
	node *pivot, *old_median;

	old_median = init;
	pivot = find_pivot(init, end);
	median = (offset+1)/2;
	
	int i;
	for(i=0; i<median-1; i++)
		old_median = old_median->next;

	if(pivot != old_median){
		swap_nodes(pivot, old_median, list);

		if(pivot == end)
			end = old_median;

		if(pivot == init)
			init = old_median;

	}

	printf("PIVOT: %d\n", pivot->value);
	printf("OLD MEDIAN: %d\n", old_median->value);
		
	node *temp, *aux;
	for(temp=init; temp != pivot; temp=temp->next){

		if(temp->value > pivot->value){

			printf("Found %d to change\n", temp->value);
			
			while(end->value >= pivot->value)
				end = end->next;

			swap_nodes(temp, end, list);

			aux = end;
			end = temp;
			temp = aux;
		}
	}

}


node *find_pivot(node *init, node *end){

	int vec_aux[MAX_KEY] = { 0 };
	int index, sum, offset, median, median_val;
	node *temp, *pivot;

	offset=0;
	sum=0;

	int i;
	for(temp=init; temp != end->next; temp=temp->next){
		index = temp->value;
		vec_aux[index]++;
		offset++;
	}	

	median = (offset+1)/2;
	
	for(i=0; i<MAX_KEY && sum < median; i++)
		sum+=vec_aux[i];

	median_val = i-1;

	for(pivot=init; pivot->value != median_val; pivot=pivot->next);

	return pivot;

}















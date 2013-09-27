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


void remove_node(node *src, linked_list *list){

	node *ant, *suc;

	ant = src->prev;
	suc = src->next;

	if(ant)
		ant->next = suc;
	else{
		
		list->head = suc;

	}

	if(suc)
		suc->prev = ant;
	else
		list->tail = ant;

}

void insert_behind_pivot(node *pivot, node *smaller){

	pivot_ant = pivot->prev;
	
	if(pivot_ant)
		

	
	pivot->prev = smaller




}


void quick_sort(linked_list *list){

	order_pivot(list->head, list->tail);	

}

node *order_pivot(node *init, node *end){

	node *pivot, *temp;

	pivot = find_pivot(init, end);

	for(temp=init; temp!=end->next; temp=end){

		if(temp->value < pivot->value){
			




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















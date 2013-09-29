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

	if(a == b)
		return;

	if(a->next == b || b->next == a){
		adjacent_nodes(a, b, list);
		return;
	}

	node *a_pred = a->prev;
	node *a_suc = a->next;

	node *b_pred = b->prev;
	node *b_suc = b->next;

	if(!a_pred)
		list->head = b;
	else
		a_pred->next = b;

	if(!a_suc)
		list->tail = b;
	else
		a_suc->prev = b;

	if(!b_pred)
		list->head = a;
	else
		b_pred->next = a;

	if(!b_suc)
		list->tail = a;
	else
		b_suc->prev = a;

	a->next = b_suc;
	a->prev = b_pred;

	b->next = a_suc;
	b->prev = a_pred;

}

void adjacent_nodes(node *a, node *b, linked_list *list){

	node *a_pred = a->prev;
	node *a_suc = a->next;

	node *b_pred = b->prev;
	node *b_suc = b->next;

	if(a->next == b){

		if(!a_pred)
			list->head = b;
		else
			a_pred->next = b;

		if(!b_suc)
			list->tail = a;
		else
			b_suc->prev = a;

		a->next = b_suc;
		a->prev = b;

		b->next = a;
		b->prev = a_pred;

	}else if(b->next == a){
	
		if(!a_suc)
			list->tail = b;
		else
			a_suc->prev = b;

		if(!b_pred)
			list->head = a;
		else
			b_pred->next = a;

		b->next = a_suc;
		b->prev = a;

		a->next = b;
		a->prev = b_pred;

	}
}

void swap_pointers(node **a, node **b){

	node *aux = *a;

	*a = *b;
	*b = aux;
}


void quick_sort(linked_list *list){

	quick_sort_partition(list->head, list->tail, list);	

}

void quick_sort_partition(node *init, node *end, linked_list *list){

	if(init && end && init != end){

		partition_args arg;
		arg = order_partition(init, end, list);

		init = arg.new_init;
		end = arg.new_end;

		node *pivot;
		pivot = arg.pivot;

		printf("\nBeginning of this part: %d\n", init->value);
		printf("End of this part: %d\n", end->value);
		printf("Pivot of this part: %d\n\n", pivot->value);

		//quick_sort_partition(init, pivot->prev, list);
		//quick_sort_partition(pivot->next, end, list);

	}

}

partition_args order_partition(node *init, node *end, linked_list *list){

	node *temp, *last_smaller, *pivot;

	last_smaller = NULL;
	pivot = find_pivot(init, end);

	swap_nodes(pivot, end, list);
	end = pivot;

	for(temp=init; temp != end; temp=temp->next){

		if(temp->value < pivot->value){

			last_smaller = (!last_smaller) ? init : last_smaller->next;

			if(last_smaller == init)
				init = temp;

			swap_nodes(temp, last_smaller, list);
			swap_pointers(&temp, &last_smaller);
		}

	}

	last_smaller = (!last_smaller) ? init : last_smaller->next;

	if(last_smaller == init)
		init = end;

	swap_nodes(end, last_smaller, list);
	swap_pointers(&end, &last_smaller);

	partition_args arg;

	arg.new_init = init;
	arg.new_end = end;
	arg.pivot = pivot;

	return arg;
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















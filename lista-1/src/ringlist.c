#include <ringlist.h>
#include <stdio.h>
#include <stdlib.h>

RingList* ringlist_new() {
	RingList * list = calloc(1, sizeof(RingList));
	
	if (!list) 
		return (RingList *) NULL;

	list->head = NULL;
	list->size = 0;
	
	return list;
}

int _ringlist_insert_end(RingList *list, int val) {
	if(!list)
		return ERROR_NULL_LIST;

	Node *node =  node_new();
	node->val = val;

	if(!list->size) {
		list->head = node;
		list->head->next = list->head;
	} else {
		Node *travel =  NULL;
		for(travel = list->head; travel->next != list->head; travel = travel->next);
		travel->next = node;
		node->next = list->head;
	}

	list->size++;

	return OK;

}

int ringlist_fill(RingList *list, int size) {
	if(!list)
		return ERROR_NULL_LIST;
	if(list->size)
		return ERROR_NOT_EMPTY_LIST;

	int i;
	for(i = 0; i < size; i++, _ringlist_insert_end(list, i));

	return OK;
}

int ringlist_print(RingList *list) {
	if(!list)
		return ERROR_NULL_LIST;

	Node *travel =  NULL;
	printf("[");
	for(travel = list->head; travel->next != list->head; travel = travel->next) {
		printf("%d, ", travel->val);
	}
	printf("]\n");

	return OK;
}

int ringlist_search(RingList *list, int val) {
	if(!list)
		return ERROR_NULL_LIST;

	if(list->size)
		return ERROR_NOT_EMPTY_LIST;

	// TO DO

	return OK;
}
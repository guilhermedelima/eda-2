#include <ringlist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

RingList* ringlist_new(unsigned int capacity) {
	if (capacity < 1)
		return NULL;

	RingList * list = calloc(1, sizeof(RingList));

	list->values = calloc(capacity, sizeof(int));;
	list->size = 0;
	list->capacity = capacity;
	
	return list;
}

int _ringlist_increase_capacity(RingList *list, unsigned int new_capacity)
{
	if(!list)
		return ERROR_NULL_LIST;
	if(new_capacity <= list->capacity)
		return ERROR_NEW_CAPACITY_LESS_THAN_ACTUAL;

	int *new_values = calloc(new_capacity, sizeof(int));
	
	int i;
	for(i = 0; i < list->size; i++) 
		new_values[i] = list->values[i];

	free(list->values);
	list->values = new_values;

	list->capacity = new_capacity;

	return OK;
}

int _ringlist_move_cells(RingList *list, unsigned int low_index, direction dir) {
	if(!list)
		return ERROR_NULL_LIST;

	if (dir == FRONT) {
		if (list->size > 1) {
			int i;
			for (i = list->size; i > low_index; i--)
				list->values[i] = list->values[i-1];
		} else {
			list->values[1] = list->values[0];
		}
	
	} else {
		if (list->size > 1) {
			int i;
			for (i = low_index; i < list->size-1; i++)
				list->values[i] = list->values[i+1];
		} 	
	}
		
	return OK;
}

int ringlist_insert(RingList *list, int val) {
	if(!list)
		return ERROR_NULL_LIST;
	
	if(list->size >= list->capacity) 
		_ringlist_increase_capacity(list, list->capacity + (list->capacity/2));
	
	if (list->size == 0) {
		list->values[0] = val;
		list->size++;
	} else if (val > list->values[list->size-1]) {
		list->values[list->size] = val;
		list->size++;
	} else {
		int i;
		for (i = 0; i < list->size; ++i) {
			if (val <= list->values[i]) {
				_ringlist_move_cells(list, i, FRONT);
				list->values[i] = val;
				list->size++;

				break;
			} 
		}	
	}

	return OK;
}

int ringlist_remove_byindex(RingList *list, unsigned int index) {
	if(!list)
		return ERROR_NULL_LIST;
	if(list->size == 0)
		return ERROR_EMPTY_LIST;

	if(list->size == 1) {
		list->size--;
	} else {
		_ringlist_move_cells(list, index % list->size, BACK);	
		list->size--;
	}

	return OK;
}

int ringlist_remove_byvalue(RingList *list, int val) {
	if(!list)
		return ERROR_NULL_LIST;
	if(list->size == 0)
		return ERROR_EMPTY_LIST;

	if(list->size == 1 && val == list->values[0]) {
		list->size--;
	} else {
		int index = ringlist_bsearch(list, val);
		if (index == ERROR_NOT_FOUND) {
			return ERROR_NOT_FOUND;
		} else {
			_ringlist_move_cells(list, index, BACK);			
			list->size--;
		}	
	}

	return OK;
}

int ringlist_get(RingList *list, unsigned int index) {
	if(!list)
		return ERROR_NULL_LIST;
	if(list->size == 0)
		return ERROR_EMPTY_LIST;

	return list->values[index % list->size];
}


int ringlist_fill(RingList *list, unsigned long long int range) {
	if(!list)
		return ERROR_NULL_LIST;

	int i;
	for(i = 0; i < range; i++)
		ringlist_insert(list, i*5);

	return OK;
}

int ringlist_print(RingList *list) {
	if(!list)
		return ERROR_NULL_LIST;
	
	if(list->size == 0) {
		printf("Values = []\n");
	} else if (list->size <= 1000) {
		int i;
		printf("Values = [");
		for(i = 0; i < list->size - 1; i++) {
			printf("%d, ", list->values[i]);
		}
		printf("%d]\n", list->values[list->size-1]);	
	} else {
		printf("Values = [...]\n");
	} 

	
	printf("Size = %d\nCapacity = %d\n", list->size, list->capacity);

	return OK;
}

int ringlist_bsearch(RingList *list, int val) {
	if(!list)
		return ERROR_NULL_LIST;
	if(!list->size)
		return ERROR_NOT_FOUND;
	int low, high, mid;
	low = 0;
	high = list->size-1;
	
	int i = 0;
	while (low <= high) {
		mid = low + ((high-low) / 2);

		if (val < list->values[mid]) {
			high = mid - 1;
		} else if (val > list->values[mid]) {
			low = mid + 1;
		} else {
			printf("Search loops = %d\n", i);
			return mid;
		}
		i++;
	}
	printf("Search loops = %d\n", i);

	return ERROR_NOT_FOUND;
}

int ringlist_interpolsearch(RingList *list, int val) {
	if(!list)
		return ERROR_NULL_LIST;
	if(!list->size)
		return ERROR_NOT_FOUND;
	int low, high, mid;
	low = 0;
	high = list->size-1;
	
	int i = 0;
	while (low <= high) {
		mid = low + (high-low) * ((val - list->values[low]) / (list->values[high] - list->values[low]));

		if (val < list->values[mid]) {
			high = mid - 1;
		} else if (val > list->values[mid]) {
			low = mid + 1;
		} else {
			printf("Search loops = %d\n", i);
			return mid;
		}
		i++;
	}
	printf("Search loops = %d\n", i);

	return ERROR_NOT_FOUND;	
}
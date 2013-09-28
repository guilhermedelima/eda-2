#include <heapsort.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Vector* vector_new(unsigned int capacity) {
	if (capacity < 1)
		return NULL;

	Vector *v = calloc(1, sizeof(Vector));
	v->v = calloc(capacity, sizeof(int));
	v->capacity = capacity;
	v->size = 0;

	return v;
} 

int _vector_increase(Vector *v) {
	if(!v)
		return ERROR_NULL_VECTOR;

	v->v = realloc(v->v, v->capacity * 2);

	return OK;
}

inline int _r_son (int i) {return (2*i) + 2;}
inline int _l_son (int i) {return (2*i) + 1;}
inline int _parent(int i) {return (i-1) / 2;}

int vector_insert(Vector *v, int val) {
	if (!v) 
		return ERROR_NULL_VECTOR;
	if (v->size == v->capacity)
		_vector_increase(v);

	v->v[v->size] = val;
	v->size++;

	return OK;
}

int vector_fill(Vector *v) {
	if (!v) 
		return ERROR_NULL_VECTOR;

	srand(time(0));

	unsigned int i;
	for(i = 0; i < v->capacity; i++) 
		vector_insert(v, rand() % (v->capacity*10));

	return OK;
}

int vector_print(Vector *v) {
	if(!v)
		return ERROR_NULL_VECTOR;
	
	if(v->size == 0) {
		printf("[]\n");
	} else {
		unsigned int i;
		printf("[");
		for(i = 0; i < v->size - 1; i++) {
			printf("%d, ", v->v[i]);
		}
		printf("%d]\n", v->v[v->size-1]);
	} 

	return OK;
}

inline int _swap(int *a, int *b) {

	int temp = *a;
	*a = *b;
	*b = temp;
	
	return OK;
}

int _vector_heapify(Vector *v, int heapsize, int index) {
	if(!v) 
		return ERROR_NULL_VECTOR;
	if(!v->size)
		return ERROR_EMPTY_VECTOR;
	if(index >= v->size)
		return ERROR_INVALID_INDEX;

	int left, right, biggest;
	left = _l_son(index);
	right = _r_son(index);

	if ((left < heapsize) && (v->v[left] > v->v[index]))
		biggest = left;
	else
		biggest = index;

	if ((right < heapsize) && (v->v[right] > v->v[biggest]))
		biggest =  right;
	
	if (biggest != index) {
		_swap(&v->v[biggest], &v->v[index]);
		_vector_heapify(v, heapsize, biggest);
	}

	return OK;
}

int _vector_build_heap(Vector *v) {
	if(!v)
		return ERROR_NULL_VECTOR;
	if(!v->size)
		return ERROR_EMPTY_VECTOR;

	int i;
	
	for(i = (int) floor(v->size/2); i >= 0; i--) {
		_vector_heapify(v, v->size, i);
	}

	return OK;
}

int vector_heapsort(Vector *v) {
	if(!v)
		return ERROR_NULL_VECTOR;
	if(!v->size)
		return ERROR_EMPTY_VECTOR;

	int heapsize = v->size;
	
	_vector_build_heap(v);

	int i;
	for (i = v->size - 1; i >= 1; i--) {
		_swap(&v->v[0], &v->v[i]);
		heapsize--;
		_vector_heapify(v, heapsize, 0);
	}

	return OK;
}

int heap_insert(Vector *h, int val) {
	if(!h)
		return ERROR_NULL_VECTOR;
	if(h->size == h->capacity)
		_vector_increase(h);

	int temp = h->size;
	while (temp > 0 && h->v[_parent(temp)] < val) {
		h->v[temp] = h->v[_parent(temp)];
		temp = _parent(temp);
    }
    h->v[temp] = val;
    h->size++;
	  
	return OK;
}

/*FindMinInMaxHeap(Heap heap)
   startIndex = heap->Array[heap->lastIndex/2]
   if startIndex == 0
          return heap->Array[startIndex]
   Minimum = heap->Array[startIndex + 1]
   for count from startIndex+2 to heap->lastIndex
            if(heap->Array[count] < Minimum)
                Minimum := heap->Array[count]
   print Minimum */

// int heap_remove_min(Vector *h, int *removed_val) {
// 	if(!h)
// 		return ERROR_NULL_VECTOR;
// 	if(!h->size)
// 		return ERROR_EMPTY_VECTOR;

// 	int start = _parent(h->size);
// 	if (start == 0) {
// 		*removed_val = h->v[start];
// 		h->v[start] = 0;
// 		return OK;
// 	}

// 	int min_index = start + 1;
// 	int min = h->v[min_index];
// 	int i;
	
// 	for (i = start+2; i < h->size; i++) {
// 		if(h->v[i] < min) {
// 			min = h->v[i];
// 			min_index = i;
// 		}
// 		printf("MIN %d\n", min);		
// 	}

// 	*removed_val = min;
// 	h->v[min_index] = 0;

// 	return OK;
// }

int heap_remove_max(Vector *h, int *removed_val) {
	if(!h)
		return ERROR_NULL_VECTOR;
	if(!h->size)
		return ERROR_EMPTY_VECTOR;

	*removed_val = h->v[0];
	h->v[0] = h->v[h->size-1];
	h->size--;
	_vector_build_heap(h);

	return OK;
}

int heap_fill(Vector *h) {
	if (!h) 
		return ERROR_NULL_VECTOR;

	srand(time(0));

	unsigned int i;
	for(i = 0; i < h->capacity; i++) 
		heap_insert(h, rand() % (h->capacity*10));

	return OK;
}

int vector_revert(Vector *v) {
	if(!v)
		return ERROR_NULL_VECTOR;
	if(!v->size)
		return ERROR_EMPTY_VECTOR;

	int i, j;
	for (i = 0, j = v->size-1; i < j; i++, j--)
		_swap(&v->v[i], &v->v[j]);
	
		

	return OK;
}

int heap_move_roots_to_vector(Vector *h, Vector *v) {
	if (!h || !v) 
		return ERROR_NULL_VECTOR;	
	if(!h->size)
		return ERROR_EMPTY_VECTOR;
	
	int max;
	int i;
	int heap_pre_size = h->size;
	for (i = 0; i < heap_pre_size; i++) {
		heap_remove_max(h, &max);
		vector_insert(v, max);
	}
	vector_revert(v);

	return OK;
}
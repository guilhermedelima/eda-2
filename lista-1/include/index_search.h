#ifndef SEQ_SEARCH_PK_H_INCLUDED
#define SEQ_SEARCH_PK_H_INCLUDED

#include <limits.h>

#define EMPTY INT_MAX

typedef enum{TRUE=1, FALSE=0}boolean;

typedef struct{
	int value;
	int *regst;
}primary_index;

typedef struct{
	int length;
	int window_size;
	primary_index *list;
}indexed_table;


extern int *create_vec(int length);
extern void print_vec(int *vec, int length);

extern indexed_table *create_indexed_table(int *vec, int index_length, int window_size);
extern indexed_table *rebuild_indexed_table(indexed_table *table, int *vec);
extern void print_indexed_table(indexed_table *table);

extern int *search(indexed_table *table, int val);
extern int get_index(indexed_table *table, int val);

extern void delete(indexed_table *table, int val);
extern void delete_index(int *element, int window_size, int val_last_index);
extern void delete_element(int *element);
extern void swap_int(int *a, int *b);

#endif

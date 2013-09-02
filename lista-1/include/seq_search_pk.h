#ifndef SEQ_SEARCH_PK_H_INCLUDED
#define SEQ_SEARCH_PK_H_INCLUDED

#include <limits.h>

#define EMPTY INT_MAX

typedef struct{
	int value;
	int *regst;
}p_index;

int *create_vec(int length);
void print_vec(int *vec, int length);
p_index *create_index(int *vec, int vec_length, int n_index);
p_index *rebuild_index(p_index *table, int *vec, int index_length, int offset);
void print_index_table(p_index *table, int length);
int get_index(p_index *table, int table_length, int val);
int *search(int *vec, int offset, p_index *table, int table_length, int val);
void delete(int *vec, int offset, p_index *table, int table_length, int val);
void delete_element(int *element);
void delete_index(int *element, int offset, int val_last_index);


#endif

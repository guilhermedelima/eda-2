/*
	Header que define as funções e estruturas referentes a busca por índices primários
	Inserção e remoção não utiliza técnica de deixar buracos pelo vetor

*/



#ifndef SEQ_SEARCH_PK_H_INCLUDED
#define SEQ_SEARCH_PK_H_INCLUDED

#include <limits.h>

#define LAST_BLOCK INT_MAX

#define REMOVE_INDEX 1
#define INCREASE_INDEX 2
#define DO_NOTHING 3

//Estrutura para armazenar as informações do vetor (tamanho + valores)
typedef struct{
	int length;
	int *list;
}vector;

//Estrutura para o índice primário (kindex + ponteiro para registro)
typedef struct{
	int value;
	int *regst;
}primary_index;

//Estrutura que representa a tabela de índices primários
typedef struct{
	int length;
	int window_size;
	primary_index *list;
}indexed_table;

extern vector *create_vector(int length);
extern int *rebuild_vec_list(int *vec_list, int length);
extern void print_vec_list(int *vec_list);

extern indexed_table *create_indexed_table(int *vec_list, int index_length, int window_size);
extern indexed_table *rebuild_indexed_table(indexed_table *table, int *vec_list);
extern void print_indexed_table(indexed_table *table);

extern int get_index(indexed_table *table, int val);
extern int check_last_index(indexed_table *table);
extern void swap_int(int *a, int *b);

extern int *search(indexed_table *table, int val);
extern void delete(indexed_table **table, vector *vec, int val);
extern void insert(indexed_table **table, vector *vec, int val);

#endif

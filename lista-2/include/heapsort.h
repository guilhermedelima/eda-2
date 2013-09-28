/* 
	Cabeçalho heapsort.h

	Cabeçalho com as definições para o algoritmo Heapsort.
*/

#ifndef HEAPSORT_H
#define HEAPSORT_H

// CÓDIGOS DE RETORNO
#define OK 1
#define ERROR_NULL_VECTOR -100
#define ERROR_MEMMORY_ALLOC -101
#define ERROR_EMPTY_VECTOR -104
#define ERROR_INVALID_INDEX -105

// DEFINIÇÕES
typedef enum _boolean {true=1, false=0} boolean;
typedef struct _Vector
{
	int *v;
	unsigned int size;
	unsigned int capacity;
} Vector;

// FUNÇÕES PÚBLICAS
// Comuns ao modo normal e ao modo com estrutura separada
extern Vector* vector_new(unsigned int capacity); 
extern int vector_fill(Vector *v);
extern int vector_print(Vector *v);
extern int vector_insert(Vector *v, int val);
// Modo normal
extern int vector_heapsort(Vector *v);
// Modo com estrutura separada
extern int heap_insert(Vector *h, int val);
extern int heap_fill(Vector *h);
extern int heap_remove_max(Vector *h, int *removed_val);
extern int heap_move_roots_to_vector(Vector *h, Vector *v);

#endif
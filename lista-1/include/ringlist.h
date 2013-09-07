/* 
	Cabeçalho ringlist.c

	Cabeçalho com as definições de estruturas, constantes e assinaturas de funções para uma estrutura 'ringlist'.
*/

#ifndef RINGLIST_H
#define RINGLIST_H

// Códigos de retorno
#define OK 1
#define ERROR_NULL_LIST -100
#define ERROR_MEMMORY_ALLOC -101
#define ERROR_NOT_FOUND -103
#define ERROR_NEW_CAPACITY_LESS_THAN_ACTUAL -104
#define ERROR_INVALID_CAPACITY -105
#define ERROR_EMPTY_LIST -107

// Definições
typedef enum _direction {FRONT=1, BACK=2} direction;
typedef enum _boolean {true=1, false=0} boolean;
typedef struct _RingList
{
	int *values;
	unsigned int size;
	unsigned int capacity;
} RingList;

// Funções públicas
extern RingList* ringlist_new(unsigned int capacity); 
extern int ringlist_fill(RingList *list, unsigned long long int size);
extern int ringlist_print(RingList *list);
extern int ringlist_bsearch(RingList *list, int val);
extern int ringlist_interpolsearch(RingList *list, int val);
extern int ringlist_insert(RingList *list, int val);
extern int ringlist_remove_byindex(RingList *list, unsigned int index);
extern int ringlist_remove_byvalue(RingList *list, int val);
extern int ringlist_get(RingList *list, unsigned int index);

#endif
#ifndef RINGLIST_H
#define RINGLIST_H

// Return Codes
#define OK 1
#define ERROR_NULL_LIST -100
#define ERROR_MEMMORY_ALLOC -101
#define ERROR_NOT_FOUND -103
#define ERROR_NEW_CAPACITY_LESS_THAN_ACTUAL -104
#define ERROR_INVALID_CAPACITY -105
#define ERROR_INVALID_INDEX -106
#define ERROR_EMPTY_LIST -107

// Definitions
typedef enum _direction {FRONT=1, BACK=2} direction;
typedef enum _boolean {true=1, false=0} boolean;
typedef struct _RingList
{
	int *values;
	int size;
	int capacity;
} RingList;

// Public functions
extern RingList* ringlist_new(int capacity); 
extern int ringlist_fill(RingList *list, int size);
extern int ringlist_print(RingList *list);
extern int ringlist_bsearch(RingList *list, int val);
extern int ringlist_insert(RingList *list, int val);
extern int ringlist_remove_index(RingList *list, int index);
extern int ringlist_remove_value(RingList *list, int val);
extern int ringlist_get(RingList *list, int index);

#endif
#ifndef RINGLIST_H
#define RINGLIST_H

#include <node.h>
#include <ringlist-common.h>

typedef struct _RingList
{
	Node *head;
	int size;	
} RingList;

extern RingList* ringlist_new(); 
extern int ringlist_fill(RingList *list, int size);
extern int ringlist_print(RingList *list);
extern int ringlist_search(RingList *list, int val);
// extern int ringlist_insert(RingList *list, int val);
// extern int ringlist_remove(RingList *list, int val);
// extern int ringlist_delete(RingList *list, int val);

#endif
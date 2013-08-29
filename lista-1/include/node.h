#ifndef NODE_H
#define NODE_H

#include <ringlist-common.h>

typedef struct _Node
{
	int val;
	struct _Node *next;
} Node;

extern Node* node_new();

#endif
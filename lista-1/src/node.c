#include <node.h>
#include <stdlib.h>

Node* node_new() {
	Node * node = calloc(1, sizeof(Node));

	if (!node) 
		return (Node*) NULL;

	node->next = NULL;
	node->val = 0;

	return node;
}
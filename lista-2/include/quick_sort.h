#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#define MAX_KEY 50


struct node_linked_list{
	int value;
	struct node_linked_list *next;
	struct node_linked_list *prev;
};

typedef struct node_linked_list node;

typedef struct{
	node *head;
	node *tail;
	int length;
}linked_list;


extern linked_list *create_list();
extern void fill_list(linked_list *list, int length);
extern void insert_node(linked_list *list, int val);
extern void print_list(linked_list *list);
extern void quick_sort(linked_list *list);
extern void order_pivot(node *init, node *end);
extern node *find_pivot(node *init, node *end);



#endif

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdio.h>
#include <stdlib.h>

#define ANSI_RED	"\x1b[31m"
#define ANSI_BLACK	"\033[22;30m"
#define ANSI_DEFAULT	"\033[0m"

typedef enum{
	LEFT, RIGHT, NONE
}direction;

typedef enum{
	BLACK, RED
}node_color;

struct node_rbt{
	int value;
	node_color color;
	struct node_rbt *left;
	struct node_rbt *right;
	struct node_rbt *parent;

};

typedef struct node_rbt node;

typedef struct{
	node *root;
}rb_tree;


extern const char *shell_colors[];
extern const node nill_val;
extern const node *nill;

extern rb_tree *create_tree();
extern void print_tree_as_list(node *root);
extern void print_node(node *n, int level);
extern void print_tree(node *root);

extern node *get_grand(node *n);
extern node *get_uncle(node *n);
extern direction get_node_direction(node *n);
extern node *create_node(int val);

extern void left_rotate(node *n, node **root);
extern void right_rotate(node *n, node **root);

extern void insert(node **root, int val);
extern void insert_root(node **root, int val);
extern node *insert_node(node *dad, int val);
extern void fix_red_dad(node *n, node **root);
extern void fix_red_uncle(node *n, node *u, node *g);
extern node *fix_with_rotations(node *n, node *g, node **root);

extern void delete(node **root, int val);
extern node* search(node **root, int val);

#endif












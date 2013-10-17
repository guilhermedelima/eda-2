#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

extern void insert(rb_tree *tree, int val);
extern node *search(node *root, int val);
extern void delete(rb_tree *tree, int val);

extern void verify_properties(rb_tree *tree);

#endif












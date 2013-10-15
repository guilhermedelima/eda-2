#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdio.h>
#include <stdlib.h>

#define ANSI_RED	"\x1b[31m"
#define ANSI_BLACK	"\033[22;30m"
#define ANSI_DEFAULT	"\033[0m"


typedef enum{
	black, red
}node_color;

struct node_rbt{
	int value;
	node_color color;
	struct node_rbt *left;
	struct node_rbt *right;
	struct node_rbt *parent;

};

typedef struct node_rbt node;

extern const char *shell_colors[];
extern const node nill;


extern node *search(node *root, int val);



#endif

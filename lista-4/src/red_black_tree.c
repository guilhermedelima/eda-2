#include "red_black_tree.h"

const char *shell_colors[] = { ANSI_BLACK, ANSI_RED };
const node nill_val = {0, BLACK, NULL, NULL, NULL};
const node *nill = &nill_val;


/*
  Função para criar uma árvore com raiz nula
*/
rb_tree *create_tree(){

	rb_tree *tree;
	tree = (rb_tree *) calloc(1, sizeof(rb_tree));

	tree->root = NULL;

	return tree;
}

void print_tree(node *root){

	print_node(root,0);

}

void print_node(node *n, int level){

	if(n && n!=nill){
		printf("%s%*d\n" ANSI_DEFAULT, shell_colors[n->color], level, n->value);
		print_node(n->left, level+5);
		print_node(n->right, level+5);
	}else
		printf("%*c\n", level, '-');

}


node *get_grand(node *n){

	node *g;

	g = (n && n->parent) ? n->parent->parent : NULL;

	return g;
}

node *get_uncle(node *n){

	node *g, *u;

	g = get_grand(n);

	if(g)
		u = (g->left == n->parent) ? g->right : g->left;
	else
		u = NULL;
	
	return u;		
}

direction get_node_direction(node *n){

	direction d;

	if(!n || !n->parent)
		d = NONE;
	else if(n->parent->left == n)
		d = LEFT;
	else
		d = RIGHT;

	return d;
}


node *create_node(int val){

	node *n;
	n = (node *) malloc(sizeof(node));

	n->value = val;
	n->color = RED;
	n->parent = NULL;
	n->left = (node *) nill;
	n->right = (node *) nill;

	return n;
}


void left_rotate(node *n, node **root){

	node *dad, *sub_tree, *new_node;
	direction n_dir;

	new_node = n->right;
	dad = n->parent;
	sub_tree = new_node->left;		
	n_dir = get_node_direction(n);

	if(new_node == nill)
		return;
	else
		n->parent = new_node;	

	n->right = sub_tree;

	if(sub_tree != nill)
		sub_tree->parent = n;
		
	new_node->left = n;
	new_node->parent = dad;

	if(n_dir == RIGHT)
		dad->right = new_node;
	else if(n_dir == LEFT)
		dad->left = new_node;		
	else
		*root = new_node;
}



void right_rotate(node *n, node **root){

	node *dad, *sub_tree, *new_node;
	direction n_dir;

	new_node = n->left;
	dad = n->parent;
	sub_tree = new_node->right;		
	n_dir = get_node_direction(n);

	if(new_node == nill)
		return;
	else
		n->parent = new_node;	

	n->left = sub_tree;

	if(sub_tree != nill)
		sub_tree->parent = n;
		
	new_node->right = n;
	new_node->parent = dad;

	if(n_dir == RIGHT)
		dad->right = new_node;
	else if(n_dir == LEFT)
		dad->left = new_node;		
	else
		*root = new_node;
}



void insert(node **root, int val){

	if(!*root)
		insert_root(root, val);
	else{

		node *dad, *kid, *new_node;
		kid = *root;

		while(kid != nill){
			dad = kid;
			kid = (val > kid->value) ? kid->right : kid->left;
		}
	
		new_node = insert_node(dad, val);

		if(dad->color == RED)
			fix_red_dad(new_node, root);
			
	}

}


void insert_root(node **root, int val){

	*root = create_node(val);
	(*root)->color = BLACK;

}

node *insert_node(node *dad, int val){

	node *n;
	n = create_node(val);

	if(val > dad->value)
		dad->right = n;
	else
		dad->left = n;

	n->parent = dad;
	return n;
}


void fix_red_dad(node *n, node **root){


	while(n->parent && n->parent->color == RED){

		node *u, *g;
		u = get_uncle(n);
		g = get_grand(n);

		if(u->color == RED){
			fix_red_uncle(n, u, g);
			n = g;
		}else
			n = fix_with_rotations(n, g, root);

	}

}

void fix_red_uncle(node *n, node *u, node *g){

	u->color = BLACK;
	n->parent->color = BLACK;
	g->color = (!g->parent) ? BLACK : RED ;

}

node *fix_with_rotations(node *n, node *g, node **root){

	direction n_dir, p_dir;
	n_dir = get_node_direction(n);
	p_dir = get_node_direction(n->parent);

	if(p_dir != n_dir){
		n = n->parent;

		if(p_dir == LEFT && n_dir == RIGHT)
			left_rotate(n, root);			
		else if(p_dir == RIGHT && n_dir == LEFT)
			right_rotate(n, root);
	}
	
	n->parent->color = BLACK;
	g->color = RED;

	n_dir = get_node_direction(n);
	p_dir = get_node_direction(n->parent);

	if(p_dir == LEFT && n_dir == LEFT)
		right_rotate(g, root);
	else if(p_dir == RIGHT && n_dir == RIGHT)
		left_rotate(g, root);

	return n;
}








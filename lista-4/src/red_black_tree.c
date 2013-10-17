#include "red_black_tree.h"


/* Constante para representar o vetor de cores que são acessados de acordo com o tipo BLACK ou RED */
const char *shell_colors[] = { ANSI_BLACK, ANSI_RED };

/* Ponteiro global para nill (constante)*/
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

/* 
   Função que imprime os nós de acordo como se fosse uma lista.
*/
void print_tree_as_list(node *root){

	if(root && root!=nill){
		print_tree_as_list(root->left);
		printf("%s%d " ANSI_DEFAULT, shell_colors[root->color], root->value);
		print_tree_as_list(root->right);
	}

}

/* 
   Imprime a raiz e seus filhos recursivamente a partir da identação 0
*/
void print_tree(node *root){

	print_node(root,0);

}

/* 
   Função que imprime os nós de acordo com sua altura na árvore
   A cada nível são impressos o filho esquerdo e seus filhos (com identação maior), o filho direito e seus filhos
   As cores também são impressas 
*/
void print_node(node *n, int level){

	if(n && n!=nill){
		printf("%s%*d\n" ANSI_DEFAULT, shell_colors[n->color], level, n->value);
		print_node(n->left, level+5);
		print_node(n->right, level+5);
	}else
		printf("%*c\n", level, '-');

}

/* 
   Função que retorna o avô do nó
*/
node *get_grand(node *n){

	node *g;

	g = (n && n->parent) ? n->parent->parent : NULL;

	return g;
}

/* 
   Função que retorna o tio do nó
*/
node *get_uncle(node *n){

	node *g, *u;

	g = get_grand(n);

	if(g)
		u = (g->left == n->parent) ? g->right : g->left;
	else
		u = NULL;
	
	return u;		
}

/* 
   Função para descobrir se o nó é um filho a esquerda ou direita
*/
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

/* 
   Função para criar um nó vermelho com filhos nill
*/
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

/* 
   Função para rotacionar nó para esquerda
*/
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


/* 
   Função para rotacionar nó para direita
*/
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


/* 
  Função para inserir um nó na árvore. São tratados os seguintes casos
  1: Nó é a raiz
  2: Pai do nó é preto (Não precisa consertar árvore)
  3: Pai do Nó é vermellho e tio também (Muda cor de avô e continua verificando casos 3, 4 e 5)
  4: Pai do Nó é vermellho e tio preto (Pai e filho tem mesmas "direções" - Rotação dupla (1 + caso 5))
  5: Pai do Nó é vermellho e tio preto (Pai e filho diferentes "direções" - 1 rotação )

*/
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

		/* Quando o no é vermelho tem que manter as propriedades da árvore */
		if(dad->color == RED)
			fix_red_dad(new_node, root);
			
	}

}

/* 
   Função para inserir raiz da árvore
*/
void insert_root(node **root, int val){

	*root = create_node(val);
	(*root)->color = BLACK;

}

/* 
   Função para inserir nó vermelho nas extremidades
*/
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

/* 
   Função para tratar inserção enquanto o pai do novo nó for vermelho
*/
void fix_red_dad(node *n, node **root){

	/* Trata os casos enquanto as propriedades da árvore não forem mantidas*/
	while(n->parent && n->parent->color == RED){

		node *u, *g;
		u = get_uncle(n);
		g = get_grand(n);

		/* trata caso 3 para tio vermelho e casos 4 e/ou 5 para tio preto */
		if(u->color == RED){
			fix_red_uncle(n, u, g);
			n = g;
		}else
			n = fix_with_rotations(n, g, root);

	}

}

/* 
   Função para tratar caso 3 da inserção. 
   Se avô não for raiz volta para a função fix_red_dad e pode ser tratado pelos casos 3 ou 4 e/ou 5
   Se Avô for raiz então sua cor será preta 
*/
void fix_red_uncle(node *n, node *u, node *g){

	u->color = BLACK;
	n->parent->color = BLACK;
	g->color = (!g->parent) ? BLACK : RED ;

}

/* 
   Função para tratar casos 4 e 5 da inserção
*/
node *fix_with_rotations(node *n, node *g, node **root){

	direction n_dir, p_dir;
	n_dir = get_node_direction(n);
	p_dir = get_node_direction(n->parent);

	/* 
	   Caso 4: Pai é filho Esquerdo e N também é filho esquerdo
	   Ou Pai é filho Direito e N também é filho Direito
	   Após sair do if cai no caso 5, realizando então rotação dupla
	*/
	if(p_dir != n_dir){
		n = n->parent;

		if(p_dir == LEFT && n_dir == RIGHT)
			left_rotate(n, root);			
		else if(p_dir == RIGHT && n_dir == LEFT)
			right_rotate(n, root);
	}
	
	/* 
	   Caso 5: Pai é filho Esquerdo e N é filho Direito
	   Ou Pai é filho Direito e N é filho Esquerdo
	   Após esta rotação a árvore mantém suas propriedades devidamente
	*/

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

node * search(node **root, int val) {
	node *n = *root;
	
	while (n != nill) {
		if (n->value == val)
			return n;
		else if (val < n->value)
			n = n->left;
		else if (val > n->value)
			n = n->right;
	}
	
	return NULL;
}

node * minimum_node(node *n) {
	if(n == nill)
		return n;

	node * temp = n;
	while (temp->left != nill) {
		temp = temp->left;
	}

	return temp;
}

node *get_sibling(node *n) {
	if (n->parent == NULL) 
		return NULL;

	direction dir = get_node_direction(n);

	return (dir == LEFT) ? n->parent->right : n->parent->left;
}

void delete_case6(node *n, node **root)
{
	node *sibling = get_sibling(n);

	sibling->color = n->parent->color;
	n->parent->color = BLACK;

	printf("caso 6\n");
	if (n == n->parent->left) {
		sibling->right->color = BLACK;
		left_rotate(n->parent, root);
	} else {
		sibling->left->color = BLACK;
		right_rotate(n->parent, root);
	}
}

void delete_case5(node *n, node **root)
{
	node *sibling = get_sibling(n);

	printf("caso 5\n");
	if  (sibling->color == BLACK) { 
		if ((n == n->parent->left) &&
			(sibling->right->color == BLACK) &&
			(sibling->left->color == RED)) { 
			sibling->color = RED;
			sibling->left->color = BLACK;
			right_rotate(sibling, root);
		} else if ((n == n->parent->right) &&
				    (sibling->left->color == BLACK) &&
				    (sibling->right->color == RED)) {
			sibling->color = RED;
			sibling->right->color = BLACK;
			left_rotate(sibling, root);
		}
	}
	delete_case6(n, root);
}

void delete_case4(node *n, node **root)
{
	node *sibling = get_sibling(n);

	printf("caso 4\n");
	if ((n->parent->color == RED) &&
		(sibling->color == BLACK) &&
		(sibling->left->color == BLACK) &&
		(sibling->right->color == BLACK)) {
	sibling->color = RED;
	n->parent->color = BLACK;
	} else {

		delete_case5(n, root);	
	}
	
}

void delete_case1(node *n, node **root);
void delete_case3(node *n, node **root)
{
	node *sibling = get_sibling(n);

	printf("caso 3\n");
	if ((n->parent->color == BLACK) &&
		(sibling->color == BLACK) &&
		(sibling->left->color == BLACK) &&
		(sibling->right->color == BLACK)) {

		sibling->color = RED;
		delete_case1(n->parent, root);
	} else {
		delete_case4(n, root);
	}
}

void delete_case2(node *n, node **root)
{
	node *sibling = get_sibling(n);

	printf("caso 2\n");
	if (sibling->color == RED) {
		n->parent->color = RED;
		sibling->color = BLACK;
		if (n == n->parent->left)
			left_rotate(n->parent, root);
		else
			right_rotate(n->parent, root);
	}
	delete_case3(n, root);
}
void delete_case1(node *n, node **root) {
	printf("caso 1\n");
	if (n->parent == NULL) {
		return;
	} else {
		delete_case2(n, root);
	}
}

void delete(node **root, int val) {
	
    if(!*root)
		return;

	node *n = search(root, val);
	if (n == NULL) return;

	node *delete;
	if (n->right == nill && n->left == nill) {
		direction n_dir =  get_node_direction(n);
		if (n_dir == LEFT)
			n->parent->left = (node *) nill;
		else if (n_dir == RIGHT)
			n->parent->right = (node *) nill;

		delete = n;
	} else if (n->left != nill && n->right != nill) {
		node * min_right = minimum_node(n->right);
		n->value = min_right->value;
		
		direction dir = get_node_direction(min_right);
		if (dir == LEFT) {
			min_right->parent->left = (node *) nill;
		} else {
			min_right->parent->right = (node *) nill;
		}
        
        delete = min_right;
	} else {
		node * child = (n->right != nill) ? n->right : n->left;
		direction n_dir =  get_node_direction(n);
		if (n_dir == LEFT)
			n->parent->left = child;
		else if (n_dir == RIGHT)
			n->parent->right = child;

		delete = n;
	}
	
	node * child = n->right == NULL ? n->left  : n->right;
    if (n->color == BLACK) {
    	if (child->color == RED) 
        	child->color = BLACK;
        else
        	delete_case1(n, root);
    }

	free(delete);
}
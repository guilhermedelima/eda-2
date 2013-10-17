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


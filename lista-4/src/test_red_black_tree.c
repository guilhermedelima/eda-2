#include "red_black_tree.h"

void menu_tree(rb_tree *tree);
void test_tree(rb_tree *t);

/*
  Main que realizar teste aleatório ou utilizar um menu para isso  
*/
int main(void){

	rb_tree *tree;
	tree = create_tree();
	

	int op;

	printf("RED BLACK PROGRAM\n");
	printf("(1)-Use Red Black Menu\n(2)-Run Aleatory test\n");
	scanf("%d", &op);

	if(op == 2)
		test_tree(tree);
	else
		menu_tree(tree);

	return 0;
}

/*
  Função com menu para realizar operações em árvore rubro-negra
*/
void menu_tree(rb_tree *tree){

	int op, val;
	char end;

	do{

		system("clear");
		printf("RED BLACK TREE - MENU\n");
		printf("(1)-Insert\n(2)-Delete\n(3)-Print Tree\n(4)-Print Tree as List - ");
		scanf("%d", &op);

		switch(op){
			case 1:
				printf("Node Value: ");
				scanf("%d", &val);
				insert(tree, val);
				print_tree(tree->root);
				break;
			case 2:
				printf("Value to remove: ");
				scanf("%d", &val);
				delete(tree, val);
				print_tree(tree->root);
				break;
			case 3:
				print_tree(tree->root);
				break;
			case 4:
				print_tree_as_list(tree->root);
				break;
			default:
				printf("Invalid Option\n");

		}

		printf("\nContinue? <Y/N>: ");
		scanf(" %c", &end);

	}while(end == 'Y' || end == 'y');


}

/*
  Função para testar valores de forma aleatória (4 inserções 2 remoções) por x vezes
  Após cada remoção verifica propriedades da árvore 
*/
void test_tree(rb_tree *t){

	int val[4];

	int i, j;
	for(i=0; i<100; i++){
		for(j=0; j<4; j++){
			val[j] = random() % 1000;
			insert(t, val[j]);
		}

		for(j=0; j<2; j++){
			delete(t, val[j]);
			verify_properties(t);
		}
	}

	print_tree(t->root);
}





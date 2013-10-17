#include "red_black_tree.h"

int main(void){
	
	//printf("%sTHIS IS THE BLACK NODE'S COLOR\n" ANSI_DEFAULT, shell_colors[black]);
	//printf("%sTHIS IS THE RED NODE'S COLOR\n" ANSI_DEFAULT, shell_colors[red]);
	//printf("THIS IS THE NILL NODE'S COLOR\n\n");

	rb_tree *tree;
	tree = create_tree();

	// int op, val;
	// char end;

	// do{

	// 	system("clear");
	// 	printf("RED BLACK TREE - MENU\n");
	// 	printf("(1)-Insert\n(2)-Delete\n(3)-Print Tree\n(4)-Print Tree as List - ");
	// 	scanf("%d", &op);

	// 	switch(op){
	// 		case 1:
	// 			printf("Node Value: ");
	// 			scanf("%d", &val);
	// 			insert(&tree->root, val);
	// 			print_tree(tree->root);
	// 			break;
	// 		case 2:
	// 			break;
	// 		case 3:
	// 			print_tree(tree->root);
	// 			break;
	// 		case 4:
	// 			print_tree_as_list(tree->root);
	// 			break;
	// 		default:
	// 			printf("Invalid Option\n");

	// 	}

	// 	printf("\nContinue? <Y/N>: ");
	// 	scanf(" %c", &end);


	// }while(end == 'Y' || end == 'y');
	insert(&tree->root, 20);
	insert(&tree->root, 190);
	insert(&tree->root, 247);
	insert(&tree->root, 77);
	insert(&tree->root, 250);
	insert(&tree->root, 385);
	insert(&tree->root, 230);
	insert(&tree->root, 200);
	insert(&tree->root, 100);
	
	insert(&tree->root, 225);
	insert(&tree->root, 4);
	insert(&tree->root, 90000);
	insert(&tree->root, 409);
	print_tree(tree->root);
	verify_properties(&tree->root);

	delete(&tree->root, 247);
	print_tree(tree->root);	
	verify_properties(&tree->root);
	return 0;
}






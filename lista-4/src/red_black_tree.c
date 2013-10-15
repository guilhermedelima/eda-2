#include "red_black_tree.h"

const char *shell_colors[] = { ANSI_BLACK, ANSI_RED };
const node nill = {0, black, NULL, NULL, NULL};


node *search(node *root, int val){

	while(!root){
		if(val > root->value)
			root = root->right;
		else if(val < root->value)
			root = root->left;
		else
			break;
	}

	return root;
}

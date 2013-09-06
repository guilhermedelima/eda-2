#include <stdio.h>
#include <stdlib.h>
#include "index_search.h"

int main(int argc, char *argv[]){

	if(argc != 3){
		fprintf(stderr, "Correct usage: %s <INDEX_LENGTH> <VECTOR_LENGTH>\n", argv[0]);
		exit(-1);
	}


	int vec_length, index_length, window_size;
	vector *vec;
	indexed_table *i_table;

	vec_length = atoi(argv[2]);
	index_length = atoi(argv[1]);

	if(index_length > vec_length){
		fprintf(stderr, "INDEX_LENGTH cant be greater than VECTOR_LENGTH\n");
		exit(-1);
	}

	window_size = vec_length/index_length ;

	if(vec_length%index_length > 0)
		index_length++;

	vec = create_vector(vec_length); 
	i_table = create_indexed_table(vec->list, index_length, window_size);  

	char stp;
	int n, op;

	do{
		printf("\n(1)-Insert\n(2)-Search\n(3)-Delete\n(4)-Print Vector\n(5)-Print Index: ");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				printf("Insert value: ");
				scanf("%d", &n);

				insert(&i_table, vec, n);

				printf("Index Table:\n");
				print_indexed_table(i_table);

				printf("Vector:\n");
				print_vec_list(vec->list);
				break;
			case 2:
				printf("Search for: ");
				scanf("%d", &n);

				search(i_table, n);
				break;
			case 3:
				printf("Delete value: ");
				scanf("%d", &n);

				delete(&i_table, vec, n);

				printf("Index Table:\n");
				print_indexed_table(i_table);

				printf("Vector:\n");
				print_vec_list(vec->list);
				break;
			case 4:
				print_vec_list(vec->list);
				break;
			case 5:
				print_indexed_table(i_table);
				break;
			default:
				printf("Invalid Option\n");
				
		}

		printf("Continue ? <y/n> ");
		scanf(" %c", &stp);

	}while(stp == 'Y' || stp == 'y');

	return 0;
}

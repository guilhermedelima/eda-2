#include <stdio.h>
#include <stdlib.h>
#include "index_search.h"

int main(int argc, char *argv[]){

	if(argc != 3){
		fprintf(stderr, "Correct usage: %s <INDEX_LENGTH> <VECTOR_LENGTH>\n", argv[0]);
		exit(-1);
	}

	int vec_length, index_length, window_size;
	int *vec;
	indexed_table *i_table;

	vec_length = atoi(argv[2]);
	index_length = atoi(argv[1]);

	window_size = vec_length/index_length ;

	vec = create_vec(vec_length);
	i_table = create_indexed_table(vec, index_length, window_size);  

	char stp;
	int n, op;

	do{
		
		printf("1-Insert || 2-Search || 3-Delete || 4-Print Vector || 5-Print Index: ");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				break;
			case 2:
				printf("Search for: ");
				scanf("%d", &n);

				search(i_table, n);
				break;
			case 3:
				printf("Delete value: ");
				scanf("%d", &n);

				delete(i_table, n);
				i_table = rebuild_indexed_table(i_table, vec);

				print_indexed_table(i_table);
				printf("New Vector:\n");
				print_vec(vec, vec_length);
				break;
			case 4:
				print_vec(vec, vec_length);
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

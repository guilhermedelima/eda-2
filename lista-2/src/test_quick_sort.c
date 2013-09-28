#include <stdio.h>
#include <stdlib.h>
#include "quick_sort.h"


int main(int argc, char *argv[]){

	if(argc != 2){
		fprintf(stderr, "Correct Usage: %s <LIST_LENGTH>\n", argv[0]);
		exit(-1);
	}

	linked_list *list;

	list = create_list();
	fill_list(list, atoi( argv[1] ));

	print_list(list);
	quick_sort(list);
	print_list(list);

	return 0;
}

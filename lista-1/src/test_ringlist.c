#include <stdio.h>
#include <stdlib.h>
#include <ringlist.h>

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "Error! Usage:\n\t%s <RING_LIST_CAPACITY>\n", argv[0]);
		exit(-1);
	}

	int capacity = atoi(argv[1]);
	if (capacity == 0) {
		fprintf(stderr, "Error! <RING_LIST_CAPACITY> must be an integer bigger than 0.\n");
		exit(-1);
	}

	RingList *list = ringlist_new(capacity);

	int option, param, response;
	do {
		printf("\n (1) Print RingList\n (2) Insert new value\n (3) Remove by index\n (4) Remove by value\n (5) Serch by value\n (6) Get by index \n (7) Fill untill the range \n (0) Exit\n");
			
		printf("Your option: ");
		scanf("%d", &option);

		switch(option) {
			case 1:
				ringlist_print(list);
				break;
			case 2:
				printf("Value = ");
				scanf("%d", &param);
				ringlist_insert(list, param);
				
				break;
			case 3:
				printf("Index = ");
				scanf("%d", &param);
				ringlist_remove_index(list, param);
				
				break;
			case 4:
				printf("Value = ");
				scanf("%d", &param);
				ringlist_remove_value(list, param);
				
				break;
			case 5:
				printf("Value = ");
				scanf("%d", &param);
				response = ringlist_bsearch(list, param);
				if (response == ERROR_NOT_FOUND)
					printf("'%d' not found.\n", param);
				else
					printf("list[%d] = %d\n", response, param);
				
				break;
			case 6:
				printf("Index = ");
				scanf("%d", &param);
				response = ringlist_get(list, param);
				printf("list[%d] = %d\n", param, response);

				break;
			case 7:
				printf("Range = ");
				scanf("%d", &param);
				ringlist_fill(list, param);

				break;
		}

	} while (option != 0);

	return 0;
}
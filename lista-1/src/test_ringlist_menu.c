/* 
	Módulo test_ringlist_menu.c

	Programa que oferece um menu de opções para efetuar operações (inserir, preencher, remover, etc) em uma estrutura 'ringlist'.
	Modo de uso: ./programa <RING_LIST_CAPACITY>
*/

#include <stdio.h>
#include <stdlib.h>
#include <ringlist.h>
#include <time.h>
#include <unistd.h>

/* 
	Função para cálculo de diferença de tempo entre duas 'struct timespec'.
	Retorna o tempo em segundos.
*/
double diff_seconds(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}

	return (double) (temp.tv_sec + (double) temp.tv_nsec/1000000000L);
}

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

	int option, response;
	long long int param;
	struct timespec start, stop;
	double elapsed_time;
	do {
		printf(" (1) Print RingList\n (2) Insert new value\n (3) Remove by index\n (4) Remove by value\n (5) Binary search \n (6) Interpolation search \n (7) Get by index \n (8) Fill untill the range \n (0) Exit\n");
			
		printf("Your option: ");
		scanf("%d", &option);
		printf("----------------------------------\n");

		switch(option) {
			case 1:
				ringlist_print(list);
				break;
			case 2:
				printf("Value = ");
				scanf("%lld", &param);
				ringlist_insert(list, param);
				
				break;
			case 3:
				printf("Index = ");
				scanf("%lld", &param);
				ringlist_remove_byindex(list, param);
				
				break;
			case 4:
				printf("Value = ");
				scanf("%lld", &param);
				ringlist_remove_byvalue(list, param);
				
				break;
			case 5:
				printf("Value = ");
				scanf("%lld", &param);
				
				clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);

				response = ringlist_bsearch(list, param);
				if (response == ERROR_NOT_FOUND)
					printf("'%lld' not found.\n", param);
				else
					printf("list[%d] = %lld\n", response, param);
					printf("list[%d] = %lld\n", response, param);

				clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &stop);
				elapsed_time = diff_seconds(start, stop);
				
				printf("Binary search time  = %lf sec\n", elapsed_time);
				
				break;
			case 6:
				printf("Value = ");
				scanf("%lld", &param);
				
				clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);

				response = ringlist_interpolsearch(list, param);
				if (response == ERROR_NOT_FOUND)
					printf("'%lld' not found.\n", param);
				else
					printf("list[%d] = %lld\n", response, param);

				clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &stop);
				elapsed_time = diff_seconds(start, stop);
				
				printf("Interpolation search time  = %lf sec\n", elapsed_time);
				
				break;
			case 7:
				printf("Index = ");
				scanf("%lld", &param);
				response = ringlist_get(list, param);
				printf("list[%lld] = %d\n", param, response);

				break;
			case 8:
				printf("Range = ");
				scanf("%lld", &param);
				ringlist_fill(list, param);

				break;
		}
		printf("----------------------------------\n");
		/* #ifdef TARGET_OS_MAC
		  system("clear");
		#elif defined __linux__
		  system("clear");
		#elif defined _WIN32 || defined _WIN64
		  system("cls");
		#endif */
	} while (option != 0);

	return 0;
}
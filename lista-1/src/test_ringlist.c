/* 
	Módulo test_ringlist_menu.c

	Programa que oferece um menu de opções para efetuar operações (inserir, preencher, remover, etc) em uma estrutura 'ringlist'.
	Modo de uso: ./programa <FILL_RANGE> <VALUE> <SEARCH_TYPE(binary=0,interpol=1)>
*/

#include <stdio.h>
#include <stdlib.h>
#include <ringlist.h>
#include <time.h>
#include <unistd.h>

#define BINARY 1
#define INTERPOL 2

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
	RingList *list;

	if (argc < 4) {
		fprintf(stderr, "Error! Usage:\n\t%s <FILL_RANGE> <VALUE> <SEARCH_TYPE(binary=0,interpol=1)>\n", argv[0]);
		exit(-1);
	}
	
	int range = atoi(argv[1]);
	long long int value = atoi(argv[2]);
	int stype = atoi(argv[3]);


	list = ringlist_new(1000000);
	ringlist_fill(list, range);

	printf("\nList size = %d\n", list->size);

	struct timespec start, stop;
	int response;
	printf("Searching for = %lld\n", value);
	if (stype==BINARY) {
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);
		response = ringlist_bsearch(list, value);
		if (response == ERROR_NOT_FOUND)
			printf("'%lld' not found.\n", value);
		else
			printf("List[%d] = %lld\n", response, value);
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &stop);
		
		printf("Binary Search time = %lf sec\n", diff_seconds(start, stop));	
	} else {
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);
		response = ringlist_interpolsearch(list, value);
		if (response == ERROR_NOT_FOUND)
			printf("'%lld' not found.\n", value);
		else
			printf("List[%d] = %lld\n", response, value);
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &stop);
		
		printf("Interpolation Search time = %lf sec\n", diff_seconds(start, stop));	
	}

	return 0;
}

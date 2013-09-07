/* 
	Módulo ringlist.c

	Implementação de operações para uma estrutura 'ringlist'.
*/

#include <ringlist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* 
	Função para criação de uma nova estrutura 'ringlist'
*/
RingList* ringlist_new(unsigned int capacity) {
	if (capacity < 1)
		return NULL;

	RingList * list = calloc(1, sizeof(RingList));

	list->values = calloc(capacity, sizeof(int));;
	list->size = 0;
	list->capacity = capacity;
	
	return list;
}

/* 
	Função interna (visível somente neste módulo) para aumentar a capacidade de uma estrutura 'ringlist'
*/
int _ringlist_increase_capacity(RingList *list, unsigned int new_capacity)
{
	if(!list)
		return ERROR_NULL_LIST;
	if(new_capacity <= list->capacity)
		return ERROR_NEW_CAPACITY_LESS_THAN_ACTUAL;

	int *new_values = calloc(new_capacity, sizeof(int));
	
	int i;
	for(i = 0; i < list->size; i++) 
		new_values[i] = list->values[i];

	free(list->values);
	list->values = new_values;

	list->capacity = new_capacity;

	return OK;
}

/* 
	Função interna (visível somente neste módulo) para mover as células de uma estrutura 'ringlist' para frente ou para tras
*/
int _ringlist_move_cells(RingList *list, unsigned int low_index, direction dir) {
	if(!list)
		return ERROR_NULL_LIST;

	// Move de 'low_index' até o final da lista (para frente)
	if (dir == FRONT) {
		if (list->size > 1) {
			int i;
			for (i = list->size; i > low_index; i--)
				list->values[i] = list->values[i-1];
		} else {
			list->values[1] = list->values[0];
		}
	
	// Move do final da lista até 'low_index' (para tras)
	} else {
		if (list->size > 1) {
			int i;
			for (i = low_index; i < list->size-1; i++)
				list->values[i] = list->values[i+1];
		} 	
	}
		
	return OK;
}

/* 
	Função para inserção de um valor em uma estrutura 'ringlist'
*/
int ringlist_insert(RingList *list, int val) {
	if(!list)
		return ERROR_NULL_LIST;
	
	if(list->size >= list->capacity) 
		_ringlist_increase_capacity(list, list->capacity + (list->capacity/2));
	
	// Se a lista estiver vazia insere na primeira célula
	if (list->size == 0) {
		list->values[0] = val;
		list->size++;
	// Se 'val' for maior que a ultima célula insere no final
	} else if (val > list->values[list->size-1]) {
		list->values[list->size] = val;
		list->size++;
	// Procura o local para ser inserida de forma 'ringlist' continue ordenada (acha o local, move as células para frente coloca o valor)
	} else {
		int i;
		for (i = 0; i < list->size; ++i) {
			if (val <= list->values[i]) {
				_ringlist_move_cells(list, i, FRONT);
				list->values[i] = val;
				list->size++;

				break;
			} 
		}	
	}

	return OK;
}

/* 
	Função para removre uma célula de uma estrutura 'ringlist' pelo índice
*/
int ringlist_remove_byindex(RingList *list, unsigned int index) {
	if(!list)
		return ERROR_NULL_LIST;
	if(list->size == 0)
		return ERROR_EMPTY_LIST;

	// Se a lista tiver só um valor só precisa decrementar o atributo size
	if(list->size == 1) {
		list->size--;
	// Senão ai precisa só mover todas as células posteriores a ela pra trás (dessa forma a célula do índice passado some)
	} else {
		_ringlist_move_cells(list, index % list->size, BACK);	
		list->size--;
	}

	return OK;
}

/* 
	Função para remover uma célula de uma estrutura 'ringlist' pelo valor dela
*/
int ringlist_remove_byvalue(RingList *list, int val) {
	if(!list)
		return ERROR_NULL_LIST;
	if(list->size == 0)
		return ERROR_EMPTY_LIST;

	// Se a lista tiver só um valor e ele for que estiver sendo procurado, só precisa decrementar o atributo size
	if(list->size == 1 && val == list->values[0]) {
		list->size--;
	// Senão ai precisa procurar o valor e só mover todas as células posteriores a ela pra trás (dessa forma a célula do índice passado some).
	} else {
		int index = ringlist_bsearch(list, val);
		if (index == ERROR_NOT_FOUND) {
			return ERROR_NOT_FOUND;
		} else {
			_ringlist_move_cells(list, index, BACK);			
			list->size--;
		}	
	}

	return OK;
}

/* 
	Função para pegar uma célula (por índice) da estrutura 'ringlist'
*/
int ringlist_get(RingList *list, unsigned int index) {
	if(!list)
		return ERROR_NULL_LIST;
	if(list->size == 0)
		return ERROR_EMPTY_LIST;

	return list->values[index % list->size];
}

/* 
	Função para preencher uma estrutura 'ringlist' com valores até um determinado 'range' (de 0 até 'range', sempre com múltiplos de 5)
*/
int ringlist_fill(RingList *list, unsigned long long int range) {
	if(!list)
		return ERROR_NULL_LIST;

	int i;
	for(i = 0; i < range; i++)
		ringlist_insert(list, i*5);

	return OK;
}

/* 
	Função que imprime os dados de uma estrutura 'ringlist'
*/
int ringlist_print(RingList *list) {
	if(!list)
		return ERROR_NULL_LIST;
	
	if(list->size == 0) {
		printf("Values = []\n");
	} else if (list->size <= 1000) {
		int i;
		printf("Values = [");
		for(i = 0; i < list->size - 1; i++) {
			printf("%d, ", list->values[i]);
		}
		printf("%d]\n", list->values[list->size-1]);	
	} else {
		printf("Values = [...]\n");
	} 

	
	printf("Size = %d\nCapacity = %d\n", list->size, list->capacity);

	return OK;
}

/* 
	Função que realiza uma busca binária em uma estrutura 'ringlist'
*/
int ringlist_bsearch(RingList *list, int val) {
	if(!list)
		return ERROR_NULL_LIST;
	if(!list->size)
		return ERROR_NOT_FOUND;
	int low, high, mid;
	low = 0;
	high = list->size-1;
	
	int i = 0;
	// Aqui a busca é efetuada seguindo o algoritmo, também é informado quantos loops foram necessários para a busca
	while (low <= high) {
		mid = low + ((high-low) / 2);

		if (val < list->values[mid]) {
			high = mid - 1;
		} else if (val > list->values[mid]) {
			low = mid + 1;
		} else {
			printf("Search loops = %d\n", i);
			return mid;
		}
		i++;
	}
	printf("Search loops = %d\n", i);

	return ERROR_NOT_FOUND;
}

/* 
	Função que realiza uma busca por interpolação em uma estrutura 'ringlist'
*/
int ringlist_interpolsearch(RingList *list, int val) {
	if(!list)
		return ERROR_NULL_LIST;
	if(!list->size)
		return ERROR_NOT_FOUND;
	int low, high, mid;
	low = 0;
	high = list->size-1;
	
	int i = 0;
	// Aqui a busca é efetuada seguindo o algoritmo, também é informado quantos loops foram necessários para a busca
	while (low <= high) {
		// O typecast é necessário para o valor não ser truncado e levado a 0
		mid = low + (high-low) * ( (float) (val - list->values[low]) / (float) (list->values[high] - list->values[low]));
		
		if (val < list->values[mid]) {
			high = mid - 1;
		} else if (val > list->values[mid]) {
			low = mid + 1;
		} else {
			printf("Search loops = %d\n", i);
			return mid;
		}
		i++;
	}
	printf("Search loops = %d\n", i);

	return ERROR_NOT_FOUND;	
}
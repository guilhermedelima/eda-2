/*
	Módulo que implementa as funções referentes a busca por índices primários
	Inserção e remoção não utiliza técnica de deixar buracos pelo vetor

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index_search.h"


/*
  Funcao apenas para crir um vetor demonstrativo de inteiros com valores 1 até Tamanho do vetor.
  Ao fim do vetor é adicionado um valor para representar um terminador nulo. 
*/
vector *create_vector(int length){

	int *vec_list = (int *) malloc( (length+1) * sizeof(int));
	
	int i;
	for(i=0; i<length; i++)
		vec_list[i] = i+1;

	vec_list[i] = LAST_BLOCK;

	vector *vec = (vector *) malloc( 1 * sizeof(vector) );

	vec->length = length;
	vec->list = vec_list;

	return vec;
}

/*
  Funcao que realoca o vetor de inteiros. 
  Diminui a última posição quando se quer remover um item e Aumenta uma posição quando deseja-se inserir um novo valor
*/
int *rebuild_vec_list(int *vec_list, int length){

	vec_list = (int *) realloc( vec_list, (length+1) * sizeof(int) );

	return vec_list;

}

/*
  Funcao para impressão do vetor de inteiros.
*/
void print_vec_list(int *vec_list){

	printf("[ ");

	int i;
	for(i=0; vec_list[i]!=LAST_BLOCK; i++)
		printf("%d ", vec_list[i]);

	printf("]\n");
}


/*
  Funcao para criar uma nova tabela de índices de acordo com o vetor de inteiros.
*/
indexed_table *create_indexed_table(int *vec_list, int index_length, int window_size){

	primary_index *index_list = (primary_index *) calloc( index_length, sizeof(primary_index) );
	
	//Percorre o vetor criando os índices
	int i;
	for(i=0; i<index_length; i++){
		primary_index idx;
		
		idx.value = vec_list[i*window_size] ;
		idx.regst = vec_list + i*window_size;

		index_list[i] = idx;
	}

	indexed_table *table = malloc(1 * sizeof(indexed_table));

	table->length = index_length;
	table->window_size = window_size;
	table->list = index_list;

	return table;

}

/*
  Funcao para atualizar a tabela de índices. 
  Cria uma nova tabela e libera a memória da antiga. 
*/
indexed_table *rebuild_indexed_table(indexed_table *table, int *vec_list){

	indexed_table *new_table = create_indexed_table(vec_list, table->length, table->window_size);

	free(table->list);
	free(table);

	return new_table;
}

/*
  Funcao para impressão dos índices primários
*/
void print_indexed_table(indexed_table *table){

	int i;
	for(i=0; i < table->length; i++)
		printf("Index %d\n", (table->list[i]).value ) ;

}

/*
  Funcao para trocar o valor de duas variáveis
*/
void swap_int(int *a, int *b){

	int temp = *b;
	*b = *a;
	*a = temp;
}


/*
  Funcao que realiza a busca de um elemento na tabela de índices;
  É retornado o valor do índice na qual ele pode estar dentro e -1 quando este valor for menor que o primeiro índice
*/
int get_index(indexed_table *table, int val){

	int i;
	for(i=0; i < table->length && !(val < table->list[i].value); i++);
	
	return i-1;
}


/*
  Funcao para verificar se após uma remoção ou inserção será necessário excluir ou adicionar um índice, respectivamente.
*/
int check_last_index(indexed_table *table){

	int op, *last_index;

	//Obtém último index para percorrer a janela e checar a necessidade de exluir ou adicionar um novo índice
	last_index = table->list[table->length -1].regst;

	int i;
	for(i=0; last_index[i] != LAST_BLOCK; i++);

	if(i > table->window_size)
		op = INCREASE_INDEX;
	else if(!i)
		op = REMOVE_INDEX;
	else
		op = DO_NOTHING;

	return op;

}


/*
  Funcao que a realiza a busca de um elemento no vetor.
  Primeiramente é feita a busca na tabela de índices e em seguida a busca na janela correspondente
*/
int *search(indexed_table *table, int val){

	int index;
	int *result = NULL;

	//Busca na tabela de índices
	index = get_index(table, val);
	
	//Se o index for -1 sabe-se que o elemento não está no vetor
	if(index >= 0){

		//obtém o ponteiro do índice para o vetor, para então realizar a buca na janela dentro do vetor
		int *window;
		window = table->list[index].regst;

		int i;
		for(i=0; i < table->window_size && window[i]!=LAST_BLOCK; i++){
			if(val == window[i]){
				result = window+i;
				printf("Found value %d after %d searches on window\n", *result, i+1);
				break;		
			}
		}
	}

	if(!result)
		printf("Didn't find this value\n");

	return result;

}

/*
  Funcao que realiza a remoção de um elemento no vetor.
  O elemento é identificado através da funcao search. 
  Em seguida este elemento é deslocado para o fim do vetor e depois removido
*/
void delete(indexed_table **table, vector *vec, int val){

	int *element, op;

	element = search(*table, val);

	if(!element)
		return;
	
	//Desloca elemento para o fim do vetor
	do{
		swap_int(element, element+1);
		element = element+1;

	}while( *(element-1) != LAST_BLOCK );

	//Remove o último elemento
	vec->length--;
	vec->list = rebuild_vec_list(vec->list, vec->length);

	//Verifica se será necessário remover um índice
	op = check_last_index(*table);

	if(op == REMOVE_INDEX)
		(*table)->length--;

	//Reconstrói a tabela de índices e atualiza o ponteiro que aponta para tabela de índices
	*table = rebuild_indexed_table(*table, vec->list);
	
}


/*
  Funcao que realiza inserção de um elemento no vetor.
  Primeiramente é feita a busca na tabela de índices. 
  Em seguida é realizada a busca na janela do vetor para buscar a posição exata na qual deve ser inserido.
  Uma posição 
*/
void insert(indexed_table **table, vector *vec, int val){

	int index, index_to_insert, *element, op;

	//Busca na tabela de índices
	index = get_index(*table, val);
	
	if(index < 0)
		index_to_insert=0;
	else{

		int *window;
		window = (*table)->list[index].regst;

		//Procura na janela dentro do vetor a posição exata na qual o elemento deve ser inserido
		int i;
		for(i=0; i < (*table)->window_size && val >= window[i] && window[i]!=LAST_BLOCK ; i++);

		index_to_insert = i + index * (*table)->window_size;
	}

	//Cria um novo espaço no fim do vetor
	vec->length++;
	vec->list = rebuild_vec_list(vec->list, vec->length);

	//Adiciona o elemento no fim do vetor
	vec->list[vec->length] = val;
	element = (vec->list) + vec->length;	

	//Desloca elemento até a posição exata de inserção
	int i;
	for(i=vec->length; i > index_to_insert; i-- ){
		swap_int(element, element-1);
		element = element -1;
	}

	//Verifica se a janela no último índice estoura e se deve criar um novo índice
	op = check_last_index(*table);

	if(op == INCREASE_INDEX)
		(*table)->length++;

	//Reconstrói a tabela de índices e atualiza o ponteiro que aponta para tabela de índices
	*table = rebuild_indexed_table(*table, vec->list);

}


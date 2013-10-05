#include "radix_sort.h"

int *create_vector(int length){

	int *vec, i;
	vec = (int *) calloc(length, sizeof(int));

	for(i=0; i<length; i++)
		vec[i] = random() % MAX_KEY;

	return vec;
}

void print_vector(int *vec, int length){

	printf("[ ");

	int i;
	for(i=0; i<length; i++)
		printf("%d ", vec[i]);

	printf("]\n");
}

/*
  Funcao para verificar o numero de digitos do maior numero do vetor. Desta forma evita-se que no inicio do radix sort
  apenas um balde seja preenchido (balde 0), caso o maior digito possivel seja definido previamente. 
*/
int check_max_digit(int *vec, int length){

	int i, big, max_digit;

	for(big=0, i=0; i<length; i++){
		if(big < vec[i])
			big=vec[i];		
	}

	max_digit = (!big) ? 1 : pow(10, abs(log10(big)));

	return max_digit;
}

/* 
  Funcao que chama a funcao bucket sort para iniciar a recursividade (counting + bucket) 
  no vetor. Antes verifica-se qual a quantidade de digitos do maior numero do vetor.
*/
void radix_sort(int *vec, int length){

	int max_digit;

	max_digit = check_max_digit(vec, length);
	bucket_sort(vec, length, max_digit);

}

/*
  Funcao que realiza o counting sort de acordo com o digito significativo em questao.
  Após a ordenação os valores são divididos em baldes de 0 a 9, de acordo com o digito passado
  como parametro. Para cada balde é realizada a recursividade, garantindo que o radix sort funcione do 
  digito mais significativo para o menos significativo
*/
void bucket_sort(int *vec, int length, int digit){

	if(digit && length > 1){

		int b_index, b_sum;
		int *bucket_vec;
		int bucket_size[DIGITS] = { 0 };

		counting_sort(vec, length, digit);

		/* Percorre o vetor verificando o tamanho de cada um dos 10 baldes */
		int i;
		for(i=0; i<length; i++){
			b_index = (vec[i]/digit) % 10;
			bucket_size[ b_index ]++;
		}

		b_sum=0;

		/* Apos o counting sort, cada balde esta organizado no vetor. 
		   Desta forma os baldes podem ser divididos no proprio vetor.
		   A referencia e o tamanho para cada balde e passado para recursividade, na qual sera
		   executada levando em consideracao o proximo digito a direita
		*/
		for(i=0; i<DIGITS; i++){
			bucket_vec = vec + b_sum;
			bucket_sort(bucket_vec, bucket_size[i], digit/10);

			b_sum += bucket_size[i];
		}

	}

}

/*
  Funcao que realiza o counting sort em um vetor. 
  A ordenacao é feita levando em consideração apenas um digito significativo passado como parametro, 
  como por exemplo, o primeiro digito a esquerda. Portanto o vetor auxiliar de soma tem 10 posicoes (0 a 9).	
*/
void counting_sort(int *vec, int length, int digit){

	int vec_sum[DIGITS] = { 0 };
	int vec_sort[length];
	int index, new_index;

	int i;
	for(i=0; i<length; i++){
		index = (vec[i] / digit) % 10 ;
		vec_sum[index]++;
	}

	for(i=1; i<DIGITS; i++)
		vec_sum[i] += vec_sum[i-1];

	for(i=length-1; i >= 0; i--){
		index = (vec[i] / digit) % 10 ;
		new_index = --vec_sum[index];
		vec_sort[new_index] = vec[i];
	}

	for(i=0; i<length; i++)
		vec[i]=vec_sort[i];

}




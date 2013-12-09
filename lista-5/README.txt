Quinta Lista - EDA 2

 -Guilherme de Lima Bernardes (09/0115350)
 -Matheus Souza Fonseca (10/0054650)

OBS: Executar Makefile para compilação dos exercícios.


Questão 1)

Exercício para implementação do algoritmo guloso para o problema interval scheduling. O algoritmo cria um conjunto de N (passado por parâmetro) tarefas aleatórias. Para cada critério é verificado o número de tarefas selecionadas, o critério que apresentar o maior número de tarefas selecionadas é o escolhido. Caso critérios fiquem empatados o algoritmo cria outro conjunto de tarefas aleatórias e repete o processo até que apenas um critério seja o mais efetivo. 

Caso já tenham sido testados MAX_LOOP (constante) conjuntos de tarefas, o programa, ao invés de continuar testando tarefas aleatórias, cria um conjunto de tarefas que representa o contra exemplo para o critério de "menores colisões". Isto serve apenas para que o programa não fique executando valores aleatórios até achar a resposta. 

Para ordenar as tarefas por critério foi utilziado o algoritmo merge sort. Arquivos correspondentes: 

 -greedy_task.h
 -greedy_task.c
 -merge_sort.c
 -test_greedy_task.c (main)


OBS: Quando o programa é tastado passando como parâmentro 10 a solução geralmente é encontrada mais rápido.

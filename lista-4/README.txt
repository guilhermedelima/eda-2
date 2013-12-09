Quarta Lista - EDA 2

 -Guilherme de Lima Bernardes (09/0115350)
 -Matheus Souza Fonseca (10/0054650)

OBS: Executar Makefile para compilação dos exercícios.


Questão 1)

Exercício para implementação da árvore rubro-negra. O programa permite realizar as operações de inserção, remoção e impressão. Também está disponível uma função para verificar as propriedades da árvore. O programa main apresenta duas opções, executar inserções e remoções e impressões manualmente através de um menu, ou realizar a execução de um teste aleatório, que insere 4 valores randomicos e remove 2, durante 100 vezes. A cada remoção é verificado se as propriedades da árvore se mantém, no fim do teste a árvore é impressa. A impresssão da árvore é realizada utilizando uma travessia Pré-Ordem, onde a cada nível é impresso o nó, e em seguida so filhos esquerdo e direito (recursivamente). Cada nível da árvore possui uma identação diferente. Os nós também são impressos de acordo com sua cor (preto ou vermelho). Arquivos correspondentes: 

 -red_black_tree.h
 -red_black_tree.c
 -test_red_black_tree.c (main)

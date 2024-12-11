#ifndef CONJUNTO_H
  #define CONJUNTO_H

  #define ERRO 1000010

  /*Constantes para melhor leitura do código*/
  #define TAD_LISTA 0
  #define TAD_ARVORE 1

  typedef struct conjunto_ CONJUNTO;

  /*Todas operações seguintes utilizam as funções específicas do TAD selecionado*/
  /*Aloca memória para um conjunto. De acordo com a escolha do TAD, também aloca espaço para a estrutura escolhida
  Retorna um ponteiro para o conjunto criado*/
  CONJUNTO *conjunto_criar(int TAD);

  /*Apaga a estrutura escolhida*/
  void conjunto_apagar(CONJUNTO **conj);

  /*Insere o elemento no conjunto. Se o elemento já existe no conjunto, ele não é inserido
  Retorna true se o elemento foi inserido, senão false*/
  bool conjunto_inserir(CONJUNTO *conj, int elemento);

  /*Remove o elemento do conjunto
  Retorna o elemento removido se bem sucedido, senão retorna ERRO*/
  int conjunto_remover(CONJUNTO *conj, int elemento);

  /*Imprime o conjunto em ordem crescente, sem quebra de linha no final*/
  void conjunto_imprimir(CONJUNTO *conj);

  /*Verifica se o elemento pertence ao conjunto indicado realizando uma busca na estrutura
  Se sim, retorna true. Senão, retorna falso*/
  bool conjunto_pertence(CONJUNTO *conj, int elemento);

  /*Realiza a união de dois conjuntos copiando um e adicionando a esta cópia os elementos do segundo. Se o elemento já existir nesse conjunto, ele não é inserido
  Retorna um ponteiro para o conjunto resultante
  NÃO apaga ou modifica os conjuntos originais*/
  CONJUNTO *conjunto_uniao(CONJUNTO *conjAOriginal, CONJUNTO *conjBOriginal);

  /*Realiza a intersecção de dois conjuntos
  Retorna um ponteiro para o conjunto resultante
  NÃO apaga ou modifica os conjuntos originais*/
  CONJUNTO *conjunto_interseccao(CONJUNTO *conjAOriginal, CONJUNTO *conjBOriginal);

  /*Cria um conjunto novo e copia os elementos do conjunto passado
  Retorna um ponteiro para esse novo conjunto*/
  CONJUNTO *conjunto_copiar(CONJUNTO *conj);

#endif
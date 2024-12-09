#ifndef LISTA_H
  #define LISTA_H

  #define TAM_MAX 199999
  #define ERRO 1000010

  typedef struct lista_ LISTA;

  /*Aloca uma lista na memória, inicializa ela com tamanho 0
  Retorna o ponteiro para essa lista*/
  LISTA *lista_criar(void);

  /*Desaloca o espaço apontado pelo ponteiro e o torna nulo*/
  void lista_apagar(LISTA **lista);

  /*Insere um elemento na lista ordenadamente na lista
  Retorna true se o elemento foi inserido e false senão*/
  bool lista_inserir(LISTA *lista, int elemento);
  
  /*Remove o elemento da lista
  Retorna o elemento removido se bem sucedido, ERRO senão*/
  int lista_remover(LISTA *lista, int elemento);

  /*Imprime a lista em ordem crescente, sem quebra de linha no final*/
  void lista_imprimir(LISTA *lista);

  /*Realiza a busca binária para encontrar a chave
  Retorna o elemento se ele foi encontrado, ERRO senão*/
  int lista_busca(LISTA *lista, int chave);
  
  /*Retorna o elemento armazenaod no índice passado, ERRO senão*/
  int lista_consultar(LISTA *lista, int indice);

  /*Copia os elementos da lista passada
  Retorna um ponteiro para essa cópia*/
  LISTA *lista_copiar(LISTA *lista);

#endif 
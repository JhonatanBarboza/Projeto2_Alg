#ifndef LISTA_H
  #define LISTA_H

  #define TAM_MAX 100000
  #define ERRO 1000010

  typedef struct lista_ LISTA;

  LISTA *lista_criar(void);
  void lista_apagar(LISTA **lista);
  bool lista_inserir(LISTA *lista, int elemento);
  int lista_remover(LISTA *lista, int elemento);
  void lista_imprimir(LISTA *lista);
  int lista_busca(LISTA *lista, int chave);
  int lista_consultar(LISTA *lista, int indice);
  LISTA *lista_copiar(LISTA *lista);

#endif 
#ifndef HEAPMAX_H
  #define HEAPMAX_H

  #define TAM_MAX 100000
  #define ERRO 1000010

  typedef struct heapmax_ HEAPMAX;

  HEAPMAX *heapmax_criar(void);
  bool heapmax_inserir(HEAPMAX *heap, int elemento);
  int heapmax_remover(HEAPMAX *heap);
  void heapmax_rearranjar(HEAPMAX *heap, int i, int tamHeap);
  void heapSort(HEAPMAX *heap, int tamHeap);
  bool heapmax_cheia(HEAPMAX *heap);
  bool heapmax_vazia(HEAPMAX *heap);
  int heapmax_tamanho(HEAPMAX *heap);
  void heapmax_imprimir(HEAPMAX *heap);
  void heapmax_apagar(HEAPMAX **heap);
  int buscaBinaria(HEAPMAX *heap, int inicio, int fim, int chave);

#endif
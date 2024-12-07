#ifndef AVL_H
  #define AVL_H

  #define ERRO 1000010
  #define max(a, b) ((a > b) ? a : b)

  typedef struct avl_ AVL;

  AVL *avl_criar(void);
  void avl_apagar(AVL **avl);
  bool avl_inserir(AVL *avl, int chave);
  int avl_remover(AVL *avl, int chave);
  int avl_get_altura(AVL *avl);
  int avl_get_tamanho(AVL *avl);
  AVL *avl_copiar(AVL *avl);
  void avl_imprimir(AVL *avl);
  int avl_busca(AVL *avl, int chave);
  int avl_get_chave_raiz(AVL *avl);

#endif
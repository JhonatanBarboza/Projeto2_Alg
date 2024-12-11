#ifndef AVL_H
  #define AVL_H

  #define ERRO 1000010
  /*Retorna o maior elemento entre a e b*/
  #define max(a, b) ((a > b) ? a : b)

  typedef struct avl_ AVL;

  /*Aloca uma AVL na memória, inicializa ela com tamanho 0
  Retorna um ponteiro para essa árvore*/
  AVL *avl_criar(void);

  /*Desaloca o espaço apontado pelo ponteiro e o torna nulo*/
  void avl_apagar(AVL **avl);

  /*Insere o elemento na árvore (seguindo as regras da AVL)
  Retorna true se o elemento foi inserido e false senão*/
  bool avl_inserir(AVL *avl, int chave);

  /*Remove o elemento na árvore
  Retorna o elemento se bem sucedido, ERRO senão*/
  int avl_remover(AVL *avl, int chave);

  /*Calcula a altura da árvore
  Retorna a altura se bem sucediso, ERRO senão*/
  int avl_get_altura(AVL *avl);

  /*Retorna a QUANTIDADE total de nós na árvore
  Retorna erro se mal sucedida*/
  int avl_get_tamanho(AVL *avl);

  /*Aloca uma nova árvore e copia os elementos da árvore passada para essa nova
  Retorna um ponteiro para a cópia*/
  AVL *avl_copiar(AVL *avl);

  /*Imprime a árvore em-ordem, sem quebra de linha no final*/
  void avl_imprimir(AVL *avl);

  /*Busca a chave na árvore usando busca binária
  Retorna o elemento se ele foi encontrado, ERRO senão*/
  int avl_busca(AVL *avl, int chave);

  /*Retorna a chave da raíz da árvore (ERRO se a raíz for nula)*/
  int avl_get_chave_raiz(AVL *avl);

#endif
#ifndef CONJUNTO_H
  #define CONJUNTO_H

  #define TAD_LISTA 0
  #define TAD_ARVORE 1

  typedef struct conjunto_ CONJUNTO;

  CONJUNTO *conjunto_criar(int TAD);
  bool conjunto_apagar(CONJUNTO **conj);
  bool conjunto_inserir(CONJUNTO *conj, int elemento);
  int conjunto_remover(CONJUNTO *conj);
  void conjunto_imprimir(CONJUNTO *conj);
  bool conjunto_pertence(CONJUNTO *conj, int elemento);
  CONJUNTO *conjunto_uniao(CONJUNTO *conjA, CONJUNTO *conjB);
  CONJUNTO *conjunto_interseccao(CONJUNTO *conjA, CONJUNTO *conjB);

#endif
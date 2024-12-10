#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../bibliotecas/conjunto.h"

/*Constantes para tornar o código mais claro*/
#define TAD_LISTA 0
#define TAD_ARVORE 1
#define ERRO 1000010
#define PERTENCE 1
#define UNIAO 2
#define INTERSEC 3
#define CONJ_A 1
#define CONJ_B 2

int main(void){
  /*Escolha do TAD a ser utilizado*/
  int TAD;
  scanf("%d", &TAD);

  CONJUNTO *conjA = conjunto_criar(TAD);
  CONJUNTO *conjB = conjunto_criar(TAD);

  int tamA, tamB;
  scanf("%d", &tamA);
  scanf("%d", &tamB);

  if(tamA == 0 && tamB == 0){
    printf("Conjuntos vazios!\n");
    return EXIT_SUCCESS;
  }

  /*Leitura dos elementos de cada conjunto*/
  for(int i = 0; i < tamA; i++){
    int elem;
    scanf("%d", &elem);
    conjunto_inserir(conjA, elem);
  }
  for(int i = 0; i < tamB; i++){
    int elem;
    scanf("%d", &elem);
    conjunto_inserir(conjB, elem);
  }

  /*Escolha da operação a ser realizada*/
  int op;
  scanf("%d", &op);

  switch(op){
    case PERTENCE:{
      int elem;
      scanf("%d", &elem);

      if(conjunto_pertence(conjA, elem)){
        printf("Pertence.\n");
      }
      else{
        printf("Não pertence.\n");
      }
      break;
    }
    case UNIAO:{
      CONJUNTO *conjC = conjunto_uniao(conjA, conjB); 
      conjunto_imprimir(conjC);

      conjunto_apagar(&conjC);
      break;
    }
    case INTERSEC:{
      CONJUNTO *conjC = conjunto_interseccao(conjA, conjB);
      conjunto_imprimir(conjC);

      conjunto_apagar(&conjC);
      break;
    }
    default:{
      printf("Operacao invalida.\n");
      break;
    }
  }

  conjunto_apagar(&conjA);
  conjunto_apagar(&conjB);
  return EXIT_SUCCESS;
}
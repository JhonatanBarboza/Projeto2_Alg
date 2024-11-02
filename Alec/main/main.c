#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../bibliotecas/conjunto.h"

#define TAD_LISTA 0
#define TAD_ARVORE 1
#define ERRO 1000010
#define PERTENCE 1
#define UNIAO 2
#define INTERSEC 3
#define CONJ_A 1
#define CONJ_B 2

int main(void){
  int TAD;
  //printf("Digite o TAD(Lista/Arvore): 0/1\n");
  scanf("%d", &TAD);

  CONJUNTO *conjA = conjunto_criar(TAD);
  CONJUNTO *conjB = conjunto_criar(TAD);

  int tamA, tamB;
  //printf("Tamanho do conjunto A:\n");
  scanf("%d", &tamA);
  //printf("Tamanho do conjunto B:\n");
  scanf("%d", &tamB);

  for(int i = 0; i < tamA; i++){
    int elem;
    //printf("Elemento a ser inserido no conjunto A:\n");
    scanf("%d", &elem);
    conjunto_inserir(conjA, elem);
  }
  for(int i = 0; i < tamB; i++){
    int elem;
    //printf("Elemento a ser inserido no conjunto B:\n");
    scanf("%d", &elem);
    conjunto_inserir(conjB, elem);
  }

  int op;
  //printf("Digite a operação:\n");
  //printf("1: PERTENCE (Conjunto A)\n");
  //printf("2: UNIAO\n");
  //printf("3: INTERSEC\n");
  scanf("%d", &op);
  switch(op){
    case PERTENCE:{
      //printf("Operação escolhida: PERTENCE\n");
      int elem;
      //printf("Elemento a ser checado:\n");
      scanf("%d", &elem);

      if(conjunto_pertence(conjA, elem)){
        printf("Pertence.\n");
      }
      else{
        printf("Nao pertence.\n");
      }
      
      break;
    }
    case UNIAO:{
      //printf("Operação escolhida: UNIAO\n");
      CONJUNTO *conjC = conjunto_uniao(conjA, conjB);
      conjunto_imprimir(conjC);

      conjunto_apagar(&conjC);
      break;
    }
    case INTERSEC:{
      //printf("Operação escolhida: INTERSEC\n");
      CONJUNTO *conjC = conjunto_interseccao(conjA, conjB);
      conjunto_imprimir(conjC);

      conjunto_apagar(&conjC);
      break;
    }
    default:{
      printf("Operação inválida\n");
      break;
    }
  }

  conjunto_apagar(&conjA);
  conjunto_apagar(&conjB);
  return EXIT_SUCCESS;
}
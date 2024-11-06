#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lista.h"
#include "../ABB.h"
#include "../conjunto.h"

struct conjunto_{
  int TAD;
  LISTA *conjuntoLista; /*Um desses ponteiros não será utilizado*/
  ABB *conjuntoABB;
  int tamanho;
};

CONJUNTO *conjunto_criar(int TAD){
  if((TAD != TAD_LISTA) && (TAD != TAD_ARVORE)) return NULL; //TAD inválido

  CONJUNTO *conjunto = (CONJUNTO *) malloc(sizeof(CONJUNTO));
  if(conjunto == NULL) return NULL;

  conjunto->TAD = TAD;
  conjunto->tamanho = 0;
  if(TAD == TAD_LISTA){
    conjunto->conjuntoLista = lista_criar();
    conjunto->conjuntoABB = NULL;
  }
  else if(TAD == TAD_ARVORE){
    conjunto->conjuntoLista = NULL;
    conjunto->conjuntoABB = abb_criar();
  }

  return conjunto;
}

bool conjunto_apagar(CONJUNTO **conj){
  if(*conj == NULL) return true;

  if((*conj)->TAD == TAD_LISTA){
    lista_apagar(&((*conj)->conjuntoLista));
  }
  else{
    abb_apagar(&((*conj)->conjuntoABB));
  }

  free(*conj);
  *conj = NULL;
  return true;
}

bool conjunto_inserir(CONJUNTO *conj, int elemento){
  if(conj == NULL) return false;

  if(conj->TAD == TAD_LISTA){
    lista_inserir(conj->conjuntoLista, elemento);
  }
  else{
    abb_inserir(conj->conjuntoABB, elemento);
  }

  conj->tamanho++;
  return true;
}

int conjunto_remover(CONJUNTO *conj, int elemento){ 
  if(conj == NULL) return ERRO;

  int elementoRemovido;
  if(conj->TAD == TAD_LISTA){
    elementoRemovido =  lista_remover(conj->conjuntoLista, elemento);// ********************************
  }
  else{
    elementoRemovido = abb_remover(conj->conjuntoABB);
  }

  if(elementoRemovido == ERRO) return ERRO;

  conj->tamanho--;
  return elementoRemovido;
}

void conjunto_imprimir(CONJUNTO *conj){
  if(conj == NULL) return;

  if(conj->TAD == TAD_LISTA){
    lista_imprimir(conj->conjuntoLista);
  }
  else{
    abb_imprimir(conj->conjuntoABB, true); //true: referente a imprimir a árvore ordenadamente ou não
  }

  return;
}

bool conjunto_pertence(CONJUNTO *conj, int elemento){
  if(conj == NULL) return false;

  if(conj->TAD == TAD_LISTA){
    if(elemento == lista_busca(conj->conjuntoLista, elemento)) return true;
  }
  else{
    if(elemento == abb_busca(conj->conjuntoABB, elemento)) return true;
  }

  //Se a busca não retornar o elemento buscado (não pertence):
  return false;
}

CONJUNTO *conjunto_uniao(CONJUNTO *conjAOriginal, CONJUNTO *conjBOriginal){
  if((conjAOriginal == NULL) || (conjBOriginal == NULL)){
    printf ("Conjunto união vazio!\n");    // ***************************************************
    return NULL;
  }

  CONJUNTO *conjA = conjunto_copiar(conjAOriginal);
  CONJUNTO *conjB = conjunto_copiar(conjBOriginal);
  if((conjA == NULL) || (conjB == NULL)){
    conjunto_apagar(&conjA);
    conjunto_apagar(&conjB);
    return NULL;
  }

  CONJUNTO *conjUniao = conjunto_criar(conjAOriginal->TAD);
  if(conjUniao == NULL){
    conjunto_apagar(&conjUniao);
    return NULL;
  }

  if(conjUniao->TAD == TAD_LISTA){
    /*Inserindo todos os elementos de A em conjUniao*/
    conjUniao = conjunto_copiar(conjA);

    /*Inserindo os elementos de B em conjUniao*/
    for(int i = 0; i < conjB->tamanho; i++){
      lista_inserir(conjUniao->conjuntoLista, lista_consultar(conjB->conjuntoLista, i));

      conjUniao->tamanho++;
    }

    /*Observação: a lista não insere números que já aparecem nela*/
  }

  if(conjUniao->TAD == TAD_ARVORE){
    /*Mesma lógica e observação que na lista*/
    for(int i = 0; i < conjA->tamanho; i++){
      int elemento = abb_remover(conjA->conjuntoABB);
      abb_inserir(conjUniao->conjuntoABB, elemento);

      conjUniao->tamanho++;
    }
    
    for(int i = 0; i < conjB->tamanho; i++){
      int elemento = abb_remover(conjB->conjuntoABB);

      if(abb_busca(conjUniao->conjuntoABB, elemento) == ERRO){
        abb_inserir(conjUniao->conjuntoABB, elemento);
        
        conjUniao->tamanho++;
      }
    }
  }

  return conjUniao;
}

CONJUNTO *conjunto_interseccao(CONJUNTO *conjAOriginal, CONJUNTO *conjBOriginal){
  if((conjAOriginal == NULL) || (conjBOriginal == NULL)) return NULL;

  CONJUNTO *conjA = conjunto_copiar(conjAOriginal);
  if(conjA == NULL){
    conjunto_apagar(&conjA);
    return NULL;
  }

  CONJUNTO *conjIntersec = conjunto_criar(conjAOriginal->TAD);
  if(conjIntersec == NULL){
    conjunto_apagar(&conjIntersec);
    return NULL;
  }

  if(conjIntersec->TAD == TAD_LISTA){
    /*Somente inserindo os elementos de A se eles aparecerem em B*/
    for(int i = 0; i < conjA->tamanho; i++){
      int elemento = lista_consultar(conjA->conjuntoLista, i);

      if(conjunto_pertence(conjBOriginal, elemento)){
        lista_inserir(conjIntersec->conjuntoLista, elemento);

        conjIntersec->tamanho++;
      }
    }
  }

  if(conjIntersec->TAD == TAD_ARVORE){
    /*Mesma lógica*/
    for(int i = 0; i < conjA->tamanho; i++){
      int elemento = abb_remover(conjA->conjuntoABB);

      if(conjunto_pertence(conjBOriginal, elemento)){
        abb_inserir(conjIntersec->conjuntoABB, elemento);

        conjIntersec->tamanho++;
      }
    }
  }

  conjunto_apagar(&conjA);
  /*verifica se o conjunto é vazio*/
  if (conjIntersec->tamanho == 0){
    printf("Conjunto intersecção vazio!\n"); // ********************************
  }
  return conjIntersec;
}

CONJUNTO *conjunto_copiar(CONJUNTO *conj){
  if(conj == NULL) return NULL;

  CONJUNTO *copiaConj = conjunto_criar(conj->TAD);
  if(copiaConj == NULL){
    conjunto_apagar(&copiaConj);
    return NULL;
  }
  copiaConj->TAD = conj->TAD;

  if(copiaConj->TAD == TAD_LISTA){
    copiaConj->conjuntoLista = lista_copiar(conj->conjuntoLista);
  }
  else{
    copiaConj->conjuntoABB = abb_copiar(conj->conjuntoABB);
  }

  copiaConj->tamanho = conj->tamanho;
  return copiaConj;
}
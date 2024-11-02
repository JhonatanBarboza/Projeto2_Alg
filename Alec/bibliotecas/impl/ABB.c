#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../ABB.h"

typedef struct no_ NO;

struct no_{
  int chave;
  NO *noEsq;
  NO *noDir;
};

struct abb_{
  NO *raiz;
  int tamanho;
};

NO *buscaBinariaABB(NO *noRaiz, int chave);
NO *inserirABB(NO *noRaiz, NO *noNovo);
NO *removeRaizABB(NO *noRaiz);
void imprimirOrdenada(NO *noRaiz);
void imprimirNaoOrdenada(NO *noRaiz);
NO *no_criar(int chave, NO *noEsq, NO *noDir);
void no_apagar(NO **no);
void no_apagar_recursivo(NO *no);
NO *no_copiar_recursivo(NO *no);

ABB *abb_criar(void){
  ABB *arvore = (ABB *) malloc(sizeof(ABB));
  if(arvore == NULL){
    printf("Erro em abb_criar: arvore == NULL\n");
    return NULL;
  }

  arvore->raiz = NULL;
  arvore->tamanho = 0;
  return arvore;
}

void abb_apagar(ABB **arvore){
  if(*arvore == NULL) return;

  no_apagar_recursivo((*arvore)->raiz);

  free(*arvore);
  *arvore = NULL;
}

bool abb_inserir(ABB *arvore, int elemento){
  if(arvore == NULL){
    printf("Erro 1 em abb_inserir: arvore == NULL\n");
    return false;
  }

  if(abb_busca(arvore, elemento) == elemento) return false;

  NO *noNovo = no_criar(elemento, NULL, NULL);

  arvore->raiz = inserirABB(arvore->raiz, noNovo);
  if(arvore->raiz == NULL){
    printf("Erro 2 em abb_inserir: arvore->raiz == NULL\n");
    return false;
  }

  arvore->tamanho++;
  return true;
}

int abb_remover(ABB *arvore){
  if(arvore == NULL){
    printf("Erro em abb_remover: arvore == NULL\n");
    return ERRO;
  }
  if(arvore->raiz == NULL){
    printf("Erro em abb_remover: arvore->raiz == NULL\n");
    return ERRO;
  }
  if(arvore->tamanho == 0) return ERRO;

  NO *raizVelha = arvore->raiz;
  int elemRemovido = raizVelha->chave;

  arvore->raiz = removeRaizABB(raizVelha);

  arvore->tamanho--;
  return elemRemovido;
}

void abb_imprimir(ABB *arvore, bool ordenada){
  if(arvore == NULL){
    printf("Erro em abb_imprimir: arvore == NULL\n");
    return;
  }

  if(ordenada){
    imprimirOrdenada(arvore->raiz);
  }
  else{
    imprimirNaoOrdenada(arvore->raiz);
  }
  printf("\n");
  fflush(stdout);

  return;
}

int abb_busca(ABB *arvore, int chave){
  if(arvore == NULL){
    printf("Erro em abb_busca: arvore == NULL\n");
    return ERRO;
  }
  if(arvore->tamanho == 0) return ERRO;

  NO *noChave = buscaBinariaABB(arvore->raiz, chave);
  if(noChave == NULL) return ERRO;

  return noChave->chave;
}

ABB *abb_copiar(ABB *arvore){
  if(arvore == NULL){
    printf("Erro em abb_copiar: arvore == NULL\n");
    return NULL;
  }

  ABB *copiaArvore = abb_criar();
  if(copiaArvore == NULL){
    printf("Erro em abb_copiar: copiaArvore == NULL\n");
    return NULL;
  }

  copiaArvore->raiz = no_copiar_recursivo(arvore->raiz);
  copiaArvore->tamanho = arvore->tamanho;

  return copiaArvore;
}

NO *buscaBinariaABB(NO *noRaiz, int chave){
  if((noRaiz == NULL) || (noRaiz->chave == chave)){
    return noRaiz;
  }

  if(noRaiz->chave > chave){
    return buscaBinariaABB(noRaiz->noEsq, chave);
  }
  else{
    return buscaBinariaABB(noRaiz->noDir, chave);
  }
}

NO *inserirABB(NO *noRaiz, NO *noNovo){
  if(noRaiz == NULL){
    return noNovo;
  }

  if(noRaiz->chave > noNovo->chave){
    noRaiz->noEsq = inserirABB(noRaiz->noEsq, noNovo); 
  }
  else{
    noRaiz->noDir = inserirABB(noRaiz->noDir, noNovo);
  }

  return noRaiz;
}

NO *removeRaizABB(NO *noRaiz){
  if(noRaiz == NULL){
    printf("Erro em removeRaizABB: noRaiz == NULL\n");
    return NULL;
  }

  NO *noAuxP, *noAuxQ;
  if(noRaiz->noEsq == NULL){
    noAuxQ = noRaiz->noDir;

    noRaiz->noDir = NULL;
    no_apagar(&noRaiz);

    return noAuxQ;
  }
  if(noRaiz->noDir == NULL){
    noAuxQ = noRaiz->noEsq;

    noRaiz->noEsq = NULL;
    no_apagar(&noRaiz);

    return noAuxQ;
  }
  
  noAuxP = noRaiz;
  noAuxQ = noRaiz->noEsq;
  while(noAuxQ->noDir != NULL){
    noAuxP = noAuxQ;
    noAuxQ = noAuxQ->noDir;
  }

  if(noAuxP != noRaiz){
    noAuxP->noDir = noAuxQ->noEsq;
    noAuxQ->noEsq = noRaiz->noEsq;
  }
  noAuxQ->noDir = noRaiz->noDir;

  noRaiz->noDir = NULL;
  noRaiz->noEsq = NULL;
  no_apagar(&noRaiz);

  return noAuxQ;
}

void imprimirNaoOrdenada(NO *noRaiz){
  if(noRaiz != NULL){
    printf("%d ", noRaiz->chave);
    imprimirNaoOrdenada(noRaiz->noEsq);
    imprimirNaoOrdenada(noRaiz->noDir);
  }
  fflush(stdout);

  return;
}

void imprimirOrdenada(NO *noRaiz){
  if(noRaiz != NULL){
    imprimirOrdenada(noRaiz->noEsq);
    printf("%d ", noRaiz->chave);
    imprimirOrdenada(noRaiz->noDir);
  }
  fflush(stdout);

  return;
}

NO *no_criar(int chave, NO *noEsq, NO *noDir){
  NO *noNovo = (NO *) malloc(sizeof(NO));
  if(noNovo == NULL){
    printf("Erro em noCriar: noNovo == NULL\n");
    return NULL;
  }

  noNovo->chave = chave;
  noNovo->noEsq = noEsq;
  noNovo->noDir = noDir;
  return noNovo;
}

void no_apagar(NO **no){
  if(*no == NULL) return;

  free(*no);
  *no = NULL;
  return;
}

void no_apagar_recursivo(NO *no){
  if(no == NULL) return;

  no_apagar_recursivo(no->noEsq);
  no_apagar_recursivo(no->noDir);
  no_apagar(&no);

  return;
}

NO *no_copiar_recursivo(NO *no){
  if(no == NULL) return NULL;

  NO *noNovo = no_criar(no->chave, NULL, NULL);
  if(noNovo == NULL){
    printf("Erro em no_copiar_recursivo: noNovo == NULL\n");
    return NULL;
  }

  noNovo->noEsq = no_copiar_recursivo(no->noEsq);
  noNovo->noDir = no_copiar_recursivo(no->noDir);

  return noNovo;
}
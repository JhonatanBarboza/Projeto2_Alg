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

/*Funções auxiliares*/
NO *buscaBinariaABB(NO *noRaiz, int chave);
NO *inserirABB(NO *noRaiz, NO *noNovo);
NO *removeRaizABB(NO *noRaiz, int elemento, bool *removido);
void imprimirOrdenada(NO *noRaiz);
void imprimirNaoOrdenada(NO *noRaiz);
NO *no_criar(int chave, NO *noEsq, NO *noDir);
void no_apagar(NO **no);
void no_apagar_recursivo(NO *no);
NO *no_copiar_recursivo(NO *no);

ABB *abb_criar(void){
  ABB *arvore = (ABB *) malloc(sizeof(ABB));
  if(arvore == NULL) return NULL;

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

void no_apagar_recursivo(NO *no){
  if(no == NULL) return;

  no_apagar_recursivo(no->noEsq);
  no_apagar_recursivo(no->noDir);
  no_apagar(&no);

  return;
}

bool abb_inserir(ABB *arvore, int elemento){
  if(arvore == NULL) return false;

  /*Não inserimos o elemento se ele já existir na árvore*/
  if(abb_busca(arvore, elemento) == elemento) return false;

  NO *noNovo = no_criar(elemento, NULL, NULL);
  if(noNovo == NULL) return false;

  /*inserirABB() explicada mais adiante*/
  arvore->raiz = inserirABB(arvore->raiz, noNovo);
  if(arvore->raiz == NULL) return false;

  arvore->tamanho++;
  return true;
}

NO *no_criar(int chave, NO *noEsq, NO *noDir){
  NO *noNovo = (NO *) malloc(sizeof(NO));
  if(noNovo == NULL) return NULL;

  noNovo->chave = chave;
  noNovo->noEsq = noEsq;
  noNovo->noDir = noDir;
  return noNovo;
}

/*Percorre a árvore recursivamente e insere
o nó quando encontrar um filho nulo*/
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

int abb_remover(ABB *arvore, int elemento){
  if(arvore == NULL) return ERRO;
  if((arvore->raiz == NULL) || (arvore->tamanho == 0)) return ERRO;

  bool removido = false;
  arvore->raiz = removeRaizABB(arvore->raiz, elemento, &removido);

  if(removido){
    arvore->tamanho--;
    return elemento;
  }

  return ERRO;
}

/*Remove um nó e o subtitui por um de seus filhos*/
NO *removeRaizABB(NO *noRaiz, int elemento, bool *removido){
  if(noRaiz == NULL){
    *removido = false;
    return NULL;
  }

  /*Encontrando o nó a ser removido*/
  if(elemento < noRaiz->chave){
    noRaiz->noEsq = removeRaizABB(noRaiz->noEsq, elemento, removido);
    return noRaiz;
  }
  else if(elemento > noRaiz->chave){
    noRaiz->noDir = removeRaizABB(noRaiz->noDir, elemento, removido);
    return noRaiz;
  }

  /*Encontramos o nó*/
  /*Nó folha*/
  if((noRaiz->noEsq == NULL) && (noRaiz->noDir == NULL)){
    *removido = true;
    no_apagar(&noRaiz);
    return NULL;
  }

  /*Nó com um filho só*/
  if(noRaiz->noEsq == NULL){
    *removido = true;
    NO *noTemp = noRaiz->noDir;
    no_apagar(&noRaiz);
    return noTemp;
  }
  if(noRaiz->noDir == NULL){
    *removido = true;
    NO *noTemp = noRaiz->noEsq;
    no_apagar(&noRaiz);
    return noTemp;
  }

  /*Nó com dois filhos*/
  NO *sucessor = noRaiz->noDir;
  NO *paiSucessor = noRaiz;

  while(sucessor->noEsq != NULL){
    paiSucessor = sucessor;
    sucessor = sucessor->noEsq;
  }

  if(paiSucessor !=  noRaiz){
    paiSucessor->noEsq = sucessor->noDir;
    sucessor->noDir = noRaiz->noDir;
  }

  sucessor->noEsq = noRaiz->noEsq;
  no_apagar(&noRaiz);
  *removido = true;
  return sucessor;
}

void no_apagar(NO **no){
  if(*no == NULL) return;

  free(*no);
  *no = NULL;
  return;
}

void abb_imprimir(ABB *arvore, bool ordenada){
  if(arvore == NULL) return;

  if(ordenada){
    imprimirOrdenada(arvore->raiz);
  }
  else{
    imprimirNaoOrdenada(arvore->raiz);
  }
  printf("\n");

  return;
}

void imprimirNaoOrdenada(NO *noRaiz){
  if(noRaiz != NULL){
    printf("%d ", noRaiz->chave);
    imprimirNaoOrdenada(noRaiz->noEsq);
    imprimirNaoOrdenada(noRaiz->noDir);
  }

  return;
}

void imprimirOrdenada(NO *noRaiz){
  if(noRaiz != NULL){
    imprimirOrdenada(noRaiz->noEsq);
    printf("%d ", noRaiz->chave);
    imprimirOrdenada(noRaiz->noDir);
  }

  return;
}

int abb_busca(ABB *arvore, int chave){
  if(arvore == NULL) return ERRO;
  if(arvore->tamanho == 0) return ERRO;

  NO *noChave = buscaBinariaABB(arvore->raiz, chave);
  if(noChave == NULL) return ERRO;

  return noChave->chave;
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

ABB *abb_copiar(ABB *arvore){
  if(arvore == NULL) return NULL;

  ABB *copiaArvore = abb_criar();
  if(copiaArvore == NULL) return NULL;

  copiaArvore->raiz = no_copiar_recursivo(arvore->raiz);
  copiaArvore->tamanho = arvore->tamanho;

  return copiaArvore;
}

NO *no_copiar_recursivo(NO *no){
  if(no == NULL) return NULL;

  NO *noNovo = no_criar(no->chave, NULL, NULL);
  if(noNovo == NULL) return NULL;

  noNovo->noEsq = no_copiar_recursivo(no->noEsq);
  noNovo->noDir = no_copiar_recursivo(no->noDir);

  return noNovo;
}

int abb_get_chave_raiz(ABB *arvore){
  if(arvore == NULL) return ERRO;
  if(arvore->tamanho == 0) return ERRO;

  return arvore->raiz->chave;
}
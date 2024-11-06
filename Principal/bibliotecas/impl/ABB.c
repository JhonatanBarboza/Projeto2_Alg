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

/* ÁRVORE BINÁRIA DE BUSCA */

/*Funções auxiliares*/
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
  if(arvore == NULL) return NULL;

  arvore->raiz = NULL;
  arvore->tamanho = 0;
  return arvore;
}

void abb_apagar(ABB **arvore){
  if(*arvore == NULL) return;

  /*Apaga todos os nós da árvore recursivamente, começando pela raíz*/
  no_apagar_recursivo((*arvore)->raiz);

  free(*arvore);
  *arvore = NULL;
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

int abb_remover(ABB *arvore){
  if(arvore == NULL) return ERRO;
  if(arvore->raiz == NULL) return ERRO;
  if(arvore->tamanho == 0) return ERRO;

  NO *raizVelha = arvore->raiz;
  int elemRemovido = raizVelha->chave;

  /*removeRaizABB() explicado mais adiante*/
  arvore->raiz = removeRaizABB(raizVelha);

  arvore->tamanho--;
  return elemRemovido;
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

int abb_busca(ABB *arvore, int chave){
  if(arvore == NULL) return ERRO;
  if(arvore->tamanho == 0) return ERRO;

  NO *noChave = buscaBinariaABB(arvore->raiz, chave);
  if(noChave == NULL) return ERRO;

  return noChave->chave;
}

ABB *abb_copiar(ABB *arvore){
  if(arvore == NULL) return NULL;

  ABB *copiaArvore = abb_criar();
  if(copiaArvore == NULL) return NULL;

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

/*Remove um nó e o subtitui por um de seus filhos*/
NO *removeRaizABB(NO *noRaiz){
  if(noRaiz == NULL) return NULL;

  /*Nó a ser removido com somente um filho*/
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
  
  /*Nó com os dois filhos*/
  /*Percorremos a árvore até achar o maior nó passível
  de substituir o nó a ser removido (o maior nó passível
  será aquele da direita com filho nulo)*/
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

NO *no_criar(int chave, NO *noEsq, NO *noDir){
  NO *noNovo = (NO *) malloc(sizeof(NO));
  if(noNovo == NULL) return NULL;

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
  if(noNovo == NULL) return NULL;

  noNovo->noEsq = no_copiar_recursivo(no->noEsq);
  noNovo->noDir = no_copiar_recursivo(no->noDir);

  return noNovo;
}
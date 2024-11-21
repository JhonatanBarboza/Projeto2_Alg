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
  int tamanho; //Quantidade de nós
};

/*Funções auxiliares da árvore*/
NO *buscaBinariaABB(NO *noRaiz, int chave);
NO *inserirABB(NO *noRaiz, NO *noNovo);
NO *removeRaizABB(NO *noRaiz, int elemento, bool *removido);
void imprimirOrdenada(NO *noRaiz);
void imprimirNaoOrdenada(NO *noRaiz);

/*Funções auxiliares do nó*/
NO *no_criar(int chave, NO *noEsq, NO *noDir);
void no_apagar(NO **no);
void no_apagar_recursivo(NO *no);
NO *no_copiar_recursivo(NO *no);

/*Cria uma nova árvore binária de busca vazia, inicializando
a raiz como NULL e o tamanho como 0*/
ABB *abb_criar(void){
  ABB *arvore = (ABB *) malloc(sizeof(ABB));
  if(arvore == NULL) return NULL;

  arvore->raiz = NULL;
  arvore->tamanho = 0;
  return arvore;
}

/*Apaga toda a árvore binária de busca, liberando a memória
de todos os nós recursivamente e da própria estrutura da árvore*/
void abb_apagar(ABB **arvore){
  if(*arvore == NULL) return;

  /*Função no_apagar_recursivo() mais abaixo*/
  no_apagar_recursivo((*arvore)->raiz);

  free(*arvore);
  *arvore = NULL;
}

/*Apaga recursivamente um nó em PÓS-ORDEM, ou seja,
começamos removendo as folhas e vamos "subindo" até
a raíz*/
void no_apagar_recursivo(NO *no){
  if(no == NULL) return;

  no_apagar_recursivo(no->noEsq);
  no_apagar_recursivo(no->noDir);
  no_apagar(&no);

  return;
}

/*Insere um novo elemento na árvore mantendo a propriedade de ABB.
Retorna true se a inserção foi bem sucedida e false caso contrário*/
bool abb_inserir(ABB *arvore, int elemento){
  if(arvore == NULL) return false;

  /*Não inserimos o elemento se ele já existir na árvore*/
  if(abb_busca(arvore, elemento) == elemento) return false;

  /*O elemento não está presente, vamos inserí-lo*/
  NO *noNovo = no_criar(elemento, NULL, NULL);
  if(noNovo == NULL) return false;

  /*inserirABB() explicada mais adiante*/
  arvore->raiz = inserirABB(arvore->raiz, noNovo);
  if(arvore->raiz == NULL) return false;

  arvore->tamanho++; //Atualizando o tamanho da árvore
  return true;
}

/*Cria um novo nó com a chave e ponteiros para os filhos especificados.
Retorna NULL em caso de erro na alocação*/
NO *no_criar(int chave, NO *noEsq, NO *noDir){
  NO *noNovo = (NO *) malloc(sizeof(NO));
  if(noNovo == NULL) return NULL;

  noNovo->chave = chave;
  noNovo->noEsq = noEsq;
  noNovo->noDir = noDir;
  return noNovo;
}

/*Função auxiliar recursiva que insere um novo nó na árvore,
mantendo a propriedade de ABB onde elementos menores ficam à
esquerda e maiores à direita*/
NO *inserirABB(NO *noRaiz, NO *noNovo){
  /*Chegamos na posição de inserção do novo nó*/
  if(noRaiz == NULL){
    return noNovo;
  }

  if(noRaiz->chave > noNovo->chave){
    /*Tentamos inserir no lado esquerdo*/
    noRaiz->noEsq = inserirABB(noRaiz->noEsq, noNovo); 
  }
  else{
    /*Tentamos inserir no lado direito*/
    noRaiz->noDir = inserirABB(noRaiz->noDir, noNovo);
  }

  /*Útil no caso em que a árvore está vazia*/
  return noRaiz;
}

/*Remove um elemento da árvore mantendo suas propriedades.
Retorna o elemento removido em caso de sucesso ou ERRO
caso contrário*/
int abb_remover(ABB *arvore, int elemento){
  if(arvore == NULL) return ERRO;
  if((arvore->raiz == NULL) || (arvore->tamanho == 0)) return ERRO;

  /*Utilizamos uma flag*/
  bool removido = false;
  /*removeRaizABB() explicado adiante*/
  arvore->raiz = removeRaizABB(arvore->raiz, elemento, &removido);

  if(removido){
    arvore->tamanho--;
    return elemento;
  }
  //else:
  return ERRO;
}

/*Encontra o sucessor do nó a ser removido (o menor valor na sub-árvore
da direita) e o coloca no lugar do nó a ser removido, conectando o resto
da árvore a ele*/
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
  /*Se for nó folha*/
  if((noRaiz->noEsq == NULL) && (noRaiz->noDir == NULL)){
    *removido = true;
    no_apagar(&noRaiz);
    return NULL;
  }

  /*Se for nó com um filho só*/
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

  /*Se for nó com dois filhos*/
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

/*Libera a memória de um nó específico e seta o ponteiro para NULL*/
void no_apagar(NO **no){
  if(*no == NULL) return;

  free(*no);
  *no = NULL;
  return;
}

/*Imprime os elementos da árvore. Se ordenada for true, imprime em ordem
crescente (in-ordem). Caso contrário, imprime em pré-ordem*/
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

/*Imprime os elementos da árvore em pré-ordem (raiz, esquerda, direita)*/
void imprimirNaoOrdenada(NO *noRaiz){
  if(noRaiz != NULL){
    printf("%d ", noRaiz->chave);
    imprimirNaoOrdenada(noRaiz->noEsq);
    imprimirNaoOrdenada(noRaiz->noDir);
  }

  return;
}

/*Imprime os elementos da árvore em ordem crescente (in-ordem: 
esquerda, raiz, direita)*/
void imprimirOrdenada(NO *noRaiz){
  if(noRaiz != NULL){
    imprimirOrdenada(noRaiz->noEsq);
    printf("%d ", noRaiz->chave);
    imprimirOrdenada(noRaiz->noDir);
  }

  return;
}

/*Busca um elemento na árvore. Retorna o elemento se encontrado
ou ERRO caso contrário*/
int abb_busca(ABB *arvore, int chave){
  if(arvore == NULL) return ERRO;
  if(arvore->tamanho == 0) return ERRO;

  NO *noChave = buscaBinariaABB(arvore->raiz, chave);
  if(noChave == NULL) return ERRO;

  return noChave->chave;
}

/*Função auxiliar recursiva que implementa a busca binária na árvore.
Retorna o nó contendo a chave buscada ou NULL se não encontrar*/
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

/*Cria e retorna uma cópia profunda da árvore, onde todos os nós
são duplicados mantendo a mesma estrutura*/
ABB *abb_copiar(ABB *arvore){
  if(arvore == NULL) return NULL;

  ABB *copiaArvore = abb_criar();
  if(copiaArvore == NULL) return NULL;

  copiaArvore->raiz = no_copiar_recursivo(arvore->raiz);
  copiaArvore->tamanho = arvore->tamanho;

  return copiaArvore;
}

/*Função auxiliar recursiva que cria uma cópia profunda de um nó
e todos os seus descendentes*/
NO *no_copiar_recursivo(NO *no){
  if(no == NULL) return NULL;

  NO *noNovo = no_criar(no->chave, NULL, NULL);
  if(noNovo == NULL) return NULL;

  noNovo->noEsq = no_copiar_recursivo(no->noEsq);
  noNovo->noDir = no_copiar_recursivo(no->noDir);

  return noNovo;
}

/*Retorna a chave armazenada na raiz da árvore ou ERRO
se a árvore estiver vazia*/
int abb_get_chave_raiz(ABB *arvore){
  if(arvore == NULL) return ERRO;
  if(arvore->tamanho == 0) return ERRO;

  return arvore->raiz->chave;
}
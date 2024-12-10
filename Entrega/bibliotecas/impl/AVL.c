#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../AVL.h"

typedef struct no_ NO;

struct no_{
  int chave;
  NO *noEsq;
  NO *noDir;
  int FB; //Fator de Balanceamento
};

/*Funções auxiliares do nó*/
NO *no_criar(int chave, NO *noEsq, NO *noDir);
void no_apagar(NO **no);
void no_apagar_recursivo(NO *no);
NO *no_rodar_direita(NO *noA);
NO *no_rodar_esquerda(NO *noA);
int no_get_altura(NO *no);
NO *no_copiar_recursivo(NO *no);
/*Funções auxiliares do nó*/

struct avl_{
  NO *noRaiz;
  int tamanho; //Quantidade total de nós
};

/*Funções auxiliares da árvore*/
NO *avl_inserir_no(NO *noRaiz, NO *noNovo, bool *jaInserido);
bool avl_remover_no(NO **pontNoRaiz, int chave);
void avl_imprimir_arv(NO *noRaiz);
NO *busca_binaria_avl(NO *noRaiz, int chave);
/*Funções auxiliares da árvore*/

AVL *avl_criar(void){
  /*Alocando memória*/
  AVL *avl = (AVL *) malloc(sizeof(AVL));
  if(avl == NULL) return NULL;

  /*Inicializando valores*/
  avl->noRaiz = NULL;
  avl->tamanho = 0;

  return avl;
}

void avl_apagar(AVL **avl){
  if(*avl == NULL) return;

  /*Apagando os nós das árvores*/
  no_apagar_recursivo((*avl)->noRaiz);

  /*Desalocando a memória*/
  free(*avl);
  *avl = NULL;

  return;
}

void no_apagar_recursivo(NO *no){
  /*Caso base*/
  if(no == NULL) return;

  /*Pós-ordem*/
  no_apagar_recursivo(no->noEsq);
  no_apagar_recursivo(no->noDir);

  /*Apaga o nó*/
  no_apagar(&no);
  return;
}

void no_apagar(NO **no){
  if(*no == NULL) return;

  /*Desalocando memória*/
  free(*no);
  *no = NULL;
  return;
}

bool avl_inserir(AVL *avl, int chave){
  /*Erro*/
  if(avl == NULL) return false;

  /*Criando o nó*/
  NO* noNovo = no_criar(chave, NULL, NULL);
  if(noNovo == NULL) return false;

  /*Inserindo o nó na árvore*/
  /*Atribuir o resultado de avl_inserir_no diretamente ao nó raiz poderia quebrar a árvore caso a função retorne NULL. Por causa disso, vamos utilizar o noTemp*/
  bool jaInserido = false; // Flag para retornamos falso caso o elemento já exista na árvore

  NO *noTemp = avl_inserir_no(avl->noRaiz, noNovo, &jaInserido);
  if((noTemp == NULL) || (jaInserido == true)) return false;
  avl->noRaiz = noTemp;

  avl->tamanho++;

  return true;
}

NO *avl_inserir_no(NO *noRaiz, NO *noNovo, bool *jaInserido){
  /*
  noRaiz == NULL -> a árvore está vazia, devemos inserir
  noNovo == NULL -> o nó foi criado incorretamente, não devemos inserir
  */
  if(noNovo == NULL) return NULL;

  /*Inserindo o nó em pré-ordem, que nem uma ABB*/
  if(noRaiz == NULL) return noNovo;
  else if(noNovo->chave == noRaiz->chave){
    /*Prevenindo inserção de elementos duplicados*/
    *jaInserido = true;
    return noRaiz;
  }
  else if(noNovo->chave < noRaiz->chave) noRaiz->noEsq = avl_inserir_no(noRaiz->noEsq, noNovo, jaInserido);
  else noRaiz->noDir = avl_inserir_no(noRaiz->noDir, noNovo, jaInserido);

  /*Definindo os fatores de balanceamento*/
  noRaiz->FB = no_get_altura(noRaiz->noEsq) - no_get_altura(noRaiz->noDir);

  /*Balanceando, se necessário*/
  if(noRaiz->FB < -1){
    if(noRaiz->noDir->FB <= 0) noRaiz = no_rodar_esquerda(noRaiz); /*Rotação esquerda*/
    else{
      /*Rotação direita esquerda*/
      noRaiz->noDir = no_rodar_direita(noRaiz->noDir);
      noRaiz = no_rodar_esquerda(noRaiz);
    }
  }

  if(noRaiz->FB > 1){
    if(noRaiz->noEsq->FB >= 0) noRaiz = no_rodar_direita(noRaiz); /*Rotação direita*/
    /*Rotação esquerda direita*/
    else{
      noRaiz->noEsq = no_rodar_esquerda(noRaiz->noEsq);
      noRaiz = no_rodar_direita(noRaiz);
    }
  }

  return noRaiz;
}

NO *no_criar(int chave, NO *noEsq, NO *noDir){
  /*Alocando memória*/
  NO *no = (NO *) malloc(sizeof(NO));
  if(no == NULL) return NULL;

  /*Definindo valores iniciais*/
  no->chave = chave;
  no->FB = 0;
  no->noEsq = noEsq;
  no->noDir = noDir;

  return no;
}

int no_get_altura(NO *no){
  int alt = -1;
  if(no == NULL) return alt;

  int altEsq = no_get_altura(no->noEsq);
  int altDir = no_get_altura(no->noDir);
  alt = max(altEsq, altDir);
  alt++;

  return alt;
}

NO *no_rodar_direita(NO *noA){
  /*noA é o nó desbalanceado*/
  NO *noB = noA->noEsq;
  
  /*Rotacionando*/
  noA->noEsq = noB->noDir;
  noB->noDir = noA;

  /*Definindo os fatores de balanceamento*/
  if((noA->FB == -2) && (noB->FB == -2)){
    noA->FB = 1;
    noB->FB = 0;
  }
  else if((noA->FB == -2) && (noB->FB == -1)){
    noA->FB = 0;
    noB->FB = 0;
  }
  else if((noA->FB == -2) && (noB->FB == 0)){
    noA->FB = -1;
    noB->FB = 1;
  }
  else if((noA->FB == -1) && (noB->FB == -1)){
    noA->FB = 1;
    noB->FB = 1;
  }
  else if((noA->FB == -1) && (noB->FB == 0)){
    noA->FB = 0;
    noB->FB = 1;
  }
  else if((noA->FB == -1) && (noB->FB == 1)){
    noA->FB = 0;
    noB->FB = 2;
  }

  return noB;
}

NO *no_rodar_esquerda(NO *noA){
  /*noA é o nó desbalanceado*/
  NO *noB = noA->noDir;
  
  /*Rotacionando*/
  noA->noDir = noB->noEsq;
  noB->noEsq = noA;

  /*Definindo os fatores de balanceamento
  OBS: Do jeito que fizemos aqui, a complexidade pode ser afetada.
  Podemos evitar isso usando ifs.
  */
  noA->FB = no_get_altura(noA->noEsq) - no_get_altura(noA->noDir);
  noB->FB = no_get_altura(noB->noEsq) - no_get_altura(noB->noDir);

  return noB;
}

int avl_get_altura(AVL *avl){
  if(avl == NULL) return -9999; //ERRO

  return no_get_altura(avl->noRaiz);
}

int avl_remover(AVL *avl, int chave){
  if(avl == NULL) return ERRO;

  bool elementoRemovido = avl_remover_no(&(avl->noRaiz), chave);
  if(elementoRemovido){
    avl->tamanho--;
    return chave;
  }
  //else:
  return ERRO;
}

bool avl_remover_no(NO **pontNoRaiz, int chave){
  /*Casos a serem considerados na remoção:
    1. O nó é folha;
    2. O nó possui uma sub-árvore (esquerda ou direita);
    3. O nó possui duas sub-árvores.
  */
  //Caso base da recursão:
  if(*pontNoRaiz == NULL) return false;

  bool chaveRemovida = false;

  if(chave < (*pontNoRaiz)->chave){
    chaveRemovida = avl_remover_no(&((*pontNoRaiz)->noEsq), chave);
  }
  else if(chave > (*pontNoRaiz)->chave){
    chaveRemovida = avl_remover_no(&((*pontNoRaiz)->noDir), chave);
  }
  else{
    /*Encontramos o nó a ser removido*/
    if(((*pontNoRaiz)->noEsq == NULL) || ((*pontNoRaiz)->noDir == NULL)){
      /*O nó atual tem um ou nenhum filho -> resolve os casos 1 e 2*/
      NO *noTemp = (*pontNoRaiz)->noEsq ? (*pontNoRaiz)->noEsq : (*pontNoRaiz)->noDir;

      if(noTemp == NULL){
        /*Nó folha*/
        noTemp = *pontNoRaiz;
        *pontNoRaiz = NULL;
      }
      else{
        /*Há um filho*/
        **pontNoRaiz = *noTemp;
      }

      no_apagar(&noTemp);
      chaveRemovida = true;
    }
    else{
      /*O nó atual tem dois filhos -> resolve o caso 3*/

      /*Troca o nó atual pelo nó com a maior chave da sub-árvore
      esquerda em relação ao nó atual*/
      NO *sucessor = (*pontNoRaiz)->noEsq;
      while (sucessor->noDir != NULL){
        sucessor = sucessor->noDir;
      }

      (*pontNoRaiz)->chave = sucessor->chave;
      chaveRemovida = avl_remover_no(&((*pontNoRaiz)->noEsq), sucessor->chave);
    }
  }

  if(!chaveRemovida) return false;
  if(*pontNoRaiz == NULL) return true;

  /*Ajustando o fator de balanceamento*/
  (*pontNoRaiz)->FB = no_get_altura((*pontNoRaiz)->noEsq) - no_get_altura((*pontNoRaiz)->noDir);

  /*Balanceando, se necessário*/
  if((*pontNoRaiz)->FB < -1){
    if((*pontNoRaiz)->noDir->FB <= 0) *pontNoRaiz = no_rodar_esquerda(*pontNoRaiz); /*Rotação esquerda*/
    else{
      /*Rotação direita esquerda*/
      (*pontNoRaiz)->noDir = no_rodar_direita((*pontNoRaiz)->noDir);
      *pontNoRaiz = no_rodar_esquerda(*pontNoRaiz);
    }
  }

  if((*pontNoRaiz)->FB > 1){
    if((*pontNoRaiz)->noEsq->FB >= 0) *pontNoRaiz = no_rodar_direita(*pontNoRaiz); /*Rotação direita*/
    /*Rotação esquerda direita*/
    else{
      (*pontNoRaiz)->noEsq = no_rodar_esquerda((*pontNoRaiz)->noEsq);
      *pontNoRaiz = no_rodar_direita(*pontNoRaiz);
    }
  }

  return true;
}

/*Imprime os elementos da árvore em ordem crescente (in-ordem: 
esquerda, raiz, direita)*/
void avl_imprimir(AVL *avl){
  avl_imprimir_arv(avl->noRaiz);
  printf("\n");

  return;
}

void avl_imprimir_arv(NO *noRaiz){
  if(noRaiz != NULL){
    avl_imprimir_arv(noRaiz->noEsq);
    printf("%d ", noRaiz->chave);
    avl_imprimir_arv(noRaiz->noDir);
  }

  return;
}

/*Cria e retorna uma cópia profunda da árvore, onde todos os nós
são duplicados mantendo a mesma estrutura*/
AVL *avl_copiar(AVL *avl){
  if(avl == NULL) return NULL;

  AVL *copiaAvl = avl_criar();
  if(copiaAvl == NULL) return NULL;

  copiaAvl->noRaiz = no_copiar_recursivo(avl->noRaiz);
  copiaAvl->tamanho = avl->tamanho;

  return copiaAvl;
}

/*Função auxiliar recursiva que cria uma cópia profunda de um nó
e todos os seus descendentes*/
NO *no_copiar_recursivo(NO *no){
  if(no == NULL) return NULL;

  NO *noNovo = no_criar(no->chave, NULL, NULL);
  if(noNovo == NULL) return NULL;

  noNovo->FB = no->FB;
  noNovo->noEsq = no_copiar_recursivo(no->noEsq);
  noNovo->noDir = no_copiar_recursivo(no->noDir);

  return noNovo;
}

/*Busca um elemento na árvore. Retorna o elemento se encontrado
ou ERRO caso contrário*/
int avl_busca(AVL *avl, int chave){
  if(avl == NULL) return ERRO;
  if(avl->tamanho == 0) return ERRO;

  NO *noChave = busca_binaria_avl(avl->noRaiz, chave);
  if(noChave == NULL) return ERRO;

  return noChave->chave;
}

/*Função auxiliar recursiva que implementa a busca binária na árvore.
Retorna o nó contendo a chave buscada ou NULL se não encontrar*/
NO *busca_binaria_avl(NO *noRaiz, int chave){
  if((noRaiz == NULL) || (noRaiz->chave == chave)) return noRaiz;

  if(noRaiz->chave > chave) return busca_binaria_avl(noRaiz->noEsq, chave);
  else return busca_binaria_avl(noRaiz->noDir, chave);
}

/*Retorna a chave armazenada na raiz da árvore ou ERRO
se a árvore estiver vazia*/
int avl_get_chave_raiz(AVL *avl){
  if(avl == NULL) return ERRO;
  if(avl->tamanho <= 0) return ERRO;

  return avl->noRaiz->chave;
}

int avl_get_tamanho(AVL *avl){
  if(avl == NULL) return ERRO;

  return avl->tamanho;
}
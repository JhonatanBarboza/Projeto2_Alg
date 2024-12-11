#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lista.h"
#include "../AVL.h"
#include "../conjunto.h"

struct conjunto_{
  int TAD;
  int tamanho;
  /*Somente um dos próximos ponteiros será utilizado*/
  LISTA *conjuntoLista;
  AVL *conjuntoAVL;
};

/*Chama a função específica de cada um dos TADs para criar
a ED escolhida e a armazena no ponteiro correspondente*/
CONJUNTO *conjunto_criar(int TAD){
  if((TAD != TAD_LISTA) && (TAD != TAD_ARVORE)){
    printf("TAD inválido!\n");
    return NULL;  
  }

  CONJUNTO *conjunto = (CONJUNTO *) malloc(sizeof(CONJUNTO));
  if(conjunto == NULL) return NULL;

  conjunto->TAD = TAD;
  conjunto->tamanho = 0;
  if(TAD == TAD_LISTA){
    conjunto->conjuntoLista = lista_criar();
    conjunto->conjuntoAVL = NULL;
  }
  else if(TAD == TAD_ARVORE){
    conjunto->conjuntoLista = NULL;
    conjunto->conjuntoAVL = avl_criar();
  }

  return conjunto;
}

/*Análoga à criar*/
void conjunto_apagar(CONJUNTO **conj){
  if(*conj == NULL) return;

  if((*conj)->TAD == TAD_LISTA){
    lista_apagar(&((*conj)->conjuntoLista));
  }
  else{
    avl_apagar(&((*conj)->conjuntoAVL));
  }

  free(*conj);
  *conj = NULL;
  return;
}

/*Análoga à criar*/
bool conjunto_inserir(CONJUNTO *conj, int elemento){
  if(conj == NULL) return false;

  if(conj->TAD == TAD_LISTA){
    lista_inserir(conj->conjuntoLista, elemento);
  }
  else{
    avl_inserir(conj->conjuntoAVL, elemento);
  }

  conj->tamanho++;
  return true;
}

/*Análoga à criar*/
int conjunto_remover(CONJUNTO *conj, int elemento){ 
  if(conj == NULL) return ERRO;

  int elementoRemovido;
  if(conj->TAD == TAD_LISTA){
    elementoRemovido =  lista_remover(conj->conjuntoLista, elemento);
  }
  else{
    elementoRemovido = avl_remover(conj->conjuntoAVL, elemento);
  }

  if(elementoRemovido == ERRO) return ERRO;

  conj->tamanho--;
  return elementoRemovido;
}

/*Análoga à criar*/
void conjunto_imprimir(CONJUNTO *conj){
  if(conj == NULL) return;

  if(conj->TAD == TAD_LISTA){
    lista_imprimir(conj->conjuntoLista);
  }
  else{
    avl_imprimir(conj->conjuntoAVL);
  }

  return;
}

/*Utiliza a função de busca do TAD escolhido para tentar encontrar o elemento*/
bool conjunto_pertence(CONJUNTO *conj, int elemento){
  if(conj == NULL) return false;

  if(conj->TAD == TAD_LISTA){
    if(elemento == lista_busca(conj->conjuntoLista, elemento)) return true;
  }
  else{
    if(elemento == avl_busca(conj->conjuntoAVL, elemento)) return true;
  }

  return false;
}

CONJUNTO *conjunto_uniao(CONJUNTO *conjAOriginal, CONJUNTO *conjBOriginal){
  if((conjAOriginal == NULL) || (conjBOriginal == NULL)) return NULL;
  if((conjAOriginal->tamanho == 0) && (conjBOriginal->tamanho == 0)){
    printf ("Conjunto união vazio!\n");
    return NULL;
  }

  /*Como o conjunto união contém os elementos dos dois conjuntos, podemos
  inicializar ele com todos os elementos de um dos conjutos. Fazemos isso
  utilizando a função conjunto_copia() com o conjunto A.*/
  CONJUNTO *conjUniao = conjunto_copiar(conjAOriginal);
  if(conjUniao == NULL){
    conjunto_apagar(&conjUniao);
    return NULL;
  }
  /*Assim conjUniao já tem todos os elementos de A*/

  if(conjUniao->TAD == TAD_LISTA){
    /*Inserindo os elementos de B em conjUniao utilizando a função inserir da lista*/
    for(int i = 0; i < conjBOriginal->tamanho; i++){
      int elemento = lista_consultar(conjBOriginal->conjuntoLista, i); /*Obtendo o elemento da lista na posição i*/
      conjunto_inserir(conjUniao, elemento);
    }
    /*Observação: a lista não insere números que já aparecem nela!*/
  }

  if(conjUniao->TAD == TAD_ARVORE){
    /*Utilizando o TAD árvore, para inserir os elementos de B em conjUniao vamos ter
    que removê-los da árvore (devido à sua implementação). Devido a isso, vamos
    criar uma cópia do conjunto B e remover os elementos esse conjunto, mantendo
    o original intacto.*/
    CONJUNTO *conjBCopia = conjunto_copiar(conjBOriginal);
    if(conjBCopia == NULL){
      conjunto_apagar(&conjBCopia);
      return NULL;
    }
    
    while(avl_get_tamanho(conjBCopia->conjuntoAVL) > 0){
      /*Removemos a raíz da árvore por padrão para facilitar a operação de remoção.*/
      int chaveRaiz = avl_get_chave_raiz(conjBCopia->conjuntoAVL);
      if(chaveRaiz == ERRO) break;
      int elemento = avl_remover(conjBCopia->conjuntoAVL, chaveRaiz);
      if(elemento != ERRO) conjunto_inserir(conjUniao, elemento);
    }
    /*Mesma observação que na lista*/
    conjunto_apagar(&conjBCopia);
  }

  return conjUniao;
}

CONJUNTO *conjunto_interseccao(CONJUNTO *conjAOriginal, CONJUNTO *conjBOriginal){
  if((conjAOriginal == NULL) || (conjBOriginal == NULL)) return NULL;
  if((conjAOriginal->tamanho == 0) && (conjBOriginal->tamanho == 0)){
    printf ("Conjunto intersecção vazio!\n");
    return NULL;
  }

  CONJUNTO *conjIntersec = conjunto_criar(conjAOriginal->TAD);
  if(conjIntersec == NULL){
    conjunto_apagar(&conjIntersec);
    return NULL;
  }

  if(conjIntersec->TAD == TAD_LISTA){
    /*Somente inserimos um elemento de A em conjIntersec se ele também aparecer em B*/
    for(int i = 0; i < conjAOriginal->tamanho; i++){
      //Vamos percorrer a lista A elemento a elemento
      int elemento = lista_consultar(conjAOriginal->conjuntoLista, i);

      //Se o elemento atual pertencer à B, inserimos em Intersec
      if((elemento != ERRO) && (conjunto_pertence(conjBOriginal, elemento))){
        conjunto_inserir(conjIntersec, elemento);
      }
      //Senão, não inserimos
    }
  }

  if(conjIntersec->TAD == TAD_ARVORE){
    /*Mesma lógica de copiar a árvore na união, pelo mesmo motivo*/
    CONJUNTO *conjACopia = conjunto_copiar(conjAOriginal);
    if(conjACopia == NULL){
      conjunto_apagar(&conjACopia);
      return NULL;
    }

    /*Mesma lógica usada com o TAD lista*/
    while(avl_get_tamanho(conjACopia->conjuntoAVL) > 0){
      int chaveRaiz = avl_get_chave_raiz(conjACopia->conjuntoAVL);
      if (chaveRaiz == ERRO) break;
      int elemento = avl_remover(conjACopia->conjuntoAVL, chaveRaiz);
      if (elemento == ERRO) break;
      if(conjunto_pertence(conjBOriginal, elemento)){
        conjunto_inserir(conjIntersec, elemento);
      }
    }

    conjunto_apagar(&conjACopia);
  }

  if (conjIntersec->tamanho == 0){
    printf("Conjunto intersecção vazio!\n");
    conjunto_apagar(&conjIntersec);
    return NULL;
  }

  return conjIntersec;
}

/*Análoga à criar*/
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
    copiaConj->conjuntoAVL = avl_copiar(conj->conjuntoAVL);
  }

  if((copiaConj->conjuntoLista == NULL) && (copiaConj->conjuntoAVL == NULL)){
    /*Houve um erro ao criar a lista ou a árvore*/
    conjunto_apagar(&copiaConj);
    return NULL;
  }
  
  copiaConj->tamanho = conj->tamanho;
  return copiaConj;
}
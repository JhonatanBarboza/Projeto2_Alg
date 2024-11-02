#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lista.h"
#include "../ABB.h"
#include "../conjunto.h"

struct conjunto_{
  int TAD;
  LISTA *conjuntoLista;
  ABB *conjuntoABB;
  int tamanho;
};

CONJUNTO *conjunto_criar(int TAD){
  if((TAD != TAD_LISTA) && (TAD != TAD_ARVORE)) return NULL;

  CONJUNTO *conjunto = (CONJUNTO *) malloc(sizeof(CONJUNTO));
  if(conjunto == NULL) return NULL;

  conjunto->TAD = TAD;
  conjunto->tamanho = 0;
  if(TAD == TAD_LISTA){
    conjunto->conjuntoLista = Lista_Criar();
    conjunto->conjuntoABB = NULL;
  }
  else if(TAD == TAD_ARVORE){
    conjunto->conjuntoABB = abb_criar();
    conjunto->conjuntoLista = NULL;
  }

  return conjunto;
}

bool conjunto_apagar(CONJUNTO **conj){
  if(*conj == NULL) return true;

  if((*conj)->TAD == TAD_LISTA){
    Lista_Apagar(&((*conj)->conjuntoLista));
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
    Lista_Inserir(conj->conjuntoLista, elemento);
  }
  else{
    abb_inserir(conj->conjuntoABB, elemento);
  }

  conj->tamanho++;
  return true;
}

int conjunto_remover(CONJUNTO *conj){
  if(conj == NULL) return ERRO;

  int elementoRemovido;
  if(conj->TAD == TAD_LISTA){
    elementoRemovido =  Lista_Remover(conj->conjuntoLista);
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
    Lista_Imprimir(conj->conjuntoLista);
  }
  else{
    abb_imprimir(conj->conjuntoABB, true);
  }

  return;
}

bool conjunto_pertence(CONJUNTO *conj, int elemento){
  if(conj == NULL) return false;

  if(conj->TAD == TAD_LISTA){
    return busca_binaria(conj->conjuntoLista, elemento);
  }
  else{
    if(elemento == abb_busca(conj->conjuntoABB, elemento)) return true;
  }

  return false;
}

CONJUNTO *conjunto_uniao(CONJUNTO *conjAOriginal, CONJUNTO *conjBOriginal){
  if((conjAOriginal == NULL) || (conjBOriginal == NULL)) return NULL;

  CONJUNTO *conjA = conjunto_copiar(conjAOriginal);
  CONJUNTO *conjB = conjunto_copiar(conjBOriginal);
  if((conjA == NULL) || (conjB == NULL)) return NULL;

  CONJUNTO *conjUniao = conjunto_criar(conjAOriginal->TAD);

  if(conjUniao->TAD == TAD_LISTA){
    for(int i = 0; i < conjA->tamanho; i++){
      int elemento = Lista_Remover(conjA->conjuntoLista);
      Lista_Inserir(conjUniao->conjuntoLista, elemento);

      conjUniao->tamanho++;
    }

    for(int i = 0; i < conjB->tamanho; i++){
      int elemento = Lista_Remover(conjB->conjuntoLista);

      if(!busca_binaria(conjUniao->conjuntoLista, elemento)){
        Lista_Inserir(conjUniao->conjuntoLista, elemento);

        conjUniao->tamanho++;
      }
    }
  }

  if(conjUniao->TAD == TAD_ARVORE){
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
  CONJUNTO *conjB = conjunto_copiar(conjBOriginal);
  if((conjA == NULL) || (conjB == NULL)) return NULL;

  CONJUNTO *conjIntersec = conjunto_criar(conjAOriginal->TAD);

  if(conjIntersec->TAD == TAD_LISTA){
    for(int i = 0; i < conjA->tamanho; i++){
      int elemento = Lista_Remover(conjA->conjuntoLista);

      if(busca_binaria(conjB->conjuntoLista, elemento)){
        Lista_Inserir(conjIntersec->conjuntoLista, elemento);

        conjIntersec->tamanho++;
      }
    }
    for(int i = 0; i < conjB->tamanho; i++){
      int elemento = Lista_Remover(conjB->conjuntoLista);

      if(busca_binaria(conjA->conjuntoLista, elemento)){
        Lista_Inserir(conjIntersec->conjuntoLista, elemento);

        conjIntersec->tamanho++;
      }
    }
  }

  if(conjIntersec->TAD == TAD_ARVORE){
    for(int i = 0; i < conjA->tamanho; i++){
      int elemento = abb_remover(conjA->conjuntoABB);

      if(abb_busca(conjB->conjuntoABB, elemento) == elemento){
        abb_inserir(conjIntersec->conjuntoABB, elemento);

        conjIntersec->tamanho++;
      }
    }
    for(int i = 0; i < conjB->tamanho; i++){
      int elemento = abb_remover(conjB->conjuntoABB);

      if(abb_busca(conjA->conjuntoABB, elemento) == elemento){
        abb_inserir(conjIntersec->conjuntoABB, elemento);
        
        conjIntersec->tamanho++;
      }
    } 
  }

  return conjIntersec;
}

CONJUNTO *conjunto_copiar(CONJUNTO *conj){
  if(conj == NULL){
    printf("Erro em conjunto_copiar: conj == NULL\n");
    return NULL;
  }

  CONJUNTO *copiaConj = conjunto_criar(conj->TAD);
  if(copiaConj == NULL){
    printf("Erro em conjunto_copiar: copiaConj == NULL\n");
    conjunto_apagar(&copiaConj);
    return NULL;
  }
  copiaConj->TAD = conj->TAD;

  if(copiaConj->TAD == TAD_LISTA){
    copiaConj->conjuntoLista = Lista_Copiar(conj->conjuntoLista);
  }
  else{
    copiaConj->conjuntoABB = abb_copiar(conj->conjuntoABB);
  }

  copiaConj->tamanho = conj->tamanho;
  return copiaConj;
}
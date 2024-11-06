#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../heapmax.h"

struct heapmax_{
  int vet[TAM_MAX];
  int tamanho;
};

HEAPMAX *heapmax_criar(void){
  HEAPMAX *pontHeap = (HEAPMAX *) malloc(sizeof(HEAPMAX));
  if(pontHeap == NULL){
    printf("Erro em heapmax_criar: pontHeap == NULL\n");
    return NULL;
  }

  pontHeap->tamanho = 0;
  
  return pontHeap;
}

bool heapmax_inserir(HEAPMAX *heap, int elemento){
  if(heap == NULL){
    printf("Erro em heapmax_inserir: heap == NULL\n");
    return false;
  }
  if(heapmax_cheia(heap)){
    printf("heapmax_inserir: heapmax cheia\n");
    return false;
  }

  heap->vet[heap->tamanho] = elemento;
  int tamHeap = heap->tamanho;
  while(tamHeap > 0 && heap->vet[(tamHeap-1)/2] < heap->vet[tamHeap]){
    int aux = heap->vet[tamHeap];
    heap->vet[tamHeap] = heap->vet[(tamHeap-1)/2];
    heap->vet[(tamHeap-1)/2] = aux;
    tamHeap = (tamHeap-1)/2;
  }

  heap->tamanho++;

  return true;
}


int heapmax_remover(HEAPMAX *heap){
  if(heap == NULL){
    printf("Erro em heapmax_remover: heap == NULL\n");
    return ERRO;
  }
  if(heapmax_vazia(heap)){
    printf("heapmax_remover: heapmax vazia\n");
    return ERRO;
  }

  int elementoRemovido = heap->vet[heap->tamanho];
  heap->vet[heap->tamanho] = ERRO;
  heap->tamanho--;

  return elementoRemovido;
}


void heapmax_rearranjar(HEAPMAX *heap, int i, int tamHeap){
  if(heap == NULL){
    printf("Erro em heapmax_inserir: heap == NULL\n");
    return;
  }
  if(heapmax_vazia(heap)){
    printf("heapmax_rearranjar: heapmax vazia\n");
    return;
  }

  int esq, dir, maior, aux;
  esq = 2*i + 1;
  dir = 2*i + 2;
  maior = i;

  /*Encontrando o maior elemento entre o filho da direita e da esquerda*/
  if((esq < tamHeap) && (heap->vet[esq] > heap->vet[maior])){
    maior = esq;
  }
  if((dir < tamHeap) && (heap->vet[dir] > heap->vet[maior])){
    maior = dir;
  }

  /*Fazendo o swap e repetindo para o próximo nível*/
  if(maior != i){
    aux = heap->vet[maior];
    heap->vet[maior] = heap->vet[i];
    heap->vet[i] = aux;

    heapmax_rearranjar(heap, maior, tamHeap);
  }

  return;
}

void heapSort(HEAPMAX *heap, int tamHeap){
  if(heap == NULL){
    printf("Erro em heapSort: heap == NULL\n");
    return;
  }
  if(heapmax_vazia(heap)){
    printf("heapSort: heapmax vazia\n");
    return;
  }

  for(int i = tamHeap - 1; i > 0; i--){
    int aux = heap->vet[0];
    heap->vet[0] = heap->vet[i];
    heap->vet[i] = aux;

    tamHeap--;
    heapmax_rearranjar(heap, 0, tamHeap);
  }

  return;
}

bool heapmax_cheia(HEAPMAX *heap){
  if(heap == NULL){
    printf("Erro em heapmax_cheia: heap == NULL\n");
    return false;
  }
  if(heap->tamanho == TAM_MAX){
    return true;
  }

  return false;
}

bool heapmax_vazia(HEAPMAX *heap){
  if(heap == NULL){
    printf("Erro em heapmax_vazia: heap == NULL\n");
    return false;
  }
  if(heap->tamanho == 0){
    return true;
  }

  return false;
}

int heapmax_tamanho(HEAPMAX *heap){
  if(heap == NULL){
    printf("Erro em heapmax_tamanho: heap == NULL\n");
    return ERRO;
  }

  return heap->tamanho;
}

void heapmax_imprimir(HEAPMAX *heap){
  if(heap == NULL){
    printf("Erro em heapmax_imprimir: heap == NULL\n");
    return;
  }
  if(heapmax_vazia(heap)){
    printf("heapmax_imprimir: heap vazia\n");
    return;
  }

  for(int i = 0; i < heap->tamanho - 1; i++){
    printf("%d ", heap->vet[i]);
  }
  printf("%d\n", heap->vet[heap->tamanho - 1]);

  return;
}

void heapmax_apagar(HEAPMAX **heap){
  if(*heap != NULL){
    free(*heap);
    *heap = NULL;
  }

  return;
}

int buscaBinaria(HEAPMAX *heap, int inicio, int fim, int chave){
  if(heap == NULL){
    printf("Erro em buscaBinaria: heap == NULL\n");
    return ERRO;
  }
  if(heapmax_vazia(heap)){
    printf("buscaBinaria: heap vazia\n");
    return ERRO;
  }
  if(inicio > fim){
    return ERRO;
  }

  int meio = inicio + (fim - inicio) / 2;

  if(heap->vet[meio] == chave){
    return meio;
  }
  if(inicio == fim){
    return ERRO;
  }

  if(chave > heap->vet[meio]){
    return buscaBinaria(heap, meio + 1, fim, chave);
  }
  else{
    return buscaBinaria(heap, inicio, meio, chave);
  }

  return ERRO;
}
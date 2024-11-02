#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lista.h"

struct lista_ {
  int vet[TAM_MAX];
  int tamanho;
};

int buscaBinariaLista(int v[], int inicio, int fim, int chave);

LISTA *lista_criar(void){
  LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
  if(lista == NULL){
    printf("Erro em lista_criar: lista == NULL\n");
    return NULL;
  }

  lista->tamanho = 0;
  return lista;
}

void lista_apagar(LISTA **lista){
  if(*lista == NULL) return;

  free(*lista);
  *lista = NULL;
  return;
}

bool lista_inserir(LISTA *lista, int elemento){
  if(lista == NULL){
    printf("Erro em lista_inserir: lista == NULL\n");
    return false;
  }
  if(lista->tamanho > TAM_MAX) return false;

  int i = 0;
  while((i < lista->tamanho) && (lista->vet[i] < elemento)) i++;
  if(lista_busca(lista, elemento) == elemento) return false;

  for(int j = lista->tamanho; j > i; j--){
    lista->vet[j] = lista->vet[j-1];
  }
  lista->vet[i] = elemento;
  lista->tamanho++;

  return true;
}

int lista_remover(LISTA *lista){
  if(lista == NULL){
    printf("Erro em lista_remover: lista == NULL\n");
    return ERRO;
  }
  if(lista->tamanho == 0) return ERRO;

  int elemRemovido = lista->vet[lista->tamanho - 1];
  lista->vet[lista->tamanho - 1] = ERRO;
  lista->tamanho--;

  return elemRemovido;
}

void lista_imprimir(LISTA *lista){
  if(lista == NULL){
    printf("Erro em lista_imprimir: lista == NULL\n");
    return;
  }

  for(int i = 0; i < lista->tamanho; i++){
    if(lista->vet[i] != ERRO) printf("%d ", lista->vet[i]);
  }
  printf("\n");
  fflush(stdout);

  return;
}

int lista_busca(LISTA *lista, int chave){
  if(lista == NULL){
    printf("Erro em lista_busca: lista == NULL\n");
    return ERRO;
  }
  if(lista->tamanho == 0) return ERRO;

  if(buscaBinariaLista(lista->vet, 0, lista->tamanho - 1, chave) != ERRO) return chave;
  return ERRO;
}

LISTA *lista_copiar(LISTA *lista){
  if(lista == NULL){
    printf("Erro em lista_copiar: lista == NULL\n");
    return NULL;
  }

  LISTA *listaCopia = lista_criar();
  if(listaCopia == NULL){
    printf("Erro em lista_copiar: listaCopia == NULL\n");
    return NULL;
  }

  for(int i = 0; i < lista->tamanho; i++){
    lista_inserir(listaCopia, lista->vet[i]);
  }

  return listaCopia;
}

int buscaBinariaLista(int v[], int inicio, int fim, int chave){
  if(inicio > fim) return ERRO;

  int meio = (inicio + fim) / 2;

  if(v[meio] == chave) return meio;
  else if(chave < v[meio]) return buscaBinariaLista(v, inicio, meio - 1, chave);
  else{
    return buscaBinariaLista(v, meio + 1, fim, chave);
  }
}
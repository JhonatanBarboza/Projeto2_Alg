// lista.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lista.h"

struct lista_ {
    int vet[TAM_MAX];
    int tamanho;
};

// Função auxiliar para busca binária
bool busca_binaria(LISTA *lista, int elemento) {
    if(lista == NULL) return false;
    if(lista->tamanho == 0) return false;

    int esquerda = 0, direita = lista->tamanho - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (lista->vet[meio] == elemento) {
            return true;
        } else if (lista->vet[meio] < elemento) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return false;
}

LISTA* Lista_Criar(void) {
    LISTA *lista = (LISTA*)malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->tamanho = 0;
    }

    return lista;
}

void Lista_Apagar(LISTA **lista) {
    if(*lista == NULL) return;

    free(*lista);
    *lista = NULL;
    return;
}

void Lista_Inserir(LISTA *lista, int elemento) {
    if(lista == NULL) return;
    if(lista->tamanho == TAM_MAX) return;

    // Encontra posição para inserção para manter a ordenação
    int i = lista->tamanho - 1;
    while (i >= 0 && lista->vet[i] > elemento) {
        lista->vet[i + 1] = lista->vet[i];
        i--;
    }
    lista->vet[i + 1] = elemento;
    lista->tamanho++;

    return;
}

int Lista_Remover(LISTA *lista) {
    if(lista == NULL) return ERRO;
    if(lista->tamanho == 0) return ERRO;

    int temp = lista->vet[lista->tamanho];
    lista->vet[lista->tamanho] = ERRO;
    lista->tamanho--;

    return temp;
}

void Lista_Imprimir(LISTA *lista) {
    if(lista == NULL) return;
    if(lista->tamanho == 0) return;

    for (int i = 0; i < lista->tamanho; i++) {
        printf("%d ", lista->vet[i]);
    }
    printf("\n");
}

int Lista_Consultar (LISTA *lista, int i){
    if(lista == NULL) return ERRO;
    if(i > lista->tamanho) return ERRO;

    return lista->vet[i];
} 


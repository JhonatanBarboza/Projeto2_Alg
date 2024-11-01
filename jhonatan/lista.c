// lista.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

typedef struct Lista_ {
    int *dados;
    int tamanho;
    int capacidade;
}LISTA;

// Função auxiliar para busca binária
bool busca_binaria(LISTA *lista, int elemento) {
    int esquerda = 0, direita = lista->tamanho - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (lista->dados[meio] == elemento) {
            return true;
        } else if (lista->dados[meio] < elemento) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return false;
}

LISTA* Lista_Criar(int capacidade) {
    LISTA *lista = (LISTA*)malloc(sizeof(LISTA));
    lista->dados = (int*)malloc(capacidade * sizeof(int));
    lista->tamanho = 0;
    lista->capacidade = capacidade;
    return lista;
}

void Lista_Apagar(LISTA *lista) {
    free(lista->dados);
    free(lista);
}

bool Lista_cheia(LISTA *lista){
    return lista->tamanho == lista->capacidade;
}

bool Lista_vazia(LISTA *lista){
    return lista->tamanho == 0;
}

void Lista_Inserir(LISTA *lista, int elemento) {
    if (Lista_cheia(lista)) {
        printf("Lista cheia!\n");
        lista->capacidade *= 2;
        lista->dados = (int*)realloc(lista->dados, lista->capacidade * sizeof(int));
    }

    // Encontra posição para inserção para manter a ordenação
    int i = lista->tamanho - 1;
    while (i >= 0 && lista->dados[i] > elemento) {
        lista->dados[i + 1] = lista->dados[i];
        i--;
    }
    lista->dados[i + 1] = elemento;
    lista->tamanho++;
}

void Lista_Remover(LISTA *lista, int elemento) {
    if (Lista_vazia(lista)) {
        printf("Lista vazia!\n");
        return;
    }

    // Encontra a posição do elemento a ser removido
    int pos = -1;
    for (int i = 0; i < lista->tamanho; i++) {
        if (lista->dados[i] == elemento) {
            pos = i;
            break;
        }
    }

    // Se o elemento não for encontrado, retorne
    if (pos == -1) {
        printf("Elemento não encontrado!\n");
        return;
    }

    // Remove o elemento deslocando os itens para a esquerda
    for (int i = pos; i < lista->tamanho - 1; i++) {
        lista->dados[i] = lista->dados[i + 1];
    }

    // Reduz o tamanho da lista
    lista->tamanho--;
}


void Lista_Imprimir(LISTA *lista) {
    if (lista->tamanho == 0){
        printf("Conjunto vazio!\n");
    }
    else {
    for (int i = 0; i < lista->tamanho; i++) {
        printf("%d ", lista->dados[i]);
    }
    printf("\n");
    }
}

int Lista_Consultar (LISTA *lista, int i){
    return lista->dados[i];
} 


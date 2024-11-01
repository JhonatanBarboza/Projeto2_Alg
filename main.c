#include "conjunto.h"
#include "arvore.h"
#include "lista.h"
#include <stdio.h>

// Funções auxiliares para modularizar o código

void Inicializar_Listas(LISTA** lista_A, LISTA** lista_B, int tamanho_A, int tamanho_B) {
    *lista_A = Lista_Criar(tamanho_A);
    *lista_B = Lista_Criar(tamanho_B);
    int temp;

    for (int i = 0; i < tamanho_A; i++) {
        scanf(" %d", &temp);
        Lista_Inserir(*lista_A, temp);
    }

    for (int i = 0; i < tamanho_B; i++) {
        scanf(" %d", &temp);
        Lista_Inserir(*lista_B, temp);
    }
}

void Inicializar_Arvores(ARVORE** arvore_A, ARVORE** arvore_B, int tamanho_A, int tamanho_B) {
    *arvore_A = Arvore_Criar(tamanho_A);
    *arvore_B = Arvore_Criar(tamanho_B);
    int temp;

    for (int i = 0; i < tamanho_A; i++) {
        scanf(" %d", &temp);
        Arvore_Inserir(*arvore_A, temp);
    }

    for (int i = 0; i < tamanho_B; i++) {
        scanf(" %d", &temp);
        Arvore_Inserir(*arvore_B, temp);
    }
}

void Executar_Operacao_Lista(LISTA* lista_A, int tamanho_A, LISTA* lista_B, int tamanho_B, int operacao, int elemento) {
    switch (operacao) {
        case 1:
            Conjunto_Pertence_0(lista_A, tamanho_A, elemento);
            break;
        case 2:
            Conjunto_Uniao_0(lista_A, tamanho_A, lista_B, tamanho_B);
            break;
        case 3:
            Conjunto_Intersecao_0(lista_A, tamanho_A, lista_B, tamanho_B);
            break;
        default:
            printf("Comando inválido!\n");
    }
}

void Executar_Operacao_Arvore(ARVORE* arvore_A, int tamanho_A, ARVORE* arvore_B, int tamanho_B, int operacao, int elemento) {
    switch (operacao) {
        case 1:
            Conjunto_Pertence_1(arvore_A, tamanho_A, elemento);
            break;
        case 2:
            Conjunto_Uniao_1(arvore_A, tamanho_A, arvore_B, tamanho_B);
            break;
        case 3:
            Conjunto_Intersecao_1(arvore_A, tamanho_A, arvore_B, tamanho_B);
            break;
        default:
            printf("Comando inválido!\n");
    }
}

int main() {
    int TAD, tamanho_A, tamanho_B, operacao, elemento = 0;

    ARVORE* arvore_A = NULL;
    ARVORE* arvore_B = NULL;
    LISTA* lista_A = NULL;  
    LISTA* lista_B = NULL;

    scanf(" %d %d %d", &TAD, &tamanho_A, &tamanho_B);

    if (TAD == 0) {
        Inicializar_Listas(&lista_A, &lista_B, tamanho_A, tamanho_B);
    } else if (TAD == 1) {
        Inicializar_Arvores(&arvore_A, &arvore_B, tamanho_A, tamanho_B);
    } else {
        printf("Comando inválido!\n");
        return 1;
    }

    scanf("%d", &operacao);
    if (operacao == 1) {
        scanf("%d", &elemento);
    }

    if (TAD == 0) {
        Executar_Operacao_Lista(lista_A, tamanho_A, lista_B, tamanho_B, operacao, elemento);
    } else if (TAD == 1) {
        Executar_Operacao_Arvore(arvore_A, tamanho_A, arvore_B, tamanho_B, operacao, elemento);
    }

    return 0;
}

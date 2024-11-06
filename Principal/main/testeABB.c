#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../bibliotecas/ABB.h"

void test_criar_e_apagar() {
    printf("\nTeste 1: Criar e apagar árvore\n");
    ABB *arvore = abb_criar();
    if (arvore != NULL) {
        printf("✓ Árvore criada com sucesso\n");
    } else {
        printf("✗ Falha ao criar árvore\n");
        return;
    }
    
    abb_apagar(&arvore);
    if (arvore == NULL) {
        printf("✓ Árvore apagada com sucesso\n");
    } else {
        printf("✗ Falha ao apagar árvore\n");
    }
}

void test_inserir() {
    printf("\nTeste 2: Inserir elementos\n");
    ABB *arvore = abb_criar();
    
    int elementos[] = {50, 30, 70, 20, 40, 60, 80};
    int n_elementos = sizeof(elementos) / sizeof(elementos[0]);
    
    for (int i = 0; i < n_elementos; i++) {
        if (abb_inserir(arvore, elementos[i])) {
            printf("✓ Elemento %d inserido com sucesso\n", elementos[i]);
        } else {
            printf("✗ Falha ao inserir elemento %d\n", elementos[i]);
        }
    }
    
    printf("\nImpressão ordenada: ");
    abb_imprimir(arvore, true);
    printf("Impressão não ordenada: ");
    abb_imprimir(arvore, false);
    
    abb_apagar(&arvore);
}

void test_busca() {
    printf("\nTeste 3: Buscar elementos\n");
    ABB *arvore = abb_criar();
    
    // Inserir alguns elementos para teste
    int elementos[] = {50, 30, 70, 20, 40, 60, 80};
    int n_elementos = sizeof(elementos) / sizeof(elementos[0]);
    
    for (int i = 0; i < n_elementos; i++) {
        abb_inserir(arvore, elementos[i]);
    }
    
    // Testar busca de elementos existentes e não existentes
    int buscar[] = {40, 90, 20, 100};
    for (int i = 0; i < 4; i++) {
        int resultado = abb_busca(arvore, buscar[i]);
        if (resultado != ERRO) {
            printf("✓ Elemento %d encontrado\n", buscar[i]);
        } else {
            printf("✗ Elemento %d não encontrado\n", buscar[i]);
        }
    }
    
    abb_apagar(&arvore);
}

void test_remover() {
    printf("\nTeste 4: Remover elementos\n");
    ABB *arvore = abb_criar();
    
    // Inserir elementos
    int elementos[] = {50, 30, 70, 20, 40, 60, 80};
    int n_elementos = sizeof(elementos) / sizeof(elementos[0]);
    
    for (int i = 0; i < n_elementos; i++) {
        abb_inserir(arvore, elementos[i]);
    }
    
    printf("Árvore inicial: ");
    abb_imprimir(arvore, true);
    
    // Testar remoção da raiz algumas vezes
    for (int i = 0; i < 3; i++) {
        int removido = abb_remover(arvore);
        if (removido != ERRO) {
            printf("✓ Elemento %d removido com sucesso\n", removido);
            printf("Árvore após remoção: ");
            abb_imprimir(arvore, true);
        } else {
            printf("✗ Falha ao remover elemento\n");
        }
    }
    
    abb_apagar(&arvore);
}

int main() {
    printf("Iniciando testes da ABB (Árvore Binária de Busca)\n");
    printf("================================================\n");
    
    test_criar_e_apagar();
    test_inserir();
    test_busca();
    test_remover();
    
    printf("\nTestes concluídos!\n");
    return 0;
}
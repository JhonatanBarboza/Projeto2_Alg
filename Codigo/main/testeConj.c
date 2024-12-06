#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../bibliotecas/conjunto.h"

/*Gerado pelo CLAUDE*/

void testar_conjunto_lista();
void testar_conjunto_arvore();
void imprimir_pertence(CONJUNTO *conj, int elemento);

int main() {
    printf("\n=== Testando implementação com Lista ===\n");
    testar_conjunto_lista();
    
    printf("\n=== Testando implementação com Árvore ===\n");
    testar_conjunto_arvore();
    
    return 0;
}

void testar_conjunto_lista() {
    // Criar conjuntos
    CONJUNTO *conjA = conjunto_criar(TAD_LISTA);
    CONJUNTO *conjB = conjunto_criar(TAD_LISTA);
    
    if (!conjA || !conjB) {
        printf("Erro ao criar conjuntos!\n");
        return;
    }
    
    // Inserir elementos no conjunto A
    printf("\nInserindo elementos no conjunto A: 1, 3, 5, 7, 9\n");
    conjunto_inserir(conjA, 1);
    conjunto_inserir(conjA, 3);
    conjunto_inserir(conjA, 5);
    conjunto_inserir(conjA, 7);
    conjunto_inserir(conjA, 9);
    
    printf("Conjunto A: ");
    conjunto_imprimir(conjA);
    
    // Inserir elementos no conjunto B
    printf("\nInserindo elementos no conjunto B: 2, 3, 4, 5, 6\n");
    conjunto_inserir(conjB, 2);
    conjunto_inserir(conjB, 3);
    conjunto_inserir(conjB, 4);
    conjunto_inserir(conjB, 5);
    conjunto_inserir(conjB, 6);
    
    printf("Conjunto B: ");
    conjunto_imprimir(conjB);
    
    // Testar pertence
    printf("\nTestando pertinência:\n");
    imprimir_pertence(conjA, 3);  // Deve pertencer
    imprimir_pertence(conjA, 4);  // Não deve pertencer
    
    // Testar união
    printf("\nUnião dos conjuntos A e B:\n");
    CONJUNTO *uniao = conjunto_uniao(conjA, conjB);
    if (uniao) {
        conjunto_imprimir(uniao);
        conjunto_apagar(&uniao);
    }
    
    // Testar interseção
    printf("\nInterseção dos conjuntos A e B:\n");
    CONJUNTO *intersecao = conjunto_interseccao(conjA, conjB);
    if (intersecao) {
        conjunto_imprimir(intersecao);
        conjunto_apagar(&intersecao);
    }
    
    // Testar remoção
    printf("\nRemovendo elemento 5 do conjunto A:\n");
    conjunto_remover(conjA, 5);
    printf("Conjunto A após remoção: ");
    conjunto_imprimir(conjA);
    
    // Testar cópia
    printf("\nCriando cópia do conjunto A:\n");
    CONJUNTO *copia = conjunto_copiar(conjA);
    if (copia) {
        printf("Cópia do conjunto A: ");
        conjunto_imprimir(copia);
        conjunto_apagar(&copia);
    }
    
    // Limpar memória
    conjunto_apagar(&conjA);
    conjunto_apagar(&conjB);
}

void testar_conjunto_arvore() {
    // Criar conjuntos
    CONJUNTO *conjA = conjunto_criar(TAD_ARVORE);
    CONJUNTO *conjB = conjunto_criar(TAD_ARVORE);
    
    if (!conjA || !conjB) {
        printf("Erro ao criar conjuntos!\n");
        return;
    }
    
    // Inserir elementos no conjunto A
    printf("\nInserindo elementos no conjunto A: 10, 5, 15, 3, 7\n");
    conjunto_inserir(conjA, 10);
    conjunto_inserir(conjA, 5);
    conjunto_inserir(conjA, 15);
    conjunto_inserir(conjA, 3);
    conjunto_inserir(conjA, 7);
    
    printf("Conjunto A: ");
    conjunto_imprimir(conjA);
    
    // Inserir elementos no conjunto B
    printf("\nInserindo elementos no conjunto B: 7, 12, 15, 9, 4\n");
    conjunto_inserir(conjB, 7);
    conjunto_inserir(conjB, 12);
    conjunto_inserir(conjB, 15);
    conjunto_inserir(conjB, 9);
    conjunto_inserir(conjB, 4);
    
    printf("Conjunto B: ");
    conjunto_imprimir(conjB);
    
    // Testar pertence
    printf("\nTestando pertinência:\n");
    imprimir_pertence(conjA, 7);  // Deve pertencer
    imprimir_pertence(conjA, 12); // Não deve pertencer
    
    // Testar união
    printf("\nUnião dos conjuntos A e B:\n");
    CONJUNTO *uniao = conjunto_uniao(conjA, conjB);
    if (uniao) {
        conjunto_imprimir(uniao);
        conjunto_apagar(&uniao);
    }
    
    // Testar interseção
    printf("\nInterseção dos conjuntos A e B:\n");
    CONJUNTO *intersecao = conjunto_interseccao(conjA, conjB);
    if (intersecao) {
        conjunto_imprimir(intersecao);
        conjunto_apagar(&intersecao);
    }
    
    // Testar remoção
    printf("\nRemovendo elemento 5 do conjunto A:\n");
    conjunto_remover(conjA, 5);
    printf("Conjunto A após remoção: ");
    conjunto_imprimir(conjA);
    
    // Testar cópia
    printf("\nCriando cópia do conjunto A:\n");
    CONJUNTO *copia = conjunto_copiar(conjA);
    if (copia) {
        printf("Cópia do conjunto A: ");
        conjunto_imprimir(copia);
        conjunto_apagar(&copia);
    }
    
    // Limpar memória
    conjunto_apagar(&conjA);
    conjunto_apagar(&conjB);
}

void imprimir_pertence(CONJUNTO *conj, int elemento) {
    if (conjunto_pertence(conj, elemento)) {
        printf("O elemento %d pertence ao conjunto\n", elemento);
    } else {
        printf("O elemento %d NÃO pertence ao conjunto\n", elemento);
    }
}
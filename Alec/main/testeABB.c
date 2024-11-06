#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ABB.h"

#define ERRO -1

void test_criar_apagar(void) {
    printf("\n=== Testing Creation and Deletion ===\n");
    
    ABB *arvore = abb_criar();
    if (arvore == NULL) {
        printf("FAILED: Tree creation returned NULL\n");
        return;
    }
    printf("PASSED: Tree created successfully\n");
    
    abb_apagar(&arvore);
    if (arvore != NULL) {
        printf("FAILED: Tree not NULL after deletion\n");
        return;
    }
    printf("PASSED: Tree deleted successfully\n");
}

void test_insercao(void) {
    printf("\n=== Testing Insertion ===\n");
    
    ABB *arvore = abb_criar();
    
    // Test inserting root
    if (!abb_inserir(arvore, 50)) {
        printf("FAILED: Could not insert root node (50)\n");
        abb_apagar(&arvore);
        return;
    }
    printf("PASSED: Root node (50) inserted successfully\n");
    
    // Test inserting left and right children
    if (!abb_inserir(arvore, 30) || !abb_inserir(arvore, 70)) {
        printf("FAILED: Could not insert children nodes (30, 70)\n");
        abb_apagar(&arvore);
        return;
    }
    printf("PASSED: Left and right children (30, 70) inserted successfully\n");
    
    // Test inserting more nodes to create a complex tree
    int values[] = {20, 40, 60, 80, 35, 45, 65, 75};
    for (int i = 0; i < 8; i++) {
        if (!abb_inserir(arvore, values[i])) {
            printf("FAILED: Could not insert node (%d)\n", values[i]);
            abb_apagar(&arvore);
            return;
        }
    }
    printf("PASSED: Complex tree created successfully\n");
    
    // Print the tree both ordered and unordered
    printf("In-order traversal (should be sorted): ");
    abb_imprimir(arvore, true);
    printf("Pre-order traversal: ");
    abb_imprimir(arvore, false);
    
    abb_apagar(&arvore);
}

void test_busca(void) {
    printf("\n=== Testing Search ===\n");
    
    ABB *arvore = abb_criar();
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    
    // Insert test values
    for (int i = 0; i < 7; i++) {
        abb_inserir(arvore, values[i]);
    }
    
    // Test searching for existing values
    for (int i = 0; i < 7; i++) {
        int result = abb_busca(arvore, values[i]);
        if (result == -1) {
            printf("FAILED: Could not find existing value %d\n", values[i]);
        } else {
            printf("PASSED: Found value %d\n", values[i]);
        }
    }
    
    // Test searching for non-existent value
    int result = abb_busca(arvore, 45);
    if (result != -1) {
        printf("FAILED: Found non-existent value 45\n");
    } else {
        printf("PASSED: Correctly did not find value 45\n");
    }
    
    abb_apagar(&arvore);
}

void test_remocao(void) {
    printf("\n=== Testing Removal ===\n");
    
    ABB *arvore = abb_criar();
    int values[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    
    // Insert test values
    for (int i = 0; i < 9; i++) {
        abb_inserir(arvore, values[i]);
    }
    
    printf("Initial tree: ");
    abb_imprimir(arvore, true);
    
    // Test removing leaf node
    int removed = abb_remover(arvore, 35);
    if (removed == ERRO) {
        printf("FAILED: Could not remove leaf node 35\n");
    } else {
        printf("PASSED: Removed leaf node 35\n");
        printf("Tree after removing 35: ");
        abb_imprimir(arvore, true);
    }
    
    // Test removing node with one child
    removed = abb_remover(arvore, 20);
    if (removed == ERRO) {
        printf("FAILED: Could not remove node 20 with one child\n");
    } else {
        printf("PASSED: Removed node 20 with one child\n");
        printf("Tree after removing 20: ");
        abb_imprimir(arvore, true);
    }
    
    // Test removing node with two children
    removed = abb_remover(arvore, 30);
    if (removed == ERRO) {
        printf("FAILED: Could not remove node 30 with two children\n");
    } else {
        printf("PASSED: Removed node 30 with two children\n");
        printf("Tree after removing 30: ");
        abb_imprimir(arvore, true);
    }
    
    // Test removing non-existent node
    removed = abb_remover(arvore, 35);
    if (removed != ERRO) {
        printf("FAILED: Should not be able to remove non-existent node 35\n");
    } else {
        printf("PASSED: Correctly failed to remove non-existent node 35\n");
    }
    
    abb_apagar(&arvore);
}

void test_casos_extremos(void) {
    printf("\n=== Testing Edge Cases ===\n");
    
    // Test operations on NULL tree
    ABB *arvore = NULL;
    if (abb_inserir(arvore, 10)) {
        printf("FAILED: Should not be able to insert into NULL tree\n");
    } else {
        printf("PASSED: Correctly failed to insert into NULL tree\n");
    }
    
    if (abb_busca(arvore, 10) != -1) {
        printf("FAILED: Should not be able to search in NULL tree\n");
    } else {
        printf("PASSED: Correctly failed to search in NULL tree\n");
    }
    
    // Test with empty tree
    arvore = abb_criar();
    if (abb_busca(arvore, 10) != -1) {
        printf("FAILED: Should not find value in empty tree\n");
    } else {
        printf("PASSED: Correctly did not find value in empty tree\n");
    }
    
    abb_apagar(&arvore);
}

int main(void) {
    printf("Starting Binary Search Tree Tests\n");
    printf("=================================\n");
    
    test_criar_apagar();
    test_insercao();
    test_busca();
    test_remocao();
    test_casos_extremos();
    
    printf("\nAll tests completed!\n");
    return 0;
}
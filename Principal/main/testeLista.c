#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../bibliotecas/lista.h"

void test_criar(void) {
    printf("\n=== Testing lista_criar ===\n");
    LISTA *lista = lista_criar();
    if (lista != NULL) {
        printf("PASS: Lista created successfully\n");
    } else {
        printf("FAIL: Lista creation failed\n");
    }
    lista_apagar(&lista);
}

void test_inserir(void) {
    printf("\n=== Testing lista_inserir ===\n");
    LISTA *lista = lista_criar();
    
    // Test inserting in ascending order
    printf("Testing ascending insertion:\n");
    bool success = true;
    success &= lista_inserir(lista, 10);
    success &= lista_inserir(lista, 20);
    success &= lista_inserir(lista, 30);
    if (success) {
        printf("PASS: Ascending insertions successful\n");
    } else {
        printf("FAIL: One or more insertions failed\n");
    }
    lista_imprimir(lista);

    // Test inserting in descending order
    printf("\nTesting descending insertion:\n");
    LISTA *lista2 = lista_criar();
    success = true;
    success &= lista_inserir(lista2, 30);
    success &= lista_inserir(lista2, 20);
    success &= lista_inserir(lista2, 10);
    if (success) {
        printf("PASS: Descending insertions successful\n");
    } else {
        printf("FAIL: One or more insertions failed\n");
    }
    lista_imprimir(lista2);

    // Test inserting duplicates
    printf("\nTesting duplicate insertion:\n");
    success = lista_inserir(lista, 20);
    if (success) {
        printf("Duplicate insertion result:\n");
        lista_imprimir(lista);
    }

    lista_apagar(&lista);
    lista_apagar(&lista2);
}

void test_remover(void) {
    printf("\n=== Testing lista_remover ===\n");
    LISTA *lista = lista_criar();
    
    // Test removing from empty list
    int removed = lista_remover(lista);
    if (removed == ERRO) {
        printf("PASS: Correctly handled removal from empty list\n");
    } else {
        printf("FAIL: Should return ERRO for empty list\n");
    }

    // Test normal removal
    lista_inserir(lista, 10);
    lista_inserir(lista, 20);
    lista_inserir(lista, 30);
    
    printf("List before removal:\n");
    lista_imprimir(lista);
    
    removed = lista_remover(lista);
    if (removed == 30) {
        printf("PASS: Correctly removed element 30\n");
    } else {
        printf("FAIL: Removed wrong element or failed\n");
    }
    
    printf("List after removal:\n");
    lista_imprimir(lista);
    
    lista_apagar(&lista);
}

void test_busca(void) {
    printf("\n=== Testing lista_busca ===\n");
    LISTA *lista = lista_criar();
    
    // Insert some elements
    lista_inserir(lista, 10);
    lista_inserir(lista, 20);
    lista_inserir(lista, 30);
    lista_inserir(lista, 40);
    lista_inserir(lista, 50);
    
    printf("Current list:\n");
    lista_imprimir(lista);

    // Test finding existing elements
    int pos = lista_busca(lista, 30);
    if (pos != ERRO) {
        printf("PASS: Found 30 at position %d\n", pos);
    } else {
        printf("FAIL: Couldn't find existing element 30\n");
    }

    // Test finding non-existing elements
    pos = lista_busca(lista, 35);
    if (pos == ERRO) {
        printf("PASS: Correctly returned ERRO for non-existing element\n");
    } else {
        printf("FAIL: Found non-existing element at position %d\n", pos);
    }

    lista_apagar(&lista);
}

void test_copiar(void) {
    printf("\n=== Testing lista_copiar ===\n");
    LISTA *original = lista_criar();
    
    // Insert some elements
    lista_inserir(original, 10);
    lista_inserir(original, 20);
    lista_inserir(original, 30);
    
    printf("Original list:\n");
    lista_imprimir(original);
    
    LISTA *copy = lista_copiar(original);
    if (copy != NULL) {
        printf("Copy result:\n");
        lista_imprimir(copy);
    } else {
        printf("FAIL: Copy operation failed\n");
    }
    
    lista_apagar(&original);
    lista_apagar(&copy);
}

void test_null_handling(void) {
    printf("\n=== Testing NULL handling ===\n");
    
    // Test operations with NULL
    if (!lista_inserir(NULL, 10)) {
        printf("PASS: Correctly handled NULL lista in inserir\n");
    }
    
    if (lista_remover(NULL) == ERRO) {
        printf("PASS: Correctly handled NULL lista in remover\n");
    }
    
    if (lista_busca(NULL, 10) == ERRO) {
        printf("PASS: Correctly handled NULL lista in busca\n");
    }
    
    if (lista_copiar(NULL) == NULL) {
        printf("PASS: Correctly handled NULL lista in copiar\n");
    }
}

int main(void) {
    printf("Starting Lista ADT tests...\n");
    
    test_criar();
    test_inserir();
    test_remover();
    test_busca();
    test_copiar();
    test_null_handling();
    
    printf("\nAll tests completed.\n");
    return 0;
}
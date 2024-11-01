#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../bibliotecas/conjunto.h"

void print_separator() {
    printf("\n====================================\n");
}

void test_conjunto_criar() {
    print_separator();
    printf("TESTING CONJUNTO_CRIAR\n");
    print_separator();
    
    printf("Test 1: Creating TAD_LISTA conjunto\n");
    CONJUNTO *conj_lista = conjunto_criar(TAD_LISTA);
    if (conj_lista != NULL) {
        printf("SUCCESS: List conjunto created\n");
        conjunto_apagar(&conj_lista);
    } else {
        printf("FAIL: Could not create list conjunto\n");
    }

    printf("\nTest 2: Creating TAD_ARVORE conjunto\n");
    CONJUNTO *conj_arvore = conjunto_criar(TAD_ARVORE);
    if (conj_arvore != NULL) {
        printf("SUCCESS: Tree conjunto created\n");
        conjunto_apagar(&conj_arvore);
    } else {
        printf("FAIL: Could not create tree conjunto\n");
    }

    printf("\nTest 3: Testing invalid TAD value\n");
    CONJUNTO *conj_invalid = conjunto_criar(999);
    if (conj_invalid == NULL) {
        printf("SUCCESS: Correctly rejected invalid TAD value\n");
    } else {
        printf("FAIL: Accepted invalid TAD value\n");
        conjunto_apagar(&conj_invalid);
    }
}

void test_conjunto_inserir() {
    print_separator();
    printf("TESTING CONJUNTO_INSERIR\n");
    print_separator();

    printf("Test 1: Inserting into TAD_LISTA conjunto\n");
    CONJUNTO *conj_lista = conjunto_criar(TAD_LISTA);
    if (conjunto_inserir(conj_lista, 10)) {
        printf("SUCCESS: Inserted 10\n");
    } else {
        printf("FAIL: Could not insert 10\n");
    }
    printf("Current conjunto: ");
    conjunto_imprimir(conj_lista);
    conjunto_apagar(&conj_lista);

    printf("\nTest 2: Inserting into TAD_ARVORE conjunto\n");
    CONJUNTO *conj_arvore = conjunto_criar(TAD_ARVORE);
    if (conjunto_inserir(conj_arvore, 20)) {
        printf("SUCCESS: Inserted 20\n");
    } else {
        printf("FAIL: Could not insert 20\n");
    }
    printf("Current conjunto: ");
    conjunto_imprimir(conj_arvore);
    conjunto_apagar(&conj_arvore);

    printf("\nTest 3: Testing NULL conjunto\n");
    if (!conjunto_inserir(NULL, 30)) {
        printf("SUCCESS: Correctly handled NULL conjunto\n");
    } else {
        printf("FAIL: Incorrectly handled NULL conjunto\n");
    }
}

void test_conjunto_pertence() {
    print_separator();
    printf("TESTING CONJUNTO_PERTENCE\n");
    print_separator();

    printf("Test 1: Testing with TAD_LISTA\n");
    CONJUNTO *conj_lista = conjunto_criar(TAD_LISTA);
    conjunto_inserir(conj_lista, 10);
    conjunto_inserir(conj_lista, 20);
    conjunto_inserir(conj_lista, 30);
    printf("Conjunto atual: ");
    conjunto_imprimir(conj_lista);
    
    printf("\nChecking for 20: %s\n", conjunto_pertence(conj_lista, 20) ? "Found" : "Not found");
    printf("Checking for 40: %s\n", conjunto_pertence(conj_lista, 40) ? "Found" : "Not found");
    conjunto_apagar(&conj_lista);

    printf("\nTest 2: Testing with TAD_ARVORE\n");
    CONJUNTO *conj_arvore = conjunto_criar(TAD_ARVORE);
    conjunto_inserir(conj_arvore, 10);
    conjunto_inserir(conj_arvore, 20);
    conjunto_inserir(conj_arvore, 30);
    printf("Conjunto atual: ");
    conjunto_imprimir(conj_arvore);
    
    printf("\nChecking for 20: %s\n", conjunto_pertence(conj_arvore, 20) ? "Found" : "Not found");
    printf("Checking for 40: %s\n", conjunto_pertence(conj_arvore, 40) ? "Found" : "Not found");
    conjunto_apagar(&conj_arvore);
}

void test_conjunto_uniao() {
    print_separator();
    printf("TESTING CONJUNTO_UNIAO\n");
    print_separator();

    printf("Test 1: Union of TAD_LISTA conjuntos\n");
    CONJUNTO *conj_a = conjunto_criar(TAD_LISTA);
    CONJUNTO *conj_b = conjunto_criar(TAD_LISTA);
    
    // Create copies for display since union destroys original sets
    CONJUNTO *display_a = conjunto_criar(TAD_LISTA);
    CONJUNTO *display_b = conjunto_criar(TAD_LISTA);
    
    int valores_a[] = {10, 20, 30};
    int valores_b[] = {20, 30, 40};
    
    for (int i = 0; i < 3; i++) {
        conjunto_inserir(conj_a, valores_a[i]);
        conjunto_inserir(display_a, valores_a[i]);
        conjunto_inserir(conj_b, valores_b[i]);
        conjunto_inserir(display_b, valores_b[i]);
    }
    
    printf("Conjunto A: ");
    conjunto_imprimir(display_a);
    printf("Conjunto B: ");
    conjunto_imprimir(display_b);
    
    CONJUNTO *uniao = conjunto_uniao(conj_a, conj_b);
    printf("União: ");
    if (uniao != NULL) {
        conjunto_imprimir(uniao);
        conjunto_apagar(&uniao);
    } else {
        printf("FAIL: Union operation failed\n");
    }
    
    conjunto_apagar(&display_a);
    conjunto_apagar(&display_b);
}

void test_conjunto_interseccao() {
    print_separator();
    printf("TESTING CONJUNTO_INTERSECCAO\n");
    print_separator();

    printf("Test 1: Intersection of TAD_LISTA conjuntos\n");
    CONJUNTO *conj_a = conjunto_criar(TAD_LISTA);
    CONJUNTO *conj_b = conjunto_criar(TAD_LISTA);
    
    // Create copies for display since intersection destroys original sets
    CONJUNTO *display_a = conjunto_criar(TAD_LISTA);
    CONJUNTO *display_b = conjunto_criar(TAD_LISTA);
    
    int valores_a[] = {10, 20, 30};
    int valores_b[] = {20, 30, 40};
    
    for (int i = 0; i < 3; i++) {
        conjunto_inserir(conj_a, valores_a[i]);
        conjunto_inserir(display_a, valores_a[i]);
        conjunto_inserir(conj_b, valores_b[i]);
        conjunto_inserir(display_b, valores_b[i]);
    }
    
    printf("Conjunto A: ");
    conjunto_imprimir(display_a);
    printf("Conjunto B: ");
    conjunto_imprimir(display_b);
    
    CONJUNTO *intersec = conjunto_interseccao(conj_a, conj_b);
    printf("Intersecção: ");
    if (intersec != NULL) {
        conjunto_imprimir(intersec);
        conjunto_apagar(&intersec);
    } else {
        printf("FAIL: Intersection operation failed\n");
    }
    
    conjunto_apagar(&display_a);
    conjunto_apagar(&display_b);
}

int main() {
    printf("STARTING CONJUNTO ADT TESTS\n");
    
    test_conjunto_criar();
    test_conjunto_inserir();
    test_conjunto_pertence();
    test_conjunto_uniao();
    test_conjunto_interseccao();
    
    printf("\nTESTS COMPLETED\n");
    return 0;
}
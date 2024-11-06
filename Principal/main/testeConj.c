#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../bibliotecas/conjunto.h"

#define ERRO 1000010

// Test function prototypes
bool test_criar(void);
bool test_inserir(void);
bool test_pertence(void);
bool test_remover(void);
bool test_uniao(void);
bool test_interseccao(void);

// Utility function to print test results
void print_test_result(const char* test_name, bool passed, const char* details) {
    printf("\n=== Test: %s ===\n", test_name);
    printf("Result: %s\n", passed ? "PASSED" : "FAILED");
    if (details != NULL) {
        printf("Details: %s\n", details);
    }
    printf("================\n");
}

int main(void) {
    printf("Starting Conjunto ADT Tests...\n\n");
    
    int passed = 0;
    int total = 6;  // Total number of test categories
    
    // Run all tests
    passed += test_criar();
    passed += test_inserir();
    passed += test_pertence();
    passed += test_remover();
    passed += test_uniao();
    passed += test_interseccao();
    
    printf("\n=== Final Test Summary ===\n");
    printf("Passed: %d/%d test categories\n", passed, total);
    printf("Overall Status: %s\n", (passed == total) ? "ALL TESTS PASSED!" : "SOME TESTS FAILED!");
    
    return 0;
}

bool test_criar(void) {
    bool all_passed = true;
    char details[200] = "";
    
    // Test 1: Create with valid TAD_LISTA
    CONJUNTO* conj_lista = conjunto_criar(TAD_LISTA);
    if (conj_lista == NULL) {
        all_passed = false;
        strcat(details, "Failed to create lista conjunto. ");
    }
    
    // Test 2: Create with valid TAD_ARVORE
    CONJUNTO* conj_arvore = conjunto_criar(TAD_ARVORE);
    if (conj_arvore == NULL) {
        all_passed = false;
        strcat(details, "Failed to create arvore conjunto. ");
    }
    
    // Test 3: Create with invalid TAD
    CONJUNTO* conj_invalid = conjunto_criar(99);
    if (conj_invalid != NULL) {
        all_passed = false;
        strcat(details, "Should return NULL for invalid TAD. ");
    }
    
    // Cleanup
    conjunto_apagar(&conj_lista);
    conjunto_apagar(&conj_arvore);
    
    if (all_passed) {
        strcat(details, "All creation tests passed successfully.");
    }
    
    print_test_result("Creation Tests", all_passed, details);
    return all_passed;
}

bool test_inserir(void) {
    bool all_passed = true;
    char details[200] = "";
    
    // Test both implementations
    for (int tad = TAD_LISTA; tad <= TAD_ARVORE; tad++) {
        CONJUNTO* conj = conjunto_criar(tad);
        
        // Test basic insertion
        if (!conjunto_inserir(conj, 10)) {
            all_passed = false;
            sprintf(details + strlen(details), "Failed to insert 10 in TAD %d. ", tad);
        }
        
        // Test multiple insertions
        if (!conjunto_inserir(conj, 20) || !conjunto_inserir(conj, 30)) {
            all_passed = false;
            sprintf(details + strlen(details), "Failed multiple insertions in TAD %d. ", tad);
        }
        
        conjunto_apagar(&conj);
    }
    
    // Test insertion into NULL conjunto
    if (conjunto_inserir(NULL, 10)) {
        all_passed = false;
        strcat(details, "Should fail insertion into NULL conjunto. ");
    }
    
    if (all_passed) {
        strcat(details, "All insertion tests passed successfully.");
    }
    
    print_test_result("Insertion Tests", all_passed, details);
    return all_passed;
}

bool test_pertence(void) {
    bool all_passed = true;
    char details[200] = "";
    
    // Test both implementations
    for (int tad = TAD_LISTA; tad <= TAD_ARVORE; tad++) {
        CONJUNTO* conj = conjunto_criar(tad);
        
        // Insert some elements
        conjunto_inserir(conj, 10);
        conjunto_inserir(conj, 20);
        conjunto_inserir(conj, 30);
        
        // Test presence of inserted elements
        if (!conjunto_pertence(conj, 10) || !conjunto_pertence(conj, 20) || !conjunto_pertence(conj, 30)) {
            all_passed = false;
            sprintf(details + strlen(details), "Failed to find inserted element in TAD %d. ", tad);
        }
        
        // Test absence of non-inserted element
        if (conjunto_pertence(conj, 40)) {
            all_passed = false;
            sprintf(details + strlen(details), "Found non-existent element in TAD %d. ", tad);
        }
        
        conjunto_apagar(&conj);
    }
    
    if (all_passed) {
        strcat(details, "All pertence tests passed successfully.");
    }
    
    print_test_result("Pertence Tests", all_passed, details);
    return all_passed;
}

bool test_remover(void) {
    bool all_passed = true;
    char details[200] = "";
    
    // Test both implementations
    for (int tad = TAD_LISTA; tad <= TAD_ARVORE; tad++) {
        CONJUNTO* conj = conjunto_criar(tad);
        
        // Insert elements
        conjunto_inserir(conj, 10);
        conjunto_inserir(conj, 20);
        
        // Test removal
        int removed = conjunto_remover(conj);
        if (removed == ERRO) {
            all_passed = false;
            sprintf(details + strlen(details), "Failed to remove from non-empty conjunto in TAD %d. ", tad);
        }
        
        conjunto_apagar(&conj);
    }
    
    // Test removal from NULL conjunto
    if (conjunto_remover(NULL) != ERRO) {
        all_passed = false;
        strcat(details, "Should return ERRO when removing from NULL conjunto. ");
    }
    
    if (all_passed) {
        strcat(details, "All removal tests passed successfully.");
    }
    
    print_test_result("Removal Tests", all_passed, details);
    return all_passed;
}

bool test_uniao(void) {
    bool all_passed = true;
    char details[200] = "";
    
    // Test both implementations
    for (int tad = TAD_LISTA; tad <= TAD_ARVORE; tad++) {
        CONJUNTO* conjA = conjunto_criar(tad);
        CONJUNTO* conjB = conjunto_criar(tad);
        
        // Insert elements
        conjunto_inserir(conjA, 10);
        conjunto_inserir(conjA, 20);
        conjunto_inserir(conjB, 20);
        conjunto_inserir(conjB, 30);
        
        // Test union
        CONJUNTO* uniao = conjunto_uniao(conjA, conjB);
        if (uniao == NULL) {
            all_passed = false;
            sprintf(details + strlen(details), "Union operation failed for TAD %d. ", tad);
            continue;
        }
        
        // Note: Original sets are destroyed by union operation
        // This is potentially unexpected behavior that should be documented
        
        conjunto_apagar(&uniao);
    }
    
    // Test union with NULL conjunto
    if (conjunto_uniao(NULL, NULL) != NULL) {
        all_passed = false;
        strcat(details, "Should return NULL when inputs are NULL. ");
    }
    
    if (all_passed) {
        strcat(details, "All union tests passed successfully. Note: Union destroys input sets.");
    }
    
    print_test_result("Union Tests", all_passed, details);
    return all_passed;
}

bool test_interseccao(void) {
    bool all_passed = true;
    char details[200] = "";
    
    // Test both implementations
    for (int tad = TAD_LISTA; tad <= TAD_ARVORE; tad++) {
        CONJUNTO* conjA = conjunto_criar(tad);
        CONJUNTO* conjB = conjunto_criar(tad);
        
        // Insert elements
        conjunto_inserir(conjA, 10);
        conjunto_inserir(conjA, 20);
        conjunto_inserir(conjB, 20);
        conjunto_inserir(conjB, 30);
        
        // Test intersection
        CONJUNTO* intersec = conjunto_interseccao(conjA, conjB);
        if (intersec == NULL) {
            all_passed = false;
            sprintf(details + strlen(details), "Intersection operation failed for TAD %d. ", tad);
            continue;
        }
        
        // Note: Original sets are destroyed by intersection operation
        // This is potentially unexpected behavior that should be documented
        
        conjunto_apagar(&intersec);
    }
    
    // Test intersection with NULL conjunto
    if (conjunto_interseccao(NULL, NULL) != NULL) {
        all_passed = false;
        strcat(details, "Should return NULL when inputs are NULL. ");
    }
    
    if (all_passed) {
        strcat(details, "All intersection tests passed successfully. Note: Intersection destroys input sets.");
    }
    
    print_test_result("Intersection Tests", all_passed, details);
    return all_passed;
}
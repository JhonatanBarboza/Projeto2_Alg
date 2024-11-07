#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "../bibliotecas/lista.h"

// Utility function to print test results
void print_test_result(const char* test_name, bool passed) {
    printf("%s: %s\n", test_name, passed ? "PASSED ✓" : "FAILED ✗");
}

// Utility function to verify list contents
bool verify_list_contents(LISTA* lista, int expected[], int size) {
    for(int i = 0; i < size; i++) {
        if(lista_consultar(lista, i) != expected[i]) {
            printf("List content mismatch at index %d: expected %d, got %d\n", 
                   i, expected[i], lista_consultar(lista, i));
            return false;
        }
    }
    return true;
}

int main() {
    int test_count = 0;
    int failed_count = 0;
    bool test_passed;
    
    printf("=== Starting Lista ADT Tests ===\n\n");

    // Test 1: Creation and initialization
    printf("Test Group 1: Basic Operations\n");
    LISTA* lista = lista_criar();
    test_passed = (lista != NULL);
    print_test_result("Lista creation", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 2: Basic insertion
    test_passed = lista_inserir(lista, 5);
    print_test_result("First insertion", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 3: Ordered insertion
    test_passed = true;
    test_passed &= lista_inserir(lista, 3);  // Should go before 5
    test_passed &= lista_inserir(lista, 7);  // Should go after 5
    test_passed &= lista_inserir(lista, 1);  // Should go first
    int expected1[] = {1, 3, 5, 7};
    test_passed &= verify_list_contents(lista, expected1, 4);
    print_test_result("Ordered insertion", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 4: Duplicate insertion
    test_passed = !lista_inserir(lista, 5);  // Should fail
    print_test_result("Duplicate insertion prevention", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 5: Binary search
    printf("\nTest Group 2: Search Operations\n");
    test_passed = true;
    test_passed &= (lista_busca(lista, 5) == 5);    // Existing element
    test_passed &= (lista_busca(lista, 6) == ERRO); // Non-existing element
    print_test_result("Binary search", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 6: Removal
    printf("\nTest Group 3: Removal Operations\n");
    test_passed = true;
    test_passed &= (lista_remover(lista, 3) == 3);  // Remove middle element
    test_passed &= (lista_remover(lista, 1) == 1);  // Remove first element
    test_passed &= (lista_remover(lista, 7) == 7);  // Remove last element
    int expected2[] = {5};
    test_passed &= verify_list_contents(lista, expected2, 1);
    print_test_result("Element removal", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 7: Remove non-existent element
    test_passed = (lista_remover(lista, 99) == ERRO);
    print_test_result("Non-existent element removal", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 8: List copying
    printf("\nTest Group 4: Copy Operations\n");
    // Add some elements for copying
    lista_inserir(lista, 2);
    lista_inserir(lista, 8);
    LISTA* copy = lista_copiar(lista);
    test_passed = (copy != NULL);
    int expected3[] = {2, 5, 8};
    test_passed &= verify_list_contents(copy, expected3, 3);
    print_test_result("List copying", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 9: Edge cases
    printf("\nTest Group 5: Edge Cases\n");
    test_passed = true;
    LISTA* null_lista = NULL;
    test_passed &= (lista_busca(null_lista, 5) == ERRO);  // Search in NULL list
    test_passed &= (!lista_inserir(null_lista, 5));       // Insert in NULL list
    test_passed &= (lista_remover(null_lista, 5) == ERRO); // Remove from NULL list
    print_test_result("NULL list operations", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Clean up
    lista_apagar(&lista);
    lista_apagar(&copy);
    test_passed = (lista == NULL && copy == NULL);
    print_test_result("Memory deallocation", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Final report
    printf("\n=== Test Summary ===\n");
    printf("Total tests: %d\n", test_count);
    printf("Passed: %d\n", test_count - failed_count);
    printf("Failed: %d\n", failed_count);
    printf("Success rate: %.1f%%\n", ((float)(test_count - failed_count) / test_count) * 100);

    return failed_count > 0 ? 1 : 0;
}
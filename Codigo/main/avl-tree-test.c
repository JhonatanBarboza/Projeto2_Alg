#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../bibliotecas/AVL.h"

// Function to print test result
void print_test_result(bool result, const char* test_name) {
    printf("%s: %s\n", test_name, result ? "PASSED" : "FAILED");
}

int main() {
    // Test 1: Creating an AVL tree
    printf("--- AVL Tree Testing ---\n");
    AVL *avl = avl_criar();
    print_test_result(avl != NULL, "Tree Creation");

    // Test 2: Inserting elements
    bool insert_results[10];
    int insert_values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35};
    
    printf("\n--- Insertion Tests ---\n");
    for (int i = 0; i < 10; i++) {
        char test_name[50];
        snprintf(test_name, sizeof(test_name), "Inserting %d", insert_values[i]);
        insert_results[i] = avl_inserir(avl, insert_values[i]);
        print_test_result(insert_results[i], test_name);
    }

    // Test 3: Height retrieval
    int height = avl_get_altura(avl);
    printf("\n--- Height Test ---\n");
    printf("Tree Height: %d\n", height);
    print_test_result(height >= 3, "Height Retrieval");

    // Test 4: Removal tests
    printf("\n--- Removal Tests ---\n");
    int remove_values[] = {30, 50, 20};
    bool remove_results[3];

    for (int i = 0; i < 3; i++) {
        char test_name[50];
        snprintf(test_name, sizeof(test_name), "Removing %d", remove_values[i]);
        remove_results[i] = avl_remover(avl, remove_values[i]);
        print_test_result(remove_results[i], test_name);
    }

    // Test 5: Removal and height validation
    int new_height = avl_get_altura(avl);
    printf("\nTree Height after Removal: %d\n", new_height);
    print_test_result(new_height >= 2, "Height After Removal");

    // Test 6: Edge Case Tests
    printf("\n--- Edge Case Tests ---\n");
    // Now this should PASS (return false for duplicate)
    bool duplicate_insert = avl_inserir(avl, 10);
    bool remove_nonexistent = avl_remover(avl, 100);

    // Updated to expect false for these operations
    print_test_result(duplicate_insert == false, "Duplicate Insertion");
    print_test_result(remove_nonexistent == false, "Remove Non-existent Element");

    // Cleanup
    avl_apagar(&avl);
    print_test_result(avl == NULL, "Tree Deletion");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "../bibliotecas/AVL.h"

// Function prototypes for test functions
void test_create_and_destroy();
void test_insertion();
void test_insertion_balancing();
void test_duplicate_insertion();
void test_removal();
void test_removal_balancing();
void test_search();
void test_tree_height();
void test_tree_copy();
void test_edge_cases();

// Helper function to print test status
void print_test_result(const char* test_name, bool passed) {
    printf("%s: %s\n", test_name, passed ? "PASSED" : "FAILED");
}

int main() {
    printf("Starting AVL Tree Comprehensive Test Suite\n");
    printf("==========================================\n\n");

    // Run all test functions
    test_create_and_destroy();
    test_insertion();
    test_insertion_balancing();
    test_duplicate_insertion();
    test_removal();
    test_removal_balancing();
    test_search();
    test_tree_height();
    test_tree_copy();
    test_edge_cases();

    printf("\nAVL Tree Test Suite Completed.\n");
    return 0;
}

void test_create_and_destroy() {
    printf("Testing Tree Creation and Destruction\n");
    
    // Test tree creation
    AVL *tree = avl_criar();
    bool creation_test = (tree != NULL);
    print_test_result("Tree Creation", creation_test);
    
    // Test initial state
    bool size_test = (avl_get_altura(tree) == -1);
    print_test_result("Initial Tree Height", size_test);
    
    // Test destruction
    avl_apagar(&tree);
    bool destruction_test = (tree == NULL);
    print_test_result("Tree Destruction", destruction_test);
}

void test_insertion() {
    printf("\nTesting Insertion\n");
    
    AVL *tree = avl_criar();
    
    // Basic insertion
    bool insert_1 = avl_inserir(tree, 10);
    bool insert_2 = avl_inserir(tree, 20);
    bool insert_3 = avl_inserir(tree, 30);
    
    bool insertion_test = (insert_1 && insert_2 && insert_3);
    print_test_result("Basic Insertion", insertion_test);
    
    // Check size after insertion
    bool size_test = (avl_get_altura(tree) > 0);
    print_test_result("Tree Height After Insertion", size_test);
    
    avl_apagar(&tree);
}

void test_insertion_balancing() {
    printf("\nTesting Insertion Balancing\n");
    
    AVL *tree = avl_criar();
    
    // Insert elements to trigger rotations
    avl_inserir(tree, 30);
    avl_inserir(tree, 20);
    avl_inserir(tree, 40);
    avl_inserir(tree, 10);
    avl_inserir(tree, 25);
    avl_inserir(tree, 50);
    avl_inserir(tree, 5);
    
    // Height should remain balanced
    int height = avl_get_altura(tree);
    bool balancing_test = (height <= 3);  // Logarithmic height
    print_test_result("Insertion Balancing", balancing_test);
    
    avl_apagar(&tree);
}

void test_duplicate_insertion() {
    printf("\nTesting Duplicate Insertion\n");
    
    AVL *tree = avl_criar();
    
    avl_inserir(tree, 10);
    bool duplicate_test = !avl_inserir(tree, 10);  // Should return false
    print_test_result("Duplicate Insertion Rejection", duplicate_test);
    
    avl_apagar(&tree);
}

void test_removal() {
    printf("\nTesting Removal\n");
    
    AVL *tree = avl_criar();
    
    // Insert multiple elements
    avl_inserir(tree, 50);
    avl_inserir(tree, 30);
    avl_inserir(tree, 70);
    avl_inserir(tree, 20);
    avl_inserir(tree, 40);
    avl_inserir(tree, 60);
    avl_inserir(tree, 80);
    
    // Remove elements
    bool remove_1 = avl_remover(tree, 30);
    bool remove_2 = avl_remover(tree, 70);
    
    bool removal_test = (remove_1 && remove_2);
    print_test_result("Element Removal", removal_test);
    
    // Attempt to remove non-existent element
    bool remove_non_existent = !avl_remover(tree, 100);
    print_test_result("Non-Existent Element Removal", remove_non_existent);
    
    avl_apagar(&tree);
}

void test_removal_balancing() {
    printf("\nTesting Removal Balancing\n");
    
    AVL *tree = avl_criar();
    
    // Insert elements to create a complex tree
    int elements[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    for (int i = 0; i < 11; i++) {
        avl_inserir(tree, elements[i]);
    }
    
    // Remove multiple elements to test balancing
    avl_remover(tree, 30);
    avl_remover(tree, 70);
    
    // Height should remain balanced
    int height = avl_get_altura(tree);
    bool balancing_test = (height <= 4);  // Logarithmic height
    print_test_result("Removal Balancing", balancing_test);
    
    avl_apagar(&tree);
}

void test_search() {
    printf("\nTesting Search\n");
    
    AVL *tree = avl_criar();
    
    // Insert elements
    avl_inserir(tree, 50);
    avl_inserir(tree, 30);
    avl_inserir(tree, 70);
    
    // Successful searches
    bool search_1 = (avl_busca(tree, 50) == 50);
    bool search_2 = (avl_busca(tree, 30) == 30);
    
    // Failed search
    bool search_3 = (avl_busca(tree, 100) == ERRO);
    
    bool search_test = (search_1 && search_2 && search_3);
    print_test_result("Search Functionality", search_test);
    
    avl_apagar(&tree);
}

void test_tree_height() {
    printf("\nTesting Tree Height\n");
    
    AVL *tree = avl_criar();
    
    // Initial height should be -1
    bool initial_height_test = (avl_get_altura(tree) == -1);
    print_test_result("Initial Tree Height", initial_height_test);
    
    // Insert elements and check height progression
    avl_inserir(tree, 10);
    avl_inserir(tree, 20);
    avl_inserir(tree, 30);
    
    bool height_progression_test = (avl_get_altura(tree) > 0);
    print_test_result("Height Progression", height_progression_test);
    
    avl_apagar(&tree);
}

void test_tree_copy() {
    printf("\nTesting Tree Copying\n");
    
    AVL *original_tree = avl_criar();
    
    // Insert elements into original tree
    int elements[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        avl_inserir(original_tree, elements[i]);
    }
    
    // Create a deep copy
    AVL *copied_tree = avl_copiar(original_tree);
    
    // Verify copy
    bool copy_test = (copied_tree != NULL) && 
                     (avl_get_altura(original_tree) == avl_get_altura(copied_tree));
    print_test_result("Tree Deep Copy", copy_test);
    
    avl_apagar(&original_tree);
    avl_apagar(&copied_tree);
}

void test_edge_cases() {
    printf("\nTesting Edge Cases\n");
    
    // Test NULL tree operations
    AVL *null_tree = NULL;
    
    bool null_insert_test = !avl_inserir(null_tree, 10);
    bool null_remove_test = !avl_remover(null_tree, 10);
    bool null_height_test = (avl_get_altura(null_tree) == -9999);
    bool null_search_test = (avl_busca(null_tree, 10) == ERRO);
    
    bool edge_cases_test = (null_insert_test && 
                             null_remove_test && 
                             null_height_test && 
                             null_search_test);
    
    print_test_result("NULL Tree Operations", edge_cases_test);
    
    // Empty tree operations
    AVL *empty_tree = avl_criar();
    
    bool empty_remove_test = !avl_remover(empty_tree, 10);
    bool empty_search_test = (avl_busca(empty_tree, 10) == ERRO);
    
    bool empty_cases_test = (empty_remove_test && empty_search_test);
    print_test_result("Empty Tree Operations", empty_cases_test);
    
    avl_apagar(&empty_tree);
}
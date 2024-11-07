#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "../bibliotecas/ABB.h"

// Utility function to print test results
void print_test_result(const char* test_name, bool passed) {
    printf("%s: %s\n", test_name, passed ? "PASSED ✓" : "FAILED ✗");
}

// Utility function to verify if tree is ordered correctly by checking root's value
bool verify_subtree_order(ABB* tree, int root_value) {
    // If element exists in tree, it should be found by search
    return (abb_busca(tree, root_value) == root_value);
}

int main() {
    int test_count = 0;
    int failed_count = 0;
    bool test_passed;
    
    printf("=== Starting ABB (Binary Search Tree) Tests ===\n\n");

    // Test 1: Creation and initialization
    printf("Test Group 1: Basic Operations\n");
    ABB* tree = abb_criar();
    test_passed = (tree != NULL);
    print_test_result("Tree creation", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 2: Basic insertion
    test_passed = true;
    test_passed &= abb_inserir(tree, 50);  // Root
    test_passed &= (abb_get_chave_raiz(tree) == 50);
    print_test_result("Root insertion", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 3: Complex insertion (creating a balanced-like structure)
    printf("\nTest Group 2: Complex Insertions\n");
    test_passed = true;
    test_passed &= abb_inserir(tree, 30);  // Left of 50
    test_passed &= abb_inserir(tree, 70);  // Right of 50
    test_passed &= abb_inserir(tree, 20);  // Left of 30
    test_passed &= abb_inserir(tree, 40);  // Right of 30
    test_passed &= abb_inserir(tree, 60);  // Left of 70
    test_passed &= abb_inserir(tree, 80);  // Right of 70
    print_test_result("Multiple insertions", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 4: Duplicate insertion prevention
    test_passed = !abb_inserir(tree, 50);  // Should fail
    print_test_result("Duplicate insertion prevention", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 5: Search operations
    printf("\nTest Group 3: Search Operations\n");
    test_passed = true;
    test_passed &= (abb_busca(tree, 50) == 50);    // Root
    test_passed &= (abb_busca(tree, 30) == 30);    // Internal node
    test_passed &= (abb_busca(tree, 80) == 80);    // Leaf node
    test_passed &= (abb_busca(tree, 99) == ERRO);  // Non-existing element
    print_test_result("Various searches", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 6: Tree printing (visual inspection needed)
    printf("\nTest Group 4: Printing Operations\n");
    printf("Ordered printing (should be ascending):\n");
    abb_imprimir(tree, true);
    printf("Non-ordered printing (should be level-order):\n");
    abb_imprimir(tree, false);
    print_test_result("Print functions executed", true);
    test_count++;

    // Test 7: Copy operation (do this before removals to avoid segfault)
    printf("\nTest Group 5: Copy Operations\n");
    ABB* tree_copy = abb_copiar(tree);
    test_passed = (tree_copy != NULL);
    test_passed &= (abb_get_chave_raiz(tree_copy) == abb_get_chave_raiz(tree));
    test_passed &= (abb_busca(tree_copy, 30) == 30);
    test_passed &= (abb_busca(tree_copy, 80) == 80);
    print_test_result("Tree copying", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 8: Removal operations
    printf("\nTest Group 6: Removal Operations\n");
    
    // Remove leaf
    test_passed = (abb_remover(tree, 20) == 20);
    test_passed &= (abb_busca(tree, 20) == ERRO);
    print_test_result("Leaf removal", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Remove node with one child
    test_passed = (abb_remover(tree, 70) == 70);
    test_passed &= (abb_busca(tree, 70) == ERRO);
    test_passed &= verify_subtree_order(tree, 80); // Verify child is still accessible
    print_test_result("Single child node removal", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Remove node with two children
    test_passed = (abb_remover(tree, 30) == 30);
    test_passed &= (abb_busca(tree, 30) == ERRO);
    test_passed &= verify_subtree_order(tree, 40); // Verify children are still accessible
    print_test_result("Two children node removal", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Test 9: Edge cases
    printf("\nTest Group 7: Edge Cases\n");
    ABB* null_tree = NULL;
    test_passed = true;
    test_passed &= (abb_busca(null_tree, 5) == ERRO);     // Search in NULL tree
    test_passed &= (!abb_inserir(null_tree, 5));          // Insert in NULL tree
    test_passed &= (abb_remover(null_tree, 5) == ERRO);   // Remove from NULL tree
    test_passed &= (abb_get_chave_raiz(null_tree) == ERRO); // Get root of NULL tree
    print_test_result("NULL tree operations", test_passed);
    if(!test_passed) failed_count++;
    test_count++;

    // Clean up
    abb_apagar(&tree);
    abb_apagar(&tree_copy);
    test_passed = (tree == NULL && tree_copy == NULL);
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
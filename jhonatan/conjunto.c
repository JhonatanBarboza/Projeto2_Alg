#include "conjunto.h"
#include <stdio.h>

bool Conjunto_Lista_Pertence (LISTA *lista, int elemento);
LISTA* Conjunto_Lista_Uniao (LISTA *lista_A, int tamanho_A, LISTA *lista_B, int tamanho_B); 
LISTA* Conjunto_Lista_Interseccao (LISTA* lista_A, int tamanho_A, LISTA* lista_B);

bool Conjunto_Arvore_Pertence (ARVORE* arvore, int elemento);
ARVORE* Conjunto_Arvore_Uniao (ARVORE* arvore_A, int tamanho_A, ARVORE* arvore_B, int tamanho_B); 
ARVORE* Conjunto_Arvore_Interseccao (ARVORE* arvore_A, int tamanho_A, ARVORE* arvore_B);


bool Conjunto_Lista_Pertence(LISTA *lista, int elemento) {
    return busca_binaria(lista, elemento);
}

// Funções de união 
LISTA* Conjunto_Lista_Uniao(LISTA *lista_A, int tamanho_A, LISTA *lista_B, int tamanho_B) {
    LISTA *uniao = Lista_Criar(tamanho_A + tamanho_B);
    int i = 0, j = 0;

    while (i < tamanho_A && j < tamanho_B) {
        if (Lista_Consultar (lista_A, i) < Lista_Consultar (lista_B, j)) {
            Lista_Inserir(uniao, Lista_Consultar (lista_A, i++));
        } else if (Lista_Consultar (lista_A, i) > Lista_Consultar (lista_B, j)) {
            Lista_Inserir(uniao, Lista_Consultar (lista_B, j++));
        } else {
            Lista_Inserir(uniao, Lista_Consultar (lista_A, i));
            i++;
            j++;
        }
    }
    while (i < tamanho_A) Lista_Inserir(uniao, Lista_Consultar (lista_A, i++));
    while (j < tamanho_B) Lista_Inserir(uniao, Lista_Consultar (lista_B, j++));

    return uniao;
}

// Funções de interseção
LISTA* Conjunto_Lista_Interseccao(LISTA* lista_A, int tamanho_A, LISTA* lista_B) {
    LISTA *interseccao = Lista_Criar(tamanho_A);

    for (int i = 0; i < tamanho_A; i++) {
        if (Conjunto_Lista_Pertence(lista_B, Lista_Consultar (lista_A, i))) {
            Lista_Inserir(interseccao, Lista_Consultar (lista_A, i));
        }
    }
    return interseccao;
}




bool Conjunto_Arvore_Pertence(ARVORE* arvore, int elemento) {
    // Implementação temporária
    return false;
}

ARVORE* Conjunto_Arvore_Uniao(ARVORE* arvore_A, int tamanho_A, ARVORE* arvore_B, int tamanho_B) {
    // Implementação temporária
    return NULL;
}

ARVORE* Conjunto_Arvore_Interseccao(ARVORE* arvore_A, int tamanho_A, ARVORE* arvore_B) {
    // Implementação temporária
    return NULL;
}





//***********************************************************************************************************




// Verifica se um elemento pertence ao conjunto A, implementado com listas
void Conjunto_Pertence_0(LISTA* conjunto_A, int tamanho_A, int elemento) {

    // Verifica se o elemento está na lista e imprime o resultado
    if (Conjunto_Lista_Pertence(conjunto_A, elemento)) {
        printf("Pertence\n");
    } else {
        printf("Não pertence\n");
    }

    Lista_Apagar(conjunto_A); // Libera a memória da lista
}

// Realiza a união entre dois conjuntos A e B, implementados com listas
void Conjunto_Uniao_0(LISTA* conjunto_A, int tamanho_A, LISTA* conjunto_B, int tamanho_B) {

    // Cria e imprime a união das listas
    LISTA* uniao = Conjunto_Lista_Uniao(conjunto_A, tamanho_A, conjunto_B, tamanho_B);
    Lista_Imprimir(uniao);

    // Libera a memória das listas
    Lista_Apagar(conjunto_A);
    Lista_Apagar(conjunto_B);
    Lista_Apagar(uniao);
}

// Realiza a interseção entre dois conjuntos A e B, implementados com listas
void Conjunto_Intersecao_0(LISTA* conjunto_A, int tamanho_A, LISTA* conjunto_B, int tamanho_B) {

    // Cria e imprime a interseção das listas
    LISTA* intersecao = Conjunto_Lista_Interseccao(conjunto_A, tamanho_A, conjunto_B);
    Lista_Imprimir(intersecao);

    // Libera a memória das listas
    Lista_Apagar(conjunto_A);
    Lista_Apagar(conjunto_B);
    Lista_Apagar(intersecao);
}

// Verifica se um elemento pertence ao conjunto A, implementado com árvores
void Conjunto_Pertence_1(ARVORE* conjunto_A, int tamanho_A, int elemento) {

    // Verifica se o elemento está na árvore e imprime o resultado
    if (Conjunto_Arvore_Pertence(conjunto_A, elemento)) {
        printf("Pertence\n");
    } else {
        printf("Não pertence\n");
    }

    Arvore_Apagar(conjunto_A); // Libera a memória da árvore
}

// Realiza a união entre dois conjuntos A e B, implementados com árvores
void Conjunto_Uniao_1(ARVORE* conjunto_A, int tamanho_A, ARVORE* conjunto_B, int tamanho_B) {

    // Cria e imprime a união das árvores
    ARVORE* uniao = Conjunto_Arvore_Uniao(conjunto_A, tamanho_A, conjunto_B, tamanho_B);
    Arvore_Imprimir(uniao);

    // Libera a memória das árvores
    Arvore_Apagar(conjunto_A);
    Arvore_Apagar(conjunto_B);
    Arvore_Apagar(uniao);
}

// Realiza a interseção entre dois conjuntos A e B, implementados com árvores
void Conjunto_Intersecao_1(ARVORE* conjunto_A, int tamanho_A, ARVORE* conjunto_B, int tamanho_B) {

    // Cria e imprime a interseção das árvores
    ARVORE* intersecao = Conjunto_Arvore_Interseccao(conjunto_A, tamanho_A, conjunto_B);
    Arvore_Imprimir(intersecao);

    // Libera a memória das árvores
    Arvore_Apagar(conjunto_A);
    Arvore_Apagar(conjunto_B);
    Arvore_Apagar(intersecao);
}

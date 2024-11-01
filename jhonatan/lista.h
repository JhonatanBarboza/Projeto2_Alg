#ifndef LISTA_H
    #define LISTA_H
    #include <stdbool.h>

    typedef struct Lista_ LISTA;

    void Lista_Apagar (LISTA *lista); 
    void Lista_Imprimir (LISTA *lista);
    LISTA* Lista_Criar (int tamanho_dados);
    int Lista_Consultar (LISTA *lista, int indice);
    bool busca_binaria(LISTA *lista, int elemento); 
    void Lista_Remover (LISTA *lista, int elemento); 
    void Lista_Inserir (LISTA* lista, int elemento);

#endif 

#ifndef LISTA_H
    #define LISTA_H
    #include <stdbool.h>

    #define TAM_MAX 100000
    #define ERRO 1000010

    typedef struct lista_ LISTA;

    void Lista_Apagar (LISTA **lista); 
    int Lista_Remover (LISTA *lista);
    void Lista_Imprimir (LISTA *lista);
    LISTA* Lista_Criar (void);
    int Lista_Consultar (LISTA *lista, int indice);
    bool busca_binaria(LISTA *lista, int elemento);  
    void Lista_Inserir (LISTA* lista, int elemento);

#endif 

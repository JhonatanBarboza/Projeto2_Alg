#ifndef CONJUNTO_H
    #define CONJUNTO_H

    #include "lista.h"
    #include "arvore.h"

    void Conjunto_Pertence_0(LISTA* conjunto_A, int tamanho_A, int elemento);
    void Conjunto_Uniao_0(LISTA* conjunto_A, int tamanho_A, LISTA* conjunto_B, int tamanho_B);
    void Conjunto_Intersecao_0(LISTA* conjunto_A, int tamanho_A, LISTA* conjunto_B, int tamanho_B);
    void Conjunto_Pertence_1(ARVORE* conjunto_A, int tamanho_A, int elemento);
    void Conjunto_Uniao_1(ARVORE* conjunto_A, int tamanho_A, ARVORE* conjunto_B, int tamanho_B);
    void Conjunto_Intersecao_1(ARVORE* conjunto_A, int tamanho_A, ARVORE* conjunto_B, int tamanho_B);

#endif 

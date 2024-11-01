
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Arvore_{
    int a;
}ARVORE;

void Arvore_Apagar (ARVORE* arvore){
    
}
void Arvore_Remover (ARVORE* arvore){

} 
void Arvore_Imprimir (ARVORE* arvore){

}
ARVORE* Arvore_Criar (int tamanho_dados){
    ARVORE* a = (ARVORE*)malloc(sizeof(ARVORE));
    a->a = tamanho_dados;
    return a;
}
void Arvore_Inserir (ARVORE* arvore, int elemento){

}



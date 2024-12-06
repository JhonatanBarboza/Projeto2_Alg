## Descrição do projeto:  
Conjuntos, conceito fundamental da Teoria dos Conjuntos, representam coleções de objetos chamados elementos, cuja relação de pertinência define se pertencem ou não ao conjunto. Com ampla aplicação em sistemas computacionais, os conjuntos aparecem em diversas linguagens de programação como estruturas de dados e são utilizados em problemas matemáticos, de otimização e estatística.

## Objetivo:  
O objetivo do projeto foi implementar três TADs, visando desenvolver tanto as operações básicas de cada TAD quanto as operações específicas do conjunto, como pertinência, união e interseção, otimizando ao máximo a complexidade computacional. Para isso, escolhemos implementar os TADs utilizando uma lista com busca binária, uma árvore binária de busca AVL e um TAD Conjunto, responsável por gerenciar as operações durante a execução. 

## Justificativa:  
A escolha de implementar o TAD com uma lista utilizando busca binária deve-se ao fato de que a operação de busca pode ser realizada em $$O(\log n)$$. Apesar de as operações de inserção e remoção apresentarem complexidade $$O(n)$$, no geral, o desempenho é satisfatório em cenários onde a busca é predominante. Já a árvore binária de busca AVL foi escolhida por sua eficiência consistente, com complexidade $$O(\log n)$$ para as operações de busca, inserção e remoção, garantindo bom desempenho mesmo no pior caso. 

## Principais operações:
### Main:

A função main gerencia as operações e o fluxo do programa. Inicialmente, ela solicita ao usuário que escolha a estrutura de dados a ser utilizada (0 para lista e 1 para ABB AVL). Com base nessa escolha, dois conjuntos (conjA e conjB) são criados utilizando a estrutura selecionada.

Em seguida, o programa lê o tamanho dos conjuntos A e B. Caso ambos os tamanhos sejam zero, uma mensagem informando que os conjuntos estão vazios é exibida, e o programa é encerrado. Caso contrário, os elementos de cada conjunto são lidos e inseridos nas respectivas estruturas de dados por meio da função conjunto_inserir.

Posteriormente, o programa solicita ao usuário que selecione a operação a ser realizada entre os conjuntos. As operações disponíveis são: verificar a pertinência de um elemento a um conjunto (PERTENCE), realizar a união dos conjuntos (UNIAO) ou calcular a interseção dos conjuntos (INTERSEC). Com base na operação escolhida, a função correspondente é executada para obter e exibir o resultado.

Ao final do programa, os conjuntos criados são apagados da memória utilizando a função conjunto_apagar, e o programa é encerrado com sucesso.


### TAD Conjunto:
### TAD Lista:
### TAD Arvora Binaria de Busca AVL:

## Complexidade das operação:

### Main:  
Na função `main`, as operações realizadas têm complexidade diretamente relacionada ao número de elementos nos conjuntos e ao tipo de estrutura escolhida. Segue a análise:  

1. **Leitura do TAD**:  
   - A escolha da estrutura de dados é uma simples leitura de entrada e tem complexidade $$O(1)$$.  

2. **Leitura dos Tamanhos dos Conjuntos (`tamA` e `tamB`)**:  
   - São realizadas duas operações de leitura, cada uma com complexidade $$O(1)$$.  

3. **Inserção de Elementos nos Conjuntos (`conjunto_inserir`)**:  
   - A `main` executa dois laços de leitura e inserção:  
     - Para `tamA` elementos no conjunto `A`, a complexidade é $$O(tamA \cdot C_{\text{inserir}})$$.  
     - Para `tamB` elementos no conjunto `B`, a complexidade é $$O(tamB \cdot C_{\text{inserir}})$$.  
   - A complexidade final depende da implementação da função `conjunto_inserir`.  

4. **Escolha da Operação e Execução**:  
   - A leitura da operação tem complexidade $$O(1)$$.  
   - A execução da operação (pertence, união ou interseção) depende do código interno de cada função chamada, sendo detalhada posteriormente.  

5. **Liberação dos Conjuntos (`conjunto_apagar`)**:  
   - São chamadas duas vezes para liberar os conjuntos `A` e `B`. A complexidade depende do número de elementos nos conjuntos e da implementação da função `conjunto_apagar`.  

**Resumo Geral da Main**:  
A complexidade da função `main` é dominada pelo custo da leitura e inserção dos elementos, além das operações executadas sobre os conjuntos. Estes detalhes são dependentes das implementações específicas das funções chamadas.



### TAD Conjunto:
### TAD Lista:
### TAD Arvora Binaria de Buca AVL:


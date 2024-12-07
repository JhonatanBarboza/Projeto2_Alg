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

### TAD Conjunto

O código importa os arquivos `list.h`, `abb.h` e `conjunto.h` e define a estrutura `conjunto`. Essa estrutura contém o campo `TAD`, que indica o tipo de estrutura de dados utilizada (lista ou árvore binária), o tamanho do conjunto e dois ponteiros: um para a lista (`conjuntoLista`) e outro para a árvore binária (`conjuntoABB`). Apenas um desses ponteiros será utilizado, dependendo da estrutura escolhida.

A ideia principal das funções é gerenciar as chamadas para as funções específicas da lista ou da árvore binária, garantindo que as operações sejam executadas de acordo com a estrutura de dados escolhida.

#### Descrição das Funções

1. **`conjunto_criar`**: Aloca espaço na memória para criar um conjunto, inicializando-o conforme o tipo de estrutura especificado (`lista` ou `árvore binária`).

2. **`conjunto_apagar`**: Libera a memória do conjunto, utilizando as funções específicas da estrutura escolhida.

3. **`conjunto_inserir`**: Insere um elemento no conjunto e incrementa seu tamanho.

4. **`conjunto_remover`**: Remove um elemento específico do conjunto, decrementa seu tamanho e retorna o elemento removido.

5. **`conjunto_imprimir`**: Imprime os elementos do conjunto utilizando a função correspondente à estrutura de dados.

6. **`conjunto_pertence`**: Verifica se um elemento pertence ao conjunto. Retorna `true` se o elemento for encontrado e `false` caso contrário.

7. **`conjunto_uniao`**: Realiza a união de dois conjuntos. 
   - Verifica se ambos não estão vazios.
   - Cria um novo conjunto e insere os elementos do conjunto A nele.
   - Para listas, insere diretamente os elementos de B, pois a função `lista_inserir` evita duplicatas.
   - Para árvores, é necessário ajustar a lógica para lidar com a remoção e inserção de elementos (essa parte está pendente no código).

8. **`conjunto_interseccao`**: Calcula a interseção de dois conjuntos.
   - Verifica se ambos não estão vazios.
   - Cria um novo conjunto e insere elementos que pertencem simultaneamente aos dois conjuntos originais.
   - Para árvores, segue a mesma lógica de manipulação de cópias utilizada na união.

9. **`conjunto_copiar`**: Cria uma cópia de um conjunto, alocando um novo espaço na memória e copiando os elementos da estrutura original.


### TAD Lista:
### TAD Arvora Binaria de Busca AVL:

## Complexidade das operação:
O objetivo é analisar separadamente a complexidade de cada função implementada, considerando apenas o código presente em cada uma delas. Para funções que realizam chamadas a TADs externos, a análise se limitará à lógica interna da função, desconsiderando a complexidade das funções chamadas. Ao final, será feito um levantamento geral para determinar a complexidade predominante de cada operação.

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

A análise a seguir considera apenas a lógica implementada no arquivo `conjunto.c`, sem detalhar as funções chamadas (como `lista_inserir`, `abb_inserir`, entre outras). A complexidade destas funções será especificada posteriormente.


1. **`conjunto_criar`**  
   - **Descrição**: Aloca memória para o conjunto e inicializa o ponteiro correspondente à estrutura escolhida (lista ou árvore).  
   - **Operações principais**:  
     - Alocação de memória: $$O(1)$$.  
     - Inicialização de ponteiros: $$O(1)$$.  
   - **Complexidade Total**: $$O(1)$$.  

2. **`conjunto_apagar`**  
   - **Descrição**: Libera a memória ocupada pelo conjunto.  
   - **Operações principais**:  
     - Liberação do conjunto com chamada à função específica (detalhada posteriormente).  
     - Liberação da memória do próprio `conjunto`.  
   - **Complexidade Total**: $$O(1)$$, desconsiderando a complexidade das funções chamadas.  

3. **`conjunto_inserir`**  
   - **Descrição**: Insere um elemento no conjunto e incrementa o tamanho.  
   - **Operações principais**:  
     - Verifica o tipo de estrutura e chama a função correspondente para inserção.  
     - Incrementa o tamanho do conjunto.  
   - **Complexidade Total**: $$O(1)$$, desconsiderando a complexidade da função chamada.  

4. **`conjunto_remover`**  
   - **Descrição**: Remove um elemento do conjunto e decrementa o tamanho.  
   - **Operações principais**:  
     - Verifica o tipo de estrutura e chama a função correspondente para remoção.  
     - Atualiza o tamanho do conjunto.  
   - **Complexidade Total**: $$O(1)$$, desconsiderando a complexidade da função chamada.  

5. **`conjunto_imprimir`**  
   - **Descrição**: Imprime os elementos do conjunto.  
   - **Operações principais**:  
     - Verifica o tipo de estrutura e chama a função de impressão correspondente.  
   - **Complexidade Total**: $$O(1)$$, desconsiderando a complexidade da função chamada.  

6. **`conjunto_pertence`**  
   - **Descrição**: Verifica se um elemento pertence ao conjunto.  
   - **Operações principais**:  
     - Chama a função de busca correspondente à estrutura escolhida.  
     - Retorna o resultado da busca.  
   - **Complexidade Total**: $$O(1)$$, desconsiderando a complexidade da função chamada.  

7. **`conjunto_uniao`**  
   - **Descrição**: Realiza a união de dois conjuntos.  
   - **Operações principais**:  
     - Copia o conjunto A.  
     - Chama as funções de inserção para adicionar os elementos do conjunto B.  
   - **Complexidade Total**: $$O(1)$$, desconsiderando a complexidade das funções chamadas.  

8. **`conjunto_interseccao`**  
   - **Descrição**: Calcula a interseção de dois conjuntos.  
   - **Operações principais**:  
     - Cria um novo conjunto.  
     - Chama a função de busca para verificar a presença de elementos nos dois conjuntos.  
     - Insere os elementos encontrados na interseção.  
   - **Complexidade Total**: $$O(1)$$, desconsiderando a complexidade das funções chamadas.  

9. **`conjunto_copiar`**  
   - **Descrição**: Cria uma cópia de um conjunto.  
   - **Operações principais**:  
     - Cria um novo conjunto.  
     - Chama a função de cópia correspondente à estrutura utilizada.  
   - **Complexidade Total**: $$O(1)$$, desconsiderando a complexidade das funções chamadas.  

**Resumo Geral:**  
Todas as funções do arquivo `conjunto.c` apresentam complexidade constante $$O(1)$$ com relação à lógica interna do código. A complexidade completa dependerá diretamente das funções chamadas (`lista_inserir`, `abb_remover`, etc.), cujas complexidades serão analisadas separadamente.


### TAD Lista:
### TAD Arvora Binaria de Buca AVL:


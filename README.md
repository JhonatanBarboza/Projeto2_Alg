## Descrição do projeto:  
Conjuntos, conceito fundamental da Teoria dos Conjuntos, representam coleções de objetos chamados elementos, cuja relação de pertinência define se pertencem ou não ao conjunto. Com ampla aplicação em sistemas computacionais, os conjuntos aparecem em diversas linguagens de programação como estruturas de dados e são utilizados em problemas matemáticos, de otimização e estatística.

## Objetivo:  
O objetivo do projeto foi implementar três TADs, visando desenvolver tanto as operações básicas de cada TAD quanto as operações específicas do conjunto, como pertinência, união e interseção, otimizando ao máximo a complexidade computacional. Para isso, escolhemos implementar os TADs utilizando uma lista com busca binária, uma árvore binária de busca AVL e um TAD Conjunto, responsável por gerenciar as operações durante a execução. 

## Justificativa:  
A escolha de implementar o TAD com uma lista utilizando busca binária deve-se ao fato de que a operação de busca pode ser realizada em $$O(\log n)$$. Apesar de as operações de inserção e remoção apresentarem complexidade $$O(n)$$, no geral, o desempenho é satisfatório em cenários onde a busca é predominante. Já a árvore binária de busca AVL foi escolhida por sua eficiência consistente, com complexidade $$O(\log n)$$ para as operações de busca, inserção e remoção, garantindo bom desempenho mesmo no pior caso. 


## Complexidade das operação:

O objetivo é analisar separadamente a complexidade de cada função implementada, considerando apenas o código presente em cada uma delas. Para funções que realizam chamadas a TADs externos, a análise se limitará à lógica interna da função, desconsiderando a complexidade das funções chamadas. Ao final, será feito um levantamento geral para determinar a complexidade predominante de cada operação.


### Função main 

A função `main` gerencia o fluxo do programa. Após solicitar ao usuário a escolha da estrutura de dados (`0` para Lista, `1` para ABB AVL), cria os conjuntos `conjA` e `conjB`. Em seguida, lê os tamanhos dos conjuntos e insere os elementos utilizando a função `conjunto_inserir`.  

O usuário escolhe a operação a ser realizada entre os conjuntos: **PERTENCE**, **UNIÃO** ou **INTERSECÇÃO**, e a função correspondente é chamada. Ao final, os conjuntos são liberados da memória com `conjunto_apagar`.

#### **Análise de Complexidade**  

1. **Escolha da Estrutura de Dados**:  
   $$O(1)$$  

2. **Leitura dos Tamanhos**:  
   $$O(1)$$ por leitura, total $$O(2)$$.  

3. **Inserção de Elementos (`conjunto_inserir`)**:  
   - Para `tamA`: $$O(tamA \cdot C_{\text{inserir}})$$  
   - Para `tamB`: $$O(tamB \cdot C_{\text{inserir}})$$  

4. **Escolha e Execução da Operação**:  
   - Leitura: $$O(1)$$  
   - Execução: Depende da operação e estrutura de dados.  

5. **Liberação de Memória (`conjunto_apagar`)**:  
   $$O(tamA + tamB)$$ (dependente do tamanho dos conjuntos).  

**Resumo**:  
A complexidade da função `main` é dominada pelo custo das inserções O(tamA C inserir + tamB C inserir) e pela operação escolhida, variando conforme a estrutura utilizada.

### TAD Conjunto:

O código importa os arquivos `list.h`, `avl.h` e `conjunto.h` e define a estrutura `conjunto`. Essa estrutura contém o campo `TAD`, que indica o tipo de estrutura de dados utilizada (lista ou árvore binária), o tamanho do conjunto e dois ponteiros: um para a lista (`conjuntoLista`) e outro para a árvore binária (`conjuntoAVL`). Apenas um desses ponteiros será utilizado, dependendo da estrutura escolhida.

A ideia principal das funções é gerenciar as chamadas para as funções específicas da lista ou da árvore binária, garantindo que as operações sejam executadas de acordo com a estrutura de dados escolhida.

#### **Análise de Complexidade**  

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
Todas as funções do arquivo `conjunto.c` apresentam complexidade constante $$O(1)$$ com relação à lógica interna do código. A complexidade completa dependerá diretamente das funções chamadas (`lista_inserir`, `avl_remover`, etc.), cujas complexidades serão analisadas separadamente.

### TAD Lista Sequencial  

O objetivo do arquivo `lista.c` é implementar uma lista sequencial ordenada com suporte a busca binária. Ele contém as principais funções relacionadas à manipulação da lista, como inserção, remoção, busca binária e outras operações úteis. Abaixo segue uma breve descrição de cada função: 

#### **Análise de Complexidade**  

**1. `lista_criar` e `lista_apagar`**
- **Descrição:** Operações simples de alocação e desalocação de memória.
- **Complexidade:** $$O(1)$$ para ambas, já que alocar/desalocar uma estrutura de tamanho fixo é constante.


**2. `lista_inserir`**
- **Descrição:**
  1. **Encontrar a posição de inserção:** Laço `while` percorre a lista até encontrar o primeiro elemento maior que o elemento a ser inserido.
      - Pior caso: percorre toda a lista. $$O(n)$$.
  2. **Verificar duplicatas:** Chama `lista_busca`, que usa busca binária.
      - Complexidade da busca binária: $$O(\log n)$$.
  3. **Inserir o elemento:** Move os elementos da posição encontrada até o final da lista uma posição para a direita.
      - Pior caso: desloca todos os elementos. $$O(n)$$.

- **Complexidade Total:** 
  $$O(n) + O(\log n) + O(n) = O(n)$$  
  O termo dominante é $$O(n)$$.


**3. `lista_remover`**
- **Descrição:**
  1. **Buscar o elemento a ser removido:** Usa busca binária.
      - $$O(\log n)$$.
  2. **Remover o elemento:** Move os elementos da posição do elemento removido até o final da lista uma posição para a esquerda.
      - Pior caso: desloca $$n-1$$ elementos. $$O(n)$$.

- **Complexidade Total:**
  $$O(\log n) + O(n) = O(n)$$.


**4. `lista_imprimir`**
- **Descrição:** Percorre a lista e imprime cada elemento.
- **Complexidade:** $$O(n)$$, onde $$ n $$ é o número de elementos na lista.


**5. `lista_busca`**
- **Descrição:** Verifica se uma chave está presente na lista usando busca binária.
- **Complexidade:** $$O(\log n)$$.


**6. `lista_copiar`**
- **Descrição:**
  1. **Criar uma nova lista:** $$O(1)$$.
  2. **Inserir todos os elementos da lista original na nova lista:** Laço que percorre todos os $$ n $$ elementos, chamando `lista_inserir` para cada um.
      - Cada chamada de `lista_inserir` tem complexidade $$O(n)$$.
      - Total para $$ n $$ elementos: $$O(n^2)$$.

- **Complexidade Total:** $$O(n^2)$$.


**7. `lista_consultar`**
- **Descrição:** Acessa diretamente o índice no vetor.
- **Complexidade:** $$O(1)$$.


**8. `buscaBinariaLista`**
- **Descrição:** Implementação recursiva da busca binária.
- **Complexidade:** A cada chamada, o tamanho da lista é reduzido pela metade.
  - Total de chamadas: $$O(\log n)$$.

Embora algumas funções como `lista_inserir` e `lista_remover` sejam $$ O(n) $$, é importante considerar que, no contexto de $$n$$ muito grande, o comportamento constante de funções mais rápidas (como $$O(\log n)$$) pode ser um fator relevante em comparação à soma ou multiplicação de constantes associadas a essas operações.

### TAD Árvore Binária de Busca AVL  

O objetivo do arquivo `AVL.c` é implementar uma **Árvore Binária de Busca AVL** (uma árvore de busca balanceada). A característica principal dessa estrutura é o balanceamento automático, que garante que a diferença entre as alturas das subárvores esquerda e direita de qualquer nó nunca seja maior que 1. Caso essa condição seja violada após uma inserção ou remoção, a árvore realiza rotações para corrigir o balanceamento.

A implementação inclui definições auxiliares para criar, remover, balancear e acessar os nós, além das funções principais do TAD AVL.

#### **Análise de Complexidade**  

**1. `avl_criar` e `avl_apagar`**  
- **Descrição:**  
  - `avl_criar`: Aloca memória para uma estrutura AVL e inicializa seus atributos.  
  - `avl_apagar`: Desaloca recursivamente todos os nós da árvore e, por fim, desaloca a estrutura AVL.  
- **Complexidade:**  
  - `avl_criar`: $$O(1)$$, pois envolve apenas operações de alocação e inicialização.  
  - `avl_apagar`: $$O(n)$$, onde $$n$$ é o número de nós da árvore. A recursão percorre todos os nós para desalocá-los.


**2. `avl_inserir` e `avl_inserir_no`**  
- **Descrição:**  
  1. **Inserção de um nó:** A função `avl_inserir_no` navega recursivamente pela árvore para encontrar a posição adequada para inserir o nó, similar à inserção em uma árvore binária de busca.  
  2. **Balanceamento:** Após a inserção, a função verifica o fator de balanceamento ($$ FB $$) e aplica rotações, se necessário.  
  - **Rotação:** A rotação esquerda, direita, ou dupla requer acesso a um número constante de nós ($$O(1)$$).  

- **Complexidade:**  
  - Inserir um nó: No pior caso, a altura da árvore é percorrida, o que equivale a $$O(\log n)$$ para árvores balanceadas.  
  - Balanceamento: Como as rotações têm complexidade $$O(1)$$, o balanceamento não altera a complexidade total.  
  - **Total:** $$O(\log n) + O(1) = O(\log n)$$.


**3. `no_get_altura`**  
- **Descrição:**  
  Calcula a altura de uma árvore recursivamente ao acessar as subárvores esquerda e direita.  
- **Complexidade:**  
  - Cada chamada recursiva percorre todos os nós da subárvore para calcular sua altura.  
  - No pior caso, se chamada repetidamente para todas as operações, torna-se $$ O(n) $$ devido à redundância no cálculo.  


**4. `avl_remover` e `avl_remover_no`**  
- **Descrição:**  
  1. **Busca pelo nó a ser removido:** Navega recursivamente até localizar o nó.  

  2. **Remoção:** Existem três casos:  
     - O nó é uma folha: remoção direta.  
     - O nó tem um filho: substituição pelo filho.  
     - O nó tem dois filhos: substituição pelo sucessor ou antecessor.  
  3. **Balanceamento:** Após a remoção, a função recalcula o fator de balanceamento e aplica rotações, se necessário.  

- **Complexidade:**  
  - Buscar o nó: $$O(\log n)$$.  
  - Ajustar a árvore: As rotações têm custo $$O(1)$$.  
  - **Total:** $$O(\log n) + O(1) = O(\log n)$$.


**5. `avl_busca` e `busca_binaria_avl`**  
- **Descrição:**  
  Navega recursivamente pela árvore, reduzindo pela metade o espaço de busca em cada passo (busca binária).  
- **Complexidade:**  
  - **Total:** $$O(\log n)$$, pois a altura de uma árvore AVL é $$O(\log n)$$.


**6. `no_rodar_direita` e `no_rodar_esquerda`**  
- **Descrição:**  
  Ambas executam uma rotação entre um nó e seus filhos, ajustando os ponteiros e recalculando o fator de balanceamento.  
- **Complexidade:**  
  - **Total:** $$O(1)$$, pois afetam um número constante de nós.  


**7. `no_copiar_recursivo` e `avl_copiar`**  
- **Descrição:**  
  Percorrem todos os nós da árvore original e criam uma nova cópia, incluindo todos os seus descendentes.  
- **Complexidade:**  
  - **Total:** $$O(n)$$, onde $$n$$ é o número de nós na árvore.  


**8. `avl_imprimir` e `avl_imprimir_arv`**  
- **Descrição:**  
  Percorrem a árvore em ordem (in-ordem) para imprimir seus elementos.  
- **Complexidade:**  
  - **Total:** $$O(n)$$, pois todos os nós são visitados uma vez.  


A implementação assegura que as operações de busca, inserção e remoção sejam executadas de forma eficiente, com complexidade garantida de $$O(\log n)$$ no pior caso, graças ao balanceamento automático proporcionado pelas rotações AVL. 

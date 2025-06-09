

# Gerenciador de Contatos com Árvore Binária de Busca em C

Este projeto é uma implementação de um sistema de gerenciamento de contatos utilizando a linguagem C. A principal característica deste sistema é o uso de uma **Árvore Binária de Busca (ABB)** para armazenar e organizar os contatos, o que garante operações de inserção, remoção e busca com boa performance, além de manter a lista de contatos sempre em ordem alfabética.

## ✨ Funcionalidades

* **Adicionar Contato**: Insere um novo contato (nome e celular) na agenda. A inserção é feita de forma a manter a ordem alfabética dos nomes.
* **Buscar Contato**: Procura por um contato específico através do nome.
* **Remover Contato**: Exclui um contato da agenda pelo nome.
* **Listar Contatos**: Exibe todos os contatos cadastrados em ordem alfabética.
* **Compatibilidade Multiplataforma**: O código detecta o sistema operacional (Windows ou Unix-like) para adaptar os comandos de limpar o terminal e pausar a execução.
* **Interface de Linha de Comando**: Um menu interativo simples para facilitar a interação do usuário.

## 🌳 Estrutura de Dados: Árvore Binária de Busca

A escolha da Árvore Binária de Busca (ABB) como estrutura de dados central não foi por acaso. Ela oferece as seguintes vantagens para este projeto:

-   **Busca Eficiente**: A busca por um nome tem complexidade de tempo média de $O(\log n)$, sendo muito mais rápida que a busca em uma lista linear ($O(n)$).
-   **Inserção e Remoção Eficientes**: Assim como a busca, a inserção e a remoção também possuem complexidade de tempo média de $O(\log n)$.
-   **Ordenação Intrínseca**: A listagem de todos os contatos em ordem alfabética é uma operação natural e eficiente em uma ABB, realizada através de um percurso em-ordem (in-order traversal).

## 🚀 Como Compilar e Executar

Para compilar e executar este projeto, você precisará de um compilador C, como o **GCC**.

### Pré-requisitos

-   **GCC** (GNU Compiler Collection) ou outro compilador C.
-   **Git** (para clonar o repositório).

### Passos

1.  **Clone o repositório:**
    ```bash
    git clone <URL-DO-SEU-REPOSITORIO>
    cd <NOME-DA-PASTA-DO-REPOSITORIO>
    ```

2.  **Compile o código-fonte:**
    O arquivo `arvore_bruno_24795502.c` pode ser compilado com o seguinte comando no terminal:
    ```bash
    gcc arvore_bruno_24795502.c -o agenda_arvore
    ```
    *Isso criará um arquivo executável chamado `agenda_arvore` (ou `agenda_arvore.exe` no Windows).*

3.  **Execute o programa:**
    -   No **Linux ou macOS**:
        ```bash
        ./agenda_arvore
        ```
    -   No **Windows**:
        ```bash
        agenda_arvore.exe
        ```

Após a execução, um menu interativo será exibido no terminal.

## 🔧 Estrutura do Código

O código está organizado da seguinte forma:

-   `struct Contato`: Define a estrutura de um nó da árvore, contendo o nome, o celular e ponteiros para os filhos da esquerda (`esq`) e da direita (`dir`).

-   **Funções da Árvore Binária de Busca:**
    -   `inserir()`: Adiciona um novo nó na árvore.
    -   `buscar()`: Procura por um nó com base no nome.
    -   `remover()`: Remove um nó da árvore, tratando os três casos possíveis (nó folha, nó com um filho e nó com dois filhos).
    -   `listar()`: Percorre a árvore em-ordem para imprimir os contatos em ordem alfabética.
    -   `liberar()`: Libera toda a memória alocada pela árvore.

-   **Funções de Interface com o Usuário:**
    -   `main()`: Contém o loop principal do programa e o menu de opções.
    -   `adicionar_contato()`, `buscar_contato()`, `remover_contato()`, `listar_contatos()`: Funções que interagem com o usuário para obter dados e chamar as funções correspondentes da árvore.

-   **Funções Auxiliares:**
    -   `limpar_terminal()`: Limpa a tela do console.
    -   `pausar_tela()`: Pausa a execução até que o usuário pressione Enter.

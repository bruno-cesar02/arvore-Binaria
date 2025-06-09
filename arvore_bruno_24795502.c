#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Detectar o sistema operacional para limpar e pausar
#ifdef _WIN32
#define CLEAR "cls"
#define PAUSE "pause"
#else
#define CLEAR "clear"
#define PAUSE "read -p 'Pressione Enter para continuar...'"
#endif

// Estrutura do contato
struct Contato {
    char nome[50];
    char celular[50];
    struct Contato *esq, *dir;
};

// Funções auxiliares
void limpar_terminal() {
    system(CLEAR);
}

void pausar_tela() {
    system(PAUSE);
}

// Função para criar um novo contato
struct Contato* criar_contato(char* nome, char* celular) {
    struct Contato* novo = (struct Contato*) malloc(sizeof(struct Contato));
    if (novo == NULL) {
        printf("Erro: Falha ao alocar memoria!\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    strcpy(novo->celular, celular);
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Função para inserir contato na árvore
struct Contato* inserir(struct Contato* raiz, struct Contato* novo) {
    if (raiz == NULL) return novo;
    int cmp = strcmp(novo->nome, raiz->nome);
    if (cmp < 0)
        raiz->esq = inserir(raiz->esq, novo);
    else if (cmp > 0)
        raiz->dir = inserir(raiz->dir, novo);
    else {
        printf("Nome %s ja existe!\n", novo->nome);
        free(novo);
    }
    return raiz;
}

// Função para buscar contato
struct Contato* buscar(struct Contato* raiz, char* nome) {
    if (raiz == NULL || strcmp(raiz->nome, nome) == 0) return raiz;
    if (strcmp(nome, raiz->nome) < 0) return buscar(raiz->esq, nome);
    return buscar(raiz->dir, nome);
}

// Função para listar contatos em ordem
void listar(struct Contato* raiz) {
    if (raiz != NULL) {
        listar(raiz->esq);
        printf("Nome: %s, Celular: %s\n", raiz->nome, raiz->celular);
        listar(raiz->dir);
    }
}

// Função para encontrar o menor valor (usada em remover)
struct Contato* menor(struct Contato* raiz) {
    struct Contato* atual = raiz;
    while (atual && atual->esq != NULL) atual = atual->esq;
    return atual;
}

// Função para remover contato
struct Contato* remover(struct Contato* raiz, char* nome) {
    if (raiz == NULL) return raiz;
    int cmp = strcmp(nome, raiz->nome);
    if (cmp < 0)
        raiz->esq = remover(raiz->esq, nome);
    else if (cmp > 0)
        raiz->dir = remover(raiz->dir, nome);
    else {
        if (raiz->esq == NULL) {
            struct Contato* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            struct Contato* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        struct Contato* temp = menor(raiz->dir);
        strcpy(raiz->nome, temp->nome);
        strcpy(raiz->celular, temp->celular);
        raiz->dir = remover(raiz->dir, temp->nome);
    }
    return raiz;
}

// Função para liberar a memória da árvore
void liberar(struct Contato* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}

// Funções de interface com o usuário
void adicionar_contato(struct Contato** raiz) {
    limpar_terminal();
    char nome[50], celular[50];
    printf("Digite o nome: ");
    scanf("%49s", nome);  // Limita a 49 caracteres para evitar overflow
    printf("Digite o celular: ");
    scanf("%49s", celular);
    struct Contato* novo = criar_contato(nome, celular);
    if (buscar(*raiz, nome) != NULL) {
        printf("Nome %s ja existe!\n", nome);
        free(novo);
    } else {
        *raiz = inserir(*raiz, novo);
        printf("Contato adicionado!\n");
    }
    pausar_tela();
}

void buscar_contato(struct Contato* raiz) {
    limpar_terminal();
    char nome[50];
    printf("Digite o nome para buscar: ");
    scanf("%49s", nome);
    struct Contato* achado = buscar(raiz, nome);
    if (achado) {
        printf("Contato: %s, Celular: %s\n", achado->nome, achado->celular);
    } else {
        printf("Contato nao encontrado.\n");
    }
    pausar_tela();
}

void remover_contato(struct Contato** raiz) {
    limpar_terminal();
    char nome[50];
    printf("Digite o nome para remover: ");
    scanf("%49s", nome);
    *raiz = remover(*raiz, nome);
    printf("Contato removido (se existia).\n");
    pausar_tela();
}

void listar_contatos(struct Contato* raiz) {
    limpar_terminal();
    printf("Lista de contatos:\n");
    listar(raiz);
    pausar_tela();
}

// Função principal
int main() {
    struct Contato* raiz = NULL;
    int op;
    do {
        limpar_terminal();
        printf("Menu de Contatos:\n");
        printf("1. Adicionar contato\n");
        printf("2. Buscar contato\n");
        printf("3. Remover contato\n");
        printf("4. Listar contatos\n");
        printf("5. Sair\n");
        printf("DIGITE A OPCAO: ");
        scanf("%d", &op);
        printf("======================================\n");
        switch (op) {
            case 1:
                adicionar_contato(&raiz);
                break;
            case 2:
                buscar_contato(raiz);
                break;
            case 3:
                remover_contato(&raiz);
                break;
            case 4:
                listar_contatos(raiz);
                break;
            case 5:
                limpar_terminal();
                liberar(raiz);
                printf("Saindo...\n");
                pausar_tela();
                break;
            default:
                limpar_terminal();
                printf("Opcao invalida! Tente novamente.\n");
                pausar_tela();
        }
    } while (op != 5);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa um comodo da mansao
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Estrutura que representa um no da arvore BST de pistas
typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

/**
 * Funcao criarSala
 * Cria dinamicamente um comodo com nome e pista (opcional).
 */
Sala* criarSala(const char* nome, const char* pista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memoria para a sala.\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    if (pista != NULL)
        strcpy(novaSala->pista, pista);
    else
        strcpy(novaSala->pista, "");
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

/**
 * Funcao inserirPista
 * Insere uma nova pista na arvore BST de pistas.
 */
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    if (raiz == NULL) {
        PistaNode* novoNo = (PistaNode*)malloc(sizeof(PistaNode));
        if (novoNo == NULL) {
            printf("Erro ao alocar memoria para a pista.\n");
            exit(1);
        }
        strcpy(novoNo->pista, pista);
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        return novoNo;
    }

    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    return raiz;
}

/**
 * Funcao exibirPistas
 * Imprime todas as pistas coletadas em ordem alfabetica.
 */
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

/**
 * Funcao explorarSalasComPistas
 * Permite ao jogador navegar pela mansao e coleta pistas automaticamente.
 */
void explorarSalasComPistas(Sala* atual, PistaNode** pistasColetadas) {
    char escolha;

    while (atual != NULL) {
        printf("\nVoce esta na sala: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);
            *pistasColetadas = inserirPista(*pistasColetadas, atual->pista);
        } else {
            printf("Nenhuma pista nesta sala.\n");
        }

        printf("Escolha um caminho: (e) esquerda, (d) direita, (s) sair: ");
        scanf(" %c", &escolha);

        if (escolha == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Nao ha caminho a esquerda. Tente novamente.\n");
            }
        } else if (escolha == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Nao ha caminho a direita. Tente novamente.\n");
            }
        } else if (escolha == 's') {
            printf("Exploracao encerrada pelo jogador.\n");
            break;
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }
}

/**
 * Funcao main
 * Monta o mapa da mansao e inicia a exploracao com coleta de pistas.
 */
int main() {
    // Criacao das salas da mansao com pistas
    Sala* hall = criarSala("Hall de Entrada", "Pegadas misteriosas");
    Sala* salaEstar = criarSala("Sala de Estar", "Xicara quebrada");
    Sala* cozinha = criarSala("Cozinha", "");
    Sala* biblioteca = criarSala("Biblioteca", "Livro rasgado");
    Sala* jardim = criarSala("Jardim", "Luvas sujas");
    Sala* escritorio = criarSala("Escritorio", "Bilhete suspeito");

    // Construcao da arvore binaria da mansao
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = escritorio;

    // Inicializa a arvore de pistas coletadas
    PistaNode* pistasColetadas = NULL;

    printf("Bem-vindo ao Detective Quest!\nExplore a mansao e colete pistas para resolver o misterio...\n");

    // Inicia a exploracao com coleta de pistas
    explorarSalasComPistas(hall, &pistasColetadas);

    // Exibe todas as pistas coletadas em ordem alfabetica
    printf("\nPistas coletadas:\n");
    exibirPistas(pistasColetadas);

    return 0;
}
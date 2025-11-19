#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10

// Estrutura que representa um comodo da mansao
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Estrutura da BST de pistas coletadas
typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

// Estrutura da tabela hash (pista -> suspeito)
typedef struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode* proximo;
} HashNode;

HashNode* tabelaHash[TAMANHO_TABELA] = {NULL};

/**
 * Funcao hash_simples
 * Gera um indice para a tabela hash baseado na soma dos caracteres da pista.
 */
int hash_simples(const char* str) {
    int soma = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        soma += str[i];
    }
    return soma % TAMANHO_TABELA;
}

/**
 * Funcao criarSala
 * Cria dinamicamente um comodo com nome e pista.
 */
Sala* criarSala(const char* nome, const char* pista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

/**
 * Funcao inserirPista
 * Insere uma pista na BST de pistas coletadas.
 */
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);
    return raiz;
}

/**
 * Funcao inserirNaHash
 * Insere uma associacao pista/suspeito na tabela hash.
 */
void inserirNaHash(const char* pista, const char* suspeito) {
    int indice = hash_simples(pista);
    HashNode* novo = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = tabelaHash[indice];
    tabelaHash[indice] = novo;
}

/**
 * Funcao encontrarSuspeito
 * Retorna o nome do suspeito associado a uma pista.
 */
char* encontrarSuspeito(const char* pista) {
    int indice = hash_simples(pista);
    HashNode* atual = tabelaHash[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;
        atual = atual->proximo;
    }
    return NULL;
}

/**
 * Funcao explorarSalas
 * Navega pela mansao e coleta pistas.
 */
void explorarSalas(Sala* atual, PistaNode** pistasColetadas) {
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
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Nao ha caminho a esquerda.\n");
        } else if (escolha == 'd') {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("Nao ha caminho a direita.\n");
        } else if (escolha == 's') {
            printf("Exploracao encerrada.\n");
            break;
        } else {
            printf("Opcao invalida.\n");
        }
    }
}

/**
 * Funcao exibirPistas
 * Exibe as pistas coletadas em ordem alfabetica.
 */
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

/**
 * Funcao verificarSuspeitoFinal
 * Conta quantas pistas apontam para o suspeito acusado.
 */
int contarPistasPorSuspeito(PistaNode* raiz, const char* suspeito) {
    if (raiz == NULL) return 0;
    int count = 0;
    char* s = encontrarSuspeito(raiz->pista);
    if (s != NULL && strcmp(s, suspeito) == 0)
        count = 1;
    return count + contarPistasPorSuspeito(raiz->esquerda, suspeito) + contarPistasPorSuspeito(raiz->direita, suspeito);
}

/**
 * Funcao main
 * Monta o mapa, associa pistas a suspeitos e conduz o julgamento.
 */
int main() {
    // Criacao da mansao
    Sala* hall = criarSala("Hall de Entrada", "Pegadas misteriosas");
    Sala* salaEstar = criarSala("Sala de Estar", "Xicara quebrada");
    Sala* cozinha = criarSala("Cozinha", "");
    Sala* biblioteca = criarSala("Biblioteca", "Livro rasgado");
    Sala* jardim = criarSala("Jardim", "Luvas sujas");
    Sala* escritorio = criarSala("Escritorio", "Bilhete suspeito");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = escritorio;

    // Associacoes pista -> suspeito
    inserirNaHash("Pegadas misteriosas", "Carlos");
    inserirNaHash("Xicara quebrada", "Ana");
    inserirNaHash("Livro rasgado", "Carlos");
    inserirNaHash("Luvas sujas", "Bruno");
    inserirNaHash("Bilhete suspeito", "Carlos");

    PistaNode* pistasColetadas = NULL;

    printf("Bem-vindo ao capitulo final de Detective Quest!\nExplore a mansao e descubra quem e o culpado...\n");

    explorarSalas(hall, &pistasColetadas);

    printf("\nPistas coletadas:\n");
    exibirPistas(pistasColetadas);

    // Julgamento final
    char suspeitoFinal[50];
    printf("\nQuem voce acusa como culpado? ");
    scanf(" %[^\n]", suspeitoFinal);

    int total = contarPistasPorSuspeito(pistasColetadas, suspeitoFinal);
    if (total >= 2) {
        printf("Acusacao valida! %s foi identificado(a) como culpado(a) com %d pistas.\n", suspeitoFinal, total);
    } else {
        printf("Acusacao fraca. Apenas %d pista(s) apontam para %s. Caso nao resolvido.\n", total, suspeitoFinal);
    }

    return 0;
}
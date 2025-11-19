#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala da mansao
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

/**
 * Funcao criarSala
 * Cria dinamicamente uma sala com o nome especificado.
 */
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memoria para a sala.\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

/**
 * Funcao explorarSalas
 * Permite ao jogador navegar pela arvore da mansao.
 */
void explorarSalas(Sala* atual) {
    char escolha;

    while (atual != NULL) {
        printf("\nVoce esta na sala: %s\n", atual->nome);

        // Verifica se eh um no-folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim da exploracao. Voce chegou ao ultimo comodo.\n");
            break;
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
 * Monta o mapa da mansao e inicia a exploracao.
 */
int main() {
    // Criacao manual da arvore binaria da mansao
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");
    Sala* escritorio = criarSala("Escritorio");

    // Montagem da estrutura da mansao
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = escritorio;

    printf("Bem-vindo ao Detective Quest!\nExplore a mansao e descubra seus segredos...\n");

    // Inicio da exploracao
    explorarSalas(hall);

    // Liberacao de memoria
    free(hall);
    free(salaEstar);
    free(cozinha);
    free(biblioteca);
    free(jardim);
    free(escritorio);

    return 0;
}
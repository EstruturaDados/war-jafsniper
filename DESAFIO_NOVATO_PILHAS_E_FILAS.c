#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struct que representa uma peca do jogo
typedef struct {
    char nome; // Tipo da peca: 'I', 'O', 'T', 'L'
    int id;    // Identificador unico
} Peca;

// Tamanho maximo da fila
#define TAMANHO_FILA 5

// Fila circular
Peca fila[TAMANHO_FILA];
int inicio = 0;
int fim = 0;
int quantidade = 0;
int contadorID = 1; // Controla o id unico das pecas

// Funcao que gera uma nova peca automaticamente
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

// Funcao para inserir uma nova peca no final da fila (enqueue)
void inserirPeca() {
    if (quantidade == TAMANHO_FILA) {
        printf("Fila cheia. Nao e possivel inserir nova peca.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAMANHO_FILA;
    quantidade++;
    printf("Nova peca inserida na fila.\n");
}

// Funcao para jogar uma peca (remover da frente da fila - dequeue)
void jogarPeca() {
    if (quantidade == 0) {
        printf("Fila vazia. Nao ha pecas para jogar.\n");
        return;
    }

    Peca jogada = fila[inicio];
    inicio = (inicio + 1) % TAMANHO_FILA;
    quantidade--;
    printf("Peca jogada: Tipo %c | ID %d\n", jogada.nome, jogada.id);
}

// Funcao para exibir o estado atual da fila
void exibirFila() {
    printf("\nEstado atual da fila:\n");
    if (quantidade == 0) {
        printf("Fila vazia.\n");
        return;
    }

    int i = inicio;
    for (int count = 0; count < quantidade; count++) {
        printf("%d. Tipo: %c | ID: %d\n", count + 1, fila[i].nome, fila[i].id);
        i = (i + 1) % TAMANHO_FILA;
    }
}

// Funcao principal com menu interativo
int main() {
    srand(time(NULL)); // Inicializa gerador de numeros aleatorios
    int opcao;

    // Inicializa a fila com 5 pecas
    for (int i = 0; i < TAMANHO_FILA; i++) {
        inserirPeca();
    }

    do {
        exibirFila();
        printf("\nMenu Tetris Stack:\n");
        printf("1. Jogar peca\n");
        printf("2. Inserir nova peca\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca();
                break;
            case 2:
                inserirPeca();
                break;
            case 0:
                printf("Saindo do jogo. Ate a proxima!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
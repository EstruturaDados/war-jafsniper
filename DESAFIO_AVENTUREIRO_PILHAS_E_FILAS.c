#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struct que representa uma peca
typedef struct {
    char nome; // Tipo da peca: 'I', 'O', 'T', 'L'
    int id;    // Identificador unico
} Peca;

// Tamanhos das estruturas
#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

// Fila circular
Peca fila[TAMANHO_FILA];
int inicioFila = 0;
int fimFila = 0;
int quantidadeFila = 0;

// Pilha linear
Peca pilha[TAMANHO_PILHA];
int topoPilha = -1;

// Contador global de IDs
int contadorID = 1;

// Gera uma nova peca aleatoria
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

// Insere uma nova peca no final da fila
void inserirNaFila() {
    if (quantidadeFila == TAMANHO_FILA) return;
    fila[fimFila] = gerarPeca();
    fimFila = (fimFila + 1) % TAMANHO_FILA;
    quantidadeFila++;
}

// Remove a peca da frente da fila
Peca removerDaFila() {
    Peca removida = fila[inicioFila];
    inicioFila = (inicioFila + 1) % TAMANHO_FILA;
    quantidadeFila--;
    return removida;
}

// Insere uma peca no topo da pilha
int empilhar(Peca p) {
    if (topoPilha == TAMANHO_PILHA - 1) return 0;
    pilha[++topoPilha] = p;
    return 1;
}

// Remove a peca do topo da pilha
int desempilhar(Peca* p) {
    if (topoPilha == -1) return 0;
    *p = pilha[topoPilha--];
    return 1;
}

// Exibe o estado atual da fila
void exibirFila() {
    printf("\nFila de pecas futuras:\n");
    if (quantidadeFila == 0) {
        printf("Fila vazia.\n");
        return;
    }
    int i = inicioFila;
    for (int count = 0; count < quantidadeFila; count++) {
        printf("%d. Tipo: %c | ID: %d\n", count + 1, fila[i].nome, fila[i].id);
        i = (i + 1) % TAMANHO_FILA;
    }
}

// Exibe o estado atual da pilha
void exibirPilha() {
    printf("\nPilha de reserva:\n");
    if (topoPilha == -1) {
        printf("Pilha vazia.\n");
        return;
    }
    for (int i = topoPilha; i >= 0; i--) {
        printf("%d. Tipo: %c | ID: %d\n", topoPilha - i + 1, pilha[i].nome, pilha[i].id);
    }
}

// Exibe o estado geral
void exibirEstado() {
    printf("\n==============================");
    exibirFila();
    exibirPilha();
    printf("==============================\n");
}

// Menu principal
int main() {
    srand(time(NULL));
    int opcao;

    // Inicializa a fila com 5 pecas
    for (int i = 0; i < TAMANHO_FILA; i++) {
        inserirNaFila();
    }

    do {
        exibirEstado();
        printf("\nMenu Tetris Stack:\n");
        printf("1. Jogar peca\n");
        printf("2. Reservar peca\n");
        printf("3. Usar peca reservada\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (quantidadeFila == 0) {
                    printf("Fila vazia. Nao ha peca para jogar.\n");
                } else {
                    Peca jogada = removerDaFila();
                    printf("Peca jogada: Tipo %c | ID %d\n", jogada.nome, jogada.id);
                    inserirNaFila();
                }
                break;
            }
            case 2: {
                if (quantidadeFila == 0) {
                    printf("Fila vazia. Nao ha peca para reservar.\n");
                } else if (topoPilha == TAMANHO_PILHA - 1) {
                    printf("Pilha cheia. Nao e possivel reservar mais pecas.\n");
                } else {
                    Peca reservada = removerDaFila();
                    empilhar(reservada);
                    printf("Peca reservada: Tipo %c | ID %d\n", reservada.nome, reservada.id);
                    inserirNaFila();
                }
                break;
            }
            case 3: {
                Peca usada;
                if (desempilhar(&usada)) {
                    printf("Peca usada da reserva: Tipo %c | ID %d\n", usada.nome, usada.id);
                } else {
                    printf("Pilha vazia. Nao ha peca reservada para usar.\n");
                }
                break;
            }
            case 0:
                printf("Saindo do jogo. Ate a proxima!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
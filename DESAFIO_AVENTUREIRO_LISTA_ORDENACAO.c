#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct que representa um item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Capacidade maxima do vetor
#define MAX_ITENS 100

// Mochila com vetor
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

// Mochila com lista encadeada
No* mochilaLista = NULL;

// Contadores de comparacoes
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// Funcoes para vetor
void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("Mochila cheia.\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalVetor++] = novo;
    printf("Item inserido no vetor.\n");
}

void removerItemVetor() {
    char nome[30];
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalVetor--;
            printf("Item removido do vetor.\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

void listarItensVetor() {
    printf("\nItens no vetor:\n");
    for (int i = 0; i < totalVetor; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = i + 1; j < totalVetor; j++) {
            if (strcmp(mochilaVetor[i].nome, mochilaVetor[j].nome) > 0) {
                Item temp = mochilaVetor[i];
                mochilaVetor[i] = mochilaVetor[j];
                mochilaVetor[j] = temp;
            }
        }
    }
    printf("Vetor ordenado por nome.\n");
}

void buscarSequencialVetor() {
    char nome[30];
    printf("Nome do item para busca sequencial: ");
    scanf(" %[^\n]", nome);
    comparacoesSequencial = 0;

    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("Item encontrado: %s | Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
            return;
        }
    }
    printf("Item nao encontrado.\n");
    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
}

void buscarBinariaVetor() {
    char nome[30];
    printf("Nome do item para busca binaria: ");
    scanf(" %[^\n]", nome);
    comparacoesBinaria = 0;

    int inicio = 0, fim = totalVetor - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0) {
            printf("Item encontrado: %s | Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("Item nao encontrado.\n");
    printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
}

// Funcoes para lista encadeada
void inserirItemLista() {
    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;

    printf("Item inserido na lista.\n");
}

void removerItemLista() {
    char nome[30];
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nome);

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                mochilaLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item removido da lista.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item nao encontrado.\n");
}

void listarItensLista() {
    printf("\nItens na lista:\n");
    No* atual = mochilaLista;
    int i = 1;
    while (atual != NULL) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista() {
    char nome[30];
    printf("Nome do item para busca sequencial: ");
    scanf(" %[^\n]", nome);
    comparacoesSequencial = 0;

    No* atual = mochilaLista;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado: %s | Tipo: %s | Quantidade: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
    }

    printf("Item nao encontrado.\n");
    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
}

// Menu principal
int main() {
    int estrutura, opcao;

    do {
        printf("\nEscolha a estrutura:\n");
        printf("1. Vetor\n");
        printf("2. Lista encadeada\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &estrutura);

        if (estrutura == 1) {
            do {
                printf("\nMenu Vetor:\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar sequencial\n");
                printf("5. Ordenar vetor\n");
                printf("6. Buscar binaria\n");
                printf("0. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4: buscarSequencialVetor(); break;
                    case 5: ordenarVetor(); break;
                    case 6: buscarBinariaVetor(); break;
                }
            } while (opcao != 0);
        } else if (estrutura == 2) {
            do {
                printf("\nMenu Lista:\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar sequencial\n");
                printf("0. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItem
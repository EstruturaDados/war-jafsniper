#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct que representa um componente da torre
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Capacidade maxima
#define MAX_COMPONENTES 20

// Vetor de componentes
Componente torre[MAX_COMPONENTES];
int total = 0;

// Contadores de comparacoes
int comparacoesOrdenacao = 0;
int comparacoesBusca = 0;

// Funcao para mostrar todos os componentes
void mostrarComponentes(Componente vetor[], int n) {
    printf("\nComponentes:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].prioridade);
    }
}

// Bubble Sort por nome
void bubbleSortNome(Componente vetor[], int n) {
    comparacoesOrdenacao = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoesOrdenacao++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Componente temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente vetor[], int n) {
    comparacoesOrdenacao = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && strcmp(vetor[j].tipo, chave.tipo) > 0) {
            vetor[j + 1] = vetor[j];
            j--;
            comparacoesOrdenacao++;
        }
        vetor[j + 1] = chave;
        comparacoesOrdenacao++;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente vetor[], int n) {
    comparacoesOrdenacao = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoesOrdenacao++;
            if (vetor[j].prioridade < vetor[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = temp;
        }
    }
}

// Busca binaria por nome
int buscaBinariaPorNome(Componente vetor[], int n, char chave[]) {
    int inicio = 0, fim = n - 1;
    comparacoesBusca = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBusca++;
        int cmp = strcmp(vetor[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// Funcao para medir tempo de execucao
void medirTempo(void (*algoritmo)(Componente[], int), Componente vetor[], int n) {
    clock_t inicio = clock();
    algoritmo(vetor, n);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    printf("Comparacoes realizadas: %d\n", comparacoesOrdenacao);
}

// Funcao para cadastrar componentes
void cadastrarComponentes() {
    if (total >= MAX_COMPONENTES) {
        printf("Limite de componentes atingido.\n");
        return;
    }

    Componente novo;
    printf("Nome do componente: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do componente: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Prioridade (1 a 10): ");
    scanf("%d", &novo.prioridade);
    getchar(); // limpar buffer

    torre[total++] = novo;
    printf("Componente cadastrado.\n");
}

// Menu principal
int main() {
    int opcao;
    char chave[30];

    do {
        printf("\nMenu Torre de Fuga:\n");
        printf("1. Cadastrar componente\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente-chave por nome (Binaria)\n");
        printf("6. Mostrar componentes\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                cadastrarComponentes();
                break;
            case 2:
                medirTempo(bubbleSortNome, torre, total);
                break;
            case 3:
                medirTempo(insertionSortTipo, torre, total);
                break;
            case 4:
                medirTempo(selectionSortPrioridade, torre, total);
                break;
            case 5:
                printf("Digite o nome do componente-chave: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';
                int pos = buscaBinariaPorNome(torre, total, chave);
                if (pos != -1) {
                    printf("Componente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                           torre[pos].nome, torre[pos].tipo, torre[pos].prioridade);
                } else {
                    printf("Componente nao encontrado.\n");
                }
                printf("Comparacoes realizadas: %d\n", comparacoesBusca);
                break;
            case 6:
                mostrarComponentes(torre, total);
                break;
            case 0:
                printf("Saindo do sistema. Boa sorte na fuga!\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
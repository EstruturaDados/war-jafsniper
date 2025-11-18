// Desagio jogo WAR Aventureiro // 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um territorio
#define TAM_STRING_NOME 30
#define TAM_STRING_COR 10

typedef struct {
    char nome[TAM_STRING_NOME];
    char cor[TAM_STRING_COR];
    int q_tropas;
} Territorio;

// Funcao para cadastrar os territorios
void cadastrarTerritorios(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exercito: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].q_tropas);
    }
}

// Funcao para exibir os dados dos territorios
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n--- Territorios ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].q_tropas);
    }
}

// Funcao que simula o ataque entre dois territorios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nErro: Nao e possivel atacar um territorio da mesma cor!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nAtaque de %s contra %s\n", atacante->nome, defensor->nome);
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: Vitoria do atacante!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->q_tropas = atacante->q_tropas / 2;
    } else {
        printf("Resultado: Defesa bem-sucedida!\n");
        if (atacante->q_tropas > 0) {
            atacante->q_tropas--;
        }
    }
}

// Funcao para liberar a memoria alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // Inicializa a semente de aleatoriedade

    int total;
    printf("Digite a quantidade de territorios: ");
    scanf("%d", &total);

    // Alocacao dinamica dos territorios
    Territorio* mapa = (Territorio*)calloc(total, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, total);

    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        exibirTerritorios(mapa, total);
        
        int iAtacante, iDefensor;
        printf("\nEscolha o indice do territorio atacante: ");
        scanf("%d", &iAtacante);
        printf("Escolha o indice do territorio defensor: ");
        scanf("%d", &iDefensor);

        if (iAtacante < 0 || iAtacante >= total || iDefensor < 0 || iDefensor >= total) {
            printf("Indices invalidos. Tente novamente.\n");
            continue;
        }

        atacar(&mapa[iAtacante], &mapa[iDefensor]);

        printf("\nEstado atualizado dos territorios:\n");
        exibirTerritorios(mapa, total);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    }

    liberarMemoria(mapa);
    printf("\nMemoria liberada. Programa encerrado.\n");
    return 0;
}
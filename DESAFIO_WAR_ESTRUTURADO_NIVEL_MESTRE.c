// Desafio jogo WAR Nível Mestre //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING_NOME 30
#define TAM_STRING_COR 10
#define TAM_MISSAO 100

// Estrutura que representa um territorio no jogo
typedef struct {
    char nome[TAM_STRING_NOME];
    char cor[TAM_STRING_COR];
    int q_tropas;
} Territorio;

// Cadastra os territorios com nome, cor e quantidade de tropas
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

// Exibe os dados de todos os territorios cadastrados
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n--- Territorios ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].q_tropas);
    }
}

// Exibe a missao atribuida ao jogador (passagem por valor)
void exibirMissao(char* missao) {
    printf("\nMissao: %s\n", missao);
}

// Sorteia uma missao aleatoria e copia para o destino (passagem por referencia)
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Verifica se a missao foi cumprida com base no estado atual do mapa
int verificarMissao(char* missao, Territorio* mapa, int total) {
    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        int cont = 0;
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) {
                cont++;
                if (cont == 3) return 1;
            } else {
                cont = 0;
            }
        }
    } else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].q_tropas > 0)
                return 0;
        }
        return 1;
    } else if (strcmp(missao, "Controlar 2 territorios com mais de 5 tropas") == 0) {
        int cont = 0;
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0 && mapa[i].q_tropas > 5)
                cont++;
        }
        if (cont >= 2) return 1;
    } else if (strcmp(missao, "Ter pelo menos 4 territorios") == 0) {
        int cont = 0;
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0)
                cont++;
        }
        if (cont >= 4) return 1;
    } else if (strcmp(missao, "Eliminar todas as tropas da cor verde") == 0) {
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, "verde") == 0 && mapa[i].q_tropas > 0)
                return 0;
        }
        return 1;
    }
    return 0;
}

// Simula um ataque entre dois territorios com rolagem de dados
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

// Libera toda a memoria alocada dinamicamente
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

// Funcao principal que controla o fluxo do jogo
int main() {
    srand(time(NULL));

    // Vetor de missoes pre-definidas
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar 2 territorios com mais de 5 tropas",
        "Ter pelo menos 4 territorios",
        "Eliminar todas as tropas da cor verde"
    };
    int totalMissoes = 5;

    // Alocacao dinamica da missao do jogador
    char* missaoJogador = (char*)malloc(TAM_MISSAO * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    // Cadastro dos territorios
    int total;
    printf("\nDigite a quantidade de territorios: ");
    scanf("%d", &total);

    Territorio* mapa = (Territorio*)calloc(total, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        free(missaoJogador);
        return 1;
    }

    cadastrarTerritorios(mapa, total);

    // Loop de turnos com verificacao de missao
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

        if (verificarMissao(missaoJogador, mapa, total)) {
            printf("\nMissao cumprida! Voce venceu o jogo!\n");
            break;
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    }

    liberarMemoria(mapa, missaoJogador);
    printf("\nMemoria liberada. Programa encerrado.\n");
    return 0;
}
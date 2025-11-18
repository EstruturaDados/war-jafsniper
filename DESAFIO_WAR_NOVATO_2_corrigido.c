//======================================================================================
// Jogo War em linguagem C //

// Objetivos:

// 1 - Definir estrutura com:
// 	NOME
// 	COR
// 	TROPA 

// 2 - Criar um Vetor para armazenar os 5 territórios
// 	Pedir ao usuário para preencher os dados de cada território pelo terminal.

// 3 - Exibir a lista completa com todos os dados do Mapa Mundi, formado pelos cinco territórios.


///// SAÍDA /////

// ========================================================

// Vamos cadastrar os 5 terriorios iniciais do nosso mundo.

// --- Cadatrando Territorio 1 ---
// Nome do Territorio:
// Cor do Exercito (ex.: Azul, Verde, Amarelo...):
// Quantidade de tropas:

// --- Cadatrando Territorio 2 ---
// Nome do Territorio:
// Cor do Exercito (ex.: Azul, Verde, Amarelo...):
// Quantidade de tropas:

// --- Cadatrando Territorio 3 ---
// Nome do Territorio:
// Cor do Exercito (ex.: Azul, Verde, Amarelo...):
// Quantidade de tropas:

// --- Cadatrando Territorio 4 ---
// Nome do Territorio:
// Cor do Exercito (ex.: Azul, Verde, Amarelo...):
// Quantidade de tropas:

// --- Cadatrando Territorio 5 ---
// Nome do Territorio:
// Cor do Exercito (ex.: Azul, Verde, Amarelo...):
// Quantidade de tropas:

// ========================================================


// *** Cadatro inicial concluido com sucesso!
// ========================================================
// 	MAPA DO MUNDO - ESTADO ATUAL
// ========================================================

// TERRITORIO 1:
// 	- Nome: (nome)
// 	- Dominado por: Exercito (cor)
// 	- Tropas: (quantidade)


// TERRITORIO 2:
// 	- Nome: (nome)
// 	- Dominado por: Exercito (cor)
// 	- Tropas: (quantidade)

// TERRITORIO 3:
// 	- Nome: (nome)
// 	- Dominado por: Exercito (cor)
// 	- Tropas: (quantidade)

// TERRITORIO 4:
// 	- Nome: (nome)
// 	- Dominado por: Exercito (cor)
// 	- Tropas: (quantidade)

// TERRITORIO 5:
// 	- Nome: (nome)
// 	- Dominado por: Exercito (cor)
// 	- Tropas: (quantidade)


//
//======================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define TAM_STRING 20

// --- Definição da Estrutura --- //
struct Territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int Q_tropas;
};

// --- Função para limpar o buffer de entrada --- //
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal --- //
int main() {
    struct Territorio lista[MAX_TERRITORIOS];
    int totalTerritorios = 0;

    printf("========================================\n");
    printf("        CADASTRO DE TERRITORIOS\n");
    printf("========================================\n\n");
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n\n");

    // Cadastro dos territórios
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        fgets(lista[i].nome, TAM_STRING, stdin);
        lista[i].nome[strcspn(lista[i].nome, "\n")] = '\0'; // Remove o '\n'

        printf("Cor do Exercito (ex.: Azul, Verde, Amarelo...): ");
        fgets(lista[i].cor, TAM_STRING, stdin);
        lista[i].cor[strcspn(lista[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &lista[i].Q_tropas);
        limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf

        totalTerritorios++;
        printf("\n");
    }
        printf("A lista de territorios esta completa.\n\n");   

    printf("========================================\n");
    printf("      MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("========================================\n\n");

    // Listagem dos territórios
    for (int i = 0; i < totalTerritorios; i++) {
        printf("TERRITORIO %d:\n", i + 1);
        printf("  - Nome: %s\n", lista[i].nome);
        printf("  - Dominado por: Exercito %s\n", lista[i].cor);
        printf("  - Tropas: %d\n", lista[i].Q_tropas);
        printf("----------------------------------------\n");
    }

    return 0;
}
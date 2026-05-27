#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    int qtd, i, atk, def;
    srand(time(NULL)); // Semente para os dados aleatórios

    printf("Quantos territorios? ");
    scanf("%d", &qtd);

    // Alocação dinâmica simples
    Territorio* mapa = (Territorio*) malloc(qtd * sizeof(Territorio));

    // Cadastro dos territórios
    for(i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i);
        printf("Nome: ");    scanf(" %[^\n]", mapa[i].nome);
        printf("Cor: ");     scanf(" %[^\n]", mapa[i].cor);
        printf("Tropas: ");   scanf("%d", &mapa[i].tropas);
    }

    // Exibição inicial
    printf("\n=== MAPA ATUAL ===\n");
    for(i = 0; i < qtd; i++) {
        printf("[%d] %s (%s) - Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    // Escolha do ataque
    printf("\nEscolha o indice do ATACANTE e do DEFENSOR: ");
    scanf("%d %d", &atk, &def);

    // Uso de ponteiros para referenciar os territórios escolhidos
    Territorio* pAtk = &mapa[atk];
    Territorio* pDef = &mapa[def];

    printf("\n%s ataca %s!\n", pAtk->nome, pDef->nome);

    // Dados de 1 a 6
    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtk, dadoDef);

    // Resolução da batalha e atualização dos dados
    if (dadoAtk > dadoDef) {
        printf("VITORIA DO ATACANTE! O territorio foi conquistado.\n");
        strcpy(pDef->cor, pAtk->cor);       // Defensor muda de cor
        pDef->tropas = pAtk->tropas / 2;    // Recebe metade das tropas
        pAtk->tropas -= pDef->tropas;       // Atacante perde as tropas enviadas
    } else {
        printf("DEFENSOR VENCEU! O ataque falhou.\n");
        if (pAtk->tropas > 0) pAtk->tropas--; // Atacante perde 1 tropa
    }

    // Exibição final pós-ataque
    printf("\n=== MAPA ATUALIZADO ===\n");
    for(i = 0; i < qtd; i++) {
        printf("[%d] %s (%s) - Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    // Liberação da memória
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");

    return 0;
}
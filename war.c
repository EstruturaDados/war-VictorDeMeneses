#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função modularizada para atribuição da missão por referência (ponteiro)
void atribuirMissao(char* destino, const char* missoes[], int total) {
    int sorteio = rand() % total;
    strcpy(destino, missoes[sorteio]); // Copia para o destino alocado
}

// Função modularizada para verificação da missão
int verificarMissao(char* missao, Territorio* mapa, int qtd, char* corJogador) {
    int i, contagem = 0;
    for(i = 0; i < qtd; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            contagem++; // Conta quantos territórios o jogador possui
        }
    }
    // Lógica simples: se a missão pede 2 ou 3 e o jogador atingiu essa quantidade
    if (strstr(missao, "2") && contagem >= 2) return 1;
    if (strstr(missao, "3") && contagem >= 3) return 1;
    return 0;
}

int main() {
    srand(time(NULL));
    int qtd, i, atk, def;

    // Vetor de strings com as descrições das missões
    const char* listaMissoes[] = {
        "Conquistar pelo menos 2 territorios",
        "Dominar 3 territorios do mapa"
    };

    printf("Quantos territorios? ");
    scanf("%d", &qtd);

    // Alocação dinâmica de memória (Mapa e Missão)
    Territorio* mapa = (Territorio*) malloc(qtd * sizeof(Territorio));
    char* missao = (char*) malloc(100 * sizeof(char));

    // Cadastro simplificado
    for(i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\nNome: ", i);  scanf(" %[^\n]", mapa[i].nome);
        printf("Cor: ");                      scanf(" %[^\n]", mapa[i].cor);
        printf("Tropas: ");                   scanf("%d", &mapa[i].tropas);
    }

    // Define a cor do jogador humano com base no primeiro território cadastrado
    char minhaCor[10];
    strcpy(minhaCor, mapa[0].cor);

    // Atribuição (Passagem por referência) e Exibição única
    atribuirMissao(missao, listaMissoes, 2);
    printf("\n=== SUA MISSAO SECRETA: %s ===\n", missao);

    // Rodada Única de Ataque
    printf("\n=== MAPA ATUAL ===\n");
    for(i = 0; i < qtd; i++) printf("[%d] %s (%s) - Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);

    printf("\nEscolha o indice do ATACANTE e do DEFENSOR: ");
    scanf("%d %d", &atk, &def);

    // Validação técnica: Não pode atacar a própria cor (Fogo amigo)
    if (strcmp(mapa[atk].cor, mapa[def].cor) == 0) {
        printf("Erro: Voce nao pode atacar seu proprio exercito!\n");
    } else {
        // Simulação do ataque usando ponteiros locais para alterar o mapa
        Territorio* pAtk = &mapa[atk];
        Territorio* pDef = &mapa[def];
        
        int dAtk = (rand() % 6) + 1;
        int dDef = (rand() % 6) + 1;
        printf("Dados -> Atacante: %d | Defensor: %d\n", dAtk, dDef);

        if (dAtk > dDef) {
            printf("VITORIA! Territorio conquistado.\n");
            strcpy(pDef->cor, pAtk->cor);       // Atualização de dados (muda de dono)
            pDef->tropas = pAtk->tropas / 2;    // Transfere metade das tropas
            pAtk->tropas -= pDef->tropas;
        } else {
            printf("DERROTA! O ataque falhou.\n");
            if (pAtk->tropas > 0) pAtk->tropas--;
        }
    }

    // Verificação silenciosa de vitória ao fim do turno
    if (verificarMissao(missao, mapa, qtd, minhaCor)) {
        printf("\nVOCO VENCEU O JOGO! Sua missao foi cumprida.\n");
    } else {
        printf("\nA missao ainda nao foi cumprida.\n");
    }

    // Liberação de toda a memória alocada
    free(mapa);
    free(missao);
    printf("Memoria liberada. Fim.\n");

    return 0;
}
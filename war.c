#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor global e contador para simplificar a passagem de parâmetros nas funções
Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para listar todos os itens da mochila
void listarItens() {
    printf("\n=== SEU INVENTARIO (%d/%d) ===\n", totalItens, MAX_ITENS);
    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }
    for (int i = 0; i < totalItens; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Qtd: %d\n", i, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função para inserir um novo item na mochila
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Nao eh possivel carregar mais itens.\n");
        return;
    }
    
    printf("\n--- COLETAR NOVO ITEM ---\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", mochila[totalItens].nome);
    printf("Tipo (Arma, Municao, Cura): ");
    scanf(" %[^\n]", mochila[totalItens].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    
    totalItens++; // Incrementa o total de itens na mochila
    printf("Item adicionado com sucesso!\n");
    listarItens();
}

// Função de busca sequencial pelo nome
void buscarItem() {
    char termoBusca[30];
    printf("\nDigite o nome do item que procura: ");
    scanf(" %[^\n]", termoBusca);
    
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, termoBusca) == 0) {
            printf("\nItem Encontrado! Posicao [%d] | Tipo: %s | Qtd: %d\n", i, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("\nItem '%s' nao foi encontrado na mochila.\n", termoBusca);
}

// Função para remover um item deslocando os elementos seguintes
void removerItem() {
    char termoRemover[30];
    printf("\nDigite o nome do item que deseja descartar: ");
    scanf(" %[^\n]", termoRemover);
    
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, termoRemover) == 0) {
            // Move todos os itens da frente uma posição para trás para preencher o buraco
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--; // Reduz o tamanho da lista
            printf("Item removido com sucesso!\n");
            listarItens();
            return;
        }
    }
    printf("Item nao encontrado para remocao.\n");
}

int main() {
    int opcao = 0;

    // Menu interativo simples
    while (opcao != 5) {
        printf("\n======= MENU DA MOCHILA =======\n");
        printf("1. Coletar Item (Inserir)\n");
        printf("2. Descartar Item (Remover)\n");
        printf("3. Olhar Mochila (Listar)\n");
        printf("4. Procurar por Item (Buscar)\n");
        printf("5. Sair do Jogo\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 5: printf("\nSaindo... Inventario salvo.\n"); break;
            default: printf("\nAcao invalida!\n");
        }
    }

    return 0;
}
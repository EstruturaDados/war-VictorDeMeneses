#include <stdio.h>
#include <string.h>

// Definição da struct
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Criação do vetor para 5 territórios
    struct Territorio lista[5];
    int i;

    // Entrada dos dados
    printf("=== CADASTRO DOS TERRITORIOS ===\n\n");
    for(i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        
        printf("Nome: ");
        scanf(" %[^\n]", lista[i].nome); // O espaco antes de % garante a limpeza do buffer
        
        printf("Cor do exercito: ");
        scanf(" %[^\n]", lista[i].cor);
        
        printf("Quantidade de tropas: ");
        scanf("%d", &lista[i].tropas);
        
        printf("\n");
    }

    // Exibição dos dados
    printf("=== DADOS REGISTRADOS ===\n\n");
    for(i = 0; i < 5; i++) {
        printf("Territorio: %s | Cor: %s | Tropas: %d\n", 
                lista[i].nome, lista[i].cor, lista[i].tropas);
    }

    return 0;
}
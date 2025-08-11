#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constantes globais
#define MAX_TERRITORIOS 50

// struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

void limpaBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Territorio territorios[MAX_TERRITORIOS];
    int totalTerritorios = 0;
    int opcao;
    
    do {
        printf("\n==================================\n");
        printf("\n### DESAFIO WAR - NÍVEL NOVATO ###\n");
        printf("\n==================================\n");
        printf("1 - CADASTRAR TERRITÓRIO\n");
        printf("2 - LISTAR TERRITÓRIOS\n");
        printf("0 - SAIR\n");
        printf("\n----------------------------------\n");
        printf("Escolha uma opção: ");

        scanf("%d", &opcao);
        limpaBufferEntrada();

        switch (opcao) {
            case 1: // CADASTRO DE TERRITORIOS
                printf("\n--- Cadastrar Novo Território ---\n");

                if (totalTerritorios < MAX_TERRITORIOS) {
                    printf("Digite o Nome do Território: ");
                    fgets(territorios[totalTerritorios].nome, 30, stdin);
                    territorios[totalTerritorios].nome[strcspn(territorios[totalTerritorios].nome, "\n")] = '\0';

                    printf("Digite a Cor: ");
                    fgets(territorios[totalTerritorios].cor, 10, stdin);
                    territorios[totalTerritorios].cor[strcspn(territorios[totalTerritorios].cor, "\n")] = '\0';

                    printf("Digite a quantidade de Tropas: ");
                    scanf("%d", &territorios[totalTerritorios].tropas);
                    limpaBufferEntrada();

                    totalTerritorios++;

                    printf("\nTerritório cadastrado com sucesso!\n");
                } else {
                    printf("\nQuantidade máxima de Territórios cadastrados atingida.");
                }

                printf("\nPressione ENTER para continuar...");
                getchar();
                break;
            case 2: // LISTAGEM DE TERRITORIOS
                printf("\n--- Lista de Territórios Cadastrados ---\n");

                if (totalTerritorios == 0) {
                    printf("\nNenhum território cadastrado!");
                } else {
                    for (int i = 0; i < totalTerritorios; i++) {
                        printf("\n====================================\n");
                        printf("TERRITÓRIO %d\n", i + 1);
                        printf("Nome: %s\n", territorios[i].nome);
                        printf("Cor: %s\n", territorios[i].cor);
                        printf("Tropas: %d\n", territorios[i].tropas);
                    }
                    printf("\n====================================\n");
                }

                printf("\nPressione ENTER para continuar...");
                getchar();
                break;
            case 0: // SAIR
                printf("\nSaindo do sistema...\n");
                break;
            default: // OPCAO INVALIDA
                printf("\n Opção inválida. Tente novamente.\n");

                printf("\nPressione ENTER para continuar...");
                getchar();
                break;
        }

    } while (opcao != 0);

    return 0;
}

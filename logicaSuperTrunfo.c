#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função para limpar buffer
void limpaBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar território
void cadastrarTerritorio(struct Territorio* t) {
    printf("Digite o Nome do Território: ");
    fgets(t->nome, 30, stdin);
    t->nome[strcspn(t->nome, "\n")] = '\0';

    printf("Digite a Cor: ");
    fgets(t->cor, 10, stdin);
    t->cor[strcspn(t->cor, "\n")] = '\0';

    printf("Digite a quantidade de Tropas: ");
    scanf("%d", &t->tropas);
    limpaBufferEntrada();
}

// Função para listar territórios
void listarTerritorios(struct Territorio* lista, int total) {
    printf("\n=== MAPA DO MUNDO ===\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s (Exército %s, Tropas: %d)\n", 
               i + 1, lista[i].nome, lista[i].cor, lista[i].tropas);
    }
}

// Função de ataque
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Você não pode atacar territórios da mesma cor!\n");
        return;
    }
    if (atacante->tropas < 1) {
        printf("O território atacante não tem tropas suficientes!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Atacante %s rolou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor %s rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Vitória do ataque! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;
        if (defensor->tropas <= 0) {
            printf("O território %s agora pertence ao exército %s!\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2; // transfere metade
            atacante->tropas /= 2;
        }
    } else {
        printf("O ataque falhou! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;
    }
}

// Função para liberar memória
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL));

    int totalTerritorios;
    printf("Digite o número de territórios: ");
    scanf("%d", &totalTerritorios);
    limpaBufferEntrada();

    // Alocação dinâmica
    struct Territorio* territorios = calloc(totalTerritorios, sizeof(struct Territorio));

    // Cadastro inicial
    for (int i = 0; i < totalTerritorios; i++) {
        printf("\n--- Cadastrando Território %d ---\n", i + 1);
        cadastrarTerritorio(&territorios[i]);
    }

    int opcao;
    do {
        printf("\n1 - Listar territórios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limpaBufferEntrada();

        if (opcao == 1) {
            listarTerritorios(territorios, totalTerritorios);
        }
        else if (opcao == 2) {
            listarTerritorios(territorios, totalTerritorios);
            int atq, def;
            printf("Escolha o território atacante (1 a %d): ", totalTerritorios);
            scanf("%d", &atq);
            printf("Escolha o território defensor (1 a %d): ", totalTerritorios);
            scanf("%d", &def);
            limpaBufferEntrada();

            if (atq >= 1 && atq <= totalTerritorios && def >= 1 && def <= totalTerritorios && atq != def) {
                atacar(&territorios[atq - 1], &territorios[def - 1]);
            } else {
                printf("Opção inválida!\n");
            }
        }
    } while (opcao != 0);

    liberarMemoria(territorios);
    return 0;
}

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

// Função para exibir o mapa
void exibirMapa(struct Territorio* lista, int total) {
    printf("============= MAPA DO MUNDO =============\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %-10s (Exercito %-7s, Tropas: %d)\n", 
               i + 1, lista[i].nome, lista[i].cor, lista[i].tropas);
    }
    printf("==========================================\n");
}

// Cadastro de território
void cadastrarTerritorio(struct Territorio* t) {
    printf("Nome do Territorio: ");
    fgets(t->nome, 30, stdin);
    t->nome[strcspn(t->nome, "\n")] = '\0';

    printf("Cor do Exercito: ");
    fgets(t->cor, 10, stdin);
    t->cor[strcspn(t->cor, "\n")] = '\0';

    printf("Numero de Tropas: ");
    scanf("%d", &t->tropas);
    limpaBufferEntrada();
}

// Função de ataque
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Nao pode atacar territorios da mesma cor!\n");
        return;
    }
    if (atacante->tropas < 1) {
        printf("O atacante nao tem tropas suficientes!\n");
        return;
    }

    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("%s rolou: %d\n", atacante->nome, dadoAtq);
    printf("%s rolou: %d\n", defensor->nome, dadoDef);

    if (dadoAtq > dadoDef) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;
        if (defensor->tropas <= 0) {
            printf("O territorio %s agora pertence ao exercito %s!\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2;
            atacante->tropas /= 2;
        }
    } else {
        printf("O ataque falhou! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;
    }
}

// Função para sortear e atribuir missão
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

// Função para verificar missão (exemplo: destruir exercito verde)
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    if (strstr(missao, "Verde")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) {
                return 0; // missão ainda não cumprida
            }
        }
        return 1; // missão cumprida
    }
    return 0;
}

// Liberar memória
void liberarMemoria(struct Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

int main() {
    srand(time(NULL));

    int totalTerritorios;
    printf("Digite o numero de territorios: ");
    scanf("%d", &totalTerritorios);
    limpaBufferEntrada();

    struct Territorio* territorios = calloc(totalTerritorios, sizeof(struct Territorio));

    for (int i = 0; i < totalTerritorios; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        cadastrarTerritorio(&territorios[i]);
    }

    // Lista de missões pré-definidas
    char* missoes[] = {
        "Destruir o exercito Verde.",
        "Destruir o exercito Azul.",
        "Conquistar 3 territorios.",
        "Conquistar 2 territorios do exercito Amarelo.",
        "Eliminar todas as tropas de Oceania."
    };
    int totalMissoes = 5;

    // Missão do jogador (alocada dinamicamente)
    char* minhaMissao = malloc(100 * sizeof(char));
    atribuirMissao(minhaMissao, missoes, totalMissoes);

    printf("\n--- SUA MISSAO ---\n%s\n", minhaMissao);

    int opcao;
    do {
        exibirMapa(territorios, totalTerritorios);
        printf("\n--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limpaBufferEntrada();

        if (opcao == 1) {
            int atq, def;
            printf("Escolha o territorio atacante: ");
            scanf("%d", &atq);
            printf("Escolha o territorio defensor: ");
            scanf("%d", &def);
            limpaBufferEntrada();
            if (atq >= 1 && atq <= totalTerritorios && def >= 1 && def <= totalTerritorios && atq != def) {
                atacar(&territorios[atq - 1], &territorios[def - 1]);
            } else {
                printf("Opcoes invalidas!\n");
            }

            // Verifica missão ao fim do turno
            if (verificarMissao(minhaMissao, territorios, totalTerritorios)) {
                printf("\n*** MISSAO CUMPRIDA! Voce venceu o jogo! ***\n");
                break;
            }

        } else if (opcao == 2) {
            printf("\nSua Missao: %s\n", minhaMissao);
        }

    } while (opcao != 0);

    liberarMemoria(territorios, minhaMissao);
    return 0;
}

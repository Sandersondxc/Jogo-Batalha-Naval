#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5
#define NAVIOS 3

void inicializarTabuleiro(char tabuleiro[TAM][TAM], char simbolo) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = simbolo;
}

void imprimirTabuleiro(char tabuleiro[TAM][TAM], int mostrarNavios) {
    printf("  ");
    for (int i = 0; i < TAM; i++) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            if (!mostrarNavios && tabuleiro[i][j] == 'N')
                printf("~ ");
            else
                printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void posicionarNavios(char tabuleiro[TAM][TAM]) {
    int x, y, naviosColocados = 0;
    while (naviosColocados < NAVIOS) {
        x = rand() % TAM;
        y = rand() % TAM;
        if (tabuleiro[x][y] != 'N') {
            tabuleiro[x][y] = 'N';
            naviosColocados++;
        }
    }
}

int atacar(char tabuleiro[TAM][TAM], int x, int y) {
    if (tabuleiro[x][y] == 'N') {
        tabuleiro[x][y] = 'X';
        return 1;
    } else if (tabuleiro[x][y] == '~') {
        tabuleiro[x][y] = 'O';
    }
    return 0;
}

int contarAcertos(char tabuleiro[TAM][TAM]) {
    int acertos = 0;
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tabuleiro[i][j] == 'X')
                acertos++;
    return acertos;
}

int main() {
    char jogador[TAM][TAM], computador[TAM][TAM];
    int x, y;

    srand(time(NULL));
    inicializarTabuleiro(jogador, '~');
    inicializarTabuleiro(computador, '~');
    posicionarNavios(jogador);
    posicionarNavios(computador);

    printf("=== BATALHA NAVAL ===\n");

    while (1) {
        printf("\nSeu tabuleiro:\n");
        imprimirTabuleiro(jogador, 1);
        printf("\nTabuleiro do computador:\n");
        imprimirTabuleiro(computador, 0);

        printf("\nSua jogada (linha e coluna): ");
        scanf("%d %d", &x, &y);
        if (x < 0 || x >= TAM || y < 0 || y >= TAM) {
            printf("Coordenadas inválidas.\n");
            continue;
        }

        if (computador[x][y] == 'X' || computador[x][y] == 'O') {
            printf("Você já atacou essa posição.\n");
            continue;
        }

        if (atacar(computador, x, y))
            printf("Acertou!\n");
        else
            printf("Errou.\n");

        if (contarAcertos(computador) == NAVIOS) {
            printf("Parabéns! Você venceu!\n");
            break;
        }

        // Jogada do computador
        do {
            x = rand() % TAM;
            y = rand() % TAM;
        } while (jogador[x][y] == 'X' || jogador[x][y] == 'O');

        printf("Computador ataca (%d, %d)... ", x, y);
        if (atacar(jogador, x, y))
            printf("acertou!\n");
        else
            printf("errou.\n");

        if (contarAcertos(jogador) == NAVIOS) {
            printf("O computador venceu.\n");
            break;
        }
    }

    return 0;
}

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int tablePlayer1[4][4], tablePlayer2[4][4];
int bingoNumbers[60];


bool alreadyExists(int table[16], int tableNumber) {
    bool exist = false;
    int count;

    for (count = 0; count < 15; count++) { // Inicio do for
        if(table[count] == tableNumber) {
            exist = true;
        }
    } // Fim do for

    return exist;
}


bool nonRepeat(int randomNumbers[60], int randomNumer) {
    bool repeated = false;
    int count;

    for (count = 0; count < 59; count++) { // Inicio do for
        if(randomNumbers[count] == randomNumer) {
            repeated = true;
        }
    } // Fim do for

    return repeated;
}


int resetNumbers() {
    int i, j;

    for (i = 0; i < 4; i++) { // Inicio do for para zerar as cartelas
        for (j = 0; j < 4; j++) {
            tablePlayer1[i][j] = 0;
            tablePlayer2[i][j] = 0;
        }
    } // Fim do for

    for (i = 0; i < 16; i++) { // Inicio do for para zerar os numeros de sorteio
        bingoNumbers[i] = 0;
    } // Fim do for

    return 0;
}


int generateNumbers() {
    int i, j, count = 0;
    int number;
    int numbersTable1[16], numbersTable2[16];

    srand(time(NULL));

    // For para geração dos numeros da tabela do jogador 1
    for (i = 0; i < 16; i++) {
        number = 1 + rand() % 60;

        while (alreadyExists(numbersTable1, number)) {
            number = 1 + rand() % 60;
        }

        numbersTable1[i] = number;
    } // Fim do for

    // For para geração dos numeros da tabela do jogador 2
    for (i = 0; i < 16; i++) {
        number = 1 + rand() % 60;

        while (alreadyExists(numbersTable2, number)) {
            number = 1 + rand() % 60;
        }
        
        numbersTable2[i] = number;
    } // Fim do for

    // For para preenchimento dos valores para numeros de sorteio
    for (i = 0; i < 60; i++) {
        number = 1 + rand() % 60;

        while (nonRepeat(bingoNumbers, number)){
            number = 1 + rand() % 60;
        }

        bingoNumbers[i] = number;
    } // Fim do for

    // For para preenchimento das matrizes de ambos jogadores
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++){
            tablePlayer1[i][j] = numbersTable1[count];
            tablePlayer2[i][j] = numbersTable2[count];

            count++;
        }
    } // Fim do preenchimento das matrizes

    return 0;
}


int main() {
    resetNumbers();
    generateNumbers();
    
    // Declaração das variaveis de controle e do contador
    char proceed;
    int winner;
    int i, j, count = 0;
    int pointPlayer1 = 0, pointPlayer2 = 0;

    // Exibição dos valores da tabela dos dois jogadores

    printf("\tCartelas dos Jogadores\t\n");

    printf("\n----    Jogador 1    ----\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d\t", tablePlayer1[i][j]);
        }
        printf("\n");
    }


    printf("\n----    Jogador 2    ----\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d\t", tablePlayer2[i][j]);
        }
        printf("\n");
    }

    printf("\nAperta qualquer tecla para continuar...");
    scanf("%c", &proceed);
    system("clear");
    // Fim da exibição dos valores das tabelas dos jogadores

    while (pointPlayer1 <= 16 || pointPlayer2 <= 16) {
        printf("Numero sorteado: %d\n", bingoNumbers[count]);

        // For para contagem de pontos
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (tablePlayer1[i][j] == bingoNumbers[count]) {
                    pointPlayer1++;
                }
                
                if (tablePlayer2[i][j] == bingoNumbers[count]) {
                    pointPlayer2++;
                }
            }
        } // Fim do for de contagem de pontos

        // Exibição das tabelas, pontuação e da rodada
        printf("\n----    Jogador 1    ----\n");
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                printf("%d\t", tablePlayer1[i][j]);
            }
            printf("\n");
        }
        printf("\n\nPontos: %d", pointPlayer1);

        printf("\n\n_____________________________\n");

        printf("\n----    Jogador 2    ----\n");
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                printf("%d\t", tablePlayer2[i][j]);
            }
            printf("\n");
        }
        printf("\n\nPontos: %d", pointPlayer2);

        printf("\n\n_____________________________\n");

        printf("\n\nRodada numero: %d", count+1);
        //For para exibição dos numeros sorteados até o momento
        printf("\nOs numeros sorteados foram: ");
        for (i = 0; i < count; i++) {
            printf("%d ", bingoNumbers[i]);
        }// Fim do for
        
        count++;
        
        printf("\nAperte qualquer tecla para continuar...");
        scanf("%c", &proceed);
        // Fim da exibição das tabelas, pontuação e rodadas


        // Veficação se algum dos jogadores marcou toda a tabela
        if (pointPlayer1 == 16) {
            winner = 1;
            system("clear");
            break;
        }

        if (pointPlayer2 == 16) {
            winner = 2;
            system("clear");
            break;
        }
        // Fim da verificação

        system("clear");
    }


    // Exibição do vencedor, de sua tabela e de todos os numero sorteados ate a rodada final
    printf("\nO vencedor foi o Jogador %d \n", winner);
    printf("\nA tabela do Jogador: \n");
    if (winner == 1) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                printf("%d\t", tablePlayer1[i][j]);
            }
            printf("\n");
        }
    } else if (winner == 2) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                printf("%d\t", tablePlayer2[i][j]);
            }
            printf("\n");
        }
    }

    printf("\nOs numeros sorteados em cada rodada foram: \n");
    for (i = 0; i < count; i++) {
        printf("Rodada %d: %d\n", i+1, bingoNumbers[i]);
    }
    // Fim da exibição

    return 0;
}
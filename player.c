#include "game.h"
#include "player.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool is_symbol_unique(Player *players, int num_players, char symbol) {
    for (int i = 0; i < num_players; i++) {
        if (players[i].symbol == symbol) {
            return false;
        }
    }
    return true;
}

void setup_players(Player players[], int *num_players, char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < *num_players; i++) {
        printf("Entrez le nom du joueur %d : ", i + 1);
        scanf("%s", players[i].name);

        
        do {
            printf("Choisissez un symbole pour le joueur %s (par exemple @, #, $, &) : ", players[i].name);
            scanf(" %c", &players[i].symbol);
            int symbol_used = 0;
            for (int j = 0; j < i; j++) {
                if (players[j].symbol == players[i].symbol) {
                    symbol_used = 1;
                    printf("Ce symbole est déjà utilisé par un autre joueur. Veuillez en choisir un autre.\n");
                    break;
                }
            }
            if (!symbol_used) break;
        } while (1);

        do {
            printf("Le joueur %s est-il un humain (1) ou une IA (0) ? ", players[i].name);
            scanf("%d", &players[i].is_human);
        } while (players[i].is_human != 0 && players[i].is_human != 1);

        if (i == 0) {
            players[i].x = 0;           
            players[i].y = BOARD_SIZE / 2;
        } else if (i == 1) {
            players[i].x = BOARD_SIZE - 1; 
            players[i].y = BOARD_SIZE / 2;
        } else if (i == 2) {
            players[i].x = BOARD_SIZE / 2; 
            players[i].y = 0;
        } else if (i == 3) {
            players[i].x = BOARD_SIZE / 2; 
            players[i].y = BOARD_SIZE - 1;
        }

        board[players[i].x][players[i].y] = players[i].symbol;
    }
}

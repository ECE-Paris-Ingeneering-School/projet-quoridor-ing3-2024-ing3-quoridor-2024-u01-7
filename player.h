#ifndef PLAYER_H
#define PLAYER_H

#include "game.h" 

typedef struct {
    char name[20];
    char symbol;
    int x, y;
    int barriers;
    int is_human;
} Player;

void setup_players(Player players[], int *num_players, char board[BOARD_SIZE][BOARD_SIZE]); 

#endif

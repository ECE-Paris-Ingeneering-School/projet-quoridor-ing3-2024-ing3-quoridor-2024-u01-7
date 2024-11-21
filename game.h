#ifndef GAME_H
#define GAME_H

#include "player.h"

#define BOARD_SIZE 9

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
    Player players[4];
    int num_players;
} Game;

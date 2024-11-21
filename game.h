#ifndef GAME_H
#define GAME_H

#include "player.h"

#define BOARD_SIZE 9

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
    Player players[4];
    int num_players;
} Game;

int is_valid_barrier_placement(Game *game, int row, int col);
void gotoligcol(int lig, int col);
void setup_board(char board[BOARD_SIZE][BOARD_SIZE]);
void setup_players(Player players[], int *num_players, char board[BOARD_SIZE][BOARD_SIZE]);
void init_game(Game *game);
void start_game(Game *game);
int quit_game(Game *game);  // Ajoutez ceci si absent

#endif

#include "game.h"
#include "player.h"
#include "display.h"
#include "save.h"
#include <stdio.h>
#include <windows.h>

void gotoligcol(int lig, int col) {
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

void setup_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '.';  
        }
    }
    
}

void init_game(Game *game) {
    setup_board(game->board); 
    setup_players(game->players, &game->num_players, game->board); 
}

int is_valid_move(Game *game, int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && game->board[x][y] == '.';
}

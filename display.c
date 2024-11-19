#include "game.h"
#include "player.h"
#include "display.h"
#include <stdio.h>

void set_text_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void display_colored_token(char token, int color) {
    set_text_color(color);
    printf("%c", token);
    set_text_color(15); 
}

void display_board(Game *game) {
    printf("\nPlateau de jeu:\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", game->board[i][j]);
        }
        printf("\n");
    }

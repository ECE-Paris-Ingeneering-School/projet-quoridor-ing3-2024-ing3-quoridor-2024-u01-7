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

    printf("\nRecapitulatif des joueurs:\n");
    for (int i = 0; i < game->num_players; i++) {
        printf("Joueur %d (%s): Barrieres: %d, %s\n", i + 1, game->players[i].name, game->players[i].barriers, game->players[i].is_human ? "Humain" : "IA");
    }
}

int getMouseClickPosition(int *row, int *col) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, prev_mode | ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

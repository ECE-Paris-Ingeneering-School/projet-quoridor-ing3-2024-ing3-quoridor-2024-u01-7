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

int is_valid_barrier_placement(Game *game, int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return 0; 
    }

    if (game->board[row][col] != '.') {
        return 0; 
    }
    return 1; 
}

void move_pawn_with_click(Game *game, int player_index) {
    int row, col;
    printf("Cliquez sur la grille pour déplacer le pion de %s.\n", game->players[player_index].name);
    if (getMouseClickPosition(&row, &col)) {
        if (is_valid_move(game, row, col)) {
            game->board[game->players[player_index].x][game->players[player_index].y] = '.';
            game->players[player_index].x = row;
            game->players[player_index].y = col;
            game->board[row][col] = game->players[player_index].symbol;
            display_board(game);  
        } else {
            printf("Mouvement invalide ! Veuillez réessayer.\n");
        }
    }
}

void place_barrier_with_click(Game *game, int player_index) {
    int row, col;
    printf("Cliquez sur la grille pour placer une barrière pour %s.\n", game->players[player_index].name);

    if (getMouseClickPosition(&row, &col)) {
        if (is_valid_barrier_placement(game, row, col)) {
            game->board[row][col] = '|';  
            display_board(game);  
        } else {
            printf("Position de barrière invalide ! Veuillez réessayer.\n");
        }
    }
}

void start_game(Game *game) {
    int running = 1;
    int current_player = 0;

    while (running) {
        display_board(game);  

        printf("\nTour de %s :\n", game->players[current_player].name);
        printf("Choisissez une action :\n");
        printf("1. Déplacer le pion\n");
        printf("2. Placer une barrière\n");
        printf("3. Quitter le jeu\n");
        printf("Votre choix : ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                move_pawn_with_click(game, current_player);
                break;
            case 2:
                place_barrier_with_click(game, current_player);
                break;
            case 3:
                running = !quit_game(game);
                break;
            default:
                printf("Option invalide, veuillez réessayer.\n");
        }

        if (choice == 1 || choice == 2) {
            current_player = (current_player + 1) % game->num_players;
        }
    }
}

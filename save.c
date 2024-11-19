#include "save.h"
#include <stdio.h>

void save_game(Game *game) {
    FILE *f = fopen("sauvegarde.txt", "w");
    if (f == NULL) {
        printf("Erreur lors de la sauvegarde.\n");
        return;
    }

    fprintf(f, "%d\n", game->num_players);
    for (int i = 0; i < game->num_players; i++) {
        fprintf(f, "%s %d %d %d %d\n", game->players[i].name, game->players[i].x, game->players[i].y, game->players[i].barriers, game->players[i].is_human);
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            fprintf(f, "%c", game->board[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Partie sauvegardée avec succès.\n");
}

int load_game(Game *game) {
    FILE *f = fopen("sauvegarde.txt", "r");
    if (f == NULL) {
        printf("Aucune partie sauvegardée trouvée.\n");
        return 0;
    }

    fscanf(f, "%d\n", &game->num_players);
    for (int i = 0; i < game->num_players; i++) {
        fscanf(f, "%s %d %d %d %d\n", game->players[i].name, &game->players[i].x, &game->players[i].y, &game->players[i].barriers, &game->players[i].is_human);
        game->players[i].symbol = '1' + i;
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            fscanf(f, " %c", &game->board[i][j]);
        }
    }

    fclose(f);
    printf("Partie chargée avec succès.\n");
    return 1;
}

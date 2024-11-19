#include "game.h"
#include "player.h"
#include "menu.h"
#include "save.h"
#include <stdio.h>
#include <stdlib.h>

void main_menu(Game *game) {
    int choice;
    do {
        system("cls");
        printf("=== Menu Principal ===\n");
        printf("1. Lancer une nouvelle partie\n");
        printf("2. Reprendre une partie sauvegardee\n");
        printf("3. Afficher l'aide (non disponible)\n");
        printf("4. Afficher les scores (non disponible)\n");
        printf("5. Quitter le jeu\n");
        printf("Choisissez une option: ");
        scanf("%d", &choice);

    }

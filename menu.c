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

switch (choice) {
            case 1:
                init_game(game);
                return;
            case 2:
                if (!load_game(game)) {
                    system("pause");
                }
                return;
            case 3:
            case 4:
                printf("Option non disponible.\n");
                system("pause");
                break;
            case 5:
                printf("Quitter le jeu.\n");
                exit(0);
            default:
                printf("Option invalide, veuillez reessayer.\n");
                system("pause");
        }
    } while (choice != 1 && choice != 2);
}

int quit_game(Game *game) {
    char save_choice;
    printf("Voulez-vous sauvegarder la partie avant de quitter ? (y/n) : ");
    scanf(" %c", &save_choice);

    if (save_choice == 'y' || save_choice == 'Y') {
        save_game(game);  // Sauvegarde de la partie
    }

    printf("Retour au menu principal.\n");
    return 1;  // Retourne 1 pour indiquer que la partie est terminée
}

#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

#include "jeu.h"

void afficherMenu() {
    int choix;
    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Nouvelle Partie\n");
        printf("2. Reprendre Partie\n");
        printf("3. Afficher Aide\n");
        printf("4. Sauvegarder Partie\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                nouvellePartie(); // Appelle la nouvelle partie
                break;
            case 2:
                printf("Reprendre partie : fonctionnalité en cours de développement.\n");
                break;
            case 3:
                afficherAide();
                break;
            case 4:
                printf("Sauvegarder partie : fonctionnalité en cours de développement.\n");
                break;
            case 5:
                printf("Merci d'avoir joué ! À bientôt !\n");
                exit(0);
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    } while (choix != 5);
}


void afficherAide() {
    printf("\n--- Aide ---\n");
    printf("Le jeu Quoridor est un jeu de strategie où le but est d'atteindre le bord oppose du plateau.\n");
    printf("Vous pouvez vous deplacer ou placer des barrieres pour ralentir vos adversaires.\n");
}

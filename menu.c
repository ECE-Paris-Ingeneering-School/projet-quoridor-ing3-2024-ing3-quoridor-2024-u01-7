#include <stdio.h>
#include <stdlib.h>
#include "ia.h"
#include "sauvegarde.h"
#include "menu.h"
#include "joueurs.h"

#include "jeu.h"

void afficherMenu(int niveauIA) {
    int choix;
    char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
    Joueur joueurs[NB_MAX_JOUEURS];
    int nbJoueurs = 0, joueurActuel = 0;

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
                if (chargerPartie("sauvegarde.txt", plateau, joueurs, &nbJoueurs, &joueurActuel)) {
                    jeu(plateau, joueurs, nbJoueurs, niveauIA);
                }
                break;
            case 3:
                afficherAide();
                break;
            case 4:
                sauvegarderPartie("sauvegarde.txt", plateau, joueurs, nbJoueurs, joueurActuel);
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

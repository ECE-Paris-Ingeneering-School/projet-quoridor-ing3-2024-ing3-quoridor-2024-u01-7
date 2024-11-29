#include <stdio.h>
#include "jeu.h"
#include "plateau.h"
#include "joueurs.h"
#include "barrieres.h"

void jeu(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nbJoueurs) {
    int joueurActuel = 0;
    int choixAction;
    char direction;

    while (1) {
        // Afficher les informations des joueurs une seule fois par tour
        printf("\n--- Informations des joueurs ---\n");
        for (int i = 0; i < nbJoueurs; i++) {
            printf("Joueur %d : %s (%c) - Type : %s - Barrieres restantes : %d\n",
                   i + 1, joueurs[i].nom, joueurs[i].symbole,
                   joueurs[i].estIA ? "IA" : "Humain",
                   joueurs[i].nbBarrieres);
        }

        // Afficher le tour actuel et le plateau
        printf("\n--- Tour de %s (%c) ---\n", joueurs[joueurActuel].nom, joueurs[joueurActuel].symbole);
        afficherPlateau(plateau, joueurs, nbJoueurs);

        // Choisir une action
        do {
            printf("1. Se déplacer\n");
            printf("2. Placer une barrière\n");
            printf("Choisissez une action : ");
            scanf("%d", &choixAction);

            if (choixAction != 1 && choixAction != 2) {
                printf("Erreur : Action invalide. Choisissez 1 ou 2.\n");
            }
        } while (choixAction != 1 && choixAction != 2);

        if (choixAction == 1) {
            // Déplacement
            do {
                printf("Direction (z = haut, s = bas, q = gauche, d = droite) : ");
                scanf(" %c", &direction);
                if (deplacerPion(&joueurs[joueurActuel], direction, plateau)) {
                    break; // Déplacement réussi
                }
            } while (1);
        } else if (choixAction == 2) {
            // **Placement de barrière**
            if (joueurs[joueurActuel].nbBarrieres > 0) {
                int barrierePlacee = 0;
                char case1[3], case2[3], position; // Déclaration des variables nécessaires
                do {
                    printf("Entrez les deux cases voisines et la position (ex : D1 D2 G) : ");
                    scanf("%s %s %c", case1, case2, &position);
                    if (placerBarriere(plateau, case1, case2, position)) {
                        joueurs[joueurActuel].nbBarrieres--; // Réduction des barrières disponibles
                        barrierePlacee = 1;                // Barrière placée avec succès
                    } else {
                        printf("Erreur : Placement invalide. Essayez encore.\n");
                    }
                } while (!barrierePlacee);
            } else {
                printf("Erreur : Vous n'avez plus de barrières disponibles.\n");
            }
        }

        // Passer au joueur suivant
        joueurActuel = (joueurActuel + 1) % nbJoueurs;
    }
}

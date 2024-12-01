#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "plateau.h"

void initialiserPlateau(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            plateau[i][j] = '.'; // Case vide
        }
    }
}

void afficherPlateau(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nbJoueurs) {
    printf("\n--- Plateau de jeu ---\n");
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            int estJoueur = 0;
            for (int k = 0; k < nbJoueurs; k++) {
                if (joueurs[k].x == i && joueurs[k].y == j) {
                    printf("%c ", joueurs[k].symbole);
                    estJoueur = 1;
                    break;
                }
            }
            if (!estJoueur) {
                printf("%c ", plateau[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n--- Informations des joueurs ---\n");
    for (int i = 0; i < nbJoueurs; i++) {
        printf("Joueur %d : %s (%c) - Barrieres restantes : %d\n",
               i + 1, joueurs[i].nom, joueurs[i].symbole, joueurs[i].nbBarrieres);
    }
}

void placerJoueursSurPlateau(Joueur joueurs[], int nbJoueurs, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    // Réinitialiser le plateau avec des cases vides
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            plateau[i][j] = '.'; // Case vide
        }
    }

    // Placer les joueurs en fonction du nombre de joueurs
    if (nbJoueurs == 2) {
        // Joueur 1 commence en bas-centre
        joueurs[0].x = TAILLE_PLATEAU - 1;
        joueurs[0].y = TAILLE_PLATEAU / 2;
        joueurs[0].directionCible = 'H'; // Objectif : haut
        joueurs[0].ligneCible = 0;

        // Joueur 2 commence en haut-centre
        joueurs[1].x = 0;
        joueurs[1].y = TAILLE_PLATEAU / 2;
        joueurs[1].directionCible = 'B'; // Objectif : bas
        joueurs[1].ligneCible = TAILLE_PLATEAU - 1;

        plateau[joueurs[0].x][joueurs[0].y] = joueurs[0].symbole;
        plateau[joueurs[1].x][joueurs[1].y] = joueurs[1].symbole;

        printf("Débogage : Joueur 1 (%c) placé en (%d, %d).\n", joueurs[0].symbole, joueurs[0].x, joueurs[0].y);
        printf("Débogage : Joueur 2 (%c) placé en (%d, %d).\n", joueurs[1].symbole, joueurs[1].x, joueurs[1].y);

    } else if (nbJoueurs == 4) {
        // Joueur 1 commence en bas-centre
        joueurs[0].x = TAILLE_PLATEAU - 1;
        joueurs[0].y = TAILLE_PLATEAU / 2;
        joueurs[0].directionCible = 'H'; // Objectif : haut
        joueurs[0].ligneCible = 0;

        // Joueur 2 commence en haut-centre
        joueurs[1].x = 0;
        joueurs[1].y = TAILLE_PLATEAU / 2;
        joueurs[1].directionCible = 'B'; // Objectif : bas
        joueurs[1].ligneCible = TAILLE_PLATEAU - 1;

        // Joueur 3 commence en milieu-gauche
        joueurs[2].x = TAILLE_PLATEAU / 2;
        joueurs[2].y = 0;
        joueurs[2].directionCible = 'D'; // Objectif : droite
        joueurs[2].ligneCible = TAILLE_PLATEAU - 1;

        // Joueur 4 commence en milieu-droit
        joueurs[3].x = TAILLE_PLATEAU / 2;
        joueurs[3].y = TAILLE_PLATEAU - 1;
        joueurs[3].directionCible = 'G'; // Objectif : gauche
        joueurs[3].ligneCible = 0;

        for (int i = 0; i < nbJoueurs; i++) {
            plateau[joueurs[i].x][joueurs[i].y] = joueurs[i].symbole;
            printf("Débogage : Joueur %d (%c) placé en (%d, %d).\n", i + 1, joueurs[i].symbole, joueurs[i].x, joueurs[i].y);
        }
    } else {
        printf("Erreur : Nombre de joueurs non supporté.\n");
        exit(1); // Terminer le programme
    }
}




void afficherInfosJoueurs(Joueur joueurs[], int nbJoueurs) {
    printf("\n--- Informations des joueurs ---\n");
    for (int i = 0; i < nbJoueurs; i++) {
        printf("Joueur %d : %s (%c) - Type : %s - Barrieres restantes : %d\n",
               i + 1, joueurs[i].nom, joueurs[i].symbole,
               joueurs[i].estIA ? "IA" : "Humain",
               joueurs[i].nbBarrieres);
    }
}

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
    for (int i = 0; i < nbJoueurs; i++) {
        plateau[joueurs[i].x][joueurs[i].y] = joueurs[i].symbole;
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

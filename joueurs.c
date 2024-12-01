#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "joueurs.h"

int symboleEstUnique(char symbole, Joueur joueurs[], int nbJoueurs) {
    for (int i = 0; i < nbJoueurs; i++) {
        if (joueurs[i].symbole == symbole) {
            return 0; // Symbole déjà utilisé
        }
    }
    return 1; // Symbole est unique
}

void initialiserJoueurs(Joueur joueurs[], int nbJoueurs) {
    for (int i = 0; i < nbJoueurs; i++) {
        printf("\n--- Joueur %d ---\n", i + 1);

        // Saisie des informations du joueur
        int estIA;
        do {
            printf("Le joueur est-il une IA ? (1 = Oui, 0 = Non) : ");
            if (scanf("%d", &estIA) == 1 && (estIA == 0 || estIA == 1)) {
                joueurs[i].estIA = estIA;
                break;
            } else {
                printf("Erreur : Veuillez entrer 1 pour IA ou 0 pour Humain.\n");
                while (getchar() != '\n'); // Vider le buffer
            }
        } while (1);

        if (!joueurs[i].estIA) {
            printf("Nom du joueur : ");
            scanf("%s", joueurs[i].nom);
        } else {
            sprintf(joueurs[i].nom, "IA_%d", i + 1);
        }

        // Saisie d'un symbole unique
        char symbole;
        do {
            printf("Symbole (@, #, $, &) : ");
            scanf(" %c", &symbole);

            if (strchr("@#$&", symbole) && symboleEstUnique(symbole, joueurs, i)) {
                joueurs[i].symbole = symbole;
                break;
            } else if (!strchr("@#$&", symbole)) {
                printf("Erreur : Symbole invalide. Choisissez parmi @, #, $, &.\n");
            } else {
                printf("Erreur : Ce symbole est déjà utilisé. Essayez un autre.\n");
            }
        } while (1);

        // Configuration du placement initial et de la cible
        if (i == 0) { // Joueur 1
            joueurs[i].x = 0;                       // Ligne du haut
            joueurs[i].y = TAILLE_PLATEAU / 2;      // Centré horizontalement
            joueurs[i].directionCible = 'B';       // Objectif : bas
            joueurs[i].ligneCible = TAILLE_PLATEAU - 1; // Ligne du bas
        } else if (i == 1) { // Joueur 2
            joueurs[i].x = TAILLE_PLATEAU - 1;      // Ligne du bas
            joueurs[i].y = TAILLE_PLATEAU / 2;      // Centré horizontalement
            joueurs[i].directionCible = 'H';       // Objectif : haut
            joueurs[i].ligneCible = 0;             // Ligne du haut
        } else if (i == 2) { // Joueur 3
            joueurs[i].x = TAILLE_PLATEAU / 2;      // Centré verticalement
            joueurs[i].y = 0;                       // Colonne de gauche
            joueurs[i].directionCible = 'D';       // Objectif : droite
            joueurs[i].ligneCible = TAILLE_PLATEAU - 1; // Colonne de droite
        } else if (i == 3) { // Joueur 4
            joueurs[i].x = TAILLE_PLATEAU / 2;      // Centré verticalement
            joueurs[i].y = TAILLE_PLATEAU - 1;      // Colonne de droite
            joueurs[i].directionCible = 'G';       // Objectif : gauche
            joueurs[i].ligneCible = 0;             // Colonne de gauche
        } else {
            printf("Erreur : Nombre de joueurs invalide.\n");
            exit(1);
        }

        // Vérification après placement
        if ((joueurs[i].directionCible == 'B' && joueurs[i].x != 0) || // Doit commencer en haut
            (joueurs[i].directionCible == 'H' && joueurs[i].x != TAILLE_PLATEAU - 1) || // Doit commencer en bas
            (joueurs[i].directionCible == 'D' && joueurs[i].y != 0) || // Doit commencer à gauche
            (joueurs[i].directionCible == 'G' && joueurs[i].y != TAILLE_PLATEAU - 1)) { // Doit commencer à droite
            printf("Erreur : %s (%c) n'est pas correctement place sur la ligne de depart.\n", joueurs[i].nom, joueurs[i].symbole);
            exit(1);
        }

        joueurs[i].nbBarrieres = (nbJoueurs == 2) ? NB_BARRIERES_2J : NB_BARRIERES_4J;
    }
}






int deplacerPion(Joueur *joueur, char direction, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    // Coordonnées temporaires pour calculer le déplacement
    int newX = joueur->x;
    int newY = joueur->y;

    // Calcul de la nouvelle position en fonction de la direction
    switch (direction) {
        case 'z': newX--; break; // Haut
        case 's': newX++; break; // Bas
        case 'q': newY--; break; // Gauche
        case 'd': newY++; break; // Droite
        default:
            printf("Erreur : Direction invalide. Utilisez z (haut), s (bas), q (gauche), d (droite).\n");
            return 0; // Déplacement invalide
    }

    // Vérification des limites du plateau
    if (newX < 0 || newX >= TAILLE_PLATEAU || newY < 0 || newY >= TAILLE_PLATEAU) {
        printf("Erreur : Déplacement hors limites. Essayez encore.\n");
        return 0;
    }

    // Vérification si la case est libre ou si une barrière bloque le passage
    if (plateau[newX][newY] != '.') {
        if (plateau[newX][newY] == 'B') {
            printf("Erreur : Une barrière bloque le passage vers (%d, %d).\n", newX, newY);
        } else {
            printf("Erreur : La case (%d, %d) est occupée par '%c'.\n", newX, newY, plateau[newX][newY]);
        }
        return 0;
    }

    // Mise à jour du plateau et des coordonnées du joueur
    printf("Deplacement reussi de (%d, %d) à (%d, %d).\n", joueur->x, joueur->y, newX, newY);
    plateau[joueur->x][joueur->y] = '.';     // Efface l'ancienne position
    joueur->x = newX;                        // Met à jour la nouvelle coordonnée X
    joueur->y = newY;                        // Met à jour la nouvelle coordonnée Y
    plateau[newX][newY] = joueur->symbole;   // Place le symbole du joueur sur la nouvelle position

    return 1; // Déplacement réussi
}

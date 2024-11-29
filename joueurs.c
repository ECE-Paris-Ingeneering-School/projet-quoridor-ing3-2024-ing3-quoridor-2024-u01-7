#include <stdio.h>
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

        // Saisie du type de joueur (IA ou Humain)
        int valide = 0; // Indique si la saisie est valide
        while (!valide) {
            printf("Le joueur est-il une IA ? (1 = Oui, 0 = Non) : ");
            if (scanf("%d", &joueurs[i].estIA) == 1 && (joueurs[i].estIA == 0 || joueurs[i].estIA == 1)) {
                valide = 1; // Saisie correcte
            } else {
                printf("Erreur : Veuillez entrer 1 pour IA ou 0 pour Humain.\n");
                while (getchar() != '\n'); // Vide le buffer
            }
        }

        // Saisie du nom
        if (!joueurs[i].estIA) {
            do {
                printf("Nom du joueur : ");
                scanf("%s", joueurs[i].nom);
            } while (strlen(joueurs[i].nom) == 0);
        } else {
            sprintf(joueurs[i].nom, "IA_%d", i + 1); // Nom automatique pour une IA
        }

        // Saisie d'un symbole unique
        do {
            printf("Symbole (@, #, $, &) : ");
            scanf(" %c", &joueurs[i].symbole);
            if (!strchr("@#$&", joueurs[i].symbole)) {
                printf("Erreur : Symbole invalide. Choisissez parmi @, #, $, &.\n");
            } else if (!symboleEstUnique(joueurs[i].symbole, joueurs, i)) {
                printf("Erreur : Ce symbole est déjà utilisé. Essayez un autre.\n");
            }
        } while (!strchr("@#$&", joueurs[i].symbole) || !symboleEstUnique(joueurs[i].symbole, joueurs, i));

        // Position initiale
        joueurs[i].x = (i == 0) ? 0 : TAILLE_PLATEAU - 1;
        joueurs[i].y = TAILLE_PLATEAU / 2;

        // Initialisation des barrières
        joueurs[i].nbBarrieres = (nbJoueurs == 2) ? NB_BARRIERES_2J : NB_BARRIERES_4J;
    }
}




int deplacerPion(Joueur *joueur, char direction, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    int newX = joueur->x;
    int newY = joueur->y;

    // Calcul de la nouvelle position
    switch (direction) {
        case 'z': newX--; break; // Haut
        case 's': newX++; break; // Bas
        case 'q': newY--; break; // Gauche
        case 'd': newY++; break; // Droite
        default:
            printf("Erreur : Direction invalide. Utilisez z (haut), s (bas), q (gauche), d (droite).\n");
            return 0;
    }

    // Vérification des limites du plateau
    if (newX < 0 || newX >= TAILLE_PLATEAU || newY < 0 || newY >= TAILLE_PLATEAU) {
        printf("Erreur : Déplacement hors limites.\n");
        return 0;
    }

    // Vérification si la case est libre
    if (plateau[newX][newY] != '.') {
        printf("Erreur : La case est occupée.\n");
        return 0;
    }

    // Déplacement validé : mettre à jour la position
    plateau[joueur->x][joueur->y] = '.'; // Efface l'ancienne position
    joueur->x = newX;
    joueur->y = newY;
    plateau[newX][newY] = joueur->symbole; // Met à jour la nouvelle position

    return 1;
}

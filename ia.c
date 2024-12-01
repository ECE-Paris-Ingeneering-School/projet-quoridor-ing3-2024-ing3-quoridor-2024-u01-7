#include <stdio.h>
#include <stdlib.h>
#include "ia.h"
#include "plateau.h"
#include "joueurs.h"
#include "barrieres.h"
#include <limits.h>


void jouerIAFacile(Joueur *joueur, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    if (rand() % 2 == 0 && joueur->nbBarrieres > 0) {
        // Essayons de placer une barrière aléatoire
        char case1[3], case2[3], position;
        do {
            sprintf(case1, "%c%d", 'A' + (rand() % TAILLE_PLATEAU), 1 + (rand() % TAILLE_PLATEAU));
            sprintf(case2, "%c%d", 'A' + (rand() % TAILLE_PLATEAU), 1 + (rand() % TAILLE_PLATEAU));
            position = "GDSB"[rand() % 4]; // Aléatoire parmi Gauche, Droite, Haut, Bas
        } while (!placerBarriere(plateau, case1, case2, position));
        joueur->nbBarrieres--;
    } else {
        // Déplacement aléatoire
        char directions[] = {'z', 's', 'q', 'd'};
        char direction;
        do {
            direction = directions[rand() % 4];
        } while (!deplacerPion(joueur, direction, plateau));
    }
}

void jouerIAMoyen(Joueur *joueur, Joueur joueurs[], int nbJoueurs, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    for (int i = 0; i < nbJoueurs; i++) {
        if (joueurs[i].symbole != joueur->symbole) {
            // Trouvons les coordonnées approximatives pour bloquer l'adversaire
            int targetX = joueurs[i].x + (joueurs[i].x < TAILLE_PLATEAU / 2 ? 1 : -1);
            int targetY = joueurs[i].y;

            // Tentons de placer une barrière autour de cet endroit
            char case1[3], case2[3], position = 'G'; // Exemple pour Gauche
            sprintf(case1, "%c%d", 'A' + targetY, 1 + targetX);
            sprintf(case2, "%c%d", 'A' + targetY, 1 + targetX + 1);

            if (placerBarriere(plateau, case1, case2, position)) {
                joueur->nbBarrieres--;
                return;
            }
        }
    }

    // Si aucune barrière valide, se déplacer vers l'objectif
    jouerIAFacile(joueur, plateau); // Repli sur un comportement simple
}

int astar(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int startX, int startY, int goalX) {
    // Implémentation simplifiée d'un algorithme A*.
    // Calculer le chemin optimal. Retourne la distance ou une valeur élevée si impossible.
    // Ajoute ici un algorithme réaliste basé sur les cases adjacentes et les barrières.
    return 0; // Placeholder pour une implémentation complète
}

void jouerIADifficile(Joueur *joueur, Joueur joueurs[], int nbJoueurs, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    int chemin = astar(plateau, joueur->x, joueur->y, (joueur->x == 0) ? TAILLE_PLATEAU - 1 : 0);

    if (chemin < INT_MAX) {
        // Utilise A* pour bouger ou placer une barrière
        jouerIAMoyen(joueur, joueurs, nbJoueurs, plateau); // Approche mixte
    } else {
        jouerIAFacile(joueur, plateau); // Si aucun chemin, fallback
    }
}

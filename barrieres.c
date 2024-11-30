#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "barrieres.h"

int coordonneesDepuisCase(char *caseStr, int *x, int *y) {
    if (strlen(caseStr) != 2) return 0;
    char colonne = toupper(caseStr[0]);
    char ligne = caseStr[1];

    if (colonne < 'A' || colonne > 'I' || ligne < '1' || ligne > '9') return 0;

    *x = ligne - '1';   
    *y = colonne - 'A'; 
    return 1;          
}




int placerBarriere(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char case1[], char case2[], char position) {
    int x1, y1, x2, y2;

    if (!coordonneesDepuisCase(case1, &x1, &y1) || !coordonneesDepuisCase(case2, &x2, &y2)) {
        printf("Erreur : Coordonnées invalides.\n");
        return 0;
    }


    if (!((x1 == x2 && abs(y1 - y2) == 1) || (y1 == y2 && abs(x1 - x2) == 1))) {
        printf("Erreur : Les cases ne sont pas voisines.\n");
        return 0;
    }


    position = toupper(position); 
    if (position == 'H') { 
        if (x1 == 0 || plateau[x1 - 1][y1] == 'B' || plateau[x2 - 1][y2] == 'B') {
            printf("Erreur : Une barrière existe déjà.\n");
            return 0;
        }
        plateau[x1 - 1][y1] = 'B';
        plateau[x2 - 1][y2] = 'B';
    } else if (position == 'B') { 
        if (x1 >= TAILLE_PLATEAU - 1 || plateau[x1 + 1][y1] == 'B' || plateau[x2 + 1][y2] == 'B') {
            printf("Erreur : Une barrière existe déjà.\n");
            return 0;
        }
        plateau[x1 + 1][y1] = 'B';
        plateau[x2 + 1][y2] = 'B';
    } else if (position == 'G') { 
        if (y1 == 0 || plateau[x1][y1 - 1] == 'B' || plateau[x2][y2 - 1] == 'B') {
            printf("Erreur : Une barrière existe déjà.\n");
            return 0;
        }
        plateau[x1][y1 - 1] = 'B';
        plateau[x2][y2 - 1] = 'B';
    } else if (position == 'D') { 
        if (y1 >= TAILLE_PLATEAU - 1 || plateau[x1][y1 + 1] == 'B' || plateau[x2][y2 + 1] == 'B') {
            printf("Erreur : Une barrière existe déjà.\n");
            return 0;
        }
        plateau[x1][y1 + 1] = 'B';
        plateau[x2][y2 + 1] = 'B';
    } else {
        printf("Erreur : Position invalide ou hors limites.\n");
        return 0;
    }

    return 1; 
}

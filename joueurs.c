#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "joueurs.h"

int symboleEstUnique(char symbole, Joueur joueurs[], int nbJoueurs) {
    for (int i = 0; i < nbJoueurs; i++) {
        if (joueurs[i].symbole == symbole) {
            return 0; 
        }
    }
    return 1; 
}

void initialiserJoueurs(Joueur joueurs[], int nbJoueurs) {
    for (int i = 0; i < nbJoueurs; i++) {
        printf("\n--- Joueur %d ---\n", i + 1);


        int valide = 0; 
        while (!valide) {
            printf("Le joueur est-il une IA ? (1 = Oui, 0 = Non) : ");
            if (scanf("%d", &joueurs[i].estIA) == 1 && (joueurs[i].estIA == 0 || joueurs[i].estIA == 1)) {
                valide = 1; 
            } else {
                printf("Erreur : Veuillez entrer 1 pour IA ou 0 pour Humain.\n");
                while (getchar() != '\n'); 
            }
        }


        if (!joueurs[i].estIA) {
            do {
                printf("Nom du joueur : ");
                scanf("%s", joueurs[i].nom);
            } while (strlen(joueurs[i].nom) == 0);
        } else {
            sprintf(joueurs[i].nom, "IA_%d", i + 1); 
        }


        do {
            printf("Symbole (@, #, $, &) : ");
            scanf(" %c", &joueurs[i].symbole);
            if (!strchr("@#$&", joueurs[i].symbole)) {
                printf("Erreur : Symbole invalide. Choisissez parmi @, #, $, &.\n");
            } else if (!symboleEstUnique(joueurs[i].symbole, joueurs, i)) {
                printf("Erreur : Ce symbole est déjà utilisé. Essayez un autre.\n");
            }
        } while (!strchr("@#$&", joueurs[i].symbole) || !symboleEstUnique(joueurs[i].symbole, joueurs, i));


        joueurs[i].x = (i == 0) ? 0 : TAILLE_PLATEAU - 1;
        joueurs[i].y = TAILLE_PLATEAU / 2;


        joueurs[i].nbBarrieres = (nbJoueurs == 2) ? NB_BARRIERES_2J : NB_BARRIERES_4J;
    }
}




int deplacerPion(Joueur *joueur, char direction, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {

    int newX = joueur->x;
    int newY = joueur->y;


    switch (direction) {
        case 'z': newX--; break; 
        case 's': newX++; break; 
        case 'q': newY--; break; 
        case 'd': newY++; break; 
        default:
            printf("Erreur : Direction invalide. Utilisez z (haut), s (bas), q (gauche), d (droite).\n");
            return 0;
    }


    if (newX < 0 || newX >= TAILLE_PLATEAU || newY < 0 || newY >= TAILLE_PLATEAU) {
        printf("Erreur : Deplacement hors limites. Essayez encore.\n");
        return 0;
    }


    if (plateau[newX][newY] != '.') {
        printf("Erreur : La case (%d, %d) est occupee par '%c'.\n", newX, newY, plateau[newX][newY]);
        return 0;
    }


    printf("Deplacement de (%d, %d) à (%d, %d).\n", joueur->x, joueur->y, newX, newY);
    plateau[joueur->x][joueur->y] = '.'; 
    joueur->x = newX;                  
    joueur->y = newY;                  
    plateau[newX][newY] = joueur->symbole; 

    return 1; 
}

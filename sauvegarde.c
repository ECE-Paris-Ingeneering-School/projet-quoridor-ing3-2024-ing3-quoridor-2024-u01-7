#include <stdio.h>
#include "structures.h"
#include "sauvegarde.h"

void sauvegarderPartie(const char *nomFichier, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nbJoueurs, int joueurActuel) {
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur : Impossible de sauvegarder la partie.\n");
        return;
    }


    fprintf(fichier, "%d %d\n", TAILLE_PLATEAU, TAILLE_PLATEAU);


    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            fprintf(fichier, "%c", plateau[i][j]);
        }
        fprintf(fichier, "\n");
    }


    fprintf(fichier, "%d\n", nbJoueurs);


    for (int i = 0; i < nbJoueurs; i++) {
        fprintf(fichier, "%s %c %d %d %d %d\n",
                joueurs[i].nom,
                joueurs[i].symbole,
                joueurs[i].x,
                joueurs[i].y,
                joueurs[i].nbBarrieres,
                joueurs[i].estIA);
    }


    fprintf(fichier, "%d\n", joueurActuel);

    fclose(fichier);
    printf("Partie sauvegardée dans %s.\n", nomFichier);
}

int chargerPartie(const char *nomFichier, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int *nbJoueurs, int *joueurActuel) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible de charger la partie.\n");
        return 0;
    }


    int lignes, colonnes;
    fscanf(fichier, "%d %d\n", &lignes, &colonnes);


    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            fscanf(fichier, " %c", &plateau[i][j]);
        }
    }


    fscanf(fichier, "%d\n", nbJoueurs);


    for (int i = 0; i < *nbJoueurs; i++) {
        fscanf(fichier, "%s %c %d %d %d %d\n",
               joueurs[i].nom,
               &joueurs[i].symbole,
               &joueurs[i].x,
               &joueurs[i].y,
               &joueurs[i].nbBarrieres,
               &joueurs[i].estIA);
    }


    fscanf(fichier, "%d\n", joueurActuel);

    fclose(fichier);
    printf("Partie chargée depuis %s.\n", nomFichier);
    return 1;
}

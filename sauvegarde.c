#include <stdio.h>
#include "structures.h"
#include "sauvegarde.h"

void sauvegarderPartie(const char *nomFichier, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nbJoueurs, int joueurActuel) {
    // Ouvrir le fichier en mode écriture
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        perror("Erreur : Impossible de sauvegarder la partie");
        return;
    }

    // Sauvegarder les dimensions du plateau (facultatif si fixe, mais inclut pour compatibilité future)
    fprintf(fichier, "%d %d\n", TAILLE_PLATEAU, TAILLE_PLATEAU);

    // Sauvegarder l'état du plateau
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            fprintf(fichier, "%c", plateau[i][j]);
        }
        fprintf(fichier, "\n");
    }

    // Sauvegarder le nombre de joueurs
    fprintf(fichier, "%d\n", nbJoueurs);

    // Sauvegarder les informations des joueurs
    for (int i = 0; i < nbJoueurs; i++) {
        fprintf(fichier, "%s %c %d %d %d %c %d\n",
                joueurs[i].nom,           // Nom du joueur
                joueurs[i].symbole,       // Symbole du joueur
                joueurs[i].x,             // Position X
                joueurs[i].y,             // Position Y
                joueurs[i].nbBarrieres,   // Barrières restantes
                joueurs[i].directionCible, // Direction cible (H, B, G, D)
                joueurs[i].ligneCible);    // Ligne ou colonne cible
    }

    // Sauvegarder le joueur actuel
    fprintf(fichier, "%d\n", joueurActuel);

    // Fermer le fichier
    fclose(fichier);
    printf("Partie sauvegardée avec succès dans le fichier '%s'.\n", nomFichier);
}



int chargerPartie(const char *nomFichier, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int *nbJoueurs, int *joueurActuel) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur : Impossible de charger la partie");
        return 0;
    }

    // Charger les dimensions du plateau
    int lignes, colonnes;
    if (fscanf(fichier, "%d %d\n", &lignes, &colonnes) != 2) {
        printf("Erreur : Format incorrect pour les dimensions du plateau.\n");
        fclose(fichier);
        return 0;
    }

    if (lignes != TAILLE_PLATEAU || colonnes != TAILLE_PLATEAU) {
        printf("Erreur : Plateau incompatible avec cette version du jeu.\n");
        fclose(fichier);
        return 0;
    }

    // Charger l'état du plateau
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            fscanf(fichier, " %c", &plateau[i][j]);
        }
    }

    // Charger le nombre de joueurs
    if (fscanf(fichier, "%d\n", nbJoueurs) != 1) {
        printf("Erreur : Format incorrect pour le nombre de joueurs.\n");
        fclose(fichier);
        return 0;
    }

    // Charger les informations des joueurs
    for (int i = 0; i < *nbJoueurs; i++) {
        if (fscanf(fichier, "%s %c %d %d %d %c %d\n",
                   joueurs[i].nom,
                   &joueurs[i].symbole,
                   &joueurs[i].x,
                   &joueurs[i].y,
                   &joueurs[i].nbBarrieres,
                   &joueurs[i].directionCible,
                   &joueurs[i].ligneCible) != 7) {
            printf("Erreur : Format incorrect pour les informations des joueurs.\n");
            fclose(fichier);
            return 0;
        }

        // Ajouter des vérifications après le chargement
        if ((joueurs[i].directionCible == 'H' && joueurs[i].ligneCible != 0) ||
            (joueurs[i].directionCible == 'B' && joueurs[i].ligneCible != TAILLE_PLATEAU - 1) ||
            (joueurs[i].directionCible == 'G' && joueurs[i].ligneCible != 0) ||
            (joueurs[i].directionCible == 'D' && joueurs[i].ligneCible != TAILLE_PLATEAU - 1)) {
            printf("Erreur : Direction ou cible incorrecte pour le joueur %s (%c).\n", joueurs[i].nom, joueurs[i].symbole);
            fclose(fichier);
            return 0;
        }
    }

    // Charger le joueur actuel
    if (fscanf(fichier, "%d\n", joueurActuel) != 1) {
        printf("Erreur : Format incorrect pour le joueur actuel.\n");
        fclose(fichier);
        return 0;
    }

    fclose(fichier);
    printf("Partie chargée depuis %s avec succès.\n", nomFichier);
    return 1;
}



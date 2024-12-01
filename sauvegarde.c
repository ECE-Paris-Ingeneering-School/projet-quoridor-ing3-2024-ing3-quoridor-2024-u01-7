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

    // Sauvegarder les dimensions du plateau
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
        fprintf(fichier, "%s %c %d %d %d %c %d %d\n",
                joueurs[i].nom,            // Nom du joueur
                joueurs[i].symbole,        // Symbole du joueur
                joueurs[i].x,              // Position X
                joueurs[i].y,              // Position Y
                joueurs[i].nbBarrieres,    // Barrières restantes
                joueurs[i].directionCible, // Direction cible (H, B, G, D)
                joueurs[i].ligneCible,     // Ligne ou colonne cible
                joueurs[i].estIA);         // IA ou humain
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
            if (fscanf(fichier, " %c", &plateau[i][j]) != 1) {
                printf("Erreur : Format incorrect pour l'état du plateau.\n");
                fclose(fichier);
                return 0;
            }
        }
    }

    // Charger le nombre de joueurs
    if (fscanf(fichier, "%d\n", nbJoueurs) != 1 || *nbJoueurs < 2 || *nbJoueurs > 4) {
        printf("Erreur : Nombre de joueurs invalide.\n");
        fclose(fichier);
        return 0;
    }

    // Charger les informations des joueurs
    for (int i = 0; i < *nbJoueurs; i++) {
        if (fscanf(fichier, "%s %c %d %d %d %c %d %d\n",
                   joueurs[i].nom,               // Nom
                   &joueurs[i].symbole,          // Symbole
                   &joueurs[i].x,                // Position X
                   &joueurs[i].y,                // Position Y
                   &joueurs[i].nbBarrieres,      // Barrières restantes
                   &joueurs[i].directionCible,   // Direction cible
                   &joueurs[i].ligneCible,       // Ligne cible
                   &joueurs[i].estIA) != 8) {    // IA ou humain
            printf("Erreur : Format incorrect pour les informations des joueurs.\n");
            fclose(fichier);
            return 0;
        }

        // Vérifications des positions et des cibles
        if (joueurs[i].x < 0 || joueurs[i].x >= TAILLE_PLATEAU ||
            joueurs[i].y < 0 || joueurs[i].y >= TAILLE_PLATEAU) {
            printf("Erreur : Position invalide pour le joueur %s (%c).\n", joueurs[i].nom, joueurs[i].symbole);
            fclose(fichier);
            return 0;
        }

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
    if (fscanf(fichier, "%d\n", joueurActuel) != 1 || *joueurActuel < 0 || *joueurActuel >= *nbJoueurs) {
        printf("Erreur : Joueur actuel invalide.\n");
        fclose(fichier);
        return 0;
    }

    fclose(fichier);
    printf("Partie chargée depuis '%s' avec succès.\n", nomFichier);
    return 1;
}




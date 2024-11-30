#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"
#include "plateau.h"
#include "joueurs.h"
#include "jeu.h"

void afficherMenu();

int main() {
    char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
    Joueur joueurs[NB_MAX_JOUEURS];
    int choixMenu;
    int nbJoueurs;

    do {
        afficherMenu();
        printf("Choisissez une option : ");
        scanf("%d", &choixMenu);

        switch (choixMenu) {
            case 1: // Nouvelle Partie
                do {
                    printf("Nombre de joueurs (2 ou 4) : ");
                    scanf("%d", &nbJoueurs);
                    if (nbJoueurs != 2 && nbJoueurs != 4) {
                        printf("Erreur : Vous devez saisir 2 ou 4 joueurs.\n");
                    }
                } while (nbJoueurs != 2 && nbJoueurs != 4);

                // Initialisation du plateau et des joueurs
                initialiserPlateau(plateau);
                initialiserJoueurs(joueurs, nbJoueurs);
                placerJoueursSurPlateau(joueurs, nbJoueurs, plateau);
                afficherInfosJoueurs(joueurs, nbJoueurs);

                // Lancer le jeu
                jeu(plateau, joueurs, nbJoueurs);
                break;

            case 2: // Afficher Aide
                printf("\n--- Aide ---\n");
                printf("Le jeu Quoridor est un jeu de strategie.\n");
                printf("Deplacez votre pion ou placez des barrieres pour atteindre le bord oppose.\n");
                break;

            case 3: // Quitter
                printf("Au revoir !\n");
                return 0;

            default:
                printf("Option invalide. Essayez encore.\n");
        }
    } while (choixMenu != 3);

    return 0;
}


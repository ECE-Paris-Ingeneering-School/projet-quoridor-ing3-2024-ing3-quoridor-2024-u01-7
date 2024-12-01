#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"
#include "plateau.h"
#include "joueurs.h"
#include "jeu.h"
#include "sauvegarde.h"

void afficherMenu();

int main() {
    char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
    Joueur joueurs[NB_MAX_JOUEURS];
    int choixMenu;
    int nbJoueurs;
    int niveauIA = 1; // Niveau d'IA par défaut
    int joueurActuel;

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

                // Configurer le niveau d'IA
                printf("Choisissez le niveau d'IA (1 = Facile, 2 = Moyen, 3 = Difficile) : ");
                scanf("%d", &niveauIA);

                // Initialisation du plateau et des joueurs
                initialiserPlateau(plateau);
                initialiserJoueurs(joueurs, nbJoueurs);
                placerJoueursSurPlateau(joueurs, nbJoueurs, plateau);

                // Afficher les informations des joueurs
                afficherInfosJoueurs(joueurs, nbJoueurs);

                // Lancer le jeu
                jeu(plateau, joueurs, nbJoueurs, niveauIA);
                break;

            case 2: // Charger une partie
                if (chargerPartie("sauvegarde.txt", plateau, joueurs, &nbJoueurs, &joueurActuel)) {
                    printf("\nPartie chargee avec succes !\n");
                    afficherInfosJoueurs(joueurs, nbJoueurs);
                    afficherPlateau(plateau, joueurs, nbJoueurs);

                    // Lancer le jeu à partir de l'état chargé
                    jeu(plateau, joueurs, nbJoueurs, niveauIA);
                } else {
                    printf("Erreur : Impossible de charger la partie.\n");
                }
                break;

            case 3: // Afficher Aide
                printf("\n--- Aide ---\n");
                printf("Le jeu Quoridor est un jeu de strategie.\n");
                printf("Deplacez votre pion ou placez des barrieres pour atteindre le bord oppose.\n");
                printf("Vous pouvez sauvegarder et charger une partie en cours.\n");
                printf("Les niveaux d'IA disponibles sont :\n");
                printf("- Facile : Pas de stratégie.\n");
                printf("- Moyen : Bloque les chemins évidents.\n");
                printf("- Difficile : Utilise une stratégie avancée.\n");
                break;

            case 4: // Quitter
                printf("Au revoir !\n");
                return 0;

            default:
                printf("Option invalide. Essayez encore.\n");
        }
    } while (choixMenu != 4);

    return 0;
}

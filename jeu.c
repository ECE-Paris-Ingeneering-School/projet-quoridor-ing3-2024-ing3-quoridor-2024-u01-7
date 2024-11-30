#include <stdio.h>
#include "jeu.h"
#include "plateau.h"
#include "joueurs.h"
#include "barrieres.h"
#include "affichage.h"

void afficherTourActuel(Joueur joueur) {
    printf("\n--- Tour de %s (%c) ---\n", joueur.nom, joueur.symbole);
}

int verifierVictoire(Joueur joueur, int taillePlateau) {

    if (joueur.x == 0 && joueur.y >= 0 && joueur.y < taillePlateau) {
        return 1;
    }

    if (joueur.x == taillePlateau - 1 && joueur.y >= 0 && joueur.y < taillePlateau) {
        return 1;
    }
    return 0; 
}



void nouvellePartie() {
    char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
    Joueur joueurs[4];  
    int nbJoueurs;



    initialiserPlateau(plateau);


    do {
        printf("Nombre de joueurs (2 ou 4) : ");
        scanf("%d", &nbJoueurs);
        if (nbJoueurs != 2 && nbJoueurs != 4) {
            printf("Erreur : Vous devez entrer 2 ou 4.\n");
        }
    } while (nbJoueurs != 2 && nbJoueurs != 4);


    initialiserJoueurs(joueurs, nbJoueurs);


    placerJoueursSurPlateau(joueurs, nbJoueurs, plateau);


    jeu(plateau, joueurs, nbJoueurs);
}


void jeu(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nbJoueurs) {
    int joueurActuel = 0;

    while (1) {

        printf("\n--- Informations des joueurs ---\n");
        for (int i = 0; i < nbJoueurs; i++) {
            printf("Joueur %d : %s (%c) - Type : %s - Barrieres restantes : %d\n",
                   i + 1, joueurs[i].nom, joueurs[i].symbole,
                   joueurs[i].estIA ? "IA" : "Humain",
                   joueurs[i].nbBarrieres);
        }


        afficherTourActuel(joueurs[joueurActuel]);
        afficherPlateau(plateau, joueurs, nbJoueurs);


        int choixAction;
        do {
            printf("1. Se deplacer\n");
            printf("2. Placer une barriere\n");
            printf("Choisissez une action : ");
            scanf("%d", &choixAction);

            if (choixAction != 1 && choixAction != 2) {
                printf("Erreur : Action invalide. Choisissez 1 ou 2.\n");
            }
        } while (choixAction != 1 && choixAction != 2);

        if (choixAction == 1) {

            char direction;
            do {
                printf("Direction (z = haut, s = bas, q = gauche, d = droite) : ");
                scanf(" %c", &direction);
                if (deplacerPion(&joueurs[joueurActuel], direction, plateau)) {
                    break; 
                } else {
                    printf("Erreur : Deplacement invalide. Reessayez.\n");
                }
            } while (1);


            if (verifierVictoire(joueurs[joueurActuel], TAILLE_PLATEAU)) {
                printf("\n--- Victoire ! ---\n");
                printf("Felicitations, %s (%c) a gagne !\n", joueurs[joueurActuel].nom, joueurs[joueurActuel].symbole);
                return; 
            }
        } else if (choixAction == 2) {

            if (joueurs[joueurActuel].nbBarrieres > 0) {
                int barrierePlacee = 0;
                char case1[3], case2[3], position; 
                do {
                    printf("Entrez les deux cases voisines et la position (ex : D1 D2 G) : ");
                    scanf("%s %s %c", case1, case2, &position);
                    if (placerBarriere(plateau, case1, case2, position)) {
                        joueurs[joueurActuel].nbBarrieres--; 
                        barrierePlacee = 1;                
                    } else {
                        printf("Erreur : Placement invalide. Essayez encore.\n");
                    }
                } while (!barrierePlacee);
            } else {
                printf("Erreur : Vous n'avez plus de barrieres disponibles.\n");
            }
        }

        // Passer au joueur suivant
        joueurActuel = (joueurActuel + 1) % nbJoueurs;
    }
}

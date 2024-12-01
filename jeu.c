#include <stdio.h>
#include "jeu.h"
#include "plateau.h"
#include "joueurs.h"
#include "barrieres.h"
#include "affichage.h"
#include "ia.h"
#include "sauvegarde.h"

void afficherTourActuel(Joueur joueur) {
    printf("\n--- Tour de %s (%c) ---\n", joueur.nom, joueur.symbole);
}

void jouerTourHumain(Joueur *joueur, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    int choixAction;
    char direction;

    // Afficher les options
    printf("1. Se deplacer\n");
    printf("2. Placer une barriere\n");
    printf("Choisissez une action : ");
    scanf("%d", &choixAction);

    if (choixAction == 1) {
        // Déplacement
        do {
            printf("Direction (z = haut, s = bas, q = gauche, d = droite) : ");
            scanf(" %c", &direction);
        } while (!deplacerPion(joueur, direction, plateau));
    } else if (choixAction == 2 && joueur->nbBarrieres > 0) {
        // Placement de barrière
        char case1[3], case2[3], position;
        do {
            printf("Entrez les deux cases voisines et la position (ex : D1 D2 G) : ");
            scanf("%s %s %c", case1, case2, &position);
        } while (!placerBarriere(plateau, case1, case2, position));
        joueur->nbBarrieres--;
    } else {
        printf("Erreur : Action invalide ou plus de barrieres disponibles.\n");
    }
}

int verifierVictoire(Joueur joueur) {
    printf("Débogage : Verification de victoire pour %s (%c) à la position (%d, %d). Ligne cible : %d\n",
           joueur.nom, joueur.symbole, joueur.x, joueur.y, joueur.ligneCible);

    // Vérifier la condition de victoire en fonction de la direction cible
    switch (joueur.directionCible) {
        case 'H': // Objectif : ligne du haut
            if (joueur.x == joueur.ligneCible) {
                printf("Debogage : %s (%c) a atteint la ligne cible en haut.\n", joueur.nom, joueur.symbole);
                return 1;
            }
            break;

        case 'B': // Objectif : ligne du bas
            if (joueur.x == joueur.ligneCible) {
                printf("Debogage : %s (%c) a atteint la ligne cible en bas.\n", joueur.nom, joueur.symbole);
                return 1;
            }
            break;

        case 'G': // Objectif : colonne de gauche
            if (joueur.y == joueur.ligneCible) {
                printf("Debogage : %s (%c) a atteint la colonne cible à gauche.\n", joueur.nom, joueur.symbole);
                return 1;
            }
            break;

        case 'D': // Objectif : colonne de droite
            if (joueur.y == joueur.ligneCible) {
                printf("Debogage : %s (%c) a atteint la colonne cible à droite.\n", joueur.nom, joueur.symbole);
                return 1;
            }
            break;

        default:
            printf("Erreur : Direction cible invalide pour %s (%c).\n", joueur.nom, joueur.symbole);
            break;
    }

    printf("Debogage : Pas de victoire detectee pour %s (%c).\n", joueur.nom, joueur.symbole);
    return 0; // Pas de victoire
}




void nouvellePartie() {
    char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
    Joueur joueurs[NB_MAX_JOUEURS];  // Maximum 4 joueurs
    int nbJoueurs;
    int niveauIA; // Stocke le niveau d'IA

    // Initialiser le plateau
    initialiserPlateau(plateau);

    // Saisir le nombre de joueurs
    do {
        printf("Nombre de joueurs (2 ou 4) : ");
        scanf("%d", &nbJoueurs);
        if (nbJoueurs != 2 && nbJoueurs != 4) {
            printf("Erreur : Vous devez entrer 2 ou 4.\n");
        }
    } while (nbJoueurs != 2 && nbJoueurs != 4);

    // Configurer le niveau d'IA
    printf("Choisissez le niveau d'IA (1 = Facile, 2 = Moyen, 3 = Difficile) : ");
    do {
        scanf("%d", &niveauIA);
        if (niveauIA < 1 || niveauIA > 3) {
            printf("Erreur : Vous devez choisir un niveau entre 1 et 3.\n");
        }
    } while (niveauIA < 1 || niveauIA > 3);

    // Initialiser les joueurs
    initialiserJoueurs(joueurs, nbJoueurs);

    // Placer les joueurs sur le plateau
    placerJoueursSurPlateau(joueurs, nbJoueurs, plateau);

    // Lancer la boucle principale du jeu
    jeu(plateau, joueurs, nbJoueurs, niveauIA);
}



void jeu(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nbJoueurs, int niveauIA) {
    int joueurActuel = 0;

    // Vérification initiale des positions des joueurs
    for (int i = 0; i < nbJoueurs; i++) {
        printf("Débogage : Verification initiale pour %s (%c) à la position (%d, %d). Ligne cible : %d\n",
               joueurs[i].nom, joueurs[i].symbole, joueurs[i].x, joueurs[i].y, joueurs[i].ligneCible);

        // Vérifie uniquement si les joueurs sont sur le plateau
        if (joueurs[i].x < 0 || joueurs[i].x >= TAILLE_PLATEAU ||
            joueurs[i].y < 0 || joueurs[i].y >= TAILLE_PLATEAU) {
            printf("Erreur : %s (%c) est hors du plateau. Verifiez le fichier de sauvegarde.\n",
                   joueurs[i].nom, joueurs[i].symbole);
            return;
        }
    }

    // Boucle principale du jeu
    while (1) {
        // Afficher les informations des joueurs
        printf("\n--- Informations des joueurs ---\n");
        for (int i = 0; i < nbJoueurs; i++) {
            printf("Joueur %d : %s (%c) - Type : %s - Barrières restantes : %d\n",
                   i + 1, joueurs[i].nom, joueurs[i].symbole,
                   joueurs[i].estIA ? "IA" : "Humain",
                   joueurs[i].nbBarrieres);
        }

        // Afficher le tour actuel et le plateau
        afficherTourActuel(joueurs[joueurActuel]);
        afficherPlateau(plateau, joueurs, nbJoueurs);

        // Vérifier si le joueur est une IA ou un humain
        if (joueurs[joueurActuel].estIA) {
            printf("\n--- Tour de l'IA : %s (%c) ---\n", joueurs[joueurActuel].nom, joueurs[joueurActuel].symbole);

            if (niveauIA == 1) {
                jouerIAFacile(&joueurs[joueurActuel], plateau);
            } else if (niveauIA == 2) {
                jouerIAMoyen(&joueurs[joueurActuel], joueurs, nbJoueurs, plateau);
            } else if (niveauIA == 3) {
                jouerIADifficile(&joueurs[joueurActuel], joueurs, nbJoueurs, plateau);
            }
        } else {
            printf("\n--- Tour du joueur humain : %s (%c) ---\n", joueurs[joueurActuel].nom, joueurs[joueurActuel].symbole);

            int choixAction;
            do {
                printf("1. Se deplacer\n");
                printf("2. Placer une barriere\n");
                printf("3. Afficher le menu\n");
                printf("Choisissez une action : ");
                if (scanf("%d", &choixAction) != 1 || (choixAction < 1 || choixAction > 3)) {
                    printf("Erreur : Action invalide. Choisissez 1, 2 ou 3.\n");
                    while (getchar() != '\n'); // Vider le buffer
                }
            } while (choixAction < 1 || choixAction > 3);

            if (choixAction == 1) {
                // Déplacement
                char direction;
                do {
                    printf("Direction (z = haut, s = bas, q = gauche, d = droite) : ");
                    if (scanf(" %c", &direction) != 1) {
                        printf("Erreur : Direction invalide. Reessayez.\n");
                        while (getchar() != '\n'); // Vider le buffer
                        continue;
                    }

                    if (deplacerPion(&joueurs[joueurActuel], direction, plateau)) {
                        printf("Deplacement reussi pour %s (%c) vers (%d, %d)\n",
                               joueurs[joueurActuel].nom, joueurs[joueurActuel].symbole,
                               joueurs[joueurActuel].x, joueurs[joueurActuel].y);
                        break;
                    } else {
                        printf("Erreur : Deplacement invalide. Reessayez.\n");
                    }
                } while (1);
            } else if (choixAction == 2) {
                // Placement de barrière
                if (joueurs[joueurActuel].nbBarrieres > 0) {
                    int barrierePlacee = 0;
                    char case1[3], case2[3], position;
                    do {
                        printf("Entrez les deux cases voisines et la position (ex : D1 D2 G) : ");
                        if (scanf("%s %s %c", case1, case2, &position) != 3) {
                            printf("Erreur : Format incorrect pour les cases et la position. Reessayez.\n");
                            while (getchar() != '\n'); // Vider le buffer
                            continue;
                        }

                        if (placerBarriere(plateau, case1, case2, position)) {
                            joueurs[joueurActuel].nbBarrieres--;
                            barrierePlacee = 1;
                            printf("Barriere placee avec succes par %s (%c).\n",
                                   joueurs[joueurActuel].nom, joueurs[joueurActuel].symbole);
                        } else {
                            printf("Erreur : Placement invalide. Essayez encore.\n");
                        }
                    } while (!barrierePlacee);
                } else {
                    printf("Erreur : Vous n'avez plus de barrieres disponibles.\n");
                }
            } else if (choixAction == 3) {
                printf("\n--- Menu du Jeu ---\n");
                printf("1. Continuer la partie\n");
                printf("2. Sauvegarder la partie\n");
                printf("3. Quitter au menu principal\n");
                int choixMenu;
                do {
                    printf("Choisissez une option : ");
                    if (scanf("%d", &choixMenu) != 1 || (choixMenu < 1 || choixMenu > 3)) {
                        printf("Erreur : Choix invalide. Reessayez.\n");
                        while (getchar() != '\n'); // Vider le buffer
                    }
                } while (choixMenu < 1 || choixMenu > 3);

                if (choixMenu == 2) {
                    sauvegarderPartie("sauvegarde.txt", plateau, joueurs, nbJoueurs, joueurActuel);
                } else if (choixMenu == 3) {
                    printf("Retour au menu principal...\n");
                    return;
                }
            }
        }

        if (verifierVictoire(joueurs[joueurActuel])) {
            printf("\n--- Victoire ! ---\n");
            printf("Felicitations, %s (%c) a gagne !\n", joueurs[joueurActuel].nom, joueurs[joueurActuel].symbole);
            return;
        }

        joueurActuel = (joueurActuel + 1) % nbJoueurs;
    }
}

#ifndef JEU_H
#define JEU_H

#include "structures.h"

void jeu(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nbJoueurs, int niveauIA);
void nouvellePartie();
void afficherTourActuel(Joueur joueur);
int verifierVictoire(Joueur joueur);
void jouerTourHumain(Joueur *joueur, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);


#endif

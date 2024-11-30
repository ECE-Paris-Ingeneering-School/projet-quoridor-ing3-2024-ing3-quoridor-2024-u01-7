#ifndef JEU_H
#define JEU_H

#include "structures.h"

void jeu(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nbJoueurs);
void nouvellePartie();
void afficherTourActuel(Joueur joueur);
int verifierVictoire(Joueur joueur, int taillePlateau);

#endif

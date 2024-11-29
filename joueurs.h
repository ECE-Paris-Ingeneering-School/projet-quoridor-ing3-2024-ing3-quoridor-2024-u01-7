#ifndef JOUEURS_H
#define JOUEURS_H

#include "structures.h"

void initialiserJoueurs(Joueur joueurs[], int nbJoueurs);
int deplacerPion(Joueur *joueur, char direction, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

#endif

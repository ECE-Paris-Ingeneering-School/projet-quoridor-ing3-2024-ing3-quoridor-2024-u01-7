#ifndef PLATEAU_H
#define PLATEAU_H

#include "structures.h"

void initialiserPlateau(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);
void afficherPlateau(char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nbJoueurs);
void placerJoueursSurPlateau(Joueur joueurs[], int nbJoueurs, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);
void afficherInfosJoueurs(Joueur joueurs[], int nbJoueurs);

#endif

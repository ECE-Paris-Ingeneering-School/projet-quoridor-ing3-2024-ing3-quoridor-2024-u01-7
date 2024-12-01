#ifndef IA_H
#define IA_H

#include "structures.h"

void jouerIAFacile(Joueur *joueur, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);
void jouerIAMoyen(Joueur *joueur, Joueur joueurs[], int nbJoueurs, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);
void jouerIADifficile(Joueur *joueur, Joueur joueurs[], int nbJoueurs, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

#endif // IA_H

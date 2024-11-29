#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "structures.h"

void sauvegarderPartie(const char *nomFichier, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nbJoueurs, int joueurActuel);
int chargerPartie(const char *nomFichier, char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int *nbJoueurs, int *joueurActuel);

#endif

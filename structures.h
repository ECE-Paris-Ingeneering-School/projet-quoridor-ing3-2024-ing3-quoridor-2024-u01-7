#ifndef STRUCTURES_H
#define STRUCTURES_H
#define NB_MAX_JOUEURS 4


#define TAILLE_PLATEAU 9
#define NB_BARRIERES_2J 10
#define NB_BARRIERES_4J 5

typedef struct {
    char nom[50];
    int x, y;          // Position du pion
    char symbole;      // Symbole pour représenter le joueur
    int nbBarrieres;// Nombre de barrières restantes
    int estIA;
} Joueur;

#endif

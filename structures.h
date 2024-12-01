#ifndef STRUCTURES_H
#define STRUCTURES_H
#define NB_MAX_JOUEURS 4


#define TAILLE_PLATEAU 9
#define NB_BARRIERES_2J 10
#define NB_BARRIERES_4J 5

typedef struct {
    char nom[50];
    char symbole;
    int x, y; // Position actuelle
    int nbBarrieres;
    char directionCible; // Direction de la cible ('H', 'B', 'G', 'D')
    int ligneCible;      // Ligne ou colonne cible pour la victoire
    int estIA;
} Joueur;

#endif

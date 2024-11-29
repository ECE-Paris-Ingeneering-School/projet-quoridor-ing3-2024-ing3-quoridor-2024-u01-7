#include <stdio.h>
#include "menu.h"

void afficherMenu() {
    printf("\n--- Menu Principal ---\n");
    printf("1. Nouvelle Partie\n");
    printf("2. Reprendre Partie\n");
    printf("3. Afficher Aide\n");
    printf("4. Afficher Scores\n");
    printf("5. Quitter\n");
}

void afficherAide() {
    printf("\n--- Aide ---\n");
    printf("Le jeu Quoridor est un jeu de strategie où le but est d'atteindre le bord oppose du plateau.\n");
    printf("Vous pouvez vous deplacer ou placer des barrieres pour ralentir vos adversaires.\n");
}

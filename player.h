#ifndef PLAYER_H
#define PLAYER_H

#include "map.h" // IMPORTANT : Pour que player.h connaisse MAP_SIZE

#define MAX_NAME 25

typedef struct {
    char player_name[MAX_NAME];
    int x;
    int y;
    char arme_recherchee;
    char arme_active;
    char icone;             // Pour afficher 'W', 'R', 'M', 'T'
    char case_sous_joueur;  // Mémorise le '-', '|' ou '#' sous le joueur
    int monstres_vaincus[MAP_SIZE][MAP_SIZE]; // La mémoire personnelle du joueur

} player;

void movement_keys();
// avancement prend le joueur complet et la carte !
void avancement(player *p, char Lab[MAP_SIZE][MAP_SIZE]);
void choisir_arme(char *arme);

#endif
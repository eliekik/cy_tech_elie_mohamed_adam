#ifndef EVENT_H
#define EVENT_H

#include "player.h"
#include "map.h"

// Retourne 1 si le joueur survit (ou case vide), 0 s'il meurt
int declencher_evenement(player *p, int id_joueur, char carte_cachee[MAP_SIZE][MAP_SIZE], char labyrinthe[MAP_SIZE][MAP_SIZE]);

#endif
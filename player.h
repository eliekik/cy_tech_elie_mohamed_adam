#ifndef PLAYER_H
#define PLAYER_H

#define MAX_NAME 25

typedef struct {
    char player_name[MAX_NAME];
    int x;
    int y;
    char arme_recherchee;
    char arme_active;
} player;

void movement_keys();
void avancement(int *x, int *y);
void choisir_arme(char *arme);

#endif
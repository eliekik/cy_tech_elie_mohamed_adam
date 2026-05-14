#include <stdio.h>
#include "map.h"

void init_labyrinthe(char Lab[MAP_SIZE][MAP_SIZE]) {
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            if (y == 0 || y == MAP_SIZE - 1) {
                Lab[y][x] = '-';
            }
            else if (x == 0 || x == MAP_SIZE - 1) {
                Lab[y][x] = '|';
            }
            else {
                Lab[y][x] = '#'; 
            }
        }
    }
    Lab[0][0] = '+';
    Lab[0][MAP_SIZE - 1] = '+';
    Lab[MAP_SIZE - 1][0] = '+';
    Lab[MAP_SIZE - 1][MAP_SIZE - 1] = '+';
}

void afficher_labyrinthe(char Lab[MAP_SIZE][MAP_SIZE]) {
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            printf("%c ", Lab[y][x]);
        }
        printf("\n"); 
    }
}
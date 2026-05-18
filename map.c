#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

void init_carte_cachee(char Lab_cache[MAP_SIZE][MAP_SIZE]) {
    // 25 éléments (4 Basilics, 4 Zombies, 4 Harpies, 4 Trolls = 16 monstres)
    // Epée,L,G,D = Armes antiques, C = Coffres, P = Portail, K = Totems (K pour transmutation)
    char elements[25] = {
        'B','B','B','B', 'Z','Z','Z','Z',
        'H','H','H','H', 'T','T','T','T',
        'E','L','G','D', 'C','C', 'P', 'K','K'
    };

    // Mélange aléatoire complet de la liste
    srand(time(NULL));
    for (int i = 24; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = elements[i];
        elements[i] = elements[j];
        elements[j] = temp;
    }

    // Remplissage des cases de 1 à 5 (l'intérieur des murs)
    int index = 0;
    for (int y = 1; y < MAP_SIZE - 1; y++) {
        for (int x = 1; x < MAP_SIZE - 1; x++) {
            Lab_cache[y][x] = elements[index];
            index++;
        }
    }
}

void afficher_labyrinthe(char Lab[MAP_SIZE][MAP_SIZE], int memoire[MAP_SIZE][MAP_SIZE]) {
    printf("\n");
    for (int y = 0; y < MAP_SIZE; y++) {

        printf("                                            ");

        for (int x = 0; x < MAP_SIZE; x++) {
            if (Lab[y][x] == '#' && memoire[y][x] == 1) {
                printf("  "); 
            } 
            else {
                printf("%c ", Lab[y][x]);
            }
        }
        printf("\n"); 
    }
}

void afficher_guide_coordonnees() {
    printf("\n              --- COORDINATES GUIDE ---\n");
    printf("                 X (Columns: 1 to 5)  \n");
    printf("                  1 2 3 4 5 \n");
    printf("                + - - - - - +\n");
    printf("              1 | # # # # # |\n");
    printf("           Y  2 | # # # # # |\n");
    printf("         (Row)3 | # # # # # |\n");
    printf("              4 | # # # # # |\n");
    printf("              5 | # # # # # |\n");
    printf("                + - - - - - +\n\n");
}
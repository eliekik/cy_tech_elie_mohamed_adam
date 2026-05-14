#include <stdio.h>
#include "player.h"

void movement_keys() {
    printf("      1:^ \n");
    printf(" 2:<   3:v   4:> \n");
}

void choisir_arme(char *arme) {
    int choix;

    printf("\n--- WEAPON CHOICE ---\n");
    printf("1. Shield (against Basilic)\n");
    printf("2. Torch (against Zombie)\n");
    printf("3. Long Bow (against Harpie)\n");
    printf("4. Stone Axe (against Troll)\n");
    printf("Choose your weapon (1-4) : ");

    if (scanf("%d", &choix) != 1) {
        scanf("%*s"); // Nettoyage propre sans variable
        printf("Error : invalid entry.\n");
        choisir_arme(arme); 
        return; // Ajout obligatoire
    }

    switch (choix) {
        case 1: *arme = 'S'; break; 
        case 2: *arme = 'T'; break; 
        case 3: *arme = 'B'; break; 
        case 4: *arme = 'A'; break; 
        default: 
            printf("Error : Invalid Choice.\n");
            choisir_arme(arme);
            return; // Changé de break à return pour sécuriser la récursivité
    }
}

void avancement(int *x, int *y) {
    int movement;

    printf("Advance to a case \n");
    movement_keys();

    if (scanf("%d", &movement) != 1) {
        scanf("%*s");
        printf("\n[ERROR] Please enter a working number!\n\n");
        avancement(x, y);
        return;
    }

    if (movement < 1 || movement > 4) {
        printf(" error :/ try again \n \n");
        avancement(x, y); 
        return; // Ajout obligatoire ici aussi
    } 
    else {  
        switch (movement) {
            case 1: *y = *y - 1; break; 
            case 2: *x = *x - 1; break; 
            case 3: *y = *y + 1; break; 
            case 4: *x = *x + 1; break; 
        }
    }
}
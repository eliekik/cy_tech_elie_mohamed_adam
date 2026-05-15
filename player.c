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
    printf("\n\n");

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

void avancement(player *p, char Lab[MAP_SIZE][MAP_SIZE]) {
    int movement;
    int futur_x = p->x;
    int futur_y = p->y;

    printf("Advance to a case \n");
    movement_keys();

    if (scanf("%d", &movement) != 1) {
        scanf("%*s");
        printf("\n[ERROR] Please enter a valid number!\n\n");
        avancement(p, Lab);
        return;
    }
    // 1. Calcul de la future position
    switch (movement) {
        case 1: futur_y--; break; // Haut
        case 2: futur_x--; break; // Gauche
        case 3: futur_y++; break; // Bas
        case 4: futur_x++; break; // Droite
        default: printf("Invalid choice.\n"); avancement(p, Lab); return;
    }
    // VERIFICATION DES LIMITES ET DES MURS
    if (futur_x < 0 || futur_x >= MAP_SIZE || futur_y < 0 || futur_y >= MAP_SIZE) {
        printf("\n[Border] You cannot leave the map area!\n\n");
        avancement(p, Lab); 
        return; // Ajout obligatoire ici aussi
    } 
      
    char cible = Lab[futur_y][futur_x];

    // RÈGLE 1 : Si on est déjà à l'intérieur, interdit de retourner sur un mur
    if (p->case_sous_joueur == '#' && (cible == '-' || cible == '|' || cible == '+')) {
        printf("\n[Locked] The door is closed! You must stay inside the labyrinth.\n\n");
        avancement(p, Lab);
        return;
    }

    // RÈGLE 2 : Si on est sur le bord, on n'a pas le droit de marcher le long du mur
    if (p->case_sous_joueur != '#' && (cible == '-' || cible == '|' || cible == '+')) {
        printf("\n[Entry] You must enter the labyrinth (move to a # case)!\n\n");
        avancement(p, Lab);
        return;
    }

    // 3. MISE À JOUR VISUELLE (La gommette)
    // A. On redessine le décor d'origine là où le joueur se trouvait
    Lab[p->y][p->x] = p->case_sous_joueur;

    // B. On valide les nouvelles coordonnées du joueur
    p->x = futur_x;
    p->y = futur_y;    
    // C. On sauvegarde le décor de la NOUVELLE case avant de marcher dessus
    p->case_sous_joueur = Lab[p->y][p->x];

    // D. On dessine le joueur sur sa nouvelle case
    Lab[p->y][p->x] = p->icone;    
}
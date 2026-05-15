#include <stdio.h>
#include "event.h"

int declencher_evenement(player *p, int id_joueur, char carte_cachee[MAP_SIZE][MAP_SIZE], char labyrinthe[MAP_SIZE][MAP_SIZE]) {
    
    // Si CE joueur a DÉJÀ vaincu cette case, il ne se passe rien !
    if (p->monstres_vaincus[p->y][p->x] == 1) {
        return 1; 
    }

    char case_actuelle = carte_cachee[p->y][p->x];
    
    if (case_actuelle != ' ') { 
        printf("\n!!! EVENT !!!\n");
        int victoire = 0; 

        // Les monstres
        if (case_actuelle == 'B') {
            printf("A wild BASILIC appears!\n");
            if (p->arme_active == 'S') victoire = 1; 
        }
        else if (case_actuelle == 'Z') {
            printf("A ZOMBIE rises from the ground!\n");
            if (p->arme_active == 'T') victoire = 1; 
        }
        else if (case_actuelle == 'H') {
            printf("A HARPIE attacks from above!\n");
            if (p->arme_active == 'B') victoire = 1; 
        }
        else if (case_actuelle == 'T') { 
            printf("A TROLL blocks the path!\n");
            if (p->arme_active == 'A') victoire = 1; 
        }
        // Les bonus
        else if (case_actuelle == 'A') {
            printf("You found an Antique Weapon!\n"); victoire = 1;
        }
        else if (case_actuelle == 'C') {
            printf("You found a Treasure Chest!\n"); victoire = 1;
        }
        else if (case_actuelle == 'P') {
            printf("You stepped on the Magic Portal!\n"); victoire = 1;
        }
        else if (case_actuelle == 'K') {
            printf("You found a Transmutation Totem!\n"); victoire = 1;
        }

        // Conséquences
        if (victoire == 1) {
            printf(">>> SUCCESS!\n");
            
            // On note dans le cerveau du joueur que la case est "nettoyée" pour lui
            p->monstres_vaincus[p->y][p->x] = 1; 
            
            printf("You can continue your turn.\n");
            return 1; 
        } 
        else {
            printf(">>> DEFEAT! Wrong weapon... You died.\n");
            
            labyrinthe[p->y][p->x] = p->case_sous_joueur;
            
            if (id_joueur == 0)      { p->x = 3; p->y = 0; p->case_sous_joueur = '-'; }
            else if (id_joueur == 1) { p->x = 6; p->y = 3; p->case_sous_joueur = '|'; }
            else if (id_joueur == 2) { p->x = 3; p->y = 6; p->case_sous_joueur = '-'; }
            else if (id_joueur == 3) { p->x = 0; p->y = 3; p->case_sous_joueur = '|'; }
            
            labyrinthe[p->y][p->x] = p->icone;
            printf("%s is teleported back to the start!\n", p->player_name);
            
            return 0; 
        }
    }
    
    return 1; 
}
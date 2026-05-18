#include <stdio.h>
#include "player.h"

void movement_keys() {
    printf("                                                                                        ");
    printf("      1:^ \n");
    printf("                                                                                        ");
    printf(" 2:<   3:v   4:> \n");
}

void choisir_arme(char *arme) {
    int choix;

    printf("\n                                                                                        --- WEAPON CHOICE ---\n");
    printf("                                                                                        1. Shield (against Basilic)\n");
    printf("                                                                                        2. Torch (against Zombie)\n");
    printf("                                                                                        3. Long Bow (against Harpie)\n");
    printf("                                                                                        4. Stone Axe (against Troll)\n\n");
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
void afficher_nom_arme(char code) {
    switch (code) {
        case 'S': printf("Shield"); break;
        case 'T': printf("Torch"); break;
        case 'B': printf("Long Bow"); break;
        case 'A': printf("Stone Axe"); break;
        case 'E': printf("Epic Sword"); break;
        case 'L': printf("Lunar Crossbow"); break;
        case 'G': printf("Forbidden Grimoire"); break;
        case 'D': printf("Shadow Dagger"); break;
        default:  printf("Unknown Weapon"); break;
    }
}
void avancement(player *p, char Lab[MAP_SIZE][MAP_SIZE]) {
    int movement;
    int futur_x = p->x;
    int futur_y = p->y;

    // --- LOGIQUE DU PORTAIL MAGIQUE ---
    if (p->a_portail == 1) {
        printf("\n[MAGIC PORTAL] Choose ANY hidden case ('#') to teleport to!\n");

        // ON AFFICHE LE PLAN ICI
        afficher_guide_coordonnees();

        printf("Enter the column (X: 1-5) and row (Y: 1-5) separated by a space : ");
        
        if (scanf("%d %d", &futur_x, &futur_y) != 2) {
            scanf("%*s");
            printf("Invalid input.\n");
            avancement(p, Lab);
            return;
        }
        p->a_portail = 0; // Le pouvoir est consommé !
        // On vide tout ce que le joueur a pu taper en trop (espaces, autres chiffres...)
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        p->a_portail = 0;
    } 
    else {
        // --- LOGIQUE DE DÉPLACEMENT NORMALE ---
        printf("                                                                                        Advance to a case \n");
        movement_keys();

        if (scanf("%d", &movement) != 1) {
            scanf("%*s");
            printf("\n[ERROR] Please enter a valid number!\n\n");
            avancement(p, Lab);
            return;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        // 1. Calcul de la future position (DOIT ETRE DANS LE ELSE !)
        switch (movement) {
            case 1: futur_y--; break; // Haut
            case 2: futur_x--; break; // Gauche
            case 3: futur_y++; break; // Bas
            case 4: futur_x++; break; // Droite
            default: printf("Invalid choice.\n"); avancement(p, Lab); return;
        }
    }
    
    // VERIFICATION DES LIMITES ET DES MURS
    if (futur_x < 0 || futur_x >= MAP_SIZE || futur_y < 0 || futur_y >= MAP_SIZE) {
        printf("\n[Border] You cannot leave the map area!\n\n");
        avancement(p, Lab); 
        return; 
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
    Lab[p->y][p->x] = p->case_sous_joueur;
    p->x = futur_x;
    p->y = futur_y;    
    p->case_sous_joueur = Lab[p->y][p->x];
    Lab[p->y][p->x] = p->icone;    
}
int verifier_etouffement(player *p, int id_joueur, char labyrinthe[MAP_SIZE][MAP_SIZE]) {
    int cases_cachees = 0;
    
    // On vérifie les 4 cases autour
    if (labyrinthe[p->y - 1][p->x] == '#' && p->monstres_vaincus[p->y - 1][p->x] == 0) cases_cachees++; 
    if (labyrinthe[p->y + 1][p->x] == '#' && p->monstres_vaincus[p->y + 1][p->x] == 0) cases_cachees++; 
    if (labyrinthe[p->y][p->x - 1] == '#' && p->monstres_vaincus[p->y][p->x - 1] == 0) cases_cachees++; 
    if (labyrinthe[p->y][p->x + 1] == '#' && p->monstres_vaincus[p->y][p->x + 1] == 0) cases_cachees++; 
    
    // Si on est à l'intérieur du labyrinthe ET qu'il n'y a plus de '#' inexplorés autour
    if (p->case_sous_joueur != '-' && p->case_sous_joueur != '|' && cases_cachees == 0) {
        printf("\n[BLOCKED] There are no hidden cases around you! You are teleported back to the start.\n");
        
        // 1. On efface le joueur de sa position actuelle
        labyrinthe[p->y][p->x] = p->case_sous_joueur;
        
        // 2. On réinitialise ses coordonnées à sa case de départ selon son rôle
        if (id_joueur == 0)      { p->x = 3; p->y = 0; p->case_sous_joueur = '-'; }
        else if (id_joueur == 1) { p->x = 6; p->y = 3; p->case_sous_joueur = '|'; }
        else if (id_joueur == 2) { p->x = 3; p->y = 6; p->case_sous_joueur = '-'; }
        else if (id_joueur == 3) { p->x = 0; p->y = 3; p->case_sous_joueur = '|'; }
        
        // 3. On redessine le joueur sur sa case de départ
        labyrinthe[p->y][p->x] = p->icone;
        
        return 1; // 1 = Le joueur est bloqué
    }
    
    return 0; // 0 = Le joueur n'est pas bloqué, tout va bien
}
#include <stdio.h>
#include "event.h"
#include "map.h"

int declencher_evenement(player *p, int id_joueur, char carte_cachee[MAP_SIZE][MAP_SIZE], char labyrinthe[MAP_SIZE][MAP_SIZE]) {
    
    // Si CE joueur a DÉJÀ vaincu cette case, il ne se passe rien !
    if (p->monstres_vaincus[p->y][p->x] == 1) {
        return 1; 
    }

    char case_actuelle = carte_cachee[p->y][p->x];
    
    if (case_actuelle != ' ') { 
        printf("\n                                            !!! EVENT !!!\n");
        int victoire = 0; 

        // Les monstres
        if (case_actuelle == 'B') {
            printf("                                       A wild BASILIC appears!\n");
            if (p->arme_active == 'S'){ 
                victoire = 1;
                printf(">>> SUCCESS!                             Right weapon... You live.\n");
            }
        }
        else if (case_actuelle == 'Z') {
            printf("                                       A ZOMBIE rises from the ground!\n");
            if (p->arme_active == 'T'){ 
                victoire = 1; 
                printf(">>> SUCCESS!                             Right weapon... You live.\n");
            }
        }
        else if (case_actuelle == 'H') {
            printf("                                       A HARPIE attacks from above!\n");
            if (p->arme_active == 'B'){ 
                victoire = 1; 
                printf(">>> SUCCESS!                             Right weapon... You live.\n");
            }
        }
        else if (case_actuelle == 'T') { 
            printf("                                       A TROLL blocks the path!\n");
            if (p->arme_active == 'A'){ 
                victoire = 1;
                printf(">>> SUCCESS!                             Right weapon... You live.\n");
            } 
        }
        // Les bonus
       
        else if (case_actuelle == 'P') {
            printf("                                            You stepped on the Magic Portal! Your next move is a free teleport.\n");
            p->a_portail = 1; // On active le pouvoir
            victoire = 1;
        }
        else if (case_actuelle == 'K') {
            printf("                                            You found a Transmutation Totem!\n\n");
            int cible_x, cible_y;
            // ON AFFICHE LE PLAN ICI
            afficher_guide_coordonnees();
            printf("                                            Choose a hidden case to swap the Totem with (X Y) : ");
            scanf("%d %d", &cible_x, &cible_y);
            
            // On vérifie que la case cible est bien sur la map et qu'elle est cachée '#'
            if (cible_x >= 1 && cible_x <= 5 && cible_y >= 1 && cible_y <= 5 && labyrinthe[cible_y][cible_x] == '#') {
                // On échange secrètement dans la carte invisible
                char temp = carte_cachee[p->y][p->x];//temp prend la case du joueur (le totem)
                carte_cachee[p->y][p->x] = carte_cachee[cible_y][cible_x];// la case cible choisi par joueur remplace la case du joueur
                carte_cachee[cible_y][cible_x] = temp;// le totem est placée dans la case choisi par joueur
                printf("                                            Totem swapped successfully!\n");
            }
            else {
                printf("Invalid target! The Totem fizzles out...\n");
            }
            victoire = 3;//fin du tour 
        }
        else if (case_actuelle == 'C') {
            printf("                                            You found a Treasure Chest!\n");
            printf(">>> SUCCESS!                                  Lucky ... You live.\n"); 
            p->a_trouve_tresor = 1;
            victoire = 1;
            // VERIFICATION VICTOIRE TOTALE
            if (p->a_trouve_arme == 1) {
                return 2; // 2 = VICTOIRE DU JEU !
            }
        }

        // LES ARMES LÉGENDAIRES
        else if (case_actuelle == 'E' || case_actuelle == 'L' || case_actuelle == 'G' || case_actuelle == 'D') {
            
            if (case_actuelle == p->arme_recherchee) {
                printf("EPIC SUCCESS!                                       You found your Legendary Weapon!\n");
                p->a_trouve_arme = 1; // Il la met dans sa poche !
                victoire = 1; // Tu peux rajouter des points de score ici plus tard !
                // VERIFICATION VICTOIRE TOTALE
                if (p->a_trouve_tresor == 1) {
                    return 2; // 2 = VICTOIRE DU JEU !
                }
            } 
            else {
                printf("You found a Legendary weapon               ... It's not yours keep looking\n");
                printf(">>> SUCCESS!                                  ... You live.\n");
                victoire = 1;
            }
        }

        // Conséquences
        if (victoire == 1) {
            
            // On note dans le cerveau du joueur que la case est "nettoyée" pour lui
            p->monstres_vaincus[p->y][p->x] = 1; 
            
            printf("You can continue your turn.\n");
            return 1; 
        }
        else if (victoire == 3) {
            printf(">>> The Totem's magic teleports you safely back to the start!\n");
            // On efface le joueur de sa position actuelle
            labyrinthe[p->y][p->x] = p->case_sous_joueur;
            
            // On le remet à sa place de départ selon son rôle
            if (id_joueur == 0)      { p->x = 3; p->y = 0; p->case_sous_joueur = '-'; }
            else if (id_joueur == 1) { p->x = 6; p->y = 3; p->case_sous_joueur = '|'; }
            else if (id_joueur == 2) { p->x = 3; p->y = 6; p->case_sous_joueur = '-'; }
            else if (id_joueur == 3) { p->x = 0; p->y = 3; p->case_sous_joueur = '|'; }
            
            labyrinthe[p->y][p->x] = p->icone;
            
            return 0; // On renvoie 0 au main pour dire "le tour est fini"
        } 
        else {
            printf(">>> DEFEAT!                             Wrong weapon... You died.\n");
            
           
            // LE JOUEUR PERD SON BUTIN
            p->a_trouve_arme = 0;
            p->a_trouve_tresor = 0;
            
            // Il "oublie" qu'il a vidé les cases des coffres et de son arme
            for (int lig = 0; lig < MAP_SIZE; lig++) {
            for (int col = 0; col < MAP_SIZE; col++) {
                if (carte_cachee[lig][col] == 'C' || carte_cachee[lig][col] == p->arme_recherchee) {
                        p->monstres_vaincus[lig][col] = 0; // La case redevient active pour lui !
                }
            }
        }
        printf("You lost your items! They returned to the labyrinth.\n");

        labyrinthe[p->y][p->x] = p->case_sous_joueur;
            
        if (id_joueur == 0)      { p->x = 3; p->y = 0; p->case_sous_joueur = '-'; }
        else if (id_joueur == 1) { p->x = 6; p->y = 3; p->case_sous_joueur = '|'; }
        else if (id_joueur == 2) { p->x = 3; p->y = 6; p->case_sous_joueur = '-'; }
        else if (id_joueur == 3) { p->x = 0; p->y = 3; p->case_sous_joueur = '|'; }
        
        labyrinthe[p->y][p->x] = p->icone;
        printf("%s is teleported back to the start!\n", p->player_name);
        
        return 0; 
        }
    
        return 1; 
    }
}
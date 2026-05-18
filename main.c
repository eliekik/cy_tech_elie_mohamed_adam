#include <stdio.h>
#include <stdlib.h>
#include "menu.h" // N'oublie pas le menu !
#include "map.h"
#include "player.h"
#include "event.h"

int main() {
    // 1. APPEL DU MENU PRINCIPAL
    int lancement = afficher_menu_principal();
    
    // Si le joueur ne choisit pas de jouer (ex: quitter), on arrête là.
    if (lancement != 1) {
        return 0; 
    }

    // 2. INITIALISATION DU JEU
    char labyrinthe[MAP_SIZE][MAP_SIZE];
    init_labyrinthe(labyrinthe);
    
    char carte_cachee[MAP_SIZE][MAP_SIZE];
    init_carte_cachee(carte_cachee); 
    
    player joueurs[4]; 
    int nb_joueurs = 0;
    
    while (nb_joueurs < 2 || nb_joueurs > 4) {
        printf("How many players (2, 3 or 4) ? ");
        if (scanf("%d", &nb_joueurs) != 1) {
            scanf("%*s"); 
            printf("[Error] Please enter a number.\n\n");
        }
        else if (nb_joueurs < 2 || nb_joueurs > 4) {
            printf("[Error] You must choose between 2 and 4 players.\n\n");
        }
    }

    // On demande les noms et on place les joueurs sur la carte
    for (int i = 0; i < nb_joueurs; i++) {
        printf("Player [%d] name : " , i+1);
        scanf("%s", joueurs[i].player_name);

        joueurs[i].arme_active = ' ';
        joueurs[i].a_trouve_arme = 0;
        joueurs[i].a_trouve_tresor = 0;
        joueurs[i].a_portail = 0;

        if (i == 0) { // Guerrier
            joueurs[i].x = 3; joueurs[i].y = 0; 
            joueurs[i].arme_recherchee = 'E';
            joueurs[i].icone = 'W';
            joueurs[i].case_sous_joueur = '-'; 
            printf("Your role : Warrior\n\n");
        }
        else if (i == 1) { // Ranger
            joueurs[i].x = 6; joueurs[i].y = 3; 
            joueurs[i].arme_recherchee = 'L';
            joueurs[i].icone = 'R'; 
            joueurs[i].case_sous_joueur = '|'; 
            printf("Your role : Ranger\n\n");            
        }
        else if (i == 2) { // Magicien
            joueurs[i].x = 3; joueurs[i].y = 6; 
            joueurs[i].arme_recherchee = 'G';
            joueurs[i].icone = 'M'; 
            joueurs[i].case_sous_joueur = '-'; 
            printf("Your role : Magician\n\n");            
        }
        else if (i == 3) { // Voleur
            joueurs[i].x = 0; joueurs[i].y = 3; 
            joueurs[i].arme_recherchee = 'D';
            joueurs[i].icone = 'T'; 
            joueurs[i].case_sous_joueur = '|';  
            printf("Your role : Thief\n\n");            
        }
        
        // On met la mémoire des monstres vaincus à 0
        for (int y = 0; y < MAP_SIZE; y++) {
            for (int x = 0; x < MAP_SIZE; x++) {
                joueurs[i].monstres_vaincus[y][x] = 0;
            }
        }
        
        // On place l'icône sur la carte
        labyrinthe[joueurs[i].y][joueurs[i].x] = joueurs[i].icone;
    }

    printf("\n\n                                      --- THE GAME STARTS ! ---\n");
    
    int partie_en_cours = 1;
    
   // 3. LA GRANDE BOUCLE DE JEU
    while (partie_en_cours == 1) {
        
        for (int i = 0; i < nb_joueurs; i++) {
            int joueur_vivant = 1; 
            
            printf("\n                                 ====================================\n");
            printf("                                   >>> STARTING TURN FOR [%s] <<<\n", joueurs[i].player_name);
            printf("                                 ====================================\n");

            while (joueur_vivant == 1) {
                
               // LE RADAR D'ÉTOUFFEMENT 
                if (verifier_etouffement(&joueurs[i], i, labyrinthe) == 1) {
                    joueur_vivant = 0; // Fin du tour immédiate
                    break; // On casse la boucle pour passer au joueur suivant
                }
                
                // 1. On affiche la carte en premier avec la mémoire de CE joueur
                afficher_labyrinthe(labyrinthe, joueurs[i].monstres_vaincus);
                
                // 2. Le joueur choisit où il va et se déplace
                avancement(&joueurs[i], labyrinthe);
                
                // 3. SEULEMENT si la case sous lui est un '#' et qu'elle n'est pas dans sa mémoire
                if (joueurs[i].case_sous_joueur == '#' && joueurs[i].monstres_vaincus[joueurs[i].y][joueurs[i].x] == 0) {
                    choisir_arme(&joueurs[i].arme_active);
                    printf("              Equipped arm: [");
                    afficher_nom_arme(joueurs[i].arme_active); // La fonction va écrire "Shield" ici
                    printf("]\n");
                }
               
                // 4. On récupère le résultat de l'événement (0=mort, 1=vivant, 2=VICTOIRE)
                int resultat_event = declencher_evenement(&joueurs[i], i, carte_cachee, labyrinthe);
                
                if (resultat_event == 2) {
                    printf("\n\n                                            ========================================================\n");
                    printf("                                                     CONGRATULATIONS %s ! YOU WON THE GAME !  \n", joueurs[i].player_name);
                    printf("                                            ========================================================\n\n");
                    partie_en_cours = 0; 
                    break; 
                }
                
                joueur_vivant = resultat_event; 
            } // Fin du while(joueur_vivant)

            printf("End of turn for %s.\n", joueurs[i].player_name);
            
            if (partie_en_cours == 0) break; // Si quelqu'un a gagné, on arrête aussi la boucle des joueurs
            
        } // Fin du for(joueurs)
    } // Fin du while(partie_en_cours)
    
    return 0;
}
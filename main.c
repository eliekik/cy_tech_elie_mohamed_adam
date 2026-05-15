#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "player.h"
#include "event.h"

int main() {
    // 1. Initialisation de la carte
    char labyrinthe[MAP_SIZE][MAP_SIZE];
    init_labyrinthe(labyrinthe);
    
    player joueurs[4]; 
    int nb_joueurs = 0;
    printf("=================================\n");
    printf("       MEMO-RPG : THE GAME       \n");
    printf("=================================\n");

    while (nb_joueurs < 2 || nb_joueurs > 4) {
        printf("How many players (2, 3 or 4) ? ");
        
        // Test 1 : Est-ce que le joueur a tapé une lettre ?
        if (scanf("%d", &nb_joueurs) != 1) {
            scanf("%*s"); // L'aspirateur magique
            printf("[Error] Please enter a number.\n\n");
        }
        // Test 2 : C'est un chiffre, mais est-il en dehors de 2, 3 ou 4 ?
        else if (nb_joueurs < 2 || nb_joueurs > 4) {
            printf("[Error] You must choose between 2 and 4 players.\n\n");
        }
    }

    // On demande les noms et on place les joueurs sur la carte
    for (int i = 0; i < nb_joueurs; i++) {

        printf("Player [%d] name : " ,i+1);
        scanf("%s", joueurs[i].player_name);
        joueurs[i].arme_active = ' ';

        // On donne les positions selon le numéro du joueur
        // INITIALISATION DES ICONES ET DES CASES DE DEPART
        if (i == 0) { // Le Guerrier (en haut)
            joueurs[i].x = 3; joueurs[i].y = 0; joueurs[i].arme_recherchee = 'E';
            joueurs[i].icone = 'W';
            joueurs[i].case_sous_joueur = '-'; // Il commence sur le mur du haut
            printf("Your role : Warrior\n\n");
        }
        else if (i == 1) { // Le Ranger (à droite)
            joueurs[i].x = 6; joueurs[i].y = 3; joueurs[i].arme_recherchee = 'B';
            joueurs[i].icone = 'R'; 
            joueurs[i].case_sous_joueur = '|'; // Mur de droite
            printf("Your role : Ranger\n\n");            
        }
        else if (i == 2) { // Le Magicien (en bas)
            joueurs[i].x = 3; joueurs[i].y = 6; joueurs[i].arme_recherchee = 'G';
            joueurs[i].icone = 'M'; 
            joueurs[i].case_sous_joueur = '-'; // Mur du bas
            printf("Your role : Magician\n\n");            
        }
        else if (i == 3) { // Le Voleur (à gauche)
            joueurs[i].x = 0; joueurs[i].y = 3; joueurs[i].arme_recherchee = 'D';
            joueurs[i].icone = 'T'; 
            joueurs[i].case_sous_joueur = '|'; // Mur de gauche 
            printf("Your role : Thief\n\n");            
        }
        // On place immédiatement l'icône du joueur sur la carte de départ !
        labyrinthe[joueurs[i].y][joueurs[i].x] = joueurs[i].icone;
        
        // On met la mémoire des monstres vaincus à 0 pour toute la carte
        for (int y = 0; y < MAP_SIZE; y++) {
            for (int x = 0; x < MAP_SIZE; x++) {
                joueurs[i].monstres_vaincus[y][x] = 0;
            }
        }
        
        // On place immédiatement l'icône du joueur sur la carte de départ !
        labyrinthe[joueurs[i].y][joueurs[i].x] = joueurs[i].icone;

    }



    printf("\n\n--- THE GAME STARTS ! ---\n");
    


    // Affichage constant des noms demandé par le cahier des charges
    printf("Now playing : ");
    for (int i = 0; i < nb_joueurs; i++) {
        printf("[%s] ", joueurs[i].player_name);
    }
    printf("\n");

    afficher_labyrinthe(labyrinthe);
    

    char carte_cachee[MAP_SIZE][MAP_SIZE];
    init_carte_cachee(carte_cachee); 
    
    int partie_en_cours = 1;
    
    while (partie_en_cours == 1) {
        
        for (int i = 0; i < nb_joueurs; i++) {
            
            int joueur_vivant = 1; // À chaque début de tour, le joueur est vivant
            printf("\n====================================\n");
            printf("  >>> STARTING TURN FOR [%s] <<<\n", joueurs[i].player_name);
            printf("====================================\n");

            while (joueur_vivant == 1) {
                
                choisir_arme(&joueurs[i].arme_active);
                printf("Equipped arm: %c\n", joueurs[i].arme_active);
                    
                avancement(&joueurs[i], labyrinthe);
                afficher_labyrinthe(labyrinthe);

                joueur_vivant = declencher_evenement(&joueurs[i], i, carte_cachee, labyrinthe);
            }

            printf("End of turn for %s.\n", joueurs[i].player_name);
        } // On passe au joueur suivant dans le "for"
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "player.h"

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
        if (i == 0) { // Le Guerrier (en haut)
            joueurs[i].x = 3; joueurs[i].y = 0; joueurs[i].arme_recherchee = 'E';
            printf("Your role : Warrior\n\n");
        }
        else if (i == 1) { // Le Ranger (à droite)
            joueurs[i].x = 6; joueurs[i].y = 3; joueurs[i].arme_recherchee = 'B';
            printf("Your role : Ranger\n\n");            
        }
        else if (i == 2) { // Le Magicien (en bas)
            joueurs[i].x = 3; joueurs[i].y = 6; joueurs[i].arme_recherchee = 'G';
            printf("Your role : Magician\n\n");            
        }
        else if (i == 3) { // Le Voleur (à gauche)
            joueurs[i].x = 0; joueurs[i].y = 3; joueurs[i].arme_recherchee = 'D';
            printf("Your role : Thief\n\n");            
        }
    }
    printf("\n\n--- THE GAME STARTS NOW ! ---\n");
    
    // Affichage constant des noms demandé par le cahier des charges
    printf("Now playing : ");
    for (int i = 0; i < nb_joueurs; i++) {
        printf("[%s] ", joueurs[i].player_name);
    }
    printf("\n");

    afficher_labyrinthe(labyrinthe);
    
    // 3. LA BOUCLE DE JEU (GAME LOOP)
    // On fait jouer chaque joueur l'un après l'autre
    for (int i = 0; i < nb_joueurs; i++) {
            
        printf(" It's [%s]'s turn to play !\n", joueurs[i].player_name);
            
        // 1. Il choisit son arme
        choisir_arme(&joueurs[i].arme_active);
        printf("Equipped arm: %c\n", joueurs[i].arme_active);
            
        // 2. Il se déplace
        avancement(&joueurs[i].x, &joueurs[i].y);
            
        // 3. On affiche la carte mise à jour et sa nouvelle position
        printf("\nNew position of %s : (%d,%d)\n", joueurs[i].player_name, joueurs[i].x, joueurs[i].y);
        afficher_labyrinthe(labyrinthe);
            
        // Plus tard, on ajoutera ici la vérification :
        // "Est-ce qu'il est tombé sur un monstre ? Est-ce qu'il a gagné ?"
    }
}
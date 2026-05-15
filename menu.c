#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int afficher_menu_principal() {
    int choix = 0;

    while (choix != 4) {
        printf("\n=================================\n");
        printf("       MEMO-RPG : THE GAME       \n");
        printf("=================================\n");
        printf("1. Play a New Game\n");
        printf("2. Load a Saved Game\n");
        printf("3. View High Scores\n");
        printf("4. Quit\n");
        printf("=================================\n");
        printf("Your choice (1-4) : ");

        if (scanf("%d", &choix) != 1) {
            scanf("%*s"); // L'aspirateur magique si le joueur tape une lettre
            printf("\n[Error] Please enter a valid number.\n");
            continue; // Relance la boucle du menu
        }

        switch (choix) {
            case 1:
                printf("\n>>> Starting a new adventure...\n");
                return 1; // On quitte le menu et on lance le jeu dans le main

            case 2:
                printf("\n[Feature in progress] Loading save file...\n");
                // Plus tard : on lira le fichier save.txt ici
                break;

            case 3:
                printf("\n[Feature in progress] Fetching scores...\n");
                // Plus tard : on lira le fichier scores.txt ici
                break;

            case 4:
                printf("\nExiting MEMO-RPG. See you soon!\n");
                exit(0); // Ferme complètement le programme

            default:
                printf("\n[Error] Invalid choice. Please choose between 1 and 4.\n");
        }
    }
    return 0;
}
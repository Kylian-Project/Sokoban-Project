/**
 * @file jeuUtils.c
 * @brief Fichier contenant les fonctions supplémentaire dont la modification du tableau pour le jeu.
 */

#include "../include/jeuUtils.h"
#include "../include/loadLvl.h"


void RefreshTab(char level[MAX_ROWS][MAX_COLS], int rows, int cols, Player player, TabCaisse tabCaisse){
    clear();
    int isCaisse = 0;

    int nbCible = 0;
    int nbCibleValide = 0;
    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j < cols; j++) {
            isCaisse = 0;
            for (int k = 0; k < nbCaisse; k++){
                if (i == tabCaisse.caisse[k].y && j == tabCaisse.caisse[k].x) {
                    printw("C");
                    isCaisse = 1;
                }
            }
            if (isCaisse == 0){
                if (level[i][j] == 'o'){
                    nbCible++;
                    for (int k = 0; k < 3; k++) { // Vérifie si une caisse est à la même position
                        if (tabCaisse.caisse[k].x == j && tabCaisse.caisse[k].y == i) {
                            nbCibleValide++;
                            break;
                        }
                    }
                }
                if (i == player.y && j == player.x) {
                    printw("P");
                }
                else {
                    printw("%c", level[i][j]);
                }
            }
        }
    }
    refresh();
    if (nbCible == nbCibleValide){
        printf("Vous avez gagne, fin du jeu !\n");
        Jeu = 0;
    }
}


int peutBougerCaisse(char level[MAX_ROWS][MAX_COLS], TabCaisse tabCaisse, int x, int y){
    // Vérifie si la caisse peut bouger
    if (level[y][x] == '#' || level[y][x] == 'C'){
        return 0;
    }
    for (int i = 0; i < 3; i++){
        if (tabCaisse.caisse[i].x == x && tabCaisse.caisse[i].y == y){
            return 0;
        }
    }
    return 1;
}
#include "../include/jeuUtils.h"


/**
 * @brief Rafraîchit l'affichage du tableau de jeu.
 *
 * @param level Tableau représentant le niveau.
 * @param rows Nombre de lignes dans le tableau.
 * @param cols Nombre de colonnes dans le tableau.
 * @param player Structure représentant le joueur.
 * @param tabCaisse Tableau de structures représentant les caisses.
 */
void RefreshTab(char level[MAX_ROWS][MAX_COLS], int rows, int cols, Player player, TabCaisse tabCaisse){
    clear();
    int isCaisse = 0;

    int nbCible = 0;
    int nbCibleValide = 0;
    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j < cols; j++) {
            isCaisse = 0;
            for (int k = 0; k < 3; k++){
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
        printf("Vous avez gagne !");
        Jeu = 0;
    }
}

/**
 * @brief Vérifie si la caisse peut être déplacée à la nouvelle position.
 *
 * @param level Tableau représentant le niveau.
 * @param rows Nombre de lignes dans le tableau.
 * @param cols Nombre de colonnes dans le tableau.
 * @param player Structure représentant le joueur.
 * @param tabCaisse Tableau de structures représentant les caisses.
 * @param x Nouvelle position en colonne.
 * @param y Nouvelle position en ligne.
 * @return 1 si la caisse peut être déplacée, 0 sinon.
 */
int peutBougerCaisse(char level[MAX_ROWS][MAX_COLS], int rows, int cols, Player player, TabCaisse tabCaisse, int x, int y){
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